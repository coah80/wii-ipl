# fz8 attempts
Baseline a4c84cbf537becd2cf9931d2406601a18312d0c5
All owned data already exact; no symbol changes required.
libs/RevoEX/src/net/hmac POOL IDENTICAL up to 3 (mine=3 base=3)
libs/RevoEX/src/so/SOInformation POOL IDENTICAL up to 0 (mine=0 base=0)
libs/NW4R/src/ut/ut_ArchiveFontBase POOL IDENTICAL up to 0 (mine=0 base=0)
src/scene/setting/iplRakuRakuThread POOL IDENTICAL up to 1 (mine=1 base=1)

## NETHMACInit / NETHMACGetDigest
Diagnosis: same 0x60 Init frame; GetDigest target 105 instructions vs 102. Target makes a second context pointer at pad initialization, proving an inline helper boundary. Both loops otherwise have the same unroll and branch structure.
Attempt 1: shared BeginDigest inline helper owns its key buffer and context pointer. GetDigest reaches diffs 0, Init falls from 78 diffs to 2 literal offsets.
Attempt 2: inline WarnInterface parameter emits function-name literal first, fixes pool; leaves two swapped argument setup instructions.
Attempt 3: warning format temporary gives no scheduling change.
Attempt 4: scoped function-name temporary gives no scheduling change.
Attempt 5: use MWCC __FUNCTION__ for diagnostic name. Pool identical, Init 143/143 diffs 0; GetDigest 105/105 diffs 0.

## SOGetHostByName
Diagnosis: frames 0x30 and 80/80 instructions match; remaining initial 17 diffs are registers only. Length and result share a register in target.
Attempt 1: leading declaration search, 70 builds, reduces 17 diffs to 11.
Attempt 2: coalesce length and result source variable, remains 11 diffs.
Attempt 3: scoped request/reply declarations, 28 diffs; restored.
Attempt 4: inline GetHostReply helper isolates request bookkeeping. Passing rm by value adds an early load and saved register, 81/80; pointer parameter restores 80/80.
Attempt 5: declaration search over helper locals, 16 builds, reaches 80/80 diffs 0.

## SOGetAddrInfo
Diagnosis: frame 0x40 matches, 183/185 instructions. Null branches go the opposite direction, name length helpers and evaluation order differ; request/reply registers also swapped.
Attempt 1: null-aware NameSize, NameLength, ServiceSize helpers, 185/185 with 62 diffs.
Attempt 2: explicit null-first if/else and service evaluation first, 185/185 with 28 diffs.
Attempt 3: separate serviceLength/nodeLength before alignment expression, 185/185 with 24 register-only diffs.
Attempt 4: leading declaration search, 118 builds, no improvement at 24 diffs.
Attempt 5: inline GetAddressReply helper isolates allocation bookkeeping; 185/185 with 31 register-only diffs. Helper-local declaration search follows.

Attempt 6, SOGetAddrInfo: helper declaration search, 39 builds, reaches 185/185 diffs 0. Preserves retail service-size behavior using node strlen under service null check.

## RakuRakuThread::start / finish
Diagnosis: start 97/96, finish 135/133 with 0x20/0x30 frames. Target uses one BSS base for allocator, status, queue; ours loads separate addresses. Shared globals have correct names, offsets, extents and 456/456 exact data; no rename justified.
Attempt 1, both functions: define C-linkage objects directly instead of prior extern declarations. No instruction change; restored.
Attempt 2, both functions: explicit zero initialization on those objects. No instruction change; restored.
Attempt 3, both functions: file-local C-linkage objects. No instruction change; restored.
Attempt 4, finish: positive state-range if/else instead of early return. Correct branch direction, but 136/133 and BSS-base/frame differences remain; restored.
Additional start attempt: cache allocator pointer before state check; 98/96 instructions, structural/exact (8, 65); restored.
Additional start attempt: separate created heap local from member assignment; 97/96 instructions, structural/exact (13, 88); restored.
Additional start attempt: declare socket configuration before interrupt and time locals; 97/96 instructions, structural/exact (13, 88); restored.
Additional finish attempt: cache status pointer before state check; 132/133 instructions, structural/exact (19, 75); restored.
Additional finish attempt: explicit two-state comparison rather than range subtraction; 138/133 instructions, structural/exact (38, 133); restored.
Additional finish attempt: equality-bound key loops instead of less-than loops; 135/133 instructions, structural/exact (34, 127); restored.

