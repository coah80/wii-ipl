43U structural matching run. Initial HEAD 0cc4c57ecdeeee25872bf7c93c654f6fceb5e1ab
src/keyboard/tiCandidateBox pool-first
POOL IDENTICAL up to 57 (mine=57 base=57)

src/scene/sdChannelTitle/iplSDChannelTitle pool-first
POOL IDENTICAL up to 55 (mine=55 base=55)

libs/RevoEX/src/nhttp/NHTTP_recvbuf pool-first
POOL IDENTICAL up to 0 (mine=0 base=0)

src/scene/memoryCard/iplMemoryCardManager pool-first
POOL IDENTICAL up to 0 (mine=0 base=0)

DATA ownership: memory/NHTTP have .text only; both matched_data_percent=100 with no data symbols. Candidate rebuilt after #742; pane-name bytes identical; no code function gains.
DATA PROOF lbl_816554C4 -> __vt__Q33ipl5scene25SDTitleButtonEventHandler, size 0x1C->0x1C, same address: constructor .text+0x82 HA/.text+0x8a LO references .data+0x52c; target 5 virtual slots+2 ABI words and source vtable 28 bytes at same offset.
DATA PROOF lbl_816554E0 -> __vt__Q33ipl5scene23SDTitlePaneEventHandler, size 0x18->0x18, same address: create .text+0x612 HA/.text+0x61a LO references .data+0x548; target 4 virtual slots+2 ABI words and source vtable 24 bytes at same offset.
DATA PROOF lbl_816554F8 -> __vt__Q33ipl5scene14SDChannelTitle, size 0x140->0x68, same address: constructor .text+0x22 HA/.text+0x2a LO references .data+0x560; target relocations end .data+0x5c4, 26 words=104 bytes, remaining 216 bytes have no relocations and are weak-data neighbours/padding.
DATA PROOF lbl_81696E40 -> sButtonNames__Q23ipl5scene, size 0x8->0x8, same address: create .text+0x6f8/0x740 and event handlers load .sdata+0x10; two pointer relocations .sdata+0x10/0x14 point to B_BtnA/B_BtnB, matching char*[2] source.
DATA PROOF lbl_81696EA0 -> sTextNames__Q23ipl5scene, size 0x8->0x8, same address: create .text+0x448/0x478 loads .sdata+0x70; two pointer relocations .sdata+0x70/0x74 point to T_BtnA/T_BtnB, matching char*[2] source.
DATA PROOF lbl_81610918 -> sCaptureSizes__Q23ipl5scene, size 0x10->0x10, same address: create .text+0x95a HA/.text+0x962 LO addresses .rodata+0; indexed words 128/96/176/96 match int[2][2] source.
DATA PROOF lbl_81694B60 -> sMissingTitle__Q23ipl5scene, size 0x8->0x8, same address: loadTitleBanner .text+0x19b8 SDA references .sdata2+0; wchar_t[4] question marks + NUL bytes 003f003f003f0000 match source.
DATA attempt SD real object names and vtable extent: {'fuzzy_match_percent': 99.89347, 'total_code': '18624', 'matched_code': '17444', 'matched_code_percent': 93.66409, 'total_data': '1976', 'matched_data': '240', 'matched_data_percent': 12.145749, 'total_functions': 69, 'matched_functions': 64, 'matched_functions_percent': 92.753624, 'total_units': 1}
DATA EXTENT PROOF __vt__Q39textinput12candidatebox20CandidateTextAnmPane 0x30->0x2C same address: two ABI words and nine virtual function slots; final relocation .data+0xac0, source vtable44 bytes; four zero alignment bytes before LayoutByNW4R
DATA EXTENT PROOF __vt__Q39textinput12candidatebox5UIObj 0x20->0x1C same address: two ABI words and five virtual slots; final relocation .data+0xcb0, source28 bytes; four zero alignment bytes before EventHandler
DATA EXTENT PROOF __vt__Q39textinput11nw4rmanager11AnmObserver 0x4C->0xC same address: AnmObserver has one virtual onChangeAnmState slot and two ABI words; source12 bytes and target no relocations (linker deduplicated), 64 trailing bytes belong to neighbours/zero space
DATA EXTENT PROOF csAninationFile__Q29textinput12candidatebox 0x378->0x374 same address: AnimationFile is u32 id+char fileName[64]=68 bytes, thirteen records=884 bytes; PaneToAnimation pAnims relocations reference 0x0..0x330 stepping0x44, source symbol size0x374; four trailing bytes align pointer tables
DATA Candidate scEmptyWChars[4] last element 1->0: target .sdata+8 eight bytes zero, all code references the empty wide-character array at that offset; source array is 8 bytes (wchar_t=2).
DATA measured src/keyboard/tiCandidateBox {'fuzzy_match_percent': 99.4395, 'total_code': '24000', 'matched_code': '19988', 'matched_code_percent': 83.28333, 'total_data': '4652', 'matched_data': '1132', 'matched_data_percent': 24.33362, 'total_functions': 112, 'matched_functions': 109, 'matched_functions_percent': 97.32143, 'total_units': 1}
DATA measured src/scene/sdChannelTitle/iplSDChannelTitle {'fuzzy_match_percent': 99.89347, 'total_code': '18624', 'matched_code': '17444', 'matched_code_percent': 93.66409, 'total_data': '1976', 'matched_data': '240', 'matched_data_percent': 12.145749, 'total_functions': 69, 'matched_functions': 64, 'matched_functions_percent': 92.753624, 'total_units': 1}
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | DATA empty wide literal | 351/352 insns structural/exact (27, 239) objdiff 92.71023% regress 0 source create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.3e7bde005d55
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | DATA const wide literal inference | 351/352 insns structural/exact (27, 239) objdiff 92.71023% regress 0 source create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.b2a82fa26667
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | DATA empty aggregate explicit braces | 351/352 insns structural/exact (27, 239) objdiff 92.71023% regress 0 source create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.6854ec97a2f3
DATA empty wchar attempts reverted: every all-zero form emits .sbss (target .sdata), literal inference size2; cannot force initialized section under current rules. Existing last1 left unchanged, records byte mismatch.
START isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl origin/main b3c23834a7c4ac362ff85018a5fedd90a97befe2 upstream source UNCHANGED
src 0x1d8 base 0x1d8 insns 118/118
diffs 2: [28, 78]
    28 M add r5, r3, r0
       B add r5, r0, r3
    78 M add r5, r3, r0
       B add r5, r0, r3

isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl diagnosis: frame0x30 and118 instructions exact, branch/helper boundaries exact; only28/78 final directory row+column add operands swapped. Test addressing syntax before declaration search.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | commuted subscript file[row] | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.264979154279
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | explicit commuted file plus row first element | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.aacea7457fa9
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | directory struct row files member | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.a1ae5582100e
START isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl origin/main b3c23834a7c4ac362ff85018a5fedd90a97befe2 upstream source UNCHANGED
src 0x1d8 base 0x1d8 insns 118/118
diffs 2: [28, 78]
    28 M add r5, r3, r0
       B add r5, r0, r3
    78 M add r5, r3, r0
       B add r5, r0, r3

isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl diagnosis: frame0x30 and118 instructions exact, branch/helper boundaries exact; only28/78 final directory row+column add operands swapped. Test addressing syntax before declaration search.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | commuted subscript file[row] | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.5169af77e8ef
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | explicit commuted file plus row first element | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.ec93d834b8bf
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | directory struct row files member | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.db36a570c85b
DATA EXTENT TEST scEmptyWChars 8->2: all uses pass an empty wchar_t string (target bytes are zero), no relocation into following six bytes; wchar_t NUL literal size2. Candidate source currently defines wchar_t[4]; test whether source-size discrepancy is tolerated, not accepted without a complete type proof.
START isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs origin/main 08923eda6ca98c9270567edcac967fe6d30868cf upstream source UNCHANGED
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

DIAGNOSIS isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: frame0x20,26/26 instructions; restoring-helper stack base r11 materialized early in source (before address math), target after lbzx. Three typed addressing/evaluation forms before register-only search.
DATA extent-only empty wchar test discarded: inferred string length cannot establish declared array4 size, source extent8 was known; no source/config change retained for this object.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | reference binds icon member | 26/26 insns structural/exact (2, 8) objdiff 92.30769% regress 0 source isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs.e68ad93d5f04
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | index copied before external accessor | 26/26 insns structural/exact (2, 8) objdiff 92.30769% regress 0 source isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs.224bd8c02185
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | explicit unsigned result predicate | 26/26 insns structural/exact (2, 8) objdiff 92.30769% regress 0 source isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs.7639367669a7
DATA STRING EXTENT PROOF lbl_81654FE2 ->0x9 same address, trailing neighbours unowned: G_OutBtn string9, next pointer array starts .data+0x54 and 7 relocations to group strings; former0x26 included 1 alignment byte plus char*[7]
DATA STRING EXTENT PROOF lbl_816550CD ->0x24 same address, trailing neighbours unowned: mn_SdcardMenuBanner_bc_OutBtn_in.brlan string36, next array begins .data+0x15c and6 pointer relocations to animation names; former0x3f absorbed3 padding bytes plus char*[6]
DATA STRING EXTENT PROOF lbl_8165517C ->0xE same address, trailing neighbours unowned: sdChanTtl.ash string14; former0x120 joined twenty following null-terminated literals used by create; source first literal symbol size14 and target matching NUL terminator
DATA STRING EXTENT PROOF lbl_81655318 ->0xF same address, trailing neighbours unowned: sound stopped newline string15; former0xb2 joined following diagnostic strings; source first literal size15 matches target bytes
DATA STRING EXTENT PROOF lbl_816553CA ->0xD same address, trailing neighbours unowned: banner.brlyt string13; former0x34 joined icon.brlyt/icon.brlan/icon_Whole.brlan; target NUL and source first literal size13
DATA STRING EXTENT PROOF lbl_81655462 ->0x16 same address, trailing neighbours unowned: iplSDChannelTitle.cpp string22; former0x62 joined four sound-name literals; target NUL and source first literal size22
DATA PROOF lbl_81655140 -> sBannerAnimationNames__Q23ipl5scene,0x3c->0xc same address: bindBannerAnimations .text+0x37be HA/0x37d2 LO references .data+0x1a8, three pointer relocations to banner.brlan/banner_Start.brlan/banner_Loop.brlan; following char*[3][4] begins .data+0x1b4, left unowned.
DATA after SD true string extents and banner pointer-array boundary: {'fuzzy_match_percent': 99.89347, 'total_code': '18624', 'matched_code': '17444', 'matched_code_percent': 93.66409, 'total_data': '1976', 'matched_data': '240', 'matched_data_percent': 12.145749, 'total_functions': 69, 'matched_functions': 64, 'matched_functions_percent': 92.753624, 'total_units': 1} [{'name': '.data', 'size': '1696', 'fuzzy_match_percent': 19.598541, 'metadata': {}}, {'name': '.rodata', 'size': '48', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata', 'size': '192', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata2', 'size': '40', 'fuzzy_match_percent': 90.0, 'metadata': {}}, {'name': '.text', 'size': '18624', 'fuzzy_match_percent': 99.89347, 'metadata': {}}]
START create_icon__Q33ipl5scene17MemoryCardManagerFUcs origin/main 08923eda6ca98c9270567edcac967fe6d30868cf upstream source UNCHANGED
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

