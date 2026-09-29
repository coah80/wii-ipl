# PC keyboard third pass

Baseline: 123/141 instruction-exact functions, 20128 code bytes, 5972 data bytes. Existing string pool and .rodata match. This pass changes code and data only; configure.py remains unchanged.

## LayoutByNW4R::init
Start: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. group both coordinate records and pane vectors in a language-position structure: (98.14773, (358, 352, 224, 0.8985915492957747)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. copy selector records into one two-element position array: (97.619316, (359, 352, 239, 0.9310829817158931)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. scope language positions independently from the remaining layout initialization: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::getWCCode char*
Start: (96.14035, (56, 57, 18, 0.9203539823008849)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. choose the grid variant with a conditional selector: (100.0, (57, 57, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. name the negative mode index before adding the grid variant base: (98.22807, (56, 57, 16, 0.9380530973451328)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. write the matched grid variant as explicit mode branches: (81.03509, (57, 57, 33, 0.43859649122807015)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::setTranslateMode
Start: (99.04762, (106, 105, 99, 0.995260663507109)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. use direct as the initialized fallback mode: (99.04762, (106, 105, 101, 0.995260663507109)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. join the direct and fallback switch labels: (98.0, (103, 105, 96, 0.9519230769230769)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. keep the mode enum itself as the mutable switch result: (99.04762, (106, 105, 99, 0.995260663507109)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::sendInputWChar
Start: (98.24074, (107, 108, 104, 0.9488372093023256)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. mask incoming conversion flags when merging them into the stored mode: (99.02778, (107, 108, 104, 0.986046511627907)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. clear rejection after modifier calculation and mask conversion flags: (92.59259, (108, 108, 18, 0.9722222222222222)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. clear rejection before declaring modifier flags and mask conversion flags: (100.0, (108, 108, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.

## Base::KeyState::getWCCode u32
Start: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. scope modifier calculation separately from punctuation-mode evaluation: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. compute the character through a named ASCII record pointer: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. evaluate direct input mode before its punctuation mapping: (95.48, (128, 125, 116, 0.9011857707509882)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::refresh_
Start: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. test the normalized mode before checking its language range: (97.994415, (177, 179, 156, 0.9550561797752809)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. select the language table through a single conditional expression: (91.480446, (174, 179, 148, 0.8781869688385269)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. compute normalized flags before assigning the stored mode: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::createAnmPane_
Start: (98.515625, (192, 192, 55, 0.7135416666666666)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. use a typed table-row pointer instead of a reference: (98.515625, (192, 192, 55, 0.7135416666666666)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. declare shared-pane storage before the outer loop: (100.0, (192, 192, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. write the outer table traversal as a while loop: (98.515625, (192, 192, 55, 0.7135416666666666)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::getControlKey
Start: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. name the comparison result before branching on a control: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. declare the table index outside the loop initialization: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use an explicit unsigned comparison for the name-match result: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::getWCCode
Start: (None, (57, 2, 57, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. call the key-state lookup through its explicitly qualified class: (None, (57, 2, 57, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. hold the pane name in a local before forwarding: (None, (57, 2, 57, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use a member-function pointer to forward the lookup: (None, (18, 2, 18, 0.1)); .data=12584, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::setInputModeJP
Start: (86.92208, (69, 77, 36, 0.8493150684931506)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. give the two kana input modes separate switch bodies: (79.09091, (77, 77, 21, 0.8571428571428571)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. restore direct, roman, kana switch body order: (100.0, (77, 77, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. restore switch body order with unsigned mode dispatch: (100.0, (77, 77, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::sendInputWChar
Start: (95.22727, (42, 44, 35, 0.9302325581395349)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. record consumed shift state after retrieving its last pane: (100.0, (44, 44, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. record shift state before retrieving its last pane: (95.454544, (44, 44, 5, 0.9772727272727273)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use an integer shift-state result assigned in the active branch: (100.0, (44, 44, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## EventHandler::onTiEvent
Start: (88.862946, (196, 197, 176, 0.8702290076335878)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. restore event switch body order to press, release, focus: (99.44163, (196, 197, 176, 0.9872773536895675)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. switch on bounding-pane prefix with the target event body order: (98.88325, (197, 197, 5, 0.9847715736040609)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. split the modifier exclusion tests before bounding-pane dispatch: compiler rejected; reverted.                 ^^^^^^^ #   (10140) undefined identifier 'AnmPane' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

## LayoutByNW4R::onPressedShift
Start: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare the modifier setter inline in the owned header: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. select the pressed animation through the stored button state: (94.89796, (47, 49, 41, 0.8125)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. separate shift-mask construction from the lower mode nibble: (90.71429, (45, 49, 42, 0.8085106382978723)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onReleasedShift
Start: (90.0, (38, 39, 35, 0.7792207792207793)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. clear mode then shift in two named modifier steps: (90.89744, (37, 39, 34, 0.7894736842105263)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. keep the cleared modifier in a const local: (90.0, (38, 39, 35, 0.7792207792207793)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. load button state before the modifier update and retain the later live check: (79.97436, (43, 39, 40, 0.6341463414634146)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## EventHandler::onTiEvent
Start: (99.44163, (196, 197, 176, 0.9872773536895675)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. switch on the caps-exclusion result before testing the pane prefix: (100.0, (197, 197, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. name the caps-exclusion result before switch dispatch: (100.0, (197, 197, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. join failed exclusion checks through a shared function return: (100.0, (197, 197, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::getControlKey
Start: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare a full-width control table index before the loop: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. use a 16-bit cached control index declared before the loop: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. name the control table index inside each iteration: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::create
Start: (87.49367, (151, 158, 106, 0.7637540453074434)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare the pane manager before constructing the event handler: (87.49367, (151, 158, 106, 0.7637540453074434)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. retain a typed reference to each modifier while wiring its components: (87.49367, (151, 158, 106, 0.7637540453074434)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. name the listener pointers before attaching each bounding component: (87.49367, (151, 158, 106, 0.7637540453074434)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput int chan
Start: (95.78571, (136, 140, 91, 0.855072463768116)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. cache the hardware keyboard manager before changing shift state: (90.10714, (134, 140, 105, 0.8102189781021898)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. branch on the held-shift mask through an integer switch: (94.28571, (138, 140, 65, 0.841726618705036)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. name the released shift state before invoking its handler: (92.77143, (136, 140, 91, 0.8115942028985508)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput HKBManager
Start: (89.07929, (239, 227, 230, 0.6952789699570815)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. provide a memberwise KeySet copy constructor within the implementation-only guard: (91.18943, (233, 227, 211, 0.8304347826086956)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. dispatch triggered control keys through a signed switch: (91.21586, (242, 227, 234, 0.7249466950959488)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use a full-width converted character and 16-bit Korean map indices: (86.14978, (237, 227, 229, 0.6508620689655172)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onEvent
Start: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. dispatch listener events through a signed integer switch: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. return early before converting the sound payload: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. forward a named sound identifier inside the handled-event scope: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput HKBManager
Start: (91.18943, (233, 227, 211, 0.8304347826086956)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. combine copy elision with target triggered-key switch dispatch: (94.00881, (236, 227, 150, 0.8596112311015118)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. keep the Korean character scalar scoped to its conversion block: (93.37004, (232, 227, 208, 0.9019607843137255)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. combine target triggered-key dispatch with the scoped Korean scalar: (96.18943, (235, 227, 48, 0.9437229437229437)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.

## Base::getControlKey
Start: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. join the found key and fallback through one return: (69.97222, (33, 36, 33, 0.37681159420289856)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. write the control traversal as an explicit infinite loop with a bound break: (90.55556, (37, 36, 20, 0.7397260273972602)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. hold the result in a local initialized at the match and exit through a label: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput HKBManager
Start: (96.18943, (235, 227, 48, 0.9437229437229437)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. share the delete animation across repeated delete and backspace cases: (99.73568, (227, 227, 1, 0.9955947136563876)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. share repeated delete handling and explicitly narrow the converted Korean character: (99.73568, (227, 227, 1, 0.9955947136563876)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. share repeated delete handling and keep the outer character full-width until its final conversion: (95.66079, (227, 227, 38, 0.9118942731277533)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::getControlKey
Start: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare the compared control pointer before the traversal while retaining the live result lookup: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. bind each compared control through a const reference: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. name the compared pane pointer before traversal and assign it per entry: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onReleasedShift
Start: (90.89744, (37, 39, 34, 0.7894736842105263)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. return early when the live shift-button state is already off: (90.89744, (37, 39, 34, 0.7894736842105263)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.


The earlier wasOn trial was rejected and is not counted toward three valid attempts: a refresh callback could change the live button state. The early-return trial above preserves the live-state check and supplies the third valid alternative.

## Final source review
Reverted the onPressedShift animation-state branch despite its fuzzy gain: the stored state was just assigned true, making its alternate animation branch redundant. The trial remains evidence of the target compiler artifact, not retained source progress. The instruction-exact count remains 129; this also returns controller updateInput to its previous flag-load differences.
Reverted the two-step cleared-modifier temporary in onReleasedShift: its small local fuzzy gain made inlined controller updateInput worse, 95.25% -> 94.35714%. Both functions retain their baseline implementations; all new instruction-exact functions remain.

## Final verification
Full non-quick gate: GATE PASS. Instruction-exact functions 123 -> 129/141; objdiff code 20128 -> 22828/28484; matched data 5972 -> 5972/18564. Fuzzy 98.4280 -> 99.3443. Regressions, forbidden additions, readability warnings: 0. Source remains NonMatching; configure.py was not edited.

New exact functions: Base::sendInputWChar, 108 instructions; KeyState::getWCCode(char*), 57; LayoutByNW4R::createAnmPane_, 192; LayoutByNW4R::sendInputWChar, 44; LayoutByNW4R::setInputModeJP, 77; EventHandler::onTiEvent, 197. Each was measured at 100% and identical instruction sequences.

Shared change: the KeySet copy constructor is inside TI_PC_KEYBOARD_IMPLEMENTATION, defined by this .cpp alone. It restores return-value copy elision and real memberwise copy semantics. Other translation units have zero output regressions. Files changed: src/keyboard/tiPcKeyboard.cpp, include/keyboard/tiHKBManager.h, tools/decomp-assist/tiPcKeyboard.round3.md.

Data audit: pool 204/204 identical. Raw .data is byte-identical, 12576 bytes; all 1303 relocation sites coincide. Resolving local symbols to section offsets leaves one relocation-name difference, the truncated onEvent thunk at 0x2fb8. Ordinary tables, coordinate records, and owned vtable order remain correct. .rodata, .sdata, .sdata2, .sbss and .ctors score 100%. The .data score remains 74.95624; anonymous-symbol attribution is still uncertain. .bss remains 12 versus 16 zero bytes; extraction alignment is plausible but unproven. No dummy bytes, padding objects or symbol-name fixes were added.

Every remaining function has at least three distinct valid source-level attempts recorded in this pass. Source transformations that failed to apply or compile were not retained. Remaining evidence:
getWCCode__Q49textinput8keyboard6pctype4BaseFPc: None; The forwarding wrapper still inlines the now-exact key-state lookup: 57/2 instructions.
getControlKey__Q49textinput8keyboard6pctype4BaseFPc: 93.333336; Loop-index and table-offset registers are swapped: 36/36 instructions, 8 differences.
setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode: 99.04762; Defined fallback initialization adds a mode-register move: 106/105 instructions. Invalid-enum intent remains unknown.
refresh___Q59textinput8keyboard6pctype4Base8KeyStateFv: 98.77095; Mode normalization eliminates two repeated flag loads: 177/179 instructions.
getWCCode__Q59textinput8keyboard6pctype4Base8KeyStateFUl: 98.8; The first modifier load is reused across punctuation evaluation: 124/125 instructions; register differences remain.
create__Q49textinput8keyboard6pctype12LayoutByNW4RFP12MEMAllocator: 87.49367; Nullable multiple-inheritance pointer adjustments disappear and temporaries are scheduled differently: 151/158 instructions.
init__Q49textinput8keyboard6pctype12LayoutByNW4RFv: 99.94886; Selector records and their pane-vector temporaries occupy different stack slots: 352/352 instructions, 18 differences.
onPressedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFb: 90.81633; The modifier setter eliminates repeated flag loads; the target also contains a dead virtual-call branch artifact: 45/49 instructions.
onReleasedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFv: 90.0; Modifier masking and cached loads differ: 38/39 instructions.
updateInput__Q49textinput8keyboard6pctype12LayoutByNW4RFiffUlUlUlPv: 95.25; Inlined shift setters eliminate repeated flag loads: 135/140 instructions.
updateInput__Q49textinput8keyboard6pctype12LayoutByNW4RFRQ39textinput5input10HKBManager: 99.73568; One final character move should narrow to 16 bits: 227/227 instructions, source mr r26,r3 versus target clrlwi r26,r3,16.
@236@onEvent__Q49textinput8keyboard6pctype12LayoutByNW4RFPQ49textinput8keyboard6pctype5: None; Target name is truncated; the canonical compiler thunk still has identical two-instruction code under its complete signature.
