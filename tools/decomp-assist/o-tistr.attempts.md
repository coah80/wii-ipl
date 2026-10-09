# o-tistr attempts (tiString Decolated::inputChar)

Worktree data-d5, branch agent/w1009/o-tistr, base 12e857a9. inputChar 13/136 at start and at end.
Scratch: /tmp/o-tistr (bf/run.py variant runner, sched/schedsim.py scheduler model, cap/ per-pass captures
with extra pre-RA hooks 0x4695dd/0x4695ee/0x469602 and global-optimizer start/end hooks).

## Kept

The dispatch is now `if (mode == TM_Kana || mode == TM_Roman) ... else if (mode == TM_Hangul) ... else`
instead of the two gotos and labels. .text and .data are byte-identical to the goto form; inputChar stays 13.

## Why the target's Hangul block is not reachable from any single-block shape

Target: `li r6,0; sth r6,0x10(r1); cmplwi r4,0xa; slwi r0,r6,1; ...`.

1. The scheduler cannot produce `li; sth; cmplwi` from one block. A block {li P; sth P; cmpli; bf} always
   comes out `li; cmpli; sth` (v013 compiles it that way, and the MWCC list-scheduler model with 750 latencies
   li 1, sth 2, cmpli 3 reproduces it: cmpli fills the second IU slot in cycle 0). Without the branch the result
   is the same. GC3's Scheduler_Schedule (0x5995c0) has no "already scheduled" check, and the final call is
   force=1, so every block with more than 2 instructions is rescheduled after RA. The only things removed after
   the final schedule are branches to the next instruction (optimize_branches at emission).
   So in the original, `[li; sth]` and `[cmplwi]` were separate blocks at the final schedule.
2. MergeAdjacentBlocks (0x596960, run in the global optimizer, before RA and after RA) merges a block into
   its successor when the edge is the only successor and the only predecessor. The cmplwi block must therefore
   have had two predecessors (or the `[li; sth]` block two successors) at every merge. This is how the
   dead compare in WADImportDVDExForBS survives in its own block: it is the join block of the previous
   `if (header.tmdSize != 0)`.
3. The split before the cmplwi block must be invisible in the final code. Every compare in the target uses cr0,
   so the entry 0xfffe compare and the kana range compare cannot be reused (a reused cr would get another
   field). Only the mode compare of the `else if` can be reused. Verified: with a function-scope
   `s32 mode = mTranslateMode;` (all other code unchanged, still 13) an inner `if (mode == TM_Hangul)` is
   not folded by IRO and the backend VN reuses the compare: `li r6,0; sth r6,0x10(r1); bne; ...; cmplwi r4,0xa`
   (variant ml1, 72 diffs because both then-blocks keep `li r6,0`). A reloaded member test or a bool computed
   at the top does not work (reload, or a materialized bool).
4. Both then-blocks must be empty by emission, and the index still needs two reaching definitions at both
   constant-propagation passes (otherwise `input[n] = ch` folds to `sth r4,0x10(r1)`).
   - GC3 value numbering never deletes or replaces a redundant `li` of a named local. Even with the
     function-start zero record killed by a call, `n = 0` in the then-block survives (variant callbreak).
     It deletes only temporaries and array-to-register vregs (the o3 LinePosition mechanism).
   - The store's literal zero only lands in the counter's register when the counter is a named local whose
     2-operand `li` comes first in that block (VN pass 1 merges within the block). A temp or an a2r field is
     replaced by the function-start zero (r5) instead.
   These two facts contradict each other for a single counter, and every shape that empties the then-blocks
   either loses the store register (p1, poc1, poc2, bf1, bf2) or keeps a `li` (ml1, base). A struct-reset
   then-block also makes IRO drop the inner mode test (bf1, m1, m2, modeloc1).
5. count: the use-site `clrlwi r0,r29,0x10` survives only if count's Hangul definition at the first
   constant-propagation pass is not an extension. `lhz` is not treated as extended (probe p3 f1), a `rlwinm`
   is (v001-v003 lose it).

## Other measured shapes (diffs)

