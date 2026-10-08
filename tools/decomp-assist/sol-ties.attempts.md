# sol-ties attempts

Base 23b77a33, branch agent/w1008/rx1. No source edits initially.
Baseline: update 85/446, DeleteUnauthorizedData 74/449, equal sizes.
Both string pools identical. Tracer requires output beneath _mwdbg; first local-output attempt rejected before compilation.

ZI1 lift declarations in reverse requested virtual order: 32 differing. src size 0x6f8 base size 0x6f8

ZI2 u32 LatestWord[copied] = LatestWord[copied + (wordLength - copyLength)];: 32 differing. src size 0x6f8 base size 0x6f8

ZI3 u32 *(LatestWord + copied) = *(LatestWord + wordLength - copyLength + copied);: 215 differing. src size 0x700 base size 0x6f8

ZI4 u32 LatestWord[copied] = LatestWord[wordLength + copied - copyLength];: 233 differing. src size 0x744 base size 0x6f8

ZI5 u32 LatestWord[copied] = LatestWord[copied - copyLength + wordLength];: 232 differing. src size 0x748 base size 0x6f8

ZI6 s32 LatestWord[copied] = LatestWord[copied + (wordLength - copyLength)];: 216 differing. src size 0x6dc base size 0x6f8

ZI7 s32 *(LatestWord + copied) = *(LatestWord + wordLength - copyLength + copied);: 216 differing. src size 0x6c0 base size 0x6f8

ZI8 s32 LatestWord[copied] = LatestWord[wordLength + copied - copyLength];: 232 differing. src size 0x740 base size 0x6f8

ZI9 s32 LatestWord[copied] = LatestWord[copied - copyLength + wordLength];: 226 differing. src size 0x71c base size 0x6f8

ZI10 u16 LatestWord[copied] = LatestWord[copied + (wordLength - copyLength)];: 215 differing. src size 0x65c base size 0x6f8

ZI11 u16 *(LatestWord + copied) = *(LatestWord + wordLength - copyLength + copied);: 215 differing. src size 0x65c base size 0x6f8

ZI12 u16 LatestWord[copied] = LatestWord[wordLength + copied - copyLength];: 217 differing. src size 0x660 base size 0x6f8

ZI13 u16 LatestWord[copied] = LatestWord[copied - copyLength + wordLength];: 217 differing. src size 0x660 base size 0x6f8

ZI14 int LatestWord[copied] = LatestWord[copied + (wordLength - copyLength)];: 216 differing. src size 0x6dc base size 0x6f8

ZI15 int *(LatestWord + copied) = *(LatestWord + wordLength - copyLength + copied);: 216 differing. src size 0x6c0 base size 0x6f8

ZI16 int LatestWord[copied] = LatestWord[wordLength + copied - copyLength];: 232 differing. src size 0x740 base size 0x6f8

ZI17 int LatestWord[copied] = LatestWord[copied - copyLength + wordLength];: 226 differing. src size 0x71c base size 0x6f8

ZI18 copied != copyLength copied++: 216 differing. src size 0x6c0 base size 0x6f8

ZI19 copied != copyLength copied += 1: 216 differing. src size 0x6c0 base size 0x6f8

ZI20 copied != copyLength copied = copied + 1: 216 differing. src size 0x6c0 base size 0x6f8

ZI21 copyLength > copied copied++: 32 differing. src size 0x6f8 base size 0x6f8

ZI22 copyLength > copied copied += 1: 32 differing. src size 0x6f8 base size 0x6f8

ZI23 copyLength > copied copied = copied + 1: 32 differing. src size 0x6f8 base size 0x6f8

ZI24 pointer copy before ++source; ++destination; ++copied: 299 differing. src size 0x6d4 base size 0x6f8

ZI25 pointer copy before ++copied; ++destination; ++source: 299 differing. src size 0x6d4 base size 0x6f8

ZI26 pointer copy before ++destination; ++source; ++copied: 299 differing. src size 0x6d4 base size 0x6f8

