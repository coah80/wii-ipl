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


## Continuation 2026-10-03

Started at `b9bda11d` on `agent/w1002/sol-perm8b-max`. The subject/text setter was already merged and 12/12 exact, so it was skipped after a fresh origin check. Each open function was checked against freshly fetched `origin/main` before its search. All three units had identical pools before experiments.

Compile scripts and targets were refreshed in the existing `/tmp/perm-<function>` directories. Flags match this worktree's `ninja -t commands`; only temporary dependency-file generation is omitted. Contexts contain the requested C function and its real dependencies, with the partition buffer's 32-byte alignment preserved. Stack and branch-target differences are scored. This lane used at most two permutation jobs. Dummy, padding, mask-noise, self-assignment, and external-type mutation passes are disabled; every generated hint still receives semantic and readability review.

### Exact calendar conversion

The monthly-loop score-16 hint initially matched with a pointer alias of `days`; that generated form was rejected. The readable reconstruction needs a signed `calendarYear` temporary in the real leap-year helper and a direct `*parsedMonth` February test. The cached month remains the month-table index. No pointer alias, unused variable, artificial helper, assembly, volatile cast, or register keyword is retained.

`ConvertDaysToDate` is 100.0% by exact-name objdiff and 103/103 instructions with zero ctxdiff differences. The six previously exact DateParser functions remain exact. The focused source change and its first clean full gate were committed as `1cc1ddd4`; evidence is `/tmp/perm8r-month-full-gate.log`.

### Readable attempts for remaining functions

- `ConvertDateToDays`: tried partial Gregorian quotient expressions and equivalent year inputs; separate annual/century/ordinary-leap accumulations with meaningful scalar temporaries; live-variable declaration orders; natural 32-bit scalar types and dependency-correct const scopes. Best readable seed: 113/113 instructions, six scheduling/register differences. The whole-function phase was narrowed to the arithmetic tail, then stopped after 45 minutes without improvement. No non-exact source is retained.
- `pdm_part_is_master_boot_sector`: tried little-endian inline helpers and expression trees; independent cursor/index declarations, initialization and increment order; byte-promotion types and real even/odd accumulators; meaningful offset staging. Best readable seed: 84/84 instructions, 23 differences, improving the prior 33-difference seed. Score 795 overwrites the real sector bound and is rejected. Score 660 introduces unrelated staged constants; its natural reconstructions remain non-exact. The resumed seed stalled for 45 minutes and was stopped. Original source is retained.
- `pdm_part_get_start_sector`: tried typed MBR record fields; separately accumulated even/odd relative-sector bytes with block/function scopes; real entry-byte views and cached bytes; inline byte loops and sequential/pair decoders. Best readable seed: 276/276 instructions, eleven differences. Scores 213 and 114 contain dead scalar/pointer assignments. Natural byte-cache and pointer-view reconstructions remain non-exact. The search was stopped after about 45 minutes with no readable improvement. Original source is retained.

One temporary const-scope experiment moved a declaration before its dependency was initialized. It was rejected, excluded from valid readable attempts, and rerun with dependency-correct declarations. No such source was applied or committed.

Each remaining function has at least three distinct readable source attempts documented above. Full raw records are preserved at `/tmp/perm8r-final-raw-attempts.md`; trial sources, compiler output and instruction diffs remain under `/tmp/perm8-resume-trials`. Permutation inputs and outputs remain outside the repository.

### Resumed search measurements

Permuter scores are search penalties, not objdiff percentages. Current continuation phases are listed separately from the earlier round above.

| Function | Iterations | Best score | Seconds | Result |
| --- | ---: | ---: | ---: | --- |
| pdm_part_is_master_boot_sector | 2224 | 795 | 921 | Reseeded from a better readable form; unsafe hint rejected |
| ConvertDaysToDate | 4078 | 16 | 1571 | Readable exact reconstruction committed |
| ConvertDateToDays | 1107 | 252 | 573 | Reseeded to focus on arithmetic tail |
| pdm_part_is_master_boot_sector | 6239 | 660 | 2756 | Stopped after 45 minutes without improvement |
| ConvertDateToDays | 6425 | 252 | 2715 | Stopped after 45 minutes without improvement |
| pdm_part_get_start_sector | 5594 | 114 | 2714 | Dead-variable hints rejected; no readable improvement |

The first two phases were reattached to their existing processes after restarting the supervisor; their exit codes are unavailable, while their elapsed time, iteration count and scores were preserved. Remaining owned phases exited normally. All searches stopped; the directories are ready to resume.

### Final full gate

