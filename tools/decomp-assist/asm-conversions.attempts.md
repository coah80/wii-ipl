# Inline assembly conversion attempts

Target: Wii Menu 4.3U. Keep a conversion only after ctxdiff reports zero differences and quick/full gates pass. Failed source experiments were restored. Baseline asm functions already count as exact; this task preserves their exact count while replacing their implementation.

The requested ghidra_decomp.txt has no functions from these five units. Temporary Ghidra exports of the original objects and the target assembly supplied the function bodies. Ghidra outputs and full experiment sources/build/ctx/pool/gate results are in /tmp/sol-low-asm.

## Attempts

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseInit :: attempt 1: direct initialization
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x44 base 0x44 insns 17/17; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseInit-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseOpen :: attempt 1: preserve success default
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x50 base 0x50 insns 20/20; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseOpen-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseClose :: attempt 1: literal report and typed instance
FIRST DIVERGENCE at index 1; src 0xac base 0xb0 insns 43/44; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseClose-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseClose :: attempt 2: separate free status
FIRST DIVERGENCE at index 1; src 0xac base 0xb0 insns 43/44; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseClose-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseClose :: attempt 3: success branch first
FIRST DIVERGENCE at index 1; src 0xac base 0xb0 insns 43/44; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseClose-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnce :: attempt 1: nested validation and captured codes
no string entries; #   Error:                                               ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabasePrivateCreateRecordAtOnce-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnce :: attempt 2: load converted codes after obtaining time
no string entries; #   Error:                                               ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabasePrivateCreateRecordAtOnce-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnce :: attempt 3: validate with cleanup label
no string entries; #   Error:                                               ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabasePrivateCreateRecordAtOnce-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordAtOnce :: attempt 1: capture maker then game before time
no string entries; #   Error:                                               ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordAtOnce-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordAtOnce :: attempt 2: capture game then maker before time
no string entries; #   Error:                                               ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordAtOnce-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordAtOnce :: attempt 3: read codes after timestamp
no string entries; #   Error:                                               ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordAtOnce-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnce :: attempt 4: nested validation and captured codes
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xec base 0xec insns 59/59; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabasePrivateCreateRecordAtOnce-4

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordAtOnce :: attempt 4: capture maker then game before time
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x94 base 0x94 insns 37/37; diffs 8: [5, 7, 14, 15, 23, 24, 25, 26]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordAtOnce-4

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordAtOnce :: attempt 5: capture game then maker before time
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x94 base 0x94 insns 37/37; diffs 8: [5, 7, 14, 15, 23, 24, 25, 26]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordAtOnce-5

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordAtOnce :: attempt 6: read codes after timestamp
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x94 base 0x94 insns 37/37; diffs 12: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 25, 26]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordAtOnce-6

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordAtOnceEx :: attempt 1: calendar fields in argument order
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xcc base 0xcc insns 51/51; diffs 12: [23, 24, 26, 27, 28, 29, 37, 38, 39, 40, 42, 45]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordAtOnceEx-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordAtOnceEx :: attempt 2: seconds first
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xcc base 0xcc insns 51/51; diffs 21: [6, 10, 11, 13, 17, 19, 20, 21, 22, 23, 24, 26, 27, 28, 29, 37, 38, 39, 40, 42]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordAtOnceEx-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordAtOnceEx :: attempt 3: game code captured before maker
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xcc base 0xcc insns 51/51; diffs 12: [23, 24, 26, 27, 28, 29, 37, 38, 39, 40, 42, 45]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordAtOnceEx-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnceEx :: attempt 1: calendar fields in argument order
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xb0 base 0xb0 insns 44/44; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabasePrivateCreateRecordAtOnceEx-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnceEx_ :: attempt 1: calendar fields in argument order
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x124 base 0x124 insns 73/73; diffs 12: [45, 46, 48, 49, 50, 51, 59, 60, 61, 62, 64, 66]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabasePrivateCreateRecordAtOnceEx_-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnceEx_ :: attempt 2: converted codes held across time conversion
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x124 base 0x124 insns 73/73; diffs 19: [39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 59, 60, 61, 62, 64, 66]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabasePrivateCreateRecordAtOnceEx_-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnceEx_ :: attempt 3: reverse calendar assignment
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x124 base 0x124 insns 73/73; diffs 18: [38, 40, 41, 42, 43, 44, 45, 46, 48, 49, 50, 51, 59, 60, 61, 62, 64, 66]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabasePrivateCreateRecordAtOnceEx_-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordImAtOnce_ :: attempt 1: closed check before read-only
no string entries; #   Error:                                                                 ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordImAtOnce_-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordImAtOnce_ :: attempt 2: write bit first then closed status
no string entries; #   Error:                                                                 ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordImAtOnce_-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordImAtOnce_ :: attempt 3: split quotient and date conversion
no string entries; #   Error:                                                                 ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordImAtOnce_-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseFindByKey :: attempt 1: descriptor then existence branches
FIRST DIVERGENCE at index 0; src 0xe4 base 0xe4 insns 57/57; diffs 0: []; RESTORED ASM; regressions vs baseline: 0; GATE FAIL: full build failed; DOL hash 02347405ac466976c1a73c72e504f2cd7643ecbb != 26116613f624061ba99c8d1a299aaa6efa85670d; evidence /tmp/sol-low-asm/CDBDatabaseFindByKey-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordImAtOnce_ :: attempt 4: closed check before read-only
no string entries; #   Error:                   ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordImAtOnce_-4

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordImAtOnce_ :: attempt 5: write bit first then closed status
no string entries; #   Error:                   ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordImAtOnce_-5

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseFindByKey :: attempt 2: use cleanup on invalid key
FIRST DIVERGENCE at index 0; src 0xe4 base 0xe4 insns 57/57; diffs 0: []; RESTORED ASM; regressions vs baseline: 0; GATE FAIL: full build failed; DOL hash 02347405ac466976c1a73c72e504f2cd7643ecbb != 26116613f624061ba99c8d1a299aaa6efa85670d; evidence /tmp/sol-low-asm/CDBDatabaseFindByKey-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordImAtOnce_ :: attempt 6: split quotient and date conversion
no string entries; #   Error:     ^^^^^^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordImAtOnce_-6

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseFindByKey :: attempt 3: descriptor then existence branches
FIRST DIVERGENCE at index 0; src 0xe4 base 0xe4 insns 57/57; diffs 0: []; RESTORED ASM; regressions vs baseline: 0; GATE FAIL: full build failed; DOL hash 8a2ff623bf5f6611c9628eb03c921004772b758a != 26116613f624061ba99c8d1a299aaa6efa85670d; evidence /tmp/sol-low-asm/CDBDatabaseFindByKey-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseFindByKey :: attempt 3: assume success before existence test
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xe4 base 0xe4 insns 57/57; diffs 0: []; RESTORED ASM; regressions vs baseline: 0; GATE FAIL: full build failed; DOL hash 02347405ac466976c1a73c72e504f2cd7643ecbb != 26116613f624061ba99c8d1a299aaa6efa85670d; evidence /tmp/sol-low-asm/CDBDatabaseFindByKey-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseFindByKey :: attempt 4: use cleanup on invalid key
no string entries; #   Error:     ^^^^^^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseFindByKey-4

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseFindByKey :: attempt 5: assume success before existence test
FIRST DIVERGENCE at index 0; src 0xe0 base 0xe4 insns 56/57; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseFindByKey-5

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordImAtOnce_ :: attempt 7: closed check before read-only
FIRST DIVERGENCE at index 0; src 0x120 base 0x150 insns 72/84; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordImAtOnce_-7

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordImAtOnce_ :: attempt 8: write bit first then closed status
FIRST DIVERGENCE at index 0; src 0x150 base 0x150 insns 84/84; diffs 2: [75, 76]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordImAtOnce_-8

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCreateRecordImAtOnce_ :: attempt 9: split quotient and date conversion
FIRST DIVERGENCE at index 0; src 0x120 base 0x150 insns 72/84; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCreateRecordImAtOnce_-9

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseFindByKey :: attempt 6: descriptor then existence branches
FIRST DIVERGENCE at index 0; src 0xe4 base 0xe4 insns 57/57; diffs 0: []; RESTORED ASM; regressions vs baseline: 0; GATE FAIL: full build failed; DOL hash 02347405ac466976c1a73c72e504f2cd7643ecbb != 26116613f624061ba99c8d1a299aaa6efa85670d; evidence /tmp/sol-low-asm/CDBDatabaseFindByKey-6

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseFindByKey :: attempt 7: use cleanup on invalid key
FIRST DIVERGENCE at index 0; src 0xe4 base 0xe4 insns 57/57; diffs 0: []; RESTORED ASM; regressions vs baseline: 0; GATE FAIL: full build failed; DOL hash 02347405ac466976c1a73c72e504f2cd7643ecbb != 26116613f624061ba99c8d1a299aaa6efa85670d; evidence /tmp/sol-low-asm/CDBDatabaseFindByKey-7

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseFindByKey :: attempt 8: assume success before existence test
FIRST DIVERGENCE at index 0; src 0xe0 base 0xe4 insns 56/57; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseFindByKey-8

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchConditionsIsMatch :: attempt 1: early returns and typed search fields
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x100 base 0x100 insns 64/64; diffs 12: [0, 2, 3, 6, 36, 39, 48, 51, 58, 59, 60, 62]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchConditionsIsMatch-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchConditionsIsMatch :: attempt 2: larger type buffer
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x100 base 0x100 insns 64/64; diffs 6: [5, 10, 36, 39, 48, 51]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchConditionsIsMatch-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchConditionsIsMatch :: attempt 3: nested game-code validation
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x100 base 0x100 insns 64/64; diffs 12: [0, 2, 3, 6, 36, 39, 48, 51, 58, 59, 60, 62]; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchConditionsIsMatch-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchCallCallback :: attempt 1: open before callback with early errors
no string entries; #   Error:                                                                 ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchCallCallback-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchCallCallback :: attempt 2: match failure returns immediately
no string entries; #   Error:                                                                 ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchCallCallback-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchCallCallback :: attempt 3: read-only branch first
no string entries; #   Error:                                                                 ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchCallCallback-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchConditionsIsMatch :: attempt 4: decoded key fields share a structured local
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x100 base 0x100 insns 64/64; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseSearchConditionsIsMatch-4

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchCallCallback :: attempt 4: open before callback with early errors
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xf0 base 0xf4 insns 60/61; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchCallCallback-4

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchCallCallback :: attempt 5: match failure returns immediately
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xf8 base 0xf4 insns 62/61; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchCallCallback-5

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchCallCallback :: attempt 6: read-only branch first
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xf0 base 0xf4 insns 60/61; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchCallCallback-6

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchRecordLayer :: attempt 1: typed record keys and directory traversal
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x714 base 0x6fc insns 453/447; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchRecordLayer-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchRecordLayer :: attempt 2: name variables per nested directory
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x714 base 0x6fc insns 453/447; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchRecordLayer-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchRecordLayer :: attempt 3: reverse iteration pre-decrement
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x710 base 0x6fc insns 452/447; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchRecordLayer-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchMinuteLayer :: attempt 1: typed directories and indexed traversal
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3a8 base 0x3a0 insns 234/232; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchMinuteLayer-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchMinuteLayer :: attempt 2: forward traversal while loop
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3a8 base 0x3a0 insns 234/232; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchMinuteLayer-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchMinuteLayer :: attempt 3: reverse traversal pre-decrement
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3a4 base 0x3a0 insns 233/232; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchMinuteLayer-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchHourLayer :: attempt 1: typed directories and indexed traversal
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x394 base 0x38c insns 229/227; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchHourLayer-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchHourLayer :: attempt 2: forward traversal while loop
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x394 base 0x38c insns 229/227; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchHourLayer-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchHourLayer :: attempt 3: reverse traversal pre-decrement
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x390 base 0x38c insns 228/227; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchHourLayer-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchDayLayer :: attempt 1: typed directories and indexed traversal
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x428 base 0x3f0 insns 266/252; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchDayLayer-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchDayLayer :: attempt 2: forward traversal while loop
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x428 base 0x3f0 insns 266/252; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchDayLayer-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchDayLayer :: attempt 3: reverse traversal pre-decrement
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x424 base 0x3f0 insns 265/252; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchDayLayer-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchMonthLayer :: attempt 1: typed directories and indexed traversal
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x408 base 0x3c0 insns 258/240; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchMonthLayer-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchMonthLayer :: attempt 2: forward traversal while loop
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x408 base 0x3c0 insns 258/240; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchMonthLayer-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchMonthLayer :: attempt 3: reverse traversal pre-decrement
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x404 base 0x3c0 insns 257/240; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchMonthLayer-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchYearLayer :: attempt 1: typed directories and indexed traversal
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3d0 base 0x378 insns 244/222; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchYearLayer-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchYearLayer :: attempt 2: forward traversal while loop
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3d0 base 0x378 insns 244/222; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchYearLayer-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchYearLayer :: attempt 3: reverse traversal pre-decrement
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3cc base 0x378 insns 243/222; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearchYearLayer-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearch :: attempt 1: typed forwarding under lock
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xa0 base 0xa0 insns 40/40; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseSearch-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearch_ :: attempt 1: normalized date bounds and search state
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xcc base 0xd4 insns 51/53; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearch_-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearch_ :: attempt 2: explicit optional console id branches
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xd0 base 0xd4 insns 52/53; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearch_-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearch_ :: attempt 3: set minimum then maximum
POOL IDENTICAL up to 7 (mine=7 base=7); src 0xcc base 0xd4 insns 51/53; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseSearch_-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseInstanceInit :: attempt 1: instance state and owner initialization
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x18 base 0x18 insns 6/6; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseInstanceInit-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseInstanceIsUsed :: attempt 1: read instance allocation state
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x8 base 0x8 insns 2/2; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseInstanceIsUsed-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBIsSDAvailable :: attempt 1: explicit boolean availability default
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x48 base 0x48 insns 18/18; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBIsSDAvailable-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBMountSD :: attempt 1: forward sd mount
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x4 base 0x4 insns 1/1; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBMountSD-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBUnmountSDForce :: attempt 1: default success and propagate unmount status
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x34 base 0x34 insns 13/13; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBUnmountSDForce-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesRecord :: attempt 1: typed directory and child counter
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x10c base 0x10c insns 67/67; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectoriesRecord-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesType :: attempt 1: typed directory and child counter
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x15c base 0x15c insns 87/87; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectoriesType-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesCode :: attempt 1: typed directory and child counter
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x14c base 0x14c insns 83/83; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectoriesCode-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesMinute :: attempt 1: typed directory and child counter
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x140 base 0x140 insns 80/80; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectoriesMinute-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesHour :: attempt 1: typed directory and child counter
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x134 base 0x134 insns 77/77; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectoriesHour-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesDay :: attempt 1: typed directory and child counter
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x128 base 0x128 insns 74/74; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectoriesDay-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesMonth :: attempt 1: typed directory and child counter
POOL IDENTICAL up to 7 (mine=7 base=7); src 0x124 base 0x124 insns 73/73; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectoriesMonth-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectories :: attempt 1: typed root traversal and inline availability
no string entries; #   Error:                        ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectories-1

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectories :: attempt 2: available check as nested condition
no string entries; #   Error:                        ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectories-2

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectories :: attempt 3: explicit mounted then ejected checks
no string entries; #   Error:                        ^; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectories-3

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectories :: attempt 4: typed root traversal and inline availability
FIRST DIVERGENCE at index 0; src 0x21c base 0x214 insns 135/133; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectories-4

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectories :: attempt 5: available check as nested condition
FIRST DIVERGENCE at index 0; src 0x21c base 0x214 insns 135/133; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectories-5

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectories :: attempt 6: explicit mounted then ejected checks
FIRST DIVERGENCE at index 0; src 0x21c base 0x214 insns 135/133; RESTORED ASM; evidence /tmp/sol-low-asm/CDBDatabaseCleanUpEmptyDirectories-6

