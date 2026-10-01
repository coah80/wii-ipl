# tiInputForm matching continuation

Instruction-exact 214/221 -> 215/221. Objdiff-exact 216/221 -> 217/221.
Matched code 45080/50656 -> 46972/50656 bytes. Matched data 908/3772 -> 908/3772 bytes.
Assembly bodies 3 -> 1. Exact C++ conversions: Base::calc, Base::RowInfoManager::init.
New exact function: Base::onCursor.

The cursor change uses existing rectangle width accessors and computes the centered marker offset in one expression. This preserves width temporary homes and both multiplication operand orders. Fresh ctxdiff: 473/473 instructions, diffs 0.

The calculation conversion follows the actual sustain virtual slot and cached draw-scroll field. Separate blue, phase and angle values preserve conversion/store/sine scheduling. Ordinary inline sine and phase helpers reproduce the target operand order. Fresh ctxdiff: 165/165 instructions, diffs 0.

The row initializer uses an inline loop returning its final capacity read, then retains the row-array pointer for linking the final and first free rows. Fresh ctxdiff: 39/39 instructions, diffs 0. The original creation functions call the initializer out of line. The repository-standard never_inline attribute is therefore applied to its declaration only under TIINPUTFORM_IMPLEMENTATION, inside the existing guard. The other existing guard sides keep their declarations. A definition-only attribute was ineffective and was removed. The final header correction restores LayoutByNW4R::create to its original 352/356 instructions and 95.02809%.

## Remaining functions

| Function | Objdiff | Evidence |
| --- | --- | --- |
| Base::calcCursorPos | 91.622696% | 326/326 instructions; cached scale register homes and rectangle arithmetic scheduling differ. 32 distinct built source variants. |
| LayoutByNW4R::create | 95.02809% | 352/356 instructions; initial root lookup, conditional receiver timing and animation-file pointer reload boundaries differ. 8 distinct built variants. Direct root lookup and file-slot references reach 356/356 but remain non-exact. |
| LayoutByNW4R::setLanguage | 96.44726% | 237/237 instructions; root receiver loads move ahead of conditional pane-name selection. 12 distinct built variants. |
| Concatenated isEnableCursorCache/getStartPos | None | Original eight-byte symbol spans two existing members. No permitted source/config identity change repairs this pairing. |

Base::create remains an instruction-exact assembly body. Its C++ conversion trials reached 72/72 instructions with zero structural differences. Three final declaration searches performed 168 builds; best result retains 19 register differences. All non-exact conversions were restored. Its 33 distinct successfully built source variants are recorded in the attempts log.

The remaining actual functions and the remaining assembly conversion each have at least three distinct built source attempts. No shared guard side was removed or widened. No configuration, symbol sizes, other translation-unit source, protected tools or baseline reports were changed.

Data remains incomplete in objdiff. Existing weak/deduplicated data and the concatenated source-symbol identity remain unresolved; this run makes no full-unit or linked-completion claim. Two existing instruction-gate branch-normalization artifacts also remain; their objdiff scores are 100%. No symbols or offsets were adjusted to alter their counts.

## Local commits

- 7ebf38b7 match input form cursor marker spacing
- 0d9e4bd0 replace input form calculation assembly with c++
- 9ea85e5a replace row initialization assembly with c++
- fc9db92c preserve row initializer call boundary

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiInputForm] pool: IDENTICAL
[src/keyboard/tiInputForm] objdiff: code 46972/50656 data 908/3772 functions 217/221 fuzzy 99.5623 linked code 0
[src/keyboard/tiInputForm] instruction-exact functions: 215/221
[src/keyboard/tiInputForm]   section .bss size 96 match None
[src/keyboard/tiInputForm]   section .ctors size 4 match 100.0
[src/keyboard/tiInputForm]   section .data size 2736 match 65.53332
[src/keyboard/tiInputForm]   section .rodata size 760 match 100.0
[src/keyboard/tiInputForm]   section .sbss size 32 match 33.333336
[src/keyboard/tiInputForm]   section .sdata size 40 match 100.0
[src/keyboard/tiInputForm]   section .sdata2 size 104 match 100.0
[src/keyboard/tiInputForm]   section .text size 50656 match 99.5623
[src/keyboard/tiInputForm]   below 100: calcCursorPos__Q39textinput9inputform4BaseFff 91.622696
[src/keyboard/tiInputForm]   below 100: create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer 95.02809
[src/keyboard/tiInputForm]   below 100: setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language 96.44726
[src/keyboard/tiInputForm]   below 100: isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv None
[src/keyboard/tiInputForm] baseline: code 45080/50656 data 908 functions 216 fuzzy 99.5591
regressions vs baseline: 0
global matched_code_percent: 87.67423 -> 87.73740
global fuzzy_match_percent: 99.36937 -> 99.36944
global complete_code_percent: 61.81448 -> 61.81448
global matched_data_percent: 91.15570 -> 91.15570
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
