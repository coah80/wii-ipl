# perm8 C permuter lane

Baseline: `255f3e05305939d73df73fcf9c4cd9044be9fa91`. Worktree: `sol-high`, branch `agent/w1002/sol-perm8-max`.

All three units had identical pools before source experiments. Only Wii Menu 4.3U was built. Compile scripts use the GC/3.0a5.2 MWCC command and flags from `ninja -t commands`, including `-O4,p`, `-ipa file`, `-fp_contract off`, and `-lang=c`; dependency-file generation is omitted for temporary objects. Original extracted objects supply the targets. The scorer selects the exact function name and includes stack differences. The aligned partition buffer remains aligned to 32 bytes in the preprocessed context.

Per-function contexts and compile scripts are under `/tmp/perm-<function>`. Compiler dependencies are in `/tmp/perm8-venv`. Searches used at most two permutation jobs in this lane: one job per concurrent function, then two jobs for the final partition search after the other searches finished. Each stalled search was stopped after about 45 minutes without a better score. Searches stopped earlier when a readable exact reconstruction was found or when a better readable seed replaced the old seed.

## Exact source changes

- `NWC24ReadMsgSubjectPublic`: baseline 100/104 instructions. At offsets 0xa0..0xb8 and 0xe0..0xf8, the target compares status with 0 and -8. The four missing instructions are unconditional switch exits, including unreachable default exits; there are no additional length-check comparisons. A single success-case switch whose default marks overflow and breaks, then returns other errors directly, produces 104/104 instructions and zero differences.
- `NWC24ReadMsgTextPublic`: the same status dispatch at 0xa8..0xc0 needs two unconditional exits. The same readable switch/default/early-return form produces 70/70 instructions and zero differences.
- `NWC24SetMsgSubjectAndTextPublic`: the score-40 permutation suggested staging the computed text capacity. The readable reconstruction stores that value in `textCapacity`, copies it to the mutable `textWorkSize`, and declares `subjectWork` before `subjectWorkSize`. This produces 190/190 instructions and zero differences. No unused pointer assignment, identity inline wrapper, or multiplication noise from the generated candidate remains.

Reader changes were committed as `1bb68c6f`. Their clean full gate reported 11/12 exact functions, code 4592/5352, data 232/232, identical pools, zero regressions, zero forbidden patterns/readability warnings, and the correct DOL SHA1.

The setter was committed as `30744387`. Its clean full gate reported 12/12 exact functions, code 5352/5352, data 232/232, every owned section at 100%, identical pools, zero regressions, zero forbidden patterns/readability warnings, and the correct DOL SHA1.

## Reader source attempts

Both reader functions were tried with at least these distinct changes:

1. Explicit OK/OVERFLOW/default switches: correct instruction counts, but 10 subject differences and five text differences from range dispatch.
2. A success/default switch with an overflow `if` ending in `break`: still 100/104 and 68/70 instructions because the exits disappeared.
3. Nested overflow switches and reordered case labels: no exact result; extra dispatch tests or missing exits remained.
4. Explicit rejected error cases: 110/104 and 73/70 instructions; discarded.
5. Early `return result` for rejected statuses instead of `goto done`: both functions became exact. Existing buffer bounds and truncation behavior are preserved.

## NWC24SetMsgSubjectAndTextPublic attempts

1. Split the text-capacity ratio into numerator and division statements; reorder size and work-pointer setup; retain a charset-name pointer: still non-exact.
2. Use meaningful text/subject charset temporaries and separate encoding variables: 65 register differences, or shorter non-matching instruction streams; discarded.
3. Name the text buffer separately: 65 differences; discarded.
4. Reconstruct the staged text capacity with a real `textCapacity` variable: eight remaining differences, solely swapping `subjectWork` and `subjectWorkSize` registers.
5. Reorder those two declarations while retaining the capacity staging: zero differences and 100% exact-name objdiff. No helper or redundant temporary was needed.

