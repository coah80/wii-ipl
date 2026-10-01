# Structural matching round 4

| Unit | Instruction-exact functions | Objdiff matched code bytes | Objdiff matched data bytes |
| --- | --- | --- | --- |
| `src/scene/sdChannelSelect/iplSDChannelSelect` | 116/129 -> 117/129 | 26472 -> 27108 / 33828 | 224 -> 224 / 2960 |
| `src/keyboard/tiCandidateBox` | 104/112 -> 108/112 | 17996 -> 19988 / 24000 | 1132 -> 1132 / 4652 |
| `src/keyboard/tiCellPhone` | 83/86 -> 83/86 | 12824 -> 12824 / 19028 | 3860 -> 3860 / 3860 |

## New exact functions

- `drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv`: objdiff 100.0%; src 0x27c base 0x27c insns 159/159; diffs 0: [].
- `GetNextPageIdx___Q39textinput12candidatebox10UITextAreaCFl`: objdiff 100.0%; src 0x208 base 0x208 insns 130/130; diffs 0: [].
- `GetPrevPageIdx___Q39textinput12candidatebox10UITextAreaCFl`: objdiff 100.0%; src 0x204 base 0x204 insns 129/129; diffs 0: [].
- `StartScroll__Q39textinput12candidatebox10UITextAreaFl`: objdiff 100.0%; src 0x2e4 base 0x2e4 insns 185/185; diffs 0: [].
- `StartScrollToIdx__Q39textinput12candidatebox10UITextAreaFl`: objdiff 100.0%; src 0x2e0 base 0x2e0 insns 184/184; diffs 0: [].

## Remaining functions, in unit and object order

| Function | Objdiff | Successful logged trials | Remaining difference |
| --- | --- | --- | --- |
| `create__Q33ipl5scene15SDChannelSelectFv` | 97.73972% | 3 | BS2 loop manager reload and data-base lifetime; 145/146 instructions. |
| `handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv` | 99.15205% | 6 | Time guard needs beq plus branch; titleId/channelCount homes differ; 170/171 instructions. |
| `collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl` | 97.81188% | 7 | Count update and threshold/stack load scheduling, four differences. |
| `collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl` | 97.833336% | 7 | Count update and threshold/stack load scheduling, four differences. |
| `collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl` | 97.29365% | 6 | Count update scheduling plus title/page/index register homes, 22 differences. |
| `collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl` | 97.55125% | 4 | Count update scheduling in four blocks, 16 differences. |
| `flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv` | 99.65714% | 3 | Heap and savedata argument loads reversed, two differences. |
| `calcCommon__Q33ipl5scene15SDChannelSelectFv` | 99.07407% | 3 | Target omits optOutEvent r5 default initialization; source preserves the declared ABI. |
| `initializeNormalPage__Q33ipl5scene15SDChannelSelectFv` | 98.93617% | 3 | Target omits optOutEvent r5 default initialization; source preserves the declared ABI. |
| `selectChannel__Q33ipl5scene15SDChannelSelectFii` | 98.305084% | 3 | Target omits optOutEvent r5 default initialization; source preserves the declared ABI. |
| `setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj` | 93.4721% | 4 | Projection/scissor FP operand ordering, conversion scheduling and register homes, 68 differences. |
| `onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface` | 98.541664% | 3 | Event branch form and missing target r5 default initialization. |
| `create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator` | 92.71023% | 3 | Inline pane initialization cursor, button helper string lifetimes; 351/352 instructions. |
| `createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator` | 96.56481% | 3 | Animation table reload boundaries and saved-register homes; 214/216 instructions. |
| `CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv` | 99.873566% | 14 | Inline string width versus height FP homes, 11 differences. |
| `onGUIEvent__Q39textinput12candidatebox10UITextAreaFRQ39textinput3gui13PaneComponentUlPQ49textinput11nw4rmanager14TiEventHandler5Input` | 100.0% | 3 | Objdiff 100%; odiff incorrectly subtracts function address from CR operands on two branches. The gate instruction count is conservative. |
| `onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv` | 99.67009% | 7 | Inlined key search cursor/offset and pane/state saved-register homes, 37 differences. |
| `create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator` | 99.8949% | 7 | Toggle-pane record and inner-animation offset saved-register homes, seven differences. |
| `init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv` | 98.52612% | 4 | Layout this, zero/T and loop pointer/offset saved-register homes, 155 differences. |

