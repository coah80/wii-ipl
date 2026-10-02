# data-d6 attempts

Applied unslop to this log and final report. Worker scope is the four assigned units; no orchestration or upstream actions.

Baseline HEAD and origin/main: eecf16f0. Fetch checked before each unit; owned source paths have no incoming changes.

Baseline instruction-exact / matched code / matched data:
- CDBRecord: 27/29, 5464/7076, 144/2640.
- sd_drv: 21/26, 8940/11760, 408/3592.
- www_surface: 21/21, 1916/1916, 40/3536.
- iplFocusObject: 88/89, 19772/20332, 408/2576.
Initial full-build quick gate passes, zero regressions, retail DOL SHA1.

## sd_drv data

Pool identical, all 46 strings at identical offsets. nm -n, objdump -t and ELF symbols show target g_pfd_sddrv_info has size 32, source 28; the next object starts at 32 in both. Target .bss is 608 bytes aligned to 32. Source .bss is 608 bytes aligned to 8. Raw BSS bytes are identical. Existing fields occupy 25 bytes; the source type rounds to 28. Recovering eight-byte struct alignment rounds the real type to its original 32-byte extent without adding a field or object.

1. Restore ALIGN32 on SD globals and interrupt event. .sbss g_event moves from 8 to target 32 and section alignment becomes 32, but final size is 36 rather than extracted 40. No data score gain. Not retained.
2. Give the information type 32-byte alignment, with aligned globals. BSS becomes 100%, but code falls from 21 to 17 exact functions. ctxdiff shows changed physical-read increment scheduling and an extra move in get_disk_info. Rejected and restored.
3. Give only the information type eight-byte alignment. BSS becomes 100%; matched_data 408 -> 1016; code remains 8940 and 21 exact functions. No extra fields, padding objects, forced sections or symbol-size edits.

The .data raw bytes match for all 2574 source bytes; target is 2576 bytes, with two trailing zero bytes. All 46 pool strings and offsets match. No source table is missing. The remaining .data score 99.96117 reflects the extracted final section extent. No split correction is justified by relocations; no correction made. .sbss raw zero bytes match, but extracted target includes alignment before g_event and trailing alignment. Objdiff already scores it 100%; this is not proof of identical object layout.

## www_surface data

Pool identical, all 126 strings. .data target 3496/source 3495, every overlapping byte identical and target final byte zero. All export-table relocations resolve to the same exported functions and string offsets. Target .data has no relocations for the discarded message table at 0xc0c..0xc6b; source has a relocation at 0xc64 to IPL_WWW_SURFACE_ZERO. Real manager vtable relocation at 0xd98 matches its destructor. The weak TickTimer report string at 0xd9c is zero-filled in both extracted objects and source, with one final alignment byte only in target. Existing header includes a weak-zero workaround; no additional workaround is added. No table, vtable, or function is deleted to suppress weak relocations. The remaining score is 99.842384, matched_data 40/3536. Object extraction and deduplication explain these differences; no ownership correction has supporting relocation evidence.

## iplFocusObject data

Pool identical, all 80 strings. .data target 2168/source 2164; all overlapping raw bytes identical, final four extracted bytes zero. Relocations through the real event vtable at 0x7c8..0x7df agree. Original has no relocations after 0x7df. Source emits real weak PaneManager, gui::EventHandler and gui::Interface vtables at 0x7e0..0x873 with destructor/method relocations, whereas the extracted original contains zero-filled discarded weak data. No class declarations or virtual methods are deleted to remove required real tables. .rodata, .sdata and .sdata2 already score 100%. Remaining .data score 99.90767 reflects weak relocation metadata and final alignment. No split correction is justified.

## CDBRecord data

Pool first diverges at index 8, offset 0x1b0. Target diagnostic is file-size, source data-size. Target .data is 2496 bytes; source 925. The target retains 47 diagnostic strings, source 19. The absent diagnostics refer to file/data reduction, type getters/setters, maker-code, modification getters, keyword, key/calendar access, duplication and owner change. Target .text has only 29 live functions; these diagnostic-producing functions have no surviving instructions. Definitions cannot be recovered literally from the assigned extracted object. No string blobs, unused diagnostic objects or speculative public functions are added merely to obtain these bytes. Existing typed crypt buffers and AES key match, 144 bytes.

