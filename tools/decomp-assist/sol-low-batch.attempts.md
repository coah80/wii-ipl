# Setting and SDK batch

All units remain NonMatching. No shared header or configure.py changes.

## USBAPThread::Init

1. Nested current-thread priority expression: 32/32 instructions, two li instructions swapped.
2. Separate priority temporary: unchanged.
3. Pointer, integer, and Boolean argument declarations: unchanged. Retained pointer parameters and the priority temporary.

## USBAP::DoRegistration

1. WDScanParam plus a local typed SSID pointer: 160/161 instructions and larger frame.
2. A typed scan structure and corrected response flags: 161/161, 48 differences.
3. Shared function exit for cancellation and initial failure: 161/161, 35 differences, mostly register assignments.

## SensitivityDrawing::draw

1. Independent GetWidth/GetHeight expressions: 278/278, 39 differences.
2. Width/height temporaries: 15 differences.
3. Explicit dimensions in the texture section: 11 differences.
4. Direct GXSetScissor arguments: removed the integer register permutation.
5. Four dimension and scale declaration variants: best seven differences.
6. Horizontal scale computed before vertical scale: one operand-order difference.
7. Division by 1024 rather than multiplication by its reciprocal: zero instruction differences. Corrected the vertical offset constant to -45 after examining the target constant bytes. Code is exact; the constant pool still differs.

## RakuRakuThread

Constructor, destructor, callback, destroy, Run, getState, four allocator callbacks, cancel, and printInfo reached exact instructions in the separate-global implementation. The additional progressCallback adapts the recovered member callback to the ATERM callback signature. That recovered signature needs parent review.

### start

1. Separate allocator, status, and queue globals: 97/96 instructions.
2. A domain context containing those fields: 96/96, 30 differences; changed previously exact functions through relocation offsets.
3. An explicit context pointer before the active check: 96/96, one mr versus addi difference, but worsened other owned functions. Restored the separate globals to preserve 12 exact functions.

### finish

1. Separate globals and early state rejection: 136/133 instructions.
2. Signed state and unsigned state-range check: removed branch differences.
3. Domain context and nested success branch: 133/133, 115 differences.
4. Context pointer, out-of-line printInfo and delayed configuration pointer: 132/133, allocation and address-generation differences. Restored separate globals and retained the signed security field and out-of-line printInfo.

## AOSSLink

Twelve functions have exact instructions. Swapping the alarm message/storage declaration order fixed AOSS_813FD18C.

### AOSSi_WLANGetBSSList

1. Structured access-point output and while retry loops: 227/227, 186 differences.
2. Startup label, retry increment ordering and aligned scan variables: 227/227, 186 differences; larger frame.
3. Cleanup/unlock labels and ordinary scan/mac locals: 227/227, 202 differences. Corrected the access-point layout with its real privacy field, restoring the 84-byte record size. Remaining differences involve stack placement, loop scheduling and register allocation.

### AOSSi_WLANConnect

1. Direct global configuration fields: 162/155 instructions.
2. Typed interface/IP pointers: 154/155 instructions.
3. Separate cancellation and timeout branches, pre-sleep retry increment: 156/155 instructions. Remaining differences involve pointer lifetime, control flow and register allocation.

## nup_mem::__nupRegisterAllocator

The three allocation/free functions match exactly; allocator registration remains open.

1. Two heap-magic checks in the non-null branch: 17/19 instructions; compiler removes two repeated loads.
2. Explicit heap pointer and validity Boolean: unchanged.
3. Separate null-aware registration branch: 21/19 instructions with two extra null-check instructions. Restored the first version.

## kbd_lib_map_us

Restored the eight ordinary key/modifier tables as u16 arrays and four region registrations. Code and data match 100 percent.

## kpr_lib

Seven functions have exact instructions after using a byte for the initialization guard.

### KPRProcessAltKeypad

