# fa/pf_volume continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFVOL_p_setvol:
- rotate independent local declarations: 93/94, 83 differences.
- common operation status exit: 93/94, 83 differences.
- reverse independent local declarations: 93/94, 84 differences.
- Retained: [93, 94, 83].

PFVOL_attach:
- rotate independent local declarations: 174/176, 64 differences.
- common operation status exit: 174/176, 37 differences.
- reverse independent local declarations: 174/176, 64 differences.
- Retained: [174, 176, 37].

PFVOL_regctx:
- rotate independent local declarations: 75/75, 15 differences.
- common operation status exit: 75/75, 15 differences.
- reverse independent local declarations: 75/75, 20 differences.
- Retained: [75, 75, 15].

PFVOL_setcode:
- common operation status exit: 24/23, 20 differences.
- Retained: [23, 23, 17].

setcode additionally tried a copy helper taking both a destination codeset pointer and the source pointer (23/23, seventeen register/load-store differences, unchanged). Restored the original helper. The original aggregate-copy and loop variations, and all remaining volume functions' targeted three-attempt records, remain in fa-volume.md.
