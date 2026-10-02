# AES round-expression reconstruction, 2026-10-02

Separate follow-on to AES key-cursor candidate `2a537c14`. Frozen MD5 candidate
`8a6461f9` and prior logs are untouched. This commit changes five expression
lines in `libs/RevoEX/src/net/aes.c`, plus this log. 43U only; no linking changes.

## Evidence and reconstruction

Target evidence remains the original split `aes.o`, AESiEncryptBlock and
AESiDecryptBlock. Both round bodies use four cyclic T-table columns: rotations
of 24, 16 and 8 bits plus the unrotated low-byte column. Their XOR dependencies
and the inverse-key transform's successive rotate/XOR dependencies lower in a
different order from the previous source. The retained expressions associate
these same unsigned contributions so compiler scheduling moves closer to the
target. Byte indices, rotation counts, table identity, key traversal, row order,
loop conditions and final substitution are unchanged.

The inverse-key transform still computes doubled/four-times/eight-times byte
values in the same GF(2^8) representation. Each subsequent stage combines its
old mixed value, its 8-bit rotation and the same added contribution. Explicit
XOR assignment replaces the compound assignment; all RHS values are evaluated
before the assignment, with no side effects or undefined evaluation order.

No source body or algorithm was missing. This is further instruction-shape
reconstruction, not a new functional path or an exact-match claim.

## Attempts

- Eight staged column/round helpers and six explicit table-load stages did not
  improve both functions; reverted.
- Tested 120 associative/permutation forms of four T-table contributions,
  retaining the independent improving expression for each cipher direction.
- Tested twelve uniform inverse-key XOR forms plus per-stage refinements. The
  retained rotate-first XOR form improves all three stages without new helpers.
- Array/struct state views, a 15-by-4 round-key view, initial-key cursor forms,
  and typed table helpers were evaluated. Small gains that required larger
  changes were rejected, along with all regressions.
- No register declaration sweep, inline assembly, volatile qualifier, padding,
  undefined input, compiler-option change or table change was used.

## Verification

Before -> after:
- AESiEncryptBlock fuzzy 60.348103 -> 62.58228%; 158/158 instructions unchanged;
  final ctxdiff has 133 positional differences.
- AESiDecryptBlock fuzzy 63.836655 -> 67.64143%; 251/251 instructions unchanged;
  final ctxdiff has 224 positional differences.
- Unit fuzzy 77.700584 -> 79.601746%.
- Exact functions 7/9, exact code 1116/2752 bytes, data 2800/2800 (100%), and
  linked status are unchanged. All seven exact functions retain ctxdiff diffs 0.
- All four pool strings match. Table and data source is unchanged.
- Frozen MD5 source/metrics are unchanged: unit96.179825%, ProcessBlock94.30719%.
- The full 1027-unit report has zero exact-function/code/data/fuzzy regressions
  against the immediately preceding frozen MD5/AES source report.
- Full 43U build and build/43U/ok passed. DOL SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`.

`python3 /tmp/crypto-remainder/validate_aes.py` passed all 2,406 production-source
known-answer/randomized AES-128/192/256 CBC checks, including in-place buffers
and incremental calls. The frozen AES parent source independently passed the
same coverage in the same run. Input/key/IV words carry their PPC big-endian
numeric values in the native host harness; production source is unmodified.

Local evidence, not committed or uploaded: `/tmp/crypto-remainder/` contains
`aes.xor-results.json`, `aes.invmix-results.json`, `aes-rounds-final.json`,
`aes-rounds-AESiEncryptBlock.ctx`, `aes-rounds-AESiDecryptBlock.ctx`,
`aes-rounds-vectors.log`, `aes-rounds-full-build.log`, and `validate_aes.py`.
No original retail assembly or binary is included in this commit.

GATE: validated partial arithmetic/data-flow candidate; no regressions. Exact
matching and linking remain open.
