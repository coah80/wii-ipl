# f5b focus round

Branch agent/w1005/f5b, base 491bba6a. Own Address::onEventDerived, then AddressEdit::create, get_friendinfo and update_friendinfo. Fresh origin fetch confirms the base. Prior f5 drag match is merged as #1159 and must stay exact.

Acceptance: readable C/C++, identical pools, exact-name objdiff 100.0 and zero raw instruction differences for each retained candidate, no other function drops, then clean full gate and DOL SHA1. Matching phase only; configure.py remains unchanged. No pushes, PRs, merges, rebases or other-worktree edits.

Read scene4, gk3 and a23h history, plus f5's 88 manual update measurements and three completed 1200-second searches. Reuse those findings and avoid repeating unchanged hypotheses. Fresh experiments and all rejected variants remain in /tmp/f5b-work.

## Baseline and trials

- event-baseline: Fresh real-command compilation on 491bba6a. {"score": 98.42593, "insns": [270, 270], "diffs": 81, "drops": {}, "pool": "POOL IDENTICAL up to 81 (mine=81 base=81)"}. Evidence `/tmp/f5b-work/event-baseline/`.
- create-baseline: Fresh real-command compilation on 491bba6a. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-baseline/`.
- get-baseline: Fresh real-command compilation on 491bba6a. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-baseline/`.
- update-baseline: Fresh real-command compilation on 491bba6a. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-baseline/`.
- event-r1-manager-pointer: Give the full pane-name lookup a typed inline return boundary. {"error": "pl-workers\\data-\n#   d5\\include\\scene\\iplSceneBase.h:6\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\scene\\iplFaderSceneBase.h:4\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\iplSceneUIHeader.h:5\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\scene\\address\\iplAddress.h:4\n#       Z:\\tmp\\f5b-work\\event-r1-manager-pointer\\iplAddress.cpp:6)\n### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\f5b-work\\event-r1-manager-pointer\\iplAddress.cpp\n# ----------------------------------------------------------------\n#    1422:        const char* paneName = getEventPaneName(mpManager, compId); \n#   Error:                                                                 ^\n#   (10248) function call '[ipl::scene::Address].getEventPaneName({lval} \n#   gui::Manager *, {lval} unsigned long)' does not match\n#   'ipl::scene::getEventPaneName(ipl::gui::PaneManager *, unsigned long)'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}. Evidence `/tmp/f5b-work/event-r1-manager-pointer/`.
- event-r1-manager-reference: Give the full pane-name lookup a typed inline return boundary. {"error": "orkers\\data-\n#   d5\\include\\scene\\iplSceneBase.h:6\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\scene\\iplFaderSceneBase.h:4\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\iplSceneUIHeader.h:5\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\scene\\address\\iplAddress.h:4\n#       Z:\\tmp\\f5b-work\\event-r1-manager-reference\\iplAddress.cpp:6)\n### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\f5b-work\\event-r1-manager-reference\\iplAddress.cpp\n# ------------------------------------------------------------------\n#    1422:       const char* paneName = getEventPaneName(*mpManager, compId); \n#   Error:                                                                 ^\n#   (10248) function call '[ipl::scene::Address].getEventPaneName({lval} \n#   gui::Manager, {lval} unsigned long)' does not match\n#   'ipl::scene::getEventPaneName(ipl::gui::PaneManager &, unsigned long)'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}. Evidence `/tmp/f5b-work/event-r1-manager-reference/`.
- event-r1-pane-reference: Give the full pane-name lookup a typed inline return boundary. {"score": 98.42593, "insns": [270, 270], "diffs": 81, "drops": {}, "pool": "POOL IDENTICAL up to 81 (mine=81 base=81)"}. Evidence `/tmp/f5b-work/event-r1-pane-reference/`.
- event-r1-button-getter: Typed scene getter controls the button receiver lifetime. {"score": 100.0, "insns": [270, 270], "diffs": 0, "drops": {}, "pool": "POOL IDENTICAL up to 81 (mine=81 base=81)"}. Evidence `/tmp/f5b-work/event-r1-button-getter/`.
- event-r1-button-reference-getter: Typed scene getter controls the button receiver lifetime. {"score": 100.0, "insns": [270, 270], "diffs": 0, "drops": {}, "pool": "POOL IDENTICAL up to 81 (mine=81 base=81)"}. Evidence `/tmp/f5b-work/event-r1-button-reference-getter/`.
- event-r1-mail-getter: Typed mail-scene getter boundary before exit animation. {"score": 98.37037, "insns": [270, 270], "diffs": 84, "drops": {"onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface": [98.42593, 98.37037]}, "pool": "POOL IDENTICAL up to 81 (mine=81 base=81)"}. Evidence `/tmp/f5b-work/event-r1-mail-getter/`.
- event-r1-controller-getter: Typed controller lookup boundary in both hover cases. {"score": 98.42593, "insns": [270, 270], "diffs": 81, "drops": {}, "pool": "POOL IDENTICAL up to 81 (mine=81 base=81)"}. Evidence `/tmp/f5b-work/event-r1-controller-getter/`.
- event-r1-animation-pointer: Keep each animation operation behind a typed layout boundary. {"score": 98.42593, "insns": [270, 270], "diffs": 81, "drops": {}, "pool": "POOL IDENTICAL up to 81 (mine=81 base=81)"}. Evidence `/tmp/f5b-work/event-r1-animation-pointer/`.
- event-r1-animation-reference: Keep each animation operation behind a typed layout boundary. {"score": 98.42593, "insns": [270, 270], "diffs": 81, "drops": {}, "pool": "POOL IDENTICAL up to 81 (mine=81 base=81)"}. Evidence `/tmp/f5b-work/event-r1-animation-reference/`.

## Address exact candidate

A typed getEventButton() inline lookup fixes all 81 register differences without changing the 270-instruction stream or pool. Both pointer-return and reference-return variants were exact; retain the smaller pointer form. Every Address function remains at its baseline or improves, including the merged drag match. Other helper boundaries did not help. The two failed manager experiments passed the derived PaneManager type where the stored receiver is the base gui::Manager; they were not retained.

- create-r1-board-file-getter: Typed Board lookup boundary, following the exact event Button getter. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r1-board-file-getter/`.
- create-r1-board-file-reference: Typed Board lookup boundary, following the exact event Button getter. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r1-board-file-reference/`.
- create-r1-board-scene-getter: Typed Board lookup boundary, following the exact event Button getter. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r1-board-scene-getter/`.
- create-r1-text-pointer: Inline named-pane setter binds the actual text before its virtual pane lookup. {"score": 95.99756, "insns": [802, 820], "diffs": 318, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 95.99756]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r1-text-pointer/`.
- create-r1-text-reference: Inline named-pane setter binds the actual text before its virtual pane lookup. {"score": 95.99756, "insns": [802, 820], "diffs": 318, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 95.99756]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r1-text-reference/`.
- create-r1-text-wrapper: Inline named-pane setter binds the actual text before its virtual pane lookup. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r1-text-wrapper/`.

Address candidate object rebuild: pool 81/81 identical; onEventDerived 270/270, raw ctxdiff zero. Incremental full gate GATE PASS, Address 101/101 instruction-exact, code 23988/23988, data 1964/1964, zero regressions and correct DOL SHA1. Final clean gate remains required. Evidence: /tmp/f5b-work/address-quick-gate.log.
- create-r2-member-direct: Guarded inline member setter binds text across the pane lookup. {"error": "### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\f5b-work\\create-r2-member-direct\\iplAddressEdit.cpp\n# -------------------------------------------------------------------\n#       2: #include \"/tmp/f5b-work/create-r2-member-direct-header/iplAddressEdit.h\" \n#   Error:          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n#   (10151) the file '/tmp/f5b-work/create-r2-member-direct-header/\n#   iplAddressEdit.h' cannot be opened\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}. Evidence `/tmp/f5b-work/create-r2-member-direct/`.
- create-r2-member-wrapper: Guarded inline member setter binds text across the pane lookup. {"error": "### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\f5b-work\\create-r2-member-wrapper\\iplAddressEdit.cpp\n# --------------------------------------------------------------------\n#       2: #include \"/tmp/f5b-work/create-r2-member-wrapper-header/iplAddressEdit.h\" \n#   Error:          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n#   (10151) the file '/tmp/f5b-work/create-r2-member-wrapper-header/\n#   iplAddressEdit.h' cannot be opened\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}. Evidence `/tmp/f5b-work/create-r2-member-wrapper/`.
- create-r2-margin-getters: Inline margin value boundary inside the new expression, preserving allocation condition. {"score": 96.42927, "insns": [808, 820], "diffs": 791, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 96.42927]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r2-margin-getters/`.
- create-r2-margin-helper-arg: Inline margin value boundary inside the new expression, preserving allocation condition. {"score": 96.42927, "insns": [808, 820], "diffs": 791, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 96.42927]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r2-margin-helper-arg/`.
- create-r2-member-direct-local: Same guarded setter test with a source-local private include path. {"score": 95.99756, "insns": [802, 820], "diffs": 318, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 95.99756]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r2-member-direct-local/`.
- create-r2-member-wrapper-local: Same guarded setter test with a source-local private include path. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r2-member-wrapper-local/`.

Create search seeds 50, 500 and 5000 queued for 1200 seconds each from the best manual state, still baseline. Current shared srcsearch copied privately with only the already-proven owned-definition locator fix; mutation safety guards and the global 24-slot limiter are unchanged. Output directories /tmp/f5b-work/create-search-<seed>.
- get-r1-arguments-edit-pane-text: Small setter boundary passes the actual pane and text values in a natural alternate parameter order. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r1-arguments-edit-pane-text/`.
- get-r1-arguments-edit-text-pane: Small setter boundary passes the actual pane and text values in a natural alternate parameter order. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r1-arguments-edit-text-pane/`.
- get-r1-arguments-pane-edit-text: Small setter boundary passes the actual pane and text values in a natural alternate parameter order. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r1-arguments-pane-edit-text/`.
- get-r1-arguments-pane-text-edit: Small setter boundary passes the actual pane and text values in a natural alternate parameter order. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r1-arguments-pane-text-edit/`.
- get-r1-arguments-text-edit-pane: Small setter boundary passes the actual pane and text values in a natural alternate parameter order. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r1-arguments-text-edit-pane/`.
- get-r1-arguments-text-pane-edit: Small setter boundary passes the actual pane and text values in a natural alternate parameter order. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r1-arguments-text-pane-edit/`.
- get-r1-wrapper: Vary the actual pane lookup object boundary without caching an unrelated pointer. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r1-wrapper/`.
- get-r1-root-reference: Vary the actual pane lookup object boundary without caching an unrelated pointer. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r1-root-reference/`.
- get-search-seed: Name the real cache index and text lifetimes to expose source-search declaration mutations. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-search-seed/`.
- update-r1-scene-pointer: Use the typed scene getter boundary that made Address event handling exact. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r1-scene-pointer/`.
- update-r1-scene-reference: Use the typed scene getter boundary that made Address event handling exact. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r1-scene-reference/`.
- update-r1-commit-pointer: Group the cache update and parent-list refresh behind one real operation boundary. {"error": "rSceneBase.h:4\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\iplSceneHeader.h:5\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\scene\\address\\iplAddressEdit.h:4\n#       Z:\\tmp\\f5b-work\\update-r1-commit-pointer\\iplAddressEdit.cpp:2)\n### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\f5b-work\\update-r1-commit-pointer\\iplAddressEdit.cpp\n# --------------------------------------------------------------------\n#     313:         return; \n# Warning:               ^\n#   (10184) return value expected\n### mwcceppc.exe Compiler:\n#     316: } \n# Warning: ^\n#   (10184) return value expected\n### mwcceppc.exe Compiler:\n#    2885: pl::scene::Address*>(ipl::System::getScene(0x14))->reset_friend(); \n#   Error:                                                                 ^\n#   (10381) illegal access from 'ipl::scene::Address' to protected/private \n#   member 'ipl::scene::Address::reset_friend()'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}. Evidence `/tmp/f5b-work/update-r1-commit-pointer/`.
- update-r1-commit-reference: Group the cache update and parent-list refresh behind one real operation boundary. {"error": "Base.h:4\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\iplSceneHeader.h:5\n#       Z:\\mnt\\drive2\\projects\\wii-ipl-workers\\data-\n#   d5\\include\\scene\\address\\iplAddressEdit.h:4\n#       Z:\\tmp\\f5b-work\\update-r1-commit-reference\\iplAddressEdit.cpp:2)\n### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\f5b-work\\update-r1-commit-reference\\iplAddressEdit.cpp\n# ----------------------------------------------------------------------\n#     313:         return; \n# Warning:               ^\n#   (10184) return value expected\n### mwcceppc.exe Compiler:\n#     316: } \n# Warning: ^\n#   (10184) return value expected\n### mwcceppc.exe Compiler:\n#    2885: pl::scene::Address*>(ipl::System::getScene(0x14))->reset_friend(); \n#   Error:                                                                 ^\n#   (10381) illegal access from 'ipl::scene::Address' to protected/private \n#   member 'ipl::scene::Address::reset_friend()'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n"}. Evidence `/tmp/f5b-work/update-r1-commit-reference/`.

Get-friendinfo seeds 51, 501 and 5001 queued with the same 1200-second budget and unchanged limiter. The named-local seed compiled identically to baseline: 82/84 instructions, 88.03571%, 66 positional differences, identical pool and zero drops.
- create-r3-const-margins: Test the genuine margin value or reference lifetime across vector construction. {"score": 96.42927, "insns": [808, 820], "diffs": 791, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 96.42927]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r3-const-margins/`.
- create-r3-static-margins: Test the genuine margin value or reference lifetime across vector construction. {"score": 96.42927, "insns": [808, 820], "diffs": 791, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 96.42927]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r3-static-margins/`.
- create-r3-reference-margins: Test the genuine margin value or reference lifetime across vector construction. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r3-reference-margins/`.
- create-r3-double-margins: Test the genuine margin value or reference lifetime across vector construction. {"score": 97.40976, "insns": [818, 820], "diffs": 329, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 97.40976]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r3-double-margins/`.
- create-r3-heap-getter: Give the final constructor heap argument a typed value boundary. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r3-heap-getter/`.
- create-r3-heap-reference: Give the final constructor heap argument a typed value boundary. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r3-heap-reference/`.
- get-r2-const-array-ref-direct: Preserve the actual String array or enclosing edit accessor type across pane lookup. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r2-const-array-ref-direct/`.
- get-r2-const-array-ref-wrapper: Preserve the actual String array or enclosing edit accessor type across pane lookup. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r2-const-array-ref-wrapper/`.
- get-r2-array-ref-direct: Preserve the actual String array or enclosing edit accessor type across pane lookup. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r2-array-ref-direct/`.
- get-r2-array-ref-wrapper: Preserve the actual String array or enclosing edit accessor type across pane lookup. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r2-array-ref-wrapper/`.
- get-r2-const-array-pointer-direct: Preserve the actual String array or enclosing edit accessor type across pane lookup. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r2-const-array-pointer-direct/`.
- get-r2-const-array-pointer-wrapper: Preserve the actual String array or enclosing edit accessor type across pane lookup. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r2-const-array-pointer-wrapper/`.
- update-r2-cache-getter: Typed cache/index accessor boundaries around the final friend update. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r2-cache-getter/`.
- get-r2-edit-pointer-direct: Preserve the actual String array or enclosing edit accessor type across pane lookup. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r2-edit-pointer-direct/`.
- update-r2-index-getter: Typed cache/index accessor boundaries around the final friend update. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r2-index-getter/`.
- update-r2-both-getter: Typed cache/index accessor boundaries around the final friend update. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r2-both-getter/`.
- get-r2-edit-pointer-wrapper: Preserve the actual String array or enclosing edit accessor type across pane lookup. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r2-edit-pointer-wrapper/`.
- update-r2-commit-member: A member boundary retains the real friend access permission while grouping cache update and list refresh. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r2-commit-member/`.
- get-r3-load-name-pointer: Return the actual name buffer from the operation that fills it. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r3-load-name-pointer/`.
- get-r3-load-buffers-pointer: Return populated text buffers at both real String operation boundaries. {"score": 88.09524, "insns": [84, 84], "diffs": 42, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r3-load-buffers-pointer/`.
- get-r3-load-name-reference: Return the actual name buffer from the operation that fills it. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r3-load-name-reference/`.
- get-r3-load-buffers-reference: Return populated text buffers at both real String operation boundaries. {"score": 88.09524, "insns": [84, 84], "diffs": 42, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r3-load-buffers-reference/`.
- update-search-seed: Combine the prior named-local seed with a typed cache getter for a new source-search round. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-search-seed/`.

Update seeds 52, 502 and 5002 use the prior named-local seed with a new typed cache getter, verified at unchanged 99.42105%, 38/38, two differences. Get-friendinfo seed 50001 uses the best new manual candidate: returning populated display buffers from real String operations gives 84/84 instructions, 88.09524%, 42 positional differences and no drops. Its two added address instructions are duplicated across the format branches, so this is still structurally wrong and is not retained. All runs retain the standard 1200-second budget and 24-slot limiter.
- get-r4-display-entry: Keep the display buffer address alive across the real formatting operations. {"score": 92.67857, "insns": [83, 84], "diffs": 36, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r4-display-entry/`.
- get-r4-display-before-name: Keep the display buffer address alive across the real formatting operations. {"score": 91.40476, "insns": [83, 84], "diffs": 36, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r4-display-before-name/`.
- get-r4-display-before-format: Keep the display buffer address alive across the real formatting operations. {"score": 91.07143, "insns": [83, 84], "diffs": 42, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r4-display-before-format/`.
- get-r4-format-boundary: One common formatter return expresses the shared display address after both formatting paths. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r4-format-boundary/`.
- get-r5-const-entry-declare: Reuse one typed text receiver with separate definite assignments and natural declaration positions. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r5-const-entry-declare/`.
- get-r5-const-entry-name: Reuse one typed text receiver with separate definite assignments and natural declaration positions. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r5-const-entry-name/`.
- get-r5-const-after-copy-declare: Reuse one typed text receiver with separate definite assignments and natural declaration positions. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r5-const-after-copy-declare/`.
- get-r5-const-after-copy-name: Reuse one typed text receiver with separate definite assignments and natural declaration positions. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r5-const-after-copy-name/`.
- get-r5-mutable-entry-declare: Reuse one typed text receiver with separate definite assignments and natural declaration positions. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r5-mutable-entry-declare/`.
- get-r5-mutable-entry-name: Reuse one typed text receiver with separate definite assignments and natural declaration positions. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r5-mutable-entry-name/`.
- get-r5-mutable-after-copy-declare: Reuse one typed text receiver with separate definite assignments and natural declaration positions. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r5-mutable-after-copy-declare/`.
- get-r5-mutable-after-copy-name: Reuse one typed text receiver with separate definite assignments and natural declaration positions. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r5-mutable-after-copy-name/`.
- get-r6-text-first: Bind the two real text-setting operands as a typed local value before applying them. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r6-text-first/`.
- get-r6-pane-first: Bind the two real text-setting operands as a typed local value before applying them. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r6-pane-first/`.
- get-r6-reference-text: Bind the two real text-setting operands as a typed local value before applying them. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r6-reference-text/`.

Seed get-50001 was still unstarted with an empty log, so it was requeued once from the stronger manual display-entry candidate: 92.67857%, 83/84 instructions, no drops and an identical pool. Its single remaining missing instruction is not yet fixed; the display pointer is computed too early. No trials were discarded, and seed, output directory, time budget and limiter are unchanged.
- create-r4-margin-reference-getters: Evaluate ordinary read-only margin objects through references within the new expression. {"score": 96.42927, "insns": [808, 820], "diffs": 791, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 96.42927]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r4-margin-reference-getters/`.
- create-r4-heap-first: Name actual portrait-creation arguments in the two natural evaluation orders. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r4-heap-first/`.
- create-r4-manager-first: Name actual portrait-creation arguments in the two natural evaluation orders. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r4-manager-first/`.
- create-r4-layout-factory: Share the repeated real layout construction operation through a typed factory. {"score": 94.68414, "insns": [827, 820], "diffs": 759, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 94.68414]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r4-layout-factory/`.

## Retained source audit

Address source object audit confirms every changed byte lies inside onEventDerived: 106 bytes across its 81 previously differing instruction words. Function names and extents remain identical; getEventButton emits no standalone function. All allocated non-code sections are byte-identical, and the .sbss extent is unchanged. Evidence: /tmp/f5b-work/event-section-audit.json. Literal-reference checking analyzed all three sound arguments in the owned function with no candidates, skips or errors.

Origin/main advanced from 491bba6a to bfe77b7f with two keyboard commits. The owned source/header files are unchanged there. The assigned branch remains on its original base, following the no-rebase rule; final regression comparisons will name base 491bba6a explicitly.
- create-r5-address-pointer: Apply the successful typed scene-return boundary to the parent Address lookup. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r5-address-pointer/`.
- create-r5-two-scene-pointer: Combine both real scene lookup boundaries before judging their register interaction. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r5-two-scene-pointer/`.
- create-r6-reviewed-search: Recompile the best search spelling while restoring the target-proven signed Mii index load. {"score": 97.55366, "insns": [818, 820], "diffs": 331, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 97.55366]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r6-reviewed-search/`.
- create-r5-address-reference: Apply the successful typed scene-return boundary to the parent Address lookup. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r5-address-reference/`.
- create-r5-two-scene-reference: Combine both real scene lookup boundaries before judging their register interaction. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r5-two-scene-reference/`.
- create-r7-baseline-api-index: Use the API native unsigned index buffer with an explicit signed value at the target-proven load. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r7-baseline-api-index/`.
- create-r7-baseline-direct-api-index: Remove the now redundant buffer cast while retaining the signed portrait index value. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r7-baseline-direct-api-index/`.
- create-r7-search-api-index: Use the API native unsigned index buffer with an explicit signed value at the target-proven load. {"score": 97.55366, "insns": [818, 820], "diffs": 331, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 97.55366]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r7-search-api-index/`.
- create-r7-search-direct-api-index: Remove the now redundant buffer cast while retaining the signed portrait index value. {"score": 97.55366, "insns": [818, 820], "diffs": 331, "drops": {"create__Q33ipl5scene11AddressEditFv": [97.5561, 97.55366]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r7-search-direct-api-index/`.

## Completed create search review

- Seed 50: done 290 trials; best-nodrop energy -93.9512; it 180 best-nodrop -93.9512 cnt {'create__Q33ipl5scene11AddressEditFv': 818} score [97.95122]; solution.c present: False.
- Seed 500: done 292 trials; best-nodrop energy -93.9512; it 198 best-nodrop -93.9512 cnt {'create__Q33ipl5scene11AddressEditFv': 818} score [97.95122]; solution.c present: False.
- Seed 5000: done 289 trials; best-nodrop energy -93.939; it 241 best-nodrop -93.9390 cnt {'create__Q33ipl5scene11AddressEditFv': 818} score [97.939026]; solution.c present: False.

All three runs used the full 1200-second budget after slot acquisition. Best sources remain 818/820 instructions and below 98%. Their higher scores include an unsigned Mii index buffer that changes the target signed load. Recompiling the best with s16 storage or an explicit s16 value restores that load but gives 97.55366%, below the 97.5561% baseline. Both forms were compiled and rejected. No search changes were retained.

The current manual archive includes 30 compiled create measurements, 37 get_friendinfo measurements, 8 update_friendinfo measurements and 8 onEventDerived measurements, including each baseline. Six rejected compile attempts are logged separately.

## First get-friendinfo search results

- Seed 51: done 237 trials; best-nodrop energy -84.0357; best.c False; solution.c False.
- Seed 501: done 238 trials; best-nodrop energy -84.0357; best.c False; solution.c False.
- Seed 5001: done 236 trials; best-nodrop energy -84.0357; best.c False; solution.c False.

These three full 1200-second searches found no improvement from the named-local baseline. The fourth seed still waits to search the stronger 92.67857% early-display-pointer state.

## Clean full gate

The non-quick gate ran against pinned branch base 491bba6a. All four pending searches were paused before acquiring a slot or starting their budget, then resumed in a finally block. Evidence: /tmp/f5b-work/gate-search-pause.json. The current source remained unchanged.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 23988/23988 data 1964/1964 functions 101/101 fuzzy 100.0000 linked code 0
[src/scene/address/iplAddress] instruction-exact functions: 101/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 100.0
[src/scene/address/iplAddress]   section .rodata size 24 match 100.0
[src/scene/address/iplAddress]   section .sbss size 8 match 100.0
[src/scene/address/iplAddress]   section .sdata size 16 match 100.0
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 100.0
[src/scene/address/iplAddress] baseline: code 22908/23988 data 1964 functions 100 fuzzy 99.9291
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 23344/27112 data 2560/2560 functions 91/94 fuzzy 99.5528 linked code 0
[src/scene/address/iplAddressEdit] instruction-exact functions: 91/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 100.0
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 99.55282
[src/scene/address/iplAddressEdit]   below 100: create__Q33ipl5scene11AddressEditFv 97.5561
[src/scene/address/iplAddressEdit]   below 100: get_friendinfo__Q33ipl5scene11AddressEditFv 88.03571
[src/scene/address/iplAddressEdit]   below 100: update_friendinfo__Q33ipl5scene11AddressEditFv 99.42105
[src/scene/address/iplAddressEdit] baseline: code 23344/27112 data 2560 functions 91 fuzzy 99.5528
regressions vs baseline: 0
global matched_code_percent: 92.65446 -> 92.69051
global fuzzy_match_percent: 99.77653 -> 99.77708
global complete_code_percent: 76.20227 -> 76.20227
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Fresh progress and report generation completed after the gate. Address is instruction-exact and all owned sections are 100%; configure.py is unchanged, so linking remains for the parent.
- create-text-view-conditional: Select the two real String text views through a small constant-argument inline accessor. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-text-view-conditional/`.
- get-text-view-conditional: Select the two real String text views through a small constant-argument inline accessor. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-text-view-conditional/`.
- create-text-view-branches: Select the two real String text views through a small constant-argument inline accessor. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-text-view-branches/`.
- get-text-view-branches: Select the two real String text views through a small constant-argument inline accessor. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-text-view-branches/`.
- create-text-view-selected-local: Select the two real String text views through a small constant-argument inline accessor. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-text-view-selected-local/`.
- get-text-view-selected-local: Select the two real String text views through a small constant-argument inline accessor. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-text-view-selected-local/`.
- create-text-view-switch: Select the two real String text views through a small constant-argument inline accessor. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-text-view-switch/`.
- get-text-view-switch: Select the two real String text views through a small constant-argument inline accessor. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-text-view-switch/`.

## Updated lever pack and compiler diagnostics

Read the new Ghidra exports for every owned function. Event control flow agrees with the retained exact source. get_friendinfo and update_friendinfo have the same calls and branch structure as the current source. The create export truncates at its prologue with bad instruction data, so target assembly remains the authority. New lever 18 permits optimization pragmas for diagnosis only; all experiments stay in private temporary sources and no pragma is retained.

- get-r9-diagnostic-opt_propagation: Private diagnostic only: determine whether opt_propagation controls the surviving copy or address scheduling difference. {"score": 91.84524, "insns": [82, 84], "diffs": 62, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r9-diagnostic-opt_propagation/`.
- get-r9-diagnostic-opt_common_subs: Private diagnostic only: determine whether opt_common_subs controls the surviving copy or address scheduling difference. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r9-diagnostic-opt_common_subs/`.
- get-r9-diagnostic-scheduling: Private diagnostic only: determine whether scheduling controls the surviving copy or address scheduling difference. {"score": 72.54762, "insns": [82, 84], "diffs": 69, "drops": {"get_friendinfo__Q33ipl5scene11AddressEditFv": [88.03571, 72.54762]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r9-diagnostic-scheduling/`.
- get-r9-diagnostic-opt_dead_assignments: Private diagnostic only: determine whether opt_dead_assignments controls the surviving copy or address scheduling difference. {"score": 91.84524, "insns": [82, 84], "diffs": 62, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r9-diagnostic-opt_dead_assignments/`.
- update-r9-diagnostic-opt_propagation: Private diagnostic only: determine whether opt_propagation controls the surviving copy or address scheduling difference. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r9-diagnostic-opt_propagation/`.
- update-r9-diagnostic-opt_common_subs: Private diagnostic only: determine whether opt_common_subs controls the surviving copy or address scheduling difference. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r9-diagnostic-opt_common_subs/`.
- update-r9-diagnostic-scheduling: Private diagnostic only: determine whether scheduling controls the surviving copy or address scheduling difference. {"score": 62.63158, "insns": [38, 38], "diffs": 17, "drops": {"update_friendinfo__Q33ipl5scene11AddressEditFv": [99.42105, 62.63158]}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r9-diagnostic-scheduling/`.
- update-r9-diagnostic-opt_dead_assignments: Private diagnostic only: determine whether opt_dead_assignments controls the surviving copy or address scheduling difference. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r9-diagnostic-opt_dead_assignments/`.
- create-r10-cstyle-casts: Test the new allocator hypothesis that C-style and C++ casts give different temporary numbering. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r10-cstyle-casts/`.
- get-r10-cstyle-casts: Test the new allocator hypothesis that C-style and C++ casts give different temporary numbering. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r10-cstyle-casts/`.
- update-r10-cstyle-casts: Test the new allocator hypothesis that C-style and C++ casts give different temporary numbering. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r10-cstyle-casts/`.
- update-r10-const-count: Keep the real bounded name-copy operation and vary inline parameter const qualification per the new allocator hypothesis. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r10-const-count/`.
- update-r10-plain-count: Keep the real bounded name-copy operation and vary inline parameter const qualification per the new allocator hypothesis. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r10-plain-count/`.
- update-r10-const-pointer-count: Keep the real bounded name-copy operation and vary inline parameter const qualification per the new allocator hypothesis. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r10-const-pointer-count/`.

The eight private diagnostics identify no exact optimization-mode result. Disabling propagation/dead assignments leaves get_friendinfo at 82/84 instructions; disabling scheduling worsens both functions. No diagnostics are retained. C-style cast spellings in all three open functions and primitive/pointer const qualifications in the bounded-name helper also preserve the original scores. These are evidence only, not production changes.
- get-r11-root-pointer: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r11-root-pointer/`.
- update-r12-copy-member: Use an actual String member operation instead of a free getter/copy helper; keep the bounded copy and optional clear unchanged. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r12-copy-member/`.
- update-r12-copy-member-count: Use an actual String member operation instead of a free getter/copy helper; keep the bounded copy and optional clear unchanged. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r12-copy-member-count/`.
- update-r12-copy-member-const-count: Use an actual String member operation instead of a free getter/copy helper; keep the bounded copy and optional clear unchanged. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r12-copy-member-const-count/`.
- update-r12-store-member: Use an actual String member operation instead of a free getter/copy helper; keep the bounded copy and optional clear unchanged. {"score": 99.42105, "insns": [38, 38], "diffs": 2, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/update-r12-store-member/`.
- create-r11-root-pointer: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r11-root-pointer/`.
- get-r11-root-reference: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r11-root-reference/`.
- create-r11-root-reference: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r11-root-reference/`.
- get-r11-recursive-const: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r11-recursive-const/`.
- create-r11-recursive-const: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r11-recursive-const/`.
- get-r11-recursive-plain: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r11-recursive-plain/`.
- create-r11-recursive-plain: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r11-recursive-plain/`.
- get-r11-root-local: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 88.03571, "insns": [82, 84], "diffs": 66, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/get-r11-root-local/`.
- create-r11-root-local: Inline only the virtual lookup and text application while evaluating the actual root outside the boundary; test statement count and parameter lifetime. {"score": 97.5561, "insns": [818, 820], "diffs": 329, "drops": {}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)"}. Evidence `/tmp/f5b-work/create-r11-root-local/`.

Five further root-pane boundaries, each tested in create and get_friendinfo, preserve the original output. Four String::copyNameTo member forms (fixed bound, bound parameter, const bound parameter, combined clear/copy) preserve update_friendinfo at 99.42105%, 38/38 and two differences. The guarded declarations exist only in the private temporary headers; none is retained.

Manual archive after the updated lever checks: event: 8 successful measurements and 2 rejected compiles, create: 40 successful measurements and 2 rejected compiles, get: 51 successful measurements and 0 rejected compiles, update: 20 successful measurements and 2 rejected compiles. Counts include baselines and eight diagnostic-only measurements. The six compile errors are the previously logged private-type/include-path experiments. Private test-runner selector and quoting mistakes were corrected before compilation and added no source experiment.

## Declaration-parser repair for update searches

Seed 5002 exited after 14 trials with no improvement: every mutable integer declaration had become `unsigned int`, which the shared tool can generate but its single-word declaration parser cannot read back. With the remaining pointer declarations separated, there were no further recognized mutations. This is not an exhausted 1200-second search. The private copy now recognizes that generated type; a direct check finds 11 valid declaration mutations in the formerly absorbing state. The global 24-slot limiter and all mutation dependency/safety guards are unchanged.

Three replacement update seeds (52, 502, 5002) were queued with fresh 1200-second budgets in /tmp/f5b-work/update-decl-search-<seed>. Original logs remain intact and their outcomes will be counted separately. No shared tool or other worktree was edited.

Initial update searches ended without any best/solution output: seed 52: 315 trials, seed 502: 315 trials, seed 5002: 14 trials. Seeds 52 and 502 ran through their budgets; seed 5002 stopped at the diagnosed parser state. The three fixed-parser runs remain active to explore the declared integer spellings.

The fourth get_friendinfo search completed 312 trials over its full budget. Its best objective stayed at 92.67857%, 83/84 instructions, with no best.c or solution.c output. The earlier three get searches also had no improvement. The retained function therefore remains at the original 88.03571%, 82/84; the private fuzzy seed is not retained.

All three update searches with the declaration-parser repair completed without an improved candidate. update-decl-search-52: 289 trials in 1209.851 seconds; update-decl-search-502: 269 trials in 1200.658 seconds; update-decl-search-5002: 267 trials in 1202.936 seconds. None produced best.c or solution.c. Each used a normal shared search slot and its full 1200-second budget.

## Final handoff

- create-search-50: 290 trials, final objective -93.9512, best source True, solution source False, highest logged improvement 97.95122.
- create-search-500: 292 trials, final objective -93.9512, best source True, solution source False, highest logged improvement 97.95122.
- create-search-5000: 289 trials, final objective -93.939, best source True, solution source False, highest logged improvement 97.939026.
- get-search-51: 237 trials, final objective -84.0357, best source False, solution source False, highest logged improvement None.
- get-search-501: 238 trials, final objective -84.0357, best source False, solution source False, highest logged improvement None.
- get-search-5001: 236 trials, final objective -84.0357, best source False, solution source False, highest logged improvement None.
- update-search-52: 315 trials, final objective -99.421, best source False, solution source False, highest logged improvement None.
- update-search-502: 315 trials, final objective -99.421, best source False, solution source False, highest logged improvement None.
- update-search-5002: 14 trials, final objective -99.421, best source False, solution source False, highest logged improvement None.
- get-search-50001: 312 trials, final objective -90.6786, best source False, solution source False, highest logged improvement None.
- update-decl-search-52: 289 trials, final objective -99.421, best source False, solution source False, highest logged improvement None.
- update-decl-search-502: 269 trials, final objective -99.421, best source False, solution source False, highest logged improvement None.
- update-decl-search-5002: 267 trials, final objective -99.421, best source False, solution source False, highest logged improvement None.

All 13 recorded search runs have ended, 3363 source-search trials total. The seven create/get searches used their full 1200-second budgets; the three declaration-repair update searches also completed their full budgets after slot acquisition. The initial update searches are counted separately because the parser could become stuck after generating unsigned int declarations. Every generated candidate remains below 100.0%; no search source was retained.

Address::onEventDerived is exact at 100.0%, 270/270 instructions with zero differences. Address now has 101/101 instruction-exact functions, 23988/23988 matched code bytes and 1964/1964 matched data bytes. The source commit is 944e82d9. All allocated data bytes and other function outputs are unchanged. The unit remains NonMatching under the current matching-only worker contract; the parent owns linking.

AddressEdit::create stays 97.5561%, 818/820 instructions. It rematerializes the two text-buffer addresses at their call sites instead of retaining them across virtual pane lookups, and retains register and constructor argument-scheduling differences. Typed scene/file/heap getters, named-pane setters, margin types/lifetimes, constructor factories, API index forms and three full source searches did not produce an exact result.

AddressEdit::get_friendinfo stays 88.03571%, 82/84 instructions. Target retains the two text-buffer addresses across virtual pane calls. Array/pointer/reference accessors, argument-order helpers, formatting-return helpers, early declarations and local aggregate views failed to reproduce it. The strongest readable private candidate reached 92.67857%, 83/84, by preserving the display address too early; another reached 84/84 with duplicated branch-local address formation. Neither is exact or retained. Four full search runs exhausted those starting states.

AddressEdit::update_friendinfo stays 99.42105%, 38/38 instructions. The remaining difference is still the order of wcsncpy source r4 and destination r3 setup. Six new scene/cache/index/commit helper experiments, the checked named-local seed and three new full searches with the declaration-parser repair did not change it. Earlier f5 trials and completed searches were reused before this round. Additional cast, parameter-const, String member-copy, root-pane boundary and diagnostic-only tests from the updated lever pack found no exact result; their measurements are logged above.

The clean full gate recorded above validates the final source: GATE PASS, correct DOL SHA1, identical pools, zero regressions, zero added forbidden patterns and zero readability warnings. Only this evidence log changed after that gate. No source or header changes from the AddressEdit trials were retained.

## Gate after capacity-error recovery

The resumed branch is still agent/w1005/f5b at 944e82d9, with only this evidence log uncommitted. All 13 searches completed before the interruption. The current origin/main b7a912ce02ba00ac94d29a738c03473cd93490f1 has no changes to the four owned source/header paths since base 491bba6a. No branch movement or source change was needed.

At the user's request, repeated the clean full gate with both owned units and --base 491bba6a. The fresh gate passes, so the source match and this evidence log are retained.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 23988/23988 data 1964/1964 functions 101/101 fuzzy 100.0000 linked code 0
[src/scene/address/iplAddress] instruction-exact functions: 101/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 100.0
[src/scene/address/iplAddress]   section .rodata size 24 match 100.0
[src/scene/address/iplAddress]   section .sbss size 8 match 100.0
[src/scene/address/iplAddress]   section .sdata size 16 match 100.0
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 100.0
[src/scene/address/iplAddress] baseline: code 22908/23988 data 1964 functions 100 fuzzy 99.9291
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 23344/27112 data 2560/2560 functions 91/94 fuzzy 99.5528 linked code 0
[src/scene/address/iplAddressEdit] instruction-exact functions: 91/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 100.0
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 99.55282
[src/scene/address/iplAddressEdit]   below 100: create__Q33ipl5scene11AddressEditFv 97.5561
[src/scene/address/iplAddressEdit]   below 100: get_friendinfo__Q33ipl5scene11AddressEditFv 88.03571
[src/scene/address/iplAddressEdit]   below 100: update_friendinfo__Q33ipl5scene11AddressEditFv 99.42105
[src/scene/address/iplAddressEdit] baseline: code 23344/27112 data 2560 functions 91 fuzzy 99.5528
regressions vs baseline: 0
global matched_code_percent: 92.65446 -> 92.69051
global fuzzy_match_percent: 99.77653 -> 99.77708
global complete_code_percent: 76.20227 -> 76.20227
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Fresh progress/report generation after the recovery gate confirms the four target scores: 100.0, 97.5561, 88.03571 and 99.42105. DOL SHA1 is unchanged. Every open function has more than three distinct compiled source-level attempts; the archive contains 119 successful manual measurements and 3363 source-search trials across 13 completed runs. Final git diff --check passes. Only the evidence log changed after this gate.