Generated score-150 candidates assigned to unused charset temporaries; discarded. Score-300 output read `subjectWorkSize` before initialization; discarded. Score-125 output added a pointer-to-pointer alias of `work`; discarded. The useful score-40 capacity hint was translated into the minimal readable source above.

## ConvertDateToDays attempts

1. Compute annual days before the century quotient, or decrement the year offset later: 16 differences remained.
2. Split common-leap quotients and try a single total expression: 16-18 differences.
3. Enumerate natural groupings of annual, century, and ordinary leap days, with real scalar temporaries: best six differences, at instructions 98..103. This seed keeps 113/113 instructions but changes scheduling and registers in the final arithmetic.
4. Put the century and ordinary leap calculations in readable inline helpers, and vary their source expressions: best still six differences.
5. Permute both the original and refined seeds: no exact result. The original source was restored; no fuzzy-only change is retained.

## ConvertDaysToDate attempts

1. Initialize the month at its declaration or use a word-sized month: 26 differences.
2. Invert the monthly leap branch: 12 differences. Nest the February check: 107/103 instructions; discarded.
3. Initialize the saved day count at its declaration, change the leap-result scalar type, or qualify the month alias: six differences remained.
4. Reorder the monthly declarations: six differences remained at 55, 57, 60, 83, 84, and 88, swapping the month byte and leap flag between r0 and r12.
5. Permute the complete function, then restrict randomization to the monthly loop: no improvement over score 30. Original source restored.

## pdm_part_is_master_boot_sector attempts

1. Grouped little-endian inline helpers, separate even/odd groups, byte locals, and sequential accumulators: no exact result.
2. Enumerate direct little-endian macro expression trees: the best readable seed has 84/84 instructions and 33 differences. It removes the two extra baseline instructions but still differs in allocation and scheduling.
3. Cache each real start-sector input byte before or after clearing the destination, using byte and word temporaries: 33-35 differences; discarded.
4. Run whole-function randomization: best score 820, with no exact candidate. A valid score-820 hint caches buffer byte 456; readable reconstructions did not match.

The tied score-820 candidate using `(454 & 0xFF) + 3` reads byte 201 instead of byte 457. It is semantically wrong and was rejected. Earlier score-950 candidates combined the two cursor pointers into an array; those were also discarded. Original source is retained.

## pdm_part_get_start_sector attempts

1. Grouped endian inline helpers, word macros, byte locals, pointer views, and expression-tree permutations: the best initial readable seed had 45 differences with 276/276 instructions.
2. Reconstruct the valid permutation declaration-order hint: 39 differences. Permute the four real loop-variable declarations: best eleven differences, all in the two extended-entry byte decoding blocks, at 175..181, 208..209, and 213..214.
3. Relative-sector helpers, explicit grouping of base and decoded word, and named even/odd byte groups: 26-38 differences, or no exact build; discarded.
4. Meaningful byte-array views of the partition start/count fields: eleven differences remained.
5. Cache actual offset bytes with byte/word scalar types at different declaration positions: 11-41 differences. Every value was initialized and actually used; no exact result.
6. Run a second search from the eleven-difference seed, restricted to the two byte-decoding blocks, with two jobs. Generated score-107 and score-85 hints introduced unused pointer/scalar assignments. The natural byte-view and cached-byte reconstructions did not match and are not retained.

Before starting each function, origin was fetched under `/tmp/wii-git.lock` and checked for existing exact work. Origin's partition source changed during the run in `230c3af2`, adding a typed endian helper. Compiling that updated source separately proved both requested functions remained non-exact (86/84 instructions for the master-sector function, 276/276 and 147 positional differences for the start-sector function). The start-sector search was resumed after a fresh fetch; the source was unchanged at that second check. No remote changes, branch operations, or rebases were performed in this worktree.

## Search measurements and final gate

