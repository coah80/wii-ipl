# fa/driver/nand_drv continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

fa_nanddrv_ParseCreateNANDFile:
- rotate independent local declarations: 130/130, 22 differences.
- common operation status exit: 130/130, 10 differences.
- reverse independent local declarations: 130/130, 22 differences.
- Retained: [130, 130, 10].

fa_nanddrv_NotifyNANDFile:
- rotate independent local declarations: 72/72, 12 differences.
- common operation status exit: 72/72, 12 differences.
- reverse independent local declarations: 72/72, 12 differences.
- Retained: [72, 72, 12].

fa_nanddrv_physical_write:
- rotate independent local declarations: 175/175, 30 differences.
- common operation status exit: 175/175, 38 differences.
- reverse independent local declarations: 175/175, 27 differences.
- Retained: [175, 175, 38].

NotifyNANDFile additionally used the indexed file-size destination (72/72, twelve differences reduced to six) and a separate candidate pointer (72/72, unchanged). Retained the indexed destination without the extra alias. Six pointer/stride register differences remain. ParseCreateNANDFile retains ten control-flow differences around the directory-change error exit. physical_write retains callee-saved register differences; all three declaration/return variants preserved instruction count.
