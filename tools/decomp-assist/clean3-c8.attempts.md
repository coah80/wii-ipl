# clean3-c8 cleanup attempts

Worktree `clean3-c8`, branch `agent/w1009/clean3-c8`, initial commit `8a67b68cf`.
Read clean3-head.md, cleanup-common.md, local AGENTS.md, unslop and writing-for-agents.
Initial completion check passed with DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.
Saved all 1028 built objects and the complete report under `/tmp/clean3-c8-baseline*`.
Each trial rebuilds its unit and compares allocated section bytes, size, alignment and resolved relocation targets.
A changed byte or target restores the previous source and rebuilds the exact object.

## Prior evidence and new hypotheses

Read cleanup-c1 through cleanup-c7 and the assigned-file entries in cleanup2-w6, cleanup2-x2, cleanup2-x3, cleanup2-x4, cleanup2-x7, cleanup2-x8 and cleanup2-x11.
Plain IRO removal, receiver/heap locals, declaration-order swaps, straightforward list loops, volatile render-copy removal and ChannelTitle result/early-return rewrites already failed. Do not repeat those alone.
The tiInputForm geometry/helper families were rejected before completion; keep the natural expressions and real member abstractions.
Try narrower scopes, real local references, branch-local buffer lifetimes and alternate structured conditions that preserve the same operations.
Exception's two zero-only fields, System::Arg's zero-only field and APScanThread's undefined virtual slot have no established purpose. Keep their names.
BS2's interrupt-shared declaration volatility and idiomatic common error/cleanup exits keep their existing evidence.
The tiInputForm constant-section pragma and BS2Start's original .init placement serve data/code ownership rather than a function optimizer workaround.

