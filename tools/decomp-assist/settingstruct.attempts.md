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

## Post-#1277 rebase (origin/main@c723136f)
Owner merged get_friendinfo+update_friendinfo via #1277 (IRO-1 + named locals — same
decode). Branch now keeps only create's `ppc_iro_level 1` (98.73) + this log.

## libs/RevoEX/src/net/aes.c (added to leaf)
- AESiEncryptBlock 65.81 (158=158 insns): whole-body table-load issue-order interleave.
  Orig hoists all 16 byte-extract rlwinm webs to the loop top then interleaves
  lwzx/rotlwi/xor; next-round key loads land mid-body. TRIED: IRO-0 (195 diffs, worse
  than 183 baseline), IRO-1 (same 195), `nextState[4]` array (183 = scalarized
  identical), `state[4]`+`nextState[4]` arrays (180), fused key-XOR into nextState
  assignments (192, savegpr_20). All reverted — issue-order wall, no lever.
- AESiDecryptBlock 78.96 (246=246 insns): IRO-0/IRO-1 both drop fuzzy to ~70 (+7 insns,
  266 normalized diffs vs 290 baseline — normalized counts mislead again). Reverted.
  Allhands exhaustive-decl-order docs predate IRO but the pragma is verified harmful
  here — remaining residual is the same table-load scheduler family.

## MWCC scheduling-pragmas sweep (post-#1296 orchestrator hint)

Target: AESiEncryptBlock/DecryptBlock table-load interleave (orig hoists ~11 rlwinm
extracts before first lwzx; ours issues loads after ~4).

Per-fn pragma results (normalized diffs -> objdiff fuzzy):
- `#pragma scheduling off`   EncryptBlock 183->178 norm, fuzzy 65.81->36.20 (revert)
- `#pragma scheduling once`  EncryptBlock 183->179 norm, fuzzy ->40.54 (revert)
- `#pragma scheduling twice` EncryptBlock 183 (no change), DecryptBlock 290 (no change)
- `#pragma scheduling 600`   rejected by MWCC 3.0a5.2 (CPU names only)
- `#pragma scheduling 750`/`gekko` 183 (=default), `603`/`generic` 237 (worse)
- `#pragma schedule_twice on`/`scheduling on`/`twice` 183 (no-ops)
- `-opt schedule_twice` cflag: not a valid -opt for 3.0a5.2 (opts: prop,strength,dead,peep,schedule,display|dump)
- `-schedule twice|twice,750|=twice` cflag: all rejected by 3.0a5.2 arg parser
- `-opt schedule` cflag: 183 (no change)

