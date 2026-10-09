# sol-m7 BS2Mach max attempts

Worktree data-d7, branch agent/w1009/bs2-max. Clean starting HEAD and freshly fetched origin/main e6837211c118a183b9b34332e5e94cedd76abfa7. Required first full Ninja build passed and checked main.dol against 26116613f624061ba99c8d1a299aaa6efa85670d. Baseline 27/29 exact functions, code 7596/16980, data 158528/158528. CheckBS2CommandStatus 2/406 differing; BS2Tick 71/1940. Both sizes equal target. Pool identical 91/91.

Read sol-common, brief-v2, all levers through 34, AGENTS, unslop and writing-for-agents. Read a96d1422:sol-b1.attempts.md, 6feef7a9:sol-y2.attempts.md, relevant effort-policy entries and archived BS2Mach, big1, allhands-bs2-tick, data-d13, agg, da3, fz1, ult13, lv19, sol-high rounds, opus-bs2, sol-bs2 and sol-tiny logs. Read the saved sol-b1 and sol-y2 diffs. The old 60-difference source uses loaderRead; that carrier is excluded. Current main has three independent loader outputs, without the earlier branch-scoped IRQ change or flag qualifiers.

## Earlier work I will not repeat

- Completion-before-length, sibling explicit addition, parenthesized/commuted sums, literal multiply/round forms and primitive completion/count/cache signedness. These preserve 2 differences or worsen them to 4-11.
- Ordinary const TOC casts, global TOC pointer types, count snapshots, shared rounded-size caching, count/size accessors and whole cache-account helpers. Target recomputes the size in the write branch. The user-requested shared-size lead is already disproved by these captures; any new test must preserve the second computation.
- Completion bitfield/aggregate/one-field wrappers, use-site volatility, dummy values, declaration-only permutations, broad flag volatility or optimization sweeps. Completion is only used here; its callback updates the already-volatile NandPending.
- Ordinary boot/device helpers, merging the device state tail without a new explanation for the two lost base loads, console-class bitfields, IOS word snapshots, title-word overlays, banner snapshots, cover-delay locals and interrupt/output declaration permutations.
- Carrier structs, raw offset casts, source padding, forced lifetimes, assembly, artificial helper outputs or semantic changes. Existing BS2StartGame/BS2StartGCGame and all data sections remain protected.

## Acceptance and records

Each trial uses the unit's native compiler command and records both requested functions, all other function regressions and data. Require equal instruction counts, zero differences, exact-name objdiff 100%, identical pool and readable source. Commit each new exact function. Save best non-exact source outside the repo, restore experiments and run the requested final quick gate once. Matching is unchanged unless all 29 functions and all owned sections are exact and the linked DOL passes.

## Backend baseline

Fresh CheckBS2CommandStatus capture: /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/sol-m7-command-base. Inspect B44 before allocation for the completion-store/count-shift ordering before selecting new source shapes.

## Trials

