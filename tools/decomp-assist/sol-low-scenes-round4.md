# Scenes round 4 attempts

Baseline: merged main `55fd34f9`. All 129 Select, 112 Setting and 66 Memory original functions are present. No assembly bodies remain. Only this checkout and /tmp were changed. No matching flags changed.

Coverage: every one of the 31 initially open Select functions, 10 initially open Setting functions and four initially open Memory functions received at least three distinct successful source builds this round. Earlier-round attempts are excluded. Failed builds are logged separately. Compiler-folded variations are experiments, without any claim that they improved the output.

The continuation first ran a full passing gate against the state left after the capacity interruption. The pending exact NAND compaction improvement was then checked and committed.

## Measurements

- `src/scene/sdChannelSelect/iplSDChannelSelect`: instruction-exact 98 -> 102; objdiff exact 98 -> 102; matched code 21832 -> 24100/33828; matched data 224 -> 224/2960; fuzzy 97.236140% -> 97.385250%.
- `src/scene/setting/iplSetting`: instruction-exact 101 -> 101; objdiff exact 102 -> 102; matched code 25220 -> 25220/37884; matched data 1040 -> 1040/5696; fuzzy 90.153730% -> 92.950800%.
- `src/scene/sdChannelMemory/iplSDMemory`: instruction-exact 61 -> 62; objdiff exact 62 -> 63; matched code 13852 -> 14484/20872; matched data 200 -> 200/3344; fuzzy 97.650635% -> 97.657340%.

Function experiments: 160 successful builds, 8 failed builds. Header/table-order experiments and the additional scoped animation-status experiment are recorded separately below.

## Retained changes

- Select onEventDerived: signed event dispatch in case 5, case 1, case 2 source block order. 105/105 instructions, diffs 0; +420 matched code bytes.
- Select onButtonEvent: combine the left-arrow name and available-page checks into the left guard. The right-arrow branch is then considered when the left page is unavailable; retain the pending-action check inside pointing handling. 91/91, diffs 0; +364 bytes.
- Memory onDialogState8: reuse a typed textbox for the header and body panes, with the original inline float conversion of rounded row counts. 158/158, diffs 0; +632 bytes.
- Setting vtable order: forward-declare APEvent before Setting, and place its actual definition after Setting under IPL_SETTING_IMPLEMENTATION. Only Setting.cpp defines this guard; other translation units retain the complete original APEvent definition before Setting. This restores actual APEvent offset 0xe9c and Setting offset 0xeb4 without address objects, padding or forced emission. Matched-data byte count remains unchanged.
- Select startPageTransition: an owner-only inline member returns the actual nw4r vector by value before conversion to the scene math vector. Its typed pane/matrix access preserves the original zero vector and transform. 45/45, diffs 0; +180 bytes.
- Select processWorkerCommands: extract the actual NAND-title search and compaction into an owner-only inline member. Declare the next record reference before the current record reference. 326/326, diffs 0; +1304 bytes. Both new members are inside IPL_SD_CHANNEL_SELECT_CPP, defined only by Select.cpp.
- Setting draw: rebuild the missing rendering blocks from original assembly. Restore RGB565 textures, correct wide/standard material bindings and draw order, opaque/faded TPL side rectangles, the wide-buffer word scan, state-8 fade reset, retained animation receivers, render-mode copy and clipped main-layout draw. The AP clipping block still runs when either texture buffer is absent. This is partial matching progress: 412/632 -> 598/632 instructions, 49.120255% -> 91.036390%. No new exact function or matched-code bytes are claimed for this body.
- Function order: move the existing keyboard State assignment to after Setting::calcFadein, Scroller::init to after Memory::setScrollLimit, and Memory::updateSideArrows to after hideUpArrow. The original functions in Select and Setting now emit in original relative order. Memory scene/explicit helper definitions follow original relative order; three compiler-emitted LinkList iterator helpers still precede writeFourFlagBytes/setTitleRowColors rather than follow them. Their bodies remain exact.

## Data audit and limitations

- All three string pools remain identical. Source literal and pointer-table order was compared with the original objects; no string blobs or pinned address data were added.
- Select .rodata 64, .sdata 80 and .sdata2 80 bytes are 100%. Named pane/clock tables and actual handler/scene vtable slots have original offsets. The .data section has 2736 bytes and a 35.06984% score. Normal weak-table relocations remain in source where the extracted object has deduplicated zero-filled space.
- Setting .bss 456, .sbss 16, .sdata 504 and .sdata2 64 bytes are 100%. APEvent/Setting vtables now occupy original offsets, and the actual Setting slots include the correct inherited FaderSceneBase::calc. The .data score stays 5.146636% despite restored order because symbol aggregation and weak relocations differ.
- Setting source .rodata is 600 versus 640 original bytes. The two 20-byte scNumber/scNumber2 digit maps still have no established caller. They were not introduced as unused filler. scAnmTable contains the actual 232 binding bytes; the original symbol also aggregates following compiler-emitted arrays. .rodata remains 32.25412%.
- Memory .sdata 152 and .sdata2 48 bytes are 100%. .data is 3144 bytes in both objects. Pane arrays, strings, dialog jump tables and real handler vtable slots have original positions. Remaining weak tables contain normal source relocations where the extracted original has zero-filled space.
- One objdiff-exact Setting function and one objdiff-exact Memory function are undercounted by the instruction decoder around CR1 varargs. Both raw and objdiff totals are reported; the decoder was left unchanged.
- Open uncertainties: missing Setting digit-map callers, deduplicated weak data, Memory iterator-helper emission order and remaining compiler allocation choices. These units are not fully matching.

## Remaining functions


### src/scene/sdChannelSelect/iplSDChannelSelect

