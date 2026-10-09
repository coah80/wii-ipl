# Strict completion section coverage

Base: c3dd1c08c04a38975b63dded77a7aef6fce385f3 (rebased from aed62d8530993250fe0237e5adfd3b5a4d811020).
No source or build inputs changed by this candidate.

Schema evidence: locally available objdiff source at c02eb31dbbf9dd33577aead353bb2db62933b2af,
`objdiff-cli/src/cmd/report.rs:250-325`, emits full section sizes, sums Data/Bss
section sizes into total_data, but sums only retained function symbols into
total_code. Hidden, ignored, zero-size and previously seen global/weak symbols
are excluded from code totals. `objdiff-core/protos/report.proto` declares
ReportItem.size as proto3 uint64; a missing JSON scalar size represents zero.
43U section classification comes from `config/43U/splits.txt`; `.ctors$10`
is a constructor subsection present in the generated report.

Consequently section data bytes must equal total_data; section code bytes must
cover total_code, not necessarily equal it. In the current report msghndlr has
28 .text bytes but only 16 counted code bytes. No unit-specific exception is
needed. Unknown/duplicate section names and malformed sizes fail closed.
A structural check cannot authenticate a report against deliberately forged
sizes/names; original report generation and the independent DOL gate remain
required. Truly zero-byte records contribute no measurable coverage.

Validation repeated after rebasing, using an unchanged copy of the parent-generated
c3dd1c08 main 43U report and DOL, without building main:

- All 23 preexisting guards pass; 12 new guards bring the total to 35, no skips.
- Actual report and main DOL: DECOMPLETE_OK.
- All section lists emptied only in memory: 1,695 coverage failures.
- Each of the 2,676 section records deleted individually in memory: rejected.
- Data-only and protobuf zero-sized sections accepted; deduplicated code-size
  slack accepted; code/data deficits, excess data and invalid records rejected.
- Strict combined report/DOL plus live inventory: exit 1, as required.
  Inventory reports 166 functions / 168 bodies, 162 ORIGINAL and 4 PLACEHOLDER:
  TMCJPEGDEC_err_restart, CNTCACHEClear, Manager::hasChannel, System::warning_run.
- CI inventory command is conditional on workflow_dispatch require_complete;
  ordinary progress builds do not acquire a source-completion requirement.
