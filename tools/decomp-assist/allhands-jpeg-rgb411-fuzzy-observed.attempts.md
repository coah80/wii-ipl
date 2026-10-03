# RGB565411 repeated search with official fuzzy observation

Base: `180e620c`; branch: `agent/bittle/jpeg-rgb411-fuzzy-observed`; 43U only.
This is one explicitly authorized repeat of the previous 1,000-evaluation
RGB565411 search. It newly observes official fuzzy scores for every compiled
snapshot; it does not claim newly explored declaration-order coverage.
All prior branches and evidence remain preserved.

## Historical overlap and pinned context

The earlier `/tmp/jpeg-rgb411-declarations/` run preserved only baseline and
rejected final source/object pairs. No intermediate snapshot or per-order
manifest existed. It ended at its cap with internal trajectory
`(21,144) -> (21,142) -> (17,138)`. Its final official fuzzy fell from
90.599075 to 90.18433, so it was restored. Intermediate fuzzy was unknown.
The AES exhaustive-order evidence subsequently demonstrated that the tool's
structural-first objective can discard a higher official-fuzzy candidate.

The current RGB565411 function is byte-for-byte identical in source to the
prior baseline; its freshly rebuilt 868-byte function also equals the saved
baseline machine code. Other RGB565 converters changed in the meantime, so
the current complete translation unit was used throughout.

- Function source SHA256, definition through closing brace plus newline:
  `54d0ab05ff25601050e671e30f3e174a176a345983d8bbfa4b45c8d243008040`
- Baseline compiled function SHA256:
  `09825a00e8ab1d9d8ecef92d56b1cd9cdcd399fa059f88fbcc72672282c0bdb1`
- Fresh official baseline: 90.599075, 217/217 instructions
- Eligible block: exactly 24 existing uninitialized declarations at lines
  169–192 in `Texture_MCUtoRGB565.c`, including unchanged `u8 value;`
- Search tool SHA256:
  `9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`

The baseline retains the post-search u8 luminance context described by
`jpeg-round4-attempts.md:1545-1551`. That old 400-swap history is not presented
as new work either. Configuration/compiler/header inputs relevant to this
unit did not change between the prior run and this baseline.

## Unmodified search, ordinary compilation, complete recording

Exactly one official invocation ran, with no restart or continuation:

```sh
WIBO_SJIS_MISSING_IMPORTS=1 \
NINJA=/tmp/jpeg-rgb411-fuzzy-observed/ninja-record.py \
PYTHONPATH=../local-tools ../.venv/bin/python -u \
  tools/decomp-assist/declsearch.py \
  libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 \
  TMCJPEGDEC_converterYUV411toRGB565 --lines 169 192 --max-evals 1000
```

The recorder always invoked the real Ninja with the unchanged arguments and
inherited environment. It captured compiler stdout/stderr and saved each exact
source, declaration order and successful compiled object with SHA256 hashes.
It compared source bytes before/after every invocation. No compilation was
suppressed, no cached score replaced compilation, and the official search
script was unchanged.

The manifest distinguishes 1,000 evaluation calls and one final-restoration
call. All 1,001 calls succeeded with explicit MWCC object-build messages,
changed object mtimes and stable source. Failed calls: zero. No-work calls:
zero. There are 1,000 distinct orders within this invocation and 441 distinct
whole objects; equal objects were still independently compiled and recorded.
The separate baseline full build and final selection rebuild are outside
these recorder-call counts.

The tool again reported `(21,144) -> (21,142) -> (17,138)` and stopped at the
1,000 cap, not a local fixed point. Its final function exactly matches the old
rejected function, SHA256
`a92d979a5900543193e4600e55417306ba5e29d49652fc8db661719d0e08bf09`.
The historical per-order sequence was not recorded, so no exact cross-run
unique-order count is claimed. This remains deliberate repeated coverage.

## Official scoring and selection

A private copy of the current `objdiff.json` retained its diff settings,
metadata, scratch settings and mappings. Only its unit list was reduced to
RGB565 snapshots, with unique unit names, a frozen original target_path and
each recorded object as base_path. The official report command was used with
no `--deduplicate`. A one-unit baseline snapshot report first reproduced the
ordinary full-project baseline functions, sections and unit measures exactly.

