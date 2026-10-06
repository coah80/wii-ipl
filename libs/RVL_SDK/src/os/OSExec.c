#include <private/os.h>
#include <revolution/os.h>
#include <revolution/os/OSBootInfo.h>


#include <revolution/esp.h>

#include <private/dvd.h>
#include <revolution/dvd.h>


#include <revolution/nand.h>
#include <revolution/sc.h>

#include <private/bus.h>

#include <stdio.h>
#include <string.h>


/* some string pooling (the first one is used but is just pooled first...)*/
static char execFailure[] = "\nOSExec(): Failed to exec %d in %d\n";

extern BOOL __OSInIPL;
extern BOOL __OSInNandBoot;

BOOL __OSInReboot;

static volatile u32 DVDLowIntType;
static u32 DesiredPartitionType;

extern void IPCReInit(void);
extern s32 IPCCltReInit(void);

static void ExecLowCallback(u32 intType) {
    DVDLowIntType = intType;
}

static BOOL ExecLowOk(u32 line) {
    while (DVDLowIntType == 0) {
    }

    if (DVDLowIntType != DVD_INTTYPE_TC) {
        OSReport(execFailure, DVDLowIntType, line);
        return FALSE;
    }

    DVDLowIntType = 0;
    return TRUE;
}

void __OSLaunchNextFirmware(void) {
    u8 i;
    s32 rc = -1;
    u32 ticketCnt = 1;
    ESTicketView* ticket;
    ESTicketView* diTicket;
    ESTitleId version = 0x0000000100000003;
    u32 mem2Size;
    u32 mem2End;
    DVDGameTOC* gameToc;
    DVDPartitionInfo* partInfo;
    DVDPartitionInfo* bootPart;
    DVDPartitionInfo* partPtr;
    ESTitleMeta* tmd;
    u32 numTmdBytes = 0;

    gameToc = (DVDGameTOC*)OSAllocFromMEM1ArenaLo(OSRoundUp32B(sizeof(DVDGameTOC)), DEFAULT_ALIGN);
    partInfo = (DVDPartitionInfo*)OSAllocFromMEM1ArenaLo(OSRoundUp32B(sizeof(DVDPartitionInfo) * 256), DEFAULT_ALIGN);
    tmd = (ESTitleMeta*)OSAllocFromMEM1ArenaLo(OSRoundUp32B(sizeof(ESTitleMeta)), 64);
    diTicket = (ESTicketView*)OSAllocFromMEM1ArenaLo(OSRoundUp32B(sizeof(ESTicketView)), DEFAULT_ALIGN);

    if (DesiredPartitionType == __OSLaunchPartitionType && *(u32*)OSPhysicalToCached(OS_ADDR_BOOT_PART_OFFSET) != 0) {
        rc = ESP_InitLib();
        if (rc == ES_ERR_OK) {
            rc = ESP_DiGetTicketView(NULL, diTicket);
        }
        if (rc == ES_ERR_OK) {
            rc = ESP_DiGetTmd(NULL, &numTmdBytes);
        }
        if (rc == ES_ERR_OK) {
            rc = ESP_DiGetTmd(tmd, &numTmdBytes);
        }
        ESP_CloseLib();

        {
            OSPlayTimeType playType = OS_PLAYTIME_PERMANENT;
            u32 remain = 0xFFFFFFFF;

            if (__OSGetPlayTime(diTicket, &playType, &remain) == ES_ERR_OK && playType == OS_PLAYTIME_TIME_LIMIT && remain == 0) {
                __OSWriteExpiredFlag();
                __OSReturnToMenuForError();
            }
        }
    }

    if (rc == ES_ERR_OK) {
        bootPart = partInfo;
        bootPart->partitionType = __OSLaunchPartitionType;
        bootPart->partition = (DVDGamePartition*)*(u32*)OSPhysicalToCached(OS_ADDR_BOOT_PART_OFFSET);
    } else {
        DVDLowIntType = 0;
        DVDLowClosePartition(ExecLowCallback);
        if (!ExecLowOk(0x378)) {
            __OSReturnToMenuForError();
        }

        DVDLowUnencryptedRead(gameToc, OSRoundUp32B(sizeof(DVDGameTOC)), 0x40000 >> 2, ExecLowCallback);
        if (!ExecLowOk(0x382)) {
            __OSReturnToMenuForError();
        }

        DVDLowUnencryptedRead(partInfo, OSRoundUp32B(sizeof(DVDPartitionInfo) * 256), (u32)gameToc->partitionInfo, ExecLowCallback);
        if (!ExecLowOk(0x38E)) {
            __OSReturnToMenuForError();
        }

        bootPart = NULL;
        partPtr = partInfo;
        for (i = 0; i < gameToc->partitionCount; i++) {
            if (partPtr->partitionType == DesiredPartitionType) {
                bootPart = partPtr;
            }
            partPtr++;
        }

        if (bootPart == NULL) {
            gameToc++;
            partPtr = partInfo + 4;
            for (i = 0; i < gameToc->partitionCount; i++) {
                if (partPtr->partitionType == DesiredPartitionType) {
                    bootPart = partPtr;
                }
                partPtr++;
            }
        }

        if (bootPart == NULL) {
            OSReport("\nOSExec(): The specified game doesn't exist in the disc\n");
            __OSReturnToMenuForError();
        }

        __OSLaunchPartitionType = bootPart->partitionType;
        *(u32*)OSPhysicalToCached(OS_ADDR_BOOT_PART_OFFSET) = (u32)bootPart->partition;

        DVDLowIntType = 0;
        if (__OSLockedAppType == OS_APP_TYPE_DVD) {
            DVDLowOpenPartitionWithTmdAndTicketView((u32)bootPart->partition, diTicket, numTmdBytes, tmd, 0, NULL, ExecLowCallback);
        } else {
            DVDLowOpenPartition((u32)bootPart->partition, NULL, 0, NULL, tmd, ExecLowCallback);
        }
        if (!ExecLowOk(0x3CB)) {
            __OSReturnToMenuForError();
        }

        DVDLowClosePartition(ExecLowCallback);
        if (!ExecLowOk(0x3D5)) {
            __OSReturnToMenuForError();
        }
    }

    version = tmd->head.sysVersion;

    rc = ESP_InitLib();
    if (rc != ES_ERR_OK) {
        OSReport(execFailure, rc, 0x3E0);
        __OSHotResetForError();
    }

    rc = ESP_GetTicketViews(version, NULL, &ticketCnt);
    if (ticketCnt != 1 || rc != ES_ERR_OK) {
        OSReport(execFailure, rc, 0x3E9);
        __OSHotResetForError();
    }

    ticket = (ESTicketView*)OSAllocFromMEM1ArenaLo(OSRoundUp32B(sizeof(ESTicketView) * ticketCnt), DEFAULT_ALIGN);
    rc = ESP_GetTicketViews(version, ticket, &ticketCnt);
    if (rc != ES_ERR_OK) {
        OSReport(execFailure, rc, 0x3F2);
        __OSHotResetForError();
    }

    DVDLowFinalize();

    mem2Size = *(u32*)OSPhysicalToCached(OS_ADDR_SIMULATED_MEM2_SIZE);
    mem2End = *(u32*)OSPhysicalToCached(OS_ADDR_ACCESSIBLE_MEM2);
    DCStoreRange(OSPhysicalToCached(OS_ADDR_PHYSICAL_MEM1_SIZE), OS_ADDR_MEMORY_MAP_SIZE);

    rc = ESP_LaunchTitle(version, ticket);
    if (rc != ES_ERR_OK) {
        OSReport(execFailure, rc, 0x402);
        __OSHotResetForError();
    }

    ESP_CloseLib();
    DCInvalidateRange(OSPhysicalToCached(OS_ADDR_PHYSICAL_MEM1_SIZE), OS_ADDR_MEMORY_MAP_SIZE);

    if (mem2Size < *(u32*)OSPhysicalToCached(OS_ADDR_SIMULATED_MEM2_SIZE)) {
        *(u32*)OSPhysicalToCached(OS_ADDR_ACCESSIBLE_MEM2) =
            mem2Size - (*(u32*)OSPhysicalToCached(OS_ADDR_SIMULATED_MEM2_SIZE) - *(u32*)OSPhysicalToCached(OS_ADDR_ACCESSIBLE_MEM2));
        *(u32*)OSPhysicalToCached(OS_ADDR_AVAILABLE_MEM2_END) =
            mem2Size - (*(u32*)OSPhysicalToCached(OS_ADDR_SIMULATED_MEM2_SIZE) - *(u32*)OSPhysicalToCached(OS_ADDR_AVAILABLE_MEM2_END));
        *(u32*)OSPhysicalToCached(OS_ADDR_IPC_BUFFER_START) =
            mem2Size - (*(u32*)OSPhysicalToCached(OS_ADDR_SIMULATED_MEM2_SIZE) - *(u32*)OSPhysicalToCached(OS_ADDR_IPC_BUFFER_START));
        *(u32*)OSPhysicalToCached(OS_ADDR_IPC_BUFFER_END) =
            mem2Size - (*(u32*)OSPhysicalToCached(OS_ADDR_SIMULATED_MEM2_SIZE) - *(u32*)OSPhysicalToCached(OS_ADDR_IPC_BUFFER_END));
        *(u32*)OSPhysicalToCached(OS_ADDR_SIMULATED_MEM2_SIZE) = mem2Size;
    }

    if (mem2End < *(u32*)OSPhysicalToCached(OS_ADDR_ACCESSIBLE_MEM2)) {
        __OSInitMemoryProtection();
    }

    __OSInitIPCBuffer();
    IPCReInit();
    IPCCltReInit();

    DVDLowInit();
    DVDLowIntType = 0;
    {
        DVDDiskID diskId;
        DVDLowReadDiskID(&diskId, ExecLowCallback);
    }
    if (!ExecLowOk(0x42E)) {
        __OSReturnToMenuForError();
    }

    if (__OSLockedAppType == OS_APP_TYPE_DVD) {
        DVDLowOpenPartitionWithTmdAndTicketView((u32)bootPart->partition, diTicket, numTmdBytes, tmd, 0, NULL, ExecLowCallback);
    } else {
        DVDLowOpenPartition((u32)bootPart->partition, NULL, 0, NULL, tmd, ExecLowCallback);
    }
    if (!ExecLowOk(0x445)) {
        __OSReturnToMenuForError();
    }
}

