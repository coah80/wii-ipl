# Aggregate boundary sweep

Worktree sol-high, branch agent/w1003/agg-sweep. Baseline 38cb84c8. Fresh full 43U Ninja build and progress report pass. Origin fetched under /tmp/wii-git.lock. AOSS, ATERM, AOSSLink and eZiText excluded. Existing a6x, h6 and u7 untracked logs preserved.

Read AGENTS.md, common.md, levers.md and unslop. Only lever 13 candidates with target evidence can change object boundaries. Prior function-only helper/type trials are recorded in the existing attempts logs. Snapshot reference ELFs, section bytes and resolved relocations before any object correction. No configure/link changes.

## Live baseline and open-function audit

### src/system/iplKeyboard
{"fuzzy_match_percent": 98.73506, "matched_code": "4752", "matched_code_percent": 78.88447, "matched_data": "1184", "matched_data_percent": 100.0, "matched_functions": 31, "matched_functions_percent": 96.875, "total_code": "6024", "total_data": "1184", "total_functions": 32, "total_units": 1}
POOL IDENTICAL up to 28 (mine=28 base=28)
Instruction-exact 31/32.
- `create__Q33ipl8keyboard7ManagerFPQ33ipl4nand4FilePQ23EGG4Heap` 94.00944%; instructions 318/318, diffs 210, address-instruction diffs 61. Target objects: __vt__Q49textinput6extend4memo7Manager, jumptable_81638D20, lbl_816961F8, mspAllocator__Q34nw4r3lyt6Layout, sZiSysLangTable__Q23ipl8keyboard, smArg__Q23ipl6System. Large objects: sZiSysLangTable__Q23ipl8keyboard 0x58.

### src/system/odh
{"fuzzy_match_percent": 99.55462, "matched_code": "12876", "matched_code_percent": 87.68728, "matched_data": "6360", "matched_data_percent": 100.0, "matched_functions": 26, "matched_functions_percent": 92.85714, "total_code": "14684", "total_data": "6360", "total_functions": 28, "total_units": 1}
POOL IDENTICAL up to 10 (mine=10 base=10)
Instruction-exact 26/28.
- `LineConv11__9CArGBAOdhFPUcPUcPUcPUcUsUsPCli` 98.08219%; instructions 146/146, diffs 12, address-instruction diffs 2. Target objects: lbl_816945A0, lbl_816945A4, lbl_816945A8, lbl_816945AC, lbl_816945B0, lbl_816945B4, lbl_816945B8, lbl_816945C0. Large objects: none.
- `huffmanDecoder__9CArGBAOdhFPUlP21SArCDJ_HuffmanRequestPPUsiUl` 95.57189%; instructions 306/306, diffs 171, address-instruction diffs 21. Target objects: none. Large objects: none.

### src/utility/iplESMisc
{"fuzzy_match_percent": 99.8625, "matched_code": "9404", "matched_code_percent": 83.96429, "matched_data": "4416", "matched_data_percent": 100.0, "matched_functions": 30, "matched_functions_percent": 96.77419, "total_code": "11200", "total_data": "4416", "total_functions": 31, "total_units": 1}
POOL IDENTICAL up to 114 (mine=114 base=114)
Instruction-exact 30/31.
- `DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap` 99.14254%; instructions 449/449, diffs 74, address-instruction diffs 3. Target objects: @17577. Large objects: none.

