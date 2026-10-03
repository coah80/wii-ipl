# tiZiString language-one copy scalar pair

Base: `d4b9850a45dca95ea4bd8a86dbadeb95a55118bb`, 43U only.
Leaf: `agent/bittle/tizi-copy-local-pair`.
Owned source: `src/keyboard/tiZiString.cpp`, `WithZi::update`, only the
`length`/`output` declarations inside the `getPredictLanguage() == 1` copy arm.
No compiler, header, configuration, array-layout, helper, or other source edits.

## Prior coverage and bounded trial

Reviewed `tiZiString.attempts.md` update section,
`structural-matching.attempts.md:140-146`, and
`fz7.attempts.md:1694-1697,1767`, plus repository-wide exact-symbol searches.
Those attempts cover outer candidate-buffer lifetimes, candidate counts, holding
key descriptors, context copying, and separate `setElementBuffer` declarations.
No logged trial permutes this language-one branch-local scalar pair. Later
`bcac2337` changed prediction refresh/character flow while leaving this pair in
its original order.

The original pair was `s32 length = 0;` then `u16* output = destination;`.
First normalize only declarations, retaining `length = 0;` followed by
`output = destination;` in the same branch scope. Proceed only if the whole
object and complete official report remain byte-identical. Then reverse only
the two declaration statements. This is the complete, non-adaptive search.

| Trial | Function fuzzy | Source/target instructions | Result |
| --- | ---: | --- | --- |
| Original fresh build | 97.273544% | 448/446 | Baseline |
| Declaration normalization | 97.273544% | 448/446 | Whole-object/full-report neutral |
| Reversed two declarations | 97.36323% | 448/446 | Retained for independent review |

Normalization preserved all 1027 compiled source objects and the complete
1027-unit report byte-for-byte. Baseline/normalized owned object SHA256:
`71cf5e0811771a695f910c97af7f4df56915cad2f3b04d8824d4614c63ba01f7`.
Baseline/normalized report SHA256:
`91f14f8add61f35317c8287dea8167929794b0d2a649eb1c70ea4b785e4b3045`.

## Target evidence and change boundary

Original target object `.text` offsets `0x1000/0x1004` prepare output in r3 and
length in r4. The baseline compiled block at `0x1014/0x1018` has the opposite
roles. This is an allocation hypothesis, not proof of original declaration order.

Exactly six candidate instruction words differ from the compiled baseline:
`0x1014`, `0x1018`, `0x1020`, `0x1024`, `0x1028`, `0x1044`.
They exchange r3/r4 for output initialization, length initialization, the output
store, output increment, length increment, and final length scaling.
All instructions before/after this block, branches, relocations, function
extents, and frame/save/restore instructions are byte-identical to baseline.
The function remains 1792 source bytes versus 1784 target bytes.

## Read/write, alias, and continuation review

- Both declarations are ordinary scalar locals, `s32` and `u16*`, without
  constructors, destructors, volatile qualification, or address-taking.
- Both assignments dominate every use. Neither declaration moves out of its
  existing `if` arm. No initializer evaluation, call, pointer dereference, or
  loop operation moves. `destination` was initialized in the outer candidate
  loop scope before this arm is entered.
- The compiled loop's read/write order is unchanged: load and test the source
  halfword; store it through the output cursor; advance output, length, and
  source; repeat. The exit advances source once and writes zero to
  `destination[length]`. This preserves sequential aliasing even when source
  and destination overlap: no load/store is moved across another, and no bulk
  copy or non-alias assumption is introduced.
- The only changed live register roles at block exit are r3/r4. The final r0
  scaled length, r27 source cursor, and r31 destination base are unchanged.
  At the shared continuation `0x10D4`, `lwz r3,0x8C(r28)` overwrites r3 before
  its old value is read.
- The suffix has no read of the old r4 value. Its text-case helpers take one
  argument in r3; `toWLower` assigns r4 at helper offset `0x28`, and `toWUpper`
  at helper offset `0x20`, before either uses it. A subsequent virtual
  `getPredictLanguage()` has only the receiver argument; the actual body uses
  r0/r3/CTR and never reads r4. A later same-language arm reinitializes r4;
  an `EZTXCopy` path replaces it with `this+0x4C` at `0x10C0`. Remaining paths
  either loop without observing r4 or return from this void function, where
  r4 is caller-clobbered. No callee-saved state differs.
- This validates the local baseline-to-candidate transformation and its
  continuation. It does not assert that the still-partial entire function is
  semantically or instruction-exact with the retail target.

## Final gates

- Only `src/keyboard/tiZiString.o` changes among all 1027 source objects.
- Only this function changes among all 1027 report units; all 28 sibling
  function records and bytes remain unchanged. No function or unit regression.
- Unit fuzzy: 98.264534% -> 98.2936%. Unit exact functions remain 26/29;
  matched code remains 3136/5504. Data remains 7680/7680. All non-fuzzy unit
  measures, including linking, remain unchanged.
