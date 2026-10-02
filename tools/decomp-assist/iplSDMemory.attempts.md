
## drawTransferTitles — setTitleRowColors decode (session cont.)
- Helper signature: `setTitleRowColors(TextBox*, const ut::Color&, const ut::Color&)` — mangle `RCQ34nw4r2ut5Color` proven via orig .text symbol.
- Orig callsite: `Color c; writeFourFlagBytes(&c.r,...); Color a=c; Color b=c; setTitleRowColors(tb,a,b)` — 3 memberwise byte-copies (lbz/stb x4) from the same source.
- DECODE: orig's `ut::Color()` ctor was TRIVIAL in this TU — orig emits no WHITE-init `stw` anywhere in drawTransferTitles and no `__ct__Color` weak def. Gated via `IPL_SDMEMORY_TRIVIAL_COLOR_CTOR` -> `Color() {}`. Produces exact 451-insn instruction stream (structure identical; residual = stack slot numbering + sched + regalloc).
- WALL: weak-emission asymmetry — orig UND-references `__as__Color`/`__dt__PaneManager`/`__ct__PaneManager`/`__dt__Interface`/`__dt__scroller`/`__dt__Scroller`/`__dt__BScroller` (emitted weak in OTHER TUs); ours emits them as weak defs here -> extra .text bytes. Same family as iplGCWindow's weak-dtor backup wall.
- Result: drawTransferTitles 96.99 fuzzy, create 99.13 (1064/1064 reg-home tie). Unit stays NonMatching.

## Weak-emission asymmetry — decl-only gating (session cont. 2)
- Mechanism: orig's TU sees many gui/nw4r members DECL-ONLY while ours inlines/emits weak defs. Orig .o UND-references: EventHandler{onEvent,setManager,setLatestEventCtrlNo,getLatestEventCtrlNo}, scene::scroller{calc,is_busy,~scroller}, Pane::SetVisible, Pane::SetTranslate, ipl::gui::PaneManager{ctor,~}, Color::operator=(const Color&), iplSDChannelTitle_copyTitleRange.
- Orig emits the 3 handler vtables as unnamed .data objects (4 slots each: onEvent + 3 UND EventHandler slots).
- Gates applied: IPL_SDMEMORY_PANEMANAGER_DECL_ONLY (iplGuiManager.h ctor+~PaneManager), IPL_SDMEMORY_DECL_ONLY_GUI (GUIManager.h EventHandler 4 virtuals + Pane::SetVisible), IPL_SDMEMORY_DECL_ONLY_SCROLLER (iplFocusObject.h ~scroller+calc+is_busy), IPL_SDMEMORY_TRIVIAL_COLOR_CTOR (Color() trivial + operator=(const Color&) decl + ~Color undec'd, ~Rect undec'd).
- DECODE: setTitleLists calls free fn iplSDChannelTitle_copyTitleRange(&dst,&src) x2 — NOT operator= (53/53 insn-equal now).
- Result: extra weak defs 28 -> 4 (__dt__Scroller, __dt__Rect, getPane__PaneComponent, offPoint__Component — all unreferenced emission fossils; the getPane/offPoint CALLSITES are identical virtual dispatches vs orig). .text 21012 vs orig 20920 (+92B fossils).
- create regalloc rotation noise (r30 vs r31 home) after layout shift — count-equal family.

## Decl-only gating cont. — weak-emission fully resolved (session cont. 3)
- All 28 extra weak defs eliminated: additional gates = offPoint/getPane decl-only (GUIManager.h under IPL_SDMEMORY_DECL_ONLY_GUI — the virtual CALLSITES are byte-identical bctrl dispatches vs orig; only the weak DEF emission differed) + scroller ctor teardown (decl-only ~scroller/calc/is_busy kills __dt__Scroller fossil) + ~Rect undec kills __dt__Rect fossil + setTitleLists now calls iplSDChannelTitle_copyTitleRange (kills __as__TitleRange).
- .text now 20836 vs orig 20920 (-84B). .data relocs byte-identical incl. the 3 handler vtables at same offsets with UND slot targets = orig.
- REGRESSION to document: .data shrank 3144 -> 2996 (-148B). Orig's .data has a 148B ALL-ZERO tail after the last vtable (no relocs) — provenance unknown (link slack from split? a zero .data object our reconstruction lacks?). Pre-gate .data was coincidentally filled by the weak-vtable emission region (zero bytes + relocs). matched_data dropped 100 -> 5.98 as a side effect of removing the wrong vtables; .data fuzzy = 97.59.
- create fuzzy 98.07 (reg-homing rotation after layout shift), drawTransferTitles 96.99.

---

## Weak-emission asymmetry — decl-only gating (session cont. 2)
- Mechanism: orig's TU sees many gui/nw4r members DECL-ONLY while ours inlines/emits weak defs. Orig .o UND-references: EventHandler{onEvent,setManager,setLatestEventCtrlNo,getLatestEventCtrlNo}, scene::scroller{calc,is_busy,~scroller}, Pane::SetVisible, Pane::SetTranslate, ipl::gui::PaneManager{ctor,~}, Color::operator=(const Color&), iplSDChannelTitle_copyTitleRange.
- Orig emits the 3 handler vtables as unnamed .data objects (4 slots each: onEvent + 3 UND EventHandler slots).
- Gates applied: IPL_SDMEMORY_PANEMANAGER_DECL_ONLY (iplGuiManager.h ctor+~PaneManager), IPL_SDMEMORY_DECL_ONLY_GUI (GUIManager.h EventHandler 4 virtuals + Pane::SetVisible), IPL_SDMEMORY_DECL_ONLY_SCROLLER (iplFocusObject.h ~scroller+calc+is_busy), IPL_SDMEMORY_TRIVIAL_COLOR_CTOR (Color() trivial + operator=(const Color&) decl + ~Color undec'd, ~Rect undec'd).
- DECODE: setTitleLists calls free fn iplSDChannelTitle_copyTitleRange(&dst,&src) x2 — NOT operator= (53/53 insn-equal now).
- Result: extra weak defs 28 -> 4 (__dt__Scroller, __dt__Rect, getPane__PaneComponent, offPoint__Component — all unreferenced emission fossils; the getPane/offPoint CALLSITES are identical virtual dispatches vs orig). .text 21012 vs orig 20920 (+92B fossils).
- create regalloc rotation noise (r30 vs r31 home) after layout shift — count-equal family.

