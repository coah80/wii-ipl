# a2c-warn2 attempts

Owned function: `System::warning_run` in `src/system/iplSystem.cpp` (asm placeholder).
Worktree `data-d10`, branch `agent/w1009/a2c-warn2`, base `ec965ad5`.
Prior state: rx17 C 47/176, a2c-warn C + `opt_dead_assignments off` 42/176 (smArg/visibility swap).

## Tooling

- `/tmp/a2c-warn2-try.py <fragment>`: splices a `warning_run` body into the unit, compiles with the unit's
  real flags (1.2 s), diffs against the target, prints saved-register mismatches.
- `/tmp/a2c-warn2-cap.sh <full source> <name>`: mwdbg capture of a reduced unit (warning_run +
  getRenderModeObj only, 39 s instead of 105 s). The reduced unit reproduces the full-unit graph exactly.
- `/tmp/a2c-warn2-vals.py <capture>`: vreg map (name, degree, color, defining PCode).
- `/tmp/a2c-warn2-hyp.py`: replays the capture with relabelled vregs (what-if numbering).

## Allocator facts (from captures, confirmed against the MWCC decomp sources)

- Numbering: named locals (reverse declaration order), then `@` temps, then codegen temps in creation order.
  `&smArg` is the backend CSE of the first `lis/addi` in the reset check, so every frontend local is
  numbered below it.
- Target colour order is snd r31, 0x4330 r30, visibility r29, smArg r28, rMode r27. That needs numbering
  rMode < smArg < visibility < 0x4330 < snd with smArg not deferred. smArg has degree 32 (12 precoloured), so
  at least 4 of its neighbours must be numbered below it.
- Simulation on the captured graphs: any layout with visibility between smArg and 0x4330 plus two more
  frontend neighbours below smArg reproduces the target colours exactly.

## Results

| variant | diffs | note |
|---|---|---|
| rx17 C (bool visible) | 47 | baseline |
| `u8 visible` | 47 | visibility becomes a codegen temp (clrlwi from bool->u8 folds away), but smArg still deferred (2 below) |
| `u8 visible` + dead_assignments off | 42 | survivors below smArg, but the value moves back into isVisible's `@` return temp |
| `const bool& visible` + dead_assignments off | 7 | smArg r28, rMode r27 correct; visibility is a stack temp promoted after codegen, numbered last |
| `volatile` mbVisible + dead_assignments off (diagnostic only) | 5 | all registers right; only the volatile load/store scheduling differs |
| `Arg& arg = smArg;` + dead_assignments off | 47 | arg keeps the target `lis r3; addi rX, r3` form (only while rMode comes from getRenderModeObj) |
| pragma single/pair sweeps on u8, const-ref and Arg& variants | >= 7 | nothing below 7 |
| `u8 visible = getPointer()->mbVisible;` + dead_assignments off (`friend class System;` in Pointer) | **0** | exact |

## Why the exact form works

- `opt_dead_assignments off` keeps the inline `this` temporaries (framework, pointer, reset handler) and the
  rMode return temp alive. They are frontend values numbered below `&smArg`, so smArg is no longer deferred.
- Reading the field straight into a `u8` adds a bool->u8 conversion at the load. The load goes into a fresh
  codegen temp, the clrlwi folds into a copy and copy propagation keeps the temp, so the saved visibility is
  numbered between `&smArg` and the 0x4330 constant. Any accessor call (`isVisible()`) puts the value back in
  an inline return temp (42 diffs); `bool`/`BOOL`/`int`/`u16`/`u32` locals give 47, `char`/`s8` add an extsb.
- `friend class System;` follows the existing `friend class System;` in WarningHandler. No other unit changes.

## Final verification

- `ninja build/43U/src/src/system/iplSystem.o`: odiff 0/176, ctxdiff `diffs 0`, 176/176 instructions.
- pool_diff: POOL IDENTICAL up to 52 (mine=52 base=52).
- Unit report: 63/63 functions, code/data/complete 100%, every owned section 100%.
- Full build PASS, `main.dol` SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `check_decomp_complete.py`: DECOMPLETE_OK.
- `check_asm_inventory.py`: 164 functions, 166 blocks, 162 ORIGINAL, 2 PLACEHOLDER (the remaining failure is
  only the two placeholders owned by other workers; no stale rows). Row and `[rx17]` link removed, header counts fixed.
- `gate.py src/system/iplSystem --quick`: GATE PASS, 0 regressions, 0 forbidden, 0 readability warnings; review
  note for the scoped `opt_dead_assignments` pragma (allowed by the 2026-10-09 rules).
