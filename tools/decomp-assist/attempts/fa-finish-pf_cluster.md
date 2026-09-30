# fa/pf_cluster continuation

Measured source variations; counts are source/target instructions and positional comparison differences. Each candidate was built separately and compared with ctxdiff. Variations were reverted unless instruction exact. Earlier targeted attempts remain in the existing fa attempt logs.

PFCLUSTER_CombineFiles:
- rotate independent local declarations: 207/207, 4 differences.
- common operation status exit: 207/207, 4 differences.
- reverse independent local declarations: 207/207, 58 differences.
- Retained: [207, 207, 4].

PFCLUSTER_InsertCluster:
- rotate independent local declarations: 126/126, 28 differences.
- common operation status exit: 126/126, 28 differences.
- reverse independent local declarations: 126/126, 40 differences.
- Retained: [126, 126, 28].

PFCLUSTER_DeleteCluster:
- rotate independent local declarations: 108/108, 35 differences.
- common operation status exit: 108/108, 35 differences.
- reverse independent local declarations: 108/108, 53 differences.
- Retained: [108, 108, 35].

Swapping the operands around the grouped cluster total leaves CombineFiles at 207 instructions and four differences, confined to the overflow comparison arithmetic schedule. Restored. InsertCluster and DeleteCluster retain equal counts with 28 and 35 register differences. Prior targeted attempts are in fa_pf_cluster_attempts.md.