## Owned data audit
libs/RevoEX/src/net/hmac: baseline matched_data 104 / 104; sections .data 100.0, .sdata 100.0. No unpaired owned data symbol; no rename or extent edit.
libs/RevoEX/src/so/SOInformation: baseline matched_data 0 / 0; sections . No unpaired owned data symbol; no rename or extent edit.
libs/NW4R/src/ut/ut_ArchiveFontBase: baseline matched_data 96 / 96; sections .data 100.0, .sbss2 100.0. No unpaired owned data symbol; no rename or extent edit.
src/scene/setting/iplRakuRakuThread: baseline matched_data 456 / 456; sections .bss 100.0, .data 100.0, .sbss 100.0, .sdata 100.0. No unpaired owned data symbol; no rename or extent edit.

Latest fetched origin/main b84b3c0d579c520be71051ce33d22965cab6965d.
libs/RevoEX/src/net/hmac.c: origin/main source unchanged from initial baseline = True.
libs/RevoEX/src/so/SOInformation.c: origin/main source unchanged from initial baseline = True.
libs/NW4R/src/ut/ut_ArchiveFontBase.cpp: origin/main source unchanged from initial baseline = True.
src/scene/setting/iplRakuRakuThread.cpp: origin/main source unchanged from initial baseline = True.

## ConstructOpAnalyzeGLGR
Diagnosis: 239/239 instructions, same frame and loop/branch forms. Offset calculation scheduling differs at instructions 109-147; later register and pointer-add operand order differences. All 96 data bytes already exact.
Attempt 1: inline analyzeGroups helper around second phase; 238/239 until local pGlgr recomputation restored 239/239, structural 22 / exact 120, rejected.
Attempt 2: inline getOffsetSize scratch allocator; 239/239 structural 22 / exact 104, rejected.
Attempt 3: leading local declaration search; first 13 builds unchanged, then moved metadata locals to top and searched. No structural improvement.
Attempt 4: permute independent metadata, scratch and flags calculation statement blocks to diagnose scheduling.
Calculation order ('blocks', 'glyphs', 'scratch', 'step', 'flags'): 239/239, structural/exact (22, 99).
Calculation order ('blocks', 'glyphs', 'step', 'scratch', 'flags'): 239/239, structural/exact (19, 99).
Attempt 3 completed 577 declaration builds; best structural/exact 22/73, restored. Attempt 4 completed 120 statement orders; best 19/99, not exact.
Attempt 5 variant cache workspace before metadata: 239/239, structural/exact (25, 99).
Attempt 5 variant cache workspace after count: 239/239, structural/exact (25, 99).
Attempt 5 variant cache workspace before scratch: 239/239, structural/exact (19, 99).
Attempt 5 variant reverse commutative pointer operands: 239/239, structural/exact (19, 99).
Attempt 5 variant size flags before scratch declaration set 0: 239/239, structural/exact (19, 99).
Attempt 5 variant offset flags before scratch declaration set 0: 239/239, structural/exact (19, 99).
Attempt 5 variant size flags before scratch declaration set 1: 239/239, structural/exact (19, 72).
All ArchiveFontBase experiments restored. No additional instruction-exact function; remaining scheduling differences are structural, not solely register names.

## Completion audit before final gate
NETHMACInit and NETHMACGetDigest exact, 143/143 and 105/105 with diffs 0.
SOGetHostByName and SOGetAddrInfo exact, 80/80 and 185/185 with diffs 0.
Remaining ConstructOpAnalyzeGLGR has five logged experiment groups, including inline boundaries, scratch allocation, 577 declaration builds, 120 statement orders, workspace caches and operand reversals.
Remaining RakuRakuThread::start has six distinct logged source attempts. Remaining finish has seven. No function remains untried.
Only hmac.c, SOInformation.c and this attempts log retained changes. No configure.py, shared header or symbol changes.

