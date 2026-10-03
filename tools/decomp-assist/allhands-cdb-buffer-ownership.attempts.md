# CDB crypt-buffer ownership contract

Base: 20ba34a8, 43U. Focused source correction after the read-only CDBRecordEncrypt audit found only register-allocation differences in that function.

## Evidence and change

CDBRecord.c already declares CDBCryptBufAllocate and CDBCryptBufFree with CDBCryptBuf** parameters. Its callers supply the address of the record's crypt-buffer pointer slot. CDBCrypt.c instead declared CDBCryptBuf* and accessed buffer32[0] as a u32-encoded pointer, producing incompatible cross-translation-unit function types and describing the caller's pointer slot as an entire crypt-buffer object.

Both definitions now take CDBCryptBuf** and use direct typed pointer loads/stores. Allocation assigns the pool pointer; free compares the owned pointer and clears the slot to NULL. The existing pool-index expression, flag update order, diagnostics and failure behavior are retained. The obsolete placeholder comment is removed. No header, payload layout, pool extent, Encrypt implementation, or linking change.

## Validation

- Configure: `python3 configure.py --version 43U --wrapper ../toolchain/wibo-build/wibo`
- Build: `WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja`
- Entire compiled CDBCrypt.o is byte-identical to the baseline, including all code/data, symbols and relocations
- CDBCryptBufAllocate: 36/36 instructions, ctxdiff zero
- CDBCryptBufFree: 33/33 instructions, ctxdiff zero
- Unit remains 100% fuzzy, 3/3 exact functions, 296/296 code bytes and 80/80 data bytes
- Full-project before/after objdiff reports are identical; no metric gain is claimed
- Pool identical: 2/2 strings; literal-reference audit: 2 arguments across all 3 functions, no candidates/errors/skips
- Host test compiles the production source with the actual CDBCryptBuf layout and minimal platform/error stubs. AddressSanitizer and UBSan pass 50,036 ownership transitions, including every combination of six representative allocation flags and null/owned/foreign pointer slots, 10,000 randomized state cases, and 10,000 allocate/reallocate/free/refree cycles. Checks cover pointer-slot canaries, complete payload preservation, allocation flag, return value and diagnostic count
- LeakSanitizer is disabled because it cannot run under this execution environment's ptrace; the harness makes no heap allocations. Address and undefined-behavior instrumentation remain enabled
- Full 43U build and build/43U/ok pass; DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d
- git diff --check passes

Private reproducible evidence is in /tmp/cdb-buffer-ownership (baseline object, full reports, host validator and build log). Original objects/disassembly from the preceding read-only audit remain private under /tmp/cdb-record-encrypt-audit.
