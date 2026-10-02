43U structural matching run. Initial HEAD cb0716f7a56b7b7431aa7673a394b12780db63e8
src/keyboard/tiCandidateBox pool-first
POOL IDENTICAL up to 57 (mine=57 base=57)

src/scene/sdChannelTitle/iplSDChannelTitle pool-first
POOL IDENTICAL up to 55 (mine=55 base=55)

libs/RevoEX/src/nhttp/NHTTP_recvbuf pool-first
POOL IDENTICAL up to 0 (mine=0 base=0)

src/scene/memoryCard/iplMemoryCardManager pool-first
POOL IDENTICAL up to 0 (mine=0 base=0)

START calcFadein__Q33ipl5scene14SDChannelTitleFv origin/main 0b623f581bb359f058651f7ef858e0813200754d upstream source UNCHANGED
src 0xc0 base 0xbc insns 48/47
--- replace mine 11:12 base 11:12
  M   11 b 124
  B   11 b 120
--- replace mine 15:16 base 15:16
  M   15 beq 84
  B   15 beq 80
--- delete mine 24:25 base 24:24
  M   24 li r5, 0

calcFadein__Q33ipl5scene14SDChannelTitleFv structural diagnosis: same stack, branch topology and call targets, one extra initialized ignored optOutEvent argument. No uninitialized or incompatible-call workaround allowed. Try initialized context and receiver lifetime.
calcFadein__Q33ipl5scene14SDChannelTitleFv | event handler owns both initialized event paths | 48/47 insns structural/exact (3, 26) objdiff 97.87234% regress 0 source calcFadein__Q33ipl5scene14SDChannelTitleFv.2704a24834f9
calcFadein__Q33ipl5scene14SDChannelTitleFv | event null argument shares named typed handler local | 48/47 insns structural/exact (3, 26) objdiff 97.87234% regress 0 source calcFadein__Q33ipl5scene14SDChannelTitleFv.9f1fb18b3c24
calcFadein__Q33ipl5scene14SDChannelTitleFv | fade playing snapshot before transition condition | 48/47 insns structural/exact (3, 26) objdiff 97.87234% regress 0 source calcFadein__Q33ipl5scene14SDChannelTitleFv.c8c8f158061c
START initCalcFadeout__Q33ipl5scene14SDChannelTitleFv origin/main 0b623f581bb359f058651f7ef858e0813200754d upstream source UNCHANGED
src 0xc8 base 0xc4 insns 50/49
--- delete mine 43:44 base 43:43
  M   43 li r5, 0

initCalcFadeout__Q33ipl5scene14SDChannelTitleFv structural diagnosis: same stack, branch topology and call targets, one extra initialized ignored optOutEvent argument. No uninitialized or incompatible-call workaround allowed. Try initialized context and receiver lifetime.
initCalcFadeout__Q33ipl5scene14SDChannelTitleFv | fade state snapshot shared by exit and button branches | 50/49 insns structural/exact (1, 7) objdiff 97.95918% regress 0 source initCalcFadeout__Q33ipl5scene14SDChannelTitleFv.9159d62e470f
initCalcFadeout__Q33ipl5scene14SDChannelTitleFv | null handler shared by both initialized arguments | 50/49 insns structural/exact (1, 7) objdiff 97.95918% regress 0 source initCalcFadeout__Q33ipl5scene14SDChannelTitleFv.dc9cc5e382dd
initCalcFadeout__Q33ipl5scene14SDChannelTitleFv | button receiver reference for cleanup | 50/49 insns structural/exact (1, 7) objdiff 97.95918% regress 0 source initCalcFadeout__Q33ipl5scene14SDChannelTitleFv.b6b8145ca689
START iplSDChannelTitle_startCopyProgress origin/main 0b623f581bb359f058651f7ef858e0813200754d upstream source UNCHANGED
src 0x15c base 0x158 insns 87/86
--- replace mine 10:11 base 10:11
  M   10 bne 284
  B   10 bne 280
--- replace mine 15:16 base 15:16
  M   15 bne 264
  B   15 bne 260
--- replace mine 20:21 base 20:21
  M   20 b 244
  B   20 b 240
--- replace mine 65:66 base 65:68
  M   65 b 64
  B   65 b 60
  B   66 lwz r3, 0x13c(r31)
  B   67 addi r7, r31, 0x228
--- delete mine 67:68 base 69:69
  M   67 addi r7, r31, 0x228
--- delete mine 69:71 base 70:70
  M   69 li r4, 0
  M   70 lwz r3, 0x13c(r31)

iplSDChannelTitle_startCopyProgress structural diagnosis: same frame; one extra ignored controller initialization and high/low title word argument scheduling. Receiver evaluation and explicit temporaries first; no omitted initialized parameter.
iplSDChannelTitle_startCopyProgress | title halves have named call-boundary lifetimes | 87/86 insns structural/exact (8, 31) objdiff 95.81396% regress 0 source iplSDChannelTitle_startCopyProgress.963faa672f1c
iplSDChannelTitle_startCopyProgress | current selected index as initialized ignored controller context | 87/86 insns structural/exact (9, 24) objdiff 98.62791% regress 0 source iplSDChannelTitle_startCopyProgress.5c5590ed103a
iplSDChannelTitle_startCopyProgress | selector receiver reference at actual notice boundary | 88/86 insns structural/exact (10, 34) objdiff 92.19768% regress 0 source iplSDChannelTitle_startCopyProgress.ebf366686a81
START iplSDChannelTitle_updateCopyStart origin/main 0b623f581bb359f058651f7ef858e0813200754d upstream source UNCHANGED
src 0x134 base 0x130 insns 77/76
--- replace mine 10:11 base 10:11
  M   10 bne 244
  B   10 bne 240
--- replace mine 37:38 base 37:38
  M   37 beq 104
  B   37 beq 100
--- replace mine 43:44 base 43:44
  M   43 beq 80
  B   43 beq 76
--- replace mine 46:47 base 46:47
  M   46 beq 100
  B   46 beq 96
--- insert mine 48:48 base 48:49
  B   48 mr r6, r29
--- delete mine 49:51 base 50:50
  M   49 mr r6, r29
  M   50 li r4, 0