The final measurements and the final clean gate are appended after every search exits. Permuter scores are search penalties, not objdiff percentages. Only readable source with exact-name objdiff 100% and zero instruction differences counts as a result.

| Function | Permutations | Best score | Result |
| --- | ---: | ---: | --- |
| NWC24ReadMsgSubjectPublic | 1455 | 400 | Exact structural source rewrite; search stopped |
| NWC24ReadMsgTextPublic | 4496 | 200 | Exact structural source rewrite after stalled search |
| NWC24SetMsgSubjectAndTextPublic | 2498 | 40 | Readable reconstruction reached exact match; search stopped |
| ConvertDateToDays | 1336 + 3721 | 355 then 235 | No exact result |
| ConvertDaysToDate | 1826 + 1814 | 30 in both phases | No exact result |
| pdm_part_is_master_boot_sector | 4950 | 820 | No exact result |
| pdm_part_get_start_sector | 2317 + 15888 | 418 then 85 | No readable exact result |

The final partition phase ran 4133 seconds with two jobs, ending after about 45 minutes without a lower score. The score-85 candidate still requires an unused byte assignment. Forty-eight readable cached-byte variants and the entry-view variants failed exact comparison. The best readable partition seed stayed eleven differences and was not retained. Every search exited, with no permutation process left running. Full raw source-attempt details are preserved in `/tmp/perm8-raw-attempts.md`; all generated inputs and candidates remain outside the repository.

| Unit | Instruction-exact functions before -> after | Exact code bytes before -> after | Exact data bytes before -> after |
| --- | --- | --- | --- |
| NWC24MsgSubject | 9/12 -> 12/12 | 3896/5352 -> 5352/5352 | 232/232 -> 232/232 |
| NWC24DateParser | 6/8 -> 6/8 | 1508/2372 -> 1508/2372 | 40/40 -> 40/40 |
| pdm_partition | 18/20 -> 18/20 | 2276/3716 -> 2276/3716 | No data sections |

Final open-function audit:

- `ConvertDateToDays`: 96.92921%; 73 logged source attempts in the raw record, with at least three distinct readable changes documented above.
- `ConvertDaysToDate`: 99.70874%; 42 logged source attempts in the raw record, with at least three distinct readable changes documented above.
- `pdm_part_is_master_boot_sector`: 86.5%; 36 logged source attempts in the raw record, with at least three distinct readable changes documented above.
- `pdm_part_get_start_sector`: 82.56159%; 87 logged source attempts in the raw record, with at least three distinct readable changes documented above.

The final full gate uses a clean 4.3U rebuild and all three assigned units. Source remained unchanged after it; only this attempt record was consolidated. No configure.py linking flags, shared headers, symbols, retail assembly, or other units changed. Remaining compiler choices are unresolved; no fuzzy-only source is retained.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 5352/5352 data 232/232 functions 12/12 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 12/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 3896/5352 data 232 functions 9 fuzzy 99.3012
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1508/2372 data 40/40 functions 6/8 fuzzy 99.3642 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 6/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.36425
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 99.70874
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1508/2372 data 40 functions 6 fuzzy 99.3642
[libs/RVL_SDK/src/fa/pdm_partition] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pdm_partition] objdiff: code 2276/3716 data None/None functions 18/20 fuzzy 93.5985 linked code 0
[libs/RVL_SDK/src/fa/pdm_partition] instruction-exact functions: 18/20
[libs/RVL_SDK/src/fa/pdm_partition]   section .text size 3716 match 93.598495
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_is_master_boot_sector 86.5
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_get_start_sector 82.56159
[libs/RVL_SDK/src/fa/pdm_partition] baseline: code 2276/3716 data None functions 18 fuzzy 93.5985
regressions vs baseline: 0
global matched_code_percent: 91.16326 -> 91.21187
global fuzzy_match_percent: 99.60110 -> 99.60236
global complete_code_percent: 74.56724 -> 74.56724
global matched_data_percent: 99.55890 -> 99.55890
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