src/sound/iplSound :: __ct__Q33ipl3snd6SystemFv :: attempt 1: implicit audio base constructor
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x4c base 0x4c insns 19/19; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/__ct__Q33ipl3snd6SystemFv-1

src/sound/iplSound :: __dt__Q33ipl3snd10tagSSeInfoFv :: attempt 1: implicit member destruction
no string entries; #   Error:                                                      ^; RESTORED ASM; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd10tagSSeInfoFv-1

src/sound/iplSound :: __dt__Q33ipl3snd10tagSSeInfoFv :: attempt 2: out-of-line sound-handle destructor
no string entries; #   Error:                                                      ^; RESTORED ASM; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd10tagSSeInfoFv-2

src/sound/iplSound :: __dt__Q33ipl3snd10tagSSeInfoFv :: attempt 3: member destruction after local handle binding
no string entries; #   Error:                                                      ^; RESTORED ASM; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd10tagSSeInfoFv-3

src/sound/iplSound :: __dt__Q33ipl3snd11tagSBgmInfoFv :: attempt 1: implicit member destruction
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x58 base 0x58 insns 22/22; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd11tagSBgmInfoFv-1

src/sound/iplSound :: __dt__Q33ipl3snd6UnkClsFv :: attempt 1: reverse array destruction by index
no string entries; #   Error:                          ^; RESTORED ASM; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd6UnkClsFv-1

