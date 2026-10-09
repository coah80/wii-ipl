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