switch on mode 120; switch on ch 60 (signed cmpwi); if/else with equal arms folded 73; do/while(false),
goto label, for(;;) break, while(ch=='\n') break 61-72; `((void)0)` then-block folded 73; volatile store 62
(not a barrier); bool flag before the store 72; aggregate-initialized buffers emit stw; empty ifs and single-def
index with opt_dead_code / opt_propagation / opt_common_subs / opt_dead_assignments / opt_lifetimes off: no
change (73); scheduling off 61; peephole off 137-140; optimization_level 0-3 127-151.

Next idea not finished: a then-block whose definition is a copy `n = m` with `m` copied from `n` in the
newline block after a join (const-prop cannot fold it, VN deletes it). It needs a second join before the
copy, so the same contradiction comes back.

## Closest structural lead (40 diffs, not kept)

With the function-scope `mode` local, `LinePosition position; position.index = 0; input[0] = position.index;`
then `if (mode == TM_Hangul) { position.index = 0; }` and `u32 n = position.index;` gives the target's first
block exactly (`li r6,0; sth r6,0x10(r1)`, then a `bne` on the reused cr0). Two things still differ: the inner
then-block keeps `li r6,0` (IRO scalarizes the field into a named local, which VN never deletes), and IRO's
dead-store pass removes a newline then-block that only resets the position, so the `cmplwi` disappears.
The gate for this round passed with the dispatch cleanup only (0 regressions, DOL hash unchanged).

## Round b (worktree data-d5, branch agent/w1009/o-tistr2, base f1d824ac)

Scratch: /tmp/o-tistr/r2 (run2.py parallel variant runner, s1..s33 variant sets, captures in
/tmp/o-tistr/cap/run-b-*). Owner ruling: the `s32 mode` re-test is allowed.

### Target block structure, corrected

The target's Hangul code is five blocks at the final schedule, not three:

1. `li r6,0; sth r6,0x10(r1)` then the re-test branch (reused cr0, removed at emission).
2. Re-test then-block, empty.
3. `cmplwi r4,0xa; slwi r0,r6,1; addi r5,r1,0x10; sthx r4,r5,r0; addi r6,r6,1; mr r4,r5` then the newline
   branch. The char store and the pointer copy are in the same block as the newline compare: the
   scheduler moves the independent `cmplwi` to the front. So the original writes the character before the
   newline test, and the terminator after it.
4. Newline then-block, empty.
5. `li r5,0; slwi r0,r6,1; clrlwi r29,r6,0x10; sthx r5,r4,r0; sth r5,0x42(r3); b`.

### GC3 facts measured with per-pass captures (new)

- 0x59a030 (peephole forward, run at optimizer start and before RA) CSEs equal li's inside a block into the
  first one and forwards stack loads from stores in the same block.
- VN (0x5976e0) forwards stores to loads across single-predecessor chains in both runs, deletes a copy or
  load whose destination already holds the value, flattens copy chains (also into named locals), and keys
  records by opcode, flags and operand count. Codegen li has 2 operands, const-prop li 3; codegen addi has 4
  operands, const-prop addi 3. Different shapes never match, pre or post RA.
- Copy propagation (0x621d00) also propagates copies into function-scope named locals.
- Halfword store-to-load forwarding always produces `rlwinm d,s,0,16,31`, even for a zero-extended source.
- A dead store to a constant-initialized one-field POD struct (`LinePosition position = {0};`) survives IRO
  and is removed by array-to-register: that makes the newline then-block empty and leaves the bare `cmplwi`
  exactly as in the target (variants rb-*, nt1, o-*).
- An indexed first store (`input[position.index] = 0;`) hides the store from VN(0), so a re-test then-block
  `n = input[0];` survives both const-prop passes as a second definition of n and is forwarded only by VN(1).
  First block, dead `cmplwi` and empty newline block then match; the re-test block keeps one
  `clrlwi r6,r6,16` (halfword forwarding). Variant rb-a-rd0-pz, 60 diffs (41 without the newline test).
- IRO block-local expression propagation copies a pointer definition into its single use; `&input[k]` forms
  with k from a memory struct become const-prop addi's (3 operands) that survive VN as a separate register
  (ap1), but never turn into `mr`.

### Still open

