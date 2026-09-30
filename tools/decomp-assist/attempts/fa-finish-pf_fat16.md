# fa/pf_fat16 continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFFAT16_WriteFATEntryWithBuf:
- rotate independent local declarations: 66/66, 12 differences.
- common operation status exit: 66/66, 7 differences.
- reverse independent local declarations: 66/66, 16 differences.
- Retained: [66, 66, 7].

Swapping sector and offset declarations reduces seven differences to one at equal 66-instruction count. Reversing pointer addition and introducing an entry pointer each leave the final add operand order unchanged. Kept the declaration change.
