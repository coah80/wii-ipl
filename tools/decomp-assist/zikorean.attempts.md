Both table helpers match exactly on reconstruction: Zi8_814813FC 49/49
instructions, Zi8_81481E6C 629/629. Both have ctxdiff diffs 0.
The string pools are empty and identical.

Zi8GetKoreanCandidates:
1. For loop with an explicit break in character mapping: 68.13893%, 629/619 instructions.
2. Full-width result and character index: 67.34895%, 600/619.
3. Typed three-byte character/sequence records: 66.96769%, 629/619.
Retained attempt 1. The main routine still differs in stack state, loop structure
and register allocation. No register/volatile keywords were retained.
