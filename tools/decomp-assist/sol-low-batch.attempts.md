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

Not attempted: vi/i2c, nup/nup_nhttp, axfx/AXFXChorusExp, and all eight requested eZiText units. This is a partial batch, not completion.
