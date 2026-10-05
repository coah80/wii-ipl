# da2 de-asm attempts

Base: 9d40859ee8f4ee37dc692e444727d17367bfcbeb, agent/w1005/da2.
Scope: CDBDatabase, CDBFileSystemUtils, NWC24Manage, NWC24UserId, vf/develop/nand_drv, WDScan.
All six units begin linked with every function, code byte and data byte exact.
Initial DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
Each conversion starts from the original-object Ghidra export, uses typed C, and requires identical pools, exact objdiff, zero ctxdiff differences and a full gate before its own commit.
Evidence files live in build/da2 while this run is active. Rejected conversions restore the existing asm before final verification.

CDBDatabaseSearchCallCallback / callback-1: Ghidra callback branch with typed instance flags and success nesting. objdiff 100.0%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0xf4 base 0xf4 insns 61/61; diffs 0: []

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
CDBDatabaseSearchRecordLayer / record-1: Ghidra traversal with typed search buffer and record key array, current directory date prototype. objdiff 97.76286%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x704 base 0x6fc insns 449/447; --- replace mine 6:7 base 6:9

CDBDatabaseSearchRecordLayer / record-2: Separate dictionary result to preserve call order, finished local before path bounds. objdiff 98.85906%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x704 base 0x6fc insns 449/447; --- replace mine 6:7 base 6:9

CDBDatabaseSearchRecordLayer / record-3: Repair five-argument target call through guarded header declaration; other translation units retain existing prototype. objdiff 100.0%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x6fc base 0x6fc insns 447/447; diffs 0: []

Record-layer evidence: the target only prepares r3-r7 for CDBConvDirStrToCDBDate, and CDBConv.c only consumes the five directory strings. The header currently advertises two unused trailing arguments. CDB_DATABASE_IMPLEMENTATION scopes the accurate five-argument declaration to this unit; no other source or output changes. The key storage starts at instance+8 because CDBRecordKey has 8-byte alignment; a typed prefix view replaces byte-offset casts.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
CDBDatabaseSearchMinuteLayer / minute-1: Ghidra two-location directory batching with typed integer array and separate dictionary result. objdiff 99.82758%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3a0 base 0x3a0 insns 232/232; diffs 7: [154, 156, 159, 161, 180, 183, 186]

CDBDatabaseSearchMinuteLayer / minute-2: Branch-local forward iterator and current pointer declarations. objdiff 100.0%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3a0 base 0x3a0 insns 232/232; diffs 0: []

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
CDBDatabaseSearchHourLayer / hour-1: Ghidra hour search with branch-local forward iterator. objdiff 100.0%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x38c base 0x38c insns 227/227; diffs 0: []

CDBDatabaseSearchDayLayer / day-1: Ghidra day filter and traversal using earlier branch-local iterator fix. COMPILE FAILED.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
CDBDatabaseSearchDayLayer / day-2: Scoped date-boundary signatures now match actual used arguments, Ghidra day traversal. objdiff 98.63095%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3f0 base 0x3f0 insns 252/252; diffs 63: [12, 13, 15, 19, 34, 39, 41, 47, 48, 52, 56, 61, 75, 79, 81, 85, 89, 95, 96, 100]

CDBDatabaseSearchDayLayer / day-3: Date predicates follow target compare operand order. objdiff 98.86905%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3f0 base 0x3f0 insns 252/252; diffs 55: [12, 13, 15, 19, 34, 39, 41, 47, 48, 52, 56, 61, 75, 79, 81, 85, 89, 95, 96, 100]

CDBDatabaseSearchDayLayer / day-4: Outer typed iterator locals precede directory state. objdiff 99.80159%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3f0 base 0x3f0 insns 252/252; diffs 9: [150, 152, 155, 157, 163, 170, 188, 191, 194]

CDBDatabaseSearchDayLayer / day-5: Forward and reverse loop counters are distinct outer locals. objdiff 99.60317%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3f0 base 0x3f0 insns 252/252; diffs 18: [150, 152, 155, 157, 163, 170, 188, 191, 194, 199, 201, 204, 206, 212, 219, 237, 240, 241]

