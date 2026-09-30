# PC keyboard attempts

Target: 43U, src/keyboard/tiPcKeyboard. Initial baseline: no source, 0 instruction-exact functions, 0 code/data bytes.

All trials below rebuild only this object. The retained source uses ordinary literals; shared declarations are guarded by TI_PC_KEYBOARD_IMPLEMENTATION. NonMatching remains unchanged.

## textinput::keyboard::pctype::Base::onActive()
Initial: objdiff 82.42857, instructions (133, 119), differing positions 73.
1. use a named KeyState reference: objdiff 82.42857, instructions (133, 119), differing positions 73, pool identical; reverted.
2. separate local declarations and assignments: objdiff 82.42857, instructions (133, 119), differing positions 73, pool identical; reverted.
3. reverse the first if/else direction and exchange its bodies: objdiff 72.27731, instructions (133, 119), differing positions 90, pool identical; reverted.

## textinput::keyboard::pctype::Base::getWCCode(char*)
Initial: objdiff None, instructions (56, 2), differing positions 56.
1. use a named KeyState reference: objdiff None, instructions (56, 2), differing positions 56, pool identical; reverted.
2. hold the returned character in a named local: objdiff None, instructions (56, 2), differing positions 56, pool identical; reverted.
3. use a named KeyState pointer: objdiff None, instructions (56, 2), differing positions 56, pool identical; reverted.

## textinput::keyboard::pctype::Base::getControlKey(char*)
Initial: objdiff 93.333336, instructions (36, 36), differing positions 8.
1. use a named KeyState reference: objdiff 93.333336, instructions (36, 36), differing positions 8, pool identical; reverted.
2. rewrite the first for loop as while with explicit update: objdiff 93.333336, instructions (36, 36), differing positions 8, pool identical; reverted.
3. use a named KeyState pointer: objdiff 93.333336, instructions (36, 36), differing positions 8, pool identical; reverted.

## textinput::keyboard::pctype::Base::sendInputWChar(wchar_t, bool)
Initial: objdiff 98.24074, instructions (107, 108), differing positions 104.
1. use a named KeyState reference: objdiff 94.75, instructions (108, 108), differing positions 26, pool identical; reverted.
2. separate local declarations and assignments: objdiff 98.24074, instructions (107, 108), differing positions 104, pool identical; reverted.
3. use a named KeyState pointer: objdiff 94.75, instructions (108, 108), differing positions 26, pool identical; reverted.

## textinput::keyboard::pctype::Base::updateFixMode()
Initial: objdiff 98.166664, instructions (59, 60), differing positions 32.
1. use a named KeyState reference: objdiff 98.166664, instructions (59, 60), differing positions 32, pool identical; reverted.
2. separate local declarations and assignments: objdiff 98.166664, instructions (59, 60), differing positions 32, pool identical; reverted.
3. use a named KeyState pointer: objdiff 98.166664, instructions (59, 60), differing positions 32, pool identical; reverted.

## textinput::keyboard::pctype::Base::setTranslateMode(textinput::keyboard::pctype::Base::TranslateMode)
Initial: objdiff 98.0, instructions (107, 105), differing positions 89.
1. use a named KeyState reference: objdiff 93.190475, instructions (110, 105), differing positions 103, pool identical; reverted.
2. separate local declarations and assignments: objdiff 98.0, instructions (107, 105), differing positions 89, pool identical; reverted.
3. use a named KeyState pointer: objdiff 93.190475, instructions (110, 105), differing positions 103, pool identical; reverted.

## textinput::keyboard::pctype::Base::KeyState::refresh_()
Initial: objdiff 98.77095, instructions (177, 179), differing positions 152.
1. access members through a named owner pointer: objdiff 98.77095, instructions (177, 179), differing positions 152, pool identical; reverted.
2. reverse the first if/else direction and exchange its bodies: objdiff 84.03911, instructions (177, 179), differing positions 152, pool identical; reverted.
3. hold the switch selector in a named signed local: objdiff 98.77095, instructions (177, 179), differing positions 152, pool identical; reverted.


## textinput::keyboard::pctype::Base::KeyState::refreshText(nw4r::lyt::Pane*)
Initial: objdiff 90.46154, instructions (170, 169), differing positions 107.
1. access members through a named owner pointer: objdiff 90.46154, instructions (170, 169), differing positions 107, pool identical; reverted.
2. rewrite the first for loop as while with explicit update: objdiff 90.46154, instructions (170, 169), differing positions 107, pool identical; reverted.
3. use a 32-bit unsigned loop index: objdiff 83.83432, instructions (170, 169), differing positions 160, pool identical; reverted.


