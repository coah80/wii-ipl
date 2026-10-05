# perm4 attempts

Base: `41023c51a6e326d5850a8edf5d0cc4989a7c903a`. Branch: `agent/w1005/perm4`.

Exact gain: replaced the 792-byte TVRCSendStartAsync asm body with readable, instruction-exact C++. Commit `b30a82bb68b58c519ce61305060f7b465c09d7d0`. NHTTP and KBD production source is unchanged. No fuzzy-only candidate was retained.

| Unit | Exact functions before -> after | Code bytes before -> after | Data bytes before -> after |
| --- | --- | --- | --- |
| NHTTP_stdlib_RVL | 12/14 -> 12/14 | 1864/2248 -> 1864/2248 | 112/112 -> 112/112 |
| kbd_lib | 18/21 -> 18/21 | 4472/5764 -> 4472/5764 | 5296/5296 -> 5296/5296 |
| TVRC | 9/9 -> 9/9 | 2312/2312 -> 2312/2312 | 280/280 -> 280/280 |

TVRC was already linked through asm, so its exact and linked byte counts do not increase. Its best C seed moved from 99.747475% to 100.0%; final permuter cost is zero.

## Source review and compiler evidence

TVRC: the useful permuter change binds the repeat offset by const reference after storing the repeat flag. The final source names the real file fields and command records, uses a shared file-relative record reader, and keeps eight command entries, matching the validated command range. mwdbg shows the stride changing from r6 to r7 and the reloaded file base from r7 to r6. The final capture produces the same whole object as ordinary MWCC. Obsolete asm aliases and constants were removed; ordinary numeric literals emit the original float pool.

The raw TVRC hit was not acceptable as-is: objdiff reported 100% and ctxdiff reported zero, but it called __cvt_dbl_ull twice instead of __cvt_dbl_usll. The full DOL exposed four wrong bytes. Removing the unsigned intermediate cast restores signed timing conversion and the exact calls. Doldiff then reports zero differing bytes. All 202 allocated relocations and allocated symbol offsets/sizes match. Textual symorder differences are debug entries or literal label names at identical allocated offsets; the DOL is identical.

NHTTPi_strnicmp remains 99.76471% (51/51 instructions), and NHTTPi_compareToken remains 99.73333% (45/45). Both differ only in two initial loads: A, zero, Z versus A, Z, zero. Named bounds, predicate helpers, helper parameter forms, and byte-cursor forms did not remove the difference. mwdbg shows this ordering before register allocation.

kbdProcMod remains 99.90234% (256/256), and KBDSetModState remains 99.40476% (42/42). Both retain four address/value register differences. Tried declaration order, real modifier-field types, mask merges, union reuse, pointer and helper boundaries, caller locals, and compound updates. Union reuse reached 99.921875% for kbdProcMod but regressed KBDSetModState to 98.809525%; rejected. mwdbg confirmed a real remaining operand change. kbd_led_handler (99.72%) is outside this assignment.

## Search budgets

Six permuter processes at most, with the raised MWCC settings and PERM_LINESWAP on single-line declaration blocks. Five searches completed 7200 seconds; TVRC stopped early only after its exact C result passed the full quick gate and DOL check. Total permuter iterations: 89129.

| Permuter target | Minutes | Iterations | Saved improvements |
| --- | ---: | ---: | ---: |
| strnicmp | 120.02 | 18770 | 0 |
| token | 120.03 | 18853 | 0 |
| procmod | 120.03 | 7058 | 0 |
| setmod | 120.03 | 15470 | 0 |
| lowercase | 120.03 | 23917 | 0 |
| tvrc | 79.96 | 5061 | 1 |

The only permuter output was TVRC output-40-1; it was reviewed, rewritten, and verified as described above.

Four srcsearch jobs used a private copy of srcsearch.py. Fixes cover function definitions rather than prototypes, same-signedness integer aliases, declaration initialization, branch inversion, and modifier merge forms. Every best candidate is archived and passed to whole-unit review and mwdbg. The shared tool and its 24-slot limit were unchanged.

| Source target | Budget seconds | Iterations | Saved improvements |
| --- | ---: | ---: | ---: |
| setmod | 6567 + 633 initial | 13621 | 0 |
| procmod | 7200 | 15036 | 0 |
| strnicmp | 7200 | 18308 | 0 |
| token | 7200 | 18209 | 0 |

