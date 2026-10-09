# a2c-jdec2: TMCJPEGDEC_err_restart asm -> C

Branch `agent/w1009/a2c-jdec2`, base `be309e8f7`. Owns `TMCJPEGDEC_err_restart` in
`libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c` and its asm inventory row.
Untracked rx63 files in the worktree are unrelated and left alone.

Read opus-common.md, levers.md (all, esp. 35-38), a2c-jdec, opus-ph, sol-ph2,
jpeg-restart-status-lifetime logs, saved diffs in `_luna-runs/best/`, PR #1355 diff.

Harness: `/tmp/a2c-jdec2/h.py` / `hm.py` splice a candidate body into the unit,
compile with the unit's exact MWCC command (0.07 s per trial), and report
instruction count, positional diffs, register-blind shape diffs, and whether any
of the other 12 functions changed.

## Two separable problems

1. Topology: target has `cmplwi d0; blt top; cmplwi d7; ble +8; b top`. Plain
   `continue`/`break`/`goto` forms fold to `bgt top` (114 insns).
2. Finish block registers/schedule (dist/interval/pitch/skip/pos temps).

### Topology findings

- Any front-end IR statement in the out-of-range arm that the backend later
  deletes reproduces the target shape. Proof: `#pragma opt_dead_assignments off`
  + dead `result = 0;` in that arm gives 115/115 (28 diffs, all in finish).
  The same pragma unit-wide changes parse_sof, scan_varinit, restart_interval,
  so the original unit was not compiled that way.
- Front end removes: dead stores to locals, self-referencing dead counters
  (`skipCount++`), unreachable-after-loop uses, empty inline calls, `(void)x`.
- Kept and backend-visible: stores (`byte = marker` 116), loads
  (`state = work->pState` 116).
- Only a register copy that coalesces works: `scanner = work` (sol-ph2 idea).
  Loop-head aliases (block-scoped `TMCCJPEGDecWork* scanner = work;`, for-loop
  increment) do not work (114/116): the copy must be inside the arm itself.
- DOL-wide scan: `bc +8; b back` occurs only in NHTTP switch lowering, VF inlined
  Advance/MoveTo returns, and this function.
- Switch with `case 0xD9`/default: 115 insns, 23 diffs (signed `cmpwi` for D9).
- Loop-flag forms (found/keepGoing/searching, do/while/for): 118-121 insns.
- Empty `else {}` (get_wbyte idiom) on the range test: 114, folded.
- Inline helper decompositions of the scan (skip-to-FF, readMarker, predicate):
  114-119 insns.

### Finish block

Exhaustive enumeration of all 3410 dependency-valid statement orders x 2 dist
forms x 2 next forms x 2 decl orders plus annealing searches: best 6 diffs
(pitch r8/skip r7 swap, `mullw` operand order). Fixes:
- `oy = pos & 0xFF` as a named u16 local makes `mullw` keep source order
  (`(u8)pos`, casts, `(u8)` locals are reordered to pitch-first).
- The skip count must stay a named local so pitch is coloured first: reusing
  the u8 distance local for the multiplied count (`dist *= interval`) gives
  0 diffs. A separate `skipped` local is copy-propagated into a temp that takes r7.

Result with scanner alias stand-in: 115/115, 0 diffs, other 12 functions unchanged.

## Prior art (read-only)

hotlandsoftware/wii-news-channel decompiled an older build of the same TMCC JPEG
library (`src/revolution/TMCC_JPEG/jpgd_dec.c`, `jpgdResync`). Its finish uses
the same `skip = ...; skip *= restartInterval;`, `(x << 16) + y` and `n % pitch`
spellings, passes `&ctx->stream` (a stream sub-struct at offset 0 of the work)
to every stream call, and its notes record the identical unsolved problem:
"the loop exit is `ble; b` instead of `bgt`, plus two register swaps" (98.44%,
400 srcsearch iterations, continue/goto/switch/duplicated-condition forms).
So the unfolded exit comes from the original source in two independent builds.
Their flat finish reproduces here as 11-12 diffs (marker r5, skip r8); the inline
helper boundary fixes both swaps.

## Why a no-op pointer copy is required (not a trick)

- The arm must hold a front-end statement the backend deletes after the PCode
  branch fold. Dead stores, self-referencing counters, pure expressions, empty
  inline calls, labels, nested blocks, `asm {}` and `#pragma unused` all vanish
  in the front end (114, folded).
- Only register copies survive to the allocator and then coalesce. Coalescing
  needs no interference, so the destination is live at the loop head yet always
  holds the source value. At the loop head only `work` (r30) and `state` (r31)
  are live in registers (the inner test reloads the stack byte), so every
  matching source has a value-preserving pointer copy on this path. Exact forms
  found: an alias reset (`stream = work`, or a `state`/finish alias), a pointer
  self-assignment through a cast, a for-loop increment alias. Plain
  self-assignments and `+ 0` are folded away.
- Brute force of 46 natural assignments over the function's own variables,
  loads and constants in the arm: only the two pointer cast self-assignments
  match; loads/stores add instructions, scalar copies fold.
- Compiler sweep GC/3.0a5, 3.0a5.2, Wii 0x4201_127, 1.0RC1-1.7: all fold the plain
  form; only GC/3.0a5.x keeps the other 12 functions.
- Chosen form mirrors the original's `&ctx->stream` handle: a `stream` pointer
  used for rewind/peek/get_byte, reset at the end of the scan loop, with an
  `MWCC needs ...` comment (precedent: `AudioWaveUtility.cpp` local aliases of
  `this`, `get_wbyte` empty else branches). Loop uses the prior art's
  `if (RST) break;` structure.

## Final

`restartFromMarker` inline helper (locals in computation order: skip, pitch, pos,
row, column, mcuIndex, y, x, result; `row = pos & 0xFF` keeps the multiply
operand order) plus `TMCJPEGDEC_err_restart` with the stream handle.
- odiff 0/115, ctxdiff diffs 0, pool identical (no strings), whole-object .text
  byte-identical, other 12 functions unchanged.
- Asm inventory row and `[rx24]` link removed; header now 164 functions,
  166 bodies/blocks, 162 ORIGINAL, 2 PLACEHOLDER. Checker FAIL only for the two
  remaining unrelated placeholders (CNTCACHEClear, System::warning_run).
- Full build OK, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d, DECOMPLETE_OK.