1. Shared normalized and converted value plus while shift loop: 96/96, 28 differences.
2. Separate accumulator and translated value, digit subtraction before multiplication: 96/96, 25 differences.
3. For-form insertion shift loop: unchanged. Kept the readable for loop. Remaining differences are register assignments.

### KPRProcessDeadKeys

1. Initialized fallback indices, second-character temporary: 89/90 instructions.
2. Initialize fallbacks after the single-character case and load the second character inside the matching condition: 91/90.
3. A moving mapping pointer: 91/90 with more register differences. Restored variant two. The original reads an unset fallback register on invalid input; this source deliberately initializes that fallback rather than adding an uninitialized value to obtain a match.

The continuation below attempts the eleven previously skipped units.

## Continuation at dcc384b7

vi/i2c, sendSlaveAddr and __VISendI2CData:
1. Inlined clock/data/delay helpers, signed flags and combined ACK condition: 236/237 and 371/372 instructions; initial data polarity and ACK shifts differed.
2. Correct initial polarity, unsigned flags and explicit ACK bit shift: same counts; only ACK flag reuse and its dependent branches remain.
3. Nested ACK condition: same counts and differences.
4. Expanded data helper into source blocks: same counts and differences; restored readable helper.
5. Signed flag with unsigned ACK comparison: same counts; original reloads the flag after GPIO sampling, compiler retains it. No artificial volatile/barrier added. Pools identical; data 16/16.

nup/nup_nhttp:
- BufFull: direct nested translation 94/97; invert limit branch and use explicit valid-request branch 94/97; nested overflow test 94/97. Residual redundant branches, comparison orientation and error-zero store.
- Op: direct cleanup-label translation 341/348; correct NHTTPCreateRequestEx to ten actual arguments and preserve OpString call 339/348; reorder status/state declarations 339/348, stack locals and register/control-flow differences remain. Pool identical.
- StringFlush: direct growth calculation 55/56; invert capacity/growth comparisons 55/56; reverse sum operand order 55/56, extra target branch and registers remain.
- OpString: direct else produced 55/56; preserve call with NO_INLINE; separate error if gives 56/56 exact. GetFull and PostFull also exact after preserving the call. BufFree, ReqDone and GetIncr exact.

axfx/AXFXChorusExp:
- Init and Settings: inline shutdown helper initially swapped saved mask/counter; change shutdown declaration order fixes Init; OR-before-AND active bits fixes Settings, both exact. GetMemSize exact; the declaration change leaves Shutdown with a register permutation.
- Callback: direct three-channel implementation 216/216, 78 differences; reverse array declarations and unsigned distance shift 216/216, 70 differences; unsigned distance variable 216/216, same remaining allocation/scheduling differences.
- InitParams: direct formulas 126/126, 56 differences; invert depth comparison and initialize LFO state before conversion formulas 126/126, 55 differences; explicit rateStep temporary leaves floating scheduling/register differences. No data placement: ordinary literal constants yield all 48 data bytes exact.
- CalcLFO: signed 64-bit shift 51/65; explicit high/low shift expression 51/65; union product words 57/65 adds stack stores, worse; restore scalar product, invert phase branch and derive table index from masked phase 51/65. Target uses generic signed multiply corrections; ours uses mulhw. All real algorithms retained.

## eZiText continuation

All eight expected source paths were absent and have now been implemented. These units use the existing unoptimized compiler settings. The following are distinct source experiments, not exact-match claims.

zoemdata:
- MatchOEMdata: structured early returns produced 196/192 instructions; decrement the capacity parameter rather than a maximum temporary produced 194/192; share the no-match exit produced 189/192. Pointer-zero comparisons retained that count. Remaining stack, register and branch differences. Attach and Detach exact after inverting the detach rejection condition.

