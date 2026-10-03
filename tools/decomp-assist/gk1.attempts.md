# gk1 iplSetting max round

Owned unit: src/scene/setting/iplSetting. Data naming and extents first; convertRevIP then scanAP.
Baseline HEAD 20ba34a80f9d0a09c4a8fad51352f0dd97d84be0; fetched origin/main 20ba34a80f9d0a09c4a8fad51352f0dd97d84be0.
Initial worktree has an unrelated untracked perm4.attempts.md; left untouched.
Prior-art index has no iplSetting, scanAP or convertRevIP entry.
Baseline report measures {"fuzzy_match_percent": 99.85767, "total_code": "37884", "matched_code": "36504", "matched_code_percent": 96.35731, "total_data": "5696", "matched_data": "1680", "matched_data_percent": 29.49438, "total_functions": 112, "matched_functions": 110, "matched_functions_percent": 98.21429, "total_units": 1}.

## Data audit

POOL IDENTICAL, 108/108 strings, identical offsets. No missing string or table literals.
All named objects already pair: scAnmTable, sSettingAPButtonNames, sSettingArrowNames, sSettingAPTextNames, sSettingAPNumberNames, sSettingAPPaneNames, sSettingAPAnimations, m_AOSSConfig, m_RakuConfig, mem1Buffer_, mem2Buffer_, browserScrollDirection, scNumber, scNumber2, APEvent/Setting vtables. Each has identical symbol extent and section-relative address in both ELFs. No permitted lbl-to-real-name rename remains.
.data raw nonrelocated bytes are identical, 4016/4016. The only relocation differences are the scanAP switch table at .data+0xc7c, target @27409/source @27430, size 0x28. Its entries at 0xc7c/0xc98/0xc9c/0xca0 point into scanAP at target offsets 1068/872/940/956 vs source 1044/864/924/940. Therefore the 4016-byte data gap is caused by scanAP code offsets, not missing data or names. No symbols changed.
.rodata is byte-identical; renamed compiler-generated @188xx references point to identical version-suffix literals. .sdata and .sdata2 have only final 4-byte unowned alignment absent in the source ELF. Weak extra vtables are ignored.

## Function baseline

Fetched origin/main before inspecting functions; its iplSetting.cpp and header are identical to HEAD. Current report has convertRevIP 98.69863 and scanAP 95.39338; no newer exact match exists in origin/main.
convertRevIP has 73/73 instructions and a 0x40 frame. Structural instruction shapes agree; 16 register/allocation and initialization-order differences remain.
scanAP has 266/272 instructions and a 0x10 frame. Three isPlaying negations are branch-folded in ours, while target materializes the bool with addi/cntlzw/rlwinm. Cases 7 and 9 also differ in load/store scheduling. Fix structure before allocation.

convertRevIP attempt 1: leading-local declaration order search, after confirming identical structural instruction shapes.
declaration block:
              char ascii[20];
              int count = 0;
              int index;
start (0, 16)
best (0, 16) after 6 builds; source restored; best order was:
            char ascii[20];
            int count = 0;
            int index;


