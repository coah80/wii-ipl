# da5 de-asm attempts

Worktree `w0929-fix-board`, branch `agent/w1005/da5`, starting commit `7aa71d29`.
Read deasm-round.md, common.md, levers.md, and the original-object Ghidra exports.
Baseline full build and quick gate pass. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.
WPAD: 67/67 exact, code 31040/31040, data 15096/15096.
cntcache: 5/5 exact, code 1828/1828, data 280/280.
sdi_api: 22/22 exact, code 5948/5948, data 248/248.

## ISD_GetCardSize

1. Activate the existing C fallback, name the card geometry values, and correct the high-capacity sector multiplier from 512 to 1024 to match the target shift by 10. Pool 4/4 identical; 84/84 instructions, 33 differences.
2. Decode the CSD fields into named locals before clamping the read block length. 84/84 instructions, 26 differences.
3. Reverse the two bitwise-OR expressions so MWCC emits the target rotate-insert direction. 84/84 instructions, 23 differences.
4. Split the block-length subtraction and capacity product into assignments. 84/84 instructions, 26 differences. Rejected.
5. Compile all 36 declaration/field-extraction orders from attempt 3. Best 84/84, 20 differences. No exact result yet. Results in build/da5/sdi-search.json.

6. Run the provided srcsearch tool. Its relative --out path failed to resolve the mini report; a worktree-local copy used an absolute output path and matched the function definition instead of the earlier prototype. One legal mutation produced no score gain from 98.39286%.
7. Compile 180 combinations of declaration order, normalized block length, capacity reuse, and an inline clamp helper. Best remained 84/84 with 20 differences.
8. Compile 96 combinations of hoisted fields, separate declarations, unsigned-int versus u32 locals, and output-local order. Same best.
9. Compile 24 product/scale/sector inline-helper and geometry-struct variants. Same best.
10. Compile all 24 orders including the status local and three output locals. Same best.
11. Compile all 24 factor order/grouping combinations from the two best declaration layouts. Best remained 84/84 with 20 register differences. The unchanged asm was retained.

## WPADiManageHandler

1. Restore the C handler using the existing queue/rumble/settings helpers, as in the ogws WPAD_WPAD.c reference. The 2010 target also needs the reconnect countdown: decrement with saturation on every running handler call, then reconnect only at zero. Move __reconnect before WPADiAfh to restore literal order and remove the assembly-only packed string block.
   Pool 22/22 identical; ctxdiff 484/484 instructions, diffs 0.
   Clean full gate: GATE PASS, 67/67 exact, code 31040/31040, data 15096/15096, no regressions or forbidden/readability findings. DOL SHA1 unchanged.

## _CNTCACHEDeleteTitle

1. Reconstruct the token loop and deletion dispatch. Pool 9/9 identical; 51/50 instructions. ES_TITLE_TYPE returns u64, so comparison emits xor plus compare.
2. Cast the extracted title type to u32, matching the target's word comparison. Pool unchanged; 50/50 instructions, diffs 0.
   Clean full gate: GATE PASS, 5/5 exact, code 1828/1828, data 280/280; zero regressions. DOL SHA1 unchanged.

## _CNTCACHEIsTitleRemovable

1. Inline NAND usage helper, aligned TMD buffer, typed ESTmdView access. Pool 9/9 identical; 81/82 instructions, path stack offset and return-register differences.
2. Align the path buffer, use a single-exit helper, and unsigned version extraction. 80/82; correct frame and path positions, but two missing return copies.
3. Separate NAND status from the helper's result and mask the high version byte. 80/82; version test now exact. Missing copies and initializer scheduling remain.
4. Shared goto exit in the outer function. 78/82; collapses the target's two early-return branches. Rejected.
5. Separate inline TMD eligibility helper. 80/82, shifts scalar stack slots and retains the missing copies. Rejected.
6. Use s32 for statuses and the public return value. Same 80/82; DeleteTitle remains exact. Rejected.
7. Put the usage check directly into the outer function and reuse the ES result local. Still 80/82; scalar stack positions worsen. Rejected.
8. Unsigned removable flag. Still 80/82 and changes cmpwi to cmplwi. Rejected.
9. Hoist the ES result declaration without changing early returns. Still 80/82.
10. Separate helper result initialization and the negative-error arm. 81/82; adds a branch rather than the target return copies. Rejected.

