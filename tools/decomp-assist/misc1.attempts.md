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
