
## drawTransferTitles — setTitleRowColors decode (session cont.)
- Helper signature: `setTitleRowColors(TextBox*, const ut::Color&, const ut::Color&)` — mangle `RCQ34nw4r2ut5Color` proven via orig .text symbol.
- Orig callsite: `Color c; writeFourFlagBytes(&c.r,...); Color a=c; Color b=c; setTitleRowColors(tb,a,b)` — 3 memberwise byte-copies (lbz/stb x4) from the same source.
- DECODE: orig's `ut::Color()` ctor was TRIVIAL in this TU — orig emits no WHITE-init `stw` anywhere in drawTransferTitles and no `__ct__Color` weak def. Gated via `IPL_SDMEMORY_TRIVIAL_COLOR_CTOR` -> `Color() {}`. Produces exact 451-insn instruction stream (structure identical; residual = stack slot numbering + sched + regalloc).
- WALL: weak-emission asymmetry — orig UND-references `__as__Color`/`__dt__PaneManager`/`__ct__PaneManager`/`__dt__Interface`/`__dt__scroller`/`__dt__Scroller`/`__dt__BScroller` (emitted weak in OTHER TUs); ours emits them as weak defs here -> extra .text bytes. Same family as iplGCWindow's weak-dtor backup wall.
- Result: drawTransferTitles 96.99 fuzzy, create 99.13 (1064/1064 reg-home tie). Unit stays NonMatching.
