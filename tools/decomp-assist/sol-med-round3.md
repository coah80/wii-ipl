# ATERM and AOSS third matching pass

Baseline: ATERM 5/26, code 1108/19204, data 18448/18864; AOSS 8/21, code 2764/16192, data 3896/3928.
Pool first: ATERM strings identical.

ATERMi_ApConfigGetState initial 99.42857%
- reciprocal operand first in multiply-high: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000
- reciprocal declared before clock sample: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
- single tick divisor expression: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000
Retained best candidate

ATERMi_AutoConfigThread initial 94.75%
- result loaded into progress before state calculation: 91.45%; src 0xa0 base 0xa0 insns 40/40; diffs 7: [20, 22, 23, 28, 29, 30, 31];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- state equality uses result-local assignment: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- completed state written directly to progress before global: 91.25%; src 0xa0 base 0xa0 insns 40/40; diffs 9: [20, 21, 22, 23, 24, 26, 28, 29, 30];     20 M nor r0, r3, r0;        B nor r3, r3, r0
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- tick divisor expressed as bus clock divided by 4000: 84.71429%; src 0x84 base 0x8c insns 33/35; --- replace mine 13:14 base 13:14;   M   13 b 48;   B   13 b 56
- ordinary OS ticks to milliseconds conversion: 84.71429%; src 0x84 base 0x8c insns 33/35; --- replace mine 13:14 base 13:14;   M   13 b 48;   B   13 b 56
- signed native clock divisor: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000
Retained best candidate

ATERMi_AutoConfigThread initial 94.75%
- ordinary completion state conditional: 85.25%; src 0x9c base 0xa0 insns 39/40; --- replace mine 18:21 base 18:22;   M   18 addi r0, r31, -1;   M   19 li r5, -1
- boolean completion state subtraction: 72.1%; src 0x9c base 0xa0 insns 39/40; --- replace mine 18:19 base 18:21;   M   18 addi r0, r31, -1;   B   18 addi r3, r31, -1
- result snapshot between mask and shift: 91.45%; src 0xa0 base 0xa0 insns 40/40; diffs 7: [20, 22, 23, 28, 29, 30, 31];     20 M nor r0, r3, r0;        B nor r3, r3, r0
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- wide clock product with explicit high word: 90.42857%; src 0x98 base 0x8c insns 38/35; --- replace mine 13:14 base 13:14;   M   13 b 68;   B   13 b 56
- divisor expressed as signed 64-bit temporary: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
- clock read and shifted into separate lifetime: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
Retained best candidate

ATERMi_AutoConfigThread initial 94.75%
- deadline set after state construction: 91.625%; src 0xa0 base 0xa0 insns 40/40; diffs 6: [20, 22, 23, 26, 28, 29];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- signed equality mask and state: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- progress constructed from computed state and saved result: compile failed
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- microsecond conversion multiplier unsigned long: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
- elapsed quotient assigned back to time: compile failed
- remaining time directly from signed quotient: 97.71429%; src 0x8c base 0x8c insns 35/35; diffs 4: [17, 18, 20, 25];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
Retained best candidate

ATERMi_AutoConfigThread initial 94.75%
- progress state calculation contains mask expression directly: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- progress result snapshot declared after equality mask: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- state calculation before deadline and callback fields: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- signed reciprocal temporary: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
- unsigned long clock temporary: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
- temporary divisor narrowed after wide multiply: compile failed
- clock conversion uses native signed time cast: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
- clock reciprocal multiplication explicitly unsigned: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
- remaining delay subtracts signed elapsed scalar: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
Retained best candidate

ATERMi_AutoConfigThread initial 94.75%
- equality mask written using De Morgan conjunction: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- two signed differences retained before mask: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- progress fields filled before global state publication: 91.45%; src 0xa0 base 0xa0 insns 40/40; diffs 7: [20, 22, 23, 28, 29, 30, 31];     20 M nor r0, r3, r0;        B nor r3, r3, r0
Retained best candidate

ATERM_81402E40 initial 99.791664%
- payload header alias names cleared storage: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- encryption key read through const byte pointer: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- memset result names initialized payload header: 97.5%; src 0x180 base 0x180 insns 96/96; diffs 12: [5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 47, 52];      5 M mr r30, r3;        B mr r27, r5
- checksum initialized after payload clear: 96.34375%; src 0x180 base 0x180 insns 96/96; diffs 9: [9, 10, 11, 12, 13, 14, 15, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- byte extent signed for checksum traversal: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
Retained best candidate

ATERMi_ApConfigStart block reconstruction: inclusive busy-state checks, globals stored in target order, OSCreateThread reads the configured stack size after allocation callback. 104/103 -> 103/103 instructions; remaining six differences swap clock/reciprocal base registers.

ATERMi_ApConfigStart initial 99.70874%
- clock operand before reciprocal at both timer conversions: 97.76699%; src 0x19c base 0x19c insns 103/103; diffs 7: [48, 49, 51, 75, 76, 77, 78];     48 M lwz r6, 0xf8(r30);        B lwz r0, 0xf8(r30)
- clock pointer sampled through const object pointer: 95.485435%; src 0x19c base 0x19c insns 103/103; diffs 45: [4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23];      4 M mr r31, r3;        B stw r30, 0x18(r1)
- reciprocal scalar shared between conversions: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
- time arithmetic named inside first conversion scope: 99.805824%; src 0x19c base 0x19c insns 103/103; diffs 3: [48, 49, 51];     48 M lwz r6, 0xf8(r30);        B lwz r0, 0xf8(r30)
Retained best candidate

ATERMi_ApConfigGetState inline tick divisor helper: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000;     16 M lis r6, 0x1062;        B lis r5, 0x1062;     17 M lwz r0, 0xf8(r5);        B lwz r0, 0xf8(r6);     18 M addi r6, r6, 0x4dd3;        B addi r6, r5, 0x4dd3; 

ATERMi_ApConfigGetState inline clock argument helper: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6);     18 M addi r0, r5, 0x4dd3;        B addi r6, r5, 0x4dd3;     20 M srwi r6, r6, 2;        B srwi r0, r0, 2; 

ATERMi_ApConfigGetState inline milliseconds conversion helper: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000;     16 M lis r6, 0x1062;        B lis r5, 0x1062;     17 M lwz r0, 0xf8(r5);        B lwz r0, 0xf8(r6);     18 M addi r6, r6, 0x4dd3;        B addi r6, r5, 0x4dd3; 

ATERMi_ApConfigStart initial 99.805824%
- first conversion clock inlined but reciprocal retained: 99.805824%; src 0x19c base 0x19c insns 103/103; diffs 3: [48, 49, 51];     48 M lwz r6, 0xf8(r30);        B lwz r0, 0xf8(r30)
- first conversion reciprocal inlined but clock retained: 99.805824%; src 0x19c base 0x19c insns 103/103; diffs 3: [48, 49, 51];     48 M lwz r6, 0xf8(r30);        B lwz r0, 0xf8(r30)
- timer divisor scalar separate from elapsed quotient: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
- timer clock division assigned before multiplication: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
- first timer named 64-bit divisor: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
Retained best candidate

ATERM_81404844 initial 92.62393%
- both counter-product operands explicitly signed 64 bit: 92.62393%; src 0x1bc base 0x1d4 insns 111/117; --- replace mine 8:13 base 8:13;   M    8 mr r29, r3;   M    9 mr r22, r4
- counter storage declared before IV storage: 92.71795%; src 0x1bc base 0x1d4 insns 111/117; --- replace mine 8:11 base 8:12;   M    8 mr r29, r3;   M    9 mr r22, r4
- IV initialized by normal array initializer: 89.89744%; src 0x1bc base 0x1d4 insns 111/117; --- replace mine 6:13 base 6:13;   M    6 lwz r8, 0(0);   M    7 lwz r0, 0(0)
Retained best candidate

