# AOSS round 7 attempts

Baseline at 7f055a58: instruction exact 15/21, matched code 6436/16192, data 3896/3928, fuzzy 87.587204%.

Work highest-percentage first. Check the stack frame and local order, branch direction, temporaries, then register allocation. Distinct successful compiling trials are counted; unchanged/failed trials are excluded. Both units have identical string pools before iteration. Complete initial and retained instruction differences are recorded below. No data pins or padding.

## AOSS_81400E0C initial instruction differences

objdiff reports 100%. Raw instructions agree except ctxdiff mis-normalizes absolute branch targets in CR1 bc operands. Keep source token/pool order and try ordinary byte accumulation, record-offset promotion, and record lifetime. Raw equality is audited separately; no function placement manipulation.

```text
src 0x2f8 base 0x2f8 insns 190/190
diffs 5: [19, 57, 62, 117, 122]
    19 M bgt -10875
       B bgt -11215
    57 M ble -11027
       B ble -11367
    62 M blt -11047
       B blt -11387
   117 M ble -11267
       B ble -11607
   122 M blt -11287
       B blt -11627
```

AOSS_81400E0C initial 100.0%
- temporary: shifted accumulation expressed as one add assignment: 96.89474%; src 0x2f8 base 0x2f8 insns 190/190; diffs 77: [19, 54, 56, 57, 59, 61, 62, 66, 67, 69, 72, 74, 75, 76, 77, 78, 79, 80, 81, 82];     19 M bgt -10875;        B bgt -11215
- temporary: native unsigned record offset instead of halfword temporary: 100.0%; src 0x2f8 base 0x2f8 insns 190/190; diffs 5: [19, 57, 62, 117, 122];     19 M bgt -10875;        B bgt -11215
- local order: current record initialized in declaration: 98.789474%; src 0x2f8 base 0x2f8 insns 190/190; diffs 12: [5, 6, 7, 9, 10, 11, 12, 19, 57, 62, 117, 122];      5 M mr r28, r3;        B mr r29, r4
Retained objdiff-100 candidate

## AOSS_814013AC initial instruction differences

Frame, all 114 instructions, branches and table/config view offsets agree. Two entry argument moves swap; search pointer, state-table base, selected option and remaining span have r29/r31/r24 cycles. Start with span initialization order, then header length call, then wire length width; all actual four configuration views stay in their original source order.

```text
src 0x1c8 base 0x1c8 insns 114/114
diffs 22: [6, 7, 14, 15, 16, 17, 20, 25, 29, 30, 34, 42, 55, 60, 65, 70, 75, 81, 87, 95]
     6 M mr r24, r5
       B mr r27, r3
     7 M mr r27, r3
       B mr r24, r5
    14 M mr r29, r4
       B mr r31, r4
    15 M li r31, 0
       B li r29, 0
    16 M lbz r3, 0(r29)
       B lbz r3, 0(r31)
    17 M lbzx r0, r31, r27
       B lbzx r0, r29, r27
    20 M lhz r3, 2(r29)
       B lhz r3, 2(r31)
    25 M add r29, r29, r0
       B add r31, r31, r0
    29 M lhz r3, 2(r29)
       B lhz r3, 2(r31)
    30 M addi r24, r29, 4
       B addi r31, r31, 4
    34 M clrlwi r31, r3, 0x10
       B clrlwi r24, r3, 0x10
    42 M lbz r0, 0(r24)
       B lbz r0, 0(r31)
    55 M mr r3, r24
       B mr r3, r31
    60 M mr r3, r24
       B mr r3, r31
    65 M mr r3, r24
       B mr r3, r31
    70 M mr r3, r24
       B mr r3, r31
    75 M lhz r3, 8(r24)
       B lhz r3, 8(r31)
    81 M lbz r0, 6(r24)
       B lbz r0, 6(r31)
    87 M addi r4, r24, 0xc
       B addi r4, r31, 0xc
    95 M lhz r3, 2(r24)
       B lhz r3, 2(r31)
    99 M subf. r31, r0, r31
       B subf. r24, r0, r24
   100 M add r24, r24, r0
       B add r31, r31, r0
```

AOSS_814013AC initial 98.77193%
- local order: response span assigned immediately before validation: 98.77193%; src 0x1c8 base 0x1c8 insns 114/114; diffs 22: [6, 7, 14, 15, 16, 17, 20, 25, 29, 30, 34, 42, 55, 60, 65, 70, 75, 81, 87, 95];      6 M mr r24, r5;        B mr r27, r3
- temporary: wire header length decoded directly before selected option view: 97.00877%; src 0x1c8 base 0x1c8 insns 114/114; diffs 27: [6, 7, 14, 15, 16, 17, 20, 25, 29, 30, 31, 32, 33, 34, 35, 36, 42, 55, 60, 65];      6 M mr r24, r5;        B mr r27, r3
- temporary: wire length is held in a halfword before promotion: 95.08772%; src 0x1c8 base 0x1c8 insns 114/114; diffs 26: [6, 7, 14, 15, 16, 17, 20, 22, 23, 25, 29, 30, 34, 42, 55, 60, 65, 70, 75, 81];      6 M mr r24, r5;        B mr r27, r3
Retained best candidate

## AOSS_81401E80 initial instruction differences

Frame, all 147 instructions, callee-saved registers, mask fill and round loop agree. Remaining 39 differences are the second XOR loop scratch r3/r4/r5 cycle plus CR1 branch normalization. Try a separate XOR traversal lifetime, independent byte view inside that loop, then real per-byte temporary.

```text
src 0x24c base 0x24c insns 147/147
diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86]
    53 M li r5, 0
       B li r3, 0
    54 M ble -15235
       B ble -15567
    56 M addi r3, r29, -8
       B addi r4, r29, -8
    58 M li r4, 0
       B li r5, 0
    59 M blt -15255
       B blt -15587
    63 M li r4, 1
       B li r5, 1
    64 M cmpwi r4, 0
       B cmpwi r5, 0
    66 M addi r0, r3, 7
       B addi r0, r4, 7
    69 M cmpwi r3, 0
       B cmpwi r4, 0
    71 M lbzx r6, r28, r5
       B lbzx r6, r28, r3
    72 M add r4, r26, r5
       B add r4, r26, r3
    73 M lbzx r0, r26, r5
       B lbzx r0, r26, r3
    74 M add r3, r28, r5
       B add r5, r28, r3
    76 M stbx r0, r28, r5
       B stbx r0, r28, r3
    77 M addi r5, r5, 8
       B addi r3, r3, 8
    78 M lbz r6, 1(r3)
       B lbz r6, 1(r5)
    81 M stb r0, 1(r3)
       B stb r0, 1(r5)
    82 M lbz r6, 2(r3)
       B lbz r6, 2(r5)
    85 M stb r0, 2(r3)
       B stb r0, 2(r5)
    86 M lbz r6, 3(r3)
       B lbz r6, 3(r5)
    89 M stb r0, 3(r3)
       B stb r0, 3(r5)
    90 M lbz r6, 4(r3)
       B lbz r6, 4(r5)
    93 M stb r0, 4(r3)
       B stb r0, 4(r5)
    94 M lbz r6, 5(r3)
       B lbz r6, 5(r5)
    97 M stb r0, 5(r3)
       B stb r0, 5(r5)
    98 M lbz r6, 6(r3)
       B lbz r6, 6(r5)
   101 M stb r0, 6(r3)
       B stb r0, 6(r5)
   102 M lbz r6, 7(r3)
       B lbz r6, 7(r5)
   105 M stb r0, 7(r3)
       B stb r0, 7(r5)
   107 M subf r0, r5, r29
       B subf r0, r3, r29
   108 M add r4, r28, r5
       B add r5, r28, r3
   109 M add r3, r26, r5
       B add r4, r26, r3
   111 M cmpw r5, r29
       B cmpw r3, r29
   113 M lbz r0, 0(r3)
       B lbz r0, 0(r4)
   114 M addi r5, r5, 1
       B addi r3, r3, 1
   115 M lbz r6, 0(r4)
       B lbz r6, 0(r5)
   116 M addi r3, r3, 1
       B addi r4, r4, 1
   118 M stb r0, 0(r4)
       B stb r0, 0(r5)
   119 M addi r4, r4, 1
       B addi r5, r5, 1
```

AOSS_81401E80 initial 98.5034%
- local order: XOR traversal has its own signed index lifetime: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
- temporary: XOR bytes use a named second-half view at first use: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
- temporary: input byte captured before XOR and publication: 98.605446%; src 0x24c base 0x24c insns 147/147; diffs 36: [54, 59, 72, 74, 75, 76, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91];     54 M ble -15235;        B ble -15567
Retained best candidate

## AOSS_81400830 initial instruction differences

Target derives its encrypted payload view at message+24 near entry; source repeats member addresses later. Frames agree; five extra instructions remain around schedule publication, checksum load/CRC signed traversal and the payload address lifetime. Give the real existing encrypted payload a named type (same fields/size) and try its early typed view, then checksum sampling, then RC4 output publication order.

```text
src 0x518 base 0x504 insns 326/321
--- replace mine 5:6 base 5:7
  M    5 mr r28, r3
  B    5 mr r26, r3
  B    6 addi r29, r3, 0x18
--- delete mine 7:8 base 8:8
  M    7 addi r4, r28, 0x10
--- insert mine 9:9 base 9:10
  B    9 addi r4, r26, 0x10
--- replace mine 22:24 base 23:25
  M   22 b 1192
  M   23 lhz r3, 6(r28)
  B   23 b 1168
  B   24 lhz r3, 6(r26)
--- replace mine 30:32 base 31:33
  M   30 b 1160
  M   31 lhz r3, 6(r28)
  B   31 b 1136
  B   32 lhz r3, 6(r26)
--- replace mine 40:41 base 41:42
  M   40 lhz r3, 0xc(r28)
  B   41 lhz r3, 0xc(r26)
--- replace mine 45:47 base 46:48
  M   45 b 1100
  M   46 lhz r3, 0x18(r28)
  B   46 b 1076
  B   47 lhz r3, 0(r29)
--- replace mine 48:50 base 49:51
  M   48 clrlwi r30, r3, 0x10
  M   49 mr r3, r30
  B   49 clrlwi r27, r3, 0x10
  B   50 mr r3, r27
--- replace mine 52:53 base 53:54
  M   52 mr r31, r3
  B   53 mr r28, r3
--- replace mine 57:60 base 58:61
  M   57 b 1052
  M   58 lbz r29, 0xe(r28)
  M   59 mr r3, r30
  B   58 b 1028
  B   59 lbz r31, 0xe(r26)
  B   60 mr r3, r27
--- replace mine 67:71 base 68:72
  M   67 b 932
  M   68 lis r27, 0
  M   69 addi r4, r28, 0x1a
  M   70 addi r3, r27, 0
  B   68 b 908
  B   69 lis r30, 0
  B   70 addi r4, r29, 2
  B   71 addi r3, r30, 0
--- replace mine 73:74 base 74:75
  M   73 addi r27, r27, 0
  B   74 addi r30, r30, 0
--- replace mine 75:76 base 76:77
  M   75 addi r3, r27, 2
  B   76 addi r3, r30, 2
--- replace mine 78:80 base 79:81
  M   78 mr r4, r27
  M   79 mr r6, r30
  B   79 mr r4, r30
  B   80 mr r6, r27
--- replace mine 83:89 base 84:90
  M   83 cmplwi r30, 0
  M   84 mr r3, r31
  M   85 mr r5, r30
  M   86 addi r4, r28, 0x1c
  M   87 ble 424
  M   88 rlwinm. r0, r30, 0x1f, 1, 0x1f
  B   84 cmplwi r27, 0
  B   85 mr r5, r28
  B   86 mr r4, r27
  B   87 addi r3, r29, 4
  B   88 ble 400
  B   89 rlwinm. r0, r27, 0x1f, 1, 0x1f
--- replace mine 90:92 base 91:93
  M   90 beq 272
  M   91 lwz r5, 0x10(r1)
  B   91 beq 256
  B   92 lwz r4, 0x10(r1)
--- replace mine 93:94 base 94:95
  M   93 addi r6, r5, 1
  B   94 addi r6, r4, 1
--- replace mine 95:96 base 96:97
  M   95 divwu r5, r6, r7
  B   96 divwu r4, r6, r7
--- replace mine 97:103 base 98:104
  M   97 mullw r5, r5, r7
  M   98 subf r5, r5, r6
  M   99 clrlwi r9, r5, 0x18
  M  100 lbzx r10, r8, r9
  M  101 add r5, r10, r0
  M  102 divwu r0, r5, r7
  B   98 mullw r4, r4, r7
  B   99 subf r4, r4, r6
  B  100 clrlwi r9, r4, 0x18
  B  101 lbzx r6, r8, r9
  B  102 add r4, r6, r0
  B  103 divwu r0, r4, r7
--- replace mine 104:107 base 105:108
  M  104 subf r0, r0, r5
  M  105 clrlwi r0, r0, 0x18
  M  106 lbzx r7, r8, r0
  B  105 subf r0, r0, r4
  B  106 clrlwi r4, r0, 0x18
  B  107 lbzx r0, r8, r4
--- replace mine 108:123 base 109:122
  M  108 add r6, r10, r7
  M  109 stw r0, 0x14(r1)
  M  110 stbx r10, r8, r0
  M  111 lwz r5, 0x18(r1)
  M  112 stbx r7, r5, r9
  M  113 lwz r5, 0x1c(r1)
  M  114 lwz r7, 0x18(r1)
  M  115 divwu r0, r6, r5
  M  116 lbz r8, 0(r4)
  M  117 mullw r0, r0, r5
  M  118 subf r0, r0, r6
  M  119 lbzx r0, r7, r0
  M  120 xor r0, r8, r0
  M  121 stb r0, 0(r3)
  M  122 lwz r5, 0x10(r1)
  B  109 add r7, r6, r0
  B  110 stw r4, 0x14(r1)
  B  111 stbx r6, r8, r4
  B  112 stbx r0, r8, r9
  B  113 lwz r6, 0x1c(r1)
  B  114 lbz r0, 0(r3)
  B  115 divwu r4, r7, r6
  B  116 mullw r4, r4, r6
  B  117 subf r4, r4, r7
  B  118 lbzx r4, r8, r4
  B  119 xor r0, r4, r0
  B  120 stb r0, 0(r5)
  B  121 lwz r4, 0x10(r1)
--- replace mine 124:125 base 123:124
  M  124 addi r6, r5, 1
  B  123 addi r6, r4, 1
--- replace mine 126:127 base 125:126
  M  126 divwu r5, r6, r7
  B  125 divwu r4, r6, r7
--- replace mine 128:134 base 127:133
  M  128 mullw r5, r5, r7
  M  129 subf r5, r5, r6
  M  130 clrlwi r9, r5, 0x18
  M  131 lbzx r10, r8, r9
  M  132 add r5, r10, r0
  M  133 divwu r0, r5, r7
  B  127 mullw r4, r4, r7
  B  128 subf r4, r4, r6
  B  129 clrlwi r9, r4, 0x18
  B  130 lbzx r6, r8, r9
  B  131 add r4, r6, r0
  B  132 divwu r0, r4, r7
--- replace mine 135:138 base 134:137
  M  135 subf r0, r0, r5
  M  136 clrlwi r0, r0, 0x18
  M  137 lbzx r7, r8, r0
  B  134 subf r0, r0, r4
  B  135 clrlwi r4, r0, 0x18
  B  136 lbzx r0, r8, r4
--- replace mine 139:154 base 138:144
  M  139 add r6, r10, r7
  M  140 stw r0, 0x14(r1)
  M  141 stbx r10, r8, r0
  M  142 lwz r5, 0x18(r1)
  M  143 stbx r7, r5, r9
  M  144 lwz r5, 0x1c(r1)
  M  145 lbz r8, 1(r4)
  M  146 addi r4, r4, 2
  M  147 divwu r0, r6, r5
  M  148 lwz r7, 0x18(r1)
  M  149 mullw r0, r0, r5
  M  150 subf r0, r0, r6
  M  151 lbzx r0, r7, r0
  M  152 xor r0, r8, r0
  M  153 stb r0, 1(r3)
  B  138 add r7, r6, r0
  B  139 stw r4, 0x14(r1)
  B  140 stbx r6, r8, r4
  B  141 stbx r0, r8, r9
  B  142 lwz r6, 0x1c(r1)
  B  143 lbz r0, 1(r3)
--- replace mine 155:160 base 145:157
  M  155 bdnz -256
  M  156 andi. r5, r30, 1
  M  157 beq 144
  M  158 mtctr r5
  M  159 lwz r5, 0x10(r1)
  B  145 divwu r4, r7, r6
  B  146 mullw r4, r4, r6
  B  147 subf r4, r4, r7
  B  148 lbzx r4, r8, r4
  B  149 xor r0, r4, r0
  B  150 stb r0, 1(r5)
  B  151 addi r5, r5, 2
  B  152 bdnz -240
  B  153 andi. r4, r27, 1
  B  154 beq 136
  B  155 mtctr r4
  B  156 lwz r4, 0x10(r1)
--- replace mine 161:162 base 158:159
  M  161 addi r6, r5, 1
  B  158 addi r6, r4, 1
--- replace mine 163:164 base 160:161
  M  163 divwu r5, r6, r7
  B  160 divwu r4, r6, r7
--- replace mine 165:171 base 162:168
  M  165 mullw r5, r5, r7
  M  166 subf r5, r5, r6
  M  167 clrlwi r9, r5, 0x18
  M  168 lbzx r10, r8, r9
  M  169 add r5, r10, r0
  M  170 divwu r0, r5, r7
  B  162 mullw r4, r4, r7
  B  163 subf r4, r4, r6
  B  164 clrlwi r9, r4, 0x18
  B  165 lbzx r6, r8, r9
  B  166 add r4, r6, r0
  B  167 divwu r0, r4, r7
--- replace mine 172:175 base 169:172
  M  172 subf r0, r0, r5
  M  173 clrlwi r0, r0, 0x18
  M  174 lbzx r7, r8, r0
  B  169 subf r0, r0, r4
  B  170 clrlwi r4, r0, 0x18
  B  171 lbzx r0, r8, r4
--- replace mine 176:191 base 173:179
  M  176 add r6, r10, r7
  M  177 stw r0, 0x14(r1)
  M  178 stbx r10, r8, r0
  M  179 lwz r5, 0x18(r1)
  M  180 stbx r7, r5, r9
  M  181 lwz r5, 0x1c(r1)
  M  182 lbz r8, 0(r4)
  M  183 addi r4, r4, 1
  M  184 divwu r0, r6, r5
  M  185 lwz r7, 0x18(r1)
  M  186 mullw r0, r0, r5
  M  187 subf r0, r0, r6
  M  188 lbzx r0, r7, r0
  M  189 xor r0, r8, r0
  M  190 stb r0, 0(r3)
  B  173 add r7, r6, r0
  B  174 stw r4, 0x14(r1)
  B  175 stbx r6, r8, r4
  B  176 stbx r0, r8, r9
  B  177 lwz r6, 0x1c(r1)
  B  178 lbz r0, 0(r3)
--- replace mine 192:193 base 180:188
  M  192 bdnz -132
  B  180 divwu r4, r7, r6
  B  181 mullw r4, r4, r6
  B  182 subf r4, r4, r7
  B  183 lbzx r4, r8, r4
  B  184 xor r0, r4, r0
  B  185 stb r0, 0(r5)
  B  186 addi r5, r5, 1
  B  187 bdnz -124
--- insert mine 194:194 base 189:191
  B  189 li r30, -1
  B  190 addi r4, r4, 0
--- delete mine 195:196 base 192:192
  M  195 addi r4, r4, 0
--- replace mine 197:199 base 193:194
  M  197 cmpwi cr1, r30, 0
  M  198 li r7, -1
  B  193 cmpwi cr1, r27, 0
--- replace mine 200:203 base 195:198
  M  200 ble -10079
  M  201 cmpwi r30, 8
  M  202 addi r5, r30, -8
  B  195 ble -10419
  B  196 cmpwi r27, 8
  B  197 addi r5, r27, -8
--- replace mine 205:206 base 200:201
  M  205 blt -10099
  B  200 blt -10439
--- replace mine 208:209 base 203:204
  M  208 cmpw r30, r0
  B  203 cmpw r27, r0
--- replace mine 220:223 base 215:218
  M  220 lbzx r5, r31, r4
  M  221 add r12, r31, r4
  M  222 srwi r6, r7, 8
  B  215 lbzx r5, r28, r4
  B  216 add r12, r28, r4
  B  217 srwi r6, r30, 8
--- replace mine 224:225 base 219:220
  M  224 xor r5, r7, r5
  B  219 xor r5, r30, r5
--- replace mine 269:270 base 264:265
  M  269 xor r7, r5, r0
  B  264 xor r30, r5, r0
--- replace mine 272:273 base 267:268
  M  272 subf r0, r4, r30
  B  267 subf r0, r4, r27
--- replace mine 274:275 base 269:270
  M  274 add r3, r31, r4
  B  269 add r3, r28, r4
--- replace mine 276:277 base 271:272
  M  276 cmpw r4, r30
  B  271 cmpw r4, r27
--- replace mine 279:280 base 274:275
  M  279 srwi r4, r7, 8
  B  274 srwi r4, r30, 8
--- replace mine 281:282 base 276:277
  M  281 xor r0, r7, r0
  B  276 xor r0, r30, r0
--- replace mine 284:285 base 279:280
  M  284 xor r7, r4, r0
  B  279 xor r30, r4, r0
--- replace mine 287:288 base 282:283
  M  287 xor r0, r7, r0
  B  282 xor r0, r30, r0
--- replace mine 289:290 base 284:285
  M  289 cmplw r0, r29
  B  284 cmplw r0, r31
--- replace mine 302:303 base 297:298
  M  302 mr r3, r31
  B  297 mr r3, r28
--- replace mine 310:313 base 305:308
  M  310 mr r4, r31
  M  311 mr r5, r30
  M  312 addi r3, r28, 0x18
  B  305 mr r3, r29
  B  306 mr r4, r28
  B  307 mr r5, r27
--- replace mine 314:315 base 309:310
  M  314 mr r3, r30
  B  309 mr r3, r27
--- replace mine 316:318 base 311:313
  M  316 sth r3, 0xa(r28)
  M  317 mr r3, r31
  B  311 sth r3, 0xa(r26)
  B  312 mr r3, r28
```