src/sound/iplSound :: __dt__Q33ipl3snd6UnkClsFv :: attempt 2: reverse array destruction by pointer
no string entries; #   Error:                          ^; RESTORED ASM; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd6UnkClsFv-2

src/sound/iplSound :: __dt__Q33ipl3snd6UnkClsFv :: attempt 3: forward array destruction
no string entries; #   Error:                          ^; RESTORED ASM; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd6UnkClsFv-3

src/sound/iplSound :: __dt__Q33ipl3snd10tagSSeInfoFv :: attempt 4: implicit member destruction
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x58 base 0x58 insns 22/22; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd10tagSSeInfoFv-4

src/sound/iplSound :: __dt__Q33ipl3snd6UnkClsFv :: attempt 4: reverse array destruction by index
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x78 base 0x1c insns 30/7; RESTORED ASM; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd6UnkClsFv-4

src/sound/iplSound :: __dt__Q33ipl3snd6UnkClsFv :: attempt 5: reverse array destruction by pointer
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x7c base 0x1c insns 31/7; RESTORED ASM; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd6UnkClsFv-5

src/sound/iplSound :: __dt__Q33ipl3snd6UnkClsFv :: attempt 6: forward array destruction
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x7c base 0x1c insns 31/7; RESTORED ASM; evidence /tmp/sol-low-asm/__dt__Q33ipl3snd6UnkClsFv-6

src/sound/iplSound :: stopBGM__Q33ipl3snd6SystemFi :: attempt 1: normal handle methods
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x34 base 0x34 insns 13/13; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/stopBGM__Q33ipl3snd6SystemFi-1

src/sound/iplSound :: muteOnBGM__Q33ipl3snd6SystemFi :: attempt 1: normal handle methods
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x38 base 0x34 insns 14/13; RESTORED ASM; evidence /tmp/sol-low-asm/muteOnBGM__Q33ipl3snd6SystemFi-1

src/sound/iplSound :: muteOnBGM__Q33ipl3snd6SystemFi :: attempt 2: rely on handle attachment check
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x34 base 0x34 insns 13/13; diffs 5: [3, 4, 6, 7, 8]; RESTORED ASM; evidence /tmp/sol-low-asm/muteOnBGM__Q33ipl3snd6SystemFi-2

src/sound/iplSound :: muteOnBGM__Q33ipl3snd6SystemFi :: attempt 3: local main handle
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x34 base 0x34 insns 13/13; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/muteOnBGM__Q33ipl3snd6SystemFi-3

src/sound/iplSound :: muteOffBGM__Q33ipl3snd6SystemFi :: attempt 1: normal handle methods
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x38 base 0x34 insns 14/13; RESTORED ASM; evidence /tmp/sol-low-asm/muteOffBGM__Q33ipl3snd6SystemFi-1

src/sound/iplSound :: muteOffBGM__Q33ipl3snd6SystemFi :: attempt 2: rely on handle attachment check
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x34 base 0x34 insns 13/13; diffs 5: [3, 4, 6, 7, 8]; RESTORED ASM; evidence /tmp/sol-low-asm/muteOffBGM__Q33ipl3snd6SystemFi-2

src/sound/iplSound :: muteOffBGM__Q33ipl3snd6SystemFi :: attempt 3: local main handle
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x34 base 0x34 insns 13/13; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/muteOffBGM__Q33ipl3snd6SystemFi-3

src/sound/iplSound :: pauseOnSE__Q33ipl3snd6SystemFv :: attempt 1: normal handle methods
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x74 base 0x74 insns 29/29; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/pauseOnSE__Q33ipl3snd6SystemFv-1

src/sound/iplSound :: pauseOffSE__Q33ipl3snd6SystemFv :: attempt 1: normal handle methods
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x74 base 0x74 insns 29/29; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/pauseOffSE__Q33ipl3snd6SystemFv-1

src/sound/iplSound :: pauseOnBGM__Q33ipl3snd6SystemFv :: attempt 1: normal handle methods
POOL IDENTICAL up to 0 (mine=0 base=0); src 0xa8 base 0xa8 insns 42/42; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/pauseOnBGM__Q33ipl3snd6SystemFv-1

src/sound/iplSound :: pauseOffBGM__Q33ipl3snd6SystemFv :: attempt 1: normal handle methods
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x80 base 0x80 insns 32/32; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/pauseOffBGM__Q33ipl3snd6SystemFv-1

src/sound/iplSound :: stopSE__Q33ipl3snd6SystemFPQ34nw4r3snd11SoundHandlei :: attempt 1: normal handle methods
POOL IDENTICAL up to 0 (mine=0 base=0); src 0xa8 base 0xa8 insns 42/42; diffs 9: [12, 16, 19, 20, 22, 30, 31, 32, 34]; RESTORED ASM; evidence /tmp/sol-low-asm/stopSE__Q33ipl3snd6SystemFPQ34nw4r3snd11SoundHandlei-1

src/sound/iplSound :: stopSE__Q33ipl3snd6SystemFPQ34nw4r3snd11SoundHandlei :: attempt 2: early return for inactive handle
POOL IDENTICAL up to 0 (mine=0 base=0); src 0xac base 0xa8 insns 43/42; RESTORED ASM; evidence /tmp/sol-low-asm/stopSE__Q33ipl3snd6SystemFPQ34nw4r3snd11SoundHandlei-2

src/sound/iplSound :: stopSE__Q33ipl3snd6SystemFPQ34nw4r3snd11SoundHandlei :: attempt 3: iterate with pointer
POOL IDENTICAL up to 0 (mine=0 base=0); src 0xa0 base 0xa8 insns 40/42; RESTORED ASM; evidence /tmp/sol-low-asm/stopSE__Q33ipl3snd6SystemFPQ34nw4r3snd11SoundHandlei-3

src/sound/iplSound :: resetAllSound__Q33ipl3snd6SystemFv :: attempt 1: normal handle methods
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x114 base 0x110 insns 69/68; RESTORED ASM; evidence /tmp/sol-low-asm/resetAllSound__Q33ipl3snd6SystemFv-1

src/sound/iplSound :: resetAllSound__Q33ipl3snd6SystemFv :: attempt 2: main handle checks attachment
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x110 base 0x110 insns 68/68; diffs 7: [5, 9, 13, 21, 22, 23, 25]; RESTORED ASM; evidence /tmp/sol-low-asm/resetAllSound__Q33ipl3snd6SystemFv-2

src/sound/iplSound :: resetAllSound__Q33ipl3snd6SystemFv :: attempt 3: pointer traversal of sound blocks
POOL IDENTICAL up to 0 (mine=0 base=0); src 0x10c base 0x110 insns 67/68; RESTORED ASM; evidence /tmp/sol-low-asm/resetAllSound__Q33ipl3snd6SystemFv-3

src/sound/iplSound :: __ct__Q34nw4r3snd11SoundHandleFv :: attempt 1: out-of-line constructor member initializer
POOL IDENTICAL up to 0 (mine=0 base=0); src 0xc base 0xc insns 3/3; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/__ct__Q34nw4r3snd11SoundHandleFv-1

src/system/iplSaveDataManager :: hasChannel__Q33ipl8savedata7ManagerCFUxPiPi :: attempt 1: nested page and slot indices
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x11c base 0x11c insns 71/71; diffs 58: [0, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]; RESTORED ASM; evidence /tmp/sol-low-asm/hasChannel-1

src/system/iplSaveDataManager :: hasChannel__Q33ipl8savedata7ManagerCFUxPiPi :: attempt 2: mask conditional as explicit branches
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x11c base 0x11c insns 71/71; diffs 58: [0, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]; RESTORED ASM; evidence /tmp/sol-low-asm/hasChannel-2

src/system/iplSaveDataManager :: hasChannel__Q33ipl8savedata7ManagerCFUxPiPi :: attempt 3: local channel pointer
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x11c base 0x11c insns 71/71; diffs 58: [0, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]; RESTORED ASM; evidence /tmp/sol-low-asm/hasChannel-3

