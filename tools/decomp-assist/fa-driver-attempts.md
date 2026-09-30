# FA driver attempts

Baseline pools identical for all four units. Each trial builds only its owned object. Failed experiments are restored.

- pfd_get_media_drv_char: output pointer unchanged. 67/70 instructions; 57 differing positions.
- pfd_get_media_drv_char: volume index in for increment. 69/70 instructions; 46 differing positions.
- pfd_get_media_drv_char: signed volume index and partition initialized first. 69/70 instructions; 44 differing positions.
- pfd_get_media_drv_char: separate pointer advance after volume loop body. 69/70 instructions; 46 differing positions.
- pfd_get_media_drv_char: use loop bound on indexed volume address. 69/70 instructions; 46 differing positions.
- fa_nanddrv_physical_write: find disk using existing inline accessor. 176/175 instructions; 161 differing positions.
- fa_nanddrv_physical_write: compute file size before byte count. 175/175 instructions; 38 differing positions.
- fa_nanddrv_physical_write: compute wanted byte offset before byte count. 175/175 instructions; 38 differing positions.
- fa_nanddrv_physical_write: declare disk record before size variables. 175/175 instructions; 21 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 1. 175/175 instructions; 21 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 2. 175/175 instructions; 41 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 3. 175/175 instructions; 27 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 4. 175/175 instructions; 42 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 5. 175/175 instructions; 42 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 6. 175/175 instructions; 39 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 7. 175/175 instructions; 23 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 8. 175/175 instructions; 42 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 9. 175/175 instructions; 31 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 10. 175/175 instructions; 42 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 11. 175/175 instructions; 42 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 12. 175/175 instructions; 35 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 13. 175/175 instructions; 27 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 14. 175/175 instructions; 42 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 15. 175/175 instructions; 30 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 16. 175/175 instructions; 41 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 17. 175/175 instructions; 42 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 18. 175/175 instructions; 38 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 19. 175/175 instructions; 42 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 20. 175/175 instructions; 39 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 21. 175/175 instructions; 41 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 22. 175/175 instructions; 34 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 23. 175/175 instructions; 42 differing positions.
- fa_nanddrv_physical_write: record and byte-count declaration order 24. 175/175 instructions; 38 differing positions.
- fa_nanddrv_physical_write: record declared after scratch buffer. 175/175 instructions; 0 differing positions.
- fa_nanddrv_ParseCreateNANDFile: directory success branch contains buffer reset. 130/130 instructions; 11 differing positions.
- fa_nanddrv_ParseCreateNANDFile: explicit failure and success arms. 130/130 instructions; 10 differing positions.
- fa_nanddrv_ParseCreateNANDFile: explicit failure arm and break after success arm. 130/130 instructions; 10 differing positions.
- fa_nanddrv_NotifyNANDFile: declare record after index. 72/72 instructions; 6 differing positions.
- fa_nanddrv_NotifyNANDFile: use record field for empty disk and size store. 72/72 instructions; 15 differing positions.
- fa_nanddrv_NotifyNANDFile: record indexed before loop body rather than saved local. 72/72 instructions; 0 differing positions.

NAND full gate: PASS, instruction exact 15 -> 17/18, code 5444 -> 6432/6952, data 5696/5696, zero regressions, correct DOL SHA1. Notify uses direct indexed fields; physical_write uses source declaration ordering.
- pfd_sddrv_store_fat32_bpb_buf: constant field offsets use word index quotient plus remainder. 374/370 instructions; 354 differing positions.
- pfd_sddrv_store_fat32_bpb_buf: validate both pointers and write signature bytes. 370/370 instructions; 8 differing positions.
- pfd_sddrv_store_fat32_bpb_buf: declare table pointer after requested sector count. 370/370 instructions; 0 differing positions.
- pfd_sddrv_store_bpb_buf: word-index endian macro instead of direct unaligned pointer. 327/327 instructions; 8 differing positions.
- pfd_sddrv_store_bpb_buf: initialize table before requested count. 327/327 instructions; 8 differing positions.
- pfd_sddrv_store_bpb_buf: table pointer declared after sector count. 327/327 instructions; 0 differing positions.

