#define BS2_UPDATE_SOURCE
#include "BS2/BS2Update.h"
#include "BS2/BS2.h"
#include <private/os.h>
#include <private/es.h>
#include <private/nand.h>
#include <revolution/sc.h>
#include <revolution/dvd.h>

#include <string.h>

static u32 Flags0[BS2_UPDATE_ENTRY_COUNT] = {0};
static u32 Flags1[BS2_UPDATE_ENTRY_COUNT] = {0};
static OSThread Thread = {0};
static u8 ThreadStack[4096] = {0};
static BS2UpdateHeader UpdateHeader0 ALIGN32 = {0};
static BS2UpdateHeader UpdateHeader1 ALIGN32 = {0};

BS2UpdateEntry DiscEntries[BS2_UPDATE_ENTRY_COUNT] ADDRESS(0x80480000);

s32 WADCheckImport(u64 titleId, u16 titleVersion);
s32 WADImportDVDForBS(const char* path, void* buffer, u32 length);
s32 WADImportDVDExForBS(const char* path, void* buffer, u32 length);

static BS2UpdateEntry* pEntries = NULL;
static volatile u32 EntriesCount = 0;
static u32* pFlags = NULL;
static void* MemAllocator = NULL;
volatile int State = 0;
BS2UpdateEntry* CurrentEntry = 0;
static u32 RebootRequired = 0;
static BOOL ContainsSeatTitles = 0;
static u32 UpdateImportState = 0;
static u32 UpdateImportResult = 0;
volatile u32 StartUpdate = 0;
volatile u32 CancelUpdate = 0;
static u32 UpdateProgress = 0;
static volatile s32 rc = 0;
static u64 VersionIOS = 0;
static u32 VersionMEM2 = 0;
static u32 VersionES = 0;
static u32 ConsoleType = 0;
static void* FatalFunc = NULL;

char* getSuffix(const char* path) {
    char* suffix = strrchr(path, '.');
    if (suffix != NULL) {
        suffix++;
    }
    return suffix;
}

static void* UpdateThread(void* argument);

void BS2UpdateInit(void* allocator) {
    BS2Report("initialize BS2Update\n");
    ConsoleType = OSGetConsoleType();
    VersionES = __OSGetHollywoodRev();
    VersionMEM2 = OSGetPhysicalMem2Size();
    __OSGetIOSRev((OSIOSRev*)&VersionIOS);
    BS2Report("Console Type  : %08X\n", ConsoleType);
    BS2Report("Hollywood Rev : %08X\n", VersionES);
    BS2Report("MEM2 Size     : %08X\n", VersionMEM2);
    MemAllocator = allocator;
    State = 0;
    CurrentEntry = NULL;
    pEntries = NULL;
    EntriesCount = 0;
    memset(DiscEntries, 0, 0x40000);
    memset(EntriesToImport, 0, 0x40000);
    memset(Flags1, 0, sizeof(Flags1));
    BS2Report("Create update thread\n");
    OSCreateThread(&Thread, UpdateThread, NULL, ThreadStack + sizeof(ThreadStack),
                   sizeof(ThreadStack), 31, OS_THREAD_ATTR_DETACH);
    OSResumeThread(&Thread);
}