KBDSetModState first searched for 633 confirmed seconds with only declaration swaps, then used the remaining 6567 seconds with broader mutations. Its table iteration count covers the resumed run; the initial run recorded at least 50 additional trials. Slot waits do not consume search time. A queue-restart race briefly created duplicate waiters; all were stopped before acquiring slots or executing trials. The recovery metadata is in build/perm4/srcsearch-queue-recovery.json. A local singleton lock prevents recurrence. The controller reaped its final child before refreshing that row, so the last exit code is unrecorded; its terminal done marker and absent process verify completion in srcsearch-completion-audit.json.

## Verification

All pools were identical before tuning. Final verification used a clean 43U gate against the pinned starting base. Source and original objects, exact-name objdiff, ctxdiff, allocated relocations, DOL SHA1, forbidden patterns, and readability were checked. TVRC was already Matching; no configure.py edit was needed.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] pool: IDENTICAL
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] objdiff: code 1864/2248 data 112/112 functions 12/14 fuzzy 99.9573 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] instruction-exact functions: 12/14
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .data size 72 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   section .text size 2248 match 99.9573
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_strnicmp 99.76471
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL]   below 100: NHTTPi_compareToken 99.73333
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] baseline: code 1864/2248 data 112 functions 12 fuzzy 99.9573
[libs/RVL_SDK/src/kbd/kbd_lib] pool: IDENTICAL
[libs/RVL_SDK/src/kbd/kbd_lib] objdiff: code 4472/5764 data 5296/5296 functions 18/21 fuzzy 99.9604 linked code 0
[libs/RVL_SDK/src/kbd/kbd_lib] instruction-exact functions: 18/21
[libs/RVL_SDK/src/kbd/kbd_lib]   section .bss size 3968 match 100.0
[libs/RVL_SDK/src/kbd/kbd_lib]   section .data size 1304 match 100.0
[libs/RVL_SDK/src/kbd/kbd_lib]   section .sbss size 16 match 100.0
[libs/RVL_SDK/src/kbd/kbd_lib]   section .sdata size 8 match 100.0
[libs/RVL_SDK/src/kbd/kbd_lib]   section .text size 5764 match 99.96044
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: kbdProcMod 99.90234
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: kbd_led_handler 99.72
[libs/RVL_SDK/src/kbd/kbd_lib]   below 100: KBDSetModState 99.40476
[libs/RVL_SDK/src/kbd/kbd_lib] baseline: code 4472/5764 data 5296 functions 18 fuzzy 99.9604
[src/system/TVRC] pool: IDENTICAL
[src/system/TVRC] objdiff: code 2312/2312 data 280/280 functions 9/9 fuzzy 100.0000 linked code 2312
[src/system/TVRC] instruction-exact functions: 9/9
[src/system/TVRC]   section .bss size 96 match 100.0
[src/system/TVRC]   section .sbss size 120 match 100.0
[src/system/TVRC]   section .sdata size 32 match 100.0
[src/system/TVRC]   section .sdata2 size 32 match 100.0
[src/system/TVRC]   section .text size 2312 match 100.0
[src/system/TVRC] baseline: code 2312/2312 data 280 functions 9 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 93.82541 -> 93.82541
global fuzzy_match_percent: 99.81117 -> 99.81117
global complete_code_percent: 79.26653 -> 79.26653
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Artifacts and reproduction

Campaign root: `build/perm4/` in this worktree. Read `attempts-full.md` for the chronological log and `trials.json` for complete trial measurements. The table below indexes every compiled manual trial by job and label; its source, compiler output, pool, objdiff report, ctxdiff, and summary are in `<job>/trial-<label>/`.

- Permuter setup and scores: `<job>/job.json`, `base.c`, `settings.toml`, `baseline-score.json`, `run.log`; `permuter-summary.json` records final iteration counts.
- Source search: `srcsearch-<job>/run.log`, archived hits, `srcsearch-summary.json`; `srcsearch-candidates.jsonl` records any hits.
- Final TVRC: `tvrc-signed-ready.cpp`, `tvrc/final-permuter-score.json`, `tvrc-link-audit.json`, `tvrc-doldiff-final.txt`.
- Compiler captures: `mwdbg/<job>-baseline/` and `mwdbg/tvrc-final-signed-source/`; validation.json and normal-object.json prove the debugger did not alter code generation.
- Ghidra: private TVRC export `ghidra/TVRC.c`; NHTTP/KBD shared exports were read only.
- The user-specified rx17 TVRC artifact was read only and copied into `rx17-reference/`. No command ran in that other worktree.
- Adapter support for `prepare --start` retains a separate production reference for the freshness guard. C preprocessing and the C++ seed were compiled and compared before the long campaigns.

