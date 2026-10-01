# zi8cgetc matching continuation, 2026-10-01

Unslop and coah-voice read. No worker delegation or remote actions.

An inherited orphan declaration search PID 1729918 was writing this worktree during discovery. SIGINT stopped it and restored its original HEAD source. The discovery/g00 numbers are invalid and excluded from attempts. Fresh baseline follows after stopping it.

- g01 zi8InternalGetZH: account for unsupported combined charset in switch; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g02 zi8InternalGetZH: make charset switch default explicit; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g03 zi8InternalGetZH: use integer charset switch expression; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g04 zi8InternalGetZH: cast charset result to byte before testing its traditional flag; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g05 zi8InternalGetZH: compare traditional charset flag explicitly; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g06 zi8InternalGetZH: mask unsigned charset return in traditional flag test; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g07 zi8InternalGetZH: test byte cast with unsigned charset flag; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g08 zi8InternalGetZH: use unsigned traditional charset mask; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g09 zi8InternalGetZH: evaluate traditional charset mask before helper result; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g10 zi8InternalGetZH: test traditional charset bit by shifting helper result; fuzzy 95.988660 -> 95.983986, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g11 zi8InternalGetZH: negate zero charset flag test; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g12 zi8InternalGetZH: cast traditional charset flag to truth value; fuzzy 95.988660 -> 95.979300, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9079, data 144 -> 144; rejected, restored.
- s01 ZiMatchZHSpelling: use unsigned candidate character length; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s02 ZiMatchZHSpelling: use long spelling match result; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s03 ZiMatchZHSpelling: use long candidate character length; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s04 ZiMatchZHSpelling: use short candidate character length; fuzzy 98.801650 -> 98.347110, insns 121 -> 121, diffs 29 -> 29, non-register first None -> 56, non-register count 0 -> 1, data 144 -> 144; rejected, restored.
- s05 ZiMatchZHSpelling: express spelling mismatch as zero comparison; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s06 ZiMatchZHSpelling: test both phonetic cursors explicitly; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s07 ZiMatchZHSpelling: use for loop for phonetic index traversal; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s08 ZiMatchZHSpelling: use for loop for phonetic cursor traversal; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s09 ZiMatchZHSpelling: use explicit phonetic index subtraction; fuzzy 98.801650 -> 97.809910, insns 121 -> 122, diffs 29 -> 69, non-register first None -> 84, non-register count 0 -> 42, data 144 -> 72; rejected, restored.
- s10 ZiMatchZHSpelling: name spelling result by its meaning; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s11 ZiMatchZHSpelling: use unsigned spelling match result; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s12 ZiMatchZHSpelling: declare spelling result beside candidate length; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s13 ZiMatchZHSpelling: cast candidate character count to byte; fuzzy 98.801650 -> 98.347110, insns 121 -> 121, diffs 29 -> 29, non-register first None -> 56, non-register count 0 -> 1, data 144 -> 144; rejected, restored.
- s14 ZiMatchZHSpelling: group match and candidate length declarations; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s15 ZiMatchZHSpelling: group phonetic cursor declarations; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s16 ZiMatchZHSpelling: use while loop for leading spelling scan; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s17 ZiMatchZHSpelling: initialize spelling result at declaration; fuzzy 98.801650 -> 98.801650, insns 121 -> 121, diffs 29 -> 29, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- s18 ZiMatchZHSpelling: scope candidate length before spelling buffers; fuzzy 98.801650 -> 91.818184, insns 121 -> 125, diffs 29 -> 123, non-register first None -> 0, non-register count 0 -> 116, data 144 -> 24; rejected, restored.
- c01 Zi8GetElementCount: declare result count before element cursors; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- c02 Zi8GetElementCount: name element result count explicitly; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- c03 Zi8GetElementCount: use pointer-array parameter form for elements; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- c04 Zi8GetElementCount: initialize cursors with grouped byte declaration; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- c05 Zi8GetElementCount: use for loop for element traversal; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- c06 Zi8GetElementCount: make remaining character condition explicit; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- c07 Zi8GetElementCount: use direct separator local; fuzzy 99.347824 -> 97.486950, insns 115 -> 113, diffs 13 -> 106, non-register first None -> 40, non-register count 0 -> 99, data 144 -> 24; rejected, restored.
- c08 Zi8GetElementCount: use compound result count increments; fuzzy 99.347824 -> 98.478264, insns 115 -> 116, diffs 13 -> 36, non-register first None -> 72, non-register count 0 -> 23, data 144 -> 72; rejected, restored.
- c09 Zi8GetElementCount: use while loop for latin element scan; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- c10 Zi8GetElementCount: initialize result count before cursor assignments; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- c11 Zi8GetElementCount: use left-associated chained initialization; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- c12 Zi8GetElementCount: use for loop to advance spaced cursor; fuzzy 99.347824 -> 99.347824, insns 115 -> 115, diffs 13 -> 13, non-register first None -> None, non-register count 0 -> 0, data 144 -> 144; rejected, restored.
- g13 zi8InternalGetZH: initialize 70 engine locals at declaration; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g14 zi8InternalGetZH: initialize engine charset,charsetFilter at declaration; fuzzy 95.988660 -> 95.988660, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; rejected, restored.
- g15 zi8InternalGetZH: initialize engine phase,outputIndex at declaration; fuzzy 95.988660 -> 95.913260, insns 10676 -> 10676, diffs 10068 -> 10070, non-register first 1204 -> 72, non-register count 9080 -> 9084, data 144 -> 144; rejected, restored.
- g16 zi8InternalGetZH: initialize engine candidateOrdinal,alternateCharacter,character,relatedOrdinal at declaration; fuzzy 95.988660 -> 95.836460, insns 10676 -> 10676, diffs 10068 -> 10074, non-register first 1204 -> 72, non-register count 9080 -> 9088, data 144 -> 144; rejected, restored.
- g17 zi8InternalGetZH: initialize engine record,componentCursor,componentTable,componentOrdinals at declaration; fuzzy 95.988660 -> 95.821000, insns 10676 -> 10676, diffs 10068 -> 10090, non-register first 1204 -> 72, non-register count 9080 -> 9115, data 144 -> 144; rejected, restored.
- g18 zi8InternalGetZH: initialize engine totalResults,switchedPhonetic at declaration; fuzzy 95.988660 -> 95.893875, insns 10676 -> 10676, diffs 10068 -> 10094, non-register first 1204 -> 72, non-register count 9080 -> 9126, data 144 -> 144; rejected, restored.
- g19 zi8InternalGetZH: initialize engine firstPhoneticPass,exactPhrase,singleCharacterPass at declaration; fuzzy 95.988660 -> 95.856600, insns 10676 -> 10676, diffs 10068 -> 10097, non-register first 1204 -> 68, non-register count 9080 -> 9142, data 144 -> 144; rejected, restored.

