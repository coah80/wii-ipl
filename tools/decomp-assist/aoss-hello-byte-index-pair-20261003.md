# AOSS Hello stream byte/index declaration pair

Base: `57c17ebe2a7b3788cbbbf54f7dc9a9fb35abaec8`, 43U only.
The sole source change swaps existing uninitialized `u32 firstByte` and
`u32 firstIndex` declarations at AOSS.c lines 2340–2341. All other bytes,
assignments, initializers, scopes, calls, helpers and compiler flags are fixed.

## Two official-scored orders

Exactly two name-lexicographic orders, baseline included, were compiled:

| Order | Hello fuzzy | Unit fuzzy | Instructions / target |
| --- | ---: | ---: | ---: |
| firstByte / firstIndex (baseline) | 92.190475% | 97.73641% | 271/273 |
| firstIndex / firstByte (retained) | 92.48351% | 97.75617% | 271/273 |

Both forced a real MWCC compile by removing the owned object. Build logs and
output timestamps verify compilation. Both immutable source/object snapshots
received a full 1,027-unit official objdiff report, using the actual leaf
configuration with only AOSS's base-object path redirected to its snapshot.
No proxy filtering, object/score deduplication, adaptive continuation or restart
was used. The winning object was reproduced by the final default full build.
This is a partial fuzzy gain, not a new exact function or linking gain.

The cache came from frozen parent `wii-rgb422-next-review`, HEAD
`8f1d13822b51509c354ab676d5e6c0097b7e0552`. Its tree and merged 57c17ebe
both equal `1dde64c7318dc1cfdb4fd7e067931d495d56b02c`.
Before trials, a fresh default full build reproduced that parent's full report
byte-for-byte and all 1,027 source-object SHA256 hashes. Cached tools were
explicitly selected with `../toolchain/wibo-release64/wibo` and
`WIBO_SJIS_MISSING_IMPORTS=1`. No moving-main cache was used.

## Source safety and target evidence

Neither scalar's address is taken. Both retain unsigned 32-bit type and are
assigned on every RC4 iteration before their first read. firstIndex is computed
before indexing the state array; firstByte is loaded before the second-index
calculation, stream sum and stores. No executable statement moves. The stack
construction record and nonce, initialized response/request pointers, modulo
widths, byte masks, state-publication order and buffer accesses are unchanged.

The original Hello function at `0x81401778`, size 1,092, was checked directly
against the SHA1-verified original DOL: all 231 nonrelocated words and 27 direct
call destinations agree with the original object. In both unrolled stream
steps, the target holds firstIndex in r8 and firstByte in r10. The old object
reversed these roles. The retained pair restores those two roles, while keeping
the other preexisting base-register and shared-BSS differences.

## Actual instruction and continuation audit

Only fourteen instruction words change, at Hello-relative offsets:

`+0x214`, `+0x218`, `+0x21C`, `+0x234`, `+0x238`, `+0x240`, `+0x244`,
`+0x290`, `+0x294`, `+0x298`, `+0x2B0`, `+0x2B4`, `+0x2BC`, `+0x2C0`.

Every other text word and every other ELF section, section header and
relocation is byte-identical. The audit maps the actual definitions and uses:

- +0x214/+0x290 define the masked firstIndex in r8 instead of r10
- +0x218/+0x294 load the same state byte into r10 instead of r8
- The following addition, schedule.i store, stream sum and two permutation
  stores consume the corresponding role with identical memory addresses/order
- There is no branch or call inside either changed-role lifetime and no branch
  enters either region partway through
- +0x248/+0x2C4 overwrite r8 with schedule.length immediately afterward
- r10 is never read after either region before its next role definition, or
  anywhere in the function after the second region

All 271 instruction nodes are reachable in the syntactic CFG. Dominator checks
verify both role definitions precede every read, and every return passes through
the unchanged restoration helper. This is graph coverage, not runtime coverage.
Unsigned divwu/mullw/subf modulo operations, 8-bit masks, loop count, branches,
all call identities/locations and stack accesses remain identical.

