# eZiText continuation attempts, 2026-09-30

Base: `884952a1`. One additional instruction-exact function: `Zi8GetCandidatesOrCount` (694/694 instructions, zero ctxdiff differences). All six pools remain identical. No Matching flags or shared headers changed.

| Unit | Instruction exact | Fuzzy | Matched code bytes | Matched data bytes |
| --- | --- | --- | --- | --- |
| zkokeyp | 1/7 -> 1/7 | 81.034615% -> 94.311540% | 332 -> 332/5200 | 0 -> 56/140 |
| zprepare | 0/1 -> 0/1 | 82.473404% -> 86.263830% | 0 -> 0/3760 | 8 -> 8/68 |
| zikorean | 2/3 -> 2/3 | 86.860450% -> 86.940636% | 2712 -> 2712/5188 | 24 -> 24/348 |
| zi8match | 7/10 -> 7/10 | 89.016470% -> 89.016470% | 3720 -> 3720/8256 | 608 -> 608/728 |
| zi8getc2 | 14/17 -> 15/17 | 94.793270% -> 99.950640% | 3584 -> 6360/6888 | 112 -> 324/332 |
| zi8dawg | 5/6 -> 5/6 | 99.975350% -> 99.975350% | 4356 -> 4356/4868 | 120 -> 120/120 |

## Remaining functions

- Zi8_8148302C: 99.491520%; Only register allocation: work pointer and table count exchange r27/r29. src 0xec base 0xec insns 59/59; 5 successful additional logged attempts.
- Zi8_81483264: 98.902435%; Only register allocation: parameter pointer and byte cursor exchange r30/r31. src 0xa4 base 0xa4 insns 41/41; 3 successful additional logged attempts.
- Zi8_81483308: 99.137930%; Only register allocation: insertion-count pointer and byte cursor exchange r29/r30. src 0xe8 base 0xe8 insns 58/58; 3 successful additional logged attempts.
- Zi8_814833F0: 99.042560%; Only register allocation: parameter pointer and byte cursor exchange r30/r31. src 0xbc base 0xbc insns 47/47; 3 successful additional logged attempts.
- Zi8_814834AC: 99.067055%; Packed-key initialization and one later narrowing instruction differ; work pointer and insertion cursor exchange registers. src 0x55c base 0x55c insns 343/343; 5 successful additional logged attempts.
- Zi8GetKOcandidates: 89.678630%; Word-prefix traversal, key-index assignment narrowing and address-expression scheduling still differ; final count/materialize arms now follow the original. src 0xa88 base 0xa74 insns 674/669; 14 successful additional logged attempts.
- Zi8PrepareMatch: 86.263830%; Original 0x70 frame restored. Stroke and phonetic instruction scheduling and conversions differ; original stores to its unused component-present byte are absent. src 0xf08 base 0xeb0 insns 962/940; 9 successful additional logged attempts.
- Zi8GetKoreanCandidates: 72.636510%; Mapping/candidate scanning blocks, temporary widths and address arithmetic differ; three-byte record arithmetic trials worsened the result. src 0x9b4 base 0x9ac insns 621/619; 6 successful additional logged attempts.
- Zi8MatchPhonetic: 85.950420%; Dictionary traversal, alternate sound and terminal checks retain different blocks and parameter allocation. src 0x598 base 0x5ac insns 358/363; 3 successful additional logged attempts.
- Zi8GetPyPhonetic: 75.584960%; Pinyin conversion/final parsing blocks and stack/register allocation differ; compound updates reached the original instruction count but lowered similarity. src 0xb5c base 0xb38 insns 727/718; 3 successful additional logged attempts.
- Zi8GetPyFinal: 99.245285%; Only register allocation: table address and shifted row index exchange r6/r7. src 0xd4 base 0xd4 insns 53/53; 3 successful additional logged attempts.
- Zi8GetDataSignature: 99.347824%; Only register allocation: destination, language and signature pointer use different saved registers. src 0x114 base 0x114 insns 69/69; 3 successful additional logged attempts.
- Zi8IsDupWChar: 99.365080%; Only register allocation: input character and duplicate flag exchange r27/r28. src 0xfc base 0xfc insns 63/63; 3 successful additional logged attempts.
- Zi8MatchROMdata1: 99.765625%; Only register allocation: group index and table address exchange r26/r27. src 0x200 base 0x200 insns 128/128; 3 successful additional logged attempts.

