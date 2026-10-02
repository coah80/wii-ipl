# NHTTP stdlib source reconstruction, 2026-10-02

Base `b26e248b`, branch `agent/bittle/nhttp-source-reconstruction`, 43U only.
Owned source: `libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL.c`. No headers, metadata,
configuration, linking flags, binary data, or other source files changed.
The earlier `four-leaves-r9.attempts.md` and other worker logs are untouched.

## Target-grounded changes

### NHTTPi_compareToken

The target enters through its case-folded equality test, then checks the raw left
byte for NUL/space before advancing the two pointers. It retains the unsigned
byte separately and sign-extends it for both the case fold and termination check.
The baseline unconditional loop placed that control-flow boundary differently
and compiled to 44 instructions rather than the target's 45.

The retained while condition captures the raw u8 load and explicitly sign-extends
it into LowerCase. The body reuses that captured byte for termination. LowerCase
returns its conditional value directly, preserving the target's separate folded
value lifetime. This recovers the complete 45-instruction control-flow shape.
The common helper's other callers remain unchanged at the instruction level.
A separate token-only helper gave the same result; it was removed to avoid
unnecessary duplication.

Remaining differences: two initial constant loads are reversed, and eight
instruction operands use different scratch/callee-saved registers. This is not
an exact match.

### NHTTPi_Base64Encode

The target retains signed length/padding comparisons. The length local is now
s32, matching those comparisons without the previous mixed-sign comparisons.
Each quartet snapshots its three signed input bytes before writing the output,
then combines each later byte's high fragment with the preceding byte's masked
low fragment. This expresses the target's byte-load and index dependency
structure more closely, preserving the 119-instruction body size.

The target and existing implementation use signed byte shifts, a NUL-terminated
input, and full three-byte reads even for a short final group. This candidate does
not broaden the API to arbitrary binary data or repair those original constraints.
The repository's caller supplies a separate temporary source and authorization
output buffer (`d_nhttp.c`, NHTTP_CreateRequest proxy authorization path).

## Experiments

- Recovered the previously logged loop-test/raw-byte/ternary-fold approach rather
  than repeat register/declaration searches. Local conditional-loop alternatives
  were measured against the target before retaining the compact while condition.
- One exploratory assignment/read condition was found to be unsequenced. It was
  withdrawn, never behavior-tested, and is not part of the retained source.
- Signed/unsigned/raw byte representations and explicit sextet fragments were
  checked against target load/sign-extension evidence. Signed byte snapshots
  with the retained index grouping gave the best compact source.
- Stream-cursor forms generated identical code and were not retained.
- A separate quartet helper improved Base64 only 67.63025 -> 67.79832%; it was
  discarded as unnecessary source expansion. There is no new helper in the diff.
- No declaration/register sweep, inline assembly, use-site volatile, dummy value,
  padding, compiler-option change, or linking experiment was performed.

## Verification

Before -> after:
- NHTTPi_compareToken: 54.622223 -> 98.844444% fuzzy; 44 -> 45 instructions against
  target 45. Final ctxdiff: 10 positional differences.
- NHTTPi_Base64Encode: 60.285713 -> 67.63025% fuzzy; 119/119 instructions unchanged.
  Final ctxdiff: 67 positional differences (baseline 58); aligned objdiff improves
  despite that positional metric. Exact dependency scheduling remains open.
- Unit fuzzy: 87.93594 -> 93.03203%.
- Exact functions 11/14, exact code 1388/2248, data 112/112 (100%) and linked status
  are unchanged. All 11 previously exact functions have ctxdiff diffs 0.
- The unchanged strnicmp remains 99.76471%, 51/51 instructions, two constant-order
  differences. LowerCase's other exact users remain exact.
- Pool: the one alphabet string is identical. .data's 65 bytes and .rodata's
  36 bytes equal the prefixes of their 72-byte/40-byte target sections. Existing
  trailing target alignment extents are unchanged; no padding was introduced.
- Literal-reference audit: 14 functions analyzed, no candidates, skips or errors;
  zero statically addressed call arguments, so this is not a separate proof of
  complete data matching.
- Full 1027-unit report: zero exact-function/code/data/fuzzy regressions.
- Full 43U build and build/43U/ok passed. DOL SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

Host behavior validation compiles both unchanged production sources (baseline
and candidate) with -fsigned-char and fixed-width SDK type shims:
- 75,536 compareToken cases: all 65,536 first-byte pairs plus 10,000 seeded
  multi-byte/case-fold/mismatch cases, against an independent token reference.
- 3,033 Base64 cases: known answers, every length 0..1024, and 2,000 seeded ASCII
  strings up to 4096 bytes, against Python base64. Return length, NUL terminator
  and a 16-byte output canary are checked. Inputs have readable zero tail bytes
  for the original full-triplet reads. High-bit/binary inputs are not claimed.

Private local evidence: `/tmp/nhttp-source-reconstruction/` contains baseline and
final reports, all function ctxdiffs, pool/literal audits, full-build.log,
validate_nhttp.py, vectors.log, and the rejected local experiments. No retail
assembly or binary is included in this commit.

GATE: validated partial control/data-flow/type reconstruction; no regressions.
Exact matching and linking remain open. Frozen for independent parent validation.