src/system/iplSaveDataManager :: getNumValidChannel__Q33ipl8savedata7ManagerCFv :: attempt 1: nested page and slot indices
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x60 base 0x5c insns 24/23; RESTORED ASM; evidence /tmp/sol-low-asm/getNumValidChannel-1

src/system/iplSaveDataManager :: getNumValidChannel__Q33ipl8savedata7ManagerCFv :: attempt 2: split type and scene tests
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x60 base 0x5c insns 24/23; RESTORED ASM; evidence /tmp/sol-low-asm/getNumValidChannel-2

src/system/iplSaveDataManager :: getNumValidChannel__Q33ipl8savedata7ManagerCFv :: attempt 3: row pointer and counted inner loop
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x58 base 0x5c insns 22/23; RESTORED ASM; evidence /tmp/sol-low-asm/getNumValidChannel-3

src/system/iplSaveDataManager :: getNumValidChannel__Q33ipl8savedata7ManagerCFv :: attempt 4: direct member references avoid hoisting channel base
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x5c base 0x5c insns 23/23; diffs 4: [4, 7, 8, 11]; RESTORED ASM; evidence /tmp/sol-low-asm/getNumValidChannel-4

src/system/iplSaveDataManager :: getNumValidChannel__Q33ipl8savedata7ManagerCFv :: attempt 5: page index declared before count
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x5c base 0x5c insns 23/23; diffs 10: [0, 1, 4, 7, 8, 11, 14, 17, 19, 21]; RESTORED ASM; evidence /tmp/sol-low-asm/getNumValidChannel-5

src/system/iplSaveDataManager :: getNumValidChannel__Q33ipl8savedata7ManagerCFv :: attempt 6: increment count before page counter declaration
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x5c base 0x5c insns 23/23; diffs 4: [4, 7, 8, 11]; RESTORED ASM; evidence /tmp/sol-low-asm/getNumValidChannel-6

src/system/iplSaveDataManager :: makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl :: attempt 1: direct title list traversal
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x1ec base 0x214 insns 123/133; RESTORED ASM; evidence /tmp/sol-low-asm/makePriorTitleIDList-1

src/system/iplSaveDataManager :: makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl :: attempt 2: nested nonzero input body
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x1ec base 0x214 insns 123/133; RESTORED ASM; evidence /tmp/sol-low-asm/makePriorTitleIDList-2

src/system/iplSaveDataManager :: makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl :: attempt 3: local input title snapshot
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x1ec base 0x214 insns 123/133; RESTORED ASM; evidence /tmp/sol-low-asm/makePriorTitleIDList-3

src/system/iplSaveDataManager :: makeTmpList__Q33ipl8savedata7ManagerFPUxUlPUxUl :: attempt 1: direct title list traversal
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x170 base 0x17c insns 92/95; RESTORED ASM; evidence /tmp/sol-low-asm/makeTmpList-1

src/system/iplSaveDataManager :: makeTmpList__Q33ipl8savedata7ManagerFPUxUlPUxUl :: attempt 2: pointer advances input titles
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x168 base 0x17c insns 90/95; RESTORED ASM; evidence /tmp/sol-low-asm/makeTmpList-2

src/system/iplSaveDataManager :: makeTmpList__Q33ipl8savedata7ManagerFPUxUlPUxUl :: attempt 3: separate append and output count increment
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x170 base 0x17c insns 92/95; RESTORED ASM; evidence /tmp/sol-low-asm/makeTmpList-3

src/system/iplSaveDataManager :: doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx :: attempt 1: direct title list traversal
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x104 base 0x10c insns 65/67; RESTORED ASM; evidence /tmp/sol-low-asm/doUpdateChanInfos-1

src/system/iplSaveDataManager :: doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx :: attempt 2: read title halves directly from input array
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x10c base 0x10c insns 67/67; diffs 54: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24]; RESTORED ASM; evidence /tmp/sol-low-asm/doUpdateChanInfos-2

src/system/iplSaveDataManager :: doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx :: attempt 3: explicit changed-channel branch
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x104 base 0x10c insns 65/67; RESTORED ASM; evidence /tmp/sol-low-asm/doUpdateChanInfos-3

src/system/iplSaveDataManager :: getAvailableInList__Q33ipl8savedata7ManagerFPCUxUl :: attempt 1: direct search and title comparison
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x70 base 0x70 insns 28/28; diffs 10: [0, 2, 11, 12, 13, 14, 15, 16, 21, 23]; RESTORED ASM; evidence /tmp/sol-low-asm/getAvailableInList-1

src/system/iplSaveDataManager :: getAvailableInList__Q33ipl8savedata7ManagerFPCUxUl :: attempt 2: split quotient and remainder
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x70 base 0x70 insns 28/28; diffs 10: [0, 2, 11, 12, 13, 14, 15, 16, 21, 23]; RESTORED ASM; evidence /tmp/sol-low-asm/getAvailableInList-2

src/system/iplSaveDataManager :: getAvailableInList__Q33ipl8savedata7ManagerFPCUxUl :: attempt 3: pointer input traversal
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x68 base 0x70 insns 26/28; RESTORED ASM; evidence /tmp/sol-low-asm/getAvailableInList-3

src/system/iplSaveDataManager :: isEqualChannel__Q33ipl8savedata7ManagerFUxUx :: attempt 1: direct search and title comparison
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x8c base 0x9c insns 35/39; RESTORED ASM; evidence /tmp/sol-low-asm/isEqualChannel-1

src/system/iplSaveDataManager :: isEqualChannel__Q33ipl8savedata7ManagerFUxUx :: attempt 2: base mismatch early return
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x8c base 0x9c insns 35/39; RESTORED ASM; evidence /tmp/sol-low-asm/isEqualChannel-2

src/system/iplSaveDataManager :: isEqualChannel__Q33ipl8savedata7ManagerFUxUx :: attempt 3: region conditions use XOR
POOL IDENTICAL up to 3 (mine=3 base=3); src 0x98 base 0x9c insns 38/39; RESTORED ASM; evidence /tmp/sol-low-asm/isEqualChannel-3

src/system/iplSaveDataManager :: iplSavedata_813596B8__Q33ipl8savedata7ManagerFUx :: attempt 1: direct search and title comparison
POOL IDENTICAL up to 3 (mine=3 base=3); src 0xd8 base 0xe8 insns 54/58; RESTORED ASM; evidence /tmp/sol-low-asm/iplSavedata_813596B8-1

src/system/iplSaveDataManager :: iplSavedata_813596B8__Q33ipl8savedata7ManagerFUx :: attempt 2: separate excluded title checks
POOL IDENTICAL up to 3 (mine=3 base=3); src 0xd4 base 0xe8 insns 53/58; RESTORED ASM; evidence /tmp/sol-low-asm/iplSavedata_813596B8-2