### src/iplwww/www_wiisetting
{"fuzzy_match_percent": 99.94495, "matched_code": "3740", "matched_code_percent": 60.556995, "matched_data": "3856", "matched_data_percent": 100.0, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_code": "6176", "total_data": "3856", "total_functions": 21, "total_units": 1}
POOL IDENTICAL up to 72 (mine=72 base=72)
Instruction-exact 20/21.
- `Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue` 99.86043%; instructions 609/609, diffs 14, address-instruction diffs 4. Target objects: funcResult__Q23www10wiisetting, jumptable_816441AC, jumptable_816442CC, lbl_8160F0F0, lbl_816440A0, lbl_81644834, lbl_816946B8, lbl_816946C0, lbl_8169631C, lbl_8169631D, opera_callbacks__Q23www10wiisetting, pString__Q23www10wiisetting, sWiiData__Q23www10wiisetting, saveData__Q23www10wiisetting, setupFlag__Q23www10wiisetting, wiiFlag__Q23www10wiisetting, wiiOSReport__Q23www10wiisettingFP14WWWJSPluginObjP14WWWJSPluginObjiP16WWWJSPluginValueP16WWWJSPluginValue, wiiWriteBack__Q23www10wiisettingFP14WWWJSPluginObjP14WWWJSPluginObjiP16WWWJSPluginValueP16WWWJSPluginValue, writeBackID__Q23www10wiisetting. Large objects: jumptable_816441AC 0x120, jumptable_816442CC 0x64, lbl_8160F0F0 0x164, lbl_81644834 0x64, sWiiData__Q23www10wiisetting 0x48, wiiOSReport__Q23www10wiisettingFP14WWWJSPluginObjP14WWWJSPluginObjiP16WWWJSPluginValueP16WWWJSPluginValue 0x5c, wiiWriteBack__Q23www10wiisettingFP14WWWJSPluginObjP14WWWJSPluginObjiP16WWWJSPluginValueP16WWWJSPluginValue 0x344.

### src/BS2/BS2Mach
{"fuzzy_match_percent": 99.169846, "matched_code": "5112", "matched_code_percent": 30.106009, "matched_data": "158528", "matched_data_percent": 100.0, "matched_functions": 25, "matched_functions_percent": 86.206894, "total_code": "16980", "total_data": "158528", "total_functions": 29, "total_units": 1}
POOL IDENTICAL up to 91 (mine=91 base=91)
Instruction-exact 25/29.
- `BS2StartGame` 98.72774%; instructions 393/393, diffs 10, address-instruction diffs 6. Target objects: BS2NANDCallback, Block, CacheFailed, DiskID, DvdTransferred, GamePartition, LoaderClose, LowReadResult, NandPending, RequiredIosHigh, RequiredIosLow, StartingGame, TicketViews, callback, lbl_81645DA8. Large objects: BS2NANDCallback 0x64.
- `BS2StartGCGame` 97.82895%; instructions 228/228, diffs 9, address-instruction diffs 5. Target objects: BS2NANDCallback, BS2VideoMode, Block, CacheFailed, NandPending, StartingGame, TicketViews, lbl_81645DA8, lbl_81696584. Large objects: BS2NANDCallback 0x64.
- `CheckBS2CommandStatus` 99.50739%; instructions 406/406, diffs 2, address-instruction diffs 0. Target objects: BS2BootCaching, BS2BootFromCache, BS2NANDCallback, BannerBuffer, BannerLength, Block, CacheCommandComplete, CacheLength, CacheSeekComplete, DataToc, LoaderAddress, LoaderLength, NandPending, State, jumptable_81646338, lbl_81645DA8. Large objects: BS2NANDCallback 0x64, jumptable_81646338 0xb8.
- `BS2Tick` 98.799484%; instructions 1940/1940, diffs 71, address-instruction diffs 15. Target objects: AbortFlag, Allocator, AudioBufferUnconfigured, BS2BootCaching, BS2BootFromCache, BS2DVDCallback, BS2DriveReset, BS2NANDCallback, BS2NoDisk, BS2Report, BS2WaitSpinup, BannerAllocation, BannerAvailable, BannerBuffer, BannerLength, Block, CoverOpenTimeHigh, CoverOpenTimeLow, CoverPollTime, CurrentTmd, DataToc, DriveWasReset, DvdProgress, DvdReadPending, DvdTransferLength, DvdTransferred, FatalErrorFlag, GamePartition, GameToc, LoaderAddress, LoaderClose, LoaderInit, LoaderLength, LoaderMain, LoaderOffset, LoadingTitle, NandPending, OSReport, PartitionCursor, PartitionOpen, RegionValid, RequiredIosHigh, RequiredIosLow, ResetTime, RestartRequested, RetryErrorFlag, SpinupDeadline, StartingGame, State, TitleCode, TitleTicketView, UpdateErrorFlag, UpdatePartition, __DVDLayoutFormat, jumptable_816467F4, jumptable_81646850, lbl_81645DA8, lbl_8169658B, lbl_81696590, lbl_81696594. Large objects: BS2DVDCallback 0x144, BS2NANDCallback 0x64, BS2Report 0x50, jumptable_816467F4 0x5c, jumptable_81646850 0x124.

### src/BS2/BS2Update
{"fuzzy_match_percent": 95.340576, "matched_code": "400", "matched_code_percent": 9.871669, "matched_data": "10488", "matched_data_percent": 100.0, "matched_functions": 9, "matched_functions_percent": 90.0, "total_code": "4052", "total_data": "10488", "total_functions": 10, "total_units": 1}
POOL IDENTICAL up to 55 (mine=55 base=55)
Instruction-exact 9/10.
- `UpdateThread` 94.83023%; instructions 911/913, diffs 337, address-instruction diffs 163. Target objects: CancelUpdate, ContainsSeatTitles, CurrentEntry, EntriesCount, Flags0, RebootRequired, StartUpdate, State, UpdateImportResult, UpdateImportState, UpdateProgress, jumptable_81646E78, lbl_81646978, lbl_81696598, lbl_8169659A, lbl_8169659E, lbl_816965A5, pEntries, pFlags, rc. Large objects: Flags0 0x800, lbl_81646978 0x500.

### src/scene/address/iplAddress
{"fuzzy_match_percent": 99.923294, "matched_code": "22016", "matched_code_percent": 91.77922, "matched_data": "1964", "matched_data_percent": 100.0, "matched_functions": 99, "matched_functions_percent": 98.019806, "total_code": "23988", "total_data": "1964", "total_functions": 101, "total_units": 1}
POOL IDENTICAL up to 81 (mine=81 base=81)
Instruction-exact 98/101.
- `start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface` 99.84305%; instructions 223/223, diffs 7, address-instruction diffs 1. Target objects: @17080, lbl_816947D8, sSystem__Q23ipl3snd, smArg__Q23ipl6System. Large objects: none.
- `onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface` 98.42593%; instructions 270/270, diffs 81, address-instruction diffs 12. Target objects: @17080, sSystem__Q23ipl3snd, smArg__Q23ipl6System, smButtonName__Q33ipl5scene6Button. Large objects: none.

### src/scene/address/iplAddressEdit
{"fuzzy_match_percent": 99.55282, "matched_code": "23344", "matched_code_percent": 86.10209, "matched_data": "2560", "matched_data_percent": 100.0, "matched_functions": 91, "matched_functions_percent": 96.80851, "total_code": "27112", "total_data": "2560", "total_functions": 94, "total_units": 1}
POOL IDENTICAL up to 57 (mine=57 base=57)
Instruction-exact 91/94.
- `create__Q33ipl5scene11AddressEditFv` 97.5561%; instructions 818/820, diffs 331, address-instruction diffs 155. Target objects: @16959, __vt__Q33ipl5scene16AddressEditEvent, __vt__Q33ipl5scene17AddressInputEvent, lbl_816947F0, lbl_816947F4, lbl_816947F8, lbl_816965E4, lbl_816965E8, lbl_816965EA, nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv, sFriendInfo__Q23ipl5scene, sInputPaneName, smArg__Q23ipl6System. Large objects: nigaoe_create_callback_edit__Q33ipl5scene11AddressEditFPQ33ipl6nigaoe6ObjectPv 0xb0, sFriendInfo__Q23ipl5scene 0x140.
- `get_friendinfo__Q33ipl5scene11AddressEditFv` 88.03571%; instructions 82/84, diffs 68, address-instruction diffs 37. Target objects: @24215, @24231, sFriendInfo__Q23ipl5scene. Large objects: sFriendInfo__Q23ipl5scene 0x140.
- `update_friendinfo__Q33ipl5scene11AddressEditFv` 99.42105%; instructions 38/38, diffs 2, address-instruction diffs 2. Target objects: sFriendInfo__Q23ipl5scene, smArg__Q23ipl6System. Large objects: sFriendInfo__Q23ipl5scene 0x140.

### src/scene/memoryCard/iplMemoryCardManager
{"complete_data_percent": 100.0, "fuzzy_match_percent": 97.90215, "matched_code": "2932", "matched_code_percent": 54.336548, "matched_data_percent": 100.0, "matched_functions": 19, "matched_functions_percent": 73.07692, "total_code": "5396", "total_functions": 26, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 19/26.
- `isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl` 99.830505%; instructions 118/118, diffs 2, address-instruction diffs 0. Target objects: none. Large objects: none.
- `isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl` 99.830505%; instructions 118/118, diffs 2, address-instruction diffs 0. Target objects: none. Large objects: none.
- `isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs` 92.30769%; instructions 26/26, diffs 8, address-instruction diffs 2. Target objects: none. Large objects: none.
- `_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl` 87.55%; instructions 100/100, diffs 37, address-instruction diffs 5. Target objects: none. Large objects: none.
- `getComment__Q33ipl5scene17MemoryCardManagerFUcsi` 98.94309%; instructions 123/123, diffs 20, address-instruction diffs 1. Target objects: none. Large objects: none.
- `create_banner__Q33ipl5scene17MemoryCardManagerFUcs` 90.42453%; instructions 106/106, diffs 70, address-instruction diffs 11. Target objects: none. Large objects: none.
- `getBlocks__Q33ipl5scene17MemoryCardManagerFUcs` 92.0%; instructions 25/25, diffs 9, address-instruction diffs 2. Target objects: none. Large objects: none.

### src/scene/cardSequence/iplCardSequence
{"fuzzy_match_percent": 97.225334, "matched_code": "4168", "matched_code_percent": 42.30613, "matched_data": "1496", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 90.0, "total_code": "9852", "total_data": "1496", "total_functions": 30, "total_units": 1}
POOL IDENTICAL up to 43 (mine=43 base=43)
Instruction-exact 27/30.
- `cardThreadMain` 97.9402%; instructions 301/301, diffs 78, address-instruction diffs 8. Target objects: jumptable_81652F68, jumptable_8165321C, lbl_81696CF8, sThread__Q23ipl10memorycard. Large objects: jumptable_81652F68 0x70.
- `loadCardFileIcons` 90.37305%; instructions 508/512, diffs 436, address-instruction diffs 107. Target objects: sThread__Q23ipl10memorycard. Large objects: none.
- `runCardMoveOrCopy` 97.88651%; instructions 608/608, diffs 176, address-instruction diffs 26. Target objects: clearCardWritePending, jumptable_81652F68, sThread__Q23ipl10memorycard. Large objects: jumptable_81652F68 0x70.

### src/scene/sdChannelSelect/iplSDChannelSelect
{"fuzzy_match_percent": 99.77309, "matched_code": "30344", "matched_code_percent": 89.70084, "matched_data": "2960", "matched_data_percent": 100.0, "matched_functions": 123, "matched_functions_percent": 95.34883, "total_code": "33828", "total_data": "2960", "total_functions": 129, "total_units": 1}
POOL IDENTICAL up to 101 (mine=101 base=101)
Instruction-exact 123/129.
- `create__Q33ipl5scene15SDChannelSelectFv` 97.73972%; instructions 145/146, diffs 39, address-instruction diffs 15. Target objects: @24633, @24634, smArg__Q23ipl6System. Large objects: none.
- `collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl` 97.81188%; instructions 101/101, diffs 4, address-instruction diffs 2. Target objects: smArg__Q23ipl6System. Large objects: none.
- `collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl` 97.833336%; instructions 102/102, diffs 4, address-instruction diffs 2. Target objects: smArg__Q23ipl6System. Large objects: none.
- `collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl` 98.007935%; instructions 126/126, diffs 7, address-instruction diffs 2. Target objects: lbl_816105D8, smArg__Q23ipl6System. Large objects: none.
- `collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl` 97.55125%; instructions 361/361, diffs 16, address-instruction diffs 8. Target objects: smArg__Q23ipl6System. Large objects: none.
- `flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv` 99.65714%; instructions 35/35, diffs 2, address-instruction diffs 0. Target objects: smArg__Q23ipl6System. Large objects: none.

### src/scene/sdChannelTitle/iplSDChannelTitle
{"fuzzy_match_percent": 99.98883, "matched_code": "18476", "matched_code_percent": 99.20533, "matched_data": "1976", "matched_data_percent": 100.0, "matched_functions": 68, "matched_functions_percent": 98.55073, "total_code": "18624", "total_data": "1976", "total_functions": 69, "total_units": 1}
POOL IDENTICAL up to 55 (mine=55 base=55)
Instruction-exact 68/69.
- `iplSDChannelTitle_flushSaveBeforeExit` 98.5946%; instructions 37/37, diffs 6, address-instruction diffs 2. Target objects: smArg__Q23ipl6System. Large objects: none.

### src/scene/sdChannelMemory/iplSDMemory
{"fuzzy_match_percent": 99.26294, "matched_code": "14812", "matched_code_percent": 70.96589, "matched_data": "3344", "matched_data_percent": 100.0, "matched_functions": 64, "matched_functions_percent": 96.969696, "total_code": "20872", "total_data": "3344", "total_functions": 66, "total_units": 1}
POOL IDENTICAL up to 90 (mine=90 base=90)
Instruction-exact 63/66.
- `create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect` 99.15884%; instructions 1064/1064, diffs 175, address-instruction diffs 111. Target objects: lbl_81655CA0, lbl_8165680C, lbl_81656824, lbl_8165683C, lbl_81696F7C, lbl_81696F80, lbl_81696F88, lbl_81696F8F, lbl_81696F96, lbl_81696F9D, lbl_81696FA4, lbl_81696FAB, lbl_81696FB3, lbl_81696FBB, smArg__Q23ipl6System. Large objects: lbl_8165683C 0xac.
- `drawTransferTitles__Q33ipl5scene8SDMemoryFv` 93.456764%; instructions 438/451, diffs 371, address-instruction diffs 96. Target objects: lbl_81655CA0, lbl_81694BD0, lbl_81694BD8, lbl_81694BF0, lbl_81694BF4, lbl_81694BF8, lbl_81694BFC, lbl_81696FC2, lbl_81696FC9, lbl_81696FD6, lbl_81696FDA, lbl_81696FE1, smArg__Q23ipl6System. Large objects: none.

### src/scene/setting/iplSetting
{"fuzzy_match_percent": 99.97709, "matched_code": "36796", "matched_code_percent": 97.128075, "matched_data": "5696", "matched_data_percent": 100.0, "matched_functions": 111, "matched_functions_percent": 99.10714, "total_code": "37884", "total_data": "5696", "total_functions": 112, "total_units": 1}
POOL IDENTICAL up to 108 (mine=108 base=108)
Instruction-exact 110/112.
- `scanAP__Q33ipl5scene7SettingFv` 99.20221%; instructions 272/272, diffs 4, address-instruction diffs 2. Target objects: @27404, @27405, @27406, @27407, @27409. Large objects: none.

### src/keyboard/tiCellPhone
{"fuzzy_match_percent": 99.992645, "matched_code": "17696", "matched_code_percent": 92.999794, "matched_data": "3860", "matched_data_percent": 100.0, "matched_functions": 85, "matched_functions_percent": 98.83721, "total_code": "19028", "total_data": "3860", "total_functions": 86, "total_units": 1}
POOL IDENTICAL up to 76 (mine=76 base=76)
Instruction-exact 85/86.
- `create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator` 99.8949%; instructions 333/333, diffs 7, address-instruction diffs 0. Target objects: __vt__Q39textinput11nw4rmanager7AnmPane, __vt__Q49textinput8keyboard13cellphonetype12EventHandler, __vt__Q49textinput8keyboard13cellphonetype16CellPhoneAnmPane, __vt__Q49textinput8keyboard13cellphonetype23CellPhoneControlAnmPane, csPaneNameToControlKey__Q39textinput8keyboard13cellphonetype, csszPredictLanguage__Q39textinput8keyboard13cellphonetype. Large objects: csPaneNameToControlKey__Q39textinput8keyboard13cellphonetype 0x120.

### src/keyboard/tiInputForm
{"fuzzy_match_percent": 99.71999, "matched_code": "47928", "matched_code_percent": 94.614655, "matched_data": "3772", "matched_data_percent": 100.0, "matched_functions": 219, "matched_functions_percent": 99.095024, "total_code": "50656", "total_data": "3772", "total_functions": 221, "total_units": 1}
POOL IDENTICAL up to 20 (mine=20 base=20)
Instruction-exact 217/221.
- `calcCursorPos__Q39textinput9inputform4BaseFff` 93.05215%; instructions 326/326, diffs 43, address-instruction diffs 0. Target objects: mbHyphen__Q29textinput9inputform, scInputFormHalfF, scInputFormOneF, scInputFormZeroF. Large objects: none.
- `create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer` 96.40169%; instructions 356/356, diffs 153, address-instruction diffs 28. Target objects: __vt__Q39textinput11nw4rmanager7AnmPane, __vt__Q39textinput9inputform12EventHandler, __vt__Q39textinput9inputform19NormalButtonAnmPane, csCharColor__Q29textinput9inputform, lbl_816973B4, lbl_816973B8, scP_txtScrll_UP. Large objects: none.

### src/keyboard/tiCandidateBox
{"fuzzy_match_percent": 99.71067, "matched_code": "21728", "matched_code_percent": 90.53333, "matched_data": "4652", "matched_data_percent": 100.0, "matched_functions": 110, "matched_functions_percent": 98.21429, "total_code": "24000", "total_data": "4652", "total_functions": 112, "total_units": 1}
POOL IDENTICAL up to 57 (mine=57 base=57)
Instruction-exact 109/112.
- `create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator` 95.99148%; instructions 356/352, diffs 278, address-instruction diffs 57. Target objects: __vt__Q39textinput8tistring9Decolated, lbl_81694D90, scB_OnBtn, scEmptyWChars, scP_OnBtn, scT_prdc_Text_00. Large objects: none.
- `createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator` 98.49537%; instructions 216/216, diffs 64, address-instruction diffs 5. Target objects: __vt__Q39textinput11nw4rmanager7AnmPane, __vt__Q39textinput12candidatebox12OnOffAnmPane, __vt__Q39textinput12candidatebox13PredictWindow, __vt__Q39textinput12candidatebox20CandidateTextAnmPane, __vt__Q39textinput12candidatebox22CandidateScrollAnmPane, scCandidatePaneData. Large objects: scCandidatePaneData 0x68c.

### src/keyboard/tiSignWindow
{"fuzzy_match_percent": 99.9833, "matched_code": "6300", "matched_code_percent": 87.69488, "matched_data": "3468", "matched_data_percent": 100.0, "matched_functions": 55, "matched_functions_percent": 98.21429, "total_code": "7184", "total_data": "3468", "total_functions": 56, "total_units": 1}
POOL IDENTICAL up to 30 (mine=30 base=30)
Instruction-exact 55/56.
- `create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator` 99.86425%; instructions 221/221, diffs 6, address-instruction diffs 0. Target objects: __vt__Q39textinput11nw4rmanager7AnmPane, __vt__Q49textinput8keyboard10signwindow12EventHandler, __vt__Q49textinput8keyboard10signwindow23CellPhoneSignAllAnmPane, __vt__Q49textinput8keyboard10signwindow23CellPhoneSignButtonPane, __vt__Q49textinput8keyboard10signwindow26CellPhoneSignScrollAnmPane, csLanguageDependencyData__Q39textinput8keyboard10signwindow, csPaneToAnimationInSign__Q39textinput8keyboard10signwindow. Large objects: csLanguageDependencyData__Q39textinput8keyboard10signwindow 0x50, csPaneToAnimationInSign__Q39textinput8keyboard10signwindow 0x640.

### src/keyboard/tiString
{"fuzzy_match_percent": 99.028595, "matched_code": "4632", "matched_code_percent": 89.48995, "matched_data": "288", "matched_data_percent": 100.0, "matched_functions": 41, "matched_functions_percent": 97.61904, "total_code": "5176", "total_data": "288", "total_functions": 42, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 41/42.
- `inputChar__Q39textinput8tistring9DecolatedFw` 90.757355%; instructions 126/136, diffs 73, address-instruction diffs 12. Target objects: none. Large objects: none.

### src/keyboard/tiZiString
{"fuzzy_match_percent": 98.32413, "matched_code": "3136", "matched_code_percent": 56.97674, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 26, "matched_functions_percent": 89.655174, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 26/29.
- `clearCandidates__Q39textinput8tistring6WithZiFv` 93.28395%; instructions 84/81, diffs 76, address-instruction diffs 19. Target objects: ElementBuffer__Q39textinput8tistring6WithZi. Large objects: ElementBuffer__Q39textinput8tistring6WithZi 0x200.
- `update__Q39textinput8tistring6WithZiFv` 97.4574%; instructions 448/446, diffs 427, address-instruction diffs 98. Target objects: ElementBuffer__Q39textinput8tistring6WithZi. Large objects: ElementBuffer__Q39textinput8tistring6WithZi 0x200.
- `setElementBuffer__Q39textinput8tistring6WithZiFv` 90.33846%; instructions 65/65, diffs 18, address-instruction diffs 9. Target objects: ElementBuffer__Q39textinput8tistring6WithZi. Large objects: ElementBuffer__Q39textinput8tistring6WithZi 0x200.

### src/channelScript/CHANSVm
{"fuzzy_match_percent": 99.45986, "matched_code": "39908", "matched_code_percent": 74.505264, "matched_data": "6904", "matched_data_percent": 100.0, "matched_functions": 224, "matched_functions_percent": 96.13734, "total_code": "53564", "total_data": "6904", "total_functions": 233, "total_units": 1}
POOL IDENTICAL up to 125 (mine=125 base=125)
Instruction-exact 224/233.
- `CHANSVmConvertToFloatFromStr` 97.59036%; instructions 83/83, diffs 2, address-instruction diffs 0. Target objects: lbl_81694F08, scFloatConstantList. Large objects: none.
- `VmDateDtor` 94.96703%; instructions 91/91, diffs 7, address-instruction diffs 4. Target objects: scUndefinedUtf16. Large objects: none.
- `VmStringSplit` 98.04054%; instructions 222/222, diffs 66, address-instruction diffs 4. Target objects: none. Large objects: none.
- `CHANSVmFormatString` 99.84919%; instructions 431/431, diffs 13, address-instruction diffs 2. Target objects: jumptable_81669C54, jumptable_81669D34. Large objects: jumptable_81669C54 0xe0, jumptable_81669D34 0x84.
- `VmBlobGetHexString` 98.71951%; instructions 82/82, diffs 14, address-instruction diffs 2. Target objects: scHexDigitsPtr. Large objects: none.
- `VmBlobPackCommon` 97.949104%; instructions 668/668, diffs 244, address-instruction diffs 22. Target objects: lbl_81694FA7. Large objects: none.
- `VmBlobUnpack` 98.452614%; instructions 517/517, diffs 141, address-instruction diffs 12. Target objects: scHexDigitsPtr2. Large objects: none.
- `VmWinEmuWrite` 99.62687%; instructions 67/67, diffs 5, address-instruction diffs 0. Target objects: lbl_8166A07E, lbl_81697583. Large objects: none.
- `CHANSVmStep` 96.98723%; instructions 1253/1253, diffs 276, address-instruction diffs 39. Target objects: CHANSVmConstStringObjectUndefined, CHANSVmDebugVerboseMode, VmARShift, VmAdd, VmBitAnd, VmBitOr, VmBitXor, VmCmpEq, VmCmpGeq, VmCmpGt, VmCmpLeq, VmCmpLt, VmCmpNeq, VmDiv, VmMod, VmMul, VmSub, VmULShift, jumptable_8166A0CC, jumptable_8166A0F4, jumptable_8166A1B0, lbl_8166A0B0, lbl_81694F28, lbl_81694FB8, lbl_81697591, scVmGetResultType. Large objects: VmARShift 0x98, VmAdd 0x158, VmBitAnd 0x54, VmBitOr 0x54, VmBitXor 0x54, VmCmpEq 0x1ac, VmCmpLeq 0x124, VmCmpLt 0x11c, VmCmpNeq 0x54, VmDiv 0xac, VmMod 0xa8, VmMul 0x8c, VmSub 0x7c, VmULShift 0x94, jumptable_8166A0F4 0xbc, jumptable_8166A1B0 0x100.

### libs/RevoEX/src/cdb/CDBRecord
{"fuzzy_match_percent": 99.86998, "matched_code": "5940", "matched_code_percent": 83.94573, "matched_data": "2640", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "7076", "total_data": "2640", "total_functions": 29, "total_units": 1}
POOL IDENTICAL up to 47 (mine=47 base=47)
Instruction-exact 28/29.
- `CDBRecordEncrypt` 99.19014%; instructions 284/284, diffs 44, address-instruction diffs 10. Target objects: lbl_8166BBC0. Large objects: none.

### libs/RevoEX/src/net/md5
{"fuzzy_match_percent": 97.01755, "matched_code": "600", "matched_code_percent": 32.894737, "matched_data": "456", "matched_data_percent": 100.0, "matched_functions": 3, "matched_functions_percent": 75.0, "total_code": "1824", "total_data": "456", "total_functions": 4, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 3/4.
- `ProcessBlock` 95.55556%; instructions 306/306, diffs 197, address-instruction diffs 12. Target objects: k$2351, t$2350. Large objects: k$2351 0xc0, t$2350 0x100.

### libs/RevoEX/src/net/aes
{"fuzzy_match_percent": 84.47093, "matched_code": "1116", "matched_code_percent": 40.552326, "matched_data": "2800", "matched_data_percent": 100.0, "matched_functions": 7, "matched_functions_percent": 77.77778, "total_code": "2752", "total_data": "2800", "total_functions": 9, "total_units": 1}
POOL IDENTICAL up to 4 (mine=4 base=4)
Instruction-exact 7/9.
- `AESiEncryptBlock` 65.81013%; instructions 158/158, diffs 137, address-instruction diffs 6. Target objects: AESiEncryptTable, AESiSubShiftTable. Large objects: AESiEncryptTable 0x400, AESiSubShiftTable 0x100.
- `AESiDecryptBlock` 78.95618%; instructions 251/251, diffs 215, address-instruction diffs 9. Target objects: AESiDecryptTable, AESiInvSubShiftTable. Large objects: AESiDecryptTable 0x400, AESiInvSubShiftTable 0x100.

### libs/RevoEX/src/nhttp/NHTTP_bgnend
{"complete_code": "880", "complete_code_percent": 100.0, "complete_data": "136", "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "880", "matched_code_percent": 100.0, "matched_data": "136", "matched_data_percent": 100.0, "matched_functions": 9, "matched_functions_percent": 100.0, "total_code": "880", "total_data": "136", "total_functions": 9, "total_units": 1}
POOL IDENTICAL up to 4 (mine=4 base=4)
Instruction-exact 9/9.

### libs/RevoEX/src/nhttp/NHTTP_control
{"complete_code": "420", "complete_code_percent": 100.0, "complete_data": "32", "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "420", "matched_code_percent": 100.0, "matched_data": "32", "matched_data_percent": 100.0, "matched_functions": 3, "matched_functions_percent": 100.0, "total_code": "420", "total_data": "32", "total_functions": 3, "total_units": 1}
POOL IDENTICAL up to 1 (mine=1 base=1)
Instruction-exact 3/3.

### libs/RevoEX/src/nhttp/NHTTP_list
{"complete_code": "592", "complete_code_percent": 100.0, "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "592", "matched_code_percent": 100.0, "matched_data_percent": 100.0, "matched_functions": 5, "matched_functions_percent": 100.0, "total_code": "592", "total_functions": 5, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 5/5.

### libs/RevoEX/src/nhttp/NHTTP_os_RVL
{"complete_code": "548", "complete_code_percent": 100.0, "complete_data": "72", "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "548", "matched_code_percent": 100.0, "matched_data": "72", "matched_data_percent": 100.0, "matched_functions": 11, "matched_functions_percent": 100.0, "total_code": "548", "total_data": "72", "total_functions": 11, "total_units": 1}
POOL IDENTICAL up to 3 (mine=3 base=3)
Instruction-exact 11/11.

### libs/RevoEX/src/nhttp/NHTTP_recvbuf
{"complete_data_percent": 100.0, "fuzzy_match_percent": 99.21513, "matched_code": "1196", "matched_code_percent": 70.68558, "matched_data_percent": 100.0, "matched_functions": 6, "matched_functions_percent": 85.71429, "total_code": "1692", "total_functions": 7, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 6/7.
- `NHTTPi_compareTokenN_HdrRecvBuf` 97.32258%; instructions 124/124, diffs 5, address-instruction diffs 2. Target objects: none. Large objects: none.

### libs/RevoEX/src/nhttp/NHTTP_request
{"complete_code": "2512", "complete_code_percent": 100.0, "complete_data": "48", "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "2512", "matched_code_percent": 100.0, "matched_data": "48", "matched_data_percent": 100.0, "matched_functions": 7, "matched_functions_percent": 100.0, "total_code": "2512", "total_data": "48", "total_functions": 7, "total_units": 1}
POOL IDENTICAL up to 1 (mine=1 base=1)
Instruction-exact 7/7.

### libs/RevoEX/src/nhttp/NHTTP_response
{"complete_code": "1044", "complete_code_percent": 100.0, "complete_data": "16", "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "1044", "matched_code_percent": 100.0, "matched_data": "16", "matched_data_percent": 100.0, "matched_functions": 4, "matched_functions_percent": 100.0, "total_code": "1044", "total_data": "16", "total_functions": 4, "total_units": 1}
POOL IDENTICAL up to 1 (mine=1 base=1)
Instruction-exact 4/4.

### libs/RevoEX/src/nhttp/NHTTP_socket_RVL
{"complete_code": "2140", "complete_code_percent": 100.0, "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "2140", "matched_code_percent": 100.0, "matched_data_percent": 100.0, "matched_functions": 10, "matched_functions_percent": 100.0, "total_code": "2140", "total_functions": 10, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 10/10.

### libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL
{"fuzzy_match_percent": 99.9573, "matched_code": "1864", "matched_code_percent": 82.91815, "matched_data": "112", "matched_data_percent": 100.0, "matched_functions": 12, "matched_functions_percent": 85.71429, "total_code": "2248", "total_data": "112", "total_functions": 14, "total_units": 1}
POOL IDENTICAL up to 1 (mine=1 base=1)
Instruction-exact 12/14.
- `NHTTPi_strnicmp` 99.76471%; instructions 51/51, diffs 2, address-instruction diffs 0. Target objects: none. Large objects: none.
- `NHTTPi_compareToken` 99.73333%; instructions 45/45, diffs 2, address-instruction diffs 0. Target objects: none. Large objects: none.

### libs/RevoEX/src/nhttp/NHTTP_thread
{"complete_code": "11292", "complete_code_percent": 100.0, "complete_data": "504", "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "11292", "matched_code_percent": 100.0, "matched_data": "504", "matched_data_percent": 100.0, "matched_functions": 26, "matched_functions_percent": 100.0, "total_code": "11292", "total_data": "504", "total_functions": 26, "total_units": 1}
POOL IDENTICAL up to 8 (mine=8 base=8)
Instruction-exact 26/26.

### libs/RevoEX/src/nwc24/NWC24Download
{"fuzzy_match_percent": 99.950386, "matched_code": "11920", "matched_code_percent": 95.390526, "matched_data": "80", "matched_data_percent": 100.0, "matched_functions": 29, "matched_functions_percent": 96.666664, "total_code": "12496", "total_data": "80", "total_functions": 30, "total_units": 1}
POOL IDENTICAL up to 3 (mine=3 base=3)
Instruction-exact 29/30.
- `NWC24InitDlTask` 98.923615%; instructions 144/144, diffs 31, address-instruction diffs 2. Target objects: NWC24WorkP, lbl_8166E1FC. Large objects: none.

### libs/RevoEX/src/so/SOBasic
{"fuzzy_match_percent": 99.79452, "matched_code": "3836", "matched_code_percent": 93.83562, "matched_data": "144", "matched_data_percent": 100.0, "matched_functions": 21, "matched_functions_percent": 95.454544, "total_code": "4088", "total_data": "144", "total_functions": 22, "total_units": 1}
POOL IDENTICAL up to 1 (mine=1 base=1)
Instruction-exact 21/22.
- `SOGetSockName` 96.666664%; instructions 63/63, diffs 3, address-instruction diffs 0. Target objects: none. Large objects: none.

### libs/RevoEX/src/vf/dskmng/pdm_partition
{"complete_code": "6108", "complete_code_percent": 100.0, "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "6108", "matched_code_percent": 100.0, "matched_data_percent": 100.0, "matched_functions": 19, "matched_functions_percent": 100.0, "total_code": "6108", "total_functions": 19, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 19/19.

### libs/RevoEX/src/vf/develop/sd_drv
{"complete_code": "3608", "complete_code_percent": 100.0, "complete_data": "992", "complete_data_percent": 100.0, "complete_units": 1, "fuzzy_match_percent": 100.0, "matched_code": "3608", "matched_code_percent": 100.0, "matched_data": "992", "matched_data_percent": 100.0, "matched_functions": 16, "matched_functions_percent": 100.0, "total_code": "3608", "total_data": "992", "total_functions": 16, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 16/16.

### libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var
{"complete_data_percent": 100.0, "fuzzy_match_percent": 90.488045, "matched_data_percent": 100.0, "total_code": "2844", "total_functions": 2, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 0/2.
- `TMCJPEGDEC_IdctBlock_Lumi` 86.178986%; instructions 257/257, diffs 185, address-instruction diffs 11. Target objects: none. Large objects: none.
- `TMCJPEGDEC_IdctBlock_Col` 92.927315%; instructions 454/454, diffs 290, address-instruction diffs 5. Target objects: none. Large objects: none.

### libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse
{"complete_data_percent": 100.0, "fuzzy_match_percent": 98.98035, "matched_code": "1348", "matched_code_percent": 26.49371, "matched_data_percent": 100.0, "matched_functions": 3, "matched_functions_percent": 50.0, "total_code": "5088", "total_functions": 6, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 3/6.
- `TMCJPEGDEC_exif_parse` 99.43396%; instructions 212/212, diffs 21, address-instruction diffs 2. Target objects: none. Large objects: none.
- `TMCJPEGDEC_IFD0_tag_parse` 99.49065%; instructions 480/481, diffs 457, address-instruction diffs 40. Target objects: none. Large objects: none.
- `TMCJPEGDEC_IFD1_tag_parse` 96.14876%; instructions 239/242, diffs 226, address-instruction diffs 22. Target objects: none. Large objects: none.

### libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8
{"complete_data_percent": 100.0, "fuzzy_match_percent": 99.64535, "matched_code": "15164", "matched_code_percent": 95.08402, "matched_data_percent": 100.0, "matched_functions": 12, "matched_functions_percent": 92.30769, "total_code": "15948", "total_functions": 13, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 2/13.
- `TMCJPEGDEC_set_converterY8U8V8` 92.78571%; instructions 195/196, diffs 195, address-instruction diffs 58. Target objects: TMCJPEG_814EFEAC, TMCJPEG_814F043C, TMCJPEG_814F0A58, TMCJPEG_814F11C4, TMCJPEG_814F17E0, TMCJPEG_814F1F48, TMCJPEG_814F2570, TMCJPEG_814F2B50, TMCJPEG_814F3158, TMCJPEG_814F32E4, TMCJPEG_814F34A4, TMCJPEG_814F372C. Large objects: TMCJPEG_814EFEAC 0x590, TMCJPEG_814F043C 0x61c, TMCJPEG_814F0A58 0x76c, TMCJPEG_814F11C4 0x61c, TMCJPEG_814F17E0 0x768, TMCJPEG_814F1F48 0x628, TMCJPEG_814F2570 0x5e0, TMCJPEG_814F2B50 0x608, TMCJPEG_814F3158 0x18c, TMCJPEG_814F32E4 0x1c0, TMCJPEG_814F34A4 0x288, TMCJPEG_814F372C 0x2bc.

### libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565
{"complete_data_percent": 100.0, "fuzzy_match_percent": 96.95084, "matched_code": "2648", "matched_code_percent": 42.820183, "matched_data_percent": 100.0, "matched_functions": 7, "matched_functions_percent": 53.846157, "total_code": "6184", "total_functions": 13, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 7/13.
- `TMCJPEGDEC_set_converterRGB565` 93.91765%; instructions 169/170, diffs 169, address-instruction diffs 58. Target objects: TMCJPEGDEC_converterYUV211toRGB565, TMCJPEGDEC_converterYUV211toRGB565edge, TMCJPEGDEC_converterYUV400toRGB565, TMCJPEGDEC_converterYUV400toRGB565edge, TMCJPEGDEC_converterYUV411toRGB565, TMCJPEGDEC_converterYUV411toRGB565edge, TMCJPEGDEC_converterYUV420toRGB565, TMCJPEGDEC_converterYUV420toRGB565edge, TMCJPEGDEC_converterYUV422toRGB565, TMCJPEGDEC_converterYUV422toRGB565edge, TMCJPEGDEC_converterYUV444toRGB565, TMCJPEGDEC_converterYUV444toRGB565edge. Large objects: TMCJPEGDEC_converterYUV211toRGB565 0x188, TMCJPEGDEC_converterYUV211toRGB565edge 0x1b4, TMCJPEGDEC_converterYUV400toRGB565 0x118, TMCJPEGDEC_converterYUV400toRGB565edge 0x14c, TMCJPEGDEC_converterYUV411toRGB565 0x364, TMCJPEGDEC_converterYUV411toRGB565edge 0x1a8, TMCJPEGDEC_converterYUV420toRGB565 0x234, TMCJPEGDEC_converterYUV420toRGB565edge 0x1c8, TMCJPEGDEC_converterYUV422toRGB565 0x220, TMCJPEGDEC_converterYUV422toRGB565edge 0x1ac, TMCJPEGDEC_converterYUV444toRGB565 0x16c, TMCJPEGDEC_converterYUV444toRGB565edge 0x1a0.
- `TMCJPEGDEC_converterYUV411toRGB565` 91.17512%; instructions 217/217, diffs 141, address-instruction diffs 3. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV411toRGB565edge` 95.42453%; instructions 106/106, diffs 61, address-instruction diffs 7. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV422toRGB565` 97.132355%; instructions 136/136, diffs 52, address-instruction diffs 1. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV420toRGB565` 95.42553%; instructions 141/141, diffs 80, address-instruction diffs 2. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV420toRGB565edge` 97.850876%; instructions 114/114, diffs 35, address-instruction diffs 1. Target objects: none. Large objects: none.

### libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8
{"complete_data_percent": 100.0, "fuzzy_match_percent": 90.70224, "matched_code": "660", "matched_code_percent": 10.006064, "matched_data_percent": 100.0, "matched_functions": 2, "matched_functions_percent": 15.384616, "total_code": "6596", "total_functions": 13, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 2/13.
- `TMCJPEGDEC_set_converterRGBA8` 93.91765%; instructions 169/170, diffs 169, address-instruction diffs 58. Target objects: TMCJPEGDEC_converterYUV211toRGBA8, TMCJPEGDEC_converterYUV211toRGBA8edge, TMCJPEGDEC_converterYUV400toRGBA8, TMCJPEGDEC_converterYUV400toRGBA8edge, TMCJPEGDEC_converterYUV411toRGBA8, TMCJPEGDEC_converterYUV411toRGBA8edge, TMCJPEGDEC_converterYUV420toRGBA8, TMCJPEGDEC_converterYUV420toRGBA8edge, TMCJPEGDEC_converterYUV422toRGBA8, TMCJPEGDEC_converterYUV422toRGBA8edge, TMCJPEGDEC_converterYUV444toRGBA8, TMCJPEGDEC_converterYUV444toRGBA8edge. Large objects: TMCJPEGDEC_converterYUV211toRGBA8 0x1a0, TMCJPEGDEC_converterYUV211toRGBA8edge 0x1cc, TMCJPEGDEC_converterYUV400toRGBA8 0x130, TMCJPEGDEC_converterYUV400toRGBA8edge 0x164, TMCJPEGDEC_converterYUV411toRGBA8 0x3c8, TMCJPEGDEC_converterYUV411toRGBA8edge 0x1c0, TMCJPEGDEC_converterYUV420toRGBA8 0x264, TMCJPEGDEC_converterYUV420toRGBA8edge 0x1e0, TMCJPEGDEC_converterYUV422toRGBA8 0x250, TMCJPEGDEC_converterYUV422toRGBA8edge 0x1c4, TMCJPEGDEC_converterYUV444toRGBA8 0x184, TMCJPEGDEC_converterYUV444toRGBA8edge 0x1b8.
- `TMCJPEGDEC_converterYUV411toRGBA8` 82.70661%; instructions 242/242, diffs 153, address-instruction diffs 26. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV411toRGBA8edge` 94.28571%; instructions 112/112, diffs 51, address-instruction diffs 6. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV422toRGBA8` 88.195946%; instructions 148/148, diffs 80, address-instruction diffs 10. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV422toRGBA8edge` 92.0354%; instructions 113/113, diffs 51, address-instruction diffs 5. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV420toRGBA8` 90.973854%; instructions 153/153, diffs 76, address-instruction diffs 10. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV420toRGBA8edge` 87.5%; instructions 120/120, diffs 77, address-instruction diffs 12. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV211toRGBA8` 91.15385%; instructions 104/104, diffs 49, address-instruction diffs 5. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV211toRGBA8edge` 92.17391%; instructions 115/115, diffs 47, address-instruction diffs 5. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV444toRGBA8` 90.670105%; instructions 97/97, diffs 46, address-instruction diffs 5. Target objects: none. Large objects: none.
- `TMCJPEGDEC_converterYUV444toRGBA8edge` 88.90909%; instructions 110/110, diffs 61, address-instruction diffs 5. Target objects: none. Large objects: none.

### libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32
{"complete_data_percent": 100.0, "fuzzy_match_percent": 99.710144, "matched_data_percent": 100.0, "total_code": "1104", "total_functions": 1, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 0/1.
- `TMCJPEGDEC_decode_iquant` 99.710144%; instructions 276/276, diffs 13, address-instruction diffs 4. Target objects: TMCJPEGDEC_Zigzag_data, TMCJPEGDEC_Zigzag_loop. Large objects: none.

### libs/NW4R/src/lyt/lyt_window
{"fuzzy_match_percent": 99.75864, "matched_code": "9848", "matched_code_percent": 86.751236, "matched_data": "316", "matched_data_percent": 100.0, "matched_functions": 20, "matched_functions_percent": 95.2381, "total_code": "11352", "total_data": "316", "total_functions": 21, "total_units": 1}
POOL IDENTICAL up to 1 (mine=1 base=1)
Instruction-exact 20/21.
- `DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc` 98.17819%; instructions 376/376, diffs 119, address-instruction diffs 10. Target objects: flipInfos$7849, lbl_8169553C, lbl_81695540, lbl_81695548. Large objects: none.

### libs/RVL_SDK/src/kpad/KPAD
{"fuzzy_match_percent": 99.875916, "matched_code": "12316", "matched_code_percent": 94.33211, "matched_data": "8032", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "13056", "total_data": "8032", "total_functions": 29, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 28/29.
- `KPADInit` 97.810814%; instructions 185/185, diffs 58, address-instruction diffs 4. Target objects: __KPADVersion, iaccXY_nrm_hori, icenter_org, idist_org, inside_kpads, isec_nrm_hori, kp_dist_vv1, kp_err_dist_max, kp_err_dist_min, kp_obj_interval, lbl_81140C80, lbl_816958A8, lbl_816958B4, lbl_816958BC, lbl_816958C4, lbl_8169590C, lbl_81695910, lbl_8169821C. Large objects: inside_kpads 0x14a0, lbl_81140C80 0x40.

### libs/RVL_SDK/src/wad/wad
{"fuzzy_match_percent": 98.944, "matched_code": "13180", "matched_code_percent": 53.795918, "matched_data": "528", "matched_data_percent": 100.0, "matched_functions": 35, "matched_functions_percent": 87.5, "total_code": "24500", "total_data": "528", "total_functions": 40, "total_units": 1}
POOL IDENTICAL up to 18 (mine=18 base=18)
Instruction-exact 35/40.
- `WADImportGetBlocks` 94.24161%; instructions 286/298, diffs 286, address-instruction diffs 57. Target objects: none. Large objects: none.
- `WADImportEx` 99.02269%; instructions 1146/1146, diffs 201, address-instruction diffs 24. Target objects: WAD_815BFFA8, __func__$1718. Large objects: WAD_815BFFA8 0xf8.
- `WAD_815C1288` 96.803276%; instructions 61/61, diffs 32, address-instruction diffs 2. Target objects: none. Large objects: none.
- `WADBackupEx` 97.385124%; instructions 1057/1062, diffs 876, address-instruction diffs 204. Target objects: @4643, WAD_815C1288, lbl_816982F0. Large objects: WAD_815C1288 0xf4.
- `WADImportDVDExForBS` 97.49049%; instructions 261/263, diffs 193, address-instruction diffs 28. Target objects: none. Large objects: none.

### libs/RVL_SDK/src/fa/pdm_partition
{"complete_data_percent": 100.0, "fuzzy_match_percent": 98.86006, "matched_code": "3380", "matched_code_percent": 90.958015, "matched_data_percent": 100.0, "matched_functions": 19, "matched_functions_percent": 95.0, "total_code": "3716", "total_functions": 20, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 19/20.
- `pdm_part_is_master_boot_sector` 87.39286%; instructions 86/84, diffs 84, address-instruction diffs 17. Target objects: none. Large objects: none.

### libs/RVL_SDK/src/fa/driver/sd_drv
{"fuzzy_match_percent": 99.14116, "matched_code": "9260", "matched_code_percent": 78.74149, "matched_data": "3592", "matched_data_percent": 100.0, "matched_functions": 22, "matched_functions_percent": 84.61539, "total_code": "11760", "total_data": "3592", "total_functions": 26, "total_units": 1}
POOL IDENTICAL up to 46 (mine=46 base=46)
Instruction-exact 22/26.
- `pfd_sddrv_init` 93.125%; instructions 141/144, diffs 142, address-instruction diffs 56. Target objects: g_event, g_pfd_sddev, g_pfd_sddrv_info, lbl_81690D18, pfd_st_inter_callback, pfd_st_removal_callback. Large objects: g_pfd_sddev 0x40, pfd_st_inter_callback 0x114, pfd_st_removal_callback 0x108.
- `pfd_sddrv_finalize` 92.63158%; instructions 57/57, diffs 4, address-instruction diffs 0. Target objects: g_pfd_sddrv_info, lbl_81690FFC, lbl_81691040. Large objects: lbl_81690FFC 0x41, lbl_81691040 0x2d0.
- `pfd_sddrv_store_mbr_buf` 99.75247%; instructions 202/202, diffs 9, address-instruction diffs 0. Target objects: lbl_8169134C, sddrv_size_depend_tbl. Large objects: lbl_8169134C 0x57, sddrv_size_depend_tbl 0x150.
- `pfd_sddrv_build_fat32_mbr_bpb` 95.202705%; instructions 229/222, diffs 122, address-instruction diffs 36. Target objects: g_pfd_sddrv_buf, g_pfd_sddrv_info, lbl_81690D18. Large objects: g_pfd_sddrv_buf 0x200.

### libs/RVL_SDK/src/nup/nup
{"fuzzy_match_percent": 99.5968, "matched_code": "7748", "matched_code_percent": 71.98068, "matched_data": "1720", "matched_data_percent": 100.0, "matched_functions": 20, "matched_functions_percent": 86.95652, "total_code": "10764", "total_data": "1720", "total_functions": 23, "total_units": 1}
POOL IDENTICAL up to 28 (mine=28 base=28)
Instruction-exact 20/23.
- `__nupParseServerInfo__FP14NUPContextInfoPcPcUx` 98.108406%; instructions 452/452, diffs 148, address-instruction diffs 24. Target objects: lbl_81691798, lbl_816983C8, lbl_816983CC. Large objects: none.
- `__nupGetBootVersion__FP14NUPContextInfoP14ESTitleVersion` 99.35583%; instructions 163/163, diffs 17, address-instruction diffs 3. Target objects: none. Large objects: none.
- `__nupGetTitleSize__FP12NUPTitleInfo` 99.100716%; instructions 139/139, diffs 22, address-instruction diffs 3. Target objects: none. Large objects: none.

### libs/RVL_SDK/src/kbd/kbd_lib
{"fuzzy_match_percent": 99.93963, "matched_code": "3728", "matched_code_percent": 64.67731, "matched_data": "5296", "matched_data_percent": 100.0, "matched_functions": 17, "matched_functions_percent": 80.952385, "total_code": "5764", "total_data": "5296", "total_functions": 21, "total_units": 1}
POOL IDENTICAL up to 0 (mine=0 base=0)
Instruction-exact 17/21.
- `kbdEventHandler` 99.83871%; instructions 186/186, diffs 5, address-instruction diffs 3. Target objects: kbdData. Large objects: kbdData 0x9a0.
- `kbdProcMod` 99.90234%; instructions 256/256, diffs 4, address-instruction diffs 0. Target objects: jumptable_816925A0, kbdData, kbdInitialized, kbdKeyMaps. Large objects: jumptable_816925A0 0x88, kbdData 0x9a0, kbdKeyMaps 0x400.
- `kbd_led_handler` 99.72%; instructions 25/25, diffs 3, address-instruction diffs 0. Target objects: kbdCmdBuf, kbdLCBuf. Large objects: kbdCmdBuf 0x180, kbdLCBuf 0x60.
- `KBDSetModState` 99.40476%; instructions 42/42, diffs 4, address-instruction diffs 0. Target objects: kbdData, kbdInitialized. Large objects: kbdData 0x9a0.

## Candidate triage

The baseline covers 51 requested units and 106 open functions. Both sd_drv and pdm_partition copies are included; RevoEX copies already have no open functions. Already-exact NHTTP units are retained in the inventory. No AOSS/ATERM/AOSSLink or eZiText source is in scope.

Closest structural candidate: tiCandidateBox scCandidatePaneData is a synthetic wrapper containing 26 0x40-byte pane records and a 12-byte tail string. Actual bytes at 0x8165D978 are P_OffBtn followed by four zero bytes. Array consumers use exactly 26 records. UIOnOffButton::Create uses base+0x680 only as a string in searchPaneComponent/searchAnmPane/FindPaneByName. No function treats the string as a 27th record. Source currently forces them into the same object. Test the real table and ordinary string separately, with no explicit string padding.

KPAD lbl_81140C80 is a 0x40-byte float region whose first 0x30 bytes are passed as an MTX34 and initialized as a rotation matrix. No evidence yet identifies a second object in the last 0x10 bytes. A split there is not justified without further references. The typed inside_kpads[4] is one repeated array, not a mixed aggregate.

kbdData is four 0x268-byte KBDChannel records; all indexed references agree with that stride. kbdKeyMaps is a homogeneous map array with storage union. Neither establishes separate object boundaries. sFriendInfo is a full NWC24FriendInfo that is copied and cleared as 0x140 bytes. Flags0 is a homogeneous u32 array. These must not be split solely to influence allocation.

ATTEMPT {"build": 0, "functions": [{"diffs": 231, "insns": [353, 352], "name": "create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator", "percent": 98.286934}, {"diffs": 64, "insns": [216, 216], "name": "createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator", "percent": 98.49537}], "gained": [], "label": "separate pane records from ordinary off-button name array", "lost": [], "measures": {"fuzzy_match_percent": 99.84534, "matched_code": "21728", "matched_code_percent": 90.53333, "matched_data": "1164", "matched_data_percent": 25.021496, "matched_functions": 110, "matched_functions_percent": 98.21429, "total_code": "24000", "total_data": "4652", "total_functions": 112, "total_units": 1}, "pool": "POOL IDENTICAL up to 57 (mine=57 base=57)", "pool_ok": true, "source_hash": "4bdcbe84d9c5", "trial": 1, "unit": "src/keyboard/tiCandidateBox"}

ATTEMPT {"build": 0, "functions": [{"diffs": 231, "insns": [353, 352], "name": "create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator", "percent": 98.27273}, {"diffs": 64, "insns": [216, 216], "name": "createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator", "percent": 98.49537}], "gained": [], "label": "standalone pane array and ordinary off-button string literal accessor", "lost": [], "measures": {"fuzzy_match_percent": 99.8445, "matched_code": "21728", "matched_code_percent": 90.53333, "matched_data": "116", "matched_data_percent": 2.4935513, "matched_functions": 110, "matched_functions_percent": 98.21429, "total_code": "24000", "total_data": "4652", "total_functions": 112, "total_units": 1}, "pool": "FIRST DIVERGENCE at index 4\n    2 mine=0x6c     base=0x6c    \n      M 'P_prdc_scrl_Left'\n      B 'P_prdc_scrl_Left'\n    3 mine=0xac     base=0xac    \n      M 'P_prdc_scrl_Rght'\n      B 'P_prdc_scrl_Rght'\n*   4 mine=0x6a8    base=0x6a8   \n      M 'B_OffBtn'\n      B 'P_OffBtn'\n*   5 mine=0x6b4    base=0x6b4   \n      M 'P_JPOffBtn'\n      B 'B_OffBtn'\n*   6 mine=0x6c0    base=0x6c0   \n      M 'P_CNOffBtn'\n      B 'P_JPOffBtn'\n*   7 mine=0x6cc    base=0x6cc   \n      M 'P_CNOnBtn'\n      B 'P_CNOffBtn'\n*   8 mine=0x6d8    base=0x6d8   \n      M 'B_prdc_scrl_Left'\n      B 'P_CNOnBtn'\n\nmine has 57 strings, base has 57", "pool_ok": false, "source_hash": "a0f5ae8bb1bb", "trial": 2, "unit": "src/keyboard/tiCandidateBox"}

ATTEMPT {"build": 0, "functions": [{"diffs": 317, "insns": [354, 352], "name": "create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator", "percent": 96.701706}, {"diffs": 64, "insns": [216, 216], "name": "createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator", "percent": 98.49537}], "gained": [], "label": "standalone pane array and const off-button name object", "lost": [], "measures": {"fuzzy_match_percent": 99.752335, "matched_code": "21728", "matched_code_percent": 90.53333, "matched_data": "116", "matched_data_percent": 2.4935513, "matched_functions": 110, "matched_functions_percent": 98.21429, "total_code": "24000", "total_data": "4652", "total_functions": 112, "total_units": 1}, "pool": "FIRST DIVERGENCE at index 4\n    2 mine=0x6c     base=0x6c    \n      M 'P_prdc_scrl_Left'\n      B 'P_prdc_scrl_Left'\n    3 mine=0xac     base=0xac    \n      M 'P_prdc_scrl_Rght'\n      B 'P_prdc_scrl_Rght'\n*   4 mine=0x6a8    base=0x6a8   \n      M 'B_OffBtn'\n      B 'P_OffBtn'\n*   5 mine=0x6b4    base=0x6b4   \n      M 'P_JPOffBtn'\n      B 'B_OffBtn'\n*   6 mine=0x6c0    base=0x6c0   \n      M 'P_CNOffBtn'\n      B 'P_JPOffBtn'\n*   7 mine=0x6cc    base=0x6cc   \n      M 'P_CNOnBtn'\n      B 'P_CNOffBtn'\n*   8 mine=0x6d8    base=0x6d8   \n      M 'B_prdc_scrl_Left'\n      B 'P_CNOnBtn'\n\nmine has 56 strings, base has 57", "pool_ok": false, "source_hash": "e7c2dc9d3b63", "trial": 3, "unit": "src/keyboard/tiCandidateBox"}

tiCandidateBox trials 1-3 produced no exact gain. The natural writable string preserved the pool; the const object and literal accessor moved the pool. All three left createAnmPane_ at 64 differences. Restored source, with no metadata edits.

Next boundary candidate: tiZiString CandidatesBuffer size 0x600 is used as three independent 0x200-byte regions. clearCandidates clears them separately with sizes 0x200, 0x1fe and 0x200 at ElementBuffer+0x200, +0x400 and +0x600. The input methods only use the first region. setElementBuffer separately clears the middle region. EZTXGetParam::candidates and update's input-to-result copy use only the third region. The target forms all three addresses from the common BSS base, whereas the current source preserves a second base for the inferred combined CandidatesBuffer. Test separate real input, element-work and prediction arrays. Keep section bytes, total BSS size, existing alignment and all resolved reference targets fixed.

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 8, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 99.30769}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "split input, element-work and prediction arrays at three target memset boundaries", "lost": [], "measures": {"fuzzy_match_percent": 99.43896, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "384", "matched_data_percent": 5.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "86c93cfda3dd", "trial": 4, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 8, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 99.30769}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "prove corrected target symbols and remeasure three distinct candidate buffers", "lost": [], "measures": {"fuzzy_match_percent": 99.43896, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "86c93cfda3dd", "trial": 5, "unit": "src/keyboard/tiZiString"}

Reference proof after tiZiString symbol correction: all 1027 extracted objects have identical allocated-section types, sizes and SHA256 byte hashes. All 109496 relocation entries retain the same relocation section, offset, type and resolved destination section+value+addend. Manifest comparison reports changed=[]. The corrected unit still has 7680 data bytes; all 7680 match. No splits.txt ranges changed. Full raw manifest and comparator are saved under /tmp/agg-sweep for this run.

## First accepted worker state

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3460/5504 data 7680/7680 functions 27/29 fuzzy 99.4390 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 27/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 99.43896
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 98.36996
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 99.30769
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 98.3241
regressions vs baseline: 0
global matched_code_percent: 92.57366 -> 92.58447
global fuzzy_match_percent: 99.73627 -> 99.73832
global complete_code_percent: 76.20227 -> 76.20227
global matched_data_percent: 99.94696 -> 99.94696
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 8, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 99.30769}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "setElementBuffer reads the distinct input buffer through a const pointer", "lost": [], "measures": {"fuzzy_match_percent": 99.43896, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "d7f08ae2b616", "trial": 6, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 16, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 93.15385}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "setElementBuffer binds separate element and const input array references", "lost": [], "measures": {"fuzzy_match_percent": 99.148254, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "08398ac8718d", "trial": 7, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 8, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 99.30769}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "separate input object with body using the same narrowed count as the condition", "lost": [], "measures": {"fuzzy_match_percent": 99.43896, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "e64c27fef411", "trial": 8, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 13, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 98.38461}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "input and element pointer declarations follow their post-clear lifetimes", "lost": [], "measures": {"fuzzy_match_percent": 99.39535, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "f8eb9947ed00", "trial": 9, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 8, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 99.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "indexed input read helper owns the independent input global address", "lost": [], "measures": {"fuzzy_match_percent": 99.424416, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "5e1069e0a752", "trial": 10, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 47, "insns": [66, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 96.76923}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "separate buffer copy helper receives const input and mutable element arrays", "lost": [], "measures": {"fuzzy_match_percent": 99.31904, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "4be3debcc782", "trial": 11, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "candidate element view binds independent input and output objects", "lost": [], "measures": {"fuzzy_match_percent": 99.47166, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "4dd87de61882", "trial": 12, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 8, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 99.30769}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "separate global element conversion helper with explicit input pointer", "lost": [], "measures": {"fuzzy_match_percent": 99.43896, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "6efbb5d815c5", "trial": 13, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 9, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 98.84615}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "input pointer declared before writable element pointer after storage split", "lost": [], "measures": {"fuzzy_match_percent": 99.41715, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "6e83e0b4b419", "trial": 14, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 47, "insns": [66, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 93.61539}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "narrowed element index belongs to the entire input loop", "lost": [], "measures": {"fuzzy_match_percent": 99.17006, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "ca420f1a259b", "trial": 15, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 16, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 95.2}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv"], "label": "input pointer binds its independent array at function entry", "lost": [], "measures": {"fuzzy_match_percent": 99.24491, "matched_code": "3460", "matched_code_percent": 62.863373, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 27, "matched_functions_percent": 93.10345, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "1eac611d8b49", "trial": 16, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "retain independent-buffer view with exact setElementBuffer", "lost": [], "measures": {"fuzzy_match_percent": 99.47166, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "4dd87de61882", "trial": 17, "unit": "src/keyboard/tiZiString"}

## Second accepted worker state

Trial 12 binds the two real input and element globals in ElementInputView. Its constructor and read/element accessors inline without additional code or objects. setElementBuffer is 65/65 instructions, diffs 0, exact-name objdiff 100.0. The direct pointer, array-reference, helper-read and declaration-lifetime alternatives did not match. clearCandidates remains exact. Full gate:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3720/5504 data 7680/7680 functions 28/29 fuzzy 99.4717 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 28/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 99.47166
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 98.36996
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 98.3241
regressions vs baseline: 0
global matched_code_percent: 92.57366 -> 92.59315
global fuzzy_match_percent: 99.73627 -> 99.73837
global complete_code_percent: 76.20227 -> 76.20227
global matched_data_percent: 99.94696 -> 99.94696
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "prediction search helper binds the independent element and result objects", "lost": [], "measures": {"fuzzy_match_percent": 99.47166, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "c6baf290218a", "trial": 18, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 37, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 99.46861}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "latest-word suffix helper owns only the independent context object", "lost": [], "measures": {"fuzzy_match_percent": 99.82776, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "1318734b1e5f", "trial": 19, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "input-to-prediction copy helper names both separate objects", "lost": [], "measures": {"fuzzy_match_percent": 99.47166, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "b61fbb7a17ff", "trial": 20, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "prediction buffer view binds both pointer fields after search flags", "lost": [], "measures": {"fuzzy_match_percent": 99.47166, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "1b5193ca6142", "trial": 21, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 85, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.36996}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "model forty candidate words as separate rows of the existing result array", "lost": [], "measures": {"fuzzy_match_percent": 99.47166, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "6118e212d953", "trial": 22, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 141, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.13453}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "final prediction copy is an inline member over the independent result object", "lost": [], "measures": {"fuzzy_match_percent": 99.39535, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "69cba6e50407", "trial": 23, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 37, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 99.46861}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "prediction output view owns read cursor and result row cursor", "lost": [], "measures": {"fuzzy_match_percent": 99.82776, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "45f3bae22724", "trial": 24, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 36, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 99.49103}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "prediction output view binds result rows before a const input cursor", "lost": [], "measures": {"fuzzy_match_percent": 99.83503, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "5ac04b7a87c3", "trial": 25, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 37, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 99.46861}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "prediction output advances complete 64-character row objects", "lost": [], "measures": {"fuzzy_match_percent": 99.82776, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "6937ecc8492e", "trial": 26, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 37, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 99.46861}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "prediction output rows consume a const character cursor", "lost": [], "measures": {"fuzzy_match_percent": 99.82776, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "e75a18950588", "trial": 27, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 37, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 99.46861}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "prediction output uses native wide-character pointers for words", "lost": [], "measures": {"fuzzy_match_percent": 99.82776, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "84e9a0b8d45b", "trial": 28, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 33, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 99.524666}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "result buffer bound before readonly prediction input at copy start", "lost": [], "measures": {"fuzzy_match_percent": 99.84593, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "b0a45fb31c44", "trial": 29, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 126, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.3139}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "Korean word copy helper consumes prediction input and writes one result row", "lost": [], "measures": {"fuzzy_match_percent": 99.45349, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "2f0fcdc58eba", "trial": 30, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 121, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.40359}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "wide word copy helper consumes prediction input and writes one result row", "lost": [], "measures": {"fuzzy_match_percent": 99.48256, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "f616675dca0b", "trial": 31, "unit": "src/keyboard/tiZiString"}

## Prior trial coverage for parked functions

All 106 functions in the fresh inventory have at least three distinct source-level trials recorded before this sweep. These references are historical attempts, not new compiles in this run. They prevent repeating the old helper/type/scheduling searches on functions for which lever 13 has no object-boundary evidence. Current trial records above separately identify the new compiled boundary experiments.

- `libs/NW4R/src/lyt/lyt_window DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc`: tools/decomp-assist/fz2.attempts.md:755 Round4 final open-function and data audit; tools/decomp-assist/fz2.attempts.md:826 lyt_window data gate; tools/decomp-assist/prior1.attempts.md:105 W1 reference mutable bUseVtxCol
- `libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 TMCJPEGDEC_decode_iquant`: tools/decomp-assist/jpeg-matching-attempts.md:215 huffman code uses decoded threshold; tools/decomp-assist/jpeg-matching-attempts.md:216 dc load failure through common return; tools/decomp-assist/jpeg-matching-attempts.md:217 sign-extension subtraction operand grouping
- `libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var TMCJPEGDEC_IdctBlock_Col`: tools/decomp-assist/jpeg-matching-attempts.md:205 ac operand order; tools/decomp-assist/jpeg-matching-attempts.md:206 butterfly operand grouping; tools/decomp-assist/jpeg-matching-attempts.md:207 first pass row counter form
- `libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var TMCJPEGDEC_IdctBlock_Lumi`: tools/decomp-assist/jpeg-matching-attempts.md:200 ac operand order; tools/decomp-assist/jpeg-matching-attempts.md:201 butterfly operand grouping; tools/decomp-assist/jpeg-matching-attempts.md:202 first pass row counter form
- `libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD0_tag_parse`: tools/decomp-assist/ult3.attempts.md:38 compression has own ignored return block; tools/decomp-assist/ult3.attempts.md:39 compression returns separately and rational pointer declared before offset; tools/decomp-assist/ult3.attempts.md:40 all unhandled compressed/strip/jpeg-offset tags have separate exits
- `libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD1_tag_parse`: tools/decomp-assist/ult3.attempts.md:20 remove redundant orientation case and give strip offset explicit return; tools/decomp-assist/ult3.attempts.md:21 ignored tags use exact separate strip-offset exit without orientation or planar noops; tools/decomp-assist/ult3.attempts.md:22 ignored tags return directly, all recognized bodies remain separate
- `libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_exif_parse`: tools/decomp-assist/ult3.attempts.md:44 each IFD has independent lexical entry cursor; tools/decomp-assist/ult3.attempts.md:45 each IFD has independent entry-count and byte-length locals; tools/decomp-assist/ult3.attempts.md:46 each IFD owns all real traversal locals
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV411toRGB565`: tools/decomp-assist/jpeg-matching-attempts.md:86 source pointer walks; tools/decomp-assist/jpeg-matching-attempts.md:87 column declared at function scope; tools/decomp-assist/jpeg-matching-attempts.md:88 x/y bound initialization order
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV411toRGB565edge`: tools/decomp-assist/jpeg-matching-attempts.md:91 source pointer walks; tools/decomp-assist/jpeg-matching-attempts.md:92 column declared at function scope; tools/decomp-assist/jpeg-matching-attempts.md:93 x/y bound initialization order
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV420toRGB565`: tools/decomp-assist/jpeg-matching-attempts.md:106 source pointer walks; tools/decomp-assist/jpeg-matching-attempts.md:107 column declared at function scope; tools/decomp-assist/jpeg-matching-attempts.md:108 x/y bound initialization order
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV420toRGB565edge`: tools/decomp-assist/jpeg-matching-attempts.md:111 source pointer walks; tools/decomp-assist/jpeg-matching-attempts.md:112 column declared at function scope; tools/decomp-assist/jpeg-matching-attempts.md:113 x/y bound initialization order
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV422toRGB565`: tools/decomp-assist/jpeg-matching-attempts.md:96 source pointer walks; tools/decomp-assist/jpeg-matching-attempts.md:97 column declared at function scope; tools/decomp-assist/jpeg-matching-attempts.md:98 x/y bound initialization order
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_set_converterRGB565`: tools/decomp-assist/jpeg-matching-attempts.md:82 state load before component; tools/decomp-assist/jpeg-matching-attempts.md:83 pointer stores before converter stores; tools/decomp-assist/jpeg-matching-attempts.md:84 dimension operand order
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV211toRGBA8`: tools/decomp-assist/fz20.attempts.md:1365 91.05769%; tools/decomp-assist/fz20.attempts.md:1366 91.95652%; tools/decomp-assist/fz20.attempts.md:1481 TMCJPEGDEC_converterYUV444toRGBA8edge
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV211toRGBA8edge`: tools/decomp-assist/fz20.attempts.md:1366 91.95652%; tools/decomp-assist/fz20.attempts.md:1482 TMCJPEGDEC_converterYUV444toRGBA8edge; tools/decomp-assist/fz20.attempts.md:2097 92.0%
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV411toRGBA8`: tools/decomp-assist/fz20.attempts.md:1359 82.54132%; tools/decomp-assist/fz20.attempts.md:1360 93.83929%; tools/decomp-assist/fz20.attempts.md:1475 TMCJPEGDEC_converterYUV444toRGBA8edge
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV411toRGBA8edge`: tools/decomp-assist/fz20.attempts.md:1360 93.83929%; tools/decomp-assist/fz20.attempts.md:1476 TMCJPEGDEC_converterYUV444toRGBA8edge; tools/decomp-assist/fz20.attempts.md:2091 93.88393%
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV420toRGBA8`: tools/decomp-assist/fz20.attempts.md:1363 89.33987%; tools/decomp-assist/fz20.attempts.md:1364 87.316666%; tools/decomp-assist/fz20.attempts.md:1479 TMCJPEGDEC_converterYUV444toRGBA8edge
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV420toRGBA8edge`: tools/decomp-assist/fz20.attempts.md:1364 87.316666%; tools/decomp-assist/fz20.attempts.md:1480 TMCJPEGDEC_converterYUV444toRGBA8edge; tools/decomp-assist/fz20.attempts.md:2095 87.4%
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV422toRGBA8`: tools/decomp-assist/fz20.attempts.md:1361 87.6554%; tools/decomp-assist/fz20.attempts.md:1362 90.04425%; tools/decomp-assist/fz20.attempts.md:1477 TMCJPEGDEC_converterYUV444toRGBA8edge
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV422toRGBA8edge`: tools/decomp-assist/fz20.attempts.md:1362 90.04425%; tools/decomp-assist/fz20.attempts.md:1478 TMCJPEGDEC_converterYUV444toRGBA8edge; tools/decomp-assist/fz20.attempts.md:2093 90.08849%
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV444toRGBA8`: tools/decomp-assist/fz20.attempts.md:1367 90.4433%; tools/decomp-assist/fz20.attempts.md:1368 88.90909%; tools/decomp-assist/fz20.attempts.md:1483 TMCJPEGDEC_converterYUV444toRGBA8edge
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV444toRGBA8edge`: tools/decomp-assist/fz20.attempts.md:1368 88.90909%; tools/decomp-assist/fz20.attempts.md:1484 TMCJPEGDEC_converterYUV444toRGBA8edge; tools/decomp-assist/jpeg-matching-attempts.md:190 source pointer walks
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_set_converterRGBA8`: tools/decomp-assist/fz20.attempts.md:1358 93.91765%; tools/decomp-assist/fz20.attempts.md:1474 TMCJPEGDEC_converterYUV444toRGBA8edge; tools/decomp-assist/jpeg-matching-attempts.md:141 state load before component
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8 TMCJPEGDEC_set_converterY8U8V8`: tools/decomp-assist/jpeg-matching-attempts.md:333 converter stores before row stores; tools/decomp-assist/jpeg-matching-attempts.md:334 pointer to whole conversion buffer; tools/decomp-assist/jpeg-matching-attempts.md:335 signed conversion sample pointer
- `libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_build_fat32_mbr_bpb`: tools/decomp-assist/perm2.attempts.md:1120 pfd_sddrv_build_fat32_mbr_bpb new T3 source trials; tools/decomp-assist/perm2.attempts.md:1186 94.75225; tools/decomp-assist/data-d6.attempts.md:62 named sector buffer
- `libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_finalize`: tools/decomp-assist/perm2.attempts.md:1110 pfd_sddrv_finalize new T3 source trials; tools/decomp-assist/data-d6.attempts.md:50 clear disk before media state; tools/decomp-assist/data-d6.attempts.md:52 named remaining flags
- `libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_init`: tools/decomp-assist/perm2.attempts.md:1092 pfd_sddrv_init new T3 source trials; tools/decomp-assist/data-d6.attempts.md:44 unsigned null comparison; tools/decomp-assist/data-d6.attempts.md:46 named null disk
- `libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_store_mbr_buf`: tools/decomp-assist/perm2.attempts.md:1101 pfd_sddrv_store_mbr_buf new T3 source trials; tools/decomp-assist/data-d6.attempts.md:56 name cylinder size; tools/decomp-assist/data-d6.attempts.md:58 name first sector before CHS
- `libs/RVL_SDK/src/fa/pdm_partition pdm_part_is_master_boot_sector`: tools/decomp-assist/sol-high-four-oct2.attempts.jsonl:21 inline endian helper with high byte first and two addition groups; tools/decomp-assist/sol-high-four-oct2.attempts.jsonl:22 evaluate high byte group before low byte group; tools/decomp-assist/sol-high-four-oct2.attempts.jsonl:23 declare traversal index after pointers at endian helper boundary
- `libs/RVL_SDK/src/kbd/kbd_lib KBDSetModState`: tools/decomp-assist/sol-low-leaves-attempts.md:30 typed channel pointer for load and store; tools/decomp-assist/sol-low-leaves-attempts.md:31 physical modifier masked expression; tools/decomp-assist/sol-low-leaves-attempts.md:32 single modifier state temporary
- `libs/RVL_SDK/src/kbd/kbd_lib kbdEventHandler`: tools/decomp-assist/sol-low-leaves-attempts.md:16 reuse report status temporary in comparisons; tools/decomp-assist/sol-low-leaves-attempts.md:17 initialize channel pointer in one expression; tools/decomp-assist/sol-low-leaves-attempts.md:106 remove redundant report status temporary
- `libs/RVL_SDK/src/kbd/kbd_lib kbdProcMod`: tools/decomp-assist/sol-low-leaves-attempts.md:37 pass modifier expression directly; tools/decomp-assist/sol-low-leaves-attempts.md:38 local modifier scope around inline setter; tools/decomp-assist/sol-low-leaves-attempts.md:39 channel argument recovered from typed channel
- `libs/RVL_SDK/src/kbd/kbd_lib kbd_led_handler`: tools/decomp-assist/sol-low-leaves-attempts.md:33 load completion callback before releasing command; tools/decomp-assist/sol-low-leaves-attempts.md:43 null callback test after clear; conditional error code; tools/decomp-assist/sol-low-leaves-attempts.md:44 guard completion body with non-null callback
- `libs/RVL_SDK/src/kpad/KPAD KPADInit`: tools/decomp-assist/perm7.attempts.md:58 matrix_before_scale_initialization; tools/decomp-assist/perm7.attempts.md:61 reference_height_before_width; tools/decomp-assist/perm7.attempts.md:63 direct_sine_assignment
- `libs/RVL_SDK/src/nup/nup __nupGetBootVersion__FP14NUPContextInfoP14ESTitleVersion`: tools/decomp-assist/h6.attempts.md:108 013-kbd_lib-led-result-switch-failure; tools/decomp-assist/h6.attempts.md:136 018-nup-installed-content-array; tools/decomp-assist/h6.attempts.md:142 019-nup-installed-content-reference
- `libs/RVL_SDK/src/nup/nup __nupGetTitleSize__FP12NUPTitleInfo`: tools/decomp-assist/sol-med-structural-round10.attempts.md:16 __nupGetTitleSize__FP12NUPTitleInfo; tools/decomp-assist/sol-med-structural-round10.attempts.md:224 139/139 instructions; reserve high-word temporary and installed-content helper colors differ.; tools/decomp-assist/sol-med-structural-round12.attempts.md:15 diagnosis __nupGetTitleSize__FP12NUPTitleInfo
- `libs/RVL_SDK/src/nup/nup __nupParseServerInfo__FP14NUPContextInfoPcPcUx`: tools/decomp-assist/sol-med-structural-round10.attempts.md:13 __nupParseServerInfo__FP14NUPContextInfoPcPcUx; tools/decomp-assist/sol-med-structural-round10.attempts.md:221 452/452 instructions; repeated tag-helper local colors differ.; tools/decomp-assist/sol-med-structural-round12.attempts.md:12 diagnosis __nupParseServerInfo__FP14NUPContextInfoPcPcUx
- `libs/RVL_SDK/src/wad/wad WADBackupEx`: tools/decomp-assist/sol-med-attempts.md:7278 WADBackupEx; tools/decomp-assist/h6.attempts.md:375 051-sd_drv-fat32-write-sector-helper; tools/decomp-assist/h6.attempts.md:443 061-wad-backup-export-buffer-wait-helper
- `libs/RVL_SDK/src/wad/wad WADImportDVDExForBS`: tools/decomp-assist/sol-med-attempts.md:7323 WADImportDVDExForBS; tools/decomp-assist/h6.attempts.md:376 051-sd_drv-fat32-write-sector-helper; tools/decomp-assist/h6.attempts.md:464 064-wad-dvd-import-section-helper
- `libs/RVL_SDK/src/wad/wad WADImportEx`: tools/decomp-assist/sol-med-attempts.md:7275 WADImportEx; tools/decomp-assist/h6.attempts.md:373 051-sd_drv-fat32-write-sector-helper; tools/decomp-assist/h6.attempts.md:401 055-wad-import-installed-content-scan
- `libs/RVL_SDK/src/wad/wad WADImportGetBlocks`: tools/decomp-assist/sol-med-attempts.md:7308 WADImportGetBlocks; tools/decomp-assist/h6.attempts.md:372 051-sd_drv-fat32-write-sector-helper; tools/decomp-assist/h6.attempts.md:380 052-wad-blocks-content-accounting-helper
- `libs/RVL_SDK/src/wad/wad WAD_815C1288`: tools/decomp-assist/sol-med-attempts.md:7290 WAD_815C1288; tools/decomp-assist/h6.attempts.md:374 051-sd_drv-fat32-write-sector-helper; tools/decomp-assist/h6.attempts.md:422 058-wad-export-buffer-wait-helper
- `libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt`: tools/decomp-assist/data-d6.attempts.md:82 file-size and data-size declaration order; tools/decomp-assist/data-d6.attempts.md:84 signed pointer tests to pointer null tests; tools/decomp-assist/data-d6.attempts.md:86 signature before hash output
- `libs/RevoEX/src/net/aes AESiDecryptBlock`: tools/decomp-assist/sol-high-four-oct2.attempts.jsonl:107 mutate inverse MixColumns intermediate terms in target operand order; tools/decomp-assist/sol-high-four-oct2.attempts.jsonl:108 retain key schedule base separately before round offset; tools/decomp-assist/sol-high-four-oct2.attempts.jsonl:109 inline inverse MixColumns column helper
- `libs/RevoEX/src/net/aes AESiEncryptBlock`: tools/decomp-assist/sol-high-four-oct2.attempts.jsonl:101 explicit target low byte XOR association with nested high-byte pair; tools/decomp-assist/sol-high-four-oct2.attempts.jsonl:102 inline encryption round lookup helper with target association; tools/decomp-assist/sol-high-four-oct2.attempts.jsonl:103 separate leading state declarations from round-count and initial key loads
- `libs/RevoEX/src/net/md5 ProcessBlock`: tools/decomp-assist/allhands-md5-rotation.attempts.md:32 direct byte-reversed pointers and arithmetic groupings; tools/decomp-assist/allhands-md5-rotation.attempts.md:34 typed inline endian-load wrapper; tools/decomp-assist/allhands-md5-rotation.attempts.md:36 rotation helpers without independent load results
- `libs/RevoEX/src/nhttp/NHTTP_recvbuf NHTTPi_compareTokenN_HdrRecvBuf`: tools/decomp-assist/partial-oct2d.attempts.md:621 positive enclosing range guard; tools/decomp-assist/partial-oct2d.attempts.md:622 word character narrows at comparison helper; tools/decomp-assist/partial-oct2d.attempts.md:623 positive guard and int character with conditional lower-case helper
- `libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL NHTTPi_compareToken`: tools/decomp-assist/allhands-nhttp-stdlib.attempts.md:64 NHTTPi_Base64Encode; tools/decomp-assist/perm2.attempts.md:196 NHTTPi_compareToken readable trials; tools/decomp-assist/pk2.attempts.md:198 mwcceppc.exe Compiler:
- `libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL NHTTPi_strnicmp`: tools/decomp-assist/four-leaves-r11.attempts.md:51 constant-first lower bound; tools/decomp-assist/four-leaves-r11.attempts.md:52 constant-first upper bound; tools/decomp-assist/four-leaves-r11.attempts.md:53 both bounds constant-first
- `libs/RevoEX/src/nwc24/NWC24Download NWC24InitDlTask`: tools/decomp-assist/ult3.attempts.md:215 home-directory char buffer uses empty string initialization; tools/decomp-assist/ult3.attempts.md:216 home-directory represented as bytes until NAND and numeric parse interfaces; tools/decomp-assist/ult3.attempts.md:217 task pointer and download type are immutable formal values
- `libs/RevoEX/src/so/SOBasic SOGetSockName`: tools/decomp-assist/prior1.attempts.md:185 mwcceppc.exe Compiler:; tools/decomp-assist/prior1.attempts.md:187 S1 reference statement order and conclude goto, with typed wire fields; tools/decomp-assist/prior1.attempts.md:193 S2 reference address initialization and separate prepare assignment
- `src/BS2/BS2Mach BS2StartGCGame`: tools/decomp-assist/sol-med-attempts.md:7191 BS2StartGCGame; tools/decomp-assist/fz1.attempts.md:3751 proven asynchronous DVD state field polled inline; tools/decomp-assist/fz1.attempts.md:3752 readonly native DVD polling helper boundary
- `src/BS2/BS2Mach BS2StartGame`: tools/decomp-assist/sol-med-attempts.md:7190 BS2StartGame; tools/decomp-assist/fz1.attempts.md:3728 proven async flags volatile definitions and direct state polling; tools/decomp-assist/fz1.attempts.md:3729 polling through native readonly inline DVD accessor
- `src/BS2/BS2Mach BS2Tick`: tools/decomp-assist/sol-med-attempts.md:7181 BS2Tick; tools/decomp-assist/fz1.attempts.md:3776 loader outputs represented as three independent addressable locals; tools/decomp-assist/fz1.attempts.md:3777 disc header hardware fields accessed through actual readonly disk type
- `src/BS2/BS2Mach CheckBS2CommandStatus`: tools/decomp-assist/sol-med-attempts.md:7187 CheckBS2CommandStatus; tools/decomp-assist/fz1.attempts.md:3762 NAND pending stored before inline partition-size arithmetic; tools/decomp-assist/fz1.attempts.md:3763 partition count read through real constant TOC view
- `src/BS2/BS2Update UpdateThread`: tools/decomp-assist/a6x.attempts.md:20 copy selected seat helper returns immutable source for requirements; tools/decomp-assist/a6x.attempts.md:21 seat copy helper returns required bytes and accumulates inode requirements; tools/decomp-assist/a6x.attempts.md:22 seat copy helper accumulates bytes and returns inode requirement
- `src/channelScript/CHANSVm CHANSVmConvertToFloatFromStr`: tools/decomp-assist/fz1.attempts.md:3626 read-only parse input object; tools/decomp-assist/fz1.attempts.md:3627 const parsed string view inside parse helper; tools/decomp-assist/fz1.attempts.md:3628 nested result/null parse condition
- `src/channelScript/CHANSVm CHANSVmFormatString`: tools/decomp-assist/fz1.attempts.md:3655 actual UTF16 character data instead of misleading pad name; tools/decomp-assist/fz1.attempts.md:3656 read-only format input bytes; tools/decomp-assist/fz1.attempts.md:3657 format cleanup length native signed count
- `src/channelScript/CHANSVm CHANSVmStep`: tools/decomp-assist/fz1.attempts.md:3713 default step count explicit branch; tools/decomp-assist/fz1.attempts.md:3714 step loop has precondition and post decrement; tools/decomp-assist/fz1.attempts.md:3715 step count and top tested loop use positive bound
- `src/channelScript/CHANSVm VmBlobGetHexString`: tools/decomp-assist/fz1.attempts.md:3662 read-only byte/hex table input views; tools/decomp-assist/fz1.attempts.md:3663 two destination slots owned by a single character cursor; tools/decomp-assist/fz1.attempts.md:3664 hex output as pointer cursor
- `src/channelScript/CHANSVm VmBlobPackCommon`: tools/decomp-assist/fz1.attempts.md:3673 boolean packing-mode parameter; tools/decomp-assist/fz1.attempts.md:3674 source blobs and string bytes readonly during copy; tools/decomp-assist/fz1.attempts.md:3675 native signed format length
- `src/channelScript/CHANSVm VmBlobUnpack`: tools/decomp-assist/fz1.attempts.md:3681 format string readonly pointer and getter cast; tools/decomp-assist/fz1.attempts.md:3682 packing parser signed counts explicitly decoded from unsigned field; tools/decomp-assist/fz1.attempts.md:3683 native signed inner iteration index
- `src/channelScript/CHANSVm VmDateDtor`: tools/decomp-assist/fz1.attempts.md:3635 read-only calendar view for format arguments; tools/decomp-assist/fz1.attempts.md:3636 month value computed before weekday in format call; tools/decomp-assist/fz1.attempts.md:3637 month then weekday genuine names
- `src/channelScript/CHANSVm VmStringSplit`: tools/decomp-assist/fz1.attempts.md:3648 read-only source and delimiter byte pointers; tools/decomp-assist/fz1.attempts.md:3649 delimiter payload before parent payload addressing; tools/decomp-assist/fz1.attempts.md:3650 two-pass output uses do loop
- `src/channelScript/CHANSVm VmWinEmuWrite`: tools/decomp-assist/fz1.attempts.md:3689 conversion object readonly binding; tools/decomp-assist/fz1.attempts.md:3690 constant string payload cached separately; tools/decomp-assist/fz1.attempts.md:3691 length loop checked before offset initialization
- `src/iplwww/www_wiisetting Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue`: tools/decomp-assist/a6x.attempts.md:14 append helper owns index increment through int reference; tools/decomp-assist/a6x.attempts.md:15 mask helper returns final reloaded buffer and publishes length by reference; tools/decomp-assist/a6x.attempts.md:16 entire region and language selection owns reference country result in helper
- `src/keyboard/tiCandidateBox createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator`: tools/decomp-assist/a23h.attempts.md:85 animation reference refers directly to the real record; tools/decomp-assist/a23h.attempts.md:86 animation slot cursor advances once per resource; tools/decomp-assist/a23h.attempts.md:87 signed local count preserves bounded descriptor traversal
- `src/keyboard/tiCandidateBox create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator`: tools/decomp-assist/a23h.attempts.md:71 text-area setup helper subobject reference and layout pointer; tools/decomp-assist/a23h.attempts.md:72 text-area setup helper subobject pointer and caller pointer reference; tools/decomp-assist/a23h.attempts.md:73 text-area setup helper subobject and layout references
- `src/keyboard/tiCellPhone create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator`: tools/decomp-assist/a23h.attempts.md:134 toggle animation helper layout first; tools/decomp-assist/a23h.attempts.md:135 toggle animation helper descriptor first; tools/decomp-assist/a23h.attempts.md:136 toggle animation helper references to live pane and resource objects
- `src/keyboard/tiInputForm calcCursorPos__Q39textinput9inputform4BaseFff`: tools/decomp-assist/a23h.attempts.md:33 scaled height compound accumulator; tools/decomp-assist/a23h.attempts.md:34 glyph width computed through a const scalar pair; tools/decomp-assist/a23h.attempts.md:35 scaled cursor bounds output references isolate two calculations
- `src/keyboard/tiInputForm create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer`: tools/decomp-assist/a23h.attempts.md:79 textbox metrics preserve complete font-size value; tools/decomp-assist/a23h.attempts.md:80 animation descriptor is a const record reference; tools/decomp-assist/a23h.attempts.md:126 row activation helper receives real row storage and capacity
- `src/keyboard/tiSignWindow create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator`: tools/decomp-assist/a23h.attempts.md:92 animation reference refers directly to the real record; tools/decomp-assist/a23h.attempts.md:93 animation slot cursor advances once per resource; tools/decomp-assist/a23h.attempts.md:94 signed local count preserves bounded descriptor traversal
- `src/keyboard/tiString inputChar__Q39textinput8tistring9DecolatedFw`: tools/decomp-assist/a23h.attempts.md:52 builder append returns current length after postincrement; tools/decomp-assist/a23h.attempts.md:53 newline append and ordinary append use distinct real cursor operations; tools/decomp-assist/a23h.attempts.md:54 literal converter uses builder count reference with explicit newline terminator
- `src/keyboard/tiZiString clearCandidates__Q39textinput8tistring6WithZiFv`: tools/decomp-assist/a23h.attempts.md:40 candidate buffer storage uses three proven typed ranges; tools/decomp-assist/a23h.attempts.md:41 three-range storage with input array-reference lifetime; tools/decomp-assist/a23h.attempts.md:43 separate named subrange pointers at reset boundary
- `src/keyboard/tiZiString setElementBuffer__Q39textinput8tistring6WithZiFv`: tools/decomp-assist/a23h.attempts.md:40 candidate buffer storage uses three proven typed ranges; tools/decomp-assist/a23h.attempts.md:41 three-range storage with input array-reference lifetime; tools/decomp-assist/a23h.attempts.md:43 separate named subrange pointers at reset boundary
- `src/keyboard/tiZiString update__Q39textinput8tistring6WithZiFv`: tools/decomp-assist/a23h.attempts.md:40 candidate buffer storage uses three proven typed ranges; tools/decomp-assist/a23h.attempts.md:41 three-range storage with input array-reference lifetime; tools/decomp-assist/a23h.attempts.md:43 separate named subrange pointers at reset boundary
- `src/scene/address/iplAddress onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface`: tools/decomp-assist/a23h.attempts.md:102 event dispatch pane component helper boundary; tools/decomp-assist/a23h.attempts.md:103 event dispatch separate scene-base receiver; tools/decomp-assist/a23h.attempts.md:104 event dispatch scoped event kind and immutable mail receiver
- `src/scene/address/iplAddress start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface`: tools/decomp-assist/a23h.attempts.md:99 drag texture helper const object and pane references; tools/decomp-assist/a23h.attempts.md:100 drag texture helper const input pointer references; tools/decomp-assist/a23h.attempts.md:101 drag texture helper destination-first pointer arguments
- `src/scene/address/iplAddressEdit create__Q33ipl5scene11AddressEditFv`: tools/decomp-assist/a23h.attempts.md:109 address create typed balloon margins; tools/decomp-assist/a23h.attempts.md:110 address create const friend-string receiver; tools/decomp-assist/a23h.attempts.md:111 address create inline aspect-ratio margin selector
- `src/scene/address/iplAddressEdit get_friendinfo__Q33ipl5scene11AddressEditFv`: tools/decomp-assist/a23h.attempts.md:27 member string getter with explicit nullable receiver; tools/decomp-assist/a23h.attempts.md:28 typed member-array getter retains array dimensions; tools/decomp-assist/a23h.attempts.md:56 layout pane wrapper with correct one-name signature
- `src/scene/address/iplAddressEdit update_friendinfo__Q33ipl5scene11AddressEditFv`: tools/decomp-assist/a23h.attempts.md:112 friend name copy explicit array element and size type; tools/decomp-assist/a23h.attempts.md:113 friend name copy bounded array helper; tools/decomp-assist/a23h.attempts.md:114 friend name copy separate string and name receivers
- `src/scene/cardSequence/iplCardSequence cardThreadMain`: tools/decomp-assist/gk3.attempts.md:89 native OSMessage receive/storage matching exact probeCard: 301/301 instructions; structural/exact (2, 78); pool identical; exact regressions []; reverted.; tools/decomp-assist/gk3.attempts.md:90 queue local before union field assembly matching exact sendCardSlotState: 301/301 instructions; structural/exact (2, 78); pool identical; exact regressions []; reverted.; tools/decomp-assist/gk3.attempts.md:91 signed do/while mounted-file scan following exact clearAllCardFileEntries: 301/301 instructions; structural/exact (2, 78); pool identical; exact regressions []; reverted.
- `src/scene/cardSequence/iplCardSequence loadCardFileIcons`: tools/decomp-assist/gk3.attempts.md:99 const CARDDir input matching read-only icon metadata view: 505/512 instructions; structural/exact (103, 431); pool identical; exact regressions []; reverted.; tools/decomp-assist/gk3.attempts.md:100 native unsigned sector size outputs matching exact refreshCardSlotInfo: 508/512 instructions; structural/exact (66, 436); pool identical; exact regressions []; reverted.; tools/decomp-assist/gk3.attempts.md:101 signed do/while animation speed scan matching clearAllCardFileEntries: 509/512 instructions; structural/exact (71, 423); pool identical; exact regressions []; reverted.
- `src/scene/cardSequence/iplCardSequence runCardMoveOrCopy`: tools/decomp-assist/gk3.attempts.md:107 inline common-sector helper with reference outputs and exact sibling error returns: 608/608 instructions; structural/exact (12, 185); pool identical; exact regressions []; reverted.; tools/decomp-assist/gk3.attempts.md:108 scoped permission result matching exact status-helper local lifetime: 608/608 instructions; structural/exact (12, 176); pool identical; exact regressions []; reverted.; tools/decomp-assist/gk3.attempts.md:109 explicit block count guard following exact sibling native loop locals: 609/608 instructions; structural/exact (24, 498); pool identical; exact regressions []; reverted.
- `src/scene/memoryCard/iplMemoryCardManager _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl`: tools/decomp-assist/ult15.attempts.md:239 const directory and icon metadata views at GX boundaries; tools/decomp-assist/ult15.attempts.md:241 render metadata as mutable typed reference; tools/decomp-assist/ult15.attempts.md:243 linear icon records using actual slot stride and typed field access
- `src/scene/memoryCard/iplMemoryCardManager create_banner__Q33ipl5scene17MemoryCardManagerFUcs`: tools/decomp-assist/ult15.attempts.md:247 const directory and icon metadata views at GX boundaries; tools/decomp-assist/ult15.attempts.md:249 render metadata as mutable typed reference; tools/decomp-assist/ult15.attempts.md:251 linear icon records using actual slot stride and typed field access
- `src/scene/memoryCard/iplMemoryCardManager getBlocks__Q33ipl5scene17MemoryCardManagerFUcs`: tools/decomp-assist/ult22.attempts.md:18 return through signed index parameter after metadata lookup; tools/decomp-assist/ult22.attempts.md:19 single exit after readonly manager selection scope; tools/decomp-assist/ult22.attempts.md:20 metadata value output reference at inline helper boundary
- `src/scene/memoryCard/iplMemoryCardManager getComment__Q33ipl5scene17MemoryCardManagerFUcsi`: tools/decomp-assist/ult22.attempts.md:54 encoded scratch is unsigned byte array with matching trim cursor types; tools/decomp-assist/ult22.attempts.md:55 narrow trailing trim owns scoped read and write cursor declarations; tools/decomp-assist/ult22.attempts.md:56 comment terminator has named character-code type
- `src/scene/memoryCard/iplMemoryCardManager isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs`: tools/decomp-assist/ult22.attempts.md:14 return through byte parameter after metadata lookup; tools/decomp-assist/ult22.attempts.md:15 single exit after readonly manager selection scope; tools/decomp-assist/ult22.attempts.md:16 metadata value output reference at inline helper boundary
- `src/scene/memoryCard/iplMemoryCardManager isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl`: tools/decomp-assist/ult22.attempts.md:34 commuted built-in subscript preserves file-first source operands; tools/decomp-assist/ult22.attempts.md:35 flat typed directory uses shared slot/file element offset; tools/decomp-assist/ult22.attempts.md:36 typed inline directory selector takes file before slot
- `src/scene/memoryCard/iplMemoryCardManager isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl`: tools/decomp-assist/ult22.attempts.md:28 commuted built-in subscript preserves file-first source operands; tools/decomp-assist/ult22.attempts.md:29 flat typed directory uses shared slot/file element offset; tools/decomp-assist/ult22.attempts.md:30 typed inline directory selector takes file before slot
- `src/scene/sdChannelMemory/iplSDMemory create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect`: tools/decomp-assist/a6x.attempts.md:41 entire initial dialog construction and message setup owns helper temporaries; tools/decomp-assist/a6x.attempts.md:42 initial dialog factory receives immutable heap and layout-file bindings; tools/decomp-assist/a6x.attempts.md:43 cached-title scan uses helper with const savedata object reference
- `src/scene/sdChannelMemory/iplSDMemory drawTransferTitles__Q33ipl5scene8SDMemoryFv`: tools/decomp-assist/a6x.attempts.md:26 only body child-alpha traversal uses value-parameter static inline helper; tools/decomp-assist/a6x.attempts.md:28 message splitting and drawing loop owns line temporaries in inline helper; tools/decomp-assist/a6x.attempts.md:32 body alpha helper returns inherited alpha from const source pane
- `src/scene/sdChannelSelect/iplSDChannelSelect collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl`: tools/decomp-assist/a23h.attempts.md:64 paired usage local stores blocks then bytes; tools/decomp-assist/a23h.attempts.md:65 paired usage member predicate owns threshold reads; tools/decomp-assist/a23h.attempts.md:66 append count and compare through real usage pointers
- `src/scene/sdChannelSelect/iplSDChannelSelect collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl`: tools/decomp-assist/a23h.attempts.md:64 paired usage local stores blocks then bytes; tools/decomp-assist/a23h.attempts.md:65 paired usage member predicate owns threshold reads; tools/decomp-assist/a23h.attempts.md:66 append count and compare through real usage pointers
- `src/scene/sdChannelSelect/iplSDChannelSelect collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl`: tools/decomp-assist/a23h.attempts.md:64 paired usage local stores blocks then bytes; tools/decomp-assist/a23h.attempts.md:65 paired usage member predicate owns threshold reads; tools/decomp-assist/a23h.attempts.md:66 append count and compare through real usage pointers
- `src/scene/sdChannelSelect/iplSDChannelSelect collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl`: tools/decomp-assist/a23h.attempts.md:64 paired usage local stores blocks then bytes; tools/decomp-assist/a23h.attempts.md:65 paired usage member predicate owns threshold reads; tools/decomp-assist/a23h.attempts.md:66 append count and compare through real usage pointers
- `src/scene/sdChannelSelect/iplSDChannelSelect create__Q33ipl5scene15SDChannelSelectFv`: tools/decomp-assist/a23h.attempts.md:64 paired usage local stores blocks then bytes; tools/decomp-assist/a23h.attempts.md:65 paired usage member predicate owns threshold reads; tools/decomp-assist/a23h.attempts.md:66 append count and compare through real usage pointers
- `src/scene/sdChannelSelect/iplSDChannelSelect flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv`: tools/decomp-assist/a23h.attempts.md:64 paired usage local stores blocks then bytes; tools/decomp-assist/a23h.attempts.md:65 paired usage member predicate owns threshold reads; tools/decomp-assist/a23h.attempts.md:66 append count and compare through real usage pointers
- `src/scene/sdChannelTitle/iplSDChannelTitle iplSDChannelTitle_flushSaveBeforeExit`: tools/decomp-assist/a6x.attempts.md:53 queued-file publication and reconnect own output-reference helper; tools/decomp-assist/a6x.attempts.md:54 concrete save request submits through const member with heap and manager fields; tools/decomp-assist/a6x.attempts.md:55 heap query returns heap and publishes loaded savedata manager
- `src/scene/setting/iplSetting scanAP__Q33ipl5scene7SettingFv`: tools/decomp-assist/a6x.attempts.md:35 whole state-9 completion transaction moved into inline member; tools/decomp-assist/a6x.attempts.md:36 state-9 static inline query owns BOOL output and referenced index/layout inputs; tools/decomp-assist/a6x.attempts.md:37 const member publishes current animation index and returns layout
- `src/system/iplKeyboard create__Q33ipl8keyboard7ManagerFPQ33ipl4nand4FilePQ23EGG4Heap`: tools/decomp-assist/a6x.attempts.md:71 layout allocator installation returns owned allocator through inline factory; tools/decomp-assist/a6x.attempts.md:72 destination switch owns reloadable MemoManager reference boundary; tools/decomp-assist/a6x.attempts.md:73 three MemoSetting assignments retain their order inside inline output transaction
- `src/system/odh LineConv11__9CArGBAOdhFPUcPUcPUcPUcUsUsPCli`: tools/decomp-assist/a6x.attempts.md:59 RGB565 helper returns meaningful three-component RGB5 aggregate; tools/decomp-assist/a6x.attempts.md:60 RGB565 tile-address helper reads source and index through const references; tools/decomp-assist/a6x.attempts.md:61 video sample conversion and pedestal subtraction own static inline boundary
- `src/system/odh huffmanDecoder__9CArGBAOdhFPUlP21SArCDJ_HuffmanRequestPPUsiUl`: tools/decomp-assist/a6x.attempts.md:65 DC Huffman walk publishes leaf category by reference and returns consumed depth; tools/decomp-assist/a6x.attempts.md:66 DC and AC magnitude tree walks share the same bounded inline helper; tools/decomp-assist/a6x.attempts.md:67 post-DC byte alignment updates the meaningful cursor state through inline references
- `src/utility/iplESMisc DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap`: tools/decomp-assist/a6x.attempts.md:47 both three-slot save-name validation loops share pure inline result helper; tools/decomp-assist/a6x.attempts.md:48 single save-slot validation owns six short-circuit name checks; tools/decomp-assist/a6x.attempts.md:49 zeroing and read helper retains allocated buffer through const reference

ATTEMPT {"build": 0, "functions": [{"diffs": 0, "insns": [81, 81], "name": "clearCandidates__Q39textinput8tistring6WithZiFv", "percent": 100.0}, {"diffs": 126, "insns": [446, 446], "name": "update__Q39textinput8tistring6WithZiFv", "percent": 98.3139}, {"diffs": 0, "insns": [65, 65], "name": "setElementBuffer__Q39textinput8tistring6WithZiFv", "percent": 100.0}], "gained": ["clearCandidates__Q39textinput8tistring6WithZiFv", "setElementBuffer__Q39textinput8tistring6WithZiFv"], "label": "both word copy helpers own independent input and result row cursors", "lost": [], "measures": {"fuzzy_match_percent": 99.45349, "matched_code": "3720", "matched_code_percent": 67.58721, "matched_data": "7680", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "5504", "total_data": "7680", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "bc0131073a6b", "trial": 32, "unit": "src/keyboard/tiZiString"}

ATTEMPT {"build": 0, "functions": [{"diffs": 58, "insns": [185, 185], "name": "KPADInit", "percent": 97.810814}], "gained": [], "label": "preserve the full 64-byte rotation object as its natural four-by-four matrix type", "lost": [], "measures": {"fuzzy_match_percent": 99.875916, "matched_code": "12316", "matched_code_percent": 94.33211, "matched_data": "8032", "matched_data_percent": 100.0, "matched_functions": 28, "matched_functions_percent": 96.55172, "total_code": "13056", "total_data": "8032", "total_functions": 29, "total_units": 1}, "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "pool_ok": true, "source_hash": "3c6a31371288", "trial": 33, "unit": "libs/RVL_SDK/src/kpad/KPAD"}

## Disposition of the other global-address candidates

- CHANSVm: scUndefinedUtf16 is a compiler-used anchor for separately declared UTF16 strings and date-name tables. No wrapper combines those objects. VmDateDtor's seven differences are ordering of weekday/month argument preparation, not missing object boundaries. The other open functions use separate scalar constants, function/jump tables or register-only loops.
- BS2Mach: Block, DiskID, TicketViews and loader state already have separate declarations. The shared data anchor covers ordinary diagnostic literals. The two startup prologues and CheckBS2CommandStatus have scheduling differences; BS2Tick also has hardware-address and callback scheduling differences. No mixed source global remains to split.
- BS2Update: Flags0/Flags1, thread/stack and the two update headers already have separate globals. The 0x500 lbl_81646978 region is a literal pool. No source struct wraps these objects.
- iplKeyboard: two separate language tables contain repeated EZTXLanguageEntry records and terminators. No row straddles another global. iplSDMemory's large unnamed regions are string pools, with separate save/system state owned elsewhere.
- iplCardSequence: sThread is a pointer to one allocated CardThreadState, not an inferred static aggregate. iplMemoryCardManager's seven open functions do not reference global objects. They cannot use lever 13 without changing a different ownership model.
- iplAddress/iplAddressEdit: system and sound globals are outside this leaf. The local 0x140 sFriendInfo is passed to whole-object memset/memcpy and typed NWC24 APIs, so its fields do not prove separate globals. The two-instruction update_friendinfo difference exchanges preparation of a local name and the friend-name address.
- iplSDChannelSelect/iplSDChannelTitle: relevant global references are to the existing System::Arg; their collector/flush differences concern pointer reload order or local indexing, not owned object boundaries. iplSetting::scanAP reads only this object's fields at its four remaining differences. iplESMisc references a diagnostic literal, and odh references scalar floating constants.
- tiCellPhone/tiInputForm/tiSignWindow: pane/animation/language data are indexed arrays of uniform records. Their register allocation differs inside record consumers, but no interleaved independently addressed object is present. tiString has no global-object relocation in its open function.
- www_wiisetting: keyboard-language LUTs are independent homogeneous tables. The near match differs in the saved pointer/index registers for masked values and the European table; the tables do not contain unrelated state. sWiiData is already an independent typed object.
- NHTTP_recvbuf/NHTTP_stdlib_RVL/SOBasic: open functions have no global data references. Other requested NHTTP units are already exact. NWC24InitDlTask refers to the existing NWC24WorkP pointer and a literal; no owned aggregate is implicated.
- CDBRecordEncrypt references an error literal. Its two 0x40 crypt buffers are already independent globals. AES has separate encryption/decryption and substitution tables. MD5 has separate 64-word constant and 48-word index tables and advances their cursors across the relevant rounds.
- JPEG IDCT/exif functions have no global-object relocations; converter selection functions reference function addresses, and open pixel converters read caller-owned buffers. iqdec uses two separate Zigzag lookup arrays, not a merged object. No eligible boundary was found.
- lyt_window: flipInfos is a repeated TextureFlipInfo array. SDK pdm_partition's open function has no global-object references; the RevoEX copy is exact.
- sd_drv: g_pfd_sddrv_info is a typed state object; g_pfd_sddev is a 0x40 storage union around the 0x28 SDDev. No access identifies a second object in the trailing 0x18 bytes, so no split or metadata shrink is justified. The sector buffer and size-dependence table are already separate globals. The RevoEX driver copy is exact.
- nup: remaining differences use caller-owned title/context data and literal/scalar references. No large owned global is implicated.
- kbd_lib: kbdData is indexed at the target 0x268 stride for four channels. Command and callback arrays are already separate. The key-map storage is uniform; no reference proves a new boundary. The LED callback's remaining branch direction has no global-layout cause.
- KPAD: initial_rotation_matrix has no target use of the last 0x10 bytes or relocation naming another object there. A natural Mtx44 representation preserves all data but leaves KPADInit at 185/185 and 58 differences. Restored. No speculative object or alignment was added.

The scan checked every open function's address-forming instruction differences and referenced objects. Most apparent large-object hits were jump tables, function symbols, literal pools or real repeated arrays. Only tiZiString supplied a productive, provable split. tiCandidateBox's real table/string separation compiled in three forms without an exact gain; all were restored.

## Remaining tiZiString work

After the split, update has 446/446 instructions and 85 differences at 98.36996%. Trials 18-32 cover distinct search, context, input-copy, output-view, row-array and word-copy boundaries. The best context helper plus result-first const cursor reached 99.524666% and 33 differences, still not exact. It exchanges saved zero/one registers and final input/output/index registers, plus the two phone-output increment instructions. All fuzzy-only update helpers, the row-array experiment, and unrelated type experiments were restored. Only the two exact matches remain.

## Final clean validation

Full non-quick gate across all 51 audited units, baseline 38cb84c8, exited 0. Log: /tmp/agg-sweep/final.full-gate.txt. The gate removed and rebuilt build/43U. Fresh progress/report/ok Ninja targets passed afterward.
No unit other than tiZiString changed any report measure. All 1027 unit data totals stayed unchanged. No regressions, forbidden additions or readability warnings.
Reference-object proof rerun after the clean build: 1027 objects, 109496 resolved relocations, changed: []. Every allocated section retains its type, size and bytes; every relocation retains its source position/type and resolved destination section + value + addend.
clearCandidates: 81/81 instructions, diffs 0, exact-name objdiff 100.0%. setElementBuffer: 65/65 instructions, diffs 0, exact-name objdiff 100.0%.
DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d.
Fresh decomp_status output: /tmp/agg-sweep/final.status.json and /tmp/agg-sweep/final.status.md. The terminal project completion checker still returns DECOMPLETE_FAIL: overall code exact 2773328/2995176, linked 2282392/2995176, data exact 1831712/1832684, linked 1542216/1832684. This matching-only sweep does not claim project or unit completion.

Final gate excerpts (verbatim):

```
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3720/5504 data 7680/7680 functions 28/29 fuzzy 99.4717 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 28/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 99.47166
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 98.36996
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 98.3241
regressions vs baseline: 0
global matched_code_percent: 92.57366 -> 92.59315
global fuzzy_match_percent: 99.73627 -> 99.73837
global complete_code_percent: 76.20227 -> 76.20227
global matched_data_percent: 99.94696 -> 99.94696
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

### Every audited unit: before -> after

| Unit | Instruction-exact functions | Exact code bytes | Exact data bytes |
| --- | --- | --- | --- |
| src/system/iplKeyboard | 31 -> 31 / 32 | 4752 -> 4752 / 6024 | 1184 -> 1184 / 1184 |
| src/system/odh | 26 -> 26 / 28 | 12876 -> 12876 / 14684 | 6360 -> 6360 / 6360 |
| src/utility/iplESMisc | 30 -> 30 / 31 | 9404 -> 9404 / 11200 | 4416 -> 4416 / 4416 |
| src/iplwww/www_wiisetting | 20 -> 20 / 21 | 3740 -> 3740 / 6176 | 3856 -> 3856 / 3856 |
| src/BS2/BS2Mach | 25 -> 25 / 29 | 5112 -> 5112 / 16980 | 158528 -> 158528 / 158528 |
| src/BS2/BS2Update | 9 -> 9 / 10 | 400 -> 400 / 4052 | 10488 -> 10488 / 10488 |
| src/scene/address/iplAddress | 98 -> 98 / 101 | 22016 -> 22016 / 23988 | 1964 -> 1964 / 1964 |
| src/scene/address/iplAddressEdit | 91 -> 91 / 94 | 23344 -> 23344 / 27112 | 2560 -> 2560 / 2560 |
| src/scene/memoryCard/iplMemoryCardManager | 19 -> 19 / 26 | 2932 -> 2932 / 5396 | 0 -> 0 / 0 |
| src/scene/cardSequence/iplCardSequence | 27 -> 27 / 30 | 4168 -> 4168 / 9852 | 1496 -> 1496 / 1496 |
| src/scene/sdChannelSelect/iplSDChannelSelect | 123 -> 123 / 129 | 30344 -> 30344 / 33828 | 2960 -> 2960 / 2960 |
| src/scene/sdChannelTitle/iplSDChannelTitle | 68 -> 68 / 69 | 18476 -> 18476 / 18624 | 1976 -> 1976 / 1976 |
| src/scene/sdChannelMemory/iplSDMemory | 63 -> 63 / 66 | 14812 -> 14812 / 20872 | 3344 -> 3344 / 3344 |
| src/scene/setting/iplSetting | 110 -> 110 / 112 | 36796 -> 36796 / 37884 | 5696 -> 5696 / 5696 |
| src/keyboard/tiCellPhone | 85 -> 85 / 86 | 17696 -> 17696 / 19028 | 3860 -> 3860 / 3860 |
| src/keyboard/tiInputForm | 217 -> 217 / 221 | 47928 -> 47928 / 50656 | 3772 -> 3772 / 3772 |
| src/keyboard/tiCandidateBox | 109 -> 109 / 112 | 21728 -> 21728 / 24000 | 4652 -> 4652 / 4652 |
| src/keyboard/tiSignWindow | 55 -> 55 / 56 | 6300 -> 6300 / 7184 | 3468 -> 3468 / 3468 |
| src/keyboard/tiString | 41 -> 41 / 42 | 4632 -> 4632 / 5176 | 288 -> 288 / 288 |
| src/keyboard/tiZiString | 26 -> 28 / 29 | 3136 -> 3720 / 5504 | 7680 -> 7680 / 7680 |
| src/channelScript/CHANSVm | 224 -> 224 / 233 | 39908 -> 39908 / 53564 | 6904 -> 6904 / 6904 |
| libs/RevoEX/src/cdb/CDBRecord | 28 -> 28 / 29 | 5940 -> 5940 / 7076 | 2640 -> 2640 / 2640 |
| libs/RevoEX/src/net/md5 | 3 -> 3 / 4 | 600 -> 600 / 1824 | 456 -> 456 / 456 |
| libs/RevoEX/src/net/aes | 7 -> 7 / 9 | 1116 -> 1116 / 2752 | 2800 -> 2800 / 2800 |
| libs/RevoEX/src/nhttp/NHTTP_bgnend | 9 -> 9 / 9 | 880 -> 880 / 880 | 136 -> 136 / 136 |
| libs/RevoEX/src/nhttp/NHTTP_control | 3 -> 3 / 3 | 420 -> 420 / 420 | 32 -> 32 / 32 |
| libs/RevoEX/src/nhttp/NHTTP_list | 5 -> 5 / 5 | 592 -> 592 / 592 | 0 -> 0 / 0 |
| libs/RevoEX/src/nhttp/NHTTP_os_RVL | 11 -> 11 / 11 | 548 -> 548 / 548 | 72 -> 72 / 72 |
| libs/RevoEX/src/nhttp/NHTTP_recvbuf | 6 -> 6 / 7 | 1196 -> 1196 / 1692 | 0 -> 0 / 0 |
| libs/RevoEX/src/nhttp/NHTTP_request | 7 -> 7 / 7 | 2512 -> 2512 / 2512 | 48 -> 48 / 48 |
| libs/RevoEX/src/nhttp/NHTTP_response | 4 -> 4 / 4 | 1044 -> 1044 / 1044 | 16 -> 16 / 16 |
| libs/RevoEX/src/nhttp/NHTTP_socket_RVL | 10 -> 10 / 10 | 2140 -> 2140 / 2140 | 0 -> 0 / 0 |
| libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL | 12 -> 12 / 14 | 1864 -> 1864 / 2248 | 112 -> 112 / 112 |
| libs/RevoEX/src/nhttp/NHTTP_thread | 26 -> 26 / 26 | 11292 -> 11292 / 11292 | 504 -> 504 / 504 |
| libs/RevoEX/src/nwc24/NWC24Download | 29 -> 29 / 30 | 11920 -> 11920 / 12496 | 80 -> 80 / 80 |
| libs/RevoEX/src/so/SOBasic | 21 -> 21 / 22 | 3836 -> 3836 / 4088 | 144 -> 144 / 144 |
| libs/RevoEX/src/vf/dskmng/pdm_partition | 19 -> 19 / 19 | 6108 -> 6108 / 6108 | 0 -> 0 / 0 |
| libs/RevoEX/src/vf/develop/sd_drv | 16 -> 16 / 16 | 3608 -> 3608 / 3608 | 992 -> 992 / 992 |
| libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var | 0 -> 0 / 2 | 0 -> 0 / 2844 | 0 -> 0 / 0 |
| libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse | 3 -> 3 / 6 | 1348 -> 1348 / 5088 | 0 -> 0 / 0 |
| libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8 | 2 -> 2 / 13 | 15164 -> 15164 / 15948 | 0 -> 0 / 0 |
| libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 | 7 -> 7 / 13 | 2648 -> 2648 / 6184 | 0 -> 0 / 0 |
| libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 | 2 -> 2 / 13 | 660 -> 660 / 6596 | 0 -> 0 / 0 |
| libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 | 0 -> 0 / 1 | 0 -> 0 / 1104 | 0 -> 0 / 0 |
| libs/NW4R/src/lyt/lyt_window | 20 -> 20 / 21 | 9848 -> 9848 / 11352 | 316 -> 316 / 316 |
| libs/RVL_SDK/src/kpad/KPAD | 28 -> 28 / 29 | 12316 -> 12316 / 13056 | 8032 -> 8032 / 8032 |
| libs/RVL_SDK/src/wad/wad | 35 -> 35 / 40 | 13180 -> 13180 / 24500 | 528 -> 528 / 528 |
| libs/RVL_SDK/src/fa/pdm_partition | 19 -> 19 / 20 | 3380 -> 3380 / 3716 | 0 -> 0 / 0 |
| libs/RVL_SDK/src/fa/driver/sd_drv | 22 -> 22 / 26 | 9260 -> 9260 / 11760 | 3592 -> 3592 / 3592 |
| libs/RVL_SDK/src/nup/nup | 20 -> 20 / 23 | 7748 -> 7748 / 10764 | 1720 -> 1720 / 1720 |
| libs/RVL_SDK/src/kbd/kbd_lib | 17 -> 17 / 21 | 3728 -> 3728 / 5764 | 5296 -> 5296 / 5296 |

### Fresh open-function list and attempt coverage

104 functions remain below 100% in these units. Every entry has at least three distinct prior compiled source attempts cited above; those historical attempts were not rerun or counted as new sweep trials. The current sweep added 33 compiled trials, retained two exact functions, and restored all other source experiments. The audit and disposition sections record why a new object split is unsupported for the other units.

- `src/system/iplKeyboard create__Q33ipl8keyboard7ManagerFPQ33ipl4nand4FilePQ23EGG4Heap`: 94.00944%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/system/odh LineConv11__9CArGBAOdhFPUcPUcPUcPUcUsUsPCli`: 98.08219%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/system/odh huffmanDecoder__9CArGBAOdhFPUlP21SArCDJ_HuffmanRequestPPUsiUl`: 95.57189%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/utility/iplESMisc DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap`: 99.14254%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/iplwww/www_wiisetting Getter___Q23www10wiisettingFP14WWWJSPluginObjPCcP16WWWJSPluginValue`: 99.86043%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/BS2/BS2Mach BS2StartGame`: 98.72774%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/BS2/BS2Mach BS2StartGCGame`: 97.82895%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/BS2/BS2Mach CheckBS2CommandStatus`: 99.50739%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/BS2/BS2Mach BS2Tick`: 98.799484%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/BS2/BS2Update UpdateThread`: 94.83023%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/address/iplAddress start_drag_event__Q33ipl5scene7AddressFPCcPCQ33ipl10controller9Interface`: 99.84305%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/address/iplAddress onEventDerived__Q33ipl5scene7AddressFUlUlPCQ33ipl10controller9Interface`: 98.42593%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/address/iplAddressEdit create__Q33ipl5scene11AddressEditFv`: 97.5561%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/address/iplAddressEdit get_friendinfo__Q33ipl5scene11AddressEditFv`: 88.03571%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/address/iplAddressEdit update_friendinfo__Q33ipl5scene11AddressEditFv`: 99.42105%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/memoryCard/iplMemoryCardManager isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl`: 99.830505%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/memoryCard/iplMemoryCardManager isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl`: 99.830505%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/memoryCard/iplMemoryCardManager isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs`: 92.30769%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/memoryCard/iplMemoryCardManager _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl`: 87.55%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/memoryCard/iplMemoryCardManager getComment__Q33ipl5scene17MemoryCardManagerFUcsi`: 98.94309%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/memoryCard/iplMemoryCardManager create_banner__Q33ipl5scene17MemoryCardManagerFUcs`: 90.42453%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/memoryCard/iplMemoryCardManager getBlocks__Q33ipl5scene17MemoryCardManagerFUcs`: 92.0%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/cardSequence/iplCardSequence cardThreadMain`: 97.9402%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/cardSequence/iplCardSequence loadCardFileIcons`: 90.37305%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/cardSequence/iplCardSequence runCardMoveOrCopy`: 97.88651%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/sdChannelSelect/iplSDChannelSelect create__Q33ipl5scene15SDChannelSelectFv`: 97.73972%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/sdChannelSelect/iplSDChannelSelect collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl`: 97.81188%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/sdChannelSelect/iplSDChannelSelect collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl`: 97.833336%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/sdChannelSelect/iplSDChannelSelect collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl`: 98.007935%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/sdChannelSelect/iplSDChannelSelect collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl`: 97.55125%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/sdChannelSelect/iplSDChannelSelect flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv`: 99.65714%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/sdChannelTitle/iplSDChannelTitle iplSDChannelTitle_flushSaveBeforeExit`: 98.5946%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/sdChannelMemory/iplSDMemory create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect`: 99.15884%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/sdChannelMemory/iplSDMemory drawTransferTitles__Q33ipl5scene8SDMemoryFv`: 93.456764%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/scene/setting/iplSetting scanAP__Q33ipl5scene7SettingFv`: 99.20221%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/keyboard/tiCellPhone create__Q49textinput8keyboard13cellphonetype12LayoutByNW4RFP12MEMAllocator`: 99.8949%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/keyboard/tiInputForm calcCursorPos__Q39textinput9inputform4BaseFff`: 93.05215%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/keyboard/tiInputForm create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer`: 96.40169%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/keyboard/tiCandidateBox create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator`: 95.99148%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/keyboard/tiCandidateBox createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator`: 98.49537%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/keyboard/tiSignWindow create__Q49textinput8keyboard10signwindow12LayoutByNW4RFP12MEMAllocator`: 99.86425%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/keyboard/tiString inputChar__Q39textinput8tistring9DecolatedFw`: 90.757355%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/keyboard/tiZiString update__Q39textinput8tistring6WithZiFv`: 98.36996%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/channelScript/CHANSVm CHANSVmConvertToFloatFromStr`: 97.59036%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/channelScript/CHANSVm VmDateDtor`: 94.96703%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/channelScript/CHANSVm VmStringSplit`: 98.04054%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/channelScript/CHANSVm CHANSVmFormatString`: 99.84919%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/channelScript/CHANSVm VmBlobGetHexString`: 98.71951%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/channelScript/CHANSVm VmBlobPackCommon`: 97.949104%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/channelScript/CHANSVm VmBlobUnpack`: 98.452614%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/channelScript/CHANSVm VmWinEmuWrite`: 99.62687%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `src/channelScript/CHANSVm CHANSVmStep`: 96.98723%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RevoEX/src/cdb/CDBRecord CDBRecordEncrypt`: 99.19014%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RevoEX/src/net/md5 ProcessBlock`: 95.55556%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RevoEX/src/net/aes AESiEncryptBlock`: 65.81013%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RevoEX/src/net/aes AESiDecryptBlock`: 78.95618%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RevoEX/src/nhttp/NHTTP_recvbuf NHTTPi_compareTokenN_HdrRecvBuf`: 97.32258%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL NHTTPi_strnicmp`: 99.76471%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL NHTTPi_compareToken`: 99.73333%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RevoEX/src/nwc24/NWC24Download NWC24InitDlTask`: 98.923615%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RevoEX/src/so/SOBasic SOGetSockName`: 96.666664%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var TMCJPEGDEC_IdctBlock_Lumi`: 86.178986%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var TMCJPEGDEC_IdctBlock_Col`: 92.927315%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_exif_parse`: 99.43396%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD0_tag_parse`: 99.49065%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse TMCJPEGDEC_IFD1_tag_parse`: 96.14876%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8 TMCJPEGDEC_set_converterY8U8V8`: 92.78571%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_set_converterRGB565`: 93.91765%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV411toRGB565`: 91.17512%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV411toRGB565edge`: 95.42453%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV422toRGB565`: 97.132355%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV420toRGB565`: 95.42553%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGB565 TMCJPEGDEC_converterYUV420toRGB565edge`: 97.850876%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_set_converterRGBA8`: 93.91765%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV411toRGBA8`: 82.70661%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV411toRGBA8edge`: 94.28571%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV422toRGBA8`: 88.195946%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV422toRGBA8edge`: 92.0354%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV420toRGBA8`: 90.973854%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV420toRGBA8edge`: 87.5%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV211toRGBA8`: 91.15385%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV211toRGBA8edge`: 92.17391%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV444toRGBA8`: 90.670105%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoRGBA8 TMCJPEGDEC_converterYUV444toRGBA8edge`: 88.90909%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVLMiddleware/TMC_JPEG/src/b65/iqdec_b65_frv32 TMCJPEGDEC_decode_iquant`: 99.710144%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/NW4R/src/lyt/lyt_window DrawFrame__Q34nw4r3lyt6WindowFRCQ34nw4r4math4VEC2RCQ44nw4r3lyt6Window5FrameRCQ34nw4r3lyt15WindowFrameSizeUc`: 98.17819%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/kpad/KPAD KPADInit`: 97.810814%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/wad/wad WADImportGetBlocks`: 94.24161%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/wad/wad WADImportEx`: 99.02269%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/wad/wad WAD_815C1288`: 96.803276%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/wad/wad WADBackupEx`: 97.385124%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/wad/wad WADImportDVDExForBS`: 97.49049%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/fa/pdm_partition pdm_part_is_master_boot_sector`: 87.39286%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_init`: 93.125%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_finalize`: 92.63158%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_store_mbr_buf`: 99.75247%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/fa/driver/sd_drv pfd_sddrv_build_fat32_mbr_bpb`: 95.202705%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/nup/nup __nupParseServerInfo__FP14NUPContextInfoPcPcUx`: 98.108406%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/nup/nup __nupGetBootVersion__FP14NUPContextInfoP14ESTitleVersion`: 99.35583%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/nup/nup __nupGetTitleSize__FP12NUPTitleInfo`: 99.100716%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/kbd/kbd_lib kbdEventHandler`: 99.83871%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/kbd/kbd_lib kbdProcMod`: 99.90234%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/kbd/kbd_lib kbd_led_handler`: 99.72%; three historical attempts verified; see per-unit audit/disposition and coverage above.
- `libs/RVL_SDK/src/kbd/kbd_lib KBDSetModState`: 99.40476%; three historical attempts verified; see per-unit audit/disposition and coverage above.

The original descriptive names of the two newly separated tiZiString buffers are unknown. ElementWorkBuffer and PredictionBuffer are inferred from the clear/conversion/search consumers. Their extents and locations preserve the measured section bytes, all canonical relocation targets and the full unit data total. No padding, forced objects or link-status changes were introduced.
