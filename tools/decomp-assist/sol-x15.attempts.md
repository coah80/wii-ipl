# sol-x15 ATERMi_AutoConfigThread

Branch agent/w1008/data-d3-j, baseline 9321a926. Owned source src/scene/setting/ATERM.c.

Read sol-common, brief-v2, levers, prior ATERM logs, and orch-aterm-autoconfig.md before trials. Baseline pools identical, zero strings. Function 94.75%, 3/40 differing instructions. ATERM 20/26 exact, code 12200/19204, data 18864/18864.

| Trial | Result | Other functions | Source SHA256 prefix |
| --- | --- | --- | --- |
| 01-readable | 94.75%, 3 differing, 40/40 instructions | unchanged | 831dec15aef3 |
| 02-report-state-args | 88.625%, 20 differing, 42/40 instructions | unchanged | 5b9b672537fe |
| 03-completion-state-args | 88.625%, 20 differing, 42/40 instructions | unchanged | 3b406a9e8504 |
| 04-completion-status-args | 87.75%, 10 differing, 40/40 instructions | unchanged | 544e37b2e460 |
| 05-completion-aggregate | Compile rejected, MWCC C dynamic aggregate initializer is not a constant expression | unchanged | 05445452803c |
| 06-local-aggregate | Compile rejected, MWCC C dynamic aggregate initializer is not a constant expression | unchanged | ee4701aa576f |
| 07-state-from-aggregate | Compile rejected, MWCC C dynamic aggregate initializer is not a constant expression | unchanged | e1aa84f37e70 |
| 08-completion-three-args | 87.75%, 10 differing, 40/40 instructions | unchanged | 7584ff68717f |
| 09-completion-time-middle | 87.75%, 10 differing, 40/40 instructions | unchanged | 38f0dbca8d95 |
| 10-completion-time-first | 87.75%, 10 differing, 40/40 instructions | unchanged | 954a9a688612 |
| 11-completion-result-first | 87.75%, 10 differing, 40/40 instructions | unchanged | 8e61e54b289a |
| 12-completion-const-return | 87.75%, 10 differing, 40/40 instructions | unchanged | 15722d7eb4c6 |
| 13-completion-const-reported | 87.75%, 10 differing, 40/40 instructions | unchanged | 9ce069cbc138 |
| 14-completion-state-declared-last | 87.75%, 10 differing, 40/40 instructions | unchanged | 8f099e2f77cc |
| 15-completion-assigned-state | 87.75%, 10 differing, 40/40 instructions | unchanged | 166049ed8b6a |
| 16-deadline-before-completion | 94.25%, 7 differing, 40/40 instructions | unchanged | ad71a24a281c |
| 17-completion-named-sentinel | 87.75%, 10 differing, 40/40 instructions | unchanged | 1ff1a2596589 |
| 18-completion-pointer | 94.25%, 7 differing, 40/40 instructions | unchanged | e9ba48ff3758 |
| 19-completion-pointer-deadline | 87.75%, 10 differing, 40/40 instructions | unchanged | 3da6b047b91d |
| 20-report-named-state | 94.75%, 3 differing, 40/40 instructions | unchanged | d883e434ed7e |
| 21-report-global-state | 94.75%, 3 differing, 40/40 instructions | unchanged | 20856d20d55d |
| 22-chained-state | 94.75%, 3 differing, 40/40 instructions | unchanged | 5ee804fb6b9b |
| 23-chained-select | 94.0%, 9 differing, 40/40 instructions | unchanged | 28c944e1b6b3 |
| 24-progress-macro | 94.75%, 3 differing, 40/40 instructions | unchanged | 74121dd6ef4e |
| 25-progress-return-aggregate | 77.625%, 25 differing, 43/40 instructions | unchanged | f0f0d22caef9 |
| 26-progress-return-after-state | 91.575%, 21 differing, 43/40 instructions | unchanged | 1c6a11ab59bd |
| 27-get-progress-state-param | 94.0%, 9 differing, 40/40 instructions | unchanged | f3a27668f96f |
| 28-get-progress-result-param | 94.0%, 9 differing, 40/40 instructions | unchanged | 5624532f42a1 |
| 29-get-completion-result-param | 94.25%, 7 differing, 40/40 instructions | unchanged | 4e62454cd179 |
| 30-progress-pointer-snapshot | 87.75%, 10 differing, 40/40 instructions | unchanged | d71b77bd441e |
| 31-progress-pointer-load-last | 94.75%, 3 differing, 40/40 instructions | unchanged | 88dd98d9cd90 |
| 32-progress-pointer-load-first | 85.2%, 10 differing, 40/40 instructions | unchanged | 879aa0bb3ea7 |
| 33-report-state-local-copy | 94.25%, 7 differing, 40/40 instructions | unchanged | b8848a306fe9 |
| 34-report-state-global-reload | 94.25%, 7 differing, 40/40 instructions | unchanged | cb1e4ad09655 |
| 35-completion-callback-param | 87.75%, 10 differing, 40/40 instructions | unchanged | 86ae07db931c |
| 36-completion-callback-first | 87.75%, 10 differing, 40/40 instructions | unchanged | a093a81864a2 |
| 37-completion-callback-global-result | 94.75%, 3 differing, 40/40 instructions | unchanged | 35c8192d9e95 |
| 38-global-result-select | 66.325%, 37 differing, 37/40 instructions | unchanged | 877456206a39 |
| 39-progress-deadline-macro | 94.75%, 3 differing, 40/40 instructions | unchanged | 9c64104abc48 |
| 40-progress-shared-inline | 94.75%, 3 differing, 40/40 instructions | unchanged | 39bec75fdec5 |
| 41-shared-sibling-inline | 94.75%, 3/40 differing | ATERMRunConfigProtocol 92.100945 -> 92.08623; ATERMi_ApConfigEnd 100.0 -> 99.84496 | measured full unit |