## Validation

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 27108/33828 data 224/2960 functions 117/129 fuzzy 99.5051 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 117/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 99.50514
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 97.73972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.29365
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.55125
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.4721
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 98.541664
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 26472/33828 data 224 functions 116 fuzzy 99.4179
[src/keyboard/tiCandidateBox] pool: IDENTICAL
[src/keyboard/tiCandidateBox] objdiff: code 19988/24000 data 1132/4652 functions 109/112 fuzzy 99.4395 linked code 0
[src/keyboard/tiCandidateBox] instruction-exact functions: 108/112
[src/keyboard/tiCandidateBox]   section .ctors size 4 match 100.0
[src/keyboard/tiCandidateBox]   section .data size 3488 match 99.27954
[src/keyboard/tiCandidateBox]   section .rodata size 1048 match 100.0
[src/keyboard/tiCandidateBox]   section .sdata size 32 match 96.875
[src/keyboard/tiCandidateBox]   section .sdata2 size 80 match 100.0
[src/keyboard/tiCandidateBox]   section .text size 24000 match 99.4395
[src/keyboard/tiCandidateBox]   below 100: create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator 92.71023
[src/keyboard/tiCandidateBox]   below 100: createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator 96.56481
[src/keyboard/tiCandidateBox]   below 100: CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv 99.873566
[src/keyboard/tiCandidateBox] baseline: code 17996/24000 data 1132 functions 106 fuzzy 99.4112
[src/keyboard/tiCellPhone] pool: IDENTICAL
[src/keyboard/tiCellPhone] objdiff: code 12824/19028 data 3860/3860 functions 83/86 fuzzy 99.7793 linked code 0
[src/keyboard/tiCellPhone] instruction-exact functions: 83/86
[src/keyboard/tiCellPhone]   section .ctors size 4 match 100.0
[src/keyboard/tiCellPhone]   section .data size 2416 match 100.0
[src/keyboard/tiCellPhone]   section .rodata size 1320 match 100.0
[src/keyboard/tiCellPhone]   section .sdata size 112 match 100.0
[src/keyboard/tiCellPhone]   section .sdata2 size 8 match 100.0
[src/keyboard/tiCellPhone]   section .text size 19028 match 99.779274
[src/keyboard/tiCellPhone]   below 100: onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv 99.67009
[src/keyboard/tiCellPhone]   below 100: create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator 99.8949
[src/keyboard/tiCellPhone]   below 100: init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv 98.52612
[src/keyboard/tiCellPhone] baseline: code 12824/19028 data 3860 functions 83 fuzzy 99.7793
regressions vs baseline: 0
global matched_code_percent: 86.74680 -> 86.83454
global fuzzy_match_percent: 99.31120 -> 99.31242
global complete_code_percent: 60.61288 -> 60.61288
global matched_data_percent: 91.11031 -> 91.11031
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

All existing shared keyboard header guard sides remain intact. The new CandidateBox helper is enabled only by its own translation unit. The units remain NonMatching; no configure, symbol-size, section-placement or other-unit source changes were made.

The onGUIEvent entry is a checker limitation, not an objdiff failure. The unchanged SD default-argument mismatch has no demonstrated readable C++ solution with the current ABI. The residual data bytes were preserved; identical string pools alone do not prove every data section exact.

## Source commits

c11d586e match candidate scroll margin helper
85c1e3ae pass scroll displacement to animation callback
b893fd2f replace forward page index assembly with c
bc0ac0c5 match backward page scale helper boundary
2d0b4e65 match sd channel transition state switches
