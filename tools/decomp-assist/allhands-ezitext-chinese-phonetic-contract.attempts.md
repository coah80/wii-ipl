# Chinese phonetic callee contract, 2026-10-02

Base: 654c65dd; branch agent/bittle/chinese-source-reconstruction.
Changed source: libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.c only.
This is type-correctness work with zero code-generation or percentage gain.

## Callee evidence

The actual Zi8MatchPhonetic definition in zi8match.c takes a byte-addressed
12-byte dictionary, a native-width ziU32 dictionary address, a byte record
pointer, and two byte-pointer outputs. In particular its stringOffset output
is ziU8**: it tests *stringOffset, compares a sound cursor against it, and
writes the sound cursor to it. It is not an integer index output.

The old zi8cgetc declaration instead described records and the record output
with a different struct-pointer type, the dictionary address as ziPtr, and
the string output as int*. The two engine calls cast &phoneticGroups to
int*. The third call, in Zi8NewMatchPhonetic, supplied an address-taken int
matchedIndex even though the callee wrote a pointer through it.

The corrected local declaration now has exactly the callee's parameter
representations and compatible C types:
- ziPtr for the opaque phonetic table
- ziU8* for the dictionary and current record
- ziU32 for the packed-table address
- ziU8** for the current-record and string-cursor outputs
- the unchanged matching halfword, byte and workspace parameter types

All three call sites were inspected and updated. The engine's real byte
pointer variables can now be passed by address directly, without incompatible
pointer-to-pointer casts. The small exact helper retains its typed dictionary
array but passes its byte address and uses actual byte-pointer output locals;
matchedString names the recovered cursor role. No shared header or callee
implementation is changed, and the pointer-to-native-word cast is explicit
only at the callee's existing native-address argument boundary.

## Isolated investigation

- Native 12-byte dictionary table indexing: codegen/metrics unchanged
- Named dictionary-record stride: codegen/metrics unchanged
- String-pointer output correction alone: codegen/metrics unchanged
- Complete callee contract, all three call sites: codegen/metrics unchanged

Only the callee-contract correction is retained. These are source-type
checks, not register/declaration-order permutations. The previously parked
halfword-result and component-cursor experiments were not repeated in this
candidate or combined incidentally.

## Validation

Baseline: /tmp/ezi-chinese-recon-baseline.json.
Final full report: /tmp/ezi-chinese-contract-full-report.json.
Full build: /tmp/ezi-chinese-contract-full-build.log.
Detailed checks: /tmp/ezi-chinese-contract-verification.txt.

All 1027 full-report unit measures are unchanged. Unit fuzzy remains
96.65468%; zi8InternalGetZH remains 96.27482%. Exact functions remain 5/8,
exact code 4168/47816, and exact data 144/536. No metric gain is claimed.

Compared with a preserved baseline object, every owned code/data section has
identical length, payload bytes and canonical relocation tuples:
.text 47816, .sdata2 16, .sbss2 8, .data 392, extab 48, extabindex 72.
The NOBITS section is checked by extent; all other payloads compare bytewise.

Pool first: identical and empty. All five baseline exact functions retain
ctxdiff diffs 0 with identical instruction counts:
Zi8SetFindCand 50, ZiGetNextPhonetic 31, ZiPartialMatch 51,
Zi8NewMatchPhonetic 755, Zi8GetChineseCandidates 155.
The unmatched engine remains 10676/10676 instructions; its code payload and
relocations are baseline-identical as well.

Full 43U build passes with the approved wrapper and WIBO_SJIS_MISSING_IMPORTS=1.
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No linking, remote, metadata, shared-header, assembly,
volatile, artificial storage or register-forcing changes.
