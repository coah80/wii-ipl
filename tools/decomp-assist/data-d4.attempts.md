# Data d4 high round

Baseline instruction-exact: tiInputForm 216/221, tiKeyboard 62/62, MyTiManager 91/91, MyTiInputForm 84/84. Matched_data: 908/3772, 12/2708, 76/1132, 2960/3032. All sources equal origin/main after initial fetch. Initial all-unit quick gate passes. All pools identical. Investigate actual relocations and typed source for every mismatch; do not claim completion from the safety gate alone.

## MyTiInputForm

High attempt 1: add the real protected textdrawer::Base draw-scroll setter taking const f32&, guarded by MYTIINPUTFORM_IMPLEMENTATION, and call it from calc's non-edit branch. This encapsulates the existing field assignment and lets MWCC materialize the addressable zero argument naturally in .sdata. No explicit object, array, forced section or padding was added.

Concrete baseline difference: target .sdata+0x28 is four zero bytes, with Nigaoe at +0x2C; source omitted this constant and placed Nigaoe at +0x28. Target calc relocation at .text+0x1F24 referenced .sdata+0x28; baseline source referenced .sdata2 zero. Setter now produces .sdata+0x28 zero and moves the following strings to their target offsets. Source .sdata contains 67 bytes matching target through +0x42; the remaining five target bytes are zero section-end linker alignment. Every non-text section reports 100%, matched_data 2960 -> 3032. calc instruction count remains 629/629, ctxdiff diffs 0. All 84 functions remain objdiff 100%. Await full-unit regression gate before committing.

All-unit quick gate after the setter passes: retail DOL hash preserved, regressions 0, forbidden/readability scans 0. MyTiInputForm remains 84/84 instruction-exact. Accepted and committed this focused improvement.

## tiInputForm

High attempts 1 and 2: defer tiLayoutGather.h until after the Color definitions, then until after sfColorPhase. Both emitted the seven Color objects at their real target offsets 0x0..0x18 instead of source offsets 0x8..0x20. However the compiler still schedules zero-initialized sfColorPhase after the singleton weak statics, and the section score regressed 33.333336 -> 31.818182. Static constructor objdiff regressed from 100 to 99.91954, unit matched_functions 218 -> 217 and matched_code 46980 -> 46632. Both changes rejected and restored. No accepted-data bytes gained.

High attempt 3: recover the existing sfColorPhase symbol name without changing any size or split range. Target calcCursorTimer has lfs at 0x8141F13C, 0x8141F26C, 0x8141F2CC and stfs at 0x8141F2E0, all relocating to .sbss 0x81698D1C. The real C++ float sfColorPhase feeds those same sine/phase updates. Original anonymous float is already four bytes. This is a name correction, not source address pinning or resizing; total bytes unchanged.

Phase-name recovery changes .sbss score 33.333336 -> 68.181816, but matched_data stays 908, with code/functions unchanged. No size or byte changes. Not retained as a fuzzy-only result.

## tiKeyboard

High attempt 1: declare gui::EventHandler's real virtual destructor out of line under a new macro defined only by tiKeyboard.cpp. The target does not retain this weak table or its weak methods in this unit. MWCC correctly changes its table ownership to external without changing any of the 62 original functions. .data improves 99.117645 -> 99.55687, matched_data remains 12. Pure abstract UIObj::Listener and AnmObserver still contribute 24 appended zero bytes not owned by the original split. Investigating before accepting any declaration-only change.

## MyTiManager

Fetched origin and checked pool first. All 91 functions already exact. Target .data+0x3B0..0x3D7 is 40 zero bytes without outgoing relocations; source ends at +0x3B0. Scan of all 43U extracted objects found references to that tail label: []. No concrete virtual method/function-pointer slot or used table object can be recovered from those zeros. Do not invent one. Target .bss is byte-identical 72 bytes but aggregates the first three compiler destructor records into a 36-byte symbol; source has three real 12-byte records at offsets 0, 12 and 24. The fourth record at +0x30 is 12 bytes. Source state objects at +0x24/+0x3C match target. No symbol sizes changed.

tiKeyboard declaration attempt rejected and restored. It improves only fuzzy section similarity and does not make data exact. Last pure-abstract base tables have no target-owned relocation slots to fill; declaring invented virtual methods or suppressing tables with compiler attributes would be dishonest.

High attempt 4: recover the actual four-byte ownership of each of seven Color objects in symbols.txt, preserving every address, split boundary and section byte. This corrects wrongly inferred byte objects; it does not hide a byte or relocation difference. Target static initialization relocates r6 to each named Color base and stores the R byte at base plus G/B/A bytes at +1,+2,+3 before registering the same base with __dt__nw4r::ut::Color. All seven objects are exactly four bytes apart, with no overlapping object or unrelated symbol in the three omitted bytes. Existing source already has the real typed nw4r::ut::Color globals. The prior one-byte annotations incorrectly assigned G/B/A to anonymous gaps. sfColorPhase name is recovered from its exact lfs/stfs relocations. Total .sbss stays 32 and whole-unit total_data stays 3772. This is evidence-backed object ownership recovery, not shrinking tables to hide mismatches.

