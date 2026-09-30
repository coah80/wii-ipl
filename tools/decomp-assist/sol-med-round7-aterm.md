# ATERM round 7 attempts

Baseline at 7f055a58: instruction exact 11/26, matched code 6576/19204, data 18504/18864, fuzzy 91.468864%.

Work highest-percentage first. Check the stack frame and local order, branch direction, temporaries, then register allocation. Distinct successful compiling trials are counted; unchanged/failed trials are excluded. Both units have identical string pools before iteration. Complete initial and retained instruction differences are recorded below. No data pins or padding.

## ATERM_81402FC0 initial instruction differences

Frame, counts and raw instructions are identical. Two printed cr1 branch displacements are context normalization differences. Source trials preserve checksum/protocol behavior; do not alter function placement to influence these diagnostics.

```text
src 0x21c base 0x21c insns 135/135
diffs 2: [18, 23]
    18 M bge -3635
       B bge -3647
    23 M bgt -3655
       B bgt -3667
```

ATERM_81402FC0 initial 100.0%
- temporary: checksum compared after an explicit halfword narrowing: 100.0%; src 0x21c base 0x21c insns 135/135; diffs 2: [18, 23];     18 M bge -3635;        B bge -3647
- branch: valid checksum selects payload before rejection arm: 99.07407%; src 0x21c base 0x21c insns 135/135; diffs 5: [18, 23, 61, 62, 64];     18 M bge -3635;        B bge -3647
- local order: checksum accumulator declared after option state fields: 98.51852%; src 0x21c base 0x21c insns 135/135; diffs 32: [8, 10, 13, 15, 18, 23, 32, 34, 36, 38, 40, 42, 44, 46, 54, 59, 66, 67, 68, 72];      8 M li r29, 0;        B li r31, 0
Retained objdiff-100 candidate

## ATERM_81402E40 initial instruction differences

Frame 0x30 and 96 instructions already agree. Remaining real difference is ordering of entry argument moves at 9/10. Two cr1 branch diagnostics are normalization artifacts; no branch control-flow difference. Test source pointer/type lifetimes before broader restructuring.

```text
src 0x180 base 0x180 insns 96/96
diffs 4: [9, 10, 47, 52]
     9 M mr r29, r7
       B mr r3, r27
    10 M mr r3, r27
       B mr r29, r7
    47 M bge -3367
       B bge -3379
    52 M bgt -3387
       B bgt -3399
```

ATERM_81402E40 initial 99.791664%
- local order: opaque payload argument with typed halfword header view: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- temporary: typed payload view assigned after the header clear: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- register choice: payload header view introduced at SOHtoNs store: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
Retained best candidate

## ATERM_8140502C initial instruction differences

Frame and all 138 instructions agree; branches are identical. Eleven operand differences are one last-index/swap-word r6/r8 cycle in the reversal loop. The remaining inverse-table transform is identical. Start with local index order, then the actual swap temporary lifetime.

```text
src 0x228 base 0x228 insns 138/138
diffs 11: [11, 15, 18, 20, 21, 24, 25, 28, 29, 33, 35]
    11 M slwi r6, r3, 2
       B slwi r8, r3, 2
    15 M lwz r8, 0(r4)
       B lwz r6, 0(r4)
    18 M addi r6, r6, -4
       B addi r8, r8, -4
    20 M stw r8, 0(r5)
       B stw r6, 0(r5)
    21 M lwz r8, 4(r4)
       B lwz r6, 4(r4)
    24 M stw r8, 4(r5)
       B stw r6, 4(r5)
    25 M lwz r8, 8(r4)
       B lwz r6, 8(r4)
    28 M stw r8, 8(r5)
       B stw r6, 8(r5)
    29 M lwz r8, 0xc(r4)
       B lwz r6, 0xc(r4)
    33 M stw r8, 0xc(r5)
       B stw r6, 0xc(r5)
    35 M cmpw r7, r6
       B cmpw r7, r8
```

