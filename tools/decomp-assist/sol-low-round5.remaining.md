# Final matching audit

| Unit | Gate instruction-exact before → after | Objdiff exact before → after | Fuzzy before → after | Matched code bytes before → after | Matched data bytes before → after |
| --- | --- | --- | --- | --- | --- |
| iplSDChannelSelect | 102/129 → 102/129 | 102/129 → 102/129 | 98.0426 → 98.0426 | 24100 → 24100 | 224 → 224 |
| NWC24Download | 17/30 → 18/30 | 17/30 → 18/30 | 97.2494 → 97.2654 | 3640 → 4172 | 80 → 80 |
| iplSetting | 103/112 → 104/112 | 104/112 → 105/112 | 98.6649 → 98.8008 | 30156 → 30532 | 1040 → 1040 |

Source commits: 2f8fcdfe (download task-list creation), 62f8c797 (EULA TMD validation). Final full gate over all three units: GATE PASS; zero regressions, forbidden patterns and readability warnings.

All experiments are restored except NWC24iCreateDlTaskList and validateEULA_. The initial flushSaveDataAndMountSD retained candidate was later restored.

Each remaining objdiff-open function has at least three distinct, compiled source variations in the attempts log. Compile failures are excluded.

## src/scene/sdChannelSelect/iplSDChannelSelect

- create__Q33ipl5scene15SDChannelSelectFv: 94.23972% | instructions 146/146 | 3 distinct compiled attempts | heap capture versus reload around allocation; loop reload remains.
- enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv: 94.117645% | instructions 18/17 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv: 94.44444% | instructions 19/18 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl: 97.51111% | instructions 46/45 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv: 95.652176% | instructions 24/23 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv: 95.652176% | instructions 24/23 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl: 95.652176% | instructions 24/23 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl: 90.86957% | instructions 25/23 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl: 95.652176% | instructions 24/23 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl: 95.13043% | instructions 24/23 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl: 95.652176% | instructions 24/23 | 3 distinct compiled attempts | initialized command argument words emit stores absent from target; preserve defined values.
- handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv: 99.15205% | instructions 170/171 | 3 distinct compiled attempts | 64-bit elapsed-time branch form and loop allocation.
- isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl: 93.07843% | instructions 50/51 | 3 distinct compiled attempts | block/byte arithmetic order and saved registers.
- getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl: 86.82353% | instructions 49/51 | 3 distinct compiled attempts | target reloads title-info pointer between output stores.
- collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.81188% | instructions 101/101 | 3 distinct compiled attempts | count increment allocation and threshold scheduling.
- collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.833336% | instructions 102/102 | 3 distinct compiled attempts | count increment allocation and threshold scheduling.
- collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.29365% | instructions 126/126 | 3 distinct compiled attempts | count/offset registers and threshold scheduling.
- collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 77.944595% | instructions 350/361 | 3 distinct compiled attempts | channel-specific bookkeeping and title-id reload boundaries.
- findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi: 81.77778% | instructions 45/45 | 3 distinct compiled attempts | page/count/result register allocation.
- flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv: 99.65714% | instructions 35/35 | 3 distinct compiled attempts | heap/save-manager load scheduling.
- calcCommon__Q33ipl5scene15SDChannelSelectFv: 99.07407% | instructions 109/108 | 3 distinct compiled attempts | target event-handler call lacks initialized third argument.
- destroy__Q33ipl5scene15SDChannelSelectFv: 95.097565% | instructions 203/205 | 3 distinct compiled attempts | loop-entry shape and zero constant reuse.
- drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv: 94.974846% | instructions 153/159 | 3 distinct compiled attempts | state/flag access and range-test branch form.
- initializeNormalPage__Q33ipl5scene15SDChannelSelectFv: 98.93617% | instructions 95/94 | 3 distinct compiled attempts | target event-handler call lacks initialized third argument.
- selectChannel__Q33ipl5scene15SDChannelSelectFii: 98.305084% | instructions 60/59 | 3 distinct compiled attempts | target event-handler call lacks initialized third argument.
- setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj: 93.48498% | instructions 233/233 | 3 distinct compiled attempts | floating-point operand scheduling and registers.
- onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface: 98.541664% | instructions 144/144 | 3 distinct compiled attempts | event branch layout, register allocation and handler-call boundary.

