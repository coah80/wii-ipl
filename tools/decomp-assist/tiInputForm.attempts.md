# tiInputForm attempts

Target: 4.3U, `src/keyboard/tiInputForm`. Initial gate: 175/221 instruction-exact, objdiff 176/221, code 19124/50656, data 864/3772. All shared-header changes use `TIINPUTFORM_IMPLEMENTATION`, defined only in this source file.

- `DeadKeyStream::ToCombineClass`: translated the original switch and per-language comparisons. First build: 69/69 instructions, zero differences. `ToIndependentClass` now uses its real static member declaration; 30/30, zero differences.
- `RowInfoManager::init`: direct references produced 40/39 instructions. A cached last-row index and array pointer produced 38/39. Widening the index and narrowing only the array subscript retained 38/39. Restored the original asm to avoid regression. The remaining difference includes a repeated maximum-length load and indexing/store scheduling.
- `Base::~Base`: restored the row-manager destructor and the real C++ destructor. First build: 29/29, zero differences. This also restores twelve exact inheritance thunks.
- `LayoutByNW4R::~LayoutByNW4R`: used the sibling event handler and animation list, with explicit event-handler destruction and allocator release. First successful build: 77/77, zero differences. This restores ten additional exact inheritance thunks.
- `Base::calcCursorTimer`, `dirtyCacheAll`, `setCursorPos`, `setAtokDictionary`, `closeAtokDictionary`, `isAtokDictionaryOpened`, `getCursorPos`, and `LayoutByNW4R::isAbleToUp`/`isAbleToDown`: converted existing asm into real members. Each first build was instruction-exact. `getCursorPos` is 27/27 instructions with zero differences.
- `Base::isAtokActive`: early false return: 10/10 instructions, seven differences in branch direction/block order. A result variable: 10/10, eight differences. Positive conditional return: 10/10, seven differences. Boolean switch: 11/10. Restored the original asm to avoid regression.
- `NormalButtonAnmPane::onAnmEvent`: added the missing state-machine member. Natural numeric case order gave 147/147 instructions with 23 differences in switch-block order. Ordering the cases as the target emits them gave 147/147, zero differences.
- `Base::calcCursorPos`: direct translation with the empty-input recursion at the loop head gave 329/326 instructions and an oversized frame. Moving the empty-input handling after the loop gave 332/326. Reducing DrawInfo to its actual rectangle and character fields and introducing scalar scale components gave 323/326. Restoring aggregate scale and initializing line bottom beside line top gave 332/326. Qualifying recursive calls as Base calls and matching comparison operand direction gave 326/326, with 81 differences in floating-point allocation and scheduling. This implementation remains partial.
- `LayoutByNW4R::updateInput`: direct translation gave 155/154 instructions. Inverting the midpoint branch gave 154/154 with five operand-order differences. Reordering commutative expressions did not change those five differences. Dividing the height by two and using separate bottom-position temporaries reduced this to three. Correcting the bottom expression to add height and origin before adding one gave 154/154, zero differences.

Every measured state retained the original 20-string pool. The first gate lacked its current merge-base baseline; the baseline became available during the run. Subsequent quick gates passed with zero regressions and zero forbidden/readability additions. The unit remains NonMatching.

- `Base::isOverRowLimit`: direct glyph/row walk gave 239/238 instructions. Separating scale construction from assignment and adding an explicit null pointer initialization gave 241/238. Restoring aggregate initialization and arranging the cursor/scale temporaries gave 236/238; the retained implementation has an undersized frame plus floating-point scheduling/register differences.
- `LayoutByNW4R::onCommand`: translated the length trimming and row-limit handling. Reusing one limit variable, introducing a separate trim limit, then separating the excess position reached 251/251 instructions with 17 differences. Calling the existing inline observer method emitted an additional `OutOfLength` string. Declaring it out of line and placing its real definition at the existing string position emitted a vtable and an additional `Cancel!` string. Restored the original state; the candidate is not included because its pool did not pass.
- `RowInfoManager::init`: a fourth attempt using a typed row accessor still gave 38/39 instructions. Restored the original asm.
- `Animation::startAnm`, `getValue`, `isActive`, `setSEFlag`, `isSEFlag`, `stop`: translated into their real class members; each is instruction-exact. `Animation::calc`: reversing the commutative increment expression matches the original raw 33-instruction bytes. ctxdiff still prints two differing CR1 branch offsets; its disassembly normalization depends on each object's function offset. This is a tooling discrepancy, not an instruction-count claim.
- Static colors: restored the seven actual color objects and their constructors. Their compiler-generated initializer is 83/87 instructions. The target also registers a real LayoutGather singleton in the still-missing command handler and dynamically initializes an animation table pointer. Those missing objects account for destructor-chain offsets and the final four instructions. No artificial placement was added.
- `LayoutByNW4R::getScale`: root-pane lookup using the existing layout and pane headers. First build: 18/18 instructions, zero differences.
- `WithAtok`: replaced 36 existing no-op/constant-return asm methods with C++ bodies reproducing the original disabled Atok implementation. Also converted the original no-op `Decolated::EnableKSXFilter` and `deleteChar`. Corrected the confirmed-string getter's const qualifier. The fresh gate retains 199/221 instruction-exact functions, with zero regressions; these conversions improve source quality rather than function counts.
- `Base::checkHeadOfSentence`: translated the observer command, previous-character switch, cursor move and sentence check. First build: 71/71 instructions, zero differences.
- `Base::isOverLine`: aggregate scale locals gave 55/51 instructions due to duplicate temporary copies. Scalar scale values gave 59/51 with four saved floating-point registers. A single return expression gave 43/51 by delaying width loads. Const references retained 55/51; separate scale assignments gave 59/51. Restored the existing exact asm body.

- `Base::isEditMode`: a direct Boolean range and tail return gave 13/22 instructions. Switching on the two direct-edit prediction modes and explicitly testing the Zi fix state gave 22/22, zero differences.
- `Base::onPressUp` and `onPressDown`: literal translation gave 245/246 instructions. Reversing pointer comparison operands, preserving the current-string call result in a separate local, and making the prediction test positive reduced the differences to the final kana branch. An explicit common exit retained 245/246. Boolean switches with the false case first gave 247/246; the true case first gave 246/246 with only the comparison constant and branch polarity differing. A negated switch gave 247/246 and changed register allocation. Restored the readable 245/246 version; the target retains one extra unconditional branch. Guarded sibling headers expose actual Zi methods, candidate text area, and the hardware keyboard's single/double quote state.
- `Base::onPressDownHWKB`: initial nested conversion-first handling gave 266/270 with large block-order differences. Putting the modifier-driven commit before candidate navigation retained 266/270 and aligned the blocks. Hoisting the selected index and splitting the kana/candidate tests retained 266/270. The retained partial has one conditional branch difference, selected-index register allocation, and an original trailing Zi comparison whose no-op body is not reconstructed.
- `Base::onCursor`: literal candidate/kana drawing gave 475/473 instructions. Combining selection flags, ordering rectangle assignments and explicitly calculating box coordinates gave 473/473 with 22 differences. Reordering color branches and centering widths gave 473/473 with seven differences. Separate font-height temporaries regressed to 475/473. Using direct cursor-height call expressions restored 473/473 with five differences, confined to the centered-space calculation's floating-point registers and commutative operand order. Retained the best real C++ implementation, including genuine candidate/kana background colors and typed drawer fields.

- `Base::onPressLeftHWKB` and `onPressRightHWKB`: initial typed translation gave 263/264 and 274/275 instructions. Using the target's nonpositive candidate-count test and placing the active-conversion block first removed the remaining block-order differences. A true-case Boolean switch gave 264/264 and 275/275, each with two differences: compare-to-one/branch-equal instead of compare-to-zero/branch-not-equal. Retained this source variant. Zi's selected-candidate access uses the actual class state and the SDK's EZTXGetParam, guarded for this source; the selected field load agrees with the target at 0x98. The extra search-state word at 0x74 is present in the original 0x2c cleared parameter range but its precise semantics remain uncertain.

- `Base::toggleAtokMode_`: first typed translation gave 154/154 with 56 differences. Inverting the toolbar permission condition, placing active-candidate handling first, and putting mode-enable handling first gave 154/154, zero differences. The sibling PC header omitted its original allocator at 0x38; exposing that field only under this unit's macro places the original QWERTY/language flags at 0x3c/0x3d. Guarding KeyboardBase's existing two-argument onKey signature prevents an extra virtual slot.
- `Base::onHKBCtrlCode`: numeric case order gave 375/375 with 314 differences. Reordering the cases to their original emitted order reduced this to two range-test differences. Writing the inclusive CN/KR range as an unsigned difference <= 1 gave 375/375, zero differences.

- `Base::inputCharZi_`: direct translation gave 163/166 instructions. Explicitly setting the direct-input Boolean, placing the Korean alphabet branch first, and reordering letter-mode cases gave 166/166 with seven block-order differences. Ordering letter-mode cases as lower, upper, default gave 166/166, zero differences.
- `Base::confirmInputting_`: direct translation gave 345/346 instructions with the direct-input block emitted last. Moving that block first aligned the remaining code; inclusive input and prediction-length comparisons remove two comparison differences. Factoring an unconfirmed Boolean gave 349/346; two separate pointer predicates gave 347/346. Retaining the original else-if chain and its repeated unconfirmed-pointer predicate gave 346/346 and byte-identical raw text (1384 bytes). ctxdiff reports two CR1 offsets because of its disassembly normalization; objdiff is the authority for this function's score.

- `Base::inputCharDefault_`: literal C++ restored from asm: 135/135, 14 differences. Correct cursor-query calls, positive prediction branch, and local declaration order: 135/135, diffs 0.
- `Base::onSpaceKeyHWKB`: literal C++ plus semantic dead-key compatibility filter: 592/603. Original candidate/body order, inline context reset, explicit Atok boolean, and bottom-tested input loops: 603/603, 21 differences. Active-string temporary and positive boolean branch: 603/603, seven differences. Boolean switch: 607/603. Retained 603/603; seven differences are the Atok boolean block order only. Pool identical; filter loop and both candidate cycling bodies are instruction exact.

- `LayoutByNW4R::init`: qualified Layout calls: 136/151. Virtual dispatch restored: 151/151, diffs 0; pool identical. Text-drawer fields reconstructed at original offsets with no sibling output changes.
- `EventHandler::onTiEvent`: literal event dispatch: 423/419. Hoisted animation buffer and ordinary fallback literal: 420/419, but pool gains an extra `T_2l_TextBox`. Pane-name load before cursor initialization and existing base-pane field as fallback: 423/419, 96.10501%; pool identical. Remaining string-base addressing, register allocation, and fallback load differ; retained complete readable implementation.

