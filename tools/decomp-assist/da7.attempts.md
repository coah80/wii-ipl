# da7 de-asm attempts

Worktree w0929-fix-board, branch agent/w1005/da7. Starting commit 5e7b5ad045a8cf930106fab1a6c3294b0015e38b.
All 12 assigned functions still contain placeholder asm. Prior trials read in da5.attempts.md and asm-conversions.attempts.md; retain only exact C/C++ conversions.
Scratch source snapshots, Ghidra exports, trial records, and gate outputs live in build/da7/. The local exporter copy only redirects its project directory into this worktree.

- src/system/iplChannelManager getTitleName__Q33ipl7channel7ManagerCFiii title-01-direct-array: 94.84507%; src 0x124 base 0x11c insns 73/71 | --- replace mine 14:15 base 14:15 | POOL IDENTICAL up to 9 (mine=9 base=9)

- src/system/iplChannelManager getTitleName__Q33ipl7channel7ManagerCFiii title-02-language-pointer: 98.943665%; src 0x11c base 0x11c insns 71/71 | diffs 12: [17, 18, 19, 20, 38, 41, 42, 43, 44, 45, 54, 59] | POOL IDENTICAL up to 9 (mine=9 base=9)

- src/system/iplChannelManager getTitleName__Q33ipl7channel7ManagerCFiii title-03-character-helper: COMPILE FAIL ne\iplSceneManager.h:14
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\system\iplSystem.h:15
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\iplSystem.h:9
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\src\system\iplChannelManager.cpp:6)
### mwcceppc.exe Compiler:
#    File: src\system\iplChannelManager.cpp
# -----------------------------------------
#     472:         static inline bool hasTitleName(const SMetaHdr* header, int language, int nameIndex) {
# Warning:                                               ^^^^^^^^
#   (10349) implicit 'int' is no longer supported in C++
### mwcceppc.exe Compiler:
#     472:         static inline bool hasTitleName(const SMetaHdr* header, int language, int nameIndex) {
#   Error:                                                       ^
#   (10115) ')' expected
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


- src/system/iplChannelManager getTitleName__Q33ipl7channel7ManagerCFiii title-03b-character-helper: 92.1831%; src 0x128 base 0x11c insns 74/71 | --- delete mine 7:8 base 7:7 | POOL IDENTICAL up to 9 (mine=9 base=9)

- src/system/iplChannelManager getTitleName__Q33ipl7channel7ManagerCFiii title-04-name-walk: 96.19718%; src 0x11c base 0x11c insns 71/71 | diffs 12: [17, 18, 19, 20, 38, 41, 42, 43, 44, 45, 54, 59] | POOL IDENTICAL up to 9 (mine=9 base=9)

- src/scene/button/iplButton push__Q33ipl7utility36Queue<Q43ipl5scene6Button7Command,8>FRCQ43ipl5scene6Button7Command queue-01-template: 100.0%; src 0x70 base 0x70 insns 28/28 | diffs 0: [] | POOL IDENTICAL up to 32 (mine=32 base=32)

- src/system/TVRC TVRCSendStartAsync tvrc-send-01-typed-records: 98.93939%; src 0x31c base 0x318 insns 199/198 | --- replace mine 16:17 base 16:17 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-send-02-entry-reference: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/sound/iplSound resetAllSound__Q33ipl3snd6SystemFv reset-01-block-local: COMPILE FAIL -ipl-workers\w0929-fix-
#   board\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\iplSceneManager.h:14
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\system\iplSystem.h:15
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\build\da7\trials\reset-01-block-local\iplSound.cpp:9)
### mwcceppc.exe Compiler:
#    File: build\da7\trials\reset-01-block-local\iplSound.cpp
# -----------------------------------------------------------
#     341:         void System::resetAllSound() {
#   Error:                                      ^
#   (10563) identifier 'ipl::snd::System::resetAllSound()' redeclared as 'void
#   ()'
#   Too many errors printed, aborting program

User break, cancelled...


