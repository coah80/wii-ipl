# g-aoss attempts, 2026-10-09

Assigned worktree data-d1, branch agent/w1009/g-aoss, base 54ca052b. Scope AOSS_Init_old and AOSSi_WLANConnect. Read opus-common.md, AGENTS.md, unslop, prior AOSS logs and 509c4f11. Preserve rx67c.attempts.md. No pushes, PRs, merges, rebases, other-worktree edits or subagents.

Initial full 43U build passed. Target AOSS .sdata2 contains ffffffff00000000, 8 bytes with section alignment 8. Opus replay emits four bytes, ffffffff; objdiff rejects the entire 8-byte section, accounting for DATA DROP 2800 -> 2792. Both main and Opus emit 364 bytes in .data versus target 368, because the split includes final section alignment. This .data extent alone is not the reported regression.

## Attempts

- opus-replay: 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 4}. Replay 509c4f11 without changing its source.
- defaults-array-typed-view: 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Preserve the existing four halfword option defaults and read its connection/response pair as a struct.
- defaults-array-pairs: 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Preserve the existing four halfword option defaults and read its connection/response pair as a struct.
- defaults-union-view: 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Preserve the existing four halfword option defaults and read its connection/response pair as a struct.
- connect-alias-void: 2/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Typed config view survives into the later NCD call; target has one coalesced config pointer.
- connect-alias-typed: 2/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Typed config view survives into the later NCD call; target has one coalesced config pointer.
- connect-alias-bytes: 2/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Typed config view survives into the later NCD call; target has one coalesced config pointer.
- connect-local-static-ip: 2/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Local static config limits alias edges, lever 35; trial only until data/order verification.
- connect-local-static-both: 2/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Local static config limits alias edges, lever 35; trial only until data/order verification.
- connect-memset-result: 14/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Consume the memset return value as the typed config pointer.
- connect-success-value: 105/155 positional diffs, 154/155 instructions; sections {'.data': 48}. Use the current initialization success value in related zero stores and memset.
- connect-pointer-at-entry: 79/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Initialize the real config pointer at declaration, before wireless setup.

Full single/pairwise optimizer sweep: AOSS_Init_old best 1264 positional differences; WLANConnect best 2. No pragma hit. Fixed defaults array with typed struct view restores AOSS data 2800/2800 and preserves Opus Init score 97.33775%, 20/21 exact.

