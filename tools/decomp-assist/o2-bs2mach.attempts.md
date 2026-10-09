# o2-bs2mach attempts (BS2Mach: CheckBS2CommandStatus, BS2Tick)

Worktree data-d7, branch agent/w1009/o2-bs2mach, base 20cf9f9f (origin/main).
Start: 27/29 exact, CheckBS2CommandStatus 2/406, BS2Tick 57/1940, data 158528/158528, pool 91/91.

## CheckBS2CommandStatus (lever 35)

Target case 0x12 issues `lwz count; stw CacheCommandComplete; slwi`: the completion
store fills the load-latency slot, so it has no edge to the partition-count load
through `DataToc`. A file-scope static may alias that pointer load, a
function-local static whose address is never taken may not.

1. `static u32 CacheCommandComplete = 0;` inside CheckBS2CommandStatus (it is the
   only user), completion stored before the length update as in every other case:
   CheckBS2CommandStatus 0/406. Every other function unchanged, pool identical.
   The static lands at the end of .sbss (after LoaderInit) instead of 0x50.
2. Compiler probe (same flags): initialized objects and function statics are
   emitted in parse order, tentative definitions after them in reverse definition
   order (`I1 I2 L$4 I3 T4 T3 T2 T1`).
3. AudioBufferUnconfigured..LoaderInit made tentative (initializers dropped) and
   listed in reverse: .sbss order and offsets identical to the target, 28/29
   exact, data 158528/158528. Target symbol renamed `CacheCommandComplete$1964`
   in config/43U/symbols.txt (project convention for function statics).

## BS2Tick (57 at start)

4. Same lever in case 0: the target schedules `li 1` first and keeps the
   `AudioBufferUnconfigured = 1` store free of the absolute `*(u32 *)0x800030d4`
   store (unknown storage aliases every file-scope object, not a function static).
   AudioBufferUnconfigured, ResetTime and SpinupDeadline are only used by BS2Tick
   and sit right after CacheCommandComplete in .sbss. All three as BS2Tick
   statics: 57 -> 52; only AudioBufferUnconfigured as a static gives the same 52,
   so ResetTime/SpinupDeadline stay file-scope tentatives. Symbol renamed
   `AudioBufferUnconfigured$2066`. .sbss order identical.
5. Store-before-load pairs the target keeps and we hoist (case 0x30
   `PartitionOpen = 0; if (RegionValid == 0)`, case 0x34/0x35
   `LoadingTitle = 0; switch (Block.state)`, case 0x40 `AbortFlag = 0;
   if (RestartRequested == 0)` and `RestartRequested = 0; if (FatalErrorFlag)`).
   Compiler probe with the unit's flags (/tmp/o2-bs2mach/probe/t2.c, t3.c): a
   store to one global followed by a load of another keeps its order only when
   BOTH are volatile; non-volatile/volatile, volatile/non-volatile, extern and
   address-taken globals are all reordered. So the target proves PartitionOpen,
   LoadingTitle, AbortFlag, RestartRequested and FatalErrorFlag volatile
   (RegionValid and DVDCommandBlock.state already are). AbortFlag is also read in
   BS2DVDCallback (interrupt context); RestartRequested/AbortFlag writers disable
   interrupts. One-at-a-time sweeps could not see the case-0x40 chain because it
   needs all three together. All five: 52 -> 42, other 28 functions unchanged.
6. Device-code block (case 5): the initial PCode has a separate `lis 0x8000` per
   branch and backend value numbering merges them into the consoleType base. Per
   the MWCC decomp (ValueNumbering.c), `li`/`lis` are only value-numbered when the
   destination is a temporary inside the coalesce window; named locals never are.
   Reading consoleType through a named `OSBootInfo *bootInfo` and sharing the
   `State = BS2_STT_8` tail: 42 -> 28, block exact.
7. Case 0: `DvdProgress = (u32 *)0x800030d4; ... *DvdProgress = 0;` (as case 2
   writes it) and testing `BS2NoDisk` directly: 28 -> 24 -> 12 together with 8.
