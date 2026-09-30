# Final remaining-function ctxdiff evidence

## libs/RVL_SDK/src/nup/nup __nupParseServerInfo__FP14NUPContextInfoPcPcUx

```text
src 0x710 base 0x710 insns 452/452
diffs 148: [13, 14, 15, 18, 21, 23, 26, 30, 32, 33, 34, 36, 41, 43, 44, 49, 52, 53, 56, 59]
    13 M addi r24, r28, 0x90
       B addi r25, r28, 0x90
    14 M addi r25, r28, 0x9c
       B addi r22, r28, 0x9c
    15 M li r27, 0
       B li r23, 0
    18 M mr r4, r25
       B mr r4, r22
    21 M mr r23, r3
       B mr r24, r3
    23 M mr r4, r24
       B mr r4, r25
    26 M mr r22, r3
       B mr r26, r3
    30 M mr r3, r25
       B mr r3, r22
    32 M add r29, r23, r3
       B add r24, r24, r3
    33 M mr r3, r24
       B mr r3, r25
    34 M subf r26, r29, r22
       B subf r25, r24, r26
    36 M add r0, r22, r3
       B add r0, r26, r3
    41 M cmplw r26, r3
       B cmplw r25, r3
    43 M mr r3, r29
       B mr r3, r24
    44 M mr r5, r26
       B mr r5, r25
    49 M li r27, -0x138c
       B li r23, -0x138c
    52 M addi r25, r28, 0xa8
       B addi r27, r28, 0xa8
    53 M addi r18, r28, 0xb4
       B addi r26, r28, 0xb4
    56 M mr r4, r18
       B mr r4, r26
    59 M mr r24, r3
       B mr r29, r3
    61 M mr r4, r25
       B mr r4, r27
    64 M mr r23, r3
       B mr r18, r3
    68 M mr r3, r18
       B mr r3, r26
    70 M add r29, r24, r3
       B add r24, r29, r3
    71 M mr r3, r25
       B mr r3, r27
    72 M subf r26, r29, r23
       B subf r25, r24, r18
    74 M add r0, r23, r3
       B add r0, r18, r3
    77 M mr r3, r29
       B mr r3, r24
    85 M li r27, -0x138c
       B li r23, -0x138c
    88 M addi r18, r28, 0xc0
       B addi r27, r28, 0xc0
    89 M addi r25, r28, 0xd0
       B addi r26, r28, 0xd0
    92 M mr r4, r25
       B mr r4, r26
    95 M mr r24, r3
       B mr r18, r3
    97 M mr r4, r18
       B mr r4, r27
   100 M mr r23, r3
       B mr r29, r3
   104 M mr r3, r25
       B mr r3, r26
   106 M add r29, r24, r3
       B add r24, r18, r3
   107 M mr r3, r18
       B mr r3, r27
   108 M subf r26, r29, r23
       B subf r25, r24, r29
   110 M add r0, r23, r3
       B add r0, r29, r3
   115 M cmplw r26, r3
       B cmplw r25, r3
   117 M mr r3, r29
       B mr r3, r24
   119 M mr r5, r26
       B mr r5, r25
   123 M li r27, -0x138c
       B li r23, -0x138c
   126 M addi r18, r28, 0xdc
       B addi r27, r28, 0xdc
   127 M addi r25, r28, 0xec
       B addi r26, r28, 0xec
   130 M mr r4, r25
       B mr r4, r26
   133 M mr r24, r3
       B mr r18, r3
   135 M mr r4, r18
       B mr r4, r27
   138 M mr r23, r3
       B mr r29, r3
   142 M mr r3, r25
       B mr r3, r26
   144 M add r29, r24, r3
       B add r24, r18, r3
   145 M mr r3, r18
       B mr r3, r27
   146 M subf r26, r29, r23
       B subf r25, r24, r29
   148 M add r0, r23, r3
       B add r0, r29, r3
   153 M cmplw r26, r3
       B cmplw r25, r3
   155 M mr r3, r29
       B mr r3, r24
   156 M mr r5, r26
       B mr r5, r25
   161 M li r27, -0x138c
       B li r23, -0x138c
   164 M addi r18, r28, 0xf8
       B addi r27, r28, 0xf8
   165 M addi r25, r28, 0x10c
       B addi r26, r28, 0x10c
   168 M mr r4, r25
       B mr r4, r26
   171 M mr r24, r3
       B mr r18, r3
   173 M mr r4, r18
       B mr r4, r27
   176 M mr r23, r3
       B mr r29, r3
   180 M mr r3, r25
       B mr r3, r26
   182 M add r29, r24, r3
       B add r24, r18, r3
   183 M mr r3, r18
       B mr r3, r27
   184 M subf r26, r29, r23
       B subf r25, r24, r29
   186 M add r0, r23, r3
       B add r0, r29, r3
   191 M cmplw r26, r3
       B cmplw r25, r3
   193 M lbz r3, 0(r29)
       B lbz r3, 0(r24)
   199 M li r27, -0x138c
       B li r23, -0x138c
   210 M addi r18, r28, 0x120
       B addi r27, r28, 0x120
   211 M addi r25, r28, 0x134
       B addi r26, r28, 0x134
   214 M mr r4, r25
       B mr r4, r26
   217 M mr r24, r3
       B mr r18, r3
   219 M mr r4, r18
       B mr r4, r27
   222 M mr r23, r3
       B mr r29, r3
   226 M mr r3, r25
       B mr r3, r26
   228 M add r29, r24, r3
       B add r24, r18, r3
   229 M mr r3, r18
       B mr r3, r27
   230 M subf r26, r29, r23
       B subf r25, r24, r29
   232 M add r0, r23, r3
       B add r0, r29, r3
   235 M cmpwi r26, 0
       B cmpwi r25, 0
   237 M li r27, -0x138c
       B li r23, -0x138c
   239 M addi r3, r26, 1
       B addi r3, r25, 1
   244 M li r27, -0x1388
       B li r23, -0x1388
   246 M mr r4, r29
       B mr r4, r24
   247 M mr r5, r26
       B mr r5, r25
   252 M addi r18, r28, 0x148
       B addi r27, r28, 0x148
   253 M stbx r0, r3, r26
       B stbx r0, r3, r25
   254 M addi r25, r28, 0x164
       B addi r26, r28, 0x164
   257 M mr r4, r25
       B mr r4, r26
   260 M mr r24, r3
       B mr r18, r3
   262 M mr r4, r18
       B mr r4, r27
   265 M mr r23, r3
       B mr r29, r3
   269 M mr r3, r25
       B mr r3, r26
   271 M add r29, r24, r3
       B add r24, r18, r3
   272 M mr r3, r18
       B mr r3, r27
   273 M subf r26, r29, r23
       B subf r25, r24, r29
   275 M add r0, r23, r3
       B add r0, r29, r3
   278 M cmpwi r26, 0
       B cmpwi r25, 0
   280 M li r27, -0x138c
       B li r23, -0x138c
   282 M addi r3, r26, 1
       B addi r3, r25, 1
   287 M li r27, -0x1388
       B li r23, -0x1388
   289 M mr r4, r29
       B mr r4, r24
   290 M mr r5, r26
       B mr r5, r25
   295 M addi r18, r28, 0x90
       B addi r27, r28, 0x90
   296 M stbx r0, r4, r26
       B stbx r0, r4, r25
   297 M addi r25, r28, 0x9c
       B addi r26, r28, 0x9c
   298 M addi r26, r28, 0x180
       B addi r25, r28, 0x180
   299 M addi r29, r28, 0x18c
       B addi r24, r28, 0x18c
   300 M li r24, 0
       B li r29, 0
   302 M addi r24, r24, 1
       B addi r29, r29, 1
   305 M mr r4, r29
       B mr r4, r24
   309 M mr r4, r26
       B mr r4, r25
   312 M mr r23, r3
       B mr r18, r3
   316 M mr r3, r29
       B mr r3, r24
   318 M mr r3, r26
       B mr r3, r25
   320 M add r3, r23, r3
       B add r3, r18, r3
   324 M mr r4, r25
       B mr r4, r26
   328 M mr r4, r18
       B mr r4, r27
   331 M mr r23, r3
       B mr r18, r3
   335 M mr r3, r25
       B mr r3, r26
   337 M mr r3, r18
       B mr r3, r27
   339 M add r3, r23, r3
       B add r3, r18, r3
   342 M mulli r23, r24, 0x60
       B mulli r18, r29, 0x60
   343 M mr r3, r23
       B mr r3, r18
   348 M li r27, -0x1388
       B li r23, -0x1388
   350 M mr r5, r23
       B mr r5, r18
   353 M addi r26, r28, 0x90
       B addi r24, r28, 0x90
   355 M addi r24, r28, 0x180
       B addi r26, r28, 0x180
   356 M addi r23, r28, 0x18c
       B addi r27, r28, 0x18c
   368 M li r27, -0x138c
       B li r23, -0x138c
   378 M li r27, -0x138c
       B li r23, -0x138c
   383 M li r27, -0x138c
       B li r23, -0x138c
   402 M mr r4, r23
       B mr r4, r27
   405 M mr r29, r3
       B mr r18, r3
   407 M mr r4, r24
       B mr r4, r26
   414 M mr r3, r23
       B mr r3, r27
   416 M add r22, r29, r3
       B add r22, r18, r3
   417 M mr r3, r24
       B mr r3, r26
   427 M mr r29, r3
       B mr r18, r3
   429 M mr r4, r26
       B mr r4, r24
   438 M add r21, r29, r3
       B add r21, r18, r3
   439 M mr r3, r26
       B mr r3, r24
   446 M mr r3, r27
       B mr r3, r23
```

## libs/RVL_SDK/src/nup/nup __nupGetServerInfo__FPcPcUxPcPcUlPcUsUsUxUsPPc

```text
src 0x244 base 0x244 insns 145/145
diffs 1: [58]
    58 M add r3, r3, r29
       B add r3, r29, r3
```

## libs/RVL_SDK/src/nup/nup __nupBase64Encode__FPUcPUcUl

```text
src 0xfc base 0xfc insns 63/63
diffs 21: [5, 9, 11, 16, 17, 18, 20, 21, 22, 23, 25, 31, 35, 38, 42, 44, 48, 52, 55, 58]
     5 M li r10, 0
       B li r7, 0
     9 M addi r10, r10, 1
       B addi r7, r7, 1
    11 M cmplwi r10, 3
       B cmplwi r7, 3
    16 M rlwinm r5, r9, 0x14, 0x1a, 0x1f
       B rlwinm r0, r9, 0xe, 0x1a, 0x1f
    17 M rlwinm r0, r9, 0xe, 0x1a, 0x1f
       B rlwinm r6, r9, 0x14, 0x1a, 0x1f
    18 M lbzx r7, r8, r5
       B lbzx r7, r8, r0
    20 M lbzx r6, r8, r0
       B clrlwi r0, r9, 0x1a
    21 M clrlwi r0, r9, 0x1a
       B lbzx r6, r8, r6
    22 M li r10, 0
       B stb r7, 0(r3)
    23 M stb r6, 0(r3)
       B li r7, 0
    25 M stb r7, 1(r3)
       B stb r6, 1(r3)
    31 M cmplwi r10, 2
       B cmplwi r7, 2
    35 M rlwinm r4, r9, 0x14, 0x1a, 0x1f
       B rlwinm r4, r9, 0xe, 0x1a, 0x1f
    38 M rlwinm r5, r9, 0xe, 0x1a, 0x1f
       B rlwinm r5, r9, 0x14, 0x1a, 0x1f
    42 M stb r5, 0(r3)
       B stb r6, 0(r3)
    44 M stb r6, 1(r3)
       B stb r5, 1(r3)
    48 M cmplwi r10, 1
       B cmplwi r7, 1
    52 M rlwinm r4, r9, 0x14, 0x1a, 0x1f
       B rlwinm r4, r9, 0xe, 0x1a, 0x1f
    55 M rlwinm r0, r9, 0xe, 0x1a, 0x1f
       B rlwinm r0, r9, 0x14, 0x1a, 0x1f
    58 M stb r0, 0(r3)
       B stb r4, 0(r3)
    59 M stb r4, 1(r3)
       B stb r0, 1(r3)
```

## libs/RVL_SDK/src/nup/nup __nupGetBootVersion__FP14ESTitleVersion

```text
Exact-name ctxdiff unavailable. Source symbol __nupGetBootVersion__FP14NUPContextInfoP14ESTitleVersion; cross-name instruction counts 163/163.
```

## libs/RVL_SDK/src/nup/nup __nupGetTitleSize__FP12NUPTitleInfo

```text
src 0x22c base 0x22c insns 139/139
diffs 22: [39, 40, 42, 43, 56, 57, 58, 59, 61, 62, 67, 68, 69, 71, 74, 75, 78, 80, 90, 91]
    39 M adde r0, r5, r7
       B adde r5, r5, r7
    40 M addi r5, r8, 5
       B addi r0, r8, 5
    42 M stw r5, 0x20(r3)
       B stw r0, 0x20(r3)
    43 M adde r0, r0, r7
       B adde r0, r5, r7
    56 M lwz r30, 0x54(r3)
       B lwz r28, 0x54(r3)
    57 M add r27, r12, r8
       B add r26, r12, r8
    58 M lwz r25, 0x5c(r27)
       B lwz r25, 0x5c(r26)
    59 M cmpwi r30, 0
       B cmpwi r28, 0
    61 M lwz r26, 0x58(r3)
       B lwz r30, 0x58(r3)
    62 M cmpwi r26, 0
       B cmpwi r30, 0
    67 M li r28, 0
       B li r27, 0
    68 M mtctr r30
       B mtctr r28
    69 M cmplwi r30, 0
       B cmplwi r28, 0
    71 M lwz r11, 0(r26)
       B lwz r11, 0(r30)
    74 M addi r28, r28, 4
       B addi r27, r27, 4
    75 M addi r26, r26, 4
       B addi r30, r30, 4
    78 M xor r11, r30, r12
       B xor r11, r28, r12
    80 M slw r11, r30, r11
       B slw r11, r28, r11
    90 M lwz r26, 0x68(r27)
       B lwz r27, 0x68(r26)
    91 M lwz r12, 0x64(r27)
       B lwz r12, 0x64(r26)
    92 M subfc r11, r26, r6
       B subfc r11, r27, r6
    99 M addc r11, r26, r5
       B addc r11, r27, r5
```

## libs/RVL_SDK/src/nup/nup __nupOp

```text
src 0x6e0 base 0x6d8 insns 440/438
--- delete mine 8:9 base 8:8
  M    8 li r28, 0
--- insert mine 11:11 base 10:11
  B   10 li r21, 0
--- delete mine 12:13 base 12:12
  M   12 li r21, 0
--- replace mine 26:28 base 25:27
  M   26 bne 1428
  M   27 lwz r31, 0x24(r1)
  B   25 bne 1424
  B   26 lwz r30, 0x24(r1)
--- replace mine 31:39 base 30:37
  M   31 bne 32
  M   32 lwz r4, 0x20(r1)
  M   33 li r0, -0x1389
  M   34 clrlwi r28, r4, 0x10
  M   35 cmplw r28, r4
  M   36 bne 8
  M   37 mr r0, r3
  M   38 mr r3, r0
  B   30 bne 28
  B   31 lwz r0, 0x20(r1)
  B   32 clrlwi r28, r0, 0x10
  B   33 cmplw r28, r0
  B   34 beq 8
  B   35 li r3, -0x1389
  B   36 cmplw r28, r0
--- replace mine 54:55 base 52:53
  M   54 li r30, 0
  B   52 li r31, 0
--- replace mine 56:57 base 54:55
  M   56 stw r30, 0x2c(r1)
  B   54 stw r31, 0x2c(r1)
--- replace mine 66:67 base 64:65
  M   66 stw r30, 0x2c(r1)
  B   64 stw r31, 0x2c(r1)
--- replace mine 88:89 base 86:87
  M   88 li r30, 1
  B   86 li r31, 1
--- replace mine 92:94 base 90:92
  M   92 li r30, 0
  M   93 cmpwi r30, 0
  B   90 li r31, 0
  B   91 cmpwi r31, 0
--- replace mine 114:115 base 112:113
  M  114 mr r6, r31
  B  112 mr r6, r30
--- replace mine 139:140 base 137:138
  M  139 mr r8, r31
  B  137 mr r8, r30
--- replace mine 147:148 base 145:146
  M  147 cmplw r30, r3
  B  145 cmplw r31, r3
--- replace mine 263:264 base 261:262
  M  263 lwz r5, 4(r20)
  B  261 lwz r8, 4(r20)
--- replace mine 265:267 base 263:265
  M  265 mtctr r5
  M  266 cmplwi r5, 0
  B  263 mtctr r8
  B  264 cmplwi r8, 0
--- replace mine 269:274 base 267:272
  M  269 add r6, r0, r4
  M  270 lwzx r7, r4, r0
  M  271 lwz r8, 4(r6)
  M  272 xori r0, r7, 1
  M  273 xori r3, r8, 1
  B  267 add r5, r0, r4
  B  268 lwzx r6, r4, r0
  B  269 lwz r7, 4(r5)
  B  270 xori r0, r6, 1
  B  271 xori r3, r7, 1
--- replace mine 276:277 base 274:275
  M  276 mr r23, r6
  B  274 mr r23, r5
--- replace mine 278:280 base 276:278
  M  278 xori r3, r8, 2
  M  279 xori r0, r7, 1
  B  276 xori r3, r7, 2
  B  277 xori r0, r6, 1
--- replace mine 282:283 base 280:281
  M  282 mr r22, r6
  B  280 mr r22, r5
--- replace mine 284:286 base 282:284
  M  284 xor r3, r8, r24
  M  285 xor r0, r7, r25
  B  282 xor r3, r24, r7
  B  283 xor r0, r25, r6
--- replace mine 288:289 base 286:287
  M  288 mr r21, r6
  B  286 mr r21, r5
--- replace mine 306:309 base 304:307
  M  306 lwz r8, 8(r3)
  M  307 mtctr r5
  M  308 cmplwi r5, 0
  B  304 lwz r9, 8(r3)
  B  305 mtctr r8
  B  306 cmplwi r8, 0
--- replace mine 315:316 base 313:314
  M  315 xor r3, r8, r3
  B  313 xor r3, r9, r3
```