## textinput::keyboard::pctype::Base::KeyState::getWCCode(unsigned long)
Initial: objdiff 98.8, instructions (124, 125), differing positions 109.
1. access members through a named owner pointer: objdiff 98.8, instructions (124, 125), differing positions 109, pool identical; reverted.
2. separate local declarations and assignments: objdiff 98.8, instructions (124, 125), differing positions 109, pool identical; reverted.
3. hold the returned character in a named local: compiler rejected the variant; retained original.

## textinput::keyboard::pctype::Base::KeyState::getWCCode(char*)
Initial: objdiff 96.14035, instructions (56, 57), differing positions 18.
1. access members through a named owner pointer: objdiff 96.14035, instructions (56, 57), differing positions 18, pool identical; reverted.
2. separate local declarations and assignments: objdiff 96.14035, instructions (56, 57), differing positions 18, pool identical; reverted.
3. rewrite the first for loop as while with explicit update: objdiff 96.14035, instructions (56, 57), differing positions 18, pool identical; reverted.

## textinput::keyboard::pctype::LayoutByNW4R::create(MEMAllocator*)
Initial: objdiff 87.49367, instructions (151, 158), differing positions 106.
1. use a named KeyState reference: objdiff 87.49367, instructions (151, 158), differing positions 106, pool identical; reverted.
2. separate local declarations and assignments: objdiff 87.49367, instructions (151, 158), differing positions 106, pool identical; reverted.
3. use a named KeyState pointer: objdiff 87.49367, instructions (151, 158), differing positions 106, pool identical; reverted.

## textinput::keyboard::pctype::LayoutByNW4R::createAnmPane_(MEMAllocator*)
Initial: objdiff 98.515625, instructions (192, 192), differing positions 55.
1. access members through a named owner pointer: objdiff 98.515625, instructions (192, 192), differing positions 55, pool identical; reverted.
2. separate local declarations and assignments: objdiff 98.515625, instructions (192, 192), differing positions 55, pool identical; reverted.
3. rewrite the first for loop as while with explicit update: objdiff 98.515625, instructions (192, 192), differing positions 55, pool identical; reverted.

## textinput::keyboard::pctype::LayoutByNW4R::init()
Initial: objdiff 75.89773, instructions (280, 352), differing positions 336.
1. access members through a named owner pointer: objdiff 75.89773, instructions (280, 352), differing positions 336, pool identical; reverted.
2. use a 32-bit unsigned loop index: objdiff 72.02841, instructions (275, 352), differing positions 347, pool identical; reverted.
3. express a conditional call with a short circuit expression: compiler rejected the variant; retained original.


## textinput::keyboard::pctype::LayoutByNW4R::initLayout()
Initial: objdiff 99.71429, instructions (384, 385), differing positions 66.
1. use a named KeyState reference: objdiff 99.71429, instructions (384, 385), differing positions 66, pool identical; reverted.
2. reverse the first if/else direction and exchange its bodies: objdiff 99.69091, instructions (384, 385), differing positions 71, pool identical; reverted.
3. use a named KeyState pointer: objdiff 99.71429, instructions (384, 385), differing positions 66, pool identical; reverted.

## textinput::keyboard::pctype::LayoutByNW4R::onPressedShift(bool)
Initial: objdiff 90.81633, instructions (45, 49), differing positions 42.
1. use a named KeyState reference: objdiff 90.81633, instructions (45, 49), differing positions 42, pool identical; reverted.
2. use a named KeyState pointer: objdiff 90.81633, instructions (45, 49), differing positions 42, pool identical; reverted.
3. access state through a named Base view: compiler rejected the variant; retained original.


## textinput::keyboard::pctype::LayoutByNW4R::onReleasedShift()
Initial: objdiff 89.871796, instructions (38, 39), differing positions 36.
1. use a named KeyState reference: objdiff 89.871796, instructions (38, 39), differing positions 36, pool identical; reverted.
2. use a named KeyState pointer: objdiff 89.871796, instructions (38, 39), differing positions 36, pool identical; reverted.
3. access state through a named Base view: compiler rejected the variant; retained original.


