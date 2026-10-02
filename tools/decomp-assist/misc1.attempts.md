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

## w0929 — BS2UpdateInit fold via early &Flags0 def (w1017)

- **BS2UpdateInit 79.88 → 94.0**: `pFlags = Flags0;` after the first
  BS2Report materializes &Flags0 as an early-def web → MWCC anchors a
  dedicated callee reg (r30) to the .bss base, exactly reproducing orig's
  fold: `addi r3,r30,0x800` (Flags1 memset), `addi r3,r30,0x1000`
  (Thread.thread ×2), `addi r6,r30,0x1318` (stack). Frame 0x20 +
  savegpr_29 match orig. Reloc evidence: orig's r30 targets symbol
  `Flags0` (not `...bss.0`) — MWCC anchors the fold to the first .bss
  object when an &Flags0 web exists; without one it remats per-object
  (Flags1/Thread separately) instead of folding.
- **Residual (9 filtered diffs)**: (a) the pFlags store is +2 insns orig
  provably lacks (store-run order matters — best fuzzy is pFlags right
  after first BS2Report; before MemAllocator or after EntriesCount are
  ~91); (b) orig's stack-top arg is two-step `addi r6,r30,0x1318` +
  `addi r6,r6,0x1000` — `&Thread.stack` as a distinct web then +sizeof.
  MWCC folds `stack + sizeof` into one addend (memberoff+size) on the
  live &Thread web (r3+0x1318) under every form tried: decl-init local,
  += reassign, (u32)/(u8*) casts, literal 4096, `(u8*)&Thread+sizeof(Thread)`,
  `&arr[sizeof]` — all fold. The two-step needs &Thread.stack materialized
  BEFORE arg1's &Thread web — scheduler-internal eval order, no lever.
- pFlags semantic: Init defaults the flag-pointer to Flags0;
  UpdateThread rebinds to Flags1 (line 418). Plausible init, honest C —
  but orig's Init has no pFlags store, so this is the "early-def"
  substitute for orig's internal fold trigger.

## w1018 — odh: setQuantizationTable flip + symbol-name pairing

- **cdj_c_setQuantizationTable → 100%** (99.57): `temp = 0x4000000 / temp;`
  `master->quantizationTables[...] = temp;` — the result-through-temp web
  split puts the division result back through `temp`'s web, matching
  orig's reg layout (0x400 const → r10, byte load → r11). Plain
  `0x4000000 / temp` inline in the store kept a 3-reg split.