## libs/RVL_SDK/src/kbd/kbd_lib kbdEventHandler

```text
src 0x2e8 base 0x2e8 insns 186/186
diffs 5: [35, 36, 38, 39, 42]
    35 M lbz r3, 2(r4)
       B lbz r5, 2(r4)
    36 M lis r30, 0
       B lis r3, 0
    38 M addi r0, r3, 0xff
       B addi r0, r5, 0xff
    39 M addi r30, r30, 0
       B addi r3, r3, 0
    42 M add r30, r30, r4
       B add r30, r3, r4
```

## libs/RVL_SDK/src/kbd/kbd_lib kbdProcKey

```text
src 0x2b8 base 0x2b0 insns 174/172
--- replace mine 6:9 base 6:9
  M    6 lis r7, 0
  M    7 mulli r8, r5, 0x268
  M    8 li r6, 0
  B    6 lis r6, 0
  B    7 mulli r7, r5, 0x268
  B    8 stb r5, 8(r1)
--- replace mine 10:12 base 10:11
  M   10 stb r5, 8(r1)
  M   11 addi r7, r7, 0
  B   10 addi r6, r6, 0
--- delete mine 15:16 base 14:14
  M   15 stw r6, 0x10(r1)
--- replace mine 17:18 base 15:16
  M   17 add r30, r7, r8
  B   15 add r30, r6, r7
```

## libs/RVL_SDK/src/kbd/kbd_lib kbdProcMod

```text
src 0x414 base 0x400 insns 261/256
--- replace mine 20:24 base 20:22
  M   20 lbz r8, 1(r6)
  M   21 bne 12
  M   22 li r7, 2
  M   23 b 52
  B   20 lbz r7, 1(r6)
  B   21 beq 40
--- replace mine 25:26 base 23:24
  M   25 bge 12
  B   23 bge 32
--- replace mine 27:30 base 25:26
  M   27 bne 12
  M   28 li r7, 4
  M   29 b 28
  B   25 beq 24
--- delete mine 31:32 base 27:27
  M   31 li r7, 0
--- delete mine 36:40 base 31:31
  M   36 cmpwi r7, 0
  M   37 beq 12
  M   38 lwz r6, 0x220(r4)
  M   39 stw r6, 8(r1)
--- replace mine 43:44 base 34:35
  M   43 bgt 752
  B   34 bgt 768
--- replace mine 54:55 base 45:46
  M   54 beq 708
  B   45 beq 724
--- replace mine 58:63 base 49:54
  M   58 b 692
  M   59 lbz r6, 0x225(r4)
  M   60 lwz r3, 8(r1)
  M   61 add r0, r6, r0
  M   62 clrlwi r6, r0, 0x18
  B   49 b 708
  B   50 lbz r3, 0x225(r4)
  B   51 lwz r6, 8(r1)
  B   52 add r0, r3, r0
  B   53 clrlwi r3, r0, 0x18
--- replace mine 64:69 base 55:61
  M   64 neg r0, r6
  M   65 or r0, r0, r6
  M   66 rlwimi r3, r0, 2, 0x1e, 0x1e
  M   67 stw r3, 8(r1)
  M   68 b 652
  B   55 neg r0, r3
  B   56 or r0, r0, r3
  B   57 rlwinm r0, r0, 2, 0x1e, 0x1e
  B   58 rlwimi r0, r6, 0, 0x1f, 0x1d
  B   59 stw r0, 8(r1)
  B   60 b 664
--- replace mine 73:74 base 65:66
  M   73 beq 632
  B   65 beq 644
--- replace mine 77:78 base 69:70
  M   77 b 616
  B   69 b 628
--- replace mine 88:89 base 80:81
  M   88 b 572
  B   80 b 584
--- replace mine 93:94 base 85:86
  M   93 beq 552
  B   85 beq 564
--- replace mine 97:102 base 89:94
  M   97 b 536
  M   98 lbz r6, 0x224(r4)
  M   99 lwz r3, 8(r1)
  M  100 add r0, r6, r0
  M  101 clrlwi r6, r0, 0x18
  B   89 b 548
  B   90 lbz r3, 0x224(r4)
  B   91 lwz r6, 8(r1)
  B   92 add r0, r3, r0
  B   93 clrlwi r3, r0, 0x18
--- replace mine 103:108 base 95:101
  M  103 neg r0, r6
  M  104 or r0, r0, r6
  M  105 rlwimi r3, r0, 1, 0x1f, 0x1f
  M  106 stw r3, 8(r1)
  M  107 b 496
  B   95 neg r0, r3
  B   96 or r0, r0, r3
  B   97 srwi r0, r0, 0x1f
  B   98 rlwimi r0, r6, 0, 0, 0x1e
  B   99 stw r0, 8(r1)
  B  100 b 504
--- replace mine 109:110 base 102:103
  M  109 beq 488
  B  102 beq 496
--- replace mine 112:113 base 105:106
  M  112 beq 476
  B  105 beq 484
--- replace mine 116:117 base 109:110
  M  116 b 460
  B  109 b 468
--- replace mine 118:119 base 111:112
  M  118 beq 452
  B  111 beq 460
--- replace mine 121:122 base 114:115
  M  121 beq 440
  B  114 beq 448
--- replace mine 125:126 base 118:119
  M  125 b 424
  B  118 b 432
--- replace mine 127:128 base 120:121
  M  127 beq 416
  B  120 beq 424
--- replace mine 130:131 base 123:124
  M  130 beq 404
  B  123 beq 412
--- replace mine 138:139 base 131:132
  M  138 bge 372
  B  131 bge 380
--- replace mine 141:142 base 134:135
  M  141 b 360
  B  134 b 368
--- replace mine 144:146 base 137:139
  M  144 b 348
  M  145 clrlwi r0, r8, 0x1f
  B  137 b 356
  B  138 clrlwi r0, r7, 0x1f
--- replace mine 147:148 base 140:141
  M  147 bne 336
  B  140 bne 344
--- replace mine 150:152 base 143:145
  M  150 b 324
  M  151 rlwinm r0, r8, 0, 0x1d, 0x1d
  B  143 b 332
  B  144 rlwinm r0, r7, 0, 0x1d, 0x1d
--- replace mine 155:156 base 148:149
  M  155 bne 304
  B  148 bne 312
--- replace mine 158:159 base 151:152
  M  158 b 292
  B  151 b 300
--- replace mine 161:162 base 154:155
  M  161 b 280
  B  154 b 288
--- replace mine 164:165 base 157:158
  M  164 b 268
  B  157 b 276
--- replace mine 169:170 base 162:163
  M  169 beq 248
  B  162 beq 256
--- replace mine 173:174 base 166:167
  M  173 b 232
  B  166 b 240
--- replace mine 184:185 base 177:178
  M  184 b 188
  B  177 b 196
--- replace mine 189:190 base 182:183
  M  189 beq 168
  B  182 beq 176
--- replace mine 193:194 base 186:187
  M  193 b 152
  B  186 b 160
--- replace mine 196:204 base 189:198
  M  196 add r0, r6, r0
  M  197 clrlwi r6, r0, 0x18
  M  198 stb r0, 0x227(r4)
  M  199 neg r0, r6
  M  200 or r0, r0, r6
  M  201 rlwimi r3, r0, 4, 0x1c, 0x1c
  M  202 stw r3, 8(r1)
  M  203 b 112
  B  189 add r7, r6, r0
  B  190 clrlwi r6, r7, 0x18
  B  191 rlwinm r0, r3, 0, 0x1d, 0x1b
  B  192 neg r3, r6
  B  193 stb r7, 0x227(r4)
  B  194 or r3, r3, r6
  B  195 rlwimi r0, r3, 4, 0x1c, 0x1c
  B  196 stw r0, 8(r1)
  B  197 b 116
--- replace mine 208:209 base 202:203
  M  208 beq 92
  B  202 beq 96
--- replace mine 212:213 base 206:207
  M  212 b 76
  B  206 b 80
--- replace mine 215:222 base 209:217
  M  215 add r0, r6, r0
  M  216 clrlwi r6, r0, 0x18
  M  217 stb r0, 0x229(r4)
  M  218 neg r0, r6
  M  219 or r0, r0, r6
  M  220 rlwimi r3, r0, 5, 0x1b, 0x1b
  M  221 stw r3, 8(r1)
  B  209 add r7, r6, r0
  B  210 clrlwi r6, r7, 0x18
  B  211 rlwinm r0, r3, 0, 0x1c, 0x1a
  B  212 neg r3, r6
  B  213 stb r7, 0x229(r4)
  B  214 or r3, r3, r6
  B  215 rlwimi r0, r3, 5, 0x1b, 0x1b
  B  216 stw r0, 8(r1)
--- replace mine 250:254 base 245:249
  M  250 add r5, r4, r31
  M  251 lwz r4, 0x220(r5)
  M  252 rlwimi r0, r4, 0, 0x1a, 0x1f
  M  253 stw r0, 0x220(r5)
  B  245 add r4, r4, r31
  B  246 lwz r5, 0x220(r4)
  B  247 rlwimi r0, r5, 0, 0x1a, 0x1f
  B  248 stw r0, 0x220(r4)
```

## libs/RVL_SDK/src/kbd/kbd_lib kbd_led_handler

```text
src 0x60 base 0x64 insns 24/25
--- replace mine 2:4 base 2:4
  M    2 slwi r7, r4, 3
  M    3 slwi r0, r4, 5
  B    2 slwi r0, r4, 3
  B    3 li r8, 0
--- insert mine 5:5 base 5:7
  B    5 slwi r7, r4, 5
  B    6 lwzx r0, r5, r0
--- replace mine 6:10 base 8:10
  M    6 lwzx r12, r5, r7
  M    7 li r4, 0
  M    8 stwx r4, r6, r0
  M    9 cmpwi r12, 0
  B    8 stwx r8, r6, r7
  B    9 cmplw r0, r8
--- replace mine 12:14 base 12:13
  M   12 beq 8
  M   13 b 12
  B   12 bne 12
--- replace mine 17:20 base 16:21
  M   17 lis r4, 0
  M   18 addi r4, r4, 0
  M   19 add r4, r4, r7
  B   16 lis r5, 0
  B   17 slwi r0, r4, 3
  B   18 addi r5, r5, 0
  B   19 lwzx r12, r5, r0
  B   20 add r4, r5, r0
```

## libs/RVL_SDK/src/kbd/kbd_lib KBDSetLedsAsync

```text
src 0x150 base 0x144 insns 84/81
--- replace mine 14:15 base 14:15
  M   14 b 256
  B   14 b 244
--- replace mine 18:23 base 18:22
  M   18 b 240
  M   19 clrlwi r0, r3, 0x18
  M   20 addi r3, r31, 0x580
  M   21 mulli r0, r0, 0x268
  M   22 add r3, r3, r0
  B   18 b 228
  B   19 mulli r3, r3, 0x268
  B   20 addi r0, r31, 0x580
  B   21 add r3, r0, r3
--- replace mine 29:31 base 28:30
  M   29 b 196
  M   30 clrlwi r29, r4, 0x18
  B   28 b 188
  B   29 clrlwi r30, r4, 0x18
--- replace mine 33:35 base 32:35
  M   33 addi r4, r31, 0x400
  M   34 li r30, 0
  B   32 addi r6, r31, 0x400
  B   33 li r29, 0
  B   34 li r4, 0
--- replace mine 36:37 base 36:37
  M   36 lwz r0, 0(r4)
  B   36 lwzx r0, r6, r4
--- replace mine 38:39 base 38:39
  M   38 bne 36
  B   38 bne 28
--- replace mine 40:46 base 40:44
  M   40 addi r6, r31, 0x580
  M   41 slwi r0, r30, 5
  M   42 addi r4, r31, 0x400
  M   43 add r5, r6, r5
  M   44 lwz r5, 0xc(r5)
  M   45 stwx r5, r4, r0
  B   40 addi r0, r31, 0x580
  B   41 add r5, r0, r5
  B   42 lwz r0, 0xc(r5)
  B   43 stwx r0, r6, r4
--- insert mine 47:47 base 45:46
  B   45 addi r29, r29, 1
--- replace mine 48:50 base 47:48
  M   48 addi r30, r30, 1
  M   49 bdnz -52
  B   47 bdnz -44
--- replace mine 51:52 base 49:50
  M   51 cmplwi r30, 0xc
  B   49 cmplwi r29, 0xc
--- replace mine 54:58 base 52:56
  M   54 b 96
  M   55 mulli r0, r26, 0x268
  M   56 addi r3, r31, 0x580
  M   57 slwi r5, r30, 3
  B   52 b 92
  B   53 mulli r3, r26, 0x268
  B   54 addi r0, r31, 0x580
  B   55 slwi r5, r29, 3
--- replace mine 59:60 base 57:58
  M   59 add r3, r3, r0
  B   57 add r3, r0, r3
--- replace mine 64:65 base 62:63
  M   64 slwi r5, r30, 5
  B   62 slwi r5, r29, 5
--- replace mine 67:69 base 65:67
  M   67 mr r4, r29
  M   68 mr r7, r30
  B   65 mr r4, r30
  B   66 mr r7, r29
--- replace mine 73:75 base 71:74
  M   73 beq 8
  M   74 b 12
  B   71 beq 12
  B   72 li r3, 7
  B   73 b 8
--- delete mine 76:78 base 75:75
  M   76 b 8
  M   77 li r3, 7
```

## libs/RVL_SDK/src/kbd/kbd_lib KBDSetLeds

```text
src 0x138 base 0x13c insns 78/79
--- insert mine 4:4 base 4:5
  B    4 mr r31, r3
--- replace mine 15:16 base 16:17
  M   15 mulli r31, r3, 0x268
  B   16 mulli r0, r3, 0x268
--- replace mine 18:19 base 19:20
  M   18 add r3, r3, r31
  B   19 add r3, r3, r0
--- replace mine 26:27 base 27:28
  M   26 clrlwi r29, r4, 0x18
  B   27 clrlwi r30, r4, 0x18
--- replace mine 28:29 base 29:30
  M   28 lis r4, 0
  B   29 lis r6, 0
--- replace mine 30:32 base 31:34
  M   30 li r30, 0
  M   31 addi r4, r4, 0
  B   31 li r29, 0
  B   32 li r4, 0
  B   33 addi r6, r6, 0
--- replace mine 33:34 base 35:36
  M   33 lwz r0, 0(r4)
  B   35 lwzx r0, r6, r4
--- replace mine 35:36 base 37:39
  M   35 bne 40
  B   37 bne 32
  B   38 mulli r0, r31, 0x268
--- delete mine 37:38 base 40:40
  M   37 lis r4, 0
--- replace mine 39:44 base 41:44
  M   39 slwi r0, r30, 5
  M   40 add r5, r5, r31
  M   41 addi r4, r4, 0
  M   42 lwz r5, 0xc(r5)
  M   43 stwx r5, r4, r0
  B   41 add r5, r5, r0
  B   42 lwz r0, 0xc(r5)
  B   43 stwx r0, r6, r4
--- insert mine 45:45 base 45:46
  B   45 addi r29, r29, 1
--- replace mine 46:48 base 47:48
  M   46 addi r30, r30, 1
  M   47 bdnz -56
  B   47 bdnz -48
--- replace mine 49:50 base 49:50
  M   49 cmplwi r30, 0xc
  B   49 cmplwi r29, 0xc
--- replace mine 52:53 base 52:54
  M   52 b 76
  B   52 b 80
  B   53 mulli r0, r31, 0x268
--- replace mine 54:55 base 55:56
  M   54 lis r5, 0
  B   55 lis r31, 0
--- replace mine 56:60 base 57:60
  M   56 slwi r0, r30, 5
  M   57 add r3, r3, r31
  M   58 addi r5, r5, 0
  M   59 add r31, r5, r0
  B   57 add r3, r3, r0
  B   58 addi r31, r31, 0
  B   59 slwi r0, r29, 5
--- replace mine 61:63 base 61:63
  M   61 mr r4, r29
  M   62 mr r5, r31
  B   61 mr r4, r30
  B   62 add r5, r31, r0
--- delete mine 64:65 base 64:64
  M   64 li r0, 0
--- replace mine 66:67 base 65:68
  M   66 stw r0, 0(r31)
  B   65 slwi r0, r29, 5
  B   66 li r3, 0
  B   67 stwx r3, r31, r0
```