static inline u32 BS2SelectUpdateEntries(void) {
    BOOL missingFile;
    u32 index;
    u32 selectedCount;
    u32 requiredBytes;
    u32 requiredInodes;
    u32 channelCount;
    BS2UpdateEntry* seatEntries;
    BS2UpdateEntry* selectedSeats;
    u32 selectedSeatCount;
    BOOL regionValid;
    u32 titleRegion;
    u32 freeChannels;
    u32 freeBlocks;
    u32 freeInodes;
    u32 ticketCount;
    char productArea[8];
    u64 titleId;
    char updatePath[32];
    char seatPath[32];
    DVDFileInfo file;

    missingFile = FALSE;
    selectedCount = 0;
    requiredBytes = 0;
    requiredInodes = 0;
    channelCount = 0;
    freeChannels = 0;
    freeBlocks = 0;
    freeInodes = 0;
    selectedSeatCount = 0;
    State = 0;
    ContainsSeatTitles = FALSE;
    if (ES_GetTitleId(&titleId) != ES_ERR_OK) {
        regionValid = FALSE;
    } else {
        titleRegion = (u8)titleId;
        switch (SCGetProductArea()) {
        case SC_PRODUCT_AREA_JPN:
        case SC_PRODUCT_AREA_TWN:
            if (titleRegion == 'J' || titleRegion == 'D') {
                regionValid = TRUE;
                goto product_region_checked;
            }
            goto invalid_product_region;
        case SC_PRODUCT_AREA_USA:
            if (titleRegion == 'E' || titleRegion == 'D') {
                regionValid = TRUE;
                goto product_region_checked;
            }
            goto invalid_product_region;
        case SC_PRODUCT_AREA_EUR:
            if (titleRegion == 'P' || titleRegion == 'D') {
                regionValid = TRUE;
                goto product_region_checked;
            }
            goto invalid_product_region;
        case SC_PRODUCT_AREA_KOR:
            if (titleRegion == 'K') {
                regionValid = TRUE;
                goto product_region_checked;
            }
            goto invalid_product_region;
        case SC_PRODUCT_AREA_CHN:
            if (titleRegion == 'C') {
                regionValid = TRUE;
                goto product_region_checked;
            }
            goto invalid_product_region;
        default:
invalid_product_region:
            regionValid = FALSE;
            break;
        }
    }
product_region_checked:
    if (!regionValid) {
        BS2Report("Error: failed to check product region.");
        selectedCount = 0;
        goto selection_complete;
    }
    if (!SCGetProductAreaString(productArea, sizeof(productArea))) {
        BS2Report("Error: failed to get product information.");
        selectedCount = 0;
        goto selection_complete;
    }
    strcpy(updatePath, "__update.inf");
    strcat(updatePath, ".");
    strcat(updatePath, productArea);
    if (DVDConvertPathToEntrynum(updatePath) < 0) {
        switch (SCGetProductArea()) {
        case 0:
        case 1:
        case 2:
        case 6:
        case 11:
            strcpy(updatePath, "__update.inf");
            if (DVDConvertPathToEntrynum(updatePath) < 0) {
                BS2Report("Error: update information file is not found.");
                selectedCount = 0;
                goto selection_complete;
            }
            break;
        default:
            BS2Report("Error: update information file is not found.");
            selectedCount = 0;
            goto selection_complete;
        }
    }
    BS2Report("%s is found.\n", updatePath);
    if (!DVDOpen(updatePath, &file)) {
        BS2Report("Error: failed to open update information file.");
        selectedCount = 0;
        goto selection_complete;
    }
    if (DVDReadPrio(&file, &UpdateHeader0, sizeof(UpdateHeader0), 0, 2) < 0) {
        BS2Report("Error: failed to read update information header.");
        selectedCount = 0;
        goto selection_complete;
    }
    if (UpdateHeader0.wadCount == 0) {
        BS2Report("Error: no entry.");
        selectedCount = 0;
        goto selection_complete;
    }
    if (UpdateHeader0.wadCount > 32) {
        BS2Report("Error: found too many entries.");
        selectedCount = 0;
        goto selection_complete;
    }
    UpdateHeader0.wadCount += UpdateHeader0.extraCount;
    if (UpdateHeader0.wadCount > BS2_UPDATE_ENTRY_COUNT) {
        BS2Report("Error: found too many extra entries.");
        selectedCount = 0;
        goto selection_complete;
    }
    if (DVDReadPrio(&file, DiscEntries, UpdateHeader0.wadCount * sizeof(BS2UpdateEntry), 32, 2) < 0) {
        BS2Report("Error: failed to read update information.");
        selectedCount = 0;
        goto selection_complete;
    }
    {
        for (index = 0; index < UpdateHeader0.wadCount; index++) {
            if ((DiscEntries[index].attr & 1) == 0) {
                continue;
            }
            switch (OSGetPhysicalMem2Size()) {
            case 0x4000000:
                if ((DiscEntries[index].depend & 1) == 0) {
                    continue;
                }
                break;
            case 0x8000000:
                if ((DiscEntries[index].depend & 2) == 0) {
                    continue;
                }
                break;
            default:
                BS2Report("Cannot get physical MEM2 size\n");
                State = 5;
                selectedCount = 0;
                goto selection_complete;
            }
            if (DVDOpen(DiscEntries[index].path, &file) < 0) {
                BS2Report("%s is not found\n", DiscEntries[index].path);
                missingFile = TRUE;
                continue;
            }
            DiscEntries[index].size = file.length;
            if (DiscEntries[index].type == 0) {
                selectedCount++;
            } else if (WADCheckImport(DiscEntries[index].titleId, DiscEntries[index].titleVersion) == 0) {
                BS2Report("%s is already installed\n", DiscEntries[index].path);
                Flags1[index] = 0;
            } else {
                BS2Report("%s\n", DiscEntries[index].path);
                memcpy(&EntriesToImport[selectedCount], &DiscEntries[index], sizeof(BS2UpdateEntry));
                selectedCount++;
                Flags1[index] = 1;
            }
        }
    }
    strcpy(seatPath, "__seatholder.inf");
    strcat(seatPath, ".");
    strcat(seatPath, productArea);
    if (DVDConvertPathToEntrynum(seatPath) < 0) {
        switch (SCGetProductArea()) {
        case 0:
        case 1:
        case 2:
        case 6:
        case 11:
            strcpy(seatPath, "__seatholder.inf");
            if (DVDConvertPathToEntrynum(seatPath) < 0) {
                BS2Report("Error: update seatholder information file is not found.");
                goto seats_done;
            }
            break;
        default:
            BS2Report("Error: update seatholder information file is not found.");
            goto seats_done;
        }
    }
    BS2Report("%s is found.\n", seatPath);
    if (!DVDOpen(seatPath, &file)) {
        BS2Report("Error: failed to open update information file.");
        goto seats_done;
    }
    if (DVDReadPrio(&file, &UpdateHeader1, sizeof(UpdateHeader1), 0, 2) < 0) {
        BS2Report("Error: failed to read update information header.");
        goto seats_done;
    }
    if ((UpdateHeader1.wadCount | UpdateHeader1.extraCount) == 0) {
        BS2Report("Error: no entry.");
        goto seats_done;
    }
    UpdateHeader1.wadCount += UpdateHeader1.extraCount;
    if (UpdateHeader0.wadCount + UpdateHeader1.wadCount > BS2_UPDATE_ENTRY_COUNT) {
        BS2Report("Error: found too many extra entries.");
        goto seats_done;
    }
    seatEntries = DiscEntries + UpdateHeader0.wadCount;
    selectedSeats = EntriesToImport + selectedCount;
    if (DVDReadPrio(&file, seatEntries, UpdateHeader1.wadCount * sizeof(BS2UpdateEntry), 32, 2) < 0) {
        BS2Report("Error: failed to read update information.");
        goto seats_done;
    }
    for (index = 0; index < UpdateHeader1.wadCount; index++) {
        OSReport("type = %d\n", seatEntries[index].type);
        OSReport("attribute = %d\n", seatEntries[index].attr);
        OSReport("size = %d\n", seatEntries[index].size);
        OSReport("inodes = %d\n", seatEntries[index].inodes);
        OSReport("dependency = %d\n", seatEntries[index].depend);
        OSReport("path = %64s\n", seatEntries[index].path);
        OSReport("titleId = %llx\n", seatEntries[index].titleId);
        OSReport("titleVersion = %d\n", seatEntries[index].titleVersion);
        Flags0[index] = 0;
        if ((seatEntries[index].attr & 1) == 0) {
            continue;
        }
        switch (OSGetPhysicalMem2Size()) {
        case 0x4000000:
            if ((seatEntries[index].depend & 1) == 0) {
                continue;
            }
            break;
        case 0x8000000:
            if ((seatEntries[index].depend & 2) == 0) {
                continue;
            }
            break;
        default:
            BS2Report("Cannot get physical MEM2 size\n");
            State = 5;
            goto seats_done;
        }
        if (DVDOpen(seatEntries[index].path, &file) < 0) {
            BS2Report("%s is not found\n", seatEntries[index].path);
            missingFile = TRUE;
            continue;
        }
        if (seatEntries[index].type != 7) {
            continue;
        }
        if (ES_GetTicketViews(seatEntries[index].titleId, NULL, &ticketCount) != ES_ERR_OK) {
            BS2Report("Faild to get eTicket views.\n");
            continue;
        }
        if (ticketCount != 0) {
            continue;
        }
        if (SCGetWwwRestriction() && ((u32)(seatEntries[index].titleId & 0xFFFFFFFFULL) & 0xFFFFFF00) == 0x48414400) {
            Flags0[index] = 0;
            OSReport("Internet CH is restricted!\n");
            continue;
        }
        if (SCGetProductGameRegion() == 2 && (SCGetSimpleAddressID() >> 24) != 110 &&
            (u32)(seatEntries[index].titleId & 0xFFFFFFFFULL) == 0x48434A50) {
            Flags0[index] = 0;
            OSReport("BBCi CH is only for UK!\n");
            continue;
        }
        BS2Report("%s\n", seatEntries[index].path);
        memcpy(&selectedSeats[selectedSeatCount], &seatEntries[index], sizeof(BS2UpdateEntry));
        Flags0[index] = 1;
        channelCount++;
        selectedSeatCount++;
        requiredBytes += seatEntries[index].size;
        requiredInodes += seatEntries[index].inodes;
    }
    if (channelCount != 0) {
        if (!SCGetFreeChannelAppCount(&freeChannels)) {
            BS2Report("Error: cannot get channel count.");
            goto seats_done;
        }
        if (NANDSecretGetUserAvailableArea(&freeBlocks, &freeInodes) != NAND_RESULT_OK) {
            BS2Report("Error: cannot get free user blocks.");
            goto seats_done;
        }
        if ((freeBlocks << 14) < 0x1004000 || requiredBytes > (freeBlocks << 14) - 0x1004000) {
            BS2Report("Sufficient user blocks doesn't exist.");
            goto seats_done;
        }
        if (freeInodes < requiredInodes + 36) {
            BS2Report("Sufficient user inodes doesn't exist.");
            goto seats_done;
        }
        if (channelCount > freeChannels) {
            BS2Report("No enough blank channel.");
            goto seats_done;
        }
        for (index = 0; index < UpdateHeader1.wadCount; index++) {
            Flags1[UpdateHeader0.wadCount + index] = Flags0[index];
            if (Flags0[index] == 1) {
                selectedCount++;
            }
        }
        ContainsSeatTitles = TRUE;
        UpdateHeader0.wadCount += UpdateHeader1.wadCount;
    }
seats_done:
    if (missingFile) {
        State = 5;
        selectedCount = 0;
        goto selection_complete;
    }
    pEntries = EntriesToImport;
    pFlags = Flags1;
    {
        for (index = 0; index < UpdateHeader0.wadCount; index++) {
            if (Flags1[index] == 1) {
                BS2Report("File: %s\n", DiscEntries[index].path);
                BS2Report("Name: %s\n", DiscEntries[index].dataName);
                BS2Report("Info: %s\n", DiscEntries[index].dataMeta);
                BS2Report("Attr: %s\n", (DiscEntries[index].attr & 1) ? "Critical" : "Non critical");
                BS2Report("      %s\n", (DiscEntries[index].attr & 2) ? "Reboot" : "Not reboot");
            }
        }
    }
selection_complete:
    return selectedCount;
}

