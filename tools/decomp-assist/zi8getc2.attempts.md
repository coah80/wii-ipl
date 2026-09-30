Reconstructed all 17 functions in target order. Empty string pools are identical.
Exact: fuzzy setters, Latin search order, global size, both candidate wrappers,
duplicate-buffer initialization, memset, memcpy and maximum word length.

Zi8GetDataSignature:
1. length > capacity instead of capacity < length: 99.05797%, 69/69 instructions.
2. Reuse table selector as U16 length: 99.347824%, 69/69, 9 differences.
3. Reorder locals and widen return: 98.478264%, 69/69, 10 differences.
Retained attempt 2. Only saved register assignment differs.

Zi8GetEngineSignature:
1. Separate OEM/build locals: 95.85268%, 219/224 instructions.
2. Explicit quotient/remainder arithmetic: 95.71875%, 219/224.
3. Reordered major/minor locals and reused identifier value: 95.58036%, 219/224.
Retained reconstruction, 95.95982%; minor version is held in a register instead
of a stack slot, with a different saved-register frame.

Zi8AlphaSignature:
1. Counted for loops instead of postdecrement while: 63.64706%, 191/204.
2. U32 candidate count: 63.887257%, 188/204.
3. Widen helper return types and restore U16 candidate count: 63.32353%, 189/204.
Retained reconstruction, 67.61275%, 188/204; stack locals and control flow differ.

Zi8ZhSignature:
1. U32 candidate count: 25.711538%, 209/208.
2. U32 engine length: 29.216347%, 202/208.
3. Widen helper returns and restore U16 lengths: 22.509615%, 212/208.
Retained attempt 2; integer promotion, loops and allocation differ.

Zi8GetCandidatesOrCount:
1. Unsigned signature result: 74.48703%, 760/694.
2. U8 result count: 74.85447%, 764/694.
3. Restore full-width count with widened signature helper returns: 75.452446%, 756/694.
Retained reconstruction, 75.64553%, 754/694; branch layout and allocation differ.

Zi8IsDupWChar:
1. U16 position increment: 99.20635%, 63/63, 9 differences.
2. Signed position with explicit U16 index: 96.666664%, 64/63.
3. U32 position and signed duplicate flag: 96.666664%, 64/63.
Retained attempt 1; character, duplicate and position register allocation differs.

Zi8IsDupWordW:
1. Unsigned duplicate flag: 85.76259%, 140/139.
2. Explicit loop break: 90.22302%, 140/139.
3. U8 cache position: 88.78417%, 142/139.
Retained attempt 2; loop layout and cache index allocation differ.

Continuation on merged baseline (10/17 exact, code 484/6888, data 24/332).

Zi8GetDataSignature (baseline 99.347824%, 69/69, 9 differences):
1. Keep table address as U32 until memcpy: unchanged.
2. Generic destination parameter with typed output alias: 97.072464%, 70/69.
3. Successful length branch first with error fallthrough: 81.73913%, 69/69.
Retained baseline: saved register allocation only.

Zi8GetEngineSignature:
1. Reuse numeric value for major, OEM and build: 96.02679%, 219/224.
2. Store minor version as a member of version state: 100%, 224/224, ctxdiff 0.
3. Two-component version array: 99.98661%, 224/224, 3 differences.
4. Unsigned output index: 87.52232%, 205/224.
Retained version state and reused number; this is the new instruction-exact function.

Zi8AlphaSignature:
1. Dictionary buffer sized for the passed 32-byte capacity: 67.61275%, 188/204.
2. Group signature pointers, lengths and countOnly state: 59.32353%, 213/204.
3. Invert the dictionary eligibility branch with grouped state:
   62.656864%, 213/204.
Retained capacity-sized buffer; stack locals and branches still differ.

Zi8ZhSignature:
1. Dictionary buffer sized for passed capacity: 29.225962%, 202/208.
2. U16 lengths/count and explicit presence increments: 26.26923%, 212/208.
3. Group countOnly and available state with U16 lengths/count:
   21.259615%, 214/208.
Retained capacity-sized buffer; promotions, stack state and loops differ.

Zi8GetCandidatesOrCount:
1. Unsigned UTF16 sentinel comparisons and signature result: 81.198845%, 740/694.
2. Direct signature tests, sixteen-character info buffer: 84.46254%, 717/694.
3. Direct language/character helper tests: 85.65274%, 709/694.
4. Name and reuse final character-info character: 86.7536%, 707/694.
Retained these improvements; dispatch branches and saved stack state still differ.

Zi8IsDupWChar:
1. U32 buffer position with U16 count/index conversions: 96.031746%, 65/63.
2. Unsigned position and direct count increment: 97.53968%, 64/63.
3. Append with buffer[(*buffer)++]: 99.36508%, 63/63, 8 differences.
4. Unsigned result flag: 98.492065%, 63/63, extra return narrowing.
5. Separate buffer/result declarations from initialization: unchanged 99.36508%.
Retained postincrement append and separate initialization; character/result
register assignments are swapped.

Zi8IsDupWordW:
1. Unsigned loop indices: 87.84892%, 140/139.
2. Typed twenty-one-character cache records: 82.51798%, 141/139.
3. Boolean duplicate flag: 91.33813%, 141/139.
Retained boolean flag; cache loop layout and allocation remain different.

Data audit: 16-byte search-order .rodata is identical. Both .data sections are
80-byte switch tables whose entries depend on unmatched dispatch branches.
Original .sdata2 is 8 bytes (4-byte fuzzy pair plus section-end zeros), source
4 bytes. Original zero fuzzy symbol/.sbss2 is 8 bytes, current header type and
source object are 4. Both section alignments are 8. The current shared headers
do not explain the extra trailing bytes; no fake padding or shared ABI edits.
Empty string pools remain identical.
