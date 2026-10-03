# ult3 ultra worker, 2026-10-03

Read unslop and applied it to logs and final report. Worktree data-d2, branch agent/w1003/sol-ult3-ultra. No subagents, pushes, PRs, rebases or changes to other worktrees.

Baseline main/src/scene/memoryCard/iplMemoryCardManager: {'fuzzy_match_percent': 97.88362, 'total_code': '5396', 'matched_code': '2572', 'matched_code_percent': 47.664936, 'matched_data_percent': 100.0, 'total_functions': 26, 'matched_functions': 18, 'matched_functions_percent': 69.230774, 'complete_data_percent': 100.0, 'total_units': 1}
Data already 100 percent; no symbol rename or extent correction is warranted.
Baseline main/src/scene/sdChannelSelect/iplSDChannelSelect: {'fuzzy_match_percent': 99.749435, 'total_code': '33828', 'matched_code': '29412', 'matched_code_percent': 86.945724, 'total_data': '2960', 'matched_data': '2960', 'matched_data_percent': 100.0, 'total_functions': 129, 'matched_functions': 122, 'matched_functions_percent': 94.57364, 'total_units': 1}
Data already 100 percent; no symbol rename or extent correction is warranted.
Baseline main/libs/RevoEX/src/nwc24/NWC24Download: {'fuzzy_match_percent': 99.169655, 'total_code': '12496', 'matched_code': '8456', 'matched_code_percent': 67.669655, 'total_data': '80', 'matched_data': '80', 'matched_data_percent': 100.0, 'total_functions': 30, 'matched_functions': 26, 'matched_functions_percent': 86.666664, 'total_units': 1}
Data already 100 percent; no symbol rename or extent correction is warranted.
Baseline main/libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse: {'fuzzy_match_percent': 98.98035, 'total_code': '5088', 'matched_code': '1348', 'matched_code_percent': 26.49371, 'matched_data_percent': 100.0, 'total_functions': 6, 'matched_functions': 3, 'matched_functions_percent': 50.0, 'complete_data_percent': 100.0, 'total_units': 1}
Data already 100 percent; no symbol rename or extent correction is warranted.
src/scene/sdChannelSelect/iplSDChannelSelect: POOL IDENTICAL up to 101 (mine=101 base=101)
src/scene/memoryCard/iplMemoryCardManager: POOL IDENTICAL up to 0 (mine=0 base=0)
libs/RevoEX/src/nwc24/NWC24Download: POOL IDENTICAL up to 3 (mine=3 base=3)
libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse: POOL IDENTICAL up to 0 (mine=0 base=0)

