# fa/pdm_disk continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

pdm_disk_convert_block_into_sector`:
- common operation status exit: 44/44, 0 differences.
- split local declaration from initialization: 44/44, 0 differences.
- Retained: [44, 44, 0].

The original symbol is literally named pdm_disk_convert_block_into_sector` with a trailing backtick in config/43U/symbols.txt and the extracted object. The C definition has the valid identifier without that backtick. Its 44 instructions and 176 bytes already agree exactly when compared under the two names. Three source variants were compiled and restored. ctxdiff rejects the absent backtick-bearing C symbol; no symbol rename, inline assembler alias or symbol-size change was introduced. This remains a symbol-identity mismatch, not a code mismatch.

Third attempt: return small-sector validation failure before the conversion branch; 44/44 instructions, 41 positional differences. Restored original source.
