# cleanup2-x3 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/rx1`, branch `agent/w1009/cleanup2-x3`, baseline `85d653b0`.
Scope: `src/scene/` subdirectories n through z, except `src/scene/setting/AOSS.c`.
Read cleanup-common.md including wave-2 guidance, repository AGENTS.md, unslop and writing-for-agents. Worker prose remains confined to this log and the final report.
Initial full 43U build passed; regenerated report passed DECOMPLETE_OK; DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.

Acceptance: each retained function cleanup preserves every allocated ELF section, resolved relocation and symbol record against this baseline. Local compiler label spelling may change. Final gate covers every edited unit, all sections and functions, zero regressions, complete linkage and the DOL hash.

## Inspection

Largest actual decompiler-control-flow targets: SDChannelSelect has eight comma traversal conditions and three dispatch gotos; ATERM has two emulated parser loops and one timeout jump into a block. AOSSLink has one emulated startup retry loop. USBAP and SceneManager gotos are common exits. Most initial comma grep hits were argument lists.
Prior cleanup-c3 attempts already rejected direct pragma removal, named receiver/heap variants, channel for-loop traversal, and a flattened worker-state guard. Do not repeat those. Try structured dispatch preserving its nested comparisons, and explicit traversal condition assignment. Existing pragma notes explain required register/scheduling behavior. Prior cleanup-c4 already rejected direct scanAP pragma removal and volatile render-copy simplification.
The SDMemory field `unk_0x3C` and two virtual `unk_0x2C` slots have no clear meaning in this scope; preserve their names.

