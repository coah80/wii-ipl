# cleanup2-w5 SDK and JPEG cleanup

Branch `agent/w1009/cleanup2-w5`, initial base `85d653b0`.
Read cleanup-common.md fully, including wave-2 goto/comma guidance, and the local AGENTS.md.
Initial full 43U build passed, all 1028 units and 12563 functions exact and linked.
Initial completion checker returned `DECOMPLETE_OK`; DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.
Owned units: usb, ipcclt, scsystem, sdi_api, KPAD, buffer_system.

## Method and references

Rebuild each trial at its real source path. Compare every allocated ELF section and its relocations against fresh baseline objects before retaining a change. Restore each rejected function before the next trial.
Preserve SDK shared error and cleanup exits. Existing rx67/rx67b attempts explain USB diagnostic order; do not retry deleting those data owners.
Public SDK references downloaded read-only into `/tmp/cleanup2-w5-*.c`:

- SC: https://github.com/SMGCommunity/Petari/blob/31a44d0a99fe61bcf150b2104db44ea671930ce5/src/RVL_SDK/sc/scsystem.c
- SC: https://github.com/doldecomp/ogws/blob/27fa94a593096eed7442efc4e70981fd52025b9c/src/revolution/SC/scsystem.c
- IPC and USB: SMGCommunity/Petari source, downloaded from the public master branch.
- JPEG word-reader search found no separate public source reference.

## Compiled trials

- `kpad-ring-switch-break`: rejected: .rela.text; differing: 0 / 96.
- `kpad-select_2obj_first-for-continue`: rejected: .rela.text, .text; differing: 103 / 124.
- `kpad-select_2obj_continue-for-continue`: rejected: .rela.text, .text; differing: 119 / 140.
- `kpad-acc-structured`: rejected: .rela.text, .text; differing: 197 / 400.
- `sc-reload-while`: rejected: .rela.text, .text; differing: 77 / 80.
- `sdi-no-symbol-pragma`: retained.
- `sdi-ISD_InitCard-separate-allocations`: retained.
- `usb-IUSB_GetDeviceList-separate-assignment`: retained.
- `usb-_GetStrCb-separate-assignment`: retained.
- `usb-IUSB_GetAsciiStr-separate-assignment`: retained.
- `usb-IUSB_DeviceInsertionNotifyAsync-separate-assignment`: retained.
- `usb-IUSB_DeviceClassInsertionNotifyAsync-separate-assignment`: retained.
- `kpad-ring-switch-break-canonical-relocations`: retained.
- `kpad-select_2obj_first-nested-guards`: retained.
- `kpad-select_2obj_continue-nested-guards`: retained.
- `jpeg-move-structured`: rejected: .rela.text, .text; differing: 49 / 57.
- `jpeg-load-direct-return`: rejected: .rela.text, .text; differing: 51 / 74.
- `kpad-dpd-break-selection`: retained.
- `kpad-acc-nested-returns`: rejected: .text; differing: 7 / 400.
- `sc-reload-for-loop`: retained.
- `sc-flush-state-path-names`: retained.
- `ipc-free-remove-redundant-local`: retained.
- `kpad-select_2obj_first-sdk-do-continue`: retained.
- `kpad-select_2obj_continue-sdk-do-continue`: retained.
- `jpeg-load-if-else`: retained.
- `jpeg-move-while`: rejected: .rela.text, .text; differing: 39 / 59.
- `jpeg-sbyte-break-blocks`: rejected: .rela.text, .text; differing: 34 / 55.
- `sc-create-file-fallthrough`: retained.
- `kpad-acc-format-switch`: rejected: .rela.text, .text; differing: 197 / 401.
- `jpeg-sbyte-inline-public-reader`: rejected: .rela.text, .text; differing: 52 / 55.
- `jpeg-word-inline-public-reader`: rejected: .rela.text, .text; differing: 84 / 89.
- `jpeg-move-while-success-continue`: retained.
- `jpeg-word-direct-error-return`: retained.
- `jpeg-word-second-buffer-guard`: retained.
- `jpeg-sbyte-one-read-block`: retained.
- `jpeg-word-first-read-block`: retained.
- `jpeg-word-second-read-block`: retained.
- `kpad-acc-format-if-else`: rejected: .rela.text, .text; differing: 195 / 401.
- `sc-parse-separate-name-assignment`: COMPILE FAILED.
- `sc-create-separate-name-assignment`: rejected: .text; differing: 9 / 158.
- `sc-flush-shared-inline-actions`: rejected: .rela.data, .rela.text, .text; differing: 199 / 230.
- `jpeg-TMCJPEGDEC_get_wbyte-remove-empty-else`: rejected: .text; differing: 8 / 89.
- `jpeg-TMCJPEGDEC_get_sbyte-remove-empty-else`: rejected: .text; differing: 4 / 55.
- `sc-parse-separate-name-c89`: rejected: .rela.text, .text; differing: 38 / 147.
- `sc-product-terminator-index`: retained.
- `sc-loop-spacing`: retained.
- `kpad-explain-format-branches`: retained.
- `kpad-name-freestyle-format-range`: rejected: .text; differing: 1 / 158.
- `jpeg-reader-names-and-compiler-notes`: retained.
- `sdi-allocation-spacing`: retained.

