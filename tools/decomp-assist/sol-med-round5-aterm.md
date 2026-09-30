# ATERM round 5 attempts

Fresh baseline: instruction exact 6/26; objdiff exact 7/26; matched code 4528/19204, data 18448/18864; fuzzy 89.32577. Pools identical.

Each trial below starts from the current best function; only an improved candidate is retained. Failed compilation and unchanged source do not count as attempts.

ATERMi_ApConfigStart initial 99.805824%
- use reciprocal as first unsigned high-product operand: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
- single clock conversion expression after OSGetTime: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
- name the unshifted bus frequency before reciprocal multiplication: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- reciprocal first in unsigned high product: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000
- clock quotient inline in elapsed expression: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000
- name raw clock frequency then scale in reciprocal product: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000
Retained best candidate

ATERMi_ApConfigStart initial 99.805824%
- SDK tick-to-milliseconds macro: 100.0%; src 0x19c base 0x19c insns 103/103; diffs 0: []
Retained exact candidate

ATERM_81402E40 initial 99.791664%
- key view begins after payload header initialization: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- payload header initialized using a named view: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- key availability branch from unencrypted case: 92.239586%; src 0x180 base 0x180 insns 96/96; diffs 15: [9, 10, 20, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 47, 52];      9 M mr r29, r7;        B mr r3, r27
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- SDK tick conversion expresses constant division: 100.0%; src 0x8c base 0x8c insns 35/35; diffs 0: []
Retained exact candidate

