#include <private/nwc24.h>

#include <revolution/nand.h>
#include <revolution/nwc24/NWC24Dl.h>

#include <stdlib.h>
#include <string.h>

typedef struct {
    u16 id;
    u8 type;
    u8 priority;
    u32 flags;
    u32 appId;
    u32 nwc24IdHigh;
    u32 nwc24IdLow;
    u16 groupId;
    u8 unknown_0x16[2];
    u16 subTaskCount;
    u16 unknown_0x1a;
    u16 interval;
    u16 intervalWait;
    u32 unknown_0x20;
    u8 retryCount;
    u8 retryEnabled;
    u8 unknown_0x26[2];
    u32 retryMask;
    u8 unknown_0x2c[0x88];
    char url[0xec];
    char fileName[0x5c];
    u8 optOutFlags;
    u8 unknown_0x1fd[3];
} DlTaskData;

typedef struct {
    u32 magic;
    u32 version;
    u32 unknown_0x08;
    u16 unknown_0x0c;
    u16 unknown_0x0e;
    u16 legacyTaskCount;
    u16 taskCount;
    u16 maxTaskCount;
    u8 unknown_0x16[0x6a];
    struct {
        u32 flags;
        u32 nextTime;
        u32 lastAccess;
        u8 priority;
        u8 unknown_0x0d[3];
    } entries[NWC24_DL_TASK_MAX];
} DlTaskListHeader;

typedef struct {
    u32 sortMode;
    s32 comparisonValue;
    s32 selectedValue;
    u32 comparisonId;
    u32 initialized;
    u32 valid;
} DlTaskIterationState;

static char* DLFilePath = "/shared2/wc24/nwc24dl.bin";
static BOOL NWC24iLaxParameterCheck;

NWC24Err NWC24iLoadDlHeader();
NWC24Err NWC24iCheckDlHeaderConsistency(DlTaskListHeader* header, BOOL repair);
NWC24Err NWC24iCreateDlTaskList();
NWC24Err NWC24iOpenDlTaskList();
NWC24Err StoreDlTask(NWC24DlTask* dlTask);
NWC24Err AddTaskInternal(NWC24DlTask* dlTask, u16 taskCount, u16 maxTaskCount);
NWC24Err DeleteDlTask(NWC24DlTask* dlTask);
static s32 IterationPredicatorLastAccess(NWC24DlId taskId);
static s32 IterationPredicatorNextTime(NWC24DlId taskId);
static s32 IterationPredicatorPriority(NWC24DlId taskId);

NWC24Err NWC24InitDlTask(NWC24DlTask* dlTask, NWC24DLType dlType) {
    char homePath[64] = { 0 };
    u32 nwc24IdHigh;
    u32 nwc24IdLow;
    DlTaskData* task;
    DlTaskListHeader* header;
    NWC24Err result;
    BOOL allowed;
    BOOL useContentFile;

    NANDGetHomeDir(homePath);
    homePath[0x0f] = '\0';
    nwc24IdHigh = strtoul(homePath + 7, NULL, 16);
    homePath[0x18] = '\0';
    nwc24IdLow = strtoul(homePath + 0x10, NULL, 16);

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }
    if (dlTask == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (dlType >= 4) {
        return NWC24_ERR_INVALID_VALUE;
    }

    memset(dlTask, 0, sizeof(*dlTask));
    task = (DlTaskData*)dlTask;
    task->type = dlType;
    task->priority = 0x7f;
    task->appId = NWC24GetAppId();
    task->groupId = NWC24GetGroupId();
    task->nwc24IdHigh = nwc24IdHigh;
    task->nwc24IdLow = nwc24IdLow;
    task->id = 0xffff;
    task->subTaskCount = 1;
    task->interval = 0x0b40;
    task->intervalWait = 0x05a0;

    useContentFile = FALSE;
    if (dlType == NWC24_DLTYPE_OCTETSTREAM_V1 || dlType == NWC24_DLTYPE_OCTETSTREAM_V2) {
        useContentFile = TRUE;
    }
    if (useContentFile) {
        strcpy(task->fileName, "content.bin");
    }

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (dlTask == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    result = NWC24_OK;
    allowed = NWC24IsMsgLibOpenedByTool();
    if (!allowed) {
        u32 taskAppId = task->appId;
        u32 appId = NWC24GetAppId();
        allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
        if (!allowed) {
            allowed = FALSE;
            if (task->flags & 0x40) {
                if (task->groupId == NWC24GetGroupId()) {
                    allowed = TRUE;
                }
            }
            if (!allowed) {
                result = NWC24_ERR_PROTECTED;
            }
        }
    }

    if (result == NWC24_OK && task->id != 0xffff && task->id >= header->maxTaskCount) {
        result = NWC24_ERR_INVALID_VALUE;
    }

    return result >> 31;
}

NWC24Err NWC24SetDlId(NWC24DlTask* dlTask, NWC24DlId dlId) {
    NWC24Err result;
    u16 taskId;
    DlTaskData* task;
    DlTaskListHeader* header;
    NWC24Work* work = NWC24WorkP;

    if (work != NULL) {
        header = (DlTaskListHeader*)work->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        task = (DlTaskData*)dlTask;
        taskId = task->id;
        if (taskId != 0xffff && taskId >= header->maxTaskCount) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }

    if (result != NWC24_OK) {
        return result;
    }
    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (dlId >= header->maxTaskCount) {
        return NWC24_ERR_INVALID_VALUE;
    }

    task->id = dlId;
    return NWC24_OK;
}

NWC24Err NWC24SetDlPriority(NWC24DlTask* dlTask, u8 dlPriority) {
    DlTaskListHeader* header;
    NWC24Err result;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        result = NWC24_OK;
        if (!NWC24IsMsgLibOpenedByTool()) {
            u32 taskAppId = ((DlTaskData*)dlTask)->appId;
            u32 appId = NWC24GetAppId();
            BOOL sameAppId = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
            if (!sameAppId) {
                BOOL allowed = FALSE;
                if (((DlTaskData*)dlTask)->flags & 0x40) {
                    u16 groupId = ((DlTaskData*)dlTask)->groupId;
                    if (groupId == NWC24GetGroupId()) {
                        allowed = TRUE;
                    }
                }
                if (!allowed) {
                    result = NWC24_ERR_PROTECTED;
                }
            }
        }
        if (result == NWC24_OK) {
            u16 taskId = ((DlTaskData*)dlTask)->id;
            if (taskId != 0xffff && taskId >= header->maxTaskCount) {
                result = NWC24_ERR_INVALID_VALUE;
            }
        }
    }

    if (result != NWC24_OK) {
        return result;
    }

    ((DlTaskData*)dlTask)->priority = dlPriority;
    return NWC24_OK;
}

