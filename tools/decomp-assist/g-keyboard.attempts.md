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