ATERM_8140502C initial 99.42029%
- round reversal tests ascending index first: 99.42029%; src 0x228 base 0x228 insns 138/138; diffs 13: [11, 12, 15, 16, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r7, r3, 2;        B slwi r8, r3, 2
- swap indices declared descending first: 99.565216%; src 0x228 base 0x228 insns 138/138; diffs 11: [11, 15, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r6, r3, 2;        B slwi r8, r3, 2
- round reversal uses for index updates: 99.42029%; src 0x228 base 0x228 insns 138/138; diffs 13: [11, 12, 15, 16, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r7, r3, 2;        B slwi r8, r3, 2
Retained best candidate

ATERM_8140502C initial 99.565216%
- single round-word temporary declared before reversal indices: 98.62319%; src 0x228 base 0x228 insns 138/138; diffs 25: [10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30];     10 M mr r5, r31;        B mr r4, r31
- shared swap word then ascending and descending indices: 98.91304%; src 0x228 base 0x228 insns 138/138; diffs 20: [10, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34];     10 M mr r5, r31;        B mr r4, r31
- reversal counters initialized after expanded key pointers: 98.62319%; src 0x228 base 0x228 insns 138/138; diffs 25: [10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30];     10 M mr r5, r31;        B mr r4, r31
Retained best candidate

ATERMi_ApConfigEnd initial 99.4186%
- SDK alarm delay and progress clock macros: 100.0%; src 0x204 base 0x204 insns 129/129; diffs 0: []
- alarm delays alone use SDK millisecond macro: 99.84496%; src 0x204 base 0x204 insns 129/129; diffs 4: [102, 103, 104, 105];    102 M lis r5, -0x8000;        B lis r6, -0x8000
- progress conversion alone uses SDK millisecond macro: 99.57365%; src 0x204 base 0x204 insns 129/129; diffs 7: [54, 55, 56, 57, 58, 59, 61];     54 M lis r3, -0x8000;        B lis r4, -0x8000
Retained exact candidate

Clock checkpoint full gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 5596/19204 data 18448/18864 functions 10/26 fuzzy 89.3539 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 9/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match None
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 38.88889
[src/scene/setting/ATERM]   section .sdata size 56 match None
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 89.35388
[src/scene/setting/ATERM]   below 100: ATERM_814021BC 96.61688
[src/scene/setting/ATERM]   below 100: ATERM_8140276C 98.965515
[src/scene/setting/ATERM]   below 100: ATERM_81402A24 81.04943
[src/scene/setting/ATERM]   below 100: ATERM_81402E40 99.791664
[src/scene/setting/ATERM]   below 100: ATERM_814031DC 90.766914
[src/scene/setting/ATERM]   below 100: ATERM_814033F0 98.649635
[src/scene/setting/ATERM]   below 100: ATERM_814036D8 99.08064
[src/scene/setting/ATERM]   below 100: ATERM_814038C8 83.25657
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERM_81404844 95.1453
[src/scene/setting/ATERM]   below 100: ATERM_81404A18 99.09091
[src/scene/setting/ATERM]   below 100: ATERM_81404BFC 98.75746
[src/scene/setting/ATERM]   below 100: ATERM_8140502C 99.565216
[src/scene/setting/ATERM]   below 100: ATERM_81405254 54.959408
[src/scene/setting/ATERM]   below 100: ATERM_81405690 52.671585
[src/scene/setting/ATERM]   below 100: ATERM_81405ACC 88.583336
[src/scene/setting/ATERM] baseline: code 4528/19204 data 18448 functions 7 fuzzy 89.3258
regressions vs baseline: 0
global matched_code_percent: 82.75705 -> 82.79270
global fuzzy_match_percent: 95.36525 -> 95.36544
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.46682 -> 89.46682
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

ATERM_81404A18 initial 99.09091%
- unwrap output block and descending index have function scope: 100.0%; src 0x1e4 base 0x1e4 insns 121/121; diffs 0: []
- unwrap result and pass declared before block count and rounds: 99.09091%; src 0x1e4 base 0x1e4 insns 121/121; diffs 20: [12, 29, 38, 40, 41, 42, 43, 46, 49, 50, 51, 56, 67, 94, 98, 102, 103, 105, 113, 114];     12 M li r29, 1;        B li r24, 1
- descending pass loop keeps block index at function scope: 98.80165%; src 0x1e4 base 0x1e4 insns 121/121; diffs 24: [12, 20, 21, 29, 38, 39, 40, 41, 42, 43, 44, 46, 49, 50, 51, 56, 67, 94, 98, 102];     12 M li r25, 1;        B li r24, 1
Retained exact candidate

ATERM_814036D8 initial 99.08064%
- declare source/output/text views before traversal index: 99.645164%; src 0x1f0 base 0x1f0 insns 124/124; diffs 4: [35, 36, 95, 97];     35 M addi r23, r25, 0x28;        B addi r22, r1, 8
- text view initialized before output and key index: 99.33871%; src 0x1f0 base 0x1f0 insns 124/124; diffs 3: [48, 95, 97];     48 M mr r3, r22;        B addi r3, r1, 8
- key cursor advancements follow output then source in separate for update: 99.33871%; src 0x1f0 base 0x1f0 insns 124/124; diffs 3: [48, 95, 97];     48 M mr r3, r22;        B addi r3, r1, 8
Retained best candidate

ATERM_814036D8 initial 99.645164%
- match source/text/output view initialization order with corrected declarations: 99.33871%; src 0x1f0 base 0x1f0 insns 124/124; diffs 3: [48, 95, 97];     48 M mr r3, r22;        B addi r3, r1, 8
- source and output advance in independent reversed statement order: 99.51613%; src 0x1f0 base 0x1f0 insns 124/124; diffs 1: [48];     48 M mr r3, r22;        B addi r3, r1, 8
- text view initialized at declaration following text buffer: 96.53226%; src 0x1f0 base 0x1f0 insns 124/124; diffs 37: [8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28];      8 M addi r21, r1, 8;        B li r31, 1
Retained best candidate

ATERM_814036D8 initial 99.645164%
- key copy length reads local text array with views initialized once: 100.0%; src 0x1f0 base 0x1f0 insns 124/124; diffs 0: []
- key copy views are reused while strlen reads local array: 99.82258%; src 0x1f0 base 0x1f0 insns 124/124; diffs 2: [35, 36];     35 M addi r23, r25, 0x28;        B addi r22, r1, 8
- source/text/output setup with direct text strlen and keyIndex update first: 100.0%; src 0x1f0 base 0x1f0 insns 124/124; diffs 0: []
Retained exact candidate

ATERM_8140502C initial 99.565216%
- single swap word before key-mixing traversal count: 98.62319%; src 0x228 base 0x228 insns 138/138; diffs 25: [10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30];     10 M mr r5, r31;        B mr r4, r31
- single swap word after reversal round pointer views: 98.62319%; src 0x228 base 0x228 insns 138/138; diffs 25: [10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30];     10 M mr r5, r31;        B mr r4, r31
- swaps share temporary declared after ascending index: 98.62319%; src 0x228 base 0x228 insns 138/138; diffs 25: [10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30];     10 M mr r5, r31;        B mr r4, r31
Retained best candidate

ATERM_8140276C initial 98.965515%
- previous traversal index declared after shared comparison scalars: 98.965515%; src 0x2b8 base 0x2b8 insns 174/174; diffs 34: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 66, 69, 70, 72, 74, 80, 82, 84, 87];      8 M addi r20, r3, 4;        B addi r31, r3, 4
- found status declared before final result and fallback indices: 99.166664%; src 0x2b8 base 0x2b8 insns 174/174; diffs 27: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 69, 70, 74, 82, 84, 87, 88, 89, 90];      8 M addi r20, r3, 4;        B addi r31, r3, 4
- fallback presence flags declared before fallback buffer: 98.965515%; src 0x2b8 base 0x2b8 insns 174/174; diffs 34: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 66, 69, 70, 72, 74, 80, 82, 84, 87];      8 M addi r20, r3, 4;        B addi r31, r3, 4
Retained best candidate

