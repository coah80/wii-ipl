# ezi3 continuation, round 3

Baseline: `dfb64b97476e939a37a75cadd1253b3464c83868`.

All fourteen functions open at the baseline received at least three successful, distinct source-level attempts in this round. Failed builds and three invalid no-op span selections are logged separately and are not counted. The function-span parser was corrected and three real Zi8GetPyFinal variations were then built and measured. One function became instruction-exact: `Zi8GetKoreanCandidates`, 619 instructions, zero ctxdiff differences. No Matching flags or shared headers changed.

## Before and after

| Unit | Instruction-exact functions | Matched code bytes | Matched data bytes | Code fuzzy percent |
|---|---|---|---|---|
| zkokeyp | 1/7 -> 1/7 | 332 -> 332 | 56 -> 56 | 94.311540 -> 98.615390 |
| zprepare | 0/1 -> 0/1 | 0 -> 0 | 8 -> 8 | 86.263830 -> 96.097870 |
| zikorean | 2/3 -> 3/3 | 2712 -> 5188 | 24 -> 60 | 86.940636 -> 100.000000 |
| zi8match | 7/10 -> 7/10 | 3720 -> 3720 | 608 -> 608 | 89.016470 -> 99.035370 |
| zi8getc2 | 15/17 -> 15/17 | 6360 -> 6360 | 324 -> 324 | 99.950640 -> 99.950640 |
| zi8dawg | 5/6 -> 5/6 | 4356 -> 4356 | 120 -> 120 | 99.975350 -> 99.975350 |

## Remaining functions

- `Zi8_8148302C`: 99.49152%; 59/59 instructions; six work/index register differences (r27/r29). Successful new attempts: 6.
- `Zi8_81483264`: 98.902435%; 41/41 instructions; eight parameter/index register differences (r30/r31). Successful new attempts: 3.
- `Zi8_81483308`: 99.13793%; 58/58 instructions; nine count-pointer/index register differences (r29/r30). Successful new attempts: 3.
- `Zi8_814833F0`: 99.04256%; 47/47 instructions; eight parameter/index register differences (r30/r31). Successful new attempts: 3.
- `Zi8_814834AC`: 99.3586%; 344/343 instructions; extra byte narrowing during packed-key initialization, two reversed add operands, and work/candidate register allocation. Successful new attempts: 7.
- `Zi8GetKOcandidates`: 97.89238%; 674/669 instructions; packed-key initialization, helper-return narrowing, address-expression scheduling, and temporary registers remain. Successful new attempts: 9.
- `Zi8PrepareMatch`: 96.09787%; 939/940 instructions; original unread component-flag stores are absent, component-pointer expression scheduling and temporary registers remain; switch relocations are 16 bytes early. Successful new attempts: 6.
- `Zi8MatchPhonetic`: 97.2011%; 366/363 instructions; dictionary spills where target keeps r17, strictMode stays in r17 where target reads its stack parameter; traversal locals shift four bytes and three instructions remain. Successful new attempts: 6.
- `Zi8GetPyPhonetic`: 98.69777%; 718/718 instructions; register assignment cycle among initial/final/result-count/current/value/index; initial loop-entry branch still targets the bound test instead of the count test. Successful new attempts: 17.
- `Zi8GetPyFinal`: 99.245285%; 53/53 instructions; eight r6/r7 temporary-register differences. Successful new attempts: 3.
- `Zi8GetDataSignature`: 99.347824%; 69/69 instructions; nine destination/language/signature-pointer register differences. Successful new attempts: 3.
- `Zi8IsDupWChar`: 99.36508%; 63/63 instructions; eight character/result-flag register differences (r27/r28). Successful new attempts: 3.
- `Zi8MatchROMdata1`: 99.765625%; 128/128 instructions; five group-index/table-address register differences (r26/r27). Successful new attempts: 3.

Completed: `Zi8GetKoreanCandidates`, 100.0%; six successful new attempts.

## Data and uncertainties

Every owned string pool is identical and empty. The real lookup tables retain their source order. No synthetic table or alignment object was added.

- `zikorean`: both 124-byte switch tables now have all 62 relocation tuples identical to the first 248 bytes of the target. The target section has another 40 bytes, whose ten relocations name `Zi8_81483118` in `zkokeyp`. The source emits that real switch in `zkokeyp`. Thus objdiff leaves `.data` unmatched because the section lengths differ, despite both Korean-owned switch tables being exact. All Korean code, extab, and extabindex payloads are exact. Gate data credit rises from 24 to 60 bytes.
- `zkokeyp`: extab is exact; extabindex depends on the two remaining function-size differences. Its source-only 40-byte switch is the table extracted into the Korean target section, as described above. Moving it would change another translation unit output or require a fabricated table.
- `zprepare`: the 48-byte switch payload is identical, but its twelve relocation addends remain 16 bytes early. The target stores an unread component-present byte at frame offset 0x0f twice; its role is inferred and no dummy local was added to reproduce dead stores.
- `zi8match`: all 528 bytes of real lookup tables and 80 bytes of extab match. Remaining extabindex size words follow the three-instruction difference in `Zi8MatchPhonetic`. The original byte at stack offset 0x0c is initialized to zero and read by alternate-initial branches, never reassigned. `alternateInitial` is the inferred semantic name; the actual original zero initialization and both branch bodies are preserved.
- `zi8getc2`: both switch tables (80 bytes, all 20 relocations), the 16-byte search-order table, and metadata payloads match. Target `.sdata2` and `.sbss2` are each eight bytes; source sections are each four. The target PY symbol itself is four bytes, leaving an unnamed zero tail. The target ZY symbol is recorded as eight, while its real twelve-bit-field type and exact setter use a single four-byte word. Whether the remaining zero bytes reflect extraction/alignment or an unavailable original type remains uncertain. No padding or invented field was added.
- `zi8dawg`: all 120 data/metadata payload bytes match.

Raw data comparison and relocation tuples:

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
extabindex target/source bytes 120 120 equal False relocations equal False
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

Each evaluation rebuilt only its object, checked the pool before ctxdiff, and generated fresh objdiff. The successful body snapshots and full per-attempt diffs remain in `/tmp/zi8round3`; this log records the source change and measured result.

