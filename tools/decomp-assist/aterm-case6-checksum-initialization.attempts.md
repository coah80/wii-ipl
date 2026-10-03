# ATERM case-6 checksum initialization

## Scope

- Wii Menu 4.3U only; baseline `50d1494474dbfd691ebb707c1a0e5b72d91f9708`.
- Exactly one candidate: move `u32 checksum = 0;` above the two SONtoHs
  initializers in RunConfigProtocol case 6, immediately after `packet`.
- Case 8 and every other source/configuration byte are fixed. A byte-level source
  replacement assertion verified that only the first of the two identical
  receive-block declaration sequences changed.
- No additional candidate, uninitialized declaration trial, count-word union,
  session-key type, message-length cache, or association-contract trial ran.
- Baseline source SHA256:
  `db97c32c0c68f8e4c6018908c336c2bac3ddb57a2aaf82a93b4ee900ac9f7abd`.
- Candidate source SHA256:
  `537e102586da8d21d987a8cc4bb9529a99b4af2af41516a6da4683544ab74a71`.
- Baseline source object SHA256:
  `572a2d14550fc8f4f07e7cb1011b278717be351ebddc893793f9131b114a19e8`.
- Candidate source object SHA256:
  `82a6ba2109f8ba7ac4a9077844527a51bff594b224584e537baba71b541e3372`.
- Original object SHA256:
  `14f7910c05e64937ebdf810cee905eab0b77b58d684570311b97fedf40bc7522`.

The prior-read audit covered all 72 available ATERM-changing revisions and the
ATERM/fz20/ult15 attempt logs. Recorded case-6 checksum initializations followed
the conversions; the older manual-loop form also assigned zero afterward.
fz20's 250-build declaration search was function-scope only. The current
case-local initialization ordering was not covered by that search.

## Target evidence and bounded safety audit

Original `.text+0x1D7C` initializes the checksum before SONtoHs calls at
`+0x1D80` and `+0x1D90`. Baseline checksum initialization occurs after both.
This supports a scheduling hypothesis, not a unique original source order.

Both original and compiled SONtoHs are exactly `5463043e4e800020`, or
`clrlwi r3,r3,0x10; blr`. The runnable audit asserts those actual callee bytes
before evaluation. The moved expression is the integer constant zero, assigned
to a private scalar whose address never escapes. No mutable read or call moves
relative to another mutable read or call in the source.

The candidate retains 958 instructions and changes only 25, at indices:
`414..422, 439, 441, 443, 445, 447, 449, 451, 453, 461, 466, 474, 479, 484,
487, 490, 492`. All instructions outside indices 414..492 are identical to the
baseline, including the entire case-8 code.

- Header indices 414..422 move the constant initialization across two pure calls.
- Every instruction at indices 423..492 is exactly the baseline with r15/r16
  exchanged. The checksum moves from r15 to r16, and payload length from r16
  to r15. The checksum loop, memory accesses, branch targets, call arguments,
  payload handling and final length test otherwise agree.
- A small evaluator checks 64 sampled header inputs: two packet bases, four
  sequence values and eight lengths. For each, both versions produce identical
  packet-read/call/private-stack-write observations and equivalent registers
  under that permutation. The sequence is: read sequence halfword, convert it,
  read length halfword, store the private sequence word, convert length.
- These are bounded sampled checks, not a general symbolic proof, host runtime
  protocol test, or a claim that arbitrary packet memory is valid.
- The checksum is zero and the converted length equal in their respective mapped
  registers at the loop entry. Both SONtoHs calls preserve r15/r16 as proven by
  their actual code. Other calls in the renamed region consume unchanged
  r3..r7 arguments and preserve r15/r16 under the callee-saved ABI.
- After the final length comparison, r15/r16 may differ physically. A conservative
  caller def-use traversal follows direct branches and the decoded switch-table
  entries from index 493, treating both registers as surviving ordinary calls.
  It rejects a read before a fresh definition; it passed 1085 baseline and 1078
  candidate control-flow states. The restore helper is treated as restoring the
  saved entry values. No incoming branch/table entry bypasses header setup.
- All 123 call identities and their order are unchanged. All sibling function
  bytes, sizes and offsets, all allocated non-text bytes and section
  extents/types/alignment, and all relocations outside the moved header agree.

## Official results

Fresh baseline object/report matched main before the trial. The final full-build
report is identical to the initially scored candidate report.

| Measure | Baseline | Candidate |
| --- | ---: | ---: |
| RunConfigProtocol fuzzy | 89.56257% | 89.57834% |
| Compiled/original instructions | 958/951 | 958/951 |
| ATERM fuzzy | 97.307434% | 97.31056% |
| ATERM exact functions (objdiff) | 18/26 | 18/26 |
| ATERM matched code | 11036/19204 | 11036/19204 |
| ATERM matched data | 18584/18864 | 18584/18864 |
| Global fuzzy | 99.73069% | 99.73071% |
| Global matched code | 2761552/2995176 | 2761552/2995176 |
| Global matched data | 1828688/1832684 | 1828688/1832684 |
| Global linked code | 2243780/2995176 | 2243780/2995176 |
| Global linked data | 1523420/1832684 | 1523420/1832684 |

- All 1027 report units compared: only ATERM changed; no sibling-function,
  exact/code/data/fuzzy/link regression.
- Pool identical: zero strings in both objects.
- Literal audit: 24 functions and 6 arguments checked, zero candidates/errors.
  DiscoverAccessPoints and RunConfigProtocol are skipped because their sizes
  differ from target. This is not claimed as full literal coverage of unmatched
  functions; this source change adds or changes no string/array/data bytes.
- Focused object build and full default 4.3U build: pass.
- Report and `build/43U/ok`: pass.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `git diff --check`: pass.
- ATERM remains NonMatching and unlinked. This is a small fuzzy improvement, not
  an exact function or completed unit. Seven extra instructions remain.

## Reproduction and session evidence

Tools were explicitly configured from the existing cache:

```sh
../.venv/bin/python configure.py --version 43U \
  --wrapper ../toolchain/wibo-release64/wibo \
  --dtk build/tools/dtk --objdiff build/tools/objdiff-cli \
  --sjiswrap build/tools/sjiswrap.exe --bstool build/tools/bstool \
  --compilers build/compilers --binutils build/binutils
WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja build/43U/src/src/scene/setting/ATERM.o
build/tools/objdiff-cli report generate -p . -o build/43U/report.json -f json
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/pool_diff.py \
  build/43U/src/src/scene/setting/ATERM.o build/43U/obj/src/scene/setting/ATERM.o
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/literal_reference_diff.py \
  src/scene/setting/ATERM --all-functions
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/ctxdiff.py \
  src/scene/setting/ATERM ATERMRunConfigProtocol
WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja
WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja build/43U/report.json build/43U/ok
sha1sum build/43U/main.dol
```

Detailed snapshots, build/report logs, the runnable pinned-callee audit and its
JSON output are in `/tmp/aterm-case6-checksum-evidence/` for parent review. This
is a session-local path, not a durable artifact claim.

GATE: PASS for the one authorized strict-fuzzy-improvement trial; not an
exact-match/completion gate. Parent independent verification is still required.