## textinput::keyboard::pctype::LayoutByNW4R::onKey(unsigned long, void*)
Initial: objdiff 66.72967, instructions (341, 418), differing positions 373.
1. use a named KeyState reference: objdiff 63.64593, instructions (338, 418), differing positions 408, pool identical; reverted.
2. use a named KeyState pointer: objdiff 63.64593, instructions (338, 418), differing positions 408, pool identical; reverted.
3. hold the switch selector in a named signed local: objdiff 66.72967, instructions (341, 418), differing positions 373, pool identical; reverted.


## textinput::keyboard::pctype::LayoutByNW4R::updateFromReceiver(unsigned long, void*)
Initial: objdiff 94.51613, instructions (30, 31), differing positions 16.

## textinput::keyboard::pctype::LayoutByNW4R::cancelStateFocusIn()
Initial: objdiff 60.854168, instructions (144, 144), differing positions 69.
1. access members through a named owner pointer: objdiff 60.854168, instructions (144, 144), differing positions 69, pool identical; reverted.
2. rewrite the first for loop as while with explicit update: objdiff 60.854168, instructions (144, 144), differing positions 69, pool identical; reverted.
3. hold the switch selector in a named signed local: objdiff 60.854168, instructions (144, 144), differing positions 69, pool identical; reverted.


## textinput::keyboard::pctype::LayoutByNW4R::sendInputWChar(wchar_t, bool)
Initial: objdiff 93.97727, instructions (42, 44), differing positions 35.
1. use a named KeyState reference: objdiff 93.97727, instructions (42, 44), differing positions 35, pool identical; reverted.
2. separate local declarations and assignments: objdiff 93.97727, instructions (42, 44), differing positions 35, pool identical; reverted.
3. use a named KeyState pointer: objdiff 93.97727, instructions (42, 44), differing positions 35, pool identical; reverted.

## textinput::keyboard::pctype::LayoutByNW4R::setInputModeJP(bool, unsigned long, unsigned long)
Initial: objdiff 86.92208, instructions (69, 77), differing positions 36.
1. use a named KeyState reference: objdiff 79.96104, instructions (72, 77), differing positions 71, pool identical; reverted.
2. use a named KeyState pointer: objdiff 79.96104, instructions (72, 77), differing positions 71, pool identical; reverted.
3. hold the switch selector in a named signed local: objdiff 86.92208, instructions (69, 77), differing positions 36, pool identical; reverted.


## textinput::keyboard::pctype::LayoutByNW4R::updateInput(int, float, float, unsigned long, unsigned long, unsigned long, void*)
Initial: objdiff 60.17143, instructions (135, 140), differing positions 101.
1. separate local declarations and assignments: objdiff 60.17143, instructions (135, 140), differing positions 101, pool identical; reverted.
2. reverse the first if/else direction and exchange its bodies: objdiff 95.25, instructions (135, 140), differing positions 92, pool identical; retained.
3. express a conditional call with a short circuit expression: objdiff 88.96429, instructions (140, 140), differing positions 59, pool identical; reverted.


## textinput::keyboard::pctype::LayoutByNW4R::updateInput(textinput::input::HKBManager&)
Initial: objdiff 84.687225, instructions (237, 227), differing positions 219.
1. access members through a named owner pointer: objdiff 84.687225, instructions (237, 227), differing positions 219, pool identical; reverted.
2. separate local declarations and assignments: objdiff 84.687225, instructions (237, 227), differing positions 219, pool identical; reverted.
3. reverse the first if/else direction and exchange its bodies: objdiff 74.48458, instructions (237, 227), differing positions 219, pool identical; reverted.

## textinput::keyboard::pctype::EventHandler::onTiEvent(textinput::gui::PaneComponent*, unsigned long, textinput::nw4rmanager::TiEventHandler::Input*)
Initial: objdiff 88.83249, instructions (196, 197), differing positions 176.
1. access members through a named owner pointer: objdiff 88.83249, instructions (196, 197), differing positions 176, pool identical; reverted.
2. separate local declarations and assignments: objdiff 88.83249, instructions (196, 197), differing positions 176, pool identical; reverted.

3. hold the switch selector in a named signed local: objdiff 88.83249, instructions (196, 197), differing positions 176, pool identical; reverted.


## @236@onEvent__Q49textinput8keyboard6pctype12LayoutByNW4RFPQ49textinput8keyboard6pctype5
The extracted target thunk name is truncated; MWCC emits the complete canonical C++ name. Symbol metadata was left unchanged.
1. early return for unrelated events: objdiff None, canonical thunk instructions 2/2, differing positions 0; target name remains absent. Reverted.
2. signed switch for listener events: objdiff None, canonical thunk instructions 2/2, differing positions 0; target name remains absent. Reverted.
3. named sound identifier before dispatch: objdiff None, canonical thunk instructions 2/2, differing positions 0; target name remains absent. Reverted.


