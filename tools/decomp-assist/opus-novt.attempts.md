# opus-novt: per-TU novtable switches

Method: full `ninja`, then SHA1 of all 1027 `build/43U/src/**/*.o` compared with a
baseline from origin/main ca98b14a, plus the DOL SHA1. A variant is kept only if
no object changes.

| # | Change | Result |
|---|--------|--------|
| 1 | `LangFile`/`LayoutFile`: out-of-line virtuals for everyone | iplChannelTitle.o, iplSDChannelTitle.o change, DOL changes. Both TUs need weak copies of `~LangFile` (88), `read` (4), `checkData` (8), `isFinished` (8), `isFatalError` (8), `~LayoutFile` (92) and weak `__vt__LangFile`/`__vt__LayoutFile`. |
| 2 | `LangFile`/`LayoutFile`: inline stub virtuals for everyone | iplNand.cpp fails (redefinition of the real bodies); 46 other objects gain weak copies. |
| 3 | `MemoryBase`: drop the `IPL_CHANNEL_TITLE_NOVTABLE` novtable switch | no object changes. **Kept.** |
| 4 | primary `HermiteIntp` under the macro: drop `__declspec(novtable)` | no object changes. **Kept.** |
| 5 | `HermiteIntp` macro block disabled for everyone (`#if 0`) | iplChannelTitle.o, iplSDChannelTitle.o change. |
| 6 | `HermiteIntp` macro block enabled for everyone (`#if 1`) | ~50 objects change. |
| 7 | `gui::Interface` novtable for everyone | ~20 objects change (saveDataEdit, sdButton, setting, dialog window, ...). |
| 8 | `gui::Interface` never novtable | iplGCSaveData.o, iplMemoryCard.o gain an unused UNDEF `__vt__Q23gui9Interface` (code/data bytes same). |
| 9 | `~gui::Interface` always inline | iplGCSaveData.o, iplMemoryCard.o gain a weak 64-byte `~Interface`. |
| 10 | `gui::EventHandler` never novtable | iplGCSaveData.o, iplGCWindow.o, iplMemoryCard.o change, DOL changes. |
| 11 | `gui::EventHandler` always novtable | ~20 objects change. |
| 12 | `ipl::gui::PaneManager` dtor always inline | iplGCSaveData.o, iplMemoryCard.o change, DOL changes. |
| 13 | `MemCardEventListener`: drop its (already unconditional) novtable | iplGCWindow.o changes. Already consistent; left as is. |

## Result

Removed the two dead pieces (3, 4). All 1027 objects and the DOL are unchanged.

Switches that stay, and why:

- `IPL_CHANNEL_TITLE_NOVTABLE` in `iplNand.h`: the channel-title TUs must emit
  weak stub copies of the `LangFile`/`LayoutFile` virtuals, which have real
  out-of-line bodies in iplNand.cpp. No single declaration gives both (1, 2).
  The macro no longer adds any `novtable`; its name is historical.
- `IPL_CHANNEL_TITLE_NOVTABLE` in `iplInterporation.h`: it selects a different
  `HermiteIntp` primary template (FrameController base, out-of-line `init`,
  `HermiteIntp<f32>` specialization, `dont_instantiate`). The same header also
  has `IPL_CHANNEL_SELECT_CPP` / `IPL_SD_CHANNEL_SELECT_CPP` /
  `IPL_SD_CHANNEL_TITLE_CPP` variants, so untangling it is a separate job (5, 6).
- `IPL_GC_SAVEDATA_NOVTABLE` / `IPL_MEMORY_CARD_NOVTABLE` / `IPL_GC_WINDOW_NOVTABLE`
  in `GUIManager.h` and `iplGuiManager.h`: the memory-card TUs need novtable
  `Interface`/`EventHandler` and out-of-line `~Interface`/`~PaneManager`, while
  every other GUI user needs the opposite (7-12).
