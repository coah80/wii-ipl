# perm8d ultra continuation

Worktree sol-high, branch agent/w1003/sol-perm8d-ultra, initial HEAD 98d8a522. Initial full quick gate passes. DateParser 7/8 instruction-exact, code 1920/2372, data 40/40. Partition 19/20 instruction-exact, code 3380/3716, no data. Both pools are identical. Unrelated untracked pk4/pk6 logs are untouched.

Read perm8, NWC24DateParser, relevant fz7 and sol-high-four attempts, effort-policy, and prior orch progress history before trials. The prior-art index has no reference for either open function. Origin was fetched under the shared git lock; both functions remain non-exact on origin/main 409ef82d.

ConvertDateToDays target CFG: validate year/month; February Gregorian leap predicate and leap-day bound; ordinary day bound; month-prefix/day addition; March-or-later leap-day adjustment; signed year offset; annual and Gregorian quotient accumulation; return. No calls, frame, or immediate stack-store/reload. The first 92 instructions match; the final arithmetic differs in quotient scheduling and scalar allocation. No volatile is justified. DateParser .rodata is already 40/40 and both table objects are paired correctly.

pdm_part_is_master_boot_sector target CFG: clear output; validate 55/AA signature; four-entry decode loop with start/count nonzero test and first-entry output update; four-entry extent-bound loop; early return 2 or success 0. No calls. Target frame 0x30 saves r30/r31; current 0x40 also saves r29. Byte-pair arithmetic should combine high/low even and odd byte groups. Both original arrays occupy 16 bytes; start is at stack 0x18 and count at 0x08. First loop uses start/count/index r6/r7/r8; second loop reverses the cursor allocation. Partition owns only .text, so no data rename or extent change applies.

All experimental files are in /tmp/perm8d and compiled with this worktree's exact ninja flags, omitting only dependency generation. Raw instruction comparisons are /tmp/perm8d/trials.jsonl. No source experiment will be kept without exact matching and a passing full gate.
- Master attempt 1: direct array indexing in one or both loops, or fresh second-loop cursor lifetimes, combined with the existing helper, MBR_WORD and explicit byte-pair decoding. Valid comparisons 25; best penalty 24.
- Master attempt 2: a meaningful destination-writing MBR decoder, using direct, summed or bytewise accumulation, mutable/const byte views and native int/SDK long arithmetic. Tested both pointer and indexed traversals. Valid comparisons 224; best penalty 24.
- Date attempt 1: reuse the actual annual/century subtotal or prior-year offset as the final accumulator, including a real in-place decrement and separately staged century numerator. Signed long/native int result lifetimes and final operand order were varied. Valid comparisons 309; best penalty 1.
- Exact temporary candidate ConvertDateToDays /tmp/perm8d/ConvertDateToDays-a28442585b5f.c.
- ConvertDateToDays exact reconstruction: accumulate ordinary annual days first, form the real day-plus-century subtotal in centuryLeapDays, then return that subtotal plus the common-leap correction. No new locals or helpers. Correct subtotal operand order removes the last instruction difference. 113/113 instructions, zero differences in the temporary full unit.
- Exact temporary candidate ConvertDateToDays /tmp/perm8d/ConvertDateToDays-7ac42db86e86.c.
- Readable retained local name is totalDays, since it contains the day-of-year, ordinary-year days and century correction. The rename preserves the zero-difference result. Fresh origin check still has the original open function.

## Calendar acceptance

ConvertDateToDays worktree build is 113/113 instructions with ctxdiff diffs 0, exact-name objdiff 100.0%. The first clean full two-unit gate is GATE PASS, DateParser 7/8 -> 8/8, code 1920/2372 -> 2372/2372, data 40/40 unchanged. Every owned DateParser section is 100%. Pools identical, regressions 0, forbidden patterns 0, readability warnings 0. Full build passes, DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d. Evidence /tmp/perm8d/date-full-gate.log. The focused source diff changes only the final arithmetic accumulator and its meaningful local name; no helper, unused local, symbol, header or link flag changes.
- Master attempt 3: direct shift/multiply hybrids for each actual little-endian byte, with unsigned native-int and SDK-long promotion, even/odd pair trees and a separate indexed second loop. Valid comparisons 768; best penalty 20.
- Master attempt 4: actual MBR byte views using const-qualified input pointers, with declaration/loop scopes, signed or unsigned low-byte promotion and separate second-loop traversal lifetimes. Valid comparisons 81; best penalty 20.
- Master attempt 6: cache one actual start/count input byte using byte, halfword or unsigned-word scalar types, before/after the initial clear and at function/loop scope. Every cache is initialized and used. Valid comparisons 128; best penalty 19.
- Master attempt 5: the start and length fields use independent little-endian trees and promotions, preserving the improved traversal while testing direct assignment versus meaningful accumulation into the cleared start. Valid comparisons 1022; best penalty 19.
- Master attempt 8: real named even/odd endian sums, separate high-byte staging or all four decoded byte contributions. Tested direct/native word arithmetic, clear placement and independent count decoding. Valid comparisons 168; best penalty 19.