```text
zi8dawg Zi8MatchROMdata1 attempt 1: signed group selector with preserved byte-mask comparison; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; POOL IDENTICAL, no strings
zi8dawg Zi8MatchROMdata1 attempt 2: native unsigned table address alongside long-width result; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; POOL IDENTICAL, no strings
zi8dawg Zi8MatchROMdata1 attempt 3: split null group test into explicit matching label after initialization; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 1: read-only key table parameter retains byte record layout; fuzzy 99.49152; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 2: explicit typed work parameter for Korean table lookup; fuzzy 99.49152; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 3: compare decoded key through its actual halfword type; fuzzy 97.79661; src 0xf0 base 0xec insns 60/59; --- replace mine 7:8 base 7:8; POOL IDENTICAL, no strings
zi8getc2 Zi8IsDupWChar attempt 1: copy input character into local halfword before duplicate scanning; fuzzy 96.650795; src 0x100 base 0xfc insns 64/63; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 2: keep duplicate result as promoted word through scan and final return; fuzzy 98.492065; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 3: initialize duplicate flag at declaration before buffer/cursor declarations; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetDataSignature attempt 1: keep signature length as full-width table count until byte/table conversions; fuzzy 92.753624; src 0x108 base 0x114 insns 66/69; --- replace mine 5:6 base 5:6; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetDataSignature attempt 2: explicit zero-length rejection before capacity rejection; fuzzy 99.347824; src 0x114 base 0x114 insns 69/69; diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetDataSignature attempt 3: promote language parameter and narrow only at byte helper boundaries; fuzzy 99.347824; src 0x114 base 0x114 insns 69/69; diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
INVALID NO-OP (function-span regex selected a call block; excluded from real attempt count): zi8match Zi8GetPyFinal attempt 1: read final metadata through flat byte representation of the whole table; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
INVALID NO-OP (function-span regex selected a call block; excluded from real attempt count): zi8match Zi8GetPyFinal attempt 2: evaluate final-code store before initial-code store; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
INVALID NO-OP (function-span regex selected a call block; excluded from real attempt count): zi8match Zi8GetPyFinal attempt 3: combine byte index reset with successful row advance; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 1: capture insertion index pointer as a local before candidate membership scan; fuzzy 97.13793; src 0xec base 0xe8 insns 59/58; --- replace mine 0:1 base 0:1; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 2: initialize scan cursor before the first error callback; fuzzy 93.86207; src 0xe4 base 0xe8 insns 57/58; --- replace mine 7:8 base 7:8; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 3: return from in-range insertion arm before resetting wrapped cursor; fuzzy 95.43104; src 0xf0 base 0xe8 insns 60/58; --- replace mine 7:8 base 7:8; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 1: native unsigned packed key word removes long-to-byte initialization coercion; fuzzy 99.067055; src 0x55c base 0x55c insns 343/343; diffs 318: [9, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34]; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 2: restore halfword narrowing in final remaining-candidate subtraction; fuzzy 99.3586; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 3: evaluate typed record index before table base in decoded candidate lookup; fuzzy 99.3586; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 4: separate packed-prefix word and suffix byte clears; fuzzy 99.3586; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 5: discard prefix-store result before assigning zero suffix byte; fuzzy 98.379005; src 0x56c base 0x55c insns 347/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 6: chain suffix byte assignment into prefix word clear; fuzzy 98.77551; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 7: retain table API integer address until typed record decoding; fuzzy 99.3586; src 0x560 base 0x55c insns 344/343; --- replace mine 9:10 base 9:10; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 1: capture read-only scratch candidate array after initial error callback; fuzzy 91.78723; src 0xc0 base 0xbc insns 48/47; --- replace mine 6:8 base 6:7; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 2: promote candidate key parameter with halfword comparison at scratch lookup; fuzzy 96.489365; src 0xbc base 0xbc insns 47/47; diffs 10: [6, 7, 13, 22, 24, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 3: split found-candidate return from unsuccessful scan continuation; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483264 attempt 1: cache candidate capacity after validating scratch storage; fuzzy 87.29269; src 0xb4 base 0xa4 insns 45/41; --- replace mine 6:10 base 6:9; POOL IDENTICAL, no strings
zkokeyp Zi8_81483264 attempt 2: describe scratch entries as single-character records; fuzzy 98.902435; src 0xa4 base 0xa4 insns 41/41; diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]; POOL IDENTICAL, no strings
zkokeyp Zi8_81483264 attempt 3: assign next scan cursor through a compound byte update; fuzzy 96.21951; src 0xa8 base 0xa4 insns 42/41; --- replace mine 6:7 base 6:7; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 1: restore oversized input return, pass-selection arm order and collision-scan blocks; fuzzy 92.42601; src 0xa8c base 0xa74 insns 675/669; --- insert mine 14:14 base 14:15; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 2: restore materialized candidate postincrements and promoted halfword node-byte decoding; fuzzy 94.16741; src 0xa94 base 0xa74 insns 677/669; --- delete mine 13:15 base 13:13; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 3: restore skip-count-first word arm, count-mode-first overflow arms and assignment-result comparisons; fuzzy 97.59342; src 0xa88 base 0xa74 insns 674/669; --- delete mine 11:13 base 11:11; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 4: native unsigned integer lookup result at definition; fuzzy 99.49152; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 4: native unsigned integer lookup result at word search assignments; fuzzy 97.59342; src 0xa88 base 0xa74 insns 674/669; --- delete mine 11:13 base 11:11; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 5: signed integer lookup result at definition; fuzzy 99.49152; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 5: signed integer lookup result at word search assignments; fuzzy 97.59342; src 0xa88 base 0xa74 insns 674/669; --- delete mine 11:13 base 11:11; POOL IDENTICAL, no strings
zkokeyp Zi8_8148302C attempt 6: signed long lookup result at definition; fuzzy 99.49152; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 6: signed long lookup result at word search assignments; fuzzy 97.59342; src 0xa88 base 0xa74 insns 674/669; --- delete mine 11:13 base 11:11; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 7: retain integer Korean key table address for offset-first typed record accesses; fuzzy 97.59342; src 0xa88 base 0xa74 insns 674/669; --- delete mine 11:13 base 11:11; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 8: restore packed-prefix word clear before tail-byte clear; fuzzy 97.89238; src 0xa88 base 0xa74 insns 674/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 9: restore unmatched-prefix remaining count before cursor restart; fuzzy 97.09716; src 0xa88 base 0xa74 insns 674/669; --- replace mine 11:13 base 11:13; POOL IDENTICAL, no strings
zprepare Zi8PrepareMatch attempt 1: store bpmf result byte before checking return; fuzzy 86.36383; src 0xf0c base 0xeb0 insns 963/940; --- replace mine 9:13 base 9:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 2: success branch first and save previous phonetic before output; fuzzy 90.935104; src 0xf0c base 0xeb0 insns 963/940; --- replace mine 9:13 base 9:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 3: compound nibble updates preserve evaluated array addresses; fuzzy 93.42021; src 0xe84 base 0xeb0 insns 929/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 4: keep prefix full assignments and promote high stroke before or; fuzzy 94.355316; src 0xea8 base 0xeb0 insns 938/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 5: mask chosen final phonetic inside each arm and decode low byte first; fuzzy 96.09787; src 0xeac base 0xeb0 insns 939/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 6: phonetic restoration initial before final and direct segment exit; fuzzy 96.04681; src 0xeb4 base 0xeb0 insns 941/940; --- replace mine 11:13 base 11:13; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8match Zi8MatchPhonetic attempt 1: unsigned partial flag and direct increment comparison; fuzzy 86.4876; src 0x590 base 0x5ac insns 356/363; --- replace mine 5:10 base 5:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 2: restore node sound index state before node sound address decode; fuzzy 89.812675; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 3: string mismatch skip arm before matched part continuation; fuzzy 97.09642; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 4: table address first when decoding packed sound offset; fuzzy 97.2011; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 5: separate strict boundary checks in partial matching arm; fuzzy 97.2011; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 6: typed twelve-byte dictionary records for sound lookups; fuzzy 97.2011; src 0x5b8 base 0x5ac insns 366/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 1: restore shared conversion byte and alternate initial state and first output copies; fuzzy 80.3078; src 0xb1c base 0xb38 insns 711/718; --- replace mine 5:12 base 5:12; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 2: partial final first and chain invalid outputs and normalized extension subtraction; fuzzy 76.92897; src 0xb18 base 0xb38 insns 710/718; --- replace mine 5:12 base 5:12; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 3: postincrement converted output indices and decrement remaining count directly; BUILD FAILED, see Zi8GetPyPhonetic-3.build
zi8match Zi8GetPyPhonetic attempt 4: postincrement converted indices and decrement remaining count directly corrected syntax; fuzzy 84.03064; src 0xb30 base 0xb38 insns 716/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 5: partial final first and complete final success before retry arm; fuzzy 90.725624; src 0xb3c base 0xb38 insns 719/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 6: chain invalid outputs and extension subtraction and result based final correction; fuzzy 91.72702; src 0xb2c base 0xb38 insns 715/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 7: extension normalization after invalid arm and normalized tone value; fuzzy 93.006966; src 0xb30 base 0xb38 insns 716/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 8: final fallback success first and tail index limit before parsing; fuzzy 97.17131; src 0xb40 base 0xb38 insns 720/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 9: decode trailing separator once into live phonetic value; fuzzy 97.6727; src 0xb44 base 0xb38 insns 721/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 10: share one tail index check between direct and extended final parse; fuzzy 98.259056; src 0xb3c base 0xb38 insns 719/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 11: increment decoded tone before merging into final; fuzzy 98.69081; src 0xb38 base 0xb38 insns 718/718; diffs 169: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 12: reorder value index and pinyin pointer declarations; fuzzy 98.69081; src 0xb38 base 0xb38 insns 718/718; diffs 169: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 13: read only text and direct dereference of first output; fuzzy 97.548744; src 0xb40 base 0xb38 insns 720/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 14: outer syllable for loop; fuzzy 98.37743; src 0xb38 base 0xb38 insns 718/718; diffs 174: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 15: explicit output pointer constant arguments; fuzzy 98.69081; src 0xb38 base 0xb38 insns 718/718; diffs 169: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings
zikorean Zi8GetKoreanCandidates attempt 1: matched candidate arm before literal fallback and remove duplicate switch limit; fuzzy 82.292404; src 0x9b0 base 0x9ac insns 620/619; --- replace mine 8:10 base 8:10; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 2: skip candidate branches first and byte candidate indices and promoted table comparisons; fuzzy 96.04039; src 0x9b8 base 0x9ac insns 622/619; --- replace mine 29:30 base 29:30; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 3: table31 skip search exits from its comparison body; fuzzy 98.68336; src 0x9b8 base 0x9ac insns 622/619; --- replace mine 29:30 base 29:30; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 4: byte candidate result count with promoted public return; fuzzy 99.135704; src 0x9b8 base 0x9ac insns 622/619; --- replace mine 29:30 base 29:30; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 5: test cached literal value from candidate assignment; fuzzy 99.88692; src 0x9ac base 0x9ac insns 619/619; diffs 7: [135, 174, 182, 426, 482, 531, 550]; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 6: base first record addresses for mapping and candidate tables; fuzzy 100.0; src 0x9ac base 0x9ac insns 619/619; diffs 0: []; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8match Zi8GetPyPhonetic attempt 16: name shared conversion byte by its count and initial code phases; fuzzy 98.604454; src 0xb38 base 0xb38 insns 718/718; diffs 229: [0, 2, 3, 7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 52, 55, 58, 61, 64, 68]; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 17: route alternate initial through complete final instead of skipping syllable; fuzzy 98.69777; src 0xb38 base 0xb38 insns 718/718; diffs 168: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 18: enter outer syllable loop at remaining count tail condition; BUILD FAILED, see Zi8GetPyPhonetic-18.build
zi8match Zi8GetPyPhonetic attempt 19: remaining count while loop and output limit at body tail; fuzzy 98.461006; src 0xb38 base 0xb38 insns 718/718; diffs 201: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 4: use signed row counter narrowed at table access; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 5: evaluate final-code store before initial-code store; fuzzy 99.01887; src 0xd4 base 0xd4 insns 53/53; diffs 12: [26, 27, 28, 29, 30, 32, 34, 35, 36, 37, 38, 40]; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 6: reset comparison byte index before advancing failed row; fuzzy 96.98113; src 0xd4 base 0xd4 insns 53/53; diffs 10: [26, 27, 28, 29, 34, 35, 36, 37, 43, 44]; POOL IDENTICAL, no strings
```

## zkokeyp exact remaining instruction differences