Color ownership recovery passes the all-unit quick gate. .sbss now 100%, tiInputForm matched_data 908 -> 940, total_data unchanged 3772, instruction-exact 216/221 unchanged, whole-project regressions 0, DOL hash unchanged. Gate explicitly marks symbols.txt for orchestrator review. No source or object bytes were changed by this metadata correction.

High record-ownership experiment: recover the real 12-byte DestructorChain objects in two incorrectly aggregated BSS labels. NMWException.h defines next/dtor/object, all four-byte pointers. Runtime __register_global_object writes exactly those three fields. Target tiInputForm onCommand registers its singleton using BSS+0; static initialization registers the seven Color globals with BSS+12,+24,+36,+48,+60,+72,+84. Target MyTiManager static initialization registers Disp/Edit/Appear/Disappear states with BSS+0,+12,+24,+48. State objects themselves occupy +36..47 and +60..71 and stay untouched. Replace only the aggregate ownership annotation with those separately proved record boundaries; no byte, section size, split or pointer target changes. No source records or dummy padding added. Keep only if original functions do not regress and data measures improve.

Record ownership recovery passes the all-unit quick gate. tiInputForm .bss is now 100%, data 940 -> 1036; MyTiManager .bss is now 100%, data 76 -> 148. Both sections have the same byte extent and all original instruction-exact functions are preserved. Whole-project regressions 0, retail DOL hash unchanged. Symbols review remains required by the orchestrator.

calcCursorPos attempt right-before-bottom: objdiff 91.59509%, code 46980, data 1036. ['src 0x518 base 0x518 insns 326/326', 'diffs 43: [77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 127, 128, 129, 130, 131, 132, 133]']
calcCursorPos attempt separate-scale-components: objdiff 86.54601%, code 46980, data 1036. ['src 0x4f4 base 0x518 insns 317/326', '--- replace mine 28:29 base 28:29']
calcCursorPos attempt aggregate-line-bounds: objdiff 78.78528%, code 46980, data 1036. ['src 0x56c base 0x518 insns 347/326', '--- replace mine 0:1 base 0:1']
create attempt reload-row-owner: objdiff 94.985954%, code 46980, data 1036. ['src 0x580 base 0x590 insns 352/356', '--- replace mine 5:6 base 5:6']
create attempt font-branch-direction: objdiff 85.985954%, code 46980, data 1036. ['src 0x580 base 0x590 insns 352/356', '--- replace mine 5:6 base 5:6']
create attempt typed-button-index: objdiff 95.02809%, code 46980, data 1036. ['src 0x580 base 0x590 insns 352/356', '--- replace mine 5:6 base 5:6']
setLanguage attempt text-pane-branch-direction: objdiff 96.44726%, code 46980, data 1036. ['src 0x3b4 base 0x3b4 insns 237/237', 'diffs 22: [57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 118, 119, 120, 121, 122, 123, 124, 125, 126]']
setLanguage attempt reload-language-pane-after-query: objdiff 96.44726%, code 46980, data 1036. ['src 0x3b4 base 0x3b4 insns 237/237', 'diffs 22: [57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 118, 119, 120, 121, 122, 123, 124, 125, 126]']
setLanguage attempt split-visibility-counts: objdiff 93.44304%, code 46980, data 1036. ['src 0x3bc base 0x3b4 insns 239/237', '--- replace mine 9:11 base 9:10']
High tiInputForm vtable attempt: declare the real GUIComponent virtual destructor out of line in this unit only. This asks the compiler to use the actual external destructor/vtable ownership instead of emitting a duplicate weak GUIComponent table. Every virtual method and signature remains intact. Original unit does not own the GUIComponent destructor. Inspect data and original-function counts before keeping it.
GUIComponent destructor declaration had no data/code effect because this unit still defines its real non-inline init, which causes MWCC to emit the table. Restored header. Next real-class ownership attempt declares only gui::EventHandler destructor out of line, preserving all virtual slots.
GUI EventHandler destructor-declaration result: code 46916, functions 217, data 1036. Sections [{'name': '.bss', 'size': '96', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.ctors', 'size': '4', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.data', 'size': '2736', 'fuzzy_match_percent': 65.68563, 'metadata': {}}, {'name': '.rodata', 'size': '760', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sbss', 'size': '32', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata', 'size': '40', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata2', 'size': '104', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.text', 'size': '50656', 'fuzzy_match_percent': 99.521164, 'metadata': {}}]. Rejected and restored; no exact-data improvement.

## Final concrete data-symbol audit

Rebuilt all four units from a clean build with the final full gate. The following table compares every target .data symbol to its same-name source object (unnamed labels use the same section offset). Relocations are compared relative to the named object, not to the section start. Named weak tables at different section offsets can have identical real entries. An aligned target symbol extent can include zeros beyond the actual C++ object; these are shown separately rather than treated as missing virtual functions.

### tiInputForm .data

Target 2736 bytes; source 3077 bytes.

