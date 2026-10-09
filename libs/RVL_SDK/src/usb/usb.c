#include <private/usb.h>

#include <revolution/os.h>

#include <private/ios.h>
#include <private/ipc.h>

#include <private/fs.h>

#include <stdio.h>

#include <stdarg.h>
#include <string.h>

#define USB_HEAP_SIZE 0x4000

typedef enum {
    USB_NCLEAN_CLOSEDEVICE = 0,
    USB_NCLEAN_1,
    USB_NCLEAN_2,
    USB_NCLEAN_BULKMSG,
    USB_NCLEAN_4,
    USB_NCLEAN_5,
    USB_NCLEAN_6,
    USB_NCLEAN_CTRLMSG,
    USB_NCLEAN_MAX
} USBNClean;

typedef enum {
    USB_IOCTLV_CTRLMSG = 0,
    USB_IOCTLV_BLKMSG,
    USB_IOCTLV_INTRMSG
} USBIoctl;

typedef struct USBMsg {
    void* buffer;  // 0x00
    u16 length;    // 0x04
} USBMsg;

typedef struct {
    u8 bLength;
    u8 bDescriptorType;
    u16 bcdUSB;
    u8 bDeviceClass;
    u8 bDeviceSubClass;
    u8 bDeviceProtocol;
    u8 bMaxPacketSize0;
    u16 idVendor;
    u16 idProduct;
    u16 bcdDevice;
    u8 iManufacturer;
    u8 iProduct;
    u8 iSerialNumber;
    u8 bNumConfigurations;
} USBDeviceDescriptor;

typedef struct USBDeviceInfo {
    IOSFd fd;
    u16 vid;
    u16 pid;
} USBDeviceInfo;

typedef struct USBIsoTransfer {
    void* buf;
    u8 numPackets;
    u16* packets;
} USBIsoTransfer;

typedef struct USBCommandBlock {
    USBCallback callback;        // 0x00
    USBIsoCallback isoCallback;  // 0x04
    void* callbackArg;           // 0x08
    void* isoArg;                // 0x0C

    void* spare;

    void* clean[USB_NCLEAN_MAX];  // 0x14
    u32 nclean;                   // 0x34
    char pad_0x38[0x40 - 0x38];
    union {
        char path[FS_MAX_PATH];
        USBMsg msg;
        USBDeviceDescriptor descriptor;
    };  // 0x40
} USBCommandBlock;

static s32 hId = -1;

static void* lo = NULL;
static void* hi = NULL;

static u8 s_usb_log = FALSE;
static u8 s_usb_err = TRUE;

static void USB_LOG(const char* fmt, ...) {
    va_list list;

    if (s_usb_log) {
        OSReport("USB: ");
        va_start(list, fmt);
        vprintf(fmt, list);
        va_end(list);
    }
}

static void USB_ERR(const char* fmt, ...) {
    va_list list;

    if (s_usb_err) {
        OSReport("USB ERR: ");
        va_start(list, fmt);
        vprintf(fmt, list);
        va_end(list);
    }
}

static void* IOSAlloc(size_t size) {
    void* mem;

    mem = iosAllocAligned(hId, size, DEFAULT_ALIGN);

    if (mem == NULL) {
        USB_ERR("iosAllocAligned(%d, %u) failed: %d\n", hId, size, mem);
    }

    return mem;
}

static void IOSFree(void* mem) {
    s32 result;

    if (mem != NULL) {
        result = iosFree(hId, mem);

        if (result < IPC_RESULT_OK) {
            USB_ERR("iosFree(%d, 0x%x) failed: %d\n", hId, mem, result);
        }
    }
}

IOSError IUSB_OpenLib() {
    IOSError result;
    BOOL enabled;

    result = IPC_RESULT_OK;
    enabled = OSDisableInterrupts();

    if (hId != -1) {
        USB_LOG("Library is already initialized. Heap Id = %d\n", hId);
        goto end;
    }

    if (lo == NULL) {
        lo = IPCGetBufferLo();
        hi = IPCGetBufferHi();

        USB_LOG("iusb size: %d lo: %x hi: %x\n", sizeof(USBCommandBlock), lo, hi);

        if ((u8*)lo + USB_HEAP_SIZE > hi) {
            USB_ERR("Not enough IPC arena\n");
            result = IPC_RESULT_ALLOC_FAILED;
            goto end;
        }

        IPCSetBufferLo((u8*)lo + USB_HEAP_SIZE);
    }

    hId = iosCreateHeap(lo, USB_HEAP_SIZE);
    if (hId < 0) {
        USB_ERR("Not enough heaps\n");
        result = IPC_RESULT_ALLOC_FAILED;
    }

end:
    OSRestoreInterrupts(enabled);
    return result;
}