AOSS_81400830 initial 93.84112%
- temporary: encrypted payload view initialized at message entry: 93.84112%; src 0x518 base 0x504 insns 326/321; --- replace mine 5:6 base 5:7;   M    5 mr r28, r3;   B    5 mr r26, r3
- local order: checksum sampled before payload allocation with typed payload view: 93.24922%; src 0x518 base 0x504 insns 326/321; --- replace mine 5:6 base 5:7;   M    5 mr r28, r3;   B    5 mr r26, r3
- temporary: RC4 indices published after swap with typed payload view: 89.75078%; src 0x518 base 0x504 insns 326/321; --- replace mine 5:6 base 5:7;   M    5 mr r28, r3;   B    5 mr r26, r3
Retained best candidate

## AOSS_81401778 initial instruction differences

Two extra instructions remain. Target has independent response and CRC-table bases, while source file IPA shares a BSS owner base; hello bytes are at stack+0x20 versus target+0x18. RC4 unrolled loads/stores and schedule field reloads differ. Try hello stack-local order first, then explicit CRC table view, then signed bounded RC4 index.

```text
src 0x44c base 0x444 insns 275/273
--- replace mine 5:7 base 5:6
  M    5 lis r31, 0
  M    6 lwz r30, 0(0)
  B    5 lwz r28, 0(0)
--- replace mine 9:11 base 8:10
  M    9 addi r31, r31, 0
  M   10 addi r3, r1, 0x20
  B    8 addi r3, r1, 0x18
  B    9 li r30, 0
--- delete mine 12:13 base 11:11
  M   12 li r28, 0
--- replace mine 16:17 base 14:15
  M   16 mr r3, r30
  B   14 mr r3, r28
--- replace mine 22:23 base 20:22
  M   22 stb r3, 0x20(r1)
  B   20 stb r3, 0x18(r1)
  B   21 addi r31, r28, 0x18
--- replace mine 24:25 base 23:24
  M   24 stb r0, 0x21(r1)
  B   23 stb r0, 0x19(r1)
--- replace mine 26:28 base 25:28
  M   26 addi r4, r31, 0
  M   27 sth r3, 0x22(r1)
  B   25 lis r4, 0
  B   26 sth r3, 0x1a(r1)
  B   27 addi r4, r4, 0
--- replace mine 29:30 base 29:30
  M   29 stw r3, 0x24(r1)
  B   29 stw r3, 0x1c(r1)
--- replace mine 33:34 base 33:34
  M   33 stw r3, 0x24(r1)
  B   33 stw r3, 0x1c(r1)
--- replace mine 35:38 base 35:40
  M   35 bne 652
  M   36 addi r4, r31, 0x9a8
  M   37 li r28, 1
  B   35 bne 640
  B   36 lis r25, 0
  B   37 li r29, 1
  B   38 addi r4, r25, 0
  B   39 li r30, -1
--- replace mine 40:49 base 42:49
  M   40 lbz r5, 0x20(r1)
  M   41 li r3, -1
  M   42 addi r4, r31, 0x9a8
  M   43 lbz r0, 0x21(r1)
  M   44 xor r3, r5, r3
  M   45 lbz r9, 0x22(r1)
  M   46 rlwinm r3, r3, 2, 0x16, 0x1d
  M   47 lbz r8, 0x23(r1)
  M   48 lwzx r5, r4, r3
  B   42 lbz r6, 0x18(r1)
  B   43 addi r5, r25, 0
  B   44 srwi r7, r30, 8
  B   45 li r0, -1
  B   46 xor r4, r30, r6
  B   47 lbz r6, 0x19(r1)
  B   48 rlwinm r4, r4, 2, 0x16, 0x1d
--- replace mine 50:93 base 50:95
  M   50 lbz r7, 0x24(r1)
  M   51 xoris r11, r5, 0xff
  M   52 lbz r6, 0x25(r1)
  M   53 xori r11, r11, 0xffff
  M   54 lbz r5, 0x26(r1)
  M   55 xor r10, r11, r0
  M   56 lbz r0, 0x27(r1)
  M   57 rlwinm r10, r10, 2, 0x16, 0x1d
  M   58 srwi r11, r11, 8
  M   59 lwzx r10, r4, r10
  M   60 xor r10, r11, r10
  M   61 xor r9, r10, r9
  M   62 rlwinm r9, r9, 2, 0x16, 0x1d
  M   63 srwi r10, r10, 8
  M   64 lwzx r9, r4, r9
  M   65 xor r9, r10, r9
  M   66 xor r8, r9, r8
  M   67 rlwinm r8, r8, 2, 0x16, 0x1d
  M   68 srwi r9, r9, 8
  M   69 lwzx r8, r4, r8
  M   70 xor r8, r9, r8
  M   71 xor r7, r8, r7
  M   72 rlwinm r7, r7, 2, 0x16, 0x1d
  M   73 srwi r8, r8, 8
  M   74 lwzx r7, r4, r7
  M   75 xor r7, r8, r7
  M   76 xor r6, r7, r6
  M   77 rlwinm r6, r6, 2, 0x16, 0x1d
  M   78 srwi r7, r7, 8
  M   79 lwzx r6, r4, r6
  M   80 xor r6, r7, r6
  M   81 xor r5, r6, r5
  M   82 rlwinm r5, r5, 2, 0x16, 0x1d
  M   83 srwi r6, r6, 8
  M   84 lwzx r5, r4, r5
  M   85 xor r5, r6, r5
  M   86 xor r0, r5, r0
  M   87 rlwinm r0, r0, 2, 0x16, 0x1d
  M   88 srwi r5, r5, 8
  M   89 lwzx r0, r4, r0
  M   90 xor r0, r5, r0
  M   91 clrlwi r0, r0, 0x18
  M   92 xori r29, r0, 0xff
  B   50 lwzx r4, r5, r4
  B   51 xor r30, r7, r4
  B   52 xor r4, r30, r6
  B   53 lbz r6, 0x1a(r1)
  B   54 rlwinm r4, r4, 2, 0x16, 0x1d
  B   55 srwi r7, r30, 8
  B   56 lwzx r4, r5, r4
  B   57 xor r30, r7, r4
  B   58 xor r4, r30, r6
  B   59 lbz r6, 0x1b(r1)
  B   60 rlwinm r4, r4, 2, 0x16, 0x1d
  B   61 srwi r7, r30, 8
  B   62 lwzx r4, r5, r4
  B   63 xor r30, r7, r4
  B   64 xor r4, r30, r6
  B   65 lbz r6, 0x1c(r1)
  B   66 rlwinm r4, r4, 2, 0x16, 0x1d
  B   67 srwi r7, r30, 8
  B   68 lwzx r4, r5, r4
  B   69 xor r30, r7, r4
  B   70 xor r4, r30, r6
  B   71 lbz r6, 0x1d(r1)
  B   72 rlwinm r4, r4, 2, 0x16, 0x1d
  B   73 srwi r7, r30, 8
  B   74 lwzx r4, r5, r4
  B   75 xor r30, r7, r4
  B   76 xor r4, r30, r6
  B   77 lbz r6, 0x1e(r1)
  B   78 rlwinm r4, r4, 2, 0x16, 0x1d
  B   79 srwi r7, r30, 8
  B   80 lwzx r4, r5, r4
  B   81 xor r30, r7, r4
  B   82 xor r4, r30, r6
  B   83 lbz r6, 0x1f(r1)
  B   84 rlwinm r4, r4, 2, 0x16, 0x1d
  B   85 srwi r7, r30, 8
  B   86 lwzx r4, r5, r4
  B   87 xor r30, r7, r4
  B   88 xor r4, r30, r6
  B   89 rlwinm r4, r4, 2, 0x16, 0x1d
  B   90 srwi r7, r30, 8
  B   91 lwzx r4, r5, r4
  B   92 xor r30, r7, r4
  B   93 xor r0, r30, r0
  B   94 clrlwi r30, r0, 0x18
--- replace mine 96:97 base 98:99
  M   96 beq 388
  B   98 beq 368
--- replace mine 99:100 base 101:102
  M   99 addi r3, r30, 0x1a
  B  101 addi r3, r31, 2
--- replace mine 103:105 base 105:108
  M  103 addi r3, r31, 0x940
  M  104 addi r4, r30, 0x1a
  B  105 lis r25, 0
  B  106 addi r4, r31, 2
  B  107 addi r3, r25, 0
--- replace mine 107:108 base 110:111
  M  107 addi r25, r31, 0x940
  B  110 addi r25, r25, 0
--- replace mine 118:119 base 121:122
  M  118 addi r3, r1, 0x20
  B  121 addi r5, r1, 0x18
--- replace mine 121:123 base 124:147
  M  121 lwz r6, 0x28(r1)
  M  122 add r5, r30, r4
  B  124 lwz r3, 0x28(r1)
  B  125 add r6, r31, r4
  B  126 lwz r9, 0x34(r1)
  B  127 addi r4, r4, 1
  B  128 addi r8, r3, 1
  B  129 lwz r3, 0x30(r1)
  B  130 divwu r7, r8, r9
  B  131 lwz r0, 0x2c(r1)
  B  132 mullw r7, r7, r9
  B  133 subf r7, r7, r8
  B  134 clrlwi r8, r7, 0x18
  B  135 lbzx r10, r3, r8
  B  136 add r7, r10, r0
  B  137 divwu r0, r7, r9
  B  138 mullw r0, r0, r9
  B  139 subf r0, r0, r7
  B  140 clrlwi r0, r0, 0x18
  B  141 lbzx r7, r3, r0
  B  142 stw r8, 0x28(r1)
  B  143 add r9, r10, r7
  B  144 stw r0, 0x2c(r1)
  B  145 stbx r10, r3, r0
  B  146 stbx r7, r3, r8
--- insert mine 124:124 base 148:156
  B  148 lbz r0, 0(r5)
  B  149 divwu r7, r9, r8
  B  150 mullw r7, r7, r8
  B  151 subf r7, r7, r9
  B  152 lbzx r3, r3, r7
  B  153 xor r0, r3, r0
  B  154 stb r0, 4(r6)
  B  155 add r6, r31, r4
--- replace mine 125:128 base 157:162
  M  125 addi r9, r6, 1
  M  126 lwz r7, 0x30(r1)
  M  127 divwu r6, r9, r8
  B  157 lwz r3, 0x28(r1)
  B  158 lwz r9, 0x34(r1)
  B  159 addi r8, r3, 1
  B  160 lwz r3, 0x30(r1)
  B  161 divwu r7, r8, r9
--- replace mine 129:138 base 163:171
  M  129 mullw r6, r6, r8
  M  130 subf r6, r6, r9
  M  131 clrlwi r6, r6, 0x18
  M  132 stw r6, 0x28(r1)
  M  133 lbzx r9, r7, r6
  M  134 add r6, r9, r0
  M  135 divwu r0, r6, r8
  M  136 mullw r0, r0, r8
  M  137 subf r0, r0, r6
  B  163 mullw r7, r7, r9
  B  164 subf r7, r7, r8
  B  165 clrlwi r8, r7, 0x18
  B  166 lbzx r10, r3, r8
  B  167 add r7, r10, r0
  B  168 divwu r0, r7, r9
  B  169 mullw r0, r0, r9
  B  170 subf r0, r0, r7
--- insert mine 139:139 base 172:175
  B  172 lbzx r7, r3, r0
  B  173 stw r8, 0x28(r1)
  B  174 add r9, r10, r7
--- replace mine 140:158 base 176:178
  M  140 lbzx r8, r7, r0
  M  141 stbx r9, r7, r0
  M  142 add r7, r9, r8
  M  143 lwz r6, 0x30(r1)
  M  144 lwz r0, 0x28(r1)
  M  145 stbx r8, r6, r0
  M  146 lwz r6, 0x34(r1)
  M  147 lwz r8, 0x30(r1)
  M  148 divwu r0, r7, r6
  M  149 lbz r9, 0(r3)
  M  150 mullw r0, r0, r6
  M  151 subf r0, r0, r7
  M  152 lbzx r0, r8, r0
  M  153 xor r0, r9, r0
  M  154 stb r0, 0x1c(r5)
  M  155 add r5, r30, r4
  M  156 addi r4, r4, 1
  M  157 lwz r6, 0x28(r1)
  B  176 stbx r10, r3, r0
  B  177 stbx r7, r3, r8
--- replace mine 159:191 base 179:188
  M  159 addi r9, r6, 1
  M  160 lwz r7, 0x30(r1)
  M  161 divwu r6, r9, r8
  M  162 lwz r0, 0x2c(r1)
  M  163 mullw r6, r6, r8
  M  164 subf r6, r6, r9
  M  165 clrlwi r6, r6, 0x18
  M  166 stw r6, 0x28(r1)
  M  167 lbzx r9, r7, r6
  M  168 add r6, r9, r0
  M  169 divwu r0, r6, r8
  M  170 mullw r0, r0, r8
  M  171 subf r0, r0, r6
  M  172 clrlwi r0, r0, 0x18
  M  173 stw r0, 0x2c(r1)
  M  174 lbzx r8, r7, r0
  M  175 stbx r9, r7, r0
  M  176 add r7, r9, r8
  M  177 lwz r6, 0x30(r1)
  M  178 lwz r0, 0x28(r1)
  M  179 stbx r8, r6, r0
  M  180 lwz r6, 0x34(r1)
  M  181 lbz r9, 1(r3)
  M  182 addi r3, r3, 2
  M  183 divwu r0, r7, r6
  M  184 lwz r8, 0x30(r1)
  M  185 mullw r0, r0, r6
  M  186 subf r0, r0, r7
  M  187 lbzx r0, r8, r0
  M  188 xor r0, r9, r0
  M  189 stb r0, 0x1c(r5)
  M  190 bdnz -276
  B  179 lbz r0, 1(r5)
  B  180 addi r5, r5, 2
  B  181 divwu r7, r9, r8
  B  182 mullw r7, r7, r8
  B  183 subf r7, r7, r9
  B  184 lbzx r3, r3, r7
  B  185 xor r0, r3, r0
  B  186 stb r0, 4(r6)
  B  187 bdnz -252
--- replace mine 195:196 base 192:193
  M  195 sth r3, 0x18(r30)
  B  192 sth r3, 0(r31)
--- replace mine 198:200 base 195:197
  M  198 addi r3, r30, 0x18
  M  199 addi r4, r1, 0x20
  B  195 mr r3, r31
  B  196 addi r4, r1, 0x18
--- replace mine 202:203 base 199:200
  M  202 addi r3, r1, 0x10
  B  199 addi r3, r1, 0x20
--- replace mine 206:207 base 203:204
  M  206 addi r3, r1, 0x10
  B  203 addi r3, r1, 0x20
--- replace mine 216:217 base 213:214
  M  216 b 212
  B  213 b 216
--- replace mine 219:220 base 216:217
  M  219 sth r3, 0(r30)
  B  216 sth r3, 0(r28)
--- replace mine 222:224 base 219:221
  M  222 sth r26, 2(r30)
  M  223 sth r26, 4(r30)
  B  219 sth r26, 2(r28)
  B  220 sth r26, 4(r28)
--- replace mine 225:226 base 222:223
  M  225 sth r3, 6(r30)
  B  222 sth r3, 6(r28)
--- replace mine 227:228 base 224:225
  M  227 sth r26, 8(r30)
  B  224 sth r26, 8(r28)
--- replace mine 229:231 base 226:228
  M  229 sth r3, 0xa(r30)
  M  230 mr r3, r28
  B  226 sth r3, 0xa(r28)
  B  227 mr r3, r29
--- replace mine 232:233 base 229:230
  M  232 sth r3, 0xc(r30)
  B  229 sth r3, 0xc(r28)
--- replace mine 234:237 base 231:234
  M  234 addi r3, r30, 0x10
  M  235 addi r4, r1, 0x10
  M  236 stb r29, 0xe(r30)
  B  231 addi r3, r28, 0x10
  B  232 addi r4, r1, 0x20
  B  233 stb r30, 0xe(r28)
--- replace mine 238:239 base 235:236
  M  238 stb r0, 0xf(r30)
  B  235 stb r0, 0xf(r28)
--- replace mine 241:242 base 238:239
  M  241 addi r3, r1, 0x18
  B  238 addi r3, r1, 0x10
--- replace mine 248:249 base 245:246
  M  248 stb r0, 0x19(r1)
  B  245 stb r0, 0x11(r1)
--- replace mine 250:252 base 247:250
  M  250 addi r26, r31, 0
  M  251 sth r3, 0x1a(r1)
  B  247 lis r26, 0
  B  248 sth r3, 0x12(r1)
  B  249 addi r26, r26, 0
--- replace mine 255:256 base 253:254
  M  255 stw r3, 0x1c(r1)
  B  253 stw r3, 0x14(r1)
--- replace mine 259:260 base 257:258
  M  259 stw r0, 0x1c(r1)
  B  257 stw r0, 0x14(r1)
--- replace mine 262:264 base 260:262
  M  262 stb r0, 0x18(r1)
  M  263 mr r4, r30
  B  260 stb r0, 0x10(r1)
  B  261 mr r4, r28
--- replace mine 265:266 base 263:264
  M  265 addi r7, r1, 0x18
  B  263 addi r7, r1, 0x10
```