create_icon__Q33ipl5scene17MemoryCardManagerFUcs DIAGNOSIS: frame0x20;51/51 insns. Target hoists animation counter lha before loop, but rereads duration anmFrameBits lhz on every loop iteration at0xe94 (backedge0xebc->0xe90), no stores or calls inside. Source hoists lhz outside; frame/file register allocation also reversed. Check duration read/loop boundaries first.
create_icon__Q33ipl5scene17MemoryCardManagerFUcs | counter named before duration extraction | 51/51 insns structural/exact (7, 15) objdiff 87.05882% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.3119b1fb2b08
create_icon__Q33ipl5scene17MemoryCardManagerFUcs | remaining duration words advanced each iteration | 49/51 insns structural/exact (10, 30) objdiff 81.47059% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.3555d482ce60
create_icon__Q33ipl5scene17MemoryCardManagerFUcs | for frame progression with separate terminal frame | 51/51 insns structural/exact (6, 14) objdiff 87.15686% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.b06501736219
create_icon__Q33ipl5scene17MemoryCardManagerFUcs definition-only volatile duration experiment: target loop repeats lhz .IconState+0x10 each backedge0xebc->0xe90, no stores or calls between reads; change scoped by IPL_MEMORY_CARD_MANAGER_CPP, no other TU output. Not retained without exact code and full gate.
create_icon__Q33ipl5scene17MemoryCardManagerFUcs | duration repeated read with original scalar order | 51/51 insns structural/exact (0, 12) objdiff 98.43137% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.f4f3cc81a163
create_icon__Q33ipl5scene17MemoryCardManagerFUcs | duration repeated read with frame-before-file | 51/51 insns structural/exact (0, 4) objdiff 99.411766% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.eab89c8e631d
START _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl origin/main 08923eda6ca98c9270567edcac967fe6d30868cf upstream source UNCHANGED
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

create_icon__Q33ipl5scene17MemoryCardManagerFUcs DECLSEARCH after structural duration fix

create_icon__Q33ipl5scene17MemoryCardManagerFUcs | duration + declaration search | 51/51 insns structural/exact (0, 4) objdiff 99.411766% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.eab89c8e631d
create_icon__Q33ipl5scene17MemoryCardManagerFUcs | duration right shift postfix frame directly | 51/51 insns structural/exact (0, 0) objdiff 100.0% regress 0 source create_icon__Q33ipl5scene17MemoryCardManagerFUcs.ff57b3a014b7
EXACT CANDIDATE create_icon__Q33ipl5scene17MemoryCardManagerFUcs duration right shift postfix frame directly
create_icon accepted quick gate PASS:51/51 instructions ctxdiff0, objdiff100, memory instruction-exact17->18 code2368->2572, regressions0; volatile duration reads at target0xe94 recur on0xebc->0xe90 backedge without stores/calls; guarded other TUs unchanged.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl DIAGNOSIS frame0x30,100/100insns; target retains independent cell row/column addresses across GX calls, computes final texture address after GXInitTexObj, source caches complete texture before call; icon row/column add operands also reversed. Three lifetime/address forms.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | texture branch result assigned after initializer | 101/100 insns structural/exact (17, 61) objdiff 85.3% regress 0 source _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl.fe3d5b6066e8
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | commuted icon row address and image displacement | 100/100 insns structural/exact (16, 37) objdiff 87.55% regress 0 source _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl.d3e6de82b2d3
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | column then row selector via typed cell helper | 100/100 insns structural/exact (20, 67) objdiff 78.13% regress 0 source _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl.853475ce68a5
DATA RECOVERED NEIGHBOUR PROOF sButtonGroups__Q23ipl5scene = .data:0x81654FEC; // type:object size:0x1C scope:local data:4byte: char*[7], .data+0x54..0x6c relocations to seven G_* group strings; create/event handler base .data+0 addressing uses +0x54; was swallowed by G_OutBtn extent; original addresses and split section totals unchanged, only target object boundaries.
DATA RECOVERED NEIGHBOUR PROOF sButtonAnimationNames__Q23ipl5scene = .data:0x816550F4; // type:object size:0x18 scope:local data:4byte: char*[6], .data+0x15c..0x170 relocations to six mn_SdcardMenuBanner_bc_* strings; create uses same offsets from pooled .data base; swallowed by OutBtn string extent; original addresses and split section totals unchanged, only target object boundaries.
DATA RECOVERED NEIGHBOUR PROOF sTexturePaneNames__Q23ipl5scene = .data:0x8165514C; // type:object size:0x30 scope:local data:4byte: char*[3][4], .data+0x1b4..0x1e0 relocations to twelve Fre_* pane strings; create indexes12 pointers; swallowed by banner animation array extent; original addresses and split section totals unchanged, only target object boundaries.
START getComment__Q33ipl5scene17MemoryCardManagerFUcsi origin/main 2f0f5a44c72cb84e23732e09fc8e75487c788f76 upstream source UNCHANGED
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

