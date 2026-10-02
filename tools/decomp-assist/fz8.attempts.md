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

# fz8 followup round
Baseline 2cc9824045aee4d546a31b5859a7cfe480d8c75e
libs/NW4R/src/ut/ut_ArchiveFontBase POOL IDENTICAL up to 0 (mine=0 base=0)
src/scene/setting/iplRakuRakuThread POOL IDENTICAL up to 1 (mine=1 base=1)
libs/RVL_SDK/src/fa/pf_cluster POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RevoEX/src/nhttp/NHTTP_thread POOL IDENTICAL up to 8 (mine=8 base=8)
libs/MSL/src/MSL_Common/wprintf POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RevoEX/src/cdb/CDBRecord FIRST DIVERGENCE at index 10
    8 mine=0x1b0    base=0x1b0
      M "can't get file size of the record ; the record is closed\n"
      B "can't get file size of the record ; the record is closed\n"
    9 mine=0x1ec    base=0x1ec
      M "can't get data size of the record ; the record is closed\n"
      B "can't get data size of the record ; the record is closed\n"
*  10 mine=0x228    base=0x228
      M "can't remove the record ; the record is opened\n"
      B "can't reduce file size of the record ; the record is closed\n"
*  11 mine=0x258    base=0x268
      M "can't remove the record ; permission denied\n"
      B "can't reduce file size of the record ; the record is opened as READONL"
*  12 mine=0x288    base=0x2b8
      M "can't get CDBId of the record ; the record is closed\n"
      B "can't reduce file size of the record ; file size must be over %d bytes"
*  13 mine=0x2c0    base=0x300
      M "can't get maker code of the record ; the record is closed\n"
      B "can't reduce data size of the record ; the record is closed\n"
*  14 mine=0x2fc    base=0x340
      M "can't set modified time of the record; the database is opened as READO"
      B "can't reduce data size of the record ; the record is opened as READONL"

mine has 19 strings, base has 47

## Followup PFCLUSTER_DeleteCluster
Pool empty, 108/108 and same frame, normalized structural 0. Remaining 35 differences are register choices. Declaration search 71 builds unchanged.
Attempt 2: real inline deleteCluster helper, permuting helper argument declaration and call order together while preserving public ABI.
Helper argument order ('p_iter', 'p_ent', 'cluster_index', 'num_clusters', 'p_deleted_clusters'): 108/108, structural/exact (11, 53)
src/scene/setting/iplRakuRakuThread start__Q33ipl5scene14RakuRakuThreadFv | socket allocator aggregate initialization | 95/96 instructions, structural/exact (17, 87) | restored
src/scene/setting/iplRakuRakuThread start__Q33ipl5scene14RakuRakuThreadFv | restore interrupts through success branch | 97/96 instructions, structural/exact (18, 90) | restored
src/scene/setting/iplRakuRakuThread start__Q33ipl5scene14RakuRakuThreadFv | time sampled before interrupt local initialized | 97/96 instructions, structural/exact (13, 88) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | separate deleted byte count from cluster-count argument | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | typed iterator and entry aliases | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | local rounded deleted-cluster count before output store | 107/108 instructions, structural/exact (8, 49) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | long conversion-length local rather than int | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | separate narrow string-length local from wide output length | 593/593 instructions, structural/exact (2, 170) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | count-output pointer has independent scope | 593/593 instructions, structural/exact (0, 98) | restored
src/scene/setting/iplRakuRakuThread finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | configuration switch instead of security if ladder | 138/133 instructions, structural/exact (53, 130) | restored
src/scene/setting/iplRakuRakuThread finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | share key-loop index across security branches | 135/133 instructions, structural/exact (34, 127) | restored
src/scene/setting/iplRakuRakuThread finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | inline configuration-copy boundary | 134/133 instructions, structural/exact (41, 98) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | read group metadata through parsed header pointer | 239/239 instructions, structural/exact (32, 98) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | typed end and start pointers for scratch allocation | 239/239 instructions, structural/exact (22, 99) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | sheet-flag helper takes stride before flag pointer | 239/239 instructions, structural/exact (22, 99) | restored

## Followup CDB data and code
First pool divergence at 0x228 is missing ReduceFileSize diagnostics. Target 47 strings vs source 19; existing target .data total 2496 retained. Missing strings come from dead-stripped reduction, setter/getter, duplication and owner functions, not misnamed equivalent objects. No surviving reduction body or backing truncation API located. No rename/extent change justified. CDBCryptBuffer has only three literal offsets different; source experiments below cannot fill the missing earlier pool.
libs/RevoEX/src/cdb/CDBRecord CDBCryptBuffer | for-loop owns chunk offset advancement | 119/119 instructions, structural/exact (3, 3) | restored
libs/RevoEX/src/cdb/CDBRecord CDBCryptBuffer | name the AES operation success result | 119/119 instructions, structural/exact (3, 3) | restored
libs/RevoEX/src/cdb/CDBRecord CDBCryptBuffer | typed chunk pointer shared by input and output copies | 120/119 instructions, structural/exact (10, 76) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | declare data size before file size to match target stack slots | 283/284 instructions, structural/exact (21, 89) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | save tell position only on successful tell result | 283/284 instructions, structural/exact (24, 92) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | cache authenticated byte count before SHA interface call | 284/284 instructions, structural/exact (9, 53) | restored