NWC24Err NWC24SetDlInterval(NWC24DlTask* dlTask, u16 dlInterval) {
    DlTaskListHeader* header;
    DlTaskData* task;
    u16 taskId;
    s64 nextTime;
    s32 intervalSeconds;
    NWC24Work* work;
    NWC24Err result;
    OSTime universalTime;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        task = (DlTaskData*)dlTask;
        result = NWC24_OK;
        if (!NWC24IsMsgLibOpenedByTool()) {
            u32 taskAppId = task->appId;
            u32 appId = NWC24GetAppId();
            if ((taskAppId & 0xffffff00) != (appId & 0xffffff00) &&
                (!(task->flags & 0x40) || task->groupId != NWC24GetGroupId())) {
                result = NWC24_ERR_PROTECTED;
            }
        }
        if (result == NWC24_OK) {
            taskId = task->id;
            if (taskId != 0xffff && taskId >= header->maxTaskCount) {
                result = NWC24_ERR_INVALID_VALUE;
            }
        }
    }

    if (result != NWC24_OK) {
        return result;
    }

    task = (DlTaskData*)dlTask;
    if (!NWC24iLaxParameterCheck) {
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        taskId = task->id;
        if (taskId >= header->taskCount && !(task->flags & 0x40000000) &&
            (dlInterval < 0x00b4 || dlInterval > 0x2760)) {
            return NWC24_ERR_INVALID_VALUE;
        }
    }

    if (task->interval != dlInterval) {
        task->interval = dlInterval;
        if (task->id != 0xffff) {
            universalTime = 0;
            if (NWC24iGetUniversalTime(&universalTime) >= NWC24_OK) {
                intervalSeconds = task->interval * 60;
                work = NWC24WorkP;
                nextTime = (s64)universalTime + intervalSeconds;
                if (work != NULL) {
                    header = (DlTaskListHeader*)work->dlHead;
                } else {
                    header = NULL;
                }
                if (dlTask == NULL) {
                    result = NWC24_ERR_INVALID_VALUE;
                } else if (header == NULL) {
                    result = NWC24_ERR_LIB_NOT_OPENED;
                } else {
                    taskId = task->id;
                    if (taskId != 0xffff && taskId >= header->maxTaskCount) {
                        result = NWC24_ERR_INVALID_VALUE;
                    } else {
                        result = NWC24_OK;
                    }
                }
                if (result == NWC24_OK) {
                    taskId = task->id;
                    if (taskId != 0xffff) {
                        nextTime /= 60;
                        if (work != NULL) {
                            header = (DlTaskListHeader*)work->dlHead;
                        } else {
                            header = NULL;
                        }
                        header->entries[taskId].nextTime = nextTime;
                    }
                }
            }
        }
    }
    return NWC24_OK;
}

NWC24Err NWC24SetDlUrl(NWC24DlTask* dlTask, const char* dlUrl) {
    DlTaskListHeader* header;
    DlTaskData* task;
    u16 taskId;
    NWC24Err result;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    task = (DlTaskData*)dlTask;
    if (!NWC24IsMsgLibOpenedByTool()) {
        u32 taskAppId = task->appId;
        u32 appId = NWC24GetAppId();
        BOOL allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
        if (!allowed) {
            allowed = FALSE;
            if (task->flags & 0x40) {
                if (task->groupId == NWC24GetGroupId()) {
                    allowed = TRUE;
                }
            }
            if (!allowed) {
                return NWC24_ERR_PROTECTED;
            }
        }
    }

    taskId = task->id;
    if (taskId != 0xffff && taskId >= header->maxTaskCount) {
        return NWC24_ERR_INVALID_VALUE;
    }

    result = NWC24iCheckStringLength(dlUrl, 7, 0x100);
    if (result < NWC24_OK) {
        return result;
    }
    if (strncmp(dlUrl, "http://", 7) != 0 && strncmp(dlUrl, "https://", 8) != 0) {
        result = NWC24_ERR_FORMAT;
    } else {
        result = NWC24_OK;
    }
    if (result < NWC24_OK) {
        return result;
    }

    task = (DlTaskData*)dlTask;
    if (!NWC24iLaxParameterCheck && (task->flags & 0x4) && strncmp(dlUrl, "http://", 7) == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    NWC24iStrLCpy(task->url, dlUrl, sizeof(task->url));
    return NWC24_OK;
}

NWC24Err NWC24SetDlFlags(NWC24DlTask* dlTask, u32 dlFlags) {
    DlTaskListHeader* header;
    DlTaskData* task;
    u16 taskId;
    NWC24Err result;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    task = (DlTaskData*)dlTask;
    result = NWC24_OK;
    if (!NWC24IsMsgLibOpenedByTool()) {
        u32 taskAppId = task->appId;
        u32 appId = NWC24GetAppId();
        if ((taskAppId & 0xffffff00) != (appId & 0xffffff00)) {
            BOOL allowed = FALSE;
            if (task->flags & 0x40) {
                u16 groupId = task->groupId;
                if (groupId == NWC24GetGroupId()) {
                    allowed = TRUE;
                }
            }
            if (!allowed) {
                result = NWC24_ERR_PROTECTED;
            }
        }
    }

    if (result == NWC24_OK) {
        taskId = task->id;
        if (taskId != 0xffff && taskId >= header->maxTaskCount) {
            result = NWC24_ERR_INVALID_VALUE;
        }
    }
    if (result != NWC24_OK) {
        return result;
    }

    task = (DlTaskData*)dlTask;
    if (!NWC24iLaxParameterCheck && (dlFlags & 0x4) && strncmp(task->url, "http://", 7) == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }
    switch (task->type) {
    case NWC24_DLTYPE_MULTIPART_V1:
    case NWC24_DLTYPE_OCTETSTREAM_V1: {
        if (dlFlags & 0x80000038) {
            return NWC24_ERR_INVALID_OPERATION;
        }
        break;
    }
    default:
        break;
    }
    task->flags = dlFlags;
    return NWC24_OK;
}

NWC24Err NWC24GetDlAppId(const NWC24DlTask* dlTask, u32* dlAppId) {
    NWC24Err result;
    const DlTaskData* task;
    DlTaskListHeader* header;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        task = (const DlTaskData*)dlTask;
        if (task->id != 0xffff && task->id >= header->maxTaskCount) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }
    if (result != NWC24_OK) {
        return result;
    }
    if (dlAppId == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    *dlAppId = ((const DlTaskData*)dlTask)->appId;
    return NWC24_OK;
}

NWC24Err NWC24DumpDlTask(NWC24DlTask* dlTask) {
    DlTaskListHeader* header;
    DlTaskData* task;
    u16 taskId;
    NWC24Err result;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        task = (DlTaskData*)dlTask;
        taskId = task->id;
        if (taskId != 0xffff && taskId >= header->maxTaskCount) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }
    if (result != NWC24_OK) {
        return result;
    }
    return NWC24_OK;
}

