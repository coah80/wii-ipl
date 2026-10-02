
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
