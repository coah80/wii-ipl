# ult25 ultra matching attempts

2026-10-03. Worktree data-d3, branch agent/w1003/sol-ult25-ultra, baseline32be36cb. Read owned AGENTS.md, ult25.md and full ezi-insight.md. Silent worker; no delegation, remotes changed, pushes, merges or rebases. Unslop applied to report. Historical bubblewrap startup failure absent.

Baseline libs/RVLMiddleware/eZiText/src/clib/zconvert: {'fuzzy_match_percent': 99.83696, 'total_code': '2208', 'matched_code': '1380', 'matched_code_percent': 62.5, 'total_data': '112', 'matched_data': '112', 'matched_data_percent': 100.0, 'total_functions': 4, 'matched_functions': 3, 'matched_functions_percent': 75.0, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)

Zi8ConvertUC2Key 99.565216%
src 0x33c base 0x33c insns 207/207
diffs 18: [7, 8, 14, 20, 26, 32, 40, 48, 92, 99, 112, 127, 165, 179, 186, 191, 198, 200]
     7 M mr r27, r5
       B mr r28, r5
     8 M li r28, 0
       B li r27, 0
    14 M mr r4, r27
       B mr r4, r28
    20 M add r3, r27, r0
       B add r3, r28, r0
    26 M mr r5, r27
       B mr r5, r28
    32 M mr r5, r27
       B mr r5, r28
    40 M mr r5, r27
       B mr r5, r28
    48 M mr r4, r27
       B mr r4, r28
    92 M clrlwi r28, r0, 0x10
       B clrlwi r27, r0, 0x10
    99 M clrlwi r4, r28, 0x10
       B clrlwi r4, r27, 0x10
   112 M clrlwi r28, r0, 0x10
       B clrlwi r27, r0, 0x10
   127 M mr r4, r27
       B mr r4, r28
   165 M clrlwi r28, r0, 0x18
       B clrlwi r27, r0, 0x18
   179 M lhzx r28, r4, r0
       B lhzx r27, r4, r0
   186 M clrlwi r0, r28, 0x10
       B clrlwi r0, r27, 0x10
   191 M mr r4, r27
       B mr r4, r28
   198 M mr r4, r27
       B mr r4, r28
   200 M mr r3, r28
       B mr r3, r27

Baseline libs/RVLMiddleware/eZiText/src/clib/zi8getc2: {'fuzzy_match_percent': 99.95064, 'total_code': '6888', 'matched_code': '6360', 'matched_code_percent': 92.334496, 'total_data': '332', 'matched_data': '332', 'matched_data_percent': 100.0, 'total_functions': 17, 'matched_functions': 15, 'matched_functions_percent': 88.2353, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)

Zi8GetDataSignature 99.347824%
src 0x114 base 0x114 insns 69/69
diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]
     5 M mr r27, r3
       B mr r28, r3
     7 M mr r28, r5
       B mr r29, r5
     9 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
    28 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
    32 M mr r29, r3
       B mr r27, r3
    33 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
    51 M mr r3, r27
       B mr r3, r28
    52 M mr r4, r29
       B mr r4, r27
    57 M stbx r3, r27, r0
       B stbx r3, r28, r0

Zi8IsDupWChar 99.36508%
src 0xfc base 0xfc insns 63/63
diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]
     5 M mr r27, r3
       B mr r28, r3
     7 M li r28, 0
       B li r27, 0
    14 M sth r27, 2(r31)
       B sth r28, 2(r31)
    25 M clrlwi r3, r27, 0x10
       B clrlwi r3, r28, 0x10
    30 M li r28, 1
       B li r27, 1
    41 M sthx r27, r31, r0
       B sthx r28, r31, r0
    49 M sth r27, 2(r31)
       B sth r28, 2(r31)
    56 M mr r3, r28
       B mr r3, r27

Baseline libs/RVLMiddleware/eZiText/src/clib/zi8pud2: {'fuzzy_match_percent': 99.81274, 'total_code': '2136', 'matched_code': '720', 'matched_code_percent': 33.707867, 'total_data': '120', 'matched_data': '48', 'matched_data_percent': 40.0, 'total_functions': 7, 'matched_functions': 6, 'matched_functions_percent': 85.71429, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)

Zi8MatchPUDdata_ZHS 99.717514%
src 0x584 base 0x588 insns 353/354
--- insert mine 15:15 base 15:16
  B   15 stw r31, 0x24(r1)

Baseline libs/RVLMiddleware/eZiText/src/clib/zi8uwd: {'fuzzy_match_percent': 99.91717, 'total_code': '2656', 'matched_code': '2192', 'matched_code_percent': 82.53012, 'total_data': '80', 'matched_data': '80', 'matched_data_percent': 100.0, 'total_functions': 4, 'matched_functions': 3, 'matched_functions_percent': 75.0, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)

Zi8_81480224 99.52586%
src 0x1d0 base 0x1d0 insns 116/116
diffs 9: [5, 16, 24, 46, 54, 55, 63, 67, 104]
     5 M mr r26, r3
       B mr r28, r3
    16 M cmpwi r26, 0
       B cmpwi r28, 0
    24 M lbz r25, 2(r26)
       B lbz r25, 2(r28)
    46 M lwz r28, 4(r30)
       B lwz r26, 4(r30)
    54 M blt 144
       B bgt 144
    55 M lbz r0, 2(r28)
       B lbz r0, 2(r26)
    63 M add r3, r28, r0
       B add r3, r0, r26
    67 M add r3, r26, r0
       B add r3, r0, r28
   104 M stw r26, 4(r29)
       B stw r28, 4(r29)

Baseline libs/RVLMiddleware/eZiText/src/clib/zidawg1: {'fuzzy_match_percent': 99.71154, 'total_code': '1664', 'matched_code': '888', 'matched_code_percent': 53.365387, 'total_data': '80', 'matched_data': '80', 'matched_data_percent': 100.0, 'total_functions': 6, 'matched_functions': 4, 'matched_functions_percent': 66.66667, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)

ZiDAWGgetCHARattribute 99.0%
src 0xf0 base 0xf0 insns 60/60
diffs 12: [5, 14, 18, 19, 20, 29, 31, 32, 36, 37, 42, 43]
     5 M mr r30, r3
       B mr r31, r3
    14 M clrlwi r31, r0, 0x18
       B clrlwi r30, r0, 0x18
    18 M clrlwi r31, r0, 0x18
       B clrlwi r30, r0, 0x18
    19 M clrlwi r3, r31, 0x18
       B clrlwi r3, r30, 0x18
    20 M lhz r0, 4(r30)
       B lhz r0, 4(r31)
    29 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18
    31 M lwz r3, 0xc(r30)
       B lwz r3, 0xc(r31)
    32 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18
    36 M lwz r3, 8(r30)
       B lwz r3, 8(r31)
    37 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18
    42 M lwz r3, 8(r30)
       B lwz r3, 8(r31)
    43 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18

ZiDAWGGetGraphInfo 99.55224%
src 0x218 base 0x218 insns 134/134
diffs 12: [5, 8, 10, 11, 85, 87, 94, 97, 98, 99, 102, 127]
     5 M mr r25, r3
       B mr r29, r3
     8 M mr r3, r25
       B mr r3, r29
    10 M mr r29, r3
       B mr r26, r3
    11 M li r26, 0
       B li r25, 0
    85 M add r3, r29, r3
       B add r3, r26, r3
    87 M add r26, r3, r0
       B add r25, r3, r0
    94 M add r3, r29, r3
       B add r3, r26, r3
    97 M stw r0, 0x338(r25)
       B stw r0, 0x338(r29)
    98 M lwz r0, 0x338(r25)
       B lwz r0, 0x338(r29)
    99 M cmplw r0, r29
       B cmplw r0, r26
   102 M stw r0, 0x338(r25)
       B stw r0, 0x338(r29)
   127 M mr r3, r26
       B mr r3, r25

Baseline libs/RVLMiddleware/eZiText/src/clib/zkokeyp: {'fuzzy_match_percent': 98.746155, 'total_code': '5200', 'matched_code': '332', 'matched_code_percent': 6.3846154, 'total_data': '180', 'matched_data': '96', 'matched_data_percent': 53.333336, 'total_functions': 7, 'matched_functions': 1, 'matched_functions_percent': 14.285715, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)

Zi8_8148302C 99.49152%
src 0xec base 0xec insns 59/59
diffs 6: [7, 12, 32, 34, 38, 49]
     7 M mr r27, r5
       B mr r29, r5
    12 M mr r5, r27
       B mr r5, r29
    32 M clrlwi r29, r0, 0x10
       B clrlwi r27, r0, 0x10
    34 M cmplw r29, r0
       B cmplw r27, r0
    38 M mr r4, r27
       B mr r4, r29
    49 M mr r4, r27
       B mr r4, r29

Zi8_81483264 98.902435%
src 0xa4 base 0xa4 insns 41/41
diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]
     6 M mr r30, r3
       B mr r31, r3
     8 M lwz r0, 0x24(r30)
       B lwz r0, 0x24(r31)
    17 M li r31, 0
       B li r30, 0
    20 M lwz r3, 0x24(r30)
       B lwz r3, 0x24(r31)
    21 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18
    24 M addi r31, r31, 1
       B addi r30, r30, 1
    25 M clrlwi r3, r31, 0x18
       B clrlwi r3, r30, 0x18
    26 M lbz r0, 0x1c(r30)
       B lbz r0, 0x1c(r31)

Zi8_81483308 99.13793%
src 0xe8 base 0xe8 insns 58/58
diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]
     7 M mr r29, r5
       B mr r30, r5
    22 M li r30, 0
       B li r29, 0
    26 M clrlwi r0, r30, 0x18
       B clrlwi r0, r29, 0x18
    33 M addi r30, r30, 1
       B addi r29, r29, 1
    34 M clrlwi r3, r30, 0x18
       B clrlwi r3, r29, 0x18
    39 M lbz r0, 0(r29)
       B lbz r0, 0(r30)
    42 M lbz r3, 0(r29)
       B lbz r3, 0(r30)
    44 M stb r0, 0(r29)
       B stb r0, 0(r30)
    50 M stb r0, 0(r29)
       B stb r0, 0(r30)

