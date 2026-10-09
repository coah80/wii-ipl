# cleanup2-x8 attempts

Worktree /mnt/drive2/projects/wii-ipl-workers/data-d7. Branch agent/w1009/cleanup2-x8. Baseline c3dd1c08c04a38975b63dded77a7aef6fce385f3.

Read cleanup-common.md fully, including wave-2 goto and comma guidance, before building. Read AGENTS.md, unslop, and writing-for-agents. Prior memory supplied verification conventions; all completion measurements below come from this run.

Full 43U baseline build passed. Initial report: 1028/1028 units fully linked, 12563/12563 functions exact, all code and data matched. Initial completion checker returned DECOMPLETE_OK. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.

## Scope and exclusions

Inventoried 58 files by descending size. Audited the 51 files not changed in the last 12 hours. The largest eligible file was tiPcKeyboard.cpp. Large tiCpData, tiPkData, and tiSwData files are keyboard tables; preserved their data and encodings.

Skipped these seven recently changed files, using git log --since=12.hours --name-only:

- src/BS2/BS2Mach.c
- src/BS2/BS2Update.c
- src/channelScript/CHANSVm.c
- src/keyboard/tiHwKeyboard.cpp
- src/keyboard/tiInputForm.cpp
- src/keyboard/tiString.cpp
- src/keyboard/tiZiString.cpp

Kept idiomatic shared error exits in BS2::HasTitleInstalled and SaveData::decode_odh, plus Base::onActive's common updateFix tail. Preserved the remaining ordinary handlers and lookup tables. Left all hand-written assembly and the BS2Start .init pragma untouched. No header, configure.py, other-worktree, push, PR, merge, rebase, or subagent changes.

## Comparison method

Each trial built its 43U object sequentially. Compared every allocated section byte, section size/type/flags/alignment, resolved relocation, and global/weak symbol against the initial built object. Reverted and rebuilt any trial that changed that signature.

The first comparator used whole-object equality. Removing the unused next local and renaming tmp changed only .strtab, so that trial was initially restored. Re-ran it with the allocated-section and relocation comparator; code, data, layout, linkage, and symbols were identical. Local-name metadata does not enter the DOL.

## Trials

