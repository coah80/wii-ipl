# Address drag-width reconstruction, 2026-10-03 UTC

Base `e4a94492`, branch `agent/bittle/address-drag-reconstruction`, 43U only.
Only `src/scene/address/iplAddress.cpp` and this log changed. Headers, metadata,
linking flags, other worktrees and earlier attempt logs are untouched.

## Recovered behavior and source structure

The original movePane_onDrag null-text-box and null-name exits skip the 0.01f
text-width margin. The baseline incorrectly added that margin unconditionally.
This was visible in the original branch destinations and also documented in
older fz10 attempts, but the incomplete correction had not been retained.

The new typed inline GetDragNameWidth helper receives the text box and a reference
to the real friend record. It evaluates the record address before entering the
measurement path, checks the text box, then derives/checks the name address.
This recovers the target's two early-exit regions, delayed name-member address,
font calls, character-width loop, and successful-only margin. An empty but valid
name still receives the margin, as the target does. The existing unused GetWidth
call and per-character GetFont lookup remain present.

The text box lookup now spells out the root-pane FindPaneByName call already
used by layout::Object's wrapper. An explicit right-edge value preserves the
existing single-precision add, ratio multiply, and negation sequence; it does
not combine ratios, reassociate operations, or change the comparison. Together,
these source boundaries make the complete function instruction-exact.

## Attempts

- Read scene4, data-d7, sol-med and fz10 drag-width evidence before iterating.
- Moving only the margin to the measured branch improved 92.451614 -> 93.741936%.
  The target's margin-first addition reached 93.80645%.
- Computing the typed friend-record reference before the guard reached 98.064514%.
- A nullable name-pointer helper reached 98.741936% but 156/155 instructions.
  The friend-record-reference helper recovered 155/155 and 99.80645%.
- An explicit projected right-edge accumulator recovered the target FP register
  lifetime and reached 99.870964%. Mutating the translation vector instead grew
  the function and was rejected.
- Direct root-pane lookup resolved the last four receiver/literal register
  operands, reaching 100.0%. No parameter or declaration sweep was used.
- No new assembly, use-site volatile, dummy storage, padding, uninitialized
  values, compiler-option changes or linking experiments were introduced.

## Verification

Before -> after:
- movePane_onDrag: 92.451614 -> 100.0% objdiff; 153 -> 155 instructions against
  target 155; ctxdiff diffs 0 across the whole 0x26C-byte function.
- Unit fuzzy: 99.69818 -> 99.89328%.
- Exact functions 97/101 -> 98/101; matched code 21236 -> 21856 / 23988 bytes.
- Data 1964/1964 (100%) and linked status unchanged.
- Fresh baseline/candidate object comparison: all 97 previously objdiff-exact
  function streams are unchanged. Raw .data, .rodata, .sbss, .sdata, .sdata2 and
  .ctors bytes/extents are unchanged.
- Pool: all 81 strings identical to target.
- Literal audit: 86 arguments checked across 100 functions, no candidates or
  errors. FriendListCache::update is skipped for its pre-existing size mismatch.
- Full 1027-unit report has no exact-function/code/data/fuzzy regressions.
- Full 43U build and build/43U/ok passed. DOL SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

Host behavior verification extracts the production helper and method bodies and
uses deterministic UI/controller/font stubs. With -fno-fast-math,
-ffp-contract=off and undefined-behavior/bounds sanitizers, all 200,000 geometry
cases agree bit-for-bit with an independent target-ordered FP reference. Coverage
includes 66,667 null-text-box cases, empty/nonempty UTF-16 names, page offsets,
varied projection widths, both clamp branches and comparison boundaries. Font
lookup/width/character-call counts are also checked. Embedded name arrays are
valid objects; invalid-record/null-name pointer execution and Wii runtime UI
behavior are not claimed.

Private evidence: `/tmp/address-drag-reconstruction/` contains baseline/final
reports and source objects, drag-final.ctx, pool/literal audits, full-build.log,
validate_drag.py and drag-tests.log, plus the rejected source experiments. No
retail assembly or binary is included in this commit.

GATE: movePane_onDrag exact, behavior correction verified, all prior exact/data
metrics preserved. Other unit remainders and linking remain open. Frozen for
independent parent validation.
