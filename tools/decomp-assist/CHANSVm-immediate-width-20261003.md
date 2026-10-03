# CHANSVm immediate integer accumulation

Base: `a52b3390` on `agent/bittle/chans-scalar-contracts` (43U).
This isolated commit follows, but does not alter, the boolean-output correction.

## Correction

`VmLoadImmInteger` assembled bytes by repeatedly left-shifting a signed
64-bit accumulator. An eight-byte immediate beginning with 0x80 through
0xFF can overflow that signed shift on the final iteration. Use an unsigned
64-bit accumulator, then convert the final word to the existing signed
`vmInteger` argument of `CHANSVmSetInteger`.

The original helper at `0x81455D88` shifts and combines high/low 32-bit words
modulo 64 bits. It reads unsigned bytes in big-endian order. Short immediate
widths do not sign-extend: one-byte 0xFF is 255, not -1. The target tail call
preserves VM/object in r3/r4 and supplies high/low value words in r5/r6.
Step's two call sites supply counts 1, 2, 4, or 8 for immediate loads, and
1 for binary immediate operations. No negative-width caller was found.

Unsigned shifts are defined. The final out-of-range unsigned-to-signed
conversion is implementation-defined in C; configured MWCC probes verify
bit-preserving conversion for bit 63, all bits set, and dynamic input.
The dynamic conversion emits only a return instruction. Host GCC tests
independently verify the selected implementation's behavior. No universal
portable-C conversion claim is made.

## Verification

- Source-extracted baseline UBSan fails while assembling `80 00 00 00 00
  00 00 00`. The candidate passes 315,813 cases: every combination of
  0x00/0x7F/0x80/0xFF at widths 1/2/4/8, generated inputs, and zero width.
  Tests check value bits, VM/object callback arguments, and propagated result.
- A bounded interpreter executes the original helper's 16 nonbranch-tail
  instruction words, independently checked against the original DOL.
  The tail branch destination is verified as `CHANSVmSetInteger`.
  All 165,813 original-DOL cases agree with an independent big-endian
  unsigned reference and with r3/r4/r5:r6 call contracts.
- These are focused host/helper-slice tests, not complete VM or Wii runtime
  execution. Counts outside the observed 1/2/4/8 contract are not generally
  validated; zero was checked as an additional no-read boundary.
- VmLoadImmInteger remains exact: 17/17 instructions, ctxdiff 0 differences.
- Entire CHANSVm.o remains byte-identical to both the preceding commit and
  initial branch baseline, including code/data/symbols/relocations. SHA256:
  `5bf3f4a0a404e2a574287c16de81d702a1402d9fca416455e84dc1df67c9eb76`.
- All 1,027 report units remain unchanged. All 222 exact functions were
  independently compared with the original and have zero differences.
- Pool: 125/125. Literal advisory: 233 functions, 40 arguments, no
  candidates/errors/skips. `git diff --check` passes.
- Full 43U `all_source`, report, and `ok` gate passes with existing cached
  tooling. DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.

Artifacts: `/tmp/chans-step-abi/test_immediate.py`,
`check_immediate_original.py`, conversion probe, and build/test results.
No original binary or disassembly is committed.

GATE: source-width correctness correction; no fuzzy/exact/data/link gain.
