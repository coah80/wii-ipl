# sol-z1 UpdateThread integrity cleanup

Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d10`, branch `agent/w1009/data-d10-c`, base `c723136f`. Own `src/BS2/BS2Update.c` and this log. Read sol-common, brief-v2, all levers, local AGENTS.md, effort policy, earlier UpdateThread notes, both sol-x8 rounds and sol-y3 log recovered with `git show 4925fde2:tools/decomp-assist/sol-y3.attempts.md`. Applied unslop and writing-for-agents. Fetched only the fork under `/tmp/wii-git.lock`. No push, PR, merge, rebase, subagents, shared header changes or other-worktree writes.

The explicit task authorizes committing this integrity cleanup even without an exact UpdateThread match. It overrides brief-v2's default instruction to restore nonexact source. The requested final gate is `gate.py src/BS2/BS2Update --quick`.

## Prior evidence

Do not repeat the logged restrict/const pointers, flag helpers, primitive/enum types, volatile-bank diagnostics, entry wrappers, whole-table seat indexing, bitfield views, cursors, source order variants or optimizer sweeps. sol-x8 and sol-y3 both already flattened the scratch carrier in their saved best. Neither source candidate was landed; main still has the carrier. The saved sol-y3 diff applies cleanly and already contains the required ordinary locals. This round independently verifies that order and commits the valid cleanup.

## Compiled trials

1. Fresh rebuild of HEAD: UpdateThread 335/913 differing, source 911 versus target 913 instructions, size 0xe3c versus 0xe44. No inherited source object used as measurement.
2. Apply sol-y3.BS2Update.diff: 6/913, equal 913 instructions and size 0xe44, pools 55/55 identical. All scratch members are separate ordinary locals. The three scheduling swaps are unchanged after cleanup.
3. Correct saved titleRegion indentation and remove extra blank lines: 6/913, 913/913.
4. Restore original static linkage for rc, VersionIOS, VersionMEM2, VersionES and ConsoleType: 6/913, 913/913. All other nine functions instruction exact. Keep this narrower change; the saved external-linkage edits were unnecessary.
5. Restore original external linkage of getSuffix: 6/913, 913/913. Keep original linkage; changing it was unnecessary.
6. Read a named ordinary attributes scalar after the diagnostic reports and before clearing Flags0, then test that value: 7/913, 913/913. Address add moves before the store, but load and bit test also precede it. Reject and restore trial 5.

No declaration permutation is needed: the supplied ordinary declarations already reproduce every target stack access. No carrier, dummy object, padding, helper that merely hoists locals, added pragma or assembly is retained. Configure remains NonMatching because UpdateThread is not exact.

## Target stack layout

Source declaration order: freeChannels, freeBlocks, freeInodes, ticketCount, productArea[8], titleId, updatePath[32], seatPath[32], DVDFileInfo file. MWCC assigns these independent objects the target offsets without a wrapper.

| Object | r1 offset | Size | Target use |
| --- | --- | --- | --- |
| freeChannels | 0x08 | 4 | Zero store, SCGetFreeChannelAppCount argument, channel limit load |
| freeBlocks | 0x0c | 4 | Zero store, NAND area output, available byte limit load |
| freeInodes | 0x10 | 4 | Zero store, NAND area output, inode limit load |
| ticketCount | 0x14 | 4 | ES_GetTicketViews output and count load |
| productArea | 0x18 | 8 | SCGetProductAreaString output and both strcat sources |
| titleId | 0x20 | 8 | ES_GetTitleId output; low word loaded at 0x24 |
| updatePath | 0x28 | 32 | Update path construction, entry lookup, report and DVDOpen |
| seatPath | 0x48 | 32 | Seat path construction, entry lookup, report and DVDOpen |
| file | 0x68 | 0x3c | DVD open/read arguments; length loaded at 0x9c |

Frame is 0xf0. LR slot is 0xf4. _savegpr_14/_restgpr_14 use r11 = r1 + 0xf0. The disassembly audit below records every explicit r1 access, including frame and LR operations.

## Remaining differences

913/913 instructions, equal 0xe44 size. Differences 442/443 exchange Flags0 clear and seat attribute address add. Differences 545/546 exchange constant-one load and selected seat address add. Differences 549/550 exchange selected output offset increment and seat size load. Registers and operands match otherwise. Ordinary stack objects do not remove these previously documented seat-memory scheduling dependencies.

## Final validation

Requested quick gate passed on the retained source. Full 43U build passed; DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`. Pools are identical. UpdateThread is 99.33625% fuzzy with 6 differences, not exact; unit remains 9/10 exact functions, code 400/4052, data 10488/10488, linked code 0. All data sections are 100%. Global regressions, forbidden additions and readability warnings are zero. Fresh `ninja progress build/43U/report.json` and ctxdiff confirm those results.

