# o2-aes-idct attempts

Worktree data-d11, branch agent/w1009/o2-aes-idct (from origin/main 20cf9f9f). 43U only.

## Unit-level checks

- Compiler sweep (all GC and Wii compilers; `-ipa file` dropped for GC < 3.0): aes GC/3.0a3 .. 3.0a5.2
  identical (7/9), older or Wii compilers worse. idct_block_var GC/3.0a3 .. 3.0a5.2 identical (0/2).
  Version is not the lever for either unit.
- combosweep (single + pairwise pragmas): aes best 137 -> 135 (opt_propagation off), no lead.

## net/aes: AESiEncryptBlock 137 -> 0, AESiDecryptBlock 215 -> 0 (unit Matching, DOL OK)

Tooling: `tree.py` symbolically executes a function and compares the expression tree of every
store against the target, independent of registers and scheduling. That separated "wrong
dataflow" from "wrong allocation", which earlier rounds had mixed together.

Findings, in order:

1. The target round is plain rijndael-fst order `hi ^ m16 ^ m8 ^ lo`, then `^ key`. The target
   tree is `(lo ^ (m8 ^ (hi ^ m16))) ^ key`. At -O3/-O4 MWCC rebalances any 4-leaf XOR chain
   (tree height reduction): every one of the 120 shapes tried compiled to `(x^y)^(z^w)`. At
   optimization_level 2 it is not rebalanced, but level 2 cannot unroll the decrypt key loop,
   which the target does (mtctr 2), so the unit is O4.
2. With the rotate written as the `__rlwinm(x, n, 0, 31)` intrinsic instead of the shift/or
   macro, O4 leaves the chain alone (intrinsic calls are not reassociated), and the natural
   expression gives exactly the target tree. It also removes the CSE temporaries the shift/or
   macro created for the table loads (x used twice), which is what had kept the allocation off.
3. Final round: encrypt `(hi<<24 | m16<<16 | m8<<8 | lo) ^ key[i]`; decrypt is XOR-based with the
   key first, `key[i] ^ hi<<24 ^ m16<<16 ^ m8<<8 ^ lo` (O4 rebalances it the target way).
4. Encrypt init: `state = input[i]; ... state ^= key[i]` with `key = context->keys` walked by
   `key += 4` (single-expression init put keys[i] in the state register; 9 diffs).
5. Decrypt: `key = context->keys; key += rounds * 4;` (the one-expression form folds +16 into
   the loads). InvMixColumn as `static inline void AESiInvMixColumn(u32* word)` (pointer
   parameter) fixes the last r7/r8 swap between value and timesTwo; value-parameter helpers and
   all local declaration orders left 26+ diffs.

Rejected along the way: optimization_level 2 pragma (correct tree, wrong key loop), int/long
casts between XOR stages (blocks rebalancing but unnatural).

`include/global/decomp/ide.h`: declared `__rlwinm` for non-MWCC tooling (guarded by
`#ifndef __MWERKS__`, no build effect).

## buffer/idct_block_var: Lumi and Col (in progress)

Dataflow first (path-based symbolic execution of both objects, `ptree.py`):

1. Even part: the target computes `rot + (c6 + c2)` into a fresh variable. `x = rot + x` is
   rewritten by MWCC to `x += rot` (operand order `sum + rot`), and a single-use `evenSum`
   gets forward-substituted and reassociated (`c2 + (rot + c6)`). Fix: `evenSum = c6 + c2;
   c2 = evenRotation * 0xB5 >> 8; evenRotationSum = c2 + evenSum;` (the c2 reassignment
   blocks the substitution). Same in both passes of both functions.
2. AC test: the target ORs leaf-first (`c2 | acc`). `acc |= c` or `acc = c | acc` with a u32/s32
   accumulator is canonicalised to acc-first, a single 7-way expression is rebalanced at O4.
   An `int` accumulator over `s32` coefficients (`acBits = c2 | acBits;`) keeps leaf-first
   (the long->int conversion stops the `|=` rewrite).
3. Level 2 or 1 cannot be it: no CTR row loop at level 2 (274 vs 257 insns).

With 1-2, all store/call trees of Lumi (3 paths) and Col (4 paths) equal the target and the
frame sizes match. Remaining differences are allocation and scheduling only.

Allocation findings (mwdbg + regsim, `wantmap.py` maps candidate vregs to target registers by
symbolic value):

- Named locals are numbered per block in reverse declaration order, blocks top-down (function
  scope first), forward-substituted locals take no number; split webs and inline locals become
  `@` temps numbered after all named locals.
- Column setup now matches exactly: `pitch4/7/6/5/3/2` as named locals assigned before the
  loop, a separate column cursor (`src`, not a split web of the row cursor), and
  `for (column = 7; column >= 0; column--)` (CTR trip count becomes a temp colored first).
- Declaration-order search inside blocks on the captured graph tops out at 113/153 target
  registers, and a greedy order-feasibility check stalls on callee-saved claim order, so the
  column AC block still has a different pre-RA schedule (live ranges).
- objdiff fuzzy is the gate metric and disagrees with positional diff counts; searches now
  score candidates with objdiff itself (`odfuzzy.py`, one-unit objdiff project per slot).