zidawg1:
- GetChild: u16 header and separate offset expression 68/68; u32 header with combined offset 65/68; restore u16 and reorder long offset 68/68, 93.29 percent.
- GetSibling: u16 header and zero-bit outer branch 127/131; u32 header changed masks and reduced instructions; restore u16 and reverse outer cases 127/131, 81.58 percent.
- GetCHAR: combined attributes 59/60; reverse key/attribute declarations and mask 60/60; sequential OR/add 60/60, 95.5 percent, remaining registers.
- GetGraphInfo: original field translation 134/134; reorder declarations 134/134; typed context and combined pair shift 134/134, 80.77 percent, remaining stack/register differences.
- EOW: nonzero expression, explicit repeated mask and local mask differed; positive mask test exact. Graph: direct offset, local table and reordered table variants differed; addition grouped with the table base exact.

ziswordw:
- IsWordW: aggregate search initialization and packed byte fields introduced a frame pointer; explicit six-word initialization removed aggregate copying; move the unmatched counter to function scope produced 423/416, 71.03 percent. Removed an unused seventh search-state field after checking the original six initialized words; the final full gate gives 71.08414 percent. Default format array corrected to the original ordinary eight bytes.
- ConvertUC2UserKey: initial pointer/character tests 88/91; zero-pointer tests and explicit halfword character casts 89/91; inclusive key bounds 89/91, 97.69 percent. Remaining branches/registers.

zi8pud2:
- SetPDremoveOpt: initialized byte previous option 21/21; separate declaration/assignment unchanged; word previous option added a return mask. Restored byte, 98.57 percent, saved-register assignment differs.
- MatchPUDdata_ZHS: direct typed dictionary traversal 72.45 percent; split normalization and reverse threshold branch 72.16 percent; word return type with explicit final byte-length conversion removes an implicit caller mask. Remaining control-flow and register differences.
- MatchPUDdata: byte return with early exit 52/50; break and next-dictionary block 53/50; word return and function-scope locals 53/50; assignment condition instead of next-dictionary temporary 52/50. Remaining redundant branches and masks.
- Phonetic helper: positive branch, negative branch and word return type; final exact. Word-size helper: combined loop, explicit inner test, function-scope cursor and for initialization; final exact. Copy helper: divided index, shifted index, typed cursor and positive size branch; final exact. Dictionary-length helper exact.

zconvert:
- UC2WC: native dynamic halfword fields 101/124; serialized byte fields and reversed default branch 123/124; capture default unicode pointer before error call 124/124, 99.68 percent. Remaining cyclic saved-register assignment.
- WC2UC: native dynamic fields and pointer-entry default test 179/199; byte fields and branch inversion 201/199; recovered default header address check and range snapshot 189/199, 77.70 percent. Remaining control flow and scheduling.
- UC2Key: initial dynamic fields 186/207; serialized fields and branch inversion 207/207; recovered default header address and captured range pointer 200/207, 83.90 percent. Original empty default header exists even when its entries pointer is zero.
- WC2Key: temporary conversion added instructions; nested conversion call gives 22/22 exact. All conversion tables are ordinary typed zero initializers.

zmtkey:
- GetKeyLayout: byte tables and halfword count 182/182, four differences; word count eliminates sth but introduces stw/mask and regresses two exact functions; reuse the character count retains four differences. Restored the halfword-count version and all three exact functions. Remaining count storage/register choice.

zi8uwd:
- Attach: early rejection and combined comparison loop 116/116, 90.47 percent; reordered position, bounded length and explicit inner break 117/116; split insertion counter updates 117/116, 97.24 percent. Remaining extra comparison and saved registers.
- MatchUWDdata: typed ring traversal 61.84 percent; capture visited index before filtering and reverse fallback 60.95 percent; segment endpoint conditional in ring loop remains 60.95 percent. Remaining shared-return control flow and stack/register differences.
- Pop: zero-first branch differed; reverse count branch exact. Clear: byte memset fill added mask; word fill exact.

zprepare:
- PrepareMatch: typed request/match translation 1062/940, 58 percent, missing switch table; word memset argument, native component stores and wildcard loop with break 1047/940; explicit dense gap cases and word computational nibble count 1019/940, 64.76 percent. Compiler now emits the ordinary 48-byte switch table. Remaining stack, loop, branch and register differences.

