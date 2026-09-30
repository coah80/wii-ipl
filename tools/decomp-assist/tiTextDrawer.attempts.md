# tiTextDrawer attempts

No source existed. Reconstructed all 24 functions using tiTextDrawer.h and tiUtil.h, with a private implementation macro preserving every existing guard branch. Replaced raw scratch offsets with viewport/projection/string/cache fields and typed DrawInfo members. Ordinary table initialization loops reproduce the compiler's 32-store unrolling. Pools are empty and identical.

## beginDraw
1. Direct scale * viewport width expression: 109/109 instructions, one difference at instruction 59, fmuls f7,f11,f7 versus fmuls f7,f7,f11.
2. Reverse multiplication operands: unchanged single difference; compiler canonicalizes this expression.
3. Separate scaledWidth temporary with compound multiplication: 109/109, sixteen floating scheduling/register differences. Discarded; retained attempt 1.

## data
BSS is 1408/1408. The .sdata2 constants have identical order and bytes for all 44 emitted bytes. The extracted object has four additional zero bytes at its section end; no padding object was added. The vtable has one relocation-name discrepancy: the target references isEnableCursorCache__Q39textinput10textdrawer4BaseCFvgetStartPos__Q39textinput10textdrawer4BaseCFv, a concatenated symbol name present in symbols.txt, whereas normal C++ references isEnableCursorCache__Q39textinput10textdrawer4BaseCFv. Kept ordinary declarations rather than renaming a real function or introducing a fabricated alias. Other data bytes and vtable entries match.