## Backend captures

- Readable baseline: /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/ATERMi_AutoConfigThread-20261008-215834. Backend-01 orders addi/subfic/nor/li/srawi/lwz. NOR r43 gets r0, gAtermResult load r48 gets r0. Their live ranges do not interfere. regsim reproduces 17/17 registers. Active tie values are compiler temporaries, so named-local declaration order cannot directly reorder them.
- Completion helper with reported-result parameter: /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/ATERMi_AutoConfigThread-20261008-215954. Backend-01 still orders addi/subfic/nor/li/srawi/lwz. The helper gives reportedResult the early inline-argument register r34, colored r5, while the sentinel r47 gets r0 and the NOR r44 gets r3. It fixes the NOR destination but changes the sentinel/state/result register assignments and produces 10 differences. Argument permutations, const parameters, local declaration placement, and a named sentinel do not solve it.
- Shared helper capture: /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/ATERMi_AutoConfigThread-20261008-220248. Backend-01 still orders addi/subfic/nor/li/srawi/lwz, with the same virtual registers as the readable baseline. Sharing the helper does not move the result load before the NOR.
- Shared progress helper trial 41 replaces four sibling report blocks and the completion report. AutoConfigThread remains at 3/40. ATERMi_ApConfigEnd drops from exact to 99.84496%, and RunConfigProtocol changes from 92.100945% to 92.08623%. Reject the helper and restore all siblings.

## Retained change

Replace the hand-expanded equality mask and arithmetic shift with completedState = (result == 1) ? 6 : 7. Keep deadline/state/progress store order. This compiles to the same function instructions as the initial source and leaves every ATERM function score unchanged. No exact gain.

Final independent comparison recompiles the original committed source into /tmp/sol-x15-baseline. Every allocated ELF section and every relocation resolved to section/value or external symbol is identical to the readable replacement. This proves every sibling function and unit code/data are unchanged, beyond unchanged fuzzy scores. Final pool check identical, ctxdiff 3 differences with 40/40 instructions, focused source diff clean.

## Final gate

Command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/setting/ATERM --quick

Full 43U build passes. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Pools identical. Unit exact functions 20/26 before and after, matched code 12200/19204, matched data 18864/18864, fuzzy 98.20204%. Regressions 0, forbidden patterns 0, readability warnings 0. Gate baseline is ancestor 22e6bbed, one commit before HEAD; the separate current-HEAD unit baseline and allocated-section/relocation comparison also prove zero drops.

GATE PASS

Readability-only source commit cdf7c17c. Exact matching remains open after 41 source candidates, including three rejected aggregate initializers. The retained ternary replaces the hand-expanded comparison without changing executable code or data.
