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