src/system/iplSaveDataManager :: iplSavedata_813596B8__Q33ipl8savedata7ManagerFUx :: attempt 3: shift using source and destination indices
POOL IDENTICAL up to 3 (mine=3 base=3); src 0xe8 base 0xe8 insns 58/58; diffs 18: [24, 34, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 50, 51, 52, 53, 54]; RESTORED ASM; evidence /tmp/sol-low-asm/iplSavedata_813596B8-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_imagestart :: attempt 1: typed zigzag array stores
no string entries; src 0x188 base 0x190 insns 98/100; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_imagestart-1

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_imagestart :: attempt 2: counted for loop
no string entries; src 0x188 base 0x190 insns 98/100; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_imagestart-2

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_imagestart :: attempt 3: natural sequential zigzag stores
no string entries; src 0x188 base 0x190 insns 98/100; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_imagestart-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_scan_varinit :: attempt 1: frame fields and sampling component index
no string entries; src 0x204 base 0x204 insns 129/129; diffs 9: [8, 9, 10, 11, 12, 13, 15, 20, 21]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_scan_varinit-1

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_scan_varinit :: attempt 2: ceil divisions as explicit increments
no string entries; src 0x1f8 base 0x204 insns 126/129; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_scan_varinit-2

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_scan_varinit :: attempt 3: capture horizontal and vertical sampling before stores
no string entries; src 0x204 base 0x204 insns 129/129; diffs 18: [8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_scan_varinit-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_restart_interval :: attempt 1: nested restart parsing
no string entries; src 0x16c base 0x174 insns 91/93; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_restart_interval-1

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_restart_interval :: attempt 2: post-increment restart count
no string entries; src 0x16c base 0x174 insns 91/93; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_restart_interval-2

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_restart_interval :: attempt 3: modulus for next MCU remainder
no string entries; src 0x16c base 0x174 insns 91/93; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_restart_interval-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_para :: attempt 1: marker switch with common error exit
no string entries; src 0x2c4 base 0x2dc insns 177/183; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_para-1

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_para :: attempt 2: single negative-result clamp
no string entries; src 0x2bc base 0x2dc insns 175/183; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_para-2

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_para :: attempt 3: stop flag bool conditions
no string entries; src 0x2c4 base 0x2dc insns 177/183; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_para-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dht :: attempt 1: Huffman lengths and symbol buffers
no string entries; src 0x1e0 base 0x1e0 insns 120/120; diffs 35: [6, 7, 10, 17, 21, 31, 34, 38, 39, 41, 51, 52, 56, 59, 61, 63, 65, 67, 69, 70]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_dht-1

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dht :: attempt 2: loop sum of code counts
no string entries; src 0x1e0 base 0x1e0 insns 120/120; diffs 16: [6, 10, 17, 21, 30, 31, 32, 34, 38, 39, 41, 51, 52, 91, 99, 100]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_dht-2

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dht :: attempt 3: count pointer follows index
no string entries; src 0x1e0 base 0x1e0 insns 120/120; diffs 35: [6, 7, 10, 17, 21, 31, 34, 38, 39, 41, 51, 52, 56, 59, 61, 63, 65, 67, 69, 70]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_dht-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dqt :: attempt 1: typed quantization coefficients
no string entries; src 0x148 base 0x148 insns 82/82; diffs 8: [8, 17, 24, 30, 43, 45, 52, 62]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_dqt-1

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dqt :: attempt 2: array copy using memcpy
no string entries; src 0x130 base 0x148 insns 76/82; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_dqt-2

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dqt :: attempt 3: advance zigzag pointer at read
no string entries; src 0x148 base 0x148 insns 82/82; diffs 35: [8, 17, 24, 25, 26, 30, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_dqt-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_sof :: attempt 1: frame header fields and sample tables
no string entries; src 0x388 base 0x37c insns 226/223; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_sof-1

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_sof :: attempt 2: split zero sample-factor checks
no string entries; src 0x390 base 0x37c insns 228/223; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_sof-2

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_sof :: attempt 3: sampling maximum via conditional expression
no string entries; src 0x388 base 0x37c insns 226/223; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_sof-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_sos :: attempt 1: named component and entropy table fields
no string entries; src 0x1d0 base 0x1c0 insns 116/112; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_sos-1

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_sos :: attempt 2: component index instead of map pointer
no string entries; src 0x1c4 base 0x1c0 insns 113/112; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_sos-2

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_sos :: attempt 3: clamp move result by sign branch
no string entries; src 0x1d0 base 0x1c0 insns 116/112; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_sos-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_err_restart :: attempt 1: restart scan with typed state fields
no string entries; src 0x1c0 base 0x1cc insns 112/115; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_err_restart-1

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_err_restart :: attempt 2: combine restart distance arithmetic
no string entries; src 0x1bc base 0x1cc insns 111/115; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_err_restart-2

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_err_restart :: attempt 3: remainder using modulus
no string entries; src 0x1c0 base 0x1cc insns 112/115; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_err_restart-3

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_scan_varinit :: attempt 4: declare sampling index before factors
no string entries; src 0x204 base 0x204 insns 129/129; diffs 9: [8, 9, 10, 11, 12, 13, 15, 20, 21]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_scan_varinit-4

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_scan_varinit :: attempt 5: compute horizontal scale before vertical load
no string entries; src 0x204 base 0x204 insns 129/129; diffs 9: [8, 9, 10, 11, 12, 13, 15, 20, 21]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_scan_varinit-5

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_scan_varinit :: attempt 6: use promoted factors directly in division
no string entries; src 0x204 base 0x204 insns 129/129; diffs 13: [7, 8, 9, 10, 12, 13, 14, 15, 17, 18, 19, 21, 22]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_scan_varinit-6

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dqt :: attempt 4: nested scale view for quantization flags
no string entries; src 0x148 base 0x148 insns 82/82; diffs 6: [8, 17, 24, 30, 52, 62]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_dqt-4

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dqt :: attempt 5: local coefficient copy declared before scale view
no string entries; src 0x148 base 0x148 insns 82/82; diffs 6: [8, 17, 24, 30, 52, 62]; RESTORED ASM; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_dqt-5

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dqt :: attempt 6: use coefficient copy directly for scale multiplication
no string entries; src 0x148 base 0x148 insns 82/82; diffs 0: []; KEPT; regressions vs baseline: 0; GATE PASS; evidence /tmp/sol-low-asm/TMCJPEGDEC_parse_dqt-6

src/keyboard/tiInputForm :: draw__Q39textinput9inputform12LayoutByNW4RFv :: attempt 1: layout draw and named rectangle fields
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57]; RESTORED ASM; evidence /tmp/sol-low-asm/draw__Q39textinput9inputform12LayoutByNW4RFv-1

src/keyboard/tiInputForm :: draw__Q39textinput9inputform12LayoutByNW4RFv :: attempt 2: read scale before constructing rectangle
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57]; RESTORED ASM; evidence /tmp/sol-low-asm/draw__Q39textinput9inputform12LayoutByNW4RFv-2

src/keyboard/tiInputForm :: draw__Q39textinput9inputform12LayoutByNW4RFv :: attempt 3: rectangle extent temporary expressions
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57]; RESTORED ASM; evidence /tmp/sol-low-asm/draw__Q39textinput9inputform12LayoutByNW4RFv-3

src/keyboard/tiInputForm :: create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer :: attempt 1: allocator and row list insertion
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x120 base 0x120 insns 72/72; diffs 26: [28, 30, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43, 44, 46, 49, 51, 53, 54, 55, 56]; RESTORED ASM; evidence /tmp/sol-low-asm/create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer-1

src/keyboard/tiInputForm :: create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer :: attempt 2: selected row fields loaded before next row
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x120 base 0x120 insns 72/72; diffs 23: [28, 30, 33, 34, 35, 38, 39, 40, 43, 44, 46, 49, 51, 53, 54, 55, 56, 57, 58, 59]; RESTORED ASM; evidence /tmp/sol-low-asm/create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer-2

src/keyboard/tiInputForm :: create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer :: attempt 3: explicit typed allocation byte count
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x120 base 0x120 insns 72/72; diffs 26: [28, 30, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43, 44, 46, 49, 51, 53, 54, 55, 56]; RESTORED ASM; evidence /tmp/sol-low-asm/create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer-3

src/keyboard/tiInputForm :: onPressLeft__Q39textinput9inputform4BaseFv :: attempt 1: typed cursor movement and input relation
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x264 base 0x268 insns 153/154; RESTORED ASM; evidence /tmp/sol-low-asm/onPressLeft__Q39textinput9inputform4BaseFv-1

src/keyboard/tiInputForm :: onPressLeft__Q39textinput9inputform4BaseFv :: attempt 2: switch for kana confirmation
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x268 base 0x268 insns 154/154; diffs 2: [89, 90]; RESTORED ASM; evidence /tmp/sol-low-asm/onPressLeft__Q39textinput9inputform4BaseFv-2

src/keyboard/tiInputForm :: onPressLeft__Q39textinput9inputform4BaseFv :: attempt 3: inline quote and prediction relation reset
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x264 base 0x268 insns 153/154; RESTORED ASM; evidence /tmp/sol-low-asm/onPressLeft__Q39textinput9inputform4BaseFv-3

src/keyboard/tiInputForm :: onPressRight__Q39textinput9inputform4BaseFv :: attempt 1: typed cursor movement and input relation
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x2d8 base 0x2e4 insns 182/185; RESTORED ASM; evidence /tmp/sol-low-asm/onPressRight__Q39textinput9inputform4BaseFv-1

src/keyboard/tiInputForm :: onPressRight__Q39textinput9inputform4BaseFv :: attempt 2: switch for kana confirmation
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x2dc base 0x2e4 insns 183/185; RESTORED ASM; evidence /tmp/sol-low-asm/onPressRight__Q39textinput9inputform4BaseFv-2

src/keyboard/tiInputForm :: onPressRight__Q39textinput9inputform4BaseFv :: attempt 3: inline quote and prediction relation reset
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x2d8 base 0x2e4 insns 182/185; RESTORED ASM; evidence /tmp/sol-low-asm/onPressRight__Q39textinput9inputform4BaseFv-3

src/keyboard/tiInputForm :: calc__Q39textinput9inputform4BaseFv :: attempt 1: scroll animation and named color components
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x294 base 0x294 insns 165/165; diffs 13: [53, 126, 127, 128, 129, 130, 131, 132, 145, 151, 152, 153, 154]; RESTORED ASM; evidence /tmp/sol-low-asm/calc__Q39textinput9inputform4BaseFv-1

