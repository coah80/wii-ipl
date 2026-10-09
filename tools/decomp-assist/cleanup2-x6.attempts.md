# cleanup2-x6 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/rx1`, branch `agent/w1009/cleanup2-x6`, baseline `ab9cdd32`.
Scope: `libs/RVL_SDK/src/`, excluding bte, wad, fs, nup, usb, ipc, sc, sdi, kpad, kbd, dvd, cntcache, fa/driver/sd_drv.c and fa/pdm_partition.c. Original assembly functions stay unchanged.
Read cleanup-common.md fully, including wave-2 guidance, repository AGENTS.md, unslop and writing-for-agents. Initial full 43U build passed with every unit and function exact and linked, DECOMPLETE_OK and DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.

Acceptance: each retained function cleanup preserves allocated ELF sections, resolved relocations and symbol records against the initial object. Final gate covers all touched units, every section, zero regressions, full linkage and DOL hash. Commit each source file separately.

## Inspection

319 owned C/C++/header files inspected, largest first. A balanced-parenthesis scan found no comma operators in if/while conditions; argument separators and idiomatic for-loop clauses are not cleanup targets. WPAD, ES and FAT file gotos mostly share cleanup exits. Actual decompiler control flow appears in WUD registered-device compaction, FAT retry/cache/directory code, VI region dispatch, CARD callbacks, CX streaming, OS play-time and ARC path traversal.
Prior cleanup-c6 experiments belong to excluded DVD and partition files; do not repeat them. NANDOpenClose and ARC push/pop scopes retain required force-active data, not optimization settings. Remaining unfamiliar fields stay unless their meaning is clear from use.

