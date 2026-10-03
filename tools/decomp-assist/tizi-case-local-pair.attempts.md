# tiZiString case-conversion scalar pair

Base: `86e56941932022ad22c325d39aa0191785a37f0f`, 43U only.
Leaf: `agent/bittle/tizi-case-local-pair`.
Owned source: `src/keyboard/tiZiString.cpp`, `WithZi::update`, only the
`position` / `candidate` declarations in the existing case-conversion block.
No helper, header, compiler, array, initializer-order, or other source changes.

## Read-only selection and prior exclusion

The adjacent language-0x12 copy arm was rejected as a trial candidate. Target
and current both use r3 for output and r0 for character. All nine instructions
agree after normalizing the enclosing source/destination registers and branch
addresses; that arm has no supported local allocation discrepancy.

The following case-conversion block does have a local discrepancy. Target
initializes candidate in r25 and position in r24 at `.text` 0x10C4/0x10C8.
The current baseline initializes candidate in r24 and position in r25 at
0x10D8/0x10DC. Stores, position comparison, increments and character loads
consistently use these opposite roles. This is an allocation hypothesis, not
proof of the original source declaration order.

Reviewed the update section of `tiZiString.attempts.md`,
`structural-matching.attempts.md:143-146`, `fz7.attempts.md:1695-1697,1767`,
and `ult15.attempts.md` (its active tiZiString trials are setElementBuffer).
Exact-symbol log searches and all-history source `git log -G` for `position`
and `for (u16* candidate` found no case-pair declaration trial; those lines
had remained unchanged since the original readable implementation. The
separate language-one pair accepted in PR #1114 was not retried.

## Exact bounded trial

Original: `s32 position = 0;` followed by
`for (u16* candidate = destination; *candidate != 0; ++candidate)`.
Normalize to `s32 position; u16* candidate; position = 0;` followed by
`for (candidate = destination; ...)`. Require whole-object, all 1027 source
objects, and complete official-report byte identity before proceeding.
Only if neutral, reverse the two declaration statements, retaining all
assignments and for-init execution in their original order. No other variant.

| Trial | update fuzzy | Compiled / target bytes | Outcome |
| --- | ---: | ---: | --- |
| Fresh baseline | 97.36323% | 1792 / 1784 | Baseline |
| Normalized declarations | 97.36323% | 1792 / 1784 | Whole-object/full-report neutral |
| Reversed declarations | 97.40807% | 1792 / 1784 | Retained for independent review |

Baseline/normalized object SHA256:
`a76cba1023f419c3b2ec0b3bf6b9afe28fe8894ade7ad182f7675bca7a9f1148`.
Baseline/normalized full-report SHA256:
`ca12dada5b0f94e8fd04c98493e1a9b79cfa804f5d70af8cfc8b287332760860`.

## Scope, sequencing and alias safety

Both variables are built-in, nonvolatile scalars (`s32` and `u16*`), with no
constructors, destructors, or address-taking. Both assignments dominate all
uses. Candidate's declaration moves from the for-init scope into its existing
immediately enclosing explicit block. This only begins its lifetime before
one independent scalar assignment; that block contains nothing after the
loop. The nearby `goto nextCandidate` skips the entire block and does not
enter either lifetime. No read, store, call, increment or branch moves.

The case helpers take the loaded character by value in r3. Neither local's
address nor the candidate cursor itself is passed to them. The sequential
character load, conversion call, and store retain their order and mapped
addresses, so no non-alias assumption or bulk-copy change is introduced.

## Actual instructions, calls and callee-saved continuation

Exactly ten words change: 0x10D8, 0x10DC, 0x1114, 0x1120, 0x1128, 0x1134,
0x1140, 0x1144, 0x1148, 0x114C. The 32-instruction block is identical under
an r24/r25 bijection. All other update words, call relocations, branches,
function extents, and sibling bytes are unchanged. Candidate now has the
target's local roles. The target still increments pointer before position,
whereas the baseline/candidate increment position before pointer; this is
explicitly reported, not claimed exact.

Runnable read-only checker and evidence are in
`/workspace/shared/tizi-case-local-pair-86e56941/`:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python \
  /workspace/shared/tizi-case-local-pair-86e56941/check_case_pair_evidence.py \
  --repo . --candidate build/43U/src/src/keyboard/tiZiString.o
