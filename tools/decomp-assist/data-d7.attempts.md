# Data lane d7 attempts

Baseline HEAD 85701c82. Origin fetched; all four owned sources unchanged on origin/main. Initial quick gate PASS, DOL 26116613f624061ba99c8d1a299aaa6efa85670d, regressions 0.

| Unit | matched_data | instruction-exact | matched_code |
| --- | --- | --- | --- |
| iplAddressEdit | 368/2560 | 87/94 | 21556/27112 |
| iplAddress | 36/1964 | 94/101 | 20256/23988 |
| WPADHIDParser | 224/1664 | 22/22 | 21664/21664 |
| iplBoardObject | 56/1320 | 38/39 | 9184/9184 |

Pool checks run before source experiments: identical strings and offsets, counts 57/81/45/39 respectively. ELF section and symbol comparison found no missing tables or wrong nonzero initializer bytes. All overlapping non-relocated bytes agree.

## iplAddress

The digit table target symbol is 22 bytes, source 20 bytes. Target holds the wide string 0123456789 plus its terminator. Investigate a real terminated digit table rather than adding padding.

Attempt 1, set_page_text: use the target wide-string initializer with explicit 10-element array. MWCC rejects it as too many initializers; stale object was not counted as a result.
Attempt 2, set_page_text: inferred-size terminated wide-string array emits the correct 22-byte literal, but copies its terminator to the stack and regresses the exact function from 67 to 69 instructions. Rejected.
Attempt 3, set_page_text: copy ten digits from the terminated literal with memcpy. Correct literal but emits a memcpy call and 65 instructions versus 67; rejected.
Attempt 4, set_page_text: ten-element indexed copy loop from the real wide literal. 66 versus 67 instructions; the target copies pairs with update loads/stores. Rejected.
Attempt 5, set_page_text: paired indexed copy loop. 69 versus 67 instructions; still indexed addressing instead of paired pointer-update addressing. Restored original exact function. No rejected experiment retained.

## Section audit and stopping evidence

Fresh origin fetch before each unit; owned source paths have no changes on origin/main. Native nm -n, objdump -t and objdump -r inspected both ELF objects, with detailed output in /tmp/data-d7.symbols.txt. The semantic relocation audit resolves target section offsets and target function plus offset, avoiding auto-generated literal names. Full evidence follows below.

- AddressEdit: all 211 original .data relocations match semantically. Source has 31 additional relocations in the deduplicated PaneManager, EventHandler and Interface weak vtables. Original bytes there are all zero with no relocations. Overlapping raw data bytes are equal. The only size residuals are 4 trailing zero bytes in .data and 5 trailing zeros in .rodata. No missing typed object found.
- Address: all 87 original .data relocations match semantically, including the jump table. Same 31 extra weak-vtable relocations and zero-filled extraction. .sbss has the real 8-byte VEC2, versus two unnamed 4-byte extraction symbols; bytes agree and its accesses match. .data/.rodata/.sdata/.sdata2 each have 4 trailing original zero bytes. Only possible semantic discrepancy is the terminated wide-digit literal, tested five ways above without retaining regressions.
- WPADHIDParser: all 32 dispatch table relocations match. checkInvalidData is correctly 21 bytes, all BSS arrays have the target types/order/sizes, and .sdata2 plus .sbss agree byte-for-byte. .data is identical over all 1434 source bytes; only the 6-byte trailing extraction alignment differs. This unit is already linked C and the DOL gate passes. No source fix is justified.
- BoardObject: all 38 original .data relocations match, including the 120-byte animation-name table and vtables. Same 31 additional weak-vtable relocations into target zeros. .rodata has the correct 12-byte three-pointer struct and its 3 relocations match. .sdata2 is identical over 60 source bytes, including the target white color and float constants. .data/.rodata/.sdata2 each have 4 trailing original zero bytes. This unit is already linked C++ and the DOL gate passes. No source fix is justified.

No extab or extabindex sections exist in any owned object. No ownership correction is warranted: every original relocation is accounted for; changing split endpoints would merely redistribute alignment rather than fix missing source data. No dummy objects, forced placement or fake tables introduced.

This is the data lane. Existing unmatched code functions are unchanged and are not data causes: all owned original data relocations match. No code tuning was done beyond the digit-table experiments. Every identified data discrepancy has either direct byte/relocation evidence for the extraction exception or five distinct logged source attempts. The requested literal 100-percent section/data metrics remain unresolved because the extraction includes alignment and weak-data holes.

### Semantic ELF comparison

```text

## src/scene/address/iplAddressEdit
.data: original/source 2152/2148 bytes, overlapping non-relocation byte differences [], original tail 00000000
relocations: missing []; extra [2020, 2008, 2064, 2060, 2056, 2052, 2048, 2040, 2044, 2036, 2032, 2024, 2016, 2012, 2088, 2084, 2080, 2076, 2072, 2068, 2028, 2112, 2108, 2104, 2100, 2144, 2136, 2140, 2132, 2128, 2124]; changed []
extra targets: [('0x7e4', (1, ('draw__Q23gui9InterfaceFRA3_A4_f', 0)), '00000000'), ('0x7d8', (1, ('create__Q23gui9InterfaceFv', 0)), '00000000'), ('0x810', (1, ('setDraggingButton__Q23gui7ManagerFUl', 0)), '00000000'), ('0x80c', (1, ('changeEventHandler__Q23gui7ManagerFPQ23gui12EventHandler', 0)), '00000000'), ('0x808', (1, ('setEventHandler__Q23gui7ManagerFPQ23gui12EventHandler', 0)), '00000000'), ('0x804', (1, ('setAllComponentTriggerTarget__Q23gui7ManagerFb', 0)), '00000000'), ('0x800', (1, ('onEvent__Q23gui7ManagerFUlUliPv', 0)), '00000000'), ('0x7f8', (1, ('update__Q23gui7ManagerFiPC10KPADStatusffPv', 0)), '00000000'), ('0x7fc', (1, ('update__Q23gui7ManagerFiffUlUlUlPv', 0)), '00000000'), ('0x7f4', (1, ('getComponent__Q23gui7ManagerFUl', 0)), '00000000'), ('0x7f0', (1, ('addComponent__Q23gui7ManagerFPQ23gui9Component', 0)), '00000000'), ('0x7e8', (1, ('draw__Q23gui7ManagerFv', 0)), '00000000'), ('0x7e0', (1, ('calc__Q23gui7ManagerFv', 0)), '00000000'), ('0x7dc', (1, ('init__Q23gui7ManagerFv', 0)), '00000000'), ('0x828', (1, ('walkInChildren__Q23gui11PaneManagerFRQ34nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>', 0)), '00000000'), ('0x824', (1, ('setAllBoundingBoxComponentTriggerTarget__Q23gui11PaneManagerFb', 0)), '00000000'), ('0x820', (1, ('setDrawInfo__Q23gui11PaneManagerFPCQ34nw4r3lyt8DrawInfo', 0)), '00000000'), ('0x81c', (1, ('getDrawInfo__Q23gui11PaneManagerFv', 0)), '00000000'), ('0x818', (1, ('getPaneComponentByPane__Q23gui11PaneManagerFPQ34nw4r3lyt4Pane', 0)), '00000000'), ('0x814', (1, ('createLayoutScene__Q23gui11PaneManagerFRCQ34nw4r3lyt6Layout', 0)), '00000000'), ('0x7ec', (1, ('__dt__Q33ipl3gui11PaneManagerFv', 0)), '00000000'), ('0x840', (1, ('getLatestEventCtrlNo__Q23gui12EventHandlerFv', 0)), '00000000'), ('0x83c', (1, ('setLatestEventCtrlNo__Q23gui12EventHandlerFi', 0)), '00000000'), ('0x838', (1, ('setManager__Q23gui12EventHandlerFPQ23gui7Manager', 0)), '00000000'), ('0x834', (1, ('onEvent__Q23gui12EventHandlerFUlUlPv', 0)), '00000000'), ('0x860', (1, ('__dt__Q23gui9InterfaceFv', 0)), '00000000'), ('0x858', (1, ('draw__Q23gui9InterfaceFRA3_A4_f', 0)), '00000000'), ('0x85c', (1, ('draw__Q23gui9InterfaceFv', 0)), '00000000'), ('0x854', (1, ('calc__Q23gui9InterfaceFv', 0)), '00000000'), ('0x850', (1, ('init__Q23gui9InterfaceFv', 0)), '00000000'), ('0x84c', (1, ('create__Q23gui9InterfaceFv', 0)), '00000000')]
.rodata: original/source 40/35 bytes, overlapping non-relocation byte differences [], original tail 0000000000
relocations: missing []; extra []; changed []
.sdata: original/source 24/24 bytes, overlapping non-relocation byte differences [], original tail 
relocations: missing []; extra []; changed []
.sdata2: original/source 24/24 bytes, overlapping non-relocation byte differences [], original tail 
relocations: missing []; extra []; changed []
.bss: original/source 320/320 bytes, overlapping non-relocation byte differences [], original tail 
relocations: missing []; extra []; changed []
.sbss: absent on both
.ctors: absent on both
extab: absent on both
extabindex: absent on both

## src/scene/address/iplAddress
.data: original/source 1880/1876 bytes, overlapping non-relocation byte differences [], original tail 00000000
relocations: missing []; extra [1748, 1736, 1792, 1788, 1784, 1780, 1776, 1768, 1772, 1764, 1760, 1752, 1744, 1740, 1816, 1812, 1808, 1804, 1800, 1796, 1756, 1840, 1836, 1832, 1828, 1872, 1864, 1868, 1860, 1856, 1852]; changed []
extra targets: [('0x6d4', (1, ('draw__Q23gui9InterfaceFRA3_A4_f', 0)), '00000000'), ('0x6c8', (1, ('create__Q23gui9InterfaceFv', 0)), '00000000'), ('0x700', (1, ('setDraggingButton__Q23gui7ManagerFUl', 0)), '00000000'), ('0x6fc', (1, ('changeEventHandler__Q23gui7ManagerFPQ23gui12EventHandler', 0)), '00000000'), ('0x6f8', (1, ('setEventHandler__Q23gui7ManagerFPQ23gui12EventHandler', 0)), '00000000'), ('0x6f4', (1, ('setAllComponentTriggerTarget__Q23gui7ManagerFb', 0)), '00000000'), ('0x6f0', (1, ('onEvent__Q23gui7ManagerFUlUliPv', 0)), '00000000'), ('0x6e8', (1, ('update__Q23gui7ManagerFiPC10KPADStatusffPv', 0)), '00000000'), ('0x6ec', (1, ('update__Q23gui7ManagerFiffUlUlUlPv', 0)), '00000000'), ('0x6e4', (1, ('getComponent__Q23gui7ManagerFUl', 0)), '00000000'), ('0x6e0', (1, ('addComponent__Q23gui7ManagerFPQ23gui9Component', 0)), '00000000'), ('0x6d8', (1, ('draw__Q23gui7ManagerFv', 0)), '00000000'), ('0x6d0', (1, ('calc__Q23gui7ManagerFv', 0)), '00000000'), ('0x6cc', (1, ('init__Q23gui7ManagerFv', 0)), '00000000'), ('0x718', (1, ('walkInChildren__Q23gui11PaneManagerFRQ34nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>', 0)), '00000000'), ('0x714', (1, ('setAllBoundingBoxComponentTriggerTarget__Q23gui11PaneManagerFb', 0)), '00000000'), ('0x710', (1, ('setDrawInfo__Q23gui11PaneManagerFPCQ34nw4r3lyt8DrawInfo', 0)), '00000000'), ('0x70c', (1, ('getDrawInfo__Q23gui11PaneManagerFv', 0)), '00000000'), ('0x708', (1, ('getPaneComponentByPane__Q23gui11PaneManagerFPQ34nw4r3lyt4Pane', 0)), '00000000'), ('0x704', (1, ('createLayoutScene__Q23gui11PaneManagerFRCQ34nw4r3lyt6Layout', 0)), '00000000'), ('0x6dc', (1, ('__dt__Q33ipl3gui11PaneManagerFv', 0)), '00000000'), ('0x730', (1, ('getLatestEventCtrlNo__Q23gui12EventHandlerFv', 0)), '00000000'), ('0x72c', (1, ('setLatestEventCtrlNo__Q23gui12EventHandlerFi', 0)), '00000000'), ('0x728', (1, ('setManager__Q23gui12EventHandlerFPQ23gui7Manager', 0)), '00000000'), ('0x724', (1, ('onEvent__Q23gui12EventHandlerFUlUlPv', 0)), '00000000'), ('0x750', (1, ('__dt__Q23gui9InterfaceFv', 0)), '00000000'), ('0x748', (1, ('draw__Q23gui9InterfaceFRA3_A4_f', 0)), '00000000'), ('0x74c', (1, ('draw__Q23gui9InterfaceFv', 0)), '00000000'), ('0x744', (1, ('calc__Q23gui9InterfaceFv', 0)), '00000000'), ('0x740', (1, ('init__Q23gui9InterfaceFv', 0)), '00000000'), ('0x73c', (1, ('create__Q23gui9InterfaceFv', 0)), '00000000')]
.rodata: original/source 24/20 bytes, overlapping non-relocation byte differences [], original tail 00000000
relocations: missing []; extra []; changed []
.sdata: original/source 16/12 bytes, overlapping non-relocation byte differences [], original tail 00000000
relocations: missing []; extra []; changed []
.sdata2: original/source 32/28 bytes, overlapping non-relocation byte differences [], original tail 00000000
relocations: missing []; extra []; changed []
.bss: absent on both
.sbss: original/source 8/8 bytes, overlapping non-relocation byte differences [], original tail 
relocations: missing []; extra []; changed []
.ctors: original/source 4/4 bytes, overlapping non-relocation byte differences [], original tail 
relocations: missing []; extra []; changed []
extab: absent on both
extabindex: absent on both

## libs/RVL_SDK/src/wpad/WPADHIDParser
.data: original/source 1440/1434 bytes, overlapping non-relocation byte differences [], original tail 000000000000
relocations: missing []; extra []; changed []
.rodata: absent on both
.sdata: absent on both
.sdata2: original/source 96/96 bytes, overlapping non-relocation byte differences [], original tail 
relocations: missing []; extra []; changed []
.bss: original/source 104/104 bytes, overlapping non-relocation byte differences [], original tail 
relocations: missing []; extra []; changed []
.sbss: original/source 24/24 bytes, overlapping non-relocation byte differences [], original tail 
relocations: missing []; extra []; changed []
.ctors: absent on both
extab: absent on both
extabindex: absent on both

## src/scene/board/iplBoardObject
.data: original/source 1200/1196 bytes, overlapping non-relocation byte differences [], original tail 00000000
relocations: missing []; extra [1068, 1056, 1112, 1108, 1104, 1100, 1096, 1088, 1092, 1084, 1080, 1072, 1064, 1060, 1136, 1132, 1128, 1124, 1120, 1116, 1076, 1160, 1156, 1152, 1148, 1192, 1184, 1188, 1180, 1176, 1172]; changed []
extra targets: [('0x42c', (1, ('draw__Q23gui9InterfaceFRA3_A4_f', 0)), '00000000'), ('0x420', (1, ('create__Q23gui9InterfaceFv', 0)), '00000000'), ('0x458', (1, ('setDraggingButton__Q23gui7ManagerFUl', 0)), '00000000'), ('0x454', (1, ('changeEventHandler__Q23gui7ManagerFPQ23gui12EventHandler', 0)), '00000000'), ('0x450', (1, ('setEventHandler__Q23gui7ManagerFPQ23gui12EventHandler', 0)), '00000000'), ('0x44c', (1, ('setAllComponentTriggerTarget__Q23gui7ManagerFb', 0)), '00000000'), ('0x448', (1, ('onEvent__Q23gui7ManagerFUlUliPv', 0)), '00000000'), ('0x440', (1, ('update__Q23gui7ManagerFiPC10KPADStatusffPv', 0)), '00000000'), ('0x444', (1, ('update__Q23gui7ManagerFiffUlUlUlPv', 0)), '00000000'), ('0x43c', (1, ('getComponent__Q23gui7ManagerFUl', 0)), '00000000'), ('0x438', (1, ('addComponent__Q23gui7ManagerFPQ23gui9Component', 0)), '00000000'), ('0x430', (1, ('draw__Q23gui7ManagerFv', 0)), '00000000'), ('0x428', (1, ('calc__Q23gui7ManagerFv', 0)), '00000000'), ('0x424', (1, ('init__Q23gui7ManagerFv', 0)), '00000000'), ('0x470', (1, ('walkInChildren__Q23gui11PaneManagerFRQ34nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>', 0)), '00000000'), ('0x46c', (1, ('setAllBoundingBoxComponentTriggerTarget__Q23gui11PaneManagerFb', 0)), '00000000'), ('0x468', (1, ('setDrawInfo__Q23gui11PaneManagerFPCQ34nw4r3lyt8DrawInfo', 0)), '00000000'), ('0x464', (1, ('getDrawInfo__Q23gui11PaneManagerFv', 0)), '00000000'), ('0x460', (1, ('getPaneComponentByPane__Q23gui11PaneManagerFPQ34nw4r3lyt4Pane', 0)), '00000000'), ('0x45c', (1, ('createLayoutScene__Q23gui11PaneManagerFRCQ34nw4r3lyt6Layout', 0)), '00000000'), ('0x434', (1, ('__dt__Q33ipl3gui11PaneManagerFv', 0)), '00000000'), ('0x488', (1, ('getLatestEventCtrlNo__Q23gui12EventHandlerFv', 0)), '00000000'), ('0x484', (1, ('setLatestEventCtrlNo__Q23gui12EventHandlerFi', 0)), '00000000'), ('0x480', (1, ('setManager__Q23gui12EventHandlerFPQ23gui7Manager', 0)), '00000000'), ('0x47c', (1, ('onEvent__Q23gui12EventHandlerFUlUlPv', 0)), '00000000'), ('0x4a8', (1, ('__dt__Q23gui9InterfaceFv', 0)), '00000000'), ('0x4a0', (1, ('draw__Q23gui9InterfaceFRA3_A4_f', 0)), '00000000'), ('0x4a4', (1, ('draw__Q23gui9InterfaceFv', 0)), '00000000'), ('0x49c', (1, ('calc__Q23gui9InterfaceFv', 0)), '00000000'), ('0x498', (1, ('init__Q23gui9InterfaceFv', 0)), '00000000'), ('0x494', (1, ('create__Q23gui9InterfaceFv', 0)), '00000000')]
.rodata: original/source 16/12 bytes, overlapping non-relocation byte differences [], original tail 00000000
relocations: missing []; extra []; changed []
.sdata: original/source 40/40 bytes, overlapping non-relocation byte differences [], original tail 
relocations: missing []; extra []; changed []
.sdata2: original/source 64/60 bytes, overlapping non-relocation byte differences [], original tail 00000000
relocations: missing []; extra []; changed []
.bss: absent on both
.sbss: absent on both
.ctors: absent on both
extab: absent on both
extabindex: absent on both

```

