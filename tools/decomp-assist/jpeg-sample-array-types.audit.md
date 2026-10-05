# JPEG sample-array type correction

Current base: `bf65a26b5e38cddaa37b0e12e15e55ba61f57dd9` (43U only).
Original validation base: `e174f2c2bedc4baa28490dcf53989c9a2994bd2e`.

## Source correction

- Declare and define `TMCJPEGDEC_SampleH_N` and `TMCJPEGDEC_SampleV_N`
  consistently as `const u8[6][4]`, using six explicitly grouped rows.
- Remove the obsolete H/V declaration conditional. The independent
  `TMCJPEGDEC_SampleComps` incomplete-array condition and parser flag remain
  unchanged; they are outside this type mismatch.
- Preserve every initializer byte and both existing `[sample][component]`
  consumers in `TMCJPEGDEC_parse_sof`. Both tables remain 24 bytes, at
  `.rodata` offsets 0 and 24. No flags, dummy state, casts or assembly added.

## Original e174f2c2 validation snapshot

A clean baseline and candidate were built in an isolated leaf with local
copies of the recovered tools and original input. Main's build was untouched.
The comparisons and numbers in this section describe the JPEG correction
relative to the original e174f2c2 baseline, before the disjoint eZiText changes
in bf65a26b. They are not current-main metrics.

- Full `ninja -j4` 43U build passed. The header change rebuilt all 15 dependent
  objects, followed by linking and the DOL check.
- Explicit `ninja build/43U/ok`, with the generated stamp removed first,
  passed: `build/43U/main.dol: OK`.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.
- Baseline/candidate full reports are byte-identical, SHA256
  `dfe72493ec41da47a3052f4903a2ccddccfa1907002b6831274b76ee0b4844ef`.
  All 1,027 units and 12,563 function records are unchanged.
- All 1,027 source objects preserve all 2,717 allocated sections, including
  bytes, lengths, types, flags and alignments, and all 117,551 relocation
  records (locations, types, target names/sections/offsets/sizes/bindings and
  addends). This includes all 15 header-dependent objects.
- `jdec_main`: 13/13 exact functions; 5,604/5,604 code bytes and 256/256 data
  bytes matched and linked. Its complete `.text` and `.rodata` match retail;
  all 67 relocations have identical canonical destinations and addends.
- `jpformat`: 376/376 data bytes matched and linked. `.rodata` is exactly
  368/368 bytes; both H/V tables retain their bytes and addresses. Existing
  `.sdata2` remains 6 source bytes versus 8 retail bytes, with identical
  contents and two retail zero-padding bytes; alignment remains 8. No
  relocations exist in either object.
- `pool_diff.py`: identical pools for all 15 dependents (0/0 strings each).
- `ctxdiff.py`, using the recovered local helper: all 13 `jdec_main`
  functions have equal instruction counts and `diffs 0`; 1,401/1,401 total
  instructions. `jpformat` contains no functions.
- `decomp_status.py` ran. `check_decomp_complete.py` still returns 1 for the
  existing repository-wide incomplete state; its baseline/candidate findings
  are identical. This correction makes no repository-completion claim.
- `git diff --check` passed.

Original-snapshot global values were unchanged: 93.996216% exact code, 99.817444% fuzzy,
80.08451% linked code, 99.9941% matched data, 85.36267% linked data,
12,469/12,563 exact functions and 982/1,027 complete units.

Detailed local evidence is in the sibling `wii-jpeg-array-evidence` directory:
`audit.py`, `audit.txt`, baseline/final build logs and reports,
`all-dependent-pools.txt`, `pools-ctxdiff.txt`, `explicit-ok.txt`, and completion
checker outputs. Original input and binary build artifacts remain local.

## Rebased bf65a26b independent verification

After the disjoint eZiText change in PR #1221 landed, the parent mechanically
rebased the correction onto bf65a26b and independently rebuilt both main and
the leaf. The parent reported identical full reports and identical allocated
sections and relocation records across all 1,027 source objects between that
new baseline and the rebased leaf. Both full 43U builds passed and retained
DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.

The correction still preserves the separate `SampleComps` conditional. This
audit update changes documentation only; it does not change source or flags.
