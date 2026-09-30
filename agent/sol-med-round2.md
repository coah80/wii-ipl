# ATERM and AOSS continuation

Baseline ATERM: 5/26, code 1108/19204, data 18440/18864, fuzzy 50.973755. Baseline AOSS: 8/21, code 2764/16192, data 3896/3928, fuzzy 63.720604. All functions have bodies; existing large state machine and crypto bodies remain incomplete reconstructions. No absent symbols or empty bodies found.

ATERM_8140276C initial 92.10345%
- previous cursor declaration before current cursor: no source change; skipped
- signed record indices: 92.10345%; src 0x2ac base 0x2b8 insns 171/174; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0x80(r1)
- AOSS flags initialized after clear: 91.72988%; src 0x2ac base 0x2b8 insns 171/174; --- replace mine 5:10 base 5:13;   M    5 mr r25, r3;   M    6 mr r26, r4
Retained best candidate

ATERM_81402A24 initial 72.47529%
- record byte count kept signed: no source change; skipped
- allocate nullable buffers before handling failure: 72.380226%; src 0x3cc base 0x41c insns 243/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- multiply-high tick conversion: 75.76426%; src 0x3f4 base 0x41c insns 253/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
Retained best candidate

ATERM_81402E40 initial 99.791664%
- payload clear through byte alias: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- natural checksum loop: 65.208336%; src 0x108 base 0x180 insns 66/96; --- replace mine 5:12 base 5:12;   M    5 mr r28, r5;   M    6 mr r26, r3
- end length as packet byte extent: 95.572914%; src 0x180 base 0x180 insns 96/96; diffs 6: [9, 10, 42, 44, 47, 52];      9 M mr r29, r7;        B mr r3, r27
Retained best candidate

ATERM_81402FC0 initial 67.28148%
- full-width checksum accumulator: 64.76296%; src 0x20c base 0x21c insns 131/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11
- bottom-tested option loop: compile failed
- early return for bad checksum: 66.94074%; src 0x20c base 0x21c insns 131/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11
Retained best candidate

ATERM_814031DC initial 85.7218%
- MAC text uses equal-sized buffers: 85.766914%; src 0x1f4 base 0x214 insns 125/133; --- replace mine 47:48 base 47:48;   M   47 beq 288;   B   47 beq 320
- nibble conversion advances output cursor: 84.293236%; src 0x204 base 0x214 insns 129/133; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x70(r1);   B    0 stwu r1, -0x60(r1)
- inclusive digit bound and pointer-based MAC scan: 85.90225%; src 0x1f4 base 0x214 insns 125/133; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x70(r1);   B    0 stwu r1, -0x60(r1)
Retained best candidate

ATERM_814033F0 initial 65.868614%
- option fields retain converted word width: 67.39416%; src 0x214 base 0x224 insns 133/137; --- replace mine 5:6 base 5:6;   M    5 addi r30, r3, 8;   B    5 addi r29, r3, 8
- bottom-tested parser dispatch: 65.79562%; src 0x21c base 0x224 insns 135/137; --- replace mine 5:6 base 5:6;   M    5 addi r28, r3, 8;   B    5 addi r29, r3, 8
- signed nibble comparisons: 65.32117%; src 0x21c base 0x224 insns 135/137; --- insert mine 7:7 base 7:8;   B    7 li r24, 0; --- replace mine 10:29 base 11:17
Retained best candidate

ATERM_814036D8 initial 73.92742%
- security switch matches original decision tree: 85.22581%; src 0x1ec base 0x1f0 insns 123/124; --- replace mine 14:15 base 14:15;   M   14 beq 340;   B   14 beq 344
- key text passed through one cursor: 87.0%; src 0x1e4 base 0x1f0 insns 121/124; --- replace mine 14:24 base 14:16;   M   14 bne 36;   M   15 addi r3, r25, 0
- counted loop over key records: 73.92742%; src 0x1e0 base 0x1f0 insns 120/124; --- replace mine 14:24 base 14:16;   M   14 bne 36;   M   15 addi r3, r25, 0
Retained best candidate

