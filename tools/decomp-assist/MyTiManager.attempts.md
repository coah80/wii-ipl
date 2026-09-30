# MyTiManager matching attempts

Baseline: 84/91 instruction-exact functions, 12748/20196 code bytes,
20/1132 reported data bytes. Existing pool was identical.

## reflectSaveData

1. Branch directly on revision one: six instructions versus eight.
2. Switch with revision one and a default call: seven versus eight.
3. Separate revision-zero/default calls: eleven versus eight.
4. Revision-zero break followed by the shared default call: eight/eight,
   zero instruction differences.

## DispMemoState::start

1. Reconstructed pane translations and alpha assignments using VEC3 and
   byte conversion: 321/326 instructions.
2. VEC2 translations and an integer alpha helper: 325/326.
3. Corrected toolbar pane accessor order under the private header guard,
   and used the configuration switch: 326/326, zero differences.

## EditMemoState::start

1. Full initialization with VEC3 and direct byte conversion: 381/385.
2. VEC2 and integer alpha helper: 385/385, four accessor-slot differences.
3. Corrected the toolbar accessor declarations in the private guard:
   385/385, zero differences.

## AppearMemoState::calc

1. Reconstructed interpolation, pane movement, alpha and scrolling:
   437/428. Background movement, toolbar alpha and configuration branches
   differed from the target.
2. Kept the background stationary, used the configuration switch and removed
   the extra toolbar alpha assignment: 428/428, one accessor-slot difference.
3. Applied alpha to the upper toolbar pane: 428/428, zero differences.

## EditMemoState::updateInput

1. Restored common input processing and candidate-dependent pointer handling.
   Infinity is computed with ordinary floating arithmetic. 306/309;
   caching the prediction dialog removed the repeated virtual getter.
2. Repeated the prediction getter as the target does: 309/309, two register
   differences in the combined return value.
3. Reused the keyboard-handled local for the combined result:
   309/309, zero differences.

## DisappearMemoState::calc

1. Restored animation interpolation and pane assignments: 370/342.
2. Kept the background stationary, used the configuration switch and removed
   the scrolling operation absent from the target: 342/342, zero differences.

## Static initialization and data

1. Corrected DisappearMemoState to inherit AppearMemoState and its timer,
   and made State's abstract operations pure under the private guard:
   63/64 initializer instructions; the derived table now inherits the correct
   appearance operations.
2. Explicit background base construction and moving base function definitions
   earlier did not change the initializer differences. Discarded.
3. Inline definitions for the base destructor and background operations:
   64/64, four remaining state-table offsets. Retained the inline State
   destructor; discarded the ineffective background edits.
4. Background constructor moved out of the class with an inline definition:
   same four offsets; createBG stayed exact. Discarded.
5. Restored function definitions to target object order and fixed the real
   letter/photo-letter translation values to 145 and 151. This made the
   floating constant pool identical, rather than relying on relocation-only
   function scoring. Restored the background destructor omitted by the
   ordering experiment before accepting the result.
6. External state globals: no code change, worse .bss score (40% versus 60%).
   Reverted to the existing static definitions.
7. Included the background class declarations after the memo state classes:
   moved its tables ahead of the state tables, but the strong background
   destructor also emitted its derived table there.
8. Made the background destructor inline only for this unit, preserving the
   existing header branches: its deduplicated derived table remains external,
   background Base is first, and all four state offsets match. Initializer:
   64/64, zero differences. All 91 functions are instruction-exact.

Pool remains identical. .sdata, .sdata2, .sbss and .ctors report 100%.
Reported .data remains 61.94834% and .bss 60.000004%. The original splits the
Manager vtable at 0x33c into a separately named 156-byte symbol; the compiler
emits one ordinary 320-byte vtable. Its entries and relocations through 0x3ac
agree. The extracted original additionally ends in 40 zero bytes after the
vtable; no source padding was added. The .bss registry buffers and state
objects have identical offsets and 72 zero bytes, but different buffer symbol
boundaries. No symbol configuration or hand-placed data was introduced.
