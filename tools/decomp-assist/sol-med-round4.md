# ATERM and AOSS fourth matching pass

Pool-first checks and live baseline recorded in final gate below. Iteration changes one function at a time, descending by baseline objdiff score.

ATERMi_ApConfigStart initial 99.805824%
- first tick conversion multiplies reciprocal before clock: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
- clock sample follows reciprocal declaration in first scope: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
- first divisor uses a signed widened high-word product: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
Retained best candidate

ATERM_81402E40 initial 99.791664%
- payload header lifetime starts at clear: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- immutable encryption key local retained across clear: compile failed
- byte clear view reused for first converted header word: 99.583336%; src 0x180 base 0x180 insns 96/96; diffs 6: [6, 7, 9, 10, 47, 52];      6 M mr r26, r4;        B mr r30, r3
Retained best candidate

ATERMi_ApConfigStart initial 99.805824%
- ordinary unsigned high-word clock product: 86.660194%; src 0x1a4 base 0x19c insns 105/103; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x30(r1);   B    0 stwu r1, -0x20(r1)
- both timer products expressed as unsigned high words: 82.58253%; src 0x1ac base 0x19c insns 107/103; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x30(r1);   B    0 stwu r1, -0x20(r1)
- first clock divisor and quotient reuse their original source values: 99.805824%; src 0x19c base 0x19c insns 103/103; diffs 3: [48, 49, 51];     48 M lwz r6, 0xf8(r30);        B lwz r0, 0xf8(r30)
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- clock multiplier expanded as ordinary unsigned high word: 90.42857%; src 0x98 base 0x8c insns 38/35; --- replace mine 13:14 base 13:14;   M   13 b 68;   B   13 b 56
- clock address and sampled shifted value have named lifetimes: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
- elapsed quotient reuses current time local: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
Retained best candidate

ATERM_8140502C initial 99.42029%
- reverse indices declared before key expansion lifetime: 98.62319%; src 0x228 base 0x228 insns 138/138; diffs 25: [10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30];     10 M mr r6, r31;        B mr r4, r31
- each round word has a separately named swap temporary: 99.42029%; src 0x228 base 0x228 insns 138/138; diffs 13: [11, 12, 15, 16, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r7, r3, 2;        B slwi r8, r3, 2
- round reversal counters updated by counted for loop: 99.42029%; src 0x228 base 0x228 insns 138/138; diffs 14: [11, 12, 15, 16, 18, 20, 21, 24, 25, 28, 29, 33, 35, 36];     11 M slwi r7, r3, 2;        B slwi r8, r3, 2
Retained best candidate

ATERM_814036D8 initial 99.08064%
- source, text and output views established in target preheader order: 98.69355%; src 0x1f0 base 0x1f0 insns 124/124; diffs 22: [33, 35, 36, 37, 43, 48, 58, 59, 64, 65, 70, 71, 76, 77, 82, 83, 88, 89, 94, 95];     33 M addi r23, r26, 0x164;        B addi r24, r26, 0x164
- key loop index advances before both independent streams: 98.69355%; src 0x1f0 base 0x1f0 insns 124/124; diffs 22: [33, 35, 36, 37, 43, 48, 58, 59, 64, 65, 70, 71, 76, 77, 82, 83, 88, 89, 94, 95];     33 M addi r23, r26, 0x164;        B addi r24, r26, 0x164
- WEP keys traversed using counted four-entry loop: 98.69355%; src 0x1f0 base 0x1f0 insns 124/124; diffs 22: [33, 35, 36, 37, 43, 48, 58, 59, 64, 65, 70, 71, 76, 77, 82, 83, 88, 89, 94, 95];     33 M addi r23, r26, 0x164;        B addi r24, r26, 0x164
Retained best candidate

ATERM_81404A18 initial 99.09091%
- unwrap result assigned before IV initialization: 99.09091%; src 0x1e4 base 0x1e4 insns 121/121; diffs 20: [12, 20, 21, 29, 39, 40, 42, 44, 46, 49, 50, 51, 56, 67, 94, 98, 102, 103, 113, 114];     12 M li r26, 1;        B li r24, 1
- destination stream view established on entry: 98.67769%; src 0x1e4 base 0x1e4 insns 121/121; diffs 26: [8, 12, 20, 21, 29, 34, 38, 39, 40, 41, 42, 43, 44, 46, 49, 50, 51, 56, 67, 94];      8 M mr r29, r3;        B mr r23, r3
- descending block index declared with pass counter: 99.09091%; src 0x1e4 base 0x1e4 insns 121/121; diffs 20: [12, 20, 21, 29, 39, 40, 42, 44, 46, 49, 50, 51, 56, 67, 94, 98, 102, 103, 113, 114];     12 M li r25, 1;        B li r24, 1
Retained best candidate

ATERM_81404844 initial 99.0171%
- wrap destination stream view established on entry: 98.84615%; src 0x1d4 base 0x1d4 insns 117/117; diffs 22: [8, 18, 19, 27, 30, 36, 37, 38, 39, 41, 42, 43, 45, 48, 54, 58, 60, 99, 101, 103];      8 M mr r29, r3;        B mr r25, r3
- ascending block index declared with pass counter: 99.0171%; src 0x1d4 base 0x1d4 insns 117/117; diffs 18: [18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     18 M srwi r29, r5, 3;        B srwi r27, r5, 3
- wrap unsigned pass product assigned as separate inner operation: 99.0171%; src 0x1d4 base 0x1d4 insns 117/117; diffs 18: [18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     18 M srwi r29, r5, 3;        B srwi r27, r5, 3
Retained best candidate

ATERM_81402E40 initial 99.791664%
- encryption pointer local assigned after payload clear: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
Retained best candidate

Data audit: both units have identical bytes in every existing non-code section prefix. ATERM .data/.rodata/.sbss exactly identical; .bss/.sdata/.sdata2 only differ in original extraction tail alignment. AOSS .bss/.sbss/.sdata/.sdata2 exactly identical; .data only original extraction tail alignment. No filler added. Trying normal AES table declarations to recover original address selection.
- forward and combined substitution/inverse groups: unit fuzzy 82.53218%, rodata byte identity True; [('ATERM_81404BFC', 97.56716), ('ATERM_8140502C', 95.58696), ('ATERM_81405254', 51.099632), ('ATERM_81405690', 48.560886)]
- substitution tables and inverse mix columns grouped by role: unit fuzzy 82.51177%, rodata byte identity True; [('ATERM_81404BFC', 97.56716), ('ATERM_8140502C', 94.246376), ('ATERM_81405254', 51.099632), ('ATERM_81405690', 48.88192)]
- each actual AES lookup table has its own object: unit fuzzy 82.600914%, rodata byte identity True; [('ATERM_81404BFC', 97.56716), ('ATERM_8140502C', 99.42029), ('ATERM_81405254', 50.830257), ('ATERM_81405690', 48.09594)]
Retained best real-table declarations

ATERMi_ApConfigStart initial 99.805824%
- clock operands assigned after predeclared time snapshot: 99.805824%; src 0x19c base 0x19c insns 103/103; diffs 3: [48, 49, 51];     48 M lwz r6, 0xf8(r30);        B lwz r0, 0xf8(r30)
- first timer uses same inline tick expression as callback timer: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
- predeclared reciprocal assigned before sampled clock: 99.805824%; src 0x19c base 0x19c insns 103/103; diffs 3: [48, 49, 51];     48 M lwz r6, 0xf8(r30);        B lwz r0, 0xf8(r30)
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- all clock conversion temporaries declared before assignments: compile failed
- literal reciprocal and clock expression replace temporary inputs: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000
- clock sampled after reciprocal assignment with predeclared operands: compile failed
Retained best candidate

ATERM_81404BFC initial 97.56716%
- substitution view established before round constants per branch: 97.73508%; src 0x430 base 0x430 insns 268/268; diffs 51: [38, 39, 40, 41, 43, 44, 45, 46, 48, 52, 53, 54, 55, 60, 61, 62, 63, 64, 66, 67];     38 M xor r31, r30, r31;        B xor r0, r6, r0
- round constant pointer has each key-size branch scope: 98.01492%; src 0x430 base 0x430 insns 268/268; diffs 37: [38, 39, 40, 41, 43, 44, 45, 46, 48, 52, 53, 54, 55, 58, 60, 61, 62, 63, 64, 66];     38 M xor r31, r30, r31;        B xor r0, r6, r0
- initial four big-endian words assembled before ordered publication: 98.3097%; src 0x430 base 0x430 insns 268/268; diffs 73: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 40, 41, 43];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
Retained best candidate

ATERM_81404BFC initial 98.3097%
- ordered initial words with substitution-first branch setup: 98.477615%; src 0x430 base 0x430 insns 268/268; diffs 67: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 40, 41, 43];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
- ordered initial words with branch-local round constants: 98.75746%; src 0x430 base 0x430 insns 268/268; diffs 53: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 40, 41, 43];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
- ordered initial words with both target branch view lifetimes: 98.589554%; src 0x430 base 0x430 insns 268/268; diffs 59: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 40, 41, 43];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
Retained best candidate