Zi8_814833F0 99.04256%
src 0xbc base 0xbc insns 47/47
diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]
     6 M mr r30, r3
       B mr r31, r3
    13 M lwz r0, 0x24(r30)
       B lwz r0, 0x24(r31)
    22 M li r31, 0
       B li r30, 0
    26 M lwz r3, 0x24(r30)
       B lwz r3, 0x24(r31)
    27 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18
    34 M addi r31, r31, 1
       B addi r30, r30, 1
    35 M clrlwi r3, r31, 0x18
       B clrlwi r3, r30, 0x18
    36 M lbz r0, 0x1c(r30)
       B lbz r0, 0x1c(r31)

Zi8_814834AC 99.3586%
src 0x560 base 0x55c insns 344/343
--- replace mine 9:10 base 9:10
  M    9 mr r25, r7
  B    9 mr r26, r7
--- delete mine 16:17 base 16:16
  M   16 clrlwi r0, r0, 0x18
--- replace mine 20:21 base 19:20
  M   20 mr r4, r25
  B   19 mr r4, r26
--- replace mine 36:37 base 35:36
  M   36 mr r6, r25
  B   35 mr r6, r26
--- replace mine 57:58 base 56:57
  M   57 mr r6, r25
  B   56 mr r6, r26
--- replace mine 98:99 base 97:98
  M   98 mr r5, r25
  B   97 mr r5, r26
--- replace mine 104:105 base 103:104
  M  104 mr r5, r25
  B  103 mr r5, r26
--- replace mine 112:113 base 111:112
  M  112 mr r4, r25
  B  111 mr r4, r26
--- replace mine 121:122 base 120:121
  M  121 mr r4, r25
  B  120 mr r4, r26
--- replace mine 129:130 base 128:129
  M  129 mr r5, r25
  B  128 mr r5, r26
--- replace mine 205:206 base 204:205
  M  205 add r3, r4, r3
  B  204 add r3, r3, r4
--- replace mine 212:213 base 211:212
  M  212 add r3, r4, r3
  B  211 add r3, r3, r4
--- replace mine 250:251 base 249:250
  M  250 li r26, 0
  B  249 li r25, 0
--- replace mine 253:254 base 252:253
  M  253 slwi r0, r26, 1
  B  252 slwi r0, r25, 1
--- replace mine 259:260 base 258:259
  M  259 slwi r3, r26, 1
  B  258 slwi r3, r25, 1
--- replace mine 272:273 base 271:272
  M  272 slwi r0, r26, 1
  B  271 slwi r0, r25, 1
--- replace mine 275:276 base 274:275
  M  275 mr r6, r25
  B  274 mr r6, r26
--- replace mine 279:280 base 278:279
  M  279 cmpw r0, r26
  B  278 cmpw r0, r25
--- replace mine 282:283 base 281:282
  M  282 slwi r0, r26, 1
  B  281 slwi r0, r25, 1
--- replace mine 291:292 base 290:291
  M  291 addi r26, r26, 1
  B  290 addi r25, r25, 1
--- replace mine 293:294 base 292:293
  M  293 cmpw r26, r0
  B  292 cmpw r25, r0
--- replace mine 321:322 base 320:321
  M  321 mr r6, r25
  B  320 mr r6, r26

Zi8GetKOcandidates 98.146484%
src 0xa7c base 0xa74 insns 671/669
--- delete mine 15:16 base 15:15
  M   15 li r0, 0
--- insert mine 27:27 base 26:28
  B   26 li r0, 0
  B   27 stw r0, 0x24(r1)
--- replace mine 28:31 base 29:30
  M   28 stw r3, 0x24(r1)
  M   29 li r0, 0
  M   30 stw r0, 0x20(r1)
  B   29 stw r3, 0x20(r1)
--- replace mine 53:55 base 52:53
  M   53 mr r4, r3
  M   54 stw r4, 0x34(r1)
  B   52 stw r3, 0x34(r1)
--- replace mine 63:65 base 61:63
  M   63 lwz r0, 0x34(r1)
  M   64 cmpwi r0, 0
  B   61 lwz r4, 0x34(r1)
  B   62 cmpwi r4, 0
--- replace mine 80:82 base 78:80
  M   80 lwz r4, 0x18(r31)
  M   81 sth r0, 0(r4)
  B   78 lwz r3, 0x18(r31)
  B   79 sth r0, 0(r3)
--- replace mine 86:88 base 84:86
  M   86 lbz r3, 0x14(r31)
  M   87 cmpwi r3, 0
  B   84 lbz r0, 0x14(r31)
  B   85 cmpwi r0, 0
--- replace mine 95:97 base 93:95
  M   95 clrlwi r4, r3, 0x10
  M   96 cmplwi r4, 0xffff
  B   93 clrlwi r5, r3, 0x10
  B   94 cmplwi r5, 0xffff
--- insert mine 98:98 base 96:98
  B   96 lhz r4, 0x18(r1)
  B   97 slwi r3, r4, 3
--- replace mine 99:106 base 99:104
  M   99 slwi r4, r0, 3
  M  100 lhz r0, 0x18(r1)
  M  101 add r3, r28, r4
  M  102 add r3, r0, r3
  M  103 lbz r4, 4(r3)
  M  104 rlwinm r3, r4, 0, 0x1c, 0x1c
  M  105 cmpwi r3, 0
  B   99 add r0, r3, r0
  B  100 add r3, r0, r28
  B  101 lbz r0, 4(r3)
  B  102 rlwinm r4, r0, 0, 0x1c, 0x1c
  B  103 cmpwi r4, 0
--- replace mine 108:112 base 106:110
  M  108 slwi r0, r0, 3
  M  109 lhz r3, 0x18(r1)
  M  110 add r0, r28, r0
  M  111 add r3, r3, r0
  B  106 slwi r3, r0, 3
  B  107 lhz r0, 0x18(r1)
  B  108 add r0, r3, r0
  B  109 add r3, r0, r28
--- insert mine 113:113 base 111:119
  B  111 lhz r0, 0x18(r1)
  B  112 slwi r3, r0, 3
  B  113 lhz r0, 0x18(r1)
  B  114 add r0, r3, r0
  B  115 add r4, r0, r28
  B  116 lbz r3, 4(r4)
  B  117 clrlwi r0, r3, 0x1e
  B  118 slwi r5, r0, 0x10
--- replace mine 114:121 base 120:121
  M  114 slwi r0, r4, 3
  M  115 lhz r3, 0x18(r1)
  M  116 add r0, r28, r0
  M  117 add r3, r3, r0
  M  118 lbz r0, 4(r3)
  M  119 clrlwi r5, r0, 0x1e
  M  120 slwi r4, r5, 0x10
  B  120 slwi r3, r4, 3
--- replace mine 122:126 base 122:124
  M  122 slwi r0, r0, 3
  M  123 lhz r3, 0x18(r1)
  M  124 add r0, r28, r0
  M  125 add r3, r3, r0
  B  122 add r0, r3, r0
  B  123 add r3, r0, r28
--- replace mine 128:131 base 126:129
  M  128 or r4, r4, r0
  M  129 or r0, r6, r4
  M  130 stw r0, 0x28(r1)
  B  126 or r0, r5, r0
  B  127 or r4, r6, r0
  B  128 stw r4, 0x28(r1)
--- replace mine 132:135 base 130:133
  M  132 addi r3, r3, -1
  M  133 clrlwi r0, r3, 0x18
  M  134 stb r0, 0xe(r1)
  B  130 addi r0, r3, -1
  B  131 clrlwi r3, r0, 0x18
  B  132 stb r3, 0xe(r1)
--- replace mine 143:145 base 141:143
  M  143 slwi r4, r0, 1
  M  144 lhzx r3, r3, r4
  B  141 slwi r0, r0, 1
  B  142 lhzx r3, r3, r0
--- replace mine 149:150 base 147:148
  M  149 lhz r5, 0x18(r1)
  B  147 lhz r4, 0x18(r1)
--- replace mine 153:154 base 151:152
  M  153 slwi r4, r0, 8
  B  151 slwi r3, r0, 8
--- replace mine 155:158 base 153:156
  M  155 clrlwi r3, r0, 0x10
  M  156 or r0, r4, r3
  M  157 cmpw r5, r0
  B  153 clrlwi r0, r0, 0x10
  B  154 or r3, r3, r0
  B  155 cmpw r4, r3
--- replace mine 160:162 base 158:160
  M  160 addi r3, r3, -1
  M  161 stb r3, 0xe(r1)
  B  158 addi r0, r3, -1
  B  159 stb r0, 0xe(r1)
--- replace mine 163:165 base 161:163
  M  163 addi r0, r3, 1
  M  164 stb r0, 0xd(r1)
  B  161 addi r3, r3, 1
  B  162 stb r3, 0xd(r1)
--- replace mine 171:175 base 169:173
  M  171 clrlwi r3, r0, 0x18
  M  172 stb r3, 0xe(r1)
  M  173 li r0, 1
  M  174 stb r0, 0xd(r1)
  B  169 clrlwi r0, r0, 0x18
  B  170 stb r0, 0xe(r1)
  B  171 li r3, 1
  B  172 stb r3, 0xd(r1)
--- replace mine 180:183 base 178:181
  M  180 lbz r4, 0x14(r31)
  M  181 addi r0, r4, -1
  M  182 clrlwi r0, r0, 0x18
  B  178 lbz r3, 0x14(r31)
  B  179 addi r4, r3, -1
  B  180 clrlwi r0, r4, 0x18
