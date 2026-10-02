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
    u32 appId;
    u32 nextTime;
    u32 lastAccess;
    u8 priority;
    u8 reserved[3];
} DlTaskEntry;

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
    DlTaskEntry entries[NWC24_DL_TASK_MAX];
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
NWC24Err StoreDlTask(NWC24DlTask* dlTask) NO_INLINE;
NWC24Err AddTaskInternal(NWC24DlTask* dlTask, u16 taskCount, u16 maxTaskCount);
NWC24Err DeleteDlTask(NWC24DlTask* dlTask) NO_INLINE;
static s32 IterationPredicatorLastAccess(NWC24DlId taskId);
static s32 IterationPredicatorNextTime(NWC24DlId taskId);
static s32 IterationPredicatorPriority(NWC24DlId taskId);

static inline DlTaskListHeader* GetCachedDlHeader(void) {
    if (NWC24WorkP != NULL) {
        return (DlTaskListHeader*)NWC24WorkP->dlHead;
    }
    return NULL;
}

static inline BOOL IsDlTaskOwner(u32 appId) {
    return (appId & 0xffffff00) == (NWC24GetAppId() & 0xffffff00);
}

static inline BOOL IsDlTaskGroupWritable(u16 groupId, u32 flags) {
    return (flags & 0x40) && groupId == NWC24GetGroupId();
}

