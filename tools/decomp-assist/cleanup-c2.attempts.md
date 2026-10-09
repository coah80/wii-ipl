# cleanup-c2 attempts

Baseline: f1db6b656e386063a8bc263fb75a299f36ae4803. Full 43U build passed before edits. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Fresh initial report passed DECOMPLETE_OK. All four assigned units are Matching.

Each retained trial must preserve every allocated object section and relocation. Any changed byte or build failure restores the source and rebuilds the initial exact object. Final acceptance also requires the full build, report, completion checker and four-unit gate with zero regressions.

## Trials

- src/system/iplChannelManager: remove iro pragma from Manager::loadMetaHeaderAsync: reverted; changed .rela.text, .text; functions: loadMetaHeaderAsync__Q33ipl7channel7ManagerFii.
- src/system/iplSaveDataManager: remove iro pragma from Manager::makePriorTitleIDList: reverted; changed .rela.text, .text; functions: makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl.
- src/system/iplSaveDataManager: remove iro pragma from Manager::doUpdateChanInfos: reverted; changed .rela.text, .text; functions: doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx.
- src/scene/board/iplBoard: remove iro pragma from Board::stt_wait_child_dst: reverted; changed .rela.text, .text; functions: stt_wait_child_dst__Q33ipl5scene5BoardFv.
- src/scene/board/iplBoard: remove iro pragma from Board::return_to_freelist_if_diff_date: reverted; changed .text; functions: return_to_freelist_if_diff_date__Q33ipl5scene5BoardFv.
- src/scene/board/iplBoard: remove iro pragma from Board::get_log_obj: reverted; changed .text; functions: get_log_obj__Q33ipl5scene5BoardFv.
- src/utility/iplUtility: remove iro pragma from BScroller::set_arw_param: reverted; changed .rela.text, .text; functions: set_arw_param__Q33ipl7utility9BScrollerFv.
- src/utility/iplUtility: remove Scroller constructor dont_inline pragma: reverted; changed .rela.text, .text; functions: __ct__Q33ipl7utility8ScrollerFv, __ct__Q33ipl4math14HermiteIntp<f>Fv.
- src/scene/board/iplBoard: replace RecordReadState with independent metadata and interrupt locals: reverted; changed .rela.text, .text; functions: appendRecord__Q33ipl5scene5BoardFP10_CDBRecord.
- src/scene/board/iplBoard: remove freelist pragma and use a structured while loop: reverted; changed .rela.text, .text; functions: return_to_freelist_if_diff_date__Q33ipl5scene5BoardFv.
- src/scene/board/iplBoard: remove get_log_obj pragma and return the found object directly: reverted; changed .rela.text, .text; functions: get_log_obj__Q33ipl5scene5BoardFv.
- src/scene/board/iplBoard: replace comma expression in object iteration with an assignment condition: reverted; changed .rela.text; functions: .
- src/scene/board/iplBoard: use typed BoardObject pointer when destroying free objects: reverted; changed .rela.text, .text; functions: destroy__Q33ipl5scene5BoardFv.
- src/system/iplChannelManager: rename load-order locals and use MAX_CHANNEL_PAGE: retained; every allocated section and relocation is identical to the initial object.
- src/system/iplSaveDataManager: remove use-site volatile MD5 reference: reverted; changed .rela.text, .text; functions: initManagerTask__Q33ipl8savedata7ManagerFPv.
- src/system/iplSaveDataManager: remove unused mangled helper declarations: retained; every allocated section and relocation is identical to the initial object.
- src/system/iplSaveDataManager: read available channel slot through chanInfo instead of raw offsets: reverted; changed .rela.text, .text; functions: getAvailableInList__Q33ipl8savedata7ManagerFPCUxUl.
- src/utility/iplUtility: replace set_string goto with a structured type-search loop: reverted; changed .rela.text, .text; functions: set_string__Q33ipl7utility6layoutFPQ34nw4r3lyt4PanePCw.
- src/utility/iplUtility: remove unused decimal-conversion byte offset: reverted; changed .rela.text; functions: .
- src/utility/iplUtility: use TPL_MAGIC instead of its literal value: retained; every allocated section and relocation is identical to the initial object.
- src/utility/iplUtility: replace cursor position word copies with vector assignment: reverted; changed .rela.text, .text; functions: get_cursor_pos__Q23ipl7utilityFRCQ33ipl4math4VEC2.
- src/scene/board/iplBoard: replace comma expression in object iteration with an assignment condition after sorting relocations: reverted; changed .rela.text; functions: .
- src/utility/iplUtility: remove unused decimal-conversion byte offset after sorting relocations: reverted; changed .rela.text; functions: .
- src/scene/board/iplBoard: structure freelist iteration while retaining iro pragma: reverted; changed .rela.text; functions: .
- src/scene/board/iplBoard: remove get_log_obj pragma with an explicit counted iteration: reverted; changed .rela.text, .text; functions: get_log_obj__Q33ipl5scene5BoardFv.
- src/scene/board/iplBoard: remove stt_wait_child_dst pragma and shorten channel-title lookup lifetime: reverted; changed .rela.text, .text; functions: stt_wait_child_dst__Q33ipl5scene5BoardFv.
- src/system/iplChannelManager: remove loadMetaHeaderAsync pragma with directly scoped channel-info assignment: reverted; changed .rela.text, .text; functions: loadMetaHeaderAsync__Q33ipl7channel7ManagerFii.
- src/system/iplSaveDataManager: remove makePriorTitleIDList pragma and scope output index to channel: reverted; changed .rela.text, .text; functions: makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl.
- src/system/iplSaveDataManager: remove doUpdateChanInfos pragma and name channel info reference: reverted; changed .rela.text, .text; functions: doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx.
- src/utility/iplUtility: remove set_arw_param pragma and scope arrow-length intermediates: reverted; changed .rela.text, .text; functions: set_arw_param__Q33ipl7utility9BScrollerFv.
- src/utility/iplUtility: remove set_string goto with a break and initialized match flag: reverted; changed .rela.text, .text; functions: set_string__Q33ipl7utility6layoutFPQ34nw4r3lyt4PanePCw.
- src/system/iplSaveDataManager: use channel fields for valid-channel count: reverted; changed .rela.text, .text; functions: getNumValidChannel__Q33ipl8savedata7ManagerCFv.
- src/system/iplSaveDataManager: rename valid-channel count locals to their field meanings: retained; every allocated section and relocation is identical to the initial object.

