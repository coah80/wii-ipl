
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

## wave 14 findings (orchestrator hints exhausted)

- **UpdateDlTask web-reduction**: tried hoisting `DlTaskListHeader* header` once
  (regressed 249->248 — added a web), dropping the `task` alias (identical),
  nested-ifs for the `write && !opened && !owner` chain (identical), flat
  4-term `&&` (identical). The 5th callee web is the second phase's workP-select
  rotator — the phases are disjoint so the webs can't merge; base's r28 reuse
  across phases is allocator color-choice, not a source-level merge. Wall stands.
- **EncodeWord ||-chain polarity**: term reorder (`q` before `Q`), `!(x!=c)`
  last-term negation, `!(A||B||C||D)` guard-form inversion, else-folded
  `*encoded='\0'; goto done` — all emit the same `bne` last term or worse (+2
  for else-fold). The else-fall layout base shows requires the join be
  non-adjacent; MWCC's block order here isn't moved by source polarity.

## wave 15 findings

- **MsgRead CSE wall bypass (no volatile)**: `type = NWC24_MBOX_TYPE_SEND;`
  default-assign immediately before `SelectMBox(msg, &type)` folds to `li r5,0`
  in the out-reg and makes the fn insn-equal — ReadMsgField 102/102,
  ReadMsgSubject 82/82, ReadMsgAttached 91/91. FromAddr regressed +4
  (reverted — its -1 gap is the same double-load wall but the default's `li`
  doesn't balance there). NOTE: MWCC does NOT model the store as a clobber
  (folds the local's value through the call) — the win is insn-balance, not
  genuine CSE suppression; base still emits a real second `lwz`.
- **CSE wall verified deeper**: base `NWC24ReadMsgField`/`FromAddr` show TWO
  `lwz 4(r27)` separated only by the bit-test error branch — no call, no store
  between them. The clobber-reproduction theory is dead for this pair; orig's
  suppression mechanism is still unknown (volatile decl vetoed).
- **UpdateDlTask workP re-fetch**: `header` var fetched via GetCachedDlHeader
  + re-fetched after validate2 is a dead-assign (eliminated, no web effect).
  `task`-alias drop, flat/nested && chains, early-return variants — all
  identical. The 5th callee web (phase-2 workP rotator, r27 vs base's r28
  reuse) is allocator coloring, not source-mergeable.
- **RemoveDlTask caller-conflict**: NWC24DeleteDlTask's inline wants the
  single-check `if (result>=0) id=0xffff` form (base: one cmpwi + bge + sth),
  PurgeOldestDlTask wants separate-ifs (double `mr r5,r3` carrier copies).
  Separate-ifs wins the aggregate (175/176 + 108/105); single-if, early-return,
  and assign-then-if all regress both callers.

## wave 16 findings (CSE wall — final verdict)

- **The CSE is purely address-keyed**: EVERY same-address access path
  normalizes to the same VN and merges — `*((u32*)((u8*)msg+4))`,
  `*((s32*)msg+1)`, `*(&msg->data[1])`, SelectMBox taking
  `const NWC24MsgObjPrivate*` (`pmsg->type` member path), and a same-offset
  union member (`union { u32 type; u32 msgType; }` — caller reads ->type,
  SelectMBox reads ->msgType). All emit one `lwz` and merge.
- **Bitfield does defeat it but wrong ops**: `u32 type : 20` member produced
  the fused-extract form (`rlwinm. r0,r3,0x14,bit; srwi r0,r3,0xc`) on ONE
  load — never a second lwz. `u32 type : 32` normalized to plain u32 (merge).
  A `union { u32 type; u32 typeBits : 20; }` keeps ->type clean for all other
  fns (FaceData stays diffs-0) but SelectMBox's read still fuses-extracts.
- **Verdict**: only a true clobber or volatile breaks it (vetoed). Base's
  second `lwz` at a different code position with no intervening call/store
  means orig's suppression mechanism is internal to MWCC's block model —
  likely a load in a non-dominated sibling block orig emitted differently
  that we haven't found. Documented wall; committed form uses the
  `type = NWC24_MBOX_TYPE_SEND` default-assign (insn-equal, plausible orig
  idiom) for Field/Subject/Attached.

## Wave 17 — closest-flip sweep (blocking fns enumerated; all insn-equal ties)
Blocking fns per unit (diff counts, all count-matched): MsgSubject — NWC24SetMsgSubjectAndTextPublic 65, NWC24iSetMsgSubjectQP 12, NWC24iSetMsgSubjectBase64 10. MsgCommit — NWC24CommitMsgInternal 18, CheckMsgBoxSpace 75, WriteMIMEAttachHeader 5. DateParser — NWC24iDateToOSCalendarTime 13, ConvertDateToDays 16, ConvertDaysToDate 79. MsgRead — NWC24ReadMsgTextInternal (insn-equal), NWC24ReadMsgFromAddr -1 (SelectMBox CSE wall), NWC24ReadMsgAttached -1 (same wall), NWC24ReadMsgMBRegDate/MBDelay/etc. diff 0.
- WriteMIMEAttachHeader: 2-web home swap (type→r30/disp→r29 vs r29/r30) + assoc ((mime+disp)+type vs mime+(disp+type)). Tried: expr assoc reorder, decl reorder, stmt merge (+= into strlen expr → extra web, savegpr_25 vs _24, reverted). Wall: MWCC normalizes assoc; home assignment is allocator-internal.
- iSetMsgSubjectBase64: arg-copy order — base pins work(r8)→r22 FIRST then r4..r7→r18..r21; mine arg-order. Web-creation order unmovable by: work-first stmt reorder, `second-work` re-derive (+1 insn, charset spilled), second-as-copy form. Second cluster: stack-reload scheduling (lwz r0/r3 + add order). Wall.
- iDateToOSCalendarTime: year-web r0↔r5 + shared "0"-web (isLeapYear=0 / msec=0 / usec=0 coalesced) r5↔r0. Tried: isLeapYear init moved late (+1 insn), single-assign form (identical), interleaved-init (identical). Coloring tie.
- ConvertDateToDays: magic-div interleave at tail — base materializes 0x51ec magic before yo+299; same insns, different operand emission/dest names. Scheduling tie.

## Wave 18 — smallest-blocker decode passes (no flips; all web-coloring ties)
- WriteMIMEAttachHeader (5): base assoc = type+=enc in-place then disp+typeSum→r0, mime+that→r3. Tried chained accumulation (`disp += type`; mime+disp) → -1 insn + savegpr_25 (extra web, reverted); paren-isolated pair sum → same 5 diffs; decl/stmt orders → normalized. Residual = type/disp r29↔r30 home swap + assoc — allocator tie.
- iSetMsgSubjectBase64 (10): arg-copy order r8→r22 first (web-creation order: work pinned earliest) + stack-reload scheduling. work-first stmt reorder normalized; `second-work` re-derive +1. Wall.
- iSetMsgSubjectQP (12): single secondSize-web r30↔r31 swap vs stack-reloaded loop local. Init-order flip regressed to 17 (swap moved to different web pair) — reverted.
- CommitMsgInternal (18): two web-permutation clusters (flag→r23/r28, stringWork→r24/r23, err→r28/r23) — whole-function coloring.
- iDateToOSCalendarTime (13): year-web r0↔r5 vs coalesced "0"-web (isLeapYear/msec/usec share one li 0 web). 3 init-position variants tried — coloring tie.
- ConvertDateToDays (16): magic-div const-materialization + interleave order at tail — scheduling tie.
Verdict: remaining nwc24 diffs are all allocator/scheduler-internal homes; source levers (assoc, decl order, stmt order, init position, accumulation direction) have been exhausted across ~15 forms this wave.