BEGIN TMCJPEGDEC_IFD1_tag_parse: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS TMCJPEGDEC_IFD1_tag_parse: source 239 versus target 242 instructions. Target pivots 0x11a before 0x111, then 0x128 and 0x11c; source pivots 0x11b. Target rational offset stays r8 while pointer occupies r6; source exchanges these. Calls absent. Data absent. Correct ignored-tag exits and decoder local lifetime before registers.
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | remove redundant orientation case and give strip offset explicit return | source c9972682b4a6 | objdiff 95.54958%; instructions (241, 242, 228) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored tags use exact separate strip-offset exit without orientation or planar noops | source 36c7c6fd2840 | objdiff 92.23141%; instructions (241, 242, 230) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | ignored tags return directly, all recognized bodies remain separate | source 59bb4c74c948 | objdiff 96.08264%; instructions (248, 242, 236) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: target recomputes texture and palette field addresses from cached slot base plus file stride at GX calls; source caches the complete address. Metadata row/file addition order also differs. Calls and widths agree. Test member-address expression boundaries and offset-base lifetime; no raw offsets or new data.
ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | member addresses use typed row pointer addition at each GX call | source 0ffe904d8869 | objdiff 87.55%; instructions (100, 100, 37) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | metadata and cell member accesses use index-first typed row expressions | source 4554b5fc9247 | objdiff 87.55%; instructions (100, 100, 37) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | metadata flattened as actual contiguous slots, texture address remains row plus file | source 29b6e0c6c494 | objdiff 84.44%; instructions (102, 100, 62) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN create_banner__Q33ipl5scene17MemoryCardManagerFUcs: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS create_banner__Q33ipl5scene17MemoryCardManagerFUcs: target recomputes texture and palette field addresses from cached slot base plus file stride at GX calls; source caches the complete address. Metadata row/file addition order also differs. Calls and widths agree. Test member-address expression boundaries and offset-base lifetime; no raw offsets or new data.
ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | member addresses use typed row pointer addition at each GX call | source 68cdc0e57ef4 | objdiff 90.42453%; instructions (106, 106, 70) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | metadata and cell member accesses use index-first typed row expressions | source a3cd2595d561 | objdiff 90.42453%; instructions (106, 106, 70) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT create_banner__Q33ipl5scene17MemoryCardManagerFUcs | metadata flattened as actual contiguous slots, texture address remains row plus file | source 542a9f3e199f | objdiff 89.85849%; instructions (109, 106, 89) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN TMCJPEGDEC_IFD0_tag_parse: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS TMCJPEGDEC_IFD0_tag_parse: 480/481 instructions; target has bltlr after the ignored compression comparison, source omits it. Target offset/pointer use r8/r6 opposite to source. Rational reads and stores otherwise align after accounting for missing exit. Separate ignored compression return is a real branch-shape lever.
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | compression has own ignored return block | source 6dce02112543 | objdiff 99.282745%; instructions (481, 481, 75) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | compression returns separately and rational pointer declared before offset | source 44cc78f254d2 | objdiff 99.282745%; instructions (481, 481, 75) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT TMCJPEGDEC_IFD0_tag_parse | all unhandled compressed/strip/jpeg-offset tags have separate exits | source 46ab9c4db428 | objdiff 98.03534%; instructions (487, 481, 451) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN TMCJPEGDEC_exif_parse: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS TMCJPEGDEC_exif_parse: 212 identical instruction forms with 21 register differences. First IFD cursor and original TIFF base exchange r27/r30; first entry count and byte length exchange r26/r23. No store-reload or extent evidence. Give each real IFD its own local cursor and count lifetime, then declaration search.
ATTEMPT TMCJPEGDEC_exif_parse | each IFD has independent lexical entry cursor | source 7da75eebee29 | objdiff 98.962265%; instructions (212, 212, 34) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT TMCJPEGDEC_exif_parse | each IFD has independent entry-count and byte-length locals | source f79fcd855aa6 | objdiff 99.43396%; instructions (212, 212, 21) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT TMCJPEGDEC_exif_parse | each IFD owns all real traversal locals | source b4521814b5ae | objdiff 98.77358%; instructions (212, 212, 40) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN NWC24UpdateDlTask: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS NWC24UpdateDlTask: target 0x20 frame, four saved registers, 253 instructions; source 0x30 frame and 249 instructions. Group permission target loads flags then initializes separate BOOL and loads groupId; retry target caches work before retry count. Calls sequence and access-time conversion agree. Reconstruct the permission boolean and cache boundary before any allocator search.
ATTEMPT NWC24UpdateDlTask | update-only validation reads group fields inside nested allowed predicate | source c5491e32ce37 | objdiff 98.81423%; instructions (253, 253, 37) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored
FAILED NWC24UpdateDlTask | nested group permission plus readonly cached retry validation with shift first | 034b74aebc60 | .o  build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nwc24/NWC24Download.c -o build/43U/src/libs/RevoEX/src/nwc24 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d ### mwcceppc.exe Compiler: #    File: libs\RevoEX\src\nwc24\NWC24Download.c # ---------------------------------------------- #     750:     u32 retryMask;  #   Error:     ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
FAILED NWC24UpdateDlTask | permission boolean declared before group and flags at its real helper boundary | 7bc50c5b2886 | .o  build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RevoEX/src/nwc24/NWC24Download.c -o build/43U/src/libs/RevoEX/src/nwc24 && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d build/43U/src/libs/RevoEX/src/nwc24/NWC24Download.d ### mwcceppc.exe Compiler: #    File: libs\RevoEX\src\nwc24\NWC24Download.c # ---------------------------------------------- #     750:     u32 retryMask;  #   Error:     ^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

Prior-art index has no entries for these four units. Read prior parked rounds and orch/perm9-progress diff. The current task supersedes remembered orchestrator workflows. No old memory result is used as match evidence.