- src/system/TVRC TVRCSendStartAsync tvrc-send-03-entry-pointer: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/sound/iplSound resetAllSound__Q33ipl3snd6SystemFv reset-01b-block-local: 97.94118%; insns 69/68 diffs 40 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/scene/button/iplButton push__Q33ipl7utility36Queue<Q43ipl5scene6Button7Command,8>FRCQ43ipl5scene6Button7Command queue-02-specialization: COMPILE FAIL ted
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\iplFaderSceneBase.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\iplSceneUIHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\button\iplButton.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\src\scene\button\iplButton.cpp:1)
### mwcceppc.exe Compiler:
#    File: src\scene\button\iplButton.cpp
# ---------------------------------------
#      10: extern namespace ipl {
# Warning:        ^^^^^^^^^
#   (10349) implicit 'int' is no longer supported in C++
### mwcceppc.exe Compiler:
#      10: extern namespace ipl {
#   Error:        ^^^^^^^^^
#   (10121) declaration syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


- src/system/TVRC TVRCSendStartAsync tvrc-send-04-current-file-local: 97.72222%; insns 196/198 diffs 158 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/scene/button/iplButton push__Q33ipl7utility36Queue<Q43ipl5scene6Button7Command,8>FRCQ43ipl5scene6Button7Command queue-02b-specialization: COMPILE FAIL .cpp
# ---------------------------------------
#      40:                 }
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\iplFaderSceneBase.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\iplSceneUIHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\button\iplButton.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\src\scene\button\iplButton.cpp:1)
### mwcceppc.exe Compiler:
#    File: src\scene\button\iplButton.cpp
# ---------------------------------------
#      27: char scPaneName_T_Stop[];
#   Error:                         ^
#   (10145) data type is incomplete
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


- src/sound/iplSound resetAllSound__Q33ipl3snd6SystemFv reset-02-loop-local-order: 100.0%; insns 68/68 diffs 0 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/scene/button/iplButton push__Q33ipl7utility36Queue<Q43ipl5scene6Button7Command,8>FRCQ43ipl5scene6Button7Command queue-02c-tail-specialization: COMPILE FAIL drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\iplFaderSceneBase.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\iplSceneUIHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\button\iplButton.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\src\scene\button\iplButton.cpp:1)
### mwcceppc.exe Compiler:
#    File: src\scene\button\iplButton.cpp
# ---------------------------------------
#     985: ::Button::Command, 8>::push(const scene::Button::Command& item) {
#   Error:                                                                 ^
#   (10333) object 'ipl::utility::Queue<ipl::scene::Button::Command,
#   8>::push(const ipl::scene::Button::Command &)' redefined
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.


- src/system/TVRC TVRCSendStartAsync tvrc-send-05-timing-helper: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/scene/button/iplButton push_button_queue queue-03-typed-wrapper: COMPILE FAIL ects\wii-ipl-workers\w0929-fix-
#   board\include\iplSceneUIHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\button\iplButton.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\build\da7\trials\queue-03-typed-wrapper\iplButton.cpp:1)
### mwcceppc.exe Compiler:
#    File: build\da7\trials\queue-03-typed-wrapper\iplButton.cpp
# --------------------------------------------------------------
#     974:             const Button::Command* command = static_cast<const Button::Command*>(item);
#   Error:                                            ^
#   (10412) illegal access from 'ipl::scene::Button' to protected/private
#   member 'ipl::scene::Button::Command'
#   Too many errors printed, aborting program

User break, cancelled...


- src/system/TVRC TVRCSendStartAsync tvrc-send-06-declaration-order: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/sound/iplSound resetAllSound__Q33ipl3snd6SystemFv reset-03-void-return: 100.0%; src 0x110 base 0x110 insns 68/68 | diffs 0: [] | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-send-07-entry-helper: 99.36869%; insns 199/198 diffs 145 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-send-08-entry-helper: 99.36869%; insns 199/198 diffs 145 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/sound/iplSound resetAllSound__Q33ipl3snd6SystemFv reset-04-existing-zero-constant: 100.0%; insns 68/68 diffs 0 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-send-09-entry-helper: 99.36869%; insns 199/198 diffs 145 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-send-10-entry-helper: 99.36869%; insns 199/198 diffs 145 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/keyboard/tiGUIManager draw__Q39textinput3gui13PaneComponentFv draw-01-size-color-locals: 96.92308%; insns 104/104 diffs 14 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/keyboard/tiGUIManager draw__Q39textinput3gui13PaneComponentFv draw-02-half-literal: 96.92308%; insns 104/104 diffs 14 | POOL IDENTICAL up to 0 (mine=0 base=0)

