# o2-aoss attempts (2026-10-09)

Worktree data-d1, branch agent/w1009/o2-aoss at origin/main 20cf9f9f.
Scratch compiles in /tmp/o2-aoss (same flags as ninja, ~0.2 s per unit).

## Findings that apply to both AOSSLink functions

- IRO is skipped for AOSSi_WLANGetBSSList and AOSSi_WLANConnect. Enabling
  MWCC's own IRO dump (flag byte 0x725e5c, log opened by 0x5ed500 in
  GC/3.0a5.2) shows both stop after IRO_BuildflowGraph. The cause is the
  check at 0x5bd060/0x5bd150: any EOBJREF to an object whose qualifiers carry
  alignment bits (0x1f000000) disables IRO for the whole function. Here that
  is `WD_Info info ATTRIBUTE_ALIGN(32)` (and `scan`). Removing the attribute
  makes IRO run, but it also drops the 32-byte frame alignment the target
  has. Type-level `ATTRIBUTE_ALIGN(32)` on the WD structs is ignored by this
  compiler (sizeof/alignof unchanged, no aligned frame), so the target also
  ran without IRO. Source shape maps almost 1:1 to PCode in these functions.
- Ported MWCC's pre-RA list scheduler and the 750 machine model to Python
  (/tmp/o2-aoss/sched.py). It reproduces our B1/B14 of WLANConnect, the
  target B1, and our B19 of GetBSSList exactly. Facts it needed: stores to
  the same local at different offsets are independent; a store cannot issue
  while another store sits in LSU stage 2; ties go count -> height -> opcode
  rank (MR 0 < STH 1 < ADDI 2 < LHZ 3 < LI 4) -> program order.
- With mwdbg extended with dump points before/after pre-RA scheduling and
  after each COptimizer level-4 pass (private copy, /tmp/o2-aoss/mwdbg2):
  the scheduler input for both blocks equals our final code minus nothing.
  Both target orders need one extra instruction in the block at scheduling
  time that is gone later (RA coalescing or post-schedule cleanup).

## AOSSi_WLANGetBSSList: 25 -> 3

regsim with the parameter pinned (/tmp/o2-aoss/ordanneal.py) found 1500
declaration orders reaching all 11 target registers. Common constraints:
index < driver < buffer < descriptor < count < cleanupRetries < unlockRetries
and result < startupRetries < scanRetries. Declared C89-style at the top in
that order (block-scoped declarations moved up): 25 -> 3, pool identical.

Remaining 3: block after `memset(buffer, 0, 0x3200)`, target issues
`sth channelBit` before `li r5, 6` (so the lhz temp can be r5). Simulator:
any one extra instruction in that block at scheduling time gives the target
(dead VN copy, extra addi, ...). Tried, all still 3: `&scan.bssid`, scan
pointer local, inline scan-param initializers (2 shapes), inline memset
wrappers (void and returning), statement order permutations, unpacked WD
structs (header override).

## AOSSi_WLANConnect: 2 (unchanged)

Second memset: target `li r4; li r5; mr r3, r27`, ours `li r4; mr r3; li r5`.
Simulator: only an extra instruction on the address chain
(lis -> addi -> X -> mr r3, X later coalesced) reproduces the target; no
reordering of the block's inputs does, and a dead side copy does not.
Explicit copies through a second local (i6, n3), inline helpers with a
param or a cast local (m0/m1 x void/int x global/var), getter inline,
NULL-initialised pointer, extern/global/static/struct-wrapped configs
(struct gives `addi r27, r3, 0x160`: right order but one extra insn),
array decay, casts: all removed by the COptimizer "pre" phase (peephole 0 +
DCE) before scheduling, or by VN. 2 unchanged.

## AOSSi_WLANGetBSSList: 3 -> 0 (EXACT)

The missing instruction is a copy that lives until pre-RA scheduling and is
coalesced by the allocator afterwards. A copy into a named local survives the
COptimizer when its uses are in other blocks (the block-local peephole cannot
rewrite them). A typed view of the scan buffer does exactly that:
`void* buffer` for alloc/memset/free, `u8* scanBuffer = (u8*)buffer;` right
after the memset, used by WD_Scan, the BSS count and the first descriptor.
The copy sits in the scan-parameter block at scheduling time, so `sth` of
channelBit issues before `li r5, 6` (target), then r24 holds both names.
Variants that did not work: alias for the count pointer only (3), alias
assigned before the memset (3).

## AOSSi_WLANConnect: more evidence (still 2)

- Pass tracing (dump after every COptimizer level-4 call): the in-block copy
  chain `addi vB; mr vC, vB; mr r3, vC` is collapsed by 0x596850 (block-local
  copy forwarding + DCE, pre phase); copies created later by value numbering
  (0x5976e0) get their uses canonicalised to the first holder. So a chain
  copy in the memset block cannot come from a plain second local.
- Simulator searches: no input order, no 1-2 dead extra instructions
  (return copy, li, mr, addi, lis), no 1-2 side copies reproduce the target.
  Only (a) a copy on the address chain or (b) r4 and r5 both coming from
  register copies at scheduling time do.
- Pragma sweep (15 single + all pairs, unit-wide, diagnostic): best is
  baseline 2; `peephole off` 11, `scheduling off` 50.
