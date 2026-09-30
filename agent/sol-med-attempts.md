# sol-med matching attempts

ATERM pool was identical before iteration. Initial gate: 3/26 instruction-exact, code 72/19204, data 18440/18864, no regressions.

ATERM_814021BC: (1) combined network settings and access-point name, moved member-pointer initialization after clears, bottom-tested host loop: 153/154 instructions, register and addressing differences; (2) aligned the name member and explicit settings pointer: same instruction count and differences; (3) initialized IP pointer before clear: no improvement. Restored original to avoid unrelated aggregate changes.
ATERM_81402424: (1) aligned scan parameters to 32, swapped message/buffer declarations, preserved scan exit result test: 210/210, three condition-register differences; (2) tested scan result != retry error: one branch difference; (3) tested scan result == retry error: 210/210, diffs 0. Retained.
ATERM_8140276C: (1) initialized previous record cursor before outer loop, reset at outer tail, separated result flag, scoped AOSS flags: 174/174, 31 register differences; (2) reordered result/found declarations and scoped previous index: 174/174, 27 register differences. Further experiments below.
ATERM_81403614: (1) switch over hex character ranges, signed index and indexed output: 49/49, two division differences; (2) explicit signed truncation for index/2: one operand-order difference; (3) reversed addition operands: diffs 0. Retained.
ATERMi_AutoConfigThread: (1) real three-field progress object and conditional terminal state: 39/40 instructions; (2) signed equality mask: 40/40, three scheduling/register differences; (3) read progress result before deadline assignment: eight differences. Further experiments below.
ATERMi_ApConfigStart: (1) inclusive state bounds, use stored stack size and callback: 103/103, twelve differences; (2) restore source order of global initialization: six clock-register differences. Further experiments below.
ATERMi_ApConfigEnd: (1) capture initial state only inside active-thread branch, swap message declarations, compute 500ms alarm instead of reciprocal literal: 125/129 instructions, frame/scheduling differences. Further experiments below.
ATERMi_ApConfigGetState: (1) reciprocal first in multiply-high: four register differences; (2) load bus clock in multiply expression: unchanged; (3) direct time conversion expression: unchanged. Restored original, 35/35 instructions with three register differences.

ATERM_8140276C initial 99.166664%
- previous cursor declaration before current cursor: 99.5115%; src 0x2b8 base 0x2b8 insns 174/174; diffs 15: [8, 9, 82, 84, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97];      8 M addi r27, r4, 4;        B addi r31, r3, 4
- signed record indices: 99.166664%; src 0x2b8 base 0x2b8 insns 174/174; diffs 27: [8, 9, 18, 29, 34, 41, 50, 54, 55, 60, 61, 68, 74, 75, 82, 84, 87, 88, 89, 90];      8 M addi r27, r3, 4;        B addi r31, r3, 4
- AOSS flags initialized after clear: 99.54023%; src 0x2b8 base 0x2b8 insns 174/174; diffs 14: [8, 9, 18, 29, 34, 41, 50, 54, 55, 60, 61, 68, 74, 75];      8 M addi r27, r3, 4;        B addi r31, r3, 4
Retained original

ATERM_81402A24 initial 72.47529%
- record capacity includes final descriptor: 71.30038%; src 0x3d4 base 0x41c insns 245/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- allocate nullable buffers before handling failure: 72.380226%; src 0x3cc base 0x41c insns 243/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- multiply-high tick conversion: 75.76426%; src 0x3f4 base 0x41c insns 253/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
Retained original

ATERM_81402E40 initial 99.791664%
- payload clear through byte alias: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- natural checksum loop: 65.208336%; src 0x108 base 0x180 insns 66/96; --- replace mine 5:12 base 5:12;   M    5 mr r28, r5;   M    6 mr r26, r3
- end length as packet byte extent: 95.572914%; src 0x180 base 0x180 insns 96/96; diffs 6: [9, 10, 42, 44, 47, 52];      9 M mr r29, r7;        B mr r3, r27
Retained original

