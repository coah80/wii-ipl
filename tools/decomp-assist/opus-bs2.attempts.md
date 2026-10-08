# opus-bs2 attempts (BS2Mach 4 non-exact, BS2Update UpdateThread)

Base 16023905. Start: BS2StartGame 10/393, BS2StartGCGame 9/228, CheckBS2CommandStatus 2/406, BS2Tick 71/1940, UpdateThread 335/913.

Tooling notes:
- mwdbg crashes the emulator (WRITE_UNMAPPED @47e090) whenever `-enc SJIS` is on the command line; drop that flag for tracing (BS2Mach is ASCII). Pass the command via `--args`.
- /tmp/var.py belongs to another worker; my scratch lives in /tmp/opusbs2/.

## Lever 26 IRO off
1. `#pragma ppc_iro_level 0` around each of the four BS2Mach functions, one at a time: StartGame 10->10, StartGCGame 9->145, CheckBS2CommandStatus 2->2, BS2Tick 71->71. Rejected.

## Symbol binding (found via readelf, target LOCAL vs ours GLOBAL)
2. Target has 39 BS2Mach symbols LOCAL (State, NandPending, CacheCommandComplete, CacheSeekComplete, Run, CheckBS2CommandStatus, BS2NANDDivide*, LoaderInit/Main/Close, ...). Made them `static`. Bindings now match; no function changed score (codegen identical). Kept as a link-correctness fix.

## CheckBS2CommandStatus (case 0x12: target `lwz count; stw CacheCommandComplete; slwi`, ours `slwi; stw`)
3. NP; CCC; CacheLength += expr -> 4 (store hoisted before count load).
4. `sizeof * count` operand order -> 2. 5. `CacheLength = CacheLength + expr` -> 9. 6. `= expr + CacheLength + 32` -> 9. 7. `+= 32 + round` -> 2. 8. `* 8` -> 2. 9. `**(u32 **)&DataToc` -> 2.
10. const DVDGameTOC* cast, CCC before -> 4; CCC after -> 2 (lever 27, no effect).
11. (u32) cast on sum -> 3. 12. TRUE -> 2. 13. 0x20 -> 2. 14. `*(DVDGameTOC **)&DataToc` -> 2. 15. open-coded round -> 2.
16. static inline WriteCacheData(buf,size) helper for case 0x12 -> 241 (size becomes temp; target recomputes in else branch, so no helper).
17. mwdbg: the order comes from the pre-RA scheduler (backend-00 -> 01); post-RA scheduler leaves it. Input order has CCC store after the CacheLength store.
18. CacheCommandComplete type BOOL/int/s32 -> 2; volatile -> 46.
19. With static globals: NP;CCC;CL+= -> 4; CL = CL + (expr) after CCC -> 4.

## BS2StartGame / BS2StartGCGame shared prologue (`li r0,1` must precede the base `lis` pair)
20. mwdbg: B1 holds the bss/data base pairs, li/stw StartingGame and the hoisted `&CoverBlock` addi; height of the bss chain wins over li.
21. do-while cover loop -> 10; `for(;;) if break` -> 10; `(&CoverBlock)->state` -> 10; `while (CoverBlock.state)` -> 10; StartingGame = 1 / state != 0 -> 10.
22. `DVDGetCommandBlockStatus(&CoverBlock)` call -> 8 (prologue fixed but loop becomes bl; rejected, evidence that the stw needs a successor/priority).
23. static inline WaitForCoverCommand() / WaitCommandIdle(block) helpers -> 10/9.
24. StartingGame after the loop -> 368 (wrong).
25. `volatile BOOL StartingGame` -> StartGame 10->5, StartGCGame 9->4, every other BS2Mach function unchanged (report: 25/29 exact, data 100%). StartingGame is the cross-thread "game is starting" flag read by BS2Tick, like the other volatile flags (CacheFailed, RegionValid, NandPending). KEPT.

## BS2StartGame DI write (0xCC003024): target addr r4 / value r3, ours addr r3 / value r4 (5 diffs)
26. Declaration permutations of diBits/diValue/diAddr (5 orders) -> 5 or 7.
27. `__PIRegs[9]` instead of raw pointer, value/bits named -> 5 (same tie). regsim (want diValue=r3): structural, 0/1.
28. regsim on three-named form (want diValue=r3,diAddr=r4,diBits=r0): best 1/3, structural. The address is always a lis temp (r196); the value must be a temp numbered after it to be colored first.
29. `*diAddr = (*diAddr | 1) | diBits` (u32/vu32, 1U, no parens) -> registers right but `ori 4`+`ori 1` merge into `ori 5`: 24, size -4.
30. `diBits | (*diAddr | 1)` -> 7 (ori 1 moves after the or). `(u32)(...) | diBits` -> 7. `diValue = *diAddr | 1` -> 7. `__PIRegs[9] | 1` into named -> 7.