CDBDatabaseSearchDayLayer / day-6: Outer reverse locals plus branch-local forward iterator pair. objdiff 99.60317%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3f0 base 0x3f0 insns 252/252; diffs 18: [150, 152, 155, 157, 163, 170, 188, 191, 194, 199, 201, 204, 206, 212, 219, 237, 240, 241]

CDBDatabaseSearchDayLayer / day-7: Iterator index declared before the pointer in each scope. objdiff 100.0%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3f0 base 0x3f0 insns 252/252; diffs 0: []

Day-layer signature proof: CDBConv.c's DayBegin/DayEnd ignore the final three declared parameters; MonthBegin/MonthEnd ignore four, and YearBegin/YearEnd ignore five. Target calls pass only the calendar components used. The accurate declarations use the existing CDB_DATABASE_IMPLEMENTATION guard to leave every other translation unit unchanged. Day comparisons now use the target's operand order. All remaining day differences were resolved by iterator declaration scope and order.

CDBDatabaseSearchMonthLayer / month-1: Ghidra month traversal with corrected signatures and iterator order. objdiff 100.0%; POOL IDENTICAL up to 7 (mine=7 base=7); insns 240/240; positional diffs 0.

NWC24CheckUserId / usercheck-1: Ghidra area checks and CRC loop in existing file style. objdiff 95.50848%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 59/59; positional diffs 13.

_MountPrfFile / nand-1: Existing C fallback checked against Ghidra using native retry helpers. objdiff 97.511734%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 424/426; positional diffs 386.

WDiFindVendorSpecificIE / vendor-1: Ghidra traversal using WD vendor element fields and cached mode. objdiff 96.53846%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 35.

NWC24Check / manage-1: Original-object Ghidra flow with News Channel prior C and current SDK type names. objdiff 100.0%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 119/119; positional diffs 0.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
NWC24CheckUserId / usercheck-2: CRC iterator declared before area fields in lifetime order. objdiff 100.0%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 59/59; positional diffs 0.

CDBDatabaseSearchMonthLayer / month-live: Fresh worktree object confirms isolated exact candidate. objdiff 100.0%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x3c0 base 0x3c0 insns 240/240; diffs 0: []

CDBDatabaseSearchYearLayer / year-1: Ghidra root search with date boundary helpers and typed iterator scopes. objdiff 100.0%; POOL IDENTICAL up to 7 (mine=7 base=7); insns 222/222; positional diffs 0.

CDBFSIsCDBFileOnSD / fsutils-1: Ghidra hexadecimal digit pairs agree with existing C fallback. objdiff 98.85827%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 127/127; positional diffs 20.

CDBFSIsCDBFileOnSD / fsutils-2: Declare hexadecimal loop counters before character pointer. objdiff 98.74016%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 127/127; positional diffs 22.

WDiFindVendorSpecificIE / vendor-2: Typed output locals and signed two-byte IE header increment. objdiff 98.53846%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 14.

WDiFindVendorSpecificIE / vendor-3: Length local precedes found state; compound offset increment. COMPILE FAILED.

CDBFSIsCDBFileOnSD / fsutils-3: Explicit pair validation avoids inner-loop induction temporary. objdiff 97.20473%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 125/127; positional diffs 104.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
WDiFindVendorSpecificIE / vendor-4: C89 declaration order for length and signed compound offset. objdiff 99.84615%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 1.

CDBDatabaseSearchYearLayer / year-live: Fresh object verifies exact root traversal. objdiff 100.0%; POOL IDENTICAL up to 7 (mine=7 base=7); src 0x378 base 0x378 insns 222/222; diffs 0: []

CDBFSIsCDBFileOnSD / fsutils-4: Static inline character validation helper around ctype conversion. objdiff 93.97638%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 132/127; positional diffs 112.

