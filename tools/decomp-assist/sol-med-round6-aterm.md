# ATERM round 6 attempts

Baseline at 03ed29cc: instruction exact 11/26, code 6576/19204, data 18448/18864, fuzzy 90.81421.

Each distinct compiling source trial is measured and logged. Only higher scores are retained; unchanged and failed candidates do not count.

ATERM_81402FC0 initial 100.0%
- checksum cursor increments after accumulation: 87.59259%; src 0x1fc base 0x21c insns 127/135; --- replace mine 5:6 base 5:6;   M    5 mr r25, r3;   B    5 mr r27, r3
- success mode uses conditional value expression: 96.39259%; src 0x218 base 0x21c insns 134/135; --- replace mine 18:19 base 18:19;   M   18 bge -3631;   B   18 bge -3647
- packet checksum length is named as a byte span: compile failed
Retained objdiff-100 original; instruction residual is reported below

ATERM_81402E40 initial 99.791664%
- checksum initialized after payload header call: 96.34375%; src 0x180 base 0x180 insns 96/96; diffs 9: [9, 10, 11, 12, 13, 14, 15, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- payload byte view initialized for header memset: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
- payload header destination uses end view before checksum span: 99.791664%; src 0x180 base 0x180 insns 96/96; diffs 4: [9, 10, 47, 52];      9 M mr r29, r7;        B mr r3, r27
Retained best candidate

ATERM_81402FC0 initial 100.0%
- checksum halfword widened only at comparison: 100.0%; src 0x21c base 0x21c insns 135/135; diffs 2: [18, 23];     18 M bge -3631;        B bge -3647
Retained objdiff-100 original; instruction residual is reported below

ATERM_8140502C initial 99.565216%
- round swaps share one full-scope temporary word: 98.62319%; src 0x228 base 0x228 insns 138/138; diffs 25: [10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30];     10 M mr r5, r31;        B mr r4, r31
- swap temporary declared before reversal indices: 98.62319%; src 0x228 base 0x228 insns 138/138; diffs 25: [10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30];     10 M mr r5, r31;        B mr r4, r31
- round swap traverses by named four-word span: 99.565216%; src 0x228 base 0x228 insns 138/138; diffs 11: [11, 15, 18, 20, 21, 24, 25, 28, 29, 33, 35];     11 M slwi r6, r3, 2;        B slwi r8, r3, 2
Retained best candidate

ATERM_814033F0 initial 99.56204%
- parser result declared before key view: 99.56204%; src 0x224 base 0x224 insns 137/137; diffs 11: [11, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];     11 M li r23, 0;        B li r22, 0
- key view declared at option-loop scope: 99.56204%; src 0x224 base 0x224 insns 137/137; diffs 11: [11, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];     11 M li r23, 0;        B li r22, 0
- zero parser result initialized immediately before option iteration: 97.66423%; src 0x224 base 0x224 insns 137/137; diffs 18: [7, 8, 9, 10, 11, 12, 13, 14, 65, 66, 81, 82, 85, 86, 96, 97, 98, 101];      7 M bl 0;        B li r24, 0
Retained best candidate

ATERM_8140276C initial 99.166664%
- current record view assigned after flags: 99.08046%; src 0x2b8 base 0x2b8 insns 174/174; diffs 28: [8, 9, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 69, 70, 74, 82, 84, 87, 88, 89];      8 M addi r27, r4, 4;        B addi r31, r3, 4
- both record views assigned after scalar declarations: 99.166664%; src 0x2b8 base 0x2b8 insns 174/174; diffs 27: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 69, 70, 74, 82, 84, 87, 88, 89, 90];      8 M addi r20, r3, 4;        B addi r31, r3, 4
- fallback presence flags initialized in previous/current order: 99.05173%; src 0x2b8 base 0x2b8 insns 174/174; diffs 31: [8, 11, 12, 13, 18, 29, 30, 34, 41, 54, 60, 69, 70, 74, 82, 84, 87, 88, 89, 90];      8 M addi r20, r3, 4;        B addi r31, r3, 4
Retained best candidate

ATERM_81404844 initial 98.97436%
- wrap loop scalars declared in block/round/pass order: 98.67522%; src 0x1d4 base 0x1d4 insns 117/117; diffs 24: [8, 18, 19, 27, 30, 36, 37, 38, 39, 40, 41, 42, 43, 45, 48, 54, 58, 60, 99, 100];      8 M mr r24, r3;        B mr r25, r3
- wrap block offset declared before output view at loop scope: 98.67522%; src 0x1d4 base 0x1d4 insns 117/117; diffs 24: [8, 18, 19, 27, 30, 36, 37, 38, 39, 40, 41, 42, 43, 45, 48, 54, 58, 60, 99, 100];      8 M mr r24, r3;        B mr r25, r3
- wrap count assigned before expanded key result: no source change; skipped
Retained best candidate

