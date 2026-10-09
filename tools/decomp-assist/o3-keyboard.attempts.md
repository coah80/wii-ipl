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