## Trials
- RESTORE `src/system/iplSaveDataManager` remove loop-invariant pragma using a for-loop page scope: .text; hasChannel__Q33ipl8savedata7ManagerCFUxPiPi: 71/71 instructions, 45 differing positions.
- RESTORE `src/system/iplSaveDataManager` remove IRO scope with a referenced output title instead of repeated output indexing: .rela.data, .rela.text, .text; makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl: 122/133 instructions, 86 differing positions.
- RESTORE `src/system/iplSaveDataManager` remove IRO scope with a referenced input title and separate channel fields: .rela.data, .rela.text, .text; doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx: 68/67 instructions, 61 differing positions.
- RESTORE `src/scene/board/iplBoard` remove IRO scope using one search cursor and a direct result: .rela.data, .rela.text, .text; get_log_obj__Q33ipl5scene5BoardFv: 22/26 instructions, 17 differing positions.
- RESTORE `src/scene/board/iplBoard` remove IRO scope with a for-loop cursor and per-iteration next pointer: .text; return_to_freelist_if_diff_date__Q33ipl5scene5BoardFv: 37/37 instructions, 9 differing positions.
- RESTORE `src/scene/board/iplBoard` remove IRO scope by placing the button pointer after a scene-manager reference: .text; stt_wait_child_dst__Q33ipl5scene5BoardFv: 171/171 instructions, 2 differing positions.
- RESTORE `src/scene/channelTitle/iplChannelTitle` remove IRO scope with a BS2 manager reference limited to the initial disk check: .text; calcNormalParentalDialog__Q33ipl5scene12ChannelTitleFv: 128/128 instructions, 5 differing positions.
- RESTORE `src/scene/channelTitle/iplChannelTitle` remove IRO scope with a referenced ticket flag to retain its separate boolean conversion: .rela.data, .rela.text, .text; calcNormalWaitTmd__Q33ipl5scene12ChannelTitleFv: 94/99 instructions, 89 differing positions.
- RESTORE `src/scene/channelTitle/iplChannelTitle` remove IRO scope with a scoped update-manager reference: .text; calcNormalUpdating__Q33ipl5scene12ChannelTitleFv: 45/45 instructions, 12 differing positions.
- RESTORE `src/scene/address/iplAddressEdit` remove IRO scope with a narrow source-text scope around wcsncpy: .text; update_friendinfo__Q33ipl5scene11AddressEditFv: 38/38 instructions, 2 differing positions.
- RESTORE `src/scene/address/iplAddressEdit` remove IRO scope with separate branch-local Wii-number and email buffers: .rela.data, .rela.text, .text; get_friendinfo__Q33ipl5scene11AddressEditFv: 82/84 instructions, 66 differing positions.
- RESTORE `src/scene/sdChannelSelect/iplSDChannelSelect` remove IRO scope with a BS2 manager reference local to the wait loop: .rela.data, .rela.text, .text; create__Q33ipl5scene15SDChannelSelectFv: 148/146 instructions, 35 differing positions.
- RESTORE `src/scene/sdChannelSelect/iplSDChannelSelect` remove IRO scope with a referenced save manager for both flag and flush calls: .rela.data, .rela.text, .text; flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv: 34/35 instructions, 14 differing positions.
- RESTORE `src/scene/sdChannelTitle/iplSDChannelTitle` remove IRO scope with one save-manager reference for cache, page and flush: .rela.text, .text; iplSDChannelTitle_flushSaveBeforeExit: 37/37 instructions, 20 differing positions.
- RESTORE `src/system/iplChannelManager` remove IRO scope with one named channel-entry reference: .rela.data, .rela.text, .text; loadMetaHeaderAsync__Q33ipl7channel7ManagerFii: 159/192 instructions, 153 differing positions.
- RESTORE `src/utility/iplUtility` remove IRO scope using default direction followed by a negative-speed override: .rela.data, .rela.text, .text; set_arw_param__Q33ipl7utility9BScrollerFv: 50/51 instructions, 45 differing positions.
- RESTORE `libs/RVL_SDK/src/kbd/kbd_lib` remove IRO scope by declaring the new modifier union before old state and interrupt token: .text; KBDSetModState: 42/42 instructions, 4 differing positions.
- RESTORE `libs/RVL_SDK/src/kbd/kbd_lib` remove propagation scope with the modifier word declared after lock-count temporaries: .text; kbdProcMod: 256/256 instructions, 4 differing positions.
- RESTORE `libs/RVL_SDK/src/kbd/kbd_lib` remove IRO scope with positive callback guard and separate failure branch: .rela.text, .text; kbd_led_handler: 22/25 instructions, 18 differing positions.
- RESTORE `src/scene/address/iplAddressEdit` remove IRO scope with branch-local friend text and pane declarations: .rela.data, .rela.text, .text; create__Q33ipl5scene11AddressEditFv: 818/820 instructions, 327 differing positions.
- RESTORE `src/scene/sdChannelMemory/iplSDMemory` remove IRO scope using a main-layout reference during its construction block: .rela.data, .rela.text, .text; create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: 1057/1064 instructions, 1001 differing positions.
- RESTORE `src/scene/setting/iplSetting` remove IRO scope with a main-layout reference and explicit per-arm animation state: .rela.data, .rela.text, .text; scanAP__Q33ipl5scene7SettingFv: 260/272 instructions, 238 differing positions.
- RESTORE `src/system/iplSystem` remove dead-assignment pragma with viewport dimensions confined to their render scope: .text; warning_run__Q23ipl6SystemFv: 176/176 instructions, 47 differing positions.
- RESTORE `src/scene/cardSequence/iplCardSequence` remove propagation scope with a positive valid-state guard around command dispatch: .rela.data, .rela.text, .text; cardThreadMain: 300/301 instructions, 255 differing positions.
- RESTORE `src/system/iplSaveDataManager` remove MD5 volatility with a plain byte-array reference and file-byte load before the digest comparison: .text; initManagerTask__Q33ipl8savedata7ManagerFPv: 227/227 instructions, 4 differing positions.
- RESTORE `src/scene/setting/iplSetting` remove render-copy volatility using member-address memcpy for scalar fields: .rela.data, .rela.text, .text; draw__Q33ipl5scene7SettingFv: 638/632 instructions, 80 differing positions.
- KEEP `src/system/iplSystem` replace projection use-site casts with declaration-qualified constants: all allocated sections and resolved relocations identical.
- RESTORE `src/scene/cardSequence/iplCardSequence` handleCardMountResult replace dispatch gotos with nested result conditions: .rela.text, .text; handleCardMountResult: 38/39 instructions, 32 differing positions.
- RESTORE `src/scene/cardSequence/iplCardSequence` probeCard replace dispatch gotos with explicit valid-state command arms: .rela.data, .rela.text, .text; probeCard__Q23ipl10memorycardFv: 167/162 instructions, 137 differing positions.
- The round-2 harness stopped after the successful projection declaration trial because the next cast-reference alternative no longer had casts to replace. No source mutation occurred for that skipped alternative; resumed the remaining control-flow trials separately.
- KEEP `src/system/iplSystem` remove all projection constant volatility after removing casts: all allocated sections and resolved relocations identical.
- KEEP `src/system/iplSaveDataManager` document retained hasChannel loop-invariant setting: all allocated sections and resolved relocations identical.
- RESTORE `src/scene/cardSequence/iplCardSequence` probeCard replace dispatch gotos with a command switch and shared state-update arm: .rela.data, .rela.text, .text; probeCard__Q23ipl10memorycardFv: 163/162 instructions, 138 differing positions.
- RESTORE `src/scene/cardSequence/iplCardSequence` loadCardFileIcons replace animation completion goto with break and full-length guard: .rela.text, .text; loadCardFileIcons: 516/512 instructions, 381 differing positions.
- RESTORE `src/scene/cardSequence/iplCardSequence` handleCardMountResult use early I/O-error return then nested repair and success paths: .rela.text, .text; handleCardMountResult: 42/39 instructions, 33 differing positions.
- KEEP `src/keyboard/tiInputForm` notifyChangeMode remove mode-check goto using a short-circuit input-mode guard: all allocated sections and resolved relocations identical.
- RESTORE `src/utility/iplUtility` layout::set_string remove goto and found flag with a dual-condition parent-type walk: .rela.text, .text; set_string__Q33ipl7utility6layoutFPQ34nw4r3lyt4PanePCw: 43/46 instructions, 30 differing positions.
- KEEP `src/scene/channelSelect/iplChannelSelect` name the Hermite point subtraction result: all allocated sections and resolved relocations identical.
- RESTORE `libs/RVL_SDK/src/kbd/kbd_lib` remove setter IRO scope with a channel-local pointer only during locked modifier updates: .rela.text, .text; KBDSetModState: 42/42 instructions, 7 differing positions; kbdProcMod: 253/256 instructions, 44 differing positions.
- RESTORE `libs/RVL_SDK/src/kbd/kbd_lib` remove modifier propagation scope with a scope around state read, switch and write: .text; kbdProcMod: 256/256 instructions, 4 differing positions.
- Corrected the function selector to distinguish definitions from calls and targeted animationDone in loadCardIconImages rather than its wrapper. These harness errors happened before source writes; no compiler result is claimed for those aborted invocations.
- KEEP `src/keyboard/tiInputForm` remove the stale mode-check goto compiler note after structured guard succeeded: all allocated sections and resolved relocations identical.
- KEEP `src/BS2/BS2Update` replace five successful product-region jumps with switch breaks: all allocated sections and resolved relocations identical.
- KEEP `src/scene/cardSequence/iplCardSequence` runCardMoveOrCopy remove sector-size bypass goto and unused labels using an error guard: all allocated sections and resolved relocations identical.
- RESTORE `src/scene/cardSequence/iplCardSequence` probeCard eliminate the state-update jump while retaining the separate command comparison tail: .rela.data, .rela.text, .text; probeCard__Q23ipl10memorycardFv: 167/162 instructions, 137 differing positions.
- RESTORE `src/scene/channelTitle/iplChannelTitle` checkNetSetting use an inverted network-required guard with a shared successful return: .text; checkNetSetting__Q33ipl5scene12ChannelTitleFii: 44/44 instructions, 5 differing positions.

