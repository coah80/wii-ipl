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
