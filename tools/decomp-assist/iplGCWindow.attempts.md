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

## Continuation from c77b866e

Starting measurements: 46/48 instruction-exact functions, 8552/9964 code bytes, 248/2032 data bytes, 38/50 pool strings.

### Pool and constructor

The original object's .rela.text, .rela.rodata and .rela.data contain no references into the twelve trailing strings at .data offsets 0x444 through 0x597. The only reference to the encompassing lbl_81652C50 symbol is the preceding WIPL_SE_COPY_FINISH literal. Therefore no surviving target function uses the missing strings. The SavedataEditWindow layout uses the same deletion animation indices as those filenames imply; its constructor was stripped from the final DOL. The neighboring SavedataEdit constructor also disables T_Block_01 during layout initialization.

1. Reconstructed an inline SavedataEditWindow constructor using a local animation table and the same pane/event/button setup as GCWindow and GCSaveData. Because the constructor has no live callers, MWCC omitted it and the missing strings remained absent, 38/50.
2. Compiled the ordinary constructor out of line. Its animation table and T_Block_01 appeared in exactly the target order and offsets. A direct B_Del_00 argument emitted an extra string; referencing the existing scButtonName[2] corrected the pool to 50/50. The local descriptor table added 80 rodata bytes, reducing that section to 88.37209%; rejected that table representation.
3. Added a private name/group overload that creates one ordinary stack descriptor and calls MemoryBase::add_animation. Individual calls reproduced the original animation filenames. Literal group arguments duplicated G_DelFlash and G_Select, giving 52 strings and an sdata mismatch. Reusing the existing scAnmName groupName fields restored 50/50 pool strings and 100% rodata, sdata and sdata2. Kept this implementation.
4. Tested guarded inline MemoryBaseEvent destructor/event-handler definitions recovered from the original iplMemoryCardBase assembly. The empty destructor alone emitted no additional vtable. Inlining the event handler emitted its real 28-byte vtable after MemCardEventHandler, rather than in the preceding 32-byte discarded range. It did not improve objdiff data measurements; reverted both changes.

The pool now matches all 50 strings with identical offsets. The raw data bytes are identical over the complete 0x678-byte candidate .data section. Original .data has 0x6f8 bytes, including linker-discarded weak-table ranges; the candidate naturally emits 100 bytes for the GCWindow vtable rather than the original symbol's 132-byte span and 16 bytes for MemCardEventHandler rather than its 168-byte span. No padding, retention directive or synthetic symbol was introduced. The reconstructed constructor's code cannot be instruction-verified because the original DOL has no surviving constructor symbol. Its intended behavior follows the existing scene setup, and this uncertainty remains explicit.

### onMemEvent

1. Changed the format-message state's terminal break into an early return. Still 153/155 instructions.
2. Moved that early-return case immediately before the processing case. Generated 154/155 instructions, but the return branch appeared before the nested operation switch.
3. Placed the format-message case after the operation switch and routed processing to the named process_complete block. Generated exactly 155/155 instructions with diffs 0. Exact-name objdiff reports 100%. Kept this arrangement.

### init

1. Reused the full-width blocks variable and explicitly masked it after the digit-array initialization, instead of introducing a separate truncated blockCount. Still 198/198 instructions with 48 differing positions.
2. Bound the interpolated result to a const reference before finding the pane. Same 198/198 instructions, 48 differing positions and exchanged vector stack slots; rejected.
3. Declared and initialized the blocks accumulator before the title calls and assigned the getter result later. Same 198/198 instructions and 48 differing positions; rejected. Restored the previously accepted initialization source.

The remaining init differences are register allocation in decimal conversion and the two vector stack slots. No further untried target functions remain.

### Validation baseline

The installed gate has no baseline-c77b866e.json. The final full gate therefore uses --base 550c5f19, the closest installed baseline. An additional fresh report was generated by rebuilding the unchanged c77b866e GCWindow source/header in this worktree and saved only to /tmp/sol-high-gcw-r2-current-main-baseline.json. The final report is also compared against that current-main snapshot across every unit and every previously exact function. Protected baseline files were neither edited nor created.

Final full gate with --base 550c5f19: GATE PASS. Pool IDENTICAL, 47/48 instruction-exact functions, 9172/9964 code bytes, 248/2032 data bytes. rodata, sdata and sdata2 each 100%; data 8.861147%. Fresh c77b866e comparison: zero regressions across all unit measures and previously exact functions. The complete 43U build passed with DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Forbidden patterns and readability warnings: zero.
