#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <test_stubs.h>
#ifndef USB_SOURCE
#define USB_SOURCE "../../../libs/RVL_SDK/src/usb/usb.c"
#endif
#include USB_SOURCE

static void* active[32];
static int live, allocation_count, fail_allocation, opens, closes, calls;
static int open_result, submit_result, sync_result, immediate, completion_result;
static IOSIpcCb pending_cb;
static void* pending_arg;
static int ordinary_calls, iso_calls, expected_command;
static USBIsoTransfer* expected_xfer;
static int callback_cookie;

static void reset(void) {
    assert(live == 0 && pending_cb == NULL);
    assert(opens == closes);
    memset(active, 0, sizeof(active));
    allocation_count = fail_allocation = opens = closes = calls = 0;
    ordinary_calls = iso_calls = 0;
    open_result = 7;
    submit_result = sync_result = immediate = 0;
    completion_result = -17;
    expected_command = -1;
    expected_xfer = NULL;
    s_usb_err = s_usb_log = FALSE;
}

void* iosAllocAligned(IOSHeapId heap, u32 size, u32 alignment) {
    (void)heap;
    if (++allocation_count == fail_allocation) return NULL;
    void* ptr = aligned_alloc(alignment, (size + alignment - 1) & ~(alignment - 1));
    assert(ptr != NULL);
    memset(ptr, 0xa5, size);
    for (int i = 0; i < 32; ++i) if (!active[i]) {
        active[i] = ptr;
        ++live;
        return ptr;
    }
    abort();
}
IOSError iosFree(IOSHeapId heap, void* ptr) {
    (void)heap;
    for (int i = 0; i < 32; ++i) if (active[i] == ptr) {
        active[i] = NULL;
        --live;
        free(ptr);
        return 0;
    }
    assert(!"free of unowned or already freed allocation");
    return -1;
}
IOSError IOS_Open(const char* path, u32 flags) {
    assert(path != NULL && flags == 0);
    if (open_result >= 0) ++opens;
    return open_result;
}
IOSError IOS_Close(IOSFd fd) {
    assert(fd == open_result && closes < opens);
    ++closes;
    return 0;
}
static void finish(void) {
    IOSIpcCb cb = pending_cb;
    void* arg = pending_arg;
    assert(cb != NULL);
    pending_cb = NULL;
    pending_arg = NULL;
    assert(cb(completion_result, arg) == completion_result);
}
IOSError IOS_IoctlvAsync(IOSFd fd, s32 cmd, u32 reads, u32 writes, IOSIoVector* vec, IOSIpcCb cb, void* arg) {
    assert(fd == 7 && cb != NULL && arg != NULL && pending_cb == NULL);
    assert(cmd == expected_command);
    ++calls;
    if (cmd == 9) {
        assert(reads == 3 && writes == 2);
        assert(*vec[0].base == 0x81 && *(u16*)vec[1].base == 5 && *vec[2].base == 2);
        assert(vec[3].base == (u8*)expected_xfer->packets && vec[4].base == expected_xfer->buf);
    } else if (cmd == 27) {
        assert(reads == 2 && writes == 0);
        assert(*(u16*)vec[0].base == 0x1234 && *(u16*)vec[1].base == 0x5678);
    } else if (cmd == 28) {
        assert(reads == 1 && writes == 0 && *vec[0].base == 3);
    }
    if (submit_result < 0) return submit_result;
    pending_cb = cb;
    pending_arg = arg;
    if (immediate) finish();
    return submit_result;
}
IOSError IOS_Ioctlv(IOSFd fd, s32 cmd, u32 reads, u32 writes, IOSIoVector* vec) {
    assert(fd == 7);
    ++calls;
    if (cmd == 12) {
        assert(reads == 2 && writes == 2);
        assert(*vec[0].base == 1 && *vec[1].base == 3);
        *vec[2].base = 1;
    } else {
        assert(cmd == 0 && reads == 6 && writes == 1);
    }
    return sync_result;
}
static void ordinary(IOSError result, void* arg) {
    assert(result == completion_result && arg == &callback_cookie);
    ++ordinary_calls;
}
static void iso(IOSError result, void* xfer, void* arg) {
    assert(result == completion_result && xfer == expected_xfer && arg == &callback_cookie);
    ++iso_calls;
}
void OSReport(const char* fmt, ...) { (void)fmt; }
BOOL OSDisableInterrupts(void) { return TRUE; }
void OSRestoreInterrupts(BOOL b) { (void)b; }
void DCFlushRange(void* p, u32 n) { (void)p; (void)n; }
void DCInvalidateRange(void* p, u32 n) { (void)p; (void)n; }
void* IPCGetBufferLo(void) { return NULL; }
void* IPCGetBufferHi(void) { return NULL; }
void IPCSetBufferLo(void* p) { (void)p; }
IOSHeapId iosCreateHeap(void* p, u32 n) { (void)p; (void)n; return 0; }
IOSError IOS_OpenAsync(const char* p, u32 f, IOSIpcCb cb, void* a) { abort(); }
IOSError IOS_CloseAsync(IOSFd f, IOSIpcCb cb, void* a) { abort(); }
IOSError IOS_IoctlAsync(IOSFd f, s32 c, void* i, u32 il, void* o, u32 ol, IOSIpcCb cb, void* a) { abort(); }

