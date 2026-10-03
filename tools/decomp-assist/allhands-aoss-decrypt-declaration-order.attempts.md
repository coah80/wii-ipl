# AOSS decrypt declaration order: official-fuzzy intermediate recovery

Base: `f46483afafa066cf1dfaa6e7603241b9c7beeff4`.
Leaf: `agent/bittle/aoss-decrypt-declaration-order`.
Only the existing uninitialized `controlFlags` and `secondValue` declaration
positions are exchanged in `src/scene/setting/AOSS.c`. No expression, assignment,
initializer, scope, type, array, aggregate, helper, configuration or linking
setting changes. The initialized encrypted-payload pointer remains fixed.

## Current source and historical coverage

The source baseline SHA256 is
`ac7a459ef23327c3dd415b3146391da10553ce8bddeb82b9a4030c120dbd44b4`.
The AOSSDecryptMessage definition SHA256, excluding trailing whitespace, is
`6ea09d2a3ac78a6b0b498073f5e3423ca8898752fb8e92e5c53502c4b0ad8fdf`.
The selected source SHA256 is
`3176094eb46f60ea3fbfad5d70d3d169752650d58fadafa30d17ca7add7567ba`.

Original and baseline have 321 instructions, the same frame and branch/call
positions, and structural/raw score (0,87). The actual key-schedule boundary
passes schedule, complete ten-byte key, key length 10 and dataLength in r3-r6.
The callee consumes those arguments. Allocation error exits, CRC comparison,
success copy and cleanup agree with original. No new semantic defect is claimed.

The earlier `big1.attempts.md` search tried the full 19-declaration leading
block, stopping at its 300-evaluation cap with no structural improvement.
That immediate neighborhood has 477 nonbaseline neighbors, or 478 unique
evaluations including the baseline. Earlier 110/120 capped
searches also do not establish completion. The older improving 180-evaluation
search recorded no complete per-order history, so its exact overlap is unknown.

Current lines 1858-1872 form a contiguous block of 15 existing uninitialized
scalar/pointer declarations. The other four leading declarations include
arrays/aggregate storage and an initializer, and remain fixed. Read-only replay
of the unchanged tool's ordering shows that 154 of this block's 288 evaluated
orders (the baseline plus 153 neighbors) lie in the known old 300-evaluation
prefix, while 134 nonbaseline neighbors lie beyond it.
The current function differs from the recorded older function only through the
accepted, whole-object-neutral complete-key-subobject correction.

The selected order is itself within the previously covered swap prefix.
This gain is recovery through official-fuzzy ranking, not a claim of historical
novelty. Unknown old per-order scores are not reconstructed or invented.

## One official run and complete snapshot scoring

One unchanged official invocation was used:

```
tools/decomp-assist/declsearch.py src/scene/setting/AOSS AOSSDecryptMessage \
    --lines 1858 1872 --max-evals 288
```

Tool SHA256 before/after:
`9642fe689ee3a4d80236b5f790fdda83397214cd209c62ce07088b3f2b3726bb`.
The ordinary compiler wrapper was `../toolchain/wibo-release64/wibo`, with
`WIBO_SJIS_MISSING_IMPORTS=1`. No compiler/configuration/tool/cache changes.

An external NINJA recorder passed every argument unchanged to real Ninja.
It saved source and object after every successful actual MWCC invocation,
checked source stability across the build, and recorded full hashes and the
unchanged Ninja/objdiff configuration hashes. There were 288 unique evaluations:
one baseline plus 287 nonbaseline neighbors. The tool's final baseline-restoration
rebuild adds one further snapshot, for 289 successful snapshots in total.
No compilation was skipped, substituted, reused or deduplicated.

Every snapshot received a fresh official objdiff report in its own private
project. Each project retained the full 1027-unit configuration, changing only
the owned object's base path to that immutable snapshot. A private baseline
report first reproduced the complete live baseline report byte-for-byte.
No snapshot was copied over the live object to obtain a report.

The structural tool retained no improvement: (0,87) throughout, source restored.
It hit its numerical cap exactly after the baseline and all 287 distinct
nonbaseline neighbors had been visited. For 15 locals, there are 105 swaps and
196 distinct moves, with 14 orders common to both sets: 105 + 196 - 14 = 287
neighbors. Recorded orders cover that complete swap/move neighborhood plus the
baseline, establishing a structural local fixed point. This is not exhaustive
coverage of 15! orders.