static inline NWC24Err ValidateDlTask(const NWC24DlTask* dlTask, BOOL write) {
    const DlTaskData* task = (const DlTaskData*)dlTask;
    DlTaskListHeader* header = GetCachedDlHeader();
    if (task == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (header == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }
    if (write && !NWC24IsMsgLibOpenedByTool() && !IsDlTaskOwner(task->appId)) {
        if (!IsDlTaskGroupWritable(task->groupId, task->flags)) {
            return NWC24_ERR_PROTECTED;
        }
    }
    if (task->id != 0xffff && task->id >= header->maxTaskCount) {
        return NWC24_ERR_INVALID_VALUE;
    }
    return NWC24_OK;
}

static inline NWC24Err SeekDlTaskEntry(u16 taskId, NWC24File* file) {
    DlTaskListHeader* header = GetCachedDlHeader();
    if (header->maxTaskCount > NWC24_DL_TASK_MAX || taskId >= header->maxTaskCount) {
        return NWC24_ERR_INVALID_VALUE;
    }
    return NWC24FSeek(file, 0x800 + taskId * 0x200, NWC24_SEEK_BEG);
}

static inline NWC24Err WriteDlTaskEntry(DlTaskData* task, NWC24File* file) {
    NWC24Err result = SeekDlTaskEntry(task->id, file);
    if (result < NWC24_OK) {
        return result;
    }
    memcpy(NWC24WorkP->dlTask, task, sizeof(*task));
    result = NWC24FWrite(NWC24WorkP->dlTask, sizeof(*task), file);
    if (result < NWC24_OK) {
        return result;
    }
    return NWC24_OK;
}

static inline NWC24Err WriteDlHeader(NWC24File* file) {
    NWC24Err result = NWC24FSeek(file, 0, NWC24_SEEK_BEG);
    if (result < NWC24_OK) {
        return result;
    }
    result = NWC24FWrite(GetCachedDlHeader(), 0x800, file);
    if (result < NWC24_OK) {
        return result;
    }
    return NWC24_OK;
}

static inline NWC24Err UpdateDlEntryHeader(DlTaskData* task) {
    u16 taskId = task->id;
    DlTaskListHeader* header = GetCachedDlHeader();
    DlTaskEntry* entry = &header->entries[taskId];
    entry->appId = task->appId;
    entry->priority = task->priority;
    return NWC24_OK;
}

static inline void InitDlEntryHeader(u16 taskId) {
    DlTaskListHeader* header = (DlTaskListHeader*)NWC24WorkP->dlHead;
    memset(&header->entries[taskId], 0, sizeof(header->entries[taskId]));
}

static inline NWC24Err ClearDlTaskEntry(u16 taskId, NWC24File* file) {
    DlTaskData* task = (DlTaskData*)NWC24WorkP->dlTask;
    memset(task, 0, sizeof(*task));
    task->type = 0xff;
    task->id = taskId;
    InitDlEntryHeader(taskId);
    return WriteDlTaskEntry(task, file);
}



static inline NWC24Err ReadDlTaskInline(NWC24DlTask* dlTask, NWC24DlId dlId) {
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
        if (header->entries[dlId].appId == 0) {
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

static inline NWC24Err RemoveDlTask(NWC24DlTask* dlTask) {
    NWC24Err result = ValidateDlTask(dlTask, FALSE);
    if (result != NWC24_OK) { return result; }
    result = DeleteDlTask(dlTask);
    if (result < NWC24_OK) { return result; }
    ((DlTaskData*)dlTask)->id = 0xffff;
    return result;
}

static inline NWC24Err GetMaxDlTaskCount(u16* count) {
    DlTaskListHeader* header = GetCachedDlHeader();
    if (header == NULL) { return NWC24_ERR_LIB_NOT_OPENED; }
    *count = header->maxTaskCount;
    return NWC24_OK;
}

NWC24Err NWC24InitDlTask(NWC24DlTask* dlTask, NWC24DLType dlType) {
    char homePath[64] = {0};
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

    if (dlType == NWC24_DLTYPE_OCTETSTREAM_V1 || dlType == NWC24_DLTYPE_OCTETSTREAM_V2) { useContentFile = TRUE; }
    else { useContentFile = FALSE; }
    if (useContentFile) {
        strcpy(task->fileName, "content.bin");
    }

    result = ValidateDlTask(dlTask, TRUE);
    return result >> 31;
}

NWC24Err NWC24SetDlId(NWC24DlTask* dlTask, NWC24DlId dlId) {
    NWC24Err result;
    DlTaskData* task;
    DlTaskListHeader* header;
    NWC24Work* work = NWC24WorkP;

    result = ValidateDlTask(dlTask, FALSE);
    if (result != NWC24_OK) {
        return result;
    }
    task = (DlTaskData*)dlTask;

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
    NWC24Err result;

    result = ValidateDlTask(dlTask, TRUE);
    if (result != NWC24_OK) {
        return result;
    }

    ((DlTaskData*)dlTask)->priority = dlPriority;
    return NWC24_OK;
}



static inline void ReadDlTaskIdentifier(const NWC24DlTask* dlTask, u16* identifier) {
    *identifier = ((const DlTaskData*)dlTask)->id;
}

static inline NWC24Err SetDlTaskNextTime(NWC24DlTask* dlTask, OSTime time) {
    NWC24Work* work = NWC24WorkP;
    DlTaskListHeader* header = work != NULL ? (DlTaskListHeader*)work->dlHead : NULL;
    DlTaskData* task = (DlTaskData*)dlTask;
    NWC24Err result;
    u16 taskId;
    if (task == NULL) { result = NWC24_ERR_INVALID_VALUE; }
    else if (header == NULL) { result = NWC24_ERR_LIB_NOT_OPENED; }
    else if (task->id != 0xffff && task->id >= header->maxTaskCount) { result = NWC24_ERR_INVALID_VALUE; }
    else { result = NWC24_OK; }
    if (result != NWC24_OK) { return result; }
    ReadDlTaskIdentifier(dlTask, &taskId);
    if (taskId == 0xffff) { return NWC24_ERR_FAILED; }
    time /= 60;
    header = work != NULL ? (DlTaskListHeader*)work->dlHead : NULL;
    header->entries[taskId].nextTime = time;
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

    result = ValidateDlTask(dlTask, TRUE);
    if (result != NWC24_OK) {
        return result;
    }
    task = (DlTaskData*)dlTask;

    task = (DlTaskData*)dlTask;
    if (!NWC24iLaxParameterCheck) {
        if (NWC24WorkP != NULL) {
            header = (DlTaskListHeader*)NWC24WorkP->dlHead;
        } else {
            header = NULL;
        }
        taskId = task->id;
        if (taskId >= header->taskCount && !(task->flags & 0x40000000) && (dlInterval < 0x00b4 || dlInterval > 0x2760)) {
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
                    ReadDlTaskIdentifier(dlTask, &taskId);
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

static inline NWC24Err CheckDlUrlString(const char* url) {
    NWC24Err result = NWC24iCheckStringLength(url, 7, 0x100);
    if (result < NWC24_OK) { return result; }
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) { return NWC24_ERR_FORMAT; }
    return NWC24_OK;
}

NWC24Err NWC24SetDlUrl(NWC24DlTask* dlTask, const char* dlUrl) {
    DlTaskData* task;
    NWC24Err result;

    result = ValidateDlTask(dlTask, TRUE);
    if (result != NWC24_OK) {
        return result;
    }
    task = (DlTaskData*)dlTask;
    result = CheckDlUrlString(dlUrl);
    if (result < NWC24_OK) { return result; }

    task = (DlTaskData*)dlTask;
    if (!NWC24iLaxParameterCheck && (task->flags & 0x4) && strncmp(dlUrl, "http://", 7) == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    NWC24iStrLCpy(task->url, dlUrl, sizeof(task->url));
    return NWC24_OK;
}

NWC24Err NWC24SetDlFlags(NWC24DlTask* dlTask, u32 dlFlags) {
    DlTaskData* task;
    NWC24Err result;

    result = ValidateDlTask(dlTask, TRUE);
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
        case NWC24_DLTYPE_MULTIPART_V2:
        case NWC24_DLTYPE_OCTETSTREAM_V2:
            break;
        default:
            break;
    }
    task->flags = dlFlags;
    return NWC24_OK;
}

NWC24Err NWC24GetDlAppId(const NWC24DlTask* dlTask, u32* dlAppId) {
    NWC24Err result;

    result = ValidateDlTask(dlTask, FALSE);
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
    DlTaskListHeader* entriesHeader;
    NWC24Work* work;
    u16 taskId;
    u16 maxTaskCount;
    DlTaskListHeader* header;
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

    entriesHeader = (DlTaskListHeader*)work->dlHead;
    while (taskId < (work == NULL ? (DlTaskListHeader*)NULL : entriesHeader)->maxTaskCount) {
        header = work != NULL ? entriesHeader : NULL;
        if (taskId >= header->maxTaskCount || taskId == 0xffff) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            header = work != NULL ? entriesHeader : NULL;
            result = NWC24_OK;
            if (header->entries[taskId].appId == 0) { result = NWC24_ERR_NOT_FOUND; }
        }
        if (result >= NWC24_OK) {
            *dlIterateId = taskId;
            return NWC24_OK;
        }
        taskId++;
    }
    return NWC24_ERR_DONE;
}

NWC24Err NWC24IterateDlTaskEx(NWC24DlIterateWork* dlIterateWork, NWC24DlId* dlIterateId) {
    DlTaskIterationState* state = (DlTaskIterationState*)dlIterateWork;
    NWC24DlId taskId;
    s32 value;
    BOOL descending;
    BOOL passesSelected;
    BOOL bestCandidate;
    BOOL found = FALSE;
    s32 (*getValue)(NWC24DlId);
    NWC24Err result;

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
            if (value == state->comparisonValue && (s32)state->comparisonId < (s32)taskId) {
                *dlIterateId = taskId;
                state->comparisonValue = value;
                state->comparisonId = taskId;
                state->selectedValue = value;
                return NWC24_OK;
            }
            result = NWC24IterateDlTask(&taskId, FALSE);
        }
    } else {
        state->initialized = 0;
    }

    if (!(state->sortMode & 0x80000000)) { state->comparisonValue = 0x7fffffff; }
    else { state->comparisonValue = (s32)0x80000001; }
    result = NWC24IterateDlTask(&taskId, TRUE);
    while (result >= NWC24_OK) {
        value = getValue(taskId);
        {
        s32 selectedValue = state->selectedValue;
        if (descending) {
            passesSelected = selectedValue > value;
        } else {
            passesSelected = selectedValue < value;
        }
        if (passesSelected) {
            s32 comparisonValue = state->comparisonValue;
            if (descending) {
                bestCandidate = comparisonValue < value;
            } else {
                bestCandidate = comparisonValue > value;
            }
            if (bestCandidate) {
                *dlIterateId = taskId;
                state->comparisonValue = value;
                state->comparisonId = taskId;
                found = TRUE;
            }
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

static inline NWC24Err SetDlTaskAccessTime(NWC24DlTask* dlTask, OSTime time) {
    NWC24Work* work = NWC24WorkP;
    DlTaskListHeader* header = work != NULL ? (DlTaskListHeader*)work->dlHead : NULL;
    DlTaskData* task = (DlTaskData*)dlTask;
    NWC24Err result;
    u16 taskId;
    if (task == NULL) { result = NWC24_ERR_INVALID_VALUE; }
    else if (header == NULL) { result = NWC24_ERR_LIB_NOT_OPENED; }
    else if (task->id != 0xffff && task->id >= header->maxTaskCount) { result = NWC24_ERR_INVALID_VALUE; }
    else { result = NWC24_OK; }
    if (result != NWC24_OK) { return result; }
    taskId = task->id;
    if (taskId == 0xffff) { return NWC24_ERR_FAILED; }
    time /= 60;
    header = work != NULL ? (DlTaskListHeader*)work->dlHead : NULL;
    header->entries[taskId].lastAccess = time;
    return NWC24_OK;
}

static inline NWC24Err CheckDlTaskRetry(NWC24DlTask* dlTask, u8 retryCount) {
    DlTaskData* task = (DlTaskData*)dlTask;
    NWC24Err result = ValidateDlTask(dlTask, FALSE);
    u32 retryMask;
    if (result != NWC24_OK) { return result; }
    if (task->retryEnabled == 0) { return NWC24_ERR_INVALID_OPERATION; }
    retryMask = task->retryMask;
    if (retryMask == 0) { return NWC24_ERR_FATAL; }
    if (retryCount > 31) { return NWC24_ERR_INVALID_VALUE; }
    if ((retryMask & (1 << retryCount)) == 0) { return NWC24_ERR_DISABLED; }
    return NWC24_OK;
}
static inline NWC24Err UpdateDlTaskAccessTime(NWC24DlTask* dlTask) {
    OSTime universalTime;
    NWC24Err result = NWC24iGetUniversalTime(&universalTime);
    if (result >= NWC24_OK) {
        result = SetDlTaskAccessTime(dlTask, universalTime);
        if (result < NWC24_OK) { return result; }
    }
    return result;
}

NWC24Err NWC24UpdateDlTask(NWC24DlTask* dlTask) {
    DlTaskData* task = (DlTaskData*)dlTask;
    DlTaskListHeader* header;
    u16 taskId;
    OSTime universalTime;
    NWC24Err result;

    result = ValidateDlTask(dlTask, TRUE);
    if (result != NWC24_OK) { return result; }
    taskId = task->id;
    if (taskId == 0xffff || taskId >= GetCachedDlHeader()->maxTaskCount) { return NWC24_ERR_INVALID_VALUE; }
    result = UpdateDlTaskAccessTime(dlTask);
    if (result < NWC24_OK) { return result; }
    result = ValidateDlTask(dlTask, TRUE);
    if (result == NWC24_OK) {
        task->unknown_0x20 = 0;
        task->unknown_0x1a = 0;
    }
    if (task->retryEnabled == 1) {
        while ((result = CheckDlTaskRetry(dlTask, task->retryCount)) == NWC24_ERR_DISABLED) {
            task->retryCount = (task->retryCount + 1) & 0x1f;
        }
        if (result < NWC24_OK) { return result; }
    }
    return StoreDlTask(dlTask);
}
NWC24Err NWC24DeleteDlTask(NWC24DlTask* dlTask) {
    NWC24Err result;
    if (NWC24GetAppId() != 0x48414541) {
        result = ValidateDlTask(dlTask, TRUE);
        if (result != NWC24_OK) { return result; }
    }
    return RemoveDlTask(dlTask);
}


static inline NWC24Err CheckDlTaskListHeader(DlTaskListHeader* header) {
    if (header->maxTaskCount < 1 || header->taskCount < 1 || header->maxTaskCount < header->taskCount) { return NWC24_ERR_BROKEN; }
    return NWC24_OK;
}
NWC24Err NWC24AddDlTask(NWC24DlTask* dlTask) {
    DlTaskListHeader* header = GetCachedDlHeader();
    NWC24File file;
    NWC24Err result;
    OSTime universalTime;


    if (header->maxTaskCount == 0 && header->legacyTaskCount != 0) {
        header->maxTaskCount = header->legacyTaskCount;
        if (header->legacyTaskCount > 32) { header->legacyTaskCount = 32; }
        result = NWC24FOpen(&file, DLFilePath, 4);
        if (result >= NWC24_OK) {
            result = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
            if (result >= NWC24_OK) { NWC24FWrite(GetCachedDlHeader(), 0x800, &file); }
            NWC24FClose(&file);
        }
    }
    result = CheckDlTaskListHeader(header);
    if (result < NWC24_OK) { return result; }
    result = AddTaskInternal(dlTask, GetCachedDlHeader()->taskCount, GetCachedDlHeader()->maxTaskCount);
    if (result >= NWC24_OK) {
        universalTime = 0;
        result = NWC24iGetUniversalTime(&universalTime);
        if (result < NWC24_OK) { return result; }
        {
            s32 intervalSeconds;
            s64 nextTime;
            intervalSeconds = ((DlTaskData*)dlTask)->interval * 60;
            nextTime = universalTime + intervalSeconds;
            return SetDlTaskNextTime(dlTask, nextTime);
        }
    }
    return result;
}


NWC24Err NWC24GetDlTask(NWC24DlTask* dlTask, NWC24DlId dlId) {
    DlTaskListHeader* header;
    NWC24File file;
    DlTaskData* task = (DlTaskData*)dlTask;
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
        if (header->entries[dlId].appId == 0) {
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
        operationResult = NWC24FRead(task, 0x200, &file);
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

static inline NWC24Err InitDlIteration(DlTaskIterationState* state, u32 sortMode) {
    memset(state, 0, sizeof(*state));
    state->comparisonValue = 0x7fffffff;
    state->selectedValue = (s32)0x80000001;
    state->sortMode = sortMode;
    state->comparisonId = 0xffffffff;
    state->initialized = 1;
    state->valid = 1;
    return NWC24_OK;
}

NWC24Err NWC24PurgeOldestDlTask() {
    DlTaskIterationState state;
    NWC24File file;
    NWC24DlTask task;
    DlTaskListHeader* header;
    NWC24DlId taskId;
    NWC24DlId selectedId;
    NWC24DlTask* taskPointer;
    NWC24Err result;
    NWC24Err closeResult;

    result = InitDlIteration(&state, 0);
    if (result < NWC24_OK) { return NWC24_OK; }

    while ((result = NWC24IterateDlTaskEx((NWC24DlIterateWork*)&state, &taskId)) == NWC24_OK) {
        header = GetCachedDlHeader();
        if (taskId >= header->taskCount) { break; }
    }

    if (result >= NWC24_OK) {
        taskPointer = &task;
        selectedId = taskId;
        result = ReadDlTaskInline(taskPointer, selectedId);
        if (result < NWC24_OK) { return result; }
        taskPointer = &task;
        result = RemoveDlTask(taskPointer);
        if (result < NWC24_OK) { return result; }
    } else if (result == NWC24_ERR_DONE) {
        result = NWC24_ERR_FAILED;
    }
    return result;
}
NWC24Err NWC24ManageDlTaskListForMenu() {
    NWC24DlTask task;
    NWC24DlTask* taskPointer;
    u16 maxTaskCount;
    NWC24Err result = GetMaxDlTaskCount(&maxTaskCount);
    if (result < NWC24_OK) { return result; }
    if (maxTaskCount >= NWC24_DL_TASK_MAX) { return NWC24_OK; }
    result = NWC24ExtendDlTaskList(NWC24_DL_TASK_MAX);
    if (result < NWC24_OK) { return result; }
    taskPointer = &task;
    result = ReadDlTaskInline(taskPointer, 2);
    if (result == NWC24_ERR_NOT_FOUND) { return NWC24_OK; }
    if (result < NWC24_OK) { return result; }
    taskPointer = &task;
    result = RemoveDlTask(taskPointer);
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
        result = ClearDlTaskEntry(taskId, &file);
        if (result < NWC24_OK) {
            goto closeList;
        }
    }
    result = WriteDlHeader(&file);
closeList:
    closeResult = NWC24FClose(&file);
    closeResult = result != NWC24_OK ? result : closeResult;
    result = NWC24iLoadDlHeader();
    if (closeResult != NWC24_OK) {
        result = closeResult;
    }
    return result;
}

NWC24Err NWC24iCheckDlHeaderConsistency(DlTaskListHeader* header, BOOL repair) {
    NWC24DlTask task;
    DlTaskData* taskData = (DlTaskData*)&task;
    NWC24DlTask* taskPointer = &task;
    NWC24DlId taskId;
    NWC24Err result;
    DlTaskListHeader* currentHeader;
    DlTaskListHeader* listHeader = header;
    BOOL shouldRepair = repair;

    for (taskId = 0; taskId < listHeader->maxTaskCount; taskId++) {
        currentHeader = GetCachedDlHeader();
        if (taskId >= currentHeader->maxTaskCount || taskId == 0xffff) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            currentHeader = GetCachedDlHeader();
            result = NWC24_OK;
            if (currentHeader->entries[taskId].appId == 0) { result = NWC24_ERR_NOT_FOUND; }
        }
        if (result != NWC24_OK || !shouldRepair) { continue; }
        result = ReadDlTaskInline(taskPointer, taskId);
        if (result < NWC24_OK) {
            if (ValidateDlTask(taskPointer, FALSE) == NWC24_OK) {
                result = DeleteDlTask(taskPointer);
                if (result >= NWC24_OK) { taskData->id = 0xffff; }
            }
        } else {
            currentHeader = GetCachedDlHeader();
            if (taskId >= currentHeader->taskCount && (s16)taskData->subTaskCount == 0) {
                if (ValidateDlTask(taskPointer, FALSE) == NWC24_OK) {
                    result = DeleteDlTask(taskPointer);
                    if (result >= NWC24_OK) { taskData->id = 0xffff; }
                }
            }
        }
    }
    return NWC24_OK;
}


NWC24Err NWC24iCreateDlTaskList() {
    u16 taskId;
    DlTaskListHeader* header = GetCachedDlHeader();
    NWC24Err result;
    NWC24File file;


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

    result = WriteDlHeader(&file);
    if (result >= NWC24_OK) {
        for (taskId = 0; taskId < NWC24_DL_TASK_MAX; taskId++) {
            result = ClearDlTaskEntry(taskId, &file);
            if (result < NWC24_OK) {
                break;
            }
        }
    }
    {
        NWC24Err closeResult = NWC24FClose(&file);
        if (result != NWC24_OK) {
            return result;
        }
        return closeResult;
    }
}

#pragma dont_inline on
NWC24Err NWC24iInitDlTaskList(BOOL force) {
    NWC24Err result;
    DlTaskListHeader* header;

    result = NWC24iOpenDlTaskList();
    if (result == NWC24_OK && !force) {
        return result;
    }
    if (result == NWC24_ERR_VER_MISMATCH) {
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
#pragma dont_inline reset

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
        result = closeResult;
    } else {
        closeResult = NWC24FRead(NWC24WorkP->dlHead, 0x800, &file);
        result = closeResult < NWC24_OK ? closeResult : NWC24_OK;
    }
    if (result < NWC24_OK) { return result; }

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
                    DlTaskListHeader* writeHeader;
                    if (NWC24WorkP != NULL) {
                        writeHeader = (DlTaskListHeader*)NWC24WorkP->dlHead;
                    } else {
                        writeHeader = NULL;
                    }
                    NWC24FWrite(writeHeader, 0x800, &updateFile);
                }
                NWC24FClose(&updateFile);
            }
        }

        if (header->maxTaskCount < 1 || header->taskCount < 1 || header->maxTaskCount < header->taskCount) {
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
    NWC24Err result;
    NWC24Err closeResult;
    result = NWC24FOpen(&file, DLFilePath, NWC24_OPEN_RW);
    if (result < NWC24_OK) {
        return result;
    }
    result = WriteDlTaskEntry((DlTaskData*)dlTask, &file);
    if (result >= NWC24_OK) {
        result = UpdateDlEntryHeader((DlTaskData*)dlTask);
        if (result >= NWC24_OK) {
            result = WriteDlHeader(&file);
        }
    }
    closeResult = NWC24FClose(&file);
    if (result != NWC24_OK) {
        return result;
    }
    return closeResult;
}

static inline NWC24Err ValidateDlTaskUrl(NWC24DlTask* dlTask) {
    DlTaskData* task = (DlTaskData*)dlTask;
    DlTaskListHeader* header = GetCachedDlHeader();
    NWC24Err result;
    if (task->id >= header->maxTaskCount && task->id != 0xffff) { return NWC24_ERR_INVALID_VALUE; }
    {
        const char* url = task->url;
        result = NWC24iCheckStringLength(url, 7, 0x100);
        if (result >= NWC24_OK) {
            if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) { result = NWC24_ERR_FORMAT; }
            else { result = NWC24_OK; }
        }
        if (result < NWC24_OK) { return result; }
        return NWC24_OK;
    }
}

static inline NWC24Err FindFreeDlTask(NWC24DlTask* dlTask, u16 taskCount, u16 maxTaskCount) {
    DlTaskListHeader* header = GetCachedDlHeader();
    NWC24DlId taskId;
    if (dlTask == NULL || taskCount > maxTaskCount || taskCount >= header->maxTaskCount || maxTaskCount > header->maxTaskCount) {
        return NWC24_ERR_INVALID_VALUE;
    }
    for (taskId = taskCount; taskId < maxTaskCount; taskId++) {
        header = GetCachedDlHeader();
        if (header->entries[taskId].appId == 0) {
            ((DlTaskData*)dlTask)->id = taskId;
            return NWC24_OK;
        }
    }
    return NWC24_ERR_FULL;
}

static inline NWC24Err UpdateDlTaskInline(NWC24DlTask* dlTask) {
    DlTaskData* task = (DlTaskData*)dlTask;
    DlTaskListHeader* header;
    u16 taskId;
    OSTime universalTime;
    NWC24Err result;

    result = ValidateDlTask(dlTask, TRUE);
    if (result != NWC24_OK) { return result; }
    taskId = task->id;
    if (taskId == 0xffff || taskId >= GetCachedDlHeader()->maxTaskCount) { return NWC24_ERR_INVALID_VALUE; }
    result = UpdateDlTaskAccessTime(dlTask);
    if (result < NWC24_OK) { return result; }
    result = ValidateDlTask(dlTask, TRUE);
    if (result == NWC24_OK) {
        task->unknown_0x20 = 0;
        task->unknown_0x1a = 0;
    }
    if (task->retryEnabled == 1) {
        while ((result = CheckDlTaskRetry(dlTask, task->retryCount)) == NWC24_ERR_DISABLED) {
            task->retryCount = (task->retryCount + 1) & 0x1f;
        }
        if (result < NWC24_OK) { return result; }
    }
    return StoreDlTask(dlTask);
}
NWC24Err AddTaskInternal(NWC24DlTask* dlTask, u16 taskCount, u16 maxTaskCount) {
    DlTaskData* task = (DlTaskData*)dlTask;
    NWC24Err result;
    result = ValidateDlTask(dlTask, TRUE);
    if (result != NWC24_OK) { return result; }
    result = ValidateDlTaskUrl(dlTask);
    if (result < NWC24_OK) { return result; }
    for (;;) {
        if (task->id != 0xffff) { return UpdateDlTaskInline(dlTask); }
        result = FindFreeDlTask(dlTask, taskCount, maxTaskCount);
        if (result == NWC24_ERR_FULL) {
            result = NWC24PurgeOldestDlTask();
            if (result < NWC24_OK) { return result; }
        } else if (result < NWC24_OK) { return result; }
    }
}


NWC24Err DeleteDlTask(NWC24DlTask* dlTask) {
    NWC24File file;
    NWC24Err result;
    NWC24Err closeResult;

    result = NWC24FOpen(&file, DLFilePath, 4);
    if (result < NWC24_OK) {
        return result;
    }

    result = ClearDlTaskEntry(((DlTaskData*)dlTask)->id, &file);
    if (result >= NWC24_OK) {
        InitDlEntryHeader(((DlTaskData*)dlTask)->id);
        result = WriteDlHeader(&file);
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