CDBFSIsCDBFileOnSD / fsutils-5: Direct filename indexing removes cached element pointer. objdiff 97.125984%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 128/127; positional diffs 117.

CDBFSIsCDBFileOnSD / fsutils-6: Function-scope pointer and loop counters, assignment after length check. objdiff 98.85827%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 127/127; positional diffs 20.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
NWC24Check / manage-live: Prior C adapted to local SDK declarations, isolated exact candidate verified in worktree. objdiff 100.0%; POOL IDENTICAL up to 0 (mine=0 base=0); src 0x1dc base 0x1dc insns 119/119; diffs 0: []

WDiFindVendorSpecificIE / vendor-5: Unsigned IE length gives target addition operand order. objdiff 99.84615%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 1.

WDiFindVendorSpecificIE / vendor-6: Offset-first source sum leaves loaded length first in target instruction. objdiff 99.84615%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 1.

WDiFindVendorSpecificIE / vendor-7: Inline helper for the information-element offset step. objdiff 99.84615%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 1.

NWC24Check prior source: https://raw.githubusercontent.com/hotlandsoftware/wii-news-channel/main/src/revolution/NWC24/NWC24Manage.c . The original-object Ghidra control flow agrees with that C implementation. SDK names adapted locally; exact 119/119 instructions.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Manage] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Manage] objdiff: code 3784/3784 data 336/336 functions 21/21 fuzzy 100.0000 linked code 3784
[libs/RevoEX/src/nwc24/NWC24Manage] instruction-exact functions: 21/21
[libs/RevoEX/src/nwc24/NWC24Manage]   section .bss size 32 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage]   section .data size 272 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage]   section .sbss size 24 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage]   section .sdata size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage]   section .text size 3784 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage] baseline: code 3784/3784 data 336 functions 21 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
NWC24CheckUserId / usercheck-live: Verify area and CRC checks in the live object. objdiff 100.0%; POOL IDENTICAL up to 0 (mine=0 base=0); src 0xec base 0xec insns 59/59; diffs 0: []

_MountPrfFile / nand-2: Remove dead initial values and separate read result from open result. objdiff 97.511734%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 424/426; positional diffs 386.

CDBFSIsCDBFileOnSD / fsutils-7: Inline helper owns prefix walker and nested hexadecimal loops. objdiff 95.03937%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 132/127; positional diffs 87.

getUnScrambleId / unscramble-1: Ghidra permutation reconstructed as 53-bit rotate, byte permutation, inverse nibble substitution. objdiff 50.298138%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 162/161; positional diffs 157.

getUnScrambleId / unscramble-2: 64-bit byte helper values preserve masks across inline boundaries. objdiff 49.826088%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 164/161; positional diffs 160.

getUnScrambleId / unscramble-3: Mask the rotated 53-bit result after the left shift. objdiff 40.51553%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 165/161; positional diffs 161.

_MountPrfFile / nand-3: Natural null test and grouped big-endian header words. objdiff 100.0%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 426/426; positional diffs 0.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24UserId] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24UserId] objdiff: code 1032/1032 data 16/16 functions 3/3 fuzzy 100.0000 linked code 1032
[libs/RevoEX/src/nwc24/NWC24UserId] instruction-exact functions: 3/3
[libs/RevoEX/src/nwc24/NWC24UserId]   section .rodata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24UserId]   section .text size 1032 match 100.0
[libs/RevoEX/src/nwc24/NWC24UserId] baseline: code 1032/1032 data 16 functions 3 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
_MountPrfFile / nand-live: Verify native C mount with grouped header decoding. objdiff 100.0%; POOL IDENTICAL up to 0 (mine=0 base=0); src 0x6a8 base 0x6a8 insns 426/426; diffs 0: []

WDiFindVendorSpecificIE / vendor-8: Simplify source-search result to output local declaration order only. objdiff 99.84615%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 1.

getUnScrambleId / unscramble-4: Byte replacement helper mutates a typed 64-bit value in place. objdiff 39.62733%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 169/161; positional diffs 159.