DATA after recovered pointer-array neighbours: [{'name': '.data', 'size': '1696', 'fuzzy_match_percent': 28.318872, 'metadata': {}}, {'name': '.rodata', 'size': '48', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata', 'size': '192', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata2', 'size': '40', 'fuzzy_match_percent': 90.0, 'metadata': {}}, {'name': '.text', 'size': '18624', 'fuzzy_match_percent': 99.89347, 'metadata': {}}]
getComment__Q33ipl5scene17MemoryCardManagerFUcsi DIAGNOSIS frame0x60 and123/123 insns, zero structural differences; this/column/file-cell-offset/decoded-pointer callee-saved lifetimes differ and trailing ASCII trim uses r5/r3 reversed. Preserve operations and test actual source-level local/loop boundaries before declsearch.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | stack comment declared before file selection | 123/123 insns structural/exact (27, 47) objdiff 78.032524% regress 0 source getComment__Q33ipl5scene17MemoryCardManagerFUcsi.d78de696c8f6
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | trim character pointer decrement integrated in scan | 123/123 insns structural/exact (0, 21) objdiff 98.861786% regress 0 source getComment__Q33ipl5scene17MemoryCardManagerFUcsi.f127fa891688
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | newline truncation for loop scoped found flag | 123/123 insns structural/exact (0, 20) objdiff 98.94309% regress 0 source getComment__Q33ipl5scene17MemoryCardManagerFUcsi.6d93e902721f
START create_banner__Q33ipl5scene17MemoryCardManagerFUcs origin/main 5d63d152486a556fa24edf46b65dee7ce88474d6 upstream source UNCHANGED
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

create_banner__Q33ipl5scene17MemoryCardManagerFUcs DIAGNOSIS frame0x40,106/106 insns; target rebuilds row+column icon pointer after validation and preserves separate texture/TLUT base offsets across GX calls; source merges validation and rendering icon pointers. Try argument and cell row lifetimes; no volatile evidence for banner fields.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | typed render-image temporary inside each format branch | 106/106 insns structural/exact (15, 70) objdiff 90.42453% regress 0 source create_banner__Q33ipl5scene17MemoryCardManagerFUcs.c5dde8aad816
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | texture and TLUT typed cells addressed after validation | 97/106 insns structural/exact (81, 90) objdiff 63.103775% regress 0 source create_banner__Q33ipl5scene17MemoryCardManagerFUcs.ebdaefe8aed5
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | directory reference validates before icon access | 108/106 insns structural/exact (18, 87) objdiff 88.4434% regress 0 source create_banner__Q33ipl5scene17MemoryCardManagerFUcs.ceae65267db5
START getBlocks__Q33ipl5scene17MemoryCardManagerFUcs origin/main 5543b7b720e18b9e093f2f3a9e8f9d4cb3a2eabb upstream source UNCHANGED
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

getBlocks__Q33ipl5scene17MemoryCardManagerFUcs DIAGNOSIS frame0x20,25/25 insns; source hoists restore stack-base instruction before address chain, target leaves it after final lhzx. Three real selector/value declaration forms.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | directory reference and named result | 25/25 insns structural/exact (2, 9) objdiff 91.0% regress 0 source getBlocks__Q33ipl5scene17MemoryCardManagerFUcs.b96479a35734
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | file lookup named before card directory getter | 23/25 insns structural/exact (20, 23) objdiff 26.08% regress 0 source getBlocks__Q33ipl5scene17MemoryCardManagerFUcs.b2485fca815c
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | commuted directory column plus typed row | 25/25 insns structural/exact (2, 9) objdiff 91.0% regress 0 source getBlocks__Q33ipl5scene17MemoryCardManagerFUcs.8933679ebf34
SKIP update_file_array__Q33ipl5scene17MemoryCardManagerFUc: user-directed known r3/r4 tie; already exact update_icon_anm not touched.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl REGISTER SEARCH after >=3 addressing/lifetime attempts
fewer than two leading declarations; pass --lines START END

isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | final declaration order search | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.ff57b3a014b7
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl REGISTER SEARCH after >=3 addressing/lifetime attempts
fewer than two leading declarations; pass --lines START END

isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | final declaration order search | 118/118 insns structural/exact (0, 2) objdiff 99.830505% regress 0 source isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl.ff57b3a014b7
getComment__Q33ipl5scene17MemoryCardManagerFUcsi REGISTER SEARCH after >=3 addressing/lifetime attempts
declaration block:
      const u8* encoded;
      char* tail;
      char* end;
start (0, 20)
best (0, 20) after 6 builds; source restored; best order was:
    const u8* encoded;
    char* tail;
    char* end;

getComment__Q33ipl5scene17MemoryCardManagerFUcsi | final declaration order search | 123/123 insns structural/exact (0, 20) objdiff 98.94309% regress 0 source getComment__Q33ipl5scene17MemoryCardManagerFUcsi.e2182693d4f2
START calcFadein__Q33ipl5scene14SDChannelTitleFv origin/main 422a344b282c65104a9157a99239d0950b337472 upstream source UNCHANGED
src 0xc0 base 0xbc insns 48/47
--- replace mine 11:12 base 11:12
  M   11 b 124
  B   11 b 120
--- replace mine 15:16 base 15:16
  M   15 beq 84
  B   15 beq 80
--- delete mine 24:25 base 24:24
  M   24 li r5, 0

isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl DECLSEARCH explicit six-line typed declarations (autodetect stops at qualified type)
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

isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl DECLSEARCH explicit six-line typed declarations (autodetect stops at qualified type)
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

