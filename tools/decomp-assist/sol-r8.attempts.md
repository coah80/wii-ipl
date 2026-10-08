# sol-r8 modifier matching attempts

Assignment: rx1, agent/w1009/kbd-r. Own KBDSetModState and kbdProcMod in libs/RVL_SDK/src/kbd/kbd_lib.c. Starting HEAD and fetched origin/main are b1e911808f46a70edae7a457fd7a0673b83ee888. Worktree started clean. Full requested Ninja build passed before experiments. DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d.

Read sol-common.md, brief-v2.md, every lever through 32, local AGENTS.md, unslop and writing-for-agents. No worker delegation. All experiments use rx1 or private /tmp/sol-r8-* files. Other worktrees are read only.

## History and excluded repeats

Collected effort-policy.txt entries 14, 36, 48, 195, 213, 323-324, 423, 455, 493, 509-510, 532, 666, 731, 735-736. Read modifier evidence from archived agg, lv19, fz15, sol-kbd, rx6, rx6b, rx6c, structural-matching, opus-art, kbd_lib, opus-mwdbg, perm4 and sol-tiny logs, plus the landed sol-y8 log. Collected the unmerged g2 log read only from data-d4. The old data-d1 f1 log is gone from disk, so recovered its full contents with git show 532e1220:tools/decomp-assist/f1.attempts.md. f1 recorded 187 manual trials and 33,856 search trials; g2 recorded 103 compiled experiments and 26,680 search trials. Private consolidated history is /tmp/sol-r8-history.txt, with complete f1/g2 copies beside it.

Saved sol-tiny.kbd_lib.diff is empty. sol-y8.kbd_lib.diff contains only the already-landed LED match; baseline already includes it. There is no better retained modifier candidate.

Excluded repeated ideas: default-setting declaration permutations, cached channel or word pointers, old-first mask rewrites, signed/narrow index casts, scalar XOR/sum/complement merges, whole-union copies, direct physical/lock field assignments, nested channel records, const load/merge helpers, definition-level volatile, compiler versions and random spelling searches. Earlier helpers and member views leave the address/old-word priority unchanged or lose three inlined instructions. Scoped baseline IRO 0/1 and optimization levels 0-3, plus sol-y8 scalar/union combinations, already failed. Run the requested fresh optsweep as a diagnostic, then test new combinations of scoped settings with macro/inline/expanded shared updates and individual modifier-bit views.

## Baseline evidence

Unit exact 19/21; code 4572/5764, data 5296/5296. KBDSetModState is 4/42 differing instructions, kbdProcMod 4/256. Both have equal target size. First setter difference at instruction 30 and processor difference at 245. Target assigns the channel address to r4 and loaded old state to r5; source assigns the address to r5 and old state to r4. The four affected instructions are add, lwz, rlwimi and stw. Pool identical, zero strings. pool_diff.py requires explicit object paths here; its documented unit shorthand raises FileNotFoundError, so use built and target object paths.

Historical captures identify unnamed setter address v48 and old word v49, processor address v181 and old word v182. Fresh capture and simulation are required before relying on those IDs.

## Prior art

Fresh gh search code KBDSetModState returned RVL declarations in DarkRTA/rb3 and galaxymaster2007/THPConv, application callers and Wii U exports. No RVL implementation appeared. This agrees with opus-art; source provenance cannot resolve the modifier update from these results. No upstream contact.

## Trials

| baseline | 4/42 | 4/256 | 0 |
Fresh setter capture /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/sol-r8-setter-baseline/unit.o is byte-identical to Ninja output. vmap confirms address v48=r5, target r4; old word v49=r4, target r5. Interference edge v48-v49 remains. regsim reproduces 23/23 and reaches 0/2 desired colors after 20,000 steps. Stop declaration-order trials. Fresh requested optsweep completed without a lead, matching sol-y8. Tool copy changes only temporary output naming and import location.