## libs/RVL_SDK/src/kbd/kbd_lib KBDSetModState

```text
src 0xa8 base 0xa8 insns 42/42
diffs 4: [30, 31, 32, 33]
    30 M add r5, r5, r4
       B add r4, r5, r4
    31 M lwz r4, 0x220(r5)
       B lwz r5, 0x220(r4)
    32 M rlwimi r0, r4, 0, 0x1a, 0x1f
       B rlwimi r0, r5, 0, 0x1a, 0x1f
    33 M stw r0, 0x220(r5)
       B stw r0, 0x220(r4)
```

## libs/RVL_SDK/src/kbd/kbd_lib KBDTranslateHidCode

```text
src 0x290 base 0x290 insns 164/164
diffs 9: [44, 45, 46, 79, 81, 83, 88, 91, 102]
    44 M lhzx r9, r3, r6
       B lhzx r11, r3, r6
    45 M rlwinm r10, r9, 0, 0x10, 0x11
       B rlwinm r9, r11, 0, 0x10, 0x11
    46 M addis r6, r10, 0
       B addis r6, r9, 0
    79 M cmpwi r10, 0
       B cmpwi r9, 0
    81 M clrlwi r11, r8, 0x10
       B clrlwi r10, r8, 0x10
    83 M and. r8, r9, r11
       B and. r8, r11, r10
    88 M addis r8, r10, 0
       B addis r8, r9, 0
    91 M and. r8, r9, r11
       B and. r8, r11, r10
   102 M cmpwi r10, 0x4000
       B cmpwi r9, 0x4000
```

## src/scene/memoryCard/iplMemoryCardManager isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl

```text
src 0x1d8 base 0x1d8 insns 118/118
diffs 41: [13, 14, 17, 19, 26, 28, 29, 33, 34, 35, 36, 37, 38, 41, 42, 45, 48, 51, 52, 63]
    13 M mr r31, r3
       B slwi r0, r28, 4
    14 M slwi r0, r28, 4
       B mr r31, r3
    17 M li r29, 0
       B li r28, 0
    19 M lwz r28, 8(r5)
       B lwz r29, 8(r5)
    26 M mulli r3, r28, 0xc
       B mulli r3, r29, 0xc
    28 M add r4, r3, r0
       B add r5, r0, r3
    29 M lbz r0, 5(r4)
       B lbz r0, 5(r5)
    33 M mulli r3, r26, 0x14
       B mulli r3, r0, 0x14
    34 M mulli r0, r0, 0x14
       B mulli r0, r26, 0x14
    35 M add r3, r31, r3
       B add r4, r31, r3
    36 M lwz r3, 8(r3)
       B add r3, r31, r0
    37 M add r5, r31, r0
       B lwz r3, 8(r3)
    38 M lwz r0, 8(r5)
       B lwz r0, 8(r4)
    41 M lhz r3, 0x10(r5)
       B lhz r3, 0x10(r4)
    42 M lhz r0, 2(r4)
       B lhz r0, 2(r5)
    45 M lhz r0, 0xe(r5)
       B lhz r0, 0xe(r4)
    48 M lhz r0, 6(r4)
       B lhz r0, 6(r5)
    51 M li r28, -0x15
       B li r29, -0x15
    52 M li r29, 1
       B li r28, 1
    63 M li r28, -0x17
       B li r29, -0x17
    71 M li r28, -0x16
       B li r29, -0x16
    73 M li r28, -0x1c
       B li r29, -0x1c
    76 M mulli r3, r28, 0xc
       B mulli r3, r29, 0xc
    78 M add r4, r3, r0
       B add r5, r0, r3
    79 M lbz r0, 5(r4)
       B lbz r0, 5(r5)
    82 M li r28, -0x1a
       B li r29, -0x1a
    85 M mulli r3, r26, 0x14
       B mulli r3, r0, 0x14
    86 M mulli r0, r0, 0x14
       B mulli r0, r26, 0x14
    87 M add r3, r31, r3
       B add r4, r31, r3
    88 M lwz r3, 8(r3)
       B add r3, r31, r0
    89 M add r5, r31, r0
       B lwz r3, 8(r3)
    90 M lwz r0, 8(r5)
       B lwz r0, 8(r4)
    93 M li r28, -0x1b
       B li r29, -0x1b
    95 M lhz r3, 0x10(r5)
       B lhz r3, 0x10(r4)
    96 M lhz r0, 2(r4)
       B lhz r0, 2(r5)
    99 M lhz r0, 0xe(r5)
       B lhz r0, 0xe(r4)
   102 M li r28, -0x19
       B li r29, -0x19
   104 M lhz r0, 6(r4)
       B lhz r0, 6(r5)
   107 M li r28, -0x18
       B li r29, -0x18
   110 M stw r28, 0(r27)
       B stw r29, 0(r27)
   112 M mr r3, r29
       B mr r3, r28
```

## src/scene/memoryCard/iplMemoryCardManager isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl

```text
src 0x1d8 base 0x1d8 insns 118/118
diffs 41: [13, 14, 17, 19, 26, 28, 29, 33, 34, 35, 36, 37, 38, 41, 42, 45, 48, 51, 52, 63]
    13 M mr r31, r3
       B slwi r0, r28, 4
    14 M slwi r0, r28, 4
       B mr r31, r3
    17 M li r29, 0
       B li r28, 0
    19 M lwz r28, 8(r5)
       B lwz r29, 8(r5)
    26 M mulli r3, r28, 0xc
       B mulli r3, r29, 0xc
    28 M add r4, r3, r0
       B add r5, r0, r3
    29 M lbz r0, 4(r4)
       B lbz r0, 4(r5)
    33 M mulli r3, r26, 0x14
       B mulli r3, r0, 0x14
    34 M mulli r0, r0, 0x14
       B mulli r0, r26, 0x14
    35 M add r3, r31, r3
       B add r4, r31, r3
    36 M lwz r3, 8(r3)
       B add r3, r31, r0
    37 M add r5, r31, r0
       B lwz r3, 8(r3)
    38 M lwz r0, 8(r5)
       B lwz r0, 8(r4)
    41 M lhz r3, 0x10(r5)
       B lhz r3, 0x10(r4)
    42 M lhz r0, 2(r4)
       B lhz r0, 2(r5)
    45 M lhz r0, 0xe(r5)
       B lhz r0, 0xe(r4)
    48 M lhz r0, 6(r4)
       B lhz r0, 6(r5)
    51 M li r28, -0x15
       B li r29, -0x15
    52 M li r29, 1
       B li r28, 1
    63 M li r28, -0x17
       B li r29, -0x17
    71 M li r28, -0x16
       B li r29, -0x16
    73 M li r28, -0x1c
       B li r29, -0x1c
    76 M mulli r3, r28, 0xc
       B mulli r3, r29, 0xc
    78 M add r4, r3, r0
       B add r5, r0, r3
    79 M lbz r0, 4(r4)
       B lbz r0, 4(r5)
    82 M li r28, -0x1a
       B li r29, -0x1a
    85 M mulli r3, r26, 0x14
       B mulli r3, r0, 0x14
    86 M mulli r0, r0, 0x14
       B mulli r0, r26, 0x14
    87 M add r3, r31, r3
       B add r4, r31, r3
    88 M lwz r3, 8(r3)
       B add r3, r31, r0
    89 M add r5, r31, r0
       B lwz r3, 8(r3)
    90 M lwz r0, 8(r5)
       B lwz r0, 8(r4)
    93 M li r28, -0x1b
       B li r29, -0x1b
    95 M lhz r3, 0x10(r5)
       B lhz r3, 0x10(r4)
    96 M lhz r0, 2(r4)
       B lhz r0, 2(r5)
    99 M lhz r0, 0xe(r5)
       B lhz r0, 0xe(r4)
   102 M li r28, -0x19
       B li r29, -0x19
   104 M lhz r0, 6(r4)
       B lhz r0, 6(r5)
   107 M li r28, -0x18
       B li r29, -0x18
   110 M stw r28, 0(r27)
       B stw r29, 0(r27)
   112 M mr r3, r29
       B mr r3, r28
```

## src/scene/memoryCard/iplMemoryCardManager isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs

```text
src 0x68 base 0x68 insns 26/26
diffs 8: [11, 12, 13, 14, 15, 16, 17, 18]
    11 M addi r11, r1, 0x20
       B add r4, r29, r4
    12 M add r4, r29, r4
       B add r4, r4, r0
    13 M add r4, r4, r0
       B mulli r5, r30, 0x1fc0
    14 M mulli r5, r30, 0x1fc0
       B lwz r4, 8(r4)
    15 M lwz r4, 8(r4)
       B add r0, r3, r5
    16 M add r0, r3, r5
       B slwi r3, r4, 6
    17 M slwi r3, r4, 6
       B lbzx r3, r3, r0
    18 M lbzx r3, r3, r0
       B addi r11, r1, 0x20
```

## src/scene/memoryCard/iplMemoryCardManager update_icon_anm__Q33ipl5scene17MemoryCardManagerFv

```text
src 0x14c base 0x150 insns 83/84
--- replace mine 29:30 base 29:30
  M   29 bge 160
  B   29 bge 164
--- replace mine 33:34 base 33:34
  M   33 beq 144
  B   33 beq 148
--- replace mine 38:41 base 38:41
  M   38 lbz r26, 4(r9)
  M   39 lha r22, 0x10e8(r8)
  M   40 extsb r26, r26
  B   38 lbz r22, 4(r9)
  B   39 lha r26, 0x10e8(r8)
  B   40 extsb r22, r22
--- replace mine 46:52 base 46:53
  M   46 blt 48
  M   47 lbz r26, 5(r9)
  M   48 cmplwi r26, 4
  M   49 bne 28
  M   50 lbz r26, 7(r9)
  M   51 subf r26, r26, r22
  B   46 blt 52
  B   47 lbz r22, 5(r9)
  B   48 cmplwi r22, 4
  B   49 bne 32
  B   50 lbz r22, 7(r9)
  B   51 lha r26, 0x12(r9)
  B   52 subf r26, r22, r26
--- replace mine 70:71 base 71:72
  M   70 bdnz -176
  B   71 bdnz -180
--- replace mine 76:77 base 77:78
  M   76 blt -228
  B   77 blt -232
```

## src/scene/memoryCard/iplMemoryCardManager update_file_array__Q33ipl5scene17MemoryCardManagerFUc

```text
src 0x168 base 0x168 insns 90/90
diffs 4: [15, 16, 17, 20]
    15 M addis r4, r30, 1
       B addis r3, r30, 1
    16 M lwz r3, 0x6934(r4)
       B lwz r4, 0x6934(r3)
    17 M addi r0, r3, -1
       B addi r0, r4, -1
    20 M lwz r0, 0x6930(r4)
       B lwz r0, 0x6930(r3)
```

## src/scene/memoryCard/iplMemoryCardManager create_icon__Q33ipl5scene17MemoryCardManagerFUcs

```text
src 0xc8 base 0xcc insns 50/51
--- replace mine 16:18 base 16:18
  M   16 li r9, 0
  M   17 lwz r8, 8(r4)
  B   16 li r8, 0
  B   17 lwz r9, 8(r4)
--- replace mine 19:21 base 19:21
  M   19 slwi r5, r8, 6
  M   20 mulli r6, r31, 0x1fc0
  B   19 slwi r6, r9, 6
  B   20 mulli r5, r31, 0x1fc0
--- replace mine 22:25 base 22:24
  M   22 add r3, r3, r6
  M   23 mulli r4, r8, 0x15c
  M   24 add r5, r5, r3
  B   22 mulli r4, r9, 0x15c
  B   23 add r5, r3, r5
--- replace mine 26:31 base 25:32
  M   26 lhz r4, 0x10(r5)
  M   27 lha r3, 0x10e8(r3)
  M   28 rlwinm r0, r9, 1, 0x1a, 0x1e
  M   29 addi r9, r9, 1
  M   30 sraw r0, r4, r0
  B   25 add r4, r6, r5
  B   26 lha r5, 0x10e8(r3)
  B   27 extsh r0, r8
  B   28 lhz r3, 0x10(r4)
  B   29 slwi r0, r0, 1
  B   30 addi r8, r8, 1
  B   31 sraw r0, r3, r0
--- replace mine 33:34 base 34:35
  M   33 cmpw r3, r7
  B   34 cmpw r5, r7
--- replace mine 35:39 base 36:40
  M   35 extsh r0, r9
  M   36 cmpwi r0, 9
  M   37 blt -36
  M   38 extsh r6, r9
  B   36 extsh r0, r8
  B   37 cmpwi r0, 8
  B   38 ble -44
  B   39 extsh r6, r8
--- replace mine 41:42 base 42:43
  M   41 extsh r5, r8
  B   42 extsh r5, r9
```

## src/scene/memoryCard/iplMemoryCardManager _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl

```text
src 0x190 base 0x190 insns 100/100
diffs 37: [19, 20, 22, 23, 24, 34, 39, 40, 42, 44, 45, 46, 47, 48, 57, 59, 63, 64, 65, 66]
    19 M mulli r30, r26, 0x1fc0
       B mulli r29, r26, 0x1fc0
    20 M slwi r31, r27, 6
       B slwi r30, r27, 6
    22 M add r0, r31, r3
       B add r0, r3, r29
    23 M add r29, r30, r0
       B add r31, r0, r30
    24 M add r3, r29, r28
       B add r3, r31, r28
    34 M add r3, r29, r0
       B add r3, r31, r0
    39 M add r4, r29, r0
       B add r4, r0, r31
    40 M mulli r26, r27, 0x15c
       B mulli r24, r27, 0x15c
    42 M addi r27, r3, 0x10ec
       B addi r25, r3, 0x10ec
    44 M add r24, r27, r26
       B add r3, r25, r24
    45 M mr r3, r24
       B bl 0
    46 M bl 0
       B add r24, r25, r24
    47 M mr r3, r24
       B li r4, 0
    48 M li r4, 0
       B mr r3, r24
    57 M mullw r28, r26, r4
       B mullw r26, r26, r4
    59 M add r3, r29, r0
       B add r3, r31, r0
    63 M mulli r26, r27, 0x15c
       B add r3, r25, r26
    64 M add r3, r25, r28
       B add r4, r31, r0
    65 M add r4, r29, r0
       B mulli r27, r27, 0x15c
    66 M addi r27, r3, 0x10ec
       B li r7, 9
    67 M li r7, 9
       B addi r28, r3, 0x10ec
    69 M add r3, r27, r26
       B add r3, r28, r27
    73 M add r0, r24, r30
       B add r0, r24, r29
    74 M add r4, r25, r28
       B add r4, r25, r26
    75 M add r3, r0, r31
       B add r3, r0, r30
    77 M add r4, r4, r26
       B lwz r0, 0x3c(r3)
    78 M lwz r0, 0x3c(r3)
       B addi r24, r4, 0x112c
    79 M addi r24, r4, 0x112c
       B add r3, r24, r27
    81 M mr r3, r24
       B add r4, r31, r0
    82 M add r4, r29, r0
       B bl 0
    83 M bl 0
       B add r3, r24, r27
    84 M mr r3, r24
       B li r4, 0
    85 M li r4, 0
       B bl 0
    86 M bl 0
       B add r24, r28, r27
    87 M add r3, r27, r26
       B li r4, 0
    88 M li r4, 0
       B mr r3, r24
    93 M add r3, r27, r26
       B mr r3, r24
```

## src/scene/memoryCard/iplMemoryCardManager getComment__Q33ipl5scene17MemoryCardManagerFUcsi