AOSS_81401778 initial 79.13919%
- stack local order: hello record follows key schedule: 79.16483%; src 0x44c base 0x444 insns 275/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- temporary: independent CRC table byte-processing view at function entry: 77.93407%; src 0x44c base 0x444 insns 275/273; --- replace mine 5:14 base 5:11;   M    5 lis r31, 0;   M    6 mr r25, r4
- temporary: bounded eight-byte RC4 loop uses signed index: 79.13919%; src 0x44c base 0x444 insns 275/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
Retained best candidate

The encrypted payload type/view trials did not improve code. The original anonymous field type is restored; no extra unused type declaration is retained.

## AOSS_Init_old initial instruction differences

Target prologue dynamically aligns the stack to 32 bytes with a 0x160 frame; source has an ordinary 0x100 frame. Original request record storage begins at aligned stack+0xa0. Original SOPoll descriptor preparation writes two full three-word descriptors (stack+0x70..0x84), while source has four array words and two optimized-away scalar result slots. Reconstruct those genuine SDK records, then align the request buffer observed in the original, then combine both. The source keeps the initialized fallback; the original r14 pre-assignment test remains uncertain.

```text
src 0x1758 base 0x18c0 insns 1494/1584
--- replace mine 0:1 base 0:4
  M    0 stwu r1, -0x100(r1)
  B    0 clrlwi r11, r1, 0x1b
  B    1 mr r12, r1
  B    2 subfic r11, r11, -0x160
  B    3 stwux r1, r1, r11
--- replace mine 2:4 base 5:7
  M    2 stw r0, 0x104(r1)
  M    3 addi r11, r1, 0x100
  B    5 mr r11, r12
  B    6 stw r0, 4(r12)
--- insert mine 5:5 base 8:9
  B    8 lhz r4, 0(0)
--- replace mine 6:9 base 10:15
  M    6 mr r31, r3
  M    7 stw r0, 8(r1)
  M    8 addi r3, r1, 0x58
  B   10 lhz r5, 0(0)
  B   11 mr r15, r3
  B   12 sth r4, 0x28(r1)
  B   13 addi r3, r1, 0xa0
  B   14 li r19, 0
--- insert mine 10:10 base 16:17
  B   16 sth r5, 0x2a(r1)
--- replace mine 11:12 base 18:20
  M   11 stw r0, 0xc(r1)
  B   18 stw r0, 0x24(r1)
  B   19 stw r0, 0x20(r1)
--- replace mine 13:28 base 21:36
  M   13 lha r23, 0x106(r31)
  M   14 cmpwi r23, -1
  M   15 bne 8
  M   16 li r23, 0xa
  M   17 lha r3, 0x10a(r31)
  M   18 cmpwi r3, -1
  M   19 bne 8
  M   20 li r3, 0xa
  M   21 lhz r22, 0x108(r31)
  M   22 cmplwi r22, 0xffff
  M   23 bne 8
  M   24 li r22, 0x64
  M   25 lhz r0, 0x10c(r31)
  M   26 cmplwi r0, 0xffff
  M   27 sth r0, 0xa(r1)
  B   21 lha r0, 0x106(r15)
  B   22 cmpwi r0, -1
  B   23 sth r0, 0x28(r1)
  B   24 bne 12
  B   25 li r0, 0xa
  B   26 sth r0, 0x28(r1)
  B   27 lha r0, 0x10a(r15)
  B   28 cmpwi r0, -1
  B   29 sth r0, 0x24(r1)
  B   30 bne 12
  B   31 li r0, 0xa
  B   32 sth r0, 0x24(r1)
  B   33 lha r0, 0x108(r15)
  B   34 cmpwi r0, -1
  B   35 sth r0, 0x2a(r1)
--- replace mine 30:34 base 38:47
  M   30 sth r0, 0xa(r1)
  M   31 lha r14, 0x10e(r31)
  M   32 sth r3, 8(r1)
  M   33 cmpwi r14, -1
  B   38 sth r0, 0x2a(r1)
  B   39 lha r0, 0x10c(r15)
  B   40 cmpwi r0, -1
  B   41 sth r0, 0x26(r1)
  B   42 bne 12
  B   43 li r0, 0x64
  B   44 sth r0, 0x26(r1)
  B   45 lha r20, 0x10e(r15)
  B   46 cmpwi r20, -1
--- replace mine 35:36 base 48:49
  M   35 li r14, 0x7d0
  B   48 li r20, 0x7d0
--- replace mine 41:42 base 54:55
  M   41 lis r15, 0
  B   54 lis r16, 0
--- replace mine 43:44 base 56:57
  M   43 addi r3, r15, 0
  B   56 addi r3, r16, 0
--- replace mine 47:48 base 60:61
  M   47 addi r0, r31, 6
  B   60 addi r0, r15, 6
--- replace mine 49:64 base 62:70
  M   49 stw r0, 0(r15)
  M   50 addi r0, r3, 0xb01
  M   51 addi r4, r15, 0
  M   52 li r15, 0
  M   53 lhz r3, 4(r31)
  M   54 stw r3, 4(r4)
  M   55 lhz r3, 0(r31)
  M   56 clrlwi r3, r3, 0x1c
  M   57 stw r3, 8(r4)
  M   58 lbz r3, 2(r31)
  M   59 stb r3, 0x19(r4)
  M   60 stw r15, 0xc(r4)
  M   61 stw r0, 0x10(r4)
  M   62 stb r15, 0x18(r4)
  M   63 lhz r0, 0(r31)
  B   62 stw r0, 0(r16)
  B   63 addi r5, r16, 0
  B   64 addi r3, r3, 0xb01
  B   65 li r16, 0
  B   66 lhz r0, 4(r15)
  B   67 stw r0, 4(r5)
  B   68 lhz r0, 0(r15)
  B   69 clrlwi r4, r0, 0x1c
--- replace mine 65:66 base 71:78
  M   65 cmpwi r0, 1
  B   71 stw r4, 8(r5)
  B   72 cmplwi r0, 1
  B   73 lbz r0, 2(r15)
  B   74 stb r0, 0x19(r5)
  B   75 stw r16, 0xc(r5)
  B   76 stw r3, 0x10(r5)
  B   77 stb r16, 0x18(r5)
--- replace mine 70:71 base 82:83
  M   70 stb r0, 0x116(r31)
  B   82 stb r0, 0x116(r15)
--- replace mine 75:76 base 87:88
  M   75 stw r15, 0(0)
  B   87 stw r16, 0(0)
--- replace mine 83:84 base 95:96
  M   83 b 5620
  B   95 b 5928
--- replace mine 85:86 base 97:98
  M   85 li r16, 0
  B   97 li r18, 0
--- replace mine 88:89 base 100:101
  M   88 stw r15, 0(0)
  B  100 stw r16, 0(0)
--- replace mine 91:92 base 103:105
  M   91 li r15, 0
  B  103 lha r16, 0x28(r1)
  B  104 li r17, 0
--- replace mine 96:97 base 109:110
  M   96 stw r15, 0(0)
  B  109 stw r17, 0(0)
--- replace mine 102:103 base 115:116
  M  102 stb r0, 0x116(r31)
  B  115 stb r0, 0x116(r15)
--- replace mine 116:117 base 129:130
  M  116 b 5488
  B  129 b 5792
--- replace mine 121:122 base 134:135
  M  121 stb r0, 0x116(r31)
  B  134 stb r0, 0x116(r15)
--- replace mine 135:136 base 148:149
  M  135 b 5412
  B  148 b 5716
--- replace mine 141:142 base 154:231
  M  141 stb r0, 0x116(r31)
  B  154 stb r0, 0x116(r15)
  B  155 lwz r3, 0(0)
  B  156 cmpwi r3, 0
  B  157 beq 16
  B  158 bl 0
  B  159 li r0, 0
  B  160 stw r0, 0(0)
  B  161 lwz r3, 0(0)
  B  162 cmpwi r3, 0
  B  163 beq 16
  B  164 bl 0
  B  165 li r0, 0
  B  166 stw r0, 0(0)
  B  167 li r3, -1
  B  168 b 5636
  B  169 cmpwi r3, 0
  B  170 beq 308
  B  171 extsh r0, r18
  B  172 cmpw r0, r16
  B  173 blt 68
  B  174 li r0, 1
  B  175 stb r0, 0x116(r15)
  B  176 lwz r3, 0(0)
  B  177 cmpwi r3, 0
  B  178 beq 16
  B  179 bl 0
  B  180 li r0, 0
  B  181 stw r0, 0(0)
  B  182 lwz r3, 0(0)
  B  183 cmpwi r3, 0
  B  184 beq 16
  B  185 bl 0
  B  186 li r0, 0
  B  187 stw r0, 0(0)
  B  188 li r3, -1
  B  189 b 5552
  B  190 lhz r21, 0x2a(r1)
  B  191 b 132
  B  192 lwz r0, 0(0)
  B  193 cmpwi r0, 1
  B  194 bne 68
  B  195 li r0, 0xf
  B  196 stb r0, 0x116(r15)
  B  197 lwz r3, 0(0)
  B  198 cmpwi r3, 0
  B  199 beq 16
  B  200 bl 0
  B  201 li r0, 0
  B  202 stw r0, 0(0)
  B  203 lwz r3, 0(0)
  B  204 cmpwi r3, 0
  B  205 beq 16
  B  206 bl 0
  B  207 li r0, 0
  B  208 stw r0, 0(0)
  B  209 li r3, -1
  B  210 b 5468
  B  211 cmplwi r21, 0x64
  B  212 ble 12
  B  213 li r3, 0x64
  B  214 b 8
  B  215 mr r3, r21
  B  216 bl 0
  B  217 cmplwi r21, 0x64
  B  218 ble 12
  B  219 li r0, 0x64
  B  220 b 8
  B  221 mr r0, r21
  B  222 subf r0, r0, r21
  B  223 clrlwi r21, r0, 0x10
  B  224 cmpwi r21, 0
  B  225 bne -132
  B  226 lwz r0, 0(0)
  B  227 cmpwi r0, 1
  B  228 bne 68
  B  229 li r0, 0xf
  B  230 stb r0, 0x116(r15)
--- replace mine 156:158 base 245:247
  M  156 cmpwi r3, 0
  M  157 bne 336
  B  245 addi r18, r18, 1
  B  246 b -564
--- replace mine 165:166 base 254:255
  M  165 addi r3, r1, 0x70
  B  254 addi r3, r1, 0xb8
--- replace mine 169:171 base 258:260
  M  169 lis r15, 0
  M  170 addi r3, r15, 0
  B  258 lis r16, 0
  B  259 addi r3, r16, 0
--- replace mine 172:173 base 261:262
  M  172 stw r3, 0x70(r1)
  B  261 stw r3, 0xb8(r1)
--- replace mine 174:176 base 263:265
  M  174 addi r3, r1, 0x74
  M  175 addi r4, r15, 0
  B  263 addi r3, r1, 0xbc
  B  264 addi r4, r16, 0
--- replace mine 179:180 base 268:269
  M  179 stw r0, 0x94(r1)
  B  268 stw r0, 0xdc(r1)
--- replace mine 181:184 base 270:274
  M  181 cmplwi r3, 0xe
  M  182 stw r3, 0x98(r1)
  M  183 bge 20
  B  270 cmplwi r3, 0xd
  B  271 stw r3, 0xe0(r1)
  B  272 ble 8
  B  273 b 20
--- replace mine 185:186 base 275:276
  M  185 addi r3, r1, 0x9c
  B  275 addi r3, r1, 0xe4
--- replace mine 196:200 base 286:289
  M  196 bne 108
  M  197 li r3, 0x58
  M  198 bl 0
  M  199 cmpwi r3, 0
  B  286 beq 76
  B  287 li r3, 0xc
  B  288 li r0, 0xf
--- replace mine 201:209 base 290:291
  M  201 beq 24
  M  202 li r4, 0
  M  203 li r5, 0x58
  M  204 bl 0
  M  205 li r15, 0
  M  206 b 432
  M  207 li r0, 0xf
  M  208 stb r0, 0x116(r31)
  B  290 stb r0, 0x116(r15)
--- replace mine 222:224 base 304:306
  M  222 b 5064
  M  223 li r3, 0xc
  B  304 b 5092
  B  305 beq 68
--- replace mine 225:227 base 307:308
  M  225 stw r3, 0(0)
  M  226 stb r0, 0x116(r31)
  B  307 stb r0, 0x116(r15)
--- replace mine 240:246 base 321:329
  M  240 b 4992
  M  241 cmpw r23, r16
  M  242 mr r17, r22
  M  243 bgt 188
  M  244 li r0, 1
  M  245 stb r0, 0x116(r31)
  B  321 b 5024
  B  322 li r3, 0x58
  B  323 bl 0
  B  324 cmpwi r3, 0
  B  325 stw r3, 0(0)
  B  326 bne 68
  B  327 li r0, 0xf
  B  328 stb r0, 0x116(r15)
--- replace mine 259:263 base 342:353
  M  259 b 4916
  M  260 b 120
  M  261 lwz r0, 0(0)
  M  262 cmpwi r0, 1
  B  342 b 4940
  B  343 li r4, 0
  B  344 li r5, 0x58
  B  345 bl 0
  B  346 lha r16, 0x28(r1)
  B  347 li r18, 0
  B  348 b 340
  B  349 lwz r4, 0(0)
  B  350 addi r3, r1, 0xb8
  B  351 bl 0
  B  352 cmpwi r3, -1
--- replace mine 265:266 base 355:356
  M  265 stb r0, 0x116(r31)
  B  355 stb r0, 0x116(r15)
--- replace mine 279:292 base 369:379
  M  279 b 4836
  M  280 cmpwi r17, 0x64
  M  281 clrlwi r3, r17, 0x10
  M  282 ble 8
  M  283 li r3, 0x64
  M  284 bl 0
  M  285 cmpwi r17, 0x64
  M  286 clrlwi r0, r17, 0x10
  M  287 ble 8
  M  288 li r0, 0x64
  M  289 subf r17, r0, r17
  M  290 cmpwi r17, 0
  M  291 bne -120
  B  369 b 4832
  B  370 cmpwi r3, 0
  B  371 bne 24
  B  372 bne 256
  B  373 lwz r3, 0(0)
  B  374 lwz r0, 0(r3)
  B  375 cmplwi r0, 1
  B  376 beq 240
  B  377 lhz r17, 0x2a(r1)
  B  378 b 132
--- replace mine 294:298 base 381:382
  M  294 beq 16
  M  295 addi r0, r16, 1
  M  296 extsh r16, r0
  M  297 b -820
  B  381 bne 68
--- replace mine 299:300 base 383:384
  M  299 stb r0, 0x116(r31)
  B  383 stb r0, 0x116(r15)
--- replace mine 313:319 base 397:403
  M  313 b 4700
  M  314 extsh r0, r15
  M  315 cmpw r0, r23
  M  316 bge 344
  M  317 lwz r4, 0(0)
  M  318 addi r3, r1, 0x70
  B  397 b 4720
  B  398 cmplwi r17, 0x64
  B  399 ble 12
  B  400 li r3, 0x64
  B  401 b 8
  B  402 mr r3, r17
--- replace mine 320:321 base 404:415
  M  320 cmpwi r3, -1
  B  404 cmplwi r17, 0x64
  B  405 ble 12
  B  406 li r0, 0x64
  B  407 b 8
  B  408 mr r0, r17
  B  409 subf r0, r0, r17
  B  410 clrlwi r17, r0, 0x10
  B  411 cmpwi r17, 0
  B  412 bne -132
  B  413 lwz r0, 0(0)
  B  414 cmpwi r0, 1
--- replace mine 323:324 base 417:418
  M  323 stb r0, 0x116(r31)
  B  417 stb r0, 0x116(r15)
--- replace mine 337:348 base 431:439
  M  337 b 4604
  M  338 cmpwi r3, 0
  M  339 mr r16, r22
  M  340 bne 156
  M  341 lwz r3, 0(0)
  M  342 lwz r0, 0(r3)
  M  343 cmpwi r0, 1
  M  344 beq 232
  M  345 b 136
  M  346 lwz r0, 0(0)
  M  347 cmpwi r0, 1
  B  431 b 4584
  B  432 addi r18, r18, 1
  B  433 extsh r0, r18
  B  434 cmpw r0, r16
  B  435 blt -344
  B  436 lha r0, 0x28(r1)
  B  437 extsh r3, r18
  B  438 cmpw r3, r0
--- replace mine 350:351 base 441:442
  M  350 stb r0, 0x116(r31)
  B  441 stb r0, 0x116(r15)
--- replace mine 364:386 base 455:456
  M  364 b 4496
  M  365 clrlwi r0, r16, 0x10
  M  366 mr r3, r16
  M  367 cmplwi r0, 0x64
  M  368 ble 8
  M  369 li r3, 0x64
  M  370 clrlwi r3, r3, 0x10
  M  371 bl 0
  M  372 clrlwi r0, r16, 0x10
  M  373 mr r3, r16
  M  374 cmplwi r0, 0x64
  M  375 ble 8
  M  376 li r3, 0x64
  M  377 subf r0, r3, r16
  M  378 clrlwi r16, r0, 0x10
  M  379 clrlwi. r0, r16, 0x10
  M  380 bne -136
  M  381 lwz r0, 0(0)
  M  382 cmpwi r0, 1
  M  383 bne 68
  M  384 li r0, 0xf
  M  385 stb r0, 0x116(r31)
  B  455 b 4488
--- replace mine 398:404 base 468:493
  M  398 li r3, -1
  M  399 b 4356
  M  400 addi r15, r15, 1
  M  401 b -348
  M  402 cmpw r15, r23
  M  403 bne 68
  B  468 addi r17, r1, 0xa0
  B  469 li r18, 0
  B  470 li r16, 0
  B  471 addi r3, r1, 0xa0
  B  472 addi r4, r15, 0x110
  B  473 add r3, r3, r16
  B  474 li r5, 6
  B  475 bl 0
  B  476 bl 0
  B  477 add r21, r17, r16
  B  478 sth r3, 6(r21)
  B  479 clrlwi r3, r3, 0x10
  B  480 bl 0
  B  481 addi r18, r18, 1
  B  482 sth r3, 6(r21)
  B  483 cmpwi r18, 3
  B  484 addi r16, r16, 8
  B  485 blt -56
  B  486 li r3, 2
  B  487 li r4, 2
  B  488 li r5, 0
  B  489 bl 0
  B  490 cmpwi r3, 0
  B  491 stw r3, 0(0)
  B  492 bge 68
--- replace mine 405:406 base 494:495
  M  405 stb r0, 0x116(r31)
  B  494 stb r0, 0x116(r15)
--- replace mine 420:454 base 509:513
  M  420 lwz r3, 0(0)
  M  421 cmpwi r3, 0
  M  422 beq 16
  M  423 bl 0
  M  424 li r0, 0
  M  425 stw r0, 0(0)
  M  426 lwz r3, 0(0)
  M  427 cmpwi r3, 0
  M  428 beq 16
  M  429 bl 0
  M  430 li r0, 0
  M  431 stw r0, 0(0)
  M  432 addi r15, r1, 0x58
  M  433 li r17, 0
  M  434 mr r16, r15
  M  435 mr r3, r15
  M  436 addi r4, r31, 0x110
  M  437 li r5, 6
  M  438 bl 0
  M  439 bl 0
  M  440 sth r3, 6(r16)
  M  441 clrlwi r3, r3, 0x10
  M  442 bl 0
  M  443 addi r17, r17, 1
  M  444 sth r3, 6(r16)
  M  445 cmpwi r17, 3
  M  446 addi r16, r16, 8
  M  447 addi r15, r15, 8
  M  448 blt -52
  M  449 li r3, 2
  M  450 li r4, 2
  M  451 li r5, 0
  M  452 bl 0
  M  453 cmpwi r3, 0
  B  509 cmpwi r14, 0
  B  510 bge 76
  B  511 li r3, 0xb
  B  512 li r0, 0xf
--- replace mine 455:458 base 514:515
  M  455 bge 68
  M  456 li r0, 0xf
  M  457 stb r0, 0x116(r31)
  B  514 stb r0, 0x116(r15)
--- replace mine 471:473 base 528:530
  M  471 b 4068
  M  472 addi r3, r1, 0x18
  B  528 b 4196
  B  529 addi r3, r1, 0x40
--- replace mine 476:478 base 533:535
  M  476 li r24, 2
  M  477 stb r24, 0x19(r1)
  B  533 li r22, 2
  B  534 stb r22, 0x41(r1)
--- replace mine 479:480 base 536:537
  M  479 stw r3, 0x1c(r1)
  B  536 stw r3, 0x44(r1)
--- replace mine 482:484 base 539:541
  M  482 li r25, 8
  M  483 sth r3, 0x1a(r1)
  B  539 li r23, 8
  B  540 sth r3, 0x42(r1)
--- replace mine 485:487 base 542:544
  M  485 addi r4, r1, 0x18
  M  486 stb r25, 0x18(r1)
  B  542 addi r4, r1, 0x40
  B  543 stb r23, 0x40(r1)
--- replace mine 488:546 base 545:547
  M  488 cmpwi r3, -1
  M  489 ble 1948
  M  490 lis r3, 0x1062
  M  491 lis r5, -0x3f58
  M  492 addi r0, r3, 0x4dd3
  M  493 lis r4, 0
  M  494 mulhw r0, r0, r14
  M  495 addi r6, r5, 0xb65
  M  496 stw r6, 0xac(r1)
  M  497 addi r5, r5, 0xb01
  M  498 lis r3, 0x431c
  M  499 lha r19, 8(r1)
  M  500 srawi r6, r0, 6
  M  501 stw r5, 0xb0(r1)
  M  502 srawi r0, r0, 6
  M  503 addi r28, r4, 0
  M  504 srwi r5, r0, 0x1f
  M  505 srwi r7, r6, 0x1f
  M  506 add r0, r0, r5
  M  507 addi r30, r3, -0x217d
  M  508 mulli r0, r0, 0x3e8
  M  509 add r20, r6, r7
  M  510 li r18, 0
  M  511 li r27, 0
  M  512 subf r0, r0, r14
  M  513 li r14, 3
  M  514 mulli r21, r0, 0x3e8
  M  515 li r26, -1
  M  516 li r29, 1
  M  517 lwz r16, 0(0)
  M  518 addi r3, r1, 0x40
  M  519 li r4, 0
  M  520 li r5, 0x14
  M  521 bl 0
  M  522 lwz r0, 0xb0(r1)
  M  523 stw r0, 0x40(r1)
  M  524 cmpwi r18, 1
  M  525 bne 944
  M  526 lbz r0, 0x18(r28)
  M  527 cmplwi r0, 1
  M  528 beq 932
  M  529 lwz r3, 0(0)
  M  530 cmpwi r3, -1
  M  531 beq 8
  M  532 bl 0
  M  533 lwz r0, 0(0)
  M  534 stw r26, 0(0)
  M  535 cmpwi r0, 1
  M  536 bne 28
  M  537 stw r27, 0(0)
  M  538 bl 0
  M  539 cmpwi r3, -1
  M  540 bgt 12
  M  541 li r0, -1
  M  542 b 8
  M  543 li r0, 0
  M  544 cmpwi r0, 0
  M  545 beq 68
  B  545 cmpwi r3, 0
  B  546 bge 68
--- replace mine 547:548 base 548:549
  M  547 stb r0, 0x116(r31)
  B  548 stb r0, 0x116(r15)
--- replace mine 561:573 base 562:639
  M  561 b 3708
  M  562 lwz r4, 0x14(r28)
  M  563 lwz r5, 0x10(r28)
  M  564 nor r6, r4, r4
  M  565 and r3, r5, r6
  M  566 and r7, r5, r4
  M  567 addi r0, r3, 1
  M  568 or r3, r7, r0
  M  569 or r0, r7, r6
  M  570 cmplw r0, r3
  M  571 bgt 8
  M  572 ori r3, r7, 1
  B  562 b 4060
  B  563 lis r3, 0x1062
  B  564 lis r4, 0
  B  565 addi r0, r3, 0x4dd3
  B  566 lis r5, -0x3f58
  B  567 mulhw r29, r0, r20
  B  568 lis r3, 0x431c
  B  569 addi r0, r5, 0xb65
  B  570 lha r31, 0x24(r1)
  B  571 stw r0, 0xf4(r1)
  B  572 addi r27, r4, 0
  B  573 addi r0, r5, 0xb01
  B  574 addi r30, r3, -0x217d
  B  575 stw r0, 0xf8(r1)
  B  576 li r14, 0x11
  B  577 li r26, 0
  B  578 li r21, 8
  B  579 li r28, -1
  B  580 li r24, 1
  B  581 lwz r17, 0(0)
  B  582 addi r3, r1, 0x88
  B  583 li r4, 0
  B  584 li r5, 0x14
  B  585 bl 0
  B  586 lwz r0, 0xf4(r1)
  B  587 stw r0, 0x98(r1)
  B  588 lwz r0, 0xf8(r1)
  B  589 stw r0, 0x88(r1)
  B  590 cmpwi r19, 1
  B  591 bne 968
  B  592 lbz r0, 0x18(r27)
  B  593 cmpwi r0, 1
  B  594 beq 956
  B  595 lwz r3, 0(0)
  B  596 cmpwi r3, -1
  B  597 beq 8
  B  598 bl 0
  B  599 lwz r0, 0(0)
  B  600 stw r28, 0(0)
  B  601 cmpwi r0, 1
  B  602 bne 28
  B  603 stw r26, 0(0)
  B  604 bl 0
  B  605 cmpwi r3, 0
  B  606 bge 12
  B  607 li r0, -1
  B  608 b 8
  B  609 li r0, 0
  B  610 cmpwi r0, 0
  B  611 beq 68
  B  612 li r0, 0xf
  B  613 stb r0, 0x116(r15)
  B  614 lwz r3, 0(0)
  B  615 cmpwi r3, 0
  B  616 beq 16
  B  617 bl 0
  B  618 li r0, 0
  B  619 stw r0, 0(0)
  B  620 lwz r3, 0(0)
  B  621 cmpwi r3, 0
  B  622 beq 16
  B  623 bl 0
  B  624 li r0, 0
  B  625 stw r0, 0(0)
  B  626 li r3, -1
  B  627 b 3800
  B  628 lwz r3, 0x14(r27)
  B  629 lwz r0, 0x10(r27)
  B  630 andc r4, r0, r3
  B  631 and r5, r0, r3
  B  632 addi r0, r4, 1
  B  633 orc r4, r5, r3
  B  634 or r3, r5, r0
  B  635 cmplw r3, r4
  B  636 blt 8
  B  637 ori r3, r5, 1
  B  638 lwz r4, 0x14(r27)
--- insert mine 574:574 base 640:641
  B  640 lwz r5, 0x10(r27)
--- replace mine 581:582 base 648:671
  M  581 stb r0, 0x116(r31)
  B  648 stb r0, 0x116(r15)
  B  649 lwz r3, 0(0)
  B  650 cmpwi r3, 0
  B  651 beq 16
  B  652 bl 0
  B  653 li r0, 0
  B  654 stw r0, 0(0)
  B  655 lwz r3, 0(0)
  B  656 cmpwi r3, 0
  B  657 beq 16
  B  658 bl 0
  B  659 li r0, 0
  B  660 stw r0, 0(0)
  B  661 li r3, -1
  B  662 b 3660
  B  663 stb r24, 0x18(r27)
  B  664 li r3, 0x58
  B  665 bl 0
  B  666 cmpwi r3, 0
  B  667 stw r3, 0(0)
  B  668 bne 68
  B  669 li r0, 0xf
  B  670 stb r0, 0x116(r15)
--- replace mine 596:598 base 685:687
  M  596 stb r29, 0x18(r28)
  M  597 li r3, 0x58
  B  685 li r4, 0
  B  686 li r5, 0x58
--- replace mine 599:601 base 688:695
  M  599 cmpwi r3, 0
  M  600 stw r3, 0(0)
  B  688 lha r25, 0x28(r1)
  B  689 li r18, 0
  B  690 b 340
  B  691 lwz r4, 0(0)
  B  692 addi r3, r1, 0xb8
  B  693 bl 0
  B  694 cmpwi r3, -1
--- replace mine 603:604 base 697:698
  M  603 stb r0, 0x116(r31)
  B  697 stb r0, 0x116(r15)
--- replace mine 617:627 base 711:723
  M  617 b 3484
  M  618 li r4, 0
  M  619 li r5, 0x58
  M  620 bl 0
  M  621 li r15, 0
  M  622 b 328
  M  623 lwz r4, 0(0)
  M  624 addi r3, r1, 0x70
  M  625 bl 0
  M  626 cmpwi r3, -1
  B  711 b 3464
  B  712 cmpwi r3, 0
  B  713 bne 24
  B  714 bne 256
  B  715 lwz r3, 0(0)
  B  716 lwz r0, 0(r3)
  B  717 cmplwi r0, 1
  B  718 beq 240
  B  719 lhz r16, 0x2a(r1)
  B  720 b 132
  B  721 lwz r0, 0(0)
  B  722 cmpwi r0, 1
--- replace mine 629:630 base 725:726
  M  629 stb r0, 0x116(r31)
  B  725 stb r0, 0x116(r15)
--- replace mine 643:652 base 739:755
  M  643 b 3380
  M  644 cmpwi r3, 0
  M  645 mr r17, r22
  M  646 bne 140
  M  647 lwz r3, 0(0)
  M  648 lwz r0, 0(r3)
  M  649 cmpwi r0, 1
  M  650 beq 224
  M  651 b 120
  B  739 b 3352
  B  740 cmplwi r16, 0x64
  B  741 ble 12
  B  742 li r3, 0x64
  B  743 b 8
  B  744 mr r3, r16
  B  745 bl 0
  B  746 cmplwi r16, 0x64
  B  747 ble 12
  B  748 li r0, 0x64
  B  749 b 8
  B  750 mr r0, r16
  B  751 subf r0, r0, r16
  B  752 clrlwi r16, r0, 0x10
  B  753 cmpwi r16, 0
  B  754 bne -132
--- replace mine 656:657 base 759:760
  M  656 stb r0, 0x116(r31)
  B  759 stb r0, 0x116(r15)
--- replace mine 670:675 base 773:781
  M  670 b 3272
  M  671 cmpwi r17, 0x64
  M  672 clrlwi r3, r17, 0x10
  M  673 ble 8
  M  674 li r3, 0x64
  B  773 b 3216
  B  774 addi r18, r18, 1
  B  775 extsh r0, r18
  B  776 cmpw r0, r25
  B  777 blt -344
  B  778 li r3, 2
  B  779 li r4, 2
  B  780 li r5, 0
--- replace mine 676:686 base 782:785
  M  676 cmpwi r17, 0x64
  M  677 clrlwi r0, r17, 0x10
  M  678 ble 8
  M  679 li r0, 0x64
  M  680 subf r17, r0, r17
  M  681 cmpwi r17, 0
  M  682 bne -120
  M  683 lwz r0, 0(0)
  M  684 cmpwi r0, 1
  M  685 bne 68
  B  782 cmpwi r3, 0
  B  783 stw r3, 0(0)
  B  784 bge 68
--- replace mine 687:688 base 786:787
  M  687 stb r0, 0x116(r31)
  B  786 stb r0, 0x116(r15)
--- replace mine 701:709 base 800:814
  M  701 b 3148
  M  702 addi r0, r15, 1
  M  703 extsh r15, r0
  M  704 cmpw r15, r23
  M  705 blt -328
  M  706 li r3, 2
  M  707 li r4, 2
  M  708 li r5, 0
  B  800 b 3108
  B  801 addi r3, r1, 0x40
  B  802 li r4, 0
  B  803 li r5, 8
  B  804 bl 0
  B  805 stb r22, 0x41(r1)
  B  806 bl 0
  B  807 stw r3, 0x44(r1)
  B  808 li r3, 0x5790
  B  809 bl 0
  B  810 sth r3, 0x42(r1)
  B  811 addi r4, r1, 0x40
  B  812 lwz r3, 0(0)
  B  813 stb r23, 0x40(r1)
--- delete mine 711:712 base 816:816
  M  711 stw r3, 0(0)
--- replace mine 714:715 base 818:819
  M  714 stb r0, 0x116(r31)
  B  818 stb r0, 0x116(r15)
--- replace mine 728:730 base 832:912
  M  728 b 3040
  M  729 addi r3, r1, 0x18
  B  832 b 2980
  B  833 cmpwi r19, 1
  B  834 lwz r16, 0(0)
  B  835 beq 76
  B  836 bge 16
  B  837 cmpwi r19, 0
  B  838 bge 20
  B  839 b 384
  B  840 cmpwi r19, 3
  B  841 bge 376
  B  842 b 96
  B  843 lwz r0, 0(0)
  B  844 cmpwi r0, 2
  B  845 beq 16
  B  846 stw r22, 0(0)
  B  847 li r3, 2
  B  848 bl 0
  B  849 mr r5, r16
  B  850 addi r3, r1, 0x88
  B  851 addi r4, r1, 0xa0
  B  852 bl 0
  B  853 b 332
  B  854 lwz r0, 0(0)
  B  855 cmpwi r0, 3
  B  856 beq 20
  B  857 li r0, 3
  B  858 li r3, 3
  B  859 stw r0, 0(0)
  B  860 bl 0
  B  861 mr r5, r16
  B  862 addi r3, r1, 0x88
  B  863 addi r4, r1, 0xa0
  B  864 bl 0
  B  865 b 284
  B  866 lwz r0, 0(0)
  B  867 cmpwi r0, 5
  B  868 beq 20
  B  869 li r0, 5
  B  870 li r3, 5
  B  871 stw r0, 0(0)
  B  872 bl 0
  B  873 lwz r18, 0(0)
  B  874 li r4, 0
  B  875 li r5, 0x5dc
  B  876 mr r3, r18
  B  877 bl 0
  B  878 addi r3, r1, 0x38
  B  879 addi r4, r1, 0xb0
  B  880 li r5, 8
  B  881 bl 0
  B  882 li r3, 0
  B  883 bl 0
  B  884 mr r6, r3
  B  885 addi r3, r1, 0x38
  B  886 li r4, 8
  B  887 li r5, 0
  B  888 bl 0
  B  889 li r3, 1
  B  890 bl 0
  B  891 sth r3, 0(r18)
  B  892 li r3, 0x3000
  B  893 sth r26, 2(r18)
  B  894 sth r26, 4(r18)
  B  895 bl 0
  B  896 sth r3, 6(r18)
  B  897 li r3, 0
  B  898 sth r26, 8(r18)
  B  899 bl 0
  B  900 sth r3, 0xa(r18)
  B  901 li r3, 0
  B  902 bl 0
  B  903 sth r3, 0xc(r18)
  B  904 li r0, 0
  B  905 addi r3, r18, 0x10
  B  906 addi r4, r1, 0x38
  B  907 stb r0, 0xe(r18)
  B  908 li r5, 8
  B  909 stb r14, 0xf(r18)
  B  910 bl 0
  B  911 addi r3, r1, 0x30
--- replace mine 733:736 base 915:916
  M  733 stb r24, 0x19(r1)
  M  734 bl 0
  M  735 stw r3, 0x1c(r1)
  B  915 stb r22, 0x31(r1)
--- replace mine 738:742 base 918:920
  M  738 sth r3, 0x1a(r1)
  M  739 addi r4, r1, 0x18
  M  740 lwz r3, 0(0)
  M  741 stb r25, 0x18(r1)
  B  918 sth r3, 0x32(r1)
  B  919 lwz r3, 0x10(r27)
--- replace mine 743:745 base 921:939
  M  743 cmpwi r3, 0
  M  744 bge 68
  B  921 lbz r0, 0x18(r27)
  B  922 stw r3, 0x34(r1)
  B  923 extsb. r0, r0
  B  924 bne 8
  B  925 stw r28, 0x34(r1)
  B  926 stb r21, 0x30(r1)
  B  927 mr r3, r16
  B  928 mr r4, r18
  B  929 addi r7, r1, 0x30
  B  930 li r5, 0x18
  B  931 li r6, 0
  B  932 bl 0
  B  933 li r3, 0
  B  934 b 8
  B  935 li r3, -1
  B  936 cmpwi r3, -1
  B  937 bne 76
  B  938 addi r3, r19, 0x1000
--- replace mine 746:747 base 940:942
  M  746 stb r0, 0x116(r31)
  B  940 stw r3, 0(0)
  B  941 stb r0, 0x116(r15)
--- replace mine 760:764 base 955:961
  M  760 b 2912
  M  761 cmpwi r18, 1
  M  762 lwz r17, 0(0)
  M  763 bne 48
  B  955 b 2488
  B  956 mr r3, r17
  B  957 li r4, 0
  B  958 li r5, 0x5f8
  B  959 bl 0
  B  960 srawi r5, r29, 6
--- replace mine 765:769 base 962:992
  M  765 cmpwi r0, 3
  M  766 beq 16
  M  767 stw r14, 0(0)
  M  768 li r3, 3
  B  962 srawi r3, r29, 6
  B  963 stw r24, 0x74(r1)
  B  964 srwi r4, r3, 0x1f
  B  965 srwi r7, r5, 0x1f
  B  966 add r3, r3, r4
  B  967 stw r0, 0x70(r1)
  B  968 add r8, r5, r7
  B  969 lis r5, -0x8000
  B  970 mulli r6, r3, 0x3e8
  B  971 stw r26, 0x78(r1)
  B  972 addi r3, r1, 0x70
  B  973 lwz r5, 0xf8(r5)
  B  974 li r4, 1
  B  975 subf r7, r6, r20
  B  976 srwi r6, r5, 2
  B  977 stw r0, 0x7c(r1)
  B  978 mulhwu r5, r30, r6
  B  979 stw r26, 0x84(r1)
  B  980 stw r24, 0x80(r1)
  B  981 mulli r7, r7, 0x3e8
  B  982 stw r8, 0x60(r1)
  B  983 srwi r0, r5, 0xf
  B  984 mullw r5, r8, r6
  B  985 stw r7, 0x64(r1)
  B  986 mullw r0, r7, r0
  B  987 addc r6, r26, r5
  B  988 adde r5, r26, r26
  B  989 srwi r0, r0, 3
  B  990 addc r6, r6, r0
  B  991 adde r5, r5, r26
--- replace mine 770:780 base 993:1016
  M  770 mr r5, r17
  M  771 addi r3, r1, 0x40
  M  772 addi r4, r1, 0x58
  M  773 bl 0
  M  774 b 348
  M  775 bge 64
  M  776 cmpwi r18, 0
  M  777 bge 12
  M  778 li r3, -1
  M  779 b 328
  B  993 cmpwi r3, 0
  B  994 bgt 300
  B  995 lwz r3, 0x20(r1)
  B  996 addi r0, r3, 1
  B  997 cmpw r0, r31
  B  998 stw r0, 0x20(r1)
  B  999 ble 60
  B 1000 cmpwi r19, 0
  B 1001 bne 16
  B 1002 li r0, 0xf
  B 1003 stw r0, 0(0)
  B 1004 b 32
  B 1005 cmpwi r19, 1
  B 1006 bne 16
  B 1007 li r0, 0x10
  B 1008 stw r0, 0(0)
  B 1009 b 12
  B 1010 li r0, 0x11
  B 1011 stw r0, 0(0)
  B 1012 li r14, -1
  B 1013 b 1864
  B 1014 lhz r16, 0x26(r1)
  B 1015 b 132
--- replace mine 781:864 base 1017:1019
  M  781 cmpwi r0, 2
  M  782 beq 16
  M  783 stw r24, 0(0)
  M  784 li r3, 2
  M  785 bl 0
  M  786 mr r5, r17
  M  787 addi r3, r1, 0x40
  M  788 addi r4, r1, 0x58
  M  789 bl 0
  M  790 b 284
  M  791 cmpwi r18, 2
  M  792 bgt -56
  M  793 lwz r0, 0(0)
  M  794 cmpwi r0, 5
  M  795 beq 20
  M  796 li r0, 5
  M  797 li r3, 5
  M  798 stw r0, 0(0)
  M  799 bl 0
  M  800 lwz r15, 0(0)
  M  801 li r4, 0
  M  802 li r5, 0x5dc
  M  803 mr r3, r15
  M  804 bl 0
  M  805 addi r3, r1, 0x20
  M  806 addi r4, r1, 0x68
  M  807 li r5, 8
  M  808 bl 0
  M  809 li r3, 0
  M  810 bl 0
  M  811 mr r6, r3
  M  812 addi r3, r1, 0x20
  M  813 li r4, 8
  M  814 li r5, 0
  M  815 bl 0
  M  816 li r3, 1
  M  817 bl 0
  M  818 sth r3, 0(r15)
  M  819 li r3, 0x3000
  M  820 sth r27, 2(r15)
  M  821 sth r27, 4(r15)
  M  822 bl 0
  M  823 sth r3, 6(r15)
  M  824 li r3, 0
  M  825 sth r27, 8(r15)
  M  826 bl 0
  M  827 sth r3, 0xa(r15)
  M  828 li r3, 0
  M  829 bl 0
  M  830 sth r3, 0xc(r15)
  M  831 li r0, 0x11
  M  832 addi r3, r15, 0x10
  M  833 addi r4, r1, 0x20
  M  834 stb r27, 0xe(r15)
  M  835 li r5, 8
  M  836 stb r0, 0xf(r15)
  M  837 bl 0
  M  838 addi r3, r1, 0x28
  M  839 li r4, 0
  M  840 li r5, 8
  M  841 bl 0
  M  842 stb r24, 0x29(r1)
  M  843 li r3, 0x5790
  M  844 bl 0
  M  845 sth r3, 0x2a(r1)
  M  846 lwz r3, 0x10(r28)
  M  847 bl 0
  M  848 lbz r0, 0x18(r28)
  M  849 stw r3, 0x2c(r1)
  M  850 cmpwi r0, 0
  M  851 bne 8
  M  852 stw r26, 0x2c(r1)
  M  853 stb r25, 0x28(r1)
  M  854 mr r3, r17
  M  855 mr r4, r15
  M  856 addi r7, r1, 0x28
  M  857 li r5, 0x18
  M  858 li r6, 0
  M  859 bl 0
  M  860 li r3, 0
  M  861 cmpwi r3, -1
  M  862 bne 76
  M  863 addi r3, r18, 0x1000
  B 1017 cmpwi r0, 1
  B 1018 bne 68
--- replace mine 865:867 base 1020:1021
  M  865 stw r3, 0(0)
  M  866 stb r0, 0x116(r31)
  B 1020 stb r0, 0x116(r15)
--- replace mine 880:881 base 1034:1039
  M  880 b 2432
  B 1034 b 2172
  B 1035 cmplwi r16, 0x64
  B 1036 ble 12
  B 1037 li r3, 0x64
  B 1038 b 8
--- delete mine 882:884 base 1040:1040
  M  882 li r4, 0
  M  883 li r5, 0x5f8
--- replace mine 885:926 base 1041:1050
  M  885 lwz r0, 0(0)
  M  886 lis r5, -0x8000
  M  887 stw r29, 0x34(r1)
  M  888 addi r3, r1, 0x30
  M  889 li r4, 1
  M  890 stw r0, 0x30(r1)
  M  891 stw r27, 0x38(r1)
  M  892 stw r0, 0x3c(r1)
  M  893 lwz r0, 0xf8(r5)
  M  894 srwi r5, r0, 2
  M  895 mulhwu r0, r30, r5
  M  896 mullw r7, r20, r5
  M  897 srwi r0, r0, 0xf
  M  898 mullw r0, r21, r0
  M  899 srwi r6, r0, 3
  M  900 addc r0, r7, r6
  M  901 adde r5, r27, r27
  M  902 add r6, r7, r6
  M  903 bl 0
  M  904 cmpwi r3, 0
  M  905 bgt 348
  M  906 lwz r3, 0xc(r1)
  M  907 lwz r15, 8(r1)
  M  908 addi r0, r3, 1
  M  909 cmpw r19, r0
  M  910 stw r0, 0xc(r1)
  M  911 bge 176
  M  912 cmpwi r18, 0
  M  913 bne 16
  M  914 li r0, 0xf
  M  915 stw r0, 0(0)
  M  916 b 28
  M  917 addi r3, r18, -1
  M  918 subfic r0, r18, 1
  M  919 nor r0, r3, r0
  M  920 srawi r3, r0, 0x1f
  M  921 addi r0, r3, 0x11
  M  922 stw r0, 0(0)
  M  923 li r14, -1
  M  924 b 1804
  M  925 b 120
  B 1041 cmplwi r16, 0x64
  B 1042 ble 12
  B 1043 li r0, 0x64
  B 1044 b 8
  B 1045 mr r0, r16
  B 1046 subf r0, r0, r16
  B 1047 clrlwi r16, r0, 0x10
  B 1048 cmpwi r16, 0
  B 1049 bne -132
--- replace mine 928:929 base 1052:1053
  M  928 bne 68
  B 1052 bne -1848
--- replace mine 930:931 base 1054:1055
  M  930 stb r0, 0x116(r31)
  B 1054 stb r0, 0x116(r15)
--- replace mine 944:949 base 1068:1076
  M  944 b 2176
  M  945 cmplwi r15, 0x64
  M  946 mr r3, r15
  M  947 ble 8
  M  948 li r3, 0x64
  B 1068 b 2036
  B 1069 li r0, 8
  B 1070 lwz r3, 0(0)
  B 1071 stb r0, 0x68(r1)
  B 1072 addi r4, r17, 0xc
  B 1073 addi r7, r1, 0x68
  B 1074 li r5, 0x5dc
  B 1075 li r6, 0
--- delete mine 950:957 base 1077:1077
  M  950 cmplwi r15, 0x64
  M  951 mr r0, r15
  M  952 ble 8
  M  953 li r0, 0x64
  M  954 subf r15, r0, r15
  M  955 clrlwi. r15, r15, 0x10
  M  956 bne -120
--- insert mine 958:958 base 1078:1108
  B 1078 clrlwi r3, r3, 0x10
  B 1079 stw r0, 0(r17)
  B 1080 bl 0
  B 1081 clrlwi r0, r3, 0x10
  B 1082 mr r3, r19
  B 1083 stw r0, 4(r17)
  B 1084 mr r4, r17
  B 1085 addi r5, r1, 0x20
  B 1086 addi r6, r1, 0xa0
  B 1087 lwz r7, 0(0)
  B 1088 bl 0
  B 1089 cmpwi r3, 0x64
  B 1090 mr r16, r3
  B 1091 bne 12
  B 1092 li r14, 0
  B 1093 b 1544
  B 1094 cmpwi r3, -1
  B 1095 bne 12
  B 1096 li r14, -1
  B 1097 b 1528
  B 1098 cmpw r19, r3
  B 1099 beq 1224
  B 1100 cmpwi r3, 2
  B 1101 bne 1208
  B 1102 lwz r3, 0(0)
  B 1103 cmpwi r3, -1
  B 1104 beq 8
  B 1105 bl 0
  B 1106 lwz r0, 0(0)
  B 1107 stw r28, 0(0)
--- replace mine 959:960 base 1109:1119
  M  959 bne -1740
  B 1109 bne 28
  B 1110 stw r26, 0(0)
  B 1111 bl 0
  B 1112 cmpwi r3, 0
  B 1113 bge 12
  B 1114 li r0, -1
  B 1115 b 8
  B 1116 li r0, 0
  B 1117 cmpwi r0, 0
  B 1118 beq 68
--- replace mine 961:962 base 1120:1121
  M  961 stb r0, 0x116(r31)
  B 1120 stb r0, 0x116(r15)
--- replace mine 975:976 base 1134:1151
  M  975 b 2052
  B 1134 b 1772
  B 1135 lwz r0, 0(0)
  B 1136 cmpwi r0, 4
  B 1137 beq 20
  B 1138 li r0, 4
  B 1139 li r3, 4
  B 1140 stw r0, 0(0)
  B 1141 bl 0
  B 1142 lwz r3, 0(0)
  B 1143 cmpwi r3, 0
  B 1144 beq 12
  B 1145 bl 0
  B 1146 stw r26, 0(0)
  B 1147 li r3, 0
  B 1148 bl 0
  B 1149 cmpwi r3, -1
  B 1150 bne 68
--- replace mine 977:978 base 1152:1153
  M  977 stb r0, 0x116(r31)
  B 1152 stb r0, 0x116(r15)
--- replace mine 991:999 base 1166:1167
  M  991 b 1988
  M  992 stb r25, 0x10(r1)
  M  993 addi r4, r16, 0xc
  M  994 lwz r3, 0(0)
  M  995 addi r7, r1, 0x10
  M  996 li r5, 0x5dc
  M  997 li r6, 0
  M  998 bl 0
  B 1166 b 1644
--- delete mine 1000:1030 base 1168:1168
  M 1000 clrlwi r3, r3, 0x10
  M 1001 stw r0, 0(r16)
  M 1002 bl 0
  M 1003 clrlwi r0, r3, 0x10
  M 1004 mr r3, r18
  M 1005 stw r0, 4(r16)
  M 1006 mr r4, r16
  M 1007 addi r5, r1, 0xc
  M 1008 addi r6, r1, 0x58
  M 1009 bl 0
  M 1010 cmpwi r3, 0x64
  M 1011 mr r16, r3
  M 1012 bne 12
  M 1013 li r14, 0
  M 1014 b 1444
  M 1015 cmpwi r3, -1
  M 1016 bne 12
  M 1017 li r14, -1
  M 1018 b 1428
  M 1019 cmpw r18, r3
  M 1020 beq 1144
  M 1021 cmpwi r3, 2
  M 1022 mr r18, r16
  M 1023 bne -2024
  M 1024 lwz r3, 0(0)
  M 1025 cmpwi r3, -1
  M 1026 beq 8
  M 1027 bl 0
  M 1028 lwz r0, 0(0)
  M 1029 stw r26, 0(0)
--- replace mine 1031:1041 base 1169:1170
  M 1031 bne 28
  M 1032 stw r27, 0(0)
  M 1033 bl 0
  M 1034 cmpwi r3, 0
  M 1035 bge 12
  M 1036 li r0, -1
  M 1037 b 8
  M 1038 li r0, 0
  M 1039 cmpwi r0, 0
  M 1040 beq 68
  B 1169 bne 68
--- replace mine 1042:1043 base 1171:1172
  M 1042 stb r0, 0x116(r31)
  B 1171 stb r0, 0x116(r15)
--- replace mine 1056:1063 base 1185:1187
  M 1056 b 1728
  M 1057 lwz r0, 0(0)
  M 1058 cmpwi r0, 4
  M 1059 beq 20
  M 1060 li r0, 4
  M 1061 li r3, 4
  M 1062 stw r0, 0(0)
  B 1185 b 1568
  B 1186 lwz r3, 0(0)
--- replace mine 1064:1072 base 1188:1189
  M 1064 lwz r3, 0(0)
  M 1065 cmpwi r3, 0
  M 1066 beq 12
  M 1067 bl 0
  M 1068 stw r27, 0(0)
  M 1069 li r3, 0
  M 1070 bl 0
  M 1071 cmpwi r3, -1
  B 1188 cmpwi r3, 4
--- replace mine 1073:1075 base 1190:1192
  M 1073 li r0, 0xf
  M 1074 stb r0, 0x116(r31)
  B 1190 li r0, 2
  B 1191 stb r0, 0x116(r15)
--- replace mine 1088:1094 base 1205:1210
  M 1088 b 1600
  M 1089 lwz r0, 0(0)
  M 1090 cmpwi r0, 1
  M 1091 bne 68
  M 1092 li r0, 0xf
  M 1093 stb r0, 0x116(r31)
  B 1205 b 1488
  B 1206 cmpwi r3, 0
  B 1207 beq 68
  B 1208 li r0, 1
  B 1209 stb r0, 0x116(r15)
--- replace mine 1107:1109 base 1223:1225
  M 1107 b 1524
  M 1108 lwz r3, 0(0)
  B 1223 b 1416
  B 1224 li r3, 0x58
--- replace mine 1110:1111 base 1226:1228
  M 1110 cmpwi r3, 4
  B 1226 cmpwi r3, 0
  B 1227 stw r3, 0(0)
--- replace mine 1112:1114 base 1229:1231
  M 1112 li r0, 2
  M 1113 stb r0, 0x116(r31)
  B 1229 li r0, 0xf
  B 1230 stb r0, 0x116(r15)
--- replace mine 1127:1132 base 1244:1258
  M 1127 b 1444
  M 1128 cmpwi r3, 0
  M 1129 beq 68
  M 1130 li r0, 1
  M 1131 stb r0, 0x116(r31)
  B 1244 b 1332
  B 1245 li r4, 0
  B 1246 li r5, 0x58
  B 1247 bl 0
  B 1248 lha r19, 0x28(r1)
  B 1249 li r18, 0
  B 1250 b 340
  B 1251 lwz r4, 0(0)
  B 1252 addi r3, r1, 0xb8
  B 1253 bl 0
  B 1254 cmpwi r3, -1
  B 1255 bne 68
  B 1256 li r0, 0xf
  B 1257 stb r0, 0x116(r15)
--- replace mine 1145:1148 base 1271:1272
  M 1145 b 1372
  M 1146 li r3, 0x58
  M 1147 bl 0
  B 1271 b 1224
--- replace mine 1149:1150 base 1273:1283
  M 1149 stw r3, 0(0)
  B 1273 bne 24
  B 1274 bne 256
  B 1275 lwz r3, 0(0)
  B 1276 lwz r0, 0(r3)
  B 1277 cmplwi r0, 1
  B 1278 beq 240
  B 1279 lhz r17, 0x2a(r1)
  B 1280 b 132
  B 1281 lwz r0, 0(0)
  B 1282 cmpwi r0, 1
--- replace mine 1152:1153 base 1285:1286
  M 1152 stb r0, 0x116(r31)
  B 1285 stb r0, 0x116(r15)
--- replace mine 1166:1169 base 1299:1305
  M 1166 b 1288
  M 1167 li r4, 0
  M 1168 li r5, 0x58
  B 1299 b 1112
  B 1300 cmplwi r17, 0x64
  B 1301 ble 12
  B 1302 li r3, 0x64
  B 1303 b 8
  B 1304 mr r3, r17
--- replace mine 1170:1176 base 1306:1317
  M 1170 li r17, 0
  M 1171 b 328
  M 1172 lwz r4, 0(0)
  M 1173 addi r3, r1, 0x70
  M 1174 bl 0
  M 1175 cmpwi r3, -1
  B 1306 cmplwi r17, 0x64
  B 1307 ble 12
  B 1308 li r0, 0x64
  B 1309 b 8
  B 1310 mr r0, r17
  B 1311 subf r0, r0, r17
  B 1312 clrlwi r17, r0, 0x10
  B 1313 cmpwi r17, 0
  B 1314 bne -132
  B 1315 lwz r0, 0(0)
  B 1316 cmpwi r0, 1
--- replace mine 1178:1179 base 1319:1320
  M 1178 stb r0, 0x116(r31)
  B 1319 stb r0, 0x116(r15)
--- replace mine 1192:1193 base 1333:1339
  M 1192 b 1184
  B 1333 b 976
  B 1334 addi r18, r18, 1
  B 1335 extsh r0, r18
  B 1336 cmpw r0, r19
  B 1337 blt -344
  B 1338 lwz r3, 0(0)
--- replace mine 1194:1196 base 1340:1343
  M 1194 mr r15, r22
  M 1195 bne 140
  B 1340 beq 12
  B 1341 bl 0
  B 1342 stw r26, 0(0)
--- replace mine 1197:1204 base 1344:1355
  M 1197 lwz r0, 0(r3)
  M 1198 cmpwi r0, 1
  M 1199 beq 224
  M 1200 b 120
  M 1201 lwz r0, 0(0)
  M 1202 cmpwi r0, 1
  M 1203 bne 68
  B 1344 cmpwi r3, 0
  B 1345 beq 12
  B 1346 bl 0
  B 1347 stw r26, 0(0)
  B 1348 li r3, 2
  B 1349 li r4, 2
  B 1350 li r5, 0
  B 1351 bl 0
  B 1352 cmpwi r3, 0
  B 1353 stw r3, 0(0)
  B 1354 bge 68
--- replace mine 1205:1206 base 1356:1357
  M 1205 stb r0, 0x116(r31)
  B 1356 stb r0, 0x116(r15)
--- replace mine 1219:1224 base 1370:1374
  M 1219 b 1076
  M 1220 cmpwi r15, 0x64
  M 1221 clrlwi r3, r15, 0x10
  M 1222 ble 8
  M 1223 li r3, 0x64
  B 1370 b 828
  B 1371 addi r3, r1, 0x40
  B 1372 li r4, 0
  B 1373 li r5, 8
--- replace mine 1225:1235 base 1375:1387
  M 1225 cmpwi r15, 0x64
  M 1226 clrlwi r0, r15, 0x10
  M 1227 ble 8
  M 1228 li r0, 0x64
  M 1229 subf r15, r0, r15
  M 1230 cmpwi r15, 0
  M 1231 bne -120
  M 1232 lwz r0, 0(0)
  M 1233 cmpwi r0, 1
  M 1234 bne 68
  B 1375 stb r22, 0x41(r1)
  B 1376 bl 0
  B 1377 stw r3, 0x44(r1)
  B 1378 li r3, 0x5790
  B 1379 bl 0
  B 1380 sth r3, 0x42(r1)
  B 1381 addi r4, r1, 0x40
  B 1382 lwz r3, 0(0)
  B 1383 stb r23, 0x40(r1)
  B 1384 bl 0
  B 1385 cmpwi r3, 0
  B 1386 bge 68
--- replace mine 1236:1237 base 1388:1389
  M 1236 stb r0, 0x116(r31)
  B 1388 stb r0, 0x116(r15)
--- replace mine 1250:1256 base 1402:1410
  M 1250 b 952
  M 1251 addi r0, r17, 1
  M 1252 extsh r17, r0
  M 1253 cmpw r17, r23
  M 1254 blt -328
  M 1255 lwz r3, 0(0)
  B 1402 b 700
  B 1403 mr r19, r16
  B 1404 b -3292
  B 1405 lwz r4, 0x20(r1)
  B 1406 mr r19, r16
  B 1407 lha r0, 0x24(r1)
  B 1408 cmpw r4, r0
  B 1409 ble 60
--- replace mine 1257:1272 base 1411:1412
  M 1257 beq 12
  M 1258 bl 0
  M 1259 stw r27, 0(0)
  M 1260 lwz r3, 0(0)
  M 1261 cmpwi r3, 0
  M 1262 beq 12
  M 1263 bl 0
  M 1264 stw r27, 0(0)
  M 1265 li r3, 2
  M 1266 li r4, 2
  M 1267 li r5, 0
  M 1268 bl 0
  M 1269 cmpwi r3, 0
  M 1270 stw r3, 0(0)
  M 1271 bge 68
  B 1411 bne 16
--- replace mine 1273:1274 base 1413:1431
  M 1273 stb r0, 0x116(r31)
  B 1413 stw r0, 0(0)
  B 1414 b 32
  B 1415 cmpwi r3, 1
  B 1416 bne 16
  B 1417 li r0, 0x10
  B 1418 stw r0, 0(0)
  B 1419 b 12
  B 1420 li r0, 0x11
  B 1421 stw r0, 0(0)
  B 1422 li r14, -1
  B 1423 b 224
  B 1424 lhz r16, 0x26(r1)
  B 1425 b 132
  B 1426 lwz r0, 0(0)
  B 1427 cmpwi r0, 1
  B 1428 bne 68
  B 1429 li r0, 0xf
  B 1430 stb r0, 0x116(r15)
--- replace mine 1287:1291 base 1444:1450
  M 1287 b 804
  M 1288 addi r3, r1, 0x18
  M 1289 li r4, 0
  M 1290 li r5, 8
  B 1444 b 532
  B 1445 cmplwi r16, 0x64
  B 1446 ble 12
  B 1447 li r3, 0x64
  B 1448 b 8
  B 1449 mr r3, r16
--- replace mine 1292:1312 base 1451:1460
  M 1292 stb r24, 0x19(r1)
  M 1293 bl 0
  M 1294 stw r3, 0x1c(r1)
  M 1295 li r3, 0x5790
  M 1296 bl 0
  M 1297 sth r3, 0x1a(r1)
  M 1298 addi r4, r1, 0x18
  M 1299 lwz r3, 0(0)
  M 1300 stb r25, 0x18(r1)
  M 1301 bl 0
  M 1302 cmpwi r3, 0
  M 1303 mr r18, r16
  M 1304 blt 676
  M 1305 b -3152
  M 1306 lwz r4, 0xc(r1)
  M 1307 lhz r0, 8(r1)
  M 1308 lwz r15, 8(r1)
  M 1309 cmpw r4, r0
  M 1310 bgt 212
  M 1311 b 120
  B 1451 cmplwi r16, 0x64
  B 1452 ble 12
  B 1453 li r0, 0x64
  B 1454 b 8
  B 1455 mr r0, r16
  B 1456 subf r0, r0, r16
  B 1457 clrlwi r16, r0, 0x10
  B 1458 cmpwi r16, 0
  B 1459 bne -132
--- replace mine 1314:1315 base 1462:1463
  M 1314 bne 68
  B 1462 bne -3524
--- replace mine 1316:1317 base 1464:1465
  M 1316 stb r0, 0x116(r31)
  B 1464 stb r0, 0x116(r15)
--- replace mine 1330:1335 base 1478:1482
  M 1330 b 632
  M 1331 cmplwi r15, 0x64
  M 1332 mr r3, r15
  M 1333 ble 8
  M 1334 li r3, 0x64
  B 1478 b 396
  B 1479 lwz r3, 0(0)
  B 1480 cmpwi r3, -1
  B 1481 beq 8
--- delete mine 1336:1343 base 1483:1483
  M 1336 cmplwi r15, 0x64
  M 1337 mr r0, r15
  M 1338 ble 8
  M 1339 li r0, 0x64
  M 1340 subf r15, r0, r15
  M 1341 clrlwi. r15, r15, 0x10
  M 1342 bne -120
--- replace mine 1344:1345 base 1484:1486
  M 1344 mr r18, r16
  B 1484 li r3, -1
  B 1485 stw r3, 0(0)
--- replace mine 1346:1347 base 1487:1498
  M 1346 bne -3316
  B 1487 bne 32
  B 1488 li r0, 0
  B 1489 stw r0, 0(0)
  B 1490 bl 0
  B 1491 cmpwi r3, 0
  B 1492 bge 12
  B 1493 li r0, -1
  B 1494 b 8
  B 1495 li r0, 0
  B 1496 cmpwi r0, 0
  B 1497 beq 68
--- replace mine 1348:1349 base 1499:1500
  M 1348 stb r0, 0x116(r31)
  B 1499 stb r0, 0x116(r15)
--- replace mine 1362:1365 base 1513:1540
  M 1362 b 504
  M 1363 cmpwi r3, 0
  M 1364 bne 16
  B 1513 b 256
  B 1514 cmpwi r14, 0
  B 1515 beq 164
  B 1516 lwz r0, 0(0)
  B 1517 cmpwi r0, 0x11
  B 1518 beq 64
  B 1519 bge 20
  B 1520 cmpwi r0, 0xf
  B 1521 beq 36
  B 1522 bge 40
  B 1523 b 68
  B 1524 cmpwi r0, 0x15
  B 1525 beq 52
  B 1526 bge 56
  B 1527 cmpwi r0, 0x14
  B 1528 bge 32
  B 1529 b 44
  B 1530 li r0, 3
  B 1531 b 40
  B 1532 li r0, 4
  B 1533 b 32
  B 1534 li r0, 5
  B 1535 b 24
  B 1536 li r0, 7
  B 1537 b 16
  B 1538 li r0, 8
  B 1539 b 8
--- replace mine 1366:1396 base 1541:1542
  M 1366 stw r0, 0(0)
  M 1367 b 28
  M 1368 addi r4, r3, -1
  M 1369 subfic r0, r3, 1
  M 1370 nor r0, r4, r0
  M 1371 srawi r3, r0, 0x1f
  M 1372 addi r0, r3, 0x11
  M 1373 stw r0, 0(0)
  M 1374 li r14, -1
  M 1375 lwz r3, 0(0)
  M 1376 cmpwi r3, -1
  M 1377 beq 8
  M 1378 bl 0
  M 1379 lwz r0, 0(0)
  M 1380 li r3, -1
  M 1381 stw r3, 0(0)
  M 1382 cmpwi r0, 1
  M 1383 bne 32
  M 1384 li r0, 0
  M 1385 stw r0, 0(0)
  M 1386 bl 0
  M 1387 cmpwi r3, -1
  M 1388 bgt 12
  M 1389 li r0, -1
  M 1390 b 8
  M 1391 li r0, 0
  M 1392 cmpwi r0, 0
  M 1393 beq 68
  M 1394 li r0, 0xf
  M 1395 stb r0, 0x116(r31)
  B 1541 stb r0, 0x116(r15)
--- replace mine 1409:1413 base 1555:1557
  M 1409 b 316
  M 1410 cmpwi r14, 0
  M 1411 bne 92
  M 1412 mr r3, r31
  B 1555 b 88
  B 1556 mr r3, r15
--- replace mine 1415:1418 base 1559:1560
  M 1415 bne 12
  M 1416 li r3, 0
  M 1417 b 284
  B 1559 beq 68
--- replace mine 1419:1420 base 1561:1562
  M 1419 stb r0, 0x116(r31)
  B 1561 stb r0, 0x116(r15)
--- delete mine 1433:1456 base 1575:1575
  M 1433 b 220
  M 1434 lwz r0, 0(0)
  M 1435 cmplwi r0, 0x11
  M 1436 bne 12
  M 1437 li r0, 5
  M 1438 b 80
  M 1439 bge 36
  M 1440 cmplwi r0, 0xf
  M 1441 bne 12
  M 1442 li r0, 3
  M 1443 b 60
  M 1444 cmplwi r0, 0xe
  M 1445 ble 48
  M 1446 li r0, 4
  M 1447 b 44
  M 1448 cmplwi r0, 0x15
  M 1449 bne 12
  M 1450 li r0, 8
  M 1451 b 28
  M 1452 bge 20
  M 1453 cmplwi r0, 0x13
  M 1454 ble 12
  M 1455 li r0, 7
--- replace mine 1457:1462 base 1576:1579
  M 1457 li r0, 0xf
  M 1458 stb r0, 0x116(r31)
  M 1459 lwz r3, 0(0)
  M 1460 cmpwi r3, 0
  M 1461 beq 16
  B 1576 li r3, 0
  B 1577 lwz r10, 0(r1)
  B 1578 mr r11, r10
--- replace mine 1463:1491 base 1580:1581
  M 1463 li r0, 0
  M 1464 stw r0, 0(0)
  M 1465 lwz r3, 0(0)
  M 1466 cmpwi r3, 0
  M 1467 beq 16
  M 1468 bl 0
  M 1469 li r0, 0
  M 1470 stw r0, 0(0)
  M 1471 li r3, -1
  M 1472 b 64
  M 1473 li r0, 0xf
  M 1474 stb r0, 0x116(r31)
  M 1475 lwz r3, 0(0)
  M 1476 cmpwi r3, 0
  M 1477 beq 16
  M 1478 bl 0
  M 1479 li r0, 0
  M 1480 stw r0, 0(0)
  M 1481 lwz r3, 0(0)
  M 1482 cmpwi r3, 0
  M 1483 beq 16
  M 1484 bl 0
  M 1485 li r0, 0
  M 1486 stw r0, 0(0)
  M 1487 li r3, -1
  M 1488 addi r11, r1, 0x100
  M 1489 bl 0
  M 1490 lwz r0, 0x104(r1)
  B 1580 lwz r0, 4(r10)
--- replace mine 1492:1493 base 1582:1583
  M 1492 addi r1, r1, 0x100
  B 1582 mr r1, r10
```

