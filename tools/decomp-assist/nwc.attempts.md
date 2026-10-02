
## NWC24MsgCommit data decode (2026-09-28)
- Orig's 8B {1,0} .sdata object = `BOOL LoopBackEnable[2] = {TRUE,FALSE}` + `[0]` use-site (SDA reloc same as scalar).
- Orig's second "\r\n" literal @.sdata+0x24 (literal-use position between "\r\n--%s" and "--\r\n") = explicit-NUL literal `"\r\n\0"` — emits a distinct 4B literal MWCC won't dedup with the plain "\r\n". Named `static char crlf[]` can't reproduce it: named objects emit before pooled literals (lands at 0x8). Compound literals unsupported by this MWCC build. After this, .sdata/.data/.sbss/.bss all byte-identical modulo extraction end-pads.

## MWCC literal dedup / load-CSE notes
- SelectMBox reload tie (NWC24MsgRead, 4 fns, -4B each): orig emits `lwz r0,4(priv)` for the `&0x200` test then RE-LOADS `lwz r3,4(priv)` inside inlined SelectMBox. MWCC always CSEs the two `->type` loads to one register; tried `data[1]` lvalue, public-param+inside-cast, cast-callsite, inside-cast combos — all fold. Same class as pf_stub `message->operation` re-read.
- CheckMsgBoxSpace (223/223): identical insn stream, 45 scheduling diffs on the div-by-10 mulhwu chain + reg-home cascade (orig dateFlags->r23/buffer->r24 vs swapped).
- NWC24CommitMsgInternal/WriteMIMEAttachHeader: ndiff-0, residual fuzzy from one r23<->r24 home swap at ~0x770 (cascade from earlier live range).
- NWC24MsgSubject fns: reg-name/arg-staging diffs only; ReadMsgSubjectPublic missing `mr r8,r26` staging; iSetMsgSubjectBase64 +12 same-stream.
- ConvertDaysToDate: 57 regname diffs + one extra tail block (`*month++` + b) vs orig's fall-through return.

## Wave 8 (agent/w0929/nwc24 post-veto)

- Veto compliance: `volatile u32 type` member gate REMOVED from NWC24MsgObj.h.
  MsgRead 14/16 -> 11/16 (orchestrator-accepted: CSE wall documented, no legal barrier).
- SelectMBox TBAA-pair experiment (SelectMBox(NWC24MsgObj*) reading data[1]):
  committed as 6d3792ef but claims diffs-0 were wrong - loads STILL merge
  (verified ReadMsgField 101/102). Confirms MWCC load-RLE is type-insensitive/
  address-keyed: provably-same address merges regardless of struct member path.
- MBoxCheck store-forward: 3 forms tried. Struct+out-param: `stw` kept, reload
  forwarded (-1). Plain locals: promoted entirely (-2). `*idp` read: same.
  Base's `stw r0,8(r1); lwz r4,8(r1)` requires producer-reg != consumer-reg AND
  no fold - pure scheduling, no source lever found.
- UpdateDlTask 249/253: base saves r28-r31 MANUALLY (interleaved `stw`+`mr`),
  mine pins r27-r31 -> `_savegpr_27`. Extra pinned reg = second workP temp
  (r27 vs r28 reuse). Removing `taskId` local didn't drop a reg. Documented
  manual-vs-savegpr family.
- DecodeMIMEHeaderFieldBody lever confirmed: local mutation copies keep args
  unpinned (95.76).

## Wave 9 (agent/w0929/nwc24)

- MBoxCheck store-forward: 6 alias-provenance forms tried (whole-struct escape
  via named MBCOldestMsg + &mailbox arg, return-value getter + member
  assign/read, *idp read, box-> member access, header->oldestId re-derive).
  ALL still forward: MWCC coalesces the producing load into the arg reg (r4)
  whenever the value flows to the call. Base's `stw r0,8(r1); lwz r4,8(r1)`
  requires producer != arg reg - pure scheduling, exhausted.
