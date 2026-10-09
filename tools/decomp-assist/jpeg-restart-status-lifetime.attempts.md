# JPEG restart scan-status lifetime investigation

Base: `aed62d8530993250fe0237e5adfd3b5a4d811020` (43U only).
Target: `TMCJPEGDEC_err_restart`, 0x814EDAC0, 460 bytes / 115 instructions.

The retained MWCC assembly remains unchanged. No inventory classification,
link setting, compiler option, or other function changed. No upstream or external
source was accessed; all target observations came from the locally split retail
object. This is not an exact-C conversion or a decompilation-completion claim.

## Prior evidence and bounded new approach

Read rx19 and the rx24 summary, then found the later `opus-ph.attempts.md` and
its preserved C. That log already tested the ordinary loop/exit/predicate forms
and reports front-end folding of the missing range-test exit branch. Its switch
candidate has 115 instructions but wrong signed comparisons and bound order.

New hypothesis: the call's real error status may naturally stay live across the
marker-scan latch. Unlike an artificial flag or dummy copy, this status already
controls whether scanning can continue and is returned on read failure. Two
structured forms tested its lifetime without changing marker-read order or the
successful restart computation:

| Form | Exact-name objdiff | Instructions |
| --- | ---: | ---: |
| Recovered ordinary-loop baseline | 95.73913% | 114/115 |
| `while (result >= 0)` scan with gated success | 91.13043% | 117/115 |
| `do` scan with error break and status latch | 92.13043% | 116/115 |

Both new forms retain a status comparison absent in the target and still fold
the upper marker-bound test. They do not justify further status-flag sweeps.
All three trial implementations were removed. No debugger, compiler-memory,
register forcing, inline assembly addition, or optimizer control was used.

## Independently proven inactive-fallback correction

One existing fallback line returned
`state->result - state->posY * state->maxX - state->posY`.
The retail function instead ends with these data accesses and operations:

- `lhz r4, 2(r31)`: posY
- `lhz r3, 0x10(r31)`: maxX
- `lwz r0, 0xc(r31)`: result
- `mullw r3, r4, r3`
- `lhz r4, 0(r31)`: posX
- `subf r0, r3, r0`
- `subf r3, r4, r0`

`TMCCJPEGDecState` in `tmc_jpeg.h` independently names those offsets. The API's
normal decode completion in `src/api/decapi.c` uses the same remaining-MCU
formula, `state->result - (curY * maxX) - curX`; its error path calls this restart
function. Therefore the last subtraction must use posX. For total=100,
maxX=10, posY=2, posX=3, the correct target result is 77; the old fallback gives 78.

Only this one inactive C line is corrected. It does not alter the active MWCC
implementation or make the remaining C fallback exact.

## Validation

Validation results are recorded below after the final build.

- Final `ninja build/43U/ok`: passed (1,031 build steps); immediate repeat:
  no work to do
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `tools/test_workflow_guards.py`: all 23 tests passed
- Fresh full objdiff report: 1,028 units, preserved in the external evidence
  directory as `restored-full-report.json`
- Complete compiled `jdec_main.o` is byte-identical to the retained-production
  baseline object, including all ELF metadata and relocations
- Original target versus final built `.text`: all 5,604 raw bytes identical
- Original target versus final built `.rodata`: all 256 raw bytes identical
- All 13 unit functions have identical instructions and resolved relocations
- Restart target: all 460 raw bytes, 115 instructions, and normalized
  relocation records identical; this remains the retained assembly
- String pool comparison: identical (zero printable strings in `.data`)
- Target instruction sequence checked directly; 10,004 boundary/random
  arithmetic states agree with the corrected unsigned return expression
- `git diff --check`: passed

Evidence, including trial sources/objects, reports, raw function bytes,
relocation records, disassembly, sibling audit, build log and test log, is kept
outside the repository in the task's `jpeg-restart-evidence` directory. The
one-line fallback correction is the only production-source change.

## Rebase validation

Rebased the minimal correction onto `c3dd1c08c04a38975b63dded77a7aef6fce385f3`.
The final leaf passes `43U/ok`, retains the expected DOL SHA1, and passes all 23
guard tests. Its freshly generated full report has identical global measures
and all 1,028 unit records to the freshly generated report on that main commit.
The complete `jdec_main.o` remains byte-identical to the production baseline;
the raw target, relocation, sibling and arithmetic audits pass again.

## Final integration-base validation

Rebased again onto `f2006bdd15fd1a6bed189aa53924fdfc7e0e841f` after the
independent hasChannel conversion and scene cleanup. Full `43U/ok`, expected DOL
SHA1, 23 guards, byte-identical `jdec_main.o`, and all focused audits pass again.
The fresh full report's global measures and all 1,028 unit records exactly match
the fresh report on this main commit. Current inventory is 165 functions,
167 bodies/blocks, 162 ORIGINAL and 3 PLACEHOLDER; this leaf changes none of
those counts. The inventory's expected failure still lists err_restart,
CNTCACHEClear and System::warning_run.
