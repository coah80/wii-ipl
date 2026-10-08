# sol-x14 SDMemory attempts

Baseline branch agent/w1008/w0929-fix-board-y. Only iplSDMemory.cpp and this log are owned. Existing untracked rx61-work and rx69 log are untouched.

Initial object already built. Baseline create 175/1064 differences, equal size; drawTransferTitles 371/451 differences, 438/451 instructions. Pool identical. Scoped IRO 1 authorized by task and levers 26/30.

- create swap cached count/saveData declarations: 5 differing, 1064/1064 instructions; other-function drops [].

- create cached count declared at initialization: 5 differing, 1064/1064 instructions; other-function drops [].

- create count initialized before saveData accessor: 5 differing, 1064/1064 instructions; other-function drops [].

- create postfix count increment: 5 differing, 1064/1064 instructions; other-function drops [].

- draw scoped IRO 1: 287 differing, 451/451 instructions; other-function drops [].

- draw scoped IRO 0: 287 differing, 451/451 instructions; other-function drops [].

- create cached-title pointer named at first use: 543 differing, 1065/1064 instructions; other-function drops [].

- create loop result reused as actual title count: 5 differing, 1064/1064 instructions; other-function drops [].

- create prefix loop index: 5 differing, 1064/1064 instructions; other-function drops [].

- create test title entry as boolean: 5 differing, 1064/1064 instructions; other-function drops [].

- create scoped saveData with count kept root: 5 differing, 1064/1064 instructions; other-function drops [].

- create count-index single for expression: 14 differing, 1064/1064 instructions; other-function drops [].

- create cache walker actual pointer loop: 541 differing, 1063/1064 instructions; other-function drops [].

- create actual count helper: 0 differing, 1064/1064 instructions; other-function drops [].

- create exact: helper countCachedTitles plus scoped IRO 1. Last five differences were cachedTitleCount r49 allocated r6 instead of r5, and System save-data pointer r136 r5 instead of r6. mwdbg replay 727/727. Corrected regsim excluding compiler @ temporaries reaches 0/2 wanted registers with 3000 declaration trials; structural helper fixes both. Pool 90/90 identical, ctxdiff 1064/1064 and diffs 0. Exact-name objdiff 100.0%; unit 64/66 -> 65/66, matched code 14812 -> 19068 / 20872, data 3344/3344. Every other function unchanged. Capture /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect-20261008-215212.

- draw newline initial guard and for: 388 differing, 453/451 instructions; other-function drops [].

- draw line loop guarded counted for: 287 differing, 451/451 instructions; other-function drops [].

- draw remove unused color copies: 381 differing, 443/451 instructions; other-function drops [].

- draw ceil double converted directly to s32: 357 differing, 450/451 instructions; other-function drops [].

- draw target loop shape and only used color copies: 390 differing, 445/451 instructions; other-function drops [].

- draw all real scalar declarations forward IRO1: 290 differing, 451/451 instructions; other-function drops [].

- draw all real scalar declarations reverse IRO1: 285 differing, 451/451 instructions; other-function drops [].

- draw reverse declarations with initial newline guard IRO1: 386 differing, 453/451 instructions; other-function drops [].

- draw reverse declarations with initial newline guard IRO0: 386 differing, 453/451 instructions; other-function drops [].

- draw guard repeated while IRO0: 388 differing, 453/451 instructions; other-function drops [].

- draw prior best shape replay with exact create IRO0: 263 differing, 451/451 instructions; other-function drops [('__ne__Q24nw4r2utFQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8IteratorQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8Iterator', (0, 6, 6), (6, 8, 6))].

- draw prior helper shape scoped IRO1: 263 differing, 451/451 instructions; other-function drops [('__ne__Q24nw4r2utFQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8IteratorQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8Iterator', (0, 6, 6), (6, 8, 6))].

- draw prior helper shape initial newline guard: 391 differing, 453/451 instructions; other-function drops [('__ne__Q24nw4r2utFQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8IteratorQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8Iterator', (0, 6, 6), (6, 8, 6))].

- draw one child iterator reused for three panes: 287 differing, 451/451 instructions; other-function drops [].

- draw guarded newline do while: 392 differing, 452/451 instructions; other-function drops [].

- draw totalLines compared to zero with existing do loop: 391 differing, 450/451 instructions; other-function drops [].

- draw full line for without separate guard: 391 differing, 450/451 instructions; other-function drops [].

