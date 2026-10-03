# Korean empty-context flow recovery, 2026-10-03

Base: 1fa33882; branch agent/bittle/korean-candidate-reconstruction.
Owned source: zkokeyp.c / Zi8GetKOcandidates only.

## Target evidence

The first context-length test at target function+0x158 sends an empty current
word directly to+0x730, the input-length/key-table scan setup. The compiled
source instead sent this case to its+0x6C8, the prefix-search result copy and
candidate cleanup. That block corresponds to target+0x6BC, which is reached
only after a nonempty context lookup attempt or word-table search.

Added an explicit empty-context guard to a label immediately before the
existing input-length check. The nonempty prefix-search paths still enter
search_table and perform the original result/candidate cleanup. The change
recovers the target control-flow edge without moving any body or introducing
storage, helper calls, or artificial register constraints. The old edge did
not necessarily change visible output for initialized empty context; this
is a target-flow correction, not a claim of a newly demonstrated user bug.

## Validation

Fresh baseline: /tmp/ezi-korean-recon-baseline.json.
Fresh final report: /tmp/ezi-korean-flow-full-report.json.
Full build: /tmp/ezi-korean-flow-full-build.log.
Detailed gates: /tmp/ezi-korean-flow-verification.txt.

Zi8GetKOcandidates: 97.96712% ->97.97459%.
Unit fuzzy: 98.65385% ->98.65769%.
Exact functions remain1/7, exact code332/5200, matched data96/180.
All1027 units were checked: the unit fuzzy gain is the only changed measure,
with no code/data/function or fuzzy regressions. No new exact function claimed.

The source object differs from its preserved baseline at exactly one .text
payload byte, the corrected branch displacement. All section sizes and all
canonical relocation tuples remain unchanged. .data40, extab56 and
extabindex84 are byte-identical to baseline. The unit's existing exact
Zi8_81483118 remains83/83 instructions and ctxdiff diffs0, with its exact
10-entry generated switch table unchanged.

Pool first: identical and empty. Main still673/669 instructions; the known
extra zero materialization, two lookup-result narrowings and return-value
move remain. All92 mapped direct main branches now preserve their target
destinations; the17 ordered helper calls agree. The filter's43 direct branches
also agree. These are advisory correspondence checks, not an exactness claim.

Full43U build passes with the approved wrapper and WIBO_SJIS_MISSING_IMPORTS=1.
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No header, metadata, linking, remote, assembly,
volatile, dummy-storage or forced-register changes.