- `scP_txtScrll_UP` target +0x0, source +0x0: owned bytes equal, 0 relocation entries equal.
- `scP_txtScrll_DOWN` target +0x10, source +0x10: owned bytes equal, 0 relocation entries equal.
- `lbl_8165C840` target +0x20, source +0x20: owned bytes equal, 18 relocation entries equal.
- `scN_JPNUSAEUR` target +0xA0, source +0xA0: owned bytes equal, 0 relocation entries equal.
- `scN_separateBarAll` target +0xAC, source +0xAC: owned bytes equal, 0 relocation entries equal.
- `scT_2l_TextBox` target +0xC0, source +0xC0: owned bytes equal, 0 relocation entries equal.
- `scT_title_textJPN` target +0xD0, source +0xD0: owned bytes equal, 0 relocation entries equal.
- `scN_separateBarKOR` target +0xE0, source +0xE0: owned bytes equal, 0 relocation entries equal.
- `scT_2l_TextBoxKOR` target +0xF8, source +0xF8: owned bytes equal, 0 relocation entries equal.
- `scT_title_textKOR` target +0x108, source +0x108: owned bytes equal, 0 relocation entries equal.
- `scN_separateBarCHN` target +0x118, source +0x118: owned bytes equal, 0 relocation entries equal.
- `scT_2l_TextBoxCHN` target +0x130, source +0x130: owned bytes equal, 0 relocation entries equal.
- `scT_title_textCHN` target +0x140, source +0x140: owned bytes equal, 0 relocation entries equal.
- `lbl_8165C970` target +0x150, source +0x150: owned bytes equal, 0 relocation entries equal.
- `jumptable_8165C990` target +0x170, source +0x170: owned bytes equal, 40 relocation entries equal.
- `jumptable_8165CA30` target +0x210, source +0x210: owned bytes equal, 10 relocation entries equal.
- `jumptable_8165CA58` target +0x238, source +0x238: owned bytes equal, 13 relocation entries equal.
- `jumptable_8165CA8C` target +0x26C, source +0x26C: owned bytes equal, 48 relocation entries equal.
- `jumptable_8165CB4C` target +0x32C, source +0x32C: owned bytes equal, 37 relocation entries equal.
- `lbl_8165CBE0` target +0x3C0, source +0x3C0: owned bytes equal, 0 relocation entries equal.
- `lbl_8165CC14` target +0x3F4, source +0x3F4: owned bytes equal, 0 relocation entries equal.
- `lbl_8165CC28` target +0x408, source +0x408: owned bytes equal, 0 relocation entries equal.
- `lbl_8165CC4C` target +0x42C, source +0x42C: owned bytes equal, 0 relocation entries equal.
- `jumptable_8165CC5C` target +0x43C, source +0x43C: owned bytes equal, 7 relocation entries equal.
- `__vt__Q39textinput9inputform19NormalButtonAnmPane` target +0x458, source +0x458: owned bytes equal, 9 relocation entries equal.
- `__vt__Q39textinput9inputform7AnmPane` target +0x484, source +0x484: owned bytes equal, 9 relocation entries equal.
- `__vt__Q39textinput9inputform12EventHandler` target +0x4B0, source +0x4B0: owned bytes equal, 6 relocation entries equal.
- `__vt__Q39textinput9inputform12LayoutByNW4R` target +0x4D0, source +0x4D0: owned bytes equal, 136 relocation entries equal.
- `__vt__Q39textinput9inputform4Base` target +0x710, source +0x710: owned bytes equal, 100 relocation entries equal.
- `__vt__Q39textinput9inputform10EditBuffer` target +0x8B8, source +0x8B8: owned bytes equal, target extent 16, source object 12, 1 relocation entries equal.
- `__vt__Q39textinput8tistring8WithAtok` target +0x8C8, source +0x8C8: owned bytes equal, 78 relocation entries equal.
- `__vt__Q29textinput4Base` target +0xA08, source +0xBA0: owned bytes equal, target extent 48, source object 20, 3 relocation entries equal.
- `__vt__Q39textinput4util9Animation` target +0xA38, source +0xB58: owned bytes equal, 7 relocation entries equal.
- `lbl_8165D258` target +0xA5C, source +0xA5C: first byte difference +0x0: 4F -> 00, relocations +0x0 None -> ('inputString__Q39textinput8tistring9DecolatedFPCw', 0); +0x4 None -> ('deleteChar__Q39textinput8tistring9DecolatedFv', 0); +0x8 None -> ('backSpace__Q39textinput8tistring9DecolatedFv', 0); +0xC None -> ('confirm__Q39textinput8tistring9DecolatedFPCw', 0).
- `@STRING@GetTextColor__Q34nw4r3lyt7TextBoxCFUl` target +0xA6C, source +0xBC4: owned bytes equal, target extent 68, source object 65, source section ends after 65 available bytes, 0 relocation entries equal.

Additional real compiler-emitted weak tables absent from the target symbol inventory:

- `__vt__Q39textinput8tistring9Decolated` source +0xA08, 208 bytes: +0x4C -> getLastWChar__Q39textinput8tistring10StringBaseFv; +0x48 -> hasCandidate__Q39textinput8tistring10StringBaseCFv; +0x44 -> getCandidate__Q39textinput8tistring10StringBaseCFv; +0x40 -> setCandidate__Q39textinput8tistring10StringBaseFw; +0x3C -> getWCString__Q39textinput8tistring10StringBaseCFv; +0x34 -> setAt__Q39textinput8tistring10StringBaseFUsw; +0x2C -> replace__Q39textinput8tistring10StringBaseFUsUsPCw; +0x28 -> remove__Q39textinput8tistring10StringBaseFUsUs; +0x24 -> insert__Q39textinput8tistring10StringBaseFUsPCw; +0x20 -> append__Q39textinput8tistring10StringBaseFPCw; +0x1C -> getLength__Q39textinput8tistring10StringBaseCFv; +0x14 -> popBack__Q39textinput8tistring10StringBaseFv; +0x10 -> pushBack__Q39textinput8tistring10StringBaseFw; +0xC -> create__Q39textinput8tistring10StringBaseFP12MEMAllocator; +0xCC -> EnableKSXFilter__Q39textinput8tistring9DecolatedFb; +0xC8 -> clearKana__Q39textinput8tistring9DecolatedFv; +0xC4 -> confirmKana__Q39textinput8tistring9DecolatedFv; +0xC0 -> isKanaFix__Q39textinput8tistring9DecolatedCFv; +0xBC -> getKanaBuffer__Q39textinput8tistring9DecolatedFv; +0xB8 -> initKanaConverter__Q39textinput8tistring9DecolatedFv; +0xB4 -> atTheBeginningOfASentence__Q39textinput8tistring9DecolatedFv; +0xB0 -> converSmall__Q39textinput8tistring9DecolatedFv; +0xAC -> isSmall__Q39textinput8tistring9DecolatedFv; +0xA8 -> convertAll__Q39textinput8tistring9DecolatedFv; +0xA4 -> converHandaku__Q39textinput8tistring9DecolatedFv; +0xA0 -> isHandaku__Q39textinput8tistring9DecolatedFv; +0x9C -> converDakuten__Q39textinput8tistring9DecolatedFv; +0x98 -> isDakuten__Q39textinput8tistring9DecolatedFv; +0x94 -> replaceAtCursor__Q39textinput8tistring9DecolatedFw; +0x90 -> getWCharAtCursor__Q39textinput8tistring9DecolatedFv; +0x8C -> getSelected__Q39textinput8tistring9DecolatedFRUlRUl; +0x88 -> deleteForward__Q39textinput8tistring9DecolatedFv; +0x84 -> canBackSpace__Q39textinput8tistring9DecolatedFv; +0x7C -> getCursorPos__Q39textinput8tistring9DecolatedCFv; +0x80 -> getCursorPos__Q39textinput8tistring9DecolatedFPUlPUl; +0x78 -> isOnSustain__Q39textinput8tistring9DecolatedFv; +0x74 -> offSustain__Q39textinput8tistring9DecolatedFv; +0x70 -> onSustain__Q39textinput8tistring9DecolatedFv; +0x6C -> setCursorPos__Q39textinput8tistring9DecolatedFUl; +0x68 -> moveCursorLeft__Q39textinput8tistring9DecolatedFv; +0x64 -> moveCursorRight__Q39textinput8tistring9DecolatedFv; +0x60 -> confirm__Q39textinput8tistring9DecolatedFPCw; +0x5C -> backSpace__Q39textinput8tistring9DecolatedFv; +0x58 -> deleteChar__Q39textinput8tistring9DecolatedFv; +0x50 -> inputChar__Q39textinput8tistring9DecolatedFw; +0x54 -> inputString__Q39textinput8tistring9DecolatedFPCw; +0x38 -> setLength__Q39textinput8tistring9DecolatedFUs; +0x30 -> set__Q39textinput8tistring9DecolatedFPCw; +0x18 -> clear__Q39textinput8tistring9DecolatedFv; +0x8 -> __dt__Q39textinput8tistring9DecolatedFv.
- `__vt__Q39textinput3gui12GUIComponent` source +0xAD8, 104 bytes: +0x18 -> draw__Q39textinput3gui12GUIInterfaceFRA3_A4_f; +0x1C -> draw__Q39textinput3gui12GUIInterfaceFv; +0x14 -> calc__Q39textinput3gui12GUIInterfaceFv; +0xC -> create__Q39textinput3gui12GUIInterfaceFv; +0x60 -> setFlightDuration__Q39textinput3gui12GUIComponentFiUs; +0x5C -> getFlightDuration__Q39textinput3gui12GUIComponentFi; +0x58 -> isVisible__Q39textinput3gui12GUIComponentFv; +0x54 -> setTriggerTarget__Q39textinput3gui12GUIComponentFb; +0x50 -> isTriggerTarget__Q39textinput3gui12GUIComponentFv; +0x48 -> updatePointer__Q39textinput3gui12GUIComponentFRCQ39textinput3gui10GUIPointer; +0x4C -> updatePointer__Q39textinput3gui12GUIComponentFiffUlUlUl; +0x44 -> setDraggingButton__Q39textinput3gui12GUIComponentFUl; +0x40 -> onTrig__Q39textinput3gui12GUIComponentFiUlR3Vec; +0x3C -> onMove__Q39textinput3gui12GUIComponentFiff; +0x38 -> onDrag__Q39textinput3gui12GUIComponentFff; +0x34 -> onPointOut__Q39textinput3gui12GUIComponentFi; +0x30 -> onPointIn__Q39textinput3gui12GUIComponentFi; +0x2C -> setPointed__Q39textinput3gui12GUIComponentFib; +0x28 -> isDragging__Q39textinput3gui12GUIComponentFi; +0x24 -> isPointed__Q39textinput3gui12GUIComponentFi; +0x20 -> getID__Q39textinput3gui12GUIComponentFv; +0x8 -> __dt__Q39textinput3gui12GUIComponentFv; +0x10 -> init__Q39textinput3gui12GUIComponentFv.
- `__vt__Q39textinput3gui12EventHandler` source +0xB40, 24 bytes: +0x14 -> getLatestEventCtrlNo__Q39textinput3gui12EventHandlerFv; +0x10 -> setLatestEventCtrlNo__Q39textinput3gui12EventHandlerFi; +0xC -> onEvent__Q39textinput3gui12EventHandlerFRQ39textinput3gui12GUIComponentUlPv; +0x8 -> __dt__Q39textinput3gui12EventHandlerFv.
- `__vt__Q29textinput15CommandReceiver` source +0xB80, 32 bytes: +0x10 -> init__Q29textinput4BaseFv; +0xC -> create__Q29textinput4BaseFP12MEMAllocator; +0x1C -> addSender__Q29textinput15CommandReceiverFPQ29textinput13CommandSender; +0x18 -> onCommand__Q29textinput15CommandReceiverFQ39textinput15CommandReceiver13INPUT_COMMANDPv; +0x14 -> clearSender__Q29textinput15CommandReceiverFv; +0x8 -> __dt__Q29textinput15CommandReceiverFv.

