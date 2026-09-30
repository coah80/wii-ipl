# Scenes round 6 attempts

Baseline: merged main `c923937c`. All original functions are present. Only the worker checkout and /tmp were used. Matching configuration was unchanged.

Coverage: all 27 initially open Select functions, eight initially open Setting functions and three initially open Memory functions received at least three distinct successful source builds this round. Earlier-round attempts are excluded. Failed builds do not count toward coverage. Trials are listed by baseline percentage.

No new instruction-exact functions or matched code/data bytes were gained. Retained changes restore original creation and dispatch behavior and improve Setting and Memory fuzzy scores. All three units remain incomplete.

## Measurements

- `src/scene/sdChannelSelect/iplSDChannelSelect`: instruction-exact 102 -> 102; objdiff exact 102 -> 102; matched code 24100 -> 24100/33828; matched data 224 -> 224/2960; fuzzy 98.042570% -> 98.042570%.
- `src/scene/setting/iplSetting`: instruction-exact 103 -> 103; objdiff exact 104 -> 104; matched code 30156 -> 30156/37884; matched data 1040 -> 1040/5696; fuzzy 98.495830% -> 98.664870%.
- `src/scene/sdChannelMemory/iplSDMemory`: instruction-exact 62 -> 62; objdiff exact 63 -> 63; matched code 14484 -> 14484/20872; matched data 200 -> 200/3344; fuzzy 97.657340% -> 98.189730%.

Function experiments: 144 successful builds and 6 failed builds.

## Retained changes

- Setting createBrowser registers the HTML layout archive from mpSettingHTMLFile and the browser configuration archive from mpWWWArchiveFile, following the original .64 and .68 member loads. The direct-page fallback remains initialized. The function improves from 98.843860% to 98.850500%, with 299/301 instructions.
- Setting validateEULA_ reuses the original status slot for GetTmdView and ContentExist, clears that status in the success block and initializes validity before lookup. The status and view are initialized on every path. The function improves from 81.212770% to 86.308510%, with 94/94 instructions and register/scheduling differences.
- Setting setUSBAP dispatches actual states 1 and 2 through a switch and places successful nickname initialization before the failure block. The function improves from 78.421050% to 98.070175%, with 56/57 instructions. The remaining difference is the original separate completion-byte condition/argument reload.
- Memory create uses static casts for the sixteen known TextBox panes, reads cached titles from the savedata manager field, retains the scroll animator across initialization and restart, restores the original dialog-layout binding receiver after background creation and writes the missing final transfer flag. The function improves from 95.456764% to 98.067670%, with 1060/1064 instructions. The indexed cache accessor is guarded by IPL_SDMEMORY_TITLE_CACHE_ACCESS, which only Memory.cpp defines.
- Select remains unchanged. The six flush experiments all retain exactly two reversed manager/heap loads. Source wrappers were restored after they did not change those instructions. All other unsuccessful Select trials were restored.

## Data and function-order audit

- All three pools are identical. Every original function exists. No owned assembly bodies remain. Explicit original function definitions retain their relative order; the three compiler-emitted Memory iterator helpers retain their existing ordering difference.
- Select .rodata/.sdata/.sdata2 and Memory .sdata/.sdata2 retain 100% objdiff section scores. Setting .bss/.sbss/.sdata/.sdata2 retain 100% section scores. Section-end alignment differences were not filled with artificial objects.
- Select .data remains 2736 bytes at 35.06984%; Setting .data remains 4016 bytes at 5.146636%; Memory .data remains 3144 bytes. Ordinary vtable relocations still differ from the extracted original deduplicated zero-filled weak data. Actual scene/handler tables and vtables retain their established order; no synthetic replacement vtables were introduced.
- Setting .rodata remains 600 versus 640 target bytes, at 32.25412%. Original scNumber/scNumber2 are two local 20-byte wide digit maps containing characters 0 through 9. The original unit has no relocation reference to either map, including section-relative references to their ranges. Their source callers remain unknown. Their local linkage was not changed to force emission, and no artificial references were added.
- The extracted original animation-table symbol spans 424 bytes, while the source named animation table spans 232 bytes and compiler jump tables follow it. The original symbol size was preserved.
- Raw instruction decoding undercounts objdiff-exact Setting::calcFadeout and Memory::updateState around CR1 varargs. Both raw and objdiff counts are reported; the decoder was unchanged.

Fresh ELF audit:

```text
src/scene/sdChannelSelect/iplSDChannelSelect: missing original functions []
  original strong-function relative order identical True
  .rodata original/source size 64/64
  .data original/source size 2736/2736
  .sdata2 original/source size 80/80
  .sdata original/source size 80/79
src/scene/setting/iplSetting: missing original functions []
  original strong-function relative order identical True
  .bss original/source size 456/456
  .rodata original/source size 640/600
  .data original/source size 4016/4016
  .sdata2 original/source size 64/60
  .sdata original/source size 504/500
  .sbss original/source size 16/12
  __vt__Q33ipl5scene7APEvent original/source 0xe9c/0xe9c
  __vt__Q33ipl5scene7Setting original/source 0xeb4/0xeb4
  scNumber__Q23ipl5scene binding STB_LOCAL values [48, 49, 50, 51, 52, 53, 54, 55, 56, 57]
    original relocation references []
  scNumber2__Q23ipl5scene binding STB_LOCAL values [48, 49, 50, 51, 52, 53, 54, 55, 56, 57]
    original relocation references []
  original .rodata relocation targets ['lbl_81610AF0', 'lbl_81610B20', 'lbl_81610B80', 'scAnmTable__Q23ipl5scene']
src/scene/sdChannelMemory/iplSDMemory: missing original functions []
  original strong-function relative order identical True
  original compiler-emitted iterator helpers precede the two scene helpers in source output; original extracted helper ordering differs
  .data original/source size 3144/3144
  .sdata2 original/source size 48/48
  .sdata original/source size 152/152
```

## Remaining functions


### src/scene/sdChannelSelect/iplSDChannelSelect

- `ipl::scene::SDChannelSelect::flushSaveDataAndMountSD()` 99.657140%: heap and NAND manager loads have reversed operand scheduling. src 0x8c base 0x8c insns 35/35.
- `ipl::scene::SDChannelSelect::handleSDTitleListResult()` 99.152050%: the short initial-result branch uses a different branch sequence plus register choices. src 0x2a8 base 0x2ac insns 170/171.
- `ipl::scene::SDChannelSelect::calcCommon()` 99.074070%: the button call emits an extra unused-parameter load. src 0x1b4 base 0x1b0 insns 109/108.
- `ipl::scene::SDChannelSelect::initializeNormalPage()` 98.936170%: the button call emits an extra unused-parameter load. src 0x17c base 0x178 insns 95/94.
- `ipl::scene::@unnamed@iplSDChannelSelect_cpp@::SDChannelSelectButtonEventHandler::onEventDerived(unsigned long, unsigned long, const ipl::controller::Interface*)` 98.541664%: 144/144 forwarding instructions retain receiver/register allocation and an initialized unused button argument. src 0x240 base 0x240 insns 144/144.
- `ipl::scene::SDChannelSelect::selectChannel(int, int)` 98.305084%: the button call emits an extra unused-parameter load. src 0xf0 base 0xec insns 60/59.
- `ipl::scene::SDChannelSelect::collectTitlesFromNandUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)` 97.833336%: count increment and usage-threshold load scheduling differ. src 0x198 base 0x198 insns 102/102.
- `ipl::scene::SDChannelSelect::collectTitlesByUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)` 97.811880%: count increment and usage-threshold load scheduling differ. src 0x194 base 0x194 insns 101/101.
- `ipl::scene::SDChannelSelect::enqueueNotice(unsigned long, unsigned long, unsigned long)` 97.511110%: initialized payload stores, member reloads and queue-call scheduling differ. src 0xb8 base 0xb4 insns 46/45.
- `ipl::scene::SDChannelSelect::collectTitlesByChannelOrder(const long*, const long*, unsigned long long*, char*, unsigned long*)` 97.293650%: 126/126 instructions retain usage-record reload scheduling and register differences. src 0x1f8 base 0x1f8 insns 126/126.
- `ipl::scene::SDChannelSelect::enqueueLoadNotice()` 95.652176%: initialized payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueuePageNotice()` 95.652176%: initialized payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueResultNotice(unsigned long)` 95.652176%: initialized payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueMoveNotice(unsigned long, unsigned long, unsigned long)` 95.652176%: initialized payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueErrorNotice(unsigned long, unsigned long)` 95.652176%: initialized payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueStateNotice(unsigned long, unsigned long, unsigned long, unsigned long)` 95.130430%: initialized payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::destroy()` 95.097565%: teardown loop and pointer-reload scheduling differ. src 0x32c base 0x334 insns 203/205.
- `ipl::scene::SDChannelSelect::drawChannelTransitionObjects()` 94.974846%: paired-vector conversion, stack layout and transform scheduling differ. src 0x264 base 0x27c insns 153/159.
- `ipl::scene::SDChannelSelect::enqueueFinishNotice()` 94.444440%: initialized payload stores, member reloads and queue-call scheduling differ. src 0x4c base 0x48 insns 19/18.
- `ipl::scene::SDChannelSelect::create()` 94.239720%: allocation receivers and polling-loop scheduling differ. src 0x248 base 0x248 insns 146/146.
- `ipl::scene::SDChannelSelect::enqueueStartNotice()` 94.117645%: initialized payload stores, member reloads and queue-call scheduling differ. src 0x48 base 0x44 insns 18/17.
- `ipl::scene::SDChannelSelect::setChannelScissor(const ipl::scene::SDChannelObj*) const` 93.484980%: floating-point/register scheduling and scissor-bound evaluation differ. src 0x3a4 base 0x3a4 insns 233/233.
- `ipl::scene::SDChannelSelect::isCurrentTitleUsageEnough(const long*) const` 93.078430%: register, stack and operation scheduling differ. src 0xc8 base 0xcc insns 50/51.
- `ipl::scene::SDChannelSelect::enqueueChannelNotice(unsigned long, unsigned long, unsigned long, unsigned long)` 90.869570%: initialized payload stores, member reloads and queue-call scheduling differ. src 0x64 base 0x5c insns 25/23.
- `ipl::scene::SDChannelSelect::getCurrentTitleUsage(long*, long*) const` 86.823530%: register, stack and operation scheduling differ. src 0xc4 base 0xcc insns 49/51.
- `ipl::scene::SDChannelSelect::findAdjacentChannel(int, int*, int*) const` 81.777780%: 45/45 common-loop instructions still allocate page, slot and return values to different registers; early current-page load scheduling differs. src 0xb4 base 0xb4 insns 45/45.
- `ipl::scene::SDChannelSelect::collectTitlesBySpecialChannels(const long*, const long*, unsigned long long*, char*, unsigned long*)` 77.944595%: priority lookup sentinels, initialized coordinates, cache bounds and register lifetimes differ; the body has 350/361 instructions. src 0x578 base 0x5a4 insns 350/361.

