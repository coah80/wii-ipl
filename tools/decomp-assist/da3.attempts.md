# da3 asm conversion evidence

Scope: agent/w1005/da3, base 9d40859e. Only the six assigned source files are in scope. Original objects and Ghidra exports are the conversion reference. Sources, reports and rejected trials are retained locally under build/da3.

## Baseline

Fresh source objects and report: BS2Start 3/3 functions, 472/472 code; BS2Init 2/2, 272/272; BS2Mach 25/29, 5112/16980 code, 158528/158528 data; rvl_dec 4/4, 2600/2600 code, 36872/36872 data; CHANSVm 224/233, 39908/53564 code, 6904/6904 data. Every assigned asm function starts at objdiff 100%. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.

## Architectural assembly retained under deasm rule 1

- BS2Init::ClearOtherBATs: target has isync, zeroes DBAT2/3 and IBAT1/2/3 lower and upper SPRs, then isync/blr. Ghidra drops every BAT write and shows only the synchronizations. These writes change memory mappings; translating that output would delete required effects. Inspect repository intrinsics before deciding whether C can preserve the exact sequence.
- BS2Mach::Run: target starts mtctr r5 / mtlr r3, clears r2/r13 and nonvolatile r14-r31, replaces r1 with 0x81600000, then dcbz/dcbf every 32-byte block and blr to the supplied entry point. C cannot promise a no-return handoff with cleared ABI base registers and a replacement stack. Ghidra loses the stack/register setup. Keep unchanged.
- BS2Start::__start and __init_registers: both are in .init. __start calls __init_registers before establishing an 8-byte stack record, then transfers to main/exit. __init_registers initializes r1, r2 and r13 from linker symbols and clears every other required GPR. An ordinary C prologue would use an uninitialized stack and SDA bases. Ghidra reduces __init_registers to return 0 and omits startup stack effects. Keep both unchanged; the assignment counted one but the file contains two.
- gsPlatformUtil::GetTicks: mfc0 reads MIPS CP0 register 9 under #ifdef _PS2. It is excluded from the RVL build and has no 43U target symbol or Ghidra export. Hardware counter access requires its platform instruction; keep unchanged. Verify the enclosing preprocessor branch against the included nonport source.

## VmPushFuncReturnInfo

