# sol-audit2 carrier audit

Worktree `data-d12`, branch `agent/w1009/carriers2`, baseline `ebf00fbc`.
Initial full 43U build passed with DOL SHA1
`26116613f624061ba99c8d1a299aaa6efa85670d`.
All four pools are identical. Starting source objects and sources are saved in
`/tmp/sol-audit2-baseline` for whole-object comparisons.

Read sol-common.md, brief-v2.md, all levers, and the first audit at `7b2e1bfa`.
Earlier FAT12, Board, and PUD logs confirm the first audit's blocked cases.
This round investigates actual import metadata, parameter spills, allocator
creation order, and real interrupt-lock interfaces. It does not repeat the
first audit's flat declaration permutations, sector helpers, named mask/call
values, unread PUD local, or ordinary guard experiments.

Every retained edit must keep the requested function exact, preserve every
other function and allocated section, and pass the final quick gate with zero
drops and the target DOL SHA1. Commit each fixed source separately.

## Trials

| Trial | Source change or evidence | Result |
| --- | --- | --- |
| wad-shared-import-descriptor | Reuse the boot routine's existing 0x28-byte parsed WAD section descriptor, exposing its header fields and giving both routines the common WADImportParts type | Initial focused checks used a stale object after a masked build failure; corrected and freshly verified below |

## WAD descriptor evidence

The anonymous `parts` is parsed WAD metadata, not unrelated scalar state.
Its four size/address pairs describe the certificate chain, CRLs, ticket, and
TMD, in precisely the package order declared by WADHeader. WAD_815C2F44 writes
the format subtype in its first word. ES_ImportTicket and ES_ImportTitleInit
consume these same parsed sections. The contiguous memset clears exactly this
40-byte descriptor at SP+0x40.

WADImportDVDForBS already uses WADBootImportParts with the identical extent,
identical four section pairs, and two header words. Generalize that existing
type to WADImportParts, expose the non-boot routine's existing header fields,
and use it in both import routines. This reconstructs a shared internal type;
it does not claim that WADImportParts is an original SDK identifier. No new
field, padding, alignment requirement, helper, or runtime operation is added.

Read-only GitHub searches for WADImportDVDExForBS, WADImportBootDVD,
WADImportDVD, and _WADUnpack found only the old SDK's public interface, not an
implementation. That header confirms WADHeader/WADHeader1's section order and
the content-mask version distinction; it has no public 40-byte parsed type.
Source: https://github.com/galaxymaster2007/THPConv/blob/e7f2a17eeff43bc6b822a01af66ce670822ab77b/include/private/wad.h

The initial focused command failed to compile because one boot import
comparison still used parts.headerInfo[0]. It continued into object checks
and compared the stale pre-edit object. Those first WAD checks are invalid;
the corrected fresh build and final gate below are authoritative.

## Further compiled trials

These rows record new source shapes and diagnostics. Reproduction of the flat
FAT12 source for a fresh debugger capture is baseline evidence, not another
declaration-order trial.

| Trial | Source change or evidence | Result |
| --- | --- | --- |
| pud-const-void-all | Const workspace alias initialized at declaration and used for all actual workspace accesses | {"function": "Zi8MatchPUDdata_ZHS", "insns": [385, 354], "diffs": 373, "changed_sections": [".text", "extab", "extabindex"], "relocations_identical": false} |
| pud-const-typed-all | Const workspace alias initialized at declaration and used for all actual workspace accesses | {"function": "Zi8MatchPUDdata_ZHS", "insns": [385, 354], "diffs": 373, "changed_sections": [".text", "extab", "extabindex"], "relocations_identical": false} |
| pud-const-typed-check | Const workspace alias initialized at declaration and used for check actual workspace accesses | {"function": "Zi8MatchPUDdata_ZHS", "insns": [368, 354], "diffs": 357, "changed_sections": [".text", "extab", "extabindex"], "relocations_identical": false} |
| fat12-word-helper-0 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_vol', 'offset', 'p_value', 'p_page') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-1 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_vol', 'offset', 'p_page', 'p_value') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-2 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_vol', 'p_value', 'offset', 'p_page') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-3 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_vol', 'p_value', 'p_page', 'offset') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-4 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_vol', 'p_page', 'offset', 'p_value') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-5 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_vol', 'p_page', 'p_value', 'offset') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-6 | Real two-byte buffered FAT read helper, returns status; parameter order ('offset', 'p_vol', 'p_value', 'p_page') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-7 | Real two-byte buffered FAT read helper, returns status; parameter order ('offset', 'p_vol', 'p_page', 'p_value') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-8 | Real two-byte buffered FAT read helper, returns status; parameter order ('offset', 'p_value', 'p_vol', 'p_page') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-9 | Real two-byte buffered FAT read helper, returns status; parameter order ('offset', 'p_value', 'p_page', 'p_vol') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-10 | Real two-byte buffered FAT read helper, returns status; parameter order ('offset', 'p_page', 'p_vol', 'p_value') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-11 | Real two-byte buffered FAT read helper, returns status; parameter order ('offset', 'p_page', 'p_value', 'p_vol') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-12 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_value', 'p_vol', 'offset', 'p_page') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-13 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_value', 'p_vol', 'p_page', 'offset') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-14 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_value', 'offset', 'p_vol', 'p_page') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-15 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_value', 'offset', 'p_page', 'p_vol') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-16 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_value', 'p_page', 'p_vol', 'offset') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-17 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_value', 'p_page', 'offset', 'p_vol') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-18 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_page', 'p_vol', 'offset', 'p_value') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-19 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_page', 'p_vol', 'p_value', 'offset') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-20 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_page', 'offset', 'p_vol', 'p_value') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-21 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_page', 'offset', 'p_value', 'p_vol') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-22 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_page', 'p_value', 'p_vol', 'offset') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-23 | Real two-byte buffered FAT read helper, returns status; parameter order ('p_page', 'p_value', 'offset', 'p_vol') | 155/155 instructions, diffs 11; changed sections ['.text'] |
| fat12-word-helper-local-order | Swap the real helper sector/current FAT declaration order after moving byte offset into its argument | 155/155 instructions, diffs 0; baseline sections [], relocations identical True |
| board-iro0-diagnostic | Diagnostic compiler pass boundary on ordinary locals; removed after measurement | 283/283 instructions, diffs 52 |
| board-iro1-diagnostic | Diagnostic compiler pass boundary on ordinary locals; removed after measurement | 283/283 instructions, diffs 52 |
| board-opt1-diagnostic | Diagnostic compiler pass boundary on ordinary locals; removed after measurement | 287/283 instructions, diffs 266 |
| board-opt2-diagnostic | Diagnostic compiler pass boundary on ordinary locals; removed after measurement | 283/283 instructions, diffs 68 |
| board-opt3-diagnostic | Diagnostic compiler pass boundary on ordinary locals; removed after measurement | 283/283 instructions, diffs 52 |

