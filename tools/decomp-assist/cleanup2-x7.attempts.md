# cleanup2-x7 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d5`, branch `agent/w1009/cleanup2-x7`, baseline `c3dd1c08c04a38975b63dded77a7aef6fce385f3`.

Read cleanup-common.md fully, including wave-2 guidance. Applied unslop and writing-for-agents to this handoff. Initial full 43U build passed; fresh report and completion checker returned DECOMPLETE_OK. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`. All 1028 units and 12563 functions match and link completely.

Scope is all C/C++ and headers in libs/NW4R and libs/EGG. Hand-written assembly stays untouched. Audit and trials proceed largest-first. Each trial compares all allocated section sizes and bytes and normalized relocations with fresh baseline objects. Any changed byte rejects the trial.

Prior cleanup-c4 tested AxManager pragma removal, pointer iteration, voice local, and loop scope. Those failed because default IRO hoists the voice address and removes one instruction. Do not repeat those trials without a different source hypothesis. Prior fz2 confirms Window assertion colors have distinct constant storage and GetFrameMaterial uses its named quartet.

## Trials

- window-direct-constant-colors: REJECT, [{"unit": "libs/NW4R/src/lyt/lyt_window", "sections": [".rela.ctors", ".rela.text", ".text"], "functions": ["GetFrameMaterial__Q34nw4r3lyt6WindowCFUl: 31 diffs, 38/41 instructions"]}]. Restored.
- window-declaration-volatile-colors: REJECT, [{"unit": "libs/NW4R/src/lyt/lyt_window", "sections": [".rela.ctors", ".rela.text", ".sbss2", ".sdata2", ".text"], "functions": ["GetFrameMaterial__Q34nw4r3lyt6WindowCFUl: 31 diffs, 39/41 instructions"]}]. Restored.
- archivefontbase-remove-commented-implementations: KEEP, all allocated sections and normalized relocations identical.
- window-format-and-document-required-byte-loads: KEEP, all allocated sections and normalized relocations identical.
- textbox-loop-breaks: KEEP, all allocated sections and normalized relocations identical.
- axmanager-default-iro-positive-init-guard: REJECT, [{"unit": "libs/NW4R/src/snd/snd_AxManager", "sections": [".rela.text", ".text"], "functions": ["Init__Q44nw4r3snd6detail9AxManagerFv: 52 diffs, 62/63 instructions"]}]. Restored.
- axmanager-default-iro-do-while-init: REJECT, [{"unit": "libs/NW4R/src/snd/snd_AxManager", "sections": [".rela.text", ".text"], "functions": ["Init__Q44nw4r3snd6detail9AxManagerFv: 52 diffs, 62/63 instructions"]}]. Restored.
- archivefont-remove-character-size-reference: REJECT, [{"unit": "libs/NW4R/src/ut/ut_ArchiveFont", "sections": [".text"], "functions": ["GetRequireBufferSize__Q34nw4r2ut11ArchiveFontFPCvPCc: 7 diffs, 256/256 instructions"]}]. Restored.
- archivefont-stream-reader-direct-member: REJECT, [{"unit": "libs/NW4R/src/ut/ut_ArchiveFont", "sections": [".text"], "functions": ["StreamingConstruct__Q34nw4r2ut11ArchiveFontFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPCvUl: 3 diffs, 142/142 instructions"]}]. Restored.
- archivefont-remove-redundant-map-count-copy: REJECT, [{"unit": "libs/NW4R/src/ut/ut_ArchiveFont", "sections": [".text"], "functions": ["GetRequireBufferSize__Q34nw4r2ut11ArchiveFontFPCvPCc: 6 diffs, 256/256 instructions"]}]. Restored.
- archivefont-typed-group-name-cursor: REJECT, [{"unit": "libs/NW4R/src/ut/ut_ArchiveFont", "sections": [".text"], "functions": ["GetRequireBufferSize__Q34nw4r2ut11ArchiveFontFPCvPCc: 3 diffs, 256/256 instructions"]}]. Restored.
- archivefont-block-buffer-max: KEEP, all allocated sections and normalized relocations identical.
- console-structured-draw-exits: KEEP, all allocated sections and normalized relocations identical.
- archivefont-max-with-direct-map-count: REJECT, [{"unit": "libs/NW4R/src/ut/ut_ArchiveFont", "sections": [".text"], "functions": ["GetRequireBufferSize__Q34nw4r2ut11ArchiveFontFPCvPCc: 6 diffs, 256/256 instructions"]}]. Restored.
- archivefont-indexed-group-name: REJECT, [{"unit": "libs/NW4R/src/ut/ut_ArchiveFont", "sections": [".text"], "functions": ["GetRequireBufferSize__Q34nw4r2ut11ArchiveFontFPCvPCc: 44 diffs, 256/256 instructions"]}]. Restored.
- console-remove-redundant-function-scope: REJECT, trial script removed the function closing brace. MWCC error 10121 at Console_DrawDirect. Restored, then corrected the rewrite below.
- arcplayer-remove-debug-symbol-pragma: KEEP, all allocated sections and normalized relocations identical.
- heap-remove-no-op-statements: REJECT, [{"unit": "libs/EGG/src/core/eggHeap", "sections": [".rela.text", ".text"], "functions": ["__dt__Q23EGG4HeapFv: 11 diffs, 36/35 instructions"]}]. Restored.
- heap-remove-stripped-empty-allocation-check: KEEP, all allocated sections and normalized relocations identical.
- archivefont-name-CWDH-CMAP-fields-and-layout-helpers: KEEP, all allocated sections and normalized relocations identical.
- console-remove-redundant-function-scope-corrected: KEEP, all allocated sections and normalized relocations identical.
- heap-delete-never-inline-definition: REJECT, [{"unit": "libs/EGG/src/core/eggHeap", "sections": [".rela.text", ".text"], "functions": ["__dt__Q23EGG4HeapFv: 11 diffs, 36/35 instructions"]}]. Restored.
- heap-delete-never-inline-declaration: REJECT, [{"unit": "libs/EGG/src/core/eggHeap", "sections": [".rela.text", ".text"], "functions": ["__dt__Q23EGG4HeapFv: 11 diffs, 36/35 instructions"]}]. Restored.
- heap-four-no-op-statements: REJECT, [{"unit": "libs/EGG/src/core/eggHeap", "sections": [".rela.text", ".text"], "functions": ["__dt__Q23EGG4HeapFv: 11 diffs, 36/35 instructions"]}]. Restored.
- heap-document-required-delete-boundary: KEEP, all allocated sections and normalized relocations identical.
- frameheap-remove-unused-parameter-pragma: KEEP, all allocated sections and normalized relocations identical.
- archivefontbase-remove-speculative-boundary-comments: KEEP, all allocated sections and normalized relocations identical.
- textbox-direct-font-resource-result: KEEP, all allocated sections and normalized relocations identical.
- archivefont-typed-flag-word-indexing: REJECT, [{"unit": "libs/NW4R/src/ut/ut_ArchiveFont", "sections": [".rela.text", ".text"], "functions": ["GetRequireBufferSize__Q34nw4r2ut11ArchiveFontFPCvPCc: 207 diffs, 246/256 instructions"]}]. Restored.
- archivefont-remove-unused-sheet-data-pointer: KEEP, all allocated sections and normalized relocations identical.
- archivefont-const-resource-cast: KEEP, all allocated sections and normalized relocations identical.
- heap-alloc-direct-current-heap-return: KEEP, all allocated sections and normalized relocations identical.
- fontresources-align-renamed-field-columns: KEEP, all allocated sections and normalized relocations identical.
- arcplayer-separate-includes-from-namespace: KEEP, all allocated sections and normalized relocations identical.

## Retained cleanup

- `lyt_textBox.cpp`: both loop exits use break, the end_draw label is gone, and the unused SetResource result is gone. The corresponding SS source also exits the line loop with break.
- `db_console.cpp`: all five gotos become an early return or loop breaks. Removed the common label, trailing return, redundant scope, and speculative label comment.
- `ut_ArchiveFont.cpp`: Max<u32> replaces the size-reference alias and branch; removed the unused sheet-data pointer and assignment. CWDH/CMAP names replace offsets and unknown sizes. Named the header cursor and used a const resource cast. Widened CMAP count, header-base iteration, and byte-addressed flags remain because typed/direct alternatives change instructions. StreamingConstruct retains the same reader-reference idiom as the News Channel source.
- `ut_ArchiveFontBase.cpp`: removed two commented-out implementations and speculative IncludeName examples; uses named CWDH/CMAP counts.
- `fontResources.h`: GlyphGroups fields at 0x0A and 0x0C are cwdhCount and cmapCount. News Channel FontGlyphGroups names these numCWDH and numCMAP at the same offsets.
- `ArchiveFontBase.h`: layout helper names and parameters identify CWDH/CMAP instead of 0A/0C.
- `lyt_window.cpp`: formatted the assertion macro and documented the required byte loads. Direct constants change 31 instructions; declaration-level volatile changes section placement too, so the four casts remain.
- `eggAudioArcPlayerMgr.cpp`: removed the debug-symbol pragma.
- `eggFrmHeap.cpp`: an unnamed free parameter replaces pragma unused.
- `eggHeap.cpp`: removed the empty allocation-failure check and redundant result local. Five no-op statements remain in operator delete. Removing even one, or replacing them with never_inline, makes Heap's destructor inline the delete path and changes 11 instructions. Replaced the vague comment with the measured compiler requirement.
- `snd_AxManager.cpp`: unchanged. Positive initialization guard and do/while at default IRO still change 52 instructions and remove one instruction. The SS reference retains the same IRO 0 pragma.
- `eggHeap.h`: the two placeholder inline method names remain because their callers are in src/system/iplSystem.cpp, outside this assignment. No aliases or outside-scope edits were added.

## References

- https://github.com/zeldaret/ss/blob/main/src/nw4r/lyt/lyt_textBox.cpp
- https://github.com/zeldaret/ss/blob/main/src/nw4r/snd/snd_AxManager.cpp
- https://github.com/hotlandsoftware/wii-news-channel/blob/main/include/nw4r/ut/ut_ArchiveFontBase.h
- https://github.com/hotlandsoftware/wii-news-channel/blob/main/src/nw4r/ut/ut_ArchiveFont.cpp
- Compared ogws and mkw Heap sources as additional structure references. Their heap implementations differ from this menu version, so no code was copied.

## Final verification

Final gate ran once with --quick over all 96 NW4R and 16 EGG units, including header consumers and reverted AxManager trials. Full build passed; 1324/1324 owned functions remain 100% in objdiff and every owned section is 100%. The gate raw-name count is 1323/1324 because snd_Channel uses __arraydtor$3415 where retail uses __arraydtor$3264, already true in the initial baseline. Comparing those corresponding helpers gives identical instructions, so all 1324 owned functions are instruction-exact after that local-name normalization. Pool checks reproduce the initial baseline for every edited source unit. TextBox and Window each have two preexisting duplicate assertion strings in their raw object pools. These bytes are identical to the initial baseline; the linked DOL and reported code/data remain exact. All other edited pools are identical to retail objects. All 112 owned objects have the same allocated sections and normalized relocations as the initial full-build baseline.

Fresh report and build/43U/ok passed. Completion checker returned DECOMPLETE_OK. All 1028 global unit measures remain unchanged from the initial report. Focused ctxdiff checks for TextBox line measurement, console drawing, ArchiveFont buffer sizing, Window frame material, Heap destruction, and AxManager initialization have equal instruction counts and diffs 0.

Gate output `/tmp/cleanup2-x7-final-gate.txt`:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Source commits

- `libs/NW4R/include/nw4r/ut/fontResources.h`: `3bfd2cf8db8a8bc9703bb8f94149ce5369967622`.
- `libs/NW4R/include/nw4r/ut/ArchiveFontBase.h`: `aa60f547f3c4683f34289d8677f63ce549fbe8c6`.
- `libs/NW4R/src/ut/ut_ArchiveFontBase.cpp`: `c2cc2119930a875833544769595aa22dcfa2593e`.
- `libs/NW4R/src/lyt/lyt_window.cpp`: `bc781718f47745f55deb40ae721aa8daed2cd490`.
- `libs/NW4R/src/lyt/lyt_textBox.cpp`: `3d747fad0e8353546bd6967d9bb4de778bd0d53e`.
- `libs/NW4R/src/ut/ut_ArchiveFont.cpp`: `ba5022222cc88cf402cee7abbf70da01e273cf61`.
- `libs/NW4R/src/db/db_console.cpp`: `9dc1c1ddb68ba7d4afc0dc000ed5feebedc5e258`.
- `libs/EGG/src/core/eggAudioArcPlayerMgr.cpp`: `d673df55690308d78359a6c093ae558b65ef157d`.
- `libs/EGG/src/core/eggHeap.cpp`: `a35ca57371efe83407bd15fe997dd9d78dfb4990`.
- `libs/EGG/src/core/eggFrmHeap.cpp`: `b34119321091cb3d5e9b1eb8e57955e220cb9702`.

Each cleaned file has its own commit. Source scope is restricted to NW4R/EGG; assembly and other worktrees are unchanged. All experiments that changed bytes were restored.
