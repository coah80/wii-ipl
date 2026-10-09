# o3-keyboard attempts (tiInputForm calcCursorPos / LayoutByNW4R::create, tiString inputChar)

Worktree data-d4, branch agent/w1009/o3-keyboard, base 4789b7c3. Full build at base: DOL SHA1
26116613f624061ba99c8d1a299aaa6efa85670d. Baselines: calcCursorPos 8/326, create 120/356, inputChar 13/136.

## calcCursorPos: EXACT

The 8 differences were f29/f30 swapped between the glyph-rect zero and scale.x. Target order of the three
loop-invariant FPRs is zero < scale.x < scale.y by virtual register number.

What decides it (verified with mwdbg traces and a per-pass capture, /tmp/o2-keyboard/cap-o3direct):
- FPR numbering: named locals first (reverse declaration order), then IRO temps (reverse creation order:
  late @149xx return temps below early @98xx inline params), then codegen temps in codegen order.
- In the helper form scale.x is the scaledExtent parameter temp @9875 (IRO), scale.y is a codegen load in
  the loop head, and the zero is a codegen load in the loop top. Codegen beats IRO, so zero lands above scale.x.
- Computing `right` before `lineBottom` (scale.x loaded first) fixes the registers but breaks the loop-head
  schedule. A port of MWCC's list scheduler + 750 pipeline model (/tmp/o3-keyboard/schedsim.py, reproduces
  the direct, helper and width-first schedules exactly) shows the target schedule needs the height chain
  first with one copy into lineBottom (the helper form), or width-first with two chained copies after the
  height add. Backend VN (pass 0x5976e0) flattens copy chains inside the block, so the second option is
  impossible.
- Fix: keep the helper form and hold the rect reset value in a named float local declared first. IRO does not
  propagate a constant into a deeper loop, so the local survives; declared first, it gets the highest
  named-local number, which colors it right after the two temps (f29). Assigned right before the loop.

Trials that did not work: 128 helper/direct mixes (best 8), width-first + named-local/chained/struct/array
intermediates (7-8, structs 282+), nested inline height helper (7), per-function single/pair pragmas on
width-first forms (opt_propagation off: 304, others unchanged), zero via named const global (folded, 8),
inline returning 0.0f (propagated, 8), zero local declared inside the loop or right after scale (45),
initialized at declaration (35), const local (propagated, 8).

Result: calcCursorPos 8 -> 0 differing, pool identical, tiInputForm 219 -> 220/221 exact.

## LayoutByNW4R::create: not exact (120)

All 120 differences are GPR renames. Target saved-register roles (verified instruction by instruction):
r31 AnmPane vtable, r30 table base, r29 bindingName, r28 buttonIndex, r27 button, r26 animationPane,
r25 animationIndex, r24 allocator, r23 this, r22 count, r21 NormalButtonAnmPane vtable,
r20 zero/textBox/early zero, r19 file pointer (@13697), r18 resource (@10823)/editBuffer.

Coloring takes the lowest free register in the pool and adds new saved registers from r31 down, so this forces
the coloring order ... allocator, this, count, NBAP-vtable, zero, textBox, file, resource. Simplify removes
nodes in ascending vreg order per pass (regsim reproduces 137/137), so count must be removed right before
`this` and right after the NBAP vtable temp (r164). Parameters are always r32-r34, named locals next (reverse
declaration order), IRO temps next, codegen temps last. Scan degrees (/tmp/o3-keyboard/scans.py): count starts
at 30 against K=29; `this` cannot stay >= 29 into pass 2 without spills. So count has to be a codegen temp
numbered above r164, i.e. a hoisted load. It cannot be one: csButtonAnimations is global .data (STB_GLOBAL in
the original object), loads through `button` are fIsPtrOp and CodeMotion never hoists those, and the inner
loop calls functions. Unresolved contradiction; the target graph must differ in a way not found.

regsim: declaration order alone (params pinned) reaches 6/12; with count free as a high temp plus resource and
file placed among named locals, 12/12. Tried: count removed (button.count in the condition: reloaded each
iteration, 106), count in for-init / block / loop scope (133), const-ref inline helper owning the inner loop
(106, still reloaded), addButtonAnimation body written into create with named file/resource (139, moved the
vtable temps). Header experiment reverted.

## inputChar: not exact (13)

Per-pass capture (/tmp/o2-keyboard/cap-o3ic0) of the current source: the then-block `li mCount, 0` survives
every pass. Findings that constrain the original:
- GC3 VN records every li but only replaces li whose destination is a codegen temp (coalesce window); VN
  flattens copy chains to the first holder and deletes `mr d,s` when d already holds s; VN removes
  overwritten stores in the block.
