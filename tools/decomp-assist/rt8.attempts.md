# rt8 fuzzy lane

Baseline HEAD 1994d24f; origin fetched before analysis.

## src/scene/memoryCard/iplMemoryCardManager
Pool first: POOL IDENTICAL up to 0 (mine=0 base=0)

## src/scene/setting/iplRakuRakuThread
Pool first: POOL IDENTICAL up to 1 (mine=1 base=1)

## src/keyboard/tiCandidateBox
Pool first: POOL IDENTICAL up to 57 (mine=57 base=57)

### isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: same 0x30 stack, 118 instructions; directory final add operands reversed at 28 and 78. Source alias/address forms first.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | const directory view | 118/118 instructions; structural/exact (0, 2); source 48cb3ea550. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | constant row base and pointer addition | 118/118 instructions; structural/exact (0, 2); source 2334e7ee31. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | flat file array combined element index | 118/118 instructions; structural/exact (6, 8); source eef2709d96. Restored.

### isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: same 0x30 stack, 118 instructions; directory final add operands reversed at 28 and 78. Source alias/address forms first.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | const directory view | 118/118 instructions; structural/exact (0, 2); source 931bf96b4b. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | constant row base and pointer addition | 118/118 instructions; structural/exact (0, 2); source fae8c0231e. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | flat file array combined element index | 118/118 instructions; structural/exact (6, 8); source 7331032c0a. Restored.

### isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: target epilogue begins after indexed load, source schedules r11 setup before it; identical frame/count. Try typed access and argument width.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | word slot local | 26/26 instructions; structural/exact (2, 8); source aaa889c050. Restored.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | read-only metadata view | 26/26 instructions; structural/exact (2, 8); source 63ce1c0ba9. Restored.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | result local and explicit access boundary | 26/26 instructions; structural/exact (2, 8); source de66a68f8c. Restored.

### getBlocks__Q33ipl5scene17MemoryCardManagerFUcs
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: target epilogue begins after indexed load, source schedules r11 setup before it; identical frame/count. Try typed access and argument width.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | word slot local | 25/25 instructions; structural/exact (2, 9); source 2fa0910156. Restored.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | read-only metadata view | 25/25 instructions; structural/exact (2, 9); source 533e5280d2. Restored.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | result local and explicit access boundary | 25/25 instructions; structural/exact (2, 9); source 01bbf121c4. Restored.

### update_file_array__Q33ipl5scene17MemoryCardManagerFUc
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: stack/count and branch structure exact, r3/r4 colors swapped around command range load. Try bounded-command representations.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | reference command local | 90/90 instructions; structural/exact (0, 4); source ead62fd09e. Restored.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | pre-subtracted unsigned command | 90/90 instructions; structural/exact (2, 6); source 638889488c. Restored.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | result captured before command test | 90/90 instructions; structural/exact (3, 7); source 0d8d38e2bb. Restored.

### start__Q33ipl5scene14RakuRakuThreadFv
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: target 96 instructions versus 97 source; target hoists one .bss base for allocator/status/queue, source independently addresses extern globals. Frame 0x20 exact. Static storage ownership could enable compiler pooling without changing names or object extents.
start__Q33ipl5scene14RakuRakuThreadFv | internal C-linkage storage for all three context objects | 97/96 instructions; structural/exact (13, 88); source f4e8a26895. Restored.
start__Q33ipl5scene14RakuRakuThreadFv | retain exp heap allocation result across member store | 97/96 instructions; structural/exact (13, 88); source ab852d6631. Restored.
start__Q33ipl5scene14RakuRakuThreadFv | pooled context with aggregate socket callback initializer | 95/96 instructions; structural/exact (17, 87); source 1e0137e9e8. Restored.

### _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: 100/100 instructions, same frame; target row/column icon additions ordered differently, GX texture base and index stay separate until each call, source caches full texture earlier. No volatile proof.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | const icon metadata changes alias assumptions | build failed 'GXInitTexObj(const _GXTexObj *, void *, unsigned short, unsigned short,  #   _GXTexFmt, _GXTexWrapMode, _GXTexWrapMode, unsigned char)' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | cell row lifetime independent from texture index | 95/100 instructions; structural/exact (52, 84); source 2ae5ae2cb9. Restored.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | branch texture result computed after GX initialization | 101/100 instructions; structural/exact (17, 61); source b5b649fb17. Restored.

### getComment__Q33ipl5scene17MemoryCardManagerFUcsi
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: 123/123 instructions, same frame; callee-saved pointer order rotated, byte-trim read pointer r3/r5 swapped. Try byte trim boundaries, destination lifetime, then declaration search.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | read pointer declared before write pointer | 123/123 instructions; structural/exact (0, 21); source e55df59159. Restored.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | const trim read pointer | 123/123 instructions; structural/exact (0, 20); source 894b4c4417. Restored.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | destination pointer shared across clearing and conversion calls | 123/123 instructions; structural/exact (0, 26); source 031502f100. Restored.

### create_banner__Q33ipl5scene17MemoryCardManagerFUcs
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: 106/106 same frame, target re-forms icon row before format tests while source shares validity pointer; texture/TLUT address lifetime and register color differ.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | const render metadata pointer | build failed 'GXInitTexObj(const _GXTexObj *, void *, unsigned short, unsigned short,  #   _GXTexFmt, _GXTexWrapMode, _GXTexWrapMode, unsigned char)' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | cell row pointer independent of banner column | 97/106 instructions; structural/exact (81, 90); source bd83a5bab1. Restored.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | load and return share banner result pointer | 94/106 instructions; structural/exact (57, 92); source bad9423cf7. Restored.

### finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: source frame0x20 vs target0x30 and 135/133 instructions; target wraps state 6/7 branch around teardown then joins config copy, source early returns before it. Separate .bss loads also differ.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | state success block with shared config continuation | 136/133 instructions; structural/exact (30, 127); source 780ba8f60a. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | read-only configuration copy view | 136/133 instructions; structural/exact (30, 127); source 0d7c100521. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | defer settings pointer until privacy selection | 136/133 instructions; structural/exact (30, 126); source 69ed282da6. Restored.

### create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis: source351/target352 instructions, equal frame; inlined UITextArea::Init uses index offset plus this, target advancing receiver pointer. Button Create retains pane name pointers instead of repeated base offsets. Avoid changing other exact helper users.
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | typed decorated-string receiver lifetime | 351/352 instructions; structural/exact (27, 239); source a76583d3c1. Restored.
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | direct scroll-name arguments without intermediate base local | 353/352 instructions; structural/exact (29, 268); source 2c5d15643f. Restored.
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | text-area receiver pointer before inlined init | 352/352 instructions; structural/exact (29, 262); source 95ff94a16d. Restored.

### createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis:214/216 instructions, target reloads animation descriptor pointer after CreateAnimTransform whereas source keeps descriptor itself live. Frame0x50 equal. Entry reference lifetime then loop indices.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | entry pointer reference retains descriptor location | 216/216 instructions; structural/exact (0, 82); source 5adfa7b003. Restored.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | leading outer and inner index locals | 216/216 instructions; structural/exact (0, 53); source 11ad2cba2a. Restored.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | transform result lifetime declared at function entry | 216/216 instructions; structural/exact (0, 82); source ec1377ac1d. Restored.

### CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv
Origin fetched d94df60412dfa411caa9fd5479e01f0468c644e3; remote source same.
Diagnosis:435/435 instructions and frame0x190 identical; second width inline return f2/f3 exchanged with height loads/stores, all branches exact. Vary forward width/height declaration and operand boundaries.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | width result declaration precedes height temporary | 435/435 instructions; structural/exact (0, 11); source ef62e906eb. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | retain height scalar instead of Size aggregate | 435/435 instructions; structural/exact (325, 429); source e2ed25d8b4. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | explicit forward width helper arguments | 431/435 instructions; structural/exact (11, 180); source 5d94b8adce. Restored.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | const metadata with mutable image view at GX boundary | 100/100 instructions; structural/exact (16, 37); source ceef1e1e18. Restored.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | const metadata with mutable image view at GX boundary | 106/106 instructions; structural/exact (15, 70); source a495998c58. Restored.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | uninitialized declarations assigned before use; range local declared before card query | 90/90 instructions; structural/exact (0, 4); source 05fe63d84d. Kept for gate.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc declaration search after 3 structural trials
declaration block:
      memorycard::CardState* states;
      long command;
start (0, 4)
best (0, 4) after 2 builds; source restored; best order was:
    memorycard::CardState* states;
    long command;

CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | size and width separate declarations | 437/435 instructions; structural/exact (11, 203); source ea64db9737. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | width before size separate declarations | 437/435 instructions; structural/exact (11, 203); source fbdfa53825. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | forward size declared before pane pointers | 437/435 instructions; structural/exact (11, 214); source 218a27844b. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv declaration search after 6 local/helper trials
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl register declaration search after three structural/access trials.

DATA AUDIT src/scene/memoryCard/iplMemoryCardManager: 0/0 matched data bytes in starting live report.

DATA AUDIT src/scene/setting/iplRakuRakuThread: 456/456 matched data bytes in starting live report.
  src .sbss startTimeHigh__Q23ipl5scene offset 0 size 4
  src .sbss startTimeLow__Q23ipl5scene offset 4 size 4
  src .sbss active__Q23ipl5scene offset 8 size 1
  src .sbss messageSlot__Q23ipl5scene offset c size 4
  src .sdata displayState__Q23ipl5scene offset 0 size 4
  src .data @7631 offset 0 size 38
  src .data @7661 offset 38 size 20
  src .bss sRakuAllocator offset 0 size 10
  src .bss sRakuStatus offset 10 size f4
  src .bss sRakuMsgQueue offset 104 size 20
  src .data __vt__Q33ipl5scene14RakuRakuThread offset 58 size 30
  obj .data jumptable_81657BF8 offset 38 size 20
  obj .bss sRakuAllocator offset 0 size 10
  obj .bss sRakuStatus offset 10 size f4
  obj .bss sRakuMsgQueue offset 104 size 20
  obj .data lbl_81657BC0 offset 0 size 38
  obj .data __vt__Q33ipl5scene14RakuRakuThread offset 58 size 30
  obj .sdata displayState__Q23ipl5scene offset 0 size 4
  obj .sbss startTimeHigh__Q23ipl5scene offset 0 size 4
  obj .sbss startTimeLow__Q23ipl5scene offset 4 size 4
  obj .sbss active__Q23ipl5scene offset 8 size 1
  obj .sbss messageSlot__Q23ipl5scene offset c size 4