#define BI2_ROUND(x, a) (((x) & ~((a) - 1)))

BOOL PackArgs(void* addr, int argc, char** argv) {
    int argCount;
    u8* bootInfo2;
    u8* argPtr;

    bootInfo2 = addr;
    memset(bootInfo2, 0, BI2_SIZE);

    if (argc == 0) {
        *(u32*)&bootInfo2[BI2_OFFSET_ARGOFFSET] = 0;
    } else {
        argCount = argc;
        argPtr = bootInfo2 + BI2_OFFSET_ARGS;  // Arguments are located after BI2

        // For each argument
        while (--argc >= 0) {
            // Copy arguments
            argPtr -= (strlen(argv[argc]) + 1);
            strcpy((char*)argPtr, argv[argc]);

            argv[argc] = (char*)(argPtr - bootInfo2);
        }

        argPtr = bootInfo2 + BI2_ROUND(argPtr - bootInfo2, 4);
        argPtr -= (argCount + 1) * sizeof(argv);

        {
            u32 i;
            char** argList = (char**)argPtr;
            for (i = 0; i < argCount + 1; i++) {
                argList[i] = argv[i];
            }
        }

        // Write copied arguments to BI2
        argPtr -= sizeof(argCount);
        *(u32*)argPtr = argCount;
        *(u32*)&bootInfo2[BI2_OFFSET_ARGOFFSET] = argPtr - bootInfo2;
    }

    return TRUE;
}

