# tiHKBManager attempts

Baseline: no source, 0/29 instruction-exact functions and 0/6116 code bytes.
The pool is empty and identical from the first object build. All fields and
calls use typed keyboard declarations. Only TIHKBMANAGER_IMPLEMENTATION selects
the added layouts; existing keyboard guard branches remain unchanged.

## Remaining functions, in object order

### SetLedCB
1. Initialized pointer union followed by device byte: 41/41 instructions,
   six differences in stack offsets and store scheduling.
2. Typed LED request containing the device and LED mask, using its mask as
   the asynchronous call argument: 42/41, one extra load and mask conversion.
3. Snapshot the request mask before disabling interrupts: 42/41, unchanged.
4. Make the snapshot const: 42/41, unchanged. Retained this readable request.
   A literal mask enum reached 41/41 with zero differences, but left the
   request's mask unused; that experiment was discarded.

### KBDListenerOwn::OnAttach
1. Pointer union initialized to zero: 59/61 instructions; saved-register
   allocation and callback stores differed.
2. LED request and mask argument: 60/61; allocation still differed.
3. Declare owner/device outside the branch: request with a literal mask
   reached 61/61 and zero differences.
4. Read the actual request mask into a local, then make that local const:
   both 62/61, an extra load and mask conversion. Retained the const snapshot
   so both request fields have a real use.

### KBDListenerOwn::OnDetach
1. Owner alias and typed Clear helper: 22/22, four register differences.
2. Declare a state pointer before clearing attached: 22/22, same four.
3. Access manager directly twice: 23/22, an additional owner load.
4. State reference before owner declaration: 22/22, six differences.
5. Owner declared before device: 22/22, six differences. Retained attempt 1.

### HKBManager::Update
1. Zero-initialized pointer union: 55/55, two callback-store differences.
2. Typed LED request used by the asynchronous call: 55/55, one argument
   conversion difference.
3. Literal LED mask enum: 55/55, zero differences, but unused request mask.
4. Snapshot the request mask, then make it const: 55/55, one conversion
   difference. Retained the const snapshot with both request fields used.

### KeyState_::Update
1. Explicit groups of two event/repeat slots: 183/183, 63 differences.
2. Ordinary loops over eight slots: 183/183, 51 differences.
3. Snapshot held keys before clearing triggers: 183/183, 47 differences.
4. Hoist shared bit/index declarations: 183/183, unchanged.
5. Cache previous/current array pointers: 247/183, rejected.
6. Reverse bit/index declaration order: 183/183, 44 differences, retained.
   Registers and repeat-array address calculation still differ.

### KeyState_::UpdateModState_
1. Loop counter before old modifier snapshot: 104/104, seven differences.
2. Move old modifier snapshot before counter: 104/104, ten differences.
3. Use a byte slot index: 104/104, seven differences.
4. Separate slot/key-mask declarations and assignments: 104/104, unchanged.
5. Scope the counter inside for: 104/104, ten differences. Retained attempt 4.

### KeySet::GetWChar
1. Original nested descending range tests: 70/77 instructions.
2. Ascending range branches, u32 virtual-code return, direct whitelist
   indexing and early exits: 74/77.
3. Signed code temporary: 82/77, rejected.
4. Separate u16 character for the private-code mask: 75/77, retained.
5. Inline range predicate accepting u16: 89/77, rejected.
   The retained version lacks two repeated narrowing instructions and uses
   different whitelist-loop registers.

### KeySet::IsValid
1. Direct guard/switch with owner alias: 70/70, 18 register differences.
2. Hoist index/device declarations before owner: 70/70, 12 differences.
3. Reverse those declaration positions: 70/70, unchanged.
4. Widen index/device temporaries: 70/70, 14 differences.
5. Inline the same CheckValidity helper used by GetKey/GetVCode:
   70/70, 12 differences, retained. Index/device registers are exchanged.

## Exact functions

All other functions are C++ and instruction-exact. Important successful
changes: sequential Clear stores; callback traversal compares its next node
with the owning listener; a polymorphic listener base initializes its links
before the derived vtable; NotifyEvent shares its loop index outside both
branches; SetModifierState computes its comparison before changing the field
and compares new locks against old locks; KeySet uses typed validity and
separate switch cases; GetVCode declares the second modifier mask before its
state value. The constructor uses the compiler
never_inline attribute so static initialization calls the real constructor.
Both the constructor and its static initializer are exact. A scoped pragma
experiment was rejected by the source gate and removed. Changing the
constructor loop to do/while produced 35/45 constructor and 43/18 initializer
instructions; the ordinary for loop was restored.

## Data and files

The singleton and compiler-generated destructor registration supply .bss.
The compiler supplies the constructor entry and listener vtable. No literal
pool, pinned addresses, hand-built vtable, or forced sections are added.
A weak abstract listener-base vtable is also compiler-generated.

Changed files:
- src/keyboard/tiHKBManager.cpp
- include/keyboard/tiHKBManager.h
- libs/RVL_SDK/include/revolution/kbd.h
- tools/decomp-assist/tiHKBManager.attempts.md
