# RGB565411 fixed neighborhood after the lumaSkip/tileRow gain

Base: `e8c465a0827d9c907fa6b6da62d93ad633ca33ac` (merged #1103), 43U only.
Leaf: `wii-jpeg-rgb411-next-neighbors`.
Branch: `agent/bittle/jpeg-rgb411-next-neighbors`.

## Fixed scope

One authorized fixed-center pass around normal
`TMCJPEGDEC_converterYUV411toRGB565` at **91.013824%**, using exactly the same
24 contiguous uninitialized declarations at lines 169-192 in
`Texture_MCUtoRGB565.c`. No adaptive center changes, restart, broader search,
new local, artificial guard/padding, assembly, volatile cast, compiler setting,
initializer, type, scope, assignment, expression or sibling change.

The fixed center's declaration names, in zero-based CSV index order:

```
output, tileRow, cbValue, blue, state, tileWidth, crValue, width,
height, chromaSkip, texture, luminance, cb, cr, column, xEnd,
yEnd, redOffset, lumaSkip, greenOffset, value, red, blueOffset, green
```

The only retained change swaps the existing `s32 redOffset;` and `u8 value;`
lines, originally 186 and 189. Their types and all assignments remain intact;
both are assigned before use. Every byte outside the eligible block is fixed.

## Pinned baseline and exact history overlap

Baseline whole-source SHA256:
`5807c83409afebc021a1311143f045eb5a147ce8a60ea7dd3b1d7bed1ec6314d`.
Function source, definition through closing brace and LF:
`af2899de091862526a9012f8b780cc2e01699a012f7b057b56320eee701446d4`.
Declaration-block SHA256:
`b616ee0fdc8d9c4e77b983924806766046730c6de9ee06b9b49555a5ac81d39f`.
Whole-source context excluding the block:
`f2d7fddcc33d949cc1ca7ae550e1faa6441a0db2dc6055fd7d8aa34875af6d07`.
Baseline whole-object SHA256:
`7f4ca0cfa4bfccfd13f7b0dc476830a8e4531a0e299930ce2ded76ed68b20c94`.
Frozen original whole-object SHA256:
`51fd09b6b6b2b7e07363f9286537e12ce2ef14e3e0f344ad142d29af66ed661e`.
Actual copied objdiff configuration SHA256:
`5a767a65a3c1ecc0b5a5a06679131566ff04cfe0871b20ab101d4dc90ac199ea`.

The prior `allhands-jpeg-rgb411-fixed-neighbors.attempts.md` records the full
immediate neighborhood around 90.89862%, selecting lumaSkip/tileRow at
91.013824%. That manifest survives. Exact source-order comparisons, after
checking identical surrounding source, establish six overlapping orders:

| Current index | Previous index |
| ---: | ---: |
| 0 | 40 |
| 40 | 0 |
| 313 | 314 |
| 314 | 313 |
| 657 | 658 |
| 658 | 657 |

All six are freshly compiled. The other **777** current orders were absent
from that manifest. Older capped searches have no surviving per-order
snapshots, so their exact overlap remains unknown. No global novelty claim is
made; no closed RGB422, RGB420, or edge group is searched again.

## Setup, enumeration and official scoring

The fresh leaf copies the parent's idle verified cache once during setup.
All subsequent commands use the explicit leaf workdir; no main changes or
additional main-cache copies occur. Configure uses the approved cached dtk,
objdiff, sjiswrap, bstool, compilers and binutils paths, the explicit
`../toolchain/wibo-release64/wibo` wrapper and
`WIBO_SJIS_MISSING_IMPORTS=1`. Tool hashes and actual compiler command are saved.

A fresh default 43U build, explicit `build/43U/ok`, official full report and
empty-pool check pass before enumeration. The baseline full report and all
1,027 object hashes exactly equal the previously tested selected leaf.

The unchanged declaration tool's two generator loops yield **276 swaps** and
**529 distinct moves**, sharing **23** adjacent swaps: **782 unique immediate
neighbors**, plus baseline, **783 real audit compilations**. Duplicate source
orders are removed in first-seen order before compilation. There is no object
or score deduplication, structural filtering, skipped compilation, or adaptive
center. The official tool SHA256 remains
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

Each of the 783 Ninja/MWCC calls emits an object-build line, changes object
mtime and preserves source bytes during compilation. Every exact source,
object, order, timestamp, argv, stdout/stderr and hash is recorded. There are
**336 distinct whole objects**, zero failed/no-work calls and zero source
instabilities. Initial baseline and final selection builds are separate
validation operations, not extra searched orders.

A private copy of the actual objdiff configuration retains settings, metadata,
mappings and scratch settings. Only unit names and frozen target/base paths
change. A one-unit baseline reproduces the full baseline's raw function,
section and unit records exactly. All 783 frozen objects receive official
reports without `--deduplicate`; batch aggregate measures are never the
selection objective.

All snapshots preserve the function set, all 12 sibling raw bodies and scores,
all 7 exact functions, allocated non-code bytes and code/data/completion
measures. Zero non-fuzzy admission failures occur:

- 237 baseline ties, including baseline
- 14 strict improvements
- 532 unit-fuzzy losses, rejected
- 251 admissible orders

The maximum **91.129036%** occurs at calls **258, 259, 651, 652, 653** across two
whole-object hashes. Deterministic first best **0258** is retained. Its only
source change is the redOffset/value declaration swap.

All **782/782** neighbors of the fixed starting center were evaluated.
The selected winner has only **5/782** neighbors observed in this pass, with
**777 unobserved here**. No fixed point around the winner, broader optimum,
exact match, or linking gain is claimed. No continuation followed.

## Fresh final gates

- Function fuzzy: **91.013824% -> 91.129036%**
- Unit fuzzy: **96.86675% -> 96.88293%**
- Global fuzzy on this base: **99.73129% -> 99.73133%**
- Function: **868/868 bytes, 217/217 instructions**, unchanged
- Structural/positional comparator: **(21,142) -> (21,142)**
- Exact functions/code: **7/13, 2648/6184 bytes**, unchanged
- Every sibling body/score and all seven raw exact functions preserved
- Empty allocated non-code sections and string pool identical
- Literal audit: 12 functions, no candidates/errors; unchanged setter skipped
  for differing instruction counts
- Fresh final whole object equals frozen snapshot 0258 byte-for-byte
- Fresh full report equals that snapshot's function/section/unit records
- All **1,027** report units, function scores and compiled-object hashes checked;
  only the intended RGB565 target/unit changes, no code/data/link/exact loss
- Actual objdiff configuration remains byte-identical
- Ordinary default build/progress and explicit 43U `ok` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- Exact source-scope check and `git diff --check` pass

Final whole-source SHA256:
`dd72be279635ec04682558ba09b79e74284f52a70e7cbe22620b0190fdc4fc5f`.
Final function-source SHA256:
`daac265236b0145854c5722e96a1e747ae7716ecdd7dfa4d73e04ed352bddb7e`.
Final whole-object SHA256:
`e01d44ae67a7bd0d969025f3bbe21d389c3d70c0ce0ced1ce3650d748d3a7c15`.
Final 868-byte function SHA256:
`156f10972ae5feb812e6b47530909657f24d1aa4bf6027cd4a837f163728335d`.

## Pixel, alias and repository differential checks

The unchanged repository JPEG suite passes **9,456 paired cases** across
28 functions, preserving GPR14-GPR31, stack pointer and LR.

The separate sequential RGB565411 scalar reference passes **13,366 vectors**
against actual candidate, original and saved baseline objects, totaling
**40,098 object executions**:

- 2,016 geometry/pattern vectors span supported scales 1/2/4/8, aligned x
  origins, row residues, tile boundaries, minimum/wide pitches and random or
  constant samples
- 6,400 saturation vectors cover every luminance byte and all pairs of signed
  chroma in {-128,-1,0,1,127}
- 4,950 halfword-aligned input/output overlap vectors keep every output write
  within the actual 0x184-byte conversion buffer; descriptor/state stay separate

The scalar model caches each group's chroma and reads each luminance byte from
its evolving memory immediately before packing/storing that pixel. It therefore
preserves alias observation order. Every non-stack byte, including guards,
agrees. All three actual objects exercise **217/217 instructions** and preserve
nonvolatile registers, stack pointer and LR. Arithmetic remains bounded integer
arithmetic with no FPU reassociation. Extra residue/alias diagnostics do not
create new API guarantees. These are bounded interpreter tests, not a formal
proof or Wii hardware test.

## Evidence and endpoint

The committed CSV contains all 783 exact order tuples, source/object hashes,
official target/unit scores, compile/source flags, gate decisions, and previous
manifest indices for the six repeated orders. CSV SHA256:
`bda3bc6a1c5187182e0e65df77f2980e0f772348492624bb8ab425e2a10f173d`.

`/tmp/jpeg-rgb411-next-neighbors/` preserves all immutable snapshots and
compiler output, calls.jsonl, enumeration.json, manifest.json, selection.json,
historical-overlap.json, actual config, frozen originals/baseline, raw official
reports, all-unit hashes, compiler/tool evidence, build/pool/literal/ctx logs,
scalar/differential results and the enumerator/recorder/scorer/verifier/model.
A complete local workspace archive preserves the evidence independently of
`/tmp`. Original executable bytes remain local. No remote writes, merge,
continuation or broader search was performed.
