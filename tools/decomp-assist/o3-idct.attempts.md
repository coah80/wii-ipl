# o3-idct attempts

Worktree data-d11, branch agent/w1009/o3-idct (from origin/main 179cd4e3). 43U only.
Unit: `libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var`.

Start: Lumi 11 diffs (O3 pragma), Col 51 diffs.

## What was wrong (Lumi)

- Post-RA scheduler model (`/tmp/opus-idct-sched/sched.py`, reproduces all 61 captured blocks)
  applied to our pre-RA order with only four values recoloured (scaled even rotation and odd
  difference rotation to r20, even sum and first even output to r10) gives the target order
  exactly. So the 11 diffs were pure colouring; no schedule or dataflow change was needed.
- The retained source made the scaled rotation a split web of `rowC2` (`rowC2 = rot * 0xB5 >> 8`).
  MWCC's lifetime splitter (`fn_00459420` in the rayanht GC/1.x decomp) turns every web but the
  first-defined one into an `@` temp numbered after all named locals, so it is coloured early and
  takes r10. Named locals are numbered in reverse declaration order; single-use locals are forward
  substituted and become codegen temps numbered in statement order at their use.
- regsim on that capture: no declaration order and no single renumbering reaches the target.
  With a named rotation, the even-sum temp has to be numbered between the rotation temps and the
  named locals (it must be created before the odd-part temps).

## The fix (Lumi exact, no pragma)

- Natural row pass in the 4x4 sibling's shape: even part first (`evenRotation = c2 - c6;
  evenSum = c2 + c6; ... scaled = evenRotation * 0xB5 >> 8; evenRotationSum = scaled + evenSum;`),
  then the odd part. Single-use `evenSum` is substituted and MWCC emits `add c6, c2`, as in the
  target; no reassociation (that came from the old statement order, not from the types).
- mwdbg capture of that source (`runs/o3-idct-nat1`), vmap to the target, then an anneal over the
  order of named locals with regsim: cost 0. Declaring the locals in the solved order compiles
  to an exact Lumi at O3 and at the unit's O4, so the scoped `optimization_level 3` was dropped.

## Col (exact)

- Same natural row pass: 51 -> 28 diffs (dataflow now matches; the old source reassociated the
  even sum to `c2 + (rot + c6)`).
- Compiler-in-the-loop declaration climb: 28 -> 13.
- mwdbg capture of the climbed source (`runs/o3-idct-natcol1c1`): regsim reproduced it with only
  4 wrong registers; the declaration anneal reached cost 0 on four of five seeds and the solved
  order compiles to an exact Col. A duplicated `rowOddOutput2` statement left over from the splice
  was removed (still exact).

## Result

- Lumi 11 -> 0 diffs, Col 51 -> 0 diffs; `.text` byte-identical, pool identical, symorder ORDER OK.
- Unit flipped to `Matching`; full build passes, main.dol SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
- No pragmas left in the file (the scoped `optimization_level 3` from #1322 is gone).
- Gate: `GATE PASS`, code 2844/2844, functions 2/2, linked code 2844, 0 regressions.

## Method worth reusing

1. Make the source natural first and check the dataflow (here: copy the sibling 4x4 butterfly).
2. Capture once with mwdbg, map every vreg to the target register (`/tmp/o3-idct/sched/vmap.py`,
   a copy of the opus-idct one with `andi.` added).
3. Anneal the order of named locals with regsim against the full want map
   (`/tmp/o3-idct/sim/declsearch2.py <capture> <vmap.json> '{}' <seed> <steps>`), then write the
   declarations in that order. If temps are among the mismatches, no declaration order can fix it:
   change which values are named or where single-use values are consumed, and recapture.

Tools tried and not needed: per-function pragma sweep (no lead), grouping row/column declarations
(breaks the match; the solved interleaving is required).