ATERM_8140502C initial 99.565216%
- local order: first reversal index declared before last index: 99.42029%; src 0x228 base 0x228 insns 138/138; diffs 13: [11, 12, 15, 16, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r7, r3, 2;        B slwi r8, r3, 2
- temporary: unsigned last word index with signed range comparison: 99.565216%; src 0x228 base 0x228 insns 138/138; diffs 11: [11, 15, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r6, r3, 2;        B slwi r8, r3, 2
- register choice: last pointer assigned from the named final word index: 99.565216%; src 0x228 base 0x228 insns 138/138; diffs 11: [11, 15, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r6, r3, 2;        B slwi r8, r3, 2
Retained best candidate

## ATERM_814033F0 initial instruction differences

Frame and 137 instructions agree; branch directions match. Eleven differences are the result/key-view r22/r23 cycle, including zero stores that reuse the result accumulator. Introduce the SSID-found result at its logical search scope and the key view at the key-option scope.

```text
src 0x224 base 0x224 insns 137/137
diffs 11: [11, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101]
    11 M li r23, 0
       B li r22, 0
    65 M addi r22, r3, 0x164
       B addi r23, r3, 0x164
    66 M mr r3, r22
       B mr r3, r23
    81 M addi r3, r22, 1
       B addi r3, r23, 1
    82 M stb r0, 0(r22)
       B stb r0, 0(r23)
    85 M addi r3, r22, 1
       B addi r3, r23, 1
    86 M stb r0, 0(r22)
       B stb r0, 0(r23)
    96 M subf r0, r22, r3
       B subf r0, r23, r3
    97 M stb r23, 0(r3)
       B stb r22, 0(r3)
    98 M add r22, r22, r0
       B add r23, r23, r0
   101 M mr r3, r22
       B mr r3, r23
```

ATERM_814033F0 initial 99.56204%
- local order: key view declared and initialized only inside key option block: 99.56204%; src 0x224 base 0x224 insns 137/137; diffs 11: [11, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];     11 M li r23, 0;        B li r22, 0
- temporary: SSID-found result is a signed boolean-sized byte: 99.56204%; src 0x224 base 0x224 insns 137/137; diffs 11: [11, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];     11 M li r23, 0;        B li r22, 0
- register choice: key pointer assigned after the key buffer length view: 99.56204%; src 0x224 base 0x224 insns 137/137; diffs 11: [11, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];     11 M li r23, 0;        B li r22, 0
Retained best candidate

## ATERM_8140276C initial instruction differences

Frame, count, and branches match. Current-record and previous-index views exchange r20/r31 in the first loop; found/result/index initializations are in a different order. The fallback exchanges clear-zero, presence flags, and traversal index registers. Try initial scalar order, then pointer declaration lifetime, then separate fallback traversal locals.

```text
src 0x2b8 base 0x2b8 insns 174/174
diffs 27: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 69, 70, 74, 82, 84, 87, 88, 89, 90]
     8 M addi r20, r3, 4
       B addi r31, r3, 4
    11 M li r30, 0
       B li r29, 0
    12 M li r29, 0
       B li r28, 0
    13 M li r28, 0
       B li r30, 0
    18 M addi r4, r20, 4
       B addi r4, r31, 4
    29 M lwz r0, 0(r20)
       B lwz r0, 0(r31)
    30 M li r31, 0
       B li r20, 0
    34 M lwz r0, 0(r20)
       B lwz r0, 0(r31)
    41 M lbz r0, 4(r20)
       B lbz r0, 4(r31)
    54 M addi r3, r20, 0x28
       B addi r3, r31, 0x28
    60 M lhz r3, 0x2e(r20)
       B lhz r3, 0x2e(r31)
    69 M addi r31, r31, 1
       B addi r20, r20, 1
    70 M cmplw r31, r26
       B cmplw r20, r26
    74 M addi r20, r20, 0x30
       B addi r31, r31, 0x30
    82 M li r27, 0
       B li r22, 0
    84 M stw r27, 8(r1)
       B stw r22, 8(r1)
    87 M li r26, 0
       B li r27, 0
    88 M stw r27, 0xc(r1)
       B stw r22, 0xc(r1)
    89 M li r20, 0
       B li r26, 0
    90 M li r22, 0
       B li r20, 0
    91 M stw r27, 0x10(r1)
       B stw r22, 0x10(r1)
    92 M stw r27, 0x14(r1)
       B stw r22, 0x14(r1)
    93 M stw r27, 0x18(r1)
       B stw r22, 0x18(r1)
    94 M stw r27, 0x1c(r1)
       B stw r22, 0x1c(r1)
    95 M stw r27, 0x20(r1)
       B stw r22, 0x20(r1)
    96 M stw r27, 0x24(r1)
       B stw r22, 0x24(r1)
    97 M sth r27, 0x28(r1)
       B sth r22, 0x28(r1)
```

ATERM_8140276C initial 99.166664%
- local order: found and result initialized before current index: 98.56322%; src 0x2b8 base 0x2b8 insns 174/174; diffs 45: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 66, 69, 70, 72, 74, 76, 78, 80, 82];      8 M addi r20, r3, 4;        B addi r31, r3, 4
- local order: record views declared after scalar traversal locals: 98.93678%; src 0x2b8 base 0x2b8 insns 174/174; diffs 34: [11, 12, 13, 66, 72, 76, 78, 80, 82, 84, 85, 87, 88, 89, 90, 91, 92, 93, 94, 95];     11 M li r30, 0;        B li r29, 0
- temporary: independent fallback previous-list traversal index: 99.08046%; src 0x2b8 base 0x2b8 insns 174/174; diffs 30: [8, 9, 11, 12, 13, 18, 29, 34, 41, 50, 54, 55, 60, 61, 68, 74, 75, 82, 84, 87];      8 M addi r27, r3, 4;        B addi r31, r3, 4
Retained best candidate

## ATERM_81404844 initial instruction differences

Frame, all 117 instructions, and branches match. Twenty operands differ: destination/rounds/pass/index/offset registers form a cycle. Try byte-view lifetime, then remove redundant destination view through a byte formal, then reverse the equal-cost index/offset initialization source order.

```text
src 0x1d4 base 0x1d4 insns 117/117
diffs 20: [8, 27, 30, 36, 38, 39, 40, 41, 42, 45, 48, 54, 58, 60, 99, 100, 101, 103, 104, 106]
     8 M mr r24, r3
       B mr r25, r3
    27 M mr r28, r3
       B mr r26, r3
    30 M addi r3, r24, 8
       B addi r3, r25, 8
    36 M li r26, 0
       B li r28, 0
    38 M li r25, 1
       B li r29, 1
    39 M srawi r0, r26, 0x1f
       B srawi r0, r28, 0x1f
    40 M li r29, 8
       B li r24, 8
    41 M mulhwu r3, r27, r26
       B mulhwu r3, r27, r28
    42 M mullw r4, r4, r26
       B mullw r4, r4, r28
    45 M mullw r30, r27, r26
       B mullw r30, r27, r28
    48 M add r22, r24, r29
       B add r22, r25, r24
    54 M mr r4, r28
       B mr r4, r26
    58 M srawi r0, r25, 0x1f
       B srawi r0, r29, 0x1f
    60 M addc r3, r25, r30
       B addc r3, r29, r30
    99 M addi r25, r25, 1
       B addi r29, r29, 1
   100 M addi r29, r29, 8
       B addi r24, r24, 8
   101 M cmpw r25, r27
       B cmpw r29, r27
   103 M addi r26, r26, 1
       B addi r28, r28, 1
   104 M cmpwi r26, 6
       B cmpwi r28, 6
   106 M mr r3, r24
       B mr r3, r25
```

ATERM_81404844 initial 98.97436%
- local order: destination byte view scoped to first actual copy: compile failed
- temporary: destination byte formal replaces redundant alias: compile failed
- register choice: offset initialized before block index: 99.0%; src 0x1d4 base 0x1d4 insns 117/117; diffs 20: [8, 27, 30, 36, 38, 39, 40, 41, 42, 45, 48, 54, 58, 60, 99, 100, 101, 103, 104, 106];      8 M mr r24, r3;        B mr r25, r3
Retained best candidate

ATERM_81404844 initial 99.0%
- local order: destination byte view initialized with formal before guard: 98.74359%; src 0x1d4 base 0x1d4 insns 117/117; diffs 24: [8, 18, 19, 27, 30, 36, 37, 38, 39, 40, 41, 42, 43, 45, 48, 54, 58, 60, 99, 100];      8 M mr r28, r3;        B mr r25, r3
- temporary: pass counter uses unsigned six-pass range: 95.333336%; src 0x1d0 base 0x1d4 insns 116/117; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x1a0(r1);   B    0 stwu r1, -0x190(r1)
Retained best candidate

## ATERM_81404BFC initial instruction differences

All 268 instructions and control-flow blocks agree. Initial four packed words are scheduled in a different order, then the AES-128 constant/substitution views use r5/r4 instead of r4/r9. Later 192/256 expansion blocks agree. Try immediate per-word stores, direct destination words, then table view initialization order.

```text
src 0x430 base 0x430 insns 268/268
diffs 49: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 45, 48, 49]
     5 M lbz r7, 6(r4)
       B lbz r7, 2(r4)
     7 M lbz r6, 4(r4)
       B lbz r6, 0(r4)
     8 M lbz r0, 5(r4)
       B lbz r0, 1(r4)
    10 M lbz r7, 0xa(r4)
       B lbz r7, 6(r4)
    13 M lbz r6, 8(r4)
       B lbz r6, 4(r4)
    14 M lbz r0, 9(r4)
       B lbz r0, 5(r4)
    16 M lbz r7, 0xe(r4)
       B lbz r7, 0xa(r4)
    19 M lbz r6, 0xc(r4)
       B lbz r6, 8(r4)
    20 M lbz r0, 0xd(r4)
       B lbz r0, 9(r4)
    22 M lbz r25, 7(r4)
       B lbz r25, 3(r4)
    25 M lbz r7, 2(r4)
       B lbz r7, 0xe(r4)
    26 M lbz r6, 0(r4)
       B lbz r6, 0xc(r4)
    28 M lbz r0, 1(r4)
       B lbz r0, 0xd(r4)
    30 M lbz r28, 0xb(r4)
       B lbz r28, 7(r4)
    31 M xor r25, r25, r27
       B xor r27, r25, r27
    32 M lbz r12, 0xf(r4)
       B lbz r12, 0xb(r4)
    34 M lbz r8, 3(r4)
       B lbz r8, 0xf(r4)
    45 M stw r25, 4(r3)
       B stw r27, 0(r3)
    48 M stw r0, 0(r3)
       B stw r10, 4(r3)
    49 M stw r10, 8(r3)
       B stw r8, 8(r3)
    50 M stw r8, 0xc(r3)
       B stw r0, 0xc(r3)
    52 M lis r5, 0
       B lis r4, 0
    53 M lis r4, 0
       B lis r9, 0
    54 M addi r5, r5, 0
       B addi r4, r4, 0
    55 M addi r4, r4, 0
       B addi r9, r9, 0
    58 M lwz r10, 0(r5)
       B lwz r10, 0(r4)
    60 M rlwinm r9, r0, 0xa, 0x16, 0x1d
       B rlwinm r8, r0, 0xa, 0x16, 0x1d
    61 M rlwinm r8, r0, 2, 0x16, 0x1d
       B rlwinm r7, r0, 2, 0x16, 0x1d
    62 M lwzx r9, r4, r9
       B lwzx r8, r9, r8
    63 M rlwinm r7, r0, 0x12, 0x16, 0x1d
       B rlwinm r5, r0, 0x12, 0x16, 0x1d
    64 M lwzx r8, r4, r8
       B lwzx r7, r9, r7
    66 M lwzx r7, r4, r7
       B lwzx r5, r9, r5
    67 M clrlwi r9, r9, 0x18
       B clrlwi r8, r8, 0x18
    68 M rlwinm r8, r8, 0, 0x10, 0x17
       B rlwinm r7, r7, 0, 0x10, 0x17
    69 M lwzx r0, r4, r0
       B lwzx r0, r9, r0
    70 M xor r9, r9, r8
       B xor r8, r8, r7
    71 M lwz r8, 0(r3)
       B lwz r7, 0(r3)
    72 M rlwinm r7, r7, 0, 0, 7
       B rlwinm r5, r5, 0, 0, 7
    74 M xor r7, r8, r7
       B xor r5, r7, r5
    75 M xor r8, r10, r9
       B xor r7, r10, r8
    76 M xor r0, r7, r0
       B xor r0, r5, r0
    77 M addi r5, r5, 4
       B addi r4, r4, 4
    78 M xor r7, r8, r0
       B xor r5, r7, r0
    79 M stw r7, 0x10(r3)
       B stw r5, 0x10(r3)
    81 M xor r7, r0, r7
       B xor r5, r0, r5
    82 M stw r7, 0x14(r3)
       B stw r5, 0x14(r3)
    84 M xor r7, r0, r7
       B xor r5, r0, r5
    85 M stw r7, 0x18(r3)
       B stw r5, 0x18(r3)
    87 M xor r0, r0, r7
       B xor r0, r0, r5
```

ATERM_81404BFC initial 98.94403%
- temporary: store each packed word immediately after packing: 98.01492%; src 0x430 base 0x430 insns 268/268; diffs 37: [38, 39, 40, 41, 43, 44, 45, 46, 48, 52, 53, 54, 55, 58, 60, 61, 62, 63, 64, 66];     38 M xor r31, r30, r31;        B xor r0, r6, r0
- temporary: pack initial key directly into destination words: 98.01492%; src 0x430 base 0x430 insns 268/268; diffs 37: [38, 39, 40, 41, 43, 44, 45, 46, 48, 52, 53, 54, 55, 58, 60, 61, 62, 63, 64, 66];     38 M xor r31, r30, r31;        B xor r0, r6, r0
- register choice: initialize substitution view before round constants: 98.77612%; src 0x430 base 0x430 insns 268/268; diffs 55: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 45, 48, 49];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
Retained best candidate

## ATERM_814021BC initial instruction differences

Frame and count agree. Most 54 reported differences come from scheduling one aggregate address instruction early and from distinct SSID/global base loads; the final host wait also reverses call-argument setup. Try named aggregate owner view, independent IP view scope, then host-ID argument temporary.

```text
src 0x268 base 0x268 insns 154/154
diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27]
     7 M addi r3, r30, 0
       B addi r30, r30, 0
     9 M li r5, 0x7c4
       B addi r3, r30, 0
    10 M bl 0
       B li r5, 0x7c4
    11 M li r29, 0
       B bl 0
    12 M addi r28, r30, 0
       B li r29, 0
    13 M li r3, 0x514
       B addi r28, r30, 0
    14 M li r5, 0x64
       B li r3, 0x514
    15 M li r0, 4
       B li r5, 0x64
    16 M stw r3, 0x1c(r28)
       B li r0, 4
    17 M addi r3, r28, 8
       B stw r3, 0x1c(r28)
    18 M li r4, 0
       B addi r3, r28, 8
    19 M stw r5, 0x20(r28)
       B li r4, 0
    20 M li r5, 4
       B stw r5, 0x20(r28)
    21 M stw r0, 0x24(r28)
       B li r5, 4
    22 M stw r29, 0(r30)
       B stw r0, 0x24(r28)
    23 M stw r29, 4(r28)
       B stw r29, 0(r30)
    24 M bl 0
       B stw r29, 4(r28)
    25 M addi r3, r28, 0xc
       B bl 0
    26 M li r4, 0
       B addi r3, r28, 0xc
    27 M li r5, 4
       B li r4, 0
    28 M bl 0
       B li r5, 4
    29 M addi r3, r28, 0x10
       B bl 0
    30 M li r4, 0
       B addi r3, r28, 0x10
    31 M li r5, 4
       B li r4, 0
    32 M bl 0
       B li r5, 4
    33 M addi r3, r28, 0x14
       B bl 0
    34 M li r4, 0
       B addi r3, r28, 0x14
    35 M li r5, 4
       B li r4, 0
    36 M bl 0
       B li r5, 4
    37 M addi r3, r28, 0x18
       B bl 0
    38 M li r4, 0
       B addi r3, r28, 0x18
    39 M li r5, 4
       B li r4, 0
    40 M bl 0
       B li r5, 4
    41 M mr r3, r28
       B bl 0
    42 M bl 0
       B mr r3, r28
    43 M addi r3, r28, 0x7c4
       B bl 0
    44 M li r4, 0
       B addi r3, r30, 0x7c4
    45 M li r5, 0x15e
       B li r4, 0
    46 M bl 0
       B li r5, 0x15e
    47 M addi r30, r28, 0x7c4
       B bl 0
    48 M li r0, 1
       B addi r28, r30, 0x7c4
    49 M lis r28, 0
       B li r0, 1
    50 M stb r0, 0(r30)
       B stb r0, 0x7c4(r30)
    51 M addi r3, r28, 0
       B addi r3, r30, 0x924
    52 M sth r29, 2(r30)
       B sth r29, 2(r28)
    53 M stb r29, 4(r30)
       B stb r29, 4(r28)
    54 M sth r29, 0x2a(r30)
       B sth r29, 0x2a(r28)
    56 M sth r3, 0x26(r30)
       B sth r3, 0x26(r28)
    57 M addi r3, r30, 6
       B addi r3, r28, 6
    58 M addi r4, r28, 0
       B addi r4, r30, 0x924
    61 M mr r3, r30
       B mr r3, r28
   139 M bl 0
       B li r3, 0
   140 M mr r31, r3
       B bl 0
   141 M li r3, 0
       B mr r31, r3
```

ATERM_814021BC initial 96.61688%
- local order: named aggregate owner used by both configurations: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- local order: IP view initialized at declaration: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- temporary: converted zero host value belongs to host polling loop: 94.045456%; src 0x274 base 0x268 insns 157/154; --- replace mine 5:8 base 5:8;   M    5 lis r31, 0;   M    6 li r28, 0
Retained best candidate

## ATERMi_AutoConfigThread initial instruction differences

Exactly three differences: NOR destination r0 versus r3; load of global result and arithmetic shift exchange scheduling. Frame and branches match. Try signed mask lifetime, two-stage completed-state expression, then mask held in existing result variable.

```text
src 0xa0 base 0xa0 insns 40/40
diffs 3: [20, 22, 23]
    20 M nor r0, r3, r0
       B nor r3, r3, r0
    22 M srawi r3, r0, 0x1f
       B lwz r0, 0(0)
    23 M lwz r0, 0(0)
       B srawi r3, r3, 0x1f
```

ATERMi_AutoConfigThread initial 94.75%
- temporary: signed mask converted explicitly from unsigned bitwise expression: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- temporary: completed state computed as shift then state offset: 94.0%; src 0xa0 base 0xa0 insns 40/40; diffs 9: [20, 21, 22, 23, 24, 26, 28, 29, 30];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- register choice: completed equality mask reuses local result after publication: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
Retained best candidate

## ATERM_81402A24 initial instruction differences

Target alignment expands to addic/li/and; source uses addi/rlwinm. Descriptor owner points four bytes earlier in target while field views are identical. Target negative scan result has bge/branch instead of source blt. MAC conversion target has six-iteration CTR with conditional colon; source terminal break suppresses CTR. Work branch direction, descriptor owner, then bounded MAC-loop guard.

```text
src 0x410 base 0x41c insns 260/263
--- replace mine 6:7 base 6:7
  M    6 li r25, 0
  B    6 li r4, 0
--- replace mine 8:9 base 8:9
  M    8 li r27, -1
  B    8 li r22, -1
--- replace mine 11:12 base 11:12
  M   11 stw r25, 8(r1)
  B   11 stw r4, 8(r1)
--- replace mine 13:14 base 13:14
  M   13 addi r21, r3, 0x34
  B   13 addi r20, r3, 0x34
--- replace mine 15:16 base 15:16
  M   15 mr r3, r21
  B   15 mr r3, r20
--- replace mine 19:20 base 19:20
  M   19 mr r26, r3
  B   19 mr r19, r3
--- replace mine 21:22 base 21:22
  M   21 mr r5, r21
  B   21 mr r5, r20
--- replace mine 24:26 base 24:26
  M   24 cmpwi r26, 0
  M   25 beq 836
  B   24 cmpwi r19, 0
  B   25 beq 848
--- replace mine 27:28 base 27:28
  M   27 mr r3, r21
  B   27 mr r3, r20
--- replace mine 31:32 base 31:32
  M   31 mr r25, r3
  B   31 mr r18, r3
--- replace mine 33:34 base 33:34
  M   33 mr r5, r21
  B   33 mr r5, r20
--- replace mine 36:38 base 36:38
  M   36 cmpwi r25, 0
  M   37 beq 788
  B   36 cmpwi r18, 0
  B   37 beq 800
--- replace mine 40:42 base 40:42
  M   40 slwi r20, r0, 8
  M   41 addi r3, r20, 0x40
  B   40 slwi r15, r0, 8
  B   41 addi r3, r15, 0x40
--- replace mine 44:45 base 44:47
  M   44 addi r0, r3, 0x1f
  B   44 addic r4, r3, 0x1f
  B   45 li r0, -0x20
  B   46 and r16, r4, r0
--- delete mine 46:47 base 48:48
  M   46 rlwinm r24, r0, 0, 0, 0x1a
--- replace mine 48:49 base 49:51
  M   48 addi r23, r24, 2
  B   49 li r23, 0
  B   50 addi r27, r16, 2
--- replace mine 53:54 base 55:56
  M   53 b 608
  B   55 b 620
--- replace mine 62:66 base 64:68
  M   62 cmplw r0, r4
  M   63 ble 588
  M   64 mr r3, r24
  M   65 mr r4, r20
  B   64 cmplw r4, r0
  B   65 bge 600
  B   66 mr r3, r16
  B   67 mr r4, r15
--- replace mine 68:70 base 70:73
  M   68 mr r27, r3
  M   69 blt 660
  B   70 mr r22, r3
  B   71 bge 8
  B   72 b 660
--- replace mine 72:73 base 75:76
  M   72 bne 552
  B   75 bne 560
--- replace mine 76:77 base 79:80
  M   76 li r27, -6
  B   79 li r22, -6
--- replace mine 78:83 base 81:86
  M   78 mr r17, r23
  M   79 addi r16, r26, 8
  M   80 addi r15, r26, 0x2c
  M   81 addi r22, r26, 4
  M   82 li r19, 0
  B   81 mr r17, r27
  B   82 mr r25, r19
  B   83 addi r26, r19, 8
  B   84 addi r24, r19, 0x2c
  B   85 li r21, 0
--- replace mine 84:85 base 87:88
  M   84 mr r3, r16
  B   87 mr r3, r26
--- replace mine 91:92 base 94:95
  M   91 stw r30, 0(r22)
  B   94 stw r30, 4(r25)
--- replace mine 93:96 base 96:99
  M   93 stw r0, 0(r22)
  M   94 lwz r0, 0(r22)
  M   95 mr r3, r15
  B   96 stw r0, 4(r25)
  B   97 lwz r0, 4(r25)
  B   98 mr r3, r24
--- replace mine 98:100 base 101:103
  M   98 add r6, r22, r0
  M   99 stb r30, 4(r6)
  B  101 add r6, r25, r0
  B  102 stb r30, 8(r6)
--- replace mine 102:103 base 105:106
  M  102 sth r0, 0x2e(r22)
  B  105 sth r0, 0x32(r25)
--- replace mine 105:108 base 108:111
  M  105 addi r16, r16, 0x30
  M  106 addi r15, r15, 0x30
  M  107 addi r22, r22, 0x30
  B  108 addi r26, r26, 0x30
  B  109 addi r25, r25, 0x30
  B  110 addi r24, r24, 0x30
--- replace mine 109:110 base 112:113
  M  109 addi r19, r19, 1
  B  112 addi r21, r21, 1
--- replace mine 111:112 base 114:115
  M  111 cmpw r19, r27
  B  114 cmpw r21, r22
--- replace mine 113:114 base 116:117
  M  113 stw r27, 0(r26)
  B  116 stw r22, 0(r19)
--- replace mine 116:119 base 119:122
  M  116 beq 232
  M  117 mr r3, r26
  M  118 mr r4, r25
  B  119 beq 240
  B  120 mr r3, r19
  B  121 mr r4, r18
--- replace mine 122:123 base 125:126
  M  122 beq 208
  B  125 beq 216
--- replace mine 128:129 base 131:132
  M  128 add r14, r26, r0
  B  131 add r14, r19, r0
--- replace mine 135:136 base 138:140
  M  135 addi r7, r1, 0x18
  B  138 li r0, 6
  B  139 addi r8, r1, 0x18
--- replace mine 137:138 base 141:143
  M  137 li r6, 0
  B  141 li r7, 0
  B  142 li r3, 0x3a
--- replace mine 139:141 base 144:146
  M  139 li r0, 0x3a
  M  140 lbz r3, 0(r5)
  B  144 mtctr r0
  B  145 lbz r0, 0(r5)
--- replace mine 142:145 base 147:150
  M  142 rlwinm r8, r3, 0x1c, 0x1c, 0x1f
  M  143 clrlwi r9, r3, 0x1c
  M  144 cmpwi r8, 9
  B  147 rlwinm r6, r0, 0x1c, 0x1c, 0x1f
  B  148 clrlwi r9, r0, 0x1c
  B  149 cmpwi r6, 9
--- replace mine 146:149 base 151:154
  M  146 addi r3, r8, 0x30
  M  147 addi r8, r7, 1
  M  148 stb r3, 0(r7)
  B  151 addi r0, r6, 0x30
  B  152 addi r6, r8, 1
  B  153 stb r0, 0(r8)
--- replace mine 150:153 base 155:158
  M  150 addi r3, r8, 0x37
  M  151 addi r8, r7, 1
  M  152 stb r3, 0(r7)
  B  155 addi r0, r6, 0x37
  B  156 addi r6, r8, 1
  B  157 stb r0, 0(r8)
--- replace mine 155:156 base 160:172
  M  155 addi r3, r9, 0x30
  B  160 addi r0, r9, 0x30
  B  161 stb r0, 0(r6)
  B  162 addi r6, r6, 1
  B  163 b 16
  B  164 addi r0, r9, 0x37
  B  165 stb r0, 0(r6)
  B  166 addi r6, r6, 1
  B  167 cmpwi r7, 5
  B  168 subf r0, r8, r6
  B  169 stb r4, 0(r6)
  B  170 add r8, r8, r0
  B  171 bge 12
--- delete mine 158:168 base 174:174
  M  158 b 16
  M  159 addi r3, r9, 0x37
  M  160 stb r3, 0(r8)
  M  161 addi r8, r8, 1
  M  162 cmpwi r6, 5
  M  163 subf r3, r7, r8
  M  164 stb r4, 0(r8)
  M  165 add r7, r7, r3
  M  166 beq 20
  M  167 stb r0, 0(r7)
--- replace mine 169:171 base 175:176
  M  169 addi r6, r6, 1
  M  170 b -120
  B  175 bdnz -120
--- replace mine 172:173 base 177:178
  M  172 stb r0, 0(r7)
  B  177 stb r0, 0(r8)
--- replace mine 174:177 base 179:182
  M  174 mr r3, r25
  M  175 mr r4, r26
  M  176 mr r5, r21
  B  179 mr r3, r18
  B  180 mr r4, r19
  B  181 mr r5, r20
--- replace mine 204:206 base 209:211
  M  204 addi r18, r18, 1
  M  205 cmpwi r18, 0x12c
  B  209 addi r23, r23, 1
  B  210 cmpwi r23, 0x12c
--- replace mine 209:214 base 214:217
  M  209 beq -620
  M  210 cmpwi r18, 0x12c
  M  211 blt 12
  M  212 li r27, -3
  M  213 b 84
  B  214 beq -632
  B  215 cmpwi r23, 0x12c
  B  216 bge 56
--- replace mine 227:228 base 230:231
  M  227 li r27, -3
  B  230 li r22, -3
--- replace mine 230:231 base 233:234
  M  230 li r27, 1
  B  233 li r22, 1
--- replace mine 233:234 base 236:237
  M  233 li r27, -8
  B  236 li r22, -8
--- replace mine 241:242 base 244:245
  M  241 cmpwi r26, 0
  B  244 cmpwi r19, 0
--- replace mine 244:245 base 247:248
  M  244 mr r3, r26
  B  247 mr r3, r19
--- replace mine 247:248 base 250:251
  M  247 cmpwi r25, 0
  B  250 cmpwi r18, 0
--- replace mine 250:251 base 253:254
  M  250 mr r3, r25
  B  253 mr r3, r18
--- replace mine 254:255 base 257:258
  M  254 mr r3, r27
  B  257 mr r3, r22
```

ATERM_81402A24 initial 92.41445%
- branch direction: success scan and in-range iteration before error branches: 92.43346%; src 0x410 base 0x41c insns 260/263; --- replace mine 6:7 base 6:7;   M    6 li r25, 0;   B    6 li r4, 0
- loop temporary: bound MAC iteration to six with conditional colon: 83.12928%; src 0x48c base 0x41c insns 291/263; --- replace mine 6:7 base 6:7;   M    6 li r25, 0;   B    6 li r4, 0
- local order: first descriptor initialized at raw scan allocation: 92.41445%; src 0x410 base 0x41c insns 260/263; --- replace mine 6:7 base 6:7;   M    6 li r25, 0;   B    6 li r4, 0
Retained best candidate

## ATERM_814031DC initial instruction differences

Frame agrees; source four instructions short. Both formatting blocks lack the original CTR six-byte traversal. Target places the conditional colon inside the bounded loop rather than terminal break. Try bounded guards and pointer walk that keeps the real six-byte span.

```text
src 0x204 base 0x214 insns 129/133
--- replace mine 47:48 base 47:49
  M   47 beq 304
  B   47 beq 320
  B   48 li r0, 6
--- replace mine 49:51 base 50:53
  M   49 addi r7, r1, 0x38
  M   50 li r6, 0
  B   50 addi r8, r1, 0x38
  B   51 li r7, 0
  B   52 li r3, 0x3a
--- replace mine 52:54 base 54:56
  M   52 li r0, 0x3a
  M   53 lbz r3, 0(r5)
  B   54 mtctr r0
  B   55 lbz r0, 0(r5)
--- replace mine 55:58 base 57:60
  M   55 rlwinm r8, r3, 0x1c, 0x1c, 0x1f
  M   56 clrlwi r9, r3, 0x1c
  M   57 cmpwi r8, 9
  B   57 rlwinm r6, r0, 0x1c, 0x1c, 0x1f
  B   58 clrlwi r9, r0, 0x1c
  B   59 cmpwi r6, 9
--- replace mine 59:62 base 61:64
  M   59 addi r3, r8, 0x30
  M   60 addi r8, r7, 1
  M   61 stb r3, 0(r7)
  B   61 addi r0, r6, 0x30
  B   62 addi r6, r8, 1
  B   63 stb r0, 0(r8)
--- replace mine 63:66 base 65:68
  M   63 addi r3, r8, 0x37
  M   64 addi r8, r7, 1
  M   65 stb r3, 0(r7)
  B   65 addi r0, r6, 0x37
  B   66 addi r6, r8, 1
  B   67 stb r0, 0(r8)
--- replace mine 68:69 base 70:82
  M   68 addi r3, r9, 0x30
  B   70 addi r0, r9, 0x30
  B   71 stb r0, 0(r6)
  B   72 addi r6, r6, 1
  B   73 b 16
  B   74 addi r0, r9, 0x37
  B   75 stb r0, 0(r6)
  B   76 addi r6, r6, 1
  B   77 cmpwi r7, 5
  B   78 subf r0, r8, r6
  B   79 stb r4, 0(r6)
  B   80 add r8, r8, r0
  B   81 bge 12
--- insert mine 71:71 base 84:103
  B   84 addi r7, r7, 1
  B   85 bdnz -120
  B   86 li r4, 0
  B   87 li r0, 6
  B   88 stb r4, 0(r8)
  B   89 addi r5, r1, 0x10
  B   90 addi r8, r1, 0x18
  B   91 li r7, 0
  B   92 li r3, 0x3a
  B   93 mtctr r0
  B   94 lbz r0, 0(r5)
  B   95 addi r5, r5, 1
  B   96 rlwinm r6, r0, 0x1c, 0x1c, 0x1f
  B   97 clrlwi r9, r0, 0x1c
  B   98 cmpwi r6, 9
  B   99 bgt 20
  B  100 addi r0, r6, 0x30
  B  101 addi r6, r8, 1
  B  102 stb r0, 0(r8)
--- replace mine 72:73 base 104:121
  M   72 addi r3, r9, 0x37
  B  104 addi r0, r6, 0x37
  B  105 addi r6, r8, 1
  B  106 stb r0, 0(r8)
  B  107 cmpwi r9, 9
  B  108 bgt 20
  B  109 addi r0, r9, 0x30
  B  110 stb r0, 0(r6)
  B  111 addi r6, r6, 1
  B  112 b 16
  B  113 addi r0, r9, 0x37
  B  114 stb r0, 0(r6)
  B  115 addi r6, r6, 1
  B  116 cmpwi r7, 5
  B  117 subf r0, r8, r6
  B  118 stb r4, 0(r6)
  B  119 add r8, r8, r0
  B  120 bge 12
--- delete mine 75:81 base 123:123
  M   75 cmpwi r6, 5
  M   76 subf r3, r7, r8
  M   77 stb r4, 0(r8)
  M   78 add r7, r7, r3
  M   79 beq 20
  M   80 stb r0, 0(r7)
--- replace mine 82:121 base 124:125
  M   82 addi r6, r6, 1
  M   83 b -120
  M   84 li r4, 0
  M   85 addi r5, r1, 0x10
  M   86 stb r4, 0(r7)
  M   87 addi r7, r1, 0x18
  M   88 li r6, 0
  M   89 li r0, 0x3a
  M   90 lbz r3, 0(r5)
  M   91 addi r5, r5, 1
  M   92 rlwinm r8, r3, 0x1c, 0x1c, 0x1f
  M   93 clrlwi r9, r3, 0x1c
  M   94 cmpwi r8, 9
  M   95 bgt 20
  M   96 addi r3, r8, 0x30
  M   97 addi r8, r7, 1
  M   98 stb r3, 0(r7)
  M   99 b 16
  M  100 addi r3, r8, 0x37
  M  101 addi r8, r7, 1
  M  102 stb r3, 0(r7)
  M  103 cmpwi r9, 9
  M  104 bgt 20
  M  105 addi r3, r9, 0x30
  M  106 stb r3, 0(r8)
  M  107 addi r8, r8, 1
  M  108 b 16
  M  109 addi r3, r9, 0x37
  M  110 stb r3, 0(r8)
  M  111 addi r8, r8, 1
  M  112 cmpwi r6, 5
  M  113 subf r3, r7, r8
  M  114 stb r4, 0(r8)
  M  115 add r7, r7, r3
  M  116 beq 20
  M  117 stb r0, 0(r7)
  M  118 addi r7, r7, 1
  M  119 addi r6, r6, 1
  M  120 b -120
  B  124 bdnz -120
--- replace mine 122:123 base 126:127
  M  122 stb r0, 0(r7)
  B  126 stb r0, 0(r8)
```

ATERM_814031DC initial 90.766914%
- loop guard: six-byte bound and conditional colon before last byte: 53.969925%; src 0x2fc base 0x214 insns 191/133; --- replace mine 47:49 base 47:49;   M   47 beq 552;   M   48 li r0, 3
- branch direction: colon condition as non-final index: 53.894737%; src 0x2fc base 0x214 insns 191/133; --- replace mine 47:49 base 47:49;   M   47 beq 552;   M   48 li r0, 3
- temporary: six-byte unsigned traversal count: 51.097744%; src 0x2fc base 0x214 insns 191/133; --- replace mine 47:49 base 47:49;   M   47 beq 552;   M   48 li r0, 3
Retained best candidate

## ATERM_81405ACC initial instruction differences

Initial counter update and transform loop agree. First byte-copy body has lbzx/add followed by hoisted alternating loads, versus target incrementing read cursor and interleaved stores. Both destination cursors retain constant 0x18 at stores; target forms the named buffer address once. Frame agrees; five instructions short. Try array buffer alias, then mixed source cursor/index, then full named destination/source cursor with counted loop.

```text
src 0x22c base 0x240 insns 139/144
--- replace mine 26:27 base 26:27
  M   26 blt 232
  B   26 blt 244
--- replace mine 28:30 base 28:30
  M   28 li r9, 0
  M   29 beq 168
  B   28 li r7, 0
  B   29 beq 180
--- replace mine 31:35 base 31:35
  M   31 addi r6, r31, -8
  M   32 ble 108
  M   33 addi r5, r6, 7
  M   34 add r7, r3, r0
  B   31 addi r8, r31, -8
  B   32 ble 116
  B   33 addi r5, r8, 7
  B   34 add r6, r3, r0
--- insert mine 36:36 base 36:38
  B   36 mr r9, r29
  B   37 addi r6, r6, 0x18
--- replace mine 37:38 base 39:40
  M   37 cmplwi r6, 0
  B   39 cmplwi r8, 0
--- replace mine 39:42 base 41:57
  M   39 lbzx r6, r4, r9
  M   40 add r8, r4, r9
  M   41 lbz r5, 1(r8)
  B   41 lbz r5, 0(r9)
  B   42 addi r7, r7, 8
  B   43 stb r5, 0(r6)
  B   44 lbz r5, 1(r9)
  B   45 stb r5, 1(r6)
  B   46 lbz r5, 2(r9)
  B   47 stb r5, 2(r6)
  B   48 lbz r5, 3(r9)
  B   49 stb r5, 3(r6)
  B   50 lbz r5, 4(r9)
  B   51 stb r5, 4(r6)
  B   52 lbz r5, 5(r9)
  B   53 stb r5, 5(r6)
  B   54 lbz r5, 6(r9)
  B   55 stb r5, 6(r6)
  B   56 lbz r5, 7(r9)
--- replace mine 43:58 base 58:60
  M   43 stb r6, 0x18(r7)
  M   44 lbz r6, 2(r8)
  M   45 stb r5, 0x19(r7)
  M   46 lbz r5, 3(r8)
  M   47 stb r6, 0x1a(r7)
  M   48 lbz r6, 4(r8)
  M   49 stb r5, 0x1b(r7)
  M   50 lbz r5, 5(r8)
  M   51 stb r6, 0x1c(r7)
  M   52 lbz r6, 6(r8)
  M   53 stb r5, 0x1d(r7)
  M   54 lbz r5, 7(r8)
  M   55 stb r6, 0x1e(r7)
  M   56 stb r5, 0x1f(r7)
  M   57 addi r7, r7, 8
  B   58 stb r5, 7(r6)
  B   59 addi r6, r6, 8
--- replace mine 60:63 base 62:66
  M   60 subf r0, r9, r31
  M   61 add r5, r9, r3
  M   62 add r3, r4, r9
  B   62 subf r0, r7, r31
  B   63 add r3, r3, r7
  B   64 add r4, r4, r7
  B   65 addi r3, r3, 0x18
--- replace mine 64:65 base 67:68
  M   64 cmplw r9, r31
  B   67 cmplw r7, r31
--- replace mine 66:67 base 69:72
  M   66 lbz r0, 0(r3)
  B   69 lbz r0, 0(r4)
  B   70 addi r4, r4, 1
  B   71 stb r0, 0(r3)
--- delete mine 68:70 base 73:73
  M   68 stb r0, 0x18(r5)
  M   69 addi r5, r5, 1
--- replace mine 85:93 base 88:96
  M   85 subf. r7, r31, r30
  M   86 li r8, 0
  M   87 beq 176
  M   88 cmplwi r7, 8
  M   89 addi r4, r7, -8
  M   90 ble 112
  M   91 addi r3, r4, 7
  M   92 add r5, r29, r31
  B   88 subf. r8, r31, r30
  B   89 li r5, 0
  B   90 beq 184
  B   91 cmplwi r8, 8
  B   92 addi r6, r8, -8
  B   93 ble 116
  B   94 addi r3, r6, 7
  B   95 add r4, r28, r0
--- replace mine 94:95 base 97:99
  M   94 add r6, r28, r0
  B   97 add r7, r29, r31
  B   98 addi r4, r4, 0x18
--- replace mine 96:97 base 100:101
  M   96 cmplwi r4, 0
  B  100 cmplwi r6, 0
--- replace mine 98:113 base 102:103
  M   98 lbz r4, 0(r5)
  M   99 addi r8, r8, 8
  M  100 lbz r3, 1(r5)
  M  101 stb r4, 0x18(r6)
  M  102 lbz r4, 2(r5)
  M  103 stb r3, 0x19(r6)
  M  104 lbz r3, 3(r5)
  M  105 stb r4, 0x1a(r6)
  M  106 lbz r4, 4(r5)
  M  107 stb r3, 0x1b(r6)
  M  108 lbz r3, 5(r5)
  M  109 stb r4, 0x1c(r6)
  M  110 lbz r4, 6(r5)
  M  111 stb r3, 0x1d(r6)
  M  112 lbz r3, 7(r5)
  B  102 lbz r3, 0(r7)
--- replace mine 114:117 base 104:121
  M  114 stb r4, 0x1e(r6)
  M  115 stb r3, 0x1f(r6)
  M  116 addi r6, r6, 8
  B  104 stb r3, 0(r4)
  B  105 lbz r3, 1(r7)
  B  106 stb r3, 1(r4)
  B  107 lbz r3, 2(r7)
  B  108 stb r3, 2(r4)
  B  109 lbz r3, 3(r7)
  B  110 stb r3, 3(r4)
  B  111 lbz r3, 4(r7)
  B  112 stb r3, 4(r4)
  B  113 lbz r3, 5(r7)
  B  114 stb r3, 5(r4)
  B  115 lbz r3, 6(r7)
  B  116 stb r3, 6(r4)
  B  117 lbz r3, 7(r7)
  B  118 addi r7, r7, 8
  B  119 stb r3, 7(r4)
  B  120 addi r4, r4, 8
--- replace mine 118:119 base 122:123
  M  118 add r3, r28, r0
  B  122 add r0, r28, r0
--- replace mine 120:123 base 124:128
  M  120 subf r0, r8, r7
  M  121 add r4, r8, r4
  M  122 add r3, r8, r3
  B  124 add r3, r0, r5
  B  125 subf r0, r5, r8
  B  126 add r4, r5, r4
  B  127 addi r3, r3, 0x18
--- replace mine 124:125 base 129:130
  M  124 cmplw r8, r7
  B  129 cmplw r5, r8
--- replace mine 128:129 base 133:134
  M  128 stb r0, 0x18(r3)
  B  133 stb r0, 0(r3)
```

ATERM_81405ACC initial 88.583336%
- temporary: named buffer field byte view independent of context owner: 80.02778%; src 0x220 base 0x240 insns 136/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:5 base 4:11
- temporary: indexed destination and incrementing read cursor: 71.96528%; src 0x224 base 0x240 insns 137/144; --- delete mine 5:6 base 5:5;   M    5 mr r31, r4; --- insert mine 7:7 base 6:7
- local order: mixed copy cursor declarations destination first: 71.96528%; src 0x224 base 0x240 insns 137/144; --- delete mine 5:6 base 5:5;   M    5 mr r31, r4; --- insert mine 7:7 base 6:7
Retained best candidate

ATERM_814031DC initial 90.766914%
- loop guard: equality termination keeps conditional colon inside counted loop: 53.969925%; src 0x2fc base 0x214 insns 191/133; --- replace mine 47:49 base 47:49;   M   47 beq 552;   M   48 li r0, 3
- loop guard: inclusive sixth-byte traversal: 53.969925%; src 0x2fc base 0x214 insns 191/133; --- replace mine 47:49 base 47:49;   M   47 beq 552;   M   48 li r0, 3
- loop guard: descending remaining length with forward index: 90.37594%; src 0x21c base 0x214 insns 135/133; --- replace mine 47:48 base 47:49;   M   47 beq 328;   B   47 beq 320
Retained best candidate

## ATERM_814038C8 initial instruction differences

Block-by-block disassembly: both frames are 0x180 and save r14..31. Wait queue/alarm offsets 0x78/0x98 match; wait buffer is 0x14 versus target 0x0c. Initialization has extra module-base spills at 0x12c and reciprocal at 0x130 versus target reciprocal at 0x12c. Target binds header/challenge/key directly from one module base; source keeps several ConfigurationResult subviews. All protocol cases exist, but 27 extra instructions remain, mainly alias publication, digest/options temporaries and loop scheduling. Start with wait-local order, then digest scope, then connection-key alias lifetime.

```text
src 0xf48 base 0xedc insns 978/951
--- replace mine 5:7 base 5:11
  M    5 lis r0, 0
  M    6 lis r27, 0x1062
  B    5 li r0, 1
  B    6 lis r20, 0x1062
  B    7 lis r18, 0
  B    8 stw r0, 0(0)
  B    9 addi r18, r18, 0
  B   10 addi r0, r20, 0x4dd3
--- replace mine 8:26 base 12:15
  M    8 li r0, 1
  M    9 li r22, 0
  M   10 li r21, -5
  M   11 lwz r3, 0x12c(r1)
  M   12 li r20, 0
  M   13 stw r0, 0(0)
  M   14 addi r0, r27, 0x4dd3
  M   15 addi r3, r3, 0
  M   16 li r19, 0
  M   17 stw r3, 0x12c(r1)
  M   18 addi r26, r3, 0xba0
  M   19 addi r3, r3, 0x14a0
  M   20 li r18, 0
  M   21 stw r0, 0x130(r1)
  M   22 addi r25, r26, 0x8f8
  M   23 lwz r31, 0x12c(r1)
  M   24 addi r24, r26, 0xe8
  M   25 addi r23, r3, 0x7f8
  B   12 addi r31, r18, 0x1498
  B   13 addi r15, r18, 0xc98
  B   14 addi r25, r18, 0x1c98
--- replace mine 27:31 base 16:27
  M   27 lis r28, -0x8000
  M   28 li r29, -1
  M   29 li r14, 8
  M   30 b 3712
  B   16 li r29, -5
  B   17 li r28, 0
  B   18 li r27, 0
  B   19 li r26, 0
  B   20 li r24, 0
  B   21 lis r19, -0x8000
  B   22 li r21, -1
  B   23 li r22, 8
  B   24 li r23, 2
  B   25 lis r14, 1
  B   26 b 3620
--- replace mine 32:33 base 28:29
  M   32 addi r4, r1, 0x14
  B   28 addi r4, r1, 0xc
--- replace mine 40:41 base 36:37
  M   40 lwz r0, 0xf8(r28)
  B   36 lwz r0, 0xf8(r19)
--- replace mine 45:46 base 41:42
  M   45 lwz r0, 0x130(r1)
  B   41 lwz r0, 0x12c(r1)
--- replace mine 57:58 base 53:54
  M   57 bgt 3604
  B   53 bgt 3512
--- replace mine 66:67 base 62:63
  M   66 mr r21, r3
  B   62 mr r29, r3
--- replace mine 68:70 base 64:66
  M   68 li r20, 1
  M   69 b 3556
  B   64 li r26, 1
  B   65 b 3464
--- replace mine 78:79 base 74:75
  M   78 stw r29, 0x6c(r1)
  B   74 stw r21, 0x6c(r1)
--- replace mine 81:83 base 77:79
  M   81 lwz r0, 0xf8(r28)
  M   82 addi r6, r27, 0x4dd3
  B   77 lwz r0, 0xf8(r19)
  B   78 addi r6, r20, 0x4dd3
--- replace mine 97:100 base 93:95
  M   97 li r0, 2
  M   98 stw r0, 0(0)
  M   99 b 3436
  B   93 stw r23, 0(0)
  B   94 b 3348
--- replace mine 102:103 base 97:98
  M  102 mr r21, r3
  B   97 mr r29, r3
--- replace mine 104:106 base 99:101
  M  104 li r20, 1
  M  105 b 3412
  B   99 li r26, 1
  B  100 b 3324
--- replace mine 107:109 base 102:104
  M  107 lwz r0, 0xf8(r28)
  M  108 addi r6, r27, 0x4dd3
  B  102 lwz r0, 0xf8(r19)
  B  103 addi r6, r20, 0x4dd3
--- replace mine 119:121 base 114:116
  M  119 lwz r0, 0xf8(r28)
  M  120 addi r6, r27, 0x4dd3
  B  114 lwz r0, 0xf8(r19)
  B  115 addi r6, r20, 0x4dd3
--- replace mine 130:131 base 125:126
  M  130 b 3312
  B  125 b 3224
--- replace mine 136:137 base 131:132
  M  136 mr r22, r3
  B  131 mr r30, r3
--- replace mine 138:141 base 133:136
  M  138 li r21, -2
  M  139 li r20, 1
  M  140 b 3272
  B  133 li r29, -2
  B  134 li r26, 1
  B  135 b 3184
--- replace mine 145:148 base 140:142
  M  145 lis r3, 1
  M  146 stb r14, 0x48(r1)
  M  147 addi r0, r3, -0x19ff
  B  140 addi r0, r14, -0x19ff
  B  141 stb r22, 0x48(r1)
--- replace mine 149:151 base 143:144
  M  149 li r0, 2
  M  150 stb r0, 0x49(r1)
  B  143 stb r23, 0x49(r1)
--- replace mine 153:154 base 146:147
  M  153 mr r3, r22
  B  146 mr r3, r30
--- replace mine 155:156 base 148:149
  M  155 stw r30, 0x4c(r1)
  B  148 stw r24, 0x4c(r1)
--- replace mine 158:159 base 151:152
  M  158 mr r21, r3
  B  151 mr r29, r3
--- replace mine 160:163 base 153:156
  M  160 li r21, -2
  M  161 li r20, 1
  M  162 b 3184
  B  153 li r29, -2
  B  154 li r26, 1
  B  155 b 3104
--- replace mine 165:166 base 158:159
  M  165 b 3172
  B  158 b 3092
--- replace mine 167:169 base 160:162
  M  167 lwz r0, 0xf8(r28)
  M  168 addi r6, r27, 0x4dd3
  B  160 lwz r0, 0xf8(r19)
  B  161 addi r6, r20, 0x4dd3
--- replace mine 177:178 base 170:171
  M  177 mr r3, r22
  B  170 mr r3, r30
--- replace mine 179:184 base 172:178
  M  179 li r21, -3
  M  180 li r20, 1
  M  181 b 3108
  M  182 stb r14, 0x40(r1)
  M  183 mr r3, r24
  B  172 li r29, -3
  B  173 li r26, 1
  B  174 b 3028
  B  175 stb r22, 0x40(r1)
  B  176 addi r3, r18, 0xc88
  B  177 addi r4, r1, 0x40
--- replace mine 185:187 base 179:181
  M  185 mr r3, r22
  M  186 addi r4, r26, 0xf8
  B  179 mr r3, r30
  B  180 addi r4, r18, 0xc98
--- replace mine 192:194 base 186:188
  M  192 ble 3064
  M  193 addi r3, r26, 0xf8
  B  186 ble 2980
  B  187 addi r3, r18, 0xc98
--- replace mine 197:198 base 191:192
  M  197 beq 3044
  B  191 beq 2960
--- replace mine 199:201 base 193:195
  M  199 lwz r0, 0xf8(r28)
  M  200 addi r6, r27, 0x4dd3
  B  193 lwz r0, 0xf8(r19)
  B  194 addi r6, r20, 0x4dd3
--- replace mine 217:218 base 211:212
  M  217 stw r29, 0x60(r1)
  B  211 stw r21, 0x60(r1)
--- replace mine 220:222 base 214:216
  M  220 lwz r0, 0xf8(r28)
  M  221 addi r6, r27, 0x4dd3
  B  214 lwz r0, 0xf8(r19)
  B  215 addi r6, r20, 0x4dd3
--- replace mine 236:237 base 230:238
  M  236 b 2888
  B  230 b 2804
  B  231 lwz r16, 0(0)
  B  232 li r3, 1
  B  233 bl 0
  B  234 lbz r11, 0(0)
  B  235 li r4, 0
  B  236 lbz r10, 0(0)
  B  237 li r5, 4
--- delete mine 238:239 base 239:239
  M  238 li r3, 1
--- delete mine 242:244 base 242:242
  M  242 lbz r5, 0(0)
  M  243 lbz r4, 0(0)
--- replace mine 245:253 base 243:252
  M  245 stb r9, 0x30(r1)
  M  246 lwz r15, 0(0)
  M  247 stb r8, 0x31(r1)
  M  248 stb r7, 0x32(r1)
  M  249 stb r6, 0x33(r1)
  M  250 stb r5, 0x34(r1)
  M  251 stb r4, 0x35(r1)
  M  252 stb r0, 0x36(r1)
  B  243 sth r3, 8(r1)
  B  244 mr r3, r16
  B  245 stb r11, 0x38(r1)
  B  246 stb r10, 0x39(r1)
  B  247 stb r9, 0x3a(r1)
  B  248 stb r8, 0x3b(r1)
  B  249 stb r7, 0x3c(r1)
  B  250 stb r6, 0x3d(r1)
  B  251 stb r0, 0x3e(r1)
--- replace mine 254:256 base 253:260
  M  254 sth r3, 8(r1)
  M  255 mr r3, r15
  B  253 li r3, 1
  B  254 bl 0
  B  255 sth r3, 0(r16)
  B  256 li r3, 2
  B  257 bl 0
  B  258 sth r3, 2(r16)
  B  259 addi r3, r16, 4
--- replace mine 259:270 base 263:264
  M  259 li r3, 1
  M  260 bl 0
  M  261 sth r3, 0(r15)
  M  262 li r3, 2
  M  263 bl 0
  M  264 sth r3, 2(r15)
  M  265 addi r3, r15, 4
  M  266 li r4, 0
  M  267 li r5, 4
  M  268 bl 0
  M  269 addi r3, r15, 4
  B  263 addi r3, r16, 4
--- replace mine 273:274 base 267:268
  M  273 addi r3, r15, 8
  B  267 addi r17, r16, 8
--- insert mine 275:275 base 269:270
  B  269 mr r3, r17
--- replace mine 279:280 base 274:275
  M  279 sth r3, 8(r15)
  B  274 sth r3, 0(r17)
--- replace mine 282:284 base 277:279
  M  282 sth r3, 0xa(r15)
  M  283 addi r3, r15, 0xc
  B  277 sth r3, 2(r17)
  B  278 addi r3, r17, 4
--- replace mine 287:288 base 282:283
  M  287 addi r3, r15, 0xc
  B  282 addi r3, r17, 4
--- replace mine 292:293 base 287:288
  M  292 addi r15, r15, 0x10
  B  287 addi r16, r17, 8
--- replace mine 295:296 base 290:291
  M  295 mr r3, r15
  B  290 mr r3, r16
--- replace mine 301:302 base 296:297
  M  301 sth r3, 0(r15)
  B  296 sth r3, 0(r16)
--- replace mine 304:306 base 299:301
  M  304 sth r3, 2(r15)
  M  305 addi r3, r15, 4
  B  299 sth r3, 2(r16)
  B  300 addi r3, r17, 0xc
--- replace mine 309:310 base 304:305
  M  309 addi r3, r15, 4
  B  304 addi r3, r17, 0xc
--- replace mine 313:315 base 308:311
  M  313 addi r15, r15, 8
  M  314 mr r3, r15
  B  308 addi r16, r17, 0x10
  B  309 mr r17, r16
  B  310 mr r3, r16
--- replace mine 320:321 base 316:317
  M  320 sth r3, 0(r15)
  B  316 sth r3, 0(r16)
--- replace mine 323:325 base 319:321
  M  323 sth r3, 2(r15)
  M  324 addi r3, r15, 4
  B  319 sth r3, 2(r16)
  B  320 addi r3, r16, 4
--- replace mine 328:330 base 324:326
  M  328 addi r3, r15, 4
  M  329 addi r4, r1, 0x30
  B  324 addi r3, r16, 4
  B  325 addi r4, r1, 0x38
--- replace mine 333:334 base 329:330
  M  333 addi r15, r15, 0x10
  B  329 addi r16, r16, 0x10
--- replace mine 335:337 base 331:333
  M  335 beq 80
  M  336 mr r3, r15
  B  331 beq 84
  B  332 addi r16, r17, 0x10
--- insert mine 338:338 base 334:335
  B  334 mr r3, r16
--- replace mine 342:343 base 339:340
  M  342 sth r3, 0(r15)
  B  339 sth r3, 0(r16)
--- replace mine 345:347 base 342:344
  M  345 sth r3, 2(r15)
  M  346 addi r3, r15, 4
  B  342 sth r3, 2(r16)
  B  343 addi r3, r17, 0x14
--- replace mine 350:351 base 347:348
  M  350 addi r3, r15, 4
  B  347 addi r3, r17, 0x14
--- replace mine 354:355 base 351:352
  M  354 addi r15, r15, 0x10
  B  351 addi r16, r17, 0x20
--- replace mine 356:358 base 353:355
  M  356 mr r5, r25
  M  357 addi r3, r26, 0xf8
  B  353 addi r3, r18, 0xc98
  B  354 addi r5, r18, 0x1498
--- replace mine 359:360 base 356:357
  M  359 subf r6, r0, r15
  B  356 subf r6, r0, r16
--- replace mine 364:366 base 361:364
  M  364 lis r3, 1
  M  365 addi r0, r3, -0x19ff
  B  361 addi r0, r14, -0x19ff
  B  362 mr r16, r3
  B  363 stb r22, 0x30(r1)
--- replace mine 367:371 base 365:367
  M  367 stb r14, 0x28(r1)
  M  368 li r0, 2
  M  369 stb r0, 0x29(r1)
  M  370 stw r29, 0x2c(r1)
  B  365 stb r23, 0x31(r1)
  B  366 stw r21, 0x34(r1)
--- replace mine 372:377 base 368:373
  M  372 sth r3, 0x2a(r1)
  M  373 mr r3, r22
  M  374 lwz r5, 0(0)
  M  375 addi r4, r26, 0xf8
  M  376 addi r7, r1, 0x28
  B  368 sth r3, 0x32(r1)
  B  369 mr r3, r30
  B  370 mr r5, r16
  B  371 addi r4, r18, 0xc98
  B  372 addi r7, r1, 0x30
--- replace mine 380:382 base 376:378
  M  380 lwz r0, 0xf8(r28)
  M  381 addi r6, r27, 0x4dd3
  B  376 lwz r0, 0xf8(r19)
  B  377 addi r6, r20, 0x4dd3
--- replace mine 388:389 base 384:385
  M  388 mr r18, r4
  B  384 mr r28, r4
--- replace mine 390:391 base 386:387
  M  390 b 2272
  B  386 b 2180
--- replace mine 392:394 base 388:390
  M  392 lwz r0, 0xf8(r28)
  M  393 addi r6, r27, 0x4dd3
  B  388 lwz r0, 0xf8(r19)
  B  389 addi r6, r20, 0x4dd3
--- replace mine 402:403 base 398:399
  M  402 mr r3, r22
  B  398 mr r3, r30
--- replace mine 404:409 base 400:405
  M  404 li r21, -4
  M  405 li r20, 1
  M  406 b 2208
  M  407 mr r3, r22
  M  408 addi r4, r26, 0xf8
  B  400 li r29, -4
  B  401 li r26, 1
  B  402 b 2116
  B  403 mr r3, r30
  B  404 addi r4, r18, 0xc98
--- replace mine 414:417 base 410:413
  M  414 ble 956
  M  415 lhz r3, 0xf8(r26)
  M  416 addi r15, r26, 0xf8
  B  410 ble 888
  B  411 lhz r3, 0(r15)
  B  412 li r17, 0
--- replace mine 422:432 base 418:426
  M  422 clrlwi r17, r3, 0x10
  M  423 mr r3, r15
  M  424 add r4, r15, r17
  M  425 addi r15, r15, 6
  M  426 addi r4, r4, 6
  M  427 li r16, 0
  M  428 cmplw cr1, r3, r4
  M  429 bge -7575
  M  430 subf r0, r3, r4
  M  431 addi r5, r4, -8
  B  418 clrlwi r16, r3, 0x10
  B  419 mr r4, r15
  B  420 add r3, r15, r16
  B  421 addi r3, r3, 6
  B  422 cmplw cr1, r15, r3
  B  423 bge -7579
  B  424 subf r0, r15, r3
  B  425 addi r5, r3, -8
--- replace mine 434:435 base 428:429
  M  434 bgt -7595
  B  428 bgt -7599
--- replace mine 436:437 base 430:431
  M  436 subf r0, r3, r0
  B  430 subf r0, r15, r0
--- replace mine 439:440 base 433:434
  M  439 cmplw r3, r5
  B  433 cmplw r15, r5
--- replace mine 441:458 base 435:452
  M  441 lbz r5, 0(r3)
  M  442 lbz r0, 1(r3)
  M  443 add r16, r16, r5
  M  444 lbz r5, 2(r3)
  M  445 add r16, r16, r0
  M  446 lbz r0, 3(r3)
  M  447 add r16, r16, r5
  M  448 lbz r5, 4(r3)
  M  449 add r16, r16, r0
  M  450 lbz r0, 5(r3)
  M  451 add r16, r16, r5
  M  452 lbz r5, 6(r3)
  M  453 add r16, r16, r0
  M  454 lbz r0, 7(r3)
  M  455 add r16, r16, r5
  M  456 addi r3, r3, 8
  M  457 add r16, r16, r0
  B  435 lbz r5, 0(r4)
  B  436 lbz r0, 1(r4)
  B  437 add r17, r17, r5
  B  438 lbz r5, 2(r4)
  B  439 add r17, r17, r0
  B  440 lbz r0, 3(r4)
  B  441 add r17, r17, r5
  B  442 lbz r5, 4(r4)
  B  443 add r17, r17, r0
  B  444 lbz r0, 5(r4)
  B  445 add r17, r17, r5
  B  446 lbz r5, 6(r4)
  B  447 add r17, r17, r0
  B  448 lbz r0, 7(r4)
  B  449 add r17, r17, r5
  B  450 addi r4, r4, 8
  B  451 add r17, r17, r0
--- replace mine 459:460 base 453:454
  M  459 subf r0, r3, r4
  B  453 subf r0, r4, r3
--- replace mine 461:462 base 455:456
  M  461 cmplw r3, r4
  B  455 cmplw r4, r3
--- replace mine 463:466 base 457:460
  M  463 lbz r0, 0(r3)
  M  464 addi r3, r3, 1
  M  465 add r16, r16, r0
  B  457 lbz r0, 0(r4)
  B  458 addi r4, r4, 1
  B  459 add r17, r17, r0
--- replace mine 467:468 base 461:462
  M  467 lhz r3, 0(r4)
  B  461 lhz r3, 0(r3)
--- replace mine 470:471 base 464:465
  M  470 clrlwi r0, r16, 0x10
  B  464 clrlwi r0, r17, 0x10
--- insert mine 472:472 base 466:467
  B  466 addi r4, r15, 6
--- replace mine 473:475 base 468:470
  M  473 li r15, 0
  M  474 cmpwi r15, 0
  B  468 li r4, 0
  B  469 cmpwi r4, 0
--- replace mine 476:478 base 471:473
  M  476 li r17, 0
  M  477 b 80
  B  471 li r16, 0
  B  472 b 72
--- replace mine 481:489 base 476:483
  M  481 li r17, 0
  M  482 b 60
  M  483 cmpwi r24, 0
  M  484 beq 36
  M  485 mr r3, r25
  M  486 mr r4, r15
  M  487 mr r5, r17
  M  488 mr r6, r24
  B  476 li r16, 0
  B  477 b 52
  B  478 addic. r0, r18, 0xc88
  B  479 beq 32
  B  480 mr r5, r16
  B  481 mr r6, r0
  B  482 addi r3, r18, 0x1498
--- replace mine 491:496 base 485:489
  M  491 addi r17, r17, -8
  M  492 b 20
  M  493 mr r3, r25
  M  494 mr r4, r15
  M  495 mr r5, r17
  B  485 addi r16, r16, -8
  B  486 b 16
  B  487 mr r5, r16
  B  488 addi r3, r18, 0x1498
--- replace mine 497:501 base 490:494
  M  497 cmpwi r17, 0
  M  498 beq 620
  M  499 lhz r3, 0(r25)
  M  500 addi r15, r25, 8
  B  490 cmpwi r16, 0
  B  491 beq 564
  B  492 lhz r3, 0x1498(r18)
  B  493 addi r16, r31, 8
--- replace mine 503:505 base 496:498
  M  503 add r0, r15, r0
  M  504 cmplw r15, r0
  B  496 add r0, r16, r0
  B  497 cmplw r16, r0
--- replace mine 506:507 base 499:500
  M  506 li r15, 0
  B  499 li r16, 0
--- replace mine 508:509 base 501:502
  M  508 lhz r3, 0(r15)
  B  501 lhz r3, 0(r16)
--- replace mine 511:513 base 504:506
  M  511 lhz r3, 2(r15)
  M  512 stw r0, 0x124(r1)
  B  504 lhz r3, 2(r16)
  B  505 stw r0, 0x120(r1)
--- replace mine 514:518 base 507:509
  M  514 addi r15, r15, 4
  M  515 cmpwi r15, 0
  M  516 beq 548
  M  517 lwz r0, 0x124(r1)
  B  507 addi r16, r16, 4
  B  508 lwz r0, 0x120(r1)
--- replace mine 519:520 base 510:511
  M  519 bne 536
  B  510 bne 1684
--- replace mine 521:523 base 512:514
  M  521 lwz r0, 0xf8(r28)
  M  522 addi r6, r27, 0x4dd3
  B  512 lwz r0, 0xf8(r19)
  B  513 addi r6, r20, 0x4dd3
--- replace mine 528:531 base 519:522
  M  528 stw r4, 0xc(r1)
  M  529 mr r4, r15
  M  530 addi r3, r25, 0x800
  B  519 stw r4, 0x14(r1)
  B  520 mr r4, r16
  B  521 addi r3, r18, 0x1c98
--- replace mine 534:536 base 525:531
  M  534 stw r30, 0xd8(r1)
  M  535 addi r4, r3, 0x2301
  B  525 stw r24, 0xdc(r1)
  B  526 addi r8, r3, 0x2301
  B  527 addi r4, r1, 0x14
  B  528 lis r3, -0x1032
  B  529 stw r24, 0xd8(r1)
  B  530 addi r7, r3, -0x5477
--- delete mine 537:541 base 532:532
  M  537 lis r3, -0x1032
  M  538 stw r4, 0xc8(r1)
  M  539 addi r7, r3, -0x5477
  M  540 addi r4, r1, 0xc
--- replace mine 542:543 base 533:534
  M  542 stw r7, 0xcc(r1)
  B  533 stw r8, 0xc8(r1)
--- insert mine 545:545 base 536:538
  B  536 stw r7, 0xcc(r1)
  B  537 addi r0, r3, 0x5476
--- replace mine 546:547 base 539:540
  M  546 addi r0, r3, 0x5476
  B  539 addi r3, r1, 0xc8
--- insert mine 548:548 base 541:544
  B  541 bl 0
  B  542 lwz r8, 0xd8(r1)
  B  543 lis r4, 0
--- replace mine 549:564 base 545:552
  M  549 stw r30, 0xdc(r1)
  M  550 bl 0
  M  551 lwz r5, 0xd8(r1)
  M  552 lis r4, 0
  M  553 lwz r11, 0xdc(r1)
  M  554 addi r3, r1, 0xc8
  M  555 rlwinm r12, r5, 0x1d, 0x1a, 0x1f
  M  556 rlwinm r10, r5, 0x18, 0x18, 0x1f
  M  557 rlwinm r9, r5, 0x10, 0x18, 0x1f
  M  558 srwi r8, r5, 0x18
  M  559 rlwinm r7, r11, 0x18, 0x18, 0x1f
  M  560 rlwinm r6, r11, 0x10, 0x18, 0x1f
  M  561 srwi r0, r11, 0x18
  M  562 stb r5, 0x38(r1)
  M  563 cmplwi r12, 0x38
  B  545 rlwinm r9, r8, 0x1d, 0x1a, 0x1f
  B  546 rlwinm r7, r8, 0x18, 0x18, 0x1f
  B  547 rlwinm r6, r8, 0x10, 0x18, 0x1f
  B  548 srwi r0, r8, 0x18
  B  549 stb r8, 0x28(r1)
  B  550 cmplwi r9, 0x38
  B  551 lwz r8, 0xdc(r1)
--- replace mine 565:573 base 553:564
  M  565 stb r10, 0x39(r1)
  M  566 subfic r5, r12, 0x78
  M  567 stb r9, 0x3a(r1)
  M  568 stb r8, 0x3b(r1)
  M  569 stb r11, 0x3c(r1)
  M  570 stb r7, 0x3d(r1)
  M  571 stb r6, 0x3e(r1)
  M  572 stb r0, 0x3f(r1)
  B  553 stb r7, 0x29(r1)
  B  554 subfic r5, r9, 0x78
  B  555 rlwinm r7, r8, 0x18, 0x18, 0x1f
  B  556 stb r6, 0x2a(r1)
  B  557 rlwinm r6, r8, 0x10, 0x18, 0x1f
  B  558 stb r0, 0x2b(r1)
  B  559 srwi r0, r8, 0x18
  B  560 stb r8, 0x2c(r1)
  B  561 stb r7, 0x2d(r1)
  B  562 stb r6, 0x2e(r1)
  B  563 stb r0, 0x2f(r1)
--- replace mine 574:575 base 565:566
  M  574 subfic r5, r12, 0x38
  B  565 subfic r5, r9, 0x38
--- replace mine 577:578 base 568:569
  M  577 addi r4, r1, 0x38
  B  568 addi r4, r1, 0x28
--- replace mine 580:625 base 571:604
  M  580 lwz r0, 0xc8(r1)
  M  581 addi r3, r1, 0xc8
  M  582 stb r0, 0x808(r25)
  M  583 lwz r0, 0xc8(r1)
  M  584 rlwinm r0, r0, 0x18, 0x18, 0x1f
  M  585 stb r0, 0x809(r25)
  M  586 lwz r0, 0xc8(r1)
  M  587 rlwinm r0, r0, 0x10, 0x18, 0x1f
  M  588 stb r0, 0x80a(r25)
  M  589 lwz r0, 0xc8(r1)
  M  590 srwi r0, r0, 0x18
  M  591 stb r0, 0x80b(r25)
  M  592 lwz r0, 0xcc(r1)
  M  593 stb r0, 0x80c(r25)
  M  594 lwz r0, 0xcc(r1)
  M  595 rlwinm r0, r0, 0x18, 0x18, 0x1f
  M  596 stb r0, 0x80d(r25)
  M  597 lwz r0, 0xcc(r1)
  M  598 rlwinm r0, r0, 0x10, 0x18, 0x1f
  M  599 stb r0, 0x80e(r25)
  M  600 lwz r0, 0xcc(r1)
  M  601 srwi r0, r0, 0x18
  M  602 stb r0, 0x80f(r25)
  M  603 lwz r0, 0xd0(r1)
  M  604 stb r0, 0x810(r25)
  M  605 lwz r0, 0xd0(r1)
  M  606 rlwinm r0, r0, 0x18, 0x18, 0x1f
  M  607 stb r0, 0x811(r25)
  M  608 lwz r0, 0xd0(r1)
  M  609 rlwinm r0, r0, 0x10, 0x18, 0x1f
  M  610 stb r0, 0x812(r25)
  M  611 lwz r0, 0xd0(r1)
  M  612 srwi r0, r0, 0x18
  M  613 stb r0, 0x813(r25)
  M  614 lwz r0, 0xd4(r1)
  M  615 stb r0, 0x814(r25)
  M  616 lwz r0, 0xd4(r1)
  M  617 rlwinm r0, r0, 0x18, 0x18, 0x1f
  M  618 stb r0, 0x815(r25)
  M  619 lwz r0, 0xd4(r1)
  M  620 rlwinm r0, r0, 0x10, 0x18, 0x1f
  M  621 stb r0, 0x816(r25)
  M  622 lwz r0, 0xd4(r1)
  M  623 srwi r0, r0, 0x18
  M  624 stb r0, 0x817(r25)
  B  571 lwz r5, 0xc8(r1)
  B  572 addi r6, r1, 0xc8
  B  573 stb r5, 8(r25)
  B  574 rlwinm r4, r5, 0x18, 0x18, 0x1f
  B  575 rlwinm r3, r5, 0x10, 0x18, 0x1f
  B  576 srwi r0, r5, 0x18
  B  577 stb r4, 9(r25)
  B  578 lwz r5, 0xcc(r1)
  B  579 stb r3, 0xa(r25)
  B  580 rlwinm r4, r5, 0x18, 0x18, 0x1f
  B  581 rlwinm r3, r5, 0x10, 0x18, 0x1f
  B  582 stb r0, 0xb(r25)
  B  583 srwi r0, r5, 0x18
  B  584 stb r5, 0xc(r25)
  B  585 lwz r5, 0xd0(r1)
  B  586 stb r4, 0xd(r25)
  B  587 rlwinm r4, r5, 0x18, 0x18, 0x1f
  B  588 stb r3, 0xe(r25)
  B  589 rlwinm r3, r5, 0x10, 0x18, 0x1f
  B  590 stb r0, 0xf(r25)
  B  591 srwi r0, r5, 0x18
  B  592 stb r5, 0x10(r25)
  B  593 lwz r5, 0xd4(r1)
  B  594 stb r4, 0x11(r25)
  B  595 rlwinm r4, r5, 0x18, 0x18, 0x1f
  B  596 stb r3, 0x12(r25)
  B  597 rlwinm r3, r5, 0x10, 0x18, 0x1f
  B  598 stb r0, 0x13(r25)
  B  599 srwi r0, r5, 0x18
  B  600 stb r5, 0x14(r25)
  B  601 stb r4, 0x15(r25)
  B  602 stb r3, 0x16(r25)
  B  603 stb r0, 0x17(r25)
--- replace mine 627:636 base 606:615
  M  627 stb r30, 0(r3)
  M  628 stb r30, 1(r3)
  M  629 stb r30, 2(r3)
  M  630 stb r30, 3(r3)
  M  631 stb r30, 4(r3)
  M  632 stb r30, 5(r3)
  M  633 stb r30, 6(r3)
  M  634 stb r30, 7(r3)
  M  635 addi r3, r3, 8
  B  606 stb r24, 0(r6)
  B  607 stb r24, 1(r6)
  B  608 stb r24, 2(r6)
  B  609 stb r24, 3(r6)
  B  610 stb r24, 4(r6)
  B  611 stb r24, 5(r6)
  B  612 stb r24, 6(r6)
  B  613 stb r24, 7(r6)
  B  614 addi r6, r6, 8
--- replace mine 645:647 base 624:626
  M  645 li r19, 0
  M  646 stw r29, 0(0)
  B  624 li r27, 0
  B  625 stw r21, 0(0)
--- replace mine 648:649 base 627:628
  M  648 stw r29, 0x54(r1)
  B  627 stw r21, 0x54(r1)
--- replace mine 652:653 base 631:632
  M  652 b 1224
  B  631 b 1200
--- replace mine 654:656 base 633:635
  M  654 lwz r0, 0xf8(r28)
  M  655 addi r6, r27, 0x4dd3
  B  633 lwz r0, 0xf8(r19)
  B  634 addi r6, r20, 0x4dd3
--- replace mine 661:662 base 640:641
  M  661 addi r0, r18, 0x7d0
  B  640 addi r0, r28, 0x7d0
--- replace mine 663:664 base 642:643
  M  663 blt 1180
  B  642 blt 1156
--- replace mine 666:669 base 645:647
  M  666 b 1168
  M  667 mr r3, r25
  M  668 addi r15, r25, 8
  B  645 b 1144
  B  646 mr r3, r31
--- replace mine 672:673 base 650:651
  M  672 mr r3, r15
  B  650 addi r16, r31, 8
--- insert mine 674:674 base 652:653
  B  652 mr r3, r16
--- replace mine 678:679 base 657:658
  M  678 sth r3, 0(r15)
  B  657 sth r3, 0(r16)
--- replace mine 681:683 base 660:662
  M  681 sth r3, 2(r15)
  M  682 addi r3, r15, 4
  B  660 sth r3, 2(r16)
  B  661 addi r3, r16, 4
--- replace mine 686:688 base 665:667
  M  686 addi r3, r15, 4
  M  687 addi r4, r25, 0x808
  B  665 addi r3, r16, 4
  B  666 addi r4, r25, 8
--- replace mine 690:694 base 669:673
  M  690 addi r0, r15, 0x10
  M  691 mr r5, r25
  M  692 subf r6, r25, r0
  M  693 mr r7, r24
  B  669 addi r0, r16, 0x10
  B  670 mr r5, r31
  B  671 subf r6, r31, r0
  B  672 addi r3, r18, 0xc98
--- replace mine 696:697 base 675:676
  M  696 addi r3, r26, 0xf8
  B  675 addi r7, r18, 0xc88
--- replace mine 698:699 base 677:678
  M  698 sth r0, 0(r25)
  B  677 sth r0, 0(r31)
--- replace mine 701:703 base 680:683
  M  701 lis r3, 1
  M  702 addi r0, r3, -0x19ff
  B  680 addi r0, r14, -0x19ff
  B  681 mr r16, r3
  B  682 stb r22, 0x20(r1)
--- replace mine 704:708 base 684:686
  M  704 stb r14, 0x20(r1)
  M  705 li r0, 2
  M  706 stb r0, 0x21(r1)
  M  707 stw r29, 0x24(r1)
  B  684 stb r23, 0x21(r1)
  B  685 stw r21, 0x24(r1)
--- replace mine 710:713 base 688:691
  M  710 mr r3, r22
  M  711 lwz r5, 0(0)
  M  712 addi r4, r26, 0xf8
  B  688 mr r3, r30
  B  689 mr r5, r16
  B  690 addi r4, r18, 0xc98
--- replace mine 717:719 base 695:697
  M  717 lwz r0, 0xf8(r28)
  M  718 addi r6, r27, 0x4dd3
  B  695 lwz r0, 0xf8(r19)
  B  696 addi r6, r20, 0x4dd3
--- replace mine 724:726 base 702:704
  M  724 lwz r3, 0x12c(r1)
  M  725 mr r18, r4
  B  702 mr r28, r4
  B  703 addi r3, r18, 0x948
--- delete mine 728:729 base 706:706
  M  728 addi r3, r3, 0x948
--- replace mine 730:734 base 707:711
  M  730 stw r14, 0(0)
  M  731 b 908
  M  732 mr r3, r22
  M  733 addi r4, r26, 0xf8
  B  707 stw r22, 0(0)
  B  708 b 892
  B  709 mr r3, r30
  B  710 addi r4, r18, 0xc98
--- replace mine 739:742 base 716:719
  M  739 ble 404
  M  740 lhz r3, 0xf8(r26)
  M  741 addi r16, r26, 0xf8
  B  716 ble 392
  B  717 lhz r3, 0(r15)
  B  718 li r16, 0
--- replace mine 744:746 base 721:723
  M  744 lhz r3, 2(r16)
  M  745 stw r0, 0x120(r1)
  B  721 lhz r3, 2(r15)
  B  722 stw r0, 0x124(r1)
--- replace mine 747:757 base 724:732
  M  747 clrlwi r15, r3, 0x10
  M  748 mr r3, r16
  M  749 add r4, r16, r15
  M  750 addi r17, r16, 6
  M  751 addi r4, r4, 6
  M  752 li r16, 0
  M  753 cmplw cr1, r3, r4
  M  754 bge -8875
  M  755 subf r0, r3, r4
  M  756 addi r5, r4, -8
  B  724 clrlwi r17, r3, 0x10
  B  725 mr r4, r15
  B  726 add r3, r15, r17
  B  727 addi r3, r3, 6
  B  728 cmplw cr1, r15, r3
  B  729 bge -8803
  B  730 subf r0, r15, r3
  B  731 addi r5, r3, -8
--- replace mine 759:760 base 734:735
  M  759 bgt -8895
  B  734 bgt -8823
--- replace mine 761:762 base 736:737
  M  761 subf r0, r3, r0
  B  736 subf r0, r15, r0
--- replace mine 764:765 base 739:740
  M  764 cmplw r3, r5
  B  739 cmplw r15, r5
--- replace mine 766:768 base 741:743
  M  766 lbz r5, 0(r3)
  M  767 lbz r0, 1(r3)
  B  741 lbz r5, 0(r4)
  B  742 lbz r0, 1(r4)
--- replace mine 769:770 base 744:745
  M  769 lbz r5, 2(r3)
  B  744 lbz r5, 2(r4)
--- replace mine 771:772 base 746:747
  M  771 lbz r0, 3(r3)
  B  746 lbz r0, 3(r4)
--- replace mine 773:774 base 748:749
  M  773 lbz r5, 4(r3)
  B  748 lbz r5, 4(r4)
--- replace mine 775:776 base 750:751
  M  775 lbz r0, 5(r3)
  B  750 lbz r0, 5(r4)
--- replace mine 777:778 base 752:753
  M  777 lbz r5, 6(r3)
  B  752 lbz r5, 6(r4)
--- replace mine 779:780 base 754:755
  M  779 lbz r0, 7(r3)
  B  754 lbz r0, 7(r4)
--- replace mine 781:782 base 756:757
  M  781 addi r3, r3, 8
  B  756 addi r4, r4, 8
--- replace mine 784:785 base 759:760
  M  784 subf r0, r3, r4
  B  759 subf r0, r4, r3
--- replace mine 786:787 base 761:762
  M  786 cmplw r3, r4
  B  761 cmplw r4, r3
--- replace mine 788:790 base 763:765
  M  788 lbz r0, 0(r3)
  M  789 addi r3, r3, 1
  B  763 lbz r0, 0(r4)
  B  764 addi r4, r4, 1
--- replace mine 792:793 base 767:768
  M  792 lhz r3, 0(r4)
  B  767 lhz r3, 0(r3)
--- insert mine 797:797 base 772:773
  B  772 addi r4, r15, 6
--- insert mine 798:798 base 774:777
  B  774 li r4, 0
  B  775 cmpwi r4, 0
  B  776 bne 12
--- replace mine 799:804 base 778:780
  M  799 cmpwi r17, 0
  M  800 bne 12
  M  801 li r15, 0
  M  802 b 80
  M  803 lwz r0, 0x120(r1)
  B  778 b 72
  B  779 lwz r0, 0x124(r1)
--- replace mine 806:814 base 782:789
  M  806 li r15, 0
  M  807 b 60
  M  808 cmpwi r23, 0
  M  809 beq 36
  M  810 mr r3, r25
  M  811 mr r4, r17
  M  812 mr r5, r15
  M  813 mr r6, r23
  B  782 li r17, 0
  B  783 b 52
  B  784 cmpwi r25, 0
  B  785 beq 32
  B  786 mr r5, r17
  B  787 mr r6, r25
  B  788 addi r3, r18, 0x1498
--- replace mine 816:821 base 791:795
  M  816 addi r15, r15, -8
  M  817 b 20
  M  818 mr r3, r25
  M  819 mr r4, r17
  M  820 mr r5, r15
  B  791 addi r17, r17, -8
  B  792 b 16
  B  793 mr r5, r17
  B  794 addi r3, r18, 0x1498
--- replace mine 822:824 base 796:798
  M  822 cmpwi r15, 0
  M  823 stw r15, 0(0)
  B  796 cmpwi r17, 0
  B  797 stw r17, 0(0)
--- replace mine 825:826 base 799:800
  M  825 mr r3, r25
  B  799 addi r3, r18, 0x1498
--- replace mine 829:830 base 803:804
  M  829 addi r3, r31, 0x948
  B  803 addi r3, r18, 0x948
--- replace mine 832:833 base 806:807
  M  832 li r19, 0
  B  806 li r27, 0
--- replace mine 839:840 base 813:814
  M  839 b 476
  B  813 b 472
--- replace mine 841:843 base 815:817
  M  841 lwz r0, 0xf8(r28)
  M  842 addi r6, r27, 0x4dd3
  B  815 lwz r0, 0xf8(r19)
  B  816 addi r6, r20, 0x4dd3
--- replace mine 848:849 base 822:823
  M  848 addi r0, r18, 0x3e8
  B  822 addi r0, r28, 0x3e8
--- replace mine 850:853 base 824:827
  M  850 blt 432
  M  851 addi r19, r19, 1
  M  852 cmpwi r19, 0xa
  B  824 blt 428
  B  825 addi r27, r27, 1
  B  826 cmpwi r27, 0xa
--- replace mine 854:855 base 828:829
  M  854 mr r3, r22
  B  828 mr r3, r30
--- replace mine 856:859 base 830:833
  M  856 li r21, -2
  M  857 li r20, 1
  M  858 b 400
  B  830 li r29, -2
  B  831 li r26, 1
  B  832 b 396
--- replace mine 861:864 base 835:837
  M  861 b 388
  M  862 mr r3, r25
  M  863 addi r15, r25, 8
  B  835 b 384
  B  836 mr r3, r31
--- replace mine 867:868 base 840:841
  M  867 mr r3, r15
  B  840 addi r16, r31, 8
--- insert mine 869:869 base 842:843
  B  842 mr r3, r16
--- replace mine 873:874 base 847:848
  M  873 sth r3, 0(r15)
  B  847 sth r3, 0(r16)
--- replace mine 876:878 base 850:852
  M  876 sth r3, 2(r15)
  M  877 addi r3, r15, 4
  B  850 sth r3, 2(r16)
  B  851 addi r3, r16, 4
--- replace mine 881:882 base 855:856
  M  881 addi r3, r15, 4
  B  855 addi r3, r16, 4
--- replace mine 885:889 base 859:863
  M  885 addi r0, r15, 8
  M  886 mr r5, r25
  M  887 subf r6, r25, r0
  M  888 mr r7, r23
  B  859 addi r0, r16, 8
  B  860 mr r5, r31
  B  861 subf r6, r31, r0
  B  862 addi r3, r18, 0xc98
--- replace mine 891:892 base 865:866
  M  891 addi r3, r26, 0xf8
  B  865 addi r7, r18, 0x1c98
--- replace mine 893:894 base 867:868
  M  893 sth r0, 0(r25)
  B  867 sth r0, 0(r31)
--- replace mine 900:902 base 874:876
  M  900 lwz r0, 0xf8(r28)
  M  901 addi r6, r27, 0x4dd3
  B  874 lwz r0, 0xf8(r19)
  B  875 addi r6, r20, 0x4dd3
--- replace mine 907:914 base 881:888
  M  907 li r19, 0xa
  M  908 addi r18, r4, 0x3e8
  M  909 stw r19, 0(0)
  M  910 b 192
  M  911 lis r3, 1
  M  912 stb r14, 0x18(r1)
  M  913 addi r0, r3, -0x19ff
  B  881 li r27, 0xa
  B  882 addi r28, r4, 0x3e8
  B  883 stw r27, 0(0)
  B  884 b 188
  B  885 addi r0, r14, -0x19ff
  B  886 stb r22, 0x18(r1)
  B  887 lwz r16, 0(0)
--- replace mine 915:918 base 889:891
  M  915 stw r29, 0x1c(r1)
  M  916 li r0, 2
  M  917 stb r0, 0x19(r1)
  B  889 stb r23, 0x19(r1)
  B  890 stw r21, 0x1c(r1)
--- replace mine 920:923 base 893:896
  M  920 mr r3, r22
  M  921 lwz r5, 0(0)
  M  922 addi r4, r26, 0xf8
  B  893 mr r3, r30
  B  894 mr r5, r16
  B  895 addi r4, r18, 0xc98
--- replace mine 927:929 base 900:902
  M  927 lwz r0, 0xf8(r28)
  M  928 addi r6, r27, 0x4dd3
  B  900 lwz r0, 0xf8(r19)
  B  901 addi r6, r20, 0x4dd3
--- replace mine 935:936 base 908:909
  M  935 mr r18, r4
  B  908 mr r28, r4
--- replace mine 939:941 base 912:914
  M  939 lwz r0, 0xf8(r28)
  M  940 addi r6, r27, 0x4dd3
  B  912 lwz r0, 0xf8(r19)
  B  913 addi r6, r20, 0x4dd3
--- replace mine 946:947 base 919:920
  M  946 addi r0, r18, 0x3e8
  B  919 addi r0, r28, 0x3e8
--- replace mine 949:951 base 922:924
  M  949 addi r19, r19, 1
  M  950 cmpwi r19, 0xa
  B  922 addi r27, r27, 1
  B  923 cmpwi r27, 0xa
--- replace mine 952:953 base 925:926
  M  952 li r20, 1
  B  925 li r26, 1
--- replace mine 954:955 base 927:928
  M  954 mr r21, r3
  B  927 mr r29, r3
--- replace mine 958:959 base 931:932
  M  958 cmpwi r20, 0
  B  931 cmpwi r26, 0
--- replace mine 962:964 base 935:937
  M  962 beq -3724
  M  963 cmpwi r22, 0
  B  935 beq -3632
  B  936 cmpwi r30, 0
--- replace mine 965:966 base 938:939
  M  965 mr r3, r22
  B  938 mr r3, r30
--- replace mine 970:971 base 943:944
  M  970 li r21, -8
  B  943 li r29, -8
--- replace mine 972:973 base 945:946
  M  972 mr r3, r21
  B  945 mr r3, r29
```

ATERM_814038C8 initial 85.933754%
- local order: wait-message declaration before single-message storage: 85.9327%; src 0xf48 base 0xedc insns 978/951; --- replace mine 5:7 base 5:11;   M    5 lis r0, 0;   M    6 lis r27, 0x1062
- stack lifetime: MD5 context and count bytes confined to authentication block: 85.95689%; src 0xf48 base 0xedc insns 978/951; --- replace mine 5:7 base 5:11;   M    5 lis r0, 0;   M    6 lis r27, 0x1062
- temporary: connection key accesses named owner field at actual calls: 87.2755%; src 0xf30 base 0xedc insns 972/951; --- replace mine 5:7 base 5:11;   M    5 lis r0, 0;   M    6 lis r26, 0x1062
Retained best candidate

## ATERM_81405254 initial instruction differences

All 271 instructions, frame and round-loop branch topology agree. Initial packed-word scheduling changes state register colors, propagating into table loads and pairwise XOR chains. The final table and output store sequence also differ. Try state-word reuse for final round, a named two-stage initial XOR, and final table view at function scope; no key/table contents change.

```text
src 0x43c base 0x43c insns 271/271
diffs 214: [12, 13, 18, 20, 24, 26, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41]
    12 M slwi r21, r11, 0x18
       B slwi r22, r11, 0x18
    13 M slwi r20, r10, 0x10
       B slwi r21, r10, 0x10
    18 M slwi r17, r11, 0x18
       B slwi r18, r11, 0x18
    20 M slwi r16, r10, 0x10
       B slwi r17, r10, 0x10
    24 M slwi r7, r7, 0x18
       B srawi r30, r4, 1
    26 M slwi r0, r0, 0x10
       B slwi r7, r7, 0x18
    28 M slwi r12, r12, 8
       B slwi r0, r0, 0x10
    29 M lbz r24, 3(r5)
       B lbz r25, 3(r5)
    30 M slwi r11, r11, 0x18
       B slwi r12, r12, 8
    31 M lbz r22, 7(r5)
       B lbz r24, 7(r5)
    32 M slwi r10, r10, 0x10
       B slwi r11, r11, 0x18
    33 M lbz r18, 0xb(r5)
       B lbz r20, 0xb(r5)
    34 M xor r25, r8, r24
       B xor r26, r25, r8
    35 M xor r24, r7, r0
       B lbz r5, 0xf(r5)
    36 M lbz r5, 0xf(r5)
       B xor r25, r7, r0
    37 M xor r8, r19, r18
       B xor r7, r18, r17
    38 M xor r7, r17, r16
       B slwi r10, r10, 0x10
    39 M xor r17, r8, r7
       B xor r8, r20, r19
    40 M xor r22, r23, r22
       B xor r5, r5, r12
    41 M xor r20, r21, r20
       B xor r0, r11, r10
    42 M xor r0, r11, r10
       B xor r23, r24, r23
    43 M xor r5, r12, r5
       B xor r21, r22, r21
    44 M lwz r18, 8(r3)
       B xor r8, r8, r7
    45 M xor r12, r5, r0
       B lwz r18, 0(r3)
    46 M lwz r16, 0xc(r3)
       B xor r17, r26, r25
    47 M lwz r23, 0(r3)
       B xor r5, r5, r0
    48 M xor r21, r25, r24
       B lwz r12, 4(r3)
    49 M srawi r0, r4, 1
       B xor r10, r23, r21
    50 M lwz r19, 4(r3)
       B lwz r11, 8(r3)
    51 M xor r11, r22, r20
       B xor r0, r18, r17
    52 M addi r5, r9, 0xc00
       B lwz r7, 0xc(r3)
    53 M addi r7, r9, 0x800
       B xor r17, r11, r8
    54 M addi r8, r9, 0
       B xor r10, r12, r10
    55 M addi r10, r9, 0x400
       B xor r11, r7, r5
    56 M xor r4, r23, r21
       B addi r8, r9, 0xc00
    57 M xor r11, r19, r11
       B addi r7, r9, 0x800
    58 M xor r17, r18, r17
       B addi r5, r9, 0
    59 M xor r12, r16, r12
       B addi r4, r9, 0x400
    60 M rlwinm r30, r12, 2, 0x16, 0x1d
       B rlwinm r31, r11, 2, 0x16, 0x1d
    62 M rlwinm r26, r4, 2, 0x16, 0x1d
       B rlwinm r26, r0, 2, 0x16, 0x1d
    63 M rlwinm r25, r12, 0x1a, 0x16, 0x1d
       B rlwinm r25, r11, 0x1a, 0x16, 0x1d
    64 M rlwinm r22, r11, 2, 0x16, 0x1d
       B rlwinm r22, r10, 2, 0x16, 0x1d
    66 M rlwinm r19, r12, 0x12, 0x16, 0x1d
       B rlwinm r19, r11, 0x12, 0x16, 0x1d
    67 M rlwinm r16, r12, 0xa, 0x16, 0x1d
       B rlwinm r12, r11, 0xa, 0x16, 0x1d
    70 M rlwinm r17, r11, 0x1a, 0x16, 0x1d
       B rlwinm r17, r10, 0x1a, 0x16, 0x1d
    71 M rlwinm r12, r4, 0x12, 0x16, 0x1d
       B rlwinm r11, r0, 0x12, 0x16, 0x1d
    72 M rlwinm r28, r4, 0xa, 0x16, 0x1d
       B rlwinm r28, r0, 0xa, 0x16, 0x1d
    73 M rlwinm r27, r11, 0x12, 0x16, 0x1d
       B rlwinm r27, r10, 0x12, 0x16, 0x1d
    74 M rlwinm r24, r11, 0xa, 0x16, 0x1d
       B rlwinm r24, r10, 0xa, 0x16, 0x1d
    75 M rlwinm r21, r4, 0x1a, 0x16, 0x1d
       B rlwinm r21, r0, 0x1a, 0x16, 0x1d
    76 M lwzx r30, r5, r30
       B lwzx r31, r8, r31
    77 M addic. r0, r0, -1
       B addic. r30, r30, -1
    79 M lwzx r4, r10, r27
       B lwzx r0, r4, r27
    80 M lwzx r11, r8, r28
       B lwzx r10, r5, r28
    81 M xor r27, r30, r29
       B xor r27, r31, r29
    82 M lwzx r26, r5, r26
       B lwzx r26, r8, r26
    83 M xor r4, r11, r4
       B xor r0, r10, r0
    84 M lwzx r11, r8, r24
       B lwzx r10, r5, r24
    85 M xor r27, r27, r4
       B xor r27, r27, r0
    86 M lwzx r4, r10, r23
       B lwzx r0, r4, r23
    88 M xor r4, r11, r4
       B xor r0, r10, r0
    89 M lwzx r22, r5, r22
       B lwzx r22, r8, r22
    91 M lwzx r11, r7, r21
       B lwzx r10, r7, r21
    92 M lwzx r20, r8, r20
       B lwzx r20, r5, r20
    93 M xor r23, r23, r4
       B xor r23, r23, r0
    94 M lwzx r19, r10, r19
       B lwzx r19, r4, r19
    95 M xor r21, r22, r11
       B xor r21, r22, r10
    99 M lwzx r18, r5, r18
       B lwzx r18, r8, r18
   102 M xor r4, r25, r27
       B xor r0, r25, r27
   103 M lwzx r16, r8, r16
       B lwzx r12, r5, r12
   104 M xor r11, r24, r23
       B xor r10, r24, r23
   105 M lwzx r12, r10, r12
       B lwzx r11, r4, r11
   108 M xor r12, r16, r12
       B xor r11, r12, r11
   110 M xor r16, r17, r12
       B xor r12, r17, r11
   112 M xor r12, r20, r19
       B xor r11, r20, r19
   113 M xor r31, r18, r16
       B xor r12, r18, r12
   115 M rlwinm r16, r31, 2, 0x16, 0x1d
       B rlwinm r17, r12, 2, 0x16, 0x1d
   116 M rlwinm r17, r12, 0x1a, 0x16, 0x1d
       B rlwinm r18, r11, 0x1a, 0x16, 0x1d
   117 M rlwinm r30, r4, 2, 0x16, 0x1d
       B rlwinm r29, r0, 2, 0x16, 0x1d
   118 M rlwinm r29, r31, 0x1a, 0x16, 0x1d
       B rlwinm r25, r10, 2, 0x16, 0x1d
   119 M rlwinm r26, r11, 2, 0x16, 0x1d
       B rlwinm r23, r11, 0xa, 0x16, 0x1d
   120 M rlwinm r24, r12, 0xa, 0x16, 0x1d
       B rlwinm r21, r11, 2, 0x16, 0x1d
   121 M rlwinm r23, r31, 0x12, 0x16, 0x1d
       B rlwinm r26, r11, 0x12, 0x16, 0x1d
   122 M rlwinm r20, r31, 0xa, 0x16, 0x1d
       B rlwinm r20, r10, 0x1a, 0x16, 0x1d
   123 M rlwinm r22, r12, 2, 0x16, 0x1d
       B rlwinm r11, r0, 0x12, 0x16, 0x1d
   124 M rlwinm r27, r12, 0x12, 0x16, 0x1d
       B rlwinm r19, r0, 0xa, 0x16, 0x1d
   125 M rlwinm r21, r11, 0x1a, 0x16, 0x1d
       B rlwinm r28, r12, 0x1a, 0x16, 0x1d
   126 M rlwinm r12, r4, 0x12, 0x16, 0x1d
       B rlwinm r22, r12, 0x12, 0x16, 0x1d
   127 M rlwinm r18, r4, 0xa, 0x16, 0x1d
       B rlwinm r12, r12, 0xa, 0x16, 0x1d
   128 M rlwinm r19, r11, 0x12, 0x16, 0x1d
       B rlwinm r31, r10, 0x12, 0x16, 0x1d
   129 M rlwinm r28, r11, 0xa, 0x16, 0x1d
       B rlwinm r27, r10, 0xa, 0x16, 0x1d
   130 M rlwinm r25, r4, 0x1a, 0x16, 0x1d
       B rlwinm r24, r0, 0x1a, 0x16, 0x1d
   131 M lwzx r16, r5, r16
       B lwzx r17, r8, r17
   132 M lwzx r31, r7, r17
       B lwzx r18, r7, r18
   133 M lwzx r11, r8, r18
       B lwzx r10, r5, r19
   134 M lwzx r4, r10, r19
       B lwzx r0, r4, r31
   135 M xor r18, r16, r31
       B xor r19, r17, r18
   136 M lwzx r30, r5, r30
       B lwzx r29, r8, r29
   137 M xor r4, r11, r4
       B xor r0, r10, r0
   138 M lwzx r11, r8, r28
       B lwzx r10, r5, r27
   139 M xor r31, r18, r4
       B xor r31, r19, r0
   140 M lwzx r4, r10, r27
       B lwzx r0, r4, r26
   141 M lwzx r29, r7, r29
       B lwzx r28, r7, r28
   142 M xor r4, r11, r4
       B xor r0, r10, r0
   143 M lwzx r26, r5, r26
       B lwzx r25, r8, r25
   144 M lwzx r11, r7, r25
       B lwzx r10, r7, r24
   145 M xor r27, r30, r29
       B xor r26, r29, r28
   146 M lwzx r24, r8, r24
       B lwzx r23, r5, r23
   147 M xor r27, r27, r4
       B xor r26, r26, r0
   148 M lwzx r23, r10, r23
       B lwzx r22, r4, r22
   149 M xor r25, r26, r11
       B xor r24, r25, r10
   150 M lwz r16, 0(r3)
       B lwz r17, 0(r3)
   151 M lwz r28, 4(r3)
       B lwz r27, 4(r3)
   152 M xor r23, r24, r23
       B xor r22, r23, r22
   153 M lwzx r22, r5, r22
       B lwzx r21, r8, r21
   154 M xor r23, r25, r23
       B xor r22, r24, r22
   155 M lwzx r21, r7, r21
       B lwzx r20, r7, r20
   156 M xor r4, r16, r31
       B xor r0, r17, r31
   157 M lwzx r20, r8, r20
       B lwzx r12, r5, r12
   158 M xor r11, r28, r27
       B xor r10, r27, r26
   159 M lwzx r12, r10, r12
       B lwzx r11, r4, r11
   160 M xor r21, r22, r21
       B xor r20, r21, r20
   161 M lwz r22, 8(r3)
       B lwz r21, 8(r3)
   162 M xor r12, r20, r12
       B xor r11, r12, r11
   163 M lwz r20, 0xc(r3)
       B lwz r12, 0xc(r3)
   164 M xor r12, r21, r12
       B xor r11, r20, r11
   165 M xor r17, r22, r23
       B xor r17, r21, r22
   166 M xor r12, r20, r12
       B xor r11, r12, r11
   169 M rlwinm r20, r31, 2, 0x16, 0x1d
       B rlwinm r20, r12, 2, 0x16, 0x1d
   170 M rlwinm r22, r11, 0x12, 0x16, 0x1d
       B rlwinm r24, r0, 2, 0x16, 0x1d
   171 M rlwinm r24, r12, 0xa, 0x16, 0x1d
       B rlwinm r31, r0, 0xa, 0x16, 0x1d
   172 M rlwinm r26, r12, 2, 0x16, 0x1d
       B rlwinm r5, r0, 0x1a, 0x16, 0x1d
   173 M rlwinm r27, r11, 0x1a, 0x16, 0x1d
       B rlwinm r29, r0, 0x12, 0x16, 0x1d
   174 M rlwinm r28, r31, 0xa, 0x16, 0x1d
       B rlwinm r26, r11, 2, 0x16, 0x1d
   175 M rlwinm r21, r12, 0x1a, 0x16, 0x1d
       B rlwinm r27, r10, 0x1a, 0x16, 0x1d
   176 M rlwinm r8, r12, 0x12, 0x16, 0x1d
       B rlwinm r23, r12, 0x1a, 0x16, 0x1d
   177 M rlwinm r25, r4, 0xa, 0x16, 0x1d
       B lwzx r0, r30, r20
   178 M lwzx r24, r30, r24
       B rlwinm r25, r12, 0x12, 0x16, 0x1d
   179 M rlwinm r23, r4, 2, 0x16, 0x1d
       B rlwinm r28, r12, 0xa, 0x16, 0x1d
   180 M lwzx r26, r30, r26
       B rlwinm r21, r11, 0x1a, 0x16, 0x1d
   181 M rlwinm r9, r11, 0xa, 0x16, 0x1d
       B rlwinm r22, r10, 0x12, 0x16, 0x1d
   182 M rlwinm r7, r11, 2, 0x16, 0x1d
       B lwzx r25, r30, r25
   183 M lwzx r27, r30, r27
       B rlwinm r9, r10, 0xa, 0x16, 0x1d
   184 M rlwinm r5, r4, 0x1a, 0x16, 0x1d
       B rlwinm r7, r10, 2, 0x16, 0x1d
   185 M rlwinm r29, r4, 0x12, 0x16, 0x1d
       B lwzx r10, r30, r31
   186 M lwzx r4, r30, r25
       B clrlwi r31, r0, 0x18
   187 M rlwinm r10, r31, 0x1a, 0x16, 0x1d
       B lwzx r26, r30, r26
   188 M lwzx r25, r30, r23
       B lwzx r27, r30, r27
   189 M rlwinm r0, r31, 0x12, 0x16, 0x1d
       B rlwinm r8, r11, 0x12, 0x16, 0x1d
   190 M lwzx r12, r30, r20
       B rlwinm r4, r11, 0xa, 0x16, 0x1d
   191 M rlwinm r24, r24, 0, 0, 7
       B lwzx r11, r30, r21
   192 M lwzx r23, r30, r9
       B lwzx r0, r30, r22
   193 M clrlwi r9, r25, 0x18
       B rlwinm r25, r25, 0, 8, 0xf
   194 M lwzx r11, r30, r21
       B rlwinm r12, r11, 0, 0x10, 0x17
   195 M clrlwi r31, r12, 0x18
       B rlwinm r11, r10, 0, 0, 7
   196 M lwzx r25, r30, r8
       B rlwinm r10, r0, 0, 8, 0xf
   197 M clrlwi r26, r26, 0x18
       B lwzx r24, r30, r24
   198 M rlwinm r12, r11, 0, 0x10, 0x17
       B lwzx r0, r30, r9
   199 M rlwinm r11, r4, 0, 0, 7
       B clrlwi r26, r26, 0x18
   200 M lwzx r4, r30, r10
       B clrlwi r9, r24, 0x18
   201 M rlwinm r27, r27, 0, 0x10, 0x17
       B lwzx r23, r30, r23
   202 M lwzx r22, r30, r22
       B lwzx r24, r30, r8
   203 M rlwinm r8, r4, 0, 0x10, 0x17
       B rlwinm r27, r27, 0, 0x10, 0x17
   204 M lwzx r4, r30, r7
       B rlwinm r8, r23, 0, 0x10, 0x17
   205 M rlwinm r10, r22, 0, 8, 0xf
       B lwzx r23, r30, r7
   206 M rlwinm r7, r23, 0, 0, 7
       B rlwinm r7, r0, 0, 0, 7
   207 M lwzx r23, r30, r5
       B lwzx r0, r30, r5
   208 M rlwinm r5, r25, 0, 8, 0xf
       B rlwinm r5, r24, 0, 8, 0xf
   209 M lwzx r25, r30, r0
       B lwzx r24, r30, r4
   210 M xor r10, r11, r10
       B lwzx r28, r30, r28
   211 M lwzx r28, r30, r28
       B xor r9, r9, r8
   212 M xor r22, r31, r12
       B lwzx r30, r30, r29
   213 M lwzx r30, r30, r29
       B xor r22, r31, r12
   214 M xor r8, r9, r8
       B xor r10, r11, r10
   215 M rlwinm r29, r28, 0, 0, 7
       B xor r8, r7, r5
   216 M xor r5, r7, r5
       B rlwinm r24, r24, 0, 0, 7
   217 M rlwinm r12, r30, 0, 8, 0xf
       B clrlwi r4, r23, 0x18
   218 M xor r28, r26, r27
       B rlwinm r0, r0, 0, 0x10, 0x17
   219 M xor r7, r8, r5
       B xor r11, r22, r10
   220 M lwz r9, 4(r3)
       B xor r7, r4, r0
   221 M clrlwi r4, r4, 0x18
       B xor r5, r24, r25
   222 M rlwinm r0, r23, 0, 0x10, 0x17
       B xor r9, r9, r8
   223 M xor r17, r9, r7
       B lwz r10, 4(r3)
   224 M rlwinm r25, r25, 0, 8, 0xf
       B rlwinm r29, r28, 0, 0, 7
   225 M xor r4, r4, r0
       B rlwinm r12, r30, 0, 8, 0xf
   226 M lwz r11, 0(r3)
       B xor r18, r10, r9
   227 M xor r0, r24, r25
       B xor r4, r26, r27
   228 M xor r10, r22, r10
       B xor r0, r29, r12
   229 M xor r16, r11, r10
       B lwz r12, 0(r3)
   230 M xor r30, r29, r12
       B lwz r8, 8(r3)
   231 M xor r0, r4, r0
       B xor r5, r7, r5
   232 M lwz r5, 8(r3)
       B xor r17, r12, r11
   233 M lwz r26, 0xc(r3)
       B srwi r11, r18, 0x18
   234 M xor r3, r28, r30
       B xor r19, r8, r5
   235 M xor r18, r5, r0
       B rlwinm r10, r18, 0x10, 0x18, 0x1f
   236 M srwi r4, r16, 0x18
       B srwi r24, r17, 0x18
   237 M xor r19, r26, r3
       B rlwinm r23, r17, 0x10, 0x18, 0x1f
   238 M rlwinm r0, r16, 0x10, 0x18, 0x1f
       B rlwinm r12, r17, 0x18, 0x18, 0x1f
   239 M rlwinm r12, r16, 0x18, 0x18, 0x1f
       B rlwinm r9, r18, 0x18, 0x18, 0x1f
   240 M srwi r11, r17, 0x18
       B srwi r8, r19, 0x18
   241 M rlwinm r10, r17, 0x10, 0x18, 0x1f
       B rlwinm r7, r19, 0x10, 0x18, 0x1f
   242 M rlwinm r9, r17, 0x18, 0x18, 0x1f
       B rlwinm r5, r19, 0x18, 0x18, 0x1f
   243 M srwi r8, r18, 0x18
       B lwz r3, 0xc(r3)
   244 M rlwinm r7, r18, 0x10, 0x18, 0x1f
       B xor r0, r4, r0
   245 M rlwinm r5, r18, 0x18, 0x18, 0x1f
       B stb r24, 0(r6)
   246 M stb r4, 0(r6)
       B xor r20, r3, r0
   247 M srwi r4, r19, 0x18
       B srwi r4, r20, 0x18
   248 M rlwinm r3, r19, 0x10, 0x18, 0x1f
       B stb r23, 1(r6)
   249 M stb r0, 1(r6)
       B rlwinm r3, r20, 0x10, 0x18, 0x1f
   250 M rlwinm r0, r19, 0x18, 0x18, 0x1f
       B rlwinm r0, r20, 0x18, 0x18, 0x1f
   252 M stb r16, 3(r6)
       B stb r17, 3(r6)
   256 M stb r17, 7(r6)
       B stb r18, 7(r6)
   260 M stb r18, 0xb(r6)
       B stb r19, 0xb(r6)
   264 M stb r19, 0xf(r6)
       B stb r20, 0xf(r6)
```

ATERM_81405254 initial 62.110703%
- temporary: final AES words reuse dead state variables: 62.110703%; src 0x43c base 0x43c insns 271/271; diffs 214: [12, 13, 18, 20, 24, 26, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41];     12 M slwi r21, r11, 0x18;        B slwi r22, r11, 0x18
- temporary: input words packed before separate initial key XOR: compile failed
- local order: final substitution table view declared before paired rounds: 59.92989%; src 0x43c base 0x43c insns 271/271; diffs 221: [10, 16, 24, 26, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 44, 45];     10 M slwi r24, r12, 8;        B slwi r23, r12, 8
Retained best candidate

## ATERM_81405690 initial instruction differences

All 271 instructions, frame and round-loop branch topology agree. Initial packed-word scheduling changes state register colors, propagating into table loads and pairwise XOR chains. The final table and output store sequence also differ. Try state-word reuse for final round, a named two-stage initial XOR, and final table view at function scope; no key/table contents change.

```text
src 0x43c base 0x43c insns 271/271
diffs 199: [24, 26, 28, 30, 32, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45, 46, 47, 48, 49, 50]
    24 M slwi r7, r7, 0x18
       B srawi r30, r4, 1
    26 M slwi r0, r0, 0x10
       B slwi r7, r7, 0x18
    28 M slwi r12, r12, 8
       B slwi r0, r0, 0x10
    30 M slwi r11, r11, 0x18
       B slwi r12, r12, 8
    32 M slwi r10, r10, 0x10
       B slwi r11, r11, 0x18
    35 M xor r25, r7, r0
       B lbz r5, 0xf(r5)
    36 M xor r7, r18, r17
       B xor r25, r7, r0
    37 M lbz r5, 0xf(r5)
       B xor r7, r18, r17
    38 M xor r8, r20, r19
       B slwi r10, r10, 0x10
    39 M xor r0, r11, r10
       B xor r8, r20, r19
    40 M xor r23, r24, r23
       B xor r5, r5, r12
    41 M xor r10, r8, r7
       B xor r0, r11, r10
    42 M xor r5, r5, r12
       B xor r23, r24, r23
    44 M lwz r19, 0(r3)
       B xor r8, r8, r7
    45 M xor r7, r5, r0
       B lwz r11, 8(r3)
    46 M lwz r8, 0xc(r3)
       B xor r17, r26, r25
    47 M lwz r17, 4(r3)
       B lwz r18, 0(r3)
    48 M xor r12, r23, r21
       B xor r5, r5, r0
    49 M lwz r11, 8(r3)
       B xor r11, r11, r8
    50 M xor r18, r26, r25
       B lwz r12, 4(r3)
    51 M xor r5, r17, r12
       B xor r10, r23, r21
    52 M srawi r0, r4, 1
       B lwz r7, 0xc(r3)
    53 M xor r17, r11, r10
       B xor r10, r12, r10
    54 M xor r4, r19, r18
       B xor r0, r18, r17
    55 M xor r7, r8, r7
       B xor r12, r7, r5
    56 M addi r10, r9, 0x2000
       B addi r8, r9, 0x2000
    57 M addi r11, r9, 0x1c00
       B addi r7, r9, 0x1c00
    58 M addi r12, r9, 0x1400
       B addi r5, r9, 0x1400
    59 M addi r30, r9, 0x1800
       B addi r4, r9, 0x1800
    60 M rlwinm r31, r7, 0x12, 0x16, 0x1d
       B rlwinm r31, r10, 2, 0x16, 0x1d
    61 M rlwinm r29, r4, 0xa, 0x16, 0x1d
       B rlwinm r29, r11, 0x1a, 0x16, 0x1d
    62 M rlwinm r26, r4, 0x12, 0x16, 0x1d
       B rlwinm r19, r10, 0x12, 0x16, 0x1d
    63 M rlwinm r25, r5, 0xa, 0x16, 0x1d
       B rlwinm r18, r0, 2, 0x16, 0x1d
    64 M rlwinm r22, r5, 0x12, 0x16, 0x1d
       B rlwinm r17, r10, 0x1a, 0x16, 0x1d
    65 M rlwinm r20, r7, 2, 0x16, 0x1d
       B rlwinm r28, r0, 0xa, 0x16, 0x1d
    66 M rlwinm r19, r4, 0x1a, 0x16, 0x1d
       B rlwinm r24, r10, 0xa, 0x16, 0x1d
    67 M rlwinm r18, r17, 0x12, 0x16, 0x1d
       B rlwinm r27, r12, 0x12, 0x16, 0x1d
    68 M rlwinm r8, r4, 2, 0x16, 0x1d
       B rlwinm r23, r0, 0x12, 0x16, 0x1d
    69 M rlwinm r27, r17, 0x1a, 0x16, 0x1d
       B rlwinm r21, r0, 0x1a, 0x16, 0x1d
    70 M rlwinm r28, r5, 2, 0x16, 0x1d
       B rlwinm r26, r11, 2, 0x16, 0x1d
    71 M rlwinm r24, r17, 2, 0x16, 0x1d
       B rlwinm r20, r11, 0xa, 0x16, 0x1d
    72 M rlwinm r21, r17, 0xa, 0x16, 0x1d
       B rlwinm r25, r12, 0x1a, 0x16, 0x1d
    73 M rlwinm r17, r7, 0xa, 0x16, 0x1d
       B rlwinm r22, r12, 2, 0x16, 0x1d
    74 M rlwinm r23, r7, 0x1a, 0x16, 0x1d
       B rlwinm r12, r12, 0xa, 0x16, 0x1d
    75 M rlwinm r7, r5, 0x1a, 0x16, 0x1d
       B rlwinm r11, r11, 0x12, 0x16, 0x1d
    76 M lwzx r31, r30, r31
       B lwzx r31, r8, r31
    77 M addic. r0, r0, -1
       B addic. r30, r30, -1
    78 M lwzx r29, r12, r29
       B lwzx r29, r7, r29
    79 M lwzx r4, r11, r27
       B lwzx r0, r4, r27
    80 M lwzx r5, r10, r28
       B lwzx r10, r5, r28
    82 M lwzx r26, r30, r26
       B lwzx r26, r8, r26
    83 M xor r4, r5, r4
       B xor r0, r10, r0
    84 M lwzx r5, r10, r24
       B lwzx r10, r5, r24
    85 M xor r27, r27, r4
       B xor r27, r27, r0
    86 M lwzx r4, r11, r23
       B lwzx r0, r4, r23
    87 M lwzx r25, r12, r25
       B lwzx r25, r7, r25
    88 M xor r4, r5, r4
       B xor r0, r10, r0
    89 M lwzx r22, r30, r22
       B lwzx r22, r8, r22
    91 M lwzx r5, r12, r21
       B lwzx r10, r7, r21
    92 M lwzx r20, r10, r20
       B lwzx r20, r5, r20
    93 M xor r23, r23, r4
       B xor r23, r23, r0
    94 M lwzx r19, r11, r19
       B lwzx r19, r4, r19
    95 M xor r21, r22, r5
       B xor r21, r22, r10
    99 M lwzx r18, r30, r18
       B lwzx r18, r8, r18
   101 M lwzx r17, r12, r17
       B lwzx r17, r7, r17
   102 M xor r4, r25, r27
       B xor r0, r25, r27
   103 M lwzx r8, r10, r8
       B lwzx r12, r5, r12
   104 M xor r5, r24, r23
       B xor r10, r24, r23
   105 M lwzx r7, r11, r7
       B lwzx r11, r4, r11
   108 M xor r7, r8, r7
       B xor r11, r12, r11
   110 M xor r8, r17, r7
       B xor r12, r17, r11
   112 M xor r7, r20, r19
       B xor r11, r20, r19
   113 M xor r8, r18, r8
       B xor r12, r18, r12
   115 M rlwinm r17, r8, 0x12, 0x16, 0x1d
       B rlwinm r17, r10, 2, 0x16, 0x1d
   116 M rlwinm r18, r4, 0xa, 0x16, 0x1d
       B rlwinm r18, r11, 0x1a, 0x16, 0x1d
   117 M rlwinm r29, r4, 0x12, 0x16, 0x1d
       B rlwinm r22, r10, 0x12, 0x16, 0x1d
   118 M rlwinm r28, r5, 0xa, 0x16, 0x1d
       B rlwinm r21, r0, 2, 0x16, 0x1d
   119 M rlwinm r25, r5, 0x12, 0x16, 0x1d
       B rlwinm r20, r10, 0x1a, 0x16, 0x1d
   120 M rlwinm r23, r8, 2, 0x16, 0x1d
       B rlwinm r19, r0, 0xa, 0x16, 0x1d
   121 M rlwinm r22, r4, 0x1a, 0x16, 0x1d
       B rlwinm r27, r10, 0xa, 0x16, 0x1d
   122 M rlwinm r21, r7, 0x12, 0x16, 0x1d
       B rlwinm r31, r12, 0x12, 0x16, 0x1d
   123 M rlwinm r20, r8, 0xa, 0x16, 0x1d
       B rlwinm r26, r0, 0x12, 0x16, 0x1d
   124 M rlwinm r26, r8, 0x1a, 0x16, 0x1d
       B rlwinm r24, r0, 0x1a, 0x16, 0x1d
   125 M rlwinm r8, r4, 2, 0x16, 0x1d
       B rlwinm r29, r11, 2, 0x16, 0x1d
   126 M rlwinm r31, r7, 0x1a, 0x16, 0x1d
       B rlwinm r23, r11, 0xa, 0x16, 0x1d
   127 M rlwinm r19, r5, 2, 0x16, 0x1d
       B rlwinm r28, r12, 0x1a, 0x16, 0x1d
   128 M rlwinm r27, r7, 2, 0x16, 0x1d
       B rlwinm r25, r12, 2, 0x16, 0x1d
   129 M rlwinm r24, r7, 0xa, 0x16, 0x1d
       B rlwinm r12, r12, 0xa, 0x16, 0x1d
   130 M rlwinm r7, r5, 0x1a, 0x16, 0x1d
       B rlwinm r11, r11, 0x12, 0x16, 0x1d
   131 M lwzx r17, r30, r17
       B lwzx r17, r8, r17
   132 M lwzx r18, r12, r18
       B lwzx r18, r7, r18
   133 M lwzx r5, r10, r19
       B lwzx r10, r5, r19
   134 M lwzx r4, r11, r31
       B lwzx r0, r4, r31
   136 M lwzx r29, r30, r29
       B lwzx r29, r8, r29
   137 M xor r4, r5, r4
       B xor r0, r10, r0
   138 M lwzx r5, r10, r27
       B lwzx r10, r5, r27
   139 M xor r31, r19, r4
       B xor r31, r19, r0
   140 M lwzx r4, r11, r26
       B lwzx r0, r4, r26
   141 M lwzx r28, r12, r28
       B lwzx r28, r7, r28
   142 M xor r4, r5, r4
       B xor r0, r10, r0
   143 M lwzx r25, r30, r25
       B lwzx r25, r8, r25
   144 M lwzx r5, r12, r24
       B lwzx r10, r7, r24
   146 M lwzx r23, r10, r23
       B lwzx r23, r5, r23
   147 M xor r26, r26, r4
       B xor r26, r26, r0
   148 M lwzx r22, r11, r22
       B lwzx r22, r4, r22
   149 M xor r24, r25, r5
       B xor r24, r25, r10
   151 M lwz r27, 4(r3)
       B xor r22, r23, r22
   152 M xor r22, r23, r22
       B lwz r27, 4(r3)
   153 M lwzx r21, r30, r21
       B lwzx r21, r8, r21
   155 M lwzx r20, r12, r20
       B lwzx r20, r7, r20
   156 M xor r4, r17, r31
       B xor r0, r17, r31
   157 M lwzx r8, r10, r8
       B lwzx r12, r5, r12
   158 M xor r5, r27, r26
       B xor r10, r27, r26
   159 M lwzx r7, r11, r7
       B lwzx r11, r4, r11
   161 M lwz r21, 8(r3)
       B lwz r23, 8(r3)
   162 M xor r7, r8, r7
       B xor r11, r12, r11
   163 M lwz r8, 0xc(r3)
       B lwz r21, 0xc(r3)
   164 M xor r7, r20, r7
       B xor r12, r20, r11
   165 M xor r17, r21, r22
       B xor r11, r23, r22
   166 M xor r7, r8, r7
       B xor r12, r21, r12
   169 M rlwinm r20, r5, 2, 0x16, 0x1d
       B rlwinm r20, r10, 2, 0x16, 0x1d
   170 M rlwinm r24, r7, 0xa, 0x16, 0x1d
       B rlwinm r26, r0, 2, 0x16, 0x1d
   171 M rlwinm r27, r5, 0x1a, 0x16, 0x1d
       B rlwinm r31, r0, 0xa, 0x16, 0x1d
   172 M rlwinm r23, r4, 0x1a, 0x16, 0x1d
       B rlwinm r24, r11, 2, 0x16, 0x1d
   173 M rlwinm r26, r4, 2, 0x16, 0x1d
       B rlwinm r8, r0, 0x12, 0x16, 0x1d
   174 M rlwinm r21, r7, 0x1a, 0x16, 0x1d
       B rlwinm r5, r0, 0x1a, 0x16, 0x1d
   175 M rlwinm r31, r4, 0xa, 0x16, 0x1d
       B rlwinm r25, r10, 0x12, 0x16, 0x1d
   176 M rlwinm r22, r4, 0x12, 0x16, 0x1d
       B rlwinm r27, r10, 0x1a, 0x16, 0x1d
   177 M rlwinm r11, r7, 2, 0x16, 0x1d
       B rlwinm r9, r10, 0xa, 0x16, 0x1d
   178 M rlwinm r29, r7, 0x12, 0x16, 0x1d
       B rlwinm r23, r12, 0x1a, 0x16, 0x1d
   179 M rlwinm r28, r8, 0xa, 0x16, 0x1d
       B rlwinm r28, r12, 0xa, 0x16, 0x1d
   180 M lwzx r24, r30, r24
       B lwzx r0, r30, r20
   181 M rlwinm r9, r5, 0xa, 0x16, 0x1d
       B rlwinm r21, r11, 0x1a, 0x16, 0x1d
   182 M rlwinm r0, r5, 0x12, 0x16, 0x1d
       B lwzx r10, r30, r31
   183 M lwzx r26, r30, r26
       B rlwinm r22, r12, 0x12, 0x16, 0x1d
   184 M lwzx r27, r30, r27
       B clrlwi r31, r0, 0x18
   185 M rlwinm r12, r8, 0x12, 0x16, 0x1d
       B lwzx r25, r30, r25
   186 M lwzx r7, r30, r20
       B lwzx r26, r30, r26
   187 M rlwinm r10, r8, 0x1a, 0x16, 0x1d
       B rlwinm r4, r11, 0xa, 0x16, 0x1d
   188 M lwzx r4, r30, r31
       B rlwinm r29, r11, 0x12, 0x16, 0x1d
   189 M rlwinm r25, r8, 2, 0x16, 0x1d
       B lwzx r27, r30, r27
   190 M clrlwi r31, r7, 0x18
       B lwzx r11, r30, r21
   191 M lwzx r5, r30, r21
       B rlwinm r7, r12, 2, 0x16, 0x1d
   192 M lwzx r7, r30, r12
       B lwzx r0, r30, r22
   193 M rlwinm r24, r24, 0, 0, 7
       B rlwinm r25, r25, 0, 8, 0xf
   194 M rlwinm r12, r5, 0, 0x10, 0x17
       B rlwinm r12, r11, 0, 0x10, 0x17
   195 M lwzx r5, r30, r11
       B rlwinm r11, r10, 0, 0, 7
   196 M rlwinm r11, r4, 0, 0, 7
       B rlwinm r10, r0, 0, 8, 0xf
   197 M lwzx r4, r30, r10
       B lwzx r24, r30, r24
   198 M rlwinm r10, r7, 0, 8, 0xf
       B lwzx r0, r30, r9
   199 M lwzx r7, r30, r9
       B clrlwi r26, r26, 0x18
   200 M clrlwi r9, r5, 0x18
       B clrlwi r9, r24, 0x18
   201 M lwzx r5, r30, r22
       B lwzx r23, r30, r23
   202 M rlwinm r8, r4, 0, 0x10, 0x17
       B lwzx r24, r30, r8
   203 M lwzx r4, r30, r25
       B rlwinm r27, r27, 0, 0x10, 0x17
   204 M lwzx r25, r30, r0
       B rlwinm r8, r23, 0, 0x10, 0x17
   205 M xor r10, r11, r10
       B lwzx r23, r30, r7
   206 M lwzx r23, r30, r23
       B rlwinm r7, r0, 0, 0, 7
   207 M xor r22, r31, r12
       B lwzx r0, r30, r5
   208 M lwzx r28, r30, r28
       B rlwinm r5, r24, 0, 8, 0xf
   209 M xor r8, r9, r8
       B lwzx r24, r30, r4
   210 M lwzx r30, r30, r29
       B lwzx r28, r30, r28
   211 M rlwinm r7, r7, 0, 0, 7
       B xor r9, r9, r8
   212 M rlwinm r5, r5, 0, 8, 0xf
       B lwzx r30, r30, r29
   213 M clrlwi r4, r4, 0x18
       B xor r22, r31, r12
   214 M rlwinm r0, r23, 0, 0x10, 0x17
       B xor r10, r11, r10
   215 M rlwinm r25, r25, 0, 8, 0xf
       B xor r8, r7, r5
   216 M xor r5, r7, r5
       B rlwinm r24, r24, 0, 0, 7
   217 M clrlwi r26, r26, 0x18
       B clrlwi r4, r23, 0x18
   218 M xor r4, r4, r0
       B rlwinm r0, r0, 0, 0x10, 0x17
   219 M xor r0, r24, r25
       B xor r11, r22, r10
   220 M xor r7, r8, r5
       B xor r7, r4, r0
   221 M lwz r9, 4(r3)
       B xor r5, r24, r25
   222 M rlwinm r27, r27, 0, 0x10, 0x17
       B xor r9, r9, r8
   223 M rlwinm r29, r28, 0, 0, 7
       B lwz r10, 4(r3)
   224 M xor r18, r9, r7
       B rlwinm r29, r28, 0, 0, 7
   226 M xor r28, r26, r27
       B xor r18, r10, r9
   227 M lwz r11, 0(r3)
       B xor r4, r26, r27
   228 M xor r10, r22, r10
       B xor r0, r29, r12
   229 M rlwinm r9, r18, 0x18, 0x18, 0x1f
       B lwz r12, 0(r3)
   230 M xor r17, r11, r10
       B lwz r8, 8(r3)
   231 M xor r30, r29, r12
       B xor r5, r7, r5
   232 M xor r0, r4, r0
       B xor r17, r12, r11
   233 M lwz r5, 8(r3)
       B srwi r11, r18, 0x18
   234 M lwz r26, 0xc(r3)
       B xor r19, r8, r5
   235 M xor r3, r28, r30
       B rlwinm r10, r18, 0x10, 0x18, 0x1f
   236 M xor r19, r5, r0
       B srwi r24, r17, 0x18
   237 M srwi r4, r17, 0x18
       B rlwinm r23, r17, 0x10, 0x18, 0x1f
   238 M xor r20, r26, r3
       B rlwinm r12, r17, 0x18, 0x18, 0x1f
   239 M rlwinm r0, r17, 0x10, 0x18, 0x1f
       B rlwinm r9, r18, 0x18, 0x18, 0x1f
   240 M rlwinm r12, r17, 0x18, 0x18, 0x1f
       B srwi r8, r19, 0x18
   241 M srwi r11, r18, 0x18
       B rlwinm r7, r19, 0x10, 0x18, 0x1f
   242 M rlwinm r10, r18, 0x10, 0x18, 0x1f
       B rlwinm r5, r19, 0x18, 0x18, 0x1f
   243 M srwi r8, r19, 0x18
       B lwz r3, 0xc(r3)
   244 M rlwinm r7, r19, 0x10, 0x18, 0x1f
       B xor r0, r4, r0
   245 M rlwinm r5, r19, 0x18, 0x18, 0x1f
       B stb r24, 0(r6)
   246 M stb r4, 0(r6)
       B xor r20, r3, r0
   248 M rlwinm r3, r20, 0x10, 0x18, 0x1f
       B stb r23, 1(r6)
   249 M stb r0, 1(r6)
       B rlwinm r3, r20, 0x10, 0x18, 0x1f
```

ATERM_81405690 initial 59.309963%
- temporary: final AES words reuse dead state variables: 59.309963%; src 0x43c base 0x43c insns 271/271; diffs 199: [24, 26, 28, 30, 32, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45, 46, 47, 48, 49, 50];     24 M slwi r7, r7, 0x18;        B srawi r30, r4, 1
- temporary: input words packed before separate initial key XOR: compile failed
- local order: final substitution table view declared before paired rounds: 58.372692%; src 0x43c base 0x43c insns 271/271; diffs 217: [24, 26, 28, 30, 32, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45, 46, 47, 48, 49, 50];     24 M slwi r7, r7, 0x18;        B srawi r30, r4, 1
Retained best candidate

ATERM_81405254 initial 62.110703%
- temporary: all initial state declarations precede packed-word and key-XOR statements: 53.660515%; src 0x43c base 0x43c insns 271/271; diffs 225: [12, 13, 18, 20, 24, 26, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41];     12 M slwi r21, r11, 0x18;        B slwi r22, r11, 0x18
Retained best candidate

ATERM_81405690 initial 59.309963%
- temporary: all initial state declarations precede packed-word and key-XOR statements: 52.402214%; src 0x43c base 0x43c insns 271/271; diffs 214: [13, 14, 24, 26, 28, 30, 32, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47];     13 M lbz r11, 8(r5);        B slwi r21, r10, 0x10
Retained best candidate

## Small-BSS type correction

Original selected-BSSID symbol occupies eight bytes at .sbss+0x44; the previous declaration inferred six bytes from its six-byte MAC copy. Declare the original eight-byte address buffer, as with the interface-MAC buffers. All copies still use the real six-byte BSSID length. This changes no global address or section size: cancel remains at .sbss+0x4c. No storage or padding object is added.

ATERM_81402A24 initial 92.43346%
- branch readability: valid scan body inside positive-result branch: 92.43346%; src 0x410 base 0x41c insns 260/263; --- replace mine 6:7 base 6:7;   M    6 li r25, 0;   B    6 li r4, 0
- branch readability: direct negative-result failure guard with retained iteration direction: 92.43346%; src 0x410 base 0x41c insns 260/263; --- replace mine 6:7 base 6:7;   M    6 li r25, 0;   B    6 li r4, 0
Retained best candidate

The final scan variant keeps the direct negative-result failure guard. Its score and instruction count equal the positive-result variant (92.43346%, 260/263); only the successful final-iteration branch inversion is retained. Empty branches are not retained.

## Attempt coverage

Every baseline instruction residual has at least three successful distinct source trials. Failed and unchanged candidates are excluded; all sections, including later targeted trials, are counted.

- ATERM_81402FC0: 3 compiling trials.
- ATERM_81402E40: 5 compiling trials.
- ATERM_8140502C: 6 compiling trials.
- ATERM_814033F0: 3 compiling trials.
- ATERM_8140276C: 3 compiling trials.
- ATERM_81404844: 3 compiling trials.
- ATERM_81404BFC: 3 compiling trials.
- ATERM_814021BC: 3 compiling trials.
- ATERMi_AutoConfigThread: 3 compiling trials.
- ATERM_81402A24: 5 compiling trials.
- ATERM_814031DC: 6 compiling trials.
- ATERM_81405ACC: 3 compiling trials.
- ATERM_814038C8: 3 compiling trials.
- ATERM_81405254: 3 compiling trials.
- ATERM_81405690: 3 compiling trials.

## Remaining instruction residuals

| Function | objdiff % | Instructions (mine/original) | Evidence / remaining reason |
|---|---:|---|---|
| ATERM_814021BC | 96.61688 | 154/154 | settings aggregate base-address scheduling and temporary register allocation |
| ATERM_8140276C | 99.166664 | 174/174 | current/previous record and fallback flag register cycles |
| ATERM_81402A24 | 92.43346 | 260/263 | scan descriptor-view scheduling, alignment expression and MAC-loop guard; three instructions short |
| ATERM_81402E40 | 99.791664 | 96/96 | two argument-move ordering differences plus two cr1 normalization differences |
| ATERM_81402FC0 | 100.0 | 135/135 | objdiff 100; gate/ctxdiff has two cr1 address-normalization differences; raw bytes identical |
| ATERM_814031DC | 90.766914 | 129/133 | explicit terminal MAC break versus original CTR loop; four instructions short |
| ATERM_814033F0 | 99.56204 | 137/137 | result/key pointer register cycle |
| ATERM_814038C8 | 87.2755 | 972/951 | protocol frame and option/authentication loop scheduling; connection key accesses its owner field directly; 21 extra instructions remain |
| ATERMi_AutoConfigThread | 94.75 | 40/40 | NOR mask temporary and result-load scheduling |
| ATERM_81404844 | 99.0 | 117/117 | wrap pass/block/output/byte-offset register allocation |
| ATERM_81404BFC | 98.94403 | 268/268 | initial key byte-load order and AES-128 substitution view allocation |
| ATERM_8140502C | 99.565216 | 138/138 | round-reversal index/swap register allocation |
| ATERM_81405254 | 62.110703 | 271/271 | AES input, round and final XOR scheduling/register allocation; instruction count now identical |
| ATERM_81405690 | 59.309963 | 271/271 | inverse AES input, round and final XOR scheduling/register allocation; instruction count now identical |
| ATERM_81405ACC | 88.583336 | 139/144 | MD5 input-copy guards and state/index scheduling; five instructions short |

## Data audit

No artificial data objects or symbol names added. String pools are identical. These C units contain no vtables.

- .bss: mine 8144, original 8160 bytes; prefix mismatches 0/8144; extra alignment tail bytes 16, all zero True.
- .rodata: mine 10280, original 10280 bytes; prefix mismatches 0/10280; extra alignment tail bytes 0, all zero True.
- .data: mine 280, original 280 bytes; prefix mismatches 0/280; extra alignment tail bytes 0, all zero True.
- .sdata2: mine 7, original 8 bytes; prefix mismatches 0/7; extra alignment tail bytes 1, all zero True.
- .sdata: mine 53, original 56 bytes; prefix mismatches 0/53; extra alignment tail bytes 3, all zero True.
- .sbss: mine 84, original 80 bytes; prefix mismatches 0/80; extra alignment tail bytes 4, all zero True.

ATERM_81402FC0 raw .text bytes identical: True. SHA-256 mine 91a60a7585553b8702d6f6ff83d5a91eedfd3cbaf3a04fb25501c637a6f84acd, original 91a60a7585553b8702d6f6ff83d5a91eedfd3cbaf3a04fb25501c637a6f84acd. Raw bytes do not assert relocation identity. The gate instruction count remains authoritative.

Relocations at corresponding instruction offsets in objdiff-exact functions (observed mappings only, no object/config override):

- (('.sbss', 'gAtermAllocate', 12, 4, 0), ('.sbss', 'lbl_81698C9C', 12, 4, 0))
- (('.sbss', 'gAtermAllocation', 20, 4, 0), ('.sbss', 'lbl_81698CA4', 20, 4, 0))
- (('.sbss', 'gAtermCancelRequested', 80, 4, 0), ('.sbss', 'lbl_81698CDC', 76, 4, 0))
- (('.sbss', 'gAtermProgressCallback', 8, 4, 0), ('.sbss', 'lbl_81698C98', 8, 4, 0))
- (('.sbss', 'gAtermRelease', 16, 4, 0), ('.sbss', 'lbl_81698CA0', 16, 4, 0))
- (('.sbss', 'gAtermResult', 4, 4, 0), ('.sbss', 'lbl_81698C94', 4, 4, 0))
- (('.sbss', 'gAtermState', 0, 4, 0), ('.sbss', 'lbl_81698C90', 0, 4, 0))
- (('.sbss', 'gAtermThreadStarted', 24, 4, 0), ('.sbss', 'lbl_81698CA8', 24, 4, 0))
- (('.sdata', 'gAtermDeadline', 0, 4, 0), ('.sdata', 'lbl_81697218', 0, 4, 0))
- (('.sdata', 'gAtermScanBufferSize', 8, 4, 0), ('.sdata', 'lbl_81697220', 8, 4, 0))
- (('.sdata', 'gAtermScanLimit', 4, 4, 0), ('.sdata', 'lbl_8169721C', 4, 4, 0))

Data is not claimed 100%: ATERM switch-table and anonymous small-BSS symbol mappings remain incomplete; initialized .sdata is now 100%. Original extracted alignment tails are not synthesized.

Prior and current supplemental native verification PASS: AES-128/192/256 encrypt/decrypt, MD5 lengths 0/1/3/55/56/64/130, scan-list fallback/reset transitions, normalized BSSID and six-byte MAC formatting. Native verification checks behavior; the MWCC/object gate checks matching.

## Retained instruction differences


ATERM_81402A24

```text
src 0x410 base 0x41c insns 260/263
--- replace mine 6:7 base 6:7
  M    6 li r25, 0
  B    6 li r4, 0
--- replace mine 8:9 base 8:9
  M    8 li r27, -1
  B    8 li r22, -1
--- replace mine 11:12 base 11:12
  M   11 stw r25, 8(r1)
  B   11 stw r4, 8(r1)
--- replace mine 13:14 base 13:14
  M   13 addi r21, r3, 0x34
  B   13 addi r20, r3, 0x34
--- replace mine 15:16 base 15:16
  M   15 mr r3, r21
  B   15 mr r3, r20
--- replace mine 19:20 base 19:20
  M   19 mr r26, r3
  B   19 mr r19, r3
--- replace mine 21:22 base 21:22
  M   21 mr r5, r21
  B   21 mr r5, r20
--- replace mine 24:26 base 24:26
  M   24 cmpwi r26, 0
  M   25 beq 836
  B   24 cmpwi r19, 0
  B   25 beq 848
--- replace mine 27:28 base 27:28
  M   27 mr r3, r21
  B   27 mr r3, r20
--- replace mine 31:32 base 31:32
  M   31 mr r25, r3
  B   31 mr r18, r3
--- replace mine 33:34 base 33:34
  M   33 mr r5, r21
  B   33 mr r5, r20
--- replace mine 36:38 base 36:38
  M   36 cmpwi r25, 0
  M   37 beq 788
  B   36 cmpwi r18, 0
  B   37 beq 800
--- replace mine 40:42 base 40:42
  M   40 slwi r20, r0, 8
  M   41 addi r3, r20, 0x40
  B   40 slwi r15, r0, 8
  B   41 addi r3, r15, 0x40
--- replace mine 44:45 base 44:47
  M   44 addi r0, r3, 0x1f
  B   44 addic r4, r3, 0x1f
  B   45 li r0, -0x20
  B   46 and r16, r4, r0
--- delete mine 46:47 base 48:48
  M   46 rlwinm r24, r0, 0, 0, 0x1a
--- replace mine 48:49 base 49:51
  M   48 addi r23, r24, 2
  B   49 li r23, 0
  B   50 addi r27, r16, 2
--- replace mine 53:54 base 55:56
  M   53 b 608
  B   55 b 620
--- replace mine 62:66 base 64:68
  M   62 cmplw r0, r4
  M   63 ble 588
  M   64 mr r3, r24
  M   65 mr r4, r20
  B   64 cmplw r4, r0
  B   65 bge 600
  B   66 mr r3, r16
  B   67 mr r4, r15
--- replace mine 68:70 base 70:73
  M   68 mr r27, r3
  M   69 blt 660
  B   70 mr r22, r3
  B   71 bge 8
  B   72 b 660
--- replace mine 72:73 base 75:76
  M   72 bne 552
  B   75 bne 560
--- replace mine 76:77 base 79:80
  M   76 li r27, -6
  B   79 li r22, -6
--- replace mine 78:83 base 81:86
  M   78 mr r17, r23
  M   79 addi r16, r26, 8
  M   80 addi r15, r26, 0x2c
  M   81 addi r22, r26, 4
  M   82 li r19, 0
  B   81 mr r17, r27
  B   82 mr r25, r19
  B   83 addi r26, r19, 8
  B   84 addi r24, r19, 0x2c
  B   85 li r21, 0
--- replace mine 84:85 base 87:88
  M   84 mr r3, r16
  B   87 mr r3, r26
--- replace mine 91:92 base 94:95
  M   91 stw r30, 0(r22)
  B   94 stw r30, 4(r25)
--- replace mine 93:96 base 96:99
  M   93 stw r0, 0(r22)
  M   94 lwz r0, 0(r22)
  M   95 mr r3, r15
  B   96 stw r0, 4(r25)
  B   97 lwz r0, 4(r25)
  B   98 mr r3, r24
--- replace mine 98:100 base 101:103
  M   98 add r6, r22, r0
  M   99 stb r30, 4(r6)
  B  101 add r6, r25, r0
  B  102 stb r30, 8(r6)
--- replace mine 102:103 base 105:106
  M  102 sth r0, 0x2e(r22)
  B  105 sth r0, 0x32(r25)
--- replace mine 105:108 base 108:111
  M  105 addi r16, r16, 0x30
  M  106 addi r15, r15, 0x30
  M  107 addi r22, r22, 0x30
  B  108 addi r26, r26, 0x30
  B  109 addi r25, r25, 0x30
  B  110 addi r24, r24, 0x30
--- replace mine 109:110 base 112:113
  M  109 addi r19, r19, 1
  B  112 addi r21, r21, 1
--- replace mine 111:112 base 114:115
  M  111 cmpw r19, r27
  B  114 cmpw r21, r22
--- replace mine 113:114 base 116:117
  M  113 stw r27, 0(r26)
  B  116 stw r22, 0(r19)
--- replace mine 116:119 base 119:122
  M  116 beq 232
  M  117 mr r3, r26
  M  118 mr r4, r25
  B  119 beq 240
  B  120 mr r3, r19
  B  121 mr r4, r18
--- replace mine 122:123 base 125:126
  M  122 beq 208
  B  125 beq 216
--- replace mine 128:129 base 131:132
  M  128 add r14, r26, r0
  B  131 add r14, r19, r0
--- replace mine 135:136 base 138:140
  M  135 addi r7, r1, 0x18
  B  138 li r0, 6
  B  139 addi r8, r1, 0x18
--- replace mine 137:138 base 141:143
  M  137 li r6, 0
  B  141 li r7, 0
  B  142 li r3, 0x3a
--- replace mine 139:141 base 144:146
  M  139 li r0, 0x3a
  M  140 lbz r3, 0(r5)
  B  144 mtctr r0
  B  145 lbz r0, 0(r5)
--- replace mine 142:145 base 147:150
  M  142 rlwinm r8, r3, 0x1c, 0x1c, 0x1f
  M  143 clrlwi r9, r3, 0x1c
  M  144 cmpwi r8, 9
  B  147 rlwinm r6, r0, 0x1c, 0x1c, 0x1f
  B  148 clrlwi r9, r0, 0x1c
  B  149 cmpwi r6, 9
--- replace mine 146:149 base 151:154
  M  146 addi r3, r8, 0x30
  M  147 addi r8, r7, 1
  M  148 stb r3, 0(r7)
  B  151 addi r0, r6, 0x30
  B  152 addi r6, r8, 1
  B  153 stb r0, 0(r8)
--- replace mine 150:153 base 155:158
  M  150 addi r3, r8, 0x37
  M  151 addi r8, r7, 1
  M  152 stb r3, 0(r7)
  B  155 addi r0, r6, 0x37
  B  156 addi r6, r8, 1
  B  157 stb r0, 0(r8)
--- replace mine 155:156 base 160:172
  M  155 addi r3, r9, 0x30
  B  160 addi r0, r9, 0x30
  B  161 stb r0, 0(r6)
  B  162 addi r6, r6, 1
  B  163 b 16
  B  164 addi r0, r9, 0x37
  B  165 stb r0, 0(r6)
  B  166 addi r6, r6, 1
  B  167 cmpwi r7, 5
  B  168 subf r0, r8, r6
  B  169 stb r4, 0(r6)
  B  170 add r8, r8, r0
  B  171 bge 12
--- delete mine 158:168 base 174:174
  M  158 b 16
  M  159 addi r3, r9, 0x37
  M  160 stb r3, 0(r8)
  M  161 addi r8, r8, 1
  M  162 cmpwi r6, 5
  M  163 subf r3, r7, r8
  M  164 stb r4, 0(r8)
  M  165 add r7, r7, r3
  M  166 beq 20
  M  167 stb r0, 0(r7)
--- replace mine 169:171 base 175:176
  M  169 addi r6, r6, 1
  M  170 b -120
  B  175 bdnz -120
--- replace mine 172:173 base 177:178
  M  172 stb r0, 0(r7)
  B  177 stb r0, 0(r8)
--- replace mine 174:177 base 179:182
  M  174 mr r3, r25
  M  175 mr r4, r26
  M  176 mr r5, r21
  B  179 mr r3, r18
  B  180 mr r4, r19
  B  181 mr r5, r20
--- replace mine 204:206 base 209:211
  M  204 addi r18, r18, 1
  M  205 cmpwi r18, 0x12c
  B  209 addi r23, r23, 1
  B  210 cmpwi r23, 0x12c
--- replace mine 209:212 base 214:217
  M  209 beq -620
  M  210 cmpwi r18, 0x12c
  M  211 bge 88
  B  214 beq -632
  B  215 cmpwi r23, 0x12c
  B  216 bge 56
--- replace mine 225:227 base 230:232
  M  225 li r27, -3
  M  226 b 32
  B  230 li r22, -3
  B  231 b 24
--- replace mine 228:229 base 233:234
  M  228 li r27, 1
  B  233 li r22, 1
--- replace mine 230:234 base 235:237
  M  230 beq 16
  M  231 li r27, -8
  M  232 b 8
  M  233 li r27, -3
  B  235 beq 8
  B  236 li r22, -8
--- replace mine 241:242 base 244:245
  M  241 cmpwi r26, 0
  B  244 cmpwi r19, 0
--- replace mine 244:245 base 247:248
  M  244 mr r3, r26
  B  247 mr r3, r19
--- replace mine 247:248 base 250:251
  M  247 cmpwi r25, 0
  B  250 cmpwi r18, 0
--- replace mine 250:251 base 253:254
  M  250 mr r3, r25
  B  253 mr r3, r18
--- replace mine 254:255 base 257:258
  M  254 mr r3, r27
  B  257 mr r3, r22
```

ATERM_814038C8

```text
src 0xf30 base 0xedc insns 972/951
--- replace mine 5:7 base 5:11
  M    5 lis r0, 0
  M    6 lis r26, 0x1062
  B    5 li r0, 1
  B    6 lis r20, 0x1062
  B    7 lis r18, 0
  B    8 stw r0, 0(0)
  B    9 addi r18, r18, 0
  B   10 addi r0, r20, 0x4dd3
--- replace mine 8:25 base 12:15
  M    8 li r0, 1
  M    9 li r22, 0
  M   10 li r21, -5
  M   11 lwz r3, 0x12c(r1)
  M   12 li r20, 0
  M   13 stw r0, 0(0)
  M   14 addi r0, r26, 0x4dd3
  M   15 addi r3, r3, 0
  M   16 li r19, 0
  M   17 stw r3, 0x12c(r1)
  M   18 addi r25, r3, 0xba0
  M   19 addi r3, r3, 0x14a0
  M   20 li r18, 0
  M   21 stw r0, 0x130(r1)
  M   22 addi r24, r25, 0x8f8
  M   23 lwz r31, 0x12c(r1)
  M   24 addi r23, r3, 0x7f8
  B   12 addi r31, r18, 0x1498
  B   13 addi r15, r18, 0xc98
  B   14 addi r25, r18, 0x1c98
--- replace mine 26:31 base 16:27
  M   26 lis r27, -0x8000
  M   27 li r28, -1
  M   28 li r29, 8
  M   29 li r14, 2
  M   30 b 3688
  B   16 li r29, -5
  B   17 li r28, 0
  B   18 li r27, 0
  B   19 li r26, 0
  B   20 li r24, 0
  B   21 lis r19, -0x8000
  B   22 li r21, -1
  B   23 li r22, 8
  B   24 li r23, 2
  B   25 lis r14, 1
  B   26 b 3620
--- replace mine 32:33 base 28:29
  M   32 addi r4, r1, 0x14
  B   28 addi r4, r1, 0xc
--- replace mine 40:41 base 36:37
  M   40 lwz r0, 0xf8(r27)
  B   36 lwz r0, 0xf8(r19)
--- replace mine 45:46 base 41:42
  M   45 lwz r0, 0x130(r1)
  B   41 lwz r0, 0x12c(r1)
--- replace mine 57:58 base 53:54
  M   57 bgt 3580
  B   53 bgt 3512
--- replace mine 66:67 base 62:63
  M   66 mr r21, r3
  B   62 mr r29, r3
--- replace mine 68:70 base 64:66
  M   68 li r20, 1
  M   69 b 3532
  B   64 li r26, 1
  B   65 b 3464
--- replace mine 78:79 base 74:75
  M   78 stw r28, 0x6c(r1)
  B   74 stw r21, 0x6c(r1)
--- replace mine 81:83 base 77:79
  M   81 lwz r0, 0xf8(r27)
  M   82 addi r6, r26, 0x4dd3
  B   77 lwz r0, 0xf8(r19)
  B   78 addi r6, r20, 0x4dd3
--- replace mine 97:99 base 93:95
  M   97 stw r14, 0(0)
  M   98 b 3416
  B   93 stw r23, 0(0)
  B   94 b 3348
--- replace mine 101:102 base 97:98
  M  101 mr r21, r3
  B   97 mr r29, r3
--- replace mine 103:105 base 99:101
  M  103 li r20, 1
  M  104 b 3392
  B   99 li r26, 1
  B  100 b 3324
--- replace mine 106:108 base 102:104
  M  106 lwz r0, 0xf8(r27)
  M  107 addi r6, r26, 0x4dd3
  B  102 lwz r0, 0xf8(r19)
  B  103 addi r6, r20, 0x4dd3
--- replace mine 118:120 base 114:116
  M  118 lwz r0, 0xf8(r27)
  M  119 addi r6, r26, 0x4dd3
  B  114 lwz r0, 0xf8(r19)
  B  115 addi r6, r20, 0x4dd3
--- replace mine 129:130 base 125:126
  M  129 b 3292
  B  125 b 3224
--- replace mine 135:136 base 131:132
  M  135 mr r22, r3
  B  131 mr r30, r3
--- replace mine 137:140 base 133:136
  M  137 li r21, -2
  M  138 li r20, 1
  M  139 b 3252
  B  133 li r29, -2
  B  134 li r26, 1
  B  135 b 3184
--- replace mine 144:148 base 140:142
  M  144 lis r3, 1
  M  145 stb r29, 0x48(r1)
  M  146 addi r0, r3, -0x19ff
  M  147 stb r14, 0x49(r1)
  B  140 addi r0, r14, -0x19ff
  B  141 stb r22, 0x48(r1)
--- insert mine 149:149 base 143:144
  B  143 stb r23, 0x49(r1)
--- replace mine 151:152 base 146:147
  M  151 mr r3, r22
  B  146 mr r3, r30
--- replace mine 153:154 base 148:149
  M  153 stw r30, 0x4c(r1)
  B  148 stw r24, 0x4c(r1)
--- replace mine 156:157 base 151:152
  M  156 mr r21, r3
  B  151 mr r29, r3
--- replace mine 158:161 base 153:156
  M  158 li r21, -2
  M  159 li r20, 1
  M  160 b 3168
  B  153 li r29, -2
  B  154 li r26, 1
  B  155 b 3104
--- replace mine 163:164 base 158:159
  M  163 b 3156
  B  158 b 3092
--- replace mine 165:167 base 160:162
  M  165 lwz r0, 0xf8(r27)
  M  166 addi r6, r26, 0x4dd3
  B  160 lwz r0, 0xf8(r19)
  B  161 addi r6, r20, 0x4dd3
--- replace mine 175:176 base 170:171
  M  175 mr r3, r22
  B  170 mr r3, r30
--- replace mine 177:182 base 172:178
  M  177 li r21, -3
  M  178 li r20, 1
  M  179 b 3092
  M  180 stb r29, 0x40(r1)
  M  181 addi r3, r25, 0xe8
  B  172 li r29, -3
  B  173 li r26, 1
  B  174 b 3028
  B  175 stb r22, 0x40(r1)
  B  176 addi r3, r18, 0xc88
  B  177 addi r4, r1, 0x40
--- replace mine 183:185 base 179:181
  M  183 mr r3, r22
  M  184 addi r4, r25, 0xf8
  B  179 mr r3, r30
  B  180 addi r4, r18, 0xc98
--- replace mine 190:192 base 186:188
  M  190 ble 3048
  M  191 addi r3, r25, 0xf8
  B  186 ble 2980
  B  187 addi r3, r18, 0xc98
--- replace mine 195:196 base 191:192
  M  195 beq 3028
  B  191 beq 2960
--- replace mine 197:199 base 193:195
  M  197 lwz r0, 0xf8(r27)
  M  198 addi r6, r26, 0x4dd3
  B  193 lwz r0, 0xf8(r19)
  B  194 addi r6, r20, 0x4dd3
--- replace mine 215:216 base 211:212
  M  215 stw r28, 0x60(r1)
  B  211 stw r21, 0x60(r1)
--- replace mine 218:220 base 214:216
  M  218 lwz r0, 0xf8(r27)
  M  219 addi r6, r26, 0x4dd3
  B  214 lwz r0, 0xf8(r19)
  B  215 addi r6, r20, 0x4dd3
--- replace mine 234:235 base 230:238
  M  234 b 2872
  B  230 b 2804
  B  231 lwz r16, 0(0)
  B  232 li r3, 1
  B  233 bl 0
  B  234 lbz r11, 0(0)
  B  235 li r4, 0
  B  236 lbz r10, 0(0)
  B  237 li r5, 4
--- delete mine 236:237 base 239:239
  M  236 li r3, 1
--- delete mine 240:242 base 242:242
  M  240 lbz r5, 0(0)
  M  241 lbz r4, 0(0)
--- replace mine 243:251 base 243:252
  M  243 stb r9, 0x30(r1)
  M  244 lwz r15, 0(0)
  M  245 stb r8, 0x31(r1)
  M  246 stb r7, 0x32(r1)
  M  247 stb r6, 0x33(r1)
  M  248 stb r5, 0x34(r1)
  M  249 stb r4, 0x35(r1)
  M  250 stb r0, 0x36(r1)
  B  243 sth r3, 8(r1)
  B  244 mr r3, r16
  B  245 stb r11, 0x38(r1)
  B  246 stb r10, 0x39(r1)
  B  247 stb r9, 0x3a(r1)
  B  248 stb r8, 0x3b(r1)
  B  249 stb r7, 0x3c(r1)
  B  250 stb r6, 0x3d(r1)
  B  251 stb r0, 0x3e(r1)
--- replace mine 252:254 base 253:260
  M  252 sth r3, 8(r1)
  M  253 mr r3, r15
  B  253 li r3, 1
  B  254 bl 0
  B  255 sth r3, 0(r16)
  B  256 li r3, 2
  B  257 bl 0
  B  258 sth r3, 2(r16)
  B  259 addi r3, r16, 4
--- replace mine 257:268 base 263:264
  M  257 li r3, 1
  M  258 bl 0
  M  259 sth r3, 0(r15)
  M  260 li r3, 2
  M  261 bl 0
  M  262 sth r3, 2(r15)
  M  263 addi r3, r15, 4
  M  264 li r4, 0
  M  265 li r5, 4
  M  266 bl 0
  M  267 addi r3, r15, 4
  B  263 addi r3, r16, 4
--- replace mine 271:272 base 267:268
  M  271 addi r3, r15, 8
  B  267 addi r17, r16, 8
--- insert mine 273:273 base 269:270
  B  269 mr r3, r17
--- replace mine 277:278 base 274:275
  M  277 sth r3, 8(r15)
  B  274 sth r3, 0(r17)
--- replace mine 280:282 base 277:279
  M  280 sth r3, 0xa(r15)
  M  281 addi r3, r15, 0xc
  B  277 sth r3, 2(r17)
  B  278 addi r3, r17, 4
--- replace mine 285:286 base 282:283
  M  285 addi r3, r15, 0xc
  B  282 addi r3, r17, 4
--- replace mine 290:291 base 287:288
  M  290 addi r15, r15, 0x10
  B  287 addi r16, r17, 8
--- replace mine 293:294 base 290:291
  M  293 mr r3, r15
  B  290 mr r3, r16
--- replace mine 299:300 base 296:297
  M  299 sth r3, 0(r15)
  B  296 sth r3, 0(r16)
--- replace mine 302:304 base 299:301
  M  302 sth r3, 2(r15)
  M  303 addi r3, r15, 4
  B  299 sth r3, 2(r16)
  B  300 addi r3, r17, 0xc
--- replace mine 307:308 base 304:305
  M  307 addi r3, r15, 4
  B  304 addi r3, r17, 0xc
--- replace mine 311:313 base 308:311
  M  311 addi r15, r15, 8
  M  312 mr r3, r15
  B  308 addi r16, r17, 0x10
  B  309 mr r17, r16
  B  310 mr r3, r16
--- replace mine 318:319 base 316:317
  M  318 sth r3, 0(r15)
  B  316 sth r3, 0(r16)
--- replace mine 321:323 base 319:321
  M  321 sth r3, 2(r15)
  M  322 addi r3, r15, 4
  B  319 sth r3, 2(r16)
  B  320 addi r3, r16, 4
--- replace mine 326:328 base 324:326
  M  326 addi r3, r15, 4
  M  327 addi r4, r1, 0x30
  B  324 addi r3, r16, 4
  B  325 addi r4, r1, 0x38
--- replace mine 331:332 base 329:330
  M  331 addi r15, r15, 0x10
  B  329 addi r16, r16, 0x10
--- replace mine 333:335 base 331:333
  M  333 beq 80
  M  334 mr r3, r15
  B  331 beq 84
  B  332 addi r16, r17, 0x10
--- insert mine 336:336 base 334:335
  B  334 mr r3, r16
--- replace mine 340:341 base 339:340
  M  340 sth r3, 0(r15)
  B  339 sth r3, 0(r16)
--- replace mine 343:345 base 342:344
  M  343 sth r3, 2(r15)
  M  344 addi r3, r15, 4
  B  342 sth r3, 2(r16)
  B  343 addi r3, r17, 0x14
--- replace mine 348:349 base 347:348
  M  348 addi r3, r15, 4
  B  347 addi r3, r17, 0x14
--- replace mine 352:353 base 351:352
  M  352 addi r15, r15, 0x10
  B  351 addi r16, r17, 0x20
--- replace mine 354:356 base 353:355
  M  354 mr r5, r24
  M  355 addi r3, r25, 0xf8
  B  353 addi r3, r18, 0xc98
  B  354 addi r5, r18, 0x1498
--- replace mine 357:358 base 356:357
  M  357 subf r6, r0, r15
  B  356 subf r6, r0, r16
--- replace mine 362:365 base 361:364
  M  362 lis r3, 1
  M  363 addi r0, r3, -0x19ff
  M  364 stb r29, 0x28(r1)
  B  361 addi r0, r14, -0x19ff
  B  362 mr r16, r3
  B  363 stb r22, 0x30(r1)
--- replace mine 366:368 base 365:367
  M  366 stb r14, 0x29(r1)
  M  367 stw r28, 0x2c(r1)
  B  365 stb r23, 0x31(r1)
  B  366 stw r21, 0x34(r1)
--- replace mine 369:374 base 368:373
  M  369 sth r3, 0x2a(r1)
  M  370 mr r3, r22
  M  371 lwz r5, 0(0)
  M  372 addi r4, r25, 0xf8
  M  373 addi r7, r1, 0x28
  B  368 sth r3, 0x32(r1)
  B  369 mr r3, r30
  B  370 mr r5, r16
  B  371 addi r4, r18, 0xc98
  B  372 addi r7, r1, 0x30
--- replace mine 377:379 base 376:378
  M  377 lwz r0, 0xf8(r27)
  M  378 addi r6, r26, 0x4dd3
  B  376 lwz r0, 0xf8(r19)
  B  377 addi r6, r20, 0x4dd3
--- replace mine 385:386 base 384:385
  M  385 mr r18, r4
  B  384 mr r28, r4
--- replace mine 387:388 base 386:387
  M  387 b 2260
  B  386 b 2180
--- replace mine 389:391 base 388:390
  M  389 lwz r0, 0xf8(r27)
  M  390 addi r6, r26, 0x4dd3
  B  388 lwz r0, 0xf8(r19)
  B  389 addi r6, r20, 0x4dd3
--- replace mine 399:400 base 398:399
  M  399 mr r3, r22
  B  398 mr r3, r30
--- replace mine 401:406 base 400:405
  M  401 li r21, -4
  M  402 li r20, 1
  M  403 b 2196
  M  404 mr r3, r22
  M  405 addi r4, r25, 0xf8
  B  400 li r29, -4
  B  401 li r26, 1
  B  402 b 2116
  B  403 mr r3, r30
  B  404 addi r4, r18, 0xc98
--- replace mine 411:414 base 410:413
  M  411 ble 952
  M  412 lhz r3, 0xf8(r25)
  M  413 addi r15, r25, 0xf8
  B  410 ble 888
  B  411 lhz r3, 0(r15)
  B  412 li r17, 0
--- replace mine 419:429 base 418:426
  M  419 clrlwi r17, r3, 0x10
  M  420 mr r3, r15
  M  421 add r4, r15, r17
  M  422 addi r15, r15, 6
  M  423 addi r4, r4, 6
  M  424 li r16, 0
  M  425 cmplw cr1, r3, r4
  M  426 bge -7563
  M  427 subf r0, r3, r4
  M  428 addi r5, r4, -8
  B  418 clrlwi r16, r3, 0x10
  B  419 mr r4, r15
  B  420 add r3, r15, r16
  B  421 addi r3, r3, 6
  B  422 cmplw cr1, r15, r3
  B  423 bge -7579
  B  424 subf r0, r15, r3
  B  425 addi r5, r3, -8
--- replace mine 431:432 base 428:429
  M  431 bgt -7583
  B  428 bgt -7599
--- replace mine 433:434 base 430:431
  M  433 subf r0, r3, r0
  B  430 subf r0, r15, r0
--- replace mine 436:437 base 433:434
  M  436 cmplw r3, r5
  B  433 cmplw r15, r5
--- replace mine 438:455 base 435:452
  M  438 lbz r5, 0(r3)
  M  439 lbz r0, 1(r3)
  M  440 add r16, r16, r5
  M  441 lbz r5, 2(r3)
  M  442 add r16, r16, r0
  M  443 lbz r0, 3(r3)
  M  444 add r16, r16, r5
  M  445 lbz r5, 4(r3)
  M  446 add r16, r16, r0
  M  447 lbz r0, 5(r3)
  M  448 add r16, r16, r5
  M  449 lbz r5, 6(r3)
  M  450 add r16, r16, r0
  M  451 lbz r0, 7(r3)
  M  452 add r16, r16, r5
  M  453 addi r3, r3, 8
  M  454 add r16, r16, r0
  B  435 lbz r5, 0(r4)
  B  436 lbz r0, 1(r4)
  B  437 add r17, r17, r5
  B  438 lbz r5, 2(r4)
  B  439 add r17, r17, r0
  B  440 lbz r0, 3(r4)
  B  441 add r17, r17, r5
  B  442 lbz r5, 4(r4)
  B  443 add r17, r17, r0
  B  444 lbz r0, 5(r4)
  B  445 add r17, r17, r5
  B  446 lbz r5, 6(r4)
  B  447 add r17, r17, r0
  B  448 lbz r0, 7(r4)
  B  449 add r17, r17, r5
  B  450 addi r4, r4, 8
  B  451 add r17, r17, r0
--- replace mine 456:457 base 453:454
  M  456 subf r0, r3, r4
  B  453 subf r0, r4, r3
--- replace mine 458:459 base 455:456
  M  458 cmplw r3, r4
  B  455 cmplw r4, r3
--- replace mine 460:463 base 457:460
  M  460 lbz r0, 0(r3)
  M  461 addi r3, r3, 1
  M  462 add r16, r16, r0
  B  457 lbz r0, 0(r4)
  B  458 addi r4, r4, 1
  B  459 add r17, r17, r0
--- replace mine 464:465 base 461:462
  M  464 lhz r3, 0(r4)
  B  461 lhz r3, 0(r3)
--- replace mine 467:468 base 464:465
  M  467 clrlwi r0, r16, 0x10
  B  464 clrlwi r0, r17, 0x10
--- insert mine 469:469 base 466:467
  B  466 addi r4, r15, 6
--- replace mine 470:472 base 468:470
  M  470 li r15, 0
  M  471 cmpwi r15, 0
  B  468 li r4, 0
  B  469 cmpwi r4, 0
--- replace mine 473:475 base 471:473
  M  473 li r17, 0
  M  474 b 76
  B  471 li r16, 0
  B  472 b 72
--- replace mine 478:481 base 476:479
  M  478 li r17, 0
  M  479 b 56
  M  480 addic. r6, r25, 0xe8
  B  476 li r16, 0
  B  477 b 52
  B  478 addic. r0, r18, 0xc88
--- replace mine 482:485 base 480:483
  M  482 mr r3, r24
  M  483 mr r4, r15
  M  484 mr r5, r17
  B  480 mr r5, r16
  B  481 mr r6, r0
  B  482 addi r3, r18, 0x1498
--- replace mine 487:492 base 485:489
  M  487 addi r17, r17, -8
  M  488 b 20
  M  489 mr r3, r24
  M  490 mr r4, r15
  M  491 mr r5, r17
  B  485 addi r16, r16, -8
  B  486 b 16
  B  487 mr r5, r16
  B  488 addi r3, r18, 0x1498
--- replace mine 493:497 base 490:494
  M  493 cmpwi r17, 0
  M  494 beq 620
  M  495 lhz r3, 0(r24)
  M  496 addi r15, r24, 8
  B  490 cmpwi r16, 0
  B  491 beq 564
  B  492 lhz r3, 0x1498(r18)
  B  493 addi r16, r31, 8
--- replace mine 499:501 base 496:498
  M  499 add r0, r15, r0
  M  500 cmplw r15, r0
  B  496 add r0, r16, r0
  B  497 cmplw r16, r0
--- replace mine 502:503 base 499:500
  M  502 li r15, 0
  B  499 li r16, 0
--- replace mine 504:505 base 501:502
  M  504 lhz r3, 0(r15)
  B  501 lhz r3, 0(r16)
--- replace mine 507:509 base 504:506
  M  507 lhz r3, 2(r15)
  M  508 stw r0, 0x124(r1)
  B  504 lhz r3, 2(r16)
  B  505 stw r0, 0x120(r1)
--- replace mine 510:514 base 507:509
  M  510 addi r15, r15, 4
  M  511 cmpwi r15, 0
  M  512 beq 548
  M  513 lwz r0, 0x124(r1)
  B  507 addi r16, r16, 4
  B  508 lwz r0, 0x120(r1)
--- replace mine 515:516 base 510:511
  M  515 bne 536
  B  510 bne 1684
--- replace mine 517:519 base 512:514
  M  517 lwz r0, 0xf8(r27)
  M  518 addi r6, r26, 0x4dd3
  B  512 lwz r0, 0xf8(r19)
  B  513 addi r6, r20, 0x4dd3
--- replace mine 524:527 base 519:522
  M  524 stw r4, 0xc(r1)
  M  525 mr r4, r15
  M  526 addi r3, r24, 0x800
  B  519 stw r4, 0x14(r1)
  B  520 mr r4, r16
  B  521 addi r3, r18, 0x1c98
--- replace mine 530:532 base 525:531
  M  530 stw r30, 0xd8(r1)
  M  531 addi r4, r3, 0x2301
  B  525 stw r24, 0xdc(r1)
  B  526 addi r8, r3, 0x2301
  B  527 addi r4, r1, 0x14
  B  528 lis r3, -0x1032
  B  529 stw r24, 0xd8(r1)
  B  530 addi r7, r3, -0x5477
--- delete mine 533:537 base 532:532
  M  533 lis r3, -0x1032
  M  534 stw r4, 0xc8(r1)
  M  535 addi r7, r3, -0x5477
  M  536 addi r4, r1, 0xc
--- replace mine 538:539 base 533:534
  M  538 stw r7, 0xcc(r1)
  B  533 stw r8, 0xc8(r1)
--- insert mine 541:541 base 536:538
  B  536 stw r7, 0xcc(r1)
  B  537 addi r0, r3, 0x5476
--- replace mine 542:543 base 539:540
  M  542 addi r0, r3, 0x5476
  B  539 addi r3, r1, 0xc8
--- insert mine 544:544 base 541:544
  B  541 bl 0
  B  542 lwz r8, 0xd8(r1)
  B  543 lis r4, 0
--- replace mine 545:560 base 545:552
  M  545 stw r30, 0xdc(r1)
  M  546 bl 0
  M  547 lwz r5, 0xd8(r1)
  M  548 lis r4, 0
  M  549 lwz r11, 0xdc(r1)
  M  550 addi r3, r1, 0xc8
  M  551 rlwinm r12, r5, 0x1d, 0x1a, 0x1f
  M  552 rlwinm r10, r5, 0x18, 0x18, 0x1f
  M  553 rlwinm r9, r5, 0x10, 0x18, 0x1f
  M  554 srwi r8, r5, 0x18
  M  555 rlwinm r7, r11, 0x18, 0x18, 0x1f
  M  556 rlwinm r6, r11, 0x10, 0x18, 0x1f
  M  557 srwi r0, r11, 0x18
  M  558 stb r5, 0x38(r1)
  M  559 cmplwi r12, 0x38
  B  545 rlwinm r9, r8, 0x1d, 0x1a, 0x1f
  B  546 rlwinm r7, r8, 0x18, 0x18, 0x1f
  B  547 rlwinm r6, r8, 0x10, 0x18, 0x1f
  B  548 srwi r0, r8, 0x18
  B  549 stb r8, 0x28(r1)
  B  550 cmplwi r9, 0x38
  B  551 lwz r8, 0xdc(r1)
--- replace mine 561:569 base 553:564
  M  561 stb r10, 0x39(r1)
  M  562 subfic r5, r12, 0x78
  M  563 stb r9, 0x3a(r1)
  M  564 stb r8, 0x3b(r1)
  M  565 stb r11, 0x3c(r1)
  M  566 stb r7, 0x3d(r1)
  M  567 stb r6, 0x3e(r1)
  M  568 stb r0, 0x3f(r1)
  B  553 stb r7, 0x29(r1)
  B  554 subfic r5, r9, 0x78
  B  555 rlwinm r7, r8, 0x18, 0x18, 0x1f
  B  556 stb r6, 0x2a(r1)
  B  557 rlwinm r6, r8, 0x10, 0x18, 0x1f
  B  558 stb r0, 0x2b(r1)
  B  559 srwi r0, r8, 0x18
  B  560 stb r8, 0x2c(r1)
  B  561 stb r7, 0x2d(r1)
  B  562 stb r6, 0x2e(r1)
  B  563 stb r0, 0x2f(r1)
--- replace mine 570:571 base 565:566
  M  570 subfic r5, r12, 0x38
  B  565 subfic r5, r9, 0x38
--- replace mine 573:574 base 568:569
  M  573 addi r4, r1, 0x38
  B  568 addi r4, r1, 0x28
--- replace mine 576:621 base 571:604
  M  576 lwz r0, 0xc8(r1)
  M  577 addi r3, r1, 0xc8
  M  578 stb r0, 0x808(r24)
  M  579 lwz r0, 0xc8(r1)
  M  580 rlwinm r0, r0, 0x18, 0x18, 0x1f
  M  581 stb r0, 0x809(r24)
  M  582 lwz r0, 0xc8(r1)
  M  583 rlwinm r0, r0, 0x10, 0x18, 0x1f
  M  584 stb r0, 0x80a(r24)
  M  585 lwz r0, 0xc8(r1)
  M  586 srwi r0, r0, 0x18
  M  587 stb r0, 0x80b(r24)
  M  588 lwz r0, 0xcc(r1)
  M  589 stb r0, 0x80c(r24)
  M  590 lwz r0, 0xcc(r1)
  M  591 rlwinm r0, r0, 0x18, 0x18, 0x1f
  M  592 stb r0, 0x80d(r24)
  M  593 lwz r0, 0xcc(r1)
  M  594 rlwinm r0, r0, 0x10, 0x18, 0x1f
  M  595 stb r0, 0x80e(r24)
  M  596 lwz r0, 0xcc(r1)
  M  597 srwi r0, r0, 0x18
  M  598 stb r0, 0x80f(r24)
  M  599 lwz r0, 0xd0(r1)
  M  600 stb r0, 0x810(r24)
  M  601 lwz r0, 0xd0(r1)
  M  602 rlwinm r0, r0, 0x18, 0x18, 0x1f
  M  603 stb r0, 0x811(r24)
  M  604 lwz r0, 0xd0(r1)
  M  605 rlwinm r0, r0, 0x10, 0x18, 0x1f
  M  606 stb r0, 0x812(r24)
  M  607 lwz r0, 0xd0(r1)
  M  608 srwi r0, r0, 0x18
  M  609 stb r0, 0x813(r24)
  M  610 lwz r0, 0xd4(r1)
  M  611 stb r0, 0x814(r24)
  M  612 lwz r0, 0xd4(r1)
  M  613 rlwinm r0, r0, 0x18, 0x18, 0x1f
  M  614 stb r0, 0x815(r24)
  M  615 lwz r0, 0xd4(r1)
  M  616 rlwinm r0, r0, 0x10, 0x18, 0x1f
  M  617 stb r0, 0x816(r24)
  M  618 lwz r0, 0xd4(r1)
  M  619 srwi r0, r0, 0x18
  M  620 stb r0, 0x817(r24)
  B  571 lwz r5, 0xc8(r1)
  B  572 addi r6, r1, 0xc8
  B  573 stb r5, 8(r25)
  B  574 rlwinm r4, r5, 0x18, 0x18, 0x1f
  B  575 rlwinm r3, r5, 0x10, 0x18, 0x1f
  B  576 srwi r0, r5, 0x18
  B  577 stb r4, 9(r25)
  B  578 lwz r5, 0xcc(r1)
  B  579 stb r3, 0xa(r25)
  B  580 rlwinm r4, r5, 0x18, 0x18, 0x1f
  B  581 rlwinm r3, r5, 0x10, 0x18, 0x1f
  B  582 stb r0, 0xb(r25)
  B  583 srwi r0, r5, 0x18
  B  584 stb r5, 0xc(r25)
  B  585 lwz r5, 0xd0(r1)
  B  586 stb r4, 0xd(r25)
  B  587 rlwinm r4, r5, 0x18, 0x18, 0x1f
  B  588 stb r3, 0xe(r25)
  B  589 rlwinm r3, r5, 0x10, 0x18, 0x1f
  B  590 stb r0, 0xf(r25)
  B  591 srwi r0, r5, 0x18
  B  592 stb r5, 0x10(r25)
  B  593 lwz r5, 0xd4(r1)
  B  594 stb r4, 0x11(r25)
  B  595 rlwinm r4, r5, 0x18, 0x18, 0x1f
  B  596 stb r3, 0x12(r25)
  B  597 rlwinm r3, r5, 0x10, 0x18, 0x1f
  B  598 stb r0, 0x13(r25)
  B  599 srwi r0, r5, 0x18
  B  600 stb r5, 0x14(r25)
  B  601 stb r4, 0x15(r25)
  B  602 stb r3, 0x16(r25)
  B  603 stb r0, 0x17(r25)
--- replace mine 623:632 base 606:615
  M  623 stb r30, 0(r3)
  M  624 stb r30, 1(r3)
  M  625 stb r30, 2(r3)
  M  626 stb r30, 3(r3)
  M  627 stb r30, 4(r3)
  M  628 stb r30, 5(r3)
  M  629 stb r30, 6(r3)
  M  630 stb r30, 7(r3)
  M  631 addi r3, r3, 8
  B  606 stb r24, 0(r6)
  B  607 stb r24, 1(r6)
  B  608 stb r24, 2(r6)
  B  609 stb r24, 3(r6)
  B  610 stb r24, 4(r6)
  B  611 stb r24, 5(r6)
  B  612 stb r24, 6(r6)
  B  613 stb r24, 7(r6)
  B  614 addi r6, r6, 8
--- replace mine 641:643 base 624:626
  M  641 li r19, 0
  M  642 stw r28, 0(0)
  B  624 li r27, 0
  B  625 stw r21, 0(0)
--- replace mine 644:645 base 627:628
  M  644 stw r28, 0x54(r1)
  B  627 stw r21, 0x54(r1)
--- replace mine 648:649 base 631:632
  M  648 b 1216
  B  631 b 1200
--- replace mine 650:652 base 633:635
  M  650 lwz r0, 0xf8(r27)
  M  651 addi r6, r26, 0x4dd3
  B  633 lwz r0, 0xf8(r19)
  B  634 addi r6, r20, 0x4dd3
--- replace mine 657:658 base 640:641
  M  657 addi r0, r18, 0x7d0
  B  640 addi r0, r28, 0x7d0
--- replace mine 659:660 base 642:643
  M  659 blt 1172
  B  642 blt 1156
--- replace mine 662:665 base 645:647
  M  662 b 1160
  M  663 mr r3, r24
  M  664 addi r15, r24, 8
  B  645 b 1144
  B  646 mr r3, r31
--- replace mine 668:669 base 650:651
  M  668 mr r3, r15
  B  650 addi r16, r31, 8
--- insert mine 670:670 base 652:653
  B  652 mr r3, r16
--- replace mine 674:675 base 657:658
  M  674 sth r3, 0(r15)
  B  657 sth r3, 0(r16)
--- replace mine 677:679 base 660:662
  M  677 sth r3, 2(r15)
  M  678 addi r3, r15, 4
  B  660 sth r3, 2(r16)
  B  661 addi r3, r16, 4
--- replace mine 682:684 base 665:667
  M  682 addi r3, r15, 4
  M  683 addi r4, r24, 0x808
  B  665 addi r3, r16, 4
  B  666 addi r4, r25, 8
--- replace mine 686:690 base 669:673
  M  686 addi r0, r15, 0x10
  M  687 mr r5, r24
  M  688 subf r6, r24, r0
  M  689 addi r3, r25, 0xf8
  B  669 addi r0, r16, 0x10
  B  670 mr r5, r31
  B  671 subf r6, r31, r0
  B  672 addi r3, r18, 0xc98
--- replace mine 692:693 base 675:676
  M  692 addi r7, r25, 0xe8
  B  675 addi r7, r18, 0xc88
--- replace mine 694:695 base 677:678
  M  694 sth r0, 0(r24)
  B  677 sth r0, 0(r31)
--- replace mine 697:700 base 680:683
  M  697 lis r3, 1
  M  698 addi r0, r3, -0x19ff
  M  699 stb r29, 0x20(r1)
  B  680 addi r0, r14, -0x19ff
  B  681 mr r16, r3
  B  682 stb r22, 0x20(r1)
--- replace mine 701:703 base 684:686
  M  701 stb r14, 0x21(r1)
  M  702 stw r28, 0x24(r1)
  B  684 stb r23, 0x21(r1)
  B  685 stw r21, 0x24(r1)
--- replace mine 705:708 base 688:691
  M  705 mr r3, r22
  M  706 lwz r5, 0(0)
  M  707 addi r4, r25, 0xf8
  B  688 mr r3, r30
  B  689 mr r5, r16
  B  690 addi r4, r18, 0xc98
--- replace mine 712:714 base 695:697
  M  712 lwz r0, 0xf8(r27)
  M  713 addi r6, r26, 0x4dd3
  B  695 lwz r0, 0xf8(r19)
  B  696 addi r6, r20, 0x4dd3
--- replace mine 719:721 base 702:704
  M  719 lwz r3, 0x12c(r1)
  M  720 mr r18, r4
  B  702 mr r28, r4
  B  703 addi r3, r18, 0x948
--- delete mine 723:724 base 706:706
  M  723 addi r3, r3, 0x948
--- replace mine 725:729 base 707:711
  M  725 stw r29, 0(0)
  M  726 b 904
  M  727 mr r3, r22
  M  728 addi r4, r25, 0xf8
  B  707 stw r22, 0(0)
  B  708 b 892
  B  709 mr r3, r30
  B  710 addi r4, r18, 0xc98
--- replace mine 734:737 base 716:719
  M  734 ble 404
  M  735 lhz r3, 0xf8(r25)
  M  736 addi r16, r25, 0xf8
  B  716 ble 392
  B  717 lhz r3, 0(r15)
  B  718 li r16, 0
--- replace mine 739:741 base 721:723
  M  739 lhz r3, 2(r16)
  M  740 stw r0, 0x120(r1)
  B  721 lhz r3, 2(r15)
  B  722 stw r0, 0x124(r1)
--- replace mine 742:752 base 724:732
  M  742 clrlwi r15, r3, 0x10
  M  743 mr r3, r16
  M  744 add r4, r16, r15
  M  745 addi r17, r16, 6
  M  746 addi r4, r4, 6
  M  747 li r16, 0
  M  748 cmplw cr1, r3, r4
  M  749 bge -8855
  M  750 subf r0, r3, r4
  M  751 addi r5, r4, -8
  B  724 clrlwi r17, r3, 0x10
  B  725 mr r4, r15
  B  726 add r3, r15, r17
  B  727 addi r3, r3, 6
  B  728 cmplw cr1, r15, r3
  B  729 bge -8803
  B  730 subf r0, r15, r3
  B  731 addi r5, r3, -8
--- replace mine 754:755 base 734:735
  M  754 bgt -8875
  B  734 bgt -8823
--- replace mine 756:757 base 736:737
  M  756 subf r0, r3, r0
  B  736 subf r0, r15, r0
--- replace mine 759:760 base 739:740
  M  759 cmplw r3, r5
  B  739 cmplw r15, r5
--- replace mine 761:763 base 741:743
  M  761 lbz r5, 0(r3)
  M  762 lbz r0, 1(r3)
  B  741 lbz r5, 0(r4)
  B  742 lbz r0, 1(r4)
--- replace mine 764:765 base 744:745
  M  764 lbz r5, 2(r3)
  B  744 lbz r5, 2(r4)
--- replace mine 766:767 base 746:747
  M  766 lbz r0, 3(r3)
  B  746 lbz r0, 3(r4)
--- replace mine 768:769 base 748:749
  M  768 lbz r5, 4(r3)
  B  748 lbz r5, 4(r4)
--- replace mine 770:771 base 750:751
  M  770 lbz r0, 5(r3)
  B  750 lbz r0, 5(r4)
--- replace mine 772:773 base 752:753
  M  772 lbz r5, 6(r3)
  B  752 lbz r5, 6(r4)
--- replace mine 774:775 base 754:755
  M  774 lbz r0, 7(r3)
  B  754 lbz r0, 7(r4)
--- replace mine 776:777 base 756:757
  M  776 addi r3, r3, 8
  B  756 addi r4, r4, 8
--- replace mine 779:780 base 759:760
  M  779 subf r0, r3, r4
  B  759 subf r0, r4, r3
--- replace mine 781:782 base 761:762
  M  781 cmplw r3, r4
  B  761 cmplw r4, r3
--- replace mine 783:785 base 763:765
  M  783 lbz r0, 0(r3)
  M  784 addi r3, r3, 1
  B  763 lbz r0, 0(r4)
  B  764 addi r4, r4, 1
--- replace mine 787:788 base 767:768
  M  787 lhz r3, 0(r4)
  B  767 lhz r3, 0(r3)
--- insert mine 792:792 base 772:773
  B  772 addi r4, r15, 6
--- insert mine 793:793 base 774:777
  B  774 li r4, 0
  B  775 cmpwi r4, 0
  B  776 bne 12
--- replace mine 794:799 base 778:780
  M  794 cmpwi r17, 0
  M  795 bne 12
  M  796 li r15, 0
  M  797 b 80
  M  798 lwz r0, 0x120(r1)
  B  778 b 72
  B  779 lwz r0, 0x124(r1)
--- replace mine 801:809 base 782:789
  M  801 li r15, 0
  M  802 b 60
  M  803 cmpwi r23, 0
  M  804 beq 36
  M  805 mr r3, r24
  M  806 mr r4, r17
  M  807 mr r5, r15
  M  808 mr r6, r23
  B  782 li r17, 0
  B  783 b 52
  B  784 cmpwi r25, 0
  B  785 beq 32
  B  786 mr r5, r17
  B  787 mr r6, r25
  B  788 addi r3, r18, 0x1498
--- replace mine 811:816 base 791:795
  M  811 addi r15, r15, -8
  M  812 b 20
  M  813 mr r3, r24
  M  814 mr r4, r17
  M  815 mr r5, r15
  B  791 addi r17, r17, -8
  B  792 b 16
  B  793 mr r5, r17
  B  794 addi r3, r18, 0x1498
--- replace mine 817:819 base 796:798
  M  817 cmpwi r15, 0
  M  818 stw r15, 0(0)
  B  796 cmpwi r17, 0
  B  797 stw r17, 0(0)
--- replace mine 820:821 base 799:800
  M  820 mr r3, r24
  B  799 addi r3, r18, 0x1498
--- replace mine 824:825 base 803:804
  M  824 addi r3, r31, 0x948
  B  803 addi r3, r18, 0x948
--- replace mine 827:828 base 806:807
  M  827 li r19, 0
  B  806 li r27, 0
--- replace mine 836:838 base 815:817
  M  836 lwz r0, 0xf8(r27)
  M  837 addi r6, r26, 0x4dd3
  B  815 lwz r0, 0xf8(r19)
  B  816 addi r6, r20, 0x4dd3
--- replace mine 843:844 base 822:823
  M  843 addi r0, r18, 0x3e8
  B  822 addi r0, r28, 0x3e8
--- replace mine 846:848 base 825:827
  M  846 addi r19, r19, 1
  M  847 cmpwi r19, 0xa
  B  825 addi r27, r27, 1
  B  826 cmpwi r27, 0xa
--- replace mine 849:850 base 828:829
  M  849 mr r3, r22
  B  828 mr r3, r30
--- replace mine 851:853 base 830:832
  M  851 li r21, -2
  M  852 li r20, 1
  B  830 li r29, -2
  B  831 li r26, 1
--- replace mine 857:859 base 836:837
  M  857 mr r3, r24
  M  858 addi r15, r24, 8
  B  836 mr r3, r31
--- replace mine 862:863 base 840:841
  M  862 mr r3, r15
  B  840 addi r16, r31, 8
--- insert mine 864:864 base 842:843
  B  842 mr r3, r16
--- replace mine 868:869 base 847:848
  M  868 sth r3, 0(r15)
  B  847 sth r3, 0(r16)
--- replace mine 871:873 base 850:852
  M  871 sth r3, 2(r15)
  M  872 addi r3, r15, 4
  B  850 sth r3, 2(r16)
  B  851 addi r3, r16, 4
--- replace mine 876:877 base 855:856
  M  876 addi r3, r15, 4
  B  855 addi r3, r16, 4
--- replace mine 880:884 base 859:863
  M  880 addi r0, r15, 8
  M  881 mr r5, r24
  M  882 subf r6, r24, r0
  M  883 mr r7, r23
  B  859 addi r0, r16, 8
  B  860 mr r5, r31
  B  861 subf r6, r31, r0
  B  862 addi r3, r18, 0xc98
--- replace mine 886:887 base 865:866
  M  886 addi r3, r25, 0xf8
  B  865 addi r7, r18, 0x1c98
--- replace mine 888:889 base 867:868
  M  888 sth r0, 0(r24)
  B  867 sth r0, 0(r31)
--- replace mine 895:897 base 874:876
  M  895 lwz r0, 0xf8(r27)
  M  896 addi r6, r26, 0x4dd3
  B  874 lwz r0, 0xf8(r19)
  B  875 addi r6, r20, 0x4dd3
--- replace mine 902:905 base 881:884
  M  902 li r19, 0xa
  M  903 addi r18, r4, 0x3e8
  M  904 stw r19, 0(0)
  B  881 li r27, 0xa
  B  882 addi r28, r4, 0x3e8
  B  883 stw r27, 0(0)
--- replace mine 906:910 base 885:888
  M  906 lis r3, 1
  M  907 stb r29, 0x18(r1)
  M  908 addi r0, r3, -0x19ff
  M  909 stb r14, 0x19(r1)
  B  885 addi r0, r14, -0x19ff
  B  886 stb r22, 0x18(r1)
  B  887 lwz r16, 0(0)
--- replace mine 911:912 base 889:891
  M  911 stw r28, 0x1c(r1)
  B  889 stb r23, 0x19(r1)
  B  890 stw r21, 0x1c(r1)
--- replace mine 914:917 base 893:896
  M  914 mr r3, r22
  M  915 lwz r5, 0(0)
  M  916 addi r4, r25, 0xf8
  B  893 mr r3, r30
  B  894 mr r5, r16
  B  895 addi r4, r18, 0xc98
--- replace mine 921:923 base 900:902
  M  921 lwz r0, 0xf8(r27)
  M  922 addi r6, r26, 0x4dd3
  B  900 lwz r0, 0xf8(r19)
  B  901 addi r6, r20, 0x4dd3
--- replace mine 929:930 base 908:909
  M  929 mr r18, r4
  B  908 mr r28, r4
--- replace mine 933:935 base 912:914
  M  933 lwz r0, 0xf8(r27)
  M  934 addi r6, r26, 0x4dd3
  B  912 lwz r0, 0xf8(r19)
  B  913 addi r6, r20, 0x4dd3
--- replace mine 940:941 base 919:920
  M  940 addi r0, r18, 0x3e8
  B  919 addi r0, r28, 0x3e8
--- replace mine 943:945 base 922:924
  M  943 addi r19, r19, 1
  M  944 cmpwi r19, 0xa
  B  922 addi r27, r27, 1
  B  923 cmpwi r27, 0xa
--- replace mine 946:947 base 925:926
  M  946 li r20, 1
  B  925 li r26, 1
--- replace mine 948:949 base 927:928
  M  948 mr r21, r3
  B  927 mr r29, r3
--- replace mine 952:953 base 931:932
  M  952 cmpwi r20, 0
  B  931 cmpwi r26, 0
--- replace mine 956:958 base 935:937
  M  956 beq -3700
  M  957 cmpwi r22, 0
  B  935 beq -3632
  B  936 cmpwi r30, 0
--- replace mine 959:960 base 938:939
  M  959 mr r3, r22
  B  938 mr r3, r30
--- replace mine 964:965 base 943:944
  M  964 li r21, -8
  B  943 li r29, -8
--- replace mine 966:967 base 945:946
  M  966 mr r3, r21
  B  945 mr r3, r29
```

ATERM_81404844

```text
src 0x1d4 base 0x1d4 insns 117/117
diffs 20: [8, 27, 30, 36, 38, 39, 40, 41, 42, 45, 48, 54, 58, 60, 99, 100, 101, 103, 104, 106]
     8 M mr r24, r3
       B mr r25, r3
    27 M mr r28, r3
       B mr r26, r3
    30 M addi r3, r24, 8
       B addi r3, r25, 8
    36 M li r26, 0
       B li r28, 0
    38 M li r29, 8
       B li r29, 1
    39 M srawi r0, r26, 0x1f
       B srawi r0, r28, 0x1f
    40 M li r25, 1
       B li r24, 8
    41 M mulhwu r3, r27, r26
       B mulhwu r3, r27, r28
    42 M mullw r4, r4, r26
       B mullw r4, r4, r28
    45 M mullw r30, r27, r26
       B mullw r30, r27, r28
    48 M add r22, r24, r29
       B add r22, r25, r24
    54 M mr r4, r28
       B mr r4, r26
    58 M srawi r0, r25, 0x1f
       B srawi r0, r29, 0x1f
    60 M addc r3, r25, r30
       B addc r3, r29, r30
    99 M addi r25, r25, 1
       B addi r29, r29, 1
   100 M addi r29, r29, 8
       B addi r24, r24, 8
   101 M cmpw r25, r27
       B cmpw r29, r27
   103 M addi r26, r26, 1
       B addi r28, r28, 1
   104 M cmpwi r26, 6
       B cmpwi r28, 6
   106 M mr r3, r24
       B mr r3, r25
```

Full unit gate PASS: instruction exact remains 11/26; matched code 6576/19204 and data 18504/18864 unchanged; fuzzy 91.468864 -> 91.736305. All 15 baseline instruction residuals received at least three successful distinct source trials. Native AES, MD5, record comparison, MAC formatting and typed layout checks passed. No new instruction-exact function is claimed.

ATERM_8140502C initial 99.565216%
- temporary: explicit two-word snapshot for each key reversal swap: 99.565216%; src 0x228 base 0x228 insns 138/138; diffs 11: [11, 15, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r6, r3, 2;        B slwi r8, r3, 2
- temporary: swap snapshots use signed word storage with identical bits: 99.565216%; src 0x228 base 0x228 insns 138/138; diffs 11: [11, 15, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r6, r3, 2;        B slwi r8, r3, 2
- local order: reversal indices increment after four word swaps: 99.565216%; src 0x228 base 0x228 insns 138/138; diffs 11: [11, 15, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r6, r3, 2;        B slwi r8, r3, 2
Retained best candidate

ATERM_81402E40 initial 99.791664%
- temporary: payload pointer follows memset returned destination: 97.5%; src 0x180 base 0x180 insns 96/96; diffs 12: [5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 47, 52];      5 M mr r30, r3;        B mr r27, r5
- parameter type: encryption key is a read-only opaque key view: compile failed
- parameter type: sequence is the actual wire-format halfword: 99.166664%; src 0x180 base 0x180 insns 96/96; diffs 5: [9, 10, 37, 47, 52];      9 M mr r29, r7;        B mr r3, r27
Retained best candidate