1. Compared the original-object Ghidra control flow with the existing portable body, then compiled that body without the asm conditional. Pool identical, 107/107 instructions, only two differences at indices 54/55: heap-end and heap-start loads are reversed. No control-flow or register-allocation differences.
2. Read the free executable-buffer boundary into a named block-local before subtracting it from the object stack top. The compiler still schedules the same two loads in the wrong order.
6. space helper vmU8* start, vmU8* end: 107/107 instructions, 2 differences: [54, 55].
7. space helper vmU8* end, vmU8* start: 107/107 instructions, 2 differences: [54, 55].
8. space helper CHANSVmPrivate* pVm: 107/107 instructions, 2 differences: [54, 55].
9. space helper const vmU8* start, vmU8* end: 107/107 instructions, 2 differences: [54, 55].
10. space helper const vmU8* end, vmU8* start: 107/107 instructions, 2 differences: [54, 55].
11. space helper const CHANSVmPrivate* pVm: 108/107 instructions, 58 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 58].
12. right-hand size comparison: 107/107 instructions, 4 differences: [54, 55, 57, 58].
13. named pointer before stack end: 107/107 instructions, 2 differences: [54, 55].
14. signed negative gap then negate: 108/107 instructions, 60 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 57].
15. explicit typed end pointer: 107/107 instructions, 2 differences: [54, 55].
3. Pointer subtraction before unsigned conversion: same two load-order differences.
4. Negated start address plus end address: same two differences.
5. Extracted a stack allocator with its own typed VM pointer and free-buffer local: same two differences.
ClearOtherBATs intrinsic audit: repository provides __sync but no __isync or __mtspr declarations/usages. PPCArch wrappers are asm functions; none exposes the required BAT writes. Retained under rule 1.
GameSpy audit: nonport.c includes gsPlatformUtil.c. Its 43U report has 18/18 exact functions and no GetTicks symbol. The _PS2 branch ends at gsPlatformUtil.c:541.
16. allocator CHANSVm* vm, size, vmPtr, expression argument False: 107/107 instructions, 2 differences: [54, 55].
17. allocator CHANSVm* vm, size, vmPtr, expression argument True: 107/107 instructions, 2 differences: [54, 55].
18. allocator CHANSVm* vm, size, CHANSVmExecutionCtx*, expression argument False: 107/107 instructions, 2 differences: [54, 55].
19. allocator CHANSVm* vm, size, CHANSVmExecutionCtx*, expression argument True: 107/107 instructions, 2 differences: [54, 55].
20. allocator CHANSVm* vm, const size, vmPtr, expression argument False: 107/107 instructions, 2 differences: [54, 55].
21. allocator CHANSVm* vm, const size, vmPtr, expression argument True: 107/107 instructions, 2 differences: [54, 55].
22. allocator CHANSVm* vm, const size, CHANSVmExecutionCtx*, expression argument False: 107/107 instructions, 2 differences: [54, 55].
23. allocator CHANSVm* vm, const size, CHANSVmExecutionCtx*, expression argument True: 107/107 instructions, 2 differences: [54, 55].
24. allocator CHANSVmPrivate* pVm, size, vmPtr, expression argument False: 107/107 instructions, 2 differences: [54, 55].
25. allocator CHANSVmPrivate* pVm, size, vmPtr, expression argument True: 107/107 instructions, 2 differences: [54, 55].
26. allocator CHANSVmPrivate* pVm, size, CHANSVmExecutionCtx*, expression argument False: 107/107 instructions, 2 differences: [54, 55].
27. allocator CHANSVmPrivate* pVm, size, CHANSVmExecutionCtx*, expression argument True: 107/107 instructions, 2 differences: [54, 55].
28. allocator CHANSVmPrivate* pVm, const size, vmPtr, expression argument False: 107/107 instructions, 2 differences: [54, 55].
29. allocator CHANSVmPrivate* pVm, const size, vmPtr, expression argument True: 107/107 instructions, 2 differences: [54, 55].
30. allocator CHANSVmPrivate* pVm, const size, CHANSVmExecutionCtx*, expression argument False: 107/107 instructions, 2 differences: [54, 55].
31. allocator CHANSVmPrivate* pVm, const size, CHANSVmExecutionCtx*, expression argument True: 107/107 instructions, 2 differences: [54, 55].

Rvl_decode_szs, szs-1: Ghidra control flow with typed header and no register annotations. objdiff 64.26087%, 71/69 instructions, 69 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/szs-1/.

Rvl_decode_szs, szs-2: Use the input parameter as the stream cursor and a separate backreference pointer; signed remaining count controls literal and copy exits. objdiff 64.82609%, 71/69 instructions, 66 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/szs-2/.

Rvl_decode_szs, szs-3: Byte-wide header and inline helper decode the distance before advancing input. objdiff 55.855072%, 70/69 instructions, 64 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/szs-3/.

