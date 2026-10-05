# rx67b retention and placement follow-up

Baseline `9ca4385f` includes landed #1231. Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d1`, branch `agent/w1005/rx67b`, initially clean. Fresh report and object snapshots are in `build/rx67b/baseline*`; the starting DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`.

All 165 uses in 37 files are classified individually in `rx67b.classification.md`. Preserve legitimate runtime/boot/debugger entry placement and rx68 ownership. Earlier failed rx67 trials remain evidence; do not repeat them without a new source hypothesis. New candidates must leave all measures, functions and sections unchanged, plus the full DOL. Failed candidates are restored, including candidates with an exact DOL but lower data credit.

## Trials

### netversion-ordinary-emission

`libs/RevoEX/src/net/NETVersion.c`. Remove the force_active pragma around existing real code/data. Public definitions and actual references should provide ordinary emission; retain only if all measures and the DOL stay equal.

code 8 -> 8; data 64 -> 64; exact 1 -> 1. DOL `3800bbbe6b32558d7f729d1d6ddd9aea3f771b16`. Restored.

### arc-ordinary-emission

`libs/RVL_SDK/src/arc/arc.c`. Remove the force_active pragma around existing real code/data. Public definitions and actual references should provide ordinary emission; retain only if all measures and the DOL stay equal.

code 2464 -> 2464; data 120 -> 120; exact 14 -> 14. DOL `55dd7ac85f4663434260aa7c439d05b06848dc02`. Restored.

### nandopenclose-ordinary-emission

`libs/RVL_SDK/src/nand/NANDOpenClose.c`. Remove the force_active pragma around existing real code/data. Public definitions and actual references should provide ordinary emission; retain only if all measures and the DOL stay equal.

code 5056 -> 5056; data 88 -> 88; exact 22 -> 22. DOL `c6c9d2fad663a0d61abbbd17617b7185b8ed2e0a`. Restored.

### dvdfs-ordinary-emission

`libs/RVL_SDK/src/dvd/dvdfs.c`. Remove the force_active pragma around existing real code/data. Public definitions and actual references should provide ordinary emission; retain only if all measures and the DOL stay equal.

code 3488 -> 3488; data 472 -> 472; exact 15 -> 15. DOL `2c444308cd435ed423ad0a49185037785e706429`. Restored.

### cnt-ordinary-emission

`libs/RVL_SDK/src/cnt/cnt.c`. Remove the force_active pragma around existing real code/data. Public definitions and actual references should provide ordinary emission; retain only if all measures and the DOL stay equal.

code 2228 -> 2228; data 888 -> 888; exact 16 -> 16. DOL `c24ee2a5d455cb0456d1f21180b95b1126eec3cb`. Restored.

### iplchannelmanager-ordinary-emission

`src/system/iplChannelManager.cpp`. Remove the force_active pragma around existing real code/data. Public definitions and actual references should provide ordinary emission; retain only if all measures and the DOL stay equal.

code 12552 -> 8400; data 1080 -> 1080; exact 74 -> 59. Function changes: {"loadMetaHeaderAsync__Q33ipl7channel7ManagerFii": [100.0, 92.239586], "cbReadMetaHeader__Q33ipl7channel7ManagerFPv": [100.0, 98.584], "makeLoadOrderList__Q33ipl7channel7ManagerCFPi": [100.0, 45.51852], "updateInitState__Q33ipl7channel7ManagerFv": [100.0, 72.19231], "searchMetaHeader__Q33ipl7channel7ManagerFPCUc": [100.0, 60.714287], "checkHeaderMD5__Q33ipl7channel7ManagerFPUc": [100.0, 68.666664], "calcMD5__Q33ipl7channel7ManagerCFPCUcPCUcUl": [100.0, 72.583336], "setDiskBannerInfo__Q33ipl7channel7ManagerFb": [100.0, 82.97248], "getDiskBannerData__Q33ipl7channel7ManagerFib": [100.0, 99.74359], "titleIDtoPageIndex__Q33ipl7channel7ManagerCFUxPiPi": [100.0, 57.2], "getLockedMsgFromBuf__Q33ipl7channel7ManagerCFPCQ33ipl7channel22SChanMgrDiskInMessages": [100.0, 74.666664], "findEntryByTitleId__Q33ipl7channel7ManagerFUx": [100.0, 37.48718], "readBannerMetaAsync__Q33ipl7channel7ManagerFPQ23EGG4HeapUx": [100.0, 83.934784], "readSoundMetaAsync__Q33ipl7channel7ManagerFPQ23EGG4HeapUx": [100.0, 85.02], "readBannerCSAsync__Q33ipl7channel7ManagerFPQ23EGG4HeapUx": [100.0, 72.52941]}. Restored.

