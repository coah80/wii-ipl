# misc1 attempts

## BS2Update (src/BS2/BS2Update.c) — data ~99.24, code ~92.6
- .bss decode SOLVED: 5 separate non-static GLOBAL decls, NOT a packed work struct.
  `u32 Flags0[512]`, `u32 Flags1[512]`, `UpdateThreadData Thread` (OSThread 792B +
  `u8 stack[4096]` + `u64 reserved` = 4896B), `BS2UpdateHeader UpdateHeader0/1` (32B).
- .bss EMISSION ORDER = first-use in .text order (decl order irrelevant — verified by
  scramble). orig order Flags0,Flags1,Thread,UH0,UH1 requires Flags0 referenced before
  Flags1. `pFlags = Flags0;` at Init top materializes &Flags0 first → exact orig layout.
  The store is +1 insn vs orig (73 vs 72); insn-free alternatives don't materialize.
- `sizeof(Thread.stack)` must be 0x1000 (orig `li r7,0x1000`) → stack[4096] + 8B tail.
- UpdateThread: 635-diff web-rotation mass (orig bases r21/r22/r26 vs mine r15/r19/r23;
  index/counter webs r16-r20 vs mine r14-r21) — allocator-internal tie family.
- Init residual: r30-vs-r3 base choice for Thread args + extra stw — same family.
- .sbss caps at ~79%: orig's 4 anon objects are literally named lbl_81698B10-1C in the
  orig .o symtab; semantic decl names can't match (rule 1 bans lbl_ names).
- `.data` tail (orig +5B `780a000000000000` f64) = splits-boundary extraction artifact.