Initial and final raw ctxdiff are included for every open function in address order. The filter additionally has an aligned comparison after renaming the two swapped saved registers; this exposes its three structural differences instead of the raw one-instruction-shift cascade.

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
src 0x55c base 0x55c insns 343/343
diffs 318: [9, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34]
     9 M mr r25, r7
       B mr r26, r7
    16 M clrlwi r0, r0, 0x18
       B stb r0, 0x20(r1)
    17 M stb r0, 0x20(r1)
       B li r3, 0x64
    18 M li r3, 0x64
       B clrlwi r3, r3, 0x10
    19 M clrlwi r3, r3, 0x10
       B mr r4, r26
    20 M mr r4, r25
       B bl 0
    21 M bl 0
       B lbz r0, 0xc(r31)
    22 M lbz r0, 0xc(r31)
       B cmpwi r0, 0
    23 M cmpwi r0, 0
       B bne 256
    24 M bne 256
       B lhz r3, 0(r29)
    25 M lhz r3, 0(r29)
       B lbz r0, 0(r30)
    26 M lbz r0, 0(r30)
       B cmpw r3, r0
    27 M cmpw r3, r0
       B blt 88
    28 M blt 88
       B li r28, 0
    29 M li r28, 0
       B b 36
    30 M b 36
       B mr r3, r31
    31 M mr r3, r31
       B lwz r4, 0x18(r31)
    32 M lwz r4, 0x18(r31)
       B slwi r0, r28, 1
    33 M slwi r0, r28, 1
       B lhzx r4, r4, r0
    34 M lhzx r4, r4, r0
       B mr r5, r23
    35 M mr r5, r23
       B mr r6, r26
    36 M mr r6, r25
       B bl 0
    37 M bl 0
       B addi r28, r28, 1
    38 M addi r28, r28, 1
       B lbz r0, 0(r30)
    39 M lbz r0, 0(r30)
       B cmpw r28, r0
    40 M cmpw r28, r0
       B blt -40
    41 M blt -40
       B lbz r3, 0(r30)
    42 M lbz r3, 0(r30)
       B lhz r0, 0(r29)
    43 M lhz r0, 0(r29)
       B subf r0, r3, r0
    44 M subf r0, r3, r0
       B clrlwi r0, r0, 0x10
    45 M clrlwi r0, r0, 0x10
       B sth r0, 0(r29)
    46 M sth r0, 0(r29)
       B li r0, 0
    47 M li r0, 0
       B stb r0, 0(r30)
    48 M stb r0, 0(r30)
       B b 148
    49 M b 148
       B li r28, 0
    50 M li r28, 0
       B b 36
    51 M b 36
       B mr r3, r31
    52 M mr r3, r31
       B lwz r4, 0x18(r31)
    53 M lwz r4, 0x18(r31)
       B slwi r0, r28, 1
    54 M slwi r0, r28, 1
       B lhzx r4, r4, r0
    55 M lhzx r4, r4, r0
       B mr r5, r23
    56 M mr r5, r23
       B mr r6, r26
    57 M mr r6, r25
       B bl 0
    58 M bl 0
       B addi r28, r28, 1
    59 M addi r28, r28, 1
       B lhz r0, 0(r29)
    60 M lhz r0, 0(r29)
       B cmpw r28, r0
    61 M cmpw r28, r0
       B blt -40
    62 M blt -40
       B li r28, 0
    63 M li r28, 0
       B b 40
    64 M b 40
       B lwz r3, 0x18(r31)
    65 M lwz r3, 0x18(r31)
       B lhz r0, 0(r29)
    66 M lhz r0, 0(r29)
       B add r0, r0, r28
    67 M add r0, r0, r28
       B slwi r0, r0, 1
    68 M slwi r0, r0, 1
       B lhzx r4, r3, r0
    69 M lhzx r4, r3, r0
       B lwz r3, 0x18(r31)
    70 M lwz r3, 0x18(r31)
       B slwi r0, r28, 1
    71 M slwi r0, r28, 1
       B sthx r4, r3, r0
    72 M sthx r4, r3, r0
       B addi r28, r28, 1
    73 M addi r28, r28, 1
       B lhz r3, 0(r29)
    74 M lhz r3, 0(r29)
       B lbz r0, 0(r30)
    75 M lbz r0, 0(r30)
       B subf r0, r3, r0
    76 M subf r0, r3, r0
       B cmpw r28, r0
    77 M cmpw r28, r0
       B blt -52
    78 M blt -52
       B lhz r3, 0(r29)
    79 M lhz r3, 0(r29)
       B lbz r0, 0(r30)
    80 M lbz r0, 0(r30)
       B subf r0, r3, r0
    81 M subf r0, r3, r0
       B clrlwi r0, r0, 0x18
    82 M clrlwi r0, r0, 0x18
       B stb r0, 0(r30)
    83 M stb r0, 0(r30)
       B li r0, 0
    84 M li r0, 0
       B sth r0, 0(r29)
    85 M sth r0, 0(r29)
       B li r3, 1
    86 M li r3, 1
       B b 1004
    87 M b 1000
       B lbz r0, 0xc(r31)
    88 M lbz r0, 0xc(r31)
       B cmplwi r0, 9
    89 M cmplwi r0, 9
       B ble 20
    90 M ble 20
       B li r0, 0
    91 M li r0, 0
       B stb r0, 0(r30)
    92 M stb r0, 0(r30)
       B li r3, 0
    93 M li r3, 0
       B b 976
    94 M b 972
       B lbz r3, 0(r31)
    95 M lbz r3, 0(r31)
       B li r4, 9
    96 M li r4, 9
       B clrlwi r4, r4, 0x18
    97 M clrlwi r4, r4, 0x18
       B mr r5, r26
    98 M mr r5, r25
       B bl 0
    99 M bl 0
       B stw r3, 0x18(r1)
   100 M stw r3, 0x18(r1)
       B lbz r3, 0(r31)
   101 M lbz r3, 0(r31)
       B li r4, 0xa
   102 M li r4, 0xa
       B clrlwi r4, r4, 0x18
   103 M clrlwi r4, r4, 0x18
       B mr r5, r26
   104 M mr r5, r25
       B bl 0
   105 M bl 0
       B stw r3, 0x14(r1)
   106 M stw r3, 0x14(r1)
       B lwz r0, 0x18(r1)
   107 M lwz r0, 0x18(r1)
       B cmpwi r0, 0
   108 M cmpwi r0, 0
       B bne 28
   109 M bne 28
       B li r3, 0x76c
   110 M li r3, 0x76c
       B clrlwi r3, r3, 0x10
   111 M clrlwi r3, r3, 0x10
       B mr r4, r26
   112 M mr r4, r25
       B bl 0
   113 M bl 0
       B li r3, 0
   114 M li r3, 0
       B b 892
   115 M b 888
       B lwz r0, 0x14(r1)
   116 M lwz r0, 0x14(r1)
       B cmpwi r0, 0
   117 M cmpwi r0, 0
       B bne 28
   118 M bne 28
       B li r3, 0x776
   119 M li r3, 0x776
       B clrlwi r3, r3, 0x10
   120 M clrlwi r3, r3, 0x10
       B mr r4, r26
   121 M mr r4, r25
       B bl 0
   122 M bl 0
       B li r3, 0
   123 M li r3, 0
       B b 856
   124 M b 852
       B li r3, 0x12
   125 M li r3, 0x12
       B clrlwi r3, r3, 0x18
   126 M clrlwi r3, r3, 0x18
       B li r4, 9
   127 M li r4, 9
       B clrlwi r4, r4, 0x18
   128 M clrlwi r4, r4, 0x18
       B mr r5, r26
   129 M mr r5, r25
       B bl 0
   130 M bl 0
       B sth r3, 0xa(r1)
   131 M sth r3, 0xa(r1)
       B mr r3, r31
   132 M mr r3, r31
       B addi r4, r1, 0x1c
   133 M addi r4, r1, 0x1c
       B bl 0
   134 M bl 0
       B li r28, 0
   135 M li r28, 0
       B b 400
   136 M b 400
       B li r0, 1
   137 M li r0, 1
       B stb r0, 8(r1)
   138 M stb r0, 8(r1)
       B lwz r0, 0x18(r1)
   139 M lwz r0, 0x18(r1)
       B slwi r3, r28, 3
   140 M slwi r3, r28, 3
       B add r0, r0, r28
   141 M add r0, r0, r28
       B add r0, r3, r0
   142 M add r0, r3, r0
       B stw r0, 0x10(r1)
   143 M stw r0, 0x10(r1)
       B li r27, 0
   144 M li r27, 0
       B lbz r0, 0xc(r31)
   145 M lbz r0, 0xc(r31)
       B cmplwi r0, 1
   146 M cmplwi r0, 1
       B ble 92
   147 M ble 92
       B li r27, 0
   148 M li r27, 0
       B b 56
   149 M b 56
       B clrlwi r0, r27, 0x18
   150 M clrlwi r0, r27, 0x18
       B addi r3, r1, 0x1c
   151 M addi r3, r1, 0x1c
       B lbzx r0, r3, r0
   152 M lbzx r0, r3, r0
       B clrlwi r4, r0, 0x18
   153 M clrlwi r4, r0, 0x18
       B lwz r3, 0x10(r1)
   154 M lwz r3, 0x10(r1)
       B clrlwi r0, r27, 0x18
   155 M clrlwi r0, r27, 0x18
       B lbzx r0, r3, r0
   156 M lbzx r0, r3, r0
       B cmplw r4, r0
   157 M cmplw r4, r0
       B beq 16
   158 M beq 16
       B li r0, 0
   159 M li r0, 0
       B stb r0, 8(r1)
   160 M stb r0, 8(r1)
       B b 36
   161 M b 36
       B addi r27, r27, 1
   162 M addi r27, r27, 1
       B clrlwi r4, r27, 0x18
   163 M clrlwi r4, r27, 0x18
       B lbz r3, 0xc(r31)
   164 M lbz r3, 0xc(r31)
       B srwi r0, r3, 0x1f
   165 M srwi r0, r3, 0x1f
       B add r0, r0, r3
   166 M add r0, r0, r3
       B srawi r0, r0, 1
   167 M srawi r0, r0, 1
       B cmpw r4, r0
   168 M cmpw r4, r0
       B blt -76
   169 M blt -76
       B lbz r0, 8(r1)
   170 M lbz r0, 8(r1)
       B cmpwi r0, 0
   171 M cmpwi r0, 0
       B beq 80
   172 M beq 80
       B lbz r0, 0xc(r31)
   173 M lbz r0, 0xc(r31)
       B srwi r3, r0, 0x1f
   174 M srwi r3, r0, 0x1f
       B clrlwi r0, r0, 0x1f
   175 M clrlwi r0, r0, 0x1f
       B xor r0, r0, r3
   176 M xor r0, r0, r3
       B subf r0, r3, r0
   177 M subf r0, r3, r0
       B cmpwi r0, 0
   178 M cmpwi r0, 0
       B beq 52
   179 M beq 52
       B clrlwi r0, r27, 0x18
   180 M clrlwi r0, r27, 0x18
       B addi r3, r1, 0x1c
   181 M addi r3, r1, 0x1c
       B lbzx r0, r3, r0
   182 M lbzx r0, r3, r0
       B rlwinm r4, r0, 0, 0x18, 0x1b
   183 M rlwinm r4, r0, 0, 0x18, 0x1b
       B lwz r3, 0x10(r1)
   184 M lwz r3, 0x10(r1)
       B clrlwi r0, r27, 0x18
   185 M clrlwi r0, r27, 0x18
       B lbzx r0, r3, r0
   186 M lbzx r0, r3, r0
       B rlwinm r0, r0, 0, 0x18, 0x1b
   187 M rlwinm r0, r0, 0, 0x18, 0x1b
       B cmpw r4, r0
   188 M cmpw r4, r0
       B beq 12
   189 M beq 12
       B li r0, 0
   190 M li r0, 0
       B stb r0, 8(r1)
   191 M stb r0, 8(r1)
       B lbz r0, 8(r1)
   192 M lbz r0, 8(r1)
       B cmpwi r0, 0
   193 M cmpwi r0, 0
       B beq 164
   194 M beq 164
       B li r0, 0
   195 M li r0, 0
       B stb r0, 9(r1)
   196 M stb r0, 9(r1)
       B b 132
   197 M b 132
       B lwz r3, 0x18(r31)
   198 M lwz r3, 0x18(r31)
       B lbz r0, 9(r1)
   199 M lbz r0, 9(r1)
       B slwi r0, r0, 1
   200 M slwi r0, r0, 1
       B lhzx r0, r3, r0
   201 M lhzx r0, r3, r0
       B lwz r4, 0x18(r1)
   202 M lwz r4, 0x18(r1)
       B slwi r3, r28, 3
   203 M slwi r3, r28, 3
       B add r3, r3, r28
   204 M add r3, r3, r28
       B add r3, r3, r4
   205 M add r3, r4, r3
       B lbz r3, 7(r3)
   206 M lbz r3, 7(r3)
       B clrlwi r3, r3, 0x10
   207 M clrlwi r3, r3, 0x10
       B slwi r5, r3, 8
   208 M slwi r5, r3, 8
       B lwz r4, 0x18(r1)
   209 M lwz r4, 0x18(r1)
       B slwi r3, r28, 3
   210 M slwi r3, r28, 3
       B add r3, r3, r28
   211 M add r3, r3, r28
       B add r3, r3, r4
   212 M add r3, r4, r3
       B lbz r3, 8(r3)
   213 M lbz r3, 8(r3)
       B clrlwi r3, r3, 0x10
   214 M clrlwi r3, r3, 0x10
       B or r3, r5, r3
   215 M or r3, r5, r3
       B cmpw r0, r3
   216 M cmpw r0, r3
       B bne 40
   217 M bne 40
       B addi r24, r24, 1
   218 M addi r24, r24, 1
       B lwz r4, 0x18(r31)
   219 M lwz r4, 0x18(r31)
       B lbz r0, 9(r1)
   220 M lbz r0, 9(r1)
       B slwi r3, r0, 1
   221 M slwi r3, r0, 1
       B lhzx r0, r4, r3
   222 M lhzx r0, r4, r3
       B clrlwi r0, r0, 0x11
   223 M clrlwi r0, r0, 0x11
       B clrlwi r0, r0, 0x10
   224 M clrlwi r0, r0, 0x10
       B sthx r0, r4, r3
   225 M sthx r0, r4, r3
       B b 36
   226 M b 36
       B lbz r3, 9(r1)
   227 M lbz r3, 9(r1)
       B addi r0, r3, 1
   228 M addi r0, r3, 1
       B stb r0, 9(r1)
   229 M stb r0, 9(r1)
       B lbz r0, 9(r1)
   230 M lbz r0, 9(r1)
       B clrlwi r3, r0, 0x18
   231 M clrlwi r3, r0, 0x18
       B lbz r0, 0(r30)
   232 M lbz r0, 0(r30)
       B cmplw r3, r0
   233 M cmplw r3, r0
       B blt -144
   234 M blt -144
       B addi r28, r28, 1
   235 M addi r28, r28, 1
       B lhz r0, 0xa(r1)
   236 M lhz r0, 0xa(r1)
       B cmpw r28, r0
   237 M cmpw r28, r0
       B bge 20
   238 M bge 20
       B clrlwi r3, r24, 0x18
   239 M clrlwi r3, r24, 0x18
       B lbz r0, 0(r30)
   240 M lbz r0, 0(r30)
       B cmplw r3, r0
   241 M cmplw r3, r0
       B blt -420
   242 M blt -420
       B clrlwi r3, r24, 0x18
   243 M clrlwi r3, r24, 0x18
       B lhz r0, 0(r29)
   244 M lhz r0, 0(r29)
       B cmpw r3, r0
   245 M cmpw r3, r0
       B blt 208
   246 M blt 208
       B lbz r24, 0(r30)
   247 M lbz r24, 0(r30)
       B li r0, 0
   248 M li r0, 0
       B stb r0, 0(r30)
   249 M stb r0, 0(r30)
       B li r25, 0
   250 M li r26, 0
       B b 164
   251 M b 164
       B lwz r3, 0x18(r31)
   252 M lwz r3, 0x18(r31)
       B slwi r0, r25, 1
   253 M slwi r0, r26, 1
       B lhzx r0, r3, r0
   254 M lhzx r0, r3, r0
       B rlwinm r0, r0, 0, 0x10, 0x10
   255 M rlwinm r0, r0, 0, 0x10, 0x10
       B cmpwi r0, 0
   256 M cmpwi r0, 0
       B bne 136
   257 M bne 136
       B lwz r4, 0x18(r31)
   258 M lwz r4, 0x18(r31)
       B slwi r3, r25, 1
   259 M slwi r3, r26, 1
       B lhzx r0, r4, r3
   260 M lhzx r0, r4, r3
       B ori r0, r0, 0x8000
   261 M ori r0, r0, 0x8000
       B clrlwi r0, r0, 0x10
   262 M clrlwi r0, r0, 0x10
       B sthx r0, r4, r3
   263 M sthx r0, r4, r3
       B lhz r0, 0(r29)
   264 M lhz r0, 0(r29)
       B cmpwi r0, 0
   265 M cmpwi r0, 0
       B beq 48
   266 M beq 48
       B lhz r3, 0(r29)
   267 M lhz r3, 0(r29)
       B addi r0, r3, -1
   268 M addi r0, r3, -1
       B sth r0, 0(r29)
   269 M sth r0, 0(r29)
       B mr r3, r31
   270 M mr r3, r31
       B lwz r4, 0x18(r31)
   271 M lwz r4, 0x18(r31)
       B slwi r0, r25, 1
   272 M slwi r0, r26, 1
       B lhzx r4, r4, r0
   273 M lhzx r4, r4, r0
       B mr r5, r23
   274 M mr r5, r23
       B mr r6, r26
   275 M mr r6, r25
       B bl 0
   276 M bl 0
       B b 56
   277 M b 56
       B lbz r0, 0(r30)
   278 M lbz r0, 0(r30)
       B cmpw r0, r25
   279 M cmpw r0, r26
       B beq 32
   280 M beq 32
       B lwz r3, 0x18(r31)
   281 M lwz r3, 0x18(r31)
       B slwi r0, r25, 1
   282 M slwi r0, r26, 1
       B lhzx r4, r3, r0
   283 M lhzx r4, r3, r0
       B lwz r3, 0x18(r31)
   284 M lwz r3, 0x18(r31)
       B lbz r0, 0(r30)
   285 M lbz r0, 0(r30)
       B slwi r0, r0, 1
   286 M slwi r0, r0, 1
       B sthx r4, r3, r0
   287 M sthx r4, r3, r0
       B lbz r3, 0(r30)
   288 M lbz r3, 0(r30)
       B addi r0, r3, 1
   289 M addi r0, r3, 1
       B stb r0, 0(r30)
   290 M stb r0, 0(r30)
       B addi r25, r25, 1
   291 M addi r26, r26, 1
       B clrlwi r0, r24, 0x18
   292 M clrlwi r0, r24, 0x18
       B cmpw r25, r0
   293 M cmpw r26, r0
       B blt -168
   294 M blt -168
       B li r0, 0
   295 M li r0, 0
       B sth r0, 0(r29)
   296 M sth r0, 0(r29)
       B b 160
   297 M b 156
       B li r0, 0
   298 M li r0, 0
       B stw r0, 0xc(r1)
   299 M stw r0, 0xc(r1)
       B b 104
   300 M b 104
       B lwz r3, 0x18(r31)
   301 M lwz r3, 0x18(r31)
       B lwz r0, 0xc(r1)
   302 M lwz r0, 0xc(r1)
       B slwi r0, r0, 1
   303 M slwi r0, r0, 1
       B lhzx r0, r3, r0
   304 M lhzx r0, r3, r0
       B rlwinm r0, r0, 0, 0x10, 0x10
   305 M rlwinm r0, r0, 0, 0x10, 0x10
       B cmpwi r0, 0
   306 M cmpwi r0, 0
       B bne 64
   307 M bne 64
       B lwz r4, 0x18(r31)
   308 M lwz r4, 0x18(r31)
       B lwz r0, 0xc(r1)
   309 M lwz r0, 0xc(r1)
       B slwi r3, r0, 1
   310 M slwi r3, r0, 1
       B lhzx r0, r4, r3
   311 M lhzx r0, r4, r3
       B ori r0, r0, 0x8000
   312 M ori r0, r0, 0x8000
       B clrlwi r0, r0, 0x10
   313 M clrlwi r0, r0, 0x10
       B sthx r0, r4, r3
   314 M sthx r0, r4, r3
       B mr r3, r31
   315 M mr r3, r31
       B lwz r4, 0x18(r31)
   316 M lwz r4, 0x18(r31)
       B lwz r0, 0xc(r1)
   317 M lwz r0, 0xc(r1)
       B slwi r0, r0, 1
   318 M slwi r0, r0, 1
       B lhzx r4, r4, r0
   319 M lhzx r4, r4, r0
       B mr r5, r23
   320 M mr r5, r23
       B mr r6, r26
   321 M mr r6, r25
       B bl 0
   322 M bl 0
       B lwz r3, 0xc(r1)
   323 M lwz r3, 0xc(r1)
       B addi r0, r3, 1
   324 M addi r0, r3, 1
       B stw r0, 0xc(r1)
   325 M stw r0, 0xc(r1)
       B lwz r3, 0xc(r1)
   326 M lwz r3, 0xc(r1)
       B lbz r0, 0(r30)
   327 M lbz r0, 0(r30)
       B cmpw r3, r0
   328 M cmpw r3, r0
       B blt -112
   329 M blt -112
       B clrlwi r3, r24, 0x18
   330 M clrlwi r3, r24, 0x18
       B lhz r0, 0(r29)
   331 M lhz r0, 0(r29)
       B subf r0, r3, r0
   332 M subf r0, r3, r0
       B clrlwi r0, r0, 0x10
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
--- insert mine 14:14 base 14:15
  B   14 stw r0, 0x38(r1)