Relocation comparison correction: initial trials compared anonymous local constant names literally. MWCC renumbers these names when source tokens change. Subsequent trials resolve local relocations to their section and offset, preserve external symbol identity, and still compare every allocated section byte. Earlier relocation-only rejections are retried below.

- src/scene/board/iplBoard: replace comma iteration with assignment condition using resolved local relocations: retained; every allocated section and relocation is identical to the initial object.
- src/utility/iplUtility: remove dead decimal-conversion byte offset using resolved local relocations: retained; every allocated section and relocation is identical to the initial object.
- src/scene/board/iplBoard: replace freelist goto with structured iteration using resolved local relocations: retained; every allocated section and relocation is identical to the initial object.
- src/utility/iplUtility: replace cursor word casts with two field-sized memcpy calls: reverted; changed .rela.text, .text; functions: get_cursor_pos__Q23ipl7utilityFRCQ33ipl4math4VEC2.
- src/utility/iplUtility: replace cursor word casts with a single vector-sized memcpy: reverted; changed .rela.text, .text; functions: get_cursor_pos__Q23ipl7utilityFRCQ33ipl4math4VEC2.
- src/utility/iplUtility: use shared interpolation header instead of local class copies: reverted; changed .data, .rela.data, .rela.text, .text; functions: __dt__Q33ipl4math16Interporation<f>Fv, calc__Q33ipl7utility8ScrollerFv.
- src/system/iplSaveDataManager: remove raw MD5 byte cast while preserving address order: reverted; changed .text; functions: initManagerTask__Q33ipl8savedata7ManagerFPv.
- src/system/iplSaveDataManager: derive variable-length MD5 trailer from the saved data field: reverted; changed .rela.text, .text; functions: initManagerTask__Q33ipl8savedata7ManagerFPv.
- src/system/iplSaveDataManager: remove redundant file-length pointer in MD5 validation: reverted; changed .text; functions: initManagerTask__Q33ipl8savedata7ManagerFPv.
- src/utility/iplUtility: remove arrow pragma and branch directly at pointer setters: reverted; changed .rela.text, .text; functions: set_arw_param__Q33ipl7utility9BScrollerFv.
- src/scene/board/iplBoard: remove log-object pragma with separate cursor and candidate lifetimes: reverted; changed .rela.text, .text; functions: get_log_obj__Q33ipl5scene5BoardFv.
- src/scene/board/iplBoard: remove freelist pragma after replacing goto with structured iteration: reverted; changed .text; functions: return_to_freelist_if_diff_date__Q33ipl5scene5BoardFv.
- src/utility/iplUtility: remove dead cursor-pointer reassignment: retained; every allocated section and relocation is identical to the initial object.
- src/utility/iplUtility: replace cursor word-copy casts with named integer views: retained; every allocated section and relocation is identical to the initial object.
- src/system/iplSaveDataManager: replace MD5 raw address cast with a named byte address: retained; every allocated section and relocation is identical to the initial object.
- src/system/iplSaveDataManager: rename available-list indices and literal channel dimensions: retained; every allocated section and relocation is identical to the initial object.
- src/system/iplSaveDataManager: name flattened channel-info index: retained; every allocated section and relocation is identical to the initial object.
- src/utility/iplUtility: use GX texture and palette enums in TPL validation: retained; every allocated section and relocation is identical to the initial object.
- src/system/iplChannelManager: remove integer address casts from channel metadata pointer additions: reverted; changed .text; functions: cbReadMetaHeader__Q33ipl7channel7ManagerFPv, cbReadTmpMetaHeader__Q33ipl7channel7ManagerFPv.
- src/system/iplSaveDataManager: remove unused register-helper declarations: retained; every allocated section and relocation is identical to the initial object.
- src/system/iplSaveDataManager: use channel-row size in valid-channel count address calculation: retained; every allocated section and relocation is identical to the initial object.
- src/utility/iplUtility: simplify BScroller active-state comparison: retained; every allocated section and relocation is identical to the initial object.
- src/utility/iplUtility: remove ForceCTORWeak placeholder: reverted; changed .rela.text, .text; functions: ForceCTORWeak__3iplFv.
- src/utility/iplUtility: rename byte-conversion loop locals: retained; every allocated section and relocation is identical to the initial object.
- src/scene/board/iplBoard: remove freelist pragma with next-pointer declared before cursor: reverted; changed .text; functions: return_to_freelist_if_diff_date__Q33ipl5scene5BoardFv.
- src/scene/board/iplBoard: remove log-object pragma with cursor declared before result: reverted; changed .text; functions: get_log_obj__Q33ipl5scene5BoardFv.
- src/scene/board/iplBoard: remove unused appendRecord hide_icon label: retained; every allocated section and relocation is identical to the initial object.

