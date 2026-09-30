# Remaining FA attempts

FAAttach: signed then unsigned drive index: 125/125 instructions, saved-register differences remain. Direct repeated drive indexing: 136/125. A separate drive temporary: 128/125. Restored signed index (99.36%).
pfd_get_media_drv_char: cursor enumeration baseline 69/70. Moving count/next-drive initialization after validation changed allocation. Indexed volume lookup and reversing declaration order changed allocation but retained 69/70. Incrementing index inside the loop retained 69/70; no artificial second increment added.
pfstub_entry: signed operation ranges 88/89. Unsigned ranges 85/89. Using received for the second range restored 88/89; compiler still reuses operation rather than reloading it.
uhf_msc_blk_pread/pwrite: ternary transfer count plus early error return: 123/129. Explicit halfword selection and an error-result loop changed branch scheduling. Success-first loop with explicit final break: 127/129. Sense switch and reversed cacheable branch raised fuzzy matching but leave error exits and allocation different.
FAInit: code exact; version pointer's extracted .sdata symbol includes four trailing zero bytes. A scalar version pointer matches the code. The extra zero word has no proven source meaning; no padding introduced.
pfd_st_inter_callback: baseline src 0x104 base 0x114 insns 65/69; 7 difference groups
  truth tests in place of zero comparisons: src 0x104 base 0x114 insns 65/69; 7 difference groups
  scope the final success result: src 0x104 base 0x114 insns 65/69; 7 difference groups
pfd_st_removal_callback: baseline src 0xf8 base 0x108 insns 62/66; 7 difference groups
  truth tests in place of zero comparisons: src 0xf8 base 0x108 insns 62/66; 7 difference groups
  scope the final success result: src 0xf8 base 0x108 insns 62/66; 7 difference groups
pfd_sddrv_init: baseline src 0x23c base 0x240 insns 143/144; 8 difference groups
  reverse local declaration order: src 0x23c base 0x240 insns 143/144; 14 difference groups
  truth tests in place of zero comparisons: src 0x23c base 0x240 insns 143/144; 8 difference groups
  scope the final success result: src 0x23c base 0x240 insns 143/144; 8 difference groups
pfd_sddrv_unmount: baseline src 0x30 base 0x34 insns 12/13; 1 difference groups
  truth tests in place of zero comparisons: src 0x30 base 0x34 insns 12/13; 1 difference groups
  scope the final success result: src 0x30 base 0x34 insns 12/13; 1 difference groups
pfd_sddrv_finalize: baseline src 0xe4 base 0xe4 insns 57/57; diffs 43
  truth tests in place of zero comparisons: src 0xe4 base 0xe4 insns 57/57; diffs 43
  scope the final success result: src 0xe4 base 0xe4 insns 57/57; diffs 43
pfd_sddrv_get_disk_info: baseline src 0x188 base 0x180 insns 98/96; 1 difference groups
  reverse local declaration order: src 0x188 base 0x180 insns 98/96; 1 difference groups
  truth tests in place of zero comparisons: src 0x188 base 0x180 insns 98/96; 1 difference groups
  scope the final success result: src 0x188 base 0x180 insns 98/96; 1 difference groups
pfd_sddrv_physical_read: baseline src 0x1fc base 0x1fc insns 127/127; diffs 2
  reverse local declaration order: src 0x1fc base 0x1fc insns 127/127; diffs 12
  truth tests in place of zero comparisons: src 0x1fc base 0x1fc insns 127/127; diffs 2
  loop increment order or additive increment: src 0x1fc base 0x1fc insns 127/127; diffs 4
pfd_sddrv_physical_write: baseline src 0x1fc base 0x1fc insns 127/127; diffs 2
  reverse local declaration order: src 0x1fc base 0x1fc insns 127/127; diffs 12
  truth tests in place of zero comparisons: src 0x1fc base 0x1fc insns 127/127; diffs 2
  loop increment order or additive increment: src 0x1fc base 0x1fc insns 127/127; diffs 4
pfd_sddrv_get_total_sectors: baseline src 0x13c base 0x140 insns 79/80; 9 difference groups
  reverse local declaration order: src 0x13c base 0x140 insns 79/80; 7 difference groups
  truth tests in place of zero comparisons: src 0x13c base 0x140 insns 79/80; 9 difference groups
  scope the final success result: src 0x13c base 0x140 insns 79/80; 9 difference groups
pfd_sddrv_calc_mbr_bpb: baseline src 0x3bc base 0x2b4 insns 239/173; 20 difference groups
  reverse local declaration order: src 0x3bc base 0x2b4 insns 239/173; 18 difference groups
  truth tests in place of zero comparisons: src 0x3bc base 0x2b4 insns 239/173; 20 difference groups
  scope the final success result: src 0x3bc base 0x2b4 insns 239/173; 20 difference groups
pfd_sddrv_store_bpb_buf: baseline src 0x3d0 base 0x51c insns 244/327; 39 difference groups
  reverse local declaration order: src 0x3d0 base 0x51c insns 244/327; 40 difference groups
  truth tests in place of zero comparisons: src 0x3d0 base 0x51c insns 244/327; 39 difference groups
  loop increment order or additive increment: src 0x3d0 base 0x51c insns 244/327; 39 difference groups
pfd_sddrv_store_mbr_buf: baseline src 0x26c base 0x328 insns 155/202; 19 difference groups
  reverse local declaration order: src 0x26c base 0x328 insns 155/202; 19 difference groups
  truth tests in place of zero comparisons: src 0x26c base 0x328 insns 155/202; 19 difference groups
  loop increment order or additive increment: src 0x26c base 0x328 insns 155/202; 19 difference groups
