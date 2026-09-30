# eZiText matching attempts, 2026-09-30

Six source units; local matching only. All final string pools are identical. Six additional instruction-exact functions; remaining functions are partial.

## Before -> after

| Unit | Instruction exact | Fuzzy code | Matched code bytes | Matched data bytes |
| --- | --- | --- | --- | --- |
| zi8dawg | 2/6 -> 5/6 | 51.9523% -> 99.9754% | 536 -> 4356/4868 | 0 -> 120/120 |
| zprepare | 0/1 -> 0/1 | 64.7575% -> 82.4734% | 0 -> 0/3760 | 0 -> 8/68 |
| zkokeyp | 1/7 -> 1/7 | 76.1862% -> 81.0346% | 332 -> 332/5200 | 0 -> 0/140 |
| zi8getc2 | 11/17 -> 14/17 | 81.5273% -> 94.7933% | 1380 -> 3584/6888 | 24 -> 112/332 |
| zi8match | 7/10 -> 7/10 | 87.4123% -> 89.0165% | 3720 -> 3720/8256 | 608 -> 608/728 |
| zikorean | 2/3 -> 2/3 | 85.0925% -> 86.8605% | 2712 -> 2712/5188 | 24 -> 24/348 |

## Remaining functions

- Zi8MatchROMdata1: 99.765625%; Register allocation only (group index and table address swap registers). Logged attempts: 11.
- Zi8PrepareMatch: 82.473404%; Stack layout, stroke/phonetic basic blocks and temporaries remain different; 973 versus 940 instructions. Logged attempts: 5.
- Zi8_8148302C: 99.491520%; Register allocation only: work pointer and table count exchange r27/r29. Logged attempts: 4.
- Zi8_81483264: 98.902435%; Register allocation only: parameter pointer and byte counter exchange r30/r31. Logged attempts: 4.
- Zi8_81483308: 99.137930%; Register allocation only: insertion count pointer and byte index exchange r29/r30. Logged attempts: 4.
- Zi8_814833F0: 99.042560%; Register allocation only: parameter pointer and byte index exchange r30/r31. Logged attempts: 4.
- Zi8_814834AC: 87.938774%; 343/343 instructions, but registers, stack accesses and branch operands differ (268 changed instructions). Logged attempts: 3.
- Zi8GetKOcandidates: 69.584460%; Candidate traversal blocks and temporaries remain different; 727 versus 669 instructions. Logged attempts: 4.
- Zi8GetDataSignature: 99.347824%; Register allocation only: destination, language and signature pointer cycle through r27/r28/r29. Logged attempts: 3.
- Zi8GetCandidatesOrCount: 87.203170%; Stack frame 0x50 versus 0x60 and signature dispatch/early return order remain different; 693 versus 694 instructions. Logged attempts: 3.
- Zi8IsDupWChar: 99.365080%; Register allocation only: character and duplicate flag exchange r27/r28. Logged attempts: 3.
- Zi8MatchPhonetic: 85.950420%; Dictionary/mask registers, stack descriptor placement and nested branch order remain different; 358 versus 363 instructions. Logged attempts: 9.
- Zi8GetPyPhonetic: 75.584960%; Stack byte placement, conversion loop scheduling and phonetic branches remain different; 727 versus 718 instructions. Logged attempts: 3.
- Zi8GetPyFinal: 99.245285%; Register allocation only in final output row-address expressions (eight changed instructions). Logged attempts: 3.
- Zi8GetKoreanCandidates: 72.468500%; 621/619 instructions; expression scheduling and table/candidate branch ordering differ. Logged attempts: 3.

## Exact gains

- zi8dawg: Zi8MatchROMdata0 (522/522), Zi8MatchROMdata2 (236/236), Zi8MatchROMdata (197/197).
- zi8getc2: Zi8AlphaSignature (204/204), Zi8ZhSignature (208/208), Zi8IsDupWordW (139/139).
- Each has objdiff 100.0 and ctxdiff diffs 0 from independent final object checks.

