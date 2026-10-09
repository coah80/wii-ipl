# cleanup2-w6 attempts

Baseline 85d653b0dba14d81de4d9cf125a945d8c6ef57f7. Full 43U build passed before edits; all 1028 units linked and matched. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Existing untracked rx4/rx59/rx70 files are outside this task.

Read cleanup-common.md, including wave-2 guidance. Applied unslop and writing-for-agents to this log and final report. Queried the existing WithZi graph. Older memory reports describe pre-completion source trials; current built objects govern cleanup.

Every trial compares allocated section bytes, layout, and resolved relocations with the initial built object. A byte change or build failure restores the immediately preceding source and rebuilds it. Common error exits and required compiler forms remain when structured alternatives change bytes.

## Trials

- keyboard/tiString: restore Hangul composer explanation beside MWCC note: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiZiString: ChangeDictionaryLanguage use if/else instead of dictionary gotos: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiZiString: partialConfirmForKR replace final-letter goto with loop break: reverted; changed .text.
- keyboard/tiZiString: partialConfirmForKR use structured trailing-letter selection: reverted; changed .text.
- keyboard/tiZiString: update move context reset out of comma condition: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiZiString: update replace candidate-skip goto with continue: reverted; changed .rela.data, .rela.text, .text.
- keyboard/tiZiString: complementsCandidates_ replace scan gotos with while and break: reverted; changed .text.
- keyboard/tiZiString: complementsCandidates_ replace mode gotos with enum switch: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiZiString: setElementBuffer replace ElementInputView with related buffer pointers: reverted; changed .text.
- keyboard/tiHwKeyboard: updateTriggerKey_ structure numeric character filtering: reverted; changed .rela.data, .rela.text, .text.
- keyboard/tiHwKeyboard: updateTriggerKey_ structure numeric control-key filtering: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiHwKeyboard: updateRepeatKey_ replace dispatch gotos with switch: reverted; changed .rela.data, .rela.text, .text.
- keyboard/tiHwKeyboard: align key-input initialization with surrounding statements: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiInputForm: findURL replace character-dispatch gotos with character switch: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiInputForm: notifyChangeMode replace checkInput jump with explicit mode-check flag: reverted; changed .rela.ctors, .rela.data, .rela.text, .text.
- keyboard/tiInputForm: remove DeadKeyStream const-section pragma with mutable local table: reverted; changed .data, .rela.data, .rela.text, .rodata, .text.
- BS2/BS2Update: BS2SelectUpdateEntries replace product-region jumps with if/else: reverted; changed .rela.data, .rela.text, .text.
- BS2/BS2Update: BS2SelectUpdateEntries use product-area enum names in fallback switches: retained; allocated bytes, section layout, and resolved relocations identical.
- BS2/BS2Mach: BS2GetLockedTitles replace entry jump with a null-output branch: retained; allocated bytes, section layout, and resolved relocations identical.
- BS2/BS2Mach: BS2Tick structure GameCube region selection: reverted; changed .rela.data, .rela.text, .text.
- BS2/BS2Mach: BS2Tick structure Wii region selection: reverted; changed .rela.data, .rela.text, .text.
- BS2/BS2Mach: BS2Tick structure title-prefix dispatch and universal-region case: reverted; build failed.
- BS2/BS2Mach: BS2Tick remove duplicate 410 title comparison: reverted; changed .rela.data, .rela.text, .text.
- keyboard/tiHwKeyboard: updateRepeatKey_ use for-loop dispatch with explicit Tab case: reverted; changed .rela.data, .rela.text, .text.
- keyboard/tiHwKeyboard: updateTriggerKey_ use explicit digit and punctuation switch: reverted; changed .rela.data, .rela.text, .text.
- BS2/BS2Mach: BS2Tick structure title-prefix dispatch with corrected scope: reverted; changed .rela.data, .rela.text, .text; functions BS2Tick: 849 changed instructions, 1939/1940.
- BS2/BS2Mach: BS2StartGame structure disk-error exits with a single attempt block: retained; allocated bytes, section layout, and resolved relocations identical.
- BS2/BS2Mach: BS2StartGame structure partition-error exits with a single attempt block: reverted; changed .rela.data, .rela.text, .text; functions BS2StartGame: 62 changed instructions, 392/393.
- BS2/BS2Update: BS2SelectUpdateEntries use an inline product-region validator: reverted; changed .rela.data, .rela.text, .text; functions UpdateThread: 830 changed instructions, 923/913.
- keyboard/tiZiString: partialConfirmForKR select trailing letters with a short-circuit leading-letter test: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiZiString: partialConfirmForKR use a final-letter lookup matching the leading-letter helper: reverted; changed .text; functions partialConfirmForKR__Q39textinput8tistring6WithZiFv: 11 changed instructions, 147/147.
- keyboard/tiZiString: complementsCandidates_ use an inline numeric-element search: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiZiString: update put candidate-success processing in a single-attempt block: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiHwKeyboard: updateRepeatKey_ use for-loop dispatch with explicit Tab case: reverted; changed .rela.data, .rela.text, .text; functions updateRepeatKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager: 84 changed instructions, 181/180.
- keyboard/tiHwKeyboard: updateTriggerKey_ use explicit digit and punctuation switch: reverted; changed .rela.data, .rela.text, .text; functions updateTriggerKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager: 241 changed instructions, 409/405.
- keyboard/tiHwKeyboard: updateRepeatKey_ use direct switch arms sharing one navigation payload: reverted; changed .rela.data, .rela.text, .text; functions updateRepeatKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager: 202 changed instructions, 205/180.
- keyboard/tiHwKeyboard: updateTriggerKey_ place shared suppression after the numeric-dot case: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiHwKeyboard: updateRepeatKey_ replace dispatch tree with switch while retaining shared navigation tail: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiZiString: update use a copy-success condition instead of a single-attempt block: reverted; changed .rela.data, .rela.text, .text; functions update__Q39textinput8tistring6WithZiFv: 205 changed instructions, 450/446.
- BS2/BS2Mach: keep idiomatic disk fatal/completion exits instead of an empty-branch single-attempt block: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiZiString: update retain the shared failed-copy exit instead of a synthetic single-attempt loop: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiZiString: document remaining final-letter and candidate-copy branch requirements: retained; allocated bytes, section layout, and resolved relocations identical.
- BS2/BS2Mach: indent the locked-title branch and document remaining compiler paths: retained; allocated bytes, section layout, and resolved relocations identical.
- BS2/BS2Update: document shared region and optional-seat exits required by MWCC: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiInputForm: document the required compatibility-table section and mode-check exit: retained; allocated bytes, section layout, and resolved relocations identical.
- keyboard/tiHwKeyboard: document the shared navigation tail required by MWCC: retained; allocated bytes, section layout, and resolved relocations identical.

