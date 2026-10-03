# CHANSVm packed-hex count rounding

Base: `a30b5cecb68f4549ef83565a567cc5dd7bd4c0de` (43U).
Leaf: `agent/bittle/chans-pack-union`.

## Retained source-width correction

The sizing and writing passes of `VmBlobPackCommon` both computed
`(count + 1) / 2` in signed 32-bit arithmetic for hexadecimal strings.
The existing parser accepts `H2147483647`, making the addition overflow.
Both sites now add in unsigned 32-bit width, convert the wrapped word to
`s32`, then perform the existing signed division.

This preserves the target's unusual boundary behavior. It does not change
`INT_MAX` into a positive rounded-up size. The original result is
`-1073741824`; the writing pass forwards its signed extension to the existing
`CHANSVmBlobHasSpace` check, which rejects negative sizes. All surrounding
count, size, allocation, and error checks are unchanged.

Unsigned addition is defined modulo 2^32. Converting an out-of-range `u32`
to `s32` is implementation-defined in C, not signed-overflow undefined
behavior. Separate MWCC probes confirm the configured 32-bit compiler's
bit-preserving conversion: `0x80000000` becomes `INT_MIN`, and `0xffffffff`
becomes -1. Its dynamic rounding probe emits the same add, arithmetic-shift,
and carry-add sequence as the original. The host GCC harness uses explicit
32-bit typedefs and independently confirms that conversion behavior.
This is not a claim of portable behavior for every possible C implementation.

## Original and prior-work evidence

- Original `VmBlobPackCommon`: address `0x81453670`, extent `0xA70`.
- Sizing-pass rounding: relative `+0x320` through `+0x330`.
- Writing-pass rounding and signed call argument: `+0x940` through `+0x954`.
- Those words agree directly with the original DOL, independently of the
  extracted object's relocations.
- Earlier CHANS logs covered count validation, padding, parser locals,
  declaration orders, loop structure, and source/getter types. No earlier
  packed-hex `count + 1` wrap correction was found.

## Validation

- Source-extracted baseline arithmetic fails UBSan at `INT_MAX + 1`.
- Candidate passes 1,000,022 direct arithmetic inputs and 11 source-extracted
  parser cases, including `H2147483647`, neighboring odd/even limits, zero,
  ordinary counts, `H*` (-1), and the existing overflowing-digit rejection.
  Star-derived string lengths include zero and the largest u32 byte lengths.
- Two bounded original-DOL instruction interpreters each pass 1,000,013
  inputs against an independent widened-arithmetic reference, including
  INT_MAX neighbors, negative boundaries, and generated nonnegative counts.
  The second slice also verifies signed 64-bit argument extension.
- These are focused parser/arithmetic/slice tests, not complete VM or Wii
  runtime tests. The parser is unchanged and is not generally proven free
  from other arithmetic issues.
- Entire CHANSVm object is byte-identical before/after, including code,
  data, symbols and relocations. SHA256:
  `5bf3f4a0a404e2a574287c16de81d702a1402d9fca416455e84dc1df67c9eb76`.
- All 1,027 report units are unchanged. CHANS exact functions: 222/233;
  exact code: 38,136/53,564; exact data: 6,904/6,904.
- All 222 objdiff-exact functions independently have identical original
  instruction streams. PackCommon remains 97.949104%, 668/668 instructions;
  CHANSVmStep remains 96.98723%, 1,253/1,253 instructions.
- Pool: 125/125 identical. Literal advisory: 233 functions, 40 arguments,
  no candidates, errors, or skips. `git diff --check` passes.

- Final full 43U `all_source`, report, and `ok` gates pass. DOL SHA1:
  `26116613f624061ba99c8d1a299aaa6efa85670d`.
- The initial final-build run stopped when an automatic BSTool refresh was
  blocked. Its resume attempt found that the process had ended. The final
  build used configure.py's supported explicit paths to the existing cached
  compiler, binutils, DTK, objdiff, sjiswrap, and BSTool. No executable was
  replaced and no download was needed. All 1,027 source objects were rebuilt.
- The final object and complete report remain identical to their fresh
  baseline after that full rebuild.

GATE: source-width correctness correction; zero fuzzy, exact, data, or linking
metric changes. The unit remains NonMatching and no linking flags changed.

## Rejected separate scratch-buffer trial

Before the overflow change, one bounded trial replaced PackCommon's cast-based
scratch array with a union whose integer-width members were all used.
MWCC removed two scratch-clearing stores: 668 -> 666 instructions, fuzzy
97.949104% -> 97.500000%. The trial was fully restored; the restored whole
object was verified byte-identical before starting the overflow change.
No union change is retained, and no declaration or register sweep was run.

Reproduction artifacts are in `/tmp/chans-pack-rounding/` and
`/tmp/chans-pack-union/`. No original binary or disassembly is committed.
