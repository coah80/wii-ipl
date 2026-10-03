# RGB565420 edge pixel lifetime

Base: `57ccda3883537a308568c03924af2cebf2d8a789`, branch
`agent/bittle/jpeg-pixel-lifetime`, 43U only. One authorized source trial;
no additional variants, header/configuration changes, or remote writes.

## Source reconstruction

The existing exact RGB565444 sibling has a pixel-scoped independent luminance
value and pixel-scoped RGB locals. Apply that lifetime boundary to RGB565420
edge, retaining its current chroma sampling and every address/step expression.
Initialize red, blue, then green, matching original instructions 60..62 after
the luminance load at 58. The original overflow reduction at 63..64 is
blue/red/green; that existing source expression remains unchanged, as do clamps
and the RGB565 packing expression. No declaration-permutation search was used.

Chroma products are bounded signed integer arithmetic. For signed byte Cb/Cr,
red/green/blue offsets stay within [-180,178], [-135,135], and [-227,225]. Adding
an unsigned luminance byte cannot overflow s32. There are no floating-point
operations. Removing the blue variable's temporary ownership of luminance and
limiting RGB lifetimes to the pixel does not add or remove input reads or output
writes. The arithmetic order changes only among independent initialized scalars.

The historical tex1 log records a different sibling-template trial at
96.00877%, discarded for being nonexact. Its original source is unavailable;
this candidate is an independently measured reconstruction, not that artifact.

## Measured result

- `TMCJPEGDEC_converterYUV420toRGB565edge`: 94.692986 -> 95.570175%
- 114/114 instructions; ctxdiff differences 73 -> 65
- Unit fuzzy: 96.5207 -> 96.58538%
- Exact functions remain 7/13; matched code remains 2648/6184 bytes
- No allocated non-code sections in source or original; data remains 100%
- Global fuzzy: 99.71608 -> 99.7162%; all exact/link/data totals unchanged
- No function- or unit-level regressions across the full 1027-unit report
- Only this function's body differs from the saved baseline object; all twelve
  sibling function bodies are byte-identical to baseline
- Seven existing exact functions remain objdiff 100% and ctxdiff zero

This is partial fuzzy progress, not an exact match or linking result.

## Validation

Pool checks before the trial and after the full build: identical, zero strings.
The full 43U build passed. `ninja build/43U/ok` passed with no work pending.
DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
`git diff --check` passed. Literal-reference audit: no candidates/errors;
twelve functions analyzed, unchanged nonexact setter skipped for unequal size.

A focused independent scalar pixel model was compared with the compiled
candidate, original, and saved baseline through the existing bounded PPC
interpreter. All 8,721 vectors passed (26,163 object executions):

- 808 cases covering every valid edge width and height for scales 1/2/4/8,
  both starting-row parities, and even-column residues 0/2 within a tile
- 256 cases covering both width/height selection branches, zero/full/partial
  extents, row parity and column residues
- 6,400 saturation cases: all 256 luminance values crossed with all Cb/Cr
  pairs from {-128,-1,0,1,127}
- 1,257 aligned input/output overlaps; every output byte stays inside the
  actual 0x184-byte convBuf backing array and state remains separate

All 114 instructions in candidate, original, and baseline were exercised.
Every non-stack byte, including guards, was compared against the scalar model.
The interpreter also checked LR, stack pointer, and GPR14..GPR31 preservation.
Odd input x is excluded by the existing entry assertion; valid multi-pixel
rows exercise both odd/even column paths. Unsupported scales and invalid
pointers are not asserted valid API inputs. These are bounded interpreter
checks, not formal equivalence or Wii runtime validation. The existing integer
interpreter's limitations remain; no FPU, MMIO, exception or timing model is used.

## Reproduction artifacts

Local evidence directory: `/tmp/jpeg-pixel-lifetime/`.
- `baseline-report.json`, `baseline-rgb.o`: saved before source edits
- `candidate-report.json`, `candidate.ctx`: focused candidate measurements
- `full-build.log`: full build output
- `audit.py`, `audit-results.json`, `audit-output.txt`: independent pixel model
  and targeted differential evidence

The test script reads the current candidate object, current original object,
and saved baseline object. It does not write repository source or original
binary bytes. Re-run from this worktree:

```sh
PYTHONPATH=../local-tools ../.venv/bin/python /tmp/jpeg-pixel-lifetime/audit.py
```

Build configuration uses cached approved tools:

```sh
../.venv/bin/python configure.py --version 43U \
  --wrapper ../toolchain/wibo-build/wibo --compilers build/compilers \
  --dtk build/tools/dtk --objdiff build/tools/objdiff-cli \
  --sjiswrap build/tools/sjiswrap.exe
WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja
build/tools/objdiff-cli report generate -p . -o build/43U/report.json -f json
```
