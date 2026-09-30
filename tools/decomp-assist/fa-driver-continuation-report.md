# FA driver continuation report

pfd_cmn: exact 0 -> 1/1; fuzzy 96.3429 -> 100.0000; matched code 0 -> 280/280; matched data 0 -> 0.
nand_drv: exact 18 -> 18/18; fuzzy 100.0000 -> 100.0000; matched code 6952 -> 6952/6952; matched data 5696 -> 5696/5696.
msc_drv: exact 2 -> 2/2; fuzzy 100.0000 -> 100.0000; matched code 20 -> 20/20; matched data 8 -> 8/8.
sd_drv: exact 13 -> 15/26; fuzzy 97.2087 -> 98.1395; matched code 5716 -> 6940/11752; matched data 408 -> 408/3592.

## Remaining functions

pfd_st_inter_callback: 93.840576%; four global-field reloads are coalesced by the compiler; 4 new logged attempts.
pfd_st_removal_callback: 90.30303%; four global-field reloads are coalesced by the compiler; 3 new logged attempts.
pfd_sddrv_init: 90.27778%; global reloads, null comparison lowering, and state-store scheduling; 3 new logged attempts.
pfd_sddrv_unmount: 90.0%; flags are reused after the condition; target reads them again; 3 new logged attempts.
pfd_sddrv_finalize: 92.89474%; flag reload, mounted comparison, and final state-store scheduling; 7 new logged attempts.
pfd_sddrv_get_disk_info: 97.916664%; target symbol excludes two epilogue instructions; first 96 instructions match; 3 new logged attempts.
pfd_sddrv_physical_read: 99.92126%; two argument moves use incoming r5 instead of saved r28; 3 new logged attempts.
pfd_sddrv_physical_write: 99.92126%; two argument moves use incoming r5 instead of saved r28; 3 new logged attempts.
pfd_sddrv_get_total_sectors: 96.9875%; capacity and multiplier allocation plus constant-load scheduling; 10 new logged attempts.
pfd_sddrv_store_mbr_buf: 95.84158%; twenty CHS arithmetic scheduling/allocation differences; 10 new logged attempts.
pfd_sddrv_build_fat32_mbr_bpb: 94.75225%; reserved-sector null/error branches and one argument-load ordering; 230/222 instructions; 6 new logged attempts.

## Changes and source commits

libs/RVL_SDK/src/fa/driver/pfd_cmn.c: 70f61263 (bounded 16-bit volume index and loop/declaration order).
libs/RVL_SDK/src/fa/driver/sd_drv.c: a5f9eb19 (FAT32 geometry and scalar calendar encoder), 12e6be48 (direct format-field reads for FAT12/16), 4c9e0b18 (CHS declaration order).
tools/decomp-assist/fa-driver-continuation-attempts.md: per-function trials, measurements, restored experiments, data evidence, and gates.
tools/decomp-assist/fa-driver-continuation-report.md: this report and every gate block.

## Data and uncertainty

All 46 strings retain identical offsets and token order. Source .data is 2574 bytes; target is 2576 with two terminal zero bytes. Ordinary compiler string pooling was tested separately and rejected because it produced 2492 bytes with changed offsets. The BSS is 608 zero bytes in both objects, but the extracted state symbol is 32 bytes versus the source struct's 28. .rodata and normalized .sbss remain 100%. Source .sbss has twelve bytes of actual globals versus forty extracted bytes. No invented fields, padding, alignment, or placement changes were made. The original state layout and section-tail emission remain uncertain.

get_disk_info's target symbol is 0x180 bytes despite its next function starting 0x188 bytes later. The omitted bytes are stack restoration and blr. No symbol sizes were changed. An insertion-only finalize cleanup agreed with the observed target store but scored worse because its flag handling still differed, so that experiment was restored.

Three functions newly reach 100%: pfd_get_media_drv_char, pfd_sddrv_calc_mbr_bpb, pfd_sddrv_calc_fat32_mbr_bpb. Eleven SD functions and the data limitations remain open; every open function has at least three distinct new attempts. No Matching flags or shared headers changed. Final full gate reports zero regressions, zero forbidden patterns, and zero readability warnings.

## Every gate block

### Baseline (quick)

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
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
[libs/RVL_SDK/src/fa/driver/sd_drv] baseline: code 5716/11752 data 408 functions 13 fuzzy 97.2087
[libs/RVL_SDK/src/fa/driver/pfd_cmn] pool: IDENTICAL
[libs/RVL_SDK/src/fa/driver/pfd_cmn] objdiff: code None/280 data None/None functions 0/1 fuzzy 96.3429 linked code 0
[libs/RVL_SDK/src/fa/driver/pfd_cmn] instruction-exact functions: 0/1
[libs/RVL_SDK/src/fa/driver/pfd_cmn]   section .text size 280 match 96.34286
[libs/RVL_SDK/src/fa/driver/pfd_cmn]   below 100: pfd_get_media_drv_char 96.34286
[libs/RVL_SDK/src/fa/driver/pfd_cmn] baseline: code None/280 data None functions 0 fuzzy 96.3429
regressions vs baseline: 0
global matched_code_percent: 85.59482 -> 85.59482
global fuzzy_match_percent: 98.54022 -> 98.54022
global complete_code_percent: 59.81479 -> 59.81479
global matched_data_percent: 90.85319 -> 90.85319
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### pfd_cmn (full)

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

### SD serial encoder (full)

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

### SD FAT12/16 geometry (full)

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

### Final all four units (full)

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

