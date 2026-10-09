# cleanup2-x11 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d12`, branch `agent/w1009/cleanup2-x11`, baseline `f2006bdd`.
Scope: meaningful names for placeholder data members declared under `include/`, with every compiled use updated in the same focused commit.
Read cleanup-common.md fully, including wave-2 guidance, repository AGENTS.md, unslop, and writing-for-agents.

## Baseline

Initial full 43U build passed. All 1028 units and 12563 functions are exact and fully linked; data is 100% matched and linked.
Completion checker returned `DECOMPLETE_OK`. DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`.
Saved the report and SHA256 hashes of all 1028 source objects under `/tmp/cleanup2-x11-baseline-*`.

## Inspection

Headers ranked by placeholder declarations: iplMemoryCardLib.h has eight, vmPrivate.h has seven, VmTypes.h has three, then Scroller and Exception.
Memory-card capacity fields are assigned from CARDGetMemSize, CARDFreeBlocks, and countCardTitleBlocks. Icon fields are set by loadCardFileIcons and consumed by update_icon_anm.
Scroller's remaining unknown float is accelerated, decayed, and added to its scroll position in calc; it is scroll velocity. Earlier cleanup2-x3 preserved it because that worker only examined the SDMemory initialization use.
Acceptance for each commit: full build, DOL hash, freshly regenerated report, DECOMPLETE_OK, and no changed source-object bytes against the baseline. The final gate covers every object rebuilt because of the changed headers.

## Renames

- KEEP CardState `unk_0x0C` -> `totalBlocks`, the usable card capacity after system blocks; `unk_0x0E` -> `freeFiles`, assigned directly from CARDFreeBlocks and tested before copy/move; `unk_0x12` -> `titleBlocks`, assigned from countCardTitleBlocks. Updated the header and exact uses in CardSequence and MemoryCardManager. Full build and DECOMPLETE_OK passed; all 1028 source objects remained byte-identical. Commit `18c20470`.
- KEEP FileInfo `unk_0x06` -> `transferBlocked`. markAllCardFilesDirty sets it when checkCardFileDuplicate returns a negative result, covering duplicates and lookup failures; isCopyEnable and isMoveEnable reject transfers when it is set. The name does not assume every failure means a duplicate exists. Updated the header and exact uses in CardSequence and MemoryCardManager. Full build and DECOMPLETE_OK passed; all 1028 source objects remained byte-identical. Commit `d70e1631`.
- KEEP IconState `unk_0x01` -> `iconEnable`, `unk_0x02` -> `iconCount`, `unk_0x06` -> `anmFirstFrameDuration`, and `unk_0x07` -> `anmLastFrameDuration`. loadCardIconImages disables absent or invalid images, enables a loaded icon sequence, counts populated animation entries, and derives both endpoint durations from CARDDir.iconSpeed. update_icon_anm skips those endpoint holds when reversing a ping-pong animation. Updated the header and exact uses in CardSequence and MemoryCardManager. Full build and DECOMPLETE_OK passed; all 1028 source objects remained byte-identical. Commit `f0a8a213`.
- KEEP Scroller `unk_0x3C` -> `mScrollVelocity`. calc multiplies it by mVelocityDecay, adds or subtracts mScrollAcceleration, and adds the result to mScroll. Updated the header, constructor and calc in iplUtility, and the out-of-line init in SDMemory. Full build and DECOMPLETE_OK passed; all 1028 source objects remained byte-identical. Commit `511384ac`.

## Kept names

- vmPrivate.h: all seven pad members have no named uses in the source tree. Their runtime meaning cannot be established from use; keep them.
- VmTypes.h: all three pad declarations have no named uses. Keep their layout names.
- Exception: unk_0x04 and unk_0x0C only appear in zero initialization. That does not establish a purpose.
- System::Arg: unk_0x1C is only assigned NULL. Keep it.
- SDChannelTitle: mUnknownTitleWork and the alternate opaque unk_0x58 storage have no member uses establishing a purpose. Keep both.
- APScanThread's unk_0x2C is a virtual function, and CHANSVm.h's unk0 names function parameters. They are outside this data-member scope.
- Checked pad, padding, unused, and reserved declarations across include. SaveDataManager.padding is zeroed reserved save-file storage; actual layout padding and zero-only unused fields retain their names. No additional used placeholder member has a clear role.

Nine data members renamed across two headers; all four source users updated. Each rename commit contains only its header and exact use sites. No types, offsets, comments, statement order, compiler workarounds, or configuration changed.

## Final verification

Gate ran once with `--quick`, as required by cleanup-common.md, over all 33 units rebuilt after the header edits. These include the four edited source units and 29 dependent units. Every pool is identical; every section is 100%; all 1337 functions are instruction-exact. Full build passed, with zero regressions, forbidden patterns, or readability warnings.

| Edited source unit | Exact functions before -> after | Code bytes | Data bytes |
| --- | --- | --- | --- |
| src/scene/cardSequence/iplCardSequence | 30/30 -> 30/30 | 9852/9852 | 1496/1496 |
| src/scene/memoryCard/iplMemoryCardManager | 26/26 -> 26/26 | 5396/5396 | 0/0 |
| src/utility/iplUtility | 45/45 -> 45/45 | 5932/5932 | 304/304 |
| src/scene/sdChannelMemory/iplSDMemory | 66/66 -> 66/66 | 20872/20872 | 3344/3344 |

Final regeneration of build/43U/report.json and the completion checker passed. Compared the regenerated report with the initial baseline: measures, exact-name function records, and section records are identical for all 1028 units. All 1028 source objects remain byte-identical. Normalizing the nine documented renames reproduces the original six files exactly, including whitespace and comments.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
DECOMPLETE_OK
```

Gate transcript: `/tmp/cleanup2-x11-final-gate.log`.
Affected-unit list: `/tmp/cleanup2-x11-affected-units.json`.
Per-commit full-build logs: `/tmp/cleanup2-x11-capacity-build.log`, `/tmp/cleanup2-x11-transfer-build.log`, `/tmp/cleanup2-x11-icons-build.log`, `/tmp/cleanup2-x11-scroller-build.log`.
Baseline report and object hashes: `/tmp/cleanup2-x11-baseline-report.json`, `/tmp/cleanup2-x11-baseline-objects.json`.

origin/main advanced during the run; the leaf keeps its assigned baseline. No push, PR, merge, rebase, subagents, or edits to other worktrees. All attempted renames were retained; none changed object bytes.