## Partition continuation

The input, traversal and byte-pair work produced temporary 84/84-instruction forms with 19 positional differences, improved from the previous readable 23-difference seed. These differences still include byte-load scheduling and sum grouping inside the decoder. No fuzzy-only partition change is retained. All target calls, branch exits, stack frame, output behavior and array extents were reviewed before tuning; the target does not justify a volatile declaration.
- Master attempt 7: cache meaningful pairs or full sets of MBR input bytes in target load order and other dependency-safe orders, with byte/word scalar types and function/loop scopes. Every cached input is used in its original field. Valid comparisons 960; best penalty 19.
- Master attempt 9: swap the real even/odd limb operands independently in both decoded fields and test meaningful shift/multiply byte forms. Valid comparisons 752; best penalty 19.

## Final open-function audit

- ConvertDateToDays is exact in the retained source. 313 valid temporary comparisons this round. No other DateParser function or data regressed.
- pdm_part_is_master_boot_sector remains open at retained objdiff 86.5%, 86/84 instructions. 4128 valid temporary comparisons this round, covering nine distinct source-level classes below. Best temporary form is 84/84 with 19 instruction differences; byte-load scheduling and sum/register choices remain unresolved. All partition source experiments were discarded.
  - array-access: 24 valid comparisons, best penalty 24.
  - destination-inline-decoder: 224 valid comparisons, best penalty 24.
  - direct-shift-multiply-hybrid: 768 valid comparisons, best penalty 20.
  - read-only-entry-view: 81 valid comparisons, best penalty 20.
  - independent-MBR-start-count-expressions: 1022 valid comparisons, best penalty 19.
  - cache-real-field-byte-: 128 valid comparisons, best penalty 19.
  - cache-real-field-byte-set: 960 valid comparisons, best penalty 19.
  - semantic-byte-pairs: 168 valid comparisons, best penalty 21.
  - independent-even-odd-operand-orders: 752 valid comparisons, best penalty 19.
- All temporary compiles succeeded. No own trial/search process remains active. No symbols, shared headers, configure flags, other units, upstream or other worktrees were changed. The latest fetched origin a3e3725c still has both functions open.
- Communication audit: one initial commentary before the worker prompt was read; no further conversational text during matching.

## Final full gate

Clean non-quick two-unit gate after every experiment stopped. ConvertDateToDays is exact-name objdiff 100.0% and ctxdiff 113/113, diffs 0. All eight DateParser functions and all 40 data bytes are exact. Partition source remains unchanged. Exact objdiff JSON is /tmp/perm8d/final-report.json. The auxiliary JSON assertion initially compared string byte counts with integers; normalizing with int confirms the same gate measurements.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 2372/2372 data 40/40 functions 8/8 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 8/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1920/2372 data 40 functions 7 fuzzy 99.4148
[libs/RVL_SDK/src/fa/pdm_partition] pool: IDENTICAL
[libs/RVL_SDK/src/fa/pdm_partition] objdiff: code 3380/3716 data None/None functions 19/20 fuzzy 98.7793 linked code 0
[libs/RVL_SDK/src/fa/pdm_partition] instruction-exact functions: 19/20
[libs/RVL_SDK/src/fa/pdm_partition]   section .text size 3716 match 98.779335
[libs/RVL_SDK/src/fa/pdm_partition]   below 100: pdm_part_is_master_boot_sector 86.5
[libs/RVL_SDK/src/fa/pdm_partition] baseline: code 3380/3716 data None functions 19 fuzzy 98.7793
regressions vs baseline: 0
global matched_code_percent: 91.81992 -> 91.83501
global fuzzy_match_percent: 99.71336 -> 99.71384
global complete_code_percent: 74.76262 -> 74.76262
global matched_data_percent: 99.77803 -> 99.77803
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
