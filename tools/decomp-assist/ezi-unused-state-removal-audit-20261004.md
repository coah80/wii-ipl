# Remove unused eZiText state

Base: `4aaede9980460ce6dd616cbe2a90458c99f69363` (43U only).
This is a source-quality correction, not a matching gain. The entire source
change deletes five lines: Alpha's unused `workspace` declaration/assignment
and Prepare's unused `hasComponent` declaration/two assignments. All other
PR1152/1153 improvements, the legitimate Korean changes, and PR1155 remain.

Neither removed local has a consumer or an escaped address. Direct examination
of the SHA1-verified original DOL confirms Alpha's store at function +0x15C
to stack 0x20 and Prepare's stores at +0x48/+0x124 to stack 0xF, with no direct
loads from those slots. That establishes machine stores, not genuine source
provenance for invented write-only locals. No consumers, padding, flags,
assembly, shared-header changes, symbol edits, or extra tuning were added.

## Measured rollback

- Alpha function fuzzy: 95.648506% -> 95.45388%; unit fuzzy:
  96.82958% -> 96.687775%; matched data: 564/564 -> 408/564.
  Instructions: 3946 -> 3945 (retail 3946); size: 0x3DA8 -> 0x3DA4.
- Prepare function/unit fuzzy: 96.99468% -> 96.72872%; matched data:
  68/68 -> 8/68. Instructions: 940 -> 936 (retail 940);
  size: 0xEB0 -> 0xEA0.
- Both 48-byte jump-table sections cease matching. Alpha's 108-byte
  extabindex scores 99.07407%; Prepare's 12-byte index scores 91.66667%.
  Objdiff counts those sections as unmatched, losing 216 matched data bytes.
  Their extab sections remain exact; Alpha's rodata remains exact.
- Global fuzzy: 99.77642% -> 99.775055%; matched data:
  1,832,576 -> 1,832,360 / 1,832,684 (99.9941% -> 99.98232%).
  Matched code stays 2,773,328 / 2,995,176; linked code stays 2,282,392;
  matched functions stay 12,424 / 12,563; linked data stays 1,542,216.

## Validation

Default `WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja` rebuilt both owned
objects and regenerated the report. Explicit `build/43U/ok`, progress/report,
and `git diff --check` passed. DOL SHA1 remains
`26116613f624061ba99c8d1a299aaa6efa85670d`; both units remain NonMatching,
so the hash does not establish their compiled-code equivalence.

The full comparison covers all 1,027 units and all function names. Only these
two engines/units changed; no exact-code, exact-function, or link count fell.
Every previously exact Alpha sibling (11) independently retains equal size
and zero relocation-aware instruction differences. Prepare has no exact sibling.
Both empty string pools remain identical. The literal-reference advisory
reported zero candidates/errors across 11 functions, but skipped the two
engines because their sizes now differ; this is not a whole-engine literal proof.
The completion checker correctly fails because the project remains incomplete.

Compact baseline/candidate reports, full comparison, object hashes and build,
pool, literal, status and completion logs are preserved under the local
`validation/ezi-unused-state/` directory beside the worktrees. No clean rebuild
of every unchanged object was performed in this space-constrained leaf.
Independent parent validation is still required. The ordinary no-regression
matching gate does not pass; the rollback above is explicit and intentional.
