Both table helpers match exactly on reconstruction: Zi8_814813FC 49/49
instructions, Zi8_81481E6C 629/629. Both have ctxdiff diffs 0.
The string pools are empty and identical.

Zi8GetKoreanCandidates:
1. For loop with an explicit break in character mapping: 68.13893%, 629/619 instructions.
2. Full-width result and character index: 67.34895%, 600/619.
3. Typed three-byte character/sequence records: 66.96769%, 629/619.
Retained attempt 1. The main routine still differs in stack state, loop structure
and register allocation. No register/volatile keywords were retained.

Continuation on merged baseline (2/3 exact, code 2712/5188, data 24/348).

Zi8GetKoreanCandidates (baseline 68.13893%, 629/619):
1. Full-width candidate result: 68.76414%, 623/619.
2. Full-width character/loop cursor: 68.021%, 605/619.
3. Typed three-byte character mapping records: 67.266556%, 624/619.
Retained full-width result; candidate branches and stack/access allocation differ.

Data audit: source contains the two natural 31-entry switch tables in function
order, 248 bytes. Original .data is 288 bytes; its final 40-byte table references
Zi8_81483118, owned by zkokeyp (.text 8148302C..8148447C), outside this unit.
This is a split ownership problem, not a missing Korean function. Changing splits
or manually placing that foreign table is outside this task. Remaining owned
table relocations depend on unmatched function branch offsets. Empty pools match.
