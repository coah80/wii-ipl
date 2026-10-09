# a2c-cntc2 attempts: CNTCACHEClear asm -> C

Owned `CNTCACHEClear` in `libs/RVL_SDK/src/cntcache/cntcache.c`. Branch
agent/w1009/a2c-cntc2 at ab9cdd32, worktree data-d8. Start: asm placeholder.
History read: opus-cntc, sol-cntc (R1-R3), a2c-cntc, levers 35-38, rejected exact
11cdd576 (six out-parameter carrier).

Result: CNTCACHEClear exact in plain C, 0/151 differing, 151/151 instructions.
All five unit functions exact, pool identical 9/9.

## What blocked earlier attempts

Two shapes, traced with mwdbg (capture `_mwdbg/runs/a2c-cntc2-A`):

- Registers. The target's coloring order needs the parsing locals (lineLength,
  line, readLength, offset) numbered below opened, locked and result. MWCC numbers a
  function's own named locals first (reverse declaration order) and inlinee locals
  after them, as `@` temporaries. With the loop in an inline helper the helper
  locals always sit above the flags and are colored first: helper with ordinary
  locals = 44/151, 151 instructions. That is why 11cdd576 needed out-parameters.
  With the loop written directly in CNTCACHEClear every saved register matches
  (variant B), but two instructions go missing.
- Branches. After NANDPrivateOpen and NANDGetLength the target has
  `beq +8; b close`. An `if (result != OK) goto close` compiles to `bne close`
  (149/151). The `beq +8; b` form only survives when the block held something that
  disappears after branch optimization. Tried: ret/result split (extra mr),
  guarded steps (`if (result == OK)` chains, bne), dead flag store in the error block
  (fixes one site only and is dead code).

## The fix: switch dispatch

A single-case `switch (result) { case NAND_RESULT_OK: ...; break; default: goto close; }`
compiles to `cmpwi; beq case; b default`, which is exactly the target. Precedent in
the same SDK: RFL_NANDAccess.c opencallback_ uses
`switch (create) { case NAND_RESULT_OK: ...; default: ...; }` and emits the same
`cmpwi r3,0; mr r28,r3; beq +8; b` sequence (found by scanning every matched SDK
object for branch-over-branch). Results:

| Variant | CNTCACHEClear |
| --- | --- |
| direct C, `if` checks (B) | 127/151, 149 insns |
| direct C, switch checks (S1) | 0/151 |
| one switch with NOEXISTS, OK, default (S2/S3) | binary-search dispatch, wrong |
| `opened = TRUE` in `case NAND_RESULT_OK` | 0/151 |

## Post-delete compares

Target: `bl NANDPrivateDelete; cmpwi r3,0` with no branch, twice.

| Form | Result |
| --- | --- |
| plain call / empty if / `return x == OK` helper | 149 insns |
| `static inline BOOL DeleteCacheFile`: `if (NANDPrivateDelete(path) != OK) return FALSE; return TRUE;` | 0/151 |
| NOEXISTS-to-OK helper | 2 diffs (compares -12) |

Kept the BOOL helper; the caller ignores the result (best-effort cleanup). The
redundant `if (result != OK) return result; return OK;` helper from sol-cntc is gone.

## Declaration order and flags

Required relative order (reverse declaration = vreg order): command before result,
result before locked, locked before opened, then offset, readLength, line, lineLength.
lineEnd, info, fileLength and buf positions are free (P1, P3-P6 all exact). Kept
`info, command, result, locked, opened, fileLength, offset, readLength, line,
lineEnd, lineLength, buf`. `BOOL locked = FALSE; BOOL opened = FALSE;` initializers
are exact too. Both flags are set and tested: `locked = TRUE` after OSLockMutex,
`opened = TRUE` on a successful open, `opened = FALSE` after NANDClose.
Command declared after result or block-scoped = 40/151.

## Companion changes

- String pool: the blob `scCntCacheStrs` became literals plus SDKDefineVersion.
  The five literals used only by stripped functions ("DeleteTitle ", "%016llx ",
  "/tmp/cntcache.txt", "/shared2", "DeleteContent ") come from the reconstructed
  writers ReadCacheFile, WriteCacheFile, CNTCACHEAddDeleteTitle and
  CNTCACHEAddDeleteContent, as in 11cdd576 and the policy for linker-stripped
  functions (#1242, #1248, #1249). The linker strips them; the DOL is unchanged.
- `_CNTCACHEDeleteTitle` written as `for` + `continue` (inline score 16): the while
  form scores 15 and is auto-inlined into C CNTCACHEClear (184 insns).
- `revolution/cntcache.h`: `s32 CNTCACHEClear(void)` (target returns the status in r3).
- docs/asm-inventory.md: CNTCACHEClear row and its `[rx30]` reference removed; header
  165 functions / 167 blocks / 162 ORIGINAL / 3 PLACEHOLDER. origin/main be309e8f
  removed Manager::hasChannel with the same header text, so after a rebase the header
  must read 164 / 166 / 162 / 2.

## Validation (worktree, base ab9cdd32)

- odiff CNTCACHEClear 0/151; ctxdiff 151/151 insns, diffs 0.
- objdiff unit: code 1828/1828, data 280/280, functions 5/5, complete code/data 100%,
  sections .text/.data/.sdata/.bss/.sbss 100%.
- pool_diff: POOL IDENTICAL 9/9. .data/.sdata bytes equal the target (target adds
  only alignment tail).
- Full build ok, main.dol SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
- check_decomp_complete.py: DECOMPLETE_OK.
- check_asm_inventory.py: counts and rows consistent; exit 1 only for the 3 remaining
  placeholders (jdec_main, iplSaveDataManager, iplSystem).
- gate.py libs/RVL_SDK/src/cntcache/cntcache --quick: GATE PASS. Full build ok, DOL
  SHA1 matches, pool identical, instruction-exact 5/5, 0 regressions vs
  baseline-ab9cdd32, 0 forbidden patterns, 0 readability warnings.