## Data evidence

- `zi8getc2`: both ten-entry language sequence jump tables now have the original source order and exact instruction targets. Matched data rose from 112 to 324 bytes. Its 16-byte search-order table is exact. The four-byte PY constant is exact. The extracted object contains four additional unnamed zero bytes after that constant and assigns eight zero bytes to the ZY symbol, while the real bitfield structure emits four bytes. Both setter functions already match. The remaining eight bytes appear to be extraction/alignment space; no objects were added to manufacture it.
- `zkokeyp` / `zikorean`: the original `zkokeyp` object contains no `.data`, although its exact `Zi8_81483118` has a ten-entry switch. The final 40 bytes of the original `zikorean` `.data` contain ten relocations to that `zkokeyp` function. The compiled `zkokeyp` emits those same ten references into its own object. This indicates a split/extraction boundary issue. No switch table was manually placed, and no function was moved between units. `zkokeyp` exception-table data now matches 56 bytes.
- `zikorean`: the two genuine 31-entry switches are present in source order (248 bytes); targets depending on unfinished candidate code still differ. The additional 40-byte cross-unit switch is the boundary issue above.
- `zprepare`: the 48-byte, 12-entry component switch is present; targets still depend on unfinished code. Exception metadata matches eight bytes.
- `zi8match`: all four constant tables, including the 432-byte Pinyin final table, match all 528 `.rodata` bytes in source order. The remaining data differences are function metadata.
- `zi8dawg`: all 120 metadata bytes remain exact. There are no string literals in any of these six objects.

The boundary/alignment explanations are inferences from the object sections, symbol extents and relocations. They have not been confirmed against the original source. The raw inventory follows.