- PurgeOldestDlTask: state-init store-order cracked - orig assigns
  `comparisonValue, selectedValue, sortMode, comparisonId, initialized, valid`
  (member-init ORDER moves MWCC's stw emission order). Dropped `selectedId`
  copy. Tail remains r5 result-carrier + r30/r31 window swap (-6, same family).
- RemoveDlTask block-form tail (`if (result >= OK) {id=0xffff}`) REGRESSED
  both callers - early-return form is correct.
- ManageDlTaskListForMenu: RemoveDlTask(taskPointer) var reuse +1.
- SetDlTaskAccessTime: hand-rolled -3/-9 chain replaced with shared
  ValidateDlTask(dlTask, FALSE) - identical chain shape, plausible orig reuse.
- UpdateDlTask 249/253: base pins r28-r31 with MANUAL stw saves (interleaved
  mr r31,r3) not _savegpr_28; mine pins r27-r31 -> _savegpr_27. Epilogue-
  restructure attempts didn't change the save decision (manual-vs-savegpr
  is driven by pin count + mwcc internal cost model).
- CheckDlHeaderConsistency 212/212 = mr-emit-order only (addi r31 first).
- DecodeWord 181/180: base's loop = single offset counter + `add` recompute
  (pos never materialized as IV); mine gets pos-walking + counter (2 incrs).
  FindMarker-call, plain-recompute, pos-var forms all strength-reduce under
  this fn's register pressure. Documented SR wall.

## wave 10 findings (FindMarker materialization, ptr-arith inlining)

- **pos-local lever (proven)**: orig's `FindMarker` materializes `char* pos = input + offset`
  per iteration — MWCC pins pos to a callee reg across the strncmp call (`add rN,in,off;
  mr r3,rN; bl`). A recompute-in-arg form (`strncmp(input+offset,...)`) makes pos
  transient in r3 and loses the callee pin. Returning `input + offset` (recomputed)
  rather than `pos` matches base's site-dependent IV choice (counter+recompute at
  low-pressure sites, dual walking-pos+counter at high-pressure sites — MWCC picks
  per inlining context, same source).
- **`start + 1` exprs (proven)**: orig's ExtractEncodedText never mutates `start` —
  every use is `start + 1` (`end = FindMarker(start + 1, ...)`, `length = end - (start + 1)`,
  decode args `(u8*)(start + 1)`). A `start++` mutation pins a dead extra callee reg
  and changes the inlined-FindMarker arg from `addi (start+off),1` recompute to
  walking. Closed 134/135 -> 135/135 (remaining = reg renames + _savegpr window).
- **Redundant guard (proven)**: base emits `cmpwi end,0; beq skip` before the tail
  `*encodedSizeOut` write even though `end` was NULL-checked earlier — orig's
  source has a defensive `if (end != NULL)` MWCC can't fold (no cross-BB proof).
- **Arg-check elision**: orig's ExtractEncodedText does NOT check `decoded == NULL`
  (checks encoded, decodedSize, encodedSizeOut only).
- ConvertDateToDays tail: two magic-divide chains share the 0x51EB851F constant;
  base's scheduler emits `lis+addi` magic before the +299/-1 numerators, mine
  interleaves — pure DAG-schedule order, stmt reorder no-op (verified).
- QDecode/CheckMsgBoxSpace/ConvertDaysToDate: insn-equal pin-window swaps +
  unrolled-loop scheduling permutation — documented tie-break families.
- EncodeWord: base pins stack-arg (decodedSizeOut, 0x48(r1)) to r31 AND
  re-materializes string addrs per-site into arg regs; mine CSEs addrs into
  callee regs (competes for the same window). Whole-fn pin-order wall.

## wave 11 findings (asymmetric-access CSE-frontier break)

