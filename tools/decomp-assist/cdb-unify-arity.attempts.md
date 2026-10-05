# Unify CDB helper signatures

Base: f8957ca95be0ca4b35a281fa9a5d59f7f1787a41.
Branch: agent/fix/cdb-unify-arity.
Scope: CDBDate.h, CDBConv.h, CDBConv.c, CDBDatabase.c.

## Reason and consumer audit

PR #1167 introduced shorter declarations visible only to CDBDatabase.c while
CDBConv.c retained the old, longer definitions. Unused trailing machine
arguments do not make these incompatible C function types valid.

Unify declarations and definitions around the arguments used by the target:
DayBegin/DayEnd take three ints, MonthBegin/MonthEnd two, YearBegin/YearEnd
one, and CDBConvDirStrToCDBDate five character pointers. Remove the
CDB_DATABASE_IMPLEMENTATION guard. MonthEnd's former day parameter becomes
a local assigned in every switch arm, including default, before any read.
All seven external names, linkage, return types, and linked bytes are retained.

The complete original 43U object relocation audit found 13 call relocations,
all in CDBDatabase: one directory conversion and two calls to each of the six
date boundary helpers. The only additional 12 relocations were MonthEnd's
internal switch destinations. Decoding direct branches throughout the original
DOL confirmed the same 13 calls. No literal entry-address references, dynamic
ELF sections, relevant export list, or REL/RSO modules were found. These checks
cover observed 43U consumers, not hypothetical external fixed-address callers.
None of the removed trailing arguments is read by the helper implementations.

## One bounded source attempt

Applied the four-file signature correction directly, with no code-generation
tuning, new assembly, volatile casts, dummy arguments, or unrelated source edits.
Configured only 43U with the existing local compiler, binutils and wrapper paths.
Ran the complete default build, then progress, report and build/43U/ok targets.

Fresh results:

- CDBConv: 39/39 original functions, 4676/4676 code bytes, 232/232 data bytes;
  matched and linked code/data all 100%.
- CDBDatabase: 33/33 original functions, 12152/12152 code bytes, 312/312 data
  bytes; matched and linked code/data all 100%.
- All 72 exact-name original functions have identical raw instruction bytes,
  position-normalized Capstone instructions and normalized relocation targets.
- Every allocated section and compiled function body is identical to the
  pre-edit source-object baseline. Existing line-number-derived FORCEACTIVE
  helper names move from 132/313 to 134/315; their bodies do not change.
- String pools: CDBConv 5/5, CDBDatabase 7/7, both identical.
- Literal audit: 31 arguments, 72 functions, zero skipped functions, candidates
  or errors.
- MonthEnd jump table: 12/12 destinations identical.
- All 1027 report units retain identical measures and section results versus
  the preserved baseline; global measures are identical.
- Full build and build/43U/ok pass.
- Original and rebuilt DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
- git diff --check passes.

Global completion was also checked. It still fails the pre-existing incomplete
project totals (2778928/2995176 matched code, 2312404/2995176 linked code,
1832576/1832684 matched data, 1545364/1832684 linked data). This correction
makes no new decompilation or completion-percentage claim.

GATE PASS: bounded signature correction; no exact, data, function or link
regression. Independent parent verification is still required before landing.

Transient validation evidence is in build/cdb-arity-review/: the preserved
baseline report/objects, full-build.log, final-gates.log, check_objects.py,
object-gates.log, status.json, status.md and completion.log.
