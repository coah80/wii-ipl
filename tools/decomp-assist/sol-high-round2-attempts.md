libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_chdir | data 1 deduplicate the ordinary empty root-path literal with opendir | objdiff 100.000000% | insns 159/159 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 1 give the final header update its own task ID lifetime | objdiff 99.897960% | insns 147/147 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 2 remove the duplicate task-pointer assignment and isolate final task ID | objdiff 99.897960% | insns 147/147 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24SetDlInterval | 3 reuse the real next-time helper for the inlined header update | objdiff 99.727890% | insns 147/147 | positional diffs 8 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 1 give the final header reload result a separate local lifetime | objdiff 99.854010% | insns 137/137 | positional diffs 4 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 2 express final error precedence as a conditional return | objdiff 99.854010% | insns 137/137 | positional diffs 4 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ExtendDlTaskList | 3 return close failure before returning a separately scoped reload result | objdiff 99.854010% | insns 137/137 | positional diffs 4 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 1 retain a named destination pointer for file reads | objdiff 99.728264% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 2 separate the task ID value lifetime from the passed argument | objdiff 99.728264% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24GetDlTask | 3 retain destination and task ID as local inputs to read validation | objdiff 99.728264% | insns 92/92 | positional diffs 5 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 1 scope the entry-initialization index after header creation | objdiff 99.624060% | insns 133/133 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 2 reload the initialized header for its magic-field write | objdiff 97.218050% | insns 134/133 | positional diffs 120 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCreateDlTaskList | 3 use a natural unsigned counter for initializing all entries | objdiff 99.624060% | insns 133/133 | positional diffs 10 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 1 initialize the task pointer after the parameter aliases | objdiff 98.773580% | insns 212/212 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 2 use the passed header and repair flag directly throughout the consistency loop | objdiff 98.773580% | insns 212/212 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24iCheckDlHeaderConsistency | 3 bind a typed view for task fields separately from the file-read pointer | objdiff 98.773580% | insns 212/212 | positional diffs 3 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24DeleteDlTask | 1 keep the owner-validation result test inside the protected-app branch | objdiff 100.000000% | insns 105/105 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24DeleteDlTask | 2 spell out the delete operation and retain its success result | objdiff 98.952380% | insns 104/105 | positional diffs 15 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24DeleteDlTask | 3 use early failure returns through the final delete and ID invalidation | objdiff 100.000000% | insns 105/105 | positional diffs 0 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 1 keep the header-count validation as a direct invalid-header branch | objdiff 94.748250% | insns 142/143 | positional diffs 137 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 2 place the next-time calculation inside the successful-time-query branch | objdiff 96.783220% | insns 145/143 | positional diffs 139 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24AddDlTask | 3 derive the final validation and header timestamp update directly from target blocks | objdiff 95.384610% | insns 146/143 | positional diffs 140 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | 1 derive the explicit true and false content-file branches from target assembly | objdiff 98.923615% | insns 144/144 | positional diffs 31 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | 2 use the common header validator and typed home-path element addresses | objdiff 96.541664% | insns 143/144 | positional diffs 103 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24InitDlTask | 3 reverse the two default interval stores and retain the boolean as a signed result | objdiff 96.541664% | insns 143/144 | positional diffs 102 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 1 retain a task pointer across the read and removal blocks | BUILD FAILED: && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#     918:     NWC24DlTask* taskPointer = &task;
#   Error:     ^^^^^^^^^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 2 spell out final read-validation, delete and invalidation blocks | objdiff 94.335526% | insns 149/152 | positional diffs 124 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 3 scope final deletion result and consolidate failed-read handling | objdiff 92.217100% | insns 148/152 | positional diffs 126 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 1 derive the allocation loop as a while loop ending at task update | objdiff 71.753120% | insns 398/401 | positional diffs 319 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 2 retain the URL pointer across length and prefix checks as target does | objdiff 92.765590% | insns 393/401 | positional diffs 333 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | AddTaskInternal | 3 use one failure-result check after free-slot allocation or purging | objdiff 71.753120% | insns 398/401 | positional diffs 319 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | 1 derive the retry loop with its test before the increment body | objdiff 94.173910% | insns 247/253 | positional diffs 249 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | 2 remove the initial task-ID lifetime while preserving the target retry loop | objdiff 94.173910% | insns 247/253 | positional diffs 249 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24UpdateDlTask | 3 split universal-time and access-time failures before the corrected retry loop | objdiff 93.146250% | insns 245/253 | positional diffs 251 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24ManageDlTaskListForMenu | 4 retain the task pointer with a C89-compatible declaration | objdiff 94.736840% | insns 151/152 | positional diffs 137 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTaskEx | 1 derive separate ascending and descending initial-bound stores | objdiff 93.689650% | insns 147/145 | positional diffs 74 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTaskEx | 2 preload each comparison bound before the direction-dependent comparisons | objdiff 97.931040% | insns 145/145 | positional diffs 19 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTaskEx | 3 order the tie-breaking comparison and found flag as in the target blocks | objdiff 93.793106% | insns 147/145 | positional diffs 72 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | 1 derive the menu-task skipping loop with its iterator call at the test | objdiff 85.829544% | insns 171/176 | positional diffs 166 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | 2 reverse retained read-input lifetimes and spell out the final delete result | objdiff 83.715910% | insns 166/176 | positional diffs 86 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24PurgeOldestDlTask | 3 consolidate final iterator failures and use the selected task ID directly | objdiff 84.880684% | insns 166/176 | positional diffs 158 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 1 derive dynamic loop bounds and per-slot validation results from every target block | BUILD FAILED: /src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#     581: taskId < (work != NULL ? (DlTaskListHeader*)work->dlHead : NULL)->maxTaskCount; taskId++) {
#   Error:                                                                 ^^
#   (10149) not a struct/union/class
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 2 express the re-derived slot scan as a while loop | BUILD FAILED:  build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#     581: taskId < (work != NULL ? (DlTaskListHeader*)work->dlHead : NULL)->maxTaskCount) {
#   Error:                                                                 ^^
#   (10149) not a struct/union/class
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 3 separate the found and missing slot result assignments | BUILD FAILED: /src/libs/RevoEX/src/nwc24/NWC24Download.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nwc24\NWC24Download.c
# ----------------------------------------------
#     581: taskId < (work != NULL ? (DlTaskListHeader*)work->dlHead : NULL)->maxTaskCount; taskId++) {
#   Error:                                                                 ^^
#   (10149) not a struct/union/class
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 1 derive dynamic loop bounds and per-slot validation results from every target block | objdiff 94.620255% | insns 78/79 | positional diffs 51 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 2 express the re-derived slot scan as a while loop | objdiff 94.620255% | insns 78/79 | positional diffs 51 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 3 separate the found and missing slot result assignments | objdiff 94.620255% | insns 78/79 | positional diffs 51 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | data1 ordinary pane literals in first-use order and separate normal/toggle animation tables | objdiff 97.297295% | insns 335/333 | positional diffs 254 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 1 advance the indexed directory before the free-slot pointer | objdiff 99.681160% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 2 put the two directory advances in the for-loop step | objdiff 99.681160% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 3 derive the free candidate from the next indexed directory | objdiff 99.536230% | insns 69/69 | positional diffs 3 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 1 derive separate missing and volume-label branches and the short-name return | objdiff 97.712000% | insns 628/625 | positional diffs 540 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 2 match volume comparison operands and narrow the long-name offset adjustment | objdiff 97.808000% | insns 628/625 | positional diffs 540 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_rename | 3 give the final long-name emission loop its own counter lifetime | objdiff 97.712000% | insns 628/625 | positional diffs 540 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 1 derive the not-found and final-update branches from the target blocks | objdiff 96.640250% | insns 634/631 | positional diffs 490 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 2 use unsigned long-name division and narrow the saved entry adjustment | objdiff 96.148970% | insns 631/631 | positional diffs 482 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_move | 3 retain the stored byte-sized long-name count and advance the file pointer first | objdiff 96.354996% | insns 637/631 | positional diffs 567 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 1 derive unsigned long-name division from the target mulhwu block | objdiff 97.937720% | insns 566/562 | positional diffs 555 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 2 start the sector and long-name-count lifetimes at the allocation blocks | objdiff 97.405690% | insns 565/562 | positional diffs 376 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 3 retain the complete filename length and count through allocation | objdiff 97.076515% | insns 563/562 | positional diffs 396 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 1 assign the control key after the target search and fallback blocks | objdiff 95.718475% | insns 685/682 | positional diffs 671 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 2 express the control lookup with a while loop and selected fallback | objdiff 95.718475% | insns 685/682 | positional diffs 670 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 3 retain the current control record instead of its multiplied index | objdiff 96.230200% | insns 679/682 | positional diffs 662 | regressions 0
src/keyboard/tiCellPhone | init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 1 call the inherited virtual directly without nullable base-pointer conversion | objdiff 98.526120% | insns 536/536 | positional diffs 155 | regressions 0
src/keyboard/tiCellPhone | init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 2 use an unsigned index for the four input-mode panes | objdiff 98.423510% | insns 536/536 | positional diffs 155 | regressions 0
src/keyboard/tiCellPhone | init__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | 3 retain the toggle-pane record through the label update loop | objdiff 98.522385% | insns 536/536 | positional diffs 155 | regressions 0
src/keyboard/tiCellPhone | doNumericWithDotMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 1 give the dot-key visibility value its own local lifetime | objdiff 100.000000% | insns 35/35 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | doNumericWithDotMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 2 store numeric-dot mode before the final visibility dispatch | objdiff 56.057144% | insns 35/35 | positional diffs 11 | regressions 0
src/keyboard/tiCellPhone | doNumericWithDotMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 3 derive the explicit true and false visibility alternatives | objdiff 100.000000% | insns 35/35 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 1 place visibility updates in the enabled branch | objdiff 100.000000% | insns 169/169 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 2 retain the toolbar across its presence check and numeric-mode update | BUILD FAILED: iCellPhone.cpp
# -------------------------------------
#     410:             bool Base::onClose() {}
# Warning:                                   ^
#   (10184) return value expected
### mwcceppc.exe Compiler:
#     888:                     toolbar::ToolBar* toolbar = mpManager->getToolBar();
#   Error:                              ^^^^^^^
#   (10140) undefined identifier 'ToolBar'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