- `ipl::scene::SDChannelSelect::flushSaveDataAndMountSD()` 99.657140%: heap and NAND manager loads have reversed operand scheduling. src 0x8c base 0x8c insns 35/35.
- `ipl::scene::SDChannelSelect::handleSDTitleListResult()` 99.152050%: the short initial-result branch uses a different branch sequence plus register choices. src 0x2a8 base 0x2ac insns 170/171.
- `ipl::scene::SDChannelSelect::calcCommon()` 99.074070%: the button call emits an extra unused-parameter load. src 0x1b4 base 0x1b0 insns 109/108.
- `ipl::scene::SDChannelSelect::initializeNormalPage()` 98.936170%: the button call emits an extra unused-parameter load. src 0x17c base 0x178 insns 95/94.
- `ipl::scene::SDChannelSelect::selectChannel(int, int)` 98.305084%: the button call emits an extra unused-parameter load. src 0xf0 base 0xec insns 60/59.
- `ipl::scene::SDChannelSelect::collectTitlesFromNandUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)` 97.833336%: count increment and usage-threshold load scheduling differ. src 0x198 base 0x198 insns 102/102.
- `ipl::scene::SDChannelSelect::collectTitlesByUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)` 97.811880%: count increment and usage-threshold load scheduling differ. src 0x194 base 0x194 insns 101/101.
- `ipl::scene::SDChannelSelect::enqueueNotice(unsigned long, unsigned long, unsigned long)` 97.511110%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0xb8 base 0xb4 insns 46/45.
- `ipl::scene::@unnamed@iplSDChannelSelect_cpp@::SDChannelSelectButtonEventHandler::onEventDerived(unsigned long, unsigned long, const ipl::controller::Interface*)` 95.680560%: event dispatch branches and register allocation differ; the button handler also has different event forwarding blocks. src 0x230 base 0x240 insns 140/144.
- `ipl::scene::SDChannelSelect::enqueueLoadNotice()` 95.652176%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueuePageNotice()` 95.652176%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueResultNotice(unsigned long)` 95.652176%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueMoveNotice(unsigned long, unsigned long, unsigned long)` 95.652176%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueErrorNotice(unsigned long, unsigned long)` 95.652176%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueStateNotice(unsigned long, unsigned long, unsigned long, unsigned long)` 95.130430%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::destroy()` 95.097565%: teardown loop and pointer-reload scheduling differ. src 0x32c base 0x334 insns 203/205.
- `ipl::scene::SDChannelSelect::drawChannelTransitionObjects()` 94.974846%: paired-vector conversion, stack layout and transform scheduling differ. src 0x264 base 0x27c insns 153/159.
- `ipl::scene::SDChannelSelect::enqueueFinishNotice()` 94.444440%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0x4c base 0x48 insns 19/18.
- `ipl::scene::SDChannelSelect::create()` 94.239720%: allocation receivers and polling-loop scheduling differ. src 0x248 base 0x248 insns 146/146.
- `ipl::scene::SDChannelSelect::enqueueStartNotice()` 94.117645%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0x48 base 0x44 insns 18/17.
- `ipl::scene::SDChannelSelect::setChannelScissor(const ipl::scene::SDChannelObj*) const` 93.484980%: floating-point/register scheduling and scissor-bound evaluation differ. src 0x3a4 base 0x3a4 insns 233/233.
- `ipl::scene::SDChannelSelect::isCurrentTitleUsageEnough(const long*) const` 93.078430%: register, stack and operation scheduling differ. src 0xc8 base 0xcc insns 50/51.
- `ipl::scene::SDChannelSelect::enqueueChannelNotice(unsigned long, unsigned long, unsigned long, unsigned long)` 90.869570%: the initialized unused payload word, member reloads and queue-call scheduling differ. src 0x64 base 0x5c insns 25/23.
- `ipl::scene::SDChannelSelect::getCurrentTitleUsage(long*, long*) const` 86.823530%: register, stack and operation scheduling differ. src 0xc4 base 0xcc insns 49/51.
- `ipl::scene::SDChannelSelect::collectTitlesByChannelOrder(const long*, const long*, unsigned long long*, char*, unsigned long*)` 86.555560%: fallback-title blocks and NAND-title reloads differ; the target-derived 126/126 trial retained 22 register/scheduling differences. src 0x1d8 base 0x1f8 insns 118/126.
- `ipl::scene::SDChannelSelect::collectTitlesBySpecialChannels(const long*, const long*, unsigned long long*, char*, unsigned long*)` 71.639890%: sentinel/priority/usage blocks differ; block reconstruction reached 341/361. Output coordinates were kept initialized on unsuccessful lookups. src 0x52c base 0x5a4 insns 331/361.
- `ipl::scene::SDChannelSelect::findAdjacentChannel(int, int*, int*) const` 48.044445%: single-wrap reconstruction reached 45/45 but still had twelve register differences; retained source remains 48/45. src 0xc0 base 0xb4 insns 48/45.

### src/scene/setting/iplSetting

