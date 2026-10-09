# tiString attempts

Initial reconstruction uses the sibling tiString and tiUtil headers, real member definitions and compiler-generated vtables. The unit has no string literals; both pools are empty and identical. The normal derived destructor emits its vtable before the base vtable, restoring all 288 data bytes. The extracted target omits the derived destructor body; this additional ordinary destructor will need consideration during the later linking phase.

## insert
1. Separate getLength temporary and typed string indexing: 79/79 instructions, eight scheduling/register differences.
2. Precompute a tail pointer before getLength: 76/79 instructions, additional callee-saved register and address lifetime differences.
3. Precompute an element index: 79/79, same eight differences.
4. Put getLength directly in wcsncpy's length argument: 79/79, zero differences; retained.

## inputChar
1. Remove inherited scratch source's volatile buffer pointer, use an ordinary pointer and u32 count: 126/136. Kana conversion matches; Hangul path folds indexed stores and cursor additions lose two narrowing instructions.
2. u16 count and separate newline/ordinary character branches: 126/136, same differences. Compiler folds the equivalent branches; discarded the redundant condition.
3. Direct array indexing with no buffer alias, u16 count: 125/136. Hangul output collapses to direct stores and constant count; retained the readable version. Remaining mismatch is the Hangul output indexing/count lifetime and subsequent cursor-add narrowing, not strings or data.

## character predicates
The sibling util declarations return bool, while target callers normalize an integer result. Guarded u32 declarations preserve every other translation unit and make all three predicates 16/16 with zero differences.

## inputChar (w1010 orchestrator probe) — indexed-store + dead-compare fossil
Orig mode==3 block (this->0x24==3) emits: `sth r6,0x10` (input[0]=0, r6=0 reused as
value), `cmplwi r4,0xa` (DEAD compare — no branch consumes it), then indexed stores
`slwi r0,r6,1; sthx r4,buf,r0; addi r6,1; slwi r0,r6,1; clrlwi r29,r6,0x10; sthx r5,buf,r0`
= input[i]=ch; i++; input[i]=0 with the index kept SYMBOLIC despite li i,0.
Ours: direct-offset `sth r4,0x10; li r29,1; sth r5,0x12` (125 vs 136 insns).
Tried: `input[i]=ch; i++; input[i]=0; count=i` — MWCC constant-folds i to 0,
re-emits direct offsets. Index must be runtime-opaque in orig (loop bound from a
call result, or a non-foldable form). Dead `cmplwi r4,0xa` matches the documented
dead-compare-fossil family (both-branch merge). Also: count lands in r29 via
clrlwi (u16) — count is i.
Unresolved: what source produces symbolic-index stores + dead compare.

## inputChar (w1009 wave — post-#1319 structure)
Base: 136 insns. g-keyboard baseline (u16 mCount member + newline reset): 13 diffs
at 66-78 — rlwinm per-access masks (u16 index) + live bne on the newline compare.

Decode landed: mCount is a **u32** member — orig emits `slwi` (no mask) on the
index and ONE `clrlwi r29` (u16 narrow for count), not per-access rlwinm.
`u32 mCount` removes all mask diffs -> 135 insns vs 136.

Remaining (unresolved):
1. `if (ch == L'\n') mCount = 0;` — orig's compare is a DEAD fossil (cmplwi kept,
   no consuming branch, block straight-line). Tried and rejected: mpOutput[0]=0 /
   mpOutput[mCount]=0 conditional stores (MWCC never dedups conditional memory
   stores — kept `bne; sth`); ternary/switch/empty-if/goto-next (frontend folds
   compare AND kills the mCount phi -> index collapses to direct sth, mode3 block
   merges into else shape); mCount=0 else=0 (same collapse); adjacent backward
   redundant store (kept bne;sth). Constraint pair: mCount must stay OPAQUE
   (phi/web, else index folds) AND the if's only effect must die late. The live
   `if(ch=='\n') mCount=0` phi is currently what keeps the index symbolic —
   any fossil form that kills the branch also kills the phi. Needs the reset to
   target something else (member load/codegen temp per orchestrator hint).