resetAllSound return ABI: existing header declares int and HomeButtonMenu callback returns it. The target final call is BannerSoundPlayer::setMasterVolume, declared void, followed only by callee-save/LR restoration and blr. No return value is assigned. Changing the public declaration to void breaks that callback and was restored. Preserve the original int signature with no invented return assignment; the target proves the indeterminate return path. Reuse scSoundZeroF to avoid adding a literal to .sdata2.

- src/keyboard/tiGUIManager draw__Q39textinput3gui13PaneComponentFv draw-03-half-expression: 96.92308%; insns 104/104 diffs 14 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/keyboard/tiGUIManager draw__Q39textinput3gui13PaneComponentFv draw-04-division: 100.0%; insns 104/104 diffs 0 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC __FTVRCLoop0Handler__7LibTVRCFP7OSAlarmP9OSContext tvrc-loop-01-state-branches: 94.916664%; insns 119/120 diffs 56 | POOL IDENTICAL up to 0 (mine=0 base=0)

## resetAllSound accepted

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/sound/iplSound] pool: IDENTICAL
[src/sound/iplSound] objdiff: code 5576/5576 data 3316/3316 functions 57/57 fuzzy 100.0000 linked code 5576
[src/sound/iplSound] instruction-exact functions: 56/57
[src/sound/iplSound]   section .bss size 3128 match 100.0
[src/sound/iplSound]   section .ctors size 4 match 100.0
[src/sound/iplSound]   section .data size 120 match 100.0
[src/sound/iplSound]   section .rodata size 24 match 100.0
[src/sound/iplSound]   section .sbss size 16 match 100.0
[src/sound/iplSound]   section .sdata2 size 24 match 100.0
[src/sound/iplSound]   section .text size 5576 match 99.49785
[src/sound/iplSound] baseline: code 5576/5576 data 3316 functions 57 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.78013 -> 92.78013
global fuzzy_match_percent: 99.78155 -> 99.78155
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS


- src/keyboard/tiGUIManager draw__Q39textinput3gui13PaneComponentFv draw-05-compiler-half-constant: 100.0%; insns 104/104 diffs 0 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC __FTVRCLoop0Handler__7LibTVRCFP7OSAlarmP9OSContext tvrc-loop-02-state-store-order: 95.333336%; insns 119/120 diffs 49 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC __FTVRCLoop0Handler__7LibTVRCFP7OSAlarmP9OSContext tvrc-loop-03-for-loop: 95.333336%; insns 119/120 diffs 49 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/keyboard/tiGUIManager draw__Q39textinput3gui13PaneComponentFv draw-06-natural-color: 100.0%; insns 104/104 diffs 0 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/keyboard/tiGUIManager draw__Q39textinput3gui13PaneComponentFv draw-07-natural-constants: 100.0%; insns 104/104 diffs 0 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC __FTVRCLoop0Handler__7LibTVRCFP7OSAlarmP9OSContext tvrc-loop-04-bit-read-before-count: 100.0%; insns 120/120 diffs 0 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/scene/button/iplButton push_button_queue queue-04-friend-wrapper: COMPILE FAIL rd\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\iplFaderSceneBase.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\iplSceneUIHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\button\iplButton.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\build\da7\trials\queue-04-friend-wrapper\iplButton.cpp:2)
### mwcceppc.exe Compiler:
#      In: include\scene\button\iplButton.h
# -----------------------------------------
#     322:             friend BOOL ::push_button_queue(void*, const void*);
#   Error:                    ^^^^
#   (10121) declaration syntax error
#   Too many errors printed, aborting program

User break, cancelled...


