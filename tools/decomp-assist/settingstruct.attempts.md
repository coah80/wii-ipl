# settingstruct leaf — attempt log

Scope: src/scene/setting/AOSS.c, src/scene/setting/AOSSLink.c, src/scene/address/iplAddressEdit.cpp
Base: origin/main@9321a926. Lane-clear vs open PRs (only #1156 touches ATERM.c — dropped per orchestrator).
Tools: ~/tools/fndiff.py (capstone normalized diff, register-renaming by first-appearance order; `--raw` = literal).

## Baseline
- iplAddressEdit 99.55 — create 97.56 (3280B), get_friendinfo 88.04, update_friendinfo 99.42
- AOSSLink 99.01 — AOSSi_WLANGetBSSList 98.48 (908B), AOSSi_WLANConnect 98.71 (620B)
- AOSS 98.42 — AOSS_Init_old 96.19 (6336B), AOSSApplyAuthOptions 98.77 (456B), AOSSXorBufferWithKey 98.61
- iplAOSSThread 100, AOSSData 100

## get_friendinfo (88.04, 584B) — text-ptr early-pin wall
Orig materializes `addi r29,r28,0x2b4` (mName) and later `addi r29,r28,0x2cc` (mDisplayText)
EARLY — inside the FindPaneByName marshal window of each `set_textbox` call — pinning the
text-ptr web in callee reg r29 across `bctrl`. Mine remats `addi r5` at the marshal point.
Same pattern appears in `create` (r25 pin before `stw` field store + FindPaneByName chain).

FAILED variants (5+, all documented): `const wchar_t* name` local (MWCC forwards
single-use locals to marshal), `pane`+`name` locals, pane-only local, reused `text` local
with statement-level assignment, text decl before setName. MWCC remats cheap `this+const`
expressions regardless of def site; orig's early materialization requires the web's DAG
birth to precede the pane-chain eval — no source lever found.

## update_friendinfo (99.42) — 2-insn marshal-order swap
38=38 insns; only diff: orig marshals `addi r4,r30,0x2b4` (src) before `addi r3,r31,8`
(dst) in the wcsncpy marshal; mine dst then src. Named-local and early-birth variants
failed — MWCC emits marshal webs in its own ready order.

## create (97.56, 3280B) — 2 missing insns + pin/rotation
808 vs 810 insns. Marshal shape identical L-to-R (`mr r3; addi r4; addi r5; li r6; li r7; bl`).
Residual: same text-ptr pin (addi r25,r29,0x2b4 before `stw r0,0x14(r27)` and inside
marshal windows) + wholesale callee-window rotation (r30↔r31 const-table vs boardFile
pin, deep r25-r31 webs).

## AOSSi_WLANGetBSSList (98.48, 908B) — sth placement + IV rotation
227=227 insns. Two-loop IV web-home rotation (r26/r20 swap) + one `sth r5,0x40(r1)`
placement bound to the `lhz` operand web home. Retry webs all init'd (no uninit signature).

## AOSSi_WLANConnect (98.71, 620B) — single li-placement
155=155 insns. Only diff: `li r5,0x7c4` hoisted one slot before `mr r3,r27` in the memset
marshal (const-li vs move emission order). `u32 ifConfigSize` named local REGRESSED (4 diffs);
reverted. r28/r31 webs verified init'd — no uninit-read signature.

## AOSSApplyAuthOptions (98.77, 456B) — arg-save order + rotation
Two arg-web home swaps (r5-arg→r24 vs orig arg1→r27 first — emission order of `mr` saves
at fn entry) + cursor/literal-base swap (r29↔r31). Also `s_responseTypeByState` symbol
shows as orig `lbl_81697210` — naming artifact, reloc target identical.

## AOSSXorBufferWithKey (98.61) — XOR-loop pointer web swap
147=147 insns. Loop webs swapped: mine `add r4,r28,r3`/`add r5,r26,r3` vs orig r26/r28;
`xor r6` vs `xor r0` result reg. Decl-order swap of `temporaryHalf`/`packetHalf`
REGRESSED (moved temp-pointer web homes); reverted.

## AOSS_Init_old (96.19, 6336B) — deep wall
1581 vs 1584 insns (~3 short), 1213 normalized diffs — mass web rotation across the whole
fn (different callee layout → different numbering). Per-site: prologue `sth r4,0x28`/li
placement, a free-check block ordering (`cmpwi;beq;bl Free;stw` on two globals), one
`bne` vs `lwz+cmplwi+beq` shape. No source lever found; prior wave documented the same.

## uninit-read lever (PR #1270) — checked, N/A
Verified orig stores every compared callee reg before use on all paths: WLANConnect
`li r28,0`/`li r28,-1` stores before each `cmpwi r28,0`; GetBSSList retry webs init'd;
create/AddressEdit inits all present. No fn emits an extra init orig lacks or reaches a
compare with a path-unset reg.

## ppc_iro_level results (post-#1276 lever)
- **get_friendinfo → 100%**: `#pragma push` + `ppc_iro_level 0` + named text locals
  (`const wchar_t* name = mString.mName;`, `text = mString.mDisplayText;`). The named
  local's def site births the text-ptr web early; IRO-0 blocks the remat that previously
  folded it to the marshal — orig's `addi r29,r28,0x2b4` early-pin reproduces
  (`_savegpr_28`/`_restgpr_28` match; residual = bare `bl` reloc offsets). Neither the
  local alone (forwarded) nor IRO-0 alone (still remat) sufficed — both needed.
- **create 97.56 → 98.73** with `ppc_iro_level 1` (friendText locals already present).
  Levels 0 and 1 produce identical output here. Residual = callee-window rotation.
- FAILED: AOSSi_WLANConnect (identical at 1/2, explodes to 219 at 0 — marshal swap
  unaffected), AOSSi_WLANGetBSSList (46 diffs at 0/1 = baseline), AOSSApplyAuthOptions
  (IRO-1 drops fuzzy 98.77→97.94 despite fewer normalized diffs — reverted),
  AOSSXorBufferWithKey (61→154 at IRO — reverted), AOSS_Init_old (1213 diffs at 0/1 =
  baseline — pragma no effect), update_friendinfo (IRO regresses 2→11 — reverted).

## Status
**get_friendinfo is a NEW 100% fn** — owner PR bar (≥1 new 100% + zero regressions) met
for a source-only PR. create improved to 98.73. Remaining fns stay at documented ties;
units stay NonMatching.