Existing CDBRecord.attempts.md records three distinct CDBCryptBuffer loop variants and at least four distinct CDBRecordEncrypt lifetime/alignment variants. Those are code-lane attempts, not a repair for absent data. Current run checks these functions independently below.

pfd_sddrv_get_total_sectors | one shift expression | objdiff 96.9875%, instructions 80/80, diffs 10; unit code 8940, data 1016, functions 21

pfd_sddrv_get_total_sectors | unsigned shift expression | objdiff 95.8625%, instructions 79/80, diffs different instruction counts; unit code 8940, data 1016, functions 21

pfd_sddrv_get_total_sectors | named shift count | objdiff 96.9875%, instructions 80/80, diffs 10; unit code 8940, data 1016, functions 21

pfd_sddrv_init | unsigned null comparison | objdiff 92.326385%, instructions 144/144, diffs 31; unit code 8940, data 1016, functions 21

pfd_sddrv_init | named null disk | objdiff 92.326385%, instructions 144/144, diffs 31; unit code 8940, data 1016, functions 21

pfd_sddrv_init | explicit device lifetime | objdiff 84.02778%, instructions 145/144, diffs different instruction counts; unit code 8940, data 1016, functions 21

pfd_sddrv_finalize | clear disk before media state | objdiff 92.61404%, instructions 57/57, diffs 5; unit code 8940, data 1016, functions 21

pfd_sddrv_finalize | named remaining flags | objdiff 92.63158%, instructions 57/57, diffs 4; unit code 8940, data 1016, functions 21

pfd_sddrv_finalize | clear drive before flags | objdiff 81.929825%, instructions 57/57, diffs 9; unit code 8940, data 1016, functions 21

pfd_sddrv_store_mbr_buf | name cylinder size | objdiff 99.75247%, instructions 202/202, diffs 9; unit code 8940, data 1016, functions 21

pfd_sddrv_store_mbr_buf | name first sector before CHS | objdiff 99.75247%, instructions 202/202, diffs 9; unit code 8940, data 1016, functions 21

pfd_sddrv_store_mbr_buf | calculate start head before cylinder | objdiff 99.75247%, instructions 202/202, diffs 9; unit code 8940, data 1016, functions 21

pfd_sddrv_build_fat32_mbr_bpb | named sector buffer | objdiff 89.572075%, instructions 230/222, diffs different instruction counts; unit code 8940, data 1016, functions 21

pfd_sddrv_build_fat32_mbr_bpb | reuse initialized format structure | objdiff 90.6982%, instructions 239/222, diffs different instruction counts; unit code 8940, data 1016, functions 21

Ran nm -n, objdump -t and objdump -r -j for every present owned non-text section of both objects. Full output is /tmp/data-d6.symbols-relocations.txt. None of the four objects has extab or extabindex. No splits or symbols were changed.

pfd_sddrv_build_fat32_mbr_bpb | remove unreachable null check from reserved-sector helper | objdiff 97.20721%, instructions 216/222, diffs different instruction counts; unit code 8472, data 1016, functions 20

cmn_calc__Q33ipl5scene12focus_objectFv | name scroller translation vector | objdiff 87.21429%, instructions 140/140, diffs 31; unit code 19772, data 408, functions 88

cmn_calc__Q33ipl5scene12focus_objectFv | name balloon position | objdiff 87.185715%, instructions 140/140, diffs 35; unit code 19772, data 408, functions 88

cmn_calc__Q33ipl5scene12focus_objectFv | separate scroller and fade translations | objdiff 87.185715%, instructions 140/140, diffs 35; unit code 19772, data 408, functions 88

CDBCryptBuffer | for-loop offset lifetime | objdiff 99.97479%, instructions 119/119, diffs 3; unit code 5464, data 144, functions 27

CDBCryptBuffer | remaining-size chunk comparison | objdiff 92.411766%, instructions 118/119, diffs different instruction counts; unit code 5464, data 144, functions 27

CDBCryptBuffer | named chunk pointer | objdiff 98.29412%, instructions 119/119, diffs 5; unit code 5464, data 144, functions 27

CDBRecordEncrypt | file-size and data-size declaration order | objdiff 97.211266%, instructions 283/284, diffs different instruction counts; unit code 5464, data 144, functions 27

CDBRecordEncrypt | signed pointer tests to pointer null tests | objdiff 96.62676%, instructions 284/284, diffs 246; unit code 5464, data 144, functions 27

