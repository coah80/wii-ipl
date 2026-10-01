# Round 2 target and compiled block maps

Source baseline: `98648d19bb70d1361ccf566c643dedd567d61541`. Final source: `6bacb043`.
Target input: `build/43U/asm/<unit>.s`; compiled input: `build/43U/src/<unit>.o`. Compiled instructions were also independently exported with `tools/decomp-assist/disasm_fn.py`.
All offsets below are relative to the function start. Blocks start at entry, branch destinations, fallthroughs after control transfers, target assembly labels and relocation-resolved jump-table destinations. Each block records instruction count, call targets and relocation/string references.
Block alignment uses ordered calls, resolved string contents and opcode sequences. Call-aligned regions include every intervening instruction. Repeated cleanup calls can admit more than one alignment; a positive interval count identifies a physical stream gap and does not by itself establish a missing reachable source path.
Target-only opcode spans below list every nonempty target span not equal under the local opcode alignment, including balanced replacements. Equal opcode sequences may still differ in operands or branch destinations; ctxdiff and objdiff are the authorities for an exact match.
Attempt-region IDs refer to the contemporaneous maps in the attempt log. Final IDs refer to these maps. Exhaustion evidence is indexed by semantic family in the final audit.

| Function | Target instructions | Entry compiled instructions | Final compiled instructions | Deficit before -> after | Fuzzy before -> after |
| --- | --- | --- | --- | --- | --- |
| AOSS_Init_old | 1584 | 1510 | 1584 | 74 -> 0 | 76.132576 -> 89.022095 |
| AOSS_81400830 | 321 | 321 | 321 | 0 -> 0 | 97.0405 -> 97.0405 |
| AOSS_814013AC | 114 | 114 | 114 | 0 -> 0 | 98.77193 -> 98.77193 |
| AOSS_81401778 | 273 | 270 | 271 | 3 -> 2 | 86.67033 -> 89.78022 |
| AOSS_81401E80 | 147 | 147 | 147 | 0 -> 0 | 98.605446 -> 98.605446 |
| Zi8ChangeWordCase | 44 | 44 | 44 | 0 -> 0 | 99.09091 -> 99.09091 |
| Zi8AlphaGetCandidates | 3946 | 3949 | 3947 | -3 -> -1 | 87.00405 -> 90.22073 |

## AOSS_Init_old

Target: `build/43U/asm/src/scene/setting/AOSS.s`. Compiled: `build/43U/src/src/scene/setting/AOSS.o`.

```text
src 0x18c0 base 0x18c0 insns 1584/1584
diffs 1475: [8, 9, 10, 12, 14, 16, 17, 18, 19, 23, 26, 35, 38, 45, 46, 48, 63, 64, 66, 67]
```

Frame and saved-register range now agree; a redundant target IP-failure branch, several wait branches, stack slots and live registers differ.

Entry call-aligned gaps:

```text
R000 target [0:8] built [0:5] deficit +3 before _savegpr_14
R001 target [8:21] built [5:13] deficit +5 before memset
R002 target [21:53] built [13:41] deficit +4 before memset
R004 target [60:87] built [48:76] deficit -1 before AOSSi_Free
R007 target [103:109] built [92:97] deficit +1 before AOSSi_Free
R016 target [165:180] built [153:251] deficit -83 before AOSSi_Free
R018 target [186:201] built [257:271] deficit +1 before AOSSi_Free
R021 target [217:235] built [287:307] deficit -2 before AOSSi_Free
R023 target [241:352] built [313:323] deficit +101 before AOSS_814020CC
R026 target [366:388] built [337:358] deficit +1 before AOSSi_Free
R029 target [404:422] built [374:391] deficit +1 before AOSSi_Free
R031 target [428:446] built [397:412] deficit +3 before AOSSi_Free
R035 target [466:476] built [432:441] deficit +1 before memcpy
R037 target [477:481] built [442:445] deficit +1 before SOHtoNs
R038 target [481:490] built [445:455] deficit -1 before SOSocket
R041 target [505:533] built [470:478] deficit +20 before memset
R045 target [545:586] built [490:524] deficit +7 before memset
R046 target [586:599] built [524:535] deficit +2 before SOClose
R050 target [624:643] built [560:578] deficit +1 before AOSSi_SetNCDIPAddr
R057 target [688:694] built [623:628] deficit +1 before AOSS_814020CC
R060 target [708:730] built [642:663] deficit +1 before AOSSi_Free
R063 target [746:764] built [679:696] deficit +1 before AOSSi_Free
R095 target [960:993] built [892:913] deficit +12 before SOPoll
R096 target [993:1025] built [913:944] deficit +1 before AOSSi_Free
R099 target [1041:1059] built [960:977] deficit +1 before AOSSi_Free
R101 target [1065:1077] built [983:1010] deficit -15 before SORecvFrom
R103 target [1081:1089] built [1014:1021] deficit +1 before AOSS_814001B4
R104 target [1089:1106] built [1021:1039] deficit -1 before SOClose
R124 target [1248:1254] built [1181:1186] deficit +1 before AOSS_814020CC
R127 target [1268:1290] built [1200:1221] deficit +1 before AOSSi_Free
R130 target [1306:1324] built [1237:1254] deficit +1 before AOSSi_Free
R141 target [1385:1393] built [1315:1334] deficit -11 before AOSSi_Free
R143 target [1399:1451] built [1340:1350] deficit +42 before AOSSi_Sleep
R146 target [1475:1483] built [1374:1394] deficit -12 before SOClose
R150 target [1510:1558] built [1421:1429] deficit +40 before AOSS_813FFD68
R151 target [1558:1566] built [1429:1439] deficit -2 before AOSSi_Free
R153 target [1572:1580] built [1445:1506] deficit -53 before _restgpr_14
```

Final prologue, all basic blocks, unequal block spans and call-aligned regions:

```text
AOSS_Init_old: target 1584, built 1584, signed deficit 0
entry target: [{'off': 0, 'mn': 'clrlwi', 'op': 'r11, r1, 27', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mr', 'op': 'r12, r1', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'subfic', 'op': 'r11, r11, -0x160', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'stwux', 'op': 'r1, r1, r11', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 20, 'mn': 'mr', 'op': 'r11, r12', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'stw', 'op': 'r0, 0x4(r12)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'bl', 'op': '_savegpr_14', 'call': '_savegpr_14', 'ref': None, 'dest': None, 'strings': []}]
entry built: [{'off': 0, 'mn': 'clrlwi', 'op': 'r11, r1, 0x1b', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mr', 'op': 'r12, r1', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'subfic', 'op': 'r11, r11, -0x160', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'stwux', 'op': 'r1, r1, r11', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 20, 'mn': 'mr', 'op': 'r11, r12', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'stw', 'op': 'r0, 4(r12)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'bl', 'op': '0x248', 'call': '_savegpr_14', 'ref': ('_savegpr_14', 0), 'dest': None, 'strings': []}]
TARGET BASIC BLOCKS
T000 +0000 n=25 calls=['_savegpr_14', 'memset'] refs=[('lbl_81694C78', 0), ('lbl_81694C7A', 0)] strings=[]
T001 +0064 n=2 calls=[] refs=[] strings=[]
T002 +006c n=4 calls=[] refs=[] strings=[]
T003 +007c n=2 calls=[] refs=[] strings=[]
T004 +0084 n=4 calls=[] refs=[] strings=[]
T005 +0094 n=2 calls=[] refs=[] strings=[]
T006 +009c n=4 calls=[] refs=[] strings=[]
T007 +00ac n=2 calls=[] refs=[] strings=[]
T008 +00b4 n=3 calls=[] refs=[] strings=[]
T009 +00c0 n=1 calls=[] refs=[] strings=[]
T010 +00c4 n=30 calls=['memset', 'memset'] refs=[('lbl_81698C78', 0), ('AOSS_810BDEF8', 0), ('lbl_81698C84', 0), ('AOSS_810BDEF8', 0), ('AOSS_810BDEF8', 0), ('AOSS_810BDEF8', 0)] strings=[]
T011 +013c n=7 calls=[] refs=[('lbl_81698C84', 0), ('lbl_81698C74', 0)] strings=[]
T012 +0158 n=2 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T013 +0160 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T014 +016c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T015 +0178 n=2 calls=[] refs=[] strings=[]
T016 +0180 n=4 calls=[] refs=[('lbl_8169720C', 0)] strings=[]
T017 +0190 n=3 calls=['AOSSi_Status'] refs=[('lbl_8169720C', 0)] strings=[]
T018 +019c n=2 calls=[] refs=[] strings=[]
T019 +01a4 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T020 +01b0 n=2 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T021 +01b8 n=4 calls=['AOSSi_WLANGetBSSList'] refs=[('lbl_81698C70', 0)] strings=[]
T022 +01c8 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T023 +01dc n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T024 +01e8 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T025 +01f4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T026 +0200 n=2 calls=[] refs=[] strings=[]
T027 +0208 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T028 +0214 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T029 +0228 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T030 +0234 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T031 +0240 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T032 +024c n=2 calls=[] refs=[] strings=[]
T033 +0254 n=4 calls=['AOSS_CheckAP'] refs=[('lbl_81698C70', 0)] strings=[]
T034 +0264 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T035 +0278 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T036 +0284 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T037 +0290 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T038 +029c n=2 calls=[] refs=[] strings=[]
T039 +02a4 n=2 calls=[] refs=[] strings=[]
T040 +02ac n=3 calls=[] refs=[] strings=[]
T041 +02b8 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T042 +02cc n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T043 +02d8 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T044 +02e4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T045 +02f0 n=2 calls=[] refs=[] strings=[]
T046 +02f8 n=2 calls=[] refs=[] strings=[]
T047 +0300 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T048 +030c n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T049 +0320 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T050 +032c n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T051 +0338 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T052 +0344 n=2 calls=[] refs=[] strings=[]
T053 +034c n=2 calls=[] refs=[] strings=[]
T054 +0354 n=2 calls=[] refs=[] strings=[]
T055 +035c n=1 calls=[] refs=[] strings=[]
T056 +0360 n=3 calls=['AOSSi_Sleep'] refs=[] strings=[]
T057 +036c n=2 calls=[] refs=[] strings=[]
T058 +0374 n=1 calls=[] refs=[] strings=[]
T059 +0378 n=2 calls=[] refs=[] strings=[]
T060 +0380 n=2 calls=[] refs=[] strings=[]
T061 +0388 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T062 +0394 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T063 +03a8 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T064 +03b4 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T065 +03c0 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T066 +03cc n=2 calls=[] refs=[] strings=[]
T067 +03d4 n=2 calls=[] refs=[] strings=[]
T068 +03dc n=3 calls=[] refs=[('lbl_8169720C', 0)] strings=[]
T069 +03e8 n=4 calls=['AOSSi_Status'] refs=[('lbl_8169720C', 0)] strings=[]
T070 +03f8 n=19 calls=['memset', 'strlen', 'memcpy', 'strlen'] refs=[('lbl_81657C48', 0), ('lbl_81657C48', 0), ('lbl_81657C48', 0), ('lbl_81697204', 0)] strings=['ESSID-AOSS', 'ESSID-AOSS', 'ESSID-AOSS', 'MELCO']
T071 +0444 n=1 calls=[] refs=[] strings=[]
T072 +0448 n=4 calls=['memcpy'] refs=[('lbl_81697204', 0)] strings=['MELCO']
T073 +0458 n=9 calls=['AOSSi_SetNCDIPAddr'] refs=[] strings=[]
T074 +047c n=7 calls=[] refs=[('lbl_81698C84', 0), ('lbl_81698C74', 0)] strings=[]
T075 +0498 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T076 +04a4 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T077 +04b0 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T078 +04bc n=2 calls=[] refs=[] strings=[]
T079 +04c4 n=1 calls=[] refs=[] strings=[]
T080 +04c8 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T081 +04dc n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T082 +04e8 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T083 +04f4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T084 +0500 n=2 calls=[] refs=[] strings=[]
T085 +0508 n=5 calls=['AOSSi_Alloc'] refs=[('lbl_81698C74', 0)] strings=[]
T086 +051c n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T087 +0530 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T088 +053c n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T089 +0548 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T090 +0554 n=2 calls=[] refs=[] strings=[]
T091 +055c n=6 calls=['memset'] refs=[] strings=[]
T092 +0574 n=5 calls=['AOSS_814020CC'] refs=[('lbl_81698C74', 0)] strings=[]
T093 +0588 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T094 +059c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T095 +05a8 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T096 +05b4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T097 +05c0 n=2 calls=[] refs=[] strings=[]
T098 +05c8 n=2 calls=[] refs=[] strings=[]
T099 +05d0 n=1 calls=[] refs=[] strings=[]
T100 +05d4 n=4 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T101 +05e4 n=2 calls=[] refs=[] strings=[]
T102 +05ec n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T103 +05f8 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T104 +060c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T105 +0618 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T106 +0624 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T107 +0630 n=2 calls=[] refs=[] strings=[]
T108 +0638 n=2 calls=[] refs=[] strings=[]
T109 +0640 n=2 calls=[] refs=[] strings=[]
T110 +0648 n=1 calls=[] refs=[] strings=[]
T111 +064c n=3 calls=['AOSSi_Sleep'] refs=[] strings=[]
T112 +0658 n=2 calls=[] refs=[] strings=[]
T113 +0660 n=1 calls=[] refs=[] strings=[]
T114 +0664 n=2 calls=[] refs=[] strings=[]
T115 +066c n=2 calls=[] refs=[] strings=[]
T116 +0674 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T117 +0680 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T118 +0694 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T119 +06a0 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T120 +06ac n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T121 +06b8 n=2 calls=[] refs=[] strings=[]
T122 +06c0 n=1 calls=[] refs=[] strings=[]
T123 +06c4 n=3 calls=[] refs=[] strings=[]
T124 +06d0 n=4 calls=[] refs=[] strings=[]
T125 +06e0 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T126 +06f4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T127 +0700 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T128 +070c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T129 +0718 n=2 calls=[] refs=[] strings=[]
T130 +0720 n=3 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T131 +072c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T132 +0738 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T133 +0744 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T134 +0750 n=3 calls=[] refs=[] strings=[]
T135 +075c n=15 calls=['memcpy', 'rand', 'SOHtoNs'] refs=[] strings=[]
T136 +0798 n=7 calls=['SOSocket'] refs=[('lbl_81697200', 0)] strings=[]
T137 +07b4 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T138 +07c8 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T139 +07d4 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T140 +07e0 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T141 +07ec n=2 calls=[] refs=[] strings=[]
T142 +07f4 n=2 calls=[] refs=[] strings=[]
T143 +07fc n=7 calls=[] refs=[('lbl_81698C84', 0), ('lbl_81698C74', 0)] strings=[]
T144 +0818 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T145 +0824 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T146 +0830 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T147 +083c n=2 calls=[] refs=[] strings=[]
T148 +0844 n=18 calls=['memset', 'SOGetHostID', 'SOHtoNs', 'SOBind'] refs=[('lbl_81697200', 0)] strings=[]
T149 +088c n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T150 +08a0 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T151 +08ac n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T152 +08b8 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T153 +08c4 n=2 calls=[] refs=[] strings=[]
T154 +08cc n=18 calls=[] refs=[('AOSS_810BDEF8', 0), ('AOSS_810BDEF8', 0)] strings=[]
T155 +0914 n=9 calls=['memset'] refs=[('lbl_81698C8C', 0)] strings=[]
T156 +0938 n=2 calls=[] refs=[] strings=[]
T157 +0940 n=3 calls=[] refs=[] strings=[]
T158 +094c n=3 calls=[] refs=[('lbl_81697200', 0)] strings=[]
T159 +0958 n=1 calls=['SOClose'] refs=[] strings=[]
T160 +095c n=4 calls=[] refs=[('lbl_81698C88', 0), ('lbl_81697200', 0)] strings=[]
T161 +096c n=4 calls=['SOCleanup'] refs=[('lbl_81698C88', 0)] strings=[]
T162 +097c n=2 calls=[] refs=[] strings=[]
T163 +0984 n=1 calls=[] refs=[] strings=[]
T164 +0988 n=2 calls=[] refs=[] strings=[]
T165 +0990 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T166 +09a4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T167 +09b0 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T168 +09bc n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T169 +09c8 n=2 calls=[] refs=[] strings=[]
T170 +09d0 n=9 calls=[] refs=[] strings=[]
T171 +09f4 n=1 calls=[] refs=[] strings=[]
T172 +09f8 n=7 calls=['AOSSi_SetNCDIPAddr'] refs=[] strings=[]
T173 +0a14 n=7 calls=[] refs=[('lbl_81698C84', 0), ('lbl_81698C74', 0)] strings=[]
T174 +0a30 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T175 +0a3c n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T176 +0a48 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T177 +0a54 n=2 calls=[] refs=[] strings=[]
T178 +0a5c n=6 calls=['AOSSi_Alloc'] refs=[('lbl_81698C74', 0)] strings=[]
T179 +0a74 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T180 +0a88 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T181 +0a94 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T182 +0aa0 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T183 +0aac n=2 calls=[] refs=[] strings=[]
T184 +0ab4 n=6 calls=['memset'] refs=[] strings=[]
T185 +0acc n=5 calls=['AOSS_814020CC'] refs=[('lbl_81698C74', 0)] strings=[]
T186 +0ae0 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T187 +0af4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T188 +0b00 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T189 +0b0c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T190 +0b18 n=2 calls=[] refs=[] strings=[]
T191 +0b20 n=2 calls=[] refs=[] strings=[]
T192 +0b28 n=1 calls=[] refs=[] strings=[]
T193 +0b2c n=4 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T194 +0b3c n=2 calls=[] refs=[] strings=[]
T195 +0b44 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T196 +0b50 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T197 +0b64 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T198 +0b70 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T199 +0b7c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T200 +0b88 n=2 calls=[] refs=[] strings=[]
T201 +0b90 n=2 calls=[] refs=[] strings=[]
T202 +0b98 n=2 calls=[] refs=[] strings=[]
T203 +0ba0 n=1 calls=[] refs=[] strings=[]
T204 +0ba4 n=3 calls=['AOSSi_Sleep'] refs=[] strings=[]
T205 +0bb0 n=2 calls=[] refs=[] strings=[]
T206 +0bb8 n=1 calls=[] refs=[] strings=[]
T207 +0bbc n=2 calls=[] refs=[] strings=[]
T208 +0bc4 n=2 calls=[] refs=[] strings=[]
T209 +0bcc n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T210 +0bd8 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T211 +0bec n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T212 +0bf8 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T213 +0c04 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T214 +0c10 n=2 calls=[] refs=[] strings=[]
T215 +0c18 n=1 calls=[] refs=[] strings=[]
T216 +0c1c n=3 calls=[] refs=[] strings=[]
T217 +0c28 n=7 calls=['SOSocket'] refs=[('lbl_81697200', 0)] strings=[]
T218 +0c44 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T219 +0c58 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T220 +0c64 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T221 +0c70 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T222 +0c7c n=2 calls=[] refs=[] strings=[]
T223 +0c84 n=16 calls=['memset', 'SOGetHostID', 'SOHtoNs', 'SOBind'] refs=[('lbl_81697200', 0)] strings=[]
T224 +0cc4 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T225 +0cd8 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T226 +0ce4 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T227 +0cf0 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T228 +0cfc n=2 calls=[] refs=[] strings=[]
T229 +0d04 n=3 calls=[] refs=[('lbl_81697200', 0)] strings=[]
T230 +0d10 n=1 calls=[] refs=[] strings=[]
T231 +0d14 n=2 calls=[] refs=[] strings=[]
T232 +0d1c n=1 calls=[] refs=[] strings=[]
T233 +0d20 n=2 calls=[] refs=[] strings=[]
T234 +0d28 n=1 calls=[] refs=[] strings=[]
T235 +0d2c n=3 calls=[] refs=[('lbl_8169720C', 0)] strings=[]
T236 +0d38 n=3 calls=['AOSSi_Status'] refs=[('lbl_8169720C', 0)] strings=[]
T237 +0d44 n=5 calls=['AOSS_81401574'] refs=[] strings=[]
T238 +0d58 n=3 calls=[] refs=[('lbl_8169720C', 0)] strings=[]
T239 +0d64 n=4 calls=['AOSSi_Status'] refs=[('lbl_8169720C', 0)] strings=[]
T240 +0d74 n=5 calls=['AOSS_81401778'] refs=[] strings=[]
T241 +0d88 n=3 calls=[] refs=[('lbl_8169720C', 0)] strings=[]
T242 +0d94 n=4 calls=['AOSSi_Status'] refs=[('lbl_8169720C', 0)] strings=[]
T243 +0da4 n=52 calls=['memset', 'memcpy', 'strlen', 'AOSS_81401E80', 'SOHtoNs', 'SOHtoNs', 'SOHtoNs', 'SOHtoNs', 'memcpy', 'memset', 'SOHtoNs', 'SOHtoNl'] refs=[('lbl_81698C8C', 0), ('lbl_81697204', 0), ('lbl_81697204', 0)] strings=['MELCO', 'MELCO']
T244 +0e74 n=1 calls=[] refs=[] strings=[]
T245 +0e78 n=9 calls=['SOSendTo'] refs=[] strings=[]
T246 +0e9c n=1 calls=[] refs=[] strings=[]
T247 +0ea0 n=2 calls=[] refs=[] strings=[]
T248 +0ea8 n=7 calls=[] refs=[('lbl_81698C84', 0), ('lbl_81698C74', 0)] strings=[]
T249 +0ec4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T250 +0ed0 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T251 +0edc n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T252 +0ee8 n=2 calls=[] refs=[] strings=[]
T253 +0ef0 n=39 calls=['memset', 'SOPoll'] refs=[('lbl_81697200', 0)] strings=[]
T254 +0f8c n=5 calls=[] refs=[] strings=[]
T255 +0fa0 n=2 calls=[] refs=[] strings=[]
T256 +0fa8 n=3 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T257 +0fb4 n=2 calls=[] refs=[] strings=[]
T258 +0fbc n=3 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T259 +0fc8 n=2 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T260 +0fd0 n=2 calls=[] refs=[] strings=[]
T261 +0fd8 n=2 calls=[] refs=[] strings=[]
T262 +0fe0 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T263 +0fec n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T264 +1000 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T265 +100c n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T266 +1018 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T267 +1024 n=2 calls=[] refs=[] strings=[]
T268 +102c n=2 calls=[] refs=[] strings=[]
T269 +1034 n=2 calls=[] refs=[] strings=[]
T270 +103c n=1 calls=[] refs=[] strings=[]
T271 +1040 n=3 calls=['AOSSi_Sleep'] refs=[] strings=[]
T272 +104c n=2 calls=[] refs=[] strings=[]
T273 +1054 n=1 calls=[] refs=[] strings=[]
T274 +1058 n=2 calls=[] refs=[] strings=[]
T275 +1060 n=2 calls=[] refs=[] strings=[]
T276 +1068 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T277 +1074 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T278 +1088 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T279 +1094 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T280 +10a0 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T281 +10ac n=2 calls=[] refs=[] strings=[]
T282 +10b4 n=23 calls=['SORecvFrom', 'SONtoHs', 'AOSS_814001B4'] refs=[('lbl_81697200', 0), ('lbl_81697200', 0), ('lbl_81697200', 0)] strings=[]
T283 +1110 n=2 calls=[] refs=[] strings=[]
T284 +1118 n=2 calls=[] refs=[] strings=[]
T285 +1120 n=2 calls=[] refs=[] strings=[]
T286 +1128 n=2 calls=[] refs=[] strings=[]
T287 +1130 n=2 calls=[] refs=[] strings=[]
T288 +1138 n=3 calls=[] refs=[('lbl_81697200', 0)] strings=[]
T289 +1144 n=1 calls=['SOClose'] refs=[] strings=[]
T290 +1148 n=4 calls=[] refs=[('lbl_81698C88', 0), ('lbl_81697200', 0)] strings=[]
T291 +1158 n=4 calls=['SOCleanup'] refs=[('lbl_81698C88', 0)] strings=[]
T292 +1168 n=2 calls=[] refs=[] strings=[]
T293 +1170 n=1 calls=[] refs=[] strings=[]
T294 +1174 n=2 calls=[] refs=[] strings=[]
T295 +117c n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T296 +1190 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T297 +119c n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T298 +11a8 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T299 +11b4 n=2 calls=[] refs=[] strings=[]
T300 +11bc n=3 calls=[] refs=[('lbl_8169720C', 0)] strings=[]
T301 +11c8 n=4 calls=['AOSSi_Status'] refs=[('lbl_8169720C', 0)] strings=[]
T302 +11d8 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T303 +11e4 n=2 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T304 +11ec n=4 calls=['AOSSi_WLANGetBSSList'] refs=[('lbl_81698C70', 0)] strings=[]
T305 +11fc n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T306 +1210 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T307 +121c n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T308 +1228 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T309 +1234 n=2 calls=[] refs=[] strings=[]
T310 +123c n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T311 +1248 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T312 +125c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T313 +1268 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T314 +1274 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T315 +1280 n=2 calls=[] refs=[] strings=[]
T316 +1288 n=4 calls=['AOSS_CheckAP'] refs=[('lbl_81698C70', 0)] strings=[]
T317 +1298 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T318 +12ac n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T319 +12b8 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T320 +12c4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T321 +12d0 n=2 calls=[] refs=[] strings=[]
T322 +12d8 n=2 calls=[] refs=[] strings=[]
T323 +12e0 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T324 +12f4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T325 +1300 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T326 +130c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T327 +1318 n=2 calls=[] refs=[] strings=[]
T328 +1320 n=5 calls=['AOSSi_Alloc'] refs=[('lbl_81698C74', 0)] strings=[]
T329 +1334 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T330 +1348 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T331 +1354 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T332 +1360 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T333 +136c n=2 calls=[] refs=[] strings=[]
T334 +1374 n=6 calls=['memset'] refs=[] strings=[]
T335 +138c n=5 calls=['AOSS_814020CC'] refs=[('lbl_81698C74', 0)] strings=[]
T336 +13a0 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T337 +13b4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T338 +13c0 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T339 +13cc n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T340 +13d8 n=2 calls=[] refs=[] strings=[]
T341 +13e0 n=2 calls=[] refs=[] strings=[]
T342 +13e8 n=1 calls=[] refs=[] strings=[]
T343 +13ec n=4 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T344 +13fc n=2 calls=[] refs=[] strings=[]
T345 +1404 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T346 +1410 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T347 +1424 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T348 +1430 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T349 +143c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T350 +1448 n=2 calls=[] refs=[] strings=[]
T351 +1450 n=2 calls=[] refs=[] strings=[]
T352 +1458 n=2 calls=[] refs=[] strings=[]
T353 +1460 n=1 calls=[] refs=[] strings=[]
T354 +1464 n=3 calls=['AOSSi_Sleep'] refs=[] strings=[]
T355 +1470 n=2 calls=[] refs=[] strings=[]
T356 +1478 n=1 calls=[] refs=[] strings=[]
T357 +147c n=2 calls=[] refs=[] strings=[]
T358 +1484 n=2 calls=[] refs=[] strings=[]
T359 +148c n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T360 +1498 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T361 +14ac n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T362 +14b8 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T363 +14c4 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T364 +14d0 n=2 calls=[] refs=[] strings=[]
T365 +14d8 n=1 calls=[] refs=[] strings=[]
T366 +14dc n=3 calls=[] refs=[] strings=[]
T367 +14e8 n=3 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T368 +14f4 n=2 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T369 +14fc n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T370 +1508 n=2 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T371 +1510 n=7 calls=['SOSocket'] refs=[('lbl_81697200', 0)] strings=[]
T372 +152c n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T373 +1540 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T374 +154c n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T375 +1558 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T376 +1564 n=2 calls=[] refs=[] strings=[]
T377 +156c n=16 calls=['memset', 'SOGetHostID', 'SOHtoNs', 'SOBind'] refs=[('lbl_81697200', 0)] strings=[]
T378 +15ac n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T379 +15c0 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T380 +15cc n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T381 +15d8 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T382 +15e4 n=2 calls=[] refs=[] strings=[]
T383 +15ec n=2 calls=[] refs=[] strings=[]
T384 +15f4 n=5 calls=[] refs=[] strings=[]
T385 +1608 n=2 calls=[] refs=[] strings=[]
T386 +1610 n=3 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T387 +161c n=2 calls=[] refs=[] strings=[]
T388 +1624 n=3 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T389 +1630 n=2 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T390 +1638 n=2 calls=[] refs=[] strings=[]
T391 +1640 n=2 calls=[] refs=[] strings=[]
T392 +1648 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T393 +1654 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T394 +1668 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T395 +1674 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T396 +1680 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T397 +168c n=2 calls=[] refs=[] strings=[]
T398 +1694 n=2 calls=[] refs=[] strings=[]
T399 +169c n=2 calls=[] refs=[] strings=[]
T400 +16a4 n=1 calls=[] refs=[] strings=[]
T401 +16a8 n=3 calls=['AOSSi_Sleep'] refs=[] strings=[]
T402 +16b4 n=2 calls=[] refs=[] strings=[]
T403 +16bc n=1 calls=[] refs=[] strings=[]
T404 +16c0 n=2 calls=[] refs=[] strings=[]
T405 +16c8 n=2 calls=[] refs=[] strings=[]
T406 +16d0 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
T407 +16dc n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T408 +16f0 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T409 +16fc n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T410 +1708 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T411 +1714 n=2 calls=[] refs=[] strings=[]
T412 +171c n=3 calls=[] refs=[('lbl_81697200', 0)] strings=[]
T413 +1728 n=1 calls=['SOClose'] refs=[] strings=[]
T414 +172c n=5 calls=[] refs=[('lbl_81698C88', 0), ('lbl_81697200', 0)] strings=[]
T415 +1740 n=5 calls=['SOCleanup'] refs=[('lbl_81698C88', 0)] strings=[]
T416 +1754 n=2 calls=[] refs=[] strings=[]
T417 +175c n=1 calls=[] refs=[] strings=[]
T418 +1760 n=2 calls=[] refs=[] strings=[]
T419 +1768 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T420 +177c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T421 +1788 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T422 +1794 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T423 +17a0 n=2 calls=[] refs=[] strings=[]
T424 +17a8 n=2 calls=[] refs=[] strings=[]
T425 +17b0 n=3 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T426 +17bc n=1 calls=[] refs=[] strings=[]
T427 +17c0 n=2 calls=[] refs=[] strings=[]
T428 +17c8 n=1 calls=[] refs=[] strings=[]
T429 +17cc n=1 calls=[] refs=[] strings=[]
T430 +17d0 n=2 calls=[] refs=[] strings=[]
T431 +17d8 n=1 calls=[] refs=[] strings=[]
T432 +17dc n=2 calls=[] refs=[] strings=[]
T433 +17e4 n=1 calls=[] refs=[] strings=[]
T434 +17e8 n=2 calls=[] refs=[] strings=[]
T435 +17f0 n=2 calls=[] refs=[] strings=[]
T436 +17f8 n=2 calls=[] refs=[] strings=[]
T437 +1800 n=2 calls=[] refs=[] strings=[]
T438 +1808 n=2 calls=[] refs=[] strings=[]
T439 +1810 n=1 calls=[] refs=[] strings=[]
T440 +1814 n=4 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T441 +1824 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T442 +1830 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T443 +183c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T444 +1848 n=2 calls=[] refs=[] strings=[]
T445 +1850 n=4 calls=['AOSS_813FFD68'] refs=[] strings=[]
T446 +1860 n=5 calls=[] refs=[('lbl_81698C74', 0)] strings=[]
T447 +1874 n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C74', 0)] strings=[]
T448 +1880 n=3 calls=[] refs=[('lbl_81698C70', 0)] strings=[]
T449 +188c n=3 calls=['AOSSi_Free'] refs=[('lbl_81698C70', 0)] strings=[]
T450 +1898 n=2 calls=[] refs=[] strings=[]
T451 +18a0 n=1 calls=[] refs=[] strings=[]
T452 +18a4 n=7 calls=['_restgpr_14'] refs=[] strings=[]
BUILT BASIC BLOCKS
M000 +0000 n=25 calls=['_savegpr_14', 'memset'] refs=[('s_defaultOptions', 0), ('s_defaultOptions', 0)] strings=[]
M001 +0064 n=2 calls=[] refs=[] strings=[]
M002 +006c n=4 calls=[] refs=[] strings=[]
M003 +007c n=2 calls=[] refs=[] strings=[]
M004 +0084 n=4 calls=[] refs=[] strings=[]
M005 +0094 n=2 calls=[] refs=[] strings=[]
M006 +009c n=4 calls=[] refs=[] strings=[]
M007 +00ac n=2 calls=[] refs=[] strings=[]
M008 +00b4 n=3 calls=[] refs=[] strings=[]
M009 +00c0 n=1 calls=[] refs=[] strings=[]
M010 +00c4 n=31 calls=['memset', 'memset'] refs=[('s_accessPointName', 0), ('s_runtime', 0), ('s_errorCode', 0), ('s_runtime', 0), ('s_runtime', 0), ('s_runtime', 0)] strings=[]
M011 +0140 n=7 calls=[] refs=[('s_errorCode', 0), ('s_accessPointConfig', 0)] strings=[]
M012 +015c n=2 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M013 +0164 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M014 +0170 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M015 +017c n=2 calls=[] refs=[] strings=[]
M016 +0184 n=5 calls=[] refs=[('s_operationState', 0)] strings=[]
M017 +0198 n=3 calls=['AOSSi_Status'] refs=[('s_operationState', 0)] strings=[]
M018 +01a4 n=1 calls=[] refs=[] strings=[]
M019 +01a8 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M020 +01b4 n=2 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M021 +01bc n=4 calls=['AOSSi_WLANGetBSSList'] refs=[('s_accessPointList', 0)] strings=[]
M022 +01cc n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M023 +01e0 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M024 +01ec n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M025 +01f8 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M026 +0204 n=2 calls=[] refs=[] strings=[]
M027 +020c n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M028 +0218 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M029 +022c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M030 +0238 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M031 +0244 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M032 +0250 n=2 calls=[] refs=[] strings=[]
M033 +0258 n=4 calls=['AOSS_CheckAP'] refs=[('s_accessPointList', 0)] strings=[]
M034 +0268 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M035 +027c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M036 +0288 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M037 +0294 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M038 +02a0 n=2 calls=[] refs=[] strings=[]
M039 +02a8 n=2 calls=[] refs=[] strings=[]
M040 +02b0 n=4 calls=[] refs=[] strings=[]
M041 +02c0 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M042 +02d4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M043 +02e0 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M044 +02ec n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M045 +02f8 n=2 calls=[] refs=[] strings=[]
M046 +0300 n=1 calls=[] refs=[] strings=[]
M047 +0304 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M048 +0310 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M049 +0324 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M050 +0330 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M051 +033c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M052 +0348 n=2 calls=[] refs=[] strings=[]
M053 +0350 n=5 calls=[] refs=[] strings=[]
M054 +0364 n=1 calls=[] refs=[] strings=[]
M055 +0368 n=4 calls=['AOSSi_Sleep'] refs=[] strings=[]
M056 +0378 n=1 calls=[] refs=[] strings=[]
M057 +037c n=1 calls=[] refs=[] strings=[]
M058 +0380 n=2 calls=[] refs=[] strings=[]
M059 +0388 n=2 calls=[] refs=[] strings=[]
M060 +0390 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M061 +039c n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M062 +03b0 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M063 +03bc n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M064 +03c8 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M065 +03d4 n=2 calls=[] refs=[] strings=[]
M066 +03dc n=2 calls=[] refs=[] strings=[]
M067 +03e4 n=3 calls=[] refs=[('s_operationState', 0)] strings=[]
M068 +03f0 n=4 calls=['AOSSi_Status'] refs=[('s_operationState', 0)] strings=[]
M069 +0400 n=19 calls=['memset', 'strlen', 'memcpy', 'strlen'] refs=[('@2491', 0), ('@2491', 0), ('@2491', 0), ('s_manufacturer', 0)] strings=['ESSID-AOSS', 'ESSID-AOSS', 'ESSID-AOSS', 'MELCO']
M070 +044c n=4 calls=['memcpy'] refs=[('s_manufacturer', 0)] strings=['MELCO']
M071 +045c n=9 calls=['AOSSi_SetNCDIPAddr'] refs=[] strings=[]
M072 +0480 n=7 calls=[] refs=[('s_errorCode', 0), ('s_accessPointConfig', 0)] strings=[]
M073 +049c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M074 +04a8 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M075 +04b4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M076 +04c0 n=2 calls=[] refs=[] strings=[]
M077 +04c8 n=5 calls=['AOSSi_Alloc'] refs=[('s_accessPointConfig', 0)] strings=[]
M078 +04dc n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M079 +04f0 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M080 +04fc n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M081 +0508 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M082 +0514 n=2 calls=[] refs=[] strings=[]
M083 +051c n=5 calls=['memset'] refs=[] strings=[]
M084 +0530 n=3 calls=[] refs=[] strings=[]
M085 +053c n=5 calls=['AOSS_814020CC'] refs=[('s_accessPointConfig', 0)] strings=[]
M086 +0550 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M087 +0564 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M088 +0570 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M089 +057c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M090 +0588 n=2 calls=[] refs=[] strings=[]
M091 +0590 n=3 calls=[] refs=[] strings=[]
M092 +059c n=4 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M093 +05ac n=1 calls=[] refs=[] strings=[]
M094 +05b0 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M095 +05bc n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M096 +05d0 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M097 +05dc n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M098 +05e8 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M099 +05f4 n=2 calls=[] refs=[] strings=[]
M100 +05fc n=5 calls=[] refs=[] strings=[]
M101 +0610 n=1 calls=[] refs=[] strings=[]
M102 +0614 n=4 calls=['AOSSi_Sleep'] refs=[] strings=[]
M103 +0624 n=1 calls=[] refs=[] strings=[]
M104 +0628 n=1 calls=[] refs=[] strings=[]
M105 +062c n=2 calls=[] refs=[] strings=[]
M106 +0634 n=2 calls=[] refs=[] strings=[]
M107 +063c n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M108 +0648 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M109 +065c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M110 +0668 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M111 +0674 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M112 +0680 n=2 calls=[] refs=[] strings=[]
M113 +0688 n=2 calls=[] refs=[] strings=[]
M114 +0690 n=4 calls=[] refs=[] strings=[]
M115 +06a0 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M116 +06b4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M117 +06c0 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M118 +06cc n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M119 +06d8 n=2 calls=[] refs=[] strings=[]
M120 +06e0 n=3 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M121 +06ec n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M122 +06f8 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M123 +0704 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M124 +0710 n=3 calls=[] refs=[] strings=[]
M125 +071c n=18 calls=['memcpy', 'rand', 'SOHtoNs'] refs=[] strings=[]
M126 +0764 n=7 calls=['SOSocket'] refs=[('s_socket', 0)] strings=[]
M127 +0780 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M128 +0794 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M129 +07a0 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M130 +07ac n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M131 +07b8 n=2 calls=[] refs=[] strings=[]
M132 +07c0 n=2 calls=[] refs=[] strings=[]
M133 +07c8 n=7 calls=[] refs=[('s_errorCode', 0), ('s_accessPointConfig', 0)] strings=[]
M134 +07e4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M135 +07f0 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M136 +07fc n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M137 +0808 n=2 calls=[] refs=[] strings=[]
M138 +0810 n=18 calls=['memset', 'SOGetHostID', 'SOHtoNs', 'SOBind'] refs=[('s_socket', 0)] strings=[]
M139 +0858 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M140 +086c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M141 +0878 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M142 +0884 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M143 +0890 n=2 calls=[] refs=[] strings=[]
M144 +0898 n=17 calls=[] refs=[('s_runtime', 0), ('s_runtime', 0)] strings=[]
M145 +08dc n=9 calls=['memset'] refs=[('s_responseBuffer', 0)] strings=[]
M146 +0900 n=2 calls=[] refs=[] strings=[]
M147 +0908 n=3 calls=[] refs=[] strings=[]
M148 +0914 n=3 calls=[] refs=[('s_socket', 0)] strings=[]
M149 +0920 n=1 calls=['SOClose'] refs=[] strings=[]
M150 +0924 n=4 calls=[] refs=[('s_socketStarted', 0), ('s_socket', 0)] strings=[]
M151 +0934 n=4 calls=['SOCleanup'] refs=[('s_socketStarted', 0)] strings=[]
M152 +0944 n=2 calls=[] refs=[] strings=[]
M153 +094c n=1 calls=[] refs=[] strings=[]
M154 +0950 n=2 calls=[] refs=[] strings=[]
M155 +0958 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M156 +096c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M157 +0978 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M158 +0984 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M159 +0990 n=2 calls=[] refs=[] strings=[]
M160 +0998 n=9 calls=[] refs=[] strings=[]
M161 +09bc n=1 calls=[] refs=[] strings=[]
M162 +09c0 n=8 calls=['AOSSi_SetNCDIPAddr'] refs=[] strings=[]
M163 +09e0 n=7 calls=[] refs=[('s_errorCode', 0), ('s_accessPointConfig', 0)] strings=[]
M164 +09fc n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M165 +0a08 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M166 +0a14 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M167 +0a20 n=2 calls=[] refs=[] strings=[]
M168 +0a28 n=6 calls=['AOSSi_Alloc'] refs=[('s_accessPointConfig', 0)] strings=[]
M169 +0a40 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M170 +0a54 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M171 +0a60 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M172 +0a6c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M173 +0a78 n=2 calls=[] refs=[] strings=[]
M174 +0a80 n=6 calls=['memset'] refs=[] strings=[]
M175 +0a98 n=5 calls=['AOSS_814020CC'] refs=[('s_accessPointConfig', 0)] strings=[]
M176 +0aac n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M177 +0ac0 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M178 +0acc n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M179 +0ad8 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M180 +0ae4 n=2 calls=[] refs=[] strings=[]
M181 +0aec n=3 calls=[] refs=[] strings=[]
M182 +0af8 n=4 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M183 +0b08 n=1 calls=[] refs=[] strings=[]
M184 +0b0c n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M185 +0b18 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M186 +0b2c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M187 +0b38 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M188 +0b44 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M189 +0b50 n=2 calls=[] refs=[] strings=[]
M190 +0b58 n=5 calls=[] refs=[] strings=[]
M191 +0b6c n=1 calls=[] refs=[] strings=[]
M192 +0b70 n=4 calls=['AOSSi_Sleep'] refs=[] strings=[]
M193 +0b80 n=1 calls=[] refs=[] strings=[]
M194 +0b84 n=1 calls=[] refs=[] strings=[]
M195 +0b88 n=2 calls=[] refs=[] strings=[]
M196 +0b90 n=2 calls=[] refs=[] strings=[]
M197 +0b98 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M198 +0ba4 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M199 +0bb8 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M200 +0bc4 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M201 +0bd0 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M202 +0bdc n=2 calls=[] refs=[] strings=[]
M203 +0be4 n=1 calls=[] refs=[] strings=[]
M204 +0be8 n=3 calls=[] refs=[] strings=[]
M205 +0bf4 n=7 calls=['SOSocket'] refs=[('s_socket', 0)] strings=[]
M206 +0c10 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M207 +0c24 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M208 +0c30 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M209 +0c3c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M210 +0c48 n=2 calls=[] refs=[] strings=[]
M211 +0c50 n=16 calls=['memset', 'SOGetHostID', 'SOHtoNs', 'SOBind'] refs=[('s_socket', 0)] strings=[]
M212 +0c90 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M213 +0ca4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M214 +0cb0 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M215 +0cbc n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M216 +0cc8 n=2 calls=[] refs=[] strings=[]
M217 +0cd0 n=3 calls=[] refs=[('s_socket', 0)] strings=[]
M218 +0cdc n=1 calls=[] refs=[] strings=[]
M219 +0ce0 n=2 calls=[] refs=[] strings=[]
M220 +0ce8 n=1 calls=[] refs=[] strings=[]
M221 +0cec n=2 calls=[] refs=[] strings=[]
M222 +0cf4 n=1 calls=[] refs=[] strings=[]
M223 +0cf8 n=3 calls=[] refs=[('s_operationState', 0)] strings=[]
M224 +0d04 n=3 calls=['AOSSi_Status'] refs=[('s_operationState', 0)] strings=[]
M225 +0d10 n=6 calls=['AOSS_81401574'] refs=[] strings=[]
M226 +0d28 n=3 calls=[] refs=[('s_operationState', 0)] strings=[]
M227 +0d34 n=4 calls=['AOSSi_Status'] refs=[('s_operationState', 0)] strings=[]
M228 +0d44 n=6 calls=['AOSS_81401778'] refs=[] strings=[]
M229 +0d5c n=3 calls=[] refs=[('s_operationState', 0)] strings=[]
M230 +0d68 n=4 calls=['AOSSi_Status'] refs=[('s_operationState', 0)] strings=[]
M231 +0d78 n=52 calls=['memset', 'memcpy', 'strlen', 'AOSS_81401E80', 'SOHtoNs', 'SOHtoNs', 'SOHtoNs', 'SOHtoNs', 'memcpy', 'memset', 'SOHtoNs', 'SOHtoNl'] refs=[('s_responseBuffer', 0), ('s_manufacturer', 0), ('s_manufacturer', 0)] strings=['MELCO', 'MELCO']
M232 +0e48 n=1 calls=[] refs=[] strings=[]
M233 +0e4c n=9 calls=['SOSendTo'] refs=[] strings=[]
M234 +0e70 n=1 calls=[] refs=[] strings=[]
M235 +0e74 n=2 calls=[] refs=[] strings=[]
M236 +0e7c n=7 calls=[] refs=[('s_errorCode', 0), ('s_accessPointConfig', 0)] strings=[]
M237 +0e98 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M238 +0ea4 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M239 +0eb0 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M240 +0ebc n=2 calls=[] refs=[] strings=[]
M241 +0ec4 n=39 calls=['memset', 'SOPoll'] refs=[('s_socket', 0)] strings=[]
M242 +0f60 n=6 calls=[] refs=[] strings=[]
M243 +0f78 n=2 calls=[] refs=[] strings=[]
M244 +0f80 n=1 calls=[] refs=[] strings=[]
M245 +0f84 n=2 calls=[] refs=[] strings=[]
M246 +0f8c n=1 calls=[] refs=[] strings=[]
M247 +0f90 n=3 calls=[] refs=[('s_errorCode', 0)] strings=[]
M248 +0f9c n=3 calls=[] refs=[('s_errorCode', 0)] strings=[]
M249 +0fa8 n=2 calls=[] refs=[('s_errorCode', 0)] strings=[]
M250 +0fb0 n=2 calls=[] refs=[] strings=[]
M251 +0fb8 n=1 calls=[] refs=[] strings=[]
M252 +0fbc n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M253 +0fc8 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M254 +0fdc n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M255 +0fe8 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M256 +0ff4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M257 +1000 n=2 calls=[] refs=[] strings=[]
M258 +1008 n=3 calls=[] refs=[] strings=[]
M259 +1014 n=2 calls=[] refs=[] strings=[]
M260 +101c n=1 calls=[] refs=[] strings=[]
M261 +1020 n=3 calls=['AOSSi_Sleep'] refs=[] strings=[]
M262 +102c n=2 calls=[] refs=[] strings=[]
M263 +1034 n=1 calls=[] refs=[] strings=[]
M264 +1038 n=2 calls=[] refs=[] strings=[]
M265 +1040 n=2 calls=[] refs=[] strings=[]
M266 +1048 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M267 +1054 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M268 +1068 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M269 +1074 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M270 +1080 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M271 +108c n=2 calls=[] refs=[] strings=[]
M272 +1094 n=22 calls=['SORecvFrom', 'SONtoHs', 'AOSS_814001B4'] refs=[('s_socket', 0), ('s_socket', 0), ('s_socket', 0)] strings=[]
M273 +10ec n=2 calls=[] refs=[] strings=[]
M274 +10f4 n=2 calls=[] refs=[] strings=[]
M275 +10fc n=2 calls=[] refs=[] strings=[]
M276 +1104 n=2 calls=[] refs=[] strings=[]
M277 +110c n=3 calls=[] refs=[] strings=[]
M278 +1118 n=3 calls=[] refs=[('s_socket', 0)] strings=[]
M279 +1124 n=1 calls=['SOClose'] refs=[] strings=[]
M280 +1128 n=4 calls=[] refs=[('s_socketStarted', 0), ('s_socket', 0)] strings=[]
M281 +1138 n=4 calls=['SOCleanup'] refs=[('s_socketStarted', 0)] strings=[]
M282 +1148 n=2 calls=[] refs=[] strings=[]
M283 +1150 n=1 calls=[] refs=[] strings=[]
M284 +1154 n=2 calls=[] refs=[] strings=[]
M285 +115c n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M286 +1170 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M287 +117c n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M288 +1188 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M289 +1194 n=2 calls=[] refs=[] strings=[]
M290 +119c n=3 calls=[] refs=[('s_operationState', 0)] strings=[]
M291 +11a8 n=4 calls=['AOSSi_Status'] refs=[('s_operationState', 0)] strings=[]
M292 +11b8 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M293 +11c4 n=2 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M294 +11cc n=4 calls=['AOSSi_WLANGetBSSList'] refs=[('s_accessPointList', 0)] strings=[]
M295 +11dc n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M296 +11f0 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M297 +11fc n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M298 +1208 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M299 +1214 n=2 calls=[] refs=[] strings=[]
M300 +121c n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M301 +1228 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M302 +123c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M303 +1248 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M304 +1254 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M305 +1260 n=2 calls=[] refs=[] strings=[]
M306 +1268 n=4 calls=['AOSS_CheckAP'] refs=[('s_accessPointList', 0)] strings=[]
M307 +1278 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M308 +128c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M309 +1298 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M310 +12a4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M311 +12b0 n=2 calls=[] refs=[] strings=[]
M312 +12b8 n=2 calls=[] refs=[] strings=[]
M313 +12c0 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M314 +12d4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M315 +12e0 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M316 +12ec n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M317 +12f8 n=2 calls=[] refs=[] strings=[]
M318 +1300 n=5 calls=['AOSSi_Alloc'] refs=[('s_accessPointConfig', 0)] strings=[]
M319 +1314 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M320 +1328 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M321 +1334 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M322 +1340 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M323 +134c n=2 calls=[] refs=[] strings=[]
M324 +1354 n=6 calls=['memset'] refs=[] strings=[]
M325 +136c n=5 calls=['AOSS_814020CC'] refs=[('s_accessPointConfig', 0)] strings=[]
M326 +1380 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M327 +1394 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M328 +13a0 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M329 +13ac n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M330 +13b8 n=2 calls=[] refs=[] strings=[]
M331 +13c0 n=3 calls=[] refs=[] strings=[]
M332 +13cc n=4 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M333 +13dc n=1 calls=[] refs=[] strings=[]
M334 +13e0 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M335 +13ec n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M336 +1400 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M337 +140c n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M338 +1418 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M339 +1424 n=2 calls=[] refs=[] strings=[]
M340 +142c n=5 calls=[] refs=[] strings=[]
M341 +1440 n=1 calls=[] refs=[] strings=[]
M342 +1444 n=4 calls=['AOSSi_Sleep'] refs=[] strings=[]
M343 +1454 n=1 calls=[] refs=[] strings=[]
M344 +1458 n=1 calls=[] refs=[] strings=[]
M345 +145c n=2 calls=[] refs=[] strings=[]
M346 +1464 n=2 calls=[] refs=[] strings=[]
M347 +146c n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M348 +1478 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M349 +148c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M350 +1498 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M351 +14a4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M352 +14b0 n=2 calls=[] refs=[] strings=[]
M353 +14b8 n=1 calls=[] refs=[] strings=[]
M354 +14bc n=3 calls=[] refs=[] strings=[]
M355 +14c8 n=3 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M356 +14d4 n=2 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M357 +14dc n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M358 +14e8 n=2 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M359 +14f0 n=7 calls=['SOSocket'] refs=[('s_socket', 0)] strings=[]
M360 +150c n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M361 +1520 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M362 +152c n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M363 +1538 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M364 +1544 n=2 calls=[] refs=[] strings=[]
M365 +154c n=16 calls=['memset', 'SOGetHostID', 'SOHtoNs', 'SOBind'] refs=[('s_socket', 0)] strings=[]
M366 +158c n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M367 +15a0 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M368 +15ac n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M369 +15b8 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M370 +15c4 n=2 calls=[] refs=[] strings=[]
M371 +15cc n=2 calls=[] refs=[] strings=[]
M372 +15d4 n=5 calls=[] refs=[] strings=[]
M373 +15e8 n=2 calls=[] refs=[] strings=[]
M374 +15f0 n=1 calls=[] refs=[] strings=[]
M375 +15f4 n=2 calls=[] refs=[] strings=[]
M376 +15fc n=1 calls=[] refs=[] strings=[]
M377 +1600 n=3 calls=[] refs=[('s_errorCode', 0)] strings=[]
M378 +160c n=3 calls=[] refs=[('s_errorCode', 0)] strings=[]
M379 +1618 n=2 calls=[] refs=[('s_errorCode', 0)] strings=[]
M380 +1620 n=2 calls=[] refs=[] strings=[]
M381 +1628 n=2 calls=[] refs=[] strings=[]
M382 +1630 n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M383 +163c n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M384 +1650 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M385 +165c n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M386 +1668 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M387 +1674 n=2 calls=[] refs=[] strings=[]
M388 +167c n=3 calls=[] refs=[] strings=[]
M389 +1688 n=2 calls=[] refs=[] strings=[]
M390 +1690 n=1 calls=[] refs=[] strings=[]
M391 +1694 n=3 calls=['AOSSi_Sleep'] refs=[] strings=[]
M392 +16a0 n=2 calls=[] refs=[] strings=[]
M393 +16a8 n=1 calls=[] refs=[] strings=[]
M394 +16ac n=2 calls=[] refs=[] strings=[]
M395 +16b4 n=2 calls=[] refs=[] strings=[]
M396 +16bc n=3 calls=[] refs=[('AOSSi_cancel_flag', 0)] strings=[]
M397 +16c8 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M398 +16dc n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M399 +16e8 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M400 +16f4 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M401 +1700 n=2 calls=[] refs=[] strings=[]
M402 +1708 n=3 calls=[] refs=[('s_socket', 0)] strings=[]
M403 +1714 n=1 calls=['SOClose'] refs=[] strings=[]
M404 +1718 n=5 calls=[] refs=[('s_socketStarted', 0), ('s_socket', 0)] strings=[]
M405 +172c n=5 calls=['SOCleanup'] refs=[('s_socketStarted', 0)] strings=[]
M406 +1740 n=2 calls=[] refs=[] strings=[]
M407 +1748 n=1 calls=[] refs=[] strings=[]
M408 +174c n=2 calls=[] refs=[] strings=[]
M409 +1754 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M410 +1768 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M411 +1774 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M412 +1780 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M413 +178c n=2 calls=[] refs=[] strings=[]
M414 +1794 n=2 calls=[] refs=[] strings=[]
M415 +179c n=3 calls=[] refs=[('s_errorCode', 0)] strings=[]
M416 +17a8 n=1 calls=[] refs=[] strings=[]
M417 +17ac n=2 calls=[] refs=[] strings=[]
M418 +17b4 n=1 calls=[] refs=[] strings=[]
M419 +17b8 n=1 calls=[] refs=[] strings=[]
M420 +17bc n=2 calls=[] refs=[] strings=[]
M421 +17c4 n=1 calls=[] refs=[] strings=[]
M422 +17c8 n=2 calls=[] refs=[] strings=[]
M423 +17d0 n=1 calls=[] refs=[] strings=[]
M424 +17d4 n=3 calls=[] refs=[] strings=[]
M425 +17e0 n=3 calls=[] refs=[] strings=[]
M426 +17ec n=3 calls=[] refs=[] strings=[]
M427 +17f8 n=3 calls=[] refs=[] strings=[]
M428 +1804 n=3 calls=[] refs=[] strings=[]
M429 +1810 n=2 calls=[] refs=[] strings=[]
M430 +1818 n=3 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M431 +1824 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M432 +1830 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M433 +183c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M434 +1848 n=2 calls=[] refs=[] strings=[]
M435 +1850 n=4 calls=['AOSS_813FFD68'] refs=[] strings=[]
M436 +1860 n=2 calls=[] refs=[] strings=[]
M437 +1868 n=5 calls=[] refs=[('s_accessPointConfig', 0)] strings=[]
M438 +187c n=3 calls=['AOSSi_Free'] refs=[('s_accessPointConfig', 0)] strings=[]
M439 +1888 n=3 calls=[] refs=[('s_accessPointList', 0)] strings=[]
M440 +1894 n=3 calls=['AOSSi_Free'] refs=[('s_accessPointList', 0)] strings=[]
M441 +18a0 n=1 calls=[] refs=[] strings=[]
M442 +18a4 n=7 calls=['_restgpr_14'] refs=[] strings=[]
ALIGNMENT; each unequal span lists all target/built blocks
replace: T0:1 +25 / M0:1 +25
replace: T10:11 +30 / M10:11 +31
replace: T16:17 +4 / M16:17 +5
replace: T18:19 +2 / M18:19 +1
replace: T21:22 +4 / M21:22 +4
replace: T40:41 +3 / M40:41 +4
replace: T46:47 +2 / M46:47 +1
replace: T53:61 +15 / M53:60 +16
replace: T70:73 +24 / M69:71 +23
delete: T75:81 +17 / M73:73 +0
replace: T91:92 +6 / M83:85 +8
replace: T98:102 +9 / M91:94 +8
replace: T108:116 +15 / M100:107 +16
replace: T122:125 +8 / M113:115 +6
replace: T134:136 +18 / M124:126 +21
replace: T154:156 +27 / M144:146 +26
replace: T161:162 +4 / M151:152 +4
replace: T170:171 +9 / M160:161 +9
replace: T172:173 +7 / M162:163 +8
replace: T178:179 +6 / M168:169 +6
replace: T191:195 +9 / M181:184 +8
replace: T201:209 +15 / M190:197 +16
replace: T237:238 +5 / M225:226 +6
replace: T240:241 +5 / M228:229 +6
replace: T243:244 +52 / M231:232 +52
replace: T253:256 +46 / M241:247 +51
delete: T257:258 +2 / M248:248 +0
replace: T261:262 +2 / M251:252 +1
replace: T268:269 +2 / M258:259 +3
replace: T271:274 +6 / M261:264 +6
replace: T282:283 +23 / M272:273 +22
replace: T287:288 +2 / M277:278 +3
replace: T304:305 +4 / M294:295 +4
replace: T328:329 +5 / M318:319 +5
replace: T341:345 +9 / M331:334 +8
replace: T351:359 +15 / M340:347 +16
replace: T385:386 +2 / M373:377 +6
delete: T387:388 +2 / M378:378 +0
replace: T398:399 +2 / M388:389 +3
replace: T401:404 +6 / M391:394 +6
replace: T415:416 +5 / M405:406 +5
replace: T434:441 +15 / M424:431 +20
replace: T445:446 +4 / M435:437 +6
delete: T450:451 +2 / M441:441 +0
CALL-ALIGNED REGIONS
R001: T[8:21] M[8:21] deficit +0 before memset
R002: T[21:53] M[21:53] deficit +0 before memset
R004: T[60:87] M[60:88] deficit -1 before AOSSi_Free
R006: T[92:103] M[93:105] deficit -1 before AOSSi_Status
R007: T[103:109] M[105:110] deficit +1 before AOSSi_Free
R008: T[109:112] M[110:113] deficit +0 before AOSSi_WLANGetBSSList
R016: T[165:180] M[166:182] deficit -1 before AOSSi_Free
R018: T[186:201] M[188:202] deficit +1 before AOSSi_Free
R020: T[207:217] M[208:219] deficit -1 before AOSSi_Sleep
R021: T[217:235] M[219:237] deficit +0 before AOSSi_Free
R027: T[266:270] M[268:272] deficit +0 before strlen
R028: T[270:278] M[272:279] deficit +1 before memcpy
R030: T[285:312] M[286:296] deficit +17 before AOSSi_Free
R036: T[346:352] M[330:338] deficit -2 before AOSS_814020CC
R039: T[366:388] M[352:373] deficit +1 before AOSSi_Free
R041: T[394:404] M[379:390] deficit -1 before AOSSi_Sleep
R042: T[404:422] M[390:408] deficit +0 before AOSSi_Free
R044: T[428:446] M[414:430] deficit +2 before AOSSi_Free
R048: T[466:476] M[450:462] deficit -2 before memcpy
R050: T[477:481] M[463:467] deficit +0 before SOHtoNs
R051: T[481:490] M[467:477] deficit -1 before SOSocket
R062: T[559:586] M[546:572] deficit +1 before memset
R063: T[586:599] M[572:585] deficit +0 before SOClose
R065: T[605:618] M[591:604] deficit +0 before AOSSi_Free
R067: T[624:643] M[610:630] deficit -1 before AOSSi_SetNCDIPAddr
R071: T[666:675] M[653:662] deficit +0 before AOSSi_Free
R077: T[708:730] M[695:716] deficit +1 before AOSSi_Free
R079: T[736:746] M[722:733] deficit -1 before AOSSi_Sleep
R080: T[746:764] M[733:751] deficit +0 before AOSSi_Free
R093: T[853:861] M[840:849] deficit -1 before AOSSi_Status
R095: T[865:873] M[853:862] deficit -1 before AOSSi_Status
R098: T[882:884] M[871:873] deficit +0 before strlen
R099: T[884:889] M[873:878] deficit +0 before AOSS_81401E80
R112: T[960:993] M[949:982] deficit +0 before SOPoll
R113: T[993:1025] M[982:1016] deficit -2 before AOSSi_Free
R115: T[1031:1041] M[1022:1033] deficit -1 before AOSSi_Sleep
R116: T[1041:1059] M[1033:1051] deficit +0 before AOSSi_Free
R118: T[1065:1077] M[1057:1068] deficit +1 before SORecvFrom
R121: T[1089:1106] M[1080:1098] deficit -1 before SOClose
R127: T[1146:1149] M[1138:1141] deficit +0 before AOSSi_WLANGetBSSList
R138: T[1226:1235] M[1218:1227] deficit +0 before AOSSi_Free
R144: T[1268:1290] M[1260:1281] deficit +1 before AOSSi_Free
R146: T[1296:1306] M[1287:1298] deficit -1 before AOSSi_Sleep
R147: T[1306:1324] M[1298:1316] deficit +0 before AOSSi_Free
R160: T[1399:1435] M[1391:1429] deficit -2 before AOSSi_Free
R162: T[1441:1451] M[1435:1446] deficit -1 before AOSSi_Sleep
R163: T[1451:1469] M[1446:1464] deficit +0 before AOSSi_Free
R167: T[1491:1504] M[1486:1499] deficit +0 before AOSSi_Free
R169: T[1510:1546] M[1505:1546] deficit -5 before AOSSi_Free
R172: T[1558:1566] M[1558:1568] deficit -2 before AOSSi_Free
R174: T[1572:1580] M[1574:1580] deficit +2 before _restgpr_14
```

