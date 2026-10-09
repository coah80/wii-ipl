# clean3-c3 cleanup attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/clean3-c3`, branch `agent/w1009/clean3-c3`, baseline `8a67b68cf`.

Read clean3-head.md, cleanup-common.md and AGENTS.md fully. Initial report and completion gates pass, all 1028 units and 12563 functions remain exact and linked. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`; assembly inventory has 162 original functions and zero placeholders.

Prior cleanup2-w3 and cleanup2-w5 logs read. Do not repeat simple WAD no-inline removal, FS path-length extraction or duplicate free-guard removal, SC inline shared-switch actions or name-load extraction. Keep SDK shared cleanup/error exits. No use-site volatile or optimizer scopes appear in the assigned files; WAD retains four required no-inline scopes and a serialized-layout packing scope.

Acceptance: rebuild each trial in this worktree; retain only identical allocated section bytes, sizes, alignment and normalized relocation targets. Full build, every touched unit at 100 percent, DOL hash, DECOMPLETE_OK, ASM INVENTORY PASS and gate.py --quick with zero regressions. Commit each changed source separately and this log.

## Trials

KEEP means allocated section bytes, sizes, alignment, normalized relocations and global symbols equal the initial object. REVERT identifies the changed object components.

- KEEP `es/es` ImportTicket: use if/else for the final transfer-mode branch.
- REVERT `es/es` ES_ImportTicket: remove result initializer overwritten on every path: .rela.text, global symbols, .text.
- REVERT `es/es` ES_ImportBoot: remove result initializer overwritten on every path: .rela.text, global symbols, .text.
- KEEP `es/es` TMD sizes: derive serialized sizes from the existing metadata types.
- KEEP `es/es` remove speculative and redundant comments.
- KEEP `ipc/ipcclt` IOS_OpenAsync: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_Open: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_CloseAsync: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_Close: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_ReadAsync: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_Read: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_WriteAsync: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_Write: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_SeekAsync: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_Seek: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_IoctlAsync: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_Ioctl: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_IoctlvAsync: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_Ioctlv: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` IOS_IoctlvReboot: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` __ios_Ipc2: remove result initializer overwritten on every path.
- KEEP `ipc/ipcclt` Ioctlv: initialize output-vector start before the loop.
- KEEP `ipc/memory` DestroyHeap: remove overwritten result initializer.
- REVERT `ipc/memory` Alloc: remove duplicate NULL assignment on invalid heap: .rela.text, global symbols, .text.
- REVERT `ipc/memory` Free: remove duplicate invalid-result assignment on invalid heap: .rela.text, global symbols, .text.
- KEEP `sc/scsystem` DeleteItemByID: name the byte range shifted when deleting an offset.
- KEEP `sc/scsystem` remove redundant void-pointer casts on NULL.
- KEEP `usb/usb` IUSB_GetAsciiStr: remove overwritten result initializer.
- KEEP `usb/usb` IUSB_GetAsciiStrAsync: remove overwritten result initializer.
- KEEP `usb/usb` IUSB_GetDevDescr: remove overwritten result initializer.
- KEEP `usb/usb` IUSB_GetDevDescrAsync: remove overwritten result initializer.
- KEEP `usb/usb` IUSB_IsoMsgAsync: remove overwritten result initializer.
- KEEP `usb/usb` IUSB_GetAsciiStrAsync: remove jump to the immediately following exit.
- KEEP `usb/usb` IUSB_GetDevDescrAsync: remove jump to the immediately following exit.
- KEEP `usb/usb` type and name the asynchronous descriptor destination.
- KEEP `usb/usb` name cleanup-count values used for isochronous and class notifications.
- REVERT `usb/usb` unicode2ascii: initialize character indexes before the loop: .text.
- KEEP `usb/usb` name UTF-16 and ASCII character indexes.
- KEEP `fs/fs` name callback operation and output destinations.
- KEEP `wad/wad` use the existing WAD_ERROR_NOCOPY enum.
- OBJECT PASS, LATER REVERT `wad/wad` static import, export, hashing and format helper renames; the live report rejection is recorded below.
- KEEP `wad/wad` use ES_MAX_CONTENT for content masks and installed-content arrays.
- KEEP `ipc/memory` __iosAlloc: explain the retained invalid-heap assignment.
- KEEP `ipc/memory` iosFree: explain the retained invalid-heap assignment.
- KEEP `es/es` ES_ImportTicket: explain the retained result initializer.
- KEEP `es/es` ES_ImportBoot: explain the retained result initializer.
- REVERT `wad/wad` static helper renames after the live report: object bytes and relocations stayed identical, but objdiff .text fell to 96.04898 percent because exact-name correspondence disappeared. Restore names without changing symbol configuration.
- REVERT `wad/wad` WADImportEx: remove overwritten success reset 3: .text.
- REVERT `wad/wad` WADImportEx: remove overwritten success reset 2: .text, .rela.text, global symbols.
- REVERT `wad/wad` WADImportEx: remove overwritten success reset 1: .text, .rela.text.
- REVERT `wad/wad` WADBackupEx: remove overwritten success reset 6: .text, .rela.text, global symbols.
- REVERT `wad/wad` WADBackupEx: remove overwritten success reset 5: .text, .rela.text, global symbols.
- REVERT `wad/wad` WADBackupEx: remove overwritten success reset 4: .text, .rela.text, global symbols.
- REVERT `wad/wad` WADBackupEx: remove overwritten success reset 3: .text, .rela.text, global symbols.
- REVERT `wad/wad` WADBackupEx: remove overwritten success reset 2: .text, .rela.text, global symbols.
- KEEP `wad/wad` WADBackupEx: remove overwritten success reset 1.
- REVERT `wad/wad` _WADHash: remove overwritten success reset 1: .text, .rela.text, global symbols.
- REVERT `wad/wad` WADImportEx: remove overwritten result initializer: .text, .rela.text, global symbols.
- KEEP `wad/wad` Unpack: use the unpack structure size for initialization.
- KEEP `fs/fs` align callback operation field with the existing offset comments.
- KEEP `ipc/ipcclt` remove redundant casts from typed RPC pointers.
- KEEP `sc/scsystem` name configuration item type and name-length bit masks.
- Private IOS header: correct the open-request groupId spelling. Repository-wide search found no users of the misspelled member; the field type and layout are unchanged. Verify all consumers in the final full build.
- KEEP `wad/wad` WADImportEx: explain the retained success resets.
- KEEP `wad/wad` WADBackupEx: explain the retained success resets.
- KEEP `wad/wad` _WADHash: explain the retained success resets.


## Retained changes and constraints

- wad.c: use WAD_ERROR_NOCOPY, ES_MAX_CONTENT and sizeof the unpack structure. Remove one overwritten success reset in WADBackupEx. Keep all 185 shared cleanup/exit gotos, four no-inline scopes, packing and address-based helper names. Nine success-reset removals and the WADImportEx initializer removal changed bytes; concise comments identify those requirements.
- fs.c: name the callback operation, file-stat destination, directory-entry count destination and heap base. Keep all 58 shared exits, existing path-length assignments and nested free guards covered by cleanup2-w3.
- usb.c: remove two jumps to the immediately following exit and five overwritten result initializers. Type and name the descriptor output, name class-notification and isochronous cleanup counts, and name UTF-16/ASCII indexes. Keep 39 shared exits, diagnostic emission order and the conventional two-index loop initializer, whose extraction changed bytes.
- ipcclt.c: remove 16 overwritten result initializers, two redundant typed-pointer casts and one comma from the ioctl-vector loop initializer. Keep all 40 SDK error/cleanup exits.
- memory.c: remove the overwritten destroy-heap result initializer. Keep all 11 interrupt-restoring exits and both invalid-heap result assignments, whose removal changes bytes; each assignment has a compiler note.
- scsystem.c: rename sp14 to prefixSize, name the descriptor type and name-length masks, and remove eight redundant casts of NULL. Keep all 37 shared validation/finish exits and the two shared NAND state-machine paths covered by cleanup2-w5.
- private/ios/types.h: correct groudId to groupId. This member has no source users and preserves the serialized layout.
- es.c: replace the transfer-mode success goto with if/else and derive both metadata sizes from sizeof(ESContentMeta) and offsetof(ESTitleMeta, contents). Remove three speculative or redundant comments. Keep nine shared validation exits and the two import result initializers needed by MWCC, with one compiler note each.

## Final verification

- All seven fresh objects equal their initial objects in allocated bytes, sizes, alignment, normalized relocation targets and global symbols, including the private-header change.
- Pools identical: WAD 18 strings, FS 1, USB 54, SC 7, IPC client/memory and ES 0.
- Focused ctxdiff: 40 standalone functions, identical instruction counts and diffs 0. Eight requested helpers have no standalone symbol because they inline or are dead-stripped; whole-unit gates and compiled callers cover their emitted code. Details: /tmp/clean3-c3-pool-ctxdiff.txt.
- gate.py --quick over all seven owned units: GATE PASS. Full build passed, all 189 emitted functions instruction-exact, every owned code/data section and link measure 100 percent. Zero regressions, forbidden additions and readability warnings. Details: /tmp/clean3-c3-final-gate.txt.
- The gate used the nearest ancestor snapshot 04d3d1e8 because 8a67b68c has no external snapshot. An independent comparison with /tmp/clean3-c3-baseline-report.json also found identical global and all 1028 per-unit measures.
- Regenerated build/43U/report.json, build/43U/ok, DECOMPLETE_OK and ASM INVENTORY PASS passed. DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
- git diff --check passed. Source review found every removed initializer overwritten on every path before use, and all removed jumps reached the immediately following exit or were replaced with equivalent if/else.
- Work stayed in clean3-c3. Local commits only.

## Source commits

- fbb0611d libs/RVL_SDK/src/wad/wad.c
- 0ea9574c libs/RVL_SDK/src/fs/fs.c
- 14d96089 libs/RVL_SDK/src/usb/usb.c
- 71b6d7d6 libs/RVL_SDK/src/ipc/ipcclt.c
- 925e2096 libs/RVL_SDK/src/ipc/memory.c
- 99e72fea libs/RVL_SDK/src/sc/scsystem.c
- 9c600162 libs/RVL_SDK/src/es/es.c
- 1bb33cb6 libs/RVL_SDK/include/private/ios/types.h
