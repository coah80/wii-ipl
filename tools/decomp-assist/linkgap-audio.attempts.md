# linkgap-audio: eggAudioExpMgr — Equivalent-but-unlinkable analysis

Branch: agent/w1005/linkgap-audio. Unit stays **Equivalent**.

## Status

Per-symbol match is complete: all 8 .text fns + the 0x78 vtable match orig
(fuzzy 100.0 code+data, every fn individually 100). The .o emit set now
matches orig's exactly (see gates below).

**Remaining linker-visible diff: secondary-vt thunk emit order.**

- orig `.text` tail: `[@52@__dt__SimpleAudioMgrWithFx @+1fc][@52@calc__SimpleAudioMgr @+204]`
- mine:               `[@52@calc @+1fc][@52@__dt__ @+204]` (swapped)

Both thunks are byte-identical bodies, so objdiff fn-level fuzzy is 100 for
each — but the .o's symbol order carries into the linked DOL, so flipping
Matching fails the DOL hash. This is the *only* blocker.

## Emit-set gates (kept)

`EGG_AUDIO_EXPMGR_NO_INLINE_VIRTUALS` is defined at the top of
eggAudioExpMgr.cpp and gates these headers (TU-local: other TUs are
unaffected since the macro is only defined in this .cpp):

- `libs/EGG/include/egg/core/eggAudioArcPlayerMgr.h` — 9 ArcPlayer virtuals
  (openArchive/openDvd/openNand/setupMemory/close/loadGroup/startSound/
  prepareSound/holdSound families) -> non-inline decls for this TU.
- `libs/EGG/include/egg/core/eggAudioHeapMgr.h` — SoundHeapMgr
  `loadState`/`getCurrentLevel` -> decls.
- `libs/NW4R/include/nw4r/ut/Lock.h` — `detail::AutoLock<OSMutex>` ct/dt ->
  decls.

Without the gates MWCC weak-emits 10 extra inline fns (ArcPlayer
hold/prepare/startSound x9 + NonCopyable/AutoLock/SoundHeap helpers) that
orig's .o does not contain. With gates the emit set is byte-for-byte orig:
same 8 .text syms at the same offsets/sizes + `__vt__` at .data+0x0/0x78.

Residual cosmetic diff (does not affect the link): orig's
`__ct__AudioFxMgrArg` and `SaveState` are STB_GLOBAL; mine STB_WEAK.
Both dedup/resolve identically at link.

## Thunk-order mechanism (decoded)

Surveyed every orig .o with >=2 `@N@` adjustor thunks; my compiler
reproduces orig's order in ALL of them (iplSound, iplGCWindow,
iplMemoryCard, MyTiBg, tiCellPhone, iplBoard, ...) EXCEPT this unit.

Best-fit model for orig's ordering: thunks emit in the order the
*overriding virtuals are declared in the most-derived class*, with
thunks for inherited overrides emitted after the class's own declared
virtuals:

- SimpleAudioMgrWithFx declares `[~dtor, initialize]` -> own dtor thunk
  first, then the inherited `SimpleAudioMgr::calc` thunk -> [dt][calc] = orig
- ipl::snd::System declares `calc` before `~System` -> [calc][dt] = orig
- iplMemoryCard `[onTrig,onLeft,onPoint,~dt]` -> that order = orig
  (NOT .text def order, which is [onPoint,onLeft,onTrig])
- tiCellPhone `[~dt,updateInput,calc,draw,init]` = orig

My build instead emits thunks in *reverse secondary-vt slot order*
(the .rela.data stream is written backward — observable on every unit;
extraction .os sort relocs so orig's real write order is unknowable).
The two orders coincide for every surveyed unit except this one — it is
the only unit where a derived-declared dtor and an ancestor-declared
override (`SimpleAudioMgr::calc`, declared in the base) disagree.

## What flips it (and why it was vetoed)

Adding ANY second polymorphic class whose vt is built in this TU and
*shares* the secondary base flips the pair to orig's [dt][calc]:
verified with `class Sample : public SimpleAudioMgrWithFx` (emit
`[dt_WithFx][calc][dt_Sample]` — the parent's set comes out in forward
slot order once WithFx's vt is built as a parent). An unrelated
polymorphic class (no shared base) does NOT flip it; a declared-but-
never-defined derived class does NOT flip it (vt never built).

Mechanistically: orig's TU very likely caused WithFx's vt to be built
*as a parent* (a second derived class whose vt anchored elsewhere —
e.g. EGG's real `ipl::snd::System`-style class compiled in another TU
is the only known retail derivee), which emits the parent's thunks in
forward slot order. Any such class is invented here -> owner veto
(not in retail symbols). Orig's .o emits exactly one vtable, so no
second polymorphic class was ODR-emitted in the real TU either — the
trigger lived in code we cannot see (or is a compiler-version artifact).

## Tried and rejected (all still [calc][dt])

- dtor declared after `initialize` in the class decl
- dtor DEFINITION moved before/after ctor in the .cpp
- unrelated polymorphic class (no shared secondary base)
- derived class declared but never defined (no vt build)

## What would close it

A legitimate source construct that causes a second vt-build sharing
the ArcPlayer secondary vtable in this TU, or a linker-level symbol
ordering mechanism (none exists: symbols.txt is label-only, linker lays
out .text in .o symbol order). Until then: Equivalent.