| Trial | Setter diffs/insns | Processor diffs/insns | Previously exact losses |
| --- | --- | --- | --- |
| macro-setter-default | 4/42 | 4/256 | 0 |
| macro-setter-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| macro-pair-ppc_iro_level-0 | 7/42 | 261/267 | 0 |
| macro-setter-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| macro-pair-ppc_iro_level-1 | 4/42 | 260/264 | 0 |
| macro-setter-optimization_level-2 | 26/45 | 4/256 | 0 |
| macro-pair-optimization_level-2 | 26/45 | 257/261 | 0 |
| macro-setter-optimization_level-3 | 7/42 | 4/256 | 0 |
| macro-pair-optimization_level-3 | 7/42 | 254/258 | 0 |
| macro-setter-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| macro-pair-optimization_level-3-ppc_iro_level-1 | 4/42 | 260/264 | 0 |
| macro-setter-optimization_level-2-ppc_iro_level-1 | 26/45 | 4/256 | 0 |
| macro-pair-optimization_level-2-ppc_iro_level-1 | 26/45 | 263/267 | 0 |
| inline-setter-default | 4/42 | 4/256 | 0 |
| inline-setter-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| inline-pair-ppc_iro_level-0 | 7/42 | 261/267 | 0 |
| inline-setter-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| inline-pair-ppc_iro_level-1 | 4/42 | 260/264 | 0 |
| inline-setter-optimization_level-2 | 26/45 | 4/256 | 0 |
| inline-pair-optimization_level-2 | 26/45 | 257/261 | 0 |
| inline-setter-optimization_level-3 | 7/42 | 4/256 | 0 |
| inline-pair-optimization_level-3 | 7/42 | 254/258 | 0 |
| inline-setter-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| inline-pair-optimization_level-3-ppc_iro_level-1 | 4/42 | 260/264 | 0 |
| inline-setter-optimization_level-2-ppc_iro_level-1 | 26/45 | 4/256 | 0 |
| inline-pair-optimization_level-2-ppc_iro_level-1 | 26/45 | 263/267 | 0 |
| expanded-proc-default | 4/42 | 4/256 | 0 |
| expanded-proc-ppc_iro_level-0 | 4/42 | 258/265 | 0 |
| expanded-proc-ppc_iro_level-1 | 4/42 | 258/262 | 0 |
| expanded-proc-optimization_level-2 | 4/42 | 257/261 | 0 |
| expanded-proc-optimization_level-3 | 4/42 | 254/258 | 0 |
| expanded-proc-optimization_level-3-ppc_iro_level-1 | 4/42 | 258/262 | 0 |
| expanded-proc-optimization_level-2-ppc_iro_level-1 | 4/42 | 261/265 | 0 |
| six-bits-low-default | 20/47 | 254/232 | KBDResetChannel |
| six-bits-low-ppc_iro_level-0 | 23/47 | 254/238 | KBDResetChannel |
| six-bits-low-ppc_iro_level-1 | 20/47 | 255/235 | KBDResetChannel |
| six-bits-low-optimization_level-2 | 31/50 | 254/232 | KBDResetChannel |
| six-bits-low-optimization_level-3 | 23/47 | 254/232 | KBDResetChannel |
| six-bits-low-optimization_level-3-ppc_iro_level-1 | 20/47 | 255/235 | KBDResetChannel |
| six-bits-low-optimization_level-2-ppc_iro_level-1 | 31/50 | 255/235 | KBDResetChannel |
| six-bits-high-default | 20/47 | 254/232 | KBDResetChannel |
| six-bits-high-ppc_iro_level-0 | 23/47 | 254/238 | KBDResetChannel |
| six-bits-high-ppc_iro_level-1 | 20/47 | 255/235 | KBDResetChannel |
| six-bits-high-optimization_level-2 | 31/50 | 254/232 | KBDResetChannel |
| six-bits-high-optimization_level-3 | 23/47 | 254/232 | KBDResetChannel |
| six-bits-high-optimization_level-3-ppc_iro_level-1 | 20/47 | 255/235 | KBDResetChannel |
| six-bits-high-optimization_level-2-ppc_iro_level-1 | 31/50 | 255/235 | KBDResetChannel |

Phase 1 tested macro and inline merge blocks with scoped setter and caller settings, an expanded processor setter body, and six individual physical-bit copies. Macro/expanded default forms retain the same four differences; lower caller settings change the switch layout and add 2-11 instructions. Six-bit copies grow the setter to 47 instructions and cross MWCC inlining limits, regressing KBDResetChannel as well. None is retained. Scratch sources and full per-function counts are /tmp/sol-r8-trials.

