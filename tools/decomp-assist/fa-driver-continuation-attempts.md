# FA driver continuation attempts

Baseline pools identical for all four units. Each trial builds only its owned object. Failed experiments are restored.

- pfd_sddrv_physical_read: advance sector argument directly in fallback loop. 127/127 instructions; 40 differing positions.
- pfd_sddrv_physical_read: scope fallback sector and iteration variables to unaligned branch. 127/127 instructions; 43 differing positions.
- pfd_sddrv_physical_read: inline block transfer accessor reads sector by address. 127/127 instructions; 2 differing positions.
- pfd_sddrv_physical_write: advance sector argument directly in fallback loop. 127/127 instructions; 40 differing positions.
- pfd_sddrv_physical_write: scope fallback sector and iteration variables to unaligned branch. 127/127 instructions; 43 differing positions.
- pfd_sddrv_physical_write: inline block transfer accessor reads sector by address. 127/127 instructions; 2 differing positions.
- pfd_sddrv_get_disk_info: combine mutually exclusive geometry zero assignments. 98/96 instructions; 4 differing positions.
- pfd_sddrv_get_disk_info: check memory type with one mask. 96/96 instructions; 45 differing positions.
- pfd_sddrv_get_disk_info: give successful geometry status a common return variable. 98/96 instructions; 11 differing positions.
- pfd_sddrv_get_total_sectors: keep the two clamped exponents in nested expression. 82/80 instructions; 38 differing positions.
- pfd_sddrv_get_total_sectors: write capacity first and multiply through output field after clamp. 83/80 instructions; 44 differing positions.
- pfd_sddrv_get_total_sectors: compute block count after exponent clamp. 80/80 instructions; 23 differing positions.
- pfd_sddrv_get_total_sectors: use unsigned long unit for final sector multiplier. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: use unsigned unit for both CSD shifts. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: give first shift unsigned long width. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: give clamped exponent signed 16-bit representation. 80/80 instructions; 12 differing positions.
- pfd_sddrv_store_mbr_buf: snapshot start and end sector values for CHS calculation. 202/202 instructions; 30 differing positions.
- pfd_sddrv_store_mbr_buf: separate cylinder quotient and remainder before narrowing CHS fields. 202/202 instructions; 30 differing positions.
- pfd_sddrv_store_mbr_buf: complete end CHS before start CHS. 202/202 instructions; 24 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: declare reserved boot sector helper inline. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: direct struct signature writes without a cached boot pointer. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: local partition start snapshot before writing BPB. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: translate inline reserved-sector construction in caller. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: pass first array element explicitly to reserved-sector builder. 230/222 instructions; 122 differing positions.
- pfd_sddrv_build_fat32_mbr_bpb: use one common return from reserved-sector builder. 230/222 instructions; 122 differing positions.
- pfd_st_inter_callback: read device disk and drive through small inline accessors. 65/69 instructions; 55 differing positions.
- pfd_st_inter_callback: test through const state pointer and read globals at calls. 71/69 instructions; 65 differing positions.
- pfd_st_inter_callback: snapshot device and drive for each callback dispatch. 65/69 instructions; 55 differing positions.
- pfd_st_removal_callback: read device disk and drive through small inline accessors. 62/66 instructions; 53 differing positions.
- pfd_st_removal_callback: test through const state pointer and read globals at calls. 68/66 instructions; 62 differing positions.
- pfd_st_removal_callback: snapshot device and drive for each callback dispatch. 62/66 instructions; 53 differing positions.
- pfd_sddrv_finalize: translate target cleanup: preserve ejected state and test mounted flag as truth. 56/57 instructions; 50 differing positions.
- pfd_sddrv_finalize: clear initialized flag through local state pointer. 56/57 instructions; 50 differing positions.
- pfd_sddrv_finalize: group final state stores through state pointer. 56/57 instructions; 50 differing positions.
- pfd_sddrv_unmount: test mounted state through inline flag accessor. 12/13 instructions; 9 differing positions.
- pfd_sddrv_unmount: alias flags through named struct field pointer. 14/13 instructions; 13 differing positions.
- pfd_sddrv_unmount: test through const state pointer and clear global field directly. 14/13 instructions; 13 differing positions.
- pfd_sddrv_init: retranslate unsigned null and inserted truth tests. 143/144 instructions; 138 differing positions.
- pfd_sddrv_init: return initial-disk errors through a shared result. 141/144 instructions; 141 differing positions.
- pfd_sddrv_init: read initialized device from driver state for intr registration. 143/144 instructions; 138 differing positions.
- pfd_st_inter_callback: define driver state after functions using ordinary extern declarations. 65/69 instructions; 55 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: translate arithmetic locals and date before time low-bit fields. 133/133 instructions; 15 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: pack DOS fields through small calendar accessors. 133/133 instructions; 15 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: represent serial as date and time bit fields. 132/133 instructions; 37 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: interleave date and time field composition. 135/133 instructions; 28 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: declare DOS date and time as 16 bit encoded values. 133/133 instructions; 15 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: keep date as a signed 16-bit DOS value. 133/133 instructions; 15 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: shift date and accumulate into time. 133/133 instructions; 15 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: assemble date around the month and year fields. 133/133 instructions; 14 differing positions.
- pfd_sddrv_calc_mbr_bpb: derive converged data region from stored FAT field. 173/173 instructions; 44 differing positions.
- pfd_sddrv_calc_mbr_bpb: snapshot final partition capacity before field stores. 169/173 instructions; 77 differing positions.
- pfd_sddrv_calc_mbr_bpb: read cluster count and remainder directly from format fields. 171/173 instructions; 81 differing positions.
- pfd_get_media_drv_char: put both volume inductions in for increment with count pointer partition declaration order. 69/70 instructions; 31 differing positions.
- pfd_get_media_drv_char: initialize volume pointer alongside index and advance both at loop tail. 69/70 instructions; 31 differing positions.
- pfd_get_media_drv_char: use explicit next-partition exit from bounded volume scan. 69/70 instructions; 22 differing positions.
- pfd_get_media_drv_char: skip unmatched volumes with continue and advance both loop variables. 69/70 instructions; 31 differing positions.
- pfd_get_media_drv_char: bounded volume index is a 16-bit value. 70/70 instructions; 21 differing positions.
- pfd_get_media_drv_char: bound indexed volumes without caching an advancing pointer. 69/70 instructions; 36 differing positions.
- pfd_get_media_drv_char: advance 16-bit volume index in for increment. 70/70 instructions; 0 differing positions.
- pfd_get_media_drv_char: advance 16-bit volume index after conditional match. 70/70 instructions; 0 differing positions.
- pfd_get_media_drv_char: advance volume pointer before 16-bit index at loop tail. 70/70 instructions; 0 differing positions.