AOSS_Init_old initial 73.34911%
- stack local layout: actual SDK array of two complete poll descriptors: 73.00505%; src 0x1760 base 0x18c0 insns 1496/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x110(r1);   B    0 clrlwi r11, r1, 0x1b
- stack local alignment: request records use original cache-line alignment: 69.66288%; src 0x1834 base 0x18c0 insns 1549/1584; --- insert mine 8:8 base 8:15;   B    8 lhz r4, 0(0);   B    9 li r0, 0
- stack local layout: complete poll descriptors and aligned request records: 69.44571%; src 0x183c base 0x18c0 insns 1551/1584; --- insert mine 8:8 base 8:15;   B    8 lhz r4, 0(0);   B    9 li r0, 0
Retained best candidate

AOSS_81401E80 initial 98.605446%
- temporary: mask byte receives the XOR of two explicit snapshots: 97.517006%; src 0x24c base 0x24c insns 147/147; diffs 54: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81];     53 M li r5, 0;        B li r3, 0
- temporary: separate output byte follows input and mask snapshots: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
- local order: mask snapshot before packet snapshot: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
Retained best candidate

AOSS_814013AC initial 98.77193%
- temporary: response formal reused for both search and selected option traversal: 95.08772%; src 0x1c8 base 0x1c8 insns 114/114; diffs 28: [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 34, 37, 38, 39, 40, 41, 56, 58, 61];      6 M mr r24, r5;        B mr r27, r3
- temporary: response formal reused only during outer search: 96.75439%; src 0x1c8 base 0x1c8 insns 114/114; diffs 30: [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 20, 25, 29, 30, 32, 33, 34, 42];      6 M mr r24, r5;        B mr r27, r3
- temporary: one formal cursor with actual four-bit security flag accumulator: 90.307014%; src 0x1d8 base 0x1c8 insns 118/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:9 base 8:8
Retained best candidate