| Unit | Instruction-exact before -> after | Exact code bytes before -> after | Exact data bytes before -> after |
| --- | --- | --- | --- |
| NWC24MsgSubject | 12/12 -> 12/12 | 5352/5352 -> 5352/5352 | 232/232 -> 232/232 |
| NWC24DateParser | 6/8 -> 7/8 | 1508/2372 -> 1920/2372 | 40/40 -> 40/40 |
| pdm_partition | 18/20 -> 18/20 | 2276/3716 -> 2276/3716 | No data sections |

The final gate is a clean, non-quick rebuild of all three assigned units. Pools are identical, the DOL SHA1 is correct, and regression, forbidden-pattern and readability counts are zero. Source stayed unchanged afterward. No configure.py linking flags, shared headers, symbols, retail assembly or other units changed. The unrelated untracked pk4/pk6 records remain untouched.

Remaining open functions: `ConvertDateToDays` 96.92921% (113/113, arithmetic scheduling/register allocation); `pdm_part_is_master_boot_sector` 86.5% (86/84 in retained source, byte assembly and registers); `pdm_part_get_start_sector` 84.51811% (276/276, byte-assembly scheduling/registers). All non-exact experimental source was discarded.

Gate evidence: `/tmp/perm8r-final-full-gate.log`.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 5352/5352 data 232/232 functions 12/12 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 12/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 5352/5352 data 232 functions 12 fuzzy 100.0000
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1920/2372 data 40/40 functions 7/8 fuzzy 99.4148 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 7/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.41484
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1508/2372 data 40 functions 6 fuzzy 99.3642
[libs/RVL_SDK/src/fa/pdm_partition] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pdm_partition] objdiff: code 2276/3716 data None/None functions 18/20 fuzzy 94.1798 linked code 0
[libs/RVL_SDK/src/fa/pdm_partition] instruction-exact functions: 18/20
[libs/RVL_SDK/src/fa/pdm_partition]   section .text size 3716 match 94.17976
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_is_master_boot_sector 86.5
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_get_start_sector 84.51811
[libs/RVL_SDK/src/fa/pdm_partition] baseline: code 2276/3716 data None functions 18 fuzzy 94.1798
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## perm8c restart continuation 2026-10-03

Initial status: `agent/w1002/sol-perm8c-max`, HEAD `7654dc33e1f98d0fcf7c8361acc522ec02068b57`; no tracked diff and no commits ahead of origin/main. Unrelated pk4/pk6 untracked logs are untouched. ConvertDaysToDate was already merged in #1033 and remains exact; it is skipped. Source in all assigned units is identical to the freshly fetched origin/main. Existing /tmp search outputs and readable seeds were retained; no old supervisor or permuter process was alive. Previous failed variants were read before selecting new combined experiments.