--- replace mine 191:195 base 189:193
  M  191 lbz r3, 0(r29)
  M  192 clrlwi r0, r3, 0x10
  M  193 clrlwi r0, r0, 0x1b
  M  194 slwi r6, r0, 8
  B  189 lbz r0, 0(r29)
  B  190 clrlwi r3, r0, 0x10
  B  191 clrlwi r0, r3, 0x1b
  B  192 slwi r0, r0, 8
--- replace mine 196:199 base 194:199
  M  196 or r4, r6, r5
  M  197 clrlwi r4, r4, 0x10
  M  198 sth r4, 0x18(r1)
  B  194 or r4, r0, r5
  B  195 clrlwi r3, r4, 0x10
  B  196 sth r3, 0x18(r1)
  B  197 lhz r3, 0x18(r1)
  B  198 slwi r3, r3, 3
--- replace mine 200:206 base 200:204
  M  200 slwi r3, r0, 3
  M  201 lhz r0, 0x18(r1)
  M  202 add r3, r28, r3
  M  203 add r3, r0, r3
  M  204 lbz r3, 7(r3)
  M  205 clrlwi r0, r3, 0x10
  B  200 add r0, r3, r0
  B  201 add r3, r0, r28
  B  202 lbz r0, 7(r3)
  B  203 clrlwi r0, r0, 0x10
--- replace mine 207:212 base 205:210
  M  207 lhz r0, 0x18(r1)
  M  208 slwi r3, r0, 3
  M  209 lhz r0, 0x18(r1)
  M  210 add r3, r28, r3
  M  211 add r3, r0, r3
  B  205 lhz r3, 0x18(r1)
  B  206 slwi r0, r3, 3
  B  207 lhz r3, 0x18(r1)
  B  208 add r0, r0, r3
  B  209 add r3, r0, r28
--- replace mine 493:495 base 491:493
  M  493 li r0, 1
  M  494 stb r0, 8(r1)
  B  491 li r3, 1
  B  492 stb r3, 8(r1)
--- replace mine 506:508 base 504:506
  M  506 li r0, 0
  M  507 stb r0, 0xb(r1)
  B  504 li r3, 0
  B  505 stb r3, 0xb(r1)
--- replace mine 509:510 base 507:508
  M  509 lbz r4, 0xb(r1)
  B  507 lbz r0, 0xb(r1)
--- replace mine 511:513 base 509:511
  M  511 lbzx r3, r3, r4
  M  512 clrlwi r3, r3, 0x18
  B  509 lbzx r3, r3, r0
  B  510 clrlwi r5, r3, 0x18
--- replace mine 514:517 base 512:515
  M  514 lbz r0, 0xb(r1)
  M  515 lbzx r4, r4, r0
  M  516 cmplw r3, r4
  B  512 lbz r3, 0xb(r1)
  B  513 lbzx r0, r4, r3
  B  514 cmplw r5, r0
--- replace mine 522:524 base 520:522
  M  522 addi r3, r3, 1
  M  523 stb r3, 0xb(r1)
  B  520 addi r0, r3, 1
  B  521 stb r0, 0xb(r1)
--- replace mine 525:530 base 523:528
  M  525 lbz r3, 0xc(r31)
  M  526 srwi r0, r3, 0x1f
  M  527 add r0, r0, r3
  M  528 srawi r3, r0, 1
  M  529 cmpw r4, r3
  B  523 lbz r0, 0xc(r31)
  B  524 srwi r3, r0, 0x1f
  B  525 add r0, r3, r0
  B  526 srawi r0, r0, 1
  B  527 cmpw r4, r0
--- insert mine 531:531 base 529:551
  B  529 lbz r3, 8(r1)
  B  530 cmpwi r3, 0
  B  531 beq 80
  B  532 lbz r6, 0xc(r31)
  B  533 srwi r3, r6, 0x1f
  B  534 clrlwi r0, r6, 0x1f
  B  535 xor r0, r0, r3
  B  536 subf r0, r3, r0
  B  537 cmpwi r0, 0
  B  538 beq 52
  B  539 lbz r4, 0xb(r1)
  B  540 addi r3, r1, 0x38
  B  541 lbzx r0, r3, r4
  B  542 rlwinm r5, r0, 0, 0x18, 0x1b
  B  543 lwz r4, 0x1c(r1)
  B  544 lbz r3, 0xb(r1)
  B  545 lbzx r0, r4, r3
  B  546 rlwinm r0, r0, 0, 0x18, 0x1b
  B  547 cmpw r5, r0
  B  548 beq 12
  B  549 li r3, 0
  B  550 stb r3, 8(r1)
--- delete mine 533:555 base 553:553
  M  533 beq 80
  M  534 lbz r3, 0xc(r31)
  M  535 srwi r4, r3, 0x1f
  M  536 clrlwi r0, r3, 0x1f
  M  537 xor r3, r0, r4
  M  538 subf r6, r4, r3
  M  539 cmpwi r6, 0
  M  540 beq 52
  M  541 lbz r0, 0xb(r1)
  M  542 addi r3, r1, 0x38
  M  543 lbzx r0, r3, r0
  M  544 rlwinm r5, r0, 0, 0x18, 0x1b
  M  545 lwz r4, 0x1c(r1)
  M  546 lbz r0, 0xb(r1)
  M  547 lbzx r0, r4, r0
  M  548 rlwinm r3, r0, 0, 0x18, 0x1b
  M  549 cmpw r5, r3
  M  550 beq 12
  M  551 li r0, 0
  M  552 stb r0, 8(r1)
  M  553 lbz r3, 8(r1)
  M  554 cmpwi r3, 0
--- replace mine 558:561 base 556:559
  M  558 clrlwi r0, r0, 0x1f
  M  559 xor r3, r0, r4
  M  560 subf r0, r4, r3
  B  556 clrlwi r3, r0, 0x1f
  B  557 xor r0, r3, r4
  B  558 subf r0, r4, r0
--- replace mine 565:567 base 563:568
  M  565 lbzx r0, r3, r0
  M  566 clrlwi r3, r0, 0x1c
  B  563 lbzx r3, r3, r0
  B  564 clrlwi r0, r3, 0x1c
  B  565 cmpwi r0, 0
  B  566 beq 20
  B  567 lbz r3, 0xa(r1)
--- replace mine 568:569 base 569:571
  M  568 beq 20
  B  569 beq 300
  B  570 b 96
--- delete mine 571:575 base 573:573
  M  571 beq 300
  M  572 b 96
  M  573 lbz r3, 0xa(r1)
  M  574 cmpwi r3, 0
--- replace mine 580:584 base 578:582
  M  580 lwz r4, 0x1c(r1)
  M  581 lbz r3, 0xb(r1)
  M  582 lbzx r5, r4, r3
  M  583 rlwinm r0, r5, 0, 0x18, 0x1b
  B  578 lwz r3, 0x1c(r1)
  B  579 lbz r4, 0xb(r1)
  B  580 lbzx r0, r3, r4
  B  581 rlwinm r0, r0, 0, 0x18, 0x1b
--- replace mine 590:591 base 588:592
  M  590 lbz r0, 0xa(r1)
  B  588 lbz r3, 0xa(r1)
  B  589 cmpwi r3, 0
  B  590 beq 16
  B  591 lbz r0, 0(r30)
--- delete mine 592:595 base 593:593
  M  592 beq 16
  M  593 lbz r4, 0(r30)
  M  594 cmpwi r4, 0
--- replace mine 600:602 base 598:600
  M  600 addi r0, r3, -1
  M  601 sth r0, 0x10(r1)
  B  598 addi r3, r3, -1
  B  599 sth r3, 0x10(r1)
--- replace mine 603:605 base 601:603
  M  603 lbz r3, 0(r30)
  M  604 cmpwi r3, 0
  B  601 lbz r0, 0(r30)
  B  602 cmpwi r0, 0
--- replace mine 615:619 base 613:617
  M  615 slwi r0, r0, 3
  M  616 lwz r3, 0x30(r1)
  M  617 add r0, r28, r0
  M  618 add r3, r3, r0
  B  613 slwi r3, r0, 3
  B  614 lwz r0, 0x30(r1)
  B  615 add r0, r3, r0
  B  616 add r3, r0, r28
--- replace mine 620:622 base 618:620
  M  620 clrlwi r0, r0, 0x10
  M  621 slwi r4, r0, 8
  B  618 clrlwi r3, r0, 0x10
  B  619 slwi r4, r3, 8
--- replace mine 623:627 base 621:625
  M  623 slwi r0, r0, 3
  M  624 lwz r3, 0x30(r1)
  M  625 add r0, r28, r0
  M  626 add r3, r3, r0
  B  621 slwi r3, r0, 3
  B  622 lwz r0, 0x30(r1)
  B  623 add r0, r3, r0
  B  624 add r3, r0, r28
--- replace mine 629:637 base 627:635
  M  629 clrlwi r6, r0, 0x10
  M  630 lwz r5, 0x18(r31)
  M  631 lbz r4, 0xc(r1)
  M  632 clrlwi r3, r4, 0x18
  M  633 slwi r0, r3, 1
  M  634 sthx r6, r5, r0
  M  635 addi r0, r4, 1
  M  636 stb r0, 0xc(r1)
  B  627 clrlwi r5, r0, 0x10
  B  628 lwz r4, 0x18(r31)
  B  629 lbz r3, 0xc(r1)
  B  630 clrlwi r0, r3, 0x18
  B  631 slwi r0, r0, 1
  B  632 sthx r5, r4, r0
  B  633 addi r3, r3, 1
  B  634 stb r3, 0xc(r1)