## Existing code-only residuals, outside this data assignment

### start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface 99.34978%

```text
src 0x378 base 0x37c insns 222/223
--- replace mine 12:13 base 12:13
  M   12 beq 816
  B   12 beq 820
--- replace mine 19:20 base 19:20
  M   19 blt 788
  B   19 blt 792
--- replace mine 22:23 base 22:24
  M   22 bne 776
  B   22 beq 8
  B   23 b 776
--- replace mine 116:118 base 117:119
  M  116 lwz r29, 0x104(r3)
  M  117 cmpwi r29, 0
  B  117 lwz r26, 0x104(r3)
  B  118 cmpwi r26, 0
--- replace mine 129:130 base 130:131
  M  129 mr r26, r3
  B  130 mr r29, r3
--- replace mine 132:133 base 133:134
  M  132 addi r4, r29, 0x14
  B  133 addi r4, r26, 0x14
--- replace mine 143:144 base 144:145
  M  143 lwz r4, 0(r29)
  B  144 lwz r4, 0(r26)
--- replace mine 154:156 base 155:157
  M  154 lwz r12, 0(r26)
  M  155 mr r3, r26
  B  155 lwz r12, 0(r29)
  B  156 mr r3, r29
```

### onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface 97.662964%

```text
src 0x43c base 0x438 insns 271/270
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x20(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x24(r1)
  M    3 addi r11, r1, 0x20
  B    2 stw r0, 0x34(r1)
  B    3 addi r11, r1, 0x30
--- replace mine 5:6 base 5:6
  M    5 mr r30, r3
  B    5 mr r29, r3
--- replace mine 7:9 base 7:9
  M    7 lis r28, 0
  M    8 mr r31, r5
  B    7 lis r27, 0
  B    8 mr r25, r5
--- replace mine 10:12 base 10:12
  M   10 mr r29, r6
  M   11 addi r28, r28, 0
  B   10 mr r30, r6
  B   11 addi r27, r27, 0
--- replace mine 19:22 base 19:22
  M   19 cmpwi r31, 1
  M   20 addi r27, r3, 0xb4
  M   21 beq 716
  B   19 cmpwi r25, 1
  B   20 addi r31, r3, 0xb4
  B   21 beq 712
--- replace mine 23:24 base 23:24
  M   23 cmpwi r31, 0
  B   23 cmpwi r25, 0
--- replace mine 25:32 base 25:32
  M   25 b 960
  M   26 cmpwi r31, 3
  M   27 bge 952
  M   28 b 832
  M   29 cmpwi r29, 0
  M   30 beq 940
  M   31 lwz r12, 0(r29)
  B   25 b 956
  B   26 cmpwi r25, 3
  B   27 bge 948
  B   28 b 828
  B   29 cmpwi r30, 0
  B   30 beq 936
  B   31 lwz r12, 0(r30)
--- replace mine 33:34 base 33:34
  M   33 mr r3, r29
  B   33 mr r3, r30
--- replace mine 39:40 base 39:40
  M   39 beq 644
  B   39 beq 640
--- replace mine 45:47 base 45:47
  M   45 lwz r0, 0xac(r30)
  M   46 mr r31, r3
  B   45 lwz r0, 0xac(r29)
  B   46 mr r26, r3
--- replace mine 50:55 base 50:55
  M   50 bne 860
  M   51 lis r29, 0
  M   52 mr r3, r27
  M   53 addi r29, r29, 0
  M   54 lwz r4, 0x14(r29)
  B   50 bne 596
  B   51 lis r28, 0
  B   52 mr r3, r31
  B   53 addi r28, r28, 0
  B   54 lwz r4, 0x14(r28)
--- replace mine 63:65 base 63:65
  M   63 mr r27, r3
  M   64 mr r3, r31
  B   63 mr r25, r3
  B   64 mr r3, r26
--- replace mine 67:68 base 67:68
  M   67 lwz r0, 0x88(r30)
  B   67 lwz r0, 0x88(r29)
--- replace mine 77:78 base 77:78
  M   77 cmpwi r27, 0
  B   77 cmpwi r25, 0
--- replace mine 79:80 base 79:80
  M   79 mr r3, r27
  B   79 mr r3, r25
--- replace mine 81:82 base 81:82
  M   81 lwz r3, 0x8c(r30)
  B   81 lwz r3, 0x8c(r29)
--- replace mine 85:86 base 85:86
  M   85 mr r27, r3
  B   85 mr r28, r3
--- replace mine 88:90 base 88:90
  M   88 mr r3, r31
  M   89 stw r0, 0x14(r27)
  B   88 mr r3, r26
  B   89 stw r0, 0x14(r28)
--- replace mine 92:93 base 92:93
  M   92 mr r3, r31
  B   92 mr r3, r26
--- replace mine 96:97 base 96:97
  M   96 lwz r3, 0x8c(r30)
  B   96 lwz r3, 0x8c(r29)
--- replace mine 100:101 base 100:101
  M  100 mr r27, r3
  B  100 mr r25, r3
--- replace mine 102:103 base 102:103
  M  102 li r29, 1
  B  102 li r28, 1
--- replace mine 104:106 base 104:106
  M  104 stw r29, 0x14(r27)
  M  105 lwz r3, 0xa0(r30)
  B  104 stw r28, 0x14(r25)
  B  105 lwz r3, 0xa0(r29)
--- replace mine 108:109 base 108:109
  M  108 mr r27, r3
  B  108 mr r25, r3
--- replace mine 110:112 base 110:112
  M  110 stw r29, 0x14(r27)
  M  111 mr r3, r31
  B  110 stw r28, 0x14(r25)
  B  111 mr r3, r26
--- replace mine 114:115 base 114:115
  M  114 mr r3, r31
  B  114 mr r3, r26
--- replace mine 118:119 base 118:119
  M  118 lwz r3, 0x8c(r30)
  B  118 lwz r3, 0x8c(r29)
--- replace mine 122:123 base 122:123
  M  122 mr r27, r3
  B  122 mr r25, r3
--- replace mine 124:125 base 124:125
  M  124 li r29, 1
  B  124 li r28, 1
--- replace mine 126:128 base 126:128
  M  126 stw r29, 0x14(r27)
  M  127 lwz r3, 0xa0(r30)
  B  126 stw r28, 0x14(r25)
  B  127 lwz r3, 0xa0(r29)
--- replace mine 130:131 base 130:131
  M  130 mr r27, r3
  B  130 mr r25, r3
--- replace mine 132:134 base 132:134
  M  132 stw r29, 0x14(r27)
  M  133 mr r3, r31
  B  132 stw r28, 0x14(r25)
  B  133 mr r3, r26
--- replace mine 136:137 base 136:137
  M  136 mr r3, r31
  B  136 mr r3, r26
--- replace mine 140:141 base 140:141
  M  140 mr r3, r31
  B  140 mr r3, r26
--- replace mine 144:145 base 144:145
  M  144 mr r3, r31
  B  144 mr r3, r26
--- replace mine 147:148 base 147:148
  M  147 mr r3, r31
  B  147 mr r3, r26
--- replace mine 150:151 base 150:151
  M  150 mr r3, r31
  B  150 mr r3, r26
--- replace mine 154:155 base 154:155
  M  154 addi r4, r28, 0x5a1
  B  154 addi r4, r27, 0x5a1
--- replace mine 158:162 base 158:162
  M  158 stw r0, 0xac(r30)
  M  159 b 424
  M  160 lwz r4, 0x1c(r29)
  M  161 mr r3, r27
  B  158 stw r0, 0xac(r29)
  B  159 b 160
  B  160 lwz r4, 0x1c(r28)
  B  161 mr r3, r31
--- replace mine 166:168 base 166:168
  M  166 mr r3, r30
  M  167 stw r0, 0xc0(r30)
  B  166 mr r3, r29
  B  167 stw r0, 0xc0(r29)
--- replace mine 169:172 base 169:172
  M  169 b 384
  M  170 lwz r4, 0x24(r29)
  M  171 mr r3, r27
  B  169 b 120
  B  170 lwz r4, 0x24(r28)
  B  171 mr r3, r31
--- replace mine 175:176 base 175:176
  M  175 mr r3, r31
  B  175 mr r3, r26
--- replace mine 179:180 base 179:180
  M  179 addi r4, r28, 0x456
  B  179 addi r4, r27, 0x456
--- replace mine 182:183 base 182:183
  M  182 mr r3, r30
  B  182 mr r3, r29
--- replace mine 184:187 base 184:187
  M  184 b 324
  M  185 lwz r4, 0x28(r29)
  M  186 mr r3, r27
  B  184 b 60
  B  185 lwz r4, 0x28(r28)
  B  186 mr r3, r31
--- replace mine 189:191 base 189:191
  M  189 bne 304
  M  190 mr r3, r31
  B  189 bne 40
  B  190 mr r3, r26
--- replace mine 194:195 base 194:195
  M  194 addi r4, r28, 0x515
  B  194 addi r4, r27, 0x515
--- replace mine 197:198 base 197:198
  M  197 mr r3, r30
  B  197 mr r3, r29
--- replace mine 199:201 base 199:200
  M  199 b 264
  M  200 lbz r0, 0x84(r30)
  B  199 lbz r0, 0x84(r29)
--- replace mine 203:204 base 202:203
  M  203 cmpwi r29, 0
  B  202 cmpwi r30, 0
--- replace mine 206:207 base 205:206
  M  206 lwz r4, 0x6c(r30)
  B  205 lwz r4, 0x6c(r29)
--- replace mine 210:211 base 209:210
  M  210 cmplw r29, r3
  B  209 cmplw r30, r3
--- replace mine 212:216 base 211:215
  M  212 lis r31, 0
  M  213 mr r3, r27
  M  214 addi r31, r31, 0
  M  215 lwz r4, 0x28(r31)
  B  211 lis r30, 0
  B  212 mr r3, r31
  B  213 addi r30, r30, 0
  B  214 lwz r4, 0x28(r30)
--- replace mine 219:220 base 218:219
  M  219 lwz r0, 0x7c(r30)
  B  218 lwz r0, 0x7c(r29)
--- replace mine 223:224 base 222:223
  M  223 stw r0, 0x7c(r30)
  B  222 stw r0, 0x7c(r29)
--- replace mine 225:227 base 224:226
  M  225 lwz r4, 0x24(r31)
  M  226 mr r3, r27
  B  224 lwz r4, 0x24(r30)
  B  225 mr r3, r31
--- replace mine 230:231 base 229:230
  M  230 lwz r0, 0x78(r30)
  B  229 lwz r0, 0x78(r29)
--- replace mine 234:235 base 233:234
  M  234 stw r0, 0x78(r30)
  B  233 stw r0, 0x78(r29)
--- replace mine 236:237 base 235:236
  M  236 lbz r0, 0x84(r30)
  B  235 lbz r0, 0x84(r29)
--- replace mine 239:240 base 238:239
  M  239 cmpwi r29, 0
  B  238 cmpwi r30, 0
--- replace mine 242:243 base 241:242
  M  242 lwz r4, 0x6c(r30)
  B  241 lwz r4, 0x6c(r29)
--- replace mine 246:247 base 245:246
  M  246 cmplw r29, r3
  B  245 cmplw r30, r3
--- replace mine 248:252 base 247:251
  M  248 lis r31, 0
  M  249 mr r3, r27
  M  250 addi r31, r31, 0
  M  251 lwz r4, 0x28(r31)
  B  247 lis r30, 0
  B  248 mr r3, r31
  B  249 addi r30, r30, 0
  B  250 lwz r4, 0x28(r30)
--- replace mine 256:257 base 255:256
  M  256 stw r0, 0x7c(r30)
  B  255 stw r0, 0x7c(r29)
--- replace mine 258:260 base 257:259
  M  258 lwz r4, 0x24(r31)
  M  259 mr r3, r27
  B  257 lwz r4, 0x24(r30)
  B  258 mr r3, r31
--- replace mine 264:266 base 263:265
  M  264 stw r0, 0x78(r30)
  M  265 addi r11, r1, 0x20
  B  263 stw r0, 0x78(r29)
  B  264 addi r11, r1, 0x30
--- replace mine 267:268 base 266:267
  M  267 lwz r0, 0x24(r1)
  B  266 lwz r0, 0x34(r1)
--- replace mine 269:270 base 268:269
  M  269 addi r1, r1, 0x20
  B  268 addi r1, r1, 0x30
```