## Attempt coverage

Every baseline instruction residual has at least three successful distinct source trials. Failed and unchanged candidates are excluded; all sections, including later targeted trials, are counted.

- AOSS_81400E0C: 3 compiling trials.
- AOSS_814013AC: 6 compiling trials.
- AOSS_81401E80: 6 compiling trials.
- AOSS_81400830: 3 compiling trials.
- AOSS_81401778: 3 compiling trials.
- AOSS_Init_old: 3 compiling trials.

## Remaining instruction residuals

| Function | objdiff % | Instructions (mine/original) | Evidence / remaining reason |
|---|---:|---|---|
| AOSS_Init_old | 73.34911 | 1494/1584 | initialization frame/alignment and remaining loop scheduling; 90 instructions short, including preserved initialized fallback for target r14 |
| AOSS_81400830 | 93.84112 | 326/321 | RC4 cursor publication, payload/frame bindings and store/reload scheduling; five extra instructions |
| AOSS_81400E0C | 100.0 | 190/190 | objdiff 100; gate/ctxdiff has cr1 address-normalization differences; raw bytes identical |
| AOSS_814013AC | 98.77193 | 114/114 | response/flags/remaining-length pointer lifetimes and argument move order |
| AOSS_81401778 | 79.16483 | 275/273 | hello record now has original stack offset 0x18; CRC/BSS-base and RC4 schedule bindings remain; two extra instructions |
| AOSS_81401E80 | 98.605446 | 147/147 | XOR loop base registers r4/r5 and XOR result r6/r0 plus cr1 normalization; traversal index now agrees |