--- replace mine 638:643 base 636:641
  M  638 addi r3, r3, 1
  M  639 stb r3, 0x21(r31)
  M  640 clrlwi r3, r3, 0x18
  M  641 lbz r0, 0x1c(r31)
  M  642 cmplw r3, r0
  B  636 addi r0, r3, 1
  B  637 stb r0, 0x21(r31)
  B  638 clrlwi r0, r0, 0x18
  B  639 lbz r4, 0x1c(r31)
  B  640 cmplw r0, r4
--- replace mine 646:648 base 644:646
  M  646 lwz r4, 0x30(r1)
  M  647 addi r0, r4, 1
  B  644 lwz r3, 0x30(r1)
  B  645 addi r0, r3, 1
--- replace mine 654:657 base 652:655
  M  654 addi r3, r3, 1
  M  655 stb r3, 0xa(r1)
  M  656 clrlwi r0, r3, 0x18
  B  652 addi r0, r3, 1
  B  653 stb r0, 0xa(r1)
  B  654 clrlwi r0, r0, 0x18

Baseline libs/RVLMiddleware/eZiText/src/clib/zmtkey: {'fuzzy_match_percent': 99.84657, 'total_code': '2216', 'matched_code': '1488', 'matched_code_percent': 67.14801, 'total_data': '60', 'matched_data': '60', 'matched_data_percent': 100.0, 'total_functions': 4, 'matched_functions': 3, 'matched_functions_percent': 75.0, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)

Zi8getKeyLayout 99.53297%
src 0x2d8 base 0x2d8 insns 182/182
diffs 16: [5, 11, 21, 27, 69, 74, 75, 78, 85, 90, 91, 94, 125, 126, 130, 146]
     5 M mr r26, r3
       B mr r27, r3
    11 M clrlwi r3, r26, 0x18
       B clrlwi r3, r27, 0x18
    21 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    27 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    69 M clrlwi r3, r26, 0x18
       B clrlwi r3, r27, 0x18
    74 M mr r27, r3
       B mr r26, r3
    75 M clrlwi r0, r27, 0x10
       B clrlwi r0, r26, 0x10
    78 M clrlwi r3, r26, 0x18
       B clrlwi r3, r27, 0x18
    85 M clrlwi r3, r26, 0x18
       B clrlwi r3, r27, 0x18
    90 M mr r27, r3
       B mr r26, r3
    91 M clrlwi r0, r27, 0x10
       B clrlwi r0, r26, 0x10
    94 M clrlwi r3, r26, 0x18
       B clrlwi r3, r27, 0x18
   125 M li r27, 0
       B li r26, 0
   126 M mr r31, r27
       B mr r31, r26
   130 M add r27, r27, r0
       B add r26, r26, r0
   146 M clrlwi r0, r27, 0x10
       B clrlwi r0, r26, 0x10

Baseline libs/RVLMiddleware/eZiText/src/clib/zoemdata: {'fuzzy_match_percent': 98.934425, 'total_code': '976', 'matched_code': '208', 'matched_code_percent': 21.311476, 'total_data': '60', 'matched_data': '60', 'matched_data_percent': 100.0, 'total_functions': 3, 'matched_functions': 2, 'matched_functions_percent': 66.66667, 'total_units': 1}
POOL IDENTICAL up to 0 (mine=0 base=0)

Zi8MatchOEMdata 98.645836%
src 0x300 base 0x300 insns 192/192
diffs 47: [5, 6, 9, 12, 13, 18, 19, 20, 21, 23, 26, 27, 28, 34, 41, 46, 54, 62, 69, 73]
     5 M mr r27, r3
       B mr r28, r3
     6 M mr r26, r4
       B mr r27, r4
     9 M mr r23, r7
       B mr r24, r7
    12 M mr r28, r10
       B mr r29, r10
    13 M li r24, 0
       B li r23, 0
    18 M stw r0, 0x328(r28)
       B stw r0, 0x328(r29)
    19 M lwz r29, 0x328(r28)
       B lwz r26, 0x328(r29)
    20 M lhz r0, 0x324(r28)
       B lhz r0, 0x324(r29)
    21 M cmpw r29, r0
       B cmpw r26, r0
    23 M lwz r0, 0x320(r28)
       B lwz r0, 0x320(r29)
    26 M clrlwi r3, r26, 0x18
       B clrlwi r3, r27, 0x18
    27 M addi r23, r23, -1
       B addi r24, r24, -1
    28 M clrlwi r0, r23, 0x10
       B clrlwi r0, r24, 0x10
    34 M clrlwi r0, r23, 0x10
       B clrlwi r0, r24, 0x10
    41 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    46 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    54 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    62 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
    69 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
    73 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
    79 M mr r5, r28
       B mr r5, r29
    83 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
    91 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
    94 M lbz r0, 0x1f(r28)
       B lbz r0, 0x1f(r29)
   101 M lhzx r0, r27, r0
       B lhzx r0, r28, r0
   107 M mr r6, r28
       B mr r6, r29
   119 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   122 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   129 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   134 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   137 M addi r29, r29, 1
       B addi r26, r26, 1
   138 M lhz r0, 0x324(r28)
       B lhz r0, 0x324(r29)
   139 M cmpw r29, r0
       B cmpw r26, r0
   142 M cmpwi r24, 0
       B cmpwi r23, 0
   144 M li r29, 0
       B li r26, 0
   145 M lhz r0, 0(r27)
       B lhz r0, 0(r28)
   149 M addi r29, r29, 1
       B addi r26, r26, 1
   150 M stw r29, 0x328(r28)
       B stw r26, 0x328(r29)
   159 M lhz r0, 0x324(r28)
       B lhz r0, 0x324(r29)
   160 M cmpw r29, r0
       B cmpw r26, r0
   162 M clrlwi r3, r29, 0x10
       B clrlwi r3, r26, 0x10
   164 M clrlwi r5, r23, 0x18
       B clrlwi r5, r24, 0x18
   165 M lwz r6, 0x32c(r28)
       B lwz r6, 0x32c(r29)
   166 M lwz r12, 0x320(r28)
       B lwz r12, 0x320(r29)
   172 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
   182 M li r24, 1
       B li r23, 1
   183 M li r29, 0
       B li r26, 0


## Zi8MatchPUDdata_ZHS POLICY store
Target8147F768 stw r31,0x24(r1), immediately after incoming workspace load lwz r31,0x6c(r1) and before fallback initialization. No lbz/lhz/lwz from0x24(r1) anywhere in function. Target has exactly this one slot reference:
/* 8147F768 0014FC88  93 E1 00 24 */	stw r31, 0x24(r1)
Plausible source is a named workspace view assigned but never used; allowed by ezi-insight POLICY for -opt off. Target CFG, calls and remaining353instructions already identical.
Attempt Zi8MatchPUDdata_ZHS #1: void workspace initialization before fallback. {"insns": [364, 354], "diffs": 275, "structural": 43, "exact": false, "first": [[6, ["mr", "r25, r4"], ["mr", "r24, r4"]], [7, ["mr", "r24, r5"], ["mr", "r23, r5"]], [8, ["mr", "r23, r6"], ["mr", "r22, r6"]]], "pct": 96.0113, "code": "720", "data": null}. Retained False.
Attempt Zi8MatchPUDdata_ZHS #2: last workspace local, assignment before fallback. {"insns": [364, 354], "diffs": 280, "structural": 58, "exact": false, "first": [[6, ["mr", "r25, r4"], ["mr", "r24, r4"]], [7, ["mr", "r24, r5"], ["mr", "r23, r5"]], [8, ["mr", "r23, r6"], ["mr", "r22, r6"]]], "pct": 95.97175, "code": "720", "data": null}. Retained False.
Attempt Zi8MatchPUDdata_ZHS #3: typed workspace used as the work view. {"insns": [386, 354], "diffs": 346, "structural": 77, "exact": false, "first": [[6, ["mr", "r27, r4"], ["mr", "r24, r4"]], [7, ["mr", "r25, r5"], ["mr", "r23, r5"]], [8, ["mr", "r24, r6"], ["mr", "r22, r6"]]], "pct": 88.86723, "code": "720", "data": null}. Retained False.
Attempt Zi8MatchPUDdata_ZHS #4: int fallback = 0; ziPtr separate workspace assignment. {"insns": [364, 354], "diffs": 275, "structural": 43, "exact": false, "first": [[6, ["mr", "r25, r4"], ["mr", "r24, r4"]], [7, ["mr", "r24, r5"], ["mr", "r23, r5"]], [8, ["mr", "r23, r6"], ["mr", "r22, r6"]]], "pct": 96.0113, "code": "720", "data": null}. Retained False.
Attempt Zi8MatchPUDdata_ZHS #5: int fallback = 0; struct __zi8_work_data_s* separate workspace assignment. {"insns": [364, 354], "diffs": 275, "structural": 43, "exact": false, "first": [[6, ["mr", "r25, r4"], ["mr", "r24, r4"]], [7, ["mr", "r24, r5"], ["mr", "r23, r5"]], [8, ["mr", "r23, r6"], ["mr", "r22, r6"]]], "pct": 96.0113, "code": "720", "data": null}. Retained False.
Attempt Zi8MatchPUDdata_ZHS #6: ziU8* byteOutput; ziPtr separate workspace assignment. {"insns": [364, 354], "diffs": 280, "structural": 58, "exact": false, "first": [[6, ["mr", "r25, r4"], ["mr", "r24, r4"]], [7, ["mr", "r24, r5"], ["mr", "r23, r5"]], [8, ["mr", "r23, r6"], ["mr", "r22, r6"]]], "pct": 95.97175, "code": "720", "data": null}. Retained False.
Attempt Zi8MatchPUDdata_ZHS #7: ziU8* byteOutput; struct __zi8_work_data_s* separate workspace assignment. {"insns": [364, 354], "diffs": 280, "structural": 58, "exact": false, "first": [[6, ["mr", "r25, r4"], ["mr", "r24, r4"]], [7, ["mr", "r24, r5"], ["mr", "r23, r5"]], [8, ["mr", "r23, r6"], ["mr", "r22, r6"]]], "pct": 95.97175, "code": "720", "data": null}. Retained False.
Attempt Zi8MatchPUDdata_ZHS #8: matching state keeps workspace snapshot and fallback, workspace first=False. {"insns": [354, 354], "diffs": 0, "structural": 0, "exact": true, "first": [], "pct": 100.0, "code": "2136", "data": "120"}. Retained True.