## Followup NHTTPi_ThreadParseHeaderProc
Pool identical 504/504 data. Same frame and 191/191 initially; the sole structural difference is zero held in a saved register across Keep-Alive comparison. Request/base registers differ too.
Attempt 1: local keepAlive initialized false, conditional assignment and shared store: 189/191, rejected.
Attempt 2: local false only in false branch: identical 191/191, 20 diffs, rejected.
Attempt 3: local boolean through complete length branch: 186/191, comparison lowered to cntlzw, rejected.
Attempt 4: leading locals separated from initialization; declaration search 71 builds, structural/exact 3/20 unchanged.
Attempt 5: real inline connection-header parser: 196/191, additional success-result branches, rejected.

## Followup __wpformatter
Pool identical 836/836 data. Same frame and 593/593, structural 0; 98 register differences, including num_chars, write callback/data, constant bases and count-output pointer.
Attempt 1: independent count destination scope: unchanged 98 diffs.
Attempt 2: split leading locals and declaration search, 71 builds: unchanged 98 diffs.
Attempt 3: conversion length long instead of int: unchanged 98 diffs.
Attempt 4: separate narrow string conversion length: structural/exact 2/170, rejected.
Attempt 5: count destination declared at function entry: unchanged 98 diffs.
Attempt 6: inline count-output store helper: unchanged 98 diffs.
CDBRecordEncrypt combined stack-slot, successful tell assignment and cached authenticated length: 284/284 instructions, structural/exact 0/44. Leading declaration search 71 builds unchanged; remaining differences are registers.
CDBRecordEncrypt genuine encryptRecord inline helper; 1 parameter-order variants; best structural/exact (0, 44); restored combined structural candidate
encryptRecord helper first invocation selected a forward declaration and failed compilation; corrected definition extraction before testing.
CDBRecordEncrypt genuine encryptRecord inline helper; 120 parameter-order variants; best structural/exact (0, 44); restored combined structural candidate
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | inline Keep-Alive token boolean return | 189/191 instructions, structural/exact (16, 72) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | initialize fallback before comparison: BOOL keepAlive = FALSE | 191/191 instructions, structural/exact (3, 20) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | initialize fallback before comparison: BOOL keepAlive | 191/191 instructions, structural/exact (3, 20) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline attribute helpers (0,) | 284/284 instructions, structural/exact (0, 42) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline attribute helpers (1,) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline attribute helpers (2,) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline attribute helpers (0, 1, 2) | 284/284 instructions, structural/exact (0, 42) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | attribute pointer lifetime variant 0 | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | attribute pointer lifetime variant 1 | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | attribute pointer lifetime variant 2 | 284/284 instructions, structural/exact (0, 42) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline file-operation boundaries (0,) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline file-operation boundaries (1,) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline file-operation boundaries (2,) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline file-operation boundaries (3,) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline file-operation boundaries (4,) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | inline file-operation boundaries (0, 1, 2, 3, 4) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | structural named diagnostic pointers (0,) entry | 285/284 instructions, structural/exact (5, 276) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | structural named diagnostic pointers (0,) after_file | compile failed (C89 declaration after statement); restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | structural named diagnostic pointers (1,) entry | 285/284 instructions, structural/exact (5, 276) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | structural named diagnostic pointers (1,) after_file | compile failed (C89 declaration after statement); restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | structural named diagnostic pointers (0, 1) entry | 286/284 instructions, structural/exact (6, 270) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | structural named diagnostic pointers (0, 1) after_file | compile failed (C89 declaration after statement); restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | attrhelper named diagnostic pointers (0,) entry | 285/284 instructions, structural/exact (5, 276) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | attrhelper named diagnostic pointers (0,) after_file | compile failed (C89 declaration after statement); restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | attrhelper named diagnostic pointers (1,) entry | 285/284 instructions, structural/exact (5, 276) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | attrhelper named diagnostic pointers (1,) after_file | compile failed (C89 declaration after statement); restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | attrhelper named diagnostic pointers (0, 1) entry | 286/284 instructions, structural/exact (6, 270) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | attrhelper named diagnostic pointers (0, 1) after_file | compile failed (C89 declaration after statement); restored
Final candidate keeps only three structural corrections in CDBRecordEncrypt (stack slots, tell success lifetime, HMAC input length evaluated before interface getter). Normalized instruction structure now identical, 44 register differences; helper variants were reverted to keep the source diff small. Exact-function count has not increased.
CDB quick gate: PASS; fuzzy code 97.19718% -> 99.19014% for Encrypt; 27/29 instruction-exact unchanged, data 144/2640 unchanged, regressions/forbidden/readability all zero.

