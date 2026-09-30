# fa/pf_volume

Baseline: 7/37 exact, 1048/17992 code bytes. Matching vf source compared first; this fa variant has 26 volumes and three context slots.

Remaining experiments (ctxdiff evidence in /tmp during matching):
- PFVOL_p_setvol: inline whole operation (93/94, different stack slots); normalize helper result (97/94, different stack slots); remove redundant root error else (93/94, only first conditional branch expansion). Retained original stack layout, 93/94.
- PFVOL_attach: correct free-cluster and drive fields (170/176); canonical search loop (169/176); split driver/cache initialization and mount status (173/176); reorder locals and signed drive conversion (174/176); separate mount helper (174/176, unchanged). Remaining status return boundary, 174/176.
- PFVOL_setcode: six named pointer assignments (23/23, 17 diffs); aggregate assignment (same); word loop (same); inline copy helper (same). Compiler schedules loads before stores and allocates a different base register.
- PFVOL_regctx: indexed context loop (79/75); initialize free index after system call (77/75); return system status (75/75, 20 register differences); reorder free/index declarations (75/75, 15 register differences); split masked status declaration and assignment (unchanged). Retained 75/75.

Other corrected operations now instruction exact: driver request handling, read/write checks, formatting, context removal, label removal, cache flush status, buffering, mount/unmount and configuration. No shared headers changed.