The frame stays 0x60 with `_savegpr_24` and `_restgpr_24`. The actual DOL
helpers each have eight r24..r31 stores/loads followed by blr. Their slots remain
SP+0x40..SP+0x5C. Changed registers r8/r10 are volatile and do not cross a call.
AOSSInitKeySchedule still receives the same schedule pointer, key pointer,
10-byte key length and eight-byte state length. The free argument is still
loaded from the same schedule.bytes field after the loop. Allocation, failure,
plaintext, header/send and error-return continuations are otherwise unchanged.

## Bounded instruction execution

The checker executes the actual emitted loop setup, all four paired iterations
and the final free-argument load: 261 PowerPC instructions per execution.

- 40,320 cases cover all eight-byte state permutations, varying valid i/j and
  plaintext. Both versions also agree with an independent RC4 recurrence
- Another 1,152 cases exhaust all 64 i/j pairs for three state shapes and six
  output placements; 960 deliberately overlap output with state or plaintext
- Total: 41,472 cases, 82,944 baseline/candidate instruction-slice executions
- Complete ordered memory-read/write traces and resulting memory are identical
- Every final GPR except the proven-dead r10 agrees, including the free pointer

The overlap diagnostics go beyond ordinary fresh-allocation use. They confirm
that no alias ordering is assumed by the role substitution. This is a bounded
software interpreter diagnostic plus instruction/lifetime proof; it is not
whole-function execution with network implementations or Wii runtime testing.
It does not establish correctness of unrelated existing code.

## Previous-attempt coverage

The AOSS, board/fix-board rounds, sol-med rounds, big1, fz1, data-d3 and later
reconstruction/call-contract records were inspected before this proposal.
CRC traversal/accumulator forms, state-update order, stack/object scopes,
const request views, key/global views and shared-BSS binding trials are covered
and were not repeated. No Init or decrypt hypothesis was reopened.

The three officially scored data-d3 declaration trials concern the different
checksum/nonce/stateLength block. fz1 records 90 broad and 50 proper scalar
declaration searches, but surviving records do not identify their exact orders
or per-order official scores. Exact historical overlap remains unknown. This
experiment is a targeted current-context official remeasurement, not a claim
that the pair had never been compiled before.

## Final gates and evidence

- All 20 siblings preserve official reports, raw bodies and relocations
- All 16 exact functions retain zero target instruction differences
- Exact code remains 6,436/16,192; data remains 3,928/3,928
- All allocated noncode bytes, sizes, alignment and relocations are identical
- All nonfuzzy code/data/function/link measures remain unchanged
- All other 1,026 source objects and unit reports equal frozen baseline
- Final object and entire report reproduce the winning immutable snapshot
- Default 43U build, explicit ok/progress/report and diff-check pass
- Pool identical, 1/1, before tuning and after retention
- Literal audit: 12 arguments across 19 functions, no candidates or errors
- Existing unequal-extent Init and Hello literal-audit skips remain
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Evidence: `/workspace/shared/aoss-hello-byte-index-57c17ebe/` (13 MiB).
`run_orders.py` records the completed two trials and must not be restarted.
Read-only runnable checkers are `audit_rc4_mapping.py` and `audit_final.py`;
run from this leaf with `PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=../local-tools
../.venv/bin/python`. They print JSON to stdout. AUDIT_ROOT selects another
validation leaf; CANDIDATE_OBJECT optionally selects its AOSS object for the
mapping checker. Evidence is sealed by `evidence-sha256.json`.
No original binary/disassembly is committed. No main or remote action occurred.

Retained source SHA256:
`3d9712bfe44d0940c9ff013e3aa0e92820bd292d068031938af9da675eeb9425`.
Retained object SHA256:
`2ae576474fddf3bff25f3004931244f3bfce535d26db078793871aea2ee77811`.
Retained report SHA256:
`fa58214432bf0e2bc4630ffd5908fb5a11e00792a042179d23b923073ee755e3`.