## Followup completion audit
All eight open functions have at least three distinct, built source attempts above; no untried function remains.
Archive ConstructOpAnalyzeGLGR: parsed metadata, typed scratch bounds, helper argument boundary; remains structural 22 and total positional 99 differences.
Raku start: allocator aggregate, positive success branch, interrupt/time local ordering; finish: security switch, shared key-loop index, inline configuration boundary. Both retain shared target BSS addressing differences; finish additionally has a frame-size difference.
PFCLUSTER_DeleteCluster: separate deleted-byte count, typed aliases, rounded output local; 108/108, structural 0, register 35 differences.
NHTTP parse: initialized/shared boolean, false-branch local, full branch boolean; additional declaration/helper attempts. 191/191; zero's lifetime across comparison and base/request registers remain.
__wpformatter: count destination scope, declaration splitting/search, long length, independent narrow length, count-store helper; 593/593, structural 0, register 98 differences.
CDBCryptBuffer: for loop, named AES success, typed chunk pointer; 119/119, only three diagnostic literal offsets remain.
CDBRecordEncrypt: data/file local order, successful tell assignment, pre-call authenticated length; combined kept after quick gate. 284/284, structural 0, register 44 differences. Additional 120 helper argument orders and file/attribute helper boundaries did not match.
Owned data: Archive 96/96; Raku 456/456 including correctly named and sized BSS objects; cluster has no data; NHTTP 504/504; wprintf 836/836. CDB 144/2640: missing diagnostic pool from dead-stripped functions, not unpaired equivalent named symbols. No symbol rename or extent change justified; config unchanged.
No exact-function gain in this followup; retained structural CDB improvement remains fuzzy. Definition of done is not achieved.

## Final full gate and open-function re-list
ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader: 90.03766% open; 3 distinct compiled source attempts; src 0x3bc base 0x3bc insns 239/239
start__Q33ipl5scene14RakuRakuThreadFv: 88.635414% open; 3 distinct compiled source attempts; src 0x184 base 0x180 insns 97/96
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi: 86.56391% open; 3 distinct compiled source attempts; src 0x21c base 0x214 insns 135/133
PFCLUSTER_DeleteCluster: 98.19444% open; 3 distinct compiled source attempts; src 0x1b0 base 0x1b0 insns 108/108
NHTTPi_ThreadParseHeaderProc: 98.58639% open; 3 distinct compiled source attempts; src 0x2fc base 0x2fc insns 191/191
__wpformatter: 99.13997% open; 3 distinct compiled source attempts; src 0x944 base 0x944 insns 593/593
CDBCryptBuffer: 99.97479% open; 3 distinct compiled source attempts; src 0x1dc base 0x1dc insns 119/119
CDBRecordEncrypt: 99.19014% open; 22 distinct compiled source attempts; src 0x470 base 0x470 insns 284/284
Final full gate (non --quick), all six units:
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 98.1398 linked code 0
[src/scene/setting/iplRakuRakuThread] objdiff: code 1252/2168 data 456/456 functions 12/14 fuzzy 94.6900 linked code 0
[libs/RVL_SDK/src/fa/pf_cluster] objdiff: code 4120/4552 data None/None functions 7/8 fuzzy 99.8286 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_thread] objdiff: code 10528/11292 data 504/504 functions 25/26 fuzzy 99.9044 linked code 0
[libs/MSL/src/MSL_Common/wprintf] objdiff: code 6264/8636 data 836/836 functions 8/9 fuzzy 99.7638 linked code 0
[libs/RevoEX/src/cdb/CDBRecord] objdiff: code 5464/7076 data 144/2640 functions 27/29 fuzzy 99.8683 linked code 0
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
Before -> after: exact counts and objdiff matched code/data bytes unchanged for every unit; Encrypt fuzzy 97.19718 -> 99.19014. No new exact match; data pool reconstruction remains uncertain without stripped function bodies.