BEGIN NWC24UpdateDlTask: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS NWC24UpdateDlTask: target 0x20 frame, four saved registers, 253 instructions; source 0x30 frame and 249 instructions. Group permission target loads flags then initializes separate BOOL and loads groupId; retry target caches work before retry count. Calls sequence and access-time conversion agree. Reconstruct the permission boolean and cache boundary before any allocator search.
ATTEMPT NWC24UpdateDlTask | update-only validation reads group fields inside nested allowed predicate | source c5491e32ce37 | objdiff 98.81423%; instructions (253, 253, 37) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored
ATTEMPT NWC24UpdateDlTask | nested group permission plus readonly cached retry validation with shift first | source b0ebba62f739 | objdiff 98.83399%; instructions (253, 253, 37) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored
ATTEMPT NWC24UpdateDlTask | permission boolean declared before group and flags at its real helper boundary | source 3785a6a84641 | objdiff 98.83399%; instructions (253, 253, 37) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored

BEGIN TMCJPEGDEC_IFD1_tag_parse: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | omit redundant planar configuration label, keep orientation noop | source dc6b589558ec | objdiff 91.900826%; instructions (239, 242, 219) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | strip-offset owns direct exit, orientation remains in ignored group | source 2673e28c0bc7 | objdiff 98.57438%; instructions (242, 242, 64) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT TMCJPEGDEC_IFD1_tag_parse | rational decoder offset and cursor are shared at function scope | source 8887ff7d2707 | objdiff 91.900826%; instructions (239, 242, 219) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: matched call/branch sequence and instruction count. At each memcpy exit target completes count increment/store before stack usage and threshold loads; source hoists threshold before increment. ChannelOrder additionally homes title-ID registers and commutes channel base address. Target has no volatile reread. Test legal signed/unsigned count view and typed two-element threshold bounds to isolate aliases.
ATTEMPT collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | counter increment uses legal signed-word reference for bounded title total | source 22b47715e0a7 | objdiff 97.81188%; instructions (101, 101, 4) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | counter increment uses signed-word pointer alias at the public unsigned output boundary | source 4ad8536c09b8 | objdiff 97.81188%; instructions (101, 101, 4) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | real two-element usage thresholds retain array-reference type | source e0a4029caf95 | objdiff 97.81188%; instructions (101, 101, 4) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored

BEGIN collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: matched call/branch sequence and instruction count. At each memcpy exit target completes count increment/store before stack usage and threshold loads; source hoists threshold before increment. ChannelOrder additionally homes title-ID registers and commutes channel base address. Target has no volatile reread. Test legal signed/unsigned count view and typed two-element threshold bounds to isolate aliases.
ATTEMPT collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | counter increment uses legal signed-word reference for bounded title total | source 5386e931eda4 | objdiff 97.833336%; instructions (102, 102, 4) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | counter increment uses signed-word pointer alias at the public unsigned output boundary | source c3e79c1d7730 | objdiff 97.833336%; instructions (102, 102, 4) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | real two-element usage thresholds retain array-reference type | source c37be6a7884f | objdiff 97.833336%; instructions (102, 102, 4) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored

BEGIN collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: matched call/branch sequence and instruction count. At each memcpy exit target completes count increment/store before stack usage and threshold loads; source hoists threshold before increment. ChannelOrder additionally homes title-ID registers and commutes channel base address. Target has no volatile reread. Test legal signed/unsigned count view and typed two-element threshold bounds to isolate aliases.
ATTEMPT collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | counter increment uses legal signed-word reference for bounded title total | source 29748cadbda5 | objdiff 97.29365%; instructions (126, 126, 22) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | counter increment uses signed-word pointer alias at the public unsigned output boundary | source c1453c88f514 | objdiff 97.29365%; instructions (126, 126, 22) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | real two-element usage thresholds retain array-reference type | source 412f4d022dd4 | objdiff 97.29365%; instructions (126, 126, 22) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored

BEGIN collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: matched call/branch sequence and instruction count. At each memcpy exit target completes count increment/store before stack usage and threshold loads; source hoists threshold before increment. ChannelOrder additionally homes title-ID registers and commutes channel base address. Target has no volatile reread. Test legal signed/unsigned count view and typed two-element threshold bounds to isolate aliases.
ATTEMPT collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | counter increment uses legal signed-word reference for bounded title total | source 600437984cf2 | objdiff 97.55125%; instructions (361, 361, 16) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | counter increment uses signed-word pointer alias at the public unsigned output boundary | source 705255d53e37 | objdiff 97.55125%; instructions (361, 361, 16) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl | real two-element usage thresholds retain array-reference type | source af30b5342d4e | objdiff 97.55125%; instructions (361, 361, 16) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored

BEGIN create__Q33ipl5scene15SDChannelSelectFv: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS create__Q33ipl5scene15SDChannelSelectFv: target reloads System BS2Manager in the update body, source reuses condition value. Frame 0x20, calls/pool agree, one instruction missing. Test explicit loop statement boundaries and const state getter receiver.
ATTEMPT create__Q33ipl5scene15SDChannelSelectFv | poll loop tests state inside unconditional loop before update | source f591a0ee24e1 | objdiff 92.363014%; instructions (145, 146, 40) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT create__Q33ipl5scene15SDChannelSelectFv | poll body reloads through a read-only view of the real System manager cell | source 144446af920d | objdiff 97.73972%; instructions (145, 146, 39) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT create__Q33ipl5scene15SDChannelSelectFv | poll readiness check uses explicit scoped boolean before body | source 34d795e8d484 | objdiff 92.363014%; instructions (145, 146, 40) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored

BEGIN flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False
DIAGNOSIS flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv: 35/35 instructions; only save manager and heap argument loads reorder. No volatile evidence. Test the flush member-call boundary and actual heap lifetime.
ATTEMPT flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv | flush member receiver dereferenced after named actual heap argument | source d0d29bd8bfca | objdiff 99.65714%; instructions (35, 35, 2) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv | flush member call uses explicit parenthesized function expression and typed returned file | source 527e2a28444f | objdiff 99.65714%; instructions (35, 35, 2) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored
ATTEMPT flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv | flush receiver and allocator use object address expressions at the call | source 0e199eb4ab1b | objdiff 99.65714%; instructions (35, 35, 2) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | restored

BEGIN setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj: origin/main fdd68ddd3046c44a0a4bcc250a58d9bf226f5cbc, remote owned source differs=False

BEGIN setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj: current baseline 233/233 instructions, only X and width floating registers f29/f31 exchanged. Earlier logs used worse projection-width source. Run three real scissor lifetimes then official declaration search on this baseline.
ATTEMPT setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj | screen origin declarations precede extents | source b22710bca673 | objdiff 100.0%; instructions (233, 233, 0) | pool POOL IDENTICAL up to 101 (mine=101 base=101) | regressions [] | EXACT CANDIDATE retained

EXACT CANDIDATE setChannelScissor: declaring X, Y, width, height in that order fixes the only surviving f29/f31 rotation on current main. Objdiff100%, ctxdiff233/233 and diffs0; all 101 strings identical. Full clean gate running before local commit.

## Clean gate for first exact gain

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 30344/33828 data 2960/2960 functions 123/129 fuzzy 99.7624 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 123/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 99.76244
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 97.73972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.29365
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.55125
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 29412/33828 data 2960 functions 122 fuzzy 99.7494
[src/scene/memoryCard/iplMemoryCardManager] pool: IDENTICAL
[src/scene/memoryCard/iplMemoryCardManager] objdiff: code 2572/5396 data None/None functions 18/26 fuzzy 97.8836 linked code 0
[src/scene/memoryCard/iplMemoryCardManager] instruction-exact functions: 18/26
[src/scene/memoryCard/iplMemoryCardManager]   section .text size 5396 match 97.88362
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 99.830505
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 99.830505
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs 92.30769
[src/scene/memoryCard/iplMemoryCardManager]   below 100: update_file_array__Q33ipl5scene17MemoryCardManagerFUc 99.72222
[src/scene/memoryCard/iplMemoryCardManager]   below 100: _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl 87.55
[src/scene/memoryCard/iplMemoryCardManager]   below 100: getComment__Q33ipl5scene17MemoryCardManagerFUcsi 98.94309
[src/scene/memoryCard/iplMemoryCardManager]   below 100: create_banner__Q33ipl5scene17MemoryCardManagerFUcs 90.42453
[src/scene/memoryCard/iplMemoryCardManager]   below 100: getBlocks__Q33ipl5scene17MemoryCardManagerFUcs 92.0
[src/scene/memoryCard/iplMemoryCardManager] baseline: code 2572/5396 data None functions 18 fuzzy 97.8836
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 8456/12496 data 80/80 functions 26/30 fuzzy 99.1697 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 26/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.169655
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 95.00395
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 97.7182
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 8456/12496 data 80 functions 26 fuzzy 99.1697
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 98.9804 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 98.98035
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 99.49065
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 96.14876
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 98.9804
regressions vs baseline: 0
global matched_code_percent: 91.58086 -> 91.61198
global fuzzy_match_percent: 99.70061 -> 99.70076
global complete_code_percent: 74.76262 -> 74.76262
global matched_data_percent: 99.77803 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
Accepted local source commit 439df75559f02c66e756413148b9b37512b61074 after clean full gate, pool identical, objdiff100 and ctxdiff0.

