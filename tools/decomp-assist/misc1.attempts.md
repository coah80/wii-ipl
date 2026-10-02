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
