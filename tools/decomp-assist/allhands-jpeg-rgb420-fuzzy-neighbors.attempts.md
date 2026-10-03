# Normal RGB565420: missing official-score fixed-neighborhood audit

Base: `ccffee8af5cd76fe326187d93418d3d62ee3c177` (merged #1107), 43U only.
Leaf: `wii-jpeg-rgb420-fuzzy-neighbors`.
Branch: `agent/bittle/jpeg-rgb420-fuzzy-neighbors`.

## Result and explicit historical repetition

One authorized fixed-center audit finds a strict official-fuzzy improvement:
**95.17731% -> 95.28369%**. Snapshot **0251**, the unique maximum, swaps only the
existing `greenOffset` and `lumaSkip` declarations. Both retain their `s32`
types, function scope and assignment/use order, with assignments before use.
No initializer, body, lifetime, helper, header or compiler-setting change.

**Every one of the 783 orders deliberately repeats historical compilation.**
`allhands-jpeg-rgb420-declarations.attempts.md:123-138` records baseline plus
all 782 neighbors of this exact source order with no structural/positional
improvement at `(6,81)`. That log expressly disclaims official-fuzzy closure.
The prior immutable intermediate snapshots are absent, and their official
scores were not recorded. The present run fills that scoring gap; it does not
claim new declaration-order coverage. The earlier 1,000-order adaptive run
changed center twice; exact overlap with it was not logged and remains unknown.

The entry function source is identical to merged PR #1081 (`2c7fa341`). Later
sibling changes mean this run uses the complete current translation unit and
current verified configuration. Closed normal RGB565411 and RGB565420-edge
bodies are unchanged; RGB565422 classification remains unverified.

Only the same 24 existing uninitialized declarations at **476-499** in normal
`TMCJPEGDEC_converterYUV420toRGB565`, `Texture_MCUtoRGB565.c`, may reorder.
Every other source byte, type, scope, initializer, assignment and expression is
fixed. No new local, artificial guard/padding, assembly, volatile cast, adaptive
center, restart, other-function search or body/lifetime rewrite.

Baseline declaration names, in zero-based CSV index order:

```
output, width, redOffset, green, tileRow, texture, chromaSkip, height,
yEnd, luminance, crValue, value, cb, cr, column, xEnd, greenOffset,
tileWidth, cbValue, lumaSkip, blueOffset, red, state, blue
```

## Pinned context

Baseline source SHA256:
`665a27e9ab8f437ba1656f3a4e18739a5b6531eb2438f0c14769011c2b9c431c`.
Baseline function, definition through closing brace and LF:
`c8c40679d9d2fd3ce5841870fc4098c88a371a7e9082d41242ca6c8655507aee`.
Eligible declaration block:
`4684d17812ba8aeb2f9158d46ce19da991a070767de2859dcc572615a75fdb08`.
Whole source excluding the block:
`31f419d9f4cf5774930d7ca6f639b14b969c31637c57572f6803c81908650a9c`.
Baseline whole object:
`de691febfdde2db43da14ecca22ecdbd5e0c7fbb416ca2580ffaa4991e8a1bbc`.
Baseline compiled 564-byte function:
`11b57090aaced769847909dca9acd8dbdec07973212494dcd1741aa969adbedf`.
Frozen original whole object:
`51fd09b6b6b2b7e07363f9286537e12ce2ef14e3e0f344ad142d29af66ed661e`.
Actual copied objdiff configuration:
`5a767a65a3c1ecc0b5a5a06679131566ff04cfe0871b20ab101d4dc90ac199ea`.
Unmodified official declaration tool:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

## Finite real compilation and complete official scoring

The fresh leaf copies the verified idle cache once during setup. Subsequent
commands use explicit leaf workdir, with no main mutation or additional cache
copy. Configure uses approved cached dtk/objdiff/sjiswrap/bstool/compiler/
binutils paths, explicit `../toolchain/wibo-release64/wibo`, and
`WIBO_SJIS_MISSING_IMPORTS=1`; tool hashes and exact compiler command are saved.
Fresh default 43U build, explicit `build/43U/ok`, full official report and empty
pool check establish the baseline; all 1,027 compiled object hashes are frozen.

The unchanged generator loops, fixed once at baseline, yield 276 distinct
swaps and 529 distinct moves with 23 shared adjacent swaps: **782 neighbors**,
plus baseline, **783 real Ninja/MWCC audit compilations**. Duplicate source
orders alone are removed in first-seen order before execution. No object/score
deduplication, structural-score filtering, suppressed compile or adaptive
center occurs. Initial baseline and selected-source rebuilds are separate
validation operations, not additional searched orders.

Each call emits an MWCC build line, changes object mtime and preserves exact
source bytes through compilation. Immutable source/object snapshots, orders,
hashes, argv, timestamps and stdout/stderr are retained. There are **327 distinct
whole objects**, zero failed/no-work calls and zero source instabilities.

The scorer copies the actual objdiff configuration, preserving all settings,
metadata, mappings and scratch settings. Only unique unit names and frozen
original/candidate paths change. A private one-unit baseline reproduces the
full baseline's raw functions, sections and measures exactly. All 783 snapshots
receive official reports without `--deduplicate`. Artificial batch aggregates
are never selection objectives.

All snapshots preserve the function set, all 12 sibling raw bodies/scores,
7 exact functions, code/data/completion measures and empty allocated non-code
sections. Zero non-fuzzy admission failures occur:

- **217** baseline ties, including baseline
- **4** strict improvements
- **562** unit-fuzzy losses, rejected
- **221** admissible orders

The unique maximum is snapshot **0251**, **95.28369%**. It swaps the two existing
`s32` declarations originally at lines **492 and 495**. Its structural/positional
score remains `(6,81)`, illustrating the missing official-score measurement
rather than an improvement under the old comparator.

All **782/782** original-center neighbors are covered. The retained winner has
only **5/782** immediate neighbors observed in this pass, with **777 unobserved
here**. No winner fixed point, exhaustive 24! result, broader optimum, exact
match or linking gain is claimed. No continuation followed.

## Fresh retained-source gates

- Target fuzzy: **95.17731% -> 95.28369%**
- Unit fuzzy: **96.88939% -> 96.89909%**
- Global fuzzy on this base: **99.73140% -> 99.73142%**
- Function: **564/564 bytes, 141/141 instructions**, unchanged
- Structural/positional comparator: **(6,81) -> (6,81)**
- Exact functions/code: **7/13, 2648/6184 bytes**, unchanged
- All 12 sibling raw bodies/scores and seven exact raw functions preserved
- Empty allocated non-code sections and string pool identical
- Literal audit: 12 functions, no candidates/errors; unchanged setter skipped
  because source/target sizes differ
- Fresh rebuilt object equals immutable snapshot 0251 byte-for-byte
- Fresh full report reproduces 0251's raw function/section/unit records exactly
- All **1,027** unit/function reports and object hashes checked; only the owned
  RGB565 target/unit changes, with no exact/code/data/link regression
- Actual objdiff configuration remains byte-identical
- Default build/progress, explicit 43U `ok`, source-scope and diff checks pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Final source SHA256:
`2786627085c80a77b1e10842267d36b4fa0e975adf4c220aad2fb8d842d6ca98`.
Final function-source SHA256:
`dd4330430fd6d7277f756807d944d6b1962702ae97084faf02ee1d742f24ae9c`.
Final whole-object SHA256:
`6e46b9dadbfacd1b30cc290f6304395e56dd2e6cd41b4a501800f9c47af26eb9`.
Final 564-byte function SHA256:
`ec1a9411b9af3228c6c2573bcfae554cf1e57529f0aa7eec0519e0b212a5c26d`.

## Sequential normal-pixel and contained-alias checks

An independent scalar model uses geometric row/column indices rather than
machine cursor updates. Chroma row follows initial-row parity; each two-pixel
group caches chroma, while each luminance byte is read from evolving memory
immediately before that pixel is packed/stored. Aliasing therefore preserves
read/write observation order.

The model passes **15,260 vectors** against actual candidate, original and saved
baseline objects, totaling **45,780 executions**:

- **1,792** geometry/pattern vectors over scales 1/2/4/8, aligned/even x origins,
  row residues, tile boundaries, minimum/wide pitches and random/constant samples
- **6,400** saturation vectors cover every luminance byte and all signed chroma
  pairs from {-128,-1,0,1,127}
- **7,068** halfword-aligned aliases keep every input sample read and output
  halfword inside the actual 0x184-byte conversion buffer; state and descriptor
  remain separate

All non-stack bytes, including guards, match. Each actual object covers
**141/141 instructions** and preserves GPR14-GPR31, stack pointer and LR.
Starting rows that would force a chroma read outside the allocation are excluded.
Additional residue/alias vectors are machine-level diagnostics, not new public
API promises. Arithmetic remains bounded integer-only. These are bounded
interpreter checks, not formal equivalence or Wii hardware tests.

The unchanged repository JPEG suite passes **9,456 paired cases** across 28
functions with preserved nonvolatile registers, stack pointer and LR.

## Evidence

The committed CSV records all 783 exact order tuples, source/object hashes,
official target/unit scores, compile/source flags, admission decisions and
explicit historical-repetition markers. CSV SHA256:
`21cb30045561c8862ff8270b5d9448af1daa85e53196140fc34fcfb9aaabf900`.

`/tmp/jpeg-rgb420-fuzzy-neighbors/` preserves all immutable source/object and
compiler-output snapshots; calls/enumeration/manifest/selection/context JSON;
actual config, original/baseline, raw official reports and all-unit hashes;
tool/command evidence, build/pool/literal/ctx results; model/suite results and
all runner/scorer/verifier/model scripts. A full local workspace archive
preserves evidence independently of `/tmp`. Original executable bytes remain
local. No remote writes or merge occurred.
