# o2-small attempts (2026-10-09)

Worktree `sol-low`, branch `agent/w1009/o2-mcm-pdm-nup`, base `20cf9f9f` (origin/main). Full build OK, DOL SHA1 `26116613…`.

## Compiler version check (all three units)

`/tmp/o2-small/ccsweep.py` compiles the unit with every GC and Wii compiler using the unit's exact flags (`-ipa file` dropped for GC/1.x-2.x, `NO_INLINE` stripped where those can't parse it) and counts instruction-exact functions.

| Unit | GC/1.x-2.7 | GC/3.0a3 … 3.0a5 | GC/3.0a5.2 | Wii 1.x |
|---|---|---|---|---|
| fa/pdm_partition | 5-7/20 | 19/20 (3.0a3 17/20 without NO_INLINE) | 19/20 | 15/20 |
| nup/nup | 0/23 | 20-21/23 (GetAuditData 12) | 22/23 | 9-10/23 |
| iplMemoryCardManager | does not compile | 25/26 (_create_icon 41) | 25/26 (_create_icon 37) | 22/26 |

All three stay on GC/3.0a5.2. `-proc` sweep for pdm (gekko, 750, 740, 7400, 7450, 603e, 604e, generic, 8xx, e300 …): gekko/750/740/7400 identical (19/20), every other model breaks other functions.

## Tooling built this round (all under /tmp/o2-small, not committed)

- `mwdbg/`: private copy of `_mwdbg` (shared lock) with extra PCode dump points: after backend optimizer (0x469383), around 0x596960(func,0) (0x4693a2/0x4693af, a no-op for scheduling), after the real first scheduling pass 0x5995c0(0) (0x4695dd), after 0x59a030 (store→load forwarding, 0x4695ee), before the second pass (0x469548).
- `sim/sched750.py` + `model2.py`: the tw2004 (mitsevox/tw2004 tools/matching/sched750.py) GC/2.6 750 scheduler model, fixed for virtual CR fields (`cr10+` were not parsed) and record forms (`add. rD,…,cr0` defines cr0). GC/3.0a5.2's pick function (0x599920) and DAG builder (0x599ac0) were read from the binary: same rules as GC/2.6, except memory edges use the PCode alias objects (+0x1c, `0x5a0150`). Approximating that with "same base register" reproduces both scheduling passes of the pdm loop block exactly and 49/55 blocks over four pdm functions (the misses are blocks where one object is reached through two different base registers).

## libs/RVL_SDK/src/fa/pdm_partition: pdm_part_is_master_boot_sector (84/86 in repo)

