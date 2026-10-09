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

## inputChar (w1011/fossils wave) — symbolic-index DECODED, dead-compare wall remains
Best: 135/136 (was 125/136). The winning source form:
```cpp
u32 inputIndex = 0;
input[inputIndex] = 0;
if (ch == 10) { inputIndex = 0; }
input[inputIndex] = ch;
++inputIndex;
input[inputIndex] = 0;
count = inputIndex;              // u16 count: emits clrlwi r29,r6,0x10
mKanaStream.mOutput[0] = 0;
```
The `if(ch==10) inputIndex=0` creates an SSA phi on inputIndex -> MWCC keeps the
index SYMBOLIC -> reproduces orig's `slwi/sthx/addi/slwi/clrlwi/sthx` sequence
and the clrlwi count-narrow between the two sthx (u16 count, not int).
REMAINING GAP = dead `cmplwi r4,0xa`: orig emits the compare with NO consuming
branch and NO arm insns. Every arm-body variant fails both ways:
- arm with any real op (`inputIndex=0`, `mOutput[0]=0`, `count=inputIndex`,
  `input[0]=0`): MWCC keeps `bne` + arm insns (mine 135 = +bne+li vs orig).
- empty arm `if(ch==10){}`, self-assign `inputIndex=inputIndex`, dead-on-arrival
  `count=inputIndex` (overwritten unconditionally after), identical-arms
  if/else, ternary `(ch==10)?0:inputIndex`: MWCC merges arms BEFORE emitting the
  compare -> compare dies too (125).
A compare-without-branch fossil is not producible by any tested source form on
MWCC 3.0a5.2. Open question: whether orig's compare came from a non-if codegen
path (peeled loop head, && short-circuit whose second test folds, or an
MWCC-version difference).

## inputChar (w1011b) — ppc_iro_level pragma + insn-equal 136/136
`#pragma push` + `#pragma ppc_iro_level 4` around inputChar + `wchar_t* inputBuf
= input` second-pointer for the last store + `if(ch==10) inputIndex=0` phi-arm
=> insn-equal 136/136 (was 125/136). Orig's symbolic index IS a phi.
Remaining 7 diffs: orig's `if(ch==10)` emits ONLY the cmplwi (no bne, no arm
insns — a true compare fossil), orig's second-store base is `mr r4,r5` copy vs
my addi rematerialization, plus r5<->r6 zero-web color and tail clrlwi position.
Fossil-arm variants that ALL fail (arm must produce phi + zero insns): empty
arm (folds everything), inputIndex=inputIndex (phi collapses), (ch==10)?0:i /
?i:0 ternaries (diamond or full fold), input[0]=0 arm (emits sth),
input[inputIndex]=0 arm (emits sthx), opt_dead_code/opt_dead_assignments/
opt_common_subexpressions pragmas at IRO-0 (all still bne+li), iro 0-4.
Compare-without-branch remains non-producible; likely needs the arm's value to
materialize in the SAME register as the init (a CSE level mine never reaches).

## Wave w1011c — scheduling pragmas on inputChar (no movement)

On the 136/136 insn-equal form (IRO-4 + inputBuf + phi arm, 7 diff ops):
- `scheduling 604` → 18d (worse); `scheduling 750`/`schedule_twice on` → 7d (inert)
- `optimization_level 0` → 151 insns; `level 2` → 139 insns (+3)
- TU `-ipa function`/`-ipa off` → 7d (inert)
- TU `-O4,s` or NO extra_cflags → 132 insns — the committed `extra_cflags=["-O4,p"]` is
  LOAD-BEARING: removing it drops 4 insns (kills the symbolic-index sequence)
- bool-assign arm `u32 v=(ch==10); inputIndex=v-v` → cntlzw materialization (135,11d) — rejected
