# CHANSVm sol-low matching attempts

Baseline 699f8443: instruction-exact 216/233; code 35484/53564; data 6904/6904.
Pool identical, 125 strings; .data jump-table relocations must remain exact.

Initial CHANSVmGetSourceLine: 97.82609%; {'insns': '46/46', 'diffs': 16, 'structural': 0}
Initial CHANSVmNewObjData: 99.427086%; {'insns': '96/96', 'diffs': 10, 'structural': 0}
Initial CHANSVmParseInt: 94.69388%; {'insns': '49/49', 'diffs': 3, 'structural': 2}
Initial CHANSVm_8144B4D4: 97.59036%; {'insns': '83/83', 'diffs': 2, 'structural': 2}
Initial VmDateDtor: 94.96703%; {'insns': '91/91', 'diffs': 7, 'structural': 5}
Initial VmStringFromCharCode: 99.40678%; {'insns': '59/59', 'diffs': 6, 'structural': 0}
Initial VmStringReplace: 97.878784%; {'insns': '132/132', 'diffs': 40, 'structural': 0}
Initial VmStringSplit: 98.04054%; {'insns': '222/222', 'diffs': 66, 'structural': 0}
Initial CHANSVm_8145049C: 99.84919%; {'insns': '431/431', 'diffs': 13, 'structural': 0}
Initial VmBlobGetHexString: 98.71951%; {'insns': '82/82', 'diffs': 14, 'structural': 0}
Initial VmBlobPackCommon: 97.934135%; {'insns': '668/668', 'diffs': 246, 'structural': 2}
Initial VmBlobUnpack: 98.26886%; {'insns': '517/517', 'diffs': 156, 'structural': 0}
Initial VmWinEmuWrite: 99.62687%; {'insns': '67/67', 'diffs': 5, 'structural': 0}
Initial CHANSVmAddExe: 99.15354%; {'insns': '254/254', 'diffs': 34, 'structural': 0}
Initial CHANSVmLinkModules: 98.677246%; {'insns': '189/189', 'diffs': 43, 'structural': 0}
Initial VmCallMethod: 98.0605%; {'insns': '281/281', 'diffs': 91, 'structural': 0}
Initial CHANSVmStep: 96.452515%; {'insns': '1253/1253', 'diffs': 318, 'structural': 71}
- CHANSVmParseInt: initialize endpoint at declaration after cached type; 94.693880%; insns 49/49; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVmParseInt: declare endpoint and initialize before type load; 83.673470%; insns 49/49; structural 4; diffs 5; data 6904/6904; restored.
- CHANSVmParseInt: load type immediately before null endpoint assignment; 94.693880%; insns 49/49; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVmParseInt: assign endpoint within string-type condition; 94.693880%; insns 49/49; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVmParseInt: scope endpoint within converted string block; 82.244896%; insns 51/49; structural 10; diffs 41; data 6904/6904; restored.
- CHANSVm_8144B4D4: initialize floating parser endpoint at declaration; 97.590360%; insns 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVm_8144B4D4: float parser type loaded before endpoint in statements; 97.590360%; insns 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVm_8144B4D4: float parser endpoint assignment in type condition; 97.590360%; insns 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVm_8144B4D4: float parser endpoint initialized before type declaration; 95.180725%; insns 83/83; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVmNewObjData: allocation extent before chunk traversal index; 99.583336%; insns 96/96; structural 0; diffs 7; data 6904/6904; restored.
- CHANSVmNewObjData: chunk before traversal counters; 99.427086%; insns 96/96; structural 0; diffs 10; data 6904/6904; restored.
- CHANSVmNewObjData: chunk traversal index after union entry; 99.427086%; insns 96/96; structural 0; diffs 10; data 6904/6904; restored.
- VmWinEmuWrite: aligned byte length declared before string object; 99.179110%; insns 67/67; structural 0; diffs 8; data 6904/6904; restored.
- VmWinEmuWrite: aligned length before byte offset; 99.179110%; insns 67/67; structural 0; diffs 8; data 6904/6904; restored.
- VmWinEmuWrite: remaining byte length before string object; 99.626870%; insns 67/67; structural 0; diffs 5; data 6904/6904; restored.
- VmStringFromCharCode: character value declared before byte cursor; 99.152540%; insns 59/59; structural 0; diffs 9; data 6904/6904; restored.
- VmStringFromCharCode: byte cursor declared after character index; 98.728810%; insns 59/59; structural 0; diffs 12; data 6904/6904; restored.
- VmStringFromCharCode: character value declared after character index; 99.406780%; insns 59/59; structural 0; diffs 6; data 6904/6904; restored.
- CHANSVm_8145049C: shared character and string payload use typed pointers; COMPILE FAIL; restored.       ^ #   (10209) illegal implicit conversion from 'char *' to #   'unsigned char *' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- CHANSVm_8145049C: set shared string object before character buffer pointer; 99.350350%; insns 430/431; structural 25; diffs 142; data 2232/6904; restored.
- CHANSVm_8145049C: use separate source pointer for common string formatting; COMPILE FAIL; restored.       ^ #   (10209) illegal implicit conversion from 'char *' to #   'unsigned char *' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- VmDateDtor: cache month name before variadic argument setup; 94.967030%; insns 91/91; structural 5; diffs 7; data 6904/6904; restored.
- VmDateDtor: cache day then month names before formatting; 94.967030%; insns 91/91; structural 5; diffs 7; data 6904/6904; restored.
- VmDateDtor: cache month then day names before formatting; 94.967030%; insns 91/91; structural 5; diffs 7; data 6904/6904; restored.
- VmDateDtor: month table lookup through scoped pointer; 94.967030%; insns 91/91; structural 5; diffs 7; data 6904/6904; restored.
- VmDateDtor: cache year after month name lookup; 94.967030%; insns 91/91; structural 5; diffs 7; data 6904/6904; restored.
- CHANSVmParseInt: group parser endpoint and character buffer in typed workspace; 94.693880%; insns 49/49; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVm_8144B4D4: group float parser endpoint and buffer in typed workspace; 97.590360%; insns 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVmParseInt: type mismatch jumps to shared failure return; 94.693880%; insns 49/49; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVm_8144B4D4: float type mismatch jumps to shared failure return; 97.590360%; insns 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVm_8144B4D4: allow automatic parser inlining; 97.590360%; insns 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVmNewObjData: allocation extent before chunk traversal index; 99.583336%; insns 96/96; structural 0; diffs 7; data 6904/6904; retained.
- CHANSVmNewObjData: separate selected entry pointer from chunk index arithmetic; 97.187500%; insns 95/96; structural 7; diffs 59; data 6904/6904; restored.
- CHANSVmNewObjData: typed selected entry declared before counters; 97.187500%; insns 95/96; structural 7; diffs 59; data 6904/6904; restored.
- CHANSVmGetSourceLine: cache module before line table traversal; 97.826090%; insns 46/46; structural 0; diffs 16; data 6904/6904; restored.
- CHANSVmGetSourceLine: declare marker offset after bitfield pointer; 97.826090%; insns 46/46; structural 0; diffs 16; data 6904/6904; restored.
- CHANSVmGetSourceLine: cache low program-counter byte before line entry; 97.826090%; insns 46/46; structural 0; diffs 18; data 6904/6904; restored.
- CHANSVmGetSourceLine: traverse source markers with explicit while loop; 97.826090%; insns 46/46; structural 0; diffs 16; data 6904/6904; restored.
- VmStringFromCharCode: use named UTF16 mask declared before cursor; 99.406780%; insns 59/59; structural 0; diffs 6; data 6904/6904; restored.
- VmStringFromCharCode: scope byte cursor within allocated string block; 98.728810%; insns 59/59; structural 0; diffs 12; data 6904/6904; restored.
- VmStringFromCharCode: separate converted integer before truncation; 94.322040%; insns 57/59; structural 9; diffs 45; data 6904/6904; restored.
- VmWinEmuWrite: cache actual string payload for aligned length and conversion; 96.119400%; insns 65/67; structural 6; diffs 54; data 6904/6904; restored.
- VmWinEmuWrite: scope converted string within method body; 99.626870%; insns 67/67; structural 0; diffs 5; data 6904/6904; restored.
- VmStringReplace: search length declared ahead of parent length; 97.992424%; insns 132/132; structural 0; diffs 40; data 6904/6904; restored.
- VmStringReplace: declare output buffer ahead of source pointers; 96.818184%; insns 132/132; structural 0; diffs 61; data 6904/6904; restored.
- VmStringReplace: load search length before parent length; 97.992424%; insns 132/132; structural 0; diffs 40; data 6904/6904; restored.
- VmStringReplace: scope match pointer at comparison; 95.492424%; insns 132/132; structural 2; diffs 60; data 6904/6904; restored.
- VmStringSplit: delimited source length declared before source pointers; 97.927925%; insns 222/222; structural 0; diffs 69; data 6904/6904; restored.
- VmStringSplit: delimiter length before parent length; 97.927925%; insns 222/222; structural 0; diffs 69; data 6904/6904; restored.
- VmStringSplit: array declared after traversal counters; 98.063065%; insns 222/222; structural 0; diffs 68; data 6904/6904; restored.
- VmStringSplit: load delimiter pointer before parent pointer; 97.950450%; insns 222/222; structural 0; diffs 76; data 6904/6904; restored.
- VmBlobGetHexString: swap byte offset and character index declarations; 98.719510%; insns 82/82; structural 0; diffs 14; data 6904/6904; restored.
- VmBlobGetHexString: byte cursor initialized after hex character index; 98.719510%; insns 82/82; structural 0; diffs 14; data 6904/6904; restored.
- VmBlobGetHexString: cache first decoded nibble in word temporary; 98.719510%; insns 82/82; structural 0; diffs 14; data 6904/6904; restored.
- VmBlobGetHexString: loop counter declared before hex cursor; 98.719510%; insns 82/82; structural 0; diffs 14; data 6904/6904; restored.
- CHANSVmAddExe: source module declared after relocation counters; 99.035430%; insns 254/254; structural 0; diffs 39; data 6904/6904; restored.
- CHANSVmAddExe: executable size declared before module header; 99.035430%; insns 254/254; structural 0; diffs 39; data 6904/6904; restored.
- CHANSVmAddExe: counter before data bound; 99.153540%; insns 254/254; structural 0; diffs 34; data 6904/6904; restored.
- CHANSVmLinkModules: module declared after indices; 98.571430%; insns 189/189; structural 0; diffs 46; data 6904/6904; restored.
- CHANSVmLinkModules: global iterator before dispatch table; 98.677246%; insns 189/189; structural 0; diffs 43; data 6904/6904; restored.
- CHANSVmLinkModules: scope dispatch index within module loop; 98.677246%; insns 189/189; structural 0; diffs 43; data 6904/6904; restored.
- VmCallMethod: split frame push bounds into separate declarations; 98.060500%; insns 281/281; structural 0; diffs 91; data 6904/6904; restored.
- VmCallMethod: return value declared after native method target; 98.060500%; insns 281/281; structural 0; diffs 91; data 6904/6904; restored.
- VmCallMethod: instruction pointer declared ahead of frame metadata; 97.829180%; insns 281/281; structural 0; diffs 103; data 6904/6904; restored.
- VmBlobPackCommon: format position declared before input format; 97.934135%; insns 668/668; structural 2; diffs 246; data 6904/6904; restored.
- VmBlobPackCommon: argument array ahead of source format metadata; 97.934135%; insns 668/668; structural 2; diffs 246; data 6904/6904; restored.
- VmBlobPackCommon: reset element width before next-position output; 97.898200%; insns 668/668; structural 24; diffs 268; data 6904/6904; restored.
- VmBlobUnpack: format position before format string metadata; 98.268860%; insns 517/517; structural 0; diffs 156; data 6904/6904; restored.
- VmBlobUnpack: argument count ahead of blob cursor; 98.268860%; insns 517/517; structural 0; diffs 156; data 6904/6904; restored.
- VmBlobUnpack: signed unpacked integer declared ahead of loop counters; 98.268860%; insns 517/517; structural 0; diffs 156; data 6904/6904; restored.
- CHANSVm_8145049C: typed common string data and owned temporary object; 99.187935%; insns 431/431; structural 0; diffs 53; data 6904/6904; restored.
- CHANSVm_8145049C: separate common string data from escape flag; 99.187935%; insns 431/431; structural 0; diffs 53; data 6904/6904; restored.
- CHANSVm_8145049C: temporary string length scoped beside its owned object; 99.849190%; insns 431/431; structural 0; diffs 13; data 6904/6904; restored.
- CHANSVmNewObjData: name chunk table slot before allocator call; 99.583336%; insns 96/96; structural 0; diffs 7; data 6904/6904; restored.
- CHANSVmNewObjData: chunk table slot declared before chunk counter; 99.583336%; insns 96/96; structural 0; diffs 7; data 6904/6904; restored.
- CHANSVmNewObjData: byte table position replaces indexed chunk lookup; exploratory variant, fully restored; 99.583336%; insns 96/96; structural 0; diffs 7; data 6904/6904; restored.
- CHANSVmNewObjData: increment byte offset before chunk number; 99.583336%; insns 96/96; structural 0; diffs 7; data 6904/6904; restored.
- VmStringFromCharCode: mask unsigned integer before explicit null fallback; 93.644066%; insns 56/59; structural 9; diffs 45; data 6904/6904; restored.
- VmStringFromCharCode: apply unsigned character mask before width cast; 94.322040%; insns 57/59; structural 9; diffs 45; data 6904/6904; restored.
- VmStringFromCharCode: signed byte cursor with unsigned loop index; 99.406780%; insns 59/59; structural 0; diffs 6; data 6904/6904; restored.
- VmStringFromCharCode: promote mask to integer arithmetic width; 99.406780%; insns 59/59; structural 0; diffs 6; data 6904/6904; restored.
- VmWinEmuWrite: scope aligned total length within validated string block; COMPILE FAIL; restored. :         u32 totalLength;  #   Error:         ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- VmWinEmuWrite: fetch string before declaring loop metadata; 99.626870%; insns 67/67; structural 0; diffs 5; data 6904/6904; restored.
- CHANSVmGetSourceLine: explicit module/table/pc locals with shared failure return; 96.847824%; insns 46/46; structural 0; diffs 21; data 6904/6904; restored.
- CHANSVmStep: explicit zero step-count normalization; 96.854750%; insns 1254/1253; structural 66; diffs 1229; data 2232/6904; restored.
- CHANSVmStep: pre-tested interpreter countdown; 96.416600%; insns 1254/1253; structural 68; diffs 1238; data 2232/6904; restored.
- CHANSVmStep: direct typed result-table references; 96.308860%; insns 1254/1253; structural 89; diffs 1094; data 2232/6904; restored.
- CHANSVmStep: normalize count and pre-test interpreter loop; 96.983240%; insns 1255/1253; structural 63; diffs 1228; data 2232/6904; restored.
- CHANSVmStep: pre-tested loop with direct result table references; 96.772545%; insns 1256/1253; structural 82; diffs 1231; data 2232/6904; restored.
- CHANSVmStep: index typed operand workspace instead of carrying pointer; 96.388664%; insns 1254/1253; structural 75; diffs 1131; data 2232/6904; restored.
- CHANSVmStep: normalize pre-tested loop and index operand workspace; 96.596970%; insns 1257/1253; structural 74; diffs 1220; data 2232/6904; restored.
- CHANSVmParseInt: test type field directly after parse-end initialization; 83.673470%; insns 49/49; structural 4; diffs 5; data 6904/6904; restored.
- CHANSVmParseInt: initialize parse endpoint through pointer to local; 94.693880%; insns 49/49; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVmParseInt: assign parse-end null after computing string predicate; COMPILE FAIL; restored.               ^ #   (10393) 'isString' is not a member of class 'struct CHANSVmObjHdr' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- CHANSVm_8144B4D4: test type field directly after parse-end initialization; 95.180725%; insns 83/83; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVm_8144B4D4: initialize parse endpoint through pointer to local; 97.590360%; insns 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVm_8144B4D4: assign parse-end null after computing string predicate; COMPILE FAIL; restored.               ^ #   (10393) 'isString' is not a member of class 'struct CHANSVmObjHdr' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
- CHANSVmNewObjData: scope chunk scan state below fast-path lookup; 99.583336%; insns 96/96; structural 0; diffs 7; data 6904/6904; restored.
- CHANSVmNewObjData: express table scan with a for loop; 99.583336%; insns 96/96; structural 0; diffs 7; data 6904/6904; restored.
- CHANSVmNewObjData: outer allocation extent scoped only around allocation; 99.427086%; insns 96/96; structural 0; diffs 10; data 6904/6904; restored.
- VmStringFromCharCode: cast masked value through signed integer; 99.406780%; insns 59/59; structural 0; diffs 6; data 6904/6904; restored.
- VmStringFromCharCode: use unsigned mask on signed low-word value; 99.406780%; insns 59/59; structural 0; diffs 6; data 6904/6904; restored.
- VmStringFromCharCode: byte cursor before converted argument pointer; 99.406780%; insns 59/59; structural 0; diffs 6; data 6904/6904; restored.
- VmWinEmuWrite: declare string inside a block containing all processing; 99.626870%; insns 67/67; structural 0; diffs 5; data 6904/6904; restored.
- VmWinEmuWrite: alignment explicitly performed in signed word arithmetic; 99.626870%; insns 67/67; structural 0; diffs 5; data 6904/6904; restored.
- VmWinEmuWrite: preserve byte count then align total length; 99.477615%; insns 67/67; structural 0; diffs 6; data 6904/6904; restored.
- VmStringFromCharCode: helper for UTF16 truncation of non-null integer; 99.406780%; insns 59/59; structural 0; diffs 6; data 6904/6904; restored.
- VmStringFromCharCode: helper for nullable character argument; 86.016950%; insns 52/59; structural 13; diffs 44; data 6904/6904; restored.
- VmStringFromCharCode: early-return nullable character helper; 92.457630%; insns 59/59; structural 5; diffs 11; data 6904/6904; restored.
- VmWinEmuWrite: inline helper for aligned string byte length; 99.626870%; insns 67/67; structural 0; diffs 5; data 6904/6904; restored.
- VmWinEmuWrite: inline helper for argument conversion before processing; 99.626870%; insns 67/67; structural 0; diffs 5; data 6904/6904; restored.
- CHANSVmNewObjData: separate byte-table cursor and selected entry lifetimes; 97.656250%; insns 97/96; structural 6; diffs 74; data 6904/6904; restored.
- CHANSVmNewObjData: store selected chunk through header data pointer; 99.583336%; insns 96/96; structural 0; diffs 7; data 6904/6904; restored.
- CHANSVmParseInt: inline parser initializer combines type load and endpoint reset; 94.693880%; insns 49/49; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVmParseInt: inline parser initializer returns string predicate; 94.693880%; insns 49/49; structural 2; diffs 3; data 6904/6904; restored.
- CHANSVm_8144B4D4: inline parser initializer combines type load and endpoint reset; 97.590360%; insns 83/83; structural 2; diffs 2; data 6904/6904; restored.
- CHANSVm_8144B4D4: inline parser initializer returns string predicate; 97.590360%; insns 83/83; structural 2; diffs 2; data 6904/6904; restored.
- VmDateDtor: inline calendar name lookup month; 94.967030%; insns 91/91; structural 5; diffs 7; data 6904/6904; restored.
- VmDateDtor: inline calendar name lookup day; 94.967030%; insns 91/91; structural 5; diffs 7; data 6904/6904; restored.
- VmDateDtor: inline calendar name lookup both; 94.967030%; insns 91/91; structural 5; diffs 7; data 6904/6904; restored.

