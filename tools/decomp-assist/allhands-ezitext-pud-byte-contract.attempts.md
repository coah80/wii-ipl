# PUD byte-return producer contract, 2026-10-03

Base: a894ff5c; branch agent/bittle/pud-return-contract.
Owned source: zi8pud2.c only. The copied cache was refreshed by a configured
full 43U build before recording the baseline. No caller or header changed.

## Producer and caller evidence

Every Zi8MatchPUDdata_ZHS exit returns zero, one, or an explicitly byte-cast
copied count. Zi8_8147FD7C forwards that result directly. Zi8MatchPUDdata
receives it, tests its byte value, and returns it; it never consumes any
higher result bits. The target wrapper retains exactly this data flow.

All external callers use byte-return declarations: zi8alpha.c and zi81key.c
for Zi8MatchPUDdata, and zi8cgetc.c for Zi8MatchPUDdata_ZHS. The previously
attempted caller-side full-word corrections were therefore based on a
misreconstructed producer chain rather than a demonstrated wide result.

Recovered ziU8 returns for all three functions and their local forward
declaration, plus ziU8 for the wrapper result local. Its test now uses the
typed byte directly. The explicit cast of copied in the actual producer
remains. Changing the coherent chain preserves the complete compiled object;
no compensating caller masks, local aliases, storage or register constraints
are required.

## Validation

Baseline report: /tmp/ezi-pud-baseline.json.
Baseline object: /tmp/ezi-pud-return-contract/baseline.o.
Final report: /tmp/ezi-pud-return-full-report.json.
Full build: /tmp/ezi-pud-return-full-build.log.
Detailed gates: /tmp/ezi-pud-return-verification.txt.

The complete zi8pud2.o file is byte-identical to baseline, including symbol
strings. Every function's disassembly is unchanged. All 1027 full-report
unit measures are unchanged: unit fuzzy 98.88764%, ZHS 98.32204%, exact
functions 6/7, exact code 720/2136 and exact data 48/120. This is a contract
correction, not a percentage gain or a new exact function.

All six existing exact functions retain ctxdiff diffs 0 and identical counts:
ZiIsPhoneticChar 16, ZiGetZHWordSize 31, Zi8CopyZHSpelling 33,
ZADP_Zi8SetPDremoveOpt 21, Zi8MatchPUDdata 50, Zi8_8147FD7C 29.
The unmatched producer remains 349/354 instructions. Allocated section sizes,
payloads and canonical relocations are unchanged: .text 2116, extab 48,
extabindex 72.

Pool first: identical and empty. Full 43U build passes with the approved
wrapper and WIBO_SJIS_MISSING_IMPORTS=1. DOL SHA1:
26116613f624061ba99c8d1a299aaa6efa85670d.
git diff --check passes. No remote, linking, metadata, header, caller,
assembly, volatile, dummy-storage or undefined-value change.
