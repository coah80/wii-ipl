# PC keyboard fifth pass

Baseline: 131/141 instruction-exact functions, 24244 code bytes, 5972 data bytes. Existing string pool and .rodata match. This pass changes code and data only; configure.py remains unchanged.

## LayoutByNW4R::updateInput HKBManager
Start: (99.73568, (227, 227, 1, 0.9955947136563876)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. choose caps-normalized Korean scalar with conditional expression: (97.53304, (228, 227, 145, 0.9010989010989011)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. normalize letter case as a wchar before table conversion: (97.95154, (227, 227, 21, 0.9383259911894273)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. explicitly assign conversion in all letter mapping branches: (99.18502, (228, 227, 131, 0.9362637362637363)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::create
Start: (99.082275, (158, 158, 27, 0.8291139240506329)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. extract repeated modifier setup into inline member with literals: (99.81013, (158, 158, 6, 0.9620253164556962)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool diverged; reverted.
2. pass locally named modifier strings to inline member: (99.082275, (158, 158, 27, 0.8291139240506329)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. reuse locally named strings with inline member: (97.37342, (158, 158, 31, 0.7151898734177216)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::create
Start: (99.082275, (158, 158, 27, 0.8291139240506329)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. inline setup takes layout, pane name, bounding name: (100.0, (158, 158, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. inline setup takes pane name, bounding name, layout: (94.93671, (158, 158, 13, 0.9746835443037974)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. inline setup takes pane name, layout, bounding name: (97.46835, (158, 158, 10, 0.9873417721518988)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::setTranslateMode
Start: (99.04762, (106, 105, 99, 0.995260663507109)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. initialize fallback with a 16-bit enum conversion: (99.04762, (106, 105, 101, 0.995260663507109)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. switch with an unsigned scalar and preserve defined enum fallback: (99.04762, (106, 105, 99, 0.995260663507109)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. convert enum using explicit if chain: (90.209526, (103, 105, 99, 0.9038461538461539)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::getWCCode u32 index
Start: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. bind modifier flags to const value before tests: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. declare character before calculating modifier bits: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. explicitly select table entry after input-type evaluation: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::refresh_
Start: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. normalize invalid kana mode through named current and desired values: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=12, .rodata=5816; pool identical; reverted.
2. select language data using a switch: (98.156425, (178, 179, 152, 0.9467787114845938)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. name input mode before dispatching commands: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::getControlKey
Start: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. continue on an unmatched pane name before returning the key: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. dispatch match Boolean through a switch: (90.388885, (37, 36, 25, 0.7123287671232876)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use signed 16-bit traversal index: (47.36111, (38, 36, 30, 0.7027027027027027)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onPressedShift
Start: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. share shift button state and animation in an inline member: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. select shift animation event with conditional expression: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. select shift animation using the stored button state: (94.89796, (47, 49, 41, 0.8125)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.

## LayoutByNW4R::onPressedShift
Start: (94.89796, (47, 49, 41, 0.8125)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. obtain shift flags through const modifier getter: (99.081635, (49, 49, 9, 0.8163265306122449)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. obtain all flags through const getter then mask: (99.081635, (49, 49, 9, 0.8163265306122449)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. obtain shift flags through mutable modifier getter: (94.89796, (47, 49, 41, 0.8125)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onReleasedShift
Start: (77.17949, (41, 39, 37, 0.7)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. name the shift button pointer before refreshing key flags: (77.17949, (41, 39, 37, 0.7)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. separate mode clearing from shift-bit clearing: (78.07692, (40, 39, 35, 0.7088607594936709)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. guard the released state with an early return: (77.17949, (41, 39, 37, 0.7)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput int chan
Start: (93.89286, (141, 140, 43, 0.8754448398576512)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare retained handling result before invoking the layout: (93.89286, (141, 140, 43, 0.8754448398576512)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. name the held hardware shift bit before testing it: (93.89286, (141, 140, 43, 0.8754448398576512)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use an early return after processing the held shift branch: (91.57143, (142, 140, 62, 0.8581560283687943)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onEvent
Start: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. handle sound event using an unsigned switch: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. convert sound payload through a named integer: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. bind the event observer before calling its sound handler: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onReleasedShift
Start: (78.07692, (40, 39, 35, 0.7088607594936709)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. clear shift bit from flags returned by const getter: (79.23077, (42, 39, 31, 0.6419753086419753)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. name const getter result before clearing shift: (86.02564, (42, 39, 24, 0.7160493827160493)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. use const getter with direct released animation body: (92.051285, (39, 39, 15, 0.717948717948718)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.

## Base::KeyState::refresh_
Start: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. query ABC mode through const getter at every decision: compiler rejected; reverted.                                ^^^^^^^^^^ #   (10114) '(' expected #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
2. query ABC mode through const getter in normalization guard: (100.0, (179, 179, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. query ABC mode through const getter in normalized-state check: (99.88827, (179, 179, 4, 0.9776536312849162)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onPressedShift
Start: (99.081635, (49, 49, 9, 0.8163265306122449)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. name complete pressed modifier flags before setter call: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. update named getter result with shift bit separately: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. bind complete pressed modifier flags to const local: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::getWCCode u32 index
Start: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. query direct and Chinese ABC modes through const getter: (100.0, (125, 125, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. query only direct-input ABC mode through const getter: (100.0, (125, 125, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. query only Chinese ABC mode through const getter: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onPressedShift
Start: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. reuse modifier state helper for dynamic caps and shift with unsigned off animation: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. reuse modifier state helper with signed off animation: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. reuse modifier state helper with explicit on and off animations: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

Source review retained the general SetState helper with an unsigned off-animation argument after rechecking all function percentages: no change to any function score, pool identical, onPressedCaps remains exact. The helper now also handles the real dynamic caps state, including both enabled and disabled values. The earlier trial runner reverted this equivalent improvement only because its instruction metric was unchanged.

## LayoutByNW4R::onPressedShift
Start: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. bind key state before querying pressed flags: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. declare flags before querying and combining modifiers: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. bind modifier animation button before updating flags: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onReleasedShift
Start: (92.051285, (39, 39, 15, 0.717948717948718)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. clear the shift bit in a separate statement after const getter: (98.84615, (39, 39, 8, 0.7948717948717948)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. clear shift using an explicitly unsigned mask: (92.051285, (39, 39, 15, 0.717948717948718)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. pass separately named getter flags directly to setter: (91.666664, (40, 39, 34, 0.6835443037974683)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onPressedShift
Start: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. name full getter flags then mask before returning: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. name masked getter flags before returning: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. declare getter flags before assigning masked value: (99.081635, (49, 49, 8, 0.8367346938775511)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput int chan
Start: (99.92857, (140, 140, 2, 0.9857142857142858)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. keep getter flags and pressed bit assignment separate in inline handler: (100.0, (140, 140, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. make inline pressed flags local const: (99.92857, (140, 140, 2, 0.9857142857142858)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. pass inline pressed getter flags directly to setter: (99.92857, (140, 140, 2, 0.9857142857142858)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Final code and data review

New instruction-exact functions: LayoutByNW4R::create, 158 instructions; KeyState::refresh_, 179; KeyState::getWCCode(u32), 125; LayoutByNW4R::updateInput(int,...), 140. Each has 100% objdiff and ctxdiff reports zero differences. The const mode getter restores the independently inlined flag reads. Shared modifier creation preserves the target base conversions and original string pool. SetState is a general helper actually used by both the pressed shift and dynamic caps paths; the latter exercises both state values with its real off-animation value. onPressedCaps remains exact at 92 instructions. All exact functions at entry remain exact.

Every one of the ten functions unmatched at entry has at least three distinct compiling source-level attempts recorded this pass. Compiler failures and transformations that failed to apply are not counted. A final proposed inline-handler lifetime trial did not apply after the handler had already changed, was rejected before writing either source file, and is excluded.

Raw section audit checked ELF bytes directly. .data: 12576/12576 bytes, no differences. .rodata: 5816/5816 bytes, no differences. .sdata2: 8/8 bytes, no differences. .sdata: 133/136 bytes, equal common bytes and an all-zero three-byte target suffix. .bss: 12/16 bytes and .sbss: 5/8 bytes, with equal zero contents. Both versions align these sections to eight bytes. The string pool has 204 identical entries. Ordinary tables, positions, and vtable offsets remain in target order. Canonical .data relocation audit found equal sites for all 1303 relocations and equal destinations for 1302. The only destination-name difference remains .data+0x2fb8, the truncated onEvent thunk. No literal blobs, pinned addresses, extra data, or configuration changes were introduced.

.data objdiff remains 74.95624 despite raw byte equality; symbol correspondence is a possible cause, not a proven explanation. The anonymous twelve-byte .bss object is passed to __register_global_object from inlined LayoutGather::Singleton::getInstance. Runtime DestructorChain has three pointer fields, explaining its source size. The four-byte target suffix is consistent with section alignment, without establishing how extraction assigned those bytes.

The modified implementation header is included only through TI_PC_KEYBOARD_IMPLEMENTATION, defined by this .cpp alone. configure.py remains NonMatching and unchanged. Final object measures: {'fuzzy_match_percent': 99.90311, 'total_code': '28484', 'matched_code': '26652', 'matched_code_percent': 93.56832, 'total_data': '18564', 'matched_data': '5972', 'matched_data_percent': 32.169792, 'total_functions': 141, 'matched_functions': 135, 'matched_functions_percent': 95.74468, 'total_units': 1}

getControlKey__Q49textinput8keyboard6pctype4BaseFPc: 93.333336; (36, 36, 8, 0.8055555555555556)
setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode: 99.04762; (106, 105, 99, 0.995260663507109)
onPressedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFb: 99.081635; (49, 49, 8, 0.8367346938775511)
onReleasedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFv: 98.84615; (39, 39, 8, 0.7948717948717948)
updateInput__Q49textinput8keyboard6pctype12LayoutByNW4RFRQ39textinput5input10HKBManager: 99.73568; (227, 227, 1, 0.9955947136563876)
@236@onEvent__Q49textinput8keyboard6pctype12LayoutByNW4RFPQ49textinput8keyboard6pctype5: None; (0, 0, 100000, 0)

Full final gate: GATE PASS. Zero other-unit output regressions, zero forbidden-pattern additions, zero readability warnings.
[src/keyboard/tiPcKeyboard] objdiff: code 26652/28484 data 5972/18564 functions 135/141 fuzzy 99.9031 linked code 0
[src/keyboard/tiPcKeyboard] instruction-exact functions: 135/141