DATA AUDIT src/keyboard/tiCandidateBox: 4652/4652 matched data bytes in starting live report.
  src .rodata csAninationFile__Q29textinput12candidatebox offset 0 size 374
  src .sdata2 @9923 offset 0 size 4
  src .sdata @9924 offset 20 size 8
  src .sdata @9925 offset 28 size 8
  src .sdata2 @10188 offset 4 size 4
  src .sdata2 @10189 offset 8 size 4
  src .sdata2 @10190 offset c size 4
  src .sdata2 @10191 offset 10 size 4
  src .sdata2 @10192 offset 14 size 4
  src .sdata2 @10340 offset 18 size 4
  src .sdata2 @10341 offset 1c size 4
  src .sdata2 @10342 offset 20 size 4
  src .sdata2 @10343 offset 24 size 4
  src .data @10530 offset 778 size 1c
  src .sdata2 @10578 offset 28 size 4
  src .data @6761 offset 794 size f
  src .data @6762 offset 7a4 size f
  src .data @6763 offset 7b4 size f
  src .data @6764 offset 7c4 size f
  src .data @6765 offset 7d4 size f
  src .data @6766 offset 7e4 size f
  src .data @6767 offset 7f4 size f
  src .data @6768 offset 804 size f
  src .data @6769 offset 814 size f
  src .data @6770 offset 824 size f
  src .data @6771 offset 834 size f
  src .data @6772 offset 844 size f
  src .data @6773 offset 854 size f
  src .data @6774 offset 864 size f
  src .data @6775 offset 874 size f
  src .data @6776 offset 884 size f
  src .data @6777 offset 894 size f
  src .data @6778 offset 8a4 size f
  src .data @6779 offset 8b4 size f
  src .rodata @6780 offset 378 size 50
  src .data @6782 offset 8c4 size f
  src .data @6783 offset 8d4 size f
  src .data @6784 offset 8e4 size f
  src .data @6785 offset 8f4 size f
  src .data @6786 offset 904 size f
  src .data @6787 offset 914 size f
  src .data @6788 offset 924 size f
  src .data @6789 offset 934 size f
  src .data @6790 offset 944 size f
  src .data @6791 offset 954 size f
  src .data @6792 offset 964 size f
  src .data @6793 offset 974 size f
  src .data @6794 offset 984 size f
  src .data @6795 offset 994 size f
  src .data @6796 offset 9a4 size f
  src .data @6797 offset 9b4 size f
  src .data @6798 offset 9c4 size f
  src .data @6799 offset 9d4 size f
  src .data @6800 offset 9e4 size f
  src .data @6801 offset 9f4 size f
  src .rodata @6802 offset 3c8 size 50
  src .data @10601 offset a04 size f
  src .sdata @10793 offset 30 size 2
  src .sdata2 @10794 offset 2c size 4
  src .sdata2 @10795 offset 30 size 4
  src .sdata2 @10799 offset 38 size 8
  src .sdata2 @10942 offset 40 size 8
  src .sdata2 @11059 offset 48 size 4
  src .data scT_prdc_Text_00 offset 0 size f
  src .data scP_prdc_scrl_Left offset 10 size 11
  src .sdata scCommonTextAnimName offset 0 size 4
  src .sdata scCommonScrollAnimName offset 4 size 4
  src .sdata scEmptyWChars offset 8 size 8
  src .sdata scP_OnBtn offset 10 size 8
  src .sdata scB_OnBtn offset 18 size 8
  src .data scCandidatePaneData offset 28 size 68c
  src .data scPaneNameTable offset 6b4 size 84
  src .data scW_predictWindow offset 738 size 10
  src .data scN_predictInput offset 748 size f
  src .data scW_OnOff_Area offset 758 size d
  src .data scN_prdc_Texts offset 768 size d
  src .data __vt__Q39textinput12candidatebox4Base offset cd8 size 54
  src .data __vt__Q39textinput12candidatebox12LayoutByNW4R offset ac8 size 130
  src .data __vt__Q39textinput12candidatebox20CandidateTextAnmPane offset a98 size 2c
  src .data __vt__Q39textinput12candidatebox22CandidateScrollAnmPane offset a6c size 2c
  src .data __vt__Q39textinput12candidatebox12OnOffAnmPane offset a40 size 2c
  src .data __vt__Q39textinput12candidatebox13PredictWindow offset a14 size 2c
  src .data __vt__Q39textinput3gui12EventHandler offset d58 size 18
  src .data __vt__Q39textinput12candidatebox5UIObj offset c98 size 1c
  src .data __vt__Q39textinput4util12AnimObserver offset d70 size c
  src .data __vt__Q39textinput12candidatebox10UITextArea offset c6c size 2c
  src .data __vt__Q39textinput11nw4rmanager11AnmObserver offset d48 size c
  src .data __vt__Q39textinput12candidatebox12UITextWindow offset bf8 size 2c
  src .data __vt__Q39textinput12candidatebox8UIButton offset c50 size 1c
  src .data __vt__Q39textinput12candidatebox13UIOnOffButton offset c24 size 2c
  src .data __vt__Q39textinput12candidatebox12EventHandler offset cb8 size 20
  src .data __vt__Q39textinput12candidatebox18CandidateBoxCaller offset d2c size 1c
  obj .rodata csAninationFile__Q29textinput12candidatebox offset 0 size 374
  obj .rodata lbl_81615658 offset 378 size a0
  obj .data @10530 offset 778 size 1c
  obj .data @6761 offset 794 size f
  obj .data @6762 offset 7a4 size f
  obj .data @6763 offset 7b4 size f
  obj .data @6764 offset 7c4 size f
  obj .data @6765 offset 7d4 size f
  obj .data @6766 offset 7e4 size f
  obj .data @6767 offset 7f4 size f
  obj .data @6768 offset 804 size f
  obj .data @6769 offset 814 size f
  obj .data @6770 offset 824 size f
  obj .data @6771 offset 834 size f
  obj .data @6772 offset 844 size f
  obj .data @6773 offset 854 size f
  obj .data @6774 offset 864 size f
  obj .data @6775 offset 874 size f
  obj .data @6776 offset 884 size f
  obj .data @6777 offset 894 size f
  obj .data @6778 offset 8a4 size f
  obj .data @6779 offset 8b4 size f
  obj .data @6782 offset 8c4 size f
  obj .data @6783 offset 8d4 size f
  obj .data @6784 offset 8e4 size f
  obj .data @6785 offset 8f4 size f
  obj .data @6786 offset 904 size f
  obj .data @6787 offset 914 size f
  obj .data @6788 offset 924 size f
  obj .data @6789 offset 934 size f
  obj .data @6790 offset 944 size f
  obj .data @6791 offset 954 size f
  obj .data @6792 offset 964 size f
  obj .data @6793 offset 974 size f
  obj .data @6794 offset 984 size f
  obj .data @6795 offset 994 size f
  obj .data @6796 offset 9a4 size f
  obj .data @6797 offset 9b4 size f
  obj .data @6798 offset 9c4 size f
  obj .data @6799 offset 9d4 size f
  obj .data @6800 offset 9e4 size f
  obj .data @6801 offset 9f4 size f
  obj .data @10601 offset a04 size f
  obj .data scT_prdc_Text_00 offset 0 size f
  obj .data scP_prdc_scrl_Left offset 10 size 11
  obj .data scCandidatePaneData offset 28 size 68c
  obj .data scPaneNameTable offset 6b4 size 84
  obj .data scW_predictWindow offset 738 size 10
  obj .data scN_predictInput offset 748 size f
  obj .data scW_OnOff_Area offset 758 size d
  obj .data scN_prdc_Texts offset 768 size d
  obj .data __vt__Q39textinput12candidatebox13PredictWindow offset a14 size 2c
  obj .data __vt__Q39textinput12candidatebox12OnOffAnmPane offset a40 size 2c
  obj .data __vt__Q39textinput12candidatebox22CandidateScrollAnmPane offset a6c size 2c
  obj .data __vt__Q39textinput12candidatebox20CandidateTextAnmPane offset a98 size 2c
  obj .data __vt__Q39textinput12candidatebox12LayoutByNW4R offset ac8 size 130
  obj .data __vt__Q39textinput12candidatebox12UITextWindow offset bf8 size 2c
  obj .data __vt__Q39textinput12candidatebox13UIOnOffButton offset c24 size 2c
  obj .data __vt__Q39textinput12candidatebox8UIButton offset c50 size 1c
  obj .data __vt__Q39textinput12candidatebox10UITextArea offset c6c size 2c
  obj .data __vt__Q39textinput12candidatebox5UIObj offset c98 size 1c
  obj .data __vt__Q39textinput12candidatebox12EventHandler offset cb8 size 20
  obj .data __vt__Q39textinput12candidatebox4Base offset cd8 size 54
  obj .data __vt__Q39textinput12candidatebox18CandidateBoxCaller offset d2c size 1c
  obj .data __vt__Q39textinput11nw4rmanager11AnmObserver offset d48 size c
  obj .data __vt__Q39textinput4util12AnimObserver offset d94 size c
  obj .sdata2 lbl_81694D90 offset 0 size 4
  obj .sdata2 lbl_81694D94 offset 4 size 4
  obj .sdata2 lbl_81694D98 offset 8 size 4
  obj .sdata2 lbl_81694D9C offset c size 4
  obj .sdata2 lbl_81694DA0 offset 10 size 4
  obj .sdata2 lbl_81694DA4 offset 14 size 4
  obj .sdata2 lbl_81694DA8 offset 18 size 4
  obj .sdata2 lbl_81694DAC offset 1c size 4
  obj .sdata2 lbl_81694DB0 offset 20 size 4
  obj .sdata2 lbl_81694DB4 offset 24 size 4
  obj .sdata2 lbl_81694DB8 offset 28 size 4
  obj .sdata2 lbl_81694DBC offset 2c size 4
  obj .sdata2 lbl_81694DC0 offset 30 size 4
  obj .sdata2 lbl_81694DC8 offset 38 size 8
  obj .sdata2 lbl_81694DD0 offset 40 size 8
  obj .sdata2 lbl_81694DD8 offset 48 size 4
  obj .sdata scCommonTextAnimName offset 0 size 4
  obj .sdata scCommonScrollAnimName offset 4 size 4
  obj .sdata scEmptyWChars offset 8 size 8
  obj .sdata scP_OnBtn offset 10 size 8
  obj .sdata scB_OnBtn offset 18 size 8
No symbol rename or extent correction is justified: all owned data already reports 100%; memory-card object owns no data sections.
declaration block:
              f32 widthScale = GetWidthScale_();
              f32 margin = GetMargin_();
              f32 xOffset = mfXOffset;

              f32 areaPaneXOffset = mpTextAreaPane->getPane()->GetTranslate().x;
              f32 areaPaneWidth = mpTextAreaPane->getPane()->GetSize().width;
              s32 selectedIdx = GetSelectedTextIdx();
start (0, 11)
best (0, 11) after 52 builds; source restored; best order was:
            f32 widthScale = GetWidthScale_();
            f32 margin = GetMargin_();
            f32 xOffset = mfXOffset;

            f32 areaPaneXOffset = mpTextAreaPane->getPane()->GetTranslate().x;
            f32 areaPaneWidth = mpTextAreaPane->getPane()->GetSize().width;
            s32 selectedIdx = GetSelectedTextIdx();

declaration block:
      CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
      memorycard::CardState* states = memorycard::getCardSlotState();
      u32 file = mFile[slot][index].fileNo;
      memorycard::FileInfo* dir = NULL;
      long result;
      bool enabled = false;
start (0, 2)
best (0, 2) after 36 builds; source restored; best order was:
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    memorycard::CardState* states = memorycard::getCardSlotState();
    u32 file = mFile[slot][index].fileNo;
    memorycard::FileInfo* dir = NULL;
    long result;
    bool enabled = false;

isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | best register declaration order | 118/118 instructions; structural/exact (0, 2); source da18510e24. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl register declaration search after three structural/access trials.
declaration block:
      CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
      memorycard::CardState* states = memorycard::getCardSlotState();
      u32 file = mFile[slot][index].fileNo;
      memorycard::FileInfo* dir = NULL;
      long result;
      bool enabled = false;
start (0, 2)
best (0, 2) after 36 builds; source restored; best order was:
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    memorycard::CardState* states = memorycard::getCardSlotState();
    u32 file = mFile[slot][index].fileNo;
    memorycard::FileInfo* dir = NULL;
    long result;
    bool enabled = false;

isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | best register declaration order | 118/118 instructions; structural/exact (0, 2); source da18510e24. Restored.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi register declaration search after three structural/access trials.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | trim and destination locals declared at entry, each assigned before use | 123/123 instructions; structural/exact (0, 20); source 9e4d9f5456. Kept for gate.
declaration block:
      u32 file;
      const char* comments;
      const u8* encoded;
      char* tail;
      char* end;
      bool found;
      int count;
start (0, 20)
best (0, 20) after 52 builds; source restored; best order was:
    u32 file;
    const char* comments;
    const u8* encoded;
    char* tail;
    char* end;
    bool found;
    int count;

getComment__Q33ipl5scene17MemoryCardManagerFUcsi | best register declaration order | 123/123 instructions; structural/exact (0, 20); source 9e4d9f5456. Restored.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | restore target descriptor loads before register-order search | 216/216 instructions; structural/exact (0, 53); source 11ad2cba2a. Kept for gate.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator declaration search after descriptor structural repair
declaration block:
              u16 i;
              u16 j;
              CandidateTextAnmPane* pane;
start (0, 53)
best (0, 53) after 6 builds; source restored; best order was:
            u16 i;
            u16 j;
            CandidateTextAnmPane* pane;

CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | const forward Size value | 435/435 instructions; structural/exact (0, 11); source 5267f5f5b0. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | forward scaled-width separate result | 435/435 instructions; structural/exact (0, 11); source 574fc79f2b. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | forward height receiver copied before width scaling | 435/435 instructions; structural/exact (12, 21); source b0e9bff7f0. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | forward width getter wrapped in named expression | 435/435 instructions; structural/exact (0, 11); source ab35148b82. Restored.

RAKU STORAGE AUDIT: target start lis/addi relocations at offsets 0x2da/0x2e6 load sRakuAllocator, then offsets 0x10 and 0x1c address status/config; finish uses the same aggregate base. Existing source has three separately addressable objects. Static C-linkage did not merge them. No alias labels, pointer-offset blobs, or artificial data aggregate retained.

FINAL OPEN AUDIT isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 99.830505%; 4 distinct compiled source attempts.
src 0x1d8 base 0x1d8 insns 118/118
diffs 2: [28, 78]
    28 M add r5, r3, r0
       B add r5, r0, r3
    78 M add r5, r3, r0
       B add r5, r0, r3

FINAL OPEN AUDIT isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 99.830505%; 4 distinct compiled source attempts.
src 0x1d8 base 0x1d8 insns 118/118
diffs 2: [28, 78]
    28 M add r5, r3, r0
       B add r5, r0, r3
    78 M add r5, r3, r0
       B add r5, r0, r3

FINAL OPEN AUDIT isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: 92.30769%; 3 distinct compiled source attempts.
src 0x68 base 0x68 insns 26/26
diffs 8: [11, 12, 13, 14, 15, 16, 17, 18]
    11 M addi r11, r1, 0x20
       B add r4, r29, r4
    12 M add r4, r29, r4
       B add r4, r4, r0
    13 M add r4, r4, r0
       B mulli r5, r30, 0x1fc0
    14 M mulli r5, r30, 0x1fc0
       B lwz r4, 8(r4)
    15 M lwz r4, 8(r4)
       B add r0, r3, r5
    16 M add r0, r3, r5
       B slwi r3, r4, 6
    17 M slwi r3, r4, 6
       B lbzx r3, r3, r0
    18 M lbzx r3, r3, r0
       B addi r11, r1, 0x20

