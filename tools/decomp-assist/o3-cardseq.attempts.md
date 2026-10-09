# o3-cardseq attempts

Worktree sol-med, branch agent/w1009/o3-cardseq, started at origin/main dbbdc3dd.
Unit src/scene/cardSequence/iplCardSequence: loadCardFileIcons and cardThreadMain,
each 2 instructions off at the start. Both are now exact, the unit is flipped to
Matching, and the DOL hash is unchanged.

## loadCardFileIcons: exact

Start: instructions 135-136 differ (`add r10, r4, r30` / `stb r3, -0x6fba(r10)` where the
target uses r4).

Cause, from a per-pass PCode dump (/tmp/o2-chansvm/mwdbgp gc3p.py, copied privately):
the block holding the first icon store reaches the pre-allocation list scheduler as

    li shift, 0 / li hasTlut, 0 / li iconImageSize, 0 / li iconCount, 0
    lwz sThread / addis / add / add / stb (unk_0x02 = 0) ...
    li icon, 0 (dead after the CTR conversion) / add offset / li 8 / mtctr

The address chain leaves six free issue slots before the first `stb`. Six fillers compete
for them (shift's zero, the CTR count, the hoisted offset, and the three zero inits), so
`li iconCount, 0` lands at cycle 4, before the store. iconCount then interferes with the
store address, which cannot take r4.

The scheduler breaks ties by input order. When the dead loop-counter init `icon = 0` comes
before `iconCount = 0` in the IR, it takes the cycle-4 slot, `li iconCount, 0` moves
after the store, and the address gets r4. The dead `li` is removed before allocation, which
is why the target shows an empty slot there.

Fix: `for (iconCount = icon = 0; icon < CARD_ICON_MAX; ++icon)`. The chained assignment
evaluates `icon = 0` first. Exact spellings found:

- `for (iconCount = icon = 0; ...)` (kept).
- `iconCount = icon = 0;` or `icon = 0; iconCount = 0;` before an empty for-init.
- a while loop with `icon = 0; iconCount = 0;` before it.
- `for (icon = 0, iconCount = 0; ...)` (comma operator, not used).

Not exact: `icon = 0;` before `shift = 0` (383 diffs); moving `shift = 0` down with the
counters (10 diffs).

A srcsearch run (4 seeds, 40 minutes, --own loadCardIconImages) found nothing before this.

## cardThreadMain: exact

Start: case 10 builds the reply as `li r4, 0x100; rlwimi r4, r19, 0, 24, 31`. The
target has `mr r4, r19; rlwimi r4, r25, 8, 16, 23`: it inserts validState's own register
(r25) into a copy of command.

### Why the target needs a scoped `opt_propagation off`

- The backend cannot fold a constant into an `rlwimi` operand. The backend's own constant
  propagation still folds `(v << 8) | x` to `ori 0x100` when it is not an insert.
  So r25 in the insert means the IR handed to the backend still read `validState`.
- The 3.0a5.2 IR copy/constant propagation (`mwcceppc.exe` 0x5f4810, disassembled; GC 1.x
  source in rayanht/mwcc IroPropagate.c for comparison) replaces every plain read whose
  reaching definition is a constant. Its only use-side guards are the Assigned flag, a
  sibling-assignment check (0x5f5480) and a size-compatible type check (0x5b7980). Calls
  kill only address-taken or global candidates. Unlike GC 1.x, 3.0 propagates into call
  arguments too (h2 test: `ori r4, r44, 256` already in backend-00).
- More than 600 earlier trials and about 60 here tried plain locals of every integer type,
  enum, bool, unions, one-element arrays, pointer and reference helpers, intrinsics, and
  assignment placement. Every one is propagated. A diagnostic `opt_propagation off` gives
  the target insert with the natural spelling.

The same function-scoped pragma also reproduces the rest of the target allocation without
the old workarounds. The `command = (message >> 14) & 4` reuse in case 0 and the
`sendValidityResponse` union are both gone.

### Source shape that matches under the pragma

- Reply: `(OSMessage)((validState << 8) | (u8)command)` with `u8 validState` and
  `u32 command`. The `(u8)` cast tells the backend that bits 8-15 are clear, which makes
  the `mr` + `rlwimi` form. Without the cast, or with `u8 command`, there are 3 diffs.
- One inline helper per command: `mountCardSlot` (case 0), `formatCardSlot` (case 1),
  `deleteCardFile` (case 4), `countCardTitleBlocks` (case 12) and `listCardFiles`. Under the
  pragma, mwdbg traces show inline-helper locals are coloured first, in reverse creation
  order, and named locals last. The target needs case 0's slot, file and listing counter
  early, and the long-lived error result late.
- `mountCardSlot` uses one `result` variable for every call. Lifetime analysis splits off
  the long-lived error web as a late temp, which gets r20 like the target. A separate
  `scanResult` local in the helper gets r26 (4 diffs).
- `mountCardSlot` takes `mountDir`, `listingDir` and `fileName` by reference.
  Declaring them inside the helper moves them on the stack (15 diffs).

Progress: 2 diffs -> 29 (natural rewrite under the pragma) -> 11 (declaration order) ->
5 (formatCardSlot) -> 4 (mountCardSlot) -> 0 (single `result`).

## Harness note

`wibo sjiswrap.exe mwcceppc.exe` silently writes no object (exit 0) for some source file
names (`D1.cpp`, `W1.cpp`, `X1.cpp`, ...). The same text under another name compiles.
Early "compile failures" in this log were this, not the compiler.

## Final state

- cardThreadMain 301/301 and loadCardFileIcons 512/512, 0 differing; ctxdiff diffs 0.
- Pool identical (43); unit 30/30 instruction-exact; objdiff code 9852/9852, data
  1496/1496; every section at 100.
- configure.py: iplCardSequence NonMatching -> Matching. Full build ok, unit linked,
  main.dol SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
- `gate.py src/scene/cardSequence/iplCardSequence --quick`: GATE PASS, 0 regressions,
  0 forbidden patterns, 0 readability warnings.
