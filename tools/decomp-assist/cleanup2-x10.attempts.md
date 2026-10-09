# cleanup2-x10

Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d9`, branch `agent/w1009/cleanup2-x10`.
Baseline `f2006bdd`; all 1028 units, 12563 functions and code/data/link measures are 100%.
Initial full 43U build passed. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`; `DECOMPLETE_OK`.

## Acceptance

Each trial must preserve every object section and relocation byte for byte, except compiler-generated local names in .strtab. Reject and restore any changed code, data, symbol-table layout or relocation. Confirm harmless .strtab changes through objdiff and the linked DOL.
Final verification requires a full build, fresh report, all touched sections at 100%, `DECOMPLETE_OK`, and the worker gate with zero regressions.
Commit each retained source file separately. Leave hand-written assembly alone.

## Review and trials

Reviewed HBMBase.cpp, www_wiisetting.cpp and www_browser.cpp for pragmas, decompiler gotos, comma conditions, placeholder names and offset-cast workarounds. No scoped wave-2 candidates found. Existing placement allocation and parser field accesses remain. No pragmas or volatile casts occur in any assigned source directory.
- `src/bannerSound/AudioWaveUtility.cpp` use the dataLen parameter directly instead of aliasing its address: RESTORE, built object changed; sections .strtab, .text; checkFile__12WaveFileAiffFPCvUlb instructions 272/272, diffs 28.
- `src/bannerSound/AudioWaveUtility.cpp` use member accesses directly instead of the casted self pointer: RESTORE, built object changed; sections .strtab, .text; checkFile__12WaveFileAiffFPCvUlb instructions 272/272, diffs 24.
- `src/bannerSound/AudioWaveUtility.cpp` read the marker count before the for initializer: RESTORE, built object changed; sections .strtab.