ATERM_81404BFC initial 98.94403%
- first key word declared before expansion scratch word: 98.94403%; src 0x430 base 0x430 insns 268/268; diffs 49: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 45, 48, 49];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
- initial word declarations follow initial byte order: 98.75746%; src 0x430 base 0x430 insns 268/268; diffs 53: [5, 7, 8, 10, 13, 14, 16, 19, 20, 22, 25, 26, 28, 30, 31, 32, 34, 40, 41, 43];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
- initial word byte packing uses ordinary shift/add disjoint fields: 94.89552%; src 0x430 base 0x430 insns 268/268; diffs 68: [5, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 19, 20, 21, 22, 23, 25, 26, 27, 28];      5 M lbz r7, 6(r4);        B lbz r7, 2(r4)
Retained best candidate

ATERM_81404844 initial 98.97436%
- wrap computes pass contribution at function scope per iteration: compile failed
Retained best candidate

ATERM_814021BC initial 96.61688%
- interface configuration view assigned before its memset: 95.87013%; src 0x268 base 0x268 insns 154/154; diffs 52: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- IP configuration cleared through its aggregate field: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
- converted host declared after typed config views: 96.61688%; src 0x268 base 0x268 insns 154/154; diffs 54: [7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27];      7 M addi r3, r30, 0;        B addi r30, r30, 0
Retained best candidate

ATERM_814031DC initial 90.766914%
- MAC formatting uses bounded do-while loops: 90.22556%; src 0x20c base 0x214 insns 131/133; --- replace mine 47:48 base 47:49;   M   47 beq 312;   B   47 beq 320
- MAC do-while terminates at equality: 90.22556%; src 0x20c base 0x214 insns 131/133; --- replace mine 47:48 base 47:49;   M   47 beq 312;   B   47 beq 320
- MAC colon branch retains bounded unsigned traversal: 89.3985%; src 0x20c base 0x214 insns 131/133; --- replace mine 47:48 base 47:49;   M   47 beq 312;   B   47 beq 320
Retained best candidate

ATERMi_AutoConfigThread initial 94.75%
- completion state expresses ordinary equality selection: 94.0%; src 0xa0 base 0xa0 insns 40/40; diffs 9: [20, 21, 22, 23, 24, 26, 28, 29, 30];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- completion mask uses named unsigned difference: 82.725%; src 0xa0 base 0xa0 insns 40/40; diffs 9: [18, 19, 20, 21, 22, 23, 24, 25, 26];     18 M addi r5, r31, -1;        B addi r3, r31, -1
- progress result loaded before completion fields are published: 94.3%; src 0xa0 base 0xa0 insns 40/40; diffs 6: [20, 22, 23, 29, 30, 31];     20 M nor r0, r3, r0;        B nor r3, r3, r0
Retained best candidate

Scan allocation relocation correction: original instruction at function offset 0x98 references scan-limit .sdata offset 4, not buffer-size offset 8. Use gAtermScanLimit for scanBufferBytes, preserving the separate buffer-size global assigned by Start. objdiff 90.34981%.

ATERM_81402A24 initial 90.34981%
- first descriptor view initialized once outside scanning loop: 92.357414%; src 0x410 base 0x41c insns 260/263; --- replace mine 6:7 base 6:7;   M    6 li r25, 0;   B    6 li r4, 0
- SSID oversized branch before valid-length branch: 90.406845%; src 0x40c base 0x41c insns 259/263; --- replace mine 6:7 base 6:7;   M    6 li r24, 0;   B    6 li r4, 0
- persistent descriptor view and original SSID branch direction: 92.41445%; src 0x410 base 0x41c insns 260/263; --- replace mine 6:7 base 6:7;   M    6 li r25, 0;   B    6 li r4, 0
- scan pointer alignment uses signed integer address statements: 90.34981%; src 0x40c base 0x41c insns 259/263; --- replace mine 6:7 base 6:7;   M    6 li r24, 0;   B    6 li r4, 0
Retained best candidate

ATERM_81404844 initial 98.97436%
- wrap pass contribution stored after block byte-view declaration: 98.97436%; src 0x1d4 base 0x1d4 insns 117/117; diffs 20: [8, 27, 30, 36, 38, 39, 40, 41, 42, 45, 48, 54, 58, 60, 99, 100, 101, 103, 104, 106];      8 M mr r24, r3;        B mr r25, r3
Retained best candidate