## Scope and uncertainty

zprepare, zkokeyp, zi8match and zikorean have fuzzy improvements without increased exact-function counts. They remain partial; GATE PASS does not assert completion. Register-only differences are observed; the compiler choice causing them is unresolved. Data scores remain partial in five units. No linking changes were attempted. Runtime behavior was not tested separately; target disassembly and object comparison were the matching authority.

## Files changed

- libs/RVLMiddleware/eZiText/src/clib/zi8dawg.c
- libs/RVLMiddleware/eZiText/src/clib/zprepare.c
- libs/RVLMiddleware/eZiText/src/clib/zkokeyp.c
- libs/RVLMiddleware/eZiText/src/clib/zi8getc2.c
- libs/RVLMiddleware/eZiText/src/clib/zi8match.c
- libs/RVLMiddleware/eZiText/src/clib/zikorean.c
- tools/decomp-assist/ezi3.attempts.md
- tools/decomp-assist/ezi3.final-gate.txt

## Local source commits

```
38961b58 match dawg graph traversal
dc29ae80 match dawg segmented search
14156024 match dawg group search
cd667fb6 restore prepare match block structure
e575012c restore korean candidate filter frame and branches
a22a9876 restore korean key table traversal and options
b063bccc match latin data signature output
b36ad4ce match chinese data signature output
d004c9bc restore signed candidate language dispatch
e3d4e836 match duplicate word slot management
8b57b56d restore phonetic and korean search blocks
```

## Attempt log

Build failures are preserved. Candidate variants that failed to improve the best score were restored. The old pool tool raises KeyError on objects without .data; the gate string-reader fallback and final full gate verified their empty pools. A blank pool field in early attempts reflects that tool error, not an asserted match.