Fresh object builds needed no work. pool_diff.py reports identical pools for all three units. Baseline exact counts: NWC24MsgSubject 12/12, NWC24DateParser 7/8, pdm_partition 18/20. The three open functions remain non-exact. Raw new trials will be recorded in `/tmp/perm8c-raw-attempts.jsonl`; compile flags come directly from this worktree ninja commands, with only temporary dependency generation omitted.
- ConvertDateToDays checked origin/main a791e598 before experiments; instruction score 16.
- ConvertDateToDays new continuation classes: in-place annual accumulation with direct common-leap returns, signed quotient expression types, and a real signed calendar-year copy combined with the refined tail. 147 new compiled forms; best instruction penalty 6.
- pdm_part_is_master_boot_sector checked origin/main a791e598 before experiments; instruction score 2082.
- Temporary master batch stopped after source generation dropped a required offset declaration from an old saved hint. Those compile failures are excluded from valid attempts. Rebuilt the seed from the retained direct-expression permuter input and added replacement assertions. No repository source was affected. Initial date search setup also stopped before launch because the system Python lacks toml; use the existing permuter virtualenv.
- pdm_part_is_master_boot_sector checked origin/main 333eea81 before experiments; instruction score 2082.
- ConvertDateToDays new search reseeded from the minimal three-scalar annual-return form. Randomization now joins day-of-year accumulation with the Gregorian tail, instead of replaying the earlier tail-only plateau. Inline-wrapper mutations are disabled. Score is measured with stack and branch-target differences.
- ConvertDateToDays perm8c best score 252 after 5 seconds.
- Additional calendar continuation tried range-valid u16 year offsets with signed prior-year arithmetic, real signed counter lifetimes, and an elapsed-calendar-days helper with a live day-of-year argument. 39 forms; best instruction penalty 6.
- Checkpoint: {"ConvertDateToDays": 176, "pdm_part_is_master_boot_sector": 3986} valid temporary object comparisons. Calendar best remains 113/113 with six scheduling/register differences. The combined master extent batch has not improved the prior 84/84, 23-difference seed. Source remains unchanged in the worktree; active searches compile only under /tmp.
- Stopped the combined master declaration/decoder batch after 4134 valid comparisons with no improvement over 23 differences. Additional array ordering permutations recycle the same code generation; move to the distinct typed-field and signed-extent staging experiments. Failed scaffold compiles are excluded from this count.
- Master-sector new continuation classes additionally tried signed low-byte extent staging with real decoded start/count scalars, and typed byte fields for the on-disk MBR entries, including addition/multiplication decoders. 112 forms; best instruction penalty 23.
- pdm_part_get_start_sector checked origin/main 74dcb16a before experiments; instruction score 147.
- Start-sector multiplication decoder improved the readable seed from eleven to nine positional differences, keeping 276/276 instructions. Pause the broader five-operand tree batch to test shift/multiply hybrids around this concrete hint. The nine-difference source remains only in /tmp.
- Start-sector hybrid relative-byte decoder branch 1 complete; best instruction penalty 4, branch exact True.
- Readable exact candidate for pdm_part_get_start_sector: /tmp/perm8c-trials/pdm_part_get_start_sector-hybrid-relative-byte-decoder-2-shift-int-shift-int-shift-int-linear-5ab787fc.c.
- Readable exact candidate for pdm_part_get_start_sector: /tmp/perm8c-trials/pdm_part_get_start_sector-exact-reconstruction-formatted-direct-word-reading-ccae1132.c.
- Readable exact candidate for pdm_part_get_start_sector: /tmp/perm8c-trials/pdm_part_get_start_sector-exact-reconstruction-relative-start-return-long-3c43d9aa.c.
- Readable exact candidate for pdm_part_get_start_sector: /tmp/perm8c-trials/pdm_part_get_start_sector-exact-reconstruction-macro-return-int-663cd65f.c.
- Calendar shared-predicate continuation replaced one or both duplicated leap tests with the existing private helper, including signed scalar types and an early-return predicate. 9 forms; best instruction penalty 6. No unrelated helper changes retained.
- pdm_part_get_start_sector checked origin/main fdd68ddd before experiments; instruction score 147.
- Exact start-sector reconstruction: use unsigned int byte arithmetic for the relative LBA offset, with the real base sector included in read_relative_start_sector. This differs from SDK pf_u32, which is unsigned long, only in compiler expression typing. All shifts operate on initialized real buffer bytes and unsigned 32-bit values. The relative-start helper is a meaningful operation, not an identity wrapper. The bulk MBR-word macro remains unsigned long and is formatted over three lines. Reordered the existing real loop declarations as suggested by the earlier eleven-difference seed. Temporary object comparison is 276/276 with zero differences; copied the readable form to the owned source for object/objdiff/full-gate verification.
- Start-sector exact-name objdiff is 100.0%; the worktree object has 276/276 instructions and ctxdiff reports diffs 0. Full non-quick three-unit gate is GATE PASS: pdm_partition 18/20 -> 19/20, matched code 2276/3716 -> 3380/3716; pools identical, all regression/style/forbidden counts zero, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. DateParser stays 7/8 and MsgSubject stays 12/12. Evidence: `/tmp/perm8c-getstart-full-gate.log`.
- The broad base-inclusive start-sector tree batch was superseded by the concrete nine-difference multiplication hint and the shift/type hybrid reconstruction. No dead assignment, pointer alias, identity helper, mask noise or unused value appears in the retained source.
- pdm_part_is_master_boot_sector checked origin/main be7ded2f before experiments; instruction score 2082.
- Master-sector continuation after the relative-sector win: native unsigned-int byte operands, meaningful accumulation into the zero-initialized start value, direct byte grouping shapes and cursor/summand order. 481 forms; best instruction penalty 23.
- Calendar numerator promotions after the native-int sector result: real signed-int annual/century/common-leap numerators in mixed long/int sums, with direct return or named common-leap counts. 112 new forms; best instruction penalty 6.
- Master-sector also reused the proven relative-start decoder for absolute MBR starts with base zero or the already zero-initialized destination, keeping the count decoder separate. 24 forms; best instruction penalty 23.

### perm8c source-attempt audit

