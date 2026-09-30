# fa/pf_fat continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFFAT_DoAllocateChain:
- rotate independent local declarations: 216/216, 55 differences.
- normal path first, validation failure last: 215/216, 186 differences.
- common operation status exit: 216/216, 5 differences.
- Retained: [216, 216, 5].

PFFAT_GetSector:
- rotate independent local declarations: 88/88, 7 differences.
- common operation status exit: 88/88, 7 differences.
- reverse independent local declarations: 88/88, 7 differences.
- Retained: [88, 88, 7].

PFFAT_GetClusterAllocated:
- rotate independent local declarations: 70/70, 6 differences.
- normal path first, validation failure last: 69/70, 28 differences.
- common operation status exit: 70/70, 6 differences.
- Retained: [70, 70, 6].

PFFAT_GetSectorSpecified:
- common operation status exit: 16/17, 6 differences.
- Retained: [16, 17, 6].

PFFAT_RefreshFSINFO:
- rotate independent local declarations: 93/93, 27 differences.
- common operation status exit: 93/93, 14 differences.
- reverse independent local declarations: 93/93, 26 differences.
- Retained: [93, 93, 14].

PFFAT_FreeChain:
- rotate independent local declarations: 256/254, 137 differences.
- normal path first, validation failure last: 256/254, 178 differences.
- common operation status exit: 256/254, 113 differences.
- Retained: [256, 254, 113].