```text
src 0x1ec base 0x1ec insns 123/123
diffs 20: [10, 12, 14, 19, 20, 21, 23, 24, 45, 46, 48, 49, 51, 62, 66, 67, 86, 90, 91, 117]
    10 M mr r27, r3
       B mr r26, r3
    12 M slwi r28, r6, 7
       B slwi r27, r6, 7
    14 M mullw r30, r4, r0
       B mullw r29, r4, r0
    19 M mulli r29, r25, 0x15c
       B mulli r28, r25, 0x15c
    20 M add r0, r3, r30
       B add r0, r3, r29
    21 M add r3, r0, r29
       B add r3, r0, r28
    23 M add r26, r31, r28
       B add r30, r31, r27
    24 M mr r3, r26
       B mr r3, r30
    45 M mr r5, r4
       B mr r3, r4
    46 M li r3, 0
       B li r5, 0
    48 M stb r3, 0(r4)
       B stb r5, 0(r4)
    49 M addi r5, r5, -1
       B addi r3, r3, -1
    51 M lbz r0, 0(r5)
       B lbz r0, 0(r3)
    62 M mr r3, r26
       B mr r3, r30
    66 M add r3, r27, r30
       B add r3, r26, r29
    67 M add r0, r28, r29
       B add r0, r27, r28
    86 M mr r3, r26
       B mr r3, r30
    90 M add r3, r27, r30
       B add r3, r26, r29
    91 M add r0, r28, r29
       B add r0, r27, r28
   117 M add r3, r31, r28
       B add r3, r31, r27
```

## src/scene/memoryCard/iplMemoryCardManager create_banner__Q33ipl5scene17MemoryCardManagerFUcs

```text
src 0x1a8 base 0x1a8 insns 106/106
diffs 70: [5, 6, 9, 11, 14, 16, 17, 18, 19, 23, 24, 25, 26, 27, 32, 33, 34, 35, 36, 37]
     5 M mr r27, r3
       B mr r26, r3
     6 M mr r28, r4
       B mr r27, r4
     9 M mr r30, r3
       B mr r25, r3
    11 M mulli r4, r28, 0x7f0
       B mulli r4, r27, 0x7f0
    14 M add r4, r27, r4
       B add r4, r26, r4
    16 M lwz r29, 8(r4)
       B lwz r28, 8(r4)
    17 M mulli r0, r28, 0x5f4
       B mulli r0, r27, 0x5f4
    18 M mulli r4, r29, 0xc
       B mulli r4, r28, 0xc
    19 M add r0, r30, r0
       B add r0, r25, r0
    23 M mulli r25, r28, 0x1fc0
       B mulli r29, r27, 0x1fc0
    24 M slwi r26, r29, 6
       B slwi r30, r28, 6
    25 M add r0, r26, r3
       B add r0, r30, r3
    26 M add r30, r25, r0
       B add r4, r29, r0
    27 M lbzx r0, r25, r0
       B lbzx r0, r29, r0
    32 M lbz r0, 3(r30)
       B add r0, r3, r29
    33 M cmpwi r0, 5
       B add r25, r0, r30
    34 M bne 88
       B lbz r0, 3(r25)
    35 M lis r3, 1
       B cmpwi r0, 5
    36 M lwz r0, 0x14(r30)
       B bne 84
    37 M addi r3, r3, -0x535c
       B lis r3, 1
    38 M li r5, 0x60
       B lwz r0, 0x14(r25)
    39 M mullw r3, r28, r3
       B addi r3, r3, -0x535c
    40 M add r4, r30, r0
       B li r5, 0x60
    41 M li r6, 0x20
       B mullw r3, r27, r3
    42 M li r7, 5
       B add r4, r4, r0
    43 M li r8, 0
       B li r6, 0x20
    44 M li r9, 0
       B li r7, 5
    45 M mulli r0, r29, 0x15c
       B li r8, 0
    46 M add r3, r27, r3
       B li r9, 0
    47 M li r10, 0
       B add r3, r26, r3
    48 M add r3, r3, r0
       B li r10, 0
    49 M addi r25, r3, 0x110c
       B mulli r25, r28, 0x15c
    50 M mr r3, r25
       B addi r29, r3, 0x110c
    51 M bl 0
       B add r3, r29, r25
    52 M mr r3, r25
       B bl 0
    53 M li r4, 0
       B add r3, r29, r25
    54 M bl 0
       B li r4, 0
    55 M b 152
       B bl 0
    56 M cmpwi r0, 9
       B b 148
    57 M bne 144
       B cmpwi r0, 9
    58 M lis r3, 1
       B bne 140
    59 M li r0, 0
       B lis r3, 1
    60 M addi r3, r3, -0x535c
       B li r0, 0
    61 M stw r0, 8(r1)
       B addi r3, r3, -0x535c
    62 M mullw r23, r28, r3
       B stw r0, 8(r1)
    63 M li r5, 0x60
       B mullw r23, r27, r3
    64 M lwz r0, 0x14(r30)
       B li r5, 0x60
    65 M li r6, 0x20
       B lwz r0, 0x14(r25)
    66 M li r7, 9
       B li r6, 0x20
    67 M add r4, r30, r0
       B li r7, 9
    68 M add r3, r27, r23
       B add r4, r25, r0
    69 M li r8, 0
       B add r3, r26, r23
    70 M mulli r24, r29, 0x15c
       B li r8, 0
    71 M li r9, 0
       B mulli r24, r28, 0x15c
    72 M addi r22, r3, 0x110c
       B li r9, 0
    73 M li r10, 0
       B addi r22, r3, 0x110c
    74 M add r3, r22, r24
       B li r10, 0
    75 M bl 0
       B add r3, r22, r24
    76 M add r0, r31, r25
       B bl 0
    77 M add r4, r27, r23
       B add r0, r31, r29
    78 M add r3, r0, r26
       B add r4, r26, r23
    79 M li r5, 2
       B add r3, r0, r30
    80 M add r4, r4, r24
       B li r5, 2
    83 M li r6, 0x100
       B add r3, r23, r24
    84 M mr r3, r23
       B li r6, 0x100
    85 M add r4, r30, r0
       B add r4, r25, r0
    87 M mr r3, r23
       B add r3, r23, r24
    95 M mullw r3, r28, r0
       B mullw r3, r27, r0
    96 M mulli r0, r29, 0x15c
       B mulli r0, r28, 0x15c
    97 M add r3, r27, r3
       B add r3, r26, r3
```

## src/scene/memoryCard/iplMemoryCardManager getBlocks__Q33ipl5scene17MemoryCardManagerFUcs

```text
src 0x64 base 0x64 insns 25/25
diffs 9: [11, 12, 13, 14, 15, 16, 17, 18, 19]
    11 M addi r11, r1, 0x20
       B add r4, r29, r4
    12 M add r4, r29, r4
       B add r4, r4, r0
    13 M add r4, r4, r0
       B lwz r0, 8(r4)
    14 M lwz r0, 8(r4)
       B mulli r4, r30, 0x5f4
    15 M mulli r4, r30, 0x5f4
       B mulli r0, r0, 0xc
    16 M mulli r0, r0, 0xc
       B add r3, r3, r4
    17 M add r3, r3, r4
       B add r3, r3, r0
    18 M add r3, r3, r0
       B lhz r3, 2(r3)
    19 M lhz r3, 2(r3)
       B addi r11, r1, 0x20
```

## src/keyboard/tiZiString clearCandidates__Q39textinput8tistring6WithZiFv

```text
src 0x150 base 0x144 insns 84/81
--- insert mine 4:4 base 4:6
  B    4 lis r31, 0
  B    5 addi r31, r31, 0
--- replace mine 6:10 base 8:9
  M    6 lis r29, 0
  M    7 addi r29, r29, 0
  M    8 stw r28, 0x10(r1)
  M    9 mr r28, r3
  B    8 mr r29, r3
--- replace mine 12:13 base 11:12
  M   12 beq 256
  B   11 beq 252
--- replace mine 18:19 base 17:18
  M   18 addi r3, r29, 0
  B   17 addi r3, r31, 0
--- replace mine 20:21 base 19:20
  M   20 addi r3, r29, 0x200
  B   19 addi r3, r31, 0x200
--- replace mine 24:25 base 23:24
  M   24 addi r31, r29, 0x200
  B   23 addi r3, r31, 0x400
--- delete mine 26:27 base 25:25
  M   26 addi r3, r31, 0x200
--- replace mine 29:30 base 27:28
  M   29 addi r3, r31, 0x400
  B   27 addi r3, r31, 0x600
--- replace mine 33:34 base 31:32
  M   33 addi r3, r29, 0x800
  B   31 addi r3, r31, 0x800
--- replace mine 37:38 base 35:36
  M   37 addi r3, r28, 0x4c
  B   35 addi r3, r29, 0x4c
--- replace mine 41:43 base 39:41
  M   41 lwz r12, 0(r28)
  M   42 mr r3, r28
  B   39 lwz r12, 0(r29)
  B   40 mr r3, r29
--- replace mine 46:48 base 44:46
  M   46 addi r4, r31, 0x400
  M   47 addi r5, r29, 0
  B   44 addi r5, r31, 0
  B   45 addi r4, r31, 0x600
--- replace mine 52:64 base 50:62
  M   52 stb r3, 0x4c(r28)
  M   53 mr r3, r28
  M   54 stb r7, 0x4e(r28)
  M   55 stb r30, 0x4d(r28)
  M   56 stb r31, 0x4f(r28)
  M   57 stb r6, 0x50(r28)
  M   58 stw r5, 0x54(r28)
  M   59 stw r4, 0x64(r28)
  M   60 stb r0, 0x68(r28)
  M   61 stb r30, 0x58(r28)
  M   62 sth r30, 0x6a(r28)
  M   63 lwz r12, 0(r28)
  B   50 stb r3, 0x4c(r29)
  B   51 mr r3, r29
  B   52 stb r7, 0x4e(r29)
  B   53 stb r30, 0x4d(r29)
  B   54 stb r31, 0x4f(r29)
  B   55 stb r6, 0x50(r29)
  B   56 stw r5, 0x54(r29)
  B   57 stw r4, 0x64(r29)
  B   58 stb r0, 0x68(r29)
  B   59 stb r30, 0x58(r29)
  B   60 sth r30, 0x6a(r29)
  B   61 lwz r12, 0(r29)
--- replace mine 71:75 base 69:73
  M   71 stb r31, 0x4d(r28)
  M   72 stb r0, 0x4f(r28)
  M   73 lwz r4, 0x84(r28)
  M   74 addi r3, r28, 0x4c
  B   69 stb r31, 0x4d(r29)
  B   70 stb r0, 0x4f(r29)
  B   71 lwz r4, 0x84(r29)
  B   72 addi r3, r29, 0x4c
--- delete mine 80:81 base 78:78
  M   80 lwz r28, 0x10(r1)
```

## src/keyboard/tiZiString update__Q39textinput8tistring6WithZiFv

