#include <private/nwc24.h>

#include <private/nwc24/NWC24Download.h>
#include <private/nwc24/NWC24File.h>
#include <private/nwc24/NWC24Time.h>
#include <private/nwc24/NWC24Utils.h>

#include <revolution/nwc24.h>
#include <revolution/nwc24/NWC24Config.h>
#include <revolution/nwc24/NWC24Manage.h>

#include <revolution/nand.h>
#include <revolution/verdefs.h>

#include <string.h>
#include <stdlib.h>

SDKDefineVersion(NWC24, "Dec 12 2008", "03:06:06");

#define NWC24_DL_HEADER_MAGIC 0x5763446C
#define NWC24_DL_HEADER_VERSION 1
#define NWC24_DL_HEADER_SIZE 0x800
#define NWC24_DL_TASK_SIZE 0x200
#define NWC24_DL_RECORD_SIZE 0x10
#define NWC24_DL_RECORD_BASE 0x80
#define NWC24_DL_MENU_RESERVED 8
#define NWC24_DL_RECORD_MAX 0x20
#define NWC24_DL_APPID_KD 0x48414541

typedef u32 (*NWC24DlIterationPredicator)(NWC24DlId id);

static char* DLFilePath = "/shared2/wc24/nwc24dl.bin";

static u32 NWC24iLaxParameterCheck;

static inline NWC24DlHeader* GetDlTaskListHead() {
    return NWC24WorkP != NULL ? (NWC24DlHeader*)NWC24WorkP->dlHead : NULL;
}

static inline NWC24DlTaskEx* GetDlTaskWork() {
    return (NWC24DlTaskEx*)NWC24WorkP->dlTask;
}

static u32 IterationPredicatorLastAccess(NWC24DlId id);
static u32 IterationPredicatorNextTime(NWC24DlId id);
static u32 IterationPredicatorPriority(NWC24DlId id);

static NWC24Err StoreDlTask(NWC24DlTask* dlTask);
static NWC24Err AddTaskInternal(NWC24DlTask* dlTask, u16 first, u16 last);
static NWC24Err DeleteDlTask(NWC24DlTask* dlTask);

NWC24Err NWC24InitDlTask(NWC24DlTask* dlTask, NWC24DLType dlType) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    u32 userIdLow;
    u32 userIdHigh;
    char homeDir[0x40] = {0};

    NANDGetHomeDir(homeDir);
    homeDir[0xF] = 0;
    userIdLow = strtoul(homeDir + 7, NULL, 16);
    homeDir[0x18] = 0;
    userIdHigh = strtoul(homeDir + 0x10, NULL, 16);

    if (GetDlTaskListHead() == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    if (task == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (dlType >= NWC24_DLTYPE_OCTETSTREAM_V2 + 1) {
        return NWC24_ERR_INVALID_VALUE;
    }

    memset(task, 0, sizeof(NWC24DlTaskEx));
    task->dlType = dlType;
    task->priority = 0x7F;
    task->appId = NWC24GetAppId();
    task->groupId = NWC24GetGroupId();
    task->userIdLow = userIdLow;
    task->userIdHigh = userIdHigh;
    task->id = 0xFFFF;
    task->numSubTasks = 1;
    task->interval = 0xB40;
    task->subInterval = 0x5A0;

    {
        BOOL hasFileName;
        if (dlType == NWC24_DLTYPE_OCTETSTREAM_V1 || dlType == NWC24_DLTYPE_OCTETSTREAM_V2) {
            hasFileName = TRUE;
        } else {
            hasFileName = FALSE;
        }

        if (hasFileName) {
            strcpy(task->fileName, "content.bin");
        }
    }

    {
        NWC24DlHeader* dlHead = GetDlTaskListHead();
        NWC24Err result;

        if (task == NULL) {
            result = NWC24_ERR_INVALID_VALUE;
        } else if (dlHead == NULL) {
            result = NWC24_ERR_LIB_NOT_OPENED;
        } else {
            if (NWC24IsMsgLibOpenedByTool() == FALSE) {
                u32 appId = task->appId;
                BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
                if (eq == FALSE) {
                    BOOL owned = FALSE;
                    u16 groupId = task->groupId;
                    if ((task->flags & 0x40) != 0) {
                        if (groupId == (u16)NWC24GetGroupId()) {
                            owned = TRUE;
                        }
                    }

                    if (owned == FALSE) {
                        result = NWC24_ERR_PROTECTED;
                        goto done;
                    }
                }
            }

            if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
                result = NWC24_ERR_INVALID_VALUE;
            } else {
                result = NWC24_OK;
            }
        }

    done:
        return result >> 31;
    }
}