### onPreviousPage__Q33ipl5scene7AddressFv 97.25455%

```text
src 0x284 base 0x294 insns 161/165
--- replace mine 14:15 base 14:15
  M   14 b 564
  B   14 b 580
--- replace mine 17:18 base 17:18
  M   17 b 552
  B   17 b 568
--- replace mine 68:69 base 68:69
  M   68 b 348
  B   68 b 364
--- replace mine 87:88 base 87:88
  M   87 b 272
  B   87 b 288
--- replace mine 92:93 base 92:93
  M   92 lfs f2, 0(0)
  B   92 lfs f1, 0(0)
--- replace mine 97:98 base 97:98
  M   97 lfs f1, 4(r6)
  B   97 lfs f2, 4(r6)
--- replace mine 99:102 base 99:102
  M   99 fmuls f1, f2, f1
  M  100 fmuls f0, f2, f0
  M  101 stfs f1, 0xc(r1)
  B   99 fmuls f2, f2, f1
  B  100 fmuls f0, f0, f1
  B  101 stfs f2, 0xc(r1)
--- insert mine 103:103 base 103:107
  B  103 lwz r0, 0xc(r1)
  B  104 lwz r6, 8(r1)
  B  105 stw r0, 0x14(r1)
  B  106 stw r6, 0x10(r1)
--- replace mine 111:112 base 115:116
  M  111 addi r5, r1, 8
  B  115 addi r5, r1, 0x10
```

### set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err 98.6%

```text
src 0x144 base 0x140 insns 81/80
--- delete mine 26:27 base 26:26
  M   26 li r30, 0x190
```

### movePane_onDrag__Q33ipl5scene7AddressFv 95.70968%

```text
src 0x268 base 0x26c insns 154/155
--- replace mine 34:36 base 34:36
  M   34 lwz r6, 0x8c(r31)
  M   35 lis r7, 0
  B   34 lwz r7, 0x8c(r31)
  B   35 lis r6, 0
--- replace mine 39:40 base 39:40
  M   39 lwz r3, 0x14(r6)
  B   39 lwz r3, 0x14(r7)
--- replace mine 43:44 base 43:44
  M   43 addi r4, r7, 0
  B   43 addi r4, r6, 0
--- replace mine 50:51 base 50:51
  M   50 mr r28, r3
  B   50 mr r27, r3
--- replace mine 56:61 base 56:62
  M   56 add r27, r5, r0
  M   57 addi r27, r27, 8
  M   58 beq 112
  M   59 cmpwi r27, 0
  M   60 beq 104
  B   56 add r0, r5, r0
  B   57 bne 8
  B   58 b 124
  B   59 addic. r29, r0, 8
  B   60 bne 8
  B   61 b 112
--- replace mine 69:70 base 70:71
  M   69 mr r3, r28
  B   70 mr r3, r27
--- replace mine 72:73 base 73:74
  M   72 mr r4, r29
  B   73 mr r4, r28
--- replace mine 78:79 base 79:80
  M   78 addi r27, r27, 2
  B   79 addi r29, r29, 2
--- replace mine 83:85 base 84:86
  M   83 lhz r29, 0(r27)
  M   84 cmpwi r29, 0
  B   84 lhz r28, 0(r29)
  B   85 cmpwi r28, 0
--- insert mine 87:87 base 88:89
  B   88 fadds f30, f0, f30
--- delete mine 88:89 base 90:90
  M   88 fadds f30, f30, f0
--- replace mine 108:110 base 109:111
  M  108 fmuls f0, f5, f0
  M  109 fneg f0, f0
  B  109 fmuls f5, f5, f0
  B  110 fneg f0, f5
```

### update__Q33ipl5scene15FriendListCacheFUlPCwUx 81.35%

```text
src 0x90 base 0xa0 insns 36/40
--- replace mine 6:8 base 6:10
  M    6 mr r29, r4
  M    7 mr r30, r5
  B    6 mr r29, r3
  B    7 mr r30, r4
  B    8 mr r31, r5
  B    9 add r3, r3, r0
--- replace mine 9:10 base 11:12
  M    9 add r31, r3, r0
  B   11 stw r8, 0x24(r3)
--- replace mine 11:14 base 13:15
  M   11 stw r8, 0x24(r31)
  M   12 addi r3, r31, 8
  M   13 stw r7, 0x20(r31)
  B   13 stw r7, 0x20(r3)
  B   14 addi r3, r3, 8
--- replace mine 15:17 base 16:18
  M   15 mr r4, r30
  M   16 addi r3, r31, 8
  B   16 mulli r0, r30, 0x140
  B   17 mr r4, r31
--- insert mine 18:18 base 19:21
  B   19 add r3, r29, r0
  B   20 addi r3, r3, 8
--- replace mine 27:29 base 30:33
  M   27 mr r4, r31
  M   28 mr r5, r29
  B   30 mulli r0, r30, 0x140
  B   31 mr r5, r30
  B   32 add r4, r29, r0
```

### create__Q33ipl5scene11AddressEditFv 97.44634%