src/keyboard/tiCellPhone | doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 3 retain one visibility value across the numeric-mode pane updates | objdiff 100.000000% | insns 169/169 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 1 test the typed pane allocation before placement construction | objdiff 97.297295% | insns 335/333 | positional diffs 254 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 2 load the record animation key at its target conditional use | objdiff 92.732735% | insns 333/333 | positional diffs 155 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 3 give both animation attachment loops natural unsigned counters | objdiff 89.075070% | insns 331/333 | positional diffs 271 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode | 1 derive the dakuten pane references and direct inherited virtual dispatch | objdiff 100.000000% | insns 207/207 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode | 2 represent the disabled input-mode payload as its boolean field | objdiff 97.777780% | insns 207/207 | positional diffs 49 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode | 3 test the selected mode before its upper-case state | objdiff 98.975845% | insns 207/207 | positional diffs 4 | regressions 0
src/keyboard/tiCellPhone | setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 1 retain the language across sign-window pane decisions | objdiff 100.000000% | insns 70/70 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 2 test the Japanese language value directly | objdiff 100.000000% | insns 70/70 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 3 use the stored sign-window enable state for visibility dispatch | BUILD FAILED: -----------------
#     410:             bool Base::onClose() {}
# Warning:                                   ^
#   (10184) return value expected
### mwcceppc.exe Compiler:
#    1007:                     setVisible("W_othersBT_EU", mbSignWindowButton);
#   Error:                                                 ^^^^^^^^^^^^^^^^^^
#   (10140) undefined identifier 'mbSignWindowButton'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