ATERM_814038C8 initial 35.28917%
- one-shot 500ms wait replaces repeated alarm: 35.700314%; src 0x788 base 0xedc insns 482/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0xe0(r1);   B    0 stwu r1, -0x180(r1)
- bottom-tested state machine and wait buffer order: 35.288116%; src 0x784 base 0xedc insns 481/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0xe0(r1);   B    0 stwu r1, -0x180(r1)
- progress uses semantic structure: 35.28917%; src 0x784 base 0xedc insns 481/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0xe0(r1);   B    0 stwu r1, -0x180(r1)
Retained best candidate

ATERM_81404844 initial 19.615385%
- complete RFC3394 block handling with target initial value and byte counter: 89.89744%; src 0x1bc base 0x1d4 insns 111/117; --- replace mine 6:13 base 6:13;   M    6 lwz r8, 0(0);   M    7 lwz r0, 0(0)
- hoist signed pass product outside block loop: 89.89744%; src 0x1bc base 0x1d4 insns 111/117; --- replace mine 6:13 base 6:13;   M    6 lwz r8, 0(0);   M    7 lwz r0, 0(0)
- natural bytewise counter XOR loop: 62.299145%; src 0x178 base 0x1d4 insns 94/117; --- replace mine 6:13 base 6:13;   M    6 lwz r8, 0(0);   M    7 lwz r0, 0(0)
Retained best candidate

ATERM_81404A18 initial 51.107437%
- complete RFC3394 block handling with target initial value and byte counter: 74.38843%; src 0x1c0 base 0x1e4 insns 112/121; --- replace mine 6:13 base 6:14;   M    6 lwz r8, 0(0);   M    7 lwz r0, 0(0)
- hoist signed pass product outside block loop: 74.38843%; src 0x1c0 base 0x1e4 insns 112/121; --- replace mine 6:13 base 6:14;   M    6 lwz r8, 0(0);   M    7 lwz r0, 0(0)
- natural bytewise counter XOR loop: 55.96694%; src 0x180 base 0x1e4 insns 96/121; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x190(r1);   B    0 stwu r1, -0x1a0(r1)
Retained best candidate

ATERM_81404BFC initial 36.869404%
- complete AES schedules with bounded final expansion for all three key sizes: 52.50746%; src 0x408 base 0x430 insns 258/268; --- replace mine 0:6 base 0:20;   M    0 lbz r7, 1(r4);   M    1 cmplwi r5, 0x80
- direct expanded-key parameter used as advancing cursor: 52.50746%; src 0x408 base 0x430 insns 258/268; --- replace mine 0:6 base 0:20;   M    0 lbz r7, 1(r4);   M    1 cmplwi r5, 0x80
- round limit at loop bottom for 128-bit key: 53.074627%; src 0x404 base 0x430 insns 257/268; --- replace mine 0:6 base 0:20;   M    0 lbz r7, 1(r4);   M    1 cmplwi r5, 0x80
Retained best candidate

ATERM_8140502C initial 35.666668%
- interleaved key-word swaps: 42.355072%; src 0x280 base 0x228 insns 160/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0
- signed indexed round reversal: 38.746376%; src 0x290 base 0x228 insns 164/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0
- counted transformation loop: 11.731884%; src 0x288 base 0x228 insns 162/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0
Retained best candidate

ATERM_81405254 initial 30.464945%
- AES byte assembly uses XOR: 34.23247%; src 0x3c4 base 0x43c insns 241/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- two-round loop with final round exit: compile failed
- signed round count with separately combined key XOR: compile failed
Retained best candidate

ATERM_81405690 initial 26.601477%
- AES byte assembly uses XOR: 34.64945%; src 0x3d4 base 0x43c insns 245/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- two-round loop with final round exit: compile failed
- signed round count with separately combined key XOR: compile failed
Retained best candidate

ATERM_81405254 initial 34.23247%
- two-round AES loop with final round exit matching target structure: 16.295202%; src 0x4a8 base 0x43c insns 298/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- signed remaining round-pair count: 16.295202%; src 0x4a8 base 0x43c insns 298/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- separate round exit before key advancement: 17.630997%; src 0x4a8 base 0x43c insns 298/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
Retained best candidate

ATERM_81405690 initial 34.64945%
- two-round AES loop with final round exit matching target structure: 33.738007%; src 0x4c8 base 0x43c insns 306/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- signed remaining round-pair count: 33.738007%; src 0x4c8 base 0x43c insns 306/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
- separate round exit before key advancement: 31.90037%; src 0x4c8 base 0x43c insns 306/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1)
Retained best candidate

