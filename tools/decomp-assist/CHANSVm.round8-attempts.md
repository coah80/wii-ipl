# CHANSVm round 8 attempts

Scope CHANSVm.c only; 43U matching, no link classification changes.
Unslop writing pass applied.
Baseline HEAD 0c554a16: instruction-exact 217/233; code 35720/53564; data 6904/6904.
Initial pool identical, 125 strings; .data 4672 bytes and 121 jump-table relocations 100%.
Default gate cannot find baseline-0c554a16.json. Nearest existing immutable ancestor baseline is f00336cc; gates use --base f00336cc and compare retained improvements separately against the fresh initial report.

Initial CHANSVmGetSourceLine: 97.826090%; instructions 46/46; structural 0; positional diffs 16.
Initial CHANSVmNewObjData: 99.583336%; instructions 96/96; structural 0; positional diffs 7.
Initial CHANSVmParseInt: 94.693880%; instructions 49/49; structural 2; positional diffs 3.
Initial CHANSVm_8144B4D4: 97.590360%; instructions 83/83; structural 2; positional diffs 2.
Initial VmDateDtor: 94.967030%; instructions 91/91; structural 5; positional diffs 7.
Initial VmStringReplace: 97.878784%; instructions 132/132; structural 0; positional diffs 40.
Initial VmStringSplit: 98.040540%; instructions 222/222; structural 0; positional diffs 66.
Initial CHANSVm_8145049C: 99.849190%; instructions 431/431; structural 0; positional diffs 13.
Initial VmBlobGetHexString: 98.719510%; instructions 82/82; structural 0; positional diffs 14.
Initial VmBlobPackCommon: 97.934135%; instructions 668/668; structural 2; positional diffs 246.
Initial VmBlobUnpack: 98.268860%; instructions 517/517; structural 0; positional diffs 156.
Initial VmWinEmuWrite: 99.626870%; instructions 67/67; structural 0; positional diffs 5.
Initial CHANSVmAddExe: 99.153540%; instructions 254/254; structural 0; positional diffs 34.
Initial CHANSVmLinkModules: 98.677246%; instructions 189/189; structural 0; positional diffs 43.
Initial VmCallMethod: 98.060500%; instructions 281/281; structural 0; positional diffs 91.
Initial CHANSVmStep: 96.452515%; instructions 1253/1253; structural 71; positional diffs 318.
- CHANSVm_8145049C: separate typed string payload from escaped flag and format count; 99.187935%; instructions 431/431; structural 0; diffs 53; data 6904/6904; regressions 0; restored.
- CHANSVm_8145049C: separate temporary string owner from literal byte length; 99.849190%; instructions 431/431; structural 0; diffs 13; data 6904/6904; regressions 0; restored.
- CHANSVm_8145049C: separate typed string payload and owner lifetimes; 99.187935%; instructions 431/431; structural 0; diffs 53; data 6904/6904; regressions 0; restored.
Diagnosis CHANSVmNewObjData: target/source frame 0x30, 96 instructions; branch graph and operand order identical. Only compiler-generated chunk-table slot r25/r26 and chunk counter r26/r25 are exchanged. Tried source boundaries before allocation coloring.
- CHANSVmNewObjData: signed chunk ordinal with unsigned bounds; 99.583336%; instructions 96/96; structural 0; diffs 7; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: explicit typed chunk-table slot lifetime; 99.583336%; instructions 96/96; structural 0; diffs 7; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: table-slot pointer plus offset initialized before ordinal; 99.583336%; instructions 96/96; structural 0; diffs 7; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: inline reservation owns scan and selected-entry lifetime; 99.843750%; instructions 96/96; structural 0; diffs 3; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: inline reservation and aligned size declared after selected entry; 99.843750%; instructions 96/96; structural 0; diffs 3; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: inline reservation aligned allocation scoped beside payload; 99.843750%; instructions 96/96; structural 0; diffs 3; data 6904/6904; regressions 0; restored.
Diagnosis CHANSVm_8145049C: frame 0xe0, all 431 instructions and control flow match. Thirteen differences exchange the temporary string payload/length and object-owner registers only, beginning at char_body. Inner declaration lifetimes are the next lever.
- CHANSVm_8145049C: temporary string owner declared before temporary string length; 99.849190%; instructions 431/431; structural 0; diffs 13; data 6904/6904; regressions 0; restored.
- CHANSVm_8145049C: temporary string owner declared beside temporary string length; 99.849190%; instructions 431/431; structural 0; diffs 13; data 6904/6904; regressions 0; restored.
- CHANSVm_8145049C: payload result declared before literal length and nested owner before size; 99.756380%; instructions 431/431; structural 0; diffs 21; data 6904/6904; regressions 0; restored.
Diagnosis VmWinEmuWrite: frame 0xb0 and 67 instructions agree; branch and operand forms agree. Converted object r27 and aligned length r29 target are r29/r27 in source; five register differences. Tried typed argument/converted-owner reuse and branch ownership.
- VmWinEmuWrite: raw argument and converted string share object lifetime; 99.626870%; instructions 67/67; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- VmWinEmuWrite: converted string reuses the unused receiver parameter; 99.626870%; instructions 67/67; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- VmWinEmuWrite: converted string reuses the unused return-header parameter; 99.626870%; instructions 67/67; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- VmWinEmuWrite: conversion lengths declared before the conversion buffer; 99.552240%; instructions 67/67; structural 5; diffs 10; data 6904/6904; regressions 0; restored.
- VmWinEmuWrite: raw argument gets an independent typed temporary; 99.626870%; instructions 67/67; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: reservation and payload allocation have separate inline boundaries; 94.895836%; instructions 100/96; structural 8; diffs 88; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: payload helper receives selected entry before header; 94.895836%; instructions 100/96; structural 8; diffs 88; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: payload helper receives requested size before selected entry; 94.895836%; instructions 100/96; structural 8; diffs 88; data 6904/6904; regressions 0; restored.
Diagnosis CHANSVmParseInt: frame 0x70 and 49 instructions match; first type load matches, but endpoint zero store occurs three slots too late after base/output argument copies. CHANSVm_8144B4D4 has the same parser initialization issue inlined, with two adjacent endpoint-store/type-compare slots exchanged.
- CHANSVmParseInt: whole inline parser boundary, argument order obj, out, base; 94.693880%; instructions 49/49; structural 2; diffs 3; data 6904/6904; regressions 0; restored.
- CHANSVmParseInt: whole inline parser boundary, argument order base, obj, out; 94.693880%; instructions 49/49; structural 2; diffs 3; data 6904/6904; regressions 0; restored.
- CHANSVmParseInt: whole inline parser boundary, argument order out, obj, base; 94.693880%; instructions 49/49; structural 2; diffs 3; data 6904/6904; regressions 0; restored.
- CHANSVm_8144B4D4: parser endpoint initialized through const-qualified local pointer; 97.590360%; instructions 83/83; structural 2; diffs 2; data 6904/6904; regressions 0; restored.
- CHANSVm_8144B4D4: parser keyword conversion uses explicit success predicate; 97.590360%; instructions 83/83; structural 2; diffs 2; data 6904/6904; regressions 0; restored.
- CHANSVm_8144B4D4: parser result has scoped null-output handling; 95.060240%; instructions 85/83; structural 10; diffs 24; data 6904/6904; regressions 0; restored.
Diagnosis CHANSVmGetSourceLine: leaf frame, 46/46 instructions and normalized structure identical. Module, entry-offset, low PC byte, bitfield and line offset registers differ. Explicit named module and local declaration order are tested after verifying branch/operand forms.
- CHANSVmGetSourceLine: name the module loaded in the validation condition; 97.826090%; instructions 46/46; structural 0; diffs 16; data 6904/6904; regressions 0; restored.
- CHANSVmGetSourceLine: name the low program-counter byte before line-entry traversal; 97.391304%; instructions 46/46; structural 0; diffs 20; data 6904/6904; regressions 0; restored.
- CHANSVmGetSourceLine: loop index initialized only in its loop initializer; 97.826090%; instructions 46/46; structural 0; diffs 16; data 6904/6904; regressions 0; restored.
- CHANSVmGetSourceLine: named module and program-counter byte lifetimes; 97.391304%; instructions 46/46; structural 0; diffs 20; data 6904/6904; regressions 0; restored.
- CHANSVmGetSourceLine: inner declaration order lineOffset,i,bitfield; 97.282610%; instructions 46/46; structural 0; diffs 20; data 6904/6904; regressions 0; restored.
- CHANSVmGetSourceLine: inner declaration order bitfield,lineOffset,i; 97.826090%; instructions 46/46; structural 0; diffs 16; data 6904/6904; regressions 0; restored.
- CHANSVmGetSourceLine: inner declaration order bitfield,i,lineOffset; 97.826090%; instructions 46/46; structural 0; diffs 16; data 6904/6904; regressions 0; restored.
- CHANSVmGetSourceLine: inner declaration order i,lineOffset,bitfield; 97.282610%; instructions 46/46; structural 0; diffs 20; data 6904/6904; regressions 0; restored.
- CHANSVmGetSourceLine: inner declaration order i,bitfield,lineOffset; 97.282610%; instructions 46/46; structural 0; diffs 20; data 6904/6904; regressions 0; restored.
- CHANSVmParseInt: single-case object-type switch; 89.591835%; instructions 50/49; structural 6; diffs 43; data 6904/6904; regressions 0; restored.
- CHANSVmParseInt: object-type predicate computed before endpoint reset; 87.551020%; instructions 51/49; structural 7; diffs 45; data 6904/6904; regressions 0; restored.
- CHANSVmParseInt: parser endpoint lifetime inside parsing scope; 94.693880%; instructions 49/49; structural 2; diffs 3; data 6904/6904; regressions 0; restored.
- CHANSVm_8144B4D4: single-case object-type switch; 96.265060%; instructions 84/83; structural 4; diffs 69; data 6904/6904; regressions 0; restored.
- CHANSVm_8144B4D4: object-type predicate computed before endpoint reset; 94.939760%; instructions 85/83; structural 5; diffs 74; data 6904/6904; regressions 0; restored.
- CHANSVm_8144B4D4: parser endpoint lifetime inside parsing scope; 97.590360%; instructions 83/83; structural 2; diffs 2; data 6904/6904; regressions 0; restored.
Diagnosis VmBlobGetHexString: frame 0x20, 82/82 instructions, structural 0. Fourteen differences exchange character index, generated byte cursor and digit registers. Data/pool identical. Trial declarations, digit temporaries and loop operand forms.
- VmBlobGetHexString: declare character index before output index; 98.719510%; instructions 82/82; structural 0; diffs 14; data 6904/6904; regressions 0; restored.
- VmBlobGetHexString: explicit signed digit temporary before low-digit index; 98.719510%; instructions 82/82; structural 0; diffs 14; data 6904/6904; regressions 0; restored.
- VmBlobGetHexString: explicit signed digit temporary after low-digit index; 98.719510%; instructions 82/82; structural 0; diffs 14; data 6904/6904; regressions 0; restored.
- VmBlobGetHexString: source byte advancement in the low-digit expression; 98.719510%; instructions 82/82; structural 0; diffs 14; data 6904/6904; regressions 0; restored.
- VmBlobGetHexString: initialize character index immediately before traversal; 98.719510%; instructions 82/82; structural 0; diffs 14; data 6904/6904; regressions 0; restored.
Diagnosis VmStringReplace: frame 0x40, 132/132 instructions, structural 0. VM/return, conversion result, source/search/replacement strings and traversal registers differ; branch and operand forms already agree. Source ownership and declaration order are the tested class.
- VmStringReplace: declare traversal lengths before all source pointers; 97.878784%; instructions 132/132; structural 0; diffs 40; data 6904/6904; regressions 0; restored.
- VmStringReplace: declare search and replacement extents before traversal offsets; 97.803030%; instructions 132/132; structural 0; diffs 43; data 6904/6904; regressions 0; restored.
- VmStringReplace: explicit typed string payload owners for length and pointer loads; 97.878784%; instructions 132/132; structural 0; diffs 40; data 6904/6904; regressions 0; restored.
Diagnosis CHANSVmAddExe: frame and 254/254 instruction count match. Mostly module/context and loop-cursor registers; target also reverses addition operands for module end and native method name. Those operand forms are corrected before register search.
- CHANSVmAddExe: module-end and native-name addition follow target operand order; 99.232285%; instructions 254/254; structural 0; diffs 32; data 6904/6904; regressions 0; restored.
- CHANSVmAddExe: executable type copied before module-header read; 99.153540%; instructions 254/254; structural 0; diffs 34; data 6904/6904; regressions 0; restored.
- CHANSVmAddExe: table cursors declared before their traversal counters; 99.547240%; instructions 254/254; structural 0; diffs 18; data 6904/6904; regressions 0; restored.
- CHANSVmAddExe: target addition forms with cursors declared first; 99.625984%; instructions 254/254; structural 0; diffs 16; data 6904/6904; regressions 0; restored.
- CHANSVm_8145049C: record temporary owner before copying its payload; 96.925750%; instructions 431/431; structural 3; diffs 150; data 6904/6904; regressions 0; restored.
- CHANSVm_8145049C: record temporary owner before both character and string payloads; 96.426910%; instructions 430/431; structural 28; diffs 249; data 2232/6904; regressions 0; restored.
- CHANSVm_8145049C: literal extent reused for converted string length; 99.849190%; instructions 431/431; structural 0; diffs 13; data 6904/6904; regressions 0; restored.
- CHANSVm_8145049C: temporary owner is the direct allocation result; 97.389790%; instructions 431/431; structural 0; diffs 147; data 6904/6904; regressions 0; restored.
- CHANSVmAddExe: module header initialized in its declaration after cursor and operand fixes; 99.625984%; instructions 254/254; structural 0; diffs 16; data 6904/6904; regressions 0; restored.
- CHANSVmAddExe: module header declared after header and region extents after cursor and operand fixes; 99.507870%; instructions 254/254; structural 0; diffs 21; data 6904/6904; regressions 0; restored.
- CHANSVmAddExe: module size cached immediately at declaration after cursor and operand fixes; 99.625984%; instructions 254/254; structural 0; diffs 16; data 6904/6904; regressions 0; restored.
CHANSVmAddExe declaration-order search: declaration block: |       CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm; |       ModuleHeader* mod; |       CHANSVmModule* header; |       u32 maxEnd; |       u32 size; |       u32 cnt; |       u32 ofs; | start (0, 16) | best (0, 16) after 52 builds; source restored; best order was: |     CHANSVmPrivate* pVm = (CHANSVmPrivate*)vm; |     ModuleHeader* mod; |     CHANSVmModule* header; |     u32 maxEnd; |     u32 size; |     u32 cnt; |     u32 ofs; | 
Retained CHANSVmAddExe: 99.153540 -> 99.625984%, 34 -> 16 differing instructions; 254/254 instructions; .data and all data sections 100%. Full clean gate --base f00336cc PASS, regressions/forbidden/readability 0, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Exact count remains 217/233; this is a measured fuzzy improvement only.
Diagnosis VmDateDtor: frame 0x70 and 91/91 instructions match. Seven scheduling differences load weekday table before month table and place the year stack argument earlier than target. Month-first preparation, typed indexes and calendar helper boundary are tested.
- VmDateDtor: month-name lookup evaluated before weekday-name lookup; 94.967030%; instructions 91/91; structural 5; diffs 7; data 6904/6904; regressions 0; restored.
- VmDateDtor: year stack argument captured before the variadic call; 94.967030%; instructions 91/91; structural 5; diffs 7; data 6904/6904; regressions 0; restored.
- VmDateDtor: month and weekday table bases have explicit typed temporaries; 94.967030%; instructions 91/91; structural 5; diffs 7; data 6904/6904; regressions 0; restored.
Diagnosis VmStringSplit: target/source 222 instructions and normalized structure agree. Remaining differences are delimiter/limit, source/delimiter lengths, array ownership and traversal register allocation. Typed owner scopes and initialized array creation order are tested.
- VmStringSplit: parent and delimiter payloads get named typed owners; 98.040540%; instructions 222/222; structural 0; diffs 66; data 6904/6904; regressions 0; restored.
- VmStringSplit: optional limit conversion object scoped to the limit block; 98.040540%; instructions 222/222; structural 0; diffs 66; data 6904/6904; regressions 0; restored.
- VmStringSplit: result array starts null at its declaration; 96.666664%; instructions 222/222; structural 7; diffs 93; data 6904/6904; regressions 0; restored.
- VmStringSplit: delimiter and source extents declared before their pointers; 98.040540%; instructions 222/222; structural 0; diffs 66; data 6904/6904; regressions 0; restored.
Diagnosis VmCallMethod: frame 0x50 and 281/281 instructions agree. The target keeps the method/property selector in caller register r5 after memset and initializes the eventual callback pointer in r28 at entry. Source reuses retVal for both selector and error status across memset, holding it in r30, and leaves funcPtr uninitialized. Separate selector/error lifetimes and callback initialization are the structural-temporary class to test first.
- VmCallMethod: method/property selector has separate lifetime from call error status; 98.060500%; instructions 281/281; structural 0; diffs 91; data 6904/6904; regressions 0; restored.
- VmCallMethod: initialize callback pointer and delay selector initialization until after scratch clear; 98.113880%; instructions 282/281; structural 12; diffs 226; data 6904/6904; regressions 0; restored.
- VmCallMethod: selector reuses decoded operand, function calls explicitly select zero; 98.896800%; instructions 281/281; structural 0; diffs 54; data 6904/6904; regressions 0; restored.
Diagnosis VmCallMethod: frame 0x50 and 281/281 instructions agree. The target keeps the method/property selector in caller register r5 after memset and initializes the eventual callback pointer in r28 at entry. Source reuses retVal for both selector and error status across memset, holding it in r30, and leaves funcPtr uninitialized. Separate selector/error lifetimes and callback initialization are the structural-temporary class to test first.
- VmCallMethod: instruction and next-PC declared before callback and native target; 99.697510%; instructions 281/281; structural 0; diffs 14; data 6904/6904; regressions 0; restored.
- VmCallMethod: target lifetime order with selector-first comparisons and property flag order; 99.768684%; instructions 281/281; structural 0; diffs 12; data 6904/6904; regressions 0; restored.
- VmCallMethod: target lifetime order with explicit PC/module owners; 99.893240%; instructions 281/281; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- VmCallMethod: property null selector initialized before set flag; 99.893240%; instructions 281/281; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- VmCallMethod: set-property predicate has a named operation offset; 99.893240%; instructions 281/281; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- VmCallMethod: set-property predicate assigned after property-list lookup; 99.893240%; instructions 281/281; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- VmCallMethod: null-selector predicate assigned after push-depth selection; 100.000000%; instructions 281/281; structural 0; diffs 0; data 6904/6904; regressions 0; restored.
- VmCallMethod: inline property-mode predicate; 99.893240%; instructions 281/281; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- VmCallMethod: inline null-method predicate; 99.893240%; instructions 281/281; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
- VmCallMethod: inline mode classifier sets both property flags; 99.893240%; instructions 281/281; structural 0; diffs 5; data 6904/6904; regressions 0; restored.
VmCallMethod exact candidate: separate decoded method selector from call-status return, initialize callback to null at entry, retain native target on function mode as the target assembly does, declare instruction/PC/callback before native target, name PC/module owners, compare selector before table index, and compute null-method flag after selecting pushDepth. No artificial/uninitialized values. 281/281 instructions, ctxdiff diffs 0, objdiff 100.0%, data 6904/6904; pending full clean gate.
VmCallMethod source review removed two dead selector assignments introduced by broad trial replacements, including one after a later scratch memset. Rebuild remains 100.0% and ctxdiff diffs 0; final source uses only live selector initialization and callbacks are initialized.
Accepted VmCallMethod after fresh reviewed full gate: GATE PASS, instruction-exact 217 -> 218 / 233, matched code 35720 -> 36844 / 53564, data 6904/6904 including .data 100%, pool identical. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; regressions 0; forbidden patterns 0; readability warnings 0. Function objdiff 100%, 281/281 instructions and diffs 0.
Diagnosis CHANSVmLinkModules: target frame 0x40 and 189/189 instructions agree; only module/dispatch/global/native traversal registers differ. Target gives module r23, global dispatch r25/global node r26/index r27, then native dispatch r27/native node r26/index r25. Source shares one dispatch and one index across both passes; test distinct pass-local ownership before register permutations.
- CHANSVmLinkModules: global and native dispatch tables have independent lifetimes; 98.597885%; instructions 189/189; structural 0; diffs 45; data 6904/6904; regressions 0; restored.
- CHANSVmLinkModules: global and native table indices have independent lifetimes; 98.571430%; instructions 189/189; structural 0; diffs 46; data 6904/6904; regressions 0; restored.
- CHANSVmLinkModules: independent dispatch tables and pass indices; 98.571430%; instructions 189/189; structural 0; diffs 46; data 6904/6904; regressions 0; restored.
- CHANSVmLinkModules: module and dispatch owners declared together at function scope; 98.571430%; instructions 189/189; structural 0; diffs 46; data 6904/6904; regressions 0; restored.
- CHANSVmLinkModules: pass-local initialized table and iterator precede pass index; 98.677246%; instructions 189/189; structural 0; diffs 43; data 6904/6904; regressions 0; restored.
- CHANSVmLinkModules: native pass index precedes initialized table and iterator; 98.534390%; instructions 189/189; structural 2; diffs 46; data 6904/6904; regressions 0; restored.
- CHANSVmLinkModules: global iterator declared after pass index; 98.677246%; instructions 189/189; structural 0; diffs 43; data 6904/6904; regressions 0; restored.
Diagnosis VmBlobPackCommon: 668/668 instructions and frame agree, data/jump tables 100%. Two branch destinations differ before register tuning: zero-byte padding source still stores an unchanged offset while target branches directly to the parse loop; integer-count validation source checks negatives only in inferred-count branch while target shares the check after both branches. Packing-state register allocation also differs widely.
- VmBlobPackCommon: zero padding bypasses unchanged-offset store; 97.941620%; instructions 668/668; structural 1; diffs 245; data 6904/6904; regressions 0; restored.
- VmBlobPackCommon: integer count validation is shared by explicit and inferred counts; 97.941620%; instructions 668/668; structural 1; diffs 245; data 6904/6904; regressions 0; restored.
- VmBlobPackCommon: both target branch destinations preserved with common count validation; 97.949104%; instructions 668/668; structural 0; diffs 244; data 6904/6904; regressions 0; restored.
- VmBlobPackCommon: format owners declared after per-element work; 97.949104%; instructions 668/668; structural 0; diffs 244; data 6904/6904; regressions 0; restored.
- VmBlobPackCommon: pass counters declared before format owners; 97.949104%; instructions 668/668; structural 0; diffs 244; data 6904/6904; regressions 0; restored.
- VmBlobPackCommon: format-state declarations shared between counting and writing passes; 97.889220%; instructions 668/668; structural 40; diffs 277; data 6904/6904; regressions 0; restored.
Retained VmBlobPackCommon branch correction: target zero-padding bypass and shared count validation remove both structural differences, 668/668 instructions, 97.934135 -> 97.949104%, 246 -> 244 diffs; all remaining diffs are register/operand coloring. Data remains 6904/6904, pending gate.
VmBlobPackCommon retained branch correction passed full clean gate --base f00336cc. Instruction-exact 218/233, code 36844/53564, data 6904/6904, .data 100%, pool identical; no regressions, forbidden additions or readability warnings; correct DOL SHA1.
Diagnosis VmBlobUnpack: frame and all 517 instructions match structurally, but format cursor/count, blob owner, array element and decoded-value registers differ. Shared versus per-case array-element lifetimes, signed count treatment and type-specific decode temporaries are tested before register-only search.
- VmBlobUnpack: one array-element owner shared across integer/string/hex output cases; 98.452614%; instructions 517/517; structural 0; diffs 141; data 6904/6904; regressions 0; restored.
- VmBlobUnpack: decoded integer value scoped to each integer output iteration; 98.268860%; instructions 517/517; structural 0; diffs 156; data 6904/6904; regressions 0; restored.
- VmBlobUnpack: signed integer traversal counter with explicit unsigned bound; 98.268860%; instructions 517/517; structural 0; diffs 156; data 6904/6904; regressions 0; restored.
- VmBlobUnpack: format length read through named string-value owner; 96.392650%; instructions 526/517; structural 11; diffs 500; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: chunk-table slot declared and initialized inside the scan iteration; 99.583336%; instructions 96/96; structural 0; diffs 7; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: chunk scan bound has an unsigned named extent; 99.583336%; instructions 96/96; structural 0; diffs 7; data 6904/6904; regressions 0; restored.
- CHANSVmNewObjData: chunk scan ordinal and initialized slot share fallback scope; 99.583336%; instructions 96/96; structural 0; diffs 7; data 6904/6904; regressions 0; restored.
Retained VmBlobUnpack: one array-element variable used by every decode case, removing two shadow declarations. 98.268860 -> 98.452614%, 156 -> 141 positional differences, 517/517 instructions, structural 0, data 6904/6904; pending full gate.
VmBlobUnpack shared array-element owner passed full clean gate --base f00336cc: GATE PASS, exact 218/233, matched code 36844/53564, data 6904/6904, pools identical and .data 100%. DOL hash correct; regressions/forbidden/readability all 0.
Diagnosis CHANSVmStep last: frame 0xf0 and 1253 instructions agree, but 71 structural differences remain. Target uses explicit zero-count normalization and a pretested postdecrement loop, one shared rodata base for undefined constants and result-type tables, byte-offset enumeration rather than a moving enum pointer, different load-string error merge, and different property-result ownership. All 121 initial jump-table relocations are identical; any variant that moves them is rejected.
- CHANSVmStep: explicit zero normalization and pretested postdecrement interpreter loop; 96.983240%; instructions 1255/1253; structural 63; diffs 1228; data 2232/6904; regressions 0; restored.
- CHANSVmStep: result-type tables named directly for compiler rodata-base reuse; 96.308860%; instructions 1254/1253; structural 89; diffs 1094; data 2232/6904; regressions 0; restored.
- CHANSVmStep: enumerated type pointer derived from array index each iteration; 96.396645%; instructions 1254/1253; structural 75; diffs 1131; data 2232/6904; regressions 0; restored.
- CHANSVmStep: float index comparisons follow target operand direction; 96.452515%; instructions 1253/1253; structural 71; diffs 318; data 6904/6904; regressions 0; restored.
- CHANSVmStep: pretested countdown with direct tables and indexed type enumeration; 96.604950%; instructions 1257/1253; structural 74; diffs 1220; data 2232/6904; regressions 0; restored.
- CHANSVmStep: class test puts successful constructor selector before the error arm; 96.466080%; instructions 1253/1253; structural 65; diffs 313; data 6904/6904; regressions 0; restored.
- CHANSVmStep: indirect store addresses the second scratch header directly; 95.683160%; instructions 1251/1253; structural 78; diffs 1234; data 2232/6904; regressions 0; restored.
- CHANSVmStep: string load preserves deletion failures and merges the final result; 96.032720%; instructions 1253/1253; structural 75; diffs 318; data 6904/6904; regressions 0; restored.
- CHANSVmStep: constructor branch and direct indirect-store scratch address; 95.696730%; instructions 1251/1253; structural 72; diffs 1235; data 2232/6904; regressions 0; restored.
- CHANSVmStep: constructor branch, direct scratch address and merged string-load result; 95.450120%; instructions 1251/1253; structural 76; diffs 1235; data 2232/6904; regressions 0; restored.
Retained CHANSVmStep constructor-test direction: 96.452515 -> 96.466080%, 318 -> 313 diffs, structural 71 -> 65, unchanged 1253/1253 instructions and .data 100%. Only the positive class arm precedes the failure arm; no table relocations or strings move. Rejected every size/pool-regressing countdown/table/enumeration/indirect-store trial.
CHANSVmStep positive constructor branch passed full clean gate --base f00336cc: GATE PASS, exact 218/233, matched code 36844/53564, data 6904/6904 and .data 100%; no regressions, forbidden patterns or readability warnings. DOL hash correct.
Completeness audit PASS: every remaining open function has at least three distinct compiling source-level trials in this run. Declaration-order search added 52 builds. Accepted VmCallMethod is separately exact after a clean build; current exact count 218/233. Work remains partial because 15 functions are open.
Relocation audit correction: .data has 255 code relocations including method/function-pointer tables; all 255 normalized destinations are identical. Of these, the 121 CHANSVmStep interpreter jump-table relocations are identical. The earlier assertion mistakenly counted all code relocations as interpreter entries; no source or data changed.
Final independent unit comparison against fresh initial snapshot: preserves every one of the original 217 objdiff-exact functions, adds VmCallMethod at 100.0%, code 35720 -> 36844, data 6904 -> 6904. All 15 remaining functions have >=3 distinct compiling trials; full final gate PASS.
