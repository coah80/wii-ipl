# ATERM case-8 checksum initialization

## Single authorized trial

Baseline: `d901e5cf88abb6d62bd1a094926a7ecb25b29201`, Wii Menu 4.3U only.
Move only case 8's `u32 checksum = 0;` immediately after its packet declaration,
before the existing two SONtoHs initializers. Accepted case 6 and all other
source/configuration bytes remain fixed. Exactly one source candidate compiled;
there were no alternative variants or follow-on declaration trials.

SHA256 identifiers:

- Baseline source: `537e102586da8d21d987a8cc4bb9529a99b4af2af41516a6da4683544ab74a71`
- Candidate source: `2f16bf9c6db775c75e9a27919c5fc33f1baee949add35fe270aeab3b7c05cfb3`
- Baseline source object: `82a6ba2109f8ba7ac4a9077844527a51bff594b224584e537baba71b541e3372`
- Candidate source object: `80abe1dde72788e19c6aa5a17af690beec486fb564f67d138aea844a65c5d8ac`
- Original object: `14f7910c05e64937ebdf810cee905eab0b77b58d684570311b97fedf40bc7522`

## Independent target and historical evidence

Case 8's original `.text+0x2244` sets r16 to zero before the SONtoHs calls at
`+0x2248/+0x2258`. Its later checksum additions at `+0x22A8..+0x2300` and
checksum narrowing at `+0x2314` establish this value's role independently of
case 6. The baseline sets the checksum after those two calls. This is evidence
for a scheduling hypothesis, not proof of a unique original source order.

Read-only history review covered all 76 available ATERM-changing revisions and
relevant ATERM/fz20/ult15 attempt logs. The recorded case-8 forms initialize the
checksum after conversions, including the older manual-loop reconstruction.
Earlier checksum/type/lifetime trials did not cover this initialized declaration
boundary. The immediately preceding accepted case-6 trial explicitly preserved
case 8's source and object instructions.

## Safety and actual object audit

Both original and compiled SONtoHs bytes are pinned in the runnable audit to
`5463043e4e800020`: `clrlwi r3,r3,0x10; blr`. This function touches no memory or
callbacks. The moved expression is constant zero assigned to a private scalar;
its address never escapes. No packet/global read or call changes order relative
to another packet/global read or call.

The candidate keeps 958 instructions. Exactly 26 instructions change, confined
to indices 724..804. Header 724..732 moves the private zero initialization. Every
instruction at 733..804 is exactly the baseline under an r16/r17 permutation:
checksum moves from r17 to r16, and payload length from r16 to r17. This includes
the final payload-length comparison and the gAtermReplyLength store at 804; that
store still publishes the same length. Calls consume unchanged r3..r7 arguments
and the ABI preserves the renamed callee-saved values. All instructions outside
that region, including accepted case 6, are unchanged.

The audit checks 64 sampled header inputs (two packet bases, four sequence
values, eight lengths), identical packet-read/call/private-sequence-store
observations, and equal value roles after the register permutation. These
samples complement the exact instruction-renaming check; they are not a general
symbolic proof or runtime protocol tests. The observed event sequence is:
read sequence halfword, convert sequence, read length halfword, store the private
sequence word at stack+0x120, convert length. Both checksums are zero at loop
entry, and converted lengths agree.

A caller def-use traversal starts after the region at instruction 805 and follows
direct branches and decoded switch-table entries, treating r16/r17 as surviving
ordinary calls. It rejects reads before fresh definitions. It passed 630 baseline
and 628 candidate states. The restore helper restores the saved entry registers.
The audit also checks that no branch/table entry bypasses header setup.

All 123 call identities and ordering, sibling function bytes/sizes/offsets,
allocated non-text bytes and section extents/types/alignment, and relocations
outside the moved header are unchanged. A byte-level source assertion verifies
exactly the single approved declaration move and no other source change.

## Official scoring and gates

| Measure | Baseline | Candidate |
| --- | ---: | ---: |
| RunConfigProtocol fuzzy | 89.57834% | 89.77287% |
| Compiled/original instructions | 958/951 | 958/951 |
| ATERM fuzzy | 97.31056% | 97.34909% |
| ATERM exact functions (objdiff) | 18/26 | 18/26 |
| ATERM matched code | 11036/19204 | 11036/19204 |
| ATERM matched data | 18584/18864 | 18584/18864 |
| Global fuzzy | 99.73097% | 99.731224% |

- Fresh baseline object/report matched main before the trial.
- All 1027 report units compared: only ATERM changed; zero sibling-function,
  exact/code/data/fuzzy/link regressions. No exact-function or linking gain.
- Final full-build report equals the initially scored candidate report.
- Pool identical: zero strings in both objects.
- Literal audit: 24 functions and 6 arguments checked, no candidates/errors.
  DiscoverAccessPoints and RunConfigProtocol are skipped for unequal target/source
  sizes. This is not claimed as full coverage of either unmatched function;
  no data/string bytes changed in this candidate.
- Focused object build and full default 4.3U build: pass.
- Report and build/43U/ok: pass.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- git diff --check: pass.
- ATERM remains NonMatching and unlinked. The function still has seven extra
  instructions; this result is fuzzy progress, not exact completion.

## Reproduction

Configure with `--version 43U --wrapper ../toolchain/wibo-release64/wibo
--dtk build/tools/dtk --objdiff build/tools/objdiff-cli
--sjiswrap build/tools/sjiswrap.exe --bstool build/tools/bstool
--compilers build/compilers --binutils build/binutils` using `../.venv/bin/python`.
All tools came from the cache; no downloads or remote writes occurred.

Build using `WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja`, first the explicit
`build/43U/src/src/scene/setting/ATERM.o` target, then the full default target and
`build/43U/report.json build/43U/ok`. Score with
`build/tools/objdiff-cli report generate -p . -o build/43U/report.json -f json`.
Run pool_diff.py, literal_reference_diff.py with `--all-functions`, and ctxdiff.py
for `src/scene/setting/ATERM ATERMRunConfigProtocol` using the venv Python and
`PYTHONPATH=../local-tools`.

Snapshots, logs, reports, runnable audit.py and audit-result.json are retained in
`/tmp/aterm-case8-checksum-evidence/` for parent review. This path is session-local.

GATE: PASS for the authorized strict-fuzzy-improvement trial; not an exact-match
or completion gate. Parent independent verification remains required.