ATERM_81405D0C initial 32.62639%
- complete MD5 accumulator rotation with per-step argument-relative selectors: 53.851387%; src 0xa50 base 0xb40 insns 660/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0xa0(r1)
- MD5 selectors expressed as XOR masks: 44.879166%; src 0xa48 base 0xb40 insns 658/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0xa0(r1)
- natural sixteen-word little-endian block decode: 47.679165%; src 0x970 base 0xb40 insns 604/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0xa0(r1)
Retained best candidate

ATERMi_ApConfigGetState initial 99.42857%
- read bus clock before current time call: 72.942856%; src 0x94 base 0x8c insns 37/35; --- replace mine 4:6 base 4:5;   M    4 stw r30, 8(r1);   M    5 mr r30, r3
- direct timer division using clock conversion expression: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6)
- timer load narrowed to native clock register width: 99.42857%; src 0x8c base 0x8c insns 35/35; diffs 4: [15, 16, 17, 18];     15 M lis r5, -0x8000;        B lis r6, -0x8000
Retained best candidate

ATERM_81402E40 initial 99.791664%
- checksum terminal pointer declared before byte length: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- payload encryption size retained as signed integer: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- end pointer assigned only after header conversion: 94.947914%; src 0x180 base 0x180 insns 96/96; diffs 8: [9, 10, 42, 44, 45, 46, 47, 52];      9 M mr r29, r7;        B mr r3, r27
Retained best candidate

ATERMi_AutoConfigThread initial 94.6%
- callback progress uses three-field structure: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- signed completion state mask in correctly sized progress buffer: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- explicit completion state branch in progress structure: 85.25%; src 0x9c base 0xa0 insns 39/40; --- replace mine 18:21 base 18:22;   M   18 addi r0, r31, -1;   M   19 li r5, -1
Retained best candidate

ATERM_814021BC initial 67.655846%
- interface configuration pointer initialized before IP setup: 64.266235%; src 0x264 base 0x268 insns 153/154; --- replace mine 7:8 base 7:8;   M    7 addi r28, r30, 0;   B    7 addi r30, r30, 0
- wait queue message and buffer order follows target stack slots: 67.64286%; src 0x264 base 0x268 insns 153/154; --- insert mine 7:7 base 7:9;   B    7 addi r30, r30, 0;   B    8 li r4, 0
- host wait expressed as while with shared converted host value: 92.77922%; src 0x274 base 0x268 insns 157/154; --- replace mine 5:8 base 5:8;   M    5 lis r31, 0;   M    6 li r28, 0
Retained best candidate

ATERM_8140276C initial 92.10345%
- previous-record cursor reset at outer loop tail and scoped fallback flags: 94.04023%; src 0x2b0 base 0x2b8 insns 172/174; --- replace mine 5:11 base 5:13;   M    5 mr r25, r3;   M    6 mr r26, r4
- previous record initialized before current record: 94.0115%; src 0x2b0 base 0x2b8 insns 172/174; --- replace mine 5:11 base 5:13;   M    5 mr r25, r3;   M    6 mr r26, r4
- fallback flags set after SSID clear: 94.04023%; src 0x2b0 base 0x2b8 insns 172/174; --- replace mine 5:11 base 5:13;   M    5 mr r25, r3;   M    6 mr r26, r4
Retained best candidate

ATERM_81405ACC initial 0%
- complete two-phase update copy with target eight-byte group bounds: 55.54861%; src 0x21c base 0x240 insns 135/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:7 base 4:10
- signed byte-copy loop cursors: 55.54861%; src 0x21c base 0x240 insns 135/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:7 base 4:10
- cursor-pair copies instead of repeated indexed addresses: 55.54861%; src 0x21c base 0x240 insns 135/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:7 base 4:10
Retained best candidate
Retained complete update implementation: objdiff 55.54861%, 135/144 instructions. Older source had no reported function score; no exact claim.

