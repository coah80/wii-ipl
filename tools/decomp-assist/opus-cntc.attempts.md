# opus-cntc attempts (cntcache.c)

## _CNTCACHEDeleteContent (start: asm placeholder; prior best C 95.79%, 143/145)

1. Flat early-return C, typed `ESTmdView view` local: 80/145 differing, frame 0x2120.
2. `u8 buf[sizeof(ESTmdView)]` + `ESTmdView* tmd` pointer, size/count decl order swapped: 118 (frame fixed, pointer r28 appears).
3. Helper with multiple returns: 90 (worse branch shape in helper, `bge; b`).
4. Helper with `usage` var + if/else chain: 90.
5. `usage = result;` before chain: 118 (coalesced anyway).
6. Type check via `ES_TITLE_TYPE` (u32 cast and 64-bit): -1 still CSE'd into r31.
7. `(titleId & 0xFFFFFFFF00000000) != 0x0001000500000000`: 96, xor form.
8. Nested-if structure (single exit, memset inside): 90/145, 143/145 insns; only diffs are the
   missing `li r0,-1` reload before snprintf (CSE/LICM keeps -1 in r31) and missing `mr r0,r3`
   (helper result coalesced into r3); everything else is register renumbering from those.
9. Diagnostic: type check without mask -> li -1 hoisted to outer token-loop preheader (LICM).
10. 32-bit masks `(u32)(x>>32) & 0xFFFFFFFF`: masks fold away, 82 but wrong (no `and`).
11. Mask variants `(u32)(t>>32),(u32)(t&0xFFFFFFFF)` etc.: 89-90, -1 still hoisted.
12. Helper `static` (auto-inline) instead of `static inline`: 90, no change.

## _CNTCACHEIsTitleRemovable (start: asm placeholder; prior best C 93.71%)

Upstream koopthekoopa/wii-ipl has a non-matching C sketch (GetSavePath/GetTmdView helpers, `ret = -1`, goto out); read only.

1. Typed flat version with my usage helper: 69/82.
2. Upstream structure (GetSavePath + GetTmdView helpers, `s32 ret = -1`, goto out): 72.
3. GetTmdView takes `u32* tmdSize` from caller: frame offsets right, 72.
4. Usage code written directly in the caller (no GetSavePath): `mr r4,r3` copy appears in target position.
5. + `u8 tmdBuf[OSRoundUp32B(sizeof(ESTmdView))]` with `ESTmdView* tmd` pointer: 5/82.
6. `(u8)(titleVersion >> 8)`: no change (srawi.); `((v >> 8) & 0xFF)`: 4/82.
7. Back to GetSavePath helper with those fixes: 18 (copy coalesced on the wrong side).
8. `result`/`ret` split in helper: 18. `static inline`/`s32` helper: 18. Drop `= -1` init: 69.

## _CNTCACHEDeleteContent (cont.)

13. Usage code written directly (no helper): no copy, 90.
14. Function-wide `ret` reused for every status (typical SDK style): 94, no copy.
15. Shared `static s32 GetSaveDataUsage` helper written like the matched inline code
    (`s32 ret = -1;`, separate `usedBlocks = 1; usedINodes = 1;` stores, if/else chain):
    21/145. Swapping usedBlocks/usedINodes declaration order: 15. Declaring `titleId` before
    `tmd`: **0/145 (exact)**. The dead `ret = -1` init is load-bearing (without it: 90).
16. IsTitleRemovable switched to the same helper with caller `s32 ret;` (no init): **0/82**.
    (With caller `ret = -1` init: 16/82.)

## CNTCACHEClear (start: asm placeholder; prior best C 93.36%, 147/151)

1. Replaced the hex blob with real literals (SDKDefineVersion, path/command literals,
   `" \n"`, `"/title/%08x/%08x/data"`). Clear in C with `FindLineEnd` static helper: 162/180;
   `_CNTCACHEDeleteTitle` got auto-inlined into Clear (target calls it).
2. `(void)` prototypes, no prototypes (compile error), `-ipa function` / no ipa (no change, or
   header static inlines emitted): DeleteTitle still inlined / unusable.
3. Diagnostic `#pragma inline_max_auto_size(k)`: DeleteTitle's auto-inline size is 15 and the
   default limit is 15, so the original DeleteTitle must score >= 16.
   while->for, nested ifs, result assignments: still 15. switch: breaks DeleteTitle.
4. DeleteTitle as a `for` loop with `if (errno != 0 || type == 1) continue;`: size 16, not
   inlined, DeleteTitle still 0/50. Clear: 126/151, size 147/151.
5. Error exits: `goto close`, else-goto, switch, do/while(0)+break all give `bne close`; micro-tests
   show only `return` gives the target `beq +8; b close`. Helper `ExecuteCacheFile(info, result)`
   with returns: 151/151 (not inlined, auto size); `static inline`: 68/151, 149 insns, branch
   layout matches.
6. `s32 readLength` + `> sizeof(buf)` clamp: cmpw/bgt/cmplwi as target, 67.
   Swapping compare operands: no effect. `!lineEnd` / `if (command)`: immediate compares, 64.
7. Stripped writers `CNTCACHEAddDeleteTitle` / `CNTCACHEAddDeleteContent` (+ static Read/Write
   helpers using /shared2/cntcache.txt, /tmp/cntcache.txt, NANDPrivateMove to /shared2):
   .data and .sdata bytes identical to target, Clear string offsets match.
8. Brute-force local order: Clear's own decls have no effect; helper decls reversed
   (lineLength, line, readLength, offset): 47/151 (helper r23..r26 match).
9. Lone `cmpwi r3,0` after each NANDPrivateDelete: empty if, `;`, `(void)(x == 0)`, empty inline
   call, dead store, inline void/return helpers all remove it. Micro-test: kept only when
   the body copies between two coalesced variables (`r = res; if (g()) { r = res; }`).
   `opened = FALSE` in body: 49/155. `result = result;`: keeps only the second compare, 47/151 at 150 insns.
   Not found; stopped here.

Result: CNTCACHEClear not exact (best 47/151, 149/151 insns). Best C plus required companion
changes in [opus-cntc.best.c](opus-cntc.best.c); the asm placeholder and original data arrays stay.

## Final state
- `_CNTCACHEIsTitleRemovable` 0/82, `_CNTCACHEDeleteContent` 0/145 (C, shared GetSaveDataUsage).
- `CNTCACHEInit` 0/29, `_CNTCACHEDeleteTitle` 0/50, `CNTCACHEClear` 0/151 (asm) unchanged.
- pool_diff: identical (9/9).
- Note: in DeleteContent, `result != ES_ERR_DONT_EXISTS && result == ES_ERR_OK` keeps the
  target's separate -106 compare; this is redundant but not impossible.

## Round 2: _CNTCACHEDeleteContent without the redundant test
1. Replaced `result != ES_ERR_DONT_EXISTS && result == ES_ERR_OK && ...` with an early
   `if (result == ES_ERR_DONT_EXISTS) { return; }` followed by `if (result == ES_ERR_OK && ...)`:
   0/145, equal size. IsTitleRemovable still 0/82, pool identical (9/9).
   check_asm_inventory: FAIL before and after (same 8 pre-existing placeholders incl. parked CNTCACHEClear).