### rsosystem-ordinary-emission

`src/system/RsoSystem.cpp`. Remove the force_active pragma around existing real code/data. Public definitions and actual references should provide ordinary emission; retain only if all measures and the DOL stay equal.

code 2848 -> 2848; data 96 -> 96; exact 25 -> 25. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### iplsystem-ordinary-emission

`src/system/iplSystem.cpp`. Remove the force_active pragma around existing real code/data. Public definitions and actual references should provide ordinary emission; retain only if all measures and the DOL stay equal.

code 12456 -> 12456; data 2228 -> 2228; exact 63 -> 63. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### tvrc-natural-small-data

`src/system/TVRC.cpp`. The real five-byte writable TVR0 header belongs in .sdata under the normal small-data threshold. Remove its placement wrapper.

code 2312 -> 2312; data 280 -> 280; exact 9 -> 9. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### usb-duplicate-forced-encounters

`libs/RVL_SDK/src/usb/usb.c`. Remove three late duplicate force calls. The earlier occurrence already establishes these pool entries; recovery of those first uses remains open.

code 4396 -> 4396; data 1712 -> 1712; exact 13 -> 13. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

The first ChannelManager trial removed all pragma-pop lines by mistake, disrupting earlier compiler option scopes. Its register/code drops are invalid evidence for force_active removal. The retry edits only the nand_error_handling pragma scope.

### channelmanager-local-scope

`src/system/iplChannelManager.cpp`. Remove only the force_active wrapper around nand_error_handling. Preserve every earlier pragma scope.

code 12552 -> 12552; data 1080 -> 1080; exact 74 -> 74. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### esmisc-duplicate-title-list

`src/utility/iplESMisc.cpp`. Remove the second identical Title List allocation diagnostic retention call. Its preceding identical entry already determines pool order; recovering the first real use remains open.

code 9404 -> 9404; data 4416 -> 4416; exact 30 -> 30. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### predictlang-real-virtual-definition

`src/keyboard/tiPredictLang.cpp`. Move the actual empty virtual updateFromReceiver definition out of the class at the existing emission boundary. Its real CommandSender-derived vtables supply references; no synthetic call, object or new method is introduced.

code 5536 -> 5536; data 2300 -> 2300; exact 36 -> 36. DOL `8062a2e39778ca6355e6af9d7d25909529ae9c49`. Restored.

### predictlang-out-of-line-virtual-definition

`src/keyboard/tiPredictLang.cpp`. Define the actual empty virtual updateFromReceiver definition out of the class at the existing emission boundary. Its real CommandSender-derived vtables supply references; no synthetic call, object or new method is introduced.

code 5536 -> 5536; data 2300 -> 2300; exact 36 -> 36. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### usb-recover-open-device-async

`libs/RVL_SDK/src/usb/usb.c`. Recover the full IUSB_OpenDeviceIdsAsync API evidenced by Petari src/RVL_SDK/usb/usb.c. The request stores the real callback and path, submits IOS_OpenAsync and releases rejected requests; its two diagnostics replace their artificial encounters.

code 4396 -> 4396; data 1712 -> 1712; exact 13 -> 13. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### osreset-recover-obsolete-apis

`libs/RVL_SDK/src/os/OSReset.c`. Petari and ogws independently retain real obsolete OSResetSystem and OSSetBootDol API definitions, which always panic. Restore those APIs rather than a synthetic literal helper. Unknown removed-source line numbers use __LINE__; these functions are absent from the target DOL.

code 1308 -> 1308; data 672 -> 672; exact 8 -> 8. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### dvd-recover-cover-callback

`libs/RVL_SDK/src/dvd/dvd_broadway.c`. Restore the real cover-transaction callback and DVDLowWaitForCoverClose API from Petari. They own the two exact diagnostic strings and callback state handling. No volatile casts from the reference are carried over.

code 8900 -> 8900; data 4248 -> 4248; exact 30 -> 30. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### dvd-recover-notify-reset

`libs/RVL_SDK/src/dvd/dvd_broadway.c`. Restore the real synchronous IOS reset-notification API. Its callback rejection uses the historical SetSpinupFlag diagnostic; the second path reports the actual IOS return code.