--- delete mine 15:17 base 16:16
  M   15 li r0, 0
  M   16 stw r0, 0x38(r1)
--- replace mine 61:62 base 60:61
  M   61 b 2428
  B   60 b 2412
--- replace mine 70:71 base 69:70
  M   70 b 2392
  B   69 b 2376
--- replace mine 87:88 base 86:87
  M   87 beq 1392
  B   86 beq 1496
--- replace mine 93:98 base 92:105
  M   93 clrlwi r4, r3, 0x10
  M   94 sth r4, 0x18(r1)
  M   95 clrlwi r3, r4, 0x10
  M   96 cmplwi r3, 0xffff
  M   97 beq 1352
  B   92 sth r3, 0x18(r1)
  B   93 clrlwi r5, r3, 0x10
  B   94 cmplwi r5, 0xffff
  B   95 beq 1344
  B   96 lhz r4, 0x18(r1)
  B   97 slwi r3, r4, 3
  B   98 lhz r0, 0x18(r1)
  B   99 add r0, r3, r0
  B  100 add r3, r0, r28
  B  101 lbz r0, 4(r3)
  B  102 rlwinm r4, r0, 0, 0x1c, 0x1c
  B  103 cmpwi r4, 0
  B  104 beq 1308
--- replace mine 101:113 base 108:111
  M  101 add r3, r28, r3
  M  102 add r3, r0, r3
  M  103 lbz r0, 4(r3)
  M  104 rlwinm r4, r0, 0, 0x1c, 0x1c
  M  105 cmpwi r4, 0
  M  106 beq 1316
  M  107 lhz r3, 0x18(r1)
  M  108 slwi r0, r3, 3
  M  109 lhz r3, 0x18(r1)
  M  110 add r0, r28, r0
  M  111 add r3, r3, r0
  M  112 lbz r5, 6(r3)
  B  108 add r0, r3, r0
  B  109 add r3, r0, r28
  B  110 lbz r6, 6(r3)
