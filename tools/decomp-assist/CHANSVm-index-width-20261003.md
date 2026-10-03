# CHANSVm string-index width correction

Baseline: `7b8dbf2c96aa9b4490df35932850c59886f76be3` in the prepared
`agent/bittle/chinese-code-width` leaf. Before editing, the owned CHANSVm source
was also identical to the available `origin/main` at `6619098e`. The earlier
Chinese investigation remains unchanged. Only CHANSVm.c and this log change.

## Correction

The SET_INDEX string path parsed into a `u64`, reconstructed that value through
`VM_S64_FROM_U64`, then cast it back to `u64` for the bound check. The macro's
signed 64-bit high-word left shift overflows when the parsed value has bit 63
set. For example, parsing "-1" reaches a signed shift of 4294967295 by 32.

Compare the original `u64` directly against the existing `0xFFFFFFFE` bound.
Remove the now-unused macro. The integer and floating paths are unchanged.
This removes undefined source behavior; it does not claim a change to the
current MWCC executable, a fuzzy gain, or a new exact function.

## Original evidence

- Original CHANSVmStep is at `0x81456354`, with extent `0x1394`.
- `0x814563B8` and `0x814563BC` establish the bound's high and low words as
  zero and `0xFFFFFFFE`.
- The parsed-string check at `0x81456E90` through `0x81456EB4` reads the two
  parsed words and performs an unsigned two-word comparison. Values greater
  than the bound select the existing SET_INDEX error; accepted values forward
  their low word as the index.
- These instruction words were checked directly against the original DOL,
  independently of relocation matching. The DOL has the required SHA1 below.
- CHANSVmParseInt calls `strtoull` and stores its unsigned result. The local MSL
  implementation (`strtoul.c`, lines 327–348) explicitly applies a negative sign
  in unsigned width. Both helpers are already exact in the live report.
- Prior CHANSVm attempt logs were checked; the typed integer/float comparison
  work did not address this signed reconstruction in the parsed-string path.

## Tests and measurements

- Baseline source-extracted UBSan harness fails on "-1" with signed left-shift
  overflow. The candidate passes 300,028 parsed-value and unsigned-boundary
  cases without a sanitizer error.
- Inputs include zero, `0xFFFFFFFE`, `0xFFFFFFFF`, `0x100000000`, signed-64
  boundaries, maximum unsigned-64, negative decimal strings, parse failures,
  and deterministic generated values. The unusual unsigned parsing of
  "-18446744073709551615" to 1 remains accepted, matching the existing parser.
- A separate bounded interpreter executes the original DOL comparison slice
  for 300,010 values, checking its error branch and accepted index against an
  independent high-word/low-word bound reference. Every case passes.
- These are focused host/slice tests, not complete VM or Wii runtime tests.
  The parser harness uses a UTF-16-to-ASCII shim and host `strtoull`; MSL's
  negative-sign behavior was also checked in its local source.
- Entire compiled object, including all code, data and relocations, is
  byte-identical before/after. SHA256:
  `f971cabf817dba7e5cb240df01e1e8f814bb0a973e357a594d031046a56e691b`.
- Complete 1,027-unit report is unchanged. CHANSVmStep remains 96.98723%,
  1,253/1,253 instructions. Unit fuzzy remains 99.4341%.
- Exact functions remain 222/233, each individually checked with ctxdiff:
  zero differences. Exact code remains 38,136/53,564 bytes; data 6,904/6,904.
- Pool: 125/125 strings identical. Literal advisory: 233 functions, 40 arguments,
  no candidates, skips or errors.
- Full 43U `all_source`, report and `ok` gates pass using the assigned wrapper
  and WIBO_SJIS_MISSING_IMPORTS=1. `git diff --check` passes.
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.

Private local reproduction files are in `/tmp/chans-index-width/`, including
baseline/candidate sources and objects, test_width.py, check_original.py,
sanitizer output, original-address checks, pool/literal results and build logs.
No original binary or disassembly is committed. No header, metadata, compiler,
linking, other-region, remote, or register-allocation change was made.

GATE: source-width correctness fix; compiler output and all progress preserved.
