# BS2Mach attempts

Baseline: 16/29 instruction-exact functions, code 2500/16980 bytes,
data 155472/158528 bytes. The fresh branch baseline gate passes.
Only this unit is changed. No linking changes are made.

The assembly and the existing object decompiler exports under /tmp were read.
Older /tmp source candidates were used as reference and audited before adapting
individual bodies. Their assembly, force_active pragmas, register qualifiers,
volatile additions, packed string blobs, and raw structure offsets are excluded.

## Object-order implementation, first pass

- Run: C cache-block zero/flush loop followed by the entry call. The original
  clears nearly all GPRs, replaces the stack, and branches through LR. C cannot
  express that register contract. The report gives no function score.
- BS2ESGetTicketViews: separate aligned title/count buffers produced 72/71
  instructions and a 0x180 frame versus 0x160. A single 256-byte IPC workspace
  with typed title/count arrays and boolean null checks gives 71/71, diffs 0.
- BS2Reboot: ordinary aligned ticket, IOS workspace, state flags and vectors
  initially gave 137/137, eight stack-offset diffs. Reordering descriptor and
  count declarations gives 137/137, diffs 0. No fabricated padding is used.
- BS2StartGame: implemented boot-cache close, state flags, IOS launch, DVD
  reopen, and loader handoff. First score 96.48855%. Target contains sync/isync
  and polls callback results; no new assembly or volatile was introduced.
- BS2StartGCGame: implemented configuration, SRAM fields, clock and MIOS launch.
  First score 95.26755%.
- CheckDVDCommandStatus: original switch/state transitions, 102/102, diffs 0.
- BS2NANDDivideCallback: transfer accounting before buffer advance, separate
  full/final chunk branches, first score 85.03906%.
- BS2NANDDivideReadAsync: original request setup and chunk branches with ordinary
  globals, first score 60.31915%, 45/47 instructions. Compiler removes reloads.
- BS2NANDDivideWriteAsync: corresponding write setup, first score 60.31915%.
- CheckBS2CommandStatus: cache-writing state switch, first score 79.655174%.
- BS2InquiryAsync: boot-cache/DVD unencrypted read branches, instruction-exact.
- BS2ReadDiskID: boot-cache/DVD read branches, instruction-exact.
- BS2Tick: implementation pending at this checkpoint.

String pool: the first 56 strings are identical in order; the remaining 35
orig strings belong to BS2Tick. Checkpoint: 21/29 exact, code 4052/16980,
zero regressions, zero forbidden additions, zero readability warnings.

## Complete state machine and data review

BS2Tick was implemented last, preserving object order. All 91 ordinary string
literals now occur in the original order and at the original .data offsets.
A separate offset comparison found zero differences across all 91 strings.
The small writable GameCube language mapping, /dev/es and disc prefixes produce
an instruction-independent .sdata match of 32/32 bytes. The larger .data section
still has no objdiff match score; strings alone do not establish a data match.

Semantic review corrected the cover command block reset, replaced an unsafe
four-byte memset of separate char locals with a four-byte title array, used
DVDFileInfo fields for banner position/length, and changed the newly implemented
loader code to use the target's __DVDLayoutFormat rather than BS2LastMode.
All partition/TMD/SRAM field accesses use their existing structure definitions.
The allocation rounds down then adds one cache line to select the next aligned
banner address, as the target does. This is buffer alignment, not data padding.

The ES stack workspace follows the SDK's 256-byte IPC work-area convention.
It holds typed aligned title and count buffers. The reboot launch workspace is
also the SDK's 256-byte IPC workspace. No objects were added to move .data.

The SDK declaration of DVDReadAbsAsyncForBS has a sixth priority parameter,
but the implementation ignores it and this IPL object passes five arguments.
BS2_MACH_FIVE_ARG_READ is defined only by BS2Mach.c and guards the declaration
in the shared header. Other units keep their original declaration and output.
The NAND callback now declares its real second callback parameter. Passing NULL
on direct error notifications restores the missing r4 argument setup without
changing the already exact callback body.

## Remaining-function attempt coverage

Every remaining function has at least three distinct source-level attempts.
Percentages are advisory objdiff scores from the quick gates; none is called an
exact match. Final instruction counts come from fresh ctxdiff calls.

### Run

1. Per-block do/while DCZeroRange/DCFlushRange, then entry call: 28/43
   instructions; objdiff reports None.
2. Counted for loop over cache blocks: objdiff 0.88372093%; register clearing,
   stack replacement and LR handoff are still absent.
