# AOSS round 5 attempts

Fresh baseline: instruction exact 13/21, matched code 4868/16192, data 3896/3928, fuzzy 68.51902. Pools identical.

Each trial starts from current best; only higher scores are retained. Failed compilation and unchanged source do not count.

AOSS_81401574 initial 98.87597%
- allocated request view precedes uninitialized response view declaration: 100.0%; src 0x204 base 0x204 insns 129/129; diffs 0: []
- allocated request view declared before initialized response view: 100.0%; src 0x204 base 0x204 insns 129/129; diffs 0: []
- request record and response are first two local views: 99.4186%; src 0x204 base 0x204 insns 129/129; diffs 15: [6, 15, 24, 25, 33, 39, 42, 48, 51, 53, 54, 65, 68, 118, 120];      6 M mr r28, r4;        B mr r29, r4
Retained exact candidate

AOSS_814013AC initial 96.32456%
- selected option cursor declared after flags: 96.41228%; src 0x1c8 base 0x1c8 insns 114/114; diffs 35: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 42];      6 M mr r24, r5;        B mr r27, r3
- converted selected length calculated after payload view assignment: 96.57895%; src 0x1c8 base 0x1c8 insns 114/114; diffs 30: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 34, 37, 38, 42, 55, 58, 60, 63, 65];      6 M mr r24, r5;        B mr r27, r3
- response search and selected options share one record view: 96.32456%; src 0x1c8 base 0x1c8 insns 114/114; diffs 43: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39];      6 M mr r24, r5;        B mr r27, r3
Retained best candidate

AOSS_81400E0C initial 95.26316%
- network option parser shares final successful return after loop: 96.89474%; src 0x2f8 base 0x2f8 insns 190/190; diffs 77: [19, 54, 56, 57, 59, 61, 62, 66, 67, 69, 72, 74, 75, 76, 77, 78, 79, 80, 81, 82];     19 M bgt -10911;        B bgt -11215
- network scalar shifts and accumulates in separate statements: 99.447365%; src 0x2f8 base 0x2f8 insns 190/190; diffs 22: [19, 54, 56, 57, 62, 74, 76, 77, 79, 81, 83, 85, 87, 89, 91, 101, 103, 105, 107, 108];     19 M bgt -10911;        B bgt -11215
- network byte view advances after shift and add statements: 99.447365%; src 0x2f8 base 0x2f8 insns 190/190; diffs 22: [19, 54, 56, 57, 62, 74, 76, 77, 79, 81, 83, 85, 87, 89, 91, 101, 103, 105, 117, 122];     19 M bgt -10911;        B bgt -11215
Retained best candidate

AOSS_81401E80 initial 92.72109%
- key view uses same unsigned byte type as key mask writes: 92.72109%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
- unsigned key view declared after mask and packet half count: 92.72109%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
- key mask XOR uses explicit compound assignment with byte alias view: 92.72109%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
Retained best candidate

AOSS_81401C9C initial 83.53425%
- key and swap indices initialized after state-byte initialization: 96.369865%; src 0x124 base 0x124 insns 73/73; diffs 37: [7, 12, 14, 17, 19, 20, 22, 23, 24, 25, 26, 27, 28, 31, 32, 33, 34, 35, 38, 42];      7 M lwz r31, 8(r3);        B lwz r7, 8(r3)
- swap index initialization precedes key index in second phase: 96.438354%; src 0x124 base 0x124 insns 73/73; diffs 36: [7, 12, 14, 17, 19, 20, 22, 23, 24, 25, 26, 27, 28, 31, 32, 33, 34, 35, 38, 42];      7 M lwz r31, 8(r3);        B lwz r7, 8(r3)
- KSA accumulator updates separately before modulo: 96.23288%; src 0x124 base 0x124 insns 73/73; diffs 35: [7, 12, 14, 17, 19, 20, 22, 23, 24, 25, 26, 27, 28, 31, 32, 33, 34, 35, 38, 42];      7 M lwz r31, 8(r3);        B lwz r7, 8(r3)
Retained best candidate

AOSS_81401E80 initial 92.72109%
- mask has same character pointer type as key: 92.72109%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
- mask uses character type with signed stored-byte conversion: 92.72109%; src 0x248 base 0x24c insns 146/147; --- replace mine 6:7 base 6:7;   M    6 mr r28, r3;   B    6 mr r21, r3
- character mask declares packet view after byte loop count: 92.72109%; src 0x248 base 0x24c insns 146/147; --- insert mine 6:6 base 6:22;   B    6 mr r21, r3;   B    7 add r0, r0, r4
Retained best candidate