code 8900 -> 8900; data 4248 -> 4248; exact 30 -> 30. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### dvd-recover-no-disc-open

`libs/RVL_SDK/src/dvd/dvd_broadway.c`. Restore the real six-vector no-disc partition-open API, including argument validation, request setup, and callback failure cleanup, from Petari. Existing shared format strings emit the function name through __FUNCTION__.

code 8900 -> 8900; data 4248 -> 4248; exact 30 -> 30. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### dvd-recover-cover-getters

`libs/RVL_SDK/src/dvd/dvd_broadway.c`. Restore the two synchronous cover-register queries with their real result buffers and callback guards. Their original SDK implementations explain both pairs of unused diagnostics; defer buffer-retention removal to the next trial.

code 8900 -> 8900; data 4248 -> 4248; exact 30 -> 30. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### dvd-recover-command-apis

`libs/RVL_SDK/src/dvd/dvd_broadway.c`. Restore complete known DVD video/drive command APIs from Petari at their string encounters. Each builds the actual IOS command, submits the transaction, and releases rejected callback contexts; existing types suffice.

code 8900 -> 8900; data 4248 -> 4248; exact 30 -> 30. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### dvd-real-cover-buffer-references

`libs/RVL_SDK/src/dvd/dvd_broadway.c`. The restored synchronous cover getters are genuine references to coverStatus and coverRegister. Test their natural BSS encounter order with both artificial retention calls removed.

code 8900 -> 8900; data 4248 -> 4248; exact 30 -> 30. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### dvd-recover-open-with-ticket

`libs/RVL_SDK/src/dvd/dvd_broadway.c`. Restore the complete original full-ticket API before its ticket-view sibling. Both now encounter ordinary shared TMD diagnostics through real validation branches, eliminating the retention calls and earlier named-message workaround.

code 8900 -> 8900; data 4248 -> 4248; exact 30 -> 30. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### dvd-recover-video-result-apis

`libs/RVL_SDK/src/dvd/dvd_broadway.c`. Restore the five original DVD result APIs and their documented wire records from Petari dvd.h. The 2048-byte physical/disc-key records, 64-byte BCA, and 32-byte report/servo records determine real IOS transfer lengths. No global padding object is added.

Compile failed; see build/rx67b/dvd-recover-video-result-apis/build.log. Restored.

### osreset-recover-menu-apis

`libs/RVL_SDK/src/os/OSReset.c`. Restore both real menu-launch APIs and their shared shutdown/state helper from Petari. Actual panic fallback paths now emit the two diagnostics; normal state fields and SDK enum names express the boot behavior.

code 1308 -> 1308; data 672 -> 672; exact 8 -> 8. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Restored.

### abort_exit_ppc_eabi-ordinary-runtime-references

`libs/MSL/src/PPC_EABI/abort_exit_ppc_eabi.c`. Reclassify ordinary MSL function retention as TRICK. Petari abort_exit implementations have no force_active pragma; public C functions need actual references, unlike section-registered startup/exception tables. Keep only if ordinary emission preserves the entire linked image.

code 52 -> 52; data 28 -> 28; exact 1 -> 1. DOL `92f066e781c404eca7f48569a8cb7a289d0c5b27`. Restored.

### sysenv.GCN-ordinary-runtime-references

`libs/MSL/src/PPC_EABI/sysenv.GCN.c`. Reclassify ordinary MSL function retention as TRICK. Petari abort_exit implementations have no force_active pragma; public C functions need actual references, unlike section-registered startup/exception tables. Keep only if ordinary emission preserves the entire linked image.

code 8 -> 8; data 0 -> 0; exact 1 -> 1. DOL `f28bfa9a4ec2112ba06ee98653c60fa7e2d849de`. Restored.

### dvd-recover-video-result-apis-types

`libs/RVL_SDK/src/dvd/dvd_broadway.c`. Reuse the existing private DVDVideoReportKey definition; the first candidate duplicated it. The other four wire records are new real protocol types, not placement objects.

code 8900 -> 8900; data 4248 -> 4248; exact 30 -> 30. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### osreset-recover-data-manager

`libs/RVL_SDK/src/os/OSReset.c`. The complete menu candidate conflicts with the real BS2Reset OSReturnToMenu definition. Restore that one retained diagnostic and recover only OSReturnToDataManager plus its real shared shutdown helper. Do not invent a weak attribute or rename the duplicate SDK API.