ATERM_8140276C initial 95.965515%
- fallback current-record search resets index as target instruction 124: 95.41954%; src 0x2b8 base 0x2b8 insns 174/174; diffs 97: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 18, 20, 21, 22, 23, 24, 25, 26, 27];      5 M mr r24, r3;        B mr r23, r3
- fallback current-record view retained across previous-record search: 98.85058%; src 0x2b8 base 0x2b8 insns 174/174; diffs 38: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 66, 69, 70, 72, 74, 80, 82, 84, 87];      8 M addi r20, r3, 4;        B addi r31, r3, 4
- fallback reset with result initialized separately: compile failed
Retained best candidate

ATERM_8140276C initial 98.85058%
- found and final result initialized before first traversal index: 98.44827%; src 0x2b8 base 0x2b8 insns 174/174; diffs 49: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 66, 69, 70, 72, 74, 76, 78, 80, 82];      8 M addi r20, r3, 4;        B addi r31, r3, 4
- first traversal pointers assigned after scalar initialization: 98.85058%; src 0x2b8 base 0x2b8 insns 174/174; diffs 38: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 66, 69, 70, 72, 74, 80, 82, 84, 87];      8 M addi r20, r3, 4;        B addi r31, r3, 4
- fallback presence flags initialized before record views and SSID clear: 98.965515%; src 0x2b8 base 0x2b8 insns 174/174; diffs 34: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 66, 69, 70, 72, 74, 80, 82, 84, 87];      8 M addi r20, r3, 4;        B addi r31, r3, 4
Retained best candidate

ATERM_81402A24 initial 90.5019%
- descriptor fields address record set entries by loop index: 89.29278%; src 0x41c base 0x41c insns 263/263; diffs 242: [0, 2, 3, 6, 8, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25];      0 M stwu r1, -0x80(r1);        B stwu r1, -0x90(r1)
- indexed descriptors use original counted forward loop: 89.29278%; src 0x41c base 0x41c insns 263/263; diffs 242: [0, 2, 3, 6, 8, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25];      0 M stwu r1, -0x80(r1);        B stwu r1, -0x90(r1)
- per-iteration record view follows descriptor view: 89.69202%; src 0x418 base 0x41c insns 262/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
Retained best candidate

ATERM_814033F0 initial 98.576645%
- option cursor assignment follows all parser declarations: 98.576645%; src 0x224 base 0x224 insns 137/137; diffs 36: [11, 13, 16, 28, 29, 34, 39, 47, 55, 60, 65, 66, 71, 72, 74, 75, 81, 82, 85, 86];     11 M li r23, 0;        B li r22, 0
- hex byte decoder counts with while increment condition: 98.576645%; src 0x224 base 0x224 insns 137/137; diffs 36: [11, 13, 16, 28, 29, 34, 39, 47, 55, 60, 65, 66, 71, 72, 74, 75, 81, 82, 85, 86];     11 M li r23, 0;        B li r22, 0
- aligned option span added before cursor address: 98.649635%; src 0x224 base 0x224 insns 137/137; diffs 35: [11, 13, 16, 28, 29, 34, 39, 47, 55, 60, 65, 66, 71, 72, 74, 75, 81, 82, 85, 86];     11 M li r23, 0;        B li r22, 0
Retained best candidate

ATERM_814031DC initial 97.74436%
- MAC low nibble assigned after high nibble output: 95.150375%; src 0x214 base 0x214 insns 133/133; diffs 48: [49, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 70, 71, 72, 74, 75];     49 M addi r6, r1, 8;        B addi r5, r1, 8
- MAC source byte kept as promoted signed scalar: 97.74436%; src 0x214 base 0x214 insns 133/133; diffs 44: [50, 51, 57, 59, 61, 62, 63, 65, 66, 67, 71, 72, 75, 76, 77, 78, 79, 80, 82, 83];     50 M addi r7, r1, 0x38;        B addi r8, r1, 0x38
- MAC formatting traverses fixed six bytes with do loop: 90.22556%; src 0x20c base 0x214 insns 131/133; --- replace mine 47:48 base 47:49;   M   47 beq 312;   B   47 beq 320
Retained best candidate

ATERM_814021BC initial 96.61688%
- network settings base view survives both configuration clears: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- IP clear uses network member address directly: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- IP configuration view initialized after clear: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
Retained best candidate

ATERMi_AutoConfigThread initial 94.75%
- completion mask reuses consumed result scalar: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- state shift and bias assigned as separate operations: 94.25%; src 0xa0 base 0xa0 insns 40/40; diffs 8: [21, 22, 23, 24, 26, 28, 29, 30];     21 M li r5, -1;        B li r4, -1
- completion forward difference scoped after socket cleanup: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
Retained best candidate