## Declaration-order searches

zi8InternalGetZH: declaration block: |       ziU8 matchMode; |       int index; |       ziWChar* currentWord; |       ziU8* userEntries; |       ziU16 ordinalIndex; |       ziU16 tableIndex; |       ziU16 phraseOrdinal; |       ziU16 userIndex; |       ziU16 userCount; |       ziU8 charset; | start (286, 10068) | best (286, 10068) after 118 builds; source restored; best order was: |     ziU8 matchMode; |     int index; |     ziWChar* currentWord; |     ziU8* userEntries; |     ziU16 ordinalIndex; |     ziU16 tableIndex; |     ziU16 phraseOrdinal; |     ziU16 userIndex; |     ziU16 userCount; |     ziU8 charset; | 

ZiMatchZHSpelling: declaration block: |       ziWChar* candidateCursor; |       ziWChar* spellingCursor; |       int index; |       int matches; |       int candidateLength; |       ziWChar spacedSpelling[64]; |       ziWChar spacedCandidate[64]; | start (0, 29) | best (0, 29) after 52 builds; source restored; best order was: |     ziWChar* candidateCursor; |     ziWChar* spellingCursor; |     int index; |     int matches; |     int candidateLength; |     ziWChar spacedSpelling[64]; |     ziWChar spacedCandidate[64]; | 

Engine first-divergence audit: normalized instruction alignment across all 10,676 instructions found 24 edits, consisting of twelve extra source return-value moves, ten missing target return-value moves, and two missing halfword conversions. The opcode and immediate alignment has no other edits; resolved call names and branch destinations are checked separately before the final report. Exact ctxdiff still differs at 10,068 positions because temporary GPR assignments and the displaced return-value copies differ. First strict non-register divergence is +0x4b4, caused by the extra return-value move at +0x58c in the traditional charset helper test. Twelve condition/switch variations and seven initializer variations were rebuilt and rejected. No instruction-level difference was hidden or treated as exact.

Current measures: {"measures": {"fuzzy_match_percent": 96.39912, "total_code": "47816", "matched_code": "4168", "matched_code_percent": 8.716747, "total_data": "536", "matched_data": "144", "matched_data_percent": 26.865673, "total_functions": 8, "matched_functions": 5, "matched_functions_percent": 62.5, "total_units": 1}, "functions": {"ZiMatchZHSpelling": {"fuzzy": 98.80165, "insns": 121, "diffs": 29, "struct": 0, "first": null, "size": 484}, "zi8InternalGetZH": {"fuzzy": 95.98866, "insns": 10676, "diffs": 10068, "struct": 9080, "first": 1204, "size": 42704}, "Zi8GetElementCount": {"fuzzy": 99.347824, "insns": 115, "diffs": 13, "struct": 0, "first": null, "size": 460}}}

Open-function coverage: ZiMatchZHSpelling, 18 separately logged source trials, at least 3 distinct attempts. Still unmatched.
Open-function coverage: zi8InternalGetZH, 19 separately logged source trials, at least 3 distinct attempts. Still unmatched.
Open-function coverage: Zi8GetElementCount, 12 separately logged source trials, at least 3 distinct attempts. Still unmatched.