- The first indexed store keeps `slwi/sthx` with r6, so the index had two reaching definitions during both
  const-prop runs (0x622a20 at passes 02 and 15), and the second definition vanished afterwards (VN 19/25,
  DCE 20, coalescing, or post-regalloc VN). Only a copy or a window-temp li can vanish that late.
- A named `wchar_t* out = input` for the terminator reproduces the target's separate second-store base
  (post-regalloc VN turns its addi into `mr r4,r5`), u32 index with `clrlwi` count: 60 diffs, only the
  then-block li left (rb2 in /tmp/o3-keyboard/ic2.txt).
- Read-back then-blocks (n = out[n], n = *out, length scan) and ternary index/arms fold in IRO because IRO
  knows the buffer and n are zero (60-74). switch on u32 still compares with cmpwi (60-73).

## Round b (worktree data-d4, branch agent/w1009/o3b-keyboard, base e47a8e94)

### LayoutByNW4R::create: EXACT (120 -> 0)

Three structural changes, each found with mwdbg captures, regsim, and a positional vreg-to-target-register map
(/tmp/o3-keyboard/cr/posmap.py: aligns backend-04 with the object and reads the target register at each def):

1. Loop. `csButtonAnimations` is `const` in the original. It sits in .data only because entry 1's bindingName
   is filled by the dynamic initializer (the target's slot is zero with no relocation; __sinit stores it). With a
   const table, `button.count` and `button.bindingName` read directly in the loop are hoisted by the backend, so
   count becomes the late codegen temp that round a predicted. The loop body is written out as in tiToolBar's
   matched create; the addButtonAnimation helper is gone.
2. textBox. It must be numbered above the `&button.files[i]` CSE temp, so it is an inline local: an inline
   `getTextBox()` getter that returns a local, used by create and init. The L"" literal has to stay in the
   callers. Inside an inline member it becomes a weak @STRING@ object and .sdata grows from 40 to 46 bytes.
3. Row list. Base::create's code is duplicated in create, not inlined: inlining reverses the relative numbering
   of the inline's locals (inline locals are keyed by declaration order, named locals by reverse declaration
   order). Both functions now use the same code: C89 declarations rows, row, next, previous, selectedIndex,
   listEnd, info. `row` is reused (`row = &rows[max]; row = &rows[row->Next];`) so the selected row is a split
   IRO temp. The second mpInfo load goes into `info`, declared after listEnd. The head index is a block-scoped
   `head`. Base::create stays exact and loses the RowCursor carrier struct.

Dead ends: Base::create auto-inlined (bl, too big), `inline Base::create` (27, reversed row registers), a
RowInfoManager::newLine() helper (reloads mpInfo, 74 insns), a setupTextBox() helper holding SetString (exact
code, but .sdata changes).

### Decolated::inputChar: not exact (13)

Mechanism behind the target's vanished '\n' then-block, from per-pass PCode captures on GC3:
- VN (0x5976e0) merges li's within a block at pass 01 and across single-predecessor chains at passes 19/24.
  A redundant li disappears only if it matches a value-number record whose holder is the same register with the
  same index. Records are keyed by opcode, flags and operand count. Li's created by const-prop have 3 operands,
  so they form their own record chain.
- The function-start zeroing (`input[4..0] = 0`) owns the 2-operand `li 0` record in the mode-3 block's chain,
  so any 2-operand `n = 0` reset survives. That covers main's CharacterOutput and every class, inline, ternary,
  switch, reference, pointer and read-back form tried.
- A POD struct with a constant initializer (`LinePosition position = {0}; ... position = LinePosition();`) stays
  in memory through both const-prop passes. Array-to-register (pass 07) gives it a new vreg, const-prop (pass 17)
  turns its defs into 3-operand li's, and VN at pass 24 deletes the then-block def. This reproduces the dead
  `cmplwi` with no branch (tiny tests struct1/tc, real-function variants p1/z2).
- Remaining blocker for that family: the input[0] store's zero then belongs to the struct init's codegen li,
  which pass 24 replaces with the function-start zero. The result is `sth r5` instead of `li r6,0; sth r6`, and
  the `mr r4,r5` before the second store is lost (133 insns, 73 diffs). The target needs the store and n to share
  one register whose li comes first in the block and whose then-block def is deleted. None of about 120 variants
  reached that (/tmp/o3-keyboard/{t,t2,ic,grid}). combosweep: 13 -> 13.

### tiInputForm link (not flipped)

The unit is 221/221 exact with code and data at 100%, but a trial Matching flip fails to link: the vtables for
Decolated (tiString.o) and CommandReceiver (tiTextInputBase.o) are multiply defined, and GUIComponent's is also
emitted here. There are also about 96 extra bytes of anonymous .sdata2 floats, Base::RowInfoManager::~RowInfoManager
is emitted as a global (the target inlines it into ~Base), and only 37 of the 221 functions are in target order.
Flip reverted; the DOL is unchanged.
