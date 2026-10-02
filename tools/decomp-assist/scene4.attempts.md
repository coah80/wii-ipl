# scene4 leaf — decode attempts & evidence

Branch `agent/w1008/scene4` off origin/main@e3457d11.
Scope: iplAddress, iplAddressEdit, iplSDChannelSelect are the only sub-100 units in
the scene/address + sdChannelSelect remainder (iplAddressAddSel, iplAddressInputName,
iplAddressSelect, addressHelpers, addressInputHelpers, agreeSettings, agreeHttp,
iplFaceSelect, iplNCDSetting all verified already 100% on main; no open PR claims).

## Decodes that landed (this leaf)

### Single-case `switch` produces the `b<eq> caseblock; b after` 2-branch guard
`switch (x) { case C:` emits `cmp; beq caseblock; b exit` — MWCC keeps the
dispatch's second `b` because the case-block is a separate labelled region.
Equivalent `if`, `if||`, `if&&`, `goto`-goto, `if/else`-goto all get normalized
to a single fused `beq`/`bne`. Used in:

- `Address::start_drag_event` (892B): outer `switch (mState) { case STATE_NORMAL:`
  + inner `switch (mMode) { case 0:` reproduces orig's two nested 2-branch guards.
  Residual: 7 word diffs, pure regname — nigaoe web pinned r26 (orig) vs r29
  (mine), miiPane web r29 vs r26. Allocator home-order tie; decl-hoist of
  miiPane above the `if` was a no-op (web homes unchanged).
- `Address::onEventDerived` (1080B): TRIG case falls through to ON_POINT
  (orig has NO `break`); the `mState == COVER_NORMAL || mState == NORMAL`
  guard folds to `beq`+`bne` inside the TRIG case. Residual: 81 word diffs,
  all regname — insn sequence identical.

### `addic.` fusion for `ptr = base + const` NULL-tested members
`record->attr.name` tested `!= 0` fuses into `addic.` only when the pointer is
materialized lazily at the compare — decl the local inside the `if`. Hoisted
decls emit `addi`+`cmpwi`. (movePane_onDrag `name` web.)

## Walls re-verified (evidence)

### `Address::movePane_onDrag` 92.45 (620 orig vs 612 mine)
- Orig emits `bne next; b exit` 2-branch guards for both `textBox != NULL` and
  `name != NULL` (the `b` skips to the shared `width += 0.01f` block).
- This is switch-dispatch-shaped, but every legal polarity fails:
  `switch(ptr) { case NULL: break; default: body }` bool-materializes
  (`addic/subfe/cmpwi 1` — +3 insns); `switch (p != NULL) { case true:` also
  bool-materializes; `do { if (!x) break; } while (0)` folds to single `beq`.
- Orig computes the record math (`lwz 0x70 / mulli 5 / lwz 0x274 / mulli 0x140`)
  before the textBox branch — scheduler interleave around the guard.
- Residual also regname r27↔r29 (textBox web) + loop `name` web.

### `FriendListCache::update` 95.5 (160 orig vs 156 mine)
Orig remats `mInfos + index*0x140` per use site (memset, wcsncpy,
updateFriendInfo = 3 `mulli`+`add` pairs). Mine CSEs into callee r31.
`getInfo(index)` vs `mInfos[index]` vs `(int)index` cast — all VN-identical,
still CSE. Remat-vs-pin in the unusual remat-is-orig direction; no lever.

### `AddressEdit::create` 97.45 (3280B)
Two distinct residuals:
- Wholesale r30↔r31 web-order swap: orig pins string-table const web in r31
  and `boardFile` (getScene+0xd20) in r30; mine the reverse. Webs born in the
  same source order — allocator processing order tie.
- `friendText` (this+0x2b4 / this+0x2cc) pin: orig materializes
  `addi r25, r29, 0x2b4` at decl point between `initFrame()` and `restart()`,
  reassigns `addi r25, r29, 0x2cc` mid-block — the reg+const web is pinned.
  Mine remats `addi r5, r29, 0x2b4` at each marshal. Variants tried: non-const
  `wchar_t*`, decl moved before `animator =` — both no-op. Same this+const
  pin family as get_friendinfo.

### `AddressEdit::get_friendinfo` 88.04 (336 orig vs 328 mine)
Orig: this→r28, `this+0x2b4` (mName) pinned in r29 materialized before the
FindPaneByName marshal — 2 extra insns vs mine's marshal-site remats, and one
more callee web (savegpr_28 vs my _29 window differs). Same `this+const`
pin-vs-remat wall as create's friendText.

### `AddressEdit::update_friendinfo` 99.42 (152B)
Single 2-insn scheduling swap: `addi r4,r30,0x2b4` vs `addi r3,r31,8` order
in the wcsncpy marshal.

### iplSDChannelSelect 99.58 — 7 fns
- `create` 97.74: regname r29↔r30 swap + marshal interleaves around `bl`s
  (scheduler family); insn count equal.
- `collectTitles*` ×4 (97.29–97.83): documented ties — callee-web rotations
  around the same ES_GetTitleCount/ES_GetTitles marshal blocks.
- `flushSaveDataAndMountSD` 99.66 (140B): marshal order tie.
- `setChannelScissor` 93.47 (932B): fp/scheduling family (DrawFrame-class).

## Notes
- ndiff.py NORMALIZES register names — "diffs 0" can hide regname-only
  diffs. Always confirm with raw byte-compare of `.text` (readelf -sW for
  addr/size, -SW for file offset).
- `objdiff-cli diff` is interactive-only (fails headless); use disasm_fn.py
  + byte-compare.
