
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

## WADBackupEx decode round 2 (fossil + ptr web)
- Dead-compare fossil SOLVED: `if (A) { X = v; } ... X = v;` — conditional assign whose
  store is killed by a later unconditional assign → MWCC keeps lbz+cmplwi, drops bne.
  Applied: `if (flags[2]==1) { fileFd = -1; } if (fileOpened) NANDClose; fileFd = -1;`
  reproduces orig's exact `lbz;cmplwi;lwz;cmpwi;beq` sequence (-8B wall gone).
- file_done label placement: label sits BEFORE the flags-if (inner gotos land past it,
  outer bne/beq edges land on it) — `file_done:` above the fossil if.
- result=0 redundant-store dedup inside `if (path==0)` arm: orig omits it (already 0).
- &headerBlock member-address chains: orig emits `addi r3,r1,0x340; addi r3,r3,+off`
  (remat base + member offset) for deviceId/cidx/deviceMac args. Best source form =
  `WADBackupHeader* headerBlockHeader = &headerBlock.header` used for the three
  member args → `addi r3,r18,+off` (structurally right; r18-kept vs orig remat =
  keep-vs-remat wall). `(&x)->y` and `x.y` fold to absolute; per-site ptr assigns
  fold remat+offset — all worse.
- Remaining diffs (all documented keep-vs-remat/web-coloring): `li 0;stw` vs `li;mr`
  for result head store, `addi r1,0x340` remats vs r18/mr, stw 0x814/lwz 0x80c spill
  webs, `li -1` fileFd slot, addi+0x80 loop-IV position, `addi r1,0x3c0` remat order.