ATERM_81404844 initial 92.71795%
- RFC3394 counter uses unsigned 64-bit arithmetic: 98.65812%; src 0x1d4 base 0x1d4 insns 117/117; diffs 28: [8, 9, 10, 11, 12, 18, 19, 27, 28, 29, 30, 36, 37, 38, 39, 41, 42, 43, 45, 48];      8 M mr r29, r3;        B mr r25, r3
- counter product computed once for each wrapping pass: 92.71795%; src 0x1bc base 0x1d4 insns 111/117; --- replace mine 8:11 base 8:12;   M    8 mr r29, r3;   M    9 mr r22, r4
- equal IV words assigned from last to first: 92.73505%; src 0x1bc base 0x1d4 insns 111/117; --- replace mine 8:11 base 8:11;   M    8 mr r29, r3;   M    9 mr r22, r4
Retained best candidate

ATERM_81404844 initial 98.65812%
- unsigned product outside inner block traversal: 98.65812%; src 0x1d4 base 0x1d4 insns 117/117; diffs 28: [8, 9, 10, 11, 12, 18, 19, 27, 28, 29, 30, 36, 37, 38, 39, 41, 42, 43, 45, 48];      8 M mr r29, r3;        B mr r25, r3
- inner block index has function scope: 98.65812%; src 0x1d4 base 0x1d4 insns 117/117; diffs 28: [8, 9, 10, 11, 12, 18, 19, 27, 28, 29, 30, 36, 37, 38, 39, 41, 42, 43, 45, 48];      8 M mr r29, r3;        B mr r25, r3
- equal IV words initialized in descending order: 98.67522%; src 0x1d4 base 0x1d4 insns 117/117; diffs 26: [8, 9, 10, 18, 19, 27, 28, 29, 30, 36, 37, 38, 39, 41, 42, 43, 45, 48, 54, 58];      8 M mr r29, r3;        B mr r25, r3
- destination byte view expressed at copies: 98.82906%; src 0x1d4 base 0x1d4 insns 117/117; diffs 24: [9, 10, 11, 12, 18, 19, 27, 28, 29, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60];      9 M mr r22, r4;        B mr r23, r4
- byte views initialized after key expansion: 99.0%; src 0x1d4 base 0x1d4 insns 117/117; diffs 20: [11, 12, 18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     11 M stw r0, 8(r1);        B stw r0, 0xc(r1)
Retained best candidate

ATERM_81404844 initial 99.0%
- descending IV stores with delayed byte views: 99.0171%; src 0x1d4 base 0x1d4 insns 117/117; diffs 18: [18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     18 M srwi r29, r5, 3;        B srwi r27, r5, 3
- outer pass uses do-while form: 99.0%; src 0x1d4 base 0x1d4 insns 117/117; diffs 20: [11, 12, 18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     11 M stw r0, 8(r1);        B stw r0, 0xc(r1)
- block cursor advanced explicitly within inner traversal: 99.0%; src 0x1d4 base 0x1d4 insns 117/117; diffs 20: [11, 12, 18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     11 M stw r0, 8(r1);        B stw r0, 0xc(r1)
- named output block retained across encryption: 99.0%; src 0x1d4 base 0x1d4 insns 117/117; diffs 20: [11, 12, 18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     11 M stw r0, 8(r1);        B stw r0, 0xc(r1)
Retained best candidate

ATERM_81404844 initial 99.0171%
- inner block traversal follows explicit target basic blocks: 99.0171%; src 0x1d4 base 0x1d4 insns 117/117; diffs 18: [18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     18 M srwi r29, r5, 3;        B srwi r27, r5, 3
- outer pass follows explicit target back edge: 99.0171%; src 0x1d4 base 0x1d4 insns 117/117; diffs 18: [18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     18 M srwi r29, r5, 3;        B srwi r27, r5, 3
- both wrapping loops follow explicit target blocks: 99.0171%; src 0x1d4 base 0x1d4 insns 117/117; diffs 18: [18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     18 M srwi r29, r5, 3;        B srwi r27, r5, 3
- encryption round count retains signed return type: 99.0171%; src 0x1d4 base 0x1d4 insns 117/117; diffs 18: [18, 19, 27, 36, 37, 38, 39, 41, 42, 43, 45, 54, 58, 60, 99, 101, 103, 104];     18 M srwi r29, r5, 3;        B srwi r27, r5, 3
Retained best candidate

ATERM_81404A18 initial 75.82645%
- RFC counter product uses unsigned 64-bit representation: 75.41322%; src 0x1d8 base 0x1e4 insns 118/121; --- replace mine 8:13 base 8:14;   M    8 mr r29, r3;   M    9 mr r21, r4
- IV stores follow descending target order: 75.82645%; src 0x1c0 base 0x1e4 insns 112/121; --- replace mine 8:13 base 8:14;   M    8 mr r29, r3;   M    9 mr r21, r4
- byte views named after key expansion: 76.15703%; src 0x1c0 base 0x1e4 insns 112/121; --- replace mine 8:9 base 8:9;   M    8 mr r24, r3;   B    8 mr r23, r3
Retained best candidate

ATERM_81404A18 target block reconstruction: unsigned 64-bit RFC counter, signed-positive inner condition, XOR before low-block copy, descending IV stores, explicit successful-result branch. 112/121 -> 121/121, 87.214874%.

ATERM_81404A18 initial 87.214874%
- output block address evaluated after counter assignment: 99.09091%; src 0x1e4 base 0x1e4 insns 121/121; diffs 20: [12, 20, 21, 29, 39, 40, 42, 44, 46, 49, 50, 51, 56, 67, 94, 98, 102, 103, 113, 114];     12 M li r26, 1;        B li r24, 1
- counter high and low words stored explicitly: 90.47108%; src 0x1e4 base 0x1e4 insns 121/121; diffs 31: [12, 20, 21, 29, 39, 40, 42, 44, 46, 49, 50, 51, 54, 55, 56, 57, 58, 59, 60, 61];     12 M li r26, 1;        B li r24, 1
- unwrapping pass product outside block loop: 87.214874%; src 0x1e4 base 0x1e4 insns 121/121; diffs 36: [12, 20, 21, 29, 39, 40, 42, 44, 46, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59];     12 M li r26, 1;        B li r24, 1
Retained best candidate

ATERM_814036D8 initial 87.0%
- security modes dispatched in original basic-block order: 98.98387%; src 0x1f0 base 0x1f0 insns 124/124; diffs 25: [33, 35, 36, 37, 43, 58, 59, 64, 65, 70, 71, 75, 76, 77, 78, 81, 82, 83, 84, 88];     33 M addi r23, r26, 0x164;        B addi r24, r26, 0x164
- 26-character key handled before 16-character raw key: 87.09677%; src 0x1e4 base 0x1f0 insns 121/124; --- replace mine 14:24 base 14:16;   M   14 bne 36;   M   15 addi r3, r25, 0
- output key cursor advances before source cursor: 87.0%; src 0x1e4 base 0x1f0 insns 121/124; --- replace mine 14:24 base 14:16;   M   14 bne 36;   M   15 addi r3, r25, 0
Retained best candidate

ATERM_814036D8 initial 98.98387%
- key-length blocks follow target source order: 99.08064%; src 0x1f0 base 0x1f0 insns 124/124; diffs 21: [33, 35, 36, 37, 43, 58, 59, 64, 65, 70, 71, 76, 77, 82, 83, 88, 89, 94, 95, 96];     33 M addi r23, r26, 0x164;        B addi r24, r26, 0x164
- source key named before output key: 98.98387%; src 0x1f0 base 0x1f0 insns 124/124; diffs 25: [33, 35, 36, 37, 43, 58, 59, 64, 65, 70, 71, 75, 76, 77, 78, 81, 82, 83, 84, 88];     33 M addi r23, r26, 0x164;        B addi r24, r26, 0x164
- fixed key text view named before key traversal: 98.5%; src 0x1f0 base 0x1f0 insns 124/124; diffs 26: [33, 35, 36, 37, 43, 48, 58, 59, 64, 65, 70, 71, 75, 76, 77, 78, 81, 82, 83, 84];     33 M addi r23, r26, 0x164;        B addi r24, r26, 0x164
- key index initialized before byte cursors: 98.98387%; src 0x1f0 base 0x1f0 insns 124/124; diffs 25: [33, 35, 36, 37, 43, 58, 59, 64, 65, 70, 71, 75, 76, 77, 78, 81, 82, 83, 84, 88];     33 M addi r23, r26, 0x164;        B addi r24, r26, 0x164
Retained best candidate

ATERMi_ApConfigEnd block reconstruction: snapshot state after cancellation flag, actual 500 ms join alarm replaces erroneous reciprocal constant. 119/129 -> 125/129; remaining save/restore helpers, stack ordering and clock operand registers.

ATERMi_ApConfigEnd initial 93.91473%
- received message scalars declared before queue buffers: 93.94574%; src 0x1f4 base 0x204 insns 125/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
- progress structure has function scope: 93.91473%; src 0x1f4 base 0x204 insns 125/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
- join alarm tick computation names local clock before reciprocal: 93.91473%; src 0x1f4 base 0x204 insns 125/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
Retained best candidate

ATERMi_AutoConfigThread initial 94.75%
- global state receives equality expression directly: 94.0%; src 0xa0 base 0xa0 insns 40/40; diffs 9: [20, 21, 22, 23, 24, 26, 28, 29, 30];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- remaining-time field stored before state: 94.45%; src 0xa0 base 0xa0 insns 40/40; diffs 5: [20, 22, 23, 29, 30];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- mask shift and completed-state addition named separately: 94.0%; src 0xa0 base 0xa0 insns 40/40; diffs 9: [20, 21, 22, 23, 24, 26, 28, 29, 30];     20 M nor r0, r3, r0;        B nor r3, r3, r0
Retained best candidate

ATERM_8140502C initial 42.355072%
- reverse round order with signed key-word indices: 45.615944%; src 0x290 base 0x228 insns 164/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0
- transformed rounds address words four through seven: 43.5%; src 0x27c base 0x228 insns 159/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0
- inverse MixColumns XOR combines balanced pairs: no source change; skipped
Retained best candidate

ATERM_8140502C target block reconstruction: named AES substitution/inverse table views, balanced low-to-high byte XOR pairs, integer reversal indices, transformed round words 4..7, counted forward round loop. 85.9058%; src 0x228 base 0x228 insns 138/138

ATERM_8140502C initial 85.9058%
- table views initialized after key reversal: compile failed
- table views declared in reverse direction: 86.92029%; src 0x228 base 0x228 insns 138/138; diffs 37: [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25];      6 M bl 0;        B lis r30, 0
- reversal compares low index before high using for loop: 85.9058%; src 0x228 base 0x228 insns 138/138; diffs 65: [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25];      6 M bl 0;        B lis r30, 0
Retained best candidate

ATERM_8140502C initial 86.92029%
- table views scoped to inverse column conversion: 98.63043%; src 0x228 base 0x228 insns 138/138; diffs 26: [10, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34];     10 M mr r5, r31;        B mr r4, r31
- reversal condition explicitly compares upper index to lower: 86.95652%; src 0x228 base 0x228 insns 138/138; diffs 37: [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25];      6 M bl 0;        B lis r30, 0
- table views scoped after reversal with upper-index comparison: 98.73913%; src 0x228 base 0x228 insns 138/138; diffs 24: [10, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34];     10 M mr r5, r31;        B mr r4, r31
Retained best candidate

ATERM_8140502C initial 98.73913%
- table view initializations follow original assembly order: 97.753624%; src 0x228 base 0x228 insns 138/138; diffs 52: [10, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34];     10 M mr r5, r31;        B mr r4, r31
- round-key reversal expressed with word indices: 83.804344%; src 0x22c base 0x228 insns 139/138; --- replace mine 4:6 base 4:5;   M    4 lis r31, 0;   M    5 addi r31, r31, 0
- indexed key reversal uses ordinary counted for loop: 83.76811%; src 0x22c base 0x228 insns 139/138; --- replace mine 4:6 base 4:5;   M    4 lis r31, 0;   M    5 addi r31, r31, 0
Retained best candidate

ATERM_8140502C initial 98.73913%
- table views declared before target-order assignment: 98.91304%; src 0x228 base 0x228 insns 138/138; diffs 20: [10, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34];     10 M mr r5, r31;        B mr r4, r31
- swap word has scope shared by reversal iterations: 98.73913%; src 0x228 base 0x228 insns 138/138; diffs 24: [10, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34];     10 M mr r5, r31;        B mr r4, r31
- shared swap word and target table assignment order: 98.91304%; src 0x228 base 0x228 insns 138/138; diffs 20: [10, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34];     10 M mr r5, r31;        B mr r4, r31
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- clock and reciprocal declared before reciprocal-first assignments: compile failed
- reciprocal and clock declared before clock-first assignment: compile failed
- tick divisor computed into predeclared scalar: compile failed
Retained best candidate

ATERM_8140502C initial 98.91304%
- each swapped key word uses its own lexical temporary: 99.42029%; src 0x228 base 0x228 insns 138/138; diffs 13: [11, 12, 15, 16, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r7, r3, 2;        B slwi r8, r3, 2
- first round cursor established before key-expansion call: 94.789856%; src 0x228 base 0x228 insns 138/138; diffs 31: [0, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 15, 16, 18, 19, 20, 21, 23, 24, 25];      0 M stwu r1, -0x20(r1);        B stwu r1, -0x10(r1)
- round cursors assigned after their declarations: 98.91304%; src 0x228 base 0x228 insns 138/138; diffs 20: [10, 13, 15, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34];     10 M mr r5, r31;        B mr r4, r31
Retained best candidate

ATERM_8140502C initial 99.42029%
- reversal indices advance after first word is read: 99.42029%; src 0x228 base 0x228 insns 138/138; diffs 13: [11, 12, 15, 16, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r7, r3, 2;        B slwi r8, r3, 2
- reversal indices advance after first word pair is swapped: 99.42029%; src 0x228 base 0x228 insns 138/138; diffs 13: [11, 12, 15, 16, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r7, r3, 2;        B slwi r8, r3, 2
- reversal indices advance after all words are swapped: 99.42029%; src 0x228 base 0x228 insns 138/138; diffs 13: [11, 12, 15, 16, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r7, r3, 2;        B slwi r8, r3, 2
Retained best candidate

ATERM_81405254 initial 34.23247%
- paired AES rounds following original loop and final branch: 41.169743%; src 0x45c base 0x43c insns 279/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- paired AES rounds with left-associated table XOR: 28.512915%; src 0x45c base 0x43c insns 279/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- initial byte assembly uses XOR for all disjoint byte lanes: 36.01845%; src 0x3c4 base 0x43c insns 241/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
Retained best candidate

ATERM_81405690 initial 34.64945%
- paired AES rounds following original loop and final branch: 34.512917%; src 0x460 base 0x43c insns 280/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- paired AES rounds with left-associated table XOR: 39.645756%; src 0x460 base 0x43c insns 280/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- initial byte assembly uses XOR for all disjoint byte lanes: 36.461254%; src 0x3d4 base 0x43c insns 245/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
Retained best candidate

ATERM_814031DC reconstructed original hex-byte helper return length and two 32-byte text buffers: 54.789474%; src 0x170 base 0x214 insns 92/133

ATERM_814031DC initial 85.90225%
- MAC addresses streamed through byte pointer views: 85.90225%; src 0x1f4 base 0x214 insns 125/133; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x70(r1);   B    0 stwu r1, -0x60(r1)
- MAC text byte count is signed loop index: 85.90225%; src 0x1f4 base 0x214 insns 125/133; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x70(r1);   B    0 stwu r1, -0x60(r1)
- MAC ordering tested before binding compare result: 85.90225%; src 0x1f4 base 0x214 insns 125/133; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x70(r1);   B    0 stwu r1, -0x60(r1)
Retained best candidate

ATERM_814031DC initial 85.90225%
- hex encoding follows original cursor and byte-count blocks: 92.6391%; src 0x214 base 0x214 insns 133/133; diffs 71: [49, 50, 51, 52, 53, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69];     49 M addi r7, r1, 0x18;        B addi r5, r1, 8
- original cursor blocks with byte streams: 96.85714%; src 0x214 base 0x214 insns 133/133; diffs 45: [49, 50, 51, 55, 56, 57, 59, 61, 62, 63, 65, 66, 67, 71, 72, 75, 76, 77, 78, 79];     49 M addi r6, r1, 8;        B addi r5, r1, 8
- cursor difference counted as signed encoded length: 92.6391%; src 0x214 base 0x214 insns 133/133; diffs 71: [49, 50, 51, 52, 53, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69];     49 M addi r7, r1, 0x18;        B addi r5, r1, 8
Retained best candidate

ATERM_81405254 initial 41.169743%
- final S-box table has a named pointer view: 50.214024%; src 0x420 base 0x43c insns 264/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- final byte lanes combine with XOR: 42.671585%; src 0x47c base 0x43c insns 287/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- final key words are XOR left operands: no source change; skipped
Retained best candidate

ATERM_81405690 initial 39.645756%
- final S-box table has a named pointer view: 48.579334%; src 0x424 base 0x43c insns 265/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- final byte lanes combine with XOR: 40.2214%; src 0x480 base 0x43c insns 288/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- final key words are XOR left operands: no source change; skipped
Retained best candidate

ATERM_814031DC initial 96.85714%
- nibble mask and buffer declarations follow original stack order: 97.69173%; src 0x214 base 0x214 insns 133/133; diffs 45: [49, 50, 51, 55, 56, 57, 59, 61, 62, 63, 65, 66, 67, 71, 72, 75, 76, 77, 78, 79];     49 M addi r6, r1, 8;        B addi r5, r1, 8
- MAC format traversals have independent byte and text views: 96.90225%; src 0x214 base 0x214 insns 133/133; diffs 44: [50, 51, 57, 59, 61, 62, 63, 65, 66, 67, 71, 72, 75, 76, 77, 78, 79, 80, 82, 83];     50 M addi r7, r1, 0x18;        B addi r8, r1, 0x38
- original stack buffers with independent format traversals: 97.74436%; src 0x214 base 0x214 insns 133/133; diffs 44: [50, 51, 57, 59, 61, 62, 63, 65, 66, 67, 71, 72, 75, 76, 77, 78, 79, 80, 82, 83];     50 M addi r7, r1, 0x38;        B addi r8, r1, 0x38
Retained best candidate

ATERM_81402FC0 initial 68.577774%
- u32 checksum and nullable option iterator mirror original branches: 69.48148%; src 0x228 base 0x21c insns 138/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- delete mine 15:16 base 16:16
- iterator with signed option and selected mode words: 71.111115%; src 0x224 base 0x21c insns 137/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- delete mine 15:16 base 16:16
- original iterator with separate rejection of authentication flags: 72.48148%; src 0x228 base 0x21c insns 138/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- delete mine 15:16 base 16:16
Retained best candidate

ATERM_814033F0 initial 67.39416%
- nullable option iterator and signed byte count hex traversal: 71.350365%; src 0x22c base 0x224 insns 139/137; --- replace mine 5:6 base 5:6;   M    5 addi r30, r3, 8;   B    5 addi r29, r3, 8
- nullable iterator with signed option lengths: 71.350365%; src 0x22c base 0x224 insns 139/137; --- replace mine 5:6 base 5:6;   M    5 addi r30, r3, 8;   B    5 addi r29, r3, 8
- nullable iterator with pointer termination for hex bytes: 71.9708%; src 0x22c base 0x224 insns 139/137; --- replace mine 5:6 base 5:6;   M    5 addi r30, r3, 8;   B    5 addi r29, r3, 8
Retained best candidate

ATERM_81402FC0 initial 72.48148%
- option iteration exits on nullable value at loop bottom: 94.703705%; src 0x21c base 0x21c insns 135/135; diffs 27: [8, 9, 10, 11, 12, 13, 14, 15, 18, 23, 88, 92, 96, 100, 101, 102, 103, 104, 105, 106];      8 M bl 0;        B li r31, 0
- bottom iterator initializes checksum before endian calls: 96.62963%; src 0x21c base 0x21c insns 135/135; diffs 19: [18, 23, 88, 92, 96, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113];     18 M bge -3611;        B bge -3647
- bottom iterator adds rounded option span before pointer: 94.703705%; src 0x21c base 0x21c insns 135/135; diffs 27: [8, 9, 10, 11, 12, 13, 14, 15, 18, 23, 88, 92, 96, 100, 101, 102, 103, 104, 105, 106];      8 M bl 0;        B li r31, 0
Retained best candidate

ATERM_814033F0 initial 71.9708%
- bottom nullable iterator and counted signed hex traversal: 91.60584%; src 0x22c base 0x224 insns 139/137; --- insert mine 7:7 base 7:8;   B    7 li r24, 0; --- replace mine 10:13 base 11:14
- bottom iterator result initialization before endian call: 93.50365%; src 0x22c base 0x224 insns 139/137; --- replace mine 11:12 base 11:12;   M   11 li r23, 0;   B   11 li r22, 0
- bottom iterator option span added before cursor: 91.60584%; src 0x22c base 0x224 insns 139/137; --- insert mine 7:7 base 7:8;   B    7 li r24, 0; --- replace mine 10:13 base 11:14
Retained best candidate

ATERM_81405ACC initial 55.54861%
- MD5 copy streams use independent input and buffer cursors: 73.78472%; src 0x230 base 0x240 insns 140/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:7 base 4:10
- copy streams compute fill count after bit counters update: 83.09028%; src 0x230 base 0x240 insns 140/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:5 base 4:11
- streaming copies initialize tail count before empty check: 75.138885%; src 0x230 base 0x240 insns 140/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:7 base 4:10
Retained best candidate

ATERM_81402FC0 initial 96.62963%
- option iterator emits exhaustion branch before decoded option: 99.62963%; src 0x21c base 0x21c insns 135/135; diffs 11: [18, 23, 88, 92, 96, 101, 108, 109, 110, 112, 113];     18 M bge -3611;        B bge -3647
- exhaustion first with signed full word option length: 99.92593%; src 0x21c base 0x21c insns 135/135; diffs 3: [18, 23, 112];     18 M bge -3611;        B bge -3647
- exhaustion first and commuted option pointer addition: 99.62963%; src 0x21c base 0x21c insns 135/135; diffs 11: [18, 23, 88, 92, 96, 101, 108, 109, 110, 112, 113];     18 M bge -3611;        B bge -3647
Retained best candidate

ATERM_814033F0 initial 93.50365%
- exhaustion first and signed forward byte iteration: 98.576645%; src 0x224 base 0x224 insns 137/137; diffs 36: [11, 13, 16, 28, 29, 34, 39, 47, 55, 60, 65, 66, 71, 72, 74, 75, 81, 82, 85, 86];     11 M li r23, 0;        B li r22, 0
- forward traversal with option length captured only in hex scope: 98.576645%; src 0x224 base 0x224 insns 137/137; diffs 36: [11, 13, 16, 28, 29, 34, 39, 47, 55, 60, 65, 66, 71, 72, 74, 75, 81, 82, 85, 86];     11 M li r23, 0;        B li r22, 0
- exhaustion first commuted span pointer addition: 98.576645%; src 0x224 base 0x224 insns 137/137; diffs 36: [11, 13, 16, 28, 29, 34, 39, 47, 55, 60, 65, 66, 71, 72, 74, 75, 81, 82, 85, 86];     11 M li r23, 0;        B li r22, 0
Retained best candidate

ATERM_81402FC0 initial 99.92593%
- commute rounded span addition after signed length promotion: 99.92593%; src 0x21c base 0x21c insns 135/135; diffs 3: [18, 23, 112];     18 M bge -3611;        B bge -3647
- capture rounded option size then add before cursor: 99.92593%; src 0x21c base 0x21c insns 135/135; diffs 3: [18, 23, 112];     18 M bge -3611;        B bge -3647
- explicit rounded span statement followed by cursor advance: 99.92593%; src 0x21c base 0x21c insns 135/135; diffs 3: [18, 23, 112];     18 M bge -3611;        B bge -3647
Retained best candidate

ATERM_814021BC initial 92.77922%
- query host ID before conversion on every readiness iteration: 66.90909%; src 0x264 base 0x268 insns 153/154; --- insert mine 7:7 base 7:9;   B    7 addi r30, r30, 0;   B    8 li r4, 0
- network context view retained for IP and interface settings: 66.90909%; src 0x264 base 0x268 insns 153/154; --- insert mine 7:7 base 7:9;   B    7 addi r30, r30, 0;   B    8 li r4, 0
- host readiness loop condition uses explicit host snapshot: 66.90909%; src 0x264 base 0x268 insns 153/154; --- insert mine 7:7 base 7:9;   B    7 addi r30, r30, 0;   B    8 li r4, 0
Retained best candidate

ATERM_81402FC0 initial 99.92593%
- advance option cursor before returning option value: 99.62963%; src 0x21c base 0x21c insns 135/135; diffs 9: [18, 23, 76, 77, 99, 103, 106, 109, 112];     18 M bge -3611;        B bge -3647
- unsigned rounded span before cursor: 99.92593%; src 0x21c base 0x21c insns 135/135; diffs 3: [18, 23, 112];     18 M bge -3611;        B bge -3647
- next option derived from current typed option: 99.92593%; src 0x21c base 0x21c insns 135/135; diffs 3: [18, 23, 112];     18 M bge -3611;        B bge -3647
Retained best candidate

ATERM_81402FC0 initial 99.92593%
- rounded option span advances integer packet address: 100.0%; src 0x21c base 0x21c insns 135/135; diffs 2: [18, 23];     18 M bge -3611;        B bge -3647
- signed packet address plus rounded option span: 100.0%; src 0x21c base 0x21c insns 135/135; diffs 2: [18, 23];     18 M bge -3611;        B bge -3647
- unsigned option address and span words: 100.0%; src 0x21c base 0x21c insns 135/135; diffs 2: [18, 23];     18 M bge -3611;        B bge -3647
Retained exact candidate

ATERM_81404BFC initial 74.36194%
- balanced key byte assembly and signed key size branches: compile failed
- balanced key reads with named substitution table: compile failed
- round exit before key cursor advance and balanced substitution XOR: compile failed
Retained best candidate

ATERM_81404BFC initial 74.36194%
- balanced key byte assembly and signed key size branches: 74.36194%; src 0x46c base 0x430 insns 283/268; --- replace mine 6:7 base 6:7;   M    6 cmplwi r5, 0x80;   B    6 cmpwi r5, 0x80
- balanced key reads with named substitution table: 74.41418%; src 0x420 base 0x430 insns 264/268; --- replace mine 5:47 base 5:38;   M    5 lbz r9, 1(r4);   M    6 lis r7, 0
- round exit before key cursor advance and balanced substitution XOR: 87.30224%; src 0x424 base 0x430 insns 265/268; --- replace mine 5:47 base 5:38;   M    5 lbz r9, 1(r4);   M    6 lis r7, 0
Retained best candidate

ATERM_81404BFC initial 87.30224%
- substitution views initialized separately in key size branches: 95.94403%; src 0x43c base 0x430 insns 271/268; --- replace mine 6:7 base 6:7;   M    6 cmplwi r5, 0x80;   B    6 cmpwi r5, 0x80
- key size comparisons promoted through signed scalar: 96.61567%; src 0x43c base 0x430 insns 271/268; --- delete mine 38:40 base 38:38;   M   38 xor r31, r30, r31;   M   39 xor r11, r12, r11
- branch-local tables initialized before round constants: 95.81343%; src 0x43c base 0x430 insns 271/268; --- replace mine 6:7 base 6:7;   M    6 cmplwi r5, 0x80;   B    6 cmpwi r5, 0x80
Retained best candidate

ATERM_8140276C initial 94.04023%
- separate successful return flag from discovered record flag: 95.41954%; src 0x2b8 base 0x2b8 insns 174/174; diffs 97: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 18, 20, 21, 22, 23, 24, 25, 26, 27];      5 M mr r24, r3;        B mr r23, r3
- record indices declared with initial loop values: 95.965515%; src 0x2b4 base 0x2b8 insns 173/174; --- replace mine 5:12 base 5:13;   M    5 mr r24, r3;   M    6 mr r25, r4
- AOSS scan flags have outer function scope: 95.41954%; src 0x2b8 base 0x2b8 insns 174/174; diffs 97: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 18, 20, 21, 22, 23, 24, 25, 26, 27];      5 M mr r24, r3;        B mr r23, r3
Retained best candidate

ATERM_81402A24 initial 76.20532%
- selected MAC format uses original byte and text cursor blocks: 81.988594%; src 0x404 base 0x41c insns 257/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- scan iteration error path uses explicit cancel branches: 80.89354%; src 0x408 base 0x41c insns 258/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- scan deadline conversion reads clock inside timer expression: 81.988594%; src 0x404 base 0x41c insns 257/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
Retained best candidate
ATERM_81405D0C MD5 word decode retains separate byte and word indices: 52.447224%; src 0xa58 base 0xb40 insns 662/720
ATERM_81405D0C step additions start with message word then state: 53.851387%; src 0xa50 base 0xb40 insns 660/720
ATERM_81405D0C indexed decode with word-first step additions: 52.447224%; src 0xa58 base 0xb40 insns 662/720
ATERM_81405D0C constant-word sum precedes state and boolean function: 43.020832%; src 0xa58 base 0xb40 insns 662/720

ATERM_814038C8 block reconstruction of all protocol states from target assembly. Option formats 8/16 bytes, payload header, broadcast destinations, separate key material, actual retries/deadlines and progress callbacks. 83.21661%

ATERM_814038C8 initial 83.21661%
- digest and length serialization follow original unrolled word stores: 85.12934%; src 0xef0 base 0xedc insns 956/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- digest context erasure uses eight byte streaming groups: 84.72871%; src 0xf10 base 0xedc insns 964/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- streaming digest erase and case-local reciprocal constants: 84.72871%; src 0xf10 base 0xedc insns 964/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
Retained best candidate
ATERM data initialized option pointer precedes shared-address and product globals at file end: 18448; [('.bss', 100.0), ('.data', None), ('.rodata', 100.0), ('.sbss', 38.88889), ('.sdata', None), ('.sdata2', 100.0), ('.text', 81.95084)]
ATERM data option pointer defined alongside initialized network globals: 10288; [('.bss', 83.33333), ('.data', None), ('.rodata', 100.0), ('.sbss', 38.88889), ('.sdata', None), ('.sdata2', 100.0), ('.text', 81.95084)]
ATERM data original SBSS declaration order with initialized option pointer last: 18448; [('.bss', 100.0), ('.data', None), ('.rodata', 100.0), ('.sbss', 27.777779), ('.sdata', None), ('.sdata2', 100.0), ('.text', 81.95084)]

ATERM_814021BC initial 92.77922%
- host ID comparison in while condition follows call evaluation order: 95.87013%; src 0x268 base 0x268 insns 154/154; diffs 52: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- host readiness condition with explicit inequality negation: 95.87013%; src 0x268 base 0x268 insns 154/154; diffs 52: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- direct readiness condition with settings pointer declared after clear: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
Retained best candidate

ATERM_81402A24 initial 81.988594%
- scan allocation sizes and callback-sensitive sizing follow target: 84.539925%; src 0x414 base 0x41c insns 261/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- record count published after descriptor copy and separate field cursors: 87.71483%; src 0x424 base 0x41c insns 265/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- original scan completion error and cancel branches: 87.988594%; src 0x42c base 0x41c insns 267/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
Retained best candidate

ATERM_81402A24 initial 87.988594%
- allocate extra record with constant byte term in target order: 88.273766%; src 0x428 base 0x41c insns 266/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- initialize only selection slot before progress fields are assigned: 88.828896%; src 0x418 base 0x41c insns 262/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- selected record view survives name and BSSID copies: 90.5019%; src 0x40c base 0x41c insns 259/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
Retained best candidate

ATERM_814038C8 initial 85.12934%
- protocol idle state belongs in original jump table: 85.12934%; src 0xef0 base 0xedc insns 956/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- idle state and digest erasure counts eight-byte groups: 84.72871%; src 0xf10 base 0xedc insns 964/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
- idle state uses a common post-switch back edge: 85.12934%; src 0xef0 base 0xedc insns 956/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x180(r1)
Retained best candidate

Native supplemental check of current extracted source: AES-128/192/256 NIST encrypt/decrypt and MD5 lengths 0/1/3/55/56/64/130 pass. All remaining ATERM functions have at least three distinct compiling source trials above. Packet parser is objdiff 100%; both cr1 branches have identical raw bytes 40840098/41850064, but ctxdiff/gate normalize them using absolute offsets and report two differences when preceding functions change size. No address pinning or tool modification used.
Retained initialized option pointer before actual shared-address/product definitions at file end to preserve BSS emission; original .sdata value order restored. .data/.sdata symbol mapping remains unscored by objdiff.

AOSS_81401DC0 initial 99.375%
- CRC each bit shifted before conditional polynomial XOR: 93.75%; src 0xc0 base 0xc0 insns 48/48; diffs 35: [1, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 24, 26];      1 M li r3, 0;        B li r5, 0
- CRC last step reuses running value after shift: 98.541664%; src 0xc0 base 0xc0 insns 48/48; diffs 8: [34, 36, 37, 38, 39, 41, 42, 43];     34 M srwi r0, r3, 1;        B srwi r3, r3, 1
- CRC step guards polynomial update with low bit comparison: 75.416664%; src 0xe0 base 0xc0 insns 56/48; --- replace mine 1:2 base 1:2;   M    1 li r3, 0;   B    1 li r5, 0
- CRC table index and row pointer increment in loop body: 93.75%; src 0xc0 base 0xc0 insns 48/48; diffs 35: [1, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 24, 26];      1 M li r3, 0;        B li r5, 0
Retained best candidate

AOSS_814020CC initial 81.65%
- socket startup failure returns before readiness loop: 78.03333%; src 0xe4 base 0xf0 insns 57/60; --- replace mine 3:5 base 3:6;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- readiness timeout tests incremented attempts in condition: 81.65%; src 0xe4 base 0xf0 insns 57/60; --- replace mine 3:5 base 3:6;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- sleep tick product uses named tick divisor initialized per iteration: 81.23333%; src 0xe4 base 0xf0 insns 57/60; --- replace mine 3:5 base 3:6;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained best candidate

AOSS_81401C9C initial 71.9315%
- RC4 mixer reloads schedule length and writes swapped slot first: 77.0685%; src 0x130 base 0x124 insns 76/73; --- replace mine 0:5 base 0:5;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
- RC4 index and state cursor have independent traversal lifetimes: 77.0685%; src 0x130 base 0x124 insns 76/73; --- replace mine 0:5 base 0:5;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
- RC4 accumulator updates precede key byte addition: 77.0%; src 0x130 base 0x124 insns 76/73; --- replace mine 0:5 base 0:5;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
Retained best candidate

AOSS_814001B4 initial 88.78481%
- message word decoded to signed promoted length: 88.025314%; src 0x12c base 0x13c insns 75/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- dispatch handlers return their final state directly: 83.27848%; src 0x124 base 0x13c insns 73/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- invalid message paths share a counted rejection branch: 63.708862%; src 0x104 base 0x13c insns 65/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained best candidate

AOSS_814013AC initial 91.70175%
- record lengths include header before cursor advance and runtime state updated: 91.7193%; src 0x1cc base 0x1c8 insns 115/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
- network option errors join parser result branch: 94.48245%; src 0x1d0 base 0x1c8 insns 116/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
- parser result source declaration precedes flags lifetime: 94.48245%; src 0x1d0 base 0x1c8 insns 116/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
Retained best candidate

AOSS_81401574 initial 92.558136%
- request length formed after network conversion and send length signed halfword: 98.87597%; src 0x204 base 0x204 insns 129/129; diffs 28: [5, 6, 9, 15, 24, 25, 33, 39, 42, 48, 51, 53, 54, 65, 68, 74, 76, 77, 79, 81];      5 M lwz r29, 0(0);        B lwz r27, 0(0)
- length view uses explicit record snapshot across header call: 98.333336%; src 0x200 base 0x204 insns 128/129; --- replace mine 5:7 base 5:7;   M    5 lwz r30, 0(0);   M    6 mr r27, r4
- request payload view initialized immediately after response clear: 96.93799%; src 0x204 base 0x204 insns 129/129; diffs 39: [5, 6, 9, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 33, 39, 42];      5 M lwz r29, 0(0);        B lwz r27, 0(0)
Retained best candidate

AOSS_81401E80 initial 91.80272%
- key mask XOR rereads initialized byte before key mixing: 91.80272%; src 0x244 base 0x24c insns 145/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
- packet half length uses ordinary signed division: 87.04082%; src 0x240 base 0x24c insns 144/147; --- replace mine 5:19 base 5:13;   M    5 srawi r0, r4, 1;   M    6 mr r28, r3
- mask and packet loops retain separate signed bulk limits: 92.82313%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
Retained best candidate

AOSS_814002F0 initial 85.058334%
- target early rejection exits and actual control flag field: 100.0%; src 0x1e0 base 0x1e0 insns 120/120; diffs 0: []
- response address view initialized after initial network decode: 98.291664%; src 0x1e0 base 0x1e0 insns 120/120; diffs 4: [62, 63, 64, 70];     62 M bl 0;        B addi r29, r27, 0x28
- operation flag initialized before mask evaluation: 96.958336%; src 0x1d4 base 0x1e0 insns 117/120; --- replace mine 14:15 base 14:15;   M   14 b 388;   B   14 b 400
Retained exact candidate

AOSS_81400E0C initial 77.778946%
- enable options use target network conversion and signed length validation: 78.43158%; src 0x2c0 base 0x2f8 insns 176/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8
- byte accumulation has explicit target signed unroll bounds: 81.710526%; src 0x2ec base 0x2f8 insns 187/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8
- tail accumulation advances pointer in byte load: 78.43158%; src 0x2c0 base 0x2f8 insns 176/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8
Retained best candidate

AOSS_813FFD68 initial 96.981735%
- output and config views initialized in reverse independent order: 96.981735%; src 0x364 base 0x36c insns 217/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- SSID validation uses decrementing while loops: 96.981735%; src 0x364 base 0x36c insns 217/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- validation count reuses signed string length view: 96.981735%; src 0x364 base 0x36c insns 217/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained best candidate

AOSS_81400830 initial 77.619934%
- decrypted payload replaces encrypted length/nonce header and CRC failures free after error store: 80.56698%; src 0x4c0 base 0x504 insns 304/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- RC4 input and output streams with state published before each swap: 82.90654%; src 0x4cc base 0x504 insns 307/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- CRC bulk loop uses original signed length guard and ceiling group count: 83.99377%; src 0x4ec base 0x504 insns 315/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
Retained best candidate

AOSS_81401778 initial 71.93407%
- hello carries original flag word and signed send length with explicit reserved byte: 75.15751%; src 0x448 base 0x444 insns 274/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- RC4 swaps reuse fetched source bytes instead of reloading after index stores: 77.53846%; src 0x440 base 0x444 insns 272/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- hello encryption traverses independent plaintext and response cursors: 76.25641%; src 0x440 base 0x444 insns 272/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
Retained best candidate

AOSS_Init_old initial 28.42298%
- target option sentinel comparisons use signed snapshots: 28.222853%; src 0x1794 base 0x18c0 insns 1509/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- initialization result assigned alongside packet count before first clear: 28.311237%; src 0x1790 base 0x18c0 insns 1508/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- poll timeout high and low words derived from same 64-bit sum: 28.35164%; src 0x178c base 0x18c0 insns 1507/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
Retained best candidate

AOSS data emission: original SBSS order list/config/name/connection/error/socket-started/response. MWCC emits these tentative definitions in reverse token order.
- reverse declaration order: 3896 matched data bytes

AOSS data emission: original SBSS order list/config/name/connection/error/socket-started/response. MWCC emits these tentative definitions in reverse token order.
- reverse declaration order: 3896 matched data bytes
- retain address pair before error and connection in source: 3896 matched data bytes
- reverse original real-object order: 3896 matched data bytes

AOSS_81401DC0 initial 99.375%
- compiler unrolls eight polynomial steps from bit loop: 24.833334%; src 0x40 base 0xc0 insns 16/48; --- insert mine 0:0 base 0:1;   B    0 li r0, 0x100; --- delete mine 1:3 base 2:2
- final polynomial branch publishes each final value directly: 86.875%; src 0xd0 base 0xc0 insns 52/48; --- replace mine 39:48 base 39:44;   M   39 beq 28;   M   40 srwi r0, r3, 1
- bit loop counts down with explicit common final value: 30.3125%; src 0x44 base 0xc0 insns 17/48; --- replace mine 1:2 base 1:2;   M    1 li r3, 0;   B    1 li r5, 0
Retained best candidate

AOSS_81401574 initial 98.87597%
- response packet view initialized after independent clear: 98.87597%; src 0x204 base 0x204 insns 129/129; diffs 28: [5, 6, 9, 15, 24, 25, 33, 39, 42, 48, 51, 53, 54, 65, 68, 74, 76, 77, 79, 81];      5 M lwz r29, 0(0);        B lwz r27, 0(0)
- header view begins after request data copy and manufacturer transform: 98.87597%; src 0x204 base 0x204 insns 129/129; diffs 28: [5, 6, 9, 15, 24, 25, 33, 39, 42, 48, 51, 53, 54, 65, 68, 74, 76, 77, 79, 81];      5 M lwz r29, 0(0);        B lwz r27, 0(0)
- allocated request declaration precedes response view: 98.87597%; src 0x204 base 0x204 insns 129/129; diffs 28: [5, 6, 9, 15, 24, 25, 33, 39, 42, 48, 51, 53, 54, 65, 68, 74, 76, 77, 79, 81];      5 M lwz r28, 0(0);        B lwz r27, 0(0)
Retained best candidate

AOSS_81400E0C initial 81.710526%
- record view after clear and original positive signed byte-count guard: 85.8421%; src 0x2f4 base 0x2f8 insns 189/190; --- replace mine 19:20 base 19:20;   M   19 bgt -10867;   B   19 bgt -11215
- bulk byte count snapshot before eight-byte bound test: 86.81579%; src 0x2fc base 0x2f8 insns 191/190; --- replace mine 19:20 base 19:20;   M   19 bgt -10867;   B   19 bgt -11215
- tail loop increments decoded byte count instead of remaining count: 86.1579%; src 0x2fc base 0x2f8 insns 191/190; --- replace mine 19:20 base 19:20;   M   19 bgt -10867;   B   19 bgt -11215
Retained best candidate

Retained reverse original real-object order: SBSS addresses now list 0x00/config 0x04/name 0x08/connection 0x10/error 0x14/socket-started 0x18/response 0x1c. All seven real objects have the original relative offsets; no padding or artificial objects. Objdiff reports 42.857143 for the zero-filled section; three of seven symbol correspondences appear inferred, despite the original relative offsets and zero bytes.

AOSS_814002F0 is instruction-exact (120/120, diffs 0, objdiff 100). Every baseline-unmatched AOSS function received at least three distinct compiling source trials above. Native supplemental KSA checks lengths 0/1/7/8/9/16/256/300, CRC all 256 rows, and actual decryption/checksum-rejection checks lengths 1/7/8/9/16/31/32/255/256/257 pass. Vendor transform and network conversion were stubbed in the native harness to isolate crypto and payload placement.

AOSS_81400830 cleanup trial: removing the final state publication from the odd-byte tail reduced objdiff from 83.99377 to 82.99689; restored the best compiling source. Hello record field renamed supportedModes to reflect its original runtime flags source; output unchanged.

## Final remaining functions

src/scene/setting/ATERM

ATERM_814021BC, 96.61688%, register allocation and instruction scheduling around interface setup; src 0x268 base 0x268 insns 154/154
ATERM_8140276C, 95.965515%, one missing instruction and selected-record/result register lifetimes; src 0x2b4 base 0x2b8 insns 173/174
ATERM_81402A24, 90.5019%, stack layout and scan completion/control-flow scheduling; src 0x40c base 0x41c insns 259/263
ATERM_81402E40, 99.791664%, two argument moves ordered differently; cr1 branch normalization also differs; src 0x180 base 0x180 insns 96/96
ATERM_814031DC, 97.74436%, hex-conversion temporaries and register allocation; src 0x214 base 0x214 insns 133/133
ATERM_814033F0, 98.576645%, option iterator and byte decoder register allocation; src 0x224 base 0x224 insns 137/137
ATERM_814036D8, 99.08064%, security option register allocation; switch table now in original order; src 0x1f0 base 0x1f0 insns 124/124
ATERM_814038C8, 85.12934%, protocol stack layout, state dispatch and instruction scheduling; src 0xef0 base 0xedc insns 956/951
ATERMi_AutoConfigThread, 94.75%, mask/shift instruction choice and clock register scheduling; src 0xa0 base 0xa0 insns 40/40
ATERM_81404844, 99.0171%, wrap loop register allocation; src 0x1d4 base 0x1d4 insns 117/117
ATERM_81404A18, 99.09091%, unwrap loop register allocation; src 0x1e4 base 0x1e4 insns 121/121
ATERM_81404BFC, 96.61567%, key expansion branch and register scheduling; src 0x43c base 0x430 insns 271/268
ATERM_8140502C, 99.42029%, reverse-round-key register allocation; src 0x228 base 0x228 insns 138/138
ATERM_81405254, 50.214024%, AES encryption table loads, XOR scheduling and register allocation; src 0x420 base 0x43c insns 264/271
ATERM_81405690, 48.579334%, AES decryption table loads, XOR scheduling and register allocation; src 0x424 base 0x43c insns 265/271
ATERM_81405ACC, 83.09028%, copy loop scheduling and compiler save/restore helpers; src 0x230 base 0x240 insns 140/144
ATERM_81405D0C, 53.851387%, MD5 transform expression scheduling and missing target instructions; src 0xa50 base 0xb40 insns 660/720
ATERMi_ApConfigStart, 99.805824%, clock register allocation; src 0x19c base 0x19c insns 103/103
ATERMi_ApConfigEnd, 93.94574%, save/restore helpers and alarm clock scheduling; src 0x1f4 base 0x204 insns 125/129
ATERMi_ApConfigGetState, 99.42857%, clock quotient register allocation; src 0x8c base 0x8c insns 35/35
ATERM_81402FC0, 100.0%, gate instruction-exact remains open: two identical raw cr1 branches are normalized using absolute addresses; no address pinning used.

src/scene/setting/AOSS

AOSS_Init_old, 28.42298%, large initialization control-flow, stack layout and expression scheduling; src 0x1794 base 0x18c0 insns 1509/1584
AOSS_813FFD68, 96.981735%, compiler save/restore helper replaces original individual register saves; src 0x364 base 0x36c insns 217/219
AOSS_814001B4, 88.78481%, compiler save/restore helper and dispatch scheduling; src 0x12c base 0x13c insns 75/79
AOSS_81400830, 83.99377%, RC4/CRC loop guards, stack layout and instruction scheduling; src 0x4ec base 0x504 insns 315/321
AOSS_81400E0C, 86.81579%, bulk/tail loop scheduling and register allocation; cr1 normalization affects ctxdiff; src 0x2fc base 0x2f8 insns 191/190
AOSS_814013AC, 94.48245%, network error join and response iterator register scheduling; src 0x1d0 base 0x1c8 insns 116/114
AOSS_81401574, 98.87597%, three callee-saved registers cycle; 28 register-only differences; src 0x204 base 0x204 insns 129/129
AOSS_81401778, 77.53846%, CRC expression prefetch and RC4 scheduling; src 0x440 base 0x444 insns 272/273
AOSS_81401C9C, 77.0685%, state initialization and forward mixer loop scheduling; src 0x130 base 0x124 insns 76/73
AOSS_81401DC0, 99.375%, four register-only differences in final polynomial step (r0 versus r3); src 0xc0 base 0xc0 insns 48/48
AOSS_81401E80, 92.82313%, key mask store and packet XOR loop scheduling; src 0x248 base 0x24c insns 146/147
AOSS_814020CC, 81.65%, compiler save/restore helper and readiness clock scheduling; src 0xe4 base 0xf0 insns 57/60

Data remaining: ATERM .data/.sdata unscored symbol mapping and .sbss correspondence; AOSS zero-filled .sbss correspondence (42.857143) despite restored original real-object offsets. String pools identical for both; all other AOSS data sections 100. No data padding or manual address symbols introduced.

Uncertainties: inferred zero-filled symbol correspondence versus section score; ctxdiff/gate cr1 normalization. Native supplemental tests isolate crypto and do not substitute for the object gate.

## Final full gate across both touched units

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 1648/19204 data 18448/18864 functions 6/26 fuzzy 82.5403 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 5/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match None
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 38.88889
[src/scene/setting/ATERM]   section .sdata size 56 match None
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 82.540306
[src/scene/setting/ATERM]   below 100: ATERM_814021BC 96.61688
[src/scene/setting/ATERM]   below 100: ATERM_8140276C 95.965515
[src/scene/setting/ATERM]   below 100: ATERM_81402A24 90.5019
[src/scene/setting/ATERM]   below 100: ATERM_81402E40 99.791664
[src/scene/setting/ATERM]   below 100: ATERM_814031DC 97.74436
[src/scene/setting/ATERM]   below 100: ATERM_814033F0 98.576645
[src/scene/setting/ATERM]   below 100: ATERM_814036D8 99.08064
[src/scene/setting/ATERM]   below 100: ATERM_814038C8 85.12934
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERM_81404844 99.0171
[src/scene/setting/ATERM]   below 100: ATERM_81404A18 99.09091
[src/scene/setting/ATERM]   below 100: ATERM_81404BFC 96.61567
[src/scene/setting/ATERM]   below 100: ATERM_8140502C 99.42029
[src/scene/setting/ATERM]   below 100: ATERM_81405254 50.214024
[src/scene/setting/ATERM]   below 100: ATERM_81405690 48.579334
[src/scene/setting/ATERM]   below 100: ATERM_81405ACC 83.09028
[src/scene/setting/ATERM]   below 100: ATERM_81405D0C 53.851387
[src/scene/setting/ATERM]   below 100: ATERMi_ApConfigStart 99.805824
[src/scene/setting/ATERM]   below 100: ATERMi_ApConfigEnd 93.94574
[src/scene/setting/ATERM]   below 100: ATERMi_ApConfigGetState 99.42857
[src/scene/setting/ATERM] baseline: code 1108/19204 data 18448 functions 5 fuzzy 63.9763
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 3244/16192 data 3896/3928 functions 9/21 fuzzy 67.0618 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 9/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 42.857143
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 67.06176
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 28.42298
[src/scene/setting/AOSS]   below 100: AOSS_813FFD68 96.981735
[src/scene/setting/AOSS]   below 100: AOSS_814001B4 88.78481
[src/scene/setting/AOSS]   below 100: AOSS_81400830 83.99377
[src/scene/setting/AOSS]   below 100: AOSS_81400E0C 86.81579
[src/scene/setting/AOSS]   below 100: AOSS_814013AC 94.48245
[src/scene/setting/AOSS]   below 100: AOSS_81401574 98.87597
[src/scene/setting/AOSS]   below 100: AOSS_81401778 77.53846
[src/scene/setting/AOSS]   below 100: AOSS_81401C9C 77.0685
[src/scene/setting/AOSS]   below 100: AOSS_81401DC0 99.375
[src/scene/setting/AOSS]   below 100: AOSS_81401E80 92.82313
[src/scene/setting/AOSS]   below 100: AOSS_814020CC 81.65
[src/scene/setting/AOSS] baseline: code 2764/16192 data 3896 functions 8 fuzzy 64.9019
regressions vs baseline: 0
global matched_code_percent: 82.03095 -> 82.06500
global fuzzy_match_percent: 93.35329 -> 93.48399
global complete_code_percent: 57.20994 -> 57.20994
global matched_data_percent: 89.09643 -> 89.09643
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: src/scene/setting/AOSS.c: possible pointer+offset into a blob (orchestrator reviews) (+2 net), e.g. SOSendTo(socket, response, (s16)(requestLength + 0x18), 0, &destination);
GATE PASS
```
