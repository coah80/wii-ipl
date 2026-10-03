# Right-name compatibility on 5af01fa8, 2026-10-03

This is a separate current-baseline proof. The original source candidate,
commit c9c1491f, d0 evidence and verify_tiCandidateBox_right_names.py remain
unchanged. No new production form or compiler trial was performed here.

External PR1131 merged as 5af01fa8b9ed69e08d153b6ecb6aae4eb43e9efb. Its production
diff adds two inline geometry helpers and changes CalcPaneLocate_; create and
the pane-name declarations are unchanged. The external log is
`tools/decomp-assist/a23h.attempts.md`. Its historical measurements are not
substituted for current verification.

## Completed inputs

Parent supplied two completed full-build/progress/43U-ok inputs. Sources,
objects, full reports and all 1027 source-object hashes were immediately
snapshotted into `../candidatebox-right-names-5af-evidence/`, with before/after
identity checks and a snapshot-manifest.json. Both linked DOL hashes were
independently read as 26116613f624061ba99c8d1a299aaa6efa85670d.

- Baseline: wii-ipl, HEAD 5af01fa8b9ed69e08d153b6ecb6aae4eb43e9efb,
  tree 895cd2c434b0d88403cd3b8a9bc601ddd2d802ae
- Candidate: wii-candidatebox-right-review,
  HEAD 376d425a7393b9dfe6a381df9d0e3a751ae06f80,
  tree 7f65657881fece903ac51173fa4802691449efe0
- Baseline source SHA256:
  318b7768c0b35d2e0f785c655aae39183a7aa61e44abb76bf2e70f7df2899f1c
- Candidate source SHA256:
  b3677b0adccaf52b31b3abb4514f4174cf14be775820e7aa84805faa0b5f9b7d
- Baseline object SHA256:
  6f9055cfa4b93bb03d9013f13e9569eff6ec36cbab02bf21af56b7b9cd87866d
- Candidate object SHA256:
  b3a52f551c2ac0f28f5580a332789e837446b5bd139512989bd2e020f09c85e4

The new verifier pins both current object and source hashes. It proves that
the candidate source is exactly the current source with the previously approved
right-pair three-line replacement. No external geometry edit is removed,
reinterpreted or excluded from sibling verification.

## Current result and complete accounting

create remains 94.59091 -> 95.99148%; unit 99.6285 -> 99.71067%.
Current exact functions 110/112, matched code 21728/24000, data 4652/4652 and link
status are unchanged. Both baseline and candidate independently compare all
110 exact functions with the original, including CalcPaneLocate_ at
435 instructions and zero differences. All 1026 other object hashes and whole
official unit records match. Only create and the text/unit fuzzy aggregates
change within the owned unit.

The exact instruction/lifetime/CFG/ABI proof is rerun on current inputs:
- Two inserted address additions; five changed existing instructions
- Same preserved branch continuations and all direct/indirect calls
- Same nonoverlapping left/right/window value lifetimes and fixed-array names
- Same frame 0x30, helper targets, stack references and save/restore bodies
- Baseline 354 -> candidate 356 instructions; target 352 and frame 0x20
- Source/target/original-DOL name bytes, address calculations and actual helper
  bodies checked, with the original raw-word relocation exclusions preserved

All 337 current symbols and 752 current relocations are rechecked. Exactly
59 private object names advance by 2, no symbol indices change, 129 later
function values advance by 8 and 333 text relocation offsets advance by 8.
Every allocated nontext byte and every raw nontext relocation payload remains
identical. Current text outside create, including the externally changed
geometry body, is byte-identical under the eight-byte shift.

Changed payloads, independently derived for the current pair:
- .text: 28576 -> 28584 bytes, 20906 positional common-byte differences
- .rela.text: 4728 bytes, 338 differing bytes
- .symtab: 5392 bytes, 134 differing bytes
- .strtab: 15521 bytes, 75 differing bytes

The current .strtab difference is 75 bytes, not the historical 70. This is
explicitly pinned and reconstructed byte-for-byte from all symbol-name
intervals; no private-label difference is ignored. All other sections,
including .comment, remain identical. Full section-header/file-offset changes
are checked. The seven bounded sibling jump-table addends are checked against
the unchanged current function/addend/instruction destinations.

Pool has 57 identical strings. The current candidate's literal advisory checks
111 functions/27 arguments with zero candidates/errors and explicitly skips
create for differing sizes. Its arguments are covered by the complete
instruction and original-array proof. The advisory used private snapshot
copies, not the parent's mutable build paths.

The parent reported an earlier historical verifier invocation while its build
was still in progress; the baseline-hash guard correctly rejected it. Parent
then completed the historical build and obtained a passing d0 proof before
rebasing. That timing error does not justify weakening either hash guard.
Parent preserves the historical successful evidence under
`validation/candidatebox-right-parent-historical-proof.log` and `.json`.

## Reproduction

From a checkout containing both verification helpers, use immutable completed
input snapshots:

    PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=../local-tools ../.venv/bin/python \
      tools/decomp-assist/verify_tiCandidateBox_right_names_5af.py \
      ../candidatebox-right-names-5af-evidence/baseline.o \
      ../candidatebox-right-names-5af-evidence/candidate.o \
      --target build/43U/obj/src/keyboard/tiCandidateBox.o \
      --runtime build/43U/src/libs/Runtime/src/runtime.o \
      --original-runtime build/43U/obj/libs/Runtime/src/runtime.o \
      --original-dol orig/43U/00000008.app \
      --evidence ../candidatebox-right-names-5af-evidence \
      --details ../candidatebox-right-names-5af-evidence/exhaustive-proof.json

GATE: current-baseline compatibility proof passes with strict create fuzzy gain,
all 110 exact functions preserved, unchanged data/link/siblings and the same
disclosed code-size/frame costs. Independent parent review remains required.
No additional compilation, production edit, parent-path mutation or remote
action was performed for this compatibility audit.