NWC24Err NWC24IterateDlTask(NWC24DlId* dlIterateId, BOOL begin) {
    DlTaskListHeader* header;
    NWC24Work* work;
    u16 taskId;
    u16 maxTaskCount;
    NWC24Err result;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }
    if (dlIterateId == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (begin) {
        *dlIterateId = 0;
    } else {
        *dlIterateId += 1;
    }

    work = NWC24WorkP;
    if (work != NULL) {
        header = (DlTaskListHeader*)work->dlHead;
    } else {
        header = NULL;
    }
    taskId = *dlIterateId;
    maxTaskCount = header->maxTaskCount;
    if (taskId >= maxTaskCount) {
        return NWC24_ERR_DONE;
    }

    do {
        if (work != NULL) {
            header = (DlTaskListHeader*)work->dlHead;
        } else {
            header = NULL;
        }
        if (taskId >= header->maxTaskCount) {
            return NWC24_ERR_INVALID_VALUE;
        }
        if (taskId == 0xffff) {
            return NWC24_ERR_INVALID_VALUE;
        }
        if (work != NULL) {
            header = (DlTaskListHeader*)work->dlHead;
        } else {
            header = NULL;
        }
        result = NWC24_ERR_NOT_FOUND;
        if (header->entries[taskId].flags == 0) {
            result = NWC24_OK;
        }
        if (result >= NWC24_OK) {
            *dlIterateId = taskId;
            return result;
        }
        taskId++;
    } while (taskId < header->maxTaskCount);
    return NWC24_ERR_DONE;
}