ATERMi_ApConfigEnd initial 93.94574%
- final progress storage declared alongside captured state: 93.94574%; src 0x1f4 base 0x204 insns 125/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
- cancellation alarm loop expressed as condition-only for loop: 93.94574%; src 0x1f4 base 0x204 insns 125/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
- join alarm delay multiplies unsigned wide tick count: 90.53488%; src 0x1f8 base 0x204 insns 126/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
Retained best candidate

ATERM_814038C8 initial 85.12934%
- protocol loop uses explicit initial cancellation exit: 83.953735%; src 0xef0 base 0xedc insns 956/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- wait alarm tick conversion sampled before queue setup: 83.078865%; src 0xef0 base 0xedc insns 956/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- connection and session key views retain byte type: 85.12934%; src 0xef0 base 0xedc insns 956/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
Retained best candidate

ATERM_81405ACC initial 83.09028%
- MD5 input view declared independently of copy indices: compile failed
- MD5 partial tail uses forward while loop: 83.09028%; src 0x230 base 0x240 insns 140/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:5 base 4:11
- MD5 full block traversal advances after transform: 83.09028%; src 0x230 base 0x240 insns 140/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:5 base 4:11
Retained best candidate

ATERM_81405254 initial 50.830257%
- AES input low byte precedes shifted adjacent byte: 50.867157%; src 0x41c base 0x43c insns 263/271; --- insert mine 24:24 base 24:26;   B   24 srawi r30, r4, 1;   B   25 lbz r11, 0xc(r5)
- AES round-pair counter declared before initial state: 54.959408%; src 0x41c base 0x43c insns 263/271; --- replace mine 10:11 base 10:11;   M   10 slwi r24, r12, 8;   B   10 slwi r23, r12, 8
- AES four lookup XOR grouping changed: 43.819187%; src 0x41c base 0x43c insns 263/271; --- replace mine 10:11 base 10:11;   M   10 slwi r24, r12, 8;   B   10 slwi r23, r12, 8
Retained best candidate

ATERM_81405690 initial 48.09594%
- AES input low byte precedes shifted adjacent byte: 48.132843%; src 0x41c base 0x43c insns 263/271; --- insert mine 24:24 base 24:26;   B   24 srawi r30, r4, 1;   B   25 lbz r11, 0xc(r5)
- AES round-pair counter declared before initial state: 52.671585%; src 0x41c base 0x43c insns 263/271; --- replace mine 10:11 base 10:11;   M   10 slwi r24, r12, 8;   B   10 slwi r23, r12, 8
- AES four lookup XOR grouping changed: 42.527676%; src 0x41c base 0x43c insns 263/271; --- replace mine 12:14 base 12:14;   M   12 slwi r21, r11, 0x18;   M   13 slwi r20, r10, 0x10
Retained best candidate

ATERM_81405ACC initial 83.09028%
- MD5 remaining count computed once before tail condition: 83.298615%; src 0x230 base 0x240 insns 140/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:5 base 4:11
Retained best candidate

ATERM_81405D0C initial 53.851387%
- MD5 canonical add rotate add updates state directly: 82.193054%; src 0xa60 base 0xb40 insns 664/720; --- replace mine 5:80 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
- MD5 message word and constant cached before state addition: 57.45139%; src 0xa88 base 0xb40 insns 674/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0xb0(r1);   B    0 stwu r1, -0xa0(r1)
- MD5 decoder advances separate word and byte indices: 52.87361%; src 0xa58 base 0xb40 insns 662/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0xa0(r1)
Retained best candidate

ATERM_81402FC0 initial 100.0%
- packet checksum accumulator declared after option scalars: 98.51852%; src 0x21c base 0x21c insns 135/135; diffs 32: [8, 10, 13, 15, 18, 23, 32, 34, 36, 38, 40, 42, 44, 46, 54, 59, 66, 67, 68, 72];      8 M li r29, 0;        B li r31, 0
- packet checksum remainder uses explicit cursor advance: 100.0%; src 0x21c base 0x21c insns 135/135; diffs 2: [18, 23];     18 M bge -3631;        B bge -3647
- packet option parser tests positive payload before validity exits: 100.0%; src 0x21c base 0x21c insns 135/135; diffs 2: [18, 23];     18 M bge -3631;        B bge -3647
Retained exact candidate

AOSS_81401DC0 initial 99.375%
- CRC final reflected bit writes its selected result directly: 86.875%; src 0xd0 base 0xc0 insns 52/48; --- replace mine 39:48 base 39:44;   M   39 beq 28;   M   40 srwi r0, r3, 1
- CRC seed parameter reused as row counter: 99.375%; src 0xc0 base 0xc0 insns 48/48; diffs 4: [39, 41, 42, 43];     39 M srwi r0, r3, 1;        B srwi r3, r3, 1
- CRC row output addressed by index: 90.270836%; src 0xc4 base 0xc0 insns 49/48; --- replace mine 1:3 base 1:2;   M    1 li r6, 0;   M    2 li r3, 0
Retained best candidate

AOSS_81401574 initial 98.87597%
- request payload view initialized with response view: 96.93799%; src 0x204 base 0x204 insns 129/129; diffs 41: [5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 33];      5 M lwz r29, 0(0);        B lwz r27, 0(0)
- response view assigned after allocation clear: 98.87597%; src 0x204 base 0x204 insns 129/129; diffs 28: [5, 6, 9, 15, 24, 25, 33, 39, 42, 48, 51, 53, 54, 65, 68, 74, 76, 77, 79, 81];      5 M lwz r29, 0(0);        B lwz r27, 0(0)
- request parameter typed as record view throughout function: compile failed
Retained best candidate

ATERM_81405D0C initial 82.193054%
- MD5 RFC decoder with independent word and byte traversal: 74.37361%; src 0x988 base 0xb40 insns 610/720; --- replace mine 5:10 base 5:8;   M    5 li r0, 0x10;   M    6 addi r6, r1, 8
- MD5 decoder uses word-indexed input view: 74.69722%; src 0x980 base 0xb40 insns 608/720; --- replace mine 5:12 base 5:14;   M    5 li r0, 0x10;   M    6 addi r6, r1, 8
- MD5 decoder traverses bytes and derives destination word: 74.270836%; src 0x984 base 0xb40 insns 609/720; --- replace mine 5:8 base 5:8;   M    5 li r0, 0x10;   M    6 addi r5, r1, 8
Retained best candidate

ATERM_81405D0C initial 82.193054%
- restore target word buffer erasure after state accumulation: 82.91944%; src 0xa70 base 0xb40 insns 668/720; --- replace mine 5:80 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
- target decoder uses indexed words and independently indexed input with buffer erasure: 83.825%; src 0xa78 base 0xb40 insns 670/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
- target indexed decoder erasure and canonical RFC G operands: 83.859726%; src 0xa78 base 0xb40 insns 670/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
Retained best candidate

