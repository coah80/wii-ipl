# fa/pf_fat12 continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFFAT12_WriteFATEntryWithBuf:
- rotate independent local declarations: 175/175, 8 differences.
- common operation status exit: 175/175, 8 differences.
- reverse independent local declarations: 175/175, 28 differences.
- Retained: [175, 175, 8].

PFFAT12_ReadFATEntryWithBuf:
- rotate independent local declarations: 155/155, 34 differences.
- common operation status exit: 155/155, 48 differences.
- reverse independent local declarations: 155/155, 34 differences.
- Retained: [155, 155, 34].

Additional write attempt: use a sixteen-bit FAT-sector local and write pointer additions with the buffer first (175/175, eight differences, unchanged). Restored the original declarations. The remaining write differences are sector/offset coalescing across a sector boundary and two addition operand orders. Read differs in four callee-saved registers; all tested forms retain 155/155 instructions.
