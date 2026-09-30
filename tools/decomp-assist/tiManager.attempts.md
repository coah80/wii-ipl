# tiManager matching attempts

Baseline: source absent; 0/62 functions, 0/8368 code bytes. The implementation uses only C++, existing keyboard interfaces, and constructors for the seven concrete Sample layouts. Shared declarations are enabled only by TIMANAGER_IMPLEMENTATION.

## Pool and data

1. Initial Sample constructors contained their layout literals. Deferred inline expansion placed these after the vtables and emitted them in constructor order. Pool diverged at string 1. Passing ordinary layout-name literals from the factories restored all eight strings and their offsets.
2. Sample declarations initially followed input includes and the factory order. The vtable contents mostly matched but table addresses differed. Declaring the Samples in reverse emission order, with the manager header last, restored the target's table order.
3. The out-of-line HWKeyboard destructor emitted a strong HWKeyboard vtable absent from the target. Declaring its C++ destructor inline made that table weak and restored every strong table's offset. The destructor still matches all 16 instructions.
4. Enabled the actual inherited CommandReceiver::Scroll and inherited CommandSender::updateFromReceiver declarations for this unit. This corrected the inputform and signwindow vtable relocation names without affecting other units.

A word-by-word comparison of .data now finds exactly two relocation-name differences, at 0x520 and 0xa44. The original names are `isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv` and `@236@onEvent__Q49textinput8keyboard6pctype12LayoutByNW4RFPQ49textinput8keyboard6pctype5`. The compiler produces the ordinary complete C++ names. All other .data bytes and relocations agree within the target's 2696-byte extent. The compiler additionally emits 48 bytes of weak vtables for pctype::UIObj::Listener, nw4rmanager::AnmObserver, and gui::EventHandler; these are absent from the extracted target object. No symbol aliases, forced labels, or edits to target symbol names were attempted. Objdiff nevertheless reports .data below 100%; automatic string symbols, the weak tables, and those malformed target names remain unresolved.

## Functions

- Constructor, create, initAspect, draw, prediction wrappers, string/length wrappers, factories, filters, isVacancy, and Sample destructors matched from the first implementation or after correcting header types and string placement.
- Destructor: initial implementation cleared seven members after freeing them (131 instructions versus 123). Removing those unsupported stores gave 123/123, zero diffs.
- init: 209/209 with three diffs. Comparing the aspect flag to true corrected branch direction; calling setSecretInputMode(false), as the target slot 0x4c specifies, corrected the last virtual call. Zero diffs.
- calc, setAnimationOn, scale functions, SetFont: pointer-to-secondary-base conversions added null checks. Casting dereferenced objects to Layout references removed those checks. All matched.
- createPCTypeKeyboard: 82/82, nine ordering diffs. Initializing KeyState before allocator, qwerty flag, and manager in the Base constructor gave zero diffs.
- updateInput(HKBManager&): initial 137/130 instructions. Returning immediately from modal dialog/window branches, selecting the keyboard using the saved qwerty state, and grouping the four boolean results as (keyboard | candidates) | (form | toolbar) produced 130/130, zero diffs.
- updateInput(Wii): initial 206/206 with 25 diffs after the preceding changes. Moving updateInputCommon before the sign-window activity check reproduced the target's call order, 206/206, zero diffs.
- setAspectRatio: initial 11/12 instructions; converting the bool to u8 before comparing with true restored the target's byte extension, 12/12, zero diffs.
- setTitleText: a separate pane temporary followed by DynamicCast gave 49/49 with seven register differences. Nesting the getPane call directly in DynamicCast gave 49/49, zero diffs.

## Remaining generated initializer

`__sinit_\tiKeyboard_cpp` is not emitted under that name because the required source file is tiManager.cpp.

1. A namespace-scope static default observer with its implicit constructor emits `__sinit_\tiManager_cpp`, four instructions: lis, addi, stw, blr, matching the target initializer's instruction sequence.
2. An anonymous-namespace default observer changes its object linkage name but still emits the same four instructions under the tiManager initializer name. Reverted for simpler source.
3. An explicitly empty EventObserver constructor also emits the same four instructions and unchanged initializer name. Reverted because the implicit constructor suffices.

The name mismatch remains. No generated-function rename, assembler alias, or filename override was introduced.

## Changed files

- src/keyboard/tiManager.cpp
- include/keyboard/tiCandidateBox.h
- include/keyboard/tiCellPhone.h
- include/keyboard/tiHKBManager.h
- include/keyboard/tiHwKeyboard.h
- include/keyboard/tiInputForm.h
- include/keyboard/tiKeyboard.h
- include/keyboard/tiManager.h
- include/keyboard/tiNw4rManager.h
- include/keyboard/tiPcKeyboard.h
- include/keyboard/tiPcKeyboardImpl.h
- include/keyboard/tiPredictLang.h
- include/keyboard/tiString.h
- include/keyboard/tiTextDrawer.h
- include/keyboard/tiTextInputBase.h
- include/keyboard/tiToolBar.h
- include/keyboard/tiZiString.h
- tools/decomp-assist/tiManager.attempts.md