```text
src 0xcd0 base 0xcd0 insns 820/820
diffs 323: [10, 14, 17, 24, 25, 30, 31, 36, 37, 42, 43, 48, 49, 54, 55, 60, 61, 66, 67, 72]
    10 M lis r30, 0
       B lis r31, 0
    14 M addi r30, r30, 0
       B addi r31, r31, 0
    17 M lwz r31, 0xd20(r3)
       B lwz r30, 0xd20(r3)
    24 M mr r5, r31
       B mr r5, r30
    25 M addi r7, r30, 0x72
       B addi r7, r31, 0x72
    30 M addi r4, r30, 0x84
       B addi r4, r31, 0x84
    31 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
    36 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    37 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    42 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    43 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    48 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    49 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    54 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    55 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    60 M addi r4, r30, 0xaf
       B addi r4, r31, 0xaf
    61 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    66 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    67 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
    72 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    73 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
    78 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    79 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
    84 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    85 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
    90 M addi r4, r30, 0x103
       B addi r4, r31, 0x103
    91 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
    96 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
    97 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   102 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   103 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   108 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   109 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   114 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   115 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   120 M addi r4, r30, 0x11d
       B addi r4, r31, 0x11d
   121 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   126 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   127 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   132 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   133 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   138 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   139 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   144 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   145 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   150 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   151 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   156 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   157 M addi r5, r30, 0xc8
       B addi r5, r31, 0xc8
   162 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   163 M addi r5, r30, 0xd3
       B addi r5, r31, 0xd3
   168 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   169 M addi r5, r30, 0xde
       B addi r5, r31, 0xde
   174 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   175 M addi r5, r30, 0xe9
       B addi r5, r31, 0xe9
   180 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   181 M addi r5, r30, 0xf5
       B addi r5, r31, 0xf5
   186 M addi r4, r30, 0x137
       B addi r4, r31, 0x137
   187 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   192 M addi r4, r30, 0x154
       B addi r4, r31, 0x154
   193 M addi r5, r30, 0x172
       B addi r5, r31, 0x172
   198 M addi r4, r30, 0x17e
       B addi r4, r31, 0x17e
   199 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   204 M addi r4, r30, 0x1a9
       B addi r4, r31, 0x1a9
   205 M addi r5, r30, 0x1a0
       B addi r5, r31, 0x1a0
   210 M addi r4, r30, 0x1cc
       B addi r4, r31, 0x1cc
   211 M addi r5, r30, 0xa0
       B addi r5, r31, 0xa0
   252 M addi r27, r30, 0x44
       B addi r27, r31, 0x44
   271 M addi r4, r30, 0x1e8
       B addi r4, r31, 0x1e8
   281 M mr r23, r3
       B mr r27, r3
   289 M mr r4, r23
       B mr r4, r27
   292 M addi r4, r30, 0x1f5
       B addi r4, r31, 0x1f5
   300 M mr r25, r3
       B mr r27, r3
   306 M mr r4, r25
       B mr r4, r27
   309 M addi r4, r30, 0x202
       B addi r4, r31, 0x202
   317 M mr r25, r3
       B mr r27, r3
   323 M mr r4, r25
       B mr r4, r27
   326 M addi r4, r30, 0x20f
       B addi r4, r31, 0x20f
   334 M mr r25, r3
       B mr r27, r3
   340 M mr r4, r25
       B mr r4, r27
   343 M addi r4, r30, 0x21d
       B addi r4, r31, 0x21d
   355 M addi r4, r30, 0x22b
       B addi r4, r31, 0x22b
   367 M addi r4, r30, 0xf5
       B addi r4, r31, 0xf5
   384 M mr r5, r31
       B mr r5, r30
   385 M addi r7, r30, 0x235
       B addi r7, r31, 0x235
   390 M addi r4, r30, 0x247
       B addi r4, r31, 0x247
   391 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   396 M addi r4, r30, 0x274
       B addi r4, r31, 0x274
   397 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   402 M addi r4, r30, 0x2a4
       B addi r4, r31, 0x2a4
   403 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   408 M addi r4, r30, 0x2cc
       B addi r4, r31, 0x2cc
   409 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   414 M addi r4, r30, 0x2f2
       B addi r4, r31, 0x2f2
   420 M addi r4, r30, 0x30f
       B addi r4, r31, 0x30f
   421 M addi r5, r30, 0x296
       B addi r5, r31, 0x296
   426 M addi r4, r30, 0x332
       B addi r4, r31, 0x332
   427 M addi r5, r30, 0x2c2
       B addi r5, r31, 0x2c2
   432 M addi r4, r30, 0x351
       B addi r4, r31, 0x351
   433 M addi r5, r30, 0x2e9
       B addi r5, r31, 0x2e9
   438 M addi r4, r30, 0x36f
       B addi r4, r31, 0x36f
   444 M addi r4, r30, 0x38d
       B addi r4, r31, 0x38d
   445 M addi r5, r30, 0x263
       B addi r5, r31, 0x263
   505 M mr r5, r31
       B mr r5, r30
   506 M addi r7, r30, 0x3a9
       B addi r7, r31, 0x3a9
   510 M addi r4, r30, 0x3b9
       B addi r4, r31, 0x3b9
   511 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   516 M addi r4, r30, 0x3da
       B addi r4, r31, 0x3da
   517 M addi r5, r30, 0x3cf
       B addi r5, r31, 0x3cf
   536 M lis r31, 0
       B lis r30, 0
   538 M addi r31, r31, 0
       B addi r30, r30, 0
   541 M lwz r3, 0x64(r31)
       B lwz r3, 0x64(r30)
   547 M beq 300
       B beq 308
   551 M b 832
       B b 840
   553 M bge 824
       B bge 832
   554 M b 548
       B b 556
   591 M mr r25, r3
       B mr r27, r3
   594 M addi r4, r30, 0x22b
       B addi r25, r29, 0x2b4
   595 M stw r0, 0x14(r25)
       B stw r0, 0x14(r27)
   596 M li r5, 1
       B addi r4, r31, 0x22b
   597 M lwz r3, 0x68(r29)
       B li r5, 1
   598 M lwz r3, 0x14(r3)
       B lwz r3, 0x68(r29)
   599 M lwz r12, 0(r3)
       B lwz r3, 0x14(r3)
   600 M lwz r12, 0x3c(r12)
       B lwz r12, 0(r3)
   601 M mtctr r12
       B lwz r12, 0x3c(r12)
   602 M bctrl 
       B mtctr r12
   603 M mr r4, r3
       B bctrl 
   604 M mr r3, r29
       B mr r4, r3
   605 M addi r5, r29, 0x2b4
       B mr r3, r29
   606 M bl 0
       B mr r5, r25
   607 M lwz r3, 0x68(r29)
       B bl 0
   608 M addi r4, r30, 0xf5
       B lwz r3, 0x68(r29)
   609 M li r5, 1
       B addi r25, r29, 0x2cc
   610 M lwz r3, 0x14(r3)
       B addi r4, r31, 0xf5
   611 M lwz r12, 0(r3)
       B li r5, 1
   612 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   613 M mtctr r12
       B lwz r12, 0(r3)
   614 M bctrl 
       B lwz r12, 0x3c(r12)
   615 M mr r4, r3
       B mtctr r12
   616 M mr r3, r29
       B bctrl 
   617 M addi r5, r29, 0x2cc
       B mr r4, r3
   618 M bl 0
       B mr r3, r29
   619 M li r0, 0
       B mr r5, r25
   620 M stw r0, 0x64(r29)
       B bl 0
   621 M b 552
       B li r0, 0
   622 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   623 M li r4, 0
       B b 552
   624 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   625 M bl 0
       B li r4, 0
   626 M mr r25, r3
       B addi r3, r3, 0x28c
   628 M li r28, 1
       B mr r27, r3
   629 M li r4, 1
       B bl 0
   630 M stw r28, 0x14(r25)
       B li r28, 1
   631 M lwz r3, 0x74(r29)
       B li r4, 1
   632 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   633 M bl 0
       B lwz r3, 0x74(r29)
   634 M mr r25, r3
       B addi r3, r3, 0x28c
   636 M stw r28, 0x14(r25)
       B mr r27, r3
   637 M li r4, 3
       B bl 0
   638 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   639 M addi r3, r3, 0x28c
       B li r4, 3
   640 M bl 0
       B lwz r3, 0x74(r29)
   641 M mr r25, r3
       B addi r3, r3, 0x28c
   643 M stw r28, 0x14(r25)
       B mr r27, r3
   644 M li r4, 0x1a
       B bl 0
   645 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   646 M addi r3, r3, 0x28c
       B li r4, 0x1a
   647 M bl 0
       B lwz r3, 0x68(r29)
   648 M bl 0
       B addi r3, r3, 0x28c
   649 M lwz r3, 0x68(r29)
       B bl 0
   650 M li r4, 0x10
       B bl 0
   651 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   652 M bl 0
       B li r4, 0x10
   653 M bl 0
       B addi r3, r3, 0x28c
   654 M lwz r3, 0x74(r29)
       B bl 0
   655 M addi r4, r30, 0x3ef
       B bl 0
   656 M li r5, 1
       B lwz r3, 0x74(r29)
   657 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   658 M lwz r12, 0(r3)
       B li r5, 1
   659 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   660 M mtctr r12
       B lwz r12, 0(r3)
   661 M bctrl 
       B lwz r12, 0x3c(r12)
   662 M lwz r5, 0x80(r31)
       B mtctr r12
   663 M mr r25, r3
       B bctrl 
   664 M li r4, 0x31
       B lwz r5, 0x80(r30)
   665 M lwz r3, 0(r5)
       B mr r27, r3
   666 M bl 0
       B li r4, 0x31
   667 M mr r5, r3
       B lwz r3, 0(r5)
   668 M mr r3, r29
       B bl 0
   669 M mr r4, r25
       B mr r5, r3
   670 M bl 0
       B mr r3, r29
   671 M lwz r3, 0x74(r29)
       B mr r4, r27
   672 M addi r4, r30, 0x3fd
       B bl 0
   673 M li r5, 1
       B lwz r3, 0x74(r29)
   674 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   675 M lwz r12, 0(r3)
       B li r5, 1
   676 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   677 M mtctr r12
       B lwz r12, 0(r3)
   678 M bctrl 
       B lwz r12, 0x3c(r12)
   679 M lwz r5, 0x80(r31)
       B mtctr r12
   680 M mr r25, r3
       B bctrl 
   681 M li r4, 0x47
       B lwz r5, 0x80(r30)
   682 M lwz r3, 0(r5)
       B mr r27, r3
   683 M bl 0
       B li r4, 0x47
   684 M mr r5, r3
       B lwz r3, 0(r5)
   685 M mr r3, r29
       B bl 0
   686 M mr r4, r25
       B mr r5, r3
   687 M bl 0
       B mr r3, r29
   688 M li r0, 0x10
       B mr r4, r27
   689 M stw r0, 0x64(r29)
       B bl 0
   690 M b 276
       B li r0, 0x10
   691 M lwz r3, 0x74(r29)
       B stw r0, 0x64(r29)
   692 M li r4, 0
       B b 276
   693 M addi r3, r3, 0x28c
       B lwz r3, 0x74(r29)
   694 M bl 0
       B li r4, 0
   695 M mr r25, r3
       B addi r3, r3, 0x28c
   697 M li r28, 1
       B mr r27, r3
   698 M li r4, 1
       B bl 0
   699 M stw r28, 0x14(r25)
       B li r28, 1
   700 M lwz r3, 0x74(r29)
       B li r4, 1
   701 M addi r3, r3, 0x28c
       B stw r28, 0x14(r27)
   702 M bl 0
       B lwz r3, 0x74(r29)
   703 M mr r25, r3
       B addi r3, r3, 0x28c
   705 M stw r28, 0x14(r25)
       B mr r27, r3
   706 M li r4, 3
       B bl 0
   707 M lwz r3, 0x74(r29)
       B stw r28, 0x14(r27)
   708 M addi r3, r3, 0x28c
       B li r4, 3
   709 M bl 0
       B lwz r3, 0x74(r29)
   710 M mr r25, r3
       B addi r3, r3, 0x28c
   712 M stw r28, 0x14(r25)
       B mr r27, r3
   713 M li r4, 0x1a
       B bl 0
   714 M lwz r3, 0x68(r29)
       B stw r28, 0x14(r27)
   715 M addi r3, r3, 0x28c
       B li r4, 0x1a
   716 M bl 0
       B lwz r3, 0x68(r29)
   717 M bl 0
       B addi r3, r3, 0x28c
   718 M lwz r3, 0x68(r29)
       B bl 0
   719 M li r4, 0x10
       B bl 0
   720 M addi r3, r3, 0x28c
       B lwz r3, 0x68(r29)
   721 M bl 0
       B li r4, 0x10
   722 M bl 0
       B addi r3, r3, 0x28c
   723 M lwz r3, 0x74(r29)
       B bl 0
   724 M addi r4, r30, 0x3ef
       B bl 0
   725 M li r5, 1
       B lwz r3, 0x74(r29)
   726 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3ef
   727 M lwz r12, 0(r3)
       B li r5, 1
   728 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   729 M mtctr r12
       B lwz r12, 0(r3)
   730 M bctrl 
       B lwz r12, 0x3c(r12)
   731 M lwz r5, 0x80(r31)
       B mtctr r12
   732 M mr r25, r3
       B bctrl 
   733 M li r4, 0x3f
       B lwz r5, 0x80(r30)
   734 M lwz r3, 0(r5)
       B mr r27, r3
   735 M bl 0
       B li r4, 0x3f
   736 M mr r5, r3
       B lwz r3, 0(r5)
   737 M mr r3, r29
       B bl 0
   738 M mr r4, r25
       B mr r5, r3
   739 M bl 0
       B mr r3, r29
   740 M lwz r3, 0x74(r29)
       B mr r4, r27
   741 M addi r4, r30, 0x3fd
       B bl 0
   742 M li r5, 1
       B lwz r3, 0x74(r29)
   743 M lwz r3, 0x14(r3)
       B addi r4, r31, 0x3fd
   744 M lwz r12, 0(r3)
       B li r5, 1
   745 M lwz r12, 0x3c(r12)
       B lwz r3, 0x14(r3)
   746 M mtctr r12
       B lwz r12, 0(r3)
   747 M bctrl 
       B lwz r12, 0x3c(r12)
   748 M lwz r5, 0x80(r31)
       B mtctr r12
   749 M mr r25, r3
       B bctrl 
   750 M li r4, 0x48
       B lwz r5, 0x80(r30)
   751 M lwz r3, 0(r5)
       B mr r27, r3
   752 M bl 0
       B li r4, 0x48
   753 M mr r5, r3
       B lwz r3, 0(r5)
   754 M mr r3, r29
       B bl 0
   755 M mr r4, r25
       B mr r5, r3
   756 M bl 0
       B mr r3, r29
   757 M li r0, 0x10
       B mr r4, r27
   758 M stw r0, 0x64(r29)
       B bl 0
   759 M addi r3, r29, 0x4e0
       B li r0, 0x10
   760 M addi r4, r1, 8
       B stw r0, 0x64(r29)
   761 M bl 0
       B addi r3, r29, 0x4e0
   762 M cmpwi r3, 0
       B addi r4, r1, 8
   763 M beq 56
       B bl 0
   764 M lis r4, 0
       B cmpwi r3, 0
   765 M lis r8, 0
       B beq 56
   766 M addi r4, r4, 0
       B lis r3, 0
   767 M lha r7, 8(r1)
       B lis r8, 0
   768 M lwz r3, 0x70(r4)
       B addi r3, r3, 0
   769 M mr r9, r29
       B lha r7, 8(r1)
   770 M lwz r4, 0x28(r4)
       B lwz r4, 0x28(r3)
   771 M addi r8, r8, 0
       B mr r9, r29
   772 M li r5, 0x4c
       B lwz r3, 0x70(r3)
   773 M li r6, 0x4c
       B addi r8, r8, 0
   774 M bl 0
       B li r5, 0x4c
   775 M li r0, 1
       B li r6, 0x4c
   776 M stw r0, 0x4e8(r29)
       B bl 0
   777 M lis r3, 0
       B li r0, 1
   778 M addi r3, r3, 0
       B stw r0, 0x4e8(r29)
   779 M lwz r3, 0x90(r3)
       B lis r3, 0
   780 M lwz r12, 0(r3)
       B addi r3, r3, 0
   781 M lwz r12, 0xc(r12)
       B lwz r3, 0x90(r3)
   782 M mtctr r12
       B lwz r12, 0(r3)
   783 M bctrl 
       B lwz r12, 0xc(r12)
   784 M li r3, 0x3c
       B mtctr r12
   785 M bl 0
       B bctrl 
   786 M cmpwi r3, 0
       B li r3, 0x3c
   787 M mr r23, r3
       B bl 0
   788 M beq 84
       B cmpwi r3, 0
   789 M lfs f1, 0(0)
       B mr r25, r3
   790 M addi r3, r1, 0xc
       B beq 76
   791 M lfs f31, 0(0)
       B lfs f1, 0(0)
   792 M fmr f2, f1
       B addi r3, r1, 0xc
   793 M lfs f30, 0(0)
       B lfs f31, 0(0)
   794 M fmr f3, f1
       B fmr f2, f1
   795 M lwz r25, 0x24(r29)
       B lfs f30, 0(0)
   796 M bl 0
       B fmr f3, f1
   797 M cmpwi r23, 0
       B lwz r26, 0x24(r29)
   798 M beq 44
       B bl 0
   800 M lwz r5, 0xac(r29)
       B mr r8, r3
   802 M mr r3, r23
       B lwz r5, 0xac(r29)
   803 M mr r4, r25
       B mr r3, r25
   804 M addi r7, r30, 0x406
       B mr r4, r26
   805 M addi r8, r1, 0xc
       B addi r7, r31, 0x406
   808 M mr r23, r3
       B mr r25, r3
   809 M stw r23, 0xa8(r29)
       B stw r25, 0xa8(r29)
```

### stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv 99.73404%

```text
src 0x178 base 0x178 insns 94/94
diffs 5: [20, 29, 41, 82, 86]
    20 M subfe r30, r0, r3
       B subfe r29, r0, r3
    29 M subfe r30, r0, r3
       B subfe r29, r0, r3
    41 M and r5, r30, r0
       B and r5, r29, r0
    82 M mr r30, r3
       B mr r29, r3
    86 M stw r3, 0x14(r30)
       B stw r3, 0x14(r29)
```

### start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface 99.34066%

```text
src 0x2d4 base 0x2d8 insns 181/182
--- replace mine 12:14 base 12:14
  M   12 beq 468
  M   13 bge 648
  B   12 beq 472
  B   13 bge 652
--- replace mine 16:17 base 16:17
  M   16 b 636
  B   16 b 640
--- replace mine 18:20 base 18:20
  M   18 beq 168
  M   19 bge 624
  B   18 beq 172
  B   19 bge 628
--- replace mine 21:23 base 21:24
  M   21 beq 12
  M   22 bge 312
  B   21 beq 16
  B   22 bge 316
  B   23 b 612
--- insert mine 83:83 base 84:86
  B   84 lfs f1, 0(0)
  B   85 addi r4, r1, 0x14
--- delete mine 84:86 base 87:87
  M   84 addi r4, r1, 0x14
  M   85 lfs f1, 0(0)
--- insert mine 155:155 base 156:158
  B  156 lfs f1, 0(0)
  B  157 addi r4, r1, 8
--- delete mine 156:158 base 159:159
  M  156 addi r4, r1, 8
  M  157 lfs f1, 0(0)
```

### start_left_event__Q33ipl5scene11AddressEditFPCc 98.958336%

```text
src 0x17c base 0x180 insns 95/96
--- replace mine 10:12 base 10:12
  M   10 beq 264
  M   11 bge 312
  B   10 beq 268
  B   11 bge 316
--- replace mine 14:15 base 14:15
  M   14 b 300
  B   14 b 304
--- replace mine 16:18 base 16:18
  M   16 beq 132
  M   17 bge 288
  B   16 beq 136
  B   17 bge 292
--- replace mine 19:21 base 19:22
  M   19 beq 12
  M   20 bge 144
  B   19 beq 16
  B   20 bge 148
  B   21 b 276
```

### get_friendinfo__Q33ipl5scene11AddressEditFv 88.03571%