- **Asymmetric-access lever (proven, NWC24ReadMsgAttached)**: when two identical
  `arr[index]` accesses get CSE'd at the ADDRESS level (MWCC pins `base+idx*4`
  once, single `lwz` + reuse — one insn short of base's scaled-index +
  `add`/`lwz` recompute), phrase the second access through a different-but-equal
  expression so `index*4` is the ONLY shared CSE node: member-index form for one
  site, `*(u32*)((u8*)obj->arr + index*4)` for the other. The scaled index then
  wins the pin and each site recomputes `add` + `lwz disp` — base's exact form.
  Member-index on one side + byte-cast on the other = no shared address node.
- Failed variants on the same wall: uniform member-index twice (addr pinned),
  `u32* sizePtr` local (materializes base -> `lwzx`), uniform byte-cast twice
  (addr pinned), `index *= 4` split-if (breaks single shared -5 tail block).
- TextInternal -1 confirmed = SelectMBox type-reload CSE wall + beq/bne polarity;
  Attached -1 same wall. All other remaining diffs insn-equal renames.

## wave 12 findings (arg-reg pinning model, PurgeOldestDlTask 170->175)

- **Scoped-pointer arg-pin (proven)**: when an inline helper's pointer param is
  shared across phases, declaring a scoped local per phase makes MWCC
  re-materialize `&obj` into the arg reg per phase instead of pinning one callee
  reg — this cascades the result var into the NEXT arg reg (r5), matching base.
  `readTask = &task` scoped to read phase + `&task` fresh at the remove call:
  dlTask->r3, dlHead->r4, err->r5 = base's exact arg-register carrier model.
- **Separate-ifs double-assign (proven)**: `if (result < 0) { err = result; }
  if (result >= 0) { err = result; write }` keeps BOTH `mr` emits; the if/else
  form folds them (GVN). Two separate ifs share the compare but keep per-edge
  assigns.
- **`else { return x }` unfuses the branch**: `if (c) { X } else { return x }`
  emits `b exit` on the else path where bare `if (c) {X}` fused `blt` — matches
  base's bge+ b layout piece.
- ManageDlTaskListForMenu reached insn-equal 152/152 via `&task` at both calls
  (no pointer var at all) — MWCC's phase model gives arg-reg materialization.
- Remaining PurgeOldest -1: base's dead `cmpwi err,0; mr r3,err; bge;b` tail —
  a folded `if(err>=0) return; return` that MWCC won't re-emit from source.

## wave 13 findings (index-IV recompute, store-forward ordering)

- **Index-IV + recompute lever (proven, DecodeWord 181->180 insn-equal)**:
  pointer-walk IVs (`pos++` + separate count) cost a dual increment; orig used
  `for (i...) { pos = start + i; ... }` — single index IV, pointer recomputed
  per iteration as `add r31,base,idx`. Rewrite `ptr++`-walks as indexed recompute
  when base shows `add rX,base,rI` inside the loop.
- **MBoxCheck store-forward narrowed to scheduling**: baseline (struct
  {oldestId, header} + u32* getter + member read) now emits
  `lwz r4,0x20(r4); stw r4,8` — MWCC binds the RHS load straight into the arg
  reg. Base binds it to r0 (scratch) then `stw;lwz` — an arg-marshal schedule
  where r4 was still busy. ~10 forms (void* getter, separate locals, punned
  reads, assignment-expr args) all forward the store. Wall: not a provenance
  issue, pure scheduling.
- **EncodeWord result-carrier pin**: base carries `result` in r3 across
  appends (li r3,-8/-3/0); mine pins r31 (costs savegpr_21 vs _22 + renames).
  The -1 insn is the 4-char `||` chain's last-term polarity (bne-else vs
  beq-append); `&&` inversion emits identically.
- **"?" literal via `li r4,reloc`**: base materializes short-string args via
  li+reloc inline (no pin); mine pinned r25 for it. Minor.
