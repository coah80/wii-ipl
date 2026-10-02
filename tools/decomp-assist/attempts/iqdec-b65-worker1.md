# iqdec_b65_frv32 / TMCJPEGDEC_decode_iquant (worker1)

Worktree: `/workspace/worktrees/iqdec-b65-worker1`
Branch: `agent/grok/decomp-worker-1/iqdec_b65`

## Scores

| State | Insns | Diffs | Notes |
|---|---|---|---|
| main baseline | 276/276 | **30** reg-only | entry/DC extract + AC coloring |
| this PR (sibling semantics) | 276/276 | **13** reg-only | structural 0 |
| target wall | 276/276 | 13 | AC huff/zztbl/zz permutation |

## Sibling semantics ported (from matching `decode_iquant_rc` C reference under `#else`)

- `u16*` fast indexing in `decodeLongHuffman` / `decodeACHuffman` (`entry = (u16*)(huff_tbl+9)`, `entry += 2`, `limit->bitLength = entry[0]`)
- comma-op `load_buff`: `if (load_ret = TMCJPEGDEC_load_buff(work), load_ret < 0)`
- early `s32* conv_row = (s32*)conv_row_ptr`
- `1UL << r/t`, `extra -= (tmp - 1)` paren form
- bitCount update before bitBuf read on DC/AC extract

These fixed the 17 non-AC diffs (30→13).

## Remaining wall (13 reg-only)

Permutation of 4 callee-saved across AC setup:

| Value | Ours | Target |
|---|---|---|
| `huff_tbl` (pACHuffTbl) | r29 | **r25** |
| `huff_sym` (pACHuffSym) | r30 | **r24** |
| `zztbl` | r24 | **r29** |
| `zz` | r25 | **r30** |

Cascaded: `tmp-1` in r7 vs r6; `zz<<2` index in r6 vs r7.

Insns 0–114 (through `ac_fast` load) are byte-identical. Divergence starts at AC huff loads (115–116).

## Coloring levers tried (≥12) — none beat 13

1. Separate AC-block `ac_huff_tbl`/`ac_huff_sym` → 32 (DC shifted)
2. DC-only block-local huff → 46 (prologue shifted)
3. Fully scoped DC/AC huff (no top-level) → 32
4. Early `zztbl` at function start → 138 (schedule)
5. `zztbl` before huff (before memset) → 32 (schedule)
6. Swap AC huff_tbl/huff_sym assign order → 13 (swapped wrong load order)
7. Swap DC huff assign order → build fail / unrestored
8. Decl reorder huff near zztbl → 17 (DC shifted)
9. `u8 zz` → 36
10. `u32 zz` → 13 (no change)
11. Move `zz = zztbl[idx]` after `load_buff` → 100
12. Eliminate `zz` temp (double `zztbl[idx]`) → 100
13. Huff before `ac_fast` → 14
14. Split `r` into `dc_r` + `r` → 13
15. Null-kill `huff_*=0` before AC reassign → 13
16. DC passes `work->pDCHuff*` directly → 30
17. Sibling decl order + `ac_vl`/`ac_sym` → 96
18. Scope DC HuffmanEntry temps → 33
19. Dummy pad locals → 13
20. Sibling `*(s32*)((u8*)block + zz*4)` store form → 13
21. `zztbl` first in decl list → 36
22. Coalesce huff_tbl via reassigning `dc_fast` → 36
23. `u32 idx` → 33
24. `s16 idx` → build fail
25. `unsigned long tmp` → 30
26. AC huff via `work->` at call only (no AC locals) → 120
27. Nested temp copies into huff_* → 32
28. `u8* zztbl` non-const → 13
29. **declsearch** 80 evals on decls 118–139 → best still (0, 13)

Root cause: `huff_sym`/`huff_tbl` keep DC-path preferred colors (r29/…) when reassigned for AC; target recycles freed `r24` (dc_predict) / `r25` (dc `r`) for AC huff and pushes `zztbl`/`zz` high. Any split of DC/AC names reshuffles the already-matching DC body.

## Recommendation

Need a shape that keeps DC 0–114 identical **and** births AC huff into r25/r24 (e.g. true live-range split / coalescing onto freed dc_predict/r without extra locals that raise pressure). Sibling `#else` C uses separate `ac_vl`/`ac_sym` and never shares DC huff locals — porting that cleanly without DC regen is the open problem.
