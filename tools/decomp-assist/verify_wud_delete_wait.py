#!/usr/bin/env python3
"""Exercise the WUD deletion wait with real source and a host interrupt model.

This is a bounded regression test, not Wii hardware or full Bluetooth emulation.
The alarm dispatches only when interrupts are restored, never inside a protected
read. The tested deletion/cleanup functions are extracted verbatim from WUD.c.
"""

import argparse
from pathlib import Path
import re
import subprocess
import tempfile


FUNCTIONS = (
    "DeleteFlushCallback", "WUDiCleanUp", "WUDiDeleteAllComplete",
    "DeleteAllHandler", "WUDStartClearDevice", "WUDiDeleteAllLinkKeys",
    "WUDIsBusy", "_WUDDeleteStoredDevice",
)


def function(source, name):
    match = re.search(r"^(?:static )?\w+ " + name + r"\([^\n]*\) \{", source, re.M)
    assert match, name
    start = match.start()
    depth = 1
    at = match.end()
    while depth:
        depth += (source[at] == "{") - (source[at] == "}")
        at += 1
    return source[start:at]


PRELUDE = r'''
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef int BOOL;
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef int SCStatus;
typedef int WUDDeleteState;
typedef void (*WUDClearDeviceCallback)(s32);
typedef char SCBtDeviceInfoArray[4];
typedef char SCBtCmpDevInfoArray[4];
typedef struct {
    u8 syncState, deleteState, stackState, initState;
    u32 libStatus;
    int alarm;
    WUDClearDeviceCallback clearDevCB;
} WUDCB;
enum { FALSE, TRUE };
enum { WUD_STATE_DELETE_START = 0, WUD_STATE_DELETE_DISALLOW_INCOMING = 1,
       WUD_STATE_DELETE_DISCONNECT_ALL = 2, WUD_STATE_DELETE_CLEANUP_DATABASE = 3,
       WUD_STATE_DELETE_CLEANUP_SETTING = 5, WUD_STATE_DELETE_6 = 6,
       WUD_STATE_DELETE_7 = 7, WUD_STATE_DELETE_DONE = 8 };
enum { WUD_RESULT_DELETE_BUSY = -1, WUD_RESULT_DELETE_WAITING,
       WUD_RESULT_DELETE_COMPLETE };
enum { WUD_STATE_SYNC_START = 0, WUD_STATE_STACK_INITIALIZED = 4,
       WUD_STATE_INIT_BLUETOOTH_ENABLED = 5, WUD_LIB_STATUS_3 = 3 };
enum { SC_STATUS_OK, SC_STATUS_BUSY, SC_STATUS_FATAL };
#define DEBUGPrint(...) ((void)0)
#define OSMillisecondsToTicks(ms) (ms)

static WUDCB _wcb;
static SCBtDeviceInfoArray _scArray;
static SCBtCmpDevInfoArray _spArray;
static int interrupts, in_handler, tick_count, alarm_count, wait_print_count;
static int status_delay, link_delay, flush_delay, flush_status;
static int set_standard, set_simple, set_calls, flush_calls;
static int callback_count, last_callback, callback_starts;
static void (*pending_flush)(SCStatus);
static void DeleteAllHandler(void);
BOOL WUDStartClearDevice(void);
BOOL WUDIsBusy(void);

static BOOL OSDisableInterrupts(void) {
    BOOL previous = interrupts;
    interrupts = FALSE;
    return previous;
}
static void OSRestoreInterrupts(BOOL enabled) {
    assert(!interrupts);
    interrupts = enabled;
    if (!enabled || in_handler || !_wcb.alarm) return;
    assert(++tick_count < 100);
    in_handler = TRUE;
    interrupts = FALSE;
    if (pending_flush && flush_delay-- == 0) {
        void (*callback)(SCStatus) = pending_flush;
        pending_flush = NULL;
        callback(flush_status);
    }
    DeleteAllHandler();
    interrupts = enabled;
    in_handler = FALSE;
}
static void OSCreateAlarm(int *alarm) { *alarm = 0; }
static int OSGetTime(void) { return 0; }
static void DeleteAllHandler0(void) { assert(0); }
static void OSSetPeriodicAlarm(int *alarm, int start, int period, void (*handler)(void)) {
    assert(!interrupts && start == 0 && period == 20 && handler == DeleteAllHandler0);
    *alarm = 1;
    ++alarm_count;
}
static void OSCancelAlarm(int *alarm) { *alarm = 0; }
static void WUDSetVisibility(BOOL visible, BOOL connectable) {
    assert(!visible && connectable);
}
static BOOL WUDGetConnectable(void) { return TRUE; }
static int WUDiGetDevNumber(void) { return 0; }
static void WUD_DEBUGPrint(const char *format, ...) {
    if (!strcmp(format, "dev number = %d\n")) ++wait_print_count;
}
static WUDDeleteState WUDiDisallowIncoming(void) { return WUD_STATE_DELETE_DISCONNECT_ALL; }
static WUDDeleteState WUDiTerminateDevice(void) { return WUD_STATE_DELETE_CLEANUP_DATABASE; }
static WUDDeleteState WUDiDeleteDevice(void) {
    return link_delay-- > 0 ? WUD_STATE_DELETE_CLEANUP_DATABASE : WUD_STATE_DELETE_CLEANUP_SETTING;
}
static SCStatus SCCheckStatus(void) { return status_delay-- > 0 ? SC_STATUS_BUSY : SC_STATUS_OK; }
static BOOL SCSetBtDeviceInfoArray(SCBtDeviceInfoArray *data) {
    assert(!memcmp(*data, "\0\0\0", sizeof(*data)));
    ++set_calls;
    return set_standard;
}
static BOOL SCSetBtCmpDevInfoArray(SCBtCmpDevInfoArray *data) {
    assert(!memcmp(*data, "\0\0\0", sizeof(*data)));
    ++set_calls;
    return set_simple;
}
static void SCFlushAsync(void (*callback)(SCStatus)) {
    assert(_wcb.deleteState == WUD_STATE_DELETE_6);
    pending_flush = callback;
    ++flush_calls;
}
'''

