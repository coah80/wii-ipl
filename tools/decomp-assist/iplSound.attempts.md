# iplSound.cpp — attempts log (singles leaf)

Final state: .text 98.98 fuzzy; 55/57 fns instruction-identical after
name-stripping. .ctors/.data/.rodata/.sbss/.sdata2 all 100%. .bss 70.65
(symbol-extent artifact, contents byte-identical).

## Verified decodes

- **Weak-fn emission order = first-ODR-use.** Weak copies of in-class /
  inline defs emit immediately after their first non-inlinable user;
  trivial inlines and vtable-driven emissions defer to the end.
- **`_seBlk` decode:** orig's named `__dt__Q33ipl3snd6UnkClsFv` thunk
  requires `_seBlk` to be a global of `struct UnkCls { tagSSeInfo blk[16]; }`
  with an implicit dtor (emits `b __destroy_arr` thunk). A raw
  `tagSSeInfo _seBlk[16]` or `typedef ... UnkCls[16]` instead emits
  auto-named `__arraydtor$NNNN`.
- **`EGG::ArcPlayer::startSound(&handle, idx)`** (qualified call to the
  virtual at slot 0x34) suppresses virtual dispatch, inlines to
  `detail_StartSound`, and emits its weak copy at first-use position
  (right after `startSEIndex` in orig).
- **startSE/startSEIndex redundant `block` re-test:** orig re-tests
  `cmpwi block; beq` between two `GetId()` checks — written as
  `(block != NULL && GetId()==0x39) || (block != NULL && GetId()==0x35)`:
  two `&&` clauses in one `||`, single shared return-block tail. Nested
  `if` adds insns; single `||` drops the re-test.
- **`.sdata2` literal order = parse order:** a dead
  `f32 pan = 0.0f; pan = x/rect.right;` in `holdSEwithPosDis` creates the
  0.0f literal early (MWCC folds the dead store, keeps the literal) —
  reproduces orig order [0.9, 0.0, 2.0, 1.0, 30, 60] exactly.
- **`stopSE`/`resetAllSound` are `void`** in orig (no `li r3,0` epilogue);
  header changed `int`→`void`. `stopSE` loop compare is
  `handle == &_seBlk[i].handle` (operand order → `cmplw r24,r27`).
- **`__sinit` register sequence:** `__construct_array(_seBlk)` →
  `__register_global_object(0, ~UnkCls, record@0)` → `~tagSBgmInfo`/`_bgmBlk`
  (record@0xCC) → `~System` (record@0xD8) → `~BannerSoundPlayer`
  (record@0x710).

## Unresolved

- **`__ct__Q33ipl3snd6UnkClsFv` extra weak emit (+~0x4C).** The implicit
  ctor for `UnkCls _seBlk` emits a weak copy in mine; orig has none.
  Tried: implicit ctor, `UnkCls() {}`, `~UnkCls() {}`, typedef array,
  removing `#pragma force_active on` — still emits. Likely MWCC-version
  emission difference.
- **`__dt__Q34nw4r2ut11NonCopyableFv` extra weak emit (+~0x3C).**
  `~NonCopyable() {}` in `libs/NW4R/include/nw4r/ut/inlines.h` is
  ODR-used via `~SoundHandle` base-dtor call. Removing it removes the
  emit but cascades: `tagSSeInfo`/`SoundHandle` become trivially
  destructible → `__sinit` switches `bl __construct_array` to
  `bl __ct__UnkCls` and regresses further. Reverted.
- **`.bss` 70.65%:** byte-identical layout; orig's symbols.txt extends
  `_seBlk`=0xD8 / `sSystem`=0x63C over MWCC's `__register_global_object`
  chain-record slots and omits `...bss.N` record symbols — pure
  symbol-extent artifact, no source lever.