BEGIN isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 118/118, only add operand order for directory row and file offset differs twice. Prior pointer/array/inline forms did not help. Try actual directory-row aggregate and tuple access boundaries; no control flow changes.
ATTEMPT isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | directory row modeled as an aggregate containing its file records | source 07289550c7f6 | objdiff 99.830505%; instructions (118, 118, 2) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | directory has real per-slot base pointer table | source 53e52d951738 | objdiff 91.305084%; instructions (122, 118, 115) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | selected directory entry passes through its typed pointer output | source ce4a3f3c9036 | objdiff 99.830505%; instructions (118, 118, 2) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 118/118, only add operand order for directory row and file offset differs twice. Prior pointer/array/inline forms did not help. Try actual directory-row aggregate and tuple access boundaries; no control flow changes.
ATTEMPT isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | directory row modeled as an aggregate containing its file records | source 02813d9ae7d9 | objdiff 99.830505%; instructions (118, 118, 2) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | directory has real per-slot base pointer table | source 87fb2bc993e1 | objdiff 91.305084%; instructions (122, 118, 115) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | selected directory entry passes through its typed pointer output | source cf3ff9a7e228 | objdiff 99.830505%; instructions (118, 118, 2) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: instruction count identical; sole structural difference is r11 epilogue setup hoisted before dependent file-state load. Target reads same fields. Test real return value helper, typed row aggregate and caller parameter aliases, no fake barriers.
ATTEMPT isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | return field read belongs to a typed readonly entry helper | source 8bc69628bbe1 | objdiff 92.30769%; instructions (26, 26, 8) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | real slot and displayed index retained as const input references | source fa76d137d3d9 | objdiff 92.30769%; instructions (26, 26, 8) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | actual state slot modeled as row aggregate at member read | source e92acb5d23fc | objdiff 92.30769%; instructions (26, 26, 8) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN getBlocks__Q33ipl5scene17MemoryCardManagerFUcs: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS getBlocks__Q33ipl5scene17MemoryCardManagerFUcs: instruction count identical; sole structural difference is r11 epilogue setup hoisted before dependent file-state load. Target reads same fields. Test real return value helper, typed row aggregate and caller parameter aliases, no fake barriers.
ATTEMPT getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | return field read belongs to a typed readonly entry helper | source f44ec3ae305d | objdiff 91.0%; instructions (25, 25, 9) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | real slot and displayed index retained as const input references | source 503ab0b1ff67 | objdiff 92.0%; instructions (25, 25, 9) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | actual state slot modeled as row aggregate at member read | source 805056d04e2a | objdiff 92.0%; instructions (25, 25, 9) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN getComment__Q33ipl5scene17MemoryCardManagerFUcsi: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS getComment__Q33ipl5scene17MemoryCardManagerFUcsi: 123/123, all control flow and calls equal. Saved webs for this, selector stride, slot stride, file stride and encoded buffer rotated. Narrow trim cursor and zero use r5/r3 instead of target r3/r5. Test actual encoded-buffer declaration lifetime and signed narrow-cursor views before declaration search.
ATTEMPT getComment__Q33ipl5scene17MemoryCardManagerFUcsi | encoded buffer pointer declaration precedes file lookup but assignment stays after copy | source e10298937b6f | objdiff 98.94309%; instructions (123, 123, 20) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT getComment__Q33ipl5scene17MemoryCardManagerFUcsi | mutable encoded buffer view and read cursor initialized before write cursor | source 3b7856754f96 | objdiff 98.82114%; instructions (123, 123, 21) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT getComment__Q33ipl5scene17MemoryCardManagerFUcsi | narrow trim uses signed byte cursors with read lifetime before write | source c667bd66133b | objdiff 98.82114%; instructions (123, 123, 21) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