- `LayoutByNW4R` constructor: real initializer list replaces asm: 46/46, diffs 0.
- `LayoutByNW4R::setLanguage`: literal helper: 234/237, extra inline-helper string pool. Expanded queries: 240/237, cached base-subobject register. Const pane-query helper: 237/237, 22 scheduling differences. Conditional argument form: same 22. Fallback passed into a string helper: 237/237, 64 differences. Retained const pane-query helper with pool identical.
- `EventHandler::onTiEvent`: ordinary fallback literal shared with restored constructor, pane-query reference, event-case order, inclusive repeat threshold: 419/419, five differences, all string offsets. Original table data before the second string group is still missing.
- `LayoutByNW4R::create`: literal calls to Base create: 303/356. Inlined row-list allocation and selection, real animation records, font and event handler setup: 358/356. Correct EditBuffer virtual layout and full-width outer button loop: 359/356. Pool identical. Remaining register allocation, row-list scheduling and loop lowering; complete implementation retained. Corrected missing eighth animation file pointers in both actual button records. Removed legacy duplicate font/assert string objects; ordinary literals now emit them.

- `Base::onCommand`: complete C++ dispatcher, real command payloads and Zi/dead-key/context helpers: 2038/2053, 87.37506%. Correct boolean delete-forward result, initialized saved translation mode, explicit Atok predicate: 2053/2053. Cached fixed-string selection across commands: 2056/2053; retained with gate passing. Remaining stack-frame layout (0x280 vs 0x250), register allocation, predicate lowering and case scheduling. Moved the hardware-control dispatcher before layout strings; its real jump table plus the new command jump tables fix all five event-handler offsets (419/419, diffs 0).

- `LayoutByNW4R::onCommand`: after restoring the constructor/ordinary literal pool, removing its legacy duplicate OutOfLength object allows the existing observer method to emit the real string. The earlier complete candidate is now pool-identical (251/251, 17 differences). Scope the trim limit inside the default branch, compare length on the left, and initialize the row-limit payload before its nonzero test: 251/251, diffs 0.
- `__sinit_\tiInputForm_cpp`: reconstructed the actual down-button binding target from the original final initializer store (table offset 0x4c): its animation files target the up-button pane. Using that real mutable target pointer in the down-button record emits the original dynamic initialization. 87/87, diffs 0. This object has a real runtime role, not a placement role.
- Cursor-cache symbol: restored `textdrawer::Base::isEnableCursorCache() const` and `getStartPos() const` from actual typed state. The report names the former by concatenating its mangled name with the latter. Direct bool return: raw 8 bytes `886301044e800020`, identical to the malformed original entry. Positive branch: same 8 bytes. Comparison to false: 20 bytes. Retained direct return; exact-name gate still cannot pair it with the malformed report symbol. `getStartPos`: 2/2, diffs 0. No function/config aliases were added.

- Small accessor conversion: removed 22 asm bodies in favor of existing real header definitions or typed C++ members (StringBase, Decolated, WithZi, Manager, CandidateBox and text-drawer cache state). Fresh gate: 208/221 objdiff exact, 206/221 instruction-exact, zero baseline regressions. Draw-cache getter 8/8, dirty cache 3/3, Zi candidate-count getter 2/2, string length getter 2/2, all diffs 0. Reconstructed draw/cache fields from their original loads and preserved the nested CommandReceiver::Scroll signature under the unit macro.

- `Base::onCursor`: final centered-space variation initializes the real offset before width locals and puts scale/half-width operands first: 473/473, seven differences. Restored the five-difference version.

- Final clean full gate: GATE PASS; pool IDENTICAL; instruction-exact 206/221 (baseline 175/221); objdiff functions 208/221 (baseline 176/221); code 28300/50656 (baseline 19124/50656); data 868/3772 (baseline 864/3772); zero regressions, forbidden additions and readability warnings. Full build passes and DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d. Partial result: 46 existing asm bodies remain and data is below 100%. Every remaining report-nonmatching entry has at least three logged source-level attempts.