### src/scene/setting/iplSetting

- `ipl::scene::Setting::createBrowser()` 98.850500%: correct archive registration is restored; rectangle conversion, stack placement and initialized direct-page dispatch leave 299/301 instructions. src 0x4ac base 0x4b4 insns 299/301.
- `ipl::scene::Setting::convertRevIP(unsigned char*, const char*)` 98.150690%: parser counters and output cursor use different callee-saved registers. src 0x124 base 0x124 insns 73/73.
- `ipl::scene::Setting::setUSBAP()` 98.070175%: state and success/failure blocks are restored; the compiler shares the tested completion byte with the call argument instead of the original separate reload at 56/57 instructions. src 0xe0 base 0xe4 insns 56/57.
- `ipl::scene::Setting::scanAP()` 94.562500%: animation-result normalization, dispatch and reload scheduling leave 266/272 instructions. src 0x428 base 0x440 insns 266/272.
- `ipl::scene::Setting::initKeyboard(const char*)` 93.309860%: initialized default limits, supported-form dispatch and allocation leave 212/213 instructions. src 0x350 base 0x354 insns 212/213.
- `ipl::scene::Setting::calcKeyboard()` 92.420690%: initialized default form text, supported-form dispatch and member reloads leave 289/290 instructions. src 0x484 base 0x488 insns 289/290.
- `ipl::scene::Setting::draw()` 91.036390%: the render-mode aggregate copy is shorter than the original field copies; stack placement and floating scheduling differ at 598/632 instructions. src 0x958 base 0x9e0 insns 598/632.
- `ipl::scene::Setting::validateEULA_()` 86.308510%: the shared initialized lookup/content status is restored; argument-base lifetime, validity allocation and scheduling still differ at 94/94 instructions. src 0x178 base 0x178 insns 94/94.

### src/scene/sdChannelMemory/iplSDMemory

- `ipl::scene::SDMemory::create(EGG::Heap*, ipl::nand::LayoutFile*, ipl::scene::SDChannelSelect*)` 98.067670%: original pane, binding and flag blocks are restored; true-visibility inlining and allocation/register scheduling differ at 1060/1064 instructions. src 0x1090 base 0x10a0 insns 1060/1064.
- `ipl::scene::SDMemory::onDialogState21()` 90.060974%: format initialization and pointer-length arithmetic differ; original empty-prefix initialization includes a zero-length memset whose source remains uncertain. Real prefix-copy trials did not match. src 0x13c base 0x148 insns 79/82.
- `ipl::scene::SDMemory::drawTransferTitles()` 85.421290%: color conversion, clipping, stack and register lifetimes differ at 422/451 instructions. The three gradient/clipping/iterator trials did not match. src 0x698 base 0x70c insns 422/451.

## New function attempt evidence

Each item records a distinct source transformation, its successful object build, instruction diff and pool result. Failed builds are separate. Restored experiments are not retained improvements. Payload words, button arguments, unsupported keyboard limits and failed-lookup coordinates remain initialized.


### src/scene/sdChannelSelect/iplSDChannelSelect

