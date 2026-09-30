# Scenes round 5 attempts

Baseline: merged main `6a2a3dd6`. All original functions are present. This round used only the worker checkout and /tmp. Matching configuration was unchanged.

Coverage: all 27 initially open Select functions, ten initially open Setting functions and three initially open Memory functions received at least three distinct successful source builds this round. Earlier-round attempts are excluded. Failed builds are recorded separately. Folded source variations are experiments without any claim that they improved output.

## Measurements

- `src/scene/sdChannelSelect/iplSDChannelSelect`: instruction-exact 102 -> 102; objdiff exact 102 -> 102; matched code 24100 -> 24100/33828; matched data 224 -> 224/2960; fuzzy 97.385250% -> 98.042570%.
- `src/scene/setting/iplSetting`: instruction-exact 101 -> 103; objdiff exact 102 -> 104; matched code 25220 -> 30156/37884; matched data 1040 -> 1040/5696; fuzzy 92.950800% -> 98.495830%.
- `src/scene/sdChannelMemory/iplSDMemory`: instruction-exact 62 -> 62; objdiff exact 63 -> 63; matched code 14484 -> 14484/20872; matched data 200 -> 200/3344; fuzzy 97.657340% -> 97.657340%.

Function experiments: 142 successful builds and 9 failed builds.

## Retained changes

- Setting makeSupportCode reuses the segment length through title, label and support-code construction. The final object has 76/76 instructions, diffs 0, +304 matched code bytes.
- Setting calcNormal was reconstructed block by block from the original assembly. It restores network setup, confirmation dialogs, nickname and parental operations, forced-exit transitions, message initialization, fadeout and the keyboard IME report argument. Unsigned ranges and truncated parental results follow the original. The final object has 1158/1158 instructions, diffs 0, +4632 matched code bytes.
- Setting initKeyboard and calcKeyboard restore supported form dispatch, actual setting member order, row/string limits, keypad/compact/secret modes, title clearing, SSID storage, validation and MTU completion blocks. The private MessageManager call and keyboard declarations are guarded by IPL_SETTING_IMPLEMENTATION, which only Setting.cpp defines. Default locals remain initialized. These are partial improvements at 212/213 and 289/290 instructions.
- Select collectTitlesByChannelOrder restores the loaded-banner title/fallback block and reads the matched usage record and ordered title-name slot. It now has 126/126 instructions, with allocation and reload differences remaining.
- Select collectTitlesBySpecialChannels restores the bounded cached-title lookup and matching usage record reloads. The owner-only SaveDataManager accessor uses the actual titleCache field, guarded by IPL_SD_CHANNEL_SELECT_CPP, defined only by Select.cpp. Failed-lookup coordinates remain initialized. The body has 350/361 instructions.
- Select findAdjacentChannel uses the original common wrapped-search loop and shared found return. It now has 45/45 instructions, with register differences remaining.
- Select button-handler onEventDerived forwards states 15, 16, 22 and 23, and combines the left-arrow pane and page guards. States 17 through 21 follow the original local handler flow. It now has 144/144 instructions.
- Setting createBrowser uses the original 4:3 surface dimensions, product-area dispatch and caller-supplied page index. scanAP initializes the pane manager at states 4 and 9 and restores separate scroll-animation branches. validateEULA_ places the ES error path before success, following the original block order. These remain partial matches.
- Continuation check: the pending special-channel trial failed the quick gate because its new accessor was nested inside the Memory-only guard. The guard was corrected, and all three cache variants were rebuilt successfully. The pending render-mode member-copy trial was restored after it remained non-exact. Neither failed build nor restored experiment is claimed as progress.

## Data and function-order audit

- Pools are identical for all three units. All original functions exist; no owned assembly bodies remain. Existing original function definition order and literal/pointer-table order were retained.
- No tables, vtable slots or data bytes were invented. Select .rodata/.sdata/.sdata2 and Memory .sdata/.sdata2 retain 100% objdiff section scores. Setting .bss/.sbss/.sdata/.sdata2 retain 100% scores. Short trailing source sections are normal compiler alignment differences, not missing objects to pad.
- Select .data remains 2736 bytes at 35.06984%; Setting .data remains 4016 bytes at 5.146636%; Memory .data remains 3144 bytes. Actual scene/handler vtables and named tables retain their established original source order. The extracted original objects contain zero-filled deduplicated weak data where ordinary source vtables contain relocations. This round did not replace those real tables with synthetic zeros.
- Setting .rodata remains 600 versus 640 target bytes, at 32.25412%. Both original 20-byte scNumber/scNumber2 digit maps have no relocation references in the original unit. Their source callers are still unknown; unused filler tables or forced emission were not introduced.
- Three compiler-emitted Memory iterator helpers retain the existing emission-order difference; explicit scene/helper definitions remain in original order. No fake references were added to move weak symbols.
- Raw instruction decoding undercounts objdiff-exact Setting::calcFadeout and Memory::updateState around CR1 varargs. Both counts are reported; the decoder was not changed.

Fresh ELF audit:

