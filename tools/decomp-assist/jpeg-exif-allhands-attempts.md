# EXIF parser reconstruction and aliasing audit

Base: `2a33684c` on `agent/bittle/allhands-jpeg-decompile`; EXIF source itself is
unchanged from baseline `449529d9`. This is a separate candidate from the prior
JPEG converter/IDCT commit. Those files and their logs were left unchanged.

## Retained reconstruction

1. The IFD0 entry parameter is `u8*`, with corresponding call-site casts from the
   parser's read-only directory cursor. With the reconstructed `const u8*`
   parameter, MWCC hoists all four version-byte loads before their stores.
   Removing this unsupported qualifier reproduces the original interleaved
   load/store sequence for tags 0x9000, 0x9101 and 0xA000.
2. IFD0's decoded field type is widened to `u32` and both entry fields use the
   existing `readExifU16` reader. This reproduces the target's eager zero
   extension and initial instruction order; it does not change TIFF field size.
3. IFD1 explicitly includes ignored 0x011C and 0xA000..0xA002 cases alongside
   existing ignored tags. Target dispatch compares against 0x011C and 0xA004;
   these case labels improve the recovered decision tree. The precise original
   no-op case list cannot be proved uniquely, since unknown tags also return
   unchanged. No new tag interpretation or payload write is introduced.
4. IFD1 rational denominators use `thumbnailData + (offset + 4)` without a
   redundant same-type cast.

No new exact functions. Exact stays 3/6, matched code 1348/5088 bytes, allocated
data 0 bytes / 100%, and linking is unchanged. Unit fuzzy 96.50157 -> 98.94104.

| Function | Before | After | Source/target instructions |
| --- | ---: | ---: | ---: |
| TMCCJPEGDecGetOffsetEXIF | 100 | 100 | 155/155, ctxdiff 0 |
| TMCCJPEGDecGetInfoEXIF | 100 | 100 | 132/132, ctxdiff 0 |
| TMCJPEGDEC_exif_parse | 99.43396 | 99.43396 | 212/212 |
| TMCJPEGDEC_IFD0_tag_parse | 94.46986 | 99.386696 | 480/481 |
| TMCJPEGDEC_IFD1_tag_parse | 93.099174 | 96.14876 | 239/242 |
| TMCJPEGDEC_ThumbnailCheck | 100 | 100 | 50/50, ctxdiff 0 |

IFD0 still lacks the original low-tag `bltlr` leaf. Aligning that instruction and
its branch displacements leaves 32 GPR-operand differences in the two rational
field cases. IFD1 still has decision-tree and register differences. The parser
retains 21 GPR-operand differences. Nothing here claims exact completion.

## Concrete behavioral distinction

An internal IFD0 entry can be arranged with its four version bytes overlapping
the destination by one byte. Initial source bytes 01 02 03 04 produce:

- Baseline compiled code: destination 01 02 03 04
- Original object: destination 01 01 01 01
- Corrected compiled code: destination 01 01 01 01

This is evidence about the internal parser's byte-copy/aliasing behavior. It is
not a claim that ordinary nonoverlapping EXIF input was decoded incorrectly, or
that a public API vulnerability has been established. Both byte orders and all
three version fields were checked at offsets -3 through +3, giving 42 overlap
cases. The unchanged baseline object fails this regression test; the final
object passes all 42. Local destination casts, explicit loops and removal of
other const qualifiers did not fix the discrepancy and were restored.

## Validation

- Pool checked before tuning and after the final build: identical, zero strings
- No allocated non-code sections in either EXIF object
- Fresh official report: all six function scores compared with baseline,
  zero regressions; all three exact functions retain ctxdiff zero differences