3. Bulk cache zero/flush followed by entry: 25/43 instructions, score None.
   Retained the per-block form to preserve the target's cache-operation order.
   The GPR-clearing trampoline cannot be expressed as ordinary portable C.

### BS2StartGame

1. Target-shaped nested error branches with empty polling loops: 96.48855%,
   387/393 instructions. The compiler hoists reads out of unqualified polls.
2. Switch dispatch for disk/partition results: 94.18575%, 396/393 instructions.
3. Restored nested branches, used DVDGetCommandBlockStatus for the cover wait
   and interrupt synchronization in low-level callback waits: 93.178116%,
   406/393 instructions. This keeps polling functional without new volatile.
   Compiler __sync/__isync intrinsics restore the real loader barriers without
   adding asm functions or blocks. Final NAND callback ABI correction gives
   95.496185%, 401/393. Calls and register scheduling still differ.

### BS2StartGCGame

1. Configuration/SRAM/MIOS implementation: 95.26755%, 228/228 instructions.
2. Reverse multiplication operands and pass the MIOS title as a real 64-bit
   vararg, rather than unrelated 32-bit arguments: 95.4386%, 227/228.
3. Separate seconds/timerFrequency locals and use the DVD status API for the
   cover wait: 98.11404%, 227/228. Retained this functional form. Differences
   include the polling call, the target's additional MMIO read, and scheduling.

### BS2NANDDivideCallback

1. Update transferred count, advance buffer, and retain separate full/final
   chunk paths: 85.03906%.
2. Cache the remaining length in a local shared across the paths: 70.859375%,
   119/128. This changes allocation and removes more of the target's reloads.
3. Use typed file/buffer/completion globals and advance buffer before account
   update: 85.0%. Final form retains the typed state but restores accounting
   before buffer advance: 85.03906%, 119/128. Nine target instructions remain
   missing, chiefly global reloads and callback setup ordering.

### BS2NANDDivideReadAsync

1. Original request setup order plus a total-length temporary: 60.31915%,
   45/47. Two target reload instructions are absent.
2. Compare the stored total directly, removing the temporary: 60.31915%,
   45/47. No improvement; optimizer produces the same sequence.
3. Typed request globals and file/buffer/length-first initialization:
   60.29787%, 45/47. Retained readable typed state. Reloads and register/setup
   order remain different.

### BS2NANDDivideWriteAsync

1. Original write setup plus total-length temporary: 60.31915%, 45/47.
2. Direct stored-length comparison: 60.31915%, 45/47; no instruction change.
3. Typed globals and file/buffer/length-first initialization: 60.29787%,
   45/47. Same missing reloads and initialization scheduling as the read path.

### CheckBS2CommandStatus

1. Per-state cache write paths with shared result/exit: 79.655174%, 382/406.
2. Direct returns instead of shared goto exit: 79.655174%, 382/406. No change.
3. Compute the partition chunk length once from DVDGameTOC fields:
   78.94089%. Final correct two-argument NAND callback notifications yield
   80.133%, 387/406. Target retains repeated cache-length reloads, and setup
   scheduling remains different. No volatile was added to manufacture them.

### BS2Tick

1. Complete switch in source-token order, typed fields and signed time checks:
   74.99381%, 1896/1940. All 91 string contents match.
2. Four-byte title array, real partition iteration, correct layout global and
   cover-block reset: 75.79124%, 1904/1940. All string offsets also match.
3. Region dispatch as readable switches and a forward ticket-byte scan:
   75.50567%, 1906/1940. Retained the simpler switches and typed scan. Final
   callback ABI/state cleanup gives 74.78608%, 1905/1940. Register allocation,
   branch scheduling, and remaining reloads differ across many states.

## Fresh exact-function verification

- BS2ESGetTicketViews: 71/71 instructions, diffs 0.
- BS2Reboot: 137/137 instructions, diffs 0.
- CheckDVDCommandStatus: 102/102 instructions, diffs 0.
- BS2InquiryAsync: 39/39 instructions, diffs 0.
- BS2ReadDiskID: 39/39 instructions, diffs 0.

The original 16 exact functions remain exact. Final quick gate: 21/29 exact,
4052/16980 code bytes, 155504/158528 data bytes, zero regressions, zero forbidden
additions and zero readability warnings. The unit remains NonMatching.

Final full, non-quick gate: GATE PASS. Full build succeeds, main.dol SHA1 is
26116613f624061ba99c8d1a299aaa6efa85670d, regressions 0, forbidden additions 0,
readability warnings 0. No function or unit is claimed complete below 100%.