FINAL OPEN AUDIT update_file_array__Q33ipl5scene17MemoryCardManagerFUc: 99.72222%; 4 distinct compiled source attempts.
src 0x168 base 0x168 insns 90/90
diffs 4: [15, 16, 17, 20]
    15 M addis r4, r30, 1
       B addis r3, r30, 1
    16 M lwz r3, 0x6934(r4)
       B lwz r4, 0x6934(r3)
    17 M addi r0, r3, -1
       B addi r0, r4, -1
    20 M lwz r0, 0x6930(r4)
       B lwz r0, 0x6930(r3)

FINAL OPEN AUDIT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: 87.55%; 3 distinct compiled source attempts.
src 0x190 base 0x190 insns 100/100
diffs 37: [19, 20, 22, 23, 24, 34, 39, 40, 42, 44, 45, 46, 47, 48, 57, 59, 63, 64, 65, 66]
    19 M mulli r30, r26, 0x1fc0
       B mulli r29, r26, 0x1fc0
    20 M slwi r31, r27, 6
       B slwi r30, r27, 6
    22 M add r0, r31, r3
       B add r0, r3, r29
    23 M add r29, r30, r0
       B add r31, r0, r30
    24 M add r3, r29, r28
       B add r3, r31, r28
    34 M add r3, r29, r0
       B add r3, r31, r0
    39 M add r4, r29, r0
       B add r4, r0, r31
    40 M mulli r26, r27, 0x15c
       B mulli r24, r27, 0x15c
    42 M addi r27, r3, 0x10ec
       B addi r25, r3, 0x10ec
    44 M add r24, r27, r26
       B add r3, r25, r24
    45 M mr r3, r24
       B bl 0
    46 M bl 0
       B add r24, r25, r24
    47 M mr r3, r24
       B li r4, 0
    48 M li r4, 0
       B mr r3, r24
    57 M mullw r28, r26, r4
       B mullw r26, r26, r4
    59 M add r3, r29, r0
       B add r3, r31, r0
    63 M mulli r26, r27, 0x15c
       B add r3, r25, r26
    64 M add r3, r25, r28
       B add r4, r31, r0
    65 M add r4, r29, r0
       B mulli r27, r27, 0x15c
    66 M addi r27, r3, 0x10ec
       B li r7, 9
    67 M li r7, 9
       B addi r28, r3, 0x10ec
    69 M add r3, r27, r26
       B add r3, r28, r27
    73 M add r0, r24, r30
       B add r0, r24, r29
    74 M add r4, r25, r28
       B add r4, r25, r26
    75 M add r3, r0, r31
       B add r3, r0, r30
    77 M add r4, r4, r26
       B lwz r0, 0x3c(r3)
    78 M lwz r0, 0x3c(r3)
       B addi r24, r4, 0x112c
    79 M addi r24, r4, 0x112c
       B add r3, r24, r27
    81 M mr r3, r24
       B add r4, r31, r0
    82 M add r4, r29, r0
       B bl 0
    83 M bl 0
       B add r3, r24, r27
    84 M mr r3, r24
       B li r4, 0
    85 M li r4, 0
       B bl 0
    86 M bl 0
       B add r24, r28, r27
    87 M add r3, r27, r26
       B li r4, 0
    88 M li r4, 0
       B mr r3, r24
    93 M add r3, r27, r26
       B mr r3, r24

FINAL OPEN AUDIT getComment__Q33ipl5scene17MemoryCardManagerFUcsi: 98.94309%; 4 distinct compiled source attempts.
src 0x1ec base 0x1ec insns 123/123
diffs 20: [10, 12, 14, 19, 20, 21, 23, 24, 45, 46, 48, 49, 51, 62, 66, 67, 86, 90, 91, 117]
    10 M mr r27, r3
       B mr r26, r3
    12 M slwi r28, r6, 7
       B slwi r27, r6, 7
    14 M mullw r30, r4, r0
       B mullw r29, r4, r0
    19 M mulli r29, r25, 0x15c
       B mulli r28, r25, 0x15c
    20 M add r0, r3, r30
       B add r0, r3, r29
    21 M add r3, r0, r29
       B add r3, r0, r28
    23 M add r26, r31, r28
       B add r30, r31, r27
    24 M mr r3, r26
       B mr r3, r30
    45 M mr r5, r4
       B mr r3, r4
    46 M li r3, 0
       B li r5, 0
    48 M stb r3, 0(r4)
       B stb r5, 0(r4)
    49 M addi r5, r5, -1
       B addi r3, r3, -1
    51 M lbz r0, 0(r5)
       B lbz r0, 0(r3)
    62 M mr r3, r26
       B mr r3, r30
    66 M add r3, r27, r30
       B add r3, r26, r29
    67 M add r0, r28, r29
       B add r0, r27, r28
    86 M mr r3, r26
       B mr r3, r30
    90 M add r3, r27, r30
       B add r3, r26, r29
    91 M add r0, r28, r29
       B add r0, r27, r28
   117 M add r3, r31, r28
       B add r3, r31, r27

FINAL OPEN AUDIT create_banner__Q33ipl5scene17MemoryCardManagerFUcs: 90.42453%; 3 distinct compiled source attempts.
src 0x1a8 base 0x1a8 insns 106/106
diffs 70: [5, 6, 9, 11, 14, 16, 17, 18, 19, 23, 24, 25, 26, 27, 32, 33, 34, 35, 36, 37]
     5 M mr r27, r3
       B mr r26, r3
     6 M mr r28, r4
       B mr r27, r4
     9 M mr r30, r3
       B mr r25, r3
    11 M mulli r4, r28, 0x7f0
       B mulli r4, r27, 0x7f0
    14 M add r4, r27, r4
       B add r4, r26, r4
    16 M lwz r29, 8(r4)
       B lwz r28, 8(r4)
    17 M mulli r0, r28, 0x5f4
       B mulli r0, r27, 0x5f4
    18 M mulli r4, r29, 0xc
       B mulli r4, r28, 0xc
    19 M add r0, r30, r0
       B add r0, r25, r0
    23 M mulli r25, r28, 0x1fc0
       B mulli r29, r27, 0x1fc0
    24 M slwi r26, r29, 6
       B slwi r30, r28, 6
    25 M add r0, r26, r3
       B add r0, r30, r3
    26 M add r30, r25, r0
       B add r4, r29, r0
    27 M lbzx r0, r25, r0
       B lbzx r0, r29, r0
    32 M lbz r0, 3(r30)
       B add r0, r3, r29
    33 M cmpwi r0, 5
       B add r25, r0, r30
    34 M bne 88
       B lbz r0, 3(r25)
    35 M lis r3, 1
       B cmpwi r0, 5
    36 M lwz r0, 0x14(r30)
       B bne 84
    37 M addi r3, r3, -0x535c
       B lis r3, 1
    38 M li r5, 0x60
       B lwz r0, 0x14(r25)
    39 M mullw r3, r28, r3
       B addi r3, r3, -0x535c
    40 M add r4, r30, r0
       B li r5, 0x60
    41 M li r6, 0x20
       B mullw r3, r27, r3
    42 M li r7, 5
       B add r4, r4, r0
    43 M li r8, 0
       B li r6, 0x20
    44 M li r9, 0
       B li r7, 5
    45 M mulli r0, r29, 0x15c
       B li r8, 0
    46 M add r3, r27, r3
       B li r9, 0
    47 M li r10, 0
       B add r3, r26, r3
    48 M add r3, r3, r0
       B li r10, 0
    49 M addi r25, r3, 0x110c
       B mulli r25, r28, 0x15c
    50 M mr r3, r25
       B addi r29, r3, 0x110c
    51 M bl 0
       B add r3, r29, r25
    52 M mr r3, r25
       B bl 0
    53 M li r4, 0
       B add r3, r29, r25
    54 M bl 0
       B li r4, 0
    55 M b 152
       B bl 0
    56 M cmpwi r0, 9
       B b 148
    57 M bne 144
       B cmpwi r0, 9
    58 M lis r3, 1
       B bne 140
    59 M li r0, 0
       B lis r3, 1
    60 M addi r3, r3, -0x535c
       B li r0, 0
    61 M stw r0, 8(r1)
       B addi r3, r3, -0x535c
    62 M mullw r23, r28, r3
       B stw r0, 8(r1)
    63 M li r5, 0x60
       B mullw r23, r27, r3
    64 M lwz r0, 0x14(r30)
       B li r5, 0x60
    65 M li r6, 0x20
       B lwz r0, 0x14(r25)
    66 M li r7, 9
       B li r6, 0x20
    67 M add r4, r30, r0
       B li r7, 9
    68 M add r3, r27, r23
       B add r4, r25, r0
    69 M li r8, 0
       B add r3, r26, r23
    70 M mulli r24, r29, 0x15c
       B li r8, 0
    71 M li r9, 0
       B mulli r24, r28, 0x15c
    72 M addi r22, r3, 0x110c
       B li r9, 0
    73 M li r10, 0
       B addi r22, r3, 0x110c
    74 M add r3, r22, r24
       B li r10, 0
    75 M bl 0
       B add r3, r22, r24
    76 M add r0, r31, r25
       B bl 0
    77 M add r4, r27, r23
       B add r0, r31, r29
    78 M add r3, r0, r26
       B add r4, r26, r23
    79 M li r5, 2
       B add r3, r0, r30
    80 M add r4, r4, r24
       B li r5, 2
    83 M li r6, 0x100
       B add r3, r23, r24
    84 M mr r3, r23
       B li r6, 0x100
    85 M add r4, r30, r0
       B add r4, r25, r0
    87 M mr r3, r23
       B add r3, r23, r24
    95 M mullw r3, r28, r0
       B mullw r3, r27, r0
    96 M mulli r0, r29, 0x15c
       B mulli r0, r28, 0x15c
    97 M add r3, r27, r3
       B add r3, r26, r3

FINAL OPEN AUDIT getBlocks__Q33ipl5scene17MemoryCardManagerFUcs: 92.0%; 3 distinct compiled source attempts.
src 0x64 base 0x64 insns 25/25
diffs 9: [11, 12, 13, 14, 15, 16, 17, 18, 19]
    11 M addi r11, r1, 0x20
       B add r4, r29, r4
    12 M add r4, r29, r4
       B add r4, r4, r0
    13 M add r4, r4, r0
       B lwz r0, 8(r4)
    14 M lwz r0, 8(r4)
       B mulli r4, r30, 0x5f4
    15 M mulli r4, r30, 0x5f4
       B mulli r0, r0, 0xc
    16 M mulli r0, r0, 0xc
       B add r3, r3, r4
    17 M add r3, r3, r4
       B add r3, r3, r0
    18 M add r3, r3, r0
       B lhz r3, 2(r3)
    19 M lhz r3, 2(r3)
       B addi r11, r1, 0x20

FINAL OPEN AUDIT start__Q33ipl5scene14RakuRakuThreadFv: 88.635414%; 3 distinct compiled source attempts.
src 0x184 base 0x180 insns 97/96
--- insert mine 6:6 base 6:7
  B    6 lis r30, 0
--- insert mine 8:8 base 9:10
  B    9 addi r30, r30, 0
--- replace mine 13:14 base 15:16
  M   13 b 312
  B   15 b 300
--- insert mine 23:23 base 25:26
  B   25 stw r3, 0x344(r28)
--- replace mine 24:26 base 27:28
  M   24 stw r3, 0x344(r28)
  M   25 lis r3, 0
  B   27 addi r3, r30, 0
--- delete mine 27:28 base 29:29
  M   27 addi r3, r3, 0
--- replace mine 32:33 base 33:34
  M   32 lis r31, 0
  B   33 li r31, 1
--- delete mine 34:36 base 35:35
  M   34 li r30, 1
  M   35 addi r31, r31, 0
--- replace mine 37:39 base 36:37
  M   37 stb r30, 0(0)
  M   38 addi r3, r31, 0xc
  B   36 addi r3, r30, 0x1c
--- insert mine 40:40 base 38:39
  B   38 stb r31, 0(0)
--- replace mine 43:44 base 42:43
  M   43 mr r3, r31
  B   42 addi r3, r30, 0x10
--- replace mine 68:69 base 67:68
  M   68 stw r30, 0x334(r28)
  B   67 stw r31, 0x334(r28)

FINAL OPEN AUDIT finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi: 86.56391%; 3 distinct compiled source attempts.
src 0x21c base 0x214 insns 135/133
--- replace mine 0:1 base 0:1
  M    0 stwu r1, -0x20(r1)
  B    0 stwu r1, -0x30(r1)
--- replace mine 2:4 base 2:4
  M    2 stw r0, 0x24(r1)
  M    3 addi r11, r1, 0x20
  B    2 stw r0, 0x34(r1)
  B    3 addi r11, r1, 0x30
--- replace mine 6:7 base 6:8
  M    6 mr r26, r3
  B    6 lis r31, 0
  B    7 mr r25, r3
--- insert mine 8:8 base 9:10
  B    9 cmpwi r0, 0
--- replace mine 9:10 base 11:12
  M    9 cmpwi r0, 0
  B   11 addi r31, r31, 0
--- replace mine 16:19 base 18:20
  M   16 b 452
  M   17 lis r27, 0
  M   18 lwz r4, 0(r27)
  B   18 b 436
  B   19 lwz r4, 0x10(r31)
--- replace mine 21:24 base 22:23
  M   21 ble 12
  M   22 li r3, 0
  M   23 b 424
  B   22 bgt 88
--- replace mine 26:27 base 25:26
  M   26 bne 60
  B   25 bne 52