## symbols.txt naming lever (w1003) — VERIFIED WORKING
- Renaming lbl_XXXX symbols.txt entries to semantic names propagates into the
  extracted orig .o via the splitter (touch config.yml or it won't resplit).
- Data pairing = RAW SYMBOL NAME equality between the two .o symtabs. Both sides
  need a same-named symbol: orig via symbols.txt rename, mine via a real decl.
- BS2Update .sbss: 4 anon objects named RebootRequired/ContainsSeatTitles/
  UpdateImportState/UpdateImportResult -> data 10488/10488 (was 79% capped).
- iplESMisc .sdata: 5 objects named to my emitted names (__FUNCTION__$NNNN,
  @17944 for "%s%s" literal) + last object size corrected 9->8 (orig extent
  included the section pad) -> data 4416/4416.
- www_wiisetting .data: lbl_816440A0 (0x38 merged) split into 4 interior entries
  matching my MSG_* / Message decls -> pairs; section now scores (2.05%).
- Non-pairable: anonymous pooled literals/jumptables on MY side (@NNNN) — renaming
  orig alone gives no pair (verified: wiiSettingName rename, no score move).
  Lifting needs real named decls — wiisetting is Equivalent-linked so source
  edits are off-limits; its .data string/jumptable gap (~97%) is an
  extraction-boundary artifact (orig merges pooled literals into labeled runs).
- BS2Mach .data same artifact: orig merges ~50 literals into few GLOBAL lbl_
  objects + 4 jumptables.

## AxAdpcmPlayer::start (99.78) — parked
- 14 regname diffs: const-zero web r25<->r26 + one r29/r30 mr mirror.
- Tried: remove dead NULL-init (no-op), move sSysPauseFlag store (cascade -300),
  p* decl rotation (26 diffs, worse). Same allocator-internal family.

## odh (src/system/odh.cpp) — fuzzy 99.4, data 100%
- Removed ODHEncodeRGBA8, ODHEncodeY8U8V8, ODHDecodeY8U8V8 — absent from orig .o.
- All 6 sub-100 fns verified via raw word-diff (df.py normalization had masked them):
  register-web rotations throughout. setQuantizationTable = 5 words (r10<->r11 web),
  colorConv = 18, huffmanCoder = 30, decompressLoop = 62, huffmanDecoder = 140+ —
  allocator-internal tie family, identical insn streams otherwise.
- LineConv11: 2 sched diffs (lis 0x4330 placement) + lbzux operand-web rotation —
  same family.
- Tested symbols.txt semantic rename of a pooled literal (lbl_816945A0): no fuzzy
  effect — objdiff does not resolve .o-local syms through the map. Reverted.
- `.data` tail 5B artifact (hufftreePtr extraction boundary).

## BS2Mach / iplSound / www_wiisetting / AxAdpcmPlayer / iplESMisc / wprintf
- Unchanged from prior parked states (see singles/bs2 attempts + in-tree notes):
  BS2Mach 7 fns 95-98 (u64-mul, DI-reg, marshal-order walls); iplSound sinit 83.69
  (bare-array __construct_array emission wall); wiisetting Getter_ 99.45 (i→r31 web);
  AxAdpcmPlayer start 99.78 (r25↔r26); iplESMisc DUD 88.79 + 32B data; wprintf 99.27
  (full rotation). All allocator-internal or emission-model walls, no banned tricks.

## w1004 — resume findings

### symbols.txt lever — extended
- Renamed `lbl_81644834` → `strProps__Q23www10wiisetting` (0x64 at .data+0x794): paired → wiisetting matched_data 1180→1280. All legit named pairs now done for that unit; the rest is anon strings + jumptables (unpairable both sides).

### huffmanDecoder (odh) — word-diff analysis
- Diff = fn-wide web rotation, ~140/306 insns. Root cause isolated: PAIRWISE web-class swap — orig homes the hot running-bit web (bitOffset→bitCountAndMask) in callee r31 and `sourceCursor` (bitstream ptr) in VOLATILE r12; mine gives cursor callee r27 and the hot web volatile r10.
- Orig emits load order bytesConsumed(0x20)→bitCount ptr(0x1c)→bitstream(0x10) identical to mine — web creation order same; pure allocator binding difference.
- Tried: decl-order swap of the three init stmts (2 orders: 171 diffs both, worse), s32-vs-u32 types on bitOffset/bitCountAndMask (273, codegen change), removing the maxHuffmanBits copy local (171). All reverted to 140-diff base.
- Root cause guess: MWCC's cost model ranks the cursor web higher in my IR — no source-level lever found that changes class assignment without changing codegen.

### AxAdpcm start — zero-web variants (orchestrator req)
- Pairwise swap: orig const-zero→r25, axSrc stack-addr(+0x28)→r26; mine zero→r26, addr→r25. Plus r28↔r31 mirror web.
- Tried: memset(axSrc.last_samples,0,8) → 18 diffs (store form differs slightly, reverted); assigning fields from sSysPauseFlag → 148 (flag is .sdata load, not const-zero, reverted).
- 14-diff base stays best.

### iplESMisc DUD — verified structural
- 449 vs 438 insns, ~300 word diffs: same family — orig's `ret` web is callee-pinned (r27) producing extra `mr` copies after every call; different .data base web (r21 vs r26). Decode structure is right; web pinning differs fn-wide.

### Remaining state — everything else at documented walls
- All data sections now 100% except www_wiisetting .data (anon literals/jumptables unpairable — extraction-boundary artifacts) and BS2Mach .data (None — merged pooled-literal objects, same artifact).
- All code residuals: allocator-internal web-rotation/marshal-order ties or the above.

## w1005 — live-web-window lever + DUD return decode

### iplESMisc DeleteUnauthorizedData — signature decode (REAL find)
- Orig's `mr r3,r27` immediately before `_restgpr_14` = **the fn returns `ret`** — signature is `s32` (orig: `static s32`, not void). Decl + def updated; `return ret` at end.
- Effect: ret web is now callee-pinned (mine r25, orig r27), epilogue now matches (`mr r3,r25` vs `mr r3,r27`), per-call `mr` copies align structurally.
- Fuzzy 88.79→87.76 (word diffs ~300→339) — fuzzy dipped but the structure is semantically correct (orig really does return a value). Residual = regname rotation + mine emits a second const-zero web (orig CSEs titleCount=0 + titleIds=NULL into one `li r28,0`; mine emits `li r0,0` + `li r26,0`).
- Tried merging the zero webs: decl reorder (405, worse — reverted), `titleIds=(ESTitleId*)titleCount` (339, no change — reverted).

### huffmanDecoder — deeper web analysis
- Orig's callee webs: r23(tableIdx) r24(huffmanTables — reused ×3 for [0],[1],[0] loads!), r28(bytesConsumed) r29,r30(decodedSymbol) r31(bitCount web). Cursor = volatile r12.
- Mine: r24(temp) r25(tables[0]) r26(tables[1]) r27(cursor!) r28 r29 r30(bitCount) r31(decSym) — one extra callee web vs orig's reg-reuse.
- Orig reuses ONE callee reg for the 3 separate `huffmanTables[*]` pointer loads (short-lived webs, reg recycled); mine homes them in 3 different callee regs → pushes cursor into callee, pushing hot web to volatile.
- Tried removing `predictors`/`predictor` locals (extra-web hypothesis): 171 diffs — reverted.

### AxAdpcm start — extra-web variants
- Removed `chanData` local (pass chanDataBuf[i] twice): 208 diffs — reverted.
- Added `AdpcmCoeffs* coeffs = pCoeffsBufB[i]` local (cached member ptr reused ×18): IDENTICAL 14 diffs — kept (more readable, plausibly orig's own form).

## w1006 — AxAdpcm start decode: member-load + direct-array webs

`start` 14 diffs -> 1 (fuzzy 99.962). Verified decodes:
- `mpBNSBuffer = (Header*)data;` member store; `sSysPauseFlag = false;` then
  `if (mpBNSBuffer == NULL)` — orig emits `lwz r0,0(r3)` member RELOAD for the
  check (the `stb` to the global breaks member CSE), while field reads go
  through `(Header*)data` (param r4). No `head` local.
- Removing the `pCoeffsBufB`/`pAxvpbBuf`-mixed structure: direct
  `coeffsBufB[i]` uses collapse the coeffsB access to ONE base web (r26) and
  resolves the r25<->r26 pairwise swap (const-zero vs coeffsBufB base).
- symbols.txt: orig `lbl_` literals renamed to my emitted names
  (`@4196/@4197/@4202` sdata2 fp literals, `voiceVe$3399` sdata) — pairs all
  name-bearing diffs. Numbers are MWCC anon-counter values; rename must track
  source edits (counter shifts on decl changes).

Remaining 1-diff: hoist-block emits `addi r26,r1,0x28` (coeffsBufB base) one
slot after `addi r17,r1,0x38` (axVoiceBuf base) vs orig's ascending-offset
order. Tried: dead/live pCoeffsBufB alias (rotation), decl-init form, pointer
decl order (r16/r17 rotation), array decl swap (breaks stack offsets),
pAxvpbBuf removal (remat + mass rotation), in-loop assignment (315 vs 316).
Scheduler-internal tie; no source lever found.

huffmanDecoder: `u16* table` single-web decode (reassigned per site) regressed
(185 vs 140) — MWCC SSA-splits the local, adds a 10th callee web
(_savegpr_22). Reverted.
iplESMisc DUD: u64 `titleId` local + `(u32)((titleId>>32)&0xFFFFFF)` /
`NANDTitleIdLo` arg forms — neutral (575 disasm-diff lines both ways); fn-wide
reg-rotation, not localized. Reverted.

## w1007 — wprintf __wpformatter decodes (99.27 -> 99.38)

- `num_chars = ((long)buff_end - (long)buff_ptr) / 2;` — orig emits the
  signed byte-diff divide-by-2 sequence (subf + srwi 0x1f + add + srawi); the
  plain `wchar_t*` pointer diff emitted subf only.
- `double2hex(long_double_num, buff + 512, *fmt_ptr)` — orig rematerializes
  `addi r3,r1,0x480` (r1-relative), same as the long2str/longlong2str/float2str
  buf-arg sites; `buff_end`/`buff_end + 1` forms emit member-reg math instead.
- Remaining 130 diffs are a pure 3-web callee rotation: orig binds
  buff_end->r15 / buff_ptr->r25 / numChars->r24; mine r25/r24/r15. Identical
  insn stream otherwise. Levers tried: buff_end/buff_ptr decl order, &buff[511]
  vs +511, buff_ptr=buff init, register/const qualifiers, buff_end+1 reuse —
  all no-op.

## w1009 — BS2Update post-rebase (volatile globals + base-web fold)

- `static volatile s32 rc` (decl-site volatile, same mechanism as upstream BS2Mach NAND globals): orig reloads `rc` per access site — 6 loads, volatile decl matches exactly. UpdateThread 92.3 → 93.35, insn count 902 → 904 vs orig 913. `UpdateProgress` volatile also tried — overshoots (20 loads vs orig 11): orig MIXES a callee-cached local with per-access reloads inside the import loop — not fully volatile. Reverted to plain.
- symbols.txt: `@1814/@1826/@1851/@1858` renames pair UpdateThread's sdata strings (propagates into orig .o via resplit).
- BS2UpdateInit: orig keeps `&Flags0` as a callee base web — `addi r30`+offset for `Flags1`(+0x800), `Thread.thread`(+0x1000), `Thread.stack`(+0x1318→+0x1000 top). MWCC won't hoist a single-use address web; `flags` local, `Flags0 + N` expr, and merged `Flags[1024]` all remat per-site. Orig had 3 separate LOCAL bss objects, so the fold needs a source-level `&Flags0` value used ≥2× in Init — none found. Parked (72 vs 71 insns).
- UpdateThread residual: orig uses a distinct `li r15,0` web for the 3 scratch-init stores (r15 = its first-born callee web) vs my shared r0 — allocator priority tie.
- BS2Mach BS2NANDDivideCallback: swapped `NandBuffer += result` before `NandTransferred += result` — resolved the r5↔r6 pairwise web swap (~30→16 diffs). Residual: `li r3,0`/NandCompletion-load scheduling swap + NT/NL/NF marshal order at 3 call sites (arg-eval order, compiler-internal). `u32 remaining` temp regressed (122 vs 128 — orig recomputes per-site).
- odh near-100s (decompressLoop 99.67, setQuantizationTable 99.57, huffmanCoder 99.08, colorConv 98.64, LineConv11 98.08): all verified pure regname/operand-order diffs — same callee-web rotation family, no decode gap.

## w0929 — BS2UpdateInit fold mechanism + AxAdpcm 1-diff (w1015+)

- **`...data.0` literal pool fold**: `extra_cflags=["-sdata 8"]` (configure.py,
  committed) makes MWCC emit `lis ...data.0@ha`/`addi ...data.0@l` — a
  synthesized per-section literal base — reproducing orig's folded string
  codegen AND its exact section layout (.data 0x530 pooled literals +
  .sdata 0x11 with @1814/@1826/@1851/@1858 sda21-addressed smalls).
  `-O4,p` also pools but 4-aligns literals (orig byte-packs 0x16/0x2c/0x42);
  `-str pool` puts all strings in .data@stringBase0 and strips .sdata (orig
  has both); `-str pool,readonly` wrong section; `-pooldata on`, `-common on`,
  `#pragma pool_data/pool_strings` all no-ops or rejected.
- **Orig Init web map**: 3 callee webs — r29=allocator(param), r30=&Flags0
  (.bss fold base: +0x800 Flags1 memset, +0x1000 Thread.thread ×2,
  +0x1318 stack base then +0x1000 size), r31=...data.0 pool — all
  materialized in prologue, savegpr_29 + frame 0x20.
- **Merged-struct experiment** (`static BS2UpdateData UpdateData` +
  member #defines): reproduces orig's .bss fold offsets EXACTLY (struct
  total 0x2360 = orig .bss size) but destroys data pairing — orig .bss
  is carved into 5 LOCAL objects (Flags0/Flags1/Thread/UpdateHeader0/1)
  and objdiff data pairing is raw name equality (10488→104). Reverted to
  5 separate decls. Residual diffs even under struct: base materializes
  mid-fn not prologue (allocator won't dedicate a 3rd callee reg — cost
  model, same 4-use web both sides), one-step +0x2318 vs orig two-step
  +0x1318/+0x1000 (every source form folds — stackBase local, threadData
  local, u64[512] stack, &arr[0]/&arr[512], (u8*)cast — MWCC constant-folds
  all), reg-binding order swap. 15 insns still differ → 79.88%.
- **AxAdpcm `start` 1-diff (99.962)**: orig emits frame-base addis in
  ascending order +8,+0x10,+0x18,+0x20,+0x28,+0x38; mine puts +0x38
  (axVoiceBuf via `pAxvpbBuf` pre-loop assignment) before +0x28
  (coeffsBufB direct, loop-hoisted). Orig's +0x38 is a loop-IV (body-use
  order after coeffsBufB) — implies orig had no pre-loop pAxvpbBuf
  assignment OR used axVoiceBuf[i] directly. Every variant rotates the
  entire callee allocation: remove alias, direct use w/ dead assign,
  2-member struct, decl-init `= axVoiceBuf` (moves +0x38 to fn ENTRY —
  closest alternate ordering), in-loop assignment, decl-first/decl-last —
  all mass-rotate. The web set is exquisitely balanced at the committed
  form. Parked at 1-diff.

## w0929 — AxAdpcm 1-diff RESOLVED + BS2Update lever check (w1016)

- **AxAdpcm `start` SOLVED — 0 diffs, unit flipped to Matching.** The
  winning form: keep `AXVPB** pAxvpbBuf` decl but move its assignment
  INSIDE the loop right before first use
  (`pAxvpbBuf = axVoiceBuf; pAxvpbBuf[i] = AXAcquireVoice(...)`), and
  route ALL in-loop uses through it (`pAxvpbBuf[i]` for the acquire
  store, null-check, and the vpbA/vpbB reads), while the clean_up loops
  keep direct `axVoiceBuf[i]` (orig remats `addi r6,r1,0x38` there).
  The in-loop DEF births the &axVoiceBuf web after coeffsBufB's (use
  order 279<281) so its addi hoists to position 6; the web is still
  callee-pinned (r17) because the named local crosses calls inside the
  iteration. Prior "in-loop assignment" failure mixed `pAxvpbBuf[i]` and
  direct `axVoiceBuf[i]` uses — two competing webs → rotation. Verified:
  fuzzy 100.0 all 13 fns, matched_code 3088/3088, matched_data
  6476/6476, DOL sha1 intact after Object(Matching) flip.
- Also tried this pass: for-init `i = 0, pAxvpbBuf = axVoiceBuf` (same
  swap — init materializes pre-loop), `AdpcmCoeffs** pCoeffsBufB` extra
  alias (84-line rotation — extra live web), pure direct `axVoiceBuf[i]`
  with no alias (191 — &axVoiceBuf demoted to per-use remat, 6th callee
  web lost → cascade), swap roles pCoeffsBufB-alias + axVoiceBuf-direct
  (189 — same demotion).
- **BS2UpdateInit scoped-switch lever: inapplicable** — Init is
  straight-line (reports, version reads, field stores, memsets,
  OSCreateThread/OSResumeThread); the `switch (SCGetProductArea())` and
  `OSGetPhysicalMem2Size()` branches all live in UpdateThread.
  UpdateThread's residual is the 437-line callee-web rotation (orig
  births many distinct const-0 webs r15/r17/r18 + scratch base r22 vs
  my shared zeros r20/r21 + base r23) — not a switch-dispatch shape;
  call structure already identical (3× SCGetProductArea, same sites).