AOSS_81401DC0 initial 99.375%
- CRC last bit branches from the clear-bit case: 93.541664%; src 0xc4 base 0xc0 insns 49/48; --- replace mine 39:41 base 39:42;   M   39 srwi r0, r3, 1;   M   40 xoris r3, r0, 0xedb8
- CRC last bit saved before shifting current row value: 98.541664%; src 0xc0 base 0xc0 insns 48/48; diffs 8: [34, 36, 37, 38, 39, 41, 42, 43];     34 M srwi r0, r3, 1;        B srwi r3, r3, 1
- CRC row accumulator reuses incoming seed parameter: 99.375%; src 0xc0 base 0xc0 insns 48/48; diffs 4: [39, 41, 42, 43];     39 M srwi r0, r3, 1;        B srwi r3, r3, 1
Retained best candidate

AOSS_81401574 initial 98.87597%
- request response declaration follows request-view declaration: 98.87597%; src 0x204 base 0x204 insns 129/129; diffs 28: [5, 6, 9, 15, 24, 25, 33, 39, 42, 48, 51, 53, 54, 65, 68, 74, 76, 77, 79, 81];      5 M lwz r29, 0(0);        B lwz r27, 0(0)
Retained best candidate

ATERM_81405D0C initial 83.859726%
- erase MD5 words with byte-indexed loop: 86.11528%; src 0xa84 base 0xb40 insns 673/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
- erase MD5 words with advancing byte view: 86.11528%; src 0xa84 base 0xb40 insns 673/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
- erase MD5 words through four byte fields per word: 86.51945%; src 0xa94 base 0xb40 insns 677/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
Retained best candidate

ATERM_81405D0C initial 86.51945%
- target erases temporary message words in two thirty-two-byte chunks: 90.6375%; src 0xb00 base 0xb40 insns 704/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
- target byte traversal controls decoder and thirty-two-byte buffer wipe: 90.6375%; src 0xb00 base 0xb40 insns 704/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
- message words cleared in four sixteen-byte chunks: 88.30278%; src 0xac0 base 0xb40 insns 688/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
Retained best candidate

AOSS_813FFD68 initial 96.981735%
- config result and record views initialized in declarations: 96.981735%; src 0x364 base 0x36c insns 217/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- SSID ASCII validation uses unsigned range expression: 92.43379%; src 0x34c base 0x36c insns 211/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- SSID cursor dereference advances after validation byte assignment: 96.981735%; src 0x364 base 0x36c insns 217/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained best candidate

AOSS_814013AC initial 94.48245%
- response initial view assigned with declaration: 92.59649%; src 0x1d0 base 0x1c8 insns 116/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:9 base 8:8
- response step length uses one converted length expression: 96.32456%; src 0x1c8 base 0x1c8 insns 114/114; diffs 43: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39];      6 M mr r24, r5;        B mr r27, r3
- key config views scoped to their option cases: 87.447365%; src 0x1c0 base 0x1c8 insns 112/114; --- replace mine 6:11 base 6:11;   M    6 mr r27, r5;   M    7 mr r25, r3
Retained best candidate

AOSS_81401E80 initial 92.82313%
- packet half view cached for mask and swap operations: 91.63265%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r29, r3;   B    6 mr r21, r3
- key mask initialization computes XOR before byte store: 92.82313%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
- second-half XOR scalar tail uses while advance: 92.82313%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
Retained best candidate

ATERM_81405D0C initial 90.6375%
- MD5 decoder increments word index after each decoded word: 90.9875%; src 0xb1c base 0xb40 insns 711/720; --- replace mine 5:89 base 5:98;   M    5 li r6, 2;   M    6 addi r5, r1, 8
- MD5 decoder advances both indices per decoded word: 90.9875%; src 0xb1c base 0xb40 insns 711/720; --- replace mine 5:89 base 5:98;   M    5 li r6, 2;   M    6 addi r5, r1, 8
- MD5 decoder separates word increment and byte increment statements: 90.86667%; src 0xb00 base 0xb40 insns 704/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
Retained best candidate

AOSS_814001B4 initial 88.78481%
- packet message view scoped independently of receive storage: 85.08861%; src 0x130 base 0x13c insns 76/79; --- replace mine 3:6 base 3:11;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- packet dispatch returns selected handler result directly: 83.27848%; src 0x124 base 0x13c insns 73/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- packet message length assigned after opcode declaration: 88.78481%; src 0x12c base 0x13c insns 75/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained best candidate

AOSS_81400E0C initial 86.81579%
- option record view initialized before clear: 85.63158%; src 0x2fc base 0x2f8 insns 191/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8
- option scalar byte view advances with dereference: 86.81579%; src 0x2fc base 0x2f8 insns 191/190; --- replace mine 19:20 base 19:20;   M   19 bgt -10867;   B   19 bgt -11215
- option network scalar remainder tests remaining byte count: 87.8421%; src 0x2f4 base 0x2f8 insns 189/190; --- replace mine 19:20 base 19:20;   M   19 bgt -10867;   B   19 bgt -11215
Retained best candidate

AOSS_81400830 initial 83.99377%
- payload RC4 output and input views assigned after pair count: 83.99377%; src 0x4ec base 0x504 insns 315/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- payload RC4 complete pairs use counted for traversal: 83.99377%; src 0x4ec base 0x504 insns 315/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- payload CRC tail advances source byte cursor: 83.576324%; src 0x4ec base 0x504 insns 315/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
Retained best candidate

AOSS_814020CC initial 81.65%
- host wait samples reciprocal clock before constant multiplication: 81.23333%; src 0xe4 base 0xf0 insns 57/60; --- replace mine 3:5 base 3:6;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- host wait counter increment folded into retry condition: 81.65%; src 0xe4 base 0xf0 insns 57/60; --- replace mine 3:5 base 3:6;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- host wait delay uses wide unsigned clock product: 76.15%; src 0xe8 base 0xf0 insns 58/60; --- replace mine 3:6 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained best candidate

AOSS_81401778 initial 77.53846%
- hello CRC checksum narrows after complement: 77.13553%; src 0x440 base 0x444 insns 272/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- hello pair processing traverses packet byte view: 76.1978%; src 0x444 base 0x444 insns 273/273; diffs 244: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24];      5 M lis r31, 0;        B lwz r28, 0(0)
- hello state index byte mask assigned separately from remainder: 77.53846%; src 0x440 base 0x444 insns 272/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
Retained best candidate

AOSS_81401C9C initial 77.0685%
- KSA byte state view initialized alongside counters: 77.0685%; src 0x130 base 0x124 insns 76/73; --- replace mine 0:5 base 0:5;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
- KSA initialization remainder uses advancing byte view: 76.9315%; src 0x130 base 0x124 insns 76/73; --- replace mine 0:5 base 0:5;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
- KSA swapping caches input key byte before modular addition: 71.178085%; src 0x130 base 0x124 insns 76/73; --- replace mine 0:5 base 0:5;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
Retained best candidate

