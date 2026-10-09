# cleanup2-x1 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d11`, branch `agent/w1009/cleanup2-x1`, baseline `85d653b0`. Scope is `libs/RVL_SDK/src/bte/` plus this log. Read the complete cleanup-common.md, including wave-2 guidance, before starting. Applied unslop and writing-for-agents to this report.

## Baseline and reference

The full 43U build passed before any source edits. The initial report passed `DECOMPLETE_OK`; the DOL SHA1 was `26116613f624061ba99c8d1a299aaa6efa85670d`. All 65 BTE units with target code were 100%, covering 733 target functions.

Read the Broadcom source at the fixed Android 4.2.2 tag for naming and control-flow reference:

- [btm_sco.c](https://android.googlesource.com/platform/external/bluetooth/bluedroid/+/android-4.2.2_r1/stack/btm/btm_sco.c)
- [sdp_api.c](https://android.googlesource.com/platform/external/bluetooth/bluedroid/+/android-4.2.2_r1/stack/sdp/sdp_api.c)
- [btu_task.c](https://android.googlesource.com/platform/external/bluetooth/bluedroid/+/android-4.2.2_r1/stack/btu/btu_task.c)

The baseline already used upstream names in btm_sco.c and sdp_api.c. A condition scan found no comma operators. The remaining generated local names were in btu_task1.c, hcisu_h2.c and uusb_ppc.c; inactive reconstruction blocks also contained register labels. No function-scoped pragmas or use-site volatile casts were present. Supplemental files outside the built 43U target were left unchanged.

## Per-file results

All filenames below are under `libs/RVL_SDK/src/bte/`. Every touched unit remains `Matching`, with code, data, functions, linking and each reported section at 100%.

| File | Removed or simplified | Retained and reason | Exact target functions, before to after | Commit |
| --- | --- | --- | --- | --- |
| bta_dm_main.c | Removed two inactive typedef alternatives, an inactive bonding-table row, its abandoned position notes, and an unconditional preprocessor wrapper. | Kept the active table order and typedef shapes. | 2/2 to 2/2 | `50dd730619ca2a8a04107732c9e21dd80d561d53` |
| bta_hh_main.c | Removed the inactive array typedef alternative. | Kept the active state-table typedef. | 3/3 to 3/3 | `fb03259e82db89f4e62eaa0864ebfa5aa9f12c2a` |
| btm_sco.c | Moved HCI buffer allocation before its condition. Replaced raw invalid-handle, active-mode and transaction-collision values with existing HCI constants. | Kept two short-circuit handle lookups and the repeated SCO database address assignment. Separating the lookups or deleting the address assignment changed allocated bytes; one-line MWCC notes identify them. | 15/15 to 15/15 | `9d0bfb0732120d085f5fd49ae5b438f4ba9e5640` |
| btu_task1.c | Restored upstream p_tle, p_msg, i, event, handled and mask names. Named the Wii message-drain flag and timeout callback, used the existing callback typedef and mailbox/timer constants, and removed two unused locals plus their dead assignments. Preserved the OSGetTime call. | Kept the repeated event callback check because deleting it changed allocated bytes. Kept the upstream mailbox-read assignment loops. | 4/4 to 4/4 | `35606af9116237141b6e99e81e7ff231ac597213` |
| gap_utils.c | Removed the inactive duplicate status-conversion stub and its register/range notes. | Kept the real conversion function. | 6/6 to 6/6 | `cb1d3a35878e6a86857888cf92addc8d345aa61d` |
| hcisu_h2.c | Renamed r27 to usb_pipe, identifying the one-based USB pipe. Moved the ACL packet-start assignment before its null check. | Kept packet state, buffer layout and receive ordering. | 8/8 to 8/8 | `865f3d4c5070b8715878faaf577d8a46011e127e` |
| hidh_conn.c | Removed the inactive send-data reconstruction and its stack/register annotations. | Kept the real send-data implementation. | 16/16 to 16/16 | `0a1ff8ba1a02d6c59b39a2b2e876820858be3ae4` |
| l2c_api.c | Removed two inactive compression placeholders. Replaced an empty success branch and else return with a guard. | Kept the link lookup and link-state checks because deleting them changed allocated bytes; a one-line MWCC note explains the retained checks. Kept the target compression-registration stub. | 13/13 to 13/13 | `a40372ead09e320c781f391accc54151c1f53654` |
| l2c_main.c | Removed the inactive compression-timeout placeholder. | Kept the target empty timeout function. | 5/5 to 5/5 | `71d6dcc88f745f4586201a2a0c1c91f368961125` |
| l2c_utils.c | Removed an inactive compression placeholder, two default-only switches, two unused feature-type locals and an abandoned reconstruction comment. Preserved byte advancement and C89 declaration order. | Kept the target compression stubs and the inherited raw-pool surplus described below. | 33/33 to 33/33 | `1858763764a726620598fcabe8f86d1fef2722a7` |
| sdp_api.c | Separated twelve assignments from conditions across protocol-list lookup, DI record creation and local DI record/attribute lookup. | Kept upstream local names, attribute order and the existing record-size erratum. | 9/9 to 9/9 | `ef081a29ae97e427ba534a6016360e9767255bb6` |
| uusb_ppc.c | Removed eight unused scalar locals, fifteen discarded pointer stores, two overwritten length initializations and an inert error condition. Named the HCI trace argument. | Kept sp14 in uusb_ReadIntrDataCB because removing it changed allocated bytes; a one-line MWCC note records the requirement. Kept the common end paths and definition-level volatile wait4hci. | 13/13 to 13/13 | `410ea6f94a0287d3e9dbde2fd865a5063b38e4f2` |

## Rejected trials

Each failed trial was restored and its object rebuilt before continuing. Allocated section bytes and relocations were compared against the initial full-build objects. Compiler-generated `@` symbol names were normalized to their section and offset, since deleting dead declarations can renumber those names without changing a relocation target.

| File | Trial | Evidence |
| --- | --- | --- |
| btm_sco.c | BTM_CreateSco: preserve short-circuit address check and separate ACL handle lookup | Allocated section bytes changed; restored the trial. |
| uusb_ppc.c | uusb_ReadIntrDataCB: remove unused stack/register locals | Allocated section bytes changed; restored the trial. |
| uusb_ppc.c | uusb_ReadBulkDataCB: remove unused stack/register locals | Initial strict symbol comparison rejected compiler-generated label renumbering. Retried with relocation targets resolved to section/offset; allocated bytes and targets were identical. |
| uusb_ppc.c | uusb_issue_bulk_read: remove unused stack/register locals | Initial strict symbol comparison rejected compiler-generated label renumbering. Retried with relocation targets resolved to section/offset; allocated bytes and targets were identical. |
| uusb_ppc.c | uusb_issue_intr_read: remove unused stack/register locals | Initial strict symbol comparison rejected compiler-generated label renumbering. Retried with relocation targets resolved to section/offset; allocated bytes and targets were identical. |
| uusb_ppc.c | UUSB_Write: remove unused stack/register locals | Initial strict symbol comparison rejected compiler-generated label renumbering. Retried with relocation targets resolved to section/offset; allocated bytes and targets were identical. |
| uusb_ppc.c | uusb_ReadIntrDataCB: remove unused stack/register locals with anonymous-symbol normalization | Allocated section bytes changed; restored the trial. |
| uusb_ppc.c | uusb_ReadIntrDataCB: remove unused sp14 individually | Allocated section bytes changed; restored the trial. |
| btm_sco.c | btm_sco_chk_pend_unpark: separate guarded ACL handle lookup | Allocated section bytes changed; restored the trial. |
| btm_sco.c | BTM_CreateSco: use nested address and handle checks | Allocated section bytes changed; restored the trial. |
| btm_sco.c | btm_sco_removed: remove duplicate SCO database pointer assignment | Allocated section bytes changed; restored the trial. |
| btu_task1.c | Remove repeated event callback null check after its guard | Allocated section bytes changed; restored the trial. |
| l2c_api.c | L2CA_SetCompression: remove empty branch and unused link local | Allocated section bytes changed; restored the trial. |
| l2c_utils.c | l2cu_check_feature_rsp: skip ignored feature type without a dead local | C89 rejects the declaration after p_data++; restored it, then used declaration-first form, which passed. |

The first inactive-block scanner stalled in its regex before writing the next file. Stopped only that Python process and replaced the scan with balanced preprocessor handling.

## String-pool evidence

All twelve final objects have the same allocated section bytes, named symbol positions and resolved relocation targets as the initial full-build objects. Their pools are identical to that source baseline.

Eleven raw pools also match the retail extracted objects. `l2c_utils.c` has eight raw source strings versus six retail strings both before and after cleanup. The inherited trailing strings are `L2CAP - badly formatted feature req` and `L2CAP - badly formatted feature rsp`. The retail-pool tool output is unchanged. Objdiff reports the owned data at 248/248 bytes and every reported section at 100%; the full linked DOL remains exact. These strings were retained to preserve the baseline object bytes.

## Final verification

- Ran the acceptance gate once at the end over all twelve touched units with `--quick`.
- Full 43U build passed. All 127/127 target functions in touched units are instruction-exact, with code/data/linking and every reported section at 100%.
- Gate reports zero regressions, zero net forbidden patterns and zero readability warnings.
- Explicit ctxdiff checks for fourteen changed target functions report equal instruction counts and `diffs 0`. Six other changed helpers are not separate functions in the extracted target report; their complete allocated objects remain identical to the baseline.
- Regenerated `build/43U/report.json`; `build/43U/ok` passed. Generated decomp_status output in a task-specific temporary file.
- `python3 tools/check_decomp_complete.py build/43U/report.json --dol build/43U/main.dol` returned `DECOMPLETE_OK`.

```text
GATE PASS
DECOMPLETE_OK
DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d
Global code exact 100.00%, fuzzy 100.00%, linked 100.00%
Global data matched 100.00%, linked 100.00%
```

Committed each source file separately. No push, PR, merge, rebase, subagent or other-worktree edit was performed.