Fresh primary prior art: https://github.com/DarkRTA/rb3/blob/b9dfa78b64e9120b622024687b3f27b4faed700d/src/sdk/RVL_SDK/revolution/kbd/kbd.h. _KBDModState names bits 0-5 CTRL, SHIFT, ALT, GUI, EXTRA, ALTGR, and bits 6-11 LANG1, LANG2, NUM_LOCK, CAPS_LOCK, SCROLL_LOCK, SHIFTED_KEY. Try that actual enum and a complete flag view instead of inventing HID left/right names. gh search code kbdProcMod returned no results; web searches likewise found no implementation.

| sdk-enum-001-default | 4/42 | 4/256 | 0 |
| sdk-enum-001-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| sdk-enum-001-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| sdk-enum-010-default | 4/42 | 4/256 | 0 |
| sdk-enum-010-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| sdk-enum-010-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| sdk-enum-011-default | 4/42 | 4/256 | 0 |
| sdk-enum-011-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| sdk-enum-011-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| sdk-enum-100-default | 4/42 | 4/256 | 0 |
| sdk-enum-100-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| sdk-enum-100-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| sdk-enum-101-default | 4/42 | 4/256 | 0 |
| sdk-enum-101-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| sdk-enum-101-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| sdk-enum-110-default | 4/42 | 4/256 | 0 |
| sdk-enum-110-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| sdk-enum-110-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| sdk-enum-111-default | 4/42 | 4/256 | 0 |
| sdk-enum-111-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| sdk-enum-111-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| bitview-merge-52-default | 4/42 | 4/256 | 0 |
| bitview-merge-52-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| bitview-merge-52-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| bitview-merge-42-default | 4/42 | 4/256 | 0 |
| bitview-merge-42-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| bitview-merge-42-optimization_level-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| bitview-merge-191-default | 4/42 | 4/256 | 0 |
| bitview-merge-191-ppc_iro_level-0 | 7/42 | 4/256 | 0 |
| bitview-merge-191-optimization_level-3-ppc_iro_level-1 | 4/42 | 4/256 | 0 |
| processor-bitview-assignment-default | 4/42 | 206/250 | 0 |
| processor-bitview-assignment-ppc_iro_level-0 | 4/42 | 256/261 | 0 |
| processor-bitview-assignment-ppc_iro_level-1 | 4/42 | 247/258 | 0 |
| processor-bitview-assignment-optimization_level-3 | 4/42 | 246/252 | 0 |
| processor-bitview-assignment-optimization_level-3-ppc_iro_level-1 | 4/42 | 247/258 | 0 |
| processor-bitview-clear-assignment-default | 4/42 | 22/256 | 0 |
| processor-bitview-clear-assignment-ppc_iro_level-0 | 4/42 | 261/267 | 0 |
| processor-bitview-clear-assignment-ppc_iro_level-1 | 4/42 | 260/264 | 0 |
| processor-bitview-clear-assignment-optimization_level-3 | 4/42 | 254/258 | 0 |
| processor-bitview-clear-assignment-optimization_level-3-ppc_iro_level-1 | 4/42 | 260/264 | 0 |
| processor-bitview-boolean-view-default | 4/42 | 206/250 | 0 |
| processor-bitview-boolean-view-ppc_iro_level-0 | 4/42 | 256/261 | 0 |
| processor-bitview-boolean-view-ppc_iro_level-1 | 4/42 | 247/258 | 0 |
| processor-bitview-boolean-view-optimization_level-3 | 4/42 | 246/252 | 0 |
| processor-bitview-boolean-view-optimization_level-3-ppc_iro_level-1 | 4/42 | 247/258 | 0 |
| minimal-physical-0-default | 4/42 | 4/256 | 0 |
| minimal-physical-0-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-0-optimization_level-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-1-default | 4/42 | 4/256 | 0 |
| minimal-physical-1-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-1-optimization_level-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-2-default | 4/42 | 4/256 | 0 |
| minimal-physical-2-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-2-optimization_level-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-3-default | 4/42 | 4/256 | 0 |
| minimal-physical-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-3-optimization_level-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-4-default | 4/42 | 4/256 | 0 |
| minimal-physical-4-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-4-optimization_level-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-5-default | 4/42 | 4/256 | 0 |
| minimal-physical-5-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-5-optimization_level-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-6-default | 4/42 | 4/256 | 0 |
| minimal-physical-6-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-6-optimization_level-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-7-default | 4/42 | 4/256 | 0 |
| minimal-physical-7-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| minimal-physical-7-optimization_level-3-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| physical-word-inline-helper | 4/42 | 4/256 | 0 |
| physical-word-inline-helper-and-setter | 0/42 | 4/256 | 0 |
| physical-word-inline-setter | 0/42 | 4/256 | 0 |

