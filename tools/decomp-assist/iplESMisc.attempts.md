
## w1008/card2 leaf — DeleteUnauthorizedData 79.8 → 89.6
Decodes that landed:
- Inverted head checks `if (ret != ES_ERR_OK) {report} else {work}` — orig inlines
  error bodies with success branched over (was tail-merged in nested success-if form).
- `return ret` — fn returns s32 (orig mr r3,r27 before epilog); only the OUTER
  ListTitlesOnCard results go to `ret`; inner call results use a separate local
  (`result`) — kills the per-call `mr r24` homes.
- Zelda predicate is a u64 masked compare: `(titleId & ~0xFFULL) == 0x00010000525A4400ULL`
  → `and r4,r20,-1` (hi & 0xFFFFFFFF) + `and r0,r19,-0x100` + xor/xoris/or.
- sprintf args are u64-masked exprs `(u32)((titleId >> 32) & 0xffffff)` and
  `(u32)(titleId & 0xffffffff)` → `and` with materialized masks, not clrlwi/mr.
- `ESTitleId titleId = titleIds[i]` u64 indexed load → lwzx+add+lwz4; ticket block
  re-reads `titleIds[i]` after ES_DeleteTitle (forced reload across the call).
- `ESTicketView* pTicketView` named local for memset/memcpy/DeleteTicket → r29 web.
- Blacklist chain = goto-dispatch form (beq to shared delete block + goto next_title);
  `||` chain folded wrong (bne-merged), BOOL flag form emits li/cmpwi — both wrong.
Remaining (documented walls): orig re-materializes each u64 constant per compare
  (lis/addi at every == and ordering check); mine keeps them in volatile regs across
  adjacent blocks — MWCC remat-vs-keep tie, ~10 insns. Plus beq+b vs bne tail dispatch
  and mr r6,r3 placement scheduling.

## card2 wave (w1008) — DeleteUnauthorizedData residual decode
- `beq fwd; b` dispatch sites (DISK check `beq→del;b→next`, ticketViewCount `bne→alloc;b→next`):
  decoded — orig's then-block is adjacent-forward but else is a real `b` — needs else-goto + non-fallthrough then.
  Probes that all fold to single-branch: `if(c){goto}else{goto}` (bne→next), inverted polarity `if(!c)goto/else goto` (bne),
  nested `if(>){if(==)goto}else goto`, `else if(c==0){goto}else{X}` — MWCC always prefers bne+fallthrough-del.
  Confirmed A-vs-B block-placement tie (same wall as cardseq's `bge fwd;b` sites — MWCC places del-block
  adjacent and folds else-goto). ~2 sites ≈ +2 insns orig.
- Per-compare u64 const remat: orig keeps r14=0x44490000 (DI-prefixed los) + r23=0x10000 (all his via `addi r0,r23,K`),
  rematting `addi r0,r23,{1,8}` per compare (~15 extra insns vs mine keeping 0x10001/0x10008 in r4/r5 across blocks).
  Keep-vs-remat wall — consts live in volatile regs stay live across non-call blocks; no source lever found.
- `mr r6,r27` vs `mr r6,r3` arg-reg timing shifts — sched tie.
- ret homing: `mr r27,r3` after EACH ListTitlesOnCard (both webs homed); mine keeps first web in r3.
Final residual: 1796B orig vs 1736B mine — all in documented wall families (remat, block-layout, sched, web-homing).
