#define BS2_UPDATE_SOURCE
#include "BS2/BS2Update.h"
#include "BS2/BS2.h"
#include <private/os.h>
#include <private/es.h>
#include <private/nand.h>
#include <revolution/sc.h>
#include <revolution/dvd.h>

#include <string.h>

typedef struct UpdateThreadData {
    OSThread thread;
    u8 stack[4096];
} UpdateThreadData;

static u32 Flags0[BS2_UPDATE_ENTRY_COUNT];
static u32 Flags1[BS2_UPDATE_ENTRY_COUNT];
static UpdateThreadData Thread;
static BS2UpdateHeader UpdateHeader0 ALIGN32;
static BS2UpdateHeader UpdateHeader1 ALIGN32;

#define UPDATE_DISC_ENTRIES ((BS2UpdateEntry*)0x80480000)

s32 WADCheckImport(u64 titleId, u16 titleVersion);
s32 WADImportDVDForBS(const char* path, void* buffer, u32 length);
s32 WADImportDVDExForBS(const char* path, void* buffer, u32 length);

static BS2UpdateEntry* pEntries;
static u32 EntriesCount;
static u32* pFlags;
static void* MemAllocator;
int State;
BS2UpdateEntry* CurrentEntry;
static u32 RebootRequired;
static BOOL ContainsSeatTitles;
static u32 UpdateImportState;
static u32 UpdateImportResult;
u32 StartUpdate;
u32 CancelUpdate;
static u32 UpdateProgress;
static s32 rc;
static u64 VersionIOS;
static u32 VersionMEM2;
static u32 VersionES;
static u32 ConsoleType;
static void* FatalFunc;

#pragma force_active on
char* getSuffix(const char* path) {
    char* suffix = strrchr(path, '.');
    if (suffix != NULL) {
        suffix++;
    }
    return suffix;
}
#pragma force_active off

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
    memset(UPDATE_DISC_ENTRIES, 0, 0x40000);
    memset(EntriesToImport, 0, 0x40000);
    memset(Flags1, 0, sizeof(Flags1));
    BS2Report("Create update thread\n");
    OSCreateThread(&Thread.thread, UpdateThread, NULL, Thread.stack + sizeof(Thread.stack),
                   sizeof(Thread.stack), 31, 1);
    OSResumeThread(&Thread.thread);
}