Source restructures (all reverted, fuzzy-measured):
- 16 named table-value temps (t0..t15): 149 norm but fuzzy 65.81->58.99
- named index vars i0..i15 + 16 loads: 149 norm (index vars forwarded/CSE'd), fuzzy also down
- column-order extraction (all >>24, then >>16, >>8, &255): 228 norm (worse)

Cross-check on AOSS fns:
- AOSSi_WLANConnect `scheduling twice`: norm 28->2 (li r5,0x7c4/mr r3,r27 pair only)
  BUT fuzzy unchanged 98.71 - remaining residual is the same marshal-order operand tie.
- AOSSi_WLANGetBSSList `once` 46->43 norm, fuzzy 98.48->93.53 (harmful); `twice` no-op; `off` 69
- AOSSXorBufferWithKey `twice` 61 (no-op); `off` 142 (worse)
- AOSS_Init_old `twice` 1263 (no-op)

Conclusion: the AES interleave is NOT a scheduling-pragma wall - MWCC's default
gekko scheduler already matches orig's pass config; the residual is allocator
web-lifetime/ready-set structure with no known source lever. `scheduling twice`
is a real lever ONLY for instruction-issue-order residuals (marshal pairs), and
even there fixes ordering without moving objdiff fuzzy.

## Round 2: structural decode attempts on AESiEncryptBlock (orchestrator hint)

Baseline macro form remains best (183 norm, fuzzy 65.81). All reverted:
- key as `const u32 (*key)[4]` pointer-to-row (+key++): identical 183
- state[4]/nextState[4] with strided (i+k)&3 indices + for-loops: 230
- fused `nextStateN = ENCRYPT(...) ^ key[N]` (states assigned at end): 231
- state copied to t0..t3 temps at loop top: 183 (CSE folds)
- two-phase combines (all rotated-halves then all tail-halves): 231
- xor tree rebalance `(A^B)^(C^D)` and raw-term-first reorder: 175 norm, fuzzy 60.0/60.3
- TU cflags -O4,s: 263 norm (worse); -O3: 177 norm, fuzzy 60.3/70.2 (worse)
- prologue emits `srwi` extract before the input xors complete in BOTH objects;
  158=158 insns, all residuals are regname + issue-order inside an identical op set
- AOSSi_WLANConnect residual is 2 diffs (mr r3,r27 / li r5,0x7c4 marshal order);
  pointer-local decl moved adjacent to memset: no change (baseline was already 2);
  direct-global &AOSSi_NcdIfConfig form: 163 (the local web is required)

Conclusion: the AES loop-body interleave is an allocator ready-set artifact;
the register-lifetime shape that produces orig's ordering is not expressible
through these source levers. No scheduling/-O lever improves fuzzy.

## Round 3: fn-local static lever (swarm #1299 hint) + pragma combos

Refuted for this leaf:
- Op-multiset check: EncryptBlock and DecryptBlock emit IDENTICAL opcode
  histograms vs orig (158=158, same op counts) — residual is pure
  issue-order + regname. Any memory-backed intermediate (static buffer)
  ADDS lwz/stw ops orig provably lacks.
- No SDA/r13/r2-relative accesses in orig AESi*Block, WLANConnect,
  WLANGetBSSList, AOSS_Init_old — globals go through lis+addi.
- `static u32 sbuf[4]/nbuf[4]` state buffers: 305 norm diffs (lwz/stw
  traffic), reverted.
- Pragma combos: iro1+sched-twice 195, iro0+sched-twice 195, iro2+sched-twice
  177 (all worse than 183 baseline or no better), iro1 alone 195.
- mw_version lever reported dead by orchestrator (swept, identical/worse).

Standing wall: AESiEncryptBlock/DecryptBlock = allocator ready-set ordering
inside an identical instruction multiset. No scheduling/IRO/O-level/cflag/
static/source-structure lever changes it in the right direction.
AOSSi_WLANConnect: 2-insn marshal-order pair (mr r3,r27 vs li r5,0x7c4);
all decl/static/source forms tried.

## Round 4: const-source + scoped-table hint (#1304) + Init_old op-diff decode

Post-#1296 rebase state: AOSSXorBufferWithKey landed by swarm (100). Remaining
in leaf: AOSS_Init_old 96.62, AOSSi_WLANGetBSSList 98.48,
AOSSi_WLANConnect 98.71, AESi*Block (stays as-is per orchestrator).

AOSS_Init_old op-histogram diffs (M=mine vs orig): add +1, b -1, bgt +1,
ble -1, bne -3, cmplw +2, cmplwi -2, li -1, mr +1 — real structural gap:
- Mine emits `cmplw r3,r27` at the two AOSSi_Alloc NULL checks (0xc94/0x154c)
  where orig emits `cmpwi r3,0` — the classic pinned-zero wall: MWCC shared
  one zero web in r27 across the fn's many li 0/cmpwi sites; orig
  rematerializes. All 4 pragma variants (iro 0/1/2, iro1+sched-twice) no-op.
- Orig keeps 3 more `bne` and 2 more `cmplwi r0,1` (0xd60/0x1620 = likely
  AOSSi_cancel_flag==1 sites where mine fused differently).

Scoped-retry-counter attempt (move unlockRetries/cleanupRetries/scanRetries
to uninit decls + assign before each loop — births webs later per the scoped-
locals hint): GetBSSList 46->167 diffs, reverted.

WLANConnect memset(&AOSSi_NcdIfConfig) direct-global + memsetTarget alias
forms: both still forward to the r27 web, 2 diffs unchanged.

const-table analysis: ipAddress/etc are non-const .data (written by
AOSS_SetStaticIpConfig) — can't be const; supportedRates is .data non-const
matching orig's sections (no .rodata in orig .o) — const would break data.

## Round 5: Init_old u32-deref decode (orchestrator's missing-checks lead)

Orchestrator hypothesized missing cancel_flag reads — refuted: 14 lwz
AOSSi_cancel_flag sites in BOTH objects. Orig's extra cmplwi r0,1 at
0xd60/0x1620 are `*s_accessPointConfig == 1` compares: MWCC emits cmplwi
(unsigned) vs my cmpwi (signed) keyed off the COMPARE OPERAND's type —
s_accessPointConfig stays `int*` (file is full of (int*)0x0 literal casts)
but the deref needs an unsigned compare: `(u32)*s_accessPointConfig == 1u`
at the two wait-loop break sites (lines 881/1233) matching line 675's
existing pattern. All 3 sites now cmplwi r0,1; cmplwi count 17=17.
Init_old 96.62 -> 96.69; fn now 1581 vs orig 1584 insns.

Remaining real gaps: pinned-zero cmplw r3,r27 at both AOSSi_Alloc NULL
checks vs orig cmpwi r3,0 (all pragma forms no-op); bgt-vs-ble+b layout at
the manufacturerLength<=0xd memcpy guard (goto form folds back to bgt —
orig's 2-branch layout implies a merge/region structure source can't
reproduce); net -3 insns somewhere in mass-rotation noise.

## Round 6: #1311 levers (declsearch, inline-helper, marshal forms) post-#1314

Post-rebase scope: GetBSSList matched by swarm #1314; aes Matching #1311
(object rebuilds identical). Remaining: AOSS_Init_old 96.70,
AOSSi_WLANConnect 98.71.

WLANConnect 2-insn marshal swap (li r5,0x7c4 vs mr r3,r27 order) refuted
with ALL new levers: (void*)ipConfig, sizeof(AOSSi_NcdIpConfig), folded
`memset(ipConfig = &...,...)` assignment form, and static-inline
pointer-param helper AOSSi_ClearIpConfig — every form keeps the r27 web and
MWCC emits mr-first. Pure marshal-order tie; declsearch found only the 2
leading decls (no improvement).

Init_old: declsearch.py --lines 391 435 (45-decl block, 100 evals) found a
marginally better order (waitAttempt front, initialWait later): kept,
96.69 -> 96.70. Pinned-zero root located: `li r27,0`@0xb34 — ONE shared
zero web pinned fn-wide (stw/sth stores + addc/adde + 2 cmplw) where orig
pins `input` in r27 (addi r27,r4,0) and remats zero per-site. Orig's
pinned-input vs pinned-zero callee choice is an allocator web-priority
decision; source can't declare which constant webs win a callee reg.
