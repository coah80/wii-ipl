
## scanAP (w1010 revisit) — inlined-bool materialization wall
Orig inlines `Animator::isPlaying()` (`mState == 1` at +0x14) 3x but always as a
MATERIALIZED bool: `lwz rX,0x14; addi r0,rX,-1; cntlzw r0,r0; rlwinm. r0,r0,27,5,31; bne`.
Ours fuses to `lwz r0,0x14; cmpwi r0,1; beq` — 6 insns shorter overall (272 vs 266).
Tried and rejected (MWCC normalizes/folds all of them):
  - `isPlaying() == false` at the call site
  - `bool playing = anim->isPlaying(); if (!playing)` named local (fuses; eggColorFader's
    fadeOut materializes only because `success` is also RETURNED — a second value-use)
  - `int isPlaying()` return type — still fuses
  - `return !(mState != ANIM_STATE_PLAY)` in the header — still fuses
Conclusion: orig's bool crosses a real value-boundary (2nd use, or a different inlined
shape we haven't identified). Same family as the fused-compare fossil in CHANSVm.
Also tried: convertRevIP untouched (98.7, 292B).