## Trials
- REVERT `libs/RVL_SDK/src/wud/WUD` WUDiGetRegisteredDevice replace compaction jump with break and exhausted-search test: changed .rela.data, .rela.text, .text, symbols (22956 -> 22960 bytes; 13736 differing bytes).
- REVERT `libs/RVL_SDK/src/fa/pf_fat` PFFAT_ReadFATSector replace retry jumps with continue: changed .rela.text, .text, symbols (12572 -> 12548 bytes; 9763 differing bytes).
- KEEP `libs/RVL_SDK/src/fa/pf_dir` PFDIR_p_opendir remove jumps from structured path dispatch: all allocated sections, resolved relocations and symbol records identical to baseline.
- REVERT `libs/RVL_SDK/src/fa/pf_dir` PFDIR_p_fsexec use direct result return: changed .rela.text, .text, symbols (18976 -> 18972 bytes; 3041 differing bytes).
- REVERT `libs/RVL_SDK/src/fa/pf_fat` PFFAT_ReadFATSector use nested callback handling and preserve shared retry test: changed .rela.text, .text, symbols (12572 -> 12588 bytes; 9697 differing bytes).
- KEEP `libs/RVL_SDK/src/vi/vi` __VIRetraceHandler express position interrupt dispatch as short-circuit test: all allocated sections, resolved relocations and symbol records identical to baseline.
- REVERT `libs/RVL_SDK/src/vi/vi3in1` __VISetYUVSEL replace region dispatch gotos with switch: changed .rela.text, .text, symbols (7556 -> 7812 bytes; 1577 differing bytes).
- KEEP `libs/RVL_SDK/src/vi/vi3in1` __VIInit3in1 replace region dispatch gotos with switch: all allocated sections, resolved relocations and symbol records identical to baseline.
- REVERT `libs/RVL_SDK/src/fa/pf_entry_iterator` PFENT_ITER_DoFindEntry replace search-exit jump with return: changed .rela.text, .text, symbols (7880 -> 7888 bytes; 5306 differing bytes).
- REVERT `libs/RVL_SDK/src/vi/vi3in1` __VISetYUVSEL replace region jumps with nested conditions preserving comparison order: changed .rela.text, .text, symbols (7556 -> 7576 bytes; 5670 differing bytes).
- KEEP `libs/RVL_SDK/src/fa/pf_dir` PFDIR_p_fsexec structure invalid-volume return as else: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_file` PFFILE lock dispatch replace completion jump with else: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/cx/CXStreamingUncompression` CXReadUncompLZ replace literal-data jump with else around back-reference decoding: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/arc/arc` ARCReadDir replace retry jump with structured loop: all allocated sections, resolved relocations and symbol records identical to baseline.
- REVERT `libs/RVL_SDK/src/fa/pf_cache` PFCACHE_DoReadNumSector use inline cache-page search instead of dispatch jumps: changed .rela.text, .text, symbols (7396 -> 7416 bytes; 3669 differing bytes).
- KEEP `libs/RVL_SDK/src/fa/pf_cache` PFCACHE_DoWriteNumSectorAndFreeIfNeeded use inline cache-page search instead of dispatch jumps: all allocated sections, resolved relocations and symbol records identical to baseline.
- REVERT `libs/RVL_SDK/src/fa/pf_fat16` PFFAT16_ReadFATEntryWithBuf replace callback-exit jumps with nested branches: changed .rela.text, .text, symbols (1092 -> 1116 bytes; 67 differing bytes).
- REVERT `libs/RVL_SDK/src/fa/pf_fat32` PFFAT32_ReadFATEntryWithBuf replace callback-exit jumps with nested branches: changed .rela.text, .text, symbols (1264 -> 1288 bytes; 83 differing bytes).
- REVERT `libs/RVL_SDK/src/wud/WUD` WUDiGetRegisteredDevice use inline device-slot compaction helper: changed .rela.data, .rela.text, .text, symbols (22956 -> 22968 bytes; 13376 differing bytes).
- REVERT `libs/RVL_SDK/src/vi/vi3in1` __VISetYUVSEL use nested region tests with equality for MPAL: changed .rela.text, .text, symbols (7556 -> 7572 bytes; 5205 differing bytes).
- REVERT `libs/RVL_SDK/src/fa/pf_cache` PFCACHE_DoReadNumSector structure cache search with guarded loop and breaks: changed .rela.text, .text, symbols (7396 -> 7404 bytes; 3583 differing bytes).
- REVERT `libs/RVL_SDK/src/arc/arc` path lookup replace empty-entry back-jump with structured inner loop: changed .rela.text, .text, symbols (2464 -> 2472 bytes; 1242 differing bytes).
- REVERT `libs/RVL_SDK/src/cnt/cnt` path lookup replace empty-entry back-jump with structured inner loop: changed .rela.text, .text, symbols (2376 -> 2384 bytes; 1265 differing bytes).
- REVERT `libs/RVL_SDK/src/arc/arc` ARCConvertPathToEntrynum use guarded search loop and matching-entry break: compiler error. _SDK/src/arc/arc.c -o build/43U/src/libs/RVL_SDK/src/arc && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/arc/arc.d build/43U/src/libs/RVL_SDK/src/arc/arc.d ### mwcceppc.exe Compiler: #    File: libs\RVL_SDK\src\arc\arc.c # ----------------------------------- #     172:             char* name;  #   Error:             ^^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
- REVERT `libs/RVL_SDK/src/cnt/cnt` contentConvertPathToEntrynumDVD use guarded search loop and matching-entry break: changed .text (2376 -> 2376 bytes; 252 differing bytes).
- WITHDRAW previous ARC/CNT inner-loop trial: the inner break would lose the outer skip; both sources were restored and no change was accepted.
- REVERT `libs/RVL_SDK/src/card/CARDWrite` EraseCallback move shared error callback after write-status dispatch: changed .text (900 -> 900 bytes; 9 differing bytes).
- REVERT `libs/RVL_SDK/src/card/CARDWrite` WriteCallback structure canceled, directory-update and sector-erase dispatch: changed .text (900 -> 900 bytes; 3 differing bytes).
- KEEP `libs/RVL_SDK/src/vi/vi` remove no-inline scope for getTiming: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/vi/vi` remove no-inline scope for getTiming: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/vi/vi` remove no-inline scope for setHorizontalRegs: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/vi/vi` remove no-inline scope for setVerticalRegs: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/rso/RSOLink` remove no-inline scope for RSO notification callbacks: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_InitPageList: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_SearchForPage: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_SearchForFreePage: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_FlushPageIfNeeded: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_DoAllocatePage: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_DoReadPage: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_DoReadPageAndFlushIfNeeded: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_DoReadNumSector: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_DoWritePage: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_DoWriteSector: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove no-inline scope for PFCACHE_DoFlushCache: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_entry_iterator` remove no-inline scope for PFENT_RecalcEntryIterator: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/driver/nand_drv` remove no-inline scope for fa_nanddrv_BuildUpFSInfoSector: all allocated sections, resolved relocations and symbol records identical to baseline.
- New cache-read hypothesis: its no-inline scope was removable, so retry the inline search after removing that scope.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` PFCACHE_DoReadNumSector use inline cache search after removing no-inline scope: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove remaining redundant no-inline reset: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_entry_iterator` PFENT_ITER_DoFindEntry structure indexed and sequential searches as if/else: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/arc/arc` path lookup replace empty-entry back-jump with do loop preserving outer skip: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/cnt/cnt` path lookup replace empty-entry back-jump with do loop preserving outer skip: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/card/CARDWrite` EraseCallback preserve early error edge and use successful-dispatch return: all allocated sections, resolved relocations and symbol records identical to baseline.
- REVERT `libs/RVL_SDK/src/card/CARDWrite` WriteCallback preserve early error edge and use successful-dispatch return: changed .text (900 -> 900 bytes; 2 differing bytes).
- REVERT `libs/RVL_SDK/src/card/CARDWrite` WriteCallback keep status checks beside each asynchronous call: changed .rela.text, .text, symbols (900 -> 908 bytes; 606 differing bytes).
- REVERT `libs/RVL_SDK/src/os/OSPlayTime` remove redundant result self-assignments: changed .rela.text, .text, symbols (2448 -> 2428 bytes; 290 differing bytes).
- REVERT `libs/RVL_SDK/src/arc/arc` ARCConvertPathToEntrynum test directory bound inside search with C declarations first: changed .text (2464 -> 2464 bytes; 258 differing bytes).
- KEEP `libs/RVL_SDK/src/arc/arc` indent structured path traversal and explain retained hierarchy join: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/cnt/cnt` indent structured path traversal and explain retained hierarchy join: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_file` indent structured lock dispatch: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_entry_iterator` indent structured sequential entry search: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_cache` remove blank lines left by pragma cleanup: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/vi/vi` remove blank lines left by pragma cleanup: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/cx/CXStreamingUncompression` name header byte counts, repeated byte and LZ back-reference distance: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/card/CARDWrite` tidy erase callback and name retained write-callback joins: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/vi/vi3in1` explain retained YUV region dispatch: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/wud/WUD` name and explain retained registered-device join: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_fat` explain retained FAT retry join: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_fat16` name and explain retained buffered FAT read-result join: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/fa/pf_fat32` name and explain retained buffered FAT read-result join: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `libs/RVL_SDK/src/os/OSPlayTime` explain retained result self-copies: all allocated sections, resolved relocations and symbol records identical to baseline.