--- replace mine 28:31 base 27:29
  M   28 bne 24
  M   29 addi r3, r27, 0
  M   30 addi r3, r3, 0xc
  B   27 bne 20
  B   28 addi r3, r31, 0x1c
--- replace mine 32:33 base 30:31
  M   32 mr r3, r26
  B   30 mr r3, r25
--- replace mine 34:35 base 32:33
  M   34 lis r3, 0
  B   32 addi r3, r31, 0x104
--- delete mine 36:37 base 34:34
  M   36 addi r3, r3, 0
--- replace mine 40:41 base 37:38
  M   40 b 356
  B   37 b 360
--- replace mine 43:44 base 40:41
  M   43 mr r3, r26
  B   40 mr r3, r25
--- insert mine 46:46 base 43:46
  B   43 b 12
  B   44 li r3, 0
  B   45 b 328
--- replace mine 47:49 base 47:48
  M   47 beq 300
  M   48 addi r4, r27, 0
  B   47 beq 296
--- replace mine 50:51 base 49:50
  M   50 addi r31, r4, 0xc
  B   49 addi r4, r31, 0x1c
--- delete mine 52:53 base 51:51
  M   52 mr r4, r31
--- replace mine 54:55 base 52:53
  M   54 mr r3, r31
  B   52 addi r3, r31, 0x1c
--- replace mine 57:58 base 55:57
  M   57 lwz r0, 0x20(r31)
  B   55 addi r26, r31, 0x1c
  B   56 lwz r0, 0x20(r26)
--- replace mine 61:62 base 60:61
  M   61 li r26, 0
  B   60 li r25, 0
--- replace mine 64:65 base 63:64
  M   64 lwz r0, 0x24(r31)
  B   63 lwz r0, 0x24(r26)
--- replace mine 67:68 base 66:67
  M   67 add r4, r31, r27
  B   66 add r4, r26, r27
--- replace mine 72:73 base 71:72
  M   72 addi r26, r26, 1
  B   71 addi r25, r25, 1
--- replace mine 74:75 base 73:74
  M   74 cmpwi r26, 4
  B   73 cmpwi r25, 4
--- replace mine 81:82 base 80:81
  M   81 li r26, 0
  B   80 li r25, 0
--- replace mine 85:86 base 84:85
  M   85 lwz r0, 0x24(r31)
  B   84 lwz r0, 0x24(r26)
--- replace mine 88:89 base 87:88
  M   88 add r4, r31, r28
  B   87 add r4, r26, r28
--- replace mine 93:94 base 92:93
  M   93 addi r26, r26, 1
  B   92 addi r25, r25, 1
--- replace mine 95:96 base 94:95
  M   95 cmpwi r26, 4
  B   94 cmpwi r25, 4
--- replace mine 104:105 base 103:104
  M  104 addi r4, r31, 0xa8
  B  103 addi r4, r26, 0xa8
--- replace mine 107:108 base 106:107
  M  107 addi r3, r31, 0xa8
  B  106 addi r3, r26, 0xa8
--- replace mine 116:117 base 115:116
  M  116 addi r4, r31, 0xa8
  B  115 addi r4, r26, 0xa8
--- replace mine 119:120 base 118:119
  M  119 addi r3, r31, 0xa8
  B  118 addi r3, r26, 0xa8
--- replace mine 123:126 base 122:124
  M  123 beq 20
  M  124 lis r3, 0
  M  125 addi r3, r3, 0
  B  122 beq 16
  B  123 addi r3, r31, 0x10
--- replace mine 129:130 base 127:128
  M  129 addi r11, r1, 0x20
  B  127 addi r11, r1, 0x30
--- replace mine 131:132 base 129:130
  M  131 lwz r0, 0x24(r1)
  B  129 lwz r0, 0x34(r1)
--- replace mine 133:134 base 131:132
  M  133 addi r1, r1, 0x20
  B  131 addi r1, r1, 0x30

FINAL OPEN AUDIT create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator: 92.71023%; 3 distinct compiled source attempts.
src 0x57c base 0x580 insns 351/352
--- replace mine 5:6 base 5:6
  M    5 lis r29, 0
  B    5 lis r30, 0
--- replace mine 10:11 base 10:11
  M   10 addi r29, r29, 0
  B   10 addi r30, r30, 0
--- replace mine 29:30 base 29:30
  M   29 mr r30, r3
  B   29 mr r26, r3
--- replace mine 49:51 base 49:51
  M   49 stw r30, 0xe0(r31)
  M   50 mr r3, r30
  B   49 stw r26, 0xe0(r31)
  B   50 mr r3, r26
--- replace mine 52:53 base 52:53
  M   52 lwz r12, 0(r30)
  B   52 lwz r12, 0(r26)
--- replace mine 77:79 base 77:79
  M   77 li r28, 0
  M   78 li r30, 0
  B   77 mr r26, r31
  B   78 li r29, 0
--- replace mine 80:81 base 80:81
  M   80 add r3, r31, r30
  B   80 lwz r3, 0x11c(r26)
--- delete mine 82:83 base 82:82
  M   82 lwz r3, 0x11c(r3)
--- replace mine 89:90 base 88:89
  M   89 add r3, r31, r30
  B   88 lwz r3, 0x16c(r26)
--- delete mine 91:92 base 90:90
  M   91 lwz r3, 0x16c(r3)
--- replace mine 96:100 base 94:98
  M   96 addi r28, r28, 1
  M   97 addi r30, r30, 4
  M   98 cmplwi r28, 0x14
  M   99 blt -76
  B   94 addi r29, r29, 1
  B   95 addi r26, r26, 4
  B   96 cmplwi r29, 0x14
  B   97 blt -68
--- replace mine 111:112 base 109:110
  M  111 mr r28, r3
  B  109 mr r29, r3
--- replace mine 115:116 base 113:114
  M  115 mr r3, r28
  B  113 mr r3, r29
--- replace mine 126:129 base 124:126
  M  126 addi r30, r29, 0x28
  M  127 mr r3, r28
  M  128 addi r4, r30, 0x680
  B  124 mr r3, r29
  B  125 addi r4, r30, 0x6a8
--- replace mine 131:133 base 128:130
  M  131 mr r3, r28
  M  132 addi r4, r29, 0x6b4
  B  128 mr r3, r29
  B  129 addi r4, r30, 0x6b4
--- replace mine 136:137 base 133:134
  M  136 addi r4, r30, 0x680
  B  133 addi r4, r30, 0x6a8
--- replace mine 148:149 base 145:146
  M  148 addi r4, r30, 0x680
  B  145 addi r4, r30, 0x6a8
--- replace mine 167:169 base 164:165
  M  167 addi r30, r29, 0x6b4
  M  168 addi r4, r30, 0xc
  B  164 addi r4, r30, 0x6c0
--- replace mine 187:188 base 183:184
  M  187 addi r4, r30, 0x18
  B  183 addi r4, r30, 0x6cc
--- replace mine 225:226 base 221:222
  M  225 addi r4, r30, 0x24
  B  221 addi r4, r30, 0x6d8
--- replace mine 256:257 base 252:255
  M  256 mr r27, r31
  B  252 mr r26, r31
  B  253 addi r28, r30, 0x6e4
  B  254 addi r29, r30, 0x6f8
--- replace mine 258:261 base 256:259
  M  258 addi r27, r31, 0x24
  M  259 lwz r12, 0(r27)
  M  260 mr r3, r27
  B  256 addi r26, r31, 0x24
  B  257 lwz r12, 0(r26)
  B  258 mr r3, r26
--- replace mine 264:266 base 262:264
  M  264 mr r28, r3
  M  265 addi r4, r30, 0x44
  B  262 mr r27, r3
  B  263 mr r4, r29
--- replace mine 268:270 base 266:268
  M  268 mr r3, r28
  M  269 addi r4, r30, 0x30
  B  266 mr r3, r27
  B  267 mr r4, r28
--- replace mine 272:275 base 270:273
  M  272 mr r3, r27
  M  273 addi r4, r30, 0x44
  M  274 lwz r12, 0(r27)
  B  270 mr r3, r26
  B  271 mr r4, r29
  B  272 lwz r12, 0(r26)
--- replace mine 282:283 base 280:282
  M  282 mr r27, r31
  B  280 mr r26, r31
  B  281 addi r28, r30, 0x70c
--- insert mine 284:284 base 283:284
  B  283 addi r27, r30, 0x720
--- replace mine 285:288 base 285:288
  M  285 addi r27, r31, 0x24
  M  286 lwz r12, 0(r27)
  M  287 mr r3, r27
  B  285 addi r26, r31, 0x24
  B  286 lwz r12, 0(r26)
  B  287 mr r3, r26
--- replace mine 291:293 base 291:293
  M  291 mr r28, r3
  M  292 addi r4, r30, 0x6c
  B  291 mr r29, r3
  B  292 mr r4, r27
--- replace mine 295:297 base 295:297
  M  295 mr r3, r28
  M  296 addi r4, r30, 0x58
  B  295 mr r3, r29
  B  296 mr r4, r28
--- replace mine 299:302 base 299:302
  M  299 mr r3, r27
  M  300 addi r4, r30, 0x6c
  M  301 lwz r12, 0(r27)
  B  299 mr r3, r26
  B  300 mr r4, r27
  B  301 lwz r12, 0(r26)
--- replace mine 322:323 base 322:324
  M  322 mr r27, r31
  B  322 mr r26, r31
  B  323 addi r27, r30, 0x738
--- replace mine 324:327 base 325:328
  M  324 addi r27, r31, 0x24
  M  325 lwz r12, 0(r27)
  M  326 mr r3, r27
  B  325 addi r26, r31, 0x24
  B  326 lwz r12, 0(r26)
  B  327 mr r3, r26
--- replace mine 330:331 base 331:332
  M  330 addi r4, r29, 0x738
  B  331 mr r4, r27
--- replace mine 333:336 base 334:337
  M  333 mr r3, r27
  M  334 addi r4, r29, 0x738
  M  335 lwz r12, 0(r27)
  B  334 mr r3, r26
  B  335 mr r4, r27
  B  336 lwz r12, 0(r26)

FINAL OPEN AUDIT createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator: 96.56481%; 3 distinct compiled source attempts.
src 0x358 base 0x360 insns 214/216
--- insert mine 5:5 base 5:8
  B    5 lis r25, 0
  B    6 lis r27, 0
  B    7 lis r28, 0
--- delete mine 6:10 base 9:9
  M    6 lis r26, 0
  M    7 lis r27, 0
  M    8 lis r23, 0
  M    9 lis r28, 0
--- insert mine 11:11 base 10:11
  B   10 lis r30, 0
--- insert mine 14:14 base 14:17
  B   14 addi r25, r25, 0
  B   15 addi r27, r27, 0
  B   16 addi r28, r28, 0
--- delete mine 15:19 base 18:18
  M   15 addi r26, r26, 0
  M   16 addi r27, r27, 0
  M   17 addi r23, r23, 0
  M   18 addi r28, r28, 0
--- insert mine 20:20 base 19:20
  B   19 addi r30, r30, 0
--- replace mine 21:22 base 21:22
  M   21 li r25, 0
  B   21 li r26, 0
--- replace mine 23:26 base 23:26
  M   23 li r22, 0
  M   24 add r20, r23, r0
  M   25 lwzx r0, r23, r0
  B   23 li r19, 0
  B   24 add r20, r24, r0
  B   25 lwzx r0, r24, r0
--- replace mine 40:41 base 40:41
  M   40 mr r22, r3
  B   40 mr r19, r3
--- replace mine 48:49 base 48:49
  M   48 stw r24, 0(r22)
  B   48 stw r25, 0(r19)
--- replace mine 50:54 base 50:54
  M   50 stw r3, 4(r22)
  M   51 addi r3, r22, 8
  M   52 stw r25, 0x14(r22)
  M   53 stw r25, 0x18(r22)
  B   50 stw r3, 4(r19)
  B   51 addi r3, r19, 8
  B   52 stw r26, 0x14(r19)
  B   53 stw r26, 0x18(r19)
--- replace mine 55:59 base 55:59
  M   55 stw r26, 0(r22)
  M   56 mr r3, r22
  M   57 stw r25, 0x2c(r22)
  M   58 lwz r12, 0(r22)
  B   55 stw r27, 0(r19)
  B   56 mr r3, r19
  B   57 stw r26, 0x2c(r19)
  B   58 lwz r12, 0(r19)
--- replace mine 62:64 base 62:64
  M   62 stw r27, 0(r22)
  M   63 stw r25, 0x30(r22)
  B   62 stw r28, 0(r19)
  B   63 stw r26, 0x30(r19)
--- replace mine 69:70 base 69:70
  M   69 mr r22, r3
  B   69 mr r19, r3
--- replace mine 77:78 base 77:78
  M   77 stw r24, 0(r22)
  B   77 stw r25, 0(r19)
--- replace mine 79:83 base 79:83
  M   79 stw r3, 4(r22)
  M   80 addi r3, r22, 8
  M   81 stw r25, 0x14(r22)
  M   82 stw r25, 0x18(r22)
  B   79 stw r3, 4(r19)
  B   80 addi r3, r19, 8
  B   81 stw r26, 0x14(r19)
  B   82 stw r26, 0x18(r19)
