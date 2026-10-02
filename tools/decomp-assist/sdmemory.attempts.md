# sdmemory leaf — iplSDMemory attempts log

Worktree: `/home/ubuntu/repos/wii-ipl-sdmemory`, branch `agent/w1010/sdmemory` on origin/main@813660b9 (post-#980).
Unit: `src/scene/sdChannelMemory/iplSDMemory.cpp` → `build/43U/obj/src/scene/sdChannelMemory/iplSDMemory.o`.
Report: unit fuzzy 99.73, data 100% (3344/3344), 64/66 fns. Two incomplete fns, both now
**instruction-identical** to orig — residuals are allocator-internal operand diffs only.

## create — 99.16 (1064 = 1064 insns, 0 reloc-target diffs)

Verified: every instruction matches; every R_PPC_REL24/ADDR16/SDA21 reloc target
matches at identical offsets (`bl` raw immediates differ only by link layout of
weak-emitted locals — objdiff resolves them).

Residual = a 3-web callee-pin rotation:
- orig: string-literal base (`lis;addi` of lbl_81655CA0) → **r31**; a second data
  base (`lis r26,0` + `0x80(r26)` singleton-member loads) → **r26**; the created
  `layout::Object*` web (`mr rX,r3` after `__nw`/`__ct__`, used for ~12
  `bindToGroup` receivers) → **r30**.
- mine: litbase → r30, singleton-base → r31, obj → r26.

The middle arg webs (r27=this, r28, r29) are stable; only the three late pins
rotate. Same documented family as BS2Tick/AddressEdit/wprintf pinned-const
ordering — MWCC's web-priority is internal; no source lever shifted it
(see also drawTransferTitles note below on regname ties).

## drawTransferTitles — 98.87 (451 = 451 insns, 0 normalized diffs)

Verified instruction-identical (opcode sequence + operand shapes) and identical
reloc targets. Residual = stack-frame slot numbering + one regname tie:

- orig keeps the two arm-local `GXColor` copy objects at the **lowest** stack
  slots 0x8/0x0c (written by stb×4 quads, never read — dead-store locals kept by
  MWCC); arg-copy temps at 0x18-0x27; `gx` sources at 0x38/0x3c.
- mine places them adjacent to their `gx` sources (0x30-0x3f region); temps at
  0x10-0x1f; `bodyPane` web home r30 vs orig r29.

### Decodes that LANDED (kept)

- **Missing block**: orig emits THREE stb×4 quads per arm — the `gx` memberwise
  copy into a **dead `GXColor` local** plus two arg-copy temps. Source form:
  ```cpp
  GXColor gxActive;
  writeFourFlagBytes(&gxActive.r, 0x34, 0xBE, 0xED, 0xFF);
  GXColor gxActiveCopy = gxActive;                       // memberwise C-struct copy-init
  setTitleRowColors(titleText,
                    nw4r::ut::Color(*reinterpret_cast<const nw4r::ut::Color*>(&gxActiveCopy)),
                    nw4r::ut::Color(*reinterpret_cast<const nw4r::ut::Color*>(&gxActiveCopy)));
  ```
  `Color(*(const Color*)&gxCopy)` binds the implicit `Color(const Color&)`
  copy-ctor which expands memberwise (source is non-Color-typed, so `*&` does
  not collapse). The copy stays "live" enough to be emitted because the arg
  temps reference it.
- **Newline counting loop**: `if (newline != NULL) { const wchar_t* sep = L"\n";
  while (newline != NULL) { ++lineCount; newline = wcsstr(newline + 1, sep); } }`
  — reproduces orig's `cmpwi;beq` guard + pinned `li pin,@lit` + counter.
- **Line render loop**: `s32 lineIndex = 0; if (totalLines > 0) {
  const wchar_t* lineSep = L"\n"; while (lineIndex < totalLines) {...} }` —
  peeled-entry while (addic.+ble guard + bottom cmpw) + pinned literal +
  counter declared outside the guard.
- **`bodyY` decl position**: `f32 bodyY = memoPosition.y;` moved BEFORE the
  `FindPaneByName` calls → MWCC pins it in callee f31 across the virtual calls
  (orig `lfs f31,0x30(r3)` at the copy + reuse, no reload). This was the last
  structural diff — taking the fn to 451=451.

### Variants tried and REVERTED (each regressed)

- `memoPosition.y` used directly instead of `bodyY` → per-use reloads (455,14d).
- `f32 bodyY = translation.y` → frame reshuffle, extra stfd saves (453,14d).
- `f32& bodyY` alias → worse (455,14d).
- `Color x = *&gx` + `Color(x)` args → `lwz;stw` WORD copies (Color-typed source
  selects the word-copy path / user `Color(const GXColor&)` ctor) (444,21d).
- `ut::Color` locals + field writes + `*(GXColor*)&local` args → word copies (444).
- fn-top `GXColor a,b` + `a = gx` assignment → out-of-line `__as__` call (449,14d).
- fn-top `GXColor copies[2]` + field writes → array slots land even deeper
  (0x58/0x5c) — declaration order does not drive MWCC stack order.
- `Color(*&copy)` + `Color(*&gx)` mixed-source args → extra lbz reloads (459,8d);
  swapped order `Color(*&gx)` + `Color(*&copy)` → same (459,8d) — MWCC does not
  VN-unify the two sources' fields here.
- `*&gx` args twice + dead copy → shared temp `mr r5,r4` (one temp) (443,8d).
- Inner `{ }` block around each copy+call → slots unchanged (0x38/0x30).

### Frame-slot wall

Orig allocates the dead `GXColor` copies at 0x8/0x0c (first allocatable slots);
mine allocates them adjacent to their `gx` sources. Every declaration/scope/
form variation either lands the objects at the same or deeper slots, or changes
the instruction stream (documented above). The slot ordering is allocator-internal
—not driven by declaration order, scope depth, or address-taken-ness in any form
found. Same class as the earlier "dead Color local eliminated" investigation.

## Rules compliance

- No `lbl_` names, no volatile use-site casts, no uninit-var probes
  (all store sources are provably initialized), no score-only/padding objects.
- `libs/RVL_SDK/src/wad` and `src/BS2` untouched (owner's Codex workers).
- The per-TU emission gate in `iplSDChannelTitle.h` (`IPL_SD_CHANNEL_MEMORY_CPP`)
  added in a prior pass — lets this TU UND-reference helpers owned elsewhere.

## Remaining to flip

`create` 100 needs the 3-web callee-pin rotation to resolve (litbase→r31,
singleton→r26, obj→r30). `drawTransferTitles` 100 needs orig's frame ordering
(dead GXColor copies at 0x8/0x0c, temps 0x18-0x27, gx 0x38/0x3c) + `bodyPane`
in r29. Both verified instruction-identical — pure operand/regname ties.
