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

## clib2 session (zidawg1 + zi8pud2 decodes)

### zidawg1 (unit fuzzy 94.45 -> 95.27)
- ZiDAWGGetGraphInfo 81.8 -> 99.63: shared-fail `||` guard (`if ((e0<<8)+e1 != 0 || (e2<<8)+e3 != 0) return 0;`) gives orig's two-branch-one-block layout; else-return-wrap (`if (!(range)) { while-loop } else { return 0; }`) produces orig's cold-block ordering where plain early-return doesn't; inner scan is a compound `while ((ziU32)entry < end && *keys != (ziS32)((entry[2]<<8)+entry[3]))` (orig enters mid-body via forward b); byte-packed result needs paren grouping `(graph + (entry[4]<<16)) + ((entry[5]<<8)+entry[6])`.
- ZiDAWGgetCHARattribute 95.5 -> 98.33: `attribute |= ((ziU32)(ziU8)A << 8) + B` merged-assign form (single OR'd pair).
- ZiDAWGGetChild 93.6 -> 93.9: explicit `(ziU16)` cast on table load reproduces orig's redundant clrlwi-into-home.
- ZiDAWGGetSibling 86.9 -> 89.31: cursor-walker model — a separate `cursor` web walks the node bytes (orig r3 volatile), `offset` counts advances, `node` stays at base (orig r28 callee), result `node += offset` / `node = offset + (node + b2)`. Packed-add tree: write `offset = b0x + b1x; offset += 0x8000; node += b2; node = offset + node;` — MWCC reassociates a one-line expression folding +0x8000 onto the b1 term.
- Residual (documented wall): volatile-vs-callee web choice — orig homes `node` in r28 and walks `cursor` in r3 (volatile); MWCC picks the opposite. This is the "local-before-param" family: no calls in fn, allocator assigns homes purely by internal weights.

### zi8pud2 (unit fuzzy 81.7 -> 84.6, ZHS fn 72.6 -> 77.0)
- `length &= 0x7F` before `length *= 2` is dead — `(x<<1)&0xff ≡ (x&0x7f)<<1`; MWCC doesn't fold the mask. Removing it reproduces orig's `slwi+clrlwi`.
- Section-scan loop is `while (index < count) { if (lang==match) break; section++; index++; }` — break-on-match at top, count-check at bottom. A compound `A && B` while emits the wrong check order.
- Three consecutive `if (cond) goto L` statements merge into || evaluation with `beq`-to-next polarity; orig's `bne`-past shape comes from the nested-if form `if (A) { if (B) goto L } else { if (C) goto L }`.
- ZHS byte-copy loop advances `index` between the two stores (`[i]=w[i]; i++; [i]=w[i]; i++`) — `index+1` addressing emits recompute-adds instead.
- Residual: fn-wide web permutation (orig homes `output` as a per-use stack spill `lwz r3,0x10(r1)`; mine keeps it callee) + the `next:` cold-block placement — allocator/scheduling family.

### other units checked this session — all pure web-rotation ties (documented family)
- zi8getc2: Zi8IsDupWChar (8 diffs, r27<->r28 param/local swap), Zi8GetDataSignature (9, 3-web cyclic)
- zi8match: Zi8GetPyPhonetic (uniform r-shift), Zi8GetPyFinal (8, volatile operand-order)
- zconvert: UC2WC (8, r25<->r27), UC2Key (18, r27<->r28)
- zi8dawg: Zi8MatchROMdata1 (5, r26<->r27)

## ziswordw IsWordW formats-init decode (w0930)
- orig's 8-byte `formats` init reads 8 SEPARATE 1-byte GLOBAL objects in .sdata2 (lbl_81695018-1F),
  not a pooled literal. Reproduce: `__declspec(section ".sdata2") ziU8 name = v;` (non-const!) file-scope
  globals + per-element `formats[i] = name_i;` statements. Plain `const` folds to pooled literal @33 or
  `li` immediates; `static const` pools too; array-indexed init-list also pools. declspec non-const is the
  only form that emits per-symbol lbz/stb pairs (orig pairing: 2 loads then 2 stores).
- orig zero-inits 5 locals (count/offset/group/remaining/value = stw+stw+stb+stb+sth at fn top) —
  declare them `= 0`.
- emission order: decl-init zeros -> formats copies -> saved ZI_WORK loads -> search.* = 0 -> Zi8LogError.
- Residual: MWCC remats `li r0,0` per store (orig keeps r0=0 live across contiguous zero-stores — the
  intervening formats loads clobber r0 in my scheduling); r26-vs-r27 web rotation. 83.3 -> 83.7.
