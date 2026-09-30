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