BEGIN update_file_array__Q33ipl5scene17MemoryCardManagerFUc: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS update_file_array__Q33ipl5scene17MemoryCardManagerFUc: 90/90, only command and manager high-base scratch r3/r4 exchange, switch and stores identical. Command is existing s32 storage. Test signedness-preserving word expression boundaries and real result snapshots, no dummy value.
ATTEMPT update_file_array__Q33ipl5scene17MemoryCardManagerFUc | command word widened for the legitimate range subtraction then narrowed | source b2f6fd7fa4aa | objdiff 96.94444%; instructions (92, 90, 77) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT update_file_array__Q33ipl5scene17MemoryCardManagerFUc | range and completion switch read the same typed command member pointer | source 97acbbc4fc71 | objdiff 93.28889%; instructions (89, 90, 81) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored
ATTEMPT update_file_array__Q33ipl5scene17MemoryCardManagerFUc | actual last result is a local snapshot until command query updates it | source 60c192304283 | objdiff 94.333336%; instructions (89, 90, 69) | pool POOL IDENTICAL up to 0 (mine=0 base=0) | regressions [] | restored

Read detailed orch/perm9-progress attempts after current EXIF trials. Prior source shares the ignored-strip exit that recovers IFD1 242 instructions, rational regrouping and byte-cursor experiments. Do not rerun these. No EXIF trial is accepted without a new exact function.

BEGIN NWC24InitDlTask: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS NWC24InitDlTask: 144/144 and branch/call shape already exact. Zero, high ID, low ID and cached header form different saved-register webs. No target volatile or overlap evidence. Test real byte-buffer type and initializer form, then parameter immutability before declaration search.
ATTEMPT NWC24InitDlTask | home-directory char buffer uses empty string initialization | source 98cee12444b3 | objdiff 98.923615%; instructions (144, 144, 31) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored
ATTEMPT NWC24InitDlTask | home-directory represented as bytes until NAND and numeric parse interfaces | source 68671f8cf920 | objdiff 98.923615%; instructions (144, 144, 31) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored
ATTEMPT NWC24InitDlTask | task pointer and download type are immutable formal values | source 024eb9df937b | objdiff 98.923615%; instructions (144, 144, 31) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored

BEGIN NWC24iCheckDlHeaderConsistency: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS NWC24iCheckDlHeaderConsistency: 212/212, only stack task address materialization follows rather than precedes saved header/repair arguments. Every body instruction exact. Preserve task identity and try actual object reference lifetime and single-element task array; no artificial storage or initialization.
ATTEMPT NWC24iCheckDlHeaderConsistency | one real task workspace expressed as an array for its byte-buffer API | source 623cc592ede5 | objdiff 98.77358%; instructions (212, 212, 3) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored
ATTEMPT NWC24iCheckDlHeaderConsistency | stack task is passed directly to every read/validate/delete boundary | source 3d8a70032ce2 | objdiff 96.95283%; instructions (212, 212, 6) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored
ATTEMPT NWC24iCheckDlHeaderConsistency | immutable formal header and repair values, same task workspace lifetime | source 4dd32e1e2199 | objdiff 98.77358%; instructions (212, 212, 3) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored

BEGIN AddTaskInternal: origin/main be7ded2fdc4ebba0b87695a132905e38e7f984df, remote owned source differs=False
DIAGNOSIS AddTaskInternal: 398/401, frame0x30, target free-slot count has wider loop value, URL-result error has an explicit join and inline update permission helper differs. Calls agree; target last retry saves differ. Test URL/free-slot helper branch boundaries without changing other callers.
ATTEMPT AddTaskInternal | URL helper returns its real checked result through caller join | source c75bea9d2de1 | objdiff 96.44638%; instructions (393, 401, 325) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored
ATTEMPT AddTaskInternal | slot search keeps u32 candidate with narrowed directory access at API boundary | source 98792bd884a8 | objdiff 97.7182%; instructions (398, 401, 323) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored
ATTEMPT AddTaskInternal | successful slot search explicit zero result exit inside non-full branch | source cae203a71ed5 | objdiff 97.705734%; instructions (398, 401, 323) | pool POOL IDENTICAL up to 3 (mine=3 base=3) | regressions [] | restored

## Final open-function audit