NWC24Err NWC24IterateDlTask(NWC24DlId* dlIterateId, BOOL begin) {
    NWC24DlHeader* dlHead;
    u32 id;
    NWC24Err result;

    if (GetDlTaskListHead() == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    if (dlIterateId == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    if (begin != FALSE) {
        *dlIterateId = 0;
    } else {
        *dlIterateId = *dlIterateId + 1;
    }

    dlHead = GetDlTaskListHead();
    id = *dlIterateId;
    if (id >= dlHead->numTasks) {
        return NWC24_ERR_DONE;
    }

    while ((u16)id < GetDlTaskListHead()->numTasks) {
        dlHead = GetDlTaskListHead();
        if ((u16)id >= dlHead->numTasks || (u16)id == 0xFFFF) {
            result = NWC24_ERR_INVALID_VALUE;
        } else if (GetDlTaskListHead()->infos[(u16)id].used == 0) {
            result = NWC24_ERR_NOT_FOUND;
        } else {
            result = NWC24_OK;
        }

        if (result >= NWC24_OK) {
            *dlIterateId = id;
            return NWC24_OK;
        }

        id = id + 1;
    }

    return NWC24_ERR_DONE;
}

NWC24Err NWC24IterateDlTaskEx(NWC24DlIterateWork* dlIterateWork, NWC24DlId* dlIterateId) {
    NWC24DlIterationPredicator predicator;
    int descending;
    NWC24DlId id;
    int found = 0;
    NWC24Err result;
    int type;

    if (dlIterateWork->unk_0x14 == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    type = (u16)dlIterateWork->unk_0x00;
    descending = (u32)dlIterateWork->unk_0x00 >> 31;

    switch (type) {
    case 0:
        predicator = IterationPredicatorLastAccess;
        break;
    case 1:
        predicator = IterationPredicatorNextTime;
        break;
    case 2:
        predicator = IterationPredicatorPriority;
        break;
    default:
        return NWC24_ERR_INVALID_VALUE;
    }

    if (dlIterateWork->unk_0x10 == 0) {
        result = NWC24IterateDlTask(&id, TRUE);
        while (result >= NWC24_OK) {
            s32 value = predicator(id);
            if (value == dlIterateWork->unk_0x04) {
                if (dlIterateWork->unk_0x0C < id) {
                    *dlIterateId = id;
                    dlIterateWork->unk_0x04 = value;
                    dlIterateWork->unk_0x08 = value;
                    dlIterateWork->unk_0x0C = id;
                    return NWC24_OK;
                }
            }
            result = NWC24IterateDlTask(&id, FALSE);
        }
    } else {
        dlIterateWork->unk_0x10 = 0;
    }

    if ((dlIterateWork->unk_0x00 & 0x80000000) == 0) {
        dlIterateWork->unk_0x04 = 0x7FFFFFFF;
    } else {
        dlIterateWork->unk_0x04 = 0x80000001;
    }

    result = NWC24IterateDlTask(&id, TRUE);
    while (result >= NWC24_OK) {
        s32 value = predicator(id);
        int better;

        s32 bound = dlIterateWork->unk_0x08;
        better = descending ? value > bound : value < bound;

        if (better) {
            bound = dlIterateWork->unk_0x04;
            better = descending ? value > bound : value < bound;

            if (better) {
                *dlIterateId = id;
                dlIterateWork->unk_0x04 = value;
                dlIterateWork->unk_0x0C = id;
                found = 1;
            }
        }

        result = NWC24IterateDlTask(&id, FALSE);
    }

    if (found) {
        dlIterateWork->unk_0x08 = dlIterateWork->unk_0x04;
        return NWC24_OK;
    }

    dlIterateWork->unk_0x14 = 0;
    return NWC24_ERR_DONE;
}

NWC24Err NWC24ManageDlTaskListForMenu() {
    NWC24DlHeader* dlHead;
    NWC24Err result;
    NWC24DlTaskEx task;
    NWC24File file;
    NWC24Err res2;
    u16 numTasks;

    dlHead = GetDlTaskListHead();
    if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
        goto check;
    }
    numTasks = dlHead->numTasks;
    result = NWC24_OK;

check:
    if (result < NWC24_OK) {
        return result;
    }

    if (numTasks >= NWC24_DL_TASK_MAX) {
        return NWC24_OK;
    }

    result = NWC24ExtendDlTaskList(NWC24_DL_TASK_MAX);
    if (result < NWC24_OK) {
        return result;
    }

    if (GetDlTaskListHead() == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
        goto check_hidden;
    }
    if (GetDlTaskListHead()->numTasks <= 2) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (GetDlTaskListHead()->infos[2].used == 0) {
        result = NWC24_ERR_NOT_FOUND;
    } else {
        result = NWC24_OK;
    }
    if (result < NWC24_OK) {
        goto check_hidden;
    }

    result = NWC24FOpen(&file, DLFilePath, 0xA);
    if (result < NWC24_OK) {
        goto check_hidden;
    }

    numTasks = GetDlTaskListHead()->numTasks;
    if (numTasks > NWC24_DL_TASK_MAX || numTasks <= 2) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24FSeek(&file, 0xC00, NWC24_SEEK_BEG);
    }

    if (result < NWC24_OK) {
        res2 = result;
        goto close;
    }
    result = NWC24FRead(&task, NWC24_DL_TASK_SIZE, &file);
    res2 = result < NWC24_OK ? result : NWC24_OK;
close:
    NWC24FClose(&file);
    if (res2 != NWC24_OK) {
        result = res2;
    }

check_hidden:
    if (result == NWC24_ERR_NOT_FOUND) {
        return NWC24_OK;
    }

    if (result < NWC24_OK) {
        return result;
    }

    {
        NWC24Err res;

        dlHead = GetDlTaskListHead();
        if (&task == NULL) {
            res = NWC24_ERR_INVALID_VALUE;
        } else if (dlHead == NULL) {
            res = NWC24_ERR_LIB_NOT_OPENED;
        } else if (task.id != 0xFFFF && task.id >= dlHead->numTasks) {
            res = NWC24_ERR_INVALID_VALUE;
        } else {
            res = NWC24_OK;
        }

        if (res != NWC24_OK) {
            return res;
        }

        res = DeleteDlTask((NWC24DlTask*)&task);
        res2 = res;
        if (res >= NWC24_OK) {
            task.id = 0xFFFF;
        }
        return res2;
    }
}

NWC24Err NWC24UpdateDlTask(NWC24DlTask* dlTask) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = GetDlTaskListHead();
    NWC24Err result;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        if (NWC24IsMsgLibOpenedByTool() == FALSE) {
            u32 appId = task->appId;
            BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
            if (eq == FALSE) {
                BOOL owned = FALSE;
                u16 groupId = task->groupId;
                if ((task->flags & 0x40) != 0) {
                if (groupId == (u16)NWC24GetGroupId()) {
                    owned = TRUE;
                    }
                }

                if (owned == FALSE) {
                    result = NWC24_ERR_PROTECTED;
                    goto check;
                }
            }
        }

        if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }

check:
    if (result != NWC24_OK) {
        return result;
    }

    if (task->id == 0xFFFF || task->id >= GetDlTaskListHead()->numTasks) {
        return NWC24_ERR_INVALID_VALUE;
    }

    {
        OSTime time;
        NWC24Err res;
        NWC24Err res2;
        NWC24DlHeader* dlHead2;

        res = NWC24iGetUniversalTime(&time);
        if (res < NWC24_OK) {
            res2 = res;
        } else {
            dlHead2 = GetDlTaskListHead();
            if (task == NULL) {
                res2 = NWC24_ERR_INVALID_VALUE;
            } else if (dlHead2 == NULL) {
                res2 = NWC24_ERR_LIB_NOT_OPENED;
            } else if (task->id != 0xFFFF && task->id >= dlHead2->numTasks) {
                res2 = NWC24_ERR_INVALID_VALUE;
            } else {
                res2 = NWC24_OK;
            }

            if (res2 != NWC24_OK) {
                goto time_merge;
            }
            if (task->id == 0xFFFF) {
                res2 = NWC24_ERR_FAILED;
            } else {
                GetDlTaskListHead()->infos[task->id].lastAccess = (u32)(time / 0x3C);
                res2 = NWC24_OK;
            }

time_merge:
            res = res2;
            if (res2 >= NWC24_OK) {
                res2 = res;
            }
        }

        if (res2 < NWC24_OK) {
            return res2;
        }
    }

    {
        NWC24Err res;

        dlHead = GetDlTaskListHead();
        if (task == NULL) {
            res = NWC24_ERR_INVALID_VALUE;
        } else if (dlHead == NULL) {
            res = NWC24_ERR_LIB_NOT_OPENED;
        } else {
            if (NWC24IsMsgLibOpenedByTool() == FALSE) {
                u32 appId = task->appId;
                BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
                if (eq == FALSE) {
                    BOOL owned = FALSE;
                    u16 groupId = task->groupId;
                    if ((task->flags & 0x40) != 0) {
                    if (groupId == (u16)NWC24GetGroupId()) {
                        owned = TRUE;
                        }
                    }

                    if (owned == FALSE) {
                        res = NWC24_ERR_PROTECTED;
                        goto checked;
                    }
                }
            }

            if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
                res = NWC24_ERR_INVALID_VALUE;
            } else {
                res = NWC24_OK;
            }
        }

    checked:
        if (res == NWC24_OK) {
            task->unk_0x20 = 0;
            task->processedSubTasks = 0;
        }
    }

    if (task->stType == NWC24_DL_STTYPE_INCREMENT) {
        for (;;) {
            u8 idx;
            NWC24Err res;

            idx = task->subTaskIndex;
            dlHead = GetDlTaskListHead();
            if (task == NULL) {
                res = NWC24_ERR_INVALID_VALUE;
            } else if (dlHead == NULL) {
                res = NWC24_ERR_LIB_NOT_OPENED;
            } else if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
                res = NWC24_ERR_INVALID_VALUE;
            } else {
                res = NWC24_OK;
            }

            if (res == NWC24_OK) {
                if (task->stType == 0) {
                    res = NWC24_ERR_INVALID_OPERATION;
                } else if (task->stFlags == 0) {
                    res = NWC24_ERR_FATAL;
                } else if (idx > NWC24_DL_SUBTASK_MAX - 1) {
                    res = NWC24_ERR_INVALID_VALUE;
                } else if ((task->stFlags & (1 << idx)) == 0) {
                    res = NWC24_ERR_DISABLED;
                } else {
                    res = NWC24_OK;
                }
            }

            if (res != NWC24_ERR_DISABLED) {
                if (res < NWC24_OK) {
                    return res;
                }
                break;
            }
            task->subTaskIndex = (idx + 1) & 0x1F;
        }
    }

    return StoreDlTask(dlTask);
}

