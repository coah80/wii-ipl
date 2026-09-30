# tiCandidateBox continuation

Baseline: 104/112 objdiff, 102/112 instruction exact; code 17112/24000, data 1132/4652.

Closest functions first: CalcPaneLocate_, StartScrollToIdx, StartScroll, GetPrevPageIdx_. Attempts 1 reorder margin/scale evaluation, 2 reverse multiplication and use an unsigned fixed pane-loop index, 3 reorder evaluation and addition. None improved the baseline.

Draw: attempt 1 sequential vector initialization, 2 full scissor rectangle (12 differences), 3 direct corner initialization. Discarded attempt 2 because two unused fields add no readability; original retained.

createAnmPane_: attempt 1 widened counters, 2 animation reference, 3 direct ID retrieval. All discarded.

create: attempt 1 combined string allocation/construction, 2 combined candidate allocation/construction, 3 passed the saved allocator. All discarded.

Static initializer: attempt 1 inline name access by value (exact), 2 const record member (22 differences), 3 inline name access by reference (exact). Retained meaningful shared-name accessors; 25/25 instructions, zero differences.

Data: pool identical; .rodata and .sdata2 100%. Changing the existing empty-text array's final 1 to the target zero moved its storage and reduced .sdata to 75%; reverted. Existing pinned data and assembly not expanded. No shared-header changes.

Measured trials:
- CalcPaneLocate_ attempt 1: src 0x6d0 base 0x6cc insns 436/435; --- insert mine 29:29 base 29:31
- StartScrollToIdx attempt 1: src 0x2e4 base 0x2e0 insns 185/184; --- insert mine 21:21 base 21:23
- StartScroll attempt 1: src 0x2e8 base 0x2e4 insns 186/185; --- insert mine 21:21 base 21:23
- GetPrevPageIdx_ attempt 1: src 0x208 base 0x204 insns 130/129; --- replace mine 23:24 base 23:24
- CalcPaneLocate_ attempt 2: src 0x6cc base 0x6cc insns 435/435; diffs 50: [34, 39, 41, 69, 168, 170, 247, 248, 249, 250, 254, 255, 258, 259, 260, 264, 266, 267, 269, 271]
- StartScrollToIdx attempt 2: src 0x2e0 base 0x2e0 insns 184/184; diffs 21: [27, 33, 35, 47, 54, 58, 60, 65, 70, 73, 74, 85, 88, 97, 102, 103, 121, 126, 141, 142]
- StartScroll attempt 2: src 0x2e4 base 0x2e4 insns 185/185; diffs 27: [27, 33, 35, 41, 50, 54, 56, 57, 58, 61, 63, 68, 73, 76, 77, 88, 90, 98, 106, 110]
- GetPrevPageIdx_ attempt 2: src 0x204 base 0x204 insns 129/129; diffs 23: [28, 36, 38, 39, 42, 51, 52, 58, 59, 61, 63, 64, 65, 71, 75, 76, 79, 80, 89, 90]
- CalcPaneLocate_ attempt 3: src 0x6d0 base 0x6cc insns 436/435; --- insert mine 29:29 base 29:31
- StartScrollToIdx attempt 3: src 0x2e4 base 0x2e0 insns 185/184; --- insert mine 21:21 base 21:23
- StartScroll attempt 3: src 0x2e8 base 0x2e4 insns 186/185; --- insert mine 21:21 base 21:23
- GetPrevPageIdx_ attempt 3: src 0x208 base 0x204 insns 130/129; --- replace mine 23:24 base 23:24
- Draw attempt 1: src 0x310 base 0x310 insns 196/196; diffs 33: [0, 2, 3, 68, 72, 73, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 93]
- createAnmPane_ attempt 1: src 0x36c base 0x360 insns 219/216; --- replace mine 0:1 base 0:1
- create attempt 1: src 0x57c base 0x580 insns 351/352; --- replace mine 5:6 base 5:6
- Draw attempt 2: src 0x310 base 0x310 insns 196/196; diffs 12: [0, 2, 3, 83, 84, 85, 143, 145, 148, 190, 192, 194]
- createAnmPane_ attempt 2: src 0x358 base 0x360 insns 214/216; --- insert mine 5:5 base 5:8
- create attempt 2: src 0x57c base 0x580 insns 351/352; --- replace mine 5:6 base 5:6
- Draw attempt 3: src 0x310 base 0x310 insns 196/196; diffs 33: [0, 2, 3, 68, 72, 73, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 93]
- createAnmPane_ attempt 3: src 0x370 base 0x360 insns 220/216; --- delete mine 5:6 base 5:5
- create attempt 3: src 0x57c base 0x580 insns 351/352; --- replace mine 5:6 base 5:6
- static initializer attempt 1: src 0x64 base 0x64 insns 25/25; diffs 0: []
- static initializer attempt 2: src 0x64 base 0x64 insns 25/25; diffs 22: [1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
- static initializer attempt 3: src 0x64 base 0x64 insns 25/25; diffs 0: []

## LayoutByNW4R::create — session 3

The inlined UITextArea::Init loop: base carries `this+i*4` as an incremented
pointer (mr r26,r31; lwz 0x11c(r26); r26+=4) covering both adjacent arrays via
+0x50; mine recomputes `add r3,r31,r30` per iter. Tried explicit pointer-walk
(`p = mpTextBoxPane; p != end; ++p`, `p[NUM_PANES]` for bounding, two-pointer
p+e) — MWCC materializes both array bases instead; index form is the least
bad. Strength-reduction tie; create stays 351v352.