ATERM_81405ACC initial 88.583336%
- MD5 byte copying uses explicit source/destination views: 74.416664%; src 0x21c base 0x240 insns 135/144; --- delete mine 5:6 base 5:5;   M    5 mr r31, r4; --- insert mine 7:7 base 6:7
- MD5 byte-view loops use indexed reads and writes: 72.854164%; src 0x228 base 0x240 insns 138/144; --- replace mine 15:16 base 15:16;   M   15 rlwinm r7, r6, 0x1d, 0x1a, 0x1f;   B   15 rlwinm r0, r6, 0x1d, 0x1a, 0x1f
- MD5 byte-view source declared before destination: 74.729164%; src 0x21c base 0x240 insns 135/144; --- delete mine 5:6 base 5:5;   M    5 mr r31, r4; --- insert mine 7:7 base 6:7
Retained best candidate

Protocol record layout re-derived from target: original response header begins at pooled BSS 0x1498, the named ConfigurationResult.responseLength field; options begin at adjacent response buffer 0x14a0, authentication challenge at 0x1c98. Previous source incorrectly treated response buffer 0x14a0 as the header and shifted all these views by eight bytes. Correct typed header view and challenge access: 86.15353%; src 0xf30 base 0xedc insns 972/951.

Request-options pointer initializer corrected to response-buffer data start: .rela.sdata offset 0x28 now references named response buffer with addend zero, matching the original rather than eight. No new storage or address symbols.

ATERM_814038C8 initial 86.15353%
- protocol uses SDK millisecond/tick conversions: 86.15353%; src 0xf30 base 0xedc insns 972/951; --- delete mine 5:6 base 5:5;   M    5 lis r3, 0; --- replace mine 7:9 base 6:8
- packet buffer uses named aggregate field at each call: 86.57519%; src 0xf34 base 0xedc insns 973/951; --- delete mine 5:6 base 5:5;   M    5 lis r26, 0; --- replace mine 7:9 base 6:8
- protocol callbacks reuse one function-scope progress record: 86.11672%; src 0xf30 base 0xedc insns 972/951; --- replace mine 0:1 base 0:1;   M    0 stwu r1, -0x160(r1);   B    0 stwu r1, -0x180(r1)
Retained best candidate

ATERM_81405254 initial 61.94834%
- AES initial byte packing uses ordered big-endian XOR fields: 61.98524%; src 0x43c base 0x43c insns 271/271; diffs 191: [24, 26, 28, 30, 32, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45, 46, 47, 48, 49, 50];     24 M slwi r7, r7, 0x18;        B srawi r30, r4, 1
- AES state initialization follows reverse word order: 57.701107%; src 0x43c base 0x43c insns 271/271; diffs 234: [5, 7, 9, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29];      5 M lbz r12, 0xa(r5);        B lbz r12, 6(r5)
- AES round-table declarations precede state initialization: 62.110703%; src 0x43c base 0x43c insns 271/271; diffs 214: [12, 13, 18, 20, 24, 26, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41];     12 M slwi r21, r11, 0x18;        B slwi r22, r11, 0x18
Retained best candidate

ATERM_81405690 initial 59.273064%
- AES initial byte packing uses ordered big-endian XOR fields: 59.309963%; src 0x43c base 0x43c insns 271/271; diffs 199: [24, 26, 28, 30, 32, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45, 46, 47, 48, 49, 50];     24 M slwi r7, r7, 0x18;        B srawi r30, r4, 1
- AES state initialization follows reverse word order: 55.671585%; src 0x43c base 0x43c insns 271/271; diffs 239: [5, 7, 9, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29];      5 M lbz r12, 0xa(r5);        B lbz r12, 6(r5)
- AES round-table declarations precede state initialization: 57.1845%; src 0x43c base 0x43c insns 271/271; diffs 220: [12, 13, 18, 20, 24, 26, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41];     12 M slwi r21, r11, 0x18;        B slwi r22, r11, 0x18
Retained best candidate

Scan-settings clear extent: target case 7 clears 0x254 bytes, while extracted global occupies 0x258. Reducing inferred trailing field from 0x14 to 0x10 regressed pooled BSS correspondence from 100 to 50% and was reverted. Keep existing object layout, use original explicit 0x254 clear length. No symbol sizes changed.

ATERMi_AutoConfigThread initial 94.75%
- completion NOR expression consumed directly by signed state arithmetic: 94.75%; src 0xa0 base 0xa0 insns 40/40; diffs 3: [20, 22, 23];     20 M nor r0, r3, r0;        B nor r3, r3, r0
- completion mask uses De Morgan intersection of complements: 77.725%; src 0xa4 base 0xa0 insns 41/40; --- replace mine 18:19 base 18:21;   M   18 addi r0, r31, -1;   B   18 addi r3, r31, -1
- signed completion mask retains arithmetic shift type: compile failed
Retained best candidate