2. Cursor add re-narrow x2: base emits `clrlwi r0,r29,0x10` before
   `mCursorStart + count` — count's u32/s32 web is UNPROVEN at the use (phi
   provenance lost). Tried: u32/s32/u16 count + static_cast<u16>, (u16)(s32)
   double-cast, & 0xffff, plain +count — MWCC folds all since all 3 phi inputs
   (clrlwi-0x18 kana, clrlwi-0x10 mode3, li 1 else) are provably narrow. Base's
   count web must be dirty through a different mechanism (member web? call
   boundary? different var shape).
3. 1 missing insn in mode3 tail: base has `mr r4,r5` + `li r5,0` (buf re-copied
   into r4 for the terminator store) — mine shares r5 (append and finish inlined
   reads coalesce the mpOutput web).

## inputChar — opt_propagation wave (w1009, post-#1323)
Scoped `#pragma opt_propagation off` around inputChar + u32 mCount: block shape
changed slightly (li/sth/addi ordering) but no wall cracked — live bne persists,
re-narrow still folds, mr r4,r5 still missing. Pragma does not reproduce the
fossil (compare emission is frontend, before IR prop runs).

`finish(wchar_t* p)` + `output.finish(input)`: emits `addi r4,r1,0x10` for the
buf web — SEPARATE web created (operand order matches base sthx r5,r4) but
remat, not `mr r4,r5`. `finish(output.mpOutput)` folds fully (single web). The
`mr` is a codegen remat-vs-copy tie: buf#2's web is a COPY of r5 in base —
needs a reg-valued (non-remat) arg source; no honest source form found.

Dead-cmplwi fossil — ~12 more mechanisms rejected:
- `if(ch=='\n') mCount=0` arm stays LIVE in every member shape (u32 member,
  ctor-reordered init, hoisted input[0]=0). MWCC does NOT value-track member
  stores post-inline (`cmpwi r6,0` emitted on provably-0 mCount proves it) —
  so the arm can never be redundant-eliminated.
- `if(ch=='\n') mOutput[0]=0` arm (killed-by-later-unconditional member):
  `bne;sth` kept — no member-store DSE across the block.
- `if(ch=='\n') count=0` arm (var killed by later `count=finish()`): arm does
  die BUT removing the mCount write collapses the index web -> input[0] fold.
- `i=i`, `mCount=mCount` self-stores: deleted -> compare deleted -> collapse.
- nested `if(mCount!=0) mCount=0`: inner stays live (+3).
- `input[i]=0` arm (indexed, dedup vs ctor): index folds (single-def) -> collapse.
Wall restated: index needs mCount phi'd (multi-def -> unprovable), arm must be
dead (no insns) — but every arm that dies removes the phi input. Any dead-arm
form must leave a SECOND mCount def that MWCC can't prove equal — no such form
found for var/member/local-arm writes.

u32 mCount retained (removes all rlwinm per-access mask diffs): 135 vs base 136.

## inputChar — orchestrator-diff wave 2 (w1009)
Plain-local decode confirmed pieces:
- `u32 i = 0; input[0] = i;` — stores i's web directly: `sth r5,0x10` shares ONE
  web with `slwi r0,r5` — reproduces base's single `li` web (vs two separate li
  webs in the member form). With `if(ch=='\n') i=0` arm kept: symbolic slwi +
  shared store web both landed — but arm stays LIVE (bne;li) as always.
- `i = (ch=='\n') ? 0 : i` select: folds entirely (compare deleted, index
  collapses to input[0]).
- `i = output.mCount` overwrite: member-read folds to init-0 -> collapse.
- `if(ch=='\n') input[i]=0` arm (dedup vs later input[i]=ch): i single-def ->
  index folds -> collapse.
Established: the arm's def is the ONLY phi input keeping `input[i]` symbolic;
MWCC 3.0a5.2 eliminates neither redundant var-stores nor member stores, and
deleting the arm's def always collapses the phi -> literal fold. The dead
cmplwi needs a pass ordering where the phi survives the arm's deletion —
no source form found. ~50 total probe forms on this wall across sessions.

## inputChar fossil decode (session ~197k, leaf update)

