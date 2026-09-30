# ezi3 continuation, round 4

Baseline: `c835bedbc118fd5901af258151272ad240d9c378`.

All thirteen functions open at the baseline received at least three successful new source-level attempts, with distinct function-body SHA256 hashes. Fifty attempts built successfully; one additional pinyin control-flow experiment failed to build and is excluded from the counts. Every evaluation rebuilt only its object, checked the empty string pool, ran ctxdiff, and generated fresh objdiff. Losing experiments were restored.

`Zi8MatchPhonetic` is now instruction-exact: 363/363 instructions, zero ctxdiff differences. Its dictionary parameter remains in r17 instead of spilling, strictMode is read from its stack argument, traversal fields have the original frame offsets, sound-group branches have the original direction, and packed sound-offset evaluation follows the target. All zi8match data sections now score 100%, including its 120-byte extabindex. The pinyin loop-entry branch, Korean key-byte increment, phonetic input advance, and segment bound comparisons also improved. No shared headers or Matching flags changed.

## Before and after

| Unit | Instruction-exact functions | Matched code bytes | Matched data bytes | Code fuzzy percent |
|---|---|---|---|---|
| zkokeyp | 1/7 -> 1/7 | 332 -> 332 | 56 -> 56 | 98.615390 -> 98.653850 |
| zprepare | 0/1 -> 0/1 | 0 -> 0 | 8 -> 8 | 96.097870 -> 96.319145 |
| zi8match | 7/10 -> 8/10 | 3720 -> 5172 | 608 -> 728 | 99.035370 -> 99.530040 |
| zi8getc2 | 15/17 -> 15/17 | 6360 -> 6360 | 324 -> 324 | 99.950640 -> 99.950640 |
| zi8dawg | 5/6 -> 5/6 | 4356 -> 4356 | 120 -> 120 | 99.975350 -> 99.975350 |
| zikorean | 3/3 -> 3/3 | 5188 -> 5188 | 60 -> 60 | 100.000000 -> 100.000000 |

## Remaining functions

- `Zi8_8148302C`: 99.49152%; 59/59 instructions; six work/decoded-value register differences, r27/r29. Successful attempts this round: 4.
- `Zi8_81483264`: 98.902435%; 41/41 instructions; eight parameter/index register differences, r30/r31. Successful attempts this round: 3.
- `Zi8_81483308`: 99.13793%; 58/58 instructions; nine count-pointer/index register differences, r29/r30. Successful attempts this round: 3.
- `Zi8_814833F0`: 99.04256%; 47/47 instructions; eight parameter/index register differences, r30/r31. Successful attempts this round: 3.
- `Zi8_814834AC`: 99.3586%; 344/343 instructions; packed-word-to-byte initialization adds one narrowing instruction; two adds have reversed operands; work/candidate registers r25/r26 are swapped. Successful attempts this round: 3.
- `Zi8GetKOcandidates`: 97.96712%; 673/669 instructions; extra packed-key zero load, two helper-return halfword narrowings, one redundant move, and address/temporary scheduling remain. Successful attempts this round: 4.
- `Zi8PrepareMatch`: 96.319145%; 939/940 instructions; four target instructions storing an unread component flag are absent, with extra instructions elsewhere; component-address scheduling and temporary registers differ; switch relocations are 16 bytes early. Successful attempts this round: 3.
- `Zi8GetPyPhonetic`: 98.704735%; 718/718 instructions; 167 raw differences are solely the saved-register cycle initial/final/result-count/index/current/value. Applying the six-register map gives zero differences including branch destinations. Successful attempts this round: 3.
- `Zi8GetPyFinal`: 99.245285%; 53/53 instructions; eight r6/r7 temporary-register differences. Successful attempts this round: 4.
- `Zi8GetDataSignature`: 99.347824%; 69/69 instructions; nine destination/language/signature-pointer register differences. Successful attempts this round: 3.
- `Zi8IsDupWChar`: 99.36508%; 63/63 instructions; eight character/result-flag register differences, r27/r28. Successful attempts this round: 4.
- `Zi8MatchROMdata1`: 99.765625%; 128/128 instructions; five group-index/table-address register differences, r26/r27. Successful attempts this round: 3.

Completed: `Zi8MatchPhonetic`, 100.0%; ten successful new attempts.

## Data and uncertainties

All six owned pools are identical and empty. Real table contents and source order are preserved. No synthetic table, padding object, section pragma, shared-header change, hand-placed data, or address-pinned symbol was added.

- `zi8match`: all 528 real rodata bytes, 80 extab bytes, and 120 extabindex payload bytes match. Objdiff credits 728/728 data bytes. Raw extabindex relocation symbol names differ because compiler-generated extab symbols have different names; the corresponding section offsets and payloads agree.
- `zi8getc2`: both real switch tables (80 bytes and all 20 relocations), the 16-byte search-order table, extab and extabindex payloads are exact. Target sdata2 and sbss2 lengths are eight bytes each; source lengths are four. The target PY symbol is four bytes with an unnamed four-byte zero tail. The target ZY symbol is recorded as eight, while its existing twelve-bit-field type and exact setter copy one four-byte word. The reason for the additional zeros remains uncertain; changing alignment or inventing fields would lack source evidence.
- `zikorean`: both 124-byte switch tables have all 62 relocation tuples equal to the first 248 target bytes. Target data includes another 40 bytes with ten relocations into `Zi8_81483118` in zkokeyp. The source emits that real switch in zkokeyp instead. All Korean code and metadata payloads remain exact; the split/extraction data boundary remains unresolved.
- `zkokeyp`: extab is exact. Source-only switch data is the 40-byte table described above. Extabindex has size-word differences for the filter and candidate functions. No table was moved across translation units.
- `zprepare`: all 48 switch payload bytes match, but its twelve relocation addends remain 16 bytes early. The original frame byte at 0x0f is stored zero before scanning and one after detecting a component, and never read. Its semantic role is inferred. No unused local was added solely to manufacture those stores.
- `zi8dawg`: all 120 data/metadata payload bytes match.
- Dictionary byte pointers and record size in Zi8MatchPhonetic preserve the pointer ABI. No declarations in calling translation units were edited. The original source typedef names and the semantic name of the unread PrepareMatch flag remain unavailable.

Fresh section and relocation audit:

```text
zi8dawg
extab target/source bytes 48 48 equal True relocations equal True
extabindex target/source bytes 72 72 equal True relocations equal False
zi8getc2
.rodata target/source bytes 16 16 equal True relocations equal True
.data target/source bytes 80 80 equal True relocations equal True
target relocations [(0, 'Zi8GetCandidatesOrCount', 760, 1), (4, 'Zi8GetCandidatesOrCount', 796, 1), (8, 'Zi8GetCandidatesOrCount', 836, 1), (12, 'Zi8GetCandidatesOrCount', 876, 1), (16, 'Zi8GetCandidatesOrCount', 916, 1), (20, 'Zi8GetCandidatesOrCount', 956, 1), (24, 'Zi8GetCandidatesOrCount', 996, 1), (28, 'Zi8GetCandidatesOrCount', 1036, 1), (32, 'Zi8GetCandidatesOrCount', 1076, 1), (36, 'Zi8GetCandidatesOrCount', 1076, 1), (40, 'Zi8GetCandidatesOrCount', 420, 1), (44, 'Zi8GetCandidatesOrCount', 500, 1), (48, 'Zi8GetCandidatesOrCount', 456, 1), (52, 'Zi8GetCandidatesOrCount', 500, 1), (56, 'Zi8GetCandidatesOrCount', 456, 1), (60, 'Zi8GetCandidatesOrCount', 500, 1), (64, 'Zi8GetCandidatesOrCount', 456, 1), (68, 'Zi8GetCandidatesOrCount', 500, 1), (72, 'Zi8GetCandidatesOrCount', 544, 1), (76, 'Zi8GetCandidatesOrCount', 544, 1)]
source relocations [(0, 'Zi8GetCandidatesOrCount', 760, 1), (4, 'Zi8GetCandidatesOrCount', 796, 1), (8, 'Zi8GetCandidatesOrCount', 836, 1), (12, 'Zi8GetCandidatesOrCount', 876, 1), (16, 'Zi8GetCandidatesOrCount', 916, 1), (20, 'Zi8GetCandidatesOrCount', 956, 1), (24, 'Zi8GetCandidatesOrCount', 996, 1), (28, 'Zi8GetCandidatesOrCount', 1036, 1), (32, 'Zi8GetCandidatesOrCount', 1076, 1), (36, 'Zi8GetCandidatesOrCount', 1076, 1), (40, 'Zi8GetCandidatesOrCount', 420, 1), (44, 'Zi8GetCandidatesOrCount', 500, 1), (48, 'Zi8GetCandidatesOrCount', 456, 1), (52, 'Zi8GetCandidatesOrCount', 500, 1), (56, 'Zi8GetCandidatesOrCount', 456, 1), (60, 'Zi8GetCandidatesOrCount', 500, 1), (64, 'Zi8GetCandidatesOrCount', 456, 1), (68, 'Zi8GetCandidatesOrCount', 500, 1), (72, 'Zi8GetCandidatesOrCount', 544, 1), (76, 'Zi8GetCandidatesOrCount', 544, 1)]
.sdata2 target/source bytes 8 4 equal False relocations equal True
.sbss2 target/source bytes 8 4 equal False relocations equal True
extab target/source bytes 88 88 equal True relocations equal True
extabindex target/source bytes 132 132 equal True relocations equal False
zi8match
.rodata target/source bytes 528 528 equal True relocations equal True
extab target/source bytes 80 80 equal True relocations equal True
extabindex target/source bytes 120 120 equal True relocations equal False
zikorean
.data target/source bytes 288 248 equal False relocations equal False
target relocations [(0, 'Zi8GetKoreanCandidates', 1596, 1), (4, 'Zi8GetKoreanCandidates', 980, 1), (8, 'Zi8GetKoreanCandidates', 1012, 1), (12, 'Zi8GetKoreanCandidates', 1596, 1), (16, 'Zi8GetKoreanCandidates', 1044, 1), (20, 'Zi8GetKoreanCandidates', 1596, 1), (24, 'Zi8GetKoreanCandidates', 1596, 1), (28, 'Zi8GetKoreanCandidates', 1076, 1), (32, 'Zi8GetKoreanCandidates', 1108, 1), (36, 'Zi8GetKoreanCandidates', 1140, 1), (40, 'Zi8GetKoreanCandidates', 1596, 1), (44, 'Zi8GetKoreanCandidates', 1596, 1), (48, 'Zi8GetKoreanCandidates', 1596, 1), (52, 'Zi8GetKoreanCandidates', 1596, 1), (56, 'Zi8GetKoreanCandidates', 1596, 1), (60, 'Zi8GetKoreanCandidates', 1596, 1), (64, 'Zi8GetKoreanCandidates', 1596, 1), (68, 'Zi8GetKoreanCandidates', 1172, 1), (72, 'Zi8GetKoreanCandidates', 1204, 1), (76, 'Zi8GetKoreanCandidates', 1236, 1), (80, 'Zi8GetKoreanCandidates', 1596, 1), (84, 'Zi8GetKoreanCandidates', 1268, 1), (88, 'Zi8GetKoreanCandidates', 1300, 1), (92, 'Zi8GetKoreanCandidates', 1332, 1), (96, 'Zi8GetKoreanCandidates', 1364, 1), (100, 'Zi8GetKoreanCandidates', 1396, 1), (104, 'Zi8GetKoreanCandidates', 1428, 1), (108, 'Zi8GetKoreanCandidates', 1460, 1), (112, 'Zi8GetKoreanCandidates', 1492, 1), (116, 'Zi8GetKoreanCandidates', 1524, 1), (120, 'Zi8GetKoreanCandidates', 1556, 1), (124, 'Zi8_81481E6C', 1300, 1), (128, 'Zi8_81481E6C', 164, 1), (132, 'Zi8_81481E6C', 224, 1), (136, 'Zi8_81481E6C', 1300, 1), (140, 'Zi8_81481E6C', 284, 1), (144, 'Zi8_81481E6C', 1300, 1), (148, 'Zi8_81481E6C', 1300, 1), (152, 'Zi8_81481E6C', 344, 1), (156, 'Zi8_81481E6C', 404, 1), (160, 'Zi8_81481E6C', 464, 1), (164, 'Zi8_81481E6C', 1300, 1), (168, 'Zi8_81481E6C', 1300, 1), (172, 'Zi8_81481E6C', 1300, 1), (176, 'Zi8_81481E6C', 1300, 1), (180, 'Zi8_81481E6C', 1300, 1), (184, 'Zi8_81481E6C', 1300, 1), (188, 'Zi8_81481E6C', 1300, 1), (192, 'Zi8_81481E6C', 524, 1), (196, 'Zi8_81481E6C', 584, 1), (200, 'Zi8_81481E6C', 644, 1), (204, 'Zi8_81481E6C', 1300, 1), (208, 'Zi8_81481E6C', 704, 1), (212, 'Zi8_81481E6C', 764, 1), (216, 'Zi8_81481E6C', 824, 1), (220, 'Zi8_81481E6C', 884, 1), (224, 'Zi8_81481E6C', 944, 1), (228, 'Zi8_81481E6C', 1004, 1), (232, 'Zi8_81481E6C', 1064, 1), (236, 'Zi8_81481E6C', 1124, 1), (240, 'Zi8_81481E6C', 1184, 1), (244, 'Zi8_81481E6C', 1244, 1), (248, 'Zi8_81483118', 320, 1), (252, 'Zi8_81483118', 288, 1), (256, 'Zi8_81483118', 268, 1), (260, 'Zi8_81483118', 236, 1), (264, 'Zi8_81483118', 216, 1), (268, 'Zi8_81483118', 184, 1), (272, 'Zi8_81483118', 164, 1), (276, 'Zi8_81483118', 132, 1), (280, 'Zi8_81483118', 112, 1), (284, 'Zi8_81483118', 80, 1)]
source relocations [(0, 'Zi8GetKoreanCandidates', 1596, 1), (4, 'Zi8GetKoreanCandidates', 980, 1), (8, 'Zi8GetKoreanCandidates', 1012, 1), (12, 'Zi8GetKoreanCandidates', 1596, 1), (16, 'Zi8GetKoreanCandidates', 1044, 1), (20, 'Zi8GetKoreanCandidates', 1596, 1), (24, 'Zi8GetKoreanCandidates', 1596, 1), (28, 'Zi8GetKoreanCandidates', 1076, 1), (32, 'Zi8GetKoreanCandidates', 1108, 1), (36, 'Zi8GetKoreanCandidates', 1140, 1), (40, 'Zi8GetKoreanCandidates', 1596, 1), (44, 'Zi8GetKoreanCandidates', 1596, 1), (48, 'Zi8GetKoreanCandidates', 1596, 1), (52, 'Zi8GetKoreanCandidates', 1596, 1), (56, 'Zi8GetKoreanCandidates', 1596, 1), (60, 'Zi8GetKoreanCandidates', 1596, 1), (64, 'Zi8GetKoreanCandidates', 1596, 1), (68, 'Zi8GetKoreanCandidates', 1172, 1), (72, 'Zi8GetKoreanCandidates', 1204, 1), (76, 'Zi8GetKoreanCandidates', 1236, 1), (80, 'Zi8GetKoreanCandidates', 1596, 1), (84, 'Zi8GetKoreanCandidates', 1268, 1), (88, 'Zi8GetKoreanCandidates', 1300, 1), (92, 'Zi8GetKoreanCandidates', 1332, 1), (96, 'Zi8GetKoreanCandidates', 1364, 1), (100, 'Zi8GetKoreanCandidates', 1396, 1), (104, 'Zi8GetKoreanCandidates', 1428, 1), (108, 'Zi8GetKoreanCandidates', 1460, 1), (112, 'Zi8GetKoreanCandidates', 1492, 1), (116, 'Zi8GetKoreanCandidates', 1524, 1), (120, 'Zi8GetKoreanCandidates', 1556, 1), (124, 'Zi8_81481E6C', 1300, 1), (128, 'Zi8_81481E6C', 164, 1), (132, 'Zi8_81481E6C', 224, 1), (136, 'Zi8_81481E6C', 1300, 1), (140, 'Zi8_81481E6C', 284, 1), (144, 'Zi8_81481E6C', 1300, 1), (148, 'Zi8_81481E6C', 1300, 1), (152, 'Zi8_81481E6C', 344, 1), (156, 'Zi8_81481E6C', 404, 1), (160, 'Zi8_81481E6C', 464, 1), (164, 'Zi8_81481E6C', 1300, 1), (168, 'Zi8_81481E6C', 1300, 1), (172, 'Zi8_81481E6C', 1300, 1), (176, 'Zi8_81481E6C', 1300, 1), (180, 'Zi8_81481E6C', 1300, 1), (184, 'Zi8_81481E6C', 1300, 1), (188, 'Zi8_81481E6C', 1300, 1), (192, 'Zi8_81481E6C', 524, 1), (196, 'Zi8_81481E6C', 584, 1), (200, 'Zi8_81481E6C', 644, 1), (204, 'Zi8_81481E6C', 1300, 1), (208, 'Zi8_81481E6C', 704, 1), (212, 'Zi8_81481E6C', 764, 1), (216, 'Zi8_81481E6C', 824, 1), (220, 'Zi8_81481E6C', 884, 1), (224, 'Zi8_81481E6C', 944, 1), (228, 'Zi8_81481E6C', 1004, 1), (232, 'Zi8_81481E6C', 1064, 1), (236, 'Zi8_81481E6C', 1124, 1), (240, 'Zi8_81481E6C', 1184, 1), (244, 'Zi8_81481E6C', 1244, 1)]
extab target/source bytes 24 24 equal True relocations equal True
extabindex target/source bytes 36 36 equal True relocations equal False
zkokeyp
.data target/source bytes 0 40 equal False relocations equal False
extab target/source bytes 56 56 equal True relocations equal True
extabindex target/source bytes 84 84 equal False relocations equal False
zprepare
.data target/source bytes 48 48 equal True relocations equal False
target relocations [(0, 'Zi8PrepareMatch', 608, 1), (4, 'Zi8PrepareMatch', 484, 1), (8, 'Zi8PrepareMatch', 500, 1), (12, 'Zi8PrepareMatch', 516, 1), (16, 'Zi8PrepareMatch', 532, 1), (20, 'Zi8PrepareMatch', 548, 1), (24, 'Zi8PrepareMatch', 564, 1), (28, 'Zi8PrepareMatch', 580, 1), (32, 'Zi8PrepareMatch', 596, 1), (36, 'Zi8PrepareMatch', 608, 1), (40, 'Zi8PrepareMatch', 608, 1), (44, 'Zi8PrepareMatch', 516, 1)]
source relocations [(0, 'Zi8PrepareMatch', 592, 1), (4, 'Zi8PrepareMatch', 468, 1), (8, 'Zi8PrepareMatch', 484, 1), (12, 'Zi8PrepareMatch', 500, 1), (16, 'Zi8PrepareMatch', 516, 1), (20, 'Zi8PrepareMatch', 532, 1), (24, 'Zi8PrepareMatch', 548, 1), (28, 'Zi8PrepareMatch', 564, 1), (32, 'Zi8PrepareMatch', 580, 1), (36, 'Zi8PrepareMatch', 592, 1), (40, 'Zi8PrepareMatch', 592, 1), (44, 'Zi8PrepareMatch', 500, 1)]
extab target/source bytes 8 8 equal True relocations equal True
extabindex target/source bytes 12 12 equal False relocations equal False
```

## Attempt log

Successful per-function snapshots and full ctxdiff outputs remain in `/tmp/zi8round4`. Each of the thirteen initial open functions has at least three successful snapshots distinct from its initial body; their content hashes were checked. The failed attempt has an explicit BUILD FAILED entry and is not counted.