Data checkpoint regression diagnosed: replacing the early response-global view removed its first genuine function reference, so file IPA emitted OSThread before the response buffer. Corrected session-key view uses the response global at its original encrypted-option capacity 0x7f8, with a named session union member. Union storage size is unchanged; the field is used for the real session key. This restores early response-global usage and preserves physical BSS object order without dummy references or padding.

Stable corrected layout checkpoint PASS: code 6576/19204, data 18504/18864, fuzzy 91.468864, instruction exact 11/26, regressions 0. .bss, .rodata, .sdata and .sdata2 all 100%; .sdata initializer relocation now exact.

Native behavior verification PASS: AES-128/192/256 encrypt/decrypt, MD5 boundary lengths 0/1/3/55/56/64/130, scan-list fallback/security/empty transitions and normalized MAC association formatting. Typed protocol-header/options/challenge/digest/session offsets and 0x254 scan-clear boundary verified in a contiguous module-layout test. These native checks do not assert instruction identity.

## Attempt coverage

Every baseline instruction residual has at least three distinct successful source trials. Failed and unchanged trials are excluded. Only function-name initial lines start a new count; labels beginning with "initial" remain attempts of their function.

- ATERM_81402FC0: 3 compiling trials.
- ATERM_81402E40: 3 compiling trials.
- ATERM_8140502C: 3 compiling trials.
- ATERM_814033F0: 3 compiling trials.
- ATERM_8140276C: 3 compiling trials.
- ATERM_81404844: 3 compiling trials.
- ATERM_81404BFC: 3 compiling trials.
- ATERM_814021BC: 3 compiling trials.
- ATERM_814031DC: 3 compiling trials.
- ATERMi_AutoConfigThread: 5 compiling trials.
- ATERM_81402A24: 4 compiling trials.
- ATERM_81405ACC: 3 compiling trials.
- ATERM_814038C8: 3 compiling trials.
- ATERM_81405254: 3 compiling trials.
- ATERM_81405690: 3 compiling trials.

## Remaining instruction residuals

| Function | objdiff % | Instructions (mine/original) | Evidence / remaining reason |
|---|---:|---|---|
| ATERM_814021BC | 96.61688 | 154/154 | settings aggregate base-address scheduling and temporary register allocation |
| ATERM_8140276C | 99.166664 | 174/174 | current/previous record and fallback flag register cycles |
| ATERM_81402A24 | 92.41445 | 260/263 | scan descriptor-view scheduling, alignment expression and MAC-loop guard; three instructions short |
| ATERM_81402E40 | 99.791664 | 96/96 | two argument-move ordering differences plus two cr1 normalization differences |
| ATERM_81402FC0 | 100.0 | 135/135 | objdiff 100; gate/ctxdiff has two cr1 address-normalization differences; raw bytes identical |
| ATERM_814031DC | 90.766914 | 129/133 | explicit terminal MAC break versus original CTR loop; four instructions short |
| ATERM_814033F0 | 99.56204 | 137/137 | result/key pointer register cycle |
| ATERM_814038C8 | 85.933754 | 978/951 | protocol frame and option/authentication loop scheduling; corrected response/session buffer views; frame and option/authentication scheduling still differ |
| ATERMi_AutoConfigThread | 94.75 | 40/40 | NOR mask temporary and result-load scheduling |
| ATERM_81404844 | 98.97436 | 117/117 | wrap pass/block/output/byte-offset register allocation |
| ATERM_81404BFC | 98.94403 | 268/268 | initial key byte-load order and AES-128 substitution view allocation |
| ATERM_8140502C | 99.565216 | 138/138 | round-reversal index/swap register allocation |
| ATERM_81405254 | 62.110703 | 271/271 | AES input, round and final XOR scheduling/register allocation; instruction count now identical |
| ATERM_81405690 | 59.309963 | 271/271 | inverse AES input, round and final XOR scheduling/register allocation; instruction count now identical |
| ATERM_81405ACC | 88.583336 | 139/144 | MD5 input-copy guards and state/index scheduling; five instructions short |

## Data audit

No artificial data objects or symbol names added. String pools are identical. These C units contain no vtables.