- draw alpha loops explicit for: 287 differing, 451/451 instructions; other-function drops [].

- draw VEC3 copy initialization: 436 differing, 452/451 instructions; other-function drops [].

- draw increment matched nand title before color setup: 282 differing, 451/451 instructions; other-function drops [].

- draw real color copies named as call arguments: 380 differing, 447/451 instructions; other-function drops [].

- draw children alpha helper defined after caller: 263 differing, 451/451 instructions; other-function drops [].

- draw children alpha helper after caller nonconst alpha: 263 differing, 451/451 instructions; other-function drops [].

- draw alpha helper after caller sequential confirmation: 263 differing, 451/451 instructions; other-function drops [].

- draw alpha helper after caller sequential confirmation: 263 differing, 451/451 instructions; other-function drops [].

- draw real newline counter helper: 263 differing, 451/451 instructions; other-function drops [].

- draw newline counter helper guarded while: 391 differing, 453/451 instructions; other-function drops [].

- draw line count helper computes total lines: 263 differing, 451/451 instructions; other-function drops [].

- draw original cached count-loop delimiter: 371 differing, 454/451 instructions; other-function drops [].

- draw original cached draw-loop delimiter and pre-guard index: 393 differing, 452/451 instructions; other-function drops [].

- draw original both real delimiters and target loop entry: 331 differing, 455/451 instructions; other-function drops [].

- draw original only pre-guard index/total positive loop: 287 differing, 451/451 instructions; other-function drops [].

- draw helper cached count-loop delimiter: 370 differing, 454/451 instructions; other-function drops [].

- draw helper cached draw-loop delimiter and pre-guard index: 392 differing, 452/451 instructions; other-function drops [].

- draw helper both real delimiters and target loop entry: 324 differing, 455/451 instructions; other-function drops [].

- draw helper only pre-guard index/total positive loop: 263 differing, 451/451 instructions; other-function drops [].

- draw named gradient colors three: 279 differing, 451/451 instructions; other-function drops [].

- draw named gradient colors direct: 279 differing, 451/451 instructions; other-function drops [].

- draw named gradient colors base-args: 263 differing, 451/451 instructions; other-function drops [].

- draw named gradient colors copy-init: 279 differing, 451/451 instructions; other-function drops [].

- draw named gradient colors two-named: 381 differing, 443/451 instructions; other-function drops [].

- draw solid-color helper reference: 379 differing, 431/451 instructions; other-function drops [].

- draw solid-color helper value: 378 differing, 439/451 instructions; other-function drops [].

- draw solid-color helper pointer: 379 differing, 431/451 instructions; other-function drops [].

- draw solid-color helper reference and delimiters: 311 differing, 435/451 instructions; other-function drops [].

- draw solid-color helper value and delimiters: 314 differing, 443/451 instructions; other-function drops [].

- draw solid-color helper pointer and delimiters: 311 differing, 435/451 instructions; other-function drops [].

- Newline-helper forward-declaration trials initially failed before includes; moved the declaration into ipl::scene and compiled the corrected three variants recorded above.
- draw real-color call-argument trial and alpha-helper declaration trial briefly overlapped; their first outputs are advisory. The alpha helper after caller was recompiled sequentially and confirmed 263 differing with no other-function changes.

## Source search

180 seconds, seed 14, 128 source mutation trials from the private 263-difference candidate. Full mutation records retained in /tmp/sol-x14-search14/trials.jsonl; search output /tmp/sol-x14-search14.log. Search improvements were fuzzy only and remain private. Each trial below lists draw instruction count and objdiff score; the source mutation follows.

- Search trial 1: compile failed; ---  | +++  | @@ -147 +147 @@ | -                ++footerChild; | +                footerChild = footerChild + 1; |

- Search trial 2: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -15 +15 @@ | -            s32 totalLines; | +            u32 totalLines; |

- Search trial 3: 451 instructions, objdiff 92.85809; ---  | +++  | @@ -5,0 +6 @@ | +            nw4r::lyt::TextBox* titleText; | @@ -7 +7,0 @@ | -            nw4r::lyt::TextBox* titleText; |

- Search trial 4: 451 instructions, objdiff 92.85809; ---  | +++  | @@ -3,0 +4 @@ | +            f32 rowTop; | @@ -5 +5,0 @@ | -            f32 rowTop; |

