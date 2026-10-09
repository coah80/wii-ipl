# cleanup-c6 attempts

Worktree `/mnt/drive2/projects/wii-ipl-workers/data-d7`, branch `agent/w1009/cleanup-c6`, baseline `f1db6b65`.

Initial full 43U build passed. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`; completion checker `DECOMPLETE_OK`. Every owned unit is Matching and every code/data/function measure is 100%.

Compare each compiled trial with the baseline object, including every loadable section and normalized relocation. Restore every trial that changes bytes. Prior o2-bs2mach, o3-small, o4-aosslink and sol-audit logs explain the existing compiler constraints.

## Compiled trials

- dvd-state-declaration: Declare DVDCommandBlock.state volatile and remove every owned per-use cast. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2Tick: 4 diffs, 1940/1940 instructions"]}, {"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [], "functions": []}].

- dvd-qualified-local-pointers: Use const volatile local block views for asynchronous state reads, keeping ordinary state writes. Build 2; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2Tick: 4 diffs, 1940/1940 instructions"]}, {"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [], "functions": []}].

- dvd-qualified-local-scopes: Declare asynchronous read views at the start of C scopes. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["BS2StartGCGame: 5 diffs, 228/228 instructions", "BS2StartGame: 5 diffs, 393/393 instructions", "BS2Tick: 417 diffs, 1941/1940 instructions"]}, {"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [], "functions": []}].

- bs2-cover-late-view: Assign the asynchronous read view after StartingGame, limiting its lifetime to polling. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2StartGCGame: 5 diffs, 228/228 instructions", "BS2StartGame: 5 diffs, 393/393 instructions"]}].

- bs2-flag-DvdReadPending: Remove only DvdReadPending declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2DVDCallback: 5 diffs, 81/81 instructions", "BS2Tick: 2 diffs, 1940/1940 instructions"]}].

- bs2-flag-StartingGame: Remove only StartingGame declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2StartGCGame: 5 diffs, 228/228 instructions", "BS2StartGame: 5 diffs, 393/393 instructions"]}].

- bs2-flag-RestartRequested: Remove only RestartRequested declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2Tick: 5 diffs, 1940/1940 instructions"]}].

- bs2-flag-PartitionOpen: Remove only PartitionOpen declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2Tick: 3 diffs, 1940/1940 instructions"]}].

- bs2-flag-LoadingTitle: Remove only LoadingTitle declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2Tick: 2 diffs, 1940/1940 instructions"]}].

- bs2-flag-FatalErrorFlag: Remove only FatalErrorFlag declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2Tick: 2 diffs, 1940/1940 instructions"]}].

- bs2-flag-AbortFlag: Remove only AbortFlag declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2Tick: 3 diffs, 1940/1940 instructions"]}].

- bs2-flag-CacheFailed: Remove only CacheFailed declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2NANDCallback: 3 diffs, 25/25 instructions"]}].

- bs2-flag-RegionValid: Remove only RegionValid declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2Tick: 3 diffs, 1940/1940 instructions"]}].

- bs2-flag-NandPending: Remove only NandPending declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2StartGCGame: 1 diffs, 228/228 instructions", "BS2StartGame: 1 diffs, 393/393 instructions", "CheckBS2CommandStatus: 69 diffs, 406/406 instructions"]}].

- bs2-flag-CancelNand: Remove only CancelNand declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2NANDDivideCallback: 3 diffs, 128/128 instructions"]}].

- bs2-flag-LowReadResult: Remove only LowReadResult declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["BS2StartGame: 165 diffs, 389/393 instructions"]}].

- bs2-flag-DvdTransferred: Remove only DvdTransferred declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2DVDCallback: 2 diffs, 81/81 instructions", "BS2Tick: 4 diffs, 1940/1940 instructions"]}].

- bs2-flag-DvdTransferLength: Remove only DvdTransferLength declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2DVDCallback: 3 diffs, 81/81 instructions", "BS2Tick: 6 diffs, 1940/1940 instructions"]}].

- bs2-flag-BannerLength: Remove only BannerLength declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["BS2Tick: 611 diffs, 1939/1940 instructions", "CheckBS2CommandStatus: 64 diffs, 403/406 instructions"]}].

- bs2-flag-CacheLength: Remove only CacheLength declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["CheckBS2CommandStatus: 321 diffs, 396/406 instructions"]}].

- bs2-flag-LoaderLength: Remove only LoaderLength declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["CheckBS2CommandStatus: 88 diffs, 405/406 instructions"]}].

- bs2-flag-NandCompletion: Remove only NandCompletion declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2NANDDivideCallback: 5 diffs, 128/128 instructions", "BS2NANDDivideReadAsync: 10 diffs, 47/47 instructions", "BS2NANDDivideWriteAsync: 10 diffs, 47/47 instructions"]}].

- bs2-flag-NandOperation: Remove only NandOperation declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.text", ".text"], "functions": ["BS2NANDDivideReadAsync: 6 diffs, 47/47 instructions", "BS2NANDDivideWriteAsync: 6 diffs, 47/47 instructions"]}].

- bs2-flag-NandLength: Remove only NandLength declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["BS2NANDDivideCallback: 69 diffs, 125/128 instructions", "BS2NANDDivideReadAsync: 41 diffs, 45/47 instructions", "BS2NANDDivideWriteAsync: 41 diffs, 45/47 instructions"]}].

- bs2-flag-NandTransferred: Remove only NandTransferred declaration volatility. Build 0; [{"unit": "src/BS2/BS2Mach", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["BS2NANDDivideCallback: 108 diffs, 124/128 instructions", "BS2NANDDivideReadAsync: 4 diffs, 47/47 instructions", "BS2NANDDivideWriteAsync: 4 diffs, 47/47 instructions"]}].

- bs2-state-inline-helper: Read asynchronous state through an inline function with a qualified parameter. Build 0; all loadable sections and relocations identical.

- dvd-all-state-reads-qualified: Use the same const volatile local view for every status read in DVDGetCommandBlockStatus. Build 0; all loadable sections and relocations identical.

- dvd-flag-CommandInfoCounter: Remove only CommandInfoCounter declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.data", ".rela.sdata", ".rela.text", ".text"], "functions": ["ResetAlarmHandler: 128 diffs, 132/148 instructions", "StampCommand: 31 diffs, 37/45 instructions", "StampIntType: 11 diffs, 24/25 instructions", "cbForStateBusy: 611 diffs, 623/632 instructions", "cbForStateCheckID1: 99 diffs, 113/114 instructions", "cbForStateCheckID2: 91 diffs, 100/101 instructions", "cbForStateCoverClosed: 40 diffs, 53/54 instructions", "cbForStateDownRotation: 130 diffs, 135/144 instructions", "cbForStateGettingError: 302 diffs, 304/321 instructions", "cbForStateGoToRetry: 129 diffs, 143/144 instructions", "cbForStateOpenPartition: 85 diffs, 90/98 instructions", "cbForStateOpenPartition2: 75 diffs, 88/89 instructions", "cbForStateReadingFST: 81 diffs, 88/97 instructions", "cbForStateReadingPartitionInfo: 269 diffs, 271/286 instructions", "cbForStateReadingTOC: 90 diffs, 96/104 instructions", "cbForStoreErrorCode3: 38 diffs, 41/49 instructions", "cbForUnrecoveredError: 104 diffs, 103/120 instructions", "cbForUnrecoveredErrorRetry: 39 diffs, 52/53 instructions", "stateBusy: 340 diffs, 340/364 instructions", "stateCheckID: 176 diffs, 177/206 instructions", "stateCoverClosed_CMD: 46 diffs, 86/94 instructions", "stateDownRotation: 37 diffs, 42/50 instructions", "stateReadingFST: 53 diffs, 86/94 instructions"]}].

- dvd-flag-ResumeFromHere: Remove only ResumeFromHere declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["cbForStateGoToRetry: 2 diffs, 144/144 instructions", "stateReady: 150 diffs, 201/202 instructions"]}].

- dvd-flag-NumInternalRetry: Remove only NumInternalRetry declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["CategorizeError: 25 diffs, 60/61 instructions", "ResetAlarmHandler: 3 diffs, 148/148 instructions", "cbForStateBusy: 6 diffs, 632/632 instructions", "cbForStateCheckID1: 3 diffs, 114/114 instructions", "cbForStateDownRotation: 3 diffs, 144/144 instructions", "cbForStateGoToRetry: 3 diffs, 144/144 instructions", "cbForStateOpenPartition2: 3 diffs, 89/89 instructions", "stateCoverClosed_CMD: 3 diffs, 94/94 instructions"]}].

- dvd-flag-__DVDLayoutFormat: Remove only __DVDLayoutFormat declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["cbForStateCheckID2: 43 diffs, 99/101 instructions", "stateReadingFST: 67 diffs, 92/94 instructions"]}].

- dvd-flag-__BS2DVDLowIntType: Remove only __BS2DVDLowIntType declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.text", ".text"], "functions": ["__DVDGetCoverStatus: 42 diffs, 51/50 instructions", "__DVDResetWithNoSpinup: 8 diffs, 19/17 instructions"]}].

- dvd-flag-CurrCommand: Remove only CurrCommand declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["cbForPrepareCoverRegister: 5 diffs, 98/98 instructions", "cbForStateBusy: 588 diffs, 618/632 instructions", "cbForStateGoToRetry: 100 diffs, 136/144 instructions", "stateReady: 162 diffs, 199/202 instructions"]}].

- aoss-remove-first-guard: Remove the first constant guard with no other logic change. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".text"], "functions": ["AOSSi_WLANConnect: 2 diffs, 155/155 instructions"]}].

- aoss-result-before-ssid: Initialize result before-ssid without a constant guard. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 2 diffs, 155/155 instructions", "AOSSi_WLANGetBSSList: 87 diffs, 226/227 instructions"]}].

- aoss-result-before-first-memset: Initialize result before-first-memset without a constant guard. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 2 diffs, 155/155 instructions", "AOSSi_WLANGetBSSList: 87 diffs, 226/227 instructions"]}].

- aoss-result-after-ip-memset: Initialize result after-ip-memset without a constant guard. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 109 diffs, 154/155 instructions", "AOSSi_WLANGetBSSList: 87 diffs, 226/227 instructions"]}].

- aoss-result-before-ip-submit: Initialize result before-ip-submit without a constant guard. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 47 diffs, 155/155 instructions", "AOSSi_WLANGetBSSList: 87 diffs, 226/227 instructions"]}].

- aoss-result-at-declaration: Initialize result at declaration and remove the first guard. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 2 diffs, 155/155 instructions", "AOSSi_WLANGetBSSList: 87 diffs, 226/227 instructions"]}].

- mbr-const-input: Use an ordinary const input buffer. Build 0; [{"unit": "libs/RVL_SDK/src/fa/pdm_partition", "sections": [".text"], "functions": ["pdm_part_is_master_boot_sector: 26 diffs, 84/84 instructions"]}].

- mbr-byte-locals: Name all four ordinary byte reads before assembling each sector value. Build 0; [{"unit": "libs/RVL_SDK/src/fa/pdm_partition", "sections": [".text"], "functions": ["pdm_part_is_master_boot_sector: 26 diffs, 84/84 instructions"]}].

- mbr-sequential-accumulation: Decode each little-endian word through a plain inline accumulator. Build 0; [{"unit": "libs/RVL_SDK/src/fa/pdm_partition", "sections": [".text"], "functions": ["pdm_part_is_master_boot_sector: 45 diffs, 84/84 instructions"]}].

The first five result-placement trials also removed an earlier BSS-list assignment because their text replacement was not scoped to WLANConnect. Those trials were discarded; the following trials restrict every edit to WLANConnect.

- aoss-scoped-before-ssid: Move result initialization before-ssid within WLANConnect only. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 8 diffs, 155/155 instructions"]}].

- aoss-scoped-before-first-memset: Move result initialization before-first-memset within WLANConnect only. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 71 diffs, 155/155 instructions"]}].

- aoss-scoped-after-ip-memset: Move result initialization after-ip-memset within WLANConnect only. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 109 diffs, 154/155 instructions"]}].

- aoss-scoped-before-ip-submit: Move result initialization before-ip-submit within WLANConnect only. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 47 diffs, 155/155 instructions"]}].

- aoss-scoped-declaration: Initialize WLANConnect result at declaration. Build 0; [{"unit": "src/scene/setting/AOSSLink", "sections": [".rela.text", ".text"], "functions": ["AOSSi_WLANConnect: 71 diffs, 155/155 instructions"]}].

- pud-flat-fallback-at-declaration: Remove the carrier and unread pointer, initializing the scalar fallback at declaration. Build 0; [{"unit": "libs/RVLMiddleware/eZiText/src/clib/zi8pud2", "sections": [".rela.text", ".relaextabindex", ".text", "extabindex"], "functions": ["Zi8MatchPUDdata_ZHS: 339 diffs, 353/354 instructions"]}].

- pud-live-error-workspace: Replace the carrier with scalar locals and use the saved workspace in every error-report call. Build 0; [{"unit": "libs/RVLMiddleware/eZiText/src/clib/zi8pud2", "sections": [".rela.text", ".relaextabindex", ".text", "extab", "extabindex"], "functions": ["Zi8MatchPUDdata_ZHS: 293 diffs, 364/354 instructions"]}].

- pud-small-fallback: Remove the unread pointer and represent the fallback as a byte flag. Build 0; [{"unit": "libs/RVLMiddleware/eZiText/src/clib/zi8pud2", "sections": [".rela.text", ".relaextabindex", ".text", "extabindex"], "functions": ["Zi8MatchPUDdata_ZHS: 339 diffs, 353/354 instructions"]}].

- dvd-flag-PauseFlag: Remove only PauseFlag declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.text", ".text"], "functions": ["DVDCancelAllAsync: 3 diffs, 59/59 instructions", "DVDResume: 3 diffs, 20/20 instructions", "__DVDPrepareReset: 3 diffs, 77/77 instructions", "__DVDPrepareResetAsync: 3 diffs, 71/71 instructions"]}].

- dvd-flag-PausingFlag: Remove only PausingFlag declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.text", ".text"], "functions": ["DVDCancelAllAsync: 3 diffs, 59/59 instructions", "DVDResume: 3 diffs, 20/20 instructions", "__DVDPrepareReset: 3 diffs, 77/77 instructions", "__DVDPrepareResetAsync: 3 diffs, 71/71 instructions"]}].

- dvd-flag-Canceling: Remove only Canceling declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.text", ".text"], "functions": ["ResetAlarmHandler: 3 diffs, 148/148 instructions", "cbForStateCheckID1: 3 diffs, 114/114 instructions", "cbForStateDownRotation: 3 diffs, 144/144 instructions", "cbForStateGoToRetry: 2 diffs, 144/144 instructions", "cbForStateOpenPartition2: 3 diffs, 89/89 instructions", "stateCoverClosed_CMD: 3 diffs, 94/94 instructions"]}].

- dvd-flag-WaitingForCoverOpen: Remove only WaitingForCoverOpen declaration volatility. Build 0; all loadable sections and relocations identical.

- dvd-flag-WaitingForCoverClose: Remove only WaitingForCoverClose declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.data", ".rela.text", ".text"], "functions": ["cbForPrepareCoverRegister: 85 diffs, 97/98 instructions"]}].

- dvd-flag-PreparingCover: Remove only PreparingCover declaration volatility. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.text", ".text"], "functions": ["cbForPrepareCoverRegister: 2 diffs, 98/98 instructions"]}].

- dvd-flag-Prepared: Remove only Prepared declaration volatility. Build 2; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.text", ".text"], "functions": ["cbForPrepareCoverRegister: 2 diffs, 98/98 instructions"]}].

- dvd-flag-Prepared: Remove only Prepared declaration volatility. Build 2; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.text", ".text"], "functions": ["cbForPrepareCoverRegister: 2 diffs, 98/98 instructions"]}].

- dvd-flag-Prepared-declarations: Remove volatility from both declarations of Prepared. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".text"], "functions": ["__DVDPrepareReset: 1 diffs, 77/77 instructions"]}].

- dvd-LastResetEnd: Remove declaration volatility from the shared reset timestamp. Build 0; [{"unit": "libs/RVL_SDK/src/dvd/dvd", "sections": [".rela.text", ".text"], "functions": ["__DVDGetCoverStatus: 12 diffs, 50/50 instructions", "cbForStateBusy: 12 diffs, 632/632 instructions"]}].

## Retained changes

- BS2Mach: replace all three DVD state casts with BS2ReadDVDState, an inline reader taking a const volatile block. All sections and relocations stay identical. Keep all 21 flag qualifiers; removing any one changes code. Add one compiler-ordering comment for the flags.
- dvd.c: replace both per-use casts with a const volatile local block view and use it for all status reads. Keep interrupt-shared qualifiers. WaitingForCoverOpen alone is byte-identical without its qualifier, but asynchronous callbacks write it while cancellation/state routines read it; preserve that source contract. The initial Prepared trial removed only one of its two declarations and failed compilation; the corrected two-declaration trial changes one instruction.
- dvd.h: retain an ordinary state field and explain the read/store distinction in one line. Declaring the field volatile changes BS2Tick by four instructions.
- pdm_partition: retain the volatile input parameter with a one-line comment. The three plain-buffer alternatives change 26, 26 and 45 instructions.
- AOSSLink: retain the constant first-step guard with a one-line comment. Removing it changes two scheduled instructions; scoped result initialization alternatives also fail exactness.
- zi8pud2: retain the carrier and unread pointer store with one explanatory line. Honest removal loses the target store and gives 353/354 instructions. A real workspace use adds loads and gives 364/354.

No function-scoped optimization pragmas occur in the owned files. No trial change that alters code, data or relocations is retained.

- final-owned-objects: Rebuild all owned objects after the accepted cleanup and explanatory comments. Build 0; all loadable sections and relocations identical.

## Final verification

`gate.py src/BS2/BS2Mach libs/RVL_SDK/src/dvd/dvd libs/RVL_SDK/src/fa/pdm_partition src/scene/setting/AOSSLink libs/RVLMiddleware/eZiText/src/clib/zi8pud2 --quick`: **GATE PASS**, 0 regressions, 0 added forbidden patterns, 0 readability warnings. Full build passed; every owned section is 100%.

The new DVD local view triggers one advisory volatile-declaration note. Its entire unit is byte-identical to baseline and DVDGetCommandBlockStatus is 50/50 instructions, diffs 0. It replaces casts with a qualified declaration and introduces no use-site cast.

| Unit | Exact functions before/after | Code/data and linked code/data | Pool |
| --- | --- | --- | --- |
| BS2Mach | 29/29 -> 29/29 | 100% | 91/91 identical |
| dvd | 65/65 -> 65/65 | 100% | 1/1 identical |
| pdm_partition | 20/20 -> 20/20 | 100% | empty, identical |
| AOSSLink | 14/14 -> 14/14 | 100% | empty, identical |
| zi8pud2 | 7/7 -> 7/7 | 100% | empty, identical |

Fresh ctxdiff checks: BS2StartGame 393/393, BS2StartGCGame 228/228, BS2Tick 1940/1940, DVDGetCommandBlockStatus 50/50, pdm_part_is_master_boot_sector 84/84, AOSSi_WLANConnect 155/155, Zi8MatchPUDdata_ZHS 354/354. All report diffs 0.

Fresh report generation completed; completion checker **DECOMPLETE_OK**. DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`. Git diff whitespace check passed. Gate log `/tmp/cleanup-c6-gate.log`; focused checks `/tmp/cleanup-c6-focused-validation.log`.

## Source commits

- `bf57e7f5` src/BS2/BS2Mach.c
- `5f4657c3` libs/RVL_SDK/src/dvd/dvd.c
- `1215b163` libs/RVL_SDK/include/revolution/dvd.h
- `bf52561d` libs/RVL_SDK/src/fa/pdm_partition.c
- `008d7688` src/scene/setting/AOSSLink.c
- `b3c7f9ba` libs/RVLMiddleware/eZiText/src/clib/zi8pud2.c