AOSS_Init_old initial 28.42298%
- initialization wait counters use fixed signed sixteen-bit types: 28.42298%; src 0x1794 base 0x18c0 insns 1509/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- initialization failure result stored as signed return value: 28.42298%; src 0x1794 base 0x18c0 insns 1509/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- initialization response view declared and assigned before packet fields: 28.419823%; src 0x1790 base 0x18c0 insns 1508/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
Retained best candidate

ATERM_81405D0C initial 90.9875%
- signed MD5 decoder word counter matches independent store traversal: 90.9875%; src 0xb1c base 0xb40 insns 711/720; --- replace mine 5:89 base 5:98;   M    5 li r6, 2;   M    6 addi r5, r1, 8
- MD5 decoder word counter masked to sixteen-word buffer: 91.73194%; src 0xb3c base 0xb40 insns 719/720; --- replace mine 6:10 base 6:12;   M    6 addi r6, r1, 8;   M    7 lwz r8, 0(r3)
- MD5 decoder explicitly advances word counter after stores: 90.86667%; src 0xb00 base 0xb40 insns 704/720; --- replace mine 5:82 base 5:98;   M    5 li r5, 2;   M    6 lwz r0, 0(r3)
Retained best candidate

ATERM_81405D0C initial 91.73194%
- MD5 decoder factored as standard byte-length conversion helper: 87.34722%; src 0xa20 base 0xb40 insns 648/720; --- replace mine 5:13 base 5:14;   M    5 li r0, 0x10;   M    6 addi r7, r1, 8
- MD5 decoder factored as standard word-count conversion helper: 87.34722%; src 0xa20 base 0xb40 insns 648/720; --- replace mine 5:13 base 5:14;   M    5 li r0, 0x10;   M    6 addi r7, r1, 8
- MD5 word decoding helper carries inline qualifier: 87.34722%; src 0xa20 base 0xb40 insns 648/720; --- replace mine 5:13 base 5:14;   M    5 li r0, 0x10;   M    6 addi r7, r1, 8
Retained best candidate

AOSS_81401DC0 initial 99.375%
- CRC reflected-bit helper shared by all eight polynomial steps: 0%; src 0x6c base 0xc0 insns 27/48; --- replace mine 0:26 base 0:47;   M    0 stwu r1, -0x10(r1);   M    1 mflr r0
- CRC final polynomial step expressed through reflected-bit helper: 99.375%; src 0xc0 base 0xc0 insns 48/48; diffs 4: [39, 41, 42, 43];     39 M srwi r0, r3, 1;        B srwi r3, r3, 1
- CRC reflected-bit helper shifts then applies captured-bit polynomial: 0%; src 0x6c base 0xc0 insns 27/48; --- replace mine 0:26 base 0:47;   M    0 stwu r1, -0x10(r1);   M    1 mflr r0
Retained best candidate

MD5 masked-word-index candidate rejected after source review: masking is absent from the target and unnecessary for this fixed block; retain advancing word index despite lower fuzzy score.

AOSS_81401DC0 initial 99.375%
- CRC row storage signed with explicit logical right shift: 99.375%; src 0xc0 base 0xc0 insns 48/48; diffs 4: [39, 41, 42, 43];     39 M srwi r0, r3, 1;        B srwi r3, r3, 1
- CRC traversal counter signed with unchanged bounded row count: 99.375%; src 0xc0 base 0xc0 insns 48/48; diffs 4: [39, 41, 42, 43];     39 M srwi r0, r3, 1;        B srwi r3, r3, 1
- CRC loop advances row count before publishing completed row: 99.375%; src 0xc0 base 0xc0 insns 48/48; diffs 4: [39, 41, 42, 43];     39 M srwi r0, r3, 1;        B srwi r3, r3, 1
Retained best candidate

AOSS_81401DC0 initial 99.375%
- speed optimization of standard eight-bit reflected CRC loop: 100.0%; src 0xc0 base 0xc0 insns 48/48; diffs 0: []
- speed optimization CRC loop with captured low bit: 92.916664%; src 0xc0 base 0xc0 insns 48/48; diffs 35: [1, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 24, 26];      1 M li r3, 0;        B li r5, 0
- speed optimization CRC loop with signed bit counter: 100.0%; src 0xc0 base 0xc0 insns 48/48; diffs 0: []
Retained exact candidate

ATERM_81402E40 initial 0%
- speed optimization checksum uses original scalar byte loop: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- speed optimization checksum uses postincrement cursor loop: 82.135414%; src 0x160 base 0x180 insns 88/96; --- replace mine 5:12 base 5:12;   M    5 mr r28, r5;   M    6 mr r26, r3
- speed optimization checksum loop retains nonempty packet guard: 98.75%; src 0x184 base 0x180 insns 97/96; --- insert mine 9:9 base 9:10;   B    9 mr r3, r27; --- delete mine 10:11 base 11:11
Retained best candidate

AOSS_81401C9C initial 0%
- speed optimization KSA uses canonical state byte initializer: 83.53425%; src 0x130 base 0x124 insns 76/73; --- replace mine 0:1 base 0:2;   M    0 stwu r1, -0x20(r1);   B    0 stwu r1, -0x10(r1)
- speed optimization KSA initializer retains nonempty guard: 82.16438%; src 0x134 base 0x124 insns 77/73; --- replace mine 0:1 base 0:2;   M    0 stwu r1, -0x20(r1);   B    0 stwu r1, -0x10(r1)
- speed optimization KSA initializer uses explicit advancing while: 83.53425%; src 0x130 base 0x124 insns 76/73; --- replace mine 0:1 base 0:2;   M    0 stwu r1, -0x20(r1);   B    0 stwu r1, -0x10(r1)
Retained best candidate

ATERM_81402FC0 initial 0%
- speed optimization checksum uses original scalar byte loop: 100.0%; src 0x21c base 0x21c insns 135/135; diffs 2: [18, 23];     18 M bge -3755;        B bge -3647
- speed optimization checksum uses postincrement cursor loop: 87.59259%; src 0x1fc base 0x21c insns 127/135; --- replace mine 5:6 base 5:6;   M    5 mr r25, r3;   B    5 mr r27, r3
- speed optimization checksum loop retains nonempty packet guard: 99.25926%; src 0x220 base 0x21c insns 136/135; --- replace mine 18:20 base 18:19;   M   18 bge -3755;   M   19 bge -3759
Retained exact candidate

AOSS_81400E0C initial 30.273684%
- speed optimization network scalar assembled by canonical byte loop: 90.04211%; src 0x304 base 0x2f8 insns 193/190; --- replace mine 19:20 base 19:20;   M   19 bgt -11307;   B   19 bgt -11215
- speed optimization network scalar loop uses advancing view: 95.26316%; src 0x2fc base 0x2f8 insns 191/190; --- replace mine 19:20 base 19:20;   M   19 bgt -11307;   B   19 bgt -11215
- speed optimization network scalar loop counts signed byte length: 91.41579%; src 0x2e4 base 0x2f8 insns 185/190; --- replace mine 19:20 base 19:20;   M   19 bgt -11307;   B   19 bgt -11215
Retained best candidate