- Search trial 5: 451 instructions, objdiff 92.85809; ---  | +++  | @@ -105 +105 @@ | -                    ++nandTitleIndex; | +                    nandTitleIndex++; |

- Search trial 6: 451 instructions, objdiff 92.80266; ---  | +++  | @@ -9,0 +10 @@ | +            f32 backgroundOffset; | @@ -11 +11,0 @@ | -            f32 backgroundOffset; |

- Search trial 7: 451 instructions, objdiff 92.80266; ---  | +++  | @@ -21,0 +22 @@ | +            u8 alpha; | @@ -23 +23,0 @@ | -            u8 alpha; |

- Search trial 8: 451 instructions, objdiff 92.80266; ---  | +++  | @@ -82 +82 @@ | -                    messageOffset -= bodyHeight; | +                    messageOffset = messageOffset - bodyHeight; |

- Search trial 9: 451 instructions, objdiff 92.80266; ---  | +++  | @@ -11,0 +12 @@ | +            const wchar_t* lineEnd; | @@ -13 +13,0 @@ | -            const wchar_t* lineEnd; |

- Search trial 10: 451 instructions, objdiff 92.80266; ---  | +++  | @@ -4,0 +5 @@ | +            nw4r::lyt::TextBox* titleText; | @@ -6 +6,0 @@ | -            nw4r::lyt::TextBox* titleText; |

- Search trial 11: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -14 +14 @@ | -            s32 lineIndex; | +            unsigned int lineIndex; |

