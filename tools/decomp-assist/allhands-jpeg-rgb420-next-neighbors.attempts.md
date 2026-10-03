# Normal RGB565420 fixed neighborhood after greenOffset/lumaSkip

Base: `1e0643fee3a74948564a306c9d8bf1181777ca5f` (merged #1109), 43U only.
Leaf: `wii-jpeg-rgb420-next-neighbors`.
Branch: `agent/bittle/jpeg-rgb420-next-neighbors`.

## Scope and result

One authorized fixed-center pass around normal
`TMCJPEGDEC_converterYUV420toRGB565` at **95.28369%** finds **95.35461%**.
The first maximum, snapshot **0108**, swaps only the existing `texture` and
`yEnd` declarations, originally lines 481 and 484. Their pointer/scalar types,
scopes, assignment/use order and all other source bytes remain unchanged.
Both locals are assigned before use; no address escapes are added.

Exactly the same 24 uninitialized declarations at **476-499** in
`Texture_MCUtoRGB565.c` are eligible. No initializer, body, lifetime, helper,
header, compiler/linking setting, new local, artificial guard/padding, assembly,
volatile cast, adaptive center, restart or other-function trial occurs.
Closed RGB565411/420-edge raw bodies remain untouched. RGB565422 classification
remains unverified. No continuation follows this finite pass.

Fixed baseline names, in zero-based CSV index order:

```
output, width, redOffset, green, tileRow, texture, chromaSkip, height,
yEnd, luminance, crValue, value, cb, cr, column, xEnd, lumaSkip,
tileWidth, cbValue, greenOffset, blueOffset, red, state, blue
```

## Pinned context and historical coverage

Baseline whole-source SHA256:
`2786627085c80a77b1e10842267d36b4fa0e975adf4c220aad2fb8d842d6ca98`.
Function source, definition through closing brace and LF:
`dd4330430fd6d7277f756807d944d6b1962702ae97084faf02ee1d742f24ae9c`.
Declaration block:
`2fb0352a2e0546a92cbe8f8dbf8f791044ec426d644796814f8d85c02abf187d`.
Whole source excluding this block:
`31f419d9f4cf5774930d7ca6f639b14b969c31637c57572f6803c81908650a9c`.
Baseline whole object:
`6e46b9dadbfacd1b30cc290f6304395e56dd2e6cd41b4a501800f9c47af26eb9`.
Frozen original whole object:
`51fd09b6b6b2b7e07363f9286537e12ce2ef14e3e0f344ad142d29af66ed661e`.
Copied actual objdiff configuration:
`5a767a65a3c1ecc0b5a5a06679131566ff04cfe0871b20ab101d4dc90ac199ea`.
Unmodified official declaration tool:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

The prior official audit in `allhands-jpeg-rgb420-fuzzy-neighbors.attempts.md`
retained greenOffset/lumaSkip from a fixed 783-order neighborhood. Its immutable
manifest survives. Surrounding source is identical; exact current/prior pairs:
**(0,251), (251,0), (629,630), (630,629), (693,694), (694,693)**.
All six are freshly compiled and reproduce previous exact source/object hashes
and official function/unit scores. The other **777** orders were absent from
that manifest. The older structural-only fixed pass covered the prior center;
its missing official records were supplied by the preceding audit. Exact
intersection with still older capped adaptive trials is unknown because their
per-order snapshots are absent. No global novelty claim is made.

## Real finite enumeration and official scoring

The fresh leaf receives the verified idle cache once during setup. Every
subsequent command uses explicit leaf workdir, with no main mutation or further
main-cache copy. Configure uses approved cached dtk/objdiff/sjiswrap/bstool/
compiler/binutils paths, explicit `../toolchain/wibo-release64/wibo`, and
`WIBO_SJIS_MISSING_IMPORTS=1`. Tool hashes and actual compiler command are saved.

Fresh default 43U build, explicit `build/43U/ok`, full official report and empty
pool check pass before enumeration. The baseline RGB565 raw report/unit and
object match the previously tested candidate. All 1,027 current-base object
hashes are frozen; unrelated intervening merged changes remain fixed.

The unchanged generator loops, applied once to a fixed center, yield 276 swaps
plus 529 distinct moves minus 23 common adjacent swaps: **782 neighbors**, plus
baseline. All **783 orders** receive real Ninja/MWCC compilation. Duplicate
source orders alone are removed in first-seen order before compilation. No
object/score deduplication, structural filter, suppressed compile or adaptive
center occurs. Setup and selected-source rebuilds are separate validation
operations, not additional searched orders.

Every call emits an MWCC object-build line, changes object mtime and preserves
exact source bytes throughout compilation. Source/object/order/hash, argv,
timestamp and stdout/stderr evidence is immutable. There are **323 whole-object
hashes**, zero failed/no-work calls and zero source instabilities.

Official scoring copies the actual objdiff configuration, preserving settings,
metadata, mappings and scratch settings; only snapshot names and frozen
original/candidate paths differ. A one-unit baseline reproduces the full
baseline's raw functions, sections and measures exactly. All 783 snapshots
receive official reports without `--deduplicate`; artificial batch aggregate
measures are not selection objectives.

All snapshots preserve 12 sibling raw bodies/scores, 7 exact functions, function
sets, code/data/completion measures and empty allocated non-code sections.
Zero non-fuzzy admission failures occur:

- **220** baseline ties, including baseline
- **3** strict improvements
- **560** unit-fuzzy losses, rejected
- **223** admissible orders

The three improving orders, **108, 164 and 388**, all reach **95.35461%**, across
three distinct objects. Deterministic first best **0108** is retained.
All **782/782** original-center neighbors were evaluated. Only **5/782** of the
winner's immediate neighbors were observed in this pass, with **777 unobserved
here**. No winner fixed point, broader optimum, exact match or linking gain is
claimed; no additional pass or plateau exploration followed.

## Fresh selected-source gates

- Function fuzzy: **95.28369% -> 95.35461%**
- Unit fuzzy: **96.89909% -> 96.90556%**
- Global fuzzy on this base: **99.73148% -> 99.73151%**
- Function: **564/564 bytes, 141/141 instructions**, unchanged
- Structural/positional comparator: **(6,81) -> (6,81)**
- Exact functions/code: **7/13, 2648/6184 bytes**, unchanged
- All 12 sibling raw bodies/scores and seven raw exact functions preserved
- Allocated non-code sections empty and identical; string pool identical
- Literal audit: 12 functions, zero candidates/errors; unchanged setter skipped
  because source/target sizes differ
- Fresh final object equals immutable snapshot 0108 byte-for-byte
- Fresh full report reproduces 0108's raw function/section/unit records exactly
- All **1,027** report units/functions and object hashes checked; only the owned
  RGB565 target/unit changes, with no exact/code/data/link regression
- Actual objdiff configuration remains byte-identical
- Default build/progress, explicit 43U `ok`, source-scope and diff checks pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Final whole-source SHA256:
`62da8a9e925d142025f6f0618b8a156b62dc0f5aa67f9efc627402ceaa9ab840`.
Final function-source SHA256:
`b76f363ef15c2fccb5d7f2bcd6e287bcef9ef7053dccbb0420298d9b810a2f62`.
Final whole-object SHA256:
`419c0751c5d4cb67542a4de8a3f62b962fbe2254c2144745c3dbb9534e0faedd`.
Final 564-byte function SHA256:
`a908b8204eb77093056471764575943b498cef954d62af8960e3edea3d1451e2`.

## Sequential pixels and contained aliases

The geometric scalar model independently derives chroma rows from initial-row
parity, caches chroma for each pair, and reads each luminance byte from evolving
memory before packing/storing that pixel. Alias observation order is preserved.
It passes **15,260 vectors** against actual candidate, original and saved
baseline objects, totaling **45,780 executions**:

- 1,792 geometry/pattern cases over scales 1/2/4/8, even/aligned x origins,
  row residues, tile boundaries, minimum/wide pitches and random/constant inputs
- 6,400 saturation cases over all luminance bytes and signed chroma pairs from
  {-128,-1,0,1,127}
- 7,068 halfword-aligned aliases whose every input read/output stays inside the
  actual 0x184-byte conversion buffer, with state and descriptor separate

Every non-stack byte, including guards, agrees. Each actual object covers
**141/141 instructions** and preserves GPR14-GPR31, stack pointer and LR.
Starting rows that force chroma reads beyond the allocation are excluded.
Additional residues/aliases are machine diagnostics, not new API guarantees.
Arithmetic is bounded integer-only; these are bounded interpreter tests, not
formal equivalence or Wii hardware tests.

The unchanged repository JPEG suite passes **9,456 paired cases** across
28 functions with preserved nonvolatile registers, stack pointer and LR.

## Preserved evidence

The committed CSV records all 783 exact orders, source/object hashes, official
scores, compile/source flags, admission decisions and six prior-manifest indices.
CSV SHA256:
`01cf3debbe6f0d6cad3ba1909553628468022f647876d4a0bd8a9bd55fba4543`.

`/tmp/jpeg-rgb420-next-neighbors/` preserves immutable source/object/compiler
snapshots, calls/enumeration/manifest/selection/context/overlap JSON, frozen
original/baseline and actual config, raw official reports, all-unit hashes,
tool/command evidence, build/pool/literal/ctx output, scalar/suite results and
all scripts. A complete local workspace archive preserves evidence independently
of `/tmp`. Original executable bytes stay local. No remote write or merge.