The first Init source-search selected its earlier prototype and found no mutations. This was not Init coverage. Local script now selects the definition.
- connect-helper-return-pointer: 24/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Factor the complete IPv4 initialization into a real inline helper; no dummy or identity operation.
- connect-helper-parameter: 2/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Factor the complete IPv4 initialization into a real inline helper; no dummy or identity operation.
- connect-helper-return-result: 24/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Factor the complete IPv4 initialization into a real inline helper; no dummy or identity operation.
- connect-helper-return-void-pointer: 24/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Factor the complete IPv4 initialization into a real inline helper; no dummy or identity operation.
- connect-helper-return-pointer-scoped: 24/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Factor the complete IPv4 initialization into a real inline helper; no dummy or identity operation.
- init-message-type-u8: objdiff 97.34406%, exact 20, data 2800; 1410/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Name the actual protocol message code/socket-address width instead of a loop-wide unrelated constant.
- init-address-length-u8: objdiff 97.09659%, exact 20, data 2800; 1410/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Name the actual protocol message code/socket-address width instead of a loop-wide unrelated constant.
- init-both-u8: objdiff 97.119316%, exact 20, data 2800; 1344/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Name the actual protocol message code/socket-address width instead of a loop-wide unrelated constant.
- init-message-type-u32: objdiff 97.34406%, exact 20, data 2800; 1410/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Name the actual protocol message code/socket-address width instead of a loop-wide unrelated constant.
- init-address-length-u32: objdiff 97.09659%, exact 20, data 2800; 1410/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Name the actual protocol message code/socket-address width instead of a loop-wide unrelated constant.
- init-both-u32: objdiff 97.119316%, exact 20, data 2800; 1344/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Name the actual protocol message code/socket-address width instead of a loop-wide unrelated constant.
- init-message-type-int: objdiff 97.34406%, exact 20, data 2800; 1410/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Name the actual protocol message code/socket-address width instead of a loop-wide unrelated constant.
- init-address-length-int: objdiff 97.09659%, exact 20, data 2800; 1410/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Name the actual protocol message code/socket-address width instead of a loop-wide unrelated constant.
- init-both-int: objdiff 97.119316%, exact 20, data 2800; 1344/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Name the actual protocol message code/socket-address width instead of a loop-wide unrelated constant.
- init-poll-named-products: objdiff 97.3125%, exact 20, data 2800; 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Keep native OSTime addition and the existing u32 product truncation; give real products separate names.
- init-poll-separate-components: objdiff 97.3125%, exact 20, data 2800; 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Keep native OSTime addition and the existing u32 product truncation; give real products separate names.
- init-manufacturer-single-pass-guard: objdiff 97.33775%, exact 20, data 2800; 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Express the observed bounded manufacturer copy with a structured exit; same bytes and call count.
- init-manufacturer-bounded-copy-loop: objdiff 97.08839%, exact 20, data 2800; 1154/1584 positional diffs, 1580/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Express the observed bounded manufacturer copy with a structured exit; same bytes and call count.
- init-manufacturer-bounded-copy-for: objdiff 97.08839%, exact 20, data 2800; 1154/1584 positional diffs, 1580/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Express the observed bounded manufacturer copy with a structured exit; same bytes and call count.
- init-manufacturer-switch-length-range: objdiff 96.98737%, exact 20, data 2800; 1305/1585 positional diffs, 1585/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Express the observed bounded manufacturer copy with a structured exit; same bytes and call count.
- init-manufacturer-positive-branch-label: objdiff 97.33775%, exact 20, data 2800; 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Express the observed bounded manufacturer copy with a structured exit; same bytes and call count.
- init-retry-switch-result: objdiff 97.27146%, exact 20, data 2800; 1314/1584 positional diffs, 1579/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Natural result dispatch with a single state-success test and the existing config test.
- init-retry-nested-success: objdiff 97.33775%, exact 20, data 2800; 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Natural result dispatch with a single state-success test and the existing config test.
- init-retry-continue-then-success: objdiff 97.33775%, exact 20, data 2800; 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Natural result dispatch with a single state-success test and the existing config test.
- init-preheader-type-u8: objdiff 97.39141%, exact 20, data 2800; 1263/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Initialize actual message fields after the unassigned socket-option guard, exactly in the protocol preheader.
- init-preheader-identity-length-u8: objdiff 97.33775%, exact 20, data 2800; 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Initialize actual message fields after the unassigned socket-option guard, exactly in the protocol preheader.
- init-preheader-both-u8: objdiff 97.39141%, exact 20, data 2800; 1263/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Initialize actual message fields after the unassigned socket-option guard, exactly in the protocol preheader.
- init-preheader-type-u32: objdiff 97.39141%, exact 20, data 2800; 1263/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Initialize actual message fields after the unassigned socket-option guard, exactly in the protocol preheader.
- init-preheader-identity-length-u32: objdiff 97.33775%, exact 20, data 2800; 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Initialize actual message fields after the unassigned socket-option guard, exactly in the protocol preheader.
- init-preheader-both-u32: objdiff 97.39141%, exact 20, data 2800; 1263/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Initialize actual message fields after the unassigned socket-option guard, exactly in the protocol preheader.
- init-preheader-type-int: objdiff 97.39141%, exact 20, data 2800; 1263/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Initialize actual message fields after the unassigned socket-option guard, exactly in the protocol preheader.
- init-preheader-identity-length-int: objdiff 97.33775%, exact 20, data 2800; 1264/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Initialize actual message fields after the unassigned socket-option guard, exactly in the protocol preheader.
- init-preheader-both-int: objdiff 97.39141%, exact 20, data 2800; 1263/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Initialize actual message fields after the unassigned socket-option guard, exactly in the protocol preheader.
- compiler-AOSSLink-3.0a5: objdiff 98.70968%, exact 13, data 2432; 2/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.
- compiler-AOSSLink-3.0a3.4: objdiff 98.70968%, exact 13, data 2432; 2/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.
- compiler-AOSSLink-3.0a3.3: objdiff 98.70968%, exact 13, data 2432; 2/155 positional diffs, 155/155 instructions; sections {'.data': 48}. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.
- compiler-AOSSLink-2.7: compile failed. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.
- compiler-AOSSLink-2.6: compile failed. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.
- compiler-AOSS-3.0a5: objdiff 97.39141%, exact 20, data 2800; 1263/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.
- compiler-AOSS-3.0a3.4: objdiff 97.39141%, exact 20, data 2800; 1263/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.
- compiler-AOSS-3.0a3.3: objdiff 97.39141%, exact 20, data 2800; 1263/1584 positional diffs, 1578/1584 instructions; sections {'.data': 364, '.sdata2': 8}. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.
- compiler-AOSS-2.7: compile failed. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.
- compiler-AOSS-2.6: compile failed. Check neighboring SDK compiler versions; require all siblings and sections to stay exact before considering a config change.