ZI27 pointer copy after ++source; ++destination; ++copied: 299 differing. src size 0x6d4 base size 0x6f8

ZI28 pointer copy after ++copied; ++destination; ++source: 299 differing. src size 0x6d4 base size 0x6f8

ZI29 pointer copy after ++destination; ++source; ++copied: 299 differing. src size 0x6d4 base size 0x6f8

ZI30 element type (wchar_t*)LatestWord: 32 differing. src size 0x6f8 base size 0x6f8

ZI31 element type (unsigned short*)LatestWord: 32 differing. src size 0x6f8 base size 0x6f8

ZI32 swap wordLength copied: 32 differing. src size 0x6f8 base size 0x6f8

ZI33 swap copyLength wordLength: 32 differing. src size 0x6f8 base size 0x6f8

ZI34 swap copied copyLength: 32 differing. src size 0x6f8 base size 0x6f8

ZI35 while copy: 32 differing. src size 0x6f8 base size 0x6f8

ZI36 precompute offset: 201 differing. src size 0x6f4 base size 0x6f8

ZI37 source base indexing: 216 differing. src size 0x6f0 base size 0x6f8

ZI38 typed character temporary u16: 32 differing. src size 0x6f8 base size 0x6f8

ZI39 typed character temporary wchar_t: 32 differing. src size 0x6f8 base size 0x6f8

ZI40 inline suffix helper u16* word, u32 length, u32 wordLength u32: 19 differing. src size 0x6f8 base size 0x6f8

ZI41 inline suffix helper u16* word, u32 length, u32 wordLength void: 19 differing. src size 0x6f8 base size 0x6f8

ZI42 inline suffix helper u16* word, u32 wordLength, u32 length u32: 19 differing. src size 0x6f8 base size 0x6f8

ZI43 inline suffix helper u16* word, u32 wordLength, u32 length void: 19 differing. src size 0x6f8 base size 0x6f8

ZI44 parameter order ('u16* word', 'u32 length', 'u32 wordLength'): 19 differing. src size 0x6f8 base size 0x6f8

ZI45 parameter order ('u16* word', 'u32 wordLength', 'u32 length'): 19 differing. src size 0x6f8 base size 0x6f8

ZI46 parameter order ('u32 length', 'u16* word', 'u32 wordLength'): 19 differing. src size 0x6f8 base size 0x6f8

ZI47 parameter order ('u32 length', 'u32 wordLength', 'u16* word'): 19 differing. src size 0x6f8 base size 0x6f8

ZI48 parameter order ('u32 wordLength', 'u16* word', 'u32 length'): 19 differing. src size 0x6f8 base size 0x6f8

ZI49 parameter order ('u32 wordLength', 'u32 length', 'u16* word'): 19 differing. src size 0x6f8 base size 0x6f8

ZI50 helper copies ('wordLength',): 19 differing. src size 0x6f8 base size 0x6f8

ZI51 helper copies ('length',): 19 differing. src size 0x6f8 base size 0x6f8

ZI52 helper copies ('word',): 214 differing. src size 0x6f4 base size 0x6f8

ZI53 helper copies ('wordLength', 'length'): 19 differing. src size 0x6f8 base size 0x6f8

ZI54 helper copies ('length', 'wordLength'): 19 differing. src size 0x6f8 base size 0x6f8

ZI55 helper copies ('word', 'wordLength', 'length'): 218 differing. src size 0x6f4 base size 0x6f8

ZI56 helper copies ('length', 'word', 'wordLength'): 218 differing. src size 0x6f4 base size 0x6f8

ZI57 source/destination helper source[copied] order 0: 19 differing. src size 0x6f8 base size 0x6f8

ZI58 source/destination helper source[copied] order 1: 19 differing. src size 0x6f8 base size 0x6f8

ZI59 source/destination helper *(source + copied) order 0: 19 differing. src size 0x6f8 base size 0x6f8

ZI60 source/destination helper *(source + copied) order 1: 19 differing. src size 0x6f8 base size 0x6f8