Origin/main advanced while the searches ran. The final gate uses the pinned starting base; the orchestrator must verify the commit on its landing branch. No push, PR, merge, rebase, subagent, or edit outside the assigned worktree was performed.

## Compiled trials

Each owned open function has at least three distinct compiled source attempts. Percentages below are trial scores, not retained gains; a lower score in another function rejects the candidate.

| Job | Trial | Fuzzy % | Instructions | Diffs | Regressions |
| --- | --- | ---: | --- | ---: | --- |
| tvrc | rx17-current-names | 99.747475 | 198/198 | 9 | - |
| tvrc | seed-baseline | 99.747475 | 198/198 | 9 | - |
| setmod | plain-mask-merge | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| setmod | channel-local-merge | 98.690475 | 42/42 | 7 | kbdProcMod: 99.90234->95.05469 |
| setmod | state-local-merge | 98.690475 | 42/42 | 7 | kbdProcMod: 99.90234->95.05469 |
| setmod | read-old-first | 99.40476 | 42/42 | 4 | - |
| setmod | one-state-logical-bits | 97.38095 | 42/42 | 6 | kbdProcMod: 99.90234->99.53125 |
| setmod | initializers-in-order | compile failed | - | - | - |
| setmod | helper-physical-first | 99.40476 | 42/42 | 4 | - |
| setmod | helper-logical-first | 99.40476 | 42/42 | 4 | - |
| tvrc | const-file-view | 99.747475 | 198/198 | 9 | - |
| tvrc | offset-pointer | 99.747475 | 198/198 | 9 | - |
| tvrc | local-current-file | 97.72222 | 196/198 | - | - |
| tvrc | reused-file-local | 99.747475 | 198/198 | 9 | - |
| tvrc | initialize-at-block-head | 99.747475 | 198/198 | 9 | - |
| tvrc | c-style-record-casts | 99.747475 | 198/198 | 9 | - |
| tvrc | offset-accessor | 99.747475 | 198/198 | 9 | - |
| strnicmp | fold-two-bounds-upper-first | 99.76471 | 51/51 | 2 | - |
| token | fold-two-bounds-upper-first | 99.73333 | 45/45 | 2 | - |
| strnicmp | fold-two-bounds-lower-first | 99.76471 | 51/51 | 2 | - |
| token | fold-two-bounds-lower-first | 99.73333 | 45/45 | 2 | - |
| strnicmp | fold-mutating-parameter | 99.76471 | 51/51 | 2 | NHTTPi_compareToken: 99.73333->94.62222 |
| token | fold-mutating-parameter | 94.62222 | 44/45 | - | - |
| strnicmp | fold-local-bound-values | 99.76471 | 51/51 | 2 | - |
| token | fold-local-bound-values | 99.73333 | 45/45 | 2 | - |
| strnicmp | fold-boolean-product | 56.27451 | 47/51 | - | NHTTPi_strToHex: 100.0->84.0274, NHTTPi_compareToken: 99.73333->41.644444 |
| token | fold-boolean-product | 41.644444 | 41/45 | - | NHTTPi_strnicmp: 99.76471->56.27451, NHTTPi_strToHex: 100.0->84.0274 |
| strnicmp | split-read-and-advance | 99.37255 | 51/51 | 6 | - |
| token | typed-right-byte-cursor | 99.73333 | 45/45 | 2 | - |
| strnicmp | upper-predicate-int-ternary | 99.76471 | 51/51 | 2 | - |
| token | upper-predicate-int-ternary | 99.73333 | 45/45 | 2 | - |
| strnicmp | upper-predicate-int-branch | 99.76471 | 51/51 | 2 | NHTTPi_compareToken: 99.73333->98.844444 |
| token | upper-predicate-int-branch | 98.844444 | 45/45 | 7 | - |
| strnicmp | upper-predicate-const-int-ternary | 99.76471 | 51/51 | 2 | - |
| token | upper-predicate-const-int-ternary | 99.73333 | 45/45 | 2 | - |
| strnicmp | upper-predicate-const-int-branch | 99.76471 | 51/51 | 2 | NHTTPi_compareToken: 99.73333->98.844444 |
| token | upper-predicate-const-int-branch | 98.844444 | 45/45 | 7 | - |
| setmod | scalar-old-state | 99.40476 | 42/42 | 4 | - |
| procmod | scalar-old-state | 99.90234 | 256/256 | 4 | - |
| setmod | scalar-old-state-masked | 99.40476 | 42/42 | 4 | - |
| procmod | scalar-old-state-masked | 99.90234 | 256/256 | 4 | - |
| setmod | scalar-new-state | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | scalar-new-state | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | scalar-states | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | scalar-states | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | reuse-value-scalar-old | 95.11905 | 43/42 | - | kbdProcMod: 99.90234->99.140625 |
| procmod | reuse-value-scalar-old | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->95.11905 |
| setmod | typed-modifier-field | 99.40476 | 42/42 | 4 | - |
| setmod | direct-physical-field | 98.690475 | 42/42 | 7 | kbdProcMod: 99.90234->95.05469 |
| procmod | direct-physical-field | 95.05469 | 253/256 | - | KBDSetModState: 99.40476->98.690475 |
| setmod | direct-lock-field | 97.38095 | 42/42 | 7 | kbdProcMod: 99.90234->95.54297 |
| procmod | direct-lock-field | 95.54297 | 253/256 | - | KBDSetModState: 99.40476->97.38095 |
| setmod | direct-lock-field-union | 98.809525 | 42/42 | 7 | kbdProcMod: 99.90234->95.77734 |
| procmod | direct-lock-field-union | 95.77734 | 253/256 | - | KBDSetModState: 99.40476->98.809525 |
| setmod | direct-logical-copy | 98.690475 | 42/42 | 7 | kbdProcMod: 99.90234->95.05469 |
| procmod | direct-logical-copy | 95.05469 | 253/256 | - | KBDSetModState: 99.40476->98.690475 |
| tvrc | named-command-record-reference | 99.747475 | 198/198 | 9 | - |
| tvrc | repeat-offset-reference | 99.747475 | 198/198 | 9 | - |
| tvrc | current-command-reference | 98.5101 | 196/198 | - | - |
| tvrc | array-base-pointer | 99.747475 | 198/198 | 9 | - |
| tvrc | command-index-local | 99.747475 | 198/198 | 9 | - |
| tvrc | command-accessor-pointer | 98.5101 | 196/198 | - | - |
| tvrc | command-accessor-reference | 98.5101 | 196/198 | - | - |
| setmod | merge-store-expression | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | merge-store-expression | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | merge-physical-direct | 99.40476 | 42/42 | 4 | - |
| procmod | merge-physical-direct | 99.90234 | 256/256 | 4 | - |
| setmod | reuse-old-union | 98.809525 | 42/42 | 7 | - |
| procmod | reuse-old-union | 99.921875 | 256/256 | 3 | KBDSetModState: 99.40476->98.809525 |
| setmod | reuse-new-union | 98.809525 | 42/42 | 6 | kbdProcMod: 99.90234->99.765625 |
| procmod | reuse-new-union | 99.765625 | 256/256 | 7 | KBDSetModState: 99.40476->98.809525 |
| setmod | copy-then-merge | 97.38095 | 42/42 | 6 | kbdProcMod: 99.90234->99.53125 |
| procmod | copy-then-merge | 99.53125 | 256/256 | 7 | KBDSetModState: 99.40476->97.38095 |
| setmod | physical-after-mask | 99.40476 | 42/42 | 4 | - |
| procmod | physical-after-mask | 99.90234 | 256/256 | 4 | - |
| setmod | merge-store-expression-decl-order | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| setmod | merge-physical-direct-decl-order | 99.40476 | 42/42 | 4 | - |
| setmod | reuse-old-union-decl-order | 98.809525 | 42/42 | 7 | - |
| setmod | reuse-new-union-decl-order | 98.809525 | 42/42 | 6 | kbdProcMod: 99.90234->99.765625 |
| setmod | copy-then-merge-decl-order | 97.38095 | 42/42 | 6 | kbdProcMod: 99.90234->99.53125 |
| setmod | physical-after-mask-decl-order | 99.40476 | 42/42 | 4 | - |
| setmod | reuse-input-value | 99.40476 | 42/42 | 4 | - |
| procmod | reuse-input-value | 99.90234 | 256/256 | 4 | - |
| setmod | normalize-physical-state | 94.7619 | 44/42 | - | kbdProcMod: 99.90234->98.32031 |
| procmod | normalize-physical-state | 98.32031 | 258/256 | - | KBDSetModState: 99.40476->94.7619 |
| setmod | lock-state-helper-channel-first | 99.40476 | 42/42 | 4 | - |
| procmod | lock-state-helper-channel-first | 99.90234 | 256/256 | 4 | - |
| setmod | lock-state-helper-value-first | 99.40476 | 42/42 | 4 | - |
| procmod | lock-state-helper-value-first | 99.90234 | 256/256 | 4 | - |
| setmod | lock-state-helper-channel-first-const | 99.40476 | 42/42 | 4 | kbdProcMod: 99.90234->94.87891 |
| procmod | lock-state-helper-channel-first-const | 94.87891 | 258/256 | - | - |
| setmod | lock-state-helper-value-first-const | 99.40476 | 42/42 | 4 | kbdProcMod: 99.90234->94.87891 |
| procmod | lock-state-helper-value-first-const | 94.87891 | 258/256 | - | - |
| tvrc | load-parameters-file-pointer | 98.22727 | 197/198 | - | - |
| tvrc | load-parameters-file-reference | 99.747475 | 198/198 | 9 | - |
| tvrc | load-parameters-global-file | 91.28788 | 182/198 | - | - |
| tvrc | command-data-helper-data | 99.747475 | 198/198 | 9 | - |
| tvrc | command-data-helper-repeat | 99.747475 | 198/198 | 9 | - |
| tvrc | command-data-helper-both | 99.747475 | 198/198 | 9 | - |
| procmod | reuse-mod-state | 98.80859 | 257/256 | - | - |
| procmod | final-state-at-call | 99.90234 | 256/256 | 4 | - |
| procmod | reuse-key-value | 99.90234 | 256/256 | 4 | - |
| procmod | direct-channel-access | 79.80469 | 282/256 | - | - |
| procmod | counter-width | 99.90234 | 256/256 | 4 | - |
| procmod | counter-value-unsigned | 99.16016 | 256/256 | 38 | - |
| procmod | counter-value-word | 99.90234 | 256/256 | 4 | - |
| setmod | outer-state-locals | 99.40476 | 42/42 | 4 | - |
| procmod | outer-state-locals | 99.90234 | 256/256 | 4 | - |
| setmod | outer-state-snapshot | 99.40476 | 42/42 | 4 | - |
| procmod | outer-state-snapshot | 99.90234 | 256/256 | 4 | - |
| setmod | lexical-snapshot-block | 99.40476 | 42/42 | 4 | - |
| procmod | lexical-snapshot-block | 99.90234 | 256/256 | 4 | - |
| setmod | combined-union-declaration | 99.40476 | 42/42 | 4 | - |
| procmod | combined-union-declaration | 99.90234 | 256/256 | 4 | - |
| setmod | merge-operands-0 | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | merge-operands-0 | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | merge-operands-1 | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | merge-operands-1 | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | merge-operands-2 | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | merge-operands-2 | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | merge-operands-3 | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | merge-operands-3 | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | merge-operands-4 | 95.11905 | 43/42 | - | kbdProcMod: 99.90234->99.31641 |
| procmod | merge-operands-4 | 99.31641 | 257/256 | - | KBDSetModState: 99.40476->95.11905 |
| setmod | merge-operands-5 | 91.666664 | 45/42 | - | kbdProcMod: 99.90234->98.671875 |
| procmod | merge-operands-5 | 98.671875 | 259/256 | - | KBDSetModState: 99.40476->91.666664 |
| setmod | merge-operands-6 | 98.690475 | 42/42 | 8 | - |
| procmod | merge-operands-6 | 99.90234 | 256/256 | 4 | KBDSetModState: 99.40476->98.690475 |
| setmod | merge-operands-7 | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | merge-operands-7 | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| tvrc | file-member-offset | 99.26768 | 197/198 | - | - |
| tvrc | file-member-record-pointer | 97.51515 | 197/198 | - | - |
| tvrc | file-member-record-reference | 97.51515 | 197/198 | - | - |
| setmod | pointer-load | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-load | 99.90234 | 256/256 | 4 | - |
| setmod | pointer-store | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-store | 99.90234 | 256/256 | 4 | - |
| setmod | pointer-load-store | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-load-store | 99.90234 | 256/256 | 4 | - |
| setmod | const-channel-read | 98.690475 | 42/42 | 7 | - |
| procmod | const-channel-read | 99.90234 | 256/256 | 4 | KBDSetModState: 99.40476->98.690475 |
| setmod | reversed-array-add-read | 99.40476 | 42/42 | 4 | - |
| procmod | reversed-array-add-read | 99.90234 | 256/256 | 4 | - |
| tvrc | raw-output-40-1 | 100.0 | 198/198 | 0 | - |
| tvrc | rewrite-repeat-offset-pointer-top | 99.09091 | 198/198 | 3 | - |
| tvrc | rewrite-repeat-offset-pointer-local | 99.09091 | 198/198 | 3 | - |
| tvrc | rewrite-repeat-offset-reference-local | 100.0 | 198/198 | 0 | - |
| tvrc | cleanup-complete-command-array | 100.0 | 198/198 | 0 | - |
| tvrc | cleanup-command-header-word | 100.0 | 198/198 | 0 | - |
| tvrc | cleanup-command-data-const | 100.0 | 198/198 | 0 | - |
| tvrc | final-natural-source | 100.0 | 198/198 | 0 | - |
| tvrc | remove-asm-alias-declarations | 100.0 | 198/198 | 0 | - |
| tvrc | implicit-float-constants | 100.0 | 198/198 | 0 | - |
| tvrc | command-data-reader | 100.0 | 198/198 | 0 | - |
| tvrc | signed-time-conversion | 100.0 | 198/198 | 0 | - |
| setmod | shared-oldState-union | 99.40476 | 42/42 | 4 | - |
| procmod | shared-oldState-union | 99.90234 | 256/256 | 4 | - |
| setmod | shared-oldState-scalar | 99.40476 | 42/42 | 4 | - |
| procmod | shared-oldState-scalar | 99.90234 | 256/256 | 4 | - |
| setmod | shared-newState-union | 99.40476 | 42/42 | 4 | - |
| procmod | shared-newState-union | 99.90234 | 256/256 | 4 | - |
| setmod | shared-newState-scalar | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | shared-newState-scalar | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | update-two-masks | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | update-two-masks | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | update-two-masks-local | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->95.015625 |
| procmod | update-two-masks-local | 95.015625 | 253/256 | - | KBDSetModState: 99.40476->94.04762 |
| setmod | update-mask-before-physical | 94.04762 | 42/42 | 7 | kbdProcMod: 99.90234->99.140625 |
| procmod | update-mask-before-physical | 99.140625 | 256/256 | 5 | KBDSetModState: 99.40476->94.04762 |
| setmod | update-logical-before-mask | 91.666664 | 43/42 | - | kbdProcMod: 99.90234->98.75 |
| procmod | update-logical-before-mask | 98.75 | 257/256 | - | KBDSetModState: 99.40476->91.666664 |
| setmod | pointer-helper-channel-pointer-first-requested-first | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-helper-channel-pointer-first-requested-first | 99.90234 | 256/256 | 4 | - |
| setmod | pointer-helper-channel-pointer-first-physical-first | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-helper-channel-pointer-first-physical-first | 99.90234 | 256/256 | 4 | - |
| setmod | pointer-helper-channel-value-first-requested-first | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-helper-channel-value-first-requested-first | 99.90234 | 256/256 | 4 | - |
| setmod | pointer-helper-channel-value-first-physical-first | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-helper-channel-value-first-physical-first | 99.90234 | 256/256 | 4 | - |
| setmod | pointer-helper-word-pointer-first-requested-first | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-helper-word-pointer-first-requested-first | 99.90234 | 256/256 | 4 | - |
| setmod | pointer-helper-word-pointer-first-physical-first | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-helper-word-pointer-first-physical-first | 99.90234 | 256/256 | 4 | - |
| setmod | pointer-helper-word-value-first-requested-first | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-helper-word-value-first-requested-first | 99.90234 | 256/256 | 4 | - |
| setmod | pointer-helper-word-value-first-physical-first | 99.40476 | 42/42 | 4 | - |
| procmod | pointer-helper-word-value-first-physical-first | 99.90234 | 256/256 | 4 | - |