Target-only opcode spans within each unequal call region:

```text
R001 replace target +0020..+0024 (1) vs built [8:9] (1)
  +0020 lhz r4, lbl_81694C78@sda21(r0)
R001 delete target +0034..+0038 (1) vs built [15:15] (0)
  +0034 addi r3, r1, 0xa0
R001 delete target +0044..+0048 (1) vs built [18:18] (0)
  +0044 li r5, 0x18
R002 replace target +00c4..+00c8 (1) vs built [49:50] (1)
  +00c4 addi r3, lbl_81698C78@sda21
R004 delete target +0118..+011c (1) vs built [70:70] (0)
  +0118 clrlwi r0, r0, 31
R004 delete target +0120..+0124 (1) vs built [71:71] (0)
  +0120 cmplwi r0, 0x1
R007 delete target +019c..+01a0 (1) vs built [105:105] (0)
  +019c lha r16, 0x28(r1)
R008 replace target +01b8..+01bc (1) vs built [111:112] (1)
  +01b8 addi r3, lbl_81698C70@sda21
R016 replace target +02b4..+02b8 (1) vs built [175:176] (1)
  +02b4 blt .L_813FE7A0
R018 delete target +02f8..+02fc (1) vs built [192:192] (0)
  +02f8 lhz r21, 0x2a(r1)
R020 delete target +0358..+0360 (2) vs built [218:218] (0)
  +0358 b .L_813FE808
  +035c mr r3, r21
R021 replace target +0368..+036c (1) vs built [221:223] (2)
  +0368 ble .L_813FE81C
R021 replace target +0370..+0378 (2) vs built [224:225] (1)
  +0370 b .L_813FE820
  +0374 mr r0, r21
R021 replace target +037c..+0384 (2) vs built [226:227] (1)
  +037c clrlwi r21, r0, 16
  +0380 cmpwi r21, 0x0
R027 replace target +042c..+0430 (1) vs built [269:270] (1)
  +042c addi r3, lbl_81697204@sda21
R028 replace target +0440..+0448 (2) vs built [274:275] (1)
  +0440 ble .L_813FE8F0
  +0444 b .L_813FE900
R028 replace target +0450..+0454 (1) vs built [277:278] (1)
  +0450 addi r4, lbl_81697204@sda21
R030 delete target +049c..+04e0 (17) vs built [296:296] (0)
  +049c li r0, 0x0
  +04a0 stw r0, lbl_81698C74@sda21(r0)
  +04a4 lwz r3, lbl_81698C70@sda21(r0)
  +04a8 cmpwi r3, 0x0
  +04ac beq .L_813FE964
  +04b0 bl AOSSi_Free
  +04b4 li r0, 0x0
  +04b8 stw r0, lbl_81698C70@sda21(r0)
  +04bc li r3, -0x1
  +04c0 b .L_813FFD4C
  +04c4 beq .L_813FE9B0
  +04c8 li r0, 0xf
  +04cc stb r0, 0x116(r15)
  +04d0 lwz r3, lbl_81698C74@sda21(r0)
  +04d4 cmpwi r3, 0x0
  +04d8 beq .L_813FE990
  +04dc bl AOSSi_Free
R036 replace target +0570..+0574 (1) vs built [332:335] (3)
  +0570 b .L_813FEB6C
R039 replace target +05cc..+05d0 (1) vs built [357:358] (1)
  +05cc bne .L_813FEA8C
R039 replace target +05dc..+05e0 (1) vs built [361:362] (1)
  +05dc cmplwi r0, 0x1
R039 delete target +05e4..+05e8 (1) vs built [363:363] (0)
  +05e4 lhz r17, 0x2a(r1)
R041 delete target +0644..+064c (2) vs built [389:389] (0)
  +0644 b .L_813FEAF4
  +0648 mr r3, r17
R042 replace target +0654..+0658 (1) vs built [392:394] (2)
  +0654 ble .L_813FEB08
R042 replace target +065c..+0664 (2) vs built [395:396] (1)
  +065c b .L_813FEB0C
  +0660 mr r0, r17
R042 replace target +0668..+0670 (2) vs built [397:398] (1)
  +0668 clrlwi r17, r0, 16
  +066c cmpwi r17, 0x0
R044 replace target +06c4..+06d0 (3) vs built [419:420] (1)
  +06c4 extsh r0, r18
  +06c8 cmpw r0, r16
  +06cc blt .L_813FEA1C
R044 replace target +06d4..+06d8 (1) vs built [421:422] (1)
  +06d4 extsh r3, r18
R048 replace target +0750..+0754 (1) vs built [452:453] (1)
  +0750 addi r17, r1, 0xa0
R048 replace target +0768..+076c (1) vs built [460:461] (1)
  +0768 li r5, 0x6
R050 replace target +0774..+0778 (1) vs built [463:465] (2)
  +0774 add r21, r17, r16
R050 delete target +077c..+0780 (1) vs built [466:466] (0)
  +077c clrlwi r3, r3, 16
R062 replace target +08e0..+08e4 (1) vs built [555:556] (1)
  +08e0 lis r3, 0x431c
R062 delete target +08f8..+0904 (3) vs built [563:563] (0)
  +08f8 addi r30, r3, 0x217d
  +08fc stw r0, 0xf8(r1)
  +0900 li r14, 0x11
R063 delete target +0930..+0934 (1) vs built [575:575] (0)
  +0930 lwz r0, 0xf8(r1)
R065 replace target +0978..+097c (1) vs built [592:593] (1)
  +0978 bge .L_813FEE2C
R067 delete target +09e8..+09ec (1) vs built [621:621] (0)
  +09e8 or r3, r5, r0
R067 replace target +09f0..+09f4 (1) vs built [622:623] (1)
  +09f0 blt .L_813FEEA0
R067 delete target +0a00..+0a04 (1) vs built [628:628] (0)
  +0a00 lwz r5, 0x10(r27)
R071 replace target +0a68..+0a6c (1) vs built [653:654] (1)
  +0a68 cmpwi r3, 0x0
R077 replace target +0b24..+0b28 (1) vs built [700:701] (1)
  +0b24 bne .L_813FEFE4
R077 replace target +0b34..+0b38 (1) vs built [704:705] (1)
  +0b34 cmplwi r0, 0x1
R077 delete target +0b3c..+0b40 (1) vs built [706:706] (0)
  +0b3c lhz r16, 0x2a(r1)
R079 delete target +0b9c..+0ba4 (2) vs built [732:732] (0)
  +0b9c b .L_813FF04C
  +0ba0 mr r3, r16
R080 replace target +0bac..+0bb0 (1) vs built [735:737] (2)
  +0bac ble .L_813FF060
R080 replace target +0bb4..+0bbc (2) vs built [738:739] (1)
  +0bb4 b .L_813FF064
  +0bb8 mr r0, r16
R080 replace target +0bc0..+0bc8 (2) vs built [740:741] (1)
  +0bc0 clrlwi r16, r0, 16
  +0bc4 cmpwi r16, 0x0
R098 replace target +0dc8..+0dcc (1) vs built [871:872] (1)
  +0dc8 addi r3, lbl_81697204@sda21
R099 replace target +0ddc..+0de0 (1) vs built [876:877] (1)
  +0ddc addi r5, lbl_81697204@sda21
R112 replace target +0f24..+0f28 (1) vs built [959:963] (4)
  +0f24 lis r5, 0x8000
R112 replace target +0f30..+0f34 (1) vs built [965:968] (3)
  +0f30 addi r3, r1, 0x70
R112 replace target +0f38..+0f40 (2) vs built [969:970] (1)
  +0f38 li r4, 0x1
  +0f3c subf r7, r6, r20
R112 delete target +0f44..+0f48 (1) vs built [971:971] (0)
  +0f44 stw r0, 0x7c(r1)
R112 replace target +0f50..+0f5c (3) vs built [973:974] (1)
  +0f50 stw r24, 0x80(r1)
  +0f54 mulli r7, r7, 0x3e8
  +0f58 stw r8, 0x60(r1)
R112 delete target +0f64..+0f6c (2) vs built [976:976] (0)
  +0f64 stw r7, 0x64(r1)
  +0f68 mullw r0, r7, r0
R112 replace target +0f70..+0f74 (1) vs built [977:978] (1)
  +0f70 adde r5, r26, r26
R113 replace target +0f9c..+0fa0 (1) vs built [989:990] (1)
  +0f9c ble .L_813FF480
R113 replace target +0fa4..+0fa8 (1) vs built [991:996] (5)
  +0fa4 bne .L_813FF45C
R113 delete target +0fb4..+0fbc (2) vs built [999:999] (0)
  +0fb4 cmpwi r19, 0x1
  +0fb8 bne .L_813FF470
R113 delete target +0fd8..+0fdc (1) vs built [1006:1006] (0)
  +0fd8 lhz r16, 0x26(r1)
R116 replace target +1048..+104c (1) vs built [1034:1037] (3)
  +1048 ble .L_813FF4FC
R116 delete target +1050..+1058 (2) vs built [1038:1038] (0)
  +1050 b .L_813FF500
  +1054 mr r0, r16
R118 delete target +10b4..+10bc (2) vs built [1061:1061] (0)
  +10b4 li r0, 0x8
  +10b8 lwz r3, lbl_81697200@sda21(r0)
R127 replace target +11ec..+11f0 (1) vs built [1139:1140] (1)
  +11ec addi r3, lbl_81698C70@sda21
R138 replace target +1328..+132c (1) vs built [1218:1219] (1)
  +1328 cmpwi r3, 0x0
R144 replace target +13e4..+13e8 (1) vs built [1265:1266] (1)
  +13e4 bne .L_813FF8A4
R144 replace target +13f4..+13f8 (1) vs built [1269:1270] (1)
  +13f4 cmplwi r0, 0x1
R144 delete target +13fc..+1400 (1) vs built [1271:1271] (0)
  +13fc lhz r17, 0x2a(r1)
R146 delete target +145c..+1464 (2) vs built [1297:1297] (0)
  +145c b .L_813FF90C
  +1460 mr r3, r17
R147 replace target +146c..+1470 (1) vs built [1300:1302] (2)
  +146c ble .L_813FF920
R147 replace target +1474..+147c (2) vs built [1303:1304] (1)
  +1474 b .L_813FF924
  +1478 mr r0, r17
R147 replace target +1480..+1488 (2) vs built [1305:1306] (1)
  +1480 clrlwi r17, r0, 16
  +1484 cmpwi r17, 0x0
R160 replace target +160c..+1610 (1) vs built [1403:1408] (5)
  +160c bne .L_813FFAC4
R160 delete target +161c..+1624 (2) vs built [1411:1411] (0)
  +161c cmpwi r3, 0x1
  +1620 bne .L_813FFAD8
R163 replace target +16b0..+16b4 (1) vs built [1447:1450] (3)
  +16b0 ble .L_813FFB64
R163 delete target +16b8..+16c0 (2) vs built [1451:1451] (0)
  +16b8 b .L_813FFB68
  +16bc mr r0, r16
R167 replace target +1750..+1754 (1) vs built [1487:1488] (1)
  +1750 bge .L_813FFC04
R172 replace target +185c..+1860 (1) vs built [1559:1562] (3)
  +185c beq .L_813FFD48
R174 delete target +1898..+18a0 (2) vs built [1576:1576] (0)
  +1898 li r3, -0x1
  +189c b .L_813FFD4C
```


## AOSS_81400830

Target: `build/43U/asm/src/scene/setting/AOSS.s`. Compiled: `build/43U/src/src/scene/setting/AOSS.o`.

```text
src 0x504 base 0x504 insns 321/321
diffs 123: [6, 47, 49, 50, 53, 59, 60, 69, 70, 71, 74, 76, 79, 80, 84, 85, 86, 87, 89, 93]
```

Equal counts and call sequence; CRC/cipher operand registers and scheduling differ.

Final prologue, all basic blocks, unequal block spans and call-aligned regions:

```text
AOSS_81400830: target 321, built 321, signed deficit 0
entry target: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x40(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x44(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x40', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '_savegpr_26', 'call': '_savegpr_26', 'ref': None, 'dest': None, 'strings': []}, {'off': 20, 'mn': 'mr', 'op': 'r26, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'addi', 'op': 'r29, r3, 0x18', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'addi', 'op': 'r3, r1, 0x8', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
entry built: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x40(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x44(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x40', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '0x25c4', 'call': '_savegpr_26', 'ref': ('_savegpr_26', 0), 'dest': None, 'strings': []}, {'off': 20, 'mn': 'mr', 'op': 'r26, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'addi', 'op': 'r30, r3, 0x18', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'addi', 'op': 'r3, r1, 8', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
TARGET BASIC BLOCKS
T000 +0000 n=20 calls=['_savegpr_26', 'memcpy', 'strlen', 'AOSS_81401E80'] refs=[('lbl_81697204', 0), ('lbl_81697204', 0)] strings=['MELCO', 'MELCO']
T001 +0050 n=4 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T002 +0060 n=7 calls=['SONtoHs', 'AOSS_81400D34'] refs=[] strings=[]
T003 +007c n=1 calls=[] refs=[] strings=[]
T004 +0080 n=5 calls=['SONtoHs'] refs=[] strings=[]
T005 +0094 n=4 calls=['memcpy'] refs=[('lbl_81698C78', 0)] strings=[]
T006 +00a4 n=4 calls=['SONtoHs'] refs=[] strings=[]
T007 +00b4 n=2 calls=[] refs=[] strings=[]
T008 +00bc n=8 calls=['SONtoHs', 'AOSSi_Alloc'] refs=[] strings=[]
T009 +00dc n=4 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T010 +00ec n=6 calls=['AOSSi_Alloc'] refs=[] strings=[]
T011 +0104 n=4 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T012 +0114 n=20 calls=['memcpy', 'memcpy', 'AOSS_81401C9C'] refs=[('AOSS_810BE838', 0), ('AOSS_810BE838', 0), ('AOSS_810BE838', 0), ('lbl_81698C78', 0)] strings=[]
T013 +0164 n=3 calls=[] refs=[] strings=[]
T014 +0170 n=61 calls=[] refs=[] strings=[]
T015 +0264 n=2 calls=[] refs=[] strings=[]
T016 +026c n=1 calls=[] refs=[] strings=[]
T017 +0270 n=32 calls=[] refs=[] strings=[]
T018 +02f0 n=8 calls=['AOSS_81401DC0'] refs=[('AOSS_810BE8A0', 0), ('AOSS_810BE8A0', 0)] strings=[]
T019 +0310 n=3 calls=[] refs=[] strings=[]
T020 +031c n=2 calls=[] refs=[] strings=[]
T021 +0324 n=4 calls=[] refs=[] strings=[]
T022 +0334 n=1 calls=[] refs=[] strings=[]
T023 +0338 n=2 calls=[] refs=[] strings=[]
T024 +0340 n=7 calls=[] refs=[('AOSS_810BE8A0', 0), ('AOSS_810BE8A0', 0)] strings=[]
T025 +035c n=51 calls=[] refs=[] strings=[]
T026 +0428 n=7 calls=[] refs=[('AOSS_810BE8A0', 0), ('AOSS_810BE8A0', 0)] strings=[]
T027 +0444 n=8 calls=[] refs=[] strings=[]
T028 +0464 n=5 calls=[] refs=[] strings=[]
T029 +0478 n=6 calls=['AOSSi_Free'] refs=[('lbl_81698C84', 0)] strings=[]
T030 +0490 n=3 calls=['AOSSi_Free'] refs=[] strings=[]
T031 +049c n=2 calls=[] refs=[] strings=[]
T032 +04a4 n=6 calls=['AOSSi_Free'] refs=[('lbl_81698C84', 0)] strings=[]
T033 +04bc n=2 calls=[] refs=[] strings=[]
T034 +04c4 n=10 calls=['memcpy', 'SOHtoNs', 'AOSSi_Free'] refs=[] strings=[]
T035 +04ec n=6 calls=['_restgpr_26'] refs=[] strings=[]
BUILT BASIC BLOCKS
M000 +0000 n=20 calls=['_savegpr_26', 'memcpy', 'strlen', 'AOSS_81401E80'] refs=[('s_manufacturer', 0), ('s_manufacturer', 0)] strings=['MELCO', 'MELCO']
M001 +0050 n=4 calls=[] refs=[('s_errorCode', 0)] strings=[]
M002 +0060 n=7 calls=['SONtoHs', 'AOSS_81400D34'] refs=[] strings=[]
M003 +007c n=1 calls=[] refs=[] strings=[]
M004 +0080 n=5 calls=['SONtoHs'] refs=[] strings=[]
M005 +0094 n=4 calls=['memcpy'] refs=[('s_accessPointName', 0)] strings=[]
M006 +00a4 n=4 calls=['SONtoHs'] refs=[] strings=[]
M007 +00b4 n=2 calls=[] refs=[] strings=[]
M008 +00bc n=8 calls=['SONtoHs', 'AOSSi_Alloc'] refs=[] strings=[]
M009 +00dc n=4 calls=[] refs=[('s_errorCode', 0)] strings=[]
M010 +00ec n=6 calls=['AOSSi_Alloc'] refs=[] strings=[]
M011 +0104 n=4 calls=[] refs=[('s_errorCode', 0)] strings=[]
M012 +0114 n=20 calls=['memcpy', 'memcpy', 'AOSS_81401C9C'] refs=[('s_packetState', 0), ('s_packetState', 0), ('s_packetState', 0), ('s_accessPointName', 0)] strings=[]
M013 +0164 n=3 calls=[] refs=[] strings=[]
M014 +0170 n=61 calls=[] refs=[] strings=[]
M015 +0264 n=2 calls=[] refs=[] strings=[]
M016 +026c n=1 calls=[] refs=[] strings=[]
M017 +0270 n=32 calls=[] refs=[] strings=[]
M018 +02f0 n=8 calls=['AOSS_81401DC0'] refs=[('s_crcTable', 0), ('s_crcTable', 0)] strings=[]
M019 +0310 n=3 calls=[] refs=[] strings=[]
M020 +031c n=2 calls=[] refs=[] strings=[]
M021 +0324 n=4 calls=[] refs=[] strings=[]
M022 +0334 n=1 calls=[] refs=[] strings=[]
M023 +0338 n=2 calls=[] refs=[] strings=[]
M024 +0340 n=7 calls=[] refs=[('s_crcTable', 0), ('s_crcTable', 0)] strings=[]
M025 +035c n=51 calls=[] refs=[] strings=[]
M026 +0428 n=7 calls=[] refs=[('s_crcTable', 0), ('s_crcTable', 0)] strings=[]
M027 +0444 n=8 calls=[] refs=[] strings=[]
M028 +0464 n=5 calls=[] refs=[] strings=[]
M029 +0478 n=6 calls=['AOSSi_Free'] refs=[('s_errorCode', 0)] strings=[]
M030 +0490 n=3 calls=['AOSSi_Free'] refs=[] strings=[]
M031 +049c n=2 calls=[] refs=[] strings=[]
M032 +04a4 n=6 calls=['AOSSi_Free'] refs=[('s_errorCode', 0)] strings=[]
M033 +04bc n=2 calls=[] refs=[] strings=[]
M034 +04c4 n=10 calls=['memcpy', 'SOHtoNs', 'AOSSi_Free'] refs=[] strings=[]
M035 +04ec n=6 calls=['_restgpr_26'] refs=[] strings=[]
ALIGNMENT; each unequal span lists all target/built blocks
replace: T0:1 +20 / M0:1 +20
replace: T5:6 +4 / M5:6 +4
replace: T12:13 +20 / M12:13 +20
CALL-ALIGNED REGIONS
R002: T[11:13] M[11:13] deficit +0 before strlen
R003: T[13:18] M[13:18] deficit +0 before AOSS_81401E80
R007: T[34:41] M[34:41] deficit +0 before memcpy
R013: T[74:79] M[74:79] deficit +0 before memcpy
```

Target-only opcode spans within each unequal call region:

```text
R002 replace target +002c..+0030 (1) vs built [11:12] (1)
  +002c addi r3, lbl_81697204@sda21
R003 replace target +0040..+0044 (1) vs built [16:17] (1)
  +0040 addi r5, lbl_81697204@sda21
R007 replace target +0098..+009c (1) vs built [38:39] (1)
  +0098 addi r3, lbl_81698C78@sda21
R013 replace target +012c..+0130 (1) vs built [75:76] (1)
  +012c addi r4, lbl_81698C78@sda21
```


## AOSS_814013AC

Target: `build/43U/asm/src/scene/setting/AOSS.s`. Compiled: `build/43U/src/src/scene/setting/AOSS.o`.

```text
src 0x1c8 base 0x1c8 insns 114/114
diffs 22: [6, 7, 14, 15, 16, 17, 20, 25, 29, 30, 34, 42, 55, 60, 65, 70, 75, 81, 87, 95]
```

Equal counts and call sequence; response/option cursor, flags and remaining-length register allocation differ.

Final prologue, all basic blocks, unequal block spans and call-aligned regions:

```text
AOSS_814013AC: target 114, built 114, signed deficit 0
entry target: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x30(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x34(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x30', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '_savegpr_24', 'call': '_savegpr_24', 'ref': None, 'dest': None, 'strings': []}, {'off': 20, 'mn': 'cmpwi', 'op': 'r5, 0x0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'mr', 'op': 'r27, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'mr', 'op': 'r24, r5', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
entry built: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x30(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x34(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x30', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '0x3140', 'call': '_savegpr_24', 'ref': ('_savegpr_24', 0), 'dest': None, 'strings': []}, {'off': 20, 'mn': 'cmpwi', 'op': 'r5, 0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'mr', 'op': 'r24, r5', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'mr', 'op': 'r27, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
TARGET BASIC BLOCKS
T000 +0000 n=12 calls=['_savegpr_24'] refs=[] strings=[]
T001 +0030 n=2 calls=[] refs=[] strings=[]
T002 +0038 n=2 calls=[] refs=[('lbl_81697210', 0)] strings=[]
T003 +0040 n=4 calls=[] refs=[] strings=[]
T004 +0050 n=7 calls=['SONtoHs'] refs=[] strings=[]
T005 +006c n=2 calls=[] refs=[] strings=[]
T006 +0074 n=13 calls=['SONtoHs'] refs=[] strings=[]
T007 +00a8 n=3 calls=[] refs=[] strings=[]
T008 +00b4 n=1 calls=[] refs=[] strings=[]
T009 +00b8 n=2 calls=[] refs=[] strings=[]
T010 +00c0 n=1 calls=[] refs=[] strings=[]
T011 +00c4 n=2 calls=[] refs=[] strings=[]
T012 +00cc n=1 calls=[] refs=[] strings=[]
T013 +00d0 n=2 calls=[] refs=[] strings=[]
T014 +00d8 n=1 calls=[] refs=[] strings=[]
T015 +00dc n=5 calls=['AOSS_81401104'] refs=[] strings=[]
T016 +00f0 n=5 calls=['AOSS_81401104'] refs=[] strings=[]
T017 +0104 n=5 calls=['AOSS_81401284'] refs=[] strings=[]
T018 +0118 n=5 calls=['AOSS_81401284'] refs=[] strings=[]
T019 +012c n=4 calls=['SONtoHs'] refs=[] strings=[]
T020 +013c n=2 calls=[] refs=[] strings=[]
T021 +0144 n=3 calls=[] refs=[] strings=[]
T022 +0150 n=2 calls=[] refs=[] strings=[]
T023 +0158 n=5 calls=['memcpy'] refs=[] strings=[]
T024 +016c n=1 calls=[] refs=[] strings=[]
T025 +0170 n=2 calls=[] refs=[] strings=[]
T026 +0178 n=1 calls=[] refs=[] strings=[]
T027 +017c n=7 calls=['SONtoHs'] refs=[] strings=[]
T028 +0198 n=6 calls=[] refs=[('AOSS_810BDEF8', 0), ('AOSS_810BDEF8', 0)] strings=[]
T029 +01b0 n=6 calls=['_restgpr_24'] refs=[] strings=[]
BUILT BASIC BLOCKS
M000 +0000 n=12 calls=['_savegpr_24'] refs=[] strings=[]
M001 +0030 n=2 calls=[] refs=[] strings=[]
M002 +0038 n=2 calls=[] refs=[('s_responseTypeByState', 0)] strings=[]
M003 +0040 n=4 calls=[] refs=[] strings=[]
M004 +0050 n=7 calls=['SONtoHs'] refs=[] strings=[]
M005 +006c n=2 calls=[] refs=[] strings=[]
M006 +0074 n=13 calls=['SONtoHs'] refs=[] strings=[]
M007 +00a8 n=3 calls=[] refs=[] strings=[]
M008 +00b4 n=1 calls=[] refs=[] strings=[]
M009 +00b8 n=2 calls=[] refs=[] strings=[]
M010 +00c0 n=1 calls=[] refs=[] strings=[]
M011 +00c4 n=2 calls=[] refs=[] strings=[]
M012 +00cc n=1 calls=[] refs=[] strings=[]
M013 +00d0 n=2 calls=[] refs=[] strings=[]
M014 +00d8 n=1 calls=[] refs=[] strings=[]
M015 +00dc n=5 calls=['AOSS_81401104'] refs=[] strings=[]
M016 +00f0 n=5 calls=['AOSS_81401104'] refs=[] strings=[]
M017 +0104 n=5 calls=['AOSS_81401284'] refs=[] strings=[]
M018 +0118 n=5 calls=['AOSS_81401284'] refs=[] strings=[]
M019 +012c n=4 calls=['SONtoHs'] refs=[] strings=[]
M020 +013c n=2 calls=[] refs=[] strings=[]
M021 +0144 n=3 calls=[] refs=[] strings=[]
M022 +0150 n=2 calls=[] refs=[] strings=[]
M023 +0158 n=5 calls=['memcpy'] refs=[] strings=[]
M024 +016c n=1 calls=[] refs=[] strings=[]
M025 +0170 n=2 calls=[] refs=[] strings=[]
M026 +0178 n=1 calls=[] refs=[] strings=[]
M027 +017c n=7 calls=['SONtoHs'] refs=[] strings=[]
M028 +0198 n=6 calls=[] refs=[('s_runtime', 0), ('s_runtime', 0)] strings=[]
M029 +01b0 n=6 calls=['_restgpr_24'] refs=[] strings=[]
ALIGNMENT; each unequal span lists all target/built blocks
replace: T2:3 +2 / M2:3 +2
CALL-ALIGNED REGIONS
R001: T[5:22] M[5:22] deficit +0 before SONtoHs
```

Target-only opcode spans within each unequal call region:

```text
R001 replace target +003c..+0040 (1) vs built [15:16] (1)
  +003c addi r29, lbl_81697210@sda21
```


## AOSS_81401778

Target: `build/43U/asm/src/scene/setting/AOSS.s`. Compiled: `build/43U/src/src/scene/setting/AOSS.o`.

```text
src 0x43c base 0x444 insns 271/273
--- replace mine 5:10 base 5:8
```

Frame agrees; target saves r25 upward, build saves r24 upward. CRC scheduling, common BSS base and destination/identity stack lifetimes differ.

Entry call-aligned gaps:

```text
R000 target [0:14] built [0:16] deficit -2 before memset
R003 target [25:31] built [27:32] deficit +1 before SOHtoNl
R004 target [31:42] built [32:41] deficit +2 before AOSS_81401DC0
R008 target [105:110] built [104:108] deficit +1 before memcpy
R023 target [247:252] built [245:249] deficit +1 before SOHtoNl
```