```text
zi8dawg Zi8MatchROMdata1 attempt 1: prefix decrement for the consumed dictionary group selector; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; POOL IDENTICAL, no strings
zi8dawg Zi8MatchROMdata1 attempt 2: treat fetched table address as a byte pointer throughout initialization; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; POOL IDENTICAL, no strings
zi8dawg Zi8MatchROMdata1 attempt 3: declare table address in its initialization branch; fuzzy 93.10156; src 0x20c base 0x200 insns 131/128; --- replace mine 0:1 base 0:1; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 1: use halfword row cursor rather than repeatedly masking word cursor; fuzzy 98.47458; src 0xec base 0xec insns 59/59; diffs 7: [7, 12, 32, 34, 38, 40, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 2: declare decoded character inside the search loop; fuzzy 89.81356; src 0xf8 base 0xec insns 62/59; --- replace mine 5:9 base 5:8; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 3: compare key first against decoded record character; fuzzy 99.40678; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; POOL IDENTICAL, no strings
zi8getc2 Zi8IsDupWChar attempt 1: advance duplicate-buffer count using explicit assignment; fuzzy 97.77778; src 0x100 base 0xfc insns 64/63; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 2: declare result flag after the pointer and cursor locals; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 3: iterate duplicate cursor with predecrement and explicit equality operand order; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zkokeyp Zi8_814834AC attempt 1: native unsigned packed prefix storage with unchanged suffix byte; fuzzy 99.3586; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 2: mask chained zero prefix assignment to suffix width explicitly; fuzzy 99.3586; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 3: form nine-byte record address by shifted index before reading character fields; fuzzy 99.30029; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zi8getc2 Zi8GetDataSignature attempt 1: declare signature pointer after the length local; fuzzy 99.347824; src 0x114 base 0x114 insns 69/69; diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetDataSignature attempt 2: place capacity rejection before zero-length rejection; fuzzy 90.434784; src 0x114 base 0x114 insns 69/69; diffs 16: [5, 7, 9, 28, 32, 33, 38, 39, 40, 41, 42, 43, 44, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetDataSignature attempt 3: use const byte pointer for immutable dictionary signature; fuzzy 99.347824; src 0x114 base 0x114 insns 69/69; diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8match Zi8GetPyFinal attempt 1: address and dereference final table cells explicitly; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 2: index row through a typed array pointer before selecting phonetic cells; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 3: keep row as word and mask only at table access and bound comparison; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 1: compare prior candidate first against input key; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 2: view scratch candidate records through named character fields; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 3: tail-tested scan with explicit continuation before duplicate return; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 1: compare stored halfword before input key; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 2: describe previous candidate slots with typed character record; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 3: separate byte cursor increment from scan condition in while loop; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483264 attempt 1: clear previous candidate slots in explicit tail-tested block order; fuzzy 98.902435; src 0xa4 base 0xa4 insns 41/41; diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483264 attempt 2: return status as byte boolean after clearing previous candidates; fuzzy 98.902435; src 0xa4 base 0xa4 insns 41/41; diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483264 attempt 3: initialize byte cursor at function entry before validating scratch; fuzzy 91.46342; src 0xa0 base 0xa4 insns 40/41; --- replace mine 6:7 base 6:7; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 1: remaining-count loop with separate increment and output-bound test; fuzzy 98.704735; src 0xb38 base 0xb38 insns 718/718; diffs 167: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 2: enter shared remaining-count tail before first pinyin segment; BUILD FAILED, see Zi8GetPyPhonetic-2.build
zi8match Zi8GetPyPhonetic attempt 3: do loop entering count guard while keeping output bound at tail; fuzzy 98.704735; src 0xb38 base 0xb38 insns 718/718; diffs 167: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 4: declare live character and input cursor before temporary conversion buffers; fuzzy 98.704735; src 0xb38 base 0xb38 insns 718/718; diffs 167: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 1: postincrement byte scan cursor to avoid unused assignment-value narrowing; fuzzy 97.96712; src 0xa84 base 0xa74 insns 673/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 2: assign packed prefix then suffix using a single zero-valued chain; fuzzy 97.96712; src 0xa84 base 0xa74 insns 673/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 3: narrow final table character implicitly at candidate halfword store; fuzzy 97.96712; src 0xa84 base 0xa74 insns 673/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 4: reuse initialized key-byte cursor when entering multi-byte prefix scan; fuzzy 97.54111; src 0xa78 base 0xa74 insns 670/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 1: combine strict boundary rejection in one partial-mode condition; fuzzy 97.2011; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 2: branch on strict mode once before checking dictionary boundary; fuzzy 96.421486; src 0x5ac base 0x5ac insns 363/363; diffs 104: [6, 7, 8, 82, 83, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 225, 227, 228, 229, 230]; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 3: decode sound offset with low byte before table-address high byte; fuzzy 97.09642; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zprepare Zi8PrepareMatch attempt 1: advance phonetic input before subtracting the consumed final character; fuzzy 96.30532; src 0xeac base 0xeb0 insns 939/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 2: compare consumed element index first and use explicit segment capacity; fuzzy 96.319145; src 0xeac base 0xeb0 insns 939/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 3: restore initial phonetic before final phonetic in fallback arm; fuzzy 96.318085; src 0xeac base 0xeb0 insns 939/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zkokeyp Zi8_8148302C attempt 4: name decoded character, table count and table index by their record roles; fuzzy 99.49152; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 4: branch from completed sound group to next node before repeating unfinished group; fuzzy 97.242424; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 5: use dictionary byte pointer and record-sized native array indexing at both node accesses; fuzzy 99.22314; src 0x5ac base 0x5ac insns 363/363; diffs 10: [111, 112, 113, 114, 115, 116, 117, 118, 119, 120]; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 6: pair packed high and low offset bytes before adding table base and middle byte; fuzzy 99.1157; src 0x5ac base 0x5ac insns 363/363; diffs 8: [111, 114, 115, 116, 117, 118, 119, 120]; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 7: packed offset in original byte-read order, paired sums kept explicit; fuzzy 99.05785; src 0x5ac base 0x5ac insns 363/363; diffs 10: [111, 112, 113, 114, 115, 116, 117, 118, 119, 120]; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 8: typed halfword middle byte while adding packed high and low offset first; fuzzy 98.812675; src 0x5b0 base 0x5ac insns 364/363; --- replace mine 42:43 base 42:43; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 9: retain low offset byte addition within table-relative middle-byte sum; fuzzy 99.421486; src 0x5ac base 0x5ac insns 363/363; diffs 5: [111, 112, 113, 114, 115]; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 10: sound address expression tableAddress + ((node[9] & 0xF) * 0x10000 + (node[0xB] + node[0xA] * 0x100)); fuzzy 100.0; src 0x5ac base 0x5ac insns 363/363; diffs 0: []; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 4: access phonetic output cells through the eight-byte final-table record; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8getc2 Zi8IsDupWChar attempt 4: keep duplicate scan cursor in engine-native unsigned word type; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
```

## Source changes measured by each attempt

### Zi8MatchROMdata1 attempt 1