## pfd_cmn full gate

The 16-bit volume index keeps both increments in the compiler-unrolled loop. Declaring count, output pointer, partition, index, and volume in that order also matches allocation. All 70 instructions match; no data sections exist. pool_diff.py cannot read this object without .data; gate reports IDENTICAL.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/driver/pfd_cmn] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/pfd_cmn] objdiff: code 280/280 data None/None functions 1/1 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/driver/pfd_cmn] instruction-exact functions: 1/1
[libs/RVL_SDK/src/fa/driver/pfd_cmn]   section .text size 280 match 100.0
[libs/RVL_SDK/src/fa/driver/pfd_cmn] baseline: code None/280 data None functions 0 fuzzy 96.3429
regressions vs baseline: 0
global matched_code_percent: 85.59482 -> 85.60416
global fuzzy_match_percent: 98.54022 -> 98.54056
global complete_code_percent: 59.81479 -> 59.81479
global matched_data_percent: 90.85319 -> 90.85319
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- pfd_sddrv_calc_fat32_mbr_bpb: pass calendar fields to serial encoder. 133/133 instructions; 0 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: encode fields with 16-bit intermediates. 133/133 instructions; 0 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: declare time before date in serial encoder. 133/133 instructions; 0 differing positions.
- pfd_sddrv_calc_fat32_mbr_bpb: encode unsigned calendar components. 133/133 instructions; 0 differing positions.
- pfd_sddrv_calc_mbr_bpb: shared serial encoder with converged FAT field access. 173/173 instructions; 29 differing positions.
- pfd_sddrv_calc_mbr_bpb: arithmetic locals in cluster start reserve total FAT bits fixed partition order. 173/173 instructions; 9 differing positions.
- pfd_sddrv_calc_mbr_bpb: move current start before cluster size. 173/173 instructions; 9 differing positions.
- pfd_sddrv_calc_mbr_bpb: declare current start last. 173/173 instructions; 9 differing positions.
- pfd_sddrv_calc_mbr_bpb: reverse arithmetic local order. 173/173 instructions; 27 differing positions.
- pfd_sddrv_calc_mbr_bpb: partition and fixed region before FAT calculation. 173/173 instructions; 34 differing positions.
- pfd_sddrv_calc_mbr_bpb: retain cluster size as 32-bit arithmetic operand. 173/173 instructions; 9 differing positions.
- pfd_sddrv_calc_mbr_bpb: use signed current start for positive partition calculation. 173/173 instructions; 9 differing positions.
- pfd_sddrv_calc_mbr_bpb: reuse reserved-sector multiple without a separate current start. 170/173 instructions; 104 differing positions.
- pfd_sddrv_calc_mbr_bpb: declare current start at its first loop use. 173/173 instructions; 9 differing positions.
- pfd_sddrv_calc_mbr_bpb: cluster size first among all locals. 173/173 instructions; 9 differing positions.
- pfd_sddrv_calc_mbr_bpb: cluster size declared next to calculated cluster count. 173/173 instructions; 34 differing positions.
- pfd_sddrv_calc_mbr_bpb: cluster size declared after reserved count. 173/173 instructions; 34 differing positions.
- pfd_sddrv_calc_mbr_bpb: declare reserved multiple before the loop counters. 173/173 instructions; 9 differing positions.
- pfd_sddrv_calc_mbr_bpb: declare cluster count before the geometry arithmetic. 173/173 instructions; 9 differing positions.
- pfd_sddrv_calc_mbr_bpb: declare initial reservation count before cluster size. 173/173 instructions; 9 differing positions.

