# opus-sdmem attempts: SDMemory::drawTransferTitles

Unit `src/scene/sdChannelMemory/iplSDMemory`, branch `agent/w1009/o-sdmem` from `72e9c8d6`.
Start: 363/451 differing, 447/451 instructions, 97.4102%. combosweep: no setting beats 363.

## Header loops: MSL's C++ `wcsstr` overload

The target's two guarded loops (`cmpwi; beq` / `addic.; ble`, then a preheader with
`li rX, "\n"@sda21`, then `b test`) come from MWCC's `IRO_PullOutInvariantAssignments`
(string `IRO_CopyLoopTestToLoopPreheaderAndBranchToSuccNode` in mwcceppc.exe). The pass
needs a loop-invariant *assignment* inside the loop. A plain `wcsstr(p, L"\n")` has none,
so no loop form, pragma, IRO level or `-O4,p` reproduces it in isolated tests.

Real MSL (`MSL_C/wstring.h`, see RushRE/SonicRushAdventure-Decomp tools/cw/include) declares,
for non-embedded C++, `const wchar_t* wcsstr(const wchar_t*, const wchar_t*)` plus
`inline wchar_t* wcsstr(wchar_t* s1, const wchar_t* s2)` calling the const one. Calling it
with a `wchar_t*` inlines the wrapper; its parameter assignment `s2 = L"\n"` is the
invariant assignment the IRO pass pulls into a guarded preheader. Isolated test reproduces
the target sequence instruction for instruction.

`message::Message::getMessage` already returns `wchar_t*`; the `Manager`/`System` wrappers
now return `wchar_t*` too, so message pointers in this function are non-const and use the
overload. The scoped `ppc_iro_level 1` is removed (it suppresses the pass) and the newline
counter is a plain `while` loop.

Result: 88/451 differing, 451/451 instructions, 99.28603%.

Side effect: `LetterWriter::makeHeaderCaption` passed a call result straight to `wcsstr`;
with the overload the literal is evaluated before the virtual call (100 -> 94%). A named
`caption` local restores the target order (three spellings tested, all exact). Full report
otherwise unchanged vs `72e9c8d6`, DOL SHA1 unchanged.

## Title colors: real NW4R `TextBox::SetTextColor(ut::Color top, ut::Color bottom)`

The two helpers after drawTransferTitles were invented names (`iplSDMemory_813EF6C4/6D8`
before #254). Their bodies and placement fit weak header inlines that this large function
did not inline: `nw4r::ut::Color::Color(int, int, int, int)` (four `stb`) and NW4R's
`TextBox::SetTextColor(ut::Color top, ut::Color bottom)` (by-value colors, two calls to the
weak `Color::operator=`; same inline in hotlandsoftware/wii-news-channel, declared in Petari).
By-value arguments explain the retail stack: the named color sits with the other named
locals, the two argument copies are temporaries in source order, the snapshot comes last.
`textBox.h` now has that overload instead of the `IPL_SDMEMORY_SET_TEXT_COLORS` hack, the
source is `nw4r::ut::Color color(...); titleText->SetTextColor(color, color);`, and
symbols.txt names the two functions `__ct__Q34nw4r2ut5ColorFiiii` and
`SetTextColor__Q34nw4r3lyt7TextBoxFQ34nw4r2ut5ColorQ34nw4r2ut5Color` (both 100%).

The N_Body alpha loop is written in place like the header/footer loops: through the
`setChildrenAlpha` inline its iterator temporaries were allocated after the footer's
(inline expansion runs after parsing), retail has them in source order.
`titleOffset -= visibleRows * rowHeight` fixes the `fmuls` operand order.

Result: 50/451 differing, register-blind identical apart from the renamed call targets,
99.39024%. Pool and .data/.sdata/.sdata2 identical; full report unchanged otherwise; DOL OK.