ZI61 source/destination helper source[offset + copied] order 0: 19 differing. src size 0x6f8 base size 0x6f8

ZI62 source/destination helper source[offset + copied] order 1: 19 differing. src size 0x6f8 base size 0x6f8

ZI63 source/destination helper const source[copied] order 0: 19 differing. src size 0x6f8 base size 0x6f8

ZI64 source/destination helper const source[copied] order 1: 19 differing. src size 0x6f8 base size 0x6f8

ZI65 source/destination helper const *(source + copied) order 0: 19 differing. src size 0x6f8 base size 0x6f8

ZI66 source/destination helper const *(source + copied) order 1: 19 differing. src size 0x6f8 base size 0x6f8

ZI67 source/destination helper const source[offset + copied] order 0: 19 differing. src size 0x6f8 base size 0x6f8

ZI68 source/destination helper const source[offset + copied] order 1: 19 differing. src size 0x6f8 base size 0x6f8

ES1 titleId received by value and copied into last local: 116 differing. src size 0x704 base size 0x704

ZI69 helper offset before wordLength - length: 186 differing. src size 0x6f4 base size 0x6f8

ZI70 helper offset before wordLength + -length: 186 differing. src size 0x6f4 base size 0x6f8

ZI71 helper offset after wordLength - length: 186 differing. src size 0x6f4 base size 0x6f8

ZI72 helper offset after wordLength + -length: 186 differing. src size 0x6f4 base size 0x6f8

ZI73 helper expression word[copied + (wordLength - length)]: 19 differing. src size 0x6f8 base size 0x6f8

ZI74 helper expression word[wordLength + copied - length]: 232 differing. src size 0x744 base size 0x6f8

ZI75 helper expression *(word + (wordLength - length) + copied): 19 differing. src size 0x6f8 base size 0x6f8

ZI76 helper loop u32 remaining = length;: 216 differing. src size 0x6c4 base size 0x6f8

ZI77 helper loop u32 copied = 0;: 19 differing. src size 0x6f8 base size 0x6f8

ES2 reverse paired desired locals: 34 differing. src size 0x704 base size 0x704

ES3 forward paired desired locals: 158 differing. src size 0x704 base size 0x704

ES4 reverse paired desired by ref: 403 differing. src size 0x70c base size 0x704

ES5 forward paired desired by ref: 412 differing. src size 0x70c base size 0x704

ES6 reverse paired desired by pointer: 34 differing. src size 0x704 base size 0x704

ES7 forward paired desired by pointer: 158 differing. src size 0x704 base size 0x704

ES8 InitSavedata declarations ('titleIds', 'ret', 'ticketScratch', 'i'): 34 differing. src size 0x704 base size 0x704

ES9 Init declarations ('titleIds', 'ret', 'ticketScratch', 'i') and ticket order: 20 differing. src size 0x704 base size 0x704

ES10 InitSavedata declarations ('titleIds', 'ret', 'i', 'ticketScratch'): 30 differing. src size 0x704 base size 0x704

ES11 Init declarations ('titleIds', 'ret', 'i', 'ticketScratch') and ticket order: 16 differing. src size 0x704 base size 0x704

ES12 InitSavedata declarations ('titleIds', 'ticketScratch', 'ret', 'i'): 39 differing. src size 0x704 base size 0x704

ES13 Init declarations ('titleIds', 'ticketScratch', 'ret', 'i') and ticket order: 25 differing. src size 0x704 base size 0x704

ES14 InitSavedata declarations ('titleIds', 'ticketScratch', 'i', 'ret'): 39 differing. src size 0x704 base size 0x704

ES15 Init declarations ('titleIds', 'ticketScratch', 'i', 'ret') and ticket order: 25 differing. src size 0x704 base size 0x704

ES16 InitSavedata declarations ('titleIds', 'i', 'ret', 'ticketScratch'): 35 differing. src size 0x704 base size 0x704

ES17 Init declarations ('titleIds', 'i', 'ret', 'ticketScratch') and ticket order: 21 differing. src size 0x704 base size 0x704

