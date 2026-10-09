# g-cardseq attempts

Assigned sol-med, agent/w1009/g-cardseq, HEAD 54ca052b, identical to fetched origin/main at start. Existing untracked perm5 and swe2ifd0 logs remain untouched. Read opus-common fully before repository work, local AGENTS.md, unslop, writing-for-agents, relevant sol-x3 rounds and o2-cardseq-sdmem histories. Used graphify read-only to locate the thread's calls; live source and target object establish all measurements.

Acceptance requires both owned functions to have equal size, zero instruction differences and exact-name objdiff 100%, identical pool/data and no sibling regression. Flip configure.py only after the entire unit is exact, then require the target DOL SHA1 and final quick gate. Retain readable source, scoped optimizer pragmas or compiler intrinsics only when verified. The assigned task forbids carrier structs.

Fresh full 43U build passed and DOL checker passed. Baseline report has 28/30 exact functions, cardThreadMain 99.73422%, loadCardFileIcons 97.31445%, data 1496/1496. Pool identical at all 43 entries. Early single/pair optimizer sweep output is in /tmp/g-cardseq-combosweep.log. Trials compile private source/object files under /tmp/g-cardseq-trials using the live unit flags and check both owned functions, all 28 exact siblings and the pool including literal offsets.

The first five trial lines report raw allocated-data byte equality, which is false even on the unchanged baseline. These sections contain relocations and are not a valid direct retail-data comparison. Later trials explicitly check pool equality. The final objdiff report independently verifies every owned data section at 100%.

## Compiled trials