void __OSGetExecParams(OSExecParams* params) {
    if ((u32)__OSExecParamsAddr >= OS_BASE_CACHED) {
        memcpy(params, __OSExecParamsAddr, sizeof(OSExecParams));
    } else {
        params->valid = FALSE;
    }
}

BOOL __OSCheckCompanyCode(ESTitleId titleId, BOOL diskApp) {
    NANDStatus status;
    char homePath[NAND_MAX_PATH + 1];
    char dataPath[NAND_MAX_PATH + 1];
    u16 curGroupId, launchGroupId;

    int ret = NAND_RESULT_OK;

    // Get home path
    ret = NANDGetHomeDir(homePath);
    if (ret != NAND_RESULT_OK) {
        return FALSE;
    }

    // Get status of home path
    ret = NANDGetStatus(homePath, &status);
    if (ret != NAND_RESULT_OK) {
        return FALSE;
    }

    curGroupId = status.groupId;
    if (curGroupId == 2) {
        if (OSGetAppType() == OS_APP_TYPE_DVD && (OSGetConsoleType() & OS_CONSOLE_MASK) == OS_CONSOLE_MASK_DEV) {
            DVDDiskID* diskId = DVDGetCurrentDiskID();
            curGroupId = *(u16*)diskId->company;
        }
    }

    if (diskApp) {
        // Get group ID from disc
        DVDDiskID* diskId = DVDGetCurrentDiskID();
        launchGroupId = *(u16*)diskId->company;
    } else {
        // Get group ID from title's data folder
        sprintf(dataPath, "/title/%08x/%08x/data", NANDTitleIdHi(titleId), NANDTitleIdLo(titleId));
        ret = NANDGetStatus(dataPath, &status);
        if (ret != NAND_RESULT_OK) {
            return FALSE;
        }
        launchGroupId = status.groupId;
    }

    return curGroupId == launchGroupId ? TRUE : FALSE;
}