## HIGH round
Same branch; medium structural CDB improvement retained. No new source changes in owned NHTTP unit on fetched origin/main. Pool identical (8 strings), 191/191, frame 0x30; target initializes zero before Keep-Alive comparison and reuses request register, ours initializes zero after. Main difference is boolean-expression/inline boundary before register allocation.
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH ternary bool | 187/191 instructions, structural/exact (19, 75) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH comparison bool | 187/191 instructions, structural/exact (19, 75) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH logical and length first | 190/191 instructions, structural/exact (19, 77) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH logical and compare first | 191/191 instructions, structural/exact (4, 15) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH logical or constant false | 187/191 instructions, structural/exact (19, 75) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH boolean helper argument | 187/191 instructions, structural/exact (19, 75) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH explicit bool cast | 187/191 instructions, structural/exact (19, 75) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH invert comparison branches | 191/191 instructions, structural/exact (5, 20) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH local compare and separate assignment | 191/191 instructions, structural/exact (3, 20) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH unsigned comparison zero | 191/191 instructions, structural/exact (3, 20) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH branch on logical NOT | 191/191 instructions, structural/exact (3, 20) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH nested bool branch | 195/191 instructions, structural/exact (19, 76) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH logical AND true conditional | 191/191 instructions, structural/exact (3, 20) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH logical OR false conditional | 191/191 instructions, structural/exact (3, 20) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH ternary local then branch | 192/191 instructions, structural/exact (19, 74) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH nested ternary store | 187/191 instructions, structural/exact (19, 75) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH bool compare zero reuse | 191/191 instructions, structural/exact (3, 20) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH branch boolean result against true | 193/191 instructions, structural/exact (19, 77) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH signed nonpositive comparison | 197/191 instructions, structural/exact (24, 78) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH token equality inline helper 0 | 195/191 instructions, structural/exact (19, 76) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH token equality inline helper 1 | 195/191 instructions, structural/exact (19, 76) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH token equality inline helper 2 | 195/191 instructions, structural/exact (19, 76) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH token equality inline helper 3 | 195/191 instructions, structural/exact (19, 76) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH token equality inline helper 4 | 192/191 instructions, structural/exact (19, 74) | restored

HIGH PFCLUSTER_DeleteCluster: fetched origin/main; source unchanged upstream. Empty pool, frame 0x40 and 108/108 instructions, normalized structural zero. Target maps delete bytes r24, byte position r25, cluster size r26, iterator r27, entry r28, index r29, output r30, volume r31. Source has all eight lifetimes but different coloring. Diagnose temp/inline ownership before another register search.
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialize geometry locals | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH separate delete size and original count | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH signed cluster count local | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH operator assignment for bytes | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH divide result before output store | 108/108 instructions, structural/exact (0, 32) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH error assignments folded into conditions | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH byte position operand order | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH delete size operand order | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH geometry through explicit ushort casts | 108/108 instructions, structural/exact (0, 35) | restored

HIGH __wpformatter: fetched origin/main, source unchanged; empty narrow-string pool and 593/593, same frame. Operand relationship matters despite normalized register score 0: target narrow alternate string path loads length from r25, while narrow source pointer lives in r24. Target r25 is the previous output pointer or narrow-length temporary; source loads the current narrow pointer. This may be a genuine SDK stale-pointer bug rather than a register tie-break. Do not add an uninitialized pointer read to force this register pattern. Test honest pointer-lifetime changes and record unresolved semantics.
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH reuse output pointer for wide source | compile failed | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH distinct narrow character count | compile failed | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH narrow char pointer mutable | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH wide source pointer hoisted | compile failed | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH count destination shares string-end pointer | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH wide input independent unsigned length | 581/593 instructions, structural/exact (50, 564) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH reuse output pointer for wide source | 593/593 instructions, structural/exact (0, 120) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH distinct narrow character count | 593/593 instructions, structural/exact (2, 170) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH narrow char pointer mutable | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH wide source pointer hoisted | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH count destination shares string-end pointer | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH wide input independent unsigned length | 593/593 instructions, structural/exact (1, 67) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH inline geometry/entry/count boundaries 0 | 108/108 instructions, structural/exact (0, 32) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH inline geometry/entry/count boundaries 1 | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH inline geometry/entry/count boundaries 2 | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH inline geometry/entry/count boundaries 3 | 108/108 instructions, structural/exact (0, 32) | restored

HIGH CDBRecordEncrypt: fetch checked; only owned medium changes differ from origin/main. Pool still diverges first at reduction diagnostics; all literals used by Encrypt are before divergence and correct. Medium has same frame/slots, 284/284, normalized structure zero. Test realistic wrapper and diagnostic inline boundaries to place key and first-file pointer lifetimes, then register search.
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH first attribute inline helper temp/result lifetime 0 | 284/284 instructions, structural/exact (0, 42) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH first attribute inline helper temp/result lifetime 1 | 284/284 instructions, structural/exact (4, 57) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH first attribute inline helper temp/result lifetime 2 | 284/284 instructions, structural/exact (0, 42) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH first attribute inline helper temp/result lifetime 3 | 284/284 instructions, structural/exact (0, 42) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH first attribute inline helper temp/result lifetime 4 | 284/284 instructions, structural/exact (0, 42) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH inline closed diagnostic reports (0,) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH inline closed diagnostic reports (1,) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH inline closed diagnostic reports (0, 1) | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH leading geometry/error/position declaration 0 | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH leading geometry/error/position declaration 1 | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH leading geometry/error/position declaration 2 | 284/284 instructions, structural/exact (0, 44) | restored
HIGH PFCLUSTER_DeleteCluster declaration search after output-count lifetime split: 93 builds, best structural/exact 0/32 unchanged. Restored original rather than retaining a register-only fuzzy experiment.
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH store false before conditional | 190/191 instructions, structural/exact (20, 78) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH false initialized before ternary | 187/191 instructions, structural/exact (19, 75) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH result initially true | 189/191 instructions, structural/exact (18, 99) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH conditional default using byte | 191/191 instructions, structural/exact (3, 20) | restored