- baseline: thread 2/301, icons 126/512; exact siblings lost []; data equal False.
- reply-intrinsic-direct: thread 3/301, icons 126/512; exact siblings lost []; data equal False.
- reply-intrinsic-named: thread 3/301, icons 126/512; exact siblings lost []; data equal False.
- reply-intrinsic-assign: thread 3/301, icons 126/512; exact siblings lost []; data equal False.
- reply-intrinsic-shift-mask: thread 256/300, icons 126/512; exact siblings lost []; data equal False.
- intrinsic-opt_propagation-off: thread 32/301, icons 126/512; exact siblings lost []; pool equal True.
- intrinsic-opt_lifetimes-off: thread 124/302, icons 126/512; exact siblings lost []; pool equal True.
- intrinsic-opt_dead_code-off: thread 3/301, icons 126/512; exact siblings lost []; pool equal True.
- intrinsic-opt_dead_assignments-off: thread 3/301, icons 126/512; exact siblings lost []; pool equal True.
- intrinsic-ppc_iro_level-1: thread 197/303, icons 126/512; exact siblings lost []; pool equal True.
- intrinsic-opt_common_subs-off: thread 175/302, icons 126/512; exact siblings lost []; pool equal True.
- command-packet-opt_propagation-off: thread 32/301, icons 126/512; exact siblings lost []; pool equal True.
- command-packet-opt_lifetimes-off: thread 124/302, icons 126/512; exact siblings lost []; pool equal True.
- command-packet-opt_dead_code-off: thread 3/301, icons 126/512; exact siblings lost []; pool equal True.
- command-packet-opt_dead_assignments-off: thread 3/301, icons 126/512; exact siblings lost []; pool equal True.
- command-packet-ppc_iro_level-1: thread 197/303, icons 126/512; exact siblings lost []; pool equal True.
- command-packet-opt_common_subs-off: thread 175/302, icons 126/512; exact siblings lost []; pool equal True.
- image-transfer-before-sector: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- image-transfer-top-declared: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- image-transfer-after-sector-declared: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- comment-order-address-base-offset-readSize-sectorSize-result: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- comment-order-result-sectorSize-readSize-offset-base-address: thread 2/301, icons 119/512; exact siblings lost []; pool equal True.
- comment-order-sectorSize-readSize-offset-base-address-result: thread 2/301, icons 123/512; exact siblings lost []; pool equal True.
- comment-order-offset-readSize-base-address-sectorSize-result: thread 2/301, icons 123/512; exact siblings lost []; pool equal True.
- offset-unsigned: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- offset-mask: thread 2/301, icons 477/511; exact siblings lost []; pool equal True.
- offset-split: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- offset-after-format: thread 2/301, icons 249/512; exact siblings lost []; pool equal True.
- inline-body-readCardImages: compile failed, see /tmp/g-cardseq-trials/inline-body-readCardImages.compile.txt
- inline-body-readCardComment: compile failed, see /tmp/g-cardseq-trials/inline-body-readCardComment.compile.txt
- inline-body-loadCardIconImages: thread 2/301, icons 241/512; exact siblings lost []; pool equal True.
- comment-seven-address-result-base-readSize-end-fileSize-offset: thread 2/301, icons 108/512; exact siblings lost []; pool equal True.
- comment-seven-offset-fileSize-end-readSize-base-result-address: thread 2/301, icons 123/512; exact siblings lost []; pool equal True.
- comment-seven-result-offset-readSize-base-address-fileSize-end: thread 2/301, icons 119/512; exact siblings lost []; pool equal True.
- comment-seven-result-end-fileSize-readSize-offset-base-address: thread 2/301, icons 117/512; exact siblings lost []; pool equal True.
- image-transfer-parent-top: thread 2/301, icons 117/512; exact siblings lost []; pool equal True.
- image-transfer-parent-before-offset: thread 2/301, icons 117/512; exact siblings lost []; pool equal True.
- image-transfer-parent-after-offset: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- comment-exact-transfer-parent: thread 2/301, icons 99/512; exact siblings lost []; pool equal True.
- reply-new-assign-arg: thread 3/301, icons 126/512; exact siblings lost []; pool equal True.
- image-order-iconImageSize-hasTlut-icon-iconCount-shift: thread 2/301, icons 86/512; exact siblings lost []; pool equal True.
- reply-new-compound-mask: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- image-order-iconImageSize-icon-hasTlut-iconCount-shift: thread 2/301, icons 86/512; exact siblings lost []; pool equal True.
- reply-new-const-packet: thread 3/301, icons 126/512; exact siblings lost []; pool equal True.
- image-order-iconImageSize-paletteSize-icon-hasTlut-iconCount-shift: thread 2/301, icons 29/512; exact siblings lost []; pool equal True.
- reply-new-inline-union: thread 3/301, icons 126/512; exact siblings lost []; pool equal True.
- image-order-iconImageSize-paletteSize-hasTlut-icon-iconCount-shift: thread 2/301, icons 29/512; exact siblings lost []; pool equal True.
- image-order-iconCount-shift-hasTlut-iconImageSize-icon: thread 2/301, icons 93/512; exact siblings lost []; pool equal True.
- image-order-shift-iconCount-hasTlut-iconImageSize-icon: thread 2/301, icons 99/512; exact siblings lost []; pool equal True.
- image-29-order-iconImageSize-paletteSize-icon-hasTlut-shift-iconCount: thread 2/301, icons 40/512; exact siblings lost []; pool equal True.
- image-29-order-iconImageSize-paletteSize-icon-iconCount-hasTlut-shift: thread 2/301, icons 73/512; exact siblings lost []; pool equal True.
- image-29-order-iconImageSize-paletteSize-hasTlut-shift-iconCount-icon: thread 2/301, icons 40/512; exact siblings lost []; pool equal True.
- image-29-order-paletteSize-iconImageSize-icon-hasTlut-iconCount-shift: thread 2/301, icons 38/512; exact siblings lost []; pool equal True.
- image-29-order-iconImageSize-icon-paletteSize-hasTlut-iconCount-shift: thread 2/301, icons 29/512; exact siblings lost []; pool equal True.
- image-29-transfer-sum-parentheses: thread 2/301, icons 29/512; exact siblings lost []; pool equal True.
- image-29-transfer-offset-first: thread 2/301, icons 29/512; exact siblings lost []; pool equal True.
- image-29-icon-init-shift-first: thread 2/301, icons 26/512; exact siblings lost []; pool equal True.
- image-29-icon-increment-shift-first: thread 2/301, icons 29/512; exact siblings lost []; pool equal True.
- image-29-animation-speed-assignment: thread 2/301, icons 29/512; exact siblings lost []; pool equal True.
- image-29-animation-max-compound: thread 2/301, icons 24/512; exact siblings lost []; pool equal True.
- image-29-init-iconCount-hasTlut-iconImageSize: thread 2/301, icons 29/512; exact siblings lost []; pool equal True.
- image-29-init-iconCount-iconImageSize-hasTlut: thread 2/301, icons 28/512; exact siblings lost []; pool equal True.
- image-29-init-hasTlut-iconCount-iconImageSize: thread 2/301, icons 27/512; exact siblings lost []; pool equal True.
- image-29-init-hasTlut-iconImageSize-iconCount: thread 2/301, icons 24/512; exact siblings lost []; pool equal True.
- image-29-init-iconImageSize-iconCount-hasTlut: thread 2/301, icons 28/512; exact siblings lost []; pool equal True.
- image-29-init-iconImageSize-hasTlut-iconCount: thread 2/301, icons 26/512; exact siblings lost []; pool equal True.
- image-29-second-named-count-first: thread 2/301, icons 211/512; exact siblings lost []; pool equal True.
- image-29-second-named-shift-first: thread 2/301, icons 210/512; exact siblings lost []; pool equal True.
- image-29-second-named-top: thread 2/301, icons 211/512; exact siblings lost []; pool equal True.
- image-combined-init-max: thread 2/301, icons 19/512; exact siblings lost []; pool equal True.
- image-combined-count-control: thread 2/301, icons 16/512; exact siblings lost []; pool equal True.
- image-combined-shift-control: thread 2/301, icons 19/512; exact siblings lost []; pool equal True.
- image-combined-while-count: thread 2/301, icons 19/512; exact siblings lost []; pool equal True.
- image-combined-while-shift: thread 2/301, icons 19/512; exact siblings lost []; pool equal True.
- image-combined-step-plain: thread 2/301, icons 19/512; exact siblings lost []; pool equal True.
- image-combined-init-and-step-shift-first: thread 2/301, icons 16/512; exact siblings lost []; pool equal True.
- image-combined-image-total-early: thread 2/301, icons 18/512; exact siblings lost []; pool equal True.
- image-combined-image-total-late: thread 2/301, icons 39/512; exact siblings lost []; pool equal True.
- compiler-GC-3.0a5: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- compiler-GC-3.0a3.4: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- compiler-GC-3.0a3.3: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- compiler-GC-3.0a3.2: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- compiler-GC-2.7: compile failed, see /tmp/g-cardseq-trials/compiler-GC-2.7.compile.txt
- flags--inline-deferred: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- flags--inline-noauto: thread 2/301, icons 126/512; exact siblings lost []; pool equal True.
- flags--O3-s: thread 297/303, icons 493/527; exact siblings lost ['sendCardCopyCmd__Q23ipl10memorycardFUcs', 'sendCardMoveCmd__Q23ipl10memorycardFUcs', 'sendCardDeleteCmd__Q23ipl10memorycardFUcs', 'pollCardSlot']; pool equal True.
- flags--O3-p: thread 1077/1081, icons 463/528; exact siblings lost ['sendCardCopyCmd__Q23ipl10memorycardFUcs', 'sendCardMoveCmd__Q23ipl10memorycardFUcs', 'sendCardDeleteCmd__Q23ipl10memorycardFUcs', 'sendCardThreadStopCmd__Q23ipl10memorycardFv', 'pollCardSlot', 'probeCard__Q23ipl10memorycardFv', 'initCardThread__Q23ipl10memorycardFv', 'refreshCardSlotInfo', 'markAllCardFilesDirty', 'handleCardMountResult', 'reportCardThreadError', 'sendCardSlotState', 'clearAllCardFileEntries', 'runCardMoveOrCopy']; pool equal False.
- flags--O4-p: thread 919/926, icons 349/513; exact siblings lost ['sendCardThreadStopCmd__Q23ipl10memorycardFv', 'pollCardSlot', 'probeCard__Q23ipl10memorycardFv', 'initCardThread__Q23ipl10memorycardFv', 'refreshCardSlotInfo', 'markAllCardFilesDirty', 'handleCardMountResult', 'reportCardThreadError', 'sendCardSlotState', 'clearAllCardFileEntries', 'runCardMoveOrCopy']; pool equal False.
- image-18-derived-shift: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-18-derived-shift-control-count: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-18-derived-count: thread 2/301, icons 317/520; exact siblings lost []; pool equal True.
- image-18-count-control-early-size: thread 2/301, icons 15/512; exact siblings lost []; pool equal True.
- image-18-second-step-init-early-size: thread 2/301, icons 15/512; exact siblings lost []; pool equal True.
- image-18-count-step-for: thread 2/301, icons 18/512; exact siblings lost []; pool equal True.
- image-18-shift-step-for: thread 2/301, icons 18/512; exact siblings lost []; pool equal True.
- image-2-count-after-first-store: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-count-before-animation-loop: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-count-first-loop-control: thread 2/301, icons 4/512; exact siblings lost []; pool equal True.
- image-2-count-first-uninitialized-decl: thread 2/301, icons 16/512; exact siblings lost []; pool equal True.
- image-2-count-store: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-index-store-reference: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-index-store-pointer: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-index-store-whole-reference: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-clear-animation-helper: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-lifetime-count-after-second-store: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-lifetime-count-from-dir-before-loop: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-lifetime-count-after-first-three-stores: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-first-index-only: thread 2/301, icons 51/512; exact siblings lost []; pool equal True.
- image-2-first-index-decl-top: thread 2/301, icons 51/512; exact siblings lost []; pool equal True.
- image-2-first-index-decl-loop: thread 2/301, icons 63/512; exact siblings lost []; pool equal True.
- image-2-animation-increment-shift-before-count: thread 2/301, icons 4/512; exact siblings lost []; pool equal True.
- image-2-animation-increment-postfix: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-animation-shift-derived: thread 2/301, icons 82/512; exact siblings lost []; pool equal True.
- image-2-type-iconCount-u32: thread 2/301, icons 302/508; exact siblings lost []; pool equal True.
- image-2-type-iconCount-long: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-shift-u32: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-shift-long: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-icon-u32: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-icon-long: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-imageSize-u32: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-imageSize-long: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-paletteSize-u32: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-paletteSize-long: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-iconImageSize-u32: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-iconImageSize-long: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-bannerImageSize-u32: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-type-bannerImageSize-long: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-index-row-local: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-index-array-local: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-index-array-reference: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-index-store-helper: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-stores-before-counter-inits: thread 2/301, icons 383/513; exact siblings lost []; pool equal True.
- image-2-first-store-after-shift: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-first-store-after-tlut: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-both-stores-before-count: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-count-object-pointer: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-count-object-reference: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-count-state-and-counter: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-count-state-and-counter-ref: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-animation-helper-iconCount-shift-icon: thread 2/301, icons 65/512; exact siblings lost []; pool equal True.
- image-2-tlut-init-with-decl: thread 2/301, icons 7/512; exact siblings lost []; pool equal True.
- image-2-animation-helper-shift-iconCount-icon: thread 2/301, icons 56/512; exact siblings lost []; pool equal True.
- image-2-image-init-with-decl: thread 2/301, icons 8/512; exact siblings lost []; pool equal True.
- image-2-animation-helper-icon-iconCount-shift: thread 2/301, icons 65/512; exact siblings lost []; pool equal True.
- image-2-count-init-with-decl: thread 2/301, icons 10/512; exact siblings lost []; pool equal True.
- image-2-shift-init-with-decl: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- reply-intrinsic-valid-type-u8: thread 3/301, icons 2/512; exact siblings lost []; pool equal True.
- reply-intrinsic-valid-type-s32: thread 3/301, icons 2/512; exact siblings lost []; pool equal True.
- reply-intrinsic-valid-type-BOOL: thread 3/301, icons 2/512; exact siblings lost []; pool equal True.
- reply-intrinsic-valid-assignment-after-report: thread 9/301, icons 2/512; exact siblings lost []; pool equal True.
- reply-intrinsic-valid-report-variable: thread 3/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-chain-count-then-store: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-chain-store-then-count: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-chain-shift-then-store: thread 2/301, icons 10/512; exact siblings lost []; pool equal True.
- image-2-chain-store-then-shift: thread 2/301, icons 10/512; exact siblings lost []; pool equal True.
- image-2-chain-size-then-store: thread 2/301, icons 5/512; exact siblings lost []; pool equal True.
- image-2-chain-store-then-size: thread 2/301, icons 5/512; exact siblings lost []; pool equal True.
- image-2-first-count-while: thread 2/301, icons 2/512; exact siblings lost []; pool equal True.
- image-2-first-count-for-assignment: thread 2/301, icons 4/512; exact siblings lost []; pool equal True.
- image-2-first-count-shift-begin: thread 2/301, icons 24/512; exact siblings lost []; pool equal True.
- image-2-first-count-shift-middle: thread 2/301, icons 21/512; exact siblings lost []; pool equal True.
- image-2-first-count-shift-end: thread 2/301, icons 21/512; exact siblings lost []; pool equal True.