static void test_iso(void) {
    u8 buffer[32] = {0};
    u16 packets[2] = {2, 3};
    USBIsoTransfer xfer = {buffer, 2, packets};
    for (int fail = 1; fail <= 5; ++fail) {
        reset(); fail_allocation = fail; expected_command = 9; expected_xfer = &xfer;
        assert(IUSB_IsoMsgAsync(7, 0x81, &xfer, iso, &callback_cookie) == IPC_RESULT_ALLOC_FAILED);
        assert(live == 0 && calls == 0 && iso_calls == 0);
    }
    reset(); expected_command = 9; expected_xfer = &xfer; submit_result = -88;
    assert(IUSB_IsoMsgAsync(7, 0x81, &xfer, iso, &callback_cookie) == -88);
    assert(live == 0 && calls == 1 && iso_calls == 0);
    for (int now = 0; now <= 1; ++now) for (int status = 0; status <= 1; ++status) {
        reset(); expected_command = 9; expected_xfer = &xfer; immediate = now; completion_result = status ? 5 : -17;
        assert(IUSB_IsoMsgAsync(7, 0x81, &xfer, iso, &callback_cookie) == 0);
        assert(live == (now ? 0 : 5));
        if (!now) finish();
        assert(live == 0 && iso_calls == 1 && ordinary_calls == 0);
    }
    reset();
    assert(IUSB_IsoMsgAsync(7, 0, &xfer, iso, NULL) == IPC_RESULT_INVALID);
    assert(IUSB_IsoMsgAsync(7, 0x81, NULL, iso, NULL) == IPC_RESULT_INVALID);
    assert(IUSB_IsoMsgAsync(7, 0x81, &xfer, NULL, NULL) == IPC_RESULT_INVALID);
    assert(allocation_count == 0);
}
static IOSError insertion(int cls, USBCallback cb) {
    return cls ? IUSB_DeviceClassInsertionNotifyAsync("/dev/usb/oh0", 3, cb, &callback_cookie)
               : IUSB_DeviceInsertionNotifyAsync("/dev/usb/oh0", 0x1234, 0x5678, cb, &callback_cookie);
}
static void test_insertion(int cls) {
    int allocations = cls ? 3 : 4;
    for (int fail = 1; fail <= allocations; ++fail) {
        reset(); fail_allocation = fail; expected_command = cls ? 28 : 27;
        assert(insertion(cls, ordinary) == IPC_RESULT_ALLOC_FAILED);
        assert(live == 0 && opens == 1 && closes == 1 && calls == 0 && ordinary_calls == 0);
    }
    reset(); expected_command = cls ? 28 : 27; submit_result = -88;
    assert(insertion(cls, ordinary) == -88);
    assert(live == 0 && opens == 1 && closes == 1 && calls == 1 && ordinary_calls == 0);
    for (int now = 0; now <= 1; ++now) for (int null_cb = 0; null_cb <= 1; ++null_cb) for (int status = 0; status <= 1; ++status) {
        reset(); expected_command = cls ? 28 : 27; immediate = now; completion_result = status ? 0 : -17;
        assert(insertion(cls, null_cb ? NULL : ordinary) == 0);
        assert(live == (now ? 0 : allocations) && opens == 1 && closes == 1);
        if (!now) finish();
        assert(live == 0 && ordinary_calls == !null_cb && iso_calls == 0);
    }
    reset(); open_result = -99;
    assert(insertion(cls, ordinary) == -99);
    assert(allocation_count == 0 && opens == 0 && closes == 0);
}
static void test_device_list(void) {
    _Alignas(32) USBDeviceInfo device;
    u8 count = 77;
    for (int fail = 1; fail <= 5; ++fail) {
        reset(); fail_allocation = fail;
        assert(IUSB_GetDeviceList("/dev/usb/oh0", &device, 1, 3, &count) == IPC_RESULT_ALLOC_FAILED);
        assert(live == 0 && calls == 0 && opens == (fail != 1) && closes == opens && count == 77);
    }
    for (int result = 0; result <= 1; ++result) {
        reset(); sync_result = result ? 0 : -88;
        assert(IUSB_GetDeviceList("/dev/usb/oh0", &device, 1, 3, &count) == sync_result);
        assert(live == 0 && calls == 1 && opens == 1 && closes == 1 && count == 1);
    }
    reset(); open_result = -99;
    assert(IUSB_GetDeviceList("/dev/usb/oh0", &device, 1, 3, &count) == -99);
    assert(live == 0 && opens == 0 && closes == 0 && calls == 0);
}
static void test_unicode(void) {
    for (int size = 0; size <= 260; ++size) for (int declared = 0; declared <= 255; ++declared) {
        char* buf = malloc(size ? (size_t)size : 1);
        assert(buf != NULL);
        memset(buf, 0, size ? (size_t)size : 1);
        if (size) buf[0] = (char)declared;
        if (size > 1) buf[1] = 3;
        for (int i = 2; i < size; ++i) buf[i] = (i % 2) ? (i % 7 == 0) : (char)('a' + i % 26);
        int limit = declared < size ? declared : size;
        int want = limit < 2 ? -1 : (limit - 2) / 2;
        char expected[128];
        for (int i = 0; i < want; ++i) expected[i] = buf[3 + i * 2] ? '?' : buf[2 + i * 2];
        assert(unicode2ascii(buf, size) == want);
        if (want > 0) assert(memcmp(buf, expected, (size_t)want) == 0);
        free(buf);
    }
    assert(unicode2ascii(NULL, 0) == -1);
    assert(unicode2ascii(NULL, 2) == -1);
    char wrong_type[2] = {2, 1};
    assert(unicode2ascii(wrong_type, 2) == -1);
    assert(unicode2ascii(wrong_type, -1) == -1);
}
static void test_string_wrappers(void) {
    for (int returned = 1; returned <= 8; ++returned) {
        for (int mode = 0; mode <= 1; ++mode) {
            reset();
            _Alignas(32) char buf[8] = {8, 3, 'a', 0, 'b', 0, 'c', 0};
            sync_result = completion_result = returned;
            if (!mode) {
                assert(IUSB_GetAsciiStr(7, 0, 1, 0, buf, sizeof(buf)) == returned);
            } else {
                USBCommandBlock* req = IOSAlloc(sizeof(*req));
                memset(req, 0, sizeof(*req));
                req->msg.buffer = buf;
                req->msg.length = sizeof(buf);
                req->callback = ordinary;
                req->callbackArg = &callback_cookie;
                _GetStrCb(returned, req);
                assert(ordinary_calls == 1);
            }
            if (returned == 1) assert(buf[0] == 8 && buf[1] == 3);
            else {
                int chars = (returned - 2) / 2;
                assert(buf[chars] == '\0');
                for (int i = 0; i < chars; ++i) assert(buf[i] == 'a' + i);
            }
            assert(live == 0);
        }
    }
}
int main(int argc, char** argv) {
    const char* test = argc == 2 ? argv[1] : "all";
    if (!strcmp(test, "iso") || !strcmp(test, "all")) test_iso();
    if (!strcmp(test, "insertion") || !strcmp(test, "all")) test_insertion(0);
    if (!strcmp(test, "class") || !strcmp(test, "all")) test_insertion(1);
    if (!strcmp(test, "list") || !strcmp(test, "all")) test_device_list();
    if (!strcmp(test, "unicode") || !strcmp(test, "all")) test_unicode();
    if (!strcmp(test, "wrappers") || !strcmp(test, "all")) test_string_wrappers();
    reset();
    printf("PASS: %s (allocation failures, callback ownership, descriptor cleanup, string boundaries)\n", test);
    return 0;
}
