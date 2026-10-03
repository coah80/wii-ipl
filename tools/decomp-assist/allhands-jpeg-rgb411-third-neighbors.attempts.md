# RGB565411 fixed neighborhood after redOffset/value

Base: `07a021918e562e2b094f3f68787a575227b4e2c8` (merged #1104), 43U only.
Leaf: `wii-jpeg-rgb411-third-neighbors`.
Branch: `agent/bittle/jpeg-rgb411-third-neighbors`.

## Scope and inputs

One authorized fixed-center pass around normal
`TMCJPEGDEC_converterYUV411toRGB565` at **91.129036%**. Exactly the same 24
existing uninitialized declarations at lines 169-192 in
`Texture_MCUtoRGB565.c` are eligible. Every other source byte, initializer,
type, scope, assignment, expression and sibling remains fixed. No adaptive
center, restart, broader search, new local, artificial guard/padding, assembly,
volatile cast, compiler/header/linking-setting change or remote write.

The fixed baseline names, in zero-based CSV index order:

```
output, tileRow, cbValue, blue, state, tileWidth, crValue, width,
height, chromaSkip, texture, luminance, cb, cr, column, xEnd,
yEnd, value, lumaSkip, greenOffset, redOffset, red, blueOffset, green
```

Baseline whole-source SHA256:
`dd72be279635ec04682558ba09b79e74284f52a70e7cbe22620b0190fdc4fc5f`.
Function source, definition through closing brace and LF:
`daac265236b0145854c5722e96a1e747ae7716ecdd7dfa4d73e04ed352bddb7e`.
Declaration-block SHA256:
`e976349aeb6992abb9b71a1a5cd5c7c6473bf510b791156765e01cd69dc63105`.
Whole-source context excluding this block:
`f2d7fddcc33d949cc1ca7ae550e1faa6441a0db2dc6055fd7d8aa34875af6d07`.
Baseline whole-object SHA256:
`e01d44ae67a7bd0d969025f3bbe21d389c3d70c0ce0ced1ce3650d748d3a7c15`.
Frozen original whole-object SHA256:
`51fd09b6b6b2b7e07363f9286537e12ce2ef14e3e0f344ad142d29af66ed661e`.
Actual objdiff configuration SHA256:
`5a767a65a3c1ecc0b5a5a06679131566ff04cfe0871b20ab101d4dc90ac199ea`.
Unmodified declaration tool SHA256:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

## History and overlap

The previous two fixed audits are documented in
`allhands-jpeg-rgb411-fixed-neighbors.attempts.md` and
`allhands-jpeg-rgb411-next-neighbors.attempts.md`. Their full manifests survive;
the source context outside the declaration block is identical.

Current/prior index pairs for the first manifest:
**(40,258), (258,40)**.
Current/prior index pairs for the second manifest:
**(0,258), (258,0), (651,652), (652,651), (715,716), (716,715)**.

Thus seven current orders overlap the union of those manifests:
**0,40,258,651,652,715,716**. They are all freshly compiled, reproducing exact
prior source/object hashes and official target/unit scores. The other **776**
orders were absent from both manifests. Older capped-search snapshots were
lost, so exact earlier overlap remains unknown. No global novelty claim is
made, and no closed RGB422/RGB420/edge group is searched.

## Real fixed enumeration and scoring

After the fresh leaf's one-time setup cache copy, all commands use the explicit
leaf workdir. No main mutation or further main-cache copy occurs. Configure
uses the approved cached dtk, objdiff, sjiswrap, bstool, compiler and binutils
paths, `../toolchain/wibo-release64/wibo`, and
`WIBO_SJIS_MISSING_IMPORTS=1`; actual command/tool hashes are saved.

Fresh default 43U build, explicit `build/43U/ok`, full official report and pool
check pass. Baseline report and all 1,027 object hashes exactly equal the
previously tested selected leaf.

The unchanged tool's two generators, fixed at the baseline, produce 276 swaps
and 529 distinct moves with 23 shared adjacent swaps: **782 unique neighbors**,
plus baseline. All **783** orders receive real Ninja/MWCC compilation. Each
call emits an object-build line, changes object mtime and has stable exact
source bytes. The recorder preserves argv/timestamps, source/order/object
hashes, immutable source/object snapshots and stdout/stderr. There are **335
whole-object hashes**, zero failed/no-work calls and zero unstable sources.
Initial baseline and final selection builds are separate validation operations.

Source-order duplicates are removed in first-seen order before compilation;
no object or score deduplication occurs. No structural-score filter, compiler
suppression or live-object score substitution is used. A copied actual objdiff
configuration preserves settings/metadata/mappings; only unique snapshot unit
names and frozen target/base paths differ. A private one-unit baseline first
reproduces the full baseline's raw functions, sections and unit measures.
All 783 frozen objects then receive official reports without `--deduplicate`.
Batch aggregate measures are not selection objectives.

All 783 snapshots preserve 12 sibling bodies/scores, 7 exact functions, the
function set, code/data/completion measures and empty allocated non-code
sections. There are zero non-fuzzy gate failures:

- **229** baseline ties, including baseline
- **1** strict improvement
- **553** unit-fuzzy losses, rejected
- **230** admissible orders

The sole strict improvement is **snapshot 0118**, **91.17512%**, swapping only
`u32 tileWidth;` and `s32 lumaSkip;`, originally lines 174 and 187. Their types,
assignments and scopes remain unchanged, and both are assigned before use.
The frozen snapshot is retained only after final gates pass.

All **782/782** neighbors of the starting center are covered. The selected
winner has only **5/782** immediate neighbors observed in this pass, with
**777 unobserved here**. No fixed point around the winner, exact match, broader
optimum or linking improvement is claimed. No continuation followed.

## Fresh retained-source gates

- Function fuzzy: **91.129036% -> 91.17512%**
- Unit fuzzy: **96.88293% -> 96.88939%**
- Global reported fuzzy: **99.73133% -> 99.73133%** (display precision)
- Function: **868/868 bytes, 217/217 instructions**, unchanged
- Structural/positional comparator: **(21,142) -> (21,141)**
- Exact functions/code: **7/13, 2648/6184 bytes**, unchanged
- All 12 sibling raw bodies/scores and seven raw exact functions preserved
- Allocated non-code sections empty and identical; pool identical
- Literal audit: 12 functions, zero candidates/errors; unchanged setter skipped
  because source/target sizes differ
- Fresh selected-source object equals immutable 0118 object byte-for-byte
- Full official report reproduces 0118's function/section/unit records exactly
- All **1,027** unit reports, function scores and object hashes checked: only
  the intended RGB565 target/unit changes; no exact/code/data/link loss
- Actual objdiff configuration remains byte-identical
- Ordinary default build/progress, explicit 43U `ok`, source-scope check and
  `git diff --check` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Final whole-source SHA256:
`665a27e9ab8f437ba1656f3a4e18739a5b6531eb2438f0c14769011c2b9c431c`.
Final function-source SHA256:
`ac4d5db219203b8c72d677860932ef43ab95200689c8b34980b97aea90c1b74a`.
Final whole-object SHA256:
`de691febfdde2db43da14ecca22ecdbd5e0c7fbb416ca2580ffaa4991e8a1bbc`.
Final 868-byte function SHA256:
`266888021eac75d4714a65febef74b272e4b73eb5753e485252029d4d2a51238`.

## Behavior and alias checks

The unchanged repository JPEG suite passes **9,456 paired cases** across 28
functions, preserving GPR14-GPR31, stack pointer and LR.

The independent sequential RGB565411 scalar model passes **13,366 vectors**
against actual candidate, original and saved baseline objects, totaling
**40,098 object executions**:

- 2,016 geometry/pattern vectors span all supported scales 1/2/4/8, aligned x
  origins, row residues, tiled boundaries, minimum/wide pitches and random or
  constant samples
- 6,400 saturation vectors span every luminance byte and all signed chroma
  pairs from {-128,-1,0,1,127}
- 4,950 halfword-aligned overlap vectors keep every output within the actual
  0x184-byte conversion-buffer allocation; descriptor and state stay separate

The scalar model caches group chroma and reads each luminance byte from current
evolving memory before packing/storing that pixel, preserving alias observation
order. Every non-stack byte, including guards, agrees. Each actual object
exercises **217/217 instructions** and preserves nonvolatile registers, stack
pointer and LR. Arithmetic is bounded integer-only. Additional alias/residue
vectors are machine-level diagnostics, not new API promises; these bounded
interpreter checks are not formal equivalence or Wii hardware tests.

## Preserved evidence

The committed CSV records all 783 exact order tuples, source/object hashes,
official target/unit scores, compile/source flags, admission decisions and
both prior manifest indices. CSV SHA256:
`d0ce3787dc32d52923941802e21708a883b070fe66df4226821ab1e271d45046`.

`/tmp/jpeg-rgb411-third-neighbors/` preserves every immutable source/object and
compiler-output snapshot; calls, enumeration, manifest, selection and historical
overlap JSON; copied actual config, frozen baseline/original, raw official
reports, all-unit hashes, tool/command evidence, build/pool/literal/ctx output,
pixel/suite results and all runner/scorer/verifier/model scripts. A complete
local workspace archive preserves the evidence independently of `/tmp`.
Original executable bytes remain local. No remote writes or merge occurred.