Declaration search: CHANSVm_8145049C, 300 compiled permutations, best structural/exact 0/13; source restored.

The clean gate checks byte matching, regressions, pool, source patterns and DOL integrity. Its PASS alone does not imply that the requested exact-count increase was achieved.

## Final clean-build measurements

Instruction-exact 216/233 -> 216/233; matched code 35484/53564 -> 35484/53564; matched data 6904/6904 -> 6904/6904.
CHANSVmNewObjData 99.427086% -> 99.583336%, 10 -> 7 instruction differences, source commit f07fd85c.
The requested exact-count increase was not achieved. Remaining compiler/source tie-break causes are unresolved.
Fresh .data audit: all 121 CHANSVmStep jump-table relocation offsets, types and function-relative destinations match. No linking/configuration changes.

| Open function | Objdiff % | Instructions | Structural / positional diffs | Compiled attempts | Remaining difference |
|---|---:|---|---|---:|---|
| CHANSVmGetSourceLine | 97.82609 | 46/46 | 0 / 16 | 5 | module, marker and line-offset register allocation |
| CHANSVmNewObjData | 99.583336 | 96/96 | 0 / 7 | 15 | chunk counter and table-slot registers are swapped; 7 differing instructions |
| CHANSVmParseInt | 94.69388 | 49/49 | 2 / 3 | 11 | parse-end store follows parameter copies; 3 scheduling differences |
| CHANSVm_8144B4D4 | 97.59036 | 83/83 | 2 / 2 | 11 | parse-end store follows type comparison; 2 scheduling differences |
| VmDateDtor | 94.96703 | 91/91 | 5 / 7 | 8 | month/day table loads and variadic argument setup; 7 scheduling differences |
| VmStringFromCharCode | 99.40678 | 59/59 | 0 / 6 | 16 | UTF16 mask and byte-cursor registers are swapped |
| VmStringReplace | 97.878784 | 132/132 | 0 / 40 | 4 | argument, string pointer and traversal register allocation |
| VmStringSplit | 98.04054 | 222/222 | 0 / 66 | 4 | delimiter, array and traversal register allocation |
| CHANSVm_8145049C | 99.84919 | 431/431 | 0 / 13 | 4 | string pointer and temporary object/length register coalescing |
| VmBlobGetHexString | 98.71951 | 82/82 | 0 / 14 | 4 | hex index, byte cursor and digit register allocation |
| VmBlobPackCommon | 97.934135 | 668/668 | 2 / 246 | 3 | two branch targets and pack-state register allocation |
| VmBlobUnpack | 98.26886 | 517/517 | 0 / 156 | 3 | format, cursor and decoded-value register allocation |
| VmWinEmuWrite | 99.62687 | 67/67 | 0 / 5 | 11 | converted string and aligned byte-length registers are swapped |
| CHANSVmAddExe | 99.15354 | 254/254 | 0 / 34 | 3 | module, size and relocation-loop register allocation |
| CHANSVmLinkModules | 98.677246 | 189/189 | 0 / 43 | 3 | module, dispatch index and native/global iterator registers |
| VmCallMethod | 98.0605 | 281/281 | 0 / 91 | 3 | call-frame and native target register allocation |
| CHANSVmStep | 96.452515 | 1253/1253 | 71 / 318 | 7 | entry/countdown flow, constant table base, operand-type spills and registers |