- Only `.text` bytes change in the owned ELF. Every section header and every
  relocation section is byte-identical to baseline; all non-code data unchanged.
- Pool audit: identical, zero narrow strings. Literal audit: no candidates or
  errors across 27 analyzed functions; update and clearCandidates are skipped
  because source/target sizes differ. It is not a full-function literal proof.
- Fresh full default 43U build passed; final default build and `build/43U/ok`
  passed. DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `git diff --check` passed; registered isolated leaf check passed.

Initial baseline attempts omitted the existing wrapper opt-in and failed in
sjiswrap before any source trial. Retried successfully using the canonical
`WIBO_SJIS_MISSING_IMPORTS=1`, without wrapper/compiler changes. Runtime SHA256:
`981704abab9ec515f417236fa469a78c37ce976a6d2db9a37021ec2e51e5a369`.
Build temporaries and evidence used workspace storage, not the nearly full `/tmp`.

Evidence: `/workspace/shared/tizi-copy-local-pair-d4b9850a/`, including original,
normalized and reversed sources/objects/reports, all-object manifests,
`summary.json`, `final-audit.json`, raw disassemblies, six-word diff, and gate logs.
Candidate source SHA256:
`67c0ee78b4ee51656dc00d90af13fd0071445a2f58d05e1b58cda768702b2ccf`.
Candidate object SHA256:
`a76cba1023f419c3b2ec0b3bf6b9afe28fe8894ade7ad182f7675bca7a9f1148`.
Candidate full-report SHA256:
`5ea83f259da992ad673373e1f68d77e59f655a7765b8f4815506a0ea3b8c3637`.

Fuzzy-only improvement; no exact-match or new-linking claim. Candidate frozen
for parent verification. No remote action or merge performed.

## Runnable instruction and continuation evidence

Additional read-only review uses
`/workspace/shared/tizi-copy-local-pair-d4b9850a/check_copy_pair_evidence.py`.
From a configured 43U leaf, run:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python \
  /workspace/shared/tizi-copy-local-pair-d4b9850a/check_copy_pair_evidence.py \
  --repo . \
  --candidate build/43U/src/src/keyboard/tiZiString.o
```

The baseline defaults to the preserved `baseline.o` alongside the script.
Checker SHA256:
`2169e9ca8f46f605055724f1946b1a450b00b831a17ad73fe94411aa301cebdb`.
Saved result: `copy-pair-machine-evidence.json` in the same evidence directory.
Its SHA256 is
`f23427bbace268787cddbbd243650d633da33d7ff98e0606fec76d96a042ff47`.

The checker reads ELF instruction operands, relocations, CFG edges, and helper
bodies. It verifies the six changed words, the r3/r4 operand bijection over all
16 block instructions, identical memory-address expressions and ordering,
initialization before use, and absence of alternate entries into partial
initialization. Both continuation checks explore 73 states / 72 instructions,
including loop reentry as an explicitly checked block invariant. No changed
incoming register is read before being killed or passed through an inspected
callee that does not read it.

Actual physical GPR live-ins derived from helper CFGs are: `wcschr` r3/r4;
`toWLower` and `toWUpper` r1/r3/r29/r30/r31; `_restgpr_24` r11; and
`getPredictLanguage` r3. The case helpers kill r4 before their `wcschr` call.
Helper body bytes agree between built and original objects. The getter's
12-way indirect branch is resolved using its guarded index and table
relocations, rather than assumed to terminate safely.

All 1027 original objects contain one named `getPredictLanguage` implementation
and one matching slot-0x104 vtable entry, both belonging to `WithZi`; no source
subclass was found. The checked call sequence passes the receiver in r3, and
the declared `virtual u8 getPredictLanguage()` has no r4 parameter or aggregate
return. This is a known-vtable proof, conditional on valid objects and the
ordinary PPC C++ ABI. It is not whole-program points-to analysis, does not
prove vptr integrity, and does not inspect unknown or forged dynamic targets.
The signature's constraint on an unknown override is only an ABI assumption.

Some paths preserve r4 through `_restgpr_24` and the final `blr` at 0x117C.
The checker reports this explicitly: r4 is unobserved caller-clobbered state
at a void return, not universally killed before return. This proves the local
baseline-to-candidate transformation and its continuation under the stated
scope; it does not prove global string bounds/termination, absence of data
races, or equivalence of the remaining partial function to retail.

`test_copy_pair_evidence.py` in the evidence directory passes five negative
tests using only in-memory instruction copies: altered store address,
continuation read of changed r4, unknown virtual slot, a getter requiring r4,
and an actual helper operand change that adds r4 to its derived live-ins.
All five are rejected by the checker; results are recorded in
`copy-pair-checker-selftests.json`. No source edit or compile was made for this
additional evidence review.