--- replace mine 114:118 base 112:116
  M  114 slwi r4, r0, 3
  M  115 lhz r3, 0x18(r1)
  M  116 add r0, r28, r4
  M  117 add r4, r3, r0
  B  112 slwi r3, r0, 3
  B  113 lhz r0, 0x18(r1)
  B  114 add r0, r3, r0
  B  115 add r4, r0, r28
--- replace mine 120:126 base 118:124
  M  120 slwi r4, r0, 0x10
  M  121 lhz r3, 0x18(r1)
  M  122 slwi r0, r3, 3
  M  123 lhz r3, 0x18(r1)
  M  124 add r0, r28, r0
  M  125 add r3, r3, r0
  B  118 slwi r5, r0, 0x10
  B  119 lhz r4, 0x18(r1)
  B  120 slwi r3, r4, 3
  B  121 lhz r0, 0x18(r1)
  B  122 add r0, r3, r0
  B  123 add r3, r0, r28
--- replace mine 128:130 base 126:128
  M  128 or r0, r4, r0
  M  129 or r4, r5, r0
  B  126 or r0, r5, r0
  B  127 or r4, r6, r0
--- replace mine 140:141 base 138:139
  M  140 b 184
  B  138 b 180
--- replace mine 148:152 base 146:148
  M  148 clrlwi r0, r3, 0x10
  M  149 sth r0, 0x18(r1)
  M  150 lhz r0, 0x18(r1)
  M  151 clrlwi r4, r0, 0x10
  B  146 sth r3, 0x18(r1)
  B  147 lhz r4, 0x18(r1)
--- insert mine 153:153 base 149:150
  B  149 clrlwi r0, r0, 0x10
--- insert mine 156:156 base 153:154
  B  153 clrlwi r0, r0, 0x10
--- replace mine 157:159 base 155:156
  M  157 clrlwi r0, r3, 0x10
  M  158 cmplw r4, r0
  B  155 cmpw r4, r3
--- replace mine 161:163 base 158:160
  M  161 addi r3, r3, -1
  M  162 stb r3, 0xe(r1)
  B  158 addi r0, r3, -1
  B  159 stb r0, 0xe(r1)
--- replace mine 164:166 base 161:163
  M  164 addi r0, r3, 1
  M  165 stb r0, 0xd(r1)
  B  161 addi r3, r3, 1
  B  162 stb r3, 0xd(r1)
--- replace mine 172:176 base 169:173
  M  172 clrlwi r3, r0, 0x18
  M  173 stb r3, 0xe(r1)
  M  174 li r0, 1
  M  175 stb r0, 0xd(r1)
  B  169 clrlwi r0, r0, 0x18
  B  170 stb r0, 0xe(r1)
  B  171 li r3, 1
  B  172 stb r3, 0xd(r1)
--- replace mine 181:184 base 178:181
  M  181 lbz r4, 0x14(r31)
  M  182 addi r0, r4, -1
  M  183 clrlwi r0, r0, 0x18
  B  178 lbz r3, 0x14(r31)
  B  179 addi r4, r3, -1
  B  180 clrlwi r0, r4, 0x18
--- replace mine 188:189 base 185:186
  M  188 bne -188
  B  185 bne -184
--- replace mine 191:193 base 188:191
  M  191 bne 916
  M  192 lbz r3, 0(r29)
  B  188 bne 912
  B  189 lbz r0, 0(r29)
  B  190 clrlwi r3, r0, 0x10
--- replace mine 195:201 base 193:197
  M  195 lbz r6, 1(r29)
  M  196 or r5, r0, r6
  M  197 clrlwi r4, r5, 0x10
  M  198 sth r4, 0x18(r1)
  M  199 lhz r4, 0x18(r1)
  M  200 slwi r0, r4, 3
  B  193 lbz r5, 1(r29)
  B  194 or r4, r0, r5
  B  195 clrlwi r3, r4, 0x10
  B  196 sth r3, 0x18(r1)
--- replace mine 202:204 base 198:202
  M  202 add r0, r28, r0
  M  203 add r3, r3, r0
  B  198 slwi r3, r3, 3
  B  199 lhz r0, 0x18(r1)
  B  200 add r0, r3, r0
  B  201 add r3, r0, r28
--- replace mine 205:208 base 203:205
  M  205 slwi r5, r0, 8
  M  206 lhz r0, 0x18(r1)
  M  207 slwi r4, r0, 3
  B  203 clrlwi r0, r0, 0x10
  B  204 slwi r4, r0, 8
--- replace mine 209:213 base 206:212
  M  209 add r0, r28, r4
  M  210 add r3, r3, r0
  M  211 lbz r3, 8(r3)
  M  212 or r0, r5, r3
  B  206 slwi r0, r3, 3
  B  207 lhz r3, 0x18(r1)
  B  208 add r0, r0, r3
  B  209 add r3, r0, r28
  B  210 lbz r0, 8(r3)
  B  211 or r0, r4, r0
--- replace mine 217:218 base 216:217
  M  217 bne 476
  B  216 bne 468
--- replace mine 236:237 base 235:236
  M  236 b 780
  B  235 b 768
--- replace mine 241:242 base 240:241
  M  241 bne 160
  B  240 bne 156
--- replace mine 244:245 base 243:248
  M  244 bne 132
  B  243 beq 20
  B  244 lhz r3, 0x10(r1)
  B  245 addi r0, r3, -1
  B  246 sth r0, 0x10(r1)
  B  247 b 676
--- replace mine 247:248 base 250:251
  M  247 beq 40
  B  250 beq 36
--- replace mine 249:252 base 252:254
  M  249 addi r0, r3, 1
  M  250 stw r0, 0x24(r1)
  M  251 lwz r3, 0x24(r1)
  B  252 addi r3, r3, 1
  B  253 stw r3, 0x24(r1)