SD BPB full gate: PASS, exact 10 -> 12/26, code 2100 -> 4888/11752, zero regressions. Target endian stores use word-index quotient plus remainder: BPB serial byte offset 39 stores at word offset 48, FAT32 serial 67 stores at 76, MBR first sector 454 stores at 460. Field offsets come from offsetof, with no pinned addresses.
- pfd_sddrv_build_fat32_mbr_bpb: cast reserved buffer null comparison to integer. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: use struct pointer for reserved buffer helper. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: reserved sector builder has unconditional success as target inline path. 216/222 instructions; 100 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: reserved sector helper wraps success in positive pointer branch. 230/222 instructions; 122 differing positions.
- pfd_sddrv_store_fat32_mbr_buf: validate buffers and preserve signature bytes and table register. 204/207 instructions; 147 differing positions.
- pfd_sddrv_store_fat32_mbr_buf: saturated CHS branches first and total count bound before decrement. 207/207 instructions; 15 differing positions.
- pfd_sddrv_store_fat32_mbr_buf: declare end CHS before start CHS in sector head order. 207/207 instructions; 23 differing positions.
- pfd_sddrv_store_fat32_mbr_buf: partition type then start and end CHS declarations. 207/207 instructions; 0 differing positions.
- pfd_sddrv_store_mbr_buf: word-index stores and table pointer declaration follows request. 202/202 instructions; 36 differing positions.
- pfd_sddrv_store_mbr_buf: declare CHS values in target allocation order. 202/202 instructions; 20 differing positions.
- pfd_sddrv_store_mbr_buf: compute end cylinder before start cylinder. 202/202 instructions; 20 differing positions.
- pfd_sddrv_calc_mbr_bpb: recompute fixed sectors after convergence and order table locals. 171/173 instructions; 81 differing positions.
- pfd_sddrv_calc_mbr_bpb: DOS date and time low bits before high bits. 171/173 instructions; 81 differing positions.
- pfd_sddrv_calc_mbr_bpb: cluster size local before FAT arithmetic locals. 171/173 instructions; 76 differing positions.
- pfd_get_media_drv_char: count and output pointer before partition; index before volume. 69/70 instructions; 22 differing positions.
- pfd_get_media_drv_char: volume counter advance at loop tail. 69/70 instructions; 31 differing positions.
- pfd_get_media_drv_char: do while volume traversal. 58/70 instructions; 58 differing positions.
- pfd_get_media_drv_char: while volume traversal with post increment condition. 69/70 instructions; 32 differing positions.
- pfd_sddrv_init: SDK integer pointer tests and insertion status truth tests. 143/144 instructions; 138 differing positions.
- pfd_sddrv_init: state access through local struct pointer. 138/144 instructions; 141 differing positions.
- pfd_sddrv_init: initialize state pointer after local declarations. 138/144 instructions; 141 differing positions.
- pfd_sddrv_init: initialized device null comparison and explicit wrong-disk return first. 145/144 instructions; 135 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: reread format total at output and table pointer follows request. 133/133 instructions; 33 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: 16-bit DOS date and time with low fields first. 133/133 instructions; 33 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: cluster size declared ahead of cluster and FAT arithmetic. 133/133 instructions; 31 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: declare arithmetic locals in cluster size FAT count available FAT size order. 133/133 instructions; 15 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: snapshot calendar fields before composing DOS date and time. 133/133 instructions; 15 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: compose low-bit-first time before date and add time first. 133/133 instructions; 15 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: 32-bit intermediates for calendar serial. 133/133 instructions; 15 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: time declared before date. 133/133 instructions; 15 differing positions.
- pfd_sddrv_physical_read: sector parameter used directly on aligned path. 127/127 instructions; 2 differing positions.
- pfd_sddrv_physical_read: sector local initialized at declaration. 127/127 instructions; 22 differing positions.
- pfd_sddrv_physical_read: sector copy only initialized for unaligned loop. 127/127 instructions; 43 differing positions.
- pfd_sddrv_physical_write: sector parameter used directly on aligned path. 127/127 instructions; 2 differing positions.
- pfd_sddrv_physical_write: sector local initialized at declaration. 127/127 instructions; 22 differing positions.
- pfd_sddrv_physical_write: sector copy only initialized for unaligned loop. 127/127 instructions; 43 differing positions.
- pfd_sddrv_get_disk_info: split disk and geometry pointer validation. 100/96 instructions; 90 differing positions.
- pfd_sddrv_get_disk_info: read driver state through local pointer. 98/96 instructions; 21 differing positions.
- pfd_sddrv_get_disk_info: clear geometry fields through ordinary local aliases. 98/96 instructions; 2 differing positions.
- pfd_sddrv_get_total_sectors: reuse card capacity after multiplying by block count. 80/80 instructions; 14 differing positions.
- pfd_sddrv_get_total_sectors: clamp and subtract in sector multiplier itself. 77/80 instructions; 46 differing positions.
- pfd_sddrv_get_total_sectors: declare final multiplier before block size. 77/80 instructions; 46 differing positions.
- pfd_st_inter_callback: integer pointer and function pointer presence checks. 65/69 instructions; 55 differing positions.
- pfd_st_inter_callback: read state through struct pointer initialized locally. 64/69 instructions; 43 differing positions.
- pfd_st_inter_callback: inline media drive discovery directly in callback. 65/69 instructions; 55 differing positions.
- pfd_st_removal_callback: integer pointer and function pointer presence checks. 62/66 instructions; 53 differing positions.
- pfd_st_removal_callback: read state through struct pointer initialized locally. 63/66 instructions; 40 differing positions.
- pfd_st_removal_callback: inline media drive discovery directly in callback. 62/66 instructions; 53 differing positions.
- pfd_sddrv_finalize: mounted bit truth check and ordinary direct clear. 57/57 instructions; 42 differing positions.
- pfd_sddrv_finalize: state access through struct pointer. 54/57 instructions; 54 differing positions.
- pfd_sddrv_finalize: clear insertion and ejection separately after device cleanup. 58/57 instructions; 19 differing positions.
- pfd_sddrv_unmount: clear mounted bit directly at use. 12/13 instructions; 9 differing positions.
- pfd_sddrv_unmount: state access through struct pointer. 13/13 instructions; 10 differing positions.
- pfd_sddrv_unmount: subtract mounted bit when known set. 12/13 instructions; 9 differing positions.
- fa_nanddrv_ParseCreateNANDFile: advance parser after accepted directory-change branch rather than inside it. 130/130 instructions; 0 differing positions.