CDBRecordEncrypt | signature before hash output | objdiff 97.19014%, instructions 283/284, diffs different instruction counts; unit code 5464, data 144, functions 27

## Open-function audit

Every still-open function received three distinct source experiments in this run, individually built and measured, then restored. No experimental code is retained.

- CDBCryptBuffer, 99.97479%, 119/119 instructions, exactly three diagnostic pool offsets differ. The absent pre-crypt diagnostics are the cause. Loop changes cannot repair them.
- CDBRecordEncrypt, 97.19014%, 283/284 instructions, pool offsets plus stack positions and register allocation. Three fresh attempts and prior attempts remain non-exact.
- pfd_sddrv_init, 92.326385%, 144/144 instructions, branch direction, allocation and store scheduling. Unsigned/null tests unchanged; moving the device assignment worsened the result.
- pfd_sddrv_finalize, 92.63158%, 57/57 instructions, four register/scheduling differences. Named flags unchanged; clearing other fields first worsened the result.
- pfd_sddrv_get_total_sectors, 99.5%, 80/80 instructions, six shift/register differences. One expression, unsigned shift and named shift lifetime failed.
- pfd_sddrv_store_mbr_buf, 99.75247%, 202/202 instructions, nine CHS temporary-register differences. Named cylinder size, named first sector and swapped CHS statement order all unchanged.
- pfd_sddrv_build_fat32_mbr_bpb, 94.75225%, 230/222 instructions, inlined reserved-sector null test and scheduling. Naming the buffer and initializing the structure failed. Removing the helper guard produced 216/222 instructions and regressed another exact function, so it was restored.
- cmn_calc__Q33ipl5scene12focus_objectFv, 87.185715%, 140/140 instructions, stack temporary placement and floating-point ordering. Naming the translation reduces 35 differences to 31 but is not exact; naming balloon and fade positions is unchanged.

Data goal remains incomplete. No diagnostic strings, ghost functions, dummy tables, removed virtual methods, artificial padding or section-size edits were used. Type alignment is inferred from the original 32-byte information-object extent, not from a surviving retail type declaration. Weak discarded sections and linker tail alignment are reported as extraction limitations, not as 100% objdiff results.

## Final clean gate

Command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py libs/RevoEX/src/cdb/CDBRecord libs/RVL_SDK/src/fa/driver/sd_drv src/iplwww/www_surface src/scene/board/iplFocusObject

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBRecord] pool: DIVERGES at string 8 (mine=19 orig=47)
[libs/RevoEX/src/cdb/CDBRecord] objdiff: code 5464/7076 data 144/2640 functions 27/29 fuzzy 99.5472 linked code 0
[libs/RevoEX/src/cdb/CDBRecord] instruction-exact functions: 27/29
[libs/RevoEX/src/cdb/CDBRecord]   section .bss size 128 match 100.0
[libs/RevoEX/src/cdb/CDBRecord]   section .data size 2496 match 50.833576
[libs/RevoEX/src/cdb/CDBRecord]   section .rodata size 16 match 100.0
[libs/RevoEX/src/cdb/CDBRecord]   section .text size 7076 match 99.5472
[libs/RevoEX/src/cdb/CDBRecord]   below 100: CDBCryptBuffer 99.97479
[libs/RevoEX/src/cdb/CDBRecord]   below 100: CDBRecordEncrypt 97.19014
[libs/RevoEX/src/cdb/CDBRecord] baseline: code 5464/7076 data 144 functions 27 fuzzy 99.5472
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 8940/11760 data 1016/3592 functions 21/26 fuzzy 99.0544 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 21/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 99.96117
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 99.05442
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 92.326385
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.63158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 99.5
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 99.75247
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 8940/11760 data 408 functions 21 fuzzy 99.0544
[src/iplwww/www_surface] pool: IDENTICAL
[src/iplwww/www_surface] objdiff: code 1916/1916 data 40/3536 functions 21/21 fuzzy 100.0000 linked code 1916
[src/iplwww/www_surface] instruction-exact functions: 21/21
[src/iplwww/www_surface]   section .data size 3496 match 99.842384
[src/iplwww/www_surface]   section .sbss size 32 match 100.0
[src/iplwww/www_surface]   section .sdata size 8 match 100.0
[src/iplwww/www_surface]   section .text size 1916 match 100.0
[src/iplwww/www_surface] baseline: code 1916/1916 data 40 functions 21 fuzzy 100.0000
[src/scene/board/iplFocusObject] pool: IDENTICAL
[src/scene/board/iplFocusObject] objdiff: code 19772/20332 data 408/2576 functions 88/89 fuzzy 99.6471 linked code 0
[src/scene/board/iplFocusObject] instruction-exact functions: 88/89
[src/scene/board/iplFocusObject]   section .data size 2168 match 99.90767
[src/scene/board/iplFocusObject]   section .rodata size 176 match 100.0
[src/scene/board/iplFocusObject]   section .sdata size 176 match 100.0
[src/scene/board/iplFocusObject]   section .sdata2 size 56 match 100.0
[src/scene/board/iplFocusObject]   section .text size 20332 match 99.64706
[src/scene/board/iplFocusObject]   below 100: cmn_calc__Q33ipl5scene12focus_objectFv 87.185715
[src/scene/board/iplFocusObject] baseline: code 19772/20332 data 408 functions 88 fuzzy 99.6471
regressions vs baseline: 0
global matched_code_percent: 88.52293 -> 88.52293
global fuzzy_match_percent: 99.44739 -> 99.44739
global complete_code_percent: 62.78043 -> 62.78043
global matched_data_percent: 93.05085 -> 93.08402
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Only retained source edit is the information type alignment, committed as 1fe346a7. Exact counts and code bytes unchanged across every owned unit. Final DOL hash matches, no regression, no forbidden patterns, no readability warnings. All eight open functions have three fresh attempts. Four data sections remain below 100%; full data matching is not claimed.

