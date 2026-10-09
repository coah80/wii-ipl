# clean3-c7 JPEG cleanup

Worktree `/mnt/drive2/projects/wii-ipl-workers/clean3-c7`, branch `agent/w1009/clean3-c7`.
Starting commit `8a67b68cf`. Baseline completion check returned `DECOMPLETE_OK`.
Baseline DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`.

## Prior evidence and source reference

Read `clean3-head.md`, `cleanup-common.md`, local `AGENTS.md`, and the cleanup-c5,
cleanup2-x9 and cleanup2-w5 attempt logs. Apply unslop and writing-for-agents.
Skip the previously rejected texture pragma deletion, declaration initialization,
sampling-case scopes, first-store splitting and alpha arithmetic changes. Keep the
buffer readers' explained empty branches and shared success exits. Skip the
already rejected direct rewrites of decapi's result helpers and Huffman-entry copies.

Read the older JPEG library in hotlandsoftware/wii-news-channel at revision
`128e3ffbaee9e70bd175c5f66a44fb8430068629` into `/tmp/clean3-c7-news-*`.
Reference: https://github.com/hotlandsoftware/wii-news-channel/blob/128e3ffbaee9e70bd175c5f66a44fb8430068629/src/revolution/TMCC_JPEG/jpgd_internal.h

Its `jpgd_internal.h` names the output format, EOI-check flag and planar fields.
The local EXIF parser proves that init offset 0x24 selects thumbnail processing;
the state byte at 0x21 disables EOI checking. These receive separate names.
The older library does not identify the untouched reserved byte ranges.

Before editing, rebuilt and saved all 15 JPEG objects plus iplJpegDecoder.
Every unit was exact and linked. Compare every allocated section and normalized
relocation destination against these saved objects for each compiled trial.
Compiler metadata and local literal symbol names do not establish byte changes.

## Retained changes

- tmc_jpeg.h and its callers: name thumbnailMode, outputFormat and noEoiCheck;
  name alignment bytes and reserved ranges; expose the existing planar members
  and typed EXIF data in every state declaration. Remove the planar-only macro
  from Texture_MCUtoY8U8V8.c. All 16 rebuilt objects preserve every allocated byte
  and relocation destination.

## Compiled trials

- `entropy-structured-if`: rejected; .text; TMCJPEGDEC_set_entropytbl: 14 diffs, 38/38 instructions.
- `sof-sampling-break`: rejected; .rela.text, .text; TMCJPEGDEC_parse_sof: 107 diffs, 225/223 instructions.
- `sos-component-break`: rejected; .rela.text, .text; TMCJPEGDEC_parse_sos: 73 diffs, 115/112 instructions.
- `mcu-typed-frame-view`: rejected; .text; TMCJPEGDEC_decompmcu: 13 diffs, 113/113 instructions.
- `sos-typed-map-byte`: retained; all allocated sections and relocations identical.
- `entropy-structured-nested-if`: retained; all allocated sections and relocations identical.
- `sof-sampling-inline-selection`: rejected; .text; TMCJPEGDEC_parse_sof: 21 diffs, 223/223 instructions.
- `converter-RGB565-rounding-inline-no-pragma`: rejected; .rela.text, .text; TMCJPEGDEC_set_converterRGB565: 169 diffs, 169/170 instructions.
- `converter-RGBA8-rounding-inline-no-pragma`: rejected; .rela.text, .text; TMCJPEGDEC_set_converterRGBA8: 169 diffs, 169/170 instructions; TMCJPEGDEC_converterYUV411toRGBA8: 6 diffs, 242/242 instructions.
- `converter-Y8U8V8-rounding-inline-no-pragma`: rejected; .rela.text, .text; TMCJPEGDEC_set_converterY8U8V8: 195 diffs, 195/196 instructions.
- `entropy-zero-comparison`: rejected; .text; TMCJPEGDEC_set_entropytbl: 18 diffs, 37/38 instructions.
- `mcu-named-block-count-offset`: retained; all allocated sections and relocations identical.
- `exif-thumbnail-buffer-offset-name`: retained; all allocated sections and relocations identical.

## Final source decisions

- Public header: all 11 unk names are removed. Three consumed fields receive
  semantic names. The known planar and EXIF data replace opaque byte ranges.
  Unused ranges remain reserved; their original purpose is unproven. Alignment
  members receive names. Move the existing output-format enum to the public API.
- Internal header: remove the duplicate-location output-format enum.
- iplJpegDecoder.cpp: use named thumbnail/output fields and RGB565 format constants.
- exif_parse.c: use named init fields, consistent scaleFactor/noEoiCheck fields
  for the state view, and thumbnailBufferOffset for the buffer-range calculation.
- decapi.c: use named init and EOI-check fields. Keep both shared error exits and
  the wave-2 result helpers whose direct forms were already rejected.
- jdec_main.c: remove the AC-table goto and return through structured branches.
  Replace the shifted component-struct view with the actual map-byte pointer.
  Name the block-count offset with offsetof of the existing frame type. A fully
  typed frame view changed 13 instructions and was restored. The simpler AC0
  condition dropped one instruction and was restored.
- Preserve the sampling/component-search gotos: structured break forms add two
  or three instructions; the sampling helper preserves size but changes 21
  instructions. The older library uses the same two nested-search exit patterns.
- Preserve err_restart's stream reset and its existing compiler comment. The
  final matching effort-policy entry records that this reset keeps the exact
  loop-exit branch. Do not repeat its exhausted removal trials.
- All three texture setters keep their level-1 scopes and existing comments.
  Moving dimension rounding into an ordinary inline helper without the pragma
  still removes one setter instruction. RGBA8 also changes six operands in its
  4:1:1 converter. Restore all three trials. Y8U8V8 drops its redundant planar
  declaration macro because the public state now always has those real fields.
- No use-site volatile access exists in the assigned JPEG source. Keep the
  previously explained buffer branches and Huffman copies unchanged.

## Final verification

Gate ran once with --quick over all 15 JPEG units and iplJpegDecoder. Log:
`/tmp/clean3-c7-final-gate.log`. GATE PASS, full build ok, zero regressions,
zero added forbidden patterns and zero readability warnings. The gate used
baseline 04d3d1e8, the immediate parent of the docs-only starting commit.

Fresh build/43U/report.json and build/43U/ok pass. DECOMPLETE_OK and ASM INVENTORY
PASS, with 162 original SDK assembly functions and zero placeholders. DOL SHA1
`26116613f624061ba99c8d1a299aaa6efa85670d`.

All 16 owned units retain 100 exact functions and 100% code, data, function,
section and link measures. Every allocated section and normalized relocation
matches the pre-edit object. Focused pool checks are identical. Focused ctxdiff
checks are zero for init, EXIF info/thumbnail checks, MCU decode, SOS parsing,
entropy selection, JpegDecoder::decodeJpg and JpegDecoder::get_orientation.
Focused log: `/tmp/clean3-c7-focused.log`. Whitespace check passes.

Global exact counts remain 12563/12563 functions and 1028/1028 units. Code and
 data are 100% matched and linked. Global fuzzy remains the baseline 99.999886%.

Only the assigned module, iplJpegDecoder.cpp and this attempt log change.
Source and headers are committed individually. No push, PR, merge, rebase,
other-worktree edit or additional worker was performed.

## File commits

- `2acd985a5f519bb4a46c17c52ad5e178ef1636de` libs/RVLMiddleware/TMC_JPEG/include/tmc_jpeg.h
- `231bb21a6222e9bf3f9f72612ddb8876a3c042c7` libs/RVLMiddleware/TMC_JPEG/include/tmc_jpeg_internal.h
- `b95931e8832be19643fd31767002e3a4a0a2b6ee` libs/RVLMiddleware/TMC_JPEG/src/api/decapi.c
- `3e1a71167877e712e61774499f39f2c956d9cd60` libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse.c
- `ca977fc465a1d2da1467fad855bd258c663f5c4a` libs/RVLMiddleware/TMC_JPEG/src/jpegdec/jdec_main.c
- `85ceb54b664d67d6c719734ee3705639f794e4ed` libs/RVLMiddleware/TMC_JPEG/src/texturecvtr/Texture_MCUtoY8U8V8.c
- `952e9e148ad7a54645333d52704c56ce60f7f7d4` src/utility/iplJpegDecoder.cpp