HIGH ConstructOpAnalyzeGLGR: origin/main fetch verified owned source unchanged; pool empty and all 96 data bytes exact. Same 239/239 frame/branches. Remaining calculation schedule interleaves name-count, sheet-count, context workspace and glyph-count differently. Target forms byte-aligned flag pointer by adding font after alignment. Test offset-expression tree and scratch helper boundaries before any register search.
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH explicit nested offset calculation | 239/239 instructions, structural/exact (22, 99) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH sequential flag offsets | 239/239 instructions, structural/exact (21, 99) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH named glyph-group counts | 239/239 instructions, structural/exact (22, 99) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH scratch size through SDK helper | 239/239 instructions, structural/exact (22, 104) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH byte flags pointer aligned offset | 239/239 instructions, structural/exact (22, 99) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH full group span named local | 239/239 instructions, structural/exact (22, 99) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH scratch metadata inline helper with typed references | 239/239 instructions, structural/exact (22, 104) | restored

HIGH Raku start/finish: origin/main checked unchanged; string pool identical, 456/456 data and named BSS extents already correct. Target start retains allocator base through status initialization. Target finish saves 7 registers in frame 0x30 and explicitly carries WEP source/destination strides plus loop index; ours uses smaller frame and direct indexed arrays. No fake aggregate data or offset aliases added.
src/scene/setting/iplRakuRakuThread start__Q33ipl5scene14RakuRakuThreadFv | HIGH heap allocator initialized through saved heap handle | 97/96 instructions, structural/exact (13, 88) | restored
src/scene/setting/iplRakuRakuThread start__Q33ipl5scene14RakuRakuThreadFv | HIGH zero progress through aggregate assignment | 99/96 instructions, structural/exact (22, 92) | restored
src/scene/setting/iplRakuRakuThread start__Q33ipl5scene14RakuRakuThreadFv | HIGH initialize socket callbacks in declaration | 95/96 instructions, structural/exact (17, 87) | restored
src/scene/setting/iplRakuRakuThread start__Q33ipl5scene14RakuRakuThreadFv | HIGH named start priority | 97/96 instructions, structural/exact (13, 88) | restored
src/scene/setting/iplRakuRakuThread finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH explicit WEP source and destination strides 0 | 136/133 instructions, structural/exact (43, 127) | restored
src/scene/setting/iplRakuRakuThread finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH explicit WEP source and destination strides 1 | 136/133 instructions, structural/exact (43, 126) | restored
src/scene/setting/iplRakuRakuThread finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH explicit WEP source and destination strides 2 | 136/133 instructions, structural/exact (35, 127) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH header token out-parameter boundary 0 | 189/191 instructions, structural/exact (16, 99) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH header token out-parameter boundary 1 | 187/191 instructions, structural/exact (19, 75) | restored
src/scene/setting/iplRakuRakuThread finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH explicit WEP source and destination strides 3 | 136/133 instructions, structural/exact (43, 126) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH header token out-parameter boundary 2 | 189/191 instructions, structural/exact (16, 72) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH header token out-parameter boundary 3 | 190/191 instructions, structural/exact (18, 78) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH header token out-parameter boundary 4 | 195/191 instructions, structural/exact (19, 76) | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH header token out-parameter boundary 5 | 189/191 instructions, structural/exact (16, 99) | restored
libs/RevoEX/src/cdb/CDBRecord CDBCryptBuffer | HIGH increment output count after selecting chunk length | 119/119 instructions, structural/exact (13, 18) | restored
libs/RevoEX/src/cdb/CDBRecord CDBCryptBuffer | HIGH explicit output pointer null comparisons | 120/119 instructions, structural/exact (10, 93) | restored
libs/RevoEX/src/cdb/CDBRecord CDBCryptBuffer | HIGH loop remainder local | 119/119 instructions, structural/exact (6, 8) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH HMAC lifetime and inline boundary 0 | 284/284 instructions, structural/exact (3, 52) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH HMAC lifetime and inline boundary 1 | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH HMAC lifetime and inline boundary 2 | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH HMAC lifetime and inline boundary 3 | 285/284 instructions, structural/exact (15, 102) | restored
HIGH __wpformatter leading declaration search: 71 builds after split scalar declarations; unchanged 593/593 structural/exact 0/98. Original source restored. Target narrow-alternate load reads r25 while input pointer is r24; proof is at target 0x1d54 versus 0x1d74. No stale/uninitialized pointer read introduced.
HIGH NHTTP final declaration search after initialized-getter statements split: 71 builds, best structural/exact 3/20 unchanged. Reverted split.
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH fallback token-match struct | 191/191 instructions, structural/exact (0, 0) | kept candidate
HIGH NHTTP exact gain: initialized token-match aggregate holds the fallback FALSE across comparison, while success stores TRUE. No new global data, inline assembly, volatile, uninitialized value or symbol edit. Same 191/191, ctxdiff 0, objdiff 100%, pool identical, data 504/504. Quick gate PASS, zero regressions/forbidden/readability; DOL hash correct.
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0,) reversed False | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0,) reversed True | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0, 2) reversed False | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0, 2) reversed True | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0, 1, 2) reversed False | 108/108 instructions, structural/exact (0, 14) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0, 1, 2) reversed True | 108/108 instructions, structural/exact (0, 14) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (1, 2) reversed False | 108/108 instructions, structural/exact (0, 32) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (1, 2) reversed True | 108/108 instructions, structural/exact (0, 32) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0, 5) reversed False | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0, 5) reversed True | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (3, 4) reversed False | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (3, 4) reversed True | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (3, 4, 5, 6) reversed False | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (3, 4, 5, 6) reversed True | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0, 3, 4, 5, 6) reversed False | 108/108 instructions, structural/exact (0, 35) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH cluster-deletion aggregate (0, 3, 4, 5, 6) reversed True | 108/108 instructions, structural/exact (0, 35) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (2,) reversed False | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (2,) reversed True | 284/284 instructions, structural/exact (0, 44) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (0, 2) reversed False | 287/284 instructions, structural/exact (35, 250) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (0, 2) reversed True | 288/284 instructions, structural/exact (34, 255) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (0, 1) reversed False | 291/284 instructions, structural/exact (55, 262) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (0, 1) reversed True | 292/284 instructions, structural/exact (53, 254) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (1, 3, 4) reversed False | 291/284 instructions, structural/exact (42, 264) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (1, 3, 4) reversed True | 291/284 instructions, structural/exact (42, 264) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (0, 1, 2, 3, 4) reversed False | 298/284 instructions, structural/exact (89, 278) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate (0, 1, 2, 3, 4) reversed True | 299/284 instructions, structural/exact (88, 285) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('length', 'cluster_size', 'position') entry_values | compile failed | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('length', 'cluster_size', 'position') zero_values | 118/108 instructions, structural/exact (29, 106) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('length', 'cluster_size', 'position') length_only | compile failed | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('length', 'position', 'cluster_size') entry_values | compile failed | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('length', 'position', 'cluster_size') zero_values | 118/108 instructions, structural/exact (29, 106) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('length', 'position', 'cluster_size') length_only | compile failed | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('cluster_size', 'length', 'position') entry_values | compile failed | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('cluster_size', 'length', 'position') zero_values | 118/108 instructions, structural/exact (29, 106) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('cluster_size', 'position', 'length') entry_values | compile failed | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('cluster_size', 'position', 'length') zero_values | 118/108 instructions, structural/exact (29, 106) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('position', 'length', 'cluster_size') entry_values | compile failed | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('position', 'length', 'cluster_size') zero_values | 118/108 instructions, structural/exact (29, 106) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('position', 'cluster_size', 'length') entry_values | compile failed | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH initialized deletion geometry ('position', 'cluster_size', 'length') zero_values | 118/108 instructions, structural/exact (29, 106) | restored
First CDB input-aggregate rewrite accidentally replaced identifier words inside two diagnostic literals in some variants; those variants were reverted and excluded as pool-invalid. Re-run shields string tokens.
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate preserving literals (0, 2) reversed False | 287/284 instructions, structural/exact (33, 250) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate preserving literals (0, 2) reversed True | 288/284 instructions, structural/exact (32, 255) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate preserving literals (0, 1) reversed False | 291/284 instructions, structural/exact (53, 262) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate preserving literals (0, 1) reversed True | 292/284 instructions, structural/exact (51, 254) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate preserving literals (1, 3, 4) reversed False | 291/284 instructions, structural/exact (41, 264) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate preserving literals (1, 3, 4) reversed True | 291/284 instructions, structural/exact (41, 264) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate preserving literals (0, 1, 2, 3, 4) reversed False | 298/284 instructions, structural/exact (87, 278) | restored
libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt | HIGH encryption input aggregate preserving literals (0, 1, 2, 3, 4) reversed True | 299/284 instructions, structural/exact (86, 285) | restored
libs/RVL_SDK/src/fa/pf_cluster PFCLUSTER_DeleteCluster | HIGH separate immutable input count from byte length | 108/108 instructions, structural/exact (0, 0) | kept candidate
HIGH PFCLUSTER exact gain: ClusterDeletion owns byte position, cluster size and deleted byte length; the incoming cluster count stays immutable until byte conversion after the first trace. This separates count and byte lifetimes instead of overloading the argument. Same 108/108, ctxdiff 0, objdiff 100%, empty pool. Quick gate PASS, zero regressions/forbidden/readability, DOL hash correct. All fields initialized before use; no extra data object or symbol edit.
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0,) reversed False | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0,) reversed True | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 1) reversed False | compile failed | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 1) reversed True | compile failed | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 2) reversed False | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 2) reversed True | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 1, 2) reversed False | compile failed | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 1, 2) reversed True | compile failed | restored
libs/RevoEX/src/nhttp/NHTTP_thread NHTTPi_ThreadParseHeaderProc | HIGH fill token match result before storing successful connection state | 191/191 instructions, structural/exact (0, 0) | kept candidate
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 1, 2) reversed False | compile failed | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 1, 2) reversed True | compile failed | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (3, 4, 5) reversed False | 239/239 instructions, structural/exact (22, 103) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (3, 4, 5) reversed True | 239/239 instructions, structural/exact (22, 103) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 3, 5) reversed False | 239/239 instructions, structural/exact (22, 88) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 3, 5) reversed True | 239/239 instructions, structural/exact (22, 88) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 1, 2, 3, 4, 5, 6) reversed False | compile failed | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 1, 2, 3, 4, 5, 6) reversed True | compile failed | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 1, 2) reversed False | 239/239 instructions, structural/exact (22, 89) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 1, 2) reversed True | 239/239 instructions, structural/exact (22, 99) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (3, 4, 5) reversed False | 239/239 instructions, structural/exact (22, 103) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (3, 4, 5) reversed True | 239/239 instructions, structural/exact (22, 103) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 3, 5) reversed False | 239/239 instructions, structural/exact (22, 88) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 3, 5) reversed True | 239/239 instructions, structural/exact (22, 88) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 1, 2, 3, 4, 5, 6) reversed False | 239/239 instructions, structural/exact (22, 109) | restored
libs/NW4R/src/ut/ut_ArchiveFontBase ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader | HIGH glyph sheet layout aggregate (0, 1, 2, 3, 4, 5, 6) reversed True | 239/239 instructions, structural/exact (22, 109) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0,) reversed False | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0,) reversed True | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 1) reversed False | 593/593 instructions, structural/exact (0, 117) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 1) reversed True | 593/593 instructions, structural/exact (0, 117) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 2) reversed False | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 2) reversed True | 593/593 instructions, structural/exact (0, 98) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 1, 2) reversed False | 593/593 instructions, structural/exact (0, 117) | restored
libs/MSL/src/MSL_Common/wprintf __wpformatter | HIGH format output aggregate (0, 1, 2) reversed True | 593/593 instructions, structural/exact (0, 117) | restored

