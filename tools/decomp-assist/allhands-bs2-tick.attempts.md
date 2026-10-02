# BS2Tick control-flow reconstruction, 2026-10-02

Baseline BS2Mach source is 449529d9. This candidate changes only BS2Tick in
src/BS2/BS2Mach.c. Existing ESMisc and AOSSLink commits remain separate.

Initial pool_diff: 91/91 strings identical. Read the BS2 round-two/round-three
and fz1 attempt records, and compared the current five open functions with
fresh target objects. The Run hardware-handoff deficit is separate and is not
changed or represented as complete here.

## Retained source reconstruction

1. Express the title-family dispatch as the actual sparse set D/R/S/T.
   The target compares D below R, then dispatches the contiguous R-through-T
   group using an upper boundary U. The switch restores its branch pair and
   makes the family set explicit. Exhaustively checked all 256 prefix values.
2. Restore the positive game-partition state transition and capture the
   partition offset at entry to state 0x25, before either cache or disc path.
   The target loads the partition member before choosing the cache branch;
   the old source only read it on the disc path. The incoming partition
   existence check and the state-37 fallthrough remain explicit.
3. Restore the banner address diagnostic's missing variadic argument.
   Target BS2Tick object offsets 0x39B4–0x39D8 compute the aligned banner
   pointer in r4, store it as BannerBuffer and pass it to BS2Report. The old
   source supplied the %08X format with no argument on the allocation path.
4. Express the same next-cache-line calculation as allocation + 32 minus its
   remainder modulo 32. This retains the target's strictly-next-line behavior,
   including when the allocation is already aligned. It does not add padding
   storage. Checked 196608 address samples including all low 16-bit values at
   zero, 0x80000000 and near u32 wrap.

Measured attempts, all retained and individually nonregressing:

| Attempt | BS2Tick fuzzy | Unit fuzzy |
| --- | ---: | ---: |
| Baseline | 98.230415% | 98.159485% |
| Actual title-family switch | 98.35567% | 98.21673% |
| Partition entry and typed member snapshot | 98.58763% | 98.32273% |
| Banner diagnostic argument | 98.59278% | 98.32509% |
| Explicit next-cache-line remainder | 98.639175% | 98.34629% |

BS2Tick grows from 1934 to 1937 instructions; target is 1940. The remaining
three missing instructions are address-materialization differences, with
additional register and instruction-scheduling differences. This is partial
reconstruction/matching progress, not an exact function.

## Verification

- Full all_source / fresh report / build/43U/ok requested after focused build
- DOL SHA1: 26116613f624061ba99c8d1a299aaa6efa85670d
- Exact functions unchanged: 24/29; exact code unchanged: 4940/16980
- Data unchanged: 155504/158528 (98.092445%)
- Every other unit's report unchanged
- The 91-string pool is identical; literal reference audit checks 37 arguments
  across 24 exact functions with no candidates or errors
- Compared all 1027 source objects with the initial snapshot: only previously
  committed ESMisc and this BS2Mach object differ. BS2Mach .text 16828 -> 16840
  bytes, 1306 relocations on both sides; .data stays 3020 bytes and 155 jump-table
  relocations; all other allocated sections/objects are unchanged
- git diff --check passes

No BS2Update, shared-header, metadata, link-flag or assembly change is included.