NAND parser full gate: PASS, exact 18/18, code 6952/6952, data 5696/5696, zero regressions, correct DOL SHA1. All NAND functions are now 100.0 percent objdiff and instruction exact.
- pfd_sddrv_get_total_sectors: cluster count declared before encoded card size. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: calculate cluster count directly from register bits. 80/80 instructions; 19 differing positions.
- pfd_sddrv_get_total_sectors: declare card size in block scope before computing count. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: factor sector shift clamping into an inline accessor. 80/80 instructions; 10 differing positions.

## Final open functions

- pfd_get_media_drv_char: 96.34286%; one missing unrolled-loop induction increment and register allocation; 9 logged attempts.
- pfd_st_inter_callback: 93.840576%; four missing global-field reloads around inline access and callback dispatch; 3 logged attempts.
- pfd_st_removal_callback: 90.30303%; four missing global-field reloads around inline access and callback dispatch; 3 logged attempts.
- pfd_sddrv_init: 90.27778%; global reloads, pointer-comparison lowering, initialization store scheduling; 4 logged attempts.
- pfd_sddrv_unmount: 90.0%; compiler reuses flags after the condition; target reloads the same field; 3 logged attempts.
- pfd_sddrv_finalize: 92.89474%; flag reload and final state-clear scheduling; 3 logged attempts.
- pfd_sddrv_get_disk_info: 97.916664%; target symbol size omits the final stack restore and blr; first 96 instructions match; 3 logged attempts.
- pfd_sddrv_physical_read: 99.92126%; two moves use incoming r5 instead of saved sector r28; 3 logged attempts.
- pfd_sddrv_physical_write: 99.92126%; two moves use incoming r5 instead of saved sector r28; 3 logged attempts.
- pfd_sddrv_get_total_sectors: 96.9875%; capacity and clamp-register allocation plus constant-load scheduling; 7 logged attempts.
- pfd_sddrv_calc_mbr_bpb: 92.699425%; fixed-sector recomputation, calendar-expression scheduling, register allocation; 3 logged attempts.
- pfd_sddrv_store_mbr_buf: 95.17326%; CHS arithmetic scheduling and register allocation; 3 logged attempts.
- pfd_sddrv_calc_fat32_mbr_bpb: 89.947365%; format-total reload and arithmetic/calendar register allocation; 8 logged attempts.
- pfd_sddrv_build_fat32_mbr_bpb: 94.75225%; reserved-sector helper null/error branch and argument scheduling; 4 logged attempts.

