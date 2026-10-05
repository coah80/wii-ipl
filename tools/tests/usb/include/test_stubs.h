#ifndef USB_TEST_STUBS_H
#define USB_TEST_STUBS_H
#include <stddef.h>
#include <stdint.h>
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int BOOL;
typedef s32 IOSFd;
typedef s32 IOSError;
typedef s32 IOSHeapId;
typedef IOSError (*IOSIpcCb)(IOSError, void*);
typedef void (*USBCallback)(IOSError, void*);
typedef void (*USBIsoCallback)(IOSError, void*, void*);
typedef struct IOSIoVector { u8* base; u32 length; } IOSIoVector;
#define TRUE 1
#define FALSE 0
#define DEFAULT_ALIGN 32
#define OSRoundUp32B(x) (((x) + 31) & ~31)
#define FS_MAX_PATH 64
#define IPC_RESULT_OK 0
#define IPC_RESULT_INVALID -4
#define IPC_RESULT_ALLOC_FAILED -22
void OSReport(const char*, ...);
BOOL OSDisableInterrupts(void);
void OSRestoreInterrupts(BOOL);
void DCFlushRange(void*, u32);
void DCInvalidateRange(void*, u32);
void* IPCGetBufferLo(void);
void* IPCGetBufferHi(void);
void IPCSetBufferLo(void*);
IOSHeapId iosCreateHeap(void*, u32);
void* iosAllocAligned(IOSHeapId, u32, u32);
IOSError iosFree(IOSHeapId, void*);
IOSError IOS_Open(const char*, u32);
IOSError IOS_Close(IOSFd);
IOSError IOS_OpenAsync(const char*, u32, IOSIpcCb, void*);
IOSError IOS_CloseAsync(IOSFd, IOSIpcCb, void*);
IOSError IOS_IoctlAsync(IOSFd, s32, void*, u32, void*, u32, IOSIpcCb, void*);
IOSError IOS_IoctlvAsync(IOSFd, s32, u32, u32, IOSIoVector*, IOSIpcCb, void*);
IOSError IOS_Ioctlv(IOSFd, s32, u32, u32, IOSIoVector*);
#endif