## FAT12 creation-order evidence

The fresh flat capture reproduces all 84 virtual-register assignments.
Offset r37 takes r28, while the error's compiler copies r41/r42 take r31.
The constrained regsim search permits only sector/current_fat/err/offset/result
and reaches 2 of the 4 requested colors. The stock regsim search can report
4/4 only by permuting parameters and compiler-created @ temporaries; that is
not a source declaration-order solution.

ReadFAT12WordWithBuf is a real operation: it reads the two-byte word at a FAT
byte offset, flushes/reloads sectors when needed, handles the boundary between
sectors and callback retries, and returns the read status. The public entry
routine computes the cluster's byte offset and extracts its even/odd nibble.
Its p_value parameter is the operation's genuine output, not a local-hoisting
out-parameter.

Moving the offset computation into that call's argument creates offset as
virtual r49, colored first at r31. The helper's sector and current_fat locals
initially take r29/r30, giving 11 register differences. Declare current_fat
before sector: their virtual identities reverse, leaving sector r46=r30 and
current_fat r45=r29. Error r37 takes r28. Parameter-order changes did not
matter. The exact capture reproduces all 84 assignments and its complete
unit.o equals the independent Ninja object byte for byte. The requested
function has 155/155 instructions and diffs 0; every allocated section and
relocation in the unit is baseline-identical.

Captures: /tmp/sol-audit2-fat12-carrier, /tmp/sol-audit2-fat12-flat,
/tmp/sol-audit2-fat12-word, /tmp/sol-audit2-fat12-exact.
The private mwdbg launcher changes only the output-directory restriction so
these captures stay under /tmp; the compiler flags and debugger are unchanged.
| pud-incoming-generic-working-generic | Incoming work parameter copied to a live named working pointer | 385/354 instructions, diffs 373 |
| pud-incoming-generic-working-typed | Incoming work parameter copied to a live named working pointer | 385/354 instructions, diffs 373 |
| pud-incoming-typed-working-typed | Incoming work parameter copied to a live named working pointer | 385/354 instructions, diffs 373 |
| pud-availability-inline-expression | Real PUD availability test moved across an inline parameter boundary | 345/354 instructions, diffs 336 |
| pud-availability-inline-branches | Real PUD availability test moved across an inline parameter boundary | 345/354 instructions, diffs 336 |
| pud-availability-inline-local | Real PUD availability test moved across an inline parameter boundary | 345/354 instructions, diffs 336 |

## PUD remains unresolved

The target loads the tenth incoming parameter from SP+0x6C into r31, then
stores r31 to SP+0x24 at function offset 0x3C. That word has no load, overlapping
read, or address escape. The only local address passed to an ordinary callee
is the halfword at SP+0x0E for Zi8ChangeCharCase. Incoming spelling arguments
are at SP+8/+0x0C; the save/restore area starts above SP+0x28. Neither region
can explain the pointer copy.

The actual unit uses GC/3.0a5 with -inline off and -opt off. ZI_NEED_WORK adds
one ordinary ziPtr parameter; ZI_WORK casts that parameter to the work type.
The work/error/conversion headers contain no address-taking or debug-only work
setup macro. Read-only searches for Zi8MatchPUDdata found no other indexed
implementation outside this fork and the excluded upstream.