NWC24Err NWC24iLoadDlHeader() {
    NWC24DlHeader* dlHead;
    NWC24Err result;
    NWC24Err res;
    NWC24Err res2 = NWC24_OK;
    NWC24File file;
    u32 length = 0;

    result = NWC24FOpen(&file, DLFilePath, 2);
    if (result < NWC24_OK) {
        return result;
    }

    res = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (res < NWC24_OK) {
        goto check;
    }
    res = NWC24FRead((NWC24DlHeader*)NWC24WorkP->dlHead, NWC24_DL_HEADER_SIZE, &file);
    if (res < NWC24_OK) {
        res2 = res;
    }
    res = res2;

check:
    if (res < NWC24_OK) {
        return res;
    }

    res = NWC24FGetLength(&file, &length);
    if (res >= NWC24_OK) {
        dlHead = GetDlTaskListHead();
        if (dlHead->numTasks == 0 && dlHead->numTasksInFile != 0) {
            NWC24File file2;

            dlHead->numTasks = dlHead->numTasksInFile;
            if (dlHead->numTasksInFile > NWC24_DL_RECORD_MAX) {
                dlHead->numTasksInFile = NWC24_DL_RECORD_MAX;
            }

            res = NWC24FOpen(&file2, DLFilePath, 4);
            if (res >= NWC24_OK) {
                res = NWC24FSeek(&file2, 0, NWC24_SEEK_BEG);
                if (res >= NWC24_OK) {
                    NWC24FWrite(GetDlTaskListHead(), NWC24_DL_HEADER_SIZE, &file2);
                }
                NWC24FClose(&file2);
            }
        }

        if (dlHead->numTasks < 1 || dlHead->minTasks < 1 || dlHead->numTasks < dlHead->minTasks) {
            res = NWC24_ERR_BROKEN;
        } else {
            res = NWC24_OK;
        }
    }

    res2 = NWC24FClose(&file);
    if (res != NWC24_OK) {
        res2 = res;
    }

    return res2;
}

