# opus-sdcs: iplSDChannelSelect collectTitles* (2026-10-08)

Start: ByUsage 4/101, FromNandUsage 4/102, ByChannelOrder 7/126, BySpecialChannels 16/361.

Shared diff: `lwz secondUsage[0]` scheduled above `stw ++*titleCount` in ours, after it in target.
- `*titleCount += 1`, `(*titleCount)++`, `titleCount[0]++`, `= *titleCount + 1`: no change (4).
- `!(a < b || c < d)`, nested ifs: no change. static inline usage predicate: 40 diffs.
- function-scoped IRO 0 / IRO 1: no change.
- casts `(s32*)secondUsage`, `const_cast`, `(s32*)(u32)`, local non-const copy (also under IRO 0): no change.
- mwdbg on a standalone repro: the load is hoisted before regalloc; loads through a pointer-to-const
  PARAMETER are treated as unaffected by any store (casts do not remove it). Only a non-const
  `s32*` parameter keeps source order: repro then matched the target byte for byte.
- The `PClPClPUxPcPUl` mangling was decomp-assigned (symbols.txt names were invented), so the
  params become `s32*` and the 5 symbols are renamed to `FPlPlPUxPcPUl`.
  => ByUsage 0, FromNandUsage 0, BySpecialChannels 0, ByChannelOrder 3.

ByChannelOrder residual: `mulli r0/add r3,r17,r3` vs target `mulli r4/add r0,r17,r3`.
- if/else vs ternary, `getChannel`, `hasLoadedBnr`, row pointer, ref/ptr locals, idx/manager locals
  in either order, inverted branch: 3-8 diffs.
- regsim: declaration order cannot reach (0/2), IRO temps @162/@164 for mgr/sum get low vreg numbers.
- inline Manager member with getTitleID's body (`getEntryTitleID(page, channelOrder[order])`): exact.

Result: 129/129 exact, gate PASS.

## Link (configure.py -> Matching)
First link: DOL SHA1 798af348..., .data 0x20 short and two swapped calls.
- objdiff missed that `draw` calls `ipl::math::VEC3(f,f,f)` and `getChannelPanePosition` calls
  `nw4r::math::VEC3(f,f,f)`, because the two weak bodies are identical. Fixed the local in draw
  and made getChannelPanePosition return `nw4r::math::VEC3` (NRVO builds it in the return slot,
  and callers only read .x/.y).
- Target .data has 0x20 zero bytes (deduped weak vtables) before the anonymous handler vtables.
  iplChannelSelect emits `HermiteIntp<VEC3>` and `Interporation<VEC3>` weak vtables at the same
  spot. Dropped the SD-only full `HermiteIntp<VEC3>` specialization in iplInterporation.h so the
  generic template (with the SD `get()` already there) is used: .data 0xab0, as in the target.
- Removing the unreferenced handleDeleteComplete/handleStorageCheckComplete: no DOL change (they
  get dead-stripped), so I reverted it.
Result: DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, gate PASS, linked code 33828.