Rvl_decode_szs, szs-4: Byte flags and counted tail loop with independent copy cursor. objdiff 64.82609%, 71/69 instructions, 66 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/szs-4/.
32. vmSize gap with start assigned first: 107/107 instructions, 5 differences: [54, 55, 56, 57, 59].
33. vmSize gap with end assigned first: 107/107 instructions, 2 differences: [54, 55].
34. vmS32 gap with start assigned first: 107/107 instructions, 5 differences: [54, 55, 56, 57, 59].
35. vmS32 gap with end assigned first: 107/107 instructions, 2 differences: [54, 55].
36. unsigned int gap with start assigned first: 107/107 instructions, 5 differences: [54, 55, 56, 57, 59].
37. unsigned int gap with end assigned first: 107/107 instructions, 2 differences: [54, 55].
38. int gap with start assigned first: 107/107 instructions, 5 differences: [54, 55, 56, 57, 59].
39. int gap with end assigned first: 107/107 instructions, 2 differences: [54, 55].
40. vmU32 gap with start assigned first: 107/107 instructions, 5 differences: [54, 55, 56, 57, 59].
41. vmU32 gap with end assigned first: 107/107 instructions, 2 differences: [54, 55].
42. vmSize separately bound boundaries in helper CHANSVm* vm: 108/107 instructions, 58 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 58].
43. vmSize separately bound boundaries in helper const CHANSVmPrivate* pVm: 108/107 instructions, 58 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 58].
44. vmU32 separately bound boundaries in helper CHANSVm* vm: 108/107 instructions, 58 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 58].
45. vmU32 separately bound boundaries in helper const CHANSVmPrivate* pVm: 108/107 instructions, 58 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 58].
46. int separately bound boundaries in helper CHANSVm* vm: 108/107 instructions, 58 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 58].
47. int separately bound boundaries in helper const CHANSVmPrivate* pVm: 108/107 instructions, 58 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 58].

Rvl_decode_ash, ash-1: Original Ghidra tree-building control flow rewritten with typed header and separate literal/distance trees. objdiff 27.4%, 251/220 instructions, 251 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/ash-1/.
48. vmS32 separately bound boundaries in helper CHANSVm* vm: 108/107 instructions, 58 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 58].

Rvl_decode_ash, ash-2: Word-wide node counters preserve the target addi arithmetic; offsets unsigned. objdiff 31.568182%, 247/220 instructions, 247 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/ash-2/.

Rvl_decode_ash, ash-3: Inline aligned word-reader owns stream offset arithmetic. objdiff 31.568182%, 247/220 instructions, 247 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/ash-3/.
49. vmS32 separately bound boundaries in helper const CHANSVmPrivate* pVm: 108/107 instructions, 58 differences: [17, 19, 28, 42, 51, 53, 54, 55, 56, 58].

Rvl_decode_asr, asr-1: Ghidra range decoder with named literal/distance state, typed frequency tables and eight-byte backreference copies. objdiff 49.872463%, 373/345 instructions, 372 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/asr-1/.

Rvl_decode_asr, asr-2: Counted initialization loops follow the original CTR loops and independently track cumulative totals. objdiff 46.008698%, 377/345 instructions, 376 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/asr-2/.

Rvl_decode_asr, asr-3: Inline midpoint helper changes search-expression temporary ownership. objdiff 46.008698%, 377/345 instructions, 376 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/asr-3/.
50. Assign free-size twice and bind stack-end to a separate pointer for allocation; 107/107 instructions, 35 register differences; the two loads have the correct order. Evidence build/da3/vm-50.ctx.
51. reused space helper CHANSVmPrivate* pVm, start, const return '': 107/107 instructions, 0 differences: [].
63. result before CHANSVmPrivate* pVm, initialized False: 107/107 instructions, 35 differences: [6, 7, 8, 10, 11, 20, 23, 24, 25, 29].
64. result before CHANSVmPrivate* pVm, initialized True: 107/107 instructions, 35 differences: [6, 7, 8, 10, 11, 20, 23, 24, 25, 29].
65. result before CHANSVmExecutionCtx* block;, initialized False: 107/107 instructions, 35 differences: [6, 7, 8, 10, 11, 20, 23, 24, 25, 29].
66. result before CHANSVmExecutionCtx* block;, initialized True: 107/107 instructions, 35 differences: [6, 7, 8, 10, 11, 20, 23, 24, 25, 29].
67. result before vmU8* objStackTopBuf;, initialized False: 107/107 instructions, 35 differences: [6, 7, 8, 10, 11, 20, 23, 24, 25, 29].
68. result before vmU8* objStackTopBuf;, initialized True: 107/107 instructions, 35 differences: [6, 7, 8, 10, 11, 20, 23, 24, 25, 29].
69. result before u32 size;, initialized False: 107/107 instructions, 35 differences: [6, 7, 8, 10, 11, 20, 23, 24, 25, 29].
70. result before u32 size;, initialized True: 107/107 instructions, 35 differences: [6, 7, 8, 10, 11, 20, 23, 24, 25, 29].
71. result before u32 i;, initialized False: 107/107 instructions, 9 differences: [11, 20, 24, 25, 29, 45, 83, 99, 100].
72. result before u32 i;, initialized True: 107/107 instructions, 9 differences: [11, 20, 24, 25, 29, 45, 83, 99, 100].
73. result before result = CHANS_VM_ERR_PUSH_FUNC_RETURN_INFO;, initialized False: 107/107 instructions, 9 differences: [11, 20, 24, 25, 29, 45, 83, 99, 100].
74. stack allocation locals before CHANSVmPrivate* pVm: 107/107 instructions, 0 differences: [].

