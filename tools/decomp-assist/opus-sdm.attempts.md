# opus-sdm: iplSaveDataManager asm -> C

Branch agent/w1008/data-d6-b, base a3f8fc27. Scored with odiff (differing / total) and objdiff fuzzy.
Pool identical (3/3) for every compiled trial. doUpdateChanInfos untouched. Best text: opus-sdm.best.cpp.

## hasChannel__Q33ipl8savedata7ManagerCFUxPiPi (start 14 diffs / 98.87%)

| # | Change | odiff |
|---|---|---|
| h1 | channel::Manager::hasChannel shape on mData.chanInfo, for/for loops, TITLE_REGION test | 54 |
| h2 | `(u8)titleId == 'A'` region test | 62 |
| h3 | h1 with outer do/while page loop | 54 |
| h40 | h3 + `(ESTitleId)(u8)titleId == TITLE_REGION_ALL` | 47 |
| h41-43 | u8 / u64 / casted constant spellings of the region test | 62 / 47 / 47 |
| h50 | `TITLE_NO_REGION(tId & mask) == TITLE_NO_REGION(titleId & mask)` | 53 |
| h51 | code mask inlined in the comparison | 47 |
| **h52** | code mask `titleCode` declared inside the primaryType block (stops the titleId & titleCode hoist) | **12 (99.014%)** |
| h6a | h52 with for page loop | 16 |
| h6b | mask via if/else (!= 0 first) | 12 |
| h6c | mask via if/else (== 0 first): swaps full/code mask registers | 13 |
| h6d | ternary == 0 first | 13 |
| h6e | `titleCodeRegion & ~0xFFULL` | 12 |
| h6f | no titleCode local | 47 |
| h6g | page declared then assigned | 12 |
| h7b1-b5 | const titleCode, function-scope titleCode, after tId, top of index loop, const full mask | 12 each |
| h7c1-c4 | same four on the == 0 if/else | 13 each |
| h8t/i0-6 | ternary and if/else for: bare ES_TITLE_TYPE, !type, >>32, & hi mask !=/== 0, > / <= 0xFFFFFFFF | 12-70 |
| h9r/p | slot reference / pointer | 59 |
| h9d | inner do/while | 61 |
| h9x | index declared at top | 19 |
| h9q | while page loop | 16 |
| hAt/u | tId declared at function / page scope | 22 / 18 |
| hAv | full mask declared after page | 18 |
| hAw | `continue` on non-channel slot | 12 |
| hB1-6 | operand order of both comparisons | 12 / 16 |

Stuck at 12: full mask lo/hi in r9/r0 (target r10/r9), mask constants r10/r4 (target r4/r0), row base r10 (target r0).
The == 0 if/else puts row base on r0 but then gives the full mask r12/r11 and the code mask r10/r9 (reversed).
Kept asm.

## makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl (start 80.2%, 124/133)

| # | Change | odiff |
|---|---|---|
| p1 | page/index loops, outputIndex local, u32 input loop with continue, photo replacement nested if | 96 (75.53%, 122/133) |
| pda1 | da1 prior-4 text, for reference | 118 |
| p2 | nested if instead of continue | 96 |
| p3 | output index expression at each use | 123 (spills) |
| p4 | int input counter | 96 |
| p5 | inline isNullTitle(const ESTitleId&) helper | 97 |
| p6 | `!x` / `x` null tests | 96 |
| p7 | outputIndex computed after the input null check | 118 |
| p8 | while input loop | 105 |
| p9 | output title read into a local | 96 |
| pa | photo replacement as static inline helper | 115 |
| pb | TITLE_NO_REGION repeated per comparison | 96 |
| pc | photo test and mPhotoId test in one condition | 96 |

Blocker: the target never CSEs &titleIdsIn[i] or &titleIdsOut[outputIndex] (recomputes add/slwi at every use, even
inside one block) and reloads titleIdsIn[i] for isEqualChannel, while hoisting -0x100 and 0x48410000 into r14/r26.
Every C spelling tried caches both addresses and leaves -0x100 unhoisted, so 122 vs 133 instructions. Kept asm.