WDiFindVendorSpecificIE / vendor-min-0: Single null-check operand reversal: element-success. objdiff 99.84615%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 1.

WDiFindVendorSpecificIE / vendor-min-1: Single null-check operand reversal: length-success. objdiff 99.84615%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 1.

WDiFindVendorSpecificIE / vendor-min-2: Single null-check operand reversal: element-failure. objdiff 99.84615%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 1.

CDBFSIsCDBFileOnSD / fsutils-8: Integer loop counters for the four pairs and extension. objdiff 97.28346%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 125/127; positional diffs 116.

WDiFindVendorSpecificIE / vendor-9: Signed SDK width for offset without reordered null tests. objdiff 100.0%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 65/65; positional diffs 0.

CDBFSIsCDBFileOnSD / fsutils-type-signed: Counter types s8 i, j;. objdiff 98.85827%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 127/127; positional diffs 20.

CDBFSIsCDBFileOnSD / fsutils-type-unsigned: Counter types u8 i, j;. objdiff 98.85827%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 127/127; positional diffs 20.

CDBFSIsCDBFileOnSD / fsutils-type-mixed: Counter types char i; int j;. objdiff 98.85827%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 127/127; positional diffs 20.

CDBFSIsCDBFileOnSD / fsutils-type-long: Counter types char i; s32 j;. objdiff 98.85827%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 127/127; positional diffs 20.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/vf/develop/nand_drv] pool: IDENTICAL
[libs/RevoEX/src/vf/develop/nand_drv] objdiff: code 12144/12144 data 464/464 functions 33/33 fuzzy 100.0000 linked code 12144
[libs/RevoEX/src/vf/develop/nand_drv] instruction-exact functions: 33/33
[libs/RevoEX/src/vf/develop/nand_drv]   section .bss size 424 match 100.0
[libs/RevoEX/src/vf/develop/nand_drv]   section .rodata size 32 match 100.0
[libs/RevoEX/src/vf/develop/nand_drv]   section .sbss size 8 match 100.0
[libs/RevoEX/src/vf/develop/nand_drv]   section .text size 12144 match 100.0
[libs/RevoEX/src/vf/develop/nand_drv] baseline: code 12144/12144 data 464 functions 33 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
getUnScrambleId / unscramble-5: Unsigned byte positions and explicit ten-bit wraparound mask. objdiff 50.701862%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 161/161; positional diffs 155.

WDiFindVendorSpecificIE / vendor-live: Minimal C body uses s32 offset, existing neighboring functions unchanged. objdiff 100.0%; POOL IDENTICAL up to 0 (mine=0 base=0); src 0x104 base 0x104 insns 65/65; diffs 0: []

CDBFSIsCDBFileOnSD / fsutils-9: One-field cursor struct changes pointer temporary ownership. objdiff 99.09449%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 127/127; positional diffs 17.

CDBFSIsCDBFileOnSD / fsutils-10: Inline helper separates filename format validation from bounded length check. objdiff 98.74016%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 127/127; positional diffs 22.

CDBFSIsCDBFileOnSD / fsutils-11: Advance parameter as the prefix walker and preserve the filename for extension checks. objdiff 95.15748%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 129/127; positional diffs 122.

Wireless source search: stock srcsearch.py initially selected an earlier call site. A worktree-local copy anchors its function matcher to a definition; shared tools were not changed. Seed 25 found 100% after 11 trials. Removing unnecessary reordered null tests retained 100% when offset is s32. The SDK defines s32 as signed long, distinct from int for MWCC's expression lowering. Only the owned WDiFindVendorSpecificIE body and its now-unused asm helper declarations are changed.

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/wd/WDScan] pool: IDENTICAL
[libs/RevoEX/src/wd/WDScan] objdiff: code 2180/2180 data 16/16 functions 5/5 fuzzy 100.0000 linked code 2180
[libs/RevoEX/src/wd/WDScan] instruction-exact functions: 5/5
[libs/RevoEX/src/wd/WDScan]   section .sdata size 8 match 100.0
[libs/RevoEX/src/wd/WDScan]   section .sdata2 size 8 match 100.0
[libs/RevoEX/src/wd/WDScan]   section .text size 2180 match 100.0
[libs/RevoEX/src/wd/WDScan] baseline: code 2180/2180 data 16 functions 5 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
getUnScrambleId / unscramble-6: Repeated trial 5; the intended edit did not run because git diff --check caught an EOF blank line. Superseded by trial 6b. objdiff 50.701862%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 161/161; positional diffs 155.