## libs/RevoEX/src/nwc24/NWC24Download

- NWC24InitDlTask: 98.923615% | instructions 144/144 | 3 distinct compiled attempts | header, zero and title-id register allocation.
- NWC24SetDlInterval: 99.89796% | instructions 147/147 | 3 distinct compiled attempts | final task-id register allocation.
- NWC24IterateDlTask: 95.0% | instructions 78/79 | 3 distinct compiled attempts | loop-entry validation branch and index/count allocation.
- NWC24IterateDlTaskEx: 98.034485% | instructions 145/145 | 3 distinct compiled attempts | selected-id and callback traversal register allocation.
- NWC24UpdateDlTask: 94.17391% | instructions 247/253 | 3 distinct compiled attempts | stack frame, retry loop and access-status helper boundary.
- NWC24AddDlTask: 97.552444% | instructions 146/143 | 3 distinct compiled attempts | next-time helper branch form and result scope.
- NWC24GetDlTask: 99.728264% | instructions 92/92 | 3 distinct compiled attempts | parameter register allocation.
- NWC24PurgeOldestDlTask: 85.829544% | instructions 171/176 | 3 distinct compiled attempts | iterator helper initialization and error branches.
- NWC24ManageDlTaskListForMenu: 96.74342% | instructions 150/152 | 3 distinct compiled attempts | remove helper result and task pointer allocation.
- NWC24ExtendDlTaskList: 99.85401% | instructions 137/137 | 3 distinct compiled attempts | close-result register allocation.
- NWC24iCheckDlHeaderConsistency: 98.77358% | instructions 212/212 | 3 distinct compiled attempts | header/repair/pointer setup scheduling.
- AddTaskInternal: 93.57855% | instructions 397/401 | 3 distinct compiled attempts | retry/update helper boundaries and status registers.

## src/scene/setting/iplSetting

- createBrowser__Q33ipl5scene7SettingFv: 98.8505% | instructions 299/301 | 3 distinct compiled attempts | direct-page switch and page-search lifetime/register allocation.
- draw__Q33ipl5scene7SettingFv: 91.03639% | instructions 598/632 | 3 distinct compiled attempts | render-mode copy boundary, stack slots and floating-point scheduling.
- initKeyboard__Q33ipl5scene7SettingFPCc: 93.30986% | instructions 212/213 | 3 distinct compiled attempts | keyboard global reloads and fully initialized default form values.
- calcKeyboard__Q33ipl5scene7SettingFv: 92.42069% | instructions 289/290 | 4 distinct compiled attempts | text-pointer scopes, mask-loop allocation and form switch shape.
- convertRevIP__Q33ipl5scene7SettingFPUcPCc: 98.15069% | instructions 73/73 | 3 distinct compiled attempts | parser parameter/count/output register allocation.
- scanAP__Q33ipl5scene7SettingFv: 94.5625% | instructions 266/272 | 3 distinct compiled attempts | inline animation predicate materialization and flag-store scheduling.
- setUSBAP__Q33ipl5scene7SettingFv: 98.070175% | instructions 56/57 | 3 distinct compiled attempts | compiler reuses status where target reloads it.

## Measurement limitation

setUpdate_NoUpdateDialog_ is objdiff 100%. The gate decoder reports two differing CR1 branch operands because it includes object position in decoding. Both raw branch words are identical: 4184003c and 4184000c; relocations also agree. Gate instruction-exact count therefore remains one below objdiff exact for iplSetting.