Phase 2 found a setter candidate at 0/42 with no previously exact function lost: bitview-merge-42-optimization_level-3-ppc_iro_level-1. It assigns the old whole word to a six-bit physical field, relying on the field truncation, and uses scoped optimization_level 3 plus ppc_iro_level 1. This is equivalent to copying oldState.bits.physical. The processor remains 4/256 because the caller uses its own lowering settings. All seven SDK enum combinations leave the pair unchanged or worsen the setter. Processor bit assignments remove six instructions; clear-then-assign keeps size but has 22 diffs. All unaccepted enum and processor changes stay in private scratch sources. Minimize the setter candidate before retaining it and investigate the shared inline under its caller settings.


## Retained setter match

Minimal source changes one assignment to newState.bits.physical = oldState.value and adds function-scoped ppc_iro_level 1. The six-bit destination keeps exactly oldState.value & 0x3f; incoming lock bits remain value & 0xfc0, so the previous union-field extraction is unnecessary. No additional view, enum, helper, cast or optimization_level pragma remains. In default lowering this expression still has four differences; IRO 1 with direct whole-word input swaps the address/old-word priority to the target. IRO 1 with the old extracted-field source alone had four differences in sol-y8.

Fresh requested Ninja object build passed. Explicit pool comparison identical. odiff 0/42, ctxdiff 42/42 and diffs 0. Fresh exact-name objdiff 100.0%; unit becomes 20/21, matched code 4740/5764, data 5296/5296. Comparing all 1028 report units shows exactly one function-score change, KBDSetModState 99.40476 to 100.0. kbdProcMod remains 4/256. Unit remains NonMatching while the processor is open. Full gate deferred until the end, as sol-common.md requests.