## Data audit

No artificial data objects or symbol names added. String pools are identical. These C units contain no vtables.

- .bss: mine 3496, original 3496 bytes; prefix mismatches 0/3496; extra alignment tail bytes 0, all zero True.
- .data: mine 364, original 368 bytes; prefix mismatches 0/364; extra alignment tail bytes 4, all zero True.
- .sdata2: mine 8, original 8 bytes; prefix mismatches 0/8; extra alignment tail bytes 0, all zero True.
- .sdata: mine 24, original 24 bytes; prefix mismatches 0/24; extra alignment tail bytes 0, all zero True.
- .sbss: mine 32, original 32 bytes; prefix mismatches 0/32; extra alignment tail bytes 0, all zero True.

AOSS_81400E0C raw .text bytes identical: True. SHA-256 mine 63ce5401f76a8449cd914634f600fd3410d63192a39e33e9b5f054b717a2dbee, original 63ce5401f76a8449cd914634f600fd3410d63192a39e33e9b5f054b717a2dbee. Raw bytes do not assert relocation identity. The gate instruction count remains authoritative.

Relocations at corresponding instruction offsets in objdiff-exact functions (observed mappings only, no object/config override):

- (('.sbss', 's_accessPointConfig', 4, 4, 0), ('.sbss', 'lbl_81698C74', 4, 4, 0))
- (('.sbss', 's_accessPointList', 0, 4, 0), ('.sbss', 'lbl_81698C70', 0, 4, 0))
- (('.sbss', 's_accessPointName', 8, 8, 0), ('.sbss', 'lbl_81698C78', 8, 8, 0))
- (('.sbss', 's_connectionState', 16, 4, 0), ('.sbss', 'lbl_81698C80', 16, 4, 0))
- (('.sbss', 's_errorCode', 20, 4, 0), ('.sbss', 'lbl_81698C84', 20, 4, 0))
- (('.sbss', 's_responseBuffer', 28, 4, 0), ('.sbss', 'lbl_81698C8C', 28, 4, 0))
- (('.sbss', 's_socketStarted', 24, 4, 0), ('.sbss', 'lbl_81698C88', 24, 4, 0))
- (('.sdata', 's_manufacturer', 4, 6, 0), ('.sdata', 'lbl_81697204', 4, 6, 0))
- (('.sdata', 's_socket', 0, 4, 0), ('.sdata', 'lbl_81697200', 0, 4, 0))