11. Group NAND usage counts into a local struct. Still 80/82; moves the scalar slots. Rejected.
12. Name the high/low title-ID arguments before snprintf. Still 80/82; changes argument scheduling. Rejected.
13. Use automatic inlining instead of an explicit inline keyword on the usage helper. Still 80/82.
14. Add a nested path-and-usage helper. Still 80/82.
Diagnostic-only opt_propagation, opt_common_subs, scheduling, and opt_dead_assignments pragmas did not change the 80-instruction result. All pragmas removed.

15. Source search over the usage helper completed 185 trials, with no improvement from the 80/82-instruction, 89.60976% candidate. It waited for a shared CPU slot before starting. The unchanged asm was retained.

## _CNTCACHEDeleteContent

1. Reconstruct the typed TMD content loop with an inline NAND usage helper. Pool 9/9 identical; 144/145 instructions. Buffer pointer is formed early; scalar slots reversed; extra constant kept across the loop.
2. Move buffer binding after title validation, swap scalar declarations, and use explicit cleanup branches. 143/145. Frame, buffer binding, and scalar slots now match; missing constant reload and helper-result copy remain.
3. Use NANDTitleIdHi/Lo in the path helper. Same 143/145.
4. Make the inline helper title-ID parameter const. Same 143/145.
5. Source search over DeleteContent completed 145 trials with no improvement from the 143/145-instruction, 95.793106% candidate. The unchanged asm was retained.

## CNTCACHEClear

1. Implement the NAND read/line-tokenization/delete/seek/cleanup flow with ordinary literals. Pool has 13 strings versus 9: the existing byte pool duplicates all four live literals. Rejected before register tuning.
2. Remove the packed byte pool and use a normal version literal. Place the title-data format after the clear routine. Pool has 5 strings versus 9, first divergence at index 1: `DeleteTitle` versus target `DeleteTitle `. The target also retains `%016llx `, `/shared2`, and `DeleteContent `, none referenced by the five surviving functions.
3. Reverse the command-dispatch source order. Pool still 5 versus 9, now index 1 is `DeleteContent`. Branch polarity cannot supply the four absent literal entries. Rejected.
Kept the original placeholder. No offset references into the byte blob, dummy string objects, or invented dead functions were added to force data offsets. These strings are consistent with removed cache-writing routines. Their original declarations and references remain unknown.

## Final validation

Two of six requested bodies converted: WPADiManageHandler and _CNTCACHEDeleteTitle. Four placeholders remain, with the compiled trials recorded above. No remaining assigned body was classified as original assembly.

The final full, non-quick gate rebuilt all 43U objects and passed for all three assigned units. Pools are identical, every function and owned section is 100.0%, and regressions, forbidden patterns, and readability warnings are all zero. Fresh ctxdiff after the clean build reports 484/484 instructions with zero differences for WPADiManageHandler and 50/50 with zero differences for _CNTCACHEDeleteTitle. Exact-name objdiff reports 100.0% for both.

| Unit | Instruction-exact before -> after | Code before -> after | Data before -> after |
| --- | --- | --- | --- |
| WPAD | 67/67 -> 67/67 | 31040/31040 -> 31040/31040 | 15096/15096 -> 15096/15096 |
| cntcache | 5/5 -> 5/5 | 1828/1828 -> 1828/1828 | 280/280 -> 280/280 |
| sdi_api | 22/22 -> 22/22 | 5948/5948 -> 5948/5948 | 248/248 -> 248/248 |

GATE PASS

DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
The unit counts remain unchanged because the previous assembly bodies already counted as exact.

Inventory audit: 209/209 remaining asm bodies and blocks have distinct file/line entries, verified against current source lines. Verdicts: 160 ORIGINAL-ASM, 49 PLACEHOLDER. Excluded 65 declarations and comment text. Other workers' files were classified without edits.

Scratch candidates and experiment results remain in this worktree's ignored `build/da5/` directory. `build/da5/final-gate.log` contains the full gate output. No source changes remain outside the two accepted conversions.
