
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
