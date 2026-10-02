# kbdzi leaf — attempt log (agent/w1007/kbdzi)

Scope: incomplete zi*/kbd* units (NOT ti*/MyTi* — linkgap owns those).

## Landed

### zprepare / Zi8PrepareMatch (96.32 -> 96.74, 940->941 insns = orig)
- Missing init decode: orig emits `stb 0xf(r1)=0` right after `Zi8Memset`
  before `nibbles=0`(r28) / `elementIndex=0`(0xd) / `elementCount`(0xe).
  `savedNibbles = 0` after the memset reproduces the store AND the exact
  init-order emission; decl moved to end of locals. Slot lands 0x9 vs orig
  0xf (frame packing — orig's stack u8 class has two more slots).
- `savedNibbles = 1` inside `if (Zi8IsComponent(element))` after
  `elementIndex++` reproduces orig's `li r0,1; stb 0xf` dead store (the var
  is rewritten at `savedNibbles = nibbles` later before its only read —
  MWCC emits dead frame stores).
- Residual: jumptable addends still -0x8/+0x4 off (sub-100 code region),
  callee-window regname ties elsewhere in the fn.

## Verified walls (normalized-diff / insn-level evidence)

### kbd_lib — dual-IV + callee-pin family (all 6 sub-100 fns)
- Orig loops in KBDSetLeds/KBDSetLedsAsync use base+byte-IV addressing:
  `lwzx r0,r6,r4` (r6=kbdCmdBuf base lis'd once, r4=ofs +=0x20) plus a
  separate `addi r29` index IV + `bdnz` ctr. Mine always fuses to a cursor
  walk (`lwz 0(rN)`). Tried: while+`command++`, `u32 ofs`+`((u8*)buf)[ofs]`
  (load AND store), `u8*` named base, `for`+index, `*(u32*)&kbdCmdBuf[i]`,
  `(kbdCmdBuf + index)` — ALL fuse to cursor-walk. MWCC's parallel-IV split
  appears to be an internal strength-reduction choice with no source lever
  found (~8 forms).
- Orig pins `channel` in a callee reg (r31/r26) and recomputes
  `mulli rX,channel,0x268` per `kbdData[channel]` use; mine pins the
  product. Same callee-window binding family as prior leaves.
- kbd_led_handler: orig `bne->li7; li0; b; li7` (case arm fall-through).
  `switch{case TRUE;default}` emits `beq;b;li0;b;li7` (+1 insn);
  `switch{default;case TRUE}` emits `beq->li0;li7;b;li0` (inverted);
  if/else + ternary fold to branchless `subfic` select (documented
  banned-adjacent — select fold); `case FALSE` extra arm emits an extra
  `bge` compare. `default`-first kept (64.12, best of the forms).
- KBDSetModState: instruction-identical except one dest-reg choice on the
  element-address web (`add r4,r5,r4` vs `r5`) — allocator home, no lever.

### zi* units — all verified regname/scheduler ties
- Zi8MatchOEMdata (zoemdata), Zi8_81483264 (zkokeyp), zi8InternalGetZH
  (zi8cgetc, 10677=10677 insns): instruction-identical, pure rNN<->rMM
  web-home diffs.
- Zi8GetKOcandidates (zkokeyp): 670 vs 674 — 4 real nano-diffs:
  (a) init-block const-reuse (orig reuses one `li r0,0` across two stores;
      mine materializes `li r3,0`),
  (b) `sth r3` raw-then-mask at use vs mask-then-store at 2 Zi8_8148302C
      call sites (u16-field assign form),
  (c) one extra `mr` in marshal.
- Zi8Get1KeyPressCandidates (zi81key): orig +10 insns, +8 clrlwi —
  orig masks values at each USE (per-use clrlwi webs); mine shares masked
  webs. Init-block scratch-reg rotation too.
- Zi8AlphaGetCandidates (zi8alpha): 3947=3947 insns, 218 diffs — branch
  count shuffles (bge/bgt/ble reclassified) + regname; no structural gap.

### Data sections
- zi8alpha .data(48B), zi8cgetc .data(392B), zprepare .data(48B) at fuzzy 0:
  all are jumptable_8166XXXX objects whose R_PPC_ADDR32 addends bind to the
  code diffs above — they resolve when the fn matches, NOT carveable.
- Other units' matched_data gaps are extabindex-driven (fn layout), resolve
  with code.