- src/keyboard/tiPcKeyboard.cpp: OnOffButtonAnmPane::onAnmEvent: load animation before comma-free conditions; reverted; changed .rela.data, .rela.text, .strtab, .symtab, .text.
- src/keyboard/tiPcKeyboard.cpp: OnOffButtonAnmPane::onAnmEvent: guarded loads and early returns; reverted; changed .rela.data, .rela.text, .strtab, .symtab, .text.
- src/keyboard/tiPcKeyboard.cpp: OnOffButtonAnmPane::onAnmEvent: simplify condition grouping and use event enums; retained; allocated sections, resolved relocations, and global symbols identical.
- src/keyboard/tiPcKeyboard.cpp: OnOffButtonAnmPane::onAnmEvent: name all pane events and document guarded loads; retained; allocated sections, resolved relocations, and global symbols identical.
- src/keyboard/tiCandidateBox.cpp: UITextArea::Create: remove local pool_data pragma; retained; allocated sections, resolved relocations, and global symbols identical.
- src/keyboard/tiCandidateBox.cpp: scEmptyWChars: remove explicit_zero_data pragma; reverted; changed .comment, .rela.ctors, .rela.data, .rela.rodata, .rela.sdata, .rela.text, .sbss, .sdata, .shstrtab, .symtab.
- src/keyboard/tiCandidateBox.cpp: Base::updateCandidate: index candidate text directly instead of struct-stride casts; reverted; changed .rela.text, .strtab, .symtab, .text.
- src/keyboard/tiCandidateBox.cpp: UITextArea::StartScrollPageToIdx: remove unused next local and name next page index; reverted; changed .strtab.
- src/keyboard/tiCandidateBox.cpp: scEmptyWChars: document required initialized-data placement; retained; allocated sections, resolved relocations, and global symbols identical.
- src/keyboard/tiCandidateBox.cpp: UITextArea::StartScrollPageToIdx: remove unused next and name page index, compare allocated sections and relocations; retained; allocated sections, resolved relocations, and global symbols identical.
- src/BS2/BS2.c: HasTitleInstalled: use byte pointers for work-buffer offsets; retained; allocated sections, resolved relocations, and global symbols identical.
- src/channelScript/systemmenu/iplCSSavedata.cpp: decode_odh: use existing RGB565 format enum in decoder dispatch; retained; allocated sections, resolved relocations, and global symbols identical.
- src/keyboard/tiSignWindow.cpp: LayoutByNW4R::onKey: use a control-key branch instead of character goto; retained; allocated sections, resolved relocations, and global symbols identical.
- src/keyboard/tiNw4rManager.cpp: Layout pane visibility: name the generated bounding-pane buffer; retained; allocated sections, resolved relocations, and global symbols identical.
- src/keyboard/tiGUIManager.cpp: GUIManager::update: use structured touch handling in pointer event cases; reverted; changed .rela.text, .strtab, .symtab, .text.
- src/keyboard/tiGUIManager.cpp: PaneManager::setAllBoundingBoxComponentTriggerTarget: remove use-site volatile; reverted; changed .rela.text, .strtab, .symtab, .text.
- src/keyboard/tiGUIManager.cpp: PaneManager::setAllBoundingBoxComponentTriggerTarget: use the list-size accessor; reverted; changed .rela.text, .strtab, .symtab, .text.
- src/keyboard/tiGUIManager.cpp: GUIManager and PaneManager: document required shared switch tail and list-count reloads; retained; allocated sections, resolved relocations, and global symbols identical.
- src/keyboard/tiTextDrawer.cpp: Base::getWidth: use a for loop instead of check and body gotos; reverted; changed .strtab, .text.
- src/BS2/BS2Fatal.c: ScreenReport: use nested loops for line wrapping and newline handling; reverted; changed .strtab, .text.
- src/channelScript/systemmenu/iplCSPane.cpp: become_youngest_pane: use the existing parent accessor instead of a raw offset cast; reverted; changed .strtab, .text.
- src/keyboard/tiTextDrawer.cpp: Base::getWidth: use a character-reading while loop; retained; allocated sections, resolved relocations, and global symbols identical.
- src/BS2/BS2Fatal.c: ScreenReport: name the shared line-start jump and document layout requirement; retained; allocated sections, resolved relocations, and global symbols identical.
- src/channelScript/systemmenu/iplCSPane.cpp: become_youngest_pane: initialize a scoped parent through the accessor; reverted; changed .strtab, .text.
- src/channelScript/systemmenu/iplCSPane.cpp: become_youngest_pane: document required parent-load expression; retained; allocated sections, resolved relocations, and global symbols identical.
- src/channelScript/systemmenu/iplCSColor.cpp: color::ctor: assign the packed integer directly instead of an argument struct overlay; retained; allocated sections, resolved relocations, and global symbols identical.
- src/channelScript/systemmenu/iplCSColor.cpp: color::ctor: remove unused componentValue local; retained; allocated sections, resolved relocations, and global symbols identical.
- src/channelScript/systemmenu/iplCSColor.cpp: color::set: operate on the color union without a padded wrapper; retained; allocated sections, resolved relocations, and global symbols identical.
- src/channelScript/systemmenu/iplCSColor.cpp: color::get: read the color union without a padded wrapper; retained; allocated sections, resolved relocations, and global symbols identical.
- src/channelScript/systemmenu/iplCSColor.cpp: color: remove the unused padded CS_Struct definition; retained; allocated sections, resolved relocations, and global symbols identical.
- src/keyboard/tiCandidateBox.cpp: Base::updateCandidate: use a writable text-row pointer instead of a struct-stride cast; reverted; changed .strtab, .text.
- src/keyboard/tiCandidateBox.cpp: LayoutByNW4R::updateCandidate: use a writable text-row pointer instead of a struct-stride cast; reverted; changed .strtab, .text.
- src/keyboard/tiCandidateBox.cpp: Candidate events: name selection and scroll payloads; document retained candidate-row views; retained; allocated sections, resolved relocations, and global symbols identical.

## Retained result