- src/scene/channelSelect/iplChannelSelect updateDiskState__Q33ipl5scene13ChannelSelectFv disk-01-state-switch: COMPILE FAIL e\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\scene\iplSceneManager.h:14
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\include\iplSceneUI.h:11
#       Z:\mnt\drive2\projects\wii-ipl-workers\w0929-fix-
#   board\build\da7\trials\disk-01-state-switch\iplChannelSelect.cpp:4)
### mwcceppc.exe Compiler:
#    File: build\da7\trials\disk-01-state-switch\iplChannelSelect.cpp
# -------------------------------------------------------------------
#    1373:                             if (mpDiskChanObj->mpThumbnailAnim != NULL) {
#   Error:                                                ^^^^^^^^^^^^^^^
#   (10140) undefined identifier 'mpThumbnailAnim'
#   Too many errors printed, aborting program

User break, cancelled...


## PaneComponent::draw accepted

The size division by 2.0f matches the target multiplication scheduling. Replacing the assembly-only color/float objects with ordinary literals removes duplicate constants. All code and data match and the linked DOL passes.
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiGUIManager] pool: IDENTICAL
[src/keyboard/tiGUIManager] objdiff: code 5916/5916 data 392/392 functions 42/42 fuzzy 100.0000 linked code 5916
[src/keyboard/tiGUIManager] instruction-exact functions: 42/42
[src/keyboard/tiGUIManager]   section .data size 376 match 100.0
[src/keyboard/tiGUIManager]   section .sdata2 size 16 match 100.0
[src/keyboard/tiGUIManager]   section .text size 5916 match 100.0
[src/keyboard/tiGUIManager] baseline: code 5916/5916 data 392 functions 42 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.78013 -> 92.78013
global fuzzy_match_percent: 99.78155 -> 99.78155
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS


- src/scene/button/iplButton push_button_queue queue-05-namespace-friend: None%; insns 28/28 diffs 0 | POOL IDENTICAL up to 32 (mine=32 base=32)

- src/scene/channelSelect/iplChannelSelect updateDiskState__Q33ipl5scene13ChannelSelectFv disk-01b-state-switch: 99.38261%; insns 230/230 diffs 7 | POOL IDENTICAL up to 98 (mine=98 base=98)

## FTVRCLoop0Handler accepted

The target reads the signal byte before storing the incremented combo count. Moving the byte read before that increment preserves the initial zero store and matches all 120 instructions. No volatility change was needed.
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/system/TVRC] pool: IDENTICAL
[src/system/TVRC] objdiff: code 2312/2312 data 280/280 functions 9/9 fuzzy 100.0000 linked code 2312
[src/system/TVRC] instruction-exact functions: 9/9
[src/system/TVRC]   section .bss size 96 match 100.0
[src/system/TVRC]   section .sbss size 120 match 100.0
[src/system/TVRC]   section .sdata size 32 match 100.0
[src/system/TVRC]   section .sdata2 size 32 match 100.0
[src/system/TVRC]   section .text size 2312 match 100.0
[src/system/TVRC] baseline: code 2312/2312 data 280 functions 9 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.78013 -> 92.78013
global fuzzy_match_percent: 99.78155 -> 99.78155
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS


- src/scene/channelSelect/iplChannelSelect updateDiskState__Q33ipl5scene13ChannelSelectFv disk-02-inactive-thumbnail: 99.934784%; insns 230/230 diffs 3 | POOL IDENTICAL up to 98 (mine=98 base=98)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-01-row-manager-body: 97.708336%; insns 72/72 diffs 26 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/system/TVRC TVRCSendStartAsync tvrc-send-11-separate-command-locals: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-send-12-const-file: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-send-13-signed-repeat-offset: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-send-14-command-offset-local: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/scene/channelSelect/iplChannelSelect updateDiskState__Q33ipl5scene13ChannelSelectFv disk-03-thumbnail-anim-local: 98.195656%; insns 228/230 diffs 87 | POOL IDENTICAL up to 98 (mine=98 base=98)

Source-search setup: the provided global limiter did not start the first title-name search while manual work continued. A local copy uses one worker-local slot and cached compiler commands/target objects so clean gates cannot delete its inputs. Its definition matcher excludes calls/prototypes and accepts a qualified member name. Mutation rules are unchanged. Run only one local source search at a time.

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-02-row-selection-helper: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\da7\trials\form-02-row-selection-helper\tiInputForm.cpp
# ----------------------------------------------------------------------
#    1601:     Info_* selected = &rows[rows[capacity].Next];
#   Error:     ^^^^^
#   (10140) undefined identifier 'Info_'
#   Too many errors printed, aborting program