## SD serial encoder full gate

A shared inline serial encoder accepts the six calendar fields, preserving the SDK date/year and raw-second encoding. FAT32 calculation now matches all 133 instructions. FAT12/16 reads the converged FAT field and matches 173 instructions with nine remaining register differences.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 6248/11752 data 408/3592 functions 14/26 fuzzy 98.0766 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 14/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 97.36842
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 99.96117
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 98.076584
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_inter_callback 93.840576
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_removal_callback 90.30303
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 90.27778
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_unmount 90.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.89474
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_disk_info 97.916664
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_read 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_write 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 96.9875
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_calc_mbr_bpb 99.71098
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 95.17326
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 5716/11752 data 408 functions 13 fuzzy 97.2087
regressions vs baseline: 0
global matched_code_percent: 85.59482 -> 85.62193
global fuzzy_match_percent: 98.54022 -> 98.54395
global complete_code_percent: 59.81479 -> 59.81479
global matched_data_percent: 90.85319 -> 90.85319
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- pfd_sddrv_calc_mbr_bpb: read cluster size from settings at every arithmetic use. 174/173 instructions; 118 differing positions.
- pfd_sddrv_calc_mbr_bpb: read cluster size from format field at every arithmetic use. 173/173 instructions; 0 differing positions.
- pfd_sddrv_calc_mbr_bpb: read total sectors from format field in cluster iteration. 173/173 instructions; 17 differing positions.
- pfd_sddrv_calc_mbr_bpb: compute first reserved multiple with a separate initial cursor. 173/173 instructions; 0 differing positions.
- pfd_sddrv_calc_mbr_bpb: compute selected partition start directly from reserved count. 173/173 instructions; 14 differing positions.

## SD FAT12/16 calculation full gate

Reading cluster size through the format field at each arithmetic use matches the remaining nine register differences. All 173 instructions now match; FAT32 retains 133/133 with zero differences. Removed the caller calendar intermediates that the new helper replaced.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 6940/11752 data 408/3592 functions 15/26 fuzzy 98.0936 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 15/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 97.36842
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 99.96117
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 98.0936
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_inter_callback 93.840576
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_removal_callback 90.30303
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 90.27778
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_unmount 90.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.89474
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_disk_info 97.916664
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_read 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_write 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 96.9875
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 95.17326
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 5716/11752 data 408 functions 13 fuzzy 97.2087
regressions vs baseline: 0
global matched_code_percent: 85.59482 -> 85.64503
global fuzzy_match_percent: 98.54022 -> 98.54402
global complete_code_percent: 59.81479 -> 59.81479
global matched_data_percent: 90.85319 -> 90.85319
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- pfd_sddrv_store_mbr_buf: use shared CHS calculator for start and end geometry. 202/202 instructions; 26 differing positions.
- pfd_sddrv_store_mbr_buf: calculate ending CHS before starting CHS through helper. 202/202 instructions; 25 differing positions.
- pfd_sddrv_store_mbr_buf: compute cylinder and head together before track sector. 202/202 instructions; 23 differing positions.
- pfd_sddrv_get_total_sectors: decode standard CSD capacity through scalar field accessor. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: declare block count before encoded size in scalar decoder. 80/80 instructions; 10 differing positions.
- pfd_sddrv_get_total_sectors: decode multiplier fields before computing capacity product. 80/80 instructions; 23 differing positions.
- pfd_sddrv_finalize: clear only insertion state as in target epilogue. 57/57 instructions; 11 differing positions.
- pfd_sddrv_finalize: scope initialized-flag update with media reset pointer. 57/57 instructions; 11 differing positions.
- pfd_sddrv_finalize: clear insertion state before initialized flag. 57/57 instructions; 16 differing positions.
- pfd_sddrv_store_mbr_buf: use canonical start and end CHS declaration order. 202/202 instructions; 20 differing positions.
- pfd_sddrv_finalize: validate target insertion-only reset against objdiff. 57/57 instructions; 11 differing positions.
- pfd_sddrv_store_mbr_buf: calculate head sector cylinder in partition byte order. 202/202 instructions; 18 differing positions.
- pfd_sddrv_store_mbr_buf: translate end geometry before start with head-first helper. 202/202 instructions; 23 differing positions.
- pfd_sddrv_store_mbr_buf: partition helper computes cylinders before heads and sectors. 202/202 instructions; 23 differing positions.

