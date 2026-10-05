# Thumbnail input parameter recovery

Base: `f7cc4a45a5b5dd0cc057d9b017bc8cc026eef002` (PR1179).
Branch: `agent/fix/thumbnail-parameter-view`.

One bounded source candidate removes the local `TMCJpegInputBuffer` overlay
from `TMCJPEGDEC_init_buff_thumbnail` and reads the existing
`TMCCJPEGDecInitParam` object through its declared fields. The only added
include is the existing `<stddef.h>` for `offsetof`. No header definitions,
layouts, signatures, compiler flags, matching classifications, or callers
change. No tuning or second candidate was attempted.

## Object, bounds, and lifetime evidence

The sole call is in `TMCCJPEGDecGetInfoEXIF`, in
`libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse.c`. Its third argument is
`(u8*)pParam + 0x10`, formed from the whole, live `TMCCJPEGDecInitParam`
object. That type begins with `u8 unk_0x00[0x10]`, followed by `pBuf2` at
offset 0x10. Recovering the original address with
`src - offsetof(TMCCJPEGDecInitParam, pBuf2)` stays within that object's
byte representation and restores its original alignment. It does not create
an object or reinterpret an unrelated allocation as a new structure.

The declared fields are `pBuf2`, `buf2Size`, `dataSize`, `pCallback`, and
`pContext`. Reading `pBuf2` as its declared `void*`, then assigning it to the
existing `u8* start`, uses the ordinary C pointer conversion. The old local
overlay instead read that storage as a member of an unrelated structure with
a `u8*` first member. All field accesses now use the actual parent type.
No pointer to the parameter object is retained after this function returns.

The caller supplies the real work buffer as `dst` and the real EXIF object
as the first argument, which the callee casts back to its actual type.
The caller zeroes the work and EXIF state before parsing and invokes
`TMCJPEGDEC_ThumbnailCheck` before reaching this function. The existing
initialization, source-load/destination-store order, zero-size early exits,
and final `remaining = 0` are unchanged. No loop or uninitialized local is
introduced, and both sibling functions are untouched.

End-address arithmetic is unchanged. Its additions and mark subtraction
operate in unsigned 32-bit arithmetic before target-specific integer/pointer
conversions. The existing unsigned-to-signed conversions and address
representation depend on the Wii/MWCC implementation. This is a
binary-neutral object-access correction, not a portability or malformed-EXIF
hardening claim.

## Fresh isolated verification

Configured 43U with explicit existing local tool paths and rebuilt the
unmodified baseline in this leaf before editing. Preserved the report,
object, DOL, all 1027 source-object hashes, build log, raw ELF section/function
bytes, and explicit relocation records. Then compiled the single candidate
and reran the full 43U build, report, progress, and `build/43U/ok`.

- The complete source object is byte-identical to the fresh baseline:
  SHA256 `bbc460eb1312d2be239e5ffbad750f2f36cd5ed1fc8b68aa7e5ea052418eeb73`.
- All 316 allocated `.text` bytes equal the original object, with identical
  section size, alignment, and flags. There are no allocated data sections.
- The three functions remain exact-name objdiff 100% and raw-byte identical:
  `init_buff_thumbnail` 136 bytes / 34 instructions, `init_buff` 16 / 4,
  `rewind_ptr` 164 / 41. Strict local ctxdiff reports zero differences for all.
- Explicit relocation records agree in source section, offset, type, addend,
  symbol name, binding/type, target section/value, and size. All are REL24
  with addend zero: 0x94 to `TMCJPEGDEC_load_buff`, and 0xCC/0xF0 to
  `TMCJPEGDEC_move_ptr`. All three targets are the same undefined global
  symbols in both objects; the unchanged linked DOL independently checks
  their resolved call destinations.
- Printable pools are empty on both sides. The absence of all allocated
  data sections establishes that there is no omitted data/pool comparison.
- Every source-object SHA256 is unchanged, all 1027 report unit entries
  and global measures are identical, and the unit retains 3/3 functions,
  316/316 matched bytes, and 316/316 linked bytes.
- Full build and DOL verification pass. DOL bytes equal both the fresh
  baseline and original, SHA1
  `26116613f624061ba99c8d1a299aaa6efa85670d`.
- `git diff --check` and the leaf worktree check pass. Source review finds
  no added assembly, dummy storage, volatile casts, register hints,
  uninitialized state, or unrelated source edits.
- The project-wide completion checker still reports the existing incomplete
  project. This candidate makes no project-completion claim; its complete
  report is unchanged from the baseline.

Local evidence is under `build/thumbnail-view-audit/`: baseline/candidate
reports, objects, DOLs, all-object hashes, build logs, pool/ctxdiff output,
raw ELF and relocation JSON, the read-only `verify_getcode.py` comparison,
status/completion output, and `validation.json`.

GATE PASS: actual-parent-object access; 3/3 functions and all code/data/link
measures exact; all source objects, full report, and full-build/DOL unchanged.
