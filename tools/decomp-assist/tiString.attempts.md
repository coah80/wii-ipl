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
# tiString attempts

## inputChar mode-3 indexed block (upstream main @10146c1b)

- Base emits `li r6,0; sth r6,0x10; slwi r0,r6,1; addi r5,r1,0x10;
  sthx r4,r5,r0; addi r6,r6,1; mr r4,r5; li r5,0; slwi r0,r6,1;
  clrlwi r29,r6; sthx r5,r4,r0; sth r5,0x42` — input[count] INDEXED
  stores with count a register-born (li+addi) SYMBOLIC web. MWCC folds
  the FIRST store to immediate offset (count=0 proven) but keeps later
  stores indexed — index var must be non-const-folded.
- Decode: orig's mode-3 path is NOT CharacterOutput (inlines to folded
  immediates). It's `count=0; input[count]=0; input[count++]=ch;
  input[count]=0; count` — semantics confirmed; the wall is making
  count's web symbolic.
- ~13 forms: u16/u32/int index locals (all const-propped), struct-with-
  inline-buffer member index (stays MEMORY: real stw/lwz — too far),
  CharacterOutput direct + pointer-call (fully promotes + folds),
  post-inc index (folds). Register-born symbolic web needs phi/call/
  member-load provenance — none found that emits base's li-born shape.
