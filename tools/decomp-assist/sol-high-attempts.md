libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 1 reconstruct rename allocation rollback and LFN writes from all assembly blocks | BUILD FAILED: dir.d build/43U/src/libs/RVL_SDK/src/fa/pf_dir.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\fa\pf_dir.c
# -------------------------------------
#     782:     if (PFSTR_StrNCmp((PFDIR_STR*)new_path, ":", 1, 1, 1) == 0 && 
#   Error:                                                         ^
#   (10209) illegal implicit conversion from 'char[2]' to
#   'const signed char *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 1 completed control flow typed cache and literal argument fixes | objdiff 90.192000% | insns 584/625 | positional diffs 614 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 2 inline current directory traversal with typed volume state | objdiff 96.568000% | insns 626/625 | positional diffs 619 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 3 reorder real locals to match target stack lifetimes | objdiff 96.568000% | insns 626/625 | positional diffs 619 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 1 reconstruct all allocation root cluster dot entries and LFN assembly blocks | BUILD FAILED:  -------------------------------------
#     803:                   pf_u8 attributes, pf_u32 start, pf_u32* found); 
#   Error:                                                                 ^
#   (10563) identifier 'PFENT_ITER_FindEntry(...)' redeclared as 'long (struct 
#   PF_ENT_ITER *, struct PF_DIR_ENT *, struct PFDIR_STR *, unsigned char, 
#   unsigned long, unsigned long *)'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 1 complete body with original SDK function declarations | objdiff 92.156586% | insns 550/562 | positional diffs 551 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 2 inline dot directory name stores instead of out of line calls | objdiff 96.887900% | insns 571/562 | positional diffs 559 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 3 explicit sector countdown and separate LFN loop lifetimes | objdiff 96.887900% | insns 571/562 | positional diffs 559 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 1 reconstruct move ancestry checks rollback LFN and dot dot relocation from assembly | objdiff 96.228210% | insns 636/631 | positional diffs 590 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 4 deletion buffer initializer and signed length checks | objdiff 97.376000% | insns 626/625 | positional diffs 614 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 2 use semantic deletion byte buffer and signed unicode length checks | objdiff 96.980980% | insns 636/631 | positional diffs 563 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 3 split open file index from LFN countdown temporary | objdiff 96.973060% | insns 636/631 | positional diffs 563 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rmdir | 1 restore original iterator after empty check and preserve cluster before removal | objdiff 99.975250% | insns 202/202 | positional diffs 5 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rmdir | 2 express free chain error normalization as ternary | objdiff 99.975250% | insns 202/202 | positional diffs 5 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rmdir | 3 explicit free chain success return | objdiff 99.975250% | insns 202/202 | positional diffs 5 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsexec | 1 rebuild direct and searched entry branches from original control flow | objdiff 98.178570% | insns 279/280 | positional diffs 267 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rmdir | 4 order live hint before saved hint to reproduce stack offsets | objdiff 100.000000% | insns 202/202 | positional diffs 0 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsexec | 2 order string locals and express accepted flag branch positively | objdiff 98.142860% | insns 279/280 | positional diffs 267 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsexec | 3 preserve result temporary through final dispatch branch | objdiff 98.142860% | insns 279/280 | positional diffs 267 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 1 increment free candidate before index | objdiff 99.710144% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 2 update candidate in for increment | objdiff 99.681160% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 3 advance candidate by indexed next SDD | objdiff 99.536230% | insns 69/69 | positional diffs 3 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsexec_remove | 1 let empty-check output initialize is_empty | objdiff 100.000000% | insns 176/176 | positional diffs 0 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsexec_remove | 2 reuse entry attribute temporary for both tests | objdiff 100.000000% | insns 176/176 | positional diffs 0 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsexec_remove | 3 narrow empty flag lifetime to directory branch | objdiff 100.000000% | insns 176/176 | positional diffs 0 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsnext | 1 exit scan after a real entry is found | objdiff 100.000000% | insns 193/193 | positional diffs 0 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsnext | 2 express single lookup as guarded search | objdiff 94.948190% | insns 192/193 | positional diffs 164 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsnext | 3 use positive entry result branch | objdiff 100.000000% | insns 193/193 | positional diffs 0 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 4 move index increment to loop update | objdiff 99.710144% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 5 candidate uses next indexed descriptor | objdiff 95.057970% | insns 72/69 | positional diffs 66 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 6 scalar descriptor offset drives lookup | objdiff 88.753624% | insns 62/69 | positional diffs 67 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsexec | 4 put accepted flag paths inside branch and share invalid return at tail | objdiff 98.803570% | insns 279/280 | positional diffs 38 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_fsexec | 5 put dispatch result after invalid flag return and restore pattern order | objdiff 100.000000% | insns 280/280 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 1 reconstruct header validation read failure and repair deletion assembly branches | objdiff 98.490560% | insns 212/212 | positional diffs 4 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | 1 reconstruct id rejection access-time validation reset and preincrement retry check from asm | objdiff 90.992096% | insns 247/253 | positional diffs 250 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 2 signed subtask count and separate task pointer assignment | objdiff 98.773580% | insns 212/212 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 3 separate list header and repair locals to test prologue scheduling | objdiff 98.773580% | insns 212/212 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 1 rederive URL validation before retry and full-list allocation loop with existing-task update | objdiff 93.578550% | insns 397/401 | positional diffs 328 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 2 separate existing task result from free slot branch | objdiff 93.578550% | insns 397/401 | positional diffs 328 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 3 positive free-slot branch with explicit retry label | objdiff 93.578550% | insns 397/401 | positional diffs 328 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | 2 distinct retry-count local retained across disabled branch | objdiff 90.992096% | insns 247/253 | positional diffs 250 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | 3 explicit nested result normalization after access time update | objdiff 90.557310% | insns 246/253 | positional diffs 250 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 1 restore independent cached header reads and next-time validator from assembly | objdiff 97.552444% | insns 146/143 | positional diffs 140 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 2 scope interval and next time at scheduling call | objdiff 97.552444% | insns 146/143 | positional diffs 140 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 3 preserve scheduling helper result in caller | objdiff 97.552444% | insns 146/143 | positional diffs 140 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTaskEx | 1 restore strict selected and best candidate comparisons from assembly | objdiff 90.103450% | insns 143/145 | positional diffs 92 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTaskEx | 2 materialize selected comparison with ternary | objdiff 90.103450% | insns 143/145 | positional diffs 92 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTaskEx | 3 compare updated sort flag for sentinel each pass | objdiff 90.689650% | insns 144/145 | positional diffs 92 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 1 return occupied task slots instead of empty entries | objdiff 81.113920% | insns 74/79 | positional diffs 36 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 2 move slot advance into for loop increment | objdiff 83.962030% | insns 74/79 | positional diffs 52 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 3 inline combined slot validity condition | objdiff 83.772150% | insns 72/79 | positional diffs 48 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | 1 inline original read and ordinary delete validator allowing unassigned ids | objdiff 84.312500% | insns 167/176 | positional diffs 86 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | 2 delay done-to-failed translation until iteration exit | objdiff 83.744316% | insns 168/176 | positional diffs 147 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | 3 scope selected task id at read boundary | objdiff 84.312500% | insns 167/176 | positional diffs 86 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 1 use max-count accessor and original inline read and remove control flow | objdiff 94.335526% | insns 149/152 | positional diffs 124 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 2 hold task pointer across read and deletion | objdiff 93.453950% | insns 151/152 | positional diffs 137 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 3 store removal result before return | objdiff 94.335526% | insns 149/152 | positional diffs 124 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlUrl | 1 factor URL parsing result before setter validation | objdiff 100.000000% | insns 109/109 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlUrl | 2 retain separate parse result local | objdiff 100.000000% | insns 109/109 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlUrl | 3 separate lax check from secure-download URL check | objdiff 100.000000% | insns 109/109 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 1 reuse inline reader at public entry point | objdiff 99.728264% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 2 preserve destination pointer in read phase | objdiff 99.728264% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 3 load task id only after file open | objdiff 99.728264% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlFlags | 1 keep explicit nonlegacy task type cases | objdiff 100.000000% | insns 91/91 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlFlags | 2 use enum temporary for legacy flag switch | objdiff 98.901100% | insns 90/91 | positional diffs 19 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlFlags | 3 separate legacy task flag result from setter | objdiff 98.901100% | insns 90/91 | positional diffs 19 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | 1 materialize content type boolean and reuse original write validator | objdiff 96.541664% | insns 143/144 | positional diffs 103 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | 2 order default task stores around content type comparison | objdiff 96.187500% | insns 143/144 | positional diffs 103 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | 3 express final validation result as sign test | objdiff 96.541664% | insns 143/144 | positional diffs 103 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24DeleteDlTask | 1 rebuild admin exemption and nested remove validation | objdiff 98.047620% | insns 107/105 | positional diffs 52 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24DeleteDlTask | 2 branch admin exemption positively | objdiff 98.000000% | insns 107/105 | positional diffs 96 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24DeleteDlTask | 3 retain ordinary remove result in caller | objdiff 98.047620% | insns 107/105 | positional diffs 52 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 1 shorten scheduled id lifetime after validation | objdiff 99.897960% | insns 147/147 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 2 retain local task pointer only until timestamp division | objdiff 99.897960% | insns 147/147 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 3 move time division into scheduler helper | objdiff 80.680275% | insns 175/147 | positional diffs 58 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 1 give reload result a separate lifetime after extension | objdiff 99.854010% | insns 137/137 | positional diffs 4 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 2 express close-error preference in ternary | objdiff 99.854010% | insns 137/137 | positional diffs 4 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 3 return close failure before reloaded success | objdiff 99.854010% | insns 137/137 | positional diffs 4 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 1 separate initialized header pointer from cached accessor | objdiff 99.624060% | insns 133/133 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 2 narrow initialized header to setup scope | objdiff 99.624060% | insns 133/133 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 3 retain task count as loop bound temporary | objdiff 99.624060% | insns 133/133 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iLoadDlHeader | 1 finish seek and read operation before status check | objdiff 100.000000% | insns 100/100 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iLoadDlHeader | 2 use explicit read-result normalization | objdiff 94.250000% | insns 101/100 | positional diffs 81 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iLoadDlHeader | 3 scoped header read with separate status local | objdiff 100.000000% | insns 100/100 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | updateInput__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFRQ39textinput5input10HKBManager | 1 isolate the real 12-byte hardware KeySet ABI while preserving all existing header guard sides | objdiff 76.839620% | insns 201/212 | positional diffs 201 | regressions 0
src/keyboard/tiCellPhone | updateInput__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFRQ39textinput5input10HKBManager | 2 reconstruct both switch loops with a shared iterator and pane-name release event | BUILD FAILED:                                   ^
#   (10184) return value expected
### mwcceppc.exe Compiler:
#    1073:   bool LayoutByNW4R::updateInput(input::HKBManager& hkbManager) { 
#   Error:                                                                 ^
#   (10333) object 
#   'textinput::keyboard::cellphonetype::LayoutByNW4R::updateInput(textinput::i
#   nput::HKBManager &)' redefined
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