All 1,001 saved objects then received official per-snapshot reports. Artificial
batch aggregates were never used for selection. Every snapshot passed source
preservation, all twelve sibling-body, all seven exact-function and allocated
non-code gates. The only admission failures were 632 unit-fuzzy regressions.
Of the 1,000 evaluations, 368 were admissible and 317 strictly improved the
baseline's official function fuzzy.

The maximum admissible official fuzzy is 90.89862, attained by zero-based calls
442 and 869. Their whole objects are byte-identical. The first, snapshot 0442,
is retained. The relevant objective comparison is:

| Source | Official function fuzzy | Internal structural/positional |
|---|---:|---:|
| Baseline | 90.599075 | (21,144) |
| Retained snapshot 0442 | 90.89862 | (21,142) |
| Tool-final source | 90.18433 | (17,138) |

The retained source swaps only the existing cb/chromaSkip and
greenOffset/blueOffset declaration positions. Every type, initializer,
expression, assignment order, scope, helper and pointer step is unchanged.
The highest official-fuzzy snapshot is distinct from the tool-selected final
order. No fixed point or exhaustive 24! result is claimed for fuzzy selection.

## Fresh final gates

After restoring snapshot 0442, ordinary compilation reproduced its complete
object byte-for-byte. A fresh full-project official report reproduced its raw
function, section and unit results exactly.

- Function fuzzy: 90.599075 -> 90.89862; 217/217 instructions
- ctxdiff: 144 -> 142 differences
- Unit fuzzy: 96.805305 -> 96.84735
- Exact remains 7/13; matched code remains 2648/6184 bytes
- All twelve sibling bodies unchanged, including previously accepted RGB565
  declaration gains; all seven exact siblings remain raw-byte exact/ctxdiff 0
- All allocated non-code bytes/sections unchanged and empty; pool identical
- Literal audit: twelve functions, no candidates/errors; unchanged setter
  skipped for unequal instruction counts
- All 1,027 units and all function scores checked: only RGB565 changes,
  no exact/code/data/linking or per-function fuzzy regression
- Global fuzzy on this base: 99.72766 -> 99.727745
- Fresh default progress builds and `build/43U/ok` pass before and after
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes; no header/configuration/linking edits

This is partial fuzzy progress, not an exact-matching or linking claim.

## Differential and pixel/alias checks

The unchanged repository interpreter passes all 9,456 paired calls. A separate
scalar RGB565411 oracle passes 7,469 vectors against candidate, original and
saved baseline objects, totaling 22,407 object executions:

- 384 supported-scale/MCU-origin constant and random input cases
- 64 additional tiled-row and column-residue machine-level cases
- 6,400 saturation cases: all luminance bytes crossed with signed Cb/Cr from
  {-128,-1,0,1,127}
- 621 aligned input/output overlap cases, with every output write inside the
  actual 0x184-byte conversion buffer and descriptor/state separate

Every non-stack byte, including guards, matches the independently sequenced
scalar model. SP, LR and GPR14–GPR31 restoration pass. All 217 instructions in
candidate/original/baseline were exercised. Arithmetic remains integer-only,
with unchanged read/write order and bounded color intermediates. Additional
residue and overlap cases are machine-level checks, not new public API
promises. These bounded tests are not formal equivalence or Wii runtime tests;
the existing integer interpreter's device/exception limitations apply.

## Frozen artifacts

Final function source SHA256:
`fd2f57871997ac10f8f9145d7cc5209886d0379b1ef6eacf75d21ae116e9ba50`.
Final entire source SHA256:
`a4fd0e061305f01791e636687f582ef55b5e1fc651e601b570380f67219f1642`.
Final whole object SHA256:
`fec999a214f95c1f348632de53cac7672c15d70cbaea9b3566d7a7383a4e1b70`.

`/tmp/jpeg-rgb411-fuzzy-observed/` preserves the recorder, calls.jsonl,
manifest.json, all 1,001 source/object/compiler-output snapshot sets, copied
objdiff configuration, frozen original, all-snapshot-reports.json, baseline
and final full reports/build logs, score_snapshots.py, verify.py/results,
ctxdiff/pool/literal evidence, differential.log, and pixel audit.py/results.
The per-order official scores and admission reasons are in manifest.json;
raw reports remain in all-snapshot-reports.json. Original executable bytes
and snapshots remain local. No remote write was performed.