## Final full gate
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/net/hmac] pool: IDENTICAL
[libs/RevoEX/src/net/hmac] objdiff: code 1008/1008 data 104/104 functions 3/3 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/net/hmac] instruction-exact functions: 3/3
[libs/RevoEX/src/net/hmac]   section .data size 88 match 100.0
[libs/RevoEX/src/net/hmac]   section .sdata size 16 match 100.0
[libs/RevoEX/src/net/hmac]   section .text size 1008 match 100.0
[libs/RevoEX/src/net/hmac] baseline: code 16/1008 data 104 functions 1 fuzzy 91.6984
[libs/RevoEX/src/so/SOInformation] pool: IDENTICAL
[libs/RevoEX/src/so/SOInformation] objdiff: code 1280/1280 data None/None functions 4/4 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/so/SOInformation] instruction-exact functions: 4/4
[libs/RevoEX/src/so/SOInformation]   section .text size 1280 match 100.0
[libs/RevoEX/src/so/SOInformation] baseline: code 220/1280 data None functions 2 fuzzy 92.9969
[libs/NW4R/src/ut/ut_ArchiveFontBase] pool: IDENTICAL
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 98.1398 linked code 0
[libs/NW4R/src/ut/ut_ArchiveFontBase] instruction-exact functions: 22/23
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .data size 88 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .sbss2 size 8 match 100.0
[libs/NW4R/src/ut/ut_ArchiveFontBase]   section .text size 5120 match 98.13985
[libs/NW4R/src/ut/ut_ArchiveFontBase]   below 100: ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader 90.03766
[libs/NW4R/src/ut/ut_ArchiveFontBase] baseline: code 4164/5120 data 96 functions 22 fuzzy 98.1398
[src/scene/setting/iplRakuRakuThread] pool: IDENTICAL
[src/scene/setting/iplRakuRakuThread] objdiff: code 1252/2168 data 456/456 functions 12/14 fuzzy 94.6900 linked code 0
[src/scene/setting/iplRakuRakuThread] instruction-exact functions: 12/14
[src/scene/setting/iplRakuRakuThread]   section .bss size 296 match 100.0
[src/scene/setting/iplRakuRakuThread]   section .data size 136 match 100.0
[src/scene/setting/iplRakuRakuThread]   section .sbss size 16 match 100.0
[src/scene/setting/iplRakuRakuThread]   section .sdata size 8 match 100.0
[src/scene/setting/iplRakuRakuThread]   section .text size 2168 match 94.69004
[src/scene/setting/iplRakuRakuThread]   below 100: start__Q33ipl5scene14RakuRakuThreadFv 88.635414
[src/scene/setting/iplRakuRakuThread]   below 100: finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi 86.56391
[src/scene/setting/iplRakuRakuThread] baseline: code 1252/2168 data 456 functions 12 fuzzy 94.6900
regressions vs baseline: 0
global matched_code_percent: 88.70241 -> 88.77092
global fuzzy_match_percent: 99.47499 -> 99.48078
global complete_code_percent: 63.54459 -> 63.54459
global matched_data_percent: 98.77142 -> 98.77142
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
libs/RevoEX/src/net/hmac: matched_functions 1 -> 3, matched_code 16 -> 1008, matched_data 104 -> 104
libs/RevoEX/src/so/SOInformation: matched_functions 2 -> 4, matched_code 220 -> 1280, matched_data 0 -> 0
libs/NW4R/src/ut/ut_ArchiveFontBase: matched_functions 22 -> 22, matched_code 4164 -> 4164, matched_data 96 -> 96
src/scene/setting/iplRakuRakuThread: matched_functions 12 -> 12, matched_code 1252 -> 1252, matched_data 456 -> 456
NETHMACInit src 0x23c base 0x23c insns 143/143; diffs 0: [];
NETHMACGetDigest src 0x1a4 base 0x1a4 insns 105/105; diffs 0: [];
SOGetHostByName src 0x140 base 0x140 insns 80/80; diffs 0: [];
SOGetAddrInfo src 0x2e4 base 0x2e4 insns 185/185; diffs 0: [];
Final gate PASS; zero regressions, zero net forbidden patterns, zero readability warnings. Full DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