```text
src 0x6fc base 0x6f8 insns 447/446
--- replace mine 7:8 base 7:8
  M    7 mr r27, r3
  B    7 mr r28, r3
--- replace mine 10:15 base 10:13
  M   10 beq 1724
  M   11 li r28, 0
  M   12 addi r4, r31, 0x200
  M   13 stw r28, 0x98(r3)
  M   14 addi r30, r4, 0x400
  B   10 beq 1720
  B   11 li r30, 0
  B   12 stw r30, 0x98(r3)
--- replace mine 19:20 base 17:18
  M   19 lwz r12, 0(r27)
  B   17 lwz r12, 0(r28)
--- replace mine 21:22 base 19:20
  M   21 mr r3, r27
  B   19 mr r3, r28
--- replace mine 25:29 base 23:28
  M   25 addi r4, r31, 0
  M   26 li r6, 7
  M   27 li r26, 1
  M   28 li r5, 0x81
  B   23 addi r5, r31, 0
  B   24 addi r4, r31, 0x600
  B   25 li r7, 7
  B   26 li r27, 1
  B   27 li r6, 0x81
--- replace mine 30:48 base 29:47
  M   30 stb r3, 0x4c(r27)
  M   31 mr r3, r27
  M   32 stb r6, 0x4e(r27)
  M   33 stb r28, 0x4d(r27)
  M   34 stb r26, 0x4f(r27)
  M   35 stb r5, 0x50(r27)
  M   36 stw r4, 0x54(r27)
  M   37 stw r30, 0x64(r27)
  M   38 stb r0, 0x68(r27)
  M   39 stb r29, 0x58(r27)
  M   40 sth r28, 0x6a(r27)
  M   41 stw r28, 0x5c(r27)
  M   42 stb r28, 0x60(r27)
  M   43 stb r28, 0x6c(r27)
  M   44 stb r28, 0x6d(r27)
  M   45 stb r28, 0x6e(r27)
  M   46 stw r28, 0x70(r27)
  M   47 lwz r12, 0(r27)
  B   29 stb r3, 0x4c(r28)
  B   30 mr r3, r28
  B   31 stb r7, 0x4e(r28)
  B   32 stb r30, 0x4d(r28)
  B   33 stb r27, 0x4f(r28)
  B   34 stb r6, 0x50(r28)
  B   35 stw r5, 0x54(r28)
  B   36 stw r4, 0x64(r28)
  B   37 stb r0, 0x68(r28)
  B   38 stb r29, 0x58(r28)
  B   39 sth r30, 0x6a(r28)
  B   40 stw r30, 0x5c(r28)
  B   41 stb r30, 0x60(r28)
  B   42 stb r30, 0x6c(r28)
  B   43 stb r30, 0x6d(r28)
  B   44 stb r30, 0x6e(r28)
  B   45 stw r30, 0x70(r28)
  B   46 lwz r12, 0(r28)
--- replace mine 54:55 base 53:54
  M   54 lbz r0, 0xa8(r27)
  B   53 lbz r0, 0xa8(r28)
--- replace mine 56:57 base 55:56
  M   56 stb r26, 0x4d(r27)
  B   55 stb r27, 0x4d(r28)
--- replace mine 58:59 base 57:58
  M   58 stb r3, 0x4f(r27)
  B   57 stb r3, 0x4f(r28)
--- replace mine 60:61 base 59:60
  M   60 lbz r0, 0x50(r27)
  B   59 lbz r0, 0x50(r28)
--- replace mine 62:63 base 61:62
  M   62 stb r3, 0x4f(r27)
  B   61 stb r3, 0x4f(r28)
--- replace mine 64:65 base 63:64
  M   64 stb r0, 0x50(r27)
  B   63 stb r0, 0x50(r28)
--- replace mine 66:67 base 65:66
  M   66 stw r3, 0x5c(r27)
  B   65 stw r3, 0x5c(r28)
--- replace mine 68:69 base 67:68
  M   68 stb r3, 0x60(r27)
  B   67 stb r3, 0x60(r28)
--- replace mine 71:72 base 70:71
  M   71 lbz r0, 0x60(r27)
  B   70 lbz r0, 0x60(r28)
--- replace mine 74:76 base 73:75
  M   74 lwz r12, 0(r27)
  M   75 mr r3, r27
  B   73 lwz r12, 0(r28)
  B   74 mr r3, r28
--- replace mine 87:88 base 86:87
  M   87 lwz r0, 0xa4(r27)
  B   86 lwz r0, 0xa4(r28)
--- replace mine 90:92 base 89:91
  M   90 lwz r12, 0(r27)
  M   91 mr r3, r27
  B   89 lwz r12, 0(r28)
  B   90 mr r3, r28
--- replace mine 108:109 base 107:108
  M  108 stw r3, 0x8c(r27)
  B  107 stw r3, 0x8c(r28)
--- replace mine 110:111 base 109:110
  M  110 lwz r0, 0xa4(r27)
  B  109 lwz r0, 0xa4(r28)
--- replace mine 117:118 base 116:117
  M  117 lwz r3, 0x8c(r27)
  B  116 lwz r3, 0x8c(r28)
--- replace mine 119:121 base 118:120
  M  119 stw r0, 0x8c(r27)
  M  120 lwz r0, 0xa4(r27)
  B  118 stw r0, 0x8c(r28)
  B  119 lwz r0, 0xa4(r28)
--- replace mine 128:129 base 127:128
  M  128 lwz r3, 0x8c(r27)
  B  127 lwz r3, 0x8c(r28)
--- replace mine 130:132 base 129:131
  M  130 stw r0, 0x8c(r27)
  M  131 lwz r0, 0xa4(r27)
  B  129 stw r0, 0x8c(r28)
  B  130 lwz r0, 0xa4(r28)
--- replace mine 139:140 base 138:139
  M  139 lwz r3, 0x8c(r27)
  B  138 lwz r3, 0x8c(r28)
--- replace mine 141:143 base 140:142
  M  141 stw r0, 0x8c(r27)
  M  142 lwz r0, 0xa4(r27)
  B  140 stw r0, 0x8c(r28)
  B  141 lwz r0, 0xa4(r28)
--- replace mine 150:151 base 149:150
  M  150 lwz r3, 0x8c(r27)
  B  149 lwz r3, 0x8c(r28)
--- replace mine 152:154 base 151:153
  M  152 stw r0, 0x8c(r27)
  M  153 lwz r0, 0xa4(r27)
  B  151 stw r0, 0x8c(r28)
  B  152 lwz r0, 0xa4(r28)
--- replace mine 161:162 base 160:161
  M  161 lwz r3, 0x8c(r27)
  B  160 lwz r3, 0x8c(r28)
--- replace mine 163:164 base 162:164
  M  163 stw r0, 0x8c(r27)
  B  162 stw r0, 0x8c(r28)
  B  163 addi r4, r4, 2
--- delete mine 165:166 base 165:165
  M  165 addi r4, r4, 2
--- replace mine 168:170 base 167:169
  M  168 lwz r4, 0x84(r27)
  M  169 addi r3, r27, 0x4c
  B  167 lwz r4, 0x84(r28)
  B  168 addi r3, r28, 0x4c
--- replace mine 172:173 base 171:173
  M  172 addi r26, r31, 0x200
  B  171 addi r3, r31, 0x600
  B  172 addi r4, r31, 0x200
--- delete mine 174:176 base 174:174
  M  174 mr r4, r26
  M  175 addi r3, r26, 0x400
--- replace mine 177:179 base 175:177
  M  177 lwz r12, 0(r27)
  M  178 mr r3, r27
  B  175 lwz r12, 0(r28)
  B  176 mr r3, r28
--- replace mine 182:183 base 180:181
  M  182 lwz r12, 0(r27)
  B  180 lwz r12, 0(r28)
--- replace mine 184:185 base 182:183
  M  184 mr r3, r27
  B  182 mr r3, r28
--- replace mine 189:191 base 187:189
  M  189 lwz r4, 0x84(r27)
  M  190 addi r3, r27, 0x4c
  B  187 lwz r4, 0x84(r28)
  B  188 addi r3, r28, 0x4c
--- replace mine 192:195 base 190:349
  M  192 lwz r12, 0(r27)
  M  193 clrlwi r28, r3, 0x18
  M  194 mr r3, r27
  B  190 lwz r12, 0(r28)
  B  191 clrlwi r30, r3, 0x18
  B  192 mr r3, r28
  B  193 lwz r12, 0x104(r12)
  B  194 mtctr r12
  B  195 bctrl
  B  196 clrlwi r0, r3, 0x18
  B  197 cmplwi r0, 1
  B  198 bne 72
  B  199 cmplwi r30, 0x61
  B  200 bne 64
  B  201 addi r27, r31, 0x600
  B  202 li r3, 0x61
  B  203 addi r5, r27, 0x184
  B  204 li r0, 0xc7
  B  205 sth r3, 0x6a(r28)
  B  206 addi r3, r28, 0x4c
  B  207 lwz r4, 0x84(r28)
  B  208 stw r5, 0x64(r28)
  B  209 stb r0, 0x68(r28)
  B  210 bl 0
  B  211 li r0, 0
  B  212 clrlwi r3, r3, 0x18
  B  213 sth r0, 0x6a(r28)
  B  214 add r30, r30, r3
  B  215 stw r27, 0x64(r28)
  B  216 cmpwi r30, 0x28
  B  217 ble 8
  B  218 li r30, 0x28
  B  219 lwz r12, 0(r28)
  B  220 mr r3, r28
  B  221 lwz r12, 0x104(r12)
  B  222 mtctr r12
  B  223 bctrl
  B  224 clrlwi r0, r3, 0x18
  B  225 cmplwi r0, 1
  B  226 bne 300
  B  227 lbz r0, 0x79(r28)
  B  228 cmpwi r0, 0
  B  229 beq 288
  B  230 lbz r0, 0x6c(r28)
  B  231 li r3, 0
  B  232 stb r3, 0x79(r28)
  B  233 cmpwi r0, 0
  B  234 bne 268
  B  235 lwz r30, 0x7c(r28)
  B  236 addi r3, r31, 0x1c00
  B  237 bl 0
  B  238 cmpwi r30, 0
  B  239 clrlwi r4, r3, 0x18
  B  240 li r5, 0
  B  241 beq 200
  B  242 cmplwi r30, 8
  B  243 addi r6, r30, -8
  B  244 ble 120
  B  245 subf r3, r30, r4
  B  246 addi r0, r6, 7
  B  247 addi r7, r31, 0x1c00
  B  248 slwi r3, r3, 1
  B  249 srwi r0, r0, 3
  B  250 add r3, r7, r3
  B  251 mtctr r0
  B  252 cmplwi r6, 0
  B  253 ble 84
  B  254 lhz r0, 0(r3)
  B  255 addi r5, r5, 8
  B  256 sth r0, 0(r7)
  B  257 lhz r0, 2(r3)
  B  258 sth r0, 2(r7)
  B  259 lhz r0, 4(r3)
  B  260 sth r0, 4(r7)
  B  261 lhz r0, 6(r3)
  B  262 sth r0, 6(r7)
  B  263 lhz r0, 8(r3)
  B  264 sth r0, 8(r7)
  B  265 lhz r0, 0xa(r3)
  B  266 sth r0, 0xa(r7)
  B  267 lhz r0, 0xc(r3)
  B  268 sth r0, 0xc(r7)
  B  269 lhz r0, 0xe(r3)
  B  270 addi r3, r3, 0x10
  B  271 sth r0, 0xe(r7)
  B  272 addi r7, r7, 0x10
  B  273 bdnz -76
  B  274 subf r0, r30, r4
  B  275 slwi r6, r5, 1
  B  276 slwi r0, r0, 1
  B  277 addi r4, r31, 0x1c00
  B  278 add r3, r6, r0
  B  279 add r3, r4, r3
  B  280 subf r0, r5, r30
  B  281 add r4, r4, r6
  B  282 mtctr r0
  B  283 cmplw r5, r30
  B  284 bge 28
  B  285 lhz r0, 0(r3)
  B  286 addi r3, r3, 2
  B  287 addi r5, r5, 1
  B  288 sth r0, 0(r4)
  B  289 addi r4, r4, 2
  B  290 bdnz -20
  B  291 addi r3, r31, 0x1c00
  B  292 slwi r0, r5, 1
  B  293 li r4, 0
  B  294 sthx r4, r3, r0
  B  295 bl 0
  B  296 stb r3, 0x60(r28)
  B  297 addi r3, r28, 0x4c
  B  298 lwz r4, 0x84(r28)
  B  299 bl 0
  B  300 clrlwi r30, r3, 0x18
  B  301 cmpwi r30, 0
  B  302 bne 116
  B  303 lwz r12, 0(r28)
  B  304 mr r3, r28
  B  305 lwz r12, 0x104(r12)
  B  306 mtctr r12
  B  307 bctrl
  B  308 clrlwi r0, r3, 0x18
  B  309 cmplwi r0, 1
  B  310 beq 76
  B  311 lwz r12, 0(r28)
  B  312 mr r3, r28
  B  313 lwz r12, 0x104(r12)
  B  314 mtctr r12
  B  315 bctrl
  B  316 clrlwi r0, r3, 0x18
  B  317 cmplwi r0, 0x12
  B  318 bne 28
  B  319 lwz r12, 0(r28)
  B  320 mr r3, r28
  B  321 lwz r12, 0x5c(r12)
  B  322 mtctr r12
  B  323 bctrl
  B  324 b 464
  B  325 mr r3, r28
  B  326 mr r4, r29
  B  327 bl 0
  B  328 mr r30, r3
  B  329 cmpwi r30, 0
  B  330 beq 440
  B  331 addi r3, r31, 0x800
  B  332 li r4, 0
  B  333 li r5, 0x1400
  B  334 bl 0
  B  335 li r0, 0
  B  336 cmpwi r29, 0
  B  337 stw r0, 0x8c(r28)
  B  338 bne 16
  B  339 lbz r0, 0x60(r28)
  B  340 cmpwi r0, 0
  B  341 beq 396
  B  342 lwz r29, 0x64(r28)
  B  343 addi r26, r31, 0x800
  B  344 li r31, 0
  B  345 li r27, 0
  B  346 b 368
  B  347 lwz r12, 0(r28)
  B  348 mr r3, r28
--- replace mine 201:287 base 355:358
  M  201 cmplwi r28, 0x61
  M  202 bne 60
  M  203 addi r5, r26, 0x584
  M  204 li r3, 0x61
  M  205 li r0, 0xc7
  M  206 sth r3, 0x6a(r27)
  M  207 lwz r4, 0x84(r27)
  M  208 addi r3, r27, 0x4c
  M  209 stw r5, 0x64(r27)
  M  210 stb r0, 0x68(r27)
  M  211 bl 0
  M  212 li r0, 0
  M  213 clrlwi r3, r3, 0x18
  M  214 sth r0, 0x6a(r27)
  M  215 addi r28, r3, 0x61
  M  216 stw r30, 0x64(r27)
  M  217 cmpwi r28, 0x28
  M  218 ble 8
  M  219 li r28, 0x28
  M  220 lwz r12, 0(r27)
  M  221 mr r3, r27
  M  222 lwz r12, 0x104(r12)
  M  223 mtctr r12
  M  224 bctrl
  M  225 clrlwi r0, r3, 0x18
  M  226 cmplwi r0, 1
  M  227 bne 292
  M  228 lbz r0, 0x79(r27)
  M  229 cmpwi r0, 0
  M  230 beq 280
  M  231 lbz r0, 0x60(r27)
  M  232 li r3, 0
  M  233 stb r3, 0x79(r27)
  M  234 cmpwi r0, 0
  M  235 bne 260
  M  236 lwz r28, 0x7c(r27)
  M  237 addi r3, r31, 0x1c00
  M  238 bl 0
  M  239 rlwinm r0, r3, 1, 0x17, 0x1e
  M  240 addi r5, r31, 0x1c00
  M  241 cmpwi r28, 0
  M  242 slwi r3, r28, 1
  M  243 add r0, r5, r0
  M  244 li r6, 0
  M  245 subf r7, r3, r0
  M  246 beq 176
  M  247 cmplwi r28, 8
  M  248 addi r3, r28, -8
  M  249 ble 108
  M  250 addi r0, r3, 7
  M  251 mr r4, r7
  M  252 srwi r0, r0, 3
  M  253 mtctr r0
  M  254 cmplwi r3, 0
  M  255 ble 84
  M  256 lhz r0, 0(r4)
  M  257 addi r6, r6, 8
  M  258 sth r0, 0(r5)
  M  259 lhz r0, 2(r4)
  M  260 sth r0, 2(r5)
  M  261 lhz r0, 4(r4)
  M  262 sth r0, 4(r5)
  M  263 lhz r0, 6(r4)
  M  264 sth r0, 6(r5)
  M  265 lhz r0, 8(r4)
  M  266 sth r0, 8(r5)
  M  267 lhz r0, 0xa(r4)
  M  268 sth r0, 0xa(r5)
  M  269 lhz r0, 0xc(r4)
  M  270 sth r0, 0xc(r5)
  M  271 lhz r0, 0xe(r4)
  M  272 addi r4, r4, 0x10
  M  273 sth r0, 0xe(r5)
  M  274 addi r5, r5, 0x10
  M  275 bdnz -76
  M  276 slwi r5, r6, 1
  M  277 addi r3, r31, 0x1c00
  M  278 subf r0, r6, r28
  M  279 add r4, r7, r5
  M  280 add r3, r3, r5
  M  281 mtctr r0
  M  282 cmplw r6, r28
  M  283 bge 28
  M  284 lhz r0, 0(r4)
  M  285 addi r4, r4, 2
  M  286 addi r6, r6, 1
  B  355 mr r3, r26
  B  356 li r4, 0
  B  357 b 20
--- replace mine 289:360 base 360:361
  M  289 bdnz -20
  M  290 addi r3, r31, 0x1c00
  M  291 slwi r0, r6, 1
  M  292 li r4, 0
  M  293 sthx r4, r3, r0
  M  294 bl 0
  M  295 stb r3, 0x60(r27)
  M  296 addi r3, r27, 0x4c
  M  297 lwz r4, 0x84(r27)
  M  298 bl 0
  M  299 clrlwi r28, r3, 0x18
  M  300 cmpwi r28, 0
  M  301 bne 116
  M  302 lwz r12, 0(r27)
  M  303 mr r3, r27
  M  304 lwz r12, 0x104(r12)
  M  305 mtctr r12
  M  306 bctrl
  M  307 clrlwi r0, r3, 0x18
  M  308 cmplwi r0, 1
  M  309 beq 76
  M  310 lwz r12, 0(r27)
  M  311 mr r3, r27
  M  312 lwz r12, 0x104(r12)
  M  313 mtctr r12
  M  314 bctrl
  M  315 clrlwi r0, r3, 0x18
  M  316 cmplwi r0, 0x12
  M  317 bne 28
  M  318 lwz r12, 0(r27)
  M  319 mr r3, r27
  M  320 lwz r12, 0x5c(r12)
  M  321 mtctr r12
  M  322 bctrl
  M  323 b 472
  M  324 mr r3, r27
  M  325 mr r4, r29
  M  326 bl 0
  M  327 mr r28, r3
  M  328 cmpwi r28, 0
  M  329 beq 448
  M  330 addi r3, r31, 0x800
  M  331 li r4, 0
  M  332 li r5, 0x1400
  M  333 bl 0
  M  334 li r0, 0
  M  335 cmpwi r29, 0
  M  336 stw r0, 0x8c(r27)
  M  337 bne 16
  M  338 lbz r0, 0x60(r27)
  M  339 cmpwi r0, 0
  M  340 beq 404
  M  341 lwz r29, 0x64(r27)
  M  342 addi r30, r31, 0x800
  M  343 li r31, 0
  M  344 li r26, 0
  M  345 b 376
  M  346 lwz r12, 0(r27)
  M  347 mr r3, r27
  M  348 lwz r12, 0x104(r12)
  M  349 mtctr r12
  M  350 bctrl
  M  351 clrlwi r0, r3, 0x18
  M  352 cmplwi r0, 1
  M  353 bne 68
  M  354 mr r4, r30
  M  355 li r3, 0
  M  356 b 20
  M  357 sth r0, 0(r4)
  M  358 addi r4, r4, 2
  M  359 addi r3, r3, 1
  B  360 addi r4, r4, 1
--- replace mine 366:367 base 367:368
  M  366 slwi r0, r3, 1
  B  367 slwi r0, r4, 1
--- replace mine 368:371 base 369:372
  M  368 sthx r26, r30, r0
  M  369 b 136
  M  370 lwz r0, 0x9c(r27)
  B  369 sthx r27, r26, r0
  B  370 b 132
  B  371 lwz r0, 0x9c(r28)
--- replace mine 375:380 base 376:381
  M  375 sth r0, 0(r30)
  M  376 sth r26, 2(r30)
  M  377 b 104
  M  378 lwz r12, 0(r27)
  M  379 mr r3, r27
  B  376 sth r0, 0(r26)
  B  377 sth r27, 2(r26)
  B  378 b 100
  B  379 lwz r12, 0(r28)
  B  380 mr r3, r28
--- replace mine 385:390 base 386:389
  M  385 bne 44
  M  386 mr r3, r30
  M  387 b 20
  M  388 lhz r0, 0(r29)
  M  389 addi r29, r29, 2
  B  386 bne 40
  B  387 mr r3, r26
  B  388 b 16
--- insert mine 392:392 base 391:392
  B  391 addi r29, r29, 2
--- replace mine 394:395 base 394:395
  M  394 bge -24
  B  394 bge -20
--- replace mine 396:399 base 396:399
  M  396 lwz r6, 0x84(r27)
  M  397 mr r3, r30
  M  398 addi r4, r27, 0x4c
  B  396 lwz r6, 0x84(r28)
  B  397 mr r3, r26
  B  398 addi r4, r28, 0x4c
--- replace mine 402:406 base 402:406
  M  402 beq 140
  M  403 lwz r3, 0x8c(r27)
  M  404 mr r24, r30
  M  405 li r25, 0
  B  402 beq 136
  B  403 lwz r3, 0x8c(r28)
  B  404 mr r25, r26
  B  405 li r24, 0
--- replace mine 407:413 base 407:413
  M  407 stw r0, 0x8c(r27)
  M  408 b 104
  M  409 lwz r0, 0xa0(r27)
  M  410 cmpwi r0, 1
  M  411 beq 32
  M  412 bge 16
  B  407 stw r0, 0x8c(r28)
  B  408 b 100
  B  409 lwz r0, 0xa0(r28)
  B  410 cmpwi r0, 2
  B  411 beq 40
  B  412 bge 76
--- replace mine 414:419 base 414:418
  M  414 bge 44
  M  415 b 68
  M  416 cmpwi r0, 3
  M  417 bge 60
  M  418 b 16
  B  414 beq 40
  B  415 bge 12
  B  416 b 60
  B  417 b 56
--- replace mine 420:421 base 419:420
  M  420 sth r3, 0(r24)
  B  419 sth r3, 0(r25)
--- replace mine 423:424 base 422:423
  M  423 sth r3, 0(r24)
  B  422 sth r3, 0(r25)
--- replace mine 425:426 base 424:425
  M  425 cmpwi r25, 0
  B  424 cmpwi r24, 0
--- replace mine 428:429 base 427:428
  M  428 sth r3, 0(r24)
  B  427 sth r3, 0(r25)
--- replace mine 431:435 base 430:434
  M  431 sth r3, 0(r24)
  M  432 addi r25, r25, 1
  M  433 addi r24, r24, 2
  M  434 lhz r3, 0(r24)
  B  430 sth r3, 0(r25)
  B  431 addi r25, r25, 2
  B  432 addi r24, r24, 1
  B  433 lhz r3, 0(r25)
--- replace mine 436:438 base 435:437
  M  436 bne -108
  M  437 addi r30, r30, 0x80
  B  435 bne -104
  B  436 addi r26, r26, 0x80
--- replace mine 439:441 base 438:440
  M  439 cmpw r31, r28
  M  440 blt -376
  B  438 cmpw r31, r30
  B  439 blt -368
```

