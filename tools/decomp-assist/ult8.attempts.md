# ult8 ultra worker attempts

2026-10-03. Branch agent/w1003/sol-ult8-ultra, entry 140117ea. Only sol-low edits. Read AGENTS.md and ult8.md; prior ezi1/ezi2 stash logs and fz1/fz15 structural evidence read. New attempts avoid prior isolated variants. Initial tool call successfully executed, historical bubblewrap failure absent. One initial commentary required by harness was sent before reading silent prompt; no further narrative output.

Baseline main/libs/RVLMiddleware/eZiText/src/clib/zi8getc2: exact 15/17; code 6360/6888; data 332/332.
POOL IDENTICAL up to 0 (mine=0 base=0)
Baseline main/libs/RVLMiddleware/eZiText/src/clib/zi8match: exact 8/10; code 5172/8256; data 728/728.
POOL IDENTICAL up to 0 (mine=0 base=0)
Baseline main/libs/RVLMiddleware/eZiText/src/clib/zidawg1: exact 4/6; code 888/1664; data 80/80.
POOL IDENTICAL up to 0 (mine=0 base=0)
Baseline main/libs/RVLMiddleware/eZiText/src/clib/zkokeyp: exact 1/7; code 332/5200; data 96/180.
POOL IDENTICAL up to 0 (mine=0 base=0)
Baseline main/libs/RVLMiddleware/eZiText/src/clib/zoemdata: exact 2/3; code 208/976; data 60/60.
POOL IDENTICAL up to 0 (mine=0 base=0)
Data audit: zkokeyp real .data switch table 40 bytes and extab 56 bytes identical. extabindex 84-byte deficit follows function sizes 0x560 vs 0x55c and 0xa7c vs 0xa74. Relocations pair the same functions and extab records. No symbol rename or extent correction justified. Other four units data already 100%. All 13 open functions are above 98%, so structural-first focus is the two Korean functions, then saved-register cycles and PyFinal scratch registers.

Remote check zkokeyp: fetch 0, owned source unchanged on origin/main.

## Zi8_814834AC structural diagnosis
Target CFG and calls match source: elementCount zero drains/copies candidates; >9 drops them; table9/table10 lookup errors; GetTableCount -> pack five keys -> scan key bytes -> mark candidates -> compact/insert. Frame0x50. One extra initial byte narrowing, two table-address operand associations, work/candidate saved-register swap. Prior array-at-entry and union-word variants failed; test array initialization at its semantic position and flat actual locals.

Remote check zkokeyp: fetch 0, owned source unchanged on origin/main.

## Zi8_814834AC structural diagnosis
Target CFG and calls match source: elementCount zero drains/copies candidates; >9 drops them; table9/table10 lookup errors; GetTableCount -> pack five keys -> scan key bytes -> mark candidates -> compact/insert. Frame0x50. One extra initial byte narrowing, two table-address operand associations, work/candidate saved-register swap. Prior array-at-entry and union-word variants failed; test array initialization at its semantic position and flat actual locals.
Zi8_814834AC | flatten meaningful filter locals, separate key clear | insns 344/343, structural 30, diffs 330, sha256 eb3f26386faf; first [(9, ('mr', 'r25, r7'), ('mr', 'r26, r7')), (12, ('stb', 'r0, 8(r1)'), ('stb', 'r0, 9(r1)')), (16, ('li', 'r0, 0'), ('stb', 'r0, 0x20(r1)')), (17, ('stb', 'r0, 0x20(r1)'), ('li', 'r3, 0x64'))]
Zi8_814834AC | flat locals with array initialization after counters | insns 346/343, structural 35, diffs 341, sha256 49a5a5ab299e; first [(5, ('mr', 'r31, r1'), ('mr', 'r31, r3')), (6, ('mr', 'r30, r3'), ('mr', 'r29, r4')), (7, ('mr', 'r28, r4'), ('mr', 'r30, r5')), (8, ('mr', 'r29, r5'), ('mr', 'r23, r6'))]
Zi8_814834AC | five-byte initialized key array after existing counters | insns 346/343, structural 42, diffs 341, sha256 a47a118adb13; first [(5, ('mr', 'r31, r1'), ('mr', 'r31, r3')), (6, ('mr', 'r30, r3'), ('mr', 'r29, r4')), (7, ('mr', 'r28, r4'), ('mr', 'r30, r5')), (8, ('mr', 'r29, r5'), ('mr', 'r23, r6'))]
Zi8_814834AC | compiler builtin five-byte key initialization | insns 344/343, structural 3, diffs 331, sha256 b0b6eac23d8a; first [(9, ('mr', 'r25, r7'), ('mr', 'r26, r7')), (14, ('addi', 'r3, r1, 0x1c'), ('li', 'r0, 0')), (15, ('li', 'r4, 0'), ('stw', 'r0, 0x1c(r1)')), (16, ('li', 'r5, 5'), ('stb', 'r0, 0x20(r1)'))]

