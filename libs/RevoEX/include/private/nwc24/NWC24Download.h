#ifndef PRIVATE_NWC24_DOWNLOAD_H
#define PRIVATE_NWC24_DOWNLOAD_H

#include <revolution/types.h>

#include <revolution/nwc24/NWC24Err.h>
#include <revolution/nwc24/NWC24Dl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NWC24DlTaskInfo {
    u32 used;        // 0x00
    u32 nextTime;    // 0x04
    u32 lastAccess;  // 0x08
    u8 priority;     // 0x0c
    u8 padding[3];
} NWC24DlTaskInfo;

typedef struct NWC24DlHeader {
    u32 magic;           // 0x00
    u32 version;         // 0x04
    u32 unk_0x08;        // 0x08
    u16 unk_0x0C;        // 0x0c
    u16 unk_0x0E;        // 0x0e
    u16 numTasksInFile;  // 0x10
    u16 minTasks;        // 0x12
    u16 numTasks;        // 0x14
    u8 padding[0x6A];    // 0x16
    NWC24DlTaskInfo infos[NWC24_DL_TASK_MAX];  // 0x80
} NWC24DlHeader;

typedef struct NWC24DlTaskEx {
    u16 id;                // 0x000
    u8 dlType;             // 0x002
    u8 priority;           // 0x003
    u32 flags;             // 0x004
    u32 appId;             // 0x008
    u32 userIdLow;         // 0x00c
    u32 userIdHigh;        // 0x010
    u16 groupId;           // 0x014
    u16 unk_0x16;          // 0x016
    u16 numSubTasks;       // 0x018
    u16 processedSubTasks; // 0x01a
    u16 interval;          // 0x01c
    u16 subInterval;       // 0x01e
    u32 unk_0x20;          // 0x020
    u8 subTaskIndex;       // 0x024
    u8 stType;             // 0x025
    u8 padding0[2];        // 0x026
    u32 stFlags;           // 0x028
    u8 padding1[0x88];     // 0x02c
    char url[236];         // 0x0b4
    char fileName[0x5C];   // 0x1a0
    u8 optOutFlags;        // 0x1fc
    u8 padding2[3];        // 0x1fd
} NWC24DlTaskEx;

NWC24Err NWC24iOpenDlTaskList();
NWC24Err NWC24iCloseDlTaskList();

NWC24Err NWC24iLoadDlHeader();
NWC24Err NWC24iInitDlTaskList(NWC24Err mode);
NWC24Err NWC24iCreateDlTaskList();
NWC24Err NWC24iCheckDlHeaderConsistency(NWC24DlHeader* dlHead, BOOL fixBroken);

#ifdef __cplusplus
}
#endif

#endif  // PRIVATE_NWC24_DOWNLOAD_H