ATERMi_ApConfigStart initial 86.49515%
- allocate via stored callback: 86.49515%; src 0x1a4 base 0x19c insns 105/103; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x30(r1);   B    0 stwu r1, -0x20(r1)
- tick multiplier commutes operands: 84.11651%; src 0x1a4 base 0x19c insns 105/103; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x30(r1);   B    0 stwu r1, -0x20(r1)
- progress callback loaded from installed function pointer: 93.718445%; src 0x1a0 base 0x19c insns 104/103; --- delete mine 4:5 base 4:4;   M    4 mr r31, r3; --- replace mine 6:7 base 5:6
Retained best candidate

ATERMi_ApConfigEnd initial 87.54263%
- message queues declared within their wait scopes: 85.496124%; src 0x1dc base 0x204 insns 119/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
- join loop expressed as do-while: 85.28682%; src 0x1e8 base 0x204 insns 122/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
- time conversion evaluated directly: 87.54263%; src 0x1dc base 0x204 insns 119/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0
Retained best candidate

ATERM_81402FC0 initial 67.28148%
- signed option payload cursor length: no source change; skipped
- checksum receive pointer read after length decode: 67.28148%; src 0x210 base 0x21c insns 132/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11
- option traversal explicit continuation: 67.28148%; src 0x210 base 0x21c insns 132/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11
Retained best candidate

ATERM_81402A24 initial 75.76426%
- record allocation size held as size_t: no source change; skipped
Retained best candidate

ATERM_81402FC0 initial 67.28148%
- packet and option values stay full-width until usage: 68.577774%; src 0x208 base 0x21c insns 130/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- delete mine 15:16 base 16:16
- full-width checksum accumulated before explicit final narrowing: 67.28148%; src 0x210 base 0x21c insns 132/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11
- option lengths retained as signed word count: 67.28148%; src 0x210 base 0x21c insns 132/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- replace mine 9:10 base 10:11
Retained best candidate

ATERM_81402A24 initial 75.76426%
- record allocation byte count stored in size_t: 75.76426%; src 0x3f4 base 0x41c insns 253/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- iteration counter narrowed to signed timer range: 76.20532%; src 0x3f4 base 0x41c insns 253/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
- record pointer walk and indexed record walk share cursor: 75.76426%; src 0x3f4 base 0x41c insns 253/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1)
Retained best candidate

ATERM reconstruction evidence: all 26 target function names have source bodies. Reconstructed RFC3394 wrap/unwrap initial value, signed counters, block writeback and unwrap ordering; corrected all three AES key schedules; corrected MD5 per-step accumulator/selector semantics and low/high bit counts; reconstructed the missing authentication timestamp digest and protocol option-id bytes in the main state machine. These are partial instruction matches, not completion.
Native validation of extracted unchanged crypto implementations: NIST AES 128/192/256 encryption and decryption vectors passed. MD5 messages of length 0, 1, 3, 55, 56, 64, 130 matched hashlib. Native correctness is supplemental evidence only; MWCC objdiff remains the matching authority.
Data attempts: ordinary local option-id initialization restored the real seven-byte constant sequence; .sdata2 reached 100%. Genuine MD5 fill array emitted locally, then as an ordinary named global after the state-machine function to preserve jump-table/source order. .data remains incomplete because the three generated jump tables still differ. AES tables and round constants remain byte-identical .rodata.
Data attempt: restored the genuine request-options pointer initializer shown in target .sdata; it completed .sdata but moved the response buffer before the thread in .bss and caused objdiff .bss 100 -> 83.33333 and a matched-data regression. Tried source declaration order, original thread name, and original section-aligned network buffer declaration; none passed the regression gate. Restored the pointer attempt and kept the existing BSS layout. No artificial padding, address symbols, or forced sections retained. .sdata and .sbss remain open.

Initial AOSS trial batch failed to compile because of a mistaken message-length field name in the packet dispatcher; corrected the field and reran all trials successfully. Failed batch not counted as attempts.

AOSS_Init_old initial 28.42298%
- full-width wait counters instead of narrowing every update: 28.546717%; src 0x1758 base 0x18c0 insns 1494/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- packet length conversion retains full width: 28.42298%; src 0x1794 base 0x18c0 insns 1509/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- poll arguments given semantic socket events structure: 28.42298%; src 0x1794 base 0x18c0 insns 1509/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
Retained best candidate

