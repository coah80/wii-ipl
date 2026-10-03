# NWC24InitDlTask writable-helper recovery

Base: bd5efc9c5628fb570352705177ee55f694f6401f.
Exactly one authorized source form; no alternate trials or compiler changes.

## Change and provenance

Move the existing IsDlTaskWritableGroup and ValidateWritableDlTask definitions,
byte-for-byte, immediately before NWC24InitDlTask. Change only Init's final
ValidateDlTask(dlTask, TRUE) call to ValidateWritableDlTask(dlTask). All existing
u32 identity fields, helper bodies, other callers and shared headers remain.

ult20b.attempts.md:158 recorded this helper-use idea at 99.201385, but the exact
rejected source and its placement were unavailable. This trial explicitly
recovers forward visibility through the unchanged inline definitions. It does
not claim byte-exact recovery of the historical patch.

## Actual compile and official results

An independent baseline build directory was copied before editing. A forced
normal baseline MWCC compile reproduced all 1,027 object hashes and the entire
official report. Required cached-wrapper environment:
WIBO_SJIS_MISSING_IMPORTS=1; no downloads, flag changes or tool modifications.

- Init: 98.923615 -> 99.201385, 144/144 instructions, 576 bytes, frame 0x60
- Positional target differences: 31 -> 23; this is not an exact match
- Unit: 29/30 exact; code 11920/12496 and data 80/80 unchanged
- Unit fuzzy: 99.950386 -> 99.96319
- All 1,026 other source objects and all 1,027 originals unchanged
- Full 43U build, ok, progress/report and original DOL SHA1 pass
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d
- Pool: identical three strings; literal audit: 30 functions, seven arguments,
  no skips, errors or candidates

## Actual instruction, CFG, data and ABI evidence

Only ten instruction words change, all register operands. Opcode sequence,
branch destinations, call identities, memory widths, offsets, ordered field
accesses and epilogue are unchanged. All later functions remain byte-identical;
all 29 exact siblings independently have diffs 0.

All 144 candidate instructions agree with the original after a diagnostic
r28/r29 lifetime swap at indices 5..72. Those initial live ranges finish at the
identity stores; instructions 73..143 already agree without normalization.
No source/binary/scorer normalization was applied. The unchanged save/restore
range includes both registers. Verified 128 original non-relocated words and
all 12 linked branch destinations against the local original DOL.

All allocated non-text data, relocation bytes, section extents and symbol rows
are unchanged. This unit has no unwind sections. Three compiler-generated
local literal names alone change in .strtab; .symtab bytes, bindings, offsets,
sizes and relocation indices stay identical:

- @4280 -> @4286, .data offset 28, size 12
- @4414 -> @4420, .sdata offset 8, size 8
- @4415 -> @4421, .data offset 40, size 9

## Source contract and bounded model

With write=TRUE, old and new helpers preserve cached-header acquisition,
null/error precedence, tool-open, owner, group, sentinel and capacity checks.
The actual group field and NWC24GetGroupId return are u16; the existing u32
helper argument loses no information. No alias, volatility or layout promise
is introduced.

The getters are not assumed pure. NWC24GetGroupId can invoke NAND APIs and
write a workspace buffer. Its conditional call remains after flags/group
snapshots and before task-ID/header-capacity reads. The same cached header is
held across that call. NWC24GetAppId can invoke OS/DVD getters; its call and
app-field snapshot ordering also remain. The three actual getter bodies are
instruction-exact against their originals.

A separate Python contract model checks 126,000 bounded cases, comparing
returns, ordered read/call traces and state effects, including getter-side
mutations. All agree. This is a supplementary contract model, not PPC or
hardware execution; actual instruction/CFG proof is reported separately above.

## Local verification evidence

/workspace/scratch/0128b1ed02cc/nwc24-writable-recovery-evidence/result.md
contains the full index and limitations. audit.py verifies ELF/DOL/accounting
and the bounded model. verify-local.sh provides a forced normal rebuild,
full-report/hash checks and full 43U/ok verification for the candidate leaf.

Source SHA256: 1d0e24ef3316e609dc6b17cdd96027633957232e4983af8b80fa2e51fb4c7d56
Object SHA256: cd86a99d35754fbe35318eef1b981513533f4d8a0b2a88d713deac614a7b84b0

Retained for independent parent review. No publication or integration claim.