convertRevIP | output-before-component-start | {"insns": [73, 73], "structural": 0, "diffs": 16, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | index-initialized-before-component | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | leading-component-declaration | {"insns": [73, 73], "structural": 0, "diffs": 16, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | leading-output-declaration | {"insns": [73, 73], "structural": 0, "diffs": 16, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | count-after-conversion | {"insns": [73, 73], "structural": 2, "diffs": 21, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

Named data object pairing proof, all extents retained:
- scAnmTable__Q23ipl5scene .rodata+0x0 size 0xe8; common code users create__Q33ipl5scene7SettingFv; pointers none.
- scNumber__Q23ipl5scene .rodata+0x258 size 0x14; common code users none; pointers none.
- scNumber2__Q23ipl5scene .rodata+0x26c size 0x14; common code users none; pointers none.
- m_AOSSConfig__Q23ipl5scene .bss+0x0 size 0x158; common code users AOSSProcess__Q33ipl5scene7SettingFv; pointers none.
- m_RakuConfig__Q23ipl5scene .bss+0x158 size 0x70; common code users RakuProcess__Q33ipl5scene7SettingFv; pointers none.
- sSettingAPButtonNames__Q23ipl5scene .data+0x0 size 0x10; common code users get_ap_no__Q33ipl5scene7SettingFPCc; pointers @16789, @16790, @16791, @16792.
- sSettingAPTextNames__Q23ipl5scene .data+0x10 size 0x18; common code users setAPDraw__Q33ipl5scene7SettingFv; pointers @16795, @16796, @16797, @16798, @16799.
- sSettingAPNumberNames__Q23ipl5scene .data+0x28 size 0x18; common code users initScroll__Q33ipl5scene7SettingFv; pointers @16801, @16802, @16803, @16804, @16805.
- sSettingAPPaneNames__Q23ipl5scene .data+0x90 size 0x68; common code users none; pointers @16807, @16808, @16809, @16810, @16811.
- sSettingAPAnimations__Q23ipl5scene .data+0x284 size 0x4c; common code users none; pointers @16833, @16834, @16835, @16836, @16837.
- __vt__Q33ipl5scene7APEvent .data+0xe9c size 0x18; common code users create__Q33ipl5scene7SettingFv; pointers onEvent__Q33ipl5scene7APEventFUlUlPv, setManager__Q23gui12EventHandlerFPQ23gui7Manager, setLatestEventCtrlNo__Q23gui12EventHandlerFi, getLatestEventCtrlNo__Q23gui12EventHandlerFv.
- __vt__Q33ipl5scene7Setting .data+0xeb4 size 0x68; common code users __ct__Q33ipl5scene7SettingFPQ23EGG4Heapi, __dt__Q33ipl5scene7SettingFv; pointers __dt__Q33ipl5scene7SettingFv, getParent__Q33ipl5scene4BaseFv, getChild__Q33ipl5scene4BaseFv, getNext__Q33ipl5scene4BaseFv, getPrev__Q33ipl5scene4BaseFv.
- sSettingArrowNames__Q23ipl5scene .sdata+0x28 size 0x8; common code users create__Q33ipl5scene7SettingFv, get_arw_no__Q33ipl5scene7SettingFPCc, initScroll__Q33ipl5scene7SettingFv; pointers @16793, @16794.
- mem1Buffer___Q33ipl5scene7Setting .sbss+0x0 size 0x4; common code users __dt__Q33ipl5scene7SettingFv, createBrowser__Q33ipl5scene7SettingFv; pointers none.
- mem2Buffer___Q33ipl5scene7Setting .sbss+0x4 size 0x4; common code users __dt__Q33ipl5scene7SettingFv, createBrowser__Q33ipl5scene7SettingFv; pointers none.
- browserScrollDirection__Q23ipl5scene .sbss+0x8 size 0x4; common code users draw__Q33ipl5scene7SettingFv; pointers none.

Before scanAP experiments, fetched origin/main again; owned source equals initial source: True.

scanAP | isPlaying-equals-false | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | isPlaying-equals-FALSE | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | isPlaying-not-true | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | isPlaying-materialized-int | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | isPlaying-materialized-bool | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-scan | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | leading-counter-and-pointer-declarations | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | loop-index-declared-at-initialization | {"insns": [73, 73], "structural": 0, "diffs": 20, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | unsigned-parsed-count | {"insns": [73, 73], "structural": 1, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | byte-conversion-buffer | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | signed-char-conversion-buffer | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | count-before-output-advance | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | output-advance-before-count | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | parse-value-declared-before-loop | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | loop-char-declared-before-loop | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best-convert-round2 | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-playing-BOOL | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-playing-ternary-bool | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-playing-ternary-BOOL | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-playing-explicit-result | {"insns": [266, 272], "structural": 54, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-playing-explicit-BOOL | {"insns": [266, 272], "structural": 54, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-playing-early-return | {"insns": [266, 272], "structural": 54, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-playing-reverse-compare | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-playing-negated-difference | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-scoped-playing | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | static-inline-playing-helper | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | static-BOOL-playing-helper | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | static-bool-complete-helper | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-free-helper | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP tested existing Object::isPlaying(int) const as a unit-scoped inline definition. All List_GetNth relocations in both objects use const List*; this does not distinguish the original inline accessor. That existing method remained an out-of-line call and gave 257/272 instructions, so restored its original declaration.

scanAP | inline-existing-const-Object-isPlaying | {"insns": [257, 272], "structural": 36, "diffs": 165, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-return-compare-one | {"insns": [275, 272], "structural": 56, "diffs": 158, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-return-compare-TRUE | {"insns": [275, 272], "structural": 56, "diffs": 158, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-return-less-than-one | {"insns": [275, 272], "structural": 56, "diffs": 158, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-return-complement-low-bit | {"insns": [278, 272], "structural": 59, "diffs": 163, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-return-xor-true | {"insns": [278, 272], "structural": 59, "diffs": 163, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-return-compare-one | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-return-complement-low-bit | {"insns": [278, 272], "structural": 59, "diffs": 163, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-predicate-combinations | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | inline-clamp-component-helper | {"insns": [67, 73], "structural": 11, "diffs": 50, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | inline-shift-component-helper | {"insns": [69, 73], "structural": 18, "diffs": 50, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | inline-clamp-and-shift-helpers | {"insns": [63, 73], "structural": 23, "diffs": 51, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | clamp-using-min-ternary | {"insns": [75, 73], "structural": 11, "diffs": 52, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | decimal-value-signed-view | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best-component-helpers | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | playing-explicit-inline-in-class | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | playing-outside-class-inline | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | playing-outside-class-BOOL | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | playing-byte-return | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-inline-boundaries | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | wide-playing-low-bit-is-zero | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | wide-playing-bit-inverted | {"insns": [275, 272], "structural": 56, "diffs": 158, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | wide-playing-unsigned-zero | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | wide-playing-bool-cast | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | wide-playing-equal-boolean-false | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | wide-playing-zero-ternary | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-integer-local-return | {"insns": [266, 272], "structural": 54, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-bool-cast-after-int | {"insns": [266, 272], "structural": 54, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-playing-shapes | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | readonly-output-parameter | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | readonly-address-parameter | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | array-output-parameter | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | array-address-parameter | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | output-cursor-before-memset | {"insns": [73, 73], "structural": 2, "diffs": 19, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | output-cursor-before-count | {"insns": [73, 73], "structural": 2, "diffs": 26, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | output-cursor-before-buffer | {"insns": [73, 73], "structural": 2, "diffs": 26, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | scan-counters-at-function-entry | {"insns": [73, 73], "structural": 4, "diffs": 35, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | component-start-at-function-entry | {"insns": [73, 73], "structural": 2, "diffs": 35, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | conversion-address-local-view | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | loop-count-negative-form | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | next-output-pointer-assignment | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | read-only-existing-address-view | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best-lifetimes | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | cursor-advanced-with-first-store | {"insns": [73, 73], "structural": 3, "diffs": 22, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | count-postincrement-in-first-test | {"insns": [73, 73], "structural": 4, "diffs": 22, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | count-incremented-in-both-branches | {"insns": [74, 73], "structural": 10, "diffs": 49, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | cursor-incremented-in-both-branches | {"insns": [74, 73], "structural": 8, "diffs": 49, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | index-and-component-joint-init | {"insns": [73, 73], "structural": 0, "diffs": 16, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | loop-index-and-start-joint-init | {"insns": [73, 73], "structural": 0, "diffs": 16, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | parse-array-index-address | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | write-byte-by-cursor-subscript | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | loop-with-explicit-bottom-step | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | typed-zero-byte | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | ascii-buffer-initialized-at-definition | {"insns": [75, 73], "structural": 12, "diffs": 69, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best-flow | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-nonpositive | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-less-than-TRUE | {"insns": [275, 272], "structural": 56, "diffs": 158, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-byte-mask-zero | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-full-mask-zero | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-left-shift-zero | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-unsigned-mask-zero | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-boolean-cast-false | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-zero-first-comparison | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-negative-zero-comparison | {"insns": [272, 272], "structural": 12, "diffs": 15, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-test-double-negation | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-mask-TRUE-zero | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-playing-zero-conditional | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-nonpositive | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-less-than-TRUE | {"insns": [275, 272], "structural": 56, "diffs": 158, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-byte-mask-zero | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-full-mask-zero | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-left-shift-zero | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-unsigned-mask-zero | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-boolean-cast-false | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-zero-first-comparison | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-negative-zero-comparison | {"insns": [272, 272], "structural": 12, "diffs": 15, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-test-double-negation | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-mask-TRUE-zero | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-playing-zero-conditional | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-expression-search | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | late-bool-playing-helper | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | late-BOOL-playing-helper | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | late-FrameController-playing-definition | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-late-helpers | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | inspect-wide-playing-nonpositive | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-before-output-all | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-before-output-read-only | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-before-output-decimal-only | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-before-output-scan-only | {"insns": [73, 73], "structural": 0, "diffs": 20, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-after-output-all | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-after-output-read-only | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-after-output-decimal-only | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-after-output-scan-only | {"insns": [73, 73], "structural": 0, "diffs": 20, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-after-index-all | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-after-index-read-only | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-after-index-decimal-only | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-after-index-scan-only | {"insns": [73, 73], "structural": 0, "diffs": 20, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-before-memset-all | {"insns": [71, 73], "structural": 12, "diffs": 63, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-before-memset-read-only | {"insns": [71, 73], "structural": 12, "diffs": 63, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-before-memset-decimal-only | {"insns": [71, 73], "structural": 12, "diffs": 63, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | explicit-buffer-pointer-before-memset-scan-only | {"insns": [73, 73], "structural": 5, "diffs": 27, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best-explicit-buffer-pointer | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-local-playing <= 0 | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-local-playing == 0 | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-local-!playing | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-accumulate-|= | {"insns": [272, 272], "structural": 6, "diffs": 9, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | int-accumulate-+= | {"insns": [272, 272], "structural": 6, "diffs": 9, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-local-playing <= 0 | {"insns": [272, 272], "structural": 9, "diffs": 12, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-local-playing == 0 | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-local-!playing | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-accumulate-|= | {"insns": [272, 272], "structural": 6, "diffs": 9, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-accumulate-+= | {"insns": [272, 272], "structural": 6, "diffs": 9, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-local-playing <= 0 | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-local-playing == 0 | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-local-!playing | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-accumulate-|= | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-accumulate-+= | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-local-status | {"insns": [272, 272], "structural": 6, "diffs": 9, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-status-switch-zero | {"insns": [275, 272], "structural": 54, "diffs": 157, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | bool-status-switch-one | {"insns": [275, 272], "structural": 56, "diffs": 158, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-status-switch-zero | {"insns": [275, 272], "structural": 54, "diffs": 157, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | BOOL-status-switch-one | {"insns": [275, 272], "structural": 56, "diffs": 158, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-status-switch | {"insns": [266, 272], "structural": 53, "diffs": 160, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | capture-index-in-both-remaining-cases | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | capture-index-only-in-case7 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-state-scheduling | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-unsigned-index | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-narrow-index-local | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-explicit-index-narrowing | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-unsigned-argument-view | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-readonly-index-local | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-animator-local | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-readonly-animator-local | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-layout-local-after-index | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-playing-declaration-before-index | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-case9-scheduling | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-index-const-reference | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-index-reference | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-index-const-pointer | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-const-setting-view | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-layout-reference | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-readonly-case9-views | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | lookup-index-first-case9 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | lookup-index-first-all-cases | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | lookup-layout-first-case9 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | lookup-layout-first-all-cases | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-inline-lookup | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-sdk-index | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-sdk-playing | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-sdk-index-and-playing | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-initialized-playing-after-index | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | common-playing-mask | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-add-result | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-zero-integer-initializer | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-condition-equals-FALSE | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-case9-final-forms | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | sdk-count-int-index-int-start-s32 | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | sdk-count-int-index-s32-start-int | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | sdk-count-int-index-s32-start-s32 | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | sdk-count-s32-index-int-start-int | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | sdk-count-s32-index-int-start-s32 | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | sdk-count-s32-index-s32-start-int | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | sdk-count-s32-index-s32-start-s32 | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | moving-output-parameter | {"insns": [73, 73], "structural": 0, "diffs": 24, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | moving-parameter-with-base-before-calls | {"insns": [73, 73], "structural": 2, "diffs": 29, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | reuse-address-parameter-for-converted-text | {"insns": [71, 73], "structural": 9, "diffs": 56, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | unsigned-int-value-type | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best-parameter-role-types | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-readonly-layout-query | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-readonly-layout-first | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | case9-const-reference-layout-query | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-const-layout-lookup | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | leading-all-parser-locals | {"insns": [73, 73], "structural": 0, "diffs": 14, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

## Structural result

Integer animation status accumulation preserves the target addi/cntlzw/rlwinm normalization without masks, shifts, volatile, assembly, or unused values. Capturing the animation index before the busy flag store in state 7 restores its target loads. scanAP reaches 272/272 instructions, leaving only the four load/scheduling differences in state 9; all scanAP switch-table relocations now have the correct offsets, making all 5696/5696 data bytes match. The accumulator representation is inferred from the compilation experiment.
convertRevIP initialization order reduces the register-only diff from 16 to 14 while preserving 73/73 instructions and the 0x40 frame. Neither function is claimed exact yet.
Both target extents meet their next function exactly: convertRevIP 0x813f5e1c+0x124=adjustSecA 0x813f5f40; scanAP 0x813f6858+0x440=initScroll 0x813f6c98. No extents changed.

convertRevIP | full-local declaration permutation search |
declaration block:
              char ascii[20];
              int count = 0;
              int index;
              int componentStart;
              u8* output;
              u32 value;
              u8 character;
start (0, 14)
improved (0, 8)
best (0, 8) after 60 builds; kept in source:
            char ascii[20];
            u8* output;
            int index;
            int componentStart;
            int count = 0;
            u32 value;
            u8 character;


convertRevIP | all-parser-declaration-search-result | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best-after-all-declarations | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | sdk-field-unk_0x918-s32 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | sdk-field-unk_0x918-u32 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | sdk-field-unk_0xB9C-s32 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | sdk-field-unk_0xB9C-u32 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-field-types | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | existing-character-clears-delimiter | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | character-assignment-clears-delimiter | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | existing-parsed-value-clears-delimiter | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | typed-null-literal | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | byte-null-cast | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | character-local-loop-scope | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | decimal-value-local-delimiter-scope | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | named-null-terminator-before-output | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | named-null-terminator-after-index | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | named-null-terminator-before-loop | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best-null-character-lifetimes | {"insns": [73, 73], "structural": 0, "diffs": 8, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | first-component-indexed-by-count | {"insns": [73, 73], "structural": 0, "diffs": 0, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

convertRevIP | restore-best-count-derived-cursor | {"insns": [73, 73], "structural": 0, "diffs": 0, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | single-integer-animation-status | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-getAnim-index-u16 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-getAnim-index-unsigned int | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-getAnim-index-u32 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | scoped-getAnim-index-s32 | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

scanAP | restore-best-lookup-argument-type | {"insns": [272, 272], "structural": 3, "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)"}

## Exact convertRevIP

The target output cursor is a compiler-generated induction variable, not an explicit source pointer. Using destination[count] for the first-component store lets MWCC perform its own strength reduction. Combined with the logged local order and index-before-componentStart initialization, this gives 73/73 instructions, ctxdiff diffs 0, objdiff 100.0%, matched code 36504 -> 36796, exact functions 110 -> 111. The store is equivalent because this branch executes only when count == 0. No manual cursor, assembly, uninitialized read, symbol change, or artificial data is used.
scanAP uses one BOOL status initialized FALSE and ORs the current animation query in states 6/7/9; state 7 captures the animation index before setting the busy flag. Every data section matches 100%; state 9 still has four load/operand scheduling differences. All experimental shared-header edits were restored.

## Plateau audit

{'convertRevIP': 83, 'scanAP': 123} distinct compiled source trials, plus 6-build initial and 60-build full declaration searches. Only scanAP remains open; more than three distinct successful trials are logged. Its remaining four differences are the state-9 animation-index/layout-pointer load order and the two subsequent argument instructions. None change switch destinations. No hard-case function is left untried.

## Quick gate before commit

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 36796/37884 data 5696/5696 functions 111/112 fuzzy 99.9771 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 110/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 100.0
[src/scene/setting/iplSetting]   section .rodata size 640 match 100.0
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 99.97709
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 99.20221
[src/scene/setting/iplSetting] baseline: code 36504/37884 data 1680 functions 110 fuzzy 99.8577
regressions vs baseline: 0
global matched_code_percent: 91.53532 -> 91.54507
global fuzzy_match_percent: 99.69871 -> 99.70022
global complete_code_percent: 74.74593 -> 74.74593
global matched_data_percent: 99.55890 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Instruction-exact baseline clarification

Independently rebuilt the initial source in this same worktree, then restored and rebuilt the committed candidate. The baseline has 109/112 raw instruction-exact functions, despite objdiff reporting 110/112. Candidate has 110/112 raw instruction-exact functions and 111/112 in objdiff. The pre-existing discrepancy is not introduced by this diff. Baseline raw nonexact list: convertRevIP__Q33ipl5scene7SettingFPUcPCc, scanAP__Q33ipl5scene7SettingFv, setUpdate_NoUpdateDialog___Q33ipl5scene7SettingFv.

The pre-existing raw-count discrepancy is a gate-tool normalization bug: odiff.dis treats operand 0 of blt cr1 as an immediate branch target. That operand is the CR register, while operand 1 is the target. Therefore source/target section offsets enter the comparison. setUpdate_NoUpdateDialog_ has identical 120-byte instruction bytes and correct last-operand normalization gives structural 0, exact 0; objdiff is correctly 100%. Gate still prints 110/112 after versus 109/112 before; actual instruction matches are 111/112 after and 110/112 before. No gate or helper was edited.

## Final clean full gate

Command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/setting/iplSetting (no --quick). Exit status 0.

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 36796/37884 data 5696/5696 functions 111/112 fuzzy 99.9771 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 110/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 100.0
[src/scene/setting/iplSetting]   section .rodata size 640 match 100.0
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 99.97709
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 99.20221
[src/scene/setting/iplSetting] baseline: code 36504/37884 data 1680 functions 110 fuzzy 99.8577
regressions vs baseline: 0
global matched_code_percent: 91.53532 -> 91.54507
global fuzzy_match_percent: 99.69871 -> 99.70022
global complete_code_percent: 74.74593 -> 74.74593
global matched_data_percent: 99.55890 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

After the full gate, regenerated the live report. pool_diff: IDENTICAL, 108/108. convertRevIP: objdiff 100.0%, ctxdiff diffs 0, instructions 73/73. scanAP: objdiff 99.20221%, ctxdiff diffs 4, instructions 272/272. All owned data sections are 100%. No literal is missing, and no symbol rename or extent adjustment was required. The only open function is scanAP; its 123 distinct compiled trials and declaration searches exceed the three-attempt handoff requirement.

## Host-restart recovery 2026-10-03T03:50:28.907285+00:00

Preserved commits 349be634 and f4797373 and unrelated untracked perm4.attempts.md. No tracked uncommitted source edits remained. Fetched fork origin under /tmp/wii-git.lock; origin/main is a791e598a154e105d9ca81087d8d5912e222636a. Owned source and headers have no changes in the new origin/main commits. No rebase or branch changes.
Fresh object build: no work to do. Corrected pool_diff argument from unit path to explicit source/target object paths: POOL IDENTICAL, 108/108. convertRevIP: 73/73 instructions, diffs 0. scanAP: 272/272 instructions, diffs 4 at 239-242, only state-9 lookup loads/argument ordering. Previous 123 scanAP trials retained and not repeated.
One initial skill announcement was emitted before reading silent_mode_first, as required by the session skill instructions. Subsequent worker communication is tool calls only.

scanAP | recovery-common-int-animation-index | {"insns": [272, 272], "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)", "ctxdiff": "src 0x440 base 0x440 insns 272/272\ndiffs 4: [239, 240, 241, 242]\n   239 M lwz r3, 0xc4(r3)\n       B lwz r0, 0x918(r3)\n   240 M lwz r0, 0x918(r31)\n       B lwz r3, 0xc4(r3)\n   241 M addi r3, r3, 0x28c\n       B clrlwi r4, r0, 0x10\n   242 M clrlwi r4, r0, 0x10\n       B addi r3, r3, 0x28c"}

scanAP | recovery-common-u16-animation-index | {"insns": [272, 272], "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)", "ctxdiff": "src 0x440 base 0x440 insns 272/272\ndiffs 4: [239, 240, 241, 242]\n   239 M lwz r3, 0xc4(r3)\n       B lwz r0, 0x918(r3)\n   240 M lwz r0, 0x918(r31)\n       B lwz r3, 0xc4(r3)\n   241 M addi r3, r3, 0x28c\n       B clrlwi r4, r0, 0x10\n   242 M clrlwi r4, r0, 0x10\n       B addi r3, r3, 0x28c"}

scanAP | recovery-common-animator-result | {"insns": [272, 272], "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)", "ctxdiff": "src 0x440 base 0x440 insns 272/272\ndiffs 4: [239, 240, 241, 242]\n   239 M lwz r3, 0xc4(r3)\n       B lwz r0, 0x918(r3)\n   240 M lwz r0, 0x918(r31)\n       B lwz r3, 0xc4(r3)\n   241 M addi r3, r3, 0x28c\n       B clrlwi r4, r0, 0x10\n   242 M clrlwi r4, r0, 0x10\n       B addi r3, r3, 0x28c"}

scanAP | recovery-final-preserved-source | {"insns": [272, 272], "diffs": 4, "pool": "POOL IDENTICAL up to 108 (mine=108 base=108)", "ctxdiff": "src 0x440 base 0x440 insns 272/272\ndiffs 4: [239, 240, 241, 242]\n   239 M lwz r3, 0xc4(r3)\n       B lwz r0, 0x918(r3)\n   240 M lwz r0, 0x918(r31)\n       B lwz r3, 0xc4(r3)\n   241 M addi r3, r3, 0x28c\n       B clrlwi r4, r0, 0x10\n   242 M clrlwi r4, r0, 0x10\n       B addi r3, r3, 0x28c"}

## Recovery final clean full gate 2026-10-03T03:54:55.458102+00:00

Three new common-local scanAP trials were compiled: int animation index, u16 animation index, and Animator result pointer. All stayed 272/272 instructions with the same four differences and identical 108-string pools. Restored the prior gate-passing committed source byte for byte. No previous source trial was repeated.

Command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/setting/iplSetting, without --quick. Exit status 0.

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 36796/37884 data 5696/5696 functions 111/112 fuzzy 99.9771 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 110/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 100.0
[src/scene/setting/iplSetting]   section .rodata size 640 match 100.0
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 99.97709
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 99.20221
[src/scene/setting/iplSetting] baseline: code 36504/37884 data 1680 functions 110 fuzzy 99.8577
regressions vs baseline: 0
global matched_code_percent: 91.53532 -> 91.54507
global fuzzy_match_percent: 99.69871 -> 99.70022
global complete_code_percent: 74.74593 -> 74.74593
global matched_data_percent: 99.55890 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Regenerated build/43U/report.json with ninja progress build/43U/report.json. Open functions: scanAP__Q33ipl5scene7SettingFv, 99.20221%, four differences at instructions 239-242. All 126 distinct source-level scanAP trials are logged, exceeding the three-attempt plateau handoff contract. convertRevIP is still 100.0%, 73/73 instructions, diffs 0. Data stays 5696/5696 and all six owned data sections are 100%.

Fresh raw-byte verification of the existing gate discrepancy: setUpdate_NoUpdateDialog___Q33ipl5scene7SettingFv source and target instruction bytes are identical, 120 bytes, SHA1 1d64ee400d91a5c2583db97e3334c3805da18006. Live objdiff correctly gives it 100.0%. Gate still reports 110/112 raw instruction-exact functions; actual exact count is 111/112. Earlier independently measured raw baseline 109/112 -> candidate 110/112 is preserved; corrected actual count is 110/112 -> 111/112. No helper or gate edits.
