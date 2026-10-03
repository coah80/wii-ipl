# Normal RGB565420 fixed neighborhood after texture/yEnd

Base: `d4b9850a45dca95ea4bd8a86dbadeb95a55118bb` (merged #1111), 43U only.
Leaf: `wii-jpeg-rgb420-third-neighbors`.
Branch: `agent/bittle/jpeg-rgb420-third-neighbors`.

## Scope and result

One authorized fixed-center pass around normal
`TMCJPEGDEC_converterYUV420toRGB565` at **95.35461%** finds **95.42553%**.
The unique maximum, snapshot **0116**, swaps only existing `yEnd` and `lumaSkip`
declarations, originally lines 481 and 492. Both keep their `s32` types,
function scope and assignment/use order; both are assigned before use.

Only the same 24 uninitialized declarations at **476-499** in
`Texture_MCUtoRGB565.c` may reorder. All other source bytes, initializers,
types, scopes, assignments, expressions and siblings are frozen. No new local,
artificial guard/padding, assembly, volatile cast, compiler/header/linking
change, adaptive center, restart, body/lifetime rewrite or other-function trial.
Closed RGB565411/420-edge bodies are unchanged; RGB565422 remains unverified.
No continuation follows this finite pass.

Fixed baseline names, in zero-based CSV index order:

```
output, width, redOffset, green, tileRow, yEnd, chromaSkip, height,
texture, luminance, crValue, value, cb, cr, column, xEnd, lumaSkip,
tileWidth, cbValue, greenOffset, blueOffset, red, state, blue
```

## Pinned context and history

Baseline whole source:
`62da8a9e925d142025f6f0618b8a156b62dc0f5aa67f9efc627402ceaa9ab840`.
Function source, definition through closing brace and LF:
`b76f363ef15c2fccb5d7f2bcd6e287bcef9ef7053dccbb0420298d9b810a2f62`.
Declaration block:
`394a9807af5393770f67bf3451e822c22fa539f5cb18eb4ff29d040959c7a820`.
Whole source excluding the block:
`31f419d9f4cf5774930d7ca6f639b14b969c31637c57572f6803c81908650a9c`.
Baseline whole object:
`419c0751c5d4cb67542a4de8a3f62b962fbe2254c2144745c3dbb9534e0faedd`.
Frozen original whole object:
`51fd09b6b6b2b7e07363f9286537e12ce2ef14e3e0f344ad142d29af66ed661e`.
Copied actual objdiff configuration:
`5a767a65a3c1ecc0b5a5a06679131566ff04cfe0871b20ab101d4dc90ac199ea`.
Unmodified official declaration tool:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

Both prior normal420 official manifests survive, with identical surrounding
source. Exact current/prior pairs:

- `fuzzy-neighbors`: **(108,251), (251,108)**
- `next-neighbors`: **(0,108), (108,0), (387,388), (388,387), (451,452), (452,451)**

The union has seven repeated current orders: **0,108,251,387,388,451,452**.
Every repeated order is freshly compiled and reproduces exact prior source/
object hashes and official target/unit scores. The other **776** orders were
absent from both manifests. Older capped adaptive snapshots are unavailable,
so exact earlier overlap remains unknown. No global novelty claim is made.

## Bounded storage and setup

At admission the root filesystem had 8.7GB free, while `/tmp` had only 198MB.
Evidence and `TMPDIR` are therefore workspace-local:

- `/workspace/scratch/0128b1ed02cc/jpeg-rgb420-third-evidence`
- `/workspace/scratch/0128b1ed02cc/jpeg-rgb420-third-temp`

Only the 83MB mutable 43U build cache is copied once. Existing immutable
compiler/tool/binutils directories are reused through symlinks to the preserved
previous leaf; no redundant full cache is copied and no prior evidence is
removed. Recorded shared compiler/tool hashes are unchanged after validation.
Workspace free space is checked every 100 audit calls with a 1GiB stop floor.
It remains safe, about 7.1GB at the post-model storage check; this evidence is
about 50MB and the
temporary directory is 4KB. `/tmp` free space remains unchanged at 198MB.

All commands after setup use explicit leaf workdir; main is not mutated or
recopied. Configure retains approved cached tool paths,
`../toolchain/wibo-release64/wibo`, and `WIBO_SJIS_MISSING_IMPORTS=1`. Actual
compiler command/tool hashes are saved. Fresh default 43U, explicit `ok`, full
report and empty-pool check establish the baseline. RGB565 raw unit/object
reproduce the prior tested candidate; all 1,027 current object hashes are frozen.

## Fixed real enumeration and official scoring

The unchanged generator loops, applied to one fixed center, yield 276 swaps
plus 529 distinct moves minus 23 shared adjacent swaps: **782 neighbors** plus
baseline. All **783 orders** receive real Ninja/MWCC compilation. Duplicate
source orders alone are removed before execution, in first-seen order. No
object/score deduplication, structural filtering, suppressed compilation or
adaptive center. Setup and selected-source builds are separate validation
operations, not extra searched orders.

Every call emits an MWCC object-build line, changes object mtime and preserves
exact source bytes across compilation. Immutable source/object/order/hash,
argv/timestamp and stdout/stderr records exist for each call. There are **323
whole-object hashes**, zero failed/no-work calls and zero unstable sources.

Scoring copies the actual objdiff configuration with settings, metadata,
mappings and scratch settings preserved; only unique snapshot names and frozen
original/candidate paths differ. A private one-unit baseline reproduces full
baseline raw functions, sections and measures exactly. Every frozen object
receives official objdiff scoring without `--deduplicate`. Artificial batch
aggregate measures are not selection objectives.

All snapshots preserve all 12 sibling bodies/scores, seven raw exact functions,
function sets, code/data/completion measures and empty allocated non-code.
There are zero non-fuzzy admission failures:

- **215** baseline ties, including baseline
- **1** strict improvement
- **567** unit-fuzzy losses, rejected
- **216** admissible orders

The sole strict improvement is snapshot **0116**, **95.42553%**. The initial
center has complete **782/782** immediate-neighbor coverage. Only **5/782**
neighbors of the winner were observed in this pass, with **777 unobserved here**.
No winner fixed point, broader optimum, exhaustive 24! result, exact match or
linking gain is claimed. No continuation or plateau exploration follows.

## Fresh retained-source gates

- Function fuzzy: **95.35461% -> 95.42553%**
- Unit fuzzy: **96.90556% -> 96.91203%**
- Global fuzzy on this frozen base: **99.73153% -> 99.731544%**
- Function **564/564 bytes, 141/141 instructions**, unchanged
- Structural/positional comparator: **(6,81) -> (6,80)**
- Exact functions/code **7/13, 2648/6184 bytes**, unchanged
- All 12 sibling bodies/scores and seven raw exact functions preserved
- Empty allocated non-code sections and string pool identical
- Literal audit: 12 functions, no candidates/errors; unchanged setter skipped
  because source/target sizes differ
- Fresh final whole object equals immutable snapshot 0116 byte-for-byte
- Fresh full report reproduces 0116's raw function/section/unit records exactly
- All **1,027** unit/function reports and object hashes checked: only the owned
  RGB565 target/unit changes; no exact/code/data/link regression
- Actual objdiff configuration remains byte-identical
- Default build/progress, explicit 43U `ok`, source-scope and diff checks pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Final whole source:
`20c9842ef4db199729007ee1c647ae1fedf70a476431dabafca1ed14121ba6ea`.
Final function source:
`74d741c7226759502126269d38ae060e53a35d7a15fd116fefe21436fd214c7d`.
Final whole object:
`ec16b52bfcd4b132b90d9d879ebc73ee652d4337202f371609c9a18c12120c89`.
Final 564-byte function:
`b47101cde752a0b7a5b64d59d74d68addf6126d0144995eb63c5149d0fb17e62`.

## Sequential pixels and contained aliases

The independent geometric scalar model derives chroma rows from starting-row
parity, caches each pair's chroma, and reads each luminance byte from evolving
memory before the RGB565 store. It preserves alias observation order.
Against actual candidate, original and saved baseline objects it passes
**15,260 vectors / 45,780 executions**: 1,792 supported-scale geometry/pattern
cases; 6,400 saturation cases covering all luminance bytes and chroma pairs in
{-128,-1,0,1,127}; and 7,068 halfword-aligned contained aliases.

Every alias input read/output halfword stays in the actual 0x184-byte conversion
buffer; descriptor/state stay separate. Every non-stack byte, including guards,
agrees. Each actual object covers **141/141 instructions**, preserving GPR14-GPR31,
stack pointer and LR. Rows forcing chroma reads beyond the allocation are
excluded. Extra residues/aliases are machine diagnostics, not expanded API
promises. Arithmetic is bounded integer-only; these are interpreter checks,
not formal equivalence or Wii hardware tests.

The unchanged repository JPEG suite passes **9,456 paired cases** across 28
functions with preserved nonvolatile registers, stack pointer and LR.

## Evidence

The committed CSV records all 783 exact order tuples, source/object hashes,
official scores, compilation/source flags, gate decisions and both historical
manifest indices. CSV SHA256:
`3fc25d5585183134662dd063b32e1d7f1f3f5503c418ad94f980da9a1f4ce654`.

The workspace evidence directory above retains every immutable source/object/
compiler snapshot, calls/enumeration/manifest/selection/context/overlap JSON,
actual config, original/baseline, raw official reports, all-unit hashes,
compiler/tool evidence, storage checks, build/pool/literal/ctx results,
model/suite results and every script. A compact local archive is also retained.
Original executable bytes stay local. No remote writes or merge occurred.
