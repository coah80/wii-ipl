# MD5 unsigned arithmetic and cursor reconstruction, 2026-10-02

Separate follow-on to accepted MD5 commit `521056a9`. AES commit `2a537c14`
and both prior logs are unchanged. Only 43U was configured or built.

## Target-grounded changes

The target ProcessBlock rotation halves retain independently grouped additions
of the unsigned state, round constant and separately byte-reversed message
words. Reassociating those three u32 operands inside the accepted helper brings
the compiler's data-flow closer to the target while preserving modulo-2^32
arithmetic. The first MD5 round consumes sequential message words; expressing
that consumption with `word++` as the helper's pointer argument improves its
schedule. STEP evaluates this pointer argument exactly once; the helper still
uses that captured pointer for both byte-reversed reads. No evaluation-order
ambiguity, extra read, undefined value, or new helper is introduced.

Experiments enumerated 144 valid addition operand/grouping combinations for
the two halves. The best target-sized arithmetic expression reached 93.447716%
ProcessBlock fuzzy. Five cursor/loop variants and eight independent cursor-
consumption combinations then identified the minimal `word++` form, reaching
94.30719%. A larger by-reference cursor helper reached 94.98366% but duplicated
rotation code for a small gain and was rejected. Three explicit feed-forward
variants did not improve the retained result. No declaration/register sweep,
assembly, volatile qualifier, padding or linking change was used.

## Verification

Accepted MD5 -> this candidate:
- ProcessBlock: 81.82026 -> 94.30719% fuzzy; 306/306 instructions unchanged.
- Unit fuzzy: 87.80044 -> 96.179825%.
- Exact functions 3/4 and exact code 600/1824 are unchanged.
- Data 456/456 (100%) and linking status are unchanged.
- NETMD5Init 16/16, NETMD5Update 60/60 and NETMD5GetDigest 74/74 still have
  ctxdiff diffs 0 and objdiff 100%.
- ProcessBlock has 215 positional differences. An advisory comparison that
  ignores GPR names leaves five opcode/immediate-order differences: three
  sequential cursor offsets and two final state-load positions. This is not
  an exact match or a proof that every remaining difference is register-only.
- Empty string pools remain identical. Constants/index tables and end-marker
  data are unchanged from the accepted candidate.
- AES metrics and source are unchanged from commit 2a537c14.
- Full 1027-unit report: zero exact-function/code/data/fuzzy regressions versus
  baseline449529d9; additionally both owned units preserve the immediately
  preceding candidate's exact/data scores and improve or preserve fuzzy scores.
- Full 43U build and build/43U/ok passed. DOL SHA1:
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

All 3,088 MD5 known-answer/random/chunking comparisons passed again against
Python hashlib. Run `python3 /tmp/crypto-remainder/validate_md5.py`. The test
compiles production C unchanged with PPC intrinsic shims, supplies RFC1321
padding externally, and exercises ProcessBlock through NETMD5Update. The
instruction-exact GetDigest platform-endian stores are not host-tested.

Local evidence (not committed/uploaded): `/tmp/crypto-remainder/` contains
`md5.grouping-results.json`, `md5-grouping-final.json`,
`md5-grouping-ProcessBlock.ctx`, `md5-grouping-vectors.log`, and
`md5-grouping-full-build.log`. Original target evidence remains in the local
split object and disassembly; no retail assembly is included in this commit.

GATE: validated partial structural candidate; no regressions. Exact matching
and linking remain open.
