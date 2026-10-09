# cleanup2-w2

Owned files: `src/system/iplNandSDWorker.cpp` and `src/utility/iplESMisc.cpp`.
Branch: `agent/w1009/cleanup2-w2`, baseline `85d653b0`.
Read `cleanup-common.md`, including wave-2 goto/comma guidance, and the unslop and writing-for-agents skills before edits.

## Baseline

- Full 43U build passed before edits.
- Live report: code, data, and linking 100%; 12563/12563 functions and 1028/1028 units.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- Completion checker: `DECOMPLETE_OK`.
- Initial goto statements: NandSDWorker 208; ESMisc 52.
- Preserve ordinary error/resource cleanup paths. Try each structured rewrite separately and revert any changed allocated section, relocation, or symbol.
- Prior effort policy explains the exact Zelda verification helper's parameter-to-local title ID copy. Preserve it; do not repeat register-allocation permutations.

## Trials
- `src/system/iplNandSDWorker` / `unit`: remove debug-symbol pragma. reverted; changed rel('.data', 0), ('.text', 0), rel('.text', 1), ('.text', 1), symbols, rel('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::delete_download_task`: replace jump into retry loop with while condition. reverted; changed symbols, rel('.text', 0).
- `src/utility/iplESMisc` / `DeleteDownloadTask`: replace jump into retry loop with while condition. reverted; changed rel('.text', 0), symbols.
- `src/system/iplNandSDWorker` / `NandSDWorker::do_copy_nand_save_to_sd`: replace start_backup jump with guarded setup. reverted; changed symbols, rel('.text', 0).
- `src/utility/iplESMisc` / `ESMisc::DeleteTitle`: replace do_proc jumps with else around backup. kept; all allocated sections, relocations, and symbols unchanged.

The first comparison conservatively rejected three control-flow rewrites because MWCC renumbered anonymous `@N` literal symbols. Their bytes and relocation destinations were unchanged. Normalize only these compiler-generated names and retry; named symbols and relocation destinations remain checked.
- `src/system/iplNandSDWorker` / `NandSDWorker::delete_download_task`: replace jump into retry loop with while condition. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `DeleteDownloadTask`: replace jump into retry loop with while condition. reverted; changed rel('.text', 0), symbols.
- `src/system/iplNandSDWorker` / `NandSDWorker::do_copy_nand_save_to_sd`: replace start_backup jump with guarded setup. kept; all allocated sections, relocations, and symbols unchanged.

The retry-loop rewrite in ESMisc also renumbers compiler-generated `__FUNCTION__$N` string symbols. Normalize their names while preserving their section, offset, size, bytes, and relocation destinations; retry it.
- `src/utility/iplESMisc` / `DeleteDownloadTask`: replace retry-entry jump and final cleanup jump with while condition. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::clean_duplicated_nand_app`: replace return-only goto label with early returns. reverted; changed symbols, rel('.text', 0), ('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::clean_partial_nand_app`: replace return-only goto label with early returns. reverted; changed symbols, rel('.text', 0), ('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::get_sd_wad_header`: replace return-only goto label with early returns. reverted; changed symbols, rel('.text', 0), ('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::do_startup`: remove final jump to immediately following cleanup. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `ESMisc::GetTmdView`: replace return-only goto label with early returns. reverted; changed rel('.text', 0), ('.text', 0), symbols.
- `src/utility/iplESMisc` / `ESMisc::NumInodesSaveDirRoot`: replace cleanup jump with else for directory count. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `TMDFile::Backup`: remove final jump to immediately following cleanup. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `TMDFile::Restore`: remove final error jump to immediately following cleanup. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::do_check_for_sd_app_to_nand`: remove repeated result check after successful banner read. reverted; changed symbols, rel('.text', 0), ('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::do_copy_nand_save_to_sd`: remove copied boolean before encoding copy flags. reverted; changed symbols, rel('.text', 0), ('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::check_backup_fits`: replace final jump to cleanup with else for success path. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::open_nand_app_content`: replace final jump to cleanup with else for success path. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::do_copy_nand_app_to_sd`: replace final jump to cleanup with else for success path. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::get_sd_app_banner`: replace final jump to cleanup with else for success path. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::get_sd_app_thumbnail`: replace final jump to cleanup with else for success path. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::nand_app_exist_ex`: remove final jump to immediately following cleanup. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `ESMisc::GetTmdView`: remove final jump to immediately following return. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `ESMisc::GetTicketView`: replace cleanup jump with else-if around ticket copy. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `verifySavedataZD`: replace jumps between verification loops with an inline validation helper. reverted; changed symbols, rel('.text', 0), ('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::do_copy_sd_app_to_nand`: replace restore-error jumps with else for successful import. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::get_nand_save_banner`: replace signature-error cleanup jump with else for success result. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `forceStackWeaks`: remove stand-in function that emits stack inline functions. reverted; changed symbols, ('.text', 1), rel('.text', 0), rel('.text', 1), ('.text', 0), rel('.data', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::uncompress_app_thumbnail`: replace raw IMD5 offsets with the format header fields. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `ESMisc::CheckSafeDeleteTitle`: replace zero-test intrinsics with comparison. reverted; changed rel('.text', 0), symbols, ('.text', 0).
- `src/utility/iplESMisc` / `ESMisc::DeleteSavedata`: use path arrays directly instead of displaced stack addresses. reverted; changed ('.text', 0).
- `src/utility/iplESMisc` / `verifySavedataZD`: replace verification gotos with inline validation while retaining the outer valid flag. reverted; changed rel('.text', 0), symbols, ('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::clean_duplicated_nand_app`: try early returns without shortening the final result lifetime. reverted; changed ('.text', 0), rel('.text', 0), symbols.
- `src/system/iplNandSDWorker` / `NandSDWorker::clean_partial_nand_app`: try early returns without shortening the final result lifetime. reverted; changed ('.text', 0), rel('.text', 0), symbols.
- `src/system/iplNandSDWorker` / `NandSDWorker::get_sd_wad_header`: try early returns without shortening the final result lifetime. reverted; changed ('.text', 0), rel('.text', 0), symbols.
- `src/system/iplNandSDWorker` / `NandSDWorker::clean_partial_nand_save`: remove unreferenced return label. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `ESMisc::DeleteSavedata`: use aligned path buffers rounded for a terminator, preserving the observed 0x40/0xa0 stack addresses. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::create`: use the thread stack end directly instead of a shifted Work pointer. reverted; changed rel('.text', 0), rel('.data', 0), symbols, ('.text', 0).
- `src/utility/iplESMisc` / `ESMisc::DeleteSavedata`: replace path-size literals with NAND_MAX_PATH. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::do_copy_nand_save_to_sd`: assign the data-only title flag directly. reverted; changed rel('.text', 0), symbols, ('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::do_copy_sd_save_to_nand`: remove unused initialized path buffer. reverted; changed ('.text', 0), symbols, rel('.text', 0).
- `src/system/iplNandSDWorker` / `NandSDWorker::do_copy_sd_app_to_nand`: use the success else at the final restore result, avoiding nesting the entire import setup. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `NandSDWorker::get_sd_app_banner`: combine nested success check into else-if. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `unit`: document compiler-required workarounds and trim rewrite whitespace. kept; all allocated sections, relocations, and symbols unchanged.
- `src/utility/iplESMisc` / `unit`: document retained zero-test and verification edges; remove stray comment. kept; all allocated sections, relocations, and symbols unchanged.
- `src/system/iplNandSDWorker` / `unit`: remove the remaining blank line left by the else-if rewrite. kept; all allocated sections, relocations, and symbols unchanged.

## Accepted cleanup

- NandSDWorker: 208 -> 197 goto statements. Replaced the retry-loop entry and save-backup setup jump with structured control flow, made final success paths explicit, removed redundant final jumps and an unreferenced label, and replaced raw IMD5 offsets with a real header struct. Ordinary resource/error cleanup jumps stay.
- ESMisc: 52 -> 43 goto statements. Structured ticket copying, inode counting, title backup, and the download retry loop; removed redundant final jumps. Replaced displaced save-data path addresses with aligned buffers and existing NAND path constants.
- Save-data frame evidence: baseline assembly uses directory path at `r1+0xa0` and file path at `r1+0x40`, with a dynamically aligned `0x120` frame. Two real path arrays sized `OSRoundUp32B(NAND_MAX_PATH + 1)` and aligned to 32 bytes preserve those addresses and every instruction. The file-path terminator now lies inside its declared buffer.
- Canonical object comparisons cover every allocated section, relocation target, and named symbol. Only compiler-generated anonymous literal and `__FUNCTION__` symbol numbers are normalized. All accepted edits preserve the baseline bytes and relocation destinations.
- No condition-level comma tricks or function-scoped optimization pragmas were present in these files.

## Retained with evidence

- NandSDWorker symbol mode and `forceStackWeaks`: removing either changes main/weak text and relocation ownership. The required emission remains, with one-line explanations.
- Shared return paths in duplicated/partial app cleanup and WAD-header reading: both early-return forms changed code, including the version preserving the final result assignment. These are ordinary common exits.
- Thread stack-end intermediate pointer, repeated banner result check, integer-to-boolean copy-flag conversion, and initialized unused save-path buffer: simpler forms change code. Added one-line MWCC explanations.
- ESMisc zero-test intrinsics and Zelda verification failure label: a comparison and two structured inline-validation forms change code. Retained them with one-line explanations. The existing title ID parameter copy remains untouched.
- The direct data-only flag assignment changed code. The SD-to-NAND version includes additional checks in its branch, so the simple replacement did not apply and made no edit.
- Replaced the initial wide import guard with a smaller final restore-result `else` after review. The final source keeps setup flat and preserves every byte.

## Final validation

- Required gate command: `python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/system/iplNandSDWorker src/utility/iplESMisc --quick`.
- `GATE PASS`; full build passed; 0 regressions; 0 forbidden-pattern additions; 0 readability warnings.
- NandSDWorker: objdiff 203/203 functions, 51428/51428 code bytes, 12312/12312 data bytes; code/data/linking and every reported section 100%.
- ESMisc: objdiff 31/31 functions, 11200/11200 code bytes, 4416/4416 data bytes; code/data/linking and every reported section 100%.
- Explicit pool checks: NandSDWorker 280/280 identical strings; ESMisc 114/114 identical strings.
- Gate diagnostic caveat: its raw instruction counter prints NandSDWorker 7/203 because `odiff.dis` obtains `.text` by name, and pyelftools selects the last of this symbol-mode object's two `.text` sections. A direct `ctxdiff` trial likewise read 0 instructions for the 133-instruction download function. This is a reader error, not a source mismatch.
- Independent section-aware verification selects each function's `st_shndx`: NandSDWorker 203/203 and ESMisc 31/31 have identical instruction counts and raw function bytes against the original object. Disassembly also reports zero differences for every function. Evidence is in `/tmp/cleanup2-w2-sections.log`; the read-only helper is `/tmp/cleanup2-w2-sections.py`.
- Regenerated live report: `ninja build/43U/report.json`; completion checker: `DECOMPLETE_OK`.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- Scope: only the two assigned source files and this attempts log. No push, PR, merge, rebase, other-worktree edits, or subagents.

## Source commits

- `483f492f`: NandSDWorker cleanup only.
- `6daf7896`: ESMisc cleanup only.

## Round b, MAX effort

- Worktree `data-d3`, branch `agent/w1009/cleanup2-w2b`, baseline `8e47db4a`, containing round a as PR #1353. Re-read cleanup-common.md, this log, unslop, and writing-for-agents.
- Fresh 43U build and completion checker passed. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`. Section-aware baseline verification is 203/203 NandSDWorker and 31/31 ESMisc exact functions.
- Inventory: 197 NandSDWorker gotos in 25 functions; 43 ESMisc gotos in 11 functions. Every remaining NandSDWorker target is a common cleanup or return label, not a state-machine label. ESMisc also has the Zelda verification failure label.
- Do not repeat round-a pragma, weak-emitter, buffer, boolean-conversion, or inline-verification-helper experiments. Test structured error chains, existing loop exits, and return lifetime with assembly evidence per function.

### Structured control-flow trials

- `NandSDWorker::do_startup`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_nand_save_banner`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_check_for_sd_app_to_nand`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::check_backup_fits`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::delete_nand_disk_app_with_ticket`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::delete_nand_titles`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_copy_nand_save_to_sd`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_copy_sd_save_to_nand`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_sd_save_banner`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_sd_wad_header`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_copy_nand_app_to_sd`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_save_banner_for_data_only_title`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_app_banner_from_meta`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::open_nand_app_content`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_copy_sd_app_to_nand`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_sd_app_banner`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_sd_app_thumbnail`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::nand_app_exist_ex`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_nand_save_perms`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::check_sd_title_restorable`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::GetTmdView`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::GetValidTicketIndex`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::DeleteSharedContent`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::NumPrivateContents`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::DeleteSavedata`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `DeleteTicketsForce`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `InitSavedata`: replace the last error-exit jump with a success else. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_startup`: express the save-cache requirement as a positive guard. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::GetValidTicketIndex`: express the valid ticket index as a positive guard. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_startup`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - do_startup__Q23ipl12NandSDWorkerFv: 323 -> 480 instructions; #32 `bne 0x98` -> `bne 0xc4`; #33 `lwz r3, 0(r28)` -> `lwz r4, 0(r28)`; #35 `addis r3, r3, 4` -> `mr r3, r28`.
- `NandSDWorker::do_check_for_sd_app_to_nand`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - do_check_for_sd_app_to_nand__Q23ipl12NandSDWorkerFv: 242 -> 292 instructions; #29 `beq 0x98` -> `beq 0xac`; #35 `addis r3, r3, 4` -> `mr r4, r28`; #36 `stw r30, -0x15dc(r3)` -> `addis r3, r3, 4`.
- `NandSDWorker::check_backup_fits`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - check_backup_fits__Q23ipl12NandSDWorkerFv: 246 -> 291 instructions; #36 `b 0x3ac` -> `b 0x460`; #41 `b 0x188` -> `b 0x1c4`; #44 `beq 0xc8` -> `beq 0xdc`.
- `NandSDWorker::do_list_nand_apps_usage`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - do_list_nand_apps_usage__Q23ipl12NandSDWorkerFv: 114 -> 119 instructions; #38 `b 0x180` -> `b 0x194`; #40 `bge 0x18c` -> `bge 0x1a0`; #46 `beq 0x178` -> `beq 0x18c`.
- `NandSDWorker::delete_nand_disk_app_with_ticket`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - delete_nand_disk_app_with_ticket__Q23ipl12NandSDWorkerFv: 108 -> 107 instructions; #5 `li r27, 0` -> `li r30, 0`; #7 `stw r27, 8(r1)` -> `stw r30, 8(r1)`; #19 `li r28, -2` -> `li r3, -2`.
- `NandSDWorker::delete_nand_titles`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - delete_nand_titles__Q23ipl12NandSDWorkerFv: 146 -> 168 instructions; #5 `li r22, 0` -> `li r25, 0`; #6 `lis r25, 0` -> `lis r24, 0`; #7 `stw r22, 8(r1)` -> `stw r25, 8(r1)`.
- `NandSDWorker::do_copy_nand_save_to_sd`: use early returns with the existing cleanup at each exit. reverted; changed ('.data', 0), ('.text', 0), rel('.rodata', 0), rel('.text', 0), symbols.
  - change_nand_app_count__Q23ipl12NandSDWorkerFl: 47 -> 47 instructions; #16 `addi r3, r31, 0x26af` -> `addi r3, r31, 0x2684`; #21 `addi r3, r31, 0x26e4` -> `addi r3, r31, 0x26b9`; #32 `addi r3, r31, 0x2716` -> `addi r3, r31, 0x26eb`.
  - check_sd_title_restorable__Q23ipl12NandSDWorkerFUl: 97 -> 97 instructions; #51 `addi r3, r31, 0x2ec5` -> `addi r3, r31, 0x2e9a`; #72 `addi r3, r31, 0x2f00` -> `addi r3, r31, 0x2ed5`; #81 `addi r3, r31, 0x2f29` -> `addi r3, r31, 0x2efe`.
- `NandSDWorker::do_copy_sd_save_to_nand`: use early returns with the existing cleanup at each exit. reverted; changed ('.data', 0), ('.text', 0), rel('.text', 0), symbols.
  - change_nand_app_count__Q23ipl12NandSDWorkerFl: 47 -> 47 instructions; #16 `addi r3, r31, 0x26af` -> `addi r3, r31, 0x261f`; #21 `addi r3, r31, 0x26e4` -> `addi r3, r31, 0x2654`; #32 `addi r3, r31, 0x2716` -> `addi r3, r31, 0x2686`.
  - check_sd_title_restorable__Q23ipl12NandSDWorkerFUl: 97 -> 97 instructions; #51 `addi r3, r31, 0x2ec5` -> `addi r3, r31, 0x2e35`; #72 `addi r3, r31, 0x2f00` -> `addi r3, r31, 0x2e70`; #81 `addi r3, r31, 0x2f29` -> `addi r3, r31, 0x2e99`.
- `NandSDWorker::get_sd_save_banner`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - get_sd_save_banner__Q23ipl12NandSDWorkerFUlPQ33ipl12NandSDWorker12SDSaveBanner: 142 -> 166 instructions; #6 `mr r31, r3` -> `mr r30, r3`; #7 `lis r29, 0` -> `lis r28, 0`; #10 `lis r30, 1` -> `lis r29, 1`.
- `NandSDWorker::delete_download_task`: use early returns with the existing cleanup at each exit. reverted; changed ('.data', 0), ('.text', 0), rel('.text', 0), symbols.
  - delete_download_task__Q23ipl12NandSDWorkerFUl: 133 -> 143 instructions; #6 `mr r25, r3` -> `mr r26, r3`; #8 `mr r26, r4` -> `mr r27, r4`; #10 `li r27, 0` -> `li r4, 0x4000`.
- `NandSDWorker::do_copy_nand_app_to_sd`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - do_copy_nand_app_to_sd__Q23ipl12NandSDWorkerFv: 332 -> 481 instructions; #6 `mr r23, r3` -> `mr r25, r3`; #15 `lwz r4, 0(r23)` -> `lwz r4, 0(r25)`; #18 `li r26, 0` -> `addis r4, r4, 4`.
- `NandSDWorker::get_save_banner_for_data_only_title`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - get_save_banner_for_data_only_title__Q23ipl12NandSDWorkerFUxP17WIISaveBannerFilePUl: 88 -> 115 instructions; #26 `b 0x148` -> `b 0x1b4`; #32 `bge 0x98` -> `bge 0xbc`; #36 `li r31, -3` -> `mr r3, r30`.
- `NandSDWorker::get_app_banner_from_meta`: use early returns with the existing cleanup at each exit. reverted; changed ('.data', 0), ('.text', 0), rel('.text', 0), symbols.
  - change_nand_app_count__Q23ipl12NandSDWorkerFl: 47 -> 47 instructions; #16 `addi r3, r31, 0x26af` -> `addi r3, r31, 0x2688`; #21 `addi r3, r31, 0x26e4` -> `addi r3, r31, 0x26bd`; #32 `addi r3, r31, 0x2716` -> `addi r3, r31, 0x26ef`.
  - check_sd_title_restorable__Q23ipl12NandSDWorkerFUl: 97 -> 97 instructions; #51 `addi r3, r31, 0x2ec5` -> `addi r3, r31, 0x2e9e`; #72 `addi r3, r31, 0x2f00` -> `addi r3, r31, 0x2ed9`; #81 `addi r3, r31, 0x2f29` -> `addi r3, r31, 0x2f02`.
- `NandSDWorker::open_nand_app_content`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - open_nand_app_content__Q23ipl12NandSDWorkerFUxUsPUlPP12ESTicketView: 135 -> 203 instructions; #6 `lis r30, 0` -> `lis r29, 0`; #9 `mr r31, r3` -> `mr r30, r3`; #14 `mr r28, r9` -> `mr r31, r9`.
- `NandSDWorker::do_copy_sd_app_to_nand`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - do_copy_sd_app_to_nand__Q23ipl12NandSDWorkerFb: 300 -> 370 instructions; #19 `bne 0xa8` -> `bne 0xc4`; #23 `beq 0x9c` -> `beq 0xb8`; #30 `bne 0xa8` -> `bne 0xc4`.
- `NandSDWorker::get_sd_app_banner`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - get_sd_app_banner__Q23ipl12NandSDWorkerFUlPQ33ipl12NandSDWorker11SDAppBanner: 157 -> 187 instructions; #20 `bne 0x6c` -> `bne 0x84`; #25 `stw r0, 8(r1)` -> `mr r4, r31`; #26 `b 0x244` -> `stw r0, 8(r1)`.
- `NandSDWorker::get_sd_app_thumbnail`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - get_sd_app_thumbnail__Q23ipl12NandSDWorkerFPCQ33ipl12NandSDWorker11SDAppBannerPUc: 172 -> 236 instructions; #13 `li r30, 0` -> `bl 0x34`; #14 `li r29, 0` -> `lwz r5, 8(r27)`; #15 `bl 0x3c` -> `cmplwi r5, 0xc800`.
- `NandSDWorker::nand_app_exist_ex`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - nand_app_exist_ex__Q23ipl12NandSDWorkerFUx: 226 -> 274 instructions; #29 `beq 0x98` -> `beq 0xb4`; #31 `beq 0x98` -> `beq 0xb4`; #36 `li r26, 0` -> `lwz r4, 0x2c(r1)`.
- `NandSDWorker::recursion_nand`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - recursion_nand__Q23ipl12NandSDWorkerFPCcPCcQ33ipl12NandSDWorker16RecursiveProcessPPCcUl: 318 -> 479 instructions; #83 `b 0x484` -> `b 0x708`; #89 `beq 0x188` -> `beq 0x1d0`; #96 `stw r0, 0xc(r1)` -> `lwz r4, 0x1c(r1)`.
- `NandSDWorker::get_nand_save_perms`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - get_nand_save_perms__Q23ipl12NandSDWorkerFUx: 96 -> 144 instructions; #6 `mr r27, r3` -> `mr r30, r3`; #8 `mr r29, r5` -> `mr r28, r5`; #10 `mr r28, r6` -> `mr r27, r6`.
- `NandSDWorker::check_sd_title_restorable`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - check_sd_title_restorable__Q23ipl12NandSDWorkerFUl: 97 -> 130 instructions; #15 `mr r30, r3` -> `mr r29, r3`; #19 `mr r5, r30` -> `mr r5, r29`; #24 `bne 0x154` -> `beq 0x80`.
- `ESMisc::DeleteSharedContent`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - DeleteSharedContent__Q33ipl7utility6ESMiscFPQ23EGG4Heap: 261 -> 477 instructions; #5 `li r28, 0` -> `li r25, 0`; #7 `stw r28, 0x10(r1)` -> `stw r25, 0x10(r1)`; #10 `li r27, 0` -> `li r4, 0x4a00`.
- `ESMisc::NumPrivateContents`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - NumPrivateContents__Q33ipl7utility6ESMiscFPQ23EGG4HeapUx: 153 -> 170 instructions; #13 `li r28, 0` -> `li r5, 0`; #14 `li r27, 0` -> `bl 0x38`; #15 `li r5, 0` -> `cmpwi r3, -0x6a`.
- `DeleteDownloadTask`: use early returns with the existing cleanup at each exit. reverted; changed ('.data', 0), ('.text', 0), rel('.text', 0), symbols.
  - DeleteDownloadTask__Q33ipl7utility6ESMiscFv: 154 -> 168 instructions; #23 `b 0xcc` -> `b 0x104`; #43 `ble 0xcc` -> `ble 0x104`; #47 `li r23, -0x1a` -> `crclr cr1eq`.
- `ESMisc::DeleteSavedata`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - DeleteSavedata__Q33ipl7utility6ESMiscFUxPQ23EGG4Heap: 123 -> 140 instructions; #31 `bne 0xa0` -> `bne 0xc4`; #39 `b 0x1ac` -> `cmpwi r29, 0`; #40 `mulli r4, r0, 0x41` -> `beq 0xbc`.
- `DeleteTicketsForce`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap: 449 -> 457 instructions; #25 `b 0x6c4` -> `b 0x6e4`; #44 `b 0x6c4` -> `b 0x6e4`; #56 `b 0x6c4` -> `b 0x6e4`.
- `InitSavedata`: use early returns with the existing cleanup at each exit. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap: 449 -> 465 instructions; #18 `beq 0x68` -> `beq 0x88`; #25 `b 0x6c4` -> `cmpwi r28, 0`; #26 `lwz r0, 0x24(r1)` -> `beq 0x724`.
- `NandSDWorker::get_nand_save_perms`: classify permissions with a single guarded if/else chain. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::clean_duplicated_nand_app`: return the known corruption result directly, preserving the final result assignment. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - clean_duplicated_nand_app__Q23ipl12NandSDWorkerFPUxUl: 130 -> 134 instructions; #16 `b 0x1e4` -> `b 0x1f4`; #24 `beq 0x1dc` -> `beq 0x1ec`; #30 `beq 0x1dc` -> `beq 0x1ec`.
- `NandSDWorker::clean_partial_nand_app`: return the known corruption result directly, preserving the final result assignment. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - clean_partial_nand_app__Q23ipl12NandSDWorkerFPUxUlPUl: 100 -> 102 instructions; #19 `b 0x16c` -> `b 0x174`; #24 `b 0x178` -> `b 0x180`; #30 `beq 0x164` -> `beq 0x16c`.
- `TMDFile::Backup`: use early returns with the existing backup-buffer cleanup. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - Backup__Q33ipl7utility7TMDFileFUx: 173 -> 203 instructions; #6 `lis r30, 0` -> `lis r28, 0`; #7 `mr r31, r3` -> `mr r29, r3`; #8 `mr r26, r5` -> `mr r31, r5`.
- `TMDFile::Restore`: use early returns with the existing backup-buffer cleanup. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - Restore__Q33ipl7utility7TMDFileFUx: 134 -> 145 instructions; #18 `b 0x200` -> `b 0x22c`; #26 `beq 0x1dc` -> `beq 0x208`; #28 `beq 0x90` -> `beq 0x94`.
- `NandSDWorker::delete_nand_disk_app_with_ticket`: structure the remaining outer error checks while sharing the final cleanup. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_sd_wad_header`: structure the remaining outer error checks while sharing the final cleanup. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::DeleteSavedata`: structure the remaining outer error checks while sharing the final cleanup. kept; all allocated sections, relocations, and named symbols unchanged.
- `DeleteTicketsForce`: structure the remaining outer error checks while sharing the final cleanup. kept; all allocated sections, relocations, and named symbols unchanged.
- `InitSavedata`: structure the remaining outer error checks while sharing the final cleanup. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::NumPrivateContents`: structure the remaining outer error checks while sharing the final cleanup. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::GetValidTicketIndex`: structure the remaining outer error checks while sharing the final cleanup. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_startup`: structure the final error check inside the existing operation branch. kept; all allocated sections, relocations, and named symbols unchanged.
- `TMDFile::Backup`: structure the final error check inside the existing operation branch. kept; all allocated sections, relocations, and named symbols unchanged.
- `TMDFile::Restore`: structure the final error check inside the existing operation branch. kept; all allocated sections, relocations, and named symbols unchanged.
- `verifySavedataZD`: put verification and save deletion in the successful-read branch. kept; all allocated sections, relocations, and named symbols unchanged.
- `verifySavedataZD`: use loop breaks and validate completion before the second verification pass. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap: 449 -> 453 instructions; #8 `li r28, 0` -> `li r18, 0`; #9 `lis r21, 0` -> `lis r28, 0`; #10 `stw r28, 0x24(r1)` -> `stw r18, 0x24(r1)`.
- `NandSDWorker::delete_download_task`: break on timeout and use the existing result to guard the library operations. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - delete_download_task__Q23ipl12NandSDWorkerFUl: 133 -> 135 instructions; #47 `b 0x1cc` -> `b 0xd0`; #52 `li r0, 0` -> `cmpwi r27, 0`; #53 `addi r3, r1, 8` -> `bne 0x1d4`.
- `DeleteDownloadTask`: break on timeout and guard the library operations with the result. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - DeleteDownloadTask__Q33ipl7utility6ESMiscFv: 154 -> 156 instructions; #7 `mr r27, r4` -> `mr r26, r4`; #8 `mr r26, r3` -> `mr r25, r3`; #15 `mr r28, r3` -> `mr r27, r3`.
- `NandSDWorker::clean_partial_nand_app`: break on corruption and preserve the operation result at the shared return. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - clean_partial_nand_app__Q23ipl12NandSDWorkerFPUxUlPUl: 100 -> 105 instructions; #0 `stwu r1, -0x30(r1)` -> `stwu r1, -0x40(r1)`; #2 `stw r0, 0x34(r1)` -> `stw r0, 0x44(r1)`; #3 `addi r11, r1, 0x30` -> `addi r11, r1, 0x40`.
- `NandSDWorker::clean_duplicated_nand_app`: use the result to stop both title loops after corruption. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - clean_duplicated_nand_app__Q23ipl12NandSDWorkerFPUxUl: 130 -> 138 instructions; #6 `mr r19, r3` -> `mr r18, r3`; #8 `mr r20, r4` -> `mr r19, r4`; #9 `mr r21, r5` -> `mr r20, r5`.
- `NandSDWorker::do_list_nand_apps_usage`: break on usage failure and report success only after successful iteration. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - do_list_nand_apps_usage__Q23ipl12NandSDWorkerFv: 114 -> 118 instructions; #10 `mr r27, r3` -> `mr r26, r3`; #20 `lwz r3, 0(r27)` -> `lwz r3, 0(r26)`; #30 `lwz r3, 0(r27)` -> `lwz r3, 0(r26)`.
- `NandSDWorker::recursion_nand`: use a traversal failure flag and ordinary loop and switch breaks. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - recursion_nand__Q23ipl12NandSDWorkerFPCcPCcQ33ipl12NandSDWorker16RecursiveProcessPPCcUl: 318 -> 329 instructions; #5 `li r31, 0` -> `li r27, 0`; #6 `lis r30, 0` -> `lis r26, 0`; #7 `stw r31, 0x10(r1)` -> `stw r27, 0x10(r1)`.
- `NandSDWorker::get_save_banner_for_data_only_title`: use one if/else chain for adjacent error outcomes and the successful operation. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_check_for_sd_app_to_nand`: use one if/else chain for adjacent error outcomes and the successful operation. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_copy_nand_save_to_sd`: use one if/else chain for adjacent error outcomes and the successful operation. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_copy_sd_save_to_nand`: use one if/else chain for adjacent error outcomes and the successful operation. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::do_copy_sd_app_to_nand`: use one if/else chain for adjacent error outcomes and the successful operation. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::open_nand_app_content`: use one if/else chain for adjacent error outcomes and the successful operation. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - open_nand_app_content__Q23ipl12NandSDWorkerFUxUsPUlPP12ESTicketView: 135 -> 133 instructions; #20 `bne 0x1b8` -> `bne 0x1b0`; #33 `b 0x1b8` -> `b 0x1b0`; #40 `beq 0xc0` -> `beq 0xb8`.
- `NandSDWorker::open_nand_app_content`: structure ticket query failure, zero tickets, and content opening as one error chain. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_sd_save_banner`: structure the preceding validation before the successful final checks. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_sd_app_banner`: structure the preceding validation before the successful final checks. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_sd_app_thumbnail`: structure the preceding validation before the successful final checks. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::check_sd_title_restorable`: structure the preceding validation before the successful final checks. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::nand_app_exist_ex`: structure the preceding validation before the successful final checks. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::GetValidTicketIndex`: write the library initialization success test directly. kept; all allocated sections, relocations, and named symbols unchanged.
- `ESMisc::GetValidTicketIndex`: return through the existing error cleanup after either content-close failure. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - GetValidTicketIndex__Q33ipl7utility6ESMiscFPQ23EGG4HeapUxP12ESTicketViewUl: 183 -> 235 instructions; #30 `b 0x2c4` -> `b 0x394`; #42 `blt 0x25c` -> `blt 0x32c`; #48 `blt 0x25c` -> `blt 0x32c`.
- `ESMisc::GetValidTicketIndex`: share one error jump after both content-close outcomes. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - GetValidTicketIndex__Q33ipl7utility6ESMiscFPQ23EGG4HeapUxP12ESTicketViewUl: 183 -> 185 instructions; #30 `b 0x2c4` -> `b 0x2cc`; #42 `blt 0x25c` -> `blt 0x264`; #48 `blt 0x25c` -> `blt 0x264`.
- `verifySavedataZD`: keep validation status in the existing flag and stop each verification loop with break. reverted; changed ('.text', 0), rel('.text', 0), symbols.
  - DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap: 449 -> 454 instructions; #25 `b 0x6c4` -> `b 0x6d8`; #44 `b 0x6c4` -> `b 0x6d8`; #56 `b 0x6c4` -> `b 0x6d8`.
- `NandSDWorker::check_sd_title_restorable`: guard device verification with the successful WAD-header result. kept; all allocated sections, relocations, and named symbols unchanged.
- `NandSDWorker::get_nand_save_banner`: return after closing the file and restoring the UID on each banner error. reverted; changed ('.data', 0), ('.text', 0), rel('.text', 0), symbols.
  - get_app_banner_from_meta__Q23ipl12NandSDWorkerFUxPQ33ipl12NandSDWorker15SDAppBackupData: 288 -> 288 instructions; #253 `addi r3, r30, 0xa48` -> `addi r3, r30, 0x9c2`.
  - get_nand_save_banner__Q23ipl12NandSDWorkerFUxP17WIISaveBannerFilePUl: 236 -> 383 instructions; #0 `stwu r1, -0x100(r1)` -> `stwu r1, -0x110(r1)`; #2 `stw r0, 0x104(r1)` -> `stw r0, 0x114(r1)`; #3 `addi r11, r1, 0x100` -> `addi r11, r1, 0x110`.

### Round-b results by function

Every function containing a goto was reviewed. The 197 NandSDWorker jumps all went to a single cleanup or return label per function; there was no remaining state-machine dispatch to replace with a switch. ESMisc had the same pattern plus two jumps out of Zelda verification loops. Keep the remaining ordinary resource/error exits after the structured changes below.

#### iplNandSDWorker

| Function | Gotos before -> after | Kept structure or measured reason for retention |
|---|---:|---|
| `NandSDWorker::do_startup` | 14 -> 12 | Early cleanup returns change block layout/allocation, 323 -> 480 instructions; shared error cleanup stays. |
| `NandSDWorker::clean_duplicated_nand_app` | 2 -> 2 | Constant early returns add 4 instructions. Result-controlled loops add 8 and change saved-register allocation. |
| `NandSDWorker::clean_partial_nand_app` | 1 -> 1 | Constant early return adds 2 instructions. Result-driven break adds 5 and grows the stack frame from 0x30 to 0x40. |
| `NandSDWorker::get_nand_save_banner` | 9 -> 8 | Early cleanup returns reorder error-report literals and change text/data; shared error cleanup stays. |
| `NandSDWorker::do_check_for_sd_app_to_nand` | 11 -> 8 | Early cleanup returns change block layout/allocation, 242 -> 292 instructions; shared error cleanup stays. |
| `NandSDWorker::check_backup_fits` | 10 -> 9 | Early cleanup returns change block layout/allocation, 246 -> 291 instructions; shared error cleanup stays. |
| `NandSDWorker::do_list_nand_apps_usage` | 1 -> 1 | Early cleanup return grows 114 -> 119 instructions. Break plus final status check grows 114 -> 118 and changes allocation. |
| `NandSDWorker::delete_nand_disk_app_with_ticket` | 2 -> 0 | Structured checks and one final cleanup/return preserve every byte. |
| `NandSDWorker::delete_nand_titles` | 5 -> 4 | Early cleanup returns change block layout/allocation, 146 -> 168 instructions; shared error cleanup stays. |
| `NandSDWorker::do_copy_nand_save_to_sd` | 19 -> 16 | Early cleanup returns reorder error-report literals and change text/data; shared error cleanup stays. |
| `NandSDWorker::do_copy_sd_save_to_nand` | 27 -> 24 | Early cleanup returns reorder error-report literals and change text/data; shared error cleanup stays. |
| `NandSDWorker::get_sd_save_banner` | 5 -> 3 | Early cleanup returns change block layout/allocation, 142 -> 166 instructions; shared error cleanup stays. |
| `NandSDWorker::get_sd_wad_header` | 4 -> 0 | Structured checks and one final cleanup/return preserve every byte. |
| `NandSDWorker::delete_download_task` | 1 -> 1 | Timeout break plus result guard adds one `cmpwi` and one `bne`, 133 -> 135 instructions. Direct returns duplicate cleanup and alter literal order. |
| `NandSDWorker::do_copy_nand_app_to_sd` | 11 -> 10 | Early cleanup returns change block layout/allocation, 332 -> 481 instructions; shared error cleanup stays. |
| `NandSDWorker::get_save_banner_for_data_only_title` | 4 -> 1 | Early cleanup returns change block layout/allocation, 88 -> 115 instructions; shared error cleanup stays. |
| `NandSDWorker::get_app_banner_from_meta` | 12 -> 11 | Early cleanup returns reorder error-report literals and change text/data; shared error cleanup stays. |
| `NandSDWorker::open_nand_app_content` | 5 -> 2 | Early cleanup returns change block layout/allocation, 135 -> 203 instructions; shared error cleanup stays. |
| `NandSDWorker::do_copy_sd_app_to_nand` | 11 -> 8 | Early cleanup returns change block layout/allocation, 300 -> 370 instructions; shared error cleanup stays. |
| `NandSDWorker::get_sd_app_banner` | 6 -> 4 | Early cleanup returns change block layout/allocation, 157 -> 187 instructions; shared error cleanup stays. |
| `NandSDWorker::get_sd_app_thumbnail` | 7 -> 5 | Early cleanup returns change block layout/allocation, 172 -> 236 instructions; shared error cleanup stays. |
| `NandSDWorker::nand_app_exist_ex` | 8 -> 6 | Early cleanup returns change block layout/allocation, 226 -> 274 instructions; shared error cleanup stays. |
| `NandSDWorker::recursion_nand` | 9 -> 9 | Early cleanup returns grow 318 -> 479 instructions. Failure-controlled loop/switch breaks grow 318 -> 329, with three extra comparisons and new failure branches. |
| `NandSDWorker::get_nand_save_perms` | 7 -> 0 | Structured checks and one final cleanup/return preserve every byte. |
| `NandSDWorker::check_sd_title_restorable` | 6 -> 4 | Early cleanup returns change block layout/allocation, 97 -> 130 instructions; shared error cleanup stays. |

#### iplESMisc

| Function | Gotos before -> after | Kept structure or measured reason for retention |
|---|---:|---|
| `ESMisc::GetTmdView` | 1 -> 0 | Structured checks and one final cleanup/return preserve every byte. |
| `ESMisc::GetValidTicketIndex` | 4 -> 2 | Library/index checks are structured. Direct error returns grow 183 -> 235; merging the two close-error jumps grows 183 -> 185 with two extra register moves. |
| `ESMisc::DeleteSharedContent` | 11 -> 10 | Early cleanup returns change block layout/allocation, 261 -> 477 instructions; shared error cleanup stays. |
| `ESMisc::NumPrivateContents` | 4 -> 0 | Structured checks and one final cleanup/return preserve every byte. |
| `DeleteDownloadTask` | 1 -> 1 | Timeout break plus result guard grows 154 -> 156 instructions and changes register allocation. Direct returns duplicate cleanup and alter literal order. |
| `ESMisc::DeleteSavedata` | 3 -> 0 | Structured checks and one final cleanup/return preserve every byte. |
| `verifySavedataZD` | 3 -> 2 | Successful-read branch removes the cleanup jump. Loop-index and validation-flag break forms add 4 and 5 instructions to `DeleteUnauthorizedData`, including completion tests and different failure branches. |
| `DeleteTicketsForce` | 2 -> 0 | Structured checks and one final cleanup/return preserve every byte. |
| `InitSavedata` | 3 -> 0 | Structured checks and one final cleanup/return preserve every byte. |
| `TMDFile::Backup` | 7 -> 6 | Early cleanup returns change block layout/allocation, 173 -> 203 instructions; shared error cleanup stays. |
| `TMDFile::Restore` | 4 -> 3 | Early cleanup returns change block layout/allocation, 134 -> 145 instructions; shared error cleanup stays. |

### Scope and comparison notes

- NandSDWorker: 197 -> 149 gotos, 48 removed. ESMisc: 43 -> 24 gotos, 19 removed. No new goto, carrier flag, helper, compiler pragma, inline assembly, or volatile access was kept.
- Rejected candidates include register allocation changes, extra exit tests/branches, duplicated cleanup blocks, and reordered error-report literals. The detailed trial entries above give function sizes and the first changed instructions. Zelda validation retains its one-line compiler explanation.
- The first ticket-query chain trial used two independent checks after deleting jumps. It changed the failure flow and was reverted. Discard that trial as compiler evidence; the corrected explicit else-if trial preserved every allocated byte and was kept.
- Formatting was limited to changed functions. Removed unreferenced labels and blank lines left by rewritten guards. Reviewed both focused source diffs; no unrelated edit was kept.
- After formatting, both rebuilt objects have identical allocated sections, relocation destinations, and named symbols versus the fresh round-b baseline. Only compiler-generated anonymous literal/`__FUNCTION__` symbol numbers are normalized, with offsets/sizes/bytes checked.
- Section-aware comparison against retail: NandSDWorker 203/203 and ESMisc 31/31 instruction-exact functions, zero raw-byte differences. Pools remain 280/280 and 114/114 identical strings.

### Round-b final validation

- Required gate ran once after all source changes: `python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/system/iplNandSDWorker src/utility/iplESMisc --quick`.
- `GATE PASS`: full 43U build passed; 0 regressions; 0 forbidden-pattern additions; 0 readability warnings. Gate output: `/tmp/cleanup2-w2b-gate.log`.
- NandSDWorker: 203/203 functions; 51428/51428 code bytes; 12312/12312 data bytes. ESMisc: 31/31 functions; 11200/11200 code bytes; 4416/4416 data bytes. Both units, code/data/link metrics, and every reported section remain 100%.
- Regenerated live report, `ninja build/43U/ok`, and `check_decomp_complete.py` passed with `DECOMPLETE_OK`. DOL SHA1 remains `26116613f624061ba99c8d1a299aaa6efa85670d`.
- Rechecked all original functions with the section-aware decoder: 203/203 and 31/31, identical instruction counts, zero instruction differences, and zero raw-byte differences. This independently resolves the gate's known `.text` reader bug, which still prints 7/203 for the two-text-section NandSDWorker object.
- The additional strict assembly inventory check reports three existing placeholders: `TMCJPEGDEC_err_restart`, `CNTCACHEClear`, and `System::warning_run`. Their three source files are byte-identical to baseline `8e47db4a` and outside this assignment. This is a baseline inventory failure; this cleanup introduces no assembly changes.
- Final scope is the two assigned source files and this attempts log. No push, PR, merge, rebase, other-worktree edit, or subagent.

### Round-b source commits

- `ecfc73c9e`: NandSDWorker structured error paths only.
- `866b01d3e`: ESMisc structured error paths only.