AOSS_81401E80 initial 11.714286%
- speed optimization mask uses canonical half-packet byte loop: 92.72109%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
- speed optimization mask retains nonempty half guard: 92.04082%; src 0x24c base 0x24c insns 147/147; diffs 95: [6, 8, 9, 10, 11, 12, 15, 19, 22, 24, 28, 29, 30, 32, 33, 34, 35, 36, 37, 38];      6 M mr r28, r3;        B mr r21, r3
- speed optimization mask advances second-half and key views: 86.4966%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
Retained best candidate

ATERM_81405D0C initial 83.53472%
- speed optimization canonical MD5 byte decoder and message erasure: 94.459724%; src 0xb60 base 0xb40 insns 728/720; --- replace mine 7:10 base 7:10;   M    7 lwz r15, 0(r3);   M    8 li r19, 0
- speed optimization canonical MD5 word-count decoder and message erasure: 86.406944%; src 0xb1c base 0xb40 insns 711/720; --- replace mine 5:81 base 5:98;   M    5 li r6, 2;   M    6 addi r5, r1, 8
- speed optimization canonical MD5 decoder and cursor-based erasure: 97.255554%; src 0xb40 base 0xb40 insns 720/720; diffs 74: [7, 8, 9, 11, 12, 13, 15, 16, 17, 18, 20, 22, 23, 24, 26, 28, 29, 30, 34, 35];      7 M lwz r15, 0(r3);        B lwz r17, 0(r3)
Retained best candidate

AOSS_81400830 initial 0%
- speed optimization payload CRC uses canonical signed byte loop: 11.5856695%; src 0x570 base 0x504 insns 348/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- speed optimization payload CRC uses canonical unsigned byte loop: 72.389404%; src 0x594 base 0x504 insns 357/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- speed optimization payload CRC byte pointer advances independently: 11.570093%; src 0x570 base 0x504 insns 348/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
Retained best candidate

ATERM_81405D0C initial 97.255554%
- MD5 decoder indices declared before state values: 99.74306%; src 0xb40 base 0xb40 insns 720/720; diffs 35: [12, 15, 16, 17, 22, 23, 26, 28, 29, 34, 35, 38, 41, 43, 46, 50, 51, 56, 58, 60];     12 M li r16, 0;        B li r14, 0
- MD5 decoder indices scoped independently of buffer wipe: compile failed
- MD5 input byte index precedes word index and state values: 99.673615%; src 0xb40 base 0xb40 insns 720/720; diffs 44: [8, 12, 15, 16, 17, 18, 20, 22, 23, 24, 26, 28, 29, 30, 34, 35, 36, 38, 41, 43];      8 M li r16, 0;        B li r15, 0
Retained best candidate

AOSS_81400830 initial 72.389404%
- speed optimization RC4 uses standard one-byte stream traversal: 75.40187%; src 0x5bc base 0x504 insns 367/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- speed optimization RC4 traverses advancing source and destination views: 77.14019%; src 0x5ac base 0x504 insns 363/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- speed optimization RC4 publishes cursor state after byte output: 72.361374%; src 0x5b4 base 0x504 insns 365/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
Retained best candidate

ATERM_81405ACC initial 0%
- speed optimization MD5 input copies use canonical byte-indexed loops: 88.583336%; src 0x22c base 0x240 insns 139/144; --- replace mine 26:27 base 26:27;   M   26 blt 232;   B   26 blt 244
- speed optimization MD5 input copies use advancing byte cursors: 74.86806%; src 0x21c base 0x240 insns 135/144; --- delete mine 5:6 base 5:5;   M    5 mr r31, r4; --- insert mine 7:7 base 6:7
- speed optimization MD5 byte copy loops use signed remainder bounds: 77.986115%; src 0x1fc base 0x240 insns 127/144; --- delete mine 13:14 base 13:13;   M   13 rlwinm r8, r6, 0x1d, 0x1a, 0x1f; --- insert mine 16:16 base 15:16
Retained best candidate

ATERM_814038C8 initial 44.91798%
- speed optimization response checksums use canonical source loops: 83.25552%; src 0xf28 base 0xedc insns 970/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- speed optimization response checksums use advancing cursor loops: 81.921135%; src 0xee8 base 0xedc insns 954/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- speed optimization response checksums retain initial empty guard: 83.13144%; src 0xf30 base 0xedc insns 972/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
Retained best candidate

ATERM_81405D0C initial 99.74306%
- MD5 byte index word index and input word view precede state values: 100.0%; src 0xb40 base 0xb40 insns 720/720; diffs 0: []
- MD5 word index word view and byte index precede state values: 99.673615%; src 0xb40 base 0xb40 insns 720/720; diffs 44: [8, 12, 15, 16, 17, 18, 20, 22, 23, 24, 26, 28, 29, 30, 34, 35, 36, 38, 41, 43];      8 M li r14, 0;        B li r15, 0
- MD5 all four input bytes addressed through explicit word view: 100.0%; src 0xb40 base 0xb40 insns 720/720; diffs 0: []
Retained exact candidate

Compiler-option audit: the default IPL flags end with size optimization (-O4,s). Testing speed optimization (-O4,p), scoped only to these two NonMatching C objects, recovered the original individual register-save sequences for AOSS_813FFD68 (219/219, diffs 0) and AOSS_814001B4 (79/79, diffs 0). Canonical CRC and MD5 source loops then recovered their original compiler-generated unrolling. Adding -ipa off split pooled BSS and broke the existing AOSS_814004D0 data reference, so that option was rejected and reverted. Keeping file IPA with -inline off preserves all original data mappings and prevents the compact CRC builder from being inlined into its two callers. No other translation unit receives these flags.
ATERM_81405D0C now instruction-exact: 720/720, diffs 0, objdiff 100%. Its final source restores the original temporary-message erasure, normal MD5 add/rotate/add operations, and byte-index/word-index decoder with an explicit input-word view. The intermediate manually expanded decoder/wipe and masked-index experiment are absent from the final source.
AOSS_81401DC0 now instruction-exact: 48/48, diffs 0, objdiff 100%, ordinary eight-bit polynomial loop.
Native supplemental verification passed: AES-128/192/256 encryption/decryption, MD5 lengths 0/1/3/55/56/64/130, scan comparison fallback/unchanged/status-change/empty cases with changed-index writes, KSA lengths 0/1/7/8/9/16/256/300, all 256 CRC rows, and RC4 payload decode/checksum rejection lengths 1/7/8/9/16/31/32/255/256/257. Vendor transform and network conversion are stubbed only in the isolated payload test; these are not PPC instruction-match evidence.

