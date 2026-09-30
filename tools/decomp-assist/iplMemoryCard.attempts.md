# iplMemoryCard matching attempts

Baseline: missing source, 0/41 functions and 0/9264 exact code bytes.
Reused the readable scene reconstruction saved in /tmp/iplMemoryCard.latest-baseline.cpp,
replacing its local class imitations, raw field offsets and pinned double with
existing MemoryCard, MemoryBase, GCWindow, GCSaveData and MemoryCardManager types.
All 102 strings and the animation, pane and message tables match on the first build.
The first build matched 38/41 functions; create matched all 520 instructions.

## on_fadeout2nd

1. Existing bool shutdownCardThread declaration produced 32/33 instructions;
   the target explicitly normalizes an integer return to bool.
2. Guarded the return declaration as BOOL for this source. A bool local now
   emits addic/subfe., matching all 33 instructions.

## show_arw

1. Nested visibility tests followed by else-if produced 102/104 instructions;
   the compiler eliminated the second flag comparisons.
2. Computing visibility before each flag test retained the wrong load ordering
   and 102/104 instructions.
3. Short-circuit calls to real inline can_scroll_r/can_scroll_l members match
   the original load order, repeated flag comparisons and all 104 instructions.

## show_capacity

1. Original u16 getFreeBlocks declaration truncated the return before array
   initialization: 139/139 instructions, 58 differences, 88.431656%.
2. Guarded u32 return declaration and explicit later u16 conversion reduced
   this to 19 differences, 94.85612%, still 139/139 instructions.
3. Inlining the thousands expression changed no instructions.
4. Separating freeBlocks from the converted blocks local and removing division
   temporaries changed no instructions: the remaining 19 differences involved
   decimal arithmetic scheduling and register allocation.
5. Replaced the manual copy from a static number table with a normal local
   digitTable initializer. Decimal arithmetic now matched, but digits initialized
   before the table gave 140/139 instructions and different initialization order.
6. Declared digits without initialization and zeroed them after digitTable.
   All 139 instructions now match. No pointer before an array is constructed.

## Data evidence

.rodata (280 bytes) and .sdata (40 bytes) match completely. Pool: 102/102,
identical including offsets. The generated .data bytes match the original
prefix exactly: 2252 bytes versus 2320. Original trailing 68 bytes are zero.
At 0x870 the original MemoryCardManager vtable symbol includes 160 bytes,
with only its destructor relocation at 0x878. The compiler generates the
natural 12-byte manager vtable, followed by the 80-byte MemoryBase vtable
with ordinary virtual-method relocations. These weak table relocations are
absent in the extracted original; no artificial padding was added.

An experiment using the existing inline MemoryBase destructor rather than
its explicit source definition kept its 16 instructions exact but worsened
.data from 98.51269% to 96.70525%. Kept the explicit destructor in object order.

.sdata2 contains the correct first four floats (16 bytes). The original has
an additional unreferenced eight-byte signed-integer conversion bias. No
relocation in the original references it. Its originating discarded helper
is unknown; no address-pinned constant or dummy conversion was added.

Final code: 41/41 instruction-exact functions. No open code functions.
