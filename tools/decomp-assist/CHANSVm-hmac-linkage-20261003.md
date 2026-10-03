# CHANSVm HMAC external declarations

Base: `20ba34a80f9d0a09c4a8fad51352f0dd97d84be0` (43U).
Leaf: `agent/bittle/chans-hmac-linkage`.

## Source evidence

The four HMAC/SHA1 helper declarations at the top of `CHANSVm.c` had
`static` linkage but no definitions in that translation unit. A fresh MWCC
compile emitted four warning 10532 diagnostics. The definitions in
`libs/RevoEX/src/net/sha1.c` and `hmac.c` have external linkage;
`CDBRecord.c` already declares these imports `extern`.

The original CHANS object imports all four as `STB_GLOBAL`, `SHN_UNDEF`.
The baseline source object instead imported them as `STB_LOCAL`,
`SHN_UNDEF`. Change only the four declaration storage classes to `extern`.
Do not change the context, parameter types, shared headers, or linking flags.

Independent original-DOL call decoding agrees with the extracted relocations:

| Caller | Call address | Destination | Import |
| --- | --- | --- | --- |
| VmBlobCalcHMAC | 0x81452720 | 0x81494144 | NETGetSHA1Interface |
| VmBlobCalcHMAC | 0x81452734 | 0x814944EC | NETHMACInit |
| VmBlobCalcHMAC | 0x81452744 | 0x81494728 | NETHMACUpdate |
| VmBlobCalcHMAC | 0x81452750 | 0x81494738 | NETHMACGetDigest |
| VmBlobCalcRangeHMAC | 0x814528F4 | 0x81494144 | NETGetSHA1Interface |
| VmBlobCalcRangeHMAC | 0x81452908 | 0x814944EC | NETHMACInit |
| VmBlobCalcRangeHMAC | 0x81452918 | 0x81494728 | NETHMACUpdate |
| VmBlobCalcRangeHMAC | 0x81452924 | 0x81494738 | NETHMACGetDigest |

The ABI contracts agree: Init takes context/interface/key/u32 length in
r3-r6, Update takes context/data/u32 length, and GetDigest takes
context/output. The interface helper returns its pointer in r3.
Original caller context addresses are sp+8 and sp+0x10. The exact HMAC
implementation uses the interface at 0x00-0x1B, key length at 0x1C,
96-byte digest state at 0x20, and 64-byte key at 0x80, totaling 0xC0.
The existing CHANS opaque context reserves 0xD0 with 8-byte alignment.
That storage is unchanged. Caller opaque types and callee named types
remain separate declarations; this change fixes linkage only, not complete
cross-translation-unit type compatibility.

## Validation

- Configured 43U with `../toolchain/wibo-build/wibo`; fresh baseline full
  source/report/DOL build passed, followed by a forced owned-object rebuild.
- Baseline emitted exactly four warning 10532 diagnostics; candidate emitted
  none. No other compiler warning appeared in the candidate object build.
- The four imports now have exactly the original symbol records, including
  global undefined binding. Every other symbol record is unchanged.
- All six allocated sections retain identical contents, extents, alignment,
  type and flags, including the NOBITS section's extent.
- All 2,010 relocation sites, types, symbol identities and addends are
  unchanged. Comparison resolves symbol indexes because binding changes
  can reorder the ELF symbol table.
- All 1,027 unit report records are unchanged. CHANS: fuzzy 99.4341%,
  exact code 38,136/53,564 bytes, exact functions 222/233,
  matched data 6,904/6,904 bytes.
- Independently compared all 222 exact functions against original
  instruction streams, with zero differences.
- The two HMAC callers remain 64/64 and 119/119 instructions, diffs 0.
- Pool: identical 125/125 entries. Literal advisory: 233 functions,
  40 arguments, no candidates, errors, or skips.
- Eight call destinations and 392 nonrelocated instruction words across
  the two callers and four helpers agree with original DOL bytes.
- Final `WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja all_source
  build/43U/report.json build/43U/ok` passes; DOL SHA1 remains
  `26116613f624061ba99c8d1a299aaa6efa85670d`. `git diff --check` passes.

Whole-object identity is intentionally not claimed: symbol bindings changed.
SHA256 before:
`f971cabf817dba7e5cb240df01e1e8f814bb0a973e357a594d031046a56e691b`.
SHA256 after:
`5bf3f4a0a404e2a574287c16de81d702a1402d9fca416455e84dc1df67c9eb76`.

Private reproducibility artifacts are under
`validation/chans-hmac-linkage-20261003/` in the workspace parent and
`/tmp/chans-hmac-linkage/`. No original binary or disassembly is committed.
This is a source declaration correction with no decompilation percentage gain.