NWC24Err NWC24IterateDlTaskEx(NWC24DlIterateWork* dlIterateWork, NWC24DlId* dlIterateId) {
    DlTaskIterationState* state = (DlTaskIterationState*)dlIterateWork;
    s32 (*getValue)(NWC24DlId);
    NWC24DlId taskId;
    s32 value;
    BOOL descending;
    BOOL passesSelected;
    BOOL bestCandidate;
    NWC24Err result;
    BOOL found = FALSE;

    if (state->valid == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    descending = (state->sortMode >> 31) != 0;
    switch (state->sortMode & 0xffff) {
    case 0:
        getValue = IterationPredicatorLastAccess;
        break;
    case 1:
        getValue = IterationPredicatorNextTime;
        break;
    case 2:
        getValue = IterationPredicatorPriority;
        break;
    default:
        return NWC24_ERR_INVALID_VALUE;
    }

    if (state->initialized == 0) {
        result = NWC24IterateDlTask(&taskId, TRUE);
        while (result >= NWC24_OK) {
            value = getValue(taskId);
            if (value == state->comparisonValue && taskId > state->comparisonId) {
                *dlIterateId = taskId;
                state->comparisonValue = value;
                state->selectedValue = value;
                state->comparisonId = taskId;
                return NWC24_OK;
            }
            result = NWC24IterateDlTask(&taskId, FALSE);
        }
    } else {
        state->initialized = 0;
    }

    state->comparisonValue = descending ? 0x80000001 : 0x7fffffff;
    result = NWC24IterateDlTask(&taskId, TRUE);
    while (result >= NWC24_OK) {
        value = getValue(taskId);
        if (descending) {
            passesSelected = value <= state->selectedValue;
        } else {
            passesSelected = value >= state->selectedValue;
        }
        if (!passesSelected) {
            if (descending) {
                bestCandidate = value > state->comparisonValue;
            } else {
                bestCandidate = value < state->comparisonValue;
            }
            if (!bestCandidate) {
                *dlIterateId = taskId;
                state->comparisonValue = value;
                state->comparisonId = taskId;
                found = TRUE;
            }
        }
        result = NWC24IterateDlTask(&taskId, FALSE);
    }

    if (found) {
        state->selectedValue = state->comparisonValue;
        return NWC24_OK;
    }
    state->valid = 0;
    return NWC24_ERR_DONE;
}

NWC24Err NWC24UpdateDlTask(NWC24DlTask* dlTask) {
    DlTaskData* task = (DlTaskData*)dlTask;
    DlTaskListHeader* header;
    NWC24Err result;
    OSTime universalTime;
    NWC24DlId taskId;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    if (!NWC24IsMsgLibOpenedByTool()) {
        u32 taskAppId = task->appId;
        u32 appId = NWC24GetAppId();
        BOOL allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
        if (!allowed && (task->flags & 0x40)) {
            allowed = task->groupId == NWC24GetGroupId();
        }
        if (!allowed) {
            return NWC24_ERR_PROTECTED;
        }
    }

    taskId = task->id;
    if (taskId != 0xffff && taskId >= header->maxTaskCount) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (taskId != 0xffff) {
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        if (header == NULL) {
            return NWC24_ERR_LIB_NOT_OPENED;
        }
        if (taskId >= header->maxTaskCount) {
            return NWC24_ERR_INVALID_VALUE;
        }

        result = NWC24iGetUniversalTime(&universalTime);
        if (result >= NWC24_OK) {
            if (NWC24WorkP != NULL) {
                header = (DlTaskListHeader*)NWC24WorkP->dlHead;
            } else {
                header = NULL;
            }
            result = NWC24_OK;
            if (dlTask == NULL) {
                result = NWC24_ERR_INVALID_VALUE;
            } else if (header == NULL) {
                result = NWC24_ERR_LIB_NOT_OPENED;
            } else {
                taskId = task->id;
                if (taskId == 0xffff) {
                    result = NWC24_ERR_FAILED;
                } else if (taskId >= header->maxTaskCount) {
                    result = NWC24_ERR_INVALID_VALUE;
                }
            }
            if (result >= NWC24_OK) {
                header->entries[taskId].lastAccess = universalTime / 60;
            }
        }
        if (result < NWC24_OK) {
            return result;
        }
    }

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    result = NWC24_OK;
    if (dlTask == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        if (!NWC24IsMsgLibOpenedByTool()) {
            u32 taskAppId = task->appId;
            u32 appId = NWC24GetAppId();
            BOOL allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
            if (!allowed && (task->flags & 0x40)) {
                allowed = task->groupId == NWC24GetGroupId();
            }
            if (!allowed) {
                result = NWC24_ERR_PROTECTED;
            }
        }
        taskId = task->id;
        if (result == NWC24_OK && taskId != 0xffff && taskId >= header->maxTaskCount) {
            result = NWC24_ERR_INVALID_VALUE;
        }
    }

    if (result == NWC24_OK && task->id != 0xffff) {
        task->unknown_0x20 = 0;
        task->unknown_0x1a = 0;
    }

    if (task->retryEnabled == 1) {
        do {
            u8 retryCount;
            u32 retryMask;

            task->retryCount = (task->retryCount + 1) & 0x1f;
            if (NWC24WorkP != NULL) {
                header = (DlTaskListHeader*)NWC24WorkP->dlHead;
            } else {
                header = NULL;
            }
            if (dlTask == NULL) {
                return NWC24_ERR_INVALID_VALUE;
            }
            if (header == NULL) {
                return NWC24_ERR_LIB_NOT_OPENED;
            }
            if (!NWC24IsMsgLibOpenedByTool()) {
                u32 taskAppId = task->appId;
                u32 appId = NWC24GetAppId();
                BOOL allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
                if (!allowed && (task->flags & 0x40)) {
                    allowed = task->groupId == NWC24GetGroupId();
                }
                if (!allowed) {
                    return NWC24_ERR_PROTECTED;
                }
            }
            taskId = task->id;
            if (taskId != 0xffff && taskId >= header->maxTaskCount) {
                return NWC24_ERR_INVALID_VALUE;
            }
            if (task->retryEnabled == 0) {
                return NWC24_ERR_INVALID_OPERATION;
            }
            retryCount = task->retryCount;
            retryMask = task->retryMask;
            if (retryMask == 0) {
                return NWC24_ERR_FATAL;
            }
            if (retryCount > 0x1f) {
                return NWC24_ERR_INVALID_VALUE;
            }
            result = NWC24_OK;
            if ((retryMask & (1 << retryCount)) == 0) {
                result = NWC24_ERR_DISABLED;
            }
        } while (result == NWC24_ERR_DISABLED);
        if (result < NWC24_OK) {
            return result;
        }
    }

    return StoreDlTask(dlTask);
}

NWC24Err NWC24DeleteDlTask(NWC24DlTask* dlTask) {
    DlTaskData* task;
    DlTaskListHeader* header;
    NWC24Err result;

    if (NWC24GetAppId() == 0x48414541) {
        result = NWC24_OK;
    } else {
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }

        if (dlTask == NULL) {
            return NWC24_ERR_INVALID_VALUE;
        }
        if (header == NULL) {
            return NWC24_ERR_LIB_NOT_OPENED;
        }

        task = (DlTaskData*)dlTask;
        if (!NWC24IsMsgLibOpenedByTool()) {
            u32 taskAppId = task->appId;
            u32 appId = NWC24GetAppId();
            BOOL allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
            if (!allowed && (task->flags & 0x40)) {
                allowed = task->groupId == NWC24GetGroupId();
            }
            if (!allowed) {
                return NWC24_ERR_PROTECTED;
            }
        }

        if (task->id != 0xffff && task->id >= header->maxTaskCount) {
            return NWC24_ERR_INVALID_VALUE;
        }
        result = NWC24_OK;
    }

    if (result != NWC24_OK) {
        return result;
    }

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (dlTask == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    task = (DlTaskData*)dlTask;
    if (task->id != 0xffff && task->id >= header->maxTaskCount) {
        return NWC24_ERR_INVALID_VALUE;
    }

    result = DeleteDlTask(dlTask);
    if (result >= NWC24_OK) {
        task->id = 0xffff;
    }
    return result;
}

NWC24Err NWC24AddDlTask(NWC24DlTask* dlTask) {
    DlTaskListHeader* header;
    NWC24File file;
    NWC24Err result;
    OSTime universalTime;
    s64 nextTime;
    s32 intervalSeconds;
    u16 taskCount;
    u16 maxTaskCount;
    u16 taskId;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (header->maxTaskCount == 0 && header->legacyTaskCount != 0) {
        header->maxTaskCount = header->legacyTaskCount;
        if (header->legacyTaskCount > 0x20) {
            header->legacyTaskCount = 0x20;
        }
        result = NWC24FOpen(&file, DLFilePath, 4);
        if (result >= NWC24_OK) {
            result = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
            if (result >= NWC24_OK) {
                result = NWC24FWrite(header, 0x800, &file);
            }
            NWC24FClose(&file);
        }
    }

    if (header->maxTaskCount < 1 || header->taskCount < 1 ||
        header->maxTaskCount < header->taskCount) {
        return NWC24_ERR_BROKEN;
    }

    taskCount = header->taskCount;
    maxTaskCount = header->maxTaskCount;
    result = AddTaskInternal(dlTask, taskCount, maxTaskCount);
    if (result < NWC24_OK) {
        return result;
    }

    universalTime = 0;
    result = NWC24iGetUniversalTime(&universalTime);
    if (result < NWC24_OK) {
        return result;
    }

    intervalSeconds = ((DlTaskData*)dlTask)->interval * 60;
    nextTime = universalTime + intervalSeconds;
    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    result = NWC24_OK;
    if (dlTask == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        taskId = ((DlTaskData*)dlTask)->id;
        if (taskId == 0xffff) {
            result = NWC24_ERR_FAILED;
        } else if (taskId >= header->maxTaskCount) {
            result = NWC24_ERR_INVALID_VALUE;
        }
    }

    if (result >= NWC24_OK) {
        nextTime /= 60;
        header->entries[taskId].nextTime = nextTime;
    }
    return result;
}

NWC24Err NWC24GetDlTask(NWC24DlTask* dlTask, NWC24DlId dlId) {
    DlTaskListHeader* header;
    NWC24File file;
    NWC24Err result;
    NWC24Err operationResult;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }
    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (dlId >= header->maxTaskCount || dlId == 0xffff) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        if (header->entries[dlId].flags == 0) {
            result = NWC24_ERR_NOT_FOUND;
        } else {
            result = NWC24_OK;
        }
    }
    if (result < NWC24_OK) {
        return result;
    }

    result = NWC24FOpen(&file, DLFilePath, 0x0a);
    if (result < NWC24_OK) {
        return result;
    }

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header->maxTaskCount > NWC24_DL_TASK_MAX || dlId >= header->maxTaskCount) {
        operationResult = NWC24_ERR_INVALID_VALUE;
    } else {
        operationResult = NWC24FSeek(&file, 0x800 + dlId * 0x200, NWC24_SEEK_BEG);
    }
    if (operationResult < NWC24_OK) {
        result = operationResult;
    } else {
        operationResult = NWC24FRead(dlTask, 0x200, &file);
        result = NWC24_OK;
        if (operationResult < NWC24_OK) {
            result = operationResult;
        }
    }
    operationResult = NWC24FClose(&file);
    if (result != NWC24_OK) {
        return result;
    }
    return operationResult;
}

