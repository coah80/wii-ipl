# Alpha output and scan reconstruction follow-on, 2026-10-02

Parent candidate: `94b7f57e`. Its source/log were left unchanged during
independent side experiments. No ABI/header/linking changes are included.
Changed source: `libs/RVLMiddleware/eZiText/src/clib/zi8alpha.c` only.

## Target evidence and retained changes

- At `Zi8AlphaGetCandidates +0x3178`, the original emits wide-character
  output before the encoded-byte alternative. The wide path assigns the
  same zero to output elements 2 and 1 (+0x31A4/+0x31A8), then advances by
  two characters. The encoded path likewise shares its zero assignment.
  Restored that positive branch and ordinary chained zero assignments.
- The dictionary comparison loop branches from +0x2904 to its bound check
  at +0x292C. The comparison body exits on a character mismatch at +0x2924;
  a matched character increments the index at +0x2928. Replaced the merged
  `for` condition with the corresponding bounded loop and explicit break.
- The punctuation output block at +0x1B0C..+0x1B1C reads the current cursor,
  emits its character and advances that same cursor. Expressed this with
  `wordCursor[1] = *punctuationCursor++`. It does not reuse a mutated index
  in another operand or introduce an unsequenced read/write.

## Independently compiled, isolated trials

Each trial used the exact 43U MWCC flags from the live Ninja command and a
separate object/report under `/tmp/ezi-side`, without altering the reviewed
worktree candidate. Report columns below are function fuzzy, unit fuzzy,
matched data bytes and exact-function count:

- Early candidate-skip block: 94.65585, 96.10635, 408, 11; excluded
- Wide output first: 94.887985, 96.27548, 516, 11; retained
- Next-dictionary switches: 94.4037, 95.92264, 408, 11; excluded
- Explicit dictionary-scan break: 94.62088, 96.08087, 516, 11; retained
- Combined candidate-count limit: 94.35884, 95.88995, 408, 11; excluded
- Punctuation cursor increment: 94.4782, 95.97692, 516, 11; retained
- Wide output plus scan: 95.02306, 96.37389, 516, 11
- Final three-change subset: 95.02813, 96.37759, 516, 11

## Full current-worktree validation

Fresh report: `/tmp/ezi-alpha-followup.json`.
Full build log: `/tmp/ezi-alpha-followup-build.log`.
Exact functions 11/12 unchanged; exact code 5880/21664 unchanged;
exact data 516/564 unchanged. Unit fuzzy 95.97323% -> 96.37759%.
Function fuzzy 94.47314% -> 95.02813%, about 88 additional weighted bytes.
Relative to initial 449529d9, unit fuzzy improves 94.17892% -> 96.37759%.

Pool first: identical (no narrow strings in either pool).
Main function: 3946/3946 instructions, 0x3DA8 bytes each, frame 0x2B0.
Strict ctxdiff remains nonzero (3745 differences), dominated by the known
scalar-stack displacement, instruction placement and GPR allocation. No
new exact function is claimed. Each of the existing 11 exact functions
retains identical instruction counts and ctxdiff diffs 0.

All non-text section scores match the parent: .rodata, extab and extabindex
remain 100%; the existing 48-byte generated switch table remains unmatched.
The advisory register-normalized/control-flow alignment checked 701 branch
pairs with zero destination mismatches and 73/73 helper calls. This is a
coverage check, not an exactness claim.

Full 43U build succeeds with the approved wrapper and
`WIBO_SJIS_MISSING_IMPORTS=1`. DOL SHA1:
`26116613f624061ba99c8d1a299aaa6efa85670d`.
`git diff --check` succeeds. No new assembly, volatile workaround, register
forcing, undefined value, dummy storage, prototype or shared-header change.
