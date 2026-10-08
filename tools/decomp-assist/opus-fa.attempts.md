# opus-fa attempts

## libs/RVL_SDK/src/fa/driver/sd_drv (23/26 -> 26/26, linked)

### pfd_sddrv_finalize (4 -> 0)
- Evidence for volatile: target reloads `flags` straight after testing it (`lwz; rlwinm.; beq; lwz` with no store in between) and keeps the final state stores in source order. The previous rounds faked the reloads with const-pointer accessors.
- Fix: `volatile PFD_SDDRV_INFO g_pfd_sddrv_info;` (definition-level, lever 19: the struct is written from the SD insert/remove interrupt callbacks). The fake accessors `pfd_sddrv_flags/device/disk/drive` are removed and the fields read directly. The removal callback loses its `media_inserted == 0 &&` re-check, which only existed to force a reload. Every other function stays exact.

### pfd_sddrv_init (142 -> 0)
- Explicit `return 0;` in the already-initialized branch: 142 -> 26. MWCC then turned `disk != info.disk ? -44 : 0` into a branchless select. The target branches instead.
- if/else/eq/goto spellings of the same return: still branchless (26).
- `#pragma ppc_iro_level 0` around the function (lever 26): 26 -> 1. Only the null test was left: target `li r0,0; cmplw r3,r0`.
- `disk == NULL` (NULL is `((void*)0)`) under IRO 0: 1 -> 0. Without IRO 0, NULL gives cmpwi.
- Diagnostic only: optimization_level 1/2/3 and iro 1/2 did not help.

### pfd_sddrv_build_fat32_mbr_bpb (122 -> 0)
- Target leaves an unreachable `bl OSReport` without its argument after the inlined reserved-sector writer, and has no null check of the buffer. A mini test shows this exact remnant comes from an inline helper with no null check that returns 0, compiled under IRO 0.
- The reserved-sector helper is now written like its sibling `pfd_sddrv_store_fat32_fsi_buf` (no null check, `return 0`). The only caller passes `g_pfd_sddrv_buf`, so behaviour is unchanged. With IRO 0 around build_fat32: 122 -> 2.
- Last 2: the first write loads the sector before the device. A local `partition_start_sector` like the FAT16 builder: 14. `+ 0`, casts: 2. Fix: `static inline s32 pfd_sddrv_write_sector(u32 sector)` wrapping `ISD_WriteBlock(device, sector, g_pfd_sddrv_buf, 1)`, so the argument is evaluated before the device load: 0.

### Link
- Flipped to Matching. The first DOL had `addi r27/r28` swapped in physical_read/write. The cause was `ATTRIBUTE_ALIGN(32)` on `g_pfd_sddrv_buf`, which changes codegen, so it was dropped.
- Without a 32-aligned .bss object, every `g_pfd_sddrv_info` access moved by 0x10. The fix is `ATTRIBUTE_ALIGN(32)` on `g_pfd_sddev` (the IPC device storage) and on `g_event` (the IPC event word, which the target places at .sbss+0x20).
- DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d OK.

## libs/RVL_SDK/src/fa/pdm_partition: pdm_part_is_master_boot_sector (start 84 in repo / 21 in opus-vf best -> best 19, not exact)
Remaining difference: the byte-load schedule of the inlined LE32 read. The target builds the tree (b2<<16 + b0) + (b3<<24 + b1<<8) and loads b3, b2, b0, b1. Ours loads b3, b2, b1, b0.
- mwdbg: our pre-RA scheduler already emits b1 before b0, so b1 has a higher priority. In the target, b1 shares b3's register, which proves its load comes after the b3 shift in the pre-RA order. So the target DAG or the initial order differs, and it is not a register tie.
- Mini-file study (/tmp/opus-fa/perm*.py): MWCC reassociates a 4-term add chain into pairs (L0+L2),(L1+L3) in source operand order. No permutation or parenthesization of the 4 terms gives the target pairing together with the target load order. All 120 tried in the real function: best 19 (e.g. `b1<<8 + b0 + b2<<16 + b3<<24`). Saved as opus-fa.best.pdm_partition.c.
- Unrolled byte loops (+=, |=, Horner): 43-69. Loads before the zero store: 73 (the zero store is DCE'd). Reusing a local for start/count: 21. Removing the zero store: 73. Count read first: 88.
- buf indexing instead of `buf += 16`: 90-91. Partition-entry pointer: 69.
- Helper boundaries (local for b0, u8/u32 parameter helper, two u16 halves, pointer to the field): 20-21.
- Pragmas (diagnostic): iro 0/1: 37 (25 with pointer loop 2, best 23 over all 120 sum shapes). scheduling off: 77. IRO is not the lever here.