AOSS_813FFD68 initial 96.981735%
- validation loops use signed char: 93.69406%; src 0x364 base 0x36c insns 217/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- return failure immediately on invalid character: 82.05023%; src 0x2ec base 0x36c insns 187/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- ascending validation cursor loop: 94.76712%; src 0x374 base 0x36c insns 221/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained best candidate

AOSS_814001B4 initial 88.78481%
- converted packet length stays full width: 88.78481%; src 0x12c base 0x13c insns 75/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- direct opcode return cases: 83.27848%; src 0x124 base 0x13c insns 73/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- full-width validation and branch nesting: no source change; skipped
Retained best candidate

AOSS_814002F0 initial 79.525%
- read manufacturer only after state validation: 85.058334%; src 0x1c4 base 0x1e0 insns 113/120; --- replace mine 6:8 base 6:8;   M    6 mr r30, r3;   M    7 mr r26, r4
- packet sequence values remain full-width: 76.441666%; src 0x1c4 base 0x1e0 insns 113/120; --- replace mine 5:7 base 5:8;   M    5 mr r30, r3;   M    6 mr r26, r4
- direct address error branch: 79.525%; src 0x1c8 base 0x1e0 insns 114/120; --- replace mine 5:7 base 5:8;   M    5 mr r30, r3;   M    6 mr r26, r4
Retained best candidate

AOSS_81400830 initial 77.619934%
- single-byte RC4 generation loop instead of manual pairs: 65.65109%; src 0x3c0 base 0x504 insns 240/321; --- insert mine 6:6 base 6:7;   B    6 addi r29, r3, 0x18; --- insert mine 7:7 base 8:9
- natural CRC byte loop: 60.13084%; src 0x3c4 base 0x504 insns 241/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- narrow RC4 state indices at assignment: 77.619934%; src 0x4b8 base 0x504 insns 302/321; --- insert mine 6:6 base 6:7;   B    6 addi r29, r3, 0x18; --- insert mine 7:7 base 8:9
Retained best candidate

AOSS_81400E0C initial 77.52105%
- signed option lengths and iteration indices: 77.778946%; src 0x2bc base 0x2f8 insns 175/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8
- natural integer byte decode for both address options: 44.963158%; src 0x188 base 0x2f8 insns 98/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8
- address decode accumulation uses OR: 61.963158%; src 0x284 base 0x2f8 insns 161/190; --- replace mine 5:8 base 5:8;   M    5 mr r29, r3;   M    6 mr r30, r4
Retained best candidate

AOSS_814013AC initial 91.70175%
- signed option lengths: 91.70175%; src 0x1cc base 0x1c8 insns 115/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
- apply flags after successful parser call: 84.68421%; src 0x1ec base 0x1c8 insns 123/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
- bounded while loop over selected reply payload: 88.2807%; src 0x1d4 base 0x1c8 insns 117/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
Retained best candidate

AOSS_81401574 initial 92.558136%
- semantic payload extent expression: 92.558136%; src 0x1fc base 0x204 insns 127/129; --- replace mine 5:7 base 5:7;   M    5 lwz r30, 0(0);   M    6 mr r27, r4
- request length remains full-width: 92.209305%; src 0x1f8 base 0x204 insns 126/129; --- replace mine 5:7 base 5:7;   M    5 lwz r30, 0(0);   M    6 mr r27, r4
- initialize destination length before port conversion: 88.31783%; src 0x1fc base 0x204 insns 127/129; --- replace mine 5:7 base 5:7;   M    5 lwz r30, 0(0);   M    6 mr r27, r4
Retained best candidate

AOSS_81401778 initial 71.93407%
- CRC checksum stays full width until header store: 71.93407%; src 0x434 base 0x444 insns 269/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- signed RC4 byte loop index: 71.93407%; src 0x434 base 0x444 insns 269/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- copy hello payload before manufacturer encoding: 71.91575%; src 0x434 base 0x444 insns 269/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
Retained best candidate

AOSS_81401C9C initial 71.9315%
- natural RC4 state initialization loop: 43.342464%; src 0x98 base 0x124 insns 38/73; --- replace mine 0:1 base 0:2;   M    0 li r9, 0;   B    0 stwu r1, -0x10(r1)
- schedule state reset before obtaining byte pointer: 71.9315%; src 0x12c base 0x124 insns 75/73; --- replace mine 0:6 base 0:2;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
- signed key and state indices: 71.9315%; src 0x12c base 0x124 insns 75/73; --- replace mine 0:6 base 0:2;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0
Retained best candidate