### tiKeyboard .data

Target 2696 bytes; source 2744 bytes.

- `lbl_8165F8F0` target +0x0, source +0x0: owned bytes equal, 0 relocation entries equal.
- `lbl_8165F900` target +0x10, source +0x10: owned bytes equal, 0 relocation entries equal.
- `lbl_8165F920` target +0x30, source +0x30: owned bytes equal, 0 relocation entries equal.
- `lbl_8165F938` target +0x48, source +0x48: owned bytes equal, 0 relocation entries equal.
- `lbl_8165F950` target +0x60, source +0x60: owned bytes equal, 0 relocation entries equal.
- `lbl_8165F96C` target +0x7C, source +0x7C: owned bytes equal, 0 relocation entries equal.
- `lbl_8165F988` target +0x98, source +0x98: owned bytes equal, 0 relocation entries equal.
- `lbl_8165F9A0` target +0xB0, source +0xB0: owned bytes equal, 0 relocation entries equal.
- `__vt__Q29textinput7Manager` target +0xC8, source +0xC8: owned bytes equal, 50 relocation entries equal.
- `__vt__Q49textinput8keyboard10signwindow6Sample` target +0x198, source +0x198: owned bytes equal, target extent 272, source object 268, 61 relocation entries equal.
- `__vt__Q39textinput11predictlang6Sample` target +0x2A8, source +0x2A8: owned bytes equal, 50 relocation entries equal.
- `__vt__Q39textinput11predictlang4Base` target +0x388, source +0x388: owned bytes equal, target extent 40, source object 36, 7 relocation entries equal.
- `__vt__Q39textinput7toolbar6Sample` target +0x3B0, source +0x3B0: owned bytes equal, 48 relocation entries equal.
- `__vt__Q39textinput9inputform6Sample` target +0x480, source +0x480: owned bytes equal, 136 relocation entries equal.
- `__vt__Q39textinput12candidatebox6Sample` target +0x6C0, source +0x6C0: owned bytes equal, 70 relocation entries equal.
- `__vt__Q49textinput8keyboard13cellphonetype6Sample` target +0x7F0, source +0x7F0: owned bytes equal, 75 relocation entries equal.
- `__vt__Q49textinput8keyboard6pctype6Sample` target +0x92C, source +0x92C: owned bytes equal, 81 relocation entries equal.

Additional real compiler-emitted weak tables absent from the target symbol inventory:

- `__vt__Q59textinput8keyboard6pctype5UIObj8Listener` source +0xA88, 12 bytes: all bytes zero; no relocation slots.
- `__vt__Q39textinput11nw4rmanager11AnmObserver` source +0xA94, 12 bytes: all bytes zero; no relocation slots.
- `__vt__Q39textinput3gui12EventHandler` source +0xAA0, 24 bytes: +0x14 -> getLatestEventCtrlNo__Q39textinput3gui12EventHandlerFv; +0x10 -> setLatestEventCtrlNo__Q39textinput3gui12EventHandlerFi; +0xC -> onEvent__Q39textinput3gui12EventHandlerFRQ39textinput3gui12GUIComponentUlPv; +0x8 -> __dt__Q39textinput3gui12EventHandlerFv.

### MyTiManager .data

Target 984 bytes; source 944 bytes.

