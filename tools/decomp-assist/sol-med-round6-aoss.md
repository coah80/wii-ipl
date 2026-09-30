# AOSS round 6 attempts

Baseline at 03ed29cc: instruction exact 15/21, code 6436/16192, data 3896/3928, fuzzy 69.37574.

Each distinct compiling source trial is measured and logged. Only higher scores are retained; unchanged and failed candidates do not count.

AOSS_81400E0C initial 100.0%
- network-data parser uses unsigned parsed length: 59.389473%; src 0x280 base 0x2f8 insns 160/190; --- delete mine 2:3 base 2:2;   M    2 li r5, 0x104; --- replace mine 4:7 base 3:5
- network bytes accumulate by multiplication: 100.0%; src 0x2f8 base 0x2f8 insns 190/190; diffs 5: [19, 57, 62, 117, 122];     19 M bgt -10911;        B bgt -11215
- next record offset captured as named byte view: 100.0%; src 0x2f8 base 0x2f8 insns 190/190; diffs 5: [19, 57, 62, 117, 122];     19 M bgt -10911;        B bgt -11215
Retained objdiff-100 original; instruction residual is reported below

AOSS_81401E80 initial 98.5034%
- XOR key byte precedes input byte expression: 97.993195%; src 0x24c base 0x24c insns 147/147; diffs 46: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 79, 81, 82, 83];     53 M li r5, 0;        B li r3, 0
- XOR destination uses ordinary compound assignment: 98.23129%; src 0x24c base 0x24c insns 147/147; diffs 46: [53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72, 73, 74, 76, 77, 78, 79, 81, 82, 83];     53 M li r5, 0;        B li r3, 0
- XOR loop traversal index declared before allocation views: 98.12925%; src 0x24c base 0x24c insns 147/147; diffs 48: [34, 36, 40, 41, 42, 43, 44, 48, 49, 53, 54, 56, 58, 59, 63, 64, 66, 69, 71, 72];     34 M li r5, 0;        B li r6, 0
Retained best candidate

AOSS_814013AC initial 96.57895%
- one option cursor reused after outer response search: 96.18421%; src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 34, 37, 38, 39, 40, 41, 42, 55, 56];      6 M mr r24, r5;        B mr r27, r3
- first config view computed before network-data view: 98.333336%; src 0x1c8 base 0x1c8 insns 114/114; diffs 28: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 34, 42, 55, 58, 60, 63, 65, 68, 70];      6 M mr r24, r5;        B mr r27, r3
- one option cursor with config-before-network evaluation: 96.18421%; src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 34, 37, 38, 39, 40, 41, 42, 55, 56];      6 M mr r24, r5;        B mr r27, r3
Retained best candidate

AOSS_814013AC initial 98.333336%
- single selected-option view declared after flags: 95.833336%; src 0x1c8 base 0x1c8 insns 114/114; diffs 44: [6, 7, 8, 9, 10, 14, 15, 16, 17, 20, 24, 25, 29, 30, 32, 33, 34, 36, 37, 38];      6 M mr r25, r5;        B mr r27, r3
- input state retained in a named selection before remaining length: 98.333336%; src 0x1c8 base 0x1c8 insns 114/114; diffs 28: [6, 7, 10, 14, 15, 16, 17, 20, 25, 29, 30, 34, 42, 55, 58, 60, 63, 65, 68, 70];      6 M mr r24, r5;        B mr r27, r3
- single selected cursor and named state selection: 95.833336%; src 0x1c8 base 0x1c8 insns 114/114; diffs 44: [6, 7, 8, 9, 10, 14, 15, 16, 17, 20, 24, 25, 29, 30, 32, 33, 34, 36, 37, 38];      6 M mr r25, r5;        B mr r27, r3
Retained best candidate

AOSS_81400830 initial 87.78505%
- decryption publishes schedule fields directly for each byte: 84.4486%; src 0x500 base 0x504 insns 320/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- decryption swap byte and lookup sum match their source widths: 84.4486%; src 0x500 base 0x504 insns 320/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- CRC traversal uses signed byte index and original nonempty guard: 91.97196%; src 0x51c base 0x504 insns 327/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
Retained best candidate

AOSS_81401778 initial 79.13919%
- hello encrypted destination initialized as one payload byte view: 76.29304%; src 0x440 base 0x444 insns 272/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- hello RC4 byte output writes through its named encryptedData field: 79.13919%; src 0x44c base 0x444 insns 275/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
- hello request identity view declared after packet response initialization: 79.13919%; src 0x44c base 0x444 insns 275/273; --- replace mine 5:7 base 5:6;   M    5 lis r31, 0;   M    6 lwz r30, 0(0)
Retained best candidate