## Retained changes and limits

- WUD.c: named device_ready; retained the shared registration join. Both break-with-bound-check and inline compaction changed bytes.
- WPAD.c, es.c, pf_entry_iterator's remaining sibling functions, NAND/ESP wrappers, CARD read/mount/bios/block/create/delete/format and frame-heap routines: retained ordinary error, unlock and common-return gotos. These are not decompiler loop/dispatch targets.
- pf_dir.c: removed three opendir dispatch jumps and the fsexec completion jump. Its one remaining rename jump shares an allocation-result return. Direct fsexec return shortened the function; structured else kept it exact.
- pf_file.c: replaced lock/unlock completion jump with else. The close-file cleanup join remains.
- vi.c: removed the position-interrupt jump and extra scope, using the original short-circuit interrupt tests. Removed all four no-inline scopes, including the prototype scope.
- vi3in1.c: replaced nine init-region gotos with a switch. YUV selection's ten dispatch gotos stay because switch and two nested-condition alternatives change code and inline callers; a one-line compiler note explains the separate store blocks.
- pf_cache.c: removed all four search jumps using one typed inline page-search helper. Removed eleven no-inline scopes and the unmatched reset. The read helper became exact only after its no-inline scope was removed.
- pf_entry_iterator.c: removed its no-inline scope and indexed-search exit goto using structured if/else and break. A direct return changed bytes.
- ARC arc.c: replaced directory-read retry and empty-entry back-jumps with real loops. CNT cnt.c: replaced its empty-entry back-jump with a real loop. Both retain their matched-path hierarchy join, with a compiler note; moving the bound test into the loop reordered the search instructions.
- CARDWrite.c: replaced EraseCallback's jump into the error branch with a successful-command return followed by the shared callback. WriteCallback's four joins remain with meaningful labels; common-check and per-call-check alternatives changed bytes. The note explains why failures bypass the asynchronous command-status test.
- RSOLink.c and fa/driver/nand_drv.c: removed one no-inline scope each, covering notification hooks and the FSINFO-sector builder respectively.
- CXStreamingUncompression.c: replaced the literal-data jump with else around back-reference decoding. Named headerBytes, repeatedByte and backReferenceDistance. Its two remaining gotos share decoder finish/error handling.
- pf_fat.c: retained both retry jumps because continue and nested-callback alternatives changed bytes. pf_fat16.c/pf_fat32.c: named check_read_result and retained their shared buffered-read joins because nested handling changed bytes. Added one-line compiler explanations.
- OSPlayTime.c: retained five result self-copies; deleting them shrank .text by 20 bytes and changed branch layout. Added one compiler note. Common cleanup exits remain.
- No genuine numbered placeholder identifiers were found in the owned sources. field_mode, field_rendering and local_str are meaningful existing names. Header/field renames were unnecessary. Force-active scopes in ARC/NAND retain required data emission and stay unchanged.

