# MD5 sequential word consumption, 2026-10-03

Base: `fc114afd`. Source scope: `libs/RevoEX/src/net/md5.c` only. This is a
validated partial reconstruction under the user's decompiled-first priority,
not an exact match or linking change. Prior accepted source and logs remain.

## Selected source form

The first sixteen MD5 steps consume the existing sixteen-word context block
sequentially. Each step reads the selected word twice with the byte-reversed
intrinsic, then advances its local cursor by one word. The original performs
those paired loads before each four-byte cursor increment. `rotateNextSum`
expresses that consumption through the actual cursor's address, and is used
only by the four first-round step sites. The cursor begins at `buffer32`, ends
one-past its sixteen words and never escapes. No additional state is stored.

The other three rounds select nonsequential words through the existing index
table and therefore retain the non-consuming `rotateSum` helper. Both helpers
use the same unsigned arithmetic and paired endian loads. The small duplicated
rotation expression supports these two different pointer contracts; duplication
is not itself a reason for the gain. There are no new helper families, XOR
regroupings, arbitrary ordering hints, volatile qualifiers or register forcing.

This exact source form was previously measured at 94.98366% in the grouping
work, but rejected because it duplicated the small rotation body for a partial
gain. Fresh review selected it under the current acceptance priority. Only this
archived form was compiled; no new variant sweep was performed.

## Pinned contracts and scoped instruction audit

Original ProcessBlock consumes only incoming r3. State occupies context bytes
0..15, the untouched u64 byte count 16..23, and the owned block 24..87.
The exact Update API copies each complete block there; exact GetDigest builds
its final block there. ProcessBlock has no calls, external buffer, callback or
count dependency. No missing input or width defect was found.

Both compiled streams have four CTR=4 loops and reduce to the same independent
64-step MD5 recurrence in a private symbolic PPC instruction model. Arbitrary
initial state words and arbitrary message words are retained symbolically;
normalization uses only unsigned addition/XOR identities, commutative Boolean
operations and the observed split-rotation identity. Both streams execute
1,107 instructions, 128 paired little-endian message loads, 64 constant loads
and 48 index loads. The selected addresses match all four MD5 word schedules.
All 64 constants and 48 indices match their standard formulas. The only object
writes are the four final state words, at offsets 0,4,8,12. This scoped model
is additional evidence, not a general compiler-equivalence proof.

## Fresh gates

- ProcessBlock: 94.30719 -> 94.98366% fuzzy, 306/306 instructions.
  Positional ctxdiff differences decrease 215 -> 212; it is still nonexact.
- Unit: 96.179825 -> 96.63377%; exact functions 3/4 and exact code 600/1824
  unchanged. Data remains 456/456 (100%), with no linking change.
- All three public APIs remain byte-identical to baseline and instruction-exact
  against original: Init 16/16, Update 60/60, GetDigest 74/74, diffs 0.
- All 448 .data bytes are unchanged and identical to original. The .sdata byte
  remains 0x80; the existing source size 1 / target size 8 alignment difference
  is unchanged. No padding or section changes were introduced.
- Empty pools identical. Literal-reference audit analyzes all four functions,
  with zero candidates/errors and no string arguments to check.
- Full 1,027-unit before/after report: only MD5 changes; no exact function,
  exact code, data or fuzzy regression. Post-build final report equals the
  candidate report.
- 3,088 production-C digest/chunking comparisons against hashlib pass, including
  standard vectors, one million `a` bytes, 1,500 seeded messages and block/final
  padding boundaries. Padding is supplied externally; host testing does not
  exercise GetDigest's PPC-endian length stores.
- 20,000 direct production ProcessBlock checks against an independent scalar
  compression recurrence pass with ASan/UBSan. Arbitrary initial states and
  blocks cover unsigned overflow; count, input block and surrounding canaries
  stay unchanged. Leak detection is disabled because it is unsupported under
  this environment's ptrace; address and undefined-behavior checks are enabled.
- Full 43U build and build/43U/ok pass. DOL SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

Private evidence: `/tmp/md5-cursor-revalidation/` contains the reports, source
snapshots, instruction audit, host tests, sanitizer output, pool/literal/ctxdiff
results and build logs. Read-only preselection audit is preserved separately in
`/tmp/md5-processblock-audit/`. No original assembly or binary is committed.

GATE: passing partial instruction-structure gain, frozen for independent review;
exact matching and linking remain open.