BOOL __OSCheckTmdCountryCode(ESTmdView* tmd) {
    u32 country = 0;
    country = tmd->head.reserved.region;

    if (country == ES_REGION_ALL) {
        // Do not bother checking if its region free
        return TRUE;
    } else {
        // Check if region matches the system region
        return country == SCGetProductGameRegion() ? TRUE : FALSE;
    }
}

int __OSGetValidTicketIndex(ESTicketView* ticketViewList, u32 numTickets) {
    int ret, i;
    int bestIdx = 0;
    BOOL permanent = FALSE;
    u32 maxBit = 0, maxTime = 0;

    // Check if there are any tickets
    if (ticketViewList == NULL) {
        OSReport("NULL pointer detected: line %d in %s\n", 1339, __FILE__);
        return ES_ERR_INVALID;
    }

    for (i = 0; i < numTickets; i++) {
        u32 playTime;
        u16 accessMask;
        OSPlayTimeType type;
        // Get play time for its limit tickets
        ret = __OSGetPlayTime(&ticketViewList[i], &type, &playTime);
        if (ret > 0) {
            ret = ES_ERR_OK;
            continue;
        } else if (ret != ES_ERR_OK) {
            return ret;
        }

        switch (type) {
            case OS_PLAYTIME_PERMANENT: {
                u32 j, bits = 0;
                if (!permanent) {
                    bestIdx = i;
                    permanent = TRUE;
                }

                // Get bits to access.
                accessMask = (u16)((ticketViewList[i].accessMask[1] << 8) | ticketViewList[i].accessMask[0]);

                for (j = 0; j < 16; j++) {
                    if (accessMask & (1 << j))
                        bits++;
                }

                if (bits > maxBit) {
                    bestIdx = i;
                    maxBit = bits;
                }
                break;
            }
            case OS_PLAYTIME_TIME_LIMIT: {
                if (!permanent) {
                    if (playTime > maxTime) {
                        bestIdx = i;
                        maxTime = playTime;
                    }
                }
                break;
            }
            case OS_PLAYTIME_UNKNOWN:
            default: {
                break;
            }
        }
    }

    if (!permanent && maxTime == 0) {
        return -1;
    }

    return bestIdx;
}

