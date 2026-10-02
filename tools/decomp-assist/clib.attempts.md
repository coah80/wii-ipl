# clib leaf — round-2 findings (agent/w0929/clib)

## Solved this round

- **zi8cinfo → Matching (whole-unit 100%)**. `Zi8GetSInfo` needed two levers
  together: `volatile int extraCount;` (forces the stack stw/lwz orig has)
  and the fused decrement `outputBuffer[(ziU8)--outputCount] = 0;` (lets MWCC
  schedule `li r3,0` before the `subi` — orig's order). 133/133 insn-identical.
- **zi8getc2 all data sections 100%** (`ziFuzzyZYPairs` struct sizing): orig's
  `Zi8ZYdefaultFuzzyPairs` object is 8B, not 4B — the struct has 12 real bit
  fields (added `dANDt`) plus `reserved : 20`. By-value param codegen
  unchanged (verified instruction-identical); no regression on the ~20 other
  units including zitypes.h.
- **zidawg1 GetGraphInfo 80.8 → ~95+**: three real levers —
  (a) u16 pair compares must be `int`/`ziS32`-typed on the RHS cast (orig uses
      `cmpw`, not `cmplw` + `clrlwi`);
  (b) `entry >= end` operand order (orig `cmplw entry,end;bge`);
  (c) early exits are `return 0` (orig emits `li r3,0` direct-return blocks),
      not `result=0; goto done`.
  Residual: `||` block layout + regalloc, ~4 insns.
- **zidawg1 GetChild 93.3 → ~97+**: orig folds `+0x8000` as `addis +1` /
  `addi -0x8000` applied to `(hi<<16 + mid<<8)` BEFORE adding `b2` — the
  two-statement form `offset = ... + 0x8000; offset += b2;` reproduces it.
  Residual: pure regname/scheduling.

## Extraction artifacts (no source lever)

- **zikorean .data 17.2%**: orig's extracted zikorean.o contains a THIRD
  jumptable at .data+0xf8 (10 entries) whose relocs target `Zi8_81483118` —
  a zkokeyp function. orig's zkokeyp.o has NO .data at all. The table bytes
  were attributed to zikorean's slice by the extractor; cannot be emitted
  from zikorean.c (its 3 fns are already 100%).
- **extab/extabindex ~92-97% residuals** on several units — symbol-extent
  artifacts (byte-identical content where comparable).

## Systematic tie-break family (documented, unfixed)

- **Callee-reg home shift**: orig homes the loop counter/local in the FIRST
  callee reg (r26) and args after (r27+); MWCC homes args first. Recurs in
  zi8dawg MatchROMdata1, zmtkey, zi8getc2 (2 fns), zoemdata Zi8MatchOEMdata
  (4-way swap, 192/192 insn-identical otherwise), zi8match, zkokeyp fns.
- zi8alpha Zi8AlphaGetCandidates (3946 insns): mostly uniform +4 stack-slot
  shift (orig has one more 4-byte local slot) + a few bound-form diffs
  (`>0xF010` vs `>=0xF011`, `<=1` vs `<2`) + one missing subf-rewind block.
- ziswordw Zi8IsWordW 83.3: orig homes call result in callee reg + keeps a
  selector var in r27; mine spills via ziU8 narrowing — needs deeper decode.

## Old-tip adoption notes

Old leaf tip f2afe0e8 beat upstream on: zoemdata +34.2, ziswordw +10.5,
zi8uwd +7.3, zidawg1 +1.7, zi8pud2 +0.7, zi81key/zmtkey marginal.
Upstream won on: zi8alpha +4.5, zi8cgetc +16, zconvert +0.4, zkokeyp +0.1.

## zi81key Get1KeyPressCandidates mr+clrlwi staging wall (~10 forms)

Base pattern at each `Zi8IsMatch1Key(...,Zi8GetPCode(pt,ph),...)` site:
`bl GetPCode; mr r5,r3; <arg1/arg2 setup>; clrlwi r5,r5,0x10; bl` — call result
parked RAW in the arg3 reg, narrowed at the marshal slot. Mine fuses:
`clrlwi r5,r3,0x10` at call exit. Tried: `(ziU16)` cast (folds), `& 0xffff` mask
(folds into same fused clrlwi), u32/s32 extern decl + mask (still fused),
`Zi8UInt/ziU16/int/register pcode` inner-scope local (all SPILL to stack —
named locals never stay in volatile arg regs in this fn), `(ziU16)(ziU32)` cast
chain (folds), ziU16 param on IsMatch1Key (breaks callee: +3 insns inside).
The stage-vs-fuse choice is MWCC's arg-scheduling: it narrows at call-exit when
r3 is dead, at marshal-slot only when the raw web escapes — and no reachable
source form makes the u16 result web escape. Same wall family as zi8cgetc's
22 "return-value move displacement" diffs. UNSOLVED.