## HIGH completion audit
libs/NW4R/src/ut/ut_ArchiveFontBase: origin/main source unchanged from initial owned baseline = True.
src/scene/setting/iplRakuRakuThread: origin/main source unchanged from initial owned baseline = True.
libs/RVL_SDK/src/fa/pf_cluster: origin/main source unchanged from initial owned baseline = True.
libs/RevoEX/src/nhttp/NHTTP_thread: origin/main source unchanged from initial owned baseline = True.
libs/MSL/src/MSL_Common/wprintf: origin/main source unchanged from initial owned baseline = True.
libs/RevoEX/src/cdb/CDBRecord: origin/main source unchanged from initial owned baseline = True.
NHTTPi_ThreadParseHeaderProc exact 191/191, ctxdiff 0; genuine TokenMatch tracks FALSE fallback and TRUE match before assigning keepAlive. All unit code/data 100%.
PFCLUSTER_DeleteCluster exact 108/108, ctxdiff 0; byte geometry object separates immutable requested count from byte position/cluster size/deletion length. All unit code 100%; no data section.
All six remaining open functions have at least three distinct compiled HIGH source attempts, excluding failed compilations and token-rewrite mistakes.
Archive: offset expression tree, sequential offsets, metadata locals, scratch helper and layout aggregates; remaining 22 normalized structural differences, 99 total positional differences.
Raku start: heap handle, progress aggregate, socket callback initialization, named priority. Finish: explicit WEP source/destination strides, independent index and zero lifetime; shared BSS base and frame/branch schedule still differ.
wprintf: pointer reuse/hoisting, independent wide/narrow lengths, count destination scope, output aggregates, 71 declaration builds. Target narrow alternate load has a stale-pointer operand relationship; no uninitialized read added to force it.
CDB Encrypt: first attribute wrapper lifetimes, closed diagnostic wrappers, HMAC helper/input lifetimes, protected-literal input aggregates; 284/284, normalized structure zero, 44 register differences. Medium 99.19014% retained.
CDB Crypt: output count scheduling, explicit null comparison, loop remainder; original 119/119 has only three wrong literal offsets from missing earlier diagnostics.
All rejected source variations restored. Local initialized result/range types emit no new global data. No data-symbol rename or extent correction justified; owned data scores unchanged, config untouched.
HIGH gains: NHTTP exact 25 -> 26 and code 10528 -> 11292; cluster exact 7 -> 8 and code 4120 -> 4552. Other exact/code/data counts unchanged. No linking/configure change.