NWC24Err NWC24ExtendDlTaskList(u32 num) {
    NWC24DlHeader* dlHead;
    NWC24Err result;
    NWC24Err res;
    NWC24Err res2;
    NWC24File file;
    u16 id;

    dlHead = GetDlTaskListHead();
    if (dlHead == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    id = dlHead->numTasks;
    if (num > NWC24_DL_TASK_MAX || id > num) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (id == num) {
        return NWC24_OK;
    }
    dlHead->numTasks = num;

    result = NWC24FOpen(&file, DLFilePath, 4);
    if (result < NWC24_OK) {
        return result;
    }

    for (; id < num; ) {
        NWC24DlTaskEx* task = GetDlTaskWork();

        memset(task, 0, NWC24_DL_TASK_SIZE);
        task->dlType = 0xFF;
        task->id = id;
        memset((NWC24DlTaskInfo*)((u8*)NWC24WorkP + 0x3680) + id, 0, sizeof(NWC24DlTaskInfo));

        if (GetDlTaskListHead()->numTasks > NWC24_DL_TASK_MAX || task->id >= GetDlTaskListHead()->numTasks) {
            res = NWC24_ERR_INVALID_VALUE;
        } else {
            res = NWC24FSeek(&file, task->id * NWC24_DL_TASK_SIZE + NWC24_DL_HEADER_SIZE, NWC24_SEEK_BEG);
        }
        if (res < NWC24_OK) {
            goto close;
        }

        memcpy(GetDlTaskWork(), task, NWC24_DL_TASK_SIZE);
        res = NWC24FWrite(GetDlTaskWork(), NWC24_DL_TASK_SIZE, &file);
        res2 = res < NWC24_OK ? res : NWC24_OK;
        res = res2;
        res2 = res;
        if (res < NWC24_OK) {
            goto close;
        }
        id++;
    }

    res = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (res >= NWC24_OK) {
        res = NWC24FWrite(GetDlTaskListHead(), NWC24_DL_HEADER_SIZE, &file);
        res = res < NWC24_OK ? res : NWC24_OK;
    }

close:
    res2 = NWC24FClose(&file);
    if (res != NWC24_OK) {
        res2 = res;
    }
    res = NWC24iLoadDlHeader();
    if (res2 != NWC24_OK) {
        res = res2;
    }
    return res;
}

NWC24Err NWC24iCheckDlHeaderConsistency(NWC24DlHeader* dlHead, BOOL fixBroken) {
    u32 i;
    NWC24Err result;
    NWC24Err res;
    NWC24Err res2;
    NWC24DlTaskEx task;
    NWC24File file;

    i = 0;
    while ((u16)i < dlHead->numTasks) {
        if ((u16)i >= GetDlTaskListHead()->numTasks || (u16)i == 0xFFFF) {
            result = NWC24_ERR_INVALID_VALUE;
        } else if (GetDlTaskListHead()->infos[i].used == 0) {
            result = NWC24_ERR_NOT_FOUND;
        } else {
            result = NWC24_OK;
        }

        if (result == NWC24_OK && fixBroken != FALSE) {
            if (GetDlTaskListHead() == NULL) {
                result = NWC24_ERR_LIB_NOT_OPENED;
                goto merge;
            }

            if ((u16)i >= GetDlTaskListHead()->numTasks || (u16)i == 0xFFFF) {
                result = NWC24_ERR_INVALID_VALUE;
            } else if (GetDlTaskListHead()->infos[i].used == 0) {
                result = NWC24_ERR_NOT_FOUND;
            } else {
                result = NWC24_OK;
            }

            if (result < NWC24_OK) {
                goto merge;
            }

            result = NWC24FOpen(&file, DLFilePath, 0xA);
            if (result < NWC24_OK) {
                goto merge;
            }

            if (GetDlTaskListHead()->numTasks > NWC24_DL_TASK_MAX || (u16)i >= GetDlTaskListHead()->numTasks) {
                result = NWC24_ERR_INVALID_VALUE;
            } else {
                result = NWC24FSeek(&file, i * NWC24_DL_TASK_SIZE + NWC24_DL_HEADER_SIZE, NWC24_SEEK_BEG);
            }

            if (result < NWC24_OK) {
                res2 = result;
            } else {
                result = NWC24FRead(&task, NWC24_DL_TASK_SIZE, &file);
                res2 = result < NWC24_OK ? result : NWC24_OK;
            }
            NWC24FClose(&file);
            if (res2 != NWC24_OK) {
                result = res2;
            }

        merge:
            if (result < NWC24_OK) {
                NWC24DlHeader* head = GetDlTaskListHead();
                if (&task == NULL) {
                    res = NWC24_ERR_INVALID_VALUE;
                } else if (head == NULL) {
                    res = NWC24_ERR_LIB_NOT_OPENED;
                } else if (task.id != 0xFFFF && task.id >= head->numTasks) {
                    res = NWC24_ERR_INVALID_VALUE;
                } else {
                    res = NWC24_OK;
                }

                if (res == NWC24_OK) {
                    res = DeleteDlTask((NWC24DlTask*)&task);
                    if (res >= NWC24_OK) {
                        task.id = 0xFFFF;
                    }
                }
            } else {
                NWC24DlHeader* head = GetDlTaskListHead();
                if ((u16)i >= head->minTasks && (s16)task.numSubTasks == 0) {
                    head = GetDlTaskListHead();
                    if (&task == NULL) {
                        res = NWC24_ERR_INVALID_VALUE;
                    } else if (head == NULL) {
                        res = NWC24_ERR_LIB_NOT_OPENED;
                    } else if (task.id != 0xFFFF && task.id >= head->numTasks) {
                        res = NWC24_ERR_INVALID_VALUE;
                    } else {
                        res = NWC24_OK;
                    }

                    if (res == NWC24_OK) {
                        res = DeleteDlTask((NWC24DlTask*)&task);
                        if (res >= NWC24_OK) {
                            task.id = 0xFFFF;
                        }
                    }
                }
            }
        }

        i++;
    }

    return NWC24_OK;
}

NWC24Err NWC24iCloseDlTaskList() {
    return NWC24_OK;
}

NWC24Err NWC24iOpenDlTaskList() {
    NWC24Err result;

    result = NWC24iLoadDlHeader();
    if (result < NWC24_OK) {
        return result;
    }

    NWC24iSynchronizeRtcCounter(FALSE);

    result = NWC24iCheckDlHeaderConsistency(GetDlTaskListHead(), FALSE);
    if (result < NWC24_OK) {
        return result;
    }

    return NWC24_OK;
}

NWC24Err NWC24SetDlPriority(NWC24DlTask* dlTask, u8 dlPrio) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = GetDlTaskListHead();
    NWC24Err result;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        if (NWC24IsMsgLibOpenedByTool() == FALSE) {
            u32 appId = task->appId;
            BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
            if (eq == FALSE) {
                BOOL owned = FALSE;
                u16 groupId = task->groupId;
                if ((task->flags & 0x40) != 0) {
                if (groupId == (u16)NWC24GetGroupId()) {
                    owned = TRUE;
                    }
                }

                if (owned == FALSE) {
                    result = NWC24_ERR_PROTECTED;
                    goto done;
                }
            }
        }

        if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }

done:
    if (result != NWC24_OK) {
        return result;
    }

    task->priority = dlPrio;
    return NWC24_OK;
}

static NWC24Err DeleteDlTask(NWC24DlTask* dlTask) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlTaskEx* work;
    NWC24Err result;
    NWC24Err res;
    NWC24Err res2;
    NWC24File file;
    u16 id;

    result = NWC24FOpen(&file, DLFilePath, 4);
    if (result < NWC24_OK) {
        return result;
    }

    work = GetDlTaskWork();
    id = task->id;
    memset(work, 0, NWC24_DL_TASK_SIZE);
    work->dlType = 0xFF;
    work->id = id;
    memset((NWC24DlTaskInfo*)((u8*)NWC24WorkP + 0x3680) + id, 0, sizeof(NWC24DlTaskInfo));

    {
        u16 numTasks = GetDlTaskListHead()->numTasks;
        if (numTasks > NWC24_DL_TASK_MAX || work->id >= numTasks) {
            res = NWC24_ERR_INVALID_VALUE;
        } else {
            res = NWC24FSeek(&file, work->id * NWC24_DL_TASK_SIZE + NWC24_DL_HEADER_SIZE, NWC24_SEEK_BEG);
        }
    }

    if (res < NWC24_OK) {
        goto merge;
    }
    memcpy(GetDlTaskWork(), work, NWC24_DL_TASK_SIZE);
    res = NWC24FWrite(GetDlTaskWork(), NWC24_DL_TASK_SIZE, &file);
    res = res < NWC24_OK ? res : NWC24_OK;
merge:
    res2 = res;
    if (res < NWC24_OK) {
        goto close;
    }
    memset((NWC24DlTaskInfo*)((u8*)NWC24WorkP + 0x3680) + task->id, 0, sizeof(NWC24DlTaskInfo));

    res = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (res >= NWC24_OK) {
        res = NWC24FWrite(GetDlTaskListHead(), NWC24_DL_HEADER_SIZE, &file);
        res = res < NWC24_OK ? res : NWC24_OK;
    }
    res2 = res;
close:
    res = NWC24FClose(&file);
    if (res2 != NWC24_OK) {
        res = res2;
    }
    return res;
}

NWC24Err NWC24DumpDlTask(NWC24DlTask* dlTask) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = GetDlTaskListHead();
    NWC24Err result;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24_OK;
    }

    return result != NWC24_OK ? result : NWC24_OK;
}