ATERM full clean gate before first commit:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 4528/19204 data 18448/18864 functions 7/26 fuzzy 88.3064 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 6/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match None
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 38.88889
[src/scene/setting/ATERM]   section .sdata size 56 match None
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 88.3064
[src/scene/setting/ATERM]   below 100: ATERM_814021BC 96.61688
[src/scene/setting/ATERM]   below 100: ATERM_8140276C 98.965515
[src/scene/setting/ATERM]   below 100: ATERM_81402A24 81.04943
[src/scene/setting/ATERM]   below 100: ATERM_81402E40 99.791664
[src/scene/setting/ATERM]   below 100: ATERM_814031DC 53.969925
[src/scene/setting/ATERM]   below 100: ATERM_814033F0 98.649635
[src/scene/setting/ATERM]   below 100: ATERM_814036D8 99.08064
[src/scene/setting/ATERM]   below 100: ATERM_814038C8 83.25657
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERM_81404844 95.1453
[src/scene/setting/ATERM]   below 100: ATERM_81404A18 99.09091
[src/scene/setting/ATERM]   below 100: ATERM_81404BFC 98.75746
[src/scene/setting/ATERM]   below 100: ATERM_8140502C 99.42029
[src/scene/setting/ATERM]   below 100: ATERM_81405254 54.959408
[src/scene/setting/ATERM]   below 100: ATERM_81405690 52.671585
[src/scene/setting/ATERM]   below 100: ATERM_81405ACC 88.583336
[src/scene/setting/ATERM]   below 100: ATERMi_ApConfigStart 99.805824
[src/scene/setting/ATERM]   below 100: ATERMi_ApConfigEnd 99.4186
[src/scene/setting/ATERM]   below 100: ATERMi_ApConfigGetState 99.42857
[src/scene/setting/ATERM] baseline: code 1648/19204 data 18448 functions 6 fuzzy 82.5403
regressions vs baseline: 0
global matched_code_percent: 82.45576 -> 82.59813
global fuzzy_match_percent: 95.09687 -> 95.14157
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.46201 -> 89.46201
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```

AOSS_814020CC initial 98.13333%
- startup error branch precedes common successful host return: 100.0%; src 0xf0 base 0xf0 insns 60/60; diffs 0: []
- startup result explicitly selected in success and failure branches: 98.13333%; src 0xec base 0xf0 insns 59/60; --- replace mine 11:12 base 11:12;   M   11 b 164;   B   11 b 168
- startup failure exits before host acquisition block: 91.4%; src 0xec base 0xf0 insns 59/60; --- replace mine 11:12 base 11:12;   M   11 b 164;   B   11 b 168
Retained exact candidate

AOSS_814013AC initial 96.32456%
- response payload view advances before converted option length: 96.18421%; src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 34, 37, 38, 39, 40, 41, 42, 55, 56];      6 M mr r24, r5;        B mr r27, r3
- single response cursor survives selection and option traversal: 96.18421%; src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 34, 37, 38, 39, 40, 41, 42, 55, 56];      6 M mr r24, r5;        B mr r27, r3
- single response cursor initializes flags after selected record: 95.9386%; src 0x1c8 base 0x1c8 insns 114/114; diffs 47: [6, 7, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      6 M mr r24, r5;        B mr r27, r3
Retained best candidate

AOSS_81401574 initial 98.87597%
- typed requested access-point record view initialized before response: 98.87597%; src 0x204 base 0x204 insns 129/129; diffs 28: [5, 6, 9, 15, 24, 25, 33, 39, 42, 48, 51, 53, 54, 65, 68, 74, 76, 77, 79, 81];      5 M lwz r29, 0(0);        B lwz r27, 0(0)
- typed request-record parameter view initialized before response: 98.87597%; src 0x204 base 0x204 insns 129/129; diffs 28: [5, 6, 9, 15, 24, 25, 33, 39, 42, 48, 51, 53, 54, 65, 68, 74, 76, 77, 79, 81];      5 M lwz r29, 0(0);        B lwz r27, 0(0)
- response typed view established after request storage clear: 96.434105%; src 0x204 base 0x204 insns 129/129; diffs 43: [5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26];      5 M lwz r3, 0(0);        B lwz r27, 0(0)
Retained best candidate

AOSS_813FFD68: objdiff 100%, 219/219, diffs 0 after the per-object optimization correction.
AOSS_814001B4: objdiff 100%, 79/79, diffs 0 after the same correction.
AOSS_814020CC: objdiff 100%, 60/60, diffs 0 after placing the common successful return after the explicit startup failure branch.
AOSS vendor transform independently verified against a two-round reference for even lengths 2/4/8/16/30/32/64/260 and key lengths 1/5/10, without the vendor-transform stub used by the separate payload test.
AOSS full clean gate before unit commit:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 4868/16192 data 3896/3928 functions 13/21 fuzzy 68.5190 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 13/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 42.857143
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 68.51902
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 28.1875
[src/scene/setting/AOSS]   below 100: AOSS_81400830 87.78505
[src/scene/setting/AOSS]   below 100: AOSS_81400E0C 95.26316
[src/scene/setting/AOSS]   below 100: AOSS_814013AC 96.32456
[src/scene/setting/AOSS]   below 100: AOSS_81401574 98.87597
[src/scene/setting/AOSS]   below 100: AOSS_81401778 77.92308
[src/scene/setting/AOSS]   below 100: AOSS_81401C9C 83.53425
[src/scene/setting/AOSS]   below 100: AOSS_81401E80 92.72109
[src/scene/setting/AOSS] baseline: code 3244/16192 data 3896 functions 9 fuzzy 67.0618
regressions vs baseline: 0
global matched_code_percent: 82.45576 -> 82.60614
global fuzzy_match_percent: 95.09687 -> 95.14172
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.46201 -> 89.46201
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```

ATERM_814031DC initial 53.969925%
- MAC encoder stops immediately after final address byte: 90.766914%; src 0x204 base 0x214 insns 129/133; --- replace mine 47:48 base 47:49;   M   47 beq 304;   B   47 beq 320
- MAC encoder expresses known nonempty traversal with do loop: 90.22556%; src 0x20c base 0x214 insns 131/133; --- replace mine 47:48 base 47:49;   M   47 beq 312;   B   47 beq 320
- MAC encoder traverses bounded address byte views: 89.99248%; src 0x22c base 0x214 insns 139/133; --- replace mine 47:51 base 47:50;   M   47 beq 344;   M   48 addi r6, r1, 8
Retained best candidate

ATERM_814031DC initial 90.766914%
- MAC format traversal terminates at six-byte equality: 53.969925%; src 0x2fc base 0x214 insns 191/133; --- replace mine 47:49 base 47:49;   M   47 beq 552;   M   48 li r0, 3
- MAC format traversal counts remaining bytes separately from delimiter index: 51.56391%; src 0x30c base 0x214 insns 195/133; --- replace mine 47:49 base 47:49;   M   47 beq 568;   M   48 li r0, 3
- MAC format traversal tests nonzero remaining bytes with decrement in body: 51.56391%; src 0x30c base 0x214 insns 195/133; --- replace mine 47:49 base 47:49;   M   47 beq 568;   M   48 li r0, 3
Retained best candidate