## HIGH final full gate and open-function re-list
ConstructOpAnalyzeGLGR__Q44nw4r2ut6detail15ArchiveFontBaseFPQ54nw4r2ut6detail15ArchiveFontBase16ConstructContextPQ54nw4r2ut6detail15ArchiveFontBase18CachedStreamReader: 90.03766% open; 19 compiled HIGH attempts; src 0x3bc base 0x3bc insns 239/239
libs/NW4R/src/ut/ut_ArchiveFontBase matched_functions: 22 -> 22
libs/NW4R/src/ut/ut_ArchiveFontBase matched_code: 4164 -> 4164
libs/NW4R/src/ut/ut_ArchiveFontBase matched_data: 96 -> 96
start__Q33ipl5scene14RakuRakuThreadFv: 88.635414% open; 4 compiled HIGH attempts; src 0x184 base 0x180 insns 97/96
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi: 86.56391% open; 4 compiled HIGH attempts; src 0x21c base 0x214 insns 135/133
src/scene/setting/iplRakuRakuThread matched_functions: 12 -> 12
src/scene/setting/iplRakuRakuThread matched_code: 1252 -> 1252
src/scene/setting/iplRakuRakuThread matched_data: 456 -> 456
libs/RVL_SDK/src/fa/pf_cluster matched_functions: 7 -> 8
libs/RVL_SDK/src/fa/pf_cluster matched_code: 4120 -> 4552
libs/RVL_SDK/src/fa/pf_cluster matched_data: 0 -> 0
libs/RevoEX/src/nhttp/NHTTP_thread matched_functions: 25 -> 26
libs/RevoEX/src/nhttp/NHTTP_thread matched_code: 10528 -> 11292
libs/RevoEX/src/nhttp/NHTTP_thread matched_data: 504 -> 504
__wpformatter: 99.13997% open; 21 compiled HIGH attempts; src 0x944 base 0x944 insns 593/593
libs/MSL/src/MSL_Common/wprintf matched_functions: 8 -> 8
libs/MSL/src/MSL_Common/wprintf matched_code: 6264 -> 6264
libs/MSL/src/MSL_Common/wprintf matched_data: 836 -> 836
CDBCryptBuffer: 99.97479% open; 3 compiled HIGH attempts; src 0x1dc base 0x1dc insns 119/119
CDBRecordEncrypt: 99.19014% open; 25 valid compiled HIGH attempts (8 accidental literal-rewrite variants excluded); src 0x470 base 0x470 insns 284/284
libs/RevoEX/src/cdb/CDBRecord matched_functions: 27 -> 27
libs/RevoEX/src/cdb/CDBRecord matched_code: 5464 -> 5464
libs/RevoEX/src/cdb/CDBRecord matched_data: 144 -> 144
NHTTPi_ThreadParseHeaderProc final src 0x2fc base 0x2fc insns 191/191; diffs 0: []
PFCLUSTER_DeleteCluster final src 0x1b0 base 0x1b0 insns 108/108; diffs 0: []
Final full gate (non --quick) over all six owned units:
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/NW4R/src/ut/ut_ArchiveFontBase] objdiff: code 4164/5120 data 96/96 functions 22/23 fuzzy 98.1398 linked code 0
[src/scene/setting/iplRakuRakuThread] objdiff: code 1252/2168 data 456/456 functions 12/14 fuzzy 94.6900 linked code 0
[libs/RVL_SDK/src/fa/pf_cluster] objdiff: code 4552/4552 data None/None functions 8/8 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_thread] objdiff: code 11292/11292 data 504/504 functions 26/26 fuzzy 100.0000 linked code 0
[libs/MSL/src/MSL_Common/wprintf] objdiff: code 6264/8636 data 836/836 functions 8/9 fuzzy 99.7638 linked code 0
[libs/RevoEX/src/cdb/CDBRecord] objdiff: code 5464/7076 data 144/2640 functions 27/29 fuzzy 99.8683 linked code 0
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
Remaining CDB pool reconstruction and wprintf alternate-string pointer semantics remain unresolved; no unsupported data rename/extent change or uninitialized read retained.
