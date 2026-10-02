
## WADBackupEx decode (this leaf session)
- file_done region: orig CFG has inner `goto file_done` edges landing PAST a `flags[2]==1`
  check (goto-specialized entries). Faithful source = label inside the flags-if:
  `if (hdr->flags[2]==1) { file_done: if (fileOpened) NANDClose(&savedFile); }`.
  Orig folds the outer if to a dead lbz+cmplwi fossil (no bne) via edge-prop that
  fileOpened==0 on the flags!=1 path; our MWCC emits the bne (+4B).
- result=0 at file-loop head: orig keeps ZERO in dedicated callee reg (r31);
  ours spills an extra zero to stack slot (extra stw+lwz). keep-vs-remat wall.
- Several base+offset addi folds (0x340+8 vs 0x348 etc.) = documented fold family.
- GetBlocks vestigial NULL ptr locals + conditional frees = orig-faithful decode (solved).
- DVDExForBS `if (header.contentSize != 0)` dead-check fossil = conditional-assign
  overwritten by later unconditional assign (solved).
