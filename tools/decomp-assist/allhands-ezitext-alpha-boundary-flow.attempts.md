# Alpha comparison and output boundary follow-on, 2026-10-02

Base: 813660b9 plus unchanged one-key candidate 2ec4a57e, locally fe647fe4.
Changed source: libs/RVLMiddleware/eZiText/src/clib/zi8alpha.c only.
No ABI, shared header, linking flag or other source change is included.

## Retained target source structure

- At function +0x25A8, the suffix truncation condition compares the combined
  word/prefix length first and branches on less-or-equal. Recovered that
  operand order. The separate bound check at +0x25E0 has the opposite operand
  order and is deliberately preserved.
- The dictionary lookup comparisons at +0x2948, +0x2978 and +0x2990 compare
  the dictionary scan index first against word length or the halfword-narrowed
  dictionary count. Recovered those three relational expressions without
  changing the count helper's declaration or its halfword conversion.
- The punctuation fallback at +0x30F8 compares against 0xF010 and uses a
  strict greater-than failure branch. Replaced the equivalent < 0xF011 test
  with <= 0xF010.
- The output-count branch at +0x3B08 falls through to clear letters when
  countOnly is true, and branches to the actual-count store otherwise.
  Restored that original arm order.
- Prefix selection at +0x3B84 compares against 1 and uses less-or-equal.
  Recovered <= 1 instead of the equivalent < 2.

These are demonstrated control-flow and expression reconstructions, not
register/declaration permutations. No new volatile, assembly, forced register,
padding, artificial storage, or undefined value is introduced.

## Isolated trials and rejected work

Trials used the live 43U Ninja compiler command, separate source/objects and
reports under /tmp/ezi-next, without changing the worktree before selection.
Columns: unit fuzzy / matched data bytes / exact functions.

- Output-count arm order: 96.47729 / 516 / 11
- Both inclusive boundary expressions: 96.3798 / 516 / 11
- Both maximum-length comparison orders: 96.38128 / 516 / 11
- Dictionary comparison order: 96.38405 / 516 / 11
- Initial four-group combination: 96.48966 / 516 / 11
- Final reviewed combination, preserving the second length comparison's
  original operand order: 96.52474 / 516 / 11

Further target-evidenced trials were rejected rather than committed:

- Safe temporary plus postfix prefix append: 94.71085 / 336 / 11
- Safe temporary plus postfix highlighted append: 94.60377 / 336 / 11
- Dictionary-kind switches: 96.364845 / 408 / 11
- Early candidate skip: 96.451996 / 408 / 11
- Combined candidate-count limits: 96.402695 / 408 / 11
- Full dictionary source structure plus initial boundary combination:
  96.78767 / 408 / 11; function extent 0x3DB8 versus 0x3DA8
- Explicit prefix-mode byte: 96.40805 / 408 / 11
- Explicit element-count byte: 96.3582 / 408 / 11
- Skip/count/byte combinations retained extent mismatches and were rejected.

One-key spelling compound count assignment was codegen-neutral. Prefix
increment removed the redundant byte narrowing but worsened allocation:
unit 98.23523 -> 97.36198. Neither trial is retained.

Chinese explicit halfword casts at the two paired phonetic comparisons and
an alternative proper halfword return declaration with redundant casts removed
both reproduce the previously parked result: unit 96.848755, matched data
144 -> 72. Adding the demonstrated component-cursor reload gives 96.489876
with the same loss. All remain scratch experiments, with no Chinese edit or
neutral PUD ABI commit included.

## Validation

Fresh full report: /tmp/ezi-next-alpha-full-report.json.
Full-build log: /tmp/ezi-next-alpha-full-build.log.
Baseline report: /tmp/ezi-next-baseline.json.

Zi8AlphaGetCandidates: 95.02813% -> 95.23011%.
Unit fuzzy: 96.37759% -> 96.52474%, about 31.88 weighted bytes gained.
Exact functions remain 11/12; exact code remains 5880/21664;
matched data remains 516/564. No complete unit or new exact function claimed.
All 1027 units were compared for fuzzy, matched-code, matched-data and exact
function measures: the alpha fuzzy improvement is the sole changed measure,
with no regressions.

Pool checked first: identical and empty. Main function stays 3946/3946
instructions and 0x3DA8 bytes, with the same 0x2B0 frame. Strict ctxdiff is
nonzero (3738 differences); existing scalar-stack displacement and register
allocation remain. Each of the 11 existing exact functions retains identical
instruction counts and ctxdiff diffs 0.

Baseline/candidate .rodata, .data, extab and extabindex have identical payloads
and canonical relocations. Relative to the target, extab and extabindex remain
byte-identical; the unchanged generated switch relocations remain unmatched.
The source rodata's pre-existing 330-byte size versus target 336 is unchanged;
objdiff still reports 100% for that section and the same exact-data accounting.
Advisory branch mapping checks 709 same-mnemonic branch pairs with zero
mapped destination mismatches, and 73/73 helper calls. It is not an exactness
or formal equivalence claim.

Full 43U build passes with the approved wrapper and WIBO_SJIS_MISSING_IMPORTS=1.
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No remote actions were performed.