- `lbl_81667E38` target +0x0, source +0x0: owned bytes equal, 0 relocation entries equal.
- `lbl_81667E58` target +0x20, source +0x20: owned bytes equal, 0 relocation entries equal.
- `lbl_81667E68` target +0x30, source +0x30: owned bytes equal, 0 relocation entries equal.
- `lbl_81667E7C` target +0x44, source +0x44: owned bytes equal, 0 relocation entries equal.
- `lbl_81667E94` target +0x5C, source +0x5C: owned bytes equal, 0 relocation entries equal.
- `lbl_81667EB0` target +0x78, source +0x78: owned bytes equal, 0 relocation entries equal.
- `lbl_81667EC8` target +0x90, source +0x90: owned bytes equal, 0 relocation entries equal.
- `__vt__Q49textinput6extend2bg4Base` target +0xA8, source +0xA8: owned bytes equal, 2 relocation entries equal.
- `__vt__Q49textinput6extend4memo18DisappearMemoState` target +0xB8, source +0xB8: owned bytes equal, 20 relocation entries equal.
- `__vt__Q49textinput6extend4memo13EditMemoState` target +0x110, source +0x110: owned bytes equal, 20 relocation entries equal.
- `__vt__Q49textinput6extend4memo15AppearMemoState` target +0x168, source +0x168: owned bytes equal, 20 relocation entries equal.
- `__vt__Q49textinput6extend4memo13DispMemoState` target +0x1C0, source +0x1C0: owned bytes equal, 20 relocation entries equal.
- `__vt__Q49textinput6extend4memo5State` target +0x218, source +0x218: owned bytes equal, 10 relocation entries equal.
- `__vt__Q49textinput6extend4memo7Manager` target +0x270, source +0x270: owned bytes equal, 78 relocation entries equal.
- `lbl_816681E8` target +0x3B0, source +0x3B0: target contains 40 zero bytes; source section has ended, so none of this object is present; no target relocation entries.

### MyTiInputForm .data

Target 1616 bytes; source 1616 bytes.

- `lbl_81668210` target +0x0, source +0x0: owned bytes equal, 0 relocation entries equal.
- `lbl_8166821C` target +0xC, source +0xC: owned bytes equal, 0 relocation entries equal.
- `lbl_81668228` target +0x18, source +0x18: owned bytes equal, 0 relocation entries equal.
- `lbl_81668234` target +0x24, source +0x24: owned bytes equal, 0 relocation entries equal.
- `lbl_81668240` target +0x30, source +0x30: owned bytes equal, 0 relocation entries equal.
- `lbl_8166824C` target +0x3C, source +0x3C: owned bytes equal, 0 relocation entries equal.
- `scPaneName__Q39textinput6extend4memo` target +0x4C, source +0x4C: owned bytes equal, relocations +0x0 ('lbl_81668210', 0) -> ('@6051', 0); +0x4 ('lbl_816974E0', 0) -> ('@6052', 0); +0x8 ('lbl_816974E8', 0) -> ('@6053', 0); +0xC ('lbl_8166821C', 0) -> ('@6054', 0); +0x10 ('lbl_816974F0', 0) -> ('@6055', 0); +0x14 ('lbl_81668228', 0) -> ('@6056', 0); +0x18 ('lbl_81668234', 0) -> ('@6057', 0); +0x1C ('lbl_81668240', 0) -> ('@6058', 0); +0x20 ('lbl_8166824C', 0) -> ('@6059', 0).
- `jumptable_81668280` target +0x70, source +0x70: owned bytes equal, 26 relocation entries equal.
- `lbl_81668324` target +0x114, source +0x114: owned bytes equal, 0 relocation entries equal.
- `lbl_81668330` target +0x120, source +0x120: owned bytes equal, 0 relocation entries equal.
- `lbl_81668340` target +0x130, source +0x130: owned bytes equal, 0 relocation entries equal.
- `lbl_81668350` target +0x140, source +0x140: owned bytes equal, 0 relocation entries equal.
- `lbl_8166835C` target +0x14C, source +0x14C: owned bytes equal, 0 relocation entries equal.
- `lbl_81668368` target +0x158, source +0x158: owned bytes equal, 0 relocation entries equal.
- `lbl_81668374` target +0x164, source +0x164: owned bytes equal, 0 relocation entries equal.
- `lbl_81668380` target +0x170, source +0x170: owned bytes equal, 0 relocation entries equal.
- `lbl_8166838C` target +0x17C, source +0x17C: owned bytes equal, 0 relocation entries equal.
- `csGroupName__Q39textinput6extend4memo` target +0x188, source +0x188: owned bytes equal, relocations +0x0 ('lbl_81668324', 0) -> ('@6255', 0); +0x4 ('lbl_81668330', 0) -> ('@6256', 0); +0x8 ('lbl_81668340', 0) -> ('@6257', 0); +0xC ('lbl_81668350', 0) -> ('@6258', 0); +0x10 ('lbl_8166835C', 0) -> ('@6259', 0); +0x14 ('lbl_81668368', 0) -> ('@6260', 0); +0x18 ('lbl_81668374', 0) -> ('@6261', 0); +0x1C ('lbl_81668380', 0) -> ('@6262', 0); +0x20 ('lbl_8166838C', 0) -> ('@6263', 0).
- `jumptable_816683BC` target +0x1AC, source +0x1AC: owned bytes equal, 9 relocation entries equal.
- `jumptable_816683E0` target +0x1D0, source +0x1D0: owned bytes equal, 9 relocation entries equal.
- `lbl_81668404` target +0x1F4, source +0x1F4: owned bytes equal, 0 relocation entries equal.
- `lbl_81668418` target +0x208, source +0x208: owned bytes equal, 0 relocation entries equal.
- `lbl_81668428` target +0x218, source +0x218: owned bytes equal, 0 relocation entries equal.
- `lbl_81668434` target +0x224, source +0x224: owned bytes equal, 0 relocation entries equal.
- `lbl_81668460` target +0x250, source +0x250: owned bytes equal, 0 relocation entries equal.
- `lbl_8166846C` target +0x25C, source +0x25C: owned bytes equal, 0 relocation entries equal.
- `lbl_8166847C` target +0x26C, source +0x26C: owned bytes equal, 0 relocation entries equal.
- `lbl_81668488` target +0x278, source +0x278: owned bytes equal, 0 relocation entries equal.
- `__vt__Q49textinput6extend4memo13SimpleAnmPane` target +0x284, source +0x284: owned bytes equal, 7 relocation entries equal.
- `__vt__Q49textinput6extend4memo12ScrollButton` target +0x2A8, source +0x2A8: owned bytes equal, 4 relocation entries equal.
- `__vt__Q49textinput6extend4memo10NigaoePane` target +0x2C0, source +0x2C0: owned bytes equal, 9 relocation entries equal.
- `__vt__Q49textinput6extend4memo9WholePane` target +0x2EC, source +0x2EC: owned bytes equal, 9 relocation entries equal.
- `__vt__Q49textinput6extend4memo7AnmPane` target +0x318, source +0x318: owned bytes equal, target extent 48, source object 44, 9 relocation entries equal.
- `__vt__Q49textinput6extend4memo12EventHandler` target +0x348, source +0x348: owned bytes equal, 6 relocation entries equal.
- `__vt__Q49textinput6extend4memo9InputForm` target +0x368, source +0x368: owned bytes equal, target extent 744, source object 720, 172 relocation entries equal.

