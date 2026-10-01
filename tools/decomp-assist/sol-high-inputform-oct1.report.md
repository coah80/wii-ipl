# tiInputForm matching result, October 1

Instruction-exact 208/221 -> 214/221. Objdiff-exact 210/221 -> 216/221.
Matched code 38924/50656 -> 45080/50656 bytes. Matched data 908/3772 -> 908/3772 bytes.
Asm bodies 5 -> 3. Total code size remains 50656 bytes. Shared keyboard headers are unchanged.

New exact C++ functions: Base::onPressUp, onPressDown, onPressDownHWKB, onPressLeftHWKB, onPressRightHWKB and isOverRowLimit.
Exact assembly conversions: Base::onPressLeft and Base::onPressRight. Each has exact-name objdiff 100.0%, identical instruction counts and ctxdiff diffs 0.
The right-arrow command is a 16-byte aggregate, also sent as KeyInputData by HWKeyboard::updateTriggerKey_. CharacterInput now includes the existing protocol's final data word, and its ordinary initializer replaces the old hand-labelled constant. onCommand is unchanged at 2053/2053 instructions and diffs 0. The final data word's semantic purpose is unknown.

## Remaining real functions

- Base::onCursor, 99.915436%. Retained 473/473 instructions, five differences in width register homes and multiplication operands. Rect accessors and a division by two reduce this to one operand difference. A math helper fixes both multiplication operands but leaves three width register differences. Correct declaration search exhausts six orders without an exact result.
- Base::calcCursorPos, 91.622696%. Retained 326/326 instructions. Scale X/Y register homes and rectangle-height/width arithmetic scheduling differ. Aggregate/scalar forms, rectangle accessors, intermediate height/width variables, and operand order were tried and restored.
- LayoutByNW4R::create, 95.02809%. Retained 352/356 instructions. Initial root lookup and animation-file pointer reload boundaries differ. Direct root lookup and retained file slots reach 356/356 but leave structural and register differences; restored.
- LayoutByNW4R::setLanguage, 96.44726%. Retained 237/237 instructions. The compiler hoists the root receiver before conditional pane-name selection. Member/free helpers and explicit branch forms do not prevent it; duplicating complete calls increases instruction count and was restored.
- Original concatenated isEnableCursorCache/getStartPos symbol, objdiff None. The config names one eight-byte function by concatenating two names. Both actual source members are present. Source-name and config changes are outside scope.

## Remaining assembly conversions

- Base::create: successful C++ trials reach 72/72 instructions and structural zero. The final declaration search performs 38 builds, leaving 19 register differences. Restored.
- Base::calc: successful C++ trials reach 165/165 instructions. A sine helper and staged blue/angle values reduce differences, but conversion/sine scheduling and final counter/phase load order remain. Restored.
- Base::RowInfoManager::init: successful C++ trials reach 39/39 instructions or 38/39 with fewer structural differences. Loop-limit reload, row-head addressing and store scheduling remain. Restored.

Every open real function and every remaining asm conversion has at least three distinct successful trials in sol-high-inputform-oct1.attempts.md. The two converted asm functions are exact, so no extra trials are needed. The concatenated symbol is a tooling artifact rather than a missing body. Wrong initial declaration-search line ranges were excluded and fully restored.

The two objdiff-100 functions excluded by the instruction gate remain the existing Animation::calc and Base::confirmInputting_ branch-normalization artifacts. No symbol sizes or offsets were adjusted to alter their counts.

## Commits

- 8cfbb5c3 match input form cursor guards
- 1c796490 match hardware keyboard down navigation
- 76010c6c replace left navigation assembly with exact c++
- d90650dc replace right navigation assembly with exact c++
- 779bd5e5 match row limit scale and cursor lifetimes

Only src/keyboard/tiInputForm.cpp and this run's attempts/report files were changed. Pre-existing untracked logs were left untouched.

## Final full gate

Command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/keyboard/tiInputForm --base 3440aab0

The default merge-base 0e6e2350 has no protected baseline. The nearest preceding available baseline, 3440aab0, has the same initial tiInputForm measurements. No baseline was created or edited. Global regressions are zero. The config note is the pre-existing PFSYS_TimeStamp correction already in HEAD; this worker made no config changes.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiInputForm] pool: IDENTICAL
[src/keyboard/tiInputForm] objdiff: code 45080/50656 data 908/3772 functions 216/221 fuzzy 99.5591 linked code 0
[src/keyboard/tiInputForm] instruction-exact functions: 214/221
[src/keyboard/tiInputForm]   section .bss size 96 match None
[src/keyboard/tiInputForm]   section .ctors size 4 match 100.0
[src/keyboard/tiInputForm]   section .data size 2736 match 65.53332
[src/keyboard/tiInputForm]   section .rodata size 760 match 100.0
[src/keyboard/tiInputForm]   section .sbss size 32 match 33.333336
[src/keyboard/tiInputForm]   section .sdata size 40 match 100.0
[src/keyboard/tiInputForm]   section .sdata2 size 104 match 100.0
[src/keyboard/tiInputForm]   section .text size 50656 match 99.55914
[src/keyboard/tiInputForm]   below 100: onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos 99.915436
[src/keyboard/tiInputForm]   below 100: calcCursorPos__Q39textinput9inputform4BaseFff 91.622696
[src/keyboard/tiInputForm]   below 100: create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer 95.02809
[src/keyboard/tiInputForm]   below 100: setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language 96.44726
[src/keyboard/tiInputForm]   below 100: isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv None
[src/keyboard/tiInputForm] baseline: code 38924/50656 data 908 functions 210 fuzzy 99.4528
regressions vs baseline: 0
global matched_code_percent: 87.39812 -> 87.61517
global fuzzy_match_percent: 99.36627 -> 99.36848
global complete_code_percent: 61.64133 -> 61.64144
global matched_data_percent: 91.13999 -> 91.13999
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
