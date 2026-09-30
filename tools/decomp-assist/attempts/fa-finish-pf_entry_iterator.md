# fa/pf_entry_iterator continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFENT_ITER_FindCluster:
- rotate independent local declarations: 237/237, 8 differences.
- common operation status exit: 237/237, 75 differences.
- reverse independent local declarations: 237/237, 11 differences.
- Retained: [237, 237, 8].

PFENT_ITER_GetLFNEntryName:
- rotate independent local declarations: 74/73, 33 differences.
- common operation status exit: 74/73, 33 differences.
- reverse independent local declarations: 74/73, 33 differences.
- Retained: [74, 73, 33].

GetLFNEntryName: direct i * 13 indexing and a separately incremented byte offset both produce 76 instructions against 73 and introduce pointer induction absent in the target. Restored the 74-instruction version. FindCluster remains 237/237 with eight r7/r8 differences in iterator initialization. Earlier targeted attempts are in pf_entry_iterator.attempts.md.
