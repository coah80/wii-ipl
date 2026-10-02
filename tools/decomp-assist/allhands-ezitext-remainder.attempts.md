# eZiText remainder reconstruction, 2026-10-02

Base: `449529d9`; branch `agent/bittle/allhands-ezi-decompile`.
Only 43U was configured, using `../toolchain/wibo-build/wibo` and
`WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja`. No linking flags, shared
headers, remote refs, or upstream resources were changed.

## Baseline and first candidate: alpha engine

Fresh baseline report: `/tmp/ezi-baseline.json`.
`zi8alpha`: 11/12 exact functions, 5880/21664 exact code bytes,
516/564 exact data bytes; unit fuzzy 94.17892%.
`Zi8AlphaGetCandidates`: 3946/3946 instructions, function fuzzy 92.01039%.
These function and unit percentages are deliberately distinguished.

The scalar layout is four bytes lower in source than in the target because
of the target's existing workspace snapshot at stack 0x20. No dummy alias,
padding, or unused local was added to occupy that slot.

Six semantic corrections were established from definitions and uses, not
from equal-looking raw offsets:

- The flag initialized at target stack 0x84 is the current vowel/punctuation
  restriction. At function +0x0798, the table-31 flag test for bit 4 clears
  target 0x84 and its primary-language snapshot at 0x8C. Source uses 0x80
  and 0x88 for those same definitions.
- The different completion flag is at target 0x88. The table-31 bit-2 test
  at +0x07C8 clears target 0x88 and primary snapshot 0x90. Its source slots
  are 0x84 and 0x8C. Language-pass restoration confirms both identities.
- Target reads of 0x84 at +0x2114, +0x2214, +0x32F4, +0x3384 and +0x3664
  gate punctuation retries, suffix activation, suffix locking and prefix
  punctuation. The source incorrectly read the completion flag in all five
  places. The candidate uses the traced current-restriction variable.
- At +0x1430 the target loads the dictionary-order index from 0x64, uses it
  to select a byte dictionary kind, and stores that kind at 0x60. The retry
  condition at +0x3060 reads 0x64, also used by the following outer-loop
  increment. Source incorrectly tested dictionaryKind; it now tests
  dictionaryIndex. The safe existing early dictionaryIndex initialization
  was preserved.

The isolated six-line semantic patch is preserved at
`/tmp/ezi-alpha-six-conditions.patch`. Alone it gives function 92.009125%,
unit 94.17799%, with code/data/exact counts unchanged. This tiny fuzzy
fluctuation does not invalidate the traced variable corrections.

The first handed-off candidate also restores the original address-order
suffix-lock block before alternate-prefix fallback, restores positive branch
conditions, and places each language's restriction snapshots at its actual
control-flow position. No helper prototype change is included in this first
candidate.

First-candidate fresh report: `/tmp/ezi-alpha-minimal.json`.
`Zi8AlphaGetCandidates`: 94.47314%, 3946/3946 instructions.
Unit fuzzy: 94.17892% -> 95.97323% (about 389 fewer weighted deficit bytes).
Exact functions: 11/12 -> 11/12. Exact code: 5880 -> 5880 bytes.
Exact data: 516 -> 516 bytes. All non-text section scores are unchanged.
Both pools contain no strings and compare identical.

## Separate later research, not part of the first candidate

- Further emission/cursor/comparison/switch reconstruction reached function
  95.63913%, unit 96.82275%, 3950/3946 instructions. Existing exact functions
  remain exact, but extabindex accounting drops by 108 bytes. Preserved at
  `/tmp/ezi-alpha-deliver.c`; not included in the first candidate.
- Matching PUD return declarations to zi8pud2.c's ziU32 definitions, with
  explicit caller byte narrowing, leaves alpha's score unchanged but moves
  one-key candidates 95.39716% -> 95.32416%. Its 5 exact functions and data
  1280/1388 remain unchanged. Held separately for ABI review.
- Matching Chinese Zi8GetPCode to zi8match.c's ziU16 definition restores the
  two target halfword narrowings in paired-phonetic lookup. Together with the
  explicit PUD ABI correction: engine 96.27482% -> 96.492134%, unit
  96.65468% -> 96.848755%, 10678/10676 instructions, 5 exact unchanged.
  extabindex accounting drops 72 bytes. Held for section/relocation audit.
- Splitting the Chinese component cursor/table chained assignment reproduces
  the target's intermediate reload but lowers the engine to 96.090294%;
  rejected and restored.
- Replacing the spelling candidate-count assignment with postfix increment
  lowers spelling 99.555885% -> 96.8%; rejected and restored.

The larger scratch candidate's branch-destination audit found no mapped
branch-target differences over 720 alpha, 351 one-key and 1594 Chinese
branches. Helper-call counts are respectively 73/73, 71/71 and 168/168.
This audit ignores register choices and accounts for the known stack shift;
it is evidence of control-flow coverage, not a claim of exact matching.

First-candidate validation: full 43U build succeeds; DOL SHA1 is
`26116613f624061ba99c8d1a299aaa6efa85670d`. Every one of the 11 baseline
exact alpha functions has identical instruction counts and ctxdiff diffs 0.
`git diff --check` succeeds. No new exact function or complete unit is claimed.