## Zi8GetKOcandidates structural diagnosis
Target CFG: scratch clear -> tables9/10 -> reset output -> prefix-word traversal and duplicate filtering -> key-table scan -> two match passes -> candidate insertion. Calls are same source sequence. Frame0x60; extra suffix li, wordTable mr, prefixCount/candidateIndex stack ownership crossed. Prior isolated wordTable prototype/key initialization/address rearrangements exhausted. Test flat meaningful locals and target storage types as combined structural corrections.
Zi8GetKOcandidates | flatten Korean search state into its semantic locals | insns 684/669, structural 197, diffs 677, sha256 7b149e8c92f2; first [(3, ('stw', 'r31, 0x5c(r1)'), ('addi', 'r11, r1, 0x60')), (4, ('stw', 'r30, 0x58(r1)'), ('bl', 0)), (5, ('stw', 'r29, 0x54(r1)'), ('mr', 'r31, r3')), (6, ('stw', 'r28, 0x50(r1)'), ('mr', 'r30, r4'))]
Zi8GetKOcandidates | native stored table address, counter order and builtin key clear | insns 670/669, structural 7, diffs 657, sha256 a9fedd261019; first [(13, ('addi', 'r3, r1, 0x38'), ('li', 'r0, 0')), (14, ('li', 'r4, 0'), ('stw', 'r0, 0x38(r1)')), (15, ('li', 'r5, 5'), ('stb', 'r0, 0x3c(r1)')), (16, ('bl', 0), ('li', 'r0, 0'))]
Zi8GetKOcandidates | five-byte initialized packed keys after result initialization | insns 673/669, structural 207, diffs 668, sha256 bce71cf24633; first [(5, ('mr', 'r31, r1'), ('mr', 'r31, r3')), (6, ('mr', 'r30, r3'), ('mr', 'r30, r4')), (7, ('mr', 'r29, r4'), ('mr', 'r27, r5')), (8, ('mr', 'r26, r5'), ('lis', 'r3, 1'))]

Remote check zi8getc2: fetch 0, owned source unchanged on origin/main.

## Zi8IsDupWChar
CFG calls and all63 instructions already match; only character/duplicate r27/r28 cycle. Buffer reset -> backward scan -> append/reset -> LogError. Prior while/continue/width variants read. Try branch labels outside lexical loop to lower duplicate reference weight without changing the operation.
Zi8IsDupWChar | explicit scan edges with duplicate outside lexical loop | insns 63/63, structural 0, diffs 8, sha256 f44ce0719455; first [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (7, ('li', 'r28, 0'), ('li', 'r27, 0')), (14, ('sth', 'r27, 2(r31)'), ('sth', 'r28, 2(r31)')), (25, ('clrlwi', 'r3, r27, 0x10'), ('clrlwi', 'r3, r28, 0x10'))]
Zi8IsDupWChar | scan with shared append exit and ordinary equality | insns 63/63, structural 0, diffs 8, sha256 3f2c9c8b44f5; first [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (7, ('li', 'r28, 0'), ('li', 'r27, 0')), (14, ('sth', 'r27, 2(r31)'), ('sth', 'r28, 2(r31)')), (25, ('clrlwi', 'r3, r27, 0x10'), ('clrlwi', 'r3, r28, 0x10'))]
Zi8IsDupWChar | duplicate assignment beyond for-loop lifetime | insns 63/63, structural 7, diffs 14, sha256 a9afe4d29f8a; first [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (7, ('li', 'r28, 0'), ('li', 'r27, 0')), (14, ('sth', 'r27, 2(r31)'), ('sth', 'r28, 2(r31)')), (24, ('b', 28), ('b', 36))]

## Zi8GetDataSignature
Identical69 instructions and frame0x30; signature/language/destination cycle. No loop. Calls FormatVersion -> TableAddress -> TableCount -> Memcpy -> LogError. Prior generic formal casts, termination pointer and language switch fail. Test statement boundary plus actual byte views.
Zi8GetDataSignature | callback source bytes declared readonly, conversion only at copy | insns 69/69, structural 0, diffs 9, sha256 3bfc7de4ee00; first [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (7, ('mr', 'r28, r5'), ('mr', 'r29, r5')), (9, ('clrlwi', 'r0, r28, 0x18'), ('clrlwi', 'r0, r29, 0x18')), (28, ('clrlwi', 'r3, r28, 0x18'), ('clrlwi', 'r3, r29, 0x18'))]
Zi8GetDataSignature | destination expressed as mutable array parameter | insns 69/69, structural 0, diffs 9, sha256 1fc46adcbad1; first [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (7, ('mr', 'r28, r5'), ('mr', 'r29, r5')), (9, ('clrlwi', 'r0, r28, 0x18'), ('clrlwi', 'r0, r29, 0x18')), (28, ('clrlwi', 'r3, r28, 0x18'), ('clrlwi', 'r3, r29, 0x18'))]
Zi8GetDataSignature | table lookup stored as native address, convert only at copy | insns 69/69, structural 0, diffs 9, sha256 e369c073a9f4; first [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (7, ('mr', 'r28, r5'), ('mr', 'r29, r5')), (9, ('clrlwi', 'r0, r28, 0x18'), ('clrlwi', 'r0, r29, 0x18')), (28, ('clrlwi', 'r3, r28, 0x18'), ('clrlwi', 'r3, r29, 0x18'))]

Remote check zidawg1: fetch 0, owned source unchanged on origin/main.