## Evidence and retained source

- AOSS target .sdata2 is 8 bytes, ffffffff00000000. The original two symbols cover offsets 0..2 and 2..8. Preserve the existing u16[4] defaults and read its first pair through AOSSWaitDefaults. All three reconstructed array/union views emit the same eight bytes; retained form keeps the original four halfword initializer.
- The target reads r14 at Init instruction 509, relative offset 0x7f4, with cmpwi r14,0. No earlier instruction names r14. Its first write is instruction 576, li r14,0x11. _savegpr_14 stores incoming registers without changing r14. This verifies the saved Opus unassigned socketOptionResult against the target and follows user-approved lever 10. No new undefined-value trick was invented.
- Keep requestMessageType initialized to 0x11 after the socket-option guard and successful SOBind, in the real protocol preheader. This moves the protocol constant to the target region and improves objdiff 97.33775 -> 97.39141 without changing instruction count or any exact sibling. The earlier function-entry initializer trials are rejected: they write r14 before the target's unassigned guard.
- Source-search: WLANConnect 959 trials in 180 seconds, no gain. Corrected Init definition search 723 trials in 240 seconds, no gain. No automatic mutation is retained. Searches used separate /tmp/g-aoss-* source and object files.
- Neighboring GC/3.0a5, 3.0a3.4 and 3.0a3.3 compilers produce identical remaining scores. GC/2.7 and 2.6 reject -ipa file. Compiler configuration is unchanged.
- WLANConnect still differs only at instructions 66 and 67. Target sets r5 to 0x7c4 before copying r27 to r3; source performs that copy first. Its 13 exact siblings and 2432 bytes of data are unchanged. Local-static, cross-use alias, return-pointer and real initialization-helper trials did not resolve this scheduler tie. AOSSLink.c is unchanged.
- Init remains 1578/1584 instructions. Missing target structure includes the manufacturer ble plus unconditional branch, three consecutive same-compare bne pairs, and protocol constant materialization. The DS implementation has the same bne pairs. No redundant source condition or artificial branch was added to reproduce them. Both owned units remain NonMatching because neither is fully exact.

Final gate and independent current-object checks follow.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 9856/16192 data 2800/2800 functions 20/21 fuzzy 98.9792 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 20/21
[src/scene/setting/AOSS]   section .bss size 2368 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 100.0
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 98.97925
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 97.39141
[src/scene/setting/AOSS] baseline: code 9856/16192 data 2800 functions 20 fuzzy 98.6781
[src/scene/setting/AOSSLink] pool: IDENTICAL
[src/scene/setting/AOSSLink] objdiff: code 1576/2196 data 2432/2432 functions 13/14 fuzzy 99.6357 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 13/14
[src/scene/setting/AOSSLink]   section .bss size 2344 match 100.0
[src/scene/setting/AOSSLink]   section .data size 48 match 100.0
[src/scene/setting/AOSSLink]   section .sbss size 40 match 100.0
[src/scene/setting/AOSSLink]   section .text size 2196 match 99.635704
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANConnect 98.70968
[src/scene/setting/AOSSLink] baseline: code 1576/2196 data 2432 functions 13 fuzzy 99.6357
regressions vs baseline: 0
global matched_code_percent: 99.20325 -> 99.20325
global fuzzy_match_percent: 99.97473 -> 99.97636
global complete_code_percent: 94.18519 -> 94.18519
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Independent focused checks: AOSS pool 1/1 strings identical, AOSSLink 0/0 identical; WLANConnect odiff/ctxdiff 2/155, equal 0x26c sizes. Init odiff/ctxdiff 1263 differences, 1578/1584 instructions, sizes 0x18a8/0x18c0. No new exact functions. The data regression is fully repaired; both units remain unlinked. All experimental AOSSLink and compiler changes were discarded. Retained paths are AOSS.c and this attempts log.

## w1011/aoss continuation (worker devin-w1011)