## Prior-art and data audit
Read current ult8 log, ezi1/ezi2 untracked logs via read-only stash objects, orch/ult9-progress ult9 log and effort-policy. Public reference index has no matching entry for owned functions. All eight empty pools identical. Six units already have100%data. PUD extabindex72-byte gap follows the missing one-instruction home store. Korean extabindex84-byte gap follows sizes0x560 vs0x55c and0xa7c vs0xa74; switch table40bytes and unwind56bytes already match. No name/extent correction justified.

## Target never-read stack-store sweep
Zi8ConvertUC2Key:
No never-read scalar stack slot.
Zi8GetDataSignature:
No never-read scalar stack slot.
Zi8IsDupWChar:
No never-read scalar stack slot.
Zi8MatchPUDdata_ZHS:
/* 8147F768 0014FC88  93 E1 00 24 */	stw r31, 0x24(r1)
Zi8_81480224:
No never-read scalar stack slot.
ZiDAWGgetCHARattribute:
No never-read scalar stack slot.
ZiDAWGGetGraphInfo:
No never-read scalar stack slot.
Zi8_8148302C:
No never-read scalar stack slot.
Zi8_81483264:
No never-read scalar stack slot.
Zi8_81483308:
No never-read scalar stack slot.
Zi8_814833F0:
No never-read scalar stack slot.
Zi8_814834AC:
/* 814834E8 00153A08  90 01 00 1C */	stw r0, 0x1c(r1)
/* 814834EC 00153A0C  98 01 00 20 */	stb r0, 0x20(r1)
Zi8GetKOcandidates:
/* 81483A40 00153F60  90 01 00 38 */	stw r0, 0x38(r1)
/* 81483A44 00153F64  98 01 00 3C */	stb r0, 0x3c(r1)
/* 81483A84 00153FA4  98 01 00 09 */	stb r0, 0x9(r1)
Zi8getKeyLayout:
No never-read scalar stack slot.
Zi8MatchOEMdata:
No never-read scalar stack slot.
PUD accepted trial8 groups fallback and workspace view as matching state fields. Field order maps fallback0x20/workspace0x24; stw r31,0x24 now emitted. All354instructions exact; exact-name objdiff100%; data120/120. Ordinary local workspace trials1-7 displace wordSize and are restored. No volatile, assembly, fabricated offset or other-unit changes.

First full nonquick PUD gate:
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2] objdiff: code 2136/2136 data 120/120 functions 7/7 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2] instruction-exact functions: 7/7
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2]   section .text size 2136 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2]   section extab size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2]   section extabindex size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2] baseline: code 720/2136 data 48 functions 6 fuzzy 99.8127
regressions vs baseline: 0
global matched_code_percent: 91.95013 -> 91.99740
global fuzzy_match_percent: 99.71971 -> 99.71984
global complete_code_percent: 74.84181 -> 74.84181
global matched_data_percent: 99.77803 -> 99.78196
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Zi8_814834AC structural-first
Fresh fork fetch: owned unit unchanged. CFG/calls match. Frame0x50; 344/343instructions. Target stw r0,0x1c and stb r0,0x20 clear real five-byte key buffer passed to pack helper. Both stores exist in source; extra clrlwi from chained32-bit return conversion. Also character-address operands at targetindices204/211 and workspace/candidate saved-register swap. New attempts focus comma-expression zero initialization and narrow seed, not earlier split-clear or zeroed-array probes.
Attempt Zi8_814834AC #1: one comma expression for real packed key stores. {"insns": [345, 343], "diffs": 332, "structural": 38, "exact": false, "first": [[9, ["mr", "r25, r7"], ["mr", "r26, r7"]], [12, ["stb", "r0, 0xd(r1)"], ["stb", "r0, 9(r1)"]], [15, ["stw", "r0, 0x20(r1)"], ["stw", "r0, 0x1c(r1)"]]], "pct": 98.9621, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_814834AC #2: suffix assigned from sequenced literal zero. {"insns": [347, 343], "diffs": 329, "structural": 40, "exact": false, "first": [[9, ["mr", "r25, r7"], ["mr", "r26, r7"]], [12, ["stb", "r0, 0xd(r1)"], ["stb", "r0, 9(r1)"]], [15, ["stw", "r0, 0x20(r1)"], ["stw", "r0, 0x1c(r1)"]]], "pct": 98.379005, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_814834AC #3: suffix assignment with explicitly byte typed sequenced zero. {"insns": [346, 343], "diffs": 331, "structural": 39, "exact": false, "first": [[9, ["mr", "r25, r7"], ["mr", "r26, r7"]], [12, ["stb", "r0, 0xd(r1)"], ["stb", "r0, 9(r1)"]], [15, ["stw", "r0, 0x20(r1)"], ["stw", "r0, 0x1c(r1)"]]], "pct": 98.670555, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_814834AC #4: packed key word native unsigned int in chained zero. {"insns": [344, 343], "diffs": 329, "structural": 1, "exact": false, "first": [[9, ["mr", "r25, r7"], ["mr", "r26, r7"]], [16, ["clrlwi", "r0, r0, 0x18"], ["stb", "r0, 0x20(r1)"]], [17, ["stb", "r0, 0x20(r1)"], ["li", "r3, 0x64"]]], "pct": 99.3586, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_814834AC #5: packed key word native signed int in chained zero. {"insns": [344, 343], "diffs": 329, "structural": 1, "exact": false, "first": [[9, ["mr", "r25, r7"], ["mr", "r26, r7"]], [16, ["clrlwi", "r0, r0, 0x18"], ["stb", "r0, 0x20(r1)"]], [17, ["stb", "r0, 0x20(r1)"], ["li", "r3, 0x64"]]], "pct": 99.3586, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_814834AC #6: packed struct initialized with key buffer separate from filter metadata. {"insns": [343, 343], "diffs": 60, "structural": 37, "exact": false, "first": [[9, ["mr", "r25, r7"], ["mr", "r26, r7"]], [10, ["li", "r0, 0"], ["li", "r27, 0"]], [11, ["stw", "r0, 8(r1)"], ["li", "r0, 0"]]], "pct": 97.78717, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_814834AC #7: packed union initialized with key buffer separate from filter metadata. {"insns": [343, 343], "diffs": 60, "structural": 37, "exact": false, "first": [[9, ["mr", "r25, r7"], ["mr", "r26, r7"]], [10, ["li", "r0, 0"], ["li", "r27, 0"]], [11, ["stw", "r0, 8(r1)"], ["li", "r0, 0"]]], "pct": 97.78717, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_814834AC #8: array initializer after counters with key buffer separate from filter metadata. {"insns": [347, 343], "diffs": 342, "structural": 47, "exact": false, "first": [[5, ["mr", "r31, r1"], ["mr", "r31, r3"]], [6, ["mr", "r30, r3"], ["mr", "r29, r4"]], [7, ["mr", "r28, r4"], ["mr", "r30, r5"]]], "pct": 95.63557, "code": "332", "data": "40"}. Retained False.

## Zi8GetKOcandidates structural-first
Fresh fork fetch: owned source unchanged. Target frame0x60,669instructions. Existing source671: extra li between real packed prefix/suffix stores, integer-to-pointer copy before wordTable store. Initial prefixCount/candidateIndex stores are0x24/r0 and0x20/r3. All initialization stores present, including0x9 inserted slot passed by address. Prior standalone return-prototype, count reorder and builtin clear probes rejected. New probes combine native table storage with counter-field types, then normal typed zero aggregate outside the metadata state.
Attempt Zi8GetKOcandidates #1: native table address plus unsigned prefix counter view. {"build_fail": "eware/eZiText/src/clib/zkokeyp.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVLMiddleware\\eZiText\\src\\clib\\zkokeyp.c\n# ------------------------------------------------------\n#     363:                                     if (++(ziS32)search.prefixCount < (ziS32)options->maxCount) { \n#   Error:                                                  ^^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n"}. Retained False.
Attempt Zi8GetKOcandidates #2: native table address plus actual int search counters and target field order. {"insns": [671, 669], "diffs": 639, "structural": 22, "exact": false, "first": [[15, ["li", "r0, 0"], ["stb", "r0, 0x3c(r1)"]], [16, ["stb", "r0, 0x3c(r1)"], ["li", "r0, 0"]], [17, ["li", "r0, 0"], ["stb", "r0, 0xe(r1)"]]], "pct": 98.11958, "code": "332", "data": "96"}. Retained False.
Attempt Zi8GetKOcandidates #3: native table address and initialized five-byte key aggregate. {"insns": [669, 669], "diffs": 230, "structural": 187, "exact": false, "first": [[8, ["li", "r0, 0"], ["lis", "r3, 1"]], [9, ["stw", "r0, 8(r1)"], ["addi", "r3, r3, -1"]], [10, ["stw", "r0, 0xc(r1)"], ["sth", "r3, 0x12(r1)"]]], "pct": 97.998505, "code": "332", "data": "96"}. Retained False.
Attempt Zi8GetKOcandidates #4: readonly word table with actual int counters. {"insns": [671, 669], "diffs": 639, "structural": 22, "exact": false, "first": [[15, ["li", "r0, 0"], ["stb", "r0, 0x3c(r1)"]], [16, ["stb", "r0, 0x3c(r1)"], ["li", "r0, 0"]], [17, ["li", "r0, 0"], ["stb", "r0, 0xe(r1)"]]], "pct": 98.11958, "code": "332", "data": "96"}. Retained False.

