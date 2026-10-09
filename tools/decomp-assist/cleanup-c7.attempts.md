# cleanup-c7 keyboard cleanup

Worktree `sol-high`, branch `agent/w1009/cleanup-c7`, base `f1db6b65`.
Read cleanup-common.md, o-tistr.attempts.md, o-ifl.attempts.md and o3-keyboard.attempts.md before trials.
Initial full 43U build passed. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`; `DECOMPLETE_OK`.
Baseline tiString 42/42 exact, code 5176/5176, data 288/288; tiInputForm 221/221 exact, code 50656/50656, data 3772/3772.
Both units are Matching and every reported section is 100%. Preexisting untracked rx4/rx59/rx70 artifacts are preserved.

## Retained changes

- tiString.cpp replaces the unsupported composer explanation with one compiler comment. The aggregate tests and dead stores remain because removing each one changes .text. CharacterOutput and its reset method were already absent at this base; the newline reset is composing.clear().
- tiInputForm.cpp removes glyphBottom's extent temporary, renames strippedFunctionStandIn to preserveStrippedFunctionLayout, and shortens its explanation to one line. The external stand-in remains because deleting it or making it static changes getter emission order and .sdata2.
- calcCursorPos's zero local becomes rectZero. Its first declaration and assignment before the loop remain, with one comment explaining the FPR allocation requirement. scaledExtent retains its extent local because a direct return changes 28 instructions.
- include/keyboard/tiString.h and include/keyboard/tiInputForm.h are unchanged. The retained source needs no declaration changes; inline/vtable ownership remains as established by o-tistr and o-ifl.

## Compiled trials

Each trial used the real source path and rebuilt only its owned 43U object. Allocated section sizes and bytes were compared with fresh baseline objects. Every rejected trial was restored.

| Trial | Function instruction differences | Changed allocated sections | Result |
| --- | ---: | --- | --- |
| hangul-no-empty-test | 73/136 | .text | rejected and restored |
| hangul-no-newline-reset | 71/136 | .text | rejected and restored |
| hangul-no-next-state | 65/136 | .text | rejected and restored |
| hangul-no-dead-next-store | 65/136 | .text | rejected and restored |
| hangul-no-dead-length-store | 30/136 | .text | rejected and restored |
| hangul-direct | 73/136 | .text | rejected and restored |
| hangul-explicit-count-narrowing | 30/136 | .text | rejected and restored |
| extent-direct-return | 28/326 | .text | rejected and restored |
| glyph-bottom-direct-return | 0/326 | none | retained in final cleanup |
| calc-no-zero-local | 8/326 | .text | rejected and restored |
| calc-zero-at-declaration | 35/326 | .text | rejected and restored |
| calc-direct-geometry | 41/326 | .text | rejected and restored |
| calc-direct-height | 31/326 | .text | rejected and restored |
| calc-direct-width | 32/326 | .text | rejected and restored |
| remove-stripped-function | 0/326 | .text, .sdata2 | rejected and restored |
| static-stripped-function | 0/326 | .text, .sdata2 | rejected and restored |
| count-with-length-local | 30/136 | .text | rejected and restored |
| count-with-terminator-index | 31/136 | .text | rejected and restored |
| count-before-terminator | 30/136 | .text | rejected and restored |
| count-with-narrowed-output-index | 31/136 | .text | rejected and restored |

## Verification

Final tiString and tiInputForm allocated section sizes and bytes equal the full-build baseline.
pool_diff: tiString and tiInputForm pools IDENTICAL.
ctxdiff: inputChar 136/136 instructions, diffs 0; calcCursorPos 326/326 instructions, diffs 0.
Focused diff and git diff --check passed. Final gate --quick passed with 0 regressions, 0 forbidden-pattern additions and 0 readability warnings.
Fresh build/43U/report.json and build/43U/ok passed; completion checker returned DECOMPLETE_OK.
Final tiString 42/42 and tiInputForm 221/221 instruction-exact; every reported section is 100%, both units fully linked.
Global report measures equal the fresh pre-cleanup baseline. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
Source commits: tiString 06b51c30; tiInputForm 77341408. Final gate output: /tmp/cleanup-c7-final-gate.txt.
