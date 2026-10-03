# Normal RGB565422 official-fuzzy snapshot audit

Base: `a4a4374cd234caeb538bda62633c2cb9a88bf00f`, 43U only.
Leaf: `wii-jpeg-rgb422-fuzzy-neighbors`.
Branch: `agent/bittle/jpeg-rgb422-fuzzy-neighbors`.

## Result and scope

One authorized fixed-center pass around
`TMCJPEGDEC_converterYUV422toRGB565` at **96.69118%** finds **96.76471%**.
The unique highest admissible result is snapshot **0066**, swapping only the
existing `s32 lumaSkip;` and `u16* output;` declarations at lines **327/330**.
The structural/positional comparator worsens **(0,58) -> (0,59)**. Selection
uses official fuzzy scoring, so the earlier proxy fixed point did not establish
closure for this objective.

Only the **23 uninitialized declarations at lines 324-346** in
`Texture_MCUtoRGB565.c` may reorder. Every other source byte, declaration type,
scope, initializer, statement, expression, assignment and sibling is frozen.
There are no initialized declarations or address-taken locals in this function.
Its 12 setup assignments, two row assignments, column initialization and eight
pair-local assignments precede all uses. Pointer address expressions refer to
`work->convBuf`, not to any reordered automatic variable. No new local,
artificial guard/padding, assembly, volatile cast, compiler/header/linking
change, adaptive center, restart or body/lifetime rewrite occurs.
Closed normal RGB565411, normal RGB565420 and RGB565420-edge remain untouched.
No continuation follows this finite pass.

Fixed baseline names, in zero-based CSV index order:

```
chromaSkip, width, blue, lumaSkip, red, tileRow, output, tileWidth,
texture, state, crValue, luminance, cb, cr, height, column, cbValue,
xEnd, yEnd, redOffset, greenOffset, blueOffset, green
```

## Historical repetition and missing evidence

The surviving Oct 3 08:09 checkpoint identifies the former directory
`/tmp/jpeg-rgb422-declarations`: a 1,200-cap invocation of the official
`declsearch.py` tool stopped after **716 evaluations**, with no improving step,
at structural/positional score **(0,58)**. It restored source/object/report and
passed its gates. The checkpoint was supplied by the parent during this review;
no exact log filename, historical source hash or transcript survives. Its
artifacts were lost in the 10:12 workspace reset.

Here “official declaration search” meant the repository's search tool, whose
objective is structural/positional, not official objdiff fuzzy scores for every
snapshot. The committed `allhands-jpeg-rgb420-declarations.attempts.md:4` calls
RGB565422 closed but supplies no per-order official-fuzzy evidence. Later
normal420 logs explicitly leave RGB565422 official classification unverified.

The current target function and declaration block exactly match `6ec48a1b`,
`be7ded2f`, `f3f295c6`, `17e497e0`, `36f0d43f` and this base. Every one of the
13 retained source-changing ancestry commits after `6ec48a1b` preserves this
function. Whole translation-unit context has changed in other functions.

**Treat all 716 current orders as repeated historical proxy compilations for
missing official scoring, not as new permutations.** The unchanged center and
23-local generator mathematically describe the same neighborhood, but missing
historical per-order sources/objects prevent independent snapshot-level overlap
or whole-translation-unit hash reconstruction. No exact prior-call mapping or
novelty claim is made. `jpeg-round4-attempts.md:1393-1406` additionally records
800 earlier permutations including plateaus and eleven retained steps; their
exact overlap is unknown. Isolated old body/type trials are not evidence of
complete official declaration-neighborhood coverage.

## Frozen context

Baseline whole source:
`20c9842ef4db199729007ee1c647ae1fedf70a476431dabafca1ed14121ba6ea`.
Baseline function source, definition through closing brace and LF:
`59e8e142e27bc066f3346ee6aad6c4387722dac9d17070b62571d3c42040e2c7`.
Declaration block:
`2fb1b9c483b9ca17aa2a750a37d5a67e1c642edd31d8b02cd6c222c9f4e90105`.
Whole source excluding the block:
`65a7d63eb4b178cfef83a9fb81276059adbb4801b76fade89ac6b97f79497d2a`.
Frozen body after the block, lines 347-398:
`30281da8f11a4373e29dc3c39d8975d04c3e996cfefb65726cb162acab06853b`.
Baseline whole object:
`ec16b52bfcd4b132b90d9d879ebc73ee652d4337202f371609c9a18c12120c89`.
Baseline 544-byte function:
`ffd0217fe4c9b137b0d44922d152d2ab2b761128870a6c2984a2090766b26096`.
Frozen original whole object:
`51fd09b6b6b2b7e07363f9286537e12ce2ef14e3e0f344ad142d29af66ed661e`.
Actual copied objdiff configuration:
`5a767a65a3c1ecc0b5a5a06679131566ff04cfe0871b20ab101d4dc90ac199ea`.
Unmodified official declaration tool:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

## Bounded setup and real enumeration

The fresh leaf starts at current main. It receives only the mutable 43U cache
from the preserved validated a4 leaf; shared immutable tool/compiler/binutils
directories are reused via symlinks. No main worktree source/cache is changed
or copied. Fresh default build, explicit `ok`, official full report and pool
check reproduce all 1,027 validated baseline objects and report exactly.

Approved cached configure paths, `../toolchain/wibo-release64/wibo` and
`WIBO_SJIS_MISSING_IMPORTS=1` are explicit. Actual compiler command and tool
hashes are saved and reverified unchanged. Commands use explicit leaf workdir.
Evidence and `TMPDIR` are workspace-local:

- `/workspace/scratch/0128b1ed02cc/jpeg-rgb422-fuzzy-evidence`
- `/workspace/scratch/0128b1ed02cc/jpeg-rgb422-fuzzy-temp`

No prior evidence is deleted or full tool cache duplicated. Free space is
checked every 100 audit calls with a 1GiB stop floor. Evidence is about 47MB,
TMPDIR 4KB; post-model workspace free space is 4,536,643,584 bytes. `/tmp` still
has about 198MB free; it is not used for this audit's evidence or temporary files.

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
716 calls. There are **335 distinct whole objects**, zero failed/no-work calls
and zero unstable sources.

## Official scoring and admission

Scoring copies the actual objdiff configuration, preserving all settings,
metadata, mappings and scratch options. Only unique snapshot names and frozen
original/candidate paths differ. A private one-unit baseline reproduces the
real full baseline's raw function, section and measure records exactly.
Every frozen snapshot receives official scoring without `--deduplicate`;
the artificial batch aggregate is never used for selection.

All snapshots preserve all 12 sibling bodies/scores, seven raw exact functions,
function sets, code/data/completion metrics and empty allocated non-code.
There are zero non-fuzzy admission failures:

- **178** baseline ties, including baseline
- **2** strict official improvements
- **536** unit-fuzzy losses, rejected
- **180** admissible orders

Snapshot **0066** uniquely maximizes target fuzzy at **96.76471%**. The other
improvement, snapshot **0145**, reaches **96.72794%** and is not retained.
All **715/715** neighbors of the initial center are officially covered. Only
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
every snapshot. The complete baseline headers/vectors and per-call outcomes
are preserved, in addition to independent sibling-code/data checks.

## Retained-source gates

- Function fuzzy: **96.69118% -> 96.76471%**
- Unit fuzzy: **96.91203% -> 96.9185%**
- Global fuzzy on this frozen base: **99.731544% -> 99.73157%**
- Function **544/544 bytes, 136/136 instructions**, unchanged
- Structural/positional comparator: **(0,58) -> (0,59)**, deliberately not the
  selection objective
- Exact functions/code unchanged: **7/13, 2648/6184 bytes**
- All 12 sibling bodies/scores and seven raw exact functions unchanged
- Empty allocated non-code and string pool identical
- Literal audit: 12 analyzed, no candidates/errors; unchanged setter skipped
  for unequal source/target sizes
- Fresh final whole object equals immutable snapshot 0066 byte-for-byte
- Full report reproduces 0066's raw function/section/unit records exactly
- All **1,027** report/function/object records checked: only the owned RGB565
  target/unit changes, with no exact/code/data/link regression
- Generated `build/43U/report.json` equals the final full official report
- Actual objdiff configuration remains byte-identical
- Default 43U/progress, explicit `ok`, source-scope and diff checks pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Final whole source:
`43f8cefddb56ef5c1515ffba853fe6038be9c6b651ed241da30b9533ce2001ed`.
Final function source:
`c65f24311a6890e447d037a331bf57a11474714703f3296468aaf17e7263e0ce`.
Final whole object:
`b8d1bdc306c9c60b9786f96913716812ae9721bb95753969821df5fa7f3d3a7c`.
Final 544-byte function:
`2a9d176b06f63a32b87050a67b1f4d82f550397f51fd95ce5ae9c7bc1e180959`.

## Sequential pixel and contained-alias model

The independent geometric scalar oracle uses each relative output row's
chroma row, caches each two-pixel pair's Cb/Cr, and reads every luma byte from
evolving memory before its RGB565 store. Thus alias effects are observed in
program order rather than comparing against an immutable input image.

Actual candidate, original and baseline objects pass **18,283 vectors / 54,849
object executions**: 2,016 geometry/pattern cases, 6,400 saturation cases
covering every luma byte crossed with Cb/Cr in {-128,-1,0,1,127}, and **9,867
halfword-aligned contained aliases**. Scales 1,2,4,8, even column positions,
row/tile residues and minimum/wide pitches are exercised.

Inputs stay in the normal422 luma/chroma regions; every alias store stays in
actual `convBuf[0x184]` (confirmed in `tmc_jpeg_internal.h:166`). Descriptor
and state are separate. All non-stack bytes, including guards, agree. Each
object covers all **136/136 instructions**, preserving GPR14-GPR31, SP and LR.
Arithmetic is bounded integer-only. Extra residues and aliases are machine
checks, not expanded API guarantees, formal proof or Wii hardware testing.

The unchanged repository JPEG suite passes **9,456 paired cases** across 28
functions with nonvolatile registers, SP and LR preserved.

## Evidence and stop

The CSV records all 716 order tuples, source/object hashes, official scores,
compilation/source flags, admission decisions, explicit whole-object checks
and historical-repeat/overlap limitations. CSV SHA256:
`254fd2da564a4eaa7750860890d6c9323389144b94d1aa20947a6a4a589265dd`.

The workspace evidence directory contains every immutable source/object/compiler
snapshot, raw reports, actual config, baseline/original, all-object hashes,
context/coverage/manifest/selection JSON, tool and compiler evidence, build/
pool/literal/ctx results, model/suite output and scripts. A compact local
archive is retained. Original executable bytes remain local. No remote write,
merge or further search occurs.

GATE: PASS — strict official-fuzzy gain; all source/sibling/whole-object/report,
pixel/alias, repository suite, default 43U and DOL checks pass.