ES18 InitSavedata declarations ('titleIds', 'i', 'ticketScratch', 'ret'): 39 differing. src size 0x704 base size 0x704

ES19 Init declarations ('titleIds', 'i', 'ticketScratch', 'ret') and ticket order: 25 differing. src size 0x704 base size 0x704

ES20 InitSavedata declarations ('ret', 'titleIds', 'ticketScratch', 'i'): 39 differing. src size 0x704 base size 0x704

ES21 Init declarations ('ret', 'titleIds', 'ticketScratch', 'i') and ticket order: 25 differing. src size 0x704 base size 0x704

ES22 InitSavedata declarations ('ret', 'titleIds', 'i', 'ticketScratch'): 35 differing. src size 0x704 base size 0x704

ES23 Init declarations ('ret', 'titleIds', 'i', 'ticketScratch') and ticket order: 21 differing. src size 0x704 base size 0x704

ES24 InitSavedata declarations ('ret', 'ticketScratch', 'titleIds', 'i'): 28 differing. src size 0x704 base size 0x704

ZI78 helper computes word length, local order 0 u16* word, u32 length: 2 differing. src size 0x6f8 base size 0x6f8

ZI79 helper computes word length, local order 0 u32 length, u16* word: 2 differing. src size 0x6f8 base size 0x6f8

ZI80 helper computes word length, local order 1 u16* word, u32 length: 2 differing. src size 0x6f8 base size 0x6f8

ZI81 helper computes word length, local order 1 u32 length, u16* word: 2 differing. src size 0x6f8 base size 0x6f8

ES25 Init declarations ('ret', 'ticketScratch', 'titleIds', 'i') and ticket order: 14 differing. src size 0x704 base size 0x704

ES26 InitSavedata declarations ('ret', 'ticketScratch', 'i', 'titleIds'): 39 differing. src size 0x704 base size 0x704

ES27 Init declarations ('ret', 'ticketScratch', 'i', 'titleIds') and ticket order: 25 differing. src size 0x704 base size 0x704

ES28 InitSavedata declarations ('ret', 'i', 'titleIds', 'ticketScratch'): 24 differing. src size 0x704 base size 0x704

ES29 Init declarations ('ret', 'i', 'titleIds', 'ticketScratch') and ticket order: 10 differing. src size 0x704 base size 0x704

ES30 InitSavedata declarations ('ret', 'i', 'ticketScratch', 'titleIds'): 39 differing. src size 0x704 base size 0x704

ES31 Init declarations ('ret', 'i', 'ticketScratch', 'titleIds') and ticket order: 25 differing. src size 0x704 base size 0x704

ES32 InitSavedata declarations ('ticketScratch', 'titleIds', 'ret', 'i'): 39 differing. src size 0x704 base size 0x704

ES33 Init declarations ('ticketScratch', 'titleIds', 'ret', 'i') and ticket order: 25 differing. src size 0x704 base size 0x704

ES34 InitSavedata declarations ('ticketScratch', 'titleIds', 'i', 'ret'): 39 differing. src size 0x704 base size 0x704

ES35 Init declarations ('ticketScratch', 'titleIds', 'i', 'ret') and ticket order: 25 differing. src size 0x704 base size 0x704

ES36 InitSavedata declarations ('ticketScratch', 'ret', 'titleIds', 'i'): 23 differing. src size 0x704 base size 0x704

ZI82 key copy loop iteration ++keyIndex, keyOutput += 0x40: 2 differing. src size 0x6f8 base size 0x6f8

ZI83 key copy loop iteration keyOutput += 0x40, ++keyIndex: 2 differing. src size 0x6f8 base size 0x6f8

ZI84 key copy loop body index then output: 2 differing. src size 0x6f8 base size 0x6f8

ES37 Init declarations ('ticketScratch', 'ret', 'titleIds', 'i') and ticket order: 9 differing. src size 0x704 base size 0x704

ES38 InitSavedata declarations ('ticketScratch', 'ret', 'i', 'titleIds'): 34 differing. src size 0x704 base size 0x704