- ConvertDateToDays: distinct new classes covered annual accumulation/direct common-leap returns; signed quotient and numerator typing; valid-width calendar-year lifetimes; real Gregorian-day helper arguments; and reuse of the existing leap-year predicate. 297 valid temporary object comparisons, best 113/113 with six differences. Every new source experiment stayed in /tmp. Original source is retained.
- pdm_part_is_master_boot_sector: distinct new classes covered combined real cursor/array declarations and endian grouping; signed low-byte decoded extent staging; typed on-disk byte fields; native unsigned-int decoding and initialization/accumulation; and reuse of the relative reader for an absolute start. 4752 valid comparisons, best 84/84 with 23 differences. The retained function remains unchanged. No further master permuter restart was warranted after these forms failed to improve the readable seed.
- pdm_part_get_start_sector: signed low-byte staging, multiplication-based decoding, base-inclusive expression trees and shift/type hybrids were tried. 705 valid comparisons. Native unsigned-int offset arithmetic removed the final eleven differences. The minimal readable relative-start helper also stays 276/276 with zero differences; a decoder that returns only the unsigned-int word did not remain exact and was discarded.
- Commit `8bf45d51a2bfc4d153d3b50e43a7aad25a9d583b` preserves the independently rebuilt, objdiff-100% start-sector result and its clean full gate. The unused pk4/pk6 attempt records are untouched. Remaining compiler choices are unresolved; no non-exact experimental source is retained.
- Completed perm8c search: {"function": "ConvertDateToDays", "best": 252, "elapsed": 2708, "iterations": 6698, "returncode": 0, "reason": "45 minutes without score improvement", "log": "/tmp/perm8c-search-ConvertDateToDays.log", "running": false}.

### perm8c permutation phase complete

- ConvertDateToDays new joined day-of-year/tail permutation phase ended normally after 2708 seconds and 6698 iterations. Best search penalty 252, no score improvement for about 45 minutes. No readable exact result. Stack and branch-target differences were included; one permutation job ran. The earlier master/start-sector plateaus were not replayed because the new manual forms and the already exact start-sector reconstruction supplied the useful results.
- All owned searches have exited. Inputs, candidates, raw valid-trial counts and search logs remain under /tmp. The only source change retained is the objdiff-100% start-sector reconstruction. Final validation below is another non-quick three-unit build after every search stopped.

### perm8c final full gate

| Unit | Instruction-exact before -> after | Matched code bytes before -> after | Matched data bytes before -> after |
| --- | --- | --- | --- |
| NWC24MsgSubject | 12/12 -> 12/12 | 5352/5352 -> 5352/5352 | 232/232 -> 232/232 |
| NWC24DateParser | 7/8 -> 7/8 | 1920/2372 -> 1920/2372 | 40/40 -> 40/40 |
| pdm_partition | 18/20 -> 19/20 | 2276/3716 -> 3380/3716 | No data sections |

Exact-name pdm_part_get_start_sector is 100.0%, 276/276 instructions, diffs 0 after the final clean build. ConvertDateToDays stays open at 96.92921%, 113/113 with 16 retained-source differences; best readable temporary seed has six. pdm_part_is_master_boot_sector stays open at 86.5%, 86/84; best temporary seed has 84/84 with 23 differences. Both open functions have more than three distinct valid source-attempt classes above. No untracked pk4/pk6 file, shared header, symbol, configure flag, retail assembly or other translation unit changed.

Final full gate evidence: `/tmp/perm8c-final-full-gate.log`. Final instruction diffs are `/tmp/perm8c-final-<function>.ctxdiff`. Raw temporary comparisons are `/tmp/perm8c-raw-attempts.jsonl`. All owned searches stopped before this non-quick gate.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 5352/5352 data 232/232 functions 12/12 fuzzy 100.0000 linked code 5352
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 12/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 5352/5352 data 232 functions 12 fuzzy 100.0000
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1920/2372 data 40/40 functions 7/8 fuzzy 99.4148 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 7/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.41484
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1920/2372 data 40 functions 7 fuzzy 99.4148
[libs/RVL_SDK/src/fa/pdm_partition] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pdm_partition] objdiff: code 3380/3716 data None/None functions 19/20 fuzzy 98.7793 linked code 0
[libs/RVL_SDK/src/fa/pdm_partition] instruction-exact functions: 19/20
[libs/RVL_SDK/src/fa/pdm_partition]   section .text size 3716 match 98.779335
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_is_master_boot_sector 86.5
[libs/RVL_SDK/src/fa/pdm_partition] baseline: code 2276/3716 data None functions 18 fuzzy 94.1798
regressions vs baseline: 0
global matched_code_percent: 91.56577 -> 91.60263
global fuzzy_match_percent: 99.69885 -> 99.70456
global complete_code_percent: 74.74593 -> 74.74593
global matched_data_percent: 99.55890 -> 99.55890
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
