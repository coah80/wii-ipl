# ODH Huffman node-type reconstruction, 2026-10-03 UTC

Base `a894ff5c`, branch `agent/bittle/odh-huffman-node-types`, 43U only.
Changed only the two tree declarations/initializers and their local pointer
record in `src/system/odh.cpp`, plus this log. No headers, public signatures,
metadata, linking flags, forced alignment or padding changed.

## Evidence and source correction

The decoder reads its tree entries and leaf categories with zero-extending
16-bit loads. Edges use the low 14 bits as relative halfword indices, while the
top two bits indicate terminal left/right branches. Leaves hold categories0..11.
The earlier source represented each pair of entries as one packed const u32 and
then accessed it through u16 pointers. HufftreeData likewise described the trees
as const u32 pointers, although every decoder use expects halfword entries.

Both tables are now explicit const u16 arrays, each with 24 actual entries.
HufftreeData::tables holds const u16 pointers. This removes the mismatched u32
object/u16 access representation, rather than changing the Huffman algorithm.
Every original word was split into its high and low halfwords in the target's
big-endian order; no value, tree edge or byte was added, removed or reordered.

The decoder's existing u16** parameter, its exact mangled public symbol, the C
ODH entry points and every caller are unchanged. The existing caller casts retain
the established ABI; no decoder writes a tree entry. Component0 uses the luma
value tree, components1/2 the chroma value tree, and all use the existing luma
prefix tree for zero-run categories. Request initialization starts at byte16,
bit offset0; successful decoding commits normalized offsets0..7.

## Read-only decoder audit

Prior sol-low, sol-high and fz10 attempts were reviewed. The existing decoder is
306/306 instructions with register allocation differences. Four-byte lookahead,
big-endian word assembly, unsigned bit-buffer operations, predictor selection,
DC/AC sign reconstruction, zero-run writes, EOB, success-only cursor/bit-count
commit, and error-path partial coefficient/predictor writes agree with target.
No additional algorithmic or stream-boundary behavior was invented.

Malformed overlong zero runs can exceed a nominal64-coefficient block in both
the source and original target; changing that behavior is outside this focused
type correction. Arbitrary table contents or invalid request states are likewise
not claimed to have acquired validation.

## Verification

- Each tree remains exactly48 bytes. Fresh source bytes, old packed-u32 bytes,
  and original split-object payloads agree byte-for-byte.
- Exhaustive tree-path validation: all512 nine-bit luma prefixes and all2048
  eleven-bit chroma prefixes agree with independent canonical Huffman codes,
  including each valid leaf and the depth-limit invalid path.
- Fresh baseline/candidate builds: all28 reported function instruction streams
  are unchanged. Entire .text14964, .data459, .rodata5856 and .sdata2 40 bytes
  are identical, with the same section alignments. Defined function/object
  symbol names, bindings, types and sizes are unchanged.
- Decoder remains95.57189%,306/306; unit remains99.55462%; exact26/28 and code
  12876/14684; data6360/6360 (100%) and linking unchanged. No matching gain claimed.
- Pool: all10 strings identical to target.
- Literal audit:14 arguments across28 functions, no candidates, skips or errors.
- Full1027-unit report: zero exact-function/code/data/fuzzy regressions.
- Full43U build and build/43U/ok passed. DOL SHA1:
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

A host harness compiles the actual production decoder body and the new u16 table
initializers with fixed-width types and strict aliasing enabled. It passes24000
cases against an independent canonical-code bit reader:6657 successes and17343
truncation/malformed-code failures. Coverage includes components0/1/2, starting
bit offsets0..7, positive/negative DC and AC values, zero runs, EOB, full blocks,
4-byte-lookahead boundaries, invalid tree codes and run signs, output canaries,
predictors and request-state commit. Malformed overlong zero runs are excluded;
whole-image/Wii runtime execution is not claimed.

Private evidence: `/tmp/odh-node-types/` contains baseline/final reports and
source objects, tree-proof.log, pool/literal audits, full-build.log,
validate_decoder.py and decoder-tests.log. The earlier read-only decoder audit
is in `/tmp/odh-decoder-audit/`. No retail assembly or binary is committed or
uploaded.

GATE: real halfword node types reconstructed, ABI and all compiled bytes/metrics
preserved, tree and decoder behavior verified. Frozen for parent validation.