Total: 25 gotos and 18 no-inline scopes removed, plus one unmatched reset. Every retained trial preserves all allocated sections, resolved relocations and symbol records. A final source-level comparison confirmed that original assembly blocks are unchanged and every excluded path is untouched. Scope stayed in rx1; no push, PR, merge, rebase or subagents.

## Final verification

Initial and final full builds passed. Fresh report passed `DECOMPLETE_OK`. All 1028 units and exact-name functions were independently compared against the initial report; zero regressions. The gate also reports zero regressions against its main baseline, zero added forbidden patterns and zero readability warnings. Original assembly blocks and all excluded paths are unchanged.

| Unit | Exact functions before -> after | Code bytes | Data bytes |
| --- | --- | --- | --- |
| libs/RVL_SDK/src/arc/arc | 14/14 -> 14/14 | 2464/2464 | 120/120 |
| libs/RVL_SDK/src/card/CARDWrite | 3/3 -> 3/3 | 828/828 | 0/0 |
| libs/RVL_SDK/src/cnt/cnt | 16/16 -> 16/16 | 2228/2228 | 888/888 |
| libs/RVL_SDK/src/cx/CXStreamingUncompression | 6/6 -> 6/6 | 2684/2684 | 0/0 |
| libs/RVL_SDK/src/fa/driver/nand_drv | 18/18 -> 18/18 | 6952/6952 | 5696/5696 |
| libs/RVL_SDK/src/fa/pf_cache | 36/36 -> 36/36 | 7396/7396 | 0/0 |
| libs/RVL_SDK/src/fa/pf_dir | 38/38 -> 38/38 | 18976/18976 | 40/40 |
| libs/RVL_SDK/src/fa/pf_entry_iterator | 16/16 -> 16/16 | 7880/7880 | 24/24 |
| libs/RVL_SDK/src/fa/pf_fat | 35/35 -> 35/35 | 12572/12572 | 64/64 |
| libs/RVL_SDK/src/fa/pf_fat16 | 4/4 -> 4/4 | 1092/1092 | 0/0 |
| libs/RVL_SDK/src/fa/pf_fat32 | 4/4 -> 4/4 | 1264/1264 | 0/0 |
| libs/RVL_SDK/src/fa/pf_file | 45/45 -> 45/45 | 17820/17820 | 0/0 |
| libs/RVL_SDK/src/os/OSPlayTime | 7/7 -> 7/7 | 2176/2176 | 160/160 |
| libs/RVL_SDK/src/rso/RSOLink | 16/16 -> 16/16 | 5604/5604 | 288/288 |
| libs/RVL_SDK/src/vi/vi | 30/30 -> 30/30 | 11296/11296 | 1944/1944 |
| libs/RVL_SDK/src/vi/vi3in1 | 18/18 -> 18/18 | 6976/6976 | 1512/1512 |
| libs/RVL_SDK/src/wud/WUD | 66/66 -> 66/66 | 18852/18852 | 12016/12016 |

