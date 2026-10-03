# AOSS status entry contract, 2026-10-03

Baseline: `a2c008c4`, 43U. This recovers the one-line source-contract
correction previously preserved in `0173f9cc`, with fresh current-context
verification. It claims no exact, fuzzy, data or linking gain.

## Source and ABI evidence

`AOSS.c:288` declares `int AOSSi_Status(int status)`. Its only six callers,
all in `AOSS_Init_old`, pass progress states 0, 1, 2, 3, 5 and 4. The
definition in `AOSSLink.c:341` instead declared no parameters. The correction
changes that definition to `int AOSSi_Status(int status)` and leaves its
body, the callers, callback types and callback implementation unchanged.
An unused formal is a natural implementation of an entry point whose
platform-specific handler does not use the supplied progress state. It
removes the incompatible cross-translation-unit function types.

The original DOL, verified against SHA1
`26116613f624061ba99c8d1a299aaa6efa85670d`, explicitly supplies the following
outgoing r3 values before calls to `AOSSi_Status` at `0x813FD99C`:

- `0x813FE640`: 0, source line 502
- `0x813FE89C`: 1, source line 601
- `0x813FF1E8`: 2, source line 968
- `0x813FF218`: 3, source line 975
- `0x813FF248`: 5, source line 983
- `0x813FF67C`: 4, source line 1151

A scan of all 12,526 recorded text-function extents finds precisely these
six direct calls. The 1,028 original object files contain precisely six
relocations to this symbol, all direct calls in AOSS.o; none takes its address.
The 13-instruction callee conditionally invokes the callback and returns zero.
It leaves incoming r3 untouched before the callback. The sole installed
callback has a four-byte no-op target at `0x813FCA08`.

Those facts do not establish a unique original formal parameter name or
callback payload contract. They support keeping the explicit caller
arguments and accepting the argument at the definition. No argument is
removed, synthesized, forwarded differently or newly consumed.

## Fresh verification

- Rebuilt the unchanged baseline AOSSLink.o in the fresh leaf and compared it
  byte-for-byte with the pinned main object before editing
- Rebuilt the corrected AOSSLink.o; its entire file is byte-identical to the
  baseline, including code, data, symbols and relocations
- Full default 43U build passes; all 1,027 source-object SHA256 hashes remain
  equal to pinned main, and both fresh generated reports equal the baseline
- All 12 existing exact AOSSLink functions retain zero normalized instruction
  differences; AOSSi_Status is 13/13 instructions, ctxdiff 0, objdiff 100%
- Unit unchanged: 12/14 exact, 668/2196 exact code bytes, fuzzy 99.007286%,
  data 2432/2432
- Pool: 0/0, identical; literal audit: 14 functions, no candidates, errors or
  skips, and zero narrow-string arguments to compare
- Explicit progress, report and build/43U/ok targets pass; rebuilt DOL SHA1
  remains `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

No Wii/network execution is claimed. Object identity establishes emitted-code
neutrality; the source correction is justified by the existing caller contract.