## Retained changes and remaining compiler requirements

- iplChannelManager.cpp: named load-order page and distance locals; replaced the page-limit literal with MAX_CHANNEL_PAGE. The IRO pragma and callback address casts remain after compiled removal trials changed bytes. The pragma now has a one-line explanation.
- iplSaveDataManager.cpp: removed seven unused mangled declarations and ten unused register-save declarations. Named channel-count, channel-search and flattened-title indices; used existing channel constants and row/slot sizes. Named the MD5 trailer byte address. Both IRO pragmas, the volatile MD5 reference, its file-length pointer and the original channel views remain because ordinary array/member variants changed bytes. Added one-line compiler explanations at retained workarounds.
- iplBoard.cpp: replaced the freelist goto with a structured while loop, removed its entry label and the unused appendRecord hide_icon label, and replaced comma-expression iteration with an assignment condition. All three IRO pragmas and RecordReadState remain with one-line explanations. Flattening RecordReadState changed appendRecord. Removing the freelist pragma keeps 37 instructions but exchanges r30 and r31 in nine positions; declaring next before the cursor did not fix it.
- iplUtility.cpp: removed the unused decimal-conversion offset and its dead update, removed the initial cursor-pointer assignment, simplified the active-state test, named integer-copy and byte-conversion locals, and replaced TPL/GX literals with existing constants. The IRO/inlining pragmas, local interpolation classes, out-of-line vector constructor, integer-copy order, runtime-type goto and weak factory remain because compiled alternatives changed code or data. Added one-line explanations.

Header-owned Scroller::unk_0x3C was left intact because the assigned scope excludes its declaration in include/utility/iplScroller.h. The pre-existing hasChannel assembly was left intact; earlier source attempts and their register/frame differences are recorded in tools/decomp-assist/da1.attempts.md.

60 completed source trials are recorded above. The alternate MD5 pointer spelling after the successful named-address trial was skipped because that source expression had already been replaced; no compiler result is claimed for it. After final comments, all four objects were rebuilt sequentially and every allocated section plus resolved relocation target still equals the initial exact object. git diff --check passed. Final gate and completion evidence follow below.

Source commit: 5e39d1defe8f5179694b331809bddfbca3069206 (src/system/iplChannelManager.cpp).

Source commit: c5228d90353280107f9abc9a36571715ef4ebcd7 (src/system/iplSaveDataManager.cpp).