## Round 2 baseline

HEAD 3f330a39 includes accepted #735. Origin was fetched before each unit inspection; ongoing unrelated main commits do not change assigned sources. Fresh baseline quick gate passes with data 144/1016/40/408 and exact functions 27/21/21/88. No code tuning is needed for a data-only lane. Revisit merged data ownership rather than adding source padding.

### sd_drv last merged diagnostic owner

Original lbl_8169134C owns 988 bytes starting at pool offset 0x634, but nm and source literals show 19 separate null-terminated diagnostic/format strings within that inferred aggregate. Every source byte through offset 0xa0d equals the target. Two final bytes at 0xa0e/0xa0f are linker alignment, not part of the final 54-byte error string. Target pfd_sddrv_full_format at object 0x2dbc uses relocated pool anchor r30 plus 0x9d8 immediately before OSReport. The final original string begins exactly at 0x816916f0 and ends at 0x81691726; next relocated real table st_uhs_msc_blk_func starts at 0x81691728 in the neighbouring unit. Preserve both split extents and every payload byte. Split the aggregate into its actual strings, proven by source literals, terminators and target pool-reference instructions, instead of changing the section end or fabricating padding.

Splitting all 19 real literals within the last inferred aggregate produces .data 100% and matched_data 1016 -> 3592/3592. Payload bytes and total_data are unchanged, two final zero alignment bytes remain in the same .data split. Every exact function remains exact. Quick gate PASS, zero regressions, forbidden/style 0, retail DOL hash. This is a corrected object ownership boundary supported by relocated pool-base plus 0x9d8, not a section-size reduction.

### Focus event vtable ownership

Original event vtable inferred size 0xb0 incorrectly absorbs three different compiler-emitted weak vtables and four final alignment bytes. The real event class declares four virtual methods and its compiler-generated table is 0x18. Constructor target .text relocations 0x16/0x2a point to the event table, with retained method relocations at 0x7d0/7d4/7d8/7dc. Source emits the real 0x5c PaneManager table at .data+0x7e0, 0x18 EventHandler table at +0x83c and 0x20 Interface table at +0x854. Their original retained definitions already exist at 0x816359c4, 0x81635a38 and 0x81635a50 with precisely those same sizes and weak scope. Focus make_gui_mgr target relocations at 0x2866/286e refer to the retained PaneManager table; source emits its deduplicated local weak definition. This proves separate real compiler objects, not additional event virtual slots. Split the incorrect aggregate into the real class table owners with their names, sizes and weak scope. Keep all 2168 data bytes in the same split, including discarded zero bytes and four final alignment bytes.