## Retained source and remaining differences

Retained loadCardFileIcons is 512/512 instructions, 2 differences, exact-name objdiff 99.98047%, up from 126 differences and 97.31445%. cardThreadMain is unchanged at 301/301 instructions, 2 differences and 99.73422%. The unit remains 28/30 exact, code 6600/9852, data 1496/1496, fuzzy 99.96346%. No exact function or linked-byte gain is claimed. configure.py remains NonMatching.

The comment read now declares its real address, result, base, read size, end, file size and offset together before their original assignments. A replay of the fresh allocator capture found the necessary local order, and the compiled source matches the entire comment region. The image read's aligned transfer size is calculated by its caller and passed to readCardImages. Naming the total image size preserves the target addition order. Animation locals and zero initializers follow the measured order, and the frame-duration update uses compound assignment. The icon-format loop uses iconCount directly and derives its bit shift from iconCount * 2, eliminating the second loop's extra source counter. The overwritten initialization immediately before the for initializer was removed; the object remains byte-identical to the winning compiled trial.

The existing target-proven reserved-format palette path is preserved. Moving paletteSize out of the per-iteration scope gives the target's persistent register value across frames. No initializer or alternate reserved-format behavior was introduced. The original target proof and previously merged implementation are recorded in o2-cardseq-sdmem.attempts.md.