TESTS = r'''
static void clear_callback(s32 result) {
    ++callback_count;
    last_callback = result;
    if (callback_starts && result == WUD_RESULT_DELETE_WAITING)
        assert(WUDStartClearDevice());
}
static void reset(void) {
    memset(&_wcb, 0, sizeof(_wcb));
    memset(_scArray, 0xff, sizeof(_scArray));
    memset(_spArray, 0xff, sizeof(_spArray));
    _wcb.libStatus = WUD_LIB_STATUS_3;
    _wcb.stackState = WUD_STATE_STACK_INITIALIZED;
    _wcb.initState = WUD_STATE_INIT_BLUETOOTH_ENABLED;
    interrupts = TRUE;
    in_handler = tick_count = alarm_count = wait_print_count = 0;
    status_delay = link_delay = flush_delay = 2;
    set_standard = set_simple = TRUE;
    set_calls = flush_calls = callback_count = callback_starts = 0;
    last_callback = 99;
    flush_status = SC_STATUS_OK;
    pending_flush = NULL;
}
static void completed(void) {
    assert(_wcb.deleteState == WUD_STATE_DELETE_START && !_wcb.alarm);
    assert(interrupts && !in_handler && wait_print_count == 1);
}
int main(void) {
    reset(); _wcb.libStatus = 0;
    _WUDDeleteStoredDevice(); completed(); assert(!alarm_count && !flush_calls);
    puts("PASS: uninitialized library declines deletion and returns idle");

    reset(); _wcb.syncState = 1;
    _WUDDeleteStoredDevice(); completed(); assert(!alarm_count && !flush_calls);
    puts("PASS: unrelated busy state declines deletion and returns idle");

    reset(); _wcb.clearDevCB = clear_callback;
    _WUDDeleteStoredDevice(); completed();
    assert(callback_count == 1 && last_callback == WUD_RESULT_DELETE_WAITING && !alarm_count);
    puts("PASS: callback owns request and may leave deletion idle");

    reset(); _wcb.clearDevCB = clear_callback; interrupts = FALSE;
    _WUDDeleteStoredDevice();
    assert(!interrupts && !alarm_count && wait_print_count == 1);
    puts("PASS: idle call preserves already-disabled interrupt state");

    reset();
    _WUDDeleteStoredDevice(); completed();
    assert(tick_count > 6 && alarm_count == 1 && set_calls == 2 && flush_calls == 1);
    puts("PASS: delayed link drain, busy settings and asynchronous flush complete");

    reset(); flush_status = SC_STATUS_FATAL;
    _WUDDeleteStoredDevice(); completed(); assert(flush_calls == 1);
    puts("PASS: failed asynchronous flush still reaches existing completion path");

    reset(); set_standard = set_simple = FALSE;
    _WUDDeleteStoredDevice(); completed(); assert(set_calls == 2 && !flush_calls);
    puts("PASS: both settings writes fail without waiting for a flush callback");

    reset(); set_standard = FALSE;
    _WUDDeleteStoredDevice(); completed(); assert(set_calls == 2 && flush_calls == 1);
    reset(); set_simple = FALSE;
    _WUDDeleteStoredDevice(); completed(); assert(set_calls == 2 && flush_calls == 1);
    puts("PASS: either successful settings write retains existing flush behavior");

    reset(); _wcb.clearDevCB = clear_callback; callback_starts = TRUE;
    _WUDDeleteStoredDevice(); completed();
    assert(callback_count == 2 && last_callback == WUD_RESULT_DELETE_COMPLETE && alarm_count == 1);
    puts("PASS: request callback starts deletion and completion callback fires");

    reset(); _wcb.clearDevCB = clear_callback;
    _wcb.deleteState = WUD_STATE_DELETE_CLEANUP_DATABASE; _wcb.alarm = 1;
    _WUDDeleteStoredDevice(); completed();
    assert(callback_count == 2 && last_callback == WUD_RESULT_DELETE_COMPLETE && !alarm_count);
    puts("PASS: already-active deletion reports busy then waits for its completion");

    reset(); DeleteFlushCallback(SC_STATUS_FATAL);
    assert(_wcb.deleteState == WUD_STATE_DELETE_START);
    puts("PASS: late flush callback leaves idle state unchanged");
    return 0;
}
'''


