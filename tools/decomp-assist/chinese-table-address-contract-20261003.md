# Chinese table-address contract, 2026-10-03

Base: `3dd12f63`, 43U. This is a source-contract consistency correction.
It has no exact, fuzzy, data or linking percentage gain.

## Definition and caller evidence

`zi8cgetc.c` locally declared `Zi8GetTableAddress` as returning `ziPtr`.
The exact definition in `zaddress.c:91` returns `ziU32`, forwarding
`Zi8GetTableData`. That helper's address selector explicitly converts the
computed dictionary pointer to `ziU32`. The local declaration therefore had
an incompatible cross-translation-unit function type, despite using the same
machine return register.

The change corrects that one return declaration and adds fourteen explicit
conversions at previously implicit assignments: twelve `ziU8*` conversions
and two `ziU16*` conversions. The latter preserve the exact phonetic helper's
halfword `phoneticOffsets` and `ordinalTable`. Its halfword ordinal table is
distinct from the giant engine's byte ordinal table. The fourteen existing
byte-pointer conversions remain unchanged. These are exactly fifteen changed
source lines; no argument, condition, statement order, initializer, local type,
scope, header, callee, symbol metadata or linking flag changes.

The project's typedefs make `ziU32` unsigned long and `ziPtr` void pointer.
A standalone compile-time assertion check using this unit's actual target
compiler and flags verifies `sizeof(ziU32) == sizeof(ziPtr) == 4`,
`sizeof(ziU16) == 2` and `sizeof(ziU8) == 1`. No host-width assumption is used.

## Original ABI verification

The original DOL SHA1 was verified independently. The wrapper at
`0x8145F3B0` calls `Zi8GetTableData` at `0x8145F1E0`, then leaves the full r3
return unchanged through its epilogue.

All 28 call relocations in this unit were checked against raw DOL branches:
20 in `zi8InternalGetZH` and eight in exact `Zi8NewMatchPhonetic`. Each first
return consumer stores or copies the entire address-sized r3 value. Those
consumer words also agree with the extracted original object. No byte or
halfword narrowing is introduced at the API boundary.

This establishes return-width and flow compatibility, not a uniquely proven
original pointer-versus-integer return spelling. The correction follows the
existing exact definition and the already corrected one-key/zconvert caller
contracts. No missing machine operation or new dictionary behavior is claimed.

## Prior-attempt distinction

`fz21.attempts.md:605` records MAX gM17, a byte-pointer return experiment that
failed to compile at a legitimate halfword-table consumer. It did not try the
callee's integer-address contract with per-consumer typed conversions.
The earlier zconvert and one-key contract corrections did not touch this unit.

## Fresh verification

- Rebuilt the unchanged baseline in a fresh leaf using the approved
  `wibo-release64/wibo` wrapper and `WIBO_SJIS_MISSING_IMPORTS=1`
- Corrected entire `zi8cgetc.o` is byte-identical to baseline, including all
  code/data sections, symbols and relocations
- After the full default build, all 1,027 source-object SHA256 hashes and the
  complete generated report remain equal to pinned main
- All five exact functions retain zero normalized instruction differences:
  SetFindCand 50/50, GetNextPhonetic 31/31, PartialMatch 51/51,
  NewMatchPhonetic 755/755, GetChineseCandidates 155/155
- Unit unchanged: 5/8 exact, 4168/47816 exact code, 144/536 data,
  96.65468% fuzzy; the giant engine remains 96.27482%
- Pool 0/0, identical; literal audit analyzes all eight functions with no
  candidates, errors or skips, and zero narrow-string arguments to compare
- Full default, explicit progress/report and `build/43U/ok` targets pass
- DOL SHA1 remains `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

No complete dictionary-engine or Wii runtime execution is claimed. Entire
object identity is the emitted-code neutrality evidence.