Source commit: 589458dc75dc2c94670bbe301e1b3ece870b1daa (src/scene/board/iplBoard.cpp).

Source commit: e5486c1ce5b78fb60bae41e825dc6da3ba2a4bb9 (src/utility/iplUtility.cpp).

## Final verification

Ran gate.py once at the end over all four assigned units with --quick. The initial full build had already run before edits. Final gate output:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/system/iplChannelManager] pool: IDENTICAL
[src/system/iplChannelManager] objdiff: code 12552/12552 data 1080/1080 functions 74/74 fuzzy 100.0000 linked code 12552
[src/system/iplChannelManager] instruction-exact functions: 74/74
[src/system/iplChannelManager]   section .data size 224 match 100.0
[src/system/iplChannelManager]   section .rodata size 816 match 100.0
[src/system/iplChannelManager]   section .sbss size 24 match 100.0
[src/system/iplChannelManager]   section .sdata size 16 match 100.0
[src/system/iplChannelManager]   section .text size 12552 match 100.0
[src/system/iplChannelManager] baseline: code 12552/12552 data 1080 functions 74 fuzzy 100.0000
[src/system/iplSaveDataManager] pool: IDENTICAL
[src/system/iplSaveDataManager] objdiff: code 7172/7172 data 968/968 functions 35/35 fuzzy 100.0000 linked code 7172
[src/system/iplSaveDataManager] instruction-exact functions: 35/35
[src/system/iplSaveDataManager]   section .data size 184 match 100.0
[src/system/iplSaveDataManager]   section .rodata size 768 match 100.0
[src/system/iplSaveDataManager]   section .sdata size 16 match 100.0
[src/system/iplSaveDataManager]   section .text size 7172 match 100.0
[src/system/iplSaveDataManager] baseline: code 7172/7172 data 968 functions 35 fuzzy 100.0000
[src/scene/board/iplBoard] pool: IDENTICAL
[src/scene/board/iplBoard] objdiff: code 20276/20276 data 896/896 functions 94/94 fuzzy 100.0000 linked code 20276
[src/scene/board/iplBoard] instruction-exact functions: 94/94
[src/scene/board/iplBoard]   section .data size 744 match 100.0
[src/scene/board/iplBoard]   section .rodata size 104 match 100.0
[src/scene/board/iplBoard]   section .sdata size 40 match 100.0
[src/scene/board/iplBoard]   section .sdata2 size 8 match 100.0
[src/scene/board/iplBoard]   section .text size 20276 match 100.0
[src/scene/board/iplBoard] baseline: code 20276/20276 data 896 functions 94 fuzzy 100.0000
[src/utility/iplUtility] pool: IDENTICAL
[src/utility/iplUtility] objdiff: code 5932/5932 data 304/304 functions 45/45 fuzzy 100.0000 linked code 5932
[src/utility/iplUtility] instruction-exact functions: 45/45
[src/utility/iplUtility]   section .data size 136 match 100.0
[src/utility/iplUtility]   section .sdata size 80 match 100.0
[src/utility/iplUtility]   section .sdata2 size 88 match 100.0
[src/utility/iplUtility]   section .text size 5932 match 100.0
[src/utility/iplUtility] baseline: code 5932/5932 data 304 functions 45 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 100.00000 -> 100.00000
global fuzzy_match_percent: 99.99989 -> 99.99989
global complete_code_percent: 100.00000 -> 100.00000
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Regenerated build/43U/report.json with ninja; target was already current. The fresh completion checker returned DECOMPLETE_OK. DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d. All four configure.py entries remain Matching.

- main/src/system/iplChannelManager: exact functions 74/74 before and after; code 12552/12552; data 1080/1080; code and data fully linked; every section 100.0.
- main/src/system/iplSaveDataManager: exact functions 35/35 before and after; code 7172/7172; data 968/968; code and data fully linked; every section 100.0.
- main/src/utility/iplUtility: exact functions 45/45 before and after; code 5932/5932; data 304/304; code and data fully linked; every section 100.0.
- main/src/scene/board/iplBoard: exact functions 94/94 before and after; code 20276/20276; data 896/896; code and data fully linked; every section 100.0.

Final source review: scoped to the four assigned files; no new assembly, register keywords, volatile accesses or compiler pragmas. Retained workaround comments are one line each. Forbidden-pattern and readability counts are zero. git diff --check passed. Source files are committed separately; this log is the final independent documentation commit. No push, PR, merge, rebase or edits to another worktree.
