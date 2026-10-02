
## 2026-09-30 session (scene2 continued)

- collectTitlesBySpecialChannels: 361/361 exact via separate out-param temps + decl-after-call + per-use reloads. (committed earlier)
- 12/12 enqueue* fns matched by removing `values[2] = 0` stores — orig leaves SDChannelSelectCommand.values[2] uninit except in delete/command notices.
- findAdjacentChannel: tried `step`-first decl order — regressed (bne moved earlier); scheduler tie, reverted.
- **setEventHandler r5 mystery (documented):** orig calls `setEventHandler__Q33ipl5scene8SDButtonFPQ23gui12EventHandlerPQ23gui12EventHandler` (2-param) at 4 sites in iplSDChannelSelect + 2 in iplSDChannelTitle with r5 NEVER materialized (no li/lwz/mr r5 in the 4-insn window before bl; callee is non-static so this=r3, event=r4, optOutEvent=r5 garbage). MWCC always emits `li r5,0` for the =NULL default (verified: both `(h, NULL)` and `(h)` call forms emit it in mine). iplAddress.o Button callers DO emit `li r5,0` for the analogous Button decl. No C++ source model reproduces a 2-param bl with unset r5 (1-arg call to a defaulted 2-param decl emits the default; a 1-param decl would mangle differently). Left as `(h, NULL)` explicit; ~4 insn residual across create/selectChannel/initializeNormalPage/calcCommon/onEventDerived.
- kpr_lib: orig's `once$2281` is an 8-byte fn-local accessed via lbz/stb → decoded as `static union { u64 align; u8 flag; }` inside KPRInitQueue — gives size-8 `once$` + .sbss 0x10 and .sbss scored 100%. Orig's .sbss ordering [DeadKeys@0,Romaji@4,once@8] vs mine [once@0,Romaji@4,DeadKeys@8] is MWCC reverse-decl-order emission; objdiff .sbss scores 100 anyway. kpr_lib now 8/9 fns, all data 100.
- iplSDMemory: removed dead `#pragma inline_max_total_size` (no effect). drawTransferTitles: orig re-materializes f32 consts from sdata (`lfs f0,const@sda21`) where mine spills/reloads stack copies — frame-lever not found. create: 1064 vs 1060, mostly lbl_/@N symbol-name + r30/r31 data-base home.

## beq+b two-way dispatch — SOLVED (onEventDerived)

Orig emits `beq fwd / b end` pairs where single-branch guards were expected.
Produced by a real `switch (event) { case 0: BODY; break; default: break; }`
dispatch — MWCC keeps the 2-arm dispatch layout instead of folding to `bne`.
`if`/`else` and `goto` forms all fold back to a single `bne`; only `switch`
reproduces it. Applied at the `event == 0` check in the anon
SDChannelSelectButtonEventHandler::onEventDerived → 144/144 insn-identical.
The same pair inside a u64 `<` compare (handleSDTitleListResult `neg.` hi-test)
has no applicable source form — that one stays a wall.

## switch-on-bool dispatch (handleSDTitleListResult)
Orig emits `beq fwd-body / b ret` where a plain `if (u64 < K) return;` folds to single `bne ret`.
Decode: `switch (x < K) { default: BODY; break; case true: return; }` — `default` arm FIRST
(source order) with the bool-compare as discriminant → MWCC emits the two-arm dispatch
(171/171 insn-equal). `case false:` regresses (jump-table range dispatch), if/else folds.
Residual: orig uses `neg.` flags directly (`beq`); mine emits `neg` + `cmpwi 1` + `beq` —
same insn count, operand-level diff only.

## Dead-arm fossil (iplAddressEdit, earlier)
An unreachable empty `case N:` arm in a switch materializes a dead `b end` between
dispatch and bodies: `case 4: break;` in start_left_event → EXACT 96/96;
`case 4: goto done;` in start_point_event → 182/182. Only works in range-mapped
dispatch (table/dense compare); every listed case in a compare-chain gets its own
cmpwi level — the trick cannot produce extra `b` edges there (set_err_msg stays +1).
