# fapark3 — remaining fa/ NonMatching tie-breaks

Leaf: `agent/w0929/fapark3` off origin/main@bcb37e07. 12 owned units, all
NonMatching: pf_cache, pf_cluster, pf_dir, pf_entry_iterator, pf_fat, pf_fat12,
pf_file, pf_path, pf_volume, pdm_partition, driver/sd_drv, api/FAAttach.
Data sections are already 100% on all of them — every residual below is code.

Adopted prior-wave `agent/w0929/fapark` sources (only files differing from
main): pf_cluster.c, pf_dir.c, pf_fat.c, pf_path.c, driver/sd_drv.c.

## Wins this wave

- `pfd_sddrv_get_disk_info` (sd_drv): `return result` → `return 0` made the fn
  instruction-identical (96/96) — orig emits `li r3,0` on the success path even
  when r3 is already 0. Residual fuzzy 97.9 is a pure extraction artifact:
  orig's symbol extent (0x848/0x180) ends mid-epilogue — `mtlr` is the last
  covered insn, `addi r1;blr` uncovered. Byte-identical code, fuzzy <100
  forever (same class as PFSYS_TimeStamp / pdm_disk backtick name).
- `deleted_entry_mark` (pf_volume): orig's .sdata2 object is GLOBAL OBJECT
  (8B, `e5`+pad). Non-static `const u8 deleted_entry_mark[8] = {0xE5}`
  reproduces binding+bytes exactly.

## Verified walls (levers tried, documented)

- **Global-const fold** (`PFVOL_p_rmvvol`, 95.9): orig emits `lbz r0,
  deleted_entry_mark` for a same-TU GLOBAL const. MWCC -ipa file folds every
  form to `li r0,0xe5`: static const array, extern-linkage const scalar,
  extern-linkage const array, extern-decl+def split. Only the head ordering
  differs (4 diffs at 64/64 insns).
- **Select-fold, both directions** (`PFFAT_GetSectorSpecified` −1,
  `pfd_sddrv_init` −2): orig emits a branchy `beq;b;li r3,0` for the
  0/error two-return. Every source form either select-folds
  (andc/neg-or-srawi, 17 insns, fuzzy 85.9) or merges to a single
  `bne`+`li`+shared tail (16 insns, better fuzzy — kept). Tried: explicit
  if/else returns, goto-out, `goto zero`, self-assign arm, init'd decl.
  The orig shape needs an isolated zero-return block MWCC won't emit here.
- **Batch-vs-seq struct copy** (`PFVOL_setcode`, 53.9): orig interleaves
  `lwz r0,off/stw r0,off` per field of the codeset struct copy; MWCC batches
  all loads then all stores for `pf_vol_set.codeset = *code_set`. Tried
  per-field assigns, u32* casts, loop, memcpy (emits call), array-type
  assign (illegal C). No source lever.
- **Reg-model cascade** (`PFVOL_attach` −2): orig carries the mount error in
  r0 across ClearMountRequested (`mr r0,r3` + shared `li r0,0` + per-branch
  `li r3,0` returns); MWCC keeps it in r3 and merges. Same wall as init.
- **Induction-var home** (`PFENT_ITER_GetLFNEntryName`, 90.5): orig keeps a
  byte-offset cursor (r28+=0x1a, `mulli r0,count,0x1a` + `rlwinm &~1`
  terminator) vs mine u16-index. Byte-offset rewrite regressed (76 insns);
  `long_name[num*13]` terminator emits `mulli 0xd;slwi` (extra insn);
  `(u8*)+num*26` emits `mulli 0x1a` but no `&~1` and changes the epilogue
  (inline lwz's vs orig's `_restgpr` tail). Kept u16-index form (73/73).
- **Callee-save +2 / scheduling** (`pdm_part_is_master_boot_sector` +2,
  `pdm_part_get_start_sector` 46 sched diffs at 276/276,
  `PFDIR_p_rename` +1): orig homes loop state in different callee regs
  (uniform +1 window); instruction streams otherwise identical modulo
  ordering. Regalloc-internal, no lever found (documented prior wave).
- **Symbol-overlap artifact** (`PFPATH_MatchFileNameWithPattern`, 98.5):
  orig symbol range over-extends 12B into the next fn (putShortName) — the
  covered code is byte-identical; fuzzy can't reach 100.
- **sd_drv .sbss**: 24B of dead slots between the live globals — extraction
  layout artifact, no source decl produces it.

## Remaining sub-100 fns (all documented above or size-equal regname ties)

- pdm_partition: is_master_boot_sector 86.5, get_start_sector 82.6,
  chg_ltop 97.8 (regname only)
- pf_cache: DoWriteNumSectorAndFreeIfNeeded 98.2
- pf_cluster: CombineFiles 99.8, InsertCluster 98.8, DeleteCluster 98.2
- pf_dir: p_mkdir 99.6, p_rename 98.2, p_move 99.3
- pf_entry_iterator: FindCluster 99.8, GetLFNEntryName 90.5
- pf_fat: DoAllocateChain 99.8, GetClusterAllocated 99.6, GetSector 99.4,
  GetSectorSpecified 93.5 (goto-merge beats select's 85.9 — kept),
  FreeChain 99.6, RefreshFSINFO 99.1
- pf_fat12: WriteFATEntryWithBuf 99.8, ReadFATEntryWithBuf 98.7
- pf_file: GetSFD 99.1
- pf_path: cmpNameImpl 98.4, MatchFileNameWithPattern 98.5 (artifact)
- pf_volume: p_rmvvol 95.9, attach 98.7, setcode 53.9, regctx 99.0
- FAAttach: FAAttach 99.4 (volatile-reg home tie)
- sd_drv: removal_callback 96.8, init 92.9, finalize 92.6, get_disk_info
  97.9 (artifact), get_total_sectors 99.5, store_mbr_buf 99.8,
  build_fat32_mbr_bpb 97.2
