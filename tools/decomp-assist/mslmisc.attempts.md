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

## DECODE: enqueue*Notice u64/pointer signatures (SOLVED — r4 anomaly was MWCC u64 marshaling)

The "dead leading arg" was wrong: MWCC lands a **u64 arg only in ALIGNED register pairs**
(r3:r4, r5:r6, r7:r8). For a member fn (this=r3) a u64 first param goes to r5:r6 and **r4 is
never materialized** — no dead param at all.

Verified signatures from orig def bodies (which arg regs get stored into the command struct):
- `enqueueChannelNotice(u64 titleId, u32 value)` — def stores r5:r6→titleId, r7→values[0]
- `enqueueMoveNotice(u64 titleId)` — def stores r5:r6 only
- `enqueueStateNotice(u64 titleId, u32 state)` — r5:r6 + r7
- `enqueueDeleteNotice(u64 titleId)` — r5:r6 only
- `enqueueErrorNotice(ESTitleId** titleIds, ESTitleId** secondaryTitles)` — stores r4,r5
- `enqueueCommandNotice(ESTitleId**,ESTitleId**,ESTitleId**)` — stores r4,r5,r6
- `enqueueNotice(u32,u32,u32)` — stores r4,r5,r6 — unchanged, verified correct
- `enqueueResultNotice(u32)` — stores r4 — unchanged

Orig callers confirm: iplSDMemory's onDialogState14/16/18 load `lwz r5,0x80(r4); lwz r6,0x84(r4)`
(a u64 member `mTitleIds[i]`) directly into r5:r6 — never touching r4.

Fix (all kept): header decls + defs + symbols.txt mangles (`FUxUl`/`FUx`/`FPPUxPPUx`/`FPPUxPPUxPPUx`);
sdChannelTitle call sites pass `scene->mTitleId`/`temporaryTitle` directly (dropped the
`((u64)page<<32)|index` synthesize). All defs + all callers now instruction-identical.

Access cleanup: orig callers called these as private members — extended the header's existing
`#if defined(...CPP) public:` gate with `IPL_SD_CHANNEL_MEMORY_CPP` (defined at the top of
iplSDMemory.cpp), letting the 5 banned `extern "C" iplSDChannelSelect_813DXXXX` stubs in
iplSDMemory.cpp be deleted and replaced with real member calls (insn-identical, UND names
now match orig's re-split relocs).

Result: sdChannelTitle fuzzy 99.98883 (+648B matched code; both enqueue call sites 100%),
sdChannelSelect defs all instruction-identical, sdChannelMemory callers insn-identical.

## TIE: flushSaveBeforeExit eval-order (98.59)

Insn+reloc-identical except a 6-word window: orig `lis r3` (smArg base→r3), `lwz r4,0x94` (stw-mgr),
`stw`, `lwz r4,0x28` (heap), `lwz r3,0x94` (flush receiver — reloaded LAST). Mine: base→r4,
receiver-load before heap-load. Orig evaluated the `flushAsync` ARG before the receiver reload.
Tried: `saveHeap` local (before/after stw, decl-init, separate assign — emits at-birth or at-use,
never between), `saveData`/`mgr` local (caches receiver → 5-insn form, wrong), nested
`flushAsync(System::getMem2App())` (same as original), explicit `manager` receiver temp born
between `saveHeap` and the call (identical — remat'd at use). All ~6-word identical or regression.
Precise residual: mine emits `recv lwz r3,0x94` before `arg lwz r4,0x28`; orig swaps them —
receiver-first vs arg-first marshal order, scheduler tie-break on two independent remat loads.

## TIE: ConstructOpAnalyzeGLGR 20-diff window (91.79)

239/239 insns — orig interleaves `lhz r31,0x1c` (sheetGlyphCount) + `lhz r23,0xe` (dataBlockCount)
mid-flag-chain (issued at birth, deep-callee homes); mine emits both at-use (`lhz r26/r25`,
~8 insns later). Same callee-web rotation family. Kept: flags-first reorder (24→20 diffs) +
the second `pGlgr = &font->glgr` assignment (removing it = 113 diffs). Decl-init variant no-op.

Round-2 decode of the window: both sides interleave the same inlined helper tree
(CalcSizeFlagSet + CalcOffsetSheetFlags + ROUNDUP chains + the 0x1c/0xe ctx loads) — only the
issue ORDER inside the ready-set differs. Orig issues `lhz r26,0x1c`/`lhz r25,0xe` ~10 insns
later in the chain than mine. Tried: stepSheetFlags-after-flagsSheetsOff reorder (97.94,
regression) and inlining both into use sites (96.99, regression) — committed form stands.

## ARTIFACT: .sbss2 8B vs 1B (ut_ArchiveFontBase) — splitter extent attribution

orig's `.sbss2` = 8B: `LOAD_GLYPH_ALL` (1B) + 7 anonymous tail bytes. Not a missing object —
symbols.txt shows `DefaultBlackColor` at 0x81696010 (8-aligned): the 7B is the DOL's alignment
padding absorbed into this TU's reconstructed extent. Same pattern (sbss2=8) across many orig
.o files (zi8getc2, sha1, lyt_material, ...). No legitimate source lever — adding a second
unnamed/anonymous object is banned; no static-local evidence in ghidra decomp.

## ARTIFACT: .sdata2 weak-emission literals (iplSDChannelTitle)

Mine emits `2.0f`/`3.0f` inside weak `HermiteIntp<f32>::get` (TU runs
`new math::HermiteIntp<f32>()` at line 227); orig's .o shows all-UND for the weak emission —
splitter weak-dedup artifact. .sdata2 byte-content + fuzzy already 100; only the @literal
OBJECT granularity differs (orig merges, mine carves) — no source lever found that suppresses
the weak emission without changing semantics.

## Status

- iplSDChannelTitle: fuzzy 99.98883, code 18476/18624, data 1976/1976 (all data 100%).
  Only flushSaveBeforeExit 98.59 — the eval-order tie above. Remaining granularity = weak-emission
  literal artifact.
- ut_ArchiveFontBase: fuzzy 98.468, code 4164/5120, data 96/96. Only ConstructOpAnalyzeGLGR 91.79
  (20-diff scheduler window) + .sbss2 extent artifact.
- DOL sha1 `26116613f624061ba99c8d1a299aaa6efa85670d` verified. No shims; both units stay NonMatching.