void __OSLaunchTitle(ESTitleId titleId) {
    int ret;
    ESTicketView* tik;
    ESTicketView* tikList;
    u32 ticketLen = 1;

    // Initialize ESP library
    ret = ESP_InitLib();
    if (ret != ES_ERR_OK) {
        return;
    }
    // Allocate used ticket
    tik = (ESTicketView*)OSAllocFromMEM1ArenaLo(OSRoundUp32B(sizeof(ESTicketView)), DEFAULT_ALIGN);
    if (tik == NULL) {
        return;
    }
    memset(tik, 0, OSRoundUp32B(sizeof(ESTicketView)));

    // Get ticket counts
    ret = ESP_GetTicketViews(titleId, NULL, &ticketLen);
    if (ret != ES_ERR_OK) {
        return;
    }

    // Allocate list of tickets
    tikList = (ESTicketView*)OSAllocFromMEM1ArenaLo(OSRoundUp32B(sizeof(ESTicketView) * ticketLen), DEFAULT_ALIGN);
    if (tikList == NULL) {
        return;
    }
    // Get list of tickets
    ret = ESP_GetTicketViews(titleId, tikList, &ticketLen);
    if (ret != ES_ERR_OK) {
        return;
    }

    // Find the valid ticket
    ret = __OSGetValidTicketIndex(tikList, ticketLen);
    if (ret < 0) {
        return;
    }

    // Launch the title with the valid ticket.
    memcpy(tik, &tikList[ret], sizeof(ESTicketView));
    ret = ESP_LaunchTitle(titleId, tik);
    if (ret != ES_ERR_OK) {
        return;
    }

    // Lock up
    while (TRUE) {
    }
}

inline BOOL __OSCheckTmdSysVersion(ESTmdView* tmd) {
    ESTitleId systemId = 0x0000000100000003;

    char syspath[NAND_MAX_PATH + 1] ALIGN32;

    int ret = ES_ERR_OK;
    u32 numTicket = 0, numContent = 0;

    systemId = tmd->head.sysVersion;
    ret = ESP_GetTicketViews(systemId, NULL, &numTicket);
    if (ret != ES_ERR_OK || numTicket != 1) {
        return FALSE;
    }

    ret = ESP_ListTitleContentsOnCard(systemId, NULL, &numContent);
    if (ret != ES_ERR_OK || numContent == 0) {
        return FALSE;
    }

    return TRUE;
}