--- replace mine 84:88 base 84:88
  M   84 stw r26, 0(r22)
  M   85 mr r3, r22
  M   86 stw r25, 0x2c(r22)
  M   87 lwz r12, 0(r22)
  B   84 stw r27, 0(r19)
  B   85 mr r3, r19
  B   86 stw r26, 0x2c(r19)
  B   87 lwz r12, 0(r19)
--- replace mine 91:92 base 91:92
  M   91 stw r14, 0x30(r22)
  B   91 stw r14, 0x30(r19)
--- replace mine 97:98 base 97:98
  M   97 mr r22, r3
  B   97 mr r19, r3
--- replace mine 105:106 base 105:106
  M  105 stw r24, 0(r22)
  B  105 stw r25, 0(r19)
--- replace mine 108:112 base 108:112
  M  108 stw r3, 4(r22)
  M  109 addi r3, r22, 8
  M  110 stw r25, 0x14(r22)
  M  111 stw r0, 0x18(r22)
  B  108 stw r3, 4(r19)
  B  109 addi r3, r19, 8
  B  110 stw r26, 0x14(r19)
  B  111 stw r0, 0x18(r19)
--- replace mine 113:117 base 113:117
  M  113 stw r26, 0(r22)
  M  114 mr r3, r22
  M  115 stw r25, 0x2c(r22)
  M  116 lwz r12, 0(r22)
  B  113 stw r27, 0(r19)
  B  114 mr r3, r19
  B  115 stw r26, 0x2c(r19)
  B  116 lwz r12, 0(r19)
--- replace mine 120:121 base 120:121
  M  120 stw r28, 0(r22)
  B  120 stw r29, 0(r19)
--- replace mine 122:123 base 122:123
  M  122 stw r0, 0x30(r22)
  B  122 stw r0, 0x30(r19)
--- replace mine 128:129 base 128:129
  M  128 mr r22, r3
  B  128 mr r19, r3
--- replace mine 136:137 base 136:137
  M  136 stw r24, 0(r22)
  B  136 stw r25, 0(r19)
--- replace mine 139:143 base 139:143
  M  139 stw r3, 4(r22)
  M  140 addi r3, r22, 8
  M  141 stw r25, 0x14(r22)
  M  142 stw r0, 0x18(r22)
  B  139 stw r3, 4(r19)
  B  140 addi r3, r19, 8
  B  141 stw r26, 0x14(r19)
  B  142 stw r0, 0x18(r19)
--- replace mine 144:148 base 144:148
  M  144 stw r26, 0(r22)
  M  145 mr r3, r22
  M  146 stw r25, 0x2c(r22)
  M  147 lwz r12, 0(r22)
  B  144 stw r27, 0(r19)
  B  145 mr r3, r19
  B  146 stw r26, 0x2c(r19)
  B  147 lwz r12, 0(r19)
--- replace mine 151:152 base 151:152
  M  151 stw r29, 0(r22)
  B  151 stw r30, 0(r19)
--- replace mine 153:155 base 153:155
  M  153 stw r0, 0x30(r22)
  M  154 mr r4, r22
  B  153 stw r0, 0x30(r19)
  B  154 mr r4, r19
--- replace mine 157:159 base 157:159
  M  157 lwz r30, 0x1c(r20)
  M  158 li r19, 0
  B  157 lwz r22, 0x1c(r20)
  B  158 li r18, 0
--- replace mine 160:161 base 160:161
  M  160 b 168
  B  160 b 176
--- replace mine 162:164 base 162:164
  M  162 rlwinm r0, r19, 2, 0xe, 0x1d
  M  163 add r5, r20, r0
  B  162 rlwinm r0, r18, 2, 0xe, 0x1d
  B  163 add r23, r20, r0
--- replace mine 167:168 base 167:168
  M  167 lwz r18, 0x20(r5)
  B  167 lwz r5, 0x20(r23)
--- replace mine 169:170 base 169:170
  M  169 addi r5, r18, 4
  B  169 addi r5, r5, 4
--- replace mine 184:185 base 184:185
  M  184 cmpwi r30, 0
  B  184 cmpwi r22, 0
--- replace mine 186:189 base 186:189
  M  186 bne 32
  M  187 lwz r5, 0(r18)
  M  188 mr r3, r22
  B  186 bne 36
  B  187 lwz r5, 0x20(r23)
  B  188 mr r3, r19
--- insert mine 191:191 base 191:192
  B  191 lwz r5, 0(r5)
--- replace mine 193:196 base 194:197
  M  193 b 32
  M  194 lwz r5, 0(r18)
  M  195 mr r3, r22
  B  194 b 36
  B  195 lwz r5, 0x20(r23)
  B  196 mr r3, r19
--- replace mine 197:198 base 198:200
  M  197 mr r7, r30
  B  198 mr r7, r22
  B  199 lwz r5, 0(r5)
--- replace mine 201:203 base 203:205
  M  201 addi r19, r19, 1
  M  202 clrlwi r0, r19, 0x10
  B  203 addi r18, r18, 1
  B  204 clrlwi r0, r18, 0x10
--- replace mine 204:205 base 206:207
  M  204 blt -172
  B  206 blt -180
--- replace mine 207:208 base 209:210
  M  207 blt -740
  B  209 blt -748

FINAL OPEN AUDIT CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv: 99.873566%; 10 distinct compiled source attempts.
src 0x6cc base 0x6cc insns 435/435
diffs 11: [264, 269, 304, 305, 306, 307, 310, 313, 316, 322, 324]
   264 M lfs f2, 0(0)
       B lfs f3, 0(0)
   269 M lfs f2, 0(0)
       B lfs f3, 0(0)
   304 M fadds f2, f22, f0
       B fadds f3, f22, f0
   305 M frsp f1, f2
       B frsp f1, f3
   306 M lfs f3, 0x54(r1)
       B lfs f2, 0x54(r1)
   307 M fmuls f23, f2, f29
       B fmuls f23, f3, f29
   310 M stfs f2, 0x20(r1)
       B stfs f3, 0x20(r1)
   313 M stfs f3, 0x50(r22)
       B stfs f2, 0x50(r22)
   316 M stfs f3, 0x50(r23)
       B stfs f2, 0x50(r23)
   322 M stfs f3, 0x24(r1)
       B stfs f2, 0x24(r1)
   324 M stfs f3, 0x1c(r1)
       B stfs f2, 0x1c(r1)

FINAL FULL GATE: GATE PASS; full build ok; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d; 0 regressions; 0 forbidden/readability additions. No retained code/data change or improvement; no commit.
Instruction-exact counts reported by gate before/after are 18->18,12->12,108->108. Objdiff counts are 18->18,12->12,109->109. The candidate-box discrepancy is an odiff conditional-branch normalization bug: onGUIEvent is 1800/1800 raw-byte-identical, including instructions251 40840180 and268 41850018. odiff reads the first operand as an immediate even when it is a CR field and subtracts differing object addresses. Tools were not modified. This is already-matching code; no tuning justified.
Final full gate output is rt8.final-gate.txt. All 13 actually nonmatching functions have >=3 distinct compiled attempts; 55 scored experiment entries and184 declaration-search builds. Data unchanged at100% in both units with data, memory-card has no owned data.

# HIGH round rt8b
Fresh branch agent/w1002/sol-rt8b-high, HEAD bdd15186. Previous medium experiments retained as history. All new attempts prefixed HIGH. Start with move/copy operand order. No source-level gain from previous round is assumed.

### isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl
Origin fetched bdd15186a7a7ead832da3fc5e2688bf0552a4b4f; remote source same.
HIGH diagnosis: stack/branch/lifetime/instruction counts identical, only commuted row+column add. Test subtraction/addition AST and inline helper operand ownership before register search.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH two pointer assignments in permission predicate | 118/118 instructions; structural/exact (0, 2); source 157d69d41b. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH pointer subtracts signed negated index | 120/118 instructions; structural/exact (9, 96); source 10a4a7a865. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH row pointer minus unsigned reverse index | 120/118 instructions; structural/exact (9, 96); source 4df745269e. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH signed array index | 118/118 instructions; structural/exact (0, 2); source fa08fae970. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH directory array reference | 118/118 instructions; structural/exact (6, 8); source 95600b98cd. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH row/file helper receiver first | 118/118 instructions; structural/exact (0, 2); source 4512eb6920. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH row/file helper file first | 118/118 instructions; structural/exact (0, 2); source 06eb4a4067. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH nested slot helper | 118/118 instructions; structural/exact (0, 2); source dd438f3290. Restored.
isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH slot helper receiver last | 118/118 instructions; structural/exact (0, 2); source 7e514ad9fc. Restored.

### isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl
Origin fetched bdd15186a7a7ead832da3fc5e2688bf0552a4b4f; remote source same.
HIGH diagnosis: stack/branch/lifetime/instruction counts identical, only commuted row+column add. Test subtraction/addition AST and inline helper operand ownership before register search.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH two pointer assignments in permission predicate | 118/118 instructions; structural/exact (0, 2); source e2faa4e8e1. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH pointer subtracts signed negated index | 120/118 instructions; structural/exact (9, 96); source 7c4ac97d76. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH row pointer minus unsigned reverse index | 120/118 instructions; structural/exact (9, 96); source 83f33ad5a7. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH signed array index | 118/118 instructions; structural/exact (0, 2); source 0624e22b1b. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH directory array reference | 118/118 instructions; structural/exact (6, 8); source 4ef7a3a754. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH row/file helper receiver first | 118/118 instructions; structural/exact (0, 2); source 246e73f8a7. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH row/file helper file first | 118/118 instructions; structural/exact (0, 2); source d5d087a16b. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH nested slot helper | 118/118 instructions; structural/exact (0, 2); source 3a929bf973. Restored.
isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH slot helper receiver last | 118/118 instructions; structural/exact (0, 2); source 60905b1c4f. Restored.

### update_file_array__Q33ipl5scene17MemoryCardManagerFUc
Origin fetched bdd15186a7a7ead832da3fc5e2688bf0552a4b4f; remote source same.
HIGH pool identical. Diagnosis: same90insns/0x10frame, exact branch/load/call scheduling; only address base r3 vs r4 and command r4 vs r3. Try signed-type boundary, range expression, inline observer boundary, member pointer lifetime.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | HIGH native member-width command | 90/90 instructions; structural/exact (0, 4); source 4b067642f7. Restored.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | HIGH unsigned increment range | 90/90 instructions; structural/exact (0, 4); source 07d21ca7db. Restored.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | HIGH addressable command member | 90/90 instructions; structural/exact (0, 4); source 43f1c43ca2. Restored.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | HIGH two-state member receiver | 90/90 instructions; structural/exact (0, 4); source ea7d22cfeb. Restored.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | HIGH explicit command subtraction signed temporary | 90/90 instructions; structural/exact (0, 4); source f1677ad2a8. Restored.
update_file_array__Q33ipl5scene17MemoryCardManagerFUc | HIGH pre-subtracted range with exact upper bound | 90/90 instructions; structural/exact (0, 4); source e1fc1af7de. Restored.

### start__Q33ipl5scene14RakuRakuThreadFv
Origin fetched bdd15186a7a7ead832da3fc5e2688bf0552a4b4f; remote source same.
HIGH pool first: identical. Structural diagnosis: target start addresses allocator/status/config as three independent objects through one BSS base. Source artificial RakuStatus bundles progress+C-byte offset configuration into one object, so only two distinct objects accessed. SDK callback/get-result types prove independent C-byte progress and E8-byte configuration. Test genuine object separation, no padding or aliases.
start__Q33ipl5scene14RakuRakuThreadFv | HIGH split real progress and configuration objects | 96/96 instructions; structural/exact (0, 0); source f5d83a0eba. Restored.

### isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs
Origin fetched 786a2dd3e8e0c8139026493f29a06e5aa5a93fc6; remote source same.
HIGH diagnosis: target keeps r11 epilogue preparation after final load, source hoists it earlier; identical instruction count/frame. Test pointer/reference boundary and inline scalar accessor.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | HIGH icon row reference | 26/26 instructions; structural/exact (2, 8); source b9b4b29367. Restored.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | HIGH flag pointer return | 26/26 instructions; structural/exact (2, 8); source 3b08fc61e6. Restored.
isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs | HIGH separate row pointer and column advance | 26/26 instructions; structural/exact (3, 7); source 7abe5263e5. Restored.

### getBlocks__Q33ipl5scene17MemoryCardManagerFUcs
Origin fetched 786a2dd3e8e0c8139026493f29a06e5aa5a93fc6; remote source same.
HIGH diagnosis: target keeps r11 epilogue preparation after final load, source hoists it earlier; identical instruction count/frame. Test pointer/reference boundary and inline scalar accessor.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | HIGH file member reference | 25/25 instructions; structural/exact (2, 9); source 75dca1f49d. Restored.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | HIGH block count pointer return | 25/25 instructions; structural/exact (2, 9); source 17686a1a4b. Restored.
getBlocks__Q33ipl5scene17MemoryCardManagerFUcs | HIGH slot directory reference | 25/25 instructions; structural/exact (2, 9); source 6d2c2d5e5f. Restored.