src/keyboard/tiInputForm :: calc__Q39textinput9inputform4BaseFv :: attempt 2: cache scroll value across fields
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x290 base 0x294 insns 164/165; RESTORED ASM; evidence /tmp/sol-low-asm/calc__Q39textinput9inputform4BaseFv-2

src/keyboard/tiInputForm :: calc__Q39textinput9inputform4BaseFv :: attempt 3: explicit byte casts for color conversion
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x294 base 0x294 insns 165/165; diffs 13: [53, 126, 127, 128, 129, 130, 131, 132, 145, 151, 152, 153, 154]; RESTORED ASM; evidence /tmp/sol-low-asm/calc__Q39textinput9inputform4BaseFv-3

src/keyboard/tiInputForm :: init__Q49textinput9inputform4Base14RowInfoManagerFv :: attempt 1: initialize bidirectional row and free lists
POOL IDENTICAL up to 20 (mine=20 base=20); src 0xb8 base 0x9c insns 46/39; RESTORED ASM; evidence /tmp/sol-low-asm/init__Q49textinput9inputform4Base14RowInfoManagerFv-1

src/keyboard/tiInputForm :: init__Q49textinput9inputform4Base14RowInfoManagerFv :: attempt 2: wide loop index with bounded access
POOL IDENTICAL up to 20 (mine=20 base=20); src 0xb8 base 0x9c insns 46/39; RESTORED ASM; evidence /tmp/sol-low-asm/init__Q49textinput9inputform4Base14RowInfoManagerFv-2

src/keyboard/tiInputForm :: init__Q49textinput9inputform4Base14RowInfoManagerFv :: attempt 3: store next before previous row link
POOL IDENTICAL up to 20 (mine=20 base=20); src 0xbc base 0x9c insns 47/39; RESTORED ASM; evidence /tmp/sol-low-asm/init__Q49textinput9inputform4Base14RowInfoManagerFv-3

src/keyboard/tiInputForm :: draw__Q39textinput9inputform12LayoutByNW4RFv :: attempt 4: direct scale temporary and rectangle before origin
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x1c8 base 0x1c8 insns 114/114; diffs 12: [50, 56, 59, 60, 63, 64, 65, 66, 67, 69, 73, 75]; RESTORED ASM; evidence /tmp/sol-low-asm/draw__Q39textinput9inputform12LayoutByNW4RFv-4

src/keyboard/tiInputForm :: onPressLeft__Q39textinput9inputform4BaseFv :: attempt 4: switch false case preserves separate return branch
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x26c base 0x268 insns 155/154; RESTORED ASM; evidence /tmp/sol-low-asm/onPressLeft__Q39textinput9inputform4BaseFv-4

src/keyboard/tiInputForm :: calc__Q39textinput9inputform4BaseFv :: attempt 4: color phase and blend operands in target order
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x294 base 0x294 insns 165/165; diffs 13: [53, 126, 127, 128, 129, 130, 131, 132, 145, 151, 152, 153, 154]; RESTORED ASM; evidence /tmp/sol-low-asm/calc__Q39textinput9inputform4BaseFv-4

src/keyboard/tiInputForm :: calc__Q39textinput9inputform4BaseFv :: attempt 5: compute interpolated blue before phase then assign
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x298 base 0x294 insns 166/165; RESTORED ASM; evidence /tmp/sol-low-asm/calc__Q39textinput9inputform4BaseFv-5

src/keyboard/tiInputForm :: init__Q49textinput9inputform4Base14RowInfoManagerFv :: attempt 4: reuse completed row index and end pointers
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x98 base 0x9c insns 38/39; RESTORED ASM; evidence /tmp/sol-low-asm/init__Q49textinput9inputform4Base14RowInfoManagerFv-4

src/keyboard/tiInputForm :: init__Q49textinput9inputform4Base14RowInfoManagerFv :: attempt 5: decrement and restore loop index for end links
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x98 base 0x9c insns 38/39; RESTORED ASM; evidence /tmp/sol-low-asm/init__Q49textinput9inputform4Base14RowInfoManagerFv-5

src/keyboard/tiInputForm :: init__Q49textinput9inputform4Base14RowInfoManagerFv :: attempt 6: cache row storage across both end link writes
POOL IDENTICAL up to 20 (mine=20 base=20); src 0x94 base 0x9c insns 37/39; RESTORED ASM; evidence /tmp/sol-low-asm/init__Q49textinput9inputform4Base14RowInfoManagerFv-6

## Remaining assembly audit

Each remaining function has at least three compiled, distinct source attempts. All remaining asm bodies retain their original instruction-exact implementation. No genuinely hand-written SDK assembly was changed.

libs/RevoEX/src/cdb/CDBDatabase.c: asm 33 -> 15
- CDBDatabaseClose: 3 compiled attempts; src 0xac base 0xb0 insns 43/44
- CDBDatabaseCreateRecordAtOnce: 3 compiled attempts; diffs 8: [5, 7, 14, 15, 23, 24, 25, 26] | diffs 12: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 25, 26]
- CDBDatabaseCreateRecordAtOnceEx: 3 compiled attempts; diffs 12: [23, 24, 26, 27, 28, 29, 37, 38, 39, 40, 42, 45] | diffs 21: [6, 10, 11, 13, 17, 19, 20, 21, 22, 23, 24, 26, 27, 28, 29, 37, 38, 39, 40, 42]
- CDBDatabasePrivateCreateRecordAtOnceEx_: 3 compiled attempts; diffs 19: [39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 59, 60, 61, 62, 64, 66] | diffs 18: [38, 40, 41, 42, 43, 44, 45, 46, 48, 49, 50, 51, 59, 60, 61, 62, 64, 66] | diffs 12: [45, 46, 48, 49, 50, 51, 59, 60, 61, 62, 64, 66]
- CDBDatabaseCreateRecordImAtOnce_: 3 compiled attempts; src 0x120 base 0x150 insns 72/84 | diffs 2: [75, 76]
- CDBDatabaseFindByKey: 7 compiled attempts; instruction exact but string/data regression | src 0xe0 base 0xe4 insns 56/57
- CDBDatabaseSearchCallCallback: 3 compiled attempts; src 0xf8 base 0xf4 insns 62/61 | src 0xf0 base 0xf4 insns 60/61
- CDBDatabaseSearchRecordLayer: 3 compiled attempts; src 0x710 base 0x6fc insns 452/447 | src 0x714 base 0x6fc insns 453/447
- CDBDatabaseSearchMinuteLayer: 3 compiled attempts; src 0x3a4 base 0x3a0 insns 233/232 | src 0x3a8 base 0x3a0 insns 234/232
- CDBDatabaseSearchHourLayer: 3 compiled attempts; src 0x390 base 0x38c insns 228/227 | src 0x394 base 0x38c insns 229/227
- CDBDatabaseSearchDayLayer: 3 compiled attempts; src 0x424 base 0x3f0 insns 265/252 | src 0x428 base 0x3f0 insns 266/252
- CDBDatabaseSearchMonthLayer: 3 compiled attempts; src 0x408 base 0x3c0 insns 258/240 | src 0x404 base 0x3c0 insns 257/240
- CDBDatabaseSearchYearLayer: 3 compiled attempts; src 0x3d0 base 0x378 insns 244/222 | src 0x3cc base 0x378 insns 243/222
- CDBDatabaseSearch_: 3 compiled attempts; src 0xcc base 0xd4 insns 51/53 | src 0xd0 base 0xd4 insns 52/53
- CDBDatabaseCleanUpEmptyDirectories: 3 compiled attempts; src 0x21c base 0x214 insns 135/133

src/sound/iplSound.cpp: asm 14 -> 3
- __dt__Q33ipl3snd6UnkClsFv: 3 compiled attempts; src 0x78 base 0x1c insns 30/7 | src 0x7c base 0x1c insns 31/7
- stopSE__Q33ipl3snd6SystemFPQ34nw4r3snd11SoundHandlei: 3 compiled attempts; src 0xa0 base 0xa8 insns 40/42 | src 0xac base 0xa8 insns 43/42 | diffs 9: [12, 16, 19, 20, 22, 30, 31, 32, 34]
- resetAllSound__Q33ipl3snd6SystemFv: 3 compiled attempts; src 0x10c base 0x110 insns 67/68 | diffs 7: [5, 9, 13, 21, 22, 23, 25] | src 0x114 base 0x110 insns 69/68