Data is not claimed 100%: AOSS .sbss symbol correspondence remains 42.857143%, despite all seven observed .sbss source globals now using the original offsets and identical physical bytes. Other AOSS data sections are 100%. Original extracted alignment tails are not synthesized.

Prior and current supplemental native verification PASS: KSA lengths 0/1/7/8/9/16/256/300; all 256 CRC rows; decryption/checksum rejection lengths 1/7/8/9/16/31/32/255/256/257; two-round vendor transform for eight even lengths 2..260 with three key lengths; hello packets for 64 encrypted/plain, active/broadcast, security-flag combinations against current HEAD behavior; request initialization preserves three network-order IDs and an eight-byte boundary canary; encryption flag is separate from progress state; three discovery error paths publish the error global; DHCP timeout clears config without altering response data, immediate host and cancellation paths. Decryption tests stub vendor/network conversion to isolate RC4; odd-length vendor-tail behavior is not claimed. All test harnesses are under /tmp.

Initialization uncertainty: original target AOSS_Init_old tests r14 at offset 0xa20 before its first assignment at 0xb2c in linear disassembly. The source keeps its existing initialized fallback; no undefined/uninitialized read was introduced to imitate this. Full initialization still differs and is not claimed exact.

## Retained instruction differences


AOSS_81401778