NWC24Err NWC24GetDlTask(NWC24DlTask* dlTask, NWC24DlId dlId) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead;
    NWC24File file;
    NWC24Err result;
    NWC24Err res2;

    if (GetDlTaskListHead() == NULL) {
        return NWC24_ERR_LIB_NOT_OPENED;
    }

    if (dlId >= GetDlTaskListHead()->numTasks || dlId == 0xFFFF) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (GetDlTaskListHead()->infos[dlId].used == 0) {
        result = NWC24_ERR_NOT_FOUND;
    } else {
        result = NWC24_OK;
    }

    if (result < NWC24_OK) {
        return result;
    }

    result = NWC24FOpen(&file, DLFilePath, 0xA);
    if (result < NWC24_OK) {
        return result;
    }

    dlHead = GetDlTaskListHead();
    if (dlHead->numTasks > NWC24_DL_TASK_MAX || dlId >= dlHead->numTasks) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24FSeek(&file, dlId * NWC24_DL_TASK_SIZE + NWC24_DL_HEADER_SIZE, NWC24_SEEK_BEG);
    }

    if (result < NWC24_OK) {
        res2 = result;
    } else {
        result = NWC24FRead(task, NWC24_DL_TASK_SIZE, &file);
        res2 = result < NWC24_OK ? result : NWC24_OK;
    }

    NWC24FClose(&file);
    if (res2 != NWC24_OK) {
        result = res2;
    }

done:
    return result;
}

static NWC24Err StoreDlTask(NWC24DlTask* dlTask) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead;
    NWC24Err result;
    NWC24Err res;
    NWC24Err res2;
    NWC24File file;

    result = NWC24FOpen(&file, DLFilePath, 4);
    if (result < NWC24_OK) {
        return result;
    }

    {
        u16 numTasks = GetDlTaskListHead()->numTasks;
        if (numTasks > NWC24_DL_TASK_MAX || task->id >= numTasks) {
            res = NWC24_ERR_INVALID_VALUE;
        } else {
            res = NWC24FSeek(&file, task->id * NWC24_DL_TASK_SIZE + NWC24_DL_HEADER_SIZE, NWC24_SEEK_BEG);
        }
    }

    if (res < NWC24_OK) {
        res2 = res;
        goto close;
    }

    memcpy(GetDlTaskWork(), task, NWC24_DL_TASK_SIZE);
    res = NWC24FWrite(GetDlTaskWork(), NWC24_DL_TASK_SIZE, &file);
    res = res < NWC24_OK ? res : NWC24_OK;

    res2 = res;
    if (res < NWC24_OK) {
        goto close;
    }

    dlHead = GetDlTaskListHead();
    dlHead->infos[task->id].used = task->appId;
    dlHead->infos[task->id].priority = task->priority;
    res2 = NWC24_OK;
    if (res2 < NWC24_OK) {
        goto close;
    }

    res = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (res >= NWC24_OK) {
        res = NWC24FWrite(GetDlTaskListHead(), NWC24_DL_HEADER_SIZE, &file);
        res = res < NWC24_OK ? res : NWC24_OK;
    }
    res2 = res;

close:
    res = NWC24FClose(&file);
    if (res2 != NWC24_OK) {
        res = res2;
    }
    return res;
}

static u32 IterationPredicatorPriority(NWC24DlId id) {
    return GetDlTaskListHead()->infos[id].priority;
}

NWC24Err NWC24iCreateDlTaskList() {
    NWC24DlHeader* dlHead = GetDlTaskListHead();
    NWC24Err result;
    NWC24Err res;
    NWC24Err res2;
    NWC24File file;
    u32 i;

    memset(dlHead, 0, NWC24_DL_HEADER_SIZE);
    dlHead->magic = NWC24_DL_HEADER_MAGIC;
    dlHead->version = NWC24_DL_HEADER_VERSION;
    dlHead->unk_0x0C = 0;
    dlHead->unk_0x0E = 0;
    dlHead->numTasks = NWC24_DL_TASK_MAX;
    dlHead->numTasksInFile = NWC24_DL_RECORD_MAX;
    dlHead->minTasks = NWC24_DL_MENU_RESERVED;

    res = NWC24FOpen(&file, DLFilePath, 1);
    if (res < NWC24_OK) {
        return res;
    }
    res = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
    if (res >= NWC24_OK) {
        res = NWC24FWrite(GetDlTaskListHead(), NWC24_DL_HEADER_SIZE, &file);
        res = res < NWC24_OK ? res : NWC24_OK;
    }
    res2 = res;
    if (res < NWC24_OK) {
        goto close;
    }

    {
        NWC24DlTaskEx* task;
        u8 dlType = 0xFF;
        u16 numTasks;

        for (i = 0; i < NWC24_DL_TASK_MAX; i++) {
            task = GetDlTaskWork();
            memset(task, 0, NWC24_DL_TASK_SIZE);
            task->dlType = dlType;
            task->id = i;
            memset(&dlHead->infos[i], 0, sizeof(NWC24DlTaskInfo));

            numTasks = GetDlTaskListHead()->numTasks;
            if (numTasks > NWC24_DL_TASK_MAX || task->id >= numTasks) {
                res = NWC24_ERR_INVALID_VALUE;
            } else {
                res = NWC24FSeek(&file, task->id * NWC24_DL_TASK_SIZE + NWC24_DL_HEADER_SIZE, NWC24_SEEK_BEG);
            }

            if (res >= NWC24_OK) {
                memcpy(GetDlTaskWork(), task, NWC24_DL_TASK_SIZE);
                res = NWC24FWrite(GetDlTaskWork(), NWC24_DL_TASK_SIZE, &file);
                res = res < NWC24_OK ? res : NWC24_OK;
            }

            res2 = res;
            if (res < NWC24_OK) {
                break;
            }
        }
    }

close:
    res = NWC24FClose(&file);
    if (res2 != NWC24_OK) {
        res = res2;
    }
    return res;
}

NWC24Err NWC24GetDlOptOutFlags(NWC24DlTask* dlTask, u8* dlOptOutFlags) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = NWC24WorkP != NULL ? (NWC24DlHeader*)NWC24WorkP->dlHead : NULL;
    NWC24Err result;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24_OK;
    }

    if (result != NWC24_OK) {
        return result;
    }

    if (dlOptOutFlags == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    *dlOptOutFlags = task->optOutFlags;
    return NWC24_OK;
}

NWC24Err NWC24SetDlId(NWC24DlTask* dlTask, NWC24DlId dlId) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = NWC24WorkP != NULL ? (NWC24DlHeader*)NWC24WorkP->dlHead : NULL;
    NWC24Err result;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24_OK;
    }

    if (result != NWC24_OK) {
        return result;
    }

    dlHead = GetDlTaskListHead();
    if (dlId >= dlHead->numTasks) {
        return NWC24_ERR_INVALID_VALUE;
    }

    task->id = dlId;
    return NWC24_OK;
}

NWC24Err NWC24SetDlUrl(NWC24DlTask* dlTask, const char* dlUrl) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = GetDlTaskListHead();
    NWC24Err result;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        if (NWC24IsMsgLibOpenedByTool() == FALSE) {
            u32 appId = task->appId;
            BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
            if (eq == FALSE) {
                BOOL owned = FALSE;
                u16 groupId = task->groupId;
                if ((task->flags & 0x40) != 0) {
                    if (groupId == (u16)NWC24GetGroupId()) {
                        owned = TRUE;
                    }
                }

                if (owned == FALSE) {
                    result = NWC24_ERR_PROTECTED;
                    goto done;
                }
            }
        }

        if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }

done:
    if (result != NWC24_OK) {
        return result;
    }

    result = NWC24iCheckStringLength(dlUrl, 7, 0x100);
    if (result >= NWC24_OK) {
        if (strncmp(dlUrl, "http://", 7) != 0 && strncmp(dlUrl, "https://", 8) != 0) {
            result = NWC24_ERR_FORMAT;
        } else {
            result = NWC24_OK;
        }
    }

    if (result < NWC24_OK) {
        return result;
    }

    if (NWC24iLaxParameterCheck == 0 && (task->flags & 4) != 0 && strncmp(dlUrl, "http://", 7) == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    NWC24iStrLCpy(task->url, dlUrl, sizeof(task->url));
    return NWC24_OK;
}

NWC24Err NWC24GetDlAppId(const NWC24DlTask* dlTask, u32* dlAppId) {
    const NWC24DlTaskEx* task = (const NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = NWC24WorkP != NULL ? (NWC24DlHeader*)NWC24WorkP->dlHead : NULL;
    NWC24Err result;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24_OK;
    }

    if (result != NWC24_OK) {
        return result;
    }

    if (dlAppId == NULL) {
        return NWC24_ERR_INVALID_VALUE;
    }

    *dlAppId = task->appId;
    return NWC24_OK;
}

NWC24Err NWC24AddDlTask(NWC24DlTask* dlTask) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = GetDlTaskListHead();
    NWC24Err result;
    NWC24File file;

    if (dlHead->numTasks == 0 && dlHead->numTasksInFile != 0) {
        dlHead->numTasks = dlHead->numTasksInFile;
        if (dlHead->numTasksInFile > NWC24_DL_RECORD_MAX) {
            dlHead->numTasksInFile = NWC24_DL_RECORD_MAX;
        }

        result = NWC24FOpen(&file, DLFilePath, 4);
        if (result >= NWC24_OK) {
            result = NWC24FSeek(&file, 0, NWC24_SEEK_BEG);
            if (result >= NWC24_OK) {
                NWC24FWrite(GetDlTaskListHead(), NWC24_DL_HEADER_SIZE, &file);
            }
            NWC24FClose(&file);
        }
    }

    if (dlHead->numTasks < 1 || dlHead->minTasks < 1 || dlHead->numTasks < dlHead->minTasks) {
        result = NWC24_ERR_BROKEN;
    } else {
        result = NWC24_OK;
    }

    if (result < NWC24_OK) {
        goto done;
    }

    result = AddTaskInternal(dlTask, GetDlTaskListHead()->minTasks, GetDlTaskListHead()->numTasks);
    if (result < NWC24_OK) {
        goto done;
    }

    {
        OSTime time;
        NWC24Err res;

        time = 0;
        res = NWC24iGetUniversalTime(&time);
        if (res < NWC24_OK) {
            result = res;
            goto done;
        }

        time += (s64)(s32)(task->interval * 60);

        {
            NWC24DlId id;
            NWC24Err res2;
            dlHead = GetDlTaskListHead();

            if (task == NULL) {
                res2 = NWC24_ERR_INVALID_VALUE;
            } else if (dlHead == NULL) {
                res2 = NWC24_ERR_LIB_NOT_OPENED;
            } else if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
                res2 = NWC24_ERR_INVALID_VALUE;
            } else {
                res2 = NWC24_OK;
            }

            if (res2 == NWC24_OK) {
                id = task->id;
                if (id == 0xFFFF) {
                    res2 = NWC24_ERR_FAILED;
                } else {
                    GetDlTaskListHead()->infos[id].nextTime = (u32)(time / 60);
                }
            }

            result = res2;
        }
    }

done:
    return result;
}

NWC24Err NWC24PurgeOldestDlTask() {
    NWC24DlIterateWork work;
    NWC24DlId id;
    NWC24DlTaskEx task;
    NWC24File file;
    NWC24Err result;
    NWC24Err res2;

    memset(&work, 0, sizeof(work));
    result = NWC24_OK;
    work.unk_0x04 = 0x7FFFFFFF;
    work.unk_0x08 = 0x80000001;
    work.unk_0x00 = 0;
    work.unk_0x0C = -1;
    work.unk_0x10 = 1;
    work.unk_0x14 = 1;

    while (result >= NWC24_OK) {
        result = NWC24IterateDlTaskEx(&work, &id);
        if (result == NWC24_OK) {
            if (id >= GetDlTaskListHead()->minTasks) {
                break;
            }
        }
    }

    if (result < NWC24_OK) {
        if (result == NWC24_ERR_DONE) {
            result = NWC24_ERR_FAILED;
        }
        return result;
    }

    if (GetDlTaskListHead() == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
        goto check;
    }

    if (id >= GetDlTaskListHead()->numTasks || id == 0xFFFF) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (GetDlTaskListHead()->infos[id].used == 0) {
        result = NWC24_ERR_NOT_FOUND;
    } else {
        result = NWC24_OK;
    }

    if (result < NWC24_OK) {
        goto check;
    }

    result = NWC24FOpen(&file, DLFilePath, 0xA);
    if (result < NWC24_OK) {
        goto check;
    }

    if (GetDlTaskListHead()->numTasks > NWC24_DL_TASK_MAX || id >= GetDlTaskListHead()->numTasks) {
        result = NWC24_ERR_INVALID_VALUE;
    } else {
        result = NWC24FSeek(&file, id * NWC24_DL_TASK_SIZE + NWC24_DL_HEADER_SIZE, NWC24_SEEK_BEG);
    }

    if (result < NWC24_OK) {
        res2 = result;
        goto close;
    }
    result = NWC24FRead(&task, NWC24_DL_TASK_SIZE, &file);
    res2 = result < NWC24_OK ? result : NWC24_OK;
close:
    NWC24FClose(&file);
    if (res2 != NWC24_OK) {
        result = res2;
    }

check:
    if (result < NWC24_OK) {
        return result;
    }

    {
        NWC24DlHeader* dlHead = GetDlTaskListHead();
        NWC24Err res;

        if (&task == NULL) {
            res = NWC24_ERR_INVALID_VALUE;
        } else if (dlHead == NULL) {
            res = NWC24_ERR_LIB_NOT_OPENED;
        } else if (task.id != 0xFFFF && task.id >= dlHead->numTasks) {
            res = NWC24_ERR_INVALID_VALUE;
        } else {
            res = NWC24_OK;
        }

        if (res == NWC24_OK) {
            res = DeleteDlTask((NWC24DlTask*)&task);
            if (res >= NWC24_OK) {
                task.id = 0xFFFF;
            }
        }

        return res;
    }
}