PYTHONPATH=../local-tools ../.venv/bin/python \
  /workspace/shared/tizi-case-local-pair-86e56941/test_case_pair_evidence.py
```

Checker SHA256:
`d8c041e106f6ccda1c75ed6e80404aac33a9204a910e835330a4a1e954954f27`.
It reads actual ELF operands, relocations and CFGs, rather than accepting a
written conclusion. It verifies the operand bijection, branch/memory order,
initializers, external entries, actual character argument, and target roles.
It derives transitive physical GPR live-ins/may-writes/must-writes from actual
helper bodies, including the EZTXCopy tail branch. Built and original helper
bodies and derived GPR effects agree.

- toWLower/toWUpper, including wcschr, neither read nor write r24/r25.
- The complete EZTXCopy -> Zi8CopyW -> Zi8CopyWordListW closure, including
  Zi8LogError, _savegpr_27 and _restgpr_27, neither reads nor writes r24/r25.
- The known getPredictLanguage implementation neither reads nor writes them;
  its guarded 12-entry indirect branch is resolved from table relocations.
- The continuation explores 64 states/instructions. Loop reentry establishes
  the separately checked block invariant. Its only equal-state closure is
  the actual `_restgpr_24` call at 0x116C, which overwrites both differences.
- The unchanged prologue saves r24/r25 using `_savegpr_24` at 0xA90. Exact
  save/restore operands prove r24 is saved at allocated SP+0x10 and r25 at
  SP+0x14 in the unchanged 0x30-byte frame. Actual restore loads the same
  equal-memory slots. No callee-saved difference is allowed at void return.

Eight negative tests pass using in-memory instruction copies only: wrong
store address, continuation r24 use, unknown virtual slot, getter r24 use,
missing r24 restoration, case-helper r24 clobber, an actual helper operand
that adds r24 to its derived live-ins, and a wrong restore slot. Each is
rejected. Tests do not modify or compile source/ELF files.

Virtual scope remains explicit: all 1027 original objects contain one named
getPredictLanguage implementation and one matching slot-0x104 WithZi vtable
entry; no source subclass was found. The declared nonvariadic `u8` member
function takes only receiver r3. The proof assumes valid objects using that
known vtable and ordinary PPC C++ calls. It is not whole-program points-to
analysis, does not prove vptr integrity, and does not inspect unknown or
forged targets. A signature constraint alone is not proof of unknown code.
The check also does not prove global input bounds/termination, lack of data
races, or equivalence of this still-partial whole function to retail.

## Final gates

- Only tiZiString.o changes among all 1027 source objects; only update changes
  among all 1027 report units. All 28 sibling function records/bytes unchanged.
- Every non-fuzzy field in the complete report is identical. Unit fuzzy
  98.2936% -> 98.308136%; exact functions 26/29, code 3136/5504 and data
  7680/7680 unchanged. No exact-count, data or linking gain/regression claim.
- Only `.text` bytes change. All ELF section headers, relocation sections,
  symbol tables and non-code data are byte-identical.
- Fresh full default 43U build passed; final default build and `build/43U/ok`
  passed. DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- Pool identical, zero strings. Literal audit: 27 analyzed, zero checked
  arguments/candidates/errors; update and clearCandidates skipped because
  source/target sizes differ. This is not a full-function literal proof.
- Source diff is exactly the authorized block change; `git diff --check`
  passed. Cached tool paths and `WIBO_SJIS_MISSING_IMPORTS=1` were used, with
  workspace TMPDIR and no software download, wrapper or compiler change.

Candidate source SHA256:
`f0ee52b1608f5aeb5ec85689b54201f52f06a762dfa52bc0134bb467beb91430`.
Candidate object SHA256:
`1617890835c018e253238e21f65a2629b893e2bbc2ee60fa0a4ac69cc141fbc4`.
Candidate full-report SHA256:
`a8526bf6cb0ba51481fd55be7eb54cd86ecc119273c8343c1c53afb616597760`.
Evidence includes the finite driver, original/normalized/reversed sources,
objects, reports and manifests, checker and self-tests, actual disassemblies,
`case-pair-machine-evidence.json`, `final-audit.json`, and build/gate logs.
Candidate frozen for parent verification; no remote action or merge performed.