IOSError IUSB_CloseLib() {
    return IPC_RESULT_OK;
}

static s32 _intrBlkCtrlIsoCb(s32 result, void* arg) {
    int i;
    USBCommandBlock* block = (USBCommandBlock*)arg;

    USB_LOG("_intrBlkCtrlIsoCb returned: %d\n", result);
    USB_LOG("_intrBlkCtrlIsoCb: nclean = %d\n", block->nclean);

    if (block->nclean != USB_NCLEAN_CTRLMSG && block->nclean != USB_NCLEAN_BULKMSG && block->nclean != USB_NCLEAN_CLOSEDEVICE &&
        block->nclean != USB_NCLEAN_4 && block->nclean != USB_NCLEAN_2) {
        USB_ERR("__intrBlkCtrlIsoCb: got invalid nclean\n");
    } else {
        for (i = 0; i < block->nclean; i++) {
            USB_LOG("Freeing clean[%d] = %x\n", i, block->clean[i]);
            IOSFree(block->clean[i]);
        }
        block->nclean = USB_NCLEAN_CLOSEDEVICE;
    }

    USB_LOG("cb = %x cbArg = %x\n", block->callback, block->callbackArg);

    if (block->callback != NULL) {
        block->callback(result, block->callbackArg);
    } else if (block->isoCallback != NULL) {
        USB_LOG("calling iso callback\n");
        block->isoCallback(result, block->isoArg, block->callbackArg);
    }

    IOSFree(block);
    return result;
}