AOSS_81400830 initial 91.97196%
- unsigned RC4 traversal and separate signed CRC byte index: 92.563866%; src 0x51c base 0x504 insns 327/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- signed CRC index declared before RC4 traversal index: 92.563866%; src 0x51c base 0x504 insns 327/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
- signed CRC loop carries nonempty payload guard: 91.88162%; src 0x520 base 0x504 insns 328/321; --- replace mine 5:6 base 5:7;   M    5 mr r27, r3;   B    5 mr r26, r3
Retained best candidate

Initialization default timeout corrected: input.options is signed s16; comparing against 0xffff was always false. Target compares signed value with -1 and selects 2000 ms. Native compile-time/sign-extension evidence and target offsets 0xb4..0xc0. Score 28.222221%.

AOSS_Init_old initial 28.222221%
- socket poll descriptors expressed as the actual SDK records: 28.174242%; src 0x17a4 base 0x18c0 insns 1513/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x110(r1);   B    0 clrlwi r11, r1, 0x1b
- connection counter separate from unsigned response sleep widths: 28.587122%; src 0x176c base 0x18c0 insns 1499/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- error paths return directly after their resource cleanup: 28.222221%; src 0x179c base 0x18c0 insns 1511/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
Retained best candidate

AOSS_81400830 initial 92.563866%
- RC4 allocation is owned directly by the key schedule: 93.84112%; src 0x518 base 0x504 insns 326/321; --- replace mine 5:6 base 5:7;   M    5 mr r28, r3;   B    5 mr r26, r3
- decryption output destination read before source XOR byte: 93.84112%; src 0x518 base 0x504 insns 326/321; --- replace mine 5:6 base 5:7;   M    5 mr r28, r3;   B    5 mr r26, r3
- RC4 swap sum captured before writes with byte-width swap: 93.84112%; src 0x518 base 0x504 insns 326/321; --- replace mine 5:6 base 5:7;   M    5 mr r28, r3;   B    5 mr r26, r3
Retained best candidate

AOSS_Init_old initial 28.587122%
- poll seconds and microseconds derived directly from milliseconds: 28.618687%; src 0x176c base 0x18c0 insns 1499/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- poll tick terms use target 32-bit products before 64-bit sum: 29.417297%; src 0x175c base 0x18c0 insns 1495/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- typed two-record descriptor array with original timeout arithmetic: 29.073233%; src 0x1764 base 0x18c0 insns 1497/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x110(r1);   B    0 clrlwi r11, r1, 0x1b
Retained best candidate

AOSS_814013AC initial 98.333336%
- response flags declared before response and config views: 98.77193%; src 0x1c8 base 0x1c8 insns 114/114; diffs 22: [6, 7, 14, 15, 16, 17, 20, 25, 29, 30, 34, 42, 55, 60, 65, 70, 75, 81, 87, 95];      6 M mr r24, r5;        B mr r27, r3
- remaining response span initialized before config views: 98.070175%; src 0x1c8 base 0x1c8 insns 114/114; diffs 33: [6, 7, 10, 14, 15, 16, 17, 20, 24, 25, 29, 30, 34, 37, 39, 42, 55, 56, 58, 60];      6 M mr r29, r5;        B mr r27, r3
- response search cursor declared beside selected option cursor: 96.31579%; src 0x1c8 base 0x1c8 insns 114/114; diffs 35: [6, 7, 8, 9, 10, 14, 15, 16, 17, 20, 25, 29, 30, 32, 33, 34, 36, 37, 38, 42];      6 M mr r24, r5;        B mr r27, r3
Retained best candidate

AOSS_Init_old initial 29.417297%
- initial flags failure block precedes the scan branch: 30.063131%; src 0x175c base 0x18c0 insns 1495/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- initial flags guard returns before the scan loop: 30.063131%; src 0x175c base 0x18c0 insns 1495/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- early flags guard and explicit unsigned retry halfword comparison: 30.063131%; src 0x175c base 0x18c0 insns 1495/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
Retained best candidate

