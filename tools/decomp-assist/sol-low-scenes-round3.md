# Scenes round 3 attempts

Baseline: merged main `2058b121`. All 129 Select, 112 Setting and 66 Memory original functions are present; no assembly bodies remain. Work stayed in this checkout and /tmp. No matching flags changed.

Coverage: all 35 initially open Select functions, all 12 initially open Setting functions, and all four initially open Memory functions received at least three distinct successful source builds this round. Prior-round attempts are excluded. Failed builds are recorded separately and do not satisfy the minimum. Compiler-folded variations count as experiments, without any claim that they improved the output.

## Measurements

- `src/scene/sdChannelSelect/iplSDChannelSelect`: instruction-exact 94 -> 98; objdiff exact 94 -> 98; matched code 19192 -> 21832/33828; matched data 224 -> 224/2960.
- `src/scene/setting/iplSetting`: instruction-exact 99 -> 101; objdiff exact 100 -> 102; matched code 23820 -> 25220/37884; matched data 1040 -> 1040/5696.
- `src/scene/sdChannelMemory/iplSDMemory`: instruction-exact 61 -> 61; objdiff exact 62 -> 62; matched code 13852 -> 13852/20872; matched data 200 -> 200/3344.

## Retained changes

- Select updatePageTransform: reconstructed the unfactored Hermite basis and tangent combination in its owner-only header branch; the VEC3 subtraction returns the actual nw4r vector before conversion. Paired vector subtraction uses the existing helper. 155/155 instructions, diffs 0; +620 code bytes.
- Select handleSDChannelUpdateComplete: reread the current channel across calls and retain only the state-pair pointer inside each branch. 108/108, diffs 0; +432 code bytes.
- Select applyChannelMove: enqueue failure exits after the error animation/state; destination slot precedes source slot; coordinate reads occur before destination writes. 130/130, diffs 0; +520 code bytes.
- Select updateDialogAnimation: reconstructed dialog-state blocks, operation cases and textbox/message lookup order. The zero dialog-state path stays separate; the case-8 operation blocks follow the original order. 267/267, diffs 0; +1068 code bytes.
- Select processWorkerCommands: command cases 1/3/4 fall through queue clearing; the SD reset guard exits on a pending dialog; command cases follow the original block order. Delete flags come from argument 0. Notice page/index and metadata title use the original fields. Unsigned notice-flag range and NAND-title compaction follow the target. 326/326, 11 register differences; retained as a control-flow and payload correction, not an exact match.
- Setting updateScroll: use the existing two-entry arrow table instead of the group-binding table. Read direction and layout before storing the animation index. 179/179, diffs 0; +716 code bytes.
- Setting setAPDraw: perform the actual textbox DynamicCast before UTF conversion; reset the four signal animations separately; retain each animator across initialization/restart; reread the descriptor across calls. The typed scan-buffer union covers the count and serialized records without changing layout, and the next descriptor indexes that complete buffer. 171/171, diffs 0; +684 code bytes.
- Setting data: restored the existing animation-binding table name scAnmTable. Its first 232 bytes are the original binding records. The original extracted symbol also aggregates following compiler-emitted local arrays; the restored symbol identity gives .rodata a 32.25412% objdiff score. No bytes, unused objects, force-active entries or hand-placed labels were added for this change.

## Data audit and limitations

- All three pools pass pool_diff, including the compared literal order. Source literals and pointer tables were checked against the original objects; no packed string storage was introduced. Full data-section identity is not claimed.
- Select .rodata 64, .sdata 80 and .sdata2 80 are 100%. Named pane/clock tables sit at the original offsets. The actual handler and scene vtable slots agree with the target. The extracted scene symbol includes zeroed space for deduplicated weak tables; the source contains their normal relocations.
- Setting .bss 456, .sbss 16, .sdata 504 and .sdata2 64 are 100%. The animation records and following browser arrays retain their original byte order. Source .rodata is 600 versus 640 target bytes: scNumber and scNumber2 are two original 20-byte digit maps without an established caller. They remain unresolved; no unused replacement tables were added to fill the section.
- Setting .data still differs: APEvent is at target offset 0xe9c and Setting at 0xeb4; source emits Setting at 0xe9c and APEvent at 0xf04, followed by weak tables. The actual Setting vtable slots are correct, including inherited FaderSceneBase::calc. Source emission order and deduplicated weak space remain unresolved.
- Memory .sdata 152 and .sdata2 48 are 100%; .data size is 3144 in both objects. Pane arrays, strings, two dialog jump tables and the Dialog/Title/Control handler tables have the original offsets and functional relocation slots. The remaining source weak tables occupy zero-filled space in the extracted target. No data is claimed fully matching beyond the reported sections.
- The instruction decoder counts one objdiff-exact Setting function and one objdiff-exact Memory function differently around CR1 varargs instructions. Counts in the report distinguish raw instruction checks from objdiff; the existing decoder was not changed.

## Remaining functions


### src/scene/sdChannelSelect/iplSDChannelSelect

