# g-keyboard attempts

Worktree data-d4; branch agent/w1009/g-keyboard; base 54ca052b.
Read opus-common.md in full. No pushes, PRs, rebases, or cross-worktree edits.
Initial full 43U build passed; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
Baseline odiff: calcCursorPos 43/326, create 153/356, inputChar 73/136.
Two InputForm saved diffs are byte-identical and omit addButtonAnimation declaration.
Unrelated preexisting untracked files preserved.

o2-keyboard.wip.diff: original build fails for missing member declaration. Repaired declaration: pool identical, calcCursorPos 39/326, create 128/356, equal sizes. opus-inputform.wip.diff SHA identical; same source/build/measurement.
opus-tistring.wip.diff: compiled, pool identical, 70/136 differing, size 0x210 vs 0x220. Rejected: append tests an always-zero buffer slot and alters generic newline behavior. Restored baseline for honest trials.

## Compiled trials
Single/pair pragma sweep on saved InputForm + original tiString: no exact hits or gains.
32 direct rectangle-reference/copy/size-vector forms: best 39, copies worse.
28 consistent geometry helper forms: best 50.
208 helper-scope pragmas/newline reset variants for inputChar: best 60; none exact.
90 chain/temporary/ref-return/clear variants: best 59, none exact.
GC versions 3.0a3 through 3.0a5.2: tiString unchanged; older InputForm versions regress 5 functions. GC 2.6/2.7 reject ipa.
Create: existing selectInputTextName reuse gives 120 differences; complete scoped declarations 135-138; constrained regsim reaches only 8/15 requested assignments.
Read-only prior scratch has a fully consistent calcCursorPos geometry-helper form, reproduced at 8/326. All surviving differences swap the zero constant f29/f30 with scale.x. Prior 20-difference inconsistent-helper forms excluded.
Initializer/declaration trials: best stays 8. Malformed generated named-zero-top trials used a self initializer; excluded from all results and never retained.

Further calc trials: 36 helper order/body forms, 48 scalar-reference forms, 150 scoped single/pair pragma combinations, 14 corrected constant/declaration variants, 30 local-math bodies, 18 glyphBottom signature/definition-order forms. Best remains 8; no exact.
Further create trials: 24 free animation-helper forms best 120; 16 whole animation-loop helpers best 106 but runtime count reload changes the target instruction shape. 16 row-helper forms best 117.
Fresh allocator trace saved in /tmp/g-keyboard-calc8trace. FPR zero = v89/f30, scale.x = v82/f29, scale.y = v95/f31. Simulator proves moving scale.x beyond v89 or zero below v82 fixes all colors, but the tested readable expressions do not produce that numbering.

## Retained source
Consistent glyphBottom and scaledExtent use at every glyph calculation; no mixed direct/helper forms. Reuse existing selectInputTextName in create and the saved substantial animation-resource helper with its missing header declaration. No optimization pragmas retained.
Fresh own-object report: calcCursorPos 93.05215 -> 99.877304, odiff 43 -> 8, 0x518 both; create 96.40169 -> 98.16011, odiff 153 -> 120, 0x590 both. Unit exact functions stay 219/221; data stays 3772/3772.
inputChar unchanged, 90.757355%, odiff 73/136; exact functions stay 41/42, data 288/288.
No fully exact unit; Matching flips are prohibited for this result.
24 glyph-initialization helper and 12 grouped geometry/output helper forms did not beat 8. Compiler tie remains: f29/f30 swap between zero and scale.x. InputChar reset/chain helpers retain a real conditional block or fold the indexed writes; no honest form reproduced the branchless dead compare.

Final review extended scaledExtent to the input-form width bound as well as every glyph width. It preserves the same 8 differences. Chaining the height helper through scaledExtent was measured separately.
Initial gate after retained changes: GATE PASS, zero regressions, zero forbidden patterns, zero readability warnings. Full build and DOL SHA1 passed. A final gate after the width-bound consistency edit follows.

Final GATE PASS: full 43U build ok; DOL 26116613f624061ba99c8d1a299aaa6efa85670d; identical pools; all owned data sections 100%; 0 regressions; 0 forbidden-pattern additions; 0 readability warnings. No exact function gains. Units remain NonMatching.
Height helper chaining gave 81 differences and was rejected. Final instruction counts remain calcCursorPos 8/326, create 120/356, inputChar 73/136.


## Round b, MAX, 2026-10-09