```text
zkokeyp
obj extab 56 relocs 0 symbols [('', 0, 0), ('@etb_81330770', 0, 8), ('@etb_81330778', 8, 8), ('@etb_81330780', 16, 8), ('@etb_81330788', 24, 8), ('@etb_81330790', 32, 8), ('@etb_81330798', 40, 8), ('@etb_813307A0', 48, 8)]
obj extabindex 84 relocs 14 symbols [('', 0, 0), ('@eti_813314B8', 0, 12), ('@eti_813314C4', 12, 12), ('@eti_813314D0', 24, 12), ('@eti_813314DC', 36, 12), ('@eti_813314E8', 48, 12), ('@eti_813314F4', 60, 12), ('@eti_81331500', 72, 12)]
src extab 56 relocs 0 symbols [('', 0, 0), ('@34', 0, 8), ('@60', 8, 8), ('@78', 16, 8), ('@103', 24, 8), ('@124', 32, 8), ('@223', 40, 8), ('@389', 48, 8)]
src extabindex 84 relocs 14 symbols [('', 0, 0), ('@35', 0, 12), ('@61', 12, 12), ('@79', 24, 12), ('@104', 36, 12), ('@125', 48, 12), ('@224', 60, 12), ('@390', 72, 12)]
src .data 40 relocs 10 symbols [('', 0, 0), ('@59', 0, 40)]
zprepare
obj extab 8 relocs 0 symbols [('', 0, 0), ('@etb_813307D8', 0, 8)]
obj extabindex 12 relocs 2 symbols [('', 0, 0), ('@eti_81331554', 0, 12)]
obj .data 48 relocs 12 symbols [('', 0, 0), ('jumptable_8166B3D0', 0, 48)]
src extab 8 relocs 0 symbols [('', 0, 0), ('@231', 0, 8)]
src extabindex 12 relocs 2 symbols [('', 0, 0), ('@232', 0, 12)]
src .data 48 relocs 12 symbols [('', 0, 0), ('@230', 0, 48)]
zikorean
obj extab 24 relocs 0 symbols [('', 0, 0), ('@etb_81330748', 0, 8), ('@etb_81330750', 8, 8), ('@etb_81330758', 16, 8)]
obj extabindex 36 relocs 6 symbols [('', 0, 0), ('@eti_8133147C', 0, 12), ('@eti_81331488', 12, 12), ('@eti_81331494', 24, 12)]
obj .data 288 relocs 72 symbols [('', 0, 0), ('jumptable_8166B2B0', 0, 124), ('jumptable_8166B32C', 124, 124), ('jumptable_8166B3A8', 248, 40)]
src extab 24 relocs 0 symbols [('', 0, 0), ('@35', 0, 8), ('@164', 8, 8), ('@282', 16, 8)]
src extabindex 36 relocs 6 symbols [('', 0, 0), ('@36', 0, 12), ('@165', 12, 12), ('@283', 24, 12)]
src .data 248 relocs 62 symbols [('', 0, 0), ('@163', 0, 124), ('@281', 124, 124)]
zi8match
obj extab 80 relocs 0 symbols [('', 0, 0), ('@etb_81330650', 0, 8), ('@etb_81330658', 8, 8), ('@etb_81330660', 16, 8), ('@etb_81330668', 24, 8), ('@etb_81330670', 32, 8), ('@etb_81330678', 40, 8), ('@etb_81330680', 48, 8)]
obj extabindex 120 relocs 20 symbols [('', 0, 0), ('@eti_81331308', 0, 12), ('@eti_81331314', 12, 12), ('@eti_81331320', 24, 12), ('@eti_8133132C', 36, 12), ('@eti_81331338', 48, 12), ('@eti_81331344', 60, 12), ('@eti_81331350', 72, 12)]
obj .rodata 528 relocs 0 symbols [('', 0, 0), ('Zi8PinyinInitials', 0, 28), ('Zi8BpmfInitials', 28, 36), ('Zi8PinyinFinals', 64, 432), ('nodeHeaderTable', 496, 32)]
src extab 80 relocs 0 symbols [('', 0, 0), ('@41', 0, 8), ('@72', 8, 8), ('@176', 16, 8), ('@206', 24, 8), ('@238', 32, 8), ('@383', 40, 8), ('@583', 48, 8)]
src extabindex 120 relocs 20 symbols [('', 0, 0), ('@42', 0, 12), ('@73', 12, 12), ('@177', 24, 12), ('@207', 36, 12), ('@239', 48, 12), ('@384', 60, 12), ('@584', 72, 12)]
src .rodata 528 relocs 0 symbols [('', 0, 0), ('Zi8PinyinInitials', 0, 28), ('Zi8BpmfInitials', 28, 36), ('Zi8PinyinFinals', 64, 432), ('nodeHeaderTable', 496, 32)]
zi8getc2
obj extab 88 relocs 0 symbols [('', 0, 0), ('@etb_813305D8', 0, 8), ('@etb_813305E0', 8, 8), ('@etb_813305E8', 16, 8), ('@etb_813305F0', 24, 8), ('@etb_813305F8', 32, 8), ('@etb_81330600', 40, 8), ('@etb_81330608', 48, 8)]
obj extabindex 132 relocs 22 symbols [('', 0, 0), ('@eti_81331254', 0, 12), ('@eti_81331260', 12, 12), ('@eti_8133126C', 24, 12), ('@eti_81331278', 36, 12), ('@eti_81331284', 48, 12), ('@eti_81331290', 60, 12), ('@eti_8133129C', 72, 12)]
obj .rodata 16 relocs 0 symbols [('', 0, 0), ('Zi8SOdefaultArray', 0, 16)]
obj .data 80 relocs 20 symbols [('', 0, 0), ('jumptable_8166B260', 0, 40), ('jumptable_8166B288', 40, 40)]
obj .sdata2 8 relocs 0 symbols [('', 0, 0), ('Zi8PYdefaultFuzzyPairs', 0, 4)]
obj .sbss2 8 relocs 0 symbols [('', 0, 0), ('Zi8ZYdefaultFuzzyPairs', 0, 8)]
src extab 88 relocs 0 symbols [('', 0, 0), ('@88', 0, 8), ('@101', 8, 8), ('@167', 16, 8), ('@243', 24, 8), ('@254', 32, 8), ('@265', 40, 8), ('@511', 48, 8)]
src extabindex 132 relocs 22 symbols [('', 0, 0), ('@89', 0, 12), ('@102', 12, 12), ('@168', 24, 12), ('@244', 36, 12), ('@255', 48, 12), ('@266', 60, 12), ('@512', 72, 12)]
src .rodata 16 relocs 0 symbols [('', 0, 0), ('Zi8SOdefaultArray', 0, 16)]
src .data 80 relocs 20 symbols [('', 0, 0), ('@509', 40, 40), ('@510', 0, 40)]
src .sdata2 4 relocs 0 symbols [('', 0, 0), ('Zi8PYdefaultFuzzyPairs', 0, 4)]
src .sbss2 4 relocs 0 symbols [('', 0, 0), ('Zi8ZYdefaultFuzzyPairs', 0, 4)]
zi8dawg
obj extab 48 relocs 0 symbols [('', 0, 0), ('@etb_813305A0', 0, 8), ('@etb_813305A8', 8, 8), ('@etb_813305B0', 16, 8), ('@etb_813305B8', 24, 8), ('@etb_813305C0', 32, 8), ('@etb_813305C8', 40, 8)]
obj extabindex 72 relocs 12 symbols [('', 0, 0), ('@eti_81331200', 0, 12), ('@eti_8133120C', 12, 12), ('@eti_81331218', 24, 12), ('@eti_81331224', 36, 12), ('@eti_81331230', 48, 12), ('@eti_8133123C', 60, 12)]
src extab 48 relocs 0 symbols [('', 0, 0), ('@193', 0, 8), ('@220', 8, 8), ('@270', 16, 8), ('@350', 24, 8), ('@413', 32, 8), ('@440', 40, 8)]
src extabindex 72 relocs 12 symbols [('', 0, 0), ('@194', 0, 12), ('@221', 12, 12), ('@271', 24, 12), ('@351', 36, 12), ('@414', 48, 12), ('@441', 60, 12)]
```