ATERM_814033F0 initial 98.649635%
- option value view precedes end/type/length with shared key cursor: 99.56204%; src 0x224 base 0x224 insns 137/137; diffs 11: [11, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];     11 M li r23, 0;        B li r22, 0
- option view declaration order without key cursor scope change: 99.56204%; src 0x224 base 0x224 insns 137/137; diffs 11: [11, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];     11 M li r23, 0;        B li r22, 0
- key output cursor has function scope before parser result: 98.649635%; src 0x224 base 0x224 insns 137/137; diffs 35: [11, 13, 16, 28, 29, 34, 39, 47, 55, 60, 65, 66, 71, 72, 74, 75, 81, 82, 85, 86];     11 M li r23, 0;        B li r22, 0
Retained best candidate

ATERM_81404BFC initial 98.75746%
- initial words use ordinary big-endian read macro: 98.75746%; src 0x430 base 0x430 insns 268/268; diffs 53: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 40, 41, 43];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
- initial key words declare last word before first: 98.94403%; src 0x430 base 0x430 insns 268/268; diffs 49: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 45, 48, 49];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
- initial balanced byte pairs use shifted low-pair byte first: 95.61194%; src 0x430 base 0x430 insns 268/268; diffs 76: [5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25];      5 M lbz r7, 4(r4);        B lbz r7, 2(r4)
Retained best candidate

ATERM_814033F0 initial 99.56204%
- parser result precedes output cursor declaration: 99.56204%; src 0x224 base 0x224 insns 137/137; diffs 11: [11, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];     11 M li r23, 0;        B li r22, 0
- parser result begins before option cursor declaration: 98.24818%; src 0x224 base 0x224 insns 137/137; diffs 42: [5, 7, 11, 13, 16, 28, 29, 32, 34, 39, 47, 55, 60, 65, 66, 71, 72, 74, 75, 81];      5 M addi r28, r3, 8;        B addi r29, r3, 8
- parser result initialized after payload end conversion: 97.66423%; src 0x224 base 0x224 insns 137/137; diffs 18: [7, 8, 9, 10, 11, 12, 13, 14, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];      7 M bl 0;        B li r24, 0
Retained best candidate