ATERM_81402FC0 initial 67.28148%
- full-width checksum accumulator: 64.76296%; src 0x20c base 0x21c insns 131/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11
- bottom-tested option loop: compile failed
- early return for bad checksum: 66.94074%; src 0x20c base 0x21c insns 131/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11
Retained original

ATERM_814031DC initial 85.7218%
- MAC text uses equal-sized buffers: 85.766914%; src 0x1f4 base 0x214 insns 125/133; --- replace mine 47:48 base 47:48;   M   47 beq 288;   B   47 beq 320
- nibble conversion advances output cursor: 84.293236%; src 0x204 base 0x214 insns 129/133; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x70(r1);   B    0 stwu r1, -0x60(r1)
- inclusive digit bound and pointer-based MAC scan: 85.90225%; src 0x1f4 base 0x214 insns 125/133; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x70(r1);   B    0 stwu r1, -0x60(r1)
Retained original

ATERM_814033F0 initial 65.868614%
- option fields retain converted word width: 67.39416%; src 0x214 base 0x224 insns 133/137; --- replace mine 5:6 base 5:6;   M    5 addi r30, r3, 8;   B    5 addi r29, r3, 8
- bottom-tested parser dispatch: 65.79562%; src 0x21c base 0x224 insns 135/137; --- replace mine 5:6 base 5:6;   M    5 addi r28, r3, 8;   B    5 addi r29, r3, 8
- signed nibble comparisons: 65.32117%; src 0x21c base 0x224 insns 135/137; --- insert mine 7:7 base 7:8;   B    7 li r24, 0; --- replace mine 10:29 base 11:17
Retained original

ATERM_814036D8 initial 73.92742%
- security switch matches original decision tree: 85.22581%; src 0x1ec base 0x1f0 insns 123/124; --- replace mine 14:15 base 14:15;   M   14 beq 340;   B   14 beq 344
- key text passed through one cursor: 87.0%; src 0x1e4 base 0x1f0 insns 121/124; --- replace mine 14:24 base 14:16;   M   14 bne 36;   M   15 addi r3, r25, 0
- counted loop over key records: 73.92742%; src 0x1e0 base 0x1f0 insns 120/124; --- replace mine 14:24 base 14:16;   M   14 bne 36;   M   15 addi r3, r25, 0
Retained original

ATERM_814038C8 initial 35.28917%
- one-shot 500ms wait replaces repeated alarm: 35.700314%; src 0x788 base 0xedc insns 482/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0xe0(r1);   B    0 stwu r1, -0x180(r1)
- bottom-tested state machine and wait buffer order: 35.288116%; src 0x784 base 0xedc insns 481/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0xe0(r1);   B    0 stwu r1, -0x180(r1)
- progress uses semantic structure: 35.28917%; src 0x784 base 0xedc insns 481/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0xe0(r1);   B    0 stwu r1, -0x180(r1)
Retained original

ATERM_81404844 initial 19.615385%
- signed RFC3394 counters: 16.34188%; src 0x1a0 base 0x1d4 insns 104/117; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x150(r1);   B    0 stwu r1, -0x190(r1)
- counter represented as big-endian bytes: compile failed
- RFC3394 initial value and block output order: 18.264957%; src 0x1b0 base 0x1d4 insns 108/117; --- replace mine 6:9 base 6:13;   M    6 mr r27, r3;   M    7 mr r20, r4
Retained original

ATERM_81404A18 initial 51.107437%

ATERM_81404844 initial 19.615385%
- signed RFC3394 counters: 16.34188%; src 0x1a0 base 0x1d4 insns 104/117; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x150(r1);   B    0 stwu r1, -0x190(r1)

ATERM_81404844 initial 16.34188%
- signed RFC3394 counters: 16.34188%; src 0x1a0 base 0x1d4 insns 104/117; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x150(r1);   B    0 stwu r1, -0x190(r1)
- counter represented as big-endian bytes: compile failed
- RFC3394 initial value and block output order: 18.264957%; src 0x1b0 base 0x1d4 insns 108/117; --- replace mine 6:9 base 6:13;   M    6 mr r27, r3;   M    7 mr r20, r4
Retained original

