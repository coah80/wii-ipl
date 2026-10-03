# Normal RGB565422 next fixed official-fuzzy neighborhood

Base: `246c3f8056430e98f8c10e3edc3b0b717721e917` (merged #1116), 43U only.
Leaf: `wii-jpeg-rgb422-next-neighbors`.
Branch: `agent/bittle/jpeg-rgb422-next-neighbors`.

## Result and scope

One authorized fixed-center pass around
`TMCJPEGDEC_converterYUV422toRGB565` at **96.76471%** finds **97.132355%**.
The sole strict improvement and unique highest admissible result is snapshot
**0145**, swapping only the existing `u32 tileWidth;` and `s32 redOffset;`
declarations at baseline lines **331/343**. The structural/positional comparator
also improves **(0,59) -> (0,52)**; official fuzzy remains the selection objective.

Only the **23 uninitialized declarations at lines 324-346** in
`Texture_MCUtoRGB565.c` may reorder. Every other source byte, declaration type,
scope, initializer, statement, expression, assignment and sibling is frozen.
There are no initialized declarations or address-taken locals in this function.
Its 12 setup assignments, two row assignments, column initialization and eight
pair-local assignments precede all uses. Pointer address expressions refer to
`work->convBuf`, not any reordered automatic variable. Both selected locals
retain their types, function scope and assignments. No new local, artificial
guard/padding, assembly, volatile cast, compiler/header/linking change, adaptive
center, restart or body/lifetime rewrite occurs. Closed normal RGB565411,
normal RGB565420 and RGB565420-edge remain untouched. No continuation follows.

Fixed baseline names, in zero-based CSV index order:

```
chromaSkip, width, blue, output, red, tileRow, lumaSkip, tileWidth,
texture, state, crValue, luminance, cb, cr, height, column, cbValue,
xEnd, yEnd, redOffset, greenOffset, blueOffset, green
```

## Context and historical overlap

The previous fixed official-fuzzy audit retained snapshot 0066, swapping
lumaSkip/output and reaching this 96.76471% center. Its complete immutable
716-order manifest survives in `jpeg-rgb422-fuzzy-evidence`. The surrounding
RGB565 source is identical to that audit; other units changed on this new base.
Exact **current/prior** overlap pairs are:

**(0,66), (66,0), (317,318), (318,317), (378,379), (379,378)**.

All six repeated orders freshly reproduce prior exact source/object hashes and
official function/unit scores. The other **710** orders are absent from that
surviving official manifest. No claim of global novelty is made.

The older Oct 3 08:09 checkpoint describes a 1,200-cap structural search stopping
after 716 evaluations at proxy (0,58), with source/object/report restored.
Its per-order snapshots and exact source hash were lost in a workspace reset;
that was not official-fuzzy closure. The earlier 800-permutation capped search
also lacks per-order snapshots. Exact overlap of those runs with this changed
center cannot be independently reconstructed. The preceding attempts log
records the surviving checkpoint and committed-log references in full.

## Frozen context

Baseline whole source:
`43f8cefddb56ef5c1515ffba853fe6038be9c6b651ed241da30b9533ce2001ed`.
Baseline function source, definition through closing brace and LF:
`c65f24311a6890e447d037a331bf57a11474714703f3296468aaf17e7263e0ce`.
Declaration block:
`17e2219cad42dbdd3d449c327e835ec13d62e582450f50d695fd0bbef2773f9c`.
Whole source excluding the block:
`65a7d63eb4b178cfef83a9fb81276059adbb4801b76fade89ac6b97f79497d2a`.
Frozen body after the block, lines 347-398:
`30281da8f11a4373e29dc3c39d8975d04c3e996cfefb65726cb162acab06853b`.
Baseline whole object:
`b8d1bdc306c9c60b9786f96913716812ae9721bb95753969821df5fa7f3d3a7c`.
Baseline 544-byte function:
`2a9d176b06f63a32b87050a67b1f4d82f550397f51fd95ce5ae9c7bc1e180959`.
Frozen original whole object:
`51fd09b6b6b2b7e07363f9286537e12ce2ef14e3e0f344ad142d29af66ed661e`.
Actual copied objdiff configuration:
`5a767a65a3c1ecc0b5a5a06679131566ff04cfe0871b20ab101d4dc90ac199ea`.
Unmodified official declaration tool:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

## Bounded setup and real enumeration

The fresh leaf starts at current main, preserving the newly accepted keyboard
and tiZi changes. Only the mutable 43U cache is copied from the preserved prior
leaf; immutable tool/compiler/binutils directories are shared via symlinks.
No main worktree source/cache is changed or copied. A fresh default build,
explicit `ok`, official full report and pool check establish the current
baseline: **99.73176% global fuzzy and 12,412 exact functions**. The RGB565
whole object/raw unit reproduce the prior accepted result exactly. All 1,027
current object hashes and unit reports are frozen before trials.

Approved cached configure paths, `../toolchain/wibo-release64/wibo` and
`WIBO_SJIS_MISSING_IMPORTS=1` are explicit. Actual compiler command and tool
hashes are saved and reverified unchanged. Every command uses leaf workdir.
Evidence and `TMPDIR` are workspace-local:

- `/workspace/scratch/0128b1ed02cc/jpeg-rgb422-next-evidence`
- `/workspace/scratch/0128b1ed02cc/jpeg-rgb422-next-temp`

No prior evidence is deleted and no complete tool cache is duplicated. Free
space is checked every 100 audit calls with a 1GiB stop floor. Evidence is
about 47MB, TMPDIR 4KB; post-model workspace free space is 3,455,934,464 bytes.
`/tmp` has 207,208,448 bytes free and is not used for this audit's files.

The unchanged two generator loops, fixed at the initial center, yield
**253 swaps + 484 distinct moves - 22 shared adjacent swaps = 715 neighbors**,
plus baseline. All **716** receive real Ninja/MWCC compilation. Only duplicate
source orders are removed before execution, in first-seen order. No object or
score deduplication, structural filtering, suppressed compilation, adaptive
center or restart. Setup and retained-source validation builds are separate
operations, not extra searched orders.

Each call emits an MWCC object-build line, changes object mtime and preserves
its source bytes throughout compilation. Immutable source/object snapshots,
order/source/object hashes, argv/timestamps and stdout/stderr are saved for all
716 calls. There are **331 distinct whole objects**, zero failed/no-work calls
and zero unstable sources.

## Official scoring and admission

Scoring copies the actual objdiff configuration, preserving settings, metadata,
mappings and scratch options. Only unique snapshot names and frozen original/
candidate paths differ. A private one-unit baseline reproduces the actual full
baseline's raw function, section and measure records exactly. Every frozen
snapshot receives official scoring without `--deduplicate`; the artificial
batch aggregate is never used for selection.

All snapshots preserve all 12 sibling bodies/scores, seven raw exact functions,
function sets, code/data/completion metrics and empty allocated non-code.
There are zero non-fuzzy admission failures:

- **177** baseline ties, including baseline
- **1** strict official improvement
- **538** unit-fuzzy losses, rejected
- **178** admissible orders

Snapshot **0145** uniquely maximizes target fuzzy at **97.132355%**. All
**715/715** neighbors of the initial center are officially covered. Only
**5/715** neighbors of the winner were observed, leaving **710 unobserved here**.
No winner fixed point, full 23! optimum, exact match or linking gain is claimed.

## Explicit whole-object preservation

For every snapshot and the final rebuilt object, an independent ELF check
compares every raw file byte outside the sole target interval **[2020,2564)**,
all **7 section headers**, all relocation vectors (**24 entries**), target
file interval, and complete file size (**7,784 bytes**).

The permitted interval is derived from the unique function symbol and section
file offset. Only those 544 bytes are masked; padding, other text, ELF metadata,
symbol/string tables, section headers and relocation bytes remain in the raw
comparison. All 716 masked files equal the baseline exactly, SHA256:
`aa62853a494a59a3b49a0803a5ed4d4d5e7bd2ca2a7a19f46a2873cb5965e68e`.
Explicit section-header and relocation-vector equality checks also pass for
every snapshot. Complete baseline headers/vectors and per-call outcomes are
preserved, alongside independent sibling-code/data checks.

## Retained-source gates

- Function fuzzy: **96.76471% -> 97.132355%**
- Unit fuzzy: **96.9185% -> 96.95084%**
- Global fuzzy on this frozen base: **99.73176% -> 99.73183%**
- Function **544/544 bytes, 136/136 instructions**, unchanged
- Structural/positional comparator: **(0,59) -> (0,52)**
- Exact functions/code unchanged: **7/13, 2648/6184 bytes** in the unit;
  **12,412** exact functions globally
- All 12 sibling bodies/scores and seven raw exact functions unchanged
- Empty allocated non-code and string pool identical
- Literal audit: 12 analyzed, no candidates/errors; unchanged setter skipped
  for unequal source/target sizes
- Fresh final whole object equals immutable snapshot 0145 byte-for-byte
- Full report reproduces 0145's raw function/section/unit records exactly
- All **1,027** report/function/object records checked: only the owned RGB565
  target/unit changes, with no exact/code/data/link regression; keyboard and
  tiZi accepted changes remain untouched
- Generated `build/43U/report.json` equals the final full official report
- Actual objdiff configuration remains byte-identical
- Default 43U/progress, explicit `ok`, source-scope and diff checks pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Final whole source:
`dce003b060d55cc3ed3e9c4b8be80fe2294a6bd78c8593cc9f5489389c25ef8a`.
Final function source:
`921a65452ea6b7042cdcbba9b47a2a5328126fe0ed5f6fc0b304d2a8937868bc`.
Final whole object:
`3038c01994120635cac83addc6189e844b6d86ad6aa60af4c9f857fe395c6c31`.
Final 544-byte function:
`5c210158c0adf2911a6bfaf4ff4d2d8e225768e8efafd23b778b3d2ce8073f3a`.

## Sequential pixel and contained-alias model

The independent geometric scalar oracle uses each relative output row's
chroma row, caches each two-pixel pair's Cb/Cr, and reads every luma byte from
evolving memory before its RGB565 store. Alias effects are observed in program
order instead of comparing against an immutable input image.

Actual candidate, original and baseline objects pass **18,283 vectors / 54,849
object executions**: 2,016 geometry/pattern cases, 6,400 saturation cases
covering every luma byte crossed with Cb/Cr in {-128,-1,0,1,127}, and **9,867
halfword-aligned contained aliases**. Scales 1,2,4,8, even column positions,
row/tile residues and minimum/wide pitches are exercised.

Inputs stay in normal422 luma/chroma regions; every alias store stays in actual
`convBuf[0x184]`. Descriptor and state are separate. All non-stack bytes,
including guards, agree. Each object covers all **136/136 instructions**,
preserving GPR14-GPR31, SP and LR. Arithmetic is bounded integer-only. Extra
residues and aliases are machine checks, not expanded API guarantees, formal
proof or Wii hardware testing.

The unchanged repository JPEG suite passes **9,456 paired cases** across 28
functions with nonvolatile registers, SP and LR preserved.

## Evidence and stop

The CSV records all 716 order tuples, source/object hashes, official scores,
compilation/source flags, admission decisions, explicit whole-object checks,
prior official indices and older-overlap limitations. CSV SHA256:
`125e0a9b836a4c0ee919b399a75a5b9e6a04f68a2c9860d49e3580747ab2a5a7`.

The workspace evidence directory contains every immutable source/object/compiler
snapshot, raw reports, actual config, baseline/original, all-object hashes,
context/overlap/manifest/selection JSON, tool and compiler evidence, build/
pool/literal/ctx results, model/suite output and scripts. A compact local
archive is retained. Original executable bytes remain local. No remote write,
merge or further search occurs.

GATE: PASS — strict official-fuzzy gain; all source/sibling/whole-object/report,
pixel/alias, repository suite, default 43U and DOL checks pass.