NWC24Err NWC24PurgeOldestDlTask() {
    DlTaskIterationState state;
    NWC24File file;
    NWC24DlTask task;
    DlTaskListHeader* header;
    NWC24DlId taskId;
    NWC24DlTask* taskPointer;
    NWC24DlId selectedId;
    NWC24Err result;
    NWC24Err closeResult;

    memset(&state, 0, sizeof(state));
    state.sortMode = 0;
    state.comparisonValue = 0x7fffffff;
    state.selectedValue = (s32)0x80000001;
    state.comparisonId = 0xffffffff;
    state.initialized = 1;
    state.valid = 1;
    taskId = 0;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    result = NWC24_OK;
    do {
        result = NWC24IterateDlTaskEx((NWC24DlIterateWork*)&state, &taskId);
        if (result != NWC24_OK) {
            break;
        }
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
    } while (taskId < header->taskCount);

    if (result == NWC24_ERR_DONE) {
        return NWC24_ERR_FAILED;
    }
    if (result < NWC24_OK) {
        return result;
    }

    taskPointer = &task;
    selectedId = taskId;
    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }
    if (selectedId >= header->maxTaskCount || selectedId == 0xffff) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header->entries[selectedId].flags == 0) {
        return NWC24_ERR_NOT_FOUND;
    }

    result = NWC24FOpen(&file, DLFilePath, 0x0a);
    if (result < NWC24_OK) {
        return result;
    }

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header->maxTaskCount > NWC24_DL_TASK_MAX || selectedId >= header->maxTaskCount) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24FSeek(&file, 0x800 + selectedId * 0x200, NWC24_SEEK_BEG);
    }
    if (result >= NWC24_OK) {
        result = NWC24FRead(taskPointer, sizeof(task), &file);
    }
    closeResult = NWC24FClose(&file);
    if (result < NWC24_OK) {
        return result;
    }
    result = closeResult;
    if (result < NWC24_OK) {
        return result;
    }

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else if (((DlTaskData*)taskPointer)->id == 0xffff ||
               ((DlTaskData*)taskPointer)->id >= header->maxTaskCount) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24_OK;
    }
    if (result == NWC24_OK) {
        result = DeleteDlTask(taskPointer);
    }
    if (result >= NWC24_OK) {
        ((DlTaskData*)taskPointer)->id = 0xffff;
    }
    return result;
}

NWC24Err NWC24ManageDlTaskListForMenu() {
    DlTaskListHeader* header;
    NWC24File file;
    NWC24DlTask task;
    NWC24Err result;
    NWC24Err closeResult;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    result = NWC24_OK;
    if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    }
    if (result < NWC24_OK) {
        return result;
    }
    if (header->maxTaskCount >= NWC24_DL_TASK_MAX) {
        return result;
    }

    result = NWC24ExtendDlTaskList(NWC24_DL_TASK_MAX);
    if (result < NWC24_OK) {
        return result;
    }
    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    result = NWC24_OK;
    if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else if (header->maxTaskCount <= 2) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (header->entries[2].flags == 0) {
        result = NWC24_ERR_NOT_FOUND;
    }
    if (result < NWC24_OK) {
        return result;
    }

    result = NWC24FOpen(&file, DLFilePath, 0x0a);
    if (result < NWC24_OK) {
        return result;
    }

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else if (header->maxTaskCount > NWC24_DL_TASK_MAX || header->maxTaskCount <= 2) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24FSeek(&file, 0xc00, NWC24_SEEK_BEG);
    }
    if (result >= NWC24_OK) {
        result = NWC24FRead(&task, sizeof(task), &file);
    }
    closeResult = NWC24FClose(&file);
    if (result >= NWC24_OK) {
        result = closeResult;
    }
    if (result == NWC24_ERR_NOT_FOUND) {
        return NWC24_OK;
    }
    if (result < NWC24_OK) {
        return result;
    }

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else if (((DlTaskData*)&task)->id == 0xffff ||
               ((DlTaskData*)&task)->id >= header->maxTaskCount) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24_OK;
    }
    if (result == NWC24_OK) {
        result = DeleteDlTask(&task);
    }
    if (result >= NWC24_OK) {
        ((DlTaskData*)&task)->id = 0xffff;
    }
    return result;
}