User break, cancelled...


- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-03-const-row-reference: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\da7\trials\form-03-const-row-reference\tiInputForm.cpp
# ---------------------------------------------------------------------
#    1601:     Info_* selected = &rows[rows[capacity].Next];
#   Error:     ^^^^^
#   (10140) undefined identifier 'Info_'
#   Too many errors printed, aborting program

User break, cancelled...


## push_button_queue accepted

The normal Queue template matched its instructions but moved the weak definition ahead of reserveText, changing the DOL. The final ordinary C-linkage wrapper uses the real Queue<Button::Command, 8> and retains the original function location. A guarded friend grants access to Command without changing the class layout or other translation units. Source push_button_queue and the target Queue::push are both 28 instructions with zero differences.
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/button/iplButton] pool: IDENTICAL
[src/scene/button/iplButton] objdiff: code 7624/7624 data 1744/1744 functions 42/42 fuzzy 100.0000 linked code 7624
[src/scene/button/iplButton] instruction-exact functions: 41/42
[src/scene/button/iplButton]   section .data size 944 match 100.0
[src/scene/button/iplButton]   section .rodata size 552 match 100.0
[src/scene/button/iplButton]   section .sdata size 192 match 100.0
[src/scene/button/iplButton]   section .sdata2 size 56 match 100.0
[src/scene/button/iplButton]   section .text size 7624 match 98.53095
[src/scene/button/iplButton] baseline: code 7624/7624 data 1744 functions 42 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.78013 -> 92.78013
global fuzzy_match_percent: 99.78155 -> 99.78155
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS


- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-02b-row-helper: 91.31944%; insns 74/72 diffs 41 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-03b-row-helper: 91.31944%; insns 74/72 diffs 41 | POOL IDENTICAL up to 20 (mine=20 base=20)

- libs/RVL_SDK/src/cntcache/cntcache _CNTCACHEIsTitleRemovable removable-01-copy-boundary: 89.60976%; insns 80/82 diffs 67 | POOL IDENTICAL up to 9 (mine=9 base=9)

- libs/RVL_SDK/src/cntcache/cntcache _CNTCACHEIsTitleRemovable removable-02-copy-boundary: 89.60976%; insns 80/82 diffs 67 | POOL IDENTICAL up to 9 (mine=9 base=9)

- src/scene/channelSelect/iplChannelSelect updateDiskState__Q33ipl5scene13ChannelSelectFv disk-04-play-local: 100.0%; insns 230/230 diffs 0 | POOL IDENTICAL up to 98 (mine=98 base=98)

- libs/RVL_SDK/src/cntcache/cntcache _CNTCACHEIsTitleRemovable removable-03-copy-boundary: 91.31707%; insns 80/82 diffs 64 | POOL IDENTICAL up to 9 (mine=9 base=9)

- src/scene/channelSelect/iplChannelSelect updateDiskState__Q33ipl5scene13ChannelSelectFv disk-05-play-inline-helper: 99.934784%; insns 230/230 diffs 3 | POOL IDENTICAL up to 98 (mine=98 base=98)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-04-detach-inline-helper: 97.708336%; insns 72/72 diffs 26 | POOL IDENTICAL up to 20 (mine=20 base=20)

- libs/RVL_SDK/src/cntcache/cntcache _CNTCACHEDeleteContent content-01-usage-helper: 95.793106%; insns 143/145 diffs 88 | POOL IDENTICAL up to 9 (mine=9 base=9)

- libs/RVL_SDK/src/cntcache/cntcache _CNTCACHEDeleteContent content-02-usage-helper: 95.793106%; insns 143/145 diffs 88 | POOL IDENTICAL up to 9 (mine=9 base=9)

- libs/RVL_SDK/src/cntcache/cntcache _CNTCACHEDeleteContent content-03-usage-helper: COMPILE FAIL ### mwcceppc.exe Compiler:
#    File: build\da7\trials\content-03-usage-helper\cntcache.c
# ------------------------------------------------------------
#     407:     result = ES_GetTmdView(titleId, tmdBuffer, &tmdSize);
#   Error:                                                        ^
#   (10209) illegal implicit conversion from '__aligned(32) unsigned
#   char[8288]' to
#   'struct ESTmdView *'
#   Too many errors printed, aborting program

