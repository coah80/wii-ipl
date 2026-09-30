# fa/pf_entry_iterator attempts

The matching vf implementation supplied iterator movement, path traversal, and directory parsing. The fa object adds a word to FFD, extends the FAT hint, changes search attribute handling and entry-name matching, and replaces FindCluster with an ancestor search. All 16 target functions are implemented in object order; 14 are instruction-exact.

PFENT_ITER_FindCluster:
- Initial ancestor traversal: 231/237 instructions; unused standalone chain counter disappeared.
- Use hint.chain_index, correct cluster_link initialization, and unsigned entry-offset shift: 237/237; 48 differences, mostly register allocation.
- Move hint before current_cluster and delay hint.chain_index initialization: 237/237; 11 register differences.
- Swap sector-index/entries-per-sector declaration order: 237/237; 8 register differences. Retained.
- Reverse sector-index bitwise operands: no change. Move entries declaration first: no change. Delay FFD start-cluster assignment: 16 differences; reverted.

PFENT_ITER_GetLFNEntryName:
- Separate long_name expressions for each copy: 77/73 instructions; three independently advanced destination offsets.
- Reuse one destination pointer: 78/73; fewer address calculations, but signed final division added correction instructions.
- Unsigned final index and explicit byte-offset loop: 76/73; compiler advances destination pointer directly, unlike target's offset addition.
- Signed loop counter: 76/73, adds signed comparison; reverted.
- Destination index (i * 26U) / 2U: 74/73; one extra alignment-mask instruction and loop/destination register allocation. Retained.
- Byte-pointer arithmetic, integer-address arithmetic, or three byte-pointer copy expressions: 76/73; same pointer induction. Reverted.

Data: ordinary literals occur in target order. Candidate .sdata is 22 bytes; target is 24 bytes. The common 22 bytes are identical; two trailing zero bytes remain unresolved. No padding or extra literals added. pool_diff.py requires .data and raises KeyError for this unit; the gate reports identical empty .data pools, so the explicit ELF .sdata comparison is the meaningful data check.
