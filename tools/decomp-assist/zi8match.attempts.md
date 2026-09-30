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