--- replace mine 254:255 base 256:257
  M  254 blt 664
  B  256 blt 640
--- replace mine 256:260 base 258:263
  M  256 b 1648
  M  257 lhz r4, 0x14(r1)
  M  258 lwz r3, 0x18(r31)
  M  259 lbz r0, 0xc(r1)
  B  258 b 1620
  B  259 lhz r5, 0x14(r1)
  B  260 lwz r4, 0x18(r31)
  B  261 lbz r3, 0xc(r1)
  B  262 clrlwi r0, r3, 0x18
--- replace mine 261:263 base 264:265
  M  261 sthx r4, r3, r0
  M  262 lbz r3, 0xc(r1)
  B  264 sthx r5, r4, r0
--- replace mine 274:275 base 276:277
  M  274 blt 584
  B  276 blt 560
--- replace mine 276:284 base 278:283
  M  276 b 1568
  M  277 lhz r3, 0x10(r1)
  M  278 addi r0, r3, -1
  M  279 sth r0, 0x10(r1)
  M  280 b 560
  M  281 lhz r4, 0x14(r1)
  M  282 lwz r3, 0x18(r31)
  M  283 lbz r0, 0xc(r1)
  B  278 b 1540
  B  279 lhz r5, 0x14(r1)
  B  280 lwz r4, 0x18(r31)
  B  281 lbz r3, 0xc(r1)
  B  282 clrlwi r0, r3, 0x18
--- replace mine 285:287 base 284:285
  M  285 sthx r4, r3, r0
  M  286 lbz r3, 0xc(r1)
  B  284 sthx r5, r4, r0
--- replace mine 298:299 base 296:297
  M  298 blt 488
  B  296 blt 480
--- insert mine 309:309 base 307:309
  B  307 lbz r0, 0xc(r1)
  B  308 clrlwi r3, r0, 0x18
--- delete mine 310:312 base 310:310
  M  310 clrlwi r3, r0, 0x18
  M  311 lbz r0, 0xc(r1)
--- replace mine 313:314 base 311:312
  M  313 bgt 428
  B  311 blt 420
--- replace mine 316:319 base 314:315
  M  316 bne 12
  M  317 lbz r3, 0xc(r1)
  M  318 b 1400
  B  314 beq 68
--- replace mine 321:325 base 317:320
  M  321 add r0, r3, r0
  M  322 stw r0, 0x24(r1)
  M  323 lwz r3, 0xc(r30)
  M  324 lwz r0, 0x24(r1)
  B  317 add r3, r3, r0
  B  318 stw r3, 0x24(r1)
  B  319 lwz r0, 0xc(r30)
--- replace mine 326:327 base 321:322
  M  326 bgt 12
  B  321 blt 12
--- replace mine 335:336 base 330:333
  M  335 b 340
  B  330 b 344
  B  331 lbz r3, 0xc(r1)
  B  332 b 1324
--- replace mine 338:346 base 335:336
  M  338 b 16
  M  339 lwz r3, 0x20(r1)
  M  340 addi r0, r3, 1
  M  341 stw r0, 0x20(r1)
  M  342 lwz r3, 0x20(r1)
  M  343 lbz r0, 0xc(r1)
  M  344 cmpw r3, r0
  M  345 bge 36
  B  335 b 48
--- replace mine 353:354 base 343:347
  M  353 bne -56
  B  343 beq 32
  B  344 lwz r3, 0x20(r1)
  B  345 addi r0, r3, 1
  B  346 stw r0, 0x20(r1)
--- replace mine 357:358 base 350:355
  M  357 bne 252
  B  350 blt -56
  B  351 lwz r3, 0x20(r1)
  B  352 lbz r0, 0xc(r1)
  B  353 cmpw r3, r0
  B  354 bne 248
--- replace mine 363:367 base 360:365
  M  363 bne 228
  M  364 lhz r4, 0x14(r1)
  M  365 lwz r3, 0x18(r31)
  M  366 lbz r0, 0xc(r1)
  B  360 bne 224
  B  361 lhz r5, 0x14(r1)
  B  362 lwz r4, 0x18(r31)
  B  363 lbz r3, 0xc(r1)
  B  364 clrlwi r0, r3, 0x18
--- replace mine 368:370 base 366:367
  M  368 sthx r4, r3, r0
  M  369 lbz r3, 0xc(r1)
  B  366 sthx r5, r4, r0
--- replace mine 381:382 base 378:379
  M  381 blt 156
  B  378 blt 152
--- insert mine 392:392 base 389:391
  B  389 lbz r0, 0xc(r1)
  B  390 clrlwi r3, r0, 0x18
--- delete mine 393:395 base 392:392
  M  393 clrlwi r3, r0, 0x18
  M  394 lbz r0, 0xc(r1)
--- replace mine 396:397 base 393:394
  M  396 bgt 96
  B  393 blt 92
--- replace mine 399:402 base 396:397
  M  399 bne 12
  M  400 lbz r3, 0xc(r1)
  M  401 b 1068
  B  396 beq 68
--- replace mine 404:406 base 399:404
  M  404 add r0, r3, r0
  M  405 stw r0, 0x24(r1)
  B  399 add r3, r3, r0
  B  400 stw r3, 0x24(r1)
  B  401 lwz r0, 0xc(r30)
  B  402 cmpw r3, r0
  B  403 blt 12
--- replace mine 407:412 base 405:406
  M  407 lwz r0, 0x24(r1)
  M  408 cmpw r3, r0
  M  409 bgt 12
  M  410 lwz r3, 0xc(r30)
  M  411 b 1028
  B  405 b 1032
--- replace mine 418:419 base 412:415
  M  418 b 8
  B  412 b 16
  B  413 lbz r3, 0xc(r1)
  B  414 b 996
--- replace mine 434:435 base 430:431
  M  434 beq -992
  B  430 beq -988
--- replace mine 439:440 base 435:436
  M  439 beq 104
  B  435 beq 100
--- replace mine 448:449 base 444:445
  M  448 beq 52
  B  444 beq 48
--- replace mine 451:454 base 447:449
  M  451 add r0, r3, r0
  M  452 stw r0, 0x24(r1)
  M  453 lwz r3, 0x24(r1)
  B  447 add r3, r3, r0
  B  448 stw r3, 0x24(r1)
--- replace mine 459:461 base 454:456
  M  459 lwz r0, 0x24(r1)
  M  460 stw r0, 0x2c(r1)
  B  454 lwz r3, 0x24(r1)
  B  455 stw r3, 0x2c(r1)
--- replace mine 466:468 base 461:467
  M  466 cmplwi r0, 0xa
  M  467 bge 772
  B  461 cmplwi r0, 9
  B  462 ble 20
  B  463 li r0, 0
  B  464 stb r0, 0x21(r31)
  B  465 li r3, 0
  B  466 b 788
--- replace mine 470:471 base 469:470
  M  470 beq 16
  B  469 beq 28
--- replace mine 473:475 base 472:474
  M  473 beq 16
  M  474 li r0, 1
  B  472 bne 16
  B  473 li r0, 0
--- replace mine 477:478 base 476:477
  M  477 li r0, 0
  B  476 li r0, 1
--- replace mine 491:492 base 490:491
  M  491 b 632
  B  490 b 628
--- replace mine 504:505 base 503:504
  M  504 ble 108
  B  503 ble 104
--- replace mine 507:508 base 506:507
  M  507 b 68
  B  506 b 64
--- replace mine 511:516 base 510:515
  M  511 clrlwi r4, r3, 0x18
  M  512 lwz r3, 0x1c(r1)
  M  513 lbz r0, 0xb(r1)
  M  514 lbzx r3, r3, r0
  M  515 cmplw r4, r3
  B  510 clrlwi r5, r3, 0x18
  B  511 lwz r4, 0x1c(r1)
  B  512 lbz r3, 0xb(r1)
  B  513 lbzx r0, r4, r3
  B  514 cmplw r5, r0
--- replace mine 519:520 base 518:519
  M  519 b 48
  B  518 b 44
--- replace mine 521:523 base 520:521
  M  521 addi r3, r3, 1
  M  522 clrlwi r0, r3, 0x18
  B  520 addi r0, r3, 1
--- replace mine 525:531 base 523:529
  M  525 lbz r3, 0xc(r31)
  M  526 srwi r0, r3, 0x1f
  M  527 add r3, r0, r3
  M  528 srawi r0, r3, 1
  M  529 cmplw r4, r0
  M  530 blt -88
  B  523 lbz r0, 0xc(r31)
  B  524 srwi r3, r0, 0x1f
  B  525 add r0, r3, r0
  B  526 srawi r0, r0, 1
  B  527 cmpw r4, r0
  B  528 blt -84
--- replace mine 534:539 base 532:537
  M  534 lbz r5, 0xc(r31)
  M  535 srwi r4, r5, 0x1f
  M  536 clrlwi r3, r5, 0x1f
  M  537 xor r0, r3, r4
  M  538 subf r0, r4, r0
  B  532 lbz r6, 0xc(r31)
  B  533 srwi r3, r6, 0x1f
  B  534 clrlwi r0, r6, 0x1f
  B  535 xor r0, r0, r3
  B  536 subf r0, r3, r0
--- replace mine 544:550 base 542:548
  M  544 rlwinm r4, r0, 0, 0x18, 0x1b
  M  545 lwz r3, 0x1c(r1)
  M  546 lbz r0, 0xb(r1)
  M  547 lbzx r3, r3, r0
  M  548 rlwinm r0, r3, 0, 0x18, 0x1b
  M  549 cmpw r4, r0
  B  542 rlwinm r5, r0, 0, 0x18, 0x1b
  B  543 lwz r4, 0x1c(r1)
  B  544 lbz r3, 0xb(r1)
  B  545 lbzx r0, r4, r3
  B  546 rlwinm r0, r0, 0, 0x18, 0x1b
  B  547 cmpw r5, r0