iplSDChannelTitle_updateCopyStart structural diagnosis: same frame; one extra ignored controller initialization and high/low title word argument scheduling. Receiver evaluation and explicit temporaries first; no omitted initialized parameter.
iplSDChannelTitle_updateCopyStart | title halves have named call-boundary lifetimes | 77/76 insns structural/exact (5, 33) objdiff 98.3421% regress 0 source iplSDChannelTitle_updateCopyStart.7d24a54898ae
iplSDChannelTitle_updateCopyStart | current selected index as initialized ignored controller context | 77/76 insns structural/exact (5, 33) objdiff 98.42105% regress 0 source iplSDChannelTitle_updateCopyStart.311917ae2b6e
iplSDChannelTitle_updateCopyStart | selector receiver reference at actual notice boundary | 77/76 insns structural/exact (5, 33) objdiff 98.3421% regress 0 source iplSDChannelTitle_updateCopyStart.188a3fcc1242
START iplSDChannelTitle_flushSaveBeforeExit origin/main 0b623f581bb359f058651f7ef858e0813200754d upstream source UNCHANGED
src 0x94 base 0x94 insns 37/37
diffs 6: [20, 22, 23, 24, 25, 26]
    20 M lis r4, 0
       B lis r3, 0
    22 M addi r4, r4, 0
       B addi r3, r3, 0
    23 M lwz r3, 0x94(r4)
       B lwz r4, 0x94(r3)
    24 M stw r0, 0x4c0(r3)
       B stw r0, 0x4c0(r4)
    25 M lwz r3, 0x94(r4)
       B lwz r4, 0x28(r3)
    26 M lwz r4, 0x28(r4)
       B lwz r3, 0x94(r3)

flushSaveBeforeExit structural diagnosis: 37/37, six global base and save-manager/app-heap operand evaluation differences; target computes heap access before manager reload within call expression.
iplSDChannelTitle_flushSaveBeforeExit | previous page has correctly typed named reference | 37/37 insns structural/exact (2, 6) objdiff 98.5946% regress 0 source iplSDChannelTitle_flushSaveBeforeExit.09f2acba2e61
iplSDChannelTitle_flushSaveBeforeExit | heap local declaration separated from use assignment | 37/37 insns structural/exact (2, 6) objdiff 98.5946% regress 0 source iplSDChannelTitle_flushSaveBeforeExit.ceea2499009f
iplSDChannelTitle_flushSaveBeforeExit | flush result pointer assigned after named file local | 37/37 insns structural/exact (2, 6) objdiff 98.5946% regress 0 source iplSDChannelTitle_flushSaveBeforeExit.feeacb961b65
iplSDChannelTitle_flushSaveBeforeExit | page store has inline receiver-first setter | 37/37 insns structural/exact (2, 6) objdiff 98.5946% regress 0 source iplSDChannelTitle_flushSaveBeforeExit.5d2dd1491b28
iplSDChannelTitle_flushSaveBeforeExit | page store has inline page-first setter | 37/37 insns structural/exact (2, 6) objdiff 98.5946% regress 0 source iplSDChannelTitle_flushSaveBeforeExit.22fb86223ee8
iplSDChannelTitle_flushSaveBeforeExit | page setter owns System receiver access | 37/37 insns structural/exact (2, 6) objdiff 98.5946% regress 0 source iplSDChannelTitle_flushSaveBeforeExit.c90be529ada9
iplSDChannelTitle_flushSaveBeforeExit register-last output
declaration block:
      int page;
      int index;
start (2, 6)
best (2, 6) after 2 builds; source restored; best order was:
    int page;
    int index;

START create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator origin/main 3d97a4040f1ab8f5832a182a94baa9e7e05f6c59 upstream source UNCHANGED
src 0x57c base 0x580 insns 351/352
--- replace mine 5:6 base 5:6
  M    5 lis r29, 0
  B    5 lis r30, 0
--- replace mine 10:11 base 10:11
  M   10 addi r29, r29, 0
  B   10 addi r30, r30, 0
--- replace mine 29:30 base 29:30
  M   29 mr r30, r3
  B   29 mr r26, r3
--- replace mine 49:51 base 49:51
  M   49 stw r30, 0xe0(r31)
  M   50 mr r3, r30
  B   49 stw r26, 0xe0(r31)
  B   50 mr r3, r26
--- replace mine 52:53 base 52:53
  M   52 lwz r12, 0(r30)
  B   52 lwz r12, 0(r26)
--- replace mine 77:79 base 77:79
  M   77 li r28, 0
  M   78 li r30, 0
  B   77 mr r26, r31
  B   78 li r29, 0
--- replace mine 80:81 base 80:81
  M   80 add r3, r31, r30
  B   80 lwz r3, 0x11c(r26)
--- delete mine 82:83 base 82:82
  M   82 lwz r3, 0x11c(r3)
--- replace mine 89:90 base 88:89
  M   89 add r3, r31, r30
  B   88 lwz r3, 0x16c(r26)
--- delete mine 91:92 base 90:90
  M   91 lwz r3, 0x16c(r3)
--- replace mine 96:100 base 94:98
  M   96 addi r28, r28, 1
  M   97 addi r30, r30, 4
  M   98 cmplwi r28, 0x14
  M   99 blt -76
  B   94 addi r29, r29, 1
  B   95 addi r26, r26, 4
  B   96 cmplwi r29, 0x14
  B   97 blt -68
--- replace mine 111:112 base 109:110
  M  111 mr r28, r3
  B  109 mr r29, r3
--- replace mine 115:116 base 113:114
  M  115 mr r3, r28
  B  113 mr r3, r29
--- replace mine 126:129 base 124:126
  M  126 addi r30, r29, 0x28
  M  127 mr r3, r28
  M  128 addi r4, r30, 0x680
  B  124 mr r3, r29
  B  125 addi r4, r30, 0x6a8
--- replace mine 131:133 base 128:130
  M  131 mr r3, r28
  M  132 addi r4, r29, 0x6b4
  B  128 mr r3, r29
  B  129 addi r4, r30, 0x6b4
--- replace mine 136:137 base 133:134
  M  136 addi r4, r30, 0x680
  B  133 addi r4, r30, 0x6a8
--- replace mine 148:149 base 145:146
  M  148 addi r4, r30, 0x680
  B  145 addi r4, r30, 0x6a8
--- replace mine 167:169 base 164:165
  M  167 addi r30, r29, 0x6b4
  M  168 addi r4, r30, 0xc
  B  164 addi r4, r30, 0x6c0
--- replace mine 187:188 base 183:184
  M  187 addi r4, r30, 0x18
  B  183 addi r4, r30, 0x6cc
--- replace mine 225:226 base 221:222
  M  225 addi r4, r30, 0x24
  B  221 addi r4, r30, 0x6d8
--- replace mine 256:257 base 252:255
  M  256 mr r27, r31
  B  252 mr r26, r31
  B  253 addi r28, r30, 0x6e4
  B  254 addi r29, r30, 0x6f8
--- replace mine 258:261 base 256:259
  M  258 addi r27, r31, 0x24
  M  259 lwz r12, 0(r27)
  M  260 mr r3, r27
  B  256 addi r26, r31, 0x24
  B  257 lwz r12, 0(r26)
  B  258 mr r3, r26
--- replace mine 264:266 base 262:264
  M  264 mr r28, r3
  M  265 addi r4, r30, 0x44
  B  262 mr r27, r3
  B  263 mr r4, r29
--- replace mine 268:270 base 266:268
  M  268 mr r3, r28
  M  269 addi r4, r30, 0x30
  B  266 mr r3, r27
  B  267 mr r4, r28