src/keyboard/tiCellPhone | updateInput__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFRQ39textinput5input10HKBManager | 2 reconstruct both switch loops with a shared iterator and pane-name release event | objdiff 99.245285% | insns 211/212 | positional diffs 108 | regressions 0
src/keyboard/tiCellPhone | updateInput__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFRQ39textinput5input10HKBManager | 3 retain wide character return until selected character-pane search | objdiff 100.000000% | insns 212/212 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 1 reconstruct all key cycling prediction numeric-space and confirmation blocks with typed ConfirmInput | objdiff 94.837240% | insns 682/682 | positional diffs 539 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 2 use inline pane lookup and preserve Japanese mode branch before uppercase fallback | objdiff 96.895900% | insns 681/682 | positional diffs 494 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 3 give numeric-pane lookup a reference lifetime instead of retaining pointer | objdiff 96.895900% | insns 681/682 | positional diffs 494 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 1 unroll texture acquisition and restore target final setLanguage dispatch | objdiff 81.465460% | insns 331/333 | positional diffs 303 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 2 perform initialization inside the base pane constructor and delay descriptor lifetime | objdiff 90.981980% | insns 341/333 | positional diffs 320 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 3 retain the allocator result directly through the null path | objdiff 92.228226% | insns 337/333 | positional diffs 315 | regressions 0
src/keyboard/tiCellPhone | onTiEvent__Q49textinput8keyboard13cellphonetype12EventHandlerFPQ39textinput3gui13PaneComponentUlPQ49textinput11nw4rmanager14TiEventHandler5Input | 1 derive event masks, animation dispatch, normal-key search and independent repeat timeout from target blocks | objdiff 100.000000% | insns 284/284 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | onTiEvent__Q49textinput8keyboard13cellphonetype12EventHandlerFPQ39textinput3gui13PaneComponentUlPQ49textinput11nw4rmanager14TiEventHandler5Input | 2 use signed event switch to retain the target comparison tree | objdiff 100.000000% | insns 284/284 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | onTiEvent__Q49textinput8keyboard13cellphonetype12EventHandlerFPQ39textinput3gui13PaneComponentUlPQ49textinput11nw4rmanager14TiEventHandler5Input | 3 leave event structure alignment to its natural padding | objdiff 100.000000% | insns 284/284 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | onActive__Q49textinput8keyboard13cellphonetype4BaseFv | 1 initialize a boolean command value in its owning branch | objdiff 95.825390% | insns 63/63 | positional diffs 6 | regressions 0
src/keyboard/tiCellPhone | onActive__Q49textinput8keyboard13cellphonetype4BaseFv | 2 initialize a one-element boolean array using normal aggregate initialization | objdiff 99.936510% | insns 63/63 | positional diffs 4 | regressions 0
src/keyboard/tiCellPhone | onActive__Q49textinput8keyboard13cellphonetype4BaseFv | 3 initialize a typed active-mode command structure | objdiff 99.936510% | insns 63/63 | positional diffs 4 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype4BaseFQ59textinput8keyboard13cellphonetype4Base9InputMode | 1 initialize a boolean command value in its owning branch | objdiff 96.242860% | insns 70/70 | positional diffs 6 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype4BaseFQ59textinput8keyboard13cellphonetype4Base9InputMode | 2 initialize a one-element boolean array using normal aggregate initialization | objdiff 99.942856% | insns 70/70 | positional diffs 4 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype4BaseFQ59textinput8keyboard13cellphonetype4Base9InputMode | 3 initialize a typed active-mode command structure | objdiff 99.942856% | insns 70/70 | positional diffs 4 | regressions 0
src/keyboard/tiCellPhone | onActive__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 1 initialize a boolean command value in its owning branch | objdiff 96.000000% | insns 65/65 | positional diffs 4 | regressions 0
src/keyboard/tiCellPhone | onActive__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 2 initialize a one-element boolean array using normal aggregate initialization | objdiff 100.000000% | insns 65/65 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | onActive__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 3 initialize a typed active-mode command structure | objdiff 100.000000% | insns 65/65 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | onActive__Q49textinput8keyboard13cellphonetype4BaseFv | 4 scope the inactive command alongside the active command to restore stack lifetimes | objdiff 99.936510% | insns 63/63 | positional diffs 4 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype4BaseFQ59textinput8keyboard13cellphonetype4Base9InputMode | 4 scope the inactive command alongside the active command to restore stack lifetimes | objdiff 99.942856% | insns 70/70 | positional diffs 4 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode | 1 derive signed mode cases and condition order, aggregate active flag and restore virtual pane initialization | objdiff 90.062805% | insns 216/207 | positional diffs 189 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode | 2 use the passed mode as the remapped key-set index | objdiff 90.062805% | insns 216/207 | positional diffs 189 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode | 3 scope and type the inactive command value | objdiff 90.043480% | insns 216/207 | positional diffs 189 | regressions 0
src/keyboard/tiCellPhone | changeSpaceKeyTop__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFPCQ49textinput8keyboard13cellphonetype18PaneNameToCharCode | 1 correct the cell-phone-only space-data declarations to the pointer loads shown by target asm | objdiff 100.000000% | insns 52/52 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | changeSpaceKeyTop__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFPCQ49textinput8keyboard13cellphonetype18PaneNameToCharCode | 2 select the space key label before issuing one SetString call | objdiff 82.884610% | insns 47/52 | positional diffs 21 | regressions 0
src/keyboard/tiCellPhone | changeSpaceKeyTop__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFPCQ49textinput8keyboard13cellphonetype18PaneNameToCharCode | 3 return early for Japanese input before acquiring text pane | objdiff 100.000000% | insns 52/52 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 1 re-derive Chinese and Korean prediction-button dispatch, key-set reload after visibility call and virtual FIFO initialization | objdiff 96.468285% | insns 544/536 | positional diffs 449 | regressions 0
src/keyboard/tiCellPhone | init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 2 use a narrow index for the four toggle panes | objdiff 94.992540% | insns 545/536 | positional diffs 443 | regressions 0
src/keyboard/tiCellPhone | init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 3 retain a typed text box and signed loop index | objdiff 96.468285% | insns 544/536 | positional diffs 449 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFUlPv | 1 give the current control-key descriptor a scoped reference | objdiff 97.850464% | insns 107/107 | positional diffs 9 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFUlPv | 2 use a conventional for loop and break for control-key search | objdiff 96.766360% | insns 107/107 | positional diffs 33 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFUlPv | 3 inline a value-returning control-key lookup | objdiff 100.000000% | insns 107/107 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 1 restore the fourth pane-visibility call missing from the target control flow | objdiff 93.923080% | insns 173/169 | positional diffs 168 | regressions 0
src/keyboard/tiCellPhone | doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 2 compute the shared hidden-state value once before updating panes | objdiff 93.923080% | insns 173/169 | positional diffs 168 | regressions 0
src/keyboard/tiCellPhone | doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 3 return for disabled numeric mode before updating pane visibility | objdiff 93.923080% | insns 173/169 | positional diffs 168 | regressions 0
src/keyboard/tiCellPhone | setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 1 retain typed pane-name pointers for the two sign-window controls | objdiff 71.100000% | insns 72/70 | positional diffs 70 | regressions 0
src/keyboard/tiCellPhone | setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 2 finish the disabled sign-window branch with an early return | objdiff 87.071430% | insns 70/70 | positional diffs 21 | regressions 0
src/keyboard/tiCellPhone | setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 3 select the active regional sign pane before dispatching visibility | objdiff 73.842860% | insns 63/70 | positional diffs 43 | regressions 0
src/keyboard/tiCellPhone | doNumericWithDotMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 1 retain the dot key pane name across numeric-mode dispatch | objdiff 95.000000% | insns 36/35 | positional diffs 14 | regressions 0
src/keyboard/tiCellPhone | doNumericWithDotMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 2 dispatch dot-pane visibility through the layout base pointer | objdiff 87.971430% | insns 39/35 | positional diffs 20 | regressions 0
src/keyboard/tiCellPhone | doNumericWithDotMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 3 bind the numeric-pane descriptor at the point of use | objdiff 95.000000% | insns 36/35 | positional diffs 14 | regressions 0
src/keyboard/tiCellPhone | onActive__Q49textinput8keyboard13cellphonetype4BaseFv | 5 type both activation command payloads as boolean structures to preserve stack order | objdiff 100.000000% | insns 63/63 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype4BaseFQ59textinput8keyboard13cellphonetype4Base9InputMode | 5 type both activation command payloads as boolean structures to preserve stack order | objdiff 100.000000% | insns 70/70 | positional diffs 0 | regressions 0