- tiPcKeyboard.cpp: removed excessive condition grouping and used existing PE event enums. Kept the two event-guarded comma loads; hoisting the animation load and guarded early-return branches changed .text. Added one compiler-requirement line. Base::onActive common-tail gotos remain idiomatic.
- tiCandidateBox.cpp: removed UITextArea::Create push/pool_data/pop pragmas, their stale HACK comment, and the unused scroll next local. Named nextPageIdx, candidateIdx, and scrollSteps. Kept explicit_zero_data because removing it moves the empty buffer from .sdata to .sbss. Kept both candidate-row destination views because direct indexing and writable text pointers change .text. Added one-line explanations beside retained forms.
- BS2.c: replaced three pointer-to-integer work-buffer offsets with byte-pointer arithmetic. Kept common fail exits.
- iplCSSavedata.cpp: used GX_TF_RGB565 in decoder dispatch. Kept common exit paths.
- tiSignWindow.cpp: replaced the character-dispatch goto with a control-key branch. Gotos 1 -> 0.
- tiNw4rManager.cpp: named the generated boundingPaneName buffer.
- tiGUIManager.cpp: kept the shared point/move switch tail and volatile list-count reference. Separate switch tails, a plain reference, and List_GetSize changed .text. Added one-line compiler explanations.
- tiTextDrawer.cpp: replaced getWidth check/body gotos with an idiomatic character-reading while loop. Gotos 2 -> 0. The initial for-loop form changed .text.
- BS2Fatal.c: named the shared nextLine branch and explained its requirement. The nested-loop alternative changed .text; retained two line-wrap/newline jumps.
- iplCSPane.cpp: retained the raw parent load with one compiler explanation. Both GetParent accessor forms changed .text.
- iplCSColor.cpp: removed the padded CS_Struct overlay and unused componentValue local. Constructor assigns the packed integer directly; component templates operate on the four-byte color union. All five independent cleanup steps preserved allocated bytes and linkage.

## Final verification

One final gate.py run covered all eleven changed units with --quick, as cleanup-common.md requires. Full build passed. Every unit pool is IDENTICAL; every code/data section reports 100.0; all functions below remain instruction-exact and fully linked. Measures and allocated object signatures equal the initial baseline.

- src/BS2/BS2.c: exact functions 9/9; code 6060/6060; data 5840/5840.
- src/BS2/BS2Fatal.c: exact functions 10/10; code 3116/3116; data 2448/2448.
- src/channelScript/systemmenu/iplCSColor.cpp: exact functions 22/22; code 3104/3104; data 128/128.
- src/channelScript/systemmenu/iplCSPane.cpp: exact functions 36/36; code 5804/5804; data 672/672.
- src/channelScript/systemmenu/iplCSSavedata.cpp: exact functions 35/35; code 5836/5836; data 512/512.
- src/keyboard/tiCandidateBox.cpp: exact functions 112/112; code 24000/24000; data 4652/4652.
- src/keyboard/tiGUIManager.cpp: exact functions 42/42; code 5916/5916; data 392/392.
- src/keyboard/tiNw4rManager.cpp: exact functions 46/46; code 6132/6132; data 240/240.
- src/keyboard/tiPcKeyboard.cpp: exact functions 141/141; code 28484/28484; data 18564/18564.
- src/keyboard/tiSignWindow.cpp: exact functions 56/56; code 7184/7184; data 3468/3468.
- src/keyboard/tiTextDrawer.cpp: exact functions 24/24; code 3476/3476; data 1608/1608.

Combined owned result: 533/533 exact functions, 99112/99112 code bytes, 38524/38524 data bytes; all fully linked. No unit changed its Matching configuration. Refreshed progress/report.json and checked build/43U/ok. Completion checker returned DECOMPLETE_OK. All 12563 functions and all 1028 units remain exact and fully linked. The aggregate fuzzy percentage retains its baseline rounding value of 99.999886.

GATE PASS: 0 regressions, 0 forbidden additions, 0 readability warnings. Gate output /tmp/cleanup2-x8-gate.txt. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Source review, assembly-preservation comparison, and git diff --check passed.

## Source commits

- 19c503c0c cleanup: simplify PC keyboard animation event conditions
- 49dda28d9 cleanup: remove candidate text pooling pragma and unused scroll local
- 129a9af99 cleanup: use byte pointers for BS2 title work buffers
- 8cfc3e379 cleanup: name savedata RGB565 decoder format
- 6bae544b1 cleanup: structure sign-window character input dispatch
- 1f6414e09 cleanup: name NW4R bounding pane visibility buffer
- 3a63f6f10 cleanup: explain required GUI event tail and list-count reloads
- 4355943be cleanup: simplify text-width loop while preserving compiler layout
- c34803c49 cleanup: explain BS2 fatal-report shared line branch
- f5284a5ea cleanup: explain channel-script parent-load requirement
- a5b60f3ec cleanup: remove channel-script color overlay and unused local
- dcd77ced9 cleanup: name candidate event payloads and document row views