static void* UpdateThread(void* argument) {
    u32 index;
    s32 importResult;
    BS2Report("Start update thread\n");
    StartUpdate = 0;
    CancelUpdate = 0;
    EntriesCount = BS2SelectUpdateEntries();
    if (EntriesCount == 0) {
        State = 5;
        StartUpdate = 0;
        CancelUpdate = 0;
        BS2Report("Return update thread\n");
        return NULL;
    }
    State = 1;
    UpdateProgress = 0;
    {
        for (;;) {
            if (StartUpdate != 0) {
                if (UpdateProgress < UpdateHeader0.wadCount) {
                    BS2Report("Progress : %d\n", UpdateProgress);
                    if (Flags1[UpdateProgress] == 1) {
                        const char* path = DiscEntries[UpdateProgress].path;
                        BS2Report("Import : %s\n", path);
                        State = 2;
                        CurrentEntry = &DiscEntries[UpdateProgress];
                        if (DiscEntries[UpdateProgress].type == 0) {
                            UpdateProgress++;
                            continue;
                        }
                        if (((const BS2UpdateEntry *)DiscEntries)[UpdateProgress].type == 1) {
                            BS2Report("BS2WADImportDVD : ");
                            index = UpdateProgress;
                            if (strcmp(getSuffix(DiscEntries[index].path), "wad") == 0) {
                                importResult = WADImportDVDForBS(DiscEntries[index].path, (void*)BS2_UPDATE_ADDRESS, 0x80000);
                            } else {
                                importResult = 0;
                            }
                            rc = importResult;
                            BS2Report("rc = %d\n", rc);
                            if (rc != 0) {
                                NANDLoggingAddMessageAsync(NULL, "BS2 error. [%d] titleID: 0x%016llx %s line: %d",
                                                           rc, DiscEntries[UpdateProgress].titleId, "BS2Update.c", 0x3F5);
                                State = 5;
                                UpdateProgress = UpdateHeader0.wadCount + 1;
                                break;
                            }
                            if ((DiscEntries[UpdateProgress].attr & 2) != 0) {
                                RebootRequired = 1;
                            }
                            UpdateProgress++;
                        } else {
                            BS2Report("BS2WADImportDVDEx : ");
                            index = UpdateProgress;
                            if (strcmp(getSuffix(DiscEntries[index].path), "wad") == 0) {
                                importResult = WADImportDVDExForBS(DiscEntries[index].path, (void*)BS2_UPDATE_ADDRESS, 0x80000);
                            } else {
                                importResult = 0;
                            }
                            rc = importResult;
                            BS2Report("rc = %d\n", rc);
                            if (rc != 0) {
                                NANDLoggingAddMessageAsync(NULL, "BS2 error. [%d] titleID: 0x%016llx %s line: %d",
                                                           rc, DiscEntries[UpdateProgress].titleId, "BS2Update.c", 0x40F);
                                State = 5;
                                UpdateProgress = UpdateHeader0.wadCount + 1;
                                break;
                            }
                            if ((DiscEntries[UpdateProgress].attr & 2) != 0) {
                                RebootRequired = 1;
                            }
                            UpdateProgress++;
                        }
                    } else {
                        const char* path = DiscEntries[UpdateProgress].path;
                        BS2Report("Not import : %s\n", path);
                        UpdateProgress++;
                    }
                } else if (UpdateProgress == UpdateHeader0.wadCount) {
                    if (RebootRequired != 0) {
                        State = 4;
                    } else {
                        State = 3;
                    }
                    CurrentEntry = NULL;
                    UpdateProgress++;
                    break;
                }
            } else if (CancelUpdate != 0) {
                State = 6;
                break;
            }
        }
    }
    StartUpdate = 0;
    CancelUpdate = 0;
    UpdateImportState = 0;
    UpdateImportResult = 0;
    BS2Report("Return update thread\n");
    return NULL;
}

int BS2UpdateState() {
    return State;
}

void BS2StartUpdate() {
    StartUpdate = 1;
}

void BS2CancelUpdate() {
    CancelUpdate = 1;
}

BS2UpdateEntry* BS2GetUpdateEntry() {
    return pEntries;
}

u32 BS2GetUpdateEntryNum() {
    return EntriesCount;
}

BS2UpdateEntry* BS2GetCurrentEntry() {
    return CurrentEntry;
}

BOOL BS2ContainsSeatTitles() {
    return ContainsSeatTitles;
}