def verify_object(path):
    from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN
    from elftools.elf.elffile import ELFFile

    with path.open("rb") as stream:
        elf = ELFFile(stream)
        symbols = elf.get_section_by_name(".symtab")
        symbol = symbols.get_symbol_by_name("_WUDDeleteStoredDevice")[0]
        start, size, section = symbol["st_value"], symbol["st_size"], symbol["st_shndx"]
        code = elf.get_section(section).data()[start:start + size]
        calls = {}
        for relocations in elf.iter_sections():
            if relocations["sh_type"] != "SHT_RELA" or relocations["sh_info"] != section:
                continue
            for relocation in relocations.iter_relocations():
                if relocation["r_info_type"] == 10:
                    calls[relocation["r_offset"]] = symbols.get_symbol(relocation["r_info_sym"]).name
    decoder = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    instructions = list(decoder.disasm(code, start))
    found = []
    for at in range(len(instructions) - 4):
        disable, load, restore, compare, branch = instructions[at:at + 5]
        if [i.mnemonic for i in instructions[at:at + 5]] != ["bl", "lbz", "bl", "cmpwi", "bne"]:
            continue
        if calls.get(disable.address) != "OSDisableInterrupts" or calls.get(restore.address) != "OSRestoreInterrupts":
            continue
        register, operand = load.op_str.split(", ")
        assert register != "r3", "The load must preserve the saved interrupt state in r3"
        assert operand.startswith("0xd(") and compare.op_str == register + ", 0"
        assert int(branch.op_str, 0) == disable.address, "Each iteration must reload the shared field"
        found.append(disable.address)
    assert len(found) == 1, "Expected one interrupt-protected deleteState polling loop"
    print("PASS: MWCC wait reloads deleteState and restores interrupts on every iteration at " + hex(found[0]))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=Path("libs/RVL_SDK/src/wud/WUD.c"))
    parser.add_argument("--object", type=Path, help="Also inspect the compiled 43U WUD object")
    args = parser.parse_args()
    source = args.source.read_text()
    # The source functions' declarations retain their actual storage classes.
    declarations = "\n".join(function(source, name).split("{")[0] + ";" for name in FUNCTIONS)
    code = PRELUDE + declarations + "\n" + "\n\n".join(function(source, name) for name in FUNCTIONS) + TESTS
    with tempfile.TemporaryDirectory(prefix="wud-delete-wait-") as directory:
        path = Path(directory)
        (path / "test.c").write_text(code)
        subprocess.run(["cc", "-std=c99", "-O2", "-Wall", "-Wextra", "-Werror",
                        "-Wno-unused-parameter", str(path / "test.c"), "-o", str(path / "test")], check=True)
        try:
            subprocess.run([str(path / "test")], check=True, timeout=5)
        except subprocess.TimeoutExpired:
            raise SystemExit("FAIL: deletion wait did not finish within five seconds")
    if args.object:
        verify_object(args.object)


if __name__ == "__main__":
    main()