code 1308 -> 1308; data 672 -> 672; exact 8 -> 8. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### usb-recover-device-list

`libs/RVL_SDK/src/usb/usb.c`. Restore the real IOS-aligned path helper and USB device enumeration API with its four-vector protocol. The USB request descriptor/spare fields and wire types come from Petari, preserve the existing request layout, and serve real API data. Initialize cleanup pointers on the early error paths rather than introduce uninitialized reads.

code 4396 -> 4396; data 1712 -> 1712; exact 13 -> 13. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### usb-recover-descriptor-apis

`libs/RVL_SDK/src/usb/usb.c`. Restore complete string/device-descriptor queries, conversion, callbacks and asynchronous read wrapper from Petari. Test the reference diagnostics before adjusting for this SDK revision; every helper has an actual API caller.

code 4396 -> 4396; data 1712 -> 1712; exact 13 -> 13. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### usb-recover-removal-notify

`libs/RVL_SDK/src/usb/usb.c`. The real IUSB_DeviceRemovalNotifyAsync API submits IOS ioctl 26 with the supplied completion callback; its ordinary diagnostic replaces retention.

code 4396 -> 4396; data 1712 -> 1712; exact 13 -> 13. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### usb-recover-iso-transfer

`libs/RVL_SDK/src/usb/usb.c`. Restore the actual bounded isochronous packet validator and five-vector async transfer API. The real packet sizes, callback context and four cleanup objects explain the three diagnostics.

code 4396 -> 4396; data 1712 -> 1712; exact 13 -> 13. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### usb-recover-insertion-notify

`libs/RVL_SDK/src/usb/usb.c`. Restore real VID/PID and device-class insertion notification APIs from Petari, including aligned IOS vectors, context cleanup and completion callbacks. These consume the final two retained diagnostics.

code 4396 -> 4396; data 1712 -> 1712; exact 13 -> 13. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### wud-recover-wudstartsyncspdevice

`libs/RVL_SDK/src/wud/WUD.c`. Recover the complete WUDStartSyncSpDevice routine found in Petari, using existing WUD state and callbacks. Its ordinary debug/report or device-name use replaces the listed artificial pool encounters; existing live functions are left unchanged.

code 18852 -> 18852; data 12016 -> 12016; exact 66 -> 66. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### wud-recover-wudicancelsync

`libs/RVL_SDK/src/wud/WUD.c`. Recover the complete WUDiCancelSync routine found in Petari, using existing WUD state and callbacks. Its ordinary debug/report or device-name use replaces the listed artificial pool encounters; existing live functions are left unchanged.

code 18852 -> 18852; data 12016 -> 12016; exact 66 -> 66. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

## Primary source evidence and limits