Focus ownership correction produces all non-text sections 100%, data 408 -> 2576/2576, exact 88 unchanged. Quick full gate PASS with zero regressions, forbidden/style 0 and correct DOL hash. No source/class/inline changes required; the existing real classes already emit the tables in exactly the original order. Original section byte counts and split extents are unchanged.

### Surface TickTimer format ownership

Correct previous-round note: the weak TickTimer report format at pool+0xd9c is real text ` : %d[ms]\n`, not zero-filled. Both raw objects contain identical 11 payload bytes, target includes one final zero alignment byte. The real inline TickTimer::report already emits its weak 11-byte string. Target RSO resolver call relocation at 0x434 references the retained TickTimer::report method. Its emitted source inline body references @STRING@ via address-half relocations at 0x4e6/0x4f6; the original has no duplicate method body. Source symbol size, literal contents and original literal terminator establish the discarded inline data owner's 11-byte extent. Add the missing weak literal owner at 0x81643aac with its real 11-byte null-terminated extent; preserve the original 3496-byte split and final alignment byte.

Surface missing weak format symbol correction produces every section 100% and matched_data 40 -> 3536/3536. Quick gate PASS, zero regressions, forbidden/style 0, correct DOL hash. Source already has its real inline TickTimer and 12-byte SurfaceManager vtable. Existing shared-header weak-zero workaround is untouched because it is unrelated to this missing ownership label and all sections now match without new source tricks.

### CDB first divergence, real file-size getter

Restore the file-size wrapper immediately before its data-size counterpart. This is supported by the existing actual inlined sequence in CDBRecordEncrypt and CDBRecordDecrypt: CDBLock, file-open diagnostic/error, CDBRecordFileGetFileSize, CDBUnlock. The backing typed function exists in the repository and original object. No invented external calls or dummy literals are added. Measure this first restoration before proceeding into the missing reduction diagnostics.

File-size restoration fixes the first divergence exactly: strings 8 and 9 now both match bytes and offsets 0x1b0/0x1ec. First divergence advances to 10 at 0x228, now the missing ReduceFileSize diagnostics. CDB original .text contains no reduction functions or bodies, original bridge/file/VF units likewise have no truncation API in source, headers, retained symbols or Ghidra export. No invented external truncation routine or placeholder error-only function will be used to emit these strings. Current source has 19 distinct diagnostics versus 47 original; missing payload remains visible and data stays 144/2640. Read-only field/keyword setters do not repair the first reduction block, so no speculative API additions are made.

File-size wrapper quick gate PASS with zero regressions and all 27 original exact functions preserved. Its first two previously misplaced diagnostics now match the original pool offsets. Restoration is supported by surviving inlined instructions and existing backing API; remaining APIs without surviving bodies are left unresolved.

### Round 2 scope and evidence audit

Repeated nm -n, objdump -t, objdump -r -j for every owned non-text section on both objects. Full output at /tmp/data-d6-r2.final-data-evidence.txt. Verified raw bytes for sd_drv, www_surface and Focus agree through the complete emitted source payload in every section. Only zero linker alignment is absent at source section ends. Their original split ranges and total_data never changed. Source's real weak class/vtable/format definitions are preserved, not replaced with zero arrays or assembly.

Remaining CDBRecord code functions CDBCryptBuffer and CDBRecordEncrypt each already have three distinct experiments in this persistent attempts log. CDBCryptBuffer retains the exact 119-instruction stream except three missing-pool offsets; repeated register/loop variants cannot create the reduction diagnostics. Encrypt has 283/284 instructions, pool offsets and stack allocation differences. Round 2 fixes the first two token-order diagnostics by a real recovered getter, but cannot recover the reduction/mutation/duplication bodies from retained instructions. No bogus truncation API, stub, unused string object, padding or ownership reduction is added for these missing bytes. Existing data total 2640 remains authoritative.

CDBRecordEncrypt | use recovered file-size wrapper in encryption | objdiff 96.616196%, instructions 284/284, diffs 185; unit code 5464, data 144, functions 27

CDBRecordEncrypt | wrapper with signed file null comparison | objdiff 97.19718%, instructions 283/284, diffs different instruction counts; unit code 5464, data 144, functions 27

CDBRecordEncrypt | wrapper with named file lifetime | objdiff 96.616196%, instructions 284/284, diffs 185; unit code 5464, data 144, functions 27

