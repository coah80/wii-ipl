# tiSignWindow matching attempts

Baseline: absent source, 0/56 functions and 0/7184 code bytes. The source reconstructs the actual animation, pane, language, and key-name tables using ordinary literals and typed objects. Previous scratch C++ and the original-object Ghidra export were references. Their explicit padding, mangled free-function calls, manual vtable dispatch, and raw pointer offsets were removed before the first build.

## Data

The first build already had all 30 strings in the original pool order. The nine animation records occupy 612 bytes; the compiler supplies the following alignment naturally, without a padding record. InputCharacter is a real 12-byte command payload with ordinary aggregate initialization.

The first .data score was 83.582375%. Declaring the three concrete animation-pane classes in reverse vtable emission order restored their table order. Inheriting CommandSender::setCommandReceiver and sendCommand for this unit corrected the two Base/Layout vtables. All data sections subsequently reached 100% in objdiff: .data, .rodata, .sdata, and .ctors. A trial making the key-name table static caused the compiler to remove it and broke the pool; the table retains ordinary external linkage so the real target table is present.

## Matched functions

Most functions matched on the first readable implementation, including destruction, initialization, modal-window operations, character/page rendering, input handling, and animation callbacks.

- The input payload's repeat flag initially read an unsigned-byte member into bool and emitted three normalization instructions. Declaring the actual boolean repeat/locked/input/active fields restored the target loads and stores.
- CellPhoneSignAllAnmPane::onAnmEvent had 39/39 instructions with two unsigned comparisons. Making the stored animation state signed restored both comparisons and gave zero diffs.
- Base::onKey initially had 115/115 instructions with 13 differences. Moving counters into their respective scopes produced 19 differences; reversing the two counter declarations also produced 19; using an unsigned control-key result increased the count to 116. These variants were reverted.
- A real inline control-key lookup reduced Base::onKey to ten differences and LayoutByNW4R::onKey to eight. A character lookup accepting LanguageDependency reduced the layout function to five differences. Swapping the helper's parameter order left five differences. Passing the actual key array to the character helper restored the target register allocation for both functions.
- Base::onKey then showed two false ctxdiff differences on CR1 branches. Inspection found identical instruction bytes for both branches; the helper normalizes the CR operand as if it were a branch address when function offsets differ. Declaring the already-existing KeyboardBase::getLanguage externally in this unit avoided a duplicate weak inline body, restored the original function offset, and ctxdiff reported zero differences without any instruction changes to onKey.

## Remaining function: LayoutByNW4R::create

All variants use typed placement construction, real class sizes, and the same 221 instructions as the target. The remaining differences are callee-saved register allocation, including hoisted vtable addresses, animation count, and animation-record temporaries.

1. Initial scoped const forceName/animationCount variables: 61 differences.
2. Declared forceName and animationCount outside the pane loop and assigned them after appending the pane: 34 differences.
3. Declared the pane pointer before the pane-table reference: still 34 differences.
4. Reversed the forceName/count declarations: 37 differences, reverted.
5. Changed the outer for loop to a do/while loop with an explicit paneIndex: still 34 differences, retained.
6. Kept forceName outside but made animationCount local and const: 59 differences, reverted.

The retained version has 221/221 instructions and 34 register differences. No artificial code or data placement was used.

## Changed files

- src/keyboard/tiSignWindow.cpp
- include/keyboard/tiSignWindow.h
- include/keyboard/tiHKBManager.h
- include/keyboard/tiInputForm.h
- include/keyboard/tiKeyboard.h
- include/keyboard/tiNw4rManager.h
- include/keyboard/tiPcKeyboard.h
- include/keyboard/tiPcKeyboardImpl.h
- include/keyboard/tiTextInputBase.h
- tools/decomp-assist/tiSignWindow.attempts.md
