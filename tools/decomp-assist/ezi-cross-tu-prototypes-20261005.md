# eZiText cross-translation-unit prototype correction

Base: `55ae09acca8d719980432844681f95ca4337fd7c` (fork PR #1224).
Scope: 43U only; a fresh isolated `agent/fix/ezi-cross-tu-prototypes` leaf.

## Source audit and correction

The complete source/header search found one caller translation unit for each
of the five corrected contracts:

- `Zi8Punctuation`: the caller now declares `ZiCandidateOptions*`. Its complete
  anonymous struct definition is identical, member-for-member, to the existing
  definition in `Zi8punct.c`; the types are compatible across translation units.
- `Zi8SecMatchChar`: the record parameter is `ziU8*`, matching `zi8match.c`.
- `Zi8SecMatchComp`: the component and dictionary parameters are `ziU8*`.
- `Zi8MatchPhonetic`: the phonetics parameter is `ziU8*`; the return typedef is
  spelled `ziBool` like the definition (`ziBool` and `ziU8` already denote the
  same unsigned-character type).
- `Zi8GetKoreanCandidates`: the declaration now matches both existing parameter
  types: `ziU8*` and `struct __zi8_work_data_s*`. Its only use of the byte pointer
  is a null check followed by reading the first byte. The sole caller now passes
  `&options->countOnly`, that actual first `ziU8` member, instead of relying on
  a mismatched `void*` declaration to pass the whole options struct. The caller
  already dereferences options before this call, so this adds no null case.

`ZI_NEED_WORK` expands to `ziPtr`, so the other four work parameters remain
unchanged and compatible. No new struct, opaque type, state, flag, cast, pragma,
assembly, or build-setting change was needed. No unresolved contract remains
among these five functions. Other existing APIs are outside this focused leaf.

## Verification

A fresh baseline was configured and fully built in this leaf before editing.
The final focused objects and full default build succeeded, followed by the
explicit `build/43U/ok` target. The original DOL and tools stayed local.

- Full objdiff JSON is unchanged: 1,027 units, 12,563 functions.
- Every source object is unchanged against the baseline: 2,717 allocated
  sections and 117,551 relocation records, retaining section types, flags,
  sizes, alignments, bytes, and resolved symbol metadata.
- Exact functions before/after: `zi8getc2` 17/17, `zi8cgetc` 7/7,
  `zi8match` 10/10, `Zi8punct` 1/1, `zikorean` 3/3.
- `zi8cgetc::zi8InternalGetZH` remains the preexisting 98.336266% nonmatch;
  its whole object is unchanged. This correction is not a matching gain.
- The four fully exact units retain 100% code, data, functions, and linking.
  Their allocated bytes and canonical relocations match the original objects;
  `zi8getc2` retains the original four-byte zero alignment tail in `.sdata2`.
- Pools are identical for all five units (zero printable narrow `.data`
  strings); complete section comparisons supply the stronger data check.
- Untouched `ctxdiff.py`: 35 exact functions have raw `diffs 0`. Three exact
  functions retain eight raw jump-table alias-name differences:
  `Zi8GetCandidatesOrCount` (4), `Zi8GetKoreanCandidates` (2), and
  `Zi8MatchKoreanSequence` (2). Each differing reference was independently
  proven to have the same relocation kind, section-relative target, and
  byte-identical entire referent section. Resolved instruction differences
  are zero, with equal instruction counts. No arbitrary label normalization
  or object modification was used.
- `decomp_status.py` succeeds. `check_decomp_complete.py` still fails for the
  repository's existing incomplete work; its output is byte-identical to
  baseline. No full-decompilation-completion claim is made.
- `git diff --check` and the leaf worktree checker pass.

Local evidence is in the sibling `wii-ezi-prototype-evidence/` directory:
`audit.py`, `audit.txt`, `ctx_audit.py`, `pools-ctxdiff.txt`, full baseline/final
build logs, baseline report/objects, both completion-check outputs, status,
and the complete definitions/callers search. The audit scripts use the existing
`wii-toolchain-venv`; ctx diagnostics use `PYTHONPATH=../local-tools`.

GATE: PASS — focused contracts compatible; generated code/data/relocations and
full report unchanged; 43U full build/ok pass; DOL SHA1
`26116613f624061ba99c8d1a299aaa6efa85670d`.

Local handoff only: no push, PR, merge, upstream contact, or binary upload.