AOSS_81400E0C initial 99.447365%
- network scalar byte view declared before index: 100.0%; src 0x2f8 base 0x2f8 insns 190/190; diffs 5: [19, 57, 62, 117, 122];     19 M bgt -10911;        B bgt -11215
- IP address scalar loop has its own byte view and index: 99.447365%; src 0x2f8 base 0x2f8 insns 190/190; diffs 22: [19, 57, 62, 114, 116, 117, 122, 134, 136, 137, 139, 141, 143, 145, 147, 149, 151, 161, 163, 165];     19 M bgt -10911;        B bgt -11215
- IP address local index declared before local byte view: 98.89474%; src 0x2f8 base 0x2f8 insns 190/190; diffs 39: [19, 54, 56, 57, 62, 74, 76, 77, 79, 81, 83, 85, 87, 89, 91, 101, 103, 105, 107, 108];     19 M bgt -10911;        B bgt -11215
Retained exact candidate

AOSS_814013AC initial 96.57895%
- selected option traversal reuses response search cursor after advancement: 96.18421%; src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 34, 37, 38, 39, 40, 41, 42, 55, 56];      6 M mr r24, r5;        B mr r27, r3
- shared response cursor declaration follows flags and views: 95.833336%; src 0x1c8 base 0x1c8 insns 114/114; diffs 44: [6, 7, 8, 9, 10, 14, 15, 16, 17, 20, 24, 25, 29, 30, 32, 33, 34, 36, 37, 38];      6 M mr r25, r5;        B mr r27, r3
- shared response cursor with flags declared before all config views: 96.18421%; src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 34, 37, 38, 39, 40, 41, 42, 55, 56];      6 M mr r24, r5;        B mr r27, r3
Retained best candidate

AOSS_814013AC initial 96.57895%
- response parameter serves directly as search and option cursor: 94.38596%; src 0x1c8 base 0x1c8 insns 114/114; diffs 41: [6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 20, 25, 29, 30, 34, 37, 38, 39, 40, 41];      6 M mr r24, r5;        B mr r27, r3
- response length parameter serves as remaining byte count: 96.53509%; src 0x1c8 base 0x1c8 insns 114/114; diffs 31: [7, 10, 14, 16, 20, 24, 25, 29, 30, 34, 37, 38, 39, 42, 55, 56, 58, 60, 61, 63];      7 M mr r30, r5;        B mr r24, r5
- response cursor and remaining count use their original parameters: 94.12281%; src 0x1c8 base 0x1c8 insns 114/114; diffs 47: [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 20, 24, 25, 29, 30, 32, 33, 34];      6 M mr r26, r3;        B mr r27, r3
Retained best candidate

AOSS_81401C9C initial 96.438354%
- state view declared after byte and index temporaries: 99.863014%; src 0x124 base 0x124 insns 73/73; diffs 1: [55];     55 M add r0, r0, r11;        B add r0, r11, r0
- state-byte pointer introduced in initialization block after j reset: 99.863014%; src 0x124 base 0x124 insns 73/73; diffs 1: [55];     55 M add r0, r0, r11;        B add r0, r11, r0
- initializer reads bytes through schedule with state view assigned for swapping: 47.589043%; src 0x160 base 0x124 insns 88/73; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x20(r1);   B    0 stwu r1, -0x10(r1)
Retained best candidate

AOSS_81401C9C initial 99.863014%
- KSA accumulation uses state byte before prior swap index: 100.0%; src 0x124 base 0x124 insns 73/73; diffs 0: []
- KSA accumulator includes current key byte before state byte: 99.863014%; src 0x124 base 0x124 insns 73/73; diffs 1: [55];     55 M add r0, r0, r11;        B add r0, r11, r0
- KSA accumulator adds state byte and then current key byte: 99.31507%; src 0x124 base 0x124 insns 73/73; diffs 7: [47, 53, 55, 61, 62, 63, 64];     47 M li r9, 0;        B li r0, 0
Retained exact candidate

AOSS_81401778 initial 77.92308%
- hello checksum uses canonical eight-byte CRC loop: 77.92308%; src 0x444 base 0x444 insns 273/273; diffs 244: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24];      5 M lis r31, 0;        B lwz r28, 0(0)
- hello stack declaration order follows schedule/record/address/socket fields: 77.94505%; src 0x444 base 0x444 insns 273/273; diffs 240: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24];      5 M lis r31, 0;        B lwz r28, 0(0)
- hello RC4 stream uses single-byte canonical loop: 79.13919%; src 0x44c base 0x444 insns 275/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
Retained best candidate