## ZiDAWGgetCHARattribute
Identical60 instructions/frame0x20. context31/key30 target, context30/key31 source. Decode byte key -> cap check -> three attribute fragments -> LogError. Prior generic context, wide key and assignment compounds failed. Try readonly context and stronger decoded byte view without changing shared declarations.
ZiDAWGgetCHARattribute | readonly context formal | insns 60/60, structural 0, diffs 12, sha256 8432e9472333; first [(5, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (14, ('clrlwi', 'r31, r0, 0x18'), ('clrlwi', 'r30, r0, 0x18')), (18, ('clrlwi', 'r31, r0, 0x18'), ('clrlwi', 'r30, r0, 0x18')), (19, ('clrlwi', 'r3, r31, 0x18'), ('clrlwi', 'r3, r30, 0x18'))]
ZiDAWGgetCHARattribute | decode from readonly byte pointer formal | insns 60/60, structural 0, diffs 12, sha256 c16125f53ada; first [(5, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (14, ('clrlwi', 'r31, r0, 0x18'), ('clrlwi', 'r30, r0, 0x18')), (18, ('clrlwi', 'r31, r0, 0x18'), ('clrlwi', 'r30, r0, 0x18')), (19, ('clrlwi', 'r3, r31, 0x18'), ('clrlwi', 'r3, r30, 0x18'))]
ZiDAWGgetCHARattribute | construct high-key and two attribute fragments with explicit assignments | insns 60/60, structural 0, diffs 12, sha256 672ffe442d52; first [(5, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (14, ('clrlwi', 'r31, r0, 0x18'), ('clrlwi', 'r30, r0, 0x18')), (18, ('clrlwi', 'r31, r0, 0x18'), ('clrlwi', 'r30, r0, 0x18')), (19, ('clrlwi', 'r3, r31, 0x18'), ('clrlwi', 'r3, r30, 0x18'))]

## ZiDAWGGetGraphInfo
134instructions/frame0x30 already exact under context/graph/result register cycle. GetGraph -> root guards -> bounded key/entry traversal -> child/end pointers. Target stw endNode immediately reloads it with no intervening call/store. Definition-level volatile endNode is justified but must be local to this unit and gated for all sibling functions.
ZiDAWGGetGraphInfo | word result address unsigned and direct context access | insns 134/134, structural 0, diffs 11, sha256 332f65ed6f6a; first [(10, ('mr', 'r28, r3'), ('mr', 'r26, r3')), (35, ('add', 'r26, r31, r0'), ('add', 'r27, r31, r0')), (37, ('li', 'r27, 0'), ('li', 'r28, 0')), (62, ('cmplw', 'r31, r26'), ('cmplw', 'r31, r27'))]
ZiDAWGGetGraphInfo | key input readonly with unsigned result address | insns 134/134, structural 0, diffs 12, sha256 9d689a957363; first [(5, ('mr', 'r25, r3'), ('mr', 'r29, r3')), (8, ('mr', 'r3, r25'), ('mr', 'r3, r29')), (10, ('mr', 'r29, r3'), ('mr', 'r26, r3')), (11, ('li', 'r26, 0'), ('li', 'r25, 0'))]
ZiDAWGGetGraphInfo | explicit traversal test with shared graph result | insns 134/134, structural 0, diffs 12, sha256 1820054bffc0; first [(5, ('mr', 'r25, r3'), ('mr', 'r29, r3')), (8, ('mr', 'r3, r25'), ('mr', 'r3, r29')), (10, ('mr', 'r29, r3'), ('mr', 'r26, r3')), (11, ('li', 'r26, 0'), ('li', 'r25, 0'))]
ZiDAWGGetGraphInfo | definition-level volatile endNode | insns 134/134, structural 0, diffs 12, sha256 9b7a79ec09e8; first [(5, ('mr', 'r25, r3'), ('mr', 'r29, r3')), (8, ('mr', 'r3, r25'), ('mr', 'r3, r29')), (10, ('mr', 'r29, r3'), ('mr', 'r26, r3')), (11, ('li', 'r26, 0'), ('li', 'r25, 0'))]
ZiDAWGGetGraphInfo | volatile endNode with direct mutable context fields | insns 134/134, structural 0, diffs 11, sha256 91ecdfa7541c; first [(10, ('mr', 'r28, r3'), ('mr', 'r26, r3')), (35, ('add', 'r26, r31, r0'), ('add', 'r27, r31, r0')), (37, ('li', 'r27, 0'), ('li', 'r28, 0')), (62, ('cmplw', 'r31, r26'), ('cmplw', 'r31, r27'))]
ZiDAWGGetGraphInfo | volatile endNode and native unsigned result | insns 134/134, structural 0, diffs 11, sha256 f8326b02bac0; first [(10, ('mr', 'r28, r3'), ('mr', 'r26, r3')), (35, ('add', 'r26, r31, r0'), ('add', 'r27, r31, r0')), (37, ('li', 'r27, 0'), ('li', 'r28, 0')), (62, ('cmplw', 'r31, r26'), ('cmplw', 'r31, r27'))]
Definition-level volatile endNode experiments restored. No header change retained. Target reload proof applies only GetGraphInfo; no use-site volatile cast used.

Remote check zkokeyp: fetch 0, owned source unchanged on origin/main.

## Zi8_8148302C
Frame and instruction counts already identical; remaining saved-register cycle only. Existing byte/word cursor, loop, declaration, explicit assignment and generic-cast prior experiments read. Test true typed-work formal, immutable pointer values, and fixed typed scratch view where applicable.
Zi8_8148302C | native typed workspace formal without repeated work casts | insns 59/59, structural 0, diffs 6, sha256 064f411ee0a3; first [(7, ('mr', 'r27, r5'), ('mr', 'r29, r5')), (12, ('mr', 'r5, r27'), ('mr', 'r5, r29')), (32, ('clrlwi', 'r29, r0, 0x10'), ('clrlwi', 'r27, r0, 0x10')), (34, ('cmplw', 'r29, r0'), ('cmplw', 'r27, r0'))]
Zi8_8148302C | readonly table and signed decoded value | insns 59/59, structural 1, diffs 6, sha256 f7afe9b3b918; first [(7, ('mr', 'r27, r5'), ('mr', 'r29, r5')), (12, ('mr', 'r5, r27'), ('mr', 'r5, r29')), (32, ('clrlwi', 'r29, r0, 0x10'), ('clrlwi', 'r27, r0, 0x10')), (34, ('cmpw', 'r29, r0'), ('cmplw', 'r27, r0'))]
Zi8_8148302C | wide table cursor with explicit table-index width at reads | insns 59/59, structural 1, diffs 7, sha256 65fa34a63ef7; first [(7, ('mr', 'r27, r5'), ('mr', 'r29, r5')), (12, ('mr', 'r5, r27'), ('mr', 'r5, r29')), (32, ('clrlwi', 'r29, r0, 0x10'), ('clrlwi', 'r27, r0, 0x10')), (34, ('cmplw', 'r29, r0'), ('cmplw', 'r27, r0'))]

## Zi8_81483264
Frame and instruction counts already identical; remaining saved-register cycle only. Existing byte/word cursor, loop, declaration, explicit assignment and generic-cast prior experiments read. Test true typed-work formal, immutable pointer values, and fixed typed scratch view where applicable.
Zi8_81483264 | native typed workspace formal without repeated work casts | insns 41/41, structural 0, diffs 8, sha256 d4319cf61744; first [(6, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (8, ('lwz', 'r0, 0x24(r30)'), ('lwz', 'r0, 0x24(r31)')), (17, ('li', 'r31, 0'), ('li', 'r30, 0')), (20, ('lwz', 'r3, 0x24(r30)'), ('lwz', 'r3, 0x24(r31)'))]
Zi8_81483264 | immutable argument pointers and equality termination at capacity | insns 41/41, structural 1, diffs 9, sha256 72e818857f99; first [(6, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (8, ('lwz', 'r0, 0x24(r30)'), ('lwz', 'r0, 0x24(r31)')), (17, ('li', 'r31, 0'), ('li', 'r30, 0')), (20, ('lwz', 'r3, 0x24(r30)'), ('lwz', 'r3, 0x24(r31)'))]
Zi8_81483264 | typed halfword scratch array within this unit | insns 41/41, structural 0, diffs 8, sha256 8664d0df5f63; first [(6, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (8, ('lwz', 'r0, 0x24(r30)'), ('lwz', 'r0, 0x24(r31)')), (17, ('li', 'r31, 0'), ('li', 'r30, 0')), (20, ('lwz', 'r3, 0x24(r30)'), ('lwz', 'r3, 0x24(r31)'))]

## Zi8_81483308
Frame and instruction counts already identical; remaining saved-register cycle only. Existing byte/word cursor, loop, declaration, explicit assignment and generic-cast prior experiments read. Test true typed-work formal, immutable pointer values, and fixed typed scratch view where applicable.
Zi8_81483308 | native typed workspace formal without repeated work casts | insns 58/58, structural 0, diffs 9, sha256 58aee39b6e1c; first [(7, ('mr', 'r29, r5'), ('mr', 'r30, r5')), (22, ('li', 'r30, 0'), ('li', 'r29, 0')), (26, ('clrlwi', 'r0, r30, 0x18'), ('clrlwi', 'r0, r29, 0x18')), (33, ('addi', 'r30, r30, 1'), ('addi', 'r29, r29, 1'))]
Zi8_81483308 | immutable argument pointers and equality termination at capacity | insns 58/58, structural 1, diffs 10, sha256 7680c857f308; first [(7, ('mr', 'r29, r5'), ('mr', 'r30, r5')), (22, ('li', 'r30, 0'), ('li', 'r29, 0')), (26, ('clrlwi', 'r0, r30, 0x18'), ('clrlwi', 'r0, r29, 0x18')), (33, ('addi', 'r30, r30, 1'), ('addi', 'r29, r29, 1'))]
Zi8_81483308 | typed halfword scratch array within this unit | insns 58/58, structural 0, diffs 9, sha256 117033a2e173; first [(7, ('mr', 'r29, r5'), ('mr', 'r30, r5')), (22, ('li', 'r30, 0'), ('li', 'r29, 0')), (26, ('clrlwi', 'r0, r30, 0x18'), ('clrlwi', 'r0, r29, 0x18')), (33, ('addi', 'r30, r30, 1'), ('addi', 'r29, r29, 1'))]

## Zi8_814833F0
Frame and instruction counts already identical; remaining saved-register cycle only. Existing byte/word cursor, loop, declaration, explicit assignment and generic-cast prior experiments read. Test true typed-work formal, immutable pointer values, and fixed typed scratch view where applicable.
Zi8_814833F0 | native typed workspace formal without repeated work casts | insns 47/47, structural 0, diffs 8, sha256 25cecb671d9a; first [(6, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (13, ('lwz', 'r0, 0x24(r30)'), ('lwz', 'r0, 0x24(r31)')), (22, ('li', 'r31, 0'), ('li', 'r30, 0')), (26, ('lwz', 'r3, 0x24(r30)'), ('lwz', 'r3, 0x24(r31)'))]
Zi8_814833F0 | immutable argument pointers and equality termination at capacity | insns 47/47, structural 1, diffs 9, sha256 88c3842d0b46; first [(6, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (13, ('lwz', 'r0, 0x24(r30)'), ('lwz', 'r0, 0x24(r31)')), (22, ('li', 'r31, 0'), ('li', 'r30, 0')), (26, ('lwz', 'r3, 0x24(r30)'), ('lwz', 'r3, 0x24(r31)'))]
Zi8_814833F0 | typed halfword scratch array within this unit | insns 47/47, structural 0, diffs 8, sha256 b0661dad1b59; first [(6, ('mr', 'r30, r3'), ('mr', 'r31, r3')), (13, ('lwz', 'r0, 0x24(r30)'), ('lwz', 'r0, 0x24(r31)')), (22, ('li', 'r31, 0'), ('li', 'r30, 0')), (26, ('lwz', 'r3, 0x24(r30)'), ('lwz', 'r3, 0x24(r31)'))]

Remote check zi8match: fetch 0, owned source unchanged on origin/main.

## Zi8GetPyFinal
53/53 instructions, no saved-register cycle. Only row stride/base temporaries r6/r7 differ in two output lookups; initial comparison already exact. Prior qualifier, array, dereference, row-view cast, local snapshot and row type trials read. Test real table record definition preserving all432bytes, then actual destination element views.
Zi8GetPyFinal | actual pinyin-final record with named output fields | insns 53/53, structural 0, diffs 8, sha256 2b7c48996e09; first [(26, ('slwi', 'r6, r0, 3'), ('slwi', 'r7, r0, 3')), (27, ('lis', 'r7, 0'), ('lis', 'r6, 0')), (28, ('addi', 'r0, r7, 0'), ('addi', 'r0, r6, 0')), (29, ('add', 'r6, r0, r6'), ('add', 'r6, r0, r7'))]
Zi8GetPyFinal | signed decoded component view then native output width | insns 55/53, structural 5, diffs 30, sha256 bd54f3826aee; first [(5, ('b', 168), ('b', 160)), (24, ('blt', 84), ('blt', 76)), (26, ('slwi', 'r6, r0, 3'), ('slwi', 'r7, r0, 3')), (27, ('lis', 'r7, 0'), ('lis', 'r6, 0'))]
Zi8GetPyFinal | flat constant table view at actual record component indices | insns 53/53, structural 0, diffs 8, sha256 a8a729acd292; first [(26, ('slwi', 'r6, r0, 3'), ('slwi', 'r7, r0, 3')), (27, ('lis', 'r7, 0'), ('lis', 'r6, 0')), (28, ('addi', 'r0, r7, 0'), ('addi', 'r0, r6, 0')), (29, ('add', 'r6, r6, r0'), ('add', 'r6, r0, r7'))]

## Zi8GetPyPhonetic
718/718 instructions/frame0x250, shape exact under saved register map. Call helpers and CFG match. Target resultCount lower-priority r25, decoded value31/current30/index29/final28/initial26. Prior uniform count increments alter instructions and saved pointer casts/width variations fail. Test native signed decoded value, true initial-count output-array view, and compound assignment form of increments.
Zi8GetPyPhonetic | signed decoded character accumulator with halfword reads | insns 720/718, structural 41, diffs 627, sha256 6f7468de8e0f; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r26, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r31, r7'), ('mr', 'r25, r7')), (13, ('addi', 'r29, r1, 0x20'), ('addi', 'r30, r1, 0x20'))]
Zi8GetPyPhonetic | result-count output as a byte-array formal | insns 718/718, structural 0, diffs 167, sha256 54b111d28636; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r26, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r31, r7'), ('mr', 'r25, r7')), (13, ('addi', 'r29, r1, 0x20'), ('addi', 'r30, r1, 0x20'))]
Zi8GetPyPhonetic | compound result-count updates instead of repeated self assignments | insns 718/718, structural 0, diffs 105, sha256 9efd704473de; first [(6, ('mr', 'r25, r4'), ('mr', 'r24, r4')), (8, ('mr', 'r27, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r24, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r24)'), ('stb', 'r0, 0(r25)'))]

Remote check zoemdata: fetch 0, owned source unchanged on origin/main.

## Zi8MatchOEMdata
192/192 instructions/frame0x40, zero structural changes. Calls callback -> WC2Key/ChangeCharCase as needed, OEM retry/reset/fallback CFG identical. Target workspace29/pattern28/length27/index26/complete25/capacity24/fallback23; source index29/work28/... . Prior loop/index/bounds/local workspace variants read. Try readonly pattern and typed workspace formals, then signed position with typed workspace combination.
Zi8MatchOEMdata | readonly pattern formal | insns 194/192, structural 19, diffs 129, sha256 0f52e045e033; first [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (6, ('mr', 'r26, r4'), ('mr', 'r27, r4')), (9, ('mr', 'r23, r7'), ('mr', 'r24, r7')), (12, ('mr', 'r28, r10'), ('mr', 'r29, r10'))]
Zi8MatchOEMdata | native typed workspace formal | insns 192/192, structural 0, diffs 62, sha256 0c17e62aa0de; first [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (6, ('mr', 'r26, r4'), ('mr', 'r27, r4')), (9, ('mr', 'r23, r7'), ('mr', 'r24, r7')), (12, ('mr', 'r30, r10'), ('mr', 'r29, r10'))]
Zi8MatchOEMdata | typed workspace formal and signed pattern cursor | insns 192/192, structural 0, diffs 62, sha256 e250ca10035c; first [(5, ('mr', 'r27, r3'), ('mr', 'r28, r3')), (6, ('mr', 'r26, r4'), ('mr', 'r27, r4')), (9, ('mr', 'r23, r7'), ('mr', 'r24, r7')), (12, ('mr', 'r30, r10'), ('mr', 'r29, r10'))]
PyFinal audit: actual record-table trial overlaps prior zi8match typed record evidence and is excluded from new distinct-attempt coverage. Add source output-statement forms not tested in saved logs.
Zi8GetPyFinal | paired component outputs in one comma statement | insns 55/53, structural 8, diffs 55, sha256 94c6921aa1ff; first [(0, ('stwu', 'r1, -0x20(r1)'), ('stwu', 'r1, -0x10(r1)')), (1, ('stw', 'r31, 0x1c(r1)'), ('stw', 'r31, 0xc(r1)')), (2, ('stw', 'r30, 0x18(r1)'), ('stw', 'r30, 8(r1)')), (3, ('stw', 'r29, 0x14(r1)'), ('li', 'r31, 0'))]
Zi8GetPyFinal | return success after both component output assignments | insns 56/53, structural 12, diffs 56, sha256 46d326669f46; first [(0, ('stwu', 'r1, -0x20(r1)'), ('stwu', 'r1, -0x10(r1)')), (1, ('stw', 'r31, 0x1c(r1)'), ('stw', 'r31, 0xc(r1)')), (2, ('stw', 'r30, 0x18(r1)'), ('stw', 'r30, 8(r1)')), (3, ('stw', 'r29, 0x14(r1)'), ('li', 'r31, 0'))]

## PyPhonetic follow-up after compound update gain
Compound result-count updates preserve718instructions and improve diffs167->105. Value/current/index/initial now exact; remaining two independent cycles count/resultCount and final/outputIndex. Try fold outputIndex update into its actual capacity test and mixtures of explicit count self-updates with compound updates. These are real output/count operations, no extra references added.
Zi8GetPyPhonetic | compound count updates and prefix output-index capacity test | insns 718/718, structural 0, diffs 46, sha256 d98105bf1b18; first [(6, ('mr', 'r25, r4'), ('mr', 'r24, r4')), (9, ('mr', 'r24, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r24)'), ('stb', 'r0, 0(r25)')), (20, ('clrlwi', 'r0, r25, 0x18'), ('clrlwi', 'r0, r24, 0x18'))]
Zi8GetPyPhonetic | compound count updates and assignment output-index capacity test | insns 718/718, structural 0, diffs 49, sha256 9babe69b45a9; first [(6, ('mr', 'r25, r4'), ('mr', 'r24, r4')), (9, ('mr', 'r24, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r24)'), ('stb', 'r0, 0(r25)')), (20, ('clrlwi', 'r0, r25, 0x18'), ('clrlwi', 'r0, r24, 0x18'))]
Zi8GetPyPhonetic | compound output-count updates in first 1 decoding paths | insns 718/718, structural 0, diffs 105, sha256 39e4178c9a73; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r26, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r29, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r29)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound first 1 count paths with folded output-index capacity | insns 718/718, structural 0, diffs 139, sha256 abbcd32f0ac5; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r27, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r29, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r29)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound output-count updates in first 2 decoding paths | insns 718/718, structural 0, diffs 105, sha256 1e72f6295d42; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r26, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r29, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r29)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound first 2 count paths with folded output-index capacity | insns 718/718, structural 0, diffs 139, sha256 c00d9b7e9f9c; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r27, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r29, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r29)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound output-count updates in first 3 decoding paths | insns 718/718, structural 0, diffs 72, sha256 844f8b2781d5; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r26, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r28, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r28)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound first 3 count paths with folded output-index capacity | insns 718/718, structural 0, diffs 106, sha256 7e49e434ad14; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r27, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r28, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r28)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound output-count updates in first 4 decoding paths | insns 718/718, structural 0, diffs 106, sha256 d4667aa93c9b; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r26, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r27, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r27)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound first 4 count paths with folded output-index capacity | insns 718/718, structural 0, diffs 106, sha256 f4fa3c74b8c5; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r27, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r28, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r28)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound output-count updates in first 5 decoding paths | insns 718/718, structural 0, diffs 106, sha256 dfbe277edf59; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (8, ('mr', 'r27, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r26, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r26)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound first 5 count paths with folded output-index capacity | insns 718/718, structural 0, diffs 47, sha256 c0c41cde67cf; first [(7, ('mr', 'r25, r5'), ('mr', 'r26, r5')), (9, ('mr', 'r26, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r26)'), ('stb', 'r0, 0(r25)')), (111, ('sthx', 'r3, r25, r0'), ('sthx', 'r3, r26, r0'))]
Zi8GetPyPhonetic | compound output-count updates in first 6 decoding paths | insns 718/718, structural 0, diffs 59, sha256 322d2d4d06e8; first [(8, ('mr', 'r27, r6'), ('mr', 'r28, r6')), (102, ('li', 'r28, 0'), ('li', 'r27, 0')), (109, ('clrlwi', 'r0, r28, 0x18'), ('clrlwi', 'r0, r27, 0x18')), (113, ('clrlwi', 'r4, r28, 0x18'), ('clrlwi', 'r4, r27, 0x18'))]
Zi8GetPyPhonetic | compound first 6 count paths with folded output-index capacity | insns 718/718, structural 0, diffs 0, sha256 ebc57bee449e; first []
Candidate exact instructions saved, fresh objdiff and full gate still required.
Zi8GetPyPhonetic | compound output-count updates in first 7 decoding paths | insns 718/718, structural 0, diffs 59, sha256 ced7dc8400e0; first [(8, ('mr', 'r27, r6'), ('mr', 'r28, r6')), (102, ('li', 'r28, 0'), ('li', 'r27, 0')), (109, ('clrlwi', 'r0, r28, 0x18'), ('clrlwi', 'r0, r27, 0x18')), (113, ('clrlwi', 'r4, r28, 0x18'), ('clrlwi', 'r4, r27, 0x18'))]
Zi8GetPyPhonetic | compound first 7 count paths with folded output-index capacity | insns 718/718, structural 0, diffs 0, sha256 9802c238f206; first []
Candidate exact instructions saved, fresh objdiff and full gate still required.
Zi8GetPyPhonetic | compound output-count updates in first 8 decoding paths | insns 718/718, structural 0, diffs 105, sha256 69c52b706a66; first [(6, ('mr', 'r25, r4'), ('mr', 'r24, r4')), (8, ('mr', 'r27, r6'), ('mr', 'r28, r6')), (9, ('mr', 'r24, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r24)'), ('stb', 'r0, 0(r25)'))]
Zi8GetPyPhonetic | compound first 8 count paths with folded output-index capacity | insns 718/718, structural 0, diffs 46, sha256 d5ff9da15031; first [(6, ('mr', 'r25, r4'), ('mr', 'r24, r4')), (9, ('mr', 'r24, r7'), ('mr', 'r25, r7')), (19, ('stb', 'r0, 0(r24)'), ('stb', 'r0, 0(r25)')), (20, ('clrlwi', 'r0, r25, 0x18'), ('clrlwi', 'r0, r24, 0x18'))]

## Exact candidate Zi8GetPyPhonetic
First six actual result-count increments use compound addition; final result-count decrement is compound; outputIndex increment is folded into its capacity test. Source remains ordinary C, no added locals/metadata/assembly. Two variants produced718/718 instructions and diffs0; retain variant14 with fewer changed count paths. Fresh authority checks follow before local commit.

## Coverage and retained-source audit before full gate
Zi8_814834AC: 4 compiled attempts in this run.
Zi8GetKOcandidates: 3 compiled attempts in this run.
Zi8IsDupWChar: 3 compiled attempts in this run.
Zi8GetDataSignature: 3 compiled attempts in this run.
ZiDAWGgetCHARattribute: 3 compiled attempts in this run.
ZiDAWGGetGraphInfo: 6 compiled attempts in this run.
Zi8_8148302C: 3 compiled attempts in this run.
Zi8_81483264: 3 compiled attempts in this run.
Zi8_81483308: 3 compiled attempts in this run.
Zi8_814833F0: 3 compiled attempts in this run.
Zi8GetPyFinal: 5 compiled attempts in this run.
Zi8GetPyPhonetic: 21 compiled attempts in this run.
Zi8MatchOEMdata: 3 compiled attempts in this run.
PyFinal actual record definition and flat byte-table addressing overlap earlier attempts and do not count toward new coverage. Signed component view, paired comma outputs, and returned paired assignments are three new compiled attempts. All other open functions have at least three new logged source variants. No open function left untried.
Fresh objdiff candidate Zi8GetPyPhonetic100.0%, ctxdiff718/718 diffs0, empty pool identical; zi8match8/10->9/10 and code5172->8044bytes, data728unchanged. All original exact sibling functions stay100.0%. Retained diff is eight counter/update edits in zi8match.c. Definitions and shared headers restored byte-for-byte. No configuration, symbol, data object or unrelated source edits retained.
Result-count compound assignments preserve byte wrapping and evaluate the same pointer and count; prefix outputIndex capacity test preserves the increment/comparison order. No assembly, uninitialized value, fake symbol, dummy object or use-site volatile introduced. Full clean gate is running alone in this build tree.

## Final clean non-quick full gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] objdiff: code 332/5200 data 96/180 functions 1/7 fuzzy 98.7462 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] instruction-exact functions: 1/7
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section .data size 40 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section .text size 5200 match 98.746155
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section extab size 56 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   section extabindex size 84 match 97.61904
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_8148302C 99.49152
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_81483264 98.902435
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_81483308 99.13793
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_814833F0 99.04256
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8_814834AC 99.3586
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp]   below 100: Zi8GetKOcandidates 98.146484
[libs/RVLMiddleware/eZiText/src/clib/zkokeyp] baseline: code 332/5200 data 96 functions 1 fuzzy 98.7462
[libs/RVLMiddleware/eZiText/src/clib/zi8match] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8match] objdiff: code 8044/8256 data 728/728 functions 9/10 fuzzy 99.9806 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8match] instruction-exact functions: 9/10
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   section .rodata size 528 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   section .text size 8256 match 99.98062
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   section extab size 80 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   section extabindex size 120 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8match]   below 100: Zi8GetPyFinal 99.245285
[libs/RVLMiddleware/eZiText/src/clib/zi8match] baseline: code 5172/8256 data 728 functions 8 fuzzy 99.5300
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] objdiff: code 6360/6888 data 332/332 functions 15/17 fuzzy 99.9506 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] instruction-exact functions: 15/17
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .data size 80 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .rodata size 16 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .sbss2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .sdata2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section .text size 6888 match 99.95064
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section extab size 88 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   section extabindex size 132 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   below 100: Zi8GetDataSignature 99.347824
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2]   below 100: Zi8IsDupWChar 99.36508
[libs/RVLMiddleware/eZiText/src/clib/zi8getc2] baseline: code 6360/6888 data 332 functions 15 fuzzy 99.9506
[libs/RVLMiddleware/eZiText/src/clib/zidawg1] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zidawg1] objdiff: code 888/1664 data 80/80 functions 4/6 fuzzy 99.7115 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zidawg1] instruction-exact functions: 4/6
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   section .text size 1664 match 99.71154
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   below 100: ZiDAWGgetCHARattribute 99.0
[libs/RVLMiddleware/eZiText/src/clib/zidawg1]   below 100: ZiDAWGGetGraphInfo 99.55224
[libs/RVLMiddleware/eZiText/src/clib/zidawg1] baseline: code 888/1664 data 80 functions 4 fuzzy 99.7115
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] objdiff: code 208/976 data 60/60 functions 2/3 fuzzy 98.9344 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] instruction-exact functions: 2/3
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section .text size 976 match 98.934425
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   below 100: Zi8MatchOEMdata 98.645836
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] baseline: code 208/976 data 60 functions 2 fuzzy 98.9344
regressions vs baseline: 0
global matched_code_percent: 91.66833 -> 91.76422
global fuzzy_match_percent: 99.70642 -> 99.70766
global complete_code_percent: 74.76262 -> 74.76262
global matched_data_percent: 99.77803 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
Fresh post-clean-build ctxdiff for Zi8GetPyPhonetic718/718, diffs0. Final scope exact30/43->31/43; code12960/22984->15832/22984; data1296/1380unchanged. All five pools identical. GatePASS, zero regressions/forbidden/readability, required DOLhash. Remaining12functions are unresolved; this candidate adds one exact function and does not complete any whole unit.

