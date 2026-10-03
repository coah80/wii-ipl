# RGBA420 edge inner offset triple: six official-fuzzy-scored orders

Initial base `180e620c`; branch `agent/bittle/rgba420edge-offset-orders`.
Target `TMCJPEGDEC_converterYUV420toRGBA8edge`, 43U only. The sole editable source
was `s32 redOffset, greenOffset, blueOffset;` at original line 644, inside its
existing scope. No initializer, expression, assignment, type, other declaration,
helper, or scope moved. The final source only splits this declaration in place
and orders the three variables redOffset, blueOffset, greenOffset.

## Why the finite check was not already established

The official 87-build search in `fz20.attempts.md:1030..1054` covered the eight
leading declarations, not this inner triple. Its body preceded both the later
OR-expression change and `e8241734`'s red-owned luminance reconstruction. Wider
historical split/declaration trials mentioning these names do not retain the
six exact current-body, fixed-surroundings orders with official scores. The
read-only grouped inventory likewise states that this coverage was unproven.
No prior exhaustive equivalent finite coverage was found; this does not claim
none of the individual orders had ever appeared in a broader old trial.

Current baseline function SHA256:
`0c7dcbff2b82ffca9a9b1c5cf20396ab8bc6a5191844527a87a9ac13aa2d0b47`.
It is byte-identical at `e8241734` and the initial base. Original whole-source
SHA256: `d4651ae1f7dd68082c84008ecce8b12c8f9d1053bc09ec1c0694acbb114b9cba`.

## Neutral split and exactly six ordinary permutations

A fresh baseline object/full report reproduced 87.458336%, 480 bytes. Splitting
in the same red/green/blue order first produced an entirely byte-identical
object and complete 1,027-unit report. Only after that neutral prerequisite,
exactly six distinct permutations were compiled with ordinary real Ninja.
Each exact source/order/hash and compiler output was saved; every call invoked
MWCC successfully and source bytes were stable across compilation.

All six successful snapshots were scored with official objdiff, without
`--deduplicate`, using a private copy of the current project configuration,
preserving its options/metadata and freezing the original object. Only unit
names and target/base paths changed for the six snapshot units. Raw target
fuzzy selected the winner; batch aggregate measures were not used.

- red, green, blue: 87.458336%
- red, blue, green: 87.5% (retained, first minimal tied winner)
- green, red, blue: 87.458336%
- green, blue, red: 87.5%
- blue, red, green: 87.5%
- blue, green, red: 87.5%

Every order passes sibling-byte/report, exact-sibling, allocated-data, and
unit exact/code/data/link gates. This exhausts all six internal orders with
surrounding declarations fixed. It does not cover moves across other locals,
other scopes, initialized declarations, or other source forms. No further
order trial, converter run, or restart occurred.

## Initial fresh gates

- Function fuzzy: 87.458336% -> 87.5%; unit: 90.58702% -> 90.59006%
- Global fuzzy on initial base: 99.72766% -> 99.72768%
- Instructions stay 120/120; structural/positional score stays (12,77)
- The gain is visible in official fuzzy despite the unchanged coarse score
- Exact stays 2/13; matched code stays 660/6596; link/data totals unchanged
- All 12 sibling bodies unchanged; both YUV400 functions raw-byte exact,
  official 100%, ctxdiff zero (76/76 and 89/89 instructions)
- No 1,027-unit report regression; no allocated non-code sections
- Empty pools identical; literal audit has zero candidates/errors, twelve
  functions analyzed and unchanged unequal-size setter skipped
- Fresh selected-order rebuild equals its saved snapshot object
- Full default build, explicit progress/report/43U-ok targets, and diff check pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Global completion remains incomplete; this is partial fuzzy progress only.
Retained function SHA256:
`c06a346c894ec20ff2a228498a58327c09e19c94c3c235180feee962c1e12d43`.
Retained whole-source SHA256:
`b58c82974159e852c29f437365d55fec5330676a775fc1f5e81ce418ef224978`.

## Independent 4:2:0 edge model

The scalar model passes 12,039 vectors / 36,117 object executions against
selected candidate, original, and saved baseline; every one of 120 instructions
is covered in all three. It models Y[16][16], Cb[8][8], Cr[8][8] at offsets
4/260/324, horizontal pixel pairs, absolute output-row-parity vertical reuse,
edge dimension branches, and real sequential reads/stores when input aliases
output. All x origins satisfy the existing even-x assertion.

Coverage: 1,212 complete edge-size/scale/origin cases, 256 dimension-branch
cases, 64 additional row/column-residue cases, 6,400 saturation vectors, and
4,107 halfword-aligned overlaps wholly within the actual 0x184-byte convBuf.
State/descriptors remain separate. Additional odd-row tests bound height so
chroma reads remain in the logical planes. Every byte below the reserved stack
region, including guards, matches; preserved GPRs, SP, and LR pass. Additional
residue/alias cases are machine-level checks, not API-validity claims. These
bounded interpreter tests are not formal equivalence or Wii runtime tests.
The repository differential audit independently passes all 9,456 paired cases.

## Artifacts

`build/43U/rgba420edge-offset-orders/` holds original and split source/object/
full reports, frozen original/config, all six source/object snapshots and
compiler logs, `enumerate.py`, `orders.json`, official scoring project/report,
`results.json`, final fresh gate files, `verify.py`, `audit.py`, and audit output.
No remote writes, linking changes, or previously frozen branch edits.

## Clean rebase and final current-main comparison

Initial validated commit `6d9027a5` was cleanly rebased onto `17130b4b`, producing
source/evidence commit `62a0cc5d`. That base includes the merged RGB565411 gain.
No additional order was tried. The exact base's original grouped RGBA source
was built with the rebased surrounding tree to obtain a fresh baseline, then
the already-selected source was restored and freshly built. Both RGBA baseline
and selected objects remain byte-identical to their pre-rebase counterparts.

The merged RGB565 source is byte-identical to `17130b4b`; its entire baseline
and final unit report is unchanged (unit fuzzy 96.84735%). The fresh 1,027-unit
comparison changes only RGBA420edge's fuzzy score; all other units/functions
and exact/code/data/link measures are unchanged. RGBA420edge remains
87.458336% -> 87.5%; RGBA unit 90.58702% -> 90.59006%. Current-base global fuzzy
is 99.727745% -> 99.72777%. The source remains only the grouped triple split and
red/blue/green order, with no expression, initializer, type, or scope change.

Full default build, explicit progress/report/43U-ok targets, sibling exactness,
pool/literal checks, source/byte checks, and diff checks pass again. DOL SHA1:
`26116613f624061ba99c8d1a299aaa6efa85670d`. The independent model again passes
all 12,039 vectors / 36,117 executions, including 4,107 contained overlaps and
all 120 instructions in all three objects. The repository audit again passes
all 9,456 paired cases. Previous bounded-test limitations still apply.

Current-base artifacts are in `build/43U/rgba420edge-offset-orders-rebased/`,
including fresh baseline/candidate source and objects, complete baseline/final
reports, build/progress logs, `verification.log`, `final.ctx`, exact/pool/literal/
status/completion results, and both independent/repository audit outputs. The
original six-order artifacts remain untouched in the first evidence directory.