- `ipl::scene::SDChannelSelect::flushSaveDataAndMountSD()`: baseline 99.657140%, retained 99.657140%; 6 distinct successful attempts.
  - read the named heap before a named save manager and invoke its flush: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind actual save manager and application heap as typed references: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the asynchronous file inside a heap scope before storing it: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the actual application heap through a named asynchronous save helper: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the asynchronous save helper manager separately from its incoming heap: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the actual application heap as a helper reference before asynchronous flushing: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::handleSDTitleListResult()`: baseline 99.152050%, retained 99.152050%; 3 distinct successful attempts.
  - compare the location-missing result before the successful result: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use an explicit fallback slot while loop and test the result before its added flag: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep a typed channel-title slot through the binary search and fallback clear: build FAILED; #   Error:                                                                 ^; #   (10209) illegal implicit conversion from 'unsigned long *' to.
  - keep the actual 32-bit channel-title slot through its binary search and clear: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::calcCommon()`: baseline 99.074070%, retained 99.074070%; 3 distinct successful attempts.
  - resolve the new active handler through a named pointer before installation: build OK; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass an explicitly typed null outgoing handler to the actual button API: build FAILED; #   Error:                                                                 ^^; #   (10473) '<' expected (you may have accidentally used a <: token).
  - retain a named button receiver specifically for handler installation: build OK; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass the actual typed null handler using an unambiguous template spelling: build OK; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::initializeNormalPage()`: baseline 98.936170%, retained 98.936170%; 3 distinct successful attempts.
  - resolve the new active handler through a named pointer before installation: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass an explicitly typed null outgoing handler to the actual button API: build FAILED; #   Error:                                                                 ^^; #   (10473) '<' expected (you may have accidentally used a <: token).
  - retain a named button receiver specifically for handler installation: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass the actual typed null handler using an unambiguous template spelling: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::@unnamed@iplSDChannelSelect_cpp@::SDChannelSelectButtonEventHandler::onEventDerived(unsigned long, unsigned long, const ipl::controller::Interface*)`: baseline 98.541664%, retained 98.541664%; 3 distinct successful attempts.
  - dispatch the supported button event through an unsigned switch: build OK; src 0x244 base 0x240 insns 145/144; --- replace mine 34:35 base 34:35; POOL IDENTICAL up to 101 (mine=101 base=101).
  - exit unsupported events before entering the button state guards: build OK; src 0x240 base 0x240 insns 144/144; diffs 57: [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - dispatch signed button events and bind the scene button as a typed reference: build OK; src 0x244 base 0x240 insns 145/144; --- replace mine 34:35 base 34:35; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::selectChannel(int, int)`: baseline 98.305084%, retained 98.305084%; 3 distinct successful attempts.
  - resolve the new active handler through a named pointer before installation: build OK; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass an explicitly typed null outgoing handler to the actual button API: build FAILED; #   Error:                                                      ^^; #   (10473) '<' expected (you may have accidentally used a <: token).
  - retain a named button receiver specifically for handler installation: build OK; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass the actual typed null handler using an unambiguous template spelling: build OK; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesFromNandUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 97.833336%, retained 97.833336%; 3 distinct successful attempts.
  - use a discarded postfix output-count increment before usage testing: build OK; src 0x198 base 0x198 insns 102/102; diffs 4: [69, 70, 71, 72]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the commuted next count directly to the output count: build OK; src 0x198 base 0x198 insns 102/102; diffs 4: [69, 70, 71, 72]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the current count and dereference the first usage threshold directly: build OK; src 0x198 base 0x198 insns 102/102; diffs 4: [69, 70, 71, 72]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesByUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 97.811880%, retained 97.811880%; 3 distinct successful attempts.
  - use a discarded postfix output-count increment before usage testing: build OK; src 0x194 base 0x194 insns 101/101; diffs 4: [67, 68, 69, 70]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the commuted next count directly to the output count: build OK; src 0x194 base 0x194 insns 101/101; diffs 4: [67, 68, 69, 70]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the current count and dereference the first usage threshold directly: build OK; src 0x194 base 0x194 insns 101/101; diffs 4: [67, 68, 69, 70]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueNotice(unsigned long, unsigned long, unsigned long)`: baseline 97.511110%, retained 97.511110%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0xd8 base 0xb4 insns 54/45; --- delete mine 4:5 base 4:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0xb8 base 0xb4 insns 46/45; --- replace mine 10:11 base 10:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0xb8 base 0xb4 insns 46/45; --- replace mine 10:11 base 10:12; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesByChannelOrder(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 97.293650%, retained 97.293650%; 3 distinct successful attempts.
  - declare block usage before byte usage to change accumulator lifetimes: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 31: [11, 12, 19, 23, 27, 28, 29, 33, 34, 36, 37, 38, 41, 42, 51, 52, 56, 57, 59, 62]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the ordered channel index to the actual traversal-table entry: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 22: [19, 23, 27, 28, 29, 33, 34, 36, 37, 38, 41, 42, 51, 52, 56, 85, 86, 87, 88, 102]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use discarded postfix increments for NAND records and output count: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 22: [19, 23, 27, 28, 29, 33, 34, 36, 37, 38, 41, 42, 51, 52, 56, 85, 86, 87, 88, 102]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueLoadNotice()`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0x6c base 0x5c insns 27/23; --- replace mine 7:19 base 7:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueuePageNotice()`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0x6c base 0x5c insns 27/23; --- replace mine 7:19 base 7:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueResultNotice(unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0x78 base 0x5c insns 30/23; --- replace mine 7:19 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueMoveNotice(unsigned long, unsigned long, unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0x74 base 0x5c insns 29/23; --- replace mine 7:20 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueErrorNotice(unsigned long, unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0x74 base 0x5c insns 29/23; --- replace mine 7:19 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueStateNotice(unsigned long, unsigned long, unsigned long, unsigned long)`: baseline 95.130430%, retained 95.130430%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0x78 base 0x5c insns 30/23; --- replace mine 7:20 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::destroy()`: baseline 95.097565%, retained 95.097565%; 3 distinct successful attempts.
  - compare real asynchronous completion results explicitly with false: build OK; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the owned worker through cancellation, termination and deletion: build OK; src 0x32c base 0x334 insns 203/205; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve each removed channel through an explicit head-removal loop: build OK; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::drawChannelTransitionObjects()`: baseline 94.974846%, retained 94.974846%; 3 distinct successful attempts.
  - assign each typed translation vector before storing it in the destination pane: build OK; src 0x240 base 0x27c insns 144/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - separate channel visibility and ready-state exits before rendering: build OK; src 0x264 base 0x27c insns 153/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use the equivalent source-coordinate negation and test destination index first: build OK; src 0x264 base 0x27c insns 153/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueFinishNotice()`: baseline 94.444440%, retained 94.444440%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0x58 base 0x48 insns 22/18; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0x4c base 0x48 insns 19/18; --- delete mine 12:13 base 12:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0x4c base 0x48 insns 19/18; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::create()`: baseline 94.239720%, retained 94.239720%; 3 distinct successful attempts.
  - use the platform tick type for startup timestamps and elapsed ticks: build OK; src 0x248 base 0x248 insns 146/146; diffs 84: [30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the scene allocation heap for the two owned UI heaps: build OK; src 0x24c base 0x248 insns 147/146; --- delete mine 30:31 base 30:30; POOL IDENTICAL up to 101 (mine=101 base=101).
  - poll startup through an explicit completed-state exit: build OK; src 0x248 base 0x248 insns 146/146; diffs 87: [30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueStartNotice()`: baseline 94.117645%, retained 94.117645%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0x54 base 0x44 insns 21/17; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0x48 base 0x44 insns 18/17; --- delete mine 12:13 base 12:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0x48 base 0x44 insns 18/17; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::setChannelScissor(const ipl::scene::SDChannelObj*) const`: baseline 93.484980%, retained 93.484980%; 3 distinct successful attempts.
  - resolve projection before converting the channel translation vector: build OK; src 0x3a8 base 0x3a4 insns 234/233; --- replace mine 14:16 base 14:15; POOL IDENTICAL up to 101 (mine=101 base=101).
  - calculate orthographic edges in top, bottom, left and right order: build OK; src 0x3a4 base 0x3a4 insns 233/233; diffs 69: [38, 39, 40, 41, 43, 44, 45, 46, 49, 50, 51, 52, 53, 54, 68, 69, 70, 71, 72, 74]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - expand scissor dimensions before moving the upper-left origin: build OK; src 0x3a4 base 0x3a4 insns 233/233; diffs 71: [38, 39, 40, 41, 43, 44, 46, 49, 50, 52, 53, 54, 68, 69, 70, 71, 72, 74, 75, 76]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::isCurrentTitleUsageEnough(const long*) const`: baseline 93.078430%, retained 93.078430%; 3 distinct successful attempts.
  - declare the lookup cursor before reading the NAND record count: build OK; src 0xc8 base 0xcc insns 50/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - search NAND records with an explicitly initialized while-loop cursor: build OK; src 0xc8 base 0xcc insns 50/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the current identifier as const and compare the terminal cursor with its limit: build OK; src 0xc8 base 0xcc insns 50/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueChannelNotice(unsigned long, unsigned long, unsigned long, unsigned long)`: baseline 90.869570%, retained 90.869570%; 3 distinct successful attempts.
  - construct an immutable fully initialized command aggregate before queue insertion: build OK; src 0x80 base 0x5c insns 32/23; --- replace mine 7:19 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bind the actual command-argument union before writing all payload values: build OK; src 0x64 base 0x5c insns 25/23; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the title identifier before command type and all initialized payload values: build OK; src 0x64 base 0x5c insns 25/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::getCurrentTitleUsage(long*, long*) const`: baseline 86.823530%, retained 86.823530%; 3 distinct successful attempts.
  - declare the lookup cursor before reading the NAND record count: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - search NAND records with an explicitly initialized while-loop cursor: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the current identifier as const and compare the terminal cursor with its limit: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::findAdjacentChannel(int, int*, int*) const`: baseline 81.777780%, retained 81.777780%; 6 distinct successful attempts.
  - initialize the current page on declaration and keep the chosen direction step const: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 9: [0, 2, 3, 4, 6, 13, 16, 17, 22]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - calculate slot remainder before its quotient: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 21: [0, 2, 3, 4, 6, 7, 9, 11, 12, 13, 14, 16, 17, 19, 20, 27, 29, 32, 33, 35]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - store the selected index before page through the common found return: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 11: [0, 2, 3, 4, 6, 13, 16, 17, 22, 35, 37]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize forward direction before current coordinates and branch after linearizing the current slot: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 12: [0, 2, 3, 4, 6, 7, 11, 13, 16, 17, 20, 22]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize forward direction and the next slot before reading page bounds: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 18: [0, 2, 3, 4, 6, 7, 11, 13, 14, 16, 17, 19, 20, 22, 27, 29, 33, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - assign the chosen direction before retaining the current page as const: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 12: [0, 2, 3, 4, 6, 7, 11, 13, 16, 17, 20, 22]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesBySpecialChannels(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 77.944595%, retained 77.944595%; 3 distinct successful attempts.
  - declare initialized priority coordinates before the NAND usage indices: build OK; src 0x57c base 0x5a4 insns 351/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - predecrement the bounded cache cursor in the loop condition: build OK; src 0x57c base 0x5a4 insns 351/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - exclude the second priority title before the first priority title: build OK; src 0x578 base 0x5a4 insns 350/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).

### src/scene/setting/iplSetting

- `ipl::scene::Setting::createBrowser()`: baseline 98.843860%, retained 98.850500%; 3 distinct successful attempts.
  - restore original HTML archive and browser configuration file registration receivers: build OK; src 0x4ac base 0x4b4 insns 299/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - restore registration and give the direct-page fallback its own initialized default path: build OK; src 0x4b8 base 0x4b4 insns 302/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - restore registration and scan direct-page names with an initialized while-loop cursor: build OK; src 0x4ac base 0x4b4 insns 299/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::convertRevIP(unsigned char*, const char*)`: baseline 98.150690%, retained 98.150690%; 6 distinct successful attempts.
  - assign component cursors after character conversion before scanning: build OK; src 0x124 base 0x124 insns 73/73; diffs 26: [6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the first output slot separately from the advancing component cursor: build OK; src 0x11c base 0x124 insns 71/73; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 108 (mine=108 base=108).
  - resolve a typed component substring before decimal conversion: build OK; src 0x124 base 0x124 insns 73/73; diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - declare the parsed component count before its actual conversion buffer: build OK; src 0x124 base 0x124 insns 73/73; diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain a named scanning index in a while loop before the advancing output cursor: build OK; src 0x124 base 0x124 insns 73/73; diffs 16: [6, 8, 12, 15, 16, 17, 18, 19, 21, 29, 30, 36, 38, 45, 47, 48]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - resolve the output cursor before component offsets and advance count before storing the next offset: build OK; src 0x124 base 0x124 insns 73/73; diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::scanAP()`: baseline 94.562500%, retained 94.562500%; 3 distinct successful attempts.
  - bind each selected scroll animator before initializing its frame: build OK; src 0x428 base 0x440 insns 266/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - compare actual animation completion with an explicit false value: build OK; src 0x428 base 0x440 insns 266/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - initialize the pane manager through a typed reference in a receiver scope: build OK; src 0x428 base 0x440 insns 266/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::initKeyboard(const char*)`: baseline 93.309860%, retained 93.309860%; 3 distinct successful attempts.
  - initialize supported keyboard string limits before row limits: build OK; src 0x350 base 0x354 insns 212/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the actual memo form while selecting its regional dictionaries: build FAILED; #   Error:                                          ^^^^^^^^; #   (10140) undefined identifier 'MemoForm'.
  - construct the keyboard setting aggregate in physical member order: build OK; src 0x350 base 0x354 insns 212/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the declared memo input form while selecting its regional dictionaries: build OK; src 0x34c base 0x354 insns 211/213; --- delete mine 17:18 base 17:17; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::calcKeyboard()`: baseline 92.420690%, retained 92.420690%; 3 distinct successful attempts.
  - retain the current mask-character pointer while advancing its index: build OK; src 0x480 base 0x488 insns 288/290; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 108 (mine=108 base=108).
  - dispatch each original supported form explicitly in completion state: build FAILED; #   Error:                                     ^; #   (10121) declaration syntax error.
  - initialize the shared form pointer before dispatch and advance mask index separately: build OK; src 0x480 base 0x488 insns 288/290; --- delete mine 6:7 base 6:6; POOL IDENTICAL up to 108 (mine=108 base=108).
  - dispatch the actual supported completion forms through separate switch cases: build OK; src 0x490 base 0x488 insns 292/290; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::draw()`: baseline 91.036390%, retained 91.036390%; 3 distinct successful attempts.
  - copy render mode through its actual const source object reference: build OK; src 0x958 base 0x9e0 insns 598/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
  - initialize the existing wide texture object before receiving browser texture data: build OK; src 0x970 base 0x9e0 insns 604/632; --- replace mine 14:15 base 14:15; POOL IDENTICAL up to 108 (mine=108 base=108).
  - compare draw-layer membership directly with zero: build OK; src 0x958 base 0x9e0 insns 598/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::validateEULA_()`: baseline 81.212770%, retained 86.308510%; 9 distinct successful attempts.
  - test title-unavailable results in reverse order before the ES failure branch: build OK; src 0x174 base 0x178 insns 93/94; --- replace mine 5:6 base 5:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the allocated TMD view through the final heap release: build OK; src 0x174 base 0x178 insns 93/94; --- replace mine 5:6 base 5:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - initialize content status on success and derive the valid result from lookup status: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the actual shared lookup/content status and initialize validity before lookup: build OK; src 0x178 base 0x178 insns 94/94; diffs 56: [6, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the shared status with the TMD output initialized before validity: build OK; src 0x178 base 0x178 insns 94/94; diffs 52: [6, 8, 9, 11, 12, 13, 23, 24, 25, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - assign the shared initialized status after declaring its output slot: build OK; src 0x178 base 0x178 insns 94/94; diffs 56: [6, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - hold EULA validation as the SDK BOOL status through lookup and cleanup: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - hold the validation flag as a normalized unsigned status: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the actual lookup heap before initializing the SDK validation status: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::setUSBAP()`: baseline 78.421050%, retained 98.070175%; 9 distinct successful attempts.
  - retain nickname success as const and test failure with explicit false: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - test the initial setup states through their equivalent signed range: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:8 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the typed owner nickname storage before fetching it: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive successful nickname blocks and retain normalized success as a BOOL: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive successful nickname blocks and explicitly normalize an integer result twice: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive successful nickname blocks with an unsigned normalized status: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - express USB access and completion as the two actual switch states with normalized result: build OK; src 0xe0 base 0xe4 insns 56/57; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - switch actual USB states using the original boolean nickname status: build OK; src 0xe0 base 0xe4 insns 56/57; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - make the actual idle USB state explicit before active switch states: build OK; src 0xe4 base 0xe4 insns 57/57; diffs 39: [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]; POOL IDENTICAL up to 108 (mine=108 base=108).

### src/scene/sdChannelMemory/iplSDMemory

- `ipl::scene::SDMemory::create(EGG::Heap*, ipl::nand::LayoutFile*, ipl::scene::SDChannelSelect*)`: baseline 95.456764%, retained 98.067670%; 12 distinct successful attempts.
  - derive the known textbox pane casts and restore the cache visibility branch order: build OK; src 0x1098 base 0x10a0 insns 1062/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - derive textbox casts and assign cache count from the successful slot index: build OK; src 0x10a0 base 0x10a0 insns 1064/1064; diffs 639: [5, 10, 17, 21, 27, 33, 34, 39, 40, 45, 46, 51, 57, 63, 69, 75, 81, 109, 116, 117]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - derive textbox casts and express cache capacity through the actual channel limit: build OK; src 0x1098 base 0x10a0 insns 1062/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - restore final transfer flag, original binding receiver and retained scroll animator: build OK; src 0x1094 base 0x10a0 insns 1061/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - restore creation blocks and declare the reusable textbox receiver before allocation: build OK; src 0x1094 base 0x10a0 insns 1061/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - restore creation blocks and retain the original cache reference as const: build OK; src 0x1094 base 0x10a0 insns 1061/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - inline known visible-pane operations and index the actual cache field from its manager: build OK; src 0x1088 base 0x10a0 insns 1058/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - bind cache manager by const reference with original creation blocks: build OK; src 0x1088 base 0x10a0 insns 1058/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - retain a const cache manager pointer and actual cache capacity with original creation blocks: build OK; src 0x1088 base 0x10a0 insns 1058/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - complete original creation blocks and resolve cached titles from their owning manager field: build OK; src 0x1090 base 0x10a0 insns 1060/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - complete original creation blocks with the savedata owner held by const reference: build OK; src 0x1090 base 0x10a0 insns 1060/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - complete original creation blocks using the named channel capacity for cache iteration: build OK; src 0x1090 base 0x10a0 insns 1060/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::onDialogState21()`: baseline 90.060974%, retained 90.060974%; 3 distinct successful attempts.
  - copy the actual message prefix with bounded wide-string copy and terminate its last element: build OK; src 0x144 base 0x148 insns 81/82; --- replace mine 5:8 base 5:8; POOL IDENTICAL up to 90 (mine=90 base=90).
  - copy the exact message-prefix character range with wide memory copy: build OK; src 0x144 base 0x148 insns 81/82; --- replace mine 5:8 base 5:8; POOL IDENTICAL up to 90 (mine=90 base=90).
  - copy the exact message prefix using its actual wide-character byte count: build OK; src 0x144 base 0x148 insns 81/82; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::drawTransferTitles()`: baseline 85.421290%, retained 85.421290%; 3 distinct successful attempts.
  - bind explicit top and bottom gradient colors from the actual title color: build OK; src 0x718 base 0x70c insns 454/451; --- replace mine 22:23 base 22:23; POOL IDENTICAL up to 90 (mine=90 base=90).
  - retain the floating row count and test the upper title clipping bound first: build OK; src 0x698 base 0x70c insns 422/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - advance title alpha iterators in the loop header and assign NAND row count explicitly: build OK; src 0x698 base 0x70c insns 422/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).

## Commits and changed files

- e8d31b46 restore scene creation and setup blocks
- `include/system/iplSaveDataManager.h`
- `src/scene/sdChannelMemory/iplSDMemory.cpp`
- `src/scene/setting/iplSetting.cpp`
- `tools/decomp-assist/sol-low-scenes-round6.md` records this round.

## Gate blocks

All captured round 6 gate blocks are copied verbatim below. Quick checks are identified by their filenames. The source commit followed a full GATE PASS. The final full block covers every unit exercised this round.

### sol-r6-baseline-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 98.0426 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 98.04257
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.29365
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 77.944595
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 81.77778
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 98.541664
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 98.0426
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30156/37884 data 1040/5696 functions 104/112 fuzzy 98.4958 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 103/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 98.49583
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 98.84386
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 93.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 92.42069
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 94.5625
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 81.21277
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 30156/37884 data 1040 functions 104 fuzzy 98.4958
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
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14484/20872 data 200 functions 63 fuzzy 97.6573
regressions vs baseline: 0
global matched_code_percent: 84.58613 -> 84.58613
global fuzzy_match_percent: 97.98290 -> 97.98290
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.32545 -> 90.32545
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r6-gate-derived-quick.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 98.0426 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 98.04257
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.29365
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 77.944595
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 81.77778
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 98.541664
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 98.0426
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30156/37884 data 1040/5696 functions 104/112 fuzzy 98.6649 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 103/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 98.66487
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 98.8505
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 93.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 92.42069
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 94.5625
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 86.30851
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 98.070175
[src/scene/setting/iplSetting] baseline: code 30156/37884 data 1040 functions 104 fuzzy 98.4958
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 98.1897 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 98.18973
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 98.06767
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14484/20872 data 200 functions 63 fuzzy 97.6573
regressions vs baseline: 0
global matched_code_percent: 84.58613 -> 84.58613
global fuzzy_match_percent: 97.98290 -> 97.98875
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.32545 -> 90.32545
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r6-gate-derived-full.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 98.0426 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 98.04257
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.29365
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 77.944595
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 81.77778
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 98.541664
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 98.0426
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30156/37884 data 1040/5696 functions 104/112 fuzzy 98.6649 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 103/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 98.66487
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 98.8505
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 93.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 92.42069
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 94.5625
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 86.30851
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 98.070175
[src/scene/setting/iplSetting] baseline: code 30156/37884 data 1040 functions 104 fuzzy 98.4958
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 98.1897 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 98.18973
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 98.06767
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14484/20872 data 200 functions 63 fuzzy 97.6573
regressions vs baseline: 0
global matched_code_percent: 84.58613 -> 84.58613
global fuzzy_match_percent: 97.98290 -> 97.98875
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.32545 -> 90.32545
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r6-gate-final.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 98.0426 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 98.04257
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.29365
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 77.944595
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 81.77778
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 98.541664
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 98.0426
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30156/37884 data 1040/5696 functions 104/112 fuzzy 98.6649 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 103/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 98.66487
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 98.8505
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 93.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 92.42069
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 94.5625
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 86.30851
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 98.070175
[src/scene/setting/iplSetting] baseline: code 30156/37884 data 1040 functions 104 fuzzy 98.4958
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 98.1897 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 98.18973
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 98.06767
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14484/20872 data 200 functions 63 fuzzy 97.6573
regressions vs baseline: 0
global matched_code_percent: 84.58613 -> 84.58613
global fuzzy_match_percent: 97.98290 -> 97.98875
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.32545 -> 90.32545
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r6-gate-log-final.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 24100/33828 data 224/2960 functions 102/129 fuzzy 98.0426 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 102/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 98.04257
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesByChannelOrder__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 97.29365
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: collectTitlesBySpecialChannels__Q33ipl5scene15SDChannelSelectFPClPClPUxPcPUl 77.944595
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: findAdjacentChannel__Q33ipl5scene15SDChannelSelectCFiPiPi 81.77778
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: flushSaveDataAndMountSD__Q33ipl5scene15SDChannelSelectFv 99.65714
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: calcCommon__Q33ipl5scene15SDChannelSelectFv 99.07407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: destroy__Q33ipl5scene15SDChannelSelectFv 95.097565
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: drawChannelTransitionObjects__Q33ipl5scene15SDChannelSelectFv 94.974846
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: initializeNormalPage__Q33ipl5scene15SDChannelSelectFv 98.93617
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: selectChannel__Q33ipl5scene15SDChannelSelectFii 98.305084
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: setChannelScissor__Q33ipl5scene15SDChannelSelectCFPCQ33ipl5scene12SDChannelObj 93.48498
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 98.541664
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 98.0426
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30156/37884 data 1040/5696 functions 104/112 fuzzy 98.6649 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 103/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 98.66487
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 98.8505
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 93.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 92.42069
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 94.5625
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 86.30851
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 98.070175
[src/scene/setting/iplSetting] baseline: code 30156/37884 data 1040 functions 104 fuzzy 98.4958
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14484/20872 data 200/3344 functions 63/66 fuzzy 98.1897 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 62/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match None
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 98.18973
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 98.06767
[src/scene/sdChannelMemory/iplSDMemory]   below 100: onDialogState21__Q33ipl5scene8SDMemoryFv 90.060974
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 85.42129
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14484/20872 data 200 functions 63 fuzzy 97.6573
regressions vs baseline: 0
global matched_code_percent: 84.58613 -> 84.58613
global fuzzy_match_percent: 97.98290 -> 97.98875
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.32545 -> 90.32545
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