getUnScrambleId / unscramble-6b: Corrected trial: SDK u32 byte access helpers with explicit byte-width mask. objdiff 48.714287%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 161/161; positional diffs 155.
getUnScrambleId / unscramble-7b: Keep the target out-of-line boundary while factoring the byte permutation. objdiff 50.701862%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 161/161; positional diffs 155.

getUnScrambleId / unscramble-8: Direct byte expressions through macros instead of inline argument temporaries. objdiff 41.142857%; POOL IDENTICAL up to 0 (mine=0 base=0); insns 161/161; positional diffs 157.


## Retained assembly and remaining work

CDBFSIsCDBFileOnSD remains the original exact asm. The best readable C trial, fsutils-9, has 127/127 instructions and 99.09449% objdiff, with 17 differences in registers r3/r4/r5 around ctype map access and the prefix walker. Tried nested and explicit paired loops, counters with char/s8/u8/int/s32 types, function and block scopes, typed helpers, direct indexing, a one-field cursor, and advancing the input parameter. A 120-second source search tried 217 variants from fsutils-1 without improvement. No C trial was retained. Best source and detailed diff: build/da2/fsutils-9/.

getUnScrambleId remains the original exact asm. The best C trial, unscramble-5, reaches 161/161 instructions but only 50.701862% objdiff and 155 positional differences, including instruction scheduling through byte permutation and register allocation. Tried u8/u32/u64 byte helpers, return-value and pointer setters, explicit rotation masks, a separate permutation helper, and direct macro expressions. A 180-second source search tried 292 variants with no improvement. Trial 7 inlined away the function; trial 7b restored its original call boundary with NO_INLINE and remained non-exact. No experimental helper, macro, attribute or C body was retained. Best source and detailed diff: build/da2/unscramble-5/. Neither remaining function is claimed to require assembly.

Both retained functions have more than three distinct compiled source attempts. No untried assignment remains. The two helper-signature header changes are scoped to CDB_DATABASE_IMPLEMENTATION; all other units keep their existing declarations.

## Converted functions and commits

143785b0 decomp(cdb): convert search callback to c
ea8cd532 decomp(cdb): convert record search layer to c
e5989e5e decomp(cdb): convert minute search layer to c
4a653bb3 decomp(cdb): convert hour search layer to c
952dd221 decomp(cdb): convert day search layer to c
b72b9d27 decomp(cdb): convert month search layer to c
88082111 decomp(cdb): convert year search layer to c
0743c6da decomp(nwc24): convert library check to c
a1d0e162 decomp(nwc24): convert user id validation to c
19410104 decomp(vf): convert nand prf mount to c
d612eee9 decomp(wd): convert vendor element search to c

## Baseline and final comparison

Unit | Exact functions | Matched code | Matched data | Asm bodies before -> after
--- | --- | --- | --- | ---
libs/RevoEX/src/cdb/CDBDatabase | 33 -> 33 | 12152 -> 12152 | 312 -> 312 | 7 -> 0
libs/RevoEX/src/cdb/CDBFileSystemUtils | 11 -> 11 | 2480 -> 2480 | 8 -> 8 | 1 -> 1
libs/RevoEX/src/nwc24/NWC24Manage | 21 -> 21 | 3784 -> 3784 | 336 -> 336 | 1 -> 0
libs/RevoEX/src/nwc24/NWC24UserId | 3 -> 3 | 1032 -> 1032 | 16 -> 16 | 2 -> 1
libs/RevoEX/src/vf/develop/nand_drv | 33 -> 33 | 12144 -> 12144 | 464 -> 464 | 1 -> 0
libs/RevoEX/src/wd/WDScan | 5 -> 5 | 2180 -> 2180 | 16 -> 16 | 1 -> 0