```text
src 0x44c base 0x444 insns 275/273
--- replace mine 5:7 base 5:6
  M    5 lis r31, 0
  M    6 lwz r30, 0(0)
  B    5 lwz r28, 0(0)
--- delete mine 9:10 base 8:8
  M    9 addi r31, r31, 0
--- insert mine 11:11 base 9:10
  B    9 li r30, 0
--- delete mine 12:13 base 11:11
  M   12 li r28, 0
--- replace mine 16:17 base 14:15
  M   16 mr r3, r30
  B   14 mr r3, r28
--- insert mine 23:23 base 21:22
  B   21 addi r31, r28, 0x18
--- replace mine 26:27 base 25:26
  M   26 addi r4, r31, 0
  B   25 lis r4, 0
--- insert mine 28:28 base 27:28
  B   27 addi r4, r4, 0
--- replace mine 35:38 base 35:40
  M   35 bne 652
  M   36 addi r4, r31, 0x9a8
  M   37 li r28, 1
  B   35 bne 640
  B   36 lis r25, 0
  B   37 li r29, 1
  B   38 addi r4, r25, 0
  B   39 li r30, -1
--- replace mine 40:49 base 42:49
  M   40 lbz r5, 0x18(r1)
  M   41 li r3, -1
  M   42 addi r4, r31, 0x9a8
  M   43 lbz r0, 0x19(r1)
  M   44 xor r3, r5, r3
  M   45 lbz r9, 0x1a(r1)
  M   46 rlwinm r3, r3, 2, 0x16, 0x1d
  M   47 lbz r8, 0x1b(r1)
  M   48 lwzx r5, r4, r3
  B   42 lbz r6, 0x18(r1)
  B   43 addi r5, r25, 0
  B   44 srwi r7, r30, 8
  B   45 li r0, -1
  B   46 xor r4, r30, r6
  B   47 lbz r6, 0x19(r1)
  B   48 rlwinm r4, r4, 2, 0x16, 0x1d
--- replace mine 50:52 base 50:71
  M   50 lbz r7, 0x1c(r1)
  M   51 xoris r11, r5, 0xff
  B   50 lwzx r4, r5, r4
  B   51 xor r30, r7, r4
  B   52 xor r4, r30, r6
  B   53 lbz r6, 0x1a(r1)
  B   54 rlwinm r4, r4, 2, 0x16, 0x1d
  B   55 srwi r7, r30, 8
  B   56 lwzx r4, r5, r4
  B   57 xor r30, r7, r4
  B   58 xor r4, r30, r6
  B   59 lbz r6, 0x1b(r1)
  B   60 rlwinm r4, r4, 2, 0x16, 0x1d
  B   61 srwi r7, r30, 8
  B   62 lwzx r4, r5, r4
  B   63 xor r30, r7, r4
  B   64 xor r4, r30, r6
  B   65 lbz r6, 0x1c(r1)
  B   66 rlwinm r4, r4, 2, 0x16, 0x1d
  B   67 srwi r7, r30, 8
  B   68 lwzx r4, r5, r4
  B   69 xor r30, r7, r4
  B   70 xor r4, r30, r6
--- replace mine 53:93 base 72:95
  M   53 xori r11, r11, 0xffff
  M   54 lbz r5, 0x1e(r1)
  M   55 xor r10, r11, r0
  M   56 lbz r0, 0x1f(r1)
  M   57 rlwinm r10, r10, 2, 0x16, 0x1d
  M   58 srwi r11, r11, 8
  M   59 lwzx r10, r4, r10
  M   60 xor r10, r11, r10
  M   61 xor r9, r10, r9
  M   62 rlwinm r9, r9, 2, 0x16, 0x1d
  M   63 srwi r10, r10, 8
  M   64 lwzx r9, r4, r9
  M   65 xor r9, r10, r9
  M   66 xor r8, r9, r8
  M   67 rlwinm r8, r8, 2, 0x16, 0x1d
  M   68 srwi r9, r9, 8
  M   69 lwzx r8, r4, r8
  M   70 xor r8, r9, r8
  M   71 xor r7, r8, r7
  M   72 rlwinm r7, r7, 2, 0x16, 0x1d
  M   73 srwi r8, r8, 8
  M   74 lwzx r7, r4, r7
  M   75 xor r7, r8, r7
  M   76 xor r6, r7, r6
  M   77 rlwinm r6, r6, 2, 0x16, 0x1d
  M   78 srwi r7, r7, 8
  M   79 lwzx r6, r4, r6
  M   80 xor r6, r7, r6
  M   81 xor r5, r6, r5
  M   82 rlwinm r5, r5, 2, 0x16, 0x1d
  M   83 srwi r6, r6, 8
  M   84 lwzx r5, r4, r5
  M   85 xor r5, r6, r5
  M   86 xor r0, r5, r0
  M   87 rlwinm r0, r0, 2, 0x16, 0x1d
  M   88 srwi r5, r5, 8
  M   89 lwzx r0, r4, r0
  M   90 xor r0, r5, r0
  M   91 clrlwi r0, r0, 0x18
  M   92 xori r29, r0, 0xff
  B   72 rlwinm r4, r4, 2, 0x16, 0x1d
  B   73 srwi r7, r30, 8
  B   74 lwzx r4, r5, r4
  B   75 xor r30, r7, r4
  B   76 xor r4, r30, r6
  B   77 lbz r6, 0x1e(r1)
  B   78 rlwinm r4, r4, 2, 0x16, 0x1d
  B   79 srwi r7, r30, 8
  B   80 lwzx r4, r5, r4
  B   81 xor r30, r7, r4
  B   82 xor r4, r30, r6
  B   83 lbz r6, 0x1f(r1)
  B   84 rlwinm r4, r4, 2, 0x16, 0x1d
  B   85 srwi r7, r30, 8
  B   86 lwzx r4, r5, r4
  B   87 xor r30, r7, r4
  B   88 xor r4, r30, r6
  B   89 rlwinm r4, r4, 2, 0x16, 0x1d
  B   90 srwi r7, r30, 8
  B   91 lwzx r4, r5, r4
  B   92 xor r30, r7, r4
  B   93 xor r0, r30, r0
  B   94 clrlwi r30, r0, 0x18
--- replace mine 96:97 base 98:99
  M   96 beq 388
  B   98 beq 368
--- replace mine 99:100 base 101:102
  M   99 addi r3, r30, 0x1a
  B  101 addi r3, r31, 2
--- replace mine 103:105 base 105:108
  M  103 addi r3, r31, 0x940
  M  104 addi r4, r30, 0x1a
  B  105 lis r25, 0
  B  106 addi r4, r31, 2
  B  107 addi r3, r25, 0
--- replace mine 107:108 base 110:111
  M  107 addi r25, r31, 0x940
  B  110 addi r25, r25, 0
--- replace mine 118:119 base 121:122
  M  118 addi r3, r1, 0x18
  B  121 addi r5, r1, 0x18
--- replace mine 121:123 base 124:147
  M  121 lwz r6, 0x28(r1)
  M  122 add r5, r30, r4
  B  124 lwz r3, 0x28(r1)
  B  125 add r6, r31, r4
  B  126 lwz r9, 0x34(r1)
  B  127 addi r4, r4, 1
  B  128 addi r8, r3, 1
  B  129 lwz r3, 0x30(r1)
  B  130 divwu r7, r8, r9
  B  131 lwz r0, 0x2c(r1)
  B  132 mullw r7, r7, r9
  B  133 subf r7, r7, r8
  B  134 clrlwi r8, r7, 0x18
  B  135 lbzx r10, r3, r8
  B  136 add r7, r10, r0
  B  137 divwu r0, r7, r9
  B  138 mullw r0, r0, r9
  B  139 subf r0, r0, r7
  B  140 clrlwi r0, r0, 0x18
  B  141 lbzx r7, r3, r0
  B  142 stw r8, 0x28(r1)
  B  143 add r9, r10, r7
  B  144 stw r0, 0x2c(r1)
  B  145 stbx r10, r3, r0
  B  146 stbx r7, r3, r8
--- insert mine 124:124 base 148:156
  B  148 lbz r0, 0(r5)
  B  149 divwu r7, r9, r8
  B  150 mullw r7, r7, r8
  B  151 subf r7, r7, r9
  B  152 lbzx r3, r3, r7
  B  153 xor r0, r3, r0
  B  154 stb r0, 4(r6)
  B  155 add r6, r31, r4
--- replace mine 125:128 base 157:162
  M  125 addi r9, r6, 1
  M  126 lwz r7, 0x30(r1)
  M  127 divwu r6, r9, r8
  B  157 lwz r3, 0x28(r1)
  B  158 lwz r9, 0x34(r1)
  B  159 addi r8, r3, 1
  B  160 lwz r3, 0x30(r1)
  B  161 divwu r7, r8, r9
--- replace mine 129:138 base 163:171
  M  129 mullw r6, r6, r8
  M  130 subf r6, r6, r9
  M  131 clrlwi r6, r6, 0x18
  M  132 stw r6, 0x28(r1)
  M  133 lbzx r9, r7, r6
  M  134 add r6, r9, r0
  M  135 divwu r0, r6, r8
  M  136 mullw r0, r0, r8
  M  137 subf r0, r0, r6
  B  163 mullw r7, r7, r9
  B  164 subf r7, r7, r8
  B  165 clrlwi r8, r7, 0x18
  B  166 lbzx r10, r3, r8
  B  167 add r7, r10, r0
  B  168 divwu r0, r7, r9
  B  169 mullw r0, r0, r9
  B  170 subf r0, r0, r7
--- insert mine 139:139 base 172:175
  B  172 lbzx r7, r3, r0
  B  173 stw r8, 0x28(r1)
  B  174 add r9, r10, r7
--- replace mine 140:158 base 176:178
  M  140 lbzx r8, r7, r0
  M  141 stbx r9, r7, r0
  M  142 add r7, r9, r8
  M  143 lwz r6, 0x30(r1)
  M  144 lwz r0, 0x28(r1)
  M  145 stbx r8, r6, r0
  M  146 lwz r6, 0x34(r1)
  M  147 lwz r8, 0x30(r1)
  M  148 divwu r0, r7, r6
  M  149 lbz r9, 0(r3)
  M  150 mullw r0, r0, r6
  M  151 subf r0, r0, r7
  M  152 lbzx r0, r8, r0
  M  153 xor r0, r9, r0
  M  154 stb r0, 0x1c(r5)
  M  155 add r5, r30, r4
  M  156 addi r4, r4, 1
  M  157 lwz r6, 0x28(r1)
  B  176 stbx r10, r3, r0
  B  177 stbx r7, r3, r8
--- replace mine 159:191 base 179:188
  M  159 addi r9, r6, 1
  M  160 lwz r7, 0x30(r1)
  M  161 divwu r6, r9, r8
  M  162 lwz r0, 0x2c(r1)
  M  163 mullw r6, r6, r8
  M  164 subf r6, r6, r9
  M  165 clrlwi r6, r6, 0x18
  M  166 stw r6, 0x28(r1)
  M  167 lbzx r9, r7, r6
  M  168 add r6, r9, r0
  M  169 divwu r0, r6, r8
  M  170 mullw r0, r0, r8
  M  171 subf r0, r0, r6
  M  172 clrlwi r0, r0, 0x18
  M  173 stw r0, 0x2c(r1)
  M  174 lbzx r8, r7, r0
  M  175 stbx r9, r7, r0
  M  176 add r7, r9, r8
  M  177 lwz r6, 0x30(r1)
  M  178 lwz r0, 0x28(r1)
  M  179 stbx r8, r6, r0
  M  180 lwz r6, 0x34(r1)
  M  181 lbz r9, 1(r3)
  M  182 addi r3, r3, 2
  M  183 divwu r0, r7, r6
  M  184 lwz r8, 0x30(r1)
  M  185 mullw r0, r0, r6
  M  186 subf r0, r0, r7
  M  187 lbzx r0, r8, r0
  M  188 xor r0, r9, r0
  M  189 stb r0, 0x1c(r5)
  M  190 bdnz -276
  B  179 lbz r0, 1(r5)
  B  180 addi r5, r5, 2
  B  181 divwu r7, r9, r8
  B  182 mullw r7, r7, r8
  B  183 subf r7, r7, r9
  B  184 lbzx r3, r3, r7
  B  185 xor r0, r3, r0
  B  186 stb r0, 4(r6)
  B  187 bdnz -252
--- replace mine 195:196 base 192:193
  M  195 sth r3, 0x18(r30)
  B  192 sth r3, 0(r31)
--- replace mine 198:199 base 195:196
  M  198 addi r3, r30, 0x18
  B  195 mr r3, r31
--- replace mine 202:203 base 199:200
  M  202 addi r3, r1, 0x10
  B  199 addi r3, r1, 0x20
--- replace mine 206:207 base 203:204
  M  206 addi r3, r1, 0x10
  B  203 addi r3, r1, 0x20
--- replace mine 216:217 base 213:214
  M  216 b 212
  B  213 b 216
--- replace mine 219:220 base 216:217
  M  219 sth r3, 0(r30)
  B  216 sth r3, 0(r28)
--- replace mine 222:224 base 219:221
  M  222 sth r26, 2(r30)
  M  223 sth r26, 4(r30)
  B  219 sth r26, 2(r28)
  B  220 sth r26, 4(r28)
--- replace mine 225:226 base 222:223
  M  225 sth r3, 6(r30)
  B  222 sth r3, 6(r28)
--- replace mine 227:228 base 224:225
  M  227 sth r26, 8(r30)
  B  224 sth r26, 8(r28)
--- replace mine 229:231 base 226:228
  M  229 sth r3, 0xa(r30)
  M  230 mr r3, r28
  B  226 sth r3, 0xa(r28)
  B  227 mr r3, r29
--- replace mine 232:233 base 229:230
  M  232 sth r3, 0xc(r30)
  B  229 sth r3, 0xc(r28)
--- replace mine 234:237 base 231:234
  M  234 addi r3, r30, 0x10
  M  235 addi r4, r1, 0x10
  M  236 stb r29, 0xe(r30)
  B  231 addi r3, r28, 0x10
  B  232 addi r4, r1, 0x20
  B  233 stb r30, 0xe(r28)
--- replace mine 238:239 base 235:236
  M  238 stb r0, 0xf(r30)
  B  235 stb r0, 0xf(r28)
--- replace mine 241:242 base 238:239
  M  241 addi r3, r1, 0x20
  B  238 addi r3, r1, 0x10
--- replace mine 248:249 base 245:246
  M  248 stb r0, 0x21(r1)
  B  245 stb r0, 0x11(r1)
--- replace mine 250:252 base 247:250
  M  250 addi r26, r31, 0
  M  251 sth r3, 0x22(r1)
  B  247 lis r26, 0
  B  248 sth r3, 0x12(r1)
  B  249 addi r26, r26, 0
--- replace mine 255:256 base 253:254
  M  255 stw r3, 0x24(r1)
  B  253 stw r3, 0x14(r1)
--- replace mine 259:260 base 257:258
  M  259 stw r0, 0x24(r1)
  B  257 stw r0, 0x14(r1)
--- replace mine 262:264 base 260:262
  M  262 stb r0, 0x20(r1)
  M  263 mr r4, r30
  B  260 stb r0, 0x10(r1)
  B  261 mr r4, r28
--- replace mine 265:266 base 263:264
  M  265 addi r7, r1, 0x20
  B  263 addi r7, r1, 0x10
```

AOSS_81401E80

```text
src 0x24c base 0x24c insns 147/147
diffs 36: [54, 59, 72, 74, 75, 76, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91]
    54 M ble -15235
       B ble -15567
    59 M blt -15255
       B blt -15587
    72 M add r4, r28, r3
       B add r4, r26, r3
    74 M add r5, r26, r3
       B add r5, r28, r3
    75 M xor r6, r6, r0
       B xor r0, r6, r0
    76 M stbx r6, r28, r3
       B stbx r0, r28, r3
    78 M lbz r6, 1(r4)
       B lbz r6, 1(r5)
    79 M lbz r0, 1(r5)
       B lbz r0, 1(r4)
    80 M xor r6, r6, r0
       B xor r0, r6, r0
    81 M stb r6, 1(r4)
       B stb r0, 1(r5)
    82 M lbz r6, 2(r4)
       B lbz r6, 2(r5)
    83 M lbz r0, 2(r5)
       B lbz r0, 2(r4)
    84 M xor r6, r6, r0
       B xor r0, r6, r0
    85 M stb r6, 2(r4)
       B stb r0, 2(r5)
    86 M lbz r6, 3(r4)
       B lbz r6, 3(r5)
    87 M lbz r0, 3(r5)
       B lbz r0, 3(r4)
    88 M xor r6, r6, r0
       B xor r0, r6, r0
    89 M stb r6, 3(r4)
       B stb r0, 3(r5)
    90 M lbz r6, 4(r4)
       B lbz r6, 4(r5)
    91 M lbz r0, 4(r5)
       B lbz r0, 4(r4)
    92 M xor r6, r6, r0
       B xor r0, r6, r0
    93 M stb r6, 4(r4)
       B stb r0, 4(r5)
    94 M lbz r6, 5(r4)
       B lbz r6, 5(r5)
    95 M lbz r0, 5(r5)
       B lbz r0, 5(r4)
    96 M xor r6, r6, r0
       B xor r0, r6, r0
    97 M stb r6, 5(r4)
       B stb r0, 5(r5)
    98 M lbz r6, 6(r4)
       B lbz r6, 6(r5)
    99 M lbz r0, 6(r5)
       B lbz r0, 6(r4)
   100 M xor r6, r6, r0
       B xor r0, r6, r0
   101 M stb r6, 6(r4)
       B stb r0, 6(r5)
   102 M lbz r6, 7(r4)
       B lbz r6, 7(r5)
   103 M lbz r0, 7(r5)
       B lbz r0, 7(r4)
   104 M xor r6, r6, r0
       B xor r0, r6, r0
   105 M stb r6, 7(r4)
       B stb r0, 7(r5)
   117 M xor r6, r6, r0
       B xor r0, r6, r0
   118 M stb r6, 0(r5)
       B stb r0, 0(r5)
```

Full unit gate PASS: instruction exact remains 15/21; matched code 6436/16192 and data 3896/3928 unchanged; fuzzy 87.587204 -> 87.592636. All six baseline instruction residuals received at least three successful distinct source trials. Native vendor two-round transform, 64 hello packet scenarios, KSA, CRC and decryption/checksum rejection checks passed. No new instruction-exact function is claimed.