AOSS_81400830 initial 87.78505%
- decryption stream publishes cursors between byte loads and swaps: 86.149536%; src 0x4f4 base 0x504 insns 317/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- decryption stream cursor sum named before modulo table lookup: 87.59813%; src 0x4f4 base 0x504 insns 317/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- CRC byte cursor advances alongside checksum traversal: 84.638626%; src 0x4f4 base 0x504 insns 317/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
Retained best candidate

AOSS_Init_old initial 28.1875%
- request transaction byte order published before advancing record index: 28.1875%; src 0x17a0 base 0x18c0 insns 1512/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- request records use observed 32-byte frame alignment: 21.166666%; src 0x1918 base 0x18c0 insns 1606/1584; --- replace mine 8:11 base 8:15;   M    8 li r14, 0;   M    9 stw r3, 0x20(r1)
- connection and response waits use adjacent typed interval fields: 28.193813%; src 0x17a0 base 0x18c0 insns 1512/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
Retained best candidate

Vendor key-parameter alias trial: writable character key parameter permits key-mask aliasing; 96.08843%; src 0x24c base 0x24c insns 147/147.

AOSS_81401E80 initial 96.08843%
- vendor transform uses byte packet parameter directly: compile failed
- vendor transform declares explicit second-half packet/temp views: compile failed
- second-half views have outer loop scope: compile failed
Retained best candidate

AOSS_81401E80 initial 96.08843%
- packet byte view initialized after allocations from retained packet parameter: 96.53061%; src 0x24c base 0x24c insns 147/147; diffs 80: [9, 12, 15, 22, 24, 28, 29, 30, 32, 33, 34, 36, 37, 38, 40, 41, 42, 43, 44, 48];      9 M srawi r26, r0, 1;        B srawi r29, r0, 1
- delayed packet byte view declared after allocation pointers: 96.53061%; src 0x24c base 0x24c insns 147/147; diffs 80: [9, 12, 15, 22, 24, 28, 29, 30, 32, 33, 34, 36, 37, 38, 40, 41, 42, 43, 44, 48];      9 M srawi r26, r0, 1;        B srawi r29, r0, 1
- delayed packet and temporary second-half views explicit: 96.734695%; src 0x24c base 0x24c insns 147/147; diffs 76: [9, 12, 15, 22, 24, 28, 29, 33, 34, 36, 37, 38, 40, 41, 42, 43, 44, 48, 49, 52];      9 M srawi r28, r0, 1;        B srawi r29, r0, 1
Retained best candidate

AOSS_81401E80 initial 96.734695%
- half-buffer views, round, and allocation pointers declared in target lifetime order: 98.23129%; src 0x24c base 0x24c insns 147/147; diffs 46: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 79, 81, 82, 83];     53 M li r5, 0;        B li r3, 0
- mask fill and packet XOR have separate traversal indices: 98.23129%; src 0x24c base 0x24c insns 147/147; diffs 46: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 79, 81, 82, 83];     53 M li r5, 0;        B li r3, 0
- separate XOR index declared before mask fill index: 98.23129%; src 0x24c base 0x24c insns 147/147; diffs 46: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 79, 81, 82, 83];     53 M li r5, 0;        B li r3, 0
Retained best candidate

AOSS_81401E80 initial 98.23129%
- XOR assignment expresses both indexed byte reads explicitly: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
- XOR assignment reads key byte before packet byte: 97.993195%; src 0x24c base 0x24c insns 147/147; diffs 46: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 79, 81, 82, 83];     53 M li r5, 0;        B li r3, 0
- XOR byte temporary precedes indexed assignment: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
- XOR key byte temporary precedes packet read and assignment: 97.993195%; src 0x24c base 0x24c insns 147/147; diffs 46: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 79, 81, 82, 83];     53 M li r5, 0;        B li r3, 0
Retained best candidate

AOSS_81401E80 initial 98.5034%
- separate XOR traversal declared before half-buffer lengths: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
- separate XOR traversal declared before allocation pointers: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
- separate XOR traversal declared before key traversal: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
- separate XOR traversal declared after packet byte view: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
- XOR traversal scoped independently after mask fill: 98.5034%; src 0x24c base 0x24c insns 147/147; diffs 39: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 81, 82, 85, 86];     53 M li r5, 0;        B li r3, 0
Retained best candidate

