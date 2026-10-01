# tiInputForm worker result

Instruction-exact gate count: 207/221 -> 208/221.
Objdiff-exact functions: 209/221 -> 210/221.
Matched code: 30712/50656 -> 38924/50656 bytes.
Matched data: 908/3772 -> 908/3772 bytes.
Asm bodies: 6 -> 5.

Accepted changes: onCommand prediction modes use signed temporaries with typed conversions at the API calls; LayoutByNW4R::draw is C++ and keeps the Base::draw inline boundary. Both have fresh ctxdiff diffs 0. Source commits: 82f652f0 and 320f8719.
Changed files: src/keyboard/tiInputForm.cpp, tools/decomp-assist/tiInputForm-sol.attempts.md, tools/decomp-assist/tiInputForm-sol.report.md.
No shared headers, configuration, symbols, protected tools, or baseline reports were changed.

## Remaining non-matching functions

| Function | Objdiff percent | Remaining difference |
| --- | ---: | --- |
| Base::onCursor | 99.915436 | Float allocation and multiply operand order; same 473 instructions. |
| Base::calcCursorPos | 91.622696 | Scale-component allocation and float load/arithmetic scheduling; same 326 instructions. |
| Base::onPressUp | 99.55285 | Guard omits the target's redundant branch; 245/246 instructions. |
| Base::onPressDown | 99.55285 | Guard omits the target's redundant branch; 245/246 instructions. |
| Base::onPressDownHWKB | 98.35185 | Guard, trailing Zi comparison, and selection register; 266/270 instructions. |
| Base::onPressLeftHWKB | 99.97727 | Guard compares 1/beq, target compares 0/bne; same 264 instructions. |
| Base::onPressRightHWKB | 99.97818 | Guard compares 1/beq, target compares 0/bne; same 275 instructions. |
| LayoutByNW4R::create | 95.02809 | Root-pane search and animation-file reload boundaries, allocation; 352/356 instructions. |
| LayoutByNW4R::setLanguage | 96.44726 | Root-pane load moves ahead of pane-name selection; same 237 instructions. |
| Base::isOverRowLimit | 97.184875 | Scale scalar caching removes target loads; allocation and operand order; 235/238 instructions. |

## Remaining asm conversions

All five existing asm bodies remain objdiff 100%. All have at least three distinct built C++ trials and were restored because no conversion stayed exact.

- Base::create: C++ reaches 72/72 instructions, structural 0; declaration search reached 19 register differences after 38 builds.
- Base::onPressLeft: C++ reaches 154/154 instructions, two guard differences.
- Base::onPressRight: local wchar array copies as halfwords rather than target words; stack and guard differ.
- Base::calc: C++ reaches 165/165 instructions; float scheduling and operand order differ.
- Base::RowInfoManager::init: grouped row pointers improve to 39/39 instructions; loop-limit reuse and head setup still differ.

Every remaining real non-exact function and asm conversion has at least three distinct, built, logged source trials. Failed harness trials are labeled and excluded. No fuzzy trial remains in the source.

## Gate count limitations

Animation::calc and Base::confirmInputting_ are objdiff 100%; the gate's disassembly normalizer reports two branch differences in each despite identical encoded branch bytes. These are count artifacts, not new matches. The concatenated isEnableCursorCache/getStartPos target symbol has no source function or fuzzy score and was left intact.
The exact source form for the remaining functions is unresolved. The data score remains below 100%; no linking investigation was attempted.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiInputForm] pool: IDENTICAL
[src/keyboard/tiInputForm] objdiff: code 38924/50656 data 908/3772 functions 210/221 fuzzy 99.4528 linked code 0
[src/keyboard/tiInputForm] instruction-exact functions: 208/221
[src/keyboard/tiInputForm]   section .bss size 96 match None
[src/keyboard/tiInputForm]   section .ctors size 4 match 100.0
[src/keyboard/tiInputForm]   section .data size 2736 match 65.53332
[src/keyboard/tiInputForm]   section .rodata size 760 match 100.0
[src/keyboard/tiInputForm]   section .sbss size 32 match 33.333336
[src/keyboard/tiInputForm]   section .sdata size 40 match 100.0
[src/keyboard/tiInputForm]   section .sdata2 size 104 match 100.0
[src/keyboard/tiInputForm]   section .text size 50656 match 99.45278
[src/keyboard/tiInputForm]   below 100: onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos 99.915436
[src/keyboard/tiInputForm]   below 100: calcCursorPos__Q39textinput9inputform4BaseFff 91.622696
[src/keyboard/tiInputForm]   below 100: onPressUp__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDown__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDownHWKB__Q39textinput9inputform4BaseFv 98.35185
[src/keyboard/tiInputForm]   below 100: onPressLeftHWKB__Q39textinput9inputform4BaseFv 99.97727
[src/keyboard/tiInputForm]   below 100: onPressRightHWKB__Q39textinput9inputform4BaseFv 99.97818
[src/keyboard/tiInputForm]   below 100: create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer 95.02809
[src/keyboard/tiInputForm]   below 100: setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language 96.44726
[src/keyboard/tiInputForm]   below 100: isOverRowLimit__Q39textinput9inputform4BaseFUlPCw 97.184875
[src/keyboard/tiInputForm]   below 100: isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv None
[src/keyboard/tiInputForm] baseline: code 30712/50656 data 908 functions 209 fuzzy 99.4500
regressions vs baseline: 0
global matched_code_percent: 87.07200 -> 87.34617
global fuzzy_match_percent: 99.36478 -> 99.36484
global complete_code_percent: 61.40923 -> 61.40923
global matched_data_percent: 91.13999 -> 91.13999
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