- `ipl::scene::Setting::makeSupportCode()` 99.078950%: string-length registers differ. Reusing a length temporary reduced the ten retained differences to three in a restored trial, without an exact match. src 0x130 base 0x130 insns 76/76.
- `ipl::scene::Setting::convertRevIP(unsigned char*, const char*)` 98.150690%: parser counters and output cursor use different callee-saved registers. src 0x124 base 0x124 insns 73/73.
- `ipl::scene::Setting::createBrowser()` 93.687706%: browser rectangle/stack placement and product-area/page branch structure differ. src 0x4d0 base 0x4b4 insns 308/301.
- `ipl::scene::Setting::draw()` 91.036390%: all original rendering blocks are restored; typed render-mode copy is shorter than original field copies, while stack, register and rectangle conversion scheduling differ. Explicit field-copy trials reached 631/632 but retained many differences. src 0x958 base 0x9e0 insns 598/632.
- `ipl::scene::Setting::scanAP()` 88.106620%: scroll/wait state and animation result normalization differ. Correct pane initialization and reconstructed selection reached 266/272; the scoped BOOL accessor did not change this. src 0x3fc base 0x440 insns 255/272.
- `ipl::scene::Setting::setUSBAP()` 78.421050%: state dispatch and success/completion reloads differ; original-block reconstruction reached 56/57 instructions. src 0xdc base 0xe4 insns 55/57.
- `ipl::scene::Setting::calcKeyboard()` 75.624140%: keyboard-state dispatch, form-pointer selection and masking branches differ. src 0x494 base 0x488 insns 293/290.
- `ipl::scene::Setting::calcNormal()` 67.917960%: dialog-state blocks, controller lifetime and branch/call scheduling differ. src 0x1120 base 0x1218 insns 1096/1158.
- `ipl::scene::Setting::initKeyboard(const char*)` 67.309860%: form-case order, default local initialization, regional row-limit and validation branches differ. src 0x34c base 0x354 insns 211/213.
- `ipl::scene::Setting::validateEULA_()` 64.414894%: TMD result storage, error/success block order and System argument-base scheduling differ. src 0x174 base 0x178 insns 93/94.

### src/scene/sdChannelMemory/iplSDMemory

- `ipl::scene::SDMemory::create(EGG::Heap*, ipl::nand::LayoutFile*, ipl::scene::SDChannelSelect*)` 95.456764%: cached-title visibility, animator reloads and pane-trigger setup differ. src 0x10d8 base 0x10a0 insns 1078/1064.
- `ipl::scene::SDMemory::onDialogState21()` 90.060974%: format initialization and pointer-length arithmetic differ; the original includes a zero-length memset, which was not reproduced as a dummy call. src 0x13c base 0x148 insns 79/82.
- `ipl::scene::SDMemory::drawTransferTitles()` 85.421290%: color conversion/copy lifetimes, clipping, stack and registers differ. Owner-scoped typed GXColor copies and explicit gradient conversions reached 451/451 with 283 differences; restored after the experiment. src 0x698 base 0x70c insns 422/451.

## New function attempt evidence

Each item records a distinct source transformation, its successful object build instruction diff and pool result. Failed builds are not credited toward coverage. Restored trials are not committed changes. No uninitialized payloads, unused button arguments, default keyboard limits or failed-lookup coordinates were introduced to reproduce the original output.


### src/scene/sdChannelSelect/iplSDChannelSelect