## src/keyboard/tiZiString setElementBuffer__Q39textinput8tistring6WithZiFv

```text
src 0x104 base 0x104 insns 65/65
diffs 22: [5, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 20, 29, 36, 46, 49, 50, 51, 52]
     5 M lis r30, 0
       B lis r31, 0
     7 M addi r3, r30, 0
       B addi r31, r31, 0
     8 M li r29, 0
       B li r28, 0
     9 M li r4, 0
       B addi r3, r31, 0
    10 M li r5, 0x1fe
       B li r4, 0
    11 M bl 0
       B li r5, 0x1fe
    12 M lis r31, 0
       B bl 0
    13 M li r4, 0
       B addi r3, r31, 0x400
    14 M addi r31, r31, 0
       B li r4, 0
    16 M addi r3, r31, 0x200
       B bl 0
    17 M bl 0
       B addi r30, r31, 0
    18 M addi r28, r30, 0
       B addi r31, r31, 0x200
    20 M sthx r3, r28, r30
       B sthx r3, r30, r29
    29 M lhzx r3, r28, r30
       B lhzx r3, r30, r29
    36 M sthx r0, r28, r30
       B sthx r0, r30, r29
    46 M lhzx r3, r28, r30
       B lhzx r3, r30, r29
    49 M sthx r0, r28, r30
       B sthx r0, r30, r29
    50 M addi r29, r29, 1
       B addi r28, r28, 1
    51 M rlwinm r30, r29, 1, 0xf, 0x1e
       B rlwinm r29, r28, 1, 0xf, 0x1e
    52 M lhzx r3, r31, r30
       B lhzx r3, r31, r29
    55 M clrlwi r0, r29, 0x10
       B clrlwi r0, r28, 0x10
    59 M mr r3, r29
       B mr r3, r28
```

## src/keyboard/tiZiString setCurrentWord__Q39textinput8tistring6WithZiFPCw

```text
src 0xdc base 0xe0 insns 55/56
--- replace mine 13:14 base 13:14
  M   13 li r8, 0
  B   13 li r9, 0
--- replace mine 15:16 base 15:16
  M   15 cmplwi r8, 0x3f
  B   15 cmplwi r9, 0x3f
--- replace mine 18:19 base 18:19
  M   18 slwi r0, r8, 1
  B   18 slwi r0, r9, 1
--- replace mine 24:25 base 24:25
  M   24 addi r8, r8, 1
  B   24 addi r9, r9, 1
--- replace mine 30:35 base 30:36
  M   30 lis r6, 0
  M   31 mr r7, r4
  M   32 addi r6, r6, 0
  M   33 slwi r5, r8, 1
  M   34 li r9, 0
  B   30 lis r7, 0
  B   31 mr r8, r4
  B   32 addi r7, r7, 0
  B   33 slwi r6, r9, 1
  B   34 li r10, 0
  B   35 li r5, 0
--- replace mine 36:37 base 37:38
  M   36 lhz r0, 0(r7)
  B   37 lhzx r0, r4, r5
--- replace mine 38:41 base 39:43
  M   38 addi r8, r8, 1
  M   39 addi r4, r4, 2
  M   40 sthx r0, r6, r5
  B   39 addi r8, r8, 2
  B   40 addi r10, r10, 1
  B   41 sthx r0, r7, r6
  B   42 addi r6, r6, 2
--- replace mine 42:44 base 44:45
  M   42 addi r7, r7, 2
  M   43 lhz r0, 0(r4)
  B   44 lhz r0, 0(r8)
--- replace mine 46:47 base 47:48
  M   46 cmplwi r8, 0x3f
  B   47 cmplwi r9, 0x3f
--- replace mine 49:50 base 50:51
  M   49 slwi r0, r8, 1
  B   50 slwi r0, r9, 1
--- replace mine 53:54 base 54:55
  M   53 stw r9, 0x7c(r3)
  B   54 stw r10, 0x7c(r3)
```

## libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_exif_parse

```text
src 0x350 base 0x350 insns 212/212
diffs 46: [7, 27, 28, 30, 31, 32, 34, 61, 69, 70, 72, 73, 74, 76, 77, 79, 80, 82, 86, 89]
     7 M mr r27, r3
       B mr r30, r3
    27 M lbz r5, 3(r3)
       B lbz r6, 3(r3)
    28 M lbz r6, 2(r3)
       B lbz r5, 2(r3)
    30 M rlwimi r6, r5, 8, 0x10, 0x17
       B rlwimi r5, r6, 8, 0x10, 0x17
    31 M rlwinm r0, r6, 8, 0x10, 0x17
       B rlwinm r0, r5, 8, 0x10, 0x17
    32 M rlwimi r0, r6, 0x18, 0x18, 0x1f
       B rlwimi r0, r5, 0x18, 0x18, 0x1f
    34 M clrlwi r0, r6, 0x10
       B clrlwi r0, r5, 0x10
    61 M add r30, r3, r5
       B add r27, r3, r5
    69 M lbz r3, 1(r30)
       B lbz r4, 1(r27)
    70 M lbz r4, 0(r30)
       B lbz r3, 0(r27)
    72 M rlwimi r4, r3, 8, 0x10, 0x17
       B rlwimi r3, r4, 8, 0x10, 0x17
    73 M rlwinm r0, r4, 8, 0x10, 0x17
       B rlwinm r0, r3, 8, 0x10, 0x17
    74 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r0, r3, 0x18, 0x18, 0x1f
    76 M clrlwi r0, r4, 0x10
       B clrlwi r0, r3, 0x10
    77 M clrlwi r26, r0, 0x10
       B clrlwi r23, r0, 0x10
    79 M mulli r24, r26, 0xc
       B mulli r26, r23, 0xc
    80 M addi r30, r30, 2
       B addi r27, r27, 2
    82 M cmpw r25, r24
       B cmpw r25, r26
    86 M li r23, 0
       B li r24, 0
    89 M mr r5, r30
       B mr r5, r27
    92 M addi r30, r30, 0xc
       B addi r27, r27, 0xc
    93 M addi r23, r23, 1
       B addi r24, r24, 1
    94 M clrlwi r0, r23, 0x10
       B clrlwi r0, r24, 0x10
    95 M cmplw r0, r26
       B cmplw r0, r23
    97 M subf r0, r24, r25
       B subf r0, r26, r25
   104 M lbz r3, 1(r30)
       B lbz r3, 1(r27)
   106 M lbz r4, 2(r30)
       B lbz r4, 2(r27)
   107 M lbz r5, 0(r30)
       B lbz r5, 0(r27)
   109 M lbz r0, 3(r30)
       B lbz r0, 3(r27)
   128 M add r26, r27, r3
       B add r26, r30, r3
   136 M lbz r3, 1(r26)
       B lbz r4, 1(r26)
   137 M lbz r4, 0(r26)
       B lbz r3, 0(r26)
   139 M rlwimi r4, r3, 8, 0x10, 0x17
       B rlwimi r3, r4, 8, 0x10, 0x17
   140 M rlwinm r0, r4, 8, 0x10, 0x17
       B rlwinm r0, r3, 8, 0x10, 0x17
   141 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r0, r3, 0x18, 0x18, 0x1f
   143 M clrlwi r0, r4, 0x10
       B clrlwi r0, r3, 0x10
   144 M clrlwi r30, r0, 0x10
       B clrlwi r27, r0, 0x10
   146 M mulli r0, r30, 0xc
       B mulli r0, r27, 0xc
   162 M cmplw r0, r30
       B cmplw r0, r27
   170 M add r26, r27, r3
       B add r26, r30, r3
   178 M lbz r3, 1(r26)
       B lbz r4, 1(r26)
   179 M lbz r4, 0(r26)
       B lbz r3, 0(r26)
   181 M rlwimi r4, r3, 8, 0x10, 0x17
       B rlwimi r3, r4, 8, 0x10, 0x17
   182 M rlwinm r0, r4, 8, 0x10, 0x17
       B rlwinm r0, r3, 8, 0x10, 0x17
   183 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r0, r3, 0x18, 0x18, 0x1f
   185 M clrlwi r0, r4, 0x10
       B clrlwi r0, r3, 0x10
```

## libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD0_tag_parse