Official fuzzy ranking recovered snapshot 021 at **97.88162%**, above baseline
**97.74143%**, despite the same structural/raw score (0,87). It swaps only
controlFlags and secondValue. All 289 snapshots were scored and gated; the
first admissible official maximum was selected. No second run or adaptive
expression/declaration variant was attempted. Selection was followed by a real
ordinary rebuild; the object and full live report reproduce snapshot 021 exactly.

The companion CSV records every snapshot, declaration order, full source/object
hashes, official fuzzy, structural/raw scores and preservation result. The last
row is the tool's restoration, not another unique evaluation. Snapshot 000 is
labelled baseline_evaluation; snapshots 001-287 are neighbor_evaluation; snapshot 288
is restoration. All rows pass
every existing sibling, exact/code/data/link and allocated-data gate.

## Behavioral and integration verification

The emitted candidate differs from the baseline in only 18 register operands,
inside three call-free keystream regions: 0x1A8-0x1CC, 0x21C-0x244 and
0x2A8-0x2D0. A symbolic evaluator runs the actual instructions and verifies
identical ordered memory reads/stores, resulting memory and all registers at
each region exit. It does not assume distinct state/stack/input addresses.
All other instructions, branches and all 23 call sites/destinations are
unchanged. Thus call inputs and resource-observation timing remain intact.

The production decryptor and its actual key-schedule, CRC, address-check and
manufacturer-scrambling functions were extracted without body changes into a
native UBSan harness. Candidate and baseline each passed 2,120 cases:

- Every valid payload length 0 through 1472, plus 512 seeded randomized cases,
  with an independent stream-cipher oracle and zlib CRC expectations
- Checksum mismatch, disabled encryption, missing/mismatched/stored address,
  and failure at each of four allocations
- Whole-packet publication, output length, key bytes, access-point state,
  error code and allocation call count checked; allocation guard bytes,
  ownership/free count and trailing packet-state bytes checked

The allocator and byte-order wrappers are controlled test scaffolding. No
network operation or real-device test was performed. Undefined-behavior
instrumentation uses no recovery; candidate and baseline both pass.

- AOSSDecryptMessage: 97.74143% -> 97.88162%, 321/321 instructions
- Unit fuzzy: 97.71665% -> 97.72777%
- Exact functions 16/21, exact code 6436/16192, data 3928/3928 and linking unchanged
- All 20 sibling reports and instruction/relocation streams unchanged
- Allocated non-code bytes, extents, alignment and relocations unchanged
- Every other 1026 unit report unchanged, for every scored snapshot
- Pool identical 1/1; literal audit 19 functions/12 arguments, no candidates or
  errors; the existing unequal-size AOSS_Init_old/AOSSSendHelloRequest skips remain
- Full 43U build, default progress/report/ok and DOL SHA1 pass:
  `26116613f624061ba99c8d1a299aaa6efa85670d`

Baseline object SHA256:
`8dcc1e9c2c25201b4cc4e70f04951c5526b171da95c30cd462a094136e702e09`.
Selected object SHA256:
`243e1cae7fc57681cee68ea32b602aa57c2c97a5454e8afb517ad11c2885d0d0`.

Private reproduction evidence is `/tmp/aoss-decrypt-declaration-order/`, including
all source/object snapshots, compiler outputs, full-config private projects,
official reports, scored manifest, symbolic audit and host harness. Original
objects and disassembly remain private. From this leaf, run:

```
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/aoss-decrypt-declaration-order/verify_evidence.py
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/aoss-decrypt-declaration-order/audit_changed_regions.py
python3 /tmp/aoss-decrypt-declaration-order/validate_decrypt.py
```

Setup note: the first baseline command's session was cancelled with empty logs
and no usable outputs, without a policy-denial or compiler-error reason. After
confirming the session was gone and no matching process remained, the parent
authorized one retry. That full baseline completed. The declaration experiment
itself ran exactly once and was never restarted.

The parent's later JPEG-only main update does not change this baseline's AOSS
source; parent integration still requires its independent current-main gates.

GATE PASS: strict official-fuzzy partial gain; exact/code/data/link and source
semantics preserved; all snapshots scored; full 43U/default progress/DOL pass.