The first utility comma trial changed only `.strtab`, so it was restored under an unnecessarily strict raw-object check. The executable sections, symbol-table layout and relocations were identical. Retry it under the section/relocation check and confirm objdiff/DOL.
- `src/bannerSound/AudioWaveUtility.cpp` replace the dataLen type-pun with a normal parameter copy: RESTORE, built object changed; sections .text; checkFile__12WaveFileAiffFPCvUlb instructions 272/272, diffs 28.
- `src/bannerSound/AudioWaveUtility.cpp` replace the self pointer cast with this: RESTORE, built object changed; sections .text; checkFile__12WaveFileAiffFPCvUlb instructions 272/272, diffs 24.
- `src/bannerSound/AudioWaveUtility.cpp` read the marker count before the for initializer: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/bannerSound/AudioWaveUtility.cpp` document the aliases required for MWCC register allocation: KEEP, built object byte-identical.
- `src/iplwww/www_window.cpp` remove unused receive locals and the obsolete goto comment: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/sound/iplSound.cpp` startSE use early returns instead of return/continue labels: RESTORE, built object changed; sections .rela.text, .strtab, .symtab, .text; startSE__Q33ipl3snd6SystemFPCc instructions 60/62, diffs 46.
- `src/sound/iplSound.cpp` startSEIndex use early returns instead of return/continue labels: RESTORE, built object changed; sections .rela.text, .strtab, .symtab, .text; startSEIndex__Q33ipl3snd6SystemFUl instructions 60/62, diffs 46.
- `src/sound/iplSound.cpp` name the swapped lower bound originalLo instead of temp: KEEP, built object byte-identical.
- `src/sound/iplSound.cpp` startSE share the early return in a short-circuit condition: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/sound/iplSound.cpp` startSEIndex share the early return in a short-circuit condition: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/layout/iplLayout.cpp` Object::~Object() replace comma condition with while iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; __dt__Q33ipl6layout6ObjectFv instructions 73/77, diffs 68.
- `src/layout/iplLayout.cpp` Object::~Object() replace comma condition with for iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; __dt__Q33ipl6layout6ObjectFv instructions 73/77, diffs 68.
- `src/layout/iplLayout.cpp` Object::~Object() replace comma condition with break iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; __dt__Q33ipl6layout6ObjectFv instructions 73/73, diffs 18.
- `src/layout/iplLayout.cpp` void Object::finishBinding() replace comma condition with while iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; finishBinding__Q33ipl6layout6ObjectFv instructions 36/39, diffs 34.
- `src/layout/iplLayout.cpp` void Object::finishBinding() replace comma condition with for iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; finishBinding__Q33ipl6layout6ObjectFv instructions 36/39, diffs 34.
- `src/layout/iplLayout.cpp` void Object::finishBinding() replace comma condition with break iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; finishBinding__Q33ipl6layout6ObjectFv instructions 36/35, diffs 28.
- `src/layout/iplLayout.cpp` void Object::calc() replace comma condition with while iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; calc__Q33ipl6layout6ObjectFv instructions 38/41, diffs 34.
- `src/layout/iplLayout.cpp` void Object::calc() replace comma condition with for iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; calc__Q33ipl6layout6ObjectFv instructions 38/41, diffs 34.
- `src/layout/iplLayout.cpp` void Object::calc() replace comma condition with break iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; calc__Q33ipl6layout6ObjectFv instructions 38/37, diffs 30.
- `src/layout/iplLayout.cpp` void Object::start( replace comma condition with while iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; start__Q33ipl6layout6ObjectFi instructions 34/37, diffs 30.
- `src/layout/iplLayout.cpp` void Object::start( replace comma condition with for iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; start__Q33ipl6layout6ObjectFi instructions 34/37, diffs 30.
- `src/layout/iplLayout.cpp` void Object::start( replace comma condition with break iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; start__Q33ipl6layout6ObjectFi instructions 34/32, diffs 22.
- `src/layout/iplLayout.cpp` void Object::setMaxFrame( replace comma condition with while iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; setMaxFrame__Q33ipl6layout6ObjectFfi instructions 28/30, diffs 21.
- `src/layout/iplLayout.cpp` void Object::setMaxFrame( replace comma condition with for iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; setMaxFrame__Q33ipl6layout6ObjectFfi instructions 28/30, diffs 21.
- `src/layout/iplLayout.cpp` void Object::setMaxFrame( replace comma condition with break iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; setMaxFrame__Q33ipl6layout6ObjectFfi instructions 28/27, diffs 19.
- `src/layout/iplLayout.cpp` void Object::setMinFrame( replace comma condition with while iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; setMinFrame__Q33ipl6layout6ObjectFfi instructions 28/30, diffs 21.
- `src/layout/iplLayout.cpp` void Object::setMinFrame( replace comma condition with for iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; setMinFrame__Q33ipl6layout6ObjectFfi instructions 28/30, diffs 21.
- `src/layout/iplLayout.cpp` void Object::setMinFrame( replace comma condition with break iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; setMinFrame__Q33ipl6layout6ObjectFfi instructions 28/27, diffs 19.
- `src/layout/iplLayout.cpp` void Object::setAnmType( replace comma condition with while iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; setAnmType__Q33ipl6layout6ObjectFii instructions 28/30, diffs 21.
- `src/layout/iplLayout.cpp` void Object::setAnmType( replace comma condition with for iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; setAnmType__Q33ipl6layout6ObjectFii instructions 28/30, diffs 21.
- `src/layout/iplLayout.cpp` void Object::setAnmType( replace comma condition with break iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; setAnmType__Q33ipl6layout6ObjectFii instructions 28/27, diffs 19.
- `src/layout/iplLayout.cpp` bool Object::isPlaying( replace comma condition with while iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; isPlaying__Q33ipl6layout6ObjectCFi instructions 38/40, diffs 31.
- `src/layout/iplLayout.cpp` bool Object::isPlaying( replace comma condition with for iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; isPlaying__Q33ipl6layout6ObjectCFi instructions 38/40, diffs 31.
- `src/layout/iplLayout.cpp` bool Object::isPlaying( replace comma condition with break iteration: RESTORE, built object changed; sections .text, .symtab, .strtab, .rela.text; isPlaying__Q33ipl6layout6ObjectCFi instructions 38/37, diffs 29.
- `src/layout/iplLayout.cpp` Object::~Object() remove the redundant comma and test the assigned pointer directly: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/layout/iplLayout.cpp` void Object::finishBinding() remove the redundant comma and test the assigned pointer directly: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/layout/iplLayout.cpp` void Object::calc() remove the redundant comma and test the assigned pointer directly: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/layout/iplLayout.cpp` void Object::start( remove the redundant comma and test the assigned pointer directly: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/layout/iplLayout.cpp` void Object::setMaxFrame( remove the redundant comma and test the assigned pointer directly: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/layout/iplLayout.cpp` void Object::setMinFrame( remove the redundant comma and test the assigned pointer directly: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/layout/iplLayout.cpp` void Object::setAnmType( remove the redundant comma and test the assigned pointer directly: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/layout/iplLayout.cpp` bool Object::isPlaying( remove the redundant comma and test the assigned pointer directly: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/iplwww/www_window.cpp` remove the unused two-integer constructor struct: RESTORE, built object changed; sections .strtab, .symtab, .rela.text, .text; __ct__Q37ext_ead3www13BrowserWindowFPQ37ext_ead3www13BrowserThread instructions 66/64, diffs 7.
- `src/bannerSound/AxAdpcmPlayer.cpp` reload the channel count as a statement before the loop limit: RESTORE, built object changed; sections .strtab, .rela.text, .text; start__19AxAdpcmSimplePlayerFPvUlP13AxAdpcmHandle instructions 316/316, diffs 186.
- `src/bannerSound/AxAdpcmPlayer.cpp` remove the comma and compare against the assigned channel count: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/iplwww/www_window.cpp` document the required constructor stack initialization: KEEP, built object byte-identical.
- `src/homebutton/HBMController.cpp` use the declared SoundHandle member with automatic construction/destruction: RESTORE, built object changed; sections .rela.text, .text, .comment, .symtab, .strtab; __ct__Q210homebutton10ControllerFiPQ210homebutton9RemoteSpk instructions 51/54, diffs 47.
- `src/homebutton/HBMController.cpp` document the required handle initialization/destruction shape: KEEP, built object byte-identical.
- `src/homebutton/HBMRemoteSpk.cpp` DelaySpeakerOnCallback remove the unused result local: KEEP, built object byte-identical.
- `src/homebutton/HBMRemoteSpk.cpp` SpeakerOnCallback remove the dead result assignment: KEEP, built object byte-identical.
- `src/homebutton/HBMRemoteSpk.cpp` DelaySpeakerPlayCallback remove the unused result local: KEEP, built object byte-identical.
- `src/homebutton/HBMRemoteSpk.cpp` Connect remove the unused result local: KEEP, built object byte-identical.
- `src/homebutton/HBMRemoteSpk.cpp` isPlayReady remove the redundant boolean comparison: RESTORE, built object changed; sections .symtab, .text; isPlayReady__Q210homebutton9RemoteSpkCFl instructions 6/4, diffs 3.
- `src/bannerSound/AudioWavePlayer.cpp` return the thread creation boolean directly: RESTORE, built object changed; sections .symtab, .rela.text, .text; makeThread__16SimpleWavePlayerFlPvUl instructions 38/36, diffs 9.
- `src/bannerSound/BannerSoundPlayer.cpp` derive the player thread stack size from its array: KEEP, built object byte-identical.
- `src/iplwww/www_arcreader.cpp` derive the archive slot limit from the flag array and remove a commented assignment: RESTORE, built object changed; sections .text; RegisterArcFile__Q33www9arcreader12ArcContainerFPCv instructions 43/43, diffs 1.
- `src/homebutton/HBMRemoteSpk.cpp` document the required stored-flag normalization: KEEP, built object byte-identical.
- `src/bannerSound/AudioWavePlayer.cpp` document the required thread-result comparison: KEEP, built object byte-identical.
- `src/iplwww/www_arcreader.cpp` use the archive flag array size with the existing signed comparison: KEEP, built object byte-identical.
- `src/iplwww/www_arcreader.cpp` remove the obsolete commented protocol status assignment: KEEP, built object byte-identical.
- `src/homebutton/HBMFrameController.cpp` ANIM_TYPE_FORWARD separate the frame update from its condition: RESTORE, built object changed; sections .rela.text, .text; calc__Q210homebutton15FrameControllerFv instructions 82/82, diffs 9.
- `src/homebutton/HBMFrameController.cpp` ANIM_TYPE_BACKWARD separate the frame update from its condition: KEEP, built object byte-identical.
- `src/homebutton/HBMFrameController.cpp` ANIM_TYPE_LOOP separate the frame update from its condition: KEEP, built object byte-identical.
- `src/homebutton/HBMFrameController.cpp` ANIM_TYPE_ALTERNATE += separate the frame update from its condition: RESTORE, built object changed; sections .rela.text, .text; calc__Q210homebutton15FrameControllerFv instructions 82/82, diffs 9.
- `src/homebutton/HBMFrameController.cpp` ANIM_TYPE_ALTERNATE -= separate the frame update from its condition: KEEP, built object byte-identical.
- `src/homebutton/HBMFrameController.cpp` ANIM_TYPE_FORWARD read the frame boundary before the separate frame update: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/homebutton/HBMFrameController.cpp` ANIM_TYPE_ALTERNATE read the frame boundary before the separate frame update: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/bannerSound/AxAdpcmPlayer.cpp` document the required channel-count condition update: KEEP, built object byte-identical.
- `src/homebutton/HBMFrameController.cpp` ANIM_TYPE_FORWARD reuse the cached frame boundary for clamping: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.
- `src/homebutton/HBMFrameController.cpp` ANIM_TYPE_ALTERNATE reuse the cached frame boundary for clamping: KEEP, all object sections and relocations byte-identical except compiler-generated names in .strtab.

## Retained source and scope

- AxAdpcmPlayer keeps its shared `clean_up` exits. They are idiomatic error cleanup. The channel-count assignment stays in the loop condition because moving it changes 186 instructions; its redundant comma is removed.
- iplLayout keeps idiomatic assignment tests after separate initialization/while, for, and break-loop trials changed the bytes. All eight comma operators are removed.
- AudioWaveUtility keeps the local parameter/self aliases. Normal copies and direct member access change register allocation, as measured above.
- www_window keeps the two constructor initialization stores. Removing its unused struct deletes two target instructions.
- HBMController keeps inline handle storage initialization and the explicit destructor call. Automatic construction adds three target instructions.
- HBMRemoteSpk and AudioWavePlayer keep their boolean normalization comparisons. Removing them deletes target instructions.
- No hand-written assembly, headers, configuration, or other worktrees changed.
- HBMBase, www_wiisetting, www_browser, HBMGUIManager, GUIManager, www_surface, www_trasition, HBMAnmController, iplGuiManager, www_thread, www_print and www_message were inspected for the assigned cleanup patterns and left unchanged.

## Source commits

a293dc09 cleanup(bannerSound): separate AIFF marker count initialization
ad194ccb cleanup(iplwww): remove obsolete receive-loop locals
32f0a0cb cleanup(sound): replace sound-start gotos with shared returns
aafa586f cleanup(layout): remove redundant animation-loop comma operators
b854f207 docs(iplwww): explain the required constructor stack stores
d4c6c76c cleanup(bannerSound): remove the channel-count comma condition
12d9137b docs(homebutton): explain the required sound handle lifetime
a1598ad9 docs(bannerSound): explain the required thread-result comparison
15f62999 cleanup(homebutton): remove unused speaker control results
cb0db179 cleanup(bannerSound): derive thread stack size from the buffer
30a9405a cleanup(iplwww): derive archive capacity from the flag array
d9214987 cleanup(homebutton): separate frame updates from conditions

## Final validation

Gate ran once at the end over all 11 changed units with `--quick`. Full 43U build passed.
All allocated section bytes, sizes and alignments are identical to the saved baseline objects.
Every touched function and section is 100% in the fresh report; code and data are fully linked.

| Unit | Code bytes | Data bytes | Exact functions | Sections and link |
| --- | --- | --- | --- | --- |
| src/bannerSound/AudioWavePlayer | 3288/3288 | 80/80 | 23/23 | 100% |
| src/bannerSound/AudioWaveUtility | 5496/5496 | 520/520 | 33/33 | 100% |
| src/bannerSound/AxAdpcmPlayer | 3088/3088 | 6476/6476 | 13/13 | 100% |
| src/bannerSound/BannerSoundPlayer | 1572/1572 | 16408/16408 | 13/13 | 100% |
| src/homebutton/HBMController | 2356/2356 | 440/440 | 26/26 | 100% |
| src/homebutton/HBMFrameController | 392/392 | 8/8 | 3/3 | 100% |
| src/homebutton/HBMRemoteSpk | 1824/1824 | 24/24 | 16/16 | 100% |
| src/iplwww/www_arcreader | 952/952 | 152/152 | 5/5 | 100% |
| src/iplwww/www_window | 3392/3392 | 1264/1264 | 18/18 | 100% |
| src/layout/iplLayout | 5328/5328 | 208/208 | 50/50 | 100% |
| src/sound/iplSound | 5576/5576 | 3316/3316 | 57/57 | 100% |

[src/bannerSound/AudioWaveUtility] instruction-exact functions: 33/33
[src/bannerSound/AudioWavePlayer] instruction-exact functions: 23/23
[src/bannerSound/AxAdpcmPlayer] instruction-exact functions: 13/13
[src/bannerSound/BannerSoundPlayer] instruction-exact functions: 13/13
[src/homebutton/HBMController] instruction-exact functions: 26/26
[src/homebutton/HBMFrameController] instruction-exact functions: 3/3
[src/homebutton/HBMRemoteSpk] instruction-exact functions: 16/16
[src/iplwww/www_arcreader] instruction-exact functions: 5/5
[src/iplwww/www_window] instruction-exact functions: 18/18
[src/layout/iplLayout] instruction-exact functions: 50/50
[src/sound/iplSound] instruction-exact functions: 57/57

GATE PASS
Regressions: 0. Forbidden patterns added: 0. Readability warnings: 0.
`python3 tools/check_decomp_complete.py build/43U/report.json --dol build/43U/main.dol`: `DECOMPLETE_OK`.
DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.
No pushes, PRs, merges or rebases. `origin/main` moved during this run; this branch remains based on `f2006bdd` for the parent to integrate.