OPEN isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 99.830505%; 3 distinct successfully built source attempts; 118/118, two commuted directory address adds. All nonexact trials restored.
OPEN isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 99.830505%; 3 distinct successfully built source attempts; 118/118, two commuted directory address adds. All nonexact trials restored.
OPEN isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: 92.30769%; 3 distinct successfully built source attempts; 26/26, epilogue r11 setup is hoisted before dependent member loads. All nonexact trials restored.
OPEN update_file_array__Q33ipl5scene17MemoryCardManagerFUc: 99.72222%; 3 distinct successfully built source attempts; 90/90, command/base scratch registers exchanged. All nonexact trials restored.
OPEN _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: 87.55%; 3 distinct successfully built source attempts; 100/100, metadata address operands and texture/TLUT pointer lifetimes differ. All nonexact trials restored.
OPEN getComment__Q33ipl5scene17MemoryCardManagerFUcsi: 98.94309%; 3 distinct successfully built source attempts; 123/123, saved-register webs and narrow trim scratch registers differ. All nonexact trials restored.
OPEN create_banner__Q33ipl5scene17MemoryCardManagerFUcs: 90.42453%; 3 distinct successfully built source attempts; 106/106, icon row address association and GX argument pointer lifetimes differ. All nonexact trials restored.
OPEN getBlocks__Q33ipl5scene17MemoryCardManagerFUcs: 92.0%; 3 distinct successfully built source attempts; 25/25, epilogue r11 setup hoisted before member loads. All nonexact trials restored.
OPEN create__Q33ipl5scene15SDChannelSelectFv: 97.73972%; 3 distinct successfully built source attempts; 145/146, BS2 polling body reuses condition pointer instead of target reload. All nonexact trials restored.
OPEN collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.81188%; 3 distinct successfully built source attempts; 101/101, increment/store and usage threshold load schedule differs. All nonexact trials restored.
OPEN collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.833336%; 3 distinct successfully built source attempts; 102/102, increment/store and usage threshold load schedule differs. All nonexact trials restored.
OPEN collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.29365%; 3 distinct successfully built source attempts; 126/126, title/register lifetimes, channel address and count/threshold schedule differ. All nonexact trials restored.
OPEN collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: 97.55125%; 3 distinct successfully built source attempts; 361/361, four count/threshold schedules differ. All nonexact trials restored.
OPEN flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv: 99.65714%; 3 distinct successfully built source attempts; 35/35, heap/manager argument loads reverse order. All nonexact trials restored.
OPEN NWC24InitDlTask: 98.923615%; 3 distinct successfully built source attempts; 144/144, zero, owner IDs, header and permission saved-register webs differ. All nonexact trials restored.
OPEN NWC24UpdateDlTask: 95.00395%; 3 distinct successfully built source attempts; 249/253, group permission boolean and retry/helper boundaries differ. All nonexact trials restored.
OPEN NWC24iCheckDlHeaderConsistency: 98.77358%; 3 distinct successfully built source attempts; 212/212, task address created after saved parameter copies. All nonexact trials restored.
OPEN AddTaskInternal: 97.7182%; 3 distinct successfully built source attempts; 398/401, URL/free-slot/retry helper branch boundaries differ. All nonexact trials restored.
OPEN TMCJPEGDEC_exif_parse: 99.43396%; 3 distinct successfully built source attempts; 212/212, TIFF base/cursor and count/length registers exchanged. All nonexact trials restored.
OPEN TMCJPEGDEC_IFD0_tag_parse: 99.49065%; 3 distinct successfully built source attempts; 480/481, ignored low-tag exit absent, rational offset/cursor registers exchanged. All nonexact trials restored.
OPEN TMCJPEGDEC_IFD1_tag_parse: 96.14876%; 6 distinct successfully built source attempts; 239/242, ignored-tag dispatch tree and rational offset/cursor registers differ. All nonexact trials restored.
Every remaining function has at least three distinct successfully compiled source attempts. Only setChannelScissor is accepted. Data and section ownership were already100 percent; no config/symbol/header change. No inline asm, volatile additions, register keyword, pinned labels, fake symbols, padding, comments, forced data, or unit link flags added. Compiler ties remain unresolved.