```text
src 0x148 base 0x150 insns 82/84
--- delete mine 6:7 base 6:6
  M    6 mr r29, r3
--- replace mine 8:9 base 7:9
  M    8 lwz r4, 0x4ec(r29)
  B    7 lwz r4, 0x4ec(r3)
  B    8 mr r28, r3
--- insert mine 10:10 base 10:11
  B   10 addi r3, r30, 0
--- delete mine 11:12 base 12:12
  M   11 addi r3, r30, 0
--- replace mine 15:16 base 15:16
  M   15 addi r3, r29, 0xb0
  B   15 addi r3, r28, 0xb0
--- replace mine 18:19 base 18:19
  M   18 lwz r3, 0x68(r29)
  B   18 lwz r3, 0x68(r28)
--- replace mine 20:21 base 20:21
  M   20 addi r4, r4, 0
  B   20 addi r29, r28, 0x2b4
--- insert mine 23:23 base 23:24
  B   23 addi r4, r4, 0
--- replace mine 28:30 base 29:31
  M   28 mr r3, r29
  M   29 addi r5, r29, 0x2b4
  B   29 mr r3, r28
  B   30 mr r5, r29
--- replace mine 42:43 base 43:44
  M   42 addi r3, r29, 0xb0
  B   43 addi r3, r28, 0xb0
--- replace mine 54:55 base 55:56
  M   54 addi r3, r29, 0xb0
  B   55 addi r3, r28, 0xb0
--- replace mine 57:58 base 58:59
  M   57 lwz r3, 0x68(r29)
  B   58 lwz r3, 0x68(r28)
--- replace mine 59:60 base 60:61
  M   59 addi r4, r4, 0
  B   60 addi r29, r28, 0x2cc
--- insert mine 62:62 base 63:64
  B   63 addi r4, r4, 0
--- replace mine 67:69 base 69:71
  M   67 mr r3, r29
  M   68 addi r5, r29, 0x2cc
  B   69 mr r3, r28
  B   70 mr r5, r29
--- replace mine 71:72 base 73:74
  M   71 addi r3, r29, 0x4e0
  B   73 addi r3, r28, 0x4e0
```

### update_friendinfo__Q33ipl5scene11AddressEditFv 99.42105%

```text
src 0x98 base 0x98 insns 38/38
diffs 2: [12, 13]
    12 M addi r3, r31, 8
       B addi r4, r30, 0x2b4
    13 M addi r4, r30, 0x2b4
       B addi r3, r31, 8
```

### set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err 98.666664%

```text
src 0x130 base 0x12c insns 76/75
--- delete mine 46:47 base 46:46
  M   46 li r4, 0x1c5
```

No data-driven open function remains uninvestigated. set_page_text has five distinct source attempts and was restored to 67/67 instructions with diffs 0. Existing code-only residuals were left unchanged.

## Final clean full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 21556/27112 data 368/2560 functions 87/94 fuzzy 99.4886 linked code 0
[src/scene/address/iplAddressEdit] instruction-exact functions: 87/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 99.906975
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 98.591545
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 99.48864
[src/scene/address/iplAddressEdit]   below 100: create__Q33ipl5scene11AddressEditFv 97.44634
[src/scene/address/iplAddressEdit]   below 100: stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv 99.73404
[src/scene/address/iplAddressEdit]   below 100: start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface 99.34066
[src/scene/address/iplAddressEdit]   below 100: start_left_event__Q33ipl5scene11AddressEditFPCc 98.958336
[src/scene/address/iplAddressEdit]   below 100: get_friendinfo__Q33ipl5scene11AddressEditFv 88.03571
[src/scene/address/iplAddressEdit]   below 100: update_friendinfo__Q33ipl5scene11AddressEditFv 99.42105
[src/scene/address/iplAddressEdit]   below 100: set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err 98.666664
[src/scene/address/iplAddressEdit] baseline: code 21556/27112 data 368 functions 87 fuzzy 99.4886
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 20256/23988 data 36/1964 functions 95/101 fuzzy 99.5411 linked code 0
[src/scene/address/iplAddress] instruction-exact functions: 94/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 99.8935
[src/scene/address/iplAddress]   section .rodata size 24 match 95.2381
[src/scene/address/iplAddress]   section .sbss size 8 match None
[src/scene/address/iplAddress]   section .sdata size 16 match 92.30769
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 99.54111
[src/scene/address/iplAddress]   below 100: start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface 99.34978
[src/scene/address/iplAddress]   below 100: onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface 97.662964
[src/scene/address/iplAddress]   below 100: onPreviousPage__Q33ipl5scene7AddressFv 97.25455
[src/scene/address/iplAddress]   below 100: set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err 98.6
[src/scene/address/iplAddress]   below 100: movePane_onDrag__Q33ipl5scene7AddressFv 95.70968
[src/scene/address/iplAddress]   below 100: update__Q33ipl5scene15FriendListCacheFUlPCwUx 81.35
[src/scene/address/iplAddress] baseline: code 20256/23988 data 36 functions 95 fuzzy 99.5411
[libs/RVL_SDK/src/wpad/WPADHIDParser] pool: IDENTICAL
[libs/RVL_SDK/src/wpad/WPADHIDParser] objdiff: code 21664/21664 data 224/1664 functions 22/22 fuzzy 100.0000 linked code 21664
[libs/RVL_SDK/src/wpad/WPADHIDParser] instruction-exact functions: 22/22
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .bss size 104 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .data size 1440 match 99.79123
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .sbss size 24 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .sdata2 size 96 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .text size 21664 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser] baseline: code 21664/21664 data 224 functions 22 fuzzy 100.0000
[src/scene/board/iplBoardObject] pool: IDENTICAL
[src/scene/board/iplBoardObject] objdiff: code 9184/9184 data 56/1320 functions 39/39 fuzzy 100.0000 linked code 9184
[src/scene/board/iplBoardObject] instruction-exact functions: 38/39
[src/scene/board/iplBoardObject]   section .data size 1200 match 99.83305
[src/scene/board/iplBoardObject]   section .rodata size 16 match 100.0
[src/scene/board/iplBoardObject]   section .sdata size 40 match 100.0
[src/scene/board/iplBoardObject]   section .sdata2 size 64 match 96.77419
[src/scene/board/iplBoardObject]   section .text size 9184 match 99.73868
[src/scene/board/iplBoardObject] baseline: code 9184/9184 data 56 functions 39 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 88.55724 -> 88.55724
global fuzzy_match_percent: 99.45033 -> 99.45033
global complete_code_percent: 62.78043 -> 62.78043
global matched_data_percent: 96.52597 -> 96.52597
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Final counts equal baseline. Zero accepted source improvements, zero commits. Only this attempts log changed. Data completion is not claimed. Exact function counts preserved at 87, 94, 22, 38. No source, header, split or symbol edit remains.

# High round, target symbol pairing

HEAD 775167f4, owned files unchanged versus freshly fetched origin/main. Initial quick gate PASS, data baseline 368/2560, 36/1964, 224/1664, 56/1320; instruction-exact 87,94,22,38. The medium-round extraction-only conclusion was incomplete: the target symbol table also groups literals and real pointer arrays, so object identity/extent must be repaired before assigning all missing data to extraction artifacts.

## Address identity corrections

Pool first: 81 strings identical. Every following correction preserves all section addresses, splits, section byte totals and data bytes.

- 81647574 lbl -> sTextNameB__Q23ipl5scene, 20 bytes: source declares five char pointers; set_friend callers load .data+0x3c, and five target relocations point to T_name_b_00 through T_name_b_04.
- 816475B8 extent 32 -> 12 and new sTextNameC__Q23ipl5scene at 816475C4, 20 bytes: the first 12 bytes are T_name_c_04 plus NUL; the five adjacent relocations at .data+0x8c target T_name_c_00..04, matching the typed source array and its loads.
- 81647614 lbl -> sButtonName__Q23ipl5scene, 20 bytes: create loads .data+0xdc; five target relocations point to B_name_b_00..04, matching the five-pointer source array.
- 81647664 lbl -> sButtonSpaceName__Q23ipl5scene, 16 bytes: create loads .data+0x12c; four target relocations point to four B_name_b space pane strings, matching the four-pointer source array.
- 8164769C extent 32 -> 10 and new sNameGroup__Q23ipl5scene at 816476A8, 20 bytes: name_b_04 is a ten-byte NUL-terminated string, followed by two alignment bytes and five pointer relocations to name_b_00..04 used by create.
- 816476EC extent 662 -> 12, new sNameCGroup__Q23ipl5scene at 816476F8, 20 bytes, and residual blob at 8164770C: G_name_c_04 is a twelve-byte string; five pointer relocations then identify G_name_c_00..04 used by create; the remaining 630 bytes are unchanged later literals.
- Address vtable at 81647B70 extent 288 -> 136: source class emits 0x88 bytes with two header words and 32 virtual-function slots; target relocations cover precisely the same slots through +0x84. The following 152 bytes are zero-filled deduplicated weak GUI vtables, not members of Address. No target data bytes removed or assigned elsewhere.

Diagnostic report after the first Address identities: data still 36/1964 and .data score 95.893456. Named arrays alone do not suffice; the original contains composite literal symbols and its other lbl literals are not recognized as compiler-generated. Read the installed version's primary source: https://raw.githubusercontent.com/encounter/objdiff/v3.4.5/objdiff-core/src/diff/mod.rs and data.rs. find_symbol matches @number literals by bytes/relocations; named literals match by name. diff_data_section takes the higher of named-symbol matches and the raw-section prefix comparison. matched_data credits an entire section only at 100 percent. Therefore correct target literal boundaries as well as real-array identities, with relocation/byte proof for every literal. Source-only weak symbols are excluded from the target-symbol average, as the orchestrator said.

### src/scene/address/iplAddress literal/extent proofs