NWC24Err NWC24GetDlOptOutFlags(NWC24DlTask* dlTask, u8* dlOptOutFlags) {
    DlTaskListHeader* header;
    DlTaskData* task;
    u16 taskId;
    NWC24Err result;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (header == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        task = (DlTaskData*)dlTask;
        taskId = task->id;
        if (taskId != 0xffff && taskId >= header->maxTaskCount) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }

    if (result != NWC24_OK) {
        return result;
    }
    if (dlOptOutFlags == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    *dlOptOutFlags = ((DlTaskData*)dlTask)->optOutFlags;
    return NWC24_OK;
}

NWC24Err NWC24iOpenDlTaskList() {
    NWC24Err result;
    DlTaskListHeader* header;

    result = NWC24iLoadDlHeader();
    if (result >= NWC24_OK) {
        NWC24iSynchronizeRtcCounter(FALSE);
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        result = NWC24iCheckDlHeaderConsistency(header, FALSE);
        if (result >= NWC24_OK) {
            result = NWC24_OK;
        }
    }
    return result;
}

NWC24Err NWC24iCloseDlTaskList() {
    return NWC24_OK;
}

NWC24Err NWC24ExtendDlTaskList(u32 num) {
    DlTaskListHeader* header;
    NWC24File file;
    DlTaskData* task;
    NWC24Err result;
    NWC24Err closeResult;
    u16 taskId;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    taskId = header->maxTaskCount;
    if (num > NWC24_DL_TASK_MAX || taskId > num) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (taskId == num) {
        return NWC24_OK;
    }

    header->maxTaskCount = num;
    result = NWC24FOpen(&file, DLFilePath, 4);
    if (result < NWC24_OK) {
        return result;
    }

    for (; taskId < num; taskId++) {
        if (NWC24WorkP != NULL) {
            task = (DlTaskData*)NWC24WorkP->dlTask;
        } else {
            task = NULL;
        }
        memset(task, 0, sizeof(*task));
        task->type = 0xff;
        task->id = taskId;
        memset(&((DlTaskListHeader*)NWC24WorkP->dlHead)->entries[taskId], 0,
               sizeof(header->entries[taskId]));

        if (((DlTaskListHeader*)NWC24WorkP->dlHead)->maxTaskCount > NWC24_DL_TASK_MAX ||
            taskId >= ((DlTaskListHeader*)NWC24WorkP->dlHead)->maxTaskCount) {
            result = NWC24_ERR_INVALID_VALUE;
            break;
        }
        result = NWC24FSeek(&file, 0x800 + taskId * 0x200, NWC24_SEEK_BEG);
        if (result >= NWC24_OK) {
            result = NWC24FWrite(task, sizeof(*task), &file);
            if (result >= NWC24_OK) {
                result = NWC24_OK;
            }
        }
        if (result < NWC24_OK) {
            break;
        }
    }

    if (result >= NWC24_OK) {
        result = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
        if (result >= NWC24_OK) {
            result = NWC24FWrite((DlTaskListHeader*)NWC24WorkP->dlHead, 0x800, &file);
            if (result >= NWC24_OK) {
                result = NWC24_OK;
            }
        }
    }
    closeResult = NWC24FClose(&file);
    if (result != NWC24_OK) {
        closeResult = result;
    }
    result = NWC24iLoadDlHeader();
    if (closeResult != NWC24_OK) {
        result = closeResult;
    }
    return result;
}

NWC24Err NWC24iCheckDlHeaderConsistency(DlTaskListHeader* header, BOOL repair) {
    NWC24DlId taskId;
    NWC24DlTask task;
    NWC24File file;
    DlTaskListHeader* currentHeader;
    NWC24Err result;
    NWC24Err closeResult;

    for (taskId = 0; taskId < header->maxTaskCount; taskId++) {
        if (NWC24WorkP != NULL) {
            currentHeader = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            currentHeader = NULL;
        }
        result = NWC24_OK;
        if (currentHeader == NULL) {
            result = NWC24_ERR_LIB_NOT_OPENED;
        } else if (taskId >= currentHeader->maxTaskCount || taskId == 0xffff) {
            result = NWC24_ERR_INVALID_VALUE;
        } else if (currentHeader->entries[taskId].flags == 0) {
            result = NWC24_ERR_NOT_FOUND;
        }
        if (result < NWC24_OK) {
            continue;
        }

        if (repair) {
            if (NWC24WorkP != NULL) {
                currentHeader = (DlTaskListHeader*)NWC24WorkP->dlHead;
            } else {
                currentHeader = NULL;
            }
            result = NWC24_OK;
            if (currentHeader == NULL) {
                result = NWC24_ERR_LIB_NOT_OPENED;
            } else if (taskId >= currentHeader->maxTaskCount || taskId == 0xffff) {
                result = NWC24_ERR_INVALID_VALUE;
            } else if (currentHeader->entries[taskId].flags == 0) {
                result = NWC24_ERR_NOT_FOUND;
            }
            if (result < NWC24_OK) {
                continue;
            }

            result = NWC24FOpen(&file, DLFilePath, 0x0a);
            if (result < NWC24_OK) {
                return result;
            }
            if (NWC24WorkP != NULL) {
                currentHeader = (DlTaskListHeader*)NWC24WorkP->dlHead;
            } else {
                currentHeader = NULL;
            }
            if (currentHeader == NULL) {
                result = NWC24_ERR_LIB_NOT_OPENED;
            } else if (currentHeader->maxTaskCount > NWC24_DL_TASK_MAX ||
                       taskId >= currentHeader->maxTaskCount) {
                result = NWC24_ERR_INVALID_VALUE;
            } else {
                result = NWC24FSeek(&file, 0x800 + taskId * 0x200, NWC24_SEEK_BEG);
            }
            if (result >= NWC24_OK) {
                result = NWC24FRead(&task, sizeof(task), &file);
            }
            closeResult = NWC24FClose(&file);
            if (result >= NWC24_OK) {
                result = closeResult;
            }
            if (result == NWC24_ERR_NOT_FOUND) {
                continue;
            }
            if (result < NWC24_OK) {
                return result;
            }
            if (NWC24WorkP != NULL) {
                currentHeader = (DlTaskListHeader*)NWC24WorkP->dlHead;
            } else {
                currentHeader = NULL;
            }
            if (currentHeader != NULL && taskId >= currentHeader->taskCount &&
                ((DlTaskData*)&task)->subTaskCount == 0) {
                if (((DlTaskData*)&task)->id == 0xffff ||
                    ((DlTaskData*)&task)->id >= currentHeader->maxTaskCount) {
                    result = NWC24_ERR_INVALID_VALUE;
                } else {
                    result = DeleteDlTask(&task);
                }
                if (result < NWC24_OK) {
                    return result;
                }
                ((DlTaskData*)&task)->id = 0xffff;
            }
        }
    }

    return NWC24_OK;
}

NWC24Err NWC24iCreateDlTaskList() {
    NWC24File file;
    DlTaskListHeader* header;
    DlTaskData* task;
    NWC24Err result;
    u16 taskId;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    memset(header, 0, 0x800);
    header->magic = 0x5763446c;
    header->version = 1;
    header->unknown_0x0c = 0;
    header->unknown_0x0e = 0;
    header->maxTaskCount = NWC24_DL_TASK_MAX;
    header->legacyTaskCount = 0x20;
    header->taskCount = 8;

    result = NWC24FOpen(&file, DLFilePath, 1);
    if (result < NWC24_OK) {
        return result;
    }

    result = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (result >= NWC24_OK) {
        result = NWC24FWrite(header, 0x800, &file);
        if (result >= NWC24_OK) {
            result = NWC24_OK;
        }
    }

    if (result >= NWC24_OK) {
        for (taskId = 0; taskId < NWC24_DL_TASK_MAX; taskId++) {
            if (NWC24WorkP != NULL) {
                task = (DlTaskData*)NWC24WorkP->dlTask;
            } else {
                task = NULL;
            }

            memset(task, 0, sizeof(*task));
            task->type = 0xff;
            task->id = taskId;
            memset(&header->entries[taskId], 0, sizeof(header->entries[taskId]));

            if (NWC24WorkP != NULL) {
                header = (DlTaskListHeader*)NWC24WorkP->dlHead;
            } else {
                header = NULL;
            }
            if (header->maxTaskCount > NWC24_DL_TASK_MAX || taskId >= header->maxTaskCount) {
                result = NWC24_ERR_INVALID_VALUE;
                break;
            }

            result = NWC24FSeek(&file, 0x800 + taskId * 0x200, NWC24_SEEK_BEG);
            if (result < NWC24_OK) {
                break;
            }

            memcpy((DlTaskData*)NWC24WorkP->dlTask, task, sizeof(*task));
            result = NWC24FWrite((DlTaskData*)NWC24WorkP->dlTask, 0x200, &file);
            if (result < NWC24_OK) {
                break;
            }
        }
    }

    NWC24FClose(&file);
    return result;
}

NWC24Err NWC24iInitDlTaskList(BOOL force) {
    NWC24Err result;
    DlTaskListHeader* header;

    result = NWC24iOpenDlTaskList();
    if (result == NWC24_OK) {
        if (!force) {
            return result;
        }
    } else if (result == NWC24_ERR_VER_MISMATCH) {
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        if (header != NULL && header->version > 1) {
            return result;
        }
    }
    return NWC24iCreateDlTaskList();
}

NWC24Err NWC24iLoadDlHeader() {
    NWC24File file;
    NWC24File updateFile;
    DlTaskListHeader* header;
    NWC24Err result;
    NWC24Err closeResult;
    u32 fileLength = 0;

    result = NWC24_OK;
    closeResult = NWC24FOpen(&file, DLFilePath, NWC24_OPEN_READ);
    if (closeResult < NWC24_OK) {
        return closeResult;
    }

    closeResult = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (closeResult < NWC24_OK) {
        return closeResult;
    }

    closeResult = NWC24FRead(NWC24WorkP->dlHead, 0x800, &file);
    result = closeResult < NWC24_OK ? closeResult : NWC24_OK;
    if (result < NWC24_OK) {
        return result;
    }

    result = NWC24FGetLength(&file, &fileLength);
    if (result >= NWC24_OK) {
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        if (header->maxTaskCount == 0 && header->legacyTaskCount != 0) {
            header->maxTaskCount = header->legacyTaskCount;
            if (header->legacyTaskCount > 0x20) {
                header->legacyTaskCount = 0x20;
            }
            if (NWC24FOpen(&updateFile, DLFilePath, NWC24_OPEN_RW) >= NWC24_OK) {
                if (NWC24FSeek(&updateFile, 0, NWC24_SEEK_BEG) >= NWC24_OK) {
                    if (NWC24WorkP != NULL) {
                        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
                    } else {
                        header = NULL;
                    }
                    NWC24FWrite(header, 0x800, &updateFile);
                }
                NWC24FClose(&updateFile);
            }
        }

        if (header->maxTaskCount < 1 || header->taskCount < 1 ||
            header->maxTaskCount < header->taskCount) {
            result = NWC24_ERR_BROKEN;
        } else {
            result = NWC24_OK;
        }
    }

    closeResult = NWC24FClose(&file);
    if (result != NWC24_OK) {
        return result;
    }
    return closeResult;
}

NWC24Err StoreDlTask(NWC24DlTask* dlTask) {
    NWC24File file;
    DlTaskData* task;
    DlTaskListHeader* header;
    NWC24Err result;
    NWC24DlId taskId;

    task = (DlTaskData*)dlTask;
    result = NWC24FOpen(&file, DLFilePath, 4);
    if (result < NWC24_OK) {
        return result;
    }

    taskId = task->id;
    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    if (header->maxTaskCount > NWC24_DL_TASK_MAX || taskId >= header->maxTaskCount) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24FSeek(&file, 0x800 + taskId * 0x200, NWC24_SEEK_BEG);
    }

    if (result >= NWC24_OK) {
        memcpy(NWC24WorkP->dlTask, task, sizeof(*task));
        result = NWC24FWrite(NWC24WorkP->dlTask, sizeof(*task), &file);
    }

    if (result >= NWC24_OK) {
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        header->entries[taskId].flags = task->flags;
        header->entries[taskId].priority = task->priority;
        result = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
        if (result >= NWC24_OK) {
            result = NWC24FWrite(header, 0x800, &file);
        }
    }

    NWC24FClose(&file);
    return result;
}

