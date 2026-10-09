# cleanup-c4 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d4`, branch `agent/w1009/cleanup-c4`.
Baseline `f1db6b656e386063a8bc263fb75a299f36ae4803`. Existing untracked files retained.

Acceptance: readable changes only in the four assigned files; every allocated object section and relocation stays identical; all four units remain Matching; final full build, objdiff report, DECOMPLETE_OK, and gate.py pass with zero regressions and DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`. Commit each source file separately and this log.

Baseline full build passed, report regenerated, DECOMPLETE_OK; code/data/link 100%, 12563/12563 functions; DOL SHA1 verified.

## Trials

- setting-remove-all-pragmas: REJECT, changed .rela.text, .text.
- kitayama-remove-all-pragmas: REJECT, changed .rela.text, .text.
- address-remove-all-pragmas: REJECT, changed .rela.data, .rela.text, .text.
- ax-remove-all-pragmas: REJECT, changed .rela.text, .text.
- setting-remove-all-pragmas instruction evidence: `scanAP__Q33ipl5scene7SettingFv` 14 differing instructions, 272/272 instruction counts.
- kitayama-remove-all-pragmas instruction evidence: `calcNormal__Q33ipl5scene12KitayamaTestFv` 3 differing instructions, 464/464 instruction counts.
- address-remove-all-pragmas instruction evidence: `create__Q33ipl5scene11AddressEditFv` 329 differing instructions, 818/820 instruction counts.
- address-remove-all-pragmas instruction evidence: `get_friendinfo__Q33ipl5scene11AddressEditFv` 68 differing instructions, 82/84 instruction counts.
- address-remove-all-pragmas instruction evidence: `update_friendinfo__Q33ipl5scene11AddressEditFv` 2 differing instructions, 38/38 instruction counts.
- ax-remove-all-pragmas instruction evidence: `Init__Q44nw4r3snd6detail9AxManagerFv` 52 differing instructions, 62/63 instruction counts.
- kitayama-controller-first: REJECT, changed .rela.text, .text.
- kitayama-controller-declare-first: REJECT, changed .rela.text, .text.
- kitayama-buffer-first: REJECT, changed .rela.text, .text.
- kitayama-result-last: REJECT, changed .rela.text, .text.
- kitayama-controller-reference: REJECT, changed .rela.text, .text.
- kitayama-buffer-scopes: REJECT, changed .rela.text.
- setting-scan-index-locals: REJECT, compilation failed.
- setting-scan-direct-predicate: REJECT, changed .rela.data, .rela.text, .text.
- setting-scan-state-local: REJECT, changed .rela.text, .text.
- ax-init-voice-pointer: REJECT, changed .rela.text, .text.
- ax-init-voice-local: REJECT, changed .rela.text, .text.
- ax-init-loop-scope: REJECT, changed .rela.text, .text.
- Relocation comparison now resolves local compiler labels by section/value, preserving global symbol names. Kitayama buffer scopes changed only local literal symbol names, with identical .text and .data. Retested below.
- kitayama-buffer-scopes-normalized-relocs: KEEP, all allocated sections and relocations identical.
- setting-scan-scoped-indices: REJECT, changed .text.
- setting-scan-animation-local: REJECT, changed .rela.data, .rela.text, .text.
- address-create-no-pragma: REJECT, changed .rela.data, .rela.text, .text.
- address-get-friendinfo-no-pragma: REJECT, changed .rela.data, .rela.text, .text.
- address-update-friendinfo-no-pragma: REJECT, changed .text.
- address-create-text-scopes: REJECT, changed .rela.data, .rela.text, .text.
- address-create-pane-last: REJECT, changed .rela.data, .rela.text, .text.
- address-get-pane-local: REJECT, changed .rela.data, .rela.text, .text.
- address-get-display-scope: REJECT, changed .rela.data, .rela.text, .text.
- address-update-destination-local: REJECT, changed .text.
- address-update-source-first: REJECT, changed .text.
- setting-screen-mode-remove-goto: KEEP, all allocated sections and relocations identical.
- address-create-remove-dead-label: KEEP, all allocated sections and relocations identical.
- address-title-structured-if: KEEP, all allocated sections and relocations identical.
- address-stt_ipt_input-switch: REJECT, compilation failed.
- address-stt_add_name_input-switch: REJECT, compilation failed.
- address-remove-member-parentheses: KEEP, all allocated sections and relocations identical.
- setting-copy-plain-source: REJECT, changed .text.
- setting-copy-plain-destination: REJECT, changed .text.
- setting-render-mode-copy: REJECT, changed .rela.data, .rela.text, .text.
- address-stt_ipt_input-structured-switch: KEEP, all allocated sections and relocations identical.
- address-stt_add_name_input-structured-switch: KEEP, all allocated sections and relocations identical.
- setting-prepare-font-switch: KEEP, all allocated sections and relocations identical.
- address-point-event-structured-switch: KEEP, all allocated sections and relocations identical.
- address-trigger-event-structured-switch: KEEP, all allocated sections and relocations identical.
- address-add-name-fadeout-structured-switch: KEEP, all allocated sections and relocations identical.
- address-polish-titles-and-layout-calls: KEEP, all allocated sections and relocations identical.
- setting-name-render-copy-locals: KEEP, all allocated sections and relocations identical.
- kitayama-remove-obvious-comments: KEEP, all allocated sections and relocations identical.
- ax-document-required-iro: KEEP, all allocated sections and relocations identical.
- setting-document-required-workarounds: KEEP, all allocated sections and relocations identical.
- address-document-required-iro: KEEP, all allocated sections and relocations identical.
- address-remove-unneeded-fadeout-scope: KEEP, all allocated sections and relocations identical.
- address-name-trigger-animators: KEEP, all allocated sections and relocations identical.
- setting-indent-compiler-note: KEEP, all allocated sections and relocations identical.
- ax-indent-compiler-note: KEEP, all allocated sections and relocations identical.
- Final setting: allocated sections and resolved relocations identical to baseline; 112/112 functions exact; every objdiff section 100%; POOL IDENTICAL up to 108 (mine=108 base=108).
- Final kitayama: allocated sections and resolved relocations identical to baseline; 12/12 functions exact; every objdiff section 100%; POOL IDENTICAL up to 17 (mine=17 base=17).
- Final address: allocated sections and resolved relocations identical to baseline; 94/94 functions exact; every objdiff section 100%; POOL IDENTICAL up to 57 (mine=57 base=57).
- Final ax: allocated sections and resolved relocations identical to baseline; 25/25 functions exact; every objdiff section 100%; POOL IDENTICAL up to 0 (mine=0 base=0).
- Final live report compared with the saved f1db6b65 baseline: 0 regressions across all 1028 units.
- Final ctxdiff `prepare__Q33ipl5scene7SettingFv`: src 0x2cc base 0x2cc insns 179/179.
- Final ctxdiff `updateScreenMode__Q33ipl5scene7SettingFv`: src 0x224 base 0x224 insns 137/137.
- Final ctxdiff `draw__Q33ipl5scene7SettingFv`: src 0x9e0 base 0x9e0 insns 632/632.
- Final ctxdiff `scanAP__Q33ipl5scene7SettingFv`: src 0x440 base 0x440 insns 272/272.
- Final ctxdiff `calcNormal__Q33ipl5scene12KitayamaTestFv`: src 0x740 base 0x740 insns 464/464.
- Final ctxdiff `create__Q33ipl5scene11AddressEditFv`: src 0xcd0 base 0xcd0 insns 820/820.
- Final ctxdiff `get_friendinfo__Q33ipl5scene11AddressEditFv`: src 0x150 base 0x150 insns 84/84.
- Final ctxdiff `update_friendinfo__Q33ipl5scene11AddressEditFv`: src 0x98 base 0x98 insns 38/38.
- Final ctxdiff `stt_ipt_input__Q33ipl5scene11AddressEditFv`: src 0x20c base 0x20c insns 131/131.
- Final ctxdiff `stt_add_name_input__Q33ipl5scene11AddressEditFv`: src 0x20c base 0x20c insns 131/131.
- Final ctxdiff `stt_add_name_fadeout__Q33ipl5scene11AddressEditFv`: src 0x35c base 0x35c insns 215/215.
- One ctxdiff invocation used the wrong mangled spelling for start_point_event. Corrected from the object symbol table below.
- Final ctxdiff `start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface`: src 0x2d8 base 0x2d8 insns 182/182, diffs 0.
- Final ctxdiff `start_trig_event__Q33ipl5scene11AddressEditFPCc`: src 0x1c0 base 0x1c0 insns 112/112, diffs 0.
- Final ctxdiff `setDefaultTitleText__Q33ipl5scene11AddressEditFPCwb`: src 0xfc base 0xfc insns 63/63, diffs 0.
- Final ctxdiff `Init__Q44nw4r3snd6detail9AxManagerFv`: src 0xfc base 0xfc insns 63/63, diffs 0.
- Source commit setting: `3f946af9e6f68553d12314dab89652fd9d0b56be`.
- Source commit kitayama: `3896bec3f879af024b8042fe76eaea1284acb85b`.
- Source commit address: `7d74f57dec6e658a3e371dbc5e8658e1cf7bd9ab`.
- Source commit ax: `fa054a047ec782a46d68ff170a03300d4d67cdb4`.

## Retained result

- iplSetting.cpp: removed 11 gotos through region-constant font selection and screen-mode dispatch; renamed render-copy locals. scanAP IRO 1 stays because removal changes 14 instructions. The volatile render copy stays because removing either qualifier changes .text and a normal struct copy also changes sizes and relocations. Both have one-line compiler notes.
- iplKitayamaTest.cpp: removed push/IRO 2/pop by giving each write branch its own buffer local. Removed three comments that repeated the statements. Default compiler settings now reproduce the same 464 calcNormal instructions, data, and resolved relocations; only local compiler label names change.
- iplAddressEdit.cpp: removed all 47 gotos, dead create_mode_done label, unnecessary common-block scope, and redundant member parentheses. Structured title, keyboard state, fadeout, point, and trigger dispatch retain the original fallthrough and call order. Uses existing keyboard, region, and address-mode constants. All three IRO 1 pragmas stay; removal changes create 329 instructions, get_friendinfo 68, and update_friendinfo 2. Added concise notes explaining the retained settings.
- snd_AxManager.cpp: retained IRO 0 because default lowering hoists the indexed voice address and removes one instruction. Three readable loop rewrites also changed bytes. Replaced the unclear uh comment with the specific compiler requirement.
- Final full build and report generation passed; DECOMPLETE_OK; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. All 243 owned functions and all owned sections remain 100%; fresh baseline comparison found 0 regressions in all 1028 units. All 15 focused ctxdiff checks have diffs 0 and equal instruction counts.

## Final gate

Command: `python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/setting/iplSetting src/scene/kitayamaTest/iplKitayamaTest src/scene/address/iplAddressEdit libs/NW4R/src/snd/snd_AxManager --quick`. The cleanup brief explicitly requires --quick.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 37884/37884 data 5696/5696 functions 112/112 fuzzy 100.0000 linked code 37884
[src/scene/setting/iplSetting] instruction-exact functions: 112/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 100.0
[src/scene/setting/iplSetting]   section .rodata size 640 match 100.0
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 100.0
[src/scene/setting/iplSetting] baseline: code 37884/37884 data 5696 functions 112 fuzzy 100.0000
[src/scene/kitayamaTest/iplKitayamaTest] pool: IDENTICAL
[src/scene/kitayamaTest/iplKitayamaTest] objdiff: code 2520/2520 data 632/632 functions 12/12 fuzzy 100.0000 linked code 2520
[src/scene/kitayamaTest/iplKitayamaTest] instruction-exact functions: 12/12
[src/scene/kitayamaTest/iplKitayamaTest]   section .data size 632 match 100.0
[src/scene/kitayamaTest/iplKitayamaTest]   section .text size 2520 match 100.0
[src/scene/kitayamaTest/iplKitayamaTest] baseline: code 2520/2520 data 632 functions 12 fuzzy 100.0000
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 27112/27112 data 2560/2560 functions 94/94 fuzzy 100.0000 linked code 27112
[src/scene/address/iplAddressEdit] instruction-exact functions: 94/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 100.0
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 100.0
[src/scene/address/iplAddressEdit] baseline: code 27112/27112 data 2560 functions 94 fuzzy 100.0000
[libs/NW4R/src/snd/snd_AxManager] pool: IDENTICAL
[libs/NW4R/src/snd/snd_AxManager] objdiff: code 6364/6364 data 42040/42040 functions 25/25 fuzzy 100.0000 linked code 6364
[libs/NW4R/src/snd/snd_AxManager] instruction-exact functions: 25/25
[libs/NW4R/src/snd/snd_AxManager]   section .bss size 42008 match 100.0
[libs/NW4R/src/snd/snd_AxManager]   section .sbss size 8 match 100.0
[libs/NW4R/src/snd/snd_AxManager]   section .sdata2 size 24 match 100.0
[libs/NW4R/src/snd/snd_AxManager]   section .text size 6364 match 100.0
[libs/NW4R/src/snd/snd_AxManager] baseline: code 6364/6364 data 42040 functions 25 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 100.00000 -> 100.00000
global fuzzy_match_percent: 99.99989 -> 99.99989
global complete_code_percent: 100.00000 -> 100.00000
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Post-gate report regenerated; DECOMPLETE_OK; DOL SHA1 verified again. Only the assigned source files and this log are committed. Existing untracked files remain untouched. No push, PR, merge, rebase, or cross-worktree edit.