Final prologue, all basic blocks, unequal block spans and call-aligned regions:

```text
AOSS_81401778: target 273, built 271, signed deficit 2
entry target: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x60(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x64(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x60', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '_savegpr_25', 'call': '_savegpr_25', 'ref': None, 'dest': None, 'strings': []}, {'off': 20, 'mn': 'lwz', 'op': 'r28, lbl_81698C8C@sda21(r0)', 'call': '', 'ref': ('lbl_81698C8C', 0), 'dest': None, 'strings': []}, {'off': 24, 'mn': 'mr', 'op': 'r26, r4', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'mr', 'op': 'r27, r5', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
entry built: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x60(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x64(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x60', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '0x350c', 'call': '_savegpr_24', 'ref': ('_savegpr_24', 0), 'dest': None, 'strings': []}, {'off': 20, 'mn': 'lis', 'op': 'r31, 0', 'call': '', 'ref': ('...bss.0', 0), 'dest': None, 'strings': []}, {'off': 24, 'mn': 'lwz', 'op': 'r29, 0(0)', 'call': '', 'ref': ('s_responseBuffer', 0), 'dest': None, 'strings': []}, {'off': 28, 'mn': 'mr', 'op': 'r25, r4', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
TARGET BASIC BLOCKS
T000 +0000 n=36 calls=['_savegpr_25', 'memset', 'memset', 'SOHtoNs', 'SOHtoNl'] refs=[('lbl_81698C8C', 0), ('AOSS_810BDEF8', 0), ('AOSS_810BDEF8', 0), ('lbl_81698C80', 0)] strings=[]
T001 +0090 n=63 calls=['AOSS_81401DC0', 'AOSSi_Alloc'] refs=[('AOSS_810BE8A0', 0), ('AOSS_810BE8A0', 0), ('AOSS_810BE8A0', 0)] strings=[]
T002 +018c n=25 calls=['rand', 'memcpy', 'memcpy', 'memcpy', 'AOSS_81401C9C'] refs=[('AOSS_810BE838', 0), ('AOSS_810BE838', 0), ('AOSS_810BE838', 0), ('lbl_81698C78', 0)] strings=[]
T003 +01f0 n=64 calls=[] refs=[] strings=[]
T004 +02f0 n=2 calls=['AOSSi_Free'] refs=[] strings=[]
T005 +02f8 n=5 calls=['SOHtoNs'] refs=[] strings=[]
T006 +030c n=4 calls=['memcpy'] refs=[] strings=[]
T007 +031c n=11 calls=['memcpy', 'AOSS_81401E80'] refs=[('lbl_81697204', 0)] strings=['MELCO']
T008 +0348 n=4 calls=[] refs=[('lbl_81698C84', 0)] strings=[]
T009 +0358 n=42 calls=['SOHtoNs', 'SOHtoNs', 'SOHtoNs', 'SOHtoNs', 'memcpy', 'memset', 'SOHtoNs', 'SOHtoNl'] refs=[('AOSS_810BDEF8', 0), ('AOSS_810BDEF8', 0)] strings=[]
T010 +0400 n=2 calls=[] refs=[] strings=[]
T011 +0408 n=9 calls=['SOSendTo'] refs=[] strings=[]
T012 +042c n=6 calls=['_restgpr_25'] refs=[] strings=[]
BUILT BASIC BLOCKS
M000 +0000 n=37 calls=['_savegpr_24', 'memset', 'memset', 'SOHtoNs', 'SOHtoNl'] refs=[('...bss.0', 0), ('s_responseBuffer', 0), ('...bss.0', 0), ('s_connectionState', 0)] strings=[]
M001 +0094 n=62 calls=['AOSS_81401DC0', 'AOSSi_Alloc'] refs=[] strings=[]
M002 +018c n=24 calls=['rand', 'memcpy', 'memcpy', 'memcpy', 'AOSS_81401C9C'] refs=[('s_accessPointName', 0)] strings=[]
M003 +01ec n=64 calls=[] refs=[] strings=[]
M004 +02ec n=2 calls=['AOSSi_Free'] refs=[] strings=[]
M005 +02f4 n=5 calls=['SOHtoNs'] refs=[] strings=[]
M006 +0308 n=4 calls=['memcpy'] refs=[] strings=[]
M007 +0318 n=11 calls=['memcpy', 'AOSS_81401E80'] refs=[('s_manufacturer', 0)] strings=['MELCO']
M008 +0344 n=4 calls=[] refs=[('s_errorCode', 0)] strings=[]
M009 +0354 n=41 calls=['SOHtoNs', 'SOHtoNs', 'SOHtoNs', 'SOHtoNs', 'memcpy', 'memset', 'SOHtoNs', 'SOHtoNl'] refs=[] strings=[]
M010 +03f8 n=2 calls=[] refs=[] strings=[]
M011 +0400 n=9 calls=['SOSendTo'] refs=[] strings=[]
M012 +0424 n=6 calls=['_restgpr_24'] refs=[] strings=[]
ALIGNMENT; each unequal span lists all target/built blocks
replace: T0:3 +124 / M0:3 +123
replace: T7:8 +11 / M7:8 +11
replace: T9:10 +42 / M9:10 +41
replace: T12:13 +6 / M12:13 +6
CALL-ALIGNED REGIONS
R000: T[0:14] M[0:16] deficit -2 before memset
R003: T[25:31] M[27:32] deficit +1 before SOHtoNl
R004: T[31:42] M[32:43] deficit +0 before AOSS_81401DC0
R005: T[42:96] M[43:96] deficit +1 before AOSSi_Alloc
R008: T[105:110] M[105:109] deficit +1 before memcpy
R009: T[110:115] M[109:114] deficit +0 before memcpy
R015: T[203:208] M[202:207] deficit +0 before AOSS_81401E80
R023: T[247:252] M[246:250] deficit +1 before SOHtoNl
```

Target-only opcode spans within each unequal call region:

```text
R003 replace target +0064..+0068 (1) vs built [27:28] (1)
  +0064 lis r4, AOSS_810BDEF8@ha
R003 delete target +006c..+0070 (1) vs built [29:29] (0)
  +006c addi r4, r4, AOSS_810BDEF8@l
R004 replace target +0090..+0094 (1) vs built [37:38] (1)
  +0090 lis r25, AOSS_810BE8A0@ha
R004 replace target +0098..+009c (1) vs built [39:40] (1)
  +0098 addi r4, r25, AOSS_810BE8A0@l
R005 delete target +00ac..+00b0 (1) vs built [44:44] (0)
  +00ac addi r5, r25, AOSS_810BE8A0@l
R005 delete target +00c8..+00d4 (3) vs built [53:53] (0)
  +00c8 lwzx r4, r5, r4
  +00cc xor r30, r7, r4
  +00d0 xor r4, r30, r6
R005 delete target +00d8..+0114 (15) vs built [54:54] (0)
  +00d8 rlwinm r4, r4, 24, 2
  +00dc srwi r7, r30, 8
  +00e0 lwzx r4, r5, r4
  +00e4 xor r30, r7, r4
  +00e8 xor r4, r30, r6
  +00ec lbz r6, 0x1b(r1)
  +00f0 rlwinm r4, r4, 24, 2
  +00f4 srwi r7, r30, 8
  +00f8 lwzx r4, r5, r4
  +00fc xor r30, r7, r4
  +0100 xor r4, r30, r6
  +0104 lbz r6, 0x1c(r1)
  +0108 rlwinm r4, r4, 24, 2
  +010c srwi r7, r30, 8
  +0110 lwzx r4, r5, r4
R008 delete target +01a4..+01a8 (1) vs built [105:105] (0)
  +01a4 lis r25, AOSS_810BE838@ha
R009 replace target +01bc..+01c0 (1) vs built [110:111] (1)
  +01bc addi r4, lbl_81698C78@sda21
R015 replace target +0334..+0338 (1) vs built [204:205] (1)
  +0334 addi r5, lbl_81697204@sda21
R023 replace target +03dc..+03e0 (1) vs built [246:247] (1)
  +03dc lis r26, AOSS_810BDEF8@ha
R023 delete target +03e4..+03e8 (1) vs built [248:248] (0)
  +03e4 addi r26, r26, AOSS_810BDEF8@l
```


## AOSS_81401E80

Target: `build/43U/asm/src/scene/setting/AOSS.s`. Compiled: `build/43U/src/src/scene/setting/AOSS.o`.

```text
src 0x24c base 0x24c insns 147/147
diffs 36: [54, 59, 72, 74, 75, 76, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91]
```

Equal counts and opcode sequence; XOR inputs and key bytes use different work registers.

Final prologue, all basic blocks, unequal block spans and call-aligned regions:

```text
AOSS_81401E80: target 147, built 147, signed deficit 0
entry target: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x40(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x44(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x40', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '_savegpr_21', 'call': '_savegpr_21', 'ref': None, 'dest': None, 'strings': []}, {'off': 20, 'mn': 'srwi', 'op': 'r0, r4, 31', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'mr', 'op': 'r21, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'add', 'op': 'r0, r0, r4', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
entry built: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x40(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x44(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x40', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '0x3c0c', 'call': '_savegpr_21', 'ref': ('_savegpr_21', 0), 'dest': None, 'strings': []}, {'off': 20, 'mn': 'srwi', 'op': 'r0, r4, 0x1f', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'mr', 'op': 'r21, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'add', 'op': 'r0, r0, r4', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
TARGET BASIC BLOCKS
T000 +0000 n=17 calls=['_savegpr_21', 'AOSSi_Alloc'] refs=[] strings=[]
T001 +0044 n=2 calls=[] refs=[] strings=[]
T002 +004c n=5 calls=['AOSSi_Alloc'] refs=[] strings=[]
T003 +0060 n=4 calls=['AOSSi_Free'] refs=[] strings=[]
T004 +0070 n=4 calls=[] refs=[] strings=[]
T005 +0080 n=8 calls=[] refs=[] strings=[]
T006 +00a0 n=8 calls=[] refs=[] strings=[]
T007 +00c0 n=1 calls=[] refs=[] strings=[]
T008 +00c4 n=3 calls=[] refs=[] strings=[]
T009 +00d0 n=3 calls=[] refs=[] strings=[]
T010 +00dc n=3 calls=[] refs=[] strings=[]
T011 +00e8 n=2 calls=[] refs=[] strings=[]
T012 +00f0 n=3 calls=[] refs=[] strings=[]
T013 +00fc n=1 calls=[] refs=[] strings=[]
T014 +0100 n=2 calls=[] refs=[] strings=[]
T015 +0108 n=5 calls=[] refs=[] strings=[]
T016 +011c n=36 calls=[] refs=[] strings=[]
T017 +01ac n=6 calls=[] refs=[] strings=[]
T018 +01c4 n=8 calls=[] refs=[] strings=[]
T019 +01e4 n=15 calls=['memcpy', 'memcpy', 'memcpy'] refs=[] strings=[]
T020 +0220 n=5 calls=['AOSSi_Free', 'AOSSi_Free'] refs=[] strings=[]
T021 +0234 n=6 calls=['_restgpr_21'] refs=[] strings=[]
BUILT BASIC BLOCKS
M000 +0000 n=17 calls=['_savegpr_21', 'AOSSi_Alloc'] refs=[] strings=[]
M001 +0044 n=2 calls=[] refs=[] strings=[]
M002 +004c n=5 calls=['AOSSi_Alloc'] refs=[] strings=[]
M003 +0060 n=4 calls=['AOSSi_Free'] refs=[] strings=[]
M004 +0070 n=4 calls=[] refs=[] strings=[]
M005 +0080 n=8 calls=[] refs=[] strings=[]
M006 +00a0 n=8 calls=[] refs=[] strings=[]
M007 +00c0 n=1 calls=[] refs=[] strings=[]
M008 +00c4 n=3 calls=[] refs=[] strings=[]
M009 +00d0 n=3 calls=[] refs=[] strings=[]
M010 +00dc n=3 calls=[] refs=[] strings=[]
M011 +00e8 n=2 calls=[] refs=[] strings=[]
M012 +00f0 n=3 calls=[] refs=[] strings=[]
M013 +00fc n=1 calls=[] refs=[] strings=[]
M014 +0100 n=2 calls=[] refs=[] strings=[]
M015 +0108 n=5 calls=[] refs=[] strings=[]
M016 +011c n=36 calls=[] refs=[] strings=[]
M017 +01ac n=6 calls=[] refs=[] strings=[]
M018 +01c4 n=8 calls=[] refs=[] strings=[]
M019 +01e4 n=15 calls=['memcpy', 'memcpy', 'memcpy'] refs=[] strings=[]
M020 +0220 n=5 calls=['AOSSi_Free', 'AOSSi_Free'] refs=[] strings=[]
M021 +0234 n=6 calls=['_restgpr_21'] refs=[] strings=[]
ALIGNMENT; each unequal span lists all target/built blocks
CALL-ALIGNED REGIONS
```

Target-only opcode spans within each unequal call region:

```text
```


## Zi8ChangeWordCase

Target: `build/43U/asm/libs/RVLMiddleware/eZiText/src/clib/zi8alpha.s`. Compiled: `build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8alpha.o`.

```text
src 0xb0 base 0xb0 insns 44/44
diffs 8: [9, 10, 11, 19, 22, 25, 27, 31]
```

Equal counts and opcode sequence; workspace and case-mode roles exchange r29/r30.

Final prologue, all basic blocks, unequal block spans and call-aligned regions:

```text
Zi8ChangeWordCase: target 44, built 44, signed deficit 0
entry target: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x20(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x24(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'stw', 'op': 'r31, 0x1c(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'stw', 'op': 'r30, 0x18(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 20, 'mn': 'stw', 'op': 'r29, 0x14(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'stw', 'op': 'r28, 0x10(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'mr', 'op': 'r31, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
entry built: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x20(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x24(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'stw', 'op': 'r31, 0x1c(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'stw', 'op': 'r30, 0x18(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 20, 'mn': 'stw', 'op': 'r29, 0x14(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'stw', 'op': 'r28, 0x10(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'mr', 'op': 'r31, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
TARGET BASIC BLOCKS
T000 +0000 n=14 calls=[] refs=[] strings=[]
T001 +0038 n=8 calls=['Zi8ChangeCharCase'] refs=[] strings=[]
T002 +0058 n=3 calls=[] refs=[] strings=[]
T003 +0064 n=2 calls=[] refs=[] strings=[]
T004 +006c n=6 calls=['Zi8ChangeCharCase'] refs=[] strings=[]
T005 +0084 n=3 calls=[] refs=[] strings=[]
T006 +0090 n=8 calls=[] refs=[] strings=[]
BUILT BASIC BLOCKS
M000 +0000 n=14 calls=[] refs=[] strings=[]
M001 +0038 n=8 calls=['Zi8ChangeCharCase'] refs=[] strings=[]
M002 +0058 n=3 calls=[] refs=[] strings=[]
M003 +0064 n=2 calls=[] refs=[] strings=[]
M004 +006c n=6 calls=['Zi8ChangeCharCase'] refs=[] strings=[]
M005 +0084 n=3 calls=[] refs=[] strings=[]
M006 +0090 n=8 calls=[] refs=[] strings=[]
ALIGNMENT; each unequal span lists all target/built blocks
CALL-ALIGNED REGIONS
```

Target-only opcode spans within each unequal call region:

```text
```


## Zi8AlphaGetCandidates

Target: `build/43U/asm/libs/RVLMiddleware/eZiText/src/clib/zi8alpha.s`. Compiled: `build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8alpha.o`.

```text
src 0x3dac base 0x3da8 insns 3947/3946
--- insert mine 12:12 base 12:14
```

Frame and saved registers agree. Retry blocks now align; emission, next-element arithmetic, load/store choices and operand scheduling remain.

Entry call-aligned gaps:

```text
R001 target [5:222] built [5:221] deficit +1 before Zi8ChangeCharCase
R004 target [265:301] built [264:299] deficit +1 before Zi8LangSupported
R008 target [437:487] built [435:486] deficit -1 before Zi8GetTableCount
R013 target [576:605] built [575:606] deficit -2 before Zi8IsAlphaPunct
R025 target [1114:1169] built [1115:1169] deficit +1 before Zi8GetTableCount
R026 target [1169:1235] built [1169:1234] deficit +1 before Zi8getKeyLayout
R035 target [1702:1761] built [1701:1761] deficit -1 before Zi8ITspecialExclusion
R037 target [1778:1790] built [1778:1789] deficit +1 before Zi8IsVowel
R041 target [1866:1900] built [1865:1900] deficit -1 before Zi8IsZicorpSignature
R042 target [1900:1920] built [1900:1921] deficit -1 before Zi8MatchPUDdata
R044 target [1943:1980] built [1944:1980] deficit +1 before Zi8MatchOEMdata
R046 target [2165:2248] built [2165:2247] deficit +1 before Zi8getKeyLayout
R047 target [2248:2278] built [2247:2279] deficit -2 before Zi8ITspecialExclusion
R050 target [2297:2347] built [2298:2347] deficit +1 before Zi8DeTokenization
R053 target [2403:2435] built [2403:2436] deficit -1 before Zi8IsDupWordW
R055 target [2523:2653] built [2524:2652] deficit +2 before Zi8WCharCount
R057 target [2969:3123] built [2968:3128] deficit -6 before Zi8GetTableCount
R059 target [3144:3332] built [3149:3338] deficit -1 before Zi8IsAlphaPunct
R060 target [3332:3502] built [3338:3403] deficit +105 before ZiIsLetterHyphen
R061 target [3502:3516] built [3403:3416] deficit +1 before ZiIsLetterHyphen
R062 target [3516:3532] built [3416:3433] deficit -1 before ZiIsLetterHyphen
R064 target [3540:3595] built [3441:3495] deficit +1 before Zi8IsAlphaPunct
R065 target [3595:3651] built [3495:3550] deficit +1 before Zi8GetTableCount
R066 target [3651:3669] built [3550:3567] deficit +1 before Zi8IsAlphaPunct
R067 target [3669:3720] built [3567:3722] deficit -104 before Zi8IsAlphaPunct
R070 target [3871:3891] built [3873:3894] deficit -1 before Zi8SetHighlightedWordW
```

Final prologue, all basic blocks, unequal block spans and call-aligned regions:

```text
Zi8AlphaGetCandidates: target 3946, built 3947, signed deficit -1
entry target: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x2b0(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x2b4(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x2b0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '_savegpr_27', 'call': '_savegpr_27', 'ref': None, 'dest': None, 'strings': []}, {'off': 20, 'mn': 'mr', 'op': 'r31, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'mr', 'op': 'r27, r4', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'mr', 'op': 'r30, r5', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
entry built: [{'off': 0, 'mn': 'stwu', 'op': 'r1, -0x2b0(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 4, 'mn': 'mflr', 'op': 'r0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 8, 'mn': 'stw', 'op': 'r0, 0x2b4(r1)', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 12, 'mn': 'addi', 'op': 'r11, r1, 0x2b0', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 16, 'mn': 'bl', 'op': '0xa50', 'call': '_savegpr_27', 'ref': ('_savegpr_27', 0), 'dest': None, 'strings': []}, {'off': 20, 'mn': 'mr', 'op': 'r31, r3', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 24, 'mn': 'mr', 'op': 'r27, r4', 'call': '', 'ref': None, 'dest': None, 'strings': []}, {'off': 28, 'mn': 'mr', 'op': 'r30, r5', 'call': '', 'ref': None, 'dest': None, 'strings': []}]
TARGET BASIC BLOCKS
T000 +0000 n=95 calls=['_savegpr_27'] refs=[] strings=[]
T001 +017c n=3 calls=[] refs=[] strings=[]
T002 +0188 n=3 calls=[] refs=[] strings=[]
T003 +0194 n=3 calls=[] refs=[] strings=[]
T004 +01a0 n=3 calls=[] refs=[] strings=[]
T005 +01ac n=3 calls=[] refs=[] strings=[]
T006 +01b8 n=3 calls=[] refs=[] strings=[]
T007 +01c4 n=5 calls=[] refs=[] strings=[]
T008 +01d8 n=16 calls=[] refs=[] strings=[]
T009 +0218 n=4 calls=[] refs=[] strings=[]
T010 +0228 n=1 calls=[] refs=[] strings=[]
T011 +022c n=7 calls=[] refs=[] strings=[]
T012 +0248 n=3 calls=[] refs=[] strings=[]
T013 +0254 n=3 calls=[] refs=[] strings=[]
T014 +0260 n=7 calls=[] refs=[] strings=[]
T015 +027c n=5 calls=[] refs=[] strings=[]
T016 +0290 n=3 calls=[] refs=[] strings=[]
T017 +029c n=4 calls=[] refs=[] strings=[]
T018 +02ac n=2 calls=[] refs=[] strings=[]
T019 +02b4 n=3 calls=[] refs=[] strings=[]
T020 +02c0 n=2 calls=[] refs=[] strings=[]
T021 +02c8 n=3 calls=[] refs=[] strings=[]
T022 +02d4 n=3 calls=[] refs=[] strings=[]
T023 +02e0 n=3 calls=[] refs=[] strings=[]
T024 +02ec n=3 calls=[] refs=[] strings=[]
T025 +02f8 n=3 calls=[] refs=[] strings=[]
T026 +0304 n=14 calls=[] refs=[] strings=[]
T027 +033c n=6 calls=[] refs=[] strings=[]
T028 +0354 n=12 calls=['Zi8ChangeCharCase'] refs=[] strings=[]
T029 +0384 n=1 calls=[] refs=[] strings=[]
T030 +0388 n=3 calls=[] refs=[] strings=[]
T031 +0394 n=4 calls=[] refs=[] strings=[]
T032 +03a4 n=2 calls=[] refs=[] strings=[]
T033 +03ac n=2 calls=[] refs=[] strings=[]
T034 +03b4 n=3 calls=[] refs=[] strings=[]
T035 +03c0 n=3 calls=[] refs=[] strings=[]
T036 +03cc n=3 calls=[] refs=[] strings=[]
T037 +03d8 n=3 calls=['ZiprocessHighlightedW'] refs=[] strings=[]
T038 +03e4 n=3 calls=[] refs=[] strings=[]
T039 +03f0 n=3 calls=[] refs=[] strings=[]
T040 +03fc n=3 calls=[] refs=[] strings=[]
T041 +0408 n=2 calls=[] refs=[] strings=[]
T042 +0410 n=10 calls=['Zi8GetTableCount'] refs=[] strings=[]
T043 +0438 n=3 calls=[] refs=[] strings=[]
T044 +0444 n=2 calls=[] refs=[] strings=[]
T045 +044c n=3 calls=[] refs=[] strings=[]
T046 +0458 n=3 calls=[] refs=[] strings=[]
T047 +0464 n=5 calls=[] refs=[] strings=[]
T048 +0478 n=3 calls=[] refs=[] strings=[]
T049 +0484 n=3 calls=[] refs=[] strings=[]
T050 +0490 n=3 calls=[] refs=[] strings=[]
T051 +049c n=3 calls=[] refs=[] strings=[]
T052 +04a8 n=6 calls=['Zi8LangSupported'] refs=[] strings=[]
T053 +04c0 n=7 calls=[] refs=[] strings=[]
T054 +04dc n=3 calls=[] refs=[] strings=[]
T055 +04e8 n=3 calls=[] refs=[] strings=[]
T056 +04f4 n=4 calls=[] refs=[] strings=[]
T057 +0504 n=4 calls=[] refs=[] strings=[]
T058 +0514 n=25 calls=['Zi8MatchROMdata'] refs=[] strings=[]
T059 +0578 n=3 calls=[] refs=[] strings=[]
T060 +0584 n=23 calls=['Zi8MatchROMdata'] refs=[] strings=[]
T061 +05e0 n=6 calls=[] refs=[] strings=[]
T062 +05f8 n=2 calls=[] refs=[] strings=[]
T063 +0600 n=3 calls=[] refs=[] strings=[]
T064 +060c n=3 calls=[] refs=[] strings=[]
T065 +0618 n=3 calls=[] refs=[] strings=[]
T066 +0624 n=3 calls=[] refs=[] strings=[]
T067 +0630 n=7 calls=[] refs=[] strings=[]
T068 +064c n=7 calls=[] refs=[] strings=[]
T069 +0668 n=7 calls=[] refs=[] strings=[]
T070 +0684 n=3 calls=[] refs=[] strings=[]
T071 +0690 n=2 calls=[] refs=[] strings=[]
T072 +0698 n=3 calls=[] refs=[] strings=[]
T073 +06a4 n=3 calls=[] refs=[] strings=[]
T074 +06b0 n=3 calls=[] refs=[] strings=[]
T075 +06bc n=9 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
T076 +06e0 n=4 calls=[] refs=[] strings=[]
T077 +06f0 n=4 calls=[] refs=[] strings=[]
T078 +0700 n=4 calls=[] refs=[] strings=[]
T079 +0710 n=3 calls=[] refs=[] strings=[]
T080 +071c n=7 calls=[] refs=[] strings=[]
T081 +0738 n=2 calls=[] refs=[] strings=[]
T082 +0740 n=7 calls=[] refs=[] strings=[]
T083 +075c n=3 calls=[] refs=[] strings=[]
T084 +0768 n=8 calls=[] refs=[] strings=[]
T085 +0788 n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
T086 +07ac n=3 calls=[] refs=[] strings=[]
T087 +07b8 n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
T088 +07dc n=3 calls=[] refs=[] strings=[]
T089 +07e8 n=5 calls=[] refs=[] strings=[]
T090 +07fc n=4 calls=[] refs=[] strings=[]
T091 +080c n=4 calls=[] refs=[] strings=[]
T092 +081c n=4 calls=[] refs=[] strings=[]
T093 +082c n=7 calls=[] refs=[] strings=[]
T094 +0848 n=4 calls=[] refs=[] strings=[]
T095 +0858 n=3 calls=[] refs=[] strings=[]
T096 +0864 n=2 calls=[] refs=[] strings=[]
T097 +086c n=3 calls=[] refs=[] strings=[]
T098 +0878 n=2 calls=[] refs=[] strings=[]
T099 +0880 n=3 calls=[] refs=[] strings=[]
T100 +088c n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
T101 +08b0 n=2 calls=[] refs=[] strings=[]
T102 +08b8 n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
T103 +08dc n=3 calls=[] refs=[] strings=[]
T104 +08e8 n=4 calls=[] refs=[] strings=[]
T105 +08f8 n=5 calls=['Zi8InitDupWordBuf'] refs=[] strings=[]
T106 +090c n=3 calls=[] refs=[] strings=[]
T107 +0918 n=3 calls=[] refs=[] strings=[]
T108 +0924 n=4 calls=[] refs=[] strings=[]
T109 +0934 n=3 calls=[] refs=[] strings=[]
T110 +0940 n=7 calls=[] refs=[] strings=[]
T111 +095c n=9 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
T112 +0980 n=3 calls=[] refs=[] strings=[]
T113 +098c n=11 calls=[] refs=[] strings=[]
T114 +09b8 n=10 calls=[] refs=[] strings=[]
T115 +09e0 n=5 calls=[] refs=[] strings=[]
T116 +09f4 n=13 calls=[] refs=[] strings=[]
T117 +0a28 n=2 calls=[] refs=[] strings=[]
T118 +0a30 n=4 calls=[] refs=[] strings=[]
T119 +0a40 n=3 calls=[] refs=[] strings=[]
T120 +0a4c n=3 calls=[] refs=[] strings=[]
T121 +0a58 n=2 calls=[] refs=[] strings=[]
T122 +0a60 n=4 calls=[] refs=[] strings=[]
T123 +0a70 n=1 calls=[] refs=[] strings=[]
T124 +0a74 n=2 calls=[] refs=[] strings=[]
T125 +0a7c n=1 calls=[] refs=[] strings=[]
T126 +0a80 n=1 calls=[] refs=[] strings=[]
T127 +0a84 n=3 calls=[] refs=[] strings=[]
T128 +0a90 n=3 calls=[] refs=[] strings=[]
T129 +0a9c n=7 calls=[] refs=[] strings=[]
T130 +0ab8 n=5 calls=[] refs=[] strings=[]
T131 +0acc n=3 calls=[] refs=[] strings=[]
T132 +0ad8 n=2 calls=[] refs=[] strings=[]
T133 +0ae0 n=3 calls=[] refs=[] strings=[]
T134 +0aec n=3 calls=[] refs=[] strings=[]
T135 +0af8 n=8 calls=['Zi8IsDupWordW'] refs=[] strings=[]
T136 +0b18 n=3 calls=[] refs=[] strings=[]
T137 +0b24 n=4 calls=[] refs=[] strings=[]
T138 +0b34 n=5 calls=[] refs=[] strings=[]
T139 +0b48 n=3 calls=[] refs=[] strings=[]
T140 +0b54 n=2 calls=[] refs=[] strings=[]
T141 +0b5c n=7 calls=[] refs=[] strings=[]
T142 +0b78 n=5 calls=[] refs=[] strings=[]
T143 +0b8c n=1 calls=[] refs=[] strings=[]
T144 +0b90 n=9 calls=[] refs=[] strings=[]
T145 +0bb4 n=3 calls=[] refs=[] strings=[]
T146 +0bc0 n=5 calls=['Zi8ChangeWordCase'] refs=[] strings=[]
T147 +0bd4 n=4 calls=['Zi8ChangeWordCase'] refs=[] strings=[]
T148 +0be4 n=14 calls=[] refs=[] strings=[]
T149 +0c1c n=4 calls=[] refs=[] strings=[]
T150 +0c2c n=3 calls=[] refs=[] strings=[]
T151 +0c38 n=3 calls=[] refs=[] strings=[]
T152 +0c44 n=3 calls=[] refs=[] strings=[]
T153 +0c50 n=22 calls=[] refs=[] strings=[]
T154 +0ca8 n=3 calls=[] refs=[] strings=[]
T155 +0cb4 n=5 calls=[] refs=[] strings=[]
T156 +0cc8 n=10 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
T157 +0cf0 n=5 calls=[] refs=[] strings=[]
T158 +0d04 n=5 calls=[] refs=[] strings=[]
T159 +0d18 n=2 calls=[] refs=[] strings=[]
T160 +0d20 n=3 calls=[] refs=[] strings=[]
T161 +0d2c n=5 calls=[] refs=[] strings=[]
T162 +0d40 n=10 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
T163 +0d68 n=5 calls=[] refs=[] strings=[]
T164 +0d7c n=4 calls=[] refs=[] strings=[]
T165 +0d8c n=10 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
T166 +0db4 n=3 calls=[] refs=[] strings=[]
T167 +0dc0 n=4 calls=[] refs=[] strings=[]
T168 +0dd0 n=3 calls=[] refs=[] strings=[]
T169 +0ddc n=4 calls=[] refs=[] strings=[]
T170 +0dec n=3 calls=[] refs=[] strings=[]
T171 +0df8 n=5 calls=[] refs=[] strings=[]
T172 +0e0c n=3 calls=[] refs=[] strings=[]
T173 +0e18 n=16 calls=['Zi8GetTableCount'] refs=[] strings=[]
T174 +0e58 n=3 calls=[] refs=[] strings=[]
T175 +0e64 n=3 calls=[] refs=[] strings=[]
T176 +0e70 n=3 calls=[] refs=[] strings=[]
T177 +0e7c n=3 calls=[] refs=[] strings=[]
T178 +0e88 n=3 calls=[] refs=[] strings=[]
T179 +0e94 n=3 calls=[] refs=[] strings=[]
T180 +0ea0 n=3 calls=[] refs=[] strings=[]
T181 +0eac n=2 calls=[] refs=[] strings=[]
T182 +0eb4 n=3 calls=[] refs=[] strings=[]
T183 +0ec0 n=5 calls=[] refs=[] strings=[]
T184 +0ed4 n=4 calls=[] refs=[] strings=[]
T185 +0ee4 n=3 calls=[] refs=[] strings=[]
T186 +0ef0 n=2 calls=[] refs=[] strings=[]
T187 +0ef8 n=5 calls=[] refs=[] strings=[]
T188 +0f0c n=2 calls=[] refs=[] strings=[]
T189 +0f14 n=2 calls=[] refs=[] strings=[]
T190 +0f1c n=13 calls=[] refs=[] strings=[]
T191 +0f50 n=11 calls=['Zi8ConvertWC2Key'] refs=[] strings=[]
T192 +0f7c n=1 calls=[] refs=[] strings=[]
T193 +0f80 n=3 calls=[] refs=[] strings=[]
T194 +0f8c n=21 calls=[] refs=[] strings=[]
T195 +0fe0 n=2 calls=[] refs=[] strings=[]
T196 +0fe8 n=13 calls=[] refs=[] strings=[]
T197 +101c n=11 calls=['Zi8ConvertWC2Key'] refs=[] strings=[]
T198 +1048 n=1 calls=[] refs=[] strings=[]
T199 +104c n=3 calls=[] refs=[] strings=[]
T200 +1058 n=20 calls=[] refs=[] strings=[]
T201 +10a8 n=3 calls=[] refs=[] strings=[]
T202 +10b4 n=3 calls=[] refs=[] strings=[]
T203 +10c0 n=2 calls=[] refs=[] strings=[]
T204 +10c8 n=12 calls=['Zi8GetTableCount'] refs=[] strings=[]
T205 +10f8 n=3 calls=[] refs=[] strings=[]
T206 +1104 n=3 calls=[] refs=[] strings=[]
T207 +1110 n=7 calls=[] refs=[] strings=[]
T208 +112c n=7 calls=[] refs=[] strings=[]
T209 +1148 n=12 calls=['Zi8ConvertWC2Key'] refs=[] strings=[]
T210 +1178 n=3 calls=[] refs=[] strings=[]
T211 +1184 n=5 calls=[] refs=[] strings=[]
T212 +1198 n=3 calls=[] refs=[] strings=[]
T213 +11a4 n=4 calls=[] refs=[] strings=[]
T214 +11b4 n=6 calls=[] refs=[] strings=[]
T215 +11cc n=1 calls=[] refs=[] strings=[]
T216 +11d0 n=2 calls=[] refs=[] strings=[]
T217 +11d8 n=1 calls=[] refs=[] strings=[]
T218 +11dc n=2 calls=[] refs=[] strings=[]
T219 +11e4 n=1 calls=[] refs=[] strings=[]
T220 +11e8 n=2 calls=[] refs=[] strings=[]
T221 +11f0 n=1 calls=[] refs=[] strings=[]
T222 +11f4 n=2 calls=[] refs=[] strings=[]
T223 +11fc n=2 calls=[] refs=[] strings=[]
T224 +1204 n=3 calls=[] refs=[] strings=[]
T225 +1210 n=3 calls=[] refs=[] strings=[]
T226 +121c n=1 calls=[] refs=[] strings=[]
T227 +1220 n=2 calls=[] refs=[] strings=[]
T228 +1228 n=12 calls=['Zi8GetTableCount'] refs=[] strings=[]
T229 +1258 n=3 calls=[] refs=[] strings=[]
T230 +1264 n=2 calls=[] refs=[] strings=[]
T231 +126c n=5 calls=[] refs=[] strings=[]
T232 +1280 n=3 calls=[] refs=[] strings=[]
T233 +128c n=5 calls=[] refs=[] strings=[]
T234 +12a0 n=1 calls=[] refs=[] strings=[]
T235 +12a4 n=1 calls=[] refs=[] strings=[]
T236 +12a8 n=3 calls=[] refs=[] strings=[]
T237 +12b4 n=5 calls=[] refs=[] strings=[]
T238 +12c8 n=2 calls=[] refs=[] strings=[]
T239 +12d0 n=3 calls=[] refs=[] strings=[]
T240 +12dc n=3 calls=[] refs=[] strings=[]
T241 +12e8 n=3 calls=[] refs=[] strings=[]
T242 +12f4 n=3 calls=[] refs=[] strings=[]
T243 +1300 n=3 calls=[] refs=[] strings=[]
T244 +130c n=4 calls=[] refs=[] strings=[]
T245 +131c n=3 calls=[] refs=[] strings=[]
T246 +1328 n=12 calls=['Zi8getKeyLayout'] refs=[] strings=[]
T247 +1358 n=3 calls=[] refs=[] strings=[]
T248 +1364 n=2 calls=[] refs=[] strings=[]
T249 +136c n=12 calls=['Zi8GetTableCount'] refs=[] strings=[]
T250 +139c n=2 calls=[] refs=[] strings=[]
T251 +13a4 n=3 calls=[] refs=[] strings=[]
T252 +13b0 n=7 calls=['Zi8GetTableAddress'] refs=[] strings=[]
T253 +13cc n=3 calls=[] refs=[] strings=[]
T254 +13d8 n=3 calls=[] refs=[] strings=[]
T255 +13e4 n=3 calls=[] refs=[] strings=[]
T256 +13f0 n=7 calls=[] refs=[] strings=[]
T257 +140c n=4 calls=['Zi8Memset'] refs=[] strings=[]
T258 +141c n=4 calls=[] refs=[] strings=[]
T259 +142c n=7 calls=[] refs=[] strings=[]
T260 +1448 n=3 calls=[] refs=[] strings=[]
T261 +1454 n=1 calls=[] refs=[] strings=[]
T262 +1458 n=3 calls=[] refs=[] strings=[]
T263 +1464 n=2 calls=[] refs=[] strings=[]
T264 +146c n=3 calls=[] refs=[] strings=[]
T265 +1478 n=3 calls=[] refs=[] strings=[]
T266 +1484 n=1 calls=[] refs=[] strings=[]
T267 +1488 n=2 calls=[] refs=[] strings=[]
T268 +1490 n=2 calls=[] refs=[] strings=[]
T269 +1498 n=1 calls=[] refs=[] strings=[]
T270 +149c n=5 calls=[] refs=[] strings=[]
T271 +14b0 n=1 calls=[] refs=[] strings=[]
T272 +14b4 n=2 calls=[] refs=[] strings=[]
T273 +14bc n=2 calls=[] refs=[] strings=[]
T274 +14c4 n=1 calls=[] refs=[] strings=[]
T275 +14c8 n=2 calls=[] refs=[] strings=[]
T276 +14d0 n=1 calls=[] refs=[] strings=[]
T277 +14d4 n=2 calls=[] refs=[] strings=[]
T278 +14dc n=1 calls=[] refs=[] strings=[]
T279 +14e0 n=3 calls=[] refs=[] strings=[]
T280 +14ec n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
T281 +1510 n=4 calls=[] refs=[] strings=[]
T282 +1520 n=4 calls=[] refs=[] strings=[]
T283 +1530 n=10 calls=['Zi8getKeyLayout'] refs=[] strings=[]
T284 +1558 n=3 calls=[] refs=[] strings=[]
T285 +1564 n=3 calls=[] refs=[] strings=[]
T286 +1570 n=3 calls=[] refs=[] strings=[]
T287 +157c n=3 calls=[] refs=[] strings=[]
T288 +1588 n=3 calls=[] refs=[] strings=[]
T289 +1594 n=7 calls=[] refs=[] strings=[]
T290 +15b0 n=3 calls=[] refs=[] strings=[]
T291 +15bc n=3 calls=[] refs=[] strings=[]
T292 +15c8 n=4 calls=[] refs=[] strings=[]
T293 +15d8 n=3 calls=[] refs=[] strings=[]
T294 +15e4 n=3 calls=[] refs=[] strings=[]
T295 +15f0 n=7 calls=[] refs=[] strings=[]
T296 +160c n=3 calls=[] refs=[] strings=[]
T297 +1618 n=3 calls=[] refs=[] strings=[]
T298 +1624 n=5 calls=[] refs=[] strings=[]
T299 +1638 n=3 calls=[] refs=[] strings=[]
T300 +1644 n=4 calls=[] refs=[] strings=[]
T301 +1654 n=3 calls=[] refs=[] strings=[]
T302 +1660 n=3 calls=[] refs=[] strings=[]
T303 +166c n=3 calls=[] refs=[] strings=[]
T304 +1678 n=7 calls=[] refs=[] strings=[]
T305 +1694 n=3 calls=[] refs=[] strings=[]
T306 +16a0 n=4 calls=[] refs=[] strings=[]
T307 +16b0 n=2 calls=[] refs=[] strings=[]
T308 +16b8 n=2 calls=[] refs=[] strings=[]
T309 +16c0 n=3 calls=[] refs=[] strings=[]
T310 +16cc n=4 calls=[] refs=[] strings=[]
T311 +16dc n=1 calls=[] refs=[] strings=[]
T312 +16e0 n=4 calls=[] refs=[] strings=[]
T313 +16f0 n=3 calls=[] refs=[] strings=[]
T314 +16fc n=1 calls=[] refs=[] strings=[]
T315 +1700 n=3 calls=[] refs=[] strings=[]
T316 +170c n=4 calls=[] refs=[] strings=[]
T317 +171c n=4 calls=[] refs=[] strings=[]
T318 +172c n=3 calls=[] refs=[] strings=[]
T319 +1738 n=3 calls=[] refs=[] strings=[]
T320 +1744 n=3 calls=[] refs=[] strings=[]
T321 +1750 n=4 calls=[] refs=[] strings=[]
T322 +1760 n=4 calls=[] refs=[] strings=[]
T323 +1770 n=3 calls=[] refs=[] strings=[]
T324 +177c n=5 calls=[] refs=[] strings=[]
T325 +1790 n=3 calls=[] refs=[] strings=[]
T326 +179c n=4 calls=[] refs=[] strings=[]
T327 +17ac n=4 calls=[] refs=[] strings=[]
T328 +17bc n=4 calls=[] refs=[] strings=[]
T329 +17cc n=4 calls=[] refs=[] strings=[]
T330 +17dc n=3 calls=[] refs=[] strings=[]
T331 +17e8 n=1 calls=[] refs=[] strings=[]
T332 +17ec n=3 calls=[] refs=[] strings=[]
T333 +17f8 n=3 calls=[] refs=[] strings=[]
T334 +1804 n=27 calls=[] refs=[] strings=[]
T335 +1870 n=3 calls=[] refs=[] strings=[]
T336 +187c n=6 calls=[] refs=[] strings=[]
T337 +1894 n=7 calls=[] refs=[] strings=[]
T338 +18b0 n=6 calls=[] refs=[('jumptable_8166AA58', 0), ('jumptable_8166AA58', 0)] strings=[]
T339 +18c8 n=2 calls=[] refs=[] strings=[]
T340 +18d0 n=3 calls=[] refs=[] strings=[]
T341 +18dc n=3 calls=[] refs=[] strings=[]
T342 +18e8 n=3 calls=[] refs=[] strings=[]
T343 +18f4 n=3 calls=[] refs=[] strings=[]
T344 +1900 n=5 calls=[] refs=[] strings=[]
T345 +1914 n=5 calls=[] refs=[] strings=[]
T346 +1928 n=7 calls=[] refs=[] strings=[]
T347 +1944 n=3 calls=[] refs=[] strings=[]
T348 +1950 n=3 calls=[] refs=[] strings=[]
T349 +195c n=23 calls=['Zi8MatchROMdata'] refs=[] strings=[]
T350 +19b8 n=3 calls=[] refs=[] strings=[]
T351 +19c4 n=3 calls=[] refs=[] strings=[]
T352 +19d0 n=6 calls=[] refs=[] strings=[]
T353 +19e8 n=3 calls=[] refs=[] strings=[]
T354 +19f4 n=23 calls=['Zi8MatchROMdata'] refs=[] strings=[]
T355 +1a50 n=20 calls=['Zi8MatchROMdata'] refs=[] strings=[]
T356 +1aa0 n=3 calls=[] refs=[] strings=[]
T357 +1aac n=4 calls=[] refs=[] strings=[]
T358 +1abc n=2 calls=[] refs=[] strings=[]
T359 +1ac4 n=3 calls=[] refs=[] strings=[]
T360 +1ad0 n=4 calls=[] refs=[] strings=[]
T361 +1ae0 n=3 calls=[] refs=[] strings=[]
T362 +1aec n=3 calls=[] refs=[] strings=[]
T363 +1af8 n=3 calls=[] refs=[] strings=[]
T364 +1b04 n=11 calls=[] refs=[] strings=[]
T365 +1b30 n=3 calls=[] refs=[] strings=[]
T366 +1b3c n=3 calls=[] refs=[] strings=[]
T367 +1b48 n=4 calls=[] refs=[] strings=[]
T368 +1b58 n=3 calls=[] refs=[] strings=[]
T369 +1b64 n=11 calls=['Zi8ITspecialExclusion'] refs=[] strings=[]
T370 +1b90 n=3 calls=[] refs=[] strings=[]
T371 +1b9c n=3 calls=[] refs=[] strings=[]
T372 +1ba8 n=12 calls=['Zi8_814659E8'] refs=[] strings=[]
T373 +1bd8 n=3 calls=[] refs=[] strings=[]
T374 +1be4 n=8 calls=['Zi8IsVowel'] refs=[] strings=[]
T375 +1c04 n=2 calls=[] refs=[] strings=[]
T376 +1c0c n=3 calls=[] refs=[] strings=[]
T377 +1c18 n=11 calls=[] refs=[] strings=[]
T378 +1c44 n=1 calls=[] refs=[] strings=[]
T379 +1c48 n=3 calls=[] refs=[] strings=[]
T380 +1c54 n=3 calls=[] refs=[] strings=[]
T381 +1c60 n=3 calls=[] refs=[] strings=[]
T382 +1c6c n=3 calls=[] refs=[] strings=[]
T383 +1c78 n=3 calls=[] refs=[] strings=[]
T384 +1c84 n=3 calls=[] refs=[] strings=[]
T385 +1c90 n=3 calls=[] refs=[] strings=[]
T386 +1c9c n=3 calls=[] refs=[] strings=[]
T387 +1ca8 n=3 calls=[] refs=[] strings=[]
T388 +1cb4 n=3 calls=[] refs=[] strings=[]
T389 +1cc0 n=7 calls=['Zi8ITspecialExclusion'] refs=[] strings=[]
T390 +1cdc n=3 calls=[] refs=[] strings=[]
T391 +1ce8 n=3 calls=[] refs=[] strings=[]
T392 +1cf4 n=7 calls=['Zi8_814659E8'] refs=[] strings=[]
T393 +1d10 n=3 calls=[] refs=[] strings=[]
T394 +1d1c n=6 calls=['Zi8IsVowel'] refs=[] strings=[]
T395 +1d34 n=2 calls=[] refs=[] strings=[]
T396 +1d3c n=3 calls=[] refs=[] strings=[]
T397 +1d48 n=8 calls=[] refs=[] strings=[]
T398 +1d68 n=3 calls=[] refs=[] strings=[]
T399 +1d74 n=5 calls=[] refs=[] strings=[]
T400 +1d88 n=3 calls=[] refs=[] strings=[]
T401 +1d94 n=2 calls=[] refs=[] strings=[]
T402 +1d9c n=6 calls=['Zi8IsZicorpSignature'] refs=[] strings=[]
T403 +1db4 n=3 calls=[] refs=[] strings=[]
T404 +1dc0 n=19 calls=['Zi8MatchPUDdata'] refs=[] strings=[]
T405 +1e0c n=26 calls=['Zi8MatchUWDdata'] refs=[] strings=[]
T406 +1e74 n=3 calls=[] refs=[] strings=[]
T407 +1e80 n=3 calls=[] refs=[] strings=[]
T408 +1e8c n=6 calls=[] refs=[] strings=[]
T409 +1ea4 n=3 calls=[] refs=[] strings=[]
T410 +1eb0 n=19 calls=['Zi8MatchOEMdata'] refs=[] strings=[]
T411 +1efc n=6 calls=[] refs=[] strings=[]
T412 +1f14 n=6 calls=[] refs=[] strings=[]
T413 +1f2c n=3 calls=[] refs=[] strings=[]
T414 +1f38 n=3 calls=[] refs=[] strings=[]
T415 +1f44 n=3 calls=[] refs=[] strings=[]
T416 +1f50 n=2 calls=[] refs=[] strings=[]
T417 +1f58 n=9 calls=[] refs=[] strings=[]
T418 +1f7c n=1 calls=[] refs=[] strings=[]
T419 +1f80 n=4 calls=[] refs=[] strings=[]
T420 +1f90 n=4 calls=[] refs=[] strings=[]
T421 +1fa0 n=3 calls=[] refs=[] strings=[]
T422 +1fac n=2 calls=[] refs=[] strings=[]
T423 +1fb4 n=9 calls=[] refs=[] strings=[]
T424 +1fd8 n=1 calls=[] refs=[] strings=[]
T425 +1fdc n=3 calls=[] refs=[] strings=[]
T426 +1fe8 n=3 calls=[] refs=[] strings=[]
T427 +1ff4 n=3 calls=[] refs=[] strings=[]
T428 +2000 n=9 calls=[] refs=[] strings=[]
T429 +2024 n=5 calls=[] refs=[] strings=[]
T430 +2038 n=2 calls=[] refs=[] strings=[]
T431 +2040 n=8 calls=[] refs=[] strings=[]
T432 +2060 n=8 calls=[] refs=[] strings=[]
T433 +2080 n=3 calls=[] refs=[] strings=[]
T434 +208c n=3 calls=[] refs=[] strings=[]
T435 +2098 n=5 calls=[] refs=[] strings=[]
T436 +20ac n=7 calls=[] refs=[] strings=[]
T437 +20c8 n=3 calls=[] refs=[] strings=[]
T438 +20d4 n=5 calls=[] refs=[] strings=[]
T439 +20e8 n=3 calls=[] refs=[] strings=[]
T440 +20f4 n=5 calls=[] refs=[] strings=[]
T441 +2108 n=3 calls=[] refs=[] strings=[]
T442 +2114 n=3 calls=[] refs=[] strings=[]
T443 +2120 n=3 calls=[] refs=[] strings=[]
T444 +212c n=3 calls=[] refs=[] strings=[]
T445 +2138 n=4 calls=[] refs=[] strings=[]
T446 +2148 n=3 calls=[] refs=[] strings=[]
T447 +2154 n=6 calls=[] refs=[] strings=[]
T448 +216c n=5 calls=[] refs=[] strings=[]
T449 +2180 n=6 calls=[] refs=[] strings=[]
T450 +2198 n=1 calls=[] refs=[] strings=[]
T451 +219c n=2 calls=[] refs=[] strings=[]
T452 +21a4 n=2 calls=[] refs=[] strings=[]
T453 +21ac n=1 calls=[] refs=[] strings=[]
T454 +21b0 n=13 calls=['Zi8getKeyLayout'] refs=[] strings=[]
T455 +21e4 n=2 calls=[] refs=[] strings=[]
T456 +21ec n=7 calls=[] refs=[] strings=[]
T457 +2208 n=3 calls=[] refs=[] strings=[]
T458 +2214 n=3 calls=[] refs=[] strings=[]
T459 +2220 n=3 calls=[] refs=[] strings=[]
T460 +222c n=3 calls=[] refs=[] strings=[]
T461 +2238 n=4 calls=[] refs=[] strings=[]
T462 +2248 n=3 calls=[] refs=[] strings=[]
T463 +2254 n=3 calls=[] refs=[] strings=[]
T464 +2260 n=7 calls=[] refs=[] strings=[]
T465 +227c n=5 calls=[] refs=[] strings=[]
T466 +2290 n=3 calls=[] refs=[] strings=[]
T467 +229c n=3 calls=[] refs=[] strings=[]
T468 +22a8 n=6 calls=[] refs=[] strings=[]
T469 +22c0 n=3 calls=[] refs=[] strings=[]
T470 +22cc n=6 calls=[] refs=[] strings=[]
T471 +22e4 n=1 calls=[] refs=[] strings=[]
T472 +22e8 n=2 calls=[] refs=[] strings=[]
T473 +22f0 n=2 calls=[] refs=[] strings=[]
T474 +22f8 n=1 calls=[] refs=[] strings=[]
T475 +22fc n=12 calls=['Zi8getKeyLayout'] refs=[] strings=[]
T476 +232c n=2 calls=[] refs=[] strings=[]
T477 +2334 n=5 calls=[] refs=[] strings=[]
T478 +2348 n=4 calls=[] refs=[] strings=[]
T479 +2358 n=3 calls=[] refs=[] strings=[]
T480 +2364 n=3 calls=[] refs=[] strings=[]
T481 +2370 n=3 calls=[] refs=[] strings=[]
T482 +237c n=3 calls=[] refs=[] strings=[]
T483 +2388 n=8 calls=['Zi8ITspecialExclusion'] refs=[] strings=[]
T484 +23a8 n=1 calls=[] refs=[] strings=[]
T485 +23ac n=3 calls=[] refs=[] strings=[]
T486 +23b8 n=7 calls=['Zi8_814659E8'] refs=[] strings=[]
T487 +23d4 n=1 calls=[] refs=[] strings=[]
T488 +23d8 n=7 calls=['Zi8IsVowel'] refs=[] strings=[]
T489 +23f4 n=3 calls=[] refs=[] strings=[]
T490 +2400 n=3 calls=[] refs=[] strings=[]
T491 +240c n=3 calls=[] refs=[] strings=[]
T492 +2418 n=3 calls=[] refs=[] strings=[]
T493 +2424 n=3 calls=[] refs=[] strings=[]
T494 +2430 n=3 calls=[] refs=[] strings=[]
T495 +243c n=7 calls=[] refs=[] strings=[]
T496 +2458 n=3 calls=[] refs=[] strings=[]
T497 +2464 n=4 calls=[] refs=[] strings=[]
T498 +2474 n=6 calls=[] refs=[] strings=[]
T499 +248c n=13 calls=['Zi8DeTokenization'] refs=[] strings=[]
T500 +24c0 n=6 calls=[] refs=[] strings=[]
T501 +24d8 n=6 calls=[] refs=[] strings=[]
T502 +24f0 n=6 calls=[] refs=[] strings=[]
T503 +2508 n=7 calls=[] refs=[] strings=[]
T504 +2524 n=3 calls=[] refs=[] strings=[]
T505 +2530 n=8 calls=['Zi8ZHCheckSpelling'] refs=[] strings=[]
T506 +2550 n=3 calls=[] refs=[] strings=[]
T507 +255c n=3 calls=[] refs=[] strings=[]
T508 +2568 n=3 calls=[] refs=[] strings=[]
T509 +2574 n=6 calls=['Zi8ChangeWordCase'] refs=[] strings=[]
T510 +258c n=3 calls=[] refs=[] strings=[]
T511 +2598 n=6 calls=[] refs=[] strings=[]
T512 +25b0 n=8 calls=[] refs=[] strings=[]
T513 +25d0 n=6 calls=[] refs=[] strings=[]
T514 +25e8 n=12 calls=['Zi8IsDupWordW'] refs=[] strings=[]
T515 +2618 n=3 calls=[] refs=[] strings=[]
T516 +2624 n=4 calls=[] refs=[] strings=[]
T517 +2634 n=1 calls=[] refs=[] strings=[]
T518 +2638 n=3 calls=[] refs=[] strings=[]
T519 +2644 n=3 calls=[] refs=[] strings=[]
T520 +2650 n=5 calls=[] refs=[] strings=[]
T521 +2664 n=5 calls=[] refs=[] strings=[]
T522 +2678 n=3 calls=[] refs=[] strings=[]
T523 +2684 n=1 calls=[] refs=[] strings=[]
T524 +2688 n=2 calls=[] refs=[] strings=[]
T525 +2690 n=1 calls=[] refs=[] strings=[]
T526 +2694 n=2 calls=[] refs=[] strings=[]
T527 +269c n=1 calls=[] refs=[] strings=[]
T528 +26a0 n=9 calls=[] refs=[] strings=[]
T529 +26c4 n=6 calls=[] refs=[] strings=[]
T530 +26dc n=7 calls=[] refs=[] strings=[]
T531 +26f8 n=9 calls=[] refs=[] strings=[]
T532 +271c n=2 calls=[] refs=[] strings=[]
T533 +2724 n=1 calls=[] refs=[] strings=[]
T534 +2728 n=3 calls=[] refs=[] strings=[]
T535 +2734 n=3 calls=[] refs=[] strings=[]
T536 +2740 n=3 calls=[] refs=[] strings=[]
T537 +274c n=14 calls=['Zi8ConvertWC2UC'] refs=[] strings=[]
T538 +2784 n=4 calls=[] refs=[] strings=[]
T539 +2794 n=1 calls=[] refs=[] strings=[]
T540 +2798 n=3 calls=[] refs=[] strings=[]
T541 +27a4 n=9 calls=[] refs=[] strings=[]
T542 +27c8 n=3 calls=[] refs=[] strings=[]
T543 +27d4 n=4 calls=[] refs=[] strings=[]
T544 +27e4 n=4 calls=[] refs=[] strings=[]
T545 +27f4 n=6 calls=[] refs=[] strings=[]
T546 +280c n=12 calls=[] refs=[] strings=[]
T547 +283c n=1 calls=[] refs=[] strings=[]
T548 +2840 n=3 calls=[] refs=[] strings=[]
T549 +284c n=3 calls=[] refs=[] strings=[]
T550 +2858 n=4 calls=[] refs=[] strings=[]
T551 +2868 n=3 calls=[] refs=[] strings=[]
T552 +2874 n=3 calls=[] refs=[] strings=[]
T553 +2880 n=6 calls=[] refs=[] strings=[]
T554 +2898 n=5 calls=[] refs=[] strings=[]
T555 +28ac n=6 calls=[] refs=[] strings=[]
T556 +28c4 n=5 calls=[] refs=[] strings=[]
T557 +28d8 n=6 calls=[] refs=[] strings=[]
T558 +28f0 n=1 calls=[] refs=[] strings=[]
T559 +28f4 n=3 calls=[] refs=[] strings=[]
T560 +2900 n=2 calls=[] refs=[] strings=[]
T561 +2908 n=8 calls=[] refs=[] strings=[]
T562 +2928 n=1 calls=[] refs=[] strings=[]
T563 +292c n=3 calls=[] refs=[] strings=[]
T564 +2938 n=3 calls=[] refs=[] strings=[]
T565 +2944 n=3 calls=[] refs=[] strings=[]
T566 +2950 n=3 calls=[] refs=[] strings=[]
T567 +295c n=3 calls=[] refs=[] strings=[]
T568 +2968 n=6 calls=['Zi8WCharCount'] refs=[] strings=[]
T569 +2980 n=3 calls=[] refs=[] strings=[]
T570 +298c n=3 calls=[] refs=[] strings=[]
T571 +2998 n=3 calls=[] refs=[] strings=[]
T572 +29a4 n=3 calls=[] refs=[] strings=[]
T573 +29b0 n=3 calls=[] refs=[] strings=[]
T574 +29bc n=3 calls=[] refs=[] strings=[]
T575 +29c8 n=3 calls=[] refs=[] strings=[]
T576 +29d4 n=3 calls=[] refs=[] strings=[]
T577 +29e0 n=3 calls=[] refs=[] strings=[]
T578 +29ec n=2 calls=[] refs=[] strings=[]
T579 +29f4 n=3 calls=[] refs=[] strings=[]
T580 +2a00 n=5 calls=[] refs=[] strings=[]
T581 +2a14 n=3 calls=[] refs=[] strings=[]
T582 +2a20 n=3 calls=[] refs=[] strings=[]
T583 +2a2c n=3 calls=[] refs=[] strings=[]
T584 +2a38 n=2 calls=[] refs=[] strings=[]
T585 +2a40 n=8 calls=[] refs=[] strings=[]
T586 +2a60 n=3 calls=[] refs=[] strings=[]
T587 +2a6c n=2 calls=[] refs=[] strings=[]
T588 +2a74 n=8 calls=[] refs=[] strings=[]
T589 +2a94 n=3 calls=[] refs=[] strings=[]
T590 +2aa0 n=7 calls=[] refs=[] strings=[]
T591 +2abc n=3 calls=[] refs=[] strings=[]
T592 +2ac8 n=5 calls=[] refs=[] strings=[]
T593 +2adc n=3 calls=[] refs=[] strings=[]
T594 +2ae8 n=3 calls=[] refs=[] strings=[]
T595 +2af4 n=3 calls=[] refs=[] strings=[]
T596 +2b00 n=2 calls=[] refs=[] strings=[]
T597 +2b08 n=3 calls=[] refs=[] strings=[]
T598 +2b14 n=3 calls=[] refs=[] strings=[]
T599 +2b20 n=4 calls=[] refs=[] strings=[]
T600 +2b30 n=3 calls=[] refs=[] strings=[]
T601 +2b3c n=4 calls=[] refs=[] strings=[]
T602 +2b4c n=3 calls=[] refs=[] strings=[]
T603 +2b58 n=4 calls=[] refs=[] strings=[]
T604 +2b68 n=3 calls=[] refs=[] strings=[]
T605 +2b74 n=4 calls=[] refs=[] strings=[]
T606 +2b84 n=3 calls=[] refs=[] strings=[]
T607 +2b90 n=3 calls=[] refs=[] strings=[]
T608 +2b9c n=3 calls=[] refs=[] strings=[]
T609 +2ba8 n=2 calls=[] refs=[] strings=[]
T610 +2bb0 n=6 calls=[] refs=[] strings=[]
T611 +2bc8 n=3 calls=[] refs=[] strings=[]
T612 +2bd4 n=6 calls=[] refs=[] strings=[]
T613 +2bec n=3 calls=[] refs=[] strings=[]
T614 +2bf8 n=3 calls=[] refs=[] strings=[]
T615 +2c04 n=4 calls=[] refs=[] strings=[]
T616 +2c14 n=3 calls=[] refs=[] strings=[]
T617 +2c20 n=4 calls=[] refs=[] strings=[]
T618 +2c30 n=3 calls=[] refs=[] strings=[]
T619 +2c3c n=4 calls=[] refs=[] strings=[]
T620 +2c4c n=3 calls=[] refs=[] strings=[]
T621 +2c58 n=4 calls=[] refs=[] strings=[]
T622 +2c68 n=5 calls=[] refs=[] strings=[]
T623 +2c7c n=3 calls=[] refs=[] strings=[]
T624 +2c88 n=3 calls=[] refs=[] strings=[]
T625 +2c94 n=3 calls=[] refs=[] strings=[]
T626 +2ca0 n=4 calls=[] refs=[] strings=[]
T627 +2cb0 n=2 calls=[] refs=[] strings=[]
T628 +2cb8 n=6 calls=[] refs=[] strings=[]
T629 +2cd0 n=3 calls=[] refs=[] strings=[]
T630 +2cdc n=4 calls=[] refs=[] strings=[]
T631 +2cec n=2 calls=[] refs=[] strings=[]
T632 +2cf4 n=6 calls=[] refs=[] strings=[]
T633 +2d0c n=3 calls=[] refs=[] strings=[]
T634 +2d18 n=4 calls=[] refs=[] strings=[]
T635 +2d28 n=3 calls=[] refs=[] strings=[]
T636 +2d34 n=3 calls=[] refs=[] strings=[]
T637 +2d40 n=4 calls=[] refs=[] strings=[]
T638 +2d50 n=3 calls=[] refs=[] strings=[]
T639 +2d5c n=4 calls=[] refs=[] strings=[]
T640 +2d6c n=3 calls=[] refs=[] strings=[]
T641 +2d78 n=4 calls=[] refs=[] strings=[]
T642 +2d88 n=3 calls=[] refs=[] strings=[]
T643 +2d94 n=4 calls=[] refs=[] strings=[]
T644 +2da4 n=5 calls=[] refs=[] strings=[]
T645 +2db8 n=3 calls=[] refs=[] strings=[]
T646 +2dc4 n=3 calls=[] refs=[] strings=[]
T647 +2dd0 n=3 calls=[] refs=[] strings=[]
T648 +2ddc n=2 calls=[] refs=[] strings=[]
T649 +2de4 n=6 calls=[] refs=[] strings=[]
T650 +2dfc n=3 calls=[] refs=[] strings=[]
T651 +2e08 n=2 calls=[] refs=[] strings=[]
T652 +2e10 n=7 calls=[] refs=[] strings=[]
T653 +2e2c n=3 calls=[] refs=[] strings=[]
T654 +2e38 n=2 calls=[] refs=[] strings=[]
T655 +2e40 n=2 calls=[] refs=[] strings=[]
T656 +2e48 n=10 calls=['Zi8ConvertWC2UC'] refs=[] strings=[]
T657 +2e70 n=5 calls=[] refs=[] strings=[]
T658 +2e84 n=7 calls=[] refs=[] strings=[]
T659 +2ea0 n=3 calls=[] refs=[] strings=[]
T660 +2eac n=13 calls=[] refs=[] strings=[]
T661 +2ee0 n=7 calls=[] refs=[] strings=[]
T662 +2efc n=5 calls=[] refs=[] strings=[]
T663 +2f10 n=1 calls=[] refs=[] strings=[]
T664 +2f14 n=11 calls=[] refs=[] strings=[]
T665 +2f40 n=6 calls=[] refs=[] strings=[]
T666 +2f58 n=3 calls=[] refs=[] strings=[]
T667 +2f64 n=8 calls=[] refs=[] strings=[]
T668 +2f84 n=3 calls=[] refs=[] strings=[]
T669 +2f90 n=3 calls=[] refs=[] strings=[]
T670 +2f9c n=3 calls=[] refs=[] strings=[]
T671 +2fa8 n=4 calls=[] refs=[] strings=[]
T672 +2fb8 n=3 calls=[] refs=[] strings=[]
T673 +2fc4 n=2 calls=[] refs=[] strings=[]
T674 +2fcc n=6 calls=[] refs=[] strings=[]
T675 +2fe4 n=3 calls=[] refs=[] strings=[]
T676 +2ff0 n=10 calls=[] refs=[] strings=[]
T677 +3018 n=2 calls=[] refs=[] strings=[]
T678 +3020 n=6 calls=[] refs=[] strings=[]
T679 +3038 n=3 calls=[] refs=[] strings=[]
T680 +3044 n=7 calls=[] refs=[] strings=[]
T681 +3060 n=3 calls=[] refs=[] strings=[]
T682 +306c n=3 calls=[] refs=[] strings=[]
T683 +3078 n=4 calls=[] refs=[] strings=[]
T684 +3088 n=3 calls=[] refs=[] strings=[]
T685 +3094 n=3 calls=[] refs=[] strings=[]
T686 +30a0 n=3 calls=[] refs=[] strings=[]
T687 +30ac n=3 calls=[] refs=[] strings=[]
T688 +30b8 n=10 calls=['Zi8GetTableCount'] refs=[] strings=[]
T689 +30e0 n=4 calls=[] refs=[] strings=[]
T690 +30f0 n=4 calls=[] refs=[] strings=[]
T691 +3100 n=11 calls=['Zi8getKeyLayout'] refs=[] strings=[]
T692 +312c n=2 calls=[] refs=[] strings=[]
T693 +3134 n=3 calls=[] refs=[] strings=[]
T694 +3140 n=3 calls=[] refs=[] strings=[]
T695 +314c n=3 calls=[] refs=[] strings=[]
T696 +3158 n=5 calls=[] refs=[] strings=[]
T697 +316c n=4 calls=[] refs=[] strings=[]
T698 +317c n=3 calls=[] refs=[] strings=[]
T699 +3188 n=4 calls=[] refs=[] strings=[]
T700 +3198 n=2 calls=[] refs=[] strings=[]
T701 +31a0 n=5 calls=[] refs=[] strings=[]
T702 +31b4 n=8 calls=[] refs=[] strings=[]
T703 +31d4 n=3 calls=[] refs=[] strings=[]
T704 +31e0 n=2 calls=[] refs=[] strings=[]
T705 +31e8 n=3 calls=[] refs=[] strings=[]
T706 +31f4 n=23 calls=[] refs=[] strings=[]
T707 +3250 n=11 calls=[] refs=[] strings=[]
T708 +327c n=5 calls=[] refs=[] strings=[]
T709 +3290 n=2 calls=[] refs=[] strings=[]
T710 +3298 n=5 calls=[] refs=[] strings=[]
T711 +32ac n=5 calls=[] refs=[] strings=[]
T712 +32c0 n=4 calls=[] refs=[] strings=[]
T713 +32d0 n=3 calls=[] refs=[] strings=[]
T714 +32dc n=3 calls=[] refs=[] strings=[]
T715 +32e8 n=3 calls=[] refs=[] strings=[]
T716 +32f4 n=3 calls=[] refs=[] strings=[]
T717 +3300 n=3 calls=[] refs=[] strings=[]
T718 +330c n=3 calls=[] refs=[] strings=[]
T719 +3318 n=7 calls=[] refs=[] strings=[]
T720 +3334 n=5 calls=[] refs=[] strings=[]
T721 +3348 n=6 calls=[] refs=[] strings=[]
T722 +3360 n=3 calls=[] refs=[] strings=[]
T723 +336c n=3 calls=[] refs=[] strings=[]
T724 +3378 n=3 calls=[] refs=[] strings=[]
T725 +3384 n=3 calls=[] refs=[] strings=[]
T726 +3390 n=3 calls=[] refs=[] strings=[]
T727 +339c n=3 calls=[] refs=[] strings=[]
T728 +33a8 n=3 calls=[] refs=[] strings=[]
T729 +33b4 n=7 calls=[] refs=[] strings=[]
T730 +33d0 n=5 calls=[] refs=[] strings=[]
T731 +33e4 n=5 calls=[] refs=[] strings=[]
T732 +33f8 n=9 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
T733 +341c n=3 calls=[] refs=[] strings=[]
T734 +3428 n=7 calls=[] refs=[] strings=[]
T735 +3444 n=3 calls=[] refs=[] strings=[]
T736 +3450 n=3 calls=[] refs=[] strings=[]
T737 +345c n=9 calls=[] refs=[] strings=[]
T738 +3480 n=19 calls=[] refs=[] strings=[]
T739 +34cc n=3 calls=[] refs=[] strings=[]
T740 +34d8 n=3 calls=[] refs=[] strings=[]
T741 +34e4 n=5 calls=[] refs=[] strings=[]
T742 +34f8 n=3 calls=[] refs=[] strings=[]
T743 +3504 n=3 calls=[] refs=[] strings=[]
T744 +3510 n=3 calls=[] refs=[] strings=[]
T745 +351c n=2 calls=[] refs=[] strings=[]
T746 +3524 n=3 calls=[] refs=[] strings=[]
T747 +3530 n=28 calls=[] refs=[] strings=[]
T748 +35a0 n=7 calls=[] refs=[] strings=[]
T749 +35bc n=3 calls=[] refs=[] strings=[]
T750 +35c8 n=7 calls=[] refs=[] strings=[]
T751 +35e4 n=3 calls=[] refs=[] strings=[]
T752 +35f0 n=2 calls=[] refs=[] strings=[]
T753 +35f8 n=2 calls=[] refs=[] strings=[]
T754 +3600 n=3 calls=[] refs=[] strings=[]
T755 +360c n=3 calls=[] refs=[] strings=[]
T756 +3618 n=3 calls=[] refs=[] strings=[]
T757 +3624 n=5 calls=[] refs=[] strings=[]
T758 +3638 n=3 calls=[] refs=[] strings=[]
T759 +3644 n=5 calls=[] refs=[] strings=[]
T760 +3658 n=3 calls=[] refs=[] strings=[]
T761 +3664 n=3 calls=[] refs=[] strings=[]
T762 +3670 n=3 calls=[] refs=[] strings=[]
T763 +367c n=7 calls=[] refs=[] strings=[]
T764 +3698 n=4 calls=[] refs=[] strings=[]
T765 +36a8 n=8 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
T766 +36c8 n=3 calls=[] refs=[] strings=[]
T767 +36d4 n=10 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
T768 +36fc n=3 calls=[] refs=[] strings=[]
T769 +3708 n=3 calls=[] refs=[] strings=[]
T770 +3714 n=10 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
T771 +373c n=10 calls=['Zi8GetTableCount'] refs=[] strings=[]
T772 +3764 n=7 calls=[] refs=[] strings=[]
T773 +3780 n=3 calls=[] refs=[] strings=[]
T774 +378c n=18 calls=[] refs=[] strings=[]
T775 +37d4 n=3 calls=[] refs=[] strings=[]
T776 +37e0 n=14 calls=[] refs=[] strings=[]
T777 +3818 n=8 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
T778 +3838 n=13 calls=[] refs=[] strings=[]
T779 +386c n=9 calls=[] refs=[] strings=[]
T780 +3890 n=3 calls=[] refs=[] strings=[]
T781 +389c n=7 calls=[] refs=[] strings=[]
T782 +38b8 n=4 calls=[] refs=[] strings=[]
T783 +38c8 n=3 calls=[] refs=[] strings=[]
T784 +38d4 n=3 calls=[] refs=[] strings=[]
T785 +38e0 n=3 calls=[] refs=[] strings=[]
T786 +38ec n=3 calls=[] refs=[] strings=[]
T787 +38f8 n=10 calls=['Zi8GetTableCount'] refs=[] strings=[]
T788 +3920 n=2 calls=[] refs=[] strings=[]
T789 +3928 n=6 calls=[] refs=[] strings=[]
T790 +3940 n=8 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
T791 +3960 n=13 calls=[] refs=[] strings=[]
T792 +3994 n=9 calls=[] refs=[] strings=[]
T793 +39b8 n=3 calls=[] refs=[] strings=[]
T794 +39c4 n=3 calls=[] refs=[] strings=[]
T795 +39d0 n=3 calls=[] refs=[] strings=[]
T796 +39dc n=3 calls=[] refs=[] strings=[]
T797 +39e8 n=3 calls=[] refs=[] strings=[]
T798 +39f4 n=5 calls=[] refs=[] strings=[]
T799 +3a08 n=10 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
T800 +3a30 n=3 calls=[] refs=[] strings=[]
T801 +3a3c n=3 calls=[] refs=[] strings=[]
T802 +3a48 n=3 calls=[] refs=[] strings=[]
T803 +3a54 n=9 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
T804 +3a78 n=7 calls=[] refs=[] strings=[]
T805 +3a94 n=3 calls=[] refs=[] strings=[]
T806 +3aa0 n=3 calls=[] refs=[] strings=[]
T807 +3aac n=5 calls=[] refs=[] strings=[]
T808 +3ac0 n=7 calls=[] refs=[] strings=[]
T809 +3adc n=7 calls=[] refs=[] strings=[]
T810 +3af8 n=5 calls=[] refs=[] strings=[]
T811 +3b0c n=3 calls=[] refs=[] strings=[]
T812 +3b18 n=3 calls=[] refs=[] strings=[]
T813 +3b24 n=8 calls=[] refs=[] strings=[]
T814 +3b44 n=3 calls=[] refs=[] strings=[]
T815 +3b50 n=3 calls=[] refs=[] strings=[]
T816 +3b5c n=6 calls=[] refs=[] strings=[]
T817 +3b74 n=3 calls=[] refs=[] strings=[]
T818 +3b80 n=3 calls=[] refs=[] strings=[]
T819 +3b8c n=6 calls=[] refs=[] strings=[]
T820 +3ba4 n=2 calls=[] refs=[] strings=[]
T821 +3bac n=6 calls=[] refs=[] strings=[]
T822 +3bc4 n=4 calls=[] refs=[] strings=[]
T823 +3bd4 n=3 calls=[] refs=[] strings=[]
T824 +3be0 n=2 calls=[] refs=[] strings=[]
T825 +3be8 n=3 calls=[] refs=[] strings=[]
T826 +3bf4 n=3 calls=[] refs=[] strings=[]
T827 +3c00 n=4 calls=[] refs=[] strings=[]
T828 +3c10 n=2 calls=[] refs=[] strings=[]
T829 +3c18 n=3 calls=[] refs=[] strings=[]
T830 +3c24 n=3 calls=[] refs=[] strings=[]
T831 +3c30 n=4 calls=[] refs=[] strings=[]
T832 +3c40 n=2 calls=[] refs=[] strings=[]
T833 +3c48 n=3 calls=[] refs=[] strings=[]
T834 +3c54 n=5 calls=[] refs=[] strings=[]
T835 +3c68 n=9 calls=['Zi8ConvertUC2WC'] refs=[] strings=[]
T836 +3c8c n=4 calls=[] refs=[] strings=[]
T837 +3c9c n=4 calls=[] refs=[] strings=[]
T838 +3cac n=1 calls=[] refs=[] strings=[]
T839 +3cb0 n=2 calls=[] refs=[] strings=[]
T840 +3cb8 n=5 calls=['Zi8SetHighlightedWordW'] refs=[] strings=[]
T841 +3ccc n=3 calls=[] refs=[] strings=[]
T842 +3cd8 n=4 calls=[] refs=[] strings=[]
T843 +3ce8 n=7 calls=[] refs=[] strings=[]
T844 +3d04 n=5 calls=[] refs=[] strings=[]
T845 +3d18 n=6 calls=[] refs=[] strings=[]
T846 +3d30 n=4 calls=[] refs=[] strings=[]
T847 +3d40 n=12 calls=[] refs=[] strings=[]
T848 +3d70 n=3 calls=[] refs=[] strings=[]
T849 +3d7c n=11 calls=['Zi8LogError', '_restgpr_27'] refs=[] strings=[]
BUILT BASIC BLOCKS
M000 +0000 n=94 calls=['_savegpr_27'] refs=[] strings=[]
M001 +0178 n=3 calls=[] refs=[] strings=[]
M002 +0184 n=3 calls=[] refs=[] strings=[]
M003 +0190 n=3 calls=[] refs=[] strings=[]
M004 +019c n=3 calls=[] refs=[] strings=[]
M005 +01a8 n=3 calls=[] refs=[] strings=[]
M006 +01b4 n=3 calls=[] refs=[] strings=[]
M007 +01c0 n=5 calls=[] refs=[] strings=[]
M008 +01d4 n=16 calls=[] refs=[] strings=[]
M009 +0214 n=4 calls=[] refs=[] strings=[]
M010 +0224 n=1 calls=[] refs=[] strings=[]
M011 +0228 n=7 calls=[] refs=[] strings=[]
M012 +0244 n=3 calls=[] refs=[] strings=[]
M013 +0250 n=3 calls=[] refs=[] strings=[]
M014 +025c n=7 calls=[] refs=[] strings=[]
M015 +0278 n=5 calls=[] refs=[] strings=[]
M016 +028c n=3 calls=[] refs=[] strings=[]
M017 +0298 n=4 calls=[] refs=[] strings=[]
M018 +02a8 n=2 calls=[] refs=[] strings=[]
M019 +02b0 n=3 calls=[] refs=[] strings=[]
M020 +02bc n=2 calls=[] refs=[] strings=[]
M021 +02c4 n=3 calls=[] refs=[] strings=[]
M022 +02d0 n=3 calls=[] refs=[] strings=[]
M023 +02dc n=3 calls=[] refs=[] strings=[]
M024 +02e8 n=3 calls=[] refs=[] strings=[]
M025 +02f4 n=3 calls=[] refs=[] strings=[]
M026 +0300 n=14 calls=[] refs=[] strings=[]
M027 +0338 n=6 calls=[] refs=[] strings=[]
M028 +0350 n=12 calls=['Zi8ChangeCharCase'] refs=[] strings=[]
M029 +0380 n=1 calls=[] refs=[] strings=[]
M030 +0384 n=3 calls=[] refs=[] strings=[]
M031 +0390 n=4 calls=[] refs=[] strings=[]
M032 +03a0 n=2 calls=[] refs=[] strings=[]
M033 +03a8 n=2 calls=[] refs=[] strings=[]
M034 +03b0 n=3 calls=[] refs=[] strings=[]
M035 +03bc n=3 calls=[] refs=[] strings=[]
M036 +03c8 n=3 calls=[] refs=[] strings=[]
M037 +03d4 n=3 calls=['ZiprocessHighlightedW'] refs=[] strings=[]
M038 +03e0 n=3 calls=[] refs=[] strings=[]
M039 +03ec n=3 calls=[] refs=[] strings=[]
M040 +03f8 n=3 calls=[] refs=[] strings=[]
M041 +0404 n=2 calls=[] refs=[] strings=[]
M042 +040c n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
M043 +0430 n=3 calls=[] refs=[] strings=[]
M044 +043c n=2 calls=[] refs=[] strings=[]
M045 +0444 n=3 calls=[] refs=[] strings=[]
M046 +0450 n=3 calls=[] refs=[] strings=[]
M047 +045c n=5 calls=[] refs=[] strings=[]
M048 +0470 n=3 calls=[] refs=[] strings=[]
M049 +047c n=3 calls=[] refs=[] strings=[]
M050 +0488 n=3 calls=[] refs=[] strings=[]
M051 +0494 n=3 calls=[] refs=[] strings=[]
M052 +04a0 n=6 calls=['Zi8LangSupported'] refs=[] strings=[]
M053 +04b8 n=7 calls=[] refs=[] strings=[]
M054 +04d4 n=3 calls=[] refs=[] strings=[]
M055 +04e0 n=3 calls=[] refs=[] strings=[]
M056 +04ec n=4 calls=[] refs=[] strings=[]
M057 +04fc n=4 calls=[] refs=[] strings=[]
M058 +050c n=25 calls=['Zi8MatchROMdata'] refs=[] strings=[]
M059 +0570 n=3 calls=[] refs=[] strings=[]
M060 +057c n=23 calls=['Zi8MatchROMdata'] refs=[] strings=[]
M061 +05d8 n=6 calls=[] refs=[] strings=[]
M062 +05f0 n=2 calls=[] refs=[] strings=[]
M063 +05f8 n=3 calls=[] refs=[] strings=[]
M064 +0604 n=3 calls=[] refs=[] strings=[]
M065 +0610 n=3 calls=[] refs=[] strings=[]
M066 +061c n=3 calls=[] refs=[] strings=[]
M067 +0628 n=7 calls=[] refs=[] strings=[]
M068 +0644 n=7 calls=[] refs=[] strings=[]
M069 +0660 n=7 calls=[] refs=[] strings=[]
M070 +067c n=3 calls=[] refs=[] strings=[]
M071 +0688 n=2 calls=[] refs=[] strings=[]
M072 +0690 n=3 calls=[] refs=[] strings=[]
M073 +069c n=3 calls=[] refs=[] strings=[]
M074 +06a8 n=3 calls=[] refs=[] strings=[]
M075 +06b4 n=10 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
M076 +06dc n=4 calls=[] refs=[] strings=[]
M077 +06ec n=4 calls=[] refs=[] strings=[]
M078 +06fc n=4 calls=[] refs=[] strings=[]
M079 +070c n=3 calls=[] refs=[] strings=[]
M080 +0718 n=7 calls=[] refs=[] strings=[]
M081 +0734 n=2 calls=[] refs=[] strings=[]
M082 +073c n=7 calls=[] refs=[] strings=[]
M083 +0758 n=3 calls=[] refs=[] strings=[]
M084 +0764 n=8 calls=[] refs=[] strings=[]
M085 +0784 n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
M086 +07a8 n=3 calls=[] refs=[] strings=[]
M087 +07b4 n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
M088 +07d8 n=3 calls=[] refs=[] strings=[]
M089 +07e4 n=5 calls=[] refs=[] strings=[]
M090 +07f8 n=4 calls=[] refs=[] strings=[]
M091 +0808 n=4 calls=[] refs=[] strings=[]
M092 +0818 n=4 calls=[] refs=[] strings=[]
M093 +0828 n=7 calls=[] refs=[] strings=[]
M094 +0844 n=4 calls=[] refs=[] strings=[]
M095 +0854 n=3 calls=[] refs=[] strings=[]
M096 +0860 n=2 calls=[] refs=[] strings=[]
M097 +0868 n=3 calls=[] refs=[] strings=[]
M098 +0874 n=2 calls=[] refs=[] strings=[]
M099 +087c n=3 calls=[] refs=[] strings=[]
M100 +0888 n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
M101 +08ac n=2 calls=[] refs=[] strings=[]
M102 +08b4 n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
M103 +08d8 n=3 calls=[] refs=[] strings=[]
M104 +08e4 n=4 calls=[] refs=[] strings=[]
M105 +08f4 n=7 calls=['Zi8InitDupWordBuf'] refs=[] strings=[]
M106 +0910 n=3 calls=[] refs=[] strings=[]
M107 +091c n=3 calls=[] refs=[] strings=[]
M108 +0928 n=4 calls=[] refs=[] strings=[]
M109 +0938 n=3 calls=[] refs=[] strings=[]
M110 +0944 n=7 calls=[] refs=[] strings=[]
M111 +0960 n=9 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
M112 +0984 n=3 calls=[] refs=[] strings=[]
M113 +0990 n=11 calls=[] refs=[] strings=[]
M114 +09bc n=10 calls=[] refs=[] strings=[]
M115 +09e4 n=5 calls=[] refs=[] strings=[]
M116 +09f8 n=13 calls=[] refs=[] strings=[]
M117 +0a2c n=2 calls=[] refs=[] strings=[]
M118 +0a34 n=4 calls=[] refs=[] strings=[]
M119 +0a44 n=3 calls=[] refs=[] strings=[]
M120 +0a50 n=3 calls=[] refs=[] strings=[]
M121 +0a5c n=2 calls=[] refs=[] strings=[]
M122 +0a64 n=4 calls=[] refs=[] strings=[]
M123 +0a74 n=1 calls=[] refs=[] strings=[]
M124 +0a78 n=2 calls=[] refs=[] strings=[]
M125 +0a80 n=1 calls=[] refs=[] strings=[]
M126 +0a84 n=1 calls=[] refs=[] strings=[]
M127 +0a88 n=3 calls=[] refs=[] strings=[]
M128 +0a94 n=3 calls=[] refs=[] strings=[]
M129 +0aa0 n=7 calls=[] refs=[] strings=[]
M130 +0abc n=5 calls=[] refs=[] strings=[]
M131 +0ad0 n=3 calls=[] refs=[] strings=[]
M132 +0adc n=2 calls=[] refs=[] strings=[]
M133 +0ae4 n=3 calls=[] refs=[] strings=[]
M134 +0af0 n=3 calls=[] refs=[] strings=[]
M135 +0afc n=8 calls=['Zi8IsDupWordW'] refs=[] strings=[]
M136 +0b1c n=3 calls=[] refs=[] strings=[]
M137 +0b28 n=4 calls=[] refs=[] strings=[]
M138 +0b38 n=5 calls=[] refs=[] strings=[]
M139 +0b4c n=3 calls=[] refs=[] strings=[]
M140 +0b58 n=2 calls=[] refs=[] strings=[]
M141 +0b60 n=7 calls=[] refs=[] strings=[]
M142 +0b7c n=5 calls=[] refs=[] strings=[]
M143 +0b90 n=1 calls=[] refs=[] strings=[]
M144 +0b94 n=9 calls=[] refs=[] strings=[]
M145 +0bb8 n=3 calls=[] refs=[] strings=[]
M146 +0bc4 n=5 calls=['Zi8ChangeWordCase'] refs=[] strings=[]
M147 +0bd8 n=4 calls=['Zi8ChangeWordCase'] refs=[] strings=[]
M148 +0be8 n=14 calls=[] refs=[] strings=[]
M149 +0c20 n=4 calls=[] refs=[] strings=[]
M150 +0c30 n=3 calls=[] refs=[] strings=[]
M151 +0c3c n=3 calls=[] refs=[] strings=[]
M152 +0c48 n=3 calls=[] refs=[] strings=[]
M153 +0c54 n=22 calls=[] refs=[] strings=[]
M154 +0cac n=3 calls=[] refs=[] strings=[]
M155 +0cb8 n=5 calls=[] refs=[] strings=[]
M156 +0ccc n=10 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
M157 +0cf4 n=5 calls=[] refs=[] strings=[]
M158 +0d08 n=5 calls=[] refs=[] strings=[]
M159 +0d1c n=2 calls=[] refs=[] strings=[]
M160 +0d24 n=3 calls=[] refs=[] strings=[]
M161 +0d30 n=5 calls=[] refs=[] strings=[]
M162 +0d44 n=10 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
M163 +0d6c n=5 calls=[] refs=[] strings=[]
M164 +0d80 n=4 calls=[] refs=[] strings=[]
M165 +0d90 n=11 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
M166 +0dbc n=3 calls=[] refs=[] strings=[]
M167 +0dc8 n=4 calls=[] refs=[] strings=[]
M168 +0dd8 n=3 calls=[] refs=[] strings=[]
M169 +0de4 n=4 calls=[] refs=[] strings=[]
M170 +0df4 n=3 calls=[] refs=[] strings=[]
M171 +0e00 n=5 calls=[] refs=[] strings=[]
M172 +0e14 n=3 calls=[] refs=[] strings=[]
M173 +0e20 n=15 calls=['Zi8GetTableCount'] refs=[] strings=[]
M174 +0e5c n=3 calls=[] refs=[] strings=[]
M175 +0e68 n=3 calls=[] refs=[] strings=[]
M176 +0e74 n=3 calls=[] refs=[] strings=[]
M177 +0e80 n=3 calls=[] refs=[] strings=[]
M178 +0e8c n=3 calls=[] refs=[] strings=[]
M179 +0e98 n=3 calls=[] refs=[] strings=[]
M180 +0ea4 n=3 calls=[] refs=[] strings=[]
M181 +0eb0 n=2 calls=[] refs=[] strings=[]
M182 +0eb8 n=3 calls=[] refs=[] strings=[]
M183 +0ec4 n=5 calls=[] refs=[] strings=[]
M184 +0ed8 n=4 calls=[] refs=[] strings=[]
M185 +0ee8 n=3 calls=[] refs=[] strings=[]
M186 +0ef4 n=2 calls=[] refs=[] strings=[]
M187 +0efc n=5 calls=[] refs=[] strings=[]
M188 +0f10 n=2 calls=[] refs=[] strings=[]
M189 +0f18 n=2 calls=[] refs=[] strings=[]
M190 +0f20 n=13 calls=[] refs=[] strings=[]
M191 +0f54 n=11 calls=['Zi8ConvertWC2Key'] refs=[] strings=[]
M192 +0f80 n=1 calls=[] refs=[] strings=[]
M193 +0f84 n=3 calls=[] refs=[] strings=[]
M194 +0f90 n=21 calls=[] refs=[] strings=[]
M195 +0fe4 n=2 calls=[] refs=[] strings=[]
M196 +0fec n=13 calls=[] refs=[] strings=[]
M197 +1020 n=11 calls=['Zi8ConvertWC2Key'] refs=[] strings=[]
M198 +104c n=1 calls=[] refs=[] strings=[]
M199 +1050 n=3 calls=[] refs=[] strings=[]
M200 +105c n=20 calls=[] refs=[] strings=[]
M201 +10ac n=3 calls=[] refs=[] strings=[]
M202 +10b8 n=3 calls=[] refs=[] strings=[]
M203 +10c4 n=2 calls=[] refs=[] strings=[]
M204 +10cc n=12 calls=['Zi8GetTableCount'] refs=[] strings=[]
M205 +10fc n=3 calls=[] refs=[] strings=[]
M206 +1108 n=3 calls=[] refs=[] strings=[]
M207 +1114 n=7 calls=[] refs=[] strings=[]
M208 +1130 n=7 calls=[] refs=[] strings=[]
M209 +114c n=11 calls=['Zi8ConvertWC2Key'] refs=[] strings=[]
M210 +1178 n=3 calls=[] refs=[] strings=[]
M211 +1184 n=5 calls=[] refs=[] strings=[]
M212 +1198 n=3 calls=[] refs=[] strings=[]
M213 +11a4 n=4 calls=[] refs=[] strings=[]
M214 +11b4 n=6 calls=[] refs=[] strings=[]
M215 +11cc n=1 calls=[] refs=[] strings=[]
M216 +11d0 n=2 calls=[] refs=[] strings=[]
M217 +11d8 n=1 calls=[] refs=[] strings=[]
M218 +11dc n=2 calls=[] refs=[] strings=[]
M219 +11e4 n=1 calls=[] refs=[] strings=[]
M220 +11e8 n=2 calls=[] refs=[] strings=[]
M221 +11f0 n=1 calls=[] refs=[] strings=[]
M222 +11f4 n=2 calls=[] refs=[] strings=[]
M223 +11fc n=2 calls=[] refs=[] strings=[]
M224 +1204 n=3 calls=[] refs=[] strings=[]
M225 +1210 n=3 calls=[] refs=[] strings=[]
M226 +121c n=1 calls=[] refs=[] strings=[]
M227 +1220 n=2 calls=[] refs=[] strings=[]
M228 +1228 n=11 calls=['Zi8GetTableCount'] refs=[] strings=[]
M229 +1254 n=3 calls=[] refs=[] strings=[]
M230 +1260 n=2 calls=[] refs=[] strings=[]
M231 +1268 n=5 calls=[] refs=[] strings=[]
M232 +127c n=3 calls=[] refs=[] strings=[]
M233 +1288 n=5 calls=[] refs=[] strings=[]
M234 +129c n=1 calls=[] refs=[] strings=[]
M235 +12a0 n=1 calls=[] refs=[] strings=[]
M236 +12a4 n=3 calls=[] refs=[] strings=[]
M237 +12b0 n=5 calls=[] refs=[] strings=[]
M238 +12c4 n=2 calls=[] refs=[] strings=[]
M239 +12cc n=3 calls=[] refs=[] strings=[]
M240 +12d8 n=3 calls=[] refs=[] strings=[]
M241 +12e4 n=3 calls=[] refs=[] strings=[]
M242 +12f0 n=3 calls=[] refs=[] strings=[]
M243 +12fc n=3 calls=[] refs=[] strings=[]
M244 +1308 n=4 calls=[] refs=[] strings=[]
M245 +1318 n=3 calls=[] refs=[] strings=[]
M246 +1324 n=12 calls=['Zi8getKeyLayout'] refs=[] strings=[]
M247 +1354 n=3 calls=[] refs=[] strings=[]
M248 +1360 n=2 calls=[] refs=[] strings=[]
M249 +1368 n=12 calls=['Zi8GetTableCount'] refs=[] strings=[]
M250 +1398 n=2 calls=[] refs=[] strings=[]
M251 +13a0 n=3 calls=[] refs=[] strings=[]
M252 +13ac n=7 calls=['Zi8GetTableAddress'] refs=[] strings=[]
M253 +13c8 n=3 calls=[] refs=[] strings=[]
M254 +13d4 n=3 calls=[] refs=[] strings=[]
M255 +13e0 n=3 calls=[] refs=[] strings=[]
M256 +13ec n=7 calls=[] refs=[] strings=[]
M257 +1408 n=4 calls=['Zi8Memset'] refs=[] strings=[]
M258 +1418 n=4 calls=[] refs=[] strings=[]
M259 +1428 n=7 calls=[] refs=[] strings=[]
M260 +1444 n=3 calls=[] refs=[] strings=[]
M261 +1450 n=1 calls=[] refs=[] strings=[]
M262 +1454 n=3 calls=[] refs=[] strings=[]
M263 +1460 n=2 calls=[] refs=[] strings=[]
M264 +1468 n=3 calls=[] refs=[] strings=[]
M265 +1474 n=3 calls=[] refs=[] strings=[]
M266 +1480 n=1 calls=[] refs=[] strings=[]
M267 +1484 n=2 calls=[] refs=[] strings=[]
M268 +148c n=2 calls=[] refs=[] strings=[]
M269 +1494 n=1 calls=[] refs=[] strings=[]
M270 +1498 n=5 calls=[] refs=[] strings=[]
M271 +14ac n=1 calls=[] refs=[] strings=[]
M272 +14b0 n=2 calls=[] refs=[] strings=[]
M273 +14b8 n=2 calls=[] refs=[] strings=[]
M274 +14c0 n=1 calls=[] refs=[] strings=[]
M275 +14c4 n=2 calls=[] refs=[] strings=[]
M276 +14cc n=1 calls=[] refs=[] strings=[]
M277 +14d0 n=2 calls=[] refs=[] strings=[]
M278 +14d8 n=1 calls=[] refs=[] strings=[]
M279 +14dc n=3 calls=[] refs=[] strings=[]
M280 +14e8 n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
M281 +150c n=4 calls=[] refs=[] strings=[]
M282 +151c n=4 calls=[] refs=[] strings=[]
M283 +152c n=10 calls=['Zi8getKeyLayout'] refs=[] strings=[]
M284 +1554 n=3 calls=[] refs=[] strings=[]
M285 +1560 n=3 calls=[] refs=[] strings=[]
M286 +156c n=3 calls=[] refs=[] strings=[]
M287 +1578 n=3 calls=[] refs=[] strings=[]
M288 +1584 n=3 calls=[] refs=[] strings=[]
M289 +1590 n=7 calls=[] refs=[] strings=[]
M290 +15ac n=3 calls=[] refs=[] strings=[]
M291 +15b8 n=3 calls=[] refs=[] strings=[]
M292 +15c4 n=4 calls=[] refs=[] strings=[]
M293 +15d4 n=3 calls=[] refs=[] strings=[]
M294 +15e0 n=3 calls=[] refs=[] strings=[]
M295 +15ec n=7 calls=[] refs=[] strings=[]
M296 +1608 n=3 calls=[] refs=[] strings=[]
M297 +1614 n=3 calls=[] refs=[] strings=[]
M298 +1620 n=5 calls=[] refs=[] strings=[]
M299 +1634 n=3 calls=[] refs=[] strings=[]
M300 +1640 n=4 calls=[] refs=[] strings=[]
M301 +1650 n=3 calls=[] refs=[] strings=[]
M302 +165c n=3 calls=[] refs=[] strings=[]
M303 +1668 n=3 calls=[] refs=[] strings=[]
M304 +1674 n=7 calls=[] refs=[] strings=[]
M305 +1690 n=3 calls=[] refs=[] strings=[]
M306 +169c n=4 calls=[] refs=[] strings=[]
M307 +16ac n=2 calls=[] refs=[] strings=[]
M308 +16b4 n=2 calls=[] refs=[] strings=[]
M309 +16bc n=3 calls=[] refs=[] strings=[]
M310 +16c8 n=4 calls=[] refs=[] strings=[]
M311 +16d8 n=1 calls=[] refs=[] strings=[]
M312 +16dc n=4 calls=[] refs=[] strings=[]
M313 +16ec n=3 calls=[] refs=[] strings=[]
M314 +16f8 n=1 calls=[] refs=[] strings=[]
M315 +16fc n=3 calls=[] refs=[] strings=[]
M316 +1708 n=4 calls=[] refs=[] strings=[]
M317 +1718 n=4 calls=[] refs=[] strings=[]
M318 +1728 n=3 calls=[] refs=[] strings=[]
M319 +1734 n=3 calls=[] refs=[] strings=[]
M320 +1740 n=3 calls=[] refs=[] strings=[]
M321 +174c n=4 calls=[] refs=[] strings=[]
M322 +175c n=4 calls=[] refs=[] strings=[]
M323 +176c n=3 calls=[] refs=[] strings=[]
M324 +1778 n=5 calls=[] refs=[] strings=[]
M325 +178c n=3 calls=[] refs=[] strings=[]
M326 +1798 n=4 calls=[] refs=[] strings=[]
M327 +17a8 n=4 calls=[] refs=[] strings=[]
M328 +17b8 n=4 calls=[] refs=[] strings=[]
M329 +17c8 n=4 calls=[] refs=[] strings=[]
M330 +17d8 n=3 calls=[] refs=[] strings=[]
M331 +17e4 n=1 calls=[] refs=[] strings=[]
M332 +17e8 n=3 calls=[] refs=[] strings=[]
M333 +17f4 n=3 calls=[] refs=[] strings=[]
M334 +1800 n=27 calls=[] refs=[] strings=[]
M335 +186c n=3 calls=[] refs=[] strings=[]
M336 +1878 n=6 calls=[] refs=[] strings=[]
M337 +1890 n=7 calls=[] refs=[] strings=[]
M338 +18ac n=6 calls=[] refs=[('@1526', 0), ('@1526', 0)] strings=[]
M339 +18c4 n=2 calls=[] refs=[] strings=[]
M340 +18cc n=3 calls=[] refs=[] strings=[]
M341 +18d8 n=3 calls=[] refs=[] strings=[]
M342 +18e4 n=3 calls=[] refs=[] strings=[]
M343 +18f0 n=3 calls=[] refs=[] strings=[]
M344 +18fc n=5 calls=[] refs=[] strings=[]
M345 +1910 n=5 calls=[] refs=[] strings=[]
M346 +1924 n=7 calls=[] refs=[] strings=[]
M347 +1940 n=3 calls=[] refs=[] strings=[]
M348 +194c n=3 calls=[] refs=[] strings=[]
M349 +1958 n=23 calls=['Zi8MatchROMdata'] refs=[] strings=[]
M350 +19b4 n=3 calls=[] refs=[] strings=[]
M351 +19c0 n=3 calls=[] refs=[] strings=[]
M352 +19cc n=6 calls=[] refs=[] strings=[]
M353 +19e4 n=3 calls=[] refs=[] strings=[]
M354 +19f0 n=23 calls=['Zi8MatchROMdata'] refs=[] strings=[]
M355 +1a4c n=20 calls=['Zi8MatchROMdata'] refs=[] strings=[]
M356 +1a9c n=3 calls=[] refs=[] strings=[]
M357 +1aa8 n=4 calls=[] refs=[] strings=[]
M358 +1ab8 n=2 calls=[] refs=[] strings=[]
M359 +1ac0 n=3 calls=[] refs=[] strings=[]
M360 +1acc n=4 calls=[] refs=[] strings=[]
M361 +1adc n=3 calls=[] refs=[] strings=[]
M362 +1ae8 n=3 calls=[] refs=[] strings=[]
M363 +1af4 n=3 calls=[] refs=[] strings=[]
M364 +1b00 n=12 calls=[] refs=[] strings=[]
M365 +1b30 n=3 calls=[] refs=[] strings=[]
M366 +1b3c n=3 calls=[] refs=[] strings=[]
M367 +1b48 n=4 calls=[] refs=[] strings=[]
M368 +1b58 n=3 calls=[] refs=[] strings=[]
M369 +1b64 n=11 calls=['Zi8ITspecialExclusion'] refs=[] strings=[]
M370 +1b90 n=3 calls=[] refs=[] strings=[]
M371 +1b9c n=3 calls=[] refs=[] strings=[]
M372 +1ba8 n=11 calls=['Zi8_814659E8'] refs=[] strings=[]
M373 +1bd4 n=3 calls=[] refs=[] strings=[]
M374 +1be0 n=8 calls=['Zi8IsVowel'] refs=[] strings=[]
M375 +1c00 n=2 calls=[] refs=[] strings=[]
M376 +1c08 n=3 calls=[] refs=[] strings=[]
M377 +1c14 n=11 calls=[] refs=[] strings=[]
M378 +1c40 n=1 calls=[] refs=[] strings=[]
M379 +1c44 n=3 calls=[] refs=[] strings=[]
M380 +1c50 n=3 calls=[] refs=[] strings=[]
M381 +1c5c n=3 calls=[] refs=[] strings=[]
M382 +1c68 n=3 calls=[] refs=[] strings=[]
M383 +1c74 n=3 calls=[] refs=[] strings=[]
M384 +1c80 n=3 calls=[] refs=[] strings=[]
M385 +1c8c n=3 calls=[] refs=[] strings=[]
M386 +1c98 n=3 calls=[] refs=[] strings=[]
M387 +1ca4 n=3 calls=[] refs=[] strings=[]
M388 +1cb0 n=3 calls=[] refs=[] strings=[]
M389 +1cbc n=7 calls=['Zi8ITspecialExclusion'] refs=[] strings=[]
M390 +1cd8 n=3 calls=[] refs=[] strings=[]
M391 +1ce4 n=3 calls=[] refs=[] strings=[]
M392 +1cf0 n=7 calls=['Zi8_814659E8'] refs=[] strings=[]
M393 +1d0c n=3 calls=[] refs=[] strings=[]
M394 +1d18 n=6 calls=['Zi8IsVowel'] refs=[] strings=[]
M395 +1d30 n=2 calls=[] refs=[] strings=[]
M396 +1d38 n=3 calls=[] refs=[] strings=[]
M397 +1d44 n=8 calls=[] refs=[] strings=[]
M398 +1d64 n=3 calls=[] refs=[] strings=[]
M399 +1d70 n=5 calls=[] refs=[] strings=[]
M400 +1d84 n=3 calls=[] refs=[] strings=[]
M401 +1d90 n=2 calls=[] refs=[] strings=[]
M402 +1d98 n=7 calls=['Zi8IsZicorpSignature'] refs=[] strings=[]
M403 +1db4 n=3 calls=[] refs=[] strings=[]
M404 +1dc0 n=19 calls=['Zi8MatchPUDdata'] refs=[] strings=[]
M405 +1e0c n=25 calls=['Zi8MatchUWDdata'] refs=[] strings=[]
M406 +1e70 n=3 calls=[] refs=[] strings=[]
M407 +1e7c n=3 calls=[] refs=[] strings=[]
M408 +1e88 n=6 calls=[] refs=[] strings=[]
M409 +1ea0 n=3 calls=[] refs=[] strings=[]
M410 +1eac n=19 calls=['Zi8MatchOEMdata'] refs=[] strings=[]
M411 +1ef8 n=6 calls=[] refs=[] strings=[]
M412 +1f10 n=6 calls=[] refs=[] strings=[]
M413 +1f28 n=3 calls=[] refs=[] strings=[]
M414 +1f34 n=3 calls=[] refs=[] strings=[]
M415 +1f40 n=3 calls=[] refs=[] strings=[]
M416 +1f4c n=2 calls=[] refs=[] strings=[]
M417 +1f54 n=9 calls=[] refs=[] strings=[]
M418 +1f78 n=1 calls=[] refs=[] strings=[]
M419 +1f7c n=4 calls=[] refs=[] strings=[]
M420 +1f8c n=4 calls=[] refs=[] strings=[]
M421 +1f9c n=3 calls=[] refs=[] strings=[]
M422 +1fa8 n=2 calls=[] refs=[] strings=[]
M423 +1fb0 n=9 calls=[] refs=[] strings=[]
M424 +1fd4 n=1 calls=[] refs=[] strings=[]
M425 +1fd8 n=3 calls=[] refs=[] strings=[]
M426 +1fe4 n=3 calls=[] refs=[] strings=[]
M427 +1ff0 n=3 calls=[] refs=[] strings=[]
M428 +1ffc n=9 calls=[] refs=[] strings=[]
M429 +2020 n=5 calls=[] refs=[] strings=[]
M430 +2034 n=2 calls=[] refs=[] strings=[]
M431 +203c n=8 calls=[] refs=[] strings=[]
M432 +205c n=8 calls=[] refs=[] strings=[]
M433 +207c n=3 calls=[] refs=[] strings=[]
M434 +2088 n=3 calls=[] refs=[] strings=[]
M435 +2094 n=5 calls=[] refs=[] strings=[]
M436 +20a8 n=7 calls=[] refs=[] strings=[]
M437 +20c4 n=3 calls=[] refs=[] strings=[]
M438 +20d0 n=5 calls=[] refs=[] strings=[]
M439 +20e4 n=3 calls=[] refs=[] strings=[]
M440 +20f0 n=5 calls=[] refs=[] strings=[]
M441 +2104 n=3 calls=[] refs=[] strings=[]
M442 +2110 n=3 calls=[] refs=[] strings=[]
M443 +211c n=3 calls=[] refs=[] strings=[]
M444 +2128 n=3 calls=[] refs=[] strings=[]
M445 +2134 n=4 calls=[] refs=[] strings=[]
M446 +2144 n=3 calls=[] refs=[] strings=[]
M447 +2150 n=6 calls=[] refs=[] strings=[]
M448 +2168 n=5 calls=[] refs=[] strings=[]
M449 +217c n=6 calls=[] refs=[] strings=[]
M450 +2194 n=2 calls=[] refs=[] strings=[]
M451 +219c n=2 calls=[] refs=[] strings=[]
M452 +21a4 n=2 calls=[] refs=[] strings=[]
M453 +21ac n=12 calls=['Zi8getKeyLayout'] refs=[] strings=[]
M454 +21dc n=2 calls=[] refs=[] strings=[]
M455 +21e4 n=7 calls=[] refs=[] strings=[]
M456 +2200 n=3 calls=[] refs=[] strings=[]
M457 +220c n=3 calls=[] refs=[] strings=[]
M458 +2218 n=3 calls=[] refs=[] strings=[]
M459 +2224 n=3 calls=[] refs=[] strings=[]
M460 +2230 n=4 calls=[] refs=[] strings=[]
M461 +2240 n=3 calls=[] refs=[] strings=[]
M462 +224c n=3 calls=[] refs=[] strings=[]
M463 +2258 n=7 calls=[] refs=[] strings=[]
M464 +2274 n=5 calls=[] refs=[] strings=[]
M465 +2288 n=3 calls=[] refs=[] strings=[]
M466 +2294 n=3 calls=[] refs=[] strings=[]
M467 +22a0 n=6 calls=[] refs=[] strings=[]
M468 +22b8 n=3 calls=[] refs=[] strings=[]
M469 +22c4 n=6 calls=[] refs=[] strings=[]
M470 +22dc n=2 calls=[] refs=[] strings=[]
M471 +22e4 n=2 calls=[] refs=[] strings=[]
M472 +22ec n=2 calls=[] refs=[] strings=[]
M473 +22f4 n=12 calls=['Zi8getKeyLayout'] refs=[] strings=[]
M474 +2324 n=2 calls=[] refs=[] strings=[]
M475 +232c n=5 calls=[] refs=[] strings=[]
M476 +2340 n=4 calls=[] refs=[] strings=[]
M477 +2350 n=3 calls=[] refs=[] strings=[]
M478 +235c n=3 calls=[] refs=[] strings=[]
M479 +2368 n=3 calls=[] refs=[] strings=[]
M480 +2374 n=3 calls=[] refs=[] strings=[]
M481 +2380 n=8 calls=['Zi8ITspecialExclusion'] refs=[] strings=[]
M482 +23a0 n=1 calls=[] refs=[] strings=[]
M483 +23a4 n=3 calls=[] refs=[] strings=[]
M484 +23b0 n=7 calls=['Zi8_814659E8'] refs=[] strings=[]
M485 +23cc n=1 calls=[] refs=[] strings=[]
M486 +23d0 n=7 calls=['Zi8IsVowel'] refs=[] strings=[]
M487 +23ec n=3 calls=[] refs=[] strings=[]
M488 +23f8 n=3 calls=[] refs=[] strings=[]
M489 +2404 n=3 calls=[] refs=[] strings=[]
M490 +2410 n=3 calls=[] refs=[] strings=[]
M491 +241c n=3 calls=[] refs=[] strings=[]
M492 +2428 n=3 calls=[] refs=[] strings=[]
M493 +2434 n=7 calls=[] refs=[] strings=[]
M494 +2450 n=3 calls=[] refs=[] strings=[]
M495 +245c n=4 calls=[] refs=[] strings=[]
M496 +246c n=6 calls=[] refs=[] strings=[]
M497 +2484 n=13 calls=['Zi8DeTokenization'] refs=[] strings=[]
M498 +24b8 n=5 calls=[] refs=[] strings=[]
M499 +24cc n=6 calls=[] refs=[] strings=[]
M500 +24e4 n=6 calls=[] refs=[] strings=[]
M501 +24fc n=7 calls=[] refs=[] strings=[]
M502 +2518 n=3 calls=[] refs=[] strings=[]
M503 +2524 n=8 calls=['Zi8ZHCheckSpelling'] refs=[] strings=[]
M504 +2544 n=3 calls=[] refs=[] strings=[]
M505 +2550 n=3 calls=[] refs=[] strings=[]
M506 +255c n=3 calls=[] refs=[] strings=[]
M507 +2568 n=6 calls=['Zi8ChangeWordCase'] refs=[] strings=[]
M508 +2580 n=3 calls=[] refs=[] strings=[]
M509 +258c n=6 calls=[] refs=[] strings=[]
M510 +25a4 n=8 calls=[] refs=[] strings=[]
M511 +25c4 n=6 calls=[] refs=[] strings=[]
M512 +25dc n=13 calls=['Zi8IsDupWordW'] refs=[] strings=[]
M513 +2610 n=3 calls=[] refs=[] strings=[]
M514 +261c n=4 calls=[] refs=[] strings=[]
M515 +262c n=1 calls=[] refs=[] strings=[]
M516 +2630 n=3 calls=[] refs=[] strings=[]
M517 +263c n=3 calls=[] refs=[] strings=[]
M518 +2648 n=5 calls=[] refs=[] strings=[]
M519 +265c n=5 calls=[] refs=[] strings=[]
M520 +2670 n=3 calls=[] refs=[] strings=[]
M521 +267c n=1 calls=[] refs=[] strings=[]
M522 +2680 n=2 calls=[] refs=[] strings=[]
M523 +2688 n=1 calls=[] refs=[] strings=[]
M524 +268c n=2 calls=[] refs=[] strings=[]
M525 +2694 n=1 calls=[] refs=[] strings=[]
M526 +2698 n=9 calls=[] refs=[] strings=[]
M527 +26bc n=6 calls=[] refs=[] strings=[]
M528 +26d4 n=9 calls=[] refs=[] strings=[]
M529 +26f8 n=2 calls=[] refs=[] strings=[]
M530 +2700 n=7 calls=[] refs=[] strings=[]
M531 +271c n=3 calls=[] refs=[] strings=[]
M532 +2728 n=3 calls=[] refs=[] strings=[]
M533 +2734 n=3 calls=[] refs=[] strings=[]
M534 +2740 n=14 calls=['Zi8ConvertWC2UC'] refs=[] strings=[]
M535 +2778 n=4 calls=[] refs=[] strings=[]
M536 +2788 n=1 calls=[] refs=[] strings=[]
M537 +278c n=3 calls=[] refs=[] strings=[]
M538 +2798 n=3 calls=[] refs=[] strings=[]
M539 +27a4 n=4 calls=[] refs=[] strings=[]
M540 +27b4 n=9 calls=[] refs=[] strings=[]
M541 +27d8 n=4 calls=[] refs=[] strings=[]
M542 +27e8 n=6 calls=[] refs=[] strings=[]
M543 +2800 n=12 calls=[] refs=[] strings=[]
M544 +2830 n=1 calls=[] refs=[] strings=[]
M545 +2834 n=3 calls=[] refs=[] strings=[]
M546 +2840 n=3 calls=[] refs=[] strings=[]
M547 +284c n=3 calls=[] refs=[] strings=[]
M548 +2858 n=3 calls=[] refs=[] strings=[]
M549 +2864 n=6 calls=[] refs=[] strings=[]
M550 +287c n=5 calls=[] refs=[] strings=[]
M551 +2890 n=6 calls=[] refs=[] strings=[]
M552 +28a8 n=5 calls=[] refs=[] strings=[]
M553 +28bc n=7 calls=[] refs=[] strings=[]
M554 +28d8 n=1 calls=[] refs=[] strings=[]
M555 +28dc n=3 calls=[] refs=[] strings=[]
M556 +28e8 n=2 calls=[] refs=[] strings=[]
M557 +28f0 n=1 calls=[] refs=[] strings=[]
M558 +28f4 n=3 calls=[] refs=[] strings=[]
M559 +2900 n=8 calls=[] refs=[] strings=[]
M560 +2920 n=3 calls=[] refs=[] strings=[]
M561 +292c n=3 calls=[] refs=[] strings=[]
M562 +2938 n=3 calls=[] refs=[] strings=[]
M563 +2944 n=3 calls=[] refs=[] strings=[]
M564 +2950 n=6 calls=['Zi8WCharCount'] refs=[] strings=[]
M565 +2968 n=3 calls=[] refs=[] strings=[]
M566 +2974 n=3 calls=[] refs=[] strings=[]
M567 +2980 n=3 calls=[] refs=[] strings=[]
M568 +298c n=3 calls=[] refs=[] strings=[]
M569 +2998 n=3 calls=[] refs=[] strings=[]
M570 +29a4 n=3 calls=[] refs=[] strings=[]
M571 +29b0 n=3 calls=[] refs=[] strings=[]
M572 +29bc n=3 calls=[] refs=[] strings=[]
M573 +29c8 n=3 calls=[] refs=[] strings=[]
M574 +29d4 n=2 calls=[] refs=[] strings=[]
M575 +29dc n=3 calls=[] refs=[] strings=[]
M576 +29e8 n=5 calls=[] refs=[] strings=[]
M577 +29fc n=3 calls=[] refs=[] strings=[]
M578 +2a08 n=3 calls=[] refs=[] strings=[]
M579 +2a14 n=3 calls=[] refs=[] strings=[]
M580 +2a20 n=3 calls=[] refs=[] strings=[]
M581 +2a2c n=5 calls=[] refs=[] strings=[]
M582 +2a40 n=3 calls=[] refs=[] strings=[]
M583 +2a4c n=3 calls=[] refs=[] strings=[]
M584 +2a58 n=3 calls=[] refs=[] strings=[]
M585 +2a64 n=3 calls=[] refs=[] strings=[]
M586 +2a70 n=2 calls=[] refs=[] strings=[]
M587 +2a78 n=8 calls=[] refs=[] strings=[]
M588 +2a98 n=3 calls=[] refs=[] strings=[]
M589 +2aa4 n=2 calls=[] refs=[] strings=[]
M590 +2aac n=8 calls=[] refs=[] strings=[]
M591 +2acc n=3 calls=[] refs=[] strings=[]
M592 +2ad8 n=6 calls=[] refs=[] strings=[]
M593 +2af0 n=3 calls=[] refs=[] strings=[]
M594 +2afc n=3 calls=[] refs=[] strings=[]
M595 +2b08 n=4 calls=[] refs=[] strings=[]
M596 +2b18 n=3 calls=[] refs=[] strings=[]
M597 +2b24 n=4 calls=[] refs=[] strings=[]
M598 +2b34 n=3 calls=[] refs=[] strings=[]
M599 +2b40 n=4 calls=[] refs=[] strings=[]
M600 +2b50 n=3 calls=[] refs=[] strings=[]
M601 +2b5c n=4 calls=[] refs=[] strings=[]
M602 +2b6c n=3 calls=[] refs=[] strings=[]
M603 +2b78 n=3 calls=[] refs=[] strings=[]
M604 +2b84 n=3 calls=[] refs=[] strings=[]
M605 +2b90 n=2 calls=[] refs=[] strings=[]
M606 +2b98 n=6 calls=[] refs=[] strings=[]
M607 +2bb0 n=3 calls=[] refs=[] strings=[]
M608 +2bbc n=6 calls=[] refs=[] strings=[]
M609 +2bd4 n=3 calls=[] refs=[] strings=[]
M610 +2be0 n=3 calls=[] refs=[] strings=[]
M611 +2bec n=4 calls=[] refs=[] strings=[]
M612 +2bfc n=3 calls=[] refs=[] strings=[]
M613 +2c08 n=4 calls=[] refs=[] strings=[]
M614 +2c18 n=3 calls=[] refs=[] strings=[]
M615 +2c24 n=4 calls=[] refs=[] strings=[]
M616 +2c34 n=3 calls=[] refs=[] strings=[]
M617 +2c40 n=4 calls=[] refs=[] strings=[]
M618 +2c50 n=5 calls=[] refs=[] strings=[]
M619 +2c64 n=3 calls=[] refs=[] strings=[]
M620 +2c70 n=3 calls=[] refs=[] strings=[]
M621 +2c7c n=3 calls=[] refs=[] strings=[]
M622 +2c88 n=4 calls=[] refs=[] strings=[]
M623 +2c98 n=2 calls=[] refs=[] strings=[]
M624 +2ca0 n=6 calls=[] refs=[] strings=[]
M625 +2cb8 n=3 calls=[] refs=[] strings=[]
M626 +2cc4 n=4 calls=[] refs=[] strings=[]
M627 +2cd4 n=2 calls=[] refs=[] strings=[]
M628 +2cdc n=6 calls=[] refs=[] strings=[]
M629 +2cf4 n=3 calls=[] refs=[] strings=[]
M630 +2d00 n=4 calls=[] refs=[] strings=[]
M631 +2d10 n=3 calls=[] refs=[] strings=[]
M632 +2d1c n=3 calls=[] refs=[] strings=[]
M633 +2d28 n=4 calls=[] refs=[] strings=[]
M634 +2d38 n=3 calls=[] refs=[] strings=[]
M635 +2d44 n=4 calls=[] refs=[] strings=[]
M636 +2d54 n=3 calls=[] refs=[] strings=[]
M637 +2d60 n=4 calls=[] refs=[] strings=[]
M638 +2d70 n=3 calls=[] refs=[] strings=[]
M639 +2d7c n=4 calls=[] refs=[] strings=[]
M640 +2d8c n=5 calls=[] refs=[] strings=[]
M641 +2da0 n=3 calls=[] refs=[] strings=[]
M642 +2dac n=3 calls=[] refs=[] strings=[]
M643 +2db8 n=3 calls=[] refs=[] strings=[]
M644 +2dc4 n=2 calls=[] refs=[] strings=[]
M645 +2dcc n=6 calls=[] refs=[] strings=[]
M646 +2de4 n=3 calls=[] refs=[] strings=[]
M647 +2df0 n=2 calls=[] refs=[] strings=[]
M648 +2df8 n=7 calls=[] refs=[] strings=[]
M649 +2e14 n=3 calls=[] refs=[] strings=[]
M650 +2e20 n=2 calls=[] refs=[] strings=[]
M651 +2e28 n=2 calls=[] refs=[] strings=[]
M652 +2e30 n=11 calls=['Zi8ConvertWC2UC'] refs=[] strings=[]
M653 +2e5c n=5 calls=[] refs=[] strings=[]
M654 +2e70 n=7 calls=[] refs=[] strings=[]
M655 +2e8c n=3 calls=[] refs=[] strings=[]
M656 +2e98 n=13 calls=[] refs=[] strings=[]
M657 +2ecc n=7 calls=[] refs=[] strings=[]
M658 +2ee8 n=5 calls=[] refs=[] strings=[]
M659 +2efc n=1 calls=[] refs=[] strings=[]
M660 +2f00 n=11 calls=[] refs=[] strings=[]
M661 +2f2c n=7 calls=[] refs=[] strings=[]
M662 +2f48 n=3 calls=[] refs=[] strings=[]
M663 +2f54 n=8 calls=[] refs=[] strings=[]
M664 +2f74 n=3 calls=[] refs=[] strings=[]
M665 +2f80 n=3 calls=[] refs=[] strings=[]
M666 +2f8c n=3 calls=[] refs=[] strings=[]
M667 +2f98 n=4 calls=[] refs=[] strings=[]
M668 +2fa8 n=3 calls=[] refs=[] strings=[]
M669 +2fb4 n=2 calls=[] refs=[] strings=[]
M670 +2fbc n=6 calls=[] refs=[] strings=[]
M671 +2fd4 n=3 calls=[] refs=[] strings=[]
M672 +2fe0 n=10 calls=[] refs=[] strings=[]
M673 +3008 n=2 calls=[] refs=[] strings=[]
M674 +3010 n=6 calls=[] refs=[] strings=[]
M675 +3028 n=3 calls=[] refs=[] strings=[]
M676 +3034 n=8 calls=[] refs=[] strings=[]
M677 +3054 n=3 calls=[] refs=[] strings=[]
M678 +3060 n=3 calls=[] refs=[] strings=[]
M679 +306c n=3 calls=[] refs=[] strings=[]
M680 +3078 n=4 calls=[] refs=[] strings=[]
M681 +3088 n=3 calls=[] refs=[] strings=[]
M682 +3094 n=3 calls=[] refs=[] strings=[]
M683 +30a0 n=3 calls=[] refs=[] strings=[]
M684 +30ac n=3 calls=[] refs=[] strings=[]
M685 +30b8 n=10 calls=['Zi8GetTableCount'] refs=[] strings=[]
M686 +30e0 n=4 calls=[] refs=[] strings=[]
M687 +30f0 n=4 calls=[] refs=[] strings=[]
M688 +3100 n=11 calls=['Zi8getKeyLayout'] refs=[] strings=[]
M689 +312c n=2 calls=[] refs=[] strings=[]
M690 +3134 n=3 calls=[] refs=[] strings=[]
M691 +3140 n=3 calls=[] refs=[] strings=[]
M692 +314c n=3 calls=[] refs=[] strings=[]
M693 +3158 n=5 calls=[] refs=[] strings=[]
M694 +316c n=4 calls=[] refs=[] strings=[]
M695 +317c n=10 calls=[] refs=[] strings=[]
M696 +31a4 n=3 calls=[] refs=[] strings=[]
M697 +31b0 n=4 calls=[] refs=[] strings=[]
M698 +31c0 n=2 calls=[] refs=[] strings=[]
M699 +31c8 n=5 calls=[] refs=[] strings=[]
M700 +31dc n=3 calls=[] refs=[] strings=[]
M701 +31e8 n=2 calls=[] refs=[] strings=[]
M702 +31f0 n=3 calls=[] refs=[] strings=[]
M703 +31fc n=23 calls=[] refs=[] strings=[]
M704 +3258 n=11 calls=[] refs=[] strings=[]
M705 +3284 n=5 calls=[] refs=[] strings=[]
M706 +3298 n=2 calls=[] refs=[] strings=[]
M707 +32a0 n=9 calls=[] refs=[] strings=[]
M708 +32c4 n=4 calls=[] refs=[] strings=[]
M709 +32d4 n=3 calls=[] refs=[] strings=[]
M710 +32e0 n=3 calls=[] refs=[] strings=[]
M711 +32ec n=3 calls=[] refs=[] strings=[]
M712 +32f8 n=3 calls=[] refs=[] strings=[]
M713 +3304 n=3 calls=[] refs=[] strings=[]
M714 +3310 n=3 calls=[] refs=[] strings=[]
M715 +331c n=7 calls=[] refs=[] strings=[]
M716 +3338 n=5 calls=[] refs=[] strings=[]
M717 +334c n=6 calls=[] refs=[] strings=[]
M718 +3364 n=3 calls=[] refs=[] strings=[]
M719 +3370 n=3 calls=[] refs=[] strings=[]
M720 +337c n=3 calls=[] refs=[] strings=[]
M721 +3388 n=3 calls=[] refs=[] strings=[]
M722 +3394 n=3 calls=[] refs=[] strings=[]
M723 +33a0 n=3 calls=[] refs=[] strings=[]
M724 +33ac n=3 calls=[] refs=[] strings=[]
M725 +33b8 n=7 calls=[] refs=[] strings=[]
M726 +33d4 n=5 calls=[] refs=[] strings=[]
M727 +33e8 n=5 calls=[] refs=[] strings=[]
M728 +33fc n=9 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
M729 +3420 n=3 calls=[] refs=[] strings=[]
M730 +342c n=3 calls=[] refs=[] strings=[]
M731 +3438 n=5 calls=[] refs=[] strings=[]
M732 +344c n=3 calls=[] refs=[] strings=[]
M733 +3458 n=3 calls=[] refs=[] strings=[]
M734 +3464 n=3 calls=[] refs=[] strings=[]
M735 +3470 n=2 calls=[] refs=[] strings=[]
M736 +3478 n=3 calls=[] refs=[] strings=[]
M737 +3484 n=28 calls=[] refs=[] strings=[]
M738 +34f4 n=7 calls=[] refs=[] strings=[]
M739 +3510 n=3 calls=[] refs=[] strings=[]
M740 +351c n=7 calls=[] refs=[] strings=[]
M741 +3538 n=3 calls=[] refs=[] strings=[]
M742 +3544 n=2 calls=[] refs=[] strings=[]
M743 +354c n=2 calls=[] refs=[] strings=[]
M744 +3554 n=3 calls=[] refs=[] strings=[]
M745 +3560 n=3 calls=[] refs=[] strings=[]
M746 +356c n=3 calls=[] refs=[] strings=[]
M747 +3578 n=5 calls=[] refs=[] strings=[]
M748 +358c n=3 calls=[] refs=[] strings=[]
M749 +3598 n=5 calls=[] refs=[] strings=[]
M750 +35ac n=3 calls=[] refs=[] strings=[]
M751 +35b8 n=3 calls=[] refs=[] strings=[]
M752 +35c4 n=1 calls=[] refs=[] strings=[]
M753 +35c8 n=3 calls=[] refs=[] strings=[]
M754 +35d4 n=7 calls=[] refs=[] strings=[]
M755 +35f0 n=3 calls=[] refs=[] strings=[]
M756 +35fc n=3 calls=[] refs=[] strings=[]
M757 +3608 n=9 calls=[] refs=[] strings=[]
M758 +362c n=19 calls=[] refs=[] strings=[]
M759 +3678 n=3 calls=[] refs=[] strings=[]
M760 +3684 n=7 calls=[] refs=[] strings=[]
M761 +36a0 n=4 calls=[] refs=[] strings=[]
M762 +36b0 n=8 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
M763 +36d0 n=3 calls=[] refs=[] strings=[]
M764 +36dc n=11 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
M765 +3708 n=3 calls=[] refs=[] strings=[]
M766 +3714 n=3 calls=[] refs=[] strings=[]
M767 +3720 n=10 calls=['ZiIsLetterHyphen'] refs=[] strings=[]
M768 +3748 n=10 calls=['Zi8GetTableCount'] refs=[] strings=[]
M769 +3770 n=7 calls=[] refs=[] strings=[]
M770 +378c n=3 calls=[] refs=[] strings=[]
M771 +3798 n=18 calls=[] refs=[] strings=[]
M772 +37e0 n=3 calls=[] refs=[] strings=[]
M773 +37ec n=14 calls=[] refs=[] strings=[]
M774 +3824 n=9 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
M775 +3848 n=12 calls=[] refs=[] strings=[]
M776 +3878 n=9 calls=[] refs=[] strings=[]
M777 +389c n=3 calls=[] refs=[] strings=[]
M778 +38a8 n=7 calls=[] refs=[] strings=[]
M779 +38c4 n=4 calls=[] refs=[] strings=[]
M780 +38d4 n=3 calls=[] refs=[] strings=[]
M781 +38e0 n=3 calls=[] refs=[] strings=[]
M782 +38ec n=3 calls=[] refs=[] strings=[]
M783 +38f8 n=3 calls=[] refs=[] strings=[]
M784 +3904 n=9 calls=['Zi8GetTableCount'] refs=[] strings=[]
M785 +3928 n=2 calls=[] refs=[] strings=[]
M786 +3930 n=6 calls=[] refs=[] strings=[]
M787 +3948 n=8 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
M788 +3968 n=12 calls=[] refs=[] strings=[]
M789 +3998 n=9 calls=[] refs=[] strings=[]
M790 +39bc n=3 calls=[] refs=[] strings=[]
M791 +39c8 n=3 calls=[] refs=[] strings=[]
M792 +39d4 n=3 calls=[] refs=[] strings=[]
M793 +39e0 n=3 calls=[] refs=[] strings=[]
M794 +39ec n=3 calls=[] refs=[] strings=[]
M795 +39f8 n=5 calls=[] refs=[] strings=[]
M796 +3a0c n=9 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
M797 +3a30 n=3 calls=[] refs=[] strings=[]
M798 +3a3c n=3 calls=[] refs=[] strings=[]
M799 +3a48 n=3 calls=[] refs=[] strings=[]
M800 +3a54 n=10 calls=['Zi8IsAlphaPunct'] refs=[] strings=[]
M801 +3a7c n=7 calls=[] refs=[] strings=[]
M802 +3a98 n=3 calls=[] refs=[] strings=[]
M803 +3aa4 n=3 calls=[] refs=[] strings=[]
M804 +3ab0 n=5 calls=[] refs=[] strings=[]
M805 +3ac4 n=7 calls=[] refs=[] strings=[]
M806 +3ae0 n=7 calls=[] refs=[] strings=[]
M807 +3afc n=5 calls=[] refs=[] strings=[]
M808 +3b10 n=4 calls=[] refs=[] strings=[]
M809 +3b20 n=2 calls=[] refs=[] strings=[]
M810 +3b28 n=8 calls=[] refs=[] strings=[]
M811 +3b48 n=3 calls=[] refs=[] strings=[]
M812 +3b54 n=3 calls=[] refs=[] strings=[]
M813 +3b60 n=6 calls=[] refs=[] strings=[]
M814 +3b78 n=3 calls=[] refs=[] strings=[]
M815 +3b84 n=3 calls=[] refs=[] strings=[]
M816 +3b90 n=6 calls=[] refs=[] strings=[]
M817 +3ba8 n=2 calls=[] refs=[] strings=[]
M818 +3bb0 n=6 calls=[] refs=[] strings=[]
M819 +3bc8 n=4 calls=[] refs=[] strings=[]
M820 +3bd8 n=3 calls=[] refs=[] strings=[]
M821 +3be4 n=2 calls=[] refs=[] strings=[]
M822 +3bec n=3 calls=[] refs=[] strings=[]
M823 +3bf8 n=3 calls=[] refs=[] strings=[]
M824 +3c04 n=4 calls=[] refs=[] strings=[]
M825 +3c14 n=2 calls=[] refs=[] strings=[]
M826 +3c1c n=3 calls=[] refs=[] strings=[]
M827 +3c28 n=3 calls=[] refs=[] strings=[]
M828 +3c34 n=4 calls=[] refs=[] strings=[]
M829 +3c44 n=2 calls=[] refs=[] strings=[]
M830 +3c4c n=3 calls=[] refs=[] strings=[]
M831 +3c58 n=5 calls=[] refs=[] strings=[]
M832 +3c6c n=9 calls=['Zi8ConvertUC2WC'] refs=[] strings=[]
M833 +3c90 n=4 calls=[] refs=[] strings=[]
M834 +3ca0 n=4 calls=[] refs=[] strings=[]
M835 +3cb0 n=1 calls=[] refs=[] strings=[]
M836 +3cb4 n=2 calls=[] refs=[] strings=[]
M837 +3cbc n=5 calls=['Zi8SetHighlightedWordW'] refs=[] strings=[]
M838 +3cd0 n=3 calls=[] refs=[] strings=[]
M839 +3cdc n=4 calls=[] refs=[] strings=[]
M840 +3cec n=7 calls=[] refs=[] strings=[]
M841 +3d08 n=5 calls=[] refs=[] strings=[]
M842 +3d1c n=6 calls=[] refs=[] strings=[]
M843 +3d34 n=4 calls=[] refs=[] strings=[]
M844 +3d44 n=12 calls=[] refs=[] strings=[]
M845 +3d74 n=3 calls=[] refs=[] strings=[]
M846 +3d80 n=11 calls=['Zi8LogError', '_restgpr_27'] refs=[] strings=[]
ALIGNMENT; each unequal span lists all target/built blocks
replace: T0:1 +95 / M0:1 +94
replace: T42:43 +10 / M42:43 +9
replace: T75:76 +9 / M75:76 +10
replace: T105:106 +5 / M105:106 +7
replace: T116:117 +13 / M116:117 +13
replace: T165:166 +10 / M165:166 +11
replace: T173:174 +16 / M173:174 +15
replace: T209:210 +12 / M209:210 +11
replace: T228:229 +12 / M228:229 +11
replace: T364:365 +11 / M364:365 +12
replace: T372:373 +12 / M372:373 +11
replace: T402:403 +6 / M402:403 +7
replace: T405:406 +26 / M405:406 +25
delete: T450:451 +1 / M450:450 +0
replace: T453:455 +14 / M452:454 +14
replace: T471:475 +6 / M470:473 +6
replace: T492:494 +6 / M490:492 +6
replace: T497:498 +4 / M495:496 +4
replace: T500:501 +6 / M498:499 +5
replace: T511:512 +6 / M509:510 +6
replace: T514:515 +12 / M512:513 +13
replace: T520:521 +5 / M518:519 +5
replace: T529:531 +13 / M527:528 +6
replace: T533:534 +1 / M530:531 +7
delete: T541:542 +9 / M538:538 +0
replace: T543:544 +4 / M539:541 +13
replace: T549:551 +7 / M546:547 +3
replace: T553:554 +6 / M549:550 +6
replace: T557:558 +6 / M553:554 +7
delete: T561:562 +8 / M557:557 +0
replace: T563:564 +3 / M558:560 +11
replace: T565:566 +3 / M561:562 +3
replace: T568:569 +6 / M564:565 +6
replace: T570:571 +3 / M566:567 +3
replace: T576:579 +8 / M572:575 +8
insert: T583:583 +0 / M579:584 +17
insert: T584:584 +0 / M585:586 +3
replace: T590:597 +26 / M592:593 +6
replace: T656:657 +10 / M652:653 +11
replace: T665:666 +6 / M661:662 +7
replace: T680:681 +7 / M676:678 +11
replace: T690:691 +4 / M687:688 +4
replace: T697:698 +4 / M694:696 +14
replace: T701:703 +13 / M699:700 +5
replace: T706:707 +23 / M703:704 +23
replace: T710:712 +10 / M707:708 +9
replace: T732:739 +53 / M728:729 +9
replace: T761:762 +3 / M751:759 +48
replace: T767:768 +10 / M764:765 +11
replace: T777:779 +21 / M774:776 +21
replace: T787:788 +10 / M784:785 +9
replace: T791:792 +13 / M788:789 +12
replace: T799:800 +10 / M796:797 +9
replace: T803:804 +9 / M800:801 +10
replace: T810:813 +11 / M807:810 +11
replace: T818:819 +3 / M815:816 +3
CALL-ALIGNED REGIONS
R001: T[5:222] M[5:221] deficit +1 before Zi8ChangeCharCase
R004: T[265:301] M[264:299] deficit +1 before Zi8LangSupported
R008: T[437:487] M[435:486] deficit -1 before Zi8GetTableCount
R013: T[576:605] M[575:606] deficit -2 before Zi8IsAlphaPunct
R014: T[605:707] M[606:708] deficit +0 before Zi8IsDupWordW
R020: T[874:910] M[875:911] deficit +0 before Zi8GetTableCount
R025: T[1114:1169] M[1115:1169] deficit +1 before Zi8GetTableCount
R026: T[1169:1235] M[1169:1234] deficit +1 before Zi8getKeyLayout
R035: T[1702:1761] M[1701:1761] deficit -1 before Zi8ITspecialExclusion
R037: T[1778:1790] M[1778:1789] deficit +1 before Zi8IsVowel
R042: T[1900:1920] M[1899:1920] deficit -1 before Zi8MatchPUDdata
R044: T[1943:1980] M[1943:1979] deficit +1 before Zi8MatchOEMdata
R045: T[1980:2165] M[1979:2164] deficit +0 before Zi8getKeyLayout
R046: T[2165:2248] M[2164:2246] deficit +1 before Zi8getKeyLayout
R050: T[2297:2347] M[2295:2345] deficit +0 before Zi8DeTokenization
R051: T[2347:2385] M[2345:2382] deficit +1 before Zi8ZHCheckSpelling
R053: T[2403:2435] M[2400:2432] deficit +0 before Zi8IsDupWordW
R054: T[2435:2523] M[2432:2520] deficit +0 before Zi8ConvertWC2UC
R055: T[2523:2653] M[2520:2647] deficit +3 before Zi8WCharCount
R056: T[2653:2969] M[2647:2963] deficit +0 before Zi8ConvertWC2UC
R057: T[2969:3123] M[2963:3123] deficit -6 before Zi8GetTableCount
R058: T[3123:3144] M[3123:3144] deficit +0 before Zi8getKeyLayout
R059: T[3144:3332] M[3144:3333] deficit -1 before Zi8IsAlphaPunct
R060: T[3332:3502] M[3333:3504] deficit -1 before ZiIsLetterHyphen
R062: T[3516:3532] M[3518:3535] deficit -1 before ZiIsLetterHyphen
R065: T[3595:3651] M[3598:3654] deficit +0 before Zi8GetTableCount
R066: T[3651:3669] M[3654:3671] deficit +1 before Zi8IsAlphaPunct
R067: T[3669:3720] M[3671:3721] deficit +1 before Zi8IsAlphaPunct
R068: T[3720:3739] M[3721:3739] deficit +1 before Zi8IsAlphaPunct
R069: T[3739:3871] M[3739:3872] deficit -1 before Zi8ConvertUC2WC
```