- Plain-sum LE32 (`b0 + (b1<<8) + (b2<<16) + (b3<<24)`, same as the exact sibling's MBR_WORD) + indexed second loop: 21, equal size, exact add tree and loop 2. Only the first loop's byte-load schedule/registers differ.
- First scheduling pass (0x5995c0(0)) input = initial code (the `*p_start` reload is still a `lwz`; 0x59a030 turns it into `mr` after the pass). Model reproduces our pass exactly: `s1` is picked over `s0` at cycle 2 because its shift makes one more successor ready.
- Target register sharing (`s3`/`s1` in r9, `s0`/`s1<<8` in r11) needs a pre-allocation order with `s0` loaded before `s1` and `add (s2<<16)+s0` before `s1<<8`. Annealing over all register-consistent pre-allocation orders under the post-RA model: best 10 ('base' alias) / 8 (all memory ops ordered), never 0. Both residual spots are the same pattern: target issues the low byte load before a shift that frees the next load through an anti-dependence. So with these 24 instructions the target is unreachable; the original block had a different DAG (extra node or different alias edges).
- Model experiments: an extra copy/zero-extend on `b0` in the first pass gives exactly the target load order (s3,s2,s0,s1 / c3,c2,c0,c1) but breaks the r11 sharing; keeping it through both passes (removed after) best 11.
- Source variants tried this round (all 21 or worse): `& 0xFF`, `(pf_u8)`/`(pf_u16)` casts, `<< 0`, byte_at() helper, b0 local, u8-param make_u32 helper (all forms), u8 locals, pointer cursor, array-indexed first loop (24, same first-pass input), accumulator (43).

## libs/RVL_SDK/src/nup/nup: __nupParseServerInfo (66)

- Allocator: coloring order is descending vreg for these low-degree nodes; colour = lowest already-claimed callee-saved register that is free, else claim downward from r31 (regsim reproduces 162/162).
- Per `__nupFindTag` expansion the vregs are: `start` = base, `endTag` = base+2, `startTag` = base+3, ret = base+4; `end` becomes a late temp (114, 120, …) because the backend copy propagation (0x596400) keeps the `strstr` result temp instead of the named `end` (declaring `end` first does not change that: it still becomes the temp).
- Want-list for all 34 FindTag values built from the target. Arbitrary renumbering reaches 34/34 in regsim; constrained to in-block numbering also 34/34, but per-block orders differ: blocks 1-2 need (end < start < endTag < startTag), blocks 3-7 need (end < endTag < startTag < start). No single uniform order gets more than 26/34. Target block 2 claims r18 (end2) before blocks 3-7 reuse it.
- Variants: end declared first 66, separate if-statements 469 (size).

## src/scene/memoryCard/iplMemoryCardManager: _create_icon (37)

- Callers (iplGCWindow) store the result in `const GXTexObj*`, and GXLoadTexObj takes `const GXTexObj*`. Declaring `create_icon`/`_create_icon` as returning `const GXTexObj*` (return type is not in the mangled name) with the banner-style helpers (`initIconTexture` returning `&cell.icon`, `initIconTextureCI`, `initIconPalette` with direct `&mFileCell[slot][file].iconTlut`) gives 11 with no casts. Address shapes all match; the only diff is the C8-path rotation slot*S r28/file*T r26/cellbase r27 (target r26/r27/r28).
- regsim on the captured graph: either swapping the vreg numbers of the two IRO temps (file*T @2824 → r44, slot*S @2826 → r43) or adding the slot↔file*T interference that a `mulli`-before-`mullw` pre-allocation order would create gives the exact target colours.
- IroCSE.c (rayanht/mwcc) shows temps are created in linear-IR order of each expression's first redundant occurrence (second loop of IRO_CommonSubs). Here that is the palette helper's address, where file*T is reached first. sol-r11's `cells` local fixes the order (3 diffs) but changes the TLUT address shape.
- Variants tried (all ≥11): non-const `GXTexObj*` local 44, texture assigned before the palette 21, tlut local in helper 34, helper param types (u8/u16/u32/int/s16 × s32/u32/s16/u16/long) 11-91, `GXLoadTlut(initIconPalette(...))` 11, getter for the icon 44, `&(mFileCell[slot] + file)->…` 11 (same IR).

## Round 2 findings (same day)

### Landed locally
- `6b6aeb4d` _create_icon 37 → 3: icon helpers mirroring the banner ones (palette helper walks `mFileCell[slot]`), `create_icon`/`_create_icon` return `const GXTexObj*` (iplGCWindow already stores the result as const; GXLoadTexObj takes const). No casts. Caller objects differ only in `.strtab`; DOL unchanged.
- `7086ed4c` pdm_part_is_master_boot_sector 84 → 21: entries read with the file's existing `MBR_WORD` (same add tree as the exact pdm_part_get_start_sector), extent check indexed. Equal size; only the first loop's byte-load schedule differs.

### MWCC internals used (GC/3.0a5.2)
- IRO dump: setting byte `[0x725e5c]` when the log is opened (bp at 0x5ed500) makes the compiler write `<source>.log` next to the source; also setting `[0x70f24d]` dumps the full linear IR after every IRO pass. Private mwdbg copy with its own gdb port (LD_PRELOAD bind remap) in /tmp/o2-small/mwdbg; run with `MWDBG_IRODUMP=full`. Delete the `.log` from the worktree afterwards.
- IRO lowering order (rayanht/mwcc IrOptimizer.c): for a binary node the operand with the higher cost is lowered first, ties lower the RIGHT operand first; MUL behaves like cost+2. `&mFileCell[slot][file].x` becomes `((this + C) + slot*S) + file*T`, so file*T is serialized before slot*S.
- IRO_CommonSubs mints a temp at the first redundant occurrence in that serialized order (IroCSE.c), and the backend numbers @temps in reverse creation order (earlier temp = higher vreg = coloured first).
- IRO_SplitLifetimes renames a temp that is assigned on two exclusive paths: the later path's copy gets a new, late @temp (low vreg, coloured last).
- PCode copy propagation (CopyPropagation.c) keeps a copy into a variable only if the variable is in the caller's initial named-object range or one of its uses is itself a move. This is why nup's helper `start` survives (`mr r3, start` feeds the second strstr) while `end` collapses into the late call-result temp.

### _create_icon status
- The C8 rotation (slot*S r26 / file*T r27 / cellbase r28) needs slot*S coloured before file*T. Two sources were found that give it, neither complete:
  - `R2C2T2`: `GXLoadTexObj(initIconTexture(...))`, C8 `GXLoadTexObj(&mFileCell[slot][file].icon)`, `return &mFileCell[slot][file].icon` after the if/else. The join return makes the RGB and C8 file*T/cellbase temps one object; IRO_SplitLifetimes renames the C8 copies late → C8 exact. But the same join group merges the RGB GXInitTexObj argument with the post-call address (address kept across the call, r26), 8 diffs.
  - Row-pointer local in the palette helper (committed form): slot*S is minted first, but the TLUT address becomes `(row + file*T) + 0x112c` instead of `(row + 0x112c) + file*T`, 3 diffs.
- Type experiments: with the original non-const return type, the RGB path recomputes after the call like the target (the const conversion of the GXInitTexObj argument keeps it out of the join group) but the C8 GXInitTexObjCI argument (non-const prototype) joins the group, 30. Making both GXInit prototypes match the real SDK (non-const) or both const: 27/33/46. SDK header restored each time; not changed.
- Tiny-file probes (/tmp/o2-small/t): inner-index multiply is always minted first unless an earlier statement uses the bare row `cells[slot]`.
- Function-scoped pragmas around _create_icon: wrapping alone changes size (+4), nothing below 34.

### nup
- Pragma sweep (16 singles + all pairs, function-scoped) on __nupParseServerInfo: nothing below 66.
- Literal-tag macro form: tag addresses are rematerialised each time (target keeps them in r22/r25-style registers), size 0x76c; per-block value/length locals: size 0x708. FindTag variants (end first, nested, result var, end+=, param order): 66 or worse.