--- replace mine 272:275 base 270:273
  M  272 mr r3, r27
  M  273 addi r4, r30, 0x44
  M  274 lwz r12, 0(r27)
  B  270 mr r3, r26
  B  271 mr r4, r29
  B  272 lwz r12, 0(r26)
--- replace mine 282:283 base 280:282
  M  282 mr r27, r31
  B  280 mr r26, r31
  B  281 addi r28, r30, 0x70c
--- insert mine 284:284 base 283:284
  B  283 addi r27, r30, 0x720
--- replace mine 285:288 base 285:288
  M  285 addi r27, r31, 0x24
  M  286 lwz r12, 0(r27)
  M  287 mr r3, r27
  B  285 addi r26, r31, 0x24
  B  286 lwz r12, 0(r26)
  B  287 mr r3, r26
--- replace mine 291:293 base 291:293
  M  291 mr r28, r3
  M  292 addi r4, r30, 0x6c
  B  291 mr r29, r3
  B  292 mr r4, r27
--- replace mine 295:297 base 295:297
  M  295 mr r3, r28
  M  296 addi r4, r30, 0x58
  B  295 mr r3, r29
  B  296 mr r4, r28
--- replace mine 299:302 base 299:302
  M  299 mr r3, r27
  M  300 addi r4, r30, 0x6c
  M  301 lwz r12, 0(r27)
  B  299 mr r3, r26
  B  300 mr r4, r27
  B  301 lwz r12, 0(r26)
--- replace mine 322:323 base 322:324
  M  322 mr r27, r31
  B  322 mr r26, r31
  B  323 addi r27, r30, 0x738
--- replace mine 324:327 base 325:328
  M  324 addi r27, r31, 0x24
  M  325 lwz r12, 0(r27)
  M  326 mr r3, r27
  B  325 addi r26, r31, 0x24
  B  326 lwz r12, 0(r26)
  B  327 mr r3, r26
--- replace mine 330:331 base 331:332
  M  330 addi r4, r29, 0x738
  B  331 mr r4, r27
--- replace mine 333:336 base 334:337
  M  333 mr r3, r27
  M  334 addi r4, r29, 0x738
  M  335 lwz r12, 0(r27)
  B  334 mr r3, r26
  B  335 mr r4, r27
  B  336 lwz r12, 0(r26)

create structural diagnosis: same stack, 351/352 instructions; indexed Init loop adds two loads/address sums versus target advancing array cursors. Inline Create name lifetimes also differ. Pool identical.
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | Init traverses independent text and bounding arrays | 351/352 insns structural/exact (27, 241) objdiff 93.47159% regress 1 source create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.27d1bdc77e29
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | decorated string constructed into typed local before member assignment | 351/352 insns structural/exact (27, 239) objdiff 92.71023% regress 0 source create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.358efc8af2c3
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | on/off helper owns named pane arguments throughout lookups | 219/352 insns structural/exact (165, 272) objdiff 53.039772% regress 0 source create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.d444098f9212
START createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator origin/main 3d97a4040f1ab8f5832a182a94baa9e7e05f6c59 upstream source UNCHANGED
src 0x358 base 0x360 insns 214/216
--- insert mine 5:5 base 5:8
  B    5 lis r25, 0
  B    6 lis r27, 0
  B    7 lis r28, 0
--- delete mine 6:10 base 9:9
  M    6 lis r26, 0
  M    7 lis r27, 0
  M    8 lis r23, 0
  M    9 lis r28, 0
--- insert mine 11:11 base 10:11
  B   10 lis r30, 0
--- insert mine 14:14 base 14:17
  B   14 addi r25, r25, 0
  B   15 addi r27, r27, 0
  B   16 addi r28, r28, 0
--- delete mine 15:19 base 18:18
  M   15 addi r26, r26, 0
  M   16 addi r27, r27, 0
  M   17 addi r23, r23, 0
  M   18 addi r28, r28, 0
--- insert mine 20:20 base 19:20
  B   19 addi r30, r30, 0
--- replace mine 21:22 base 21:22
  M   21 li r25, 0
  B   21 li r26, 0
--- replace mine 23:26 base 23:26
  M   23 li r22, 0
  M   24 add r20, r23, r0
  M   25 lwzx r0, r23, r0
  B   23 li r19, 0
  B   24 add r20, r24, r0
  B   25 lwzx r0, r24, r0
--- replace mine 40:41 base 40:41
  M   40 mr r22, r3
  B   40 mr r19, r3
--- replace mine 48:49 base 48:49
  M   48 stw r24, 0(r22)
  B   48 stw r25, 0(r19)
--- replace mine 50:54 base 50:54
  M   50 stw r3, 4(r22)
  M   51 addi r3, r22, 8
  M   52 stw r25, 0x14(r22)
  M   53 stw r25, 0x18(r22)
  B   50 stw r3, 4(r19)
  B   51 addi r3, r19, 8
  B   52 stw r26, 0x14(r19)
  B   53 stw r26, 0x18(r19)
--- replace mine 55:59 base 55:59
  M   55 stw r26, 0(r22)
  M   56 mr r3, r22
  M   57 stw r25, 0x2c(r22)
  M   58 lwz r12, 0(r22)
  B   55 stw r27, 0(r19)
  B   56 mr r3, r19
  B   57 stw r26, 0x2c(r19)
  B   58 lwz r12, 0(r19)
--- replace mine 62:64 base 62:64
  M   62 stw r27, 0(r22)
  M   63 stw r25, 0x30(r22)
  B   62 stw r28, 0(r19)
  B   63 stw r26, 0x30(r19)
--- replace mine 69:70 base 69:70
  M   69 mr r22, r3
  B   69 mr r19, r3
--- replace mine 77:78 base 77:78
  M   77 stw r24, 0(r22)
  B   77 stw r25, 0(r19)
--- replace mine 79:83 base 79:83
  M   79 stw r3, 4(r22)
  M   80 addi r3, r22, 8
  M   81 stw r25, 0x14(r22)
  M   82 stw r25, 0x18(r22)
  B   79 stw r3, 4(r19)
  B   80 addi r3, r19, 8
  B   81 stw r26, 0x14(r19)
  B   82 stw r26, 0x18(r19)
--- replace mine 84:88 base 84:88
  M   84 stw r26, 0(r22)
  M   85 mr r3, r22
  M   86 stw r25, 0x2c(r22)
  M   87 lwz r12, 0(r22)
  B   84 stw r27, 0(r19)
  B   85 mr r3, r19
  B   86 stw r26, 0x2c(r19)
  B   87 lwz r12, 0(r19)
--- replace mine 91:92 base 91:92
  M   91 stw r14, 0x30(r22)
  B   91 stw r14, 0x30(r19)
--- replace mine 97:98 base 97:98
  M   97 mr r22, r3
  B   97 mr r19, r3
--- replace mine 105:106 base 105:106
  M  105 stw r24, 0(r22)
  B  105 stw r25, 0(r19)