## Retained result

- BS2/BS2Update: gotos 35 -> 35. Named both fallback product-area switches with existing enums. Shared product-region paths stay because if/else and an inline validator change UpdateThread bytes. Common selection and optional-seat exits remain idiomatic error paths.
- BS2/BS2Mach: gotos 25 -> 24. Removed the locked-title entry jump with a null-output branch. Region-result jumps, shared fatal exits, interrupt-shared definitions, and repeated 410 check stay. Region restructuring and duplicate-check removal change bytes. Discarded the exact single-attempt disk block because its empty branch reads worse than common exits.
- keyboard/tiHwKeyboard: gotos 27 -> 3. Used a switch and for-loop for repeated-key dispatch, a character switch for numeric input, and a guarded switch for control keys. Kept three navigation jumps to their shared command tail. A fully structured tail adds a branch; duplicated send arms add 25 instructions. Fixed key-input indentation.
- keyboard/tiInputForm: gotos 22 -> 1. Replaced findURL character dispatch with a structured switch. Kept notifyChangeMode's shared mode-check exit and the local .data table pragma. Explicit mode flags and a mutable table without the pragma change code or data. Earlier cleanup-c7 trials already prove the geometry and stripped-function forms; those families were not repeated.
- keyboard/tiZiString: gotos 20 -> 2. Structured dictionary selection, trailing Korean-letter selection, numeric-element scanning, and letter-mode dispatch. Removed the context-reset comma condition. Kept the final-letter match exit, failed-copy destination join, and related buffer view because alternatives change instructions. Discarded the exact single-attempt candidate block as needless loop structure.
- keyboard/tiString: gotos 5 -> 5. Restored the no-Hangul-composer explanation immediately above the MWCC note. Exactly two comment lines; all source behavior and object bytes unchanged.

## Final verification

Every allocated section byte, size, alignment, and resolved relocation in all six units equals the initial built object. Every owned reported code and data section is 100%; all six units remain Matching and fully linked.

- BS2/BS2Update: exact functions 10/10; code 4052/4052; data 10488/10488.
- BS2/BS2Mach: exact functions 29/29; code 16980/16980; data 158528/158528.
- keyboard/tiHwKeyboard: exact functions 10/10; code 4596/4596; data 504/504.
- keyboard/tiInputForm: exact functions 221/221; code 50656/50656; data 3772/3772.
- keyboard/tiZiString: exact functions 29/29; code 5504/5504; data 7680/7680.
- keyboard/tiString: exact functions 42/42; code 5176/5176; data 288/288.

Full 43U build and build/43U/ok passed. Refreshed build/43U/report.json; check_decomp_complete.py returned DECOMPLETE_OK. All 12563 functions are exact and all 1028 units linked. The aggregate fuzzy value remains the baseline 99.999886 despite the all-exact function measures.

GATE PASS: 0 regressions, 0 forbidden additions, 0 readability warnings. Gate output /tmp/cleanup2-w6-gate.txt. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Focused source review and git diff --check passed.

## Source commits

- 514b873f src/BS2/BS2Update.c
- 82c61d70 src/BS2/BS2Mach.c
- dbeee8f0 src/keyboard/tiHwKeyboard.cpp
- 80824034 src/keyboard/tiInputForm.cpp
- e2c90614 src/keyboard/tiZiString.cpp
- aa8f80aa src/keyboard/tiString.cpp
