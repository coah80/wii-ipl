
## Pass 3 (w0929 worker session)

### Member-function symbol-name dialect (new lever)
Orig .o symbol names come from symbols.txt metadata, not ground truth. Orig's
`__nupGetBootVersion__FP14ESTitleVersion` used an old no-class-scope `__F`
member dialect; the fn is actually `s32 NUPContextInfo::__nupGetBootVersion(ESTitleVersion*)`.
Writing it as a member fn + fixing symbols.txt to the `__14NUPContextInfoF` name
made objdiff pair it (None → 99.36, insn-identical, 17 regname diffs remain).
Correcting WRONG names in symbols.txt is legitimate (extracted objects never link).

### Re-tested-condition decode (new lever)
`if (x != y) { result = ERR; } if (x != y) { *out = x; }` — re-testing the same
comparison emits a dead second `cmplw`. Took `__nupGetBoot2Version`/`__nupOp`
from 437 to 438=438 structural match.

### MD5 dual-lwbrx STEP
Orig emits TWO `__lwbrx(word,0)` loads per step: first feeds the `>>` (rotate-low)
chain `word + (const + (a+f))`, second feeds `word + const` → `(a+f) + wc` (`<<` side).
Capture order matters: `_xw = __lwbrx(w)` (X side) then `_wc = __lwbrx(w) + *const`
(Y side), `a += f` between decl and use, `(a) = b + (((a)+_wc) << n | (_xw + (const + a)) >> (32-n))`.
Reversed `|` operands pick srwi-base + rlwimi (orig) over slwi+rlwimi. 57.1 → 70.8.
Residual: orig's `word` walks in-place (`addi r4,r4,4`) vs MWCC strength-reduced
`base + 4k` recomputes; post-inc/_wp capture forms don't defeat it. Documented tie.

### `!direct` arm-order (SOBasic RecvFrom/SendTo)
Orig: `if (!direct) buffer = SOiAlloc(...); else buffer = data;` — alloc in-line,
data out-of-line via `bne`. `if(direct) data else alloc` emits opposite layout.
SendTo: `if (direct == 0)` form (not `switch(direct){default/case 1}` which emits
`cmpwi 1; beq`, nor `!direct` ternary which flips arms back). RecvFrom: `!direct`.
Both now instruction-identical (regname-only residual).

### Interface fn-pointer marshal order (hmac — partial)
`context->interface.init(work)` vs `init(context->digestContext)`: reusing the
`work` local matches orig's `mr r3,rX`; recomputing emits `addi r3,ctx,0x20`.
NETHMACGetDigest orig keeps `context->digestContext` in a callee web for calls
1/4/5 and materializes `work` via `mr r31,r30` at first use (web-split copy);
my build rematerializes the addi — 3-insn gap, allocator-internal.

### Cold-block out-of-line (HttpStringFlush — parked)
Orig emits `blt → growth-block` + `b → malloc` (growth block detached, cold).
`if/else`, positive `if`, `!cond` ternary, `goto` forms all normalize to
in-line growth. Same family as the documented select/cold-block walls.

### Base64Encode / ParseServerInfo / nupOp / GetTitleSize / GetBootVersion
All verified: instruction-identical streams (452=452 ParseServerInfo) or tiny
scheduling swaps — pure web-rotation / marshal-order ties, no source lever found.

### AESiEncryptBlock / AESiDecryptBlock / NETAESCreateEx
158=158 / structurally complete — remaining diff is the interleave ORDER of the
16 table-index `rlwinm` extracts vs `lwzx` loads across the 4 ENCRYPT terms
(pure list-scheduler shape); ENCRYPT operand-assoc/order variants don't move it.

## Pass 4 (orchestrator resume — decode walls)

