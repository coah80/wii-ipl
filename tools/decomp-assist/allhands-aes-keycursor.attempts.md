# AES key-schedule cursor reconstruction, 2026-10-02

Source baseline: `449529d9`. This separate candidate follows the frozen MD5
commit `521056a9`; it changes only `libs/RevoEX/src/net/aes.c` and this log.
43U only. No linking flags, configuration, tables, or public API edits.

## Target evidence and retained change

`AESiDecryptBlock` in `build/43U/obj/libs/RevoEX/src/net/aes.o` is 0x3EC bytes /
251 instructions. Its entry first forms the key-schedule base at context+0x10
(function-relative offset 0x18), extracts the last-round offset from the flags
word (offset 0x24), and adds that offset to the already formed base (offset
0x28). The baseline combined initializer produced 249 instructions. Explicitly
initializing the typed key pointer to `context->keys` before advancing it by
`rounds*4` recovers the target's two-stage pointer construction and body size.
The retained change is two added source lines and one removed line. All AES
round expressions, lazy inverse key transformation, tables and CBC chaining
remain unchanged.

This is a structural matching improvement, not a newly implemented AES path.
Both existing block algorithms were already present and pass the behavior tests.

## Explored and rejected alternatives

- Inlined single-word round helpers, byte-typed table lookups and table-rotation
  helpers changed scheduling but regressed encryption or added source complexity.
- Staging four inverse-mix column outputs through a typed round helper improved
  decrypt similarity but required substantially more source and still did not
  match. Not retained.
- Alternate inverse-key-transform local lifetimes and an inverse-key helper
  gave only small extra fuzzy movement, without new algorithm reconstruction.
- Context-relative key indexing and row/word loop variants did not improve the
  minimal key-base candidate.
- Moving next-state locals outside the round loop did not change codegen.
- Reordering key-base declarations produced a negligible score change; the
  original natural declaration order was kept.
- Two exploratory C89-incompatible mixed-declaration variants failed to compile
  and were immediately discarded. No failed source is retained.

## Verification

Before -> after:
- AESiDecryptBlock: 249 -> 251 instructions against target 251;
  fuzzy 61.49004 -> 63.836655%. Final ctxdiff: 224 positional differences.
- AESiEncryptBlock: unchanged, 158/158 instructions and 60.348103% fuzzy.
- Unit fuzzy: 76.844475 -> 77.700584%.
- Exact functions: 7/9 -> 7/9. Exact code: 1116/2752 bytes unchanged.
- Data: objdiff 2800/2800, 100%, unchanged. Linked status unchanged.
- All seven exact functions have ctxdiff diffs 0: NETAESCreateEx 108/108,
  NETAESCreate 2/2, NETAESDelete 1/1, NETAESEncrypt 46/46, NETAESDecrypt 46/46,
  NETiAESEncryptoBlock 39/39, NETiAESDecryptoBlock 37/37.
- String pool: all four strings identical.
- .rodata: 2592 identical bytes; .sdata2: 8 identical bytes. Source .data is
  197 bytes with the same prefix as the 200-byte target section; three target
  alignment bytes are an existing extent difference. No padding was added.
- The full 1027-unit report has no regressions in exact functions/code/data or
  fuzzy score against the baseline report. Frozen MD5 metrics are unchanged.
- Full 43U build passed with the configured wibo wrapper; build/43U/ok passed.
  DOL SHA1: `26116613f624061ba99c8d1a299aaa6efa85670d`.

Host validation: `python3 /tmp/crypto-remainder/validate_aes.py` compiles the
production C unchanged with minimal types/OSReport shims. Input, key and IV
words are represented with their PPC big-endian numeric values, so native host
byte order does not change the algorithm. Known-answer tests cover AES-128,
AES-192 and AES-256; seeded randomized CBC tests compare against cryptography's
AES implementation for all three key sizes. Each tests separate/in-place
buffers and single/incremental calls.

Result: all 2,406 production-source known-answer/randomized checks passed. The
original baseline had independently passed the same coverage before changes.
A separate saved helper experiment also passed but is not part of this commit.

Local evidence, not committed or uploaded: `/tmp/crypto-remainder/aes-final.ctx`,
`aes-final.json`, `aes-full-build.log`, `aes-vectors.log`, `aes-decrypt.target`,
and `validate_aes.py` plus its header shims. No retail assembly is included.

GATE: validated partial structural candidate; no regressions. Exact matching
and linking remain open.