- **symbols.txt literal pairing for odh .sdata2**: renamed orig's
  lbl_816945A0..C0 float/double literals to the emitted @NNNN names —
  the renames propagate into orig .o on resplit and pair with my
  emitted symbols (LineConv11's 10 symbol-name diffs eliminated).
- **Residuals**: LineConv11 98.08 (pixel/pixelSource web homes — pixel
  callee-pinned r25 in orig, volatile r8 in mine; lbzux ptr-update
  fused into byte0 load both sides, only reg homes differ);
  huffmanCoder 98.77 (same EmitBit arg web family — orig reuses the
  `code` load reg destructively for srawi, mine keeps it in a 3rd reg);
  colorConv 98.63, decompressLoop 99.67, huffmanDecoder 95.57 — all
  the same documented web-rotation family.

## 2026-10-02 — BS2Mach data carving + CheckBS2/DivideCallback decodes

### NEW TECHNIQUE: symbols.txt inner-literal carving (merged literal runs)
Orig's splitter merges contiguous unlabeled literal runs into ONE lbl_ object
(BS2Mach .data had lbl_81645DE4 @0x3c size 0x3b8 covering ~35 separate string
literals). Adding a symbols.txt entry at EACH inner literal's DOL address
(`@NNNN = .data:0x81645DXX; // type:object size:0xYY data:string`) makes the
splitter carve the run into separate objects at exactly the boundaries my .o
has — offset+size pair. Renamed the 3 merged-run start lbl_ to my first
literal's @name, added 84 inner entries (also 4 jumptable + 4 sdata renames).
Result: .data fuzzy 16.1 → 91.1% (remaining = jumptable relocs into the
unmatched fns). matched_data measure unchanged (pairs count completeness).

### CheckBS2CommandStatus 95.46 → 99.51 (1-insn left)
- `CacheCommandComplete = NandPending` → `= 1` (volatile global read forced
  an extra lwz; orig wrote literal 1).
- Store-interleave decode: orig emits `stw NP; lwz CL; stw CC; addi+stw CL`
  — the CC store lands INSIDE the CacheLength update. Reproduced with a
  temp for the new length: `{ u32 newLen = CacheLength + X;
  CacheCommandComplete = 1; CacheLength = newLen; }` — the temp pushes the
  CC store between the operand load and the final add/store.
- Case 0x12 (OSRoundUp32B): orig computes `(CacheLength + round) + 32` —
  `add` then `addi 0x20` — but `round+32` CSE'd into newLen when the Async
  arg had the identical `OSRoundUp32B(X) + 32` text. Broke the shared VN by
  writing the arg's scaling as `<< 3` instead of `* sizeof` — newLen then
  emitted orig's add+addi shape and the whole 3-web rotation collapsed to
  1 insn. Residual: orig's `stw CC` fills the load-use gap right after
  `lwz partitionCount`, mine sits one slot later (scheduler freedom;
  `count` locals rotate the whole allocation — rejected).

### BS2NANDDivideCallback → 100% FLIPPED
- `static u32 CancelNand` → `static volatile u32` — the volatile
  NandCompletion fp-load was hoisting before the plain CancelNand store;
  volatile-volatile ordering pins it after (matches orig's emit order).
- Per-site arg-temp decode: `{ u32 rem; ...Report...; rem = NandLength -
  NandTransferred; ret = NANDxAsync(..., rem, ...); }` — the temp's
  computation emits the subf-operand loads FIRST (orig's marshal order),
  vs inline arg3 which made MWCC load arg1 first. A SHARED `remaining`
  local crosses calls and callee-pins (regresses to mass rotation) —
  per-arm temps die after the call and stay volatile.

### Twins BS2NANDDivideReadAsync/WriteAsync 95.74 (1-insn each)
Orig emits `lis r6,cb` BEFORE `lwz r3,NandFile`; mine swaps. Per-site
`NANDCallback cb` local folds — MWCC rematerializes the constant at use.
Pure scheduler placement of an independent lis — documented tie.

### BS2StartGCGame 96.75 residual
- `time = (OS_BUS_CLOCK >> 2) * (OSTime)seconds` — operand order fix
  (orig mulhwu(bus4,sec) not mulhwu(sec,bus)).
- Head weave: orig bundles `li 1, lis r30, lis r31, stw, addi r30, addi
  r31` — splits webs around the StartingGame store. Not volatile-driven
  (tried volatile StartingGame — no-op). Scheduler weave, no lever.
- Mul-chain reg rotation: orig rtc-load→r5 / seconds→r7 / bus4→r5 vs mine
  r0/r5/r7 — eval order identical, homes rotated; local forms all regress.

### BS2UpdateInit fold residual (documented, unchanged)
Orig r30=&Flags0 materializes in the prologue and EVERY .bss address folds
onto it (&Thread = r30+0x1000, &Thread.stack = r30+0x1318, then +0x1000
as a separate pointer-arith addi — NOT folded into the member offset).
Mine anchors &Thread.stack+size onto the &Thread web (r3+0x1318). 7
source forms all fold identically. Orig's fold anchor = section-base
(Flags0@bss+0); my `pFlags = Flags0` store reproduces the r30 web at +2
insns (orig has no Init-side pFlags store — its fold trigger is internal).

### BS2StartGame / BS2StartGCGame shared head weave (both ~7 diffs)
Orig emits `li r0,1; lis r29,lis r30; stw r0,StartingGame@l(r29); addi r29;
addi r30; addi r3,r29,0x840; lwz state` — the StartingGame store folds onto
the raw lis-half base web (its own @l offset) BEFORE the CoverBlock addi
exists. Mine hoists `addi r3,&CoverBlock` above the store and folds the
store onto r3 as `(SG-CB)@l(r3)`. Volatile StartingGame/vu32 HW reg/stmt
reorder/anon base all no-op — batch-vs-lazy base materialization is
scheduler-internal. StartGame also has the diAddr r3↔r4 2-web rotation
(diBits built `li 2; ori 4` — orig binds base r4/val r3, mine swapped;
remat'd-base and decl/stmt reorder all keep r3-first binding).

### BS2Tick 98.16 (1940 insns, 1124 diff lines)
Mass callee-window rotation: orig savegpr_26 (17 callee regs live) vs mine
_27 — ONE extra web pinned. Clusters of `lis rX,-0x8000` +member-offset
loads identical but bound to different callees (r26↔r27). DvdProgress
store weave same family as above. Finding which web orig remat'd instead
of pinning = the remaining decode; 1940-insn scale, not yet found.

## 2026-10-02b — odh s32-width + mullw operand order; BS2UpdateInit arg4 split

### odh decodes (kept)
- `s32 width` in cdj_c_colorConv: binds the width web to r8 (orig) vs r7
  (u16) — volatile-reg class shift from the wider type. 36 diffs = floor;
  remaining is dim/mask r7↔r9 + cbPlane/stride r22↔r29 pairwise swaps —
  every decl-order permutation fixes one web and rotates the whole map
  (padMask temp 38, stride-decl-last 58, ternary 58 — all worse).
- decompressLoop: `blocksWide * (blockY << 6)` operand order fixed at the
  ~1397 site (orig mullw(bw,by6) — had written by6-first). 86 diffs = pure
  web rotations + add-operand commuting (MWCC commutes add operands by web
  availability — source order can't pin them).
- huffmanCoder: 3x repeated lwzx/split sites — orig keeps entry in the
  table-base reg and splits lo→r0/hi→r5-reuse; rotation family, `|`
  operand swap tested worse (38 vs 36).

### BS2UpdateInit residual (39 diffs, precisely characterized)
- Orig NEVER stores pFlags in Init (UpdateThread sets it later) — but my
  `pFlags = Flags0` store is the only source form found that materializes
  the &Flags0 fold-base web. Without it: 63 diffs (all .bss folds collapse
  to per-access lis). With it: +2 insns net-1 (73 vs 72). The stw's VALUE
  needs `addi r0,r30,0` — MWCC won't reuse r30 directly for the SDA store.
- arg4 two-step: orig emits `addi r6,r30,0x1318` (&Thread.stack) then
  `addi r6,r6,0x1000` (+sizeof) — arg4's &stack VN materializes BEFORE
  arg1's &Thread (marshal eval order), so the +0x1000 can't merge into
  the live &Thread web. Mine emits arg1 first, then folds arg4 to
  `r6,r3,0x1318`. Named stackTop/stack locals, early assignment, split
  stmts, &arr[i] — all fold to the single addi (MWCC remats the VN to the
  cheapest form at use site).
- Store-first ordering (before BS2Report): 47 — worse.

### Twins (95.74, 1 insn each) — scheduler tie confirmed
Orig materializes the callback `lis r6` FIRST in the else-arm marshal
(before all arg loads); const-arg placement is scheduler freedom. `&`of,
per-site temps (changes marshal order not the lis slot), branch-polarity
swap (worse — arm order regresses). Same class as CheckBS2's `stw CC`
one-slot residual.

### BS2StartGame/StartGCGame shared head weave + diAddr
`StartingGame = TRUE; while (CoverBlock.state)` — orig stores via
`StartingGame@l(r29)` before the CoverBlock addi materializes; mine folds
the store onto the r3=&CoverBlock web. volatile decl / vu32 HW reg /
stmt reorder / anon base all no-op. diAddr r3↔r4 swap: diAddr/vu32/anon-
base/decl-order all keep base-first binding.

## 2026-10-02c — BS2Mach .data name-pairing complete; jumptable residual is code-bound

- All 95 .data literal objects now pair: renamed orig's carved labels in
  symbols.txt to MWCC's emitted names (@NNNN numbering) offset-for-offset.
  Names, offsets, sizes, bytes AND relocs are identical — the section is
  content-complete (mine 0xbcc vs orig 0xbd0 = one 4B alignment pad tail).
- matched_data stays 155504/158528 because it only counts 100%-fuzzy
  sections. .data fuzzy 94.03 is bounded by the two BS2Tick jumptables
  (@4359/@4358): their entries resolve to `BS2Tick+<case-offset>` and my
  BS2Tick is 0x14 shorter at those labels — every label-target diff is a
  code artifact, not an extraction artifact. .data can only complete after
  .text does.

### Getter_ (wiisetting's only code blocker, 28 diffs = 2 regname pairs)
- Loop1 `i` (FORM_ID_SECURITY_KEY): orig r26, mine r25.
- Loop2 `i` (FORM_ID_DUMMY_SECURITY_KEY): orig r31, mine r25 — orig pins
  it at the deepest callee reg (more callee webs live in that region).
- Tried: for-init decl (scoping error — i used after loop), decl-before-
  memset (no-op), shared `int i` at switch scope (42 — worse). Baseline
  stands: per-case `int i` decls.
- Unit is Equivalent — orig .o links; this is score-only.

### Twins/CheckBS2 1-insn slots — volatile already semantically applied
`CancelNand`/`CacheCommandComplete` are `static volatile`/`vu32` globals
already (callback/cache-command flags — genuine async semantics). The
lis/stw materialization slots are pure scheduler order, no further lever.

## pass 2026-09-30b (BS2Tick callee-window + Getter_ rotation retry)

### BS2Tick — bootArea decode LANDED
- orig emits `_savegpr_26` (6 callee webs). Decoded the 6th web as TWO separate
  `0x80000000` webs in case 9/10: r26 = `bootDisc` field reads live across the 4
  strncmp calls, r27 = the strncmp arg base. `char *bootArea` local assigned
  inside `if (bootDisc->rvlMagic == 0x5d1c9ea3)` and used as the strncmp arg
  reproduces the two-web structure; savegpr_26 matches. Raw literal → volatile
  `lis` (wrong); fn-scope shared bootDisc → regression.
- Arm-layout: `if (GamePartition != 0) {State=37;} else {State=54; break;}` —
  orig wanted beq-to-out-of-line-arm. LANDED.
- Hoisted field: `u32 gamePartition = ((DVDPartitionInfo*)GamePartition)->partition`
  local at case-0x25 top → orig loads field pre-BS2BootFromCache branch. LANDED.
- `BannerAllocation + 0x20 - (BannerAllocation & 0x1f)` → orig's clrlwi+addi+subf
  (OSRoundDown32B emits rlwinm+addi = wrong codegen). LANDED.
- `u8 streaming` cached local (block-top decl, C89) — near-match order.
- `*(vu32*)0x8000002c`/`*(vu16*)0x800030e6` qualifiers — no-op, kept (semantically
  justified HW-reg accesses).
- Progress: 1935→1938 insns vs orig 1940; text diffs ~1130→1123.

### BS2Tick residual — all verified scheduler/web-ordering family
- o249/254: orig remats `lis -0x8000` per-block (3 block-local webs) vs my CSE'd
  shared r4 web. Const-CSE scope is allocator-internal.
- o1151: `bge;b` vs `blt` titlePrefix<U — MWCC always folds to blt (3 forms tried:
  nested if, duplicated tail, label-inside-arm — all emit blt).
- o40/480/1470/1620/1831: store-value web bound to arg reg (r6/r4) + li-const
  hoisting order — statement-reorder variants all no-op or regress.
- bootDisc-in-0xb r26 pin vs my r3; r26↔r27 binding swap; &0x800030d4 r6 vs r0.

### Getter_ (www_wiisetting) — 28 pure regname diffs, all levers exhausted
- Tried: shared fn-scope `int i` (42-regression), early-init before surrounding
  calls (32, worse — orig emits init at loop head), while-loop form (identical
  codegen), case-block scope decl (identical), for-init decl, decl reorder.
- Orig puts loop-B `i` at r31 — orig frees r31 (string-base web) just before the
  loop; MWCC's global ordering gives the loop counter the freed deep slot. Mine
  consistently picks r25 (lowest free). Deterministic allocator ordering; no
  source-level lever found that shifts the class without rotating everything.

## pass-2026-09-30c — UpdateThread volatile decode (verdict: landed)

`volatile int State` + `static vu32 EntriesCount` — both are thread-state globals
(State is read by BS2UpdateState/BS2GetUpdateEntry getters from other threads;
EntriesCount is the entry-count the getters expose). Semantically justified, same
class as the BS2Mach callback flags. Effect:
- Orig emits per-exit `li 5; stw State` at the two MEM2-default sites — mine had
  DCE'd them (selection_done's `if(EntriesCount==0)` stores State=5 anyway).
  Volatile EntriesCount also produces orig's `stw r17; lwz r0` store-then-reload
  of EntriesCount where mine forwarded the reg value.
- UpdateThread 904→909 insns (orig 913), diffs 959→505, fuzzy ~92→94.30.
- Broader volatile set (StartUpdate/CancelUpdate/RebootRequired/CurrentEntry/
  ContainsSeatTitles/UpdateImportState/UpdateImportResult/pEntries/pFlags/
  MemAllocator) = -0.45 fuzzy vs the two-var set; UpdateProgress volatile adds
  +9 insns (overshoots 913→922, diffs 505→521). All reverted; kept exactly
  State + EntriesCount.

Residual (all documented ties): ~500 regname diffs — r15↔r18/r19↔r14/r22↔r23
web rotations; 4-insn deficit = orig's per-site `li r3,0`/`lwzx` reloads
(marshal-order + aliasing ties); no structural gaps remain — store/load order
and branch shape now align.

## pass-2026-09-30c — Getter_ web-binding tie (verified, 14 word diffs)

Getter_ is instruction-identical (609 insns both, ndiff 0, relocs identical
modulo symtab index). Entire residual = 14 word diffs, two sub-cases:
- DUMMY_SECURITY_KEY loop IV `i`: orig r26, mine r25 (pString-load webs swap
  r25<->r26 to compensate).
- EUR-region LUT loop IV `i`: orig r31, mine r25. `li r31,0` at orig 0xb68 is
  born with r25-r30 all occupied (orig holds extra callee webs live there).

Orchestrator's post-loop-use theory for r31 REFUTED: orig's EUR `i` dies inside
its loop (blt 0xb70 is the loop-back edge; nothing reads r31 after). The deep
pin comes from liveness at birth, not post-loop use.

Scope experiments (all built + measured, reverted):
- Shared fn-top `int i` across SC_KEY+DUMMY+EUR: DUMMY i->r28, EUR i->r26
  (moved but overshot both targets r26/r31).
- Shared SC_KEY+DUMMY only: DUMMY r28, EUR r25.
- Shared DUMMY+EUR only: DUMMY r25, EUR r26.
- `int i = 0` before memset (web spans call): 18 diffs, regression.
- `int i` decl moved before memset (uninitialized): no change (14).
- `for (int i = 0;` init-decl: doesn't compile (i used post-loop).
Conclusion: orig's deeper pins require extra callee-pinned webs that no decl-
scope form reproduces; allocator-internal ordering. Documented wall.

## pass-2026-09-30d — DUD titleId web decode (iplESMisc)

DeleteUnauthorizedData 87.76→89.53, insns now EXACT 449/449, diffs 240.

Root-caused the tail-block deficit: orig does NOT hold `titleId` in a local
u64 — it re-reads `*(ESTitleId*)((u8*)titleIds + titleIdOffset)` per use:
- ES_DeleteTitle marshal = `add r4,r28,r24; lwzx r3; lwz r4,4(r4)` fresh load
- memset/GetTicketViews section loads the pair ONCE into callee r15/r16
  (`lwzx r15,r28,r24; lwz r16,4(r4)` at 0x223c) which serves ALL later
  OSReport/GetTicketViews marshals (`mr r7,r15; mr r8,r16`).

Winning source form:
    ES_DeleteTitle(*(ESTitleId*)((u8*)titleIds + titleIdOffset));
    ESTitleId titleId = *(ESTitleId*)((u8*)titleIds + titleIdOffset);
    // all later uses via titleId

Failed variants: (a) `ESTitleId titleId = *(ESTitleId*)(...)` single local
(BEFORE this pass's edit — MWCC emits a stack struct copy + extra pointer
web: 448 insns, 262 diffs); (b) `titleId = hi<<32|lo` built from the live
u32 pair — cleaner regs (441 insns, 89.10) but loses orig's reload shape;
(c) inline deref at ALL 4 use sites — 450 insns, fuzzy 85.52 (reloads
can't fold into the single callee pair).

Orig's u64 compare-tree idiom also verified: hi-const base materialized
once (`lis r23,0x00010000` then `addi r0,r23,{1,8}` per test), lo-consts
via `r14 = lis 0x4449` + `addi r3,r14,{0x5343,0x534b}` or `lis+addi`;
each equality test = xor/xor/or./beq; ordering tests = subfc/subfe/subfe/neg.
Mine already matched that shape.

Residual 240 diffs = callee-web rotation (titleIdHi/Lo pair r21/r22 vs
orig r19/r20, ret marshal homes, ticketViewList/heap regs) + the 1-insn
`addi r?,r?,8` extra offset web — same allocator-tie family as the rest
of the leaf.

## pass-2026-09-30e — UpdateThread lwzx reload + wpformatter def-order

UpdateThread residual rechecked: orig emits TWO `lwzx r0,r18,r4` loads of
`discEntries[UpdateProgress].type` (0xce8 + 0xd00) — mine CSEs to one and
reuses r0 across the block edge. Tried `CurrentEntry->type` for the second
check → emits `lwz r0,0(r3)` (wrong form, +1 insn, reverted). Orig's second
lwzx is a non-CSE'd re-read of the same indexed expr — a value-numbering
artifact with no clean source form found (banned volatile-cast would force
it; skipping per owner rules).

wpformatter prologue ordering characterized: orig binds buff_end→r15
(deepest callee pin) and the rodata-pool base→r16; mine binds pool→r16,
buff_end→r25. Both are prologue-materialized consts whose addi order
differs by one slot (r16-addi before buff_end-addi in orig). Tried
uninit-decl + assign after `chars_written = 0` → materialization position
unchanged (MWCC hoists loop-invariant consts regardless of def site).
Same 3-web rotation wall; reverted.