NWC24Err NWC24iInitDlTaskList(NWC24Err mode) {
    NWC24DlHeader* dlHead;
    NWC24Err result;

    result = NWC24iOpenDlTaskList();
    if (result != NWC24_OK || mode != NWC24_OK) {
        if (result == NWC24_ERR_VER_MISMATCH) {
            dlHead = GetDlTaskListHead();
            if (dlHead != NULL && dlHead->version > 1) {
                return result;
            }
        }
        NWC24iCreateDlTaskList();
    }
    return result;
}

static NWC24Err AddTaskInternal(NWC24DlTask* dlTask, u16 first, u16 last) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = GetDlTaskListHead();
    NWC24Err result;
    NWC24Err res;
    NWC24Err res2;
    u16 i;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        if (NWC24IsMsgLibOpenedByTool() == FALSE) {
            u32 appId = task->appId;
            BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
            if (eq == FALSE) {
                BOOL owned = FALSE;
                u16 groupId = task->groupId;
                if ((task->flags & 0x40) != 0) {
                if (groupId == (u16)NWC24GetGroupId()) {
                    owned = TRUE;
                    }
                }

                if (owned == FALSE) {
                    result = NWC24_ERR_PROTECTED;
                    goto done;
                }
            }
        }

        if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }

    if (result != NWC24_OK) {
        goto done;
    }

    if (task->id >= GetDlTaskListHead()->numTasks && task->id != 0xFFFF) {
        res2 = NWC24_ERR_INVALID_VALUE;
    } else {
        res = NWC24iCheckStringLength(task->url, 7, 0x100);
        if (res >= NWC24_OK) {
            if (strncmp(task->url, "http://", 7) == 0) {
                res = NWC24_OK;
            } else if (strncmp(task->url, "https://", 8) == 0) {
                res = NWC24_OK;
            } else {
                res = NWC24_ERR_FORMAT;
            }
        }
        res2 = res < NWC24_OK ? res : NWC24_OK;
    }
    if (res2 < NWC24_OK) {
        result = res2;
        goto done;
    }

retry:
    if (task->id != 0xFFFF) {
    {
        OSTime time;
        NWC24Err res3;

        dlHead = GetDlTaskListHead();

        if (task == NULL) {
            res3 = NWC24_ERR_INVALID_VALUE;
        } else if (dlHead == NULL) {
            res2 = NWC24_ERR_LIB_NOT_OPENED;
        } else {
            if (NWC24IsMsgLibOpenedByTool() == FALSE) {
                u32 appId = task->appId;
                BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
                if (eq == FALSE) {
                    BOOL owned = FALSE;
                    u16 groupId = task->groupId;
                    if ((task->flags & 0x40) != 0) {
                    if (groupId == (u16)NWC24GetGroupId()) {
                        owned = TRUE;
                        }
                    }

                    if (owned == FALSE) {
                        res2 = NWC24_ERR_PROTECTED;
                        goto res2_done;
                    }
                }
            }

            if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
                res2 = NWC24_ERR_INVALID_VALUE;
            } else {
                res2 = NWC24_OK;
            }
        }

    res2_done:
        if (res2 != NWC24_OK) {
            result = res2;
            goto done;
        }

        if (task->id != 0xFFFF && task->id < GetDlTaskListHead()->numTasks) {
            res = NWC24iGetUniversalTime(&time);
        } else {
            res2 = NWC24_ERR_INVALID_VALUE;
            goto done;
        }
        if (res < NWC24_OK) {
            res2 = res;
        } else {
            NWC24Err res3;
            NWC24DlId id;
            dlHead = GetDlTaskListHead();

            if (task == NULL) {
                res3 = NWC24_ERR_INVALID_VALUE;
            } else if (dlHead == NULL) {
                res3 = NWC24_ERR_LIB_NOT_OPENED;
            } else if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
                res3 = NWC24_ERR_INVALID_VALUE;
            } else {
                res3 = NWC24_OK;
            }

            if (res3 == NWC24_OK) {
                id = task->id;
                if (id == 0xFFFF) {
                    res3 = NWC24_ERR_FAILED;
                } else {
                    GetDlTaskListHead()->infos[id].lastAccess = (u32)(time / 60);
                }
            }

            res = res3;
            if (res3 >= NWC24_OK) {
                res2 = res;
            }
        }

        if (res2 < NWC24_OK) {
            result = res2;
            goto done;
        }

        {
            NWC24Err res4;
            dlHead = GetDlTaskListHead();

            if (task == NULL) {
                res4 = NWC24_ERR_INVALID_VALUE;
            } else if (dlHead == NULL) {
                res4 = NWC24_ERR_LIB_NOT_OPENED;
            } else {
                if (NWC24IsMsgLibOpenedByTool() == FALSE) {
                    u32 appId = task->appId;
                    BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
                    if (eq == FALSE) {
                        BOOL owned = FALSE;
                        u16 groupId = task->groupId;
                        if ((task->flags & 0x40) != 0) {
                        if (groupId == (u16)NWC24GetGroupId()) {
                            owned = TRUE;
                            }
                        }

                        if (owned == FALSE) {
                            res4 = NWC24_ERR_PROTECTED;
                            goto res4_done;
                        }
                    }
                }

                if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
                    res4 = NWC24_ERR_INVALID_VALUE;
                } else {
                    res4 = NWC24_OK;
                }
            }

        res4_done:
            if (res4 == NWC24_OK) {
                task->unk_0x20 = 0;
                task->processedSubTasks = 0;
            }
        }

        if (task->stType == NWC24_DL_STTYPE_INCREMENT) {
            for (;;) {
                u8 idx = task->subTaskIndex;
                NWC24Err res5;
                dlHead = GetDlTaskListHead();

                if (task == NULL) {
                    res5 = NWC24_ERR_INVALID_VALUE;
                } else if (dlHead == NULL) {
                    res5 = NWC24_ERR_LIB_NOT_OPENED;
                } else if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
                    res5 = NWC24_ERR_INVALID_VALUE;
                } else {
                    res5 = NWC24_OK;
                }

                if (res5 == NWC24_OK) {
                    if (task->stType == 0) {
                        res5 = NWC24_ERR_INVALID_OPERATION;
                    } else if (task->stFlags == 0) {
                        res5 = NWC24_ERR_FATAL;
                    } else if (idx > NWC24_DL_SUBTASK_MAX - 1) {
                        res5 = NWC24_ERR_INVALID_VALUE;
                    } else if ((task->stFlags & (1 << idx)) == 0) {
                        res5 = NWC24_ERR_DISABLED;
                    } else {
                        res5 = NWC24_OK;
                    }
                }

                if (res5 != NWC24_ERR_DISABLED) {
                    if (res5 < NWC24_OK) {
                        res = res5;
                        goto merge;
                    }
                    break;
                }
                task->subTaskIndex = (idx + 1) & 0x1F;
            }
        }

        if (res < NWC24_OK) {
            goto merge;
        }
        res = StoreDlTask(dlTask);
    merge:
        result = res;
        goto done;
    }

    } else {
        u16 id;

        if (task == NULL || first > last || first >= dlHead->numTasks || last > dlHead->numTasks) {
            res = NWC24_ERR_INVALID_VALUE;
        } else {
            res = NWC24_ERR_FULL;
            for (id = first; id < last; id++) {
                if (dlHead->infos[id].used == 0) {
                    task->id = id;
                    res = NWC24_OK;
                    break;
                }
            }
        }

        if (res == NWC24_ERR_FULL) {
            res = NWC24PurgeOldestDlTask();
        }
        if (res >= NWC24_OK) {
            goto retry;
        }
        result = res;
        goto done;
    }