ES39 Init declarations ('ticketScratch', 'ret', 'i', 'titleIds') and ticket order: 20 differing. src size 0x704 base size 0x704

ES40 InitSavedata declarations ('ticketScratch', 'i', 'titleIds', 'ret'): 28 differing. src size 0x704 base size 0x704

ES41 Init declarations ('ticketScratch', 'i', 'titleIds', 'ret') and ticket order: 14 differing. src size 0x704 base size 0x704

ES42 InitSavedata declarations ('ticketScratch', 'i', 'ret', 'titleIds'): 39 differing. src size 0x704 base size 0x704

ES43 Init declarations ('ticketScratch', 'i', 'ret', 'titleIds') and ticket order: 25 differing. src size 0x704 base size 0x704

ES44 InitSavedata declarations ('i', 'titleIds', 'ret', 'ticketScratch'): 32 differing. src size 0x704 base size 0x704

ES45 Init declarations ('i', 'titleIds', 'ret', 'ticketScratch') and ticket order: 18 differing. src size 0x704 base size 0x704

ES46 InitSavedata declarations ('i', 'titleIds', 'ticketScratch', 'ret'): 36 differing. src size 0x704 base size 0x704

ES47 Init declarations ('i', 'titleIds', 'ticketScratch', 'ret') and ticket order: 22 differing. src size 0x704 base size 0x704

ES48 InitSavedata declarations ('i', 'ret', 'titleIds', 'ticketScratch'): 16 differing. src size 0x704 base size 0x704

ES49 Init declarations ('i', 'ret', 'titleIds', 'ticketScratch') and ticket order: 2 differing. src size 0x704 base size 0x704

ES50 InitSavedata declarations ('i', 'ret', 'ticketScratch', 'titleIds'): 31 differing. src size 0x704 base size 0x704

ES51 Init declarations ('i', 'ret', 'ticketScratch', 'titleIds') and ticket order: 17 differing. src size 0x704 base size 0x704

ES52 InitSavedata declarations ('i', 'ticketScratch', 'titleIds', 'ret'): 25 differing. src size 0x704 base size 0x704

ES53 Init declarations ('i', 'ticketScratch', 'titleIds', 'ret') and ticket order: 11 differing. src size 0x704 base size 0x704

ES54 InitSavedata declarations ('i', 'ticketScratch', 'ret', 'titleIds'): 36 differing. src size 0x704 base size 0x704

ES55 Init declarations ('i', 'ticketScratch', 'ret', 'titleIds') and ticket order: 22 differing. src size 0x704 base size 0x704

ES56 initialize valid before j: 0 differing. src size 0x704 base size 0x704

ZI85 key source expression *(static_cast<keyboard::cellphonetype::PaneNameToCharCode*>(mpHoldingKey)->wc + keyIndex - 1): 2 differing. src size 0x6f8 base size 0x6f8

ZI86 key source expression static_cast<keyboard::cellphonetype::PaneNameToCharCode*>(mpHoldingKey)->wc[-1 + keyIndex]: 2 differing. src size 0x6f8 base size 0x6f8

ZI87 key source expression (static_cast<keyboard::cellphonetype::PaneNameToCharCode*>(mpHoldingKey)->wc - 1)[keyIndex]: 2 differing. src size 0x6f8 base size 0x6f8

ZI88 key source expression static_cast<keyboard::cellphonetype::PaneNameToCharCode*>(mpHoldingKey)->wc[keyIndex + -1]: 2 differing. src size 0x6f8 base size 0x6f8

ZI89 swap keyOutput declaration with keyIndex: 15 differing. src size 0x6f8 base size 0x6f8

ZI90 swap keyOutput declaration with keyCharacter: 2 differing. src size 0x6f8 base size 0x6f8

ZI91 swap keyOutput declaration with koreanOutput: 2 differing. src size 0x6f8 base size 0x6f8

ZI92 swap keyOutput declaration with index: 35 differing. src size 0x6f8 base size 0x6f8