- 1. native-command-control: command [2, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-001.c.
- 2. chain-pending-from-completion-before: command [4, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.48276]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-002.c.
- 3. chain-completion-from-pending-before: command [4, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.48276]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-003.c.
- 4. chain-pending-from-completion-after: command [12, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 98.5468]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-004.c.
- 5. chain-completion-from-pending-after: command [12, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 98.5468]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-005.c.
- 6. count-argument-prepare-write-u32: command [12, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 98.17734]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-006.c.
- 7. count-argument-prepare-write-const u32: command [12, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 98.17734]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-007.c.
- 8. count-argument-prepare-write-unsigned int: command [12, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 98.17734]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-008.c.
- 9. count-argument-prepare-write-const unsigned int: command [12, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 98.17734]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-009.c.
- 10. cache-add-count-and-length-argument-u32 count, u32 cacheLength: command [6, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.445816]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-010.c.
- 11. cache-add-count-and-length-argument-u32 cacheLength, u32 count: command [6, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.445816]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-011.c.
- 12. alignment-inline-direct-u32: command [9, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.37192]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-012.c.
- 13. alignment-inline-updated-u32: command [11, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.34729]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-013.c.
- 14. alignment-inline-local-u32: command [9, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.37192]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-014.c.
- 15. alignment-inline-direct-uint: command [9, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.37192]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-015.c.
- 16. alignment-inline-updated-uint: command [11, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.34729]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-016.c.
- 17. cache-byte-size-arguments-u32 cacheLength, u32 size: command [6, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.445816]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-017.c.
- 18. cache-byte-size-arguments-u32 size, u32 cacheLength: command [6, 406, 406], Tick [71, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'CheckBS2CommandStatus': [99.50739, 99.445816]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-018.c.
- 19. historical-flag-banner-seed-on-current-carrier-free-source: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-019.c.
- 20. reuse-current-time-as-elapsed: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-020.c.
- 21. direct-clock-call-in-cover-test: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-021.c.
- 22. clock-in-left-subtraction-after-stamp: command [2, 406, 406], Tick [66, 1940, 1940]; exact 27/29; data 158528/158528; regressions {'BS2Tick': [98.799484, 98.56237]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-022.c.
- 23. unsigned-clock-case-local: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-023.c.
- 24. signed-clock-case-local: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-024.c.
- 25. timestamp-disjoint-word-add: command [2, 406, 406], Tick [224, 1942, 1940]; exact 27/29; data 155504/158528; regressions {'BS2Tick': [98.799484, 98.69072]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-025.c.
- 26. timestamp-low-word-first-or: command [2, 406, 406], Tick [62, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-026.c.
- 27. timestamp-low-word-first-add: command [2, 406, 406], Tick [224, 1942, 1940]; exact 27/29; data 155504/158528; regressions {'BS2Tick': [98.799484, 98.69072]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-027.c.
- 28. timestamp-high-word-product: command [2, 406, 406], Tick [224, 1942, 1940]; exact 27/29; data 155504/158528; regressions {'BS2Tick': [98.799484, 98.69072]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-028.c.
- 29. elapsed-helper-call-and-subtract-return: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-029.c.
- 30. elapsed-helper-call-named-instant-return: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-030.c.
- 31. elapsed-helper-call-updated-instant-return: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-031.c.
- 32. device-state-ready-early-exit-separate-transitions: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-032.c.
- 33. device-state-ready-early-exit-shared-transition: command [2, 406, 406], Tick [1703, 1938, 1940]; exact 27/29; data 155504/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-033.c.
- 34. full-audio-configuration-helper-const : command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-034.c.
- 35. full-audio-configuration-helper-: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-035.c.
- 36. toc-local-same-source-before-report: command [2, 406, 406], Tick [56, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-036.c.
- 37. toc-report-count-real-local: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-037.c.
- 38. toc-publication-and-report-helper: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-038.c.
- 39. ios-publication-real-helper-scalar-halves: command [2, 406, 406], Tick [60, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-039.c.
- 40. reset-chain-forward: command [2, 406, 406], Tick [56, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-040.c.
- 41. reset-chain-reverse: command [2, 406, 406], Tick [58, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-041.c.
- 42. real-partition-only-reset-helper-both-init-paths: command [2, 406, 406], Tick [1866, 1936, 1940]; exact 27/29; data 155504/158528; regressions {'BS2Tick': [98.799484, 98.46546]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-042.c.
- 43. progress-local-reset-helper: command [2, 406, 406], Tick [63, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-043.c.
- 44. progress-absolute-reset-helper: command [2, 406, 406], Tick [63, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-044.c.
- 45. current-best-graph-revalidate-case-scoped-loader-irq: command [2, 406, 406], Tick [52, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-045.c.
- 46. ios-u64-by-value-helper-u64-low-first: command [2, 406, 406], Tick [55, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-046.c.
- 47. ios-u64-by-value-helper-u64-named-high: command [2, 406, 406], Tick [55, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-047.c.
- 48. ios-u64-by-value-helper-const u64-low-first: command [2, 406, 406], Tick [55, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-048.c.
- 49. ios-u64-by-value-helper-const u64-named-high: command [2, 406, 406], Tick [55, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-049.c.
- 50. delay-scalar-arguments-u32 milliseconds, u32 frequency-frequency-left: command [2, 406, 406], Tick [56, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-050.c.
- 51. delay-scalar-arguments-u32 milliseconds, u32 frequency-duration-left: command [2, 406, 406], Tick [57, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-051.c.
- 52. delay-scalar-arguments-u32 frequency, u32 milliseconds-frequency-left: command [2, 406, 406], Tick [56, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-052.c.
- 53. delay-scalar-arguments-u32 frequency, u32 milliseconds-duration-left: command [2, 406, 406], Tick [57, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-053.c.
- 54. audio-configuration-helper-pre-reset-stream-read-const : command [2, 406, 406], Tick [53, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-054.c.
- 55. audio-configuration-helper-pre-reset-stream-read-: command [2, 406, 406], Tick [53, 1940, 1940]; exact 27/29; data 158528/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-055.c.
- 56. banner-fit-check-helper-global-length-required-input: command [2, 406, 406], Tick [646, 1942, 1940]; exact 27/29; data 155504/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-056.c.
- 57. banner-fit-check-helper-length-and-required-inputs: command [2, 406, 406], Tick [646, 1942, 1940]; exact 27/29; data 155504/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-057.c.
- 58. banner-fit-check-helper-required-and-length-inputs: command [2, 406, 406], Tick [646, 1942, 1940]; exact 27/29; data 155504/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-058.c.
- 59. banner-fit-check-helper-required-local-rounding: command [2, 406, 406], Tick [646, 1942, 1940]; exact 27/29; data 155504/158528; regressions {}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-059.c.
- 60. capacity-and-completion-helper-extent-then-completion: command [246, 408, 406], Tick [71, 1940, 1940]; exact 27/29; data 155504/158528; regressions {'CheckBS2CommandStatus': [99.50739, 98.12562]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-060.c.
- 61. capacity-and-completion-helper-completion-then-extent: command [246, 408, 406], Tick [71, 1940, 1940]; exact 27/29; data 155504/158528; regressions {'CheckBS2CommandStatus': [99.50739, 98.12562]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-061.c.
- 62. capacity-and-completion-helper-explicit-sum-then-completion: command [246, 408, 406], Tick [71, 1940, 1940]; exact 27/29; data 155504/158528; regressions {'CheckBS2CommandStatus': [99.50739, 98.12562]}; POOL IDENTICAL up to 91 (mine=91 base=91); source /tmp/sol-m7-062.c.

## Results and private source review

62 distinct full-source candidates compiled successfully, including the native control and historical-seed revalidation. CheckBS2CommandStatus remains 2/406. Chained flags, count/byte arguments, alignment-only inline boundaries and combined capacity checks either preserve the shift/store order or regress code/data. The original source is the best command-status version. No completion volatility, count wrapper, shared cached length or optimization directive is justified.

Tick seed revalidation on the current carrier-free main reaches 60/1940 using the historical PartitionOpen/LoadingTitle qualifiers and banner-address snapshot. A new real dataToc local fixes four instructions at the second TOC publication/report, reaching 56. Revalidating the old branch-scoped IRQ shape on this new graph reaches 52; both three-output loader ABIs and every stack slot now remain target-like. The previous 70-difference result used a different scalar-output order. This is a combination on current main, not a new IRQ-scoping idea.

The private diff preserves the loaderAddress/loaderLength/loaderOffset declarations and the existing readAddress publication. It caches the actual second TOC pointer, leaves the published DataToc write and two report calls in their original order, and computes exactly the same next cache-line address before BannerLength and BannerBuffer publication. PartitionOpen and LoadingTitle use the historical definition-level qualifiers, with no use-site cast. There is no carrier, helper, new assembly, padding, forced lifetime, uninitialized read or new code comment in the saved source.

Private best: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-m7.BS2Mach.diff, source SHA256 9fb99a5dc54fb84de41d37c6f5cc8412a96ca2428d9b1cde41c2b0df3f8f63a7. Exact-name objdiff Tick 98.799484 -> 99.18144; command unchanged 99.50739. All 27 previously exact functions unchanged, code 7596/16980 and data 158528/158528; all four data sections 100%, pool identical 91/91. Tick is 52/1940 differing with equal size, so it is not exact and is not retained in the repository. Configure remains NonMatching.

IOS value helpers, full audio helpers, clock-expression and time-helper shapes, reset chains and real reset helpers, and banner-capacity predicates fail to improve 52. The banner predicates and cache-capacity helper each add two instructions and lose .data matching despite some favorable fuzzy scores. They are rejected.

## Fresh debugger evidence

Command capture is whole-object byte-identical to Ninja, SHA256 d917a5f2d38c805ffdccf417225b133d16da4b8fa8879c713f634acd356c1bbc. regsim reproduces 126/126. B44 backend-00 places the completion store after CacheLength; backend-01 puts it after the count shift; backend-02/03/04 preserve the swap. There is no allocator register mismatch. These dumps show operation order, not the scheduler's actual dependency edges.

Tick seed capture /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/sol-m7-tick-seed is whole-object identical to an independent native compile of the exact same source filename and command, SHA256 3d8f55379ae2dc09cbadfb86d44a5e3288ca9d78e811b57eaf81eec11972cf42. Comparing initially with the identical source under a different temporary filename changed ELF metadata; the exact-input retry removes that ambiguity. regsim reproduces 848/848.

Best-52 capture /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/sol-m7-tick-best52 is whole-object byte-identical to the already scored native trial 45, SHA256 eff7671aff7fb6c002264442e104ef84631c9a5e07d1dcb9ab5fa835af3df426. regsim again reproduces 848/848. vmap2 uses a private object projection with this capture and the assigned retail target, without replacing the worktree object. Both nested IRQ values now allocate target r26. B569 clock wants are v866=r6, v869=r8, v873=r8, v876=r7, v877=r7, v879=r7. These six are unnamed temporaries. B8's reset/flag ordering already differs before allocation. Remaining blocks include device-code base sharing and transition layout, audio load/clear ordering, IOS half registers, banner comparison registers and restart/abort load/store ordering.

Restricted regsim search uses only declared source locals, excluding promoted globals such as PartitionCursor and leaving every unnamed clock temporary fixed. The best-52 graph reproduces 848/848. Two thousand tested numberings retain only the two already-correct IRQ wants out of eight; none fixes a clock want. No tested declaration reordering corrected the clock temporaries on this source graph. No declaration permutation is retained.

The native -MMD trials emitted 62 task-owned .d files at the assigned worktree root. They were moved to /tmp/sol-m7-native-dependency-NNN.d. The private harness now uses the debugger's documented -gccdepends output option. Only the attempt log remains changed in the repository. All other worktrees and shared tools were read-only; generated debugger evidence lives in the debugger workspace.

## Final gate on restored repository source

The required quick gate ran once after the private best was saved. Repository source remained unchanged throughout the trials. This gate validates the original repository source, not the private 52-difference candidate. Raw output /tmp/sol-m7-gate.log:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 7596/16980 data 158528/158528 functions 27/29 fuzzy 99.4042 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 27/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match 100.0
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 99.40424
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 99.50739
[src/BS2/BS2Mach]   below 100: BS2Tick 98.799484
[src/BS2/BS2Mach] baseline: code 7596/16980 data 158528 functions 27 fuzzy 99.4042
regressions vs baseline: 0
global matched_code_percent: 98.11310 -> 98.11310
global fuzzy_match_percent: 99.92565 -> 99.92565
global complete_code_percent: 91.03011 -> 91.03011
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

No new exact function. Final repository unit remains 27/29 exact, code 7596/16980, data 158528/158528 and unlinked. CheckBS2CommandStatus remains 2/406; BS2Tick remains 71/1940 in the restored repository and 52/1940 only in the saved diff. Every data section is 100%. Private instruction audit also confirms all 27 objdiff-100 functions are instruction-exact.

Origin advanced during this run; src/BS2/BS2Mach.c and configure.py remain identical to the assigned source, verified against current origin/main. No push, PR, merge, rebase, header edit or Matching flip. Commit only this log.

## Round b, 2026-10-09: volatile proof audit and honest retained candidate

Assigned worktree `/mnt/drive2/projects/wii-ipl-workers/data-d7`, branch
`agent/w1009/bs2tick`, start and freshly fetched origin/main
`bbd98e1e4a09749183ca9dd2a8cc1a9b9a3586b5`. The initial requested full
`/home/cole/projects/tests/.venv/bin/ninja` passed before applying the private
candidate. Initial DOL SHA1 was `26116613f624061ba99c8d1a299aaa6efa85670d`.

Scope is this round's explicit instruction to commit an honest improvement
below 71 differing instructions with zero regressions. BS2Tick remains
NonMatching. A partial improvement is not an exact match or a linking gain.

Read the earlier log from `43228bbd`, opus-bs2's qualifier sweep,
sol-bs2's follow-on trials, the effort-policy entries and the supplied private
diff. This round revalidates that candidate and isolates its two qualifiers.
It does not repeat the clock, IOS helper, reset-helper, capacity-helper,
device-code or register-numbering searches already rejected above.

### PartitionOpen: both required proofs fail

`graphify explain PartitionOpen --graph
/mnt/drive2/projects/wiichannels/wii-ipl/graphify-out/graph.json` reports no
node. `rg -n -C 5 'PartitionOpen|LoadingTitle' src include libs` finds every
PartitionOpen write inside BS2Tick. The baseline source writes at lines
1678, 1845, 1865, 2104, 2149, 2225, 2247 and 2291. CheckDVDCommandStatus
only reads it. Neither BS2DVDCallback nor BS2NANDCallback writes it, and the
static variable has no other source references. This supplies no
callback, interrupt or other-thread writer.

The target relocation inventory confirms eight stores, all in BS2Tick, and
only two loads in the entire unit, one in each function. Instructions below
use target object .text offsets; `0(0)` is a relocatable operand whose
relocation resolves to PartitionOpen:

```text
CheckDVDCommandStatus
0x185c  lwz      r0, 0(0)     ; PartitionOpen
0x1860  cmpwi    r0, 0
0x1864  beq      0x1874

BS2Tick, case 0x40
0x40d0  lwz      r0, 0(0)     ; PartitionOpen
0x40d4  cmpwi    r0, 0
0x40d8  beq      0x40ec
0x40dc  li       r0, 0xf
0x40e0  stw      r3, 0(0)     ; PartitionOpen
0x40e4  stw      r0, 0(0)     ; State
```

There is no repeated load inside either function, so no back-to-back reread
without an intervening store or call. A better store schedule from vu32 does
not prove volatility. Drop this qualifier.

### LoadingTitle: writer found, required asynchronous provenance and reread absent

`graphify explain LoadingTitle --graph
/mnt/drive2/projects/wiichannels/wii-ipl/graphify-out/graph.json` resolves to
BS2StartLoadingTitle at src/BS2/BS2Mach.c:444, called by
Manager::loadLockedTitleAsync at src/system/iplBS2Manager.cpp:147.
Source inspection confirms the direct writer `LoadingTitle = 1` at baseline
BS2Mach.c:453. Its caller chain is ChannelTitle -> channel Manager -> BS2
Manager -> BS2StartLoadingTitle. The Async name initiates loading; it does
not establish that this assignment runs on another thread. BS2Tick runs from
BS2 Manager::update at iplBS2Manager.cpp:42. Every other LoadingTitle write
is a clear inside BS2Tick. No callback or interrupt writer appears in the
complete source search, and this round finds no proof of a different thread.

The target has one store in BS2StartLoadingTitle and four stores in BS2Tick.
Its only two LoadingTitle loads are these separate switch cases:

```text
BS2StartLoadingTitle
0x974   stw      r0, 0(0)     ; LoadingTitle

BS2Tick, case 0xf
0x2b0c  lwz      r0, 0(0)     ; LoadingTitle
0x2b10  cmpwi    r0, 0
0x2b14  beq      0x2b24
0x2b18  li       r0, 0x46
0x2b1c  stw      r0, 0(0)     ; State
0x2b20  b        0x4230

BS2Tick, case 0x30
0x3b50  lwz      r0, 0(0)     ; LoadingTitle
0x3b54  cmpwi    r0, 0
0x3b58  bne      0x3b68
0x3b5c  li       r0, 0x45
0x3b60  stw      r0, 0(0)     ; State
```

The two loads belong to distinct dispatch paths. They are not successive
reads on one path and do not demonstrate a value a non-volatile declaration
would CSE. Drop this qualifier too. The earlier claim that these qualifiers
were justified is not accepted by this audit.

### Measured controls

Each row was compiled with the assigned 43U Ninja object command, then
checked with pool_diff before its exact-name objdiff and instruction audit.

| Candidate | BS2Tick differing / source / target insns | BS2Tick objdiff | Other 27 exact |
|---|---|---|---|
| Baseline | 71 / 1940 / 1940 | 98.799484 | 27 unchanged |
| Saved diff, both vu32 | 52 / 1940 / 1940 | 99.18144 | 27 unchanged |
| Saved diff, LoadingTitle only vu32 | 55 / 1940 / 1940 | 99.078354 | 27 unchanged |
| Saved diff, PartitionOpen only vu32 | 54 / 1940 / 1940 | 99.078354 | 27 unchanged |
| Honest diff, both remain u32 | 57 / 1940 / 1940 | 98.97526 | 27 unchanged |

Every compiled control preserves all 27 exact functions byte-for-byte and
instruction-exact against the target. Their resolved call/data relocations
are unchanged against the fresh baseline. Comparing raw generated literal
names initially flagged @3709 -> @3712; resolving to section and offset
confirms the same .data address. Allocated .bss/.data/.sbss/.sdata bytes and
sizes are identical to baseline for every row. String pools remain 91/91.
CheckBS2CommandStatus remains 2/406 and 99.50739 in every row. There are no
per-function objdiff regressions.

### Retained source and review

Keep both flags as their original static u32 definitions. Retain only the
ordinary second-TOC pointer local, a readInterruptsEnabled local scoped to
each apploader case, and the named aligned bannerAddress calculation.
The TOC local is exactly the second DVDGameTOC element previously read.
DataToc publication and both reports retain their order and values. Each IRQ
local still receives OSDisableInterrupts before OSRestoreInterrupts; both
three-output loader ABIs and readAddress publication remain unchanged.
bannerAddress uses the same next-cache-line expression and reads the same
BannerAllocation without a call or possible write before publication.
No new comment, qualifier, helper, carrier, pragma, assembly or header edit.

Retained unit is 27/29 exact, code 7596/16980, data 158528/158528 and
fuzzy 99.48457. All four data sections are 100%. BS2Tick is 57/1940 with
ctxdiff `diffs 57`, equal size 0x1e50, and objdiff 98.97526. This is the
explicitly requested honest partial gain of 14 instructions, not a match.

Private audit files use `/tmp/sol-m7-b-*`, including the baseline report,
four candidate objects/reports/results, exact-function audit and complete
target flag relocation inventory. Final gate and commit evidence follow.

### Final gate on the retained honest source

Command: `python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/BS2/BS2Mach --quick`. The required initial full build had already passed. This gate validates the retained 57-difference candidate, not restored baseline source.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 7596/16980 data 158528/158528 functions 27/29 fuzzy 99.4846 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 27/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match 100.0
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 99.48457
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 99.50739
[src/BS2/BS2Mach]   below 100: BS2Tick 98.97526
[src/BS2/BS2Mach] baseline: code 7596/16980 data 158528 functions 27 fuzzy 99.4042
regressions vs baseline: 0
global matched_code_percent: 98.11310 -> 98.11310
global fuzzy_match_percent: 99.92995 -> 99.93040
global complete_code_percent: 91.03011 -> 91.03011
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

An additional comparison against this round's freshly generated full baseline report covers all 1028 units. Only main/src/BS2/BS2Mach changes; every matched-code/data/function/link measure and every per-function score has zero regressions. Both flag definitions are still static u32. git diff --check passes. Commit the honest source and this log locally as requested; no push, PR, merge, rebase, Matching flip or other-worktree edit.