src/system/iplSaveDataManager.cpp: asm 8 -> 8
- hasChannel: 3 compiled attempts; diffs 58: [0, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
- getNumValidChannel: 6 compiled attempts; diffs 4: [4, 7, 8, 11] | diffs 10: [0, 1, 4, 7, 8, 11, 14, 17, 19, 21] | src 0x60 base 0x5c insns 24/23 | src 0x58 base 0x5c insns 22/23
- makePriorTitleIDList: 3 compiled attempts; src 0x1ec base 0x214 insns 123/133
- makeTmpList: 3 compiled attempts; src 0x170 base 0x17c insns 92/95 | src 0x168 base 0x17c insns 90/95
- doUpdateChanInfos: 3 compiled attempts; src 0x104 base 0x10c insns 65/67 | diffs 54: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24]
- getAvailableInList: 3 compiled attempts; diffs 10: [0, 2, 11, 12, 13, 14, 15, 16, 21, 23] | src 0x68 base 0x70 insns 26/28
- isEqualChannel: 3 compiled attempts; src 0x8c base 0x9c insns 35/39 | src 0x98 base 0x9c insns 38/39
- iplSavedata_813596B8: 3 compiled attempts; src 0xd4 base 0xe8 insns 53/58 | src 0xd8 base 0xe8 insns 54/58 | diffs 18: [24, 34, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 50, 51, 52, 53, 54]

libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c: asm 9 -> 8
- TMCJPEGDEC_imagestart: 3 compiled attempts; src 0x188 base 0x190 insns 98/100
- TMCJPEGDEC_scan_varinit: 6 compiled attempts; diffs 9: [8, 9, 10, 11, 12, 13, 15, 20, 21] | diffs 18: [8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25] | src 0x1f8 base 0x204 insns 126/129 | diffs 13: [7, 8, 9, 10, 12, 13, 14, 15, 17, 18, 19, 21, 22]
- TMCJPEGDEC_restart_interval: 3 compiled attempts; src 0x16c base 0x174 insns 91/93
- TMCJPEGDEC_parse_para: 3 compiled attempts; src 0x2c4 base 0x2dc insns 177/183 | src 0x2bc base 0x2dc insns 175/183
- TMCJPEGDEC_parse_dht: 3 compiled attempts; diffs 16: [6, 10, 17, 21, 30, 31, 32, 34, 38, 39, 41, 51, 52, 91, 99, 100] | diffs 35: [6, 7, 10, 17, 21, 31, 34, 38, 39, 41, 51, 52, 56, 59, 61, 63, 65, 67, 69, 70]
- TMCJPEGDEC_parse_sof: 3 compiled attempts; src 0x388 base 0x37c insns 226/223 | src 0x390 base 0x37c insns 228/223
- TMCJPEGDEC_parse_sos: 3 compiled attempts; src 0x1c4 base 0x1c0 insns 113/112 | src 0x1d0 base 0x1c0 insns 116/112
- TMCJPEGDEC_err_restart: 3 compiled attempts; src 0x1c0 base 0x1cc insns 112/115 | src 0x1bc base 0x1cc insns 111/115

src/keyboard/tiInputForm.cpp: asm 6 -> 6
- draw__Q39textinput9inputform12LayoutByNW4RFv: 4 compiled attempts; diffs 38: [38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57] | diffs 12: [50, 56, 59, 60, 63, 64, 65, 66, 67, 69, 73, 75]
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: 3 compiled attempts; diffs 26: [28, 30, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43, 44, 46, 49, 51, 53, 54, 55, 56] | diffs 23: [28, 30, 33, 34, 35, 38, 39, 40, 43, 44, 46, 49, 51, 53, 54, 55, 56, 57, 58, 59]
- onPressLeft__Q39textinput9inputform4BaseFv: 4 compiled attempts; src 0x26c base 0x268 insns 155/154 | src 0x264 base 0x268 insns 153/154 | diffs 2: [89, 90]
- onPressRight__Q39textinput9inputform4BaseFv: 3 compiled attempts; src 0x2dc base 0x2e4 insns 183/185 | src 0x2d8 base 0x2e4 insns 182/185
- calc__Q39textinput9inputform4BaseFv: 5 compiled attempts; diffs 13: [53, 126, 127, 128, 129, 130, 131, 132, 145, 151, 152, 153, 154] | src 0x290 base 0x294 insns 164/165 | src 0x298 base 0x294 insns 166/165
- init__Q49textinput9inputform4Base14RowInfoManagerFv: 6 compiled attempts; src 0xb8 base 0x9c insns 46/39 | src 0x98 base 0x9c insns 38/39 | src 0xbc base 0x9c insns 47/39 | src 0x94 base 0x9c insns 37/39

## Baseline below-100 functions

These pre-existing functions are outside the requested asm conversion scope and remain unchanged. None of the retained conversions reduces any exact count or matched bytes.

[src/sound/iplSound]   below 100: __sinit_\iplSound_cpp None
[src/keyboard/tiInputForm]   below 100: onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv 99.98295
[src/keyboard/tiInputForm]   below 100: onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos 99.915436
[src/keyboard/tiInputForm]   below 100: calcCursorPos__Q39textinput9inputform4BaseFff 91.622696
[src/keyboard/tiInputForm]   below 100: onPressUp__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDown__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDownHWKB__Q39textinput9inputform4BaseFv 98.35185
[src/keyboard/tiInputForm]   below 100: onPressLeftHWKB__Q39textinput9inputform4BaseFv 99.97727
[src/keyboard/tiInputForm]   below 100: onPressRightHWKB__Q39textinput9inputform4BaseFv 99.97818
[src/keyboard/tiInputForm]   below 100: create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer 95.02809
[src/keyboard/tiInputForm]   below 100: setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language 96.44726
[src/keyboard/tiInputForm]   below 100: isOverRowLimit__Q39textinput9inputform4BaseFUlPCw 97.184875
[src/keyboard/tiInputForm]   below 100: isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv None

## Conversion commits

ea5a5663 convert cdbdatabaseinit to c
b5991780 convert cdbdatabaseopen to c
54eba73f convert cdbdatabaseprivatecreaterecordatonce to c
34193a8c convert cdbdatabaseprivatecreaterecordatonceex to c
53661dca convert cdbdatabasesearchconditionsismatch to c
53bf274d convert cdbdatabasesearch to c
d78969bc convert cdbdatabaseinstanceinit to c
74924f13 convert cdbdatabaseinstanceisused to c
d4b2ad59 convert cdbissdavailable to c
f3fae5b1 convert cdbmountsd to c
4c972a50 convert cdbunmountsdforce to c
29d80144 convert cdbdatabasecleanupemptydirectoriesrecord to c
6704be7e convert cdbdatabasecleanupemptydirectoriestype to c
008f9768 convert cdbdatabasecleanupemptydirectoriescode to c
50ad2a37 convert cdbdatabasecleanupemptydirectoriesminute to c
155cd177 convert cdbdatabasecleanupemptydirectorieshour to c
cf2cfb87 convert cdbdatabasecleanupemptydirectoriesday to c
3c0a062f convert cdbdatabasecleanupemptydirectoriesmonth to c
e3d2c924 convert  to c
3d4b96f0 convert  to c
4393f530 convert  to c
05e30d7b convert stopbgm to c
a8041ecd convert muteonbgm to c
b350b724 convert muteoffbgm to c
059cc314 convert pauseonse to c
5bd82bee convert pauseoffse to c
37d9077f convert pauseonbgm to c
97a00a8f convert pauseoffbgm to c
ac02e745 convert ct to c
c1480dd8 convert tmcjpegdec_parse_dqt to c

## Review cleanup

Removed unused array view types and restored extern declarations used only by remaining CDB asm. Removed an unused JPEG table pointer. Rebuilt both objects; JPEG quantization remains 82/82 instructions with zero differences. Final full gate covers all five units.

## Scope uncertainty

The generic worker definition asks for a higher instruction-exact count. That is inapplicable to asm conversions already counted as exact; the task-specific acceptance rule is no drop. No new count increase is claimed. Untested compiler tie-break resolutions and pool ordering remain open in the restored asm functions.

