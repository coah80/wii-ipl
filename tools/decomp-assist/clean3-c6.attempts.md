# clean3-c6 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/clean3-c6`, branch `agent/w1009/clean3-c6`, baseline `8a67b68cf28b8c650cff03b12c1c19a89b18501b`. Scope is `libs/RVL_SDK/src/bte/*`, `libs/RVL_SDK/include/private/bte/*` and this log.

Read `clean3-head.md`, the complete `cleanup-common.md`, this worktree's `AGENTS.md` and `cleanup2-x1.attempts.md` before editing. Applied unslop and writing-for-agents to this log. Did not repeat the earlier failed removal of the USB callback local, SCO handle checks, SCO database reassignment, BTU callback check or compression link checks.

## Naming and control-flow audit

The proposed 183 placeholder-name debt is a count of protocol names already present in the Broadcom source. The live assigned source and header directories contain 209 occurrences of eight distinct `local_*` identifiers. All eight appear in the fixed Android 4.2.2 Broadcom reference: `local_addr`, `local_bd_addr`, `local_cfg_sent`, `local_cid`, `local_ctrl`, `local_features`, `local_id`, `local_version`. There are zero generated `local_[0-9a-fA-F]+` identifiers. Kept these existing names.

Fetched and read the public reference files at `android-4.2.2_r1`, including [l2c_csm.c](https://android.googlesource.com/platform/external/bluetooth/bluedroid/+/android-4.2.2_r1/stack/l2cap/l2c_csm.c), [btm_devctl.c](https://android.googlesource.com/platform/external/bluetooth/bluedroid/+/android-4.2.2_r1/stack/btm/btm_devctl.c), [port_api.c](https://android.googlesource.com/platform/external/bluetooth/bluedroid/+/android-4.2.2_r1/stack/rfcomm/port_api.c), and the private [l2c_int.h](https://android.googlesource.com/platform/external/bluetooth/bluedroid/+/android-4.2.2_r1/stack/l2cap/l2c_int.h), [port_int.h](https://android.googlesource.com/platform/external/bluetooth/bluedroid/+/android-4.2.2_r1/stack/rfcomm/port_int.h) and [btm_int.h](https://android.googlesource.com/platform/external/bluetooth/bluedroid/+/android-4.2.2_r1/stack/btm/btm_int.h) headers. The initial private-header URLs under `stack/include/` returned 404; the module-directory URLs succeeded.

There are no decompiler gotos in the assigned directories. All five existing gotos are `goto end` in the two USB read callbacks, leading to the shared next-read path. Kept them under the cleanup brief's common-exit rule. No function-scoped compiler pragmas or use-site volatile casts exist in this scope. Kept definition-level volatile declarations.

## Accepted edits

Moved 62 assignments before their conditions while preserving branch order and short-circuit evaluation. Kept idiomatic dequeue assignment loops and guarded compound conditions. Each candidate was rebuilt and compared against the initial full-build object before retention. No names, types, strings, numeric settings or signatures changed.

Source filenames below are under `libs/RVL_SDK/src/bte/`; headers are under `libs/RVL_SDK/include/private/bte/`. Committed each edited file separately.

| File | Cleanup and retained requirements | Target exact functions before to after | Commit |
| --- | --- | --- | --- |
| btm_acl.c | Separated 16 assignments from conditions. | 29/29 to 29/29 | `be42015476` |
| btm_devctl.c | Separated 8 assignments from conditions. Removed an unreachable SCO buffer-size default; documented the retained callback tests. | 33/33 to 33/33 | `018369fe73` |
| btm_inq.c | Separated 8 assignments from conditions. | 25/25 to 25/25 | `54ce9ddf19` |
| l2c_api.c | Separated 19 assignments from conditions. | 13/13 to 13/13 | `169b3d08c3` |
| l2c_link.c | Separated 3 assignments from conditions. | 17/17 to 17/17 | `703c648e78` |
| l2c_utils.c | Separated 2 assignments from conditions. | 33/33 to 33/33 | `54a12e37e3` |
| port_api.c | Separated 2 assignments from conditions. Documented the retained MTU test. | 1/1 to 1/1 | `225f5c47a8` |
| port_rfc.c | Separated 3 assignments from conditions. | 18/18 to 18/18 | `0be0f63840` |
| rfc_mx_fsm.c | Separated 1 assignments from conditions. | 10/10 to 10/10 | `f62565dbac` |
| bt_target.h | Removed 31 unreachable defaults and two inactive configuration alternatives. Kept all active Wii settings. | All 68 BTE units unchanged | `0509e079e9` |
| bta_api.h | Removed five inactive enum placeholders. Kept the active typedefs. | All 68 BTE units unchanged | `7f8c55380f` |

## Restored trials

| File and function | Trial | Evidence and final choice |
| --- | --- | --- |
| port_api.c, RFCOMM_CreateConnection | Remove the repeated inner MTU test and its unreachable else | Allocated `.text`, named symbol positions and relocation targets changed. Restored and rebuilt the object; added one necessary MWCC note. The original function is outside this unit's extracted target range, so the full source object comparison was essential. |
| btm_devctl.c, btm_db_reset | Remove the three already-guarded local callback tests | Allocated `.text`, symbol positions and relocation targets changed. Restored and rebuilt; added one necessary MWCC note. |
| btm_devctl.c, BTM_SetLocalDeviceName | Move command-buffer allocation before its condition | Allocated `.text`, symbol positions and relocation targets changed. Restored and rebuilt the original idiomatic allocation condition. |
| bt_target.h | First removal of the nested inactive MAX_BD_CONNECTIONS alternative | The edit left the outer else/endif. Compilation failed before producing a new object. Corrected the removal boundary and rebuilt all dependent BTE objects successfully before accepting the header. |

## Object and pool verification

The initial full 43U build and DOL hash passed. Captured all 68 configured BTE source objects and the report before editing. Final rebuilt objects preserve every allocated section's bytes, type, flags, alignment and size, every named allocated symbol's position and size, and all resolved relocation targets. Anonymous compiler symbols were compared by section/offset rather than their generated names. The source objects also preserve the functions outside the extracted retail ranges.

Ran `pool_diff.py` against the initial objects and retail objects. Eleven units already have raw pool differences: bta_dm_act, bta_hh_api, btm_inq, gap_api, gap_conn, hidd_api, hidd_conn, hidd_mgmt, l2c_utils, port_api and sdp_db. In particular, port_api has 36 source strings versus zero retail strings, and l2c_utils has eight versus six. No pool byte changed from the initial source objects. Retained these inherited pools; every owned data section reported by objdiff remains 100%.

All 68 BTE units remain `Matching`. Their 733/733 target functions, code, data, linking and every reported section remain 100%. The nine edited source units retain 179/179 target functions. Explicit `ctxdiff.py` checks of the 36 changed functions that exist in the extracted report have equal instruction counts and `diffs 0`. Nineteen other changed source functions are outside their extracted target ranges and are covered by the complete object comparison.

## Final gate

Ran the acceptance gate once at the end with `--quick` over all 68 BTE units, including every consumer of the edited headers. Full 43U build passed; zero regressions, zero net forbidden patterns and zero readability warnings. Regenerated the live report and ran the `build/43U/ok` target. Global report measures are identical to the baseline.

```text
GATE PASS
DECOMPLETE_OK
ASM INVENTORY PASS
DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d
BTE 68 units, 733/733 target functions
Edited source units 179/179 target functions
```

Assembly inventory retains 162 ORIGINAL functions and zero placeholders. `git diff --check` passes. No push, PR, merge, rebase, delegation or other-worktree edit was performed.

Detailed run evidence is in `/tmp/clean3-c6-gate.txt`, `/tmp/clean3-c6-object-evidence.txt`, `/tmp/clean3-c6-ctxdiff.txt`, `/tmp/clean3-c6-pools.txt` and `/tmp/clean3-c6-trials.jsonl`. These temporary files are supplemental; the conclusions and rejected trials are recorded above.