## Exact VM candidate

Trial 51 is instruction-exact: the stack-space inline helper reads the free-buffer address into one local, replaces that local with the available byte count, then returns it. Moving the twice-assigned value across the inline boundary preserves the target register allocation and the free-buffer/top-buffer load order. No assembly, volatile casts, uninitialized values or layout changes. Trial 74 independently reaches the same 107/107 instructions by declaring the two allocation locals first; trial 51 is the selected implementation.

Source search uses a private copy under build/da3 because the shared script otherwise locates the earlier VmPushFuncReturnInfo prototype and mutates the next function. The local copy requires a function definition. Seed 31 completed 77 search trials at 99.88785% with no improvement. Seed 32 started after a CPU slot became available and was stopped once manual trial 51 was exact. No shared tooling was edited.

Decoder first-round conclusions: SZS remains 70-71 instructions versus 69; ASH remains 247-251 versus 220; ASR remains 373-377 versus 345. Each has at least three compiled, distinct source-level trials. The C candidates are not accepted and the original source is restored before the VM full gate. No decoder is claimed to be a legitimate-assembly exception based only on a failed conversion.

VmPushFuncReturnInfo accepted locally after clean full gate: GATE PASS; objdiff 100.0%, ctxdiff 107/107 and diffs 0; pool 125/125 identical; unit still 224/233 functions, 39908/53564 matched code, 6904/6904 data; global regressions 0; forbidden/readability 0. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.

Rvl_decode_ash, ash-4: Typed encoded-word views preserve byte-offset lwzx reads without index scaling. objdiff 29.263636%, 248/220 instructions, 248 positional differences; POOL IDENTICAL up to 0 (mine=0 base=0). Evidence build/da3/ash-4/.

## Decoder provenance and constraints

The local history introduced the SZS/ASH/ASR asm bodies in 94bc16ef, 50fc7d26 and ae79db87 on 2026-09-19. These commits replaced TODOs with retail instruction listings. They do not establish that assembly is required by the API. Treat all three as unresolved conversions.

The SZS target holds decodedSize in r0 for the entire decode while its C versions allocate a normal GPR; its source/input cursor copies also add instructions. ASH and ASR targets materialize work with lis @h plus ori @l, whereas normal C emits compiler-owned addressing. ASH also preserves the return size in r0 after building both trees. These are concrete code-generation differences, not grounds for asserting a completed decompilation.

Applicable levers tried: Ghidra reference; typed input/table views; signed/unsigned and byte/word locals; const inputs; separate value lifetimes; local declaration/initialization placement; block scopes; counted loops; inline expressions and allocator boundaries; automatic source mutations. No eZiText optimization-off spelling, thunk-order, data split, compiler version, flags sweep, uninitialized-local or volatile workaround is justified here. No shared header or source unit was changed.

VmPushFuncReturnInfo conversion commit: e539a6e8. All failed decoder candidates remain outside the source tree.

## Automatic decoder searches