### MD5 base-materialization + increment placement (70.8 -> 79.2)
Orig materializes `&indices` at the round-2 boundary (`lis/addi` mid-function), not in
the prologue — `u32* index` declared at top but `index = indices` assigned BETWEEN
loop 1 and loop 2. Orig also schedules `++constant` inside the step body (each step's
end), not as a separate statement after STEP — `++constant` moved inside the STEP
macro tail. Combined: 70.8 -> 79.2, 307=307 insns. `*++constant`/`*constant++` forms
score higher (75.7) but read constants[1..64] — semantically wrong (OOB on last step),
rejected. Residual: software-pipelining — orig prefetches next-step `lwz 4(rc)` /
`lwz idx` / `lwbrx` into the current step's tail; MWCC won't pipeline with this web
set. Tried: block-scoped round webs (C89 — no for-init decls; block-wrap BUILDFAIL
fixup attempt regressed), `*index++`/`word++` in expr/macro (74.1), block/wptr
elimination via context->buffer32 (70.0), const-1 init (73.1).

### AES extract/load interleave — all forms regress (60.35 stays)
nextA-D temps confirmed (fused per-statement key-xor -> 44). Tried: key+=4 early
(57.4), xor order rev (56.0), next-decl rev (58.7), xor operand swap key^next (56.4),
for(rounds>1) (53.8), *key++ (57.4), reversed xor chain (52.8), right-assoc (56.0).
Orig's interleave mixes extract/lwzx/rotlwi/xor across all 4 terms — MWCC list-
scheduler shape, no source lever found. Documented wall.

### ParseServerInfo — instruction-identical, pure reg rotation (98.11)
Normalized diff = 5 symbol-name artifacts only; raw diff = whole-fn callee-web
rotation (orig binds &locals to r25/r22/r23 webs, mine r24/r25/r27 + one web escapes
to r18). Decl-order rotation inert (all 4 orders = 98.11); per-block start/valueLength
locals regressed (94.09) — shared decls confirmed. Documented wall.

## Pass 5 (orchestrator resume — nup_nhttp gaps)

### NhttpOp/BufFull/HttpStringFlush structure check
All 9 nup_nhttp fns implemented — complete_code 22.6% reflects 3 sub-100 fns' whole
sizes, not missing code. Same for nup (53.4%).

### BufFull 96.44 -> 97.58
done-block store order: `*length = 0; next = NULL;` (orig emits `li r0,0; li r30,0;
stw r0` — separate zero materializations per use). Residual (3 blocks): cmplw
operand order on `received + *length < received` (sum-temp/operand-swap inert),
next==NULL alloc cold-block (`beq→alloc;b→merge` vs `bne` — goto/else forms inert),
req>=0x8000 set-block same cold-block family. Documented wall.

### HttpStringFlush 96.88 — cold-block, all forms inert
Orig `blt→growth;b→merge` out-of-line growth block. Tried: double-goto
(`if(req<total) goto grow; goto alloc;`), single-goto-skip, empty-else — all
normalize to in-line `bge`. Same wall as BufFull alloc block.

### NhttpOp 98.79 — single `li r29,0` placement
Orig rematerializes the `*colon=0`/`*end=0` store-zero fresh after memcpy
(web-split); mine shares headerCopy's NULL web. `'\0'` literal + late-init
headerCopy inert — allocator-internal. Documented tie.

## Pass 6 — md5 ProcessBlock 74.14 -> 81.68/81.71

Two decodes landed:
- `_k = *constant` as a separate temp BEFORE the lwbrx pair (orig emits `lwz const`
  first, then the two word loads — a distinct constant web vs folding `*constant`
  into the _wc expression). 74.14 -> 80.86.
- `_p` pointer capture inside STEP + post-increment args at call sites
  (`STEP(..., word++, 7)` and `STEP(..., block + *index++, 5)`). The `word++`
  evaluates once into `_p`, so both lwbrx see the same address while the pointer
  walks in place — reproduces orig's `addi r4,r4,4` per-step in-place walk
  (vs MWCC's `base+offset` temps from `++word` statements). `wptr` local deleted.
  index++ likewise folds to orig's stride-16/offset form. -> 81.68.
- `(_wc + (a))` operand order -> 81.71.

Rejected: `++(word)` inside shared macro tail (no-op; semantically wrong for
rounds 2-4 anyway), `word[i]` args (type error), xw-before-k decl order (74.13),
(a)+=(f) before loads (buildfix attempt broke), shift-assoc `((_xw + _k) + a)` (79.5).

Residual (32 diff blocks): pure scheduler micro-order — orig prefetches
next-step `lwz const`/`lwz idx`/`lwbrx` into the current step's tail; insn count
306 = 306. Documented pipelining wall.