Final full gate: clean 4.3U rebuild of all six units passed. The fresh report, object diffs, and DOL agree. Eleven assigned asm bodies are now exact C; the other two remain original asm with the failed C trials recorded above.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/cdb/CDBDatabase] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBDatabase] objdiff: code 12152/12152 data 312/312 functions 33/33 fuzzy 100.0000 linked code 12152
[libs/RevoEX/src/cdb/CDBDatabase] instruction-exact functions: 33/33
[libs/RevoEX/src/cdb/CDBDatabase]   section .data size 312 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase]   section .text size 12152 match 100.0
[libs/RevoEX/src/cdb/CDBDatabase] baseline: code 12152/12152 data 312 functions 33 fuzzy 100.0000
[libs/RevoEX/src/cdb/CDBFileSystemUtils] pool: IDENTICAL
[libs/RevoEX/src/cdb/CDBFileSystemUtils] objdiff: code 2480/2480 data 8/8 functions 11/11 fuzzy 100.0000 linked code 2480
[libs/RevoEX/src/cdb/CDBFileSystemUtils] instruction-exact functions: 11/11
[libs/RevoEX/src/cdb/CDBFileSystemUtils]   section .sdata size 8 match 100.0
[libs/RevoEX/src/cdb/CDBFileSystemUtils]   section .text size 2480 match 100.0
[libs/RevoEX/src/cdb/CDBFileSystemUtils] baseline: code 2480/2480 data 8 functions 11 fuzzy 100.0000
[libs/RevoEX/src/nwc24/NWC24Manage] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Manage] objdiff: code 3784/3784 data 336/336 functions 21/21 fuzzy 100.0000 linked code 3784
[libs/RevoEX/src/nwc24/NWC24Manage] instruction-exact functions: 21/21
[libs/RevoEX/src/nwc24/NWC24Manage]   section .bss size 32 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage]   section .data size 272 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage]   section .sbss size 24 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage]   section .sdata size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage]   section .text size 3784 match 100.0
[libs/RevoEX/src/nwc24/NWC24Manage] baseline: code 3784/3784 data 336 functions 21 fuzzy 100.0000
[libs/RevoEX/src/nwc24/NWC24UserId] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24UserId] objdiff: code 1032/1032 data 16/16 functions 3/3 fuzzy 100.0000 linked code 1032
[libs/RevoEX/src/nwc24/NWC24UserId] instruction-exact functions: 3/3
[libs/RevoEX/src/nwc24/NWC24UserId]   section .rodata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24UserId]   section .text size 1032 match 100.0
[libs/RevoEX/src/nwc24/NWC24UserId] baseline: code 1032/1032 data 16 functions 3 fuzzy 100.0000
[libs/RevoEX/src/vf/develop/nand_drv] pool: IDENTICAL
[libs/RevoEX/src/vf/develop/nand_drv] objdiff: code 12144/12144 data 464/464 functions 33/33 fuzzy 100.0000 linked code 12144
[libs/RevoEX/src/vf/develop/nand_drv] instruction-exact functions: 33/33
[libs/RevoEX/src/vf/develop/nand_drv]   section .bss size 424 match 100.0
[libs/RevoEX/src/vf/develop/nand_drv]   section .rodata size 32 match 100.0
[libs/RevoEX/src/vf/develop/nand_drv]   section .sbss size 8 match 100.0
[libs/RevoEX/src/vf/develop/nand_drv]   section .text size 12144 match 100.0
[libs/RevoEX/src/vf/develop/nand_drv] baseline: code 12144/12144 data 464 functions 33 fuzzy 100.0000
[libs/RevoEX/src/wd/WDScan] pool: IDENTICAL
[libs/RevoEX/src/wd/WDScan] objdiff: code 2180/2180 data 16/16 functions 5/5 fuzzy 100.0000 linked code 2180
[libs/RevoEX/src/wd/WDScan] instruction-exact functions: 5/5
[libs/RevoEX/src/wd/WDScan]   section .sdata size 8 match 100.0
[libs/RevoEX/src/wd/WDScan]   section .sdata2 size 8 match 100.0
[libs/RevoEX/src/wd/WDScan]   section .text size 2180 match 100.0
[libs/RevoEX/src/wd/WDScan] baseline: code 2180/2180 data 16 functions 5 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## Fresh function verification