### _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl
Origin fetched 786a2dd3e8e0c8139026493f29a06e5aa5a93fc6; remote source same.
HIGH diagnosis: exact100/106instruction count; target carries GX destination row and column independently across initializers and reforms metadata pointer after validation. Test field helper and row reference; no volatile declaration without reload proof.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | HIGH file cell row reference | 95/100 instructions; structural/exact (52, 84); source c8a348d2b8. Restored.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | HIGH metadata slot reference | 97/100 instructions; structural/exact (22, 79); source c02f0bc387. Restored.
_create_icon__Q33ipl5scene17MemoryCardManagerFUcsl | HIGH format switch branch | 102/100 instructions; structural/exact (23, 87); source 0f02881505. Restored.

### getComment__Q33ipl5scene17MemoryCardManagerFUcsi
Origin fetched 786a2dd3e8e0c8139026493f29a06e5aa5a93fc6; remote source same.
HIGH diagnosis:123instructions/frame exact, callee-saved addresses rotate and trim read/zero temporaries r3/r5 swap. Try return and pointer-loop declaration boundaries.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | HIGH trim pointer common postdecrement | 123/123 instructions; structural/exact (0, 21); source 1904fdc7ab. Restored.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | HIGH return stores comment selector locally | 123/123 instructions; structural/exact (13, 36); source 87ee8f4371. Restored.
getComment__Q33ipl5scene17MemoryCardManagerFUcsi | HIGH trailing buffer explicitly terminates before trimming | 124/123 instructions; structural/exact (7, 89); source fba54fbf44. Restored.

### create_banner__Q33ipl5scene17MemoryCardManagerFUcs
Origin fetched 786a2dd3e8e0c8139026493f29a06e5aa5a93fc6; remote source same.
HIGH diagnosis: exact100/106instruction count; target carries GX destination row and column independently across initializers and reforms metadata pointer after validation. Test field helper and row reference; no volatile declaration without reload proof.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | HIGH file cell row reference | 97/106 instructions; structural/exact (81, 90); source aa6a1cdbb7. Restored.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | HIGH metadata slot reference | 103/106 instructions; structural/exact (20, 96); source eddcb7f549. Restored.
create_banner__Q33ipl5scene17MemoryCardManagerFUcs | HIGH format switch branch | 108/106 instructions; structural/exact (21, 90); source 812755d390. Restored.
HIGH DATA PROOF: sRakuStatus at810BDDE0 is three32-bit words,12bytes, copied by syncRakuProgress and cleared by start size0xC; independent configuration at810BDDEC is passed to ATERMi_ApConfigGetResult and cleared by start size0xE8, with ssid32/security4/keyId4/wepKeys128/passphrase64. The prior F4-byte status extent absorbed this neighbour. Split into real C/E8 objects, preserving starts, combined F4 extent, allocator16bytes and queue32bytes, and full BSS0x128. No padding, new address pin, or function extent change. Source split alone already gives start96/96,diffs0 before target metadata edits.

HIGH Raku13 independent gate PASS: start96/96,diffs0,objdiff100%; exact12->13, code1252->1636, data456->456; all sections100%; full buildDOL26116613f624061ba99c8d1a299aaa6efa85670d,0 regressions,0 forbidden/style patterns. Gate evidence rt8.high.raku13-gate.txt.

### finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi
Origin fetched 786a2dd3e8e0c8139026493f29a06e5aa5a93fc6; remote source differs; examined source separately.
HIGH after storage repair: source132/target133, correct0x30frame; target success branch jumps over delayed failure return, configuration pointer created after SSIDcopy/strlen, source created before. Correct nesting then pointer lifetimes; register-only search last.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH success block surrounds finish teardown | 133/133 instructions; structural/exact (5, 43); source 0e8e7cb084. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH configuration pointer created after SSID copy | 133/133 instructions; structural/exact (0, 38); source 0802ade34c. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH const config pointer after SSID copy | 133/133 instructions; structural/exact (0, 38); source 22bb3d2f4c. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH result status read-only reference | 133/133 instructions; structural/exact (0, 38); source 7d003206af. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH best structure before register search | 133/133 instructions; structural/exact (0, 38); source 0802ade34c. Kept for gate.

### create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator
Origin fetched 786a2dd3e8e0c8139026493f29a06e5aa5a93fc6; remote source same.
HIGH pool first identical57 strings. create structural diagnosis:351/352 equalframe; inlined Init keeps index offsets while target advances one receiver pointer. UIButton Create retained names/receiver differ. Test genuine array iteration forms within same-unit inline helper, check exact helper callers before keeping anything.
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | HIGH text cursor and bounding index | 352/352 instructions; structural/exact (28, 255); source a27a1dc0bc. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH settings declaration at entry | 133/133 instructions; structural/exact (0, 38); source 3fc5609445. Restored.
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | HIGH bounding cursor and text index | 352/352 instructions; structural/exact (28, 255); source f3d728837c. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH settings declaration before state | 133/133 instructions; structural/exact (0, 38); source c30b098321. Restored.
create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | HIGH parallel pane cursors with end pointer | 351/352 instructions; structural/exact (29, 241); source 9139acfae9. Restored.

### createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator
Origin fetched 786a2dd3e8e0c8139026493f29a06e5aa5a93fc6; remote source same.
HIGH diagnosis:214/216,0x50frame exact; two animation descriptor reloads absent, repaired by descriptor location reference. After structural repair GPR53differences persist. Try allocating constructors through one shared raw buffer and descriptor lifetime order.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH settings declaration just before config test | 133/133 instructions; structural/exact (0, 38); source a1ed4a8968. Restored.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | HIGH shared constructor buffer declaration | 216/216 instructions; structural/exact (0, 53); source bbb359b2e0. Restored.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | HIGH descriptor pointer array reference | 217/216 instructions; structural/exact (14, 173); source edf7f5234c. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH single index declaration shared between key copies | 133/133 instructions; structural/exact (0, 38); source 182a67b6cd. Restored.
createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator | HIGH inner transform declaration before resource | 216/216 instructions; structural/exact (0, 53); source fdbaa0e626. Restored.

### CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv
Origin fetched 786a2dd3e8e0c8139026493f29a06e5aa5a93fc6; remote source same.
HIGH diagnosis:435/435,frame0x190, onlyf2/f3swap within forward helper output/sizeheight; initial pointer/call/branch structure exact. Vary forward locals and helper boundaries, retain backwards loop.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH settings entry and shared copy index | 133/133 instructions; structural/exact (0, 38); source f0211fa010. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | HIGH forward height Size member reference | 435/435 instructions; structural/exact (0, 11); source 718bf5824a. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | HIGH forward shared translation vector | 433/435 instructions; structural/exact (55, 158); source 1a86102d4d. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | HIGH forward scaled Size separate value | 435/435 instructions; structural/exact (15, 22); source 1221b0deed. Restored.
finish__Q33ipl5scene14RakuRakuThreadFP11NCDApConfigPi | HIGH config first inline copy | 133/133 instructions; structural/exact (0, 0); source d6047ab6e8. Restored.
HIGH DATA BASELINE main/src/scene/memoryCard/iplMemoryCardManager 0/0; no initially unpaired owned data.
HIGH DATA BASELINE main/src/scene/setting/iplRakuRakuThread 456/456; no initially unpaired owned data.
HIGH DATA BASELINE main/src/keyboard/tiCandidateBox 4652/4652; no initially unpaired owned data.

HIGH finish exact: inline copyRakuPrivacy takes const settings pointer and output config, preserving honest privacy-copy operation boundary; target133/133,diffs0. Structured success branch preserves delayed failure return. No ABI/function rename. Raku14 quick gatePASS; code2168/2168,data456/456,14/14functions,allsections100%,zero regressions/styles. See rt8.high.raku14-gate.txt.

### CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv
Origin fetched bf6bc87fbd959f4d25655046152bf58f4557bca4; remote source same.
HIGH final forward width inline boundary: target f3 vs source f2 allocation; test read-only TextBox helper without changing existing helper users.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | HIGH const TextBox width helper | 435/435 instructions; structural/exact (0, 11); source 4858b25f40. Restored.
CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | HIGH independent mutable TextBox width inline boundary | 435/435 instructions; structural/exact (0, 11); source da6d11d75e. Restored.
HIGH isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl register-only declaration search, after structural and inline attempts.
HIGH CalcPaneLocate register declaration search after five helper/size/translation attempts.
declaration block:
      CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
      memorycard::CardState* states = memorycard::getCardSlotState();
      u32 file = mFile[slot][index].fileNo;
      memorycard::FileInfo* dir = NULL;
      long result;
      bool enabled = false;
start (0, 2)
best (0, 2) after 36 builds; source restored; best order was:
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    memorycard::CardState* states = memorycard::getCardSlotState();
    u32 file = mFile[slot][index].fileNo;
    memorycard::FileInfo* dir = NULL;
    long result;
    bool enabled = false;

isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH final declaration order | 118/118 instructions; structural/exact (0, 2); source da18510e24. Restored.
HIGH isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl register-only declaration search, after structural and inline attempts.
declaration block:
      CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
      memorycard::CardState* states = memorycard::getCardSlotState();
      u32 file = mFile[slot][index].fileNo;
      memorycard::FileInfo* dir = NULL;
      long result;
      bool enabled = false;
start (0, 2)
best (0, 2) after 36 builds; source restored; best order was:
    CardDirectory* dirs = reinterpret_cast<CardDirectory*>(memorycard::getCardDirState());
    memorycard::CardState* states = memorycard::getCardSlotState();
    u32 file = mFile[slot][index].fileNo;
    memorycard::FileInfo* dir = NULL;
    long result;
    bool enabled = false;

isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl | HIGH final declaration order | 118/118 instructions; structural/exact (0, 2); source da18510e24. Restored.
HIGH update_file_array__Q33ipl5scene17MemoryCardManagerFUc register-only declaration search, after structural and inline attempts.
declaration block:
      memorycard::CardState* states;
      long command;
start (0, 4)
best (0, 4) after 2 builds; source restored; best order was:
    memorycard::CardState* states;
    long command;

update_file_array__Q33ipl5scene17MemoryCardManagerFUc | HIGH final declaration order | 90/90 instructions; structural/exact (0, 4); source 05fe63d84d. Restored.
declaration block:
              f32 widthScale = GetWidthScale_();
              f32 margin = GetMargin_();
              f32 xOffset = mfXOffset;

              f32 areaPaneXOffset = mpTextAreaPane->getPane()->GetTranslate().x;
              f32 areaPaneWidth = mpTextAreaPane->getPane()->GetSize().width;
              s32 selectedIdx = GetSelectedTextIdx();
start (0, 11)
best (0, 11) after 52 builds; source restored; best order was:
            f32 widthScale = GetWidthScale_();
            f32 margin = GetMargin_();
            f32 xOffset = mfXOffset;

            f32 areaPaneXOffset = mpTextAreaPane->getPane()->GetTranslate().x;
            f32 areaPaneWidth = mpTextAreaPane->getPane()->GetSize().width;
            s32 selectedIdx = GetSelectedTextIdx();

CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv | HIGH final float declaration order | 435/435 instructions; structural/exact (0, 11); source e35ef16dfc. Restored.

HIGH FINAL OPEN AUDIT isMoveEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 99.830505%; 10 distinct compiled HIGH variants.
src 0x1d8 base 0x1d8 insns 118/118
diffs 2: [28, 78]
    28 M add r5, r3, r0
       B add r5, r0, r3
    78 M add r5, r3, r0
       B add r5, r0, r3

HIGH FINAL OPEN AUDIT isCopyEnable__Q33ipl5scene17MemoryCardManagerFUcUlPl: 99.830505%; 10 distinct compiled HIGH variants.
src 0x1d8 base 0x1d8 insns 118/118
diffs 2: [28, 78]
    28 M add r5, r3, r0
       B add r5, r0, r3
    78 M add r5, r3, r0
       B add r5, r0, r3

HIGH FINAL OPEN AUDIT isBannerEnable__Q33ipl5scene17MemoryCardManagerFUcs: 92.30769%; 3 distinct compiled HIGH variants.
src 0x68 base 0x68 insns 26/26
diffs 8: [11, 12, 13, 14, 15, 16, 17, 18]
    11 M addi r11, r1, 0x20
       B add r4, r29, r4
    12 M add r4, r29, r4
       B add r4, r4, r0
    13 M add r4, r4, r0
       B mulli r5, r30, 0x1fc0
    14 M mulli r5, r30, 0x1fc0
       B lwz r4, 8(r4)
    15 M lwz r4, 8(r4)
       B add r0, r3, r5
    16 M add r0, r3, r5
       B slwi r3, r4, 6
    17 M slwi r3, r4, 6
       B lbzx r3, r3, r0
    18 M lbzx r3, r3, r0
       B addi r11, r1, 0x20

HIGH FINAL OPEN AUDIT update_file_array__Q33ipl5scene17MemoryCardManagerFUc: 99.72222%; 7 distinct compiled HIGH variants.
src 0x168 base 0x168 insns 90/90
diffs 4: [15, 16, 17, 20]
    15 M addis r4, r30, 1
       B addis r3, r30, 1
    16 M lwz r3, 0x6934(r4)
       B lwz r4, 0x6934(r3)
    17 M addi r0, r3, -1
       B addi r0, r4, -1
    20 M lwz r0, 0x6930(r4)
       B lwz r0, 0x6930(r3)