NWC24Err AddTaskInternal(NWC24DlTask* dlTask, u16 taskCount, u16 maxTaskCount) {
    DlTaskData* task;
    DlTaskListHeader* header;
    NWC24Err result;
    u16 taskId;
    char* url;
    OSTime universalTime;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }

    if (dlTask == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    task = (DlTaskData*)dlTask;
    if (!NWC24IsMsgLibOpenedByTool()) {
        u32 taskAppId = task->appId;
        u32 appId = NWC24GetAppId();
        BOOL allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
        if (!allowed && (task->flags & 0x40)) {
            allowed = task->groupId == NWC24GetGroupId();
        }
        if (!allowed) {
            return NWC24_ERR_PROTECTED;
        }
    }

    taskId = task->id;
    if (taskId != 0xffff && taskId >= header->maxTaskCount) {
        return NWC24_ERR_INVALID_VALUE;
    }

    url = task->url;
    result = NWC24iCheckStringLength(url, 7, 0x100);
    if (result >= NWC24_OK && strncmp(url, "http://", 7) != 0 &&
        strncmp(url, "https://", 8) != 0) {
        result = NWC24_ERR_FORMAT;
    }
    if (result < NWC24_OK) {
        return result;
    }

retryExistingTask:
    taskId = task->id;
    if (taskId != 0xffff) {
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }

        result = NWC24_OK;
        if (dlTask == NULL) {
            result = NWC24_ERR_INVALID_VALUE;
        } else if (header == NULL) {
            result = NWC24_ERR_LIB_NOT_OPENED;
        } else {
            if (!NWC24IsMsgLibOpenedByTool()) {
                u32 taskAppId = task->appId;
                u32 appId = NWC24GetAppId();
                BOOL allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
                if (!allowed && (task->flags & 0x40)) {
                    allowed = task->groupId == NWC24GetGroupId();
                }
                if (!allowed) {
                    result = NWC24_ERR_PROTECTED;
                }
            }
            taskId = task->id;
            if (result == NWC24_OK && taskId != 0xffff && taskId >= header->maxTaskCount) {
                result = NWC24_ERR_INVALID_VALUE;
            }
        }
        if (result < NWC24_OK) {
            return result;
        }

        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        if (taskId >= header->maxTaskCount) {
            return NWC24_ERR_INVALID_VALUE;
        }

        result = NWC24iGetUniversalTime(&universalTime);
        if (result >= NWC24_OK) {
            if (NWC24WorkP != NULL) {
                header = (DlTaskListHeader*)NWC24WorkP->dlHead;
            } else {
                header = NULL;
            }
            result = NWC24_OK;
            if (dlTask == NULL) {
                result = NWC24_ERR_INVALID_VALUE;
            } else if (header == NULL) {
                result = NWC24_ERR_LIB_NOT_OPENED;
            } else {
                taskId = task->id;
                if (taskId == 0xffff) {
                    result = NWC24_ERR_FAILED;
                } else if (taskId >= header->maxTaskCount) {
                    result = NWC24_ERR_INVALID_VALUE;
                }
            }
            if (result >= NWC24_OK) {
                header->entries[taskId].nextTime = universalTime / 60;
            }
        }
        if (result < NWC24_OK) {
            return result;
        }

        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        result = NWC24_OK;
        if (dlTask == NULL) {
            result = NWC24_ERR_INVALID_VALUE;
        } else if (header == NULL) {
            result = NWC24_ERR_LIB_NOT_OPENED;
        } else {
            if (!NWC24IsMsgLibOpenedByTool()) {
                u32 taskAppId = task->appId;
                u32 appId = NWC24GetAppId();
                BOOL allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
                if (!allowed && (task->flags & 0x40)) {
                    allowed = task->groupId == NWC24GetGroupId();
                }
                if (!allowed) {
                    result = NWC24_ERR_PROTECTED;
                }
            }
            taskId = task->id;
            if (result == NWC24_OK && taskId != 0xffff && taskId >= header->maxTaskCount) {
                result = NWC24_ERR_INVALID_VALUE;
            }
        }

        if (result == NWC24_OK && task->id != 0xffff) {
            task->unknown_0x20 = 0;
            task->unknown_0x1a = 0;
        }

        if (task->retryEnabled == 1) {
            do {
                u8 retryCount;
                u32 retryMask;

                task->retryCount = (task->retryCount + 1) & 0x1f;
                if (NWC24WorkP != NULL) {
                    header = (DlTaskListHeader*)NWC24WorkP->dlHead;
                } else {
                    header = NULL;
                }
                if (dlTask == NULL) {
                    return NWC24_ERR_INVALID_VALUE;
                }
                if (header == NULL) {
                    return NWC24_ERR_LIB_NOT_OPENED;
                }
                if (!NWC24IsMsgLibOpenedByTool()) {
                    u32 taskAppId = task->appId;
                    u32 appId = NWC24GetAppId();
                    BOOL allowed = (taskAppId & 0xffffff00) == (appId & 0xffffff00);
                    if (!allowed && (task->flags & 0x40)) {
                        allowed = task->groupId == NWC24GetGroupId();
                    }
                    if (!allowed) {
                        return NWC24_ERR_PROTECTED;
                    }
                }
                taskId = task->id;
                if (taskId != 0xffff && taskId >= header->maxTaskCount) {
                    return NWC24_ERR_INVALID_VALUE;
                }
                if (task->retryEnabled == 0) {
                    return NWC24_ERR_INVALID_OPERATION;
                }
                retryCount = task->retryCount;
                retryMask = task->retryMask;
                if (retryMask == 0) {
                    return NWC24_ERR_FATAL;
                }
                if (retryCount > 0x1f) {
                    return NWC24_ERR_INVALID_VALUE;
                }
                result = NWC24_OK;
                if ((retryMask & (1 << retryCount)) == 0) {
                    result = NWC24_ERR_DISABLED;
                }
            } while (result == NWC24_ERR_DISABLED);
            if (result < NWC24_OK) {
                return result;
            }
        }
        return StoreDlTask(dlTask);
    }

    for (;;) {
        u16 currentTaskId;

        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        if (dlTask == NULL || header == NULL || taskCount > maxTaskCount ||
            taskCount >= header->maxTaskCount || maxTaskCount > header->maxTaskCount) {
            return NWC24_ERR_INVALID_VALUE;
        }

        currentTaskId = taskCount;
        while (currentTaskId < maxTaskCount) {
            if (NWC24WorkP != NULL) {
                header = (DlTaskListHeader*)NWC24WorkP->dlHead;
            } else {
                header = NULL;
            }
            if (header->entries[currentTaskId].flags == 0) {
                task->id = currentTaskId;
                goto retryExistingTask;
            }
            currentTaskId++;
        }

        result = NWC24PurgeOldestDlTask();
        if (result < NWC24_OK) {
            return result;
        }
        goto retryExistingTask;
    }
}

