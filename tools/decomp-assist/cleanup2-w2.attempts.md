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