## Before -> after

- pfd_cmn: instruction exact 0 -> 0/1; fuzzy 96.3429 -> 96.3429; code 0 -> 0/280; data 0 -> 0.
- nand_drv: instruction exact 15 -> 18/18; fuzzy 99.7353 -> 100.0000; code 5444 -> 6952/6952; data 5696 -> 5696/5696.
- msc_drv: instruction exact 2 -> 2/2; fuzzy 100.0000 -> 100.0000; code 20 -> 20/20; data 8 -> 8/8.
- sd_drv: instruction exact 10 -> 13/26; fuzzy 95.2730 -> 97.2087; code 2100 -> 5716/11752; data 408 -> 408/3592.

Only NAND and SD source changes remain. All unsuccessful experiments were restored. No other translation unit changed output. Matching siblings in vf/develop were inspected; their per-device storage and VF adapters differ from these FA global drivers.

Uncertainty: get_disk_info has a target symbol size of 0x180 while its successor starts 0x188 later. The intervening target bytes restore r1 and return; no symbol/config edits were made. The SD BSS symbol-size and data-tail alignment differences remain open; no padding was added.

## Final full gate over all four units

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/driver/pfd_cmn] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/pfd_cmn] objdiff: code None/280 data None/None functions 0/1 fuzzy 96.3429 linked code 0
[libs/RVL_SDK/src/fa/driver/pfd_cmn] instruction-exact functions: 0/1
[libs/RVL_SDK/src/fa/driver/pfd_cmn]   section .text size 280 match 96.34286
[libs/RVL_SDK/src/fa/driver/pfd_cmn]   below 100: pfd_get_media_drv_char 96.34286
[libs/RVL_SDK/src/fa/driver/pfd_cmn] baseline: code None/280 data None functions 0 fuzzy 96.3429
[libs/RVL_SDK/src/fa/driver/nand_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/nand_drv] objdiff: code 6952/6952 data 5696/5696 functions 18/18 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/driver/nand_drv] instruction-exact functions: 18/18
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .bss size 5624 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .rodata size 32 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .sbss size 32 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .text size 6952 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv] baseline: code 5444/6952 data 5696 functions 15 fuzzy 99.7353
[libs/RVL_SDK/src/fa/driver/msc_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/msc_drv] objdiff: code 20/20 data 8/8 functions 2/2 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/driver/msc_drv] instruction-exact functions: 2/2
[libs/RVL_SDK/src/fa/driver/msc_drv]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/fa/driver/msc_drv]   section .text size 20 match 100.0
[libs/RVL_SDK/src/fa/driver/msc_drv] baseline: code 20/20 data 8 functions 2 fuzzy 100.0000
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 5716/11752 data 408/3592 functions 13/26 fuzzy 97.2087 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 13/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 97.36842
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 99.96117
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 97.20865
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_inter_callback 93.840576
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_removal_callback 90.30303
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 90.27778
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_unmount 90.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.89474
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_disk_info 97.916664
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_read 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_write 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 96.9875
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_calc_mbr_bpb 92.699425
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 95.17326
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_calc_fat32_mbr_bpb 89.947365
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 2100/11752 data 408 functions 10 fuzzy 95.2730
regressions vs baseline: 0
global matched_code_percent: 85.42374 -> 85.59482
global fuzzy_match_percent: 98.51842 -> 98.52665
global complete_code_percent: 59.81479 -> 59.81479
global matched_data_percent: 90.78073 -> 90.78073
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