```
zi8dawg Zi8MatchROMdata0 attempt 1: translate graph traversal blocks in address order; separate key and graph tables; u8 count and u16 search state; fuzzy 98.005745; src 0x824 base 0x828 insns 521/522; --- replace mine 40:41 base 40:41; 
zi8dawg Zi8MatchROMdata0 attempt 2: unsigned key array eliminates sign extension; explicit null pointer comparisons and key-table expression order; fuzzy 99.93104; src 0x828 base 0x828 insns 522/522; diffs 18: [99, 119, 120, 179, 180, 219, 222, 224, 243, 287, 316, 329, 332, 333, 335, 336, 443, 505]; 
zi8dawg Zi8MatchROMdata0 attempt 3: reverse scalar declarations to match stack offsets; explicit signed key-count local and graph table update order; fuzzy 95.72797; src 0x828 base 0x828 insns 522/522; diffs 39: [190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209]; 
zi8dawg Zi8MatchROMdata0 attempt 4: retain for-loop ternary, reorder used scalar locals to match reverse stack allocation; fuzzy 99.950195; src 0x828 base 0x828 insns 522/522; diffs 8: [219, 222, 224, 243, 316, 329, 332, 333]; 
zi8dawg Zi8MatchROMdata0 attempt 5: explicit tail-tested key loop removes compiler temporary; compound key table update and grouped character table access; fuzzy 100.0; src 0x828 base 0x828 insns 522/522; diffs 0: []; 
zi8dawg Zi8MatchROMdata1 attempt 1: widen group index to byte type; fuzzy 98.203125; src 0x208 base 0x200 insns 130/128; --- replace mine 12:13 base 12:13; 
zi8dawg Zi8MatchROMdata1 attempt 2: inline table-address assignment; fuzzy 98.47656; src 0x1fc base 0x200 insns 127/128; --- replace mine 5:7 base 5:7; 
zi8dawg Zi8MatchROMdata1 attempt 3: use pointer local for table address; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; 
zi8dawg Zi8MatchROMdata2 attempt 1: translate success-copy then failure-prefix blocks in target order; byte loop and parameter types; switch vowel test; fuzzy 99.15254; src 0x3b0 base 0x3b0 insns 236/236; diffs 10: [172, 173, 174, 175, 176, 177, 178, 179, 180, 181]; 
zi8dawg Zi8MatchROMdata2 attempt 2: byte status prototype restores call narrowing; use unsigned result mask for segment accumulation; fuzzy 99.57627; src 0x3b4 base 0x3b0 insns 237/236; --- replace mine 21:22 base 21:22; 
zi8dawg Zi8MatchROMdata1 attempt 4: byte status parameter retains callee narrowing semantics; fuzzy 98.984375; src 0x204 base 0x200 insns 129/128; --- replace mine 12:13 base 12:13; 
zi8dawg Zi8MatchROMdata1 attempt 5: avoid duplicate byte-status mask at entry; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; 
zi8dawg Zi8MatchROMdata2 attempt 3: compound segment-length update avoids redundant conversion; fuzzy 100.0; src 0x3b0 base 0x3b0 insns 236/236; diffs 0: []; 
zi8dawg Zi8MatchROMdata attempt 1: translate group iteration and fallback in address order; explicit mode reuse and table-size initialization; fuzzy 100.0; src 0x314 base 0x314 insns 197/197; diffs 0: []; 
zi8dawg Zi8MatchROMdata1 attempt 6: declare table address before result; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; 
zi8dawg Zi8MatchROMdata1 attempt 7: test group index before group terminator; fuzzy 95.11719; src 0x200 base 0x200 insns 128/128; diffs 10: [12, 36, 37, 52, 53, 54, 55, 56, 57, 58]; 
zi8dawg Zi8MatchROMdata1 attempt 8: compare group index through byte conversion; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; 
zprepare Zi8PrepareMatch attempt 1: translate component setup and loop indices from target blocks; reconstruct byte locals and stack arrays; fuzzy 72.98404; src 0xfa4 base 0xeb0 insns 1001/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 2: remove cached returns and result local; restore shared byte loop index register and direct phonetic result storage; fuzzy 74.75319; src 0xf74 base 0xeb0 insns 989/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 3: restore independent nibble counter test; u32 nibble arithmetic, array declaration order and aligned mode scalar; fuzzy 74.42021; src 0xefc base 0xeb0 insns 959/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8dawg Zi8MatchROMdata1 attempt 9: group countdown name; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; 
zi8dawg Zi8MatchROMdata1 attempt 10: table pointer name; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; 
zi8dawg Zi8MatchROMdata1 attempt 11: remaining group counter name; fuzzy 99.765625; src 0x200 base 0x200 insns 128/128; diffs 5: [12, 36, 37, 52, 57]; 
zprepare Zi8PrepareMatch attempt 4: replace stroke decisions with target switch and odd-nibble-first blocks; remove unused component flag, use compound byte increments; fuzzy 81.4617; src 0xf48 base 0xeb0 insns 978/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zprepare Zi8PrepareMatch attempt 5: switch for component mode; use integer table-address ABI like matched siblings; fuzzy 82.473404; src 0xf34 base 0xeb0 insns 973/940; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zkokeyp Zi8_8148302C attempt 1: reverse value comparison to target operand order; fuzzy 99.49152; src 0xec base 0xec insns 59/59; diffs 6: [7, 12, 32, 34, 38, 49]; 
zkokeyp Zi8_8148302C attempt 2: scope decoded table value inside loop; fuzzy 89.81356; src 0xf8 base 0xec insns 62/59; --- replace mine 5:9 base 5:8; 
zkokeyp Zi8_8148302C attempt 3: use byte table index directly as u16; fuzzy 90.50848; src 0xfc base 0xec insns 63/59; --- replace mine 7:8 base 7:8; 
zkokeyp Zi8_8148302C attempt 4: reduce key-table arithmetic to nine-byte entries; fuzzy 94.40678; src 0xe4 base 0xec insns 57/59; --- replace mine 7:8 base 7:8; 
zkokeyp Zi8_81483264 attempt 1: widen loop variable and narrow at table accesses; fuzzy 98.902435; src 0xa4 base 0xa4 insns 41/41; diffs 8: [6, 8, 17, 20, 21, 24, 25, 26]; 
zkokeyp Zi8_81483264 attempt 2: initialize loop index in declaration and use while loop; fuzzy 86.82927; src 0xa4 base 0xa4 insns 41/41; diffs 18: [8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 28]; 
zkokeyp Zi8_81483308 attempt 1: widen loop variable and narrow at table accesses; fuzzy 99.13793; src 0xe8 base 0xe8 insns 58/58; diffs 9: [7, 22, 26, 33, 34, 39, 42, 44, 50]; 
zkokeyp Zi8_81483308 attempt 2: initialize loop index in declaration and use while loop; fuzzy 93.86207; src 0xe4 base 0xe8 insns 57/58; --- replace mine 7:8 base 7:8; 
zkokeyp Zi8_814833F0 attempt 1: widen loop variable and narrow at table accesses; fuzzy 99.04256; src 0xbc base 0xbc insns 47/47; diffs 8: [6, 13, 22, 26, 27, 34, 35, 36]; 
zkokeyp Zi8_814833F0 attempt 2: initialize loop index in declaration and use while loop; fuzzy 92.53191; src 0xb8 base 0xbc insns 46/47; --- replace mine 6:7 base 6:7; 
zkokeyp Zi8_81483264 attempt 3: C99 scoped for counter rejected by C89 compiler; restored original.
zkokeyp Zi8_81483308 attempt 3: C99 scoped for counter rejected by C89 compiler; restored original.
zkokeyp Zi8_814833F0 attempt 3: C99 scoped for counter rejected by C89 compiler; restored original.
zkokeyp Zi8_81483264 attempt 4: C89 scope encloses scratch loop and counter; fuzzy 81.12195; src 0xb8 base 0xa4 insns 46/41; --- replace mine 6:11 base 6:9; POOL IDENTICAL, no strings
zkokeyp Zi8_81483308 attempt 4: C89 scope encloses scratch loop and counter; fuzzy 89.55173; src 0xf4 base 0xe8 insns 61/58; --- replace mine 5:10 base 5:9; POOL IDENTICAL, no strings
zkokeyp Zi8_814833F0 attempt 4: C89 scope encloses scratch loop and counter; fuzzy 83.319145; src 0xd0 base 0xbc insns 52/47; --- replace mine 6:11 base 6:9; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 1: replace oversized scratch union with five packed key bytes evidenced by frame and stores; fuzzy 77.472305; src 0x53c base 0x55c insns 335/343; --- replace mine 0:1 base 0:1; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 2: translate frame-sized packed key buffer, candidate index initialization, signed divide and modulo, typed nine-byte entries; fuzzy 80.90087; src 0x55c base 0x55c insns 343/343; diffs 290: [6, 7, 11, 12, 13, 14, 15, 16, 23, 24, 25, 28, 32, 37, 38, 39, 41, 42, 45, 47]; POOL IDENTICAL, no strings
zkokeyp Zi8_814834AC attempt 3: separate filtering and compaction indices; emit remaining-candidate branch first like target; fuzzy 87.938774; src 0x55c base 0x55c insns 343/343; diffs 268: [8, 9, 10, 11, 12, 13, 14, 15, 16, 19, 23, 34, 35, 48, 55, 56, 78, 79, 80, 81]; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 1: translate typed key table and options; correct nine-byte character stride and five-byte packed key frame; name traversal state; fuzzy 64.93572; src 0xb44 base 0xa74 insns 721/669; --- replace mine 3:7 base 3:5; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 2: direct early returns remove unnecessary result lifetimes; shift-plus-index entry addressing follows target blocks; BUILD FAILED, see Zi8GetKOcandidates-2.build
zkokeyp Zi8GetKOcandidates attempt 3: direct early returns and literal shift-plus-index addressing preserve live intermediate counts; fuzzy 69.149475; src 0xb3c base 0xa74 insns 719/669; --- replace mine 3:7 base 3:5; POOL IDENTICAL, no strings
zkokeyp Zi8GetKOcandidates attempt 4: signed division and modulo for packed key comparisons mirror original basic blocks; fuzzy 69.58446; src 0xb5c base 0xa74 insns 727/669; --- replace mine 3:7 base 3:5; POOL IDENTICAL, no strings
zi8getc2 Zi8GetDataSignature attempt 1: decode signature address into integer local; fuzzy 99.347824; src 0x114 base 0x114 insns 69/69; diffs 9: [5, 7, 9, 28, 32, 33, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetDataSignature attempt 2: split capacity test from empty signature; fuzzy 90.434784; src 0x114 base 0x114 insns 69/69; diffs 16: [5, 7, 9, 28, 32, 33, 38, 39, 40, 41, 42, 43, 44, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetDataSignature attempt 3: keep table selector separate from signature length; fuzzy 99.05797; src 0x114 base 0x114 insns 69/69; diffs 13: [5, 7, 9, 25, 27, 28, 29, 32, 33, 34, 51, 52, 57]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8AlphaSignature attempt 1: translate signature validation and copy blocks; keep first/second descriptors and one active cursor/length; fuzzy 97.97059; src 0x32c base 0x330 insns 203/204; --- replace mine 10:11 base 10:11; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8AlphaSignature attempt 2: keep dictionary descriptor length in aggregate storage and reverse array declarations for target stack layout; BUILD FAILED, see Zi8AlphaSignature-2.build
zi8getc2 Zi8AlphaSignature attempt 3: use aggregate descriptor length consistently in first signature copy; fuzzy 99.90196; src 0x330 base 0x330 insns 204/204; diffs 20: [0, 2, 3, 12, 16, 23, 37, 39, 40, 43, 45, 57, 69, 118, 119, 158, 159, 198, 200, 202]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8AlphaSignature attempt 4: group persistent signature descriptors into one typed state structure; fuzzy 100.0; src 0x330 base 0x330 insns 204/204; diffs 0: []; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8ZhSignature attempt 1: translate context-selected signature copy paths in address order; common u16 length and independent source lengths; fuzzy 99.01923; src 0x340 base 0x340 insns 208/208; diffs 6: [133, 147, 148, 155, 181, 187]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8ZhSignature attempt 2: ordinary copied length scalar and combined dictionary cursor expression restore target stack and statement ordering; fuzzy 100.0; src 0x340 base 0x340 insns 208/208; diffs 0: []; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 1: direct signature returns keep candidate count lifetime out of dispatcher; fuzzy 87.18588; src 0xb18 base 0xad8 insns 710/694; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 2: promote language selector to signed int for target dispatch comparisons; fuzzy 87.20317; src 0xad4 base 0xad8 insns 693/694; --- replace mine 0:1 base 0:1; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8GetCandidatesOrCount attempt 3: separate character-info buffer and saved call fields in typed state; fuzzy 86.7608; src 0xb0c base 0xad8 insns 707/694; --- replace mine 8:9 base 8:9; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 1: signed reverse scan index; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 2: invert equality into continue branch; fuzzy 99.36508; src 0xfc base 0xfc insns 63/63; diffs 8: [5, 7, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWChar attempt 3: move duplicate initialization after buffer setup; fuzzy 97.53968; src 0xfc base 0xfc insns 63/63; diffs 9: [5, 7, 8, 14, 25, 30, 41, 49, 56]; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWordW attempt 1: reconstruct word slots as 21-character rows; reuse slot and character counters; fuzzy 99.244606; src 0x230 base 0x22c insns 140/139; --- replace mine 19:20 base 19:20; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWordW attempt 2: keep selected slot as byte; fuzzy 94.71223; src 0x238 base 0x22c insns 142/139; --- replace mine 19:20 base 19:20; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWordW attempt 3: reverse duplicate branch into matched-first order; fuzzy 97.94964; src 0x230 base 0x22c insns 140/139; --- replace mine 19:20 base 19:20; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8getc2 Zi8IsDupWordW attempt 4: reuse assigned mapping byte as selected slot without an extra work count load; fuzzy 100.0; src 0x22c base 0x22c insns 139/139; diffs 0: []; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8match Zi8MatchPhonetic attempt 1: restore byte traversal fields and typed stack state; nonzero count branch first; BUILD FAILED, see Zi8MatchPhonetic-1.build
zi8match Zi8MatchPhonetic attempt 2: group sound offset in target operand order and signed header division; BUILD FAILED, see Zi8MatchPhonetic-2.build
zi8match Zi8MatchPhonetic attempt 3: use one sound cursor and packed dictionary entry terminator, as original blocks do; BUILD FAILED, see Zi8MatchPhonetic-3.build
zi8match Zi8GetPyPhonetic attempt 1: restore initial partial flag and conversion-count initialization ordering; fuzzy 75.58496; src 0xb5c base 0xb38 insns 727/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 2: group phonetic result and conversion descriptors in meaningful stack state; fuzzy 75.58218; src 0xb5c base 0xb38 insns 727/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyPhonetic attempt 3: reverse scratch array declarations and express extension normalization by subtraction; fuzzy 75.144844; src 0xb64 base 0xb38 insns 729/718; --- replace mine 7:10 base 7:10; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 1: select row base before final output columns; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 2: use wider row counter to remove redundant narrowing; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8match Zi8GetPyFinal attempt 3: tail tested index loop with explicit initialization; fuzzy 99.245285; src 0xd4 base 0xd4 insns 53/53; diffs 8: [26, 27, 28, 29, 34, 35, 36, 37]; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 4: typed traversal state with all actual fields and count initialization; fuzzy 78.10193; src 0x5a0 base 0x5ac insns 360/363; --- replace mine 5:10 base 5:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 5: target grouped offset arithmetic and signed header shift; fuzzy 77.804405; src 0x5a4 base 0x5ac insns 361/363; --- replace mine 5:10 base 5:10; POOL IDENTICAL, no strings
zikorean Zi8GetKoreanCandidates attempt 1: restore grouped output reset, successful character lookup first, candidate loop reset; helper owns input index; fuzzy 71.52342; src 0x9b4 base 0x9ac insns 621/619; --- replace mine 8:10 base 8:10; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8match Zi8MatchPhonetic attempt 6: single cursor and packed dictionary terminator state; fuzzy 82.55923; src 0x58c base 0x5ac insns 355/363; --- replace mine 6:10 base 6:10; POOL IDENTICAL, no strings
zikorean Zi8GetKoreanCandidates attempt 2: invert Korean helper success block into target address order and direct typed out parameters; fuzzy 72.4685; src 0x9b4 base 0x9ac insns 621/619; --- replace mine 8:10 base 8:10; POOL IDENTICAL up to 0 (mine=0 base=0)
zikorean Zi8GetKoreanCandidates attempt 3: widen reusable character loop counter and express special-table upper bound literally; fuzzy 72.063; src 0x95c base 0x9ac insns 599/619; --- replace mine 13:19 base 13:19; POOL IDENTICAL up to 0 (mine=0 base=0)
zi8match Zi8MatchPhonetic attempt 7: reuse mutable alternate-mode parameter; header shift without signed division correction; fuzzy 82.74104; src 0x588 base 0x5ac insns 354/363; --- replace mine 5:10 base 5:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 8: place node advance block before decoding and branch back on every skip; fuzzy 83.58127; src 0x590 base 0x5ac insns 356/363; --- replace mine 5:10 base 5:10; POOL IDENTICAL, no strings
zi8match Zi8MatchPhonetic attempt 9: place phonetic equality dispatch after nested traversal, preserving target basic block order; fuzzy 85.95042; src 0x598 base 0x5ac insns 358/363; --- replace mine 5:10 base 5:10; POOL IDENTICAL, no strings
```