```text
src/scene/sdChannelSelect/iplSDChannelSelect: missing original functions []
  .rodata original/source size 64/64
  .data original/source size 2736/2736
  .sdata2 original/source size 80/80
  .sdata original/source size 80/79
src/scene/setting/iplSetting: missing original functions []
  .bss original/source size 456/456
  .rodata original/source size 640/600
  .data original/source size 4016/4016
  .sdata2 original/source size 64/60
  .sdata original/source size 504/500
  .sbss original/source size 16/12
  scNumber/scNumber2 relocation references []
src/scene/sdChannelMemory/iplSDMemory: missing original functions []
  .data original/source size 3144/3144
  .sdata2 original/source size 48/48
  .sdata original/source size 152/152
src/scene/sdChannelSelect/iplSDChannelSelect: original strong-function relative order identical True
src/scene/setting/iplSetting: original strong-function relative order identical True
  __vt__Q33ipl5scene7APEvent original/source 0xe9c/0xe9c
  __vt__Q33ipl5scene7Setting original/source 0xeb4/0xeb4
src/scene/sdChannelMemory/iplSDMemory: original strong-function relative order identical True
```

## Remaining functions


### src/scene/sdChannelSelect/iplSDChannelSelect

- `ipl::scene::SDChannelSelect::flushSaveDataAndMountSD()` 99.657140%: heap and NAND manager loads have reversed operand scheduling. src 0x8c base 0x8c insns 35/35.
- `ipl::scene::SDChannelSelect::handleSDTitleListResult()` 99.152050%: the short initial-result branch uses a different branch sequence plus register choices. src 0x2a8 base 0x2ac insns 170/171.
- `ipl::scene::SDChannelSelect::calcCommon()` 99.074070%: the button call emits an extra unused-parameter load. src 0x1b4 base 0x1b0 insns 109/108.
- `ipl::scene::SDChannelSelect::initializeNormalPage()` 98.936170%: the button call emits an extra unused-parameter load. src 0x17c base 0x178 insns 95/94.
- `ipl::scene::@unnamed@iplSDChannelSelect_cpp@::SDChannelSelectButtonEventHandler::onEventDerived(unsigned long, unsigned long, const ipl::controller::Interface*)` 98.541664%: 144/144 corrected forwarding instructions retain receiver/register allocation and an initialized unused button argument. src 0x240 base 0x240 insns 144/144.
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
- `ipl::scene::SDChannelSelect::findAdjacentChannel(int, int*, int*) const` 81.777780%: 45/45 common-loop instructions still allocate page, slot and return values to different registers. src 0xb4 base 0xb4 insns 45/45.
- `ipl::scene::SDChannelSelect::collectTitlesBySpecialChannels(const long*, const long*, unsigned long long*, char*, unsigned long*)` 77.944595%: priority lookup sentinels, initialized output coordinates, cache bounds and register lifetimes differ; the restored body has 350/361 instructions. src 0x578 base 0x5a4 insns 350/361.

### src/scene/setting/iplSetting

- `ipl::scene::Setting::createBrowser()` 98.843860%: rectangle conversion, stack placement and signed product-area dispatch differ; restored body has 299/301 instructions. src 0x4ac base 0x4b4 insns 299/301.
- `ipl::scene::Setting::convertRevIP(unsigned char*, const char*)` 98.150690%: parser counters and output cursor use different callee-saved registers. src 0x124 base 0x124 insns 73/73.
- `ipl::scene::Setting::scanAP()` 94.562500%: pane initialization is restored; animation-result normalization, dispatch and reload scheduling leave 266/272 instructions. src 0x428 base 0x440 insns 266/272.
- `ipl::scene::Setting::initKeyboard(const char*)` 93.309860%: supported form blocks are restored; initialized default limits, form dispatch and allocation leave 212/213 instructions. src 0x350 base 0x354 insns 212/213.
- `ipl::scene::Setting::calcKeyboard()` 92.420690%: form completion is restored; initialized default form text, dispatch and member reloads leave 289/290 instructions. src 0x484 base 0x488 insns 289/290.
- `ipl::scene::Setting::draw()` 91.036390%: original rendering blocks are present; render-mode copy is shorter than original field copies, with stack/float scheduling differences. Three additional typed sample/filter copy trials reached 635/632, 631/632 and 634/632 and were restored. src 0x958 base 0x9e0 insns 598/632.
- `ipl::scene::Setting::validateEULA_()` 81.212770%: restored error-before-success blocks leave result initialization, success branch and argument-base scheduling differences at 93/94 instructions. src 0x174 base 0x178 insns 93/94.
- `ipl::scene::Setting::setUSBAP()` 78.421050%: success/failure block ordering and state-dispatch branches differ. src 0xdc base 0xe4 insns 55/57.

### src/scene/sdChannelMemory/iplSDMemory