Assigned worktree data-d4, branch agent/w1009/g2-keyboard, HEAD 5046adc6.
Read opus-common.md and this log again. Preserved preexisting untracked files.
Fetched origin under /tmp/wii-git.lock; origin/main moved to ad5b9dea during setup.
Round-a source remains the starting point. Fresh full 43U build passed with DOL
26116613f624061ba99c8d1a299aaa6efa85670d. Both owned pools are identical.
Baseline report: tiInputForm 219/221 exact, data 3772/3772; tiString 41/42 exact,
data 288/288. calcCursorPos has 8/326 differences, all f29/f30 swapping scale.x
and the glyph zero constant. create has 120/356; inputChar has 73/136.
Reviewed the prior single/pair pragma sweep rather than repeating its unchanged
source candidates. Read the original-object Ghidra bodies, prior allocator trace,
levers, and saved inputChar diffs. Used graphify only to check cursor callers;
current source and object measurements remain the matching evidence.

calcCursorPos: 240 new compiled forms covered rectangle-based width helpers,
scale-vector parameter forms, a nested axis-scaling helper, and explicit zero
arguments for glyph initialization. The best stays 8/326. Vector parameters put
the zero constant in f29, but swap scale.x/scale.y in f30/f31 and alter scheduling
at wrap transitions, leaving at least 25 differences. Explicit zero arguments
preserve the eight-difference baseline. None retained.

create: 32 new detached-row and normal-button construction helper forms compiled.
The best remains 120/356; detached-row forms give 123, and copying button data
regresses code generation. None retained. Private compiler source paths rename
__sinit_\tiInputForm_cpp; that name-only difference was excluded from the private
regression counter. Final measurement uses the real source path.

calcCursorPos: 32 additional value-returning glyph initialization helper trials;
30 compile and change stack placement/instruction count. Two harness-invalid
named-zero aggregate forms are excluded. None retained.

inputChar: the saved R1 diff remeasures at 61/136 and 0x21c, not the historic 12,
on the current source. A real CharacterOutput::clear loop plus a u16 member count
reaches 13/136 with equal 0x220 size and no other function drops. It clears prior
buffer characters before resetting the count when a newline is appended. The
caller appends one character to a fresh output, so its observable output is the
same as the baseline. This is a lead under review, not an exact match.

The clearing loop is unnecessary for the 13-difference result. Removed it and
kept only newline reset in the existing append method and a u16 member count.
This minimal form independently rebuilds to 0x220, 136/136 instructions, 13 diffs.
It reconstructs the newline test proved by target instruction 68, cmplwi r4,0xa.
The target has no consuming branch; our remaining bne/li and counter allocation
are explicitly unresolved. All 13 differences are at instructions 66-78. Both
cursor-add paths now match without extra helpers. The caller constructs an empty
output and appends one character; resetting its count on newline preserves the
output for every character, including newline and the ignored 0xfffe sentinel.
The count is bounded by the 8-element buffer and is narrowed in the target.

32 finish/count/index forms, 48 cursor-advance forms, 24 further real clear-loop
forms, 48 output-write helper forms, and 180 scoped single/pair pragma forms do
not beat 13. No loops, output-write helpers, cursor helpers, or pragmas retained.
48 coupled scale-vector/height-helper forms do not beat calcCursorPos 8; their
best is 25. Every rejected source/header experiment stays outside the worktree.
Private trial records: 712 attempts, 710 compiled. Two named-zero aggregate factory trials fail to compile and are excluded. Raw records are in /tmp/g-keyboard-b-results.jsonl.

Final round-b verification: GATE PASS, full 43U build ok, DOL SHA1
26116613f624061ba99c8d1a299aaa6efa85670d. Pools identical; all owned data sections
100%; 0 regressions; 0 forbidden-pattern additions; 0 readability warnings.
Gate output: /tmp/g-keyboard-b-final-gate.txt.
Fresh exact-name objdiff: calcCursorPos 99.877304%, create 98.16011%, inputChar
90.757355% -> 93.55882%. odiff/ctxdiff inputChar 73 -> 13, size 0x220 both,
136/136 instructions. tiInputForm stays 219/221 exact and tiString stays 41/42.
No new exact functions. Both units remain NonMatching; no Matching flip is valid.
Retained changes: src/keyboard/tiString.cpp and this log only. No push, PR, merge,
rebase, other-worktree edit, or modification of preexisting untracked files.