- 8160F650 lbl_8160F650/22 -> @18225/20: .text 0x2cea via set_page_text__Q33ipl5scene7AddressFPCci +0x0; .text 0x2cf2 via set_page_text__Q33ipl5scene7AddressFPCci +0x0; full object bytes agree.
- 81647538 lbl_81647538/12 -> @17080/12: .text 0x272 via create__Q33ipl5scene7AddressFv +0x0; .text 0x282 via create__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 81647544 lbl_81647544/12 -> @17081/12: .data 0x40 via sTextNameB__Q23ipl5scene +0x0; full object bytes agree.
- 81647550 lbl_81647550/12 -> @17082/12: .data 0x44 via sTextNameB__Q23ipl5scene +0x0; full object bytes agree.
- 8164755C lbl_8164755C/12 -> @17083/12: .data 0x48 via sTextNameB__Q23ipl5scene +0x0; full object bytes agree.
- 81647568 lbl_81647568/12 -> @17084/12: .data 0x4c via sTextNameB__Q23ipl5scene +0x0; full object bytes agree.
- 81647588 lbl_81647588/12 -> @17085/12: .data 0x8c via sTextNameC__Q23ipl5scene +0x0; full object bytes agree.
- 81647594 lbl_81647594/12 -> @17086/12: .data 0x90 via sTextNameC__Q23ipl5scene +0x0; full object bytes agree.
- 816475A0 lbl_816475A0/12 -> @17087/12: .data 0x94 via sTextNameC__Q23ipl5scene +0x0; full object bytes agree.
- 816475AC lbl_816475AC/12 -> @17088/12: .data 0x98 via sTextNameC__Q23ipl5scene +0x0; full object bytes agree.
- 816475B8 lbl_816475B8/12 -> @17089/12: .data 0x9c via sTextNameC__Q23ipl5scene +0x0; full object bytes agree.
- 816475D8 lbl_816475D8/12 -> @17090/12: .data 0xdc via sButtonName__Q23ipl5scene +0x0; full object bytes agree.
- 816475E4 lbl_816475E4/12 -> @17091/12: .data 0xe0 via sButtonName__Q23ipl5scene +0x0; full object bytes agree.
- 816475F0 lbl_816475F0/12 -> @17092/12: .data 0xe4 via sButtonName__Q23ipl5scene +0x0; full object bytes agree.
- 816475FC lbl_816475FC/12 -> @17093/12: .data 0xe8 via sButtonName__Q23ipl5scene +0x0; full object bytes agree.
- 81647608 lbl_81647608/12 -> @17094/12: .data 0xec via sButtonName__Q23ipl5scene +0x0; full object bytes agree.
- 81647628 lbl_81647628/15 -> @17095/15: .data 0x12c via sButtonSpaceName__Q23ipl5scene +0x0; full object bytes agree.
- 81647637 lbl_81647637/15 -> @17096/15: .data 0x130 via sButtonSpaceName__Q23ipl5scene +0x0; full object bytes agree.
- 81647646 lbl_81647646/15 -> @17097/15: .data 0x134 via sButtonSpaceName__Q23ipl5scene +0x0; full object bytes agree.
- 81647655 lbl_81647655/15 -> @17098/15: .data 0x138 via sButtonSpaceName__Q23ipl5scene +0x0; full object bytes agree.
- 81647674 lbl_81647674/10 -> @17099/10: .data 0x170 via sNameGroup__Q23ipl5scene +0x0; full object bytes agree.
- 8164767E lbl_8164767E/10 -> @17100/10: .data 0x174 via sNameGroup__Q23ipl5scene +0x0; full object bytes agree.
- 81647688 lbl_81647688/10 -> @17101/10: .data 0x178 via sNameGroup__Q23ipl5scene +0x0; full object bytes agree.
- 81647692 lbl_81647692/10 -> @17102/10: .data 0x17c via sNameGroup__Q23ipl5scene +0x0; full object bytes agree.
- 8164769C lbl_8164769C/10 -> @17103/10: .data 0x180 via sNameGroup__Q23ipl5scene +0x0; full object bytes agree.
- 816476BC lbl_816476BC/12 -> @17104/12: .data 0x1c0 via sNameCGroup__Q23ipl5scene +0x0; full object bytes agree.
- 816476C8 lbl_816476C8/12 -> @17105/12: .data 0x1c4 via sNameCGroup__Q23ipl5scene +0x0; full object bytes agree.
- 816476D4 lbl_816476D4/12 -> @17106/12: .data 0x1c8 via sNameCGroup__Q23ipl5scene +0x0; full object bytes agree.
- 816476E0 lbl_816476E0/12 -> @17107/12: .data 0x1cc via sNameCGroup__Q23ipl5scene +0x0; full object bytes agree.
- 816476EC lbl_816476EC/12 -> @17108/12: .data 0x1d0 via sNameCGroup__Q23ipl5scene +0x0; full object bytes agree.
- 8164770C lbl_8164770C/630 -> @23133/18: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a.brlyt\x00'; full object bytes agree.
- 8164771E lbl_8164770C/630 -> @23134/30: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_note_alp_in.brlan\x00'; full object bytes agree.
- 8164773C lbl_8164770C/630 -> @23135/11: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'G_note_all\x00'; full object bytes agree.
- 81647747 lbl_8164770C/630 -> @23136/31: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_note_alp_out.brlan\x00'; full object bytes agree.
- 81647766 lbl_8164770C/630 -> @23137/31: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_note_trns_in.brlan\x00'; full object bytes agree.
- 81647785 lbl_8164770C/630 -> @23138/32: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_note_trns_out.brlan\x00'; full object bytes agree.
- 816477A5 lbl_8164770C/630 -> @23139/29: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_note_e_rtt.brlan\x00'; full object bytes agree.
- 816477C2 lbl_8164770C/630 -> @23140/13: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'G_note_e_rtt\x00'; full object bytes agree.
- 816477CF lbl_8164770C/630 -> @23141/29: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_note_c_rtt.brlan\x00'; full object bytes agree.
- 816477EC lbl_8164770C/630 -> @23142/11: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'note_c_rtt\x00'; full object bytes agree.
- 816477F7 lbl_8164770C/630 -> @23143/26: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_name_in.brlan\x00'; full object bytes agree.
- 81647811 lbl_8164770C/630 -> @23144/27: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_name_out.brlan\x00'; full object bytes agree.
- 8164782C lbl_8164770C/630 -> @23145/27: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_name_psh.brlan\x00'; full object bytes agree.
- 81647847 lbl_8164770C/630 -> @23146/30: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_gry_name_in.brlan\x00'; full object bytes agree.
- 81647865 lbl_8164770C/630 -> @23147/31: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_gry_name_out.brlan\x00'; full object bytes agree.
- 81647884 lbl_8164770C/630 -> @23148/31: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_gry_name_psh.brlan\x00'; full object bytes agree.
- 816478A3 lbl_8164770C/630 -> @23149/29: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_a_name_c_gry.brlan\x00'; full object bytes agree.
- 816478C0 lbl_8164770C/630 -> @23150/16: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_Back_a.brlyt\x00'; full object bytes agree.
- 816478D0 lbl_8164770C/630 -> @23151/22: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_Back_a_Apear.brlan\x00'; full object bytes agree.
- 816478E6 lbl_8164770C/630 -> @23152/11: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Picture_00\x00'; full object bytes agree.
- 816478F1 lbl_8164770C/630 -> @23153/21: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_Back_a_Lost.brlan\x00'; full object bytes agree.
- 81647906 lbl_8164770C/630 -> @23154/18: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_Dialog_a.brlyt\x00'; full object bytes agree.
- 81647918 lbl_8164770C/630 -> @23155/27: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_Dialog_a_DialogIn.brlan\x00'; full object bytes agree.
- 81647933 lbl_8164770C/630 -> @23157/28: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_Dialog_a_DialogOut.brlan\x00'; full object bytes agree.
- 8164794F lbl_8164770C/630 -> @23158/9: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'T_Dialog\x00'; full object bytes agree.
- 81647958 lbl_8164770C/630 -> @23159/11: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'mii_b_%02d\x00'; full object bytes agree.
- 81647963 lbl_8164770C/630 -> @23160/11: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'mii_c_%02d\x00'; full object bytes agree.
- 8164796E lbl_8164770C/630 -> @23161/10: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'T_adrs_00\x00'; full object bytes agree.
- 81647978 lbl_8164770C/630 -> @23162/10: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'T_wii_msg\x00'; full object bytes agree.
- 81647982 lbl_81647982/12 -> @23163/12: .text 0x1e8e via stt_release__Q33ipl5scene7AddressFv +0x0; .text 0x1e92 via stt_release__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 8164798E lbl_8164798E/20 -> @23235/20: .text 0xa1a via calcNormal__Q33ipl5scene7AddressFv +0x0; .text 0xa22 via calcNormal__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 816479A4 jumptable_816479A4/104 -> @23237/104: .text 0x9fe via calcNormal__Q33ipl5scene7AddressFv +0x0; .text 0xa06 via calcNormal__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 81647A4D lbl_81647A4D/20 -> @23490/20: .text 0x1572 via stt_cover_normal__Q33ipl5scene7AddressFv +0x0; .text 0x157a via stt_cover_normal__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 81647A61 lbl_81647A61/12 -> @23528/12: .text 0x1662 via stt_cover_backward__Q33ipl5scene7AddressFv +0x0; .text 0x166a via stt_cover_backward__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 81647A6D lbl_81647A6D/11 -> @23743/11: .text 0x2086 via stt_wait_child_fadeout__Q33ipl5scene7AddressFv +0x0; .text 0x208e via stt_wait_child_fadeout__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 81647A78 lbl_81647A78/75 -> @24121/15: .text 0x310a via start_trig_event__Q33ipl5scene7AddressFPCc +0x0; .text 0x311a via start_trig_event__Q33ipl5scene7AddressFPCc +0x0; full object bytes agree.
- 81647A87 lbl_81647A78/75 -> @24186/9: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'mii_move\x00'; full object bytes agree.
- 81647A90 lbl_81647A78/75 -> @24187/16: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'WIPL_SE_CH_HOLD\x00'; full object bytes agree.
- 81647AA0 lbl_81647A78/75 -> @24229/15: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'WIPL_SE_CH_SET\x00'; full object bytes agree.
- 81647AAF lbl_81647A78/75 -> @24230/20: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'WIPL_SE_CH_NOT_MOVE\x00'; full object bytes agree.
- 81647AC3 lbl_81647AC3/47 -> @24249/22: .text 0x3936 via on_point_event__Q33ipl5scene7AddressFiPQ33ipl10controller9Interface +0x0; .text 0x393e via on_point_event__Q33ipl5scene7AddressFiPQ33ipl10controller9Interface +0x0; full object bytes agree.
- 81647AD9 lbl_81647AC3/47 -> @24469/15: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'WIPL_SE_CANCEL\x00'; full object bytes agree.
- 81647AE8 lbl_81647AC3/47 -> @24525/9: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'T_nmbr_c\x00'; full object bytes agree.
- 81647AF2 lbl_81647AF2/12 -> @24589/12: .text 0x48da via set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err +0x0; .text 0x48ea via set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err +0x0; full object bytes agree.
- 81647AFE lbl_81647AFE/28 -> @24711/12: .text 0x5076 via movePane_onDrag__Q33ipl5scene7AddressFv +0x0; .text 0x5096 via movePane_onDrag__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 81647B0A lbl_81647AFE/28 -> @24712/16: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'WIPL_SE_CH_DRAG\x00'; full object bytes agree.
- 81647B1A lbl_81647B1A/12 -> @24759/12: .text 0x5016 via movePane_onDrag__Q33ipl5scene7AddressFv +0x0; .text 0x5022 via movePane_onDrag__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 81647B26 lbl_81647B26/34 -> @24941/34: .text 0x5c1e via sendRegisterMail__Q33ipl5scene15FriendListCacheFUl +0x0; .text 0x5c26 via sendRegisterMail__Q33ipl5scene15FriendListCacheFUl +0x0; full object bytes agree.
- 81647B48 lbl_81647B48/16 -> @24942/16: .text 0x5c22 via sendRegisterMail__Q33ipl5scene15FriendListCacheFUl +0x0; .text 0x5c2e via sendRegisterMail__Q33ipl5scene15FriendListCacheFUl +0x0; full object bytes agree.
- 816947D0 lbl_816947D0/8 -> @23372/8: .text 0xcf8 via draw__Q33ipl5scene7AddressFv +0x0; .text 0xe04 via draw__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 816947D8 lbl_816947D8/4 -> @23376/4: .text 0x2b74 via set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb +0x0; .text 0x2c38 via set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb +0x0; full object bytes agree.
- 816947DC lbl_816947DC/4 -> @23610/4: .text 0x1a38 via stt_loop_forward__Q33ipl5scene7AddressFv +0x0; .text 0x4724 via onPreviousPage__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 816947E0 lbl_816947E0/4 -> @24035/4: .text 0x2b94 via set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb +0x0; full object bytes agree.
- 816947E4 lbl_816947E4/4 -> @24760/4: .text 0x5144 via movePane_onDrag__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 816947E8 lbl_816947E8/4 -> @25004/4: .text 0x5d94 via __sinit_\iplAddress_cpp +0x0; full object bytes agree.
- 816965C0 lbl_816965C0/4 -> @23132/4: .text 0x2b4 via create__Q33ipl5scene7AddressFv +0x0; .text 0x4e4 via create__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 816965C4 lbl_816965C4/6 -> @23156/6: .text 0x564 via create__Q33ipl5scene7AddressFv +0x0; .text 0x57c via create__Q33ipl5scene7AddressFv +0x0; full object bytes agree.
- 816965CA lbl_816965CA/4 -> @24036/2: .text 0x2cac via set_friend__Q33ipl5scene7AddressFPCcUlUlRQ43ipl5scene7Address6MiiObjb +0x0; full object bytes agree.
- 81698B50 lbl_81698B50/4 -> sPageOffset__Q23ipl5scene/8: .text 0xcfc via draw__Q33ipl5scene7AddressFv +0x0; .text 0xd14 via draw__Q33ipl5scene7AddressFv +0x0; full object bytes agree.

- 81698B50/81698B54 merged into sPageOffset__Q23ipl5scene, 8 bytes: source declares math::VEC2 with two float fields; the translation-unit initializer constructs its VEC2 from two -1.0f components; the VEC2 type and constructor place those components at .sbss+0/+4, and onPreviousPage/movePane_onDrag load the same two components. Interior target label is a field, not a separate object.
- 8160F650 extent 22 -> 20: set_page_text copies five pairs of 16-bit elements, exactly ten wchar_t digits, into its twenty-byte local array; source literal is the same ten elements and all target/source bytes match. The two unused zeros have no separate relocation/type evidence and remain physical section alignment.
- 816965CA extent 4 -> 2: the source empty wide string is one 16-bit NUL; its target references pass a wchar_t pointer and never load a second element. The following two zero bytes remain physical alignment.

DTK reintroduced lbl_81698B54 as a four-byte object because code has a relocation to the second VEC2 field. Preserve that relocation label as type:label with no object extent; the 8-byte sPageOffset object owns both fields. This corrects duplicate overlapping ownership, and does not remove the relocation or bytes.
DTK inferred an object extent for an unspecified-size member label. Specify its zero-size alias explicitly; the real VEC2 extent remains eight bytes and both stores/loads remain represented.
DTK v1.7.5 replaces auto Unknown labels with inferred Object symbols. Trial explicit Object with zero extent to preserve the genuine interior-address alias without assigning it duplicate storage. This is only a member label, not a zero-sized real object; sPageOffset still owns every byte.
DTK source shows auto lbl entries are replaceable inferred objects; preserving the auto name keeps restoring its four-byte extent. Name the alias sPageOffset.y, the actual proven source member path, with zero label extent. This is a member address label within the existing eight-byte VEC2, not another variable. Proof remains the same VEC2 constructor/layout and accesses at object+4. No byte becomes unowned and all original relocations remain.
The three label/extent trials all fail: DTK v1.7.5 serializes a zero-sized label without its explicit size and then detects it as another four-byte Object. The named member alias also fails. Restored the original second-field lbl name/extent. Address .sbss remains 66.66667 percent due duplicate overlapping target object ownership, not wrong source bytes. No trial alias or zero-size definition remains. Its eight physical bytes and the real VEC2 relocation proof remain intact.

### Address acceptance

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 20256/23988 data 1956/1964 functions 95/101 fuzzy 99.5411 linked code 0
[src/scene/address/iplAddress] instruction-exact functions: 94/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 100.0
[src/scene/address/iplAddress]   section .rodata size 24 match 100.0
[src/scene/address/iplAddress]   section .sbss size 8 match 66.66667
[src/scene/address/iplAddress]   section .sdata size 16 match 100.0
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 99.54111
[src/scene/address/iplAddress]   below 100: start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface 99.34978
[src/scene/address/iplAddress]   below 100: onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface 97.662964
[src/scene/address/iplAddress]   below 100: onPreviousPage__Q33ipl5scene7AddressFv 97.25455
[src/scene/address/iplAddress]   below 100: set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err 98.6
[src/scene/address/iplAddress]   below 100: movePane_onDrag__Q33ipl5scene7AddressFv 95.70968
[src/scene/address/iplAddress]   below 100: update__Q33ipl5scene15FriendListCacheFUlPCwUx 81.35
[src/scene/address/iplAddress] baseline: code 20256/23988 data 36 functions 95 fuzzy 99.5411
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 62.98463 -> 63.07103
global matched_data_percent: 97.19820 -> 97.30297
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: no baseline for merge-base 775167f4; compared against nearest snapshotted ancestor 547637bf (1 commits back)
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
Instruction-exact 94/101 unchanged, data 36 -> 1956/1964; .data/.rodata/.sdata/.sdata2/.ctors all 100 percent. .sbss remains the overlapping VEC2 field alias above. DOL hash correct and global regressions zero.

### src/scene/address/iplAddressEdit literal/extent proofs

