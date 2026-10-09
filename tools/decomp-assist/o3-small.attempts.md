# o3-small attempts (2026-10-09)

Worktree `sol-low`, branch `agent/w1009/o3-small`, base `ad5b9dea` (origin/main). Full build OK and
DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d` before, after nup, and after pdm (both units linked).

## libs/RVL_SDK/src/nup/nup: __nupParseServerInfo 66 -> 0 (unit flipped to Matching)

Root cause: the target colors every `__nupFindTag` strstr result as if it were an IRO temp created after
inlining, in source order (start_1, end_1, start_2, end_2, ...). Our source had `start` as an inline
local (inline object band) and `end` collapsed into the backend call-result temp (numbered last).

How it was found:
- `/tmp/o3-small/nup/vmap2.py` maps every virtual register of an mwdbg capture to the target's
  physical register (final code aligned by PCode instruction address), giving a want map (92 vregs).
- regsim relabel experiments (`/tmp/o3-small/nup/t5`-`t11.py`): no per-expansion order of the 4 values works
  (matches o2-small), but one band of all start/end values below the inline tag objects, ordered
  s1 > e1 > s2 > e2 ... (temps created in source order after inlining) gives 0/92 mismatches.
- MWCC decomp (rayanht/mwcc): only `CInline.c:InlineWrapResult` creates `EFORCELOAD` (result of an
  expression-inlined call that contains a load or call), and IRO lowering turns it into a fresh temp.
  So both strstr calls must go through an expression-inlined function.
- Prior art: Petari's MSL `cstring` (SMGCommunity/Petari libs/MSL_C/include/cstring) declares, for C++,
  `const char* strstr(const char*, const char*)` plus the const-correct overload
  `extern "C++" inline char* strstr(char*, const char*)`. NUP is C++ and passes `char*`.
- Backend copy propagation (`CopyPropagation.c`) still folds `end` into the call-result temp unless a use
  block kills the copy; `end += strlen(endTag); return end;` does that (wrapper alone: 83, both: 0).

Change: `libs/MSL/include/string.h` gets the MSL C++ overload (C declaration unchanged for C), and
`__nupFindTag` ends with `end += strlen(endTag); return end;`. Other C++ users of strstr
(nup_nhttp, iplSetting, iplNandSDWorker, ut_ArchiveFontBase) only change `.strtab`/debug metadata;
their code/data sections are byte-identical. nup: 23/23 exact, pool 28/28, symbol order differs only in
label names (lbl_ vs @n, `pad$` vs `fillByte$` static name).

Tried first (all worse, reduced file `/tmp/o3-small/nup/red_base.cpp` scored registers only):
value-first helpers (204/477), ternary helpers (478+), shared caller tagStart/tagEnd via pointers (89),
call inside the if condition (66), non-inline helper (66), strstr wrapper on one call only (66/83).

## libs/RVL_SDK/src/fa/pdm_partition: pdm_part_is_master_boot_sector 21 -> 0 (unit flipped to Matching)

Root cause: the eight MBR byte loads are volatile in the target. Change: the parameter is
`volatile pf_u8* buf` (C function, symbol unchanged; no prototype elsewhere; all reads go through it).

Proof that the target needs ordered (volatile) loads:
- Pass-2 scheduler model (`/tmp/o2-small/sim/sched750.py` + `model2.py`) checked against the GC/3.0a5.2
  binary: pick 0x599920, DAG builder 0x599ac0, add_dependency 0x599e90, 750 can_issue 0x63c880,
  timing table built at 0x63c1b0 (record forms +2 latency via flags2 0x100000). It reproduces
  5875/6036 blocks of every mwdbg capture in `_mwdbg/runs` (failures are alias-object cases).
- With the final 24 instructions and registers, no pass-2 input order reaches the target (random
  topological search: best 10 base alias, 8 all alias; every load/store alias subset: best 6;
  block-split partitions only at unnatural points). The blocker is cycle 2: `slwi r30,r9,24` frees
  `lbz r9,0x1c7` (WAR) while `lbz r11,0x1c6` frees nothing, so the slwi must issue first.
- Adding 0-latency load->load ordering edges (what GC3 adds for PCode flag 0x80 at 0x599b5b)
  makes the target a fixed point. mwdbg on the volatile build shows LBZ flags 0xa2 (0x22|0x80).
- Compiled: `volatile pf_u8* buf` gives 20/20 exact; use-site cast form also exact (not used).
  The buffer is filled by the disk driver (pdm_disk_physical_read) outside this function.

Tried first (all 19-85): 120 add-tree shapes (`/tmp/o3-small/v2.py`, reassociation pairs
((A+B)+C)+D -> (C+A)+(D+B)), LE32 inline helpers (21), byte loops (43-97), `#pragma scheduling`
once/twice/off and every processor model (21-83), Wii/1.x compilers (17-20, siblings break).
`#pragma scheduling once` (pass 2 only) exists in GC3 and was never in the combosweep list.
