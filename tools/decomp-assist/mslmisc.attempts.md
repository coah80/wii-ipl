# mslmisc leaf attempts

Owned units: `src/scene/sdChannelTitle/iplSDChannelTitle.cpp`, `libs/NW4R/src/ut/ut_ArchiveFontBase.cpp`.
MSL checked via live report: only `MSL_Common/wprintf` incomplete — stays in misc1b's notes.

## DECODE: SDButton::setEventHandler retail dead-param (SOLVED)

orig's real decl was **1-arg** `setEventHandler(EventHandler*)`. Evidence:
- Every orig call site (title ×2, select ×4) emits a bare `bl` with only r3/r4 — never `li r5,0`.
- The 5-insn DEF (`lwz r3,0x60; lwz r12,0; lwz r12,0x38; mtctr; bctr`) forwards to `Manager::setEventHandler`, a 1-arg weak virtual — `optOut` was never consumed.
- `Button::setEventHandler` (a DIFFERENT class, genuine 2-arg impl at 0x8139C93C) DOES emit `li r5,0` in iplFocusObject — MWCC materializes default args, so SDButton's missing r5 means the decl never had it.
- The 2-arg mangle in symbols.txt was an author mislabel inherited from `Button`'s real 2-arg.

Fix (all kept): `iplSDButton.h` decl → `void setEventHandler(::gui::EventHandler* event);`; `iplSDButton.cpp` def → 1-arg; call sites in sdChannelTitle/sdChannelSelect → 1-arg; `config/43U/symbols.txt` line 4817 renamed `...8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler` → `...8SDButtonFPQ23gui12EventHandler`. Flipped 5 fns to instruction-identical + all sdChannelTitle data sections to 100%.

Mechanism note: renaming a `.text` address in symbols.txt propagates through the splitter into orig's DEF name AND every caller's UND reloc name — the legit rename lever.

## UNSOLVED: enqueue*Notice leading dead-arg (r4)

`SDChannelSelect::enqueueChannelNotice(u32 controller, u32 page, u32 index, u32 value)` and
`enqueueStateNotice(u32 controller, u32 state, u32 type, u32)` (4×u32 each; defs build
`command.titleId = ((u64)page << 32) | index` — proven 4×u32, not u64).

orig call sites marshal r5/r6/r7 but **never write r4** (arg1 `controller` — dead param the
def bodies ignore; iplSDMemory callers DO materialize it). Same dead-arg family as
setEventHandler but on a LEADING arg — no decl form reproduces it:
- arg-count reduction shifts the marshal left (breaks r5/r6/r7 positions)
- defaulted params must be trailing
- `(u32,u64,u32)` still needs `li r4,0` for arg1
- `scene->mPage`/`mIndex`/`channel` as arg1 all emit real loads (`lwz`/`mr`) — orig has none
- r4 is call-clobbered at both sites (`bl findChannelObject`, `bl isReceiveScheduleStopped`)
  so no "value already in r4" source expr exists

Residual = `+li r4,0` plus marshal-order (orig emits r6-before-r5 / addi-first) — scheduler family.

## TIE: flushSaveBeforeExit eval-order (98.59)

Insn+reloc-identical except a 6-word window: orig `lis r3` (smArg base→r3), `lwz r4,0x94` (stw-mgr),
`stw`, `lwz r4,0x28` (heap), `lwz r3,0x94` (flush receiver — reloaded LAST). Mine: base→r4,
receiver-load before heap-load. Orig evaluated the `flushAsync` ARG before the receiver reload.
Tried: `saveHeap` local (before/after stw, decl-init, separate assign — emits at-birth or at-use,
never between), `saveData`/`mgr` local (caches receiver → 5-insn form, wrong), nested
`flushAsync(System::getMem2App())` (same as original). All ~6-word identical or regression.

## TIE: ConstructOpAnalyzeGLGR 20-diff window (91.79)

239/239 insns — orig interleaves `lhz r31,0x1c` (sheetGlyphCount) + `lhz r23,0xe` (dataBlockCount)
mid-flag-chain (issued at birth, deep-callee homes); mine emits both at-use (`lhz r26/r25`,
~8 insns later). Same callee-web rotation family. Kept: flags-first reorder (24→20 diffs) +
the second `pGlgr = &font->glgr` assignment (removing it = 113 diffs). Decl-init variant no-op.

## Status

- iplSDChannelTitle: .text 99.9, all data sections 100% (baseline was data 12.1%). Three
  sub-100 fns — all at the anomalies/ties above.
- ut_ArchiveFontBase: .text 98.5 — the 20-diff window.
- DOL sha1 `26116613f624061ba99c8d1a299aaa6efa85670d` verified. No shims; both units stay NonMatching.
