# Chinese user-dictionary address contract, 2026-10-03

Base: `5dcbc437`; branch `agent/bittle/chinese-uwd-address-contract`.
Changed source: `libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.c` only.
This is a type-correctness correction with no matching-percentage gain.

## Source and target evidence

The exact `Zi8GetZHuwdPtr` definition in `zi8ZHuwd.c` returns `ziU32` and
writes a native `ziU32` address through its first argument. It clears that
word on failure, or stores the selected dictionary address and adds its
eight-byte header on success. Its second output is a halfword entry count;
its third argument is the workspace. Both return paths produce zero or one.

The original objects contain exactly two executable references, from
`Zi8Get1KeyPressCandidates` and `zi8InternalGetZH`, plus the callee's own
exception-index reference. The accepted one-key source already uses the
definition's native address representation and explicitly narrows status.

The Chinese caller passes its stack word at 0x10C in r3, its halfword at
0x9A in r4, and the workspace in r5. After the call it explicitly narrows
the returned status to a byte. It loads the address word to decode bytes
at offsets one and two, checks a flag through the same address, and advances
that address by three for each entry. The address output does not escape
anywhere else.

The correction agrees with the real definition: the local extern returns
`ziU32` and takes `ziU32*`; `userEntriesAddress` has that native unsigned
word type. The three byte reads use explicit byte-pointer views, the loop
keeps its increment by three, and the status test has an explicit byte cast.
No additional local, helper, shared-header change, control-flow change or
unrelated prototype correction is included.

## Validation

Fresh baseline: `/tmp/ezi-chinese-uwd-baseline.json`.
Fresh final report: `/tmp/ezi-chinese-uwd-final.json`.
Full build: `/tmp/ezi-chinese-uwd-full-build.log`.
Detailed checks: `/tmp/ezi-chinese-uwd-verification.txt`.

All 1027 complete source objects are byte-identical to the fresh baseline,
including `zi8cgetc.o` and its symbol/relocation metadata. The entire decoded
1027-unit report is identical. Unit fuzzy remains 96.65468%; engine fuzzy
remains 96.27482%, with 10676/10676 instructions. Exact functions remain 5/8,
exact code 4168/47816 bytes, and matched data 144/536 bytes.

Pool checked first: identical and empty. All five exact functions retain
ctxdiff diffs zero: Zi8SetFindCand 50 instructions, ZiGetNextPhonetic 31,
ZiPartialMatch 51, Zi8NewMatchPhonetic 755, Zi8GetChineseCandidates 155.
The existing advisory flow audit still agrees on 168 ordered calls, 1594
mapped direct branches and all 98 generated switch destinations. This
normalization is diagnostic, not an exact-match claim for the engine.

Full 43U build passes with the approved wrapper and
`WIBO_SJIS_MISSING_IMPORTS=1`. DOL SHA1 remains
`26116613f624061ba99c8d1a299aaa6efa85670d`. `git diff --check` passes.
No return-width experiments, artificial storage, assembly, volatile use,
linking changes or remote operations were performed.

## Read-only remainder review

Both large engines were compared with current main before editing. Their
sources were unchanged. Chinese's remaining normalized instruction gaps
are return-copy placement, the already-tested component-cursor reload,
and the two previously parked paired-phonetic halfword conversions. Those
experiments were not repeated.

Alpha's early initialized dictionary index remains necessary in the
reconstructed source: highlighted-output capacity exits reach optional
dictionary-count finalization before the dictionary loop. The target's
unused workspace store supplies no demonstrated source lifetime. Previous
attempts already cover separate/direct exclusion results, dictionary-kind
switches, candidate-skip order, updated-count comparisons and prefix append
forms. This pass found no new supported alpha lifetime or control-flow
representation to trial, and left alpha unchanged.
