# opus-sdct: link iplSDChannelTitle

Target .data is 0x6a0 with 0xd8 zero bytes after the SDChannelTitle vtable (deduped weak vtables); built emitted 0x94 (PaneManager, EventHandler, Interface). Text extras are weak and get deduped, so they're fine.

1. Dropped IPL_CHANNEL_TITLE_NOVTABLE entirely: adds HermiteIntp<f>/Interporation<f> weak vtables, data 0x67c, text/sdata2 grow. Rejected (HermiteIntp<f> vtable is global elsewhere; Interporation<f> never exists in the DOL).
2. Kept IPL_CHANNEL_TITLE_NOVTABLE defined across iplSDChannelTitle.h too (same as iplChannelTitle.cpp does), so the inline LangFile/LayoutFile path from iplNand.h is used: adds LayoutFile + LangFile weak vtables (0x40), data 0x69c = target content. 69/69 exact, flip to Matching, DOL SHA1 OK, gate PASS.