ATERM_8140276C initial 99.166664%
- current-record view follows found/result and traversal temporaries: 98.93678%; src 0x2b8 base 0x2b8 insns 174/174; diffs 33: [8, 9, 11, 12, 13, 18, 29, 30, 34, 41, 50, 54, 55, 60, 61, 68, 69, 70, 74, 75];      8 M addi r20, r4, 4;        B addi r31, r3, 4
- previous-index variable starts before first record view: 99.08046%; src 0x2b8 base 0x2b8 insns 174/174; diffs 30: [8, 9, 11, 12, 13, 18, 29, 34, 41, 50, 54, 55, 60, 61, 68, 74, 75, 82, 84, 87];      8 M addi r27, r3, 4;        B addi r31, r3, 4
- found and result initialized before current traversal index: 98.56322%; src 0x2b8 base 0x2b8 insns 174/174; diffs 45: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 66, 69, 70, 72, 74, 76, 78, 80, 82];      8 M addi r20, r3, 4;        B addi r31, r3, 4
Retained best candidate

Small-data layout trials: target selected BSSID and interface address are only copied as six bytes. Eight-byte source arrays impose stronger alignment than original selected BSSID at small-BSS offset 0x44. Try natural hardware-address array lengths; no padding.
- six-byte selected BSSID: {'fuzzy_match_percent': 89.44428, 'total_code': '19204', 'matched_code': '6576', 'matched_code_percent': 34.242867, 'total_data': '18864', 'matched_data': '18448', 'matched_data_percent': 97.79474, 'total_functions': 26, 'matched_functions': 12, 'matched_functions_percent': 46.153847, 'total_units': 1}; sections [('.bss', 100.0), ('.data', None), ('.rodata', 100.0), ('.sbss', 38.88889), ('.sdata', None), ('.sdata2', 100.0), ('.text', 89.44428)]; exact regressions []
- six-byte selected and interface hardware addresses: {'fuzzy_match_percent': 89.44428, 'total_code': '19204', 'matched_code': '6576', 'matched_code_percent': 34.242867, 'total_data': '18864', 'matched_data': '18448', 'matched_data_percent': 97.79474, 'total_functions': 26, 'matched_functions': 12, 'matched_functions_percent': 46.153847, 'total_units': 1}; sections [('.bss', 100.0), ('.data', None), ('.rodata', 100.0), ('.sbss', 38.88889), ('.sdata', None), ('.sdata2', 100.0), ('.text', 89.44428)]; exact regressions []
Retained baseline declarations
Retained six-byte selected BSSID because every use copies exactly six bytes and it fixes small-BSS selected-address alignment 0x48 -> 0x44 and cancellation flag 0x50 -> 0x4c. Data score unchanged because extracted symbol spans include alignment tails. Unit fuzzy 89.42241 -> 89.44428 without exact regressions. Interface address declaration left unchanged.

ATERM_81404844 initial 95.1453%
- wrap block index and pass precede count/rounds at function scope: 95.1453%; src 0x1d0 base 0x1d4 insns 116/117; --- replace mine 8:9 base 8:9;   M    8 mr r24, r3;   B    8 mr r25, r3
- wrap block index remains shared with pass and count before rounds: 95.1453%; src 0x1d0 base 0x1d4 insns 116/117; --- replace mine 8:9 base 8:9;   M    8 mr r24, r3;   B    8 mr r25, r3
- wrap pass uses explicit terminal count in while loop: 95.1453%; src 0x1d0 base 0x1d4 insns 116/117; --- replace mine 8:9 base 8:9;   M    8 mr r24, r3;   B    8 mr r25, r3
Retained best candidate

ATERM_814021BC initial 96.61688%
- network settings aggregate view preserves common base across members: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- network alarm delays use SDK tick conversion: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- settings base view and standard alarm delay expression: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
Retained best candidate

ATERMi_AutoConfigThread initial 94.75%
- final completion mask assigned to consumed result before state shift: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- completion mask uses separate less-than and greater-than distances: 89.375%; src 0xa0 base 0xa0 insns 40/40; diffs 5: [18, 19, 20, 22, 23];     18 M subfic r3, r31, 1;        B addi r3, r31, -1
- deadline invalidation after completion state calculation: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
Retained best candidate

