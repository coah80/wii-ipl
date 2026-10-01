# iplESMisc.cpp — attempts log (singles leaf)

Final state: .data 100%, .sdata 98.41 (tail-pad artifact: orig's last
`.sdata` object absorbs one pad byte — contents identical), .text 97.70,
30/31 fns. Only `DeleteUnauthorizedData` (85.6) is sub-100.

## Verified decodes

- **`.data` string pool now byte-identical.** Orig emits the three
  fn-name strings `verifySavedataZD`, `DeleteTicketsForce`,
  `InitSavedata` before all of `DeleteUnauthorizedData`'s message
  literals: reproduced with three namespace-scope
  `static char FUNC_*[]` decls (non-const → `.data` at decl position;
  `const` goes to `.rodata`). Callsite literals pass the named objects —
  codegen identical (`addi rX, pool+off` either way).
- **`DeleteUnauthorizedData` structure:** orig's literal order is
  Card1-fail → alloc-fail → Card2-fail → loop strings, i.e. a flat
  `if (ret != ES_ERR_OK) { OSReport(Card1) } else { alloc; if NULL
  {alloc-report} else { list2; if (ret != ES_ERR_OK) {OSReport(Card2)}
  else { loop } } }` head, not nested `== ES_ERR_OK` wrapping.
- **Local layout:** `path[88]`@0x28, `ticketViews[0xe0]`@0x80 (homed
  r29), `fileInfo`@0x160 — decl order path → ticketViews → fileInfo.
  No `path - 8` / `&fileInfo - 0x20` compensations needed.
- **`main.dol` tail of `.data`:** orig's last object absorbs 6 bytes of
  section-alignment pad — extraction artifact, bytes identical.

## Unresolved

- **`DeleteUnauthorizedData` 85.6** (449 vs 434 insns): residual
  regalloc noise (r21-vs-r26 pool home, `ret` homed r27 in orig via
  `mr r27,r3` after each call vs direct r3), the zelda-check `&&` fusion
  (orig `xor`/`or.` single-branch; mine two `cmplwi`+2 `bne`; `&` on
  bools produced `cntlzw`+`and` — worse, reverted), 64-bit title-id
  chain codegen order, and MWCC strength-reducing my
  `*(u32*)((u8*)titleIds + titleIdOffset)` into a pointer-walk
  (`addi r30,8`/iter) vs orig's `lwzx base,offset`.
