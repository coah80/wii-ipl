# ODH source-integrity checks

Base: 3d7e767cf729de96ac1cd88ddbf5c18eaa08187d (43U only).

- Restored unsigned arithmetic in all three huffmanDecoder word refills by
  casting the shifted bytes to u32. The combined word and its bitOffset shift
  now remain unsigned, including input words with the high bit set.
- Restored unsigned planeSize indexing in LineConv11. Chroma source pointers
  are only formed by accesses in the planar-format branch. The RGB565 caller
  passes a row-offset pointer into Capture's GXGetTexBufferSize allocation;
  for tile-aligned dimensions that allocation is exactly width*height*2 bytes.
  Unconditionally adding two planes to a nonzero row pointer could therefore
  form an out-of-bounds pointer even though RGB565 never dereferences it.
- Reviewed the full huffmanDecoder rewrite against its preceding source.
  Other category shifts and caller/table preconditions were already present;
  no additional newly introduced arithmetic issue was identified in this pass.

One candidate, no compiler flags or other source changes. No debugger, compiler
memory access, forced registers, assembly, uninitialized values, or online source
references were used. Retail objects and disassembly remained local.

Validation:

- All allocated source-object sections, function spans, and resolved relocations
  are identical to the unmodified base object (debug metadata differs).
- All 28 retail function spans are raw-byte exact: 14,684 bytes, with all 203
  relocations identical after resolving local symbols to actual section offsets
  and code symbols to function-relative targets.
- Data matches: .rodata 5,856, .data 464, .sdata2 40 bytes. The source .data is
  459 bytes plus five zero alignment bytes in the split/link target.
- Pool identical, 10/10 strings. huffmanDecoder ctxdiff: 306/306, zero diffs.
  LineConv11: 146/146; the strict-name local helper prints eight pre-existing
  label-name differences. Exact bytes, resolved relocation destinations, and
  referenced data independently match; none were ignored without resolution.
- Official objdiff: ODH 28/28 functions; code, data, fuzzy and link all 100%.
- Every measure, function and section in all 1,028 report units, plus all global
  measures, is unchanged from the base report.
- Full 43U build and build/43U/ok pass. DOL SHA1:
  26116613f624061ba99c8d1a299aaa6efa85670d.
- All 22 workflow-guard tests pass. A host UBSan refill test passes 524,288
  cases against a 64-bit oracle (every high byte, offsets 0..7).
- The global completion checker still fails on pre-existing incomplete units;
  this change does not claim repository-wide completion.

Local reproducible evidence: ../odh-unsigned-refills-evidence/verify.py,
verification.log, full-build.log, pool.log, guards.log, refill-test.cpp/log,
completion.log, status.json and dol.sha1. No publication or merge performed.
