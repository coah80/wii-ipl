# o-ifl attempts: link src/keyboard/tiInputForm

Worktree data-d4, branch agent/w1009/o-ifl, base 12e857a9. Start: 221/221 exact, code and data 100%,
NonMatching. A Matching flip failed with multiply-defined `Decolated` and `CommandReceiver` vtables;
37/221 functions were in target order.

## How MWCC (GC/3.0a5.2, -ipa file) lays out this TU

Measured with small test files and the real unit:

- Non-inline definitions are emitted in source order.
- An inline function is emitted right after the definition that first "touches" it, if anything needs
  an out-of-line copy (a non-inlined call, a virtual call, a vtable). A touch is any call in the source,
  even one that is inlined and leaves no code, and an unused result still counts.
- When a non-inline function is inlined into a caller, its touches stay with its own definition. When an
  inline-only helper is inlined, its touches go to the caller.
- Virtual calls touch the statically resolved function (no relocation, so dtk shows them as UNREF).
- A constructor touches the destructors of its bases.
- The key function is the first virtual declared in the class without a body. Defined non-inline here:
  strong vtable. Defined `inline` out of class: weak vtable when referenced. Declared `inline` or with a
  body in the class: skipped, the next one becomes the key.
- `.data` vtables are emitted in reverse class-definition order. The vtable tail (inline virtuals only a
  vtable needs) follows the same order; per class: overrides with thunks first, then inherited inlines per
  base in reverse slot order, then the class's own inlines in reverse declaration order. A class whose
  vtable is never emitted (`Sample`) still runs this and re-touches inherited thunks.
- `.sdata2` constants follow emission order. Weak `.data` objects keep their space when the object's
  `.data` is referenced section-relative (`...data.0`); weak `.sbss` and unreferenced `.sdata2` objects are
  dropped by the linker.

## Changes (all 221 functions stay exact; every other object is byte-identical)

1. Vtable ownership. In this TU's view (TIINPUTFORM guards): `textinput::Base` is all inline and its weak
   vtable is emitted here; `~Decolated`, `clear`, `set` and `~CommandReceiver` have bodies in the class, so
   their key functions stay in tiString/tiTextInputBase. `GUIComponent::init` and the other header helpers
   are `inline` in the .cpp. Decolated, CommandReceiver and GUIComponent vtables are no longer emitted.
2. Header classes' small functions (WithAtok stubs, Decolated/WithZi/StringBase/textdrawer/Animation
   getters, candidatebox, `~RowInfoManager`) are inline instead of strong definitions here.
3. Definitions in target order. Base's small virtuals that the target emits from the vtable tail or after
   their first caller are inline; `textinput::Base::init` is touched by an inlined
   `CommandReceiver::init()` in `Base::init`.
4. Touch order inside `onCommand`/onPress*: the original factored some blocks into non-inline helpers
   (inlined everywhere, then dead-stripped). Recovered as `usesZiPrediction`, `hasZiPredictions`,
   `checkUnfixConverting_`, `setAtokMode_`, `trimString_`, `startConverting_`, `resetRelation()` calls,
   and `int selected` before `commitPredicted`. Each one is inlined to the same code.
5. Include `tiUtil.h`/`tiGUIManager.h` first (target `.data` vtable order), the real `inputform::Sample`
   (as in tiKeyboard.cpp) after the local classes (tail and thunk order, nothing emitted for it),
   WithAtok declares `isFix/setFix/initConverting` before its overrides (tail order, same vtable).
6. Removed the `scInputForm*` dummy constants (nothing referenced them) and the unused
   `extern "C" asm` declarations; `sbCompatibleFilterEnabled` now precedes `mbHyphen` in `.sdata`
   (both were 0x01, objdiff could not see the swap).

Result: 219/221 in target order; `.data`, `.rodata`, `.sdata`, `.sbss`, `.bss` and thunk order match.

## The remaining two: a dead-stripped function after makeUpCursorPos

Target emits `getDrawModifyEndLine` and `getEndPos` right after `makeUpCursorPos`, and `0.5f` right after
`getScale`'s `1.0f` in `.sdata2`, before `calc`'s constants. No code in the target calls the two getters,
and an unused virtual call is never removed. Skyward Sword's software keyboard REL (zeldaret/ss,
`d_SoftwareKeyboardNP` symbols, read-only) has the same `makeUpCursorPos` (0x44) followed by
`StringBase::getWCString`, `getDrawModifyEndLine`, `getEndPos`, `drawFixString`. So the original file had a
function here that touched those three and first used 0.5f, and the linker stripped it as unreferenced.
Its body is not recoverable.

Proof: an external stand-in between `makeUpCursorPos` and `drawFixString` that calls the two getters and
returns 0.5f gives 221/221 in order and, with tiInputForm Matching, DOL SHA1
26116613f624061ba99c8d1a299aaa6efa85670d, 0 differing bytes. An unused `static` stand-in fixes the
function order but not the constant (unused statics are not compiled).

This stand-in is an uncalled function, so it is kept in a separate commit for the owner to accept or drop.

## objdiff `.sdata2` artifact

objdiff now scores `.sdata2` 92% (clean commit) / 96% (linked commit): the weak `GetTextColor` copy brings
the `NW4R_ASSERT` color constant `{255,255,255,0}` into `.sdata2`; the linker strips it, the original
object had it too (its `@STRING@GetTextColor` survives in `.data`). The old 100% came from the dummy
`scInputForm*` names. With the link, complete data is 3772/3772.

## Dead ends

- `s16` local before `commitPredicted`: extra `mr` (onCommand 99.84%); `int` is exact.
- Making AnmPane strong or NormalButtonAnmPane weak, moving the local classes: no effect on the tail.
- Removing `#pragma section const_type ".data"` (non-const local array): template moves to `.rodata`,
  three functions change. Left as it was.
