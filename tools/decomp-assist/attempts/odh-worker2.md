# odh `cdj_d_decompressLoop` (worker-2) 2026-10-02

Claim was only `cdj_d_decompressLoop`. colorConv, huffmanDecoder, and LineConv11 were not modified in the committed diff.

## Result

`cdj_d_decompressLoop` **899/899, 0 diffs, byte-identical** (3596 bytes) to retail. Was 43, then 7.

## What matched

- Inlined `(blockRowSize * 2)` and `((u32)blockWidth << 4)` (init `slwi r18` / `slwi r17`).
- `planeOffset += (u32)master->blocksWide << 6` coalesces the 1x2 update into `add r15, r15, r0`.
- `int nextBlockX = master->blockX + 1` with `(u16)` compare (same shape as compressLoop).
- Second 1x1 chroma sum written blockX term first.
- idct destinations that need plane-first `add` use `(u8*)((u32)planeOffset + (u32)master->workBuffer) + 8`.
- 2x2 tail stores the updated plane in `requiredBlockEnd` and the end pointer in `planeOffset`. That is what puts the plane in r15 and the end in r16 (`addi r15, r3, -8` / `add r16, r15, r18`). Assigning the plane back to `planeOffset` left those two callee-saves swapped (7 diffs). Splitting the `-8` let MWCC cancel it against the later `+8` and dropped to 897.

colorConv left at the 18 pairwise wall. Not in this diff.
