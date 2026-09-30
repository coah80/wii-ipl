Reconstructed all six functions. NextDawgGroup matches 68/68 instructions;
Zi8SyllablesROMdata matches 66/66. Neither unit has a .data string pool;
pool_diff.py raises KeyError, and the gate confirms identical empty pools.

Zi8MatchROMdata0:
1. Three-key buffer, full-width incoming count: 30.915709%, 537/522 instructions.
2. Status branch inversion and common failure exit: 44.220306%, 531/522.
3. U16 path index and explicit header byte composition: 45.16092%, 533/522.
Retained attempt 3. Graph traversal, field access and register allocation differ.
The key buffer holds at most two converted keys and a terminator, not the
forty entries inferred by Ghidra from neighboring stack storage.

Zi8MatchROMdata1:
1. Byte-sized group index: 98.203125%, 130/128 instructions.
2. Assign returned table address directly to the workspace: 98.47656%, 127/128.
3. Scalar table address local with pointer conversion at assignment: 99.765625%,
128/128, 5 differences. Retained attempt 3; r26/r27 allocation differs.

Zi8MatchROMdata2:
1. Narrow count/language/capacity/mode/status parameters: 258/236 instructions.
2. Byte-sized result and output count: 265/236.
3. Full-width parameters and a counted prefix loop: 249/236.
Objdiff reports no fuzzy percentage for this function in all three builds.
Retained attempt 3. Instruction count, segment control flow and allocation differ.
Corrected the unsigned wide-character sentinel comparison to 0xeff1.

Zi8MatchROMdata:
1. Unsigned candidate result from the segment helper: 65.77665%, 225/197.
2. Full-width entry point result: 65.34518%, 225/197.
3. Full-width incoming count, remove its alias: 61.335026%, 234/197.
Retained the attempt 1 body. With the retained full-width segment-helper
signature it measures 58.106598%, 237/197 instructions. Group iteration and
fallback control flow differ.

Continuation on merged baseline (2/6 exact, code 536/4868, data 0/120).

Zi8MatchROMdata0 (baseline 45.16092%, 533/522):
1. Byte incoming count: 45.672413%, 532/522.
2. Unsigned converted key and key buffer: 47.754787%, 531/522.
3. Group capacity, status and result into traversal state:
   47.77203%, 534/522; first draft placed assignments before declarations and
   did not compile, then corrected declaration order.
Retained unsigned keys. Target has no extsh operations, and Zi8ConvertWC2Key
returns ziWChar. Did not retain the traversal state for a negligible fuzzy gain
with three more instructions. Graph traversal and stack allocation still differ.

Zi8MatchROMdata1 (baseline 99.765625%, 128/128, 5 differences):
1. Move group decrement to loop entry: 97.46094%, 129/128.
2. Typed table-address pointer: unchanged 99.765625%, 128/128.
3. Byte status parameter: 98.984375%, 129/128.
4. Group table address into table state: 96.671875%, 129/128.
Also tried an unsigned group parameter; rejected the compile failure caused by
existing char-pointer callers rather than changing other functions for the trial.
Retained baseline: r26/r27 assignments differ.

Zi8MatchROMdata2 (baseline 249/236):
1. Signed remaining-output cursor: 249/236.
2. Byte status parameter: 253/236.
3. Direct a/o/u vowel condition: 245/236.
Retained direct vowel test. Objdiff omits this function's fuzzy percentage in all
these reports; it is not 100%. Segment loops, narrowing and allocation differ.

Zi8MatchROMdata (baseline 58.106598%, 237/197):
1. U16 result: 55.055836%, 238/197.
2. Remove redundant input-pointer alias: 61.563454%, 234/197.
3. Unsigned table size: unchanged 58.106598%, 237/197.
Retained alias removal; fallback and group iteration branches differ.

Data audit: no .data/.rodata/.sdata content or strings. Source and target have
48-byte .extab and 72-byte .extabindex sections. Their mismatches derive from
unmatched function frames/sizes; no fabricated metadata added. Gate confirms
identical empty pools (pool_diff itself expects a .data section and raises KeyError).