HIGH FINAL OPEN AUDIT _create_icon__Q33ipl5scene17MemoryCardManagerFUcsl: 87.55%; 3 distinct compiled HIGH variants.
src 0x190 base 0x190 insns 100/100
diffs 37: [19, 20, 22, 23, 24, 34, 39, 40, 42, 44, 45, 46, 47, 48, 57, 59, 63, 64, 65, 66]
    19 M mulli r30, r26, 0x1fc0
       B mulli r29, r26, 0x1fc0
    20 M slwi r31, r27, 6
       B slwi r30, r27, 6
    22 M add r0, r31, r3
       B add r0, r3, r29
    23 M add r29, r30, r0
       B add r31, r0, r30
    24 M add r3, r29, r28
       B add r3, r31, r28
    34 M add r3, r29, r0
       B add r3, r31, r0
    39 M add r4, r29, r0
       B add r4, r0, r31
    40 M mulli r26, r27, 0x15c
       B mulli r24, r27, 0x15c
    42 M addi r27, r3, 0x10ec
       B addi r25, r3, 0x10ec
    44 M add r24, r27, r26
       B add r3, r25, r24
    45 M mr r3, r24
       B bl 0
    46 M bl 0
       B add r24, r25, r24
    47 M mr r3, r24
       B li r4, 0
    48 M li r4, 0
       B mr r3, r24
    57 M mullw r28, r26, r4
       B mullw r26, r26, r4
    59 M add r3, r29, r0
       B add r3, r31, r0
    63 M mulli r26, r27, 0x15c
       B add r3, r25, r26
    64 M add r3, r25, r28
       B add r4, r31, r0
    65 M add r4, r29, r0
       B mulli r27, r27, 0x15c
    66 M addi r27, r3, 0x10ec
       B li r7, 9
    67 M li r7, 9
       B addi r28, r3, 0x10ec
    69 M add r3, r27, r26
       B add r3, r28, r27
    73 M add r0, r24, r30
       B add r0, r24, r29
    74 M add r4, r25, r28
       B add r4, r25, r26
    75 M add r3, r0, r31
       B add r3, r0, r30
    77 M add r4, r4, r26
       B lwz r0, 0x3c(r3)
    78 M lwz r0, 0x3c(r3)
       B addi r24, r4, 0x112c
    79 M addi r24, r4, 0x112c
       B add r3, r24, r27
    81 M mr r3, r24
       B add r4, r31, r0
    82 M add r4, r29, r0
       B bl 0
    83 M bl 0
       B add r3, r24, r27
    84 M mr r3, r24
       B li r4, 0
    85 M li r4, 0
       B bl 0
    86 M bl 0
       B add r24, r28, r27
    87 M add r3, r27, r26
       B li r4, 0
    88 M li r4, 0
       B mr r3, r24
    93 M add r3, r27, r26
       B mr r3, r24

HIGH FINAL OPEN AUDIT getComment__Q33ipl5scene17MemoryCardManagerFUcsi: 98.94309%; 3 distinct compiled HIGH variants.
src 0x1ec base 0x1ec insns 123/123
diffs 20: [10, 12, 14, 19, 20, 21, 23, 24, 45, 46, 48, 49, 51, 62, 66, 67, 86, 90, 91, 117]
    10 M mr r27, r3
       B mr r26, r3
    12 M slwi r28, r6, 7
       B slwi r27, r6, 7
    14 M mullw r30, r4, r0
       B mullw r29, r4, r0
    19 M mulli r29, r25, 0x15c
       B mulli r28, r25, 0x15c
    20 M add r0, r3, r30
       B add r0, r3, r29
    21 M add r3, r0, r29
       B add r3, r0, r28
    23 M add r26, r31, r28
       B add r30, r31, r27
    24 M mr r3, r26
       B mr r3, r30
    45 M mr r5, r4
       B mr r3, r4
    46 M li r3, 0
       B li r5, 0
    48 M stb r3, 0(r4)
       B stb r5, 0(r4)
    49 M addi r5, r5, -1
       B addi r3, r3, -1
    51 M lbz r0, 0(r5)
       B lbz r0, 0(r3)
    62 M mr r3, r26
       B mr r3, r30
    66 M add r3, r27, r30
       B add r3, r26, r29
    67 M add r0, r28, r29
       B add r0, r27, r28
    86 M mr r3, r26
       B mr r3, r30
    90 M add r3, r27, r30
       B add r3, r26, r29
    91 M add r0, r28, r29
       B add r0, r27, r28
   117 M add r3, r31, r28
       B add r3, r31, r27

HIGH FINAL OPEN AUDIT create_banner__Q33ipl5scene17MemoryCardManagerFUcs: 90.42453%; 3 distinct compiled HIGH variants.
src 0x1a8 base 0x1a8 insns 106/106
diffs 70: [5, 6, 9, 11, 14, 16, 17, 18, 19, 23, 24, 25, 26, 27, 32, 33, 34, 35, 36, 37]
     5 M mr r27, r3
       B mr r26, r3
     6 M mr r28, r4
       B mr r27, r4
     9 M mr r30, r3
       B mr r25, r3
    11 M mulli r4, r28, 0x7f0
       B mulli r4, r27, 0x7f0
    14 M add r4, r27, r4
       B add r4, r26, r4
    16 M lwz r29, 8(r4)
       B lwz r28, 8(r4)
    17 M mulli r0, r28, 0x5f4
       B mulli r0, r27, 0x5f4
    18 M mulli r4, r29, 0xc
       B mulli r4, r28, 0xc
    19 M add r0, r30, r0
       B add r0, r25, r0
    23 M mulli r25, r28, 0x1fc0
       B mulli r29, r27, 0x1fc0
    24 M slwi r26, r29, 6
       B slwi r30, r28, 6
    25 M add r0, r26, r3
       B add r0, r30, r3
    26 M add r30, r25, r0
       B add r4, r29, r0
    27 M lbzx r0, r25, r0
       B lbzx r0, r29, r0
    32 M lbz r0, 3(r30)
       B add r0, r3, r29
    33 M cmpwi r0, 5
       B add r25, r0, r30
    34 M bne 88
       B lbz r0, 3(r25)
    35 M lis r3, 1
       B cmpwi r0, 5
    36 M lwz r0, 0x14(r30)
       B bne 84
    37 M addi r3, r3, -0x535c
       B lis r3, 1
    38 M li r5, 0x60
       B lwz r0, 0x14(r25)
    39 M mullw r3, r28, r3
       B addi r3, r3, -0x535c
    40 M add r4, r30, r0
       B li r5, 0x60
    41 M li r6, 0x20
       B mullw r3, r27, r3
    42 M li r7, 5
       B add r4, r4, r0
    43 M li r8, 0
       B li r6, 0x20
    44 M li r9, 0
       B li r7, 5
    45 M mulli r0, r29, 0x15c
       B li r8, 0
    46 M add r3, r27, r3
       B li r9, 0
    47 M li r10, 0
       B add r3, r26, r3
    48 M add r3, r3, r0
       B li r10, 0
    49 M addi r25, r3, 0x110c
       B mulli r25, r28, 0x15c
    50 M mr r3, r25
       B addi r29, r3, 0x110c
    51 M bl 0
       B add r3, r29, r25
    52 M mr r3, r25
       B bl 0
    53 M li r4, 0
       B add r3, r29, r25
    54 M bl 0
       B li r4, 0
    55 M b 152
       B bl 0
    56 M cmpwi r0, 9
       B b 148
    57 M bne 144
       B cmpwi r0, 9
    58 M lis r3, 1
       B bne 140
    59 M li r0, 0
       B lis r3, 1
    60 M addi r3, r3, -0x535c
       B li r0, 0
    61 M stw r0, 8(r1)
       B addi r3, r3, -0x535c
    62 M mullw r23, r28, r3
       B stw r0, 8(r1)
    63 M li r5, 0x60
       B mullw r23, r27, r3
    64 M lwz r0, 0x14(r30)
       B li r5, 0x60
    65 M li r6, 0x20
       B lwz r0, 0x14(r25)
    66 M li r7, 9
       B li r6, 0x20
    67 M add r4, r30, r0
       B li r7, 9
    68 M add r3, r27, r23
       B add r4, r25, r0
    69 M li r8, 0
       B add r3, r26, r23
    70 M mulli r24, r29, 0x15c
       B li r8, 0
    71 M li r9, 0
       B mulli r24, r28, 0x15c
    72 M addi r22, r3, 0x110c
       B li r9, 0
    73 M li r10, 0
       B addi r22, r3, 0x110c
    74 M add r3, r22, r24
       B li r10, 0
    75 M bl 0
       B add r3, r22, r24
    76 M add r0, r31, r25
       B bl 0
    77 M add r4, r27, r23
       B add r0, r31, r29
    78 M add r3, r0, r26
       B add r4, r26, r23
    79 M li r5, 2
       B add r3, r0, r30
    80 M add r4, r4, r24
       B li r5, 2
    83 M li r6, 0x100
       B add r3, r23, r24
    84 M mr r3, r23
       B li r6, 0x100
    85 M add r4, r30, r0
       B add r4, r25, r0
    87 M mr r3, r23
       B add r3, r23, r24
    95 M mullw r3, r28, r0
       B mullw r3, r27, r0
    96 M mulli r0, r29, 0x15c
       B mulli r0, r28, 0x15c
    97 M add r3, r27, r3
       B add r3, r26, r3

HIGH FINAL OPEN AUDIT getBlocks__Q33ipl5scene17MemoryCardManagerFUcs: 92.0%; 3 distinct compiled HIGH variants.
src 0x64 base 0x64 insns 25/25
diffs 9: [11, 12, 13, 14, 15, 16, 17, 18, 19]
    11 M addi r11, r1, 0x20
       B add r4, r29, r4
    12 M add r4, r29, r4
       B add r4, r4, r0
    13 M add r4, r4, r0
       B lwz r0, 8(r4)
    14 M lwz r0, 8(r4)
       B mulli r4, r30, 0x5f4
    15 M mulli r4, r30, 0x5f4
       B mulli r0, r0, 0xc
    16 M mulli r0, r0, 0xc
       B add r3, r3, r4
    17 M add r3, r3, r4
       B add r3, r3, r0
    18 M add r3, r3, r0
       B lhz r3, 2(r3)
    19 M lhz r3, 2(r3)
       B addi r11, r1, 0x20

HIGH FINAL OPEN AUDIT create__Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator: 92.71023%; 3 distinct compiled HIGH variants.
src 0x57c base 0x580 insns 351/352
--- replace mine 5:6 base 5:6
  M    5 lis r29, 0
  B    5 lis r30, 0
--- replace mine 10:11 base 10:11
  M   10 addi r29, r29, 0
  B   10 addi r30, r30, 0
--- replace mine 29:30 base 29:30
  M   29 mr r30, r3
  B   29 mr r26, r3
--- replace mine 49:51 base 49:51
  M   49 stw r30, 0xe0(r31)
  M   50 mr r3, r30
  B   49 stw r26, 0xe0(r31)
  B   50 mr r3, r26
--- replace mine 52:53 base 52:53
  M   52 lwz r12, 0(r30)
  B   52 lwz r12, 0(r26)
--- replace mine 77:79 base 77:79
  M   77 li r28, 0
  M   78 li r30, 0
  B   77 mr r26, r31
  B   78 li r29, 0
--- replace mine 80:81 base 80:81
  M   80 add r3, r31, r30
  B   80 lwz r3, 0x11c(r26)
--- delete mine 82:83 base 82:82
  M   82 lwz r3, 0x11c(r3)
--- replace mine 89:90 base 88:89
  M   89 add r3, r31, r30
  B   88 lwz r3, 0x16c(r26)
--- delete mine 91:92 base 90:90
  M   91 lwz r3, 0x16c(r3)
--- replace mine 96:100 base 94:98
  M   96 addi r28, r28, 1
  M   97 addi r30, r30, 4
  M   98 cmplwi r28, 0x14
  M   99 blt -76
  B   94 addi r29, r29, 1
  B   95 addi r26, r26, 4
  B   96 cmplwi r29, 0x14
  B   97 blt -68
--- replace mine 111:112 base 109:110
  M  111 mr r28, r3
  B  109 mr r29, r3
--- replace mine 115:116 base 113:114
  M  115 mr r3, r28
  B  113 mr r3, r29
--- replace mine 126:129 base 124:126
  M  126 addi r30, r29, 0x28
  M  127 mr r3, r28
  M  128 addi r4, r30, 0x680
  B  124 mr r3, r29
  B  125 addi r4, r30, 0x6a8
--- replace mine 131:133 base 128:130
  M  131 mr r3, r28
  M  132 addi r4, r29, 0x6b4
  B  128 mr r3, r29
  B  129 addi r4, r30, 0x6b4
--- replace mine 136:137 base 133:134
  M  136 addi r4, r30, 0x680
  B  133 addi r4, r30, 0x6a8
--- replace mine 148:149 base 145:146
  M  148 addi r4, r30, 0x680
  B  145 addi r4, r30, 0x6a8
--- replace mine 167:169 base 164:165
  M  167 addi r30, r29, 0x6b4
  M  168 addi r4, r30, 0xc
  B  164 addi r4, r30, 0x6c0
--- replace mine 187:188 base 183:184
  M  187 addi r4, r30, 0x18
  B  183 addi r4, r30, 0x6cc
--- replace mine 225:226 base 221:222
  M  225 addi r4, r30, 0x24
  B  221 addi r4, r30, 0x6d8
