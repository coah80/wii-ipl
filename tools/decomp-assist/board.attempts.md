# Board continuation, 2026-10-01

Entry AOSS_Init_old: {'fuzzy': 92.73864, 'instructions': 1578, 'target': 1584, 'structural': 1480, 'diffs': 1494, 'code': '6436', 'data': '3896'}
Entry AOSS_81400830: {'fuzzy': 97.0405, 'instructions': 321, 'target': 321, 'structural': 2, 'diffs': 125, 'code': '6436', 'data': '3896'}
Entry AOSS_814013AC: {'fuzzy': 98.77193, 'instructions': 114, 'target': 114, 'structural': 0, 'diffs': 22, 'code': '6436', 'data': '3896'}
Entry AOSS_81401778: {'fuzzy': 91.83883, 'instructions': 271, 'target': 273, 'structural': 39, 'diffs': 254, 'code': '6436', 'data': '3896'}
Entry AOSS_81401E80: {'fuzzy': 98.605446, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 36, 'code': '6436', 'data': '3896'}
Entry Zi8ChangeWordCase: {'fuzzy': 99.09091, 'instructions': 44, 'target': 44, 'structural': 0, 'diffs': 8, 'code': '5704', 'data': '72'}
Entry Zi8AlphaGetCandidates: {'fuzzy': 90.60111, 'instructions': 3947, 'target': 3946, 'structural': 1227, 'diffs': 3812, 'code': '5704', 'data': '72'}
- AOSS_Init_old: recover two separately addressed default wait constants; {'fuzzy': 92.73864, 'instructions': 1578, 'target': 1584, 'structural': 1480, 'diffs': 1494, 'code': '6436', 'data': '3896'} -> {'fuzzy': 92.56566, 'instructions': 1577, 'target': 1584, 'structural': 1473, 'diffs': 1443, 'code': '6436', 'data': '3888'}; regressions ['main/src/scene/setting/AOSS matched_data']; reverted.
- AOSS_Init_old: retain loaded input flags across runtime initialization; {'fuzzy': 92.73864, 'instructions': 1578, 'target': 1584, 'structural': 1480, 'diffs': 1494, 'code': '6436', 'data': '3896'} -> {'fuzzy': 92.67298, 'instructions': 1577, 'target': 1584, 'structural': 1473, 'diffs': 1399, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_Init_old: load response wait after the attempt limit check; {'fuzzy': 92.73864, 'instructions': 1578, 'target': 1584, 'structural': 1480, 'diffs': 1494, 'code': '6436', 'data': '3896'} -> {'fuzzy': 92.684975, 'instructions': 1578, 'target': 1584, 'structural': 1479, 'diffs': 1494, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_Init_old: remove repeated pre-sleep minimum and retain target post-call selection; {'fuzzy': 92.73864, 'instructions': 1578, 'target': 1584, 'structural': 1480, 'diffs': 1494, 'code': '6436', 'data': '3896'} -> {'fuzzy': 92.757576, 'instructions': 1576, 'target': 1584, 'structural': 1154, 'diffs': 1485, 'code': '6436', 'data': '3896'}; regressions []; retained.
- AOSS_Init_old: move first response-wait load after exhausted-attempt exit; {'fuzzy': 92.757576, 'instructions': 1576, 'target': 1584, 'structural': 1154, 'diffs': 1485, 'code': '6436', 'data': '3896'} -> {'fuzzy': 92.97854, 'instructions': 1576, 'target': 1584, 'structural': 1151, 'diffs': 1485, 'code': '6436', 'data': '3896'}; regressions []; retained.
- AOSS_Init_old: use target branch sense for elapsed connection attempts; {'fuzzy': 92.97854, 'instructions': 1576, 'target': 1584, 'structural': 1151, 'diffs': 1485, 'code': '6436', 'data': '3896'} -> {'fuzzy': 92.97854, 'instructions': 1576, 'target': 1584, 'structural': 1151, 'diffs': 1485, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_Init_old: normalize remaining waits to halfwords in the initial link loop; {'fuzzy': 92.97854, 'instructions': 1576, 'target': 1584, 'structural': 1151, 'diffs': 1485, 'code': '6436', 'data': '3896'} -> {'fuzzy': 93.14899, 'instructions': 1576, 'target': 1584, 'structural': 1151, 'diffs': 1479, 'code': '6436', 'data': '3896'}; regressions []; retained.
- AOSS_81400830: declsearch, 180 distinct declaration orders; 321/321, 97.0405 -> 97.74143%; strict differences 125 -> 89; retained checksum-first, control-before-length, input-before-output order.
- AOSS_81400830: XOR key-stream byte before consuming encrypted byte; {'fuzzy': 97.74143, 'instructions': 321, 'target': 321, 'structural': 2, 'diffs': 89, 'code': '6436', 'data': '3896'} -> {'fuzzy': 97.74143, 'instructions': 321, 'target': 321, 'structural': 2, 'diffs': 89, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81400830: narrow permutation values to their byte element type; {'fuzzy': 97.74143, 'instructions': 321, 'target': 321, 'structural': 2, 'diffs': 89, 'code': '6436', 'data': '3896'} -> {'fuzzy': 97.74143, 'instructions': 321, 'target': 321, 'structural': 2, 'diffs': 89, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81400830: declare state pointer after permutation indexes in the loop scope; {'fuzzy': 97.74143, 'instructions': 321, 'target': 321, 'structural': 2, 'diffs': 89, 'code': '6436', 'data': '3896'} -> {'fuzzy': 97.47664, 'instructions': 321, 'target': 321, 'structural': 2, 'diffs': 101, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_814013AC: use one response cursor for outer and nested options; {'fuzzy': 98.77193, 'instructions': 114, 'target': 114, 'structural': 0, 'diffs': 22, 'code': '6436', 'data': '3896'} -> {'fuzzy': 96.18421, 'instructions': 114, 'target': 114, 'structural': 2, 'diffs': 38, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_814013AC: defer flags initialization until response length validation; {'fuzzy': 98.77193, 'instructions': 114, 'target': 114, 'structural': 0, 'diffs': 22, 'code': '6436', 'data': '3896'} -> {'fuzzy': 96.97369, 'instructions': 114, 'target': 114, 'structural': 3, 'diffs': 26, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_814013AC: extend formal response length through validation before cursor setup; {'fuzzy': 98.77193, 'instructions': 114, 'target': 114, 'structural': 0, 'diffs': 22, 'code': '6436', 'data': '3896'} -> {'fuzzy': 96.97369, 'instructions': 114, 'target': 114, 'structural': 3, 'diffs': 27, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401778: walk the hello CRC as one eight-byte loop; {'fuzzy': 91.83883, 'instructions': 271, 'target': 273, 'structural': 39, 'diffs': 254, 'code': '6436', 'data': '3896'} -> {'fuzzy': 86.67033, 'instructions': 270, 'target': 273, 'structural': 49, 'diffs': 266, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401778: walk hello CRC with advancing cursor and end pointer; {'fuzzy': 91.83883, 'instructions': 271, 'target': 273, 'structural': 39, 'diffs': 254, 'code': '6436', 'data': '3896'} -> {'fuzzy': 81.490845, 'instructions': 292, 'target': 273, 'structural': 59, 'diffs': 285, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401778: walk hello CRC with postfix do-while indexing; {'fuzzy': 91.83883, 'instructions': 271, 'target': 273, 'structural': 39, 'diffs': 254, 'code': '6436', 'data': '3896'} -> {'fuzzy': 76.567764, 'instructions': 235, 'target': 273, 'structural': 77, 'diffs': 264, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401778: place destination after the identity local in source declaration order; {'fuzzy': 91.83883, 'instructions': 271, 'target': 273, 'structural': 39, 'diffs': 254, 'code': '6436', 'data': '3896'} -> {'fuzzy': 91.831505, 'instructions': 271, 'target': 273, 'structural': 38, 'diffs': 254, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401778: keep hello encryption XOR full-width through its store; {'fuzzy': 91.83883, 'instructions': 271, 'target': 273, 'structural': 39, 'diffs': 254, 'code': '6436', 'data': '3896'} -> {'fuzzy': 91.83883, 'instructions': 271, 'target': 273, 'structural': 39, 'diffs': 254, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401E80: keep packet XOR operand full-width until truncating the store; {'fuzzy': 98.605446, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 36, 'code': '6436', 'data': '3896'} -> {'fuzzy': 98.605446, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 36, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401E80: use signed native integer packet XOR temporary; {'fuzzy': 98.605446, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 36, 'code': '6436', 'data': '3896'} -> {'fuzzy': 98.605446, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 36, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401E80: express in-place packet mixing as compound XOR; {'fuzzy': 98.605446, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 36, 'code': '6436', 'data': '3896'} -> {'fuzzy': 98.23129, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 46, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401E80: load key-mask operand before packet operand and store the mixed result; {'fuzzy': 98.605446, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 36, 'code': '6436', 'data': '3896'} -> {'fuzzy': 98.57143, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 31, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_814013AC: declsearch, 150 declaration-order variants; 114/114, 98.77193%, 22 strict differences unchanged; all orders restored.
- AOSS_81401E80: declsearch, 100 declaration-order variants; 147/147, 98.605446%, 36 strict differences unchanged; all orders restored.
- AOSS_81401E80: load packet and key separately, updating the key-byte accumulator; {'fuzzy': 98.605446, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 36, 'code': '6436', 'data': '3896'} -> {'fuzzy': 98.57143, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 31, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_81401E80: write XOR of two full-width operand locals directly; {'fuzzy': 98.605446, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 36, 'code': '6436', 'data': '3896'} -> {'fuzzy': 98.5034, 'instructions': 147, 'target': 147, 'structural': 2, 'diffs': 39, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- Zi8AlphaGetCandidates: use typed workspace field view in its recovered scalar position; {'fuzzy': 90.60111, 'instructions': 3947, 'target': 3946, 'structural': 1227, 'diffs': 3812, 'code': '5704', 'data': '72'} -> {'fuzzy': 89.900406, 'instructions': 3948, 'target': 3946, 'structural': 1227, 'diffs': 3483, 'code': '5704', 'data': '0'}; regressions ['main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha matched_data']; reverted.
- Zi8AlphaGetCandidates: use one generic dictionary workspace for all helper calls; {'fuzzy': 90.60111, 'instructions': 3947, 'target': 3946, 'structural': 1227, 'diffs': 3812, 'code': '5704', 'data': '72'} -> {'fuzzy': 89.35048, 'instructions': 3959, 'target': 3946, 'structural': 560, 'diffs': 3784, 'code': '5704', 'data': '72'}; regressions []; reverted.
- Zi8AlphaGetCandidates: make engine workspace parameter typed and remove repeated casts; {'fuzzy': 90.60111, 'instructions': 3947, 'target': 3946, 'structural': 1227, 'diffs': 3812, 'code': '5704', 'data': '72'} -> {'fuzzy': 89.94602, 'instructions': 3947, 'target': 3946, 'structural': 1227, 'diffs': 3829, 'code': '5704', 'data': '72'}; regressions []; reverted.
- AOSS_814013AC: reuse the nested-option variable while selecting the outer response; {'fuzzy': 98.77193, 'instructions': 114, 'target': 114, 'structural': 0, 'diffs': 22, 'code': '6436', 'data': '3896'} -> {'fuzzy': 95.833336, 'instructions': 114, 'target': 114, 'structural': 2, 'diffs': 44, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_814013AC: advance the formal response length directly; {'fuzzy': 98.77193, 'instructions': 114, 'target': 114, 'structural': 0, 'diffs': 22, 'code': '6436', 'data': '3896'} -> {'fuzzy': 98.20175, 'instructions': 114, 'target': 114, 'structural': 0, 'diffs': 32, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- AOSS_814013AC: advance the formal response pointer across both record loops; {'fuzzy': 98.77193, 'instructions': 114, 'target': 114, 'structural': 0, 'diffs': 22, 'code': '6436', 'data': '3896'} -> {'fuzzy': 95.08772, 'instructions': 114, 'target': 114, 'structural': 5, 'diffs': 28, 'code': '6436', 'data': '3896'}; regressions []; reverted.
- Zi8ChangeWordCase: use a native integer selector for lower and upper case; {'fuzzy': 99.09091, 'instructions': 44, 'target': 44, 'structural': 0, 'diffs': 8, 'code': '5704', 'data': '72'} -> {'fuzzy': 99.09091, 'instructions': 44, 'target': 44, 'structural': 0, 'diffs': 8, 'code': '5704', 'data': '72'}; regressions []; reverted.
- Zi8ChangeWordCase: advance the word cursor in the loop continuation; {'fuzzy': 99.09091, 'instructions': 44, 'target': 44, 'structural': 0, 'diffs': 8, 'code': '5704', 'data': '72'} -> {'fuzzy': 94.545456, 'instructions': 44, 'target': 44, 'structural': 2, 'diffs': 11, 'code': '5704', 'data': '72'}; regressions []; reverted.
- Zi8ChangeWordCase: make case-conversion workspace formal typed; {'fuzzy': 99.09091, 'instructions': 44, 'target': 44, 'structural': 0, 'diffs': 8, 'code': '5704', 'data': '72'} -> {'fuzzy': 98.52273, 'instructions': 44, 'target': 44, 'structural': 0, 'diffs': 11, 'code': '5704', 'data': '72'}; regressions []; reverted.
- Zi8AlphaGetCandidates: name the context-table return before testing its high flag; {'fuzzy': 90.60111, 'instructions': 3947, 'target': 3946, 'structural': 1227, 'diffs': 3812, 'code': '5704', 'data': '72'} -> {'fuzzy': 88.31399, 'instructions': 3951, 'target': 3946, 'structural': 1242, 'diffs': 3769, 'code': '5704', 'data': '0'}; regressions ['main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha matched_data']; reverted.
- Zi8AlphaGetCandidates: retain native width for the named context table count; {'fuzzy': 90.60111, 'instructions': 3947, 'target': 3946, 'structural': 1227, 'diffs': 3812, 'code': '5704', 'data': '72'} -> {'fuzzy': 88.25798, 'instructions': 3953, 'target': 3946, 'structural': 636, 'diffs': 3872, 'code': '5704', 'data': '0'}; regressions ['main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha matched_data']; reverted.
- Zi8AlphaGetCandidates: use signed table flag temporary and explicit halfword mask; {'fuzzy': 90.60111, 'instructions': 3947, 'target': 3946, 'structural': 1227, 'diffs': 3812, 'code': '5704', 'data': '72'} -> {'fuzzy': 88.37557, 'instructions': 3955, 'target': 3946, 'structural': 620, 'diffs': 3808, 'code': '5704', 'data': '0'}; regressions ['main/libs/RVLMiddleware/eZiText/src/clib/zi8alpha matched_data']; reverted.
- Zi8AlphaGetCandidates: remove duplicate upper-bound test from next-dictionary selection; {'fuzzy': 90.60111, 'instructions': 3947, 'target': 3946, 'structural': 1227, 'diffs': 3812, 'code': '5704', 'data': '72'} -> {'fuzzy': 90.60137, 'instructions': 3945, 'target': 3946, 'structural': 1234, 'diffs': 3809, 'code': '5704', 'data': '72'}; regressions []; retained.
- Zi8AlphaGetCandidates: select punctuation dictionary with explicit dictionary-kind cases; {'fuzzy': 90.60137, 'instructions': 3945, 'target': 3946, 'structural': 1234, 'diffs': 3809, 'code': '5704', 'data': '72'} -> {'fuzzy': 90.565636, 'instructions': 3947, 'target': 3946, 'structural': 1226, 'diffs': 3812, 'code': '5704', 'data': '72'}; regressions []; reverted.
- Zi8AlphaGetCandidates: use target inclusive punctuation character bounds; {'fuzzy': 90.60137, 'instructions': 3945, 'target': 3946, 'structural': 1234, 'diffs': 3809, 'code': '5704', 'data': '72'} -> {'fuzzy': 90.60441, 'instructions': 3945, 'target': 3946, 'structural': 1230, 'diffs': 3809, 'code': '5704', 'data': '72'}; regressions []; retained.
- Zi8AlphaGetCandidates: compare exact word limit with the produced length first; {'fuzzy': 90.60441, 'instructions': 3945, 'target': 3946, 'structural': 1230, 'diffs': 3809, 'code': '5704', 'data': '72'} -> {'fuzzy': 90.605675, 'instructions': 3945, 'target': 3946, 'structural': 1229, 'diffs': 3809, 'code': '5704', 'data': '72'}; regressions []; retained.
- Zi8AlphaGetCandidates: compare produced length against option maximum in target operand order; {'fuzzy': 90.605675, 'instructions': 3945, 'target': 3946, 'structural': 1229, 'diffs': 3809, 'code': '5704', 'data': '72'} -> {'fuzzy': 90.56741, 'instructions': 3945, 'target': 3946, 'structural': 1224, 'diffs': 3810, 'code': '5704', 'data': '72'}; regressions []; reverted.
- Zi8AlphaGetCandidates: use target one-character key-layout cutoff; {'fuzzy': 90.605675, 'instructions': 3945, 'target': 3946, 'structural': 1229, 'diffs': 3809, 'code': '5704', 'data': '72'} -> {'fuzzy': 90.6072, 'instructions': 3945, 'target': 3946, 'structural': 1228, 'diffs': 3809, 'code': '5704', 'data': '72'}; regressions []; retained.

Gate normalization discrepancy: AOSS_81400E0C, objdiff 100%; corrected branch-relative disassembly identical=True.

## Final inventory

AOSS_Init_old: fuzzy 92.73864 -> 93.14899; instruction deficit 8 -> 8; at least 3 distinct measured source trials logged.
AOSS_81400830: fuzzy 97.0405 -> 97.74143; instruction deficit 0 -> 0; at least 3 distinct measured source trials logged.
AOSS_814013AC: fuzzy 98.77193 -> 98.77193; instruction deficit 0 -> 0; at least 3 distinct measured source trials logged.
AOSS_81401778: fuzzy 91.83883 -> 91.83883; instruction deficit 2 -> 2; at least 3 distinct measured source trials logged.
AOSS_81401E80: fuzzy 98.605446 -> 98.605446; instruction deficit 0 -> 0; at least 3 distinct measured source trials logged.
Zi8ChangeWordCase: fuzzy 99.09091 -> 99.09091; instruction deficit 0 -> 0; at least 3 distinct measured source trials logged.
Zi8AlphaGetCandidates: fuzzy 90.60111 -> 90.6072; instruction deficit 1 -> 1; at least 3 distinct measured source trials logged.

No instruction-exact count gain. Both units remain incomplete and NonMatching. Engine workspace snapshot and related scalar stack offsets remain unresolved; no artificial stack local was retained. AOSS default constant binding and hello shared global base remain unresolved.

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3896/3928 functions 16/21 fuzzy 96.5045 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 42.857143
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 96.50445
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 93.14899
[src/scene/setting/AOSS]   below 100: AOSS_81400830 97.74143
[src/scene/setting/AOSS]   below 100: AOSS_814013AC 98.77193
[src/scene/setting/AOSS]   below 100: AOSS_81401778 91.83883
[src/scene/setting/AOSS]   below 100: AOSS_81401E80 98.605446
[src/scene/setting/AOSS] baseline: code 6436/16192 data 3896 functions 16 fuzzy 96.2883
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] objdiff: code 5704/21664 data 72/564 functions 10/12 fuzzy 93.1492 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] instruction-exact functions: 10/12
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section .data size 48 match None
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section .rodata size 336 match 99.0991
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section .text size 21664 match 93.149185
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section extab size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   section extabindex size 108 match 99.07407
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   below 100: Zi8ChangeWordCase 99.09091
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha]   below 100: Zi8AlphaGetCandidates 90.6072
[libs/RVLMiddleware/eZiText/src/clib/zi8alpha] baseline: code 5704/21664 data 72 functions 10 fuzzy 93.1448
regressions vs baseline: 0
global matched_code_percent: 86.68724 -> 86.68724
global fuzzy_match_percent: 99.30689 -> 99.30809
global complete_code_percent: 60.61288 -> 60.61288
global matched_data_percent: 91.11031 -> 91.11031
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