static void* UpdateThread(void* argument) {
    BOOL missingFile;
    u32 selectedCount;
    u32 requiredBytes;
    u32 requiredInodes;
    u32 channelCount;
    u32 freeChannels;
    u32 freeBlocks;
    u32 freeInodes;
    u32 ticketCount;
    char productArea[8];
    u64 titleId;
    char updatePath[32];
    char seatPath[32];
    DVDFileInfo file;
    u32 index;
    BS2UpdateEntry* entry;
    BS2UpdateEntry* seatEntries;
    BS2UpdateEntry* selectedSeats;
    u32 selectedSeatCount;
    BOOL regionValid;
    u32 titleRegion;

    BS2Report("Start update thread\n");
    StartUpdate = 0;
    CancelUpdate = 0;
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
    if (ES_GetTitleId(&titleId) != 0) {
        regionValid = FALSE;
    } else {
        titleRegion = (u8)titleId;
        regionValid = FALSE;
        switch (SCGetProductArea()) {
        case 0:
        case 5:
            if (titleRegion == 'J' || titleRegion == 'D') {
                regionValid = TRUE;
            }
            break;
        case 1:
            if (titleRegion == 'E' || titleRegion == 'D') {
                regionValid = TRUE;
            }
            break;
        case 2:
            if (titleRegion == 'P' || titleRegion == 'D') {
                regionValid = TRUE;
            }
            break;
        case 6:
            if (titleRegion == 'K') {
                regionValid = TRUE;
            }
            break;
        case 11:
            if (titleRegion == 'C') {
                regionValid = TRUE;
            }
            break;
        }
    }
    if (!regionValid) {
        BS2Report("Error: failed to check product region.");
        goto no_updates;
    }
    if (!SCGetProductAreaString(productArea, sizeof(productArea))) {
        BS2Report("Error: failed to get product information.");
        goto no_updates;
    }
    strcpy(updatePath, "__update.inf");
    strcat(updatePath, "-");
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
                goto no_updates;
            }
            break;
        default:
            BS2Report("Error: update information file is not found.");
            goto no_updates;
        }
    }
    BS2Report("%s is found.\n", updatePath);
    if (!DVDOpen(updatePath, &file)) {
        BS2Report("Error: failed to open update information file.");
        goto no_updates;
    }
    if (DVDReadPrio(&file, &UpdateHeader0, sizeof(UpdateHeader0), 0, 2) < 0) {
        BS2Report("Error: failed to read update information header.");
        goto no_updates;
    }
    if (UpdateHeader0.wadCount == 0) {
        BS2Report("Error: no entry.");
        goto no_updates;
    }
    if (UpdateHeader0.wadCount > 32) {
        BS2Report("Error: found too many entries.");
        goto no_updates;
    }
    UpdateHeader0.wadCount += UpdateHeader0.extraCount;
    if (UpdateHeader0.wadCount > BS2_UPDATE_ENTRY_COUNT) {
        BS2Report("Error: found too many extra entries.");
        goto no_updates;
    }
    if (DVDReadPrio(&file, UPDATE_DISC_ENTRIES, UpdateHeader0.wadCount * sizeof(BS2UpdateEntry), 32, 2) < 0) {
        BS2Report("Error: failed to read update information.");
        goto no_updates;
    }
    for (index = 0; index < UpdateHeader0.wadCount; index++) {
        entry = &UPDATE_DISC_ENTRIES[index];
        if ((entry->attr & 1) == 0) {
            continue;
        }
        switch (OSGetPhysicalMem2Size()) {
        case 0x4000000:
            if ((entry->depend & 1) == 0) {
                continue;
            }
            break;
        case 0x8000000:
            if ((entry->depend & 2) == 0) {
                continue;
            }
            break;
        default:
            BS2Report("Cannot get physical MEM2 size\n");
            State = 5;
            goto no_updates;
        }
        if (DVDOpen(entry->path, &file) < 0) {
            BS2Report("%s is not found\n", entry->path);
            missingFile = TRUE;
            continue;
        }
        entry->size = file.length;
        if (entry->type == 0) {
            selectedCount++;
        } else if (WADCheckImport(entry->titleId, entry->titleVersion) == 0) {
            BS2Report("%s is already installed\n", entry->path);
            Flags1[index] = 0;
        } else {
            BS2Report("%s\n", entry->path);
            memcpy(&EntriesToImport[selectedCount], entry, sizeof(*entry));
            selectedCount++;
            Flags1[index] = 1;
        }
    }
    strcpy(seatPath, "__seatholder.inf");
    strcat(seatPath, "-");
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
    seatEntries = &UPDATE_DISC_ENTRIES[UpdateHeader0.wadCount];
    selectedSeats = &EntriesToImport[selectedCount];
    if (DVDReadPrio(&file, seatEntries, UpdateHeader1.wadCount * sizeof(BS2UpdateEntry), 32, 2) < 0) {
        BS2Report("Error: failed to read update information.");
        goto seats_done;
    }
    for (index = 0; index < UpdateHeader1.wadCount; index++) {
        entry = &seatEntries[index];
        OSReport("type = %d\n", entry->type);
        OSReport("attribute = %d\n", entry->attr);
        OSReport("size = %d\n", entry->size);
        OSReport("inodes = %d\n", entry->inodes);
        OSReport("dependency = %d\n", entry->depend);
        OSReport("path = %64s\n", entry->path);
        OSReport("titleId = %llx\n", entry->titleId);
        OSReport("titleVersion = %d\n", entry->titleVersion);
        Flags0[index] = 0;
        if ((entry->attr & 1) == 0) {
            continue;
        }
        switch (OSGetPhysicalMem2Size()) {
        case 0x4000000:
            if ((entry->depend & 1) == 0) {
                continue;
            }
            break;
        case 0x8000000:
            if ((entry->depend & 2) == 0) {
                continue;
            }
            break;
        default:
            BS2Report("Cannot get physical MEM2 size\n");
            State = 5;
            goto seats_done;
        }
        if (DVDOpen(entry->path, &file) < 0) {
            BS2Report("%s is not found\n", entry->path);
            missingFile = TRUE;
            continue;
        }
        if (entry->type != 7) {
            continue;
        }
        if (ES_GetTicketViews(entry->titleId, NULL, &ticketCount) != 0) {
            BS2Report("Faild to get eTicket views.\n");
            continue;
        }
        if (ticketCount != 0) {
            continue;
        }
        if (SCGetWwwRestriction() && ((u32)entry->titleId & 0xFFFFFF00) == 0x48414400) {
            Flags0[index] = 0;
            OSReport("Internet CH is restricted!\n");
            continue;
        }
        if (SCGetProductGameRegion() == 2 && (SCGetSimpleAddressID() >> 24) != 110 &&
            (u32)entry->titleId == 0x48434A50) {
            Flags0[index] = 0;
            OSReport("BBCi CH is only for UK!\n");
            continue;
        }
        BS2Report("%s\n", entry->path);
        memcpy(&selectedSeats[selectedSeatCount], entry, sizeof(*entry));
        Flags0[index] = 1;
        channelCount++;
        selectedSeatCount++;
        requiredBytes += entry->size;
        requiredInodes += entry->inodes;
    }
    if (channelCount != 0) {
        if (!SCGetFreeChannelAppCount(&freeChannels)) {
            BS2Report("Error: cannot get channel count.");
            goto seats_done;
        }
        if (NANDSecretGetUserAvailableArea(&freeBlocks, &freeInodes) != 0) {
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
        goto no_updates;
    }
    pEntries = EntriesToImport;
    pFlags = Flags1;
    for (index = 0; index < UpdateHeader0.wadCount; index++) {
        if (Flags1[index] == 1) {
            entry = &UPDATE_DISC_ENTRIES[index];
            BS2Report("File: %s\n", entry->path);
            BS2Report("Name: %s\n", entry->dataName);
            BS2Report("Info: %s\n", entry->dataMeta);
            BS2Report("Attr: %s\n", (entry->attr & 1) ? "Critical" : "Non critical");
            BS2Report("      %s\n", (entry->attr & 2) ? "Reboot" : "Not reboot");
        }
    }
    goto selection_done;
no_updates:
    selectedCount = 0;
selection_done:
    EntriesCount = selectedCount;
    if (EntriesCount == 0) {
        State = 5;
        StartUpdate = 0;
        CancelUpdate = 0;
        BS2Report("Return update thread\n");
        return NULL;
    }
    State = 1;
    UpdateProgress = 0;
    for (;;) {
        if (StartUpdate != 0) {
            if (UpdateProgress < UpdateHeader0.wadCount) {
                BS2Report("Progress : %d\n", UpdateProgress);
                if (Flags1[UpdateProgress] == 1) {
                    BS2Report("Import : %s\n", UPDATE_DISC_ENTRIES[UpdateProgress].path);
                    State = 2;
                    CurrentEntry = &UPDATE_DISC_ENTRIES[UpdateProgress];
                    if (UPDATE_DISC_ENTRIES[UpdateProgress].type == 0) {
                        UpdateProgress++;
                        continue;
                    }
                    if (UPDATE_DISC_ENTRIES[UpdateProgress].type == 1) {
                        BS2Report("BS2WADImportDVD : ");
                        index = UpdateProgress;
                        if (strcmp(getSuffix(UPDATE_DISC_ENTRIES[index].path), "wad") == 0) {
                            rc = WADImportDVDForBS(UPDATE_DISC_ENTRIES[index].path, (void*)BS2_UPDATE_ADDRESS, 0x80000);
                        } else {
                            rc = 0;
                        }
                        BS2Report("rc = %d\n", rc);
                        if (rc != 0) {
                            NANDLoggingAddMessageAsync(NULL, "BS2 error. [%d] titleID: 0x%016llx %s line: %d",
                                                       rc, UPDATE_DISC_ENTRIES[UpdateProgress].titleId, "BS2Update.c", 0x3F5);
                            State = 5;
                            UpdateProgress = UpdateHeader0.wadCount + 1;
                            break;
                        }
                        if ((UPDATE_DISC_ENTRIES[UpdateProgress].attr & 2) != 0) {
                            RebootRequired = 1;
                        }
                        UpdateProgress++;
                    } else {
                        BS2Report("BS2WADImportDVDEx : ");
                        index = UpdateProgress;
                        if (strcmp(getSuffix(UPDATE_DISC_ENTRIES[index].path), "wad") == 0) {
                            rc = WADImportDVDExForBS(UPDATE_DISC_ENTRIES[index].path, (void*)BS2_UPDATE_ADDRESS, 0x80000);
                        } else {
                            rc = 0;
                        }
                        BS2Report("rc = %d\n", rc);
                        if (rc != 0) {
                            NANDLoggingAddMessageAsync(NULL, "BS2 error. [%d] titleID: 0x%016llx %s line: %d",
                                                       rc, UPDATE_DISC_ENTRIES[UpdateProgress].titleId, "BS2Update.c", 0x40F);
                            State = 5;
                            UpdateProgress = UpdateHeader0.wadCount + 1;
                            break;
                        }
                        if ((UPDATE_DISC_ENTRIES[UpdateProgress].attr & 2) != 0) {
                            RebootRequired = 1;
                        }
                        UpdateProgress++;
                    }
                } else {
                    BS2Report("Not import : %s\n", UPDATE_DISC_ENTRIES[UpdateProgress].path);
                    UpdateProgress++;
                }
            } else if (UpdateProgress == UpdateHeader0.wadCount) {
                if (RebootRequired != 0) {
                    State = 4;
                } else {
                    State = 3;
                }
                UpdateProgress++;
                CurrentEntry = NULL;
                break;
            }
        } else if (CancelUpdate != 0) {
            State = 6;
            break;
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
