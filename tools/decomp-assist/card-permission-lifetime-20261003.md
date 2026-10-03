# Card move/copy permission result lifetime

Base: `57ccda3883537a308568c03924af2cebf2d8a789`.
Owned source: `src/scene/cardSequence/iplCardSequence.cpp` only.

## Retained reconstruction

Give the permission-check stage of `runCardMoveOrCopy` its own initialized
`permissionResult`, scoped around the existing status query, command permission
checks and error gate. The later transfer result remains separate. There is no
copy back, added operation, dummy local or initializer-order search.

Original `runCardMoveOrCopy` begins at `0x813D3D14`. Its permission stage
`+0xC8..+0x148` initializes r16 to zero at `+0xD4`, sets -10 for denied copy/move
permissions, or takes `CARDGetResultCode` after a failed status query. The error
report consumes that value at `+0x140/+0x144`, and failure branches to the final
return. Success reaches a new status query at `+0x158`; the old permission value
is dead, and r16 is reused for `createSize` at `+0x170`.

The current source previously reused `result` across the permission and transfer
stages. Narrowing the permission result follows the original lifetime without
changing control or output ownership: failed permission goes to `finish`, whose
only operation is return; successful permission is followed by a new assignment
to `result` from `__CARDGetStatusEx`. No cleanup path reads the scoped value.

This recovers a natural partial previously restored under exact-only acceptance.
`gk3.attempts.md` lines 108/240 recorded 185 -> 176 instruction differences,
identical pool and no exact regressions, but no isolated fuzzy score. The older
`iplCardSequence.attempts.md` also restored this result scope for its focused
exact-function diff. The fresh score below was measured directly.

## Results

- `runCardMoveOrCopy`: 97.8125% -> 97.88651%
- Instructions: unchanged 608/608; ctxdiff differences: 185 -> 176
- Unit fuzzy: 97.20097% -> 97.219246%
- Exact functions: unchanged 27/30; matched code: unchanged 4168/9852 bytes
- All 27 exact functions individually checked: zero ctxdiff differences
- Matched data: unchanged 1496/1496 bytes
- All allocated non-text bytes, sizes and alignments unchanged
- Every other unit's complete report unchanged; no function regression across
  the 1027-unit report
- Pool: 43/43 identical before and after
- Literal audit: 45 arguments across 29 functions; no candidates/errors. The
  unchanged unequal-extent icon loader is the only skip
- Full 43U all_source/report/DOL gates: pass
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check`: pass

## Focused original-machine validation

A bounded integer-PPC interpreter executes the actual baseline, candidate and
original instruction prefixes. It models the CARD calls and records fixed-ABI
arguments and error reports through either permission failure return or the next
status query beginning transfer. No arbitrary register renaming is assumed.

All 17,328 cases agree, including both slots, file numbers 0/63/126, all 256
permission bytes, copy/move/other command values and signed boundaries, negative
status results, and negative/nonnegative `CARDGetResultCode` results. In
particular, the retail continuation when that latter result is nonnegative is
preserved. Outcomes: 12,912 transfer entries and 4,416 early returns. Each version
covers 79 prefix instructions, and early returns preserve SP and nonvolatile
GPRs. An in-memory wrong-permission-mask mutation is detected.

The whole original function's 513 nonrelocated instruction words and all 79
call destinations agree with raw DOL bytes. Baseline, candidate and original
retain the same ordered call identities. This is bounded permission-stage
proof, not a full copy/move or Wii runtime test. The function remains nonexact;
no linking or full decompilation claim is made.
