# clean3-c4 cleanup attempts

Worktree `clean3-c4`, branch `agent/w1009/clean3-c4`, baseline `8a67b68cf`.
Read clean3-head.md, cleanup-common.md, repository AGENTS.md, unslop, writing-for-agents, and prior cleanup logs for all six assigned files. Worker conversation stays silent.

Baseline build and fresh report passed DECOMPLETE_OK. DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`.
Acceptance: preserve every allocated ELF section byte, alignment, named exported symbol and resolved relocation. Gate all touched units, regenerate the report, and run both completion checks.

## Prior evidence and scope

- NandSDWorker: 149 remaining jumps target common cleanup or return paths. Wave 2 already tested early returns, result-controlled loop exits, direct stack-end pointers, weak-emitter removal, symbol-mode removal and copied booleans. Preserve those measured requirements.
- ESMisc: 24 jumps, chiefly shared cleanup. Preserve the Zelda title-ID copy, zero-test intrinsics and direct verification failure edges. Inline validation and loop-break/status variants already changed code.
- NandShared: removing the two error-stage self-copies removes two target instructions. Preserve the shared error report.
- Nwc24Manager: retry-loop cleanup already landed. Most jumps are shared attachment/text cleanup; the received-message jump skips attachment processing and record creation.
- AOSS: prior declaration-order and cursor-placement pragma trials changed eight or more text bytes. Printable-validation loop breaks changed 256 bytes. Scalar checksum replacements and legacy poll-store deletion failed exactness.
- ATERM: wave 2 already replaced parser entry jumps with inline option readers and the timeout branch with a short-circuit condition. Remaining nine jumps share driver unlock or cleanup paths.

## Trials
- REVERT `src/system/iplNwc24Manager`: receive use the API-sized u32 opt-out app ID and remove pointer-punned initialization. changed ('.text', 0); receive__Q33ipl5nwc247ManagerFv: 1005->1005 instructions, 32 raw instruction differences.
- KEEP `src/system/iplNwc24Manager`: receive guard attachment processing and record creation instead of jumping to the received flag. all allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/scene/setting/AOSS`: AOSS_Init_old structure final configuration success and failure, removing three dispatch/exit jumps. all allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/scene/setting/AOSS`: AOSSValidateInitConfig replace six jump-based printable scans with one inline validator returning status. all allocated sections, exported symbols and resolved relocations identical.
- REVERT `src/scene/setting/AOSS`: AOSSApplyAuthOptions remove level-3 pragma with separate outer-record and inner-option cursors. changed ('.text', 0); AOSSApplyAuthOptions: 114->114 instructions, 34 raw instruction differences.
- KEEP `src/scene/setting/AOSS`: AOSS_Init_old guard state-two reconnection before advancing the protocol state. all allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/scene/setting/AOSS`: AOSSi_Init replace the cleanup-result join label with an inline socket-library cleanup routine. all allocated sections, exported symbols and resolved relocations identical.
- REVERT `src/scene/setting/AOSS`: AOSSApplyAuthOptions remove the pragma by separating option search into an inline record finder. changed ('rel', ('.text', 0)), ('.text', 0), exports; AOSSApplyAuthOptions: 114->118 instructions, 106 raw instruction differences.
- KEEP `src/scene/setting/AOSS`: AOSS_Init_old remove the unreferenced packetLength local. all allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/scene/setting/ATERM`: ATERMStartNetworkStack remove the unreferenced convertedHost local. all allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/scene/setting/AOSS`: AOSS_Init_old replace initial-link entry, back-edge and success jumps with a while loop. all allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/system/iplNandSDWorker`: get_nand_free_area remove the unreferenced result local. all allocated sections, exported symbols and resolved relocations identical.
- REVERT `src/system/iplNandShared`: openTicketFile_ express zero error stages directly instead of self-copying. changed exports, ('rel', ('.text', 0)), ('rel', ('.data', 0)), ('.text', 0); openTicketFile___Q33ipl4nand10SharedFileFv: 180->182 instructions, 137 raw instruction differences.
- REVERT `src/system/iplNwc24Manager`: receive use scoped u32 opt-out app ID storage at its initialization point. changed ('.text', 0); receive__Q33ipl5nwc247ManagerFv: 1005->1005 instructions, 26 raw instruction differences.
- KEEP `src/scene/setting/AOSS`: AOSSValidateInitConfig name the printable-check result as a status. all allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/scene/setting/AOSS`: AOSS_Init_old structure request/poll/receive repetition as one outer loop with continue and an inner poll break. all allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/scene/setting/AOSS`: AOSS_Init_old restore consistent two-space indentation after the structured loop rewrites. all allocated sections, exported symbols and resolved relocations identical.
- KEEP `src/utility/iplESMisc`: checkContentsNum name metadata/private-content counts and the installed-content search index. all allocated sections, exported symbols and resolved relocations identical.
- REVERT `src/system/iplNwc24Manager`: receive use API-sized app-ID storage declared after the group ID. changed ('.text', 0); receive__Q33ipl5nwc247ManagerFv: 1005->1005 instructions, 32 raw instruction differences.
- KEEP `src/scene/setting/AOSS`: separate the structured initializer from its printable validator. all allocated sections, exported symbols and resolved relocations identical.
- REVERT `src/scene/setting/AOSS`: AOSS_Init_old remove the repeated initialization-status guard from its successful branch. changed exports, ('rel', ('.data', 0)), ('rel', ('.text', 0)), ('.text', 0); AOSS_Init_old: 1584->1567 instructions, 1249 raw instruction differences.
- KEEP `src/system/iplNwc24Manager`: document the halfword app-ID declaration retained after three API-sized storage trials. all allocated sections, exported symbols and resolved relocations identical.

## Retained cleanup

- AOSS: 65 -> 46 gotos. Initial connection retries now use a while loop. Protocol send/poll/receive processing uses an outer loop, continue on state updates, and an inner poll break. Final configuration success/failure uses if/else. Six printable scans share a typed inline validator, and library cleanup uses an inline routine with normal returns. Removed two unreachable cleanup blocks and the unreferenced packetLength local. Remaining jumps target the shared socket cleanup, initialization return, or invalid-config cleanup.
- Nwc24Manager: 14 -> 13 gotos. Guard attachment processing and record creation with the successful attachment-count result, then set the received flag directly. Remaining jumps share message or text cleanup. Kept the halfword opt-out app-ID declaration with a compiler note after three natural u32 storage variants changed 26 or 32 instructions.
- NandSDWorker: removed the unreferenced get_nand_free_area result local. All 149 remaining jumps are the shared resource/error exits reviewed in wave 2. The symbol-mode pragma, weak emitter, stack-end pointer, copy-flag conversion and initialized save buffer retain prior measured requirements.
- ESMisc: named metadata/private-content counts and the installed-content search index in checkContentsNum. Kept its 24 shared exits, including the Zelda verifier's direct failure edges and the previously tested zero-test intrinsics.
- NandShared: source unchanged. Its eight jumps share one error report. Kept both self-copies; replacing them with explicit zero initialization adds two instructions, while the prior removal trial drops two.
- ATERM: removed the unreferenced convertedHost local. Kept all nine shared cleanup/unlock exits, whose parser and timeout dispatch had already been structured in wave 2.

## Requirements retained with new evidence

AOSSApplyAuthOptions keeps its level-3 scope and existing one-line comment. A separate inner cursor changes 34 instructions. An inline record finder adds four instructions and changes relocations. The original table/cursor allocation still needs the pragma. No new pragma, use-site volatile, assembly, carrier, uninitialized value or forced section was added.

AOSS's repeated initialization-status guard stays. Removing it reduces AOSS_Init_old from 1584 to 1567 instructions and changes relocation ownership. The existing compiler-requirement comment remains. Checksum grouping and legacy select stores retain prior rejected-trial evidence.

22 compiler trials: 15 kept, 7 restored. Formatting and required comments are included in that count. Every rejected source change was restored and rebuilt before the next trial.

## Final verification

Ran the required six-unit gate once with --quick. GATE PASS: full 43U build passed, zero regressions, zero added forbidden patterns and zero readability warnings. Gate transcript: /tmp/clean3-c4-gate.log.

| Unit | Exact original functions | Code bytes | Data bytes | Gotos |
|---|---:|---:|---:|---:|
| src/system/iplNandSDWorker | 203/203 | 51428/51428 | 12312/12312 | 149 -> 149 |
| src/utility/iplESMisc | 31/31 | 11200/11200 | 4416/4416 | 24 -> 24 |
| src/system/iplNandShared | 8/8 | 1372/1372 | 136/136 | 8 -> 8 |
| src/system/iplNwc24Manager | 53/53 | 10252/10252 | 888/888 | 14 -> 13 |
| src/scene/setting/AOSS | 21/21 | 16192/16192 | 2800/2800 | 65 -> 46 |
| src/scene/setting/ATERM | 26/26 | 19204/19204 | 18864/18864 | 9 -> 9 |

All six units retain 100% code, data, linking and every reported section. All allocated section bytes, alignment, exported symbols and resolved relocations equal the initial source-object snapshots.

Section-aware verification against retail confirms all 342 original functions have identical raw bytes and decoded instruction counts. It uses each function's st_shndx, covering NandSDWorker's two text sections. Its 210 source functions include seven pre-existing dead-stripped stand-ins/path helpers; the source function inventory also equals the baseline. The initial verifier incorrectly required equal retail/source inventory sizes; it was corrected to check every retail function and preserve the complete baseline source inventory. Gate's known name-only .text decoder still prints 7/203 for NandSDWorker; section-aware verification confirms 203/203. Evidence: /tmp/clean3-c4-sections.log, helper /tmp/clean3-c4-verify.py.

Explicit pool_diff checks are identical: NandSDWorker 280/280, ESMisc 114/114, NandShared 2/2, Nwc24Manager 21/21, AOSS 1/1, ATERM 0/0 strings.

Focused ctxdiff checks all report diffs 0: AOSS_Init_old 1584/1584, AOSSValidateInitConfig 219/219, AOSSi_Init 139/139, Manager::receive 1005/1005, ESMisc::checkContentsNum 167/167, ATERMStartNetworkStack 154/154.

Regenerated build/43U/report.json and ran build/43U/ok. Completion checker: DECOMPLETE_OK. Assembly inventory: 162 ORIGINAL functions, zero placeholders, ASM INVENTORY PASS. DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d. git diff --check passed.

Only five assigned source files and this log changed. No header or configure.py changes, push, PR, merge, rebase, other-worktree edits or subagents.

## Source commits
- `0ce159011`: `src/system/iplNandSDWorker.cpp`.
- `6efa48ac0`: `src/utility/iplESMisc.cpp`.
- `bf44ac4c9`: `src/system/iplNwc24Manager.cpp`.
- `7b5e95713`: `src/scene/setting/AOSS.c`.
- `c2ae7fb2a`: `src/scene/setting/ATERM.c`.