zi8dawg Zi8MatchROMdata1 attempt 1: prefix decrement for the consumed dictionary group selector; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchROMdata1
+++ attempt-1/Zi8MatchROMdata1
@@ -16,3 +16,3 @@
       for (; (*ZI_WORK->unk_0x1764 != 0xff && ((groupIndex & 0xff) != 0));
-          groupIndex = groupIndex - 1) {
+          --groupIndex) {
         while (*ZI_WORK->unk_0x1764 != 0xff) {
```

### Zi8MatchROMdata1 attempt 2

zi8dawg Zi8MatchROMdata1 attempt 2: treat fetched table address as a byte pointer throughout initialization; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchROMdata1
+++ attempt-2/Zi8MatchROMdata1
@@ -3,3 +3,3 @@
   unsigned int result;
-  ziU32 tableAddress;
+  ziU8* tableAddress;
 
@@ -10,3 +10,3 @@
       if (Zi8GetTableSize(language & 0xff,0xb,ZI_WORK) != 0) {
-        tableAddress = Zi8GetTableAddress(language & 0xff,0xb,ZI_WORK);
+        tableAddress = (ziU8*)Zi8GetTableAddress(language & 0xff,0xb,ZI_WORK);
         ZI_WORK->unk_0x1764 = (ziU8*)tableAddress;
```

### Zi8MatchROMdata1 attempt 3

zi8dawg Zi8MatchROMdata1 attempt 3: declare table address in its initialization branch; fuzzy 93.10156; src 0x20c base 0x200 insns 131/128; --- replace mine 0:1 base 0:1; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchROMdata1
+++ attempt-3/Zi8MatchROMdata1
@@ -3,3 +3,2 @@
   unsigned int result;
-  ziU32 tableAddress;
 
@@ -9,2 +8,3 @@
     if (ZI_WORK->unk_0x1764 == 0) {
+      ziU32 tableAddress;
       if (Zi8GetTableSize(language & 0xff,0xb,ZI_WORK) != 0) {
```

### Zi8_8148302C attempt 1

zkokeyp Zi8_8148302C attempt 1: use halfword row cursor rather than repeatedly masking word cursor; fuzzy 98.47458; src 0xec base 0xec insns 59/59; diffs 7: [7, 12, 32, 34, 38, 40, 49]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_8148302C
+++ attempt-1/Zi8_8148302C
@@ -3,8 +3,8 @@
     ziU16 count;
-    ziU32 i;
+    ziU16 i;
 
     count = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
-    for (i = 0; (ziU16)i < count; i++) {
-        value = (ziU16)(((ziU16)table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 7] << 8) |
-                       table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 8]);
+    for (i = 0; i < count; i++) {
+        value = (ziU16)(((ziU16)table[(i << 3) + i + 7] << 8) |
+                       table[(i << 3) + i + 8]);
         if (value == key) {
```

### Zi8_8148302C attempt 2

zkokeyp Zi8_8148302C attempt 2: declare decoded character inside the search loop; fuzzy 89.81356; src 0xf8 base 0xec insns 62/59; --- replace mine 5:9 base 5:8; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_8148302C
+++ attempt-2/Zi8_8148302C
@@ -1,3 +1,2 @@
 ziU32 Zi8_8148302C(ziU16 key, ziU8* table ZI_NEED_WORK) {
-    ziU32 value;
     ziU16 count;
@@ -7,2 +6,3 @@
     for (i = 0; (ziU16)i < count; i++) {
+        ziU32 value;
         value = (ziU16)(((ziU16)table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 7] << 8) |
```

### Zi8_8148302C attempt 3

zkokeyp Zi8_8148302C attempt 3: compare key first against decoded record character; fuzzy 99.40678; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_8148302C
+++ attempt-3/Zi8_8148302C
@@ -9,3 +9,3 @@
                        table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 8]);
-        if (value == key) {
+        if (key == value) {
             Zi8LogError(0x64, ZI_WORK);
```

### Zi8IsDupWChar attempt 1

zi8getc2 Zi8IsDupWChar attempt 1: advance duplicate-buffer count using explicit assignment; fuzzy 97.77778; src 0x100 base 0xfc insns 64/63; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8IsDupWChar
+++ attempt-1/Zi8IsDupWChar
@@ -19,3 +19,3 @@
     }
-    ZI_WORK->unk_0x539++;
+    ZI_WORK->unk_0x539 = ZI_WORK->unk_0x539 + 1;
     buffer[(*buffer)++] = character;
```

### Zi8IsDupWChar attempt 2

zi8getc2 Zi8IsDupWChar attempt 2: declare result flag after the pointer and cursor locals; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8IsDupWChar
+++ attempt-2/Zi8IsDupWChar
@@ -1,5 +1,5 @@
 ziBool Zi8IsDupWChar(ziWChar character ZI_NEED_WORK) {
-    ziBool duplicate;
     ziU16* buffer;
     unsigned int index;
+    ziBool duplicate;
     duplicate = 0;
```

### Zi8IsDupWChar attempt 3

zi8getc2 Zi8IsDupWChar attempt 3: iterate duplicate cursor with predecrement and explicit equality operand order; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8IsDupWChar
+++ attempt-3/Zi8IsDupWChar
@@ -13,4 +13,4 @@
     }
-    for (index = ZI_WORK->unk_0x539; index != 0; index--) {
-        if (character == buffer[index]) {
+    for (index = ZI_WORK->unk_0x539; index != 0; --index) {
+        if (buffer[index] == character) {
             duplicate = 1;
```

### Zi8_814834AC attempt 1

zkokeyp Zi8_814834AC attempt 1: native unsigned packed prefix storage with unchanged suffix byte; fuzzy 99.3586; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_814834AC
+++ attempt-1/Zi8_814834AC
@@ -11,3 +11,3 @@
         union {
-            ziU32 firstWord;
+            unsigned int firstWord;
             ziU8 bytes[5];
```

### Zi8_814834AC attempt 2

zkokeyp Zi8_814834AC attempt 2: mask chained zero prefix assignment to suffix width explicitly; fuzzy 99.3586; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_814834AC
+++ attempt-2/Zi8_814834AC
@@ -23,3 +23,3 @@
     matched = 0;
-    filter.keys.bytes[4] = filter.keys.firstWord = 0;
+    filter.keys.bytes[4] = (filter.keys.firstWord = 0) & 0xFF;
     Zi8LogError(0x64, ZI_WORK);
```

### Zi8_814834AC attempt 3

zkokeyp Zi8_814834AC attempt 3: form nine-byte record address by shifted index before reading character fields; fuzzy 99.30029; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_814834AC
+++ attempt-3/Zi8_814834AC
@@ -80,3 +80,3 @@
                         if (param->candidates[filter.candidateIndex] ==
-                            (((ziU16)((ZiKoreanKeyEntry*)filter.tableA)[i].characterHigh << 8) | (ziU16)((ZiKoreanKeyEntry*)filter.tableA)[i].characterLow)) {
+                            (((ziU16)((ZiKoreanKeyEntry*)(filter.tableA + ((i << 3) + i)))->characterHigh << 8) | (ziU16)((ZiKoreanKeyEntry*)(filter.tableA + ((i << 3) + i)))->characterLow)) {
                             matched++;
```

### Zi8GetDataSignature attempt 1

zi8getc2 Zi8GetDataSignature attempt 1: declare signature pointer after the length local; fuzzy 99.347824; src 0x114 base 0x114 insns 69/69; diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8GetDataSignature
+++ attempt-1/Zi8GetDataSignature
@@ -1,4 +1,4 @@
 static ziU16 Zi8GetDataSignature(ziU8* destination, ziU16 capacity, ziU8 language, ziPtr work) {
+    ziU16 length;
     ziU8* signature;
-    ziU16 length;
     if (language == 1) {
```

### Zi8GetDataSignature attempt 2

zi8getc2 Zi8GetDataSignature attempt 2: place capacity rejection before zero-length rejection; fuzzy 90.434784; src 0x114 base 0x114 insns 69/69; diffs 16: [5, 7, 9, 28, 32, 33, 38, 39, 40, 41, 42, 43, 44, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8GetDataSignature
+++ attempt-2/Zi8GetDataSignature
@@ -14,3 +14,3 @@
     length = Zi8GetTableCount(language, (ziU8)length, work);
-    if (length == 0 || length > capacity) {
+    if (length > capacity || length == 0) {
         Zi8LogError(0x961, work);
```

### Zi8GetDataSignature attempt 3

zi8getc2 Zi8GetDataSignature attempt 3: use const byte pointer for immutable dictionary signature; fuzzy 99.347824; src 0x114 base 0x114 insns 69/69; diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8GetDataSignature
+++ attempt-3/Zi8GetDataSignature
@@ -1,3 +1,3 @@
 static ziU16 Zi8GetDataSignature(ziU8* destination, ziU16 capacity, ziU8 language, ziPtr work) {
-    ziU8* signature;
+    const ziU8* signature;
     ziU16 length;
@@ -18,3 +18,3 @@
     }
-    Zi8Memcpy(destination, signature, length);
+    Zi8Memcpy(destination, (ziPtr)signature, length);
     destination[length] = 0;
```

### Zi8GetPyFinal attempt 1

zi8match Zi8GetPyFinal attempt 1: address and dereference final table cells explicitly; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetPyFinal
+++ attempt-1/Zi8GetPyFinal
@@ -15,4 +15,4 @@
     }
-    *initial = Zi8PinyinFinals[row][4];
-    *final = Zi8PinyinFinals[row][5];
+    *initial = *(&Zi8PinyinFinals[row][4]);
+    *final = *(&Zi8PinyinFinals[row][5]);
     return 1;
```

### Zi8GetPyFinal attempt 2

zi8match Zi8GetPyFinal attempt 2: index row through a typed array pointer before selecting phonetic cells; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetPyFinal
+++ attempt-2/Zi8GetPyFinal
@@ -15,4 +15,4 @@
     }
-    *initial = Zi8PinyinFinals[row][4];
-    *final = Zi8PinyinFinals[row][5];
+    *initial = (*(Zi8PinyinFinals + row))[4];
+    *final = (*(Zi8PinyinFinals + row))[5];
     return 1;
```

### Zi8GetPyFinal attempt 3

zi8match Zi8GetPyFinal attempt 3: keep row as word and mask only at table access and bound comparison; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetPyFinal
+++ attempt-3/Zi8GetPyFinal
@@ -2,3 +2,3 @@
     ziU8 index = 0;
-    ziU8 row;
+    unsigned int row;
     row = 0;
@@ -7,3 +7,3 @@
     while (index < 4) {
-        if (pinyin[index] != Zi8PinyinFinals[row][index]) {
+        if (pinyin[index] != Zi8PinyinFinals[(ziU8)row][index]) {
             break;
@@ -15,4 +15,4 @@
     }
-    *initial = Zi8PinyinFinals[row][4];
-    *final = Zi8PinyinFinals[row][5];
+    *initial = Zi8PinyinFinals[(ziU8)row][4];
+    *final = Zi8PinyinFinals[(ziU8)row][5];
     return 1;
@@ -22,3 +22,3 @@
 check_row:
-    if (row < 0x36) {
+    if ((ziU8)row < 0x36) {
         goto scan_row;
```

### Zi8_81483308 attempt 1

zkokeyp Zi8_81483308 attempt 1: compare prior candidate first against input key; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_81483308
+++ attempt-1/Zi8_81483308
@@ -10,3 +10,3 @@
     for (i = 0; i < param->maxCandidates; i++) {
-        if (key == ((ziU16*)param->scratch)[i]) {
+        if (((ziU16*)param->scratch)[i] == key) {
             return 1;
```

### Zi8_81483308 attempt 2

zkokeyp Zi8_81483308 attempt 2: view scratch candidate records through named character fields; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_81483308
+++ attempt-2/Zi8_81483308
@@ -1,2 +1,3 @@
 ziU32 Zi8_81483308(ziGetParam* param, ziU16 key, ziU8* count ZI_NEED_WORK) {
+    typedef struct { ziU16 character; } PreviousCandidate;
     ziU8 i;
@@ -10,3 +11,3 @@
     for (i = 0; i < param->maxCandidates; i++) {
-        if (key == ((ziU16*)param->scratch)[i]) {
+        if (key == ((PreviousCandidate*)param->scratch)[i].character) {
             return 1;
@@ -15,3 +16,3 @@
 
-    ((ziU16*)param->scratch)[*count] = key;
+    ((PreviousCandidate*)param->scratch)[*count].character = key;
     if (++*count >= param->maxCandidates) {
```

### Zi8_81483308 attempt 3

zkokeyp Zi8_81483308 attempt 3: tail-tested scan with explicit continuation before duplicate return; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_81483308
+++ attempt-3/Zi8_81483308
@@ -9,7 +9,11 @@
 
-    for (i = 0; i < param->maxCandidates; i++) {
-        if (key == ((ziU16*)param->scratch)[i]) {
-            return 1;
-        }
-    }
+    i = 0;
+    goto check_previous;
+scan_previous:
+    if (key != ((ziU16*)param->scratch)[i]) goto advance_previous;
+    return 1;
+advance_previous:
+    i++;
+check_previous:
+    if (i < param->maxCandidates) goto scan_previous;
```

### Zi8_814833F0 attempt 1

zkokeyp Zi8_814833F0 attempt 1: compare stored halfword before input key; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_814833F0
+++ attempt-1/Zi8_814833F0
@@ -10,3 +10,3 @@
     for (i = 0; i < param->maxCandidates; i++) {
-        if (key == ((ziU16*)param->scratch)[i]) {
+        if (((ziU16*)param->scratch)[i] == key) {
             return 1;
```

### Zi8_814833F0 attempt 2

zkokeyp Zi8_814833F0 attempt 2: describe previous candidate slots with typed character record; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_814833F0
+++ attempt-2/Zi8_814833F0
@@ -1,2 +1,3 @@
 ziU32 Zi8_814833F0(const ziGetParam* param, ziU16 key ZI_NEED_WORK) {
+    typedef struct { ziU16 character; } PreviousCandidate;
     ziU8 i;
@@ -10,3 +11,3 @@
     for (i = 0; i < param->maxCandidates; i++) {
-        if (key == ((ziU16*)param->scratch)[i]) {
+        if (key == ((PreviousCandidate*)param->scratch)[i].character) {
             return 1;
```

### Zi8_814833F0 attempt 3

zkokeyp Zi8_814833F0 attempt 3: separate byte cursor increment from scan condition in while loop; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_814833F0
+++ attempt-3/Zi8_814833F0
@@ -9,3 +9,4 @@
 
-    for (i = 0; i < param->maxCandidates; i++) {
+    i = 0;
+    while (i < param->maxCandidates) {
         if (key == ((ziU16*)param->scratch)[i]) {
@@ -13,2 +14,3 @@
         }
+        ++i;
     }
```

### Zi8_81483264 attempt 1

zkokeyp Zi8_81483264 attempt 1: clear previous candidate slots in explicit tail-tested block order; fuzzy 98.902435; src 0xa4 base 0xa4 insns 41/41; diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_81483264
+++ attempt-1/Zi8_81483264
@@ -8,5 +8,9 @@
 
-    for (i = 0; i < param->maxCandidates; i++) {
-        ((ziU16*)param->scratch)[i] = 0;
-    }
+    i = 0;
+    goto check_slot;
+clear_slot:
+    ((ziU16*)param->scratch)[i] = 0;
+    ++i;
+check_slot:
+    if (i < param->maxCandidates) goto clear_slot;
```

### Zi8_81483264 attempt 2

zkokeyp Zi8_81483264 attempt 2: return status as byte boolean after clearing previous candidates; fuzzy 98.902435; src 0xa4 base 0xa4 insns 41/41; diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_81483264
+++ attempt-2/Zi8_81483264
@@ -1,2 +1,2 @@
-ziU32 Zi8_81483264(const ziGetParam* param ZI_NEED_WORK) {
+ziBool Zi8_81483264(const ziGetParam* param ZI_NEED_WORK) {
     ziU8 i;
```

### Zi8_81483264 attempt 3

zkokeyp Zi8_81483264 attempt 3: initialize byte cursor at function entry before validating scratch; fuzzy 91.46342; src 0xa0 base 0xa4 insns 40/41; --- replace mine 6:7 base 6:7; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_81483264
+++ attempt-3/Zi8_81483264
@@ -1,3 +1,3 @@
 ziU32 Zi8_81483264(const ziGetParam* param ZI_NEED_WORK) {
-    ziU8 i;
+    ziU8 i = 0;
 
@@ -8,3 +8,3 @@
 
-    for (i = 0; i < param->maxCandidates; i++) {
+    for (; i < param->maxCandidates; i++) {
         ((ziU16*)param->scratch)[i] = 0;
```

### Zi8GetPyPhonetic attempt 1

zi8match Zi8GetPyPhonetic attempt 1: remaining-count loop with separate increment and output-bound test; fuzzy 98.704735; src 0xb38 base 0xb38 insns 718/718; diffs 167: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetPyPhonetic
+++ attempt-1/Zi8GetPyPhonetic
@@ -39,3 +39,3 @@
     *bestFinal = 0;
-    while ((outputIndex <= 0xf) && (count != 0)) {
+    while (count != 0) {
         initial[outputIndex] = 0;
@@ -266,2 +266,3 @@
         outputIndex++;
+        if (outputIndex > 0xf) break;
     }
```

### Zi8GetPyPhonetic attempt 2

zi8match Zi8GetPyPhonetic attempt 2: enter shared remaining-count tail before first pinyin segment; BUILD FAILED, see Zi8GetPyPhonetic-2.build

```diff
--- initial/Zi8GetPyPhonetic
+++ attempt-2/Zi8GetPyPhonetic
@@ -39,3 +39,5 @@
     *bestFinal = 0;
-    while ((outputIndex <= 0xf) && (count != 0)) {
+    goto check_remaining;
+parse_output: {
+
         initial[outputIndex] = 0;
@@ -267,2 +269,6 @@
     }
+    if (outputIndex > 0xf) goto parsed_output;
+check_remaining:
+    if (count != 0) goto parse_output;
+parsed_output:
     if ((result > 1) && (text[*resultCount - 1] >= 0xF341) && (text[*resultCount - 1] <= 0xF35A)) {
```

### Zi8GetPyPhonetic attempt 3

zi8match Zi8GetPyPhonetic attempt 3: do loop entering count guard while keeping output bound at tail; fuzzy 98.704735; src 0xb38 base 0xb38 insns 718/718; diffs 167: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetPyPhonetic
+++ attempt-3/Zi8GetPyPhonetic
@@ -39,3 +39,4 @@
     *bestFinal = 0;
-    while ((outputIndex <= 0xf) && (count != 0)) {
+    goto check_remaining;
+    do {
         initial[outputIndex] = 0;
@@ -266,3 +267,6 @@
         outputIndex++;
-    }
+        if (outputIndex > 0xf) break;
+check_remaining:
+        ;
+    } while (count != 0);
     if ((result > 1) && (text[*resultCount - 1] >= 0xF341) && (text[*resultCount - 1] <= 0xF35A)) {
```

### Zi8GetPyPhonetic attempt 4

zi8match Zi8GetPyPhonetic attempt 4: declare live character and input cursor before temporary conversion buffers; fuzzy 98.704735; src 0xb38 base 0xb38 insns 718/718; diffs 167: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetPyPhonetic
+++ attempt-4/Zi8GetPyPhonetic
@@ -8,7 +8,7 @@
     ziU8 outputIndex;
+    ziU16 value;
     ziU8 index;
-    ziU16 value;
+    ziWChar* current;
     ziWChar converted[256];
     ziU8 pinyin[12];
-    ziWChar* current;
 
@@ -39,3 +39,3 @@
     *bestFinal = 0;
-    while ((outputIndex <= 0xf) && (count != 0)) {
+    while (count != 0) {
         initial[outputIndex] = 0;
@@ -266,2 +266,3 @@
         outputIndex++;
+        if (outputIndex > 0xf) break;
     }
```

### Zi8GetKOcandidates attempt 1

zkokeyp Zi8GetKOcandidates attempt 1: postincrement byte scan cursor to avoid unused assignment-value narrowing; fuzzy 97.96712; src 0xa84 base 0xa74 insns 673/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetKOcandidates
+++ attempt-1/Zi8GetKOcandidates
@@ -204,3 +204,3 @@
                             (ziS32)search.keyByte < (int)param->elementCount / 2;
-                            search.keyByte = search.keyByte + 1) {
+                            search.keyByte++) {
                             if (search.packedKeys.bytes[search.keyByte] != search.entry->keyBytes[search.keyByte]) {
```

### Zi8GetKOcandidates attempt 2

zkokeyp Zi8GetKOcandidates attempt 2: assign packed prefix then suffix using a single zero-valued chain; fuzzy 97.96712; src 0xa84 base 0xa74 insns 673/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetKOcandidates
+++ attempt-2/Zi8GetKOcandidates
@@ -31,4 +31,3 @@
     search.resultCount = 0;
-    search.packedKeys.firstWord = 0;
-    search.packedKeys.bytes[4] = 0;
+    search.packedKeys.bytes[4] = search.packedKeys.firstWord = 0;
     search.remainingLetters = 0;
@@ -204,3 +203,3 @@
                             (ziS32)search.keyByte < (int)param->elementCount / 2;
-                            search.keyByte = search.keyByte + 1) {
+                            search.keyByte++) {
                             if (search.packedKeys.bytes[search.keyByte] != search.entry->keyBytes[search.keyByte]) {
```

### Zi8GetKOcandidates attempt 3

zkokeyp Zi8GetKOcandidates attempt 3: narrow final table character implicitly at candidate halfword store; fuzzy 97.96712; src 0xa84 base 0xa74 insns 673/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetKOcandidates
+++ attempt-3/Zi8GetKOcandidates
@@ -204,3 +204,3 @@
                             (ziS32)search.keyByte < (int)param->elementCount / 2;
-                            search.keyByte = search.keyByte + 1) {
+                            search.keyByte++) {
                             if (search.packedKeys.bytes[search.keyByte] != search.entry->keyBytes[search.keyByte]) {
@@ -236,3 +236,3 @@
                             param->candidates[search.candidateCount++] =
-                            (ziU16)((ziU16)((ZiKoreanKeyEntry*)(((search.tableIndex << 3) + search.tableIndex) + keyTable))->characterHigh << 8 |
+                            ((ziU16)((ZiKoreanKeyEntry*)(((search.tableIndex << 3) + search.tableIndex) + keyTable))->characterHigh << 8 |
                                 ((ZiKoreanKeyEntry*)(((search.tableIndex << 3) + search.tableIndex) + keyTable))->characterLow);
```

### Zi8GetKOcandidates attempt 4

zkokeyp Zi8GetKOcandidates attempt 4: reuse initialized key-byte cursor when entering multi-byte prefix scan; fuzzy 97.54111; src 0xa78 base 0xa74 insns 670/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetKOcandidates
+++ attempt-4/Zi8GetKOcandidates
@@ -202,5 +202,5 @@
                     if (1 < param->elementCount) {
-                        for (search.keyByte = 0;
+                        for (;
                             (ziS32)search.keyByte < (int)param->elementCount / 2;
-                            search.keyByte = search.keyByte + 1) {
+                            search.keyByte++) {
                             if (search.packedKeys.bytes[search.keyByte] != search.entry->keyBytes[search.keyByte]) {
```

### Zi8MatchPhonetic attempt 1

zi8match Zi8MatchPhonetic attempt 1: combine strict boundary rejection in one partial-mode condition; fuzzy 97.2011; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-1/Zi8MatchPhonetic
@@ -127,6 +127,5 @@
                     if (++traversal.partIndex == numParts) {
-                        if (partialMode != 0) {
-                            if (strictMode == 0 && (traversal.dictionaryIndex & 0x8000) != 0) goto phonetic_skip;
-                            if (strictMode != 0 && (traversal.dictionaryIndex & 0x8000) == 0) goto phonetic_skip;
-                        }
+                        if (partialMode != 0 &&
+                            ((strictMode == 0 && (traversal.dictionaryIndex & 0x8000) != 0) ||
+                             (strictMode != 0 && (traversal.dictionaryIndex & 0x8000) == 0))) goto phonetic_skip;
                         *resultNode = node;
```

### Zi8MatchPhonetic attempt 2

zi8match Zi8MatchPhonetic attempt 2: branch on strict mode once before checking dictionary boundary; fuzzy 96.421486; src 0x5ac base 0x5ac insns 363/363; diffs 104: [6, 7, 8, 82, 83, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 225, 227, 228, 229, 230]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-2/Zi8MatchPhonetic
@@ -128,4 +128,7 @@
                         if (partialMode != 0) {
-                            if (strictMode == 0 && (traversal.dictionaryIndex & 0x8000) != 0) goto phonetic_skip;
-                            if (strictMode != 0 && (traversal.dictionaryIndex & 0x8000) == 0) goto phonetic_skip;
+                            if (strictMode == 0) {
+                                if ((traversal.dictionaryIndex & 0x8000) != 0) goto phonetic_skip;
+                            } else {
+                                if ((traversal.dictionaryIndex & 0x8000) == 0) goto phonetic_skip;
+                            }
                         }
```

### Zi8MatchPhonetic attempt 3

zi8match Zi8MatchPhonetic attempt 3: decode sound offset with low byte before table-address high byte; fuzzy 97.09642; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-3/Zi8MatchPhonetic
@@ -56,3 +56,3 @@
         }
-        sound = (ziU8*)(tableAddress + node[0xA] * 0x100 + ((node[9] & 0xF) * 0x10000 + node[0xB]));
+        sound = (ziU8*)(((node[9] & 0xF) * 0x10000 + node[0xB]) + (tableAddress + node[0xA] * 0x100));
         if (ZI_WORK->unk_0x16 != 0) {
```

### Zi8PrepareMatch attempt 1

zprepare Zi8PrepareMatch attempt 1: advance phonetic input before subtracting the consumed final character; fuzzy 96.30532; src 0xeac base 0xeb0 insns 939/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8PrepareMatch
+++ attempt-1/Zi8PrepareMatch
@@ -281,3 +281,3 @@
           }
-          buffers.phoneticInput += phoneticLength - 1;
+          buffers.phoneticInput = buffers.phoneticInput + phoneticLength - 1;
           phoneticLength = 0;
```

### Zi8PrepareMatch attempt 2

zprepare Zi8PrepareMatch attempt 2: compare consumed element index first and use explicit segment capacity; fuzzy 96.319145; src 0xeac base 0xeb0 insns 939/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8PrepareMatch
+++ attempt-2/Zi8PrepareMatch
@@ -211,3 +211,3 @@
       match->nSeg++;
-      if (((stroke != 0xff) || (elementCount <= elementIndex)) || (0xf < match->nSeg)) goto complete;
+      if ((stroke != 0xff || elementIndex >= elementCount || match->nSeg >= 0x10)) goto complete;
       Zi8Memset(buffers.masks,0,0xc);
@@ -281,3 +281,3 @@
           }
-          buffers.phoneticInput += phoneticLength - 1;
+          buffers.phoneticInput = buffers.phoneticInput + phoneticLength - 1;
           phoneticLength = 0;
```

### Zi8PrepareMatch attempt 3

zprepare Zi8PrepareMatch attempt 3: restore initial phonetic before final phonetic in fallback arm; fuzzy 96.318085; src 0xeac base 0xeb0 insns 939/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8PrepareMatch
+++ attempt-3/Zi8PrepareMatch
@@ -211,3 +211,3 @@
       match->nSeg++;
-      if (((stroke != 0xff) || (elementCount <= elementIndex)) || (0xf < match->nSeg)) goto complete;
+      if ((stroke != 0xff || elementIndex >= elementCount || match->nSeg >= 0x10)) goto complete;
       Zi8Memset(buffers.masks,0,0xc);
@@ -274,4 +274,4 @@
             bestFinal = previousFinal;
+            initial = bestInitial;
             final = bestFinal;
-            initial = bestInitial;
             goto savePhonetic;
@@ -281,3 +281,3 @@
           }
-          buffers.phoneticInput += phoneticLength - 1;
+          buffers.phoneticInput = buffers.phoneticInput + phoneticLength - 1;
           phoneticLength = 0;
```

### Zi8_8148302C attempt 4

zkokeyp Zi8_8148302C attempt 4: name decoded character, table count and table index by their record roles; fuzzy 99.49152; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8_8148302C
+++ attempt-4/Zi8_8148302C
@@ -1,13 +1,13 @@
 ziU32 Zi8_8148302C(ziU16 key, ziU8* table ZI_NEED_WORK) {
-    ziU32 value;
-    ziU16 count;
-    ziU32 i;
+    ziU32 character;
+    ziU16 tableCount;
+    ziU32 tableIndex;
 
-    count = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
-    for (i = 0; (ziU16)i < count; i++) {
-        value = (ziU16)(((ziU16)table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 7] << 8) |
-                       table[((i & 0xFFFF) << 3) + (i & 0xFFFF) + 8]);
-        if (value == key) {
+    tableCount = Zi8GetTableCount(ZI8_LANG_KO, 9, ZI_WORK);
+    for (tableIndex = 0; (ziU16)tableIndex < tableCount; tableIndex++) {
+        character = (ziU16)(((ziU16)table[((tableIndex & 0xFFFF) << 3) + (tableIndex & 0xFFFF) + 7] << 8) |
+                       table[((tableIndex & 0xFFFF) << 3) + (tableIndex & 0xFFFF) + 8]);
+        if (character == key) {
             Zi8LogError(0x64, ZI_WORK);
-            return i;
+            return tableIndex;
         }
```

### Zi8MatchPhonetic attempt 4

zi8match Zi8MatchPhonetic attempt 4: branch from completed sound group to next node before repeating unfinished group; fuzzy 97.242424; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-4/Zi8MatchPhonetic
@@ -85,3 +85,4 @@
         }
-        do {
+next_group:
+        {
             traversal.nextCode = *sound++;
@@ -138,5 +139,5 @@
             }
-        } while ((traversal.nextCode & 0x80) == 0);
-
-        goto next_node;
+        }
+        if ((traversal.nextCode & 0x80) != 0) goto next_node;
+        goto next_group;
 check_code:
```

### Zi8MatchPhonetic attempt 5

zi8match Zi8MatchPhonetic attempt 5: use dictionary byte pointer and record-sized native array indexing at both node accesses; fuzzy 99.22314; src 0x5ac base 0x5ac insns 363/363; diffs 10: [111, 112, 113, 114, 115, 116, 117, 118, 119, 120]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-5/Zi8MatchPhonetic
@@ -1,2 +1,2 @@
-ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziPtr dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
+ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziU8* dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
     struct {
@@ -85,3 +85,4 @@
         }
-        do {
+next_group:
+        {
             traversal.nextCode = *sound++;
@@ -109,4 +110,4 @@
                     }
-                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, (ziU8*)&((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF]);
-                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF].header & 0x80) != 0) {
+                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, dictionary + (traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode));
+                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (dictionary[(traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode)] & 0x80) != 0) {
                         traversal.code = Zi8MatchAltSound(soundTable, soundCode, pCodeTable, traversal.dictionaryIndex & 0x7FFF, masks[traversal.partIndex], values[traversal.partIndex], flag, ZI_WORK);
@@ -138,5 +139,5 @@
             }
-        } while ((traversal.nextCode & 0x80) == 0);
-
-        goto next_node;
+        }
+        if ((traversal.nextCode & 0x80) != 0) goto next_node;
+        goto next_group;
 check_code:
```

### Zi8MatchPhonetic attempt 6

zi8match Zi8MatchPhonetic attempt 6: pair packed high and low offset bytes before adding table base and middle byte; fuzzy 99.1157; src 0x5ac base 0x5ac insns 363/363; diffs 8: [111, 114, 115, 116, 117, 118, 119, 120]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-6/Zi8MatchPhonetic
@@ -1,2 +1,2 @@
-ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziPtr dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
+ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziU8* dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
     struct {
@@ -56,3 +56,3 @@
         }
-        sound = (ziU8*)(tableAddress + node[0xA] * 0x100 + ((node[9] & 0xF) * 0x10000 + node[0xB]));
+        sound = (ziU8*)(((node[9] & 0xF) * 0x10000 + node[0xB]) + (tableAddress + node[0xA] * 0x100));
         if (ZI_WORK->unk_0x16 != 0) {
@@ -85,3 +85,4 @@
         }
-        do {
+next_group:
+        {
             traversal.nextCode = *sound++;
@@ -109,4 +110,4 @@
                     }
-                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, (ziU8*)&((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF]);
-                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF].header & 0x80) != 0) {
+                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, dictionary + (traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode));
+                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (dictionary[(traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode)] & 0x80) != 0) {
                         traversal.code = Zi8MatchAltSound(soundTable, soundCode, pCodeTable, traversal.dictionaryIndex & 0x7FFF, masks[traversal.partIndex], values[traversal.partIndex], flag, ZI_WORK);
@@ -138,5 +139,5 @@
             }
-        } while ((traversal.nextCode & 0x80) == 0);
-
-        goto next_node;
+        }
+        if ((traversal.nextCode & 0x80) != 0) goto next_node;
+        goto next_group;
 check_code:
```

### Zi8MatchPhonetic attempt 7

zi8match Zi8MatchPhonetic attempt 7: packed offset in original byte-read order, paired sums kept explicit; fuzzy 99.05785; src 0x5ac base 0x5ac insns 363/363; diffs 10: [111, 112, 113, 114, 115, 116, 117, 118, 119, 120]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-7/Zi8MatchPhonetic
@@ -1,2 +1,2 @@
-ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziPtr dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
+ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziU8* dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
     struct {
@@ -56,3 +56,3 @@
         }
-        sound = (ziU8*)(tableAddress + node[0xA] * 0x100 + ((node[9] & 0xF) * 0x10000 + node[0xB]));
+        sound = (ziU8*)((tableAddress + node[0xB] + (node[9] & 0xF) * 0x10000) + node[0xA] * 0x100);
         if (ZI_WORK->unk_0x16 != 0) {
@@ -85,3 +85,4 @@
         }
-        do {
+next_group:
+        {
             traversal.nextCode = *sound++;
@@ -109,4 +110,4 @@
                     }
-                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, (ziU8*)&((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF]);
-                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF].header & 0x80) != 0) {
+                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, dictionary + (traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode));
+                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (dictionary[(traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode)] & 0x80) != 0) {
                         traversal.code = Zi8MatchAltSound(soundTable, soundCode, pCodeTable, traversal.dictionaryIndex & 0x7FFF, masks[traversal.partIndex], values[traversal.partIndex], flag, ZI_WORK);
@@ -138,5 +139,5 @@
             }
-        } while ((traversal.nextCode & 0x80) == 0);
-
-        goto next_node;
+        }
+        if ((traversal.nextCode & 0x80) != 0) goto next_node;
+        goto next_group;
 check_code:
```

### Zi8MatchPhonetic attempt 8

zi8match Zi8MatchPhonetic attempt 8: typed halfword middle byte while adding packed high and low offset first; fuzzy 98.812675; src 0x5b0 base 0x5ac insns 364/363; --- replace mine 42:43 base 42:43; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-8/Zi8MatchPhonetic
@@ -1,2 +1,2 @@
-ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziPtr dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
+ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziU8* dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
     struct {
@@ -56,3 +56,3 @@
         }
-        sound = (ziU8*)(tableAddress + node[0xA] * 0x100 + ((node[9] & 0xF) * 0x10000 + node[0xB]));
+        sound = (ziU8*)(((node[9] & 0xF) * 0x10000 + node[0xB]) + (tableAddress + ((ziU16)node[0xA] << 8)));
         if (ZI_WORK->unk_0x16 != 0) {
@@ -85,3 +85,4 @@
         }
-        do {
+next_group:
+        {
             traversal.nextCode = *sound++;
@@ -109,4 +110,4 @@
                     }
-                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, (ziU8*)&((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF]);
-                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF].header & 0x80) != 0) {
+                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, dictionary + (traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode));
+                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (dictionary[(traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode)] & 0x80) != 0) {
                         traversal.code = Zi8MatchAltSound(soundTable, soundCode, pCodeTable, traversal.dictionaryIndex & 0x7FFF, masks[traversal.partIndex], values[traversal.partIndex], flag, ZI_WORK);
@@ -138,5 +139,5 @@
             }
-        } while ((traversal.nextCode & 0x80) == 0);
-
-        goto next_node;
+        }
+        if ((traversal.nextCode & 0x80) != 0) goto next_node;
+        goto next_group;
 check_code:
```

### Zi8MatchPhonetic attempt 9

zi8match Zi8MatchPhonetic attempt 9: retain low offset byte addition within table-relative middle-byte sum; fuzzy 99.421486; src 0x5ac base 0x5ac insns 363/363; diffs 5: [111, 112, 113, 114, 115]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-9/Zi8MatchPhonetic
@@ -1,2 +1,2 @@
-ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziPtr dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
+ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziU8* dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
     struct {
@@ -56,3 +56,3 @@
         }
-        sound = (ziU8*)(tableAddress + node[0xA] * 0x100 + ((node[9] & 0xF) * 0x10000 + node[0xB]));
+        sound = (ziU8*)((node[9] & 0xF) * 0x10000 + (node[0xB] + (tableAddress + node[0xA] * 0x100)));
         if (ZI_WORK->unk_0x16 != 0) {
@@ -85,3 +85,4 @@
         }
-        do {
+next_group:
+        {
             traversal.nextCode = *sound++;
@@ -109,4 +110,4 @@
                     }
-                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, (ziU8*)&((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF]);
-                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF].header & 0x80) != 0) {
+                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, dictionary + (traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode));
+                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (dictionary[(traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode)] & 0x80) != 0) {
                         traversal.code = Zi8MatchAltSound(soundTable, soundCode, pCodeTable, traversal.dictionaryIndex & 0x7FFF, masks[traversal.partIndex], values[traversal.partIndex], flag, ZI_WORK);
@@ -138,5 +139,5 @@
             }
-        } while ((traversal.nextCode & 0x80) == 0);
-
-        goto next_node;
+        }
+        if ((traversal.nextCode & 0x80) != 0) goto next_node;
+        goto next_group;
 check_code:
```

### Zi8MatchPhonetic attempt 10

zi8match Zi8MatchPhonetic attempt 10: sound address expression tableAddress + ((node[9] & 0xF) * 0x10000 + (node[0xB] + node[0xA] * 0x100)); fuzzy 100.0; src 0x5ac base 0x5ac insns 363/363; diffs 0: []; POOL IDENTICAL, no strings

```diff
--- initial/Zi8MatchPhonetic
+++ attempt-10/Zi8MatchPhonetic
@@ -1,2 +1,2 @@
-ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziPtr dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
+ziBool Zi8MatchPhonetic(ziPtr pCodeTable, ziU8* dictionary, ziPtr soundTable, ziU16 soundCode, ziU32 tableAddress, ziU8* node, ziU16* masks, ziU16* values, ziU16* count, ziU8** resultNode, ziU8** stringOffset, ziU8 partialMode, ziU8 strictMode, ziU8 numParts, ziU16 partMask, ziU16 partValue, ziU8 flag, ziU8 altMode, ziU16 initialCode, ziU16* resultCode, ziU8 lastMode ZI_NEED_WORK) {
     struct {
@@ -56,3 +56,3 @@
         }
-        sound = (ziU8*)(tableAddress + node[0xA] * 0x100 + ((node[9] & 0xF) * 0x10000 + node[0xB]));
+        sound = (ziU8*)(tableAddress + ((node[9] & 0xF) * 0x10000 + (node[0xB] + node[0xA] * 0x100)));
         if (ZI_WORK->unk_0x16 != 0) {
@@ -85,3 +85,4 @@
         }
-        do {
+next_group:
+        {
             traversal.nextCode = *sound++;
@@ -109,4 +110,4 @@
                     }
-                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, (ziU8*)&((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF]);
-                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (((DictionaryNode*)dictionary)[traversal.dictionaryIndex & 0x7FFF].header & 0x80) != 0) {
+                    traversal.code = Zi8GetPCode((ziU8*)pCodeTable, dictionary + (traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode));
+                    if (((traversal.code & masks[traversal.partIndex]) != values[traversal.partIndex]) && (altMode == 0) && (dictionary[(traversal.dictionaryIndex & 0x7FFF) * sizeof(DictionaryNode)] & 0x80) != 0) {
                         traversal.code = Zi8MatchAltSound(soundTable, soundCode, pCodeTable, traversal.dictionaryIndex & 0x7FFF, masks[traversal.partIndex], values[traversal.partIndex], flag, ZI_WORK);
@@ -138,5 +139,5 @@
             }
-        } while ((traversal.nextCode & 0x80) == 0);
-
-        goto next_node;
+        }
+        if ((traversal.nextCode & 0x80) != 0) goto next_node;
+        goto next_group;
 check_code:
```

### Zi8GetPyFinal attempt 4

zi8match Zi8GetPyFinal attempt 4: access phonetic output cells through the eight-byte final-table record; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings

```diff
--- initial/Zi8GetPyFinal
+++ attempt-4/Zi8GetPyFinal
@@ -1,2 +1,3 @@
 ziBool Zi8GetPyFinal(ziU8* pinyin, ziU8* initial, ziU8* final) {
+    typedef struct { ziU8 spelling[4]; ziU8 phonetic[4]; } PinyinFinal;
     ziU8 index = 0;
@@ -15,4 +16,4 @@
     }
-    *initial = Zi8PinyinFinals[row][4];
-    *final = Zi8PinyinFinals[row][5];
+    *initial = ((const PinyinFinal*)Zi8PinyinFinals)[row].phonetic[0];
+    *final = ((const PinyinFinal*)Zi8PinyinFinals)[row].phonetic[1];
     return 1;
```

### Zi8IsDupWChar attempt 4

zi8getc2 Zi8IsDupWChar attempt 4: keep duplicate scan cursor in engine-native unsigned word type; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)

```diff
--- initial/Zi8IsDupWChar
+++ attempt-4/Zi8IsDupWChar
@@ -3,3 +3,3 @@
     ziU16* buffer;
-    unsigned int index;
+    ziU32 index;
     duplicate = 0;
```

## zkokeyp exact remaining instruction differences

Initial and final raw ctxdiff for all six open functions, in address order. The register-normalized filter comparison below isolates the extra byte narrowing and two reversed add operands from the one-instruction shift in raw alignment.

### Zi8_8148302C

Initial:

```text
src 0xec base 0xec insns 59/59
diffs 6: [7, 12, 32, 34, 38, 49]
     7 M mr r27, r5
       B mr r29, r5
    12 M mr r5, r27
       B mr r5, r29
    32 M clrlwi r29, r0, 0x10
       B clrlwi r27, r0, 0x10
    34 M cmplw r29, r0
       B cmplw r27, r0
    38 M mr r4, r27
       B mr r4, r29
    49 M mr r4, r27
       B mr r4, r29
```

Final:

```text
src 0xec base 0xec insns 59/59
diffs 6: [7, 12, 32, 34, 38, 49]
     7 M mr r27, r5
       B mr r29, r5
    12 M mr r5, r27
       B mr r5, r29
    32 M clrlwi r29, r0, 0x10
       B clrlwi r27, r0, 0x10
    34 M cmplw r29, r0
       B cmplw r27, r0
    38 M mr r4, r27
       B mr r4, r29
    49 M mr r4, r27
       B mr r4, r29
```

### Zi8_81483264

Initial:

```text
src 0xa4 base 0xa4 insns 41/41
diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]
     6 M mr r30, r3
       B mr r31, r3
     8 M lwz r0, 0x24(r30)
       B lwz r0, 0x24(r31)
    17 M li r31, 0
       B li r30, 0
    20 M lwz r3, 0x24(r30)
       B lwz r3, 0x24(r31)
    21 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18
    24 M addi r31, r31, 1
       B addi r30, r30, 1
    25 M clrlwi r3, r31, 0x18
       B clrlwi r3, r30, 0x18
    26 M lbz r0, 0x1c(r30)
       B lbz r0, 0x1c(r31)
```

Final:

```text
src 0xa4 base 0xa4 insns 41/41
diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]
     6 M mr r30, r3
       B mr r31, r3
     8 M lwz r0, 0x24(r30)
       B lwz r0, 0x24(r31)
    17 M li r31, 0
       B li r30, 0
    20 M lwz r3, 0x24(r30)
       B lwz r3, 0x24(r31)
    21 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18
    24 M addi r31, r31, 1
       B addi r30, r30, 1
    25 M clrlwi r3, r31, 0x18
       B clrlwi r3, r30, 0x18
    26 M lbz r0, 0x1c(r30)
       B lbz r0, 0x1c(r31)
```

### Zi8_81483308

Initial:

```text
src 0xe8 base 0xe8 insns 58/58
diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]
     7 M mr r29, r5
       B mr r30, r5
    22 M li r30, 0
       B li r29, 0
    26 M clrlwi r0, r30, 0x18
       B clrlwi r0, r29, 0x18
    33 M addi r30, r30, 1
       B addi r29, r29, 1
    34 M clrlwi r3, r30, 0x18
       B clrlwi r3, r29, 0x18
    39 M lbz r0, 0(r29)
       B lbz r0, 0(r30)
    42 M lbz r3, 0(r29)
       B lbz r3, 0(r30)
    44 M stb r0, 0(r29)
       B stb r0, 0(r30)
    50 M stb r0, 0(r29)
       B stb r0, 0(r30)
```

Final:

```text
src 0xe8 base 0xe8 insns 58/58
diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]
     7 M mr r29, r5
       B mr r30, r5
    22 M li r30, 0
       B li r29, 0
    26 M clrlwi r0, r30, 0x18
       B clrlwi r0, r29, 0x18
    33 M addi r30, r30, 1
       B addi r29, r29, 1
    34 M clrlwi r3, r30, 0x18
       B clrlwi r3, r29, 0x18
    39 M lbz r0, 0(r29)
       B lbz r0, 0(r30)
    42 M lbz r3, 0(r29)
       B lbz r3, 0(r30)
    44 M stb r0, 0(r29)
       B stb r0, 0(r30)
    50 M stb r0, 0(r29)
       B stb r0, 0(r30)
```

### Zi8_814833F0

Initial:

```text
src 0xbc base 0xbc insns 47/47
diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]
     6 M mr r30, r3
       B mr r31, r3
    13 M lwz r0, 0x24(r30)
       B lwz r0, 0x24(r31)
    22 M li r31, 0
       B li r30, 0
    26 M lwz r3, 0x24(r30)
       B lwz r3, 0x24(r31)
    27 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18
    34 M addi r31, r31, 1
       B addi r30, r30, 1
    35 M clrlwi r3, r31, 0x18
       B clrlwi r3, r30, 0x18
    36 M lbz r0, 0x1c(r30)
       B lbz r0, 0x1c(r31)
```

Final:

```text
src 0xbc base 0xbc insns 47/47
diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]
     6 M mr r30, r3
       B mr r31, r3
    13 M lwz r0, 0x24(r30)
       B lwz r0, 0x24(r31)
    22 M li r31, 0
       B li r30, 0
    26 M lwz r3, 0x24(r30)
       B lwz r3, 0x24(r31)
    27 M clrlwi r0, r31, 0x18
       B clrlwi r0, r30, 0x18
    34 M addi r31, r31, 1
       B addi r30, r30, 1
    35 M clrlwi r3, r31, 0x18
       B clrlwi r3, r30, 0x18
    36 M lbz r0, 0x1c(r30)
       B lbz r0, 0x1c(r31)
```

### Zi8_814834AC

Initial:

```text
src 0x560 base 0x55c insns 344/343
--- replace mine 9:10 base 9:10
  M    9 mr r25, r7
  B    9 mr r26, r7
--- delete mine 16:17 base 16:16
  M   16 clrlwi r0, r0, 0x18
--- replace mine 20:21 base 19:20
  M   20 mr r4, r25
  B   19 mr r4, r26
--- replace mine 36:37 base 35:36
  M   36 mr r6, r25
  B   35 mr r6, r26
--- replace mine 57:58 base 56:57
  M   57 mr r6, r25
  B   56 mr r6, r26
--- replace mine 98:99 base 97:98
  M   98 mr r5, r25
  B   97 mr r5, r26
--- replace mine 104:105 base 103:104
  M  104 mr r5, r25
  B  103 mr r5, r26
--- replace mine 112:113 base 111:112
  M  112 mr r4, r25
  B  111 mr r4, r26
--- replace mine 121:122 base 120:121
  M  121 mr r4, r25
  B  120 mr r4, r26
--- replace mine 129:130 base 128:129
  M  129 mr r5, r25
  B  128 mr r5, r26
--- replace mine 205:206 base 204:205
  M  205 add r3, r4, r3
  B  204 add r3, r3, r4
--- replace mine 212:213 base 211:212
  M  212 add r3, r4, r3
  B  211 add r3, r3, r4
--- replace mine 250:251 base 249:250
  M  250 li r26, 0
  B  249 li r25, 0
--- replace mine 253:254 base 252:253
  M  253 slwi r0, r26, 1
  B  252 slwi r0, r25, 1
--- replace mine 259:260 base 258:259
  M  259 slwi r3, r26, 1
  B  258 slwi r3, r25, 1
--- replace mine 272:273 base 271:272
  M  272 slwi r0, r26, 1
  B  271 slwi r0, r25, 1
--- replace mine 275:276 base 274:275
  M  275 mr r6, r25
  B  274 mr r6, r26
--- replace mine 279:280 base 278:279
  M  279 cmpw r0, r26
  B  278 cmpw r0, r25
--- replace mine 282:283 base 281:282
  M  282 slwi r0, r26, 1
  B  281 slwi r0, r25, 1
--- replace mine 291:292 base 290:291
  M  291 addi r26, r26, 1
  B  290 addi r25, r25, 1
--- replace mine 293:294 base 292:293
  M  293 cmpw r26, r0
  B  292 cmpw r25, r0
--- replace mine 321:322 base 320:321
  M  321 mr r6, r25
  B  320 mr r6, r26
```

Final:

```text
src 0x560 base 0x55c insns 344/343
--- replace mine 9:10 base 9:10
  M    9 mr r25, r7
  B    9 mr r26, r7
--- delete mine 16:17 base 16:16
  M   16 clrlwi r0, r0, 0x18
--- replace mine 20:21 base 19:20
  M   20 mr r4, r25
  B   19 mr r4, r26
--- replace mine 36:37 base 35:36
  M   36 mr r6, r25
  B   35 mr r6, r26
--- replace mine 57:58 base 56:57
  M   57 mr r6, r25
  B   56 mr r6, r26
--- replace mine 98:99 base 97:98
  M   98 mr r5, r25
  B   97 mr r5, r26
--- replace mine 104:105 base 103:104
  M  104 mr r5, r25
  B  103 mr r5, r26
--- replace mine 112:113 base 111:112
  M  112 mr r4, r25
  B  111 mr r4, r26
--- replace mine 121:122 base 120:121
  M  121 mr r4, r25
  B  120 mr r4, r26
--- replace mine 129:130 base 128:129
  M  129 mr r5, r25
  B  128 mr r5, r26
--- replace mine 205:206 base 204:205
  M  205 add r3, r4, r3
  B  204 add r3, r3, r4
--- replace mine 212:213 base 211:212
  M  212 add r3, r4, r3
  B  211 add r3, r3, r4
--- replace mine 250:251 base 249:250
  M  250 li r26, 0
  B  249 li r25, 0
--- replace mine 253:254 base 252:253
  M  253 slwi r0, r26, 1
  B  252 slwi r0, r25, 1
--- replace mine 259:260 base 258:259
  M  259 slwi r3, r26, 1
  B  258 slwi r3, r25, 1
--- replace mine 272:273 base 271:272
  M  272 slwi r0, r26, 1
  B  271 slwi r0, r25, 1
--- replace mine 275:276 base 274:275
  M  275 mr r6, r25
  B  274 mr r6, r26
--- replace mine 279:280 base 278:279
  M  279 cmpw r0, r26
  B  278 cmpw r0, r25
--- replace mine 282:283 base 281:282
  M  282 slwi r0, r26, 1
  B  281 slwi r0, r25, 1
--- replace mine 291:292 base 290:291
  M  291 addi r26, r26, 1
  B  290 addi r25, r25, 1
--- replace mine 293:294 base 292:293
  M  293 cmpw r26, r0
  B  292 cmpw r25, r0
--- replace mine 321:322 base 320:321
  M  321 mr r6, r25
  B  320 mr r6, r26
```

### Zi8GetKOcandidates

Initial:

```text
src 0xa88 base 0xa74 insns 674/669
--- replace mine 11:13 base 11:13
  M   11 li r3, 0
  M   12 stw r3, 0x2c(r1)
  B   11 li r0, 0
  B   12 stw r0, 0x2c(r1)
--- replace mine 15:17 base 15:16
  M   15 li r3, 0
  M   16 stb r3, 0x3c(r1)
  B   15 stb r0, 0x3c(r1)
--- replace mine 29:31 base 28:30
  M   29 li r0, 0
  M   30 stw r0, 0x20(r1)
  B   28 li r3, 0
  B   29 stw r3, 0x20(r1)
--- replace mine 61:64 base 60:63
  M   61 b 2428
  M   62 lwz r0, 0x34(r1)
  M   63 cmpwi r0, 0
  B   60 b 2412
  B   61 lwz r4, 0x34(r1)
  B   62 cmpwi r4, 0
--- replace mine 70:71 base 69:70
  M   70 b 2392
  B   69 b 2376
--- replace mine 76:78 base 75:77
  M   76 li r3, 0
  M   77 stb r3, 0x20(r31)
  B   75 li r0, 0
  B   76 stb r0, 0x20(r31)
--- replace mine 87:88 base 86:87
  M   87 beq 1388
  B   86 beq 1496
--- replace mine 93:103 base 92:101
  M   93 clrlwi r0, r3, 0x10
  M   94 sth r0, 0x18(r1)
  M   95 clrlwi r0, r0, 0x10
  M   96 cmplwi r0, 0xffff
  M   97 beq 1348
  M   98 lhz r3, 0x18(r1)
  M   99 slwi r0, r3, 3
  M  100 lhz r5, 0x18(r1)
  M  101 add r4, r28, r0
  M  102 add r3, r5, r4
  B   92 sth r3, 0x18(r1)
  B   93 clrlwi r5, r3, 0x10
  B   94 cmplwi r5, 0xffff
  B   95 beq 1344
  B   96 lhz r4, 0x18(r1)
  B   97 slwi r3, r4, 3
  B   98 lhz r0, 0x18(r1)
  B   99 add r0, r3, r0
  B  100 add r3, r0, r28
--- replace mine 104:121 base 102:105
  M  104 rlwinm r0, r0, 0, 0x1c, 0x1c
  M  105 cmpwi r0, 0
  M  106 beq 1312
  M  107 lhz r3, 0x18(r1)
  M  108 slwi r3, r3, 3
  M  109 lhz r0, 0x18(r1)
  M  110 add r4, r28, r3
  M  111 add r3, r0, r4
  M  112 lbz r6, 6(r3)
  M  113 lhz r0, 0x18(r1)
  M  114 slwi r0, r0, 3
  M  115 lhz r3, 0x18(r1)
  M  116 add r0, r28, r0
  M  117 add r3, r3, r0
  M  118 lbz r3, 4(r3)
  M  119 clrlwi r0, r3, 0x1e
  M  120 slwi r5, r0, 0x10
  B  102 rlwinm r4, r0, 0, 0x1c, 0x1c
  B  103 cmpwi r4, 0
  B  104 beq 1308
--- replace mine 124:126 base 108:124
  M  124 add r4, r28, r3
  M  125 add r3, r0, r4
  B  108 add r0, r3, r0
  B  109 add r3, r0, r28
  B  110 lbz r6, 6(r3)
  B  111 lhz r0, 0x18(r1)
  B  112 slwi r3, r0, 3
  B  113 lhz r0, 0x18(r1)
  B  114 add r0, r3, r0
  B  115 add r4, r0, r28
  B  116 lbz r3, 4(r4)
  B  117 clrlwi r0, r3, 0x1e
  B  118 slwi r5, r0, 0x10
  B  119 lhz r4, 0x18(r1)
  B  120 slwi r3, r4, 3
  B  121 lhz r0, 0x18(r1)
  B  122 add r0, r3, r0
  B  123 add r3, r0, r28
--- replace mine 129:131 base 127:129
  M  129 or r0, r6, r0
  M  130 stw r0, 0x28(r1)
  B  127 or r4, r6, r0
  B  128 stw r4, 0x28(r1)
--- replace mine 133:137 base 131:135
  M  133 clrlwi r0, r0, 0x18
  M  134 stb r0, 0xe(r1)
  M  135 li r4, 1
  M  136 stb r4, 0xd(r1)
  B  131 clrlwi r3, r0, 0x18
  B  132 stb r3, 0xe(r1)
  B  133 li r0, 1
  B  134 stb r0, 0xd(r1)
--- replace mine 140:141 base 138:139
  M  140 b 184
  B  138 b 180
--- replace mine 148:150 base 146:147
  M  148 clrlwi r0, r3, 0x10
  M  149 sth r0, 0x18(r1)
  B  146 sth r3, 0x18(r1)
--- replace mine 152:154 base 149:151
  M  152 clrlwi r3, r0, 0x10
  M  153 clrlwi r0, r3, 0x1b
  B  149 clrlwi r0, r0, 0x10
  B  150 clrlwi r0, r0, 0x1b
--- replace mine 157:159 base 154:156
  M  157 or r0, r3, r0
  M  158 cmpw r4, r0
  B  154 or r3, r3, r0
  B  155 cmpw r4, r3
--- replace mine 164:166 base 161:163
  M  164 addi r0, r3, 1
  M  165 stb r0, 0xd(r1)
  B  161 addi r3, r3, 1
  B  162 stb r3, 0xd(r1)
--- replace mine 167:169 base 164:166
  M  167 rlwinm r3, r0, 0, 0x19, 0x19
  M  168 cmpwi r3, 0
  B  164 rlwinm r0, r0, 0, 0x19, 0x19
  B  165 cmpwi r0, 0
--- replace mine 182:184 base 179:181
  M  182 addi r3, r3, -1
  M  183 clrlwi r0, r3, 0x18
  B  179 addi r4, r3, -1
  B  180 clrlwi r0, r4, 0x18
--- insert mine 186:186 base 183:186
  B  183 lbz r3, 0xe(r1)
  B  184 cmpwi r3, 0
  B  185 bne -184
--- delete mine 188:191 base 188:188
  M  188 bne -188
  M  189 lbz r4, 0xe(r1)
  M  190 cmpwi r4, 0
--- replace mine 193:202 base 190:197
  M  193 clrlwi r0, r0, 0x10
  M  194 clrlwi r3, r0, 0x1b
  M  195 slwi r0, r3, 8
  M  196 lbz r3, 1(r29)
  M  197 or r0, r0, r3
  M  198 clrlwi r0, r0, 0x10
  M  199 sth r0, 0x18(r1)
  M  200 lhz r5, 0x18(r1)
  M  201 slwi r4, r5, 3
  B  190 clrlwi r3, r0, 0x10
  B  191 clrlwi r0, r3, 0x1b
  B  192 slwi r0, r0, 8
  B  193 lbz r5, 1(r29)
  B  194 or r4, r0, r5
  B  195 clrlwi r3, r4, 0x10
  B  196 sth r3, 0x18(r1)
--- replace mine 203:205 base 198:202
  M  203 add r0, r28, r4
  M  204 add r3, r3, r0
  B  198 slwi r3, r3, 3
  B  199 lhz r0, 0x18(r1)
  B  200 add r0, r3, r0
  B  201 add r3, r0, r28
--- replace mine 208:217 base 205:214
  M  208 lhz r0, 0x18(r1)
  M  209 slwi r3, r0, 3
  M  210 lhz r0, 0x18(r1)
  M  211 add r3, r28, r3
  M  212 add r3, r0, r3
  M  213 lbz r3, 8(r3)
  M  214 or r0, r4, r3
  M  215 clrlwi r3, r0, 0x10
  M  216 sth r3, 0x14(r1)
  B  205 lhz r3, 0x18(r1)
  B  206 slwi r0, r3, 3
  B  207 lhz r3, 0x18(r1)
  B  208 add r0, r0, r3
  B  209 add r3, r0, r28
  B  210 lbz r0, 8(r3)
  B  211 or r0, r4, r0
  B  212 clrlwi r0, r0, 0x10
  B  213 sth r0, 0x14(r1)
--- replace mine 261:262 base 258:259
  M  261 b 1628
  B  258 b 1620
--- replace mine 281:282 base 278:279
  M  281 b 1548
  B  278 b 1540
--- replace mine 326:327 base 323:324
  M  326 b 1368
  B  323 b 1360
--- replace mine 335:336 base 332:333
  M  335 b 1332
  B  332 b 1324
--- replace mine 408:409 base 405:406
  M  408 b 1040
  B  405 b 1032
--- replace mine 417:418 base 414:415
  M  417 b 1004
  B  414 b 996
--- replace mine 445:447 base 442:444
  M  445 lbz r3, 0(r30)
  M  446 cmpwi r3, 0
  B  442 lbz r0, 0(r30)
  B  443 cmpwi r0, 0
--- replace mine 456:459 base 453:456
  M  456 b 848
  M  457 lwz r0, 0x24(r1)
  M  458 stw r0, 0x2c(r1)
  B  453 b 840
  B  454 lwz r3, 0x24(r1)
  B  455 stw r3, 0x2c(r1)
--- replace mine 469:470 base 466:467
  M  469 b 796
  B  466 b 788
--- replace mine 476:478 base 473:475
  M  476 li r3, 0
  M  477 stb r3, 0xa(r1)
  B  473 li r0, 0
  B  474 stb r0, 0xa(r1)
--- replace mine 479:481 base 476:478
  M  479 li r3, 1
  M  480 stb r3, 0xa(r1)
  B  476 li r0, 1
  B  477 stb r0, 0xa(r1)
--- replace mine 493:501 base 490:498
  M  493 b 636
  M  494 li r0, 1
  M  495 stb r0, 8(r1)
  M  496 lwz r0, 0x30(r1)
  M  497 slwi r3, r0, 3
  M  498 lwz r0, 0x30(r1)
  M  499 add r3, r28, r3
  M  500 add r0, r0, r3
  B  490 b 628
  B  491 li r3, 1
  B  492 stb r3, 8(r1)
  B  493 lwz r3, 0x30(r1)
  B  494 slwi r3, r3, 3
  B  495 lwz r4, 0x30(r1)
  B  496 add r0, r28, r3
  B  497 add r0, r4, r0
--- insert mine 502:502 base 499:504
  B  499 li r0, 0
  B  500 stb r0, 0xb(r1)
  B  501 lbz r0, 0xc(r31)
  B  502 cmplwi r0, 1
  B  503 ble 104
--- replace mine 504:510 base 506:507
  M  504 lbz r3, 0xc(r31)
  M  505 cmplwi r3, 1
  M  506 ble 108
  M  507 li r0, 0
  M  508 stb r0, 0xb(r1)
  M  509 b 68
  B  506 b 64
--- replace mine 512:514 base 509:511
  M  512 lbzx r0, r3, r0
  M  513 clrlwi r5, r0, 0x18
  B  509 lbzx r3, r3, r0
  B  510 clrlwi r5, r3, 0x18
--- replace mine 521:522 base 518:519
  M  521 b 48
  B  518 b 44
--- replace mine 523:525 base 520:521
  M  523 addi r3, r3, 1
  M  524 clrlwi r0, r3, 0x18
  B  520 addi r0, r3, 1
--- replace mine 527:530 base 523:526
  M  527 lbz r3, 0xc(r31)
  M  528 srwi r6, r3, 0x1f
  M  529 add r0, r6, r3
  B  523 lbz r0, 0xc(r31)
  B  524 srwi r3, r0, 0x1f
  B  525 add r0, r3, r0
--- replace mine 532:533 base 528:529
  M  532 blt -88
  B  528 blt -84
--- replace mine 536:542 base 532:538
  M  536 lbz r0, 0xc(r31)
  M  537 srwi r3, r0, 0x1f
  M  538 clrlwi r0, r0, 0x1f
  M  539 xor r5, r0, r3
  M  540 subf r3, r3, r5
  M  541 cmpwi r3, 0
  B  532 lbz r6, 0xc(r31)
  B  533 srwi r3, r6, 0x1f
  B  534 clrlwi r0, r6, 0x1f
  B  535 xor r0, r0, r3
  B  536 subf r0, r3, r0
  B  537 cmpwi r0, 0
--- replace mine 543:544 base 539:540
  M  543 lbz r0, 0xb(r1)
  B  539 lbz r4, 0xb(r1)
--- replace mine 545:550 base 541:546
  M  545 lbzx r0, r3, r0
  M  546 rlwinm r4, r0, 0, 0x18, 0x1b
  M  547 lwz r3, 0x1c(r1)
  M  548 lbz r0, 0xb(r1)
  M  549 lbzx r0, r3, r0
  B  541 lbzx r0, r3, r4
  B  542 rlwinm r5, r0, 0, 0x18, 0x1b
  B  543 lwz r4, 0x1c(r1)
  B  544 lbz r3, 0xb(r1)
  B  545 lbzx r0, r4, r3
--- replace mine 551:552 base 547:548
  M  551 cmpw r4, r0
  B  547 cmpw r5, r0
--- replace mine 553:558 base 549:554
  M  553 li r0, 0
  M  554 stb r0, 8(r1)
  M  555 lbz r3, 8(r1)
  M  556 cmpwi r3, 0
  M  557 beq 368
  B  549 li r3, 0
  B  550 stb r3, 8(r1)
  B  551 lbz r0, 8(r1)
  B  552 cmpwi r0, 0
  B  553 beq 364
--- replace mine 567:569 base 563:568
  M  567 lbzx r0, r3, r0
  M  568 clrlwi r3, r0, 0x1c
  B  563 lbzx r3, r3, r0
  B  564 clrlwi r0, r3, 0x1c
  B  565 cmpwi r0, 0
  B  566 beq 20
  B  567 lbz r3, 0xa(r1)
--- replace mine 570:571 base 569:571
  M  570 beq 20
  B  569 beq 300
  B  570 b 96
--- delete mine 573:577 base 573:573
  M  573 beq 304
  M  574 b 96
  M  575 lbz r4, 0xa(r1)
  M  576 cmpwi r4, 0
--- replace mine 580:581 base 576:577
  M  580 beq 276
  B  576 beq 272
--- replace mine 583:586 base 579:582
  M  583 lbz r0, 0xb(r1)
  M  584 lbzx r3, r3, r0
  M  585 rlwinm r0, r3, 0, 0x18, 0x1b
  B  579 lbz r4, 0xb(r1)
  B  580 lbzx r0, r3, r4
  B  581 rlwinm r0, r0, 0, 0x18, 0x1b
--- replace mine 590:591 base 586:587
  M  590 beq 236
  B  586 beq 232
--- replace mine 592:593 base 588:592
  M  592 lbz r0, 0xa(r1)
  B  588 lbz r3, 0xa(r1)
  B  589 cmpwi r3, 0
  B  590 beq 16
  B  591 lbz r0, 0(r30)
--- replace mine 594:598 base 593:594
  M  594 beq 16
  M  595 lbz r3, 0(r30)
  M  596 cmpwi r3, 0
  M  597 beq 208
  B  593 beq 204
--- replace mine 602:605 base 598:601
  M  602 addi r0, r3, -1
  M  603 sth r0, 0x10(r1)
  M  604 b 180
  B  598 addi r3, r3, -1
  B  599 sth r3, 0x10(r1)
  B  600 b 176
--- replace mine 613:614 base 609:610
  M  613 blt 144
  B  609 blt 140
--- replace mine 615:616 base 611:612
  M  615 b 212
  B  611 b 208
--- replace mine 619:621 base 615:617
  M  619 add r3, r28, r3
  M  620 add r3, r0, r3
  B  615 add r0, r3, r0
  B  616 add r3, r0, r28
--- replace mine 622:624 base 618:620
  M  622 clrlwi r0, r0, 0x10
  M  623 slwi r4, r0, 8
  B  618 clrlwi r3, r0, 0x10
  B  619 slwi r4, r3, 8
--- replace mine 625:629 base 621:625
  M  625 slwi r0, r0, 3
  M  626 lwz r3, 0x30(r1)
  M  627 add r0, r28, r0
  M  628 add r3, r3, r0
  B  621 slwi r3, r0, 3
  B  622 lwz r0, 0x30(r1)
  B  623 add r0, r3, r0
  B  624 add r3, r0, r28
--- replace mine 634:636 base 630:631
  M  634 mr r0, r3
  M  635 clrlwi r0, r0, 0x18
  B  630 clrlwi r0, r3, 0x18
--- replace mine 640:642 base 635:637
  M  640 lbz r4, 0x21(r31)
  M  641 addi r0, r4, 1
  B  635 lbz r3, 0x21(r31)
  B  636 addi r0, r3, 1
--- replace mine 643:646 base 638:641
  M  643 clrlwi r3, r0, 0x18
  M  644 lbz r0, 0x1c(r31)
  M  645 cmplw r3, r0
  B  638 clrlwi r0, r0, 0x18
  B  639 lbz r4, 0x1c(r31)
  B  640 cmplw r0, r4
--- replace mine 650:652 base 645:647
  M  650 addi r3, r3, 1
  M  651 stw r3, 0x30(r1)
  B  645 addi r0, r3, 1
  B  646 stw r0, 0x30(r1)
--- replace mine 655:656 base 650:651
  M  655 blt -644
  B  650 blt -636
--- replace mine 661:664 base 656:659
  M  661 blt -680
  M  662 lbz r3, 0(r30)
  M  663 cmpwi r3, 0
  B  656 blt -672
  B  657 lbz r0, 0(r30)
  B  658 cmpwi r0, 0
```

Final:

```text
src 0xa84 base 0xa74 insns 673/669
--- replace mine 11:13 base 11:13
  M   11 li r3, 0
  M   12 stw r3, 0x2c(r1)
  B   11 li r0, 0
  B   12 stw r0, 0x2c(r1)
--- replace mine 15:17 base 15:16
  M   15 li r3, 0
  M   16 stb r3, 0x3c(r1)
  B   15 stb r0, 0x3c(r1)
--- replace mine 29:31 base 28:30
  M   29 li r0, 0
  M   30 stw r0, 0x20(r1)
  B   28 li r3, 0
  B   29 stw r3, 0x20(r1)
--- replace mine 61:64 base 60:63
  M   61 b 2424
  M   62 lwz r0, 0x34(r1)
  M   63 cmpwi r0, 0
  B   60 b 2412
  B   61 lwz r4, 0x34(r1)
  B   62 cmpwi r4, 0
--- replace mine 70:71 base 69:70
  M   70 b 2388
  B   69 b 2376
--- replace mine 76:78 base 75:77
  M   76 li r3, 0
  M   77 stb r3, 0x20(r31)
  B   75 li r0, 0
  B   76 stb r0, 0x20(r31)
--- replace mine 87:88 base 86:87
  M   87 beq 1388
  B   86 beq 1496
--- replace mine 93:103 base 92:101
  M   93 clrlwi r0, r3, 0x10
  M   94 sth r0, 0x18(r1)
  M   95 clrlwi r0, r0, 0x10
  M   96 cmplwi r0, 0xffff
  M   97 beq 1348
  M   98 lhz r3, 0x18(r1)
  M   99 slwi r0, r3, 3
  M  100 lhz r5, 0x18(r1)
  M  101 add r4, r28, r0
  M  102 add r3, r5, r4
  B   92 sth r3, 0x18(r1)
  B   93 clrlwi r5, r3, 0x10
  B   94 cmplwi r5, 0xffff
  B   95 beq 1344
  B   96 lhz r4, 0x18(r1)
  B   97 slwi r3, r4, 3
  B   98 lhz r0, 0x18(r1)
  B   99 add r0, r3, r0
  B  100 add r3, r0, r28
--- replace mine 104:109 base 102:119
  M  104 rlwinm r0, r0, 0, 0x1c, 0x1c
  M  105 cmpwi r0, 0
  M  106 beq 1312
  M  107 lhz r3, 0x18(r1)
  M  108 slwi r0, r3, 3
  B  102 rlwinm r4, r0, 0, 0x1c, 0x1c
  B  103 cmpwi r4, 0
  B  104 beq 1308
  B  105 lhz r0, 0x18(r1)
  B  106 slwi r3, r0, 3
  B  107 lhz r0, 0x18(r1)
  B  108 add r0, r3, r0
  B  109 add r3, r0, r28
  B  110 lbz r6, 6(r3)
  B  111 lhz r0, 0x18(r1)
  B  112 slwi r3, r0, 3
  B  113 lhz r0, 0x18(r1)
  B  114 add r0, r3, r0
  B  115 add r4, r0, r28
  B  116 lbz r3, 4(r4)
  B  117 clrlwi r0, r3, 0x1e
  B  118 slwi r5, r0, 0x10
--- replace mine 110:113 base 120:121
  M  110 add r0, r28, r0
  M  111 add r3, r4, r0
  M  112 lbz r7, 6(r3)
  B  120 slwi r3, r4, 3
--- replace mine 114:126 base 122:124
  M  114 slwi r0, r0, 3
  M  115 lhz r4, 0x18(r1)
  M  116 add r0, r28, r0
  M  117 add r3, r4, r0
  M  118 lbz r0, 4(r3)
  M  119 clrlwi r0, r0, 0x1e
  M  120 slwi r6, r0, 0x10
  M  121 lhz r3, 0x18(r1)
  M  122 slwi r0, r3, 3
  M  123 lhz r5, 0x18(r1)
  M  124 add r4, r28, r0
  M  125 add r3, r5, r4
  B  122 add r0, r3, r0
  B  123 add r3, r0, r28
--- replace mine 128:133 base 126:131
  M  128 or r0, r6, r0
  M  129 or r0, r7, r0
  M  130 stw r0, 0x28(r1)
  M  131 lbz r4, 0x14(r31)
  M  132 addi r0, r4, -1
  B  126 or r0, r5, r0
  B  127 or r4, r6, r0
  B  128 stw r4, 0x28(r1)
  B  129 lbz r3, 0x14(r31)
  B  130 addi r0, r3, -1
--- replace mine 137:141 base 135:139
  M  137 lwz r0, 0x34(r1)
  M  138 lwz r4, 0x28(r1)
  M  139 add r29, r0, r4
  M  140 b 184
  B  135 lwz r3, 0x34(r1)
  B  136 lwz r0, 0x28(r1)
  B  137 add r29, r3, r0
  B  138 b 180
--- replace mine 148:150 base 146:147
  M  148 clrlwi r0, r3, 0x10
  M  149 sth r0, 0x18(r1)
  B  146 sth r3, 0x18(r1)
--- replace mine 151:153 base 148:150
  M  151 lbz r3, 0(r29)
  M  152 clrlwi r0, r3, 0x10
  B  148 lbz r0, 0(r29)
  B  149 clrlwi r0, r0, 0x10
--- replace mine 157:159 base 154:156
  M  157 or r0, r3, r0
  M  158 cmpw r4, r0
  B  154 or r3, r3, r0
  B  155 cmpw r4, r3
--- replace mine 161:163 base 158:160
  M  161 addi r3, r3, -1
  M  162 stb r3, 0xe(r1)
  B  158 addi r0, r3, -1
  B  159 stb r0, 0xe(r1)
--- replace mine 164:168 base 161:165
  M  164 addi r0, r3, 1
  M  165 stb r0, 0xd(r1)
  M  166 lbz r3, 0(r29)
  M  167 rlwinm r0, r3, 0, 0x19, 0x19
  B  161 addi r3, r3, 1
  B  162 stb r3, 0xd(r1)
  B  163 lbz r0, 0(r29)
  B  164 rlwinm r0, r0, 0, 0x19, 0x19
--- replace mine 182:184 base 179:181
  M  182 addi r0, r3, -1
  M  183 clrlwi r0, r0, 0x18
  B  179 addi r4, r3, -1
  B  180 clrlwi r0, r4, 0x18
--- replace mine 186:189 base 183:186
  M  186 lbz r4, 0xe(r1)
  M  187 cmpwi r4, 0
  M  188 bne -188
  B  183 lbz r3, 0xe(r1)
  B  184 cmpwi r3, 0
  B  185 bne -184
--- replace mine 195:202 base 192:197
  M  195 slwi r3, r0, 8
  M  196 lbz r0, 1(r29)
  M  197 or r0, r3, r0
  M  198 clrlwi r6, r0, 0x10
  M  199 sth r6, 0x18(r1)
  M  200 lhz r5, 0x18(r1)
  M  201 slwi r4, r5, 3
  B  192 slwi r0, r0, 8
  B  193 lbz r5, 1(r29)
  B  194 or r4, r0, r5
  B  195 clrlwi r3, r4, 0x10
  B  196 sth r3, 0x18(r1)
--- replace mine 203:205 base 198:202
  M  203 add r0, r28, r4
  M  204 add r3, r3, r0
  B  198 slwi r3, r3, 3
  B  199 lhz r0, 0x18(r1)
  B  200 add r0, r3, r0
  B  201 add r3, r0, r28
--- replace mine 206:208 base 203:205
  M  206 clrlwi r3, r0, 0x10
  M  207 slwi r4, r3, 8
  B  203 clrlwi r0, r0, 0x10
  B  204 slwi r4, r0, 8
--- replace mine 211:213 base 208:210
  M  211 add r0, r28, r0
  M  212 add r3, r3, r0
  B  208 add r0, r0, r3
  B  209 add r3, r0, r28
--- replace mine 214:216 base 211:213
  M  214 or r3, r4, r0
  M  215 clrlwi r0, r3, 0x10
  B  211 or r0, r4, r0
  B  212 clrlwi r0, r0, 0x10
--- replace mine 261:262 base 258:259
  M  261 b 1624
  B  258 b 1620
--- replace mine 281:282 base 278:279
  M  281 b 1544
  B  278 b 1540
--- replace mine 326:327 base 323:324
  M  326 b 1364
  B  323 b 1360
--- replace mine 335:336 base 332:333
  M  335 b 1328
  B  332 b 1324
--- replace mine 408:409 base 405:406
  M  408 b 1036
  B  405 b 1032
--- replace mine 417:418 base 414:415
  M  417 b 1000
  B  414 b 996
--- replace mine 445:447 base 442:444
  M  445 lbz r3, 0(r30)
  M  446 cmpwi r3, 0
  B  442 lbz r0, 0(r30)
  B  443 cmpwi r0, 0
--- replace mine 456:459 base 453:456
  M  456 b 844
  M  457 lwz r0, 0x24(r1)
  M  458 stw r0, 0x2c(r1)
  B  453 b 840
  B  454 lwz r3, 0x24(r1)
  B  455 stw r3, 0x2c(r1)
--- replace mine 469:470 base 466:467
  M  469 b 792
  B  466 b 788
--- replace mine 476:478 base 473:475
  M  476 li r3, 0
  M  477 stb r3, 0xa(r1)
  B  473 li r0, 0
  B  474 stb r0, 0xa(r1)
--- replace mine 479:481 base 476:478
  M  479 li r3, 1
  M  480 stb r3, 0xa(r1)
  B  476 li r0, 1
  B  477 stb r0, 0xa(r1)
--- replace mine 493:501 base 490:498
  M  493 b 632
  M  494 li r0, 1
  M  495 stb r0, 8(r1)
  M  496 lwz r0, 0x30(r1)
  M  497 slwi r3, r0, 3
  M  498 lwz r0, 0x30(r1)
  M  499 add r3, r28, r3
  M  500 add r0, r0, r3
  B  490 b 628
  B  491 li r3, 1
  B  492 stb r3, 8(r1)
  B  493 lwz r3, 0x30(r1)
  B  494 slwi r3, r3, 3
  B  495 lwz r4, 0x30(r1)
  B  496 add r0, r28, r3
  B  497 add r0, r4, r0
--- insert mine 502:502 base 499:504
  B  499 li r0, 0
  B  500 stb r0, 0xb(r1)
  B  501 lbz r0, 0xc(r31)
  B  502 cmplwi r0, 1
  B  503 ble 104
--- delete mine 504:509 base 506:506
  M  504 lbz r3, 0xc(r31)
  M  505 cmplwi r3, 1
  M  506 ble 104
  M  507 li r0, 0
  M  508 stb r0, 0xb(r1)
--- replace mine 512:514 base 509:511
  M  512 lbzx r0, r3, r0
  M  513 clrlwi r5, r0, 0x18
  B  509 lbzx r3, r3, r0
  B  510 clrlwi r5, r3, 0x18
--- replace mine 528:530 base 525:527
  M  528 add r7, r3, r0
  M  529 srawi r0, r7, 1
  B  525 add r0, r3, r0
  B  526 srawi r0, r0, 1
--- replace mine 532:534 base 529:531
  M  532 lbz r0, 8(r1)
  M  533 cmpwi r0, 0
  B  529 lbz r3, 8(r1)
  B  530 cmpwi r3, 0
--- replace mine 535:538 base 532:535
  M  535 lbz r4, 0xc(r31)
  M  536 srwi r3, r4, 0x1f
  M  537 clrlwi r0, r4, 0x1f
  B  532 lbz r6, 0xc(r31)
  B  533 srwi r3, r6, 0x1f
  B  534 clrlwi r0, r6, 0x1f
--- replace mine 542:543 base 539:540
  M  542 lbz r6, 0xb(r1)
  B  539 lbz r4, 0xb(r1)
--- replace mine 544:545 base 541:542
  M  544 lbzx r0, r3, r6
  B  541 lbzx r0, r3, r4
--- replace mine 552:554 base 549:551
  M  552 li r0, 0
  M  553 stb r0, 8(r1)
  B  549 li r3, 0
  B  550 stb r3, 8(r1)
--- replace mine 556:562 base 553:559
  M  556 beq 368
  M  557 lbz r4, 0xc(r31)
  M  558 srwi r3, r4, 0x1f
  M  559 clrlwi r0, r4, 0x1f
  M  560 xor r0, r0, r3
  M  561 subf r0, r3, r0
  B  553 beq 364
  B  554 lbz r0, 0xc(r31)
  B  555 srwi r4, r0, 0x1f
  B  556 clrlwi r3, r0, 0x1f
  B  557 xor r0, r3, r4
  B  558 subf r0, r4, r0
--- replace mine 564:568 base 561:565
  M  564 lwz r4, 0x1c(r1)
  M  565 lbz r3, 0xb(r1)
  M  566 lbzx r0, r4, r3
  M  567 clrlwi r0, r0, 0x1c
  B  561 lwz r3, 0x1c(r1)
  B  562 lbz r0, 0xb(r1)
  B  563 lbzx r3, r3, r0
  B  564 clrlwi r0, r3, 0x1c
--- replace mine 572:573 base 569:570
  M  572 beq 304
  B  569 beq 300
--- replace mine 577:580 base 574:577
  M  577 lbz r4, 0(r30)
  M  578 cmpwi r4, 0
  M  579 beq 276
  B  574 lbz r0, 0(r30)
  B  575 cmpwi r0, 0
  B  576 beq 272
--- replace mine 582:586 base 579:583
  M  582 lbz r0, 0xb(r1)
  M  583 lbzx r0, r3, r0
  M  584 rlwinm r3, r0, 0, 0x18, 0x1b
  M  585 cmpwi r3, 0
  B  579 lbz r4, 0xb(r1)
  B  580 lbzx r0, r3, r4
  B  581 rlwinm r0, r0, 0, 0x18, 0x1b
  B  582 cmpwi r0, 0
--- replace mine 589:590 base 586:587
  M  589 beq 236
  B  586 beq 232
--- replace mine 591:593 base 588:590
  M  591 lbz r0, 0xa(r1)
  M  592 cmpwi r0, 0
  B  588 lbz r3, 0xa(r1)
  B  589 cmpwi r3, 0
--- replace mine 596:599 base 593:596
  M  596 beq 208
  M  597 lhz r3, 0x10(r1)
  M  598 cmpwi r3, 0
  B  593 beq 204
  B  594 lhz r0, 0x10(r1)
  B  595 cmpwi r0, 0
--- replace mine 603:604 base 600:601
  M  603 b 180
  B  600 b 176
--- replace mine 608:610 base 605:610
  M  608 addi r0, r3, 1
  M  609 stw r0, 0x2c(r1)
  B  605 addi r3, r3, 1
  B  606 stw r3, 0x2c(r1)
  B  607 lwz r0, 0xc(r30)
  B  608 cmpw r3, r0
  B  609 blt 140
--- replace mine 611:615 base 611:612
  M  611 cmpw r0, r3
  M  612 blt 144
  M  613 lwz r3, 0xc(r30)
  M  614 b 212
  B  611 b 208
--- replace mine 616:620 base 613:617
  M  616 slwi r0, r0, 3
  M  617 lwz r3, 0x30(r1)
  M  618 add r0, r28, r0
  M  619 add r3, r3, r0
  B  613 slwi r3, r0, 3
  B  614 lwz r0, 0x30(r1)
  B  615 add r0, r3, r0
  B  616 add r3, r0, r28
--- replace mine 621:623 base 618:620
  M  621 clrlwi r0, r0, 0x10
  M  622 slwi r4, r0, 8
  B  618 clrlwi r3, r0, 0x10
  B  619 slwi r4, r3, 8
--- replace mine 624:628 base 621:625
  M  624 slwi r0, r0, 3
  M  625 lwz r3, 0x30(r1)
  M  626 add r0, r28, r0
  M  627 add r3, r3, r0
  B  621 slwi r3, r0, 3
  B  622 lwz r0, 0x30(r1)
  B  623 add r0, r3, r0
  B  624 add r3, r0, r28
--- replace mine 630:639 base 627:635
  M  630 clrlwi r6, r0, 0x10
  M  631 lwz r5, 0x18(r31)
  M  632 lbz r4, 0xc(r1)
  M  633 mr r3, r4
  M  634 clrlwi r3, r3, 0x18
  M  635 slwi r0, r3, 1
  M  636 sthx r6, r5, r0
  M  637 addi r0, r4, 1
  M  638 stb r0, 0xc(r1)
  B  627 clrlwi r5, r0, 0x10
  B  628 lwz r4, 0x18(r31)
  B  629 lbz r3, 0xc(r1)
  B  630 clrlwi r0, r3, 0x18
  B  631 slwi r0, r0, 1
  B  632 sthx r5, r4, r0
  B  633 addi r3, r3, 1
  B  634 stb r3, 0xc(r1)
--- replace mine 640:645 base 636:641
  M  640 addi r4, r3, 1
  M  641 stb r4, 0x21(r31)
  M  642 clrlwi r3, r4, 0x18
  M  643 lbz r0, 0x1c(r31)
  M  644 cmplw r3, r0
  B  636 addi r0, r3, 1
  B  637 stb r0, 0x21(r31)
  B  638 clrlwi r0, r0, 0x18
  B  639 lbz r4, 0x1c(r31)
  B  640 cmplw r0, r4
--- replace mine 654:655 base 650:651
  M  654 blt -640
  B  650 blt -636
--- replace mine 660:661 base 656:657
  M  660 blt -676
  B  656 blt -672
```

Filter after mapping work r25 -> r26 and candidate r26 -> r25:

```text
344 343
delete 16 17 16 16
M 16 clrlwi r0, r0, 0x18
replace 205 206 204 205
M 205 add r3, r4, r3
B 204 add r3, r3, r4
replace 212 213 211 212
M 212 add r3, r4, r3
B 211 add r3, r3, r4
```

## Other final ctxdiff evidence

### Zi8PrepareMatch

```text
src 0xeac base 0xeb0 insns 939/940
--- replace mine 11:13 base 11:13
  M   11 li r3, 0x20
  M   12 stb r3, 0xb(r1)
  B   11 li r0, 0x20
  B   12 stb r0, 0xb(r1)
--- insert mine 17:17 base 17:19
  B   17 li r0, 0
  B   18 stb r0, 0xf(r1)
--- replace mine 26:28 base 28:30
  M   26 slwi r0, r0, 1
  M   27 lhzx r0, r4, r0
  B   28 slwi r3, r0, 1
  B   29 lhzx r0, r4, r3
--- replace mine 30:33 base 32:35
  M   30 lbz r3, 0xe(r1)
  M   31 addi r0, r3, -1
  M   32 stb r0, 0xe(r1)
  B   32 lbz r4, 0xe(r1)
  B   33 addi r3, r4, -1
  B   34 stb r3, 0xe(r1)
--- replace mine 43:45 base 45:47
  M   43 lhzx r4, r3, r0
  M   44 cmplwi r4, 0xef00
  B   45 lhzx r0, r3, r0
  B   46 cmplwi r0, 0xef00
--- replace mine 50:51 base 52:56
  M   50 clrlwi r3, r29, 0x18
  B   52 clrlwi r0, r29, 0x18
  B   53 lbz r3, 0xe(r1)
  B   54 cmplw r0, r3
  B   55 blt -52
--- replace mine 52:57 base 57:59
  M   52 cmplw r3, r0
  M   53 blt -52
  M   54 lbz r3, 0xe(r1)
  M   55 cmpwi r3, 0
  M   56 beq 572
  B   57 cmpwi r0, 0
  B   58 beq 580
--- replace mine 64:67 base 66:69
  M   64 clrlwi r0, r3, 0x18
  M   65 cmpwi r0, 0
  M   66 beq 532
  B   66 clrlwi r4, r3, 0x18
  B   67 cmpwi r4, 0
  B   68 beq 540
--- replace mine 68:70 base 70:74
  M   68 addi r0, r4, 1
  M   69 stb r0, 0xd(r1)
  B   70 addi r3, r4, 1
  B   71 stb r3, 0xd(r1)
  B   72 li r0, 1
  B   73 stb r0, 0xf(r1)
--- replace mine 84:87 base 88:91
  M   84 lwz r6, 0x38(r1)
  M   85 lhz r5, 0x26(r1)
  M   86 addis r4, r5, -1
  B   88 lwz r5, 0x38(r1)
  B   89 lhz r4, 0x26(r1)
  B   90 addis r4, r4, -1
--- replace mine 89:93 base 93:97
  M   89 add r3, r6, r0
  M   90 stw r3, 0x38(r1)
  M   91 lwz r3, 0x38(r1)
  M   92 lbz r0, 1(r3)
  B   93 add r0, r5, r0
  B   94 stw r0, 0x38(r1)
  B   95 lwz r4, 0x38(r1)
  B   96 lbz r0, 1(r4)
--- replace mine 98:100 base 102:104
  M   98 add r0, r4, r0
  M   99 clrlwi r0, r0, 0x10
  B  102 add r3, r4, r0
  B  103 clrlwi r0, r3, 0x10
--- replace mine 101:102 base 105:106
  M  101 lwz r3, 0x3c(r1)
  B  105 lwz r4, 0x3c(r1)
--- replace mine 103:105 base 107:109
  M  103 slwi r0, r0, 3
  M  104 add r3, r3, r0
  B  107 slwi r3, r0, 3
  B  108 add r3, r4, r3
--- replace mine 107:109 base 111:113
  M  107 lbz r0, 0(r3)
  M  108 clrlwi r0, r0, 0x1c
  B  111 lbz r3, 0(r3)
  B  112 clrlwi r0, r3, 0x1c
--- replace mine 112:116 base 116:120
  M  112 addi r3, r3, 0
  M  113 slwi r0, r0, 2
  M  114 lwzx r3, r3, r0
  M  115 mtctr r3
  B  116 addi r4, r3, 0
  B  117 slwi r3, r0, 2
  B  118 lwzx r4, r4, r3
  B  119 mtctr r4
--- replace mine 153:154 base 157:160
  M  153 lwz r4, 0x3c(r1)
  B  157 lwz r3, 0x3c(r1)
  B  158 clrlwi r0, r29, 0x18
  B  159 lbzx r0, r3, r0
--- replace mine 155:159 base 161:163
  M  155 lbzx r3, r4, r3
  M  156 clrlwi r0, r29, 0x18
  M  157 add r4, r31, r0
  M  158 stb r3, 0xd(r4)
  B  161 add r3, r31, r3
  B  162 stb r0, 0xd(r3)
--- replace mine 175:178 base 179:182
  M  175 lbz r0, 5(r3)
  M  176 clrlwi r0, r0, 0x1f
  M  177 cmpwi r0, 0
  B  179 lbz r3, 5(r3)
  B  180 clrlwi r3, r3, 0x1f
  B  181 cmpwi r3, 0
--- replace mine 180:185 base 184:189
  M  180 clrlwi r0, r29, 0x18
  M  181 add r4, r31, r0
  M  182 lbz r3, 0xd(r4)
  M  183 rlwinm r0, r3, 0, 0x18, 0x1b
  M  184 clrlwi r0, r0, 0x18
  B  184 clrlwi r3, r29, 0x18
  B  185 add r4, r31, r3
  B  186 lbz r0, 0xd(r4)
  B  187 rlwinm r3, r0, 0, 0x18, 0x1b
  B  188 clrlwi r0, r3, 0x18
--- replace mine 187:189 base 191:193
  M  187 add r4, r31, r0
  M  188 lbz r0, 1(r4)
  B  191 add r3, r31, r0
  B  192 lbz r0, 1(r3)
--- replace mine 190:194 base 194:198
  M  190 clrlwi r3, r0, 0x18
  M  191 stb r3, 1(r4)
  M  192 lwz r4, 0x3c(r1)
  M  193 lbz r3, 5(r4)
  B  194 clrlwi r0, r0, 0x18
  B  195 stb r0, 1(r3)
  B  196 lwz r3, 0x3c(r1)
  B  197 lbz r3, 5(r3)
--- replace mine 199:203 base 203:207
  M  199 lbz r3, 1(r31)
  M  200 clrlwi r0, r3, 0x1c
  M  201 clrlwi r0, r0, 0x18
  M  202 stb r0, 1(r31)
  B  203 lbz r0, 1(r31)
  B  204 clrlwi r0, r0, 0x1c
  B  205 clrlwi r3, r0, 0x18
  B  206 stb r3, 1(r31)
--- replace mine 210:212 base 214:216
  M  210 li r3, 0
  M  211 stb r3, 0xa(r1)
  B  214 li r0, 0
  B  215 stb r0, 0xa(r1)
--- replace mine 213:214 base 217:222
  M  213 rlwinm r0, r0, 0, 0x18, 0x18
  B  217 rlwinm r3, r0, 0, 0x18, 0x18
  B  218 cmpwi r3, 0
  B  219 bne 20
  B  220 lbz r4, 2(r30)
  B  221 rlwinm r0, r4, 0, 0x19, 0x19
--- delete mine 215:219 base 223:223
  M  215 bne 20
  M  216 lbz r0, 2(r30)
  M  217 rlwinm r4, r0, 0, 0x19, 0x19
  M  218 cmpwi r4, 0
--- replace mine 220:222 base 224:226
  M  220 li r3, 1
  M  221 stb r3, 0xa(r1)
  B  224 li r0, 1
  B  225 stb r0, 0xa(r1)
--- replace mine 223:225 base 227:229
  M  223 lbz r0, 2(r30)
  M  224 rlwinm r0, r0, 0, 0x1c, 0x1c
  B  227 lbz r3, 2(r30)
  B  228 rlwinm r0, r3, 0, 0x1c, 0x1c
--- replace mine 230:232 base 234:236
  M  230 lbz r3, 2(r30)
  M  231 rlwinm r0, r3, 0, 0x1a, 0x1a
  B  234 lbz r0, 2(r30)
  B  235 rlwinm r0, r0, 0, 0x1a, 0x1a
--- replace mine 235:237 base 239:241
  M  235 rlwinm r3, r0, 0, 0x1b, 0x1b
  M  236 cmpwi r3, 0
  B  239 rlwinm r4, r0, 0, 0x1b, 0x1b
  B  240 cmpwi r4, 0
--- replace mine 240:242 base 244:246
  M  240 lbz r3, 0xa(r1)
  M  241 cmpwi r3, 0
  B  244 lbz r0, 0xa(r1)
  B  245 cmpwi r0, 0
--- replace mine 243:245 base 247:249
  M  243 lbz r3, 2(r30)
  M  244 stb r3, 0xa(r1)
  B  247 lbz r0, 2(r30)
  B  248 stb r0, 0xa(r1)
--- replace mine 261:262 base 265:266
  M  261 lbz r3, 0xd(r31)
  B  265 lbz r4, 0xd(r31)
--- replace mine 264:269 base 268:273
  M  264 clrlwi r0, r0, 0x18
  M  265 or r0, r3, r0
  M  266 stb r0, 0xd(r31)
  M  267 clrlwi r0, r28, 0x18
  M  268 cmpwi r0, 0
  B  268 clrlwi r3, r0, 0x18
  B  269 or r3, r4, r3
  B  270 stb r3, 0xd(r31)
  B  271 clrlwi r3, r28, 0x18
  B  272 cmpwi r3, 0
--- insert mine 271:271 base 275:278
  B  275 lbz r3, 1(r30)
  B  276 cmpwi r3, 0
  B  277 beq 28
--- replace mine 272:276 base 279:280
  M  272 cmpwi r0, 0
  M  273 beq 28
  M  274 lbz r3, 1(r30)
  M  275 cmplwi r3, 0x10
  B  279 cmplwi r0, 0x10
--- replace mine 277:280 base 281:284
  M  277 lbz r0, 1(r30)
  M  278 cmplwi r0, 5
  M  279 bne 1320
  B  281 lbz r5, 1(r30)
  B  282 cmplwi r5, 5
  B  283 bne 1324
--- replace mine 288:293 base 292:296
  M  288 b 736
  M  289 lwz r5, 8(r30)
  M  290 lbz r4, 0xd(r1)
  M  291 mr r3, r4
  M  292 addi r0, r4, 1
  B  292 b 732
  B  293 lwz r4, 8(r30)
  B  294 lbz r3, 0xd(r1)
  B  295 addi r0, r3, 1
--- replace mine 294:297 base 297:300
  M  294 clrlwi r3, r3, 0x18
  M  295 slwi r0, r3, 1
  M  296 lhzx r0, r5, r0
  B  297 clrlwi r0, r3, 0x18
  B  298 slwi r0, r0, 1
  B  299 lhzx r0, r4, r0
--- replace mine 304:307 base 307:310
  M  304 lis r4, 1
  M  305 addi r4, r4, -0x10fd
  M  306 cmpw r5, r4
  B  307 lis r3, 1
  B  308 addi r3, r3, -0x10fd
  B  309 cmpw r5, r3
--- replace mine 309:312 base 312:315
  M  309 lis r3, 1
  M  310 addi r3, r3, -0x10ff
  M  311 cmpw r5, r3
  B  312 lis r4, 1
  B  313 addi r4, r4, -0x10ff
  B  314 cmpw r5, r4
--- replace mine 321:324 base 324:327
  M  321 lis r4, 1
  M  322 addi r4, r4, -0x10f5
  M  323 cmpw r5, r4
  B  324 lis r3, 1
  B  325 addi r3, r3, -0x10f5
  B  326 cmpw r5, r3
--- replace mine 337:338 base 340:344
  M  337 li r3, 0
  B  340 li r0, 0
  B  341 stb r0, 0xc(r1)
  B  342 b 132
  B  343 li r3, 1
--- delete mine 339:342 base 345:345
  M  339 b 132
  M  340 li r4, 1
  M  341 stb r4, 0xc(r1)
--- replace mine 346:347 base 349:353
  M  346 li r0, 3
  B  349 li r3, 3
  B  350 stb r3, 0xc(r1)
  B  351 b 96
  B  352 li r0, 4
--- delete mine 348:351 base 354:354
  M  348 b 96
  M  349 li r3, 4
  M  350 stb r3, 0xc(r1)
--- replace mine 355:357 base 358:360
  M  355 li r0, 6
  M  356 stb r0, 0xc(r1)
  B  358 li r4, 6
  B  359 stb r4, 0xc(r1)
--- replace mine 361:362 base 364:368
  M  361 li r3, 8
  B  364 li r0, 8
  B  365 stb r0, 0xc(r1)
  B  366 b 36
  B  367 li r3, 4
--- delete mine 363:366 base 369:369
  M  363 b 36
  M  364 li r0, 4
  M  365 stb r0, 0xc(r1)
--- replace mine 367:369 base 370:372
  M  367 li r3, 0xff
  M  368 stb r3, 0xc(r1)
  B  370 li r4, 0xff
  B  371 stb r4, 0xc(r1)
--- replace mine 375:377 base 378:380
  M  375 clrlwi r0, r28, 0x18
  M  376 cmplwi r0, 0x17
  B  378 clrlwi r3, r28, 0x18
  B  379 cmplwi r3, 0x17
--- replace mine 381:384 base 384:387
  M  381 b 2208
  M  382 clrlwi r3, r28, 0x18
  M  383 cmplwi r3, 8
  B  384 b 2200
  B  385 clrlwi r0, r28, 0x18
  B  386 cmplwi r0, 8
--- replace mine 390:392 base 393:395
  M  390 clrlwi r3, r28, 0x18
  M  391 srawi r5, r3, 1
  B  393 clrlwi r0, r28, 0x18
  B  394 srawi r5, r0, 1
--- replace mine 397:399 base 400:402
  M  397 lhz r0, 0x26(r1)
  M  398 cmplwi r0, 0xef0b
  B  400 lhz r3, 0x26(r1)
  B  401 cmplwi r3, 0xef0b
--- replace mine 400:405 base 403:408
  M  400 clrlwi r3, r28, 0x18
  M  401 srawi r5, r3, 1
  M  402 addi r4, r1, 0x4c
  M  403 lbzx r3, r4, r5
  M  404 ori r0, r3, 8
  B  403 clrlwi r0, r28, 0x18
  B  404 srawi r4, r0, 1
  B  405 addi r3, r1, 0x4c
  B  406 lbzx r0, r3, r4
  B  407 ori r0, r0, 8
--- replace mine 406:407 base 409:410
  M  406 stbx r0, r4, r5
  B  409 stbx r0, r3, r4
--- replace mine 411:413 base 414:416
  M  411 clrlwi r3, r28, 0x18
  M  412 srawi r5, r3, 1
  B  414 clrlwi r0, r28, 0x18
  B  415 srawi r5, r0, 1
--- replace mine 414:418 base 417:421
  M  414 lbzx r3, r4, r5
  M  415 ori r0, r3, 4
  M  416 clrlwi r0, r0, 0x18
  M  417 stbx r0, r4, r5
  B  417 lbzx r0, r4, r5
  B  418 ori r0, r0, 4
  B  419 clrlwi r3, r0, 0x18
  B  420 stbx r3, r4, r5
--- insert mine 423:423 base 426:457
  B  426 srawi r5, r0, 1
  B  427 addi r4, r1, 0x4c
  B  428 lbzx r0, r4, r5
  B  429 ori r0, r0, 7
  B  430 clrlwi r3, r0, 0x18
  B  431 stbx r3, r4, r5
  B  432 b 168
  B  433 clrlwi r0, r28, 0x18
  B  434 srawi r5, r0, 1
  B  435 addi r4, r1, 0x40
  B  436 lbzx r3, r4, r5
  B  437 lbz r0, 0xc(r1)
  B  438 slwi r0, r0, 4
  B  439 or r0, r3, r0
  B  440 clrlwi r0, r0, 0x18
  B  441 stbx r0, r4, r5
  B  442 lhz r0, 0x26(r1)
  B  443 cmplwi r0, 0xef0b
  B  444 bne 36
  B  445 clrlwi r0, r28, 0x18
  B  446 srawi r6, r0, 1
  B  447 addi r4, r1, 0x4c
  B  448 lbzx r0, r4, r6
  B  449 ori r5, r0, 0x80
  B  450 clrlwi r3, r5, 0x18
  B  451 stbx r3, r4, r6
  B  452 b 88
  B  453 lhz r0, 0x26(r1)
  B  454 cmplwi r0, 0xef0a
  B  455 bne 36
  B  456 clrlwi r0, r28, 0x18
--- replace mine 426:427 base 460:461
  M  426 ori r0, r0, 7
  B  460 ori r0, r0, 0x40
--- delete mine 429:460 base 463:463
  M  429 b 168
  M  430 clrlwi r0, r28, 0x18
  M  431 srawi r6, r0, 1
  M  432 addi r5, r1, 0x40
  M  433 lbzx r0, r5, r6
  M  434 lbz r4, 0xc(r1)
  M  435 slwi r3, r4, 4
  M  436 or r0, r0, r3
  M  437 clrlwi r0, r0, 0x18
  M  438 stbx r0, r5, r6
  M  439 lhz r3, 0x26(r1)
  M  440 cmplwi r3, 0xef0b
  M  441 bne 36
  M  442 clrlwi r0, r28, 0x18
  M  443 srawi r5, r0, 1
  M  444 addi r3, r1, 0x4c
  M  445 lbzx r0, r3, r5
  M  446 ori r0, r0, 0x80
  M  447 clrlwi r4, r0, 0x18
  M  448 stbx r4, r3, r5
  M  449 b 88
  M  450 lhz r3, 0x26(r1)
  M  451 cmplwi r3, 0xef0a
  M  452 bne 36
  M  453 clrlwi r0, r28, 0x18
  M  454 srawi r5, r0, 1
  M  455 addi r4, r1, 0x4c
  M  456 lbzx r0, r4, r5
  M  457 ori r0, r0, 0x40
  M  458 clrlwi r3, r0, 0x18
  M  459 stbx r3, r4, r5
--- replace mine 464:466 base 467:469
  M  464 clrlwi r0, r28, 0x18
  M  465 srawi r5, r0, 1
  B  467 clrlwi r3, r28, 0x18
  B  468 srawi r5, r3, 1
--- replace mine 467:469 base 470:472
  M  467 lbzx r3, r4, r5
  M  468 ori r3, r3, 0x70
  B  470 lbzx r0, r4, r5
  B  471 ori r3, r0, 0x70
--- replace mine 473:477 base 476:480
  M  473 clrlwi r3, r0, 0x18
  M  474 lbz r0, 0xe(r1)
  M  475 cmplw r3, r0
  M  476 blt -748
  B  476 clrlwi r0, r0, 0x18
  B  477 lbz r3, 0xe(r1)
  B  478 cmplw r0, r3
  B  479 blt -744
--- replace mine 482:484 base 485:487
  M  482 lbzx r4, r3, r0
  M  483 clrlwi r0, r29, 0x18
  B  485 lbzx r0, r3, r0
  B  486 clrlwi r4, r29, 0x18
--- replace mine 485:486 base 488:489
  M  485 stbx r4, r3, r0
  B  488 stbx r0, r3, r4
--- replace mine 488:489 base 491:496
  M  488 lbzx r3, r3, r0
  B  491 lbzx r0, r3, r0
  B  492 clrlwi r4, r29, 0x18
  B  493 addi r3, r1, 0x30
  B  494 stbx r0, r3, r4
  B  495 addi r29, r29, 1
--- replace mine 490:495 base 497:498
  M  490 addi r4, r1, 0x30
  M  491 stbx r3, r4, r0
  M  492 addi r29, r29, 1
  M  493 clrlwi r3, r29, 0x18
  M  494 cmplwi r3, 4
  B  497 cmplwi r0, 4
--- replace mine 499:501 base 502:504
  M  499 clrlwi r0, r28, 0x18
  M  500 cmplwi r0, 8
  B  502 clrlwi r3, r28, 0x18
  B  503 cmplwi r3, 8
--- replace mine 503:505 base 506:508
  M  503 srawi r3, r0, 1
  M  504 clrlwi r29, r3, 0x18
  B  506 srawi r0, r0, 1
  B  507 clrlwi r29, r0, 0x18
--- replace mine 512:513 base 515:533
  M  512 ori r0, r0, 0xf
  B  515 ori r3, r0, 0xf
  B  516 clrlwi r0, r3, 0x18
  B  517 clrlwi r3, r29, 0x18
  B  518 addi r4, r1, 0x34
  B  519 stbx r0, r4, r3
  B  520 clrlwi r4, r29, 0x18
  B  521 addi r3, r1, 0x30
  B  522 lbzx r0, r3, r4
  B  523 ori r3, r0, 0xf
  B  524 clrlwi r3, r3, 0x18
  B  525 clrlwi r5, r29, 0x18
  B  526 addi r4, r1, 0x30
  B  527 stbx r3, r4, r5
  B  528 b 68
  B  529 clrlwi r4, r29, 0x18
  B  530 addi r3, r1, 0x34
  B  531 lbzx r0, r3, r4
  B  532 ori r0, r0, 0xf0
--- delete mine 518:523 base 538:538
  M  518 addi r3, r1, 0x30
  M  519 lbzx r3, r3, r0
  M  520 ori r0, r3, 0xf
  M  521 clrlwi r3, r0, 0x18
  M  522 clrlwi r0, r29, 0x18
--- replace mine 524:537 base 539:540
  M  524 stbx r3, r4, r0
  M  525 b 68
  M  526 clrlwi r0, r29, 0x18
  M  527 addi r3, r1, 0x34
  M  528 lbzx r3, r3, r0
  M  529 ori r6, r3, 0xf0
  M  530 clrlwi r5, r6, 0x18
  M  531 clrlwi r4, r29, 0x18
  M  532 addi r3, r1, 0x34
  M  533 stbx r5, r3, r4
  M  534 clrlwi r0, r29, 0x18
  M  535 addi r3, r1, 0x30
  M  536 lbzx r3, r3, r0
  B  539 lbzx r3, r4, r0
--- replace mine 542:544 base 545:547
  M  542 lbz r3, 0x6c(r31)
  M  543 cmpwi r3, 0
  B  545 lbz r0, 0x6c(r31)
  B  546 cmpwi r0, 0
--- replace mine 563:566 base 566:569
  M  563 lbz r0, 0x6c(r31)
  M  564 mulli r0, r0, 0xc
  M  565 add r3, r31, r0
  B  566 lbz r4, 0x6c(r31)
  B  567 mulli r3, r4, 0xc
  B  568 add r3, r31, r3
--- replace mine 570:573 base 573:576
  M  570 lbz r0, 0x6c(r31)
  M  571 mulli r0, r0, 0xc
  M  572 add r3, r31, r0
  B  573 lbz r3, 0x6c(r31)
  B  574 mulli r3, r3, 0xc
  B  575 add r3, r31, r3
--- replace mine 578:585 base 581:588
  M  578 addi r0, r3, 1
  M  579 stb r0, 0x6c(r31)
  M  580 lbz r0, 0xc(r1)
  M  581 cmplwi r0, 0xff
  M  582 bne 1400
  M  583 lbz r3, 0xd(r1)
  M  584 clrlwi r3, r3, 0x18
  B  581 addi r3, r3, 1
  B  582 stb r3, 0x6c(r31)
  B  583 lbz r3, 0xc(r1)
  B  584 cmplwi r3, 0xff
  B  585 bne 108
  B  586 lbz r0, 0xd(r1)
  B  587 clrlwi r3, r0, 0x18
--- replace mine 587:591 base 590:594
  M  587 bge 1380
  M  588 lbz r3, 0x6c(r31)
  M  589 cmplwi r3, 0x10
  M  590 bge 1368
  B  590 bge 88
  B  591 lbz r0, 0x6c(r31)
  B  592 cmplwi r0, 0x10
  B  593 bge 76
--- replace mine 599:602 base 602:605
  M  599 lbz r3, 1(r31)
  M  600 rlwinm r3, r3, 0, 0x18, 0x1b
  M  601 clrlwi r3, r3, 0x18
  B  602 lbz r4, 1(r31)
  B  603 rlwinm r0, r4, 0, 0x18, 0x1b
  B  604 clrlwi r3, r0, 0x18
--- replace mine 603:607 base 606:610
  M  603 lbz r3, 0xd(r31)
  M  604 rlwinm r3, r3, 0, 0x18, 0x1b
  M  605 clrlwi r3, r3, 0x18
  M  606 stb r3, 0x40(r1)
  B  606 lbz r4, 0xd(r31)
  B  607 rlwinm r3, r4, 0, 0x18, 0x1b
  B  608 clrlwi r0, r3, 0x18
  B  609 stb r0, 0x40(r1)
--- insert mine 609:609 base 612:614
  B  612 li r3, 1
  B  613 b 1284
--- replace mine 612:613 base 617:618
  M  612 beq 1280
  B  617 beq 1264
--- replace mine 616:618 base 621:623
  M  616 lbz r4, 1(r30)
  M  617 cmplwi r4, 0xc
  B  621 lbz r0, 1(r30)
  B  622 cmplwi r0, 0xc
--- replace mine 633:634 base 638:639
  M  633 b 68
  B  638 b 60
--- replace mine 640:642 base 645:646
  M  640 mr r0, r3
  M  641 stw r0, 0x2c(r1)
  B  645 stw r3, 0x2c(r1)
--- replace mine 648:650 base 652:653
  M  648 mr r4, r3
  M  649 sth r4, 0x24(r1)
  B  652 sth r3, 0x24(r1)
--- replace mine 666:669 base 669:674
  M  666 b 660
  M  667 li r4, 0
  M  668 sth r4, 0x1a(r1)
  B  669 b 652
  B  670 li r0, 0
  B  671 sth r0, 0x1a(r1)
  B  672 li r0, 0
  B  673 sth r0, 0x18(r1)
--- replace mine 670:671 base 675:676
  M  670 sth r3, 0x18(r1)
  B  675 sth r3, 0x16(r1)
--- replace mine 672:675 base 677:678
  M  672 sth r0, 0x16(r1)
  M  673 li r3, 0
  M  674 sth r3, 0x14(r1)
  B  677 sth r0, 0x14(r1)
--- replace mine 681:683 base 684:686
  M  681 li r0, 0
  M  682 stb r0, 0x25(r31)
  B  684 li r3, 0
  B  685 stb r3, 0x25(r31)
--- replace mine 688:689 base 691:692
  M  688 b 464
  B  691 b 456
--- replace mine 690:692 base 693:695
  M  690 lhz r4, 0x1c(r1)
  M  691 clrlwi r4, r4, 0x18
  B  693 lhz r0, 0x1c(r1)
  B  694 clrlwi r4, r0, 0x18
--- replace mine 712:714 base 715:717
  M  712 lbz r3, 0x25(r31)
  M  713 slwi r0, r3, 1
  B  715 lbz r0, 0x25(r31)
  B  716 slwi r0, r0, 1
--- replace mine 718:719 base 721:722
  M  718 bne 328
  B  721 bne 320
--- replace mine 723:724 base 726:727
  M  723 b 308
  B  726 b 300
--- replace mine 744:746 base 747:749
  M  744 lbz r3, 0x25(r31)
  M  745 addi r0, r3, 1
  B  747 lbz r4, 0x25(r31)
  B  748 addi r0, r4, 1
--- replace mine 764:766 base 767:769
  M  764 b 176
  M  765 lwz r4, 0x28(r1)
  B  767 b 168
  B  768 lwz r5, 0x28(r1)
--- replace mine 767:772 base 770:775
  M  767 addi r0, r3, -1
  M  768 slwi r0, r0, 1
  M  769 lhzx r0, r4, r0
  M  770 cmplwi r0, 0xf360
  M  771 bne 52
  B  770 addi r3, r3, -1
  B  771 slwi r4, r3, 1
  B  772 lhzx r3, r5, r4
  B  773 cmplwi r3, 0xf360
  B  774 bne 44
--- insert mine 776:776 base 779:780
  B  779 sth r0, 0x1a(r1)
--- insert mine 778:778 base 782:783
  B  782 sth r0, 0x18(r1)
--- replace mine 779:784 base 784:785
  M  779 lhz r0, 0x14(r1)
  M  780 sth r0, 0x18(r1)
  M  781 lhz r0, 0x16(r1)
  M  782 sth r0, 0x1a(r1)
  M  783 b -308
  B  784 b -300
--- replace mine 787:791 base 788:792
  M  787 lhz r3, 0x1c(r1)
  M  788 addi r0, r3, -1
  M  789 clrlwi r5, r0, 0x18
  M  790 stb r5, 0x22(r30)
  B  788 lhz r5, 0x1c(r1)
  B  789 addi r3, r5, -1
  B  790 clrlwi r3, r3, 0x18
  B  791 stb r3, 0x22(r30)
--- replace mine 793:797 base 794:798
  M  793 slwi r0, r3, 1
  M  794 add r3, r4, r0
  M  795 addi r0, r3, -2
  M  796 stw r0, 0x28(r1)
  B  794 slwi r3, r3, 1
  B  795 add r3, r4, r3
  B  796 addi r3, r3, -2
  B  797 stw r3, 0x28(r1)
--- delete mine 800:803 base 801:801
  M  800 lhz r5, 0x1c(r1)
  M  801 addi r3, r5, 1
  M  802 sth r3, 0x1c(r1)
--- replace mine 804:810 base 802:811
  M  804 clrlwi r4, r29, 0x18
  M  805 lbz r3, 0xe(r1)
  M  806 cmplw r4, r3
  M  807 blt -472
  M  808 lbz r3, 0xe(r1)
  M  809 cmpwi r3, 0
  B  802 lhz r3, 0x1c(r1)
  B  803 addi r0, r3, 1
  B  804 sth r0, 0x1c(r1)
  B  805 clrlwi r3, r29, 0x18
  B  806 lbz r0, 0xe(r1)
  B  807 cmplw r3, r0
  B  808 blt -464
  B  809 lbz r0, 0xe(r1)
  B  810 cmpwi r0, 0
--- replace mine 812:815 base 813:816
  M  812 lbz r3, 0x25(r31)
  M  813 slwi r3, r3, 1
  M  814 add r3, r31, r3
  B  813 lbz r0, 0x25(r31)
  B  814 slwi r0, r0, 1
  B  815 add r3, r31, r0
--- replace mine 831:835 base 832:836
  M  831 lbz r3, 3(r30)
  M  832 lbz r0, 0xb(r1)
  M  833 and r0, r3, r0
  M  834 cmpwi r0, 0
  B  832 lbz r5, 3(r30)
  B  833 lbz r4, 0xb(r1)
  B  834 and r3, r5, r4
  B  835 cmpwi r3, 0
--- replace mine 844:847 base 845:848
  M  844 lis r3, 1
  M  845 addi r3, r3, -1
  M  846 sth r3, 0x26(r31)
  B  845 lis r4, 1
  B  846 addi r4, r4, -1
  B  847 sth r4, 0x26(r31)
--- replace mine 850:855 base 851:856
  M  850 li r5, 0
  M  851 stb r5, 0x25(r31)
  M  852 lbz r4, 4(r30)
  M  853 rlwinm r3, r4, 0, 0x1a, 0x1a
  M  854 cmpwi r3, 0
  B  851 li r0, 0
  B  852 stb r0, 0x25(r31)
  B  853 lbz r0, 4(r30)
  B  854 rlwinm r0, r0, 0, 0x1a, 0x1a
  B  855 cmpwi r0, 0
--- replace mine 862:864 base 863:865
  M  862 lbz r0, 0x25(r31)
  M  863 cmplwi r0, 1
  B  863 lbz r5, 0x25(r31)
  B  864 cmplwi r5, 1
--- replace mine 865:869 base 866:870
  M  865 lbz r3, 0x25(r31)
  M  866 addi r5, r3, -1
  M  867 slwi r4, r5, 1
  M  868 add r3, r31, r4
  B  866 lbz r4, 0x25(r31)
  B  867 addi r0, r4, -1
  B  868 slwi r0, r0, 1
  B  869 add r3, r31, r0
--- insert mine 871:871 base 872:885
  B  872 clrlwi r5, r0, 0x10
  B  873 sth r5, 0x22(r1)
  B  874 lbz r4, 0x25(r31)
  B  875 addi r0, r4, -1
  B  876 slwi r0, r0, 1
  B  877 add r3, r31, r0
  B  878 lhz r0, 0x46(r3)
  B  879 rlwinm r5, r0, 0, 0x10, 0x1c
  B  880 clrlwi r4, r5, 0x10
  B  881 sth r4, 0x20(r1)
  B  882 b 36
  B  883 lhz r3, 0x26(r31)
  B  884 rlwinm r0, r3, 0, 0x10, 0x1c
--- delete mine 873:886 base 887:887
  M  873 lbz r3, 0x25(r31)
  M  874 addi r5, r3, -1
  M  875 slwi r4, r5, 1
  M  876 add r3, r31, r4
  M  877 lhz r0, 0x46(r3)
  M  878 rlwinm r0, r0, 0, 0x10, 0x1c
  M  879 clrlwi r0, r0, 0x10
  M  880 sth r0, 0x20(r1)
  M  881 b 36
  M  882 lhz r0, 0x26(r31)
  M  883 rlwinm r4, r0, 0, 0x10, 0x1c
  M  884 clrlwi r3, r4, 0x10
  M  885 sth r3, 0x22(r1)
--- replace mine 894:897 base 895:898
  M  894 lhz r5, 0x1c(r1)
  M  895 slwi r0, r5, 1
  M  896 lbzx r4, r6, r0
  B  895 lhz r4, 0x1c(r1)
  B  896 slwi r0, r4, 1
  B  897 lbzx r5, r6, r0
--- replace mine 900:905 base 901:906
  M  900 add r3, r0, r3
  M  901 lbz r0, 1(r3)
  M  902 clrlwi r5, r0, 0x10
  M  903 slwi r3, r5, 8
  M  904 or r0, r4, r3
  B  901 add r4, r0, r3
  B  902 lbz r3, 1(r4)
  B  903 clrlwi r0, r3, 0x10
  B  904 slwi r0, r0, 8
  B  905 or r0, r5, r0
--- replace mine 907:912 base 908:913
  M  907 lhz r4, 0x20(r1)
  M  908 lhz r3, 0x1e(r1)
  M  909 lhz r0, 0x22(r1)
  M  910 and r5, r3, r0
  M  911 cmpw r4, r5
  B  908 lhz r3, 0x20(r1)
  B  909 lhz r5, 0x1e(r1)
  B  910 lhz r4, 0x22(r1)
  B  911 and r0, r5, r4
  B  912 cmpw r3, r0
--- replace mine 913:915 base 914:916
  M  913 lhz r4, 0x1c(r1)
  M  914 addi r0, r4, 1
  B  914 lhz r3, 0x1c(r1)
  B  915 addi r0, r3, 1
--- insert mine 916:916 base 917:922
  B  917 lhz r0, 0x1c(r1)
  B  918 clrlwi r0, r0, 0x10
  B  919 lhz r3, 0x24(r1)
  B  920 cmplw r0, r3
  B  921 blt -108
--- delete mine 920:925 base 926:926
  M  920 blt -108
  M  921 lhz r0, 0x1c(r1)
  M  922 clrlwi r5, r0, 0x10
  M  923 lhz r4, 0x24(r1)
  M  924 cmplw r5, r4
--- replace mine 926:929 base 927:930
  M  926 lis r3, 1
  M  927 addi r3, r3, -1
  M  928 sth r3, 0x26(r31)
  B  927 lis r4, 1
  B  928 addi r4, r4, -1
  B  929 sth r4, 0x26(r31)
```

### Zi8GetPyPhonetic

```text
src 0xb38 base 0xb38 insns 718/718
diffs 167: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]
     7 M mr r25, r5
       B mr r26, r5
     8 M mr r26, r6
       B mr r28, r6
     9 M mr r31, r7
       B mr r25, r7
    13 M addi r29, r1, 0x20
       B addi r30, r1, 0x20
    19 M stb r0, 0(r31)
       B stb r0, 0(r25)
    29 M li r28, 0
       B li r29, 0
    30 M stb r28, 0xf(r1)
       B stb r29, 0xf(r1)
    32 M clrlwi r4, r28, 0x18
       B clrlwi r4, r29, 0x18
    37 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
    42 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
    47 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
    58 M lhzx r4, r29, r5
       B lhzx r4, r30, r5
    64 M lhzx r0, r29, r0
       B lhzx r0, r30, r0
    71 M sthx r4, r29, r0
       B sthx r4, r30, r0
    74 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
    83 M sthx r0, r29, r3
       B sthx r0, r30, r3
    87 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
    93 M sthx r4, r29, r0
       B sthx r4, r30, r0
    96 M addi r28, r28, 1
       B addi r29, r29, 1
    97 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
   111 M sthx r3, r25, r0
       B sthx r3, r26, r0
   115 M sthx r3, r26, r0
       B sthx r3, r28, r0
   116 M lhz r30, 0(r29)
       B lhz r31, 0(r30)
   117 M clrlwi r3, r30, 0x10
       B clrlwi r3, r31, 0x10
   120 M clrlwi r3, r30, 0x10
       B clrlwi r3, r31, 0x10
   123 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   126 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   131 M sth r3, 0(r26)
       B sth r3, 0(r28)
   132 M sth r3, 0(r25)
       B sth r3, 0(r26)
   137 M addis r3, r30, -1
       B addis r3, r31, -1
   139 M clrlwi r30, r3, 0x10
       B clrlwi r31, r3, 0x10
   141 M addi r0, r30, -0x61
       B addi r0, r31, -0x61
   142 M clrlwi r30, r0, 0x10
       B clrlwi r31, r0, 0x10
   143 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   155 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   158 M stb r0, 0(r31)
       B stb r0, 0(r25)
   165 M sthx r0, r25, r3
       B sthx r0, r26, r3
   173 M sthx r3, r26, r0
       B sthx r3, r28, r0
   174 M lhz r0, 0(r25)
       B lhz r0, 0(r26)
   176 M lhz r0, 0(r26)
       B lhz r0, 0(r28)
   182 M addi r29, r29, 2
       B addi r30, r30, 2
   192 M lhzx r0, r25, r4
       B lhzx r0, r26, r4
   195 M sthx r0, r25, r4
       B sthx r0, r26, r4
   198 M lhzx r0, r26, r3
       B lhzx r0, r28, r3
   201 M sthx r0, r26, r3
       B sthx r0, r28, r3
   202 M lhz r30, 0(r29)
       B lhz r31, 0(r30)
   203 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   206 M clrlwi r4, r30, 0x10
       B clrlwi r4, r31, 0x10
   212 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   215 M stb r0, 0(r31)
       B stb r0, 0(r25)
   218 M lhzx r3, r26, r4
       B lhzx r3, r28, r4
   221 M sthx r0, r26, r4
       B sthx r0, r28, r4
   222 M lhz r0, 0(r25)
       B lhz r0, 0(r26)
   224 M lhz r0, 0(r26)
       B lhz r0, 0(r28)
   230 M addi r29, r29, 2
       B addi r30, r30, 2
   232 M lhz r0, 0(r29)
       B lhz r0, 0(r30)
   235 M lhz r3, 0(r29)
       B lhz r3, 0(r30)
   240 M li r28, 0
       B li r29, 0
   243 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   246 M addi r28, r28, 1
       B addi r29, r29, 1
   247 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   250 M li r28, 0
       B li r29, 0
   252 M lhz r30, 0(r29)
       B lhz r31, 0(r30)
   253 M clrlwi r3, r30, 0x10
       B clrlwi r3, r31, 0x10
   256 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   259 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   262 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   268 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   271 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   274 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   280 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   283 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   286 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   289 M addis r3, r30, -1
       B addis r3, r31, -1
   291 M clrlwi r30, r0, 0x10
       B clrlwi r31, r0, 0x10
   292 M cmplwi r30, 0x19
       B cmplwi r31, 0x19
   297 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   300 M stb r0, 0(r31)
       B stb r0, 0(r25)
   302 M addi r0, r30, -0x61
       B addi r0, r31, -0x61
   303 M clrlwi r30, r0, 0x10
       B clrlwi r31, r0, 0x10
   304 M clrlwi r3, r30, 0x18
       B clrlwi r3, r31, 0x18
   307 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   320 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   323 M stb r0, 0(r31)
       B stb r0, 0(r25)
   324 M addi r29, r29, 2
       B addi r30, r30, 2
   325 M addi r28, r28, 1
       B addi r29, r29, 1
   331 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   335 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
   349 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   352 M stb r0, 0(r31)
       B stb r0, 0(r25)
   354 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
   358 M addi r29, r29, 2
       B addi r30, r30, 2
   359 M addi r28, r28, 1
       B addi r29, r29, 1
   366 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
   371 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   378 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   384 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   387 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   393 M lhz r30, 0(r29)
       B lhz r31, 0(r30)
   394 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   397 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   400 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   406 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   409 M stb r0, 0(r31)
       B stb r0, 0(r25)
   410 M addi r29, r29, 2
       B addi r30, r30, 2
   412 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   439 M sthx r3, r25, r0
       B sthx r3, r26, r0
   443 M sthx r3, r26, r0
       B sthx r3, r28, r0
   446 M lhzx r3, r25, r4
       B lhzx r3, r26, r4
   452 M sthx r0, r25, r4
       B sthx r0, r26, r4
   455 M lhzx r3, r26, r4
       B lhzx r3, r28, r4
   461 M sthx r0, r26, r4
       B sthx r0, r28, r4
   462 M lhz r0, 0(r25)
       B lhz r0, 0(r26)
   464 M lhz r0, 0(r26)
       B lhz r0, 0(r28)
   467 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   475 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   494 M sthx r3, r25, r0
       B sthx r3, r26, r0
   498 M sthx r4, r26, r3
       B sthx r4, r28, r3
   501 M lhzx r4, r25, r5
       B lhzx r4, r26, r5
   507 M sthx r4, r25, r5
       B sthx r4, r26, r5
   510 M lhzx r4, r26, r3
       B lhzx r4, r28, r3
   516 M sthx r0, r26, r3
       B sthx r0, r28, r3
   517 M lhz r3, 0(r25)
       B lhz r3, 0(r26)
   519 M lhz r0, 0(r26)
       B lhz r0, 0(r28)
   528 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   561 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
   580 M sthx r3, r25, r0
       B sthx r3, r26, r0
   584 M sthx r4, r26, r0
       B sthx r4, r28, r0
   587 M lhzx r4, r25, r5
       B lhzx r4, r26, r5
   593 M sthx r0, r25, r5
       B sthx r0, r26, r5
   596 M lhzx r3, r26, r4
       B lhzx r3, r28, r4
   602 M sthx r3, r26, r4
       B sthx r3, r28, r4
   603 M lhz r0, 0(r25)
       B lhz r0, 0(r26)
   605 M lhz r0, 0(r26)
       B lhz r0, 0(r28)
   610 M lhz r30, 0(r29)
       B lhz r31, 0(r30)
   611 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   614 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   617 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   620 M addi r29, r29, 2
       B addi r30, r30, 2
   625 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   628 M stb r4, 0(r31)
       B stb r4, 0(r25)
   630 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   633 M addis r3, r30, -1
       B addis r3, r31, -1
   635 M clrlwi r30, r0, 0x10
       B clrlwi r31, r0, 0x10
   636 M cmplwi r30, 4
       B cmplwi r31, 4
   638 M addi r30, r30, 1
       B addi r31, r31, 1
   641 M lhzx r0, r25, r3
       B lhzx r0, r26, r3
   644 M sthx r0, r25, r3
       B sthx r0, r26, r3
   647 M lhzx r0, r26, r4
       B lhzx r0, r28, r4
   648 M or r3, r0, r30
       B or r3, r0, r31
   649 M sthx r3, r26, r4
       B sthx r3, r28, r4
   650 M lhz r0, 0(r25)
       B lhz r0, 0(r26)
   652 M lhz r0, 0(r26)
       B lhz r0, 0(r28)
   655 M addi r29, r29, 2
       B addi r30, r30, 2
   659 M lbz r4, 0(r31)
       B lbz r4, 0(r25)
   662 M stb r0, 0(r31)
       B stb r0, 0(r25)
   666 M lhz r30, 0(r29)
       B lhz r31, 0(r30)
   667 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   670 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   673 M clrlwi r0, r30, 0x10
       B clrlwi r0, r31, 0x10
   677 M addi r29, r29, 2
       B addi r30, r30, 2
   681 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   684 M stb r4, 0(r31)
       B stb r4, 0(r25)
   695 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   701 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   707 M lbz r3, 0(r31)
       B lbz r3, 0(r25)
   710 M stb r0, 0(r31)
       B stb r0, 0(r25)
```

### Zi8GetPyFinal

```text
src 0xd4 base 0xd4 insns 53/53
diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]
    26 M slwi r6, r0, 3
       B slwi r7, r0, 3
    27 M lis r7, 0
       B lis r6, 0
    28 M addi r0, r7, 0
       B addi r0, r6, 0
    29 M add r6, r0, r6
       B add r6, r0, r7
    34 M slwi r6, r0, 3
       B slwi r7, r0, 3
    35 M lis r7, 0
       B lis r6, 0
    36 M addi r0, r7, 0
       B addi r0, r6, 0
    37 M add r6, r0, r6
       B add r6, r0, r7
```

### Zi8GetDataSignature

```text
src 0x114 base 0x114 insns 69/69
diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]
     5 M mr r27, r3
       B mr r28, r3
     7 M mr r28, r5
       B mr r29, r5
     9 M clrlwi r0, r28, 0x18
       B clrlwi r0, r29, 0x18
    28 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
    32 M mr r29, r3
       B mr r27, r3
    33 M clrlwi r3, r28, 0x18
       B clrlwi r3, r29, 0x18
    51 M mr r3, r27
       B mr r3, r28
    52 M mr r4, r29
       B mr r4, r27
    57 M stbx r3, r27, r0
       B stbx r3, r28, r0
```

### Zi8IsDupWChar

```text
src 0xfc base 0xfc insns 63/63
diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]
     5 M mr r27, r3
       B mr r28, r3
     7 M li r28, 0
       B li r27, 0
    14 M sth r27, 2(r31)
       B sth r28, 2(r31)
    25 M clrlwi r3, r27, 0x10
       B clrlwi r3, r28, 0x10
    30 M li r28, 1
       B li r27, 1
    41 M sthx r27, r31, r0
       B sthx r28, r31, r0
    49 M sth r27, 2(r31)
       B sth r28, 2(r31)
    56 M mr r3, r28
       B mr r3, r27
```

### Zi8MatchROMdata1

```text
src 0x200 base 0x200 insns 128/128
diffs 5: [12, 36, 37, 52, 57]
    12 M mr r26, r10
       B mr r27, r10
    36 M mr r27, r3
       B mr r26, r3
    37 M stw r27, 0x1764(r31)
       B stw r26, 0x1764(r31)
    52 M addi r26, r26, -1
       B addi r27, r27, -1
    57 M clrlwi r0, r26, 0x18
       B clrlwi r0, r27, 0x18
```

### Zi8MatchPhonetic exact result

```text
src 0x5ac base 0x5ac insns 363/363
diffs 0: []
```

Pinyin register map: initial r25 -> r26, final r26 -> r28, result-count r31 -> r25, index r28 -> r29, current r29 -> r30, value r30 -> r31. With this map all 718 instructions agree, including branch destinations. No mapping is used by the gate; the function remains open.

## Gates, changed files, and commits

[Every gate block from this round](ezi3.round4.gates.txt). All nine gates passed. The final non-quick combined gate rebuilt all six owned units, reported zero regressions, zero forbidden patterns, zero readability warnings, and retained the required DOL hash. There was also a full non-quick zi8match gate at the exact-function checkpoint. No separate link investigation was performed.

Changed source files:

- `libs/RVLMiddleware/eZiText/src/clib/zkokeyp.c`
- `libs/RVLMiddleware/eZiText/src/clib/zprepare.c`
- `libs/RVLMiddleware/eZiText/src/clib/zi8match.c`

Evidence files: `tools/decomp-assist/ezi3.round4.attempts.md` and `tools/decomp-assist/ezi3.round4.gates.txt`.

Code commits, oldest first:

```text
99c599a4 match pinyin loop entry count check
9d21b4ca match korean packed key cursor increment
9878f15b match phonetic input advance and segment bounds
7f9d8710 match phonetic sound group branch direction
97cb9344 match dictionary node pointer register lifetime
8d42f90b match packed sound offset addition order
91100ac8 match phonetic dictionary traversal exactly
```

The evidence commit also removes redundant parentheses from the segment bound comparison; its generated code was included in the final full gate. Its hash appears in the final handoff.