## Decl-only gating cont. — weak-emission fully resolved (session cont. 3)
- All 28 extra weak defs eliminated: additional gates = offPoint/getPane decl-only (GUIManager.h under IPL_SDMEMORY_DECL_ONLY_GUI — the virtual CALLSITES are byte-identical bctrl dispatches vs orig; only the weak DEF emission differed) + scroller ctor teardown (decl-only ~scroller/calc/is_busy kills __dt__Scroller fossil) + ~Rect undec kills __dt__Rect fossil + setTitleLists now calls iplSDChannelTitle_copyTitleRange (kills __as__TitleRange).
- .text now 20836 vs orig 20920 (-84B). .data relocs byte-identical incl. the 3 handler vtables at same offsets with UND slot targets = orig.
- REGRESSION to document: .data shrank 3144 -> 2996 (-148B). Orig's .data has a 148B ALL-ZERO tail after the last vtable (no relocs) — provenance unknown (link slack from split? a zero .data object our reconstruction lacks?). Pre-gate .data was coincidentally filled by the weak-vtable emission region (zero bytes + relocs). matched_data dropped 100 -> 5.98 as a side effect of removing the wrong vtables; .data fuzzy = 97.59.
- create fuzzy 98.07 (reg-homing rotation after layout shift), drawTransferTitles 96.99.

## Trailing .data zeros (148B) — unrecreateable

Orig `.data` ends at 0xc48; ours at 0xbb4 — ours is a strict byte-identical prefix.
The missing 148B is an all-zero object dtk merged into `lbl_8165683C` (0xac = the
0x18 ControlPaneEventHandler vtable + 148B trailing zeros), emitted AFTER the
three event-handler vtables, unreferenced, no relocs.

Micro-test results (mwcceppc 3.0a5.2): EVERY all-zero decl goes to .bss —
`static u32 a[37] = {0}`, `= {}`, `static char b[148] = ""`, POD struct zero-init,
`__declspec(section ".data")`, `#pragma section ".data"` — all .bss.
So the zeros cannot be a standalone source-level object. Two remaining theories:
(1) pure-pad vtable slots (MCM precedent) — contradicted by `new
ControlPaneEventHandler` compiling in the same TU (abstract can't instantiate);
(2) same wall as MyTiLetterForm's "six trailing target zeros were not recreated
with padding" — an accepted tail artifact.

## Trailing .data zeros SOLVED — deduplicated weak vtables

The 148B all-zero tail = three weak vtables emitted in this TU then deduplicated
at link (dtk extraction shows zeros+no relocs, consistent with the MyTiInputForm
and iplSetting findings in data-d3/data-d4):

  __vt__ipl::gui::PaneManager  0x5c  (bb4..c10)
  __vt__gui::EventHandler      0x18  (c10..c28)
  __vt__gui::Interface         0x20  (c28..c48)

Earlier decl-only gates (IPL_SDMEMORY_DECL_ONLY_GUI /
IPL_SDMEMORY_PANEMANAGER_DECL_ONLY / IPL_SDMEMORY_DECL_ONLY_SCROLLER) suppressed
the weak emission; removing them emits the vtables in the same tail order and
.data becomes byte-identical (3144B, data 100%). Lesson: an orig data region of
zeros with no relocs after vtables = deduplicated weak vtable, NOT an all-zero
object — .bss-promotion analysis was the wrong frame.

## drawTransferTitles: copy-temp decode (451/451 insn-equal)

Orig's callsite copies the built Color into THREE disjoint stack slots per call
(4 lbz + 12 stb) — decoded as `Color(x)` copy-ctor temporaries:
`setTitleRowColors(titleText, Color(c), Color(c))` reproduces all three
materializations (MWCC emits a third dead temp in the arg area). The callee
still calls out-of-line `__as__Color` for its member copies — consistent with
decl-only `operator=(const Color&)` + inlined implicit copy-ctor in this TU.
Direct pass (`setTitleRowColors(t, c, c)`) removes 32 insns; named copies emit
`bl __as__` instead of memberwise bytes — neither matches. Remaining residual:
frame +0x20 slot layout + reg-web coloring (insn-equal tie).

## enqueue*/collect member-call conversion (post-rebase cleanup)
Removed the six `extern "C" bool iplSDChannelSelect_813Dxxxx` address-suffixed
stubs (banned identifier style). All 10 call sites now call real private member
fns via `mpSDChannelSelect->` with `friend class SDMemory` added to
iplSDChannelSelect.h (orig must have granted SDMemory access to the private
enqueue* members). Arg semantics decoded from callee impls: enqueue*Notice
page/index params are the u64 titleId halves (caller passes ((u32*)&entry)[0/1]
for the two-u32-arg callees; the raw u64 for enqueueStateNotice(u64,u32) which
emits pad-r4 + u64 in r5:r6 exactly as orig). The arg1 = this+i*8 pointer for
the 3-u32 callees is reproduced via `(u32)&mTitleIds[i] - offsetof(SDMemory,
mTitleIds)`. All call sites byte-identical after conversion.
