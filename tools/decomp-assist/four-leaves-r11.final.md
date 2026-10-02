MAX round, start d5cd4ca777677117f1e02f1124ffb375178c391d.

| Unit | Instruction-exact before -> after | Matched code bytes before -> after | Matched data bytes before -> after |
| --- | --- | --- | --- |
| src/utility/iplESMisc | 30/31 -> 30/31 | 9404/11200 -> 9404/11200 | 0/4416 -> 4416/4416 |
| libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL | 10/14 -> 11/14 | 1008/2248 -> 1388/2248 | 72/112 -> 112/112 |
| libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var | 0/2 -> 0/2 | 0/2844 -> 0/2844 | 0/0 -> 0/0 |
| libs/RevoEX/src/net/md5 | 3/4 -> 3/4 | 600/1824 -> 600/1824 | 456/456 -> 456/456 |

NHTTPi_intToStr is now exact, 95/95 instructions and ctxdiff0. TakeDecimalDigit updates the actual remaining value by reference and returns the quotient; indexed output keeps the target scratch cursor. No other production function changed.

Remaining non-matching functions, one line each:

- DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap, 79.797325%, Aligned ticket/file scratch lifetime, return-status preservation, masked title formatting and inline helper boundaries. Baseline pool first diverges at83. Proper helpers make all114 strings identical but best tested source still differs structurally. MAX successful distinct attempts 14.
- NHTTPi_strnicmp, 99.76471%, 51/51 instructions; two initial constant materializations swap Z and zero. Every later instruction is exact. Six source predicate/operand/helper variations and two declaration orders leave the swap. MAX successful distinct attempts 6.
- NHTTPi_compareToken, 54.622223%, 44/45 retained instructions. Raw signed character lifetime and right conditional normalization differ. By-reference helper reaches45/45 with6 structural differences; changed equality/branch form and unsigned raw snapshots do not match. MAX successful distinct attempts 19.
- NHTTPi_Base64Encode, 60.285713%, 119/119 retained instructions. Source loads, masked fragment/table operand association and unrolled alphabet lookup/store scheduling differ. Staged byte helper reaches42 structural differences; cursor, triplet and declaration variants do not match. MAX successful distinct attempts 10.
- TMCJPEGDEC_IdctBlock_Lumi, 82.31518%, 257/257 instructions, frame0x140. Row/column butterfly multiply/add scheduling, DC/stride temporary lifetimes and register allocation differ. Eight helper/temporary variants, then140 declaration builds leave31 structural differences at best. MAX successful distinct attempts 8.
- TMCJPEGDEC_IdctBlock_Col, 92.47577%, 454/454 instructions, frame0x130. DC memset argument/clamp lifetime and full butterfly/store/clamp scheduling differ. Fill helper fixes the DC structural difference; eight variants then160 declaration builds leave14 structural differences at best. MAX successful distinct attempts 8.
- ProcessBlock, 43.290848%, 294/306 retained instructions, frame0x20. Indexed addresses, duplicated swapped loads, associated rotation sums and sequential cursor scheduling differ. Honest typed helper/materialized addresses reach306/306; seven source variants and93 declaration builds leave36 structural differences. MAX successful distinct attempts 7.

Data identity and extent proofs are recorded individually in four-leaves-r11.attempts.md. All18 config entries retain their addresses; target and source section totals remain unchanged. Anonymous literal names are taken from compiled symbols and matched function-relative relocations. NUL-terminated character array and nine-u32 initializer types prove the corrected extents. Absorbed neighbors and alignment remain unowned, as authorized.

Uncertainty: iplESMisc objdiff matched_data4416/4416 measures paired owned objects. The raw114-string pool still diverges at83 in DeleteUnauthorizedData. This is recorded code work; data100 does not assert identical raw pools or complete linking. The target status-return lifetime and compiler scheduling still lack an exact readable source reconstruction. JPEG has no data sections, so None/None in the raw gate is0/0.

Changed production files: config/43U/symbols.txt; libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL.c.

Evidence files: tools/decomp-assist/four-leaves-r11.attempts.md; four-leaves-r11.data-gate.txt; four-leaves-r11.http-data-gate.txt; four-leaves-r11.int-gate.txt; four-leaves-r11.final-gate.txt; four-leaves-r11.final.md.

Commits: 9b0b4dda recover es misc literal identities and extents; c2927e2a recover decimal scale initializer extent; 054e0b1f match decimal conversion inline boundary.

Every open function had a fresh origin fetch and unchanged public source check before work. This branch has no push, merge, rebase, other-worktree edits, new assembly or uncommitted experimental code.

Final full gate output, copied verbatim:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/utility/iplESMisc] objdiff: code 9404/11200 data 4416/4416 functions 30/31 fuzzy 96.7604 linked code 0
[libs/RevoEX/src/nhttp/NHTTP_stdlib_RVL] objdiff: code 1388/2248 data 112/112 functions 11/14 fuzzy 87.9359 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/buffer/idct_block_var] objdiff: code None/2844 data None/None functions 0/2 fuzzy 88.8031 linked code 0
[libs/RevoEX/src/net/md5] objdiff: code 600/1824 data 456/456 functions 3/4 fuzzy 61.9452 linked code 0
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
