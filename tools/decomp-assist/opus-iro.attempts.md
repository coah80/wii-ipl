# opus-iro attempts

## Part A: function-scoped ppc_iro_level

| unit | function | before | change | after |
|------|----------|--------|--------|-------|
| sdChannelSelect/iplSDChannelSelect | create | 39/146 | `ppc_iro_level 0` around the function | 0/146 |
| sdChannelSelect/iplSDChannelSelect | flushSaveDataAndMountSD | 2/35 | `ppc_iro_level 0` | 0/35 |
| sdChannelTitle/iplSDChannelTitle | iplSDChannelTitle_flushSaveBeforeExit | 6/37 | `ppc_iro_level 0`; dropped the `saveHeap` temporary | 0/37 |
| setting/iplSetting | scanAP | 4/272 | `ppc_iro_level 1` (level 0 not exact per sweep); dropped `animationIndex` temporaries in cases 6/7 | 0/272 |

Other functions in each unit unchanged (per-function diff before/after). Pools identical.

- iplSetting: every function exact; flipped to Matching, full build DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
- iplSDChannelTitle: every .text function exact, but flipping to Matching breaks the DOL (0x40 shift).
  Object .text is 0x4b48 vs target 0x48c0 and .data 0x65c vs 0x6a0, so the unit emits extra code and
  misses data that objdiff's per-symbol view does not show. Left NonMatching.
- iplSDChannelSelect: 4 functions still non-exact; stays NonMatching.

## Part B: asm placeholders under ppc_iro_level

| function | candidate | default (3) | level 0 | level 1 | level 2 |
|----------|-----------|-------------|---------|---------|---------|
| Manager::doUpdateChanInfos | plain `mData.chanInfo[page][index]` form, `n` local | 62/68 | 7/67 | 7/67 | 66/71 |
| Manager::doUpdateChanInfos | swap `!=` operands | - | 7/67 | | |
| Manager::doUpdateChanInfos | inline `titleIds[index + page * 12]`, no `n` | - | 7/67 | | |
| Manager::doUpdateChanInfos | `int n` hoisted to function scope | - | 7/67 | | |
| Manager::doUpdateChanInfos | `ESTitleId* titleId = &titleIds[n]` | - | 7/67 | | |
| Manager::doUpdateChanInfos | `ESTitleId titleId = titleIds[n]` value local | - | 48/67 | | |
| Manager::doUpdateChanInfos | `ESTitleId titleId = ES_TITLE_ID(stored)` before `n` (same shape as makePriorTitleIDList) | - | **0/67** | | |
| Manager::hasChannel | rx30 has-00 (best C) | 14/71 | 29/71 | 29/71 | 29/71 |
| getTitleName | grok-title best C | 4/71 | 82/88 | 82/88 | 56/71 |

doUpdateChanInfos converted to C under `ppc_iro_level 0`; the remaining 7 register diffs came from the order the
stored title and the input title were evaluated. hasChannel and getTitleName have strength-reduced, hoisted
IRO-on codegen in the target (mtctr loop, hoisted name stride), so lowering IRO makes them worse; both stay asm.
