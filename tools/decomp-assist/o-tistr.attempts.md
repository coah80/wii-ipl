# o-tistr attempts (tiString Decolated::inputChar)

Worktree data-d5, branch agent/w1009/o-tistr, base 12e857a9. inputChar 13/136 at start and at end.
Scratch: /tmp/o-tistr (bf/run.py variant runner, sched/schedsim.py scheduler model, cap/ per-pass captures
with extra pre-RA hooks 0x4695dd/0x4695ee/0x469602 and global-optimizer start/end hooks).

## Kept

The dispatch is now `if (mode == TM_Kana || mode == TM_Roman) ... else if (mode == TM_Hangul) ... else`
instead of the two gotos and labels. .text and .data are byte-identical to the goto form; inputChar stays 13.

## Why the target's Hangul block is not reachable from any single-block shape

Target: `li r6,0; sth r6,0x10(r1); cmplwi r4,0xa; slwi r0,r6,1; ...`.

1. The scheduler cannot produce `li; sth; cmplwi` from one block. A block {li P; sth P; cmpli; bf} always
   comes out `li; cmpli; sth` (v013 compiles it that way, and the MWCC list-scheduler model with 750 latencies
   li 1, sth 2, cmpli 3 reproduces it: cmpli fills the second IU slot in cycle 0). Without the branch the result
   is the same. GC3's Scheduler_Schedule (0x5995c0) has no "already scheduled" check, and the final call is
   force=1, so every block with more than 2 instructions is rescheduled after RA. The only things removed after
   the final schedule are branches to the next instruction (optimize_branches at emission).
   So in the original, `[li; sth]` and `[cmplwi]` were separate blocks at the final schedule.
2. MergeAdjacentBlocks (0x596960, run in the global optimizer, before RA and after RA) merges a block into
   its successor when the edge is the only successor and the only predecessor. The cmplwi block must therefore
   have had two predecessors (or the `[li; sth]` block two successors) at every merge. This is how the
   dead compare in WADImportDVDExForBS survives in its own block: it is the join block of the previous
   `if (header.tmdSize != 0)`.
3. The split before the cmplwi block must be invisible in the final code. Every compare in the target uses cr0,
   so the entry 0xfffe compare and the kana range compare cannot be reused (a reused cr would get another
   field). Only the mode compare of the `else if` can be reused. Verified: with a function-scope
   `s32 mode = mTranslateMode;` (all other code unchanged, still 13) an inner `if (mode == TM_Hangul)` is
   not folded by IRO and the backend VN reuses the compare: `li r6,0; sth r6,0x10(r1); bne; ...; cmplwi r4,0xa`
   (variant ml1, 72 diffs because both then-blocks keep `li r6,0`). A reloaded member test or a bool computed
   at the top does not work (reload, or a materialized bool).
4. Both then-blocks must be empty by emission, and the index still needs two reaching definitions at both
   constant-propagation passes (otherwise `input[n] = ch` folds to `sth r4,0x10(r1)`).
   - GC3 value numbering never deletes or replaces a redundant `li` of a named local. Even with the
     function-start zero record killed by a call, `n = 0` in the then-block survives (variant callbreak).
     It deletes only temporaries and array-to-register vregs (the o3 LinePosition mechanism).
   - The store's literal zero only lands in the counter's register when the counter is a named local whose
     2-operand `li` comes first in that block (VN pass 1 merges within the block). A temp or an a2r field is
     replaced by the function-start zero (r5) instead.
   These two facts contradict each other for a single counter, and every shape that empties the then-blocks
   either loses the store register (p1, poc1, poc2, bf1, bf2) or keeps a `li` (ml1, base). A struct-reset
   then-block also makes IRO drop the inner mode test (bf1, m1, m2, modeloc1).
5. count: the use-site `clrlwi r0,r29,0x10` survives only if count's Hangul definition at the first
   constant-propagation pass is not an extension. `lhz` is not treated as extended (probe p3 f1), a `rlwinm`
   is (v001-v003 lose it).

## Other measured shapes (diffs)

switch on mode 120; switch on ch 60 (signed cmpwi); if/else with equal arms folded 73; do/while(false),
goto label, for(;;) break, while(ch=='\n') break 61-72; `((void)0)` then-block folded 73; volatile store 62
(not a barrier); bool flag before the store 72; aggregate-initialized buffers emit stw; empty ifs and single-def
index with opt_dead_code / opt_propagation / opt_common_subs / opt_dead_assignments / opt_lifetimes off: no
change (73); scheduling off 61; peephole off 137-140; optimization_level 0-3 127-151.

Next idea not finished: a then-block whose definition is a copy `n = m` with `m` copied from `n` in the
newline block after a join (const-prop cannot fold it, VN deletes it). It needs a second join before the
copy, so the same contradiction comes back.

## Closest structural lead (40 diffs, not kept)

With the function-scope `mode` local, `LinePosition position; position.index = 0; input[0] = position.index;`
then `if (mode == TM_Hangul) { position.index = 0; }` and `u32 n = position.index;` gives the target's first
block exactly (`li r6,0; sth r6,0x10(r1)`, then a `bne` on the reused cr0). Two things still differ: the inner
then-block keeps `li r6,0` (IRO scalarizes the field into a named local, which VN never deletes), and IRO's
dead-store pass removes a newline then-block that only resets the position, so the `cmplwi` disappears.
The gate for this round passed with the dispatch cleanup only (0 regressions, DOL hash unchanged).
