# BS2 low-level DVD completion callback contract

Base: `9c7d87ab008df7e35558321e3ca297a887d35c44`.
Leaf: `agent/bittle/bs2-dvd-callback-contract`, 43U only.

## Source evidence

`DVDLowCallback` is `void (*)(u32 intType)`. BS2Mach defined its completion
callback with a signed s32 parameter and cast it to the unsigned function
pointer type at five registration sites. DVDLowContext stores DVDLowCallback,
and the original exact doTransactionCallback dispatches through that type.
The callback simply publishes the received word to volatile u32 LowReadResult.
Use the unsigned parameter directly and remove the five casts.

The original callback symbol at 0x8137BA1C is local, while baseline source
emitted it globally. All references are private to BS2Mach.c. Restore static
linkage in a separate measured follow-on; no other function/global changes.

Original evidence was checked independently against the DOL:

- Five registration sites contain ten address-materialization relocations
  resolving to callback 0x8137BA1C
- The callback stores the entire r3 word to LowReadResult 0x81698A54, then
  returns; the actual SDA base is 0x8169E040
- Original dispatcher invocation is at 0x8154F8C8; doTransactionCallback
  remains instruction-exact, 46/46 instructions
- All 123 direct calls in BS2StartGame and BS2StartGCGame agree with original
  raw destinations; their request-buffer widths/offsets and ABI inputs agree
- Ordinary NAND completion has its separate signed-result/block contract
  and is untouched

## Separately measured trials

1. Unsigned callback parameter and removal of five casts only. Entire MWCC
   object byte-identical to baseline, SHA256
   `b853f8e58ead247dd8d333f4a7413e56b9c9e92341ad1bf54034fdf2f2be93b6`.
   Full report byte-identical across 1,027 units.
2. Add static linkage. Only callback's symbol binding changes, global to
   local, matching the original. Every other symbol record and all 1,461
   relocation sites/types/target identities/addends remain unchanged.
   All five allocated sections retain identical contents, extents, flags
   and alignment, including BSS/SBSS extents. Final object SHA256
   `154cd050a7295a1178de648a2abacf311cc2b4c96548926eb6d77eedb177c2e4`.
   Full report again byte-identical to baseline.

Whole-object identity is claimed only for trial 1; trial 2 changes metadata.
No matching/fuzzy percentage gain or change in boot behavior is claimed.

## Tests and gates

- Fresh baseline configured with `python3 configure.py --version 43U
  --wrapper ../toolchain/wibo-build/wibo`; full source/report/DOL build passes
- Candidate object built separately for both trials; final full invocation
  `WIBO_SJIS_MISSING_IMPORTS=1 ../.venv/bin/ninja all_source
  build/43U/report.json build/43U/ok` passes
- Pool identical: 91/91 strings
- All 25 exact functions independently retain zero instruction differences;
  callback remains 2/2 instructions at .text+0xA68, STB_LOCAL as original
- Unit unchanged: 25/29 exact functions, 5,112/16,980 matched code bytes,
  155,504/158,528 matched data bytes, fuzzy 99.09658%
- Literal advisory: 28 functions, 97 arguments, no candidates or errors;
  skips only BS2Tick because its extents differ
- DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`
- `git diff --check` passes

Host compiler test extracts the baseline and final callback definitions with
fixed-width host equivalents. Direct assignment to DVDLowCallback fails for
the signed baseline under -Werror=incompatible-pointer-types and succeeds for
the final definition. The final callback preserves 200,007 tested words under
UBSan, including 0, 1, 2, 0x40, INT32_MAX, 0x80000000 and UINT32_MAX.
This is a compile-time function-type counterexample; GCC UBSan is not claimed
to detect the baseline's incompatible indirect call.

Private evidence: `/tmp/bs2-boot-contract/` and workspace-parent
`validation/bs2-boot-contract-20261003/`. Original binary/disassembly is not
committed. No shared header, volatility, Run body, state, or linking change.