| prototype-iro1 | 0/42 | 4/256 | 0 |
| prototype-inline | 42/0 | 4/256 | KBDSetModState |
| definition-inline | 42/0 | 4/256 | KBDSetModState |
| both-inline | 42/0 | 4/256 | KBDSetModState |
| shared-pointer-14-ppc_iro_level-0 | 0/42 | 4/256 | 0 |
| shared-pointer-14-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| shared-pointer-14-optimization_level-1 | 0/42 | 4/256 | 0 |
| shared-pointer-14-optimization_level-2 | 0/42 | 4/256 | 0 |
| shared-index-14-ppc_iro_level-0 | 0/42 | 4/256 | 0 |
| shared-index-14-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| shared-index-14-optimization_level-1 | 0/42 | 4/256 | 0 |
| shared-index-14-optimization_level-2 | 0/42 | 4/256 | 0 |
| shared-pointer-21-ppc_iro_level-0 | 0/42 | 4/256 | 0 |
| shared-pointer-21-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| shared-pointer-21-optimization_level-1 | 0/42 | 4/256 | 0 |
| shared-pointer-21-optimization_level-2 | 0/42 | 4/256 | 0 |
| shared-index-21-ppc_iro_level-0 | 0/42 | 4/256 | 0 |
| shared-index-21-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| shared-index-21-optimization_level-1 | 0/42 | 4/256 | 0 |
| shared-index-21-optimization_level-2 | 0/42 | 4/256 | 0 |
| shared-pointer-18-ppc_iro_level-0 | 0/42 | 4/256 | 0 |
| shared-pointer-18-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| shared-pointer-18-optimization_level-1 | 0/42 | 4/256 | 0 |
| shared-pointer-18-optimization_level-2 | 0/42 | 4/256 | 0 |
| shared-index-18-ppc_iro_level-0 | 0/42 | 4/256 | 0 |
| shared-index-18-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| shared-index-18-optimization_level-1 | 0/42 | 4/256 | 0 |
| shared-index-18-optimization_level-2 | 0/42 | 4/256 | 0 |
| shared-pointer-19-ppc_iro_level-0 | 0/42 | 4/256 | 0 |
| shared-pointer-19-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| shared-pointer-19-optimization_level-1 | 0/42 | 4/256 | 0 |
| shared-pointer-19-optimization_level-2 | 0/42 | 4/256 | 0 |
| shared-index-19-ppc_iro_level-0 | 0/42 | 4/256 | 0 |
| shared-index-19-ppc_iro_level-1 | 0/42 | 4/256 | 0 |
| shared-index-19-optimization_level-1 | 0/42 | 4/256 | 0 |
| shared-index-19-optimization_level-2 | 0/42 | 4/256 | 0 |
| shared-pointer-22-ppc_iro_level-0 | 4/42 | 4/256 | KBDSetModState |
| shared-pointer-22-ppc_iro_level-1 | 4/42 | 4/256 | KBDSetModState |
| shared-pointer-22-optimization_level-1 | 4/42 | 4/256 | KBDSetModState |
| shared-pointer-22-optimization_level-2 | 4/42 | 4/256 | KBDSetModState |
| shared-index-22-ppc_iro_level-0 | 4/42 | 4/256 | KBDSetModState |
| shared-index-22-ppc_iro_level-1 | 4/42 | 4/256 | KBDSetModState |
| shared-index-22-optimization_level-1 | 4/42 | 4/256 | KBDSetModState |
| shared-index-22-optimization_level-2 | 4/42 | 4/256 | KBDSetModState |
| physical-lifetime-mask-first-word | 0/42 | 4/256 | 0 |
| physical-lifetime-mask-first-(u8) | 0/42 | 4/256 | 0 |
| physical-lifetime-mask-first-(u16) | 0/42 | 4/256 | 0 |
| physical-lifetime-old-first-word | 0/42 | 4/256 | 0 |
| physical-lifetime-old-first-(u8) | 0/42 | 4/256 | 0 |
| physical-lifetime-old-first-(u16) | 0/42 | 4/256 | 0 |
| physical-lifetime-old-copy-word | 6/42 | 7/256 | KBDSetModState |
| physical-lifetime-value-copy-word | 7/42 | 5/256 | KBDSetModState |
| physical-lifetime-value-copy-(u8) | 7/42 | 5/256 | KBDSetModState |
| physical-lifetime-value-copy-(u16) | 7/42 | 5/256 | KBDSetModState |
| physical-lifetime-mask-after-merge-word | 20/43 | 17/257 | KBDSetModState |
| physical-lifetime-mask-after-merge-(u8) | 20/43 | 17/257 | KBDSetModState |
| physical-lifetime-mask-after-merge-(u16) | 20/43 | 17/257 | KBDSetModState |
Phase 3 minimizes the setter candidate to IRO 1 alone. Masked, narrow and signed whole-word inputs also match under IRO 1; extra casts add nothing and are discarded. A scoped inline merge helper preserves four processor differences, even when the helper and setter share the candidate setting. Saved only the plain six-bit whole-word assignment.

Phase 4 tests the declaration options, explicit inline declarations, separately scoped real merge helpers and direct whole-word lifetime forms while preserving the exact setter. These differ from the old extracted-field/default-helper trials.