Additional real compiler-emitted weak tables absent from the target symbol inventory:

- `__vt__Q39textinput3gui12EventHandler` source +0x638, 24 bytes: +0x14 -> getLatestEventCtrlNo__Q39textinput3gui12EventHandlerFv; +0x10 -> setLatestEventCtrlNo__Q39textinput3gui12EventHandlerFi; +0xC -> onEvent__Q39textinput3gui12EventHandlerFRQ39textinput3gui12GUIComponentUlPv; +0x8 -> __dt__Q39textinput3gui12EventHandlerFv.

## Remaining differences and completeness audit

Raw relocation name differences for ordinary literal aliases in the inventory above are not wrong pointer targets: normalization to referenced section plus symbol value plus relocation addend resolves them to the same bytes. All retained tiInputForm tables through WithAtok, all tiKeyboard retained tables, and all MyTiManager retained tables have the exact original virtual method slots. No missing nonzero virtual slot was discovered. tiInputForm Base at target .data+0xA08 has only its real destructor/create/init at +8/+12/+16; the additional 28 bytes of its extraction extent are zeros without relocations. Its source table at +0xBA0 has those same three entries. Animation has all seven exact method slots, but shifts from target +0xA38 to source +0xB58. The target OutOfLength literal is at +0xA5C; the identical source literal is at +0xBB4. The final assertion literal shifts from +0xA6C to +0xBC4. The section is not byte-identical and remains unresolved; no invented virtual methods, suppressed tables, padding, or size truncation was used.

tiKeyboard's complete 2696-byte target prefix is byte-identical to source, including every normalized relocation. Source appends two genuine pure-abstract 12-byte weak tables with only zeros and one real 24-byte EventHandler table with the four concrete relocation slots listed above. Therefore the entire section is not identical and the data goal remains unresolved. MyTiManager's complete 944-byte source prefix is byte-identical to target, with identical normalized relocations. The target-only 40-byte zero tail has no outgoing relocations and no incoming reference found in any extracted 43U object. Its actual source object/type cannot be recovered from this evidence; adding a zero filler would violate the task. Its .data goal remains unresolved.

MyTiInputForm .data is 1616 bytes on both sides with identical raw bytes. Source's final weak EventHandler has real destructor/onEvent/setLatestEventCtrlNo/getLatestEventCtrlNo relocations at +0x640/+0x644/+0x648/+0x64C; original deduplicated weak extraction has zeros and no relocations there. Objdiff nonetheless reports 100% for the section. .rodata and .sdata2 are byte-identical, including normalized relocations. .sdata now has the genuine addressable float zero at +0x28, and its entire 67-byte source prefix equals target; target has five trailing zero alignment bytes. Objdiff reports every non-text section 100%, matched_data 3032/3032. No total_data value changed for any unit.