calcFadein__Q33ipl5scene14SDChannelTitleFv DIAGNOSIS frame0x10,48/47insns; extra li r5,0 is second optOut handler argument unused by callee, causing branch displacements; no register-only issue. Preserve callable signature; test branch/helper/live-handler forms.
calcFadein__Q33ipl5scene14SDChannelTitleFv | positive fade-playing early continuation | 48/47 insns structural/exact (17, 34) objdiff 67.87234% regress 0 source calcFadein__Q33ipl5scene14SDChannelTitleFv.b7af66be118b
calcFadein__Q33ipl5scene14SDChannelTitleFv | event handler captured before button lookup | 49/47 insns structural/exact (17, 38) objdiff 78.85107% regress 0 source calcFadein__Q33ipl5scene14SDChannelTitleFv.0fb8cd5fe935
calcFadein__Q33ipl5scene14SDChannelTitleFv | button reference with separately named fade result | 48/47 insns structural/exact (3, 26) objdiff 97.87234% regress 0 source calcFadein__Q33ipl5scene14SDChannelTitleFv.643f10ce33c6
START initCalcFadeout__Q33ipl5scene14SDChannelTitleFv origin/main c4857800df46ae3edfd824198fa09a31c4f6ce0f upstream source UNCHANGED
src 0xc8 base 0xc4 insns 50/49
--- delete mine 43:44 base 43:43
  M   43 li r5, 0

initCalcFadeout__Q33ipl5scene14SDChannelTitleFv DIAGNOSIS frame0x10,50/49insns; extra initialized optOut handler r5 makes callable ABI different from target call preparation; state branches otherwise identical. No ABI casts or unused uninitialized values.
initCalcFadeout__Q33ipl5scene14SDChannelTitleFv | state dispatch switch grouped sound cases | 52/49 insns structural/exact (14, 38) objdiff 85.46939% regress 0 source initCalcFadeout__Q33ipl5scene14SDChannelTitleFv.37f523731bf2
initCalcFadeout__Q33ipl5scene14SDChannelTitleFv | named optOut handler pointer | BUILD FAIL i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -W nomissingreturn -ipa file -gccinc -fp_contract off -O4,s -enc SJIS -lang=c++ -MMD -c src/scene/sdChannelTitle/iplSDChannelTitle.cpp -o build/43U/src/src/scene/sdChannelTitle && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/scene/sdChannelTitle/iplSDChannelTitle.d build/43U/src/src/scene/sdChannelTitle/iplSDChannelTitle.d
### mwcceppc.exe Compiler:
#      In: include\utility\iplTree.h
#    From: src\scene\sdChannelTitle\iplSDChannelTitle.cpp
# -------------------------------------------------------
#      40:                 }
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\iplFaderSceneBase.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\iplSceneHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\sdChannelTitle\iplSDChannelTitle.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\src\scene\sdChannelTitle\iplSDChannelTitle.cpp:6)
### mwcceppc.exe Compiler:
#    File: src\scene\sdChannelTitle\iplSDChannelTitle.cpp
# -------------------------------------------------------
#     347:     SDButtonOptOutEventHandler* optOut = NULL;
#   Error:     ^^^^^^^^^^^^^^^^^^^^^^^^^^
#   (10140) undefined identifier 'SDButtonOptOutEventHandler'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

initCalcFadeout__Q33ipl5scene14SDChannelTitleFv | button reference receiver | 50/49 insns structural/exact (1, 7) objdiff 97.95918% regress 0 source initCalcFadeout__Q33ipl5scene14SDChannelTitleFv.2f6b81493f27
START iplSDChannelTitle_startCopyProgress origin/main c4857800df46ae3edfd824198fa09a31c4f6ce0f upstream source UNCHANGED
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

iplSDChannelTitle_startCopyProgress DIAGNOSIS frame0x20,87/86insns; enqueueChannelNotice receives initialized controller r4=0, target does not initialize it; title high/low/receiver scheduling also differs. Test actual title and request argument lifetimes.
iplSDChannelTitle_startCopyProgress | request data pointer captured before selector | 88/86 insns structural/exact (10, 36) objdiff 94.51163% regress 0 source iplSDChannelTitle_startCopyProgress.a4eef35e180c
iplSDChannelTitle_startCopyProgress | selector receiver named for find and enqueue | 88/86 insns structural/exact (10, 34) objdiff 92.19768% regress 0 source iplSDChannelTitle_startCopyProgress.13c4126272bb
iplSDChannelTitle_startCopyProgress | title high/low grouped in union at request | 91/86 insns structural/exact (11, 40) objdiff 93.96512% regress 0 source iplSDChannelTitle_startCopyProgress.17f0521c8a49
START iplSDChannelTitle_updateCopyStart origin/main c4857800df46ae3edfd824198fa09a31c4f6ce0f upstream source UNCHANGED
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

iplSDChannelTitle_updateCopyStart DIAGNOSIS frame0x20,77/76insns; enqueueStateNotice controller r4=0 absent in target plus title-word scheduling. Try request receiver and title-word lifetime forms while keeping ABI and event order.
iplSDChannelTitle_updateCopyStart | temporary title high/low locals before enqueue | 77/76 insns structural/exact (5, 33) objdiff 98.3421% regress 0 source iplSDChannelTitle_updateCopyStart.5aade78b371d
iplSDChannelTitle_updateCopyStart | removed title request named result | 77/76 insns structural/exact (5, 33) objdiff 98.3421% regress 0 source iplSDChannelTitle_updateCopyStart.3fc0860741fd
iplSDChannelTitle_updateCopyStart | title word union preserves full comparison | 77/76 insns structural/exact (17, 47) objdiff 76.697365% regress 0 source iplSDChannelTitle_updateCopyStart.8b9ee376a5ca
START iplSDChannelTitle_flushSaveBeforeExit origin/main c4857800df46ae3edfd824198fa09a31c4f6ce0f upstream source UNCHANGED
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