- `ipl::scene::SDChannelSelect::startPageTransition(int, int)`: baseline 99.888885%, retained 100.000000%; 6 distinct successful attempts.
  - initialize output by explicit vector conversion expression: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 5: [17, 24, 28, 29, 32]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - scope the transformed input while retaining the animation value: build OK; src 0xc0 base 0xb4 insns 48/45; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - cast the transformed input directly at the animation call: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 6: [17, 24, 28, 29, 31, 32]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - transform the channel origin through an inline vector-returning helper: build FAILED; #   Error:                                                                 ^; #   (10381) illegal access from 'ipl::scene::SDChannelSelect' to protected/.
  - use the vector-returning helper as a direct animation argument: build FAILED; #   Error:                                                                 ^; #   (10381) illegal access from 'ipl::scene::SDChannelSelect' to protected/.
  - retain the returned transformed base vector before animation conversion: build FAILED; #   Error:                                                                 ^; #   (10381) illegal access from 'ipl::scene::SDChannelSelect' to protected/.
  - return the transformed origin through a typed inline scene helper: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass the returned origin directly through the animation vector conversion: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 2: [31, 32]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the transformed helper result before constructing the animation vector: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 5: [17, 24, 28, 29, 32]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::processWorkerCommands()`: baseline 99.800610%, retained 100.000000%; 9 distinct successful attempts.
  - copy the next title usage as the complete typed record: build OK; src 0x518 base 0x518 insns 326/326; diffs 11: [197, 210, 213, 215, 217, 220, 221, 225, 228, 230, 234]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the shifted source record before its destination: build OK; src 0x518 base 0x518 insns 326/326; diffs 16: [197, 210, 213, 215, 217, 220, 221, 222, 225, 226, 227, 228, 229, 230, 231, 234]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - advance the removal search through an explicit while loop: build OK; src 0x518 base 0x518 insns 326/326; diffs 11: [197, 210, 213, 215, 217, 220, 221, 225, 228, 230, 234]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - search and compact NAND title records through the typed inline removal helper: build OK; src 0x518 base 0x518 insns 326/326; diffs 9: [221, 222, 225, 226, 227, 228, 229, 230, 231]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - copy the command title into a named value before removing its usage record: build OK; src 0x518 base 0x518 insns 326/326; diffs 9: [221, 222, 225, 226, 227, 228, 229, 230, 231]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass the deleted title through its explicit title identifier conversion: build OK; src 0x518 base 0x518 insns 326/326; diffs 9: [221, 222, 225, 226, 227, 228, 229, 230, 231]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the shifted source before its destination inside the removal helper: build OK; src 0x518 base 0x518 insns 326/326; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep destination first and bind both shifted records through typed pointers: build OK; src 0x518 base 0x518 insns 326/326; diffs 9: [221, 222, 225, 226, 227, 228, 229, 230, 231]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve source first and copy the complete usage record in the removal helper: build OK; src 0x518 base 0x518 insns 326/326; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::flushSaveDataAndMountSD()`: baseline 99.657140%, retained 99.657140%; 6 distinct successful attempts.
  - resolve flush heap before manager into call-local arguments: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep the manager used for both reset and flush: build OK; src 0x88 base 0x8c insns 34/35; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name the completed-dialog predicate before flush: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the flush heap before the inline manager operation: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass manager and heap through a typed inline save flush helper: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass heap before manager through the typed save flush helper: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::handleSDTitleListResult()`: baseline 99.152050%, retained 99.152050%; 3 distinct successful attempts.
  - test the two accepted results in separate short-circuit comparisons: build OK; src 0x2b8 base 0x2ac insns 174/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - declare the fallback title value before output counters: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - count stored fallback channels after the output store: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::calcCommon()`: baseline 99.074070%, retained 99.074070%; 3 distinct successful attempts.
  - name the optional outgoing handler argument: build OK; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the incoming handler before calling the button: build OK; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use the existing declared default for the optional outgoing handler: build OK; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::initializeNormalPage()`: baseline 98.936170%, retained 98.936170%; 3 distinct successful attempts.
  - name the optional outgoing handler argument: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the incoming handler before calling the button: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use the existing declared default for the optional outgoing handler: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::selectChannel(int, int)`: baseline 98.305084%, retained 98.305084%; 3 distinct successful attempts.
  - name the optional outgoing handler argument: build OK; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the incoming handler before calling the button: build OK; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass both explicitly typed null handler arguments: build FAILED; #   Error:                                                ^^; #   (10473) '<' expected (you may have accidentally used a <: token).
  - retain explicit incoming and outgoing null handlers: build OK; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesFromNandUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 97.833336%, retained 97.833336%; 3 distinct successful attempts.
  - store the incremented output count from its postincrement expression: build OK; src 0x198 base 0x198 insns 102/102; diffs 4: [69, 70, 71, 72]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain threshold values after the count increment: build OK; src 0x198 base 0x198 insns 102/102; diffs 9: [69, 70, 71, 72, 73, 74, 75, 76, 77]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - compare a copied running usage pair after incrementing the count: build OK; src 0x198 base 0x198 insns 102/102; diffs 8: [69, 70, 71, 72, 73, 74, 75, 77]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesByUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 97.811880%, retained 97.811880%; 3 distinct successful attempts.
  - store the incremented output count from its postincrement expression: build OK; src 0x194 base 0x194 insns 101/101; diffs 4: [67, 68, 69, 70]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain threshold values after the count increment: build OK; src 0x194 base 0x194 insns 101/101; diffs 9: [67, 68, 69, 70, 71, 72, 73, 74, 75]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - compare a copied running usage pair after incrementing the count: build OK; src 0x194 base 0x194 insns 101/101; diffs 8: [67, 68, 69, 70, 71, 72, 73, 75]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueNotice(unsigned long, unsigned long, unsigned long)`: baseline 97.511110%, retained 97.511110%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0xd4 base 0xb4 insns 53/45; --- replace mine 10:11 base 10:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0xb8 base 0xb4 insns 46/45; --- replace mine 10:11 base 10:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0xb8 base 0xb4 insns 46/45; --- replace mine 10:11 base 10:12; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::@unnamed@iplSDChannelSelect_cpp@::SDChannelSelectButtonEventHandler::onEventDerived(unsigned long, unsigned long, const ipl::controller::Interface*)`: baseline 95.680560%, retained 95.680560%; 3 distinct successful attempts.
  - forward only states 15, 16, 22 and 23 from the original dispatch: build OK; src 0x240 base 0x240 insns 144/144; diffs 57: [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the corrected dispatch and use a signed state range tree: build OK; src 0x23c base 0x240 insns 143/144; --- insert mine 20:20 base 20:24; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the corrected dispatch and exit immediately on a non-trigger event: build OK; src 0x240 base 0x240 insns 144/144; diffs 57: [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueLoadNotice()`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0x7c base 0x5c insns 31/23; --- replace mine 7:15 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueuePageNotice()`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0x7c base 0x5c insns 31/23; --- replace mine 7:15 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueResultNotice(unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0x7c base 0x5c insns 31/23; --- replace mine 7:15 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueMoveNotice(unsigned long, unsigned long, unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0x7c base 0x5c insns 31/23; --- replace mine 7:15 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueErrorNotice(unsigned long, unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0x7c base 0x5c insns 31/23; --- replace mine 7:15 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueStateNotice(unsigned long, unsigned long, unsigned long, unsigned long)`: baseline 95.130430%, retained 95.130430%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0x7c base 0x5c insns 31/23; --- replace mine 7:15 base 7:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::destroy()`: baseline 95.097565%, retained 95.097565%; 3 distinct successful attempts.
  - read the first list entry before the teardown loop and reload at its tail: build OK; src 0x33c base 0x334 insns 207/205; --- delete mine 11:13 base 11:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - reload the first list entry through an explicit infinite loop: build OK; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep original list traversal and compute each sleep duration at its call: build OK; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::drawChannelTransitionObjects()`: baseline 94.974846%, retained 94.974846%; 3 distinct successful attempts.
  - convert each translated vector through the actual math wrapper before layout use: build OK; src 0x240 base 0x27c insns 144/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - read channel index after validating its page and title readiness: build OK; src 0x264 base 0x27c insns 153/159; --- replace mine 6:9 base 6:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve each target root pane before obtaining its translated vector: build OK; src 0x264 base 0x27c insns 153/159; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueFinishNotice()`: baseline 94.444440%, retained 94.444440%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0x68 base 0x48 insns 26/18; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0x4c base 0x48 insns 19/18; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0x4c base 0x48 insns 19/18; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::create()`: baseline 94.239720%, retained 94.239720%; 3 distinct successful attempts.
  - calculate allocation size before receiver and make BS2 polling an explicit guard loop: build OK; src 0x244 base 0x248 insns 145/146; --- replace mine 105:106 base 105:106; POOL IDENTICAL up to 101 (mine=101 base=101).
  - calculate allocation size first and retain the BS2 manager for polling: build OK; src 0x250 base 0x248 insns 148/146; --- replace mine 15:16 base 15:16; POOL IDENTICAL up to 101 (mine=101 base=101).
  - calculate allocation size first and recheck readiness at the polling tail: build OK; src 0x258 base 0x248 insns 150/146; --- insert mine 107:107 base 107:108; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueStartNotice()`: baseline 94.117645%, retained 94.117645%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0x64 base 0x44 insns 25/17; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0x48 base 0x44 insns 18/17; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0x48 base 0x44 insns 18/17; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::onEventDerived(const char*, unsigned long, ipl::controller::Interface*)`: baseline 94.085720%, retained 100.000000%; 3 distinct successful attempts.
  - dispatch signed events with drag, point and leave blocks in target order: build OK; src 0x1a4 base 0x1a4 insns 105/105; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
  - dispatch signed events with point and leave before drag: build OK; src 0x1a4 base 0x1a4 insns 105/105; diffs 58: [27, 30, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - dispatch unsigned GUI events with target block order: build OK; src 0x1a4 base 0x1a4 insns 105/105; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::onButtonEvent(const char*, unsigned long, const ipl::controller::Interface*)`: baseline 93.736270%, retained 100.000000%; 3 distinct successful attempts.
  - combine left-arrow name and page availability in each event branch: build OK; src 0x16c base 0x16c insns 91/91; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use signed GUI event dispatch with combined arrow guards: build OK; src 0x16c base 0x16c insns 91/91; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
  - combine left-arrow leave guard and nest point availability separately: build OK; src 0x16c base 0x16c insns 91/91; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::setChannelScissor(const ipl::scene::SDChannelObj*) const`: baseline 93.484980%, retained 93.484980%; 3 distinct successful attempts.
  - cache projection width for both untransformed horizontal expressions: build OK; src 0x3a4 base 0x3a4 insns 233/233; diffs 67: [38, 39, 40, 41, 43, 44, 46, 49, 50, 52, 53, 54, 68, 69, 70, 71, 72, 74, 75, 76]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name transformed half-width and half-height before clipping calculations: build OK; src 0x3a4 base 0x3a4 insns 233/233; diffs 67: [38, 39, 40, 41, 43, 44, 46, 49, 50, 52, 53, 54, 68, 69, 70, 71, 72, 74, 75, 76]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - test each offscreen bound through explicit early exits: build OK; src 0x3e0 base 0x3a4 insns 248/233; --- replace mine 38:42 base 38:42; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::isCurrentTitleUsageEnough(const long*) const`: baseline 93.078430%, retained 93.078430%; 3 distinct successful attempts.
  - load byte usage first and return through explicit success/failure blocks: build OK; src 0xcc base 0xcc insns 51/51; diffs 9: [5, 7, 8, 34, 35, 36, 37, 39, 40]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - test independent usage limits with separate early failures: build OK; src 0xd0 base 0xcc insns 52/51; --- insert mine 5:5 base 5:7; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep the matching title record in a const typed reference: build OK; src 0xcc base 0xcc insns 51/51; diffs 9: [5, 7, 8, 34, 35, 36, 37, 39, 40]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueChannelNotice(unsigned long, unsigned long, unsigned long, unsigned long)`: baseline 90.869570%, retained 90.869570%; 3 distinct successful attempts.
  - zero-initialize the complete typed payload before assigning active fields: build OK; src 0x80 base 0x5c insns 32/23; --- replace mine 7:16 base 7:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the third payload word before the active payload fields: build OK; src 0x64 base 0x5c insns 25/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the title identifier before the command tag and arguments: build OK; src 0x64 base 0x5c insns 25/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::getCurrentTitleUsage(long*, long*) const`: baseline 86.823530%, retained 86.823530%; 3 distinct successful attempts.
  - resolve each matching-title field before its usage addition: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - read initial usage through named local values before output stores: build OK; src 0xc4 base 0xcc insns 49/51; --- delete mine 7:8 base 7:7; POOL IDENTICAL up to 101 (mine=101 base=101).
  - search the current title using an explicit while loop: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesByChannelOrder(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 86.555560%, retained 86.555560%; 3 distinct successful attempts.
  - derive empty-channel and matching usage blocks from the original: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 22: [19, 23, 27, 28, 29, 33, 34, 36, 37, 38, 41, 42, 51, 52, 56, 85, 86, 87, 88, 102]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use derived usage blocks with output count stored before threshold reads: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 22: [19, 23, 27, 28, 29, 33, 34, 36, 37, 38, 41, 42, 51, 52, 56, 85, 86, 87, 88, 102]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use derived channel blocks with explicit named matching usage record: build OK; src 0x1ec base 0x1f8 insns 123/126; --- replace mine 5:11 base 5:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesBySpecialChannels(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 71.639890%, retained 71.639890%; 3 distinct successful attempts.
  - derive priority-channel sentinels and indexed title usage from the target blocks: build OK; src 0x554 base 0x5a4 insns 341/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep derived priority handling and store next output counts explicitly: build OK; src 0x554 base 0x5a4 insns 341/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep derived priority handling and name the retained running usage limits: build OK; src 0x554 base 0x5a4 insns 341/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::findAdjacentChannel(int, int*, int*) const`: baseline 48.044445%, retained 48.044445%; 3 distinct successful attempts.
  - use one wrap block and a common found-result return: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 12: [0, 2, 3, 4, 6, 7, 11, 13, 16, 17, 20, 22]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve direction step before reading the current slot: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 15: [2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 17, 20, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - compute destination remainder after testing title presence: build OK; src 0xbc base 0xb4 insns 47/45; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).

### src/scene/setting/iplSetting

- `ipl::scene::Setting::makeSupportCode()`: baseline 99.078950%, retained 99.078950%; 6 distinct successful attempts.
  - reuse the source segment length for the title and code label: build OK; src 0x130 base 0x130 insns 76/76; diffs 3: [54, 58, 61]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - reuse segment lengths while writing the newline as an appended wide character: build OK; src 0x130 base 0x130 insns 76/76; diffs 3: [54, 58, 61]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain a destination cursor alongside reused source segment lengths: build OK; src 0x130 base 0x130 insns 76/76; diffs 3: [54, 58, 61]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - declare the final segment length before assembling other message segments: build OK; src 0x130 base 0x130 insns 76/76; diffs 3: [54, 58, 61]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the final code length as the signed formatting count: build OK; src 0x130 base 0x130 insns 76/76; diffs 3: [54, 58, 61]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain an unsigned code length distinct from the reused segment count: build OK; src 0x130 base 0x130 insns 76/76; diffs 3: [54, 58, 61]; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::convertRevIP(unsigned char*, const char*)`: baseline 98.150690%, retained 98.150690%; 3 distinct successful attempts.
  - retain the original count lifetime but use a signed parsed decimal value: build OK; src 0x124 base 0x124 insns 73/73; diffs 23: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 33, 36, 38, 45, 46, 47, 48, 50]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - compare the capped component as an unsigned converted decimal expression: build OK; src 0x124 base 0x124 insns 73/73; diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - advance the component cursor before incrementing its parsed count: build OK; src 0x124 base 0x124 insns 73/73; diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::createBrowser()`: baseline 93.687706%, retained 93.687706%; 3 distinct successful attempts.
  - derive standard browser dimensions before height and retain a signed product-area range: build OK; src 0x4bc base 0x4b4 insns 303/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - use the target product-area groups and pass named browser dimensions: build OK; src 0x4ac base 0x4b4 insns 299/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - use the target area groups and an explicit named mem2 allocation size: build OK; src 0x4ac base 0x4b4 insns 299/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::scanAP()`: baseline 88.106620%, retained 88.106620%; 4 distinct successful attempts.
  - use virtual pane initialization in states 4 and 9 and explicit scroll direction branches: build OK; src 0x428 base 0x440 insns 266/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - keep pane initialization and test the normalized animation predicate against false: build OK; src 0x428 base 0x440 insns 266/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - keep pane initialization and retain the animation predicate as an integer status: build FAILED; #   Error:                                          ^; #   (10333) object 'animationPlaying' redefined.
  - compare the promoted playing predicate with integer zero: build OK; src 0x428 base 0x440 insns 266/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - scope each animation status inside its actual switch case: build OK; src 0x44c base 0x440 insns 275/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::setUSBAP()`: baseline 78.421050%, retained 78.421050%; 3 distinct successful attempts.
  - put the nickname success branch before failure handling: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - handle state 2 first and then test state 1 using an explicit bounded range: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:8 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - keep success-first handling and branch on the stored completion byte explicitly: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::calcKeyboard()`: baseline 75.624140%, retained 75.624140%; 3 distinct successful attempts.
  - dispatch actual keyboard states through a switch with scoped form selections: build OK; src 0x49c base 0x488 insns 295/290; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - keep the keyboard switch and fetch the form pointer in its own state scope: build OK; src 0x49c base 0x488 insns 295/290; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - keep keyboard switch and mask the security text through a counted for loop: build OK; src 0x498 base 0x488 insns 294/290; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::calcNormal()`: baseline 67.917960%, retained 67.917960%; 3 distinct successful attempts.
  - resolve the young controller after the independent screen-mode guard: build OK; src 0x111c base 0x1218 insns 1095/1158; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - split the sensor-bar transition tick comparison into ordered branch guards: build OK; src 0x1124 base 0x1218 insns 1097/1158; --- replace mine 36:37 base 36:37; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain child scene state before interpreting the parental-dialog result: build OK; src 0x1120 base 0x1218 insns 1096/1158; --- replace mine 36:37 base 36:37; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::initKeyboard(const char*)`: baseline 67.309860%, retained 67.309860%; 3 distinct successful attempts.
  - sign-extend product area and name the keyboard form for validation guards: build OK; src 0x34c base 0x354 insns 211/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain signed product area and resolve nickname keyboard limits in original assignment order: build OK; src 0x34c base 0x354 insns 211/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - use signed area and explicit country-specific parental row limits: build OK; src 0x348 base 0x354 insns 210/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::validateEULA_()`: baseline 64.414894%, retained 64.414894%; 3 distinct successful attempts.
  - derive error-first TMD blocks and initialize content result in the success block: build OK; src 0x180 base 0x178 insns 96/94; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive error-first blocks with content status initialized before lookup: build OK; src 0x174 base 0x178 insns 93/94; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive error-first blocks and retain the title view free as a named heap operation: build OK; src 0x178 base 0x178 insns 94/94; diffs 52: [6, 8, 9, 11, 12, 13, 23, 24, 25, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46]; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::draw()`: baseline 49.120255%, retained 91.036390%; 9 distinct successful attempts.
  - resolve both texture rectangles before converting browser animation visibility: build OK; src 0x674 base 0x9e0 insns 413/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain texture materials only for the corresponding standard and wide bindings: build OK; src 0x658 base 0x9e0 insns 406/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - cache the render mode after saving the AP clipping rectangle: build OK; src 0x66c base 0x9e0 insns 411/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive original texture scan, side draws, fade guard and main layout scissor: build FAILED; #   Error:                                                                 ^; #   (10247) illegal explicit conversion from 'unsigned char *' to.
  - derive blocks with countdown pixel scan: build FAILED; #   Error:                                                                 ^; #   (10247) illegal explicit conversion from 'unsigned char *' to.
  - derive blocks with wide projection rectangle reused for halves: build FAILED; #   Error:                                                                 ^; #   (10247) illegal explicit conversion from 'unsigned char *' to.
  - derive original texture scan, side draws, fade guard and main layout scissor: build OK; src 0x968 base 0x9e0 insns 602/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive blocks with countdown pixel scan: build OK; src 0x964 base 0x9e0 insns 601/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive blocks with wide projection rectangle reused for halves: build OK; src 0x974 base 0x9e0 insns 605/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
  - restore RGB565 and copy projection rectangle before field assignment: build OK; src 0x958 base 0x9e0 insns 598/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
  - copy real render mode fields and sample arrays: build OK; src 0x9dc base 0x9e0 insns 631/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
  - copy real render mode with seven filter byte assignments: build OK; src 0x9ec base 0x9e0 insns 635/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).

### src/scene/sdChannelMemory/iplSDMemory

- `ipl::scene::SDMemory::onDialogState8()`: baseline 99.778480%, retained 100.000000%; 3 distinct successful attempts.
  - set the header directly through the typed lookup expression and convert row counts inline: build OK; src 0x274 base 0x278 insns 157/158; --- replace mine 49:50 base 49:50; POOL IDENTICAL up to 90 (mine=90 base=90).
  - scope the header lookup separately from subsequent body pane lifetimes: build OK; src 0x278 base 0x278 insns 158/158; diffs 3: [83, 89, 91]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - reuse a typed title textbox for the header and each body string: build OK; src 0x278 base 0x278 insns 158/158; diffs 0: []; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::create(EGG::Heap*, ipl::nand::LayoutFile*, ipl::scene::SDChannelSelect*)`: baseline 95.456764%, retained 95.456764%; 3 distinct successful attempts.
  - emit the short title-cache layout before the expanded layout: build OK; src 0x10d8 base 0x10a0 insns 1078/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - use the corrected cache-layout order and reuse the cache count as scan cursor: build OK; src 0x10d8 base 0x10a0 insns 1078/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - use corrected cache-layout branches and restart the existing arrow animator through one lookup: build OK; src 0x10cc base 0x10a0 insns 1075/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::onDialogState21()`: baseline 90.060974%, retained 90.060974%; 3 distinct successful attempts.
  - count the prefix as unsigned bytes and clear the first character through the wide-string API: build OK; src 0x140 base 0x148 insns 80/82; --- insert mine 28:28 base 28:30; POOL IDENTICAL up to 90 (mine=90 base=90).
  - count the prefix as unsigned bytes and initialize the allocated format array: build OK; src 0x15c base 0x148 insns 87/82; --- replace mine 5:8 base 5:8; POOL IDENTICAL up to 90 (mine=90 base=90).
  - count the prefix as unsigned bytes and advance the suffix through a named pointer: build OK; src 0x138 base 0x148 insns 78/82; --- replace mine 28:29 base 28:29; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::drawTransferTitles()`: baseline 85.421290%, retained 85.421290%; 6 distinct successful attempts.
  - retain memo vertical position from the pane translation before copying the vector: build OK; src 0x694 base 0x70c insns 421/451; --- replace mine 23:24 base 23:24; POOL IDENTICAL up to 90 (mine=90 base=90).
  - retain separate gradient colors using the declared GX color conversion: build OK; src 0x6a8 base 0x70c insns 426/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - compute each row clipping coordinate before the inclusive vertical bounds: build OK; src 0x698 base 0x70c insns 422/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - construct a typed color from the raw GX value and reuse it for both gradient ends: build OK; src 0x6cc base 0x70c insns 435/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - construct a typed color from raw GX and convert each gradient argument explicitly: build OK; src 0x70c base 0x70c insns 451/451; diffs 283: [23, 26, 33, 34, 36, 37, 39, 41, 43, 47, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - construct raw and typed colors with separate gradient endpoints: build OK; src 0x6dc base 0x70c insns 439/451; --- replace mine 23:24 base 23:24; POOL IDENTICAL up to 90 (mine=90 base=90).

## Other experiments

- declare APEvent after Setting inside the owner guard: build OK; vtable offsets {"__vt__Q33ipl5scene7Setting": "0xeb4", "__vt__Q33ipl5scene7APEvent": "0xe9c"}; POOL IDENTICAL up to 108 (mine=108 base=108).
- define the real APEvent constructor out of class before the scene constructor: build OK; vtable offsets {"__vt__Q33ipl5scene7Setting": "0xe9c", "__vt__Q33ipl5scene7APEvent": "0xf04"}; POOL IDENTICAL up to 108 (mine=108 base=108).
- define the real APEvent constructor out of class in the owner header: build OK; vtable offsets {"__vt__Q33ipl5scene7Setting": "0xe9c", "__vt__Q33ipl5scene7APEvent": "0xf04"}; POOL IDENTICAL up to 108 (mine=108 base=108).
- owner-scoped BOOL animation status with actual pane initialization: build OK; src 0x428 base 0x440 insns 266/272. isAnimating, changeVideoMode and isWaitPlaying remained exact; the temporary shared header was restored.
- The Memory color-copy experiments used a temporary owner-only guard in Color.h. Raw GXColor, explicit typed gradient conversions and separate gradient colors were all built and restored; no Color.h change remains.

## Commits and changed files

- 588bf767 match sd channel event dispatch
- bc8ef401 match sd button hover guards
- a2c48d1b match sd memory title text lifetimes
- 93b2938c restore setting event table order
- 21b37264 match sd page transition vector return
- 1c31d13a match sd nand title compaction
- 9054278c restore setting browser draw blocks
- 9052c5c8 restore scene function source order
- `include/scene/sdChannelSelect/iplSDChannelSelect.h`
- `include/scene/setting/iplSetting.h`
- `src/scene/sdChannelMemory/iplSDMemory.cpp`
- `src/scene/sdChannelSelect/iplSDChannelSelect.cpp`
- `src/scene/setting/iplSetting.cpp`
- b623450b guard setting event declaration order
- `tools/decomp-assist/sol-low-scenes-round4.md` records this round.

## Gate blocks

Every captured full gate output for this round is copied verbatim below. Each source commit followed a full GATE PASS. The final block covers all three touched units.

### sol-r4-baseline-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 21832/33828 data 224/2960 functions 98/129 fuzzy 97.2361 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 98/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.23614
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 99.80061
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: startPageTransition__Q33ipl5scene15SDChannelSelectFii 99.888885
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q33ipl5scene15SDChannelSelectFPCcUlPQ33ipl10controller9Interface 94.08572
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onButtonEvent__Q33ipl5scene15SDChannelSelectFPCcUlPCQ33ipl10controller9Interface 93.73627
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 90.1537 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15373
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.650635
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState8__Q33ipl5scene8SDMemoryFv 99.77848
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.63994
global fuzzy_match_percent: 97.17255 -> 97.17255
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-resume-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 22616/33828 data 224/2960 functions 100/129 fuzzy 97.3770 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 100/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.37697
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 99.80061
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: startPageTransition__Q33ipl5scene15SDChannelSelectFii 99.888885
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 90.1537 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15373
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.650635
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState8__Q33ipl5scene8SDMemoryFv 99.77848
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.66612
global fuzzy_match_percent: 97.17255 -> 97.17413
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-gate-event.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 22252/33828 data 224/2960 functions 99/129 fuzzy 97.3096 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 99/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.30956
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 99.80061
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: startPageTransition__Q33ipl5scene15SDChannelSelectFii 99.888885
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onButtonEvent__Q33ipl5scene15SDChannelSelectFPCcUlPCQ33ipl10controller9Interface 93.73627
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 90.1537 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15373
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.650635
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState8__Q33ipl5scene8SDMemoryFv 99.77848
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.65396
global fuzzy_match_percent: 97.17255 -> 97.17339
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-gate-button.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 22616/33828 data 224/2960 functions 100/129 fuzzy 97.3770 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 100/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.37697
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 99.80061
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: startPageTransition__Q33ipl5scene15SDChannelSelectFii 99.888885
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 90.1537 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15373
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 13852/20872 data 200/3344 functions 62/66 fuzzy 97.6506 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 61/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.650635
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState8__Q33ipl5scene8SDMemoryFv 99.77848
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.66612
global fuzzy_match_percent: 97.17255 -> 97.17413
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-gate-memory.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 22616/33828 data 224/2960 functions 100/129 fuzzy 97.3770 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 100/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.37697
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 99.80061
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: startPageTransition__Q33ipl5scene15SDChannelSelectFii 99.888885
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 90.1537 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15373
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 97.6573 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.65734
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.68722
global fuzzy_match_percent: 97.17255 -> 97.17418
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-gate-data.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 22616/33828 data 224/2960 functions 100/129 fuzzy 97.3770 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 100/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.37697
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 99.80061
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: startPageTransition__Q33ipl5scene15SDChannelSelectFii 99.888885
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 90.1537 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15373
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 97.6573 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.65734
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.68722
global fuzzy_match_percent: 97.17255 -> 97.17418
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-gate-transition.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 22796/33828 data 224/2960 functions 101/129 fuzzy 97.3776 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 101/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.377556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 99.80061
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 90.1537 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15373
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 97.6573 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.65734
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.69322
global fuzzy_match_percent: 97.17255 -> 97.17420
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-gate-removal.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 97.3852 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.38525
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 90.1537 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15373
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 97.6573 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.65734
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.73676
global fuzzy_match_percent: 97.17255 -> 97.17429
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-gate-draw.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 97.3852 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.38525
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 92.9508 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 92.9508
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 97.6573 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.65734
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.73676
global fuzzy_match_percent: 97.17255 -> 97.20967
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-gate-order.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 97.3852 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.38525
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 92.9508 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 92.9508
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 97.6573 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.65734
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.73676
global fuzzy_match_percent: 97.17255 -> 97.20967
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-final-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 97.3852 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.38525
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 92.9508 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 92.9508
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 97.6573 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.65734
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.73676
global fuzzy_match_percent: 97.17255 -> 97.20967
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r4-final-owner-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 97.3852 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 97.38525
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: create__Q33ipl5scene15SDChannelSelectFv 94.23972
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStartNotice__Q33ipl5scene15SDChannelSelectFv 94.117645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueFinishNotice__Q33ipl5scene15SDChannelSelectFv 94.44444
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 97.51111
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueLoadNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueuePageNotice__Q33ipl5scene15SDChannelSelectFv 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueResultNotice__Q33ipl5scene15SDChannelSelectFUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueChannelNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 90.86957
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueMoveNotice__Q33ipl5scene15SDChannelSelectFUlUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueStateNotice__Q33ipl5scene15SDChannelSelectFUlUlUlUl 95.13043
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: enqueueErrorNotice__Q33ipl5scene15SDChannelSelectFUlUl 95.652176
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: isCurrentTitleUsageEnough__Q33ipl5scene15SDChannelSelectCFPCl 93.07843
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: getCurrentTitleUsage__Q33ipl5scene15SDChannelSelectCFPlPl 86.82353
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.81188
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesFromNandUsage__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.833336
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 86.55556
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 71.63989
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 48.044445
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 21832/33828 data 224 functions 98 fuzzy 97.2361
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25220/37884 data 1040/5696 functions 102/112 fuzzy 92.9508 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 101/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 92.9508
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 90.1537
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 97.6573 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 97.65734
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 95.456764
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 13852/20872 data 200 functions 62 fuzzy 97.6506
regressions vs baseline: 0
global matched_code_percent: 83.63994 -> 83.73676
global fuzzy_match_percent: 97.17255 -> 97.20967
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 89.93564 -> 89.93564
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