- SZS seed 33: 392 search trials in the 180-second search. Best unaccepted C candidate: 65.55073%, 70/69 instructions. The target stores the preserved result in r0 while the C result uses a different register; stream advancement and backreference scheduling also differ.
- ASH seed 34: 364 search trials. Best unaccepted C candidate: 33.47273%, 247/220 instructions. Typed tree reconstruction still adds register saves, indexing and branch instructions.
- ASR seed 35: 349 search trials. No improvement over the initial 49.872463%, 373/345-instruction C candidate. Table initialization/search/update control flow and register allocation remain different.
- Search output is diagnostic only. No automatically mutated C was copied into the source tree. Original rvl_dec.c is restored byte-for-byte. Additional wrapper Rvl_decode asm was observed; the assignment names the three decoder bodies, so the wrapper is unchanged.
- The three decoder conversions remain open after the required distinct compiled attempts and searches. Retained architectural routines have separate rule-1 evidence above. They are not conflated with failed decoder conversions.

BS2Start verification accounts for .init explicitly: __start is 168/168 raw bytes with zero differences; __init_registers is 144/144 raw bytes with zero differences. gate.py and the supplied ctxdiff helper inspect .text only, so gate.py reports 0/0 instruction functions for this .init unit; the live objdiff report and the direct section-byte comparison establish its actual 3/3 exact functions.

## Final clean validation

full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Init] pool: IDENTICAL
[src/BS2/BS2Init] objdiff: code 272/272 data None/None functions 2/2 fuzzy 100.0000 linked code 272
[src/BS2/BS2Init] instruction-exact functions: 2/2
[src/BS2/BS2Init]   section .text size 272 match 100.0
[src/BS2/BS2Init] baseline: code 272/272 data None functions 2 fuzzy 100.0000
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 5112/16980 data 158528/158528 functions 25/29 fuzzy 99.1698 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 25/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match 100.0
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 99.169846
[src/BS2/BS2Mach]   below 100: BS2StartGame 98.72774
[src/BS2/BS2Mach]   below 100: BS2StartGCGame 97.82895
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 99.50739
[src/BS2/BS2Mach]   below 100: BS2Tick 98.799484
[src/BS2/BS2Mach] baseline: code 5112/16980 data 158528 functions 25 fuzzy 99.1698
[src/BS2/BS2Start] pool: IDENTICAL
[src/BS2/BS2Start] objdiff: code 472/472 data None/None functions 3/3 fuzzy 100.0000 linked code 472
[src/BS2/BS2Start] instruction-exact functions: 0/0
[src/BS2/BS2Start]   section .init size 472 match 100.0
[src/BS2/BS2Start] baseline: code 472/472 data None functions 3 fuzzy 100.0000
[src/system/rvl_dec] pool: IDENTICAL
[src/system/rvl_dec] objdiff: code 2600/2600 data 36872/36872 functions 4/4 fuzzy 100.0000 linked code 2600
[src/system/rvl_dec] instruction-exact functions: 4/4
[src/system/rvl_dec]   section .bss size 36872 match 100.0
[src/system/rvl_dec]   section .text size 2600 match 100.0
[src/system/rvl_dec] baseline: code 2600/2600 data 36872 functions 4 fuzzy 100.0000
[src/scene/nakamuraTest/gamespy/nonport] pool: DIVERGES at string 0 (mine=4 orig=1)
[src/scene/nakamuraTest/gamespy/nonport] objdiff: code 1352/1352 data 56/56 functions 18/18 fuzzy 100.0000 linked code 1352
[src/scene/nakamuraTest/gamespy/nonport] instruction-exact functions: 18/18
[src/scene/nakamuraTest/gamespy/nonport]   section .bss size 16 match 100.0
[src/scene/nakamuraTest/gamespy/nonport]   section .data size 32 match 100.0
[src/scene/nakamuraTest/gamespy/nonport]   section .sbss size 8 match 100.0
[src/scene/nakamuraTest/gamespy/nonport]   section .text size 1352 match 100.0
[src/scene/nakamuraTest/gamespy/nonport] baseline: code 1352/1352 data 56 functions 18 fuzzy 100.0000
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 39908/53564 data 6904/6904 functions 224/233 fuzzy 99.4673 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 224/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.46733
[src/channelScript/CHANSVm]   below 100: CHANSVmConvertToFloatFromStr 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmStringSplit 98.04054
[src/channelScript/CHANSVm]   below 100: CHANSVmFormatString 99.84919
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 98.0988
[src/channelScript/CHANSVm]   below 100: VmBlobUnpack 98.452614
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 96.98723
[src/channelScript/CHANSVm] baseline: code 39908/53564 data 6904 functions 224 fuzzy 99.4673
regressions vs baseline: 0
global matched_code_percent: 92.73726 -> 92.73726
global fuzzy_match_percent: 99.78007 -> 99.78007
global complete_code_percent: 76.40339 -> 76.40339
global matched_data_percent: 99.99410 -> 99.99410
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

