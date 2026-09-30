# fa/pf_dir

Baseline 22/38 exact. VF source diff inspected before editing. Sources already contained all 38 bodies; several large bodies lacked fa-specific operations.

Remaining attempts, instruction counts (source/target), retained source in the final commit:
- GetSDD: original flag condition 67/69; status-word negation 68/69; retain flag prerequisite 69/69 with two increment-order differences; update pointer in body, measured below.
- opendir: explicit += count update 39/39 two register differences; invert successful branch 39/39 nine differences; inline status helper 39/39 nine differences. Restored first form.
- p_fsnext: local pattern, loop and global setting correction 186/193; signed indexed file scan 191/193; while loop 193/193, 39 differences (loop-limit hoisting).
- p_rmdir: opened-directory helper 165/202; normalize FreeChain result 169/202; add path split and iterator/hint copies 186/202; restore saved iterator/hint before removal 203/202. Stack/copy scheduling remains.
- p_fsexec_remove: opened-directory helper 159/176; initialize a separate iterator 153/176; delay cluster load 151/176; reset supplied iterator and restore its saved state, with file size bound 178/176. Stack/control scheduling remains.
- p_mkdir: port API calls and fa FFD/STR/hint types 254/562; order iterator workspace and split name-length errors 256/562; order hint before position 256/562. Missing original inline entry initialization/allocation operations remain.
- p_rename: unconditional filename validation 190/625; swapped iterator workspaces and corrected end sentinel 191/625; explicit destination code-mode local and restored iterator order 191/625. Original long-name allocation/update operations remain missing.
- p_move: unconditional filename validation 211/631; use opened-directory helper and workspace order 215/631; explicit code-mode local and restored iterator order 215/631. Original cross-directory entry allocation/update remains missing.
- p_fsexec: correct flags and use entry start-cluster storage 206/280; move iterator setup before start-position selection 206/280; reorder workspaces and compare status explicitly 207/280. Original name-search/control paths still differ.

New exact functions include directory allocation, open-by-path, chmod, stat, fsexec chmod and context changes. No shared headers changed.
