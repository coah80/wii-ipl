# Keyboard dictionary accessor contract, 2026-10-03 UTC

Base `1fa33882`, branch `agent/bittle/keyboard-manager-reconstruction`.
Only two calls in `src/system/iplKeyboard.cpp` and this log are changed. 43U only;
no header, metadata, compiler-setting, assembly, linking or data edits.

## Source defect and retained correction

Manager::create's two dictionary loops use an OEM index in the range 10..19.
They passed that index to System::getZiDicData(int), which is currently defined
as `smArg.mZiDicData.sys[i]`. The sys subarray has ten elements. Thus the source
expressed the OEM reads beyond that subarray's bounds, despite landing at the
intended adjacent OEM bytes on the target compiler.

The retained calls use the already existing System::getZiOemDicData accessor,
passing the OEM-relative index `oemIndex - EZTX_LANG_MAX` (0..9). This accessor
indexes the actual ten-element oem subarray. The target loads from the combined
system/OEM table base plus four times the absolute OEM index; the corrected
accessor computes the same addresses through the proper object member.
No shared accessor or data layout is changed. The existing system-dictionary
presence check governing fallback selection is preserved, as the target proves.

This is a source-correctness improvement, not a new exact match or a matching-
percentage gain. The entire generated source .text section remains byte-identical.

## Other investigations

- Read the prior fz1 and data-d1 construction/index/memo-copy attempts.
- The existing zero-argument twenty-entry dictionary accessor also preserved
  the baseline score. The dedicated OEM accessor was preferred for its explicit
  index domain and object-member contract.
- Using the system index directly for OEM lookup or changing to an independent
  zero-based OEM counter changed induction lowering and reduced similarity;
  those forms were not retained.
- Explicit allocation followed by placement construction was tried for the arc
  link, resource accessor and allocator. It did not improve output, so those
  larger changes and the extra include were discarded.
- No declaration/register sweep, artificial storage, volatile cast, padding,
  assembly, header change or linking experiment was used.

## Verification

Baseline -> candidate:
- Manager::create: 94.00944 -> 94.00944%, 318/318 instructions unchanged.
- Unit fuzzy: 98.73506 -> 98.73506%.
- Exact functions 31/32, exact code 4752/6024, data 1184/1184 (100%), and linked
  status unchanged. Exact matching of create remains open.
- Fresh baseline and candidate object builds: all 32 reported function instruction
  streams are identical. Entire source .text (6240 bytes), .data (1161 bytes),
  .sdata (6 bytes) and .sdata2 (8 bytes) are byte-identical.
- Pool: all 28 strings identical to target.
- Literal audit: 25 arguments, 32 functions, no candidates, skips or errors.
- Full 1027-unit report has no exact-function/code/data/fuzzy regressions.
- Full 43U build and build/43U/ok passed. DOL SHA1:
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

A host harness extracts the actual production dictionary loops and uses bounded
system/OEM accessor stubs. Compiled with undefined-behavior/bounds sanitizers,
it passes all 1,048,576 combinations of ten system and ten OEM availability bits.
The independent reference checks the target's fallback-selection rule, every
result pointer, the preserved language IDs and both final table sentinels.
No Wii resource-loading or UI runtime execution is claimed.

Private evidence: `/tmp/keyboard-manager-reconstruction/` contains baseline/final
reports and object copies, pool/literal audits, full-build.log, source experiments,
validate_dictionaries.py and dictionary-tests.log. No retail assembly or binary
is included in this commit.

GATE: source accessor bounds corrected with byte-identical generated code and
no matching/data regressions. Frozen for parent validation; no completion claim.