```text
src 0x784 base 0x784 insns 481/481
diffs 446: [0, 2, 3, 4, 5, 7, 10, 11, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 23, 24]
     0 M lbz r0, 1(r5)
       B lbz r6, 1(r5)
     2 M lbz r7, 0(r5)
       B lbz r0, 0(r5)
     3 M rlwimi r7, r0, 8, 0x10, 0x17
       B rlwimi r0, r6, 8, 0x10, 0x17
     4 M rlwinm r6, r7, 8, 0x10, 0x17
       B rlwinm r7, r0, 8, 0x10, 0x17
     5 M rlwimi r6, r7, 0x18, 0x18, 0x1f
       B rlwimi r7, r0, 0x18, 0x18, 0x1f
     7 M clrlwi r6, r7, 0x10
       B clrlwi r7, r0, 0x10
    10 M lbz r7, 2(r5)
       B lbz r6, 2(r5)
    11 M rlwimi r7, r0, 8, 0x10, 0x17
       B clrlwi r7, r7, 0x10
    12 M rlwinm r8, r7, 8, 0x10, 0x17
       B rlwimi r6, r0, 8, 0x10, 0x17
    13 M rlwimi r8, r7, 0x18, 0x18, 0x1f
       B rlwinm r0, r6, 8, 0x10, 0x17
    14 M bne 8
       B rlwimi r0, r6, 0x18, 0x18, 0x1f
    15 M clrlwi r8, r7, 0x10
       B bne 8
    16 M clrlwi r7, r6, 0x10
       B clrlwi r0, r6, 0x10
    18 M bge 96
       B clrlwi r8, r0, 0x10
    19 M cmpwi r7, 0x11b
       B bge 100
    20 M beq 508
       B cmpwi r7, 0x11b
    21 M bge 48
       B beq 512
    22 M cmpwi r7, 0x111
       B bge 52
    23 M beqlr
       B cmpwi r7, 0x111
    24 M bge 16
       B beqlr
    25 M cmpwi r7, 0x103
       B bge 20
    26 M beqlr
       B cmpwi r7, 0x103
    27 M blr
       B beqlr
    28 M cmpwi r7, 0x11a
       B bltlr
    29 M bge 212
       B blr
    30 M cmpwi r7, 0x113
       B cmpwi r7, 0x11a
    31 M bgelr
       B bge 212
    32 M b 160
       B cmpwi r7, 0x113
    33 M cmpwi r7, 0x12d
       B bgelr
    34 M beq 752
       B b 160
    35 M bge 16
       B cmpwi r7, 0x12d
    36 M cmpwi r7, 0x128
       B beq 752
    37 M beq 700
       B bge 16
    38 M blr
       B cmpwi r7, 0x128
    39 M cmpwi r7, 0x132
       B beq 700
    40 M beq 988
       B blr
    41 M blr
       B cmpwi r7, 0x132
    42 M lis r6, 1
       B beq 988
    43 M addi r0, r6, -0x6eff
       B blr
    44 M cmpw r7, r0
       B lis r6, 1
    45 M beq 1368
       B addi r0, r6, -0x6eff
    46 M bge 52
       B cmpw r7, r0
    47 M addi r0, r6, -0x7897
       B beq 1368
    48 M cmpw r7, r0
       B bge 52
    49 M beq 1248
       B addi r0, r6, -0x7897
    50 M bge 20
       B cmpw r7, r0
    51 M cmpwi r7, 0x213
       B beq 1248
    52 M beq 1196
       B bge 20
    53 M bgelr
       B cmpwi r7, 0x213
    54 M blr
       B beq 1196
    55 M addi r0, r6, -0x7000
       B bgelr
    56 M cmpw r7, r0
       B blr
    57 M beq 1284
       B addi r0, r6, -0x7000
    58 M blr
       B cmpw r7, r0
    59 M addi r0, r6, -0x5ffe
       B beq 1284
    60 M cmpw r7, r0
       B blr
    61 M beq 1416
       B addi r0, r6, -0x5ffe
    62 M bge 24
       B cmpw r7, r0
    63 M addi r0, r6, -0x6000
       B beq 1416
    64 M cmpw r7, r0
       B bge 24
    65 M beq 1324
       B addi r0, r6, -0x6000
    66 M bge 1356
       B cmpw r7, r0
    67 M blr
       B beq 1324
    68 M addi r0, r6, -0x5ffc
       B bge 1356
    69 M cmpw r7, r0
       B blr
    70 M bgelr
       B addi r0, r6, -0x5ffc
    71 M b 1508
       B cmpw r7, r0
    72 M lbz r0, 9(r5)
       B bgelr
    73 M cmplwi r4, 0x4949
       B b 1504
    74 M lbz r4, 8(r5)
       B lbz r0, 9(r5)
    75 M rlwimi r4, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
    76 M rlwinm r0, r4, 8, 0x10, 0x17
       B lbz r4, 8(r5)
    77 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r4, r0, 8, 0x10, 0x17
    78 M bne 8
       B rlwinm r0, r4, 8, 0x10, 0x17
    79 M clrlwi r0, r4, 0x10
       B rlwimi r0, r4, 0x18, 0x18, 0x1f
    80 M sth r0, 0xc(r3)
       B bne 8
    81 M blr
       B clrlwi r0, r4, 0x10
    82 M lbz r0, 9(r5)
       B sth r0, 0xc(r3)
    83 M cmplwi r4, 0x4949
       B blr
    84 M lbz r7, 8(r5)
       B lbz r0, 9(r5)
    85 M rlwimi r7, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
    86 M lbz r6, 0xa(r5)
       B lbz r7, 8(r5)
    87 M lbz r0, 0xb(r5)
       B rlwimi r7, r0, 8, 0x10, 0x17
    88 M rlwimi r7, r6, 0x10, 8, 0xf
       B lbz r6, 0xa(r5)
    89 M rlwimi r7, r0, 0x18, 0, 7
       B lbz r0, 0xb(r5)
    90 M bne 12
       B rlwimi r7, r6, 0x10, 8, 0xf
    91 M mr r6, r7
       B rlwimi r7, r0, 0x18, 0, 7
    92 M b 20
       B bne 12
    93 M rlwinm r6, r7, 0x18, 0x10, 0x17
       B mr r8, r7
    94 M rlwimi r6, r7, 8, 0x18, 0x1f
       B b 20
    95 M rlwimi r6, r7, 8, 8, 0xf
       B rlwinm r8, r7, 0x18, 0x10, 0x17
    96 M rlwimi r6, r7, 0x18, 0, 7
       B rlwimi r8, r7, 8, 0x18, 0x1f
    97 M lwz r0, 0x674(r3)
       B rlwimi r8, r7, 8, 8, 0xf
    98 M add r8, r0, r6
       B rlwimi r8, r7, 0x18, 0, 7
    99 M cmplw r0, r8
       B lwz r0, 0x674(r3)
   100 M bgtlr
       B add r6, r0, r8
   101 M lwz r5, 0x678(r3)
       B cmplw r0, r6
   102 M addi r0, r5, -4
       B bgtlr
   103 M cmplw r8, r0
       B lwz r5, 0x678(r3)
   104 M bgtlr
       B addi r0, r5, -4
   105 M lbz r0, 1(r8)
       B cmplw r6, r0
   106 M cmplwi r4, 0x4949
       B bgtlr
   107 M lbz r7, 0(r8)
       B lbz r0, 1(r6)
   108 M rlwimi r7, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   109 M lbz r5, 2(r8)
       B lbz r7, 0(r6)
   110 M lbz r0, 3(r8)
       B rlwimi r7, r0, 8, 0x10, 0x17
   111 M rlwimi r7, r5, 0x10, 8, 0xf
       B lbz r5, 2(r6)
   112 M rlwimi r7, r0, 0x18, 0, 7
       B lbz r0, 3(r6)
   113 M bne 12
       B rlwimi r7, r5, 0x10, 8, 0xf
   114 M mr r0, r7
       B rlwimi r7, r0, 0x18, 0, 7
   115 M b 20
       B bne 12
   116 M rlwinm r0, r7, 0x18, 0x10, 0x17
       B mr r0, r7
   117 M rlwimi r0, r7, 8, 0x18, 0x1f
       B b 20
   118 M rlwimi r0, r7, 8, 8, 0xf
       B rlwinm r0, r7, 0x18, 0x10, 0x17
   119 M rlwimi r0, r7, 0x18, 0, 7
       B rlwimi r0, r7, 8, 0x18, 0x1f
   120 M lwz r5, 0x674(r3)
       B rlwimi r0, r7, 8, 8, 0xf
   121 M stw r0, 0x10(r3)
       B rlwimi r0, r7, 0x18, 0, 7
   122 M add r6, r5, r6
       B lwz r7, 0x674(r3)
   123 M addi r6, r6, 4
       B stw r0, 0x10(r3)
   124 M cmplw r5, r6
       B add r5, r8, r7
   125 M bgtlr
       B addi r6, r5, 4
   126 M lwz r5, 0x678(r3)
       B cmplw r7, r6
   127 M addi r0, r5, -4
       B bgtlr
   128 M cmplw r6, r0
       B lwz r5, 0x678(r3)
   129 M bgtlr
       B addi r0, r5, -4
   130 M lbz r0, 1(r6)
       B cmplw r6, r0
   131 M cmplwi r4, 0x4949
       B bgtlr
   132 M lbz r5, 0(r6)
       B lbz r0, 1(r6)
   133 M rlwimi r5, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   134 M lbz r4, 2(r6)
       B lbz r5, 0(r6)
   135 M lbz r0, 3(r6)
       B rlwimi r5, r0, 8, 0x10, 0x17
   136 M rlwimi r5, r4, 0x10, 8, 0xf
       B lbz r4, 2(r6)
   137 M rlwimi r5, r0, 0x18, 0, 7
       B lbz r0, 3(r6)
   138 M bne 12
       B rlwimi r5, r4, 0x10, 8, 0xf
   139 M mr r0, r5
       B rlwimi r5, r0, 0x18, 0, 7
   140 M b 20
       B bne 12
   141 M rlwinm r0, r5, 0x18, 0x10, 0x17
       B mr r0, r5
   142 M rlwimi r0, r5, 8, 0x18, 0x1f
       B b 20
   143 M rlwimi r0, r5, 8, 8, 0xf
       B rlwinm r0, r5, 0x18, 0x10, 0x17
   144 M rlwimi r0, r5, 0x18, 0, 7
       B rlwimi r0, r5, 8, 0x18, 0x1f
   145 M stw r0, 0x14(r3)
       B rlwimi r0, r5, 8, 8, 0xf
   146 M blr
       B rlwimi r0, r5, 0x18, 0, 7
   147 M lbz r0, 9(r5)
       B stw r0, 0x14(r3)
   148 M cmplwi r4, 0x4949
       B blr
   149 M lbz r7, 8(r5)
       B lbz r0, 9(r5)
   150 M rlwimi r7, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   151 M lbz r6, 0xa(r5)
       B lbz r7, 8(r5)
   152 M lbz r0, 0xb(r5)
       B rlwimi r7, r0, 8, 0x10, 0x17
   153 M rlwimi r7, r6, 0x10, 8, 0xf
       B lbz r6, 0xa(r5)
   154 M rlwimi r7, r0, 0x18, 0, 7
       B lbz r0, 0xb(r5)
   155 M bne 12
       B rlwimi r7, r6, 0x10, 8, 0xf
   156 M mr r6, r7
       B rlwimi r7, r0, 0x18, 0, 7
   157 M b 20
       B bne 12
   158 M rlwinm r6, r7, 0x18, 0x10, 0x17
       B mr r8, r7
   159 M rlwimi r6, r7, 8, 0x18, 0x1f
       B b 20
   160 M rlwimi r6, r7, 8, 8, 0xf
       B rlwinm r8, r7, 0x18, 0x10, 0x17
   161 M rlwimi r6, r7, 0x18, 0, 7
       B rlwimi r8, r7, 8, 0x18, 0x1f
   162 M lwz r0, 0x674(r3)
       B rlwimi r8, r7, 8, 8, 0xf
   163 M add r8, r0, r6
       B rlwimi r8, r7, 0x18, 0, 7
   164 M cmplw r0, r8
       B lwz r0, 0x674(r3)
   165 M bgtlr
       B add r6, r0, r8
   166 M lwz r5, 0x678(r3)
       B cmplw r0, r6
   167 M addi r0, r5, -4
       B bgtlr
   168 M cmplw r8, r0
       B lwz r5, 0x678(r3)
   169 M bgtlr
       B addi r0, r5, -4
   170 M lbz r0, 1(r8)
       B cmplw r6, r0
   171 M cmplwi r4, 0x4949
       B bgtlr
   172 M lbz r7, 0(r8)
       B lbz r0, 1(r6)
   173 M rlwimi r7, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   174 M lbz r5, 2(r8)
       B lbz r7, 0(r6)
   175 M lbz r0, 3(r8)
       B rlwimi r7, r0, 8, 0x10, 0x17
   176 M rlwimi r7, r5, 0x10, 8, 0xf
       B lbz r5, 2(r6)
   177 M rlwimi r7, r0, 0x18, 0, 7
       B lbz r0, 3(r6)
   178 M bne 12
       B rlwimi r7, r5, 0x10, 8, 0xf
   179 M mr r0, r7
       B rlwimi r7, r0, 0x18, 0, 7
   180 M b 20
       B bne 12
   181 M rlwinm r0, r7, 0x18, 0x10, 0x17
       B mr r0, r7
   182 M rlwimi r0, r7, 8, 0x18, 0x1f
       B b 20
   183 M rlwimi r0, r7, 8, 8, 0xf
       B rlwinm r0, r7, 0x18, 0x10, 0x17
   184 M rlwimi r0, r7, 0x18, 0, 7
       B rlwimi r0, r7, 8, 0x18, 0x1f
   185 M lwz r5, 0x674(r3)
       B rlwimi r0, r7, 8, 8, 0xf
   186 M stw r0, 0x18(r3)
       B rlwimi r0, r7, 0x18, 0, 7
   187 M add r6, r5, r6
       B lwz r7, 0x674(r3)
   188 M addi r6, r6, 4
       B stw r0, 0x18(r3)
   189 M cmplw r5, r6
       B add r5, r8, r7
   190 M bgtlr
       B addi r6, r5, 4
   191 M lwz r5, 0x678(r3)
       B cmplw r7, r6
   192 M addi r0, r5, -4
       B bgtlr
   193 M cmplw r6, r0
       B lwz r5, 0x678(r3)
   194 M bgtlr
       B addi r0, r5, -4
   195 M lbz r0, 1(r6)
       B cmplw r6, r0
   196 M cmplwi r4, 0x4949
       B bgtlr
   197 M lbz r5, 0(r6)
       B lbz r0, 1(r6)
   198 M rlwimi r5, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   199 M lbz r4, 2(r6)
       B lbz r5, 0(r6)
   200 M lbz r0, 3(r6)
       B rlwimi r5, r0, 8, 0x10, 0x17
   201 M rlwimi r5, r4, 0x10, 8, 0xf
       B lbz r4, 2(r6)
   202 M rlwimi r5, r0, 0x18, 0, 7
       B lbz r0, 3(r6)
   203 M bne 12
       B rlwimi r5, r4, 0x10, 8, 0xf
   204 M mr r0, r5
       B rlwimi r5, r0, 0x18, 0, 7
   205 M b 20
       B bne 12
   206 M rlwinm r0, r5, 0x18, 0x10, 0x17
       B mr r0, r5
   207 M rlwimi r0, r5, 8, 0x18, 0x1f
       B b 20
   208 M rlwimi r0, r5, 8, 8, 0xf
       B rlwinm r0, r5, 0x18, 0x10, 0x17
   209 M rlwimi r0, r5, 0x18, 0, 7
       B rlwimi r0, r5, 8, 0x18, 0x1f
   210 M stw r0, 0x1c(r3)
       B rlwimi r0, r5, 8, 8, 0xf
   211 M blr
       B rlwimi r0, r5, 0x18, 0, 7
   212 M lbz r0, 9(r5)
       B stw r0, 0x1c(r3)
   213 M cmplwi r4, 0x4949
       B blr
   214 M lbz r4, 8(r5)
       B lbz r0, 9(r5)
   215 M rlwimi r4, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   216 M rlwinm r0, r4, 8, 0x10, 0x17
       B lbz r4, 8(r5)
   217 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r4, r0, 8, 0x10, 0x17
   218 M bne 8
       B rlwinm r0, r4, 8, 0x10, 0x17
   219 M clrlwi r0, r4, 0x10
       B rlwimi r0, r4, 0x18, 0x18, 0x1f
   220 M sth r0, 0x20(r3)
       B bne 8
   221 M blr
       B clrlwi r0, r4, 0x10
   222 M lbz r0, 9(r5)
       B sth r0, 0x20(r3)
   223 M cmplwi r4, 0x4949
       B blr
   224 M lbz r7, 8(r5)
       B lbz r0, 9(r5)
   225 M rlwimi r7, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   226 M lbz r6, 0xa(r5)
       B lbz r7, 8(r5)
   227 M lbz r0, 0xb(r5)
       B rlwimi r7, r0, 8, 0x10, 0x17
   228 M rlwimi r7, r6, 0x10, 8, 0xf
       B lbz r6, 0xa(r5)
   229 M rlwimi r7, r0, 0x18, 0, 7
       B lbz r0, 0xb(r5)
   230 M bne 12
       B rlwimi r7, r6, 0x10, 8, 0xf
   231 M mr r9, r7
       B rlwimi r7, r0, 0x18, 0, 7
   232 M b 20
       B bne 12
   233 M rlwinm r9, r7, 0x18, 0x10, 0x17
       B mr r9, r7
   234 M rlwimi r9, r7, 8, 0x18, 0x1f
       B b 20
   235 M rlwimi r9, r7, 8, 8, 0xf
       B rlwinm r9, r7, 0x18, 0x10, 0x17
   236 M rlwimi r9, r7, 0x18, 0, 7
       B rlwimi r9, r7, 8, 0x18, 0x1f
   237 M mr r7, r3
       B rlwimi r9, r7, 8, 8, 0xf
   238 M li r10, 0
       B rlwimi r9, r7, 0x18, 0, 7
   239 M li r0, 0x80
       B mr r7, r3
   240 M mr r8, r7
       B li r10, 0
   241 M li r11, 0
       B li r0, 0x80
   242 M mtctr r0
       B mr r8, r7
   243 M lwz r5, 0x674(r3)
       B li r11, 0
   244 M add r6, r5, r9
       B mtctr r0
   245 M cmplw r5, r6
       B lwz r5, 0x674(r3)
   246 M bgt 144
       B add r6, r5, r9
   247 M lwz r5, 0x678(r3)
       B cmplw r5, r6
   248 M addi r5, r5, -2
       B bgt 144
   249 M cmplw r6, r5
       B lwz r5, 0x678(r3)
   250 M bgt 128
       B addi r5, r5, -2
   251 M lbz r5, 1(r6)
       B cmplw r6, r5
   252 M cmplwi r4, 0x4949
       B bgt 128
   253 M lbz r6, 0(r6)
       B lbz r5, 1(r6)
   254 M rlwimi r6, r5, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   255 M rlwinm r5, r6, 8, 0x10, 0x17
       B lbz r6, 0(r6)
   256 M rlwimi r5, r6, 0x18, 0x18, 0x1f
       B rlwimi r6, r5, 8, 0x10, 0x17
   257 M bne 8
       B rlwinm r5, r6, 8, 0x10, 0x17
   258 M clrlwi r5, r6, 0x10
       B rlwimi r5, r6, 0x18, 0x18, 0x1f
   259 M sth r5, 0x22(r8)
       B bne 8
   260 M addi r9, r9, 2
       B clrlwi r5, r6, 0x10
   261 M lwz r5, 0x674(r3)
       B sth r5, 0x22(r8)
   262 M add r6, r5, r9
       B addi r9, r9, 2
   263 M cmplw r5, r6
       B lwz r5, 0x674(r3)
   264 M bgt 72
       B add r6, r5, r9
   265 M lwz r5, 0x678(r3)
       B cmplw r5, r6
   266 M addi r5, r5, -2
       B bgt 72
   267 M cmplw r6, r5
       B lwz r5, 0x678(r3)
   268 M bgt 56
       B addi r5, r5, -2
   269 M lbz r5, 1(r6)
       B cmplw r6, r5
   270 M cmplwi r4, 0x4949
       B bgt 56
   271 M lbz r6, 0(r6)
       B lbz r5, 1(r6)
   272 M rlwimi r6, r5, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   273 M rlwinm r5, r6, 8, 0x10, 0x17
       B lbz r6, 0(r6)
   274 M rlwimi r5, r6, 0x18, 0x18, 0x1f
       B rlwimi r6, r5, 8, 0x10, 0x17
   275 M bne 8
       B rlwinm r5, r6, 8, 0x10, 0x17
   276 M clrlwi r5, r6, 0x10
       B rlwimi r5, r6, 0x18, 0x18, 0x1f
   277 M sth r5, 0x24(r8)
       B bne 8
   278 M addi r9, r9, 2
       B clrlwi r5, r6, 0x10
   279 M addi r8, r8, 4
       B sth r5, 0x24(r8)
   280 M addi r11, r11, 1
       B addi r9, r9, 2
   281 M bdnz -152
       B addi r8, r8, 4
   282 M addi r10, r10, 1
       B addi r11, r11, 1
   283 M addi r7, r7, 0x200
       B bdnz -152
   284 M cmplwi r10, 3
       B addi r10, r10, 1
   285 M blt -180
       B addi r7, r7, 0x200
   286 M blr
       B cmplwi r10, 3
   287 M lbz r0, 9(r5)
       B blt -180
   288 M cmplwi r4, 0x4949
       B blr
   289 M lbz r6, 8(r5)
       B lbz r0, 9(r5)
   290 M rlwimi r6, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   291 M lbz r4, 0xa(r5)
       B lbz r6, 8(r5)
   292 M lbz r0, 0xb(r5)
       B rlwimi r6, r0, 8, 0x10, 0x17
   293 M rlwimi r6, r4, 0x10, 8, 0xf
       B lbz r4, 0xa(r5)
   294 M rlwimi r6, r0, 0x18, 0, 7
       B lbz r0, 0xb(r5)
   295 M bne 12
       B rlwimi r6, r4, 0x10, 8, 0xf
   296 M mr r0, r6
       B rlwimi r6, r0, 0x18, 0, 7
   297 M b 20
       B bne 12
   298 M rlwinm r0, r6, 0x18, 0x10, 0x17
       B mr r0, r6
   299 M rlwimi r0, r6, 8, 0x18, 0x1f
       B b 20
   300 M rlwimi r0, r6, 8, 8, 0xf
       B rlwinm r0, r6, 0x18, 0x10, 0x17
   301 M rlwimi r0, r6, 0x18, 0, 7
       B rlwimi r0, r6, 8, 0x18, 0x1f
   302 M lwz r4, 0x674(r3)
       B rlwimi r0, r6, 8, 8, 0xf
   303 M add r5, r4, r0
       B rlwimi r0, r6, 0x18, 0, 7
   304 M cmplw r4, r5
       B lwz r4, 0x674(r3)
   305 M bgtlr
       B add r5, r4, r0
   306 M lwz r4, 0x678(r3)
       B cmplw r4, r5
   307 M addi r0, r4, -0x14
       B bgtlr
   308 M cmplw r5, r0
       B lwz r4, 0x678(r3)
   309 M bgtlr
       B addi r0, r4, -0x14
   310 M lbz r0, 0(r5)
       B cmplw r5, r0
   311 M stb r0, 0x622(r3)
       B bgtlr
   312 M lbz r0, 1(r5)
       B lbz r0, 0(r5)
   313 M stb r0, 0x623(r3)
       B stb r0, 0x622(r3)
   314 M lbz r0, 2(r5)
       B lbz r0, 1(r5)
   315 M stb r0, 0x624(r3)
       B stb r0, 0x623(r3)
   316 M lbz r0, 3(r5)
       B lbz r0, 2(r5)
   317 M stb r0, 0x625(r3)
       B stb r0, 0x624(r3)
   318 M lbz r0, 4(r5)
       B lbz r0, 3(r5)
   319 M stb r0, 0x626(r3)
       B stb r0, 0x625(r3)
   320 M lbz r0, 5(r5)
       B lbz r0, 4(r5)
   321 M stb r0, 0x627(r3)
       B stb r0, 0x626(r3)
   322 M lbz r0, 6(r5)
       B lbz r0, 5(r5)
   323 M stb r0, 0x628(r3)
       B stb r0, 0x627(r3)
   324 M lbz r0, 7(r5)
       B lbz r0, 6(r5)
   325 M stb r0, 0x629(r3)
       B stb r0, 0x628(r3)
   326 M lbz r0, 8(r5)
       B lbz r0, 7(r5)
   327 M stb r0, 0x62a(r3)
       B stb r0, 0x629(r3)
   328 M lbz r0, 9(r5)
       B lbz r0, 8(r5)
   329 M stb r0, 0x62b(r3)
       B stb r0, 0x62a(r3)
   330 M lbz r0, 0xa(r5)
       B lbz r0, 9(r5)
   331 M stb r0, 0x62c(r3)
       B stb r0, 0x62b(r3)
   332 M lbz r0, 0xb(r5)
       B lbz r0, 0xa(r5)
   333 M stb r0, 0x62d(r3)
       B stb r0, 0x62c(r3)
   334 M lbz r0, 0xc(r5)
       B lbz r0, 0xb(r5)
   335 M stb r0, 0x62e(r3)
       B stb r0, 0x62d(r3)
   336 M lbz r0, 0xd(r5)
       B lbz r0, 0xc(r5)
   337 M stb r0, 0x62f(r3)
       B stb r0, 0x62e(r3)
   338 M lbz r0, 0xe(r5)
       B lbz r0, 0xd(r5)
   339 M stb r0, 0x630(r3)
       B stb r0, 0x62f(r3)
   340 M lbz r0, 0xf(r5)
       B lbz r0, 0xe(r5)
   341 M stb r0, 0x631(r3)
       B stb r0, 0x630(r3)
   342 M lbz r0, 0x10(r5)
       B lbz r0, 0xf(r5)
   343 M stb r0, 0x632(r3)
       B stb r0, 0x631(r3)
   344 M lbz r0, 0x11(r5)
       B lbz r0, 0x10(r5)
   345 M stb r0, 0x633(r3)
       B stb r0, 0x632(r3)
   346 M lbz r0, 0x12(r5)
       B lbz r0, 0x11(r5)
   347 M stb r0, 0x634(r3)
       B stb r0, 0x633(r3)
   348 M lbz r0, 0x13(r5)
       B lbz r0, 0x12(r5)
   349 M stb r0, 0x635(r3)
       B stb r0, 0x634(r3)
   350 M blr
       B lbz r0, 0x13(r5)
   351 M lbz r0, 9(r5)
       B stb r0, 0x635(r3)
   352 M cmplwi r4, 0x4949
       B blr
   353 M lbz r4, 8(r5)
       B lbz r0, 9(r5)
   354 M rlwimi r4, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   355 M rlwinm r0, r4, 8, 0x10, 0x17
       B lbz r4, 8(r5)
   356 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r4, r0, 8, 0x10, 0x17
   357 M bne 8
       B rlwinm r0, r4, 8, 0x10, 0x17
   358 M clrlwi r0, r4, 0x10
       B rlwimi r0, r4, 0x18, 0x18, 0x1f
   359 M sth r0, 0x636(r3)
       B bne 8
   360 M blr
       B clrlwi r0, r4, 0x10
   361 M lbz r0, 9(r5)
       B sth r0, 0x636(r3)
   362 M cmplwi r4, 0x4949
       B blr
   363 M lbz r6, 8(r5)
       B lbz r0, 9(r5)
   364 M rlwimi r6, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   365 M lbz r4, 0xa(r5)
       B lbz r6, 8(r5)
   366 M lbz r0, 0xb(r5)
       B rlwimi r6, r0, 8, 0x10, 0x17
   367 M rlwimi r6, r4, 0x10, 8, 0xf
       B lbz r4, 0xa(r5)
   368 M rlwimi r6, r0, 0x18, 0, 7
       B lbz r0, 0xb(r5)
   369 M bne 12
       B rlwimi r6, r4, 0x10, 8, 0xf
   370 M mr r0, r6
       B rlwimi r6, r0, 0x18, 0, 7
   371 M b 20
       B bne 12
   372 M rlwinm r0, r6, 0x18, 0x10, 0x17
       B mr r0, r6
   373 M rlwimi r0, r6, 8, 0x18, 0x1f
       B b 20
   374 M rlwimi r0, r6, 8, 8, 0xf
       B rlwinm r0, r6, 0x18, 0x10, 0x17
   375 M rlwimi r0, r6, 0x18, 0, 7
       B rlwimi r0, r6, 8, 0x18, 0x1f
   376 M stw r0, 0x638(r3)
       B rlwimi r0, r6, 8, 8, 0xf
   377 M blr
       B rlwimi r0, r6, 0x18, 0, 7
   378 M lbz r7, 8(r5)
       B stw r0, 0x638(r3)
   379 M lbz r6, 9(r5)
       B blr
   380 M lbz r4, 0xa(r5)
       B lbz r0, 8(r5)
   381 M lbz r0, 0xb(r5)
       B stb r0, 0x63c(r3)
   382 M stb r7, 0x63c(r3)
       B lbz r0, 9(r5)
   383 M stb r6, 0x63d(r3)
       B stb r0, 0x63d(r3)
   384 M stb r4, 0x63e(r3)
       B lbz r0, 0xa(r5)
   385 M stb r0, 0x63f(r3)
       B stb r0, 0x63e(r3)
   386 M blr
       B lbz r0, 0xb(r5)
   387 M lbz r7, 8(r5)
       B stb r0, 0x63f(r3)
   388 M lbz r6, 9(r5)
       B blr
   389 M lbz r4, 0xa(r5)
       B lbz r0, 8(r5)
   390 M lbz r0, 0xb(r5)
       B stb r0, 0x640(r3)
   391 M stb r7, 0x640(r3)
       B lbz r0, 9(r5)
   392 M stb r6, 0x641(r3)
       B stb r0, 0x641(r3)
   393 M stb r4, 0x642(r3)
       B lbz r0, 0xa(r5)
   394 M stb r0, 0x643(r3)
       B stb r0, 0x642(r3)
   395 M blr
       B lbz r0, 0xb(r5)
   396 M lbz r7, 8(r5)
       B stb r0, 0x643(r3)
   397 M lbz r6, 9(r5)
       B blr
   398 M lbz r4, 0xa(r5)
       B lbz r0, 8(r5)
   399 M lbz r0, 0xb(r5)
       B stb r0, 0x644(r3)
   400 M stb r7, 0x644(r3)
       B lbz r0, 9(r5)
   401 M stb r6, 0x645(r3)
       B stb r0, 0x645(r3)
   402 M stb r4, 0x646(r3)
       B lbz r0, 0xa(r5)
   403 M stb r0, 0x647(r3)
       B stb r0, 0x646(r3)
   404 M blr
       B lbz r0, 0xb(r5)
   405 M lbz r0, 9(r5)
       B stb r0, 0x647(r3)
   406 M cmplwi r4, 0x4949
       B blr
   407 M lbz r4, 8(r5)
       B lbz r0, 9(r5)
   408 M rlwimi r4, r0, 8, 0x10, 0x17
       B cmplwi r4, 0x4949
   409 M rlwinm r0, r4, 8, 0x10, 0x17
       B lbz r4, 8(r5)
   410 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r4, r0, 8, 0x10, 0x17
   411 M bne 8
       B rlwinm r0, r4, 8, 0x10, 0x17
   412 M clrlwi r0, r4, 0x10
       B rlwimi r0, r4, 0x18, 0x18, 0x1f
   413 M sth r0, 0x648(r3)
       B bne 8
   414 M blr
       B clrlwi r0, r4, 0x10
   415 M clrlwi r0, r8, 0x10
       B sth r0, 0x648(r3)
   416 M cmplwi r0, 3
       B blr
   417 M bne 48
       B cmplwi r8, 3
   418 M lbz r0, 9(r5)
       B bne 48
   419 M cmplwi r4, 0x4949
       B lbz r0, 9(r5)
   420 M lbz r4, 8(r5)
       B cmplwi r4, 0x4949
   421 M rlwimi r4, r0, 8, 0x10, 0x17
       B lbz r4, 8(r5)
   422 M rlwinm r0, r4, 8, 0x10, 0x17
       B rlwimi r4, r0, 8, 0x10, 0x17
   423 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwinm r0, r4, 8, 0x10, 0x17
   424 M bne 8
       B rlwimi r0, r4, 0x18, 0x18, 0x1f
   425 M clrlwi r0, r4, 0x10
       B bne 8
   426 M clrlwi r0, r0, 0x10
       B clrlwi r0, r4, 0x10
   427 M stw r0, 0x64c(r3)
       B clrlwi r0, r0, 0x10
   428 M blr
       B stw r0, 0x64c(r3)
   429 M cmplwi r0, 4
       B blr
   430 M bnelr
       B cmplwi r8, 4
   431 M lbz r0, 9(r5)
       B bnelr
   432 M cmplwi r4, 0x4949
       B lbz r0, 9(r5)
   433 M lbz r6, 8(r5)
       B cmplwi r4, 0x4949
   434 M rlwimi r6, r0, 8, 0x10, 0x17
       B lbz r6, 8(r5)
   435 M lbz r4, 0xa(r5)
       B rlwimi r6, r0, 8, 0x10, 0x17
   436 M lbz r0, 0xb(r5)
       B lbz r4, 0xa(r5)
   437 M rlwimi r6, r4, 0x10, 8, 0xf
       B lbz r0, 0xb(r5)
   438 M rlwimi r6, r0, 0x18, 0, 7
       B rlwimi r6, r4, 0x10, 8, 0xf
   439 M bne 12
       B rlwimi r6, r0, 0x18, 0, 7
   440 M mr r0, r6
       B bne 12
   441 M b 20
       B mr r0, r6
   442 M rlwinm r0, r6, 0x18, 0x10, 0x17
       B b 20
   443 M rlwimi r0, r6, 8, 0x18, 0x1f
       B rlwinm r0, r6, 0x18, 0x10, 0x17
   444 M rlwimi r0, r6, 8, 8, 0xf
       B rlwimi r0, r6, 8, 0x18, 0x1f
   445 M rlwimi r0, r6, 0x18, 0, 7
       B rlwimi r0, r6, 8, 8, 0xf
   446 M stw r0, 0x64c(r3)
       B rlwimi r0, r6, 0x18, 0, 7
   447 M blr
       B stw r0, 0x64c(r3)
   448 M clrlwi r0, r8, 0x10
       B blr
   449 M cmplwi r0, 3
       B cmplwi r8, 3
   462 M cmplwi r0, 4
       B cmplwi r8, 4
```

## libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD1_tag_parse

```text
src 0x3bc base 0x3c8 insns 239/242
--- replace mine 9:11 base 9:11
  M    9 cmpwi r7, 0x201
  M   10 beq 780
  B    9 cmpwi r7, 0x132
  B   10 beqlr
--- replace mine 12:14 base 12:14
  M   12 cmpwi r7, 0x11b
  M   13 beq 428
  B   12 cmpwi r7, 0x11a
  B   13 beq 180
--- insert mine 16:16 base 16:25
  B   16 beqlr
  B   17 bgelr
  B   18 cmpwi r7, 0x103
  B   19 beq 716
  B   20 bltlr
  B   21 blr
  B   22 blr
  B   23 cmpwi r7, 0x128
  B   24 beq 656
--- replace mine 17:23 base 26:29
  M   17 cmpwi r7, 0x103
  M   18 beq 708
  M   19 blr
  M   20 cmpwi r7, 0x11a
  M   21 bge 136
  M   22 blr
  B   26 cmpwi r7, 0x11c
  B   27 bgelr
  B   28 b 380
--- delete mine 24:30 base 30:30
  M   24 beqlr
  M   25 bge 16
  M   26 cmpwi r7, 0x128
  M   27 beq 632
  M   28 blr
  M   29 cmpwi r7, 0x132
--- insert mine 33:33 base 33:50
  B   33 addi r0, r6, -0x7897
  B   34 cmpw r7, r0
  B   35 beqlr
  B   36 bge 40
  B   37 cmpwi r7, 0x202
  B   38 beq 748
  B   39 bge 16
  B   40 cmpwi r7, 0x201
  B   41 bge 668
  B   42 blr
  B   43 cmpwi r7, 0x213
  B   44 beqlr
  B   45 blr
  B   46 addi r0, r6, -0x6eff
  B   47 cmpw r7, r0
  B   48 beqlr
  B   49 bge 20
--- replace mine 36:41 base 53:56
  M   36 bge 44
  M   37 cmpwi r7, 0x213
  M   38 beqlr
  M   39 bge 16
  M   40 cmpwi r7, 0x203
  B   53 blr
  B   54 addi r0, r6, -0x5ffc
  B   55 cmpw r7, r0
--- delete mine 42:54 base 57:57
  M   42 b 720
  M   43 addi r0, r6, -0x7897
  M   44 cmpw r7, r0
  M   45 beqlr
  M   46 blr
  M   47 addi r0, r6, -0x5ffd
  M   48 cmpw r7, r0
  M   49 beqlr
  M   50 bgelr
  M   51 addi r0, r6, -0x6eff
  M   52 cmpw r7, r0
  M   53 beqlr
--- replace mine 64:65 base 67:68
  M   64 mr r6, r7
  B   67 mr r8, r7
--- replace mine 66:70 base 69:73
  M   66 rlwinm r6, r7, 0x18, 0x10, 0x17
  M   67 rlwimi r6, r7, 8, 0x18, 0x1f
  M   68 rlwimi r6, r7, 8, 8, 0xf
  M   69 rlwimi r6, r7, 0x18, 0, 7
  B   69 rlwinm r8, r7, 0x18, 0x10, 0x17
  B   70 rlwimi r8, r7, 8, 0x18, 0x1f
  B   71 rlwimi r8, r7, 8, 8, 0xf
  B   72 rlwimi r8, r7, 0x18, 0, 7
--- replace mine 71:73 base 74:76
  M   71 add r8, r0, r6
  M   72 cmplw r0, r8
  B   74 add r6, r0, r8
  B   75 cmplw r0, r6
--- replace mine 76:77 base 79:80
  M   76 cmplw r8, r0
  B   79 cmplw r6, r0
--- replace mine 78:79 base 81:82
  M   78 lbz r0, 1(r8)
  B   81 lbz r0, 1(r6)
--- replace mine 80:81 base 83:84
  M   80 lbz r7, 0(r8)
  B   83 lbz r7, 0(r6)
--- replace mine 82:84 base 85:87
  M   82 lbz r5, 2(r8)
  M   83 lbz r0, 3(r8)
  B   85 lbz r5, 2(r6)
  B   86 lbz r0, 3(r6)
--- replace mine 93:94 base 96:97
  M   93 lwz r5, 0x674(r3)
  B   96 lwz r7, 0x674(r3)
--- replace mine 95:98 base 98:101
  M   95 add r6, r5, r6
  M   96 addi r6, r6, 4
  M   97 cmplw r5, r6
  B   98 add r5, r8, r7
  B   99 addi r6, r5, 4
  B  100 cmplw r7, r6
--- replace mine 129:130 base 132:133
  M  129 mr r6, r7
  B  132 mr r8, r7
--- replace mine 131:135 base 134:138
  M  131 rlwinm r6, r7, 0x18, 0x10, 0x17
  M  132 rlwimi r6, r7, 8, 0x18, 0x1f
  M  133 rlwimi r6, r7, 8, 8, 0xf
  M  134 rlwimi r6, r7, 0x18, 0, 7
  B  134 rlwinm r8, r7, 0x18, 0x10, 0x17
  B  135 rlwimi r8, r7, 8, 0x18, 0x1f
  B  136 rlwimi r8, r7, 8, 8, 0xf
  B  137 rlwimi r8, r7, 0x18, 0, 7
--- replace mine 136:138 base 139:141
  M  136 add r8, r0, r6
  M  137 cmplw r0, r8
  B  139 add r6, r0, r8
  B  140 cmplw r0, r6
--- replace mine 141:142 base 144:145
  M  141 cmplw r8, r0
  B  144 cmplw r6, r0
--- replace mine 143:144 base 146:147
  M  143 lbz r0, 1(r8)
  B  146 lbz r0, 1(r6)
--- replace mine 145:146 base 148:149
  M  145 lbz r7, 0(r8)
  B  148 lbz r7, 0(r6)
--- replace mine 147:149 base 150:152
  M  147 lbz r5, 2(r8)
  M  148 lbz r0, 3(r8)
  B  150 lbz r5, 2(r6)
  B  151 lbz r0, 3(r6)
--- replace mine 158:159 base 161:162
  M  158 lwz r5, 0x674(r3)
  B  161 lwz r7, 0x674(r3)
--- replace mine 160:163 base 163:166
  M  160 add r6, r5, r6
  M  161 addi r6, r6, 4
  M  162 cmplw r5, r6
  B  163 add r5, r8, r7
  B  164 addi r6, r5, 4
  B  165 cmplw r7, r6
```
