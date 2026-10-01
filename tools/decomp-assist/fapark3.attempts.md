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

## Session 4 — code-tie grind (no flips)

- **Volatile store→load pinning (sd_drv, decoded lever):** casting to
  `((volatile PFD_SDDRV_INFO*)&g_pfd_sddrv_info)->field` on BOTH the store and
  the dependent load pins MWCC's memory-op order to source order — stops it
  hoisting a load past a preceding same-struct store. Applied at init (2
  sites), finalize (4 tail assigns), removal_callback (store + check).
  Byte-identical at those sites.
- **copy_bytes peel model (sd_drv, decoded):** orig's copy helper is manually
  peeled — `d[0]=*src; src++; for(i=1;i<size;i++) d[i]=*src++;` gives the
  `addic.` live-IV test + abs-folded elem0 + `lbz k(r3)` walk. But the two
  11B volume_label copies emit an UNPEELED all-walk — needed a second plain
  helper called only at the 11B sites. store_bpb_buf + store_fat32_bpb_buf
  byte-identical.
- **Early-return vs select-assign:** `r=-44; if(cond) r=0; return r;` folds to
  select (`li -44; bne`); `if(!cond) return -44; return 0;` gives orig's
  branch layout. Fixed pfd_sddrv_init tail.
- **GetLFNEntryName IV model (pf_entry_iterator, partial):** orig's `index`
  is a byte offset into p_ent (long_name at +0): `li r31,0; addi r31,0x1a`;
  dst recomputed `add r30,r28,r31` per iter; terminator via byte-arith
  `*(u16*)((u8*)p_ent + num*0x1a) = 0` → `mulli 0x1a; rlwinm; sthx`.
  u16-index forms give `mulli 0xd; slwi`. Byte-offset forms reproduce the
  terminator but MWCC folds `p_ent + index` into a pointer-IV (4 callee webs)
  vs orig's index-IV + per-iter recompute (5 webs, r27-r31). ~8 source forms
  tried: `&long_name[index]`/`index += 13` (closest, 38 diffs — kept),
  `(u8*)p_ent->long_name + index` (+63), `(u8*)p_ent + index` (+66),
  `num*0x1a` terminator. Residual = MWCC IV-vs-recompute choice; no lever.
- **DoWrite overlap-sum derivation (pf_cache, decoded but unwinnable):**
  orig computes `sum = sector+num_sector` once then derives `last = sum-1`
  (`addi r3,r4,-1`) and `num_overlap = sum - p_sector` (`subf r4,r5,r4`).
  Source forms sharing the sum (`sector+num_sector-1` either order, named
  `end_sector` temp, `last+1-p_sector`) all cascade regalloc elsewhere
  (-205/-88/-120 diffs vs 7 baseline). The 6-diff reorder reads
  num_overlap before assignment — UB, rejected. Kept honest form.
- **pdm_part_get_start_sector:** 46 residual diffs are pure scheduling
  permutations of the flat-assoc MBR_WORD decode (same insn set, lbz/slwi
  interleave differs). Documented tie.