static BOOL __OSCheckTmdDriveSpinFlag(ESTmdView* tmd) {
    if (tmd->head.reserved.driveSpin & 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void LaunchCommon(ESTitleId titleId, u32 launchArg, const char** argv, BOOL launchCheck) {
    OSStateFlags state;
    OSNandbootInfo* info;
    u8* bi2;
    int argLen;

    char titleIdString[20];
    char** argvToPass;

    int i;

    ESTitleId title ALIGN32;
    ESTmdView* tmd = NULL;
    u32 tmdCount = 0;

    int ret = ES_ERR_OK;

    // Setup ES
    ret = ESP_InitLib();
    if (ret != ES_ERR_OK) {
        __OSReturnToMenuForError();
    }

    // Get TMD count
    ret = ESP_GetTmdView(titleId, NULL, &tmdCount);
    if (ret != ES_ERR_OK) {
        __OSReturnToMenuForError();
    }

    // Get TMD
    tmd = (ESTmdView*)OSAllocFromMEM1ArenaLo(OSRoundUp32B(tmdCount), 64);
    if (tmd == NULL) {
        __OSReturnToMenuForError();
    }
    ret = ESP_GetTmdView(titleId, tmd, &tmdCount);
    if (ret != ES_ERR_OK) {
        __OSReturnToMenuForError();
    }

    // Get firmware (IOS) from TMD
    if (!__OSCheckTmdSysVersion(tmd)) {
        OSReport("OSLaunchTitle(): Firmware is not installed\n");
        __OSReturnToMenuForError();
    }

    // Verification
    if (launchCheck) {
        if (!__OSCheckCompanyCode(titleId, FALSE)) {
            OSReport("OSLaunchTitle(): Company code is not correct\n");
            __OSReturnToMenuForError();
        }

        if (!__OSCheckTmdCountryCode(tmd)) {
            OSReport("OSLaunchTitle(): Country code is not correct\n");
            __OSReturnToMenuForError();
        }
    }

    // Check if TMD wants the disc to spin
    if (!__OSCheckTmdDriveSpinFlag(tmd)) {
        if (__DVDGetCoverStatus() == DVD_COVER_CLOSED) {
            __DVDResetWithNoSpinup();
        }
    }

    if (argv || launchArg) {
        bi2 = (u8*)OSAllocFromMEM1ArenaLo(0x2000, 64);
        info = (OSNandbootInfo*)((u32)bi2 + (0x2000 - sizeof(OSNandbootInfo)));

        sprintf(titleIdString, "%016llx", titleId);

        // Setup launch arguments

        argLen = 0;
        if (argv) {
            while (argv[argLen])
                argLen++;
        }

        argvToPass = OSAllocFromMEM1ArenaLo((++argLen + 1) * sizeof(char*), 1);
        argvToPass[0] = titleIdString;

        for (i = 1; i < argLen; i++) {
            argvToPass[i] = (char*)argv[i - 1];
        }

        PackArgs(bi2, argLen, argvToPass);

        if (__OSInIPL) {
            title = EXEC_SYSTEM_MENU_ID;
        } else {
            ret = ESP_InitLib();
            if (ret != ES_ERR_OK) {
                OSReport(execFailure, ret, 1712);
                __OSHotResetForError();
            }

            ret = ESP_GetTitleId(&title);
            if (ret != ES_ERR_OK) {
                OSReport(execFailure, ret, 1720);
                __OSHotResetForError();
            }
        }

        // Setup NANDBOOTINFO
        info->prevTitleId = title;
        info->argsOff = *(u32*)&bi2[BI2_OFFSET_ARGOFFSET];
        info->prevAppType = OSGetAppType();
        if (titleId == EXEC_SYSTEM_MENU_ID) {
            info->returnValue = OS_NANDBOOT_RETURN_MENU;
        } else {
            info->returnValue = OS_NANDBOOT_RETURN_GAME;
        }
        info->argValue = launchArg;

        // Write NANDBOOTINFO
        __OSCreateNandbootInfo();
        __OSWriteNandbootInfo(info);

        __OSReadStateFlags(&state);
        state.shutdownType = OS_STATE_FLAGS_SHUTDOWN_RETURN_MENU;
        if (titleId == EXEC_SYSTEM_MENU_ID) {
            state.discState = __OSGetDiscState(state.discState);
            state.menuMode = OS_STATE_FLAGS_MENUMODE_ARGS;
        }
        __OSWriteStateFlags(&state);
    }

    OSDisableScheduler();
    __OSShutdownDevices(OS_SHUTDOWN_LAUNCH);
    OSEnableScheduler();

    __OSLaunchTitle(titleId);

    // If failed to launch title, launch back to the menu.
    __OSLaunchMenu();
}

#define __COPY_VA_ARGS_TO_ARRAY(arg0, argv)                                                                                                          \
    {                                                                                                                                                \
        va_list list;                                                                                                                                \
        char* argPtr;                                                                                                                                \
        int i;                                                                                                                                       \
        argv = OSAllocFromMEM1ArenaLo(sizeof(*argv), 0x1000);                                                                                        \
        va_start(list, arg0);                                                                                                                        \
        for (i = 0, argPtr = (char*)arg0; (argv[i++] = argPtr) != NULL;) {                                                                           \
            argPtr = va_arg(list, char*);                                                                                                            \
        }                                                                                                                                            \
        va_end(list);                                                                                                                                \
    }

// "System" as in system menu
void __OSLaunchTitlevForSystem(ESTitleId titleId, u32 launchCode, const char** argv) {
    __OSUnRegisterStateEvent();

    OSSetArenaLo(EXEC_WORK_ARENA_LO);
    OSSetArenaHi(EXEC_WORK_ARENA_HI);

    // If we are in the system menu (but NOT in a nandloader)
    if (__OSInIPL && !__OSInNandBoot) {
        LaunchCommon(titleId, launchCode, argv, FALSE);
    } else {
        OSReport("__OSLaunchTitlevForSystem(): only system can call this function\n");
        __OSReturnToMenuForError();
    }
}

void __OSLaunchTitlelForSystem(ESTitleId titleId, u32 launchCode, const char* arg0, ...) {
    char** argv;

    __OSUnRegisterStateEvent();

    OSSetArenaLo(EXEC_WORK_ARENA_LO);
    OSSetArenaHi(EXEC_WORK_ARENA_HI);

    __COPY_VA_ARGS_TO_ARRAY(arg0, argv);

    // If we are in the system menu (but NOT in a nandloader)
    if (__OSInIPL && !__OSInNandBoot) {
        LaunchCommon(titleId, launchCode, (const char**)argv, FALSE);
    } else {
        OSReport("__OSLaunchTitlelForSystem(): only system can call this function\n");
        __OSReturnToMenuForError();
    }
}

void __OSReturnToMenul(u32 launchArg, const char* arg0, ...) {
    char** argv;

    __OSUnRegisterStateEvent();

    OSSetArenaLo(EXEC_WORK_ARENA_LO);
    OSSetArenaHi(EXEC_WORK_ARENA_HI);

    __COPY_VA_ARGS_TO_ARRAY(arg0, argv);

    LaunchCommon(EXEC_SYSTEM_MENU_ID, launchArg, (const char**)argv, FALSE);

    // If failed to launch title, launch back to the menu.
    __OSReturnToMenuForError();
}

static void OSLaunchDiskv(const DVDDiskID* id, u32 launchCode, const char** argv) {
    char idBuf[20];
    ESTitleId titleId ALIGN32;

    if (OSGetAppType() == OS_APP_TYPE_DVD) {
        OSReport("OSLaunchDisk(): You can't call this API from DVD application.  \n");
        __OSReturnToMenuForError();
    }

    if (DVDGetCurrentDiskID()->gameName[0] == '\0') {
        OSReport("OSLaunchDisk(): You must call DVDPrepareDisk before launching disc.\n");
        __OSReturnToMenuForError();
    }

    if (id != NULL && !DVDCompareDiskID(id, DVDGetCurrentDiskID())) {
        OSReport("OSLaunchDisk(): Specified id is different from one specified to DVDPrepareDisk.\n");
        __OSReturnToMenuForError();
    }

    strcpy(idBuf, "0000000000000000");
    if (argv != NULL && argv[0] != NULL) {
        strncpy(idBuf, argv[0], 16);
        idBuf[16] = '\0';
    }
    if (launchCode == 0xA0000000 && ESP_GetTitleId(&titleId) == ES_ERR_OK) {
        sprintf(idBuf, "%016llx", titleId);
    }
    if (idBuf[0] == '\0') {
        __OSReturnToMenuForError();
    }

    DesiredPartitionType = 0;
    __OSLaunchNextFirmware();
}

void OSLaunchDisk(const DVDDiskID* id, u32 launchCode, const char* firstArg, ...) {
    char** argv;

    __COPY_VA_ARGS_TO_ARRAY(firstArg, argv);
    OSLaunchDiskv(id, launchCode, (const char**)argv);
}

BOOL IsNewApploader(const char* date) {
    if (strncmp(date, "2004/02/01", 10) > 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static void OSLaunchPartitionv(ESTitleId titleId, u32 launchCode, const char** argv) {
    u8* bi2;
    int argc = 0;
    int i;
    char** argList;

    if (OSGetAppType() != OS_APP_TYPE_DVD) {
        OSReport("OSLaunchPartition(): You can't call this API from NAND application.  \n");
        __OSReturnToMenuForError();
    }

    if (NANDTitleIdHi(titleId) != 0x00010000) {
        OSReport("OSLaunchPartition(): Specified title ID is not DISC application.  \n");
        __OSReturnToMenuForError();
    }

    if (argv != NULL) {
        while (argv[argc] != NULL) {
            argc++;
        }
    }

    bi2 = (u8*)OSAllocFromMEM1ArenaLo(0x2000, 64);
    argList = (char**)OSAllocFromMEM1ArenaLo((argc + 1) * sizeof(char*), 1);
    for (i = 0; i < argc; i++) {
        argList[i] = (char*)argv[i];
    }
    argList[argc] = NULL;
    PackArgs(bi2, argc, argList);
    *(u32*)OSPhysicalToCached(OS_ADDR_NAND_TITLE_LAUNCH_CODE) = launchCode;
    *(u32*)OSPhysicalToCached(OS_ADDR_LAUNCH_EXEC_PARAMS) = (u32)bi2;

    DesiredPartitionType = NANDTitleIdLo(titleId);
    __OSLaunchNextFirmware();
}

void OSLaunchPartition(ESTitleId titleId, u32 launchCode, const char* firstArg, ...) {
    char** argv;

    __COPY_VA_ARGS_TO_ARRAY(firstArg, argv);
    OSLaunchPartitionv(titleId, launchCode, (const char**)argv);
}