| caller-shape-pressed-in-place-ppc_iro_level-1 | 0/42 | 258/264 | 0 |
| caller-shape-pressed-in-place-optimization_level-3-ppc_iro_level-1 | 0/42 | 258/264 | 0 |
| caller-shape-pressed-in-place-ppc_iro_level-0 | 0/42 | 259/267 | 0 |
| caller-shape-pressed-in-place-optimization_level-3 | 0/42 | 254/258 | 0 |
| caller-shape-pressed-local-ppc_iro_level-1 | 0/42 | 258/264 | 0 |
| caller-shape-pressed-local-optimization_level-3-ppc_iro_level-1 | 0/42 | 258/264 | 0 |
| caller-shape-pressed-local-ppc_iro_level-0 | 0/42 | 259/267 | 0 |
| caller-shape-pressed-local-optimization_level-3 | 0/42 | 254/258 | 0 |
| caller-shape-parameter-copy-ppc_iro_level-1 | 0/42 | 260/264 | 0 |
| caller-shape-parameter-copy-optimization_level-3-ppc_iro_level-1 | 0/42 | 260/264 | 0 |
| caller-shape-parameter-copy-ppc_iro_level-0 | 0/42 | 261/267 | 0 |
| caller-shape-parameter-copy-optimization_level-3 | 0/42 | 254/258 | 0 |
| caller-shape-getter-data-ppc_iro_level-1 | 0/42 | 116/260 | 0 |
| caller-shape-getter-data-optimization_level-3-ppc_iro_level-1 | 0/42 | 116/260 | 0 |
| caller-shape-getter-data-ppc_iro_level-0 | 0/42 | 256/263 | 0 |
| caller-shape-getter-data-optimization_level-3 | 0/42 | 252/255 | 0 |
| caller-shape-pressed-and-getter-ppc_iro_level-1 | 0/42 | 54/260 | 0 |
| caller-shape-pressed-and-getter-optimization_level-3-ppc_iro_level-1 | 0/42 | 54/260 | 0 |
| caller-shape-pressed-and-getter-ppc_iro_level-0 | 0/42 | 254/263 | 0 |
| caller-shape-pressed-and-getter-optimization_level-3 | 0/42 | 252/255 | 0 |
Phase 4 declaration-scoped settings and explicit inline keywords leave the processor at four differences. Separately scoped helper settings likewise fail; some lose the setter match and are rejected. Reordered whole-word input keeps the setter exact but does not affect the caller. Post-merge masking or copying the old word changes instruction shapes and is rejected.

Phase 5 combines caller IRO 0/1 or optimization level 3 with normalized pressed state, a real pressed local, a channel parameter copy and a real validated getter that uses the existing data pointer. The closest IRO 1 layout has 260 instructions and 54 differences. None beats the baseline processor. These caller changes are all rejected.

197 compiled scratch trials completed across five directed phases, including the requested fresh optsweep separately. Best processor remains 4/256. Retain the independently measured exact setter and unchanged processor; stop this round without a fuzzy-only source change.

## Final processor evidence

The queued fresh capture completed after the setter was retained. /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/sol-r8-proc-baseline/unit.o equals the full Ninja object byte for byte, SHA256 3a03d87bcc9285ae5d3fbfd374cd392a8fa3a6f33a1b27930349399f6a6cd0a5. vmap aligns 234 of 256 instructions with virtual operands and confirms address v181=r5, target r4, and old word v182=r4, target r5. regsim reproduces 154/154 virtual registers and reaches 0/2 desired colors after 20,000 steps. The new scalar bitfield input removed two temporary nodes from the old 156-node capture without resolving the caller priority. Current ctxdiff remains exactly four differences at 245-248 with 256/256 instructions. No scheduling or size gap remains.

## Final gate

Requested command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py libs/RVL_SDK/src/kbd/kbd_lib --quick. Exit 0, GATE PASS. Full 43U build passes; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Unit instruction-exact and exact-name objdiff count 19/21 to 20/21, code 4572/5764 to 4740/5764, data unchanged at 5296/5296. All four owned data sections remain 100%, pools identical, global regressions 0, net forbidden patterns 0 and readability warnings 0. The allowed scoped IRO pragma is flagged for parent review. Gate uses the exact b1e91180 baseline report. Raw output is /tmp/sol-r8-gate.log.

Live build/43U/report.json agrees with the gate and fresh object. Across all 1028 units, the only changed function score is KBDSetModState. Final ctxdiff is setter 0/42, processor 4/256. This is one exact function gain; kbd_lib remains NonMatching and unlinked with kbdProcMod open. Parent independent verification remains necessary before acceptance. No push, PR, merge, rebase, other-worktree edit, assembly addition or uninitialized value.

Source commit: 12524e6c. Focused best diff: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-r8.kbd_lib.diff. The non-exact processor source is unchanged. All rejected sources remain outside the repository in /tmp/sol-r8-trials.