pfd_sddrv_calc_fat32_mbr_bpb: baseline src 0x20c base 0x214 insns 131/133; 20 difference groups
  reverse local declaration order: src 0x20c base 0x214 insns 131/133; 19 difference groups
  truth tests in place of zero comparisons: src 0x20c base 0x214 insns 131/133; 20 difference groups
  scope the final success result: src 0x20c base 0x214 insns 131/133; 20 difference groups
pfd_sddrv_store_fat32_mbr_buf: baseline src 0x2ec base 0x33c insns 187/207; 28 difference groups
  reverse local declaration order: src 0x2ec base 0x33c insns 187/207; 25 difference groups
  truth tests in place of zero comparisons: src 0x2ec base 0x33c insns 187/207; 28 difference groups
  loop increment order or additive increment: src 0x2ec base 0x33c insns 187/207; 27 difference groups
pfd_sddrv_store_fat32_bpb_buf: baseline src 0x4a0 base 0x5c8 insns 296/370; 40 difference groups
  reverse local declaration order: src 0x4a0 base 0x5c8 insns 296/370; 39 difference groups
  truth tests in place of zero comparisons: src 0x4a0 base 0x5c8 insns 296/370; 40 difference groups
  loop increment order or additive increment: src 0x4a0 base 0x5c8 insns 296/370; 40 difference groups
pfd_sddrv_build_fat32_mbr_bpb: baseline src 0x378 base 0x378 insns 222/222; diffs 211
  reverse local declaration order: src 0x378 base 0x378 insns 222/222; diffs 211
  truth tests in place of zero comparisons: src 0x378 base 0x378 insns 222/222; diffs 211
  scope the final success result: src 0x378 base 0x378 insns 222/222; diffs 211
pfd_sddrv_full_format: baseline src 0x1d4 base 0x1d4 insns 117/117; diffs 7
  reverse local declaration order: src 0x1d4 base 0x1d4 insns 117/117; diffs 4
  truth tests in place of zero comparisons: src 0x1d4 base 0x1d4 insns 117/117; diffs 7
  loop increment order or additive increment: src 0x1d4 base 0x1d4 insns 117/117; diffs 7

pfd_st_inter_callback/pfd_st_removal_callback: integer handle tests and an explicit signed drive test remained 65/69 and 62/66; restored pointer tests.
pfd_sddrv_unmount/pfd_sddrv_finalize: explicit masked equality and inlined flag clearing produced 13/13 with seven register/test differences in unmount; restored the original.
pfd_sddrv_get_disk_info: common result return reduced 98/96 to 97/96 but changed return scheduling. Original extracted function excludes its final addi/bl r epilogue (two instructions follow .endfn). Restored the original; symbol sizes untouched.
pfd_sddrv_full_format: six permutations of scalar declarations with halfword and word output storage left 1-7 stack-offset differences. FADiskInfo geometry captures the actual total-sector/sector-size output layout and gives 117/117, diffs 0.
uhf_msc_blk_pread: separate error assignments in sense/non-sense exits and four local-order variants give 129/129 instructions; best has 17 register differences.
uhf_msc_blk_pwrite: explicit sense case 37 and independent cacheable/noncacheable updates give 129/129; four local-order variants leave 16 register differences.
pfd_sddrv_physical_read/pfd_sddrv_physical_write: initializing the running buffer before the aligned path and using it for direct transfers leaves the same two mr source-register differences. Restored the original.

pf2_buffering/pf2_setupfsi: final batch check exposed missing argument narrowing. Changing only exported formal arguments to full-width integers restores the original signed drive and byte/halfword mode conversions: both 11/11, diffs 0.

# Final full gate

Units fully exact/touched: 109/115; instruction-exact functions: 9 -> 156; objdiff code bytes: 1632 -> 17376; data bytes: 408 -> 2344

```
[libs/RVL_SDK/src/fa/driver/pfd_cmn]   below 100: pfd_get_media_drv_char 96.34286
[libs/RVL_SDK/src/fa/api/FAAttach]   below 100: FAAttach 99.36
[libs/RVL_SDK/src/fa/pf_stub]   below 100: pfstub_entry 98.8764
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   below 100: uhf_msc_blk_pread 99.30232
[libs/RVL_SDK/src/fa/msc/puh_msc_blk]   below 100: uhf_msc_blk_pwrite 99.379845
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_inter_callback 93.840576
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_st_removal_callback 90.30303
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_init 86.104164
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_unmount 90.0
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_finalize 92.26316
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_disk_info 97.916664
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_read 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_physical_write 99.92126
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_get_total_sectors 90.9375
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_calc_mbr_bpb 20.606936
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_bpb_buf 37.93578
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_mbr_buf 42.173267
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_calc_fat32_mbr_bpb 85.57143
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_fat32_mbr_buf 49.444443
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_store_fat32_bpb_buf 50.24054
[libs/RVL_SDK/src/fa/driver/sd_drv]   below 100: pfd_sddrv_build_fat32_mbr_bpb 75.14865
GATE PASS
```

Remaining differences: callback/unmount/finalize loads are reused rather than reloaded; init and geometry calculations have branch/integer scheduling differences; sector serialization has endian-store scheduling differences; physical read/write differ in two call argument source registers; build_fat32 retains allocation differences. FA mass-storage read/write have identical 129-instruction streams except register allocation. FAAttach has ten register differences. The disk-info extracted symbol omits its final two epilogue instructions; the version data includes an unexplained trailing zero word.