## Zi8_8148302C
Fresh origin fetch and source unchanged. Target never-read stack sweep found no missing home store. CFG/call sequence and instruction count agree. Remaining register ranking from baseline ctxdiff; new trials compare parameter pointer view forms and explicit narrow field access. Previously tried native workspace, loop updates, immutable-pointer and typed-scratch forms skipped.
Attempt Zi8_8148302C #1: generic readonly Korean table view in decoded character expression. {"insns": [59, 59], "diffs": 11, "structural": 0, "exact": false, "first": [[6, ["mr", "r27, r4"], ["mr", "r30, r4"]], [7, ["mr", "r28, r5"], ["mr", "r29, r5"]], [12, ["mr", "r5, r28"], ["mr", "r5, r29"]]], "pct": 99.067795, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_8148302C #2: decode low byte widened to halfword before OR, key narrowed at comparison. {"insns": [60, 59], "diffs": 30, "structural": 3, "exact": false, "first": [[7, ["mr", "r27, r5"], ["mr", "r29, r5"]], [12, ["mr", "r5, r27"], ["mr", "r5, r29"]], [16, ["b", 112], ["b", 108]]], "pct": 97.79661, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_8148302C #3: table record bytes read through a readonly pointer cast. {"insns": [59, 59], "diffs": 11, "structural": 0, "exact": false, "first": [[6, ["mr", "r27, r4"], ["mr", "r30, r4"]], [7, ["mr", "r28, r5"], ["mr", "r29, r5"]], [12, ["mr", "r5, r28"], ["mr", "r5, r29"]]], "pct": 99.067795, "code": "332", "data": "96"}. Retained False.

## Zi8_81483264
Fresh origin fetch and source unchanged. Target never-read stack sweep found no missing home store. CFG/call sequence and instruction count agree. Remaining register ranking from baseline ctxdiff; new trials compare parameter pointer view forms and explicit narrow field access. Previously tried native workspace, loop updates, immutable-pointer and typed-scratch forms skipped.
Attempt Zi8_81483264 #1: generic parameter view with const fields. {"insns": [41, 41], "diffs": 8, "structural": 0, "exact": false, "first": [[6, ["mr", "r30, r3"], ["mr", "r31, r3"]], [8, ["lwz", "r0, 0x24(r30)"], ["lwz", "r0, 0x24(r31)"]], [17, ["li", "r31, 0"], ["li", "r30, 0"]]], "pct": 98.902435, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_81483264 #2: mutable typed receiver, scalar field loads explicitly unsigned. {"insns": [42, 41], "diffs": 24, "structural": 3, "exact": false, "first": [[6, ["mr", "r30, r3"], ["mr", "r31, r3"]], [8, ["lwz", "r0, 0x24(r30)"], ["lwz", "r0, 0x24(r31)"]], [16, ["b", 76], ["b", 72]]], "pct": 96.46342, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_81483264 #3: array receiver view of fields within unchanged scratch loop. {"insns": [41, 41], "diffs": 8, "structural": 0, "exact": false, "first": [[6, ["mr", "r30, r3"], ["mr", "r31, r3"]], [8, ["lwz", "r0, 0x24(r30)"], ["lwz", "r0, 0x24(r31)"]], [17, ["li", "r31, 0"], ["li", "r30, 0"]]], "pct": 98.902435, "code": "332", "data": "96"}. Retained False.

## Zi8_81483308
Fresh origin fetch and source unchanged. Target never-read stack sweep found no missing home store. CFG/call sequence and instruction count agree. Remaining register ranking from baseline ctxdiff; new trials compare parameter pointer view forms and explicit narrow field access. Previously tried native workspace, loop updates, immutable-pointer and typed-scratch forms skipped.
Attempt Zi8_81483308 #1: generic parameter view with const fields. {"insns": [58, 58], "diffs": 10, "structural": 0, "exact": false, "first": [[5, ["mr", "r29, r3"], ["mr", "r31, r3"]], [13, ["lwz", "r0, 0x24(r29)"], ["lwz", "r0, 0x24(r31)"]], [22, ["li", "r31, 0"], ["li", "r29, 0"]]], "pct": 99.05173, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_81483308 #2: mutable typed receiver, scalar field loads explicitly unsigned. {"insns": [60, 58], "diffs": 31, "structural": 5, "exact": false, "first": [[7, ["mr", "r29, r5"], ["mr", "r30, r5"]], [21, ["b", 132], ["b", 124]], [22, ["li", "r30, 0"], ["li", "r29, 0"]]], "pct": 95.68965, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_81483308 #3: array receiver view of fields within unchanged scratch loop. {"insns": [58, 58], "diffs": 9, "structural": 0, "exact": false, "first": [[7, ["mr", "r29, r5"], ["mr", "r30, r5"]], [22, ["li", "r30, 0"], ["li", "r29, 0"]], [26, ["clrlwi", "r0, r30, 0x18"], ["clrlwi", "r0, r29, 0x18"]]], "pct": 99.13793, "code": "332", "data": "96"}. Retained False.

## Zi8_814833F0
Fresh origin fetch and source unchanged. Target never-read stack sweep found no missing home store. CFG/call sequence and instruction count agree. Remaining register ranking from baseline ctxdiff; new trials compare parameter pointer view forms and explicit narrow field access. Previously tried native workspace, loop updates, immutable-pointer and typed-scratch forms skipped.
Attempt Zi8_814833F0 #1: generic parameter view with const fields. {"insns": [47, 47], "diffs": 8, "structural": 0, "exact": false, "first": [[6, ["mr", "r30, r3"], ["mr", "r31, r3"]], [13, ["lwz", "r0, 0x24(r30)"], ["lwz", "r0, 0x24(r31)"]], [22, ["li", "r31, 0"], ["li", "r30, 0"]]], "pct": 99.04256, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_814833F0 #2: mutable typed receiver, scalar field loads explicitly unsigned. {"insns": [48, 47], "diffs": 21, "structural": 4, "exact": false, "first": [[6, ["mr", "r30, r3"], ["mr", "r31, r3"]], [13, ["lwz", "r0, 0x24(r30)"], ["lwz", "r0, 0x24(r31)"]], [21, ["b", 80], ["b", 76]]], "pct": 96.914894, "code": "332", "data": "96"}. Retained False.
Attempt Zi8_814833F0 #3: array receiver view of fields within unchanged scratch loop. {"insns": [47, 47], "diffs": 8, "structural": 0, "exact": false, "first": [[6, ["mr", "r30, r3"], ["mr", "r31, r3"]], [13, ["lwz", "r0, 0x24(r30)"], ["lwz", "r0, 0x24(r31)"]], [22, ["li", "r31, 0"], ["li", "r30, 0"]]], "pct": 99.04256, "code": "332", "data": "96"}. Retained False.

## Zi8_81480224 structural-first
Fresh origin fetch; unit unchanged. Target116instructions, same CFG and LogError call sites. Source priority branch blt instead of target bgt; both character addresses base-first instead of target index-first. Correct these operations before register allocation. Target word28/candidate26, source word26/candidate28. Read-only input/candidate formals were tested in ult9; new variations change actual stored word-pointer view rather than qualification alone.
Attempt Zi8_81480224 #1: target operand order with generic stored-word view. {"insns": [116, 116], "diffs": 25, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r27, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r26, 2(r27)"], ["lbz", "r25, 2(r28)"]]], "pct": 98.75, "code": "2192", "data": "80"}. Retained False.
Attempt Zi8_81480224 #2: target operand order with byte-oriented stored-word view. {"insns": [116, 116], "diffs": 25, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r27, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r26, 2(r27)"], ["lbz", "r25, 2(r28)"]]], "pct": 98.75, "code": "2192", "data": "80"}. Retained False.
Attempt Zi8_81480224 #3: target operand order with explicit readonly candidate view at each field. {"insns": [116, 116], "diffs": 25, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r27, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r26, 2(r27)"], ["lbz", "r25, 2(r28)"]]], "pct": 98.75, "code": "2192", "data": "80"}. Retained False.
Attempt Zi8_81480224 #4: target operand order, readonly comparison view for priority. {"insns": [116, 116], "diffs": 21, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r27, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r26, 2(r27)"], ["lbz", "r25, 2(r28)"]]], "pct": 98.92242, "code": "2192", "data": "80"}. Retained False.
Attempt Zi8_81480224 #5: target operand order, readonly comparison view for length. {"insns": [116, 116], "diffs": 21, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r27, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r26, 2(r27)"], ["lbz", "r25, 2(r28)"]]], "pct": 98.92242, "code": "2192", "data": "80"}. Retained False.
Attempt Zi8_81480224 #6: target operand order, readonly comparison view for priority,length. {"insns": [116, 116], "diffs": 25, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r27, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r26, 2(r27)"], ["lbz", "r25, 2(r28)"]]], "pct": 98.75, "code": "2192", "data": "80"}. Retained False.
Attempt Zi8_81480224 #7: target operand order, readonly comparison view for text. {"insns": [116, 116], "diffs": 21, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r27, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r26, 2(r27)"], ["lbz", "r25, 2(r28)"]]], "pct": 98.92242, "code": "2192", "data": "80"}. Retained False.
Attempt Zi8_81480224 #8: target operand order, readonly comparison view for priority,text. {"insns": [116, 116], "diffs": 25, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r27, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r26, 2(r27)"], ["lbz", "r25, 2(r28)"]]], "pct": 98.75, "code": "2192", "data": "80"}. Retained False.
Attempt Zi8_81480224 #9: target operand order, readonly comparison view for length,text. {"insns": [116, 116], "diffs": 25, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [16, ["cmpwi", "r27, 0"], ["cmpwi", "r28, 0"]], [24, ["lbz", "r26, 2(r27)"], ["lbz", "r25, 2(r28)"]]], "pct": 98.75, "code": "2192", "data": "80"}. Retained False.