ATERM_81404844 initial 95.1453%
- wrap traversal tracks byte offset and shared output block separately: 98.97436%; src 0x1d4 base 0x1d4 insns 117/117; diffs 20: [8, 27, 30, 36, 38, 39, 40, 41, 42, 45, 48, 54, 58, 60, 99, 100, 101, 103, 104, 106];      8 M mr r24, r3;        B mr r25, r3
- byte-offset wrap declares rounds after block count: 98.67522%; src 0x1d4 base 0x1d4 insns 117/117; diffs 24: [8, 18, 19, 27, 30, 36, 37, 38, 39, 40, 41, 42, 43, 45, 48, 54, 58, 60, 99, 100];      8 M mr r24, r3;        B mr r25, r3
- wrap byte offset has inner-loop scope: 98.67522%; src 0x1d4 base 0x1d4 insns 117/117; diffs 24: [8, 18, 19, 27, 30, 36, 37, 38, 39, 40, 41, 42, 43, 45, 48, 54, 58, 60, 99, 100];      8 M mr r24, r3;        B mr r25, r3
Retained best candidate

ATERM_814031DC initial 90.766914%
- MAC traversal terminates at end of six-byte address view: 89.99248%; src 0x22c base 0x214 insns 139/133; --- replace mine 47:51 base 47:50;   M   47 beq 344;   M   48 addi r6, r1, 8
- MAC traversal index uses natural small unsigned counter: 88.73684%; src 0x20c base 0x214 insns 131/133; --- replace mine 47:49 base 47:50;   M   47 beq 312;   M   48 addi r6, r1, 8
- hex digit selection uses conditional expressions: 73.849625%; src 0x1cc base 0x214 insns 115/133; --- replace mine 47:48 base 47:49;   M   47 beq 248;   B   47 beq 320
Retained best candidate

ATERM_81402A24 initial 81.04943%
- scan time conversions use SDK milliseconds macro: 81.06844%; src 0x488 base 0x41c insns 290/263; --- replace mine 6:7 base 6:7;   M    6 li r24, 0;   B    6 li r4, 0
- selected scan MAC formatting stops before terminal separator: 90.330795%; src 0x40c base 0x41c insns 259/263; --- replace mine 6:7 base 6:7;   M    6 li r24, 0;   B    6 li r4, 0
- scan uses SDK timers and terminal MAC loop: 90.34981%; src 0x40c base 0x41c insns 259/263; --- replace mine 6:7 base 6:7;   M    6 li r24, 0;   B    6 li r4, 0
Retained best candidate

ATERM_81405254 initial 54.959408%
- final round uses XOR of disjoint substituted bytes: 61.94834%; src 0x43c base 0x43c insns 271/271; diffs 196: [10, 16, 24, 26, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45];     10 M slwi r24, r12, 8;        B slwi r23, r12, 8
- final round XOR groups low and high byte pairs as target: 61.94834%; src 0x43c base 0x43c insns 271/271; diffs 196: [10, 16, 24, 26, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45];     10 M slwi r24, r12, 8;        B slwi r23, r12, 8
- balanced final round places round key first in XOR: 61.94834%; src 0x43c base 0x43c insns 271/271; diffs 196: [10, 16, 24, 26, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45];     10 M slwi r24, r12, 8;        B slwi r23, r12, 8
Retained best candidate

ATERM_81405690 initial 52.671585%
- final round uses XOR of disjoint substituted bytes: 59.273064%; src 0x43c base 0x43c insns 271/271; diffs 204: [10, 16, 24, 26, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45];     10 M slwi r24, r12, 8;        B slwi r23, r12, 8
- final round XOR groups low and high byte pairs as target: 59.273064%; src 0x43c base 0x43c insns 271/271; diffs 204: [10, 16, 24, 26, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45];     10 M slwi r24, r12, 8;        B slwi r23, r12, 8
- balanced final round places round key first in XOR: 59.273064%; src 0x43c base 0x43c insns 271/271; diffs 204: [10, 16, 24, 26, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45];     10 M slwi r24, r12, 8;        B slwi r23, r12, 8
Retained best candidate