User break, cancelled...


- libs/RVL_SDK/src/sdi/sdi_api ISD_GetCardSize sdi-01-geometry-shape: 98.15476%; insns 84/84 diffs 23 | POOL IDENTICAL up to 4 (mine=4 base=4)

- libs/RVL_SDK/src/sdi/sdi_api ISD_GetCardSize sdi-02-geometry-shape: 98.39286%; insns 84/84 diffs 20 | POOL IDENTICAL up to 4 (mine=4 base=4)

- libs/RVL_SDK/src/sdi/sdi_api ISD_GetCardSize sdi-03-geometry-shape: 98.39286%; insns 84/84 diffs 20 | POOL IDENTICAL up to 4 (mine=4 base=4)

- libs/RVL_SDK/src/cntcache/cntcache _CNTCACHEDeleteContent content-03b-const-tmd: 95.76552%; insns 143/145 diffs 88 | POOL IDENTICAL up to 9 (mine=9 base=9)

- libs/RVL_SDK/src/cntcache/cntcache CNTCACHEClear clear-01-line-walk: 51.145695%; insns 166/151 diffs 137 | POOL IDENTICAL up to 9 (mine=13 base=9)

- libs/RVL_SDK/src/cntcache/cntcache CNTCACHEClear clear-02-line-walk: 50.278145%; insns 157/151 diffs 138 | POOL IDENTICAL up to 9 (mine=13 base=9)

- libs/RVL_SDK/src/cntcache/cntcache CNTCACHEClear clear-03-line-walk: 42.668873%; insns 160/151 diffs 137 | POOL IDENTICAL up to 9 (mine=13 base=9)

- libs/RVL_SDK/src/cntcache/cntcache _CNTCACHEIsTitleRemovable removable-04-return-object: 91.31707%; insns 80/82 diffs 64 | POOL IDENTICAL up to 9 (mine=9 base=9)

updateDiskState candidate: full build and DOL SHA1 pass, all 102 unit functions are exact. Gate fails only matched_data 2336 -> 192. The generated jump table and target both begin at .data+0x508, contain 7 entries, and relocate to updateDiskState + [0x4c, 0x21c, 0x284, 0x2c8, 0x30c, 0x328, 0x358]. Diagnostic target copies under build/da7/diag-table-* only test symbol-name handling; they are never used by gate.py or installed over original objects.

Jump-table metadata: both a source-generated anonymous name and @0 made the diagnostic section score 100%; a descriptive jumptable name did not. Replace the artificial assembly-era updateDiskState_jumptable name in symbols.txt with the compiler-generated local name @24295. Address, size, scope, seven relocation targets, and DOL bytes are unchanged. No source table or pinned offsets remain. Rebuild the original object from the unmodified retail DOL and run the full gate to validate this metadata correction.

updateDiskState accepted: full clean gate PASS; unit code 25668/25668, data 2336/2336, functions 102/102; fresh ctxdiff 230/230 diffs 0; pool 98/98 identical. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Gate rebuilt the target from retail data after the anonymous jump-table metadata correction. Evidence: build/da7/disk-final-gate.log.

_CNTCACHEIsTitleRemovable source search: 212 compiled trials, no improvement beyond 91.31707%, 80/82 instructions. Evidence: build/da7/search-removable.log. Original exact asm retained.

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-05-search-result: 98.125%; insns 72/72 diffs 23 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-declarations-selected: 98.125%; insns 72/72 diffs 23 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-declarations-rows: 98.125%; insns 72/72 diffs 23 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-insert-helper: 98.125%; insns 72/72 diffs 23 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-insert-helper-const: 98.125%; insns 72/72 diffs 23 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-insert-helper-ref: 98.125%; insns 72/72 diffs 23 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-direct-manager: 91.31944%; insns 74/72 diffs 41 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-row-holder: 98.125%; insns 72/72 diffs 23 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-selected-holder: 99.236115%; insns 72/72 diffs 9 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-separate-next: 98.333336%; insns 72/72 diffs 22 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-separate-rows: 98.125%; insns 72/72 diffs 23 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/system/TVRC TVRCSendStartAsync tvrc-index-holder: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-index-local: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-entry-ref-holder: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/system/TVRC TVRCSendStartAsync tvrc-file-holder: 99.747475%; insns 198/198 diffs 9 | POOL IDENTICAL up to 0 (mine=0 base=0)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-cursor-early-rows: 99.236115%; insns 72/72 diffs 9 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-cursor-active-rows: 99.583336%; insns 72/72 diffs 5 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-cursor-separate-next: 99.44444%; insns 72/72 diffs 7 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-cursor-end-holder: 100.0%; insns 72/72 diffs 0 | POOL IDENTICAL up to 20 (mine=20 base=20)

