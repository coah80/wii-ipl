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

## STB_GLOBAL decode (session 3) — mechanism verified, sd_drv data all-100

Orig .o exports `STB_GLOBAL lbl_XXXX` data symbols = real file-scope objects
(pooled literals are STB_LOCAL). Reproduce with named file-scope decls.

### sd_drv — all data sections now 100% (.data/.rodata/.sbss/.bss)
- Orig .data = 8 GLOBAL objects packed at 4-aligned slots; MWCC 8-aligns every
  .data object ≥8B so separate decls CANNOT reproduce it — merged all 2576B into
  ONE named array `char lbl_81690D18[]` (verified byte-identical). String pad
  rule: consecutive C literals share no implicit NUL; non-final string needs
  `slot_len - len` explicit `\0`s, final needs `slot_len - len - 1`.
- Orig refs: ALL .data relocs are `lbl_X+0` — orig materializes each object
  base into a register then adds plain-int offsets per site. Reproduced via
  per-function `const char* str_base = lbl_81690D18;` + `str_base + off`.
  Single-ref fns use direct `(const char*)lbl_81690D18` (inline lis/addi).
  `pfd_st_inter_callback` now instruction-identical this way.
- .sbss 24B "dead slot" was NOT a dead object: it is g_event alignment pad —
  `u32 g_event __attribute__((aligned(32)))` puts it at 0x20; section 100%.
- .bss residual was a real decode bug: PFD_SDDRV_INFO is 32B not 28 — trailing
  `u32 reserved_1c;` (unreferenced tail field). Now byte-extent-identical.
- Remaining .text ties: multi-base materialization (fns referencing 2+ orig
  objects materialize each base; single str_base under/over-shoots ±8-24B),
  callee-reg home choices, and MWCC not homing globals that orig re-lis'd per
  site (finalize/format). Documented tie class, no source lever found.

### pf_path — .sdata2 object identities decoded
- Orig .sdata2 = 4 separate GLOBAL u8 objects {1,2,1,2} in two 4-aligned
  slots. Reproduced via `__declspec(section ".sdata2") pf_s8 lbl_81695998=1;`
  style decls (non-const so code emits `lbz` per object, matching orig's
  SDA21 relocs; const folds to `li`). sig init is `sig[0]=g; sig[1]=h;`
  assignments (local array init needs constant exprs).
- 2B section tail = extraction hole, same class as orig dead objects; no
  decl produces PROGBITS zero bytes (zero-init routes to .sbss, and MWCC
  doesn't round section size to alignment). Left at 6/8B.
- orig also had .sdata globals lbl_81698390/8391 {1,2} and lbl_81698394
  {0x20,0} shared by 3+ fns — byte-identical already via pooled literals;
  left as pools (declaring globals at 0x28 would reshuffle pool order).
