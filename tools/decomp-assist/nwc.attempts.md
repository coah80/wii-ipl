
## NWC24MsgCommit data decode (2026-09-28)
- Orig's 8B {1,0} .sdata object = `BOOL LoopBackEnable[2] = {TRUE,FALSE}` + `[0]` use-site (SDA reloc same as scalar).
- Orig's second "\r\n" literal @.sdata+0x24 (literal-use position between "\r\n--%s" and "--\r\n") = explicit-NUL literal `"\r\n\0"` — emits a distinct 4B literal MWCC won't dedup with the plain "\r\n". Named `static char crlf[]` can't reproduce it: named objects emit before pooled literals (lands at 0x8). Compound literals unsupported by this MWCC build. After this, .sdata/.data/.sbss/.bss all byte-identical modulo extraction end-pads.

## MWCC literal dedup / load-CSE notes
- SelectMBox reload tie (NWC24MsgRead, 4 fns, -4B each): orig emits `lwz r0,4(priv)` for the `&0x200` test then RE-LOADS `lwz r3,4(priv)` inside inlined SelectMBox. MWCC always CSEs the two `->type` loads to one register; tried `data[1]` lvalue, public-param+inside-cast, cast-callsite, inside-cast combos — all fold. Same class as pf_stub `message->operation` re-read.
- CheckMsgBoxSpace (223/223): identical insn stream, 45 scheduling diffs on the div-by-10 mulhwu chain + reg-home cascade (orig dateFlags->r23/buffer->r24 vs swapped).
- NWC24CommitMsgInternal/WriteMIMEAttachHeader: ndiff-0, residual fuzzy from one r23<->r24 home swap at ~0x770 (cascade from earlier live range).
- NWC24MsgSubject fns: reg-name/arg-staging diffs only; ReadMsgSubjectPublic missing `mr r8,r26` staging; iSetMsgSubjectBase64 +12 same-stream.
- ConvertDaysToDate: 57 regname diffs + one extra tail block (`*month++` + b) vs orig's fall-through return.

## net2 wave — volatile-guard isolation SOLVED the SelectMBox reload family (2026-10-01)
- LEVER: `((volatile NWC24MsgObjPrivate*)privateMsg)->type` on the *guard* `& 0x200`/`& 2` reads (NOT inside SelectMBox). A volatile first-read can't CSE into the inlined SelectMBox's `->type` reads, so it loads into r0 (dead after rlwinm.) and SelectMBox's own load gets pinned r3 and reused for its second flag test — exactly the base layout. Fixed NWC24ReadMsgField, NWC24ReadMsgSubject, NWC24ReadMsgFromAddr (insn-equal), ReadMsgTextInternal (177->178/178), ReadMsgAttached (insn-equal). Apply per-site: volatile where the load must NOT be the pinned one. Volatile *inside* SelectMBox poisons all inline sites (forces a 3rd load) — removed; the standalone double-load comes from the `*type` store alias barrier anyway.
- `switch(result){case OK: ...}` with empty default on the ReadBase64Data result: base fuses default-skip to `bne`; writing it as plain `if (result == NWC24_OK)` matches.
- ReadMsgTextInternal `if (len==0) len=text.size`: base emits `beq->then; b->join` (sunk then-block + stray b). Ternary, else-if empty-if, and explicit `if()goto;goto;` labels ALL fold to fused `bne` — unfused-beq/b wall.
- iSetMsgSubjectBase64 `beq;beq;b` 3-insn two-branch OR (==OK||==OVERFLOW ok else done): every source form folds (`||`+else, two positive gotos, else-if chain -> beq;bne); `switch` emits double-beq but adds a sign-split `bge` (+1); `(u32)`-cast switch keeps the bge. Splitting the OR across a second variable name folds too (copy-prop). Wall = unfused-branch family.
- iSetMsgSubjectQP: pure whole-fn r30<->r31 rotation (secondSize vs lineLength); decl-order moves had no effect or made it worse.
- DecodeMIMEHeaderFieldBody: r29<->r31 park-order tie (decodedSize vs input); init-stmt reorder cascades into r28<->r30. Parked.
- iMBoxCheck oldestId store-forward: `*(volatile u32*)&mailbox.oldestId` at the DeleteMsg call site STILL forwards (provable-local stack slot) — confirmed wall, not a lever.
- IsMsgObjReadable: 5-diff pure scheduling (entry->type load position vs prologue stores); volatile version adds +1 + cascade. Parked.
- ReadMsgAttached residual: r27<->r28 (index home) + base keeps scaled index (idx*4 in r27) and recomputes `add r3,r29,r27` per attachedSize access while mine keeps the pointer (+1 insn). Ptr-vs-scaled-index liveness tie.