Direct-call readability check: replaced the seven typed function-pointer calls with direct calls. All seven remain instruction exact; kept pending final full gate. Evidence: /tmp/sol-low-asm/*.direct.ctx

## Final validation

Fresh full build and full gate across all five units; all 30 retained conversions independently rechecked with ctxdiff after that build:

libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseInit :: src 0x44 base 0x44 insns 17/17; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseOpen :: src 0x50 base 0x50 insns 20/20; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnce :: src 0xec base 0xec insns 59/59; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabasePrivateCreateRecordAtOnceEx :: src 0xb0 base 0xb0 insns 44/44; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearchConditionsIsMatch :: src 0x100 base 0x100 insns 64/64; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseSearch :: src 0xa0 base 0xa0 insns 40/40; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseInstanceInit :: src 0x18 base 0x18 insns 6/6; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseInstanceIsUsed :: src 0x8 base 0x8 insns 2/2; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBIsSDAvailable :: src 0x48 base 0x48 insns 18/18; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBMountSD :: src 0x4 base 0x4 insns 1/1; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBUnmountSDForce :: src 0x34 base 0x34 insns 13/13; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesRecord :: src 0x10c base 0x10c insns 67/67; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesType :: src 0x15c base 0x15c insns 87/87; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesCode :: src 0x14c base 0x14c insns 83/83; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesMinute :: src 0x140 base 0x140 insns 80/80; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesHour :: src 0x134 base 0x134 insns 77/77; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesDay :: src 0x128 base 0x128 insns 74/74; diffs 0: []
libs/RevoEX/src/cdb/CDBDatabase :: CDBDatabaseCleanUpEmptyDirectoriesMonth :: src 0x124 base 0x124 insns 73/73; diffs 0: []
src/sound/iplSound :: __ct__Q33ipl3snd6SystemFv :: src 0x4c base 0x4c insns 19/19; diffs 0: []
src/sound/iplSound :: __dt__Q33ipl3snd10tagSSeInfoFv :: src 0x58 base 0x58 insns 22/22; diffs 0: []
src/sound/iplSound :: __dt__Q33ipl3snd11tagSBgmInfoFv :: src 0x58 base 0x58 insns 22/22; diffs 0: []
src/sound/iplSound :: stopBGM__Q33ipl3snd6SystemFi :: src 0x34 base 0x34 insns 13/13; diffs 0: []
src/sound/iplSound :: muteOnBGM__Q33ipl3snd6SystemFi :: src 0x34 base 0x34 insns 13/13; diffs 0: []
src/sound/iplSound :: muteOffBGM__Q33ipl3snd6SystemFi :: src 0x34 base 0x34 insns 13/13; diffs 0: []
src/sound/iplSound :: pauseOnSE__Q33ipl3snd6SystemFv :: src 0x74 base 0x74 insns 29/29; diffs 0: []
src/sound/iplSound :: pauseOffSE__Q33ipl3snd6SystemFv :: src 0x74 base 0x74 insns 29/29; diffs 0: []
src/sound/iplSound :: pauseOnBGM__Q33ipl3snd6SystemFv :: src 0xa8 base 0xa8 insns 42/42; diffs 0: []
src/sound/iplSound :: pauseOffBGM__Q33ipl3snd6SystemFv :: src 0x80 base 0x80 insns 32/32; diffs 0: []
src/sound/iplSound :: __ct__Q34nw4r3snd11SoundHandleFv :: src 0xc base 0xc insns 3/3; diffs 0: []
libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main :: TMCJPEGDEC_parse_dqt :: src 0x148 base 0x148 insns 82/82; diffs 0: []

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
[src/sound/iplSound] pool: IDENTICAL
[src/sound/iplSound] objdiff: code 5396/5576 data 144/3316 functions 56/57 fuzzy 96.7719 linked code 0
[src/sound/iplSound] instruction-exact functions: 56/57
[src/sound/iplSound]   section .bss size 3128 match None
[src/sound/iplSound]   section .ctors size 4 match None
[src/sound/iplSound]   section .data size 120 match 100.0
[src/sound/iplSound]   section .rodata size 24 match 100.0
[src/sound/iplSound]   section .sbss size 16 match 50.0
[src/sound/iplSound]   section .sdata2 size 24 match 60.000004
[src/sound/iplSound]   section .text size 5576 match 96.77188
[src/sound/iplSound]   below 100: __sinit_\iplSound_cpp None
[src/sound/iplSound] baseline: code 5396/5576 data 144 functions 56 fuzzy 96.7719
[src/system/iplSaveDataManager] pool: IDENTICAL
[src/system/iplSaveDataManager] objdiff: code 7172/7172 data 968/968 functions 35/35 fuzzy 100.0000 linked code 7172
[src/system/iplSaveDataManager] instruction-exact functions: 35/35
[src/system/iplSaveDataManager]   section .data size 184 match 100.0
[src/system/iplSaveDataManager]   section .rodata size 768 match 100.0
[src/system/iplSaveDataManager]   section .sdata size 16 match 100.0
[src/system/iplSaveDataManager]   section .text size 7172 match 100.0
[src/system/iplSaveDataManager] baseline: code 7172/7172 data 968 functions 35 fuzzy 100.0000
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] objdiff: code 5604/5604 data 256/256 functions 13/13 fuzzy 100.0000 linked code 5604
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] instruction-exact functions: 13/13
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .rodata size 256 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main]   section .text size 5604 match 100.0
[libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main] baseline: code 5604/5604 data 256 functions 13 fuzzy 100.0000
[src/keyboard/tiInputForm] pool: IDENTICAL
[src/keyboard/tiInputForm] objdiff: code 30712/50656 data 908/3772 functions 209/221 fuzzy 99.4500 linked code 0
[src/keyboard/tiInputForm] instruction-exact functions: 207/221
[src/keyboard/tiInputForm]   section .bss size 96 match None
[src/keyboard/tiInputForm]   section .ctors size 4 match 100.0
[src/keyboard/tiInputForm]   section .data size 2736 match 65.53332
[src/keyboard/tiInputForm]   section .rodata size 760 match 100.0
[src/keyboard/tiInputForm]   section .sbss size 32 match 33.333336
[src/keyboard/tiInputForm]   section .sdata size 40 match 100.0
[src/keyboard/tiInputForm]   section .sdata2 size 104 match 100.0
[src/keyboard/tiInputForm]   section .text size 50656 match 99.45001
[src/keyboard/tiInputForm]   below 100: onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv 99.98295
[src/keyboard/tiInputForm]   below 100: onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos 99.915436
[src/keyboard/tiInputForm]   below 100: calcCursorPos__Q39textinput9inputform4BaseFff 91.622696
[src/keyboard/tiInputForm]   below 100: onPressUp__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDown__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDownHWKB__Q39textinput9inputform4BaseFv 98.35185
[src/keyboard/tiInputForm]   below 100: onPressLeftHWKB__Q39textinput9inputform4BaseFv 99.97727
[src/keyboard/tiInputForm]   below 100: onPressRightHWKB__Q39textinput9inputform4BaseFv 99.97818
[src/keyboard/tiInputForm]   below 100: create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer 95.02809
[src/keyboard/tiInputForm]   below 100: setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language 96.44726
[src/keyboard/tiInputForm]   below 100: isOverRowLimit__Q39textinput9inputform4BaseFUlPCw 97.184875
[src/keyboard/tiInputForm]   below 100: isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv None
[src/keyboard/tiInputForm] baseline: code 30712/50656 data 908 functions 209 fuzzy 99.4500
regressions vs baseline: 0
global matched_code_percent: 86.44605 -> 86.44605
global fuzzy_match_percent: 98.92996 -> 98.92996
global complete_code_percent: 60.34391 -> 60.34391
global matched_data_percent: 90.91649 -> 90.91649
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

## Before and after

Unit | Asm bodies | Instruction-exact functions | Objdiff matched code bytes | Objdiff matched data bytes
--- | --- | --- | --- | ---
CDBDatabase | 33 -> 15 | 33 -> 33 | 12152 -> 12152 | 312 -> 312
iplSound | 14 -> 3 | 56 -> 56 | 5396 -> 5396 | 144 -> 144
iplSaveDataManager | 8 -> 8 | 35 -> 35 | 7172 -> 7172 | 968 -> 968
jdec_main | 9 -> 8 | 13 -> 13 | 5604 -> 5604 | 256 -> 256
tiInputForm | 6 -> 6 | 207 -> 207 | 30712 -> 30712 | 908 -> 908

Changed source: libs/RevoEX/src/cdb/CDBDatabase.c; src/sound/iplSound.cpp; libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c. Headers: include/sound/iplSound.h; libs/NW4R/include/nw4r/snd/SoundHandle.h. Attempt log: tools/decomp-assist/asm-conversions.attempts.md. SaveDataManager and tiInputForm experiments were restored entirely.

40 remaining asm functions, each with at least 3 compiled distinct source-level attempts. 30 conversions committed individually after full gates. No regression, forbidden-pattern addition, or readability warning in the final gate.
