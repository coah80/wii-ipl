# CHANSVm round 7 attempts

Baseline ab015200: 216/233 instruction-exact; code 35484/53564; data 6904/6904; all 121 .data relocations match.
Pool checked before code experiments. Source scope is CHANSVm.c.

Initial CHANSVmGetSourceLine: 97.826090%; instructions 46/46; structural 0; diffs 16.
Initial CHANSVmNewObjData: 99.583336%; instructions 96/96; structural 0; diffs 7.
Initial CHANSVmParseInt: 94.693880%; instructions 49/49; structural 2; diffs 3.
Initial CHANSVm_8144B4D4: 97.590360%; instructions 83/83; structural 2; diffs 2.
Initial VmDateDtor: 94.967030%; instructions 91/91; structural 5; diffs 7.
Initial VmStringFromCharCode: 99.406780%; instructions 59/59; structural 0; diffs 6.
Initial VmStringReplace: 97.878784%; instructions 132/132; structural 0; diffs 40.
Initial VmStringSplit: 98.040540%; instructions 222/222; structural 0; diffs 66.
Initial CHANSVm_8145049C: 99.849190%; instructions 431/431; structural 0; diffs 13.
Initial VmBlobGetHexString: 98.719510%; instructions 82/82; structural 0; diffs 14.
Initial VmBlobPackCommon: 97.934135%; instructions 668/668; structural 2; diffs 246.
Initial VmBlobUnpack: 98.268860%; instructions 517/517; structural 0; diffs 156.
Initial VmWinEmuWrite: 99.626870%; instructions 67/67; structural 0; diffs 5.
Initial CHANSVmAddExe: 99.153540%; instructions 254/254; structural 0; diffs 34.
Initial CHANSVmLinkModules: 98.677246%; instructions 189/189; structural 0; diffs 43.
Initial VmCallMethod: 98.060500%; instructions 281/281; structural 0; diffs 91.
Initial CHANSVmStep: 96.452515%; instructions 1253/1253; structural 71; diffs 318.
- CHANSVmNewObjData: chunk index scoped to chunk fallback scan; 99.583336%; instructions 96/96; structural 0; diffs 7; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: aligned allocation size scoped after entry selection; 99.427086%; instructions 96/96; structural 0; diffs 10; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: explicit chunk slot kept only across allocation; 99.583336%; instructions 96/96; structural 0; diffs 7; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: chunk table scanned with pointer and index; 90.020836%; instructions 96/96; structural 17; diffs 53; code 35484; data 6904/6904; restored.
- VmWinEmuWrite: aligned total length scoped inside valid string; 99.626870%; instructions 67/67; structural 0; diffs 5; code 35484; data 6904/6904; restored.
- VmWinEmuWrite: remaining and converted lengths scoped per conversion; 99.626870%; instructions 67/67; structural 0; diffs 5; code 35484; data 6904/6904; restored.
- VmWinEmuWrite: capture conversion return directly at declaration; 99.626870%; instructions 67/67; structural 0; diffs 5; code 35484; data 6904/6904; restored.
- VmWinEmuWrite: for loop owns the byte offset; COMPILE FAIL; restored. /43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    6072:         for (u32 offset = 0; offset < totalLength; offset += 0x80) {  #   Error:              ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- CHANSVmNewObjData: declaration-order search, 120 distinct compiling orders; best structural/diffs (0, 7); 99.583336%; data 6904/6904; restored.
- VmWinEmuWrite: declaration-order search, 120 distinct compiling orders; best structural/diffs (0, 5); 99.626870%; data 6904/6904; restored.
- CHANSVmParseInt: zero parser endpoint with memset; 77.020410%; instructions 53/49; structural 21; diffs 51; code 35484; data 6904/6904; restored.
- CHANSVm_8144B4D4: zero parser endpoint with memset; 93.915665%; instructions 86/83; structural 9; diffs 74; data 6904/6904; restored.
- CHANSVmParseInt: cache object type as unsigned full word; 94.693880%; instructions 49/49; structural 2; diffs 3; code 35484; data 6904/6904; restored.
- CHANSVm_8144B4D4: cache object type as unsigned full word; 97.590360%; instructions 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVmParseInt: assign type at declaration after endpoint declaration; 94.693880%; instructions 49/49; structural 2; diffs 3; code 35484; data 6904/6904; restored.
- CHANSVm_8144B4D4: assign type at declaration after endpoint declaration; 97.590360%; instructions 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVmParseInt: initialize endpoint and type in one expression; 94.693880%; instructions 49/49; structural 2; diffs 3; code 35484; data 6904/6904; restored.
- CHANSVm_8144B4D4: initialize endpoint and type in one expression; 97.590360%; instructions 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVmParseInt: load object type directly after parser endpoint initialization; 83.673470%; instructions 49/49; structural 4; diffs 5; code 35484; data 6904/6904; restored.
- CHANSVm_8144B4D4: load object type directly after parser endpoint initialization; 95.180725%; instructions 83/83; structural 2; diffs 3; data 6904/6904; restored.
- VmStringFromCharCode: word value temporary before UTF16 character mask; 94.322040%; instructions 57/59; structural 9; diffs 45; code 35484; data 6904/6904; restored.
- VmStringFromCharCode: separate character index increment from byte cursor increment; 99.406780%; instructions 59/59; structural 0; diffs 6; code 35484; data 6904/6904; restored.
- VmStringFromCharCode: for traversal owns argument conversion scope; 99.322040%; instructions 59/59; structural 0; diffs 7; code 35484; data 6904/6904; restored.
- VmStringFromCharCode: mask wide character with typed word mask; 94.322040%; instructions 57/59; structural 9; diffs 45; code 35484; data 6904/6904; restored.
- VmStringFromCharCode: converted integer helper call boundary; 99.406780%; instructions 59/59; structural 0; diffs 6; code 35484; data 6904/6904; restored.
- VmDateDtor: month and day tables use explicit pointer addition; 94.967030%; instructions 91/91; structural 5; diffs 7; code 35484; data 6904/6904; restored.
- VmDateDtor: cache weekday index and month index at format branch; 94.967030%; instructions 91/91; structural 5; diffs 7; code 35484; data 6904/6904; restored.
- VmDateDtor: format using explicit year value beside table pointers; 94.967030%; instructions 91/91; structural 5; diffs 7; code 35484; data 6904/6904; restored.
- CHANSVmGetSourceLine: inline module source-line lookup helper, module before pc; 88.369570%; instructions 48/46; structural 8; diffs 26; code 35484; data 6904/6904; restored.
- CHANSVmGetSourceLine: inline module source-line lookup helper, pc before module; 88.369570%; instructions 48/46; structural 8; diffs 26; code 35484; data 6904/6904; restored.
- CHANSVmGetSourceLine: declare module/table/pc alongside context with checked loads; 97.391304%; instructions 46/46; structural 0; diffs 17; code 35484; data 6904/6904; restored.
- CHANSVmGetSourceLine: unsigned marker offset separated from line table pointer; 97.826090%; instructions 46/46; structural 0; diffs 16; code 35484; data 6904/6904; restored.
- VmWinEmuWrite: save raw argument before string conversion; 99.626870%; instructions 67/67; structural 0; diffs 5; code 35484; data 6904/6904; restored.
- VmWinEmuWrite: loop uses current total length and named converted object; 99.626870%; instructions 67/67; structural 0; diffs 5; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: reserve chunk inline helper variant 1; 99.843750%; instructions 96/96; structural 0; diffs 3; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: reserve chunk inline helper variant 2; 99.843750%; instructions 96/96; structural 0; diffs 3; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: reserve chunk inline helper variant 3; 99.427086%; instructions 96/96; structural 0; diffs 10; code 35484; data 6904/6904; restored.
- VmWinEmuWrite: inline converted string writer variant 1; 99.104480%; instructions 67/67; structural 5; diffs 13; code 35484; data 6904/6904; restored.
- VmWinEmuWrite: inline converted string writer variant 2; 96.388060%; instructions 67/67; structural 9; diffs 16; code 35484; data 6904/6904; restored.
- VmStringFromCharCode: inline integer character conversion variant 1; 99.406780%; instructions 59/59; structural 0; diffs 6; code 35484; data 6904/6904; restored.
- VmStringFromCharCode: inline integer character conversion variant 2; 99.406780%; instructions 59/59; structural 0; diffs 6; code 35484; data 6904/6904; restored.
- VmDateDtor: inline calendar formatting variant 1; 94.967030%; instructions 91/91; structural 5; diffs 7; code 35484; data 6904/6904; restored.
- VmDateDtor: inline calendar formatting variant 2; 94.967030%; instructions 91/91; structural 5; diffs 7; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: reserve chunk inline helper selected for refinement; 99.843750%; instructions 96/96; structural 0; diffs 3; code 35484; data 6904/6904; retained.
- CHANSVmNewObjData: allocated size declared after reserved entry; 99.843750%; instructions 96/96; structural 0; diffs 3; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: outer private VM reference drives allocation; 99.270836%; instructions 96/96; structural 0; diffs 14; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: allocation size declared inside allocation scope; 99.843750%; instructions 96/96; structural 0; diffs 3; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: inline allocator for a reserved chunk entry; COMPILE FAIL; restored. ceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #     384:             object->value.ptr_v = entry;  #   Error:                                        ^ #   (10209) illegal implicit conversion from 'struct ChunkEntry *' to #   'void **' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
Restored whole-reservation helper pending a narrower scan boundary; its only surviving differences were three allocation-size registers, 99.843750%.
- CHANSVmNewObjData: reserve and allocate inline helper boundaries; 97.708336%; instructions 98/96; structural 6; diffs 13; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: reserve helper with typed aligned size named in outer scope; 99.843750%; instructions 96/96; structural 0; diffs 3; code 35484; data 6904/6904; restored.
- CHANSVmNewObjData: reserve helper with allocated byte count initialized at use; COMPILE FAIL; restored. /43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #     390:     u32 memSize = VM_ALIGN(length);  #   Error:     ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- CHANSVmNewObjData: inline chunk fallback scan keeps allocation in caller; 94.583336%; instructions 99/96; structural 8; diffs 67; code 35484; data 6904/6904; restored.
- VmBlobGetHexString: hex pairs share one character index; 90.060974%; instructions 83/82; structural 10; diffs 38; code 35484; data 6904/6904; restored.
- VmBlobGetHexString: character index advances after both hex digits; 93.780490%; instructions 79/82; structural 10; diffs 37; code 35484; data 6904/6904; restored.
- VmBlobGetHexString: byte loop index determines both output positions; 93.780490%; instructions 79/82; structural 10; diffs 37; code 35484; data 6904/6904; restored.
- VmBlobGetHexString: first nibble scoped before output index arithmetic; 98.719510%; instructions 82/82; structural 0; diffs 14; code 35484; data 6904/6904; restored.
- VmStringFromCharCode: argument index determines the two byte positions; 100.000000%; instructions 59/59; structural 0; diffs 0; code 35720; data 6904/6904; restored.
- VmStringFromCharCode: argument index determines the two byte positions exact candidate; 100.000000%; instructions 59/59; structural 0; diffs 0; code 35720; data 6904/6904; retained.
- CHANSVmNewObjData: remove unobserved traversal-offset initialization and increments; 99.583336%; instructions 96/96; structural 0; diffs 7; code 35720; data 6904/6904; restored.
- CHANSVmNewObjData: typed chunk entry and direct global chunk index; 99.583336%; instructions 96/96; structural 0; diffs 7; code 35720; data 6904/6904; restored.
- CHANSVmNewObjData: first fallback slot declared at scan boundary; 99.583336%; instructions 96/96; structural 0; diffs 7; code 35720; data 6904/6904; restored.
- VmBlobGetHexString: byte iteration supplies first destination index; 98.719510%; instructions 82/82; structural 0; diffs 14; code 35720; data 6904/6904; restored.
- VmBlobGetHexString: byte iteration supplies second destination index; 95.536580%; instructions 81/82; structural 9; diffs 36; code 35720; data 6904/6904; restored.
- VmBlobGetHexString: hex second index is initialized before first index cursor; 98.719510%; instructions 82/82; structural 0; diffs 14; code 35720; data 6904/6904; restored.
- CHANSVmGetSourceLine: program-counter-derived source entry index with explicit marker limit; 97.826090%; instructions 46/46; structural 0; diffs 18; code 35720; data 6904/6904; restored.
- CHANSVm_8145049C: typed string-format payload/owner/count declaration location 1; 99.187935%; instructions 431/431; structural 0; diffs 53; code 35720; data 6904/6904; restored.
- CHANSVm_8145049C: typed string-format payload/owner/count declaration location 2; 99.187935%; instructions 431/431; structural 0; diffs 53; code 35720; data 6904/6904; restored.
- CHANSVm_8145049C: typed string-format payload/owner/count declaration location 3; 99.849190%; instructions 431/431; structural 0; diffs 13; code 35720; data 6904/6904; restored.
- VmStringReplace: source and search payloads cached as typed string values; 97.954544%; instructions 132/132; structural 0; diffs 45; code 35720; data 6904/6904; restored.
- VmStringReplace: scope parent/search lengths after string conversions; 97.878784%; instructions 132/132; structural 0; diffs 40; code 35720; data 6904/6904; restored.
- VmStringReplace: second conversion uses its own argument scope; 97.878784%; instructions 132/132; structural 0; diffs 40; code 35720; data 6904/6904; restored.
- VmStringReplace: tail copy derives segment length at the copy site; 97.878784%; instructions 132/132; structural 0; diffs 40; code 35720; data 6904/6904; restored.
- VmStringSplit: cache parent and delimiter string records; 97.567566%; instructions 222/222; structural 0; diffs 88; code 35720; data 6904/6904; restored.
- VmStringSplit: loop counts initialized before cursors; 98.040540%; instructions 222/222; structural 0; diffs 66; code 35720; data 6904/6904; restored.
- VmStringSplit: delimiter miss branches around matched-segment tail; 96.238740%; instructions 222/222; structural 8; diffs 82; code 35720; data 6904/6904; restored.
- VmStringSplit: empty-delimiter byte cursor derives from character index; 98.040540%; instructions 222/222; structural 0; diffs 66; code 35720; data 6904/6904; restored.
- VmBlobPackCommon: skip integer packing immediately when no elements remain; 97.634730%; instructions 670/668; structural 33; diffs 469; code 35720; data 6904/6904; restored.
- VmBlobPackCommon: integer elements use loop-tail continue into format parser; 97.934135%; instructions 668/668; structural 2; diffs 246; code 35720; data 6904/6904; restored.
- VmBlobPackCommon: integer pack loop uses explicitly tested do loop; 97.410180%; instructions 669/668; structural 35; diffs 468; code 35720; data 6904/6904; restored.
- VmBlobPackCommon: packing pass owns converted format and blob locals; 97.934135%; instructions 668/668; structural 2; diffs 246; code 35720; data 6904/6904; restored.
- VmBlobUnpack: decoded integer scoped to numeric unpack cases; 98.268860%; instructions 517/517; structural 0; diffs 156; code 35720; data 6904/6904; restored.
- VmBlobUnpack: counting pass owns index and cursor declarations; COMPILE FAIL; restored. d/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    5484:     u32 blobOff = srcBlob->offset;  #   Error:     ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- VmBlobUnpack: string trimming separates remaining characters from byte pointer; 97.949710%; instructions 516/517; structural 51; diffs 258; code 35720; data 6904/6904; restored.
- VmBlobUnpack: hex output indexes derive from source-byte iteration; 96.847200%; instructions 520/517; structural 55; diffs 227; code 35720; data 6904/6904; restored.
- CHANSVmAddExe: module clearing uses typed module array index; 99.153540%; instructions 254/254; structural 0; diffs 34; code 35720; data 6904/6904; restored.
- CHANSVmAddExe: range macro counters declared at each table boundary; COMPILE FAIL; restored. d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    6301:      { u32 cnt = header->nameCount; if (cnt) { u32 ofs = (u32) header-  #   Error:      ^ #   (10121) declaration syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- CHANSVmAddExe: name pointer cached beside dispatch entry validation; 97.559050%; instructions 254/254; structural 7; diffs 42; code 35720; data 6904/6904; restored.
- CHANSVmAddExe: table traversal uses while loop with explicit increment; 97.618110%; instructions 254/254; structural 8; diffs 42; code 35720; data 6904/6904; restored.
- CHANSVmLinkModules: global and native dispatch loops own separate index scopes; COMPILE FAIL; restored. .py build/43U/src/src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    6774:             u32 i;  #   Error:             ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- CHANSVmLinkModules: index-driven module loop uses for form; 98.677246%; instructions 189/189; structural 0; diffs 43; code 35720; data 6904/6904; restored.
- CHANSVmLinkModules: dispatch entry snapshots declared before nested index loop; COMPILE FAIL; restored. src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    6779:                     u8* addr;  #   Error:                     ^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- VmCallMethod: method table selection compares method count first; 98.024910%; instructions 281/281; structural 1; diffs 92; code 35720; data 6904/6904; restored.
- VmCallMethod: property selector derives method-null after set flag; 98.060500%; instructions 281/281; structural 0; diffs 91; code 35720; data 6904/6904; restored.
- VmCallMethod: return-frame size uses conditional scalar temporary; 98.060500%; instructions 281/281; structural 0; diffs 91; code 35720; data 6904/6904; restored.
- CHANSVmLinkModules: global and native loop indices have independent lifetimes; COMPILE FAIL; restored. NSVm.d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    6843:             for (i = 0; i < module->nameCount; i++) {  #   Error:                  ^ #   (10140) undefined identifier 'i' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- CHANSVmLinkModules: dispatch snapshot declared before module passes; COMPILE FAIL; restored. src/channelScript/CHANSVm.d build/43U/src/src/channelScript/CHANSVm.d ### mwcceppc.exe Compiler: #    File: src\channelScript\CHANSVm.c # ------------------------------------ #    6779:                     u8* addr;  #   Error:                     ^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- CHANSVmLinkModules: global address derived with pointer addition operand order; 98.677246%; instructions 189/189; structural 0; diffs 43; code 35720; data 6904/6904; restored.
- VmWinEmuWrite: aligned string length from inline payload accessor; 99.626870%; instructions 67/67; structural 0; diffs 5; code 35720; data 6904/6904; restored.
- VmWinEmuWrite: byte offset increment moved into for loop expression; 99.626870%; instructions 67/67; structural 0; diffs 5; code 35720; data 6904/6904; restored.
- VmWinEmuWrite: use byte length as signed nonnegative loop bound; 99.626870%; instructions 67/67; structural 0; diffs 5; code 35720; data 6904/6904; restored.
- CHANSVmParseInt: parser endpoint reset crosses an inline helper boundary; 94.693880%; instructions 49/49; structural 2; diffs 3; code 35720; data 6904/6904; restored.
- CHANSVmParseInt: typed object type loaded through inline helper; 94.693880%; instructions 49/49; structural 2; diffs 3; code 35720; data 6904/6904; restored.
- CHANSVmParseInt: base argument copied beside parser initialization; 94.693880%; instructions 49/49; structural 2; diffs 3; code 35720; data 6904/6904; restored.
- CHANSVmLinkModules: separate global/native indices while retaining local-function index; 98.677246%; instructions 189/189; structural 0; diffs 43; code 35720; data 6904/6904; restored.
- CHANSVmLinkModules: dispatch snapshots scoped before each index loop; 98.677246%; instructions 189/189; structural 0; diffs 43; code 35720; data 6904/6904; restored.
- CHANSVmLinkModules: snapshot declared across passes with address declaration first; 98.677246%; instructions 189/189; structural 0; diffs 43; code 35720; data 6904/6904; restored.
- CHANSVmStep: normalize zero step count with explicit conditional; 96.854750%; instructions 1254/1253; structural 66; diffs 1229; code 35720; data 2232/6904; restored.
- CHANSVmStep: pretested countdown loop and explicit zero normalization; 96.983240%; instructions 1255/1253; structural 63; diffs 1228; code 35720; data 2232/6904; restored.
- CHANSVmStep: result table accesses directly name constant fields; 96.308860%; instructions 1254/1253; structural 89; diffs 1094; code 35720; data 2232/6904; restored.
- CHANSVmStep: pretested countdown and direct result table fields; 96.772545%; instructions 1256/1253; structural 82; diffs 1231; code 35720; data 2232/6904; restored.
- CHANSVmStep: enumerated operand type addresses derive from index; 96.396645%; instructions 1254/1253; structural 75; diffs 1131; code 35720; data 2232/6904; restored.
- CHANSVmStep: operand type loads follow left then right source order; 96.452515%; instructions 1253/1253; structural 71; diffs 318; code 35720; data 6904/6904; restored.
- CHANSVmStep: conditional argument type declared at enumeration call; 96.452515%; instructions 1253/1253; structural 71; diffs 318; code 35720; data 6904/6904; restored.
- CHANSVmStep: direct tables, indexed enumeration, and pretested countdown combined; 96.604950%; instructions 1257/1253; structural 74; diffs 1220; code 35720; data 2232/6904; restored.

## Final audit

VmStringFromCharCode is the only retained source change: replace the redundant byte cursor with i * 2 and i * 2 + 1. It is 100.0% in objdiff, 59/59 instructions, ctxdiff diffs 0. All other experiments were restored, including the temporary reservation helper. That helper reached 99.843750% but retained three allocation-size register differences.
The completed source diff contains no added comments, assembly, data-placement changes, shared-header edits, compiler pragmas or uninitialized-value tricks. No configure.py changes were made.
Final full clean gate: PASS; exact 216/233 -> 217/233; code 35484/53564 -> 35720/53564; data 6904/6904 -> 6904/6904. Pools contain 125 identical strings. All 121 CHANSVmStep .data jump-table relocations are identical. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Regressions, forbidden patterns and readability warnings are zero.

Every remaining function has at least three compiling, distinct source-level attempts in this run. Failed compilations are excluded. The declaration-order searches add 120 NewObjData and 120 WinEmuWrite compiled permutations; JSON trial orders are in /tmp/chansvm-r7-decl-*.json.

CHANSVmGetSourceLine 97.826090%, module, entry, bitfield and line-offset registers; 46/46 instructions, structural 0, diffs 16; 5 distinct compiling source attempts.
CHANSVmNewObjData 99.583336%, seven chunk-index and table-slot register differences; 96/96 instructions, structural 0, diffs 7; 17 distinct compiling source attempts.
CHANSVmParseInt 94.693880%, three prologue positions schedule endpoint initialization after argument copies; 49/49 instructions, structural 2, diffs 3; 8 distinct compiling source attempts.
CHANSVm_8144B4D4 97.590360%, endpoint store and type comparison are scheduled in opposite order; 83/83 instructions, structural 2, diffs 2; 5 distinct compiling source attempts.
VmDateDtor 94.967030%, seven calendar table-load and variadic argument positions are scheduled differently; 91/91 instructions, structural 5, diffs 7; 5 distinct compiling source attempts.
VmStringReplace 97.878784%, source/search/replacement and traversal register allocation; 132/132 instructions, structural 0, diffs 40; 4 distinct compiling source attempts.
VmStringSplit 98.040540%, delimiter, cursor, array and element register allocation; 222/222 instructions, structural 0, diffs 66; 4 distinct compiling source attempts.
CHANSVm_8145049C 99.849190%, thirteen string-format payload and owner register differences; 431/431 instructions, structural 0, diffs 13; 3 distinct compiling source attempts.
VmBlobGetHexString 98.719510%, fourteen hex index, cursor and digit register differences; 82/82 instructions, structural 0, diffs 14; 7 distinct compiling source attempts.
VmBlobPackCommon 97.934135%, two branch destinations plus packing-state register allocation; 668/668 instructions, structural 2, diffs 246; 4 distinct compiling source attempts.
VmBlobUnpack 98.268860%, format, cursor and decoded-value register allocation; 517/517 instructions, structural 0, diffs 156; 3 distinct compiling source attempts.
VmWinEmuWrite 99.626870%, five converted-string and aligned-length register differences; 67/67 instructions, structural 0, diffs 5; 10 distinct compiling source attempts.
CHANSVmAddExe 99.153540%, module, size and relocation-loop register allocation; 254/254 instructions, structural 0, diffs 34; 3 distinct compiling source attempts.
CHANSVmLinkModules 98.677246%, module, dispatch and object-iterator register allocation; 189/189 instructions, structural 0, diffs 43; 5 distinct compiling source attempts.
VmCallMethod 98.060500%, call-frame, native target and property selector register allocation; 281/281 instructions, structural 0, diffs 91; 3 distinct compiling source attempts.
CHANSVmStep 96.452515%, countdown control flow, table-base addressing, operand-type spill and registers; 1253/1253 instructions, structural 71, diffs 318; 8 distinct compiling source attempts.

Disassembly note: disasm_fn.py stops at the first paired-single instruction in CHANSVmStep. Its complete target was read from build/43U/asm/src/channelScript/CHANSVm.s, and ctxdiff/declsearch compare all 1253 instructions. The compiler reason behind remaining register choices and scheduling is uncertain; the residual instruction differences are measured, not asserted impossible.