- Search trial 12: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -52 +52 @@ | -                while (newline != NULL) { | +                while (NULL != newline) { |

- Search trial 13: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -6,0 +7 @@ | +            f32 rowHeight; | @@ -8 +8,0 @@ | -            f32 rowHeight; |

- Search trial 14: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -83 +83 @@ | -                    ++lineIndex; | +                    lineIndex += 1; |

- Search trial 15: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -16,0 +17 @@ | +            const wchar_t* newline; | @@ -18 +18,0 @@ | -            const wchar_t* newline; |

- Search trial 16: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -6,0 +7 @@ | +            u32 nandTitleIndex; | @@ -8 +8,0 @@ | -            u32 nandTitleIndex; |

- Search trial 17: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -21,0 +22 @@ | +            f32 messageOffset; | @@ -23 +23,0 @@ | -            f32 messageOffset; |

- Search trial 18: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -7 +7 @@ | -            u32 nandTitleIndex; | +            int nandTitleIndex; |

- Search trial 19: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -147 +147 @@ | -                ++footerChild; | +                footerChild++; |

- Search trial 20: compile failed; ---  | +++  | @@ -147 +147 @@ | -                footerChild++; | +                footerChild += 1; |

- Search trial 21: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -19,0 +20 @@ | +            f32 bodyHeight; | @@ -21 +21,0 @@ | -            f32 bodyHeight; |

- Search trial 22: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -147 +147 @@ | -                footerChild++; | +                ++footerChild; |

- Search trial 23: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -15 +15 @@ | -            s32 totalLines; | +            u32 totalLines; |

- Search trial 24: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -124 +124 @@ | -                    rowY = bodyY + backgroundOffset; | +                    rowY = backgroundOffset + bodyY; |

- Search trial 25: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -52,0 +53 @@ | +                    newline = wcsstr(newline + 1, L"\n"); | @@ -54 +54,0 @@ | -                    newline = wcsstr(newline + 1, L"\n"); |

- Search trial 26: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -7,0 +8 @@ | +            nw4r::lyt::Pane* titleSizePane; | @@ -9 +9,0 @@ | -            nw4r::lyt::Pane* titleSizePane; |

- Search trial 27: compile failed; ---  | +++  | @@ -147 +147 @@ | -                ++footerChild; | +                footerChild = footerChild + 1; |

- Search trial 28: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -82 +82 @@ | -                    messageOffset = messageOffset - bodyHeight; | +                    messageOffset -= bodyHeight; |

- Search trial 29: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -105 +105 @@ | -                    nandTitleIndex++; | +                    nandTitleIndex += 1; |

- Search trial 30: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -82 +82 @@ | -                    messageOffset -= bodyHeight; | +                    messageOffset = messageOffset - bodyHeight; |

- Search trial 31: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -88,0 +89 @@ | +            titleOffset = 79.5f + messageOffset; | @@ -90 +90,0 @@ | -            titleOffset = 79.5f + messageOffset; |

- Search trial 32: compile failed; ---  | +++  | @@ -147 +147 @@ | -                ++footerChild; | +                footerChild += 1; |

- Search trial 33: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -19 +19 @@ | -            s32 lineCount; | +            unsigned int lineCount; |

- Search trial 34: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -7 +7 @@ | -            int nandTitleIndex; | +            u32 nandTitleIndex; |

- Search trial 35: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -72 +72 @@ | -                        messageLine = lineEnd + 1; | +                        messageLine = 1 + lineEnd; |

- Search trial 36: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -13 +13 @@ | -            u32 lineLength; | +            s32 lineLength; |

- Search trial 37: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -13 +13 @@ | -            s32 lineLength; | +            int lineLength; |

- Search trial 38: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -147 +147 @@ | -                ++footerChild; | +                footerChild++; |

- Search trial 39: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -88,0 +89 @@ | +            backgroundOffset = 40.0f + messageOffset; | @@ -90 +90,0 @@ | -            backgroundOffset = 40.0f + messageOffset; |

- Search trial 40: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -15 +15 @@ | -            u32 totalLines; | +            unsigned int totalLines; |

- Search trial 41: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -139 +139 @@ | -                titleOffset -= rowHeight * static_cast<f32>(visibleRows); | +                titleOffset = titleOffset - (rowHeight * static_cast<f32>(visibleRows)); |

- Search trial 42: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -131 +131 @@ | -                    backgroundOffset -= rowHeight; | +                    backgroundOffset = backgroundOffset - rowHeight; |

- Search trial 43: compile failed; ---  | +++  | @@ -43 +43 @@ | -                ++child; | +                child = child + 1; |

- Search trial 44: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -7 +7 @@ | -            u32 nandTitleIndex; | +            int nandTitleIndex; |

- Search trial 45: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -52 +52 @@ | -                while (NULL != newline) { | +                while (newline != NULL) { |

- Search trial 46: compile failed; ---  | +++  | @@ -43 +43 @@ | -                ++child; | +                child = child + 1; |

- Search trial 47: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -90 +90 @@ | -            titleOffset = 79.5f + messageOffset; | +            titleOffset = messageOffset + 79.5f; |

- Search trial 48: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -124 +124 @@ | -                    rowY = backgroundOffset + bodyY; | +                    rowY = bodyY + backgroundOffset; |

- Search trial 49: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -52 +52 @@ | -                while (newline != NULL) { | +                while (NULL != newline) { |

- Search trial 50: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -90 +90 @@ | -            titleOffset = messageOffset + 79.5f; | +            titleOffset = 79.5f + messageOffset; |

- Search trial 51: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -147 +147 @@ | -                footerChild++; | +                ++footerChild; |

- Search trial 52: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -7,0 +8 @@ | +            f32 rowHeight; | @@ -9 +9,0 @@ | -            f32 rowHeight; |

- Search trial 53: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -131 +131 @@ | -                    backgroundOffset = backgroundOffset - rowHeight; | +                    backgroundOffset -= rowHeight; |

- Search trial 54: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -83 +83 @@ | -                    lineIndex += 1; | +                    lineIndex++; |

- Search trial 55: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -60 +60 @@ | -                totalLines = lineCount + 1; | +                totalLines = 1 + lineCount; |

- Search trial 56: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -43 +43 @@ | -                ++child; | +                child++; |

- Search trial 57: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -142 +142 @@ | -            backgroundOffset += rowHeight; | +            backgroundOffset = backgroundOffset + rowHeight; |

- Search trial 58: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -21,0 +22 @@ | +            u8 alpha; | @@ -23 +23,0 @@ | -            u8 alpha; |

- Search trial 59: compile failed; ---  | +++  | @@ -147 +147 @@ | -                ++footerChild; | +                footerChild += 1; |

- Search trial 60: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -54 +54 @@ | -                    ++lineCount; | +                    lineCount = lineCount + 1; |

- Search trial 61: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -124 +124 @@ | -                    rowY = bodyY + backgroundOffset; | +                    rowY = backgroundOffset + bodyY; |

- Search trial 62: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -1,0 +2 @@ | +            f32 rowY; | @@ -3 +3,0 @@ | -            f32 rowY; |

- Search trial 63: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -2,0 +3 @@ | +            f32 rowTop; | @@ -4 +4,0 @@ | -            f32 rowTop; |

- Search trial 64: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -142 +142 @@ | -            backgroundOffset = backgroundOffset + rowHeight; | +            backgroundOffset = rowHeight + backgroundOffset; |

- Search trial 65: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -15,0 +16 @@ | +            const wchar_t* newline; | @@ -17 +17,0 @@ | -            const wchar_t* newline; |

- Search trial 66: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -22,0 +23 @@ | +            nw4r::lyt::Pane* bodyPane; | @@ -24 +24,0 @@ | -            nw4r::lyt::Pane* bodyPane; |

- Search trial 67: 451 instructions, objdiff 92.691795; ---  | +++  | @@ -60 +60 @@ | -                totalLines = 1 + lineCount; | +                totalLines = lineCount + 1; |

- Search trial 68: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -142 +142 @@ | -            backgroundOffset = rowHeight + backgroundOffset; | +            backgroundOffset = backgroundOffset + rowHeight; |

- Search trial 69: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -23,0 +24 @@ | +            f32 bodyY; | @@ -25 +25,0 @@ | -            f32 bodyY; |

- Search trial 70: 451 instructions, objdiff 92.68071; ---  | +++  | @@ -23,0 +24 @@ | +            f32 messageOffset; | @@ -25 +25,0 @@ | -            f32 messageOffset; |

- Search trial 71: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -9,0 +10 @@ | +            f32 titleOffset; | @@ -11 +11,0 @@ | -            f32 titleOffset; |

- Search trial 72: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -48 +48 @@ | -            if (mNandTitleCount != 0) { | +            if (0 != mNandTitleCount) { |

- Search trial 73: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -54 +54 @@ | -                    lineCount = lineCount + 1; | +                    ++lineCount; |

- Search trial 74: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -7 +7 @@ | -            int nandTitleIndex; | +            s32 nandTitleIndex; |

- Search trial 75: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -19,0 +20 @@ | +            const wchar_t* messageForCount; | @@ -21 +21,0 @@ | -            const wchar_t* messageForCount; |

- Search trial 76: compile failed; ---  | +++  | @@ -147 +147 @@ | -                ++footerChild; | +                footerChild = footerChild + 1; |

- Search trial 77: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -142 +142 @@ | -            backgroundOffset = backgroundOffset + rowHeight; | +            backgroundOffset += rowHeight; |

- Search trial 78: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -21,0 +22 @@ | +            nw4r::lyt::Pane* bodyPane; | @@ -23 +23,0 @@ | -            nw4r::lyt::Pane* bodyPane; |

- Search trial 79: compile failed; ---  | +++  | @@ -147 +147 @@ | -                ++footerChild; | +                footerChild = footerChild + 1; |

- Search trial 80: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -88 +88 @@ | -            messageOffset += bodyHeight; | +            messageOffset = messageOffset + bodyHeight; |

- Search trial 81: 451 instructions, objdiff 92.736145; ---  | +++  | @@ -88 +88 @@ | -            messageOffset = messageOffset + bodyHeight; | +            messageOffset += bodyHeight; |

- Search trial 82: 451 instructions, objdiff 92.50333; ---  | +++  | @@ -45,0 +46 @@ | +            bodyHeight = bodyPane->GetSize().height; | @@ -47 +47,0 @@ | -            bodyHeight = bodyPane->GetSize().height; |

- Search trial 83: 451 instructions, objdiff 92.50333; ---  | +++  | @@ -83 +83 @@ | -                    lineIndex++; | +                    ++lineIndex; |

- Search trial 84: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -124 +124 @@ | -                    rowY = backgroundOffset + bodyY; | +                    rowY = bodyY + backgroundOffset; |

- Search trial 85: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -6,0 +7 @@ | +            f32 rowHeight; | @@ -8 +8,0 @@ | -            f32 rowHeight; |

- Search trial 86: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -83 +83 @@ | -                    ++lineIndex; | +                    lineIndex += 1; |

- Search trial 87: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -54 +54 @@ | -                    ++lineCount; | +                    lineCount += 1; |

- Search trial 88: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -23,0 +24 @@ | +            f32 bodyY; | @@ -25 +25,0 @@ | -            f32 bodyY; |

- Search trial 89: compile failed; ---  | +++  | @@ -43 +43 @@ | -                child++; | +                child = child + 1; |

- Search trial 90: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -19,0 +20 @@ | +            f32 bodyHeight; | @@ -21 +21,0 @@ | -            f32 bodyHeight; |

- Search trial 91: 451 instructions, objdiff 91.06209; ---  | +++  | @@ -65,3 +65 @@ | -                    if (lineEnd == NULL) { | -                        utility::layout::set_string(messageText, messageLine); | -                    } else { | +                    if (lineEnd != NULL) { | @@ -72,0 +71,2 @@ | +                    } else { | +                        utility::layout::set_string(messageText, messageLine); |

- Search trial 92: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -19,0 +20 @@ | +            const wchar_t* messageForCount; | @@ -21 +21,0 @@ | -            const wchar_t* messageForCount; |

- Search trial 93: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -48 +48 @@ | -            if (0 != mNandTitleCount) { | +            if (mNandTitleCount != 0) { |

- Search trial 94: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -8 +8 @@ | -            s32 nandTitleIndex; | +            u32 nandTitleIndex; |

- Search trial 95: compile failed; ---  | +++  | @@ -43 +43 @@ | -                child++; | +                child += 1; |

- Search trial 96: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -8,0 +9 @@ | +            f32 titleOffset; | @@ -10 +10,0 @@ | -            f32 titleOffset; |

- Search trial 97: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -131 +131 @@ | -                    backgroundOffset -= rowHeight; | +                    backgroundOffset = backgroundOffset - rowHeight; |

- Search trial 98: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -72 +72 @@ | -                        messageLine = 1 + lineEnd; | +                        messageLine = lineEnd + 1; |

- Search trial 99: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -13 +13 @@ | -            int lineLength; | +            u32 lineLength; |

- Search trial 100: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -20,0 +21 @@ | +            nw4r::lyt::Pane* bodyPane; | @@ -22 +22,0 @@ | -            nw4r::lyt::Pane* bodyPane; |

- Search trial 101: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -16,0 +17 @@ | +            const wchar_t* messageLine; | @@ -18 +18,0 @@ | -            const wchar_t* messageLine; |

- Search trial 102: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -83 +83 @@ | -                    lineIndex += 1; | +                    lineIndex++; |

- Search trial 103: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -54 +54 @@ | -                    lineCount += 1; | +                    ++lineCount; |

- Search trial 104: 451 instructions, objdiff 91.06209; ---  | +++  | @@ -65,3 +65 @@ | -                    if (lineEnd == NULL) { | -                        utility::layout::set_string(messageText, messageLine); | -                    } else { | +                    if (lineEnd != NULL) { | @@ -72,0 +71,2 @@ | +                    } else { | +                        utility::layout::set_string(messageText, messageLine); |

- Search trial 105: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -54 +54 @@ | -                    ++lineCount; | +                    lineCount++; |

- Search trial 106: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -48 +48 @@ | -            if (mNandTitleCount != 0) { | +            if (0 != mNandTitleCount) { |

- Search trial 107: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -43 +43 @@ | -                child++; | +                ++child; |

- Search trial 108: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -60 +60 @@ | -                totalLines = lineCount + 1; | +                totalLines = 1 + lineCount; |

- Search trial 109: 451 instructions, objdiff 91.06209; ---  | +++  | @@ -65,3 +65 @@ | -                    if (lineEnd == NULL) { | -                        utility::layout::set_string(messageText, messageLine); | -                    } else { | +                    if (lineEnd != NULL) { | @@ -72,0 +71,2 @@ | +                    } else { | +                        utility::layout::set_string(messageText, messageLine); |

- Search trial 110: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -9,0 +10 @@ | +            f32 backgroundOffset; | @@ -11 +11,0 @@ | -            f32 backgroundOffset; |

- Search trial 111: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -13 +13 @@ | -            u32 lineLength; | +            s32 lineLength; |

- Search trial 112: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -6 +6 @@ | -            s32 visibleRows; | +            int visibleRows; |

- Search trial 113: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -22,0 +23 @@ | +            f32 bodyY; | @@ -24 +24,0 @@ | -            f32 bodyY; |

- Search trial 114: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -142 +142 @@ | -            backgroundOffset += rowHeight; | +            backgroundOffset = backgroundOffset + rowHeight; |

- Search trial 115: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -5,0 +6 @@ | +            f32 rowHeight; | @@ -7 +7,0 @@ | -            f32 rowHeight; |

- Search trial 116: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -43 +43 @@ | -                ++child; | +                child++; |

- Search trial 117: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -1,0 +2 @@ | +            f32 rowTop; | @@ -3 +3,0 @@ | -            f32 rowTop; |

- Search trial 118: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -43 +43 @@ | -                child++; | +                ++child; |

- Search trial 119: compile failed; ---  | +++  | @@ -147 +147 @@ | -                ++footerChild; | +                footerChild += 1; |

- Search trial 120: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -82 +82 @@ | -                    messageOffset = messageOffset - bodyHeight; | +                    messageOffset -= bodyHeight; |

- Search trial 121: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -13 +13 @@ | -            s32 lineLength; | +            int lineLength; |

- Search trial 122: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -16,0 +17 @@ | +            nw4r::lyt::TextBox* messageText; | @@ -18 +18,0 @@ | -            nw4r::lyt::TextBox* messageText; |

- Search trial 123: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -82 +82 @@ | -                    messageOffset -= bodyHeight; | +                    messageOffset = messageOffset - bodyHeight; |

- Search trial 124: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -10,0 +11 @@ | +            const wchar_t* lineEnd; | @@ -12 +12,0 @@ | -            const wchar_t* lineEnd; |

- Search trial 125: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -13 +13 @@ | -            int lineLength; | +            u32 lineLength; |

- Search trial 126: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -83 +83 @@ | -                    lineIndex++; | +                    lineIndex += 1; |

- Search trial 127: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -19,0 +20 @@ | +            nw4r::lyt::Pane* bodyPane; | @@ -21 +21,0 @@ | -            nw4r::lyt::Pane* bodyPane; |

- Search trial 128: 451 instructions, objdiff 92.51441; ---  | +++  | @@ -8 +8 @@ | -            u32 nandTitleIndex; | +            s32 nandTitleIndex; |

## Disposition

- Retain only exact create, already committed as fb00e5ea. drawTransferTitles remains unmodified in the retained source. Its scoped IRO 0 and 1 candidates both compile to 451 instructions with 287 differences. The strongest private instruction candidate has 263 differences, 451/451 instructions, and identical other function instruction scores; its objdiff score 92.84701 is below baseline 93.456764, so it is rejected. Best private diff: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-x14.iplSDMemory.diff.
- draw mwdbg capture /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/drawTransferTitles__Q33ipl5scene8SDMemoryFv-20261008-220103 reproduces 252/252 virtual registers. Target needs cached newline delimiters in two loops, a different guarded line-loop entry, and color argument addresses formed at each call. The source hoists four color addresses across the title loop, causing four extra saved GPRs and a 16-byte larger frame. Named-color copies and real solid-color helper variants did not produce the target layout. No dummy locals, carrier objects, assembly, new volatile fields, or artificial offsets were retained.
- Unit remains NonMatching because drawTransferTitles is open. configure.py untouched.

- draw constrained declaration-number simulator search: 1500 steps, 1/7 requested colors. The unconstrained shared simulator also permutes compiler @ temporaries; such output is not a source declaration solution. The constrained copy and output remain /tmp/sol-x14-regsim-real.py and /tmp/sol-x14-draw-regsim.txt.

## Final gate

Command: python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/scene/sdChannelMemory/iplSDMemory --quick

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 19068/20872 data 3344/3344 functions 65/66 fuzzy 99.4345 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 65/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.434456
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 93.456764
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14812/20872 data 3344 functions 64 fuzzy 99.2629
regressions vs baseline: 0
global matched_code_percent: 97.58331 -> 97.72541
global fuzzy_match_percent: 99.89996 -> 99.90116
global complete_code_percent: 88.95958 -> 88.95958
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: src/scene/sdChannelMemory/iplSDMemory.cpp: per-function optimization pragma (levers 26: orchestrator checks the per-use address recompute evidence) (+1 net), e.g. #pragma ppc_iro_level 1
GATE PASS
```

Final direct instruction comparison against the saved initial object changes only create: 175 -> 0 differing, 1064/1064 instructions. Gate instruction-exact count is 65/66. create exact-name objdiff is 100.0%; draw is restored to baseline 93.456764%. Scope review: source commit fb00e5ea contains only the real countCachedTitles helper, the one-function IRO 1 push/pop, and the replacement of the title-cache loop with the helper call. configure.py unchanged. Existing rx61-work and rx69 untracked files untouched. No push, PR, merge, rebase, other-worktree edits, or subagent was used.