## Attempt log

Every entry below is a compiled source experiment followed by pool checking, ctxdiff and fresh objdiff. Build failures are recorded separately and do not count toward the three successful attempts. Lower scores were discarded.

```text
zkokeyp Zi8_8148302C attempt 1: use typed Korean key record for high and low character bytes; fuzzy 98.38983; src 0xec base 0xec insns 59/59; diffs 17: [6, 7, 12, 14, 18, 19, 20, 21, 26, 27, 28, 29, 32, 34, 38, 44, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 2: keep decoded character as u16 rather than promoted u32; fuzzy 98.38983; src 0xec base 0xec insns 59/59; diffs 17: [6, 7, 12, 14, 18, 19, 20, 21, 26, 27, 28, 29, 32, 34, 38, 44, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 3: use signed table traversal index with explicit u16 comparison; fuzzy 98.38983; src 0xec base 0xec insns 59/59; diffs 17: [6, 7, 12, 14, 18, 19, 20, 21, 26, 27, 28, 29, 32, 34, 38, 44, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483264 attempt 1: wide traversal counter with explicit byte indexing and comparison; fuzzy 98.902435; src 0xa4 base 0xa4 insns 41/41; diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483264 attempt 2: signed traversal index, preserving byte limits and buffer addressing; fuzzy 98.902435; src 0xa4 base 0xa4 insns 41/41; diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483264 attempt 3: explicit tail-tested candidate scan in original block address order; fuzzy 98.902435; src 0xa4 base 0xa4 insns 41/41; diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 1: wide traversal counter with explicit byte indexing and comparison; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 2: signed traversal index, preserving byte limits and buffer addressing; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 3: explicit tail-tested candidate scan in original block address order; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 1: wide traversal counter with explicit byte indexing and comparison; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 2: signed traversal index, preserving byte limits and buffer addressing; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 3: explicit tail-tested candidate scan in original block address order; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 1: restore typed filter stack descriptor in target field order; fuzzy 90.868805; src 0x570 base 0x55c insns 348/343; --- replace mine 9:11 base 9:11; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 2: separate oversized-input return before key table traversal, matching target block order; fuzzy 93.58309; src 0x56c base 0x55c insns 347/343; --- replace mine 9:11 base 9:11; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 3: separate remaining-candidate compaction counter from insertion cursor and use compound remaining updates; fuzzy 95.61224; src 0x584 base 0x55c insns 353/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 1: restore Korean word search descriptor with byte length and signed count/index fields in target stack order; fuzzy 73.50523; src 0xad8 base 0xa74 insns 694/669; --- replace mine 0:1 base 0:1; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 2: restore compound byte/candidate updates and direct letters increment comparisons; fuzzy 76.75785; src 0xa84 base 0xa74 insns 673/669; --- replace mine 0:1 base 0:1; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 3: translate parity pass selection and trailing prefix count blocks literally; direct result returns; fuzzy 80.847534; src 0xa78 base 0xa74 insns 670/669; --- delete mine 15:16 base 15:15; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 4: compound candidate flag updates and count subtraction; shared scratch reset; signed key-byte comparison; fuzzy 99.067055; src 0x55c base 0x55c insns 343/343; diffs 318: [9, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34]; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 5: scope insertion cursor to matched-candidate path to shorten its lifetime; fuzzy 95.44898; src 0x568 base 0x55c insns 346/343; --- replace mine 5:12 base 5:11; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 4: restore full-width membership helper return and shared packed-key initialization; fuzzy 80.76532; src 0xa78 base 0xa74 insns 670/669; --- delete mine 15:16 base 15:15; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 5: group word offset upper bytes before combining low byte in target operand order; fuzzy 81.64126; src 0xa78 base 0xa74 insns 670/669; --- delete mine 15:16 base 15:15; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 6: correct candidate count field to byte 0x20; offset-first record arithmetic and assignment-result comparison; fuzzy 81.434975; src 0xa78 base 0xa74 insns 670/669; --- insert mine 14:14 base 14:15; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 7: translate remaining-prefix scan into tail-tested loop with match-ending arm first; fuzzy 82.76083; src 0xa80 base 0xa74 insns 672/669; --- insert mine 14:14 base 14:15; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 8: restore suffix advance and prefix restart order; direct output length comparison; fuzzy 85.03288; src 0xa8c base 0xa74 insns 675/669; --- insert mine 14:14 base 14:15; POOL IDENTICAL, no strings
zprepare Zi8PrepareMatch attempt 1: group actual prepare fields, arrays and saved segment length in target stack order; BUILD FAILED, see Zi8PrepareMatch-1.build
zprepare Zi8PrepareMatch attempt 2: restore high-bit language mode arms first and reuse byte index for prefix nibble fill; BUILD FAILED, see Zi8PrepareMatch-2.build
zprepare Zi8PrepareMatch attempt 3: use typed segment rows, unsigned phonetic count assignment and grouped input advance; BUILD FAILED, see Zi8PrepareMatch-3.build
zprepare Zi8PrepareMatch attempt 4: ordered typed prepare state and saved prefix length; fuzzy 81.90745; src 0xf38 base 0xeb0 insns 974/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 5: high-bit language mode before low-bit selection and common prefix index; fuzzy 84.75; src 0xf24 base 0xeb0 insns 969/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 6: typed segment rows and unsigned phonetic count; fuzzy 84.75; src 0xf20 base 0xeb0 insns 968/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zkokeyp Zi8GetKOcandidates attempt 9: readable offset-first key record expressions; fuzzy 85.03288; src 0xa8c base 0xa74 insns 675/669; --- insert mine 14:14 base 14:15; POOL IDENTICAL, no strings
zprepare Zi8PrepareMatch attempt 7: split byte controls, halfword phonetics and aligned buffers to avoid aggregate alignment gap; BUILD FAILED, see Zi8PrepareMatch-7.build
zprepare Zi8PrepareMatch attempt 8: declare aligned phonetics and buffers before byte controls; BUILD FAILED, see Zi8PrepareMatch-8.build
zprepare Zi8PrepareMatch attempt 9: split byte controls, halfword phonetics and aligned buffers to avoid aggregate alignment gap; fuzzy 84.75106; src 0xf24 base 0xeb0 insns 969/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 10: declare aligned phonetics and buffers before byte controls; fuzzy 84.75106; src 0xf24 base 0xeb0 insns 969/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 1: restore output reset source order to count byte 0x20, count 0x22, letters 0x21; fuzzy 72.471725; src 0x9b4 base 0x9ac insns 621/619; --- replace mine 8:10 base 8:10; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 2: decode three-byte Korean mapping records with original shift-minus-index arithmetic; fuzzy 71.93538; src 0x9d4 base 0x9ac insns 629/619; --- replace mine 15:19 base 15:19; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 3: use signed output cursor and character bounds matching original compare instructions; fuzzy 71.20355; src 0x9d4 base 0x9ac insns 629/619; --- replace mine 15:19 base 15:19; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8match Zi8GetPyFinal attempt 1: cache current pinyin final table row in typed byte pointer; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 2: use halfword row cursor for the 54-entry final table; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 3: evaluate table byte before input byte in final scan; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 1: separate strict and partial terminal checks into original independent branches; fuzzy 85.95042; src 0x598 base 0x5ac insns 358/363; --- replace mine 5:10 base 5:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 2: cache decoded dictionary record for code and alternate-sound flag checks; fuzzy 85.36915; src 0x588 base 0x5ac insns 354/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 3: use explicit remaining-node decrement before node decoding; fuzzy 84.24518; src 0x598 base 0x5ac insns 358/363; --- replace mine 5:10 base 5:10; POOL IDENTICAL, no strings
zi8getc2 Zi8GetCandidatesOrCount attempt 1: restore actual saved mode, converted count and character buffer stack layout; fuzzy 88.15994; src 0xae4 base 0xad8 insns 697/694; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 2: return signature results directly from their original blocks; fuzzy 88.629684; src 0xaf0 base 0xad8 insns 700/694; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 3: separate signature byte count from main candidate count lifetime; fuzzy 88.29683; src 0xaf0 base 0xad8 insns 700/694; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8match Zi8GetPyPhonetic attempt 1: restore pinyin byte descriptor order before final-string and conversion buffers; fuzzy 75.58218; src 0xb5c base 0xb38 insns 727/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 2: compound result count updates and independent conversion count initialization; fuzzy 74.462395; src 0xb38 base 0xb38 insns 718/718; diffs 675: [13, 16, 17, 20, 21, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44]; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 3: evaluate ASCII conversion bounds before extended uppercase range; fuzzy 74.456825; src 0xb38 base 0xb38 insns 718/718; diffs 675: [13, 16, 17, 20, 21, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44]; POOL IDENTICAL, no strings
zi8getc2 Zi8GetDataSignature attempt 1: use independent signature table identifier instead of reusing length; fuzzy 99.05797; src 0x114 base 0x114 insns 69/69; diffs 13: [5, 7, 9, 25, 27, 28, 29, 32, 33, 34, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetDataSignature attempt 2: scope signature table pointer after language mode selection; fuzzy 88.89855; src 0x124 base 0x114 insns 73/69; --- replace mine 5:11 base 5:10; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetDataSignature attempt 3: store copied terminator through pointer addition expression; fuzzy 99.347824; src 0x114 base 0x114 insns 69/69; diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 1: reverse duplicate comparison operands; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 2: use explicit decrement and tail-tested duplicate scan; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 3: use signed duplicate buffer cursor with original zero bound; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8dawg Zi8MatchROMdata1 attempt 1: retain table address as typed group pointer rather than integer address; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; POOL IDENTICAL, no strings
zi8dawg Zi8MatchROMdata1 attempt 2: scope table lookup address to fallback group lookup; fuzzy 93.10156; src 0x20c base 0x200 insns 131/128; --- replace mine 0:1 base 0:1; POOL IDENTICAL, no strings
zi8dawg Zi8MatchROMdata1 attempt 3: translate group selection into while loop with explicit index decrement; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; POOL IDENTICAL, no strings
zprepare Zi8PrepareMatch attempt 11: pack scalar controls and phonetics before one buffer aggregate to recover original frame; fuzzy 85.20638; src 0xf24 base 0xeb0 insns 969/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 12: reverse independent scalar declaration order while keeping packed buffer aggregate; fuzzy 85.315956; src 0xf24 base 0xeb0 insns 969/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 13: restore phonetic lookup basic blocks, removing compiler boolean spill and excess frame; fuzzy 86.237236; src 0xf0c base 0xeb0 insns 963/940; --- replace mine 9:13 base 9:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 14: group input advance and use typed segment rows without redundant count narrowing; fuzzy 86.26383; src 0xf08 base 0xeb0 insns 962/940; --- replace mine 9:13 base 9:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 4: correct full-width candidate return declarations and separate aligned character buffer; fuzzy 89.603745; src 0xae8 base 0xad8 insns 698/694; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 5: literal Korean and tone range bounds; direct format flag and compound option update; fuzzy 89.946686; src 0xae4 base 0xad8 insns 697/694; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 6: restore language switch and Chinese/Latin state machines in target block order; fuzzy 93.33573; src 0xae0 base 0xad8 insns 696/694; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 7: place saved state before aligned character array, use halfword error and byte restoration index; fuzzy 95.21326; src 0xaec base 0xad8 insns 699/694; --- replace mine 10:11 base 10:11; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 8: restore successful syllable candidate call before unsupported-format error arm; fuzzy 96.09222; src 0xaec base 0xad8 insns 699/694; --- replace mine 10:11 base 10:11; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 9: remove syllable temporary spill and restore candidate character postincrement/predecrement blocks; fuzzy 98.2392; src 0xad8 base 0xad8 insns 694/694; diffs 21: [116, 127, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 522, 523, 524, 525, 526, 527, 528, 529]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 10: restore Chinese sequence switch source order and successful stroke-format arm before error; fuzzy 99.12104; src 0xad8 base 0xad8 insns 694/694; diffs 10: [483, 484, 485, 486, 487, 488, 489, 490, 491, 492]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 11: restore one-key spelling arm before regular candidate arms; fuzzy 100.0; src 0xad8 base 0xad8 insns 694/694; diffs 0: []; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 4: full-width candidate result consistent with dispatcher ABI; fuzzy 72.63651; src 0x9b4 base 0x9ac insns 621/619; --- replace mine 8:10 base 8:10; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 5: explicit byte output conversion after full-width candidate accumulation; fuzzy 72.63651; src 0x9b4 base 0x9ac insns 621/619; --- replace mine 8:10 base 8:10; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 6: use byte-sized result counter matching candidate indexing masks; fuzzy 72.570274; src 0x9cc base 0x9ac insns 627/619; --- replace mine 8:10 base 8:10; POOL IDENTICAL up to 0 (mine=0 base=0)
zkokeyp Zi8GetKOcandidates attempt 10: restore final decrement/count/materialize block order and common result returns; fuzzy 89.67863; src 0xa88 base 0xa74 insns 674/669; --- insert mine 14:14 base 14:15; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 11: restore packed-key reset and unmatched-prefix restart order; fuzzy 89.45441; src 0xa88 base 0xa74 insns 674/669; --- delete mine 15:16 base 15:15; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 12: use typed nine-byte key records for repeated word and table accesses; fuzzy 87.86248; src 0xa68 base 0xa74 insns 666/669; --- insert mine 14:14 base 14:15; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 4: return halfword Korean key table index to match caller assignment ABI; fuzzy 98.47458; src 0xec base 0xec insns 59/59; diffs 7: [7, 12, 32, 34, 38, 40, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 13: evaluate halfword key lookup return at word traversal callers; fuzzy 89.64873; src 0xa84 base 0xa74 insns 673/669; --- insert mine 14:14 base 14:15; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 5: use native halfword key index with halfword return; fuzzy 91.52542; src 0xfc base 0xec insns 63/59; --- replace mine 7:8 base 7:8; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 14: evaluate native halfword key lookup result at word traversal callers; fuzzy 89.64873; src 0xa84 base 0xa74 insns 673/669; --- insert mine 14:14 base 14:15; POOL IDENTICAL, no strings
```

## Gate record

[Every gate block, including the failed intermediate gate](ezi3.round2.gates.txt). The intermediate candidate frame experiment lowered metadata matches from 112 to 24 bytes. A commit was made before its failed gate output was inspected; that commit was amended after recovering the exact frame and passing the gate. The final history contains the passing exact candidate dispatch change.

The final full gate rebuilt all six owned units from clean objects, passed with zero regressions and zero new forbidden/readability findings. The original DOL hash was preserved. Its full output is the last block in the gate record.

## Source commits

f71e3c51 restore korean count mode traversal arms
859c9c6d match candidate dispatch and restore language switch tables
77c0f589 recover prepare match frame and phonetic scan blocks
dff371df restore candidate dispatcher saved argument layout
ce517199 restore korean count fields and prepare language selection
877043a9 restore korean word search state and flag updates
ba8c537c restore korean candidate filter stack state
