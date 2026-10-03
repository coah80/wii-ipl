# One-key call and parameter contracts, 2026-10-03

Base: 674722c1; branch agent/bittle/onekey-contract-reconstruction.
Owned source: zi81key.c only. This is source-type correctness work with no
percentage gain. No callee implementation or shared header was changed.

## Retained, definition-backed boundaries

- Replaced the private ziGetParam replica with the existing shared type.
  The old replica's bytes at 0x20/0x21/0x22 were named
  wordCandidates/count/letters. The established shared type names those
  count/letters/completion. All accesses were renamed by their offsets;
  no field was moved or read/written at a different address. The unused last
  word retains the same target size. Dispatcher return declarations and the
  two public candidate-count return types now agree on their byte/full-word
  roles, respectively.
- Added the actual _Zi8GetCandidates and _Zi8CheckCandidates prototypes,
  using ziGetParam pointers. Their explicit byte-result handling is preserved.
- Recovered Zi8Ord2Ord's actual ziU16 return together with the local duplicate
  helper's ziU16 ordinal parameter. Ordinary typed uses replace the explicit
  halfword masks of the former full-word local. Correcting only the external
  return lost the exact helper; this coherent pair preserves all 50 of its
  instructions and every caller instruction.
- Zi8GetPInfo and Zi8GetZInfo actually accept a ziU32 phonetic code and return
  ziU32. Corrected their local declarations; the existing caller's explicit
  byte result conversion remains.
- Added the actual Py/Bpmf phonetic prototypes. This exposed two scratch
  arrays declared as 32 bytes despite receiving 16 halfword outputs. They
  are now 16-element ziU16 arrays, preserving their 32-byte extents. The
  candidate output buffer is likewise 16 ziWChars instead of 32 bytes plus
  a cast. No new storage or alignment directive was added.
- Zi8GetZHuwdPtr writes a native ziU32 address through its first parameter.
  Its local declaration and address-taken receiving variable now use that
  actual type. Byte decoding uses an explicit view of userEntriesAddress;
  address stepping remains three bytes. This removes the incompatible
  pointer-to-pointer/integer-output contract without an extra temporary.
- Zi8GetTableAddress, Zi8Memset and Zi8InitDupWordBuf local declarations now
  agree with their actual definitions. The parameter object is cleared
  through the memset callee's byte view.
- Zi8ZHCheckSpelling now agrees with its caller in zi8alpha.c: byte Boolean
  return, byte input count, and opaque workspace pointer. Its result was
  already a byte; removing the input's redundant full-word masks preserves
  the entire existing exact body.

The authoritative definitions are in zi8getc2.c, zi8misc.c, zi8cinfo.c,
zi8match.c and zi8ZHuwd.c. The public count-return declarations are in
zi8getc2.c; the spelling-check declaration is in zi8alpha.c. Only the owned
file was edited. The private option/work views remain in place; this is not
an attempt to consolidate every library type or repair every declaration.

## Isolated trials

- PInfo/ZInfo actual declaration pair: neutral
- Bare Py/Bpmf prototypes: compile error exposing byte-array/halfword-pointer
  disagreement; fixed by correctly typed same-size output buffers
- Ord2Ord return only: duplicate helper 100 -> 98.8%; rejected
- Ord2Ord return plus typed ordinal: original exact helper restored, neutral
- Shared request type and offset-preserving field names: neutral
- Typed dispatcher prototypes with shared request type: neutral
- Phonetic and candidate halfword output buffers: neutral
- Native user-dictionary address contract: neutral
- Public return/input boundaries: neutral
- Final retained combined contracts: all code/data and metrics unchanged

Other coherent local spelling/alternate-phonetic parameter-width trials were
neutral and are not included without an external declaration disagreement.
The PUD return/caller-byte trial on the new baseline dropped unit fuzzy to
97.782295% and exact data 1280 -> 1232; it was rejected and is not included.
No blanket byte-cast, declaration-order or register-allocation sweep was used.

## Verification

Baseline report: /tmp/ezi-onekey-contract-baseline.json.
Baseline object: /tmp/ezi-onekey-contract/baseline.o.
Final report: /tmp/ezi-onekey-focused-full-report.json.
Full build: /tmp/ezi-onekey-focused-final-build.log.
Detailed gates: /tmp/ezi-onekey-focused-verification.txt.

All 1027 unit measures are unchanged. Unit fuzzy remains 98.23523%; main
candidate engine remains 96.41927%. Exact functions remain 5/9, exact code
3952/21460, and matched data 1280/1388. No new exact function or percentage
gain is claimed.

All owned emitted sections have baseline-identical lengths, payloads and
canonical relocations: .text 21496, .rodata 1152, .data 44, .sdata2 8,
extab 72 and extabindex 108. All nine functions have baseline-identical
disassembly, not only equivalent scores. Each of the five existing exact
functions still has ctxdiff diffs 0 and identical instruction counts:
Zi8IsMatch1Key 97, MatchAltSound1Key 341, Zi8SetFindCand 50,
ZiIsSupportedPhonetic 81, Zi8ZHCheckSpelling 419.

Pool first: identical and empty. Full 43U build passes with the approved
wrapper and WIBO_SJIS_MISSING_IMPORTS=1. DOL SHA1:
26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No linking, remote, metadata, new assembly, volatile
workaround, dummy storage, undefined value or forced-register change.