AOSS_Init_old initial 30.063131%
- protocol send loop precedes receive and cleanup blocks in target order: 73.34911%; src 0x1758 base 0x18c0 insns 1494/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- protocol order with signed response-count limit from input options: 73.22538%; src 0x1758 base 0x18c0 insns 1494/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
- protocol order with direct error returns after resources are freed: 73.34911%; src 0x1758 base 0x18c0 insns 1494/1584; --- replace mine 0:1 base 0:4;   M    0 stwu r1, -0x100(r1);   B    0 clrlwi r11, r1, 0x1b
Retained best candidate

AOSS_814013AC initial 98.77193%
- input response-length parameter reused for option byte span: 98.20175%; src 0x1c8 base 0x1c8 insns 114/114; diffs 32: [7, 10, 14, 15, 16, 17, 20, 24, 25, 29, 30, 34, 37, 39, 42, 55, 56, 58, 60, 61];      7 M mr r31, r5;        B mr r24, r5
- one cursor after flags with retained configuration evaluation order: 95.833336%; src 0x1c8 base 0x1c8 insns 114/114; diffs 44: [6, 7, 8, 9, 10, 14, 15, 16, 17, 20, 24, 25, 29, 30, 32, 33, 34, 36, 37, 38];      6 M mr r25, r5;        B mr r27, r3
- input length and one cursor retained throughout response parsing: 96.22807%; src 0x1c8 base 0x1c8 insns 114/114; diffs 38: [7, 10, 14, 15, 16, 17, 20, 24, 25, 29, 30, 34, 37, 38, 39, 40, 41, 42, 55, 56];      7 M mr r31, r5;        B mr r24, r5
Retained best candidate

Data linkage trial: CRC table linkage matches extracted global binding; fuzzy 87.587204%, data 3896, objdiff-exact regressions [].
- AOSS_81400830 93.84112%; src 0x518 base 0x504 insns 326/321
- AOSS_81401778 79.13919%; src 0x44c base 0x444 insns 275/273

Data linkage trial: CRC table and runtime state use externally linked storage; fuzzy 87.587204%, data 400, objdiff-exact regressions [].
- AOSS_81400830 93.84112%; src 0x518 base 0x504 insns 326/321
- AOSS_81401778 79.13919%; src 0x44c base 0x444 insns 275/273

Data linkage trial: all recovered small-BSS state objects use original global binding; fuzzy 87.587204%, data 3896, objdiff-exact regressions [].
- AOSS_81400830 93.84112%; src 0x518 base 0x504 insns 326/321
- AOSS_81401778 79.13919%; src 0x44c base 0x444 insns 275/273

AOSS_814013AC initial 98.77193%
- state type table exposed as first declared byte view: 98.77193%; src 0x1c8 base 0x1c8 insns 114/114; diffs 22: [6, 7, 14, 15, 16, 17, 20, 25, 29, 30, 34, 42, 55, 60, 65, 70, 75, 81, 87, 95];      6 M mr r24, r5;        B mr r27, r3
- state type table exposed after scalar parse result: 98.77193%; src 0x1c8 base 0x1c8 insns 114/114; diffs 22: [6, 7, 14, 15, 16, 17, 20, 25, 29, 30, 34, 42, 55, 60, 65, 70, 75, 81, 87, 95];      6 M mr r24, r5;        B mr r27, r3
- explicit state table and one option cursor declared after scalars: 95.92105%; src 0x1c8 base 0x1c8 insns 114/114; diffs 43: [6, 7, 8, 9, 10, 14, 15, 16, 17, 20, 25, 29, 30, 32, 33, 34, 36, 37, 38, 39];      6 M mr r24, r5;        B mr r27, r3
Retained best candidate

AOSS_81400830 initial 93.84112%
- encrypted payload typed view precedes crypto locals: 93.84112%; src 0x518 base 0x504 insns 326/321; --- replace mine 5:6 base 5:7;   M    5 mr r28, r3;   B    5 mr r26, r3
- encrypted payload typed view follows result declaration: 93.84112%; src 0x518 base 0x504 insns 326/321; --- replace mine 5:6 base 5:7;   M    5 mr r28, r3;   B    5 mr r26, r3
- payload byte-span view assigned before manufacturer decode call: 93.84112%; src 0x518 base 0x504 insns 326/321; --- replace mine 5:6 base 5:7;   M    5 mr r28, r3;   B    5 mr r26, r3
Retained best candidate

Retained initialization changes: signed -1 default timeout selects 2000 ms; unsigned halfword sleep durations and an integer connection counter match the target load/compare widths; poll timeout uses 32-bit products widened for the 64-bit tick sum. The initial error branch comes first. The send loop now precedes receive, socket cleanup and error reporting, matching the target block order. No branches or real functions were removed. Initialization rose from 28.193813 to 73.34911% and total AOSS fuzzy from 69.37574 to 87.587204%.