## Fresh attempts on the first eight units

USBAPThread::Init:
1. Unsigned priority: 32/32, the same two immediate-load differences.
2. Separate current-thread pointer and priority increment: unchanged.
3. Named null callback argument: unchanged. Restored the existing source, 99.6875 percent.

USBAP::DoRegistration:
1. Declare failed before found: 161/161, 35 differences.
2. Use the existing registered pointer for insertion: 159/161.
3. While-form address lookup: 161/161, 35 differences. Restored the existing source, 98.72671 percent; remaining registers and scheduling.

SensitivityDrawing::draw constant data:
1. Move background initialization after scales: 278/278, 41 differences; colors still precede floating constants.
2. Compute both texture scales once from the projection before background: 277/278, floats partly reorder but colors still first.
3. Compute horizontal texture scale first: 277/278 and different float ordering. Restored exact instructions; the original 56-byte constant section still differs from the compiler's 48-byte section. No placement objects added.

RakuRakuThread::start:
1. Declare socket config before interrupt mask: 97/96.
2. Explicit progress pointer: 97/96.
3. Separate thread and priority locals: 97/96. Restored existing source, 88.635414 percent; additional global address generation remains.

RakuRakuThread::finish:
1. Direct terminal-state tests: 138/133.
2. Unsigned key-loop counters: 135/133.
3. Advance typed WEP source pointers: 133/133, 116 differences, 81.1203 percent. Restored the better existing 86.56391 percent source; global address generation and register allocation remain.

AOSSi_WLANGetBSSList:
1. Reverse scan/info declaration order: 227/227, 202 differences.
2. Separate retry increment from comparison: unchanged.
3. Traverse rates using a typed rate pointer: initially rejected for a C89 declaration after statements; moving it to the block declarations gives 225/227. Restored the existing 81.14978 percent source, with stack/register and scheduling differences.

AOSSi_WLANConnect:
1. Declare result before retries: 156/155.
2. Reuse interface pointer for NCDSetIfConfig: 155/155, 98 differences, 95.090324 percent.
3. Combine cancellation and timeout rejection: 154/155. Restored existing 96.12258 percent source; pointer lifetimes and branches remain.

nup_mem::__nupRegisterAllocator:
1. Early null return: 17/19.
2. Positive validity branch: 19/19, 14 differences; compiler emits a Boolean value rather than repeated magic loads.
3. Typed heap and early invalid return: 14/19. Restored existing 89.47369 percent source; target repeats the magic load that this compiler removes.

KPRProcessAltKeypad:
1. Leading flag before accumulator: 96/96, 15 differences, improves from 25.
2. Explicit digit temporary: initially rejected for C89 declaration placement; function-block declaration gives 96/96, 25 differences.
3. While insertion loop: 96/96, 25 differences.
4. Derive high flag after masking through a raw value: 96/96, 25 differences.
5. Declare insertion pointer before index: 96/96, seven differences, 99.635414 percent; retained with the leading-flag variation.
6. Combine raw mask ordering with insertion ordering: 96/96, 21 differences. Remaining seven differences are register assignments.

KPRProcessDeadKeys:
1. Initialize fallback declarations before single-character branch: 92/90.
2. Capture the second character per iteration: 88/90.
3. Typed current mapping entry: 87/90. Restored existing 97.388885 percent source, with its safe fallback initialization and one extra instruction. No uninitialized matching trick introduced.

kbd_lib_map_us has no non-exact functions; its one function and all 3240 data bytes remain exact.

AXFXChorusExpShutdown additional attempts:
1. Signed channel index: 36/36, five register differences.
2. Clear via a typed channel pointer: 36/36, same five differences.
3. Explicit null/free branches: 38/36. Restored the variant that preserves exact Init and Settings; Shutdown remains 99.166664 percent.

All nineteen requested units now have implementations and measured attempts. Remaining functions and data are partial matches, not completion.