--- replace mine 256:257 base 252:255
  M  256 mr r27, r31
  B  252 mr r26, r31
  B  253 addi r28, r30, 0x6e4
  B  254 addi r29, r30, 0x6f8
--- replace mine 258:261 base 256:259
  M  258 addi r27, r31, 0x24
  M  259 lwz r12, 0(r27)
  M  260 mr r3, r27
  B  256 addi r26, r31, 0x24
  B  257 lwz r12, 0(r26)
  B  258 mr r3, r26
--- replace mine 264:266 base 262:264
  M  264 mr r28, r3
  M  265 addi r4, r30, 0x44
  B  262 mr r27, r3
  B  263 mr r4, r29
--- replace mine 268:270 base 266:268
  M  268 mr r3, r28
  M  269 addi r4, r30, 0x30
  B  266 mr r3, r27
  B  267 mr r4, r28
--- replace mine 272:275 base 270:273
  M  272 mr r3, r27
  M  273 addi r4, r30, 0x44
  M  274 lwz r12, 0(r27)
  B  270 mr r3, r26
  B  271 mr r4, r29
  B  272 lwz r12, 0(r26)
--- replace mine 282:283 base 280:282
  M  282 mr r27, r31
  B  280 mr r26, r31
  B  281 addi r28, r30, 0x70c
--- insert mine 284:284 base 283:284
  B  283 addi r27, r30, 0x720
--- replace mine 285:288 base 285:288
  M  285 addi r27, r31, 0x24
  M  286 lwz r12, 0(r27)
  M  287 mr r3, r27
  B  285 addi r26, r31, 0x24
  B  286 lwz r12, 0(r26)
  B  287 mr r3, r26
--- replace mine 291:293 base 291:293
  M  291 mr r28, r3
  M  292 addi r4, r30, 0x6c
  B  291 mr r29, r3
  B  292 mr r4, r27
--- replace mine 295:297 base 295:297
  M  295 mr r3, r28
  M  296 addi r4, r30, 0x58
  B  295 mr r3, r29
  B  296 mr r4, r28
--- replace mine 299:302 base 299:302
  M  299 mr r3, r27
  M  300 addi r4, r30, 0x6c
  M  301 lwz r12, 0(r27)
  B  299 mr r3, r26
  B  300 mr r4, r27
  B  301 lwz r12, 0(r26)
--- replace mine 322:323 base 322:324
  M  322 mr r27, r31
  B  322 mr r26, r31
  B  323 addi r27, r30, 0x738
--- replace mine 324:327 base 325:328
  M  324 addi r27, r31, 0x24
  M  325 lwz r12, 0(r27)
  M  326 mr r3, r27
  B  325 addi r26, r31, 0x24
  B  326 lwz r12, 0(r26)
  B  327 mr r3, r26
--- replace mine 330:331 base 331:332
  M  330 addi r4, r29, 0x738
  B  331 mr r4, r27
--- replace mine 333:336 base 334:337
  M  333 mr r3, r27
  M  334 addi r4, r29, 0x738
  M  335 lwz r12, 0(r27)
  B  334 mr r3, r26
  B  335 mr r4, r27
  B  336 lwz r12, 0(r26)

HIGH FINAL OPEN AUDIT createAnmPane___Q39textinput12candidatebox12LayoutByNW4RFP12MEMAllocator: 96.56481%; 3 distinct compiled HIGH variants.
src 0x358 base 0x360 insns 214/216
--- insert mine 5:5 base 5:8
  B    5 lis r25, 0
  B    6 lis r27, 0
  B    7 lis r28, 0
--- delete mine 6:10 base 9:9
  M    6 lis r26, 0
  M    7 lis r27, 0
  M    8 lis r23, 0
  M    9 lis r28, 0
--- insert mine 11:11 base 10:11
  B   10 lis r30, 0
--- insert mine 14:14 base 14:17
  B   14 addi r25, r25, 0
  B   15 addi r27, r27, 0
  B   16 addi r28, r28, 0
--- delete mine 15:19 base 18:18
  M   15 addi r26, r26, 0
  M   16 addi r27, r27, 0
  M   17 addi r23, r23, 0
  M   18 addi r28, r28, 0
--- insert mine 20:20 base 19:20
  B   19 addi r30, r30, 0
--- replace mine 21:22 base 21:22
  M   21 li r25, 0
  B   21 li r26, 0
--- replace mine 23:26 base 23:26
  M   23 li r22, 0
  M   24 add r20, r23, r0
  M   25 lwzx r0, r23, r0
  B   23 li r19, 0
  B   24 add r20, r24, r0
  B   25 lwzx r0, r24, r0
--- replace mine 40:41 base 40:41
  M   40 mr r22, r3
  B   40 mr r19, r3
--- replace mine 48:49 base 48:49
  M   48 stw r24, 0(r22)
  B   48 stw r25, 0(r19)
--- replace mine 50:54 base 50:54
  M   50 stw r3, 4(r22)
  M   51 addi r3, r22, 8
  M   52 stw r25, 0x14(r22)
  M   53 stw r25, 0x18(r22)
  B   50 stw r3, 4(r19)
  B   51 addi r3, r19, 8
  B   52 stw r26, 0x14(r19)
  B   53 stw r26, 0x18(r19)
--- replace mine 55:59 base 55:59
  M   55 stw r26, 0(r22)
  M   56 mr r3, r22
  M   57 stw r25, 0x2c(r22)
  M   58 lwz r12, 0(r22)
  B   55 stw r27, 0(r19)
  B   56 mr r3, r19
  B   57 stw r26, 0x2c(r19)
  B   58 lwz r12, 0(r19)
--- replace mine 62:64 base 62:64
  M   62 stw r27, 0(r22)
  M   63 stw r25, 0x30(r22)
  B   62 stw r28, 0(r19)
  B   63 stw r26, 0x30(r19)
--- replace mine 69:70 base 69:70
  M   69 mr r22, r3
  B   69 mr r19, r3
--- replace mine 77:78 base 77:78
  M   77 stw r24, 0(r22)
  B   77 stw r25, 0(r19)
--- replace mine 79:83 base 79:83
  M   79 stw r3, 4(r22)
  M   80 addi r3, r22, 8
  M   81 stw r25, 0x14(r22)
  M   82 stw r25, 0x18(r22)
  B   79 stw r3, 4(r19)
  B   80 addi r3, r19, 8
  B   81 stw r26, 0x14(r19)
  B   82 stw r26, 0x18(r19)
--- replace mine 84:88 base 84:88
  M   84 stw r26, 0(r22)
  M   85 mr r3, r22
  M   86 stw r25, 0x2c(r22)
  M   87 lwz r12, 0(r22)
  B   84 stw r27, 0(r19)
  B   85 mr r3, r19
  B   86 stw r26, 0x2c(r19)
  B   87 lwz r12, 0(r19)
--- replace mine 91:92 base 91:92
  M   91 stw r14, 0x30(r22)
  B   91 stw r14, 0x30(r19)
--- replace mine 97:98 base 97:98
  M   97 mr r22, r3
  B   97 mr r19, r3
--- replace mine 105:106 base 105:106
  M  105 stw r24, 0(r22)
  B  105 stw r25, 0(r19)
--- replace mine 108:112 base 108:112
  M  108 stw r3, 4(r22)
  M  109 addi r3, r22, 8
  M  110 stw r25, 0x14(r22)
  M  111 stw r0, 0x18(r22)
  B  108 stw r3, 4(r19)
  B  109 addi r3, r19, 8
  B  110 stw r26, 0x14(r19)
  B  111 stw r0, 0x18(r19)
--- replace mine 113:117 base 113:117
  M  113 stw r26, 0(r22)
  M  114 mr r3, r22
  M  115 stw r25, 0x2c(r22)
  M  116 lwz r12, 0(r22)
  B  113 stw r27, 0(r19)
  B  114 mr r3, r19
  B  115 stw r26, 0x2c(r19)
  B  116 lwz r12, 0(r19)
--- replace mine 120:121 base 120:121
  M  120 stw r28, 0(r22)
  B  120 stw r29, 0(r19)
--- replace mine 122:123 base 122:123
  M  122 stw r0, 0x30(r22)
  B  122 stw r0, 0x30(r19)
--- replace mine 128:129 base 128:129
  M  128 mr r22, r3
  B  128 mr r19, r3
--- replace mine 136:137 base 136:137
  M  136 stw r24, 0(r22)
  B  136 stw r25, 0(r19)
--- replace mine 139:143 base 139:143
  M  139 stw r3, 4(r22)
  M  140 addi r3, r22, 8
  M  141 stw r25, 0x14(r22)
  M  142 stw r0, 0x18(r22)
  B  139 stw r3, 4(r19)
  B  140 addi r3, r19, 8
  B  141 stw r26, 0x14(r19)
  B  142 stw r0, 0x18(r19)
--- replace mine 144:148 base 144:148
  M  144 stw r26, 0(r22)
  M  145 mr r3, r22
  M  146 stw r25, 0x2c(r22)
  M  147 lwz r12, 0(r22)
  B  144 stw r27, 0(r19)
  B  145 mr r3, r19
  B  146 stw r26, 0x2c(r19)
  B  147 lwz r12, 0(r19)
--- replace mine 151:152 base 151:152
  M  151 stw r29, 0(r22)
  B  151 stw r30, 0(r19)
--- replace mine 153:155 base 153:155
  M  153 stw r0, 0x30(r22)
  M  154 mr r4, r22
  B  153 stw r0, 0x30(r19)
  B  154 mr r4, r19
--- replace mine 157:159 base 157:159
  M  157 lwz r30, 0x1c(r20)
  M  158 li r19, 0
  B  157 lwz r22, 0x1c(r20)
  B  158 li r18, 0
--- replace mine 160:161 base 160:161
  M  160 b 168
  B  160 b 176
--- replace mine 162:164 base 162:164
  M  162 rlwinm r0, r19, 2, 0xe, 0x1d
  M  163 add r5, r20, r0
  B  162 rlwinm r0, r18, 2, 0xe, 0x1d
  B  163 add r23, r20, r0
--- replace mine 167:168 base 167:168
  M  167 lwz r18, 0x20(r5)
  B  167 lwz r5, 0x20(r23)
--- replace mine 169:170 base 169:170
  M  169 addi r5, r18, 4
  B  169 addi r5, r5, 4
--- replace mine 184:185 base 184:185
  M  184 cmpwi r30, 0
  B  184 cmpwi r22, 0
--- replace mine 186:189 base 186:189
  M  186 bne 32
  M  187 lwz r5, 0(r18)
  M  188 mr r3, r22
  B  186 bne 36
  B  187 lwz r5, 0x20(r23)
  B  188 mr r3, r19
--- insert mine 191:191 base 191:192
  B  191 lwz r5, 0(r5)
--- replace mine 193:196 base 194:197
  M  193 b 32
  M  194 lwz r5, 0(r18)
  M  195 mr r3, r22
  B  194 b 36
  B  195 lwz r5, 0x20(r23)
  B  196 mr r3, r19
--- replace mine 197:198 base 198:200
  M  197 mr r7, r30
  B  198 mr r7, r22
  B  199 lwz r5, 0(r5)
--- replace mine 201:203 base 203:205
  M  201 addi r19, r19, 1
  M  202 clrlwi r0, r19, 0x10
  B  203 addi r18, r18, 1
  B  204 clrlwi r0, r18, 0x10
--- replace mine 204:205 base 206:207
  M  204 blt -172
  B  206 blt -180
--- replace mine 207:208 base 209:210
  M  207 blt -740
  B  209 blt -748

HIGH FINAL OPEN AUDIT CalcPaneLocate___Q39textinput12candidatebox10UITextAreaFv: 99.873566%; 6 distinct compiled HIGH variants.
src 0x6cc base 0x6cc insns 435/435
diffs 11: [264, 269, 304, 305, 306, 307, 310, 313, 316, 322, 324]
   264 M lfs f2, 0(0)
       B lfs f3, 0(0)
   269 M lfs f2, 0(0)
       B lfs f3, 0(0)
   304 M fadds f2, f22, f0
       B fadds f3, f22, f0
   305 M frsp f1, f2
       B frsp f1, f3
   306 M lfs f3, 0x54(r1)
       B lfs f2, 0x54(r1)
   307 M fmuls f23, f2, f29
       B fmuls f23, f3, f29
   310 M stfs f2, 0x20(r1)
       B stfs f3, 0x20(r1)
   313 M stfs f3, 0x50(r22)
       B stfs f2, 0x50(r22)
   316 M stfs f3, 0x50(r23)
       B stfs f2, 0x50(r23)
   322 M stfs f3, 0x24(r1)
       B stfs f2, 0x24(r1)
   324 M stfs f3, 0x1c(r1)
       B stfs f2, 0x1c(r1)

HIGH FINAL FULL GATE PASS: full43U build and26116613f624061ba99c8d1a299aaa6efa85670d DOL; Raku14/14,code2168/2168,data456/456; MC18/26,code2572/5396,no data; CandidateBox109/112objdiff108/112gate,code19988/24000,data4652/4652. Zero regressions and zero forbidden/style additions. Every remaining function has >=3 distinct compiled HIGH attempts. Source changes retained only in RakuRakuThread; symbols only split proven status/configuration ownership. Final report rt8.high.report.md and full gate rt8.high.final-gate.txt.