done:
    return result;
}

static u32 IterationPredicatorLastAccess(NWC24DlId id) {
    return GetDlTaskListHead()->infos[id].lastAccess;
}

static u32 IterationPredicatorNextTime(NWC24DlId id) {
    return GetDlTaskListHead()->infos[id].nextTime;
}

NWC24Err NWC24SetDlInterval(NWC24DlTask* dlTask, u16 dlInterval) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = GetDlTaskListHead();
    NWC24Err result;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        if (NWC24IsMsgLibOpenedByTool() == FALSE) {
            u32 appId = task->appId;
            BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
            if (eq == FALSE) {
                BOOL owned = FALSE;
                u16 groupId = task->groupId;
                if ((task->flags & 0x40) != 0) {
                if (groupId == (u16)NWC24GetGroupId()) {
                    owned = TRUE;
                    }
                }

                if (owned == FALSE) {
                    result = NWC24_ERR_PROTECTED;
                    goto check;
                }
            }
        }

        if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }

check:
    if (result != NWC24_OK) {
        return result;
    }

    if (NWC24iLaxParameterCheck == 0) {
        NWC24DlHeader* dlHead2 = GetDlTaskListHead();
        if (task->id >= dlHead2->numTasksInFile && (task->flags & 0x40000000) == 0) {
            if (dlInterval < 0xB4 || dlInterval > 0x2760) {
                return NWC24_ERR_INVALID_VALUE;
            }
        }
    }

    if (task->interval != dlInterval) {
        task->interval = dlInterval;

        if (task->id != 0xFFFF) {
            OSTime time;
            NWC24Err res;
            NWC24DlHeader* dlHead2;

            time = 0;
            res = NWC24iGetUniversalTime(&time);
            if (res >= NWC24_OK) {
                NWC24Err res2;
                s64 nextTime = time + task->interval * 0x3C;

                dlHead2 = GetDlTaskListHead();

                if (task == NULL) {
                    res2 = NWC24_ERR_INVALID_VALUE;
                } else if (dlHead2 == NULL) {
                    res2 = NWC24_ERR_LIB_NOT_OPENED;
                } else if (task->id != 0xFFFF && task->id >= dlHead2->numTasks) {
                    res2 = NWC24_ERR_INVALID_VALUE;
                } else {
                    res2 = NWC24_OK;
                }

                if (res2 == NWC24_OK) {
                    if (task->id != 0xFFFF) {
                        GetDlTaskListHead()->infos[task->id].nextTime = (u32)(nextTime / 0x3C);
                    }
                }
            }
        }
    }

    return NWC24_OK;
}

NWC24Err NWC24SetDlFlags(NWC24DlTask* dlTask, u32 dlFlags) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24DlHeader* dlHead = GetDlTaskListHead();
    NWC24Err result;

    if (task == NULL) {
        result = NWC24_ERR_INVALID_VALUE;
    } else if (dlHead == NULL) {
        result = NWC24_ERR_LIB_NOT_OPENED;
    } else {
        if (NWC24IsMsgLibOpenedByTool() == FALSE) {
            u32 appId = task->appId;
            BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
            if (eq == FALSE) {
                BOOL owned = FALSE;
                u16 groupId = task->groupId;
                if ((task->flags & 0x40) != 0) {
                if (groupId == (u16)NWC24GetGroupId()) {
                    owned = TRUE;
                    }
                }

                if (owned == FALSE) {
                    result = NWC24_ERR_PROTECTED;
                    goto done;
                }
            }
        }

        if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
            result = NWC24_ERR_INVALID_VALUE;
        } else {
            result = NWC24_OK;
        }
    }

done:
    if (result != NWC24_OK) {
        return result;
    }

    if (NWC24iLaxParameterCheck == 0 && (dlFlags & 4) != 0 && strncmp(task->url, "http://", 7) == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }

    switch (task->dlType) {
    case 0:
    case 1:
        if ((dlFlags & 0x80000038) != 0) {
            return NWC24_ERR_INVALID_OPERATION;
        }
        break;
    default:
        break;
    }

    task->flags = dlFlags;
    return NWC24_OK;
}

NWC24Err NWC24DeleteDlTask(NWC24DlTask* dlTask) {
    NWC24DlTaskEx* task = (NWC24DlTaskEx*)dlTask;
    NWC24Err result;

    if (NWC24GetAppId() != NWC24_DL_APPID_KD) {
        NWC24DlHeader* dlHead = GetDlTaskListHead();

        if (task == NULL) {
            result = NWC24_ERR_INVALID_VALUE;
        } else if (dlHead == NULL) {
            result = NWC24_ERR_LIB_NOT_OPENED;
        } else {
            if (NWC24IsMsgLibOpenedByTool() == FALSE) {
                u32 appId = task->appId;
                BOOL eq = (appId & 0xFFFFFF00) == (NWC24GetAppId() & 0xFFFFFF00);
                if (eq == FALSE) {
                    BOOL owned = FALSE;
                    u16 groupId = task->groupId;
                    if ((task->flags & 0x40) != 0) {
                    if (groupId == (u16)NWC24GetGroupId()) {
                        owned = TRUE;
                        }
                    }

                    if (owned == FALSE) {
                        result = NWC24_ERR_PROTECTED;
                        goto done;
                    }
                }
            }

            if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
                result = NWC24_ERR_INVALID_VALUE;
            } else {
                result = NWC24_OK;
            }
        }

        if (result != NWC24_OK) {
            return result;
        }
    }

    {
        NWC24DlHeader* dlHead = GetDlTaskListHead();
        NWC24Err res;

        if (task == NULL) {
            res = NWC24_ERR_INVALID_VALUE;
        } else if (dlHead == NULL) {
            res = NWC24_ERR_LIB_NOT_OPENED;
        } else if (task->id != 0xFFFF && task->id >= dlHead->numTasks) {
            res = NWC24_ERR_INVALID_VALUE;
        } else {
            res = NWC24_OK;
        }

        if (res != NWC24_OK) {
            return res;
        }
    }

    result = DeleteDlTask(dlTask);
    if (result >= NWC24_OK) {
        task->id = 0xFFFF;
    }

done:
    return result;
}

