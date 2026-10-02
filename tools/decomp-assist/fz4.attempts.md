# fz4 attempts

Baseline origin/main c4857800; all four string pools identical.

src/scene/memoryCard/iplGCWindow: {'fuzzy_match_percent': 99.83982, 'total_code': '9964', 'matched_code': '9172', 'matched_code_percent': 92.051384, 'total_data': '2032', 'matched_data': '2032', 'matched_data_percent': 100.0, 'total_functions': 48, 'matched_functions': 47, 'matched_functions_percent': 97.91667, 'total_units': 1}

libs/RVLMiddleware/eZiText/src/clib/zoemdata: {'fuzzy_match_percent': 98.29918, 'total_code': '976', 'matched_code': '208', 'matched_code_percent': 21.311476, 'total_data': '60', 'matched_data': '60', 'matched_data_percent': 100.0, 'total_functions': 3, 'matched_functions': 2, 'matched_functions_percent': 66.66667, 'total_units': 1}

libs/RevoEX/src/nwc24/NWC24MBoxCtrl: {'fuzzy_match_percent': 99.80762, 'total_code': '10604', 'matched_code': '10104', 'matched_code_percent': 95.2848, 'total_data': '192', 'matched_data': '184', 'matched_data_percent': 95.83333, 'total_functions': 25, 'matched_functions': 23, 'matched_functions_percent': 92.0, 'total_units': 1}

libs/RVL_SDK/src/fa/pf_cache: {'fuzzy_match_percent': 99.77555, 'total_code': '7396', 'matched_code': '6464', 'matched_code_percent': 87.3986, 'matched_data_percent': 100.0, 'total_functions': 36, 'matched_functions': 35, 'matched_functions_percent': 97.22222, 'complete_data_percent': 100.0, 'total_units': 1}