src/BS2/BS2Init: functions 2 -> 2/2; code 272 -> 272/272; data 0 -> 0/0
POOL IDENTICAL up to 0 (mine=0 base=0)
ClearOtherBATs: objdiff 100.0%; src 0x38 base 0x38 insns 14/14; diffs 0: []
src/BS2/BS2Mach: functions 25 -> 25/29; code 5112 -> 5112/16980; data 158528 -> 158528/158528
POOL IDENTICAL up to 91 (mine=91 base=91)
Run: objdiff 100.0%; src 0xac base 0xac insns 43/43; diffs 0: []
src/BS2/BS2Start: functions 3 -> 3/3; code 472 -> 472/472; data 0 -> 0/0
POOL IDENTICAL up to 0 (mine=0 base=0)
__start: objdiff 100.0%, .init 42/42 instructions, raw bytes identical
__init_registers: objdiff 100.0%, .init 36/36 instructions, raw bytes identical
src/system/rvl_dec: functions 4 -> 4/4; code 2600 -> 2600/2600; data 36872 -> 36872/36872
POOL IDENTICAL up to 0 (mine=0 base=0)
Rvl_decode_szs: objdiff 100.0%; src 0x114 base 0x114 insns 69/69; diffs 0: []
Rvl_decode_ash: objdiff 100.0%; src 0x370 base 0x370 insns 220/220; diffs 0: []
Rvl_decode_asr: objdiff 100.0%; src 0x564 base 0x564 insns 345/345; diffs 0: []
src/scene/nakamuraTest/gamespy/nonport: functions 18 -> 18/18; code 1352 -> 1352/1352; data 56 -> 56/56
GameSpy pool baseline discrepancy: source .data 260 bytes / four strings, target .data 32 bytes / one string. First source string gsAssert.c, target localhost. Unit inputs are unchanged from 9d40859e, objdiff remains 18/18 and data 56/56, linked DOL is exact. No GameSpy conversion is submitted. The gate prints the pool difference but does not reject it.
src/channelScript/CHANSVm: functions 224 -> 224/233; code 39908 -> 39908/53564; data 6904 -> 6904/6904
POOL IDENTICAL up to 125 (mine=125 base=125)
VmPushFuncReturnInfo: objdiff 100.0%; src 0x1ac base 0x1ac insns 107/107; diffs 0: []
DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d

Final progress/report regeneration and build/43U/ok passed. tools/decomp_status.py wrote build/da3/final-status.json. tools/check_decomp_complete.py returns DECOMPLETE_FAIL for the existing incomplete project. No full-project completion is claimed. Details: build/da3/completion-check.log.

Result: one exact asm-to-C conversion, five architectural or excluded-platform routines retained with evidence, three decoder conversions still open. The six owned units remain at 276/289 objdiff-exact functions, 49716/75240 matched code bytes and 202360/202360 matched data bytes. All owned function scores and linked measures are unchanged.