- .bss: mine 8144, original 8160 bytes; prefix mismatches 0/8144; extra alignment tail bytes 16, all zero True.
- .rodata: mine 10280, original 10280 bytes; prefix mismatches 0/10280; extra alignment tail bytes 0, all zero True.
- .data: mine 280, original 280 bytes; prefix mismatches 0/280; extra alignment tail bytes 0, all zero True.
- .sdata2: mine 7, original 8 bytes; prefix mismatches 0/7; extra alignment tail bytes 1, all zero True.
- .sdata: mine 53, original 56 bytes; prefix mismatches 0/53; extra alignment tail bytes 3, all zero True.
- .sbss: mine 80, original 80 bytes; prefix mismatches 0/80; extra alignment tail bytes 0, all zero True.

ATERM_81402FC0 raw .text bytes identical: True. SHA-256 mine 91a60a7585553b8702d6f6ff83d5a91eedfd3cbaf3a04fb25501c637a6f84acd, original 91a60a7585553b8702d6f6ff83d5a91eedfd3cbaf3a04fb25501c637a6f84acd. Raw bytes do not assert relocation identity. The gate instruction count remains authoritative.

Relocations at corresponding instruction offsets in objdiff-exact functions (observed mappings only, no object/config override):

- (('.sbss', 'gAtermAllocate', 12, 4, 0), ('.sbss', 'lbl_81698C9C', 12, 4, 0))
- (('.sbss', 'gAtermAllocation', 20, 4, 0), ('.sbss', 'lbl_81698CA4', 20, 4, 0))
- (('.sbss', 'gAtermCancelRequested', 76, 4, 0), ('.sbss', 'lbl_81698CDC', 76, 4, 0))
- (('.sbss', 'gAtermProgressCallback', 8, 4, 0), ('.sbss', 'lbl_81698C98', 8, 4, 0))
- (('.sbss', 'gAtermRelease', 16, 4, 0), ('.sbss', 'lbl_81698CA0', 16, 4, 0))
- (('.sbss', 'gAtermResult', 4, 4, 0), ('.sbss', 'lbl_81698C94', 4, 4, 0))
- (('.sbss', 'gAtermState', 0, 4, 0), ('.sbss', 'lbl_81698C90', 0, 4, 0))
- (('.sbss', 'gAtermThreadStarted', 24, 4, 0), ('.sbss', 'lbl_81698CA8', 24, 4, 0))
- (('.sdata', 'gAtermDeadline', 0, 4, 0), ('.sdata', 'lbl_81697218', 0, 4, 0))
- (('.sdata', 'gAtermScanBufferSize', 8, 4, 0), ('.sdata', 'lbl_81697220', 8, 4, 0))
- (('.sdata', 'gAtermScanLimit', 4, 4, 0), ('.sdata', 'lbl_8169721C', 4, 4, 0))

Data is not claimed 100%: ATERM switch-table and anonymous small-BSS symbol mappings remain incomplete; initialized .sdata is now 100%. Original extracted alignment tails are not synthesized.

Supplemental native verification PASS: AES-128/192/256 encrypt/decrypt, MD5 lengths 0/1/3/55/56/64/130, scan-list fallback/reset transitions, normalized BSSID and six-byte MAC formatting. Native verification checks behavior; the MWCC/object gate checks matching.
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 6576/19204 data 18504/18864 functions 12/26 fuzzy 91.4689 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 11/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match None
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 38.88889
[src/scene/setting/ATERM]   section .sdata size 56 match 100.0
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 91.468864
[src/scene/setting/ATERM]   below 100: ATERM_814021BC 96.61688
[src/scene/setting/ATERM]   below 100: ATERM_8140276C 99.166664
[src/scene/setting/ATERM]   below 100: ATERM_81402A24 92.41445
[src/scene/setting/ATERM]   below 100: ATERM_81402E40 99.791664
[src/scene/setting/ATERM]   below 100: ATERM_814031DC 90.766914
[src/scene/setting/ATERM]   below 100: ATERM_814033F0 99.56204
[src/scene/setting/ATERM]   below 100: ATERM_814038C8 85.933754
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERM_81404844 98.97436
[src/scene/setting/ATERM]   below 100: ATERM_81404BFC 98.94403
[src/scene/setting/ATERM]   below 100: ATERM_8140502C 99.565216
[src/scene/setting/ATERM]   below 100: ATERM_81405254 62.110703
[src/scene/setting/ATERM]   below 100: ATERM_81405690 59.309963
[src/scene/setting/ATERM]   below 100: ATERM_81405ACC 88.583336
[src/scene/setting/ATERM] baseline: code 6576/19204 data 18448 functions 12 fuzzy 90.8142
regressions vs baseline: 0
global matched_code_percent: 83.23489 -> 83.23489
global fuzzy_match_percent: 96.70702 -> 96.71121
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93520
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