## Data inspection

The original and source .data bytes agree at every shared position, and all 46 pooled strings retain their offsets and token order. The source ends at 2574 bytes; the extracted target has two more zero bytes at 2576. An isolated compile using the compiler's ordinary `-str reuse,pool` option produced 2492 bytes and changed string offsets, so that option was rejected; configure.py is unchanged. No literal terminators, named string buffers, or placement attributes were added.

The BSS is 608 zero bytes in both objects. The source state record symbol is 28 bytes; the extracted target assigns it 32 bytes up to the next record at offset 32. Device storage and transfer buffer retain offsets 32 and 96 and sizes 64 and 512. The source .sbss has twelve bytes of actual globals; the extracted section is forty bytes, with the event at offset 32. Gate normalizes .sbss as 100%. The function table and fourteen-entry size table in .rodata remain 100%. Extra record members or alignment added just to reproduce extracted padding would not be justified by the available source evidence, so none were added.

## Restored experiments

The target finalizer resets inserted state without resetting ejected state. The insertion-only experiment matched instruction count but fell to 88.42105% from 92.89474%, so it was restored. Its flag load and bit comparison still differ. Physical transfers still differ only in two argument moves after three new source forms. The disk-info target symbol still omits stack restoration and return, while its first 96 instructions match. No symbol/config boundaries were changed.

All eleven remaining SD functions have at least three new distinct source-level attempts in this continuation. The table and CHS declaration order improvement is retained; speculative helpers are restored.

## Final full gate over all four units

CHS declaration order raises store_mbr_buf from 95.17326% to 95.84158%; its 202 instructions still have twenty scheduling/allocation differences.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/fa/driver/pfd_cmn] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/pfd_cmn] objdiff: code 280/280 data None/None functions 1/1 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/driver/pfd_cmn] instruction-exact functions: 1/1
[libs/RVL_SDK/src/fa/driver/pfd_cmn]   section .text size 280 match 100.0
[libs/RVL_SDK/src/fa/driver/pfd_cmn] baseline: code None/280 data None functions 0 fuzzy 96.3429
[libs/RVL_SDK/src/fa/driver/nand_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/nand_drv] objdiff: code 6952/6952 data 5696/5696 functions 18/18 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/driver/nand_drv] instruction-exact functions: 18/18
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .bss size 5624 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .rodata size 32 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .sbss size 32 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv]   section .text size 6952 match 100.0
[libs/RVL_SDK/src/fa/driver/nand_drv] baseline: code 6952/6952 data 5696 functions 18 fuzzy 100.0000
[libs/RVL_SDK/src/fa/driver/msc_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/msc_drv] objdiff: code 20/20 data 8/8 functions 2/2 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/fa/driver/msc_drv] instruction-exact functions: 2/2
[libs/RVL_SDK/src/fa/driver/msc_drv]   section .sbss size 8 match 100.0
[libs/RVL_SDK/src/fa/driver/msc_drv]   section .text size 20 match 100.0
[libs/RVL_SDK/src/fa/driver/msc_drv] baseline: code 20/20 data 8 functions 2 fuzzy 100.0000
[libs/RVL_SDK/src/fa/driver/sd_drv] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/sd_drv] objdiff: code 6940/11752 data 408/3592 functions 15/26 fuzzy 98.1395 linked code 0
[libs/RVL_SDK/src/fa/driver/sd_drv] instruction-exact functions: 15/26
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .bss size 608 match 97.36842
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .data size 2576 match 99.96117
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .rodata size 368 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .sbss size 40 match 100.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   section .text size 11760 match 98.13955
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_inter_callback 93.840576
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_removal_callback 90.30303
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 90.27778
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_unmount 90.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.89474
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_disk_info 97.916664
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_read 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_write 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 96.9875
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 95.84158
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 94.75225
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 5716/11752 data 408 functions 13 fuzzy 97.2087
regressions vs baseline: 0
global matched_code_percent: 85.59482 -> 85.64503
global fuzzy_match_percent: 98.54022 -> 98.54421
global complete_code_percent: 59.81479 -> 59.81479
global matched_data_percent: 90.85319 -> 90.85319
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
