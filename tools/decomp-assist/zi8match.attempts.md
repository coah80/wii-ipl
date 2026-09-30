Zi8PriMatchNextChar, Zi8ExactMatchNextChar, Zi8SecMatchChar,
Zi8PriMatchNextComp, Zi8SecMatchComp and Zi8GetPCode match on reconstruction.
The unit has no .data string pool; pool_diff.py raises KeyError, gate confirms identical empty pools.

Zi8MatchPhonetic: reconstructed dictionary index separately from phonetic code.
1. Byte-sized match/alternate state: 359/363 instructions, 77.62259%.
2. Inverted remaining-count initialization: 359/363, 77.242424%.
3. Direct alternate parameter and numParts == 1: 348/363, 72.46832%.
Retained 359/363, 77.66942%; stack layout, control flow and allocation differ.

Zi8GetPyPhonetic:
1. Four-byte pinyin buffer: 726/718, 75.158775%.
2. U16 spelling index: 726/718, 74.785515%.
3. Int spelling index: 701/718, 72.214485%.
Retained 726/718, 75.160164%; branch structure and allocation differ.

Zi8GetPyFinal:
1. Shared final-row pointer: 58/53, 62.28302%.
2. Reordered index/row declarations: 53/53, 99.245285%, 8 instruction differences.
3. U16 row index: 53/53, 98.86793%, 12 differences.
Retained 53/53, 99.245285%; r6/r7 allocation in result loads differs.

Zi8GetBpmfPhonetic:
1. Deferred result initialization: 309/309, 99.23948%.
2. Unsigned result counter and direct text subtraction: 309/309, 100%, diffs 0.

Continuation on merged baseline (7/10 exact, code 3720/8256, data 608/728).

Zi8GetPyFinal (baseline 99.245285%, 53/53, 8 differences):
1. Reverse byte-pointer addition in final output access: unchanged.
2. Widen row to unsigned int, narrow output table index: 95.0%, 51/53.
3. Typed eight-byte final records with spelling/initial/final/flags fields:
   99.245285%, 53/53, same eight allocation differences; table remains 528 bytes.
4. Flat object byte indexing with row stride: 99.0566%, 53/53.
Retained baseline: only r6/r7 address-expression allocation differs.

Zi8MatchPhonetic (baseline 77.66942%, 359/363):
1. Byte match/alternate flags and signed remaining count: 75.242424%, 362/363.
2. Group match flags and remaining count into semantic search state:
   72.7989%, 356/363.
3. Typed twelve-byte dictionary records rather than byte-stride indexing:
   77.694214%, 358/363.
Retained baseline: control flow, stack layout and instruction count differ.

Zi8GetPyPhonetic (baseline 75.160164%, 726/718):
1. Integer partial flag and U32 result: 73.678276%, 727/718.
2. Structured letter/extension range checks: unchanged 75.160164%, 726/718.
3. Initialize converted count at declaration; allow worst-case separator expansion
   in conversion buffer, narrow per-syllable buffer: 75.0%, 726/718.
Retained baseline: conversion branches, frame and allocation differ.

Data audit: .rodata 528 bytes is identical; .extab 80 bytes is identical.
Remaining .extabindex differences follow unmatched function sizes. Empty pools
remain identical. No data-address objects or configuration changes added.