## Zi8GetDataSignature
Fresh origin fetch, owned source unchanged. Same0x30frame and69instructions. CFG calls FormatVersion/TableAddress/TableCount/Memcpy/LogError agree. No missing stores. Only signature29/language28/destination27 versus target27/29/28. New source forms move the native table-address conversion to its copy use and change byte destination view; prior generic signature/formals and literal language cast probes skipped.
Attempt Zi8GetDataSignature #1: keep table address as native integer until copy. {"insns": [69, 69], "diffs": 9, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [7, ["mr", "r28, r5"], ["mr", "r29, r5"]], [9, ["clrlwi", "r0, r28, 0x18"], ["clrlwi", "r0, r29, 0x18"]]], "pct": 99.347824, "code": "6360", "data": "332"}. Retained False.
Attempt Zi8GetDataSignature #2: signed byte destination view with explicit library copy conversion. {"build_fail": "### mwcceppc.exe Compiler:\n#    File: libs\\RVLMiddleware\\eZiText\\src\\clib\\zi8getc2.c\n# -------------------------------------------------------\n#     130: GetDataSignature(dictionary, 0x20, parameters->language, ZI_WORK); \n#   Error:                                                                 ^\n#   (10209) illegal implicit conversion from 'unsigned char[32]' to\n#   'signed char *'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n"}. Retained False.
Attempt Zi8GetDataSignature #3: native table-address local and destination generic byte view. {"insns": [69, 69], "diffs": 9, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [7, ["mr", "r28, r5"], ["mr", "r29, r5"]], [9, ["clrlwi", "r0, r28, 0x18"], ["clrlwi", "r0, r29, 0x18"]]], "pct": 99.347824, "code": "6360", "data": "332"}. Retained False.

## Zi8IsDupWChar
Fresh origin fetch, owned source unchanged. Same0x20frame and63instructions; calls/CFG/buffer offsets exact. Character27/duplicate28 versus target28/27. No target never-read local store. Previous wideflag, continue/break, explicit scan edges and narrow store probes skipped. New probes use natural flag enum, narrow only the equality comparison, and decoded buffer view via const pointer at the readonly scan.
Attempt Zi8IsDupWChar #1: named duplicate status enum, assignments and return unchanged. {"insns": [63, 63], "diffs": 8, "structural": 1, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [7, ["li", "r28, 0"], ["li", "r27, 0"]], [14, ["sth", "r27, 2(r31)"], ["sth", "r28, 2(r31)"]]], "pct": 98.492065, "code": "6360", "data": "332"}. Retained False.
Attempt Zi8IsDupWChar #2: explicit unsigned comparison view of the input character. {"insns": [63, 63], "diffs": 8, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [7, ["li", "r28, 0"], ["li", "r27, 0"]], [14, ["sth", "r27, 2(r31)"], ["sth", "r28, 2(r31)"]]], "pct": 99.36508, "code": "6360", "data": "332"}. Retained False.
Attempt Zi8IsDupWChar #3: readonly halfword buffer view at the duplicate comparison. {"insns": [63, 63], "diffs": 8, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [7, ["li", "r28, 0"], ["li", "r27, 0"]], [14, ["sth", "r27, 2(r31)"], ["sth", "r28, 2(r31)"]]], "pct": 99.36508, "code": "6360", "data": "332"}. Retained False.
Attempt Zi8GetDataSignature #4: wide language identifier with byte conversion at equality and library calls. {"insns": [69, 69], "diffs": 9, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [7, ["mr", "r28, r5"], ["mr", "r29, r5"]], [9, ["clrlwi", "r0, r28, 0x18"], ["clrlwi", "r0, r29, 0x18"]]], "pct": 99.347824, "code": "6360", "data": "332"}. Retained False.

## ZiDAWGgetCHARattribute
Fresh origin fetch. Same0x20frame/60instructions and helper calls; no missing store. context30/key31 versus target31/30. Header already declares p08/p0C as ziU8*, but source adds byte-pointer casts. New probes remove these redundant member casts rather than repeat earlier readonly/generic context, key-width and attribute self-assignment variants.
Attempt ZiDAWGgetCHARattribute #1: use actual typed byte-table members without casts. {"insns": [60, 60], "diffs": 12, "structural": 0, "exact": false, "first": [[5, ["mr", "r30, r3"], ["mr", "r31, r3"]], [14, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]], [18, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]]], "pct": 99.0, "code": "888", "data": "80"}. Retained False.
Attempt ZiDAWGgetCHARattribute #2: typed byte-table members and natural second-byte array indexing. {"insns": [60, 60], "diffs": 13, "structural": 0, "exact": false, "first": [[5, ["mr", "r30, r3"], ["mr", "r31, r3"]], [14, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]], [18, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]]], "pct": 98.833336, "code": "888", "data": "80"}. Retained False.
Attempt ZiDAWGgetCHARattribute #3: typed byte-table members with halfword widening before high-byte shift. {"insns": [60, 60], "diffs": 12, "structural": 0, "exact": false, "first": [[5, ["mr", "r30, r3"], ["mr", "r31, r3"]], [14, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]], [18, ["clrlwi", "r31, r0, 0x18"], ["clrlwi", "r30, r0, 0x18"]]], "pct": 99.0, "code": "888", "data": "80"}. Retained False.

## ZiDAWGGetGraphInfo
Fresh fork fetch. Same0x30frame/134instructions, no missing home store. Entry scan CFG/call to GetGraph and stores/reloads endNode agree. Remove source redundant casts on the already-typed context before testing graph operand width/depth counting type. Earlier direct fields alone gave11diffs, pointer graph/end and volatile endNode variants already tested.
Attempt ZiDAWGGetGraphInfo #1: typed receiver plus explicit native-address arithmetic view. {"insns": [134, 134], "diffs": 11, "structural": 0, "exact": false, "first": [[10, ["mr", "r28, r3"], ["mr", "r26, r3"]], [35, ["add", "r26, r31, r0"], ["add", "r27, r31, r0"]], [37, ["li", "r27, 0"], ["li", "r28, 0"]]], "pct": 99.55224, "code": "888", "data": "80"}. Retained False.
Attempt ZiDAWGGetGraphInfo #2: typed receiver and word-sized depth with byte tests. {"insns": [134, 134], "diffs": 11, "structural": 0, "exact": false, "first": [[10, ["mr", "r28, r3"], ["mr", "r26, r3"]], [35, ["add", "r26, r31, r0"], ["add", "r27, r31, r0"]], [37, ["li", "r27, 0"], ["li", "r28, 0"]]], "pct": 99.55224, "code": "888", "data": "80"}. Retained False.
Attempt ZiDAWGGetGraphInfo #3: typed receiver and signed graph base interpreted as unsigned address. {"insns": [134, 134], "diffs": 11, "structural": 0, "exact": false, "first": [[10, ["mr", "r28, r3"], ["mr", "r26, r3"]], [35, ["add", "r26, r31, r0"], ["add", "r27, r31, r0"]], [37, ["li", "r27, 0"], ["li", "r28, 0"]]], "pct": 99.55224, "code": "888", "data": "80"}. Retained False.

## Zi8getKeyLayout
Fresh origin fetch.182/182instructions, frame/calls/CFG exact; language26/tableCount27 versus target27/26. No missing target local store. Prior declaration order, separate total, loops and compound/preincrement variants exhausted. New probes use native address storage, actual readonly custom map, and wide table-count arithmetic with the target halfword views.
Attempt Zi8getKeyLayout #1: native integer table address converted only at byte reads. {"insns": [182, 182], "diffs": 39, "structural": 0, "exact": false, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [9, ["mr", "r30, r7"], ["mr", "r29, r7"]], [10, ["li", "r29, 0"], ["li", "r30, 0"]]], "pct": 98.9011, "code": "1488", "data": "60"}. Retained False.
Attempt Zi8getKeyLayout #2: readonly custom key map viewed through its actual table type. {"insns": [182, 182], "diffs": 16, "structural": 0, "exact": false, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [11, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [21, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]]], "pct": 99.53297, "code": "1488", "data": "60"}. Retained False.
Attempt Zi8getKeyLayout #3: wide accumulated count with halfword API and offset views. {"insns": [180, 182], "diffs": 116, "structural": 7, "exact": false, "first": [[5, ["mr", "r26, r3"], ["mr", "r27, r3"]], [11, ["clrlwi", "r3, r26, 0x18"], ["clrlwi", "r3, r27, 0x18"]], [21, ["clrlwi", "r0, r26, 0x18"], ["clrlwi", "r0, r27, 0x18"]]], "pct": 98.07692, "code": "1488", "data": "24"}. Retained False.

## Zi8ConvertUC2Key
Fresh fork fetch, unchanged source.207/207instructions, frame0x40, key/work saved-register exchange only. CFG/calls GetTableCount/GetTableAddress/UserKey/LogError and table/range traversal agree. No target never-read slot. Prior word/char result type, readonly table/range, folded update and separate work alias probes skipped. New probes qualify decoded mapped buffer, explicitly narrow the key offset, and combine readonly encoded entries with that offset shape.
Attempt Zi8ConvertUC2Key #1: explicit halfword view of key used as table offset. {"insns": [207, 207], "diffs": 18, "structural": 0, "exact": false, "first": [[7, ["mr", "r27, r5"], ["mr", "r28, r5"]], [8, ["li", "r28, 0"], ["li", "r27, 0"]], [14, ["mr", "r4, r27"], ["mr", "r4, r28"]]], "pct": 99.565216, "code": "1380", "data": "112"}. Retained False.
Attempt Zi8ConvertUC2Key #2: mapped wide-character table exposed through generic storage pointer. {"insns": [208, 207], "diffs": 53, "structural": 13, "exact": false, "first": [[7, ["mr", "r27, r5"], ["mr", "r28, r5"]], [8, ["li", "r28, 0"], ["li", "r27, 0"]], [14, ["mr", "r4, r27"], ["mr", "r4, r28"]]], "pct": 99.08212, "code": "1380", "data": "64"}. Retained False.
Attempt Zi8ConvertUC2Key #3: readonly encoded table/entry with halfword key offset. {"insns": [207, 207], "diffs": 18, "structural": 0, "exact": false, "first": [[7, ["mr", "r27, r5"], ["mr", "r28, r5"]], [8, ["li", "r28, 0"], ["li", "r27, 0"]], [14, ["mr", "r4, r27"], ["mr", "r4, r28"]]], "pct": 99.565216, "code": "1380", "data": "112"}. Retained False.

