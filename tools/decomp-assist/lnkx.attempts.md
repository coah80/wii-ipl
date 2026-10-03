# lnkx link attempts

Assigned tree w0929-fix-board, branch agent/w1003/astra-link-xhigh, HEAD 38cea737. Prior u4, lnkm and lnkh logs read in full. Their destructor spelling, definition order, base ordering, inherited metadata, inline/weak binding, constructor, Sample emission and compiler-version trials will not be repeated. LINK scope overrides common.md matching-only text. Existing lnkm and lnkh logs preserved. Baseline DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; pools identical, keyboard 204/204 and audio 0/0.

Prior trials already cover explicit vs implicit destructor, in-class inline definition, definition before overriders and key-function placement. Secondary bases already declare their destructors first. Those hypotheses have negative evidence for both units. New tests focus on the lifetime of compiler vtable metadata and real inherited class emission, without retaining fabricated classes, force-active constructs or foreign unit output. Scratch reproducers are diagnostic only.

## X1: unused real inline derived constructors

A scratch two-base reproducer shows that an unused inline derived constructor plus an inline or implicit derived destructor builds the parent vtable metadata even though no derived-class symbol is emitted. Declaration-only, unused inline destructor-only and a constructor with an external destructor do not. This differs from u4 K18, whose forwarding constructor was non-inline and emitted the foreign table/thunk. No scratch class or artificial trigger was added to source.

Keyboard X1 adds the real pctype::Sample class already present in tiKeyboard.cpp, with its actual forwarding inline constructor and empty inline destructor. A declaration exposes LayoutByNW4R's real constructor signature to that unused inline constructor. No foreign Sample code, data or thunk is emitted. All 141 functions and all code/data remain 100%; pool 204/204. The destructor thunk now comes FIRST, followed by the five ordinary thunks in target order.

Audio X1 includes the real ipl::snd::System class and its actual empty inline constructor. No foreign symbol is emitted; order stays calc then destructor. Later probes below identify the calc override as the important difference. Restored before keyboard link validation.

Keyboard X1 Matching link PASSES: build/43U/ok, full DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, all 141 functions still 100%. Audio restored to baseline for this isolated proof.

## Audio follow-ups

Scratch reproducers distinguish a subclass that inherits calc from one that overrides calc. Only the former moves the parent destructor thunk first. The real System class overrides calc, so importing its constructor cannot reproduce Sample's useful effect. Inline declarations and inline definitions for its real calc do not change that result. These diagnostic classes remain in ignored build scratch only.

A2 defines the real empty SimpleAudioMgr destructor inline with NO_INLINE to keep WithFx calls exact. A3 likewise exposes its real ArcPlayer(&getSoundHeap()) constructor. A4 combines both. All retain 8/8 and 524/524 code, but add foreign weak functions; A4 adds a parent vtable and destructor thunk. None changes the required pair's order. All restored. The first script version had a malformed preprocessor replacement; those compiler failures produced no measurements and were fixed before these recorded results.

A5-A7 move the real parent constructor/destructor definitions into SimpleAudioMgr's class body with NO_INLINE, testing whether parsing them before WithFx's definition changes the metadata timing. Both together, constructor only, and destructor only each retain all eight exact functions but leave calc before destructor and emit extra parent code. All restored.

Both Matching after keyboard fix: SHA1 03a070db1c6ed8bbe21f9470a1c3ef24d02369ad, sizes 3867904/3867904, 9 differing bytes. Offsets: 0x2c6870, 0x2c6871, 0x2c6872, 0x2c6878, 0x2c6879, 0x2c687a, 0x3639f3, 0x363a17, 0x363a8f
Audio still fails the link criterion. Keyboard fixes all its previous 26 differing bytes. Restoring audio Equivalent before the final clean gate.

## Retained result and handoff

Keyboard is now Matching, with all 28,484 code bytes and 18,564 data bytes fully linked. Its 141/141 functions remain instruction-exact. The restored real Sample declarations emit no Sample function, vtable, or thunk in this object. The only retained source/header change is the 11-line TU-guarded declaration addition, plus the configure.py Matching flag. Audio remains Equivalent and 8/8 exact; the LINK task is incomplete for that unit.

Every one of the 149 explicit ctxdiff.py checks has identical instruction counts and diffs 0. The final full non-quick gate independently checks all 149 functions again. Both pools are identical and every owned section scores 100%. Regenerating the live report changes only the keyboard unit's link measures compared with the initial report; all other unit reports are identical. No regression, forbidden addition, or readability warning. The final 43U build, build/43U/ok and DOL checksum all pass. decomp_status.py ran. Global check_decomp_complete.py remains DECOMPLETE_FAIL because the overall project is unfinished.

Scratch programs and detailed raw checks remain under ignored build/lnkx. No other worktree, source unit, baseline, or orchestration tool was edited. No push, PR, merge, rebase, or delegation. Intermediate commentary was emitted, so the requested zero-commentary audit is not met.

Final full gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiPcKeyboard] pool: IDENTICAL
[src/keyboard/tiPcKeyboard] objdiff: code 28484/28484 data 18564/18564 functions 141/141 fuzzy 100.0000 linked code 28484
[src/keyboard/tiPcKeyboard] instruction-exact functions: 141/141
[src/keyboard/tiPcKeyboard]   section .bss size 16 match 100.0
[src/keyboard/tiPcKeyboard]   section .ctors size 4 match 100.0
[src/keyboard/tiPcKeyboard]   section .data size 12576 match 100.0
[src/keyboard/tiPcKeyboard]   section .rodata size 5816 match 100.0
[src/keyboard/tiPcKeyboard]   section .sbss size 8 match 100.0
[src/keyboard/tiPcKeyboard]   section .sdata size 136 match 100.0
[src/keyboard/tiPcKeyboard]   section .sdata2 size 8 match 100.0
[src/keyboard/tiPcKeyboard]   section .text size 28484 match 100.0
[src/keyboard/tiPcKeyboard] baseline: code 28484/28484 data 18564 functions 141 fuzzy 100.0000
[libs/EGG/src/core/eggAudioExpMgr] pool: IDENTICAL
[libs/EGG/src/core/eggAudioExpMgr] objdiff: code 524/524 data 120/120 functions 8/8 fuzzy 100.0000 linked code 0
[libs/EGG/src/core/eggAudioExpMgr] instruction-exact functions: 8/8
[libs/EGG/src/core/eggAudioExpMgr]   section .data size 120 match 100.0
[libs/EGG/src/core/eggAudioExpMgr]   section .text size 524 match 100.0
[libs/EGG/src/core/eggAudioExpMgr] baseline: code 524/524 data 120 functions 8 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.38495 -> 92.38495
global fuzzy_match_percent: 99.73445 -> 99.73445
global complete_code_percent: 74.91312 -> 75.86412
global matched_data_percent: 99.78196 -> 99.78196
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```