ATERM_81405ACC initial 88.583336%
- partial input copy terminates at exact fill length: 80.1875%; src 0x204 base 0x240 insns 129/144; --- replace mine 15:16 base 15:16;   M   15 rlwinm r7, r6, 0x1d, 0x1a, 0x1f;   B   15 rlwinm r0, r6, 0x1d, 0x1a, 0x1f
- both input copy loops use exact lengths: 69.486115%; src 0x1d4 base 0x240 insns 117/144; --- delete mine 5:6 base 5:5;   M    5 mr r31, r5; --- replace mine 7:8 base 6:7
- buffer index calculated after count publication from captured old count: 86.951385%; src 0x22c base 0x240 insns 139/144; --- replace mine 2:3 base 2:3;   M    2 slwi r6, r5, 3;   B    2 slwi r7, r5, 3
Retained best candidate

ATERM_814038C8 initial 83.25657%
- protocol progress and deadlines use SDK tick macro: 83.25657%; src 0xf28 base 0xedc insns 970/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- protocol wait delay uses SDK milliseconds macro: 83.25657%; src 0xf28 base 0xedc insns 970/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- protocol timing expressions use SDK conversions: compile failed
Retained best candidate

ATERM_81402FC0 initial 100.0%
- packet checksum cursor initialization in for clause: 99.666664%; src 0x21c base 0x21c insns 135/135; diffs 9: [18, 23, 76, 77, 99, 103, 106, 109, 112];     18 M bge -3631;        B bge -3647
- packet setup type output assigned through local selected mode value: no source change; skipped
- option parser cursor advances using explicit aligned span: no source change; skipped
Retained exact candidate

ATERM_814038C8 initial 83.25657%
- all protocol timing expressions use SDK macros including multiline clock: 83.25657%; src 0xf28 base 0xedc insns 970/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
Retained best candidate

ATERM_81402FC0 initial 100.0%
- packet aligned option advance places cursor before span: 99.92593%; src 0x21c base 0x21c insns 135/135; diffs 3: [18, 23, 112];     18 M bge -3631;        B bge -3647
- selected mode publishes normalized boolean directly: 96.39259%; src 0x218 base 0x21c insns 134/135; --- replace mine 18:19 base 18:19;   M   18 bge -3631;   B   18 bge -3647
- selected mode tests empty selection before enabled selection: 99.94815%; src 0x21c base 0x21c insns 135/135; diffs 5: [18, 23, 122, 123, 126];     18 M bge -3631;        B bge -3647
Retained exact candidate

Validation checkpoint: native AES-128/192/256 encryption and decryption, MD5 lengths 0/1/3/55/56/64/130, fallback scan comparison and MAC association formatting all pass. Final-round AES differences were eight optimized bit-field insertions caused by OR, not stack spills; XOR restores the target instruction counts. No data tables were added or reordered.

Full checkpoint gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 6576/19204 data 18448/18864 functions 12/26 fuzzy 90.8142 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 11/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match None
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 38.88889
[src/scene/setting/ATERM]   section .sdata size 56 match None
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 90.81421
[src/scene/setting/ATERM]   below 100: ATERM_814021BC 96.61688
[src/scene/setting/ATERM]   below 100: ATERM_8140276C 99.166664
[src/scene/setting/ATERM]   below 100: ATERM_81402A24 90.34981
[src/scene/setting/ATERM]   below 100: ATERM_81402E40 99.791664
[src/scene/setting/ATERM]   below 100: ATERM_814031DC 90.766914
[src/scene/setting/ATERM]   below 100: ATERM_814033F0 99.56204
[src/scene/setting/ATERM]   below 100: ATERM_814038C8 83.25657
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERM_81404844 98.97436
[src/scene/setting/ATERM]   below 100: ATERM_81404BFC 98.94403
[src/scene/setting/ATERM]   below 100: ATERM_8140502C 99.565216
[src/scene/setting/ATERM]   below 100: ATERM_81405254 61.94834
[src/scene/setting/ATERM]   below 100: ATERM_81405690 59.273064
[src/scene/setting/ATERM]   below 100: ATERM_81405ACC 88.583336
[src/scene/setting/ATERM] baseline: code 4528/19204 data 18448 functions 7 fuzzy 89.3258
regressions vs baseline: 0
global matched_code_percent: 82.75705 -> 82.82543
global fuzzy_match_percent: 95.36525 -> 95.37480
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.46682 -> 89.46682
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Attempt coverage