- Re-test then-block: needs a second definition of the counter that survives both const-prop passes and
  disappears afterwards. Named li never disappears; read-back leaves the halfword `clrlwi`; struct
  (array-to-register) forms put an extra const-prop li in block 1.
- Pointer copy in block 3: copy propagation removes `mr out,p` unless `out` has a second reaching definition
  in the newline block, and that definition has to vanish after the last copy propagation.

### Resolution: EXACT (13 -> 0), tiString linked

Scratch for this part: /tmp/o-tistr/r2/s43..s54 (variant sets), /tmp/o-tistr/r3 (probes, captures
run-main/run-F3, scheduler checks t6..t15 in /tmp/o-tistr/sched).

The "still open" items above were both wrong about the block structure. A list-scheduler model check shows
the target's char store and terminator are ONE block at the final schedule (the second `slwi r0` waits on the
first `sthx` through r0, which puts `li r5,0` before it); a separate terminator block can never give
`mr; li; slwi; clrlwi`. And `cmplwi` first is only possible with the newline test BEFORE the character store,
in its own block. Final structure: `[li n; sth] | [cmplwi] | [char store; mr; terminator]`.

GC3 facts that decided it (disassembled from mwcceppc.exe with /tmp/o-tistr/r2/x86dis.py):
- Extension elimination (0x625170, called from const-prop 0x622a20 for `rlwinm x,y,0,MB,31`) walks every
  reaching definition. It counts lhz/lbz loads, rlwinm with MB 16/24, andi., ori/xori (recursively) and
  non-negative li as zero-extended, and returns 0 for anything else. Copies are NOT looked through. So the
  tail's `clrlwi r0,r29,16` survives only if count's Hangul definition is a `mr` at both const-prop passes.
  A u16 conversion used twice (`composing.length = static_cast<u16>(n); count = n;`) is CSE'd by IRO into a
  temp, count's definition becomes `mr count,temp`, and the allocator coalesces the temp into count, which
  leaves exactly `clrlwi r29,r6,16` (36 -> 6 diffs; variants C2, S3).
- Copy propagation (0x621d00) replaces uses one at a time; a use that is itself a move (flag 0x10) or a
  source redefined before the use blocks it. Value numbering also rewrites uses inside its region, so two
  `&input` computations in one region always collapse to one register.
- The pre-RA pass 0x596850 folds `li x; cmpi x,imm; bc` in one block: always-taken branches become `b`
  (the skipped block keeps its out-edge, so the join stays a join), and never-taken branches are deleted.
  With a never-taken branch over an empty then-block, the char block, the empty block and the terminator
  form a single-predecessor chain: post-RA value numbering turns the terminator's `addi r4,r1,input` into
  `mr r4,r5`, and the post-RA merge makes it one block for the final schedule.
- The compare's `li` must be in the same block, so the always-true test needs a `{0}` struct initialised
  after the character store (probe r2 in /tmp/o-tistr/r3/fold3.cpp reproduces the whole Hangul shape;
  reusing the first struct keeps the compare).

Final source: a one-field `HangulSyllable` aggregate with isEmpty()/clear() (a class with a constructor is
scalarised by IRO and folds everything, 126 insns), `composing` checked before the character and cleared on
newline, `next` checked after it, and the CSE'd u16 length for count. Equivalent exact spellings: K1, L0-L4,
L8, M1, M3, R1, R3, S1, S3, S4, S6, T1-T5.

Link flip: the first full build changed the DOL (faa948f9...). tiString.cpp defined `~Decolated()` out of
line (STB_GLOBAL), so the linker kept tiString's copy instead of the weak one tiInputForm emits at
0x8141BC64. In the original, `~Decolated`, `clear()` and `set()` are inline (all three sit in tiInputForm's
range) and `setLength` is the vtable's key function. Making those three inline for TISTRING_IMPLEMENTATION
(dropping the inline destructor alone loses the vtable: link error) restores the DOL. All weak copies in
tiString.o are dropped at link.

Result: inputChar 0/136 differing, pool identical, ctxdiff 0; tiString 42/42 instruction-exact, code
5176/5176, data 288/288; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Gate: GATE PASS, 0 regressions,
global matched/complete code 100.00%.
