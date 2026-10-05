# USB discarded-API cleanup review

- Original verification base: `f18082e88b680072eaeafbd8f6fe11c6198b9200`
- Original source correction: `4fa0b8e2491cf50be38919644383806608bf4b9b`
- Rebased base after disjoint PRs #1233–1235: `f762dfefbdb3d819bc66729489ce5878e837642b`
- Rebased source correction: `3ce95ac8d659fdd5db4b24b58c7fb0b8e2e3b7cd`

The mechanical rebase leaves both baseline and corrected `usb.c` contents unchanged. The original verification snapshot below is historical; the rebased candidate requires fresh full-build, report, linked-image, and tracked-test verification against `f762dfef`, rather than comparison of global results against `f18082e8`.

## Scope and ownership

Only seven discarded functions in `libs/RVL_SDK/src/usb/usb.c` change:

- `IUSB_IsoMsgAsync`: check the packet-count allocation before dereferencing it
- `IUSB_GetDeviceList` and `IUSB_DeviceInsertionNotifyAsync`: close the opened descriptor after allocation/submission failure
- `IUSB_DeviceClassInsertionNotifyAsync`: check all allocations, initialize the callback context, free locally on rejected submission, and close the descriptor exactly once
- `unicode2ascii`: validate both header bytes, read the descriptor length as unsigned, avoid signed 8-bit index overflow, and bound both bytes of each UTF-16 code unit
- `_GetStrCb` and `IUSB_GetAsciiStr`: bound conversion by the smaller of the transferred byte count and buffer capacity

`IOS_IoctlvAsync` in `libs/RVL_SDK/src/ipc/ipcclt.c` returns allocation/queue failures without invoking the callback. Its queue-error path releases the IPC request, not the caller's USB allocations. Accepted requests invoke `_intrBlkCtrlIsoCb`, which frees its cleanup array and request. Thus rejected submissions need local cleanup; accepted requests remain callback-owned. Both insertion APIs already close the descriptor after successful submission, and this behavior is preserved. String callers already treat positive results as transferred byte counts; the result now also bounds parsing.

## Reproduce semantic tests

From the repository root, using a C11 GCC-compatible compiler with ASan/UBSan:

```
python3 tools/test_usb_async_cleanup.py
```

The runner directly includes the current `usb.c`, stubs only platform/IOS interfaces, and compiles into a temporary directory. It does not alter build configuration or the 43U build. It runs with signed and unsigned `char`. `--cc` selects the host compiler; `--no-sanitize` permits an explicitly unsanitized run. LeakSanitizer is off by default because it cannot run under this executor's ptrace environment; use `--leak-check` where supported. Instrumented allocations independently detect leaked, double-freed, or unowned blocks.

Coverage: every allocation failure in the ISO, vendor/product insertion, class insertion and device-list APIs; failed opens and submissions; accepted callbacks with success/error results; immediate/deferred callbacks; null user callbacks; exactly-once descriptor closes; 66,816 combinations of descriptor length and buffer bound; invalid/null inputs; and short transfers through both string callers. Nonzero-filled allocations expose uninitialized callback state.

To reproduce a baseline failure without changing the checkout:

```
git show f18082e8:libs/RVL_SDK/src/usb/usb.c > /tmp/usb-before-cleanup.c
python3 tools/test_usb_async_cleanup.py --source /tmp/usb-before-cleanup.c --case iso
```

Other failing baseline cases are `insertion`, `class`, `list`, `unicode`, and `wrappers`. Each suite stops at its first failed assertion or sanitizer error. These are host semantic tests, not Wii hardware tests.

## Original f18082e8 snapshot: recorded 43U verification

- Full default build and `build/43U/ok` passed; DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`
- Full objdiff report byte-identical to baseline across all 1,027 units
- USB: 13/13 exact retail functions, 4,396/4,396 code bytes, 1,712/1,712 data bytes, fully linked
- All retail USB instruction bytes and resolved relocation destinations identical to both baseline source object and retail object
- Complete USB `.data`, `.sdata`, `.sbss`, and data relocations identical to baseline; pool 54/54 strings; literal-reference audit 13 functions/46 arguments with no differences or skips
- All seven changed functions absent from the retail object and linked ELF
- Linked ELF differs only in non-allocated `.strtab` anonymous-label names; all other sections, including symbol entries and loadable bytes, identical
- Raw `ctxdiff.py` retains symbol spelling and reports anonymous-label aliases; the separate raw-byte/resolved-relocation audit verifies their identities rather than suppressing those diagnostics
- Global completion checker still fails on pre-existing repository incompleteness; no global completion claim

Both signed- and unsigned-char host suites passed ASan/UBSan. No target compiler flags, assembly, dummy functions, forced retention, or placement tricks were added.