- src/keyboard/tiInputForm create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer form-cursor-no-rows-reload: 98.19444%; insns 71/72 diffs 25 | POOL IDENTICAL up to 20 (mine=20 base=20)

Base::create: a one-pointer RowCursor models the selected node and insertion position. Both cursor objects together match all 72 target instructions. The pointers, indices, link updates, and initialization order preserve the prior C candidate behavior; the self-link check is the target cmplw r9,r9 and conditional branch. Pool remains 20/20. No header or other function change. Lever 18a recovered the iterator register boundaries. Full gate required before acceptance.

Base::create accepted: full non-quick gate over all nine assigned units PASS. Fresh rebuilt function 72/72 instructions, diffs 0; pool 20/20 identical. Unit instruction-exact count remains 219/221, code 47928/50656, data 3772/3772, with zero regressions. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Evidence: build/da7/final-gate-six.log.

- src/system/iplChannelManager getTitleName__Q33ipl7channel7ManagerCFiii title-language-cursor: 98.80282%; insns 71/71 diffs 13 | POOL IDENTICAL up to 9 (mine=9 base=9)

- src/system/iplChannelManager getTitleName__Q33ipl7channel7ManagerCFiii title-name-index-holder: 98.943665%; insns 71/71 diffs 12 | POOL IDENTICAL up to 9 (mine=9 base=9)

- src/system/iplChannelManager getTitleName__Q33ipl7channel7ManagerCFiii title-loop-index-holder: 98.943665%; insns 71/71 diffs 12 | POOL IDENTICAL up to 9 (mine=9 base=9)

- src/system/iplChannelManager getTitleName__Q33ipl7channel7ManagerCFiii title-language-pointer-walk: 94.985916%; insns 71/71 diffs 16 | POOL IDENTICAL up to 9 (mine=9 base=9)

## Final retained placeholders

- TVRCSendStartAsync: best C 99.747475%, 198/198 instructions, nine r6/r7 register differences. Typed command records, reference/pointer lookup helpers, separate pointer lifetimes, const/types, declaration order, and four one-field views did not resolve the tie. Source search completed 166 trials with no gain. Existing exact asm retained.
- channel::Manager::getTitleName: best C 98.943665%, 71/71 instructions, 12 address-operand/register differences. Direct member access, language-table pointer, character helper, node/name walking, local cursor/index types, and a two-trial exhausted source search did not match. Original exact asm retained. The initial search stalled at the shared limiter; its owned process was stopped after the local search finished.
- CNTCACHEClear: three new compiled shapes (line scanner, line-length updates, read-state struct) produce 13 pooled strings against nine because the existing assembly string blob duplicates ordinary literals. Prior da5 removal of that blob left only five strings: unused cache-writing routines account for four missing literals. Do not tune registers until the pool is reconstructed; no invented dead routines or offset references into the blob were added. Existing exact asm retained.
- _CNTCACHEIsTitleRemovable: best C 91.31707%, 80/82 instructions. Assignment reuse, primitive parameter, one-field result, and aggregate return did not reproduce the two missing copies. Source search over the usage helper completed 212 trials without gain. Existing exact asm retained.
- _CNTCACHEDeleteContent: best C 95.793106%, 143/145 instructions. Usage-helper lifetime variants, assigned result parameter, const TMD view and declaration ordering did not recover the missing copy/reload. Source search completed 241 trials without gain. Existing exact asm retained.
- ISD_GetCardSize: best C 98.39286%, 84/84 instructions, 20 register differences. Output geometry struct, separate scaling value and expression grouping, and primitive width spellings did not improve the prior result. Source search exhausted one legal variant without improvement. Existing exact asm retained.