- `ipl::scene::SDChannelSelect::startPageTransition(int, int)` 99.888885%: vector temporaries use reversed stack locations. src 0xb4 base 0xb4 insns 45/45.
- `ipl::scene::SDChannelSelect::processWorkerCommands()` 99.800610%: NAND-title compaction index and adjacent pointer receive r6/r7 in the opposite order. src 0x518 base 0x518 insns 326/326.
- `ipl::scene::SDChannelSelect::flushSaveDataAndMountSD()` 99.657140%: heap and NAND manager loads have reversed operand scheduling. src 0x8c base 0x8c insns 35/35.
- `ipl::scene::SDChannelSelect::handleSDTitleListResult()` 99.152050%: the short initial-result branch uses a different branch sequence plus register choices. src 0x2a8 base 0x2ac insns 170/171.
- `ipl::scene::SDChannelSelect::calcCommon()` 99.074070%: the button call emits an extra unused-parameter load. src 0x1b4 base 0x1b0 insns 109/108.
- `ipl::scene::SDChannelSelect::initializeNormalPage()` 98.936170%: the button call emits an extra unused-parameter load. src 0x17c base 0x178 insns 95/94.
- `ipl::scene::SDChannelSelect::selectChannel(int, int)` 98.305084%: the button call emits an extra unused-parameter load. src 0xf0 base 0xec insns 60/59.
- `ipl::scene::SDChannelSelect::collectTitlesFromNandUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)` 97.833336%: count increment and usage-threshold load scheduling differ. src 0x198 base 0x198 insns 102/102.
- `ipl::scene::SDChannelSelect::collectTitlesByUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)` 97.811880%: count increment and usage-threshold load scheduling differ. src 0x194 base 0x194 insns 101/101.
- `ipl::scene::SDChannelSelect::enqueueNotice(unsigned long, unsigned long, unsigned long)` 97.511110%: notice payload stores, member reloads and queue-call scheduling differ. src 0xb8 base 0xb4 insns 46/45.
- `ipl::scene::@unnamed@iplSDChannelSelect_cpp@::SDChannelSelectButtonEventHandler::onEventDerived(unsigned long, unsigned long, const ipl::controller::Interface*)` 95.680560%: event dispatch branches and register allocation differ; the button handler also has different event forwarding blocks. src 0x230 base 0x240 insns 140/144.
- `ipl::scene::SDChannelSelect::enqueueLoadNotice()` 95.652176%: notice payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueuePageNotice()` 95.652176%: notice payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueResultNotice(unsigned long)` 95.652176%: notice payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueMoveNotice(unsigned long, unsigned long, unsigned long)` 95.652176%: notice payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueErrorNotice(unsigned long, unsigned long)` 95.652176%: notice payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::enqueueStateNotice(unsigned long, unsigned long, unsigned long, unsigned long)` 95.130430%: notice payload stores, member reloads and queue-call scheduling differ. src 0x60 base 0x5c insns 24/23.
- `ipl::scene::SDChannelSelect::destroy()` 95.097565%: teardown loop and pointer-reload scheduling differ. src 0x32c base 0x334 insns 203/205.
- `ipl::scene::SDChannelSelect::drawChannelTransitionObjects()` 94.974846%: paired-vector conversion, stack layout and transform scheduling differ. src 0x264 base 0x27c insns 153/159.
- `ipl::scene::SDChannelSelect::enqueueFinishNotice()` 94.444440%: notice payload stores, member reloads and queue-call scheduling differ. src 0x4c base 0x48 insns 19/18.
- `ipl::scene::SDChannelSelect::create()` 94.239720%: constructor-local allocation and polling-loop scheduling differ. src 0x248 base 0x248 insns 146/146.
- `ipl::scene::SDChannelSelect::enqueueStartNotice()` 94.117645%: notice payload stores, member reloads and queue-call scheduling differ. src 0x48 base 0x44 insns 18/17.
- `ipl::scene::SDChannelSelect::onEventDerived(const char*, unsigned long, ipl::controller::Interface*)` 94.085720%: event dispatch branches and register allocation differ; the button handler also has different event forwarding blocks. src 0x19c base 0x1a4 insns 103/105.
- `ipl::scene::SDChannelSelect::onButtonEvent(const char*, unsigned long, const ipl::controller::Interface*)` 93.736270%: button event branches and reload scheduling differ. src 0x15c base 0x16c insns 87/91.
- `ipl::scene::SDChannelSelect::setChannelScissor(const ipl::scene::SDChannelObj*) const` 93.484980%: floating-point/register scheduling and scissor-bound evaluation differ. src 0x3a4 base 0x3a4 insns 233/233.
- `ipl::scene::SDChannelSelect::isCurrentTitleUsageEnough(const long*) const` 93.078430%: register, stack and operation scheduling differ. src 0xc8 base 0xcc insns 50/51.
- `ipl::scene::SDChannelSelect::enqueueChannelNotice(unsigned long, unsigned long, unsigned long, unsigned long)` 90.869570%: notice payload stores, member reloads and queue-call scheduling differ. src 0x64 base 0x5c insns 25/23.
- `ipl::scene::SDChannelSelect::getCurrentTitleUsage(long*, long*) const` 86.823530%: register, stack and operation scheduling differ. src 0xc4 base 0xcc insns 49/51.
- `ipl::scene::SDChannelSelect::collectTitlesByChannelOrder(const long*, const long*, unsigned long long*, char*, unsigned long*)` 86.555560%: fallback-title blocks and NAND-title reloads differ; the target-derived 126/126 trial retained 22 register/scheduling differences. src 0x1d8 base 0x1f8 insns 118/126.
- `ipl::scene::SDChannelSelect::collectTitlesBySpecialChannels(const long*, const long*, unsigned long long*, char*, unsigned long*)` 71.639890%: sentinel, priority-channel and usage branches differ; target-derived trials remained 341/361. src 0x52c base 0x5a4 insns 331/361.
- `ipl::scene::SDChannelSelect::findAdjacentChannel(int, int*, int*) const` 48.044445%: duplicated wrap blocks differ from the original single-wrap loop; target-derived trials reached 45/45 but retained register differences. src 0xc0 base 0xb4 insns 48/45.

### src/scene/setting/iplSetting

- `ipl::scene::Setting::makeSupportCode()` 99.078950%: string lengths use different callee-saved registers. src 0x130 base 0x130 insns 76/76.
- `ipl::scene::Setting::convertRevIP(unsigned char*, const char*)` 98.150690%: parser counters and output cursor use different callee-saved registers. src 0x124 base 0x124 insns 73/73.
- `ipl::scene::Setting::createBrowser()` 93.687706%: browser rectangle/stack placement and product-area/page branch structure differ. src 0x4d0 base 0x4b4 insns 308/301.
- `ipl::scene::Setting::scanAP()` 88.106620%: scroll animation selection, wait-state loads and jump-table dispatch differ. src 0x3fc base 0x440 insns 255/272.
- `ipl::scene::Setting::setUSBAP()` 78.421050%: success/failure block ordering and state-dispatch branches differ. src 0xdc base 0xe4 insns 55/57.
- `ipl::scene::Setting::calcKeyboard()` 75.624140%: keyboard-state dispatch, form-pointer selection and masking branches differ. src 0x494 base 0x488 insns 293/290.
- `ipl::scene::Setting::calcNormal()` 67.917960%: dialog-state blocks, controller lifetime and branch/call scheduling differ. src 0x1120 base 0x1218 insns 1096/1158.
- `ipl::scene::Setting::initKeyboard(const char*)` 67.309860%: form-case order, default local initialization, regional row-limit and validation branches differ. src 0x34c base 0x354 insns 211/213.
- `ipl::scene::Setting::validateEULA_()` 64.414894%: TMD result storage, error/success block order and System argument-base scheduling differ. src 0x174 base 0x178 insns 93/94.
- `ipl::scene::Setting::draw()` 49.120255%: browser rendering control flow, stack textures/colors, material setup and clipping blocks differ. src 0x670 base 0x9e0 insns 412/632.

### src/scene/sdChannelMemory/iplSDMemory

- `ipl::scene::SDMemory::onDialogState8()` 99.778480%: header textbox register and row-accumulation registers differ; direct conversion trials reduced the six differences to three header-register differences. src 0x278 base 0x278 insns 158/158.
- `ipl::scene::SDMemory::create(EGG::Heap*, ipl::nand::LayoutFile*, ipl::scene::SDChannelSelect*)` 95.456764%: cached-title visibility branch, animator reuse and pane-trigger setup differ. src 0x10d8 base 0x10a0 insns 1078/1064.
- `ipl::scene::SDMemory::onDialogState21()` 90.060974%: format initialization/copy block and pointer-length arithmetic differ; normal string-copy trials remained two instructions short. src 0x13c base 0x148 insns 79/82.
- `ipl::scene::SDMemory::drawTransferTitles()` 85.421290%: color conversion/copy temporaries, clipping and stack/register scheduling differ; the closest color-copy trial was 454/451. src 0x698 base 0x70c insns 422/451.

## New attempt evidence

Each item below records a distinct source transformation, its successful build instruction diff, and its pool result. A failed build remains a failed experiment. Restored trials are not part of the committed source.


### src/scene/sdChannelSelect/iplSDChannelSelect

- `ipl::scene::SDChannelSelect::startPageTransition(int, int)`: baseline 99.888885%, retained 99.888885%; 6 distinct successful attempts.
  - declare animation result before transform input and assign after multiplication: build OK; src 0xc0 base 0xb4 insns 48/45; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - construct animation origin then multiply directly into its base vector: build OK; src 0xc0 base 0xb4 insns 48/45; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - pass an explicit animation vector temporary to animation initialization: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 6: [17, 24, 28, 29, 31, 32]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize input as a vector value expression: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 5: [17, 24, 28, 29, 32]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep animation input immutable after transformation: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 5: [17, 24, 28, 29, 32]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - declare input before scene animation operations: build OK; src 0xc0 base 0xb4 insns 48/45; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::flushSaveDataAndMountSD()`: baseline 99.657140%, retained 99.657140%; 3 distinct successful attempts.
  - resolve manager before heap into named flush arguments: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain flush result separately before member assignment: build OK; src 0x8c base 0x8c insns 35/35; diffs 2: [20, 21]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve flush heap before resetting menu flag: build OK; src 0x8c base 0x8c insns 35/35; diffs 3: [17, 19, 20]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::handleSDTitleListResult()`: baseline 99.152050%, retained 99.152050%; 6 distinct successful attempts.
  - make short operation delay branch explicit with else work scope: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - compare signed elapsed time against signed clock interval: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use explicit signed comparison result for operation delay: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - nest result handling under completed operation delay: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - delay branch exits a single iteration work loop: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - combine asynchronous and dialog readiness guard: build OK; src 0x2b8 base 0x2ac insns 174/171; --- delete mine 8:13 base 8:8; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::calcCommon()`: baseline 99.074070%, retained 99.074070%; 3 distinct successful attempts.
  - test channel layout readiness inside the scene state guard: build FAILED; #   Error:                           ^^^^^^^^^^^^^^^; #   (10114) '(' expected.
  - pass computed arrow availability to both appearance initializers: build OK; src 0x190 base 0x1b0 insns 100/108; --- delete mine 4:5 base 4:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain event handler pointer before scene manager lookup: build FAILED; #   Error:                      ^^^^^^^^^^^^; #   (10140) undefined identifier 'EventHandler'.
  - nest layout readiness under the state check: build OK; src 0x1b4 base 0x1b0 insns 109/108; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain event handler before obtaining the button: build OK; src 0x1b8 base 0x1b0 insns 110/108; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::initializeNormalPage()`: baseline 98.936170%, retained 98.936170%; 3 distinct successful attempts.
  - handle active page animation first then initialize the normal page: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve initial page animation through a named reference: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - nest the right-arrow page bounds: build OK; src 0x194 base 0x178 insns 101/94; --- delete mine 4:5 base 4:4; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::selectChannel(int, int)`: baseline 98.305084%, retained 98.305084%; 3 distinct successful attempts.
  - construct animation position through the vector base explicitly: build OK; src 0xf0 base 0xec insns 60/59; --- delete mine 41:42 base 41:41; POOL IDENTICAL up to 101 (mine=101 base=101).
  - find button before constructing channel animation position: build OK; src 0xf4 base 0xec insns 61/59; --- replace mine 5:7 base 5:7; POOL IDENTICAL up to 101 (mine=101 base=101).
  - express arrow disappearance under positive boolean guards: build OK; src 0xf0 base 0xec insns 60/59; --- replace mine 27:29 base 27:29; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesFromNandUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 97.833336%, retained 97.833336%; 3 distinct successful attempts.
  - advance count through compound addition then test usage: build OK; src 0x198 base 0x198 insns 102/102; diffs 4: [69, 70, 71, 72]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain copied title slot separately while adding usage: build OK; src 0x198 base 0x198 insns 102/102; diffs 26: [0, 2, 3, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 69]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - test required blocks before required bytes: build OK; src 0x198 base 0x198 insns 102/102; diffs 6: [69, 70, 71, 72, 75, 76]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesByUsage(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 97.811880%, retained 97.811880%; 3 distinct successful attempts.
  - advance count through compound addition then test usage: build OK; src 0x194 base 0x194 insns 101/101; diffs 4: [67, 68, 69, 70]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - retain copied title slot separately while adding usage: build OK; src 0x194 base 0x194 insns 101/101; diffs 26: [0, 2, 3, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 67]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - test required blocks before required bytes: build OK; src 0x194 base 0x194 insns 101/101; diffs 6: [67, 68, 69, 70, 73, 74]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueNotice(unsigned long, unsigned long, unsigned long)`: baseline 97.511110%, retained 97.511110%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0xd8 base 0xb4 insns 54/45; --- delete mine 4:5 base 4:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0xd0 base 0xb4 insns 52/45; --- replace mine 10:18 base 10:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0xd0 base 0xb4 insns 52/45; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::@unnamed@iplSDChannelSelect_cpp@::SDChannelSelectButtonEventHandler::onEventDerived(unsigned long, unsigned long, const ipl::controller::Interface*)`: baseline 95.680560%, retained 95.680560%; 3 distinct successful attempts.
  - forward drag button events only in the four target states: build OK; src 0x240 base 0x240 insns 144/144; diffs 57: [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use captured scene state for normal button readiness: build OK; src 0x240 base 0x240 insns 144/144; diffs 57: [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - reject nonzero events before the normal button path: build OK; src 0x240 base 0x240 insns 144/144; diffs 57: [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueLoadNotice()`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0x6c base 0x5c insns 27/23; --- replace mine 7:19 base 7:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0x64 base 0x5c insns 25/23; --- replace mine 7:16 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0x64 base 0x5c insns 25/23; --- delete mine 3:5 base 3:3; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueuePageNotice()`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0x6c base 0x5c insns 27/23; --- replace mine 7:19 base 7:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0x64 base 0x5c insns 25/23; --- replace mine 7:16 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0x64 base 0x5c insns 25/23; --- delete mine 3:5 base 3:3; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueResultNotice(unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0x78 base 0x5c insns 30/23; --- replace mine 7:19 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0x70 base 0x5c insns 28/23; --- replace mine 7:15 base 7:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0x7c base 0x5c insns 31/23; --- delete mine 3:7 base 3:3; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueMoveNotice(unsigned long, unsigned long, unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0x74 base 0x5c insns 29/23; --- replace mine 7:20 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0x6c base 0x5c insns 27/23; --- replace mine 7:17 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0x7c base 0x5c insns 31/23; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueErrorNotice(unsigned long, unsigned long)`: baseline 95.652176%, retained 95.652176%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0x74 base 0x5c insns 29/23; --- replace mine 7:19 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0x6c base 0x5c insns 27/23; --- replace mine 7:16 base 7:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0x7c base 0x5c insns 31/23; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueStateNotice(unsigned long, unsigned long, unsigned long, unsigned long)`: baseline 95.130430%, retained 95.130430%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0x78 base 0x5c insns 30/23; --- replace mine 7:20 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0x70 base 0x5c insns 28/23; --- replace mine 7:17 base 7:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0x84 base 0x5c insns 33/23; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::destroy()`: baseline 95.097565%, retained 95.097565%; 3 distinct successful attempts.
  - iterate teardown channels through a for-loop initializer and increment: build OK; src 0x33c base 0x334 insns 207/205; --- delete mine 11:13 base 11:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - while loop as for loop: build OK; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
  - access mpSDWorker through a typed member reference: build OK; src 0x32c base 0x334 insns 203/205; --- insert mine 11:11 base 11:12; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::drawChannelTransitionObjects()`: baseline 94.974846%, retained 94.974846%; 3 distinct successful attempts.
  - while loop as for loop: build OK; src 0x264 base 0x27c insns 153/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - nested short-circuit branch guards: build OK; src 0x264 base 0x27c insns 153/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - access mpErrorLayout through a typed member reference: build OK; src 0x264 base 0x27c insns 153/159; --- replace mine 6:10 base 6:20; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::applyChannelMove()`: baseline 94.669230%, retained 100.000000%; 6 distinct successful attempts.
  - finish channel move immediately when its load request fails: build OK; src 0x20c base 0x208 insns 131/130; --- replace mine 12:13 base 12:13; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve destination slot before source slot for the exchange: build OK; src 0x20c base 0x208 insns 131/130; --- replace mine 12:13 base 12:13; POOL IDENTICAL up to 101 (mine=101 base=101).
  - copy move coordinates before updating channel objects: build OK; src 0x208 base 0x208 insns 130/130; diffs 4: [104, 105, 107, 108]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve the current channel before copying destination coordinates: build OK; src 0x208 base 0x208 insns 130/130; diffs 2: [104, 105]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - declare the current channel before evaluating destination values: build OK; src 0x208 base 0x208 insns 130/130; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
  - copy destination coordinates through a channel reference: build OK; src 0x208 base 0x208 insns 130/130; diffs 2: [104, 105]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueFinishNotice()`: baseline 94.444440%, retained 94.444440%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0x58 base 0x48 insns 22/18; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0x50 base 0x48 insns 20/18; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0x50 base 0x48 insns 20/18; --- replace mine 2:4 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::create()`: baseline 94.239720%, retained 94.239720%; 3 distinct successful attempts.
  - calculate thumbnail size before resolving allocator: build OK; src 0x244 base 0x248 insns 145/146; --- insert mine 105:105 base 105:107; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep wait tick inside a BS2 polling scope: build OK; src 0x244 base 0x248 insns 145/146; --- insert mine 105:105 base 105:107; POOL IDENTICAL up to 101 (mine=101 base=101).
  - poll BS2 readiness with an explicit for loop: build OK; src 0x244 base 0x248 insns 145/146; --- insert mine 105:105 base 105:107; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueStartNotice()`: baseline 94.117645%, retained 94.117645%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0x54 base 0x44 insns 21/17; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0x4c base 0x44 insns 19/17; --- replace mine 2:3 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0x4c base 0x44 insns 19/17; --- replace mine 2:4 base 2:4; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::onEventDerived(const char*, unsigned long, ipl::controller::Interface*)`: baseline 94.085720%, retained 94.085720%; 3 distinct successful attempts.
  - move the work region beneath the inverted readiness guard: build OK; src 0x19c base 0x1a4 insns 103/105; --- replace mine 10:11 base 10:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - nested short-circuit branch guards: build OK; src 0x19c base 0x1a4 insns 103/105; --- replace mine 19:20 base 19:20; POOL IDENTICAL up to 101 (mine=101 base=101).
  - apply an explicit positive test to the compound input guard: build OK; src 0x19c base 0x1a4 insns 103/105; --- replace mine 19:20 base 19:20; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::onButtonEvent(const char*, unsigned long, const ipl::controller::Interface*)`: baseline 93.736270%, retained 93.736270%; 3 distinct successful attempts.
  - move the work region beneath the inverted readiness guard: build OK; src 0x15c base 0x16c insns 87/91; --- replace mine 17:18 base 17:18; POOL IDENTICAL up to 101 (mine=101 base=101).
  - nested short-circuit branch guards: build OK; src 0x15c base 0x16c insns 87/91; --- replace mine 17:18 base 17:18; POOL IDENTICAL up to 101 (mine=101 base=101).
  - apply an explicit positive test to the compound input guard: build OK; src 0x15c base 0x16c insns 87/91; --- replace mine 17:18 base 17:18; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::setChannelScissor(const ipl::scene::SDChannelObj*) const`: baseline 93.484980%, retained 93.484980%; 3 distinct successful attempts.
  - invert first complete if/else: build OK; src 0x3a4 base 0x3a4 insns 233/233; diffs 128: [31, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - compute transformed scissor bounds through named display scales: build OK; src 0x3a4 base 0x3a4 insns 233/233; diffs 66: [38, 39, 40, 41, 43, 44, 46, 49, 50, 52, 53, 54, 68, 69, 70, 71, 72, 74, 75, 78]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - apply an explicit positive test to the compound input guard: build OK; src 0x3a4 base 0x3a4 insns 233/233; diffs 67: [38, 39, 40, 41, 43, 44, 46, 49, 50, 52, 53, 54, 68, 69, 70, 71, 72, 74, 75, 76]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::isCurrentTitleUsageEnough(const long*) const`: baseline 93.078430%, retained 93.078430%; 3 distinct successful attempts.
  - load bytes before blocks and return through positive usage guard: build OK; src 0xcc base 0xcc insns 51/51; diffs 9: [5, 7, 8, 34, 35, 36, 37, 39, 40]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - search current title with explicit while loop: build OK; src 0xcc base 0xcc insns 51/51; diffs 9: [5, 7, 8, 34, 35, 36, 37, 39, 40]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - reload NAND title count in usage search and hit guard: build OK; src 0xd0 base 0xcc insns 52/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::enqueueChannelNotice(unsigned long, unsigned long, unsigned long, unsigned long)`: baseline 90.869570%, retained 90.869570%; 3 distinct successful attempts.
  - initialize the complete command as an aggregate: build OK; src 0x80 base 0x5c insns 32/23; --- replace mine 7:19 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - zero-initialize command before setting its active payload: build OK; src 0x78 base 0x5c insns 30/23; --- replace mine 7:15 base 7:8; POOL IDENTICAL up to 101 (mine=101 base=101).
  - clear command before assigning its nonzero fields: build OK; src 0x8c base 0x5c insns 35/23; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::handleSDChannelUpdateComplete()`: baseline 86.824070%, retained 100.000000%; 6 distinct successful attempts.
  - reload the current loaded channel at each worker completion operation: build OK; src 0x1b8 base 0x1b0 insns 110/108; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - load completion index before its page: build OK; src 0x1b8 base 0x1b0 insns 110/108; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - enter replacement work under a positive channel visibility guard: build OK; src 0x1b8 base 0x1b0 insns 110/108; --- replace mine 9:10 base 9:10; POOL IDENTICAL up to 101 (mine=101 base=101).
  - cache the completed channel only while assigning its state pair: build OK; src 0x1b0 base 0x1b0 insns 108/108; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
  - set completion state before its icon flags: build OK; src 0x1b0 base 0x1b0 insns 108/108; diffs 8: [39, 40, 41, 42, 61, 62, 63, 64]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use a channel reference for paired completion state updates: build OK; src 0x1b0 base 0x1b0 insns 108/108; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::getCurrentTitleUsage(long*, long*) const`: baseline 86.823530%, retained 86.823530%; 3 distinct successful attempts.
  - use named byte and block destination references: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - advance title search with explicit while loop: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
  - reload title list for each usage addition through an indexed reference: build OK; src 0xc4 base 0xcc insns 49/51; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesByChannelOrder(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 86.555560%, retained 86.555560%; 5 distinct successful attempts.
  - move the work region beneath the inverted readiness guard: build FAILED; #   Error:               ^^^^; #   (10141) expression syntax error.
  - nested short-circuit branch guards: build OK; src 0x1d8 base 0x1f8 insns 118/126; --- replace mine 5:11 base 5:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - apply an explicit positive test to the compound input guard: build OK; src 0x1d8 base 0x1f8 insns 118/126; --- replace mine 5:11 base 5:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - load channel title or zero and reload matching NAND usage by index: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 22: [19, 23, 27, 28, 29, 33, 34, 36, 37, 38, 41, 42, 51, 52, 56, 85, 86, 87, 88, 102]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - declare block usage before byte usage to reflect target stack layout: build OK; src 0x1f8 base 0x1f8 insns 126/126; diffs 31: [11, 12, 19, 23, 27, 28, 29, 33, 34, 36, 37, 38, 41, 42, 51, 52, 56, 57, 59, 62]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use the channel title helper under its loaded banner branch: build OK; src 0x200 base 0x1f8 insns 128/126; --- replace mine 16:17 base 16:17; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::processWorkerCommands()`: baseline 83.055214%, retained 99.800610%; 18 distinct successful attempts.
  - for loop with explicit while and increment: build OK; src 0x51c base 0x518 insns 327/326; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - invert first complete if/else: build OK; src 0x51c base 0x518 insns 327/326; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 101 (mine=101 base=101).
  - move the work region beneath the inverted readiness guard: build OK; src 0x518 base 0x518 insns 326/326; diffs 256: [8, 17, 26, 28, 33, 36, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive queue clearing and dialog exits plus active command payloads from target blocks: build OK; src 0x51c base 0x518 insns 327/326; --- replace mine 26:27 base 26:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - cache the NAND title count for the removal search: build OK; src 0x51c base 0x518 insns 327/326; --- replace mine 26:27 base 26:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - perform NAND title removal through a bounded for loop: build OK; src 0x51c base 0x518 insns 327/326; --- replace mine 26:27 base 26:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - order worker commands by target blocks and search and shift through indexed title references: build OK; src 0x514 base 0x518 insns 325/326; --- replace mine 26:27 base 26:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - combine title entry movement in its normal struct assignment: build OK; src 0x514 base 0x518 insns 325/326; --- replace mine 26:27 base 26:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - make unsigned title count termination explicit during removal: build OK; src 0x514 base 0x518 insns 325/326; --- replace mine 26:27 base 26:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - load destination title reference first and nest valid SD states: build OK; src 0x514 base 0x518 insns 325/326; --- replace mine 26:27 base 26:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - dispatch SD reset states through their explicit cases: build OK; src 0x518 base 0x518 insns 326/326; diffs 11: [197, 210, 213, 215, 217, 220, 221, 225, 228, 230, 234]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - guard the SD reset state lower bound before its upper bound: build OK; src 0x514 base 0x518 insns 325/326; --- replace mine 26:27 base 26:27; POOL IDENTICAL up to 101 (mine=101 base=101).
  - declare removal index before capturing title count: build OK; src 0x518 base 0x518 insns 326/326; diffs 11: [197, 210, 213, 215, 217, 220, 221, 225, 228, 230, 234]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - keep the removal scan index separate from the shifted destination index: build OK; src 0x518 base 0x518 insns 326/326; diffs 11: [197, 210, 213, 215, 217, 220, 221, 225, 228, 230, 234]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - copy a next-title value into its destination reference: build OK; src 0x51c base 0x518 insns 327/326; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - use a signed removal index like the channel search indices: build OK; src 0x518 base 0x518 insns 326/326; diffs 11: [197, 210, 213, 215, 217, 220, 221, 225, 228, 230, 234]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - read the next shifted title through a const reference: build OK; src 0x518 base 0x518 insns 326/326; diffs 11: [197, 210, 213, 215, 217, 220, 221, 225, 228, 230, 234]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - declare the next shifted title before the search counter: build OK; src 0x518 base 0x518 insns 326/326; diffs 16: [197, 210, 213, 215, 217, 220, 221, 222, 225, 226, 227, 228, 229, 230, 231, 234]; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::updateDialogAnimation()`: baseline 77.247190%, retained 100.000000%; 7 distinct successful attempts.
  - invert first complete if/else: build OK; src 0x41c base 0x42c insns 263/267; --- replace mine 15:16 base 15:16; POOL IDENTICAL up to 101 (mine=101 base=101).
  - move the work region beneath the inverted readiness guard: build OK; src 0x414 base 0x42c insns 261/267; --- replace mine 10:11 base 10:11; POOL IDENTICAL up to 101 (mine=101 base=101).
  - nested short-circuit branch guards: build OK; src 0x41c base 0x42c insns 263/267; --- replace mine 15:16 base 15:16; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive zero-dialog handling separately and order pending message states as target blocks: build OK; src 0x42c base 0x42c insns 267/267; diffs 18: [117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 135]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - read operation state once during zero-dialog completion: build OK; src 0x42c base 0x42c insns 267/267; diffs 18: [117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 135]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - nest the idle dialog test under a named current state: build OK; src 0x42c base 0x42c insns 267/267; diffs 18: [117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 135]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - place the fourth operation state after the timed dialog transitions: build OK; src 0x42c base 0x42c insns 267/267; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::updatePageTransform()`: baseline 76.606450%, retained 100.000000%; 10 distinct successful attempts.
  - evaluate Hermite basis separately for each endpoint and add tangent by components: build OK; src 0x26c base 0x26c insns 155/155; diffs 26: [23, 26, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 53, 54, 56, 58, 59]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - form Hermite endpoint difference through vector subtraction operator: build OK; src 0x26c base 0x26c insns 155/155; diffs 77: [0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 23, 26, 39, 40, 41, 42, 43]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - add Hermite tangent as a vector value expression: build OK; src 0x274 base 0x26c insns 157/155; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - unfactored vector Hermite basis with paired vector subtraction: build OK; src 0x26c base 0x26c insns 155/155; diffs 9: [23, 42, 56, 58, 59, 61, 62, 63, 65]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Hermite difference returned as derived vector value: build OK; src 0x260 base 0x26c insns 152/155; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - Hermite difference with sequential component subtraction: build OK; src 0x27c base 0x26c insns 159/155; --- replace mine 23:24 base 23:24; POOL IDENTICAL up to 101 (mine=101 base=101).
  - return the paired subtraction result directly from the vector operator: build OK; src 0x26c base 0x26c insns 155/155; diffs 9: [23, 42, 56, 58, 59, 61, 62, 63, 65]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - form subtraction in a vector reference before conversion: build OK; src 0x26c base 0x26c insns 155/155; diffs 9: [23, 42, 56, 58, 59, 61, 62, 63, 65]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - subtract the endpoint through the base vector compound operator: build OK; src 0x278 base 0x26c insns 158/155; --- replace mine 23:24 base 23:24; POOL IDENTICAL up to 101 (mine=101 base=101).
  - return the base vector difference then convert once to the interpolated vector: build OK; src 0x26c base 0x26c insns 155/155; diffs 0: []; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::collectTitlesBySpecialChannels(const long*, const long*, unsigned long long*, char*, unsigned long*)`: baseline 71.639890%, retained 71.639890%; 5 distinct successful attempts.
  - for loop with explicit while and increment: build OK; src 0x52c base 0x5a4 insns 331/361; --- replace mine 5:20 base 5:13; POOL IDENTICAL up to 101 (mine=101 base=101).
  - move the work region beneath the inverted readiness guard: build FAILED; #   Error:               ^^^^; #   (10141) expression syntax error.
  - nested short-circuit branch guards: build OK; src 0x52c base 0x5a4 insns 331/361; --- replace mine 5:20 base 5:13; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize special title locations to missing values and reload indexed NAND usage: build OK; src 0x554 base 0x5a4 insns 341/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve temporary special title locations then retain them across searches: build OK; src 0x554 base 0x5a4 insns 341/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - test fallback capacity with explicit byte and block guards: build OK; src 0x554 base 0x5a4 insns 341/361; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
- `ipl::scene::SDChannelSelect::findAdjacentChannel(int, int*, int*) const`: baseline 48.044445%, retained 48.044445%; 7 distinct successful attempts.
  - one search loop wraps candidates before testing current slot: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 14: [0, 2, 3, 4, 6, 7, 9, 11, 13, 16, 17, 20, 22, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - return directly from the wrapped candidate search: build OK; src 0xb0 base 0xb4 insns 44/45; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 101 (mine=101 base=101).
  - derive candidate index from its page quotient: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 15: [0, 2, 3, 4, 6, 7, 9, 11, 13, 16, 17, 20, 22, 32, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - choose direction before loading current page and channel: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 15: [2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 17, 20, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - initialize direction step before current slot then test direction: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 12: [0, 2, 3, 4, 6, 7, 11, 13, 16, 17, 20, 22]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - declare page size and result before current slot calculation: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 14: [0, 2, 3, 4, 6, 7, 9, 11, 13, 16, 17, 20, 22, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).
  - resolve current page directly when wrapping to the original channel: build OK; src 0xb4 base 0xb4 insns 45/45; diffs 14: [0, 2, 3, 4, 6, 7, 9, 11, 13, 16, 17, 20, 22, 39]; POOL IDENTICAL up to 101 (mine=101 base=101).

### src/scene/setting/iplSetting

- `ipl::scene::Setting::makeSupportCode()`: baseline 99.078950%, retained 99.078950%; 4 distinct successful attempts.
  - retain independent immutable code length when composing the support message: build OK; src 0x130 base 0x130 insns 76/76; diffs 13: [30, 32, 35, 38, 40, 46, 49, 51, 54, 56, 58, 61, 63]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - keep source text lengths immutable during support message assembly: build OK; src 0x130 base 0x130 insns 76/76; diffs 13: [30, 32, 35, 38, 40, 46, 49, 51, 54, 56, 58, 61, 63]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - append newline through a distinct accumulated message length: build OK; src 0x130 base 0x130 insns 76/76; diffs 13: [30, 32, 35, 38, 40, 46, 49, 51, 54, 56, 58, 61, 63]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - declare accumulated length before measuring the first title: build OK; src 0x130 base 0x130 insns 76/76; diffs 13: [30, 32, 35, 38, 40, 46, 49, 51, 54, 56, 58, 61, 63]; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::convertRevIP(unsigned char*, const char*)`: baseline 98.150690%, retained 98.150690%; 3 distinct successful attempts.
  - initialize parsed component count after converting the input buffer: build OK; src 0x124 base 0x124 insns 73/73; diffs 26: [6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - initialize output cursor before component offset: build OK; src 0x124 base 0x124 insns 73/73; diffs 26: [6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - advance the address parser with an explicit while loop: build OK; src 0x124 base 0x124 insns 73/73; diffs 26: [6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 28, 29, 30, 36, 38, 45]; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::updateScroll()`: baseline 94.469280%, retained 100.000000%; 5 distinct successful attempts.
  - use the original two-entry arrow table for arrow visibility and focus: build OK; src 0x2cc base 0x2cc insns 179/179; diffs 4: [162, 163, 164, 166]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - keep the scroll animation index in a local value before accessing the layout: build OK; src 0x2cc base 0x2cc insns 179/179; diffs 4: [162, 163, 164, 166]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - use an explicit cursor when clearing arrow focus: build OK; src 0x2cc base 0x2cc insns 179/179; diffs 4: [162, 163, 164, 166]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - load the layout after storing the animation index: build OK; src 0x2cc base 0x2cc insns 179/179; diffs 4: [162, 163, 164, 166]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - read direction and layout before writing the animation index: build OK; src 0x2cc base 0x2cc insns 179/179; diffs 0: []; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::createBrowser()`: baseline 93.687706%, retained 93.687706%; 3 distinct successful attempts.
  - derive the browser dimensions from the standard projection and use the original page argument: build OK; src 0x4bc base 0x4b4 insns 303/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - map product areas through the target case groups: build OK; src 0x4ac base 0x4b4 insns 299/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - compute browser height before width and allocate from the returned mem1 heap directly: build OK; src 0x4ac base 0x4b4 insns 299/301; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::scanAP()`: baseline 88.106620%, retained 88.106620%; 3 distinct successful attempts.
  - branch before looking up either completed scroll animation: build OK; src 0x410 base 0x440 insns 260/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - leave the scan state when the worker has not terminated: build OK; src 0x410 base 0x440 insns 260/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - read the scan layout and animation before updating the wait state: build OK; src 0x410 base 0x440 insns 260/272; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::setUSBAP()`: baseline 78.421050%, retained 78.421050%; 3 distinct successful attempts.
  - emit USB success before failure in the two-state switch: build OK; src 0xe0 base 0xe4 insns 56/57; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - exit the USB state switch when the worker is unavailable: build OK; src 0xe0 base 0xe4 insns 56/57; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - convert the nickname API result into a named boolean: build OK; src 0xe0 base 0xe4 insns 56/57; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::calcKeyboard()`: baseline 75.624140%, retained 75.624140%; 3 distinct successful attempts.
  - read the current keyboard state once before the state branches: build OK; src 0x494 base 0x488 insns 293/290; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - advance the security-key masking cursor in the loop increment: build OK; src 0x490 base 0x488 insns 292/290; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - handle nonempty text before the empty commit branch: build OK; src 0x494 base 0x488 insns 293/290; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::calcNormal()`: baseline 67.917960%, retained 67.917960%; 3 distinct successful attempts.
  - clamp the wait count within its active-update branch: build OK; src 0x111c base 0x1218 insns 1095/1158; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - fetch controller input after completing the screen-mode guard: build OK; src 0x111c base 0x1218 insns 1095/1158; --- replace mine 7:8 base 7:8; POOL IDENTICAL up to 108 (mine=108 base=108).
  - read the dialog result once when selecting a function result: build OK; src 0x1120 base 0x1218 insns 1096/1158; --- replace mine 36:37 base 36:37; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::initKeyboard(const char*)`: baseline 67.309860%, retained 67.309860%; 3 distinct successful attempts.
  - sign-extend the product-area result before selecting the keyboard: build OK; src 0x34c base 0x354 insns 211/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - emit keyboard form cases in the original target block order: build OK; src 0x34c base 0x354 insns 211/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - select the regional row limit through explicit branches: build OK; src 0x340 base 0x354 insns 208/213; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::validateEULA_()`: baseline 64.414894%, retained 64.414894%; 3 distinct successful attempts.
  - emit failed TMD lookup before the content validation block: build OK; src 0x178 base 0x178 insns 94/94; diffs 52: [6, 8, 9, 11, 12, 13, 23, 24, 25, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - initialize the return status before the TMD pointer: build OK; src 0x178 base 0x178 insns 94/94; diffs 56: [6, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - separate content-existence and content-error checks into nested guards: build OK; src 0x17c base 0x178 insns 95/94; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::setAPDraw()`: baseline 62.204678%, retained 100.000000%; 12 distinct successful attempts.
  - check the pane type before converting its display text: build OK; src 0x2a0 base 0x2ac insns 168/171; --- replace mine 6:7 base 6:7; POOL IDENTICAL up to 108 (mine=108 base=108).
  - stop the four signal animations in their original explicit order: build OK; src 0x2d4 base 0x2ac insns 181/171; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - derive the next descriptor from the accumulated scan-record length: build FAILED; #   Error:                                                                 ^; #   (10209) illegal implicit conversion from 'unsigned char *' to.
  - reuse each selected animator across initialization and restart: build OK; src 0x2a8 base 0x2ac insns 170/171; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - reload the descriptor around calls and use the accumulated scan offset: build OK; src 0x2ac base 0x2ac insns 171/171; diffs 1: [158]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - advance the scan index through an explicit while loop: build OK; src 0x2ac base 0x2ac insns 171/171; diffs 8: [10, 11, 19, 20, 46, 158, 159, 163]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - advance a typed scan-record cursor before assigning the next descriptor: build OK; src 0x2b0 base 0x2ac insns 172/171; --- replace mine 15:16 base 15:16; POOL IDENTICAL up to 108 (mine=108 base=108).
  - name the next record offset before indexing the scan buffer: build OK; src 0x2ac base 0x2ac insns 171/171; diffs 1: [158]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - read the scan buffer before computing the next record index: build OK; src 0x2ac base 0x2ac insns 171/171; diffs 1: [158]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - form the next record through ordinary byte-buffer pointer addition: build OK; src 0x2ac base 0x2ac insns 171/171; diffs 1: [158]; POOL IDENTICAL up to 108 (mine=108 base=108).
  - access the scan result through a typed structure reference: build OK; src 0x2b0 base 0x2ac insns 172/171; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 108 (mine=108 base=108).
  - compute the signed next record index before advancing the byte cursor: build OK; src 0x2b0 base 0x2ac insns 172/171; --- replace mine 15:16 base 15:16; POOL IDENTICAL up to 108 (mine=108 base=108).
  - index the complete serialized scan-record buffer through its typed union view: build OK; src 0x2ac base 0x2ac insns 171/171; diffs 0: []; POOL IDENTICAL up to 108 (mine=108 base=108).
- `ipl::scene::Setting::draw()`: baseline 49.120255%, retained 49.120255%; 3 distinct successful attempts.
  - compute screen height before screen width: build OK; src 0x670 base 0x9e0 insns 412/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - select browser-window visibility through explicit animation branches: build OK; src 0x678 base 0x9e0 insns 414/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).
  - bound the browser message range through a named unsigned offset: build OK; src 0x66c base 0x9e0 insns 411/632; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 108 (mine=108 base=108).

### src/scene/sdChannelMemory/iplSDMemory

- `ipl::scene::SDMemory::onDialogState8()`: baseline 99.778480%, retained 99.778480%; 9 distinct successful attempts.
  - keep header text box and message in typed temporaries: build OK; src 0x278 base 0x278 insns 158/158; diffs 6: [83, 89, 91, 137, 142, 143]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - convert row count before loading the accumulated number of rows: build OK; src 0x274 base 0x278 insns 157/158; --- replace mine 49:50 base 49:50; POOL IDENTICAL up to 90 (mine=90 base=90).
  - declare body panes before the header lookup: build OK; src 0x278 base 0x278 insns 158/158; diffs 6: [83, 89, 91, 137, 142, 143]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - convert the rounded float directly in the row accumulation: build OK; src 0x278 base 0x278 insns 158/158; diffs 3: [83, 89, 91]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - add converted line count before accumulated row count: build OK; src 0x278 base 0x278 insns 158/158; diffs 6: [83, 89, 91, 137, 142, 143]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - reuse the pane lookup cursor for the body height and name the converted rows: build OK; src 0x278 base 0x278 insns 158/158; diffs 3: [83, 89, 91]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - restart the dialog animator through a typed reference: build OK; src 0x278 base 0x278 insns 158/158; diffs 3: [83, 89, 91]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - set the header message through a typed textbox reference: build OK; src 0x278 base 0x278 insns 158/158; diffs 3: [83, 89, 91]; POOL IDENTICAL up to 90 (mine=90 base=90).
  - reuse the message-pane cursor for the title body: build OK; src 0x278 base 0x278 insns 158/158; diffs 3: [83, 89, 91]; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::create(EGG::Heap*, ipl::nand::LayoutFile*, ipl::scene::SDChannelSelect*)`: baseline 95.456764%, retained 95.456764%; 3 distinct successful attempts.
  - use the cached-title count itself as the cache scan cursor: build OK; src 0x10d8 base 0x10a0 insns 1078/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - reuse the selected arrow animator when restarting it: build OK; src 0x10cc base 0x10a0 insns 1075/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
  - select the title-button pane range before enabling triggers: build FAILED; #   Error:             ^^^^^^^^^^^^^^^^^^^^^^; #   (10140) undefined identifier 'DialogPaneEventHandler'.
  - select the title-button pane range in a correctly scoped loop: build OK; src 0x1098 base 0x10a0 insns 1062/1064; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::onDialogState21()`: baseline 90.060974%, retained 90.060974%; 6 distinct successful attempts.
  - initialize the format through an ordinary empty-string copy: build OK; src 0x140 base 0x148 insns 80/82; --- insert mine 28:28 base 28:30; POOL IDENTICAL up to 90 (mine=90 base=90).
  - clear the first format character with its typed byte size: build OK; src 0x144 base 0x148 insns 81/82; --- replace mine 28:29 base 28:29; POOL IDENTICAL up to 90 (mine=90 base=90).
  - name the message prefix length and transfer byte count before formatting: build OK; src 0x13c base 0x148 insns 79/82; --- replace mine 5:8 base 5:8; POOL IDENTICAL up to 90 (mine=90 base=90).
  - copy the empty format with a one-character limit and count the prefix bytes: build OK; src 0x140 base 0x148 insns 80/82; --- insert mine 28:28 base 28:30; POOL IDENTICAL up to 90 (mine=90 base=90).
  - declare the destination message before allocating the format: build OK; src 0x140 base 0x148 insns 80/82; --- replace mine 22:23 base 22:23; POOL IDENTICAL up to 90 (mine=90 base=90).
  - guard marker and message validity in separate blocks: build OK; src 0x140 base 0x148 insns 80/82; --- insert mine 28:28 base 28:30; POOL IDENTICAL up to 90 (mine=90 base=90).
- `ipl::scene::SDMemory::drawTransferTitles()`: baseline 85.421290%, retained 85.421290%; 6 distinct successful attempts.
  - construct distinct top and bottom colors for each title row: build OK; src 0x6b8 base 0x70c insns 430/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - name text height and rounded row count before positioning the title backgrounds: build OK; src 0x698 base 0x70c insns 422/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - advance message lines in a for loop and compute each title clipping position once: build OK; src 0x698 base 0x70c insns 422/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - copy the row shade before constructing the two gradient colors: build OK; src 0x718 base 0x70c insns 454/451; --- replace mine 22:23 base 22:23; POOL IDENTICAL up to 90 (mine=90 base=90).
  - convert the initialized GX shade into two typed text gradient colors: build OK; src 0x71c base 0x70c insns 455/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).
  - construct the row shade from its named color components: build OK; src 0x748 base 0x70c insns 466/451; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 90 (mine=90 base=90).

## Commits and changed files

- 6ebc03dc match sd channel page interpolation
- 5af45c26 match sd channel completion and move paths
- 66dcafa6 match sd dialog animation state blocks
- af960b56 restore sd worker command and notice flow
- 4bb0a533 match setting scroll arrows and animation
- 44d55da0 restore access point pane and animation flow
- 5f0d3a7a restore setting animation table identity
- 23555ca0 match access point record traversal
- `include/math/iplInterporation.h`
- `include/math/iplMathTypes.h`
- `include/scene/setting/iplSetting.h`
- `src/scene/sdChannelSelect/iplSDChannelSelect.cpp`
- `src/scene/setting/iplSetting.cpp`
- This attempt log is also changed.

## Gate blocks

The following are the captured gate outputs for this round, copied verbatim. Quick gates are identified by their filenames. Every source commit followed a full passing gate.

### sol-r3-baseline-gate.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19192/33828 data 224/2960 functions 94/129 fuzzy 95.1933 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 94/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 95.19333
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 83.055214
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDChannelUpdateComplete__Q33ipl5scene15SDChannelSelectFv 86.82407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv 77.24719
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: updatePageTransform__Q33ipl5scene15SDChannelSelectFv 76.60645
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: applyChannelMove__Q33ipl5scene15SDChannelSelectFv 94.66923
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q33ipl5scene15SDChannelSelectFPCcUlPQ33ipl10controller9Interface 94.08572
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onButtonEvent__Q33ipl5scene15SDChannelSelectFPCcUlPCQ33ipl10controller9Interface 93.73627
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 19192/33828 data 224 functions 94 fuzzy 95.1933
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 23820/37884 data 1040/5696 functions 100/112 fuzzy 89.3668 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 99/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match None
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 89.366806
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: updateScroll__Q33ipl5scene7SettingFv 94.46928
[src/scene/setting/iplSetting]   below 100: setAPDraw__Q33ipl5scene7SettingFv 62.204678
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 23820/37884 data 1040 functions 100 fuzzy 89.3668
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
global matched_code_percent: 83.11416 -> 83.11416
global fuzzy_match_percent: 96.69282 -> 96.69282
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-gate1.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 19812/33828 data 224/2960 functions 95/129 fuzzy 95.6221 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 95/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 95.622086
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 83.055214
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDChannelUpdateComplete__Q33ipl5scene15SDChannelSelectFv 86.82407
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv 77.24719
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: applyChannelMove__Q33ipl5scene15SDChannelSelectFv 94.66923
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q33ipl5scene15SDChannelSelectFPCcUlPQ33ipl10controller9Interface 94.08572
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onButtonEvent__Q33ipl5scene15SDChannelSelectFPCcUlPCQ33ipl10controller9Interface 93.73627
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: onEventDerived__Q43ipl5scene32@unnamed@iplSDChannelSelect_cpp@33SDChannelSelectButtonEventHandlerFUlUlPCQ33ipl10controller9Interface 95.68056
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 19192/33828 data 224 functions 94 fuzzy 95.1933
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.13486
global fuzzy_match_percent: 96.69282 -> 96.69768
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-gate2.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 20764/33828 data 224/2960 functions 97/129 fuzzy 95.8723 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 97/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 95.87229
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 83.055214
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: handleSDTitleListResult__Q33ipl5scene15SDChannelSelectFv 99.15205
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: updateDialogAnimation__Q33ipl5scene15SDChannelSelectFv 77.24719
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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 19192/33828 data 224 functions 94 fuzzy 95.1933
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.16664
global fuzzy_match_percent: 96.69282 -> 96.70050
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-gate3.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelSelect/iplSDChannelSelect] pool: IDENTICAL
[src/scene/sdChannelSelect/iplSDChannelSelect] objdiff: code 21832/33828 data 224/2960 functions 98/129 fuzzy 96.5906 linked code 0
[src/scene/sdChannelSelect/iplSDChannelSelect] instruction-exact functions: 98/129
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .data size 2736 match 35.06984
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .rodata size 64 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .sdata2 size 80 match 100.0
[src/scene/sdChannelSelect/iplSDChannelSelect]   section .text size 33828 match 96.59064
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
[src/scene/sdChannelSelect/iplSDChannelSelect]   below 100: processWorkerCommands__Q33ipl5scene15SDChannelSelectFv 83.055214
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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 19192/33828 data 224 functions 94 fuzzy 95.1933
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.20230
global fuzzy_match_percent: 96.69282 -> 96.70862
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-gate4.txt

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 19192/33828 data 224 functions 94 fuzzy 95.1933
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.20230
global fuzzy_match_percent: 96.69282 -> 96.71590
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-gate5.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 24536/37884 data 1040/5696 functions 101/112 fuzzy 89.4713 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 100/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match None
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 89.47134
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: setAPDraw__Q33ipl5scene7SettingFv 62.204678
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 23820/37884 data 1040 functions 100 fuzzy 89.3668
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.22620
global fuzzy_match_percent: 96.69282 -> 96.71723
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-gate6.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 24536/37884 data 1040/5696 functions 101/112 fuzzy 90.1527 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 100/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match None
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15268
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: setAPDraw__Q33ipl5scene7SettingFv 99.94152
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 23820/37884 data 1040 functions 100 fuzzy 89.3668
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.22620
global fuzzy_match_percent: 96.69282 -> 96.72584
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-gate7.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 24536/37884 data 1040/5696 functions 101/112 fuzzy 90.1527 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 100/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15268
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: setAPDraw__Q33ipl5scene7SettingFv 99.94152
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 23820/37884 data 1040 functions 100 fuzzy 89.3668
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.22620
global fuzzy_match_percent: 96.69282 -> 96.72584
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-gate8.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
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
[src/scene/setting/iplSetting] baseline: code 23820/37884 data 1040 functions 100 fuzzy 89.3668
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.24905
global fuzzy_match_percent: 96.69282 -> 96.72586
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-ap-quick.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 24536/37884 data 1040/5696 functions 101/112 fuzzy 90.1527 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 100/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match None
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15268
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: setAPDraw__Q33ipl5scene7SettingFv 99.94152
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 23820/37884 data 1040 functions 100 fuzzy 89.3668
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.22620
global fuzzy_match_percent: 96.69282 -> 96.72584
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### sol-r3-data-quick.txt

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/iplSetting] pool: IDENTICAL
[src/scene/setting/iplSetting] objdiff: code 24536/37884 data 1040/5696 functions 101/112 fuzzy 90.1527 linked code 0
[src/scene/setting/iplSetting] instruction-exact functions: 100/112
[src/scene/setting/iplSetting]   section .bss size 456 match 100.0
[src/scene/setting/iplSetting]   section .data size 4016 match 5.146636
[src/scene/setting/iplSetting]   section .rodata size 640 match 32.25412
[src/scene/setting/iplSetting]   section .sbss size 16 match 100.0
[src/scene/setting/iplSetting]   section .sdata size 504 match 100.0
[src/scene/setting/iplSetting]   section .sdata2 size 64 match 100.0
[src/scene/setting/iplSetting]   section .text size 37884 match 90.15268
[src/scene/setting/iplSetting]   below 100: createBrowser__Q33ipl5scene7SettingFv 93.687706
[src/scene/setting/iplSetting]   below 100: calcNormal__Q33ipl5scene7SettingFv 67.91796
[src/scene/setting/iplSetting]   below 100: draw__Q33ipl5scene7SettingFv 49.120255
[src/scene/setting/iplSetting]   below 100: initKeyboard__Q33ipl5scene7SettingFPCc 67.30986
[src/scene/setting/iplSetting]   below 100: calcKeyboard__Q33ipl5scene7SettingFv 75.62414
[src/scene/setting/iplSetting]   below 100: convertRevIP__Q33ipl5scene7SettingFPUcPCc 98.15069
[src/scene/setting/iplSetting]   below 100: scanAP__Q33ipl5scene7SettingFv 88.10662
[src/scene/setting/iplSetting]   below 100: setAPDraw__Q33ipl5scene7SettingFv 99.94152
[src/scene/setting/iplSetting]   below 100: validateEULA___Q33ipl5scene7SettingFv 64.414894
[src/scene/setting/iplSetting]   below 100: makeSupportCode__Q33ipl5scene7SettingFv 99.07895
[src/scene/setting/iplSetting]   below 100: setUSBAP__Q33ipl5scene7SettingFv 78.42105
[src/scene/setting/iplSetting] baseline: code 23820/37884 data 1040 functions 100 fuzzy 89.3668
regressions vs baseline: 0
global matched_code_percent: 83.11416 -> 83.22620
global fuzzy_match_percent: 96.69282 -> 96.72584
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```


### sol-r3-final-gate.txt — full gate, all three units

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
[src/scene/sdChannelSelect/iplSDChannelSelect] baseline: code 19192/33828 data 224 functions 94 fuzzy 95.1933
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
[src/scene/setting/iplSetting] baseline: code 23820/37884 data 1040 functions 100 fuzzy 89.3668
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
global matched_code_percent: 83.11416 -> 83.24905
global fuzzy_match_percent: 96.69282 -> 96.72586
global complete_code_percent: 58.19218 -> 58.19218
global matched_data_percent: 89.93214 -> 89.93214
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