AOSS_81401E80 initial 91.80272%
- natural XOR loop over half-packet: 56.455784%; src 0x168 base 0x24c insns 90/147; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x30(r1);   B    0 stwu r1, -0x40(r1)
- half-length via signed division: 87.04082%; src 0x240 base 0x24c insns 144/147; --- replace mine 5:19 base 5:13;   M    5 srawi r0, r4, 1;   M    6 mr r28, r3
- count-down rounds: 88.734695%; src 0x244 base 0x24c insns 145/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
Retained best candidate

AOSS_814020CC initial 76.066666%
- sleep tick product stays 64-bit: 67.51667%; src 0xfc base 0xf0 insns 63/60; --- replace mine 3:6 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- tick duration via explicit multiply-high: 81.65%; src 0xe4 base 0xf0 insns 57/60; --- replace mine 3:5 base 3:6;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- do-while host acquisition loop: 65.066666%; src 0xf8 base 0xf0 insns 62/60; --- replace mine 3:6 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained best candidate

AOSS_81401DC0 initial 99.375%
- CRC output accumulator reuses incoming seed value: 99.375%; src 0xc0 base 0xc0 insns 48/48; diffs 4: [39, 41, 42, 43];     39 M srwi r0, r3, 1;        B srwi r3, r3, 1
- last CRC bit combined with conditional polynomial: 80.916664%; src 0xc8 base 0xc0 insns 50/48; --- delete mine 0:1 base 0:0;   M    0 lis r3, -0x1247; --- replace mine 2:4 base 1:2
- ordinary counted loop for eight CRC polynomial steps: 24.833334%; src 0x40 base 0xc0 insns 16/48; --- insert mine 0:0 base 0:1;   B    0 li r0, 0x100; --- delete mine 1:3 base 2:2
Retained best candidate

AOSS_Init_old initial 28.546717%
- network settings alignment follows target 32-byte stack contract: 24.69697%; src 0x17f8 base 0x18c0 insns 1534/1584; --- replace mine 8:9 base 8:11;   M    8 li r14, 0;   B    8 lhz r4, 0(0)
- request records alignment follows target stack offset a0: 24.69697%; src 0x17f8 base 0x18c0 insns 1534/1584; --- replace mine 8:9 base 8:11;   M    8 li r14, 0;   B    8 lhz r4, 0(0)
- both network settings and request records use observed stack alignment: 24.69697%; src 0x17f8 base 0x18c0 insns 1534/1584; --- replace mine 8:9 base 8:11;   M    8 li r14, 0;   B    8 lhz r4, 0(0)
Retained best candidate

AOSS_814001B4 initial 88.78481%
- opcode uses full-width switch expression after conversion: 88.78481%; src 0x12c base 0x13c insns 75/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- rejection increments written as explicit count stores: 88.78481%; src 0x12c base 0x13c insns 75/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
- validation represented by a named result before rejection: 88.78481%; src 0x12c base 0x13c insns 75/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0
Retained best candidate

AOSS_814013AC initial 91.70175%
- outer response stride evaluated once before cursor advancement: 91.70175%; src 0x1cc base 0x1c8 insns 115/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
- one option cursor serves outer and inner traversal: 91.70175%; src 0x1cc base 0x1c8 insns 115/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
- config flags initialization delayed until matching response is located: 89.60526%; src 0x1cc base 0x1c8 insns 115/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8
Retained best candidate

AOSS .sbss source-order reconstruction: moved real existing address/status declarations into original address order; 28.57143 -> 57.14286.
- explicit zero initialization of owned pointer globals: 42.857143%; original source restored if no improvement.
- explicit zero initialization of runtime status globals: 57.14286%; original source restored if no improvement.
- ordinary zero initialization of access-point address bytes: 28.57143%; original source restored if no improvement.