- Full 4.3U build: PASS
- DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check 2a33684c`: PASS, including the committed candidate diff
- No header/configuration/linking edits, no changes to the separately owned
  entropy decoder, no remote writes or original binary data committed

Build/report commands:

```sh
python3 configure.py --version 43U --wrapper ../toolchain/wibo-build/wibo
WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja
build/tools/objdiff-cli report generate -p . -o build/43U/report.json -f json
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/pool_diff.py build/43U/src/libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse.o build/43U/obj/libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse.o
PYTHONPATH=../local-tools ../.venv/bin/python tools/decomp-assist/ctxdiff.py libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse <symbol>
../.venv/bin/python tools/decomp-assist/jpeg_exif_differential_audit.py
../.venv/bin/python tools/decomp-assist/jpeg_exif_differential_audit.py --overlap-only
```

## Differential test scope

`jpeg_exif_differential_audit.py` is a read-only bounded integer PPC interpreter
and deterministic test generator. It reads local ELF objects and never writes
original executable bytes to the repository. It is a separate test tool; the
previous converter/IDCT audit remains unchanged.

- 267,282 paired calls, seed 449529
- Every 16-bit tag selector in both byte orders for both IFD handlers
- Field types 0, 3, 4 and 0xFFFF; valid, boundary, out-of-range and wrapping
  offsets for supported scalar/rational/byte-array tags
- Header sizes and offsets, valid/invalid byte order and TIFF magic, truncated
  entry arrays, IFD0/IFD1/Exif-directory chains and directory-boundary lengths
- 42 overlapping version-byte cases that distinguish baseline from original
- Every non-stack byte compared, including guard regions; parser return values,
  stack pointer, LR and GPR14..GPR31 preservation checked
- Complete instruction-address coverage of IFD0 and the central parser in both
  objects; IFD1 covers every source instruction and 241/242 target instructions
  (one unreachable return in the target dispatch is not visited)

Limitations: this is not formal equivalence or a Wii runtime test. Instruction
coverage is not exhaustive path/input coverage. The custom interpreter models
only the observed integer subset, condition comparisons and internal EXIF calls;
unsupported instructions/relocations/callees fail closed. FPU, XER overflow,
exceptions, timing, cache/MMIO and a full system ABI are not modeled. Relocations
use collision-checked symbol tokens; actual linked addresses are not tested.
Public JPEG I/O, thumbnail decoding, arbitrary pointer values and all possible
payload alias layouts are outside this test. The three exact wrappers are
checked by objdiff/ctxdiff rather than executing their external dependencies.

Run from the repository root with pyelftools and Capstone available, and without
Python's `-O` option. `--source-object` and `--target-object` can select separately
compiled objects, allowing the overlap regression to be reproduced on baseline
without changing the working tree. Final output is in
`jpeg-exif-allhands-differential-results.txt`.

## Existing external branch overlap

Read-only comparison used the already fetched ref
`origin/agent/w1009/tmc` at `cd90be696cb86258a1bc9fb9dc2b304f2bed318d`.
No fetch, author communication, branch checkout or merge was performed.

Its `1c7cf40c` independently removes const from both tag-entry parameters, so the
central IFD0 qualifier correction overlaps. Its `81440c32` then uses a u16 tag,
u16 type and explicit tag remask. Its no-op case ranges differ from this
candidate's explicit ignored tags. It also changes the shared 16-bit reader and
parser declaration order. This candidate does not contain those changes.

An isolated `/tmp` compile of that branch's EXIF source, using the current
checkout's original MWCC flags, produced:

| Measure/function | This candidate | cd90be69 EXIF object |
| --- | ---: | ---: |
| Unit fuzzy | 98.94104 | 99.01337 |
| Central parser | 99.43396 | 98.679245 |
| IFD0 | 99.386696 | 98.37838 |
| IFD1 | 96.14876 | 99.194214 |
| Exact functions | 3/6 | 3/6 |

Neither candidate wholly supersedes the other. This candidate has the better
IFD0 and preserves the current parser score; the external candidate has the
better IFD1. Integration must preserve the parser score and independently
revalidate any combined source. The isolated comparison is not a full gate of
the external branch or its other files.

Relative to baseline 449529d9, the external RGB565 edits concern its setter and
do not overlap the prior candidate's RGB444 body. Its RGBA420 edge edits overlap
that prior candidate's changed expression context. It does not change IDCT.
The previously committed JPEG candidate remains separate and unchanged.

## Attempts

All rejected/equal variants were restored. The lower-tag 0x0100 experiment had a
fuzzy improvement but was explicitly discarded after review: the original
branch shape does not establish that particular no-op label, and it changed
other lower dispatch comparisons. It is absent from the final source.

### trials

```text
TMCJPEGDEC_IFD0_tag_parse word-width-field-type: 94.469860 -> 95.122660; RETAIN
TMCJPEGDEC_IFD0_tag_parse explicit-ignored-compression-return: 95.122660 -> 94.914764; restore
TMCJPEGDEC_IFD0_tag_parse explicit-ignored-compression-break: 95.122660 -> 95.122660; restore
TMCJPEGDEC_IFD1_tag_parse recognized-ignored-planar-and-pixel-tags: 93.099174 -> 95.942150; RETAIN
TMCJPEGDEC_IFD1_tag_parse ignored-low-strip-offset-own-return: 95.942150 -> 95.342970; restore
TMCJPEGDEC_IFD1_tag_parse ignored-orientation-own-return: 95.942150 -> 95.533060; restore
TMCJPEGDEC_IFD1_tag_parse ignored-datetime-own-return: 95.942150 -> 95.528920; restore
```

### control-trials

```text
TMCJPEGDEC_IFD0_tag_parse explicit-unknown-tag-return: 95.122660 -> 94.498960; restore
TMCJPEGDEC_IFD0_tag_parse explicit-unknown-tag-break: 95.122660 -> 95.122660; restore
TMCJPEGDEC_IFD1_tag_parse explicit-unknown-tag-return: 95.942150 -> 95.876030; restore
TMCJPEGDEC_IFD1_tag_parse explicit-unknown-tag-break: 95.942150 -> 95.942150; restore
TMCJPEGDEC_IFD1_tag_parse ifd1-orientation-uses-unknown-exit: 95.942150 -> 95.756195; restore
TMCJPEGDEC_IFD1_tag_parse ifd1-planar-uses-unknown-exit: 95.942150 -> 91.694214; restore
```

### ignored-tag-trials

```text
TMCJPEGDEC_IFD0_tag_parse ignored-image-fields-before-compression: 95.122660 -> 95.110180; restore
TMCJPEGDEC_IFD1_tag_parse ignored-image-fields: 95.942150 -> 95.735535; restore
TMCJPEGDEC_IFD1_tag_parse ifd1-planar-logical-case-order: 95.942150 -> 95.942150; restore
```

### reader-trials

```text
TMCJPEGDEC_IFD0_tag_parse shared-exif-tag-reader: 95.122660 -> 95.195430; RETAIN
TMCJPEGDEC_IFD0_tag_parse shared-exif-type-reader: 95.195430 -> 95.517670; RETAIN
TMCJPEGDEC_IFD0_tag_parse shared-exif-short-reader: 95.517670 -> 95.517670; restore
TMCJPEGDEC_IFD1_tag_parse shared-exif-tag-reader: 95.942150 -> 95.942150; restore
TMCJPEGDEC_IFD1_tag_parse shared-exif-short-reader: 95.942150 -> 95.942150; restore
```

### lower-tag-trials

```text
TMCJPEGDEC_IFD0_tag_parse ignored-lower-tags-(256,): 95.517670 -> 93.004160; restore
TMCJPEGDEC_IFD0_tag_parse ignored-lower-tags-(257,): 95.517670 -> 93.004160; restore
TMCJPEGDEC_IFD0_tag_parse ignored-lower-tags-(258,): 95.517670 -> 95.505196; restore
TMCJPEGDEC_IFD0_tag_parse ignored-lower-tags-(256, 257): 95.517670 -> 93.004160; restore
TMCJPEGDEC_IFD0_tag_parse ignored-lower-tags-(256, 258): 95.517670 -> 93.004160; restore
TMCJPEGDEC_IFD0_tag_parse ignored-lower-tags-(257, 258): 95.517670 -> 95.505196; restore
TMCJPEGDEC_IFD0_tag_parse ignored-lower-tags-(256, 257, 258): 95.517670 -> 95.505196; restore
TMCJPEGDEC_IFD1_tag_parse ignored-lower-tags-(256,): 95.942150 -> 96.665290; RETAIN
TMCJPEGDEC_IFD1_tag_parse ignored-lower-tags-(257,): 96.665290 -> 96.665290; restore
TMCJPEGDEC_IFD1_tag_parse ignored-lower-tags-(258,): 96.665290 -> 95.735535; restore
TMCJPEGDEC_IFD1_tag_parse ignored-lower-tags-(256, 257): 96.665290 -> 96.644630; restore
TMCJPEGDEC_IFD1_tag_parse ignored-lower-tags-(256, 258): 96.665290 -> 96.256195; restore
TMCJPEGDEC_IFD1_tag_parse ignored-lower-tags-(257, 258): 96.665290 -> 95.735535; restore
TMCJPEGDEC_IFD1_tag_parse ignored-lower-tags-(256, 257, 258): 96.665290 -> 95.735535; restore
```

### byte-copy-trials

```text
TMCJPEGDEC_IFD0_tag_parse alias-preserving-version-byte-copy: 95.517670 -> 95.517670; restore
```

### version-loop-trials

```text
TMCJPEGDEC_IFD0_tag_parse forward-version-byte-loops: 95.517670 -> 95.517670; restore
```

### qualifier-trials

```text
TMCJPEGDEC_IFD0_tag_parse mutable-entry-view: 95.517670 -> 99.386696; RETAIN
TMCJPEGDEC_IFD1_tag_parse mutable-entry-view: 95.942150 -> 95.942150; restore
```

### pointer-trials

```text
TMCJPEGDEC_IFD1_tag_parse mutable-rational-byte-view: 95.942150 -> 95.942150; restore
TMCJPEGDEC_IFD1_tag_parse direct-denominator-byte-address: 95.942150 -> 96.148760; RETAIN
```