Every baseline instruction residual has at least three distinct successful source trials; failed/unchanged trials are excluded. Trials that reached exact continue to be counted.

- ATERMi_ApConfigStart: 4 compiling trials.
- ATERMi_ApConfigGetState: 4 compiling trials.
- ATERM_81402E40: 3 compiling trials.
- ATERM_8140502C: 9 compiling trials.
- ATERMi_ApConfigEnd: 3 compiling trials.
- ATERM_81404A18: 3 compiling trials.
- ATERM_814036D8: 9 compiling trials.
- ATERM_8140276C: 6 compiling trials.
- ATERM_814033F0: 6 compiling trials.
- ATERM_81404BFC: 3 compiling trials.
- ATERM_81404844: 6 compiling trials.
- ATERM_814021BC: 3 compiling trials.
- ATERMi_AutoConfigThread: 3 compiling trials.
- ATERM_814031DC: 3 compiling trials.
- ATERM_81402A24: 3 compiling trials.
- ATERM_81405254: 3 compiling trials.
- ATERM_81405690: 3 compiling trials.
- ATERM_81405ACC: 3 compiling trials.
- ATERM_814038C8: 3 compiling trials.
- ATERM_81402FC0: 4 compiling trials.

## Remaining instruction residuals

| Function | objdiff % | Instructions (mine/original) | Evidence / remaining reason |
|---|---:|---|---|
| ATERM_814021BC | 96.61688 | 154/154 | settings aggregate base-address scheduling and temporary register allocation |
| ATERM_8140276C | 99.166664 | 174/174 | current/previous record and fallback flag register cycles |
| ATERM_81402A24 | 90.34981 | 259/263 | scan descriptor-view scheduling, alignment expression and MAC-loop guard; four instructions short |
| ATERM_81402E40 | 99.791664 | 96/96 | two argument-move ordering differences plus two cr1 normalization differences |
| ATERM_81402FC0 | 100.0 | 135/135 | objdiff 100; gate/ctxdiff has two cr1 address-normalization differences; raw bytes identical |
| ATERM_814031DC | 90.766914 | 129/133 | explicit terminal MAC break versus original CTR loop; four instructions short |
| ATERM_814033F0 | 99.56204 | 137/137 | result/key pointer register cycle |
| ATERM_814038C8 | 83.25657 | 970/951 | protocol frame and option/authentication loop scheduling; 19 extra instructions |
| ATERMi_AutoConfigThread | 94.75 | 40/40 | NOR mask temporary and result-load scheduling |
| ATERM_81404844 | 98.97436 | 117/117 | wrap pass/block/output/byte-offset register allocation |
| ATERM_81404BFC | 98.94403 | 268/268 | initial key byte-load order and AES-128 substitution view allocation |
| ATERM_8140502C | 99.565216 | 138/138 | round-reversal index/swap register allocation |
| ATERM_81405254 | 61.94834 | 271/271 | AES input, round and final XOR scheduling/register allocation; instruction count now identical |
| ATERM_81405690 | 59.273064 | 271/271 | inverse AES input, round and final XOR scheduling/register allocation; instruction count now identical |
| ATERM_81405ACC | 88.583336 | 139/144 | MD5 input-copy guards and state/index scheduling; five instructions short |

## Data audit

No artificial data objects or symbol names added. String pools are identical. These C units contain no vtables.

- .bss: mine 8144, original 8160 bytes; prefix mismatches 0/8144; extra alignment tail bytes 16, all zero True.
- .rodata: mine 10280, original 10280 bytes; prefix mismatches 0/10280; extra alignment tail bytes 0, all zero True.
- .data: mine 280, original 280 bytes; prefix mismatches 0/280; extra alignment tail bytes 0, all zero True.
- .sdata2: mine 7, original 8 bytes; prefix mismatches 0/7; extra alignment tail bytes 1, all zero True.
- .sdata: mine 53, original 56 bytes; prefix mismatches 0/53; extra alignment tail bytes 3, all zero True.
- .sbss: mine 80, original 80 bytes; prefix mismatches 0/80; extra alignment tail bytes 0, all zero True.