Fresh captures live under /tmp/g-cardseq-mwdbg/runs/icons-fresh, icons-29 and icons-2. The private launcher uses the previous Opus transport on port 9137, with the same unmodified compiler and real unit flags. Its outputs remain under /tmp/g-cardseq-mwdbg. Baseline regsim reproduces 375/375 virtual registers. Every allocated and relocation section of icons-2/unit.o equals the final independently built Ninja object.

Remaining icon differences are instruction 135 add r10,r4,r30 instead of add r4,r4,r30 and instruction 136 stb using that address register. In the final capture the first-store address v188 interferes with animation counter v84, whose required target color is r4. Moving initializers, field pointer/reference views, actual count-reset helpers, first-loop forms and chained assignments did not remove this overlap. Reordering the existing declarations cannot assign both interfering values r4. A new source shape must change this edge; the capture does not prove that such a shape is impossible.

The thread still differs at instructions 48 and 49. Its existing valid-first packet folds to li r4,256 followed by inserting command r19. Command-first bitfields and __rlwimi produce insertion into command r19 using the hoisted constant-one register, then copy to r4. Scoped propagation-off preserves the wanted validity r25 operand but leaves copy coalescing and other differences. Compiler versions GC/3.0a5 and 3.0a3.2 through 3.0a3.4 produce the same baseline; alternative inline modes do too. Lower optimization levels introduce regressions and were discarded. No thread edit or compiler setting is retained.

