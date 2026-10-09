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

## w1011/pdm continuation: pdm_part_is_master_boot_sector (84 in repo -> 17, beats prior 19 but not exact)
- Committed decode: named local `pf_u32 s` + `*p_start = 0; s = MBR_WORD(buf,454); *p_start = s; *p_count = MBR_WORD(buf,458);` (s at fn top). The named local reproduces orig's dead `*p_start = 0` store (must precede s's computation — any form where word-building precedes the 0-store makes it adjacent-DCE'd) AND drops the extra r29 callee web: 86v84/+0x10-frame -> 84v84 insn-equal.
- Residual 17 = word-build coloring/schedule only: orig gives b3<<24 the callee (r30) and reuses r30 for `add.` s; halves stay scratch (r12/r11). Ours coalesces the dot-add backward into half1 -> r30, parks b3<<24 on r31 (shared with cb3<<24). Orig's `add.` dst is a FRESH web (dst != either operand) — MWCC coalesced count's final add (dst=src2 r9) but not start's; no source form reproduces the non-coalesced Rc dst.
- Tried: `pf_u32 c` symmetric local (=17, no-op), s in-loop decl (=17), `if (s != 0` test (=52, s spans count build -> 4 callees), store-after-count (=51, same), compute-both-store-both (=30), named halves h1/h2 both positions (=83 loses 0-store / =29), explicit even/odd + adjacent pairings (=29 each), descending operand order (=30), read_mbr_u32 static-inline pointer helper (=17 identical — inlines transparently), start[index]/count[index] pure indexing (=19, adds loop-tail bump-order diff), `pf_s16 index` alternatives (extsh already matches).
- Pragmas on the fn: ppc_iro_level 0/1 = 43, scheduling off = 47, schedule_twice on = 17 (inert), scheduling 600 = compile failure, optimization_level untested (same class).
- declsearch on the 6-line decl block: current order already optimal (scored 12,21).
- Wall class: allocator/solver-internal web-coloring (which slwi piece gets the callee + non-coalesced Rc dst) — same class as the fossils leaf. Prior worker's DAG-level note stands: orig loads b0 before b1 (b1 shares b3's r9), ours loads b1 before b0; all 120 operand perms were exhausted without the s-local cross-product — none of the ~16 s-local forms moved it past 17.
- Post-#1312 re-check on origin/main 54ca052b: still 84v84/17 (fn was never 100% — #1312 only swapped helper->MBR_WORD + pointer->index second loop). Restoring the deleted `read_partition_u32` const-ptr static-inline crossed with s-local: 86v84/42 (re-adds r29 web — const-ptr helper call boundary hurts). `pf_s32 s`: 17 no-op. The 17d macro+s form remains best of ~18 variants.

