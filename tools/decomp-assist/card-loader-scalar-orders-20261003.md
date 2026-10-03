# Card icon-loader scalar declaration order

Base: `a4a4374cd234caeb538bda62633c2cb9a88bf00f`, 43U only.
Owned source: `src/scene/cardSequence/iplCardSequence.cpp`.
The only source edit reorders three existing uninitialized scalar declarations
at lines 700–702 in `loadCardFileIcons`. The stack record, assignments,
initializers, scopes, expressions and calls are unchanged.

## Finite official-scored experiment

Exactly six name-lexicographic permutations were compiled, including baseline.
Every order forced a real MWCC compile by removing the owned output object.
Each immutable source/object snapshot received a full 1,027-unit official
objdiff report using a copy of the actual configuration with only this unit's
base-object path redirected. No proxy filtering, object/score deduplication,
adaptive continuation or restart was used.

B = `u32 iconAddressBase`, O = `s32 iconAddressOffset`, R = `s32 result`.

| Order | Loader fuzzy | Instructions / target |
| --- | ---: | ---: |
| B/O/R | 90.34375% | 508/512 |
| B/R/O | 90.34375% | 508/512 |
| O/B/R | 90.37305% | 508/512 |
| O/R/B | 90.37305% | 508/512 |
| R/B/O, baseline | 90.34375% | 508/512 |
| R/O/B | 90.37305% | 508/512 |

There are six distinct source hashes and two object hashes. The first
lexicographic winning order, O/B/R, is retained. Unit fuzzy improves
97.219246% to 97.225334%. This is a partial allocation gain; the function
remains nonexact and the unit remains unlinked.

## Initialization, alias and actual instruction evidence

`result` is assigned by CARDFastOpen before its first read. Both address locals
are assigned at lines 711–712 before their consumers; comment-stage base is
reassigned at line 869. None of the three locals has its address taken. All
retain their original signed/unsigned 32-bit types. CARDFileInfo and both
sector-size output slots remain in the same preceding stack record.

Only seven instruction words change, at loader-relative offsets:
`+0x48`, `+0x4C`, `+0x4E0`, `+0x53C`, `+0x574`, `+0x5C0`, `+0x5FC`.
Every other ELF section, header and relocation record is byte-identical;
all other `.text` words are identical too.

The baseline stores the aligned image base in r23 and the byte offset in r22.
The candidate stores the base in r22 and the offset in r23. The audit checks
each actual defining and consuming instruction, rather than merely erasing
register names:

- `+0x48/+0x4C` define the same masked base and 0..511 byte displacement
- `+0x4E0` uses the displacement in the transfer-length sum
- `+0x53C/+0x574` use the base in both unsigned range calculations
- `+0x5C0` forwards the same base as CARDRead's fourth argument in r6
- `+0x5FC` forwards the same buffer-plus-displacement as memcpy's r4 argument
- r23 is never read again after `+0x5FC`; the comment continuation assigns
  r22 at `+0x648` before its next reads at `+0x688/+0x6A4`

All 508 instruction nodes are reachable in the syntactic CFG. A dominator
check verifies the appropriate definition precedes every use, including the
comment-phase redefinition, and every return passes through the unchanged
restore helper. This graph check is not runtime instruction coverage.

The frame remains 0x60 and both versions call `_savegpr_20` and
`_restgpr_20`. The actual original DOL helper entries at `0x815F94A4` and
`0x815F94F0` store and reload r20..r31 from the same slots. With unchanged
r11 = SP + 0x60, r22/r23 are saved at SP+0x38/SP+0x3C. The sector outputs
remain SP+8/SP+0xC, and CARDFileInfo begins at SP+0x10; no lifetime or stack
object was moved. All 13 direct-call identities and locations are unchanged
between baseline and candidate. Normal call arguments, result tests and
branch destinations are unchanged.

The original loader at `0x813D3424` was checked directly against the original
DOL: all 451 nonrelocated instruction words and all 13 direct calls agree.
Its ordered non-save/restore call identities agree with baseline/candidate.
A bounded actual-instruction slice test passes 10,700 arithmetic/argument
cases, 21,400 baseline/candidate executions, including 32-bit boundaries and
deterministic generated values. It checks base/offset arithmetic, range
comparisons, CARDRead/memcpy ABI arguments and the comment redefinition.
This is not full-function execution with CARD implementations or Wii runtime
validation, and does not establish correctness of untouched code.

## Prior coverage and exclusions

The complete committed CardSequence, old address-named sol-med rounds, gk3,
icon-reconstruction and permission/thread-contract logs were inspected.
They cover initialized address/format ordering, stack-record member ordering,
indexing, error/helper joins and reserved-format carry. The 360 recorded gk3
declaration evaluations concern cardThreadMain, not this loader. No recorded
six-order evaluation of this exact scalar block was found. Exact historical
overlap remains unknown; absent artifacts are not proof of novelty.

The parent's saved 2026-10-03 04:56 checkpoint records the separate zero-icon
negative-shift correction regressing 90.34375% to 89.25%. It lacks a surviving
source/hash/path and final restoration record after the later workspace reset.
That hypothesis was treated as closed and was not compiled here. The closed
reserved-format-3 carry trial was also excluded. Neither boundary is corrected
or exploited by this declaration-only change.

An existing similarly named card-icon leaf was inspected read-only after a
branch-name collision. Its six neutral orders concern MemoryCardManager's
`_create_icon` pointer locals, a different source/function. It is unchanged.

## Final gates and reproduction

- All 27 exact functions individually retain zero original ctxdiff differences
- All 29 siblings retain raw bodies, relocations and official reports
- Exact code remains 4168/9852; exact data remains 1496/1496
- All allocated nontext bytes, extents, alignment and relocations are identical
- Other 1,026 unit reports and nonfuzzy global metrics equal the frozen baseline
- Default 43U Ninja, explicit ok/progress/report and diff-check pass
- Final full report equals the winning immutable snapshot exactly
- Pool: 43/43 identical before and after tuning
- Literal audit: 45 arguments across 29 functions, no candidates/errors;
  the unchanged unequal-extent loader remains the sole skip
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`

Main advanced independently to `86e56941` during validation. That changes only
`tiZiString.cpp`; the other 1,025 non-owned objects still equal current main.
This leaf preserves its authorized a4a4374c validation and does not rebase or
modify main. No remote actions occurred.

Workspace evidence: `/workspace/shared/card-loader-orders-a4a4374c/` (31 MiB).
`run_orders.py` records the completed six-trial experiment and must not be
restarted. `audit_mapping.py` is the runnable instruction/slice/helper checker;
set `AUDIT_ROOT`, `CANDIDATE_OBJECT` and `AUDIT_OUT` to check a different leaf
and write fresh output. `audit_final.py` reproduces the frozen-base CFG/exact/
report checks and includes the explicitly observed disjoint main checkpoint.
Run the checkers with `../.venv/bin/python`, `PYTHONPATH=../local-tools` and
`PYTHONDONTWRITEBYTECODE=1`. No binary or original disassembly is committed.

Source SHA256: `149b8f5112b0d5c92a8c22474826ffb7a3f860c0f1b26d3c3e1bbfb1609544b4`.
Object SHA256: `576238688dcdab32d60124e60bee48c030228e48949ad40e76838db5c935f316`.
Report SHA256: `36799c462088f6831f7ab0d64200b860052c6911643797cf9c65d955e952021c`.
