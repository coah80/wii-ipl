# cleanup2-w3 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d4`, branch `agent/w1009/cleanup2-w3`.
Baseline `85d653b0dba14d81de4d9cf125a945d8c6ef57f7`. Existing untracked files retained.
Owned sources: `libs/RVL_SDK/src/wad/wad.c` and `libs/RVL_SDK/src/fs/fs.c`.

Acceptance: readable source changes preserve every allocated object section, resolved relocation and global symbol; both units remain Matching and entirely exact. Run the full build, regenerate the report, require DECOMPLETE_OK, and run gate.py once over both units with --quick and zero regressions. Commit each changed source separately, then this log.

The requested initial full build passed before edits. Live code/data/linking are 100%, all 12563 functions are exact, and DECOMPLETE_OK passed. DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`.

Read cleanup-common.md in full, including wave-2 guidance. Keep ordinary shared error/cleanup exits. Test functions separately and revert byte-changing alternatives.

Prior evidence: WADImportParts must preserve its contiguous 0x28-byte initialization. No carrier-flattening experiments will repeat here. The existing FS conditions contain assignments to path lengths; the reported 17 comma conditions are assignment conditions, with no comma operator.

## Trials
- REVERT `wad` remove no-inline scope _WADMemAlloc, _WADMemFree: changed .rela.text, .text, global symbols.
- KEEP `wad` remove no-inline scope _WADUnpack: every allocated section, resolved relocation and global symbol is identical to the baseline.
- REVERT `wad` remove no-inline scope WAD_815C4A2C: changed .rela.text, .text, global symbols.
- REVERT `wad` remove no-inline scope _WADIsTerminated: changed .rela.text, .text, global symbols.
- Trial runner corrected after removing the _WADUnpack scope shifted later scope indices; no source trial was lost. The cidx/backup scope is tested next.
- REVERT `wad` remove no-inline scope for cidx and backup helpers: changed .data, .rela.text, .sdata, .text, global symbols.
- REVERT `fs` ISFS_CreateDir: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_CreateDirAsync: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_ReadDir: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_ReadDirAsync: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_SetAttr: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_SetAttrAsync: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_GetAttr: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_GetAttrAsync: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_Delete: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_DeleteAsync: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_Rename: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_RenameAsync: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_GetUsage: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_CreateFile: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_CreateFileAsync: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_Open: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_OpenAsync: split path-length assignments from validation conditions: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_CreateDir: structured path validation with standalone length assignment: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_CreateDirAsync: structured path validation with standalone length assignment: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_Open: structured path validation with standalone length assignment: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_OpenAsync: structured path validation with standalone length assignment: changed .rela.text, .text, global symbols.
- REVERT `fs` ISFS_GetAttr: structured path validation with standalone length assignment: changed .rela.text, .text, global symbols.
- KEEP `wad` _WADBackupGetFiles: replace eleven iteration exits with a structured per-entry block: every allocated section, resolved relocation and global symbol is identical to the baseline.
- REVERT `wad` _WADBackupGetFiles: remove duplicate allocation-failure check: changed .rela.text, .text, global symbols.
- KEEP `wad` _WADCheckContents: use break for the missing-content exit: every allocated section, resolved relocation and global symbol is identical to the baseline.
- REVERT `wad` WADCheckSavedataZD: return FALSE directly for unterminated fields: changed .rela.text, .text, global symbols.
- KEEP `wad` name twelve unpack-section fields and the title-metadata ownership flag: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `wad` WADImportEx: move the short-circuit ES_GetTmd assignment to a statement: every allocated section, resolved relocation and global symbol is identical to the baseline.
- REVERT `fs` ISFS_CreateDir: remove the outer null guard duplicated by FS_FREE: changed .rela.text, .text, global symbols; 14 differing instructions, 60/61 instruction counts.
- REVERT `fs` ISFS_ReadDir: remove the outer null guard duplicated by FS_FREE: changed .rela.text, .text, global symbols; 12 differing instructions, 84/85 instruction counts.
- REVERT `fs` ISFS_SetAttr: remove the outer null guard duplicated by FS_FREE: changed .rela.text, .text, global symbols; 14 differing instructions, 64/65 instruction counts.
- REVERT `fs` remove unnecessary pointer casts at memcpy and IOS calls: compilation failed; 'act on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/fs/fs.c -o build/43U/src/libs/RVL_SDK/src/fs && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/fs/fs.d build/43U/src/libs/RVL_SDK/src/fs/fs.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\fs\\fs.c\n# ---------------------------------\n#    1098:  = IOS_WriteAsync(fd, buffer, size, _isfsFuncCb, isfsCallbackArg); \n#   Error:                                                                 ^\n#   (10209) illegal implicit conversion from \'const char *\' to\n#   \'void *\'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n'.
- KEEP `fs` ISFS_CreateFileAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_OpenAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_Write: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_CloseLib: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_Read: use the existing invalid-argument enum: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` remove redundant casts while retaining the const-discarding IOS write cast: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_GetStats: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_CreateDir: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_CreateDirAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_ReadDir: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_ReadDirAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_SetAttr: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_SetAttrAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_GetAttr: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_GetAttrAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_Delete: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_DeleteAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_Rename: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_RenameAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_GetUsage: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_CreateFile: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_Open: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_GetFileStats: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_GetFileStatsAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_ReadAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_WriteAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` ISFS_ShutdownAsync: remove result initialization overwritten on every path: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `wad` name title-metadata size and offset and type the content mask pointer: every allocated section, resolved relocation and global symbol is identical to the baseline.
- REVERT `wad` WADImportGetBlocks: remove two never-allocated buffers and their dead cleanup branches: changed .rela.text, .text, global symbols; 283 differing instructions, 286/298 instruction counts.
- KEEP `wad` WADOpenStream: remove unused result local from the DVD case: every allocated section, resolved relocation and global symbol is identical to the baseline.
- REVERT `wad` WADImportDVDExForBS: remove the second null-buffer check after validating input: changed .rela.text, .text, global symbols; 239 differing instructions, 258/263 instruction counts.
- REVERT `wad` _WADBackupGetFiles: use continue in the directory loop with explicit file cleanup: changed .rela.text, .text, global symbols; 263 differing instructions, 316/317 instruction counts.
- KEEP `wad` WADCheckSavedataZD: combine field validation into one shared exit per record loop: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `wad` _WADBackupGetFiles: retain the common per-entry cleanup exit instead of a one-iteration loop: every allocated section, resolved relocation and global symbol is identical to the baseline.
- The one-iteration _WADBackupGetFiles block was instruction-exact, but it added an artificial loop. Retained the ordinary shared cleanup goto after the direct-continue trial changed bytes.
- REVERT `wad` _WADHash: combine adjacent invalid-input checks with the same exit: changed .rela.text, .text, global symbols; 172 differing instructions, 191/194 instruction counts.
- KEEP `wad` _WADBackupGetFiles: name the shared per-entry cleanup label: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `wad` WADBackupEx: name the shared per-file cleanup label: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `wad` WADImportEx: indent the standalone metadata-query success block: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `wad` document byte-changing pragma, buffer-lifetime and duplicate-check removals: every allocated section, resolved relocation and global symbol is identical to the baseline.
- KEEP `fs` document the retained short-circuit assignments and nested free guards: every allocated section, resolved relocation and global symbol is identical to the baseline.
- Final `wad` object: all allocated sections, resolved relocations and global symbols equal the initial exact object. Gotos 196 -> 185; overwritten result initializers removed: 0.
- Final `fs` object: all allocated sections, resolved relocations and global symbols equal the initial exact object. Gotos 58 -> 58; overwritten result initializers removed: 25.
- Initial libs/RVL_SDK/src/wad/wad measures: {"complete_code": "24500", "complete_code_percent": 100.0, "complete_data": "528", "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "24500", "matched_code_percent": 100.0, "matched_data": "528", "matched_data_percent": 100.0, "matched_functions": 40, "matched_functions_percent": 100.0, "total_code": "24500", "total_data": "528", "total_functions": 40, "total_units": 1}.
- Initial libs/RVL_SDK/src/fs/fs measures: {"complete_code": "6644", "complete_code_percent": 100.0, "complete_data": "80", "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "6644", "matched_code_percent": 100.0, "matched_data": "80", "matched_data_percent": 100.0, "matched_functions": 33, "matched_functions_percent": 100.0, "total_code": "6644", "total_data": "80", "total_functions": 33, "total_units": 1}.
- KEEP `wad` name BroadOn header sections for their ticket, metadata and CRL destinations: every allocated section, resolved relocation and global symbol is identical to the baseline.
- BroadOn field meanings follow the parsed destinations consumed by ES_ImportTicket and ES_ImportTitleInit; the serialized field order is unchanged.
- FS_FREE note corrected after checking the retail tail: one cmpwi followed by two beq branches, with no pointer reload. The nested guards preserve both branches.
- Final pool libs/RVL_SDK/src/wad/wad: POOL IDENTICAL up to 18 (mine=18 base=18).
- Final pool libs/RVL_SDK/src/fs/fs: POOL IDENTICAL up to 1 (mine=1 base=1).
- Final ctxdiff `_WADUnpack`: src 0x100 base 0x100 insns 64/64; diffs 0: [].
- Final ctxdiff `_WADCheckContents`: src 0x154 base 0x154 insns 85/85; diffs 0: [].
- Final ctxdiff `WADCheckSavedataZD`: src 0x16c base 0x16c insns 91/91; diffs 0: [].
- Final ctxdiff `WADImportEx`: src 0x11e8 base 0x11e8 insns 1146/1146; diffs 0: [].
- Final ctxdiff `_WADBackupGetFiles`: src 0x4f4 base 0x4f4 insns 317/317; diffs 0: [].
- Final ctxdiff `WADBackupEx`: src 0x1098 base 0x1098 insns 1062/1062; diffs 0: [].
- Final ctxdiff `_WADUnpackBroadOn`: src 0x270 base 0x270 insns 156/156; diffs 0: [].
- Final ctxdiff `ISFS_CreateDir`: src 0xf4 base 0xf4 insns 61/61; diffs 0: [].
- Final ctxdiff `ISFS_GetAttr`: src 0x158 base 0x158 insns 86/86; diffs 0: [].
- Final ctxdiff `ISFS_WriteAsync`: src 0xa4 base 0xa4 insns 41/41; diffs 0: [].

## Retained changes and compiler requirements

- wad.c: gotos 196 -> 185. Combined each savedata record's six termination failures into one ordinary exit, and replaced the missing-content goto with break. Removed _WADUnpack's two no-inline directives, moved the ES_GetTmd assignment into a statement, removed an unused DVD-case local, named 15 unpack fields and four BroadOn header fields, typed the content-mask pointer, and named the shared cleanup labels. Every changed function and allocated section remains exact.
- wad.c keeps four no-inline scopes because removing them changes callers or inline output. The duplicated allocation and DVD-buffer checks remain because removal changes instructions. Two never-allocated buffer locals retain their cleanup lifetimes because removing them changes 298 instructions into 286. Ordinary shared cleanup gotos remain. Each retained compiler requirement has a concise comment.
- fs.c: removed 25 result initializers overwritten on every control-flow path, five redundant pointer casts, and the raw -101 return in favor of ISFS_ERROR_INVALID. All paths assign ret before using it. Kept all 58 ordinary shared-exit gotos and all 17 validation conditions containing path-length assignments. Splitting the assignments changed code in every function; five structured validation alternatives also changed bytes. The redundant outer free guards remain because removal deletes one of the retail cleanup branches. Shared compiler notes explain the retained checks.
- No inline assembly, new volatile accesses, config changes, header edits, artificial loops, or new uninitialized reads were introduced. The pre-existing untracked files remain untouched.

## Final verification

Final live report compared with the saved initial report: zero regressions across all 1028 units. Both assigned units remain Matching, every function and section is 100%, and every code/data byte is linked. Final allocated sections, resolved relocation targets and global symbols equal the initial objects. Both pools are identical; focused ctxdiff checks above report diffs 0.

Ran gate.py once at the end over both owned units with --quick, after the initial full build. The final full build passed, ninja build/43U/report.json build/43U/ok passed, and tools/check_decomp_complete.py returned DECOMPLETE_OK. DOL SHA1 remains 26116613f624061ba99c8d1a299aaa6efa85670d.

Source commits:
- wad.c: 6f72f061aff43329f642353bc094f8dc6786a5cb.
- fs.c: 49736bc9448f5507546ce5b1f4b84c2f8540bb24.

Final gate output:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/wad/wad] pool: IDENTICAL
[libs/RVL_SDK/src/wad/wad] objdiff: code 24500/24500 data 528/528 functions 40/40 fuzzy 100.0000 linked code 24500
[libs/RVL_SDK/src/wad/wad] instruction-exact functions: 40/40
[libs/RVL_SDK/src/wad/wad]   section .data size 464 match 100.0
[libs/RVL_SDK/src/wad/wad]   section .sdata size 64 match 100.0
[libs/RVL_SDK/src/wad/wad]   section .text size 24500 match 100.0
[libs/RVL_SDK/src/wad/wad] baseline: code 24500/24500 data 528 functions 40 fuzzy 100.0000
[libs/RVL_SDK/src/fs/fs] pool: IDENTICAL
[libs/RVL_SDK/src/fs/fs] objdiff: code 6644/6644 data 80/80 functions 33/33 fuzzy 100.0000 linked code 6644
[libs/RVL_SDK/src/fs/fs] instruction-exact functions: 33/33
[libs/RVL_SDK/src/fs/fs]   section .data size 40 match 100.0
[libs/RVL_SDK/src/fs/fs]   section .sbss size 24 match 100.0
[libs/RVL_SDK/src/fs/fs]   section .sdata size 16 match 100.0
[libs/RVL_SDK/src/fs/fs]   section .text size 6644 match 100.0
[libs/RVL_SDK/src/fs/fs] baseline: code 6644/6644 data 80 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 100.00000 -> 100.00000
global fuzzy_match_percent: 99.99989 -> 99.99989
global complete_code_percent: 100.00000 -> 100.00000
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