The declaration search added 300 compiled formatter permutations beyond the per-function attempt counts above. Failed compilations are excluded. The single byte-offset lookup experiment was fully restored. All final source changes are the two declaration positions in CHANSVmNewObjData.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 35484/53564 data 6904/6904 functions 216/233 fuzzy 99.2732 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 216/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.27317
[src/channelScript/CHANSVm]   below 100: CHANSVmGetSourceLine 97.82609
[src/channelScript/CHANSVm]   below 100: CHANSVmNewObjData 99.583336
[src/channelScript/CHANSVm]   below 100: CHANSVmParseInt 94.69388
[src/channelScript/CHANSVm]   below 100: CHANSVm_8144B4D4 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringFromCharCode 99.40678
[src/channelScript/CHANSVm]   below 100: VmStringReplace 97.878784
[src/channelScript/CHANSVm]   below 100: VmStringSplit 98.04054
[src/channelScript/CHANSVm]   below 100: CHANSVm_8145049C 99.84919
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 97.934135
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 98.26886
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmAddExe 99.15354
[src/channelScript/CHANSVm]   below 100: CHANSVmLinkModules 98.677246
[src/channelScript/CHANSVm]   below 100: VmCallMethod 98.0605
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.452515
[src/channelScript/CHANSVm] baseline: code 35484/53564 data 6904 functions 216 fuzzy 99.2720
regressions vs baseline: 0
global matched_code_percent: 86.76230 -> 86.76230
global fuzzy_match_percent: 99.31232 -> 99.31234
global complete_code_percent: 60.61288 -> 60.61288
global matched_data_percent: 91.11031 -> 91.11031
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