## Trials
- KEEP `src/scene/sdChannelSelect/iplSDChannelSelect` calcNormal replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/sdChannelSelect/iplSDChannelSelect` refreshPageObjects replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/sdChannelSelect/iplSDChannelSelect` destroyUnusedChannelObjects replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/sdChannelSelect/iplSDChannelSelect` refreshChannelList replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/sdChannelSelect/iplSDChannelSelect` refreshAfterSDTitleList replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/sdChannelSelect/iplSDChannelSelect` findChannelObject replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/sdChannelSelect/iplSDChannelSelect` updateDragPageTransition replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/sdChannelSelect/iplSDChannelSelect` updateDragPageTransition replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/sdChannelSelect/iplSDChannelSelect` processWorkerCommands replace three dispatch gotos with state switch: all allocated sections, resolved relocations and symbol records identical to baseline.
- REVERT `src/scene/setting/ATERM` ATERMParsePacket replace jump-entered do loop with structured while: changed .rela.text, .text (19204 -> 19204 bytes; 116 differing bytes).
- REVERT `src/scene/setting/ATERM` ATERMParseAssociationResponse replace jump-entered do loop with structured while: changed .rela.data, .rela.text, .text (19204 -> 19204 bytes; 400 differing bytes).
- REVERT `src/scene/setting/ATERM` ATERMDiscoverAccessPoints replace timeout jump into block with if/else: changed .rela.data, .rela.text, .text, symbols (19204 -> 19212 bytes; 12883 differing bytes).
- KEEP `src/scene/setting/ATERM` ATERMParsePacket use inline next-option reader and ordinary while condition: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/setting/ATERM` ATERMParseAssociationResponse use inline next-option reader and ordinary while condition: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/setting/ATERM` ATERMDiscoverAccessPoints express timeout as short-circuit condition: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/setting/ATERM` ATERMParsePacket remove redundant nested scopes and unreachable return: all allocated sections, resolved relocations and symbol records identical to baseline.
- REVERT `src/scene/setting/AOSSLink` AOSSi_WLANGetBSSList structure startup retries as while and remove unused cleanup label: changed .rela.text, .text (2196 -> 2196 bytes; 30 differing bytes).
- KEEP `src/scene/sdButton/iplSDArrow` SDArrow::draw split short-circuit comma condition into scene lookup and nested if: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/saveDataEdit/iplSaveDataEdit` calc replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/saveDataEdit/iplSaveDataEdit` anmFadein replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/saveDataEdit/iplSaveDataEdit` anmSelectFadein replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/saveDataEdit/iplSaveDataBase` calc replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/saveDataEdit/iplSaveDataBox` calc replace comma traversal with ordinary assignment comparison: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/setting/ATERM` place response reader beside its parser and tidy whitespace: all allocated sections, resolved relocations and symbol records identical to baseline.
- KEEP `src/scene/setting/AOSSLink` AOSSi_WLANGetBSSList use unconditional retry loop with success break: all allocated sections, resolved relocations and symbol records identical to baseline.
- REVERT `src/scene/sdChannelSelect/iplSDChannelSelect` flushSaveDataAndMountSD replace IRO scope with heap-first inline flush helper: changed .text (35264 -> 35264 bytes; 4 differing bytes).
- REVERT `src/scene/sdChannelTitle/iplSDChannelTitle` flushSaveBeforeExit replace IRO scope with heap-first inline flush helper: changed .text (19480 -> 19480 bytes; 8 differing bytes).
- REVERT `src/scene/setting/iplSetting` scanAP replace IRO scope with animation-index-first inline predicate: changed .rela.data, .rela.text, .text, symbols (38696 -> 38696 bytes; 521 differing bytes).

## Retained changes

- SDChannelSelect: replaced worker-state dispatch with a switch, removing three gotos and its obsolete compiler note. Removed all eight remaining comma traversal conditions. Both IRO 0 scopes and drawing no-inline scope stay; prior trials and the new heap-first helper trial change bytes.
- ATERM: replaced two jump-entered parser loops with ordinary while loops calling typed inline option readers. Removed the timeout jump into a block with a short-circuit timeout test. Removed redundant parser scopes and unreachable final return. Nine cleanup/unlock gotos remain as common error exits.
- AOSSLink: replaced the startup back-jump with an unconditional retry loop and success break; removed the unused cleanup label. The two unlock gotos remain as common error exits. The rejected condition-at-head retry loop rotated 11 of 227 instructions; the accepted loop preserves all 227.
- SDArrow: split the comma condition into the draw-layer test, scene lookup statement and null test. Lookup still runs only on the default draw layer.
- SaveDataEdit, SaveDataBase, SaveDataBox: removed five comma traversal conditions, preserving the existing iterator assignments and file style.

The scope now has zero comma conditions and zero decompiler-style gotos. The 15 remaining gotos all target common error/cleanup/return paths. Placeholder fields and virtual slots with unclear meaning stay. Existing GameSpy platform-warning pragmas and non-Wii code stay.
New pragma-removal hypothesis: use meaningful inline helper parameters to make heap/index evaluation explicit, as the successful ATERM readers did. All three trials changed bytes and were reverted. scanAP retains its existing IRO 1 explanation and volatile render-copy note; SDChannelTitle retains its IRO 0 explanation. SDMemory retains the IRO 1 scope and workarounds already proved necessary in cleanup-c3.

The first pool_diff invocation incorrectly passed a unit name; the tool needs two object paths. The corrected run reports identical SDChannelSelect pools. Focused ctxdiff checks passed for processWorkerCommands 326/326, ATERMParsePacket 135/135, ATERMParseAssociationResponse 137/137, ATERMDiscoverAccessPoints 263/263 and AOSSi_WLANGetBSSList 227/227, all diffs 0.

## Final verification

Final gate includes seven changed units and the two units whose pragma trials were restored. The brief explicitly requests --quick after the initial full build. No other full build runs in this worktree. Source commits each contain one assigned file. origin/main advanced during this run; the leaf remains on the assigned baseline and was not rebased.

| Unit | Exact functions before -> after | Code bytes | Data bytes |
| --- | --- | --- | --- |
| src/scene/sdChannelSelect/iplSDChannelSelect | 129/129 -> 129/129 | 33828/33828 | 2960/2960 |
| src/scene/setting/ATERM | 26/26 -> 26/26 | 19204/19204 | 18864/18864 |
| src/scene/setting/AOSSLink | 14/14 -> 14/14 | 2196/2196 | 2432/2432 |
| src/scene/sdButton/iplSDArrow | 3/3 -> 3/3 | 304/304 | 80/80 |
| src/scene/saveDataEdit/iplSaveDataEdit | 28/28 -> 28/28 | 5192/5192 | 1344/1344 |
| src/scene/saveDataEdit/iplSaveDataBase | 20/20 -> 20/20 | 3564/3564 | 1208/1208 |
| src/scene/saveDataEdit/iplSaveDataBox | 10/10 -> 10/10 | 2068/2068 | 400/400 |
| src/scene/sdChannelTitle/iplSDChannelTitle | 69/69 -> 69/69 | 18624/18624 | 1976/1976 |
| src/scene/setting/iplSetting | 112/112 -> 112/112 | 37884/37884 | 5696/5696 |

All 411 verified functions and every section of the nine gated units remain 100%; source objects also retain identical allocated sections, resolved relocations and symbol records against the initial baseline. Fresh comparison of all 1028 units and exact-name functions finds zero regressions. Final report passed DECOMPLETE_OK.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
DECOMPLETE_OK
```

Gate transcript `/tmp/cleanup2-x3-final-gate.log`. Baseline report `/tmp/cleanup2-x3-baseline-report.json`. Every rejected trial was restored. Scope-wide scan found zero comma conditions and only the 15 common-exit gotos listed above. No push, PR, merge, rebase, subagents or edits to other worktrees. AOSS.c and configure.py are unchanged.

Source commits:
- `bddfd073` cleanup: simplify save data box pane traversal condition
- `2aed89f8` cleanup: simplify save data base pane traversal condition
- `2706b126` cleanup: simplify save data edit pane traversal conditions
- `32ff2d23` cleanup: split SD arrow scene lookup condition
- `bc392c65` cleanup: structure wireless startup retry loop
- `46a98112` cleanup: structure ATERM option parsing and timeout checks
- `0d2f1301` cleanup: structure SD worker dispatch and channel traversals