--- replace mine 581:585 base 579:583
  M  581 lbz r0, 0xb(r1)
  M  582 lbzx r0, r3, r0
  M  583 rlwinm r4, r0, 0, 0x18, 0x1b
  M  584 cmpwi r4, 0
  B  579 lbz r4, 0xb(r1)
  B  580 lbzx r0, r3, r4
  B  581 rlwinm r0, r0, 0, 0x18, 0x1b
  B  582 cmpwi r0, 0
--- replace mine 590:591 base 588:592
  M  590 lbz r0, 0xa(r1)
  B  588 lbz r3, 0xa(r1)
  B  589 cmpwi r3, 0
  B  590 beq 16
  B  591 lbz r0, 0(r30)
--- delete mine 592:595 base 593:593
  M  592 beq 16
  M  593 lbz r3, 0(r30)
  M  594 cmpwi r3, 0
--- replace mine 600:602 base 598:600
  M  600 addi r0, r3, -1
  M  601 sth r0, 0x10(r1)
  B  598 addi r3, r3, -1
  B  599 sth r3, 0x10(r1)
--- replace mine 603:605 base 601:603
  M  603 lbz r3, 0(r30)
  M  604 cmpwi r3, 0
  B  601 lbz r0, 0(r30)
  B  602 cmpwi r0, 0
--- replace mine 613:614 base 611:612
  M  613 b 220
  B  611 b 208
--- replace mine 615:619 base 613:617
  M  615 slwi r0, r0, 3
  M  616 lwz r3, 0x30(r1)
  M  617 add r0, r28, r0
  M  618 add r3, r3, r0
  B  613 slwi r3, r0, 3
  B  614 lwz r0, 0x30(r1)
  B  615 add r0, r3, r0
  B  616 add r3, r0, r28
--- replace mine 620:622 base 618:620
  M  620 clrlwi r0, r0, 0x10
  M  621 slwi r4, r0, 8
  B  618 clrlwi r3, r0, 0x10
  B  619 slwi r4, r3, 8
--- replace mine 623:627 base 621:625
  M  623 slwi r0, r0, 3
  M  624 lwz r3, 0x30(r1)
  M  625 add r0, r28, r0
  M  626 add r3, r3, r0
  B  621 slwi r3, r0, 3
  B  622 lwz r0, 0x30(r1)
  B  623 add r0, r3, r0
  B  624 add r3, r0, r28
--- replace mine 629:637 base 627:635
  M  629 clrlwi r6, r0, 0x10
  M  630 lwz r5, 0x18(r31)
  M  631 lbz r4, 0xc(r1)
  M  632 clrlwi r3, r4, 0x18
  M  633 slwi r0, r3, 1
  M  634 sthx r6, r5, r0
  M  635 addi r0, r4, 1
  M  636 stb r0, 0xc(r1)
  B  627 clrlwi r5, r0, 0x10
  B  628 lwz r4, 0x18(r31)
  B  629 lbz r3, 0xc(r1)
  B  630 clrlwi r0, r3, 0x18
  B  631 slwi r0, r0, 1
  B  632 sthx r5, r4, r0
  B  633 addi r3, r3, 1
  B  634 stb r3, 0xc(r1)
--- replace mine 640:643 base 638:641
  M  640 clrlwi r5, r0, 0x18
  M  641 lbz r0, 0x1c(r31)
  M  642 cmplw r5, r0
  B  638 clrlwi r0, r0, 0x18
  B  639 lbz r4, 0x1c(r31)
  B  640 cmplw r0, r4
--- replace mine 645:653 base 643:651
  M  645 b 92
  M  646 lwz r4, 0x30(r1)
  M  647 addi r3, r4, 1
  M  648 stw r3, 0x30(r1)
  M  649 lwz r0, 0x30(r1)
  M  650 lhz r3, 0x16(r1)
  M  651 cmpw r0, r3
  M  652 blt -640
  B  643 b 80
  B  644 lwz r3, 0x30(r1)
  B  645 addi r0, r3, 1
  B  646 stw r0, 0x30(r1)
  B  647 lwz r3, 0x30(r1)
  B  648 lhz r0, 0x16(r1)
  B  649 cmpw r3, r0
  B  650 blt -636
--- replace mine 658:662 base 656:657
  M  658 blt -676
  M  659 b 12
  M  660 li r0, 0
  M  661 stb r0, 0x21(r31)
  B  656 blt -672
```

Final:

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

Filter register-normalized structural comparison:

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
--- replace mine 296:297 base 299:300
  M  296 lhzx r0, r5, r0
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
--- replace mine 578:585 base 581:586
  M  578 addi r0, r3, 1
  M  579 stb r0, 0x6c(r31)
  M  580 lbz r0, 0xc(r1)
  M  581 cmplwi r0, 0xff
  M  582 bne 1400
  M  583 lbz r3, 0xe(r1)
  M  584 clrlwi r3, r3, 0x18
  B  581 addi r3, r3, 1
  B  582 stb r3, 0x6c(r31)
  B  583 lbz r3, 0xc(r1)
  B  584 cmplwi r3, 0xff
  B  585 bne 108
--- insert mine 586:586 base 587:589
  B  587 clrlwi r3, r0, 0x18
  B  588 lbz r0, 0xe(r1)
--- replace mine 587:591 base 590:594
  M  587 ble 1380
  M  588 lbz r3, 0x6c(r31)
  M  589 cmplwi r3, 0xf
  M  590 bgt 1368
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
  M  793 addi r0, r3, -1
  M  794 slwi r0, r0, 1
  M  795 add r0, r4, r0
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

### Zi8MatchPhonetic

```text
src 0x5b8 base 0x5ac insns 366/363
--- replace mine 6:10 base 6:10
  M    6 stw r4, 8(r1)
  M    7 stw r5, 0xc(r1)
  M    8 sth r6, 0x10(r1)
  M    9 stw r7, 0x14(r1)
  B    6 mr r17, r4
  B    7 stw r5, 8(r1)
  B    8 sth r6, 0xc(r1)
  B    9 stw r7, 0x10(r1)
--- delete mine 16:17 base 16:16
  M   16 lbz r17, 0x8b(r1)
--- replace mine 27:28 base 26:27
  M   27 stb r0, 0x18(r1)
  B   26 stb r0, 0x14(r1)
--- replace mine 30:31 base 29:30
  M   30 stb r0, 0x18(r1)
  B   29 stb r0, 0x14(r1)
--- replace mine 35:36 base 34:35
  M   35 sth r0, 0x22(r1)
  B   34 sth r0, 0x1e(r1)
--- replace mine 38:39 base 37:38
  M   38 sth r0, 0x22(r1)
  B   37 sth r0, 0x1e(r1)
--- replace mine 40:41 base 39:40
  M   40 stb r0, 0x1c(r1)
  B   39 stb r0, 0x18(r1)
--- replace mine 43:44 base 42:43
  M   43 beq 1240
  B   42 beq 1232
--- replace mine 46:47 base 45:46
  M   46 ble 1228
  B   45 ble 1220
--- replace mine 48:49 base 47:48
  M   48 b 1220
  B   47 b 1212
--- replace mine 55:56 base 54:55
  M   55 b 1192
  B   54 b 1184
--- replace mine 59:60 base 58:59
  M   59 sth r3, 0x24(r1)
  B   58 sth r3, 0x20(r1)
--- replace mine 61:62 base 60:61
  M   61 lhz r0, 0x24(r1)
  B   60 lhz r0, 0x20(r1)
--- replace mine 65:66 base 64:65
  M   65 beq 1124
  B   64 beq 1116
--- replace mine 68:69 base 67:68
  M   68 bne 1112
  B   67 bne 1104
--- replace mine 72:73 base 71:72
  M   72 beq 1096
  B   71 beq 1088
--- replace mine 76:77 base 75:76
  M   76 lhz r0, 0x22(r1)
  B   75 lhz r0, 0x1e(r1)
--- replace mine 80:81 base 79:80
  M   80 sth r0, 0x20(r1)
  B   79 sth r0, 0x1c(r1)
--- replace mine 82:85 base 81:84
  M   82 sth r23, 0x20(r1)
  M   83 lwz r3, 0xc(r1)
  M   84 lhz r4, 0x10(r1)
  B   81 sth r23, 0x1c(r1)
  B   82 lwz r3, 8(r1)
  B   83 lhz r4, 0xc(r1)
--- replace mine 86:87 base 85:86
  M   86 lhz r6, 0x20(r1)
  B   85 lhz r6, 0x1c(r1)
--- replace mine 92:94 base 91:93
  M   92 sth r3, 0x24(r1)
  M   93 b 1012
  B   91 sth r3, 0x20(r1)
  B   92 b 1004
--- replace mine 95:96 base 94:95
  M   95 lhz r0, 0x24(r1)
  B   94 lhz r0, 0x20(r1)
--- replace mine 101:102 base 100:101
  M  101 stb r0, 0x1c(r1)
  B  100 stb r0, 0x18(r1)
--- replace mine 105:106 base 104:105
  M  105 lhz r0, 0x22(r1)
  B  104 lhz r0, 0x1e(r1)
--- replace mine 109:110 base 108:109
  M  109 sth r0, 0x20(r1)
  B  108 sth r0, 0x1c(r1)
--- replace mine 111:116 base 110:112
  M  111 sth r23, 0x20(r1)
  M  112 lwz r4, 0x14(r1)
  M  113 lbz r0, 0xa(r30)
  M  114 slwi r3, r0, 8
  M  115 lbz r5, 0xb(r30)
  B  110 sth r23, 0x1c(r1)
  B  111 lwz r5, 0x10(r1)