Three fresh Encrypt experiments replace the manually expanded file-size sequence with the recovered real getter. Pointer-null and named-file-lifetime variants score 96.616196%, 284/284 instructions. The signed null test proven by the original inline cmpwi retains 97.19718%, 283/284 instructions. Retain this typed getter call: a direct disassembly comparison against the previously full-gated object confirms every one of the 29 original function instruction streams is unchanged, not only the 27 exact functions. Thus the restored getter is used by live encryption code and replaces its duplicate expanded sequence. No newly invented operation or unused diagnostic object is introduced. Pool first divergence remains 10 with the first ten strings at identical offsets.

## Round 2 final clean gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBRecord] pool: DIVERGES at string 10 (mine=19 orig=47)
[libs/RevoEX/src/cdb/CDBRecord] objdiff: code 5464/7076 data 144/2640 functions 27/29 fuzzy 99.5483 linked code 0
[libs/RevoEX/src/cdb/CDBRecord] instruction-exact functions: 27/29
[libs/RevoEX/src/cdb/CDBRecord]   section .bss size 128 match 100.0
[libs/RevoEX/src/cdb/CDBRecord]   section .data size 2496 match 52.795387
[libs/RevoEX/src/cdb/CDBRecord]   section .rodata size 16 match 100.0
[libs/RevoEX/src/cdb/CDBRecord]   section .text size 7076 match 99.54833
[libs/RevoEX/src/cdb/CDBRecord]   below 100: CDBCryptBuffer 99.97479
[libs/RevoEX/src/cdb/CDBRecord]   below 100: CDBRecordEncrypt 97.19718
[libs/RevoEX/src/cdb/CDBRecord] baseline: code 5464/7076 data 144 functions 27 fuzzy 99.5472
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 8940/11760 data 3592/3592 functions 21/26 fuzzy 99.0544 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 21/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 99.05442
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 92.326385
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.63158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 99.5
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 99.75247
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 8940/11760 data 1016 functions 21 fuzzy 99.0544
[src/iplwww/www_surface] pool: IDENTICAL
[src/iplwww/www_surface] objdiff: code 1916/1916 data 3536/3536 functions 21/21 fuzzy 100.0000 linked code 1916
[src/iplwww/www_surface] instruction-exact functions: 21/21
[src/iplwww/www_surface]   section .data size 3496 match 100.0
[src/iplwww/www_surface]   section .sbss size 32 match 100.0
[src/iplwww/www_surface]   section .sdata size 8 match 100.0
[src/iplwww/www_surface]   section .text size 1916 match 100.0
[src/iplwww/www_surface] baseline: code 1916/1916 data 40 functions 21 fuzzy 100.0000
[src/scene/board/iplFocusObject] pool: IDENTICAL
[src/scene/board/iplFocusObject] objdiff: code 19772/20332 data 2576/2576 functions 88/89 fuzzy 99.6471 linked code 0
[src/scene/board/iplFocusObject] instruction-exact functions: 88/89
[src/scene/board/iplFocusObject]   section .data size 2168 match 100.0
[src/scene/board/iplFocusObject]   section .rodata size 176 match 100.0
[src/scene/board/iplFocusObject]   section .sdata size 176 match 100.0
[src/scene/board/iplFocusObject]   section .sdata2 size 56 match 100.0
[src/scene/board/iplFocusObject]   section .text size 20332 match 99.64706
[src/scene/board/iplFocusObject]   below 100: cmn_calc__Q33ipl5scene12focus_objectFv 87.185715
[src/scene/board/iplFocusObject] baseline: code 19772/20332 data 408 functions 88 fuzzy 99.6471
regressions vs baseline: 0
global matched_code_percent: 88.55724 -> 88.55724
global fuzzy_match_percent: 99.45033 -> 99.45033
global complete_code_percent: 62.78043 -> 62.78043
global matched_data_percent: 96.55914 -> 97.00876
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

Data before -> after: CDBRecord 144 -> 144/2640, sd_drv 1016 -> 3592/3592, www_surface 40 -> 3536/3536, Focus 408 -> 2576/2576. Instruction-exact counts 27 -> 27, 21 -> 21, 21 -> 21, 88 -> 88. Matched code bytes unchanged 5464, 8940, 1916, 19772. Full clean gate passes, DOL SHA1 correct, regression/forbidden/style counts zero. No splits or total_data were changed. All three completed data units have every non-text section at 100%; CDB remains incomplete. Every original open code function has three logged attempts; Encrypt has six.