### SOLVED — the dead-`cmplwi` fossil (was the main wall, ~50 prior probes)
`cmplwi ch,0xa` survives with NO branch via TWO mechanisms combined:
1. **2-pred join** (o-tistr model): `if (mode == 3) { ia[1] = ia[0]; }` — a dead a2r
   store (`u32 ia[2]` local array). `ia[0]` never written → both elements undef →
   the store dies AT EMISSION but the if-block survives as a separate block →
   the `cmplwi` block has 2 predecessors at every MergeAdjacentBlocks pass.
2. **undef a2r read**: `if (ch == '\n') { i = ia[1]; }` — `i = ia[1]` reads an
   undef array element → ZERO instructions emitted (undef web) but `i`'s phi
   keeps a second reaching def → `input[i]` stays a symbolic index (no fold
   to offsets) AND the `\n`-compare survives branch-free.
   Compiler warns (10185) 'ia' is not initialized — warning only, not banned.

### SOLVED — epilogue `clrlwi r0,r29` re-narrow (2 sites)
`+ (u16)count` emits `clrlwi` iff count's phi has a NON-NARROW input. `count` u32
+ `count = i` (u32 index → `addi`/`mr` — non-narrow web) → emits at both sites.
u16 count / `count = (u16)i` / u8-return / `&0xff` / `(s32)` / `(u32)` double-cast
all produce narrow-flagged webs → `(u16)` folds → `add` only.
u8-return: `KPRPutChar` returns u8 — `count = ret & 0xff` — narrow everywhere.

### SOLVED — `input[0] = i` single-web zero
`input[0] = i` (the VARIABLE) produces orig's ONE `li`/`sth`/`slwi` web shared
by the store and the index. Literal `input[0] = 0` creates a second li web.

### UNSOLVED — `clrlwi r29` def vs `addi r29` (~1 insn)
`count = i` (u32,u32) emits `addi` — needed non-narrow for epilogue.
`count = (u16)i` emits `clrlwi` but flags count narrow → epilogue clrlwi dies.
Contradiction for one var; split-var models: `j = (u16)i` coalesces into the
`addi` web or gets dead-eliminated (j unused); `u16 j` + `j = i` emits `clrlwi`
but u16-var promotions elide the use-side too.
Candidate left untried: `count` live via a use that keeps the `(u16)` def but
adds no insns — not found.

### UNSOLVED — `mr r4,r5` buf-copy (1 insn)
Base: `addi r5,r1,0x10` buf→r5; `mr r4,r5` copies buf→r4 because `li r5,0`
(zero-web for input[i]=0 + sth 0x42) then clobbers r5 → allocator copy-out.
Mine: buf=r6, zero=r4 — no conflict → sthx uses r6 twice.
- `wchar_t *q = input` mid-block → `addi r4,r1,0x10` remat (colors match, wrong
  insn — remat not mr).
- `wchar_t *q = p` → forward-substituted (VN merge) even with
  `#pragma opt_propagation off` (forward-sub is a different pass).
- `q = p` in the `\n` dead arm → arm non-empty → fossil breaks.
Needs: buf + zero homing on same reg to force copy-out — allocator tie.

### Diff state: 134v136 — real diffs: `addi r29`(→clrlwi), missing `mr r4,r5`,
plus operand-color ties (r5/r6/r4 homes) elsewhere.

### Final probes (before swarm #1336 landed it)
- `u16 count` + `count = i` emits the mode-3 `clrlwi r29` def ✓ but every
  epilogue cast form (`(u32)`, `(s32)`, `(u16)`, double-cast) elides to `add`
  — u16-var promotions never materialize a use-side clrlwi.
- `u32 count` + `count = i` + `+ (u16)count` emits BOTH epilogue clrlwis ✓ but
  the mode-3 def is `addi` not `clrlwi` — narrow-def/non-narrow-phi contradiction.
- `wchar_t *p = input` as a named pointer local HOISTS the buf `addi` to block
  top (web born at def); orig never keeps buf in a vreg — it's a remat base at
  each sthx (`input[i]` direct, not p[i]).
- Pure `input[i]` form gets buf mid-block but homes stay swapped: i→r5/buf→r6
  vs orig i→r6/buf→r5 — `li r5,0` never vacates buf → no `mr r4,r5` copy-out.