ATERM_81404A18 initial 51.107437%
- signed RFC3394 counters: 52.05785%; src 0x1c8 base 0x1e4 insns 114/121; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x150(r1);   B    0 stwu r1, -0x1a0(r1)
- counter represented as big-endian bytes: compile failed
- RFC3394 initial value and block output order: 54.991737%; src 0x1c4 base 0x1e4 insns 113/121; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x1a0(r1)
Retained original

ATERM_81404BFC initial 36.869404%
- AES byte assembly uses XOR instead of OR: 37.063435%; src 0x400 base 0x430 insns 256/268; --- replace mine 0:6 base 0:20;   M    0 lbz r7, 1(r4);   M    1 cmplwi r5, 0x80
- key schedule reads preceding round and chains fourth key word: 36.925373%; src 0x3dc base 0x430 insns 247/268; --- replace mine 0:6 base 0:20;   M    0 lbz r7, 1(r4);   M    1 cmplwi r5, 0x80
- signed round count drives key expansion termination: 49.21642%; src 0x3e0 base 0x430 insns 248/268; --- replace mine 0:3 base 0:47;   M    0 lbz r8, 1(r4);   M    1 cmplwi r5, 0x80
Retained original

ATERM_8140502C initial 35.666668%
- interleaved key-word swaps: 42.355072%; src 0x280 base 0x228 insns 160/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0
- signed indexed round reversal: 38.746376%; src 0x290 base 0x228 insns 164/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0
- counted transformation loop: 11.731884%; src 0x288 base 0x228 insns 162/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0
Retained original

ATERM_81405254 initial 30.464945%
- AES byte assembly uses XOR: 34.23247%; src 0x3c4 base 0x43c insns 241/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- two-round loop with final round exit: compile failed
- signed round count with separately combined key XOR: compile failed
Retained original

ATERM_81405690 initial 26.601477%
- AES byte assembly uses XOR: 34.64945%; src 0x3d4 base 0x43c insns 245/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- two-round loop with final round exit: compile failed
- signed round count with separately combined key XOR: compile failed
Retained original

ATERM_81405ACC initial 0%
- natural byte copy instead of explicit eight-byte loop: 0%; src 0x10c base 0x240 insns 67/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:12 base 4:10
- separate 32-bit count carry updates: 0%; src 0x184 base 0x240 insns 97/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:5 base 4:11
- indexed full-block walk retains input length: 0%; src 0x17c base 0x240 insns 95/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:12 base 4:10
Retained original

ATERM_81405D0C initial 32.62639%
- decode words with XOR: 25.144444%; src 0xa5c base 0xb40 insns 663/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0xa0(r1)
- MD5 first-round select expressed as xor mask: 30.945833%; src 0x9fc base 0xb40 insns 639/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0xa0(r1)
- flat byte-to-word decode loop: 27.13889%; src 0x904 base 0xb40 insns 577/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0xa0(r1)
Retained original

ATERMi_AutoConfigThread initial 91.325%
- remaining time assigned before terminal state: 91.475%; src 0xa0 base 0xa0 insns 40/40; diffs 7: [20, 22, 23, 26, 28, 29, 30];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- terminal mask reuses result variable: 85.075%; src 0xa0 base 0xa0 insns 40/40; diffs 9: [21, 22, 23, 25, 26, 28, 29, 30, 31];     21 M lwz r4, 0(0);        B li r4, -1
- state stores preceding deadline store: 85.2%; src 0xa0 base 0xa0 insns 40/40; diffs 8: [21, 22, 23, 25, 26, 29, 30, 31];     21 M lwz r4, 0(0);        B li r4, -1
Retained original