159 successfully compiled source/flag candidates were saved and scored. Two missing-helper diagnostic variants and the GC/2.7 trial failed compilation and were discarded. Each of two optimizer sweeps compiled the baseline, 15 single settings and 105 pairs; neither improves its seed. The second sweep's seed already has 2 icon differences. Two loop-update comma variants were diagnostics only and are excluded by the source policy. Every retained change is ordinary C++ with no carrier, assembly, dummy data, volatile cast, added code comment or unrelated edit.

Fresh pool comparison including literal offsets is identical at all 43 strings. ctxdiff independently confirms both remaining 2-difference streams. All four data sections are 100% in the live objdiff report. A separate whole-report comparison against the frozen beginning-of-run report finds zero code, data, function or link drops and no lost exact function. origin/main advanced during the run; this leaf stays on its assigned 54ca052b baseline without rebase or merge. Parent integration must repeat the gates on its current main.

## Final gate

The required final quick gate ran once and passed. The full 43U build succeeds, the DOL SHA1 is independently verified, baseline drops are zero, and the source scan reports zero forbidden additions and zero readability warnings. Final allocator replay reproduces 375/375 virtual registers. The report and object checks still show two nonexact functions; no Matching flip is justified.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/cardSequence/iplCardSequence] pool: IDENTICAL
[src/scene/cardSequence/iplCardSequence] objdiff: code 6600/9852 data 1496/1496 functions 28/30 fuzzy 99.9635 linked code 0
[src/scene/cardSequence/iplCardSequence] instruction-exact functions: 28/30
[src/scene/cardSequence/iplCardSequence]   section .bss size 16 match 100.0
[src/scene/cardSequence/iplCardSequence]   section .data size 1464 match 100.0
[src/scene/cardSequence/iplCardSequence]   section .sbss size 8 match 100.0
[src/scene/cardSequence/iplCardSequence]   section .sdata size 8 match 100.0
[src/scene/cardSequence/iplCardSequence]   section .text size 9852 match 99.96346
[src/scene/cardSequence/iplCardSequence]   below 100: cardThreadMain 99.73422
[src/scene/cardSequence/iplCardSequence]   below 100: loadCardFileIcons 99.98047
[src/scene/cardSequence/iplCardSequence] baseline: code 6600/9852 data 1496 functions 28 fuzzy 99.4093
regressions vs baseline: 0
global matched_code_percent: 99.20325 -> 99.20325
global fuzzy_match_percent: 99.97473 -> 99.97657
global complete_code_percent: 94.18519 -> 94.18519
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Only src/scene/cardSequence/iplCardSequence.cpp and this attempts log are retained for a local commit. Existing untracked perm5 and swe2ifd0 logs remain untouched. No push, PR, merge, rebase, subagent or other-worktree edit.