Final src/scene/setting/ATERM residuals (each original residual has at least three successful, distinct source trials above):
| Function | objdiff % | Instructions | Evidence / remaining reason |
|---|---:|---|---|
| ATERM_814021BC | 96.61688 | 154/154 | network/settings view allocation and initial base-address scheduling |
| ATERM_8140276C | 98.965515 | 174/174 | record/flag register allocation; fallback reset now follows target |
| ATERM_81402A24 | 81.04943 | 290/263 | scan frame, descriptor-view scheduling and MAC-loop unrolling |
| ATERM_81402E40 | 99.791664 | 96/96 | argument move ordering plus cr1 branch normalization |
| ATERM_81402FC0 | 100.0 | 135/135 | objdiff exact; gate/ctxdiff cr1 branch normalization differs by preceding-function address delta |
| ATERM_814031DC | 90.766914 | 129/133 | MAC loop uses explicit terminal break; original uses CTR and different temporaries |
| ATERM_814033F0 | 98.649635 | 137/137 | option flag/cursor register allocation and span addition scheduling |
| ATERM_814036D8 | 99.08064 | 124/124 | key/text/output view register allocation and stream advancement order |
| ATERM_814038C8 | 83.25657 | 970/951 | protocol frame, loop scheduling and option/authentication block allocation |
| ATERMi_AutoConfigThread | 94.75 | 40/40 | socket result/state arithmetic register choices |
| ATERM_81404844 | 95.1453 | 116/117 | wrap loop setup/control and saved-register allocation |
| ATERM_81404A18 | 99.09091 | 121/121 | unwrap result/pass/block register allocation |
| ATERM_81404BFC | 98.75746 | 268/268 | initial key byte-load ordering and AES-128 substitution register allocation |
| ATERM_8140502C | 99.42029 | 138/138 | round-reversal index and swap register allocation |
| ATERM_81405254 | 54.959408 | 263/271 | AES round XOR scheduling and intermediate stack lifetimes |
| ATERM_81405690 | 52.671585 | 263/271 | inverse AES round XOR scheduling and intermediate stack lifetimes |
| ATERM_81405ACC | 88.583336 | 139/144 | input copy loop guards/index scheduling |
| ATERMi_ApConfigStart | 99.805824 | 103/103 | first clock conversion temporary r0/r6 cycle |
| ATERMi_ApConfigEnd | 99.4186 | 129/129 | alarm callback/clock operand setup order |
| ATERMi_ApConfigGetState | 99.42857 | 35/35 | clock conversion temporary r0/r6 cycle |

Final data byte audit (no padding or address-pinned objects added):
- .bss: mine 8144, original 8160 bytes; prefix mismatches 0/8144.
- .rodata: mine 10280, original 10280 bytes; prefix mismatches 0/10280.
- .data: mine 280, original 280 bytes; prefix mismatches 0/280.
- .sdata2: mine 7, original 8 bytes; prefix mismatches 0/7.
- .sdata: mine 53, original 56 bytes; prefix mismatches 0/53.
- .sbss: mine 84, original 80 bytes; prefix mismatches 0/80.
Packet parser raw bytes identical: True. Raw SHA-256 mine 91a60a7585553b8702d6f6ff83d5a91eedfd3cbaf3a04fb25501c637a6f84acd, original 91a60a7585553b8702d6f6ff83d5a91eedfd3cbaf3a04fb25501c637a6f84acd. Raw-byte equality does not assert linker relocation identity. The gate instruction count remains authoritative in this report.

Final src/scene/setting/AOSS residuals (each original residual has at least three successful, distinct source trials above):
| Function | objdiff % | Instructions | Evidence / remaining reason |
|---|---:|---|---|
| AOSS_Init_old | 28.1875 | 1512/1584 | initialization branch layout, wait/receive loops and stack allocation |
| AOSS_81400830 | 87.78505 | 317/321 | RC4 cursor publication, CRC-loop guards and register allocation |
| AOSS_81400E0C | 95.26316 | 191/190 | network scalar loop guards and switch/register scheduling |
| AOSS_814013AC | 96.32456 | 114/114 | response cursor, flags and config-view lifetimes and load ordering |
| AOSS_81401574 | 98.87597 | 129/129 | three pointer-register allocation cycle |
| AOSS_81401778 | 77.92308 | 273/273 | hello key/nonce stack fields and stream/CRC register lifetimes |
| AOSS_81401C9C | 83.53425 | 76/73 | KSA save/restore and initialization/swap index scheduling |
| AOSS_81401E80 | 92.72109 | 146/147 | half-buffer XOR guard and loop/allocation lifetimes |

Final data byte audit (no padding or address-pinned objects added):
- .bss: mine 3496, original 3496 bytes; prefix mismatches 0/3496.
- .data: mine 364, original 368 bytes; prefix mismatches 0/364.
- .sdata2: mine 8, original 8 bytes; prefix mismatches 0/8.
- .sdata: mine 24, original 24 bytes; prefix mismatches 0/24.
- .sbss: mine 32, original 32 bytes; prefix mismatches 0/32.

Data is not claimed 100%: ATERM switch-table relocation correspondence and anonymous small-data mappings remain below complete objdiff coverage; AOSS has unresolved small-BSS correspondence. Original extracted alignment tails are not synthesized.

ATERM association MAC formatting native check passed: normalized BSSID, descending address order and uppercase colon-separated strings, three address pairs. Buffers are exposed only in the native test wrapper. The final source uses a terminal break after the sixth byte, eliminating the compiler double unroll; 129/133 instructions remain versus target CTR loop.
ATERM full clean gate before MAC improvement commit:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 4528/19204 data 18448/18864 functions 7/26 fuzzy 89.3258 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 6/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match None
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 38.88889
[src/scene/setting/ATERM]   section .sdata size 56 match None
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 89.32577
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
[src/scene/setting/ATERM]   below 100: ATERM_8140502C 99.42029
[src/scene/setting/ATERM]   below 100: ATERM_81405254 54.959408
[src/scene/setting/ATERM]   below 100: ATERM_81405690 52.671585
[src/scene/setting/ATERM]   below 100: ATERM_81405ACC 88.583336
[src/scene/setting/ATERM]   below 100: ATERMi_ApConfigStart 99.805824
[src/scene/setting/ATERM]   below 100: ATERMi_ApConfigEnd 99.4186
[src/scene/setting/ATERM]   below 100: ATERMi_ApConfigGetState 99.42857
[src/scene/setting/ATERM] baseline: code 1648/19204 data 18448 functions 6 fuzzy 82.5403
regressions vs baseline: 0
global matched_code_percent: 82.45576 -> 82.60614
global fuzzy_match_percent: 95.09687 -> 95.14824
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.46201 -> 89.46201
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```