## Continuation from merged main
- Left/right HWKB guard: zero-case/default-break switch produces 265/264 and 276/275 with an extra branch; explicit if/else yields 263/264 and 274/275, dropping the required branch; integer switch with 0 and 1 cases adds five instructions; negated boolean switch adds boolean normalization and swaps registers; moving the body into default retains the extra branch. Restored the two-difference original.
- Cursor centering continuation: reversed multiplication nesting retained five differences; half-width accumulator moved work before scale query, 17 differences; scale-first accumulator gave seven differences; declaring the offset before widths retained five. Restored best source.
- Space-key Atok continuation: false-case switch gave 604/603 with one extra branch; false initializer plus positive assignment gave 602/603; explicit forward labels retained 603/603 and the same seven block-order differences. Restored best source.
- Data reconstruction: replacing EditBuffer destructor asm with typed C++ is 61/61, diffs 0, and emits its real vtable. EventHandler declaration moved before animation classes restores all three animation/event vtable offsets. Decolated clear/set/setLength overrides and draw-cache method signatures corrected under the unit macro. Moving genuine candidate/kana color definitions to the table group, using ordinary Korean/Chinese pane literals, and restoring the original true hyphen initializer makes every .sdata byte identical. Quick gate passes with zero regressions.
- Layout language continuation: separate name temporary retains 237/237 and 22 root-load scheduling differences; duplicating the pane query across explicit branches gives 252/237; reusing the existing text-name variable with separate if/else retains 237/237 and the same 22 differences. Restored original helper form.
- Continuation void Base::onPressUp(): true case kana guard: src 0x3d8 base 0x3d8 insns 246/246; diffs 2:.
- Continuation void Base::onPressUp(): zero case kana guard: src 0x3dc base 0x3d8 insns 247/246; 17 displayed differing instructions.
- Continuation void Base::onPressUp(): loop kana guard: src 0x3dc base 0x3d8 insns 247/246; 19 displayed differing instructions.
- Continuation void Base::onPressDown(): true case kana guard: src 0x3d8 base 0x3d8 insns 246/246; diffs 2:.
- Continuation void Base::onPressDown(): zero case kana guard: src 0x3dc base 0x3d8 insns 247/246; 17 displayed differing instructions.
- Continuation void Base::onPressDown(): loop kana guard: src 0x3dc base 0x3d8 insns 247/246; 19 displayed differing instructions.
- Continuation void Base::onPressDownHWKB(): local selected index: src 0x428 base 0x438 insns 266/270; 36 displayed differing instructions.
- Continuation void Base::onPressDownHWKB(): initialize selected index: src 0x428 base 0x438 insns 266/270; 36 displayed differing instructions.
- Continuation void Base::onPressDownHWKB(): positive kana switch: src 0x42c base 0x438 insns 267/270; 37 displayed differing instructions.
- Continuation u32 Base::calcCursorPos(: loop declaration: src 0x518 base 0x518 insns 326/326; diffs 81:.
- Continuation u32 Base::calcCursorPos(: scale assignment: src 0x520 base 0x518 insns 328/326; 154 displayed differing instructions.
- Continuation u32 Base::calcCursorPos(: defer vertical coordinate: src 0x51c base 0x518 insns 327/326; 145 displayed differing instructions.
- Continuation u32 Base::isOverRowLimit(: scale assignment: src 0x3b4 base 0x3b8 insns 237/238; 223 displayed differing instructions.
- Continuation u32 Base::isOverRowLimit(: defer scale width: src 0x3b0 base 0x3b8 insns 236/238; 220 displayed differing instructions.
- Continuation u32 Base::isOverRowLimit(: glyph field initialization: src 0x3c0 base 0x3b8 insns 240/238; 196 displayed differing instructions.
- Continuation void Base::onCommand(: fresh fixed string queries: src 0x2020 base 0x2014 insns 2056/2053; 1455 displayed differing instructions.
- Continuation void Base::onCommand(: defer translate mode query: src 0x2020 base 0x2014 insns 2056/2053; 1455 displayed differing instructions.
- Continuation void Base::onCommand(: uncached fixed predicate: src 0x2014 base 0x2014 insns 2053/2053; diffs 1985:.
- Continuation void LayoutByNW4R::create(: cache row-list pointer: src 0x590 base 0x590 insns 356/356; diffs 205:.
- Continuation LayoutByNW4R::create animation switch: first experiment failed to compile because its case scope was wrong; corrected and measured below.
- Continuation void LayoutByNW4R::create(: query animation id from record: src 0x5a4 base 0x590 insns 361/356; 303 displayed differing instructions.
- Animation-pane switch retried with corrected case scope: 357/356; original conditional retained. Cached row-list pointer is retained: 356/356, 205 differences, objdiff 88.91854% versus 88.11798%; no regressions. Removing explicit placement-allocation checks gave 354/356 and was restored.
- Additional cursor experiments: reusing either box-edge variable as the marker offset gave seven differences; a real inline space-centering helper gave ten differences and changed stack temporary order. Restored the five-difference source.
- Nine additional asm conversions are instruction-exact: initZiString 14/14, resetContextPredict_ 27/27, resetRelation 23/23, textinput Base init 1/1, drawer getLine 3/3, StringBase hasCandidate 5/5, inputform Base create allocator overload 1/1, Decolated set 19/19, Decolated clear 20/20. Layout onSE 5/5 and EditBuffer destructor 61/61 are also exact C++. The allocator overload and base initializer faithfully retain their original empty bodies.
- Data limits: ordinary literal pool and .rodata/.sdata/.sdata2 are identical. Vtable relocation comparison now agrees except the reference cursor-cache concatenated symbol. EditBuffer vtable target size includes four trailing bytes and textinput Base vtable includes 28 trailing bytes without relocations; no padding was added. Other zero-filled weak data and anonymous jump-table differences remain.
- Final clean full gate: GATE PASS, pool IDENTICAL, zero regressions/forbidden additions/readability warnings; instruction-exact 206/221 unchanged, objdiff exact 208/221 unchanged, code 28300/50656 unchanged, data 868 -> 908/3772, fuzzy 97.1980 -> 97.2205. Eleven existing asm bodies converted instruction-exact to C++; 41 asm bodies remain. Linking was not changed. The literal pane tables have 100% .rodata and .sdata.

## Third continuation: remaining asm
- Kana buffer getter 2/2, VI width setter 2/2, command sender append 2/2, candidate scroll query 2/2, Decolated destructor 22/22, WithAtok destructor 23/23, CommandReceiver destructor 16/16: real C++ first builds, diffs 0. Original KanaStream layout is a KPRQueue, pending character and five-character output.
- Decolated::isKanaFix: literal 19/19, one unsigned comparison difference; explicit signed translation-mode comparison gives diffs 0.
- Base::moveCandidateToIdx: typed translation 104/104, one return-width difference; correcting the fixed prediction count to s32 gives diffs 0. Base::confirmInput_ 141/141, diffs 0 on first translation.
- Base::init: literal 81/81, two wrong reconstructed members; original slot is enableSpaceByRight and the cursor-cache scroll offset is textdrawer 0xf0. Corrected guarded declarations give diffs 0. Base::deselectCandidate 13/13, diffs 0.
- Layout calc: direct bool comparisons 132/137; initializing real up/down state before the pane query, positive separator branch and explicit comparisons give 137/137, diffs 0. Existing bar literal object replaced by the ordinary literal at its real source position; pool stays identical.
- Layout draw: natural VEC2 initialization 114/114, 12 stack temporary differences; separate vector assignments 116/114; const references 114/114 with the same 12 offsets. Restored existing exact asm.
- updateInputCommon__Q39textinput9inputform12LayoutByNW4RFiUlUlUlPv: typed repeat dispatch: src 0x5c base 0x5c insns 23/23; diffs 0: []; retained exact C++.
- updateRepeatInput__Q39textinput9inputform12LayoutByNW4RFUlUl: typed directional repeat timers: src 0x11c base 0x11c insns 71/71; diffs 16: [20, 21, 22, 23, 34, 35, 36, 37, 48, 49, 50, 51, 62, 63, 64, 65]; restored prior body.
- doLineFeed__Q39textinput9inputform4BaseFv: line height before cursor query: src 0x98 base 0x98 insns 38/38; diffs 1: [18]; restored prior body.
- doScroll__Q39textinput9inputform4BaseFPQ39textinput15CommandReceiver6Scroll: absolute or animated scroll: src 0xc8 base 0xc8 insns 50/50; diffs 0: []; retained exact C++.
- init__Q39textinput3gui12GUIComponentFv: guarded point initialization: src 0xd8 base 0xd8 insns 54/54; diffs 0: []; retained exact C++.
- updateRepeatInput__Q39textinput9inputform12LayoutByNW4RFUlUl: reuse trigger mask: src 0x11c base 0x11c insns 71/71; diffs 0: []; retained exact C++.
- doLineFeed__Q39textinput9inputform4BaseFv: height plus current cursor: src 0x98 base 0x98 insns 38/38; diffs 1: [18]; restored prior body.
- doLineFeed__Q39textinput9inputform4BaseFv: cursor scalar addition: src 0x98 base 0x98 insns 38/38; diffs 0: []; retained exact C++.
- drawFixString__Q39textinput9inputform4BaseFUl: cursor aggregate initializer: src 0xdc base 0xdc insns 55/55; diffs 7: [2, 3, 9, 10, 28, 35, 36]; restored prior body.
- drawFixString__Q39textinput9inputform4BaseFUl: cursor fields first: src 0xdc base 0xdc insns 55/55; diffs 3: [28, 35, 36]; restored prior body.
- drawFixString__Q39textinput9inputform4BaseFUl: cursor late position: src 0xdc base 0xdc insns 55/55; diffs 10: [7, 8, 9, 10, 11, 12, 13, 28, 35, 36]; restored prior body.
- draw__Q39textinput9inputform4BaseFv: natural draw vectors: src 0x158 base 0x158 insns 86/86; diffs 0: []; retained exact C++.
- doBeforeDrawProcess__Q39textinput9inputform4BaseFPCwUlRCQ49textinput10textdrawer4Base8DrawInfo: typed wrapping and selection rectangle: src 0x1cc base 0x1cc insns 115/115; diffs 2: [73, 74]; restored prior body.
- doBeforeDrawProcess__Q39textinput9inputform4BaseFPCwUlRCQ49textinput10textdrawer4Base8DrawInfo: selection cursor first operands: src 0x1cc base 0x1cc insns 115/115; diffs 2: [73, 74]; restored prior body.
- doBeforeDrawProcess__Q39textinput9inputform4BaseFPCwUlRCQ49textinput10textdrawer4Base8DrawInfo: selected range declaration order: src 0x1cc base 0x1cc insns 115/115; diffs 6: [66, 67, 72, 73, 74, 75]; restored prior body.
- drawFixString__Q39textinput9inputform4BaseFUl: widen string length before draw call: src 0xdc base 0xdc insns 55/55; diffs 0: []; retained exact C++.
- doBeforeDrawProcess__Q39textinput9inputform4BaseFPCwUlRCQ49textinput10textdrawer4Base8DrawInfo: position-first selected range compare: src 0x1cc base 0x1cc insns 115/115; diffs 0: []; retained exact C++.
- getCurrentString__Q39textinput9inputform4BaseFb: typed current string selection: src 0x1bc base 0x1c0 insns 111/112; --- replace mine 11:12 base 11:12; restored prior body.
- getCurrentString__Q39textinput9inputform4BaseFb: positive Korean keyboard branch: src 0x1bc base 0x1c0 insns 111/112; --- replace mine 11:12 base 11:12; restored prior body.
- getCurrentString__Q39textinput9inputform4BaseFb: separate fix and input predicates: src 0x1cc base 0x1c0 insns 115/112; --- replace mine 11:12 base 11:12; restored prior body.
- moveCursorUp__Q39textinput9inputform4BaseFv: typed upper row cursor: src 0x158 base 0x160 insns 86/88; --- replace mine 5:6 base 5:6; restored prior body.
- moveCursorUp__Q39textinput9inputform4BaseFv: cursor upper operands: src 0x158 base 0x160 insns 86/88; --- replace mine 5:6 base 5:6; restored prior body.
- moveCursorUp__Q39textinput9inputform4BaseFv: upper row index declaration: src 0x158 base 0x160 insns 86/88; --- replace mine 5:6 base 5:6; restored prior body.
- moveCursorDown__Q39textinput9inputform4BaseFv: typed lower row cursor: src 0x184 base 0x180 insns 97/96; --- replace mine 5:41 base 5:12; restored prior body.
- moveCursorDown__Q39textinput9inputform4BaseFv: cursor lower operands: src 0x184 base 0x180 insns 97/96; --- replace mine 5:41 base 5:12; restored prior body.
- moveCursorDown__Q39textinput9inputform4BaseFv: lower row index declaration: src 0x184 base 0x180 insns 97/96; --- replace mine 5:41 base 5:12; restored prior body.
- updateCandidateState___Q39textinput9inputform4BaseFv: typed candidate refresh: src 0x228 base 0x1e4 insns 138/121; --- replace mine 9:10 base 9:10; restored prior body.
- updateCandidateState___Q39textinput9inputform4BaseFv: prediction buffer after suppress: src 0x228 base 0x1e4 insns 138/121; --- replace mine 9:10 base 9:10; restored prior body.
- updateCandidateState___Q39textinput9inputform4BaseFv: bottom-tested candidate loops: src 0x228 base 0x1e4 insns 138/121; --- replace mine 9:10 base 9:10; restored prior body.
- updateCandidateState___Q39textinput9inputform4BaseFv: qualified candidate caller methods: src 0x1e4 base 0x1e4 insns 121/121; diffs 0: []; retained exact C++.
- moveCursorUp__Q39textinput9inputform4BaseFv: upper boundary emitted first: src 0x158 base 0x160 insns 86/88; --- replace mine 47:48 base 47:48; restored prior body.
- moveCursorUp__Q39textinput9inputform4BaseFv: upper clamp ternary: src 0x160 base 0x160 insns 88/88; diffs 2: [58, 59]; restored prior body.
- moveCursorUp__Q39textinput9inputform4BaseFv: upper cached coordinate clamp: src 0x158 base 0x160 insns 86/88; --- replace mine 47:48 base 47:48; restored prior body.
- moveCursorDown__Q39textinput9inputform4BaseFv: lower boundary emitted first: src 0x180 base 0x180 insns 96/96; diffs 2: [67, 70]; restored prior body.
- getCurrentString__Q39textinput9inputform4BaseFb: boolean switch for Atok fix guard: src 0x1c4 base 0x1c0 insns 113/112; --- replace mine 11:12 base 11:12; restored prior body.
- moveCursorUp__Q39textinput9inputform4BaseFv: subtract line before virtual cursor setup: src 0x160 base 0x160 insns 88/88; diffs 3: [58, 59, 63]; restored prior body.
- moveCursorDown__Q39textinput9inputform4BaseFv: add line before virtual cursor setup: src 0x180 base 0x180 insns 96/96; diffs 0: []; retained exact C++.
- isVacancy__Q39textinput9inputform4BaseCFv: typed vacancy predicates: src 0x194 base 0x180 insns 101/96; --- replace mine 20:21 base 20:21; restored prior body.
- isVacancy__Q39textinput9inputform4BaseCFv: vacancy signed character comparison: src 0x194 base 0x180 insns 101/96; --- replace mine 20:21 base 20:21; restored prior body.
- isVacancy__Q39textinput9inputform4BaseCFv: vacancy positive mode branches: src 0x194 base 0x180 insns 101/96; --- replace mine 20:21 base 20:21; restored prior body.
- notifyChangeMode__Q39textinput9inputform4BaseFv: typed keyboard mode notification: src 0x1bc base 0x1b0 insns 111/108; --- replace mine 4:6 base 4:5; restored prior body.
- notifyChangeMode__Q39textinput9inputform4BaseFv: Korean predict mode ternary: src 0x1b0 base 0x1b0 insns 108/108; diffs 6: [85, 86, 87, 88, 89, 90]; restored prior body.
- notifyChangeMode__Q39textinput9inputform4BaseFv: mode notification switch: src 0x1c8 base 0x1b0 insns 114/108; --- replace mine 4:6 base 4:5; restored prior body.
- inputInputting___Q39textinput9inputform4BaseFw: typed inputting dispatch: src 0x280 base 0x284 insns 160/161; --- replace mine 10:11 base 10:11; restored prior body.
- inputInputting___Q39textinput9inputform4BaseFw: explicit alphabet input branch: src 0x280 base 0x284 insns 160/161; --- replace mine 10:11 base 10:11; restored prior body.
- inputInputting___Q39textinput9inputform4BaseFw: nonpositive prediction count: src 0x280 base 0x284 insns 160/161; --- replace mine 10:11 base 10:11; restored prior body.
- isVacancy__Q39textinput9inputform4BaseCFv: if-chain modes and combined selection flags: src 0x180 base 0x180 insns 96/96; diffs 0: []; retained exact C++.
- notifyChangeMode__Q39textinput9inputform4BaseFv: separate language assignment branches: src 0x1b0 base 0x1b0 insns 108/108; diffs 0: []; retained exact C++.
- inputInputting___Q39textinput9inputform4BaseFw: original range expression and alphabet-first branch: src 0x284 base 0x284 insns 161/161; diffs 0: []; retained exact C++.
- autoScroll__Q39textinput9inputform4BaseFv: typed automatic scrolling: src 0x260 base 0x258 insns 152/150; --- replace mine 0:1 base 0:1; restored prior body.
- autoScroll__Q39textinput9inputform4BaseFv: auto scroll separate vector assignment: src 0x268 base 0x258 insns 154/150; --- replace mine 0:1 base 0:1; restored prior body.
- autoScroll__Q39textinput9inputform4BaseFv: auto scroll scalar scale: src 0x268 base 0x258 insns 154/150; --- replace mine 0:1 base 0:1; restored prior body.
- create__Q39textinput9inputform10EditBufferFP12MEMAllocator: typed placement construction: src 0x220 base 0x214 insns 136/133; --- replace mine 14:16 base 14:15; restored prior body.
- create__Q39textinput9inputform10EditBufferFP12MEMAllocator: separate construction allocation temporaries: src 0x220 base 0x214 insns 136/133; --- replace mine 14:16 base 14:15; restored prior body.
- create__Q39textinput9inputform10EditBufferFP12MEMAllocator: implicit placement null checks: src 0x214 base 0x214 insns 133/133; diffs 0: []; retained exact C++.
- onPressLeft__Q39textinput9inputform4BaseFv: typed software left cursor: src 0x264 base 0x268 insns 153/154; --- replace mine 15:16 base 15:16; restored prior body.
- onPressLeft__Q39textinput9inputform4BaseFv: left positive motion branch: src 0x264 base 0x268 insns 153/154; --- replace mine 15:16 base 15:16; restored prior body.
- onPressLeft__Q39textinput9inputform4BaseFv: left positive prediction count: src 0x264 base 0x268 insns 153/154; --- replace mine 15:16 base 15:16; restored prior body.
- onPressRight__Q39textinput9inputform4BaseFv: typed software right cursor: src 0x308 base 0x2e4 insns 194/185; --- replace mine 0:1 base 0:1; restored prior body.
- onPressRight__Q39textinput9inputform4BaseFv: right nested space condition: src 0x308 base 0x2e4 insns 194/185; --- replace mine 0:1 base 0:1; restored prior body.
- onPressRight__Q39textinput9inputform4BaseFv: right space initialized fields: src 0x308 base 0x2e4 insns 194/185; --- replace mine 0:1 base 0:1; restored prior body.
- __ct__Q39textinput9inputform4BaseFPQ29textinput7Manager: typed input form constructor: src 0x218 base 0x210 insns 134/132; --- replace mine 6:7 base 6:7; restored prior body.
- __ct__Q39textinput9inputform4BaseFPQ29textinput7Manager: constructor body pointer assignments: src 0x218 base 0x210 insns 134/132; --- replace mine 6:7 base 6:7; restored prior body.
- __ct__Q39textinput9inputform4BaseFPQ29textinput7Manager: constructor explicit rectangle: src 0x218 base 0x210 insns 134/132; --- replace mine 6:7 base 6:7; restored prior body.
- __ct__Q39textinput9inputform4BaseFPQ29textinput7Manager: correct sender reset and packed color: src 0x210 base 0x210 insns 132/132; diffs 0: []; retained exact C++.
- init__Q49textinput9inputform4Base14RowInfoManagerFv: typed row sentinel initialization: src 0xbc base 0x9c insns 47/39; --- replace mine 16:18 base 16:21; restored prior body.
- init__Q49textinput9inputform4Base14RowInfoManagerFv: row sentinel pointer temporary: src 0xac base 0x9c insns 43/39; --- replace mine 12:13 base 12:13; restored prior body.
- init__Q49textinput9inputform4Base14RowInfoManagerFv: row unused sentinel pointer: src 0xb0 base 0x9c insns 44/39; --- replace mine 16:18 base 16:21; restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: typed base row allocation: compile failed (10412 illegal access from 'textinput::inputform::EditBuffer' to); restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: detached-row insertion guard: compile failed (10412 illegal access from 'textinput::inputform::EditBuffer' to); restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: reload row-list after removal: compile failed (10412 illegal access from 'textinput::inputform::EditBuffer' to); restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: typed base row allocation: compile failed (10412 illegal access from 'textinput::inputform::EditBuffer' to); restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: detached-row insertion guard: compile failed (10412 illegal access from 'textinput::inputform::EditBuffer' to); restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: reload row-list after removal: compile failed (10412 illegal access from 'textinput::inputform::EditBuffer' to); restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: typed base row allocation: src 0x114 base 0x120 insns 69/72; --- replace mine 27:28 base 27:60; restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: detached-row insertion guard: src 0x11c base 0x120 insns 71/72; --- replace mine 28:29 base 28:29; restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: reload row-list after removal: src 0x118 base 0x120 insns 70/72; --- replace mine 27:28 base 27:60; restored prior body.
- calc__Q39textinput9inputform4BaseFv: typed selection color animation: src 0x294 base 0x294 insns 165/165; diffs 13: [21, 53, 126, 127, 128, 129, 130, 131, 132, 151, 152, 153, 154]; restored prior body.
- calc__Q39textinput9inputform4BaseFv: color green before red assignment: src 0x294 base 0x294 insns 165/165; diffs 17: [21, 53, 78, 79, 82, 83, 126, 127, 128, 129, 130, 131, 132, 151, 152, 153, 154]; restored prior body.
- calc__Q39textinput9inputform4BaseFv: color time increment operand order: src 0x294 base 0x294 insns 165/165; diffs 12: [21, 53, 126, 127, 128, 129, 130, 131, 132, 152, 153, 154]; restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: typed URL prefix scan: compile failed (10248 function call '[textinput::inputform::Base].wcsnicmp({lval} const); restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: nested character range scan: compile failed (10248 function call '[textinput::inputform::Base].wcsnicmp({lval} const); restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: pointer iterator URL prefix scan: compile failed (10248 function call '[textinput::inputform::Base].wcsnicmp({lval} const); restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: typed URL prefix scan: src 0x190 base 0x1bc insns 100/111; --- insert mine 5:5 base 5:6; restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: nested character range scan: src 0x190 base 0x1bc insns 100/111; --- insert mine 5:5 base 5:6; restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: pointer iterator URL prefix scan: src 0x190 base 0x1bc insns 100/111; --- insert mine 5:5 base 5:6; restored prior body.
- drawCursor__Q39textinput9inputform4BaseFff: typed blinking cursor line: src 0x11c base 0x118 insns 71/70; --- insert mine 48:48 base 48:57; restored prior body.
- drawCursor__Q39textinput9inputform4BaseFff: cursor scalar opacity after coordinates: src 0x11c base 0x118 insns 71/70; --- insert mine 48:48 base 48:57; restored prior body.
- drawCursor__Q39textinput9inputform4BaseFff: cursor explicit alpha accumulator: src 0x11c base 0x118 insns 71/70; --- replace mine 34:35 base 34:35; restored prior body.
- isOverLine__Q39textinput9inputform4BaseFRCQ49textinput10textdrawer4Base8DrawInfo: typed line limit scales: src 0xdc base 0xcc insns 55/51; --- replace mine 0:1 base 0:1; restored prior body.
- isOverLine__Q39textinput9inputform4BaseFRCQ49textinput10textdrawer4Base8DrawInfo: line limit scalar scale: src 0xec base 0xcc insns 59/51; --- replace mine 0:1 base 0:1; restored prior body.
- isOverLine__Q39textinput9inputform4BaseFRCQ49textinput10textdrawer4Base8DrawInfo: line limit const vector references: src 0xdc base 0xcc insns 55/51; --- replace mine 0:1 base 0:1; restored prior body.
- isAtokActive__Q39textinput9inputform4BaseCFv: explicit Atok boolean assignment: src 0x30 base 0x28 insns 12/10; --- delete mine 2:5 base 2:2; restored prior body.
- isAtokActive__Q39textinput9inputform4BaseCFv: Atok boolean switch guard: src 0x28 base 0x28 insns 10/10; diffs 2: [1, 2]; restored prior body.
- isAtokActive__Q39textinput9inputform4BaseCFv: Atok integer guard: src 0x28 base 0x28 insns 10/10; diffs 0: []; retained exact C++.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: detached row guard with fresh list pointer: src 0x120 base 0x120 insns 72/72; diffs 26: [28, 30, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43, 44, 46, 49, 51, 53, 54, 55, 56]; restored prior body.
- drawCursor__Q39textinput9inputform4BaseFff: font height in line endpoint argument: src 0x118 base 0x118 insns 70/70; diffs 2: [59, 61]; restored prior body.
- onPressRightHWKB__Q39textinput9inputform4BaseFv: onPressRightHWKB integer zero switch: src 0x450 base 0x44c insns 276/275; --- replace mine 19:20 base 19:20; restored prior body.
- onPressRightHWKB__Q39textinput9inputform4BaseFv: onPressRightHWKB integer one switch: src 0x44c base 0x44c insns 275/275; diffs 2: [93, 94]; restored prior body.
- onPressRightHWKB__Q39textinput9inputform4BaseFv: onPressRightHWKB integer zero guard: src 0x448 base 0x44c insns 274/275; --- replace mine 19:20 base 19:20; restored prior body.
- onPressLeftHWKB__Q39textinput9inputform4BaseFv: onPressLeftHWKB integer zero switch: src 0x424 base 0x420 insns 265/264; --- replace mine 19:20 base 19:20; restored prior body.
- onPressLeftHWKB__Q39textinput9inputform4BaseFv: onPressLeftHWKB integer one switch: src 0x420 base 0x420 insns 264/264; diffs 2: [93, 94]; restored prior body.
- onPressLeftHWKB__Q39textinput9inputform4BaseFv: onPressLeftHWKB integer zero guard: src 0x41c base 0x420 insns 263/264; --- replace mine 19:20 base 19:20; restored prior body.
- onPressUp__Q39textinput9inputform4BaseFv: onPressUp integer zero switch: src 0x3dc base 0x3d8 insns 247/246; --- replace mine 11:12 base 11:12; restored prior body.
- onPressUp__Q39textinput9inputform4BaseFv: onPressUp integer one switch: src 0x3d8 base 0x3d8 insns 246/246; diffs 2: [199, 200]; restored prior body.
- onPressUp__Q39textinput9inputform4BaseFv: onPressUp integer zero guard: src 0x3d4 base 0x3d8 insns 245/246; --- replace mine 11:12 base 11:12; restored prior body.
- onPressDown__Q39textinput9inputform4BaseFv: onPressDown integer zero switch: src 0x3dc base 0x3d8 insns 247/246; --- replace mine 11:12 base 11:12; restored prior body.
- onPressDown__Q39textinput9inputform4BaseFv: onPressDown integer one switch: src 0x3d8 base 0x3d8 insns 246/246; diffs 2: [199, 200]; restored prior body.
- onPressDown__Q39textinput9inputform4BaseFv: onPressDown integer zero guard: src 0x3d4 base 0x3d8 insns 245/246; --- replace mine 11:12 base 11:12; restored prior body.
- calc__Q39textinput9inputform4BaseFv: real color phase and scrolling float assignment: compile failed (10140 undefined identifier 'sfColorPhase'); restored prior body.
- calc__Q39textinput9inputform4BaseFv: pulse query beside blue interpolation: compile failed (10140 undefined identifier 'sfColorPhase'); restored prior body.
- calc__Q39textinput9inputform4BaseFv: real color phase and scrolling float assignment: src 0x294 base 0x294 insns 165/165; diffs 11: [53, 126, 127, 128, 129, 130, 131, 132, 152, 153, 154]; restored prior body.
- calc__Q39textinput9inputform4BaseFv: pulse query beside blue interpolation: src 0x294 base 0x294 insns 165/165; diffs 8: [53, 126, 128, 129, 130, 152, 153, 154]; restored prior body.
- onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos: cursor centered width subtraction: compile failed (33026 <string not found>); restored prior body.
- onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos: cursor scale first multiplication: compile failed (33026 <string not found>); restored prior body.
- onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos: cursor half-width local: compile failed (33026 <string not found>); restored prior body.
- onPressDownHWKB__Q39textinput9inputform4BaseFv: down HWKB selected local scope: compile failed (33026 <string not found>); restored prior body.
- onPressDownHWKB__Q39textinput9inputform4BaseFv: down HWKB selected initial value: compile failed (33026 <string not found>); restored prior body.
- onPressDownHWKB__Q39textinput9inputform4BaseFv: down HWKB unsigned kana predicate: compile failed (33026 <string not found>); restored prior body.
- onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos: cursor centered width subtraction: src 0x764 base 0x764 insns 473/473; diffs 15: [265, 267, 268, 269, 271, 272, 273, 274, 275, 276, 277, 278, 280, 281, 283]; restored prior body.
- onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos: cursor scale first multiplication: src 0x764 base 0x764 insns 473/473; diffs 5: [271, 273, 276, 281, 283]; restored prior body.
- onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos: cursor half-width local: src 0x764 base 0x764 insns 473/473; diffs 17: [265, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 283]; restored prior body.
- onPressDownHWKB__Q39textinput9inputform4BaseFv: down HWKB selected local scope: src 0x428 base 0x438 insns 266/270; --- replace mine 16:17 base 16:17; restored prior body.
- onPressDownHWKB__Q39textinput9inputform4BaseFv: down HWKB selected initial value: src 0x428 base 0x438 insns 266/270; --- replace mine 16:17 base 16:17; restored prior body.
- onPressDownHWKB__Q39textinput9inputform4BaseFv: down HWKB unsigned kana predicate: src 0x428 base 0x438 insns 266/270; --- replace mine 16:17 base 16:17; restored prior body.
- onSpaceKeyHWKB__Q39textinput9inputform4BaseFUl: space-key prediction integer predicate: src 0x96c base 0x96c insns 603/603; diffs 7: [193, 194, 195, 196, 197, 198, 199]; restored prior body.
- onSpaceKeyHWKB__Q39textinput9inputform4BaseFUl: space-key prediction initialization: src 0x96c base 0x96c insns 603/603; diffs 7: [193, 194, 195, 196, 197, 198, 199]; restored prior body.
- onSpaceKeyHWKB__Q39textinput9inputform4BaseFUl: space-key positive prediction predicate: src 0x96c base 0x96c insns 603/603; diffs 11: [92, 93, 193, 194, 195, 196, 197, 198, 199, 410, 411]; restored prior body.
- setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language: language root query reference: src 0x3b8 base 0x3b4 insns 238/237; --- delete mine 52:53 base 52:52; restored prior body.
- setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language: language selected pane name temporary: src 0x3b4 base 0x3b4 insns 237/237; diffs 22: [57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 118, 119, 120, 121, 122, 123, 124, 125, 126]; restored prior body.
- setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language: language title pane declaration: src 0x3b4 base 0x3b4 insns 237/237; diffs 59: [57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 78, 79, 82, 83, 90, 91, 92, 95, 98]; restored prior body.
- create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: layout detached row insertion guard: src 0x5a0 base 0x590 insns 360/356; --- replace mine 5:6 base 5:6; restored prior body.
- create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: layout row list reload: src 0x594 base 0x590 insns 357/356; --- replace mine 5:6 base 5:6; restored prior body.
- create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: layout narrow button counter: src 0x590 base 0x590 insns 356/356; diffs 205: [5, 7, 8, 10, 14, 15, 16, 20, 22, 23, 25, 26, 28, 29, 30, 31, 32, 33, 34, 35]; restored prior body.
- calcCursorPos__Q39textinput9inputform4BaseFff: cursor position bottom-independent loop: src 0x518 base 0x518 insns 326/326; diffs 81: [28, 45, 49, 51, 58, 60, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 94]; restored prior body.
- calcCursorPos__Q39textinput9inputform4BaseFff: cursor position separate scale assignment: src 0x520 base 0x518 insns 328/326; --- replace mine 28:29 base 28:29; restored prior body.
- calcCursorPos__Q39textinput9inputform4BaseFff: cursor position string before scroll coordinate: src 0x51c base 0x518 insns 327/326; --- delete mine 22:23 base 22:22; restored prior body.
- isOverRowLimit__Q39textinput9inputform4BaseFUlPCw: row limit separate scale assignment: src 0x3b4 base 0x3b8 insns 237/238; --- replace mine 0:1 base 0:1; restored prior body.
- isOverRowLimit__Q39textinput9inputform4BaseFUlPCw: row limit defer scalar width: src 0x3b0 base 0x3b8 insns 236/238; --- replace mine 0:1 base 0:1; restored prior body.
- isOverRowLimit__Q39textinput9inputform4BaseFUlPCw: row limit glyph rectangle constructor: src 0x3c0 base 0x3b8 insns 240/238; --- replace mine 14:15 base 14:15; restored prior body.
- onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv: command fixed string predicate integer: src 0x2020 base 0x2014 insns 2056/2053; --- replace mine 0:1 base 0:1; restored prior body.
- onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv: command uncached fixed string comparison: src 0x2020 base 0x2014 insns 2056/2053; --- replace mine 0:1 base 0:1; restored prior body.
- onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv: command fixed string declaration after predicate: src 0x2020 base 0x2014 insns 2056/2053; --- replace mine 0:1 base 0:1; restored prior body.
- isEnableCursorCache__Q39textinput10textdrawer4BaseCFv: cache bool ternary: ; restored prior body.
- Cursor-cache cache bool ternary: 8/8 bytes; raw equal True. Original symbol remains malformed; no aliases/config changes.
- isEnableCursorCache__Q39textinput10textdrawer4BaseCFv: cache positive branch: ; restored prior body.
- Cursor-cache cache positive branch: 8/8 bytes; raw equal True. Original symbol remains malformed; no aliases/config changes.
- isEnableCursorCache__Q39textinput10textdrawer4BaseCFv: cache byte predicate: ; restored prior body.
- Cursor-cache cache byte predicate: 20/8 bytes; raw equal False. Original symbol remains malformed; no aliases/config changes.

## Third continuation handoff
- Converted 29 existing asm bodies instruction-exact to C++; 41 -> 12 remain. All twelve remaining asm bodies and every report-nonmatching function have at least three distinct compiled source-level attempts logged, including the cursor-cache raw-byte audit. Failed preliminary builds are recorded separately.
- Real data restored: UTF-16 URL prefix table uses ordinary wide literals; selection-color phase is an ordinary zero-initialized float replacing the inherited address-label extern. No explicit data placement was added. Pool remains identical, and .rodata/.sdata/.sdata2 remain 100%.
- Data experiment: deferring the real singleton inline definition moves its weak guard/object after the color storage, but also moves its destructor registrar behind the colors, changing seven initializer offsets. Restored the original singleton definition. Real color state occupies offsets 0x08..0x24 in the compiled .sbss because the guard/object occupy the first eight bytes; the extracted target lacks these deduplicated weak objects. No padding, force-active, section changes or symbol aliases were added.
- Weak Decolated and GUIComponent vtables appear after genuine constructors/init are restored. Their original deduplicated output is absent/zero-filled; extracted EditBuffer and textinput Base vtables also retain trailing zero gaps. Data is still incomplete. No linking-mode changes or DOL investigation.
- The gate's character-plus-0xcf65 review note concerns a wchar_t numeric range test, not a pointer into a string blob. It reproduces the target addis/addi and inclusive range comparison.
- Uncertain: the exact semantic name of WithZi's final flag at 0xa8, and some reconstructed drawer viewport/cache fields. Their offsets, sizes, zero initialization and instruction uses are verified; linking of weak data remains outside this phase.

### Remaining report-nonmatching functions
Base::onCommand, 88.05163%, stack frame, register allocation and case scheduling.
Base::onCursor, 99.915436%, five centered-space FP register/operand differences.
Base::calcCursorPos, 90.671776%, FP scheduling and register allocation.
Base::onPressUp, 99.55285%, one missing kana guard tail branch.
Base::onPressDown, 99.55285%, one missing kana guard tail branch.
Base::onPressDownHWKB, 98.35185%, candidate branches, index registers and trailing comparison.
Base::onPressLeftHWKB, 99.97727%, two kana comparison/polarity instructions.
Base::onPressRightHWKB, 99.97818%, two kana comparison/polarity instructions.
Base::onSpaceKeyHWKB, 99.32007%, seven Atok Boolean block-order instructions.
LayoutByNW4R::create, 88.91854%, row-list scheduling, registers and loops.
LayoutByNW4R::setLanguage, 96.44726%, 22 root-load scheduling differences.
Base::isOverRowLimit, 93.63866%, stack frame, FP scheduling and registers.
textdrawer::Base::isEnableCursorCache, None%, original report symbol concatenates getStartPos; actual 8 bytes are exact.

### Exact asm bodies still requiring C++
extern "C" asm void draw__Q39textinput9inputform12LayoutByNW4RFv(), objdiff 100%, 114/114 C++ instructions, twelve vector temporary offsets.
extern "C" asm bool findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl(), objdiff 100%, 100/111 C++ instructions, balanced character classification and registers.
extern "C" asm void autoScroll__Q39textinput9inputform4BaseFv(), objdiff 100%, 152/150 C++ instructions, frame and FP scheduling.
extern "C" asm void create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer(), objdiff 100%, 72/72 C++ instructions, 26 register differences.
extern "C" asm void getCurrentString__Q39textinput9inputform4BaseFb(), objdiff 100%, 111/112 C++ instructions, Atok guard tail branch.
extern "C" asm void moveCursorUp__Q39textinput9inputform4BaseFv(), objdiff 100%, 88/88 C++ instructions, two subtract/vtable scheduling differences.
extern "C" asm void onPressLeft__Q39textinput9inputform4BaseFv(), objdiff 100%, 153/154 C++ instructions, kana guard and Boolean block order.
extern "C" asm void onPressRight__Q39textinput9inputform4BaseFv(), objdiff 100%, 194/185 C++ instructions, space buffer copy and kana guard.
extern "C" asm void calc__Q39textinput9inputform4BaseFv(), objdiff 100%, 165/165 C++ instructions, eight FP/store scheduling differences.
extern "C" asm void init__Q49textinput9inputform4Base14RowInfoManagerFv(), objdiff 100%, 43/39 C++ instructions, sentinel pointer loads.
asm bool Base::isOverLine(const DrawInfo& drawInfo), objdiff 100%, 55/51 C++ instructions, vector temporary copies.
asm void Base::drawCursor(f32, f32), objdiff 100%, 70/70 C++ instructions, two linewidth result register differences.

### Final full gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiInputForm] pool: IDENTICAL
[src/keyboard/tiInputForm] objdiff: code 28300/50656 data 908/3772 functions 208/221 fuzzy 97.2205 linked code 0
[src/keyboard/tiInputForm] instruction-exact functions: 206/221
[src/keyboard/tiInputForm]   section .bss size 96 match None
[src/keyboard/tiInputForm]   section .ctors size 4 match 100.0
[src/keyboard/tiInputForm]   section .data size 2736 match 65.53332
[src/keyboard/tiInputForm]   section .rodata size 760 match 100.0
[src/keyboard/tiInputForm]   section .sbss size 32 match 33.333336
[src/keyboard/tiInputForm]   section .sdata size 40 match 100.0
[src/keyboard/tiInputForm]   section .sdata2 size 104 match 100.0
[src/keyboard/tiInputForm]   section .text size 50656 match 97.22054
[src/keyboard/tiInputForm]   below 100: onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv 88.05163
[src/keyboard/tiInputForm]   below 100: onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos 99.915436
[src/keyboard/tiInputForm]   below 100: calcCursorPos__Q39textinput9inputform4BaseFff 90.671776
[src/keyboard/tiInputForm]   below 100: onPressUp__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDown__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDownHWKB__Q39textinput9inputform4BaseFv 98.35185
[src/keyboard/tiInputForm]   below 100: onPressLeftHWKB__Q39textinput9inputform4BaseFv 99.97727
[src/keyboard/tiInputForm]   below 100: onPressRightHWKB__Q39textinput9inputform4BaseFv 99.97818
[src/keyboard/tiInputForm]   below 100: onSpaceKeyHWKB__Q39textinput9inputform4BaseFUl 99.32007
[src/keyboard/tiInputForm]   below 100: create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer 88.91854
[src/keyboard/tiInputForm]   below 100: setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language 96.44726
[src/keyboard/tiInputForm]   below 100: isOverRowLimit__Q39textinput9inputform4BaseFUlPCw 93.63866
[src/keyboard/tiInputForm]   below 100: isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv None
[src/keyboard/tiInputForm] baseline: code 28300/50656 data 908 functions 208 fuzzy 97.2205
regressions vs baseline: 0
global matched_code_percent: 72.81211 -> 72.81211
global fuzzy_match_percent: 82.03321 -> 82.03321
global complete_code_percent: 56.76068 -> 56.76068
global matched_data_percent: 86.27892 -> 86.27892
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: src/keyboard/tiInputForm.cpp: possible pointer+offset into a blob (orchestrator reviews) (+1 net), e.g. if (static_cast<u16>(character + 0xcf65) <= 1) {
GATE PASS
```

## Fourth continuation
- Baseline: 206/221 instruction-exact, 208/221 objdiff exact, code 28300/50656, data 908/3772; twelve exact asm bodies remain. Applying unslop to the attempt log and final handoff.
- onPressLeftHWKB__Q39textinput9inputform4BaseFv: signed kana direct zero guard: src 0x41c base 0x420 insns 263/264; --- replace mine 19:20 base 19:20; restored prior body.
- onPressLeftHWKB__Q39textinput9inputform4BaseFv: signed kana zero case switch: src 0x424 base 0x420 insns 265/264; --- replace mine 19:20 base 19:20; restored prior body.
- onPressLeftHWKB__Q39textinput9inputform4BaseFv: signed kana result local: src 0x41c base 0x420 insns 263/264; --- replace mine 19:20 base 19:20; restored prior body.
- onPressRightHWKB__Q39textinput9inputform4BaseFv: signed kana direct zero guard: src 0x448 base 0x44c insns 274/275; --- replace mine 19:20 base 19:20; restored prior body.
- onPressRightHWKB__Q39textinput9inputform4BaseFv: signed kana zero case switch: src 0x450 base 0x44c insns 276/275; --- replace mine 19:20 base 19:20; restored prior body.
- onPressRightHWKB__Q39textinput9inputform4BaseFv: signed kana result local: src 0x448 base 0x44c insns 274/275; --- replace mine 19:20 base 19:20; restored prior body.
- isOverLine__Q39textinput9inputform4BaseFRCQ49textinput10textdrawer4Base8DrawInfo: plain scale aggregates: src 0xdc base 0xcc insns 55/51; --- replace mine 0:1 base 0:1; restored prior body.
- isOverLine__Q39textinput9inputform4BaseFRCQ49textinput10textdrawer4Base8DrawInfo: scale assignment into declared vectors: src 0xec base 0xcc insns 59/51; --- replace mine 0:1 base 0:1; restored prior body.
- isOverLine__Q39textinput9inputform4BaseFRCQ49textinput10textdrawer4Base8DrawInfo: plain scale aggregates width first: src 0xdc base 0xcc insns 55/51; --- replace mine 0:1 base 0:1; restored prior body.
- draw__Q39textinput9inputform12LayoutByNW4RFv: clip declared before scale: src 0x1dc base 0x1c8 insns 119/114; --- insert mine 44:44 base 44:49; restored prior body.
- draw__Q39textinput9inputform12LayoutByNW4RFv: global declared before scale: src 0x1c8 base 0x1c8 insns 114/114; diffs 14: [50, 56, 59, 60, 63, 64, 65, 66, 67, 68, 69, 70, 73, 75]; restored prior body.
- draw__Q39textinput9inputform12LayoutByNW4RFv: plain global scale aggregates: src 0x1c8 base 0x1c8 insns 114/114; diffs 12: [50, 56, 59, 60, 63, 64, 65, 66, 67, 69, 73, 75]; restored prior body.
- drawCursor__Q39textinput9inputform4BaseFff: cursor direct byte thickness: src 0x118 base 0x118 insns 70/70; diffs 0: []; retained exact C++.
- Guarded signed isKanaFix return experiment: the callee stays 19/19 exact; HWKB direct zero guard loses one tail branch, zero-case switch adds one, result local loses one. Restored the original bool signature.
- moveCursorUp__Q39textinput9inputform4BaseFv: upper row coordinate compound subtract: src 0x160 base 0x160 insns 88/88; diffs 3: [58, 59, 63]; restored prior body.
- moveCursorUp__Q39textinput9inputform4BaseFv: upper row coordinate separate index: src 0x160 base 0x160 insns 88/88; diffs 0: []; retained exact C++.
- isOverLine__Q39textinput9inputform4BaseFRCQ49textinput10textdrawer4Base8DrawInfo: line direct scale expressions: src 0xc0 base 0xcc insns 48/51; --- delete mine 7:8 base 7:7; restored prior body.
- isOverLine__Q39textinput9inputform4BaseFRCQ49textinput10textdrawer4Base8DrawInfo: line intermediate field span: src 0xbc base 0xcc insns 47/51; --- replace mine 0:1 base 0:1; restored prior body.
- isOverLine__Q39textinput9inputform4BaseFRCQ49textinput10textdrawer4Base8DrawInfo: line direct width expressions: src 0xac base 0xcc insns 43/51; --- replace mine 0:1 base 0:1; restored prior body.
- getCurrentString__Q39textinput9inputform4BaseFb: current string prediction switch: src 0x1c0 base 0x1c0 insns 112/112; diffs 0: []; retained exact C++.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: URL switch with ASCII character classes: src 0x1b8 base 0x1bc insns 110/111; --- insert mine 5:5 base 5:6; restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: URL switch reordered letter cases: src 0x1b4 base 0x1bc insns 109/111; --- insert mine 5:5 base 5:6; restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: URL switch prefix pointer iteration: src 0x1b8 base 0x1bc insns 110/111; --- insert mine 5:5 base 5:6; restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: URL prefix table cached before scan: src 0x1bc base 0x1bc insns 111/111; diffs 20: [5, 9, 10, 11, 15, 57, 66, 73, 74, 76, 79, 80, 82, 88, 89, 91, 93, 95, 101, 102]; restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: URL cached prefix iterator: src 0x1bc base 0x1bc insns 111/111; diffs 36: [5, 9, 10, 11, 12, 13, 15, 53, 57, 58, 60, 62, 66, 69, 71, 73, 74, 75, 76, 77]; restored prior body.
- findURL__Q39textinput9inputform4BaseFPUlPUlPCwUlUl: URL length before word pointer declaration: src 0x1bc base 0x1bc insns 111/111; diffs 31: [5, 9, 10, 11, 12, 13, 15, 53, 57, 58, 60, 62, 66, 69, 71, 73, 75, 76, 79, 82]; restored prior body.
- onPressLeft__Q39textinput9inputform4BaseFv: left explicit kana cases: src 0x278 base 0x268 insns 158/154; --- replace mine 15:16 base 15:16; restored prior body.
- onPressLeft__Q39textinput9inputform4BaseFv: left kana guard in loop: src 0x26c base 0x268 insns 155/154; --- replace mine 15:16 base 15:16; restored prior body.
- onPressLeft__Q39textinput9inputform4BaseFv: left kana negative switch: src 0x274 base 0x268 insns 157/154; --- replace mine 15:16 base 15:16; restored prior body.
- onPressRight__Q39textinput9inputform4BaseFv: right aggregate space then clear: src 0x308 base 0x2e4 insns 194/185; --- replace mine 0:1 base 0:1; restored prior body.
- onPressRight__Q39textinput9inputform4BaseFv: right byte-copy ordinary wide literal: src 0x2cc base 0x2e4 insns 179/185; --- replace mine 15:16 base 15:16; restored prior body.
- onPressRight__Q39textinput9inputform4BaseFv: right initialized space pair: src 0x2cc base 0x2e4 insns 179/185; --- replace mine 15:16 base 15:16; restored prior body.
- autoScroll__Q39textinput9inputform4BaseFv: automatic scroll direct scale expression: src 0x26c base 0x258 insns 155/150; --- replace mine 0:1 base 0:1; restored prior body.
- autoScroll__Q39textinput9inputform4BaseFv: automatic scroll inline row conversion: src 0x26c base 0x258 insns 155/150; --- replace mine 0:1 base 0:1; restored prior body.
- autoScroll__Q39textinput9inputform4BaseFv: automatic scroll height-first scale expression: src 0x258 base 0x258 insns 150/150; diffs 25: [26, 50, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 118, 120, 122, 123, 124, 125, 126]; restored prior body.
- init__Q49textinput9inputform4Base14RowInfoManagerFv: row sentinel full-width index: src 0xbc base 0x9c insns 47/39; --- replace mine 1:3 base 1:2; restored prior body.
- init__Q49textinput9inputform4Base14RowInfoManagerFv: row end indices captured before stores: src 0xb8 base 0x9c insns 46/39; --- replace mine 12:13 base 12:13; restored prior body.
- init__Q49textinput9inputform4Base14RowInfoManagerFv: row sentinel pair reference: src 0xa0 base 0x9c insns 40/39; --- replace mine 12:13 base 12:13; restored prior body.
- init__Q49textinput9inputform4Base14RowInfoManagerFv: row end cached preceding index: src 0x9c base 0x9c insns 39/39; diffs 15: [12, 14, 16, 17, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29]; restored prior body.
- init__Q49textinput9inputform4Base14RowInfoManagerFv: row end pointer instead of reference: src 0x9c base 0x9c insns 39/39; diffs 15: [12, 14, 16, 17, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29]; restored prior body.
- init__Q49textinput9inputform4Base14RowInfoManagerFv: row end loop pair references: src 0x9c base 0x9c insns 39/39; diffs 15: [12, 14, 16, 17, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29]; restored prior body.
- calc__Q39textinput9inputform4BaseFv: color direct byte blue conversion: src 0x294 base 0x294 insns 165/165; diffs 8: [53, 126, 128, 129, 130, 152, 153, 154]; restored prior body.
- calc__Q39textinput9inputform4BaseFv: color timer and phase locals before updates: src 0x294 base 0x294 insns 165/165; diffs 6: [53, 126, 128, 129, 130, 155]; restored prior body.
- calc__Q39textinput9inputform4BaseFv: color direct byte channels: src 0x294 base 0x294 insns 165/165; diffs 8: [53, 126, 128, 129, 130, 152, 153, 154]; restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: base row selected reference: compile failed build/43U/src/src/keyboard && "/usr/bin/python3" tools/transform_dep.py build/43U/src/src/keyboard/tiInputForm.d build/43U/src/src/keyboard/tiInputForm.d ### mwcceppc.exe Compiler: #    File: src\keyboard\tiInputForm.cpp # ------------------------------------- #    1903:     u16 previous = selected.Back;  #   Error:                             ^^^^ #   (10141) expression syntax error #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. ; restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: base row detached state captured: src 0x120 base 0x120 insns 72/72; diffs 26: [28, 30, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43, 44, 46, 49, 51, 53, 54, 55, 56]; restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: base row next preceding index order: src 0x120 base 0x120 insns 72/72; diffs 26: [28, 30, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43, 44, 46, 49, 51, 53, 54, 55, 56]; restored prior body.
- onPressRight__Q39textinput9inputform4BaseFv: right string buffer aggregate: src 0x308 base 0x2e4 insns 194/185; --- replace mine 0:1 base 0:1; restored prior body.
- onPressRight__Q39textinput9inputform4BaseFv: right string buffer aggregate byte copy: src 0x328 base 0x2e4 insns 202/185; --- replace mine 0:1 base 0:1; restored prior body.
- onPressRight__Q39textinput9inputform4BaseFv: right string buffer whole literal byte copy: src 0x2d0 base 0x2e4 insns 180/185; --- replace mine 15:16 base 15:16; restored prior body.
- onSpaceKeyHWKB__Q39textinput9inputform4BaseFUl: space Atok integer enable guard: src 0x96c base 0x96c insns 603/603; diffs 0: []; retained exact C++.
- onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos: space marker scale final operand: src 0x764 base 0x764 insns 473/473; diffs 5: [271, 273, 276, 281, 283]; restored prior body.
- onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos: space marker factor after width locals: src 0x764 base 0x764 insns 473/473; diffs 9: [271, 273, 274, 275, 276, 277, 278, 281, 283]; restored prior body.
- onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos: space marker offset computed by compound steps: src 0x764 base 0x764 insns 473/473; diffs 17: [265, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 283]; restored prior body.
- onPressLeftHWKB__Q39textinput9inputform4BaseFv: onPressLeftHWKB kana false case before default: src 0x424 base 0x420 insns 265/264; --- replace mine 19:20 base 19:20; restored prior body.
- onPressLeftHWKB__Q39textinput9inputform4BaseFv: onPressLeftHWKB kana explicit false and true cases: src 0x430 base 0x420 insns 268/264; --- replace mine 19:20 base 19:20; restored prior body.
- onPressLeftHWKB__Q39textinput9inputform4BaseFv: onPressLeftHWKB kana conditional positive block: src 0x41c base 0x420 insns 263/264; --- replace mine 19:20 base 19:20; restored prior body.
- onPressRightHWKB__Q39textinput9inputform4BaseFv: onPressRightHWKB kana false case before default: src 0x450 base 0x44c insns 276/275; --- replace mine 19:20 base 19:20; restored prior body.
- onPressRightHWKB__Q39textinput9inputform4BaseFv: onPressRightHWKB kana explicit false and true cases: src 0x45c base 0x44c insns 279/275; --- replace mine 19:20 base 19:20; restored prior body.
- onPressRightHWKB__Q39textinput9inputform4BaseFv: onPressRightHWKB kana conditional positive block: src 0x448 base 0x44c insns 274/275; --- replace mine 19:20 base 19:20; restored prior body.
- onPressUp__Q39textinput9inputform4BaseFv: onPressUp kana false case before default: src 0x3dc base 0x3d8 insns 247/246; --- replace mine 11:12 base 11:12; restored prior body.
- onPressUp__Q39textinput9inputform4BaseFv: onPressUp kana explicit false and true cases: src 0x3e8 base 0x3d8 insns 250/246; --- replace mine 11:12 base 11:12; restored prior body.
- onPressUp__Q39textinput9inputform4BaseFv: onPressUp kana conditional positive block: src 0x3d4 base 0x3d8 insns 245/246; --- replace mine 11:12 base 11:12; restored prior body.
- onPressDown__Q39textinput9inputform4BaseFv: onPressDown kana false case before default: src 0x3dc base 0x3d8 insns 247/246; --- replace mine 11:12 base 11:12; restored prior body.
- onPressDown__Q39textinput9inputform4BaseFv: onPressDown kana explicit false and true cases: src 0x3e8 base 0x3d8 insns 250/246; --- replace mine 11:12 base 11:12; restored prior body.
- onPressDown__Q39textinput9inputform4BaseFv: onPressDown kana conditional positive block: src 0x3d4 base 0x3d8 insns 245/246; --- replace mine 11:12 base 11:12; restored prior body.
- onPressDownHWKB__Q39textinput9inputform4BaseFv: down HWKB candidate decrement narrow type: src 0x428 base 0x438 insns 266/270; --- replace mine 16:17 base 16:17; restored prior body.
- onPressDownHWKB__Q39textinput9inputform4BaseFv: down HWKB candidate count local: src 0x428 base 0x438 insns 266/270; --- replace mine 16:17 base 16:17; restored prior body.
- onPressDownHWKB__Q39textinput9inputform4BaseFv: down HWKB explicit kana switch: src 0x42c base 0x438 insns 267/270; --- replace mine 97:98 base 97:98; restored prior body.
- setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language: language text pane name before root query: src 0x3b4 base 0x3b4 insns 237/237; diffs 22: [57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 118, 119, 120, 121, 122, 123, 124, 125, 126]; restored prior body.
- setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language: language repeated title query direct cast: src 0x3b4 base 0x3b4 insns 237/237; diffs 59: [57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 78, 79, 82, 83, 90, 91, 92, 95, 98]; restored prior body.
- setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language: language selected name conditional assignment: src 0x3b4 base 0x3b4 insns 237/237; diffs 22: [57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 118, 119, 120, 121, 122, 123, 124, 125, 126]; restored prior body.
- create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: layout placement constructor implicit null check: src 0x584 base 0x590 insns 353/356; --- replace mine 5:6 base 5:6; restored prior body.
- create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: layout row previous index widened: src 0x590 base 0x590 insns 356/356; diffs 205: [5, 7, 8, 10, 14, 15, 16, 20, 22, 23, 25, 26, 28, 29, 30, 31, 32, 33, 34, 35]; restored prior body.
- create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: layout unused detached-state local, discarded: src 0x590 base 0x590 insns 356/356; diffs 205: [5, 7, 8, 10, 14, 15, 16, 20, 22, 23, 25, 26, 28, 29, 30, 31, 32, 33, 34, 35]; restored prior body.
- calcCursorPos__Q39textinput9inputform4BaseFff: cursor coordinate scale operands reversed: src 0x518 base 0x518 insns 326/326; diffs 81: [28, 45, 49, 51, 58, 60, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 94]; restored prior body.
- calcCursorPos__Q39textinput9inputform4BaseFff: cursor coordinate line bottom recomputed local: src 0x518 base 0x518 insns 326/326; diffs 81: [28, 45, 49, 51, 58, 60, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 94]; restored prior body.
- calcCursorPos__Q39textinput9inputform4BaseFff: cursor coordinate draw info brace initialization: src 0x548 base 0x518 insns 338/326; --- replace mine 0:1 base 0:1; restored prior body.
- isOverRowLimit__Q39textinput9inputform4BaseFUlPCw: row limit width from direct scale query: src 0x3a8 base 0x3b8 insns 234/238; --- replace mine 0:1 base 0:1; restored prior body.
- isOverRowLimit__Q39textinput9inputform4BaseFUlPCw: row limit current iterator const local: src 0x3b0 base 0x3b8 insns 236/238; --- replace mine 0:1 base 0:1; restored prior body.
- isOverRowLimit__Q39textinput9inputform4BaseFUlPCw: row limit field width operand reversed: src 0x3b0 base 0x3b8 insns 236/238; --- replace mine 0:1 base 0:1; restored prior body.
- onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv: command fixed comparison positive ternary: src 0x2020 base 0x2014 insns 2056/2053; --- replace mine 0:1 base 0:1; restored prior body.
- onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv: command active mode integer temporary: src 0x2020 base 0x2014 insns 2056/2053; --- replace mine 0:1 base 0:1; restored prior body.
- onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv: command fixed pointer query after current: src 0x2020 base 0x2014 insns 2056/2053; --- replace mine 0:1 base 0:1; restored prior body.
- create__Q39textinput9inputform4BaseFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: base row reference corrected declaration: src 0x120 base 0x120 insns 72/72; diffs 26: [28, 30, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43, 44, 46, 49, 51, 53, 54, 55, 56]; restored prior body.
- create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer: layout genuine detached-row guard: src 0x598 base 0x590 insns 358/356; --- replace mine 5:6 base 5:6; restored prior body.
- isEnableCursorCache__Q39textinput10textdrawer4BaseCFv: cache bool conditional return: 8/8 bytes, raw equality True; restored prior body. Original concatenated symbol remains unchanged.
- isEnableCursorCache__Q39textinput10textdrawer4BaseCFv: cache explicit positive branch: 8/8 bytes, raw equality True; restored prior body. Original concatenated symbol remains unchanged.
- isEnableCursorCache__Q39textinput10textdrawer4BaseCFv: cache nonzero integer predicate: 20/8 bytes, raw equality False; restored prior body. Original concatenated symbol remains unchanged.

### Fourth continuation handoff
- Three exact asm bodies converted to readable C++: getCurrentString 112/112, moveCursorUp 88/88, drawCursor 70/70. Remaining asm count is 12 -> 9. onSpaceKeyHWKB now matches 603/603, adding one instruction-exact function and 2412 exact code bytes.
- Prediction-mode switch preserves getCurrentString's original extra branch. Separating the upper-row coordinate and cursor index matches moveCursorUp's virtual-call scheduling. Direct u8 thickness conversion matches drawCursor's two integer registers. The integer prediction-enabled local preserves onSpaceKeyHWKB's original Boolean block order.
- Every remaining asm body has at least three fresh compiled source-level attempts this round. Every remaining report-nonmatching entry also has at least three fresh attempts. The malformed cursor-cache symbol was checked with three compiled implementations against its original eight bytes. Failed preliminary reference declarations were corrected and rebuilt before counting attempts.
- Data: UEJ/KOR visibility tables now use their actual u16 counts and pane-name arrays; all three language tables use their actual visibility/separator/text/title fields. Binary contents, relocations, token order and section sizes remain unchanged. Chinese visibility storage still has its inherited trailing word; this round adds no padding or objects.
- Fresh ELF audit: all main vtables through WithAtok retain the original offsets. Genuine Decolated/GUIComponent vtables occupy additional weak storage, whereas the extracted target omits these deduplicated objects. EditBuffer and textinput Base target vtable sizes include four and 28 trailing zero bytes. The singleton weak guard/object precede seven real colors, shifting their .sbss offsets by eight bytes. These differences remain unresolved without artificial data placement. No linking investigation or Matching status changes.
- The literal pool is identical, and .rodata/.sdata/.sdata2 remain 100%. .data retains jump-table target differences from unmatched code and weak vtable differences; .sbss is below 100%. Full data completion is still open.
- Uncertain: original spelling/types of some drawer fields, the intended source form of weak singleton/color storage, and the trailing Chinese visibility word. No shared headers are changed this round.

### Fourth continuation remaining report-nonmatching functions
Base::onPressLeftHWKB, 99.97727%, two kana comparison/branch-polarity instructions; direct guard loses a tail branch, explicit cases add instructions.
Base::onPressRightHWKB, 99.97818%, same two kana comparison/branch-polarity instructions.
Base::onCursor, 99.915436%, five centered-space FP register/operand differences; compound offset evaluation worsens scheduling.
Base::onPressUp, 99.55285%, missing kana tail branch; false/default switch adds one instruction, explicit cases add four.
Base::onPressDown, 99.55285%, same missing kana tail branch.
Base::onPressDownHWKB, 98.35185%, candidate index/branch scheduling and final comparison; three variants remain 266/270 or 267/270 instructions.
LayoutByNW4R::setLanguage, 96.44726%, 22 root-query scheduling differences; name local and ternary retain those differences, title local worsens allocation.
Base::isOverRowLimit, 93.63866%, stack frame and FP/register scheduling; direct scale removes four instructions, operand variants remain 236/238.
Base::calcCursorPos, 90.671776%, FP/register scheduling; two variants retain 326/326 with 81 differences, aggregate glyph initialization adds instructions.
LayoutByNW4R::create, 88.91854%, row-list allocation/register scheduling; narrow index unchanged, implicit placement constructor removes three instructions, detached guard adds two.
Base::onCommand, 88.05163%, frame, case scheduling and register allocation; three variants retain 2056/2053 instructions.
textdrawer::Base::isEnableCursorCache, None%, original report concatenates getStartPos; actual accessor remains eight exact bytes. No aliases or symbol edits.

### Fourth continuation remaining exact asm bodies
LayoutByNW4R::draw, 100%, closest C++ 114/114 with twelve vector temporary stack offsets.
Base::findURL, 100%, balanced ASCII switch and cached real prefix table produce 111/111; closest twenty register differences. Three later variants change allocation, without improving the closest result.
Base::autoScroll, 100%, direct height/scale expression produces 150/150; twenty-five FP and instruction scheduling differences.
Base::create(MEMAllocator*, EditBuffer*), 100%, typed detached-row guard and list reload produce 72/72; twenty-six register differences.
Base::onPressLeft, 100%, kana guard and prediction Boolean block order remain; fresh case/loop variants 158/154, 155/154, 157/154.
Base::onPressRight, 100%, wide space buffer uses halfword stores while target uses word copies; fresh ordinary aggregate/copy variants differ in counts and kana guard.
Base::calc, 100%, closest C++ 165/165 with six FP/store scheduling differences after genuine timer/phase locals.
Base::RowInfoManager::init, 100%, references and preceding-row index produce 39/39 with fifteen index-load/store scheduling/register differences.
Base::isOverLine, 100%, named vectors copy four extra words; expression variants reduce to 48/51, 47/51, 43/51 by changing scale/width scheduling.

### Fourth continuation final full gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiInputForm] pool: IDENTICAL
[src/keyboard/tiInputForm] objdiff: code 30712/50656 data 908/3772 functions 209/221 fuzzy 97.2529 linked code 0
[src/keyboard/tiInputForm] instruction-exact functions: 207/221
[src/keyboard/tiInputForm]   section .bss size 96 match None
[src/keyboard/tiInputForm]   section .ctors size 4 match 100.0
[src/keyboard/tiInputForm]   section .data size 2736 match 65.53332
[src/keyboard/tiInputForm]   section .rodata size 760 match 100.0
[src/keyboard/tiInputForm]   section .sbss size 32 match 33.333336
[src/keyboard/tiInputForm]   section .sdata size 40 match 100.0
[src/keyboard/tiInputForm]   section .sdata2 size 104 match 100.0
[src/keyboard/tiInputForm]   section .text size 50656 match 97.25292
[src/keyboard/tiInputForm]   below 100: onCommand__Q39textinput9inputform4BaseFQ39textinput15CommandReceiver13INPUT_COMMANDPv 88.05163
[src/keyboard/tiInputForm]   below 100: onCursor__Q39textinput9inputform4BaseFPQ49textinput10textdrawer4Base9CursorPos 99.915436
[src/keyboard/tiInputForm]   below 100: calcCursorPos__Q39textinput9inputform4BaseFff 90.671776
[src/keyboard/tiInputForm]   below 100: onPressUp__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDown__Q39textinput9inputform4BaseFv 99.55285
[src/keyboard/tiInputForm]   below 100: onPressDownHWKB__Q39textinput9inputform4BaseFv 98.35185
[src/keyboard/tiInputForm]   below 100: onPressLeftHWKB__Q39textinput9inputform4BaseFv 99.97727
[src/keyboard/tiInputForm]   below 100: onPressRightHWKB__Q39textinput9inputform4BaseFv 99.97818
[src/keyboard/tiInputForm]   below 100: create__Q39textinput9inputform12LayoutByNW4RFP12MEMAllocatorPQ39textinput9inputform10EditBuffer 88.91854
[src/keyboard/tiInputForm]   below 100: setLanguage__Q39textinput9inputform12LayoutByNW4RFQ29textinput8Language 96.44726
[src/keyboard/tiInputForm]   below 100: isOverRowLimit__Q39textinput9inputform4BaseFUlPCw 93.63866
[src/keyboard/tiInputForm]   below 100: isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv None
[src/keyboard/tiInputForm] baseline: code 28300/50656 data 908 functions 208 fuzzy 97.2205
regressions vs baseline: 0
global matched_code_percent: 73.53608 -> 73.61661
global fuzzy_match_percent: 82.99180 -> 82.99235
global complete_code_percent: 56.76068 -> 56.76068
global matched_data_percent: 86.39154 -> 86.39154
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

## w1011/struct2 probes (drawCursor/calcCursorPos)
- calcCursorPos (326 insns): already byte-identical modulo branch targets — report fuzzy 91.59 was reloc-scoring, no real residual.
- drawCursor (70v70): eval-order tie. Base completes `opacity = f32(muGlobalAlpha)/255.0f` fsubs+fdivs BEFORE loading GXColor R/G/B bytes; mine hoists the lbz loads above the fdivs. Moving `GXColor color` decl later regressed 68v70 (splits the loads differently). Kept baseline form; documented sched-order tie.

## struct2 wave 3 — extern "C" const architecture decoded

MWCC const-fold vs SDA rule for `extern "C" const` objects:
- Source ref folds to anonymous @NNNN pool object when the DEF (with init) is
  VISIBLE at the use. Ref emits named SDA only when use sees extern decl and
  def is later (defs at EOF + decls up top) => all value-uses named.
- Generated conversion magics (u32/s32->f32/f64) dedup into same-valued named
  objects INCONSISTENTLY (autoScroll signed conv deduped to
  scInputFormF32ConvertMagic; init + drawCursor unsigned convs did NOT) —
  appears tied to .sdata2 emission order (anon pools emit in fn order; defs
  at EOF emit last). Unresolved: how orig got every generated magic named.
- .sdata2 layout = emission order = DEF ORDER when defs precede fns.
  Base order: ZeroF,640F,F32ConvertMagic(8B),OneF,HalfF,DegToFIdxF,150F,30F,
  50F,10F,52F,TwoF,140F,90F,253F,20F,ColorR/G/B/A u8s,255F,127F,14592F,
  [4B pad],F64ConvertMagic(8B),15F,[pad] — copied verbatim to EOF def block.
- ALL inline float literals in the file's fn bodies were swapped to named
  refs (150F/30F/50F/10F/52F/140F/90F/253F/20F/15F/640F/255F/127F/14592F/
  DegToFIdxF/OneF/HalfF/TwoF/ZeroF + Color*u8). Mass .sdata2 184->124B.
- Out-of-namespace uses (fns defined qualified-style at global scope) need
  textinput::inputform:: qualification (~97 sites).
- drawCursor: plain static_cast<f32>(u8/u32) emits the right
  lis/lbz/stw/stw/lfd/fsubs seq; residual = magic operand @NNNN vs named +
  eval-order (~11 diff lines). Union-pun form (u32[2]+f64, subtract named
  magic) gives named operand but fsub+frsp instead of fsubs — WORSE.
- autoScroll: orig used `* scInputFormHalfF` not `/ scInputFormTwoF`.
- textdrawer::Base() header ctor literals (mfVIWidth 640 etc) — named-const
  via header gate tried+reverted (orig likely defines ctor in cpp; also
  regressed sdata2). ctor anon pair {0,640} + GetTextColor {ffffff00,0}
  remain anonymous.
- REMAINING: init @13881 (signed magic dedup didn't fire), ctor pair,
  GetTextColor pair, drawCursor operand/scheduling, then 'create'.

Post-rebase states: Base::create(73i) normalized-identical (branch-target
artifacts only). LayoutByNW4R::create(357i) residual = callee-web rotation
(mine r20/r21/r28 vs base r23/r24/r30) + anonymous 0-operand pools; pure
coloring. Unit fuzzy 99.54, data 100.
