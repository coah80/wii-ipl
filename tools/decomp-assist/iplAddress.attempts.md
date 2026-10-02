
## beq+b inside onEventDerived (solved — switch-dispatch + case-fallthrough structure)
- Orig's ON_TRIG case: `if (con == NULL) break;` (real break → switch join), `if (con->downTrg(...)) { if (mState == STATE_COVER_NORMAL || mState == STATE_NORMAL) {buttons} }` — arms and failed guards FALL THROUGH to ON_POINT code (0x31c) — no break after the if-chain; the positive `||` mState-guard emits `beq body` + `bne ON_POINT`.
- start_drag_event: `switch (mState) { case STATE_NORMAL: if (mMode == 0) break; /*fall*/ default: return; }` reproduces `beq fwd / b ret` per clause — the `b` is default's arm edge placed between dispatch test and case body. Sequential `if`s, `||`, goto, if/else all fold to single `bne`.
- Residual: pure reg-web coloring (orig this→r29/con→r30/paneName→r31 vs mine r27/r28/r30) — liveness-priority coloring, no source lever (keep-vs-remat wall family).
- movePane_onDrag: `width += 0.01f` was INSIDE the `if (textBox && name)` block in orig (b 0x164 skips it). `&&` clause polarity `bne fwd / b end` still folded in mine (block-layout tie).