Decryption retains unsigned RC4 traversal and a separate signed CRC traversal index. The schedule owns its allocated state directly instead of an extra stateBytes alias. Native checks verify payload and rejection behavior at odd/even and unroll-boundary lengths. Remaining differences include frame/payload bindings and five extra instructions; no instruction-exact claim.

Data trials changed only real state-object linkage. CRC linkage had no gain. External runtime linkage regressed data from 3896 to 400 and was reverted. Small-BSS global linkage had no gain and was reverted. All original storage declarations remain. Every data section except the .sbss symbol correspondence remains 100%; physical small-BSS bytes and observed relocation offsets are identical. No padding was added to reproduce extracted section alignment tails.

Supplemental full-initialization verification PASS under /tmp: flags rejection, cancellation cleanup, explicit 1501 ms polling, -1 selecting 2000 ms, eleven-poll retry exhaustion, and discovery/hello/final transitions. Five scenarios with explicit timeouts match the previous body for returns, status/error, poll ticks, protocol calls, allocation/free and nonce traces; the native comparison reproduces big-endian wait halfwords. The transition stub observes one configuration allocation overwritten, both before and after the reordering and consistent with the original allocation block. This existing behavior was preserved. Native verification does not assert instruction identity.

## Attempt coverage

Every baseline instruction residual has at least three distinct successful source trials. Failed and unchanged trials are excluded. Only function-name initial lines start a new count; labels beginning with "initial" remain attempts of their function.

- AOSS_81400E0C: 3 compiling trials.
- AOSS_81401E80: 3 compiling trials.
- AOSS_814013AC: 21 compiling trials.
- AOSS_81400830: 12 compiling trials.
- AOSS_81401778: 3 compiling trials.
- AOSS_Init_old: 12 compiling trials.

## Remaining instruction residuals

| Function | objdiff % | Instructions (mine/original) | Evidence / remaining reason |
|---|---:|---|---|
| AOSS_Init_old | 73.34911 | 1494/1584 | initialization frame/alignment and remaining loop scheduling; 90 instructions short, including preserved initialized fallback for target r14 |
| AOSS_81400830 | 93.84112 | 326/321 | RC4 cursor publication, payload/frame bindings and store/reload scheduling; five extra instructions |
| AOSS_81400E0C | 100.0 | 190/190 | objdiff 100; gate/ctxdiff has cr1 address-normalization differences; raw bytes identical |
| AOSS_814013AC | 98.77193 | 114/114 | response/flags/remaining-length pointer lifetimes and argument move order |
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

Prior and current supplemental native verification PASS: KSA lengths 0/1/7/8/9/16/256/300; all 256 CRC rows; decryption/checksum rejection lengths 1/7/8/9/16/31/32/255/256/257; two-round vendor transform for eight even lengths 2..260 with three key lengths; hello packets for 64 encrypted/plain, active/broadcast, security-flag combinations against prior paired-loop behavior; request initialization preserves three network-order IDs and an eight-byte boundary canary; encryption flag is separate from progress state; three discovery error paths publish the error global; DHCP timeout clears config without altering response data, immediate host and cancellation paths. Decryption tests stub vendor/network conversion to isolate RC4; odd-length vendor-tail behavior is not claimed. All test harnesses are under /tmp.

Initialization uncertainty: original target AOSS_Init_old tests r14 at offset 0xa20 before its first assignment at 0xb2c in linear disassembly. The source keeps its existing initialized fallback; no undefined/uninitialized read was introduced to imitate this. Full initialization still differs and is not claimed exact.
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3896/3928 functions 16/21 fuzzy 87.5872 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 42.857143
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 87.587204
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 73.34911
[src/scene/setting/AOSS]   below 100: AOSS_81400830 93.84112
[src/scene/setting/AOSS]   below 100: AOSS_814013AC 98.77193
[src/scene/setting/AOSS]   below 100: AOSS_81401778 79.13919
[src/scene/setting/AOSS]   below 100: AOSS_81401E80 98.5034
[src/scene/setting/AOSS] baseline: code 6436/16192 data 3896 functions 16 fuzzy 69.3757
regressions vs baseline: 0
global matched_code_percent: 83.23489 -> 83.23489
global fuzzy_match_percent: 96.70702 -> 96.80967
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93520
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
