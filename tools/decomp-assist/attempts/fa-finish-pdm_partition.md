# fa/pdm_partition continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

pdm_part_is_master_boot_sector:
- rotate independent local declarations: 86/84, 82 differences.
- common operation status exit: 86/84, 82 differences.
- reverse independent local declarations: 86/84, 82 differences.
- Retained: [86, 84, 82].

pdm_part_chg_ltop:
- rotate independent local declarations: 51/51, 16 differences.
- common operation status exit: 51/51, 16 differences.
- reverse independent local declarations: 51/51, 16 differences.
- Retained: [51, 51, 16].

pdm_part_get_start_sector:
- rotate independent local declarations: 276/276, 148 differences.
- common operation status exit: 276/276, 141 differences.
- reverse independent local declarations: 276/276, 138 differences.
- Retained: [276, 276, 141].

Additional targeted attempts: remove the preliminary partition-start store and exchange array declarations (83/84, seventy-two differences); reverse the two endian addition groups (86/84, eighty-three differences); load the sector ratio before the partition-start value (51/51, sixteen differences, unchanged). All were restored. The target retains the preliminary store and a different byte-load schedule. Logical-sector conversion still swaps its two arithmetic registers; extended partition scanning still differs in register assignment and endian load scheduling.