IOSError IUSB_OpenDeviceIds(const char* interface, u16 vid, u16 pid, IOSError* resultOut) {
    IOSError result;
    USBCommandBlock* block;

    block = NULL;

    if (resultOut == NULL) {
        result = IPC_RESULT_INVALID;
        goto end;
    }

    block = IOSAlloc(sizeof(USBCommandBlock));
    if (block == NULL) {
        USB_ERR("OpenDeviceIds: Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    memset(block, 0, sizeof(USBCommandBlock));
    snprintf(block->path, sizeof(block->path), "/dev/usb/%s/%x/%x", interface, vid, pid);
    USB_LOG("OpenDevice - %s\n", block->path);

    result = IOS_Open(block->path, 0);
    USB_LOG("OpenDevice returned: %d\n", result);

    *resultOut = result;

end:
    IOSFree(block);
    return result;
}

IOSError IUSB_OpenDeviceIdsAsync(const char* interface, u16 vid, u16 pid, USBCallback callback, void* callbackArg) {
    IOSError result;
    USBCommandBlock* block;

    USB_LOG("OpenDevice\n");
    block = IOSAlloc(sizeof(USBCommandBlock));
    if (block == NULL) {
        USB_ERR("OpenDeviceIdsAsync: Not enough memory\n");
        return IPC_RESULT_ALLOC_FAILED;
    }

    memset(block, 0, sizeof(USBCommandBlock));
    block->callback = callback;
    block->callbackArg = callbackArg;
    block->nclean = USB_NCLEAN_CLOSEDEVICE;

    snprintf(block->path, sizeof(block->path), "/dev/usb/%s/%x/%x", interface, vid, pid);
    USB_LOG("OpenDevice - %s\n", block->path);
    result = IOS_OpenAsync(block->path, 0, _intrBlkCtrlIsoCb, block);
    USB_LOG("OpenDevice returned: %d\n", result);
    if (result < IPC_RESULT_OK) {
        IOSFree(block);
    }
    return result;
}

static char closeDeviceMessage[] = "CloseDevice\n";
static char closeDeviceResult[] = "CloseDevice returned: %d\n";

IOSError IUSB_CloseDeviceAsync(s32 fd, USBCallback callback, void* callbackArg) {
    IOSError result;
    USBCommandBlock* block;

    USB_LOG(closeDeviceMessage);

    block = IOSAlloc(sizeof(USBCommandBlock));
    if (block == NULL) {
        USB_ERR("CloseDeviceAsync: Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    memset(block, 0, sizeof(USBCommandBlock));

    block->callback = callback;
    block->callbackArg = callbackArg;
    block->nclean = USB_NCLEAN_CLOSEDEVICE;

    result = IOS_CloseAsync(fd, _intrBlkCtrlIsoCb, block);
    USB_LOG(closeDeviceResult, result);

    if (result < 0) {
        IOSFree(block);
    }

end:
    return result;
}

static IOSFd __openDevice(const char* path) {
    IOSFd rv;
    char* pathBuf;
    USBCommandBlock* ctx = IOSAlloc(OSRoundUp32B(sizeof(USBCommandBlock)));

    if (ctx == 0) {
        USB_ERR("openDevice: Not enough memory\n");
        rv = IPC_RESULT_ALLOC_FAILED;
        goto done;
    }

    pathBuf = ctx->path;
    strncpy(pathBuf, path, 64);
    rv = IOS_Open(pathBuf, 0);
    IOSFree(ctx);

done:
    return rv;
}

IOSError IUSB_GetDeviceList(const char* path, USBDeviceInfo* deviceList, u8 maxDev, u8 deviceClass, u8* numDev) {
    IOSError rv = IPC_RESULT_OK;
    IOSIoVector* vector = NULL;
    u8* smaxDev = NULL;
    u8* sclass = NULL;
    u8* snumDev = NULL;
    IOSFd fd;

    if ((u32)deviceList & 0x1f) {
        rv = IPC_RESULT_INVALID;
        goto out;
    }
    fd = __openDevice(path);
    if (fd < 0) {
        rv = fd;
        goto out;
    }

    vector = IOSAlloc(OSRoundUp32B(sizeof(IOSIoVector)) * 4);
    smaxDev = IOSAlloc(OSRoundUp32B(sizeof(u8)));
    sclass = IOSAlloc(OSRoundUp32B(sizeof(u8)));
    snumDev = IOSAlloc(OSRoundUp32B(sizeof(u8)));
    if (NULL == smaxDev || NULL == sclass || NULL == snumDev || NULL == vector) {
        USB_ERR("getDeviceList: Not enough memory\n");
        rv = IPC_RESULT_ALLOC_FAILED;
        goto out;
    }

    *smaxDev = maxDev;
    *sclass = deviceClass;
    *snumDev = 0;

    vector[0].base = smaxDev;
    vector[0].length = sizeof(u8);
    vector[1].base = sclass;
    vector[1].length = sizeof(u8);
    vector[2].base = (u8*)snumDev;
    vector[2].length = sizeof(u8);
    vector[3].base = (u8*)deviceList;
    vector[3].length = sizeof(USBDeviceInfo) * maxDev;

    DCInvalidateRange(deviceList, sizeof(USBDeviceInfo) * maxDev);
    DCInvalidateRange(snumDev, OSRoundUp32B(sizeof(u8)));
    DCFlushRange(sclass, OSRoundUp32B(sizeof(u8)));
    DCFlushRange(smaxDev, OSRoundUp32B(sizeof(u8)));
    DCFlushRange(vector, OSRoundUp32B(sizeof(IOSIoVector)) * 4);

    rv = IOS_Ioctlv(fd, 12, 2, 2, vector);
    *numDev = *snumDev;
    IOS_Close(fd);

out:
    IOSFree(snumDev);
    IOSFree(smaxDev);
    IOSFree(sclass);
    IOSFree(vector);
    return rv;
}

IOSError __IntrBlkMsgInt(s32 fd, u32 endpoint, u32 length, void* buffer, u8 ioctl, USBCallback callback, void* callbackArg, u8 async) {
    IOSError result;
    IOSIoVector* vectors;
    u8* endpointWork;
    u16* lengthWork;
    USBCommandBlock* block;

    vectors = (IOSIoVector*)IOSAlloc(0x60);
    endpointWork = (u8*)IOSAlloc(DEFAULT_ALIGN);
    lengthWork = (u16*)IOSAlloc(DEFAULT_ALIGN);

    if (vectors == NULL || endpointWork == NULL || lengthWork == NULL) {
        USB_ERR("__IntrBlkMsgInt: Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    *endpointWork = (u8)endpoint;
    *lengthWork = (u16)length;

    // Input vector 1: Transfer endpoint
    vectors[0].base = endpointWork;
    vectors[0].length = sizeof(u8);

    // Input vector 2: Transfer length
    vectors[1].base = (u8*)lengthWork;
    vectors[1].length = sizeof(u16);

    // Output vector 1: Transfer buffer
    vectors[2].base = buffer;
    vectors[2].length = length;

    DCFlushRange(endpointWork, DEFAULT_ALIGN);
    DCFlushRange(lengthWork, DEFAULT_ALIGN);
    DCFlushRange(vectors, 0x60);

    if (!async) {
        result = IOS_Ioctlv(fd, ioctl, 2, 1, vectors);
        USB_LOG("intr/blk ioctl returned: %d\n", result);
        goto end;
    }

    block = IOSAlloc(sizeof(USBCommandBlock));
    if (block == NULL) {
        USB_ERR("IntBlkMsgInt (async): Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    memset(block, 0, sizeof(USBCommandBlock));

    block->callback = callback;
    block->callbackArg = callbackArg;
    USB_LOG("intrblkmsg: cb = 0x%x cbArg = 0x%x\n", block->callback, block->callbackArg);

    // Mark memory for deletion
    block->nclean = USB_NCLEAN_BULKMSG;
    block->clean[0] = endpointWork;
    block->clean[1] = lengthWork;
    block->clean[2] = vectors;

    block->msg.buffer = buffer;
    block->msg.length = length;

    result = IOS_IoctlvAsync(fd, ioctl, 2, 1, vectors, _intrBlkCtrlIsoCb, block);
    if (result >= IPC_RESULT_OK) {
        goto end_async;
    }

    IOSFree(block);

// Non-async (or unsuccessful async) means we must manually free memory
end:
    IOSFree(endpointWork);
    IOSFree(lengthWork);
    IOSFree(vectors);

// Async callback automatically freed the memory marked in block->clean
end_async:
    return result;
}

IOSError IUSB_ReadIntrMsgAsync(s32 fd, u32 endpoint, u32 length, void* buffer, USBCallback callback, void* callbackArg) {
    DCInvalidateRange(buffer, length);
    return __IntrBlkMsgInt(fd, endpoint, length, buffer, USB_IOCTLV_INTRMSG, callback, callbackArg, TRUE);
}

IOSError IUSB_ReadBlkMsgAsync(s32 fd, u32 endpoint, u32 length, void* buffer, USBCallback callback, void* callbackArg) {
    DCInvalidateRange(buffer, length);
    return __IntrBlkMsgInt(fd, endpoint, length, buffer, USB_IOCTLV_BLKMSG, callback, callbackArg, TRUE);
}

IOSError IUSB_WriteBlkMsgAsync(s32 fd, u32 endpoint, u32 length, const void* buffer, USBCallback callback, void* callbackArg) {
    DCFlushRange((void*)buffer, length);
    return __IntrBlkMsgInt(fd, endpoint, length, (void*)buffer, USB_IOCTLV_BLKMSG, callback, callbackArg, TRUE);
}

static IOSError __CtrlMsgInt(s32 fd, u8 requestType, u8 request, u16 value, u16 index, u16 length, void* buffer, USBCallback callback,
                             void* callbackArg, u8 async) {
    IOSError result;
    IOSIoVector* vectors;
    u8* requestTypeWork;
    u8* requestWork;
    u8* controlOptionsWork;
    u16* valueWork;
    u16* indexWork;
    u16* lengthWork;
    USBCommandBlock* block;

    if ((buffer == NULL && length != 0) || (u32)buffer % DEFAULT_ALIGN != 0) {
        result = IPC_RESULT_INVALID;
        USB_ERR("ctrlmsg: bad data buffer\n");
        goto end_async;
    }

    vectors = (IOSIoVector*)IOSAlloc(0xE0);
    requestTypeWork = (u8*)IOSAlloc(DEFAULT_ALIGN);
    requestWork = (u8*)IOSAlloc(DEFAULT_ALIGN);
    controlOptionsWork = (u8*)IOSAlloc(DEFAULT_ALIGN);
    valueWork = (u16*)IOSAlloc(DEFAULT_ALIGN);
    indexWork = (u16*)IOSAlloc(DEFAULT_ALIGN);
    lengthWork = (u16*)IOSAlloc(DEFAULT_ALIGN);

    if (requestTypeWork == NULL || requestWork == NULL || controlOptionsWork == NULL || valueWork == NULL || indexWork == NULL || lengthWork == NULL ||
        vectors == NULL) {
        USB_ERR("Ctrl Msg: Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    *requestTypeWork = requestType;
    *requestWork = request;
    *valueWork = (value & 0xFF) << 8 | value >> 8 & 0xFF;
    *indexWork = (index & 0xFF) << 8 | index >> 8 & 0xFF;
    *lengthWork = (length & 0xFF) << 8 | length >> 8 & 0xFF;
    *controlOptionsWork = 0;

    // Input vector 1: bmRequestType
    vectors[0].base = requestTypeWork;
    vectors[0].length = sizeof(u8);

    // Input vector 2: bmRequest
    vectors[1].base = requestWork;
    vectors[1].length = sizeof(u8);

    // Input vector 3: wValue
    vectors[2].base = (u8*)valueWork;
    vectors[2].length = sizeof(u16);

    // Input vector 4: wIndex
    vectors[3].base = (u8*)indexWork;
    vectors[3].length = sizeof(u16);

    // Input vector 5: wLength
    vectors[4].base = (u8*)lengthWork;
    vectors[4].length = sizeof(u16);

    // Input vector 6: Unknown data
    vectors[5].base = controlOptionsWork;
    vectors[5].length = sizeof(u8);

    // Output vector 1: Transfer buffer
    vectors[6].base = buffer;
    vectors[6].length = length;

    DCFlushRange(requestTypeWork, DEFAULT_ALIGN);
    DCFlushRange(requestWork, DEFAULT_ALIGN);
    DCFlushRange(controlOptionsWork, DEFAULT_ALIGN);
    DCFlushRange(valueWork, DEFAULT_ALIGN);
    DCFlushRange(indexWork, DEFAULT_ALIGN);
    DCFlushRange(lengthWork, DEFAULT_ALIGN);
    DCFlushRange(vectors, 0xE0);

    if (!async) {
        result = IOS_Ioctlv(fd, USB_IOCTLV_CTRLMSG, 6, 1, vectors);
        goto end;
    }

    block = IOSAlloc(sizeof(USBCommandBlock));
    if (block == NULL) {
        USB_ERR("CtrlMsgInt (async): Not enough memory\n");
        result = IPC_RESULT_ALLOC_FAILED;
        goto end;
    }

    memset(block, 0, sizeof(USBCommandBlock));

    block->callback = callback;
    block->callbackArg = callbackArg;
    USB_LOG("ctrlmsgint: cb = 0x%x cbArg = 0x%x\n", block->callback, block->callbackArg);

    // Mark memory for deletion
    block->nclean = USB_NCLEAN_CTRLMSG;
    block->clean[0] = requestTypeWork;
    block->clean[1] = requestWork;
    block->clean[2] = valueWork;
    block->clean[3] = indexWork;
    block->clean[4] = lengthWork;
    block->clean[5] = controlOptionsWork;
    block->clean[6] = vectors;

    block->msg.buffer = buffer;
    block->msg.length = length;

    result = IOS_IoctlvAsync(fd, USB_IOCTLV_CTRLMSG, 6, 1, vectors, _intrBlkCtrlIsoCb, block);
    USB_LOG("Ctrl Msg async returned: %d\n", result);

    if (result >= IPC_RESULT_OK) {
        goto end_async;
    }

    IOSFree(block);

// Non-async (or unsuccessful async) means we must manually free memory
end:
    IOSFree(requestTypeWork);
    IOSFree(requestWork);
    IOSFree(valueWork);
    IOSFree(indexWork);
    IOSFree(lengthWork);
    IOSFree(controlOptionsWork);
    IOSFree(vectors);

// Async callback automatically freed the memory marked in block->clean
end_async:
    return result;
}

IOSError IUSB_ReadCtrlMsgAsync(IOSFd fd, u8 reqType, u8 request, u16 value, u16 index, u16 buflen, char* buf, USBCallback cb, void* cbArg) {
    DCInvalidateRange(buf, buflen);
    return __CtrlMsgInt(fd, reqType, request, value, index, buflen, buf, cb, cbArg, 1);
}

IOSError IUSB_WriteCtrlMsgAsync(s32 fd, u8 requestType, u8 request, u16 value, u16 index, u16 length, void* buffer, USBCallback callback,
                                void* callbackArg) {
    DCFlushRange(buffer, length);
    return __CtrlMsgInt(fd, requestType, request, value, index, length, buffer, callback, callbackArg, TRUE);
}

static s8 unicode2ascii(char* tbuf, int buflen) {
    char buf[128];
    s8 di, si;

    if (tbuf[1] != 0x03) {
        di = -1;
        goto out;
    }

    for (di = 0, si = 2; si < tbuf[0] && si < buflen; si += 2) {
        if (di >= (sizeof(buf) - 1))
            break;
        if (tbuf[si + 1])
            buf[di++] = '?';
        else
            buf[di++] = tbuf[si];
    }

    buf[di] = 0;
    memcpy(tbuf, buf, (u32)di);

out:
    return di;
}

static void _GetStrCb(IOSError ret, void* ctxt) {
    IOSError rv = ret;
    USBCommandBlock* req = (USBCommandBlock*)ctxt;
    char* buf;
    u16 buflen;
    s8 len;

    USB_LOG("GetStrCb returned: %d\n", rv);
    if (rv <= 0)
        goto out;

    buf = (char*)req->msg.buffer;
    buflen = req->msg.length;
    USB_LOG("GetStrCb: buf = 0x%x buflen = %u\n", buf, buflen);
    len = unicode2ascii(buf, buflen);
    if (len < 0)
        USB_ERR("Failed to convert buffer from unicode 2 ascii\n");
    else
        buf[len] = '\0';

out:
    if (req->callback) {
        USB_LOG("calling cb 0x%x with arg 0x%x\n", req->callback, req->callbackArg);
        req->callback(ret, req->callbackArg);
    }
    IOSFree(req);
    return;
}

IOSError IUSB_GetAsciiStr(IOSFd fd, u8 ep, u16 index, u16 langId, char* buf, u16 buflen) {
    IOSError rv = IPC_RESULT_OK;
    s8 len;

    USB_LOG("GetStr\n");

    DCInvalidateRange(buf, (u32)buflen);
    rv = __CtrlMsgInt(fd, 0x80, 0x06, (u16)((0x03 << 8) + index), langId, buflen, buf, NULL, NULL, 0);
    if (rv <= 0) {
        USB_ERR("Failed __CtrlMsg: %d", rv);
        goto out;
    }
    len = unicode2ascii(buf, buflen);
    if (len < 0)
        USB_ERR("Failed to convert unicode 2 ascii\n");
    else
        buf[len] = '\0';

out:
    return rv;
}

IOSError IUSB_GetAsciiStrAsync(IOSFd fd, u8 ep, u16 index, u16 langId, char* buf, u16 buflen, USBCallback cb, void* cbArg) {
    IOSError rv = IPC_RESULT_OK;
    USBCommandBlock* req;

    USB_LOG("GetStr - _GetStrCb\n");
    req = IOSAlloc(OSRoundUp32B(sizeof(*req)));
    if (req == 0) {
        USB_ERR(" GetAsciiStrAsync: Not enough memory\n");
        rv = IPC_RESULT_ALLOC_FAILED;
        goto out;
    }

    memset(req, 0, sizeof(USBCommandBlock));

    req->callback = cb;
    req->callbackArg = cbArg;
    req->nclean = 0;
    req->msg.buffer = buf;
    req->msg.length = buflen;
    DCInvalidateRange(buf, buflen);
    rv = __CtrlMsgInt(fd, 0x80, 0x06, (u16)((0x03 << 8) + index), langId, buflen, buf, _GetStrCb, req, 1);
    if (rv < 0) {
        USB_ERR("__CtrlMsgInt failed %d\n", rv);
        IOSFree(req);
        goto out;
    }

out:
    return rv;
}

static void _GetDescrCb(IOSError ret, void* ctxt) {
    IOSError rv = ret;
    USBCommandBlock* req = (USBCommandBlock*)ctxt;

    USB_LOG("GetDescrCb returned: %d\n", rv);
    if (rv <= 0)
        goto out;

    *(USBDeviceDescriptor*)req->spare = req->descriptor;

out:
    if (req->callback)
        req->callback(ret, req->callbackArg);
    IOSFree(req);
    return;
}

IOSError IUSB_GetDevDescr(IOSFd fd, USBDeviceDescriptor* des) {
    IOSError rv = IPC_RESULT_OK;
    USBCommandBlock* req = 0;

    USB_LOG("GetDevDescr\n");
    req = IOSAlloc(OSRoundUp32B(sizeof(*req)));
    if (req == 0) {
        USB_ERR("GetDevDescr: Not enough memory\n");
        rv = IPC_RESULT_ALLOC_FAILED;
        goto out;
    }

    memset(req, 0, sizeof(USBCommandBlock));
    DCInvalidateRange(&req->descriptor, (u32)sizeof(*des));
    rv = __CtrlMsgInt(fd, 0x80, 0x06, 0x100, 0, sizeof(*des), &req->descriptor, NULL, NULL, 0);
    if (rv < 0) {
        USB_ERR("Failed __CtrlMsg: %d", rv);
        goto out;
    }
    USB_LOG("GetDevDescr: %d\n", rv);
    *des = req->descriptor;

out:
    IOSFree(req);
    return rv;
}

IOSError IUSB_GetDevDescrAsync(IOSFd fd, USBDeviceDescriptor* des, USBCallback cb, void* cbArg) {
    IOSError rv = IPC_RESULT_OK;
    USBCommandBlock* req;

    USB_LOG("GetDevDescr - _GetDescrCb\n");
    req = IOSAlloc(OSRoundUp32B(sizeof(*req)));
    if (req == 0) {
        USB_ERR("GetDevDescrAsync: Not enough memory\n");
        rv = IPC_RESULT_ALLOC_FAILED;
        goto out;
    }

    memset(req, 0, sizeof(USBCommandBlock));

    req->callback = cb;
    req->callbackArg = cbArg;
    req->nclean = 0;
    req->spare = des;

    rv = IUSB_ReadCtrlMsgAsync(fd, 0x80, 0x06, 0x100, 0, sizeof(*des), (char*)&req->descriptor, _GetDescrCb, req);
    if (rv < 0) {
        IOSFree(req);
        goto out;
    }

out:
    return rv;
}

IOSError IUSB_DeviceRemovalNotifyAsync(IOSFd fd, IOSIpcCb cb, void* cbArg) {
    IOSError rv;

    USB_LOG("DeviceRemovalNotifyAsync\n");
    rv = IOS_IoctlAsync(fd, 26, 0, 0, 0, 0, cb, cbArg);
    return rv;
}

static IOSError __checkIsoArgs(USBIsoTransfer* xfer, u16* buflen) {
    IOSError rv = IPC_RESULT_INVALID;

    if (NULL == xfer || NULL == xfer->buf || 0 == xfer->numPackets || xfer->numPackets > 8 || NULL == xfer->packets) {
        goto out;
    }
    {
        u32 i;
        *buflen = 0;
        for (i = 0; i < xfer->numPackets; ++i) {
            if (xfer->packets[i] > 1023) {
                USB_ERR("packet %u too big: %u\n", i, xfer->packets[i]);
                goto out;
            }
            *buflen += xfer->packets[i];
        }
    }
    rv = IPC_RESULT_OK;

out:
    return rv;
}

IOSError IUSB_IsoMsgAsync(IOSFd fd, u8 ep, USBIsoTransfer* xfer, USBIsoCallback cb, void* cbArg) {
    IOSError rv = IPC_RESULT_OK;
    u8 *sep, *snumPackets;
    u16* sbuflen;
    IOSIoVector* vector;
    USBCommandBlock* req;
    u16 buflen;

    if (0 == ep || NULL == cb || (__checkIsoArgs(xfer, &buflen) < 0)) {
        USB_ERR("Invalid parameters for ISO transfer request\n");
        rv = IPC_RESULT_INVALID;
        goto out;
    }

    vector = IOSAlloc(OSRoundUp32B(sizeof(IOSIoVector)) * 5);
    sep = IOSAlloc(OSRoundUp32B(sizeof(u8)));
    sbuflen = IOSAlloc(OSRoundUp32B(sizeof(u16)));
    snumPackets = IOSAlloc(OSRoundUp32B(sizeof(u8)));
    req = IOSAlloc(OSRoundUp32B(sizeof(*req)));
    if (NULL == vector || NULL == sep || NULL == sbuflen || NULL == req) {
        USB_ERR("IUSB_IsoMsgAsync: Not enough memory\n");
        rv = IPC_RESULT_ALLOC_FAILED;
        IOSFree(req);
        goto clean;
    }

    memset(req, 0, sizeof(USBCommandBlock));
    *sep = ep;
    *sbuflen = buflen;
    *snumPackets = xfer->numPackets;

    vector[0].base = (u8*)sep;
    vector[0].length = sizeof(u8);
    vector[1].base = (u8*)sbuflen;
    vector[1].length = sizeof(u16);
    vector[2].base = snumPackets;
    vector[2].length = sizeof(u8);
    vector[3].base = (u8*)xfer->packets;
    vector[3].length = sizeof(u16) * xfer->numPackets;
    vector[4].base = xfer->buf;
    vector[4].length = buflen;

    DCFlushRange(sep, OSRoundUp32B(sizeof(u8)));
    DCFlushRange(sbuflen, OSRoundUp32B(sizeof(u16)));
    DCFlushRange(snumPackets, OSRoundUp32B(sizeof(u8)));
    DCFlushRange(vector, OSRoundUp32B(sizeof(IOSIoVector)) * 5);

    req->isoCallback = cb;
    req->isoArg = xfer;
    req->callbackArg = cbArg;
    req->nclean = 4;
    req->clean[0] = sep;
    req->clean[1] = sbuflen;
    req->clean[2] = snumPackets;
    req->clean[3] = vector;

    rv = IOS_IoctlvAsync(fd, 9, 3, 2, vector, _intrBlkCtrlIsoCb, req);
    if (rv < 0) {
        IOSFree(req);
        goto clean;
    }
    goto out;

clean:
    IOSFree(sep);
    IOSFree(sbuflen);
    IOSFree(snumPackets);
    IOSFree(vector);

out:
    return rv;
}

IOSError IUSB_DeviceInsertionNotifyAsync(const char* path, u16 vid, u16 pid, USBCallback cb, void* cbArg) {
    IOSError rv;
    IOSFd fd;
    IOSIoVector* vector;
    u16 *svid, *spid;
    USBCommandBlock* req;

    if (NULL == path || 0 == vid || 0 == pid) {
        rv = IPC_RESULT_INVALID;
        goto done;
    }
    fd = IOS_Open(path, 0);
    if (fd < 0) {
        rv = fd;
        USB_ERR("Open(%s) failed\n", path);
        goto done;
    }

    vector = IOSAlloc(OSRoundUp32B(sizeof(IOSIoVector)) * 2);
    spid = IOSAlloc(OSRoundUp32B(sizeof(u16)));
    svid = IOSAlloc(OSRoundUp32B(sizeof(u16)));
    req = IOSAlloc(OSRoundUp32B(sizeof(*req)));
    if (NULL == vector || NULL == spid || NULL == svid || NULL == req) {
        USB_ERR("getDeviceList: Not enough memory\n");
        rv = IPC_RESULT_ALLOC_FAILED;
        goto clean;
    }

    memset(req, 0, sizeof(USBCommandBlock));
    *svid = vid;
    *spid = pid;

    vector[0].base = (u8*)svid;
    vector[0].length = sizeof(u16);
    vector[1].base = (u8*)spid;
    vector[1].length = sizeof(u16);
    DCFlushRange(svid, OSRoundUp32B(sizeof(u16)));
    DCFlushRange(spid, OSRoundUp32B(sizeof(u16)));
    DCFlushRange(vector, OSRoundUp32B(sizeof(IOSIoVector)) * 2);
    req->callback = cb;
    req->callbackArg = cbArg;
    req->nclean = 3;
    req->clean[0] = svid;
    req->clean[1] = spid;
    req->clean[2] = vector;

    rv = IOS_IoctlvAsync(fd, 27, 2, 0, vector, _intrBlkCtrlIsoCb, req);
    if (rv < 0) {
        goto clean;
    }
    IOS_Close(fd);
    goto done;

clean:
    IOSFree(svid);
    IOSFree(spid);
    IOSFree(vector);
    IOSFree(req);

done:
    return rv;
}

IOSError IUSB_DeviceClassInsertionNotifyAsync(const char* path, u8 devClass, USBCallback cb, void* cbArg) {
    IOSError rv;
    IOSFd fd;
    IOSIoVector* vector;
    u8* sdevClass;
    USBCommandBlock* req;

    if (NULL == path || 0 == devClass) {
        OSReport("Invalid path or devClass in insertion notification call\n");
        rv = IPC_RESULT_INVALID;
        goto done;
    }
    fd = IOS_Open(path, 0);
    if (fd < 0) {
        rv = fd;
        OSReport("Open(%s) failed\n", path);
        goto done;
    }

    vector = IOSAlloc(OSRoundUp32B(sizeof(IOSIoVector)) * 2);
    sdevClass = IOSAlloc(OSRoundUp32B(sizeof(u8)));
    req = IOSAlloc(OSRoundUp32B(sizeof(*req)));
    *sdevClass = devClass;

    vector[0].base = (u8*)sdevClass;
    vector[0].length = sizeof(u8);
    DCFlushRange(sdevClass, OSRoundUp32B(sizeof(u8)));
    DCFlushRange(vector, OSRoundUp32B(sizeof(IOSIoVector)) * 2);
    req->callback = cb;
    req->callbackArg = cbArg;
    req->nclean = 2;
    req->clean[0] = sdevClass;
    req->clean[1] = vector;

    rv = IOS_IoctlvAsync(fd, 28, 1, 0, vector, _intrBlkCtrlIsoCb, req);
    IOS_Close(fd);

done:
    return rv;
}