--- replace mine 119:122 base 115:121
  M  119 add r3, r4, r3
  M  120 add r0, r5, r0
  M  121 add r31, r3, r0
  B  115 lbz r3, 0xb(r30)
  B  116 lbz r4, 0xa(r30)
  B  117 slwi r4, r4, 8
  B  118 add r0, r0, r3
  B  119 add r3, r5, r4
  B  120 add r31, r0, r3
--- replace mine 154:155 base 153:154
  M  154 lbz r0, 0x1c(r1)
  B  153 lbz r0, 0x18(r1)
--- replace mine 170:171 base 169:170
  M  170 lhz r0, 0x22(r1)
  B  169 lhz r0, 0x1e(r1)
--- replace mine 173:174 base 172:173
  M  173 b 748
  B  172 b 740
--- replace mine 176:178 base 175:177
  M  176 stb r0, 0x1b(r1)
  M  177 lbz r0, 0x1b(r1)
  B  175 stb r0, 0x17(r1)
  B  176 lbz r0, 0x17(r1)
--- replace mine 180:182 base 179:181
  M  180 stb r0, 0x1a(r1)
  M  181 lbz r0, 0x1b(r1)
  B  179 stb r0, 0x16(r1)
  B  180 lbz r0, 0x17(r1)
--- replace mine 185:186 base 184:185
  M  185 bne 612
  B  184 bne 604
--- replace mine 195:196 base 194:195
  M  195 lbz r3, 0x1a(r1)
  B  194 lbz r3, 0x16(r1)
--- replace mine 197:199 base 196:198
  M  197 stb r0, 0x1a(r1)
  M  198 lbz r0, 0x1a(r1)
  B  196 stb r0, 0x16(r1)
  B  197 lbz r0, 0x16(r1)
--- replace mine 201:202 base 200:201
  M  201 b 548
  B  200 b 540
--- replace mine 203:205 base 202:204
  M  203 stb r0, 0x19(r1)
  M  204 lbz r0, 0x18(r1)
  B  202 stb r0, 0x15(r1)
  B  203 lbz r0, 0x14(r1)
--- replace mine 211:213 base 210:212
  M  211 stb r0, 0x18(r1)
  M  212 lbz r0, 0x18(r1)
  B  210 stb r0, 0x14(r1)
  B  211 lbz r0, 0x14(r1)
--- replace mine 222:223 base 221:222
  M  222 sth r0, 0x1e(r1)
  B  221 sth r0, 0x1a(r1)
--- replace mine 224:225 base 223:224
  M  224 lbz r0, 0x18(r1)
  B  223 lbz r0, 0x14(r1)
--- replace mine 226:227 base 225:226
  M  226 bne 224
  B  225 bne 216
--- replace mine 228:230 base 227:228
  M  228 lwz r4, 8(r1)
  M  229 lhz r0, 0x1e(r1)
  B  227 lhz r0, 0x1a(r1)
--- replace mine 232:233 base 230:231
  M  232 add r4, r4, r0
  B  230 add r4, r17, r0
--- replace mine 234:237 base 232:235
  M  234 sth r3, 0x24(r1)
  M  235 lhz r3, 0x24(r1)
  M  236 lbz r0, 0x19(r1)
  B  232 sth r3, 0x20(r1)
  B  233 lhz r3, 0x20(r1)
  B  234 lbz r0, 0x15(r1)
--- replace mine 240:241 base 238:239
  M  240 lbz r0, 0x19(r1)
  B  238 lbz r0, 0x15(r1)
--- replace mine 244:245 base 242:243
  M  244 beq 112
  B  242 beq 108
--- replace mine 247:250 base 245:247
  M  247 bne 100
  M  248 lwz r3, 8(r1)
  M  249 lhz r0, 0x1e(r1)
  B  245 bne 96
  B  246 lhz r0, 0x1a(r1)
--- replace mine 252:253 base 249:250
  M  252 lbzx r0, r3, r0
  B  249 lbzx r0, r17, r0
--- replace mine 256:258 base 253:255
  M  256 lwz r3, 0xc(r1)
  M  257 lhz r4, 0x10(r1)
  B  253 lwz r3, 8(r1)
  B  254 lhz r4, 0xc(r1)
--- replace mine 259:260 base 256:257
  M  259 lhz r0, 0x1e(r1)
  B  256 lhz r0, 0x1a(r1)
--- replace mine 262:263 base 259:260
  M  262 lbz r0, 0x19(r1)
  B  259 lbz r0, 0x15(r1)
--- replace mine 265:266 base 262:263
  M  265 lbz r0, 0x19(r1)
  B  262 lbz r0, 0x15(r1)
--- replace mine 271:274 base 268:271
  M  271 sth r3, 0x24(r1)
  M  272 lhz r3, 0x24(r1)
  M  273 lbz r0, 0x19(r1)
  B  268 sth r3, 0x20(r1)
  B  269 lhz r3, 0x20(r1)
  B  270 lbz r0, 0x15(r1)
--- replace mine 277:278 base 274:275
  M  277 lbz r0, 0x19(r1)
  B  274 lbz r0, 0x15(r1)
--- replace mine 282:283 base 279:280
  M  282 lhz r0, 0x1e(r1)
  B  279 lhz r0, 0x1a(r1)
--- replace mine 295:296 base 292:293
  M  295 lbz r3, 0x19(r1)
  B  292 lbz r3, 0x15(r1)
--- replace mine 297:298 base 294:295
  M  297 stb r0, 0x19(r1)
  B  294 stb r0, 0x15(r1)
--- replace mine 305:306 base 302:303
  M  305 clrlwi r0, r17, 0x18
  B  302 lbz r0, 0x8b(r1)
--- replace mine 308:309 base 305:306
  M  308 lhz r0, 0x1e(r1)
  B  305 lhz r0, 0x1a(r1)
--- replace mine 312:313 base 309:310
  M  312 clrlwi r0, r17, 0x18
  B  309 lbz r0, 0x8b(r1)
--- replace mine 315:316 base 312:313
  M  315 lhz r0, 0x1e(r1)
  B  312 lhz r0, 0x1a(r1)
--- replace mine 327:328 base 324:325
  M  327 lhz r0, 0x22(r1)
  B  324 lhz r0, 0x1e(r1)
--- replace mine 331:332 base 328:329
  M  331 lhz r0, 0x1e(r1)
  B  328 lhz r0, 0x1a(r1)
--- replace mine 334:336 base 331:333
  M  334 beq -472
  M  335 lbz r3, 0x1a(r1)
  B  331 beq -464
  B  332 lbz r3, 0x16(r1)
--- replace mine 337:339 base 334:336
  M  337 stb r0, 0x1a(r1)
  M  338 lbz r0, 0x1a(r1)
  B  334 stb r0, 0x16(r1)
  B  335 lbz r0, 0x16(r1)
--- replace mine 340:342 base 337:339
  M  340 bne -552
  M  341 lbz r0, 0x1b(r1)
  B  337 bne -544
  B  338 lbz r0, 0x17(r1)
--- replace mine 344:346 base 341:343
  M  344 beq -680
  M  345 b -1164
  B  341 bne -1152
  B  342 b -676
--- replace mine 347:348 base 344:345
  M  347 lhz r0, 0x24(r1)
  B  344 lhz r0, 0x20(r1)
--- replace mine 351:354 base 348:351
  M  351 beq -1028
  M  352 b -1192
  M  353 lhz r3, 0x22(r1)
  B  348 beq -1020
  B  349 b -1184
  B  350 lhz r3, 0x1e(r1)
--- replace mine 355:356 base 352:353
  M  355 sth r0, 0x22(r1)
  B  352 sth r0, 0x1e(r1)
--- replace mine 358:359 base 355:356
  M  358 bne -1236
  B  355 bne -1228
```

### Zi8GetPyPhonetic

```text
src 0xb38 base 0xb38 insns 718/718
diffs 168: [7, 8, 9, 13, 19, 29, 30, 32, 37, 42, 47, 58, 64, 71, 74, 83, 87, 93, 96, 97]
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
   107 M b 2316
       B b 2328
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

## Gates, changed files, and commits

[Every gate block, including all three full all-unit runs and the failed intermediate check](ezi3.round3.gates.txt). The failed intermediate check observed a pinyin frame experiment whose extab match fell from 608 to 528 total credited data bytes. It was corrected before any commit, and the subsequent checks pass with zero regressions. The final full gate rebuilt all six owned units, passed, and preserved the original DOL hash.

Changed source files:

- `libs/RVLMiddleware/eZiText/src/clib/zkokeyp.c`
- `libs/RVLMiddleware/eZiText/src/clib/zprepare.c`
- `libs/RVLMiddleware/eZiText/src/clib/zi8match.c`
- `libs/RVLMiddleware/eZiText/src/clib/zikorean.c`

New evidence files: `tools/decomp-assist/ezi3.round3.attempts.md` and `tools/decomp-assist/ezi3.round3.gates.txt`.

Code commits, oldest first:

```text
d3735de6 restore korean filter remaining count narrowing
82e761f1 restore korean word overflow and key scan blocks
34f5d8cc restore packed korean key initialization order
e3dbab57 restore prepare phonetic success blocks and nibble writes
4ea5edad restore prepare prefix masks and phonetic decoding
736373ef restore phonetic dictionary matching blocks
f0f7d424 restore pinyin conversion state and final branch order
4591ac02 restore pinyin final scan and tone normalization
12854693 restore shared pinyin scan continuation and tone write
af7de682 restore korean candidate emission and table search branches
e2176ab3 match korean candidate generation instructions
359336ca restore alternate pinyin branch and align translated blocks
```

The final evidence commit adds this report and the complete gate record; its hash is included in the final handoff.