## Retained result

44 completed compiler trials: 8 kept steps and 36 restored changes. The kept projection declaration qualification was an intermediate step; the final source uses ordinary const declarations and direct reads, with no new volatile qualification.
Tried removal of all 24 owned function optimizer scopes with the source changes recorded above. All changed bytes and remain in place. The earlier no-inline and compatibility-table placement trials already establish those requirements; their existing notes remain.

| File | Result | Source commit |
| --- | --- | --- |
| src/system/iplSystem.cpp | Removed all eight projection use-site volatile casts; retained warning_run's dead-assignment pragma. | 4828afe3b |
| src/system/iplSaveDataManager.cpp | Added the required one-line hasChannel loop-invariant explanation; retained all three optimizer scopes and the MD5 volatile reference after byte-changing trials. | 80d43656e |
| src/keyboard/tiInputForm.cpp | Removed the final goto and label with a short-circuit input-mode guard; removed its stale compiler note. Kept the compatibility table's .data placement. | 50d45d679 |
| src/BS2/BS2Update.c | Replaced five product-region success gotos with switch breaks and removed the unused result label. Kept common error and selection exits. | 57b1d1f6d |
| src/scene/cardSequence/iplCardSequence.cpp | Replaced one sector-size bypass goto with an error guard and removed two labels. Kept common finish/cleanup exits and the propagation pragma. | 9149bbd03 |
| src/scene/channelSelect/iplChannelSelect.cpp | Renamed the Hermite subtraction local temp to difference. | 55a096880 |