All 372 functions and every code/data section of the 17 gated units remain 100%. Allocated ELF sections, resolved relocations and symbol records remain identical to the initial built objects. Local compiler label spelling may change.

Gate command: `python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py libs/RVL_SDK/src/arc/arc libs/RVL_SDK/src/card/CARDWrite libs/RVL_SDK/src/cnt/cnt libs/RVL_SDK/src/cx/CXStreamingUncompression libs/RVL_SDK/src/fa/driver/nand_drv libs/RVL_SDK/src/fa/pf_cache libs/RVL_SDK/src/fa/pf_dir libs/RVL_SDK/src/fa/pf_entry_iterator libs/RVL_SDK/src/fa/pf_fat libs/RVL_SDK/src/fa/pf_fat16 libs/RVL_SDK/src/fa/pf_fat32 libs/RVL_SDK/src/fa/pf_file libs/RVL_SDK/src/os/OSPlayTime libs/RVL_SDK/src/rso/RSOLink libs/RVL_SDK/src/vi/vi libs/RVL_SDK/src/vi/vi3in1 libs/RVL_SDK/src/wud/WUD --quick`.

```text
GATE PASS
regressions vs baseline: 0
forbidden patterns added: 0
readability warnings: 0
DECOMPLETE_OK
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d
```

Gate transcript `/tmp/cleanup2-x6-final-gate.log`; focused ctxdiff `/tmp/cleanup2-x6-final-ctxdiff.log`; pools `/tmp/cleanup2-x6-final-pools.log`; initial report `/tmp/cleanup2-x6-baseline-report.json`.

Focused ctxdiff checks cover the 15 functions with structured control flow or renamed locals; every check has diffs 0 and equal instruction counts. All 17 string pools are identical. No new tests or gate/helper tooling changes were added.

## Commits

- `d2681b7efedc0a49cf2f66da3b2375e9918782b7`: `libs/RVL_SDK/src/wud/WUD.c`.
- `5c3845533de27c85f0c181ec37b4a3622d0e0608`: `libs/RVL_SDK/src/fa/pf_fat.c`.
- `b14976993fb6d684d0e12518aa0a6dd270eeb597`: `libs/RVL_SDK/src/fa/pf_file.c`.
- `5195916578ab48a1d7104a3ee5819a58f03aed83`: `libs/RVL_SDK/src/fa/pf_dir.c`.
- `f2f4d8f96ddacd1ca967cae375f392a9694d6f2f`: `libs/RVL_SDK/src/vi/vi.c`.
- `23d654b4c24c6b1ec3f65359cc822c87c0b6be21`: `libs/RVL_SDK/src/rso/RSOLink.c`.
- `6c4ed1649c3b613270e98b0e835f88dc8ae0feca`: `libs/RVL_SDK/src/fa/pf_cache.c`.
- `7e95eea1da53e6fa9e2b7f68c91da786b1e5d9b7`: `libs/RVL_SDK/src/fa/pf_entry_iterator.c`.
- `99f40560e5281decc04a5767c717d33c8b8b0bfa`: `libs/RVL_SDK/src/vi/vi3in1.c`.
- `b216b6de35467518b91deadbf7ea3582c3b45cca`: `libs/RVL_SDK/src/fa/driver/nand_drv.c`.
- `d6d9a251bed4a5f72224e4f46c1ca59f24b0c733`: `libs/RVL_SDK/src/cnt/cnt.c`.
- `8026d69d4de25f2a49d0929a9a723a2198ee79a9`: `libs/RVL_SDK/src/cx/CXStreamingUncompression.c`.
- `5034ea352d3033d41607560beddd5897018b9359`: `libs/RVL_SDK/src/os/OSPlayTime.c`.
- `b795061fe7121dce8b669c5c1bf09d80302eef59`: `libs/RVL_SDK/src/arc/arc.c`.
- `2686fc981e7800350635c588416848555e954f05`: `libs/RVL_SDK/src/fa/pf_fat32.c`.
- `ef54c2b61a01cbe7942d24b90f43c7100efc7440`: `libs/RVL_SDK/src/fa/pf_fat16.c`.
- `737d263b277e50e0d6f948f4de61f0f3e8f2480f`: `libs/RVL_SDK/src/card/CARDWrite.c`.
- The separate commit containing this log records all trials, retained compiler requirements, measurements and the passing final gate.