Additional trial for textinput::keyboard::pctype::Base::KeyState::getWCCode(unsigned long): copy the final mapped character into a distinct return local; objdiff 98.8, instructions (124, 125), differing positions 109; reverted.

Additional trial for textinput::keyboard::pctype::LayoutByNW4R::init(): use mutable local vectors for the mode-selector positions; objdiff 75.89773, instructions (280, 352), differing positions 336; reverted.

## Final evidence
Clean full gate: GATE PASS. DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d. Regressions, forbidden additions, readability warnings: 0. Pool: 204/204 identical.
Instruction-exact 0 -> 120/141; objdiff code 0 -> 16240/28484; data 0 -> 5964/18564. .rodata: 100%; unit remains NonMatching.
Additional retained refinements: merge address-taken boolean command values in Base::onActive using typed single-field command structs (119/119 instructions, diffs 0); use signed switch dispatch in updateFromReceiver and updateFixMode (31/31 and 60/60, diffs 0); restore cancelStateFocusIn switch case order (144/144, diffs 0); restore normal/shift/toggle/onoff creation order (192/192, register differences remain); put ordinary Korean lookup tables after animation data (.rodata 100%).
The protected default branch in Base::setTranslateMode returns for invalid enum values. The original appears to use an unset temporary outside 0..2; this implementation deliberately retains defined behavior.

textinput::keyboard::pctype::Base::getWCCode(char*): objdiff None; src 0xe0 base 0x8 insns 56/2 | --- replace mine 0:56 base 0:2 |   M    0 stwu r1, -0x20(r1) |   M    1 mflr r0

textinput::keyboard::pctype::Base::getControlKey(char*): objdiff 93.333336; src 0x90 base 0x90 insns 36/36 | diffs 8: [4, 5, 10, 12, 15, 21, 24, 25] |      4 M stw r30, 0x18(r1) |        B li r31, 0

textinput::keyboard::pctype::Base::sendInputWChar(wchar_t, bool): objdiff 98.24074; src 0x1ac base 0x1b0 insns 107/108 | --- insert mine 4:4 base 4:5 |   B    4 li r0, 0 | --- replace mine 10:11 base 11:12

textinput::keyboard::pctype::Base::setTranslateMode(textinput::keyboard::pctype::Base::TranslateMode): objdiff 98.0; src 0x1ac base 0x1a4 insns 107/105 | --- replace mine 13:14 base 13:14 |   M   13 b 348 |   B   13 b 36

textinput::keyboard::pctype::Base::KeyState::refresh_(): objdiff 98.77095; src 0x2c4 base 0x2cc insns 177/179 | --- replace mine 26:27 base 26:27 |   M   26 bgt 48 |   B   26 bgt 56

textinput::keyboard::pctype::Base::KeyState::refreshText(nw4r::lyt::Pane*): objdiff 90.46154; src 0x2a8 base 0x2a4 insns 170/169 | --- replace mine 50:52 base 50:51 |   M   50 beq 192 |   M   51 stw r25, 0xc(r1)

textinput::keyboard::pctype::Base::KeyState::getWCCode(unsigned long): objdiff 98.8; src 0x1f0 base 0x1f4 insns 124/125 | --- replace mine 2:3 base 2:3 |   M    2 li r8, 0 |   B    2 li r7, 0

textinput::keyboard::pctype::Base::KeyState::getWCCode(char*): objdiff 96.14035; src 0xe0 base 0xe4 insns 56/57 | --- replace mine 34:35 base 34:35 |   M   34 beq 48 |   B   34 beq 52

textinput::keyboard::pctype::LayoutByNW4R::create(MEMAllocator*): objdiff 87.49367; src 0x25c base 0x278 insns 151/158 | --- replace mine 42:43 base 42:45 |   M   42 mr r29, r31 |   B   42 mr r26, r31

textinput::keyboard::pctype::LayoutByNW4R::createAnmPane_(MEMAllocator*): objdiff 98.515625; src 0x300 base 0x300 insns 192/192 | diffs 55: [19, 22, 23, 24, 40, 44, 48, 50, 51, 52, 53, 55, 56, 57, 63, 67, 71, 73, 74, 75] |     19 M li r22, 0 |        B li r21, 0