8. CoverOpenTimeHigh/Low are one 8-aligned big-endian OSTime: a single
   `OSTime CoverOpenTime` keeps CheckDVDCommandStatus exact (u64 store is low word
   first, as in the target) and makes the case-0x42 zero high word a later temp,
   fixing that whole register cluster (24 -> 14 at the time).
9. Banner check: the target loads bannerFile.length straight into r6 because it is
   the 4th OSPanic argument; the format string has `(0x%08x)` and our call had no
   argument. Passing bannerFile.length fixes the cluster.
10. RequiredIosHigh/Low are likewise one 8-aligned u64 (BS2StartGame reads it as a
   title ID with the `== 0 -> 1:3` default). `u64 RequiredIos` gives the target
   pair coloring (hi r0, lo r3, TMD r4) and keeps BS2StartGame exact.
   symbols.txt: CoverOpenTime and RequiredIos as size-8 objects (only BS2Mach
   referenced the halves; every relocation resolves to the same address).
   BS2Tick 4/1940 left: case 0 `CoverBlock.state = 0` is ordered before the
   volatile BS2NoDisk load (target: after).

### Volatile flags: per-flag evidence (current source, BS2Tick 4 diffs)
Target pairs a store to one global with a later load of another and keeps that
order; MWCC only does so when both are volatile (probe t2/t3: non-volatile,
one-sided, extern and address-taken pairs are all reordered).
- 0x3b04 case 0x30: `stw PartitionOpen; lwz RegionValid` (RegionValid volatile).
- 0x3d68 case 0x34/0x35: `stw LoadingTitle; lwz Block.state` (state volatile).
- 0x40a0 case 0x40: `stw AbortFlag; lwz RestartRequested`, then
  `stw RestartRequested; lwz FatalErrorFlag`.
Dropping any single flag: PartitionOpen 4->7, LoadingTitle 4->6, AbortFlag 4->7,
RestartRequested 4->9, FatalErrorFlag 4->6; no other function changes.

### Last 4 diffs: case 0 `CoverBlock.state = 0` vs the BS2NoDisk test
Target: `lwz r0,BS2NoDisk; stw r4,AUC; cmpwi r0,0; stw r27,0xc(r3); beq`.
Ours: the CoverBlock store precedes the load. Everything else in the block,
including every register, already matches.
- BS2NoDisk, DvdTransferred and DvdTransferLength are volatile (non-volatile
  BS2NoDisk hoists the load above both DvdTransfer stores; non-volatile
  DvdTransferred breaks BS2DVDCallback's order against DvdReadPending).
- DVDCommandBlock.state reads are volatile in the target (BS2StartGame and
  BS2StartGCGame poll it with a re-read every iteration; case 0x34 above). With
  `state` non-volatile case 0 becomes exact but those break.
- So the source reads BS2NoDisk before the store. Holding it in any variable
  (named, block-scoped, inline parameter/local, any same-width type) makes it a
  named/`@` local, numbered below statement temps and colored after the constant
  1: registers rotate (1 r0, BS2NoDisk r4, &PP r4, &0x800030d4 r5), 10 diffs.
  mwdbg capture o2-bs2mach-st + regsim what-if: coloring that holder first gives
  exactly the target (only those 4 nodes change). Narrow holders (u8/s8/u16/s16)
  force a statement temp and get everything right except `clrlwi.` vs `cmpwi`
  (1 diff). A 64-bit round trip is folded away.
- Diagnostic only, both exact 29/29, both forbidden, not committed:
  `if ((BS2NoDisk | (CoverBlock.state = 0)) != 0)` (read then store in one
  expression) and `*(s32 *)&CoverBlock.state = 0;` (non-volatile store).
  No natural spelling found: hoisting a common leading store out of all three
  branches doesn't happen (size grows); statement order grid (84 builds),
  inline helpers, casts and holder types all stay at 4-10.
- Pragma sweep (combosweep, single + pairwise): BS2Tick 4 -> 4.

### Tooling note
`#pragma push / ppc_iro_level 0 / pop` tightly around BS2Tick (the last function
in the file) leaves it byte-identical, which earlier rounds read as "IRO does not
run on BS2Tick". A file-level `#pragma ppc_iro_level 0` changes BS2Tick in 1910
instructions, so IRO does run; only the scoped placement is not honored for it.