NWC24Err DeleteDlTask(NWC24DlTask* dlTask) {
    NWC24File file;
    DlTaskData* task;
    DlTaskListHeader* header;
    NWC24Err result;
    NWC24Err closeResult;
    NWC24DlId taskId;

    result = NWC24FOpen(&file, DLFilePath, 4);
    if (result < NWC24_OK) {
        return result;
    }

    taskId = ((DlTaskData*)dlTask)->id;
    task = (DlTaskData*)NWC24WorkP->dlTask;
    memset(task, 0, sizeof(*task));
    task->id = taskId;
    task->type = 0xff;
    memset(&((DlTaskListHeader*)NWC24WorkP->dlHead)->entries[taskId], 0,
           sizeof(((DlTaskListHeader*)NWC24WorkP->dlHead)->entries[taskId]));

    header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    if (header->maxTaskCount > NWC24_DL_TASK_MAX || taskId >= header->maxTaskCount) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24FSeek(&file, 0x800 + taskId * 0x200, NWC24_SEEK_BEG);
    }
    if (result >= NWC24_OK) {
        memcpy(NWC24WorkP->dlTask, task, sizeof(*task));
        result = NWC24FWrite(NWC24WorkP->dlTask, sizeof(*task), &file);
    }
    if (result >= NWC24_OK) {
        memset(&((DlTaskListHeader*)NWC24WorkP->dlHead)->entries[taskId], 0,
               sizeof(((DlTaskListHeader*)NWC24WorkP->dlHead)->entries[taskId]));
        result = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
        if (result >= NWC24_OK) {
            result = NWC24FWrite((DlTaskListHeader*)NWC24WorkP->dlHead, 0x800, &file);
        }
    }

    closeResult = NWC24FClose(&file);
    if (result != NWC24_OK) {
        return result;
    }
    return closeResult;
}

static s32 IterationPredicatorLastAccess(NWC24DlId taskId) {
    DlTaskListHeader* header;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    return header->entries[taskId].lastAccess;
}

static s32 IterationPredicatorNextTime(NWC24DlId taskId) {
    DlTaskListHeader* header;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    return header->entries[taskId].nextTime;
}

static s32 IterationPredicatorPriority(NWC24DlId taskId) {
    DlTaskListHeader* header;

    if (NWC24WorkP != NULL) {
        header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    } else {
        header = NULL;
    }
    return header->entries[taskId].priority;
}