textinput::keyboard::pctype::LayoutByNW4R::init(): objdiff 75.89773; src 0x460 base 0x580 insns 280/352 | --- replace mine 0:1 base 0:1 |   M    0 stwu r1, -0x40(r1) |   B    0 stwu r1, -0x60(r1)

textinput::keyboard::pctype::LayoutByNW4R::initLayout(): objdiff 99.71429; src 0x600 base 0x604 insns 384/385 | --- replace mine 317:318 base 317:318 |   M  317 bne 196 |   B  317 bne 200

textinput::keyboard::pctype::LayoutByNW4R::onPressedShift(bool): objdiff 90.81633; src 0xb4 base 0xc4 insns 45/49 | --- insert mine 7:7 base 7:8 |   B    7 lwz r0, 0x20(r3) | --- replace mine 8:11 base 9:13

textinput::keyboard::pctype::LayoutByNW4R::onReleasedShift(): objdiff 89.871796; src 0x98 base 0x9c insns 38/39 | --- delete mine 3:4 base 3:3 |   M    3 li r0, -0x90 | --- replace mine 6:9 base 5:10

textinput::keyboard::pctype::LayoutByNW4R::onKey(unsigned long, void*): objdiff 66.72967; src 0x554 base 0x688 insns 341/418 | --- replace mine 18:19 base 18:19 |   M   18 bne 1244 |   B   18 bne 1552

textinput::keyboard::pctype::LayoutByNW4R::sendInputWChar(wchar_t, bool): objdiff 93.97727; src 0xa8 base 0xb0 insns 42/44 | --- replace mine 9:10 base 9:11 |   M    9 rlwinm. r31, r0, 0x19, 0x1f, 0x1f |   B    9 rlwinm. r0, r0, 0, 0x18, 0x18

textinput::keyboard::pctype::LayoutByNW4R::setInputModeJP(bool, unsigned long, unsigned long): objdiff 86.92208; src 0x114 base 0x134 insns 69/77 | --- insert mine 31:31 base 31:34 |   B   31 cmpwi r30, 1 |   B   32 beq 76

textinput::keyboard::pctype::LayoutByNW4R::updateInput(int, float, float, unsigned long, unsigned long, unsigned long, void*): objdiff 95.25; src 0x21c base 0x230 insns 135/140 | --- replace mine 33:34 base 33:34 |   M   33 beq 196 |   B   33 beq 212

textinput::keyboard::pctype::LayoutByNW4R::updateInput(textinput::input::HKBManager&): objdiff 84.687225; src 0x3b4 base 0x38c insns 237/227 | --- replace mine 0:1 base 0:1 |   M    0 stwu r1, -0x70(r1) |   B    0 stwu r1, -0x60(r1)

textinput::keyboard::pctype::EventHandler::onTiEvent(textinput::gui::PaneComponent*, unsigned long, textinput::nw4rmanager::TiEventHandler::Input*): objdiff 88.83249; src 0x310 base 0x314 insns 196/197 | --- replace mine 17:18 base 17:18 |   M   17 bne 692 |   B   17 bne 696

@236@onEvent__Q49textinput8keyboard6pctype12LayoutByNW4RFPQ49textinput8keyboard6pctype5: objdiff None; target name absent; canonical thunk name differs

## Third pass (setTranslateMode solved, updateInput narrowing)
- setTranslateMode: SOLVED 105/105 diffs 0 — `u32 keyMode;` declared UNINITIALIZED with 3-case
  switch and NO default: invalid-mode paths reach the compare with stale r31 (original UB).
- updateInput(HKBManager&): 227/227 insns, 1 diff @109 — base clrlwi r26,r3 (s16->u16
  conversion materialized) vs mine mr; MWCC lazy-width elides the mask since the lha value
  is already provably 16-bit. Tried: wchar_t/u16/int/u16-code/&0xFFFF/(u16) casts —
  all elided or regressed. Documented lazy-width tie-break.
- @236@onEvent thunk: present in mine (8B, addi+b) but base symtab name is TRUNCATED
  mid-mangle ("...pctype5" ~87 chars, no UIObjUlPv tail) — extraction name cap,
  unmatchable by name. Same family as fused-name artifact.
- Data: .rodata/.data/.sdata2 byte-identical; .sdata/.bss/.sbss differ only by trailing
  zero pads (name/pad family). matched_data 32% is a name-pairing artifact.
- Unit state: 136/141 fns 100; getControlKey/onPressedShift/onReleasedShift remain
  documented reg-permutation tie-breaks (5+ forms each).