ATERMi_ApConfigStart initial 99.70874%
- allocate via stored callback: 99.70874%; src 0x19c base 0x19c insns 103/103; diffs 6: [46, 47, 48, 49, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
- tick multiplier commutes operands: 97.76699%; src 0x19c base 0x19c insns 103/103; diffs 7: [48, 49, 51, 75, 76, 77, 78];     48 M lwz r6, 0xf8(r30);        B lwz r0, 0xf8(r30)
- progress state populated before zeroing result buffer: 90.72816%; src 0x19c base 0x19c insns 103/103; diffs 18: [46, 47, 48, 49, 56, 58, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 75, 76];     46 M lis r31, -0x8000;        B lis r30, -0x8000
Retained original

ATERMi_ApConfigEnd initial 93.94574%
- message queues declared within their wait scopes: 91.89922%; src 0x1f4 base 0x204 insns 125/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
- join loop expressed as do-while: 91.54263%; src 0x200 base 0x204 insns 128/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
- time conversion evaluated directly: 93.94574%; src 0x1f4 base 0x204 insns 125/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
Retained original

ATERM_81404844 initial 19.615385%
- big-endian counter union assigned after declarations: 23.931623%; src 0x1a0 base 0x1d4 insns 104/117; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x150(r1);   B    0 stwu r1, -0x190(r1)
Retained original

ATERM_81404A18 initial 51.107437%
- big-endian counter union assigned after declarations: 57.677685%; src 0x1c8 base 0x1e4 insns 114/121; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x150(r1);   B    0 stwu r1, -0x1a0(r1)
Retained original

ATERM_81405254 initial 30.464945%
- two-round iteration with scoped second round: 25.00369%; src 0x4b8 base 0x43c insns 302/271; --- replace mine 5:42 base 5:230;   M    5 lbz r9, 1(r5);   M    6 lis r12, 0
- signed round index: 30.464945%; src 0x3a4 base 0x43c insns 233/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- round key XOR before table combination: 30.464945%; src 0x3a4 base 0x43c insns 233/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
Retained original

ATERM_81405690 initial 26.601477%
- two-round iteration with scoped second round: 23.239853%; src 0x4d8 base 0x43c insns 310/271; --- replace mine 5:13 base 5:7;   M    5 lbz r10, 1(r5);   M    6 lis r7, 0
- signed round index: 26.601477%; src 0x3b4 base 0x43c insns 237/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- round key XOR before table combination: 26.601477%; src 0x3b4 base 0x43c insns 237/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
Retained original

ATERM_81402FC0 initial 67.28148%
- option loop with explicit continuation test: 67.28148%; src 0x210 base 0x21c insns 132/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11
Retained original

ATERM final source retains only exact scan and hex-conversion changes. All unsuccessful experiments restored. Remaining 21 functions are open; their instruction counts and experiment outcomes are recorded above. Cryptographic routines require substantial reconstruction, not just register allocation.

AOSS initial gate: 7/21 instruction-exact; code 2540/16192; data 3896/3928. String pool identical.
AOSS_814001B4: early returns and opcode switch: 75/79, remaining differences are save/restore helper versus individual stores.
AOSS_81401BBC: (1) reverse rounding addition: same one operand-order difference; (2) signed rounding temporary: same difference; (3) inline signed rounding expression: 56/56, diffs 0. Retained.
AOSS_81401DC0: (1) reuse seed parameter: 48/48, four last-step register differences; (2) split shift/XOR statements: 64/48 instructions; (3) eight-iteration CRC loop: 16/48 instructions. Restored original.

AOSS_Init_old initial 28.42298%
- full-width wait counters instead of narrowing every update: 28.546717%; src 0x1758 base 0x18c0 insns 1494/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b

AOSS_Init_old initial 28.42298%
- full-width wait counters instead of narrowing every update: 28.546717%; src 0x1758 base 0x18c0 insns 1494/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- packet length conversion retains full width: 28.42298%; src 0x1794 base 0x18c0 insns 1509/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- poll arguments given semantic socket events structure: 28.42298%; src 0x1794 base 0x18c0 insns 1509/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
Retained original

AOSS_813FFD68 initial 96.981735%
- validation loops use signed char: 93.69406%; src 0x364 base 0x36c insns 217/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- return failure immediately on invalid character: 82.05023%; src 0x2ec base 0x36c insns 187/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- ascending validation cursor loop: 94.76712%; src 0x374 base 0x36c insns 221/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained original

AOSS_814001B4 initial 88.78481%
- converted packet length stays full width: 88.78481%; src 0x12c base 0x13c insns 75/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- direct opcode return cases: 83.27848%; src 0x124 base 0x13c insns 73/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- full-width validation and branch nesting: 88.78481%; src 0x12c base 0x13c insns 75/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained original

AOSS_814002F0 initial 79.525%
- read manufacturer only after state validation: 85.058334%; src 0x1c4 base 0x1e0 insns 113/120; --- replace mine 6:8 base 6:8;   M    6 mr r30, r3;   M    7 mr r26, r4
- packet sequence values remain full-width: 76.441666%; src 0x1c4 base 0x1e0 insns 113/120; --- replace mine 5:7 base 5:8;   M    5 mr r30, r3;   M    6 mr r26, r4
- direct address error branch: 79.525%; src 0x1c8 base 0x1e0 insns 114/120; --- replace mine 5:7 base 5:8;   M    5 mr r30, r3;   M    6 mr r26, r4
Retained original

AOSS_81400830 initial 77.619934%
- single-byte RC4 generation loop instead of manual pairs: 65.65109%; src 0x3c0 base 0x504 insns 240/321; --- insert mine 6:6 base 6:7;   B    6 addi r29, r3, 0x18; --- insert mine 7:7 base 8:9
- natural CRC byte loop: 60.13084%; src 0x3c4 base 0x504 insns 241/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- narrow RC4 state indices at assignment: 77.619934%; src 0x4b8 base 0x504 insns 302/321; --- insert mine 6:6 base 6:7;   B    6 addi r29, r3, 0x18; --- insert mine 7:7 base 8:9
Retained original

AOSS_81400E0C initial 77.52105%
- signed option lengths and iteration indices: 77.778946%; src 0x2bc base 0x2f8 insns 175/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8
- natural integer byte decode for both address options: 44.963158%; src 0x188 base 0x2f8 insns 98/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8
- address decode accumulation uses OR: 61.963158%; src 0x284 base 0x2f8 insns 161/190; --- replace mine 5:8 base 5:8;   M    5 mr r29, r3;   M    6 mr r30, r4
Retained original

AOSS_814013AC initial 91.70175%
- signed option lengths: 91.70175%; src 0x1cc base 0x1c8 insns 115/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
- apply flags after successful parser call: 84.68421%; src 0x1ec base 0x1c8 insns 123/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
- bounded while loop over selected reply payload: 88.2807%; src 0x1d4 base 0x1c8 insns 117/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
Retained original

AOSS_81401574 initial 92.558136%
- semantic payload extent expression: 92.558136%; src 0x1fc base 0x204 insns 127/129; --- replace mine 5:7 base 5:7;   M    5 lwz r30, 0(0);   M    6 mr r27, r4
- request length remains full-width: 92.209305%; src 0x1f8 base 0x204 insns 126/129; --- replace mine 5:7 base 5:7;   M    5 lwz r30, 0(0);   M    6 mr r27, r4
- initialize destination length before port conversion: 88.31783%; src 0x1fc base 0x204 insns 127/129; --- replace mine 5:7 base 5:7;   M    5 lwz r30, 0(0);   M    6 mr r27, r4
Retained original

AOSS_81401778 initial 71.93407%
- CRC checksum stays full width until header store: 71.93407%; src 0x434 base 0x444 insns 269/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- signed RC4 byte loop index: 71.93407%; src 0x434 base 0x444 insns 269/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- copy hello payload before manufacturer encoding: 71.91575%; src 0x434 base 0x444 insns 269/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
Retained original

AOSS_81401C9C initial 71.9315%
- natural RC4 state initialization loop: 43.342464%; src 0x98 base 0x124 insns 38/73; --- replace mine 0:1 base 0:2;   M    0 li r9, 0;   B    0 stwu r1, -0x10(r1)
- schedule state reset before obtaining byte pointer: 71.9315%; src 0x12c base 0x124 insns 75/73; --- replace mine 0:6 base 0:2;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
- signed key and state indices: 71.9315%; src 0x12c base 0x124 insns 75/73; --- replace mine 0:6 base 0:2;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
Retained original

AOSS_81401E80 initial 91.80272%
- natural XOR loop over half-packet: 56.455784%; src 0x168 base 0x24c insns 90/147; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x30(r1);   B    0 stwu r1, -0x40(r1)
- half-length via signed division: 87.04082%; src 0x240 base 0x24c insns 144/147; --- replace mine 5:19 base 5:13;   M    5 srawi r0, r4, 1;   M    6 mr r28, r3
- count-down rounds: 88.734695%; src 0x244 base 0x24c insns 145/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
Retained original

AOSS_814020CC initial 76.066666%
- sleep tick product stays 64-bit: 67.51667%; src 0xfc base 0xf0 insns 63/60; --- replace mine 3:6 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- tick duration via explicit multiply-high: 81.65%; src 0xe4 base 0xf0 insns 57/60; --- replace mine 3:5 base 3:6;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- do-while host acquisition loop: 65.066666%; src 0xf8 base 0xf0 insns 62/60; --- replace mine 3:6 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained original

AOSS final: retained exact packet builder AOSS_81401BBC only. Other experiments restored; remaining differences include loop expansion, register allocation, missing original compiler control flow.

## src/scene/memoryCard/iplMemoryCardBase
Baseline absent source: 0/34, code 0/3640, data 0/152. Implemented all real functions in target address order from original disassembly using typed classes and fields. Initial build: 33/34 exact, code 3240/3640, data 144/152; pool identical.

onCmdRecv initial 96.35%: 101/100 instructions.
- Signed lower/upper bounds for command range: extra comparison and branch.
- Switch cases 1/2/3: 95.35%, 102/100 instructions, compiler produces signed comparison tree.
- Unsigned command range distance: 100%, 100/100 instructions, diffs 0. Retained.

Data limitation: original .sdata2 contains -1.0 plus trailing alignment, while source also emits the required integer-to-float conversion double constant. No forced data or padding added. Full DOL gate determines acceptance; no configure Matching changes.

## Remaining functions at final handoff
src/scene/setting/ATERM: ATERM_814021BC 67.655846% — src 0x264 base 0x268 insns 153/154; --- insert mine 7:7 base 7:9;   B    7 addi r30, r30, 0;   B    8 li r4, 0; remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_8140276C 92.10345% — src 0x2ac base 0x2b8 insns 171/174; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0x80(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_81402A24 72.47529% — src 0x3d0 base 0x41c insns 244/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_81402E40 99.791664% — src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27; remaining register/scheduling differences
src/scene/setting/ATERM: ATERM_81402FC0 67.28148% — src 0x210 base 0x21c insns 132/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11; remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_814031DC 85.7218% — src 0x1f4 base 0x214 insns 125/133; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x70(r1);   B    0 stwu r1, -0x60(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_814033F0 65.868614% — src 0x21c base 0x224 insns 135/137; --- insert mine 7:7 base 7:8;   B    7 li r24, 0; --- replace mine 10:29 base 11:17; remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_814036D8 73.92742% — src 0x1e0 base 0x1f0 insns 120/124; --- replace mine 14:24 base 14:16;   M   14 bne 36;   M   15 addi r3, r25, 0; remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_814038C8 35.28917% — src 0x784 base 0xedc insns 481/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0xe0(r1);   B    0 stwu r1, -0x180(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERMi_AutoConfigThread 94.6% — src 0xa0 base 0xa0 insns 40/40; diffs 9: [0, 2, 3, 20, 22, 23, 34, 36, 38];      0 M stwu r1, -0x30(r1);        B stwu r1, -0x20(r1); remaining register/scheduling differences
src/scene/setting/ATERM: ATERM_81404844 19.615385% — src 0x19c base 0x1d4 insns 103/117; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x150(r1);   B    0 stwu r1, -0x190(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_81404A18 51.107437% — src 0x1c4 base 0x1e4 insns 113/121; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x150(r1);   B    0 stwu r1, -0x1a0(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_81404BFC 36.869404% — src 0x3dc base 0x430 insns 247/268; --- replace mine 0:6 base 0:20;   M    0 lbz r7, 1(r4);   M    1 cmplwi r5, 0x80; remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_8140502C 35.666668% — src 0x280 base 0x228 insns 160/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0; remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_81405254 30.464945% — src 0x3a4 base 0x43c insns 233/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_81405690 26.601477% — src 0x3b4 base 0x43c insns 237/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_81405ACC None% — src 0x17c base 0x240 insns 95/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:12 base 4:10; remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERM_81405D0C 32.62639% — src 0x9e4 base 0xb40 insns 633/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0xa0(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERMi_ApConfigStart 86.49515% — src 0x1a4 base 0x19c insns 105/103; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x30(r1);   B    0 stwu r1, -0x20(r1); remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERMi_ApConfigEnd 87.54263% — src 0x1dc base 0x204 insns 119/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0; remaining control-flow/codegen differences
src/scene/setting/ATERM: ATERMi_ApConfigGetState 99.42857% — src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6); remaining register/scheduling differences
src/scene/setting/AOSS: AOSS_Init_old 28.42298% — src 0x1794 base 0x18c0 insns 1509/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_813FFD68 96.981735% — src 0x364 base 0x36c insns 217/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_814001B4 41.518986% — src 0x118 base 0x13c insns 70/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_814002F0 79.525% — src 0x1c8 base 0x1e0 insns 114/120; --- replace mine 5:7 base 5:8;   M    5 mr r30, r3;   M    6 mr r26, r4; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_81400830 77.619934% — src 0x4b8 base 0x504 insns 302/321; --- insert mine 6:6 base 6:7;   B    6 addi r29, r3, 0x18; --- insert mine 7:7 base 8:9; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_81400E0C 77.52105% — src 0x2c4 base 0x2f8 insns 177/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_814013AC 91.70175% — src 0x1cc base 0x1c8 insns 115/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_81401574 92.558136% — src 0x1fc base 0x204 insns 127/129; --- replace mine 5:7 base 5:7;   M    5 lwz r30, 0(0);   M    6 mr r27, r4; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_81401778 71.93407% — src 0x434 base 0x444 insns 269/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0); remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_81401C9C 71.9315% — src 0x12c base 0x124 insns 75/73; --- replace mine 0:6 base 0:2;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_81401DC0 99.375% — src 0xc0 base 0xc0 insns 48/48; diffs 4: [39, 41, 42, 43];     39 M srwi r0, r3, 1;        B srwi r3, r3, 1; remaining register/scheduling differences
src/scene/setting/AOSS: AOSS_81401E80 91.80272% — src 0x244 base 0x24c insns 145/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3; remaining control-flow/codegen differences
src/scene/setting/AOSS: AOSS_814020CC 76.066666% — src 0xf0 base 0xf0 insns 60/60; diffs 39: [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 25, 26];      3 M addi r11, r1, 0x20;        B stw r31, 0x1c(r1); remaining register/scheduling differences

MemoryBase full clean gate: 34/34 instruction-exact, code 3640/3640, data 144/152, pool identical, regressions 0, forbidden patterns 0, readability warnings 0, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, GATE PASS. Data remains incomplete in objdiff; no artificial fix attempted.