Target-only opcode spans within each unequal call region:

```text
R001 delete target +0158..+015c (1) vs built [86:86] (0)
  +0158 stw r0, 0x28(r1)
R004 delete target +0424..+0428 (1) vs built [264:264] (0)
  +0424 mr r6, r3
R014 delete target +0a08..+0a0c (1) vs built [643:643] (0)
  +0a08 mr r5, r6
R020 delete target +0e1c..+0e20 (1) vs built [905:905] (0)
  +0e1c clrlwi r0, r4, 24
R025 delete target +1168..+116c (1) vs built [1115:1115] (0)
  +1168 mr r7, r3
R026 delete target +1244..+1248 (1) vs built [1169:1169] (0)
  +1244 mr r0, r3
R037 delete target +1bc8..+1bcc (1) vs built [1778:1778] (0)
  +1bc8 mr r5, r3
R044 delete target +1e5c..+1e60 (1) vs built [1943:1943] (0)
  +1e5c mr r5, r3
R045 replace target +21a8..+21b0 (2) vs built [2154:2155] (1)
  +21a8 bge .L_81467DBC
  +21ac b .L_81467E14
R046 delete target +21d4..+21d8 (1) vs built [2164:2164] (0)
  +21d4 mr r4, r3
R046 delete target +22e4..+22e8 (1) vs built [2231:2231] (0)
  +22e4 bge .L_81468C78
R046 replace target +22ec..+22f0 (1) vs built [2232:2233] (1)
  +22ec bge .L_81468C78
R046 replace target +22f4..+22fc (2) vs built [2234:2237] (3)
  +22f4 bge .L_81467F08
  +22f8 b .L_81468C78
R050 replace target +2420..+2424 (1) vs built [2310:2311] (1)
  +2420 blt .L_81468048
R050 replace target +242c..+2430 (1) vs built [2313:2314] (1)
  +242c bgt .L_81468048
R050 replace target +2470..+2474 (1) vs built [2330:2331] (1)
  +2470 ble .L_81468098
R051 delete target +24c4..+24c8 (1) vs built [2351:2351] (0)
  +24c4 clrlwi r3, r4, 24
R053 delete target +25a4..+25a8 (1) vs built [2407:2407] (0)
  +25a4 lbz r3, 0x1(r27)
R053 replace target +25ac..+25b0 (1) vs built [2408:2409] (1)
  +25ac ble .L_814681DC
R054 replace target +2660..+2664 (1) vs built [2454:2455] (1)
  +2660 ble .L_81468458
R054 replace target +26d8..+26f8 (8) vs built [2484:2485] (1)
  +26d8 bge .L_81468304
  +26dc lwz r5, 0x24(r1)
  +26e0 lwz r4, 0x24(r1)
  +26e4 lbz r0, 0x0(r4)
  +26e8 add r3, r0, r5
  +26ec addi r4, r3, 0x1
  +26f0 stw r4, 0x24(r1)
  +26f4 b .L_81468330
R055 replace target +27c4..+27e4 (8) vs built [2549:2550] (1)
  +27c4 bne .L_814683F0
  +27c8 lwz r6, 0x5c(r1)
  +27cc addi r3, r6, 0x1
  +27d0 stw r3, 0x5c(r1)
  +27d4 lwz r5, 0x5c(r1)
  +27d8 lbz r4, 0x12(r1)
  +27dc cmpw r5, r4
  +27e0 blt .L_814683B0
R055 replace target +2854..+2868 (5) vs built [2578:2579] (1)
  +2854 beq .L_81468474
  +2858 lwz r3, 0x38(r1)
  +285c addi r3, r3, 0x1
  +2860 stw r3, 0x38(r1)
  +2864 b .L_81468C6C
R055 delete target +2880..+2884 (1) vs built [2585:2585] (0)
  +2880 lbz r0, 0x15(r27)
R055 replace target +2894..+2898 (1) vs built [2590:2591] (1)
  +2894 ble .L_814684B8
R055 replace target +28ec..+28f0 (1) vs built [2613:2614] (1)
  +28ec bge .L_81469704
R055 replace target +2924..+2938 (5) vs built [2631:2632] (1)
  +2924 bne .L_81468544
  +2928 addi r29, r29, 0x1
  +292c lwz r4, 0x44(r1)
  +2930 cmpw r29, r4
  +2934 ble .L_81468514
R055 replace target +294c..+2950 (1) vs built [2637:2638] (1)
  +294c blt .L_81468C6C
R056 replace target +297c..+2980 (1) vs built [2649:2650] (1)
  +297c blt .L_81468C6C
R056 replace target +2994..+2998 (1) vs built [2655:2656] (1)
  +2994 blt .L_81468C6C
R056 replace target +29dc..+29e4 (2) vs built [2673:2675] (2)
  +29dc bgt .L_814685F8
  +29e0 li r3, 0x0
R056 replace target +29ec..+29f0 (1) vs built [2677:2678] (1)
  +29ec lhz r4, 0x0(r28)
R056 delete target +2ab4..+2b04 (20) vs built [2747:2747] (0)
  +2ab4 sth r5, 0x1a92(r3)
  +2ab8 b .L_81468714
  +2abc lwz r3, 0x54(r1)
  +2ac0 cmpwi r3, 0x0
  +2ac4 bne .L_81468714
  +2ac8 lbz r0, 0xc(r31)
  +2acc clrlwi r5, r0, 24
  +2ad0 lbz r3, 0x1b14(r30)
  +2ad4 cmplw r5, r3
  +2ad8 bne .L_81468714
  +2adc lbz r3, 0x1c(r31)
  +2ae0 cmplwi r3, 0x1
  +2ae4 beq .L_8146870C
  +2ae8 lwz r3, 0x2c(r1)
  +2aec cmpwi r3, 0x0
  +2af0 bne .L_81468714
  +2af4 lhz r0, 0x1e(r31)
  +2af8 cmpwi r0, 0x0
  +2afc bne .L_81468714
  +2b00 li r3, 0x0
R057 replace target +2f54..+2f58 (1) vs built [3025:3026] (1)
  +2f54 blt .L_81468B70
R058 replace target +30fc..+3100 (1) vs built [3135:3136] (1)
  +30fc bgt .L_81468D40
R059 replace target +3178..+317c (1) vs built [3166:3177] (11)
  +3178 bne .L_81468DC0
R059 delete target +31b0..+31d4 (9) vs built [3191:3191] (0)
  +31b0 b .L_81468DE0
  +31b4 li r7, 0x3e
  +31b8 lwz r6, 0x68(r1)
  +31bc stb r7, 0x0(r6)
  +31c0 li r4, 0x0
  +31c4 lwz r3, 0x68(r1)
  +31c8 stb r4, 0x2(r3)
  +31cc lwz r3, 0x68(r1)
  +31d0 stb r4, 0x1(r3)
R059 replace target +320c..+3218 (3) vs built [3205:3206] (1)
  +320c lwz r5, 0x98(r1)
  +3210 stw r5, 0x88(r1)
  +3214 lwz r5, 0x94(r1)
R059 replace target +323c..+3240 (1) vs built [3215:3218] (3)
  +323c li r0, 0x0
R059 delete target +32ac..+32c0 (5) vs built [3249:3249] (0)
  +32ac lwz r3, 0x90(r1)
  +32b0 stw r3, 0x88(r1)
  +32b4 lwz r0, 0x8c(r1)
  +32b8 stw r0, 0x84(r1)
  +32bc b .L_81468EDC
R060 delete target +3418..+344c (13) vs built [3335:3335] (0)
  +3418 beq .L_814690D8
  +341c lbz r4, 0x1877(r30)
  +3420 cmplwi r4, 0x1
  +3424 blt .L_81469050
  +3428 lwz r3, 0x3c(r1)
  +342c lwz r6, 0x34(r1)
  +3430 addi r4, r6, 0x1
  +3434 slwi r5, r4, 1
  +3438 lhzx r4, r3, r5
  +343c cmplwi r4, 0xeff1
  +3440 beq .L_8146927C
  +3444 lwz r3, 0xa8(r1)
  +3448 cmpwi r3, 0x0
R060 delete target +3450..+34cc (31) vs built [3336:3336] (0)
  +3450 lwz r0, 0xa4(r1)
  +3454 cmpwi r0, 0x0
  +3458 bne .L_814690D8
  +345c li r3, 0x1
  +3460 stb r3, 0x1984(r30)
  +3464 lbz r5, 0xc(r31)
  +3468 addi r4, r5, 0x1
  +346c clrlwi r7, r4, 24
  +3470 stb r7, 0x1986(r30)
  +3474 lwz r0, 0x9c(r1)
  +3478 cmpwi r0, 0x0
  +347c beq .L_81466A24
  +3480 lwz r12, 0x9c(r1)
  +3484 slwi r11, r12, 1
  +3488 subf r28, r11, r28
  +348c lwz r10, 0x9c(r1)
  +3490 slwi r9, r10, 1
  +3494 lwz r3, 0x3c(r1)
  +3498 subf r0, r9, r3
  +349c stw r0, 0x3c(r1)
  +34a0 lwz r6, 0x34(r1)
  +34a4 lwz r5, 0x9c(r1)
  +34a8 add r4, r6, r5
  +34ac stw r4, 0x34(r1)
  +34b0 lwz r3, 0x4c(r1)
  +34b4 lwz r0, 0x9c(r1)
  +34b8 add r4, r3, r0
  +34bc stw r4, 0x4c(r1)
  +34c0 li r9, 0x0
  +34c4 stw r9, 0x9c(r1)
  +34c8 b .L_81466A24
R065 delete target +384c..+3850 (1) vs built [3607:3607] (0)
  +384c mr r3, r5
R066 delete target +390c..+3910 (1) vs built [3654:3654] (0)
  +390c mr r0, r3
R067 delete target +3974..+397c (2) vs built [3679:3679] (0)
  +3974 mr r3, r5
  +3978 clrlwi r4, r3, 24
R068 delete target +3a20..+3a24 (1) vs built [3721:3721] (0)
  +3a20 mr r4, r3
R069 replace target +3b08..+3b10 (2) vs built [3779:3782] (3)
  +3b08 beq .L_81469724
  +3b0c li r0, 0x0
R069 replace target +3b18..+3b20 (2) vs built [3784:3785] (1)
  +3b18 lwz r12, 0x2c(r1)
  +3b1c clrlwi r11, r12, 24
R069 replace target +3b88..+3b8c (1) vs built [3811:3812] (1)
  +3b88 ble .L_814697B0
```
