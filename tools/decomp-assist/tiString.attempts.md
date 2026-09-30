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

## inputChar mode==3 block — session 3

Base emits `input[0]=0` direct store, dead `cmplwi ch,0xa`, then `input[i]=ch`
via indexed `sthx` with i=0 in a reg, `i++`, `input[i]=0`, `count=i`,
`mOutput[0]=0`. For the indexed stores to survive, the index must be a variable
MWCC cannot constant-fold yet provably zero. Tried and ALL fold to direct
stores: u16/int/u32 index locals, `i++`/`++i` mutation, if/else identical arms,
`(ch==10)?10:ch` ternary (keeps compare but adds select insns), function-scope
shared `inputIndex` across the goto boundary, `static_cast<u8>` index casts,
`input[i&0xff]`, do-while(0) loop form. MWCC const-props through all of them.
The dead `cmplwi` + indexed-store pair has no reachable source form; retained
the readable direct-store version (125v136 insns).
