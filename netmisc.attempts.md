# netmisc leaf — attempt log (agent/w1005/netmisc)

DOL gate: units stay NonMatching → sha1 26116613f624061ba99c8d1a299aaa6efa85670d holds.

## This wave's wins
- NHTTPi_compareTokenN_HdrRecvBuf: 126/124 -> 124/124 insn-equal (+66 regalloc/sched diffs).
  Lever: `if(position<limit){...} return -1;` wrap instead of `if(position>=limit) return -1;`
  early-return — makes the -1 return share the tail (same idiom as sibling fns in the TU).
  `int character` tried: regresses to 122/124 (drops needed extsb's) — orig uses `s8`.

## Open fns (all insn-equal unless noted) — documented walls
- NHTTPi_compareToken (stdlib): 45/45, 8d. Web-color swap: base homes carried `leftByte`
  byte-web in r31 + rightChar-select in r12; mine inverts. `li r7,0x5a`/`li r9,0` order swap.
  Tried: leftLC-first body order (+r30 save, 47/45 revert), char/s8/u8 leftByte, (s8)*left /
  (int)leftByte / *left check operands, entry-hoisted `leftByte=...` before goto (inert),
  `(const s8*)` uniform typing (identical). Wall: which web wins the lone callee slot is
  allocator-internal; base's `extsb. r0,r31` needs the s8-typed shared web pinned r31 —
  every form either pins the wrong web (r31->rightChar) or breaks the carried-web CSE.
- NHTTPi_strnicmp: 51/51, 2d. Pure `li` materialization order: base `li r9,0x5a` before
  `li r10,0`; mine swapped. The 0-web is the subfc/adde carry base for `>='A'`.
  Tried: conjunct swap in LowerCase (breaks the whole subfc/adde idiom -> 47/51),
  a/b lowercase order (12d), decl order a/b (20d). Wall: constant-web numbering.
- NHTTPi_Base64Encode: 119/119, 58d. Insn-equal, unrolled-2x loop. Whole-iteration
  list-schedule interleave: base loads s0,s1 then computes; mine pulls s2 load forward.
  Tried: named c0/c1/c2 locals (+4 insns), operand-order `(s1>>4)+((s0&3)<<4)` (61d),
  `*output++` pointer form (identical 58d). Wall: list-scheduler priority.
- SOGetSockName: 63/63, 3d. memcpy arg-marshal mr order: base r4,r5-load,r3; mine r3,r4,r5.
  Tried: reply-assign before socket store, `&request->address` direct, `size` as 3rd arg
  (still r5-copy at same slot). Wall: arg-copy scheduling.
- SOGetInterfaceOpt: 119/119, 5d. level/option color rotation: base level->r26,option->r25;
  mine level->r25,option->r28. option-store-first flips option to r25 but swaps the two
  stw's emission order (3d, offsets right order wrong). Check-order/operand variants inert.
  Wall: arg-web coloring + store emit order can't both match from this source shape.
- RecvFrom: 174/174, 65d. Uniform +1 arg-window shift (mine r24-r29 vs base r25-r30) —
  base pins one more callee web somewhere; "+1 pinned web" wall family.
- SendTo: ~98% similar family (not diffed this wave).
- md5 ProcessBlock: 306/306, 275d -> best 261d. Whole-fn web-coloring permutation.
  Decoded base's homes: block->r8, const->r9, word->r4, a->r0 (arithmetic-only web wins
  r0; r0 is ineligible as indexed-load base so word can't take it), b,c,d->r5,6,7.
  All-volatile allocation (only r29-31 callee). Moving state loads before/after pointer
  inits, stmt vs decl-init, `&block[*index++]` — allocator homes unchanged (block->r0 mine).
  Wall: which web is "first-created" for r0 is not driven by source order here.
- aes AESiEncryptBlock: 158/158, ~134d; AESiDecryptBlock: 249/251 (-2 insns + big regalloc).
  Decrypt tail: base `xor r0,r5,r0; xor r0,r6,r0` before last stw — 4-term xor-tree
  reassociation differs; not yet decoded. Both fns are the same wholesale-color wall at
  larger scale (unrolled/flat straight-line code, no calls).
- NHTTPi_compareTokenN_HdrRecvBuf residual: 124/124 insn-equal, 66d — "+1 callee web"
  family: base uses _savegpr_25 (pins char byte r25) + frame 0x30 vs mine _savegpr_26/0x20.

## Notes
- Every remaining diff is insn-equal regalloc/scheduling/web-creation-order — the same
  allocator-internal family documented in nwc.attempts.md (waves 14-26) and linkgap.
- No unit is single-fn-blocked; no unit at whole-100% -> no configure.py flips this wave.