## BS2StartGCGame 64-bit multiply (target mulhwu(freq r5, seconds r7); ours mulhwu(seconds, freq))
31. Declaration permutations of rtc/counterBias/seconds/timerFrequency x two operand orders (48 builds) -> all 8 (freq*sec) / 4; named values are forwarded, decl order irrelevant.
32. freq*sec forms: `(OSTime)freq * sec`, `freq * (OSTime)sec`, both cast, `(u64)` (145, size change), OS_TIMER_CLOCK*, `(OS_BUS_CLOCK >> 2)` / `/ 4` inline -> 8: operand order fixes the multiply but evaluation order follows it, so registers swap.
33. sec*freq forms: OSSecondsToTicks, `time = rtc + bias; time *= clock`, `time = CLOCK * time` (operands get swapped back to time first!), OSTime-typed seconds and/or timerFrequency -> 4.
34. freq computed before seconds statement -> 4/8; `time = freq; time *= sec` -> 9.
35. OSTime-typed timerFrequency x four freq*sec forms -> 8.
36. Put the SCGetCounterBias() call inside the right operand: `time = OS_TIMER_CLOCK * (OSTime)(rtc + SCGetCounterBias());` -> 0/228 EXACT. The call makes the seconds operand heavier, so it is evaluated first (lower vreg -> r7) while the clock stays the left operand. Also exact: `(OSTime)OS_TIMER_CLOCK * (rtc + SCGetCounterBias())`, `(OSTime)(OS_BUS_CLOCK >> 2) * (...)`. Unused locals counterBias/seconds/timerFrequency removed. Pool identical (91/91), BS2Mach 26/29, data 100%.

## BS2Tick (71 at start of this round)
37. IRO off -> 71 (attempt 1).
38. Move `AudioBufferUnconfigured = 1` to each of 10 positions in case 0 -> 71/72. volatile AudioBufferUnconfigured -> 71.
39. Definition-level volatile sweep, one global at a time (36 globals): PartitionOpen 71->68, LoadingTitle 71->69, all others same or worse (State 76, ResetTime 91, CoverPollTime 166, CurrentTmd 1314, ...).
40. `static vu32 PartitionOpen` + `static vu32 LoadingTitle` -> BS2Tick 66; every other BS2Mach function unchanged (26/29, data 100%). LoadingTitle is set by BS2StartLoadingTitle from the menu thread and polled by BS2Tick; PartitionOpen is likewise a cross-call state flag. KEPT.
41. Second single-volatile sweep on top of 40 -> nothing below 66.
42. Device-code block (target 0x27d4): target shares one `State = BS2_STT_8` after the if/else; ours duplicates it. Merging fixes the tail but target also re-materializes `lis 0x8000` in each branch, ours reuses the consoleType base -> 8 bytes short, 1703 diffs. Tried consoleType as `(OSBootInfo *)`, `OSPhysicalToCached(0x2C)`, `*(u32 *)0x8000002C`, `OS_ADDR_BOOT_INFO`, `!(...)`, `OSGetConsoleType()` (adds bl), and `*(u16 *)OSPhysicalToCached(0x30E6)` for the store: all 1701-1703. Restored the duplicated State (66).
43. `#pragma ppc_iro_level 0` around BS2Tick with merged State -> identical output; IRO evidently does not run on BS2Tick (or StartGame) at all, so the lis sharing comes from the backend.

## BS2Update
44. readelf: target has rc/VersionIOS/VersionMEM2/VersionES/ConsoleType GLOBAL and getSuffix LOCAL (ours the opposite). Fixed the bindings: UpdateThread 335/913 unchanged (codegen identical).
45. Logging-call `titleId` via UPDATE_DISC_ENTRIES macro instead of discEntries (target re-materializes `lis 0x8048` there) -> 335. Dropping the discEntries local entirely -> 382. Remaining diff is an extra callee-saved register in target (r14..r31) shifting every allocation; not pursued further this round.

Final gate (BS2Mach + BS2Update, --quick): GATE PASS, 0 regressions, BS2Mach 26/29 exact (BS2StartGCGame new), BS2Update 9/10.
Best non-exact sources: opus-bs2.best.c (BS2Tick 66, volatile PartitionOpen/LoadingTitle), opus-bs2.best.BS2Update.c (binding fixes, UpdateThread 335).
