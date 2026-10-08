# sol-r12 createAnmPane_ attempts

Worktree sol-high, branch agent/w1009/candbox, baseline ca6529e6. Scope src/keyboard/tiCandidateBox.cpp and a Matching flip only if the whole unit is exact. Read sol-common, brief-v2, levers 1-34, local AGENTS, unslop, writing-for-agents, prior pane logs, effort-policy and both saved best diffs.

## History and exclusions

Effort-policy lines 706, 712-713, 742 record sol-x9, its xhigh round 2, the orchestrator attempt and sol-y11. Read sol-x9.attempts.md fully and pane entries in all earlier archived/current logs. sol-y11.attempts.md is absent from the archived logs and detected worker files; its policy entry and saved diff are available. sol-y11 and sol-x9 best diffs are identical.

Not repeating standalone declaration permutations, u16/int count changes, pointer versus indexed traversal, widened indices, named-slot placement, bumped slots, direct tiPcKeyboard-style indexing, whole animation-loop helpers, plain field-return getters or animation-by-value. These have compiled evidence already. A new named-local getter boundary differs from those plain getters. Scoped IRO 0/1 and lower optimization levels are explicitly requested for this round.

Fresh first full build PASS. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Fetched origin/main under /tmp/wii-git.lock; HEAD equals ca6529e6. Initial function 41/216 differences, exact-name objdiff 98.91204%; unit 111/112 exact, code 23136/24000, data 4652/4652. Pools identical, 57/57 strings. Pre-existing rx* untracked files retained.

Read the original Ghidra export. tiPcKeyboard createAnmPane_ is exact and uses direct indexed animation fields, but the preceding orchestrator trial adds four instructions here. InputForm uses a count snapshot and a pointer-slot reference but its create function remains non-exact. No tiSoftwareKeyboard.cpp exists; inspect tiKeyboard and tiSignWindow as the available sibling classes.

## Trials

Replayed sol-x9/sol-y11 best. Function 6/216; target count r31, animation slot r23; source count r23, slot r31. Pool identical.

optsweep.py in a task-local copy keeps its compile/measure logic and prints every setting. Optimization 0: 367/216, 363 differences; 1: 241/216, 238; 2: 233/216, 231; 3: 231/216, 229. IRO 0: 236/216, 232; IRO 1: 216/216, 6. No exact lead.

Shared mwdbg queued behind other workers. Cancelled only our queued launcher before GDB started; rerun with an immutable task-local source and explicit original flags so later trials cannot invalidate the capture.