## Final full clean gate over all four owned units

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 30344/33828 data 2960/2960 functions 123/129 fuzzy 99.7624 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 123/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 99.76244
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 97.73972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.29365
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.55125
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 29412/33828 data 2960 functions 122 fuzzy 99.7494
[src/scene/memoryCard/iplMemoryCardManager] pool: IDENTICAL
[src/scene/memoryCard/iplMemoryCardManager] objdiff: code 2572/5396 data None/None functions 18/26 fuzzy 97.8836 linked code 0
[src/scene/memoryCard/iplMemoryCardManager] instruction-exact functions: 18/26
[src/scene/memoryCard/iplMemoryCardManager]   section .text size 5396 match 97.88362
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 99.830505
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl 99.830505
[src/scene/memoryCard/iplMemoryCardManager]   below 100: isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs 92.30769
[src/scene/memoryCard/iplMemoryCardManager]   below 100: update_file_array__Q33ipl5scene17MemoryCardManagerFUc 99.72222
[src/scene/memoryCard/iplMemoryCardManager]   below 100: _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl 87.55
[src/scene/memoryCard/iplMemoryCardManager]   below 100: getComment__Q33ipl5scene17MemoryCardManagerFUcsi 98.94309
[src/scene/memoryCard/iplMemoryCardManager]   below 100: create_banner__Q33ipl5scene17MemoryCardManagerFUcs 90.42453
[src/scene/memoryCard/iplMemoryCardManager]   below 100: getBlocks__Q33ipl5scene17MemoryCardManagerFUcs 92.0
[src/scene/memoryCard/iplMemoryCardManager] baseline: code 2572/5396 data None functions 18 fuzzy 97.8836
[libs/RevoEX/src/nwc24/NWC24Download] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Download] objdiff: code 8456/12496 data 80/80 functions 26/30 fuzzy 99.1697 linked code 0
[libs/RevoEX/src/nwc24/NWC24Download] instruction-exact functions: 26/30
[libs/RevoEX/src/nwc24/NWC24Download]   section .data size 56 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sbss size 8 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Download]   section .text size 12496 match 99.169655
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24InitDlTask 98.923615
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24UpdateDlTask 95.00395
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: NWC24iCheckDlHeaderConsistency 98.77358
[libs/RevoEX/src/nwc24/NWC24Download]   below 100: AddTaskInternal 97.7182
[libs/RevoEX/src/nwc24/NWC24Download] baseline: code 8456/12496 data 80 functions 26 fuzzy 99.1697
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 98.9804 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 98.98035
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 99.49065
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 96.14876
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 98.9804
regressions vs baseline: 0
global matched_code_percent: 91.58086 -> 91.61198
global fuzzy_match_percent: 99.70061 -> 99.70076
global complete_code_percent: 74.76262 -> 74.76262
global matched_data_percent: 99.77803 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Final official declaration-search scores, using already-built objects after all structural trials. No declaration mutations or repeated searches:

isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: structural/exact (0, 2), instructions 118/118.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: structural/exact (0, 2), instructions 118/118.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: structural/exact (2, 8), instructions 26/26.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc: structural/exact (0, 4), instructions 90/90.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: structural/exact (16, 37), instructions 100/100.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi: structural/exact (0, 20), instructions 123/123.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs: structural/exact (15, 70), instructions 106/106.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs: structural/exact (2, 9), instructions 25/25.
create__Q33ipl5scene15SDChannelSelectFv: structural/exact (4, 39), instructions 145/146.
collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: structural/exact (2, 4), instructions 101/101.
collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: structural/exact (2, 4), instructions 102/102.
collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: structural/exact (2, 22), instructions 126/126.
collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl: structural/exact (8, 16), instructions 361/361.
flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv: structural/exact (2, 2), instructions 35/35.
NWC24InitDlTask: structural/exact (0, 31), instructions 144/144.
NWC24UpdateDlTask: structural/exact (19, 250), instructions 249/253.
NWC24iCheckDlHeaderConsistency: structural/exact (2, 3), instructions 212/212.
AddTaskInternal: structural/exact (20, 323), instructions 398/401.
TMCJPEGDEC_exif_parse: structural/exact (0, 21), instructions 212/212.
TMCJPEGDEC_IFD0_tag_parse: structural/exact (5, 457), instructions 480/481.
TMCJPEGDEC_IFD1_tag_parse: structural/exact (14, 226), instructions 239/242.

Final progress/report and build/43U/ok passed after the clean gate. setChannelScissor fresh ctxdiff: 233/233 instructions, diffs0. SD pool101/101 identical. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Exact/code/data before->after: SD122/129->123/129,29412->30344,2960->2960; Memory18/26 unchanged,2572 unchanged,0 unchanged; NWC26/30 unchanged,8456 unchanged,80 unchanged; EXIF3/6 unchanged,1348 unchanged,0 unchanged. Source change is two declaration moves. No incomplete unit marked Matching.