src/keyboard/tiCellPhone | doNumericMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 4 retain the correctly typed toolbar through its presence check | objdiff 96.976330% | insns 164/169 | positional diffs 133 | regressions 0
src/keyboard/tiCellPhone | setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 4 retain the language in the enabled sign-window branch | objdiff 100.000000% | insns 70/70 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | setSignWindowButton__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFb | 5 reverse the language branch and its ordinary literal uses | objdiff 99.785710% | insns 70/70 | positional diffs 3 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | data2 inherit the command-sender vtable entries under the unit-only guard | objdiff 97.297295% | insns 335/333 | positional diffs 254 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | data3 initialize animation-key fields directly in their ordinary table declarations | objdiff 97.297295% | insns 335/333 | positional diffs 254 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | data4 share the actual input-mode-enabled command payload type | objdiff 97.297295% | insns 335/333 | positional diffs 254 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | data5 define the layout destructor after the pane destructors it owns | objdiff 97.297295% | insns 335/333 | positional diffs 254 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | data6 declare the layout after its event and pane classes under the unit-only guard | objdiff 97.297295% | insns 335/333 | positional diffs 254 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | data7 declare event/pane/layout ownership in the target vtable emission order | objdiff 97.297295% | insns 335/333 | positional diffs 254 | regressions 0
src/keyboard/tiCellPhone | onActive__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFv | data8 reuse the base activation command sequence and its initializer | objdiff 100.000000% | insns 65/65 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | changeInputMode__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFQ59textinput8keyboard13cellphonetype4Base9InputMode | data9 reuse the base input-mode command sequence and its initializer | objdiff 100.000000% | insns 207/207 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | convertToZiCellphoneInput___Q49textinput8keyboard13cellphonetype4BaseFw | data10 derive digit labels from the target jump table: 1-9 then 0 | objdiff 100.000000% | insns 41/41 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFUlPv | data11 derive sign-window control 9 as the target switch default | objdiff 100.000000% | insns 107/107 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | onAnmEvent__Q49textinput8keyboard13cellphonetype16CellPhoneAnmPaneFQ49textinput11nw4rmanager7AnmPane12AnmPaneEvent | data12 derive state-2/state-3 dispatch from the target jump-table relocations | objdiff 100.000000% | insns 149/149 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 4 use the same early-return control-lookup helper as layout onKey | objdiff 97.331375% | insns 680/682 | positional diffs 556 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 5 reload input-mode records at target use sites and use signed mode/count comparisons | objdiff 99.523460% | insns 683/682 | positional diffs 305 | regressions 0
src/keyboard/tiCellPhone | onKey__Q49textinput8keyboard13cellphonetype4BaseFUlPv | 6 treat the convert-space query payload as its callee-written output | objdiff 99.670090% | insns 682/682 | positional diffs 37 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 4 use the natural fixed-size descriptor index as the loop bound | objdiff 99.710144% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 5 count down the remaining descriptors in a while-loop test | objdiff 99.710144% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 6 use unsigned descriptor indices and remaining count | objdiff 99.710144% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_GetSDD | 7 advance the free candidate after the indexed loop body | objdiff 99.681160% | insns 69/69 | positional diffs 2 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 4 separate allocated and long-name sectors and order live cache outputs as target stack slots | objdiff 99.418150% | insns 563/562 | positional diffs 552 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 5 initialize both real allocation counters from their common zero value | objdiff 99.596085% | insns 562/562 | positional diffs 39 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 6 begin the long-name-count lifetime after entry metadata initialization | objdiff 99.400350% | insns 563/562 | positional diffs 385 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 7 separate the sector countdown from the long-name entry countdown | objdiff 99.649470% | insns 562/562 | positional diffs 36 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 8 initialize the long-name counter before its sector-chain pointer | objdiff 99.596085% | insns 562/562 | positional diffs 39 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 9 initialize the long-name count from the allocated-sector initial state | objdiff 99.418150% | insns 563/562 | positional diffs 552 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 4 let placement construction supply the allocation null check once | objdiff 97.897896% | insns 333/333 | positional diffs 18 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 5 load each animation-table field through its real indexed record | objdiff 99.819820% | insns 333/333 | positional diffs 11 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 6 reuse the tested animation-key value when attaching its transform | objdiff 98.618620% | insns 333/333 | positional diffs 16 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 7 initialize the tested animation key before retaining the pane record | objdiff 99.774770% | insns 333/333 | positional diffs 14 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 8 read pane animation keys through their indexed records | objdiff 99.789790% | insns 333/333 | positional diffs 12 | regressions 0
src/keyboard/tiCellPhone | create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator | 9 retain the normal-pane record but index toggle-pane key reloads | objdiff 99.729730% | insns 333/333 | positional diffs 16 | regressions 0
src/keyboard/tiCellPhone | updatePredictLanguage__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFPQ39textinput15CommandReceiver17ChangePredictMode | data13 derive empty JP/USA captions and all subsequent language slots from the target pointer table | objdiff 100.000000% | insns 85/85 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | updatePredictLanguage__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFPQ39textinput15CommandReceiver17ChangePredictMode | data14 give the real empty-caption value an ordinary named character array | objdiff 100.000000% | insns 85/85 | positional diffs 0 | regressions 0
src/keyboard/tiCellPhone | updatePredictLanguage__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFPQ39textinput15CommandReceiver17ChangePredictMode | data15 give the real empty-caption value an ordinary named character array | objdiff 100.000000% | insns 85/85 | positional diffs 0 | regressions 0
libs/RVL_SDK/src/fa/pf_dir | PFDIR_p_mkdir | 10 initialize the allocated sector independently while retaining the count-first declaration order | objdiff 99.649470% | insns 562/562 | positional diffs 36 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 4 retain the typed task-entry header at the target pre-loop block | objdiff 93.544304% | insns 79/79 | positional diffs 20 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 5 derive the prevalidated slot loop as a do-while scan | objdiff 95.000000% | insns 78/79 | positional diffs 50 | regressions 0
libs/RevoEX/src/nwc24/NWC24Download | NWC24IterateDlTask | 6 spell out each nullable header selection before slot validation | objdiff 93.544304% | insns 79/79 | positional diffs 20 | regressions 0
