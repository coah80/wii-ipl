# RGB565411 normal fixed-neighborhood declaration audit

Base: `e7ade28ae79f837ed91d76cdd10ee797b04a7193` (merged #1102), 43U only.
Leaf: `wii-jpeg-rgb411-fixed-neighbors`.
Branch: `agent/bittle/jpeg-rgb411-fixed-neighbors`.

## Scope and historical limits

One authorized fixed-center audit of normal
`TMCJPEGDEC_converterYUV411toRGB565` in `Texture_MCUtoRGB565.c`.
Exactly the 24 existing uninitialized declarations at lines 169-192 are
eligible. Every other source byte, type, initializer, scope, assignment,
expression, sibling function, compiler setting, header and linking flag is
preserved. No adaptive center change, restart, structural-score filter,
compiler suppression, new local, guard, padding, volatile cast or assembly.

The fixed baseline order, used by the zero-based index tuples in the companion
CSV, is:

```
output, lumaSkip, cbValue, blue, state, tileWidth, crValue, width,
height, chromaSkip, texture, luminance, cb, cr, column, xEnd,
yEnd, redOffset, tileRow, greenOffset, value, red, blueOffset, green
```

Historical round4 lines 501-512 record 400 declaration swaps before the later
`u8 value` change at lines 1545-1551. The committed
`allhands-jpeg-rgb411-fuzzy-observed.attempts.md` records two capped
1,000-evaluation structural searches on the later body, the second with
per-snapshot official fuzzy observation. Snapshot 0442 was retained at
90.89862%, `(21,142)`, rather than the tool-final 90.18433%, `(17,138)`.
It explicitly did not establish a fixed point around the retained source.

The current function source is byte-identical to PR #1089's retained source.
PR #1090 changed only the edge sibling's three offset declarations; its log
confirms the normal body and score unchanged. The complete current source
matches that later context. The old `/tmp` snapshots are absent after workspace
reset. Exact historical overlap is unknown, and this audit makes no claim that
its orders have never been compiled before. No closed RGB422, RGB420, or edge
group was searched again.

## Pinned inputs and setup

Baseline source SHA256:
`8fb0c89b7b0bcb7b0467ca1be3dfcdb70dfa43b1ec085d926d028e156470749a`.
Baseline function, definition through closing brace and one LF:
`fd2f57871997ac10f8f9145d7cc5209886d0379b1ef6eacf75d21ae116e9ba50`.
Eligible block, preserving whitespace and LF:
`e5fdb7ee9aa5737e6290a751eea74db9dbdf8c22135391cebebb2b60ef55b9a9`.
Whole source excluding that block:
`f2d7fddcc33d949cc1ca7ae550e1faa6441a0db2dc6055fd7d8aa34875af6d07`.
Baseline whole object:
`f82e514864af9c85e1857e2fd59bfd976deb0aba1f651662b322730ced490ad6`.
Frozen original whole object:
`51fd09b6b6b2b7e07363f9286537e12ce2ef14e3e0f344ad142d29af66ed661e`.
Actual copied objdiff configuration:
`5a767a65a3c1ecc0b5a5a06679131566ff04cfe0871b20ab101d4dc90ac199ea`.
Unmodified official declaration-search tool:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.

The leaf uses explicit cached dtk, objdiff, sjiswrap, bstool, compilers and
binutils paths, `../toolchain/wibo-release64/wibo`, and
`WIBO_SJIS_MISSING_IMPORTS=1`. The exact compiler command and tool hashes are
saved. A fresh ordinary default build, explicit 43U `ok`, full official report,
and empty-pool comparison established the baseline before enumeration.

Setup-only corrections, outside the experiment: the combined leaf-creation
command accidentally reran configure in main with the same approved cached
arguments; the parent was immediately informed and owns main verification.
No main compile or tracked/source edit occurred. The first leaf default build
stopped in splitting because the original app had not been copied; after
copying the authorized 43U input, the full build passed. An initial pool command
used a unit path instead of object paths; the corrected baseline pool check
passed before enumeration. No audit evaluation failed or was repeated.

## Fixed enumeration and complete official scoring

The unchanged tool's two generator loops, applied once to the frozen baseline,
yield 276 unique swaps and 529 unique moves, sharing 23 adjacent swaps:
**782 distinct neighbors**, plus baseline, **783 evaluated orders**. Duplicate
source orders are removed in first-seen order, before compilation. No object
or score deduplication occurs.

All **783 audit calls** invoked real Ninja/MWCC, emitted the object-build
message, changed object mtime and preserved the exact source bytes across the
compile. There were zero failed calls, no-work calls or unstable sources.
The immutable recorder saves argv, timestamps, stdout/stderr, exact source and
object bytes, source order and hashes for every call. There are **336 distinct
whole objects**. Initial baseline and final selected-source build operations
are separate validation, not extra searched orders.

The scorer copies the actual objdiff configuration, preserving all settings,
metadata, mappings and scratch settings. Only unit names and frozen target/base
paths change. A private one-unit baseline exactly reproduces the full baseline's
raw functions, sections and measures. Every snapshot then receives an official
report without `--deduplicate`. Artificial batch aggregates are not selection
objectives; the raw per-function and per-unit results are retained.

All 783 snapshots preserve the 12 sibling bodies and scores, all 7 exact
functions, function set, code/data/completion measures and empty allocated
non-code sections. There are zero non-fuzzy gate failures:

- 239 baseline ties, including baseline
- 15 strict improvements
- 529 unit-fuzzy regressions, rejected
- 254 admissible orders

The maximum admissible score is **91.013824%**, reached by calls
**40, 258, 259, 651, 652, 653**, producing three distinct whole objects.
The deterministic first best, **0040**, is retained. It swaps only the
`lumaSkip` and `tileRow` declarations, originally at lines 170 and 187.
No assignment or use moves; both scalars are assigned before use.

The original center's neighborhood is fully covered, **782/782**. Only
**5/782** immediate neighbors of the selected winner are present in this run;
**777 remain unobserved here**. No winner fixed point, exhaustive 24! result,
global optimum, exact match or linking improvement is claimed. The audit ends
at the fixed enumeration; no continuation followed.

## Fresh retained-source verification

- Function fuzzy: **90.89862% -> 91.013824%**
- Unit fuzzy: **96.850586% -> 96.86675%**
- Global fuzzy on this base: **99.73127% -> 99.73129%**
- Function size and instructions: **868/868 bytes, 217/217 instructions**
- Internal structural/positional score: **(21,142) -> (21,142)**
- Exact functions: **7/13**, exact code **2648/6184 bytes**, unchanged
- All 12 sibling raw bodies and official scores unchanged
- All allocated non-code sections are empty and identical; pool identical
- Literal audit: 12 analyzed functions, zero candidates/errors; unchanged
  setter skipped because its function sizes differ
- Fresh final whole object exactly equals immutable snapshot 0040
- Fresh final full report exactly reproduces that snapshot's functions,
  sections and unit measures
- All **1,027** units, object hashes and function scores checked; only the
  intended RGB565 target/unit changes, with no code/data/link/exact regression
- Actual objdiff configuration remains byte-identical
- Ordinary default build/progress and explicit `build/43U/ok` pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- Source preservation and `git diff --check` pass

Final source SHA256:
`5807c83409afebc021a1311143f045eb5a147ce8a60ea7dd3b1d7bed1ec6314d`.
Final function source SHA256:
`af2899de091862526a9012f8b780cc2e01699a012f7b057b56320eee701446d4`.
Final whole object SHA256:
`7f4ca0cfa4bfccfd13f7b0dc476830a8e4531a0e299930ce2ded76ed68b20c94`.
Final 868-byte function SHA256:
`9873eba0c00c8fc8800932d136ce2ef7147194fd9ed84932179295e0f7fdd5f1`.

## Sequential pixel and alias checks

The unchanged repository JPEG differential suite passes **9,456 paired cases**
across 28 functions with GPR14-GPR31, stack pointer and LR preservation.

A separate scalar RGB565411 model checks **13,366 vectors** against actual
candidate, original and saved baseline objects, **40,098 object executions**:

- 2,016 geometry/pattern vectors across all supported scales 1/2/4/8, aligned
  x origins, row residues, tile crossings, minimum/wide pitches, random and
  constant samples
- 6,400 saturation vectors: every luminance byte crossed with signed Cb/Cr in
  {-128,-1,0,1,127}
- 4,950 aligned input/output overlap vectors; every halfword output is within
  the actual 0x184-byte conversion-buffer allocation, with state/descriptor
  objects separate

The model reads cached chroma for each group and each luminance byte from the
current evolving memory before writing that pixel's packed RGB565 result.
Thus overlap checks preserve read/write observation order, rather than using
an immutable input copy. Every non-stack byte, including guards, matches.
All three objects exercise **217/217 instructions**, preserving nonvolatile
registers, stack pointer and LR. Arithmetic is bounded integer-only; no FPU
reassociation is involved. Extra residue and alias arrangements are machine
checks, not new public API promises. These are bounded interpreter tests, not
formal equivalence or a Wii hardware run.

## Evidence

The committed companion CSV records all 783 exact order tuples, source/object
hashes, official target/unit scores, compile/source flags and admission results.
Its SHA256 is
`784b82f2c8ab4a92470e5925fb4c14fb3f2fb0abe72a8c12255883a256a0df5c`.

`/tmp/jpeg-rgb411-fixed-neighbors/` retains the recorder, fixed enumerator,
scorer, verifier, scalar audit, all immutable source/object/compiler-output
snapshots, calls.jsonl, enumeration.json, manifest.json, selection.json,
actual config, frozen baseline/original, raw snapshot reports, full reports,
all-unit object hashes, tool hashes/command, build/pool/literal/ctx evidence,
pixel results and repository suite log. A local workspace archive preserves
this complete evidence independently of `/tmp`. Original executable bytes
remain local. No remote action or merge was performed.