Remaining objdiff nonmatching functions, all restored after three distinct source attempts:
- calcCursorPos__Q39textinput9inputform4BaseFff: 91.622696%, 326/326 instructions, float register allocation/scheduling differs; attempted right-before-bottom, separate scale components, aggregate line bounds.
- create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: 95.02809%, 352/356 instructions, row/button loop allocation/codegen differs; attempted reload row owner, font branch direction, typed button index.
- setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language: 96.44726%, 237/237 instructions, visibility-loop register choices differ; attempted text-pane branch direction, pane query reload, split visibility counts.

Final clean full gate over all four units: no regressions, no added forbidden patterns, no readability warnings; retail DOL SHA1 preserved. Code matched bytes and instruction-exact counts never dropped in the retained commits. This is partial data progress, with only MyTiInputForm reaching the full data goal. The symbols ownership corrections preserve all original split/section byte extents and require ordinary orchestrator evidence review.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiInputForm] pool: IDENTICAL
[src/keyboard/tiInputForm] objdiff: code 46980/50656 data 1036/3772 functions 218/221 fuzzy 99.5781 linked code 0
[src/keyboard/tiInputForm] instruction-exact functions: 216/221
[src/keyboard/tiInputForm]   section .bss size 96 match 100.0
[src/keyboard/tiInputForm]   section .ctors size 4 match 100.0
[src/keyboard/tiInputForm]   section .data size 2736 match 65.68563
[src/keyboard/tiInputForm]   section .rodata size 760 match 100.0
[src/keyboard/tiInputForm]   section .sbss size 32 match 100.0
[src/keyboard/tiInputForm]   section .sdata size 40 match 100.0
[src/keyboard/tiInputForm]   section .sdata2 size 104 match 100.0
[src/keyboard/tiInputForm]   section .text size 50656 match 99.578094
[src/keyboard/tiInputForm]   below 100: calcCursorPos__Q39textinput9inputform4BaseFff 91.622696
[src/keyboard/tiInputForm]   below 100: create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer 95.02809
[src/keyboard/tiInputForm]   below 100: setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language 96.44726
[src/keyboard/tiInputForm] baseline: code 46980/50656 data 908 functions 218 fuzzy 99.5781
[src/keyboard/tiKeyboard] pool: IDENTICAL
[src/keyboard/tiKeyboard] objdiff: code 8368/8368 data 12/2708 functions 62/62 fuzzy 100.0000 linked code 8368
[src/keyboard/tiKeyboard] instruction-exact functions: 62/62
[src/keyboard/tiKeyboard]   section .ctors size 4 match 100.0
[src/keyboard/tiKeyboard]   section .data size 2696 match 99.117645
[src/keyboard/tiKeyboard]   section .sbss size 8 match 100.0
[src/keyboard/tiKeyboard]   section .text size 8368 match 100.0
[src/keyboard/tiKeyboard] baseline: code 8368/8368 data 12 functions 62 fuzzy 100.0000
[src/keyboard/MyTiManager] pool: IDENTICAL
[src/keyboard/MyTiManager] objdiff: code 20196/20196 data 148/1132 functions 91/91 fuzzy 100.0000 linked code 0
[src/keyboard/MyTiManager] instruction-exact functions: 91/91
[src/keyboard/MyTiManager]   section .bss size 72 match 100.0
[src/keyboard/MyTiManager]   section .ctors size 4 match 100.0
[src/keyboard/MyTiManager]   section .data size 984 match 97.92531
[src/keyboard/MyTiManager]   section .sbss size 16 match 100.0
[src/keyboard/MyTiManager]   section .sdata size 24 match 100.0
[src/keyboard/MyTiManager]   section .sdata2 size 32 match 100.0
[src/keyboard/MyTiManager]   section .text size 20196 match 100.0
[src/keyboard/MyTiManager] baseline: code 20196/20196 data 76 functions 91 fuzzy 100.0000
[src/keyboard/MyTiInputForm] pool: IDENTICAL
[src/keyboard/MyTiInputForm] objdiff: code 14532/14532 data 3032/3032 functions 84/84 fuzzy 100.0000 linked code 0
[src/keyboard/MyTiInputForm] instruction-exact functions: 84/84
[src/keyboard/MyTiInputForm]   section .data size 1616 match 100.0
[src/keyboard/MyTiInputForm]   section .rodata size 1288 match 100.0
[src/keyboard/MyTiInputForm]   section .sdata size 72 match 100.0
[src/keyboard/MyTiInputForm]   section .sdata2 size 56 match 100.0
[src/keyboard/MyTiInputForm]   section .text size 14532 match 100.0
[src/keyboard/MyTiInputForm] baseline: code 14532/14532 data 2960 functions 84 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 88.55724 -> 88.55724
global fuzzy_match_percent: 99.45033 -> 99.45033
global complete_code_percent: 62.98463 -> 62.98463
global matched_data_percent: 96.82804 -> 96.84288
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

Accepted improvement commits: 2348596d (real float-reference setter), fff3e072 (Color ownership), 8532b7bf (DestructorChain ownership).