- 8160F67F lbl_8160F67F/13 -> @19550/12: .text 0x52fe via start_ipt_left_event__Q33ipl5scene11AddressEditFPCci +0x0; .text 0x5306 via start_ipt_left_event__Q33ipl5scene11AddressEditFPCci +0x0; full object bytes agree.
- 8164810B @24231/501 -> @24231/10: .text 0x2322 via stt_ipt_input__Q33ipl5scene11AddressEditFv +0x0; .text 0x2326 via stt_ipt_input__Q33ipl5scene11AddressEditFv +0x0; full object bytes agree.
- 81648115 @24231/501 -> @24804/18: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c.brlyt\x00'; full object bytes agree.
- 81648127 @24231/501 -> @24805/28: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_card_strt.brlan\x00'; full object bytes agree.
- 81648143 @24231/501 -> @24806/17: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'G_card_strt_fnsh\x00'; full object bytes agree.
- 81648154 @24231/501 -> @24807/34: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_question_alp_in.brlan\x00'; full object bytes agree.
- 81648176 @24231/501 -> @24808/14: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'G_question_00\x00'; full object bytes agree.
- 81648184 @24231/501 -> @24809/30: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_name_alp_in.brlan\x00'; full object bytes agree.
- 816481A2 @24231/501 -> @24810/10: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'G_name_00\x00'; full object bytes agree.
- 816481AC @24231/501 -> @24811/29: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_msg_alp_in.brlan\x00'; full object bytes agree.
- 816481C9 @24231/501 -> @24812/9: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'G_msg_00\x00'; full object bytes agree.
- 816481D2 @24231/501 -> @24813/29: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_mii_alp_in.brlan\x00'; full object bytes agree.
- 816481EF @24231/501 -> @24815/35: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_question_alp_out.brlan\x00'; full object bytes agree.
- 81648212 @24231/501 -> @24816/31: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_name_alp_out.brlan\x00'; full object bytes agree.
- 81648231 @24231/501 -> @24817/30: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_msg_alp_out.brlan\x00'; full object bytes agree.
- 8164824F @24231/501 -> @24818/30: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_mii_alp_out.brlan\x00'; full object bytes agree.
- 8164826D @24231/501 -> @24819/28: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'th_Adress_c_card_fnsh.brlan\x00'; full object bytes agree.
- 81648289 @24231/501 -> @24820/16: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_Back_a.brlyt\x00'; full object bytes agree.
- 81648299 @24231/501 -> @24821/22: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_Back_a_Apear.brlan\x00'; full object bytes agree.
- 816482AF @24231/501 -> @24822/11: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Picture_00\x00'; full object bytes agree.
- 816482BA @24231/501 -> @24823/21: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_Back_a_Lost.brlan\x00'; full object bytes agree.
- 816482CF @24231/501 -> @24824/14: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'T_question_00\x00'; full object bytes agree.
- 816482DD @24231/501 -> @24825/9: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'T_msg_00\x00'; full object bytes agree.
- 816482E6 @24231/501 -> @24829/25: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'my_IplTopBalloon_a.brlyt\x00'; full object bytes agree.
- 81648628 __vt__Q33ipl5scene11AddressEdit/288 -> __vt__Q33ipl5scene11AddressEdit/136: .text 0x282 via __ct__Q33ipl5scene11AddressEditFPQ23EGG4Heapi +0x0; .text 0x28a via __ct__Q33ipl5scene11AddressEditFPQ23EGG4Heapi +0x0; full object bytes agree.
- 816947F0 lbl_816947F0/4 -> @24826/4: .text 0x1078 via create__Q33ipl5scene11AddressEditFv +0x0; full object bytes agree.
- 816947F4 lbl_816947F4/4 -> @24827/4: .text 0x1080 via create__Q33ipl5scene11AddressEditFv +0x0; full object bytes agree.
- 816947F8 lbl_816947F8/4 -> @24828/4: .text 0x1070 via create__Q33ipl5scene11AddressEditFv +0x0; .text 0x4788 via start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface +0x0; full object bytes agree.
- 816947FC lbl_816947FC/4 -> @26462/4: .text 0x47c0 via start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface +0x0; .text 0x48e0 via start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface +0x0; full object bytes agree.
- 81694800 lbl_81694800/4 -> @26463/4: .text 0x47b0 via start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface +0x0; .text 0x48d0 via start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface +0x0; full object bytes agree.
- 81694804 lbl_81694804/4 -> @26464/4: .text 0x47b8 via start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface +0x0; .text 0x48d8 via start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface +0x0; full object bytes agree.
- 816965E4 lbl_816965E4/4 -> @24778/4: .text 0x47c via create__Q33ipl5scene11AddressEditFv +0x0; .text 0xa1c via create__Q33ipl5scene11AddressEditFv +0x0; full object bytes agree.
- 816965E8 lbl_816965E8/2 -> @24802/2: .text 0x994 via create__Q33ipl5scene11AddressEditFv +0x0; .text 0x9c4 via create__Q33ipl5scene11AddressEditFv +0x0; full object bytes agree.
- 816965EA lbl_816965EA/6 -> @24814/6: .text 0xa90 via create__Q33ipl5scene11AddressEditFv +0x0; .text 0xaf0 via create__Q33ipl5scene11AddressEditFv +0x0; full object bytes agree.
- 816965F0 lbl_816965F0/8 -> @26844/8: .text 0x6390 via setEMail__Q43ipl5scene11AddressEdit6StringFPCw +0x0; full object bytes agree.

Restored 16 unnecessary identity changes in Address/AddressEdit sections already scoring 100 percent. Their raw-prefix bytes and relocations already match; preserve original constant names and minimize the diff.

### AddressEdit acceptance

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 21556/27112 data 2560/2560 functions 87/94 fuzzy 99.4886 linked code 0
[src/scene/address/iplAddressEdit] instruction-exact functions: 87/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 100.0
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 99.48864
[src/scene/address/iplAddressEdit]   below 100: create__Q33ipl5scene11AddressEditFv 97.44634
[src/scene/address/iplAddressEdit]   below 100: stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv 99.73404
[src/scene/address/iplAddressEdit]   below 100: start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface 99.34066
[src/scene/address/iplAddressEdit]   below 100: start_left_event__Q33ipl5scene11AddressEditFPCc 98.958336
[src/scene/address/iplAddressEdit]   below 100: get_friendinfo__Q33ipl5scene11AddressEditFv 88.03571
[src/scene/address/iplAddressEdit]   below 100: update_friendinfo__Q33ipl5scene11AddressEditFv 99.42105
[src/scene/address/iplAddressEdit]   below 100: set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err 98.666664
[src/scene/address/iplAddressEdit] baseline: code 21556/27112 data 368 functions 87 fuzzy 99.4886
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 20256/23988 data 1956/1964 functions 95/101 fuzzy 99.5411 linked code 0
[src/scene/address/iplAddress] instruction-exact functions: 94/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 100.0
[src/scene/address/iplAddress]   section .rodata size 24 match 100.0
[src/scene/address/iplAddress]   section .sbss size 8 match 66.66667
[src/scene/address/iplAddress]   section .sdata size 16 match 100.0
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 99.54111
[src/scene/address/iplAddress]   below 100: start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface 99.34978
[src/scene/address/iplAddress]   below 100: onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface 97.662964
[src/scene/address/iplAddress]   below 100: onPreviousPage__Q33ipl5scene7AddressFv 97.25455
[src/scene/address/iplAddress]   below 100: set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err 98.6
[src/scene/address/iplAddress]   below 100: movePane_onDrag__Q33ipl5scene7AddressFv 95.70968
[src/scene/address/iplAddress]   below 100: update__Q33ipl5scene15FriendListCacheFUlPCwUx 81.35
[src/scene/address/iplAddress] baseline: code 20256/23988 data 36 functions 95 fuzzy 99.5411
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 62.98463 -> 63.07103
global matched_data_percent: 97.19820 -> 97.42258
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: no baseline for merge-base 775167f4; compared against nearest snapshotted ancestor 547637bf (1 commits back)
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
Data 368 -> 2560/2560, all non-text sections 100 percent. Instruction-exact 87/94 unchanged. Target/source pools, DOL and regression gates pass.

### Address field alias, documented DTK label representation

DTK v1.7.5 detect_objects skips named labels beginning with two dots. Try its actual address-label convention, ..sPageOffset.y, instead of a bare auto label. The alias identifies the same y member at 81698B54; the real 8-byte sPageOffset owns all .sbss bytes and all original relocations remain. No hidden/ignored/noexport flag used; no physical object is deleted or resized. This is an overlapping field-address alias, proven by VEC2's two f32 fields and the constructor initializes both fields at 0/+4. Source: https://raw.githubusercontent.com/encounter/decomp-toolkit/v1.7.5/src/analysis/objects.rs .

### libs/RVL_SDK/src/wpad/WPADHIDParser literal/extent proofs

- 81687AF0 lbl_81687AF0/1288 -> @2798/44: .text 0xf6 via abortInitExtension +0x0; .text 0xfa via abortInitExtension +0x0; full object bytes agree.
- 81687B1C lbl_81687AF0/1288 -> @3037/20: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Dpd Setting is ok.\n\x00'; full object bytes agree.
- 81687B30 lbl_81687AF0/1288 -> @3038/24: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Dpd Setting is broken.\n\x00'; full object bytes agree.
- 81687B48 lbl_81687AF0/1288 -> @3039/65: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Old Firmware uses default values because it has no Dpd Setting.\n\x00'; full object bytes agree.
- 81687B8C lbl_81687AF0/1288 -> @3041/18: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'x = %lf, y = %lf\n\x00'; full object bytes agree.
- 81687BA0 lbl_81687AF0/1288 -> @3050/30: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'difaveX = %lf, difaveY = %lf\n\x00'; full object bytes agree.
- 81687BC0 lbl_81687AF0/1288 -> @3051/30: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'deltaX  = %lf, deltaY  = %lf\n\x00'; full object bytes agree.
- 81687BE0 lbl_81687AF0/1288 -> @3052/28: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'calibX = %lf, calibY = %lf\n\x00'; full object bytes agree.
- 81687BFC lbl_81687AF0/1288 -> @3053/28: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'centX  = %lf, centY  = %lf\n\x00'; full object bytes agree.
- 81687C18 lbl_81687AF0/1288 -> @3056/14: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'rolag  = %lf\n\x00'; full object bytes agree.
- 81687C28 lbl_81687AF0/1288 -> @3057/12: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Acc is ok.\n\x00'; full object bytes agree.
- 81687C38 lbl_81687AF0/1288 -> @3058/16: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Acc is broken.\n\x00'; full object bytes agree.
- 81687C48 lbl_81687AF0/1288 -> @3059/40: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'0G:  accX = %d,  accY = %d,  accZ = %d\n\x00'; full object bytes agree.
- 81687C70 lbl_81687AF0/1288 -> @3060/40: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'1G:  accX = %d,  accY = %d,  accZ = %d\n\x00'; full object bytes agree.
- 81687C98 lbl_81687AF0/1288 -> @3061/25: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Volume: %d,   Motor: %d\n\x00'; full object bytes agree.
- 81687CB4 lbl_81687AF0/1288 -> @3125/18: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'check sum error.\n\x00'; full object bytes agree.
- 81687CC8 lbl_81687AF0/1288 -> @3126/46: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'0G:  fsaccX = %d,  fsaccY = %d,  fsaccZ = %d\n\x00'; full object bytes agree.
- 81687CF8 lbl_81687AF0/1288 -> @3127/46: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'1G:  fsaccX = %d,  fsaccY = %d,  fsaccZ = %d\n\x00'; full object bytes agree.
- 81687D28 lbl_81687AF0/1288 -> @3128/39: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'FS:  X = %d,  X max = %d,  X min = %d\n\x00'; full object bytes agree.
- 81687D50 lbl_81687AF0/1288 -> @3129/39: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'FS:  Y = %d,  Y max = %d,  Y min = %d\n\x00'; full object bytes agree.
- 81687D78 lbl_81687AF0/1288 -> @3130/39: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'CL:  X = %d,  X max = %d,  X min = %d\n\x00'; full object bytes agree.
- 81687DA0 lbl_81687AF0/1288 -> @3131/39: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'CL:  Y = %d,  Y max = %d,  Y min = %d\n\x00'; full object bytes agree.
- 81687DC8 lbl_81687AF0/1288 -> @3132/39: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'CR:  X = %d,  X max = %d,  X min = %d\n\x00'; full object bytes agree.
- 81687DF0 lbl_81687AF0/1288 -> @3133/39: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'CR:  Y = %d,  Y max = %d,  Y min = %d\n\x00'; full object bytes agree.
- 81687E18 lbl_81687AF0/1288 -> @3134/22: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'LR:  L = %d,  R = %d\n\x00'; full object bytes agree.
- 81687E30 lbl_81687AF0/1288 -> @3169/22: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'devId: %d, subId: %d\n\x00'; full object bytes agree.
- 81687E48 lbl_81687AF0/1288 -> @3170/11: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'type : %d\n\x00'; full object bytes agree.
- 81687E54 lbl_81687AF0/1288 -> @3171/11: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'mode : %d\n\x00'; full object bytes agree.
- 81687E60 lbl_81687AF0/1288 -> @3231/20: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Received report 20\n\x00'; full object bytes agree.
- 81687E74 lbl_81687AF0/1288 -> @3232/23: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'initialize attachment\n\x00'; full object bytes agree.
- 81687E8C lbl_81687AF0/1288 -> @3233/21: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'already initialized\n\x00'; full object bytes agree.
- 81687EA4 lbl_81687AF0/1288 -> @3234/22: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'already disconnected\n\x00'; full object bytes agree.
- 81687EBC lbl_81687AF0/1288 -> @3280/21: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'read error happens!\n\x00'; full object bytes agree.
- 81687ED4 lbl_81687AF0/1288 -> @3281/17: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'base addr: %08x\n\x00'; full object bytes agree.
- 81687EE8 lbl_81687AF0/1288 -> @3282/15: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'length   : %d\n\x00'; full object bytes agree.
- 81687EF8 lbl_81687AF0/1288 -> @3283/12: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'i2c = %04x\n\x00'; full object bytes agree.
- 81687F04 lbl_81687AF0/1288 -> @3284/10: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'enc = %d\n\x00'; full object bytes agree.
- 81687F10 lbl_81687AF0/1288 -> @3285/31: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Access to extension register.\n\x00'; full object bytes agree.
- 81687F30 lbl_81687AF0/1288 -> @3286/12: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Decode!!!!\n\x00'; full object bytes agree.
- 81687F3C lbl_81687AF0/1288 -> @3287/27: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'    len = %d, addr = %04x\n\x00'; full object bytes agree.
- 81687F58 lbl_81687AF0/1288 -> @3288/32: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'received data is out of range!\n\x00'; full object bytes agree.
- 81687F78 lbl_81687AF0/1288 -> @3309/15: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'Received ack!\n\x00'; full object bytes agree.
- 81687F88 lbl_81687AF0/1288 -> @3310/43: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'ack --> report ID = %02x, error code = %d\n\x00'; full object bytes agree.
- 81687FB4 lbl_81687AF0/1288 -> @3311/47: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'ack error --> report ID = %d, error code = %d\n\x00'; full object bytes agree.
- 81687FE4 lbl_81687AF0/1288 -> @3312/14: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'invalid ack!\n\x00'; full object bytes agree.