iplSDChannelTitle_flushSaveBeforeExit DIAGNOSIS frame0x20,37/37insns; target smArg base r3 vs source r4, save receiver r4 vs source r3; target heap load precedes save receiver reload after page store. Inspect argument nesting/cached receiver boundaries before register search.
iplSDChannelTitle_flushSaveBeforeExit | heap getter nested in flush argument | 37/37 insns structural/exact (2, 6) objdiff 98.5946% regress 0 source iplSDChannelTitle_flushSaveBeforeExit.6fb891065ce7
iplSDChannelTitle_flushSaveBeforeExit | save receiver named across page store and flush | 36/37 insns structural/exact (1, 16) objdiff 96.35135% regress 0 source iplSDChannelTitle_flushSaveBeforeExit.c83d79e76c61
iplSDChannelTitle_flushSaveBeforeExit | page value declared before save accessor | 37/37 insns structural/exact (2, 6) objdiff 98.5946% regress 0 source iplSDChannelTitle_flushSaveBeforeExit.987ef44c910b
initCalcFadeout__Q33ipl5scene14SDChannelTitleFv | named typed optOut handler corrected | 50/49 insns structural/exact (1, 7) objdiff 97.95918% regress 0 source initCalcFadeout__Q33ipl5scene14SDChannelTitleFv.41b00df1c3fd
iplSDChannelTitle_flushSaveBeforeExit declaration search after structural argument/receiver attempts
declaration block:
      int page;
      int index;
start (2, 6)
best (2, 6) after 2 builds; source restored; best order was:
    int page;
    int index;

SD code attempts all restored; unused optOut/controller argument declarations in neighbouring APIs account for four extra argument initialization instructions. Correcting ABI/function symbol names outside current data-only rename scope is not authorized. Flush remains argument scheduling/smArg base GPR tie.
START create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator origin/main c4857800df46ae3edfd824198fa09a31c4f6ce0f upstream source UNCHANGED
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

create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator DIAGNOSIS frame0x30,351/352 insns. Target inlined UITextArea::Init advances owner pointer with fixed loads0x11c/0x16c, source indexes offset and extra adds. Scroll/window name arguments target cached separately in callee-saved registers; ours rematerializes pointer offsets. Target pool after#742 identical, no data padding/strings added.
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | decorated string allocation typed before member store | 351/352 insns structural/exact (27, 239) objdiff 92.71023% regress 0 source create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.2a0276ff27b0
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | window name captured before window Create helper | 352/352 insns structural/exact (24, 218) objdiff 93.67614% regress 0 source create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.d9cd56dc516f
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | text area named reference across create/init calls | 352/352 insns structural/exact (34, 267) objdiff 92.55398% regress 0 source create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.822ce4aadb06
START createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator origin/main c4857800df46ae3edfd824198fa09a31c4f6ce0f upstream source UNCHANGED
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

createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator DIAGNOSIS frame0x50,214/216insns; cached animation pointer in source persists across CreateAnimTransform, target keeps entry address and reloads pAnims[j] separately in both branches; restoring these two loads makes structure exact. Remaining vtable hoisting and GPR lifetime coloring considered last.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | animation reference to entry pointer across resource creation | 216/216 insns structural/exact (0, 82) objdiff 97.361115% regress 0 source createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.095584f09005
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator animation reference to entry pointer across resource creation data 1132 [{'name': '.ctors', 'size': '4', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.data', 'size': '3488', 'fuzzy_match_percent': 99.48127, 'metadata': {}}, {'name': '.rodata', 'size': '1048', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata', 'size': '32', 'fuzzy_match_percent': 96.875, 'metadata': {}}, {'name': '.sdata2', 'size': '80', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.text', 'size': '24000', 'fuzzy_match_percent': 99.46817, 'metadata': {}}]
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | animation id read only after transform creation | 216/216 insns structural/exact (20, 152) objdiff 91.736115% regress 0 source createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.80cae5ce662f
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator animation id read only after transform creation data 1132 [{'name': '.ctors', 'size': '4', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.data', 'size': '3488', 'fuzzy_match_percent': 99.48127, 'metadata': {}}, {'name': '.rodata', 'size': '1048', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata', 'size': '32', 'fuzzy_match_percent': 96.875, 'metadata': {}}, {'name': '.sdata2', 'size': '80', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.text', 'size': '24000', 'fuzzy_match_percent': 99.26566, 'metadata': {}}]
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | separate resource and animation descriptors | 220/216 insns structural/exact (37, 170) objdiff 92.15278% regress 0 source createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.ad2835c5becf
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator separate resource and animation descriptors data 1132 [{'name': '.ctors', 'size': '4', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.data', 'size': '3488', 'fuzzy_match_percent': 99.48127, 'metadata': {}}, {'name': '.rodata', 'size': '1048', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.sdata', 'size': '32', 'fuzzy_match_percent': 96.875, 'metadata': {}}, {'name': '.sdata2', 'size': '80', 'fuzzy_match_percent': 100.0, 'metadata': {}}, {'name': '.text', 'size': '24000', 'fuzzy_match_percent': 99.28067, 'metadata': {}}]
START CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv origin/main c4857800df46ae3edfd824198fa09a31c4f6ce0f upstream source UNCHANGED
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

CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv DIAGNOSIS frame0xd0,435/435insns, structure identical; eleven f2/f3 substitutions in second (forward) calcStringWidth inline return and size/height stores. Backwards helper matches. Only forward locals/operands/helper boundaries varied, protect other exact helper users.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | forward Size reference extends temporary lifetime | 432/435 insns structural/exact (53, 195) objdiff 97.73793% regress 0 source CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv.b52821f87fc0
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | forward string width declared before pane receiver | 435/435 insns structural/exact (0, 11) objdiff 99.873566% regress 0 source CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv.ce7189ca2d09
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | forward translated centre as separate summand | 435/435 insns structural/exact (2, 39) objdiff 99.413795% regress 0 source CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv.c509618a410d
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv declaration search after three local/operand trials
fewer than two leading declarations; pass --lines START END

START NHTTPi_compareTokenN_HdrRecvBuf origin/main cbf6363d0f5e07b6dceadc43693694c14d58a229 upstream source UNCHANGED
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

NHTTPi_compareTokenN_HdrRecvBuf DIAGNOSIS source frame0x30,126/124insns; source narrows ReadHeaderChar before fold and at reader boundary, target retains integer byte with sign extension at fold; positive position<limit block and ternary LowerCase restore target124 instruction structure. Remaining constant65/90/zero hoisting must be scheduled correctly.
NHTTPi_compareTokenN_HdrRecvBuf | positive position guard integer reader and ternary fold | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.df21f56f0c89
NHTTPi_compareTokenN_HdrRecvBuf | uppercase range represented by unsigned distance | 103/124 insns structural/exact (35, 124) objdiff 76.814514% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.1a136fb9a2ed
NHTTPi_compareTokenN_HdrRecvBuf | inverted lowercase early result predicate | 127/124 insns structural/exact (53, 82) objdiff 61.629032% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.5a66fec9ead8
NHTTPi_compareTokenN_HdrRecvBuf | ASCII bounds assigned before first reader | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.e9de2d03a8f3
NHTTPi_compareTokenN_HdrRecvBuf | ASCII bounds assigned after reader and before folding | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.bf33461b268c
NHTTPi_compareTokenN_HdrRecvBuf | ASCII bounds reverse independent initialization | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.9c8088d5b576
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator declaration search after entry pointer structural fix
declaration block:
              u16 i;
              u16 j;
              CandidateTextAnmPane* pane;
start (0, 53)
best (0, 53) after 6 builds; source restored; best order was:
            u16 i;
            u16 j;
            CandidateTextAnmPane* pane;

createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | entry pointer reload with leading index declarations | 216/216 insns structural/exact (0, 53) objdiff 98.541664% regress 0 source createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator.5fd8462f4a9e
FRAME AUDIT isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: source ('stwu', 'r1, -0x30(r1)'), target ('stwu', 'r1, -0x30(r1)'), instructions 118/118, current score (0, 2). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: source ('stwu', 'r1, -0x30(r1)'), target ('stwu', 'r1, -0x30(r1)'), instructions 118/118, current score (0, 2). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: source ('stwu', 'r1, -0x20(r1)'), target ('stwu', 'r1, -0x20(r1)'), instructions 26/26, current score (2, 8). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT update_file_array__Q33ipl5scene17MemoryCardManagerFUc: source ('stwu', 'r1, -0x10(r1)'), target ('stwu', 'r1, -0x10(r1)'), instructions 90/90, current score (0, 4). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT create_icon__Q33ipl5scene17MemoryCardManagerFUcs: source ('stwu', 'r1, -0x20(r1)'), target ('stwu', 'r1, -0x20(r1)'), instructions 51/51, current score (0, 0). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: source ('stwu', 'r1, -0x30(r1)'), target ('stwu', 'r1, -0x30(r1)'), instructions 100/100, current score (16, 37). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT getComment__Q33ipl5scene17MemoryCardManagerFUcsi: source ('stwu', 'r1, -0x60(r1)'), target ('stwu', 'r1, -0x60(r1)'), instructions 123/123, current score (0, 20). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT create_banner__Q33ipl5scene17MemoryCardManagerFUcs: source ('stwu', 'r1, -0x40(r1)'), target ('stwu', 'r1, -0x40(r1)'), instructions 106/106, current score (15, 70). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT getBlocks__Q33ipl5scene17MemoryCardManagerFUcs: source ('stwu', 'r1, -0x20(r1)'), target ('stwu', 'r1, -0x20(r1)'), instructions 25/25, current score (2, 9). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT calcFadein__Q33ipl5scene14SDChannelTitleFv: source ('stwu', 'r1, -0x10(r1)'), target ('stwu', 'r1, -0x10(r1)'), instructions 48/47, current score (3, 26). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT initCalcFadeout__Q33ipl5scene14SDChannelTitleFv: source ('stwu', 'r1, -0x10(r1)'), target ('stwu', 'r1, -0x10(r1)'), instructions 50/49, current score (1, 7). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT iplSDChannelTitle_startCopyProgress: source ('stwu', 'r1, -0x20(r1)'), target ('stwu', 'r1, -0x20(r1)'), instructions 87/86, current score (9, 24). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT iplSDChannelTitle_updateCopyStart: source ('stwu', 'r1, -0x20(r1)'), target ('stwu', 'r1, -0x20(r1)'), instructions 77/76, current score (5, 33). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT iplSDChannelTitle_flushSaveBeforeExit: source ('stwu', 'r1, -0x20(r1)'), target ('stwu', 'r1, -0x20(r1)'), instructions 37/37, current score (2, 6). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator: source ('stwu', 'r1, -0x20(r1)'), target ('stwu', 'r1, -0x20(r1)'), instructions 351/352, current score (27, 239). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator: source ('stwu', 'r1, -0x50(r1)'), target ('stwu', 'r1, -0x50(r1)'), instructions 214/216, current score (9, 100). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv: source ('stwu', 'r1, -0x190(r1)'), target ('stwu', 'r1, -0x190(r1)'), instructions 435/435, current score (0, 11). Frame facts here supersede earlier manually estimated sizes.
FRAME AUDIT NHTTPi_compareTokenN_HdrRecvBuf: source ('stwu', 'r1, -0x20(r1)'), target ('stwu', 'r1, -0x30(r1)'), instructions 126/124, current score (25, 117). Frame facts here supersede earlier manually estimated sizes.
DATA final retained scope: seven SD real-object names (three vtables, two name arrays, capture sizes, missing title) with one proven SD vtable extent correction; four Candidate type extents. Experimental string-neighbour extent cuts, newly recovered pointer-array labels, and empty-wide-string size changes restored. None changes section totals or function symbols. Matched_data remains unchanged; no claim of new exact data.
DATA remaining Candidate .data source0xd7c vs target0xda0 (36 bytes), all paired named objects agree after proven extents; extra/deduplicated weak data ignored, not suppressed or padded. .sdata scEmptyWChars source last element1 vs target zero cannot fix by all-zero initialization because compiler moves it to .sbss. SD data still anonymous pooled-string extents and different virtual callback references; do not invent compiler-name renames or change function names.
NHTTPi_compareTokenN_HdrRecvBuf parameter-boundary experiment: actual differing extsb r7,r7 narrows delimiter, not reader character. Target narrows it after ASCII bounds constants; source s8 formal creates earlier narrowing. No public header declares this function. Test word formal plus explicit signed-byte comparison (same r7 word ABI, same truncation semantics), avoiding any function rename or ABI cast.
NHTTPi_compareTokenN_HdrRecvBuf | word delimiter explicitly narrowed at comparison | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.c1b441fd8d40
NHTTPi_compareTokenN_HdrRecvBuf | word delimiter copied into byte local at valid-position guard | 124/124 insns structural/exact (6, 63) objdiff 94.98387% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.c45241fd6d35
NHTTPi_compareTokenN_HdrRecvBuf | word delimiter narrowed after first header read | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.7bc6f600b89b
NHTTPi_compareTokenN_HdrRecvBuf declaration search after frame/read-width/guard/helper and delimiter boundary attempts
declaration block:
      NHTTPi_HDRBUFLIST* block;
      s32 offset;
      int character;
start (4, 5)
best (4, 5) after 6 builds; source restored; best order was:
    NHTTPi_HDRBUFLIST* block;
    s32 offset;
    int character;

NHTTPi_compareTokenN_HdrRecvBuf | final header comparator declaration search | 124/124 insns structural/exact (4, 5) objdiff 97.32258% regress 0 source NHTTPi_compareTokenN_HdrRecvBuf.df21f56f0c89
AUDIT isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 99.830505% 4 distinct compiled source variants
AUDIT isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 99.830505% 4 distinct compiled source variants
AUDIT isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs 92.30769% 3 distinct compiled source variants
AUDIT update_file_array__Q33ipl5scene17MemoryCardManagerFUc 99.72222% 0 distinct compiled source variants USER-SKIPPED
AUDIT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl 87.55% 3 distinct compiled source variants
AUDIT getComment__Q33ipl5scene17MemoryCardManagerFUcsi 98.94309% 4 distinct compiled source variants
AUDIT create_banner__Q33ipl5scene17MemoryCardManagerFUcs 90.42453% 3 distinct compiled source variants
AUDIT getBlocks__Q33ipl5scene17MemoryCardManagerFUcs 92.0% 3 distinct compiled source variants
AUDIT calcFadein__Q33ipl5scene14SDChannelTitleFv 97.87234% 3 distinct compiled source variants
AUDIT initCalcFadeout__Q33ipl5scene14SDChannelTitleFv 97.95918% 3 distinct compiled source variants
AUDIT iplSDChannelTitle_startCopyProgress 98.62791% 3 distinct compiled source variants
AUDIT iplSDChannelTitle_updateCopyStart 98.3421% 3 distinct compiled source variants
AUDIT iplSDChannelTitle_flushSaveBeforeExit 98.5946% 3 distinct compiled source variants
AUDIT create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator 92.71023% 3 distinct compiled source variants
AUDIT createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator 96.56481% 6 distinct compiled source variants
AUDIT CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv 99.873566% 3 distinct compiled source variants
AUDIT NHTTPi_compareTokenN_HdrRecvBuf 87.59677% 9 distinct compiled source variants
Completeness audit passed: every remaining function has >=3 distinct compiled source variants, except explicitly skipped update_file_array. All unsuccessful source experiments restored; only exact create_icon retained.
Final retained data metadata quick gate PASS, global regression0/forbidden0/readability0/DOL hash unchanged. SD .data fuzzy0(unpaired)->10.087957 with correct three vtable names and104-byte extent; matched_data still240/1976. Candidate four type extents corrected, matched_data still1132/4652. Extent proof is object layout/relocation evidence; no bytes or section boundaries moved.
Final full gate PASS over all four; clean rebuild, DOL exact,0 regressions/patterns/readability; final report records all17 open functions and data uncertainty.