The only retained definition-level qualifiers are StartUpdate and CancelUpdate. Public BS2StartUpdate/BS2CancelUpdate APIs write them while UpdateThread polls them. Their target-proven independent zero stores and polling/exit schedule reproduce the saved best; all other unit functions remain exact. No use-site volatile cast was added.

DiscEntries is the actual existing 512-entry disc table at 0x80480000, stride 0x200. Target memset covers 0x40000 bytes and DVDReadPrio fills the table. The declaration follows the same ADDRESS convention as Entries/EntriesToImport in the existing header and adds no allocated section storage. Direct typed accesses restore the target logging address rematerialization. Combined seat/output initializers compute the same pointers as the former assignment-plus-increment statements. No operation, string, error path, counter or call argument changes meaning.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Update] pool: IDENTICAL
[src/BS2/BS2Update] objdiff: code 400/4052 data 10488/10488 functions 9/10 fuzzy 99.4018 linked code 0
[src/BS2/BS2Update] instruction-exact functions: 9/10
[src/BS2/BS2Update]   section .bss size 9056 match 100.0
[src/BS2/BS2Update]   section .data size 1328 match 100.0
[src/BS2/BS2Update]   section .sbss size 80 match 100.0
[src/BS2/BS2Update]   section .sdata size 24 match 100.0
[src/BS2/BS2Update]   section .text size 4052 match 99.40178
[src/BS2/BS2Update]   below 100: UpdateThread 99.33625
[src/BS2/BS2Update] baseline: code 400/4052 data 10488 functions 9 fuzzy 95.7088
regressions vs baseline: 0
global matched_code_percent: 97.95043 -> 97.95043
global fuzzy_match_percent: 99.90734 -> 99.91234
global complete_code_percent: 89.90470 -> 89.90470
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: src/BS2/BS2Update.c: volatile object declaration (orchestrator checks the target really re-reads it) (+2 net), e.g. volatile u32 StartUpdate = 0;
GATE PASS
```

### Complete explicit stack-access audit

Target/source both 47 explicit stack instructions, equal at every ordinal.

```text
  0  stwu r1, -0xf0(r1)
  2  stw r0, 0xf4(r1)
  3  addi r11, r1, 0xf0
 15  addi r3, r1, 0x20
 22  stw r15, 8(r1)
 24  stw r15, 0xc(r1)
 25  stw r15, 0x10(r1)
 33  lwz r0, 0x24(r1)
 79  addi r3, r1, 0x18
 89  addi r3, r1, 0x28
 92  addi r3, r1, 0x28
 95  addi r3, r1, 0x28
 96  addi r4, r1, 0x18
 98  addi r3, r1, 0x28
115  addi r3, r1, 0x28
118  addi r3, r1, 0x28
133  addi r4, r1, 0x28
136  addi r3, r1, 0x28
137  addi r4, r1, 0x68
146  addi r3, r1, 0x68
185  addi r3, r1, 0x68
236  addi r4, r1, 0x68
248  lwz r0, 0x9c(r1)
290  addi r3, r1, 0x48
293  addi r3, r1, 0x48
296  addi r3, r1, 0x48
297  addi r4, r1, 0x18
299  addi r3, r1, 0x48
316  addi r3, r1, 0x48
319  addi r3, r1, 0x48
332  addi r4, r1, 0x48
335  addi r3, r1, 0x48
336  addi r4, r1, 0x68
344  addi r3, r1, 0x68
381  addi r3, r1, 0x68
472  addi r4, r1, 0x68
488  addi r6, r1, 0x14
499  lwz r0, 0x14(r1)
562  addi r3, r1, 8
570  addi r3, r1, 0xc
571  addi r4, r1, 0x10
579  lwz r4, 0xc(r1)
593  lwz r3, 0x10(r1)
601  lwz r0, 8(r1)
907  addi r11, r1, 0xf0
909  lwz r0, 0xf4(r1)
911  addi r1, r1, 0xf0
```