## Zi8MatchOEMdata
Fresh fork fetch, unchanged source. Target192instructions/frame0x40. Callback retry, duplicate test, fallback and error-return CFG agree; all workspace initialization stores present. Saved-register permutation covers work/pattern/length/index and capacity/fallback. Previous readonly pattern/native workspace, compound retry index, callback do-loop and operand reversal probes exhausted. New probes use the real32-bit stored index type, native int loop index, and byte-candidate callback index conversion.
Attempt Zi8MatchOEMdata #1: native int OEM entry index with explicit signed comparisons. {"insns": [192, 192], "diffs": 47, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [6, ["mr", "r26, r4"], ["mr", "r27, r4"]], [9, ["mr", "r23, r7"], ["mr", "r24, r7"]]], "pct": 98.645836, "code": "208", "data": "60"}. Retained False.
Attempt Zi8MatchOEMdata #2: OEM entry index uses workspace unsigned word type and signed tests. {"insns": [192, 192], "diffs": 47, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [6, ["mr", "r26, r4"], ["mr", "r27, r4"]], [9, ["mr", "r23, r7"], ["mr", "r24, r7"]]], "pct": 98.645836, "code": "208", "data": "60"}. Retained False.
Attempt Zi8MatchOEMdata #3: explicit callback index narrowing combined with signed word loop index. {"insns": [192, 192], "diffs": 47, "structural": 0, "exact": false, "first": [[5, ["mr", "r27, r3"], ["mr", "r28, r3"]], [6, ["mr", "r26, r4"], ["mr", "r27, r4"]], [9, ["mr", "r23, r7"], ["mr", "r24, r7"]]], "pct": 98.645836, "code": "208", "data": "60"}. Retained False.
Attempt Zi8GetKOcandidates #5: corrected native table address plus unsigned prefix count with signed capacity comparisons. {"insns": [671, 669], "diffs": 639, "structural": 2, "exact": false, "first": [[15, ["li", "r0, 0"], ["stb", "r0, 0x3c(r1)"]], [16, ["stb", "r0, 0x3c(r1)"], ["li", "r0, 0"]], [17, ["li", "r0, 0"], ["stb", "r0, 0xe(r1)"]]], "pct": 98.146484, "code": "332", "data": "96"}. Retained False.

## Final coverage and ownership audit
Zi8ConvertUC2Key: 3 compiled distinct trials; 0 rejected build failures.
Zi8GetDataSignature: 3 compiled distinct trials; 1 rejected build failures.
Zi8IsDupWChar: 3 compiled distinct trials; 0 rejected build failures.
Zi8MatchPUDdata_ZHS: 8 compiled distinct trials; 0 rejected build failures.
Zi8_81480224: 9 compiled distinct trials; 0 rejected build failures.
ZiDAWGgetCHARattribute: 3 compiled distinct trials; 0 rejected build failures.
ZiDAWGGetGraphInfo: 3 compiled distinct trials; 0 rejected build failures.
Zi8_8148302C: 3 compiled distinct trials; 0 rejected build failures.
Zi8_81483264: 3 compiled distinct trials; 0 rejected build failures.
Zi8_81483308: 3 compiled distinct trials; 0 rejected build failures.
Zi8_814833F0: 3 compiled distinct trials; 0 rejected build failures.
Zi8_814834AC: 8 compiled distinct trials; 0 rejected build failures.
Zi8GetKOcandidates: 4 compiled distinct trials; 1 rejected build failures.
Zi8getKeyLayout: 3 compiled distinct trials; 0 rejected build failures.
Zi8MatchOEMdata: 3 compiled distinct trials; 0 rejected build failures.
All unretained source trials restored. Only zi8pud2.c differs from baseline; no header/configuration/linking edits, and no candidate on the other seven units. No inline assembly, use-site volatile, register keyword, fabricated symbol or undefined input added. Final gates are matching-only; whole project and seven units remain incomplete.

## Final full nonquick gate over all eight units
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2] objdiff: code 2136/2136 data 120/120 functions 7/7 fuzzy 100.0000 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2] instruction-exact functions: 7/7
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2]   section .text size 2136 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2]   section extab size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2]   section extabindex size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8pud2] baseline: code 720/2136 data 48 functions 6 fuzzy 99.8127
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
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] objdiff: code 1488/2216 data 60/60 functions 3/4 fuzzy 99.8466 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section .text size 2216 match 99.84657
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zmtkey]   below 100: Zi8getKeyLayout 99.53297
[libs/RVLMiddleware/eZiText/src/clib/zmtkey] baseline: code 1488/2216 data 60 functions 3 fuzzy 99.8466
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] objdiff: code 2192/2656 data 80/80 functions 3/4 fuzzy 99.9172 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd]   section .text size 2656 match 99.91717
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd]   below 100: Zi8_81480224 99.52586
[libs/RVLMiddleware/eZiText/src/clib/zi8uwd] baseline: code 2192/2656 data 80 functions 3 fuzzy 99.9172
[libs/RVLMiddleware/eZiText/src/clib/zconvert] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zconvert] objdiff: code 1380/2208 data 112/112 functions 3/4 fuzzy 99.8370 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zconvert] instruction-exact functions: 3/4
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .rodata size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section .text size 2208 match 99.83696
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extab size 32 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   section extabindex size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zconvert]   below 100: Zi8ConvertUC2Key 99.565216
[libs/RVLMiddleware/eZiText/src/clib/zconvert] baseline: code 1380/2208 data 112 functions 3 fuzzy 99.8370
regressions vs baseline: 0
global matched_code_percent: 91.95013 -> 91.99740
global fuzzy_match_percent: 99.71971 -> 99.71984
global complete_code_percent: 74.84181 -> 74.84181
global matched_data_percent: 99.77803 -> 99.78196
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

zi8pud2: exact 6/7 -> 7/7; code 720 -> 2136 / 2136; data 48 -> 120 / 120.
zi8getc2: exact 15/17 -> 15/17; code 6360 -> 6360 / 6888; data 332 -> 332 / 332.
OPEN Zi8GetDataSignature 99.347824%; insns[69, 69], diffs9, normalized structural0; saved-register allocation only.
OPEN Zi8IsDupWChar 99.36508%; insns[63, 63], diffs8, normalized structural0; saved-register allocation only.
zidawg1: exact 4/6 -> 4/6; code 888 -> 888 / 1664; data 80 -> 80 / 80.
OPEN ZiDAWGgetCHARattribute 99.0%; insns[60, 60], diffs12, normalized structural0; saved-register allocation only.
OPEN ZiDAWGGetGraphInfo 99.55224%; insns[134, 134], diffs12, normalized structural0; saved-register allocation only.
zoemdata: exact 2/3 -> 2/3; code 208 -> 208 / 976; data 60 -> 60 / 60.
OPEN Zi8MatchOEMdata 98.645836%; insns[192, 192], diffs47, normalized structural0; saved-register allocation only.
zkokeyp: exact 1/7 -> 1/7; code 332 -> 332 / 5200; data 96 -> 96 / 180.
OPEN Zi8_8148302C 99.49152%; insns[59, 59], diffs6, normalized structural0; saved-register allocation only.
OPEN Zi8_81483264 98.902435%; insns[41, 41], diffs8, normalized structural0; saved-register allocation only.
OPEN Zi8_81483308 99.13793%; insns[58, 58], diffs9, normalized structural0; saved-register allocation only.
OPEN Zi8_814833F0 99.04256%; insns[47, 47], diffs8, normalized structural0; saved-register allocation only.
OPEN Zi8_814834AC 99.3586%; insns[344, 343], diffs329, normalized structural1; extra packed-byte narrowing, two address operand orders, work/candidate allocation.
OPEN Zi8GetKOcandidates 98.146484%; insns[671, 669], diffs639, normalized structural2; extra packed zero and word-table pointer copy, scratch/address register allocation.
zmtkey: exact 3/4 -> 3/4; code 1488 -> 1488 / 2216; data 60 -> 60 / 60.
OPEN Zi8getKeyLayout 99.53297%; insns[182, 182], diffs16, normalized structural0; saved-register allocation only.
zi8uwd: exact 3/4 -> 3/4; code 2192 -> 2192 / 2656; data 80 -> 80 / 80.
OPEN Zi8_81480224 99.52586%; insns[116, 116], diffs9, normalized structural1; priority/address operand order and word/candidate register allocation.
zconvert: exact 3/4 -> 3/4; code 1380 -> 1380 / 2208; data 112 -> 112 / 112.
OPEN Zi8ConvertUC2Key 99.565216%; insns[207, 207], diffs18, normalized structural0; saved-register allocation only.
Independent fresh instruction comparison confirms all38objdiff-exact functions have ctxdiff-equivalent zero differences. Baseline37exact functions preserved. Zi8MatchPUDdata_ZHS354/354instructions,0differences. Eight pools remain empty/identical. DOL exact; regressions/forbidden/readability zero.14functions remain open, each has at least3compiled distinct attempts in this round; none relabeled as exact. No data metadata edits justified.
Baseline totals exact37/52, code13568/23944, data868/1024. Final exact38/52, code14984/23944, data940/1024. PUD is now fully matched code/data; complete_code0 reflects matching-only phase.