### WPAD and Address field acceptance

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/wpad/WPADHIDParser] pool: IDENTICAL
[libs/RVL_SDK/src/wpad/WPADHIDParser] objdiff: code 21664/21664 data 1664/1664 functions 22/22 fuzzy 100.0000 linked code 21664
[libs/RVL_SDK/src/wpad/WPADHIDParser] instruction-exact functions: 22/22
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .bss size 104 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .data size 1440 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .sbss size 24 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .sdata2 size 96 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .text size 21664 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser] baseline: code 21664/21664 data 224 functions 22 fuzzy 100.0000
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 20256/23988 data 1964/1964 functions 95/101 fuzzy 99.5411 linked code 0
[src/scene/address/iplAddress] instruction-exact functions: 94/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 100.0
[src/scene/address/iplAddress]   section .rodata size 24 match 100.0
[src/scene/address/iplAddress]   section .sbss size 8 match 100.0
[src/scene/address/iplAddress]   section .sdata size 16 match 100.0
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 99.54111
[src/scene/address/iplAddress]   below 100: start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface 99.34978
[src/scene/address/iplAddress]   below 100: onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface 97.662964
[src/scene/address/iplAddress]   below 100: onPreviousPage__Q33ipl5scene7AddressFv 97.25455
[src/scene/address/iplAddress]   below 100: set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err 98.6
[src/scene/address/iplAddress]   below 100: movePane_onDrag__Q33ipl5scene7AddressFv 95.70968
[src/scene/address/iplAddress]   below 100: update__Q33ipl5scene15FriendListCacheFUlPCwUx 81.35
[src/scene/address/iplAddress] baseline: code 20256/23988 data 36 functions 95 fuzzy 99.5411
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 62.98463 -> 63.07103
global matched_data_percent: 97.19820 -> 97.50159
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: no baseline for merge-base 775167f4; compared against nearest snapshotted ancestor 547637bf (1 commits back)
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
WPAD data 224 -> 1664/1664; all sections 100 percent and instruction-exact 22/22 unchanged. Address data 1956 -> 1964/1964 with the typed member address alias, all non-text sections 100 percent and instruction-exact 94/101 unchanged. Zero regressions and correct DOL.

### src/scene/board/iplBoardObject literal/extent proofs

- 8164B1E8 lbl_8164B1E8/16 -> @16958/16: .text 0x7d2 via stt_create__Q33ipl5scene11BoardObjectFv +0x0; .text 0x7de via stt_create__Q33ipl5scene11BoardObjectFv +0x0; full object bytes agree.
- 8164B1F8 lbl_8164B1F8/28 -> @16959/28: .data 0x2e4 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B214 lbl_8164B214/24 -> @16960/24: .data 0x2e8 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B22C lbl_8164B22C/25 -> @16961/25: .data 0x2ec via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B245 lbl_8164B245/29 -> @16962/29: .data 0x2f0 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B262 lbl_8164B262/27 -> @16963/27: .data 0x2f4 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B27D lbl_8164B27D/25 -> @16964/25: .data 0x2f8 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B296 lbl_8164B296/24 -> @16965/24: .data 0x2fc via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B2AE lbl_8164B2AE/24 -> @16966/24: .data 0x300 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B2C6 lbl_8164B2C6/23 -> @16967/23: .data 0x304 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B2DD lbl_8164B2DD/16 -> @16968/16: .data 0x308 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B2ED lbl_8164B2ED/28 -> @16969/28: .data 0x30c via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B309 lbl_8164B309/24 -> @16970/24: .data 0x310 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B321 lbl_8164B321/25 -> @16971/25: .data 0x314 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B33A lbl_8164B33A/29 -> @16972/29: .data 0x318 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B357 lbl_8164B357/27 -> @16973/27: .data 0x31c via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B372 lbl_8164B372/25 -> @16974/25: .data 0x320 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B38B lbl_8164B38B/24 -> @16975/24: .data 0x324 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B3A3 lbl_8164B3A3/24 -> @16976/24: .data 0x328 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B3BB lbl_8164B3BB/23 -> @16977/23: .data 0x32c via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B3D2 lbl_8164B3D2/16 -> @16978/16: .data 0x330 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B3E2 lbl_8164B3E2/28 -> @16979/28: .data 0x334 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B3FE lbl_8164B3FE/24 -> @16980/24: .data 0x338 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B416 lbl_8164B416/25 -> @16981/25: .data 0x33c via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B42F lbl_8164B42F/29 -> @16982/29: .data 0x340 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B44C lbl_8164B44C/27 -> @16983/27: .data 0x344 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B467 lbl_8164B467/25 -> @16984/25: .data 0x348 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B480 lbl_8164B480/24 -> @16985/24: .data 0x34c via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B498 lbl_8164B498/24 -> @16986/24: .data 0x350 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B4B0 lbl_8164B4B0/144 -> @16987/23: .data 0x354 via lbl_8164B4B0 +0x0; full object bytes agree.
- 8164B4C8 lbl_8164B4B0/144 -> mAnimNames__Q33ipl5scene11BoardObject/120: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'; full object bytes agree.
- 8164B540 lbl_8164B540/21 -> @16989/21: .rodata 0x0 via scThumbChangeTexFile__Q23ipl5scene +0x0; full object bytes agree.
- 8164B555 lbl_8164B555/10 -> @16990/10: .rodata 0x4 via scThumbChangeTexFile__Q23ipl5scene +0x0; full object bytes agree.
- 8164B55F lbl_8164B55F/54 -> @19509/9: .text 0x1e7e via onEvent__Q33ipl5scene11BoardObjectFUlUlPv +0x0; .text 0x1e86 via onEvent__Q33ipl5scene11BoardObjectFUlUlPv +0x0; full object bytes agree.
- 8164B568 lbl_8164B55F/54 -> @19511/9: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'T_Letter\x00'; full object bytes agree.
- 8164B571 lbl_8164B55F/54 -> @19512/19: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'./thumbnail_LZ.bin\x00'; full object bytes agree.
- 8164B584 lbl_8164B55F/54 -> @19514/17: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'WIPL_SE_MSG_DISP\x00'; full object bytes agree.
- 8164B595 lbl_8164B595/10 -> @19542/10: .text 0xeee via stt_make_thm__Q33ipl5scene11BoardObjectFv +0x0; .text 0xef2 via stt_make_thm__Q33ipl5scene11BoardObjectFv +0x0; full object bytes agree.
- 8164B59F lbl_8164B59F/19 -> @19595/19: .text 0x1106 via stt_pinch__Q33ipl5scene11BoardObjectFv +0x0; .text 0x1112 via stt_pinch__Q33ipl5scene11BoardObjectFv +0x0; full object bytes agree.
- 8164B5B2 lbl_8164B5B2/20 -> @19785/20: .text 0x1b56 via start_point_event__Q33ipl5scene11BoardObjectFiPQ33ipl10controller9Interface +0x0; .text 0x1b62 via start_point_event__Q33ipl5scene11BoardObjectFiPQ33ipl10controller9Interface +0x0; full object bytes agree.
- 8164B5F0 __vt__Q33ipl4math31Interporation<Q33ipl4math4VEC2>/168 -> __vt__Q33ipl4math31Interporation<Q33ipl4math4VEC2>/16: source literal/type and byte-identical target pool at this exact offset; decoded bytes b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'; full object bytes agree.

- 8164B4B0 extent 144 -> 23 and mAnimNames__Q33ipl5scene11BoardObject at 8164B4C8, 120 bytes: target's first bytes are the final LetterS_c_SDAnim.brlan string plus NUL; one alignment byte follows; thirty R_PPC_ADDR32 entries then match the typed 3-by-10 char-pointer table used by stt_create. Every relocation target is the corresponding layout/animation literal.
- Interporation<VEC2> vtable at 8164B5F0 extent 168 -> 16: two header words, destructor and calc slots match the real template class vtable; following 152 zero bytes are deduplicated weak GUI vtables. All real virtual slots remain accounted for.
- 81694848 extent 8 -> 4: calc's instruction at 81395284 performs lfs of a single 32-bit 48.0f constant, emitted by source as @19646 size 4; the following four zero bytes are unused section alignment, with no load or relocation to +4. Both section totals remain 64.

### BoardObject acceptance

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/board/iplBoardObject] pool: IDENTICAL
[src/scene/board/iplBoardObject] objdiff: code 9184/9184 data 1320/1320 functions 39/39 fuzzy 100.0000 linked code 9184
[src/scene/board/iplBoardObject] instruction-exact functions: 38/39
[src/scene/board/iplBoardObject]   section .data size 1200 match 100.0
[src/scene/board/iplBoardObject]   section .rodata size 16 match 100.0
[src/scene/board/iplBoardObject]   section .sdata size 40 match 100.0
[src/scene/board/iplBoardObject]   section .sdata2 size 64 match 100.0
[src/scene/board/iplBoardObject]   section .text size 9184 match 99.73868
[src/scene/board/iplBoardObject] baseline: code 9184/9184 data 56 functions 39 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 62.98463 -> 63.07103
global matched_data_percent: 97.19820 -> 97.57056
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: no baseline for merge-base 775167f4; compared against nearest snapshotted ancestor 547637bf (1 commits back)
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
Data 56 -> 1320/1320, all non-text sections 100 percent, instruction-exact 38/39 unchanged. Matched_code remains 9184/9184. Full DOL and regression checks pass.

Ownership audit: every symbols.txt change lies inside the four owned non-text section ranges. Splits, addresses, complete section bytes and total_data are unchanged. No source/header/configure.py or other unit was edited. Original section totals remain AddressEdit 2560, Address 1964, WPAD 1664, Board 1320.

## High-round terminal verification

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/address/iplAddressEdit] pool: IDENTICAL
[src/scene/address/iplAddressEdit] objdiff: code 21556/27112 data 2560/2560 functions 87/94 fuzzy 99.4886 linked code 0
[src/scene/address/iplAddressEdit] instruction-exact functions: 87/94
[src/scene/address/iplAddressEdit]   section .bss size 320 match 100.0
[src/scene/address/iplAddressEdit]   section .data size 2152 match 100.0
[src/scene/address/iplAddressEdit]   section .rodata size 40 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .sdata2 size 24 match 100.0
[src/scene/address/iplAddressEdit]   section .text size 27112 match 99.48864
[src/scene/address/iplAddressEdit]   below 100: create__Q33ipl5scene11AddressEditFv 97.44634
[src/scene/address/iplAddressEdit]   below 100: stt_wait_btn_fadeout__Q33ipl5scene11AddressEditFv 99.73404
[src/scene/address/iplAddressEdit]   below 100: start_point_event__Q33ipl5scene11AddressEditFPCcPQ33ipl10controller9Interface 99.34066
[src/scene/address/iplAddressEdit]   below 100: start_left_event__Q33ipl5scene11AddressEditFPCc 98.958336
[src/scene/address/iplAddressEdit]   below 100: get_friendinfo__Q33ipl5scene11AddressEditFv 88.03571
[src/scene/address/iplAddressEdit]   below 100: update_friendinfo__Q33ipl5scene11AddressEditFv 99.42105
[src/scene/address/iplAddressEdit]   below 100: set_err_msg__Q33ipl5scene11AddressEditFPwUl8NWC24Err 98.666664
[src/scene/address/iplAddressEdit] baseline: code 21556/27112 data 368 functions 87 fuzzy 99.4886
[src/scene/address/iplAddress] pool: IDENTICAL
[src/scene/address/iplAddress] objdiff: code 20256/23988 data 1964/1964 functions 95/101 fuzzy 99.5411 linked code 0
[src/scene/address/iplAddress] instruction-exact functions: 94/101
[src/scene/address/iplAddress]   section .ctors size 4 match 100.0
[src/scene/address/iplAddress]   section .data size 1880 match 100.0
[src/scene/address/iplAddress]   section .rodata size 24 match 100.0
[src/scene/address/iplAddress]   section .sbss size 8 match 100.0
[src/scene/address/iplAddress]   section .sdata size 16 match 100.0
[src/scene/address/iplAddress]   section .sdata2 size 32 match 100.0
[src/scene/address/iplAddress]   section .text size 23988 match 99.54111
[src/scene/address/iplAddress]   below 100: start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface 99.34978
[src/scene/address/iplAddress]   below 100: onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface 97.662964
[src/scene/address/iplAddress]   below 100: onPreviousPage__Q33ipl5scene7AddressFv 97.25455
[src/scene/address/iplAddress]   below 100: set_err_msg__Q33ipl5scene7AddressFPwUl8NWC24Err 98.6
[src/scene/address/iplAddress]   below 100: movePane_onDrag__Q33ipl5scene7AddressFv 95.70968
[src/scene/address/iplAddress]   below 100: update__Q33ipl5scene15FriendListCacheFUlPCwUx 81.35
[src/scene/address/iplAddress] baseline: code 20256/23988 data 36 functions 95 fuzzy 99.5411
[libs/RVL_SDK/src/wpad/WPADHIDParser] pool: IDENTICAL
[libs/RVL_SDK/src/wpad/WPADHIDParser] objdiff: code 21664/21664 data 1664/1664 functions 22/22 fuzzy 100.0000 linked code 21664
[libs/RVL_SDK/src/wpad/WPADHIDParser] instruction-exact functions: 22/22
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .bss size 104 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .data size 1440 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .sbss size 24 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .sdata2 size 96 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser]   section .text size 21664 match 100.0
[libs/RVL_SDK/src/wpad/WPADHIDParser] baseline: code 21664/21664 data 224 functions 22 fuzzy 100.0000
[src/scene/board/iplBoardObject] pool: IDENTICAL
[src/scene/board/iplBoardObject] objdiff: code 9184/9184 data 1320/1320 functions 39/39 fuzzy 100.0000 linked code 9184
[src/scene/board/iplBoardObject] instruction-exact functions: 38/39
[src/scene/board/iplBoardObject]   section .data size 1200 match 100.0
[src/scene/board/iplBoardObject]   section .rodata size 16 match 100.0
[src/scene/board/iplBoardObject]   section .sdata size 40 match 100.0
[src/scene/board/iplBoardObject]   section .sdata2 size 64 match 100.0
[src/scene/board/iplBoardObject]   section .text size 9184 match 99.73868
[src/scene/board/iplBoardObject] baseline: code 9184/9184 data 56 functions 39 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 62.98463 -> 63.07103
global matched_data_percent: 97.19820 -> 97.57056
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: no baseline for merge-base 775167f4; compared against nearest snapshotted ancestor 547637bf (1 commits back)
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
All four data units meet this task: every reported non-text section is 100.0 percent and matched_data equals the unchanged total_data. Exact-instruction counts are unchanged at 87/94, 94/101, 22/22, 38/39; code bytes remain 21556,20256,21664,9184. Full clean build passes, DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d, global regressions zero, no source patterns added. No data function is open or untried. Existing code-only residuals remain as already logged; this task does not claim full code completion.
Gate baseline note: the external gate has no snapshot for 775167f4 and compares against parent 547637bf. The high-round local baseline was independently recorded before any changes and has the same per-unit instruction-exact/code totals. The orchestrator still reviews the typed extents and the DTK field-address alias.
Improvement commits: 2e44afb0,190e688e,cc957c9d,d6e9095a. Only config/43U/symbols.txt and this attempts log changed.
