# ChannelObj native linking

Baseline HEAD 8864436c, Equivalent; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
Read PR #934 native weak emission fix. Baseline report and ELF saved under /tmp/link3.*.

1. Set only ChannelObj to Matching and measure the first linked divergence.
   Result: Matching immediately produces DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Entire DOL is byte-identical to orig/43U/00000008.app; there is no first differing byte or shifted target symbol to investigate. Pool identical, 20/20 strings. No source/header emission changes required after the near1c landing.

2. Run the final clean gate, explicit build/43U/ok, all 56 ctxdiff checks, and compare every other unit with the initial report.
   Final clean gate passes; explicit ninja build/43U/ok passes. Objdiff code 10924/10924, data 2216/2216, functions 56/56; linked code 10924 and linked data 2216, both 100%. All 1026 other unit records are identical to the initial live report.

Instruction-check caveat: gate and ctxdiff report 55/56 because odiff.dis reads operands[0].imm for a conditional branch. In calcCursorAnim, branches at instruction indices 11, 21 and 22 use cr1, so operand zero is a register, not the branch target. Source function starts at object offset 0x1e08, original at 0x1cf8. The checker subtracts those different offsets from the register number 13. Actual instructions are identical: 41860014, 41860010, 40840014. Entire 240-byte calcCursorAnim bodies have SHA1 35d649cf56bd349a345a7f3da15fc3d80ac8c508 in both objects. A separate Capstone comparison using PPC_OP_IMM for branch targets verifies all 56/56 instruction streams. No repository or external verification tool was edited.

Final clean gate output:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/channelSelect/iplChannelObj] pool: IDENTICAL
[src/scene/channelSelect/iplChannelObj] objdiff: code 10924/10924 data 2216/2216 functions 56/56 fuzzy 100.0000 linked code 10924
[src/scene/channelSelect/iplChannelObj] instruction-exact functions: 55/56
[src/scene/channelSelect/iplChannelObj]   section .data size 1240 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .rodata size 784 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata size 120 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .sdata2 size 72 match 100.0
[src/scene/channelSelect/iplChannelObj]   section .text size 10924 match 100.0
[src/scene/channelSelect/iplChannelObj] baseline: code 10924/10924 data 2216 functions 56 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 90.94304 -> 90.94304
global fuzzy_match_percent: 99.58742 -> 99.58742
global complete_code_percent: 73.36610 -> 73.73083
global matched_data_percent: 99.36639 -> 99.36639
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```

No remaining non-matching function or data section. No source/header changes; configure.py switches this exact native object from Equivalent to Matching. Full DOL bytes equal the original, SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Before and after: objdiff 56/56 functions, code 10924/10924, data 2216/2216; linked code 0 -> 10924 and linked data 0 -> 2216. Gate instruction count 55/56 before and after, corrected branch-operand count 56/56.