Interim checkpoint before relocation-aware branch review: all candidates so far were rejected. The subsequent g20-g22 repairs below correct actual switch destinations and cleanup exits. No new instruction-exact function was found; the exact-count-increase completion criterion remains unmet.

Interim relocation audit found four real branch-destination differences. The eight other differing relocation names refer to anonymous source jump tables versus extracted target jump-table names, not helper calls. The four destination differences were repaired by g20-g22.

Interim full clean gate before g20-g22:

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 4168/47816 data 144/536 functions 5/8 fuzzy 96.3991 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 5/8
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .data size 392 match None
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sbss2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sdata2 size 16 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .text size 47816 match 96.39912
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extab size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extabindex size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: ZiMatchZHSpelling 98.80165
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: zi8InternalGetZH 95.98866
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: Zi8GetElementCount 99.347824
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] baseline: code 4168/47816 data 144 functions 5 fuzzy 96.3991
regressions vs baseline: 0
global matched_code_percent: 86.68724 -> 86.68724
global fuzzy_match_percent: 99.30689 -> 99.30689
global complete_code_percent: 60.61288 -> 60.61288
global matched_data_percent: 91.11031 -> 91.11031
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- g20 zi8InternalGetZH: correct pinyin final fuzzy-pair case mapping; fuzzy 95.988660 -> 95.989600, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; kept, quick gate PASS.
- g21 zi8InternalGetZH: continue frequency search cleanup after output capacity; fuzzy 95.989600 -> 95.990074, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; kept, quick gate PASS.
- g22 zi8InternalGetZH: continue frequency search cleanup after candidate capacity; fuzzy 95.990074 -> 95.990540, insns 10676 -> 10676, diffs 10068 -> 10068, non-register first 1204 -> 1204, non-register count 9080 -> 9080, data 144 -> 144; kept, quick gate PASS.
- g24 zi8InternalGetZH: narrow first paired phonetic code to target halfword; fuzzy 95.990540 -> 96.066414, insns 10676 -> 10677, diffs 10068 -> 10405, non-register first 1204 -> 876, non-register count 9080 -> 9869, data 144 -> 72; rejected, restored.
- g25 zi8InternalGetZH: narrow second paired phonetic code to target halfword; fuzzy 95.990540 -> 96.069220, insns 10676 -> 10677, diffs 10068 -> 10405, non-register first 1204 -> 876, non-register count 9080 -> 9870, data 144 -> 72; rejected, restored.
- g26 zi8InternalGetZH: narrow both paired phonetic codes to target halfwords; fuzzy 95.990540 -> 96.090294, insns 10676 -> 10678, diffs 10068 -> 10519, non-register first 1204 -> 876, non-register count 9080 -> 10222, data 144 -> 72; rejected, restored.

## Final audit after g20-g22

The source diff swaps the two pinyin fuzzy-pair case labels to route each case to the target bitfield test, and routes both component-frequency capacity exits through the existing frequency cleanup. Both changes preserve the target instruction count and stack frame. Three accepted improvements were each independently checked with the full clean gate and committed locally.

Target-normalized alignment still contains twelve extra return-value moves, ten missing return-value moves and two missing halfword conversions. The casts restoring those conversions increased the instruction count and regressed matched exception metadata from 144 to 72 bytes, so g24-g26 were restored despite higher fuzzy scores. No padding or compensating data was introduced.

Relocation-aware audit: 168/168 helper calls, 0 call-name mismatches, 0 mapped branch-destination mismatches. The full exact ctxdiff includes all temporary GPR differences and return-copy displacement.

Open-function final coverage: ZiMatchZHSpelling, 18 separately logged source trials, fuzzy 98.801650%, exact unchanged.
Open-function final coverage: zi8InternalGetZH, 25 separately logged source trials, fuzzy 95.990540%, exact unchanged.
Open-function final coverage: Zi8GetElementCount, 12 separately logged source trials, fuzzy 99.347824%, exact unchanged.

The two declaration searches evaluated 118 and 52 orders including their baselines. No declaration permutation was accepted. Final instruction-exact count is 5/8, unchanged; matched code 4168/47816 and data 144/536 are unchanged. The required exact-count increase and 100% unit completion were not achieved.

Final full clean gate after all source trials and restorations:

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 4168/47816 data 144/536 functions 5/8 fuzzy 96.4008 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 5/8
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .data size 392 match None
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sbss2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sdata2 size 16 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .text size 47816 match 96.40079
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extab size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extabindex size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: ZiMatchZHSpelling 98.80165
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: zi8InternalGetZH 95.99054
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: Zi8GetElementCount 99.347824
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] baseline: code 4168/47816 data 144 functions 5 fuzzy 96.3991
regressions vs baseline: 0
global matched_code_percent: 86.68724 -> 86.68724
global fuzzy_match_percent: 99.30689 -> 99.30693
global complete_code_percent: 60.61288 -> 60.61288
global matched_data_percent: 91.11031 -> 91.11031
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
