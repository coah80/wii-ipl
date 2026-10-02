# JPEG follow-on reconstruction

Base: `813660b9`, branch `agent/bittle/jpeg-reconstruction-next`.
The already-reviewed EXIF candidate `b9305280` was preserved unchanged as local
cherry-pick `164dbbc5`. This log concerns a separate follow-on to that candidate.

## Retained change

IFD0 rational denominator addresses now use the same explicit offset grouping as
IFD1: add four to the TIFF offset, then add the thumbnail-data base. The redundant
same-type pointer cast is removed. This is a two-line source change; it introduces
no new tag interpretation, new memory access, or function.

- `TMCJPEGDEC_IFD0_tag_parse`: 99.386696 -> 99.49065 fuzzy
- EXIF unit: 98.94104 -> 98.98035 fuzzy
- EXIF exact functions: 3/6 -> 3/6; matched code remains 1348/5088 bytes
- IFD0 remains 480/481 instructions; this is not an exact match or linking result
- All other 33 owned functions retain their baseline scores

No changes are retained in the color converters or IDCT. No declaration-order
search, forced registers, volatile, assembly, padding, headers, configuration,
linking changes, remote writes, or edits to the entropy decoder were made.

## Rejected reconstruction trials

Every equal or regressing trial was restored before validation.

- Separate rational numerator/denominator pointer lifetimes in IFD0 and IFD1:
  unchanged from the retained expression; restored
- RGB444's common edge-sibling channel evaluation and clipping order with a
  separate luminance value: 98.71429 -> 98.62637; restored
- Explicit odd-coefficient differences in the luminance second-pass butterfly:
  83.05058 -> 81.42802; restored
- Extract the luminance first-pass row transform to a static inline helper:
  83.05058 -> 81.12062; restored. The trial script initially omitted helper
  local declarations, causing a compiler error; that experiment was corrected,
  measured, and then fully restored
- Extract RGBA pixel packing to a static inline helper:
  - 411: 82.6033 -> 81.72314; restored
  - 422 and edge: unchanged at 87.72298 and 90.08849; restored
  - 420 and edge: unchanged at 89.40523 and 87.458336; restored
  - 211 and edge: unchanged at 91.15385 and 92.0; restored
  - 444: unchanged at 90.670105; restored
  - 444 edge: 88.90909 -> 87.70909; restored

These were source-structure trials, not permutations of register declarations.
The source-neutral scheduling differences that remain were not chased through
artificial source changes.

## Verification

The baseline report was generated after building the unchanged cherry-picked
candidate. The final report was freshly generated after restoring every rejected
trial and rebuilding all four owned objects.

- Full 4.3U build: PASS
- All 34 owned function scores compared against the baseline: zero regressions
- All 11 previously exact functions retain exact-name objdiff 100 and ctxdiff 0
- Pool checks before trials and after the final build: all four identical,
  zero strings
- Neither source nor original object has allocated non-code sections in any of
  the four owned units
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- The existing read-only bounded PPC audit tools were inspected before use;
  their scripts are unchanged
- Converter/IDCT audit: all 9,456 paired calls pass

- EXIF audit: all 267,282 paired calls pass, including the 42 version-byte
  overlap cases preserved by the preceding candidate
- `git diff --check 813660b9`: PASS, including the base-relative committed diff
- The working tree is paused for parent review after the focused local commit
These interpreter tests are bounded samples, not formal equivalence or Wii
runtime tests. Their existing coverage and modeling limitations still apply.

## Existing external overlap

The prior EXIF log documents the already fetched
`origin/agent/w1009/tmc` branch's overlap with EXIF and color reconstruction.
That overlap remains relevant to parent integration. This follow-on was derived
from the current source, the prior owned reconstruction, and local object
comparisons. No external branch was merged, copied, fetched, or contacted.
The parent should preserve the previously queued EXIF candidate separately.