{"label": "01-count-named-getter-snapshot-iro-default-False-False", "hash": "c4c6449e2d7b", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "02-count-named-getter-snapshot-iro1-False-False", "hash": "1e1b3909bd62", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "03-count-named-getter-bound-iro-default-False-False", "hash": "74e719f15953", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "04-count-named-getter-bound-iro1-False-False", "hash": "e622c3c11d33", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "05-count-named-getter-snapshot-iro-default-True-False", "hash": "caf5253ffaf6", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "06-count-named-getter-snapshot-iro1-True-False", "hash": "f203194d1c44", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "07-count-named-getter-bound-iro-default-True-False", "hash": "e70168d2ad35", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "08-count-named-getter-bound-iro1-True-False", "hash": "6ff04fffc140", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "09-count-named-getter-snapshot-iro-default-False-True", "hash": "7fb0473a2258", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "10-count-named-getter-snapshot-iro1-False-True", "hash": "956dcbdb6868", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "11-count-named-getter-bound-iro-default-False-True", "hash": "6f3eedc02ac6", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "12-count-named-getter-bound-iro1-False-True", "hash": "ec2dc6c86174", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "13-slot-named-getter-u16-ref-iro-default", "hash": "d2c4e1fea652", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "14-slot-named-getter-u16-ref-iro1", "hash": "55fa702dd869", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "15-slot-named-getter-const-u16-ref-iro-default", "hash": "cfc214964915", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "16-slot-named-getter-const-u16-ref-iro1", "hash": "d8aae43f0b1f", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "17-slot-named-getter-u16-ptr-iro-default", "hash": "6e127dbd432a", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "18-slot-named-getter-u16-ptr-iro1", "hash": "4fb6ebad371b", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "19-slot-named-getter-const-u16-ptr-iro-default", "hash": "a577d4ef3a3c", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "20-slot-named-getter-const-u16-ptr-iro1", "hash": "e10a41ea9c1a", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "21-signwindow-while-branch-default", "hash": "7cea664b482f", "insns": [216, 216], "diffs": 17, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "22-filename-getter-name-default", "hash": "2c0497144947", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "22-filename-getter-file-default", "hash": "65b5307906cd", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "23-loop-getter-bound-value-default", "hash": "ce47ae41f8f5", "insns": [217, 216], "diffs": 116, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "23-loop-getter-bound-ref-default", "hash": "5c70a31ad80c", "insns": [217, 216], "diffs": 116, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "24-slot-getter-named-index-u16-default", "hash": "383dc776f225", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "24-slot-getter-named-index-const-u16-default", "hash": "0d5c8c5742c3", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "21-signwindow-while-branch-iro1", "hash": "30b4974e6738", "insns": [216, 216], "diffs": 17, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "22-filename-getter-name-iro1", "hash": "989de3b1ce4f", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "22-filename-getter-file-iro1", "hash": "2266d987ba29", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "23-loop-getter-bound-value-iro1", "hash": "520b5f9a9ef9", "insns": [217, 216], "diffs": 116, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "23-loop-getter-bound-ref-iro1", "hash": "5f8f522536fd", "insns": [217, 216], "diffs": 116, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "24-slot-getter-named-index-u16-iro1", "hash": "681af4c38cc0", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "24-slot-getter-named-index-const-u16-iro1", "hash": "31d0508ba054", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "35-animation-record-getter-id-default", "hash": "6ec6c8878822", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "35-animation-record-getter-id-iro1", "hash": "2b656215f5ea", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "35-animation-record-getter-name-default", "hash": "a24397e7f5d3", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "35-animation-record-getter-name-iro1", "hash": "c14dc3df5eb4", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "35-animation-record-getter-id-name-default", "hash": "2093471b709e", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "35-animation-record-getter-id-name-iro1", "hash": "7fade926b5b4", "insns": [216, 216], "diffs": 6, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "41-named-count-break-default", "hash": "4e332bbe630a", "insns": [216, 216], "diffs": 48, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "41-named-count-break-iro1", "hash": "1ac2bafd35f5", "insns": [216, 216], "diffs": 48, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "41-named-count-guarded-do-default", "hash": "99e8eeaf7a55", "insns": [217, 216], "diffs": 59, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}
{"label": "41-named-count-guarded-do-iro1", "hash": "8a5b4493ef09", "insns": [217, 216], "diffs": 59, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_rc": 0}

## Allocator evidence

The queue remained busy, so cancelled only the second queued sol-r12 launcher before GDB started. Ran task-local mwdbg/gc3 copies with an isolated lock and host debugger port 19912. The compiler binary, hooks and compile flags stayed unchanged. The driver source hash in command.json names the task-local copy. No shared tool was edited.

Fresh immutable six-difference capture `/tmp/sol-r12-six-capture`. Compared with the freshly Ninja-built six-difference object `/tmp/sol-r12-six.o`: every section except .symtab/.strtab is byte-identical. Those metadata differences come from the temporary source filename. Selected function offset 3672, size 864, all decoded instructions and all resolved relocation tuples identical.

vmap2 task-local copy maps the capture to the original object. It aligns 173 instructions with virtual operands, 217 scheduled PCode instructions versus 216 machine instructions. Complete want-list is `/tmp/sol-r12-want.txt`.

The final successful GPR pass reproduces 127/127 colors. Count v46 animationCount currently r23, wants r31. Slot-address v141 currently r31, wants r23. All other 27 wanted colors already agree. Named-local annealing for 20000 steps reaches 0/2 for those two values, 27/29 for the whole want-list.

Color priority begins v141, v137, v122, v95, v91, v86, v85, v80, v46. v141 is simplified last at remaining degree 12 and claims r31 first. The constructor constants take r30 through r24. v46 is simplified at degree 20 and takes r23 ninth. This reproduces the prior blocker with a fresh capture. Varying declaration numbering cannot swap count and slot in this graph.

## Disposition

44 new compiled source variants plus the six-setting optsweep. Named-local getters for the count, slot, index, filename and animation ID, combined with IRO 1, leave the same six differing registers. The exact SignWindow while/branch shape gives 17 differences. Getter/loop u16-bound declarations give 217/216 instructions, 116 differences. Named-getter break and guarded-do shapes also fail. Every trial preserves all 57 pool strings.

No exact gain. Best remains the replayed 6/216 version, saved outside the repository as `/mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-r12.tiCandidateBox.diff`. Restored the original source before the one final gate. No Matching flip or source/header/config change remains. Final gate evidence below checks the restored baseline, not acceptance of the non-exact best.

## Final gate on restored baseline

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiCandidateBox] pool: IDENTICAL
[src/keyboard/tiCandidateBox] objdiff: code 23136/24000 data 4652/4652 functions 111/112 fuzzy 99.9608 linked code 0
[src/keyboard/tiCandidateBox] instruction-exact functions: 111/112
[src/keyboard/tiCandidateBox]   section .ctors size 4 match 100.0
[src/keyboard/tiCandidateBox]   section .data size 3488 match 100.0
[src/keyboard/tiCandidateBox]   section .rodata size 1048 match 100.0
[src/keyboard/tiCandidateBox]   section .sdata size 32 match 100.0
[src/keyboard/tiCandidateBox]   section .sdata2 size 80 match 100.0
[src/keyboard/tiCandidateBox]   section .text size 24000 match 99.96083
[src/keyboard/tiCandidateBox]   below 100: createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator 98.91204
[src/keyboard/tiCandidateBox] baseline: code 23136/24000 data 4652 functions 111 fuzzy 99.9608
regressions vs baseline: 0
global matched_code_percent: 98.09787 -> 98.09787
global fuzzy_match_percent: 99.92176 -> 99.92176
global complete_code_percent: 90.12492 -> 90.12492
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Unit exact functions 111/112 -> 111/112. Data stays 4652/4652, every data section 100%. Source returned to 41/216 differences; replayed best remains 6/216. Only this log is committed. No push, PR, merge, rebase, assembly, unrelated edits or shared tool edits. Awaiting parent.