PFCACHE_DoWriteNumSectorAndFreeIfNeeded structural diagnosis: 233/233 instructions, third overlap branch computes last sector via cancelled page-sector rather than request end. Attempt 1: compute request end directly before overlap count.
Attempt 1 result: 232/233 instructions; request end hoisted, broad register changes; rejected. Attempt 2: simplify overlap count while retaining page-relative last-sector expression.
Attempt 2 result: same 9 scheduling differences. Attempt 3: shared request-end temporary, then subtract page start and decrement last sector.
Attempt 3 result: 232/233, request end reused from r31. Attempt 4: retain original overlap expression and compute last sector directly using reversed operand order.
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap arithmetic variant 5: structural/exact/instructions (17, 109, 236, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap arithmetic variant 6: structural/exact/instructions (17, 109, 236, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap arithmetic variant 7: structural/exact/instructions (17, 109, 236, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap arithmetic variant 8: structural/exact/instructions (15, 228, 232, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap arithmetic variant 9: structural/exact/instructions (4, 9, 233, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap arithmetic variant 10: structural/exact/instructions (17, 109, 236, 233)
NWC24iIsMsgObjReadable: local message type: structural/exact/instructions (4, 5, 57, 57)
NWC24iIsMsgObjReadable: nested readable branch: structural/exact/instructions (4, 5, 57, 57)
NWC24iIsMsgObjReadable: explicit entry local: structural/exact/instructions (4, 5, 57, 57)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: declare position before zero: structural/exact/instructions (42, 81, 201, 198)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: unsigned block count: structural/exact/instructions (4, 48, 198, 198)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: declare block count before digit table: structural/exact/instructions (18, 60, 198, 198)
NWC24iMBoxCheck: individual oldest id and header locals: structural/exact/instructions (15, 40, 66, 68)
NWC24iMBoxCheck: direct oldest id assignment: structural/exact/instructions (10, 38, 67, 68)
NWC24iMBoxCheck: inline helper local id value: structural/exact/instructions (10, 38, 67, 68)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: inline interpolation result: structural/exact/instructions (6, 71, 199, 198)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: direct converted block count: structural/exact/instructions (18, 60, 198, 198)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: array digits scope: structural/exact/instructions (4, 48, 198, 198)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: wchar digits separate initialization: structural/exact/instructions (16, 48, 198, 198)
Zi8MatchOEMdata: predecrement capacity in bounds test: structural/exact/instructions (0, 47, 192, 192)
Zi8MatchOEMdata: initialize index after continuation reset: structural/exact/instructions ('compile failed', 'LMiddleware/eZiText/src/clib/zoemdata.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVLMiddleware\\eZiText\\src\\clib\\zoemdata.c\n# -------------------------------------------------------\n#      30:     ziS32 index = ZI_WORK->oemIdx; \n#   Error:     ^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n')
Zi8MatchOEMdata: unsigned index matching OEM index: structural/exact/instructions (2, 40, 192, 192)

Data proof: MountInfo at 0x81698DF8 is an 8-byte {s32 count; NWC24MBoxType type;} object. Target MountVFMBox relocates to MountInfo and stores the type at +4; target Unmount/ForceUnmount load type at +4. Expand extraction extent 4->8 within unchanged 8-byte .sbss section; no address or section-total change.
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: const zero vector: structural/exact/instructions (4, 48, 198, 198)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: const interpolation position: structural/exact/instructions (4, 48, 198, 198)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: declare block count before loop: structural/exact/instructions (4, 48, 198, 198)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: reuse block return local: structural/exact/instructions (4, 48, 198, 198)
NWC24iMBoxCheck: single field id object and separate header: structural/exact/instructions (15, 40, 66, 68)
NWC24iMBoxCheck: single field header object and separate id: structural/exact/instructions (15, 40, 66, 68)
NWC24iMBoxCheck: helper returns loaded id: structural/exact/instructions (10, 38, 67, 68)
NWC24iMBoxCheck: id passed through local pointer: structural/exact/instructions (10, 38, 67, 68)
NWC24iIsMsgObjReadable: common unreadable tail: structural/exact/instructions (19, 55, 53, 57)
NWC24iIsMsgObjReadable: combine unreadable masks: structural/exact/instructions (10, 55, 53, 57)
NWC24iIsMsgObjReadable: explicit mask equality: structural/exact/instructions (4, 5, 57, 57)
NWC24iIsMsgObjReadable: readable flags via shift: structural/exact/instructions (4, 5, 57, 57)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: left associative overlap subtraction: structural/exact/instructions (4, 9, 233, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: subtract sector before num sector: structural/exact/instructions (4, 9, 233, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: cancel through page end temporary: structural/exact/instructions (18, 110, 237, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: use signed request sum: structural/exact/instructions (4, 9, 233, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap subtract page minus request: structural/exact/instructions (15, 107, 234, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: overlap reversed request operands: structural/exact/instructions (15, 107, 234, 233)
Zi8MatchOEMdata: local work pointer declaration position 0: structural/exact/instructions (18, 184, 196, 192)
Zi8MatchOEMdata: local work pointer declaration position 1: structural/exact/instructions (18, 184, 196, 192)
Zi8MatchOEMdata: local work pointer declaration position 2: structural/exact/instructions (18, 184, 196, 192)
Zi8MatchOEMdata: local work pointer declaration position 3: structural/exact/instructions (18, 184, 196, 192)
Zi8MatchOEMdata: local work replaces call argument: structural/exact/instructions (22, 186, 196, 192)
Zi8MatchOEMdata: local work with predecrement capacity: structural/exact/instructions (20, 186, 196, 192)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: inline zero vector temporary: structural/exact/instructions (0, 44, 198, 198)
init__Q33ipl5scene8GCWindowFRCQ33ipl4math4VEC3PQ33ipl5scene17MemoryCardManagerUcs: inline digit formatting boundary: structural/exact/instructions (41, 52, 198, 198)

GCWindow::init: inline zero vector fixes both VEC3 stack offsets, structural diffs 4->0. declsearch swapped decimal initialization before blockCount declaration; all uses remain initialized. Exact 198/198 instructions, diffs 0. Original register-only difference was lifetime/declaration ordering.
Zi8MatchOEMdata: declsearch original leading four locals tried 13 orders, no improvement; predecrement variant tried 13 orders, no exact result. Restored baseline source.

First full gate PASS: GCWindow 48/48, code9964/9964,data2032/2032; MountInfo extraction data192/192; zero regressions/forbidden/readability warnings; DOL26116613f624061ba99c8d1a299aaa6efa85670d.
Zi8MatchOEMdata: 16 bit unsigned OEM index: structural/exact/instructions (16, 180, 196, 192)
Zi8MatchOEMdata: 16 bit signed OEM index: structural/exact/instructions (16, 180, 196, 192)
Zi8MatchOEMdata: initialize index before fallback: structural/exact/instructions (3, 182, 193, 192)
Zi8MatchOEMdata: move fallback initialization after index: structural/exact/instructions (4, 45, 192, 192)
Zi8MatchOEMdata: signed pattern position: structural/exact/instructions (2, 40, 192, 192)
NWC24iIsMsgObjReadable: inline readability validation boundary: structural/exact/instructions (11, 54, 60, 57)
NWC24iMBoxCheck: header pointer passed to oldest helper: structural/exact/instructions (10, 38, 67, 68)
NWC24iMBoxCheck: copy oldest id through memcpy: structural/exact/instructions (16, 41, 70, 68)
NWC24iMBoxCheck: helper returns status checked by caller: structural/exact/instructions (19, 66, 74, 68)
Zi8MatchOEMdata: scoped OEM index ziS32 index = ZI_WORK->oemIdx;: structural/exact/instructions (12, 191, 196, 192)
Zi8MatchOEMdata: scoped OEM index ziS32 index;
    index = ZI_WORK->oemIdx;: structural/exact/instructions (12, 191, 196, 192)
Zi8MatchOEMdata: index declaration before folded char: structural/exact/instructions (2, 40, 192, 192)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: inline request overlap helper: structural/exact/instructions (27, 113, 236, 233)
PFCACHE_DoWriteNumSectorAndFreeIfNeeded: inline page overlap helper: structural/exact/instructions (27, 110, 235, 233)

PFCACHE register-only follow-up after structural arithmetic/boundary trials:
declaration block:
      PF_CACHE_PAGE* p_page = PF_NULL;
      pf_s32 err;
      pf_u32 num_rest_sector = num_sector;
      pf_u8* p_sbuf;
      pf_u8* p_ebuf;
      pf_u32 num_overlap;
      pf_u32 last_sector;
start (4, 9)
best (4, 9) after 52 builds; source restored; best order was:
    PF_CACHE_PAGE* p_page = PF_NULL;
    pf_s32 err;
    pf_u32 num_rest_sector = num_sector;
    pf_u8* p_sbuf;
    pf_u8* p_ebuf;
    pf_u32 num_overlap;
    pf_u32 last_sector;

Zi8MatchOEMdata: int OEM index: structural/exact/instructions (2, 40, 192, 192)
Zi8MatchOEMdata: unsigned int OEM index: structural/exact/instructions (2, 40, 192, 192)
Zi8MatchOEMdata: local continuation fallback boolean: structural/exact/instructions (9, 85, 193, 192)
Zi8MatchOEMdata: OEM callback result temporary: structural/exact/instructions (14, 70, 193, 192)

Final structural audit:
- NWC24iIsMsgObjReadable: target/ours 57/57 instructions; only first field load and mask test scheduled before LR/r31 saves in ours. Seven distinct condition/local/helper trials rejected; no volatile, assembly, or added source retained.
- NWC24iMBoxCheck: target/ours 68/67; target stores oldest id then reloads into r4 at stack +8, ours forwards the loaded value. Separate locals remove spill or reorder stack; helper forms, pointer indirection, and memcpy do not reproduce target reload. Ten distinct trials rejected.
- Zi8MatchOEMdata: target/ours 192/192; bounds-check length narrowing and capacity decrement swap scheduling, plus saved-register permutation: target work r29/index r26 versus ours work r28/index r29. Leading-declaration search, scoped index, width/signedness, typed work pointer, bounds form and callback temporary all tested. No exact candidate; baseline restored.
- PFCACHE_DoWriteNumSectorAndFreeIfNeeded: target/ours 233/233; third overlap branch target recomputes reversed request end before overlap subtraction; ours reuses loop-invariant r31 then reconstructs end through page start. Arithmetic reassociation and helper-boundary trials unsuccessful; declsearch 52 builds leaves structural/exact 4/9. Baseline restored.
- GCWindow::init accepted exact 198/198 with zero differences; data100%. All four unit data scores100%; pf_cache has no data bytes.
Completeness audit: every remaining function has more than three logged distinct source-level attempts. No untried function remains. All trial edits except exact GCWindow source and relocation-proven MountInfo extent were restored.

Final full clean gate:
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/memoryCard/iplGCWindow] pool: IDENTICAL
[src/scene/memoryCard/iplGCWindow] objdiff: code 9964/9964 data 2032/2032 functions 48/48 fuzzy 100.0000 linked code 0
[src/scene/memoryCard/iplGCWindow] instruction-exact functions: 48/48
[src/scene/memoryCard/iplGCWindow]   section .data size 1784 match 100.0
[src/scene/memoryCard/iplGCWindow]   section .rodata size 176 match 100.0
[src/scene/memoryCard/iplGCWindow]   section .sdata size 48 match 100.0
[src/scene/memoryCard/iplGCWindow]   section .sdata2 size 24 match 100.0
[src/scene/memoryCard/iplGCWindow]   section .text size 9964 match 100.0
[src/scene/memoryCard/iplGCWindow] baseline: code 9172/9964 data 2032 functions 47 fuzzy 99.8398
[libs/RVL_SDK/src/fa/pf_cache] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pf_cache] objdiff: code 6464/7396 data None/None functions 35/36 fuzzy 99.7755 linked code 0
[libs/RVL_SDK/src/fa/pf_cache] instruction-exact functions: 35/36
[libs/RVL_SDK/src/fa/pf_cache]   section .text size 7396 match 99.77555
[libs/RVL_SDK/src/fa/pf_cache]   below 100: PFCACHE_DoWriteNumSectorAndFreeIfNeeded 98.21889
[libs/RVL_SDK/src/fa/pf_cache] baseline: code 6464/7396 data None functions 35 fuzzy 99.7755
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] objdiff: code 208/976 data 60/60 functions 2/3 fuzzy 98.2992 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] instruction-exact functions: 2/3
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section .text size 976 match 98.29918
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extab size 24 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   section extabindex size 36 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zoemdata]   below 100: Zi8MatchOEMdata 97.83854
[libs/RVLMiddleware/eZiText/src/clib/zoemdata] baseline: code 208/976 data 60 functions 2 fuzzy 98.2992
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl] objdiff: code 10104/10604 data 192/192 functions 23/25 fuzzy 99.8076 linked code 0
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl] instruction-exact functions: 23/25
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl]   section .data size 168 match 100.0
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl]   section .text size 10604 match 99.80762
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl]   below 100: NWC24iIsMsgObjReadable 92.98245
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl]   below 100: NWC24iMBoxCheck 98.382355
[libs/RevoEX/src/nwc24/NWC24MBoxCtrl] baseline: code 10104/10604 data 184 functions 23 fuzzy 99.8076
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.60052
global fuzzy_match_percent: 99.45531 -> 99.45585
global complete_code_percent: 63.16065 -> 63.16065
global matched_data_percent: 98.50994 -> 98.51038
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```
