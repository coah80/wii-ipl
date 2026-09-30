# fa/pf_cluster matching attempts

All eight functions are implemented. The five exact functions have zero instruction differences. The three open functions have identical instruction counts to the target and differ in register allocation or arithmetic scheduling. The unit has no target data section.

## PFCLUSTER_CombineFiles (207 instructions)

1. Initial C reconstruction: 206 instructions; swapped stack addresses and one missing branch in the second spare-chain selection.
2. Separate second-chain selection assignment, reversed stack declarations, and grouped cluster totals: 207 instructions, four differences in the overflow comparison's registers and addition order. Retained.
3. Explicit total-cluster temporary, then an explicit maximum-cluster temporary: seven differences in the same comparison; the compiler retained different temporary registers.
4. Reversed temporary initialization order: seven differences; restored attempt 2.

## PFCLUSTER_InsertCluster (126 instructions)

1. Initial C reconstruction: 28 register differences; stack locations and instruction count match. Retained.
2. Reused the incoming cluster count as the allocation-loop byte count: the same 28 differences.
3. Copied the incoming count to an allocation local before the first call: 29 differences, including changed argument scheduling; no improved register assignment.
4. Initialized the allocation count before tracing and removed the loop initializer: 36 differences, with the same total instruction count; restored attempt 1.

## PFCLUSTER_DeleteCluster (108 instructions)

1. Initial C reconstruction: 51 differences, including reversed stack locations and saved-register assignments.
2. Reordered output locals, moved volume before size locals, and reused the incoming count for the deletion byte count: 35 register differences; all stack locations and instruction count match. Retained.
3. Reversed the volume/size declaration order: 42 register differences; no instruction-count improvement.
4. Scoped the size computations in a nested block with a separate deletion-size local: 35 differences, with a different count register; restored attempt 2.

The forbidden-pattern scan initially classified the real FAT spare-chain variables as dummy objects because their inherited names contained `unused`. Renamed them to `spare`; these variables are consumed by chain tracing and freeing.
