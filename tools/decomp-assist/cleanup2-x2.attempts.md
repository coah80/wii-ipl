# cleanup2-x2 attempts

Worktree data-d12, branch agent/w1009/cleanup2-x2, baseline 85d653b0dba14d81de4d9cf125a945d8c6ef57f7.
Scope is src/scene directories beginning a through m, excluding cardSequence.
Read cleanup-common.md, including wave-2 guidance, and ran the full 43U build before edits.
Baseline build and fresh completion check passed. DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d.
Saved the baseline report and all 38 built owned objects under /tmp/cleanup2-x2-*.

Each retained trial must preserve every allocated object section and resolved relocation.
Each rejected trial restores the previous accepted source and rebuilds the exact object.
Commit each changed source file separately, run the final gate over all touched units,
regenerate the live report, and require DECOMPLETE_OK and the original DOL SHA1.

## Prior trials and scope

Reviewed cleanup-c2, cleanup-c3, and cleanup-c4. Do not repeat their plain pragma removals,
carrier flattening, typed Board destruction cursor, ChannelTitle early-return rewrite,
or AddressEdit local-order trials. Their byte changes are already recorded.
The remaining Board, AddressEdit, and ChannelTitle pragmas have compiler notes and remain.
Common error, exit, and cleanup paths remain when idiomatic. The wave-2 targets are
list-iteration comma operators, ChannelSelect block_N dispatch, GCWindow jumps into
switch bodies, Calendar cell dispatch, and local placeholder names with clear meanings.
MemoryCardManager's unk_0x fields are declared in the shared include/iplMemoryCardLib.h,
outside the assigned source directories. Leave those declarations to their owner.

## Trials

- KEEP `src/scene/channelSelect/iplChannelSelect` sortChannelListByPage replace both block_N gotos with else-if: every allocated section and resolved relocation is identical.
- KEEP `src/scene/channelSelect/iplChannelSelect` remove comma operator from FOREACH_CHANNEL_OBJ: every allocated section and resolved relocation is identical.
- KEEP `src/scene/board/iplBoard` destroy remove remaining comma operator without changing the void cursor: every allocated section and resolved relocation is identical.
- KEEP `src/scene/channelEdit/iplChannelEdit` replace list-iteration comma operators with ordinary assignment conditions: every allocated section and resolved relocation is identical.
- KEEP `src/scene/memory/iplMemory` replace list-iteration comma operators with ordinary assignment conditions: every allocated section and resolved relocation is identical.
- KEEP `src/scene/channelEdit/iplNandSDCardManager` replace list-iteration comma operators with ordinary assignment conditions: every allocated section and resolved relocation is identical.
- KEEP `src/scene/channelSelect/iplChannelObj` setBalloonText rename temp1 to widthAdjustment: every allocated section and resolved relocation is identical.
- KEEP `src/scene/memoryCard/iplGCWindow` on_error_message3rd replace both dispatch gotos with if/else-if: every allocated section and resolved relocation is identical.
- REVERT `src/scene/memoryCard/iplGCWindow` onMemEvent keep completion statements within case 0x11 and remove the jump into the switch: changed .rela.data, .rela.text, .text; onMemEvent__Q33ipl5scene8GCWindowFlUc: size 620 -> 612.
- KEEP `src/scene/calendar/iplCalendar` replace list-iteration comma operators with ordinary assignment conditions: every allocated section and resolved relocation is identical.
- KEEP `src/scene/channelEdit/iplChanAppEdit` replace list-iteration comma operators with ordinary assignment conditions: every allocated section and resolved relocation is identical.
- KEEP `src/scene/channelEdit/iplChanAppBox` replace list-iteration comma operators with ordinary assignment conditions: every allocated section and resolved relocation is identical.
- KEEP `src/scene/channelEdit/iplChanAppBase` replace list-iteration comma operators with ordinary assignment conditions: every allocated section and resolved relocation is identical.
- KEEP `src/scene/board/iplUrlProcessor` replace list-iteration comma operators with ordinary assignment conditions: every allocated section and resolved relocation is identical.
- KEEP `src/scene/calendar/iplCalendar` set_textbox_date replace three cell-dispatch gotos with an if/else-if chain: every allocated section and resolved relocation is identical.
- KEEP `src/scene/calendar/iplCalendar` set_textbox_date name month-end, visible-cell, weekday, trailing-day and list indices: every allocated section and resolved relocation is identical.
- KEEP `src/scene/button/iplArrow` draw move the scene assignment out of the condition while preserving short-circuit evaluation: every allocated section and resolved relocation is identical.
- KEEP `src/scene/memoryCard/iplGCWindow` document the retained onMemEvent dispatch branch requirement: every allocated section and resolved relocation is identical.
- New ChannelTitle hypothesis: a single final return with an explicit BOOL result may preserve the shared epilogue, unlike the previously rejected early-return shapes.
- REVERT `src/scene/channelTitle/iplChannelTitle` checkNetSetting replace goto-into-else with a common result and final return: changed .rela.data, .rela.text, .text; checkNetSetting__Q33ipl5scene12ChannelTitleFii: size 176 -> 184.
- REVERT `src/scene/calendar/iplCalendar` set_textbox_date remove the unused language declaration and call: changed .rela.ctors, .rela.data, .rela.text, .text; set_textbox_date__Q33ipl5scene8CalendarFiRCQ33ipl7utility4Date: size 668 -> 664.
- KEEP `src/scene/channelSelect/iplChannelSelect` remove the commented-out symbol-debug pragma: every allocated section and resolved relocation is identical.
- KEEP `src/scene/calendar/iplCalendar` set_textbox_date discard the unused language result while retaining the original query: every allocated section and resolved relocation is identical.