Nine new compiled trials investigated const working aliases, renaming the
incoming parameter and copying it to a live typed/generic working pointer,
and a real inline PUD-availability operation. Live aliases add actual stack
reads: the full aliases produce 385/354 instructions, and the scoped const
check produces 368/354. The availability helper stays out of line under the
actual flags: the disassembly has bl Zi8PudAvailable, 345/354 instructions, and
an additional function. It supplies no inlined parameter spill.

A debug-only use remains a hypothesis, not recovered source evidence. Adding
an invented assertion or an unread local solely to retain this store would
repeat the first audit's rejected solution. The original source and object are
unchanged, still 354/354 instructions and diffs 0 with their carrier present.
An honest carrier removal still needs original work-setup/debug-interface
source or equivalent evidence explaining the unused copy.

## Board remains unresolved

The target stores the three OSDisableInterrupts results to SP+0x14, SP+0x10,
and SP+8, and loads them into r3 only when restoring interrupts. These words
are never passed by pointer. Every remaining stack pointer argument addresses
actual record metadata or dataSize. The frame is 0xA0, with _savegpr_25.

The SDK header declares OSDisableInterrupts() and OSRestoreInterrupts(int).
Their assembly definitions only read/write MSR and return the previous EE bit;
neither saves a context, longjmps, or consumes a pointer. ObjList::getNextFree
passes &mFreeObjs and a null object, while Manager::unused uses its own mutex.
The existing utility/NW4R interrupt guards also store/restore the level by
value. The earlier guard captures already prove scalar promotion, so this
round did not repeat those source trials.

Five new pass-boundary diagnostics on ordinary locals tested IRO 0/1 and
optimization levels 1/2/3. IRO 0/1 and level 3 retain 283 instructions with
52 differences; levels 1 and 2 give 287/283 with 266 differences and 283/283
with 68 differences, respectively. The optimization-level-3 diagnostic still uses
saved registers and the 0x90 frame. All diagnostics exist only under /tmp.
No pragma, volatile declaration, manufactured pointer escape, or replacement
carrier is retained.

The earlier volatile diagnostic is already exact but explicitly rejected;
these single stores/loads around calls do not prove volatile source. No
pointer-taking lock interface or setjmp-like call was found to justify the
three required memory homes. The original source and entire object remain
unchanged: 283/283 instructions, diffs 0. Recovering that source storage cause
is the remaining blocker; this round does not claim the carrier is removed.

## Pre-gate verification

The initial pre-gate WAD check was stale, as the gate correction below
records. The FAT12 and unchanged PUD/Board comparisons were fresh. The
unresolved PUD and Board sources are unmodified. Both retained source files
are committed separately. origin/main advanced to e6837211 in the unrelated
cardSequence unit; this worker remains on its assigned branch and baseline.

## Gate correction

The first quick gate failed the full build: WADImportDVDForBS retained one
parts.headerInfo[0] comparison after the descriptor rename. The focused build
had already reported this error, but its shell continued to odiff/pool checks
and returned their success status, hiding the failed compilation. Their WAD
object evidence was stale and is explicitly invalidated above.

Change that comparison to parts.type. Run the focused build with fail-fast
shell behavior, then compare the fresh object. It has 263/263 instructions,
diffs 0, an identical pool, and every allocated section/relocation identical
to the baseline. The earlier full gate's identical DOL was an old artifact;
the final repeated gate below verifies the corrected source through the link.

## Final verified result

Retained fixes: shared parsed WAD import descriptor and the FAT12 word reader.
PUD and Board remain unresolved and unmodified. Source commits are 12100dc0,
6f051619, and da91a4fe; da91a4fe completes the WAD member rename and supersedes
its initial stale verification. Every final source object preserves all
baseline allocated sections and relocations.

| Unit | Exact functions before -> after | Final function instructions / differences | Result |
| --- | --- | --- | --- |
| libs/RVL_SDK/src/wad/wad | 40/40 -> 40/40 | 263/263, diffs 0 | Descriptor reconstructed |
| libs/RVL_SDK/src/fa/pf_fat12 | 4/4 -> 4/4 | 155/155, diffs 0 | Carrier removed |
| libs/RVLMiddleware/eZiText/src/clib/zi8pud2 | 7/7 -> 7/7 | 354/354, diffs 0 | Carrier unchanged; blocker above |
| src/scene/board/iplBoard | 94/94 -> 94/94 | 283/283, diffs 0 | Carrier unchanged; blocker above |

The final requested quick gate passes on both changed units:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
wad: pool IDENTICAL; objdiff 40/40; instruction-exact 40/40
wad: code 24500/24500; data 528/528; every section 100%; linked code 24500
pf_fat12: pool IDENTICAL; objdiff 4/4; instruction-exact 4/4
pf_fat12: code 2164/2164; .text 100%; linked code 2164
regressions vs baseline: 0
forbidden patterns added: 0
readability warnings: 0
GATE PASS
```

Full gate output: /tmp/sol-audit2-gate-final.log.
This is an integrity cleanup of two carriers, not a new function match or a
claim that the remaining two carriers have been resolved.
