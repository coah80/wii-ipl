# ChannelSelect native linking

Baseline: HEAD f7b1b9b0, Equivalent, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Unit code 25668/25668, data 2336/2336, functions 102/102. Existing untracked fresh1.attempts.md left alone.

1. Set only ChannelSelect to Matching to locate the first linked-byte divergence.
   Matching SHA1 f045a95026c3ca34039d0d9064fad33832ce581a. First DOL mismatch at file 0x5ba, address 0x8133009a in __start; relocation points to data shifted by 0x40. nm and ELF comparison show the first text layout change at createChannelThumbnails, as recorded in the exact symbol table below. Extra weak Interporation<float> destructor is 0x40 bytes, plus its vtable; neither exists in the target symbols. .text grows 0x40. Pool identical, 98 strings.
   /tmp/link1.baseline.elf: createChannelThumbnails__Q33ipl5scene13ChannelSelectFv 0x813abcc4 size 0x5c.
   /tmp/link1.matching.main.elf: createChannelThumbnails__Q33ipl5scene13ChannelSelectFv 0x813abd04 size 0x5c.
   /tmp/link1.matching.main.elf: __dt__Q33ipl4math16Interporation<f>Fv 0x813abcc4 size 0x40.

2. Model the scalar Hermite specialization as a direct FrameController subclass, with its destructor declared out of line, matching the existing scalar specialization used by ChannelTitle and the target ownership at 0x81363c10. Scope the new specialization to IPL_CHANNEL_SELECT_CPP. Preserve inline init and get calculations. This avoids instantiating a nonexistent Interporation<float> destructor or vtable.
   Result: all 102 functions and data still 100%; other unit reports unchanged. DOL SHA1 acdfd504572753800958ecd275825fdc19bb92c1. Text now correct but .data is 32 bytes short: scalar table and base table reservations were removed. Real data/vtable pointers up through ChannelSelect table still identical.

3. Keep the original Hermite primary template and specialize only scalar Interporation as a novtable base, retaining its real start/end fields and methods. The target inlined constructor stores only the derived vtable; the extra base destructor had no target owner. Test whether suppressing base vtable use lets the linker discard this extra destructor while retaining ordinary compiler-emitted data reservations.
   Result: SHA1 f7cdb8937b2638367aa0479f20a880cd063d06bb. Removing the scalar base vtable use strips the 64-byte extra destructor, but removes a 16-byte data reservation; createDiskLayout remains instruction exact.

4. Restore a direct scalar Hermite specialization, now with an inline empty destructor as in the target scalar destructor. Declare FrameController::calc inline only in this TU to test normal weak base-vtable emission. This preserves the ordinary scalar and FrameController vtables without defining or retaining any fake object. Target scalar construction only sets the derived table, destructor is empty; the target data has 32 bytes of discarded weak tables after the ChannelSelect vtable and before the GUI table reservations.
   Result: DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d with ChannelSelect Matching. Scalar and FrameController weak tables are compiler-emitted and deduplicated against their existing earlier owners; no Interporation<float> symbol remains. All 102 objdiff functions exact, code 25668/25668, data 2336/2336. Every other unit report is byte-for-byte equal as JSON to the initial live baseline. pool_diff identical, 98 strings; createDiskLayout 168/168 instructions, diffs 0; VEC3 Hermite destructor 16/16 instructions, diffs 0.

Validation: running the full clean gate, full build/43U/ok, and independent checks of all 102 function instruction streams. Inline FrameController declaration keeps the implementation in its existing owning TU and requests normal weak-vtable emission here. No forced sections, data padding, new assembly, label aliases, or force-active changes.

Final clean gate output:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/channelSelect/iplChannelSelect] pool: IDENTICAL
[src/scene/channelSelect/iplChannelSelect] objdiff: code 25668/25668 data 2336/2336 functions 102/102 fuzzy 100.0000 linked code 25668
[src/scene/channelSelect/iplChannelSelect] instruction-exact functions: 102/102
[src/scene/channelSelect/iplChannelSelect]   section .data size 2144 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .rodata size 16 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sbss size 8 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sdata size 80 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .sdata2 size 88 match 100.0
[src/scene/channelSelect/iplChannelSelect]   section .text size 25668 match 100.0
[src/scene/channelSelect/iplChannelSelect] baseline: code 25668/25668 data 2336 functions 102 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 90.80962 -> 90.80962
global fuzzy_match_percent: 99.58569 -> 99.58569
global complete_code_percent: 72.50912 -> 73.36610
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```

Explicit ninja build/43U/ok passes. Regenerated live report: all other unit records unchanged from the initial snapshot. All 102 ctxdiff.py runs report identical instruction counts and diffs 0; no open function remains. DOL bytes identical to orig/43U/00000008.app, SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Functions 102/102 -> 102/102, code 25668/25668 -> 25668/25668, data 2336/2336 -> 2336/2336, linked code 0 -> 25668.