### NEW LEVER: redundant `||` disjunct emits dead same-flags branch
`AOSS_Init_old` triple-`bne` decode: orig's `cmpwi r3,0; bne A; bne B; lwz cfg; lwz *cfg; cmplwi 1; beq B` = `if (state != 0) ->A` then `if (state != 0 || *ptr == 1) ->B` — MWCC emits the provably-dead first disjunct's `bne` because `||` conditions do NOT get the dead-branch fold a standalone `if (state != 0)` does (verified: same-var inner if folds entirely; different-var holding same value also folds — VN unifies). Fix applied at the SetNCDIPAddr else-site: inner `if (state != 0 || s_accessPointConfig[0] == 1)` (reloc-verified: insn 373/374 = s_accessPointConfig then *cfg). 1582/1584 insns, 534 positional diffs (was 1578/722). `else if` form breaks braces — kept `else { if (cond||x) {...} work }`.
- Residual per-site mapping unclear: my pair landed at MY insn ~304 while orig's three pairs sit at 371/713/1273 — the other two `if (state != 0)` sites (BSSList/CheckAP ~539, wait_for_packet ~1132) likely need the same idiom.
- Also remaining: `ble; b` dual-branch at 272 (`manufacturerLength <= 0xd` — orig enters body via taken-ble + unconditional-b; ours single bgt), protocol-constant materialization region ~566-590 (mulhw + lis/addi 0xc0a80b01 store+reload — IP 192.168.11.1 materialized via named constant?), spill-order block ~969-985.
- AOSSi_WLANConnect: all sched-copy shapes dead-end (u8* typed view cross-block, shared fillByte, result-as-fill, view-first chain, cfg-block) — swarm's two required internal shapes (chain-copy / r4+r5 both reg-copies) unreachable from source. Confirmed wall.

## w1011/aoss wave-2 (opt-level + twin-branch decode)

- `#pragma optimization_level 2` scoped to AOSS_Init_old: 1603 insns/1040 diffs (regression). `optimization_level 3`: inert (identical 1582/534 — O4,p TU flag dominates). `#pragma ppc_iro_level 0/1`: inert. Opt-level hypothesis (idct-style) disproved for this fn.
- insn-272 `ble;b` decoded from raw bytes (capstone printed reloc-addend targets — real targets are sign-extended imm): `0x40810008` = ble+8 -> memcpy body; `0x48000014` = b+0x14 -> SetNCDIPAddr args. Orig emits TWIN-BRANCH (ble->body + b->join) vs ours bgt-skip. Failed producers: goto-label form, explicit empty else{}, do{...}while(0), `|| *cfg` at lines 539/1194 (773d regression — orig does NOT deref *cfg at those sites). Likely an MWCC block-layout artifact — unresolved.
- Residual bne sites at orig 371/713/1273: NOT `||`-sites (adding *cfg loads regresses); undecoded.

## w1011/aoss wave-3 (volatile-param lever — assessed N/A)

- pdm's `volatile pf_u8* buf` idiom (ordered loads from hardware-filled mem) does NOT apply: WLANConnect's 2d is arg-marshal `li r5/mr r3` scheduling — no loads involved. `NCDIpConfig* volatile ipConfig` spills the pointer (166 insns/109d regression); `memset((volatile T*)p,...)` is an illegal qualifier-discard error on MWCC.
- Init_old residual regions (twin-branch @272, dead-bne @371/713/1273, materialization ~566-590, spills ~969-985) are control-flow/constant-materialization classes — no reordered buffer loads to pin. `*cfg`/`AOSSi_cancel_flag` reads already emit plain loads matching orig.

## w1011/aoss wave-4 (opt_propagation off — assessed N/A)

- Scoped `#pragma push/opt_propagation off/pop` around AOSS_Init_old: INERT (1582/534 identical). File-top unscoped: inert. WLANConnect: inert (2d). Pragma accepted (no warning) — but Init_old's `-O4,p` + `-inline off` + global `-ipa file` leaves nothing for it to change.
- Verified no prop-signature in residual: orig's `cmpw/cmplw reg,reg` sites (172/434/635/776/997/1098/1336, e.g. `extsh r0; cmpw r0,r16` loop-limit compares) all sit inside rename regions — mine emits the same reg-reg compares with different coloring, not `cmpwi` constant-folds. The 534d wall is reg allocation + the twin-branch + dead-bne sites, not propagation.