ATERM_81402FC0 raw .text bytes identical: True. SHA-256 mine 91a60a7585553b8702d6f6ff83d5a91eedfd3cbaf3a04fb25501c637a6f84acd, original 91a60a7585553b8702d6f6ff83d5a91eedfd3cbaf3a04fb25501c637a6f84acd. Raw bytes do not assert relocation identity. The gate instruction count remains authoritative.

Relocations at corresponding instruction offsets in objdiff-exact functions (observed mappings only, no object/config override):

- (('.sbss', 'gAtermAllocate', 12, 4, 0), ('.sbss', 'lbl_81698C9C', 12, 4, 0))
- (('.sbss', 'gAtermAllocation', 20, 4, 0), ('.sbss', 'lbl_81698CA4', 20, 4, 0))
- (('.sbss', 'gAtermCancelRequested', 76, 4, 0), ('.sbss', 'lbl_81698CDC', 76, 4, 0))
- (('.sbss', 'gAtermProgressCallback', 8, 4, 0), ('.sbss', 'lbl_81698C98', 8, 4, 0))
- (('.sbss', 'gAtermRelease', 16, 4, 0), ('.sbss', 'lbl_81698CA0', 16, 4, 0))
- (('.sbss', 'gAtermResult', 4, 4, 0), ('.sbss', 'lbl_81698C94', 4, 4, 0))
- (('.sbss', 'gAtermState', 0, 4, 0), ('.sbss', 'lbl_81698C90', 0, 4, 0))
- (('.sbss', 'gAtermThreadStarted', 24, 4, 0), ('.sbss', 'lbl_81698CA8', 24, 4, 0))
- (('.sdata', 'gAtermDeadline', 0, 4, 0), ('.sdata', 'lbl_81697218', 0, 4, 0))
- (('.sdata', 'gAtermScanBufferSize', 8, 4, 0), ('.sdata', 'lbl_81697220', 8, 4, 0))
- (('.sdata', 'gAtermScanLimit', 4, 4, 0), ('.sdata', 'lbl_8169721C', 4, 4, 0))

Data is not claimed 100%: ATERM switch-table/initialized-small-data symbol correspondence and anonymous small-BSS mappings remain incomplete. Original extracted alignment tails are not synthesized.

Supplemental native verification PASS: AES-128/192/256 encrypt/decrypt, MD5 lengths 0/1/3/55/56/64/130, scan-list fallback/reset transitions, normalized BSSID and six-byte MAC formatting. Native verification checks behavior; the MWCC/object gate checks matching.

## Final full ATERM gate

Command: `python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/setting/ATERM`

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 6576/19204 data 18448/18864 functions 12/26 fuzzy 90.8142 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 11/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match None
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 38.88889
[src/scene/setting/ATERM]   section .sdata size 56 match None
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 90.81421
[src/scene/setting/ATERM]   below 100: ATERM_814021BC 96.61688
[src/scene/setting/ATERM]   below 100: ATERM_8140276C 99.166664
[src/scene/setting/ATERM]   below 100: ATERM_81402A24 90.34981
[src/scene/setting/ATERM]   below 100: ATERM_81402E40 99.791664
[src/scene/setting/ATERM]   below 100: ATERM_814031DC 90.766914
[src/scene/setting/ATERM]   below 100: ATERM_814033F0 99.56204
[src/scene/setting/ATERM]   below 100: ATERM_814038C8 83.25657
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERM_81404844 98.97436
[src/scene/setting/ATERM]   below 100: ATERM_81404BFC 98.94403
[src/scene/setting/ATERM]   below 100: ATERM_8140502C 99.565216
[src/scene/setting/ATERM]   below 100: ATERM_81405254 61.94834
[src/scene/setting/ATERM]   below 100: ATERM_81405690 59.273064
[src/scene/setting/ATERM]   below 100: ATERM_81405ACC 88.583336
[src/scene/setting/ATERM] baseline: code 4528/19204 data 18448 functions 7 fuzzy 89.3258
regressions vs baseline: 0
global matched_code_percent: 82.75705 -> 82.87778
global fuzzy_match_percent: 95.36525 -> 95.37944
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.46682 -> 89.46682
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