## Source commits

- `e9742b88` `src/scene/channelSelect/iplChannelSelect.cpp`
- `e9aa4e9a` `src/scene/board/iplBoard.cpp`
- `98b05969` `src/scene/channelEdit/iplChannelEdit.cpp`
- `44754e4d` `src/scene/memory/iplMemory.cpp`
- `f4c3eda9` `src/scene/channelEdit/iplNandSDCardManager.cpp`
- `d9239600` `src/scene/channelSelect/iplChannelObj.cpp`
- `b913c312` `src/scene/memoryCard/iplGCWindow.cpp`
- `86a8c35a` `src/scene/calendar/iplCalendar.cpp`
- `36bdd6f0` `src/scene/channelEdit/iplChanAppEdit.cpp`
- `7ccb6917` `src/scene/channelEdit/iplChanAppBox.cpp`
- `ea935bd6` `src/scene/channelEdit/iplChanAppBase.cpp`
- `1a46112d` `src/scene/board/iplUrlProcessor.cpp`
- `a6e54585` `src/scene/button/iplArrow.cpp`

## Retained cleanup

| File | Comma conditions removed | Gotos removed |
| --- | ---: | ---: |
| iplChannelSelect.cpp | 1 | 2 |
| iplBoard.cpp | 1 | 0 |
| iplChannelEdit.cpp | 19 | 0 |
| iplMemory.cpp | 17 | 0 |
| iplNandSDCardManager.cpp | 12 | 0 |
| iplChannelObj.cpp | 0 | 0 |
| iplGCWindow.cpp | 0 | 2 |
| iplCalendar.cpp | 5 | 3 |
| iplChanAppEdit.cpp | 3 | 0 |
| iplChanAppBox.cpp | 1 | 0 |
| iplChanAppBase.cpp | 1 | 0 |
| iplUrlProcessor.cpp | 5 | 0 |
| iplArrow.cpp | 1 | 0 |

Total: 66 comma conditions and 7 decompiler-style gotos removed.
ChannelSelect also drops the obsolete debug-pragma comment and the resolved TODO.
Calendar names its month and visible-cell bounds, weekday, trailing-day count, and list/day indices.
The unused language result is gone. The query call stays because removing it drops one instruction, with a one-line compiler note.
ChannelObj names the balloon width adjustment. GCWindow retains the onMemEvent completion jump, with a one-line compiler note, because structured continuation drops two instructions and changes switch relocations.
The ChannelTitle single-result rewrite adds two instructions, so that source is unchanged. Its existing compiler notes remain.
Board, FocusObject, BoardObject, MailAddressSelect, and GCWindow keep ordinary shared error/exit/cancel paths.
All existing scoped compiler pragmas and the Board metadata aggregate remain with their earlier evidence and notes.

## Final verification

Ran gate.py once at the end with --quick over all 14 touched or tried units, including restored ChannelTitle.
Full build passed; every pool is IDENTICAL; code, data, functions, link measures, and every reported section are 100%.

| Unit | Exact functions before -> after |
| --- | --- |
| src/scene/board/iplBoard | 94/94 -> 94/94 |
| src/scene/board/iplUrlProcessor | 17/17 -> 17/17 |
| src/scene/button/iplArrow | 5/5 -> 5/5 |
| src/scene/calendar/iplCalendar | 42/42 -> 42/42 |
| src/scene/channelEdit/iplChanAppBase | 21/21 -> 21/21 |
| src/scene/channelEdit/iplChanAppBox | 13/13 -> 13/13 |
| src/scene/channelEdit/iplChanAppEdit | 31/31 -> 31/31 |
| src/scene/channelEdit/iplChannelEdit | 65/65 -> 65/65 |
| src/scene/channelEdit/iplNandSDCardManager | 64/64 -> 64/64 |
| src/scene/channelSelect/iplChannelObj | 56/56 -> 56/56 |
| src/scene/channelSelect/iplChannelSelect | 102/102 -> 102/102 |
| src/scene/channelTitle/iplChannelTitle | 95/95 -> 95/95 |
| src/scene/memory/iplMemory | 63/63 -> 63/63 |
| src/scene/memoryCard/iplGCWindow | 48/48 -> 48/48 |

All 716/716 functions in the gated units remain instruction-exact.
Gate result: GATE PASS; 0 regressions, 0 forbidden-pattern additions, 0 readability warnings.
A separate fresh-report comparison against the initial live baseline found 0 regressions across all 1028 units and their exact functions.
Focused ctxdiff checks are diffs 0 with equal instruction counts: channel sorting 79/79, calendar cells 167/167, GC error dispatch 30/30, Arrow drawing 59/59, balloon text 181/181.
Regenerated build/43U/report.json and checked build/43U/ok. Completion checker returned DECOMPLETE_OK.
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
Final source review and git diff --check passed. All 14 units preserve allocated section bytes and resolved relocation targets against their fresh initial objects.
Gate transcript: /tmp/cleanup2-x2-final-gate.log. Focused checks: /tmp/cleanup2-x2-ctxdiff.log.
Every changed source file is committed separately. No push, PR, merge, rebase, delegation, or cross-worktree edit.