--- replace mine 108:112 base 108:112
  M  108 stw r3, 4(r22)
  M  109 addi r3, r22, 8
  M  110 stw r25, 0x14(r22)
  M  111 stw r0, 0x18(r22)
  B  108 stw r3, 4(r19)
  B  109 addi r3, r19, 8
  B  110 stw r26, 0x14(r19)
  B  111 stw r0, 0x18(r19)
--- replace mine 113:117 base 113:117
  M  113 stw r26, 0(r22)
  M  114 mr r3, r22
  M  115 stw r25, 0x2c(r22)
  M  116 lwz r12, 0(r22)
  B  113 stw r27, 0(r19)
  B  114 mr r3, r19
  B  115 stw r26, 0x2c(r19)
  B  116 lwz r12, 0(r19)
--- replace mine 120:121 base 120:121
  M  120 stw r28, 0(r22)
  B  120 stw r29, 0(r19)
--- replace mine 122:123 base 122:123
  M  122 stw r0, 0x30(r22)
  B  122 stw r0, 0x30(r19)
--- replace mine 128:129 base 128:129
  M  128 mr r22, r3
  B  128 mr r19, r3
--- replace mine 136:137 base 136:137
  M  136 stw r24, 0(r22)
  B  136 stw r25, 0(r19)
--- replace mine 139:143 base 139:143
  M  139 stw r3, 4(r22)
  M  140 addi r3, r22, 8
  M  141 stw r25, 0x14(r22)
  M  142 stw r0, 0x18(r22)
  B  139 stw r3, 4(r19)
  B  140 addi r3, r19, 8
  B  141 stw r26, 0x14(r19)
  B  142 stw r0, 0x18(r19)
--- replace mine 144:148 base 144:148
  M  144 stw r26, 0(r22)
  M  145 mr r3, r22
  M  146 stw r25, 0x2c(r22)
  M  147 lwz r12, 0(r22)
  B  144 stw r27, 0(r19)
  B  145 mr r3, r19
  B  146 stw r26, 0x2c(r19)
  B  147 lwz r12, 0(r19)
--- replace mine 151:152 base 151:152
  M  151 stw r29, 0(r22)
  B  151 stw r30, 0(r19)
--- replace mine 153:155 base 153:155
  M  153 stw r0, 0x30(r22)
  M  154 mr r4, r22
  B  153 stw r0, 0x30(r19)
  B  154 mr r4, r19
--- replace mine 157:159 base 157:159
  M  157 lwz r30, 0x1c(r20)
  M  158 li r19, 0
  B  157 lwz r22, 0x1c(r20)
  B  158 li r18, 0
--- replace mine 160:161 base 160:161
  M  160 b 168
  B  160 b 176
--- replace mine 162:164 base 162:164
  M  162 rlwinm r0, r19, 2, 0xe, 0x1d
  M  163 add r5, r20, r0
  B  162 rlwinm r0, r18, 2, 0xe, 0x1d
  B  163 add r23, r20, r0
--- replace mine 167:168 base 167:168
  M  167 lwz r18, 0x20(r5)
  B  167 lwz r5, 0x20(r23)
--- replace mine 169:170 base 169:170
  M  169 addi r5, r18, 4
  B  169 addi r5, r5, 4
--- replace mine 184:185 base 184:185
  M  184 cmpwi r30, 0
  B  184 cmpwi r22, 0
--- replace mine 186:189 base 186:189
  M  186 bne 32
  M  187 lwz r5, 0(r18)
  M  188 mr r3, r22
  B  186 bne 36
  B  187 lwz r5, 0x20(r23)
  B  188 mr r3, r19
--- insert mine 191:191 base 191:192
  B  191 lwz r5, 0(r5)
--- replace mine 193:196 base 194:197
  M  193 b 32
  M  194 lwz r5, 0(r18)
  M  195 mr r3, r22
  B  194 b 36
  B  195 lwz r5, 0x20(r23)
  B  196 mr r3, r19
--- replace mine 197:198 base 198:200
  M  197 mr r7, r30
  B  198 mr r7, r22
  B  199 lwz r5, 0(r5)
--- replace mine 201:203 base 203:205
  M  201 addi r19, r19, 1
  M  202 clrlwi r0, r19, 0x10
  B  203 addi r18, r18, 1
  B  204 clrlwi r0, r18, 0x10
--- replace mine 204:205 base 206:207
  M  204 blt -172
  B  206 blt -180
--- replace mine 207:208 base 209:210
  M  207 blt -740
  B  209 blt -748

createAnmPane structural diagnosis: 214/216, cached AnimationFile pointer survives CreateAnimTransform. Target reloads through entry pointer, then only vtable bases and callee-saved loop registers differ.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | entry reload with row and column indices declared before pane | 216/216 insns structural/exact (0, 53) objdiff 98.541664% regress 0 source createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.319ce8a4b2b6
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | entry reload and candidate constructor case first | 216/216 insns structural/exact (6, 100) objdiff 96.40278% regress 0 source createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.00b1430a0eb5
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | entry reload with window and on/off constructor cases first | 215/216 insns structural/exact (70, 199) objdiff 91.291664% regress 0 source createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.c00e69413163
START CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv origin/main 73f5b332e2d19fca6be39b74ab9498d03373f59e upstream source UNCHANGED
src 0x6cc base 0x6cc insns 435/435
diffs 11: [264, 269, 304, 305, 306, 307, 310, 313, 316, 322, 324]
   264 M lfs f2, 0(0)
       B lfs f3, 0(0)
   269 M lfs f2, 0(0)
       B lfs f3, 0(0)
   304 M fadds f2, f22, f0
       B fadds f3, f22, f0
   305 M frsp f1, f2
       B frsp f1, f3
   306 M lfs f3, 0x54(r1)
       B lfs f2, 0x54(r1)
   307 M fmuls f23, f2, f29
       B fmuls f23, f3, f29
   310 M stfs f2, 0x20(r1)
       B stfs f3, 0x20(r1)
   313 M stfs f3, 0x50(r22)
       B stfs f2, 0x50(r22)
   316 M stfs f3, 0x50(r23)
       B stfs f2, 0x50(r23)
   322 M stfs f3, 0x24(r1)
       B stfs f2, 0x24(r1)
   324 M stfs f3, 0x1c(r1)
       B stfs f2, 0x1c(r1)

CalcPaneLocate structural diagnosis: same frame, 435/435; eleven float register-only differences in second width expansion. Try scalar lifetime and helper boundaries before declaration search.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | both loop widths use explicit text argument helper | 427/435 insns structural/exact (22, 317) objdiff 96.02299% regress 0 source CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv.5fe993f91161
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | font-scaled widths stored in a separate scalar | 435/435 insns structural/exact (0, 11) objdiff 99.873566% regress 0 source CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv.c55ba34d7599
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | width and offset float declarations separated from initialization | 435/435 insns structural/exact (0, 11) objdiff 99.873566% regress 0 source CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv.d29b85765ca6
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv register-only declsearch
declaration block:
              f32 xOffset;
              f32 margin;
              f32 widthScale;