## Retained cleanup and remaining constraints

- usb.c: split five assignment-in-condition expressions. Preserve public-SDK error/cleanup exits and diagnostic emission order.
- ipcclt.c: remove ipcFree's redundant result local. Preserve the public-SDK error/cleanup paths.
- scsystem.c: replace the reload goto loop with for/break; replace the create-file jump with switch fallthrough; name the remaining delete/open labels; index the product-info terminator directly. Two shared switch paths remain because inline shared actions changed 199 aligned instructions and relocations. Name-table condition assignments remain because valid separated loads changed 38 and 9 aligned instructions. Each retained constraint has one compiler comment.
- sdi_api.c: remove the symbol-debug pragma and split five allocation assignments from their conditions. Preserve shared SDK exits.
- KPAD.c: remove 17 gotos with switch break, SDK-style do/continue loops, and a selection block. Petari's select_2obj functions use the same preincrement loop conditions. Two acceleration format branches remain because the valid structured variants changed 7 to 197 aligned instructions; the comment states the compiler constraint. Preserve common finish/callback exits. The wrapped format range remains because replacing it with enum subtraction changed one instruction.
- buffer_system.c: remove 26 gotos. Byte and word reads use break blocks, pointer movement uses while/continue, and bit-buffer loading uses if/else. Rename word-reader byte/result locals. Keep the two common-success gotos. Empty else branches remain because deleting them changes 8 word-reader and 4 string-reader instructions; one comment per function explains this.

The initial ring-switch trial rejected only renamed compiler literal symbols such as @2027. The comparator was corrected to resolve defined relocation symbols to section plus address. The repeated trial preserved every allocated section and relocation destination, and fresh ctxdiff/objdiff confirmed exactness. All rejected source trials were restored; later retained trials may replace an earlier retained form.
The first separated ParseConfBuf load failed because its added statement preceded a C89 declaration. The corrected C89 trial compiled and was rejected on byte differences.

## Final verification

- Fresh allocated section bytes, sizes and normalized relocation destinations equal the initial full-build objects for all six units.
- pool_diff.py: identical in all six units, including all 54 USB, 7 SC and 4 SDI strings.
- ctxdiff.py: word reader 89/89, string reader 55/55, pointer movement 57/57, bit-buffer loading 73/73, KPAD first/continue selection 122/122 and 138/138, KPAD DPD reader 278/278, SC reload 79/79 and SC NAND callback 206/206; each has diffs 0.
- Final gate --quick over all six units: GATE PASS; full build passed; 0 regressions, 0 forbidden-pattern additions, 0 readability warnings. Output /tmp/cleanup2-w5-final-gate.txt.
- Fresh build/43U/report.json and build/43U/ok passed; completion checker returned DECOMPLETE_OK. Global measures equal the fresh pre-cleanup baseline.
- Exact functions before/after: USB 13/13, IPC 22/22, SC 30/30, SDI 22/22, KPAD 29/29, JPEG buffer 10/10. All owned sections and link measures remain 100%.
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
- Total goto reduction: 45. No push, PR, merge, rebase, header/config edit or other-worktree mutation.
- Source commit: libs/RVL_SDK/src/usb/usb.c 3bf4cb1b.
- Source commit: libs/RVL_SDK/src/ipc/ipcclt.c 403389a6.
- Source commit: libs/RVL_SDK/src/sc/scsystem.c a4ecc152.
- Source commit: libs/RVL_SDK/src/sdi/sdi_api.c 4a15421c.
- Source commit: libs/RVL_SDK/src/kpad/KPAD.c 7d374d9f.
- Source commit: libs/RVLMiddleware/TMC_JPEG/src/buffer/buffer_system.c 342be728.
