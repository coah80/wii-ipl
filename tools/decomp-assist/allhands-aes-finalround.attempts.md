# AES final-round word reconstruction, 2026-10-02

Base: `813660b9` plus local cherry-pick `97035641` of the parent's already queued
`fce31442`. The imported candidate and its log are unchanged. This follow-on
changes only two final-round expression lines in `libs/RevoEX/src/net/aes.c`
and this new log. 43U only; no configuration, metadata, headers or linking edits.

## Retained reconstruction

The last cipher round substitutes four bytes, places them in distinct unsigned
word lanes, and combines them before AddRoundKey. Encryption combines the high
and low lanes, combines the two middle lanes, then ORs those pieces. Decryption
combines high/low first, then the lower-middle and upper-middle lanes by XOR.
These expressions preserve byte indices, shifts, S-box identity, key traversal,
output order and all input/state reads. The four lane contributions are disjoint;
all operands are unsigned and have no side effects. No value, algorithmic path,
or table is newly invented. This is arithmetic-dependency reconstruction rather
than a new implementation or an exact-match claim.

The target evidence is the original split object's final substitution and
packing regions in `AESiEncryptBlock` and `AESiDecryptBlock`. Those regions
contain the same sixteen byte loads and word-lane insertion/XOR operations.
The retained grouping improves the whole-function instruction similarity at
the target's existing body sizes. It does not reproduce every target dependency
or register assignment: exact matching remains open, and positional ctxdiff
counts are slightly worse despite the improved aligned objdiff scores.

## Explored alternatives

- MD5 third-round Boolean grouping and four typed step helpers were tested.
  The best small Boolean change only reached 94.37255% from 94.30719%; a larger
  helper reached 94.43791%. Both were discarded as too little benefit for the
  added change. MD5 source is byte-for-byte unchanged.
- Typed inverse-key word, round and complete-schedule helper scopes were tested.
  A round helper reached 69.72908% decrypt similarity, but interacted poorly
  with the better final-round grouping. No helper is retained.
- Fusing AddRoundKey into each intermediate column regressed both directions.
- Typed final-substitution helpers, packed-byte intermediates, and explicit
  T-table column helpers were evaluated. Their source complexity was unnecessary
  or they scored below the two retained macro changes.
- Twelve unsigned lane-combination expressions were checked for each final-round
  macro. Two independently improving forms are retained. No register/declaration
  sweep, assembly, volatile qualifier, undefined value, padding or compiler-option
  change was used.

## Verification

Before -> after:
- AESiEncryptBlock: 62.58228 -> 65.81013% fuzzy; 158/158 instructions unchanged;
  final ctxdiff 137 positional differences (baseline 133).
- AESiDecryptBlock: 67.64143 -> 69.69323% fuzzy; 251/251 instructions unchanged;
  final ctxdiff 227 positional differences (baseline 224).
- AES unit: 79.601746 -> 81.09157% fuzzy; exact functions 7/9 and exact code
  1116/2752 bytes unchanged. Data 2800/2800 (100%) and linking unchanged.
- All seven exact AES APIs/CBC functions retain objdiff 100% and ctxdiff diffs 0:
  NETAESCreateEx 108/108, NETAESCreate 2/2, NETAESDelete 1/1, NETAESEncrypt 46/46,
  NETAESDecrypt 46/46, NETiAESEncryptoBlock 39/39, NETiAESDecryptoBlock 37/37.
- AES pool: all four strings identical. .rodata 2592 bytes and .sdata2 8 bytes
  identical. .data has the same 197-byte prefix of the 200-byte target, retaining
  the existing three-byte target alignment extent; no padding was introduced.
- MD5 remains unit 96.179825%, ProcessBlock 94.30719% (306/306 instructions),
  exact functions 3/4, exact code 600/1824, data 456/456. Its three exact APIs
  retain ctxdiff diffs 0. All 448 .data bytes are identical; .sdata retains its
  existing one-byte source/seven-byte target-alignment extent difference.
- Full 1027-unit report: no exact-function, exact-code, data or fuzzy regression
  versus the locally imported parent candidate.
- Full 43U build and build/43U/ok passed. DOL SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

Host tests compile production source unchanged with private copies of the existing
PPC type/intrinsic shims. Both final AES and the imported parent baseline passed
all 2,406 AES-128/192/256 known-answer and seeded randomized CBC checks, including
separate/in-place buffers and single/incremental calls. Unchanged MD5 passed all
3,088 known-answer/random/chunking checks. The MD5 test supplies RFC1321 padding
externally; GetDigest's target-endian length stores remain outside host coverage.

Private local evidence: `/tmp/crypto-reconstruction-next/` contains baseline/final
reports, pool/section/ctxdiff results, full-build.log, host validation scripts and
results, and the rejected experiments. No retail assembly or binary is committed
or uploaded. Prior worker logs under `/tmp/crypto-remainder/` are untouched.

GATE: validated partial arithmetic reconstruction with no report regressions.
Exact matching and linking remain open. Candidate frozen for parent validation.