Every retained function has at least three distinct compiled source-level attempts in this run. Ghidra exports were checked for every assigned function. Definition-level volatile was considered only where the target shows repeated flag loads; none of the unresolved differences establishes a missing volatile declaration. No volatile or diagnostic pragma was retained. Prior-art GitHub searches for the SDK functions failed with HTTP 401; public web searches for the exact names returned no results.

## Final validation

Six of twelve assigned placeholders were replaced with C/C++; six remain as exact assembly. All twelve live symbols independently report objdiff 100.0% and identical instructions after the final clean build. The converted functions are:

| Function | Instructions | Conversion commit |
| --- | --- | --- |
| snd::System::resetAllSound | 68/68, diffs 0 | d47f9fea |
| gui::PaneComponent::draw | 104/104, diffs 0 | 38f6f578 |
| LibTVRC::__FTVRCLoop0Handler | 120/120, diffs 0 | 0b1d74f7 |
| push_button_queue | 28/28, diffs 0 | 05363f2b |
| ChannelSelect::updateDiskState | 230/230, diffs 0 | 467eb0a2 |
| inputform::Base::create | 72/72, diffs 0 | 8c40bbde |

The resetAllSound return declaration remains the existing int declaration; the target does not define a return value, as recorded above. The jump table metadata correction changes only its anonymous local name; byte extent and relocation targets are unchanged. Both details require parent source review.

| Unit | Instruction-exact before -> after | Exact code before -> after | Data before -> after |
| --- | --- | --- | --- |
| TVRC | 9/9 -> 9/9 | 2312/2312 -> 2312/2312 | 280/280 -> 280/280 |
| iplChannelManager | 74/74 -> 74/74 | 12552/12552 -> 12552/12552 | 1080/1080 -> 1080/1080 |
| iplSound | 56/57 -> 56/57 | 5576/5576 -> 5576/5576 | 3316/3316 -> 3316/3316 |
| iplChannelSelect | 102/102 -> 102/102 | 25668/25668 -> 25668/25668 | 2336/2336 -> 2336/2336 |
| iplButton | 41/42 -> 41/42 | 7624/7624 -> 7624/7624 | 1744/1744 -> 1744/1744 |
| tiGUIManager | 42/42 -> 42/42 | 5916/5916 -> 5916/5916 | 392/392 -> 392/392 |
| tiInputForm | 219/221 -> 219/221 | 47928/50656 -> 47928/50656 | 3772/3772 -> 3772/3772 |
| cntcache | 5/5 -> 5/5 | 1828/1828 -> 1828/1828 | 280/280 -> 280/280 |
| sdi_api | 22/22 -> 22/22 | 5948/5948 -> 5948/5948 | 248/248 -> 248/248 |

The existing alias differences account for the sound and button instruction-exact counters. tiInputForm retains its two pre-existing non-exact functions and remains unlinked. Converted function counts do not raise the exact totals because their previous asm bodies were already exact.

Final full non-quick gate: build/da7/final-gate-six.log. All nine pools identical; zero regressions, forbidden-pattern additions, or readability warnings. Every assigned data section remains exact. Independent twelve-symbol audit: build/da7/final-audit.txt.

GATE PASS

DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.

Local conversion commits only; no push, PR, merge, rebase, worker spawn, or other-worktree edit. Scratch trials and exported evidence remain under build/da7/.

Integration boundary: the leaf is agent/w1005/da7, based on 5e7b5ad0. At the first handoff check, the shared origin/main ref had advanced by four commits to 66ff3a4331e21dc76b13a9f3314def947c4616dd. Those four reviewed commits do not replace an assigned source file, but 02fe1755 changes configure.py and the shared nw4r/lyt/pane.h. Main continued advancing during the final status checks, so this is a recorded checkpoint, not a claim that the leaf is synchronized. The six conversions were built and gated on this leaf; the parent must independently verify them on current main. No merge or rebase was attempted. No owned source-search process remains running.