Unchanged after restored trials: iplChannelTitle, iplBoard, iplAddressEdit, kbd_lib, iplSDChannelSelect, iplUtility, iplChannelManager, iplSetting, iplSDChannelTitle and iplSDMemory. Their required optimizer settings retain their existing one-line explanations. The render-copy volatile pointers remain because the plain/memcpy alternative changes both size and instruction order.
Other BS2 sources retain original SDK assembly, interrupt-shared volatility and common exits. Exception and APScanThread headers retain names whose meaning is not established by their uses. The clear roles of ChannelSelect::unkBool and EGG heap's unknown inline methods belong to excluded headers, so their declarations and calls remain together without aliases or outside-scope edits.
Net cleanup: eight use-site volatile casts, seven gotos and four labels removed; one local renamed. No optimizer pragma removed, no new workaround introduced, and no configuration or header edits.

## Verification

One final gate with --quick covered all 25 assigned source units, including restored trials and all ten BS2 units. Full 43U build passed. All pools are IDENTICAL; 1329/1329 functions, every section, code, data and linkage are 100%. Gate reports zero regressions, forbidden patterns and readability warnings.
The refreshed report has identical unit measures, section records and exact-name function records to the initial complete report for all 1028 units. All 1028 built objects preserve their allocated section bytes, size, alignment and resolved relocation targets.

| Changed unit | Exact functions before and after | Matched code bytes | Matched data bytes |
| --- | --- | --- | --- |
| iplSystem | 63/63 | 12456/12456 | 2228/2228 |
| iplSaveDataManager | 35/35 | 7172/7172 | 968/968 |
| tiInputForm | 221/221 | 50656/50656 | 3772/3772 |
| BS2Update | 10/10 | 4052/4052 | 10488/10488 |
| iplCardSequence | 30/30 | 9852/9852 | 1496/1496 |
| iplChannelSelect | 102/102 | 25668/25668 | 2336/2336 |

Fresh ctxdiff checks have diffs 0 with equal instruction counts: both projection functions 9/9, hasChannel 71/71, notifyChangeMode 108/108, runCardMoveOrCopy 608/608 and UpdateThread 913/913.
Refreshed build/43U/report.json and checked build/43U/ok. Completion checker returned DECOMPLETE_OK. Assembly inventory passed with 162 ORIGINAL functions and zero placeholders.
DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.
GATE PASS. Gate transcript `/tmp/clean3-c8-final-gate.log`; focused diffs `/tmp/clean3-c8-final-ctxdiff.log`; gated units `/tmp/clean3-c8-gated-units.txt`.
The report assertion initially assumed zero-valued measures were present as keys; treating omitted zero measures as zero confirms all 25 units without a source change.
Source files committed separately. No push, PR, merge, rebase, subagents or edits in another worktree.