AOSS_81401574 relocation-derived correction: allocation/option failures publish original error-code global: 100.0%; src 0x204 base 0x204 insns 129/129; diffs 0: []; data 3896; sbss 42.857143

AOSS_814002F0 relocation-derived correction: received encryption flag published to connection state, separate from progress callback state: 100.0%; src 0x1e0 base 0x1e0 insns 120/120; diffs 0: []; data 3896; sbss 42.857143

AOSS_81401778 relocation-derived correction: vendor transform failure publishes original error-code global: 79.13919%; src 0x44c base 0x444 insns 275/273; --- replace mine 5:7 base 5:6; data 3896; sbss 42.857143

AOSS_814020CC relocation-derived correction: DHCP timeout clears access-point config state rather than response packet: 100.0%; src 0xf0 base 0xf0 insns 60/60; diffs 0: []; data 3896; sbss 42.857143

Hello loop cleanup: removed unused paired-stream secondByte local; objdiff 79.13919%; retained True.

## Attempt coverage

Every baseline instruction residual has at least three distinct successful source trials; failed/unchanged trials are excluded. Trials that reached exact continue to be counted.

- AOSS_81401574: 3 compiling trials.
- AOSS_814013AC: 9 compiling trials.
- AOSS_81400E0C: 6 compiling trials.
- AOSS_81401E80: 21 compiling trials.
- AOSS_81401C9C: 9 compiling trials.
- AOSS_81401778: 3 compiling trials.
- AOSS_81400830: 3 compiling trials.
- AOSS_Init_old: 3 compiling trials.

## Remaining instruction residuals

| Function | objdiff % | Instructions (mine/original) | Evidence / remaining reason |
|---|---:|---|---|
| AOSS_Init_old | 28.193813 | 1512/1584 | initialization frame, branches, wait/receive loops; target reads r14 before first assignment on early path |
| AOSS_81400830 | 87.78505 | 317/321 | RC4 cursor publication, CRC guards and payload/frame bindings; four instructions short |
| AOSS_81400E0C | 100.0 | 190/190 | objdiff 100; gate/ctxdiff has seven cr1 address-normalization differences; raw bytes identical |
| AOSS_814013AC | 96.57895 | 114/114 | response/flags/remaining-length pointer lifetimes and argument move order |
| AOSS_81401778 | 79.13919 | 275/273 | hello RC4/CRC schedule, table/stack-field bindings; two extra instructions |
| AOSS_81401E80 | 98.5034 | 147/147 | XOR loop scratch registers r3/r4/r5 cycle plus cr1 normalization; all saved registers and instruction count identical |

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

Supplemental native verification PASS: KSA lengths 0/1/7/8/9/16/256/300; all 256 CRC rows; decryption/checksum rejection lengths 1/7/8/9/16/31/32/255/256/257; two-round vendor transform for eight even lengths 2..260 with three key lengths; hello packets for 64 encrypted/plain, active/broadcast, security-flag combinations against prior paired-loop behavior; request initialization preserves three network-order IDs and an eight-byte boundary canary; encryption flag is separate from progress state; three discovery error paths publish the error global; DHCP timeout clears config without altering response data, immediate host and cancellation paths. Decryption tests stub vendor/network conversion to isolate RC4; odd-length vendor-tail behavior is not claimed. All test harnesses are under /tmp.

Initialization uncertainty: original target AOSS_Init_old tests r14 at offset 0xa20 before its first assignment at 0xb2c in linear disassembly. The source keeps its existing initialized fallback; no undefined/uninitialized read was introduced to imitate this. Full initialization still differs and is not claimed exact.

## Final full AOSS gate

Command: `python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/setting/AOSS`

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3896/3928 functions 16/21 fuzzy 69.3757 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 42.857143
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 69.37574
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 28.193813
[src/scene/setting/AOSS]   below 100: AOSS_81400830 87.78505
[src/scene/setting/AOSS]   below 100: AOSS_814013AC 96.57895
[src/scene/setting/AOSS]   below 100: AOSS_81401778 79.13919
[src/scene/setting/AOSS]   below 100: AOSS_81401E80 98.5034
[src/scene/setting/AOSS] baseline: code 4868/16192 data 3896 functions 13 fuzzy 68.5190
regressions vs baseline: 0
global matched_code_percent: 82.75705 -> 82.87778
global fuzzy_match_percent: 95.36525 -> 95.37944
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.46682 -> 89.46682
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