- **Uniform callee-reg rotations (regname-only, insn-identical):**
  pf_cluster×3 (InsertCluster +1-web rotation, DeleteCluster mixed),
  FAAttach (volatile-reg homes on the gOpenDisk/gOpenPartition store
  cluster — inlining `table->drive-'A'` per site regressed to 136 insns),
  pf_file GetSFD (3-word mr-ordering swap, ~6 lever forms across waves),
  pf_fat12 ReadFATEntryWithBuf (flag r29/err r28 web swap in the select
  `li flag,1; beq; clrlwi` — WriteFAT's identical construct matched, so
  it's context regalloc; uninit-err rotated everything wrong).

## Session 5

### pf_entry_iterator .sdata decode (STB_GLOBAL -> named file-scope objects)
- orig exports 5 STB_GLOBAL .sdata objects ("..", ".", ":", "\\", "/") plus one 4B
  all-zero object. Named file-scope `__declspec(section ".sdata") pf_s8 g_*[]`
  reproduces them: relocs become addend-0 against named globals exactly like orig.
- NEW WALL: MWCC emits ALL all-zero-init objects to .sbss — declspec/volatile/
  const/{0}/"" all fail to reach .sdata. The 4B zero object is only reproducible
  as the pooled literal "\0\0\0" (literal pool always emits to .sdata).
- FindCluster residual: 8 word diffs = paired web-home swap — store-`1` web
  (start_cluster/previous_cluster/chain_index stores) vs shift-`1` web
  (1<<log2_entries_per_sector) swap r7/r8 between builds. Reorders cascade (218)
  or no-op.

### pf_fat12 ReadFATEntryWithBuf
- `pf_s32 err;` uninit + `err = 0;` before `while (PF_TRUE)` homes err in the
  LAST callee web like orig (35->34). Residual = pure callee-reg rotation
  (orig offset->r31,sector->r30,flag->r29,err->r28; mine err->r31,...).
  DECL ORDER DOES NOT CONTROL MWCC callee-web priority — proven invariant
  across all orderings.

### pdm_partition
- MBR_WORD merge order: flat LOW-BYTE-FIRST `b0 + (b1<<8) + (b2<<16) + (b3<<24)`
  is best (get_start_sector 146->45 word diffs, fuzzy 82.6->95.0). Orig's
  residual tree is PAIRWISE `(b2<<16+b0) + (b3<<24+b1<<8)` — even/odd pairing.
  MWCC reassociates flat `+` chains freely: no source-visible + or | tree
  reproduces the pairing (all pairwise/| forms measure 82-275).
- is_master_boot_sector: `pf_s16 index` declared LAST in the local block ->
  pointer webs home r6/r7 correctly (35->25). Residual = same pairwise-merge
  scheduling + store-reload model (orig store-reloads *p_count for the test;
  volatile pf_u32* p_count alone is a no-op, volatile p_start regresses 68).
- chg_ltop: 16 diffs, ndiff 0 — pure regname class.

### FAAttach (10 diffs, invariant)
- orig: index->r0 computed once before bgt, scaled copy->r6 (then arm) / r5
  (else arm); bases->r5,r4. mine: index+scaled fused->r5, bases->r4,r3.
  u32 index / u8 casts / index-in-arm / decl rotation: 10-57, all >= 10.
- PFFILE_GetSFD: 3 word diffs = marshal-order swap of 3 independent setup insns
  ({addi r7,r3,0x40},{mr r6,r28},{mr r29,r4}); operand flips 5-7. Documented.
- PFCACHE_DoWriteNumSectorAndFreeIfNeeded: 9-diff cluster around
  `last_sector`/`num_overlap`: orig computes last=sum-1 via addi on the shared
  sector+num_sector web; all rewrites (`sum-1` first, `p_page->sector+overlap`,
  reordered) cascade 60-228. Committed form stays optimal.
- PFCLUSTER_CombineFiles: 7 diffs = {-1/div/+1 chain r3, sum chain r0} orig vs
  {-1 r0, quot r3/r0, sums r4} mine. temp/polarity/lim-decl: 7-8. Documented.

## Session 6 (GetLFNEntryName match + s8-field decode + retests)

### MATCHED: PFENT_ITER_GetLFNEntryName (43->0 diffs)
- Derived byte-IV decode: orig uses an INDEX-IV (`add rD,rBase,rIV` dst
  recompute + `addi rIV,rIV,N`) instead of MWCC's usual pointer-IV fold.
  Reproduce by writing the byte index NON-AFFINE inside the loop:
  `index = i * 13;` as its own statement + `destination = &long_name[index]`
  (writing `long_name[i*13]` directly explodes into 4 webs, 63-72 diffs).
- Terminator: `long_name[num_entry_LFNs * 26 >> 1] = 0` (recompute from the
  bound field, element-stride arithmetic) kills the element-IV and reproduces
  orig's `mulli 0x1a` + `clrrwi`.
- DECL-FIRST pointer local flipped i<->dst callee homes r29<->r30 to match
  orig (pointer local declared before the index locals). Combined: 0 diffs.

### s8 decode (WRONG SITE -- corrected): FADrvTbl.drive stays `char`
- orig emits `lbz rX,off` + `extsb` reading `table->drive` in FAAttach.
  First theory `char drive -> s8 drive` in types.h is REFUTED by the DOL:
  iplSDVFWorker.cpp (Matching, linked) passes `driveTable.drive` to s8
  params -- with an s8 field it gains extsb at every call site -> hash
  breaks. Orig field is `char`; orig's extsb comes from source-level `(s8)`
  at the USE SITE: `index = (s8)table->drive - 'A';` reproduces the extsb
  AND makes FAAttach's instruction stream ndiff-0 (remaining 10 diffs are
  pure regname: orig index->r0/scale->r6/value->r3 vs mine index->r5 fused).
- pf_stub.o byte-identical either way (already Matching on main upstream).
- RETESTS this session: FAAttach cast-s8/drv-tmp/decl-order all still 10
  (parked reg-rotation); GetSFD start_cluster_p local: still 3 (cyclic
  marshal-order tie confirmed); FindCluster inline-`1<<x`/decl-order/fused
  assign: all still 8 (paired r7<->r8 web swap, regalloc tie).

## Session: Devin Bot lever round (web-lifetime / paired-decl / cyclic-reorder)

Applied the three targeted levers; no flips.

- FAAttach index web (r0 vs r5): tried web-shortening via block-scope,
  expression-in-arg-position, web-lifetime extension — all ≥10 or cascade.
  Pure allocator home choice; parked.
- FindCluster paired r7<->r8 webs: all decl-pair swaps invariant at 8.
- GetSFD 3-insn cyclic marshal: all 6 decl perms + cyclic stmt reorder
  invariant at 3 (marshal order is not source-statement order here).
- PFCACHE_DoWriteNumSectorAndFreeIfNeeded overlap branch (9 diffs):
  orig remats `num_sector+sector` as `add r4,r27,r26` and emits
  last=sum-1 BEFORE overlap=sum-p_sect. Any source form that reintroduces
  the literal sum CSEs to hoisted r31 (228/106 cascade) — remat choice is
  internal. Reassociated/inline forms all ≥106. Parked at 9.
- PFFAT12_ReadFATEntryWithBuf: decl-order rotation `res,sec,err,cur,off`
  DID move it 34->23 (first decl-order win on this unit); residual is a
  second callee rotation (one web homes r31 mine vs r28/r29 orig).
  u16 sector/offset, init'd-err-decl, else-if, mul3 form all worse.