START NHTTPi_compareTokenN_HdrRecvBuf origin/main 73f5b332e2d19fca6be39b74ab9498d03373f59e upstream source UNCHANGED
src 0x1f8 base 0x1f0 insns 126/124
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x20(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x24(r1)
  M    3 addi r11, r1, 0x20
  B    2 stw r0, 0x34(r1)
  B    3 addi r11, r1, 0x30
--- replace mine 6:9 base 6:7
  M    6 blt 12
  M    7 li r3, -1
  M    8 b 448
  B    6 bge 444
--- replace mine 44:45 base 42:43
  M   44 extsb r0, r0
  B   42 extsb r25, r0
--- replace mine 55:57 base 53:56
  M   55 lbz r0, 4(r10)
  M   56 extsb r10, r0
  B   53 lbz r25, 4(r10)
  B   54 li r28, 0x41
  B   55 li r31, 0x5a
--- delete mine 59:60 base 58:58
  M   59 li r28, 0x41
--- replace mine 61:64 base 59:61
  M   61 li r31, 0x5a
  M   62 b 132
  M   63 extsb. r5, r26
  B   59 b 128
  B   60 extsb. r5, r5
--- replace mine 72:73 base 69:70
  M   72 b 192
  B   69 b 196
--- replace mine 80:81 base 77:78
  M   80 extsb r5, r5
  B   77 extsb r25, r5
--- replace mine 91:93 base 88:89
  M   91 lbz r5, 4(r5)
  M   92 extsb r10, r5
  B   88 lbz r25, 4(r5)
--- replace mine 95:99 base 91:98
  M   95 srawi r12, r10, 0x1f
  M   96 srwi r11, r10, 0x1f
  M   97 subfc r5, r28, r10
  M   98 adde r30, r12, r29
  B   91 lbz r5, 0(r6)
  B   92 extsb r30, r5
  B   93 srawi r12, r30, 0x1f
  B   94 subfc r10, r28, r30
  B   95 srwi r11, r30, 0x1f
  B   96 adde r27, r12, r29
  B   97 addi r26, r30, 0x20
--- replace mine 100:107 base 99:105
  M  100 subfc r5, r10, r31
  M  101 adde r5, r12, r11
  M  102 and. r5, r30, r5
  M  103 beq 8
  M  104 addi r10, r10, 0x20
  M  105 lbz r26, 0(r6)
  M  106 extsb r27, r26
  B   99 subfc r10, r30, r31
  B  100 adde r10, r12, r11
  B  101 and. r10, r27, r10
  B  102 bne 8
  B  103 mr r26, r30
  B  104 extsb r27, r25
--- replace mine 108:109 base 106:107
  M  108 subfc r5, r28, r27
  B  106 subfc r10, r28, r27
--- replace mine 112:115 base 110:113
  M  112 subfc r5, r27, r31
  M  113 adde r5, r12, r11
  M  114 and. r5, r30, r5
  B  110 subfc r10, r27, r31
  B  111 adde r10, r12, r11
  B  112 and. r10, r30, r10
--- replace mine 117:119 base 115:117
  M  117 cmpw r10, r27
  M  118 beq -220
  B  115 cmpw r27, r26
  B  116 beq -224
--- replace mine 120:121 base 118:119
  M  120 addi r11, r1, 0x20
  B  118 addi r11, r1, 0x30
--- replace mine 122:123 base 120:121
  M  122 lwz r0, 0x24(r1)
  B  120 lwz r0, 0x34(r1)
--- replace mine 124:125 base 122:123
  M  124 addi r1, r1, 0x20
  B  122 addi r1, r1, 0x30

compareToken structural diagnosis: 126/124, frame 0x20/0x30. Early failure vs positive guard changes saved registers; s8 character prematurely narrows the block byte. Target lower-case helper uses conditional expression. Fix before schedule.
NHTTPi_compareTokenN_HdrRecvBuf | positive enclosing range guard | 124/124 insns structural/exact (22, 64) objdiff 89.29032% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.98d3cf8a40f8
NHTTPi_compareTokenN_HdrRecvBuf | word character narrows at comparison helper | 125/124 insns structural/exact (20, 114) objdiff 90.66129% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.ac93fcd6b492
NHTTPi_compareTokenN_HdrRecvBuf | positive guard and int character with conditional lower-case helper | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.2a7929e1eb77
NHTTPi_compareTokenN_HdrRecvBuf | long character retains block load until comparison | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.3a00b95d61e7
NHTTPi_compareTokenN_HdrRecvBuf | increment token before header position | 124/124 insns structural/exact (4, 7) objdiff 97.16129% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.b19d270c4685
NHTTPi_compareTokenN_HdrRecvBuf | loop increment clause contains token and position | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.edcdf362313a
NHTTPi_compareTokenN_HdrRecvBuf | lowercase calls compare named token before named header | 124/124 insns structural/exact (12, 40) objdiff 93.28226% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.ac382a8e9cfb
NHTTPi_compareTokenN_HdrRecvBuf | character scope starts inside range guard | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.4a4fbb61607a
NHTTPi_compareTokenN_HdrRecvBuf | delim equality written with delimiter first | 124/124 insns structural/exact (4, 6) objdiff 97.241936% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.44d88228c2ca
NHTTPi_compareTokenN_HdrRecvBuf | last token position equality written limit first | 124/124 insns structural/exact (4, 6) objdiff 97.241936% regress 1 source NHTTPi_compareTokenN_HdrRecvBuf.971f01ea659c
NHTTPi_compareTokenN_HdrRecvBuf register/schedule search
declaration block:
      NHTTPi_HDRBUFLIST* block;
      s32 offset;
      int character;
Traceback (most recent call last):
  File "/mnt/drive2/projects/wii-ipl-workers/sol-low/tools/decomp-assist/declsearch.py", line 160, in main
    best_score = order_score(best)
                 ^^^^^^^^^^^^^^^^^
  File "/mnt/drive2/projects/wii-ipl-workers/sol-low/tools/decomp-assist/declsearch.py", line 154, in order_score
    cache[order] = evaluate()
                   ^^^^^^^^^^
  File "/mnt/drive2/projects/wii-ipl-workers/sol-low/tools/decomp-assist/declsearch.py", line 128, in evaluate
    if subprocess.run([ninja, built], capture_output=True).returncode:
       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/usr/lib/python3.12/subprocess.py", line 548, in run
    with Popen(*popenargs, **kwargs) as process:
         ^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/usr/lib/python3.12/subprocess.py", line 1026, in __init__
    self._execute_child(args, executable, preexec_fn, close_fds,
  File "/usr/lib/python3.12/subprocess.py", line 1955, in _execute_child
    raise child_exception_type(errno_num, err_msg, err_filename)
FileNotFoundError: [Errno 2] No such file or directory: 'ninja'

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/mnt/drive2/projects/wii-ipl-workers/sol-low/tools/decomp-assist/declsearch.py", line 194, in <module>
    main()
  File "/mnt/drive2/projects/wii-ipl-workers/sol-low/tools/decomp-assist/declsearch.py", line 187, in main
    subprocess.run([ninja, built], capture_output=True)
  File "/usr/lib/python3.12/subprocess.py", line 548, in run
    with Popen(*popenargs, **kwargs) as process:
         ^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/usr/lib/python3.12/subprocess.py", line 1026, in __init__
    self._execute_child(args, executable, preexec_fn, close_fds,
  File "/usr/lib/python3.12/subprocess.py", line 1955, in _execute_child
    raise child_exception_type(errno_num, err_msg, err_filename)
FileNotFoundError: [Errno 2] No such file or directory: 'ninja'

CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv repaired NINJA declaration search
declaration block:
              f32 xOffset;
              f32 margin;
              f32 widthScale;
start (0, 11)
best (0, 11) after 6 builds; source restored; best order was:
            f32 xOffset;
            f32 margin;
            f32 widthScale;

NHTTPi_compareTokenN_HdrRecvBuf repaired NINJA declaration search
declaration block:
      NHTTPi_HDRBUFLIST* block;
      s32 offset;
      int character;
start (4, 6)
best (4, 6) after 6 builds; source restored; best order was:
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    int character;

START isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl origin/main 73f5b332e2d19fca6be39b74ab9498d03373f59e upstream source UNCHANGED
src 0x1d8 base 0x1d8 insns 118/118
diffs 2: [28, 78]
    28 M add r5, r3, r0
       B add r5, r0, r3
    78 M add r5, r3, r0
       B add r5, r0, r3

isMoveEnable structural diagnosis: 118/118, identical stack and branches; two add operands reverse directory row/cell address. Try expression boundary and pointer operand order, then declaration search.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | file index precedes directory row pointer in addition | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.38b2961c4b02
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | typed directory row reference owns slot address | 116/118 insns structural/exact (13, 67) objdiff 93.41525% regress 0 source isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.a938cc10518f
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | directory address computed within typed inline helper | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.44a0463c16e7
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl register-only declaration search
declaration block:
      CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
      memorycard::CardState* states = memorycard::getCardSlotState();
      u32 file = mFile[slot][index].fileNo;
      memorycard::FileInfo* dir = NULL;
      long result;
      bool enabled = false;
start (0, 2)
best (0, 2) after 12 builds; source restored; best order was:
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    memorycard::CardState* states = memorycard::getCardSlotState();
    u32 file = mFile[slot][index].fileNo;
    memorycard::FileInfo* dir = NULL;
    long result;
    bool enabled = false;

START isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl origin/main 73f5b332e2d19fca6be39b74ab9498d03373f59e upstream source UNCHANGED
src 0x1d8 base 0x1d8 insns 118/118
diffs 2: [28, 78]
    28 M add r5, r3, r0
       B add r5, r0, r3
    78 M add r5, r3, r0
       B add r5, r0, r3

isCopyEnable structural diagnosis: 118/118, identical stack and branches; two add operands reverse directory row/cell address. Try expression boundary and pointer operand order, then declaration search.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | file index precedes directory row pointer in addition | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.33b443747c65
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | typed directory row reference owns slot address | 116/118 insns structural/exact (13, 67) objdiff 93.41525% regress 0 source isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.378d66652388
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | directory address computed within typed inline helper | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.3da50773a3c6
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl register-only declaration search
declaration block:
      CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
      memorycard::CardState* states = memorycard::getCardSlotState();
      u32 file = mFile[slot][index].fileNo;
      memorycard::FileInfo* dir = NULL;
      long result;
      bool enabled = false;
start (0, 2)
best (0, 2) after 12 builds; source restored; best order was:
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    memorycard::CardState* states = memorycard::getCardSlotState();
    u32 file = mFile[slot][index].fileNo;
    memorycard::FileInfo* dir = NULL;
    long result;
    bool enabled = false;

START isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs origin/main 73f5b332e2d19fca6be39b74ab9498d03373f59e upstream source UNCHANGED
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

isBannerEnable structural diagnosis: 26/26, same frame and arithmetic; r11 restore-base materialization scheduled seven instructions before target.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | banner validity returned directly from owned icon field | 26/26 insns structural/exact (2, 8) objdiff 92.30769% regress 0 source isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs.090dac3fe2c6
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | file selection materialized before external icon lookup | 24/26 insns structural/exact (21, 25) objdiff 34.0% regress 0 source isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs.c64b03820434
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | row and cell address owned by typed icon row | 26/26 insns structural/exact (2, 8) objdiff 92.30769% regress 0 source isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs.66e0abe9344b
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs schedule/declaration search
declaration block:
      CardIcons* icons = reinterpret_cast<CardIcons*>(memorycard::getIconStateArray());
      u32 file = mFile[slot][index].fileNo;
      memorycard::IconState* icon = &icons[slot][file];
start (2, 8)
best (2, 8) after 6 builds; source restored; best order was:
    CardIcons* icons = reinterpret_cast<CardIcons*>(memorycard::getIconStateArray());
    u32 file = mFile[slot][index].fileNo;
    memorycard::IconState* icon = &icons[slot][file];

START update_icon_anm__Q33ipl5scene17MemoryCardManagerFv origin/main 73f5b332e2d19fca6be39b74ab9498d03373f59e upstream source UNCHANGED
src 0x14c base 0x150 insns 83/84
--- replace mine 29:30 base 29:30
  M   29 bge 160
  B   29 bge 164
--- replace mine 33:34 base 33:34
  M   33 beq 144
  B   33 beq 148
--- replace mine 41:42 base 41:42
  M   41 add r22, r22, r26
  B   41 add r22, r26, r22
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

update_icon_anm structural diagnosis: 83/84, same frame; target reloads anmMax twice at 0xa6c and 0xa88 with NO intervening stores or calls; ours reuses first read. Addition operand order also differs at instruction 41. This directly supports definition-level volatile on anmMax (AGENTS.md), isolated by source-defined macro.
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv | animation step adds external delta before current frame | 83/84 insns structural/exact (7, 41) objdiff 98.39286% regress 0 source update_icon_anm__Q33ipl5scene17MemoryCardManagerFv.26b0d5897500
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv | frame counter held as meaningful cell reference | 83/84 insns structural/exact (17, 62) objdiff 88.809525% regress 0 source update_icon_anm__Q33ipl5scene17MemoryCardManagerFv.a3bdbc108e6e
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv | proven repeated anmMax reads at field definition with delta-first addition | 84/84 insns structural/exact (0, 3) objdiff 99.7619% regress 0 source update_icon_anm__Q33ipl5scene17MemoryCardManagerFv.3f21ddb4b4ba
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv | proven max reload with counter-first sum | 84/84 insns structural/exact (0, 3) objdiff 99.7619% regress 0 source update_icon_anm__Q33ipl5scene17MemoryCardManagerFv.bc6d4df961d3
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv | max reload uses s16 frame value | 84/84 insns structural/exact (0, 3) objdiff 99.7619% regress 0 source update_icon_anm__Q33ipl5scene17MemoryCardManagerFv.23b61e539645
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv | max reload comparison uses member counter | 84/84 insns structural/exact (0, 3) objdiff 99.7619% regress 0 source update_icon_anm__Q33ipl5scene17MemoryCardManagerFv.ad293da28da8
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv | max reload and frame increment through compound assignment | 84/84 insns structural/exact (0, 24) objdiff 98.333336% regress 0 source update_icon_anm__Q33ipl5scene17MemoryCardManagerFv.fe2b5196cb2d
update_icon_anm__Q33ipl5scene17MemoryCardManagerFv field reload register search
declaration block:
      CardIcons* icons = reinterpret_cast<CardIcons*>(memorycard::getIconStateArray());
      CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
      int slot = 0;
start (0, 3)
best (0, 3) after 6 builds; source restored; best order was:
    CardIcons* icons = reinterpret_cast<CardIcons*>(memorycard::getIconStateArray());
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    int slot = 0;

update_icon_anm__Q33ipl5scene17MemoryCardManagerFv | delta and current frame own separate typed locals | 84/84 insns structural/exact (0, 0) objdiff 100.0% regress 0 source update_icon_anm__Q33ipl5scene17MemoryCardManagerFv.97731112d87f
Committed exact update_icon_anm c7843729 after quick gate PASS, instruction count 84/84 and ctxdiff diffs 0; volatile field isolated from all other units. Protected newly exact function in subsequent trials.
START create_icon__Q33ipl5scene17MemoryCardManagerFUcs origin/main eecf16f01e322dc36702d4fdd7f6cda7a96af2dc upstream source UNCHANGED
src 0xcc base 0xcc insns 51/51
diffs 19: [16, 17, 19, 20, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 34, 36, 38, 39, 42]
    16 M li r9, 0
       B li r8, 0
    17 M lwz r8, 8(r4)
       B lwz r9, 8(r4)
    19 M slwi r5, r8, 6
       B slwi r6, r9, 6
    20 M mulli r6, r31, 0x1fc0
       B mulli r5, r31, 0x1fc0
    22 M add r3, r3, r6
       B mulli r4, r9, 0x15c
    23 M mulli r4, r8, 0x15c
       B add r5, r3, r5
    24 M add r5, r5, r3
       B add r3, r4, r0
    25 M add r3, r4, r0
       B add r4, r6, r5
    26 M lhz r4, 0x10(r5)
       B lha r5, 0x10e8(r3)
    27 M lha r3, 0x10e8(r3)
       B extsh r0, r8
    28 M extsh r0, r9
       B lhz r3, 0x10(r4)
    29 M addi r9, r9, 1
       B slwi r0, r0, 1
    30 M slwi r0, r0, 1
       B addi r8, r8, 1
    31 M sraw r0, r4, r0
       B sraw r0, r3, r0
    34 M cmpw r3, r7
       B cmpw r5, r7
    36 M extsh r0, r9
       B extsh r0, r8
    38 M ble -40
       B ble -44
    39 M extsh r6, r9
       B extsh r6, r8
    42 M extsh r5, r8
       B extsh r5, r9

create_icon structural diagnosis: 51/51, same frame and branches; target loads counter before frame bits, and uses separate row then cell address. File and frame loop registers differ.
create_icon__Q33ipl5scene17MemoryCardManagerFUcs | frame declared before file selection | 51/51 insns structural/exact (6, 14) objdiff 87.15686% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.98ceff308ad1
create_icon__Q33ipl5scene17MemoryCardManagerFUcs | animation counter snapshot precedes frame-bit access | 51/51 insns structural/exact (7, 19) objdiff 86.17647% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.479cec4baa49
create_icon__Q33ipl5scene17MemoryCardManagerFUcs | slot icon row bound explicitly for frame-bit access | 51/51 insns structural/exact (6, 19) objdiff 86.17647% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.543bb608ce00
create_icon__Q33ipl5scene17MemoryCardManagerFUcs register search after load/address trials
declaration block:
      memorycard::IconState (*icons)[0x7f] = reinterpret_cast<memorycard::IconState(*)[0x7f]>(memorycard::getIconStateArray());
      int total = 0;
      u32 file = mFile[slot][index].fileNo;
      s16 frame = 0;
start (6, 19)
improved (6, 14)
best (6, 14) after 12 builds; kept in source:
    memorycard::IconState (*icons)[0x7f] = reinterpret_cast<memorycard::IconState(*)[0x7f]>(memorycard::getIconStateArray());
    int total = 0;
    s16 frame = 0;
    u32 file = mFile[slot][index].fileNo;

START _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl origin/main eecf16f01e322dc36702d4fdd7f6cda7a96af2dc upstream source UNCHANGED
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

_create_icon structural diagnosis: 100/100, same stack; target splits icon row and column offsets through texture/TLUT calls, ours caches full destination pointer for RGB and TLUT. Typed row/helper boundaries before registers.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | file-cell row owns slot calculation across texture calls | 95/100 insns structural/exact (52, 84) objdiff 59.71% regress 0 source _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl.beb88dd5ccbd
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | icon-data row address before column selection | 100/100 insns structural/exact (16, 37) objdiff 87.55% regress 0 source _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl.9948301b7ec9
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | texture address formed inside typed inline accessor | 101/100 insns structural/exact (24, 66) objdiff 82.25% regress 0 source _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl.754262769f98
START getComment__Q33ipl5scene17MemoryCardManagerFUcsi origin/main eecf16f01e322dc36702d4fdd7f6cda7a96af2dc upstream source UNCHANGED
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

getComment structural diagnosis: 123/123, same stack and branches; twenty saved-register and trim-pointer differences. Scalar declaration order and encoded buffer lifetime are primary suspects.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | encoded byte view created after trimming bytes | 123/123 insns structural/exact (4, 30) objdiff 96.86992% regress 0 source getComment__Q33ipl5scene17MemoryCardManagerFUcsi.bfbcd935f334
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | read end initialized before write tail | 123/123 insns structural/exact (0, 21) objdiff 98.82114% regress 0 source getComment__Q33ipl5scene17MemoryCardManagerFUcsi.2363b911f339
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | decoded comment referenced through typed cell member | 113/123 insns structural/exact (32, 119) objdiff 85.032524% regress 0 source getComment__Q33ipl5scene17MemoryCardManagerFUcsi.6ea4e78966f9
START create_banner__Q33ipl5scene17MemoryCardManagerFUcs origin/main eecf16f01e322dc36702d4fdd7f6cda7a96af2dc upstream source UNCHANGED
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

create_banner structural diagnosis: 106/106, same stack; target reconstructs icon row+cell after validity checks, then separate destination row/column for each branch and TLUT. Scope boundaries matter before saved-register order.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | validity icon pointer scoped before banner selection pointer | 106/106 insns structural/exact (26, 64) objdiff 84.62264% regress 0 source create_banner__Q33ipl5scene17MemoryCardManagerFUcs.3d966b2a4a8b
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | file-cell row named across texture and palette calls | 97/106 insns structural/exact (81, 90) objdiff 63.103775% regress 0 source create_banner__Q33ipl5scene17MemoryCardManagerFUcs.4623b8707ffc
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | banner icon and row declared before validation with later assignment | 106/106 insns structural/exact (15, 70) objdiff 90.42453% regress 0 source create_banner__Q33ipl5scene17MemoryCardManagerFUcs.367dcbbcfe50
START getBlocks__Q33ipl5scene17MemoryCardManagerFUcs origin/main eecf16f01e322dc36702d4fdd7f6cda7a96af2dc upstream source UNCHANGED
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

getBlocks structural diagnosis: 25/25, same frame and operands; restore r11 materialized eight instructions before target. Test local result, typed row, and helper boundary.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | file and size materialized as meaningful scalar locals | 25/25 insns structural/exact (2, 9) objdiff 92.0% regress 0 source getBlocks__Q33ipl5scene17MemoryCardManagerFUcs.123d6096e0ad
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | directory row explicitly references slot | 25/25 insns structural/exact (2, 9) objdiff 92.0% regress 0 source getBlocks__Q33ipl5scene17MemoryCardManagerFUcs.e9e2c331b93d
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | block count read at typed inline accessor boundary | 25/25 insns structural/exact (2, 9) objdiff 91.0% regress 0 source getBlocks__Q33ipl5scene17MemoryCardManagerFUcs.3b918e446ca3
compareToken after structural fix: 124/124, five differences only at loop-entry invariant setup (A/Z bounds, signed delimiter, final position, zero). Remaining trials change real lower-case helper boundaries and token lifetimes.
NHTTPi_compareTokenN_HdrRecvBuf | lowercase conditional result owns named temporary | 125/124 insns structural/exact (30, 46) objdiff 92.201614% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.6a515d30cddf
NHTTPi_compareTokenN_HdrRecvBuf | ASCII upper-case test separated into inline predicate | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.a5b9bebd7c82
NHTTPi_compareTokenN_HdrRecvBuf | lowercase uses named signed bounds | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.8e0b888eaef8
NHTTPi_compareTokenN_HdrRecvBuf | lowercase compare owned by inline equality helper | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.32c01ab52618
NHTTPi_compareTokenN_HdrRecvBuf | loop guard assigns folded token once per comparison | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.072c89bd4d2a
NHTTPi_compareTokenN_HdrRecvBuf | loop body checks named folded operands before token termination | 124/124 insns structural/exact (68, 63) objdiff 57.64516% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.8f6477cdbaa8
NHTTPi_compareTokenN_HdrRecvBuf | lowercase keeps transformed character in positive conditional | 123/124 insns structural/exact (18, 48) objdiff 92.354836% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.ceb57b0b6549
NHTTPi_compareTokenN_HdrRecvBuf | word token snapshot follows each advancement | BUILD FAIL [1/1] MWCC build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.o
FAILED: [code=2] build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.o
build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nhttp/NHTTP_recvbuf.c -o build/43U/src/libs/RevoEX/src/nhttp && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.d build/43U/src/libs/RevoEX/src/nhttp/NHTTP_recvbuf.d
### mwcceppc.exe Compiler:
#    File: libs\RevoEX\src\nhttp\NHTTP_recvbuf.c
# ----------------------------------------------
#      82:     int tokenCharacter = *token;
#   Error:     ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator register search after entry-pointer reload boundary fix
declaration block:
              u16 i;
              u16 j;
              CandidateTextAnmPane* pane;
start (0, 53)
best (0, 53) after 6 builds; source restored; best order was:
            u16 i;
            u16 j;
            CandidateTextAnmPane* pane;

getComment__Q33ipl5scene17MemoryCardManagerFUcsi | leading scalar declarations preserve every assignment boundary | 123/123 insns structural/exact (0, 20) objdiff 98.94309% regress 0 source getComment__Q33ipl5scene17MemoryCardManagerFUcsi.45fdaa131dec
getComment__Q33ipl5scene17MemoryCardManagerFUcsi register search with scalar declaration block
declaration block:
      u32 file;
      const char* comments;
      const u8* encoded;
      char* tail;
      char* end;
      bool found;
      int count;
start (0, 20)
best (0, 20) after 24 builds; source restored; best order was:
    u32 file;
    const char* comments;
    const u8* encoded;
    char* tail;
    char* end;
    bool found;
    int count;

FINAL OPEN-FUNCTION COVERAGE (unique compiled source hashes):
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 99.830505% | 3 distinct compiled source attempts
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 99.830505% | 3 distinct compiled source attempts
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: 92.30769% | 3 distinct compiled source attempts
update_file_array__Q33ipl5scene17MemoryCardManagerFUc: 99.72222% | 0 distinct compiled source attempts | SKIPPED by explicit task: known r3/r4 tie
create_icon__Q33ipl5scene17MemoryCardManagerFUcs: 86.17647% | 3 distinct compiled source attempts
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: 87.55% | 3 distinct compiled source attempts
getComment__Q33ipl5scene17MemoryCardManagerFUcsi: 98.94309% | 4 distinct compiled source attempts
create_banner__Q33ipl5scene17MemoryCardManagerFUcs: 90.42453% | 3 distinct compiled source attempts
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs: 92.0% | 3 distinct compiled source attempts
calcFadein__Q33ipl5scene14SDChannelTitleFv: 97.87234% | 3 distinct compiled source attempts
initCalcFadeout__Q33ipl5scene14SDChannelTitleFv: 97.95918% | 3 distinct compiled source attempts
iplSDChannelTitle_startCopyProgress: 98.62791% | 3 distinct compiled source attempts
iplSDChannelTitle_updateCopyStart: 98.3421% | 3 distinct compiled source attempts
iplSDChannelTitle_flushSaveBeforeExit: 98.5946% | 6 distinct compiled source attempts
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator: 92.71023% | 3 distinct compiled source attempts
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator: 96.56481% | 3 distinct compiled source attempts
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv: 99.873566% | 3 distinct compiled source attempts
NHTTPi_compareTokenN_HdrRecvBuf: 87.59677% | 17 distinct compiled source attempts
All remaining owned functions have >=3 distinct compiled attempts except explicitly skipped update_file_array. Unmatched trials restored; only instruction-exact update_icon_anm source retained. Final gate will clean and rebuild all four units.
COUNT NOTE onGUIEvent__Q39textinput12candidatebox10UITextAreaFRQ39textinput3gui13PaneComponentUlPQ49textinput11nw4rmanager14TiEventHandler5Input: objdiff 100%, gate disassembler differences [(251, ('bge', -23279), ('bge', -21251)), (268, ('bgt', -23347), ('bgt', -21319))]; proper last-branch-operand normalization score (0, 0)
Final full clean gate PASS for all four units, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; regressions 0, forbidden 0, readability 0. Exact update_icon_anm after fresh build: 84/84 instructions, ctxdiff diffs 0, objdiff 100%.