## Remaining functions and uncertainties
zi8getc2 Zi8GetDataSignature: 99.347824% open; saved-register allocation cycle at identical instruction count.
zi8getc2 Zi8IsDupWChar: 99.36508% open; saved-register allocation cycle at identical instruction count.
zi8match Zi8GetPyFinal: 99.245285% open; r6/r7 row stride/base scratch-register allocation; 53/53 instructions, 8 differences.
zidawg1 ZiDAWGgetCHARattribute: 99.0% open; saved-register allocation cycle at identical instruction count.
zidawg1 ZiDAWGGetGraphInfo: 99.55224% open; saved-register allocation cycle at identical instruction count.
zkokeyp Zi8_8148302C: 99.49152% open; saved-register allocation cycle at identical instruction count.
zkokeyp Zi8_81483264: 98.902435% open; saved-register allocation cycle at identical instruction count.
zkokeyp Zi8_81483308: 99.13793% open; saved-register allocation cycle at identical instruction count.
zkokeyp Zi8_814833F0: 99.04256% open; saved-register allocation cycle at identical instruction count.
zkokeyp Zi8_814834AC: 99.3586% open; 344/343 instructions; packed-key initialization narrows an extra byte, operand association and work/candidate register swap.
zkokeyp Zi8GetKOcandidates: 98.146484% open; 671/669 instructions; extra packed-key zero and table pointer copy plus scratch/address operand allocation.
zoemdata Zi8MatchOEMdata: 98.645836% open; saved-register allocation cycle at identical instruction count.
No metadata/data correction justified: Korean switch table/unwind bytes already identical; the84-byte unpaired index gap depends on both nonexact function extents. Saved-register source reference weights are a proven lever for PyPhonetic, but remaining register cycles need different real expression ownership. No speculative trial retained.
