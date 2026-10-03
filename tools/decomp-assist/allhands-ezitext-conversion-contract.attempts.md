# Conversion table-address contract, 2026-10-03

Base: 20ba34a8. Owned source: zconvert.c only. This candidate corrects a
cross-unit declaration; it has no percentage gain.

## Definition-backed correction

zaddress.c defines Zi8GetTableAddress as returning ziU32. It forwards the
ziU32 result of Zi8GetTableData, whose address case explicitly converts the
computed dictionary pointer to an integer address. Its target wrapper
forwards the full register result without a byte or halfword narrowing.

zconvert.c instead declared the same function as returning ziPtr. Correct
that local declaration to ziU32 and explicitly convert the returned address
at the three existing table-pointer assignments: ziU8* for UC2WC, and
ziConversionTable* for WC2UC and UC2Key. These are the only four source-line
changes. No callee, shared header, lookup representation or control flow is
changed.

## Read-only UC2Key investigation

The original remaining function is 207 instructions / 828 bytes, with 18
register-operand differences. Exchanging the two diagnostic work/key register
names makes every instruction, branch destination, memory operand, call and
relocation annotation identical. The mapping is only used by the audit and
is not expressed in source.

The existing packed representation agrees with target accesses:

- Serialized header count is a big-endian byte pair at offsets 0 and 1.
- Serialized entries have an eight-byte stride. First/last/value are byte
  pairs at offsets 0/2/6; the intervening flags pair is not read here.
- A ranged mapped-key result is another big-endian byte pair, reached via
  header + 8 + entry value + 2 * (character - first).
- The native fallback range instead uses halfword first/last fields at 0/2
  and a word pointer-or-character union at 4. A singleton explicitly keeps
  the low byte of the word; mapped keys use native halfword loads.
- The native default object is exactly 32 zero bytes, with no target data
  content or relocation supporting a different field layout.

The declared halfword result is also correct. The original reference scan
finds only three executable callers plus the function's exception-index
reference. PUD and UWD pass a byte character and narrow the return to a
halfword before comparing their halfword pattern. WC2Key forwards the result
without additional narrowing. The user-key helper definition likewise
returns a halfword, including the EFFx key range. GetTableCount's declaration
already agrees with its halfword-returning definition and target narrowing.

Prior fz2/fz21 attempts already cover const views, key widths, pointer/local
lifetimes, result initialization, expression grouping, and declaration order.
No new packed-width or control-flow defect was found. No allocation trial
was repeated.

## Verification

Fresh configure and baseline full build used 43U, the approved wibo wrapper,
and WIBO_SJIS_MISSING_IMPORTS=1. Pool checked first: identical and empty.
After the four-line correction, all 1,027 source objects are entirely
byte-identical to their baseline hashes, and the complete 1,027-unit report
is identical. The owned .text, .rodata, extab and extabindex payloads and
canonical relocations were additionally compared explicitly.

Unchanged unit: 99.83696% fuzzy, 3/4 exact functions, 1,380/2,208 exact code
bytes, and 112/112 exact data bytes. UC2Key remains 99.565216%.
All existing exact functions retain ctxdiff zero differences:
UC2WC 124 instructions; WC2UC 199; WC2Key 22.

Final full 43U build passes. DOL SHA1:
26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No assembly, artificial storage, volatile, metadata,
linking flags, shared-header edits, other-region builds or remote writes.

Private local verification artifacts:
- /tmp/ezi-conversion-baseline.json
- /tmp/ezi-conversion-final-report.json
- /tmp/ezi-conversion-final-build.log
- /tmp/ezi-conversion-verification.txt
- /tmp/ezi-conversion-caller-audit.txt