- `ipl::scene::SDMemory::create(EGG::Heap*, ipl::nand::LayoutFile*, ipl::scene::SDChannelSelect*)` 95.456764%: cached-title visibility, animator reloads and pane setup differ. src 0x10d8 base 0x10a0 insns 1078/1064.
- `ipl::scene::SDMemory::onDialogState21()` 90.060974%: format copy/initialization and pointer-length arithmetic differ. Real wcsncpy, wcscpy and memset prefix trials did not match. src 0x13c base 0x148 insns 79/82.
- `ipl::scene::SDMemory::drawTransferTitles()` 85.421290%: color conversion, clipping, stack and register lifetimes differ. Typed color/gradient source trials did not match. src 0x698 base 0x70c insns 422/451.

## New function attempt evidence

Each item records a distinct source transformation and its object build, instruction diff and pool result. Failed builds do not count toward coverage. Restored trials are not committed changes. Initialized unused payloads, button arguments, unsupported keyboard limits and failed-lookup coordinates were preserved.


### src/scene/sdChannelSelect/iplSDChannelSelect

- `ipl::scene::SDChannelSelect::flushSaveDataAndMountSD()`: baseline 99.657140%, retained 99.657140%; 3 distinct successful attempts.
  - bind the actual heap as a const pointer reference for the flush: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bundle heap and manager in a typed flush context, heap first: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - bundle manager and heap in a typed flush context, manager first: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::handleSDTitleListResult()`: baseline 99.152050%, retained 99.152050%; 3 distinct successful attempts.
  - accept location results through a switch with two shared cases: build FAILED; #   Error:               ^^^^; #   (10141) expression syntax error.
  - use one counter for each fallback channel slot: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - name each fallback record before testing its title flags: build FAILED; #   Error:                                         ^^^^^^^^^^^; #   (10140) undefined identifier 'ipl::NandSDWorker::SDTitleInfo'.
  - dispatch accepted location results and fallback through correctly scoped switch blocks: build OK; src 0x2b0 base 0x2ac insns 172/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve each fallback title through its declared const record reference: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::calcCommon()`: baseline 99.074070%, retained 99.074070%; 3 distinct successful attempts.
  - resolve the button and handler in a nested receiver scope: build OK; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the actual SDButton call through a named member-function pointer: build OK; src 0x1d8 base 0x1b0 insns 118/108; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - forward the receiver and active handler through an inline typed helper: build OK; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::initializeNormalPage()`: baseline 98.936170%, retained 98.936170%; 3 distinct successful attempts.
  - resolve the button and handler in a nested receiver scope: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the actual SDButton call through a named member-function pointer: build OK; src 0x1a0 base 0x178 insns 104/94; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - forward the receiver and active handler through an inline typed helper: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::selectChannel(int, int)`: baseline 98.305084%, retained 98.305084%; 3 distinct successful attempts.
  - resolve the button and handler in a nested receiver scope: build OK; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain the actual SDButton call through a named member-function pointer: build OK; src 0x114 base 0xec insns 69/59; --- delete mine 39:41 base 39:39; POOL IDENTICAL up to 101 (mine=101 base=101).
  - forward the receiver and active handler through an inline typed helper: build OK; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesFromNandUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 97.833336%, retained 97.833336%; 3 distinct successful attempts.
  - invert the successful accumulated usage branch before continuing the scan: build OK; src 0x198 base 0x198 insns 102/102; diffs 4: [69, 70, 71, 72]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - advance the count through its typed lvalue reference before testing the usage pair: build OK; src 0x198 base 0x198 insns 102/102; diffs 4: [69, 70, 71, 72]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - combine the complete final usage result with the reconstructed inner guard: build OK; src 0x194 base 0x198 insns 101/102; --- insert mine 69:69 base 69:72; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesByUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 97.811880%, retained 97.811880%; 3 distinct successful attempts.
  - invert the successful accumulated usage branch before continuing the scan: build OK; src 0x194 base 0x194 insns 101/101; diffs 4: [67, 68, 69, 70]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - advance the count through its typed lvalue reference before testing the usage pair: build OK; src 0x194 base 0x194 insns 101/101; diffs 4: [67, 68, 69, 70]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - combine the complete final usage result with the reconstructed inner guard: build OK; src 0x190 base 0x194 insns 100/101; --- insert mine 67:67 base 67:70; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueNotice(unsigned long, unsigned long, unsigned long)`: baseline 97.511110%, retained 97.511110%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0xd8 base 0xb4 insns 54/45; --- delete mine 4:5 base 4:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0xb8 base 0xb4 insns 46/45; --- replace mine 10:11 base 10:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0xb8 base 0xb4 insns 46/45; --- replace mine 10:11 base 10:12; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::@unnamed@iplSDChannelSelect_cpp@::SDChannelSelectButtonEventHandler::onEventDerived(unsigned long, unsigned long, const ipl::controller::Interface*)`: baseline 95.680560%, retained 98.541664%; 3 distinct successful attempts.
  - correct state forwarding and combine the left arrow name/page guards: build OK; src 0x240 base 0x240 insns 144/144; diffs 57: [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - correct forwarding and resolve the GUI pane as a typed named object: build OK; src 0x240 base 0x240 insns 144/144; diffs 57: [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - correct forwarding and reuse the queried scene state in the input guard: build OK; src 0x240 base 0x240 insns 144/144; diffs 57: [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueLoadNotice()`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0x6c base 0x5c insns 27/23; --- replace mine 7:19 base 7:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueuePageNotice()`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0x6c base 0x5c insns 27/23; --- replace mine 7:19 base 7:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueResultNotice(unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0x78 base 0x5c insns 30/23; --- replace mine 7:19 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueMoveNotice(unsigned long, unsigned long, unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0x74 base 0x5c insns 29/23; --- replace mine 7:20 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueErrorNotice(unsigned long, unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0x74 base 0x5c insns 29/23; --- replace mine 7:19 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:10 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueStateNotice(unsigned long, unsigned long, unsigned long, unsigned long)`: baseline 95.130430%, retained 95.130430%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0x78 base 0x5c insns 30/23; --- replace mine 7:20 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:8 base 7:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0x60 base 0x5c insns 24/23; --- replace mine 7:11 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::destroy()`: baseline 95.097565%, retained 95.097565%; 3 distinct successful attempts.
  - retain the save-file reference through its polling and deletion: build OK; src 0x32c base 0x334 insns 203/205; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - read the channel list before the restart and save-page operations: build OK; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - poll asynchronous save and worker completion using explicit break loops: build OK; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::drawChannelTransitionObjects()`: baseline 94.974846%, retained 94.974846%; 3 distinct successful attempts.
  - bind each existing translation vector as a const reference: build OK; src 0x21c base 0x27c insns 135/159; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - test lower state limits before upper transition limits: build OK; src 0x264 base 0x27c insns 153/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve channel index before channel page for object visibility: build OK; src 0x264 base 0x27c insns 153/159; --- replace mine 6:9 base 6:8; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueFinishNotice()`: baseline 94.444440%, retained 94.444440%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0x58 base 0x48 insns 22/18; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0x4c base 0x48 insns 19/18; --- delete mine 12:13 base 12:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0x4c base 0x48 insns 19/18; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::create()`: baseline 94.239720%, retained 94.239720%; 3 distinct successful attempts.
  - retain the mem2 application heap through worker allocations: build OK; src 0x248 base 0x248 insns 146/146; diffs 101: [9, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - form the complete thumbnail work allocation using two named size components: build OK; src 0x248 base 0x248 insns 146/146; diffs 81: [32, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve elapsed ticks in the report call with a named starting timestamp: build OK; src 0x248 base 0x248 insns 146/146; diffs 84: [30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueStartNotice()`: baseline 94.117645%, retained 94.117645%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0x54 base 0x44 insns 21/17; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0x48 base 0x44 insns 18/17; --- delete mine 12:13 base 12:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0x48 base 0x44 insns 18/17; --- replace mine 2:3 base 2:3; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::setChannelScissor(const ipl::scene::SDChannelObj*) const`: baseline 93.484980%, retained 93.484980%; 3 distinct successful attempts.
  - retain framebuffer extents before selecting transformed or normal clipping: build OK; src 0x398 base 0x3a4 insns 230/233; --- replace mine 12:13 base 12:13; POOL IDENTICAL up to 101 (mine=101 base=101).
  - form normalized screen half extents before transformed coordinates: build OK; src 0x3a4 base 0x3a4 insns 233/233; diffs 69: [38, 39, 40, 41, 43, 44, 46, 49, 50, 52, 53, 54, 68, 69, 70, 71, 73, 74, 75, 76]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clip the right and bottom edges through named coordinate sums: build OK; src 0x3a4 base 0x3a4 insns 233/233; diffs 67: [38, 39, 40, 41, 43, 44, 46, 49, 50, 52, 53, 54, 68, 69, 70, 71, 72, 74, 75, 76]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::isCurrentTitleUsageEnough(const long*) const`: baseline 93.078430%, retained 93.078430%; 3 distinct successful attempts.
  - load the required usage limits immediately before testing capacity: build OK; src 0xc8 base 0xcc insns 50/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - search NAND usage with a typed advancing record pointer: build OK; src 0xb4 base 0xcc insns 45/51; --- insert mine 5:5 base 5:7; POOL IDENTICAL up to 101 (mine=101 base=101).
  - test capacity in terms of independent signed usage deficits: build OK; src 0xc8 base 0xcc insns 50/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueChannelNotice(unsigned long, unsigned long, unsigned long, unsigned long)`: baseline 90.869570%, retained 90.869570%; 3 distinct successful attempts.
  - construct the full initialized command with an aggregate initializer: build OK; src 0x80 base 0x5c insns 32/23; --- replace mine 7:19 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - write payload words through a typed array cursor: build OK; src 0x64 base 0x5c insns 25/23; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize payload words in descending array order: build OK; src 0x64 base 0x5c insns 25/23; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::getCurrentTitleUsage(long*, long*) const`: baseline 86.823530%, retained 86.823530%; 3 distinct successful attempts.
  - retain the initial byte and block usage until each individual output store: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain a const matching usage record for the two output additions: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - search usage by comparing the current title identifier before record identifier: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesByChannelOrder(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 86.555560%, retained 97.293650%; 3 distinct successful attempts.
  - derive channel blocks and keep the traversal order cursor unsigned: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 22: [19, 23, 27, 28, 29, 33, 34, 36, 37, 38, 41, 42, 51, 52, 56, 85, 86, 87, 88, 102]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive channel blocks and load block usage before byte usage: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 28: [19, 23, 27, 28, 29, 33, 34, 36, 37, 38, 41, 42, 51, 52, 55, 56, 57, 59, 62, 65]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive channel blocks and initialize the output count before reading initial usage: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 38: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 23, 27, 28]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesBySpecialChannels(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 71.639890%, retained 77.944595%; 6 distinct successful attempts.
  - derive priority title blocks with unsigned low title identifier comparisons: build OK; src 0x554 base 0x5a4 insns 341/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive priority blocks and keep the cache scan count in unsigned descending form: build OK; src 0x558 base 0x5a4 insns 342/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive priority blocks and finish through a single combined usage predicate: build OK; src 0x550 base 0x5a4 insns 340/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive the bounded cached-title lookup and retain matching usage-record identifiers: build FAILED; #   Error:                                                            ^^^^^^^^^^^^^^; #   (10140) undefined identifier 'getCachedTitle'.
  - capture each priority-channel lookup into initialized page/index temporaries: build FAILED; #   Error:                                                            ^^^^^^^^^^^^^^; #   (10140) undefined identifier 'getCachedTitle'.
  - retain bounded cache lookup and declare page/index before priority usage indices: build FAILED; #   Error:                                                            ^^^^^^^^^^^^^^; #   (10140) undefined identifier 'getCachedTitle'.
  - derive the bounded cached-title lookup and retain matching usage-record identifiers: build OK; src 0x578 base 0x5a4 insns 350/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - capture each priority-channel lookup into initialized page/index temporaries: build OK; src 0x5c4 base 0x5a4 insns 369/361; --- insert mine 13:13 base 13:16; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain bounded cache lookup and declare page/index before priority usage indices: build OK; src 0x57c base 0x5a4 insns 351/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::findAdjacentChannel(int, int*, int*) const`: baseline 48.044445%, retained 81.777780%; 6 distinct successful attempts.
  - derive one wrapped search loop and initialize the step before direction comparison: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 14: [0, 2, 3, 4, 6, 7, 9, 11, 13, 16, 17, 20, 22, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive one search loop and store quotient before choosing the found return: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 12: [0, 2, 3, 4, 6, 7, 11, 13, 16, 17, 20, 22]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive the common return with a named page size for quotient and remainder: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 12: [0, 2, 3, 4, 6, 7, 11, 13, 16, 17, 20, 22]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - read search bounds before current page and wrapped slot: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 13: [0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize the next slot before calculating search bounds: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 18: [0, 2, 3, 4, 6, 7, 11, 13, 14, 16, 17, 19, 20, 22, 27, 29, 33, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - declare the page, limit and current-slot lifetimes together before assigning them: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 9: [0, 2, 3, 4, 6, 13, 16, 17, 22]; POOL IDENTICAL up to 101 (mine=101 base=101).

### src/scene/setting/iplSetting

- `ipl::scene::Setting::makeSupportCode()`: baseline 99.078950%, retained 100.000000%; 3 distinct successful attempts.
  - reuse the label length local for the numeric support-code segment: build OK; src 0x130 base 0x130 insns 76/76; diffs 8: [38, 40, 46, 49, 51, 56, 61, 63]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - use one source segment length through all three append operations: build OK; src 0x130 base 0x130 insns 76/76; diffs 0: []; POOL IDENTICAL up to 108 (mine=108 base=108).
  - reuse label and numeric segment counts and advance a typed message cursor: build OK; src 0x130 base 0x130 insns 76/76; diffs 8: [38, 40, 46, 49, 51, 56, 61, 63]; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::convertRevIP(unsigned char*, const char*)`: baseline 98.150690%, retained 98.150690%; 3 distinct successful attempts.
  - write each capped decimal component through an indexed output base: build OK; src 0x124 base 0x124 insns 73/73; diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - declare the parsed decimal before scanning the current component: build OK; src 0x124 base 0x124 insns 73/73; diffs 21: [6, 8, 12, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45, 46, 47, 48, 50, 64]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - scan each character through an explicit named separator predicate: build OK; src 0x134 base 0x124 insns 77/73; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::createBrowser()`: baseline 93.687706%, retained 98.843860%; 3 distinct successful attempts.
  - derive browser dimensions and region dispatch with a const signed region code: build OK; src 0x4ac base 0x4b4 insns 299/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive browser dimensions and retain named wide and standard heights: build OK; src 0x4ac base 0x4b4 insns 299/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive dimensions and scan the direct page names using a for loop with an explicit match test: build OK; src 0x4ac base 0x4b4 insns 299/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::draw()`: baseline 91.036390%, retained 91.036390%; 6 distinct successful attempts.
  - copy the actual render-mode scalar and array members before applying AP clipping: build OK; src 0xb10 base 0x9e0 insns 708/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - copy render-mode members through a const typed mode pointer: build OK; src 0xb10 base 0x9e0 insns 708/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - copy render-mode members with framebuffer width resolved before video mode: build OK; src 0xb08 base 0x9e0 insns 706/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - copy sample pairs in a counted loop and the seven filter bytes in member order: build OK; src 0x9ec base 0x9e0 insns 635/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
  - copy both sample pairs and filter bytes using counted loops: build OK; src 0x9dc base 0x9e0 insns 631/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
  - advance typed sample-pair pointers while retaining the filter member order: build OK; src 0x9e8 base 0x9e0 insns 634/632; --- replace mine 18:19 base 18:19; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::scanAP()`: baseline 88.106620%, retained 94.562500%; 3 distinct successful attempts.
  - derive pane initialization and scroll branches with signed scanning state dispatch: build OK; src 0x428 base 0x440 insns 266/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain the current animation in its own switch-case scope: build OK; src 0x428 base 0x440 insns 266/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - express normalized animation completion through an explicit boolean conditional: build OK; src 0x428 base 0x440 insns 266/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::setUSBAP()`: baseline 78.421050%, retained 78.421050%; 3 distinct successful attempts.
  - derive nickname success first and compare the setup state with explicit signed constants: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive nickname success first and promote the fetched nickname status as a BOOL: build OK; src 0xdc base 0xe4 insns 55/57; --- replace mine 7:9 base 7:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive nickname success first with a typed nickname reference: build FAILED; #   Error:                                                                 ^; #   (10248) function call '[ipl::scene::USBAPThread].setData({lval} unsigned.
  - retain a typed nickname reference and pass its actual string member to the USB worker: build OK; src 0xe8 base 0xe4 insns 58/57; --- replace mine 4:6 base 4:5; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::calcKeyboard()`: baseline 75.624140%, retained 92.420690%; 6 distinct successful attempts.
  - derive hidden-after-disappear and appearing states plus form 22 emission and vacancy direction: build OK; src 0x4bc base 0x488 insns 303/290; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 108 (mine=108 base=108).
  - scope each selected form buffer inside its OK or cancel branch: build OK; src 0x4bc base 0x488 insns 303/290; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive keyboard states and mask security input through a counted for loop: build OK; src 0x4b8 base 0x488 insns 302/290; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 108 (mine=108 base=108).
  - correct manager title clearing and remaining typed form control flow: build OK; src 0x484 base 0x488 insns 289/290; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 108 (mine=108 base=108).
  - resolve each manager or input index at its original block boundary: build OK; src 0x480 base 0x488 insns 288/290; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 108 (mine=108 base=108).
  - order settings or input cursor lifetime according to original dataflow: build OK; src 0x480 base 0x488 insns 288/290; --- replace mine 11:12 base 11:12; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::calcNormal()`: baseline 67.917960%, retained 100.000000%; 7 distinct successful attempts.
  - rederive missing parental, region, pointer, sensor and language blocks and reorder both switches: build FAILED; #   Error:                                                          ^; #   (10381) illegal access from 'ipl::message::Manager' to protected/private.
  - retain completed blocks and read reset counters before storing dialog state: build FAILED; #   Error:                                                          ^; #   (10381) illegal access from 'ipl::message::Manager' to protected/private.
  - retain completed blocks and scope the disabled home-button dialog check: build FAILED; #   Error:                                                          ^; #   (10381) illegal access from 'ipl::message::Manager' to protected/private.
  - rederive missing parental, region, pointer, sensor and language blocks and reorder both switches: build OK; src 0x11f8 base 0x1218 insns 1150/1158; --- replace mine 36:37 base 36:37; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain completed blocks and read reset counters before storing dialog state: build OK; src 0x11f8 base 0x1218 insns 1150/1158; --- replace mine 36:37 base 36:37; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain completed blocks and scope the disabled home-button dialog check: build OK; src 0x11f8 base 0x1218 insns 1150/1158; --- replace mine 36:37 base 36:37; POOL IDENTICAL up to 108 (mine=108 base=108).
  - complete scene-exit fade and restore unsigned region, message and parental result types: build OK; src 0x1218 base 0x1218 insns 1158/1158; diffs 3: [125, 126, 813]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - retain IME text through its check and commit branches: build OK; src 0x1214 base 0x1218 insns 1157/1158; --- replace mine 10:11 base 10:11; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name the actual IME object before its event-kind dispatch: build OK; src 0x1214 base 0x1218 insns 1157/1158; --- replace mine 10:11 base 10:11; POOL IDENTICAL up to 108 (mine=108 base=108).
  - pass the original IME string to its report and compare the loaded aspect byte as unsigned: build OK; src 0x1218 base 0x1218 insns 1158/1158; diffs 0: []; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::initKeyboard(const char*)`: baseline 67.309860%, retained 93.309860%; 6 distinct successful attempts.
  - derive real keyboard modes, form dispatch, setting layout, blank string and secret input setup: build OK; src 0x368 base 0x354 insns 218/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive keyboard blocks and assign the settings in physical member order: build OK; src 0x368 base 0x354 insns 218/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive keyboard blocks and resolve system dictionary before the user dictionary: build OK; src 0x368 base 0x354 insns 218/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - correct manager title clearing and remaining typed form control flow: build OK; src 0x350 base 0x354 insns 212/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - resolve each manager or input index at its original block boundary: build OK; src 0x35c base 0x354 insns 215/213; --- delete mine 17:18 base 17:17; POOL IDENTICAL up to 108 (mine=108 base=108).
  - order settings or input cursor lifetime according to original dataflow: build OK; src 0x35c base 0x354 insns 215/213; --- delete mine 17:18 base 17:17; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::validateEULA_()`: baseline 64.414894%, retained 81.212770%; 3 distinct successful attempts.
  - derive error before success and cache the actual view-allocation heap: build OK; src 0x174 base 0x178 insns 93/94; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive error-first dispatch and name whether the expected content exists: build OK; src 0x178 base 0x178 insns 94/94; diffs 52: [5, 6, 7, 8, 9, 11, 16, 17, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive error-first dispatch and initialize content status in the successful lookup scope: build OK; src 0x174 base 0x178 insns 93/94; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).

### src/scene/sdChannelMemory/iplSDMemory

- `ipl::scene::SDMemory::create(EGG::Heap*, ipl::nand::LayoutFile*, ipl::scene::SDChannelSelect*)`: baseline 95.456764%, retained 95.456764%; 3 distinct successful attempts.
  - retain target cache branch order and bind the cached-title array as a const reference: build OK; src 0x10d8 base 0x10a0 insns 1078/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - retain target cache branch order and scan cache through a pointer/count loop: build OK; src 0x10d0 base 0x10a0 insns 1076/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - retain target cache branch order and initialize dialog scroll animations through a named layout: build OK; src 0x10d0 base 0x10a0 insns 1076/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::onDialogState21()`: baseline 90.060974%, retained 90.060974%; 6 distinct successful attempts.
  - initialize the wide prefix and calculate ceil blocks using quotient times block size: build OK; src 0x138 base 0x148 insns 78/82; --- replace mine 28:29 base 28:29; POOL IDENTICAL up to 90 (mine=90 base=90).
  - initialize the wide prefix and compute block rounding through a named remainder: build OK; src 0x140 base 0x148 insns 80/82; --- insert mine 28:28 base 28:30; POOL IDENTICAL up to 90 (mine=90 base=90).
  - initialize the wide prefix and test the source message before its marker: build OK; src 0x140 base 0x148 insns 80/82; --- insert mine 26:26 base 26:29; POOL IDENTICAL up to 90 (mine=90 base=90).
  - terminate the fresh wide prefix through a one-character bounded string copy: build OK; src 0x140 base 0x148 insns 80/82; --- insert mine 28:28 base 28:30; POOL IDENTICAL up to 90 (mine=90 base=90).
  - terminate the fresh wide prefix with the ordinary wide-string copy operation: build OK; src 0x13c base 0x148 insns 79/82; --- replace mine 28:29 base 28:29; POOL IDENTICAL up to 90 (mine=90 base=90).
  - clear the first wide prefix character using its actual element size: build OK; src 0x140 base 0x148 insns 80/82; --- insert mine 28:28 base 28:30; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::drawTransferTitles()`: baseline 85.421290%, retained 85.421290%; 3 distinct successful attempts.
  - construct the title gradient colors from their RGBA values: build OK; src 0x674 base 0x70c insns 413/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - calculate title height using the text rectangle height accessor: build OK; src 0x698 base 0x70c insns 422/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - promote row clipping coordinates to the existing full pane translation: build OK; src 0x6a4 base 0x70c insns 425/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).

## Commits and changed files

- 54aad9fa record scene matching attempts and full gates
- 1a43e31e match setting support code segment lengths
- ba2b7b85 complete setting normal state and message control flow
- cd30ad61 match setting normal calculation and restore keyboard behavior
- bb289d86 restore channel search and setting browser control flow
- `include/system/iplKeyboard.h`
- `include/system/iplMessageManager.h`
- `include/system/iplSaveDataManager.h`
- `src/scene/sdChannelSelect/iplSDChannelSelect.cpp`
- `src/scene/setting/iplSetting.cpp`
- `tools/decomp-assist/sol-low-scenes-round5.md` records this round.

## Gate blocks

All captured gate outputs are copied verbatim below. Quick checks are identified by their filenames. The failed continuation check is retained as failure evidence. Every source commit followed a full GATE PASS. The final full block covers all three touched units.

### sol-r5-baseline-gate.txt

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 97.3852
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
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 92.9508
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
global matched_code_percent: 83.95137 -> 83.95137
global fuzzy_match_percent: 97.66636 -> 97.66636
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r5-gate-support.txt

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 97.3852
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25524/37884 data 1040/5696 functions 103/112 fuzzy 92.9582 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 102/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 92.95819
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 92.9508
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
global matched_code_percent: 83.95137 -> 83.96152
global fuzzy_match_percent: 97.66636 -> 97.66647
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r5-gate-normal.txt

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 97.3852
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 25524/37884 data 1040/5696 functions 103/112 fuzzy 96.7066 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 102/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 96.70658
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 98.57513
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 92.9508
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
global matched_code_percent: 83.95137 -> 83.96152
global fuzzy_match_percent: 97.66636 -> 97.71386
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r5-gate-keyboard-normal.txt

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 97.3852
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30156/37884 data 1040/5696 functions 104/112 fuzzy 97.9798 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 103/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 97.979836
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 91.03639
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 93.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 92.42069
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 92.9508
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
global matched_code_percent: 83.95137 -> 84.11617
global fuzzy_match_percent: 97.66636 -> 97.72997
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r5-resume-gate.txt

```text
full build: FAILED
ive2\projects\wii-ipl-workers\sol-low\include\iplSceneUI.h:11
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\src\scene\channelSelect\iplChannelSelect.cpp:2)
[120/126] MWCC build/43U/src/src/scene/sdChannelMemory/iplSDMemory.o
### mwcceppc.exe Compiler:
#      In: include\utility\iplTree.h
#    From: src\scene\sdChannelMemory\iplSDMemory.cpp
# --------------------------------------------------
#      40:                 } 
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\iplFaderSceneBase.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\iplSceneUIHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\board\iplBoardObject.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\board\iplFocusObject.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\sdChannelMemory\iplSDMemory.h:8
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\src\scene\sdChannelMemory\iplSDMemory.cpp:14)
[121/126] MWCC build/43U/src/src/scene/channelTitle/iplChannelTitle.o
### mwcceppc.exe Compiler:
#      In: include\utility\iplTree.h
#    From: src\scene\channelTitle\iplChannelTitle.cpp
# ---------------------------------------------------
#      40:                 } 
# Warning:                 ^
#   (10184) return value expected
#   (included from:
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\iplSceneBase.h:6
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\iplFaderSceneBase.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\iplSceneUIHeader.h:5
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\include\scene\channelTitle\iplChannelTitle.h:4
#       Z:\mnt\drive2\projects\wii-ipl-workers\sol-
#   low\src\scene\channelTitle\iplChannelTitle.cpp:6)
[122/126] LINK build/43U/main.elf
### mwldeppc.exe Linker Warning:
#   FORCEACTIVE symbol '__sinit_\iplSystem_cpp' is either not a global symbol 
#   or doesn't exist.  Ignored.
### mwldeppc.exe Linker Warning:
#   FORCEACTIVE symbol '__sinit_\iplPlayTimeLog_cpp' is either not a global 
#   symbol or doesn't exist.  Ignored.
### mwldeppc.exe Linker Warning:
#   FORCEACTIVE symbol '__sinit_\iplCalendar_cpp' is either not a global 
#   symbol or doesn't exist.  Ignored.
### mwldeppc.exe Linker Warning:
#   FORCEACTIVE symbol '__sinit_\iplDate_cpp' is either not a global symbol or 
#   doesn't exist.  Ignored.
### mwldeppc.exe Linker Warning:
#   FORCEACTIVE symbol '__sinit_\tiToolBar_cpp' is either not a global symbol 
#   or doesn't exist.  Ignored.
### mwldeppc.exe Linker Warning:
#   FORCEACTIVE symbol '__sinit_\tiPredictLang_cpp' is either not a global 
#   symbol or doesn't exist.  Ignored.
ninja: build stopped: subcommand failed.

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 97.3852
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 30156/37884 data 1040/5696 functions 104/112 fuzzy 97.9460 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 103/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 97.946045
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 90.53006
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 93.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 92.42069
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 92.9508
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
global matched_code_percent: 83.95137 -> 84.11617
global fuzzy_match_percent: 97.66636 -> 97.72955
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE FAIL: full build failed
```

### sol-r5-gate-derived-quick.txt

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 97.3852
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
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 92.9508
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
global matched_code_percent: 83.95137 -> 84.11617
global fuzzy_match_percent: 97.66636 -> 97.74393
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r5-gate-derived-full.txt

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 97.3852
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
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 92.9508
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
global matched_code_percent: 83.95137 -> 84.11617
global fuzzy_match_percent: 97.66636 -> 97.74393
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r5-gate-final.txt

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 97.3852
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
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 92.9508
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
global matched_code_percent: 83.95137 -> 84.11617
global fuzzy_match_percent: 97.66636 -> 97.74393
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r5-gate-postcommit.txt

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 24100/33828 data 224 functions 102 fuzzy 97.3852
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
[src/scene/setting/iplSetting] baseline: code 25220/37884 data 1040 functions 102 fuzzy 92.9508
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
global matched_code_percent: 83.95137 -> 84.11617
global fuzzy_match_percent: 97.66636 -> 97.74393
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.15434 -> 90.15434
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