Read-only source research recovered full SDK routines from [Petari](https://github.com/SMGCommunity/Petari/tree/2761ef9667e598cedfa48aec92b15e5b6bd5cf73/src/RVL_SDK), tree `2761ef9667e598cedfa48aec92b15e5b6bd5cf73`. USB, DVD, OSReset and WUD routines have the same API names, IOS commands, callback ownership and diagnostic strings as the retained pool. Full routines replace synthetic calls. Their code was removed by the retail linker, so a successful gate proves surviving code/data and the DOL, not instruction identity for those absent routines. Reference files and trees are saved under `build/rx67b/reference/`.

The ogws and wii-news-channel OSNet files repeat artificial retention. They are not evidence for a clean implementation. The news CNT DVD initializer only formats a path and always fails; that stub was rejected as a reconstruction reference. OSNet may contain superseded NWC24 fallback definitions, but no complete source or relocation proof establishes those definitions here. Keep that hypothesis separate from a recovered function.

The first OSReset menu reconstruction preserved object entries but failed to link because `OSReturnToMenu` is already defined by `src/BS2/BS2Reset.c`. Its printed DOL hash was the prior image, not a successful link. Restored that one macro; the separate data-manager and obsolete-API candidates pass their own full links. Do not introduce a weak attribute or rename a genuine public API merely to suppress the duplicate.

The two MSL force_active entries are reclassified TRICK. The primary abort/exit implementations have ordinary C definitions without the pragma. Runtime-library membership alone does not establish a required linker root. Removing those entries leaves object scores unchanged but changes the DOL, so they remain restored and unresolved.

Allocator assessment for accepted changes: no allocation divergence. All existing target functions retain their full objdiff entries; new source restores missing literal owners. tiPredictLang differs in emission/link ownership: inline out-of-class definition still loses the target order, whereas the ordinary out-of-line virtual definition emits at the correct position and keeps the DOL exact. The actual body remains empty and its vtable references remain real.

### wud-recover-wudenabletestmode

`libs/RVL_SDK/src/wud/WUD.c`. Recover the complete _WUDEnableTestMode routine found in Petari, using existing WUD state and callbacks. Its ordinary debug/report or device-name use replaces the listed artificial pool encounters; existing live functions are left unchanged.

code 18852 -> 18852; data 12016 -> 12016; exact 66 -> 66. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### wud-recover-wudstartsyncdevice

`libs/RVL_SDK/src/wud/WUD.c`. Recover the complete _WUDStartSyncDevice routine found in Petari, using existing WUD state and callbacks. Its ordinary debug/report or device-name use replaces the listed artificial pool encounters; existing live functions are left unchanged.

code 18852 -> 18852; data 12016 -> 12016; exact 66 -> 66. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### wud-recover-wuddeletestoreddevice

`libs/RVL_SDK/src/wud/WUD.c`. Recover the complete _WUDDeleteStoredDevice routine found in Petari, using existing WUD state and callbacks. Its ordinary debug/report or device-name use replaces the listed artificial pool encounters; existing live functions are left unchanged.

code 18852 -> 18852; data 12016 -> 12016; exact 66 -> 66. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### wud-recover-wudigetremovewbcdevice

`libs/RVL_SDK/src/wud/WUD.c`. Recover the complete WUDiGetRemoveWbcDevice routine found in Petari, using existing WUD state and callbacks. Its ordinary debug/report or device-name use replaces the listed artificial pool encounters; existing live functions are left unchanged.

code 18852 -> 18852; data 12016 -> 12016; exact 66 -> 66. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### cnt-recover-library-init

`libs/RVL_SDK/src/cnt/cnt.c`. Recover the real CNTInit/CNTShutdown library lifecycle and consumed version pointer, as implemented by the news-channel decomp. The initialization flag is real state guarded by the SDK interrupt lock. The unrelated stubbed DVD initializer from that project is not used.

code 2228 -> 2228; data 888 -> 888; exact 16 -> 16. DOL `7f4e6f8b3c37499ab09004285bb5e2fa59ecc16b`. Restored.

### wud-review-unused-state-reads

`libs/RVL_SDK/src/wud/WUD.c`. Remove the two unused nonvolatile state reads copied from the reference _WUDStartSyncDevice. They have no source purpose or target instruction evidence. Retain the real library status check and interrupt-protected transition.

code 18852 -> 18852; data 12016 -> 12016; exact 66 -> 66. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### usb-review-typed-descriptors

`libs/RVL_SDK/src/usb/usb.c`. Use the recovered descriptor union member directly for whole-descriptor copies, and remove one duplicated initialization in the newly restored insertion API. These are ordinary typed operations; existing live functions remain identical.

code 4396 -> 4396; data 1712 -> 1712; exact 13 -> 13. DOL `26116613f624061ba99c8d1a299aaa6efa85670d`. Retained for final full gate.

### wud-final-cancel-removal

`libs/RVL_SDK/src/wud/WUD.c`. The sole remaining WUD diagnostic belongs to WUDCancelSyncDevice. Petari adds _abortSync, read by a different sync handler; this checkout has no such state/read. Do not introduce a write-only compatibility flag. Measure clean removal after the seven proven recoveries.

code 18852 -> 14420; data 12016 -> 8152; exact 66 -> 59. Function changes: {"WUDiRegisterDevice": [100.0, 99.97369], "WUDiRemoveDevice": [100.0, 99.93104], "WUDSecurityCallback": [100.0, 99.935486], "WUDSearchCallback": [100.0, 99.9542], "WUDVendorSpecificCallback": [100.0, 99.96135], "WUDStoredLinkKeyCallback": [100.0, 99.93048], "WUDPowerManagerCallback": [100.0, 99.93671]}. Restored.

### osreset-final-menu-removal

`libs/RVL_SDK/src/os/OSReset.c`. Measure removal of the sole remaining menu diagnostic after recovering the other APIs. The real SDK API conflicts with BS2Reset; a clean body cannot be retained without independently proving archive/override ownership.

code 1308 -> 956; data 672 -> 24; exact 8 -> 6. Function changes: {"OSReturnToSetting": [100.0, 99.82979], "__OSReturnToMenuForError": [100.0, 99.97561]}. Restored.

## mwdbg baseline and final USB capture

`IUSB_OpenDeviceIds` remains 100.0%, 81/81 instructions. Target values: data base r31, result r30, allocation block r29, output pointer r28, vendor ID r27, interface r26; product ID shares r30 before the result exists. In both allocator captures these are virtual r40, r37, r36, r35, r33, r32 and r34. Simplify removes r32/r33/r34/r35/r36/r37/r40 at remaining degrees 17/16/15/15/14/13/12. Reverse coloring gives the data base first saved register r31, then result r30, block r29 and output r28. Product ID has no edge to the later result and reuses r30; vendor ID and interface require r27/r26. The allocation-return temporary r39 coalesces into block r36, and the free-result temporary r38 coalesces into physical r3. All other attempted call-register merges interfere. No spills occur.

Baseline and final assigned, simplify and coalescing dumps are identical. Both captures independently match wibo; each validates 68 CR plus 188 GPR operand rewrites, with zero mismatches, and 92 emitted machine register operands across 55 instructions. This confirms that restoring literal-owning APIs did not change the live allocator graph. Captures and validation are under `build/rx67b/mwdbg-usb-{baseline,final}`. The local transport and read-only shared tool use are described in the preceding rx67 log.

## Final verification

The non-quick clean gate in `rx67b.gate.txt` reports `GATE PASS`, full build OK, zero regressions, zero added forbidden patterns and zero readability warnings. DOL SHA1 is `26116613f624061ba99c8d1a299aaa6efa85670d`. A separate fresh full objdiff report compares all 1,027 units against `build/rx67b/baseline.json`: global measures and every unit measure, function entry and section entry are identical. The per-function before/after table and direct instruction comparisons are in [rx67b.functions.md](rx67b.functions.md).

| Unit | Objdiff and instruction-exact functions before -> after | Matched code before -> after | Matched data before -> after |
|---|---|---|---|
| `libs/RVL_SDK/src/dvd/dvd_broadway` | 30/30 -> 30/30 | 8900 -> 8900 | 4248 -> 4248 |
| `libs/RVL_SDK/src/os/OSReset` | 8/8 -> 8/8 | 1308 -> 1308 | 672 -> 672 |
| `libs/RVL_SDK/src/usb/usb` | 13/13 -> 13/13 | 4396 -> 4396 | 1712 -> 1712 |
| `libs/RVL_SDK/src/wud/WUD` | 66/66 -> 66/66 | 18852 -> 18852 | 12016 -> 12016 |
| `src/keyboard/tiPredictLang` | 36/36 -> 36/36 | 5536 -> 5536 | 2300 -> 2300 |
| `src/system/RsoSystem` | 25/25 -> 25/25 | 2848 -> 2848 | 96 -> 96 |
| `src/system/TVRC` | 9/9 -> 9/9 | 2312 -> 2312 | 280 -> 280 |
| `src/system/iplChannelManager` | 74/74 -> 74/74 | 12552 -> 12552 | 1080 -> 1080 |
| `src/system/iplSystem` | 63/63 -> 63/63 | 12456 -> 12456 | 2228 -> 2228 |
| `src/utility/iplESMisc` | 30/31 -> 30/31 | 9404 -> 9404 | 4416 -> 4416 |

All ten pools compare identically. Raw symorder reports include anonymous label renumbering and genuine restored functions absent from extracted retail objects; they are not reported as ORDER OK. The target-visible report entries and final linked addresses remain exact. Each final pool/symorder output is under `build/rx67b/final-evidence/<unit>/`. Raw data-section comparisons are in `build/rx67b/data-sections.json`.

The existing `DeleteUnauthorizedData` remains 99.14254%; no new function-match gain is claimed. The task removes 73 baseline retention/placement uses, keeps 15 legitimate runtime uses, restores 72 failed/unproven tricks, and defers five rx68-owned placements. Every baseline use has a final disposition in [rx67b.classification.md](rx67b.classification.md). Other explicit padding declarations outside this audit expression, including tiPredictLang_rodata_pad, remain separate findings.

Eight modified units retain byte-identical raw non-code sections. USB .sdata grows from 14 to 24 bytes and WUD .sdata from 6 to 15 because the recovered APIs also contain short diagnostic strings, including GetStr and start. Those genuine short literals are individually stripped by the linker; every target section report entry and the DOL remain unchanged. No padding object or forced-placement declaration was introduced.
