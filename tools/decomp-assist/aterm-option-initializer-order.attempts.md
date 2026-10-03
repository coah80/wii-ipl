# ATERM case-5 option initializer order

## Scope and provenance

- Target: Wii Menu 4.3U only; baseline main `059ed52b0b551e5aa7dd26a284c76c88539b7110`.
- Leaf: `agent/20261003/aterm-option-init`.
- Exactly one authorized candidate was compiled. It moves the existing constant
  `optionIds[7]` declaration below the existing `enabled = SOHtoNs(1)` declaration.
  No other source statement, initializer, type, configuration, or symbol changed.
- Baseline ATERM.c SHA256:
  `404e45ea9e55bb5d6356f7cf4a463e4202871358dc45b7c80a616c52e7fe8c19`.
- Candidate ATERM.c SHA256:
  `db97c32c0c68f8e4c6018908c336c2bac3ddb57a2aaf82a93b4ee900ac9f7abd`.
- Baseline source object SHA256:
  `2673ea22cd766f131fb184801d37581c99d559a9a31eac479783b45cf94156c1`.
- Candidate source object SHA256:
  `572a2d14550fc8f4f07e7cb1011b278717be351ebddc893793f9131b114a19e8`.
- Original object SHA256:
  `14f7910c05e64937ebdf810cee905eab0b77b58d684570311b97fedf40bc7522`.

The earlier fz20 250-build declaration search covered the function-scope block,
not these case-local initializers. The ult15 six trials covered response/session
views and authentication guards. Historical `6deff4fd` manually copied option
bytes after SOHtoNs, but loaded the global options pointer afterward. This trial
keeps that pointer read before the call. No count-word union, session-key type,
message-length cache, or association-helper signature trial was repeated.

## Target evidence and safety

Original RunConfigProtocol `.text+0x1AA8` loads `gAtermRequestOptions`,
`+0x1AB0` calls `SOHtoNs`, then `+0x1AB4..0x1AF8` initializes the seven option
bytes. The baseline object performed those private stores before the call.
This is an emitted-scheduling observation, not proof of a unique original
source declaration order or a source-level semantic bug.

`SOBasic.h:126` declares `u16 SOHtoNs(u16 hostshort)`;
`SOBasic.c:304` returns that value. Both original and current SOHtoNs objects
are exactly `5463043e4e800020`: `clrlwi r3,r3,0x10; blr`. The function has no
memory accesses, callbacks, or global effects. The only call input is the
constant 1 in r3.

The moved initializer consists solely of integer constants `6,0,1,2,3,4,5`.
Its address is first used by the later option-value memcpy. Its source-level
initialization reads no mutable global or volatile object. The mutable
`gAtermRequestOptions` load remains before SOHtoNs in both forms.

Fresh object inspection found exactly 20 changed instructions, all within
RunConfigProtocol indices 235..255 (object byte range `0x1AB0..0x1B03`). Every
instruction and resolved relocation outside that span is identical to the
baseline. All 123 calls have unchanged order and identities. All sibling
function bytes, offsets, and sizes are unchanged. All allocated non-text bytes,
section extents/types/alignment, and the 592 relocations outside the changed
span are unchanged.

A focused evaluator of the changed straight-line block, using the actual
SOHtoNs body, checked pointer values 0, 1, 0x81000000, 0x810C0140 and 0xFFFFFFF8.
Both forms produce the same private memory and callee-saved registers and the
same observable sequence: read `gAtermRequestOptions`, call `SOHtoNs(1)`, then
call `memset(savedOptionsPointer,0,4)`. These are five sampled private-memory and observable-input checks, not a
general symbolic proof or runtime protocol tests. The seven byte writes remain exactly at stack
`0x38..0x3E`, and the enabled halfword at `0x08..0x09`. The unchanged `.sdata2`
bytes are `06000102030405`. No guard, padding, volatile, register forcing,
assembly, or undefined value was added.

The evaluator now pins both original and compiled SOHtoNs bytes to
`5463043e4e800020` before simulating the call. At the following memset boundary,
only volatile r6..r11 differ. r3, r4 and r5, all private writes, and all
callee-saved registers agree. Original and compiled memset/__fill_mem contain no
r8..r11 operands. __fill_mem overwrites r7 from r4 and r6 from r3 at entry, before
using either; the length-four path uses those new values. Thus memset does not
consume the differing scratch values as inputs.

RunConfigProtocol uses no r8..r11 call arguments. Its only later ordinary reads
of those registers are in the authentication region: r8 is freshly defined at
indices 530 and 553 before reads at 537 and 563; r9 at 552 before 562; r10 at 551
before 560; and r11 at 548 before 554..564. The restore-helper r11 is freshly
assigned at 951. The audit pins all occurrences and checks that no direct branch
or data switch-table entry bypasses those definitions. Remaining scratch values
may physically survive earlier calls, but are not observable inputs and are
redefined before caller consumption. This is narrower than claiming all
registers agree at the memset boundary.

## Measurements and gates

Fresh baseline object/report matched the main report exactly before the trial.

| Measure | Baseline | Candidate |
| --- | ---: | ---: |
| RunConfigProtocol official fuzzy | 88.19559% | 89.56257% |
| RunConfigProtocol compiled instructions | 958 | 958 |
| Original instructions | 951 | 951 |
| ATERM unit fuzzy | 97.03666% | 97.307434% |
| ATERM exact functions (objdiff) | 18/26 | 18/26 |
| ATERM matched code | 11036/19204 | 11036/19204 |
| ATERM matched data | 18584/18864 | 18584/18864 |
| Global fuzzy | 99.72892% | 99.73065% |
| Global matched code | 2761552/2995176 | 2761552/2995176 |
| Global matched data | 1828688/1832684 | 1828688/1832684 |
| Global linked code | 2243780/2995176 | 2243780/2995176 |
| Global linked data | 1523420/1832684 | 1523420/1832684 |

- Official complete-report comparison: only ATERM changed; no sibling function,
  exact-function, code, data, fuzzy, or link regression.
- Pool: `POOL IDENTICAL up to 0 (mine=0 base=0)`.
- Literal audit: 24 functions analyzed, 6 arguments checked, zero candidates and
  errors. DiscoverAccessPoints and RunConfigProtocol are skipped because their
  sizes differ from the original. RunConfigProtocol's changed seven constant
  bytes were independently checked as described above; the audit is not claimed
  to cover its full unmatched body.
- Full default 4.3U baseline build: passed, 1034 build steps.
- Candidate focused object build, full default build, report and `build/43U/ok`:
  passed. ATERM remains NonMatching; its edited object is not linked into the DOL.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `git diff --check`: passed; leaf worktree check: passed.
- This is a fuzzy-only improvement. The target function, its instruction diff,
  remaining switch-table data differences, and unit linking remain unfinished.

## Reproduction

Configuration used the existing cached tools, with no downloads:

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

Local detailed logs, both source/object/report snapshots, disassemblies, and the
focused block evaluator are retained in `/tmp/aterm-option-init-evidence/` for
parent verification. This path is session-local, not a durable artifact claim.

GATE: PASS for the authorized strict-fuzzy-improvement trial; not an exact-match
or whole-unit completion gate. Parent independent verification remains required.