```text
libs/RevoEX/src/cdb/CDBDatabase: POOL IDENTICAL up to 7 (mine=7 base=7)
CDBDatabaseSearchCallCallback: objdiff 100.0%; src 0xf4 base 0xf4 insns 61/61; diffs 0: []
CDBDatabaseSearchRecordLayer: objdiff 100.0%; src 0x6fc base 0x6fc insns 447/447; diffs 0: []
CDBDatabaseSearchMinuteLayer: objdiff 100.0%; src 0x3a0 base 0x3a0 insns 232/232; diffs 0: []
CDBDatabaseSearchHourLayer: objdiff 100.0%; src 0x38c base 0x38c insns 227/227; diffs 0: []
CDBDatabaseSearchDayLayer: objdiff 100.0%; src 0x3f0 base 0x3f0 insns 252/252; diffs 0: []
CDBDatabaseSearchMonthLayer: objdiff 100.0%; src 0x3c0 base 0x3c0 insns 240/240; diffs 0: []
CDBDatabaseSearchYearLayer: objdiff 100.0%; src 0x378 base 0x378 insns 222/222; diffs 0: []

libs/RevoEX/src/cdb/CDBFileSystemUtils: POOL IDENTICAL up to 0 (mine=0 base=0)
CDBFSIsCDBFileOnSD: objdiff 100.0%; src 0x1fc base 0x1fc insns 127/127; diffs 0: []

libs/RevoEX/src/nwc24/NWC24Manage: POOL IDENTICAL up to 0 (mine=0 base=0)
NWC24Check: objdiff 100.0%; src 0x1dc base 0x1dc insns 119/119; diffs 0: []

libs/RevoEX/src/nwc24/NWC24UserId: POOL IDENTICAL up to 0 (mine=0 base=0)
NWC24CheckUserId: objdiff 100.0%; src 0xec base 0xec insns 59/59; diffs 0: []
getUnScrambleId: objdiff 100.0%; src 0x284 base 0x284 insns 161/161; diffs 0: []

libs/RevoEX/src/vf/develop/nand_drv: POOL IDENTICAL up to 0 (mine=0 base=0)
_MountPrfFile: objdiff 100.0%; src 0x6a8 base 0x6a8 insns 426/426; diffs 0: []

libs/RevoEX/src/wd/WDScan: POOL IDENTICAL up to 0 (mine=0 base=0)
WDiFindVendorSpecificIE: objdiff 100.0%; src 0x104 base 0x104 insns 65/65; diffs 0: []

Owned totals: {"matched_functions": 106, "total_functions": 106, "matched_code": 33772, "total_code": 33772, "matched_data": 1152, "total_data": 1152}
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d
GATE PASS: final clean six-unit gate, pools, exact-name objdiff, ctxdiff, fully linked code/data, and DOL hash.
```

`ninja -C . progress build/43U/report.json build/43U/ok` also passed after the clean gate. Each unit retains 100% matched and linked code/data, totaling 106 exact functions, 33772 code bytes and 1152 data bytes. The only remaining assigned asm bodies are CDBFSIsCDBFileOnSD and getUnScrambleId. No rejected source-search change was retained.