AOSS dispatch reconstruction: rejected empty/type/validation failures return immediately and opcode dispatch uses a switch; 41.518986 -> 88.78481%, 75/79 instructions. Remaining four instructions are prologue/epilogue save helpers versus individual register saves; three additional real source variations did not change them.
AOSS_Init_old has a body for every observed state path; six distinct attempts logged. Restored narrow wait counters despite a small fuzzy gain from widening, because the original performs signed 16-bit wrapping assignments. Observed 32-byte stack alignment trials all worsened codegen and were restored. Renamed existing decompiler labels to meaningful state/cleanup names.
AOSS .data/.bss/.sdata/.sdata2 remain 100%; ordinary source declaration reordering improves .sbss to 57.14286 but does not finish its symbol associations. Three normal initialization forms produced no further improvement and were restored. No forced sections, padding, address-pinning symbols, or table blobs added.

Current handoff: remaining functions and instruction evidence
ATERM_814021BC 92.77922%: src 0x274 base 0x268 insns 157/154; --- replace mine 5:8 base 5:8;   M    5 lis r31, 0;   M    6 li r28, 0;   M    7 addi r3, r31, 0
ATERM_8140276C 94.04023%: src 0x2b0 base 0x2b8 insns 172/174; --- replace mine 5:11 base 5:13;   M    5 mr r25, r3;   M    6 mr r26, r4;   M    7 mr r27, r5
ATERM_81402A24 76.20532%: src 0x3f4 base 0x41c insns 253/263; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x80(r1);   B    0 stwu r1, -0x90(r1); --- replace mine 2:4 base 2:4
ATERM_81402E40 99.791664%: src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27;     10 M mr r3, r27
ATERM_81402FC0 68.577774%: src 0x208 base 0x21c insns 130/135; --- insert mine 8:8 base 8:9;   B    8 li r31, 0; --- delete mine 15:16 base 16:16;   M   15 li r31, 0
ATERM_814031DC 85.90225%: src 0x1f4 base 0x214 insns 125/133; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x70(r1);   B    0 stwu r1, -0x60(r1); --- replace mine 4:6 base 4:6
ATERM_814033F0 67.39416%: src 0x214 base 0x224 insns 133/137; --- replace mine 5:6 base 5:6;   M    5 addi r30, r3, 8;   B    5 addi r29, r3, 8; --- insert mine 7:7 base 7:8
ATERM_814036D8 87.0%: src 0x1e4 base 0x1f0 insns 121/124; --- replace mine 14:24 base 14:16;   M   14 bne 36;   M   15 addi r3, r25, 0;   M   16 li r0, 4
ATERM_814038C8 41.043114%: src 0x9b4 base 0xedc insns 621/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x140(r1);   B    0 stwu r1, -0x180(r1); --- replace mine 2:4 base 2:4
ATERMi_AutoConfigThread 94.75%: src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0;     22 M srawi r3, r0, 0x1f
ATERM_81404844 92.62393%: src 0x1bc base 0x1d4 insns 111/117; --- replace mine 8:13 base 8:13;   M    8 mr r29, r3;   M    9 mr r22, r4;   M   10 mr r23, r5
ATERM_81404A18 75.82645%: src 0x1c0 base 0x1e4 insns 112/121; --- replace mine 8:13 base 8:14;   M    8 mr r29, r3;   M    9 mr r21, r4;   M   10 mr r22, r5
ATERM_81404BFC 74.36194%: src 0x46c base 0x430 insns 283/268; --- replace mine 6:7 base 6:7;   M    6 cmplwi r5, 0x80;   B    6 cmpwi r5, 0x80; --- delete mine 38:40 base 38:38
ATERM_8140502C 42.355072%: src 0x280 base 0x228 insns 160/138; --- insert mine 5:5 base 5:8;   B    5 stw r30, 8(r1);   B    6 lis r30, 0;   B    7 addi r30, r30, 0
ATERM_81405254 34.23247%: src 0x3c4 base 0x43c insns 241/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1); --- replace mine 2:4 base 2:4
ATERM_81405690 34.64945%: src 0x3d4 base 0x43c insns 245/271; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x40(r1);   B    0 stwu r1, -0x50(r1); --- replace mine 2:4 base 2:4
ATERM_81405ACC 55.54861%: src 0x21c base 0x240 insns 135/144; --- insert mine 2:2 base 2:3;   B    2 slwi r7, r5, 3; --- replace mine 3:7 base 4:10;   M    3 addi r11, r1, 0x20
ATERM_81405D0C 53.851387%: src 0xa50 base 0xb40 insns 660/720; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x90(r1);   B    0 stwu r1, -0xa0(r1); --- replace mine 2:4 base 2:4
ATERMi_ApConfigStart 93.718445%: src 0x1a0 base 0x19c insns 104/103; --- delete mine 4:5 base 4:4;   M    4 mr r31, r3; --- replace mine 6:7 base 5:6;   M    6 mr r30, r8
ATERMi_ApConfigEnd 87.54263%: src 0x1dc base 0x204 insns 119/129; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0xe0;   M    4 bl 0;   B    3 stw r31, 0xdc(r1)
ATERMi_ApConfigGetState 99.42857%: src 0x8c base 0x8c insns 35/35; diffs 3: [17, 18, 20];     17 M lwz r6, 0xf8(r6);        B lwz r0, 0xf8(r6);     18 M addi r0, r5, 0x4dd3
AOSS_Init_old 28.42298%: src 0x1794 base 0x18c0 insns 1509/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b;   B    1 mr r12, r1
AOSS_813FFD68 96.981735%: src 0x364 base 0x36c insns 217/219; --- replace mine 3:5 base 3:7;   M    3 addi r11, r1, 0x20;   M    4 bl 0;   B    3 stw r31, 0x1c(r1)
AOSS_814001B4 88.78481%: src 0x12c base 0x13c insns 75/79; --- replace mine 3:5 base 3:10;   M    3 addi r11, r1, 0x20;   M    4 bl 0;   B    3 stw r31, 0x1c(r1)
AOSS_814002F0 85.058334%: src 0x1c4 base 0x1e0 insns 113/120; --- replace mine 6:8 base 6:8;   M    6 mr r30, r3;   M    7 mr r26, r4;   B    6 mr r26, r3
AOSS_81400830 77.619934%: src 0x4b8 base 0x504 insns 302/321; --- insert mine 6:6 base 6:7;   B    6 addi r29, r3, 0x18; --- insert mine 7:7 base 8:9;   B    8 li r5, 8
AOSS_81400E0C 77.778946%: src 0x2bc base 0x2f8 insns 175/190; --- insert mine 5:5 base 5:6;   B    5 mr r29, r4; --- replace mine 6:8 base 7:8;   M    6 mr r29, r4
AOSS_814013AC 91.70175%: src 0x1cc base 0x1c8 insns 115/114; --- insert mine 6:6 base 6:7;   B    6 mr r27, r3; --- delete mine 7:8 base 8:8;   M    7 mr r27, r3
AOSS_81401574 92.558136%: src 0x1fc base 0x204 insns 127/129; --- replace mine 5:7 base 5:7;   M    5 lwz r30, 0(0);   M    6 mr r27, r4;   B    5 lwz r27, 0(0)
AOSS_81401778 71.93407%: src 0x434 base 0x444 insns 269/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0);   B    5 lwz r28, 0(0)
AOSS_81401C9C 71.9315%: src 0x12c base 0x124 insns 75/73; --- replace mine 0:6 base 0:2;   M    0 stwu r1, -0x20(r1);   M    1 mflr r0;   M    2 stw r0, 0x24(r1)
AOSS_81401DC0 99.375%: src 0xc0 base 0xc0 insns 48/48; diffs 4: [39, 41, 42, 43];     39 M srwi r0, r3, 1;        B srwi r3, r3, 1;     41 M xoris r0, r0, 0xedb8
AOSS_81401E80 91.80272%: src 0x244 base 0x24c insns 145/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3; --- replace mine 8:20 base 8:13
AOSS_814020CC 81.65%: src 0xe4 base 0xf0 insns 57/60; --- replace mine 3:5 base 3:6;   M    3 addi r11, r1, 0x20;   M    4 bl 0;   B    3 stw r31, 0x1c(r1)

Supplemental native crypto validation: NIST AES-128/192/256 encrypt/decrypt vectors passed; MD5 lengths 0, 1, 3, 55, 56, 64, 130 and streaming chunks 1, 7, 55, 63, 64, 65, 127 over 512 bytes passed against hashlib. RFC3394 wrap/unwrap passed using a temporary native test copy that explicitly emulates Wii big-endian counter bytes; unchanged x86 union byte order does not emulate the target. Tests reside under /tmp; MWCC object and gate remain matching authority.