ZI93 swap keyOutput declaration with source: 30 differing. src size 0x6f8 base size 0x6f8

ZI94 swap keyOutput declaration with elementCount: 44 differing. src size 0x6f8 base size 0x6f8

ZI95 key destination increment keyOutput = keyOutput + 0x40: 2 differing. src size 0x6f8 base size 0x6f8

ZI96 key destination increment keyOutput = 0x40 + keyOutput: 2 differing. src size 0x6f8 base size 0x6f8

ZI97 key destination increment keyOutput += 64: 2 differing. src size 0x6f8 base size 0x6f8

ZI98 preincrement key destination: 347 differing. src size 0x6f4 base size 0x6f8

ZI99 key destination base plus indexed offset: 353 differing. src size 0x6f4 base size 0x6f8

ZI100 key destination indexed by keyIndex: 0 differing. src size 0x6f8 base size 0x6f8

Both requested functions reached zero differing with equal size. ZI100 also indexes the key output by keyIndex, removing the final induction-update scheduling pair. ES56 initializes valid before j, removing its final scheduling pair. No configure status change yet; unit-wide checks follow.

Unit-wide objdiff after the exact source edits: tiZiString 29/29 functions, 5504/5504 code, 7680/7680 data, every section 100%; iplESMisc 31/31 functions, 11200/11200 code, 4416/4416 data, every section 100%. Pools identical; ctxdiff update 446/446 instructions, diffs 0; DeleteUnauthorizedData 449/449 instructions, diffs 0. Both configure entries changed to Matching.

Initial full gate failed despite all owned code/data exact: DOL a9c0db300b393a94c498af7a6ef5a710f804edcb. Isolating configure entries showed tiZiString linking preserves the failure hash; both NonMatching restore the target hash. dtk dol diff proved checkForNullTermination and DeleteUnauthorizedData were emitted in reverse object order. Reordered these two definitions to symbols.txt order without changing their bodies.

Final gate after definition-order repair:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 5504/5504 data 7680/7680 functions 29/29 fuzzy 100.0000 linked code 5504
[src/keyboard/tiZiString] instruction-exact functions: 29/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 100.0
[src/keyboard/tiZiString] baseline: code 3720/5504 data 7680 functions 28 fuzzy 99.4717
[src/utility/iplESMisc] pool: IDENTICAL
[src/utility/iplESMisc] objdiff: code 11200/11200 data 4416/4416 functions 31/31 fuzzy 100.0000 linked code 11200
[src/utility/iplESMisc] instruction-exact functions: 31/31
[src/utility/iplESMisc]   section .data size 4384 match 100.0
[src/utility/iplESMisc]   section .sdata size 32 match 100.0
[src/utility/iplESMisc]   section .text size 11200 match 100.0
[src/utility/iplESMisc] baseline: code 9404/11200 data 4416 functions 30 fuzzy 99.8625
regressions vs baseline: 0
global matched_code_percent: 97.29338 -> 97.41291
global fuzzy_match_percent: 99.88914 -> 99.89063
global complete_code_percent: 88.00925 -> 88.56695
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: configure.py (orchestrator reviews every config/symbols change)
GATE PASS
```

Final ctxdiff: update 446/446, diffs 0; DeleteUnauthorizedData 449/449, diffs 0. Both exact and linked.

Allocator captures: baseline tiZiString `_mwdbg/runs/update__Q39textinput8tistring6WithZiFv-20261008-193010`; ordered locals `...-20261008-193122`; baseline iplESMisc `_mwdbg/runs/DeleteUnauthorizedData__Q33ipl7utility6ESMiscFPQ23EGG4Heap-20261008-193201`; titleId-copy `...-20261008-193510`. Baseline regsim reproduces 161/161. Paired titleId constrained simulation found 64/64 wants. Generated trial scripts, reports and raw logs are retained locally under build/sol-ties.

ES exact implementation and its Matching entry committed as 0b3c7842. tiZiString exact implementation and its Matching entry follow in a separate commit. The final gate above covers the combined tree.
