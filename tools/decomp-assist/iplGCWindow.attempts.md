# GCWindow attempts

Baseline: no source, 0/48 matched functions, 0/9964 matched code bytes, 0/2032 matched data bytes.

## init

1. Recovered the constructor, state machine and initialization from original object disassembly and `/tmp/iplGCWindow.ghidra.txt`. Reused existing MemoryBase, MemoryCardManager and PaneManager headers. Initial initialization generated 197/198 instructions. The title dimensions and interpolation duration were restored to their original constants, 450, 31 and 12.
2. Corrected the local getBlocks declaration to a full-width result under IPL_GC_WINDOW_CPP, moved decimal writes into thousands-to-units order and used a separate source expression for wcscpy. Generated 198/198 instructions, 87 differing positions. This declaration preserves the target caller's truncation after the digit-table copy.
3. Split the packed working buffer into three named arrays and used memcpy plus explicit zeroing loops. Generated 199/198 instructions; memcpy remained a call and zeroing remained loops. Rejected.
4. Initialized a local digit array with ordinary character literals and used aggregate zero initialization for the decimal/output arrays. Generated 199/198 instructions; all digit copying and decimal arithmetic operations appeared in target order, with register differences and one extra address instruction.
5. Named the interpolated position before finding the pane. Generated 198/198 instructions, 48 differing positions. Differences are register allocation in decimal conversion and the exchanged stack slots of the zero and interpolated vectors. Kept this readable version.
6. Separated the truncated block count and introduced a named thousands quotient. Neither changed allocation or instruction counts; removed the unnecessary quotient variable.

## onMemEvent

1. Literal event/state/operation switches generated 153/155 instructions. The target retains two additional unconditional branches just before the common process-completion block.
2. Added an explicit outer default case. Same 153/155 instructions and missing branches; rejected.
3. Separated process completion behind a named label, with the idle format-state case before that label. Same 153/155 instructions; rejected.
4. Inverted the deletion-slot test into an early return and added an explicit inner default. Same 153/155 instructions; kept the early-return version for clarity.

## Data and declarations

The first 38 data-pool strings have the target order and offsets. The last 12 target strings belong to the unused SavedataEditWindow configuration: ten animation filenames, T_Block_01 and a second T_Del_00. The ordinary static animation table is present in source, but MWCC eliminates it and its strings because no surviving function references it. No retention trick or filler was added.

The GCWindow vtable is emitted naturally. Its original object symbol includes 32 trailing zero bytes; the MemCardEventHandler symbol includes further linker-discarded zero-filled weak artifacts. Those are not reproduced with padding. The other data sections match in objdiff.

SavedataEditWindow's virtual lifecycle names are inferred: init, calc, draw, destroy. The observed final lifecycle slot is 0x5c, and calc invokes it when fadeout completes; all seven surviving SavedataEditWindow functions match instruction-exactly. The initializer signature and unused lifecycle methods need confirmation before that class is instantiated. Its event pointer field is inferred from the corresponding memory-window layout.

No other unit is switched to Matching, no other source is changed, and shared-header declarations are guarded by IPL_GC_WINDOW_CPP, defined only by iplGCWindow.cpp.
