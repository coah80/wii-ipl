# NHTTP token byte-role recovery, 2026-10-03

Base: `81ba2799`. One authorized two-line trial in
`libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL.c`. No other function, shared helper,
header, compiler setting or linking configuration was changed.

## Source roles and historical evidence

NHTTPi_compareToken retains the raw left byte across its folded comparison,
then signs that raw value again for the matched NUL/space termination test.
The target loads the right byte and folds its signed value first, then loads
the left byte into a separate zero-extended word before signing/folding it.
The raw left word remains separate from both folded comparison results.

Use u32 for that actual zero-extended raw-left value, and express the right
input through the same explicit u8-load/s8-conversion boundary as the left.
No extra local, helper, load, dummy use or register-forcing construct is added.
The shared LowerCase helper and literal termination tests are unchanged.
This is data-representation reconstruction, not a changed byte-domain contract.

The perm2 attempt log had measured 99.51111% for the word-lived raw left byte
and 99.73333% with the right raw-byte conversion, but discarded both solely
because they were nonexact. Those old temporary sources are unavailable here;
the minimal form was independently reconstructed from current source and
original instructions. Only that one two-line form was compiled this round.

## Byte, ordering and termination proof

- All 256 byte values were checked against the target's actual carry-based
  signed comparisons. Only ASCII A..Z gain 32; bytes 128..255 remain signed
  negative values for comparison, preserving equality with the same raw byte.
- A private interpreter executes the original 45-instruction function on all
  65,536 byte pairs plus five multi-byte/high-bit/termination cases. Return
  values and ordered byte-read traces agree with the proposed semantics.
- The compiled candidate differs from original only at two initial li
  instructions: zero and 'Z' are initialized in the opposite order. They write
  distinct registers before either value is used and do not change condition
  state. After commuting those two independent instructions, all 45 match
  literally, including right-before-left loads, both signed conversions,
  folded comparisons, pointer advances and the saved raw-byte stop test.
- A matched NUL or literal space returns 0; every mismatch returns -1. Other
  whitespace bytes are ordinary token data. The comparison still happens
  before termination, and no new dereference or store is introduced.

## Fresh gates

- NHTTPi_compareToken: 98.844444 -> 99.73333%, 45/45 instructions, two residual
  constant-scheduling differences. This is not an exact match.
- Unit: 99.88612 -> 99.9573%; exact functions 12/14 and code 1864/2248 preserved;
  data 112/112 preserved. Linking unchanged.
- All 13 unrelated functions' instruction streams and resolved relocations are
  identical to baseline, including the 12 exact functions. Every allocated data
  byte and section extent is unchanged. Pool 1/1 identical.
- Literal-reference advisory: all 14 functions analyzed, no candidates, skips
  or errors; this function has no string arguments at external calls.
- Full 1,027-unit reports show only compareToken improved, with no fuzzy,
  exact-function, exact-code or data regression. Post-build final report equals
  the candidate report.
- Production C: 75,536 exhaustive byte-pair and seeded token comparisons pass
  against an independent ASCII-fold/literal-termination reference for both
  baseline and candidate.
- ASan/UBSan: 95,504 byte-pair, seeded token, aliased and overlapping-input
  comparisons pass; all input bytes remain unchanged. The harness extracts
  actual production function/helper bodies and uses signed-char host settings.
  Leak detection is disabled for ptrace; address/UB instrumentation is enabled.
- Full 43U build and build/43U/ok pass. DOL SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`. git diff --check passes.

Private evidence: `/tmp/nhttp-token-byte-roles/` contains source/object snapshots,
reports, host/sanitizer harnesses and results, pool/literal/ctxdiff and build logs.
The prior read-only byte proof and proposed diff are preserved separately in
`/tmp/nhttp-token-recovery-screen/`. Original assembly and objects remain private.

GATE: passing two-line partial recovery, frozen for independent review.
No additional constant-order or register trial was attempted.
