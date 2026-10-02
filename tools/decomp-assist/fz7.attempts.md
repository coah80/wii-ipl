# fz7 attempts

Baseline full quick gate passes; all four units have 100% data and identical pools. No data renames or extent changes needed.

## NWC24Mime
POOL IDENTICAL up to 1 (mine=1 base=1)

## NWC24MsgRead
POOL IDENTICAL up to 7 (mine=7 base=7)

## NWC24MsgSubject
POOL IDENTICAL up to 10 (mine=10 base=10)

## NWC24DateParser
POOL IDENTICAL up to 0 (mine=0 base=0)

### NWC24ReadMsgField
Fetched origin; checked current origin source against local source before experiments.
- protected check inline boundary: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored

### NWC24ReadMsgSubjectPublic
Fetched origin; checked current origin source against local source before experiments.
- error result switch with success and overflow cases: ((11, 64), 100, 104) -> ((10, 10), 104, 104); kept

### NWC24ReadMsgTextPublic
Fetched origin; checked current origin source against local source before experiments.
- error result switch with success and overflow cases: ((7, 28), 68, 70) -> ((5, 5), 70, 70); kept

### ConvertDateToDays
Fetched origin; checked current origin source against local source before experiments.
- add day minus one before month offset: ((6, 19), 113, 113) -> ((6, 19), 113, 113); restored
- combine leap totals in returned expression: ((6, 19), 113, 113) -> ((18, 21), 113, 113); restored

### DecodeWord
Fetched origin; checked current origin source against local source before experiments.
- Declaration swap and move search, explicit local block lines 535-539, up to 180 distinct source permutations: ((0, 67), 180, 180) -> ((0, 67), 180, 180)
```
declaration block:
      char* encodedWord;
      u32 consumedSize;
      u32 decodedLength;
      int encodedLength;
      NWC24Err result;
start (0, 67)
best (0, 67) after 23 builds; source restored; best order was:
    char* encodedWord;
    u32 consumedSize;
    u32 decodedLength;
    int encodedLength;
    NWC24Err result;
```

### ExtractCharset
Fetched origin; checked current origin source against local source before experiments.
- Declaration swap and move search, explicit local block lines 674-676, up to 180 distinct source permutations: ((0, 35), 84, 84) -> ((0, 35), 84, 84)
```
declaration block:
      char* start;
      char* end;
      u32 charsetLength;
start (0, 35)
best (0, 35) after 6 builds; source restored; best order was:
    char* start;
    char* end;
    u32 charsetLength;
```

### ExtractEncodedText
Fetched origin; checked current origin source against local source before experiments.
- Declaration swap and move search, explicit local block lines 711-714, up to 180 distinct source permutations: ((0, 44), 135, 135) -> ((0, 44), 135, 135)
```
declaration block:
      char* start;
      char* end;
      int length;
      NWC24Err result;
start (0, 44)
best (0, 44) after 13 builds; source restored; best order was:
    char* start;
    char* end;
    int length;
    NWC24Err result;
```

### NWC24SetMsgSubjectAndTextPublic
Fetched origin; checked current origin source against local source before experiments.
- Declaration swap and move search, explicit local block lines 228-236, up to 180 distinct source permutations: ((0, 65), 190, 190) -> ((0, 65), 190, 190)
```
declaration block:
      NWC24MsgObjPrivate* privateMsg = (NWC24MsgObjPrivate*)msg;
      NWC24Work* nwcWork;
      u32 textSourceSize;
      u32 textWorkSize;
      BOOL is7Bit;
      NWC24Charset charset;
      u32 subjectWorkSize;
      u8* subjectWork;
      NWC24Err result;
start (0, 65)
best (0, 65) after 93 builds; source restored; best order was:
    NWC24MsgObjPrivate* privateMsg = (NWC24MsgObjPrivate*)msg;
    NWC24Work* nwcWork;
    u32 textSourceSize;
    u32 textWorkSize;
    BOOL is7Bit;
    NWC24Charset charset;
    u32 subjectWorkSize;
    u8* subjectWork;
    NWC24Err result;
```

### NWC24iSetMsgSubjectQP
Fetched origin; checked current origin source against local source before experiments.
- protected result helper and success switch boundary: ((3, 84), 101, 102) -> ((9, 88), 104, 102); restored
- SelectMBox caches flags in inline-local variable: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored
- SelectMBox takes message flags by value: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored
- Declaration swap and move search, explicit local block lines 739-750, up to 180 distinct source permutations: ((0, 12), 144, 144) -> ((0, 12), 144, 144)
```
declaration block:
      u32 workHalf;
      u32 sourceOffset;
      u32 secondSize;
      u8* second;
      u32 subjectLength;
      u32 lineLength;
      u32 outputLength;
      u32 total;
      u32 combinedLength;
      u32 i;
      u32 charsetLength;
      NWC24Err result;
start (0, 12)
best (0, 12) after 177 builds; source restored; best order was:
    u32 workHalf;
    u32 sourceOffset;
    u32 secondSize;
    u8* second;
    u32 subjectLength;
    u32 lineLength;
    u32 outputLength;
    u32 total;
    u32 combinedLength;
    u32 i;
    u32 charsetLength;
    NWC24Err result;
```

### NWC24iDateToOSCalendarTime
Fetched origin; checked current origin source against local source before experiments.
- Declaration swap and move search, explicit local block lines 121-122, up to 180 distinct source permutations: ((0, 13), 85, 85) -> ((0, 13), 85, 85)
```
declaration block:
      BOOL isLeapYear;
      s32 days;
start (0, 13)
best (0, 13) after 2 builds; source restored; best order was:
    BOOL isLeapYear;
    s32 days;
```
- default arm handles overflow: ((10, 10), 104, 104) -> ((11, 64), 100, 104); restored
- overflow case first in switch: ((10, 10), 104, 104) -> ((10, 10), 104, 104); restored
- success case branches to common continue: ((10, 10), 104, 104) -> ((10, 10), 104, 104); restored
- default arm handles overflow: ((5, 5), 70, 70) -> ((7, 28), 68, 70); restored
- overflow case first in switch: ((5, 5), 70, 70) -> ((5, 5), 70, 70); restored
- success case branches to common continue: ((5, 5), 70, 70) -> ((5, 5), 70, 70); restored
- unsigned error switch dispatch: ((10, 10), 104, 104) -> ((10, 10), 104, 104); restored
- nested overflow-only switch after success test: ((10, 10), 104, 104) -> ((13, 64), 102, 104); restored
- unsigned error switch dispatch: ((5, 5), 70, 70) -> ((5, 5), 70, 70); restored
- nested overflow-only switch after success test: ((5, 5), 70, 70) -> ((8, 29), 69, 70); restored

### NWC24iSetMsgSubjectQP
Fetched origin; checked current origin source against local source before experiments.
- declare source offset in successful encode block: ((0, 12), 144, 144) -> compile failure; restored
- declare second capacity adjacent to its initialization: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- scope source offset to folding block: ((0, 12), 144, 144) -> ((0, 29), 144, 144); restored
- delay leap flag initialization until month offset stored: ((0, 13), 85, 85) -> ((5, 76), 86, 85); restored
- use IsLeapYear inline helper: ((0, 13), 85, 85) -> ((8, 68), 89, 85); restored
- cache calendar year explicitly: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- initialize half capacity before second buffer: ((0, 12), 144, 144) -> ((2, 14), 144, 144); restored
- initialize second pointer before second capacity: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- use line length directly for initial complete comparison: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- advance total before source offset in folding loop: ((0, 12), 144, 144) -> ((2, 16), 144, 144); restored
- separate day decrement from month accumulation: ((6, 19), 113, 113) -> ((4, 16), 113, 113); kept
- compute century correction after year day accumulation: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- return common leap correction first: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- split leap quotient temporaries: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored

### ConvertDaysToDate
Fetched origin; checked current origin source against local source before experiments.
- combine February leap branch before shared month subtraction: ((18, 86), 106, 103) -> ((13, 83), 102, 103); kept
- year leap calculation via inline helper: ((13, 83), 102, 103) -> ((21, 94), 98, 103); restored
- month loop exits with break and shared day update: ((13, 83), 102, 103) -> ((7, 83), 101, 103); kept

### QDecode
Fetched origin; checked current origin source against local source before experiments.
- mutate input and encoded offset directly during escape decoding: ((16, 59), 146, 146) -> ((15, 62), 146, 146); kept
- unsigned capacity comparison follows consumed output: ((15, 62), 146, 146) -> ((14, 62), 146, 146); kept
- decoded counter increments before copying plain byte: ((14, 62), 146, 146) -> ((14, 62), 146, 146); restored
- initialize returned marker at its declaration: ((0, 67), 180, 180) -> compile failure; restored
- inline marker computes current before loop: ((0, 67), 180, 180) -> ((5, 148), 181, 180); restored
- inline marker length declaration separated from call: ((0, 67), 180, 180) -> compile failure; restored
- initialize returned marker at its declaration: ((0, 35), 84, 84) -> compile failure; restored
- inline marker computes current before loop: ((0, 35), 84, 84) -> ((5, 71), 85, 84); restored
- inline marker length declaration separated from call: ((0, 35), 84, 84) -> compile failure; restored
- initialize returned marker at its declaration: ((0, 44), 135, 135) -> compile failure; restored
- inline marker computes current before loop: ((0, 44), 135, 135) -> ((7, 112), 136, 135); restored
- inline marker length declaration separated from call: ((0, 44), 135, 135) -> compile failure; restored
- marker offset initialized before marker length call: ((0, 67), 180, 180) -> ((2, 66), 180, 180); restored
- declare current marker outside loop without initial value: ((0, 67), 180, 180) -> ((0, 67), 180, 180); restored
- marker length inline-local declarations precede assignments: ((0, 67), 180, 180) -> ((0, 63), 180, 180); kept
- single input cursor throughout escape branch: ((14, 62), 146, 146) -> ((0, 41), 146, 146); kept
- validity initialization after escaped byte consumption: ((0, 41), 146, 146) -> ((0, 41), 146, 146); restored
- increment input before escape counter: ((0, 41), 146, 146) -> ((0, 41), 146, 146); restored
- grouped success and overflow arms with overflow flag test: ((10, 10), 104, 104) -> ((19, 70), 108, 104); restored
- success-only switch with conditional default arm: ((10, 10), 104, 104) -> ((11, 64), 100, 104); restored
- grouped success and overflow arms with overflow flag test: ((5, 5), 70, 70) -> ((11, 32), 72, 70); restored
- success-only switch with conditional default arm: ((5, 5), 70, 70) -> ((7, 28), 68, 70); restored
- inline year length isolates leap arithmetic: ((7, 83), 101, 103) -> ((7, 83), 101, 103); restored
- inline month length isolates February table load: ((7, 83), 101, 103) -> ((16, 83), 100, 103); restored
- month loop keeps previous days for final update: ((7, 83), 101, 103) -> compile failure; restored

- QDecode declaration search after structural fixes: 21 builds, three improving local-order swaps, structural/exact 0/41 -> 0/25 -> 0/11 -> 0/0.
```
declaration block:
      u32 decodedOffset = 0;
      u32 encodedOffset;
      char* input;
      char* output;
      u8 value = 0;
      NWC24Err result = NWC24_OK;
start (0, 41)
improved (0, 25)
improved (0, 11)
improved (0, 0)
best (0, 0) after 21 builds; kept in source:
    u32 encodedOffset;
    u32 decodedOffset = 0;
    u8 value = 0;
    char* input;
    char* output;
    NWC24Err result = NWC24_OK;
```
- Restored public subject error-switch experiments: structural comparison improved but objdiff fuzzy score declined; no exact gains.

### DecodeWord
Fetched origin; checked current origin source against local source before experiments.
- find-marker declares return cursor before offset and length: ((0, 63), 180, 180) -> ((0, 65), 180, 180); restored
- find-marker length initialized in declaration after offset: ((0, 63), 180, 180) -> ((0, 63), 180, 180); restored
- search prefix cursor return uses offset before prefix: ((0, 63), 180, 180) -> ((0, 63), 180, 180); restored

### ExtractCharset
Fetched origin; checked current origin source against local source before experiments.
- find-marker declares return cursor before offset and length: ((0, 30), 84, 84) -> ((0, 35), 84, 84); restored
- find-marker length initialized in declaration after offset: ((0, 30), 84, 84) -> ((0, 30), 84, 84); restored
- search prefix cursor return uses offset before prefix: ((0, 30), 84, 84) -> ((0, 25), 84, 84); kept

### ExtractEncodedText
Fetched origin; checked current origin source against local source before experiments.
- find-marker declares return cursor before offset and length: ((0, 34), 135, 135) -> ((0, 44), 135, 135); restored
- find-marker length initialized in declaration after offset: ((0, 34), 135, 135) -> ((0, 34), 135, 135); restored

### NWC24ReadMsgFromAddr
Fetched origin; checked current origin source against local source before experiments.
- read-permission helper returns status with conditional early return: ((4, 66), 91, 92) -> ((11, 78), 94, 92); restored
- mailbox selection in function scope: ((4, 66), 91, 92) -> ((12, 63), 91, 92); restored
- mailbox helper copies flags into local: ((4, 66), 91, 92) -> ((4, 66), 91, 92); restored

### NWC24ReadMsgSubject
Fetched origin; checked current origin source against local source before experiments.
- read-permission helper returns status with conditional early return: ((3, 65), 81, 82) -> ((9, 69), 84, 82); restored
- mailbox selection in function scope: ((3, 65), 81, 82) -> ((11, 62), 81, 82); restored
- mailbox helper copies flags into local: ((3, 65), 81, 82) -> ((3, 65), 81, 82); restored

### ReadMsgTextInternal
Fetched origin; checked current origin source against local source before experiments.
- read-permission helper returns status with conditional early return: ((16, 160), 176, 178) -> ((18, 164), 180, 178); restored
- mailbox selection in function scope: ((16, 160), 176, 178) -> ((24, 158), 176, 178); restored
- mailbox helper copies flags into local: ((16, 160), 176, 178) -> ((16, 160), 176, 178); restored

### NWC24ReadMsgAttached
Fetched origin; checked current origin source against local source before experiments.
- read-permission helper returns status with conditional early return: ((6, 75), 90, 91) -> ((13, 81), 93, 91); restored
- mailbox selection in function scope: ((6, 75), 90, 91) -> ((14, 72), 90, 91); restored
- mailbox helper copies flags into local: ((6, 75), 90, 91) -> ((6, 75), 90, 91); restored

### NWC24SetMsgSubjectAndTextPublic
Fetched origin; checked current origin source against local source before experiments.
- cache work pointer initialized in its declaration: ((0, 65), 190, 190) -> ((7, 99), 190, 190); restored
- initialize subject remainder pointer before size: ((0, 65), 190, 190) -> ((2, 65), 190, 190); restored
- scope work pointer to conversion phase: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored

### NWC24iSetMsgSubjectBase64
Fetched origin; checked current origin source against local source before experiments.
- conversion accepts success or overflow with ordinary conditions: ((18, 130), 139, 136) -> ((19, 77), 135, 136); restored
- compute second pointer before capacity: ((18, 130), 139, 136) -> ((16, 130), 139, 136); kept
- loop explicitly advances source before combined output length: ((16, 130), 139, 136) -> ((14, 130), 139, 136); kept
- leap flag initialized in local declaration: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- calendar year converted before leap flag is declared: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- century correction directly added without intermediate: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- return quotient correction directly: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- DecodeWord inline helper FindMarker declaration permutation search: ((0, 63), 180, 180) -> ((0, 63), 180, 180)
```
declaration block:
      u32 offset;
      u32 markerLength;
start (0, 63)
best (0, 63) after 2 builds; source restored; best order was:
    u32 offset;
    u32 markerLength;
```
- ExtractCharset inline helper FindMarkerAfterPrefix declaration permutation search: ((0, 25), 84, 84) -> ((0, 23), 84, 84)
```
declaration block:
      u32 markerLength = Mail_strlen(marker);
      char* current = input + prefix;
      u32 offset;
start (0, 25)
improved (0, 23)
best (0, 23) after 6 builds; kept in source:
    u32 markerLength = Mail_strlen(marker);
    u32 offset;
    char* current = input + prefix;
```
- ExtractEncodedText inline helper FindMarkerOffsetPrefix declaration permutation search: ((0, 34), 135, 135) -> ((0, 34), 135, 135)
```
declaration block:
      u32 offset;
      u32 markerLength;
start (0, 34)
best (0, 34) after 2 builds; source restored; best order was:
    u32 offset;
    u32 markerLength;
```

## Coverage audit and final diagnosis

Scores in trials are structural differences ignoring registers, positional instruction differences, mine instruction count, target instruction count. Failed compilations are recorded but do not count toward the three distinct attempts. Declaration searches evaluate swaps and moves and preserve the best order.
- Origin source check libs/RevoEX/src/nwc24/NWC24Mime: identical to starting source; baseline open functions still present.
- Origin source check libs/RevoEX/src/nwc24/NWC24MsgRead: identical to starting source; baseline open functions still present.
- Origin source check libs/RevoEX/src/nwc24/NWC24MsgSubject: identical to starting source; baseline open functions still present.
- Origin source check libs/RevoEX/src/nwc24/NWC24DateParser: identical to starting source; baseline open functions still present.
- Every owned data section was already 100% in baseline and remains 100%. No symbol renames, extent adjustments, header edits, or configure edits.

### Final open DecodeWord
register allocation only after declaration and inline-helper experiments; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x2d0 base 0x2d0 insns 180/180
diffs 63: [8, 9, 10, 12, 13, 35, 36, 41, 42, 43, 50, 52, 53, 57, 58, 64, 65, 66, 68, 69]
```

### Final open ExtractCharset
register allocation only after declaration and inline-helper experiments; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x150 base 0x150 insns 84/84
diffs 23: [10, 17, 18, 20, 22, 23, 28, 29, 31, 32, 36, 37, 39, 40, 41, 43, 45, 46, 47, 51]
```

### Final open ExtractEncodedText
register allocation only after declaration and inline-helper experiments; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x21c base 0x21c insns 135/135
diffs 34: [6, 7, 8, 9, 10, 12, 33, 35, 44, 45, 52, 54, 58, 65, 76, 77, 83, 84, 85, 86]
```

### Final open NWC24ReadMsgField
mailbox selection reuses protected/type check load; target reloads the field; no volatile added; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x194 base 0x198 insns 101/102
--- replace mine 16:19 base 16:19
```

### Final open NWC24ReadMsgFromAddr
mailbox selection reuses protected/type check load; target reloads the field; no volatile added; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x16c base 0x170 insns 91/92
--- replace mine 15:16 base 15:16
```

### Final open NWC24ReadMsgSubject
mailbox selection reuses protected/type check load; target reloads the field; no volatile added; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x144 base 0x148 insns 81/82
--- replace mine 15:18 base 15:18
```

### Final open ReadMsgTextInternal
mailbox type reload, text-length branch, decoding result/close-result merge, and register allocation; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x2c0 base 0x2c8 insns 176/178
--- replace mine 5:7 base 5:7
```

### Final open NWC24ReadMsgAttached
mailbox selection reuses protected/type check load; target reloads the field; no volatile added; attachment index temporaries and switch branch form also differ; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x168 base 0x16c insns 90/91
--- replace mine 5:9 base 5:9
```

### Final open NWC24ReadMsgSubjectPublic
target contains redundant branch pair for accepted overflow result; ordinary conditional and switch forms differ; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x190 base 0x1a0 insns 100/104
--- replace mine 14:15 base 14:15
```

### Final open NWC24ReadMsgTextPublic
target contains redundant branch pair for accepted overflow result; ordinary conditional and switch forms differ; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x110 base 0x118 insns 68/70
--- replace mine 15:16 base 15:16
```

### Final open NWC24SetMsgSubjectAndTextPublic
register allocation only after declaration and inline-helper experiments; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x2f8 base 0x2f8 insns 190/190
diffs 65: [6, 7, 8, 10, 11, 12, 13, 14, 15, 34, 35, 36, 37, 38, 39, 40, 57, 58, 59, 60]
```

### Final open NWC24iSetMsgSubjectQP
register allocation only after declaration and inline-helper experiments; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x240 base 0x240 insns 144/144
diffs 12: [10, 61, 71, 73, 87, 91, 103, 107, 111, 119, 129, 132]
```

### Final open NWC24iSetMsgSubjectBase64
work-half local stored in source prologue only; signed success/overflow switch dispatch and buffer registers differ; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x22c base 0x220 insns 139/136
--- insert mine 5:5 base 5:6
```

### Final open NWC24iDateToOSCalendarTime
register allocation only after declaration and inline-helper experiments; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x154 base 0x154 insns 85/85
diffs 13: [6, 7, 16, 17, 24, 32, 33, 38, 43, 47, 52, 54, 55]
```

### Final open ConvertDateToDays
century/quarter-year expression scheduling and temporary registers; day-minus-one/month ordering fixed; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x1c4 base 0x1c4 insns 113/113
diffs 16: [94, 95, 96, 97, 99, 100, 101, 103, 104, 105, 106, 107, 108, 109, 110, 111]
```

### Final open ConvertDaysToDate
target reloads year/month before increment; source retains earlier loads, plus leap-flag registers; at least three distinct successful source experiments or declaration permutations logged above.
```
src 0x194 base 0x19c insns 101/103
--- replace mine 8:11 base 8:11
```

Final non-quick gate interrupted externally with exit 143 before any output; clean build removed main.dol. Retrying unchanged full gate.

## Final full gate

Unmodified gate, non-quick clean full rebuild over all four owned units.
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Mime] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Mime] objdiff: code 4528/6124 data 88/88 functions 13/16 fuzzy 99.5428 linked code 0
[libs/RevoEX/src/nwc24/NWC24Mime] instruction-exact functions: 13/16
[libs/RevoEX/src/nwc24/NWC24Mime]   section .data size 72 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .text size 6124 match 99.542786
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: DecodeWord 97.888885
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractCharset 98.27381
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: ExtractEncodedText 98.703705
[libs/RevoEX/src/nwc24/NWC24Mime] baseline: code 3944/6124 data 88 functions 12 fuzzy 98.8556
[libs/RevoEX/src/nwc24/NWC24MsgRead] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgRead] objdiff: code 2480/4660 data 128/128 functions 11/16 fuzzy 98.4764 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgRead] instruction-exact functions: 11/16
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .data size 128 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .text size 4660 match 98.476395
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgField 98.92157
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgFromAddr 98.804344
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgSubject 98.65854
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: ReadMsgTextInternal 93.735954
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgAttached 96.37363
[libs/RevoEX/src/nwc24/NWC24MsgRead] baseline: code 2480/4660 data 128 functions 11 fuzzy 98.4764
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 2776/5352 data 232/232 functions 7/12 fuzzy 98.9013 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 7/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 98.901344
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectQP 99.548615
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectBase64 96.54412
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 2776/5352 data 232 functions 7 fuzzy 98.5874
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1168/2372 data 40/40 functions 5/8 fuzzy 98.0236 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 5/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 98.023605
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: NWC24iDateToOSCalendarTime 99.17647
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 92.66991
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 96.5649
regressions vs baseline: 0
global matched_code_percent: 88.70241 -> 88.72191
global fuzzy_match_percent: 99.47499 -> 99.47811
global complete_code_percent: 63.54459 -> 63.54459
global matched_data_percent: 98.77142 -> 98.77142
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Before -> after instruction exact/code/data: Mime 12->13, 3944->4528, 88->88; MsgRead 11->11, 2480->2480, 128->128; MsgSubject 7->7, 2776->2776, 232->232; DateParser 5->5, 1168->1168, 40->40.

All sixteen remaining functions have at least three distinct compiled source variations or tested local-declaration permutations. One new exact function, QDecode, independently ctxdiff 0 with 146/146 instructions. No other exact function gained. Remaining compiler differences are not proven impossible; further effort may find source levers.

# Second round on landed origin/main

Baseline 2230741d: Mime 13/16, MsgRead 11/16, MsgSubject 7/12, DateParser 5/8. All owned data is 100%.
Mime: POOL IDENTICAL up to 1 (mine=1 base=1)
MsgRead: POOL IDENTICAL up to 7 (mine=7 base=7)
MsgSubject: POOL IDENTICAL up to 10 (mine=10 base=10)
DateParser: POOL IDENTICAL up to 0 (mine=0 base=0)

### NWC24iSetMsgSubjectQP
Fetched origin; checked current origin source against local source before experiments.
- signed second-buffer capacity temporary: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- signed source cursor for folding: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- scope source cursor in braced success arm: ((0, 12), 144, 144) -> ((0, 29), 144, 144); restored

### NWC24iDateToOSCalendarTime
Fetched origin; checked current origin source against local source before experiments.
- signed cached year for Gregorian remainder arithmetic: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- unsigned cached year for Gregorian remainder arithmetic: ((0, 13), 85, 85) -> ((40, 81), 77, 85); restored
- scope leap flag to year-day correction: ((0, 13), 85, 85) -> ((5, 76), 86, 85); restored

### NWC24ReadMsgField
Fetched origin; checked current origin source against local source before experiments.
- mailbox helper receives public opaque message object: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored
- mailbox helper reads public message storage type word: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored
- permission switch single protected case: ((3, 84), 101, 102) -> ((4, 6), 102, 102); restored
- mailbox helper computes result before return: ((3, 84), 101, 102) -> ((9, 80), 101, 102); restored
- initialize folding cursor at start and advance past first encoded line: ((0, 12), 144, 144) -> ((0, 19), 144, 144); restored
- initialize second capacity in leading declarations: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- initialize second pointer in leading declarations: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- initialize converted subject length and line length at declaration: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- leap flag represented as u8: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- leap flag represented as u16: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- leap flag represented as u32: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- leap flag represented as s8: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- leap flag assigned by conditional expression: ((0, 13), 85, 85) -> ((30, 87), 92, 85); restored
- leap flag stores arithmetic zero from calendar microseconds: ((0, 13), 85, 85) -> ((5, 76), 86, 85); restored

### ExtractCharset
Fetched origin; checked current origin source against local source before experiments.
- advance charset start past prefix before length calculation: ((0, 23), 84, 84) -> ((0, 23), 84, 84); restored
- separate prefix address for copying and measured span: ((0, 23), 84, 84) -> ((0, 23), 84, 84); restored
- measure charset span by subtracting prefix after pointer difference: ((0, 23), 84, 84) -> ((7, 44), 85, 84); restored

### ExtractEncodedText
Fetched origin; checked current origin source against local source before experiments.
- advance encoded text cursor past delimiter before measuring span: ((0, 34), 135, 135) -> ((0, 34), 135, 135); restored
- separate encoded body pointer local: ((0, 34), 135, 135) -> ((10, 73), 134, 135); restored
- measure encoded span before removing delimiter byte: ((0, 34), 135, 135) -> ((4, 35), 135, 135); restored

### ConvertDateToDays
Fetched origin; checked current origin source against local source before experiments.
- Gregorian day total expression form 1: ((4, 16), 113, 113) -> ((16, 18), 113, 113); restored
- Gregorian day total expression form 2: ((4, 16), 113, 113) -> ((13, 18), 113, 113); restored
- Gregorian day total expression form 3: ((4, 16), 113, 113) -> ((16, 18), 113, 113); restored
- Gregorian day total expression form 4: ((4, 16), 113, 113) -> ((16, 18), 113, 113); restored
- Gregorian day total expression form 5: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- Gregorian day total expression form 6: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- Gregorian day total expression form 7: ((4, 16), 113, 113) -> ((13, 19), 113, 113); restored
- NWC24iSetMsgSubjectQP initialized source cursor plus declaration search: ((0, 12), 144, 144) -> ((0, 19), 144, 144), restored
```
declaration block:
      u32 workHalf;
      u32 sourceOffset = 0;
      u32 secondSize;
      u8* second;
      u32 subjectLength;
      u32 lineLength;
      u32 outputLength;
      u32 total;
      u32 combinedLength;
      u32 i;
      u32 charsetLength;
      NWC24Err result;
start (0, 19)
best (0, 19) after 177 builds; source restored; best order was:
    u32 workHalf;
    u32 sourceOffset = 0;
    u32 secondSize;
    u8* second;
    u32 subjectLength;
    u32 lineLength;
    u32 outputLength;
    u32 total;
    u32 combinedLength;
    u32 i;
    u32 charsetLength;
    NWC24Err result;
```
- NWC24iSetMsgSubjectQP initialized second capacity plus declaration search: ((0, 12), 144, 144) -> ((0, 12), 144, 144), restored
```
declaration block:
      u32 workHalf;
      u32 sourceOffset;
      u32 secondSize = workSize - (workSize >> 1);
      u8* second;
      u32 subjectLength;
      u32 lineLength;
      u32 outputLength;
      u32 total;
      u32 combinedLength;
      u32 i;
      u32 charsetLength;
      NWC24Err result;
start (0, 12)
best (0, 12) after 177 builds; source restored; best order was:
    u32 workHalf;
    u32 sourceOffset;
    u32 secondSize = workSize - (workSize >> 1);
    u8* second;
    u32 subjectLength;
    u32 lineLength;
    u32 outputLength;
    u32 total;
    u32 combinedLength;
    u32 i;
    u32 charsetLength;
    NWC24Err result;
```

### ConvertDaysToDate
Fetched origin; checked current origin source against local source before experiments.
- shared common-month label for ordinary February: ((7, 83), 101, 103) -> ((7, 83), 101, 103); restored
- year loop explicit positive remainder arm: ((7, 83), 101, 103) -> ((10, 73), 101, 103); restored
- month loop explicit positive remainder arm: ((7, 83), 101, 103) -> ((4, 83), 102, 103); kept
- NWC24iSetMsgSubjectQP initialized body pointer plus declaration search: ((0, 12), 144, 144) -> ((0, 12), 144, 144), restored
```
declaration block:
      u32 workHalf;
      u32 sourceOffset;
      u32 secondSize;
      u8* second = work + (workSize >> 1);
      u32 subjectLength;
      u32 lineLength;
      u32 outputLength;
      u32 total;
      u32 combinedLength;
      u32 i;
      u32 charsetLength;
      NWC24Err result;
start (0, 12)
best (0, 12) after 177 builds; source restored; best order was:
    u32 workHalf;
    u32 sourceOffset;
    u32 secondSize;
    u8* second = work + (workSize >> 1);
    u32 subjectLength;
    u32 lineLength;
    u32 outputLength;
    u32 total;
    u32 combinedLength;
    u32 i;
    u32 charsetLength;
    NWC24Err result;
```

### NWC24ReadMsgField
Fetched origin; checked current origin source against local source before experiments.
- permission failure shares function result return label: ((4, 6), 102, 102) -> compile failure; restored
- protected flag explicitly converted to boolean local: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored
- permission error return through ternary error variable: ((3, 84), 101, 102) -> ((9, 88), 104, 102); restored

### NWC24ReadMsgFromAddr
Fetched origin; checked current origin source against local source before experiments.
- permission failure shares function result return label: ((4, 66), 91, 92) -> compile failure; restored
- protected flag explicitly converted to boolean local: ((4, 66), 91, 92) -> ((4, 66), 91, 92); restored
- permission error return through ternary error variable: ((4, 66), 91, 92) -> ((11, 78), 94, 92); restored

### NWC24ReadMsgSubject
Fetched origin; checked current origin source against local source before experiments.
- permission failure shares function result return label: ((3, 65), 81, 82) -> compile failure; restored
- protected flag explicitly converted to boolean local: ((3, 65), 81, 82) -> ((3, 65), 81, 82); restored
- permission error return through ternary error variable: ((3, 65), 81, 82) -> ((9, 69), 84, 82); restored
- NWC24iSetMsgSubjectQP initialized subject length plus declaration search: ((0, 12), 144, 144) -> ((0, 12), 144, 144), restored
```
declaration block:
      u32 workHalf;
      u32 sourceOffset;
      u32 secondSize;
      u8* second;
      u32 subjectLength = subjectSize;
      u32 lineLength = 0;
      u32 outputLength;
      u32 total;
      u32 combinedLength;
      u32 i;
      u32 charsetLength;
      NWC24Err result;
start (0, 12)
best (0, 12) after 177 builds; source restored; best order was:
    u32 workHalf;
    u32 sourceOffset;
    u32 secondSize;
    u8* second;
    u32 subjectLength = subjectSize;
    u32 lineLength = 0;
    u32 outputLength;
    u32 total;
    u32 combinedLength;
    u32 i;
    u32 charsetLength;
    NWC24Err result;
```

Origin fetch stalled for three minutes while holding shared lock; terminated only this run own fetch and resumed with Git HTTP low-speed timeout. No other worker processes touched.

### NWC24ReadMsgField
Fetched origin; checked current origin source against local source before experiments.
- permission failure goes to single final return label: ((3, 84), 101, 102) -> ((3, 85), 101, 102); restored

### NWC24ReadMsgFromAddr
Fetched origin; checked current origin source against local source before experiments.
- permission failure goes to single final return label: ((4, 66), 91, 92) -> ((12, 74), 91, 92); restored

### NWC24ReadMsgSubject
Fetched origin; checked current origin source against local source before experiments.
- permission failure goes to single final return label: ((3, 65), 81, 82) -> ((3, 66), 81, 82); restored

### ReadMsgTextInternal
Fetched origin; checked current origin source against local source before experiments.
- permission failure goes to single final return label: ((16, 160), 176, 178) -> ((16, 161), 176, 178); restored
- protected flag explicitly converted to boolean local: ((16, 160), 176, 178) -> ((16, 160), 176, 178); restored
- permission failure via error-result variable: ((16, 160), 176, 178) -> ((18, 164), 180, 178); restored

### NWC24ReadMsgAttached
Fetched origin; checked current origin source against local source before experiments.
- permission failure goes to single final return label: ((6, 75), 90, 91) -> ((6, 76), 90, 91); restored

### NWC24ReadMsgSubjectPublic
Fetched origin; checked current origin source against local source before experiments.
- protected flag explicitly converted to boolean local: ((6, 75), 90, 91) -> ((6, 75), 90, 91); restored
- nested single-case success and overflow switches: ((11, 64), 100, 104) -> ((13, 64), 102, 104); restored
- permission failure via error-result variable: ((6, 75), 90, 91) -> ((13, 81), 93, 91); restored
- close result preserves read error then overflow accumulator: ((16, 160), 176, 178) -> ((14, 160), 176, 178); kept
- default case before success in nested switches: ((11, 64), 100, 104) -> ((13, 64), 102, 104); restored
- missing decoded length uses single-case size switch: ((14, 160), 176, 178) -> ((11, 156), 177, 178); kept
- switch boolean success followed by overflow condition: ((11, 64), 100, 104) -> ((14, 46), 104, 104); restored
- decode result checked with conditional before attachment-size comparison: ((6, 75), 90, 91) -> ((9, 75), 89, 91); restored

### NWC24ReadMsgTextPublic
Fetched origin; checked current origin source against local source before experiments.
- nested single-case success and overflow switches: ((7, 28), 68, 70) -> ((8, 29), 69, 70); restored
- default case before success in nested switches: ((7, 28), 68, 70) -> ((8, 29), 69, 70); restored
- switch boolean success followed by overflow condition: ((7, 28), 68, 70) -> ((7, 7), 70, 70); kept

### DecodeWord
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
- marker helper places pattern before input in formal argument list: ((0, 63), 180, 180) -> ((0, 63), 180, 180); restored
- marker helper returns input plus matched offset directly: ((0, 63), 180, 180) -> ((0, 40), 180, 180); kept
- whitespace loop initializes offset before whitespace flag: ((0, 40), 180, 180) -> ((2, 40), 180, 180); restored
- plain-text capacity initialized where declared: ((0, 40), 180, 180) -> ((2, 46), 180, 180); restored

### NWC24SetMsgSubjectAndTextPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
- public parameter cast scoped to protection and empty-text handling: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored
- encoding work area cached separately from context pointer: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored
- subject buffer locals scoped after text conversion sizing: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored

### NWC24iSetMsgSubjectBase64
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
- success-only conversion switch with overflow conditional in default arm: ((14, 130), 139, 136) -> ((15, 77), 135, 136); restored
- converted half capacity set only after buffer length validation: ((14, 130), 139, 136) -> ((11, 107), 138, 136); kept
- initialize work pointer and second capacity at declaration: ((11, 107), 138, 136) -> ((11, 107), 138, 136); restored
- ExtractCharset helper declaration search after returning input+offset: six permutations, before 0/6.
```
declaration block:
      u32 markerLength = Mail_strlen(marker);
      u32 offset;
      char* current = input + prefix;
start (0, 6)
best (0, 6) after 6 builds; source restored; best order was:
    u32 markerLength = Mail_strlen(marker);
    u32 offset;
    char* current = input + prefix;
```
- marker cursor advancement in for-loop update expression: ((0, 6), 84, 84) -> ((0, 6), 84, 84); restored
- counter advancement precedes cursor advancement in update expression: ((0, 6), 84, 84) -> ((0, 7), 84, 84); restored
- marker size calculated after initial cursor assignment: ((0, 6), 84, 84) -> ((4, 50), 85, 84); restored
- marker helper passes remaining length before input formal parameter: ((0, 6), 84, 84) -> ((0, 6), 84, 84); restored
- Restored NWC24ReadMsgTextPublic boolean-switch variant: raw structural comparator improved but authoritative objdiff worsened from 97.14286 to 94.2.
- ExtractEncodedText now 100.0 and ctxdiff 0, 135/135; FindMarker return input+offset caused this exact gain while preserving pools and every previously exact function.

### ExtractCharset
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
- prefix helper plain-declaration order markerLength;,offset;,current;: ((0, 6), 84, 84) -> ((0, 6), 84, 84); restored
- prefix helper plain-declaration order markerLength;,current;,offset;: ((0, 6), 84, 84) -> ((0, 10), 84, 84); restored
- prefix helper plain-declaration order offset;,markerLength;,current;: ((0, 6), 84, 84) -> ((0, 12), 84, 84); restored
- prefix helper plain-declaration order offset;,current;,markerLength;: ((0, 6), 84, 84) -> ((0, 10), 84, 84); restored
- prefix helper plain-declaration order current;,markerLength;,offset;: ((0, 6), 84, 84) -> ((0, 6), 84, 84); restored
- prefix helper plain-declaration order current;,offset;,markerLength;: ((0, 6), 84, 84) -> ((0, 0), 84, 84); kept
- prefix helper search offset is s32: ((0, 0), 84, 84) -> ((0, 0), 84, 84); restored
- prefix helper search offset is u16: ((0, 0), 84, 84) -> ((8, 39), 86, 84); restored
- ExtractCharset exact gained by declaring prefix helper current, offset, markerLength before assignments. 84/84 ctxdiff 0, objdiff 100.0; same helper keeps ExtractEncodedText at 100.0. Quick full unit gate passes, pools identical, data 88/88, regressions zero.

### DecodeWord
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
- encoded-word discriminator declared before char* encodedWord;: ((0, 40), 180, 180) -> ((0, 23), 180, 180); kept
- encoded-word discriminator declared before u32 consumedSize;: ((0, 23), 180, 180) -> compile failure; restored
- encoded-word discriminator declared before u32 decodedLength;: ((0, 23), 180, 180) -> compile failure; restored
- encoded-word discriminator declared before int encodedLength;: ((0, 23), 180, 180) -> compile failure; restored
- encoded-word discriminator declared before NWC24Err result;: ((0, 23), 180, 180) -> compile failure; restored
- inline whitespace predicate isolates size and flag locals: ((0, 23), 180, 180) -> ((0, 18), 180, 180); kept
- encoding extractor delimiter declaration precedes its assignment: ((0, 18), 180, 180) -> ((0, 18), 180, 180); restored
- encoding extractor binds scan pointer and size locals: ((0, 18), 180, 180) -> ((6, 22), 180, 180); restored
- encoding extractor size result precedes byte-output formal parameter: ((0, 18), 180, 180) -> ((0, 18), 180, 180); restored
- whitespace helper declares counter before flag assignment: ((0, 18), 180, 180) -> ((0, 12), 180, 180); kept
- encoding delimiter pattern bound before search result: ((0, 12), 180, 180) -> ((0, 12), 180, 180); restored
- encoding delimiter pattern and result plain declarations before search: ((0, 12), 180, 180) -> ((0, 12), 180, 180); restored
- encoding delimiter pattern initialized after result declaration: ((0, 12), 180, 180) -> ((0, 12), 180, 180); restored
- encoding delimiter search embedded with local order current,offset,length,delimiter: ((0, 12), 180, 180) -> ((9, 107), 179, 180); restored
- encoding delimiter search embedded with local order delimiter,current,offset,length: ((0, 12), 180, 180) -> ((9, 111), 179, 180); restored
- encoding delimiter search embedded with local order offset,current,length,delimiter: ((0, 12), 180, 180) -> ((9, 110), 179, 180); restored
- encoding delimiter search embedded with local order current,length,offset,delimiter: ((0, 12), 180, 180) -> ((9, 108), 179, 180); restored
- encoding delimiter search embedded with local order length,offset,current,delimiter: ((0, 12), 180, 180) -> ((9, 111), 179, 180); restored
- encoding marker search specialization isolates zero prefix: ((0, 12), 180, 180) -> ((0, 7), 180, 180); kept
- encoding marker search specialization takes remaining size first: ((0, 7), 180, 180) -> compile failure; restored
- encoding marker specialization receives pattern separately: ((0, 7), 180, 180) -> compile failure; restored
- encoding wrapper takes remaining size first: ((0, 7), 180, 180) -> ((0, 7), 180, 180); restored
- encoding wrapper receives marker as first formal parameter: ((0, 7), 180, 180) -> ((0, 12), 180, 180); restored
- encoding wrapper binds named delimiter marker before search: ((0, 7), 180, 180) -> ((0, 7), 180, 180); restored
- encoding wrapper returns named delimiter local: ((0, 7), 180, 180) -> ((0, 7), 180, 180); restored

## Second-round coverage audit

All sixteen functions open at baseline received at least three distinct compiled source attempts this round. The QP searches additionally compiled four initialized-local variants across 177 declaration permutations each. Failed compilations are excluded from coverage.
- DecodeWord 99.611115%: register allocation after matching instruction count and branch structure; src 0x2d0 base 0x2d0 insns 180/180; >=3 successful source attempts logged.
- NWC24ReadMsgField 98.92157%: protected type word is commoned in source but reloaded in target; no volatile workaround used; src 0x194 base 0x198 insns 101/102; >=3 successful source attempts logged.
- NWC24ReadMsgFromAddr 98.804344%: protected type word is commoned in source but reloaded in target; no volatile workaround used; src 0x16c base 0x170 insns 91/92; >=3 successful source attempts logged.
- NWC24ReadMsgSubject 98.65854%: protected type word is commoned in source but reloaded in target; no volatile workaround used; src 0x144 base 0x148 insns 81/82; >=3 successful source attempts logged.
- ReadMsgTextInternal 94.55056%: one missing protected-type reload, register allocation and early clamp scheduling; size switch and error accumulator improved; src 0x2c4 base 0x2c8 insns 177/178; >=3 successful source attempts logged.
- NWC24ReadMsgAttached 96.37363%: protected type word is commoned in source but reloaded in target; no volatile workaround used; src 0x168 base 0x16c insns 90/91; >=3 successful source attempts logged.
- NWC24ReadMsgSubjectPublic 96.15385%: accepted-overflow paths contain an extra target branch pair that conditional and nested switch variants do not reproduce; src 0x190 base 0x1a0 insns 100/104; >=3 successful source attempts logged.
- NWC24ReadMsgTextPublic 97.14286%: accepted-overflow paths contain an extra target branch pair that conditional and nested switch variants do not reproduce; src 0x110 base 0x118 insns 68/70; >=3 successful source attempts logged.
- NWC24SetMsgSubjectAndTextPublic 98.23684%: register allocation after matching instruction count and branch structure; src 0x2f8 base 0x2f8 insns 190/190; >=3 successful source attempts logged.
- NWC24iSetMsgSubjectQP 99.548615%: register allocation after matching instruction count and branch structure; src 0x240 base 0x240 insns 144/144; >=3 successful source attempts logged.
- NWC24iSetMsgSubjectBase64 97.72059%: remaining success/overflow branch dispatch and buffer register assignment; redundant work-half store removed; src 0x228 base 0x220 insns 138/136; >=3 successful source attempts logged.
- NWC24iDateToOSCalendarTime 99.17647%: register allocation after matching instruction count and branch structure; src 0x154 base 0x154 insns 85/85; >=3 successful source attempts logged.
- ConvertDateToDays 96.92921%: Gregorian quotient scheduling and temporary registers; src 0x1c4 base 0x1c4 insns 113/113; >=3 successful source attempts logged.
- ConvertDaysToDate 93.83495%: target reloads year and month before increment; source retains earlier loads; leap-register allocation; src 0x198 base 0x19c insns 102/103; >=3 successful source attempts logged.

ExtractCharset 84/84 and ExtractEncodedText 135/135 are now instruction exact and objdiff 100.0. All unit data sections remain 100%; no symbol/extent changes needed. Final percentages below will come from the non-quick gate.

## Second-round final full gate

Unmodified non-quick gate over all four owned units, clean full 43U build.
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24Mime] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24Mime] objdiff: code 5404/6124 data 88/88 functions 15/16 fuzzy 99.9739 linked code 0
[libs/RevoEX/src/nwc24/NWC24Mime] instruction-exact functions: 15/16
[libs/RevoEX/src/nwc24/NWC24Mime]   section .data size 72 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .sdata size 16 match 100.0
[libs/RevoEX/src/nwc24/NWC24Mime]   section .text size 6124 match 99.97388
[libs/RevoEX/src/nwc24/NWC24Mime]   below 100: DecodeWord 99.77778
[libs/RevoEX/src/nwc24/NWC24Mime] baseline: code 4528/6124 data 88 functions 13 fuzzy 99.5428
[libs/RevoEX/src/nwc24/NWC24MsgRead] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgRead] objdiff: code 2480/4660 data 128/128 functions 11/16 fuzzy 98.6009 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgRead] instruction-exact functions: 11/16
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .data size 128 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .text size 4660 match 98.60086
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgField 98.92157
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgFromAddr 98.804344
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgSubject 98.65854
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: ReadMsgTextInternal 94.55056
[libs/RevoEX/src/nwc24/NWC24MsgRead]   below 100: NWC24ReadMsgAttached 96.37363
[libs/RevoEX/src/nwc24/NWC24MsgRead] baseline: code 2480/4660 data 128 functions 11 fuzzy 98.4764
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 2776/5352 data 232/232 functions 7/12 fuzzy 99.0209 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 7/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 99.02093
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectQP 99.548615
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectBase64 97.72059
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 2776/5352 data 232 functions 7 fuzzy 98.9013
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1168/2372 data 40/40 functions 5/8 fuzzy 98.2260 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 5/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 98.22597
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: NWC24iDateToOSCalendarTime 99.17647
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 93.83495
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 98.0236
regressions vs baseline: 0
global matched_code_percent: 88.81829 -> 88.84753
global fuzzy_match_percent: 99.48251 -> 99.48396
global complete_code_percent: 65.19670 -> 65.19670
global matched_data_percent: 98.77142 -> 98.77142
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Before -> after instruction exact/code/data: Mime 13->15, 4528->5404, 88->88; MsgRead 11->11, 2480->2480, 128->128; MsgSubject 7->7, 2776->2776, 232->232; DateParser 5->5, 1168->1168, 40->40.

Final unresolved functions and percentages, superseding earlier snapshots:
- DecodeWord 99.77778%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24ReadMsgField 98.92157%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24ReadMsgFromAddr 98.804344%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24ReadMsgSubject 98.65854%; >=3 distinct successful source attempts logged this round; diagnosis above.
- ReadMsgTextInternal 94.55056%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24ReadMsgAttached 96.37363%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24ReadMsgSubjectPublic 96.15385%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24ReadMsgTextPublic 97.14286%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24SetMsgSubjectAndTextPublic 98.23684%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24iSetMsgSubjectQP 99.548615%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24iSetMsgSubjectBase64 97.72059%; >=3 distinct successful source attempts logged this round; diagnosis above.
- NWC24iDateToOSCalendarTime 99.17647%; >=3 distinct successful source attempts logged this round; diagnosis above.
- ConvertDateToDays 96.92921%; >=3 distinct successful source attempts logged this round; diagnosis above.
- ConvertDaysToDate 93.83495%; >=3 distinct successful source attempts logged this round; diagnosis above.

DecodeWord reduced from 63 to seven register differences, 180/180 instructions, after moving the encoding byte declaration, factoring whitespace scanning, and specializing encoding-marker search. No source-level impossibility claim; higher effort may still resolve these differences. Both newly exact functions remain exact after the full rebuild.

## Round c: fresh origin/main fe6a45c0
Baseline exact Mime15/16, MsgRead11/16, MsgSubject7/12, DateParser5/8. Pools identical in all four units; data88/88,128/128,232/232,40/40. No symbol rename or extent correction is warranted.

### DecodeWord
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: target/ours180 instructions, frame0x50, identical local stack offsets and branches. Only second marker pointer and scan offset exchange r21/r22; inline FindEncodingMarker/FindMarkerAfterPrefix boundary is the candidate lever.
- encoding finder assigns plain delimiter local: ((0, 7), 180, 180) -> ((0, 7), 180, 180); restored
- encoding finder takes marker before input: ((0, 7), 180, 180) -> ((0, 12), 180, 180); restored
- encoding helper owns named prefix length: ((0, 7), 180, 180) -> ((0, 7), 180, 180); restored
- encoding helper uses generic unprefixed finder: ((0, 7), 180, 180) -> ((0, 7), 180, 180); restored
- specialized encoding marker plain declarations current,offset,markerLength,marker: ((0, 7), 180, 180) -> ((0, 12), 180, 180); restored
- specialized encoding marker plain declarations current,offset,marker,markerLength: ((0, 7), 180, 180) -> ((0, 9), 180, 180); restored
- specialized encoding marker plain declarations current,markerLength,offset,marker: ((0, 7), 180, 180) -> ((0, 10), 180, 180); restored
- specialized encoding marker plain declarations current,markerLength,marker,offset: ((0, 7), 180, 180) -> ((0, 7), 180, 180); restored
- specialized encoding marker plain declarations current,marker,offset,markerLength: ((0, 7), 180, 180) -> ((0, 12), 180, 180); restored
- specialized encoding marker plain declarations current,marker,markerLength,offset: ((0, 7), 180, 180) -> ((0, 12), 180, 180); restored
- specialized encoding marker plain declarations offset,current,markerLength,marker: ((0, 7), 180, 180) -> ((0, 8), 180, 180); restored
- specialized encoding marker plain declarations offset,current,marker,markerLength: ((0, 7), 180, 180) -> ((0, 5), 180, 180); kept
- specialized encoding marker plain declarations offset,markerLength,current,marker: ((0, 5), 180, 180) -> ((0, 6), 180, 180); restored
- specialized encoding marker plain declarations offset,markerLength,marker,current: ((0, 5), 180, 180) -> ((0, 0), 180, 180); kept

### NWC24ReadMsgField
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: src 0x194 base 0x198 insns 101/102. Target re-loads message type after protection/type validation; ours retains the earlier value across inlined SelectMBox. Frames and file/stream local offsets agree; additional text/attachment differences are result flow and saved-register scheduling.
- mailbox selection expanded at call boundary: ((3, 84), 101, 102) -> ((11, 81), 101, 102); restored
- protection result named before early return: ((3, 84), 101, 102) -> ((9, 88), 104, 102); restored
- mailbox result switch replaced with early conditional: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored

### NWC24ReadMsgFromAddr
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: src 0x16c base 0x170 insns 91/92. Target re-loads message type after protection/type validation; ours retains the earlier value across inlined SelectMBox. Frames and file/stream local offsets agree; additional text/attachment differences are result flow and saved-register scheduling.
- mailbox selection expanded at call boundary: ((4, 66), 91, 92) -> ((12, 63), 91, 92); restored
- protection result named before early return: ((4, 66), 91, 92) -> ((11, 78), 94, 92); restored
- mailbox result switch replaced with early conditional: ((4, 66), 91, 92) -> ((4, 66), 91, 92); restored

### NWC24ReadMsgSubject
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: src 0x144 base 0x148 insns 81/82. Target re-loads message type after protection/type validation; ours retains the earlier value across inlined SelectMBox. Frames and file/stream local offsets agree; additional text/attachment differences are result flow and saved-register scheduling.
- mailbox selection expanded at call boundary: ((3, 65), 81, 82) -> ((11, 62), 81, 82); restored
- protection result named before early return: ((3, 65), 81, 82) -> ((9, 69), 84, 82); restored
- mailbox result switch replaced with early conditional: ((3, 65), 81, 82) -> ((3, 65), 81, 82); restored

### ReadMsgTextInternal
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: src 0x2c4 base 0x2c8 insns 177/178. Target re-loads message type after protection/type validation; ours retains the earlier value across inlined SelectMBox. Frames and file/stream local offsets agree; additional text/attachment differences are result flow and saved-register scheduling.
- mailbox selection expanded at call boundary: ((11, 156), 177, 178) -> ((19, 154), 177, 178); restored
- protection result named before early return: ((11, 156), 177, 178) -> ((12, 164), 181, 178); restored
- mailbox result switch replaced with early conditional: ((11, 156), 177, 178) -> ((11, 156), 177, 178); restored

### NWC24ReadMsgAttached
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: src 0x168 base 0x16c insns 90/91. Target re-loads message type after protection/type validation; ours retains the earlier value across inlined SelectMBox. Frames and file/stream local offsets agree; additional text/attachment differences are result flow and saved-register scheduling.
- mailbox selection expanded at call boundary: ((6, 75), 90, 91) -> ((14, 72), 90, 91); restored
- protection result named before early return: ((6, 75), 90, 91) -> ((13, 81), 93, 91); restored
- mailbox result switch replaced with early conditional: ((6, 75), 90, 91) -> ((6, 75), 90, 91); restored

### NWC24ReadMsgSubjectPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: src 0x190 base 0x1a0 insns 100/104. Target has a success branch and an unreachable unconditional exit after overflow handling, consistent with single-case switch enclosing an overflow conditional. Local/frame offsets agree.
- overflow conditional inside single-case switch variant 1: ((11, 64), 100, 104) -> ((11, 64), 100, 104); restored
- overflow conditional inside single-case switch variant 2: ((11, 64), 100, 104) -> ((11, 64), 100, 104); restored
- overflow conditional inside single-case switch variant 3: ((11, 64), 100, 104) -> ((11, 64), 100, 104); restored

### NWC24ReadMsgTextPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: src 0x110 base 0x118 insns 68/70. Target has a success branch and an unreachable unconditional exit after overflow handling, consistent with single-case switch enclosing an overflow conditional. Local/frame offsets agree.
- overflow conditional inside single-case switch variant 1: ((7, 28), 68, 70) -> ((7, 28), 68, 70); restored
- overflow conditional inside single-case switch variant 2: ((7, 28), 68, 70) -> ((7, 28), 68, 70); restored
- overflow conditional inside single-case switch variant 3: ((7, 28), 68, 70) -> ((7, 28), 68, 70); restored

### NWC24iDateToOSCalendarTime
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: frame0x10,85/85 instructions; fields/stores/branches identical. First loaded year and shared zero/leap temporary exchange r0/r5,13 register differences. Test live-range/field expression changes before declaration search.
- initialize leap flag after assigning year field: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- initialize calendar fractions as chained assignment: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- leap arithmetic reads populated calendar year: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- year typed temporary used across field stores and leap tests: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored

### ConvertDateToDays
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis:113/113, leaf frame absent. Date validation is identical;16 differences in final signed century/quarter division scheduling and add operands. Split independent arithmetic temporaries and adjust grouping before registers.
- explicit quarter and century correction temporaries: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- common leap correction calculated before day accumulation: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- return common correction plus complete day count: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored

### ConvertDaysToDate
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis:102/103 instructions; target reloads current year before increment, while C compiler reuses loop year. Leap decision condition branches and month continuation have remaining allocation differences. No volatile or hidden reload mechanism is justified.
- year subtraction uses explicit integer year length: ((4, 83), 102, 103) -> ((4, 83), 102, 103); restored
- year increment expressed before next iteration continue: ((4, 83), 102, 103) -> ((0, 43), 103, 103); kept
- year leap computation uses existing inline helper: ((0, 43), 103, 103) -> ((10, 93), 99, 103); restored

DecodeWord exact: specialized encoding marker scan uses ordinary literal, meaningful pointer/length/cursor locals; offset,markerLength,marker,current declaration order resolves remaining allocation. ctxdiff180/180,diffs0. Mime quick gatePASS,16/16,code6124/6124,data88/88,poolidentical,globalregressions0,forbidden0,readability0,DOLverified.

### NWC24SetMsgSubjectAndTextPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis:190/190,frame0x60,same branches and temporaries. Work context occupies r31 instead of targetr22, shifting saved input arguments. Examine initialization and arithmetic operand order, then declarations.
- work context initialized in leading declaration: ((0, 65), 190, 190) -> ((7, 99), 190, 190); restored
- private message cast scoped to message initialization: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored
- subject work pointer adds offset before input pointer: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored

### NWC24iSetMsgSubjectQP
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis:144/144,frame0x70,stack fields and branches identical. Capacity and source offset/charset length saved registers exchange r30/r31. Test initial capacity and pointer ordering and source-loop update boundary.
- initialize second pointer before second capacity: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- leading capacity initializer instead of assignment: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- source offset advanced by for increment expression: ((0, 12), 144, 144) -> ((2, 16), 144, 144); restored

### NWC24iSetMsgSubjectBase64
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis:138/136,frame0x70; switch success/overflow handling contributes two bge instructions absent in target. Second buffer pointer/capacity exchange r26/r27. Replace switch numeric dispatch with single success switch and default condition, then declarations.
- single-case conversion switch with default overflow conditional: ((11, 107), 138, 136) -> ((12, 104), 134, 136); restored
- conversion failure condition enclosing single success switch: ((11, 107), 138, 136) -> ((8, 21), 136, 136); kept
- success condition encloses overflow single-case switch: ((8, 21), 136, 136) -> ((0, 17), 136, 136); kept
- second capacity assigned before second pointer: ((0, 17), 136, 136) -> ((2, 17), 136, 136); restored
- work input named leading pointer temporary: ((0, 17), 136, 136) -> ((0, 17), 136, 136); restored
- year loop plain locals currentYear,previousDays,leapYear: ((0, 43), 103, 103) -> ((0, 43), 103, 103); restored
- year loop plain locals currentYear,leapYear,previousDays: ((0, 43), 103, 103) -> ((0, 43), 103, 103); restored
- year loop plain locals previousDays,currentYear,leapYear: ((0, 43), 103, 103) -> ((0, 43), 103, 103); restored
- year loop plain locals previousDays,leapYear,currentYear: ((0, 43), 103, 103) -> ((0, 43), 103, 103); restored
- year loop plain locals leapYear,currentYear,previousDays: ((0, 43), 103, 103) -> ((0, 43), 103, 103); restored
- year loop plain locals leapYear,previousDays,currentYear: ((0, 43), 103, 103) -> ((0, 43), 103, 103); restored
- inline month leap flag has plain declaration: ((0, 43), 103, 103) -> ((0, 43), 103, 103); restored
- permission error helper boundary variant 1: ((3, 84), 101, 102) -> ((9, 88), 104, 102); restored
- permission error helper boundary variant 2: ((3, 84), 101, 102) -> ((6, 88), 104, 102); restored
- permission error helper boundary variant 3: ((3, 84), 101, 102) -> ((8, 89), 106, 102); restored
- permission error helper boundary variant 1: ((4, 66), 91, 92) -> ((11, 78), 94, 92); restored
- permission error helper boundary variant 2: ((4, 66), 91, 92) -> ((8, 78), 94, 92); restored
- permission error helper boundary variant 3: ((4, 66), 91, 92) -> ((10, 77), 96, 92); restored
- permission error helper boundary variant 1: ((3, 65), 81, 82) -> ((9, 69), 84, 82); restored
- permission error helper boundary variant 2: ((3, 65), 81, 82) -> ((6, 69), 84, 82); restored
- permission error helper boundary variant 3: ((3, 65), 81, 82) -> ((8, 69), 86, 82); restored
- permission error helper boundary variant 1: ((11, 156), 177, 178) -> ((12, 164), 181, 178); restored
- permission error helper boundary variant 2: ((11, 156), 177, 178) -> ((9, 164), 181, 178); kept
- permission error helper boundary variant 3: ((9, 164), 181, 178) -> compile failure; restored
- permission error helper boundary variant 1: ((6, 75), 90, 91) -> compile failure; restored
- permission error helper boundary variant 2: ((6, 75), 90, 91) -> compile failure; restored
- permission error helper boundary variant 3: ((6, 75), 90, 91) -> compile failure; restored
- year loop signed promoted year local: ((0, 43), 103, 103) -> ((0, 43), 103, 103); restored
- year leap decision explicitly distinguishes common leap years: ((0, 43), 103, 103) -> ((0, 29), 103, 103); kept
- month cursor plain locals         u8 currentMonth;,        s32 previousDays;: ((0, 29), 103, 103) -> ((0, 29), 103, 103); restored
- month cursor plain locals         s32 previousDays;,        u8 currentMonth;: ((0, 29), 103, 103) -> ((0, 26), 103, 103); kept
- Register-only last: declsearch explicit actual body lines 233-241 max180: ((0, 65), 190, 190) -> ((0, 65), 190, 190); declaration block: /       NWC24MsgObjPrivate* privateMsg = (NWC24MsgObjPrivate*)msg; /       NWC24Work* nwcWork; /       u32 textSourceSize; /       u32 textWorkSize; /       BOOL is7Bit; /       NWC24Charset charset; /       u32 subjectWorkSize; /       u8* subjectWork; /       NWC24Err result; / start (0, 65) / best (0, 65) after 93 builds; source restored; best order was: /     NWC24MsgObjPrivate* privateMsg = (NWC24MsgObjPrivate*)msg; /     NWC24Work* nwcWork; /     u32 textSourceSize; /     u32 textWorkSize; /     BOOL is7Bit; /     NWC24Charset charset; /     u32 subjectWorkSize; /     u8* subjectWork; /     NWC24Err result; /
ReadMsgTextInternal permission helper lowered structural score while adding four instructions and replacing target simple permission check with status materialization; restored entire read unit to baseline before further authoritative validation. Later helper variants collided with kept definition and failed compilation, and are not counted as distinct successful attempts; all five functions already have three earlier compiled attempts.
- month leap reads year through inline pointer helper 1: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- month leap reads year through inline pointer helper 2: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- month leap reads year through inline pointer helper 3: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- month leap reads year through inline pointer helper 4: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- month leap flag uses signed promoted helper parameter: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- month inline leap flag condition sets both branches explicitly: ((0, 26), 103, 103) -> ((13, 102), 100, 103); restored
- month leap helper returns conditional flag expression: ((0, 26), 103, 103) -> ((0, 28), 103, 103); restored
- Register-only last: declsearch explicit actual body lines 744-755 max180: ((0, 12), 144, 144) -> ((0, 12), 144, 144); declaration block: /       u32 workHalf; /       u32 sourceOffset; /       u32 secondSize; /       u8* second; /       u32 subjectLength; /       u32 lineLength; /       u32 outputLength; /       u32 total; /       u32 combinedLength; /       u32 i; /       u32 charsetLength; /       NWC24Err result; / start (0, 12) / best (0, 12) after 177 builds; source restored; best order was: /     u32 workHalf; /     u32 sourceOffset; /     u32 secondSize; /     u8* second; /     u32 subjectLength; /     u32 lineLength; /     u32 outputLength; /     u32 total; /     u32 combinedLength; /     u32 i; /     u32 charsetLength; /     NWC24Err result; /
- Register-only last: declsearch explicit actual body lines 121-122 max180: ((0, 13), 85, 85) -> ((0, 13), 85, 85); declaration block: /       BOOL isLeapYear; /       s32 days; / start (0, 13) / best (0, 13) after 2 builds; source restored; best order was: /     BOOL isLeapYear; /     s32 days; /
- Register-only last: declsearch explicit actual body lines 152-156 max180: ((4, 16), 113, 113) -> ((4, 16), 113, 113); declaration block: /       s32 daysOfYear; /       s32 yearOffset; /       s32 centuryLeapDays; /       s32 commonLeapDays; /       BOOL isLeapYear; / start (4, 16) / best (4, 16) after 23 builds; source restored; best order was: /     s32 daysOfYear; /     s32 yearOffset; /     s32 centuryLeapDays; /     s32 commonLeapDays; /     BOOL isLeapYear; /
- month length inline return boundary 1: ((0, 26), 103, 103) -> ((6, 42), 102, 103); restored
- month length inline return boundary 2: ((0, 26), 103, 103) -> ((6, 42), 102, 103); restored
- month length inline return boundary 3: ((0, 26), 103, 103) -> ((6, 42), 102, 103); restored
- month helper result assigned into explicit flag local 1: ((0, 26), 103, 103) -> ((0, 29), 103, 103); restored
- month helper result assigned into explicit flag local 2: ((0, 26), 103, 103) -> ((0, 29), 103, 103); restored
- month helper result assigned into explicit flag local 3: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- calendar fields copied through inline boundary 1: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- calendar fields copied through inline boundary 2: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- calendar fields copied through inline boundary 3: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- month cursor promoted type u32: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- month cursor promoted type s32: ((0, 26), 103, 103) -> ((1, 26), 103, 103); restored
- month cursor promoted type int: ((0, 26), 103, 103) -> ((1, 26), 103, 103); restored
- month cursor promoted type u16: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- month cursor loaded before saving remainder: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- Register-only last: declsearch explicit actual body lines 819-828 max180: ((0, 17), 136, 136) -> ((0, 5), 136, 136); declaration block: /       u32 workHalf; /       u32 secondSize; /       u8* second; /       u32 subjectLength; /       u32 lineLength; /       u32 sourceOffset; /       u32 outputLength; /       u32 total; /       u32 charsetLength; /       NWC24Err result; / start (0, 17) / improved (0, 5) / best (0, 5) after 118 builds; kept in source: /     u8* second; /     u32 secondSize; /     u32 workHalf; /     u32 subjectLength; /     u32 lineLength; /     u32 sourceOffset; /     u32 outputLength; /     u32 total; /     u32 charsetLength; /     NWC24Err result; /
- second pointer initialized at declaration before input captures: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- source work named initialized leading alias: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- half capacity computed once before second pointer: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- month leap named quarter remainder 1: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- month leap named quarter remainder 2: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- month leap named quarter remainder 3: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- overflow policy inline helper boundary 1: ((11, 64), 100, 104) -> ((21, 93), 116, 104); restored
- overflow policy inline helper boundary 2: ((11, 64), 100, 104) -> ((21, 93), 116, 104); restored
- overflow policy inline helper boundary 3: ((11, 64), 100, 104) -> ((17, 88), 112, 104); restored
- overflow policy inline helper boundary 1: ((7, 28), 68, 70) -> ((12, 36), 76, 70); restored
- overflow policy inline helper boundary 2: ((7, 28), 68, 70) -> ((12, 36), 76, 70); restored
- overflow policy inline helper boundary 3: ((7, 28), 68, 70) -> ((10, 32), 74, 70); restored
- base64 inline codec boundary binds work buffer before subject inputs: ((0, 5), 136, 136) -> ((11, 36), 136, 136); restored
- ConvertDaysToDate register-only last, declsearch loop lines 208-211: declaration block: /           u16 currentYear = *year; /           s32 previousDays = days; /           BOOL leapYear = TRUE; /           BOOL commonLeapYear = FALSE; / start (0, 26) / best (0, 26) after 13 builds; source restored; best order was: /         u16 currentYear = *year; /         s32 previousDays = days; /         BOOL leapYear = TRUE; /         BOOL commonLeapYear = FALSE; /
- ConvertDaysToDate register-only last, declsearch loop lines 228-229: declaration block: /           s32 previousDays; /           u8 currentMonth; / start (0, 26) / best (0, 26) after 2 builds; source restored; best order was: /         s32 previousDays; /         u8 currentMonth; /

### Round c completeness ledger
All14 baseline-open exact-name functions were fetched and checked against unchanged origin/main source before their first attempt. All four pools were checked directly with pool_diff using source/target object paths; all data sections already100%, so no symbol or extent edits.

- DecodeWord: exact180/180,diffs0; plain delimiter assignment7->7; marker-first formal7->12; named prefix7->7; specialized marker scan declaration permutations7->5->0, retained. Mime16/16,all owned code/data100%,quickGATEPASS; committed38bb3851.
- NWC24ReadMsgField: expanded mailbox boundary(3,84)->(11,81); named permission(3,84)->(9,88); early mailbox error conditional(3,84)->(3,84); all restored.
- NWC24ReadMsgFromAddr: expanded mailbox boundary(4,66)->(12,63); named permission(4,66)->(11,78); early mailbox error conditional(4,66)->(4,66); all restored.
- NWC24ReadMsgSubject: expanded mailbox boundary(3,65)->(11,62); named permission(3,65)->(9,69); early mailbox error conditional(3,65)->(3,65); all restored.
- ReadMsgTextInternal: expanded mailbox boundary(11,156)->(19,154); named permission(11,156)->(12,164); early mailbox error conditional(11,156)->(11,156); all restored. Error-helper trial reduced structural score but added four instructions and was restored.
- NWC24ReadMsgAttached: expanded mailbox boundary(6,75)->(14,72); named permission(6,75)->(13,81); early mailbox error conditional(6,75)->(6,75); all restored.
- NWC24ReadMsgSubjectPublic: switch with default conditional/early-break, default-first switch with overflow guard, success-first switch with overflow guard each(11,64)->(11,64),100/104; three inline overflow policy boundaries116/116/112 source instructions all worse and restored.
- NWC24ReadMsgTextPublic: switch with default conditional/early-break, default-first switch with overflow guard, success-first switch with overflow guard each(7,28)->(7,28),68/70; inline overflow policy boundaries76/76/74 source instructions all worse and restored.
- NWC24SetMsgSubjectAndTextPublic: leading work-context initializer(0,65)->(7,99); scoped private cast(0,65)->(0,65); arithmetic operand reversal(0,65)->(0,65); all restored. Actual leading block declsearch93 builds unchanged.
- NWC24iSetMsgSubjectQP: second pointer initialization order(0,12)->(0,12); initialized second capacity declaration(0,12)->(0,12); source advance moved into for increment(0,12)->(2,16); all restored. Actual leading block declsearch177 builds unchanged.
- NWC24iSetMsgSubjectBase64: single-case default-overflow conversion switch138->134 worse/restored; overflow-first condition plus success switch138->136 retained; success-first condition plus overflow switch136/136 removes remaining structural dispatch differences retained. Actual leading block declsearch118 builds(0,17)->(0,5), retained. Pointer declaration initializer, work alias, shared half capacity each(0,5)->(0,5) restored; full inline codec boundary(0,5)->(11,36) restored.
- NWC24iDateToOSCalendarTime: leap initialization after year store, chained fraction-field assignment, populated calendar year in leap arithmetic each(0,13)->(0,13),85/85 restored. Typed year local and three field-copy inline boundaries unchanged/restored. Actual leading block declsearch2 builds unchanged.
- ConvertDateToDays: separate quarter/century arithmetic locals, common correction before accumulation, reversed final sum operands each(4,16)->(4,16),113/113 restored. Actual leading block declsearch23 builds unchanged.
- ConvertDaysToDate: explicit year-length temporary(4,83)->(4,83) restored; year increment/continue(4,83)->(0,43),103/103 retained; existing leap helper at year boundary(0,43)->(10,93) restored. Explicit common-leap-year condition(0,43)->(0,29), month cursor local declaration order(0,29)->(0,26) retained. Further helper boundaries, flags, promoted cursor types, named quarter remainder all failed to improve and were restored.

Score pairs above are structural differences ignoring register names, then positional instruction differences. Only objdiff/instruction-exact/full gate measurements establish matches; no fuzzy score is counted as exact. Each of the13 remaining functions has at least three distinct successfully compiled source-level trials in this round. No untried owned function remains.

### Round c remaining functions, refreshed from objdiff
- NWC24ReadMsgField 98.92157%: 101/102 instructions; target reloads message type after permission check, source CSE retains it. At least three compiled distinct attempts are listed in the completeness ledger.
- NWC24ReadMsgFromAddr 98.804344%: 91/92 instructions; target reloads message type after type capability check, source CSE retains it. At least three compiled distinct attempts are listed in the completeness ledger.
- NWC24ReadMsgSubject 98.65854%: 81/82 instructions; target reloads message type after permission check, source CSE retains it. At least three compiled distinct attempts are listed in the completeness ledger.
- ReadMsgTextInternal 94.55056%: 177/178 instructions; type reload, capacity clamp scheduling and saved-register allocation. At least three compiled distinct attempts are listed in the completeness ledger.
- NWC24ReadMsgAttached 96.37363%: 90/91 instructions; type reload and attachment-index/result temporary allocation. At least three compiled distinct attempts are listed in the completeness ledger.
- NWC24ReadMsgSubjectPublic 96.15385%: 100/104 instructions; two overflow paths each lack target unreachable branch pair. At least three compiled distinct attempts are listed in the completeness ledger.
- NWC24ReadMsgTextPublic 97.14286%: 68/70 instructions; overflow path lacks target unreachable branch pair. At least three compiled distinct attempts are listed in the completeness ledger.
- NWC24SetMsgSubjectAndTextPublic 98.23684%: 190/190 instructions; only saved-register allocation, work context r31 instead of target r22. At least three compiled distinct attempts are listed in the completeness ledger.
- NWC24iSetMsgSubjectQP 99.548615%: 144/144 instructions; only twelve register differences, capacity and offset/charset temporaries swap r30/r31. At least three compiled distinct attempts are listed in the completeness ledger.
- NWC24iSetMsgSubjectBase64 99.632355%: 136/136 instructions; only five register move ordering differences in parameter capture, body is exact. At least three compiled distinct attempts are listed in the completeness ledger.
- NWC24iDateToOSCalendarTime 99.17647%: 85/85 instructions; only thirteen register differences, year/zero-leap flag swap r0/r5. At least three compiled distinct attempts are listed in the completeness ledger.
- ConvertDateToDays 96.92921%: 113/113 instructions; sixteen instruction differences in final division scheduling and operand allocation. At least three compiled distinct attempts are listed in the completeness ledger.
- ConvertDaysToDate 97.718445%: 103/103 instructions; only twenty-six register differences in month loop; year loop is exact. At least three compiled distinct attempts are listed in the completeness ledger.
Remaining count13. Uncertainty: the surviving allocation/scheduling ties have no demonstrated source-level exact solution; no data ownership ambiguity remains.

## Round d: fresh origin/main 00f44a92
Owned MsgRead11/16, MsgSubject7/12, DateParser5/8. Source baseline copied before edits. All pools identical and owned data already100%; no symbol or extent changes are justified.

### NWC24ReadMsgField
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: Field target102/source101,frame0xf0,identical locals/branches except missing message type reload at0x58 after protection check. Test a guarded typed bitfield view of proven mask0x200 at message offset4; union remains one32-bit word and macro is defined only by owned unit. This is a source-type experiment, not volatile or padding data.
- NWC24ReadMsgField: guarded readability bitfield versus raw mailbox flags: ((3, 84), 101, 102) -> ((4, 84), 101, 102); restored
Structural diagnosis NWC24ReadMsgField: src 0x194 base 0x198 insns 101/102. Target distinct type reload versus source common load; file/stream frame locations agree. Test output-helper boundary, branch form, and typed flag temporaries.
- NWC24ReadMsgField: permission guard has explicit output error boundary: ((3, 84), 101, 102) -> ((8, 89), 106, 102); restored
- NWC24ReadMsgField: permission guard expressed as negative goto exit: ((3, 84), 101, 102) -> ((9, 86), 101, 102); restored
- NWC24ReadMsgField: mailbox type computed using signed flags view: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored

### NWC24ReadMsgFromAddr
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis NWC24ReadMsgFromAddr: src 0x16c base 0x170 insns 91/92. Target distinct type reload versus source common load; file/stream frame locations agree. Test output-helper boundary, branch form, and typed flag temporaries.
- NWC24ReadMsgFromAddr: permission guard has explicit output error boundary: ((4, 66), 91, 92) -> ((9, 77), 96, 92); restored
- NWC24ReadMsgFromAddr: permission guard expressed as negative goto exit: ((4, 66), 91, 92) -> ((12, 74), 91, 92); restored
- NWC24ReadMsgFromAddr: mailbox type computed using signed flags view: ((4, 66), 91, 92) -> ((4, 66), 91, 92); restored

### NWC24ReadMsgSubject
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis NWC24ReadMsgSubject: src 0x144 base 0x148 insns 81/82. Target distinct type reload versus source common load; file/stream frame locations agree. Test output-helper boundary, branch form, and typed flag temporaries.
- NWC24ReadMsgSubject: permission guard has explicit output error boundary: ((3, 65), 81, 82) -> ((8, 69), 86, 82); restored
- NWC24ReadMsgSubject: permission guard expressed as negative goto exit: ((3, 65), 81, 82) -> ((10, 67), 81, 82); restored
- NWC24ReadMsgSubject: mailbox type computed using signed flags view: ((3, 65), 81, 82) -> ((3, 65), 81, 82); restored

### ReadMsgTextInternal
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis ReadMsgTextInternal: src 0x2c4 base 0x2c8 insns 177/178. Target distinct type reload versus source common load; file/stream frame locations agree. Test output-helper boundary, branch form, and typed flag temporaries.
- ReadMsgTextInternal: permission guard has explicit output error boundary: ((11, 156), 177, 178) -> ((10, 169), 183, 178); kept
- ReadMsgTextInternal: permission guard expressed as negative goto exit: ((10, 169), 183, 178) -> ((10, 169), 183, 178); restored
- ReadMsgTextInternal: mailbox type computed using signed flags view: ((10, 169), 183, 178) -> ((10, 169), 183, 178); restored

### NWC24ReadMsgAttached
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis NWC24ReadMsgAttached: src 0x168 base 0x16c insns 90/91. Target distinct type reload versus source common load; file/stream frame locations agree. Test output-helper boundary, branch form, and typed flag temporaries.
- NWC24ReadMsgAttached: permission guard has explicit output error boundary: ((6, 75), 90, 91) -> compile failure; restored
- NWC24ReadMsgAttached: permission guard expressed as negative goto exit: ((6, 75), 90, 91) -> ((13, 79), 90, 91); restored
- NWC24ReadMsgAttached: mailbox type computed using signed flags view: ((6, 75), 90, 91) -> ((6, 75), 90, 91); restored

### NWC24ReadMsgSubjectPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis NWC24ReadMsgSubjectPublic: src 0x190 base 0x1a0 insns 100/104. Target error policy has an additional branch over the shared exit after overflow acceptance. Frame and stack declaration layout match. Test labeled continuation, switch inside error arm, and error-loop exit boundaries.
- NWC24ReadMsgSubjectPublic: overflow branch boundary variant 1: ((11, 64), 100, 104) -> ((13, 64), 102, 104); restored
- NWC24ReadMsgSubjectPublic: overflow branch boundary variant 2: ((11, 64), 100, 104) -> ((11, 64), 100, 104); restored
- NWC24ReadMsgSubjectPublic: overflow branch boundary variant 3: ((11, 64), 100, 104) -> ((13, 64), 102, 104); restored

### NWC24ReadMsgTextPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis NWC24ReadMsgTextPublic: src 0x110 base 0x118 insns 68/70. Target error policy has an additional branch over the shared exit after overflow acceptance. Frame and stack declaration layout match. Test labeled continuation, switch inside error arm, and error-loop exit boundaries.
- NWC24ReadMsgTextPublic: overflow branch boundary variant 1: ((7, 28), 68, 70) -> ((8, 29), 69, 70); restored
- NWC24ReadMsgTextPublic: overflow branch boundary variant 2: ((7, 28), 68, 70) -> ((7, 28), 68, 70); restored
- NWC24ReadMsgTextPublic: overflow branch boundary variant 3: ((7, 28), 68, 70) -> ((8, 29), 69, 70); restored

### NWC24SetMsgSubjectAndTextPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis NWC24SetMsgSubjectAndTextPublic: src 0x2f8 base 0x2f8 insns 190/190. Stack frame/local offsets and control flow are identical; saved register coloring or prologue capture order remains. Test initialization lifetimes, helper boundaries and expression operands before declaration search.
- NWC24SetMsgSubjectAndTextPublic: charset work buffer named independently of work context: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored
- NWC24SetMsgSubjectAndTextPublic: text/subject capacity allocation uses named weighted length: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored
- NWC24SetMsgSubjectAndTextPublic: parse charset status named local before fallback: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored

### NWC24iSetMsgSubjectQP
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis NWC24iSetMsgSubjectQP: src 0x240 base 0x240 insns 144/144. Stack frame/local offsets and control flow are identical; saved register coloring or prologue capture order remains. Test initialization lifetimes, helper boundaries and expression operands before declaration search.
- NWC24iSetMsgSubjectQP: separate first-line charset byte count and folding limit: ((0, 12), 144, 144) -> ((0, 15), 144, 144); restored
- NWC24iSetMsgSubjectQP: name charset line prefix before first break calculation: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- NWC24iSetMsgSubjectQP: combine output advancement before source advancement: ((0, 12), 144, 144) -> ((2, 16), 144, 144); restored

### NWC24iSetMsgSubjectBase64
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis NWC24iSetMsgSubjectBase64: src 0x220 base 0x220 insns 136/136. Stack frame/local offsets and control flow are identical; saved register coloring or prologue capture order remains. Test initialization lifetimes, helper boundaries and expression operands before declaration search.
- NWC24iSetMsgSubjectBase64: initial half capacity plain declared local: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- NWC24iSetMsgSubjectBase64: first converter input size initialized leading declaration: ((0, 5), 136, 136) -> ((5, 18), 136, 136); restored
- NWC24iSetMsgSubjectBase64: charset name captured by const string length helper: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
ReadMsgTextInternal output-helper candidate added six instructions despite smaller normalized structural score; restored whole read unit to baseline. Attached output-helper compile failure was caused by collision with that retained helper definition and is not counted; repeat after restoration.
- NWC24ReadMsgAttached: attachment decoder uses named attachment descriptor: ((6, 75), 90, 91) -> ((11, 62), 90, 91); restored

### NWC24iDateToOSCalendarTime
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis DateToOSCalendarTime85/85,frame0x10,same stores/branches. Shared zero-leap flag r5/year r0 versus target r0/r5. Test zero field temporary, conditional leap expression boundaries, and field-copy order.
- NWC24iDateToOSCalendarTime: fraction fields share named zero value: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- NWC24iDateToOSCalendarTime: calendar fractions initialized before year copy: ((0, 13), 85, 85) -> ((6, 18), 85, 85); restored
- NWC24iDateToOSCalendarTime: leap condition divided into common and century decisions: ((0, 13), 85, 85) -> ((4, 53), 87, 85); restored

### ConvertDateToDays
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis ConvertDateToDays113/113 leaf frame, final16 differences include arithmetic scheduling. Target accumulates century quotient in r0 and common quotient in r3; test explicit previous-year temporary and arithmetic helper boundary.
- ConvertDateToDays: name completed-year arithmetic input: ((4, 16), 113, 113) -> ((6, 17), 113, 113); restored
- ConvertDateToDays: common correction difference formed after accumulated day count: ((4, 16), 113, 113) -> ((13, 16), 113, 113); restored
- ConvertDateToDays: century correction is added through explicit yearly subtotal: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored

### ConvertDaysToDate
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis ConvertDaysToDate103/103,year loop exact,month loop26 register differences. Frame0x10 and branches identical. Investigate month inline-helper boundaries/local scope before declaration search.
- ConvertDaysToDate: month leap expression expanded inside existing loop: ((0, 26), 103, 103) -> ((14, 102), 95, 103); restored
- ConvertDaysToDate: month remainder saved with initialized declaration: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: month loop has explicit continuation after month increment: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- NWC24iSetMsgSubjectQP: second output buffer typed descriptor variation 1: ((0, 12), 144, 144) -> ((0, 20), 144, 144); restored
- NWC24iSetMsgSubjectQP: second output buffer typed descriptor variation 2: ((0, 12), 144, 144) -> ((0, 20), 144, 144); restored
- NWC24iSetMsgSubjectQP: second output buffer typed descriptor variation 3: ((0, 12), 144, 144) -> compile failure; restored
- NWC24iSetMsgSubjectBase64: second output buffer typed descriptor variation 1: ((0, 5), 136, 136) -> ((0, 19), 136, 136); restored
- NWC24iSetMsgSubjectBase64: second output buffer typed descriptor variation 2: ((0, 5), 136, 136) -> ((0, 19), 136, 136); restored
- NWC24iSetMsgSubjectBase64: second output buffer typed descriptor variation 3: ((0, 5), 136, 136) -> compile failure; restored
- ConvertDateToDays: century correction references original year directly: ((4, 16), 113, 113) -> ((14, 20), 113, 113); restored
- ConvertDateToDays: common leap correction references original year directly: ((4, 16), 113, 113) -> ((7, 18), 113, 113); restored
- ConvertDateToDays: both leap corrections reference original year directly: ((4, 16), 113, 113) -> ((10, 19), 113, 113); restored
- ConvertDaysToDate: month leap helper uses representable flag type u8: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: month leap helper uses representable flag type u32: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: month leap helper uses representable flag type s8: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: month leap flag default set after common-year decision: ((0, 26), 103, 103) -> ((9, 53), 105, 103); restored
- ConvertDaysToDate: month common path first with explicit positive fallback branch: ((0, 26), 103, 103) -> ((6, 32), 103, 103); restored
- NWC24SetMsgSubjectAndTextPublic: register-only last declsearch explicit actual body lines 233-241 max180: ((0, 65), 190, 190) -> ((0, 65), 190, 190); declaration block: /       NWC24MsgObjPrivate* privateMsg = (NWC24MsgObjPrivate*)msg; /       NWC24Work* nwcWork; /       u32 textSourceSize; /       u32 textWorkSize; /       BOOL is7Bit; /       NWC24Charset charset; /       u32 subjectWorkSize; /       u8* subjectWork; /       NWC24Err result; / start (0, 65) / best (0, 65) after 93 builds; source restored; best order was: /     NWC24MsgObjPrivate* privateMsg = (NWC24MsgObjPrivate*)msg; /     NWC24Work* nwcWork; /     u32 textSourceSize; /     u32 textWorkSize; /     BOOL is7Bit; /     NWC24Charset charset; /     u32 subjectWorkSize; /     u8* subjectWork; /     NWC24Err result; /
- ConvertDateToDays: register-only last after arithmetic structural trials, declsearch actual lines 152-156: declaration block: /       s32 daysOfYear; /       s32 yearOffset; /       s32 centuryLeapDays; /       s32 commonLeapDays; /       BOOL isLeapYear; / start (4, 16) / best (4, 16) after 23 builds; source restored; best order was: /     s32 daysOfYear; /     s32 yearOffset; /     s32 centuryLeapDays; /     s32 commonLeapDays; /     BOOL isLeapYear; /
- NWC24iSetMsgSubjectQP: register-only last declsearch explicit actual body lines 744-755 max180: ((0, 12), 144, 144) -> ((0, 12), 144, 144); declaration block: /       u32 workHalf; /       u32 sourceOffset; /       u32 secondSize; /       u8* second; /       u32 subjectLength; /       u32 lineLength; /       u32 outputLength; /       u32 total; /       u32 combinedLength; /       u32 i; /       u32 charsetLength; /       NWC24Err result; / start (0, 12) / best (0, 12) after 177 builds; source restored; best order was: /     u32 workHalf; /     u32 sourceOffset; /     u32 secondSize; /     u8* second; /     u32 subjectLength; /     u32 lineLength; /     u32 outputLength; /     u32 total; /     u32 combinedLength; /     u32 i; /     u32 charsetLength; /     NWC24Err result; /
- NWC24iSetMsgSubjectBase64: register-only last declsearch explicit actual body lines 819-828 max180: ((0, 5), 136, 136) -> ((0, 5), 136, 136); declaration block: /       u8* second; /       u32 secondSize; /       u32 workHalf; /       u32 subjectLength; /       u32 lineLength; /       u32 sourceOffset; /       u32 outputLength; /       u32 total; /       u32 charsetLength; /       NWC24Err result; / start (0, 5) / best (0, 5) after 118 builds; source restored; best order was: /     u8* second; /     u32 secondSize; /     u32 workHalf; /     u32 subjectLength; /     u32 lineLength; /     u32 sourceOffset; /     u32 outputLength; /     u32 total; /     u32 charsetLength; /     NWC24Err result; /
- NWC24iDateToOSCalendarTime: register-only last declsearch explicit actual body lines 121-122 max180: ((0, 13), 85, 85) -> ((0, 13), 85, 85); declaration block: /       BOOL isLeapYear; /       s32 days; / start (0, 13) / best (0, 13) after 2 builds; source restored; best order was: /     BOOL isLeapYear; /     s32 days; /
- ReadMsgTextInternal: capacity clamp writes length before overflow status: ((11, 156), 177, 178) -> ((9, 157), 177, 178); kept
- ReadMsgTextInternal: base64 decode result remains local until validation finishes: ((9, 157), 177, 178) -> ((7, 160), 177, 178); kept
- ReadMsgTextInternal: mailbox selection occurs before setting returned encoding default: ((7, 160), 177, 178) -> ((8, 160), 177, 178); restored
- NWC24ReadMsgField: mailbox flags passed by named field pointer 1: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored
- NWC24ReadMsgField: mailbox flags passed by named field pointer 2: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored
- NWC24ReadMsgField: mailbox flags passed by named field pointer 3: ((3, 84), 101, 102) -> ((3, 84), 101, 102); restored

Round d first retained improvement: ReadMsgTextInternal clamp assignment order and branch-local decode result remove structural scheduling differences. Objdiff94.55056 ->96.853935,177/178 instructions; missing type reload and saved-register allocation remain. Quick gate over all threePASS,poolsidentical,data100%,globalregressions0,forbidden0,readability0,DOL26116613f624061ba99c8d1a299aaa6efa85670d. No new exact function is claimed.
- NWC24iSetMsgSubjectQP: QP cursor initialization scoped to folding branch 1: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- NWC24iSetMsgSubjectQP: QP cursor initialization scoped to folding branch 2: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- NWC24iSetMsgSubjectQP: QP cursor initialization scoped to folding branch 3: ((0, 12), 144, 144) -> ((0, 12), 144, 144); restored
- ReadMsgTextInternal: register-only last declsearch explicit actual body lines 389-481 max180: ((7, 160), 177, 178) -> ((7, 157), 177, 178); declaration block: /       const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg; /       NWC24MBoxType type; /       NWC24File file; /       NWC24Err result, closeResult; /       NWC24Err overflow = NWC24_OK; /       u32 length; /       u32 decodedSize; /       char* buffer; /       if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) /           return NWC24_ERR_LIB_NOT_OPENED; /       if (!(privateMsg->type & 0x200)) /           return NWC24_ERR_PROTECTED; /       buffer = NWC24WorkP->stringWork; /       *encoding = 0; /       result = SelectMBox(privateMsg, &type); /       switch (result) { /           case NWC24_OK: /               break; /           default: /               return result; /       } /       length = privateMsg->textSize; /       switch (length) { /           case 0: length = privateMsg->text.size; break; /           default: break; /       } /       if (length == 0) /           return NWC24_ERR_NULL; /       if (length > capacity - 1) { /           length = capacity - 1; /           overflow = NWC24_ERR_OVERFLOW; /       } /       result = NWC24iMBoxOpenStoredMsg(type, privateMsg->msgId, &file); /       switch (result) { /           case NWC24_OK: /               break; /           default: /               return result; /       } /       Mail_memset(charset, 0, charsetCapacity); /       if (privateMsg->unk_0x50.size >= charsetCapacity) /           result = NWC24_ERR_FORMAT; /       else { /           if (privateMsg->unk_0x50.size != 0) { /               NWC24FSeek(&file, (u32)privateMsg->unk_0x50.ptr, NWC24_SEEK_BEG); /               result = NWC24FRead(charset, privateMsg->unk_0x50.size, &file); /               if (result != NWC24_OK) /                   goto close; /           } /           if (privateMsg->unk_0x58.size != 0 && privateMsg->unk_0x58.size < 32) { /               Mail_memset(buffer, 0, 32); /               NWC24FSeek(&file, (u32)privateMsg->unk_0x58.ptr, NWC24_SEEK_BEG); /               result = NWC24FRead(buffer, privateMsg->unk_0x58.size, &file); /               if (result != NWC24_OK) /                   goto close; /               result = NWC24ParseEncodingStr(encoding, buffer); /               if (result != NWC24_OK) /                   goto close; /           } /           NWC24FSeek(&file, (u32)privateMsg->text.ptr, NWC24_SEEK_BEG); /           switch (*encoding) { /               case 0: /               case 1: /                   result = NWC24FRead(text, length, &file); /                   text[length] = 0; /                   break; /               case 2: { /                   NWC24Err decodeResult; /                   decodedSize = 0; /                   decodeResult = ReadBase64Data(&file, &privateMsg->text, (u8*)text, length, &decodedSize); /                   if (decodeResult == NWC24_OK && decodedSize != privateMsg->textSize) /                       decodeResult = NWC24_ERR_FORMAT; /                   result = decodeResult; /                   text[length] = 0; /                   break; /               } /               case 3: /                   result = ReadQPText(privateMsg, &file, text, length); /                   break; /               default: /                   result = NWC24_ERR_NOT_SUPPORTED; /                   *text = 0; /                   break; /           } /       } /   close: /       closeResult = NWC24iMBoxCloseMsg(&file); /       if (result != NWC24_OK) /           closeResult = result; /       if (closeResult != NWC24_OK) /           overflow = closeResult; /       return overflow; /   } / start (7, 160) / improved (7, 157) / best (7, 157) after 180 builds; kept in source: /     char* buffer; /     NWC24MBoxType type; /     NWC24File file; /     NWC24Err result, closeResult; /     NWC24Err overflow = NWC24_OK; /     u32 length; /     u32 decodedSize; /     const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg; /     if (!NWC24IsMsgLibOpened() && !NWC24IsMsgLibOpenedByTool()) /         return NWC24_ERR_LIB_NOT_OPENED; /     if (!(privateMsg->type & 0x200)) /         return NWC24_ERR_PROTECTED; /     buffer = NWC24WorkP->stringWork; /     *encoding = 0; /     result = SelectMBox(privateMsg, &type); /     switch (result) { /         case NWC24_OK: /             break; /         default: /             return result; /     } /     length = privateMsg->textSize; /     switch (length) { /         case 0: length = privateMsg->text.size; break; /         default: break; /     } /     if (length == 0) /         return NWC24_ERR_NULL; /     if (length > capacity - 1) { /         length = capacity - 1; /         overflow = NWC24_ERR_OVERFLOW; /     } /     result = NWC24iMBoxOpenStoredMsg(type, privateMsg->msgId, &file); /     switch (result) { /         case NWC24_OK: /             break; /         default: /             return result; /     } /     Mail_memset(charset, 0, charsetCapacity); /     if (privateMsg->unk_0x50.size >= charsetCapacity) /         result = NWC24_ERR_FORMAT; /     else { /         if (privateMsg->unk_0x50.size != 0) { /             NWC24FSeek(&file, (u32)privateMsg->unk_0x50.ptr, NWC24_SEEK_BEG); /             result = NWC24FRead(charset, privateMsg->unk_0x50.size, &file); /             if (result != NWC24_OK) /                 goto close; /         } /         if (privateMsg->unk_0x58.size != 0 && privateMsg->unk_0x58.size < 32) { /             Mail_memset(buffer, 0, 32); /             NWC24FSeek(&file, (u32)privateMsg->unk_0x58.ptr, NWC24_SEEK_BEG); /             result = NWC24FRead(buffer, privateMsg->unk_0x58.size, &file); /             if (result != NWC24_OK) /                 goto close; /             result = NWC24ParseEncodingStr(encoding, buffer); /             if (result != NWC24_OK) /                 goto close; /         } /         NWC24FSeek(&file, (u32)privateMsg->text.ptr, NWC24_SEEK_BEG); /         switch (*encoding) { /             case 0: /             case 1: /                 result = NWC24FRead(text, length, &file); /                 text[length] = 0; /                 break; /             case 2: { /                 NWC24Err decodeResult; /                 decodedSize = 0; /                 decodeResult = ReadBase64Data(&file, &privateMsg->text, (u8*)text, length, &decodedSize); /                 if (decodeResult == NWC24_OK && decodedSize != privateMsg->textSize) /                     decodeResult = NWC24_ERR_FORMAT; /                 result = decodeResult; /                 text[length] = 0; /                 break; /             } /             case 3: /                 result = ReadQPText(privateMsg, &file, text, length); /                 break; /             default: /                 result = NWC24_ERR_NOT_SUPPORTED; /                 *text = 0; /                 break; /         } /     } / close: /     closeResult = NWC24iMBoxCloseMsg(&file); /     if (result != NWC24_OK) /         closeResult = result; /     if (closeResult != NWC24_OK) /         overflow = closeResult; /     return overflow; / } /
- NWC24ReadMsgTextPublic: diagnose success conditional plus overflow switch candidate via ctxdiff: src 0x114 base 0x118 insns 69/70 / --- replace mine 15:16 base 15:16 /   M   15 b 192 /   B   15 b 196 / --- replace mine 23:24 base 23:24 /   M   23 b 160 /   B   23 b 164 / --- replace mine 28:29 base 28:29 /   M   28 b 140 /   B   28 b 144 / --- replace mine 43:44 base 43:44 /   M   43 beq 20 /   B   43 beq 24 / --- replace mine 45:47 base 45:46 /   M   45 beq 8 /   M   46 b 68 /   B   45 bne 76 / --- insert mine 48:48 base 47:49 /   B   47 b 8 /   B   48 b 64 /; restored.
Correction: first ReadMsgTextInternal declaration search extended past leading declarations because this function has no blank before first statement. Its retained diff was only privateMsg/buffer declaration swap; no control flow was changed. Re-running with strict declaration recognition plus combined result/closeResult declaration; invalid nondeclaration shuffle evaluations are not credited as attempts.
- ReadMsgTextInternal: register-only last declsearch explicit actual body lines 389-396 max180: ((7, 157), 177, 178) -> ((7, 157), 177, 178); declaration block: /       char* buffer; /       NWC24MBoxType type; /       NWC24File file; /       NWC24Err result, closeResult; /       NWC24Err overflow = NWC24_OK; /       u32 length; /       u32 decodedSize; /       const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg; / start (7, 157) / best (7, 157) after 71 builds; source restored; best order was: /     char* buffer; /     NWC24MBoxType type; /     NWC24File file; /     NWC24Err result, closeResult; /     NWC24Err overflow = NWC24_OK; /     u32 length; /     u32 decodedSize; /     const NWC24MsgObjPrivate* privateMsg = (const NWC24MsgObjPrivate*)msg; /
- NWC24iSetMsgSubjectQP: first-line charset length separated from folding limit, then register-only declsearch actual leading block 744-756; ((0, 12), 144, 144) -> ((0, 0), 144, 144); declaration block: /       u32 workHalf; /       u32 sourceOffset; /       u32 secondSize; /       u8* second; /       u32 subjectLength; /       u32 lineLength; /       u32 outputLength; /       u32 total; /       u32 combinedLength; /       u32 i; /       u32 charsetLength; /       u32 firstCharsetLength; /       NWC24Err result; / start (0, 15) / improved (0, 3) / improved (0, 0) / best (0, 0) after 92 builds; kept in source: /     u32 workHalf; /     u32 sourceOffset; /     u32 charsetLength; /     u8* second; /     u32 subjectLength; /     u32 lineLength; /     u32 secondSize; /     u32 total; /     u32 combinedLength; /     u32 i; /     u32 outputLength; /     u32 firstCharsetLength; /     NWC24Err result; /; kept
- ConvertDaysToDate: month leap scope and shared continuation 1: ((0, 26), 103, 103) -> ((7, 47), 107, 103); restored
- ConvertDaysToDate: month leap scope and shared continuation 2: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: month leap scope and shared continuation 3: ((0, 26), 103, 103) -> ((0, 31), 103, 103); restored
- ConvertDaysToDate: register-only last after helper/scope/branch structural attempts, actual loop lines 208-211: declaration block: /           u16 currentYear = *year; /           s32 previousDays = days; /           BOOL leapYear = TRUE; /           BOOL commonLeapYear = FALSE; / start (0, 26) / best (0, 26) after 13 builds; source restored; best order was: /         u16 currentYear = *year; /         s32 previousDays = days; /         BOOL leapYear = TRUE; /         BOOL commonLeapYear = FALSE; /
- ConvertDaysToDate: register-only last after helper/scope/branch structural attempts, actual loop lines 228-229: declaration block: /           s32 previousDays; /           u8 currentMonth; / start (0, 26) / best (0, 26) after 2 builds; source restored; best order was: /         s32 previousDays; /         u8 currentMonth; /

Round d QP exact: separating the first-line charset byte count from the later folding budget changes real temporary lifetime interference. Leading declaration search reached144/144,diffs0,exact-nameobjdiff100.0000. Subject7/12->8/12,code2776->3352,data232/232. ReadText declaration placement also improves96.853935->97.44382 without changing other functions. Quick gate over threePASS,poolsidentical,globalregressions0,forbidden0,readability0,DOLverified.
- NWC24iDateToOSCalendarTime: year/fraction named local lifetime graph variant1 followed by register-only leading-declaration search; ((0, 13), 85, 85) -> ((0, 13), 85, 85); declaration block: /       u16 currentYear; /       BOOL isLeapYear; /       s32 days; / start (0, 13) / best (0, 13) after 6 builds; source restored; best order was: /     u16 currentYear; /     BOOL isLeapYear; /     s32 days; /; restored
- NWC24iDateToOSCalendarTime: year/fraction named local lifetime graph variant2 followed by register-only leading-declaration search; ((0, 13), 85, 85) -> ((0, 13), 85, 85); declaration block: /       s32 fraction; /       BOOL isLeapYear; /       s32 days; / start (0, 13) / best (0, 13) after 6 builds; source restored; best order was: /     s32 fraction; /     BOOL isLeapYear; /     s32 days; /; restored
- NWC24iDateToOSCalendarTime: year/fraction named local lifetime graph variant3 followed by register-only leading-declaration search; ((0, 13), 85, 85) -> ((0, 13), 85, 85); declaration block: /       u16 currentYear; /       s32 fraction; /       BOOL isLeapYear; /       s32 days; / start (0, 13) / best (0, 13) after 13 builds; source restored; best order was: /     u16 currentYear; /     s32 fraction; /     BOOL isLeapYear; /     s32 days; /; restored
- NWC24iSetMsgSubjectBase64: first-line charset byte count separated from later folding charset count, then register-only leading-block declsearch; ((0, 5), 136, 136) -> ((0, 5), 136, 136); declaration block: /       u8* second; /       u32 secondSize; /       u32 workHalf; /       u32 subjectLength; /       u32 lineLength; /       u32 sourceOffset; /       u32 outputLength; /       u32 total; /       u32 charsetLength; /       u32 firstCharsetLength; /       NWC24Err result; / start (0, 5) / best (0, 5) after 146 builds; source restored; best order was: /     u8* second; /     u32 secondSize; /     u32 workHalf; /     u32 subjectLength; /     u32 lineLength; /     u32 sourceOffset; /     u32 outputLength; /     u32 total; /     u32 charsetLength; /     u32 firstCharsetLength; /     NWC24Err result; /; restored

### Round d completeness audit
NWC24ReadMsgField: 7 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
NWC24ReadMsgFromAddr: 3 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
NWC24ReadMsgSubject: 3 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
ReadMsgTextInternal: 6 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
NWC24ReadMsgAttached: 3 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
NWC24ReadMsgSubjectPublic: 3 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
NWC24ReadMsgTextPublic: 3 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
NWC24SetMsgSubjectAndTextPublic: 3 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
NWC24iSetMsgSubjectQP: 8 logged compiled source variations, at least3 distinct source transformations. Now exact144/144,diffs0,objdiff100%; source commit592e7c2b.
NWC24iSetMsgSubjectBase64: 5 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
NWC24iDateToOSCalendarTime: 3 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
ConvertDateToDays: 6 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
ConvertDaysToDate: 11 logged compiled source variations, at least3 distinct source transformations. Still open; closest accepted state retains original real functions and data.
Each open function received an origin fetch and unchanged-source comparison before starting. Rejected compile failures and invalid whole-body declaration shuffles are not used to satisfy the three-source-attempt requirement. Owned data128/128,232/232,40/40 was already fully paired and exact; no config renames/extents or extra weak-symbol suppression were attempted. All header experiments were restored.

### Round d final remaining-function audit
NWC24ReadMsgField 98.92157%: 101/102 instructions; target reloads message type after protection check, source shares the load. At least three compiled distinct source attempts this round.
NWC24ReadMsgFromAddr 98.804344%: 91/92 instructions; target reloads message type after capability check, source shares the load. At least three compiled distinct source attempts this round.
NWC24ReadMsgSubject 98.65854%: 81/82 instructions; target reloads message type after protection check, source shares the load. At least three compiled distinct source attempts this round.
ReadMsgTextInternal 97.44382%: 177/178 instructions; target type reload is absent, and buffer/length temporaries exchange saved registers. Clamp and Base64 result scheduling now match. At least three compiled distinct source attempts this round.
NWC24ReadMsgAttached 96.37363%: 90/91 instructions; missing type reload plus attachment-index/result temporary allocation. At least three compiled distinct source attempts this round.
NWC24ReadMsgSubjectPublic 96.15385%: 100/104 instructions; two overflow acceptance paths lack target branch pairs. At least three compiled distinct source attempts this round.
NWC24ReadMsgTextPublic 97.14286%: 68/70 instructions; overflow acceptance path lacks target branch pair. At least three compiled distinct source attempts this round.
NWC24SetMsgSubjectAndTextPublic 98.23684%: 190/190 instructions; only saved-register allocation, work context r31 versus targetr22 shifts input register coloring. At least three compiled distinct source attempts this round.
NWC24iSetMsgSubjectBase64 99.632355%: 136/136 instructions; only five parameter-capture move ordering differences; body exact. At least three compiled distinct source attempts this round.
NWC24iDateToOSCalendarTime 99.17647%: 85/85 instructions; only thirteen register differences, year and shared zero/leap flag exchange r0/r5. At least three compiled distinct source attempts this round.
ConvertDateToDays 96.92921%: 113/113 instructions; final signed division scheduling and operand allocation differ. At least three compiled distinct source attempts this round.
ConvertDaysToDate 97.718445%: 103/103 instructions; only twenty-six month-loop register differences; year loop exact. At least three compiled distinct source attempts this round.
All12 remaining names checked against the current full gate; none is untried. Uncertainty remains in source constructs needed to reproduce the surviving compiler sharing, unreachable branch, scheduling and coloring decisions. No owned-data uncertainty remains.

### Round d final full gate: clean non-quick build
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgRead] objdiff: code 2480/4660 data 128/128 functions 11/16 fuzzy 99.0429 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgRead] instruction-exact functions: 11/16
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 3352/5352 data 232/232 functions 8/12 fuzzy 99.2638 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 8/12
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1168/2372 data 40/40 functions 5/8 fuzzy 98.9005 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 5/8
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
Before -> after instruction-exact/code bytes/data bytes: MsgRead11/2480/128 ->11/2480/128; MsgSubject7/2776/232 ->8/3352/232; DateParser5/1168/40 ->5/1168/40. ReadMsgTextInternal94.55056 ->97.44382, retained as fuzzy improvement; NWC24iSetMsgSubjectQP99.548615 ->100.0000, retained as exact144/144,diffs0.
Changed source files: libs/RevoEX/src/nwc24/NWC24MsgRead.c and libs/RevoEX/src/nwc24/NWC24MsgSubject.c. Source commits e1602004 and592e7c2b. Attempts log tools/decomp-assist/fz7.attempts.md. Shared header, DateParser, configuration, all other sources remain unchanged.

## Round e: proven source levers
Fresh origin baseline: Read 11/16, Subject 8/12, Date 5/8. All owned data sections already 100%; no symbol rename or extent correction warranted.

### NWC24ReadMsgField
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: target has one additional type-word reload between permission/capability branch and SelectMBox, same frame; text/attached also retain register scheduling differences. Test switch boundary before register allocation.
- NWC24ReadMsgField: permission mask single-case switch boundary: ((3, 84), 101, 102) -> ((4, 6), 102, 102); restored
- NWC24ReadMsgField: mutable local private view for inline alias analysis: ((3, 84), 101, 102) -> ((0, 0), 102, 102); kept
- NWC24ReadMsgField: permission comparison uses named unsigned flags: ((0, 0), 102, 102) -> compile failure; restored

### NWC24ReadMsgFromAddr
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: target has one additional type-word reload between permission/capability branch and SelectMBox, same frame; text/attached also retain register scheduling differences. Test switch boundary before register allocation.
- NWC24ReadMsgFromAddr: permission mask single-case switch boundary: ((4, 66), 91, 92) -> ((5, 14), 92, 92); restored
- NWC24ReadMsgFromAddr: mutable local private view for inline alias analysis: ((4, 66), 91, 92) -> ((0, 0), 92, 92); kept
- NWC24ReadMsgFromAddr: permission comparison uses named unsigned flags: ((0, 0), 92, 92) -> compile failure; restored

### NWC24ReadMsgSubject
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: target has one additional type-word reload between permission/capability branch and SelectMBox, same frame; text/attached also retain register scheduling differences. Test switch boundary before register allocation.
- NWC24ReadMsgSubject: permission mask single-case switch boundary: ((3, 65), 81, 82) -> ((4, 6), 82, 82); restored
- NWC24ReadMsgSubject: mutable local private view for inline alias analysis: ((3, 65), 81, 82) -> ((0, 0), 82, 82); kept
- NWC24ReadMsgSubject: permission comparison uses named unsigned flags: ((0, 0), 82, 82) -> compile failure; restored

### ReadMsgTextInternal
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: target has one additional type-word reload between permission/capability branch and SelectMBox, same frame; text/attached also retain register scheduling differences. Test switch boundary before register allocation.
- ReadMsgTextInternal: permission mask single-case switch boundary: ((7, 157), 177, 178) -> ((8, 25), 178, 178); restored
- ReadMsgTextInternal: mutable local private view for inline alias analysis: ((7, 157), 177, 178) -> ((0, 15), 178, 178); kept
- ReadMsgTextInternal: permission comparison uses named unsigned flags: ((0, 15), 178, 178) -> compile failure; restored

### NWC24ReadMsgAttached
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: target has one additional type-word reload between permission/capability branch and SelectMBox, same frame; text/attached also retain register scheduling differences. Test switch boundary before register allocation.
- NWC24ReadMsgAttached: permission mask single-case switch boundary: ((6, 75), 90, 91) -> ((7, 34), 91, 91); restored
- NWC24ReadMsgAttached: mutable local private view for inline alias analysis: ((6, 75), 90, 91) -> ((2, 18), 91, 91); kept
- NWC24ReadMsgAttached: permission comparison uses named unsigned flags: ((2, 18), 91, 91) -> compile failure; restored

Round e pool audit: all three pools IDENTICAL before trials; original/source data sections already 128/128, 232/232, 40/40. No data rename or extent adjustment.
NWC24ReadMsgField extent audit: 0x814A861C+0x198 <= next NWC24ReadMsgFaceData at 0x814A87B4: True.
NWC24ReadMsgField: immediate stack store/reload audit: none; no volatile declaration justified.
NWC24ReadMsgFromAddr extent audit: 0x814A8DD4+0x170 <= next NWC24ReadMsgSubject at 0x814A8F44: True.
NWC24ReadMsgFromAddr: immediate stack store/reload audit: none; no volatile declaration justified.
NWC24ReadMsgSubject extent audit: 0x814A8F44+0x148 <= next NWC24ReadMsgText at 0x814A908C: True.
NWC24ReadMsgSubject: immediate stack store/reload audit: none; no volatile declaration justified.
ReadMsgTextInternal extent audit: 0x814A91A0+0x2C8 <= next NWC24ReadMsgAttached at 0x814A9468: True.
ReadMsgTextInternal: immediate stack store/reload audit: none; no volatile declaration justified.
NWC24ReadMsgAttached extent audit: 0x814A9468+0x16C <= next ReadBase64Data at 0x814A95D4: True.
NWC24ReadMsgAttached: immediate stack store/reload audit: none; no volatile declaration justified.
NWC24ReadMsgSubjectPublic extent audit: 0x814A9850+0x1A0 <= next NWC24ReadMsgTextPublic at 0x814A99F0: True.
NWC24ReadMsgSubjectPublic: immediate stack store/reload audit: none; no volatile declaration justified.
NWC24ReadMsgTextPublic extent audit: 0x814A99F0+0x118 <= next NWC24SetMsgSubjectPublic at 0x814A9B08: True.
NWC24ReadMsgTextPublic: immediate stack store/reload audit: none; no volatile declaration justified.
NWC24SetMsgSubjectAndTextPublic extent audit: 0x814A9CD0+0x2F8 <= next NWC24iGetDefaultCharset at 0x814A9FC8: True.
NWC24SetMsgSubjectAndTextPublic: immediate stack store/reload audit: none; no volatile declaration justified.
NWC24iSetMsgSubjectBase64 extent audit: 0x814AAB18+0x220 <= next NWC24SuspendScheduler at 0x814AAD38: True.
NWC24iSetMsgSubjectBase64: immediate stack store/reload audit: none; no volatile declaration justified.
NWC24iDateToOSCalendarTime extent audit: 0x814AC1C4+0x154 <= next NWC24iIsValidDate at 0x814AC318: True.
NWC24iDateToOSCalendarTime: immediate stack store/reload audit: none; no volatile declaration justified.
ConvertDateToDays extent audit: 0x814AC348+0x1C4 <= next ConvertDaysToDate at 0x814AC50C: True.
ConvertDateToDays: immediate stack store/reload audit: none; no volatile declaration justified.
ConvertDaysToDate extent audit: 0x814AC50C+0x19C <= next NWC24ReadFriendInfo at 0x814AC6A8: True.
ConvertDaysToDate: immediate stack store/reload audit: none; no volatile declaration justified.
- ReadMsgTextInternal: register-only declaration search on actual leading locals after structural trials, ((0, 15), 178, 178) -> ((0, 0), 178, 178); (0, 0) after 6 builds; kept in source:.

### NWC24ReadMsgSubjectPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: same frame; each overflow acceptance block lacks two target branches. No immediate stack store/reload proof; volatile rejected without experiment. Test bool switch and helper boundaries.
- NWC24ReadMsgSubjectPublic: boolean success switch with overflow arm break: ((11, 64), 100, 104) -> ((14, 46), 104, 104); restored
- NWC24ReadMsgSubjectPublic: mutable input alias passed into read calls: ((11, 64), 100, 104) -> ((11, 78), 100, 104); restored
- NWC24ReadMsgSubjectPublic: overflow arm routed through shared continuation label: ((11, 64), 100, 104) -> ((11, 64), 100, 104); restored

### NWC24ReadMsgTextPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: same frame; each overflow acceptance block lacks two target branches. No immediate stack store/reload proof; volatile rejected without experiment. Test bool switch and helper boundaries.
- NWC24ReadMsgTextPublic: boolean success switch with overflow arm break: ((7, 28), 68, 70) -> ((7, 7), 70, 70); kept
- NWC24ReadMsgTextPublic: mutable input alias passed into read calls: ((7, 7), 70, 70) -> ((7, 25), 70, 70); restored

### NWC24ReadMsgAttached
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
- NWC24ReadMsgAttached: decode validation conditional replaces one-case switch: ((2, 18), 91, 91) -> ((8, 34), 90, 91); restored
- NWC24ReadMsgAttached: block-local decode result before error propagation: ((2, 18), 91, 91) -> ((5, 29), 91, 91); restored
- NWC24ReadMsgAttached: register-only declaration search on actual leading locals after structural trials, ((2, 18), 91, 91) -> ((2, 18), 91, 91); order was:.
- NWC24ReadMsgTextPublic: explicit accepted read label after overflow branch: ((7, 28), 68, 70) -> ((7, 28), 68, 70); restored

### NWC24SetMsgSubjectAndTextPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: 190/190 same frame and branches, saved parameter/work context register group shifted. Try const read view and separate semantic charset/text encoding lifetimes before declaration search.
- NWC24SetMsgSubjectAndTextPublic: const work-context view while buffers stay mutable: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored
- NWC24SetMsgSubjectAndTextPublic: const private message view for protection fields: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored
- NWC24SetMsgSubjectAndTextPublic: separate text encoding from result error lifetime: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored

### NWC24iDateToOSCalendarTime
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: 85/85 frame0x10, all branches/calls identical; year and zero/leap values exchange r0/r5. Const input alias and distinct first/later year lifetimes tested before declaration order.
- NWC24iDateToOSCalendarTime: mutable date input view changes alias assumptions: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- NWC24iDateToOSCalendarTime: distinct zero milliseconds local from leap flag: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- NWC24iDateToOSCalendarTime: calendar stored year drives leap test: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored

### ConvertDateToDays
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: 113/113 leaf; last arithmetic region schedules divisors and accumulated days differently. Separate quotient temporaries then search new interference graph.
- ConvertDateToDays: previous year signed temporary reused by both divisions: ((4, 16), 113, 113) -> ((6, 17), 113, 113); restored
- ConvertDateToDays: separate accumulated whole year days before final addition: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- ConvertDateToDays: register-only declaration search on actual leading locals after structural trials, ((4, 16), 113, 113) -> ((4, 16), 113, 113); order was:.
- ConvertDateToDays: split quarter/century quotient semantic locals followed by declaration graph search: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored

### ConvertDaysToDate
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: 103/103 frame0x10; year loop exact, month leap test uses different r0/r8/r11/r12. Const read-only year view and month length temporaries tested.
- ConvertDaysToDate: const year view for month leap helper: ((0, 26), 103, 103) -> compile failure; restored
- ConvertDaysToDate: month length temporary unifies subtraction: ((0, 26), 103, 103) -> ((6, 42), 102, 103); restored
- ConvertDaysToDate: separate promoted year value in month leap test: ((0, 26), 103, 103) -> ((5, 35), 103, 103); restored
- NWC24ReadMsgAttached: const read view only for post-decode attachment size: ((2, 18), 91, 91) -> ((0, 0), 91, 91); kept
- NWC24ReadMsgAttached: const read view for both attachment size checks: ((0, 0), 91, 91) -> ((8, 28), 90, 91); restored
- NWC24ReadMsgAttached: separate attachment index for post-call decoded size: ((0, 0), 91, 91) -> ((0, 0), 91, 91); restored

### NWC24iSetMsgSubjectBase64
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
Structural diagnosis: frame0x60 and136/136 instructions identical; only5 parameter-copy order differences at prologue. Separate work first-half alias and mutable subject read view before searching declarations.
- NWC24iSetMsgSubjectBase64: first buffer alias initialized before output locals: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- NWC24iSetMsgSubjectBase64: mutable subject local view at converter inline boundary: ((0, 5), 136, 136) -> ((0, 50), 136, 136); restored
- NWC24iSetMsgSubjectBase64: register-only declaration search on actual leading locals after structural trials, ((0, 5), 136, 136) -> ((0, 5), 136, 136); order was:.
- NWC24iSetMsgSubjectBase64: first-half work-buffer alias with separate assignment and declaration graph search: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- NWC24iDateToOSCalendarTime: leap calculation within existing inline helper boundary: ((0, 13), 85, 85) -> ((5, 76), 86, 85); restored
- ConvertDaysToDate: const year view declared before month statements: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: leap helper promotes year into named signed value: ((0, 26), 103, 103) -> ((0, 28), 103, 103); restored
- ConvertDaysToDate: leap helper separates declaration from zero assignment: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: leap helper boolean conditional expression: ((0, 26), 103, 103) -> ((0, 28), 103, 103); restored

### NWC24ReadMsgSubjectPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
- NWC24ReadMsgSubjectPublic: direct enum overflow switch arm order ok,overflow,default: ((11, 64), 100, 104) -> ((10, 10), 104, 104); kept
- NWC24iDateToOSCalendarTime: leap zero initialized at arithmetic block instead of field copies: ((0, 13), 85, 85) -> ((5, 76), 86, 85); restored
- NWC24iDateToOSCalendarTime: fraction zero stores grouped behind inline helper: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- NWC24iDateToOSCalendarTime: unsigned leap flag separates type from signed calendar zero: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- NWC24iDateToOSCalendarTime: byte leap flag with promoted comparison: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored

### NWC24ReadMsgSubjectPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
- NWC24ReadMsgSubjectPublic: direct enum overflow switch arm order ok,overflow,default: ((11, 64), 100, 104) -> ((10, 10), 104, 104); kept
- NWC24ReadMsgSubjectPublic: direct enum overflow switch arm order ok,default,overflow: ((11, 64), 100, 104) -> ((10, 10), 104, 104); kept
- NWC24ReadMsgSubjectPublic: direct enum overflow switch arm order overflow,ok,default: ((11, 64), 100, 104) -> ((10, 10), 104, 104); kept
- NWC24ReadMsgSubjectPublic: direct enum overflow switch arm order overflow,default,ok: ((11, 64), 100, 104) -> ((10, 10), 104, 104); kept
- NWC24ReadMsgSubjectPublic: direct enum overflow switch arm order default,ok,overflow: ((11, 64), 100, 104) -> ((10, 10), 104, 104); kept
- NWC24ReadMsgSubjectPublic: direct enum overflow switch arm order default,overflow,ok: ((11, 64), 100, 104) -> ((10, 10), 104, 104); kept

### NWC24ReadMsgTextPublic
Fetched origin and confirmed owned source equals baseline origin unit, where this exact-name function was below 100.
- NWC24ReadMsgTextPublic: direct enum overflow switch arm order ok,overflow,default: ((7, 28), 68, 70) -> ((5, 5), 70, 70); kept
- NWC24ReadMsgTextPublic: direct enum overflow switch arm order ok,default,overflow: ((7, 28), 68, 70) -> ((5, 5), 70, 70); kept
- NWC24ReadMsgTextPublic: direct enum overflow switch arm order overflow,ok,default: ((7, 28), 68, 70) -> ((5, 5), 70, 70); kept
- NWC24ReadMsgTextPublic: direct enum overflow switch arm order overflow,default,ok: ((7, 28), 68, 70) -> ((5, 5), 70, 70); kept
- NWC24ReadMsgTextPublic: direct enum overflow switch arm order default,ok,overflow: ((7, 28), 68, 70) -> ((5, 5), 70, 70); kept
- NWC24ReadMsgTextPublic: direct enum overflow switch arm order default,overflow,ok: ((7, 28), 68, 70) -> ((5, 5), 70, 70); kept
- ConvertDaysToDate: signed promoted leap-helper parameter: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: const qualified scalar leap-helper parameter: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: leap helper named year and flag with plain declarations: ((0, 26), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: leap helper year assignment precedes flag zero: ((0, 26), 103, 103) -> ((0, 28), 103, 103); restored
- NWC24SetMsgSubjectAndTextPublic: work context declaration scoped to post-validation operations: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored
- NWC24iDateToOSCalendarTime: register-only declaration search on actual leading locals after structural trials, ((0, 13), 85, 85) -> ((0, 13), 85, 85); order was:.
- ConvertDaysToDate: final register-only month declaration order search, order was:; unchanged26 exact differences.
- NWC24iSetMsgSubjectBase64: register-only declaration search on actual leading locals after structural trials, ((0, 50), 136, 136) -> ((0, 26), 136, 136); (0, 26) after 170 builds; kept in source:.
- NWC24iSetMsgSubjectBase64: mutable input view plus declaration interference search: ((0, 5), 136, 136) -> ((0, 26), 136, 136); restored

## Round e completion audit
MsgRead gained FIVE exact functions: 11/16 -> 16/16, code2480/4660 ->4660/4660, data128/128 unchanged. Subject8/12 and Date5/8 retained baseline exact/code/data counts. All pools remain identical.
Const lever proof: mutable private read views preserve the distinct initial permission load followed by the inline SelectMBox const load. Attached post-decode size uses a const read view while earlier bounds use the mutable view; this reproduces the target address recalculation. Definition-level volatile not used: none of the twelve targets has the required immediate stack store/reload pair. All twelve extents end at or before their next symbol.
Trial bookkeeping correction: direct enum switch arm permutations were temporarily kept by the normalized structural scorer but explicitly restored after each independent trial. Their extra bge is less faithful than baseline; no Subject or Date source changes remain. Compile failures and no-op replacements do not count as attempts.
OPEN NWC24ReadMsgSubjectPublic 96.15385%: overflow branch layout,100/104 instructions. Three distinct compiled Round e source attempts confirmed: boolean switch; mutable input alias; nested default switch.
OPEN NWC24ReadMsgTextPublic 97.14286%: overflow branch layout,68/70 instructions. Three distinct compiled Round e source attempts confirmed: boolean switch; mutable input alias; shared accepted label.
OPEN NWC24SetMsgSubjectAndTextPublic 98.23684%: saved parameter/context registers,190/190 instructions. Three distinct compiled Round e source attempts confirmed: const context view; const protection view; separate text encoding lifetime.
OPEN NWC24iSetMsgSubjectBase64 99.632355%: 5 parameter-copy ordering differences,136/136 instructions. Three distinct compiled Round e source attempts confirmed: initialized first-buffer alias; mutable subject view; plain first-buffer alias plus declaration search.
OPEN NWC24iDateToOSCalendarTime 99.17647%: 13 year/zero/leap register differences,85/85 instructions. Three distinct compiled Round e source attempts confirmed: mutable date view; named fractional zero; calendar-year leap input.
OPEN ConvertDateToDays 96.92921%: last quotient/add scheduling,113/113 instructions. Three distinct compiled Round e source attempts confirmed: previous-year temporary; whole-year-days temporary; separate quotient locals plus declaration search.
OPEN ConvertDaysToDate 97.718445%: 26 month-loop register differences,103/103 instructions. Three distinct compiled Round e source attempts confirmed: month-length local; promoted month year; const year view in declaration block.
Data audit: 128/128,232/232,40/40; no renames, extent edits, hand-placed data, or shared-header changes. Uncertainty: remaining source structure for overflow branch redundancy and register/scheduling tie-breaks.
NWC24ReadMsgField: final src 0x198 base 0x198 insns 102/102; diffs 0: [];
NWC24ReadMsgFromAddr: final src 0x170 base 0x170 insns 92/92; diffs 0: [];
NWC24ReadMsgSubject: final src 0x148 base 0x148 insns 82/82; diffs 0: [];
ReadMsgTextInternal: final src 0x2c8 base 0x2c8 insns 178/178; diffs 0: [];
NWC24ReadMsgAttached: final src 0x16c base 0x16c insns 91/91; diffs 0: [];

Round e final full gate (non --quick), all three owned units:
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgRead] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgRead] objdiff: code 4660/4660 data 128/128 functions 16/16 fuzzy 100.0000 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgRead] instruction-exact functions: 16/16
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .data size 128 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgRead]   section .text size 4660 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgRead] baseline: code 2480/4660 data 128 functions 11 fuzzy 99.0429
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 3352/5352 data 232/232 functions 8/12 fuzzy 99.2638 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 8/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 99.263824
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectBase64 99.632355
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 3352/5352 data 232 functions 8 fuzzy 99.2638
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1168/2372 data 40/40 functions 5/8 fuzzy 98.9005 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 5/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 98.900505
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: NWC24iDateToOSCalendarTime 99.17647
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 97.718445
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 98.9005
regressions vs baseline: 0
global matched_code_percent: 89.20985 -> 89.28263
global fuzzy_match_percent: 99.52432 -> 99.52582
global complete_code_percent: 67.00815 -> 67.00815
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
Five new exact functions independently checked with ctxdiff0 before the clean build; full gate rebuilt all three and confirmed Read16/16, Subject8/12, Date5/8; DOL hash exact; regressions0; forbidden0; readability0. Seven open functions have at least three distinct successfully compiled Round e source trials; none left untried.
Code commits: dc2a77e8 (permission reloads),4b24e55f (text lifetimes),76bf9daa (attachment const read view). Files changed: libs/RevoEX/src/nwc24/NWC24MsgRead.c and this attempts log only.

## Round f: six owned units
All six pools IDENTICAL before tuning. Owned data sections already100%, Exif has no owned data. SDMemory objdiff64/66 but instruction-exact63/66; audit the extra nominal100 function.

### NWC24ReadMsgSubjectPublic
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x190 base 0x1a0 insns 100/104; --- replace mine 14:15 base 14:15;   M   14 b 320;   B   14 b 336; --- replace mine 22:23 base 22:23;   M   22 b 288;   B   22 b 304; --- replace mine 30:31 base 30:31;   M   30 b 256;   B   30 b 272; --- replace mine 41:42 base 41:42;   M   41 beq 16;   B   41 beq 24; --- replace mine 43:44 base 43:44;   M   43 bne 204;   B   43 bne 220; --- insert mine 45:45 base 45:47;   B   45 b 8;   B   46 b 208; --- replace mine 55:56 base 57:58;   M   55 beq 16;   B   57 beq 24; --- replace mine 57:58 base 59:60;   M   57 bne 148;   B   59 bne 156; --- insert mine 59:59 base 61:63;   B   61 b 8;   B   62 b 144;
Structural diagnosis: same frame; target has redundant overflow-case exit branches, two missing instructions per overflow path. Try nested boolean switch, local error scope and inline accept boundary; register tuning cannot replace these branches.
- NWC24ReadMsgSubjectPublic: nested boolean success/overflow switch: ((11, 64), 100, 104) -> ((33, 98), 120, 104); restored
- NWC24ReadMsgSubjectPublic: local error view in overflow validation scope: ((11, 64), 100, 104) -> ((11, 64), 100, 104); restored
- NWC24ReadMsgSubjectPublic: inline overflow acceptance policy: ((11, 64), 100, 104) -> ((27, 91), 114, 104); restored

### NWC24ReadMsgTextPublic
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x110 base 0x118 insns 68/70; --- replace mine 15:16 base 15:16;   M   15 b 188;   B   15 b 196; --- replace mine 23:24 base 23:24;   M   23 b 156;   B   23 b 164; --- replace mine 28:29 base 28:29;   M   28 b 136;   B   28 b 144; --- replace mine 43:44 base 43:44;   M   43 beq 16;   B   43 beq 24; --- replace mine 45:46 base 45:46;   M   45 bne 68;   B   45 bne 76; --- insert mine 47:47 base 47:49;   B   47 b 8;   B   48 b 64;
Structural diagnosis: same frame; target has redundant overflow-case exit branches, two missing instructions per overflow path. Try nested boolean switch, local error scope and inline accept boundary; register tuning cannot replace these branches.
- NWC24ReadMsgTextPublic: nested boolean success/overflow switch: ((7, 28), 68, 70) -> ((18, 39), 78, 70); restored
- NWC24ReadMsgTextPublic: local error view in overflow validation scope: ((7, 28), 68, 70) -> ((7, 28), 68, 70); restored
- NWC24ReadMsgTextPublic: inline overflow acceptance policy: ((7, 28), 68, 70) -> ((15, 35), 75, 70); restored

### NWC24SetMsgSubjectAndTextPublic
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x2f8 base 0x2f8 insns 190/190; diffs 65: [6, 7, 8, 10, 11, 12, 13, 14, 15, 34, 35, 36, 37, 38, 39, 40, 57, 58, 59, 60];      6 M mr r22, r3;        B mr r23, r3;      7 M lwz r30, 0x58(r1);        B lwz r31, 0x58(r1);      8 M mr r23, r4;        B mr r24, r4;     10 M mr r24, r5;        B mr r25, r5;     11 M mr r25, r6;        B mr r26, r6;     12 M mr r26, r7;        B mr r27, r7;     13 M mr r27, r8;        B mr r28, r8;     14 M mr r28, r9;        B mr r29, r9;     15 M mr r29, r10;        B mr r30, r10;     34 M mr r3, r22;        B mr r3, r23;     35 M mr r4, r23;        B mr r4, r24;     36 M mr r5, r24;        B mr r5, r25;     37 M mr r6, r27;        B mr r6, r28;     38 M mr r7, r28;        B mr r7, r29;     39 M mr r8, r29;        B mr r8, r30;     40 M mr r9, r30;        B mr r9, r31;     57 M lwz r31, 0(0);        B lwz r22, 0(0);     58 M mr r5, r23;        B mr r5, r24;     59 M mr r6, r24;        B mr r6, r25;     60 M mr r7, r25;        B mr r7, r26;     61 M mr r3, r31;        B mr r3, r22;     62 M mr r8, r26;        B mr r8, r27;     63 M mr r9, r27;        B mr r9, r28;     69 M mr r4, r31;        B mr r4, r22;     76 M mullw r4, r30, r26;        B mullw r4, r31, r27;     77 M slwi r0, r24, 2;        B slwi r0, r25, 2;     78 M stw r26, 0x1c(r1);        B stw r27, 0x1c(r1);     79 M mr r3, r29;        B mr r3, r30;     80 M add r0, r26, r0;        B add r0, r27, r0;     81 M mr r5, r25;        B mr r5, r26;     83 M mr r7, r31;        B mr r7, r22;     84 M mr r9, r27;        B mr r9, r28;     85 M mr r10, r28;        B mr r10, r29;     89 M subf r25, r0, r30;        B subf r27, r0, r31;     90 M add r26, r29, r0;        B add r26, r30, r0;     96 M mr r4, r31;        B mr r4, r22;    104 M cmpwi r27, 3;        B cmpwi r28, 3;    106 M cmpwi r27, 0;        B cmpwi r28, 0;    110 M cmpwi r27, 5;        B cmpwi r28, 5;    123 M mr r3, r22;        B mr r3, r23;    125 M mr r4, r29;        B mr r4, r30;    134 M stw r31, 8(r1);        B stw r22, 8(r1);    135 M mr r3, r22;        B mr r3, r23;    136 M mr r4, r23;        B mr r4, r24;    137 M mr r5, r24;        B mr r5, r25;    139 M mr r6, r27;        B mr r6, r28;    140 M mr r7, r28;        B mr r7, r29;    142 M mr r9, r25;        B mr r9, r27;    145 M cmpwi r27, 3;        B cmpwi r28, 3;    147 M cmpwi r27, 0;        B cmpwi r28, 0;    151 M cmpwi r27, 5;        B cmpwi r28, 5;    163 M stw r31, 8(r1);        B stw r22, 8(r1);    164 M mr r3, r22;        B mr r3, r23;    165 M mr r4, r23;        B mr r4, r24;    166 M mr r5, r24;        B mr r5, r25;    168 M mr r6, r27;        B mr r6, r28;    169 M mr r7, r28;        B mr r7, r29;    171 M mr r9, r25;        B mr r9, r27;    174 M stw r31, 8(r1);        B stw r22, 8(r1);    175 M mr r3, r22;        B mr r3, r23;    176 M mr r4, r23;        B mr r4, r24;    177 M mr r5, r24;        B mr r5, r25;    179 M mr r6, r27;        B mr r6, r28;    180 M mr r7, r28;        B mr r7, r29;    182 M mr r9, r25;        B mr r9, r27;
Structural diagnosis:190/190, same frame/control; callee-saved context and input allocation differs. Separate work-size and encoding result lifetimes before declaration search.
- NWC24SetMsgSubjectAndTextPublic: const pointer binding to work context: ((0, 65), 190, 190) -> ((7, 99), 190, 190); restored
- NWC24SetMsgSubjectAndTextPublic: separate ENC API status local: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored
- NWC24SetMsgSubjectAndTextPublic: unsigned text proportion intermediate: ((0, 65), 190, 190) -> ((0, 65), 190, 190); restored

### NWC24iSetMsgSubjectBase64
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x220 base 0x220 insns 136/136; diffs 5: [8, 9, 10, 11, 12];      8 M mr r18, r4;        B mr r22, r8;      9 M mr r19, r5;        B mr r18, r4;     10 M mr r20, r6;        B mr r19, r5;     11 M mr r21, r7;        B mr r20, r6;     12 M mr r22, r8;        B mr r21, r7;
Structural diagnosis:136/136,frame0x60; only5 parameter save copy ordering differences. Inline buffer split boundary and narrowed constant/local views tried.
- NWC24iSetMsgSubjectBase64: first-half buffer pointer scoped to encoder operations: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored

### TMCJPEGDEC_exif_parse
Fetched origin; source equals origin baseline where function is still below100.
- NWC24iSetMsgSubjectBase64: const subject read view with plain binding: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
Initial ctxdiff: src 0x350 base 0x350 insns 212/212; diffs 46: [7, 27, 28, 30, 31, 32, 34, 61, 69, 70, 72, 73, 74, 76, 77, 79, 80, 82, 86, 89];      7 M mr r27, r3;        B mr r30, r3;     27 M lbz r5, 3(r3);        B lbz r6, 3(r3);     28 M lbz r6, 2(r3);        B lbz r5, 2(r3);     30 M rlwimi r6, r5, 8, 0x10, 0x17;        B rlwimi r5, r6, 8, 0x10, 0x17;     31 M rlwinm r0, r6, 8, 0x10, 0x17;        B rlwinm r0, r5, 8, 0x10, 0x17;     32 M rlwimi r0, r6, 0x18, 0x18, 0x1f;        B rlwimi r0, r5, 0x18, 0x18, 0x1f;     34 M clrlwi r0, r6, 0x10;        B clrlwi r0, r5, 0x10;     61 M add r30, r3, r5;        B add r27, r3, r5;     69 M lbz r3, 1(r30);        B lbz r4, 1(r27);     70 M lbz r4, 0(r30);        B lbz r3, 0(r27);     72 M rlwimi r4, r3, 8, 0x10, 0x17;        B rlwimi r3, r4, 8, 0x10, 0x17;     73 M rlwinm r0, r4, 8, 0x10, 0x17;        B rlwinm r0, r3, 8, 0x10, 0x17;     74 M rlwimi r0, r4, 0x18, 0x18, 0x1f;        B rlwimi r0, r3, 0x18, 0x18, 0x1f;     76 M clrlwi r0, r4, 0x10;        B clrlwi r0, r3, 0x10;     77 M clrlwi r26, r0, 0x10;        B clrlwi r23, r0, 0x10;     79 M mulli r24, r26, 0xc;        B mulli r26, r23, 0xc;     80 M addi r30, r30, 2;        B addi r27, r27, 2;     82 M cmpw r25, r24;        B cmpw r25, r26;     86 M li r23, 0;        B li r24, 0;     89 M mr r5, r30;        B mr r5, r27;     92 M addi r30, r30, 0xc;        B addi r27, r27, 0xc;     93 M addi r23, r23, 1;        B addi r24, r24, 1;     94 M clrlwi r0, r23, 0x10;        B clrlwi r0, r24, 0x10;     95 M cmplw r0, r26;        B cmplw r0, r23;     97 M subf r0, r24, r25;        B subf r0, r26, r25;    104 M lbz r3, 1(r30);        B lbz r3, 1(r27);    106 M lbz r4, 2(r30);        B lbz r4, 2(r27);    107 M lbz r5, 0(r30);        B lbz r5, 0(r27);    109 M lbz r0, 3(r30);        B lbz r0, 3(r27);    128 M add r26, r27, r3;        B add r26, r30, r3;    136 M lbz r3, 1(r26);        B lbz r4, 1(r26);    137 M lbz r4, 0(r26);        B lbz r3, 0(r26);    139 M rlwimi r4, r3, 8, 0x10, 0x17;        B rlwimi r3, r4, 8, 0x10, 0x17;    140 M rlwinm r0, r4, 8, 0x10, 0x17;        B rlwinm r0, r3, 8, 0x10, 0x17;    141 M rlwimi r0, r4, 0x18, 0x18, 0x1f;        B rlwimi r0, r3, 0x18, 0x18, 0x1f;    143 M clrlwi r0, r4, 0x10;        B clrlwi r0, r3, 0x10;    144 M clrlwi r30, r0, 0x10;        B clrlwi r27, r0, 0x10;    146 M mulli r0, r30, 0xc;        B mulli r0, r27, 0xc;    162 M cmplw r0, r30;        B cmplw r0, r27;    170 M add r26, r27, r3;        B add r26, r30, r3;    178 M lbz r3, 1(r26);        B lbz r4, 1(r26);    179 M lbz r4, 0(r26);        B lbz r3, 0(r26);    181 M rlwimi r4, r3, 8, 0x10, 0x17;        B rlwimi r3, r4, 8, 0x10, 0x17;    182 M rlwinm r0, r4, 8, 0x10, 0x17;        B rlwinm r0, r3, 8, 0x10, 0x17;    183 M rlwimi r0, r4, 0x18, 0x18, 0x1f;        B rlwimi r0, r3, 0x18, 0x18, 0x1f;    185 M clrlwi r0, r4, 0x10;        B clrlwi r0, r3, 0x10;
- NWC24iSetMsgSubjectBase64: single named buffer capacity half used for split and guard: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored

### NWC24iDateToOSCalendarTime
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x154 base 0x154 insns 85/85; diffs 13: [6, 7, 16, 17, 24, 32, 33, 38, 43, 47, 52, 54, 55];      6 M lhz r0, 0(r4);        B lhz r5, 0(r4);      7 M li r5, 0;        B li r0, 0;     16 M slwi r6, r0, 0x1e;        B slwi r6, r5, 0x1e;     17 M srwi r7, r0, 0x1f;        B srwi r7, r5, 0x1f;     24 M stw r0, 0x14(r3);        B stw r5, 0x14(r3);     32 M stw r5, 0x20(r3);        B stw r0, 0x20(r3);     33 M stw r5, 0x24(r3);        B stw r0, 0x24(r3);     38 M mulhw r7, r7, r0;        B mulhw r7, r7, r5;     43 M subf. r7, r7, r0;        B subf. r7, r7, r5;     47 M mulhw r7, r7, r0;        B mulhw r7, r7, r5;     52 M subf. r0, r7, r0;        B subf. r5, r7, r5;     54 M li r5, 1;        B li r0, 1;     55 M cmpwi r5, 0;        B cmpwi r0, 0;
Structural diagnosis85/85 frame0x10: year versus flag register interchange. Separate year scalar views with signed/unsigned local types and fraction-zero scope.
- NWC24iDateToOSCalendarTime: named u16 year read view for stores and leap test: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- NWC24iDateToOSCalendarTime: named s32 year read view for stores and leap test: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- NWC24iDateToOSCalendarTime: fraction-zero local with nested field initialization scope: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored

### ConvertDateToDays
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x1c4 base 0x1c4 insns 113/113; diffs 16: [94, 95, 96, 97, 99, 100, 101, 103, 104, 105, 106, 107, 108, 109, 110, 111];     94 M addi r5, r6, 0x12b;        B addi r5, r3, -0x7ae1;     95 M addi r3, r3, -0x7ae1;        B addi r0, r6, 0x12b;     96 M addi r0, r6, -1;        B addi r3, r6, -1;     97 M mulhw r5, r3, r5;        B mulhw r0, r5, r0;     99 M srawi r5, r5, 7;        B srawi r0, r0, 7;    100 M mulhw r3, r3, r0;        B srwi r6, r0, 0x1f;    101 M srwi r6, r5, 0x1f;        B mulhw r5, r5, r3;    103 M add r5, r5, r6;        B add r0, r0, r6;    104 M add r4, r4, r5;        B add r0, r4, r0;    105 M srawi r3, r3, 5;        B srawi r4, r5, 5;    106 M srwi r5, r3, 0x1f;        B srwi r5, r4, 0x1f;    107 M srawi r0, r0, 2;        B srawi r3, r3, 2;    108 M add r3, r3, r5;        B add r4, r4, r5;    109 M addze r0, r0;        B addze r3, r3;    110 M subf r0, r3, r0;        B subf r3, r4, r3;    111 M add r3, r4, r0;        B add r3, r3, r0;
Structural diagnosis113/113 leaf; final accumulated-day/division order differs. Try combined year contribution, staged subtractions and quotient helper boundaries.
- ConvertDateToDays: combined whole-year and century contribution: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored
- ConvertDateToDays: staged common quarter and century subtraction: ((4, 16), 113, 113) -> ((13, 16), 113, 113); restored
- ConvertDateToDays: local century-offset numerator: ((4, 16), 113, 113) -> ((4, 16), 113, 113); restored

### ConvertDaysToDate
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x19c base 0x19c insns 103/103; diffs 26: [53, 55, 57, 60, 61, 62, 63, 64, 65, 67, 68, 69, 70, 71, 72, 73, 75, 76, 77, 78];     53 M lis r12, 0x51ec;        B lis r11, 0x51ec;     55 M lbz r8, 0(r4);        B lbz r0, 0(r4);     57 M cmplwi r8, 2;        B cmplwi r0, 2;     60 M li r0, 0;        B li r12, 0;     61 M slwi r10, r31, 0x1e;        B slwi r8, r31, 0x1e;     62 M srwi r11, r31, 0x1f;        B srwi r10, r31, 0x1f;     63 M subf r10, r11, r10;        B subf r8, r10, r8;     64 M rotlwi r10, r10, 2;        B rotlwi r8, r8, 2;     65 M add. r10, r10, r11;        B add. r8, r8, r10;     67 M addi r10, r12, -0x7ae1;        B addi r8, r11, -0x7ae1;     68 M mulhw r10, r10, r31;        B mulhw r8, r8, r31;     69 M srawi r10, r10, 5;        B srawi r8, r8, 5;     70 M srwi r11, r10, 0x1f;        B srwi r10, r8, 0x1f;     71 M add r10, r10, r11;        B add r8, r8, r10;     72 M mulli r10, r10, 0x64;        B mulli r8, r8, 0x64;     73 M subf. r10, r10, r31;        B subf. r8, r8, r31;     75 M addi r10, r12, -0x7ae1;        B addi r8, r11, -0x7ae1;     76 M mulhw r10, r10, r31;        B mulhw r8, r8, r31;     77 M srawi r10, r10, 7;        B srawi r8, r8, 7;     78 M srwi r11, r10, 0x1f;        B srwi r10, r8, 0x1f;     79 M add r10, r10, r11;        B add r8, r8, r10;     80 M mulli r10, r10, 0x190;        B mulli r8, r8, 0x190;     81 M subf. r10, r10, r31;        B subf. r8, r8, r31;     83 M li r0, 1;        B li r12, 1;     84 M cmpwi r0, 0;        B cmpwi r12, 0;     88 M add r8, r9, r8;        B add r8, r9, r0;
Structural diagnosis103/103 frame0x10: year loop exact; month-loop scalar/leap registers differ. Test read-only month view, year helper const view and scoped table-length local.
- ConvertDaysToDate: const month view declared in month loop: ((0, 26), 103, 103) -> ((0, 6), 103, 103); kept
- ConvertDaysToDate: signed month length used for table subtraction: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- ConvertDaysToDate: leap helper receives pointer to const year: ((0, 6), 103, 103) -> ((0, 27), 103, 103); restored
- ConvertDaysToDate: register-only declaration search after structural attempts ((0, 6), 103, 103) -> ((0, 6), 103, 103); order was:
Structural diagnosis:212/212 frame0x30, all branches/loops identical; helper two-byte assemble operand order and pointer/count/index allocation differ. Audit helpers first.
- TMCJPEGDEC_exif_parse: readExifU16 high-byte operand before low-byte operand: ((0, 46), 212, 212) -> ((0, 46), 212, 212); restored
- TMCJPEGDEC_exif_parse: mutable input view for entry pointer alias analysis: ((0, 46), 212, 212) -> ((0, 46), 212, 212); restored
- TMCJPEGDEC_exif_parse: IFD byte extent explicitly signed multiplicand: ((0, 46), 212, 212) -> ((0, 46), 212, 212); restored
- TMCJPEGDEC_exif_parse: register-only declaration search after structural attempts ((0, 46), 212, 212) -> ((0, 43), 212, 212); (0, 43) after 70 builds; kept in source:

### AOSSi_WLANGetBSSList
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x38c base 0x38c insns 227/227; diffs 202: [9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28];      9 M li r15, 0;        B mr r19, r3;     10 M mr r17, r3;        B li r17, -1;     11 M li r16, -1;        B li r18, 0;     12 M cmplw r0, r15;        B cmpwi r0, 0;     13 M li r18, 0;        B li r23, 0;     14 M li r26, 0;        B li r21, 0;     15 M li r25, 0;        B li r20, 0;     16 M beq 20;        B beq 16;     17 M lwz r3, 0(0);        B lwz r0, 0(0);     18 M li r0, 0;        B cmpwi r0, 0;     19 M cmplw r3, r0;        B bne 12;     20 M bne 12;        B li r3, -1;     21 M li r3, -1;        B b 796;     22 M b 792;        B bl 0;     23 M bl 0;        B cmpwi r3, 0;     24 M cmpwi r3, 0;        B mr r25, r3;     25 M mr r24, r3;        B bgt 12;     26 M bgt 12;        B li r3, -1;     27 M li r3, -1;        B b 772;     28 M b 768;        B li r3, 3;     29 M li r3, 3;        B bl 0;     30 M bl 0;        B cmpwi r3, 0;     31 M cmpwi r3, 0;        B beq 28;     32 M beq 28;        B cmpwi r18, 0xa;     33 M cmpwi r15, 0xa;        B bgt 728;     34 M bgt 692;        B li r3, 0xa;     35 M li r3, 0xa;        B addi r18, r18, 1;     36 M addi r15, r15, 1;        B bl 0;     37 M bl 0;        B b -36;     38 M b -36;        B addi r3, r1, 0xa0;     39 M addi r3, r1, 0x80;        B bl 0;     40 M bl 0;        B cmpwi r3, 0;     41 M cmpwi r3, 0;        B bne 20;     42 M bne 20;        B addi r3, r1, 0x20;     43 M addi r3, r1, 0x20;        B addi r4, r1, 0xa0;     44 M addi r4, r1, 0x80;        B li r5, 6;     45 M li r5, 6;        B bl 0;     46 M bl 0;        B li r3, 0x3200;     47 M li r3, 0x3200;        B bl 0;     48 M bl 0;        B cmpwi r3, 0;     49 M li r15, 0;        B mr r24, r3;     50 M mr r23, r3;        B beq 616;     51 M cmplw r3, r15;        B li r4, 0;     52 M beq 576;        B li r5, 0x3200;     53 M li r4, 0;        B bl 0;     54 M li r5, 0x3200;        B lhz r5, 0xa6(r1);     55 M bl 0;        B li r0, 0x28;     56 M lhz r6, 0x86(r1);        B sth r0, 0x42(r1);     57 M li r0, 0x28;        B addi r3, r1, 0x44;     58 M sth r0, 0x28(r1);        B li r4, 0xff;     59 M addi r3, r1, 0x2a;        B sth r5, 0x40(r1);     60 M li r4, 0xff;        B li r5, 6;     61 M li r5, 6;        B bl 0;     62 M sth r6, 0x26(r1);        B li r0, 0;     63 M bl 0;        B addi r3, r1, 0x4e;     64 M sth r15, 0x30(r1);        B sth r0, 0x4a(r1);     65 M addi r3, r1, 0x34;        B li r4, 0;     66 M li r4, 0;        B li r5, 0x20;     67 M li r5, 0x20;        B sth r0, 0x4c(r1);     68 M sth r15, 0x32(r1);        B bl 0;     69 M bl 0;        B addi r3, r1, 0x6e;     70 M addi r3, r1, 0x54;        B li r4, 0xff;     71 M li r4, 0xff;        B li r5, 0x20;     72 M li r5, 0x20;        B bl 0;     73 M bl 0;        B mr r4, r24;     74 M mr r4, r23;        B addi r3, r1, 0x40;     75 M addi r3, r1, 0x26;        B li r5, 0x3200;     76 M li r5, 0x3200;        B bl 0;     77 M bl 0;        B cmpwi r3, 0;     78 M cmpwi r3, 0;        B beq 16;     79 M beq 16;        B addis r0, r3, -0x8000;     80 M addis r0, r3, -0x8000;        B cmplwi r0, 0x8004;     81 M cmplwi r0, 0x8004;        B bne 428;     82 M bne 420;        B lhz r22, 0(r24);     83 M lhz r22, 0(r23);        B cmpwi r22, 0;     84 M cmpwi r22, 0;        B beq 328;     85 M beq 320;        B addi r0, r22, -1;     86 M addi r0, r22, -1;        B mulli r3, r0, 0x54;     87 M mulli r3, r0, 0x50;        B addi r3, r3, 0x58;     88 M addi r3, r3, 0x54;        B bl 0;     89 M bl 0;        B cmpwi r3, 0;     90 M li r28, 0;        B mr r27, r3;     91 M mr r27, r3;        B bne 12;     92 M cmplw r3, r28;        B li r17, -1;     93 M bne 12;        B b 380;     94 M li r16, -1;        B lis r28, 0;     95 M b 368;        B stw r22, 0(r3);     96 M lis r29, 0;        B addi r23, r24, 2;     97 M stw r22, 0(r3);        B li r26, 0;     98 M addi r21, r23, 2;        B addi r28, r28, 0;     99 M li r20, 0;        B li r17, 0;    100 M addi r29, r29, 0;        B li r31, 0;    101 M li r15, 0;        B li r30, 2;    102 M li r31, 2;        B li r29, 1;    103 M li r30, 1;        B li r18, 0xc;    104 M li r16, 0xc;        B b 228;    105 M b 220;        B lhz r0, 0xa(r23);    106 M lhz r0, 0xa(r21);        B add r5, r27, r17;    107 M add r3, r27, r15;        B addi r3, r5, 8;    108 M addi r19, r3, 4;        B addi r4, r23, 0xc;    109 M addi r4, r21, 0xc;        B stw r0, 4(r5);    110 M stw r0, 4(r3);        B li r5, 0x20;    111 M addi r3, r19, 4;        B bl 0;    112 M li r18, 0;        B lhz r0, 0x36(r23);    113 M li r5, 0x20;        B add r5, r27, r17;    114 M bl 0;        B addi r3, r5, 0x34;    115 M lhz r0, 0x36(r21);        B addi r4, r23, 4;    116 M addi r3, r19, 0x30;        B stw r0, 0x28(r5);    117 M addi r4, r21, 4;        B li r5, 6;    118 M li r5, 6;        B bl 0;    119 M stw r0, 0x24(r19);        B add r7, r27, r17;    120 M bl 0;        B li r3, 0;    121 M li r3, 0;        B li r4, 0;    122 M mtctr r16;        B mtctr r18;    123 M lhz r4, 0x30(r21);        B lhz r5, 0x30(r23);    124 M lhzx r0, r29, r3;        B lhzx r0, r28, r4;    125 M and. r0, r4, r0;        B and. r0, r5, r0;    127 M add r4, r29, r3;        B add r5, r28, r4;    128 M add r5, r19, r18;        B add r6, r7, r3;    129 M lbz r0, 2(r4);        B lbz r0, 2(r5);    130 M stb r0, 0x3c(r5);        B stb r0, 0x40(r6);    131 M lhz r4, 0x2e(r21);        B lhz r5, 0x2e(r23);    132 M lhzx r0, r29, r3;        B lhzx r0, r28, r4;    133 M and. r0, r4, r0;        B and. r0, r5, r0;    135 M lbz r0, 0x3c(r5);        B lbz r0, 0x40(r6);    137 M stb r0, 0x3c(r5);        B stb r0, 0x40(r6);    138 M addi r18, r18, 1;        B addi r3, r3, 1;    139 M addi r3, r3, 4;        B addi r4, r4, 4;    141 M stw r18, 0x38(r19);        B add r4, r27, r17;    142 M lhz r0, 0x32(r21);        B stw r3, 0x3c(r4);    143 M stw r0, 0x48(r19);        B lhz r0, 0x32(r23);    144 M lhz r0, 0x2c(r21);        B stw r0, 0x50(r4);    145 M clrlwi r0, r0, 0x1e;        B lhz r0, 0x2c(r23);    146 M cmpwi r0, 1;        B clrlwi r0, r0, 0x1e;    147 M bne 12;        B cmpwi r0, 1;    148 M stw r30, 0x4c(r19);        B bne 12;    149 M b 24;        B stw r29, 0x54(r4);    150 M cmpwi r0, 2;        B b 24;    151 M bne 12;        B cmpwi r0, 2;    152 M stw r31, 0x4c(r19);        B bne 12;    153 M b 8;        B stw r30, 0x54(r4);    154 M stw r28, 0x4c(r19);        B b 8;    155 M lhz r0, 0(r21);        B stw r31, 0x54(r4);    156 M addi r20, r20, 1;        B lhz r0, 0(r23);    157 M addi r15, r15, 0x50;        B addi r26, r26, 1;    158 M slwi r0, r0, 1;        B addi r17, r17, 0x54;    159 M add r21, r21, r0;        B slwi r0, r0, 1;    160 M cmpw r20, r22;        B add r23, r23, r0;    161 M blt -220;        B cmpw r26, r22;    162 M stw r27, 0(r17);        B blt -228;    163 M li r16, 0;        B stw r27, 0(r19);    164 M b 92;        B li r17, 0;    165 M lwz r0, 0(0);        B b 92;    166 M cmpwi r0, 1;        B lwz r0, 0(0);    167 M bne 12;        B cmpwi r0, 1;    168 M li r16, -1;        B bne 12;    169 M b 72;        B li r17, -1;    170 M addi r18, r18, 1;        B b 72;    171 M cmpwi r18, 0xa;        B addi r23, r23, 1;    172 M ble 48;        B cmpwi r23, 0xa;    173 M li r3, 0x54;        B ble 48;    174 M bl 0;        B li r3, 0x58;    175 M li r0, 0;        B bl 0;    176 M cmplw r3, r0;        B cmpwi r3, 0;    178 M li r16, -1;        B li r17, -1;    179 M b 32;        B b 36;    180 M stw r0, 0(r3);        B li r0, 0;    181 M li r16, 0;        B li r17, 0;    182 M stw r3, 0(r17);        B stw r0, 0(r3);    183 M b 16;        B stw r3, 0(r19);    184 M li r3, 0x64;        B b 16;    185 M bl 0;        B li r3, 0x64;    186 M b -448;        B bl 0;    187 M lwz r12, 0(0);        B b -456;    188 M li r0, 0;        B lwz r12, 0(0);    189 M cmplw r12, r0;        B cmpwi r12, 0;    190 M beq 24;        B beq 56;    191 M mr r4, r23;        B mr r4, r24;    196 M bl 0;        B b 32;    197 M cmpwi r3, 0;        B cmpwi r21, 0xa;    198 M beq 36;        B ble 12;    199 M cmpwi r26, 0xa;        B li r17, -1;    200 M ble 12;        B b 60;    201 M li r16, -1;        B li r3, 0xa;    202 M b 20;        B addi r21, r21, 1;    203 M li r3, 0xa;        B bl 0;    204 M addi r26, r26, 1;        B bl 0;    205 M bl 0;        B cmpwi r3, 0;    206 M b -40;        B bne -36;    207 M mr r3, r24;        B b 32;    208 M bl 0;        B cmpwi r20, 0xa;    209 M cmpwi r3, 0;        B ble 12;    210 M beq 36;        B li r17, -1;    211 M cmpwi r25, 0xa;        B b 32;    212 M ble 12;        B li r3, 0xa;    213 M li r3, -1;        B addi r20, r20, 1;    214 M b 24;        B bl 0;    215 M li r3, 0xa;        B mr r3, r25;    216 M addi r25, r25, 1;        B bl 0;    217 M bl 0;        B cmpwi r3, 0;    218 M b -44;        B bne -40;    219 M mr r3, r16;        B mr r3, r17;

### AOSSi_WLANConnect
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x270 base 0x26c insns 156/155; --- replace mine 8:11 base 8:11;   M    8 lis r29, 0;   M    9 mr r28, r4;   M   10 addi r29, r29, 0;   B    8 lis r30, 0;   B    9 mr r29, r4;   B   10 addi r30, r30, 0; --- replace mine 12:13 base 12:13;   M   12 mr r3, r29;   B   12 mr r3, r30; --- delete mine 14:15 base 14:14;   M   14 li r30, 0; --- replace mine 20:23 base 19:22;   M   20 stb r0, 0(r29);   M   21 sth r3, 2(r29);   M   22 stb r3, 4(r29);   B   19 stb r0, 0(r30);   B   20 sth r3, 2(r30);   B   21 stb r3, 4(r30); --- replace mine 26:27 base 25:26;   M   26 sth r3, 0x2a(r29);   B   25 sth r3, 0x2a(r30); --- replace mine 32:34 base 31:33;   M   32 sth r3, 0x2a(r29);   M   33 addi r3, r29, 0x32;   B   31 sth r3, 0x2a(r30);   B   32 addi r3, r30, 0x32; --- replace mine 35:36 base 34:35;   M   35 sth r0, 0x2e(r29);   B   34 sth r0, 0x2e(r30); --- replace mine 43:45 base 42:44;   M   43 sth r3, 0x2a(r29);   M   44 addi r3, r29, 0x32;   B   42 sth r3, 0x2a(r30);   B   43 addi r3, r30, 0x32; --- replace mine 46:47 base 45:46;   M   46 sth r0, 0x2e(r29);   B   45 sth r0, 0x2e(r30); --- replace mine 57:58 base 56:57;   M   57 addi r3, r29, 6;   B   56 addi r3, r30, 6; --- replace mine 60:61 base 59:60;   M   60 sth r0, 0x26(r29);   B   59 sth r0, 0x26(r30); --- insert mine 64:64 base 63:65;   B   63 li r28, 0;   B   64 addi r27, r27, 0; --- delete mine 65:66 base 66:66;   M   65 addi r27, r27, 0; --- replace mine 102:104 base 102:104;   M  102 li r30, -1;   M  103 cmpwi r30, 0;   B  102 li r28, -1;   B  103 cmpwi r28, 0; --- replace mine 110:112 base 110:112;   M  110 li r30, -1;   M  111 cmpwi r30, 0;   B  110 li r28, -1;   B  111 cmpwi r28, 0; --- replace mine 117:118 base 117:118;   M  117 li r30, -1;   B  117 li r28, -1; --- replace mine 121:122 base 121:122;   M  121 li r30, -1;   B  121 li r28, -1; --- replace mine 129:131 base 129:131;   M  129 cmpwi r30, 0;   M  130 bne 64;   B  129 cmpwi r28, 0;   B  130 bne 60; --- replace mine 133:134 base 133:134;   M  133 stw r0, 0(r28);   B  133 stw r0, 0(r29); --- replace mine 138:144 base 138:143;   M  138 stw r0, 0x28(r28);   M  139 lhz r0, 0x26(r29);   M  140 addi r3, r28, 8;   M  141 addi r4, r29, 6;   M  142 stw r0, 4(r28);   M  143 lhz r5, 0x26(r29);   B  138 stw r0, 0x28(r29);   B  139 lhz r5, 0x26(r30);   B  140 addi r3, r29, 8;   B  141 addi r4, r30, 6;   B  142 stw r5, 4(r29); --- replace mine 147:149 base 146:148;   M  147 stw r0, 0(r28);   M  148 mr r3, r30;   B  146 stw r0, 0(r29);   B  147 mr r3, r28;

### clearCandidates__Q39textinput8tistring6WithZiFv
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x150 base 0x144 insns 84/81; --- insert mine 4:4 base 4:6;   B    4 lis r31, 0;   B    5 addi r31, r31, 0; --- replace mine 6:10 base 8:9;   M    6 lis r29, 0;   M    7 addi r29, r29, 0;   M    8 stw r28, 0x10(r1);   M    9 mr r28, r3;   B    8 mr r29, r3; --- replace mine 12:13 base 11:12;   M   12 beq 256;   B   11 beq 252; --- replace mine 18:19 base 17:18;   M   18 addi r3, r29, 0;   B   17 addi r3, r31, 0; --- replace mine 20:21 base 19:20;   M   20 addi r3, r29, 0x200;   B   19 addi r3, r31, 0x200; --- replace mine 24:25 base 23:24;   M   24 addi r31, r29, 0x200;   B   23 addi r3, r31, 0x400; --- delete mine 26:27 base 25:25;   M   26 addi r3, r31, 0x200; --- replace mine 29:30 base 27:28;   M   29 addi r3, r31, 0x400;   B   27 addi r3, r31, 0x600; --- replace mine 33:34 base 31:32;   M   33 addi r3, r29, 0x800;   B   31 addi r3, r31, 0x800; --- replace mine 37:38 base 35:36;   M   37 addi r3, r28, 0x4c;   B   35 addi r3, r29, 0x4c; --- replace mine 41:43 base 39:41;   M   41 lwz r12, 0(r28);   M   42 mr r3, r28;   B   39 lwz r12, 0(r29);   B   40 mr r3, r29; --- replace mine 46:48 base 44:46;   M   46 addi r4, r31, 0x400;   M   47 addi r5, r29, 0;   B   44 addi r5, r31, 0;   B   45 addi r4, r31, 0x600; --- replace mine 52:64 base 50:62;   M   52 stb r3, 0x4c(r28);   M   53 mr r3, r28;   M   54 stb r7, 0x4e(r28);   M   55 stb r30, 0x4d(r28);   M   56 stb r31, 0x4f(r28);   M   57 stb r6, 0x50(r28);   M   58 stw r5, 0x54(r28);   M   59 stw r4, 0x64(r28);   M   60 stb r0, 0x68(r28);   M   61 stb r30, 0x58(r28);   M   62 sth r30, 0x6a(r28);   M   63 lwz r12, 0(r28);   B   50 stb r3, 0x4c(r29);   B   51 mr r3, r29;   B   52 stb r7, 0x4e(r29);   B   53 stb r30, 0x4d(r29);   B   54 stb r31, 0x4f(r29);   B   55 stb r6, 0x50(r29);   B   56 stw r5, 0x54(r29);   B   57 stw r4, 0x64(r29);   B   58 stb r0, 0x68(r29);   B   59 stb r30, 0x58(r29);   B   60 sth r30, 0x6a(r29);   B   61 lwz r12, 0(r29); --- replace mine 71:75 base 69:73;   M   71 stb r31, 0x4d(r28);   M   72 stb r0, 0x4f(r28);   M   73 lwz r4, 0x84(r28);   M   74 addi r3, r28, 0x4c;   B   69 stb r31, 0x4d(r29);   B   70 stb r0, 0x4f(r29);   B   71 lwz r4, 0x84(r29);   B   72 addi r3, r29, 0x4c; --- delete mine 80:81 base 78:78;   M   80 lwz r28, 0x10(r1);

### update__Q39textinput8tistring6WithZiFv
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x6fc base 0x6f8 insns 447/446; --- replace mine 7:8 base 7:8;   M    7 mr r27, r3;   B    7 mr r28, r3; --- replace mine 10:15 base 10:13;   M   10 beq 1724;   M   11 li r28, 0;   M   12 addi r4, r31, 0x200;   M   13 stw r28, 0x98(r3);   M   14 addi r30, r4, 0x400;   B   10 beq 1720;   B   11 li r30, 0;   B   12 stw r30, 0x98(r3); --- replace mine 19:20 base 17:18;   M   19 lwz r12, 0(r27);   B   17 lwz r12, 0(r28); --- replace mine 21:22 base 19:20;   M   21 mr r3, r27;   B   19 mr r3, r28; --- replace mine 25:29 base 23:28;   M   25 addi r4, r31, 0;   M   26 li r6, 7;   M   27 li r26, 1;   M   28 li r5, 0x81;   B   23 addi r5, r31, 0;   B   24 addi r4, r31, 0x600;   B   25 li r7, 7;   B   26 li r27, 1;   B   27 li r6, 0x81; --- replace mine 30:48 base 29:47;   M   30 stb r3, 0x4c(r27);   M   31 mr r3, r27;   M   32 stb r6, 0x4e(r27);   M   33 stb r28, 0x4d(r27);   M   34 stb r26, 0x4f(r27);   M   35 stb r5, 0x50(r27);   M   36 stw r4, 0x54(r27);   M   37 stw r30, 0x64(r27);   M   38 stb r0, 0x68(r27);   M   39 stb r29, 0x58(r27);   M   40 sth r28, 0x6a(r27);   M   41 stw r28, 0x5c(r27);   M   42 stb r28, 0x60(r27);   M   43 stb r28, 0x6c(r27);   M   44 stb r28, 0x6d(r27);   M   45 stb r28, 0x6e(r27);   M   46 stw r28, 0x70(r27);   M   47 lwz r12, 0(r27);   B   29 stb r3, 0x4c(r28);   B   30 mr r3, r28;   B   31 stb r7, 0x4e(r28);   B   32 stb r30, 0x4d(r28);   B   33 stb r27, 0x4f(r28);   B   34 stb r6, 0x50(r28);   B   35 stw r5, 0x54(r28);   B   36 stw r4, 0x64(r28);   B   37 stb r0, 0x68(r28);   B   38 stb r29, 0x58(r28);   B   39 sth r30, 0x6a(r28);   B   40 stw r30, 0x5c(r28);   B   41 stb r30, 0x60(r28);   B   42 stb r30, 0x6c(r28);   B   43 stb r30, 0x6d(r28);   B   44 stb r30, 0x6e(r28);   B   45 stw r30, 0x70(r28);   B   46 lwz r12, 0(r28); --- replace mine 54:55 base 53:54;   M   54 lbz r0, 0xa8(r27);   B   53 lbz r0, 0xa8(r28); --- replace mine 56:57 base 55:56;   M   56 stb r26, 0x4d(r27);   B   55 stb r27, 0x4d(r28); --- replace mine 58:59 base 57:58;   M   58 stb r3, 0x4f(r27);   B   57 stb r3, 0x4f(r28); --- replace mine 60:61 base 59:60;   M   60 lbz r0, 0x50(r27);   B   59 lbz r0, 0x50(r28); --- replace mine 62:63 base 61:62;   M   62 stb r3, 0x4f(r27);   B   61 stb r3, 0x4f(r28); --- replace mine 64:65 base 63:64;   M   64 stb r0, 0x50(r27);   B   63 stb r0, 0x50(r28); --- replace mine 66:67 base 65:66;   M   66 stw r3, 0x5c(r27);   B   65 stw r3, 0x5c(r28); --- replace mine 68:69 base 67:68;   M   68 stb r3, 0x60(r27);   B   67 stb r3, 0x60(r28); --- replace mine 71:72 base 70:71;   M   71 lbz r0, 0x60(r27);   B   70 lbz r0, 0x60(r28); --- replace mine 74:76 base 73:75;   M   74 lwz r12, 0(r27);   M   75 mr r3, r27;   B   73 lwz r12, 0(r28);   B   74 mr r3, r28; --- replace mine 87:88 base 86:87;   M   87 lwz r0, 0xa4(r27);   B   86 lwz r0, 0xa4(r28); --- replace mine 90:92 base 89:91;   M   90 lwz r12, 0(r27);   M   91 mr r3, r27;   B   89 lwz r12, 0(r28);   B   90 mr r3, r28; --- replace mine 108:109 base 107:108;   M  108 stw r3, 0x8c(r27);   B  107 stw r3, 0x8c(r28); --- replace mine 110:111 base 109:110;   M  110 lwz r0, 0xa4(r27);   B  109 lwz r0, 0xa4(r28); --- replace mine 117:118 base 116:117;   M  117 lwz r3, 0x8c(r27);   B  116 lwz r3, 0x8c(r28); --- replace mine 119:121 base 118:120;   M  119 stw r0, 0x8c(r27);   M  120 lwz r0, 0xa4(r27);   B  118 stw r0, 0x8c(r28);   B  119 lwz r0, 0xa4(r28); --- replace mine 128:129 base 127:128;   M  128 lwz r3, 0x8c(r27);   B  127 lwz r3, 0x8c(r28); --- replace mine 130:132 base 129:131;   M  130 stw r0, 0x8c(r27);   M  131 lwz r0, 0xa4(r27);   B  129 stw r0, 0x8c(r28);   B  130 lwz r0, 0xa4(r28); --- replace mine 139:140 base 138:139;   M  139 lwz r3, 0x8c(r27);   B  138 lwz r3, 0x8c(r28); --- replace mine 141:143 base 140:142;   M  141 stw r0, 0x8c(r27);   M  142 lwz r0, 0xa4(r27);   B  140 stw r0, 0x8c(r28);   B  141 lwz r0, 0xa4(r28); --- replace mine 150:151 base 149:150;   M  150 lwz r3, 0x8c(r27);   B  149 lwz r3, 0x8c(r28); --- replace mine 152:154 base 151:153;   M  152 stw r0, 0x8c(r27);   M  153 lwz r0, 0xa4(r27);   B  151 stw r0, 0x8c(r28);   B  152 lwz r0, 0xa4(r28); --- replace mine 161:162 base 160:161;   M  161 lwz r3, 0x8c(r27);   B  160 lwz r3, 0x8c(r28); --- replace mine 163:164 base 162:164;   M  163 stw r0, 0x8c(r27);   B  162 stw r0, 0x8c(r28);   B  163 addi r4, r4, 2; --- delete mine 165:166 base 165:165;   M  165 addi r4, r4, 2; --- replace mine 168:170 base 167:169;   M  168 lwz r4, 0x84(r27);   M  169 addi r3, r27, 0x4c;   B  167 lwz r4, 0x84(r28);   B  168 addi r3, r28, 0x4c; --- replace mine 172:173 base 171:173;   M  172 addi r26, r31, 0x200;   B  171 addi r3, r31, 0x600;   B  172 addi r4, r31, 0x200; --- delete mine 174:176 base 174:174;   M  174 mr r4, r26;   M  175 addi r3, r26, 0x400; --- replace mine 177:179 base 175:177;   M  177 lwz r12, 0(r27);   M  178 mr r3, r27;   B  175 lwz r12, 0(r28);   B  176 mr r3, r28; --- replace mine 182:183 base 180:181;   M  182 lwz r12, 0(r27);   B  180 lwz r12, 0(r28); --- replace mine 184:185 base 182:183;   M  184 mr r3, r27;   B  182 mr r3, r28; --- replace mine 189:191 base 187:189;   M  189 lwz r4, 0x84(r27);   M  190 addi r3, r27, 0x4c;   B  187 lwz r4, 0x84(r28);   B  188 addi r3, r28, 0x4c; --- replace mine 192:195 base 190:349;   M  192 lwz r12, 0(r27);   M  193 clrlwi r28, r3, 0x18;   M  194 mr r3, r27;   B  190 lwz r12, 0(r28);   B  191 clrlwi r30, r3, 0x18;   B  192 mr r3, r28;   B  193 lwz r12, 0x104(r12);   B  194 mtctr r12;   B  195 bctrl ;   B  196 clrlwi r0, r3, 0x18;   B  197 cmplwi r0, 1;   B  198 bne 72;   B  199 cmplwi r30, 0x61;   B  200 bne 64;   B  201 addi r27, r31, 0x600;   B  202 li r3, 0x61;   B  203 addi r5, r27, 0x184;   B  204 li r0, 0xc7;   B  205 sth r3, 0x6a(r28);   B  206 addi r3, r28, 0x4c;   B  207 lwz r4, 0x84(r28);   B  208 stw r5, 0x64(r28);   B  209 stb r0, 0x68(r28);   B  210 bl 0;   B  211 li r0, 0;   B  212 clrlwi r3, r3, 0x18;   B  213 sth r0, 0x6a(r28);   B  214 add r30, r30, r3;   B  215 stw r27, 0x64(r28);   B  216 cmpwi r30, 0x28;   B  217 ble 8;   B  218 li r30, 0x28;   B  219 lwz r12, 0(r28);   B  220 mr r3, r28;   B  221 lwz r12, 0x104(r12);   B  222 mtctr r12;   B  223 bctrl ;   B  224 clrlwi r0, r3, 0x18;   B  225 cmplwi r0, 1;   B  226 bne 300;   B  227 lbz r0, 0x79(r28);   B  228 cmpwi r0, 0;   B  229 beq 288;   B  230 lbz r0, 0x6c(r28);   B  231 li r3, 0;   B  232 stb r3, 0x79(r28);   B  233 cmpwi r0, 0;   B  234 bne 268;   B  235 lwz r30, 0x7c(r28);   B  236 addi r3, r31, 0x1c00;   B  237 bl 0;   B  238 cmpwi r30, 0;   B  239 clrlwi r4, r3, 0x18;   B  240 li r5, 0;   B  241 beq 200;   B  242 cmplwi r30, 8;   B  243 addi r6, r30, -8;   B  244 ble 120;   B  245 subf r3, r30, r4;   B  246 addi r0, r6, 7;   B  247 addi r7, r31, 0x1c00;   B  248 slwi r3, r3, 1;   B  249 srwi r0, r0, 3;   B  250 add r3, r7, r3;   B  251 mtctr r0;   B  252 cmplwi r6, 0;   B  253 ble 84;   B  254 lhz r0, 0(r3);   B  255 addi r5, r5, 8;   B  256 sth r0, 0(r7);   B  257 lhz r0, 2(r3);   B  258 sth r0, 2(r7);   B  259 lhz r0, 4(r3);   B  260 sth r0, 4(r7);   B  261 lhz r0, 6(r3);   B  262 sth r0, 6(r7);   B  263 lhz r0, 8(r3);   B  264 sth r0, 8(r7);   B  265 lhz r0, 0xa(r3);   B  266 sth r0, 0xa(r7);   B  267 lhz r0, 0xc(r3);   B  268 sth r0, 0xc(r7);   B  269 lhz r0, 0xe(r3);   B  270 addi r3, r3, 0x10;   B  271 sth r0, 0xe(r7);   B  272 addi r7, r7, 0x10;   B  273 bdnz -76;   B  274 subf r0, r30, r4;   B  275 slwi r6, r5, 1;   B  276 slwi r0, r0, 1;   B  277 addi r4, r31, 0x1c00;   B  278 add r3, r6, r0;   B  279 add r3, r4, r3;   B  280 subf r0, r5, r30;   B  281 add r4, r4, r6;   B  282 mtctr r0;   B  283 cmplw r5, r30;   B  284 bge 28;   B  285 lhz r0, 0(r3);   B  286 addi r3, r3, 2;   B  287 addi r5, r5, 1;   B  288 sth r0, 0(r4);   B  289 addi r4, r4, 2;   B  290 bdnz -20;   B  291 addi r3, r31, 0x1c00;   B  292 slwi r0, r5, 1;   B  293 li r4, 0;   B  294 sthx r4, r3, r0;   B  295 bl 0;   B  296 stb r3, 0x60(r28);   B  297 addi r3, r28, 0x4c;   B  298 lwz r4, 0x84(r28);   B  299 bl 0;   B  300 clrlwi r30, r3, 0x18;   B  301 cmpwi r30, 0;   B  302 bne 116;   B  303 lwz r12, 0(r28);   B  304 mr r3, r28;   B  305 lwz r12, 0x104(r12);   B  306 mtctr r12;   B  307 bctrl ;   B  308 clrlwi r0, r3, 0x18;   B  309 cmplwi r0, 1;   B  310 beq 76;   B  311 lwz r12, 0(r28);   B  312 mr r3, r28;   B  313 lwz r12, 0x104(r12);   B  314 mtctr r12;   B  315 bctrl ;   B  316 clrlwi r0, r3, 0x18;   B  317 cmplwi r0, 0x12;   B  318 bne 28;   B  319 lwz r12, 0(r28);   B  320 mr r3, r28;   B  321 lwz r12, 0x5c(r12);   B  322 mtctr r12;   B  323 bctrl ;   B  324 b 464;   B  325 mr r3, r28;   B  326 mr r4, r29;   B  327 bl 0;   B  328 mr r30, r3;   B  329 cmpwi r30, 0;   B  330 beq 440;   B  331 addi r3, r31, 0x800;   B  332 li r4, 0;   B  333 li r5, 0x1400;   B  334 bl 0;   B  335 li r0, 0;   B  336 cmpwi r29, 0;   B  337 stw r0, 0x8c(r28);   B  338 bne 16;   B  339 lbz r0, 0x60(r28);   B  340 cmpwi r0, 0;   B  341 beq 396;   B  342 lwz r29, 0x64(r28);   B  343 addi r26, r31, 0x800;   B  344 li r31, 0;   B  345 li r27, 0;   B  346 b 368;   B  347 lwz r12, 0(r28);   B  348 mr r3, r28; --- replace mine 201:287 base 355:358;   M  201 cmplwi r28, 0x61;   M  202 bne 60;   M  203 addi r5, r26, 0x584;   M  204 li r3, 0x61;   M  205 li r0, 0xc7;   M  206 sth r3, 0x6a(r27);   M  207 lwz r4, 0x84(r27);   M  208 addi r3, r27, 0x4c;   M  209 stw r5, 0x64(r27);   M  210 stb r0, 0x68(r27);   M  211 bl 0;   M  212 li r0, 0;   M  213 clrlwi r3, r3, 0x18;   M  214 sth r0, 0x6a(r27);   M  215 addi r28, r3, 0x61;   M  216 stw r30, 0x64(r27);   M  217 cmpwi r28, 0x28;   M  218 ble 8;   M  219 li r28, 0x28;   M  220 lwz r12, 0(r27);   M  221 mr r3, r27;   M  222 lwz r12, 0x104(r12);   M  223 mtctr r12;   M  224 bctrl ;   M  225 clrlwi r0, r3, 0x18;   M  226 cmplwi r0, 1;   M  227 bne 292;   M  228 lbz r0, 0x79(r27);   M  229 cmpwi r0, 0;   M  230 beq 280;   M  231 lbz r0, 0x60(r27);   M  232 li r3, 0;   M  233 stb r3, 0x79(r27);   M  234 cmpwi r0, 0;   M  235 bne 260;   M  236 lwz r28, 0x7c(r27);   M  237 addi r3, r31, 0x1c00;   M  238 bl 0;   M  239 rlwinm r0, r3, 1, 0x17, 0x1e;   M  240 addi r5, r31, 0x1c00;   M  241 cmpwi r28, 0;   M  242 slwi r3, r28, 1;   M  243 add r0, r5, r0;   M  244 li r6, 0;   M  245 subf r7, r3, r0;   M  246 beq 176;   M  247 cmplwi r28, 8;   M  248 addi r3, r28, -8;   M  249 ble 108;   M  250 addi r0, r3, 7;   M  251 mr r4, r7;   M  252 srwi r0, r0, 3;   M  253 mtctr r0;   M  254 cmplwi r3, 0;   M  255 ble 84;   M  256 lhz r0, 0(r4);   M  257 addi r6, r6, 8;   M  258 sth r0, 0(r5);   M  259 lhz r0, 2(r4);   M  260 sth r0, 2(r5);   M  261 lhz r0, 4(r4);   M  262 sth r0, 4(r5);   M  263 lhz r0, 6(r4);   M  264 sth r0, 6(r5);   M  265 lhz r0, 8(r4);   M  266 sth r0, 8(r5);   M  267 lhz r0, 0xa(r4);   M  268 sth r0, 0xa(r5);   M  269 lhz r0, 0xc(r4);   M  270 sth r0, 0xc(r5);   M  271 lhz r0, 0xe(r4);   M  272 addi r4, r4, 0x10;   M  273 sth r0, 0xe(r5);   M  274 addi r5, r5, 0x10;   M  275 bdnz -76;   M  276 slwi r5, r6, 1;   M  277 addi r3, r31, 0x1c00;   M  278 subf r0, r6, r28;   M  279 add r4, r7, r5;   M  280 add r3, r3, r5;   M  281 mtctr r0;   M  282 cmplw r6, r28;   M  283 bge 28;   M  284 lhz r0, 0(r4);   M  285 addi r4, r4, 2;   M  286 addi r6, r6, 1;   B  355 mr r3, r26;   B  356 li r4, 0;   B  357 b 20; --- replace mine 289:360 base 360:361;   M  289 bdnz -20;   M  290 addi r3, r31, 0x1c00;   M  291 slwi r0, r6, 1;   M  292 li r4, 0;   M  293 sthx r4, r3, r0;   M  294 bl 0;   M  295 stb r3, 0x60(r27);   M  296 addi r3, r27, 0x4c;   M  297 lwz r4, 0x84(r27);   M  298 bl 0;   M  299 clrlwi r28, r3, 0x18;   M  300 cmpwi r28, 0;   M  301 bne 116;   M  302 lwz r12, 0(r27);   M  303 mr r3, r27;   M  304 lwz r12, 0x104(r12);   M  305 mtctr r12;   M  306 bctrl ;   M  307 clrlwi r0, r3, 0x18;   M  308 cmplwi r0, 1;   M  309 beq 76;   M  310 lwz r12, 0(r27);   M  311 mr r3, r27;   M  312 lwz r12, 0x104(r12);   M  313 mtctr r12;   M  314 bctrl ;   M  315 clrlwi r0, r3, 0x18;   M  316 cmplwi r0, 0x12;   M  317 bne 28;   M  318 lwz r12, 0(r27);   M  319 mr r3, r27;   M  320 lwz r12, 0x5c(r12);   M  321 mtctr r12;   M  322 bctrl ;   M  323 b 472;   M  324 mr r3, r27;   M  325 mr r4, r29;   M  326 bl 0;   M  327 mr r28, r3;   M  328 cmpwi r28, 0;   M  329 beq 448;   M  330 addi r3, r31, 0x800;   M  331 li r4, 0;   M  332 li r5, 0x1400;   M  333 bl 0;   M  334 li r0, 0;   M  335 cmpwi r29, 0;   M  336 stw r0, 0x8c(r27);   M  337 bne 16;   M  338 lbz r0, 0x60(r27);   M  339 cmpwi r0, 0;   M  340 beq 404;   M  341 lwz r29, 0x64(r27);   M  342 addi r30, r31, 0x800;   M  343 li r31, 0;   M  344 li r26, 0;   M  345 b 376;   M  346 lwz r12, 0(r27);   M  347 mr r3, r27;   M  348 lwz r12, 0x104(r12);   M  349 mtctr r12;   M  350 bctrl ;   M  351 clrlwi r0, r3, 0x18;   M  352 cmplwi r0, 1;   M  353 bne 68;   M  354 mr r4, r30;   M  355 li r3, 0;   M  356 b 20;   M  357 sth r0, 0(r4);   M  358 addi r4, r4, 2;   M  359 addi r3, r3, 1;   B  360 addi r4, r4, 1; --- replace mine 366:367 base 367:368;   M  366 slwi r0, r3, 1;   B  367 slwi r0, r4, 1; --- replace mine 368:371 base 369:372;   M  368 sthx r26, r30, r0;   M  369 b 136;   M  370 lwz r0, 0x9c(r27);   B  369 sthx r27, r26, r0;   B  370 b 132;   B  371 lwz r0, 0x9c(r28); --- replace mine 375:380 base 376:381;   M  375 sth r0, 0(r30);   M  376 sth r26, 2(r30);   M  377 b 104;   M  378 lwz r12, 0(r27);   M  379 mr r3, r27;   B  376 sth r0, 0(r26);   B  377 sth r27, 2(r26);   B  378 b 100;   B  379 lwz r12, 0(r28);   B  380 mr r3, r28; --- replace mine 385:390 base 386:389;   M  385 bne 44;   M  386 mr r3, r30;   M  387 b 20;   M  388 lhz r0, 0(r29);   M  389 addi r29, r29, 2;   B  386 bne 40;   B  387 mr r3, r26;   B  388 b 16; --- insert mine 392:392 base 391:392;   B  391 addi r29, r29, 2; --- replace mine 394:395 base 394:395;   M  394 bge -24;   B  394 bge -20; --- replace mine 396:399 base 396:399;   M  396 lwz r6, 0x84(r27);   M  397 mr r3, r30;   M  398 addi r4, r27, 0x4c;   B  396 lwz r6, 0x84(r28);   B  397 mr r3, r26;   B  398 addi r4, r28, 0x4c; --- replace mine 402:406 base 402:406;   M  402 beq 140;   M  403 lwz r3, 0x8c(r27);   M  404 mr r24, r30;   M  405 li r25, 0;   B  402 beq 136;   B  403 lwz r3, 0x8c(r28);   B  404 mr r25, r26;   B  405 li r24, 0; --- replace mine 407:413 base 407:413;   M  407 stw r0, 0x8c(r27);   M  408 b 104;   M  409 lwz r0, 0xa0(r27);   M  410 cmpwi r0, 1;   M  411 beq 32;   M  412 bge 16;   B  407 stw r0, 0x8c(r28);   B  408 b 100;   B  409 lwz r0, 0xa0(r28);   B  410 cmpwi r0, 2;   B  411 beq 40;   B  412 bge 76; --- replace mine 414:419 base 414:418;   M  414 bge 44;   M  415 b 68;   M  416 cmpwi r0, 3;   M  417 bge 60;   M  418 b 16;   B  414 beq 40;   B  415 bge 12;   B  416 b 60;   B  417 b 56; --- replace mine 420:421 base 419:420;   M  420 sth r3, 0(r24);   B  419 sth r3, 0(r25); --- replace mine 423:424 base 422:423;   M  423 sth r3, 0(r24);   B  422 sth r3, 0(r25); --- replace mine 425:426 base 424:425;   M  425 cmpwi r25, 0;   B  424 cmpwi r24, 0; --- replace mine 428:429 base 427:428;   M  428 sth r3, 0(r24);   B  427 sth r3, 0(r25); --- replace mine 431:435 base 430:434;   M  431 sth r3, 0(r24);   M  432 addi r25, r25, 1;   M  433 addi r24, r24, 2;   M  434 lhz r3, 0(r24);   B  430 sth r3, 0(r25);   B  431 addi r25, r25, 2;   B  432 addi r24, r24, 1;   B  433 lhz r3, 0(r25); --- replace mine 436:438 base 435:437;   M  436 bne -108;   M  437 addi r30, r30, 0x80;   B  435 bne -104;   B  436 addi r26, r26, 0x80; --- replace mine 439:441 base 438:440;   M  439 cmpw r31, r28;   M  440 blt -376;   B  438 cmpw r31, r30;   B  439 blt -368;

### setElementBuffer__Q39textinput8tistring6WithZiFv
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x104 base 0x104 insns 65/65; diffs 22: [5, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 20, 29, 36, 46, 49, 50, 51, 52];      5 M lis r30, 0;        B lis r31, 0;      7 M addi r3, r30, 0;        B addi r31, r31, 0;      8 M li r29, 0;        B li r28, 0;      9 M li r4, 0;        B addi r3, r31, 0;     10 M li r5, 0x1fe;        B li r4, 0;     11 M bl 0;        B li r5, 0x1fe;     12 M lis r31, 0;        B bl 0;     13 M li r4, 0;        B addi r3, r31, 0x400;     14 M addi r31, r31, 0;        B li r4, 0;     16 M addi r3, r31, 0x200;        B bl 0;     17 M bl 0;        B addi r30, r31, 0;     18 M addi r28, r30, 0;        B addi r31, r31, 0x200;     20 M sthx r3, r28, r30;        B sthx r3, r30, r29;     29 M lhzx r3, r28, r30;        B lhzx r3, r30, r29;     36 M sthx r0, r28, r30;        B sthx r0, r30, r29;     46 M lhzx r3, r28, r30;        B lhzx r3, r30, r29;     49 M sthx r0, r28, r30;        B sthx r0, r30, r29;     50 M addi r29, r29, 1;        B addi r28, r28, 1;     51 M rlwinm r30, r29, 1, 0xf, 0x1e;        B rlwinm r29, r28, 1, 0xf, 0x1e;     52 M lhzx r3, r31, r30;        B lhzx r3, r31, r29;     55 M clrlwi r0, r29, 0x10;        B clrlwi r0, r28, 0x10;     59 M mr r3, r29;        B mr r3, r28;

### create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x1090 base 0x10a0 insns 1060/1064; --- replace mine 5:6 base 5:6;   M    5 lis r30, 0;   B    5 lis r31, 0; --- replace mine 10:11 base 10:11;   M   10 addi r30, r30, 0;   B   10 addi r31, r31, 0; --- replace mine 17:18 base 17:18;   M   17 addi r7, r30, 0x58;   B   17 addi r7, r31, 0x58; --- replace mine 21:22 base 21:22;   M   21 addi r4, r30, 0x79;   B   21 addi r4, r31, 0x79; --- replace mine 27:28 base 27:28;   M   27 addi r4, r30, 0xa3;   B   27 addi r4, r31, 0xa3; --- replace mine 33:35 base 33:35;   M   33 addi r4, r30, 0xce;   M   34 addi r5, r30, 0xfb;   B   33 addi r4, r31, 0xce;   B   34 addi r5, r31, 0xfb; --- replace mine 39:41 base 39:41;   M   39 addi r4, r30, 0x107;   M   40 addi r5, r30, 0xfb;   B   39 addi r4, r31, 0x107;   B   40 addi r5, r31, 0xfb; --- replace mine 45:47 base 45:47;   M   45 addi r4, r30, 0x135;   M   46 addi r5, r30, 0x163;   B   45 addi r4, r31, 0x135;   B   46 addi r5, r31, 0x163; --- replace mine 51:52 base 51:52;   M   51 addi r4, r30, 0x170;   B   51 addi r4, r31, 0x170; --- replace mine 57:58 base 57:58;   M   57 addi r4, r30, 0x19f;   B   57 addi r4, r31, 0x19f; --- replace mine 63:64 base 63:64;   M   63 addi r4, r30, 0x1cd;   B   63 addi r4, r31, 0x1cd; --- replace mine 69:70 base 69:70;   M   69 addi r4, r30, 0x1f6;   B   69 addi r4, r31, 0x1f6; --- replace mine 75:76 base 75:76;   M   75 addi r4, r30, 0x225;   B   75 addi r4, r31, 0x225; --- replace mine 81:82 base 81:82;   M   81 addi r4, r30, 0x253;   B   81 addi r4, r31, 0x253; --- replace mine 109:110 base 109:110;   M  109 addi r4, r30, 0x27c;   B  109 addi r4, r31, 0x27c; --- replace mine 116:119 base 116:119;   M  116 lis r31, 0;   M  117 mr r26, r3;   M  118 addi r31, r31, 0;   B  116 lis r26, 0;   B  117 mr r30, r3;   B  118 addi r26, r26, 0; --- replace mine 120:121 base 120:121;   M  120 lwz r3, 0x80(r31);   B  120 lwz r3, 0x80(r26); --- replace mine 123:124 base 123:124;   M  123 lwz r12, 0(r26);   B  123 lwz r12, 0(r30); --- replace mine 125:126 base 125:126;   M  125 mr r3, r26;   B  125 mr r3, r30; --- replace mine 131:132 base 131:132;   M  131 addi r4, r30, 0x288;   B  131 addi r4, r31, 0x288; --- replace mine 138:140 base 138:140;   M  138 lwz r5, 0x80(r31);   M  139 mr r26, r3;   B  138 lwz r5, 0x80(r26);   B  139 mr r30, r3; --- replace mine 143:144 base 143:144;   M  143 lwz r12, 0(r26);   B  143 lwz r12, 0(r30); --- replace mine 145:146 base 145:146;   M  145 mr r3, r26;   B  145 mr r3, r30; --- replace mine 151:152 base 151:152;   M  151 addi r4, r30, 0x293;   B  151 addi r4, r31, 0x293; --- replace mine 158:160 base 158:160;   M  158 lwz r5, 0x80(r31);   M  159 mr r26, r3;   B  158 lwz r5, 0x80(r26);   B  159 mr r30, r3; --- replace mine 163:164 base 163:164;   M  163 lwz r12, 0(r26);   B  163 lwz r12, 0(r30); --- replace mine 165:166 base 165:166;   M  165 mr r3, r26;   B  165 mr r3, r30; --- replace mine 178:180 base 178:180;   M  178 lwz r5, 0x80(r31);   M  179 mr r31, r3;   B  178 lwz r5, 0x80(r26);   B  179 mr r30, r3; --- replace mine 183:184 base 183:184;   M  183 lwz r12, 0(r31);   B  183 lwz r12, 0(r30); --- replace mine 185:186 base 185:186;   M  185 mr r3, r31;   B  185 mr r3, r30; --- replace mine 196:197 base 196:197;   M  196 addi r7, r30, 0x29e;   B  196 addi r7, r31, 0x29e; --- replace mine 200:201 base 200:201;   M  200 addi r4, r30, 0x2bf;   B  200 addi r4, r31, 0x2bf; --- replace mine 206:207 base 206:207;   M  206 addi r4, r30, 0x2e9;   B  206 addi r4, r31, 0x2e9; --- replace mine 212:214 base 212:214;   M  212 addi r4, r30, 0x314;   M  213 addi r5, r30, 0xfb;   B  212 addi r4, r31, 0x314;   B  213 addi r5, r31, 0xfb; --- replace mine 218:220 base 218:220;   M  218 addi r4, r30, 0x341;   M  219 addi r5, r30, 0xfb;   B  218 addi r4, r31, 0x341;   B  219 addi r5, r31, 0xfb; --- replace mine 224:226 base 224:226;   M  224 addi r4, r30, 0x36f;   M  225 addi r5, r30, 0x163;   B  224 addi r4, r31, 0x36f;   B  225 addi r5, r31, 0x163; --- replace mine 230:231 base 230:231;   M  230 addi r4, r30, 0x39d;   B  230 addi r4, r31, 0x39d; --- replace mine 236:237 base 236:237;   M  236 addi r4, r30, 0x3cc;   B  236 addi r4, r31, 0x3cc; --- replace mine 242:243 base 242:243;   M  242 addi r4, r30, 0x3fa;   B  242 addi r4, r31, 0x3fa; --- replace mine 248:249 base 248:249;   M  248 addi r4, r30, 0x423;   B  248 addi r4, r31, 0x423; --- replace mine 254:255 base 254:255;   M  254 addi r4, r30, 0x452;   B  254 addi r4, r31, 0x452; --- replace mine 260:261 base 260:261;   M  260 addi r4, r30, 0x480;   B  260 addi r4, r31, 0x480; --- replace mine 266:267 base 266:267;   M  266 addi r4, r30, 0x4a9;   B  266 addi r4, r31, 0x4a9; --- replace mine 272:273 base 272:273;   M  272 addi r4, r30, 0x4d8;   B  272 addi r4, r31, 0x4d8; --- replace mine 278:279 base 278:279;   M  278 addi r4, r30, 0x506;   B  278 addi r4, r31, 0x506; --- replace mine 284:285 base 284:285;   M  284 addi r4, r30, 0x52f;   B  284 addi r4, r31, 0x52f; --- replace mine 290:291 base 290:291;   M  290 addi r4, r30, 0x55e;   B  290 addi r4, r31, 0x55e; --- replace mine 296:297 base 296:297;   M  296 addi r4, r30, 0x58c;   B  296 addi r4, r31, 0x58c; --- replace mine 334:335 base 334:335;   M  334 addi r4, r30, 0x5b5;   B  334 addi r4, r31, 0x5b5; --- replace mine 341:344 base 341:344;   M  341 lis r31, 0;   M  342 mr r26, r3;   M  343 addi r31, r31, 0;   B  341 lis r26, 0;   B  342 mr r30, r3;   B  343 addi r26, r26, 0; --- replace mine 345:346 base 345:346;   M  345 lwz r3, 0x80(r31);   B  345 lwz r3, 0x80(r26); --- replace mine 348:349 base 348:349;   M  348 lwz r12, 0(r26);   B  348 lwz r12, 0(r30); --- replace mine 350:351 base 350:351;   M  350 mr r3, r26;   B  350 mr r3, r30; --- replace mine 356:357 base 356:357;   M  356 addi r4, r30, 0x5be;   B  356 addi r4, r31, 0x5be; --- replace mine 363:365 base 363:365;   M  363 lwz r5, 0x80(r31);   M  364 mr r26, r3;   B  363 lwz r5, 0x80(r26);   B  364 mr r30, r3; --- replace mine 368:369 base 368:369;   M  368 lwz r12, 0(r26);   B  368 lwz r12, 0(r30); --- replace mine 370:371 base 370:371;   M  370 mr r3, r26;   B  370 mr r3, r30; --- replace mine 376:377 base 376:377;   M  376 addi r4, r30, 0x5c9;   B  376 addi r4, r31, 0x5c9; --- replace mine 383:385 base 383:385;   M  383 lwz r5, 0x80(r31);   M  384 mr r26, r3;   B  383 lwz r5, 0x80(r26);   B  384 mr r30, r3; --- replace mine 388:389 base 388:389;   M  388 lwz r12, 0(r26);   B  388 lwz r12, 0(r30); --- replace mine 390:391 base 390:391;   M  390 mr r3, r26;   B  390 mr r3, r30; --- replace mine 396:397 base 396:397;   M  396 addi r4, r30, 0x5d4;   B  396 addi r4, r31, 0x5d4; --- replace mine 403:405 base 403:405;   M  403 lwz r5, 0x80(r31);   M  404 mr r26, r3;   B  403 lwz r5, 0x80(r26);   B  404 mr r30, r3; --- replace mine 408:409 base 408:409;   M  408 lwz r12, 0(r26);   B  408 lwz r12, 0(r30); --- replace mine 410:411 base 410:411;   M  410 mr r3, r26;   B  410 mr r3, r30; --- replace mine 416:417 base 416:417;   M  416 addi r4, r30, 0x5df;   B  416 addi r4, r31, 0x5df; --- replace mine 423:425 base 423:425;   M  423 lwz r5, 0x80(r31);   M  424 mr r26, r3;   B  423 lwz r5, 0x80(r26);   B  424 mr r30, r3; --- replace mine 428:429 base 428:429;   M  428 lwz r12, 0(r26);   B  428 lwz r12, 0(r30); --- replace mine 430:431 base 430:431;   M  430 mr r3, r26;   B  430 mr r3, r30; --- replace mine 436:437 base 436:437;   M  436 addi r4, r30, 0x27c;   B  436 addi r4, r31, 0x27c; --- replace mine 443:445 base 443:445;   M  443 lwz r5, 0x80(r31);   M  444 mr r26, r3;   B  443 lwz r5, 0x80(r26);   B  444 mr r30, r3; --- replace mine 448:449 base 448:449;   M  448 lwz r12, 0(r26);   B  448 lwz r12, 0(r30); --- replace mine 450:451 base 450:451;   M  450 mr r3, r26;   B  450 mr r3, r30; --- replace mine 456:457 base 456:457;   M  456 addi r4, r30, 0x288;   B  456 addi r4, r31, 0x288; --- replace mine 463:465 base 463:465;   M  463 lwz r5, 0x80(r31);   M  464 mr r26, r3;   B  463 lwz r5, 0x80(r26);   B  464 mr r30, r3; --- replace mine 468:469 base 468:469;   M  468 lwz r12, 0(r26);   B  468 lwz r12, 0(r30); --- replace mine 470:471 base 470:471;   M  470 mr r3, r26;   B  470 mr r3, r30; --- replace mine 476:477 base 476:477;   M  476 addi r4, r30, 0x293;   B  476 addi r4, r31, 0x293; --- replace mine 483:485 base 483:485;   M  483 lwz r5, 0x80(r31);   M  484 mr r26, r3;   B  483 lwz r5, 0x80(r26);   B  484 mr r30, r3; --- replace mine 488:489 base 488:489;   M  488 lwz r12, 0(r26);   B  488 lwz r12, 0(r30); --- replace mine 490:491 base 490:491;   M  490 mr r3, r26;   B  490 mr r3, r30; --- replace mine 496:497 base 496:497;   M  496 addi r4, r30, 0x5ea;   B  496 addi r4, r31, 0x5ea; --- replace mine 503:505 base 503:505;   M  503 lwz r5, 0x80(r31);   M  504 mr r26, r3;   B  503 lwz r5, 0x80(r26);   B  504 mr r30, r3; --- replace mine 508:509 base 508:509;   M  508 lwz r12, 0(r26);   B  508 lwz r12, 0(r30); --- replace mine 510:511 base 510:511;   M  510 mr r3, r26;   B  510 mr r3, r30; --- replace mine 516:518 base 516:518;   M  516 lwz r5, 0x94(r31);   M  517 li r6, 0;   B  516 lwz r6, 0x94(r26);   B  517 li r5, 0; --- replace mine 520:521 base 520:521;   M  520 add r4, r5, r3;   B  520 add r4, r6, r3; --- replace mine 525:526 base 525:526;   M  525 addi r6, r6, 1;   B  525 addi r5, r5, 1; --- replace mine 528:530 base 528:530;   M  528 cmpwi r6, 5;   M  529 blt 96;   B  528 cmpwi r5, 5;   B  529 blt 104; --- replace mine 548:550 base 548:549;   M  548 li r4, 1;   M  549 bl 0;   B  548 lbz r4, 0xcf(r3); --- insert mine 551:551 base 550:553;   B  550 rlwinm r4, r4, 0, 0x18, 0x1e;   B  551 ori r4, r4, 1;   B  552 stb r4, 0xcf(r3); --- replace mine 552:553 base 554:555;   M  552 b 92;   B  554 b 100; --- replace mine 561:564 base 563:564;   M  561 li r4, 1;   M  562 bl 0;   M  563 lwz r3, 4(r27);   B  563 lbz r0, 0xcf(r3); --- insert mine 566:566 base 566:570;   B  566 rlwinm r0, r0, 0, 0x18, 0x1e;   B  567 ori r0, r0, 1;   B  568 stb r0, 0xcf(r3);   B  569 lwz r3, 4(r27); --- replace mine 584:585 base 588:589;   M  584 mr r26, r3;   B  588 mr r30, r3; --- replace mine 590:591 base 594:595;   M  590 lwz r12, 0(r26);   B  594 lwz r12, 0(r30); --- replace mine 592:593 base 596:597;   M  592 mr r3, r26;   B  596 mr r3, r30; --- replace mine 603:604 base 607:608;   M  603 addi r7, r30, 0x5f5;   B  607 addi r7, r31, 0x5f5; --- replace mine 607:608 base 611:612;   M  607 addi r4, r30, 0x616;   B  611 addi r4, r31, 0x616; --- replace mine 620:621 base 624:625;   M  620 addi r4, r30, 0x61f;   B  624 addi r4, r31, 0x61f; --- replace mine 626:627 base 630:631;   M  626 addi r4, r30, 0x64e;   B  630 addi r4, r31, 0x64e; --- replace mine 632:634 base 636:638;   M  632 addi r4, r30, 0x67e;   M  633 addi r5, r30, 0x6ad;   B  636 addi r4, r31, 0x67e;   B  637 addi r5, r31, 0x6ad; --- replace mine 638:640 base 642:644;   M  638 addi r4, r30, 0x6ba;   M  639 addi r5, r30, 0x6ad;   B  642 addi r4, r31, 0x6ba;   B  643 addi r5, r31, 0x6ad; --- replace mine 644:646 base 648:650;   M  644 addi r4, r30, 0x6e8;   M  645 addi r5, r30, 0x711;   B  648 addi r4, r31, 0x6e8;   B  649 addi r5, r31, 0x711; --- replace mine 650:652 base 654:656;   M  650 addi r4, r30, 0x71b;   M  651 addi r5, r30, 0x74a;   B  654 addi r4, r31, 0x71b;   B  655 addi r5, r31, 0x74a; --- replace mine 656:658 base 660:662;   M  656 addi r4, r30, 0x757;   M  657 addi r5, r30, 0x74a;   B  660 addi r4, r31, 0x757;   B  661 addi r5, r31, 0x74a; --- replace mine 662:664 base 666:668;   M  662 addi r4, r30, 0x785;   M  663 addi r5, r30, 0x7ae;   B  666 addi r4, r31, 0x785;   B  667 addi r5, r31, 0x7ae; --- replace mine 668:670 base 672:674;   M  668 addi r4, r30, 0x7b8;   M  669 addi r5, r30, 0x7e1;   B  672 addi r4, r31, 0x7b8;   B  673 addi r5, r31, 0x7e1; --- replace mine 674:676 base 678:680;   M  674 addi r4, r30, 0x7ee;   M  675 addi r5, r30, 0x7e1;   B  678 addi r4, r31, 0x7ee;   B  679 addi r5, r31, 0x7e1; --- replace mine 680:682 base 684:686;   M  680 addi r4, r30, 0x818;   M  681 addi r5, r30, 0x840;   B  684 addi r4, r31, 0x818;   B  685 addi r5, r31, 0x840; --- replace mine 686:688 base 690:692;   M  686 addi r4, r30, 0x7b8;   M  687 addi r5, r30, 0x84a;   B  690 addi r4, r31, 0x7b8;   B  691 addi r5, r31, 0x84a; --- replace mine 692:694 base 696:698;   M  692 addi r4, r30, 0x7ee;   M  693 addi r5, r30, 0x84a;   B  696 addi r4, r31, 0x7ee;   B  697 addi r5, r31, 0x84a; --- replace mine 698:700 base 702:704;   M  698 addi r4, r30, 0x818;   M  699 addi r5, r30, 0x857;   B  702 addi r4, r31, 0x818;   B  703 addi r5, r31, 0x857; --- replace mine 704:706 base 708:710;   M  704 addi r4, r30, 0x861;   M  705 addi r5, r30, 0x889;   B  708 addi r4, r31, 0x861;   B  709 addi r5, r31, 0x889; --- replace mine 710:712 base 714:716;   M  710 addi r4, r30, 0x894;   M  711 addi r5, r30, 0x889;   B  714 addi r4, r31, 0x894;   B  715 addi r5, r31, 0x889; --- replace mine 716:718 base 720:722;   M  716 addi r4, r30, 0x861;   M  717 addi r5, r30, 0x8ba;   B  720 addi r4, r31, 0x861;   B  721 addi r5, r31, 0x8ba; --- replace mine 722:724 base 726:728;   M  722 addi r4, r30, 0x894;   M  723 addi r5, r30, 0x8ba;   B  726 addi r4, r31, 0x894;   B  727 addi r5, r31, 0x8ba; --- replace mine 728:730 base 732:734;   M  728 addi r4, r30, 0x8c5;   M  729 addi r5, r30, 0x8eb;   B  732 addi r4, r31, 0x8c5;   B  733 addi r5, r31, 0x8eb; --- replace mine 734:736 base 738:740;   M  734 addi r4, r30, 0x8f5;   M  735 addi r5, r30, 0x924;   B  738 addi r4, r31, 0x8f5;   B  739 addi r5, r31, 0x924; --- replace mine 740:742 base 744:746;   M  740 addi r4, r30, 0x930;   M  741 addi r5, r30, 0x924;   B  744 addi r4, r31, 0x930;   B  745 addi r5, r31, 0x924; --- replace mine 746:748 base 750:752;   M  746 addi r4, r30, 0x8f5;   M  747 addi r5, r30, 0x95d;   B  750 addi r4, r31, 0x8f5;   B  751 addi r5, r31, 0x95d; --- replace mine 752:754 base 756:758;   M  752 addi r4, r30, 0x930;   M  753 addi r5, r30, 0x95d;   B  756 addi r4, r31, 0x930;   B  757 addi r5, r31, 0x95d; --- replace mine 796:797 base 800:801;   M  796 addi r4, r30, 0x969;   B  800 addi r4, r31, 0x969; --- replace mine 805:808 base 809:812;   M  805 lis r31, 0;   M  806 mr r26, r3;   M  807 addi r31, r31, 0;   B  809 lis r26, 0;   B  810 mr r30, r3;   B  811 addi r26, r26, 0; --- replace mine 809:810 base 813:814;   M  809 lwz r3, 0x80(r31);   B  813 lwz r3, 0x80(r26); --- replace mine 812:813 base 816:817;   M  812 lwz r12, 0(r26);   B  816 lwz r12, 0(r30); --- replace mine 814:815 base 818:819;   M  814 mr r3, r26;   B  818 mr r3, r30; --- replace mine 820:821 base 824:825;   M  820 addi r4, r30, 0x973;   B  824 addi r4, r31, 0x973; --- replace mine 827:829 base 831:833;   M  827 lwz r5, 0x80(r31);   M  828 mr r26, r3;   B  831 lwz r5, 0x80(r26);   B  832 mr r30, r3; --- replace mine 832:833 base 836:837;   M  832 lwz r12, 0(r26);   B  836 lwz r12, 0(r30); --- replace mine 834:835 base 838:839;   M  834 mr r3, r26;   B  838 mr r3, r30; --- replace mine 845:846 base 849:850;   M  845 addi r7, r30, 0x980;   B  849 addi r7, r31, 0x980; --- replace mine 849:850 base 853:854;   M  849 addi r4, r30, 0x9a1;   B  853 addi r4, r31, 0x9a1; --- replace mine 855:856 base 859:860;   M  855 addi r4, r30, 0x9cb;   B  859 addi r4, r31, 0x9cb; --- replace mine 902:903 base 906:907;   M  902 addi r29, r30, 0;   B  906 addi r29, r31, 0; --- replace mine 959:960 base 963:964;   M  959 addi r29, r30, 0xc;   B  963 addi r29, r31, 0xc; --- replace mine 979:980 base 983:984;   M  979 addi r29, r30, 0x20;   B  983 addi r29, r31, 0x20; --- replace mine 1033:1034 base 1037:1038;   M 1033 addi r29, r30, 0x48;   B 1037 addi r29, r31, 0x48;

### drawTransferTitles__Q33ipl5scene8SDMemoryFv
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x6dc base 0x70c insns 439/451; --- replace mine 23:24 base 23:24;   M   23 lis r31, 0;   B   23 lis r30, 0; --- replace mine 26:27 base 26:27;   M   26 addi r31, r31, 0;   B   26 addi r30, r30, 0; --- replace mine 33:35 base 33:35;   M   33 addi r4, r31, 0xb04;   M   34 lfs f2, 0x2c(r3);   B   33 addi r4, r30, 0xb04;   B   34 lfs f1, 0x2c(r3); --- replace mine 36:37 base 36:37;   M   36 lfs f1, 0x30(r3);   B   36 lfs f31, 0x30(r3); --- replace mine 39:40 base 39:40;   M   39 stfs f2, 0x68(r1);   B   39 stfs f1, 0x70(r1); --- replace mine 41:42 base 41:42;   M   41 stfs f1, 0x6c(r1);   B   41 stfs f31, 0x74(r1); --- replace mine 43:44 base 43:44;   M   43 stfs f0, 0x70(r1);   B   43 stfs f0, 0x78(r1); --- replace mine 47:48 base 47:48;   M   47 addi r4, r31, 0xb12;   B   47 addi r4, r30, 0xb12; --- delete mine 54:56 base 54:54;   M   54 lfs f31, 0x6c(r1);   M   55 mr r30, r3; --- insert mine 57:57 base 55:56;   B   55 mr r29, r3; --- replace mine 60:61 base 59:60;   M   60 addi r4, r31, 0xb04;   B   59 addi r4, r30, 0xb04; --- replace mine 70:72 base 69:71;   M   70 lbz r29, 0xcd(r3);   M   71 addi r3, r30, 0x10;   B   69 lbz r31, 0xcd(r3);   B   70 addi r3, r29, 0x10; --- replace mine 75:76 base 74:75;   M   75 stb r29, 0xc9(r22);   B   74 stb r31, 0xc9(r22); --- replace mine 77:78 base 76:77;   M   77 addi r3, r30, 0x10;   B   76 addi r3, r29, 0x10; --- replace mine 79:83 base 78:82;   M   79 stw r3, 0x28(r1);   M   80 addi r3, r1, 0x2c;   M   81 addi r4, r1, 0x28;   M   82 stw r22, 0x2c(r1);   B   78 stw r3, 0x30(r1);   B   79 addi r3, r1, 0x34;   B   80 addi r4, r1, 0x30;   B   81 stw r22, 0x34(r1); --- replace mine 87:89 base 86:87;   M   87 li r21, 0;   M   88 lfs f28, 0(0);   B   86 lfs f26, 0(0); --- replace mine 90:92 base 88:90;   M   90 lfs f29, 0x50(r30);   M   91 beq 332;   B   88 lfs f27, 0x50(r29);   B   89 beq 356; --- insert mine 98:98 base 96:97;   B   96 li r22, 0; --- insert mine 100:100 base 99:102;   B   99 cmpwi r3, 0;   B  100 beq 36;   B  101 li r21, 0; --- insert mine 101:101 base 103:104;   B  103 mr r4, r21; --- replace mine 102:104 base 105:106;   M  102 li r4, 0;   M  103 addi r21, r21, 1;   B  105 addi r22, r22, 1; --- replace mine 114:116 base 116:118;   M  114 mr r23, r3;   M  115 addi r4, r31, 0xb1e;   B  116 mr r26, r3;   B  117 addi r4, r30, 0xb1e; --- replace mine 122:127 base 124:131;   M  122 addic. r26, r21, 1;   M  123 mr r24, r3;   M  124 li r27, 0;   M  125 ble 196;   M  126 lfs f26, 0(0);   B  124 addic. r23, r22, 1;   B  125 mr r27, r3;   B  126 li r28, 0;   B  127 ble 204;   B  128 lfs f24, 0(0);   B  129 li r24, 0;   B  130 lfs f25, 0(0); --- replace mine 128:131 base 132:135;   M  128 lfs f27, 0(0);   M  129 mr r3, r23;   M  130 li r4, 0;   B  132 b 176;   B  133 mr r3, r26;   B  134 mr r4, r24; --- replace mine 135:137 base 139:141;   M  135 mr r3, r24;   M  136 mr r4, r23;   B  139 mr r3, r27;   B  140 mr r4, r26; --- replace mine 139:141 base 143:145;   M  139 subf r0, r23, r3;   M  140 mr r4, r23;   B  143 subf r0, r26, r3;   B  144 mr r4, r26; --- replace mine 143:145 base 147:149;   M  143 addze r23, r0;   M  144 mr r5, r23;   B  147 addze r26, r0;   B  148 mr r5, r26; --- replace mine 146:148 base 150:152;   M  146 slwi r0, r23, 1;   M  147 mr r3, r24;   B  150 slwi r0, r26, 1;   B  151 mr r3, r27; --- replace mine 152:154 base 156:158;   M  152 addi r23, r22, 2;   M  153 .long fc1fd840;   B  156 addi r26, r22, 2;   B  157 .long fc1fc840; --- replace mine 155:159 base 159:163;   M  155 stfs f26, 0x50(r1);   M  156 mr r3, r30;   M  157 addi r4, r1, 0x50;   M  158 stfs f28, 0x54(r1);   B  159 stfs f24, 0x58(r1);   B  160 mr r3, r29;   B  161 addi r4, r1, 0x58;   B  162 stfs f26, 0x5c(r1); --- replace mine 160:162 base 164:166;   M  160 lwz r12, 0(r30);   M  161 mr r3, r30;   B  164 lwz r12, 0(r29);   B  165 mr r3, r29; --- replace mine 168:169 base 172:173;   M  168 mr r4, r30;   B  172 mr r4, r29; --- replace mine 170:173 base 174:177;   M  170 addi r27, r27, 1;   M  171 fsubs f28, f28, f29;   M  172 cmpw r27, r26;   B  174 fsubs f26, f26, f27;   B  175 addi r28, r28, 1;   B  176 cmpw r28, r23; --- replace mine 175:176 base 179:180;   M  175 fadds f28, f28, f29;   B  179 fadds f26, f26, f27; --- replace mine 182:184 base 186:188;   M  182 fadds f30, f1, f28;   M  183 fadds f25, f0, f28;   B  186 fadds f30, f1, f26;   B  187 fadds f29, f0, f26; --- replace mine 187:189 base 191:193;   M  187 lfs f24, 0x50(r3);   M  188 mr r30, r3;   B  191 lfs f28, 0x50(r3);   B  192 mr r29, r3; --- replace mine 193:194 base 197:198;   M  193 stb r29, 0xc9(r22);   B  197 stb r31, 0xc9(r22); --- replace mine 195:196 base 199:200;   M  195 addi r3, r30, 0x10;   B  199 addi r3, r29, 0x10; --- replace mine 197:201 base 201:205;   M  197 stw r3, 0x20(r1);   M  198 addi r3, r1, 0x24;   M  199 addi r4, r1, 0x20;   M  200 stw r22, 0x24(r1);   B  201 stw r3, 0x28(r1);   B  202 addi r3, r1, 0x2c;   B  203 addi r4, r1, 0x28;   B  204 stw r22, 0x2c(r1); --- replace mine 205:206 base 209:210;   M  205 addi r4, r31, 0x616;   B  209 addi r4, r30, 0x616; --- replace mine 212:213 base 216:217;   M  212 stb r29, 0xcd(r3);   B  216 stb r31, 0xcd(r3); --- replace mine 214:215 base 218:219;   M  214 lfs f28, 0(0);   B  218 lfs f26, 0(0); --- replace mine 216:217 base 220:221;   M  216 lfs f27, 0(0);   B  220 lfs f25, 0(0); --- replace mine 218:219 base 222:223;   M  218 lfs f26, 0(0);   B  222 lfs f24, 0(0); --- replace mine 220:221 base 224:225;   M  220 lfd f29, 0(0);   B  224 lfd f27, 0(0); --- replace mine 224:225 base 228:229;   M  224 b 544;   B  228 b 576; --- replace mine 231:232 base 235:236;   M  231 bge 144;   B  235 bge 160; --- replace mine 241:243 base 245:247;   M  241 bne 104;   M  242 addi r3, r1, 0x34;   B  245 bne 120;   B  246 addi r3, r1, 0x3c; --- insert mine 247:247 base 251:253;   B  251 addi r27, r27, 1;   B  252 addi r24, r24, 8; --- replace mine 248:249 base 254:255;   M  248 lbz r8, 0x34(r1);   B  254 lbz r8, 0x3c(r1); --- replace mine 250:251 base 256:284;   M  250 lbz r7, 0x35(r1);   B  256 lbz r7, 0x3d(r1);   B  257 addi r4, r1, 0x24;   B  258 lbz r6, 0x3e(r1);   B  259 addi r5, r1, 0x20;   B  260 lbz r0, 0x3f(r1);   B  261 stb r8, 0xc(r1);   B  262 stb r7, 0xd(r1);   B  263 stb r6, 0xe(r1);   B  264 stb r0, 0xf(r1);   B  265 stb r8, 0x24(r1);   B  266 stb r7, 0x25(r1);   B  267 stb r6, 0x26(r1);   B  268 stb r0, 0x27(r1);   B  269 stb r8, 0x20(r1);   B  270 stb r7, 0x21(r1);   B  271 stb r6, 0x22(r1);   B  272 stb r0, 0x23(r1);   B  273 bl 0;   B  274 b 108;   B  275 addi r3, r1, 0x38;   B  276 li r4, 0x64;   B  277 li r5, 0x64;   B  278 li r6, 0x64;   B  279 li r7, 0xff;   B  280 bl 0;   B  281 lbz r8, 0x38(r1);   B  282 mr r3, r28;   B  283 lbz r7, 0x39(r1); --- replace mine 252:253 base 285:286;   M  252 lbz r6, 0x36(r1);   B  285 lbz r6, 0x3a(r1); --- replace mine 254:256 base 287:292;   M  254 lbz r0, 0x37(r1);   M  255 addi r27, r27, 1;   B  287 lbz r0, 0x3b(r1);   B  288 stb r8, 8(r1);   B  289 stb r7, 9(r1);   B  290 stb r6, 0xa(r1);   B  291 stb r0, 0xb(r1); --- delete mine 257:258 base 293:293;   M  257 addi r24, r24, 8; --- replace mine 266:272 base 301:304;   M  266 b 92;   M  267 addi r3, r1, 0x30;   M  268 li r4, 0x64;   M  269 li r5, 0x64;   M  270 li r6, 0x64;   M  271 li r7, 0xff;   B  301 lwz r4, 8(r25);   B  302 addi r3, r1, 0x60;   B  303 addi r5, r30, 0x616; --- replace mine 273:296 base 305:308;   M  273 lbz r8, 0x30(r1);   M  274 mr r3, r28;   M  275 lbz r7, 0x31(r1);   M  276 addi r4, r1, 0x14;   M  277 lbz r6, 0x32(r1);   M  278 addi r5, r1, 0x10;   M  279 lbz r0, 0x33(r1);   M  280 stb r8, 0x14(r1);   M  281 stb r7, 0x15(r1);   M  282 stb r6, 0x16(r1);   M  283 stb r0, 0x17(r1);   M  284 stb r8, 0x10(r1);   M  285 stb r7, 0x11(r1);   M  286 stb r6, 0x12(r1);   M  287 stb r0, 0x13(r1);   M  288 bl 0;   M  289 lwz r4, 8(r25);   M  290 addi r3, r1, 0x58;   M  291 addi r5, r31, 0x616;   M  292 bl 0;   M  293 lfs f2, 0x64(r1);   M  294 lfs f1, 0x5c(r1);   M  295 lfs f0, 0x50(r30);   B  305 lfs f2, 0x6c(r1);   B  306 lfs f1, 0x64(r1);   B  307 lfs f0, 0x50(r29); --- replace mine 303:305 base 315:317;   M  303 stfd f0, 0x78(r1);   M  304 lwz r20, 0x7c(r1);   B  315 stfd f0, 0x80(r1);   B  316 lwz r20, 0x84(r1); --- replace mine 307:308 base 319:320;   M  307 .long fc1a0040;   B  319 .long fc180040; --- replace mine 309:310 base 321:322;   M  309 .long fc00d840;   B  321 .long fc00c840; --- replace mine 311:315 base 323:327;   M  311 stfs f28, 0x48(r1);   M  312 mr r3, r30;   M  313 addi r4, r1, 0x48;   M  314 stfs f30, 0x4c(r1);   B  323 stfs f26, 0x50(r1);   B  324 mr r3, r29;   B  325 addi r4, r1, 0x50;   B  326 stfs f30, 0x54(r1); --- replace mine 316:318 base 328:330;   M  316 lwz r12, 0(r30);   M  317 mr r3, r30;   B  328 lwz r12, 0(r29);   B  329 mr r3, r29; --- replace mine 324:325 base 336:337;   M  324 mr r4, r30;   B  336 mr r4, r29; --- replace mine 326:327 base 338:339;   M  326 fsubs f30, f30, f24;   B  338 fsubs f30, f30, f28; --- replace mine 330:332 base 342:344;   M  330 fadds f0, f31, f25;   M  331 .long fc1a0040;   B  342 fadds f0, f31, f29;   B  343 .long fc180040; --- replace mine 333:334 base 345:346;   M  333 .long fc00d840;   B  345 .long fc00c840; --- replace mine 335:336 base 347:348;   M  335 stfs f28, 0x40(r1);   B  347 stfs f26, 0x48(r1); --- replace mine 337:339 base 349:351;   M  337 addi r4, r1, 0x40;   M  338 stfs f25, 0x44(r1);   B  349 addi r4, r1, 0x48;   B  350 stfs f29, 0x4c(r1); --- replace mine 351:352 base 363:364;   M  351 stw r21, 0x78(r1);   B  363 stw r21, 0x80(r1); --- replace mine 354:355 base 366:367;   M  354 stw r0, 0x7c(r1);   B  366 stw r0, 0x84(r1); --- replace mine 356:360 base 368:372;   M  356 lfd f0, 0x78(r1);   M  357 fsubs f0, f0, f29;   M  358 fmuls f0, f24, f0;   M  359 fsubs f25, f25, f0;   B  368 lfd f0, 0x80(r1);   B  369 fsubs f0, f0, f27;   B  370 fmuls f0, f0, f28;   B  371 fsubs f29, f29, f0; --- replace mine 362:363 base 374:375;   M  362 blt -548;   B  374 blt -580; --- replace mine 364:366 base 376:378;   M  364 fadds f30, f30, f24;   M  365 addi r4, r31, 0xa13;   B  376 fadds f30, f30, f28;   B  377 addi r4, r30, 0xa13; --- replace mine 377:378 base 389:390;   M  377 stb r29, 0xc9(r22);   B  389 stb r31, 0xc9(r22); --- replace mine 381:385 base 393:397;   M  381 stw r3, 8(r1);   M  382 addi r3, r1, 0xc;   M  383 addi r4, r1, 8;   M  384 stw r22, 0xc(r1);   B  393 stw r3, 0x10(r1);   B  394 addi r3, r1, 0x14;   B  395 addi r4, r1, 0x10;   B  396 stw r22, 0x14(r1); --- replace mine 394:397 base 406:409;   M  394 stfs f30, 0x3c(r1);   M  395 addi r4, r1, 0x38;   M  396 stfs f0, 0x38(r1);   B  406 stfs f30, 0x44(r1);   B  407 addi r4, r1, 0x40;   B  408 stfs f0, 0x40(r1); --- replace mine 409:410 base 421:422;   M  409 addi r4, r31, 0xb2c;   B  421 addi r4, r30, 0xb2c;
- ConvertDaysToDate: month scalar s32 lifetime with const input view: ((0, 6), 103, 103) -> ((1, 26), 103, 103); restored
- ConvertDaysToDate: month scalar u32 lifetime with const input view: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: month scalar u16 lifetime with const input view: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: explicit common-month branch labels: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
Structural diagnosis227/227: source savegpr15 vs target17; scan source0x28 vs target0x40 and info0x80 vs0xa0. Callback NULL tests use unsigned compare instead of cmpwi; rate loop and retry scopes differ. Move aggregate locals before adjusting registers.
- AOSSi_WLANGetBSSList: scan parameter definition aligned to 32-byte device boundary: ((89, 202), 227, 227) -> ((82, 203), 227, 227); kept
- AOSSi_WLANGetBSSList: callback presence tested as boolean: ((82, 203), 227, 227) -> ((76, 169), 226, 227); kept
- AOSSi_WLANGetBSSList: retry counters initialized at each operation boundary: ((76, 169), 226, 227) -> ((82, 210), 226, 227); restored
Structural diagnosis156/155: result zero initialized too early, target at IP configuration; final SSID field load occurs twice in source versus once target. Use const read view and later result initialization.
- AOSSi_WLANConnect: result zero initialized at IP configuration boundary: ((4, 83), 156, 155) -> ((6, 20), 156, 155); restored
- AOSSi_WLANConnect: const interface read view for status SSID copy: ((4, 83), 156, 155) -> compile failure; restored
- AOSSi_WLANConnect: cached final SSID length scalar feeds status and copy: ((4, 83), 156, 155) -> compile failure; restored

### TMCJPEGDEC_IFD0_tag_parse
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x784 base 0x784 insns 481/481; diffs 446: [0, 2, 3, 4, 5, 7, 10, 11, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 23, 24];      0 M lbz r0, 1(r5);        B lbz r6, 1(r5);      2 M lbz r7, 0(r5);        B lbz r0, 0(r5);      3 M rlwimi r7, r0, 8, 0x10, 0x17;        B rlwimi r0, r6, 8, 0x10, 0x17;      4 M rlwinm r6, r7, 8, 0x10, 0x17;        B rlwinm r7, r0, 8, 0x10, 0x17;      5 M rlwimi r6, r7, 0x18, 0x18, 0x1f;        B rlwimi r7, r0, 0x18, 0x18, 0x1f;      7 M clrlwi r6, r7, 0x10;        B clrlwi r7, r0, 0x10;     10 M lbz r7, 2(r5);        B lbz r6, 2(r5);     11 M rlwimi r7, r0, 8, 0x10, 0x17;        B clrlwi r7, r7, 0x10;     12 M rlwinm r8, r7, 8, 0x10, 0x17;        B rlwimi r6, r0, 8, 0x10, 0x17;     13 M rlwimi r8, r7, 0x18, 0x18, 0x1f;        B rlwinm r0, r6, 8, 0x10, 0x17;     14 M bne 8;        B rlwimi r0, r6, 0x18, 0x18, 0x1f;     15 M clrlwi r8, r7, 0x10;        B bne 8;     16 M clrlwi r7, r6, 0x10;        B clrlwi r0, r6, 0x10;     18 M bge 96;        B clrlwi r8, r0, 0x10;     19 M cmpwi r7, 0x11b;        B bge 100;     20 M beq 508;        B cmpwi r7, 0x11b;     21 M bge 48;        B beq 512;     22 M cmpwi r7, 0x111;        B bge 52;     23 M beqlr ;        B cmpwi r7, 0x111;     24 M bge 16;        B beqlr ;     25 M cmpwi r7, 0x103;        B bge 20;     26 M beqlr ;        B cmpwi r7, 0x103;     27 M blr ;        B beqlr ;     28 M cmpwi r7, 0x11a;        B bltlr ;     29 M bge 212;        B blr ;     30 M cmpwi r7, 0x113;        B cmpwi r7, 0x11a;     31 M bgelr ;        B bge 212;     32 M b 160;        B cmpwi r7, 0x113;     33 M cmpwi r7, 0x12d;        B bgelr ;     34 M beq 752;        B b 160;     35 M bge 16;        B cmpwi r7, 0x12d;     36 M cmpwi r7, 0x128;        B beq 752;     37 M beq 700;        B bge 16;     38 M blr ;        B cmpwi r7, 0x128;     39 M cmpwi r7, 0x132;        B beq 700;     40 M beq 988;        B blr ;     41 M blr ;        B cmpwi r7, 0x132;     42 M lis r6, 1;        B beq 988;     43 M addi r0, r6, -0x6eff;        B blr ;     44 M cmpw r7, r0;        B lis r6, 1;     45 M beq 1368;        B addi r0, r6, -0x6eff;     46 M bge 52;        B cmpw r7, r0;     47 M addi r0, r6, -0x7897;        B beq 1368;     48 M cmpw r7, r0;        B bge 52;     49 M beq 1248;        B addi r0, r6, -0x7897;     50 M bge 20;        B cmpw r7, r0;     51 M cmpwi r7, 0x213;        B beq 1248;     52 M beq 1196;        B bge 20;     53 M bgelr ;        B cmpwi r7, 0x213;     54 M blr ;        B beq 1196;     55 M addi r0, r6, -0x7000;        B bgelr ;     56 M cmpw r7, r0;        B blr ;     57 M beq 1284;        B addi r0, r6, -0x7000;     58 M blr ;        B cmpw r7, r0;     59 M addi r0, r6, -0x5ffe;        B beq 1284;     60 M cmpw r7, r0;        B blr ;     61 M beq 1416;        B addi r0, r6, -0x5ffe;     62 M bge 24;        B cmpw r7, r0;     63 M addi r0, r6, -0x6000;        B beq 1416;     64 M cmpw r7, r0;        B bge 24;     65 M beq 1324;        B addi r0, r6, -0x6000;     66 M bge 1356;        B cmpw r7, r0;     67 M blr ;        B beq 1324;     68 M addi r0, r6, -0x5ffc;        B bge 1356;     69 M cmpw r7, r0;        B blr ;     70 M bgelr ;        B addi r0, r6, -0x5ffc;     71 M b 1508;        B cmpw r7, r0;     72 M lbz r0, 9(r5);        B bgelr ;     73 M cmplwi r4, 0x4949;        B b 1504;     74 M lbz r4, 8(r5);        B lbz r0, 9(r5);     75 M rlwimi r4, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;     76 M rlwinm r0, r4, 8, 0x10, 0x17;        B lbz r4, 8(r5);     77 M rlwimi r0, r4, 0x18, 0x18, 0x1f;        B rlwimi r4, r0, 8, 0x10, 0x17;     78 M bne 8;        B rlwinm r0, r4, 8, 0x10, 0x17;     79 M clrlwi r0, r4, 0x10;        B rlwimi r0, r4, 0x18, 0x18, 0x1f;     80 M sth r0, 0xc(r3);        B bne 8;     81 M blr ;        B clrlwi r0, r4, 0x10;     82 M lbz r0, 9(r5);        B sth r0, 0xc(r3);     83 M cmplwi r4, 0x4949;        B blr ;     84 M lbz r7, 8(r5);        B lbz r0, 9(r5);     85 M rlwimi r7, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;     86 M lbz r6, 0xa(r5);        B lbz r7, 8(r5);     87 M lbz r0, 0xb(r5);        B rlwimi r7, r0, 8, 0x10, 0x17;     88 M rlwimi r7, r6, 0x10, 8, 0xf;        B lbz r6, 0xa(r5);     89 M rlwimi r7, r0, 0x18, 0, 7;        B lbz r0, 0xb(r5);     90 M bne 12;        B rlwimi r7, r6, 0x10, 8, 0xf;     91 M mr r6, r7;        B rlwimi r7, r0, 0x18, 0, 7;     92 M b 20;        B bne 12;     93 M rlwinm r6, r7, 0x18, 0x10, 0x17;        B mr r8, r7;     94 M rlwimi r6, r7, 8, 0x18, 0x1f;        B b 20;     95 M rlwimi r6, r7, 8, 8, 0xf;        B rlwinm r8, r7, 0x18, 0x10, 0x17;     96 M rlwimi r6, r7, 0x18, 0, 7;        B rlwimi r8, r7, 8, 0x18, 0x1f;     97 M lwz r0, 0x674(r3);        B rlwimi r8, r7, 8, 8, 0xf;     98 M add r8, r0, r6;        B rlwimi r8, r7, 0x18, 0, 7;     99 M cmplw r0, r8;        B lwz r0, 0x674(r3);    100 M bgtlr ;        B add r6, r0, r8;    101 M lwz r5, 0x678(r3);        B cmplw r0, r6;    102 M addi r0, r5, -4;        B bgtlr ;    103 M cmplw r8, r0;        B lwz r5, 0x678(r3);    104 M bgtlr ;        B addi r0, r5, -4;    105 M lbz r0, 1(r8);        B cmplw r6, r0;    106 M cmplwi r4, 0x4949;        B bgtlr ;    107 M lbz r7, 0(r8);        B lbz r0, 1(r6);    108 M rlwimi r7, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    109 M lbz r5, 2(r8);        B lbz r7, 0(r6);    110 M lbz r0, 3(r8);        B rlwimi r7, r0, 8, 0x10, 0x17;    111 M rlwimi r7, r5, 0x10, 8, 0xf;        B lbz r5, 2(r6);    112 M rlwimi r7, r0, 0x18, 0, 7;        B lbz r0, 3(r6);    113 M bne 12;        B rlwimi r7, r5, 0x10, 8, 0xf;    114 M mr r0, r7;        B rlwimi r7, r0, 0x18, 0, 7;    115 M b 20;        B bne 12;    116 M rlwinm r0, r7, 0x18, 0x10, 0x17;        B mr r0, r7;    117 M rlwimi r0, r7, 8, 0x18, 0x1f;        B b 20;    118 M rlwimi r0, r7, 8, 8, 0xf;        B rlwinm r0, r7, 0x18, 0x10, 0x17;    119 M rlwimi r0, r7, 0x18, 0, 7;        B rlwimi r0, r7, 8, 0x18, 0x1f;    120 M lwz r5, 0x674(r3);        B rlwimi r0, r7, 8, 8, 0xf;    121 M stw r0, 0x10(r3);        B rlwimi r0, r7, 0x18, 0, 7;    122 M add r6, r5, r6;        B lwz r7, 0x674(r3);    123 M addi r6, r6, 4;        B stw r0, 0x10(r3);    124 M cmplw r5, r6;        B add r5, r8, r7;    125 M bgtlr ;        B addi r6, r5, 4;    126 M lwz r5, 0x678(r3);        B cmplw r7, r6;    127 M addi r0, r5, -4;        B bgtlr ;    128 M cmplw r6, r0;        B lwz r5, 0x678(r3);    129 M bgtlr ;        B addi r0, r5, -4;    130 M lbz r0, 1(r6);        B cmplw r6, r0;    131 M cmplwi r4, 0x4949;        B bgtlr ;    132 M lbz r5, 0(r6);        B lbz r0, 1(r6);    133 M rlwimi r5, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    134 M lbz r4, 2(r6);        B lbz r5, 0(r6);    135 M lbz r0, 3(r6);        B rlwimi r5, r0, 8, 0x10, 0x17;    136 M rlwimi r5, r4, 0x10, 8, 0xf;        B lbz r4, 2(r6);    137 M rlwimi r5, r0, 0x18, 0, 7;        B lbz r0, 3(r6);    138 M bne 12;        B rlwimi r5, r4, 0x10, 8, 0xf;    139 M mr r0, r5;        B rlwimi r5, r0, 0x18, 0, 7;    140 M b 20;        B bne 12;    141 M rlwinm r0, r5, 0x18, 0x10, 0x17;        B mr r0, r5;    142 M rlwimi r0, r5, 8, 0x18, 0x1f;        B b 20;    143 M rlwimi r0, r5, 8, 8, 0xf;        B rlwinm r0, r5, 0x18, 0x10, 0x17;    144 M rlwimi r0, r5, 0x18, 0, 7;        B rlwimi r0, r5, 8, 0x18, 0x1f;    145 M stw r0, 0x14(r3);        B rlwimi r0, r5, 8, 8, 0xf;    146 M blr ;        B rlwimi r0, r5, 0x18, 0, 7;    147 M lbz r0, 9(r5);        B stw r0, 0x14(r3);    148 M cmplwi r4, 0x4949;        B blr ;    149 M lbz r7, 8(r5);        B lbz r0, 9(r5);    150 M rlwimi r7, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    151 M lbz r6, 0xa(r5);        B lbz r7, 8(r5);    152 M lbz r0, 0xb(r5);        B rlwimi r7, r0, 8, 0x10, 0x17;    153 M rlwimi r7, r6, 0x10, 8, 0xf;        B lbz r6, 0xa(r5);    154 M rlwimi r7, r0, 0x18, 0, 7;        B lbz r0, 0xb(r5);    155 M bne 12;        B rlwimi r7, r6, 0x10, 8, 0xf;    156 M mr r6, r7;        B rlwimi r7, r0, 0x18, 0, 7;    157 M b 20;        B bne 12;    158 M rlwinm r6, r7, 0x18, 0x10, 0x17;        B mr r8, r7;    159 M rlwimi r6, r7, 8, 0x18, 0x1f;        B b 20;    160 M rlwimi r6, r7, 8, 8, 0xf;        B rlwinm r8, r7, 0x18, 0x10, 0x17;    161 M rlwimi r6, r7, 0x18, 0, 7;        B rlwimi r8, r7, 8, 0x18, 0x1f;    162 M lwz r0, 0x674(r3);        B rlwimi r8, r7, 8, 8, 0xf;    163 M add r8, r0, r6;        B rlwimi r8, r7, 0x18, 0, 7;    164 M cmplw r0, r8;        B lwz r0, 0x674(r3);    165 M bgtlr ;        B add r6, r0, r8;    166 M lwz r5, 0x678(r3);        B cmplw r0, r6;    167 M addi r0, r5, -4;        B bgtlr ;    168 M cmplw r8, r0;        B lwz r5, 0x678(r3);    169 M bgtlr ;        B addi r0, r5, -4;    170 M lbz r0, 1(r8);        B cmplw r6, r0;    171 M cmplwi r4, 0x4949;        B bgtlr ;    172 M lbz r7, 0(r8);        B lbz r0, 1(r6);    173 M rlwimi r7, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    174 M lbz r5, 2(r8);        B lbz r7, 0(r6);    175 M lbz r0, 3(r8);        B rlwimi r7, r0, 8, 0x10, 0x17;    176 M rlwimi r7, r5, 0x10, 8, 0xf;        B lbz r5, 2(r6);    177 M rlwimi r7, r0, 0x18, 0, 7;        B lbz r0, 3(r6);    178 M bne 12;        B rlwimi r7, r5, 0x10, 8, 0xf;    179 M mr r0, r7;        B rlwimi r7, r0, 0x18, 0, 7;    180 M b 20;        B bne 12;    181 M rlwinm r0, r7, 0x18, 0x10, 0x17;        B mr r0, r7;    182 M rlwimi r0, r7, 8, 0x18, 0x1f;        B b 20;    183 M rlwimi r0, r7, 8, 8, 0xf;        B rlwinm r0, r7, 0x18, 0x10, 0x17;    184 M rlwimi r0, r7, 0x18, 0, 7;        B rlwimi r0, r7, 8, 0x18, 0x1f;    185 M lwz r5, 0x674(r3);        B rlwimi r0, r7, 8, 8, 0xf;    186 M stw r0, 0x18(r3);        B rlwimi r0, r7, 0x18, 0, 7;    187 M add r6, r5, r6;        B lwz r7, 0x674(r3);    188 M addi r6, r6, 4;        B stw r0, 0x18(r3);    189 M cmplw r5, r6;        B add r5, r8, r7;    190 M bgtlr ;        B addi r6, r5, 4;    191 M lwz r5, 0x678(r3);        B cmplw r7, r6;    192 M addi r0, r5, -4;        B bgtlr ;    193 M cmplw r6, r0;        B lwz r5, 0x678(r3);    194 M bgtlr ;        B addi r0, r5, -4;    195 M lbz r0, 1(r6);        B cmplw r6, r0;    196 M cmplwi r4, 0x4949;        B bgtlr ;    197 M lbz r5, 0(r6);        B lbz r0, 1(r6);    198 M rlwimi r5, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    199 M lbz r4, 2(r6);        B lbz r5, 0(r6);    200 M lbz r0, 3(r6);        B rlwimi r5, r0, 8, 0x10, 0x17;    201 M rlwimi r5, r4, 0x10, 8, 0xf;        B lbz r4, 2(r6);    202 M rlwimi r5, r0, 0x18, 0, 7;        B lbz r0, 3(r6);    203 M bne 12;        B rlwimi r5, r4, 0x10, 8, 0xf;    204 M mr r0, r5;        B rlwimi r5, r0, 0x18, 0, 7;    205 M b 20;        B bne 12;    206 M rlwinm r0, r5, 0x18, 0x10, 0x17;        B mr r0, r5;    207 M rlwimi r0, r5, 8, 0x18, 0x1f;        B b 20;    208 M rlwimi r0, r5, 8, 8, 0xf;        B rlwinm r0, r5, 0x18, 0x10, 0x17;    209 M rlwimi r0, r5, 0x18, 0, 7;        B rlwimi r0, r5, 8, 0x18, 0x1f;    210 M stw r0, 0x1c(r3);        B rlwimi r0, r5, 8, 8, 0xf;    211 M blr ;        B rlwimi r0, r5, 0x18, 0, 7;    212 M lbz r0, 9(r5);        B stw r0, 0x1c(r3);    213 M cmplwi r4, 0x4949;        B blr ;    214 M lbz r4, 8(r5);        B lbz r0, 9(r5);    215 M rlwimi r4, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    216 M rlwinm r0, r4, 8, 0x10, 0x17;        B lbz r4, 8(r5);    217 M rlwimi r0, r4, 0x18, 0x18, 0x1f;        B rlwimi r4, r0, 8, 0x10, 0x17;    218 M bne 8;        B rlwinm r0, r4, 8, 0x10, 0x17;    219 M clrlwi r0, r4, 0x10;        B rlwimi r0, r4, 0x18, 0x18, 0x1f;    220 M sth r0, 0x20(r3);        B bne 8;    221 M blr ;        B clrlwi r0, r4, 0x10;    222 M lbz r0, 9(r5);        B sth r0, 0x20(r3);    223 M cmplwi r4, 0x4949;        B blr ;    224 M lbz r7, 8(r5);        B lbz r0, 9(r5);    225 M rlwimi r7, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    226 M lbz r6, 0xa(r5);        B lbz r7, 8(r5);    227 M lbz r0, 0xb(r5);        B rlwimi r7, r0, 8, 0x10, 0x17;    228 M rlwimi r7, r6, 0x10, 8, 0xf;        B lbz r6, 0xa(r5);    229 M rlwimi r7, r0, 0x18, 0, 7;        B lbz r0, 0xb(r5);    230 M bne 12;        B rlwimi r7, r6, 0x10, 8, 0xf;    231 M mr r9, r7;        B rlwimi r7, r0, 0x18, 0, 7;    232 M b 20;        B bne 12;    233 M rlwinm r9, r7, 0x18, 0x10, 0x17;        B mr r9, r7;    234 M rlwimi r9, r7, 8, 0x18, 0x1f;        B b 20;    235 M rlwimi r9, r7, 8, 8, 0xf;        B rlwinm r9, r7, 0x18, 0x10, 0x17;    236 M rlwimi r9, r7, 0x18, 0, 7;        B rlwimi r9, r7, 8, 0x18, 0x1f;    237 M mr r7, r3;        B rlwimi r9, r7, 8, 8, 0xf;    238 M li r10, 0;        B rlwimi r9, r7, 0x18, 0, 7;    239 M li r0, 0x80;        B mr r7, r3;    240 M mr r8, r7;        B li r10, 0;    241 M li r11, 0;        B li r0, 0x80;    242 M mtctr r0;        B mr r8, r7;    243 M lwz r5, 0x674(r3);        B li r11, 0;    244 M add r6, r5, r9;        B mtctr r0;    245 M cmplw r5, r6;        B lwz r5, 0x674(r3);    246 M bgt 144;        B add r6, r5, r9;    247 M lwz r5, 0x678(r3);        B cmplw r5, r6;    248 M addi r5, r5, -2;        B bgt 144;    249 M cmplw r6, r5;        B lwz r5, 0x678(r3);    250 M bgt 128;        B addi r5, r5, -2;    251 M lbz r5, 1(r6);        B cmplw r6, r5;    252 M cmplwi r4, 0x4949;        B bgt 128;    253 M lbz r6, 0(r6);        B lbz r5, 1(r6);    254 M rlwimi r6, r5, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    255 M rlwinm r5, r6, 8, 0x10, 0x17;        B lbz r6, 0(r6);    256 M rlwimi r5, r6, 0x18, 0x18, 0x1f;        B rlwimi r6, r5, 8, 0x10, 0x17;    257 M bne 8;        B rlwinm r5, r6, 8, 0x10, 0x17;    258 M clrlwi r5, r6, 0x10;        B rlwimi r5, r6, 0x18, 0x18, 0x1f;    259 M sth r5, 0x22(r8);        B bne 8;    260 M addi r9, r9, 2;        B clrlwi r5, r6, 0x10;    261 M lwz r5, 0x674(r3);        B sth r5, 0x22(r8);    262 M add r6, r5, r9;        B addi r9, r9, 2;    263 M cmplw r5, r6;        B lwz r5, 0x674(r3);    264 M bgt 72;        B add r6, r5, r9;    265 M lwz r5, 0x678(r3);        B cmplw r5, r6;    266 M addi r5, r5, -2;        B bgt 72;    267 M cmplw r6, r5;        B lwz r5, 0x678(r3);    268 M bgt 56;        B addi r5, r5, -2;    269 M lbz r5, 1(r6);        B cmplw r6, r5;    270 M cmplwi r4, 0x4949;        B bgt 56;    271 M lbz r6, 0(r6);        B lbz r5, 1(r6);    272 M rlwimi r6, r5, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    273 M rlwinm r5, r6, 8, 0x10, 0x17;        B lbz r6, 0(r6);    274 M rlwimi r5, r6, 0x18, 0x18, 0x1f;        B rlwimi r6, r5, 8, 0x10, 0x17;    275 M bne 8;        B rlwinm r5, r6, 8, 0x10, 0x17;    276 M clrlwi r5, r6, 0x10;        B rlwimi r5, r6, 0x18, 0x18, 0x1f;    277 M sth r5, 0x24(r8);        B bne 8;    278 M addi r9, r9, 2;        B clrlwi r5, r6, 0x10;    279 M addi r8, r8, 4;        B sth r5, 0x24(r8);    280 M addi r11, r11, 1;        B addi r9, r9, 2;    281 M bdnz -152;        B addi r8, r8, 4;    282 M addi r10, r10, 1;        B addi r11, r11, 1;    283 M addi r7, r7, 0x200;        B bdnz -152;    284 M cmplwi r10, 3;        B addi r10, r10, 1;    285 M blt -180;        B addi r7, r7, 0x200;    286 M blr ;        B cmplwi r10, 3;    287 M lbz r0, 9(r5);        B blt -180;    288 M cmplwi r4, 0x4949;        B blr ;    289 M lbz r6, 8(r5);        B lbz r0, 9(r5);    290 M rlwimi r6, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    291 M lbz r4, 0xa(r5);        B lbz r6, 8(r5);    292 M lbz r0, 0xb(r5);        B rlwimi r6, r0, 8, 0x10, 0x17;    293 M rlwimi r6, r4, 0x10, 8, 0xf;        B lbz r4, 0xa(r5);    294 M rlwimi r6, r0, 0x18, 0, 7;        B lbz r0, 0xb(r5);    295 M bne 12;        B rlwimi r6, r4, 0x10, 8, 0xf;    296 M mr r0, r6;        B rlwimi r6, r0, 0x18, 0, 7;    297 M b 20;        B bne 12;    298 M rlwinm r0, r6, 0x18, 0x10, 0x17;        B mr r0, r6;    299 M rlwimi r0, r6, 8, 0x18, 0x1f;        B b 20;    300 M rlwimi r0, r6, 8, 8, 0xf;        B rlwinm r0, r6, 0x18, 0x10, 0x17;    301 M rlwimi r0, r6, 0x18, 0, 7;        B rlwimi r0, r6, 8, 0x18, 0x1f;    302 M lwz r4, 0x674(r3);        B rlwimi r0, r6, 8, 8, 0xf;    303 M add r5, r4, r0;        B rlwimi r0, r6, 0x18, 0, 7;    304 M cmplw r4, r5;        B lwz r4, 0x674(r3);    305 M bgtlr ;        B add r5, r4, r0;    306 M lwz r4, 0x678(r3);        B cmplw r4, r5;    307 M addi r0, r4, -0x14;        B bgtlr ;    308 M cmplw r5, r0;        B lwz r4, 0x678(r3);    309 M bgtlr ;        B addi r0, r4, -0x14;    310 M lbz r0, 0(r5);        B cmplw r5, r0;    311 M stb r0, 0x622(r3);        B bgtlr ;    312 M lbz r0, 1(r5);        B lbz r0, 0(r5);    313 M stb r0, 0x623(r3);        B stb r0, 0x622(r3);    314 M lbz r0, 2(r5);        B lbz r0, 1(r5);    315 M stb r0, 0x624(r3);        B stb r0, 0x623(r3);    316 M lbz r0, 3(r5);        B lbz r0, 2(r5);    317 M stb r0, 0x625(r3);        B stb r0, 0x624(r3);    318 M lbz r0, 4(r5);        B lbz r0, 3(r5);    319 M stb r0, 0x626(r3);        B stb r0, 0x625(r3);    320 M lbz r0, 5(r5);        B lbz r0, 4(r5);    321 M stb r0, 0x627(r3);        B stb r0, 0x626(r3);    322 M lbz r0, 6(r5);        B lbz r0, 5(r5);    323 M stb r0, 0x628(r3);        B stb r0, 0x627(r3);    324 M lbz r0, 7(r5);        B lbz r0, 6(r5);    325 M stb r0, 0x629(r3);        B stb r0, 0x628(r3);    326 M lbz r0, 8(r5);        B lbz r0, 7(r5);    327 M stb r0, 0x62a(r3);        B stb r0, 0x629(r3);    328 M lbz r0, 9(r5);        B lbz r0, 8(r5);    329 M stb r0, 0x62b(r3);        B stb r0, 0x62a(r3);    330 M lbz r0, 0xa(r5);        B lbz r0, 9(r5);    331 M stb r0, 0x62c(r3);        B stb r0, 0x62b(r3);    332 M lbz r0, 0xb(r5);        B lbz r0, 0xa(r5);    333 M stb r0, 0x62d(r3);        B stb r0, 0x62c(r3);    334 M lbz r0, 0xc(r5);        B lbz r0, 0xb(r5);    335 M stb r0, 0x62e(r3);        B stb r0, 0x62d(r3);    336 M lbz r0, 0xd(r5);        B lbz r0, 0xc(r5);    337 M stb r0, 0x62f(r3);        B stb r0, 0x62e(r3);    338 M lbz r0, 0xe(r5);        B lbz r0, 0xd(r5);    339 M stb r0, 0x630(r3);        B stb r0, 0x62f(r3);    340 M lbz r0, 0xf(r5);        B lbz r0, 0xe(r5);    341 M stb r0, 0x631(r3);        B stb r0, 0x630(r3);    342 M lbz r0, 0x10(r5);        B lbz r0, 0xf(r5);    343 M stb r0, 0x632(r3);        B stb r0, 0x631(r3);    344 M lbz r0, 0x11(r5);        B lbz r0, 0x10(r5);    345 M stb r0, 0x633(r3);        B stb r0, 0x632(r3);    346 M lbz r0, 0x12(r5);        B lbz r0, 0x11(r5);    347 M stb r0, 0x634(r3);        B stb r0, 0x633(r3);    348 M lbz r0, 0x13(r5);        B lbz r0, 0x12(r5);    349 M stb r0, 0x635(r3);        B stb r0, 0x634(r3);    350 M blr ;        B lbz r0, 0x13(r5);    351 M lbz r0, 9(r5);        B stb r0, 0x635(r3);    352 M cmplwi r4, 0x4949;        B blr ;    353 M lbz r4, 8(r5);        B lbz r0, 9(r5);    354 M rlwimi r4, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    355 M rlwinm r0, r4, 8, 0x10, 0x17;        B lbz r4, 8(r5);    356 M rlwimi r0, r4, 0x18, 0x18, 0x1f;        B rlwimi r4, r0, 8, 0x10, 0x17;    357 M bne 8;        B rlwinm r0, r4, 8, 0x10, 0x17;    358 M clrlwi r0, r4, 0x10;        B rlwimi r0, r4, 0x18, 0x18, 0x1f;    359 M sth r0, 0x636(r3);        B bne 8;    360 M blr ;        B clrlwi r0, r4, 0x10;    361 M lbz r0, 9(r5);        B sth r0, 0x636(r3);    362 M cmplwi r4, 0x4949;        B blr ;    363 M lbz r6, 8(r5);        B lbz r0, 9(r5);    364 M rlwimi r6, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    365 M lbz r4, 0xa(r5);        B lbz r6, 8(r5);    366 M lbz r0, 0xb(r5);        B rlwimi r6, r0, 8, 0x10, 0x17;    367 M rlwimi r6, r4, 0x10, 8, 0xf;        B lbz r4, 0xa(r5);    368 M rlwimi r6, r0, 0x18, 0, 7;        B lbz r0, 0xb(r5);    369 M bne 12;        B rlwimi r6, r4, 0x10, 8, 0xf;    370 M mr r0, r6;        B rlwimi r6, r0, 0x18, 0, 7;    371 M b 20;        B bne 12;    372 M rlwinm r0, r6, 0x18, 0x10, 0x17;        B mr r0, r6;    373 M rlwimi r0, r6, 8, 0x18, 0x1f;        B b 20;    374 M rlwimi r0, r6, 8, 8, 0xf;        B rlwinm r0, r6, 0x18, 0x10, 0x17;    375 M rlwimi r0, r6, 0x18, 0, 7;        B rlwimi r0, r6, 8, 0x18, 0x1f;    376 M stw r0, 0x638(r3);        B rlwimi r0, r6, 8, 8, 0xf;    377 M blr ;        B rlwimi r0, r6, 0x18, 0, 7;    378 M lbz r7, 8(r5);        B stw r0, 0x638(r3);    379 M lbz r6, 9(r5);        B blr ;    380 M lbz r4, 0xa(r5);        B lbz r0, 8(r5);    381 M lbz r0, 0xb(r5);        B stb r0, 0x63c(r3);    382 M stb r7, 0x63c(r3);        B lbz r0, 9(r5);    383 M stb r6, 0x63d(r3);        B stb r0, 0x63d(r3);    384 M stb r4, 0x63e(r3);        B lbz r0, 0xa(r5);    385 M stb r0, 0x63f(r3);        B stb r0, 0x63e(r3);    386 M blr ;        B lbz r0, 0xb(r5);    387 M lbz r7, 8(r5);        B stb r0, 0x63f(r3);    388 M lbz r6, 9(r5);        B blr ;    389 M lbz r4, 0xa(r5);        B lbz r0, 8(r5);    390 M lbz r0, 0xb(r5);        B stb r0, 0x640(r3);    391 M stb r7, 0x640(r3);        B lbz r0, 9(r5);    392 M stb r6, 0x641(r3);        B stb r0, 0x641(r3);    393 M stb r4, 0x642(r3);        B lbz r0, 0xa(r5);    394 M stb r0, 0x643(r3);        B stb r0, 0x642(r3);    395 M blr ;        B lbz r0, 0xb(r5);    396 M lbz r7, 8(r5);        B stb r0, 0x643(r3);    397 M lbz r6, 9(r5);        B blr ;    398 M lbz r4, 0xa(r5);        B lbz r0, 8(r5);    399 M lbz r0, 0xb(r5);        B stb r0, 0x644(r3);    400 M stb r7, 0x644(r3);        B lbz r0, 9(r5);    401 M stb r6, 0x645(r3);        B stb r0, 0x645(r3);    402 M stb r4, 0x646(r3);        B lbz r0, 0xa(r5);    403 M stb r0, 0x647(r3);        B stb r0, 0x646(r3);    404 M blr ;        B lbz r0, 0xb(r5);    405 M lbz r0, 9(r5);        B stb r0, 0x647(r3);    406 M cmplwi r4, 0x4949;        B blr ;    407 M lbz r4, 8(r5);        B lbz r0, 9(r5);    408 M rlwimi r4, r0, 8, 0x10, 0x17;        B cmplwi r4, 0x4949;    409 M rlwinm r0, r4, 8, 0x10, 0x17;        B lbz r4, 8(r5);    410 M rlwimi r0, r4, 0x18, 0x18, 0x1f;        B rlwimi r4, r0, 8, 0x10, 0x17;    411 M bne 8;        B rlwinm r0, r4, 8, 0x10, 0x17;    412 M clrlwi r0, r4, 0x10;        B rlwimi r0, r4, 0x18, 0x18, 0x1f;    413 M sth r0, 0x648(r3);        B bne 8;    414 M blr ;        B clrlwi r0, r4, 0x10;    415 M clrlwi r0, r8, 0x10;        B sth r0, 0x648(r3);    416 M cmplwi r0, 3;        B blr ;    417 M bne 48;        B cmplwi r8, 3;    418 M lbz r0, 9(r5);        B bne 48;    419 M cmplwi r4, 0x4949;        B lbz r0, 9(r5);    420 M lbz r4, 8(r5);        B cmplwi r4, 0x4949;    421 M rlwimi r4, r0, 8, 0x10, 0x17;        B lbz r4, 8(r5);    422 M rlwinm r0, r4, 8, 0x10, 0x17;        B rlwimi r4, r0, 8, 0x10, 0x17;    423 M rlwimi r0, r4, 0x18, 0x18, 0x1f;        B rlwinm r0, r4, 8, 0x10, 0x17;    424 M bne 8;        B rlwimi r0, r4, 0x18, 0x18, 0x1f;    425 M clrlwi r0, r4, 0x10;        B bne 8;    426 M clrlwi r0, r0, 0x10;        B clrlwi r0, r4, 0x10;    427 M stw r0, 0x64c(r3);        B clrlwi r0, r0, 0x10;    428 M blr ;        B stw r0, 0x64c(r3);    429 M cmplwi r0, 4;        B blr ;    430 M bnelr ;        B cmplwi r8, 4;    431 M lbz r0, 9(r5);        B bnelr ;    432 M cmplwi r4, 0x4949;        B lbz r0, 9(r5);    433 M lbz r6, 8(r5);        B cmplwi r4, 0x4949;    434 M rlwimi r6, r0, 8, 0x10, 0x17;        B lbz r6, 8(r5);    435 M lbz r4, 0xa(r5);        B rlwimi r6, r0, 8, 0x10, 0x17;    436 M lbz r0, 0xb(r5);        B lbz r4, 0xa(r5);    437 M rlwimi r6, r4, 0x10, 8, 0xf;        B lbz r0, 0xb(r5);    438 M rlwimi r6, r0, 0x18, 0, 7;        B rlwimi r6, r4, 0x10, 8, 0xf;    439 M bne 12;        B rlwimi r6, r0, 0x18, 0, 7;    440 M mr r0, r6;        B bne 12;    441 M b 20;        B mr r0, r6;    442 M rlwinm r0, r6, 0x18, 0x10, 0x17;        B b 20;    443 M rlwimi r0, r6, 8, 0x18, 0x1f;        B rlwinm r0, r6, 0x18, 0x10, 0x17;    444 M rlwimi r0, r6, 8, 8, 0xf;        B rlwimi r0, r6, 8, 0x18, 0x1f;    445 M rlwimi r0, r6, 0x18, 0, 7;        B rlwimi r0, r6, 8, 8, 0xf;    446 M stw r0, 0x64c(r3);        B rlwimi r0, r6, 0x18, 0, 7;    447 M blr ;        B stw r0, 0x64c(r3);    448 M clrlwi r0, r8, 0x10;        B blr ;    449 M cmplwi r0, 3;        B cmplwi r8, 3;    462 M cmplwi r0, 4;        B cmplwi r8, 4;

### TMCJPEGDEC_IFD1_tag_parse
Fetched origin; source equals origin baseline where function is still below100.
Initial ctxdiff: src 0x3bc base 0x3c8 insns 239/242; --- replace mine 9:11 base 9:11;   M    9 cmpwi r7, 0x201;   M   10 beq 780;   B    9 cmpwi r7, 0x132;   B   10 beqlr ; --- replace mine 12:14 base 12:14;   M   12 cmpwi r7, 0x11b;   M   13 beq 428;   B   12 cmpwi r7, 0x11a;   B   13 beq 180; --- insert mine 16:16 base 16:25;   B   16 beqlr ;   B   17 bgelr ;   B   18 cmpwi r7, 0x103;   B   19 beq 716;   B   20 bltlr ;   B   21 blr ;   B   22 blr ;   B   23 cmpwi r7, 0x128;   B   24 beq 656; --- replace mine 17:23 base 26:29;   M   17 cmpwi r7, 0x103;   M   18 beq 708;   M   19 blr ;   M   20 cmpwi r7, 0x11a;   M   21 bge 136;   M   22 blr ;   B   26 cmpwi r7, 0x11c;   B   27 bgelr ;   B   28 b 380; --- delete mine 24:30 base 30:30;   M   24 beqlr ;   M   25 bge 16;   M   26 cmpwi r7, 0x128;   M   27 beq 632;   M   28 blr ;   M   29 cmpwi r7, 0x132; --- insert mine 33:33 base 33:50;   B   33 addi r0, r6, -0x7897;   B   34 cmpw r7, r0;   B   35 beqlr ;   B   36 bge 40;   B   37 cmpwi r7, 0x202;   B   38 beq 748;   B   39 bge 16;   B   40 cmpwi r7, 0x201;   B   41 bge 668;   B   42 blr ;   B   43 cmpwi r7, 0x213;   B   44 beqlr ;   B   45 blr ;   B   46 addi r0, r6, -0x6eff;   B   47 cmpw r7, r0;   B   48 beqlr ;   B   49 bge 20; --- replace mine 36:41 base 53:56;   M   36 bge 44;   M   37 cmpwi r7, 0x213;   M   38 beqlr ;   M   39 bge 16;   M   40 cmpwi r7, 0x203;   B   53 blr ;   B   54 addi r0, r6, -0x5ffc;   B   55 cmpw r7, r0; --- delete mine 42:54 base 57:57;   M   42 b 720;   M   43 addi r0, r6, -0x7897;   M   44 cmpw r7, r0;   M   45 beqlr ;   M   46 blr ;   M   47 addi r0, r6, -0x5ffd;   M   48 cmpw r7, r0;   M   49 beqlr ;   M   50 bgelr ;   M   51 addi r0, r6, -0x6eff;   M   52 cmpw r7, r0;   M   53 beqlr ; --- replace mine 64:65 base 67:68;   M   64 mr r6, r7;   B   67 mr r8, r7; --- replace mine 66:70 base 69:73;   M   66 rlwinm r6, r7, 0x18, 0x10, 0x17;   M   67 rlwimi r6, r7, 8, 0x18, 0x1f;   M   68 rlwimi r6, r7, 8, 8, 0xf;   M   69 rlwimi r6, r7, 0x18, 0, 7;   B   69 rlwinm r8, r7, 0x18, 0x10, 0x17;   B   70 rlwimi r8, r7, 8, 0x18, 0x1f;   B   71 rlwimi r8, r7, 8, 8, 0xf;   B   72 rlwimi r8, r7, 0x18, 0, 7; --- replace mine 71:73 base 74:76;   M   71 add r8, r0, r6;   M   72 cmplw r0, r8;   B   74 add r6, r0, r8;   B   75 cmplw r0, r6; --- replace mine 76:77 base 79:80;   M   76 cmplw r8, r0;   B   79 cmplw r6, r0; --- replace mine 78:79 base 81:82;   M   78 lbz r0, 1(r8);   B   81 lbz r0, 1(r6); --- replace mine 80:81 base 83:84;   M   80 lbz r7, 0(r8);   B   83 lbz r7, 0(r6); --- replace mine 82:84 base 85:87;   M   82 lbz r5, 2(r8);   M   83 lbz r0, 3(r8);   B   85 lbz r5, 2(r6);   B   86 lbz r0, 3(r6); --- replace mine 93:94 base 96:97;   M   93 lwz r5, 0x674(r3);   B   96 lwz r7, 0x674(r3); --- replace mine 95:98 base 98:101;   M   95 add r6, r5, r6;   M   96 addi r6, r6, 4;   M   97 cmplw r5, r6;   B   98 add r5, r8, r7;   B   99 addi r6, r5, 4;   B  100 cmplw r7, r6; --- replace mine 129:130 base 132:133;   M  129 mr r6, r7;   B  132 mr r8, r7; --- replace mine 131:135 base 134:138;   M  131 rlwinm r6, r7, 0x18, 0x10, 0x17;   M  132 rlwimi r6, r7, 8, 0x18, 0x1f;   M  133 rlwimi r6, r7, 8, 8, 0xf;   M  134 rlwimi r6, r7, 0x18, 0, 7;   B  134 rlwinm r8, r7, 0x18, 0x10, 0x17;   B  135 rlwimi r8, r7, 8, 0x18, 0x1f;   B  136 rlwimi r8, r7, 8, 8, 0xf;   B  137 rlwimi r8, r7, 0x18, 0, 7; --- replace mine 136:138 base 139:141;   M  136 add r8, r0, r6;   M  137 cmplw r0, r8;   B  139 add r6, r0, r8;   B  140 cmplw r0, r6; --- replace mine 141:142 base 144:145;   M  141 cmplw r8, r0;   B  144 cmplw r6, r0; --- replace mine 143:144 base 146:147;   M  143 lbz r0, 1(r8);   B  146 lbz r0, 1(r6); --- replace mine 145:146 base 148:149;   M  145 lbz r7, 0(r8);   B  148 lbz r7, 0(r6); --- replace mine 147:149 base 150:152;   M  147 lbz r5, 2(r8);   M  148 lbz r0, 3(r8);   B  150 lbz r5, 2(r6);   B  151 lbz r0, 3(r6); --- replace mine 158:159 base 161:162;   M  158 lwz r5, 0x674(r3);   B  161 lwz r7, 0x674(r3); --- replace mine 160:163 base 163:166;   M  160 add r6, r5, r6;   M  161 addi r6, r6, 4;   M  162 cmplw r5, r6;   B  163 add r5, r8, r7;   B  164 addi r6, r5, 4;   B  165 cmplw r7, r6;
Structural diagnosis84/81, extra saved r28 and cached intermediate candidate-array base. Target carries one global-array base and computes offsets at each use. Test ordinary pointer expression/helper boundary; do not aggregate or pin globals.
- clearCandidates__Q39textinput8tistring6WithZiFv: candidate pointer expression uses address-of indexed element: ((12, 80), 84, 81) -> ((12, 80), 84, 81); restored
- clearCandidates__Q39textinput8tistring6WithZiFv: candidate output cast passes through void pointer: ((12, 80), 84, 81) -> ((12, 80), 84, 81); restored
- clearCandidates__Q39textinput8tistring6WithZiFv: candidate output pointer scoped to search initialization: ((12, 80), 84, 81) -> ((12, 80), 84, 81); restored
Structural diagnosis447/446: candidate output pointer cached before initial calls, target materializes in search fields; saved register group shifts. Some Korean candidate loops/source order also differ. Remove early alias first.
- update__Q39textinput8tistring6WithZiFv: candidate output calculated at use sites instead of early cached alias: ((61, 428), 447, 446) -> ((61, 380), 448, 446); kept
- update__Q39textinput8tistring6WithZiFv: read-only holding-key descriptor: ((61, 380), 448, 446) -> ((61, 380), 448, 446); restored
- update__Q39textinput8tistring6WithZiFv: signed candidate count separate from API bitmask result: ((61, 380), 448, 446) -> ((62, 380), 448, 446); restored
Structural diagnosis65/65 frame0x20: base setup/load order differs, saved element/candidate pointers and count registers. Pointer declarations moved before clears; cached indexed character introduced.
- setElementBuffer__Q39textinput8tistring6WithZiFv: buffer pointers bound before memset calls: ((5, 22), 65, 65) -> ((7, 21), 65, 65); restored
- setElementBuffer__Q39textinput8tistring6WithZiFv: const input candidate view after clearing: ((5, 22), 65, 65) -> ((5, 22), 65, 65); restored
- setElementBuffer__Q39textinput8tistring6WithZiFv: named loop index declared before loop and reused: ((5, 22), 65, 65) -> ((5, 22), 65, 65); restored

SDMemory updateState nominal100 audit: raw target/source function bytes identical=True. ctxdiff two bgt operand differences are offset-dependent disassembly artifacts for identical words 41850474 and 418500bc, not code work. Objdiff100 function is already byte-exact; gate instruction count63 instead of64 records this tool limitation.
Structural diagnosis: leaf no frame; switch dispatch tree differs (IFD0 extra bltlr and scheduling,IFD1 three missing instructions). Tag promotion/type and inline read helper variable lifetimes tested before registers.
- TMCJPEGDEC_IFD0_tag_parse: switch tag promoted to signed32 at declaration: ((29, 446), 481, 481) -> ((27, 446), 481, 481); kept
- TMCJPEGDEC_IFD0_tag_parse: const EXIF data view for bounds/base reads: ((27, 446), 481, 481) -> compile failure; restored
- TMCJPEGDEC_IFD0_tag_parse: two-byte helper separates shifted high byte before OR: ((27, 446), 481, 481) -> ((27, 446), 481, 481); restored
Structural diagnosis: leaf no frame; switch dispatch tree differs (IFD0 extra bltlr and scheduling,IFD1 three missing instructions). Tag promotion/type and inline read helper variable lifetimes tested before registers.
- TMCJPEGDEC_IFD1_tag_parse: switch tag promoted to signed32 at declaration: ((59, 222), 239, 242) -> ((59, 222), 239, 242); restored
- TMCJPEGDEC_IFD1_tag_parse: const EXIF data view for bounds/base reads: ((59, 222), 239, 242) -> ((59, 222), 239, 242); restored
- TMCJPEGDEC_IFD1_tag_parse: two-byte helper separates shifted high byte before OR: ((59, 222), 239, 242) -> ((59, 222), 239, 242); restored
- TMCJPEGDEC_exif_parse: Exif scalar reader mutable byte view: ((0, 43), 212, 212) -> ((0, 43), 212, 212); restored
- TMCJPEGDEC_exif_parse: Exif reader byte assembly plain declaration then assignment: ((0, 43), 212, 212) -> ((0, 43), 212, 212); restored
- TMCJPEGDEC_exif_parse: Exif reader separate return value selected by byte order: ((0, 43), 212, 212) -> ((0, 43), 212, 212); restored
- AOSSi_WLANGetBSSList: result success assigned before descriptor loop for lifetime reuse: ((76, 169), 226, 227) -> ((76, 170), 226, 227); restored
- AOSSi_WLANGetBSSList: const descriptor view for access-point fields: ((76, 169), 226, 227) -> ((76, 169), 226, 227); restored
- AOSSi_WLANGetBSSList: separate signed scan result initialized before scan: ((76, 169), 226, 227) -> ((76, 169), 226, 227); restored
- AOSSi_WLANConnect: const connected configuration view declared at status block entry: ((4, 83), 156, 155) -> ((4, 83), 156, 155); restored
- AOSSi_WLANConnect: cached final SSID length declared at status block entry: ((4, 83), 156, 155) -> ((4, 71), 155, 155); kept
- AOSSi_WLANConnect: result initialization immediately before NCDSetIpConfig: ((4, 71), 155, 155) -> ((2, 47), 155, 155); kept
Structural diagnosis1060/1064: true SetVisible calls should inline clear/set-bit operations, false remains out-of-line; remaining pool/parameter registers differ. All strings identical. Try real pane locals, bool argument expression and count helper scope.
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: visible pane local binding before true setter: ((14, 617), 1060, 1064) -> ((0, 179), 1064, 1064); kept
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: boolean visibility argument explicitly formed from integer: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: title cache view mutable for read-only loop fields: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
Structural diagnosis439/451 frame0x140: target position local0x70 vs source0x68, duplicate initial newline check and bottom-tested line rendering; colors copied bytewise target while source word-alias copies differ. No immediate same-slot stw/lwz proof for volatile.
- drawTransferTitles__Q33ipl5scene8SDMemoryFv: message newline count scoped after first message call: ((162, 404), 439, 451) -> ((159, 386), 441, 451); kept
- drawTransferTitles__Q33ipl5scene8SDMemoryFv: header line rendering uses explicit for loop condition: ((159, 386), 441, 451) -> ((161, 386), 441, 451); restored
- drawTransferTitles__Q33ipl5scene8SDMemoryFv: typed GXColor constructors replace word reinterpret views: ((159, 386), 441, 451) -> ((145, 388), 423, 451); kept
- AOSSi_WLANConnect: result zero at IP configuration after cached SSID graph change: ((2, 47), 155, 155) -> ((2, 2), 155, 155); kept
- AOSSi_WLANConnect: register-only declaration search after structural attempts ((2, 2), 155, 155) -> ((2, 2), 155, 155); order was:
- ConvertDaysToDate: inline leap flag u32 with const month read view: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- ConvertDaysToDate: inline leap flag u8 with const month read view: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- ConvertDaysToDate: inline leap flag u16 with const month read view: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- AOSSi_WLANConnect: IP memset size uses concrete object type: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: IP memset size local initialized before configuration binding: ((2, 2), 155, 155) -> ((2, 3), 155, 155); restored
- AOSSi_WLANConnect: IP clearing uses concrete global address instead of alias: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: IP memset input pointer expressed as byte view: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- TMCJPEGDEC_IFD0_tag_parse: const bounds view with signed tag leading declaration: ((27, 446), 481, 481) -> ((27, 446), 481, 481); restored
- TMCJPEGDEC_IFD0_tag_parse: tag type checked as promoted signed integer: ((27, 446), 481, 481) -> ((27, 474), 480, 481); restored

Mid-gate passed but fuzzy audit restored early candidate-output change in tiZiString (91.4305 below91.70852) and constructor/color changes in drawTransferTitles (89.1286 below92.7694). Retained create99.13064 and other non-regressing partial improvements only.
- AOSSi_WLANConnect: inline IP clearing helper owns pointer/size argument evaluation: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: const IP pointer binding scoped to configuration and API call: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: IP clear size computed through named constant binding: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: text-box declaration separated and placed before initial layout construction: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: each main-layout text box gets a distinct pointer lifetime: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: inline dialog text helper groups pane lookup and message setting: ((0, 179), 1064, 1064) -> ((267, 939), 802, 1064); restored
- AOSSi_WLANConnect: full leading declaration block including aligned info and config pointers, order was:
- AOSSi_WLANConnect: prior range finder extended past declarations because there was no blank. Interrupted with source restored; corrected range contains exactly five declarations, including aligned info and config pointers: order was:
- ConvertDaysToDate: const month scalar initialized from const pointer binding: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: month value declared with initializer after previous-days declaration: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- ConvertDaysToDate: leap helper returns u8 instead of signed Boolean: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- ConvertDaysToDate: leap helper returns u32 instead of signed Boolean: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
New structural type proof: target allocates(count-1)*0x54+0x58; writes list-relative beacon0x50/mode0x54 after rates0x40. Therefore access-point rates have16 bytes rather than12; actual object sizeof0x54, no dummy/padding object. Check peer type read-only before change.
- AOSSi_WLANGetBSSList: access-point rates array extent sixteen per target beacon/mode offsets: ((76, 169), 226, 227) -> ((72, 167), 226, 227); kept
- AOSSi_WLANGetBSSList: pointer NULL comparisons use boolean tests like callbacks: ((72, 167), 226, 227) -> ((58, 147), 226, 227); kept
- AOSSi_WLANGetBSSList: descriptor fields re-evaluate access-point receiver after calls: ((58, 147), 226, 227) -> ((35, 114), 228, 227); kept
- AOSSi_WLANGetBSSList: cleanup and unlock expressed as condition-tested retry loops: ((35, 114), 228, 227) -> ((11, 113), 228, 227); kept
- AOSSi_WLANGetBSSList: scan result buffer typed as const descriptor after scan: ((11, 113), 228, 227) -> ((11, 113), 228, 227); restored
- ConvertDaysToDate: year-loop common leap flag u8 separates zero lifetime: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- ConvertDaysToDate: year-loop common leap flag u32 separates zero lifetime: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- ConvertDaysToDate: year-loop immutable previous-day snapshot: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- ConvertDaysToDate: month-loop immutable previous-day snapshot initializer: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- setElementBuffer__Q39textinput8tistring6WithZiFv: register-only declaration search after structural attempts ((5, 18), 65, 65) -> ((5, 18), 65, 65); order was:
- setElementBuffer__Q39textinput8tistring6WithZiFv: leading plain buffer/input declarations followed by100-build register search ((5, 22), 65, 65) ->((5, 18), 65, 65); kept
- clearCandidates__Q39textinput8tistring6WithZiFv: candidate-array base named const pointer binding for clear/search setup: ((12, 80), 84, 81) -> ((9, 76), 84, 81); kept
- update__Q39textinput8tistring6WithZiFv: candidate-output pointer binding declared const: ((61, 428), 447, 446) -> ((61, 428), 447, 446); restored
- AOSSi_WLANGetBSSList: full10 declaration search including real aligned scan/info and mac buffer, (11, 109) after 145 builds; kept in source:
- NWC24SetMsgSubjectAndTextPublic: register-only declaration search after structural attempts ((0, 65), 190, 190) -> ((0, 65), 190, 190); order was:
- NWC24iSetMsgSubjectBase64: register-only declaration search after structural attempts ((0, 5), 136, 136) -> ((0, 5), 136, 136); order was:
- NWC24iDateToOSCalendarTime: register-only declaration search after structural attempts ((0, 13), 85, 85) -> ((0, 13), 85, 85); order was:
- ConvertDateToDays: register-only declaration search after structural attempts ((4, 16), 113, 113) -> ((4, 16), 113, 113); order was:
- AOSSi_WLANGetBSSList: rate count initialized after both descriptor memcpy calls: ((11, 109), 228, 227) -> ((9, 64), 228, 227); kept
- AOSSi_WLANGetBSSList: free callback presence checked as boolean in inline helper: ((9, 64), 228, 227) -> ((3, 28), 227, 227); kept
- AOSSi_WLANGetBSSList: scan channel field assignment after max-channel scalar: ((3, 28), 227, 227) -> ((3, 30), 227, 227); restored
- AOSSi_WLANGetBSSList: unlock retry failure exits loop through shared result return: ((3, 28), 227, 227) -> ((2, 26), 227, 227); kept
- AOSSi_WLANGetBSSList: scan setup uses const info view for enabled channel: ((2, 26), 227, 227) -> ((2, 26), 227, 227); restored
- AOSSi_WLANGetBSSList: scan bssid memset explicit void destination view: ((2, 26), 227, 227) -> ((2, 26), 227, 227); restored
- AOSSi_WLANConnect: const connection view for read-only configuration source: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: IP memory clear uses scoped byte-pointer binding: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANGetBSSList: channel scalar read explicitly separated from scan store: ((2, 26), 227, 227) -> ((2, 26), 227, 227); restored
- AOSSi_WLANGetBSSList: const channel value scoped around scan parameter setup: ((2, 26), 227, 227) -> ((2, 26), 227, 227); restored
- AOSSi_WLANGetBSSList: scan bssid destination bound before parameter writes: ((2, 26), 227, 227) -> ((8, 182), 228, 227); restored
- AOSSi_WLANGetBSSList: final declaration search after correcting record type and moving rate initialization, (2, 25) after 140 builds; kept in source:
- AOSSi_WLANConnect: IP memset global object receiver instead of cached pointer: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: IP memset typed byte receiver: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: IP memset destination scoped immutable binding: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: IP memset global object receiver instead of cached pointer: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: IP memset typed byte receiver: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- AOSSi_WLANConnect: IP memset destination scoped immutable binding: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- drawTransferTitles__Q33ipl5scene8SDMemoryFv: Color argument copies use the existing named color snapshot: ((162, 404), 439, 451) -> ((73, 403), 437, 451); kept
- AOSSi_WLANGetBSSList: register-only declaration search after structural attempts ((2, 25), 227, 227) -> ((2, 25), 227, 227); order was:
- drawTransferTitles__Q33ipl5scene8SDMemoryFv: Named Color snapshot passed directly instead of extra argument temporaries: ((73, 403), 437, 451) -> ((132, 423), 431, 451); restored
- AOSSi_WLANGetBSSList: Scan channel assignment through semantic inline setter: ((2, 25), 227, 227) -> ((2, 25), 227, 227); restored
- AOSSi_WLANGetBSSList: Scan bssid clear through semantic inline helper: ((2, 25), 227, 227) -> ((2, 25), 227, 227); restored
- AOSSi_WLANGetBSSList: Immutable driver info view for scan setup after allocation: ((2, 25), 227, 227) -> ((2, 25), 227, 227); restored
- AOSSi_WLANConnect: IP pointer declared const at start of configuration scope: ((2, 2), 155, 155) -> ((2, 2), 155, 155); restored
- NWC24iSetMsgSubjectBase64: Base64 work parameter immutable pointer binding: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- NWC24iSetMsgSubjectBase64: Base64 second-half buffer declaration initialized before size declaration: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- NWC24iSetMsgSubjectBase64: Base64 work-size pointer split into saved first-half scalar: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- ConvertDaysToDate: Month leap helper direct conditional return with readonly month view: ((0, 6), 103, 103) -> ((0, 33), 103, 103); restored
- ConvertDaysToDate: Month leap helper explicit true/false arms: ((0, 6), 103, 103) -> ((13, 102), 100, 103); restored
- ConvertDaysToDate: Month leap helper local flag initialized through a named false scalar: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored

Final fuzzy audit restored last Color snapshot trial: drawTransferTitles91.33925 below baseline92.7694 despite a smaller structural-normalized diff. Only create changes retained in SDMemory.

### Round f exhaustion and ownership audit
- NWC24ReadMsgSubjectPublic: 3 successfully compiled distinct source trials; remaining: 100/104; redundant overflow exit branches.
  Extent proof: address0x814a9850,size0x1a0,end0x814a99f0; next symbol NWC24ReadMsgTextPublic at0x814a99f0; no overlap, no symbols.txt edit.
- NWC24ReadMsgTextPublic: 3 successfully compiled distinct source trials; remaining: 68/70; redundant overflow exit branches.
  Extent proof: address0x814a99f0,size0x118,end0x814a9b08; next symbol NWC24SetMsgSubjectPublic at0x814a9b08; no overlap, no symbols.txt edit.
- NWC24SetMsgSubjectAndTextPublic: 3 successfully compiled distinct source trials; remaining: 190/190; input/context saved register allocation.
  Extent proof: address0x814a9cd0,size0x2f8,end0x814a9fc8; next symbol NWC24iGetDefaultCharset at0x814a9fc8; no overlap, no symbols.txt edit.
- NWC24iSetMsgSubjectBase64: 6 successfully compiled distinct source trials; remaining: 136/136; five parameter-save copy order differences.
  Extent proof: address0x814aab18,size0x220,end0x814aad38; next symbol NWC24SuspendScheduler at0x814aad38; no overlap, no symbols.txt edit.
- NWC24iDateToOSCalendarTime: 3 successfully compiled distinct source trials; remaining: 85/85; year and leap/zero registers exchanged.
  Extent proof: address0x814ac1c4,size0x154,end0x814ac318; next symbol NWC24iIsValidDate at0x814ac318; no overlap, no symbols.txt edit.
- ConvertDateToDays: 3 successfully compiled distinct source trials; remaining: 113/113; quotient/add scheduling and temporaries.
  Extent proof: address0x814ac348,size0x1c4,end0x814ac50c; next symbol ConvertDaysToDate at0x814ac50c; no overlap, no symbols.txt edit.
- ConvertDaysToDate: 21 successfully compiled distinct source trials; remaining: 103/103; six month versus leap register differences.
  Extent proof: address0x814ac50c,size0x19c,end0x814ac6a8; next symbol NWC24ReadFriendInfo at0x814ac6a8; no overlap, no symbols.txt edit.
- TMCJPEGDEC_exif_parse: 6 successfully compiled distinct source trials; remaining: 212/212; byte-reader and saved pointer/count registers.
  Extent proof: address0x814ee1a0,size0x350,end0x814ee4f0; next symbol TMCJPEGDEC_IFD0_tag_parse at0x814ee4f0; no overlap, no symbols.txt edit.
- TMCJPEGDEC_IFD0_tag_parse: 4 successfully compiled distinct source trials; remaining: 481/481; switch topology/byte-reader operand order.
  Extent proof: address0x814ee4f0,size0x784,end0x814eec74; next symbol TMCJPEGDEC_IFD1_tag_parse at0x814eec74; no overlap, no symbols.txt edit.
- TMCJPEGDEC_IFD1_tag_parse: 3 successfully compiled distinct source trials; remaining: 239/242; switch topology/byte-reader operand order.
  Extent proof: address0x814eec74,size0x3c8,end0x814ef03c; next symbol TMCJPEGDEC_ThumbnailCheck at0x814ef03c; no overlap, no symbols.txt edit.
- AOSSi_WLANGetBSSList: 23 successfully compiled distinct source trials; remaining: 227/227; channel-store/argument scheduling and loop/retry registers.
  Extent proof: address0x813fd3a0,size0x38c,end0x813fd72c; next symbol AOSSi_WLANConnect at0x813fd72c; no overlap, no symbols.txt edit.
- AOSSi_WLANConnect: 21 successfully compiled distinct source trials; remaining: 155/155; two memset argument setup instructions reversed.
  Extent proof: address0x813fd72c,size0x26c,end0x813fd998; next symbol AOSSi_Sleep at0x813fd998; no overlap, no symbols.txt edit.
- clearCandidates__Q39textinput8tistring6WithZiFv: 4 successfully compiled distinct source trials; remaining: 84/81; global candidate base and helper boundaries.
  Extent proof: address0x81433d8c,size0x144,end0x81433ed0; next symbol openDictionary__Q39textinput8tistring6WithZiFPvPv at0x81433ed0; no overlap, no symbols.txt edit.
- update__Q39textinput8tistring6WithZiFv: 4 successfully compiled distinct source trials; remaining: 447/446; candidate search lifetime and Korean loop structure.
  Extent proof: address0x814344c4,size0x6f8,end0x81434bbc; next symbol complementsCandidates___Q39textinput8tistring6WithZiFl at0x81434bbc; no overlap, no symbols.txt edit.
- setElementBuffer__Q39textinput8tistring6WithZiFv: 3 successfully compiled distinct source trials; remaining: 65/65; buffer base/load ordering and registers.
  Extent proof: address0x81434d34,size0x104,end0x81434e38; next symbol isFix__Q39textinput8tistring6WithZiFv at0x81434e38; no overlap, no symbols.txt edit.
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: 6 successfully compiled distinct source trials; remaining: 1064/1064; saved argument/temporary registers.
  Extent proof: address0x813eb690,size0x10a0,end0x813ec730; next symbol setTitleLists__Q33ipl5scene8SDMemoryFRCQ43ipl5scene8SDMemory10TitleRangeRCQ43ipl5scene8SDMemory10TitleRange at0x813ec730; no overlap, no symbols.txt edit.
- drawTransferTitles__Q33ipl5scene8SDMemoryFv: 5 successfully compiled distinct source trials; remaining: 439/451; newline loop and Color copy boundaries/stack offsets.
  Extent proof: address0x813eefb8,size0x70c,end0x813ef6c4; next symbol writeFourFlagBytes__Q23ipl5sceneFPUcUcUcUcUc at0x813ef6c4; no overlap, no symbols.txt edit.
All17 genuine objdiff-open functions have>=3 successfully compiled distinct source trials this round; no untried functions. All owned data already100%, Exif has none; no rename/extent corrections justified. No definition-level volatile added because no target same-slot reload proof. No new instruction-exact function gained; work remains partial.

### Round f final full nonquick gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 3352/5352 data 232/232 functions 8/12 fuzzy 99.2638 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 8/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 99.263824
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectBase64 99.632355
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 3352/5352 data 232 functions 8 fuzzy 99.2638
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1168/2372 data 40/40 functions 5/8 fuzzy 99.2462 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 5/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.24621
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: NWC24iDateToOSCalendarTime 99.17647
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 99.70874
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 98.9005
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 96.3915 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 96.39151
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 98.77358
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 94.46986
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 93.099174
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 96.2893
[src/scene/setting/AOSSLink] pool: IDENTICAL
[src/scene/setting/AOSSLink] objdiff: code 668/2196 data 2432/2432 functions 12/14 fuzzy 99.0073 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 12/14
[src/scene/setting/AOSSLink]   section .bss size 2344 match 100.0
[src/scene/setting/AOSSLink]   section .data size 48 match 100.0
[src/scene/setting/AOSSLink]   section .sbss size 40 match 100.0
[src/scene/setting/AOSSLink]   section .text size 2196 match 99.007286
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANGetBSSList 98.48018
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANConnect 98.70968
[src/scene/setting/AOSSLink] baseline: code 668/2196 data 2432 functions 12 fuzzy 91.1111
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3136/5504 data 7680/7680 functions 26/29 fuzzy 96.4608 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 26/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 96.460754
[src/keyboard/tiZiString]   below 100: clearCandidates__Q39textinput8tistring6WithZiFv 93.28395
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 91.70852
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 90.33846
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 96.3074
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14812/20872 data 3344/3344 functions 64/66 fuzzy 99.1978 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 63/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.19778
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 99.13064
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 92.7694
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14812/20872 data 3344 functions 64 fuzzy 98.9810
regressions vs baseline: 0
global matched_code_percent: 89.30427 -> 89.30427
global fuzzy_match_percent: 99.52654 -> 99.53458
global complete_code_percent: 67.07732 -> 67.07732
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Final open functions (percentages from clean rebuilt report; each has at least three distinct compiled source attempts audited above):
- NWC24ReadMsgSubjectPublic: 96.15385%; 100/104; redundant overflow exit branches.
- NWC24ReadMsgTextPublic: 97.14286%; 68/70; redundant overflow exit branches.
- NWC24SetMsgSubjectAndTextPublic: 98.23684%; 190/190; input/context saved register allocation.
- NWC24iSetMsgSubjectBase64: 99.632355%; 136/136; five parameter-save copy order differences.
- NWC24iDateToOSCalendarTime: 99.17647%; 85/85; year and leap/zero registers exchanged.
- ConvertDateToDays: 96.92921%; 113/113; quotient/add scheduling and temporaries.
- ConvertDaysToDate: 99.70874%; 103/103; six month versus leap register differences.
- TMCJPEGDEC_exif_parse: 98.77358%; 212/212; byte-reader and saved pointer/count registers.
- TMCJPEGDEC_IFD0_tag_parse: 94.46986%; 481/481; switch topology/byte-reader operand order.
- TMCJPEGDEC_IFD1_tag_parse: 93.099174%; 239/242; switch topology/byte-reader operand order.
- AOSSi_WLANGetBSSList: 98.48018%; 227/227; channel-store/argument scheduling and loop/retry registers.
- AOSSi_WLANConnect: 98.70968%; 155/155; two memset argument setup instructions reversed.
- clearCandidates__Q39textinput8tistring6WithZiFv: 93.28395%; 84/81; global candidate base and helper boundaries.
- update__Q39textinput8tistring6WithZiFv: 91.70852%; 447/446; candidate search lifetime and Korean loop structure.
- setElementBuffer__Q39textinput8tistring6WithZiFv: 90.33846%; 65/65; buffer base/load ordering and registers.
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: 99.13064%; 1064/1064; saved argument/temporary registers.
- drawTransferTitles__Q33ipl5scene8SDMemoryFv: 92.7694%; 439/451; newline loop and Color copy boundaries/stack offsets.

Before -> after instruction-exact functions, objdiff matched code bytes, matched data bytes:
- libs/RevoEX/src/nwc24/NWC24MsgSubject: instruction exact 8/12 -> 8/12; code 3352/5352 -> 3352/5352; data 232/232 -> 232/232; fuzzy 99.2638 -> 99.2638.
- libs/RevoEX/src/nwc24/NWC24DateParser: instruction exact 5/8 -> 5/8; code 1168/2372 -> 1168/2372; data 40/40 -> 40/40; fuzzy 98.9005 -> 99.2462.
- libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse: instruction exact 3/6 -> 3/6; code 1348/5088 -> 1348/5088; data None/None -> None/None; fuzzy 96.2893 -> 96.3915.
- src/scene/setting/AOSSLink: instruction exact 12/14 -> 12/14; code 668/2196 -> 668/2196; data 2432/2432 -> 2432/2432; fuzzy 91.1111 -> 99.0073.
- src/keyboard/tiZiString: instruction exact 26/29 -> 26/29; code 3136/5504 -> 3136/5504; data 7680/7680 -> 7680/7680; fuzzy 96.3074 -> 96.4608.
- src/scene/sdChannelMemory/iplSDMemory: instruction exact 63/66 -> 63/66; code 14812/20872 -> 14812/20872; data 3344/3344 -> 3344/3344; fuzzy 98.9810 -> 99.1978.
No new exact functions: acceptance definition requiring an increased instruction-exact count was not achieved. Full gate nevertheless passes with zero global regressions, identical pools, exact DOL hash, zero forbidden patterns and readability warnings. Five owned source files retain non-regressing fuzzy improvements; Subject is unchanged. SDMemory updateState remains raw-byte-exact; gate counts63 while objdiff counts64 due identical paired-single words being interpreted as offset-sensitive branch operands by ctxdiff. No configuration/header edit.

Source/log commit850747d1; six paths: libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse.c, libs/RevoEX/src/nwc24/NWC24DateParser.c, src/keyboard/tiZiString.cpp, src/scene/sdChannelMemory/iplSDMemory.cpp, src/scene/setting/AOSSLink.c, tools/decomp-assist/fz7.attempts.md. The first final-record script failed extracting the reasons dictionary; corrected it with AST literal parsing and recorded the successful full gate here. No source changed after the final full gate.

## Round high on same branch831cfd54
Selected five closest genuine open functions by current objdiff percentage. All six unit pools rechecked by baseline quick gate as IDENTICAL; all data already100%, Exif has none. Before measurements are below. No new volatile is warranted without target same-slot store/reload evidence.
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 3352/5352 data 232/232 functions 8/12 fuzzy 99.2638 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 8/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 99.263824
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectBase64 99.632355
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 3352/5352 data 232 functions 8 fuzzy 99.2638
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1168/2372 data 40/40 functions 5/8 fuzzy 99.2462 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 5/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.24621
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: NWC24iDateToOSCalendarTime 99.17647
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 99.70874
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 98.9005
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 96.3915 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 96.39151
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 98.77358
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 94.46986
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 93.099174
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 96.2893
[src/scene/setting/AOSSLink] pool: IDENTICAL
[src/scene/setting/AOSSLink] objdiff: code 668/2196 data 2432/2432 functions 12/14 fuzzy 99.0073 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 12/14
[src/scene/setting/AOSSLink]   section .bss size 2344 match 100.0
[src/scene/setting/AOSSLink]   section .data size 48 match 100.0
[src/scene/setting/AOSSLink]   section .sbss size 40 match 100.0
[src/scene/setting/AOSSLink]   section .text size 2196 match 99.007286
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANGetBSSList 98.48018
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANConnect 98.70968
[src/scene/setting/AOSSLink] baseline: code 668/2196 data 2432 functions 12 fuzzy 91.1111
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3136/5504 data 7680/7680 functions 26/29 fuzzy 96.4608 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 26/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 96.460754
[src/keyboard/tiZiString]   below 100: clearCandidates__Q39textinput8tistring6WithZiFv 93.28395
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 91.70852
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 90.33846
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 96.3074
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14812/20872 data 3344/3344 functions 64/66 fuzzy 99.1978 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 63/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.19778
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 99.13064
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 92.7694
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14812/20872 data 3344 functions 64 fuzzy 98.9810
regressions vs baseline: 0
global matched_code_percent: 89.30427 -> 89.30427
global fuzzy_match_percent: 99.52654 -> 99.53458
global complete_code_percent: 67.07732 -> 67.07732
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### High ConvertDaysToDate
Fetched origin/main. Source equals origin baseline9c641682; medium modifications still unlanded, target function remains below100. Pool check performed before tuning. Current percent99.70874. Immediate stack stw/lwz same-slot pairs=[].
src 0x19c base 0x19c insns 103/103
diffs 6: [55, 57, 60, 83, 84, 88]
    55 M lbz r12, 0(r4)
       B lbz r0, 0(r4)
    57 M cmplwi r12, 2
       B cmplwi r0, 2
    60 M li r0, 0
       B li r12, 0
    83 M li r0, 1
       B li r12, 1
    84 M cmpwi r0, 0
       B cmpwi r12, 0
    88 M add r8, r9, r12
       B add r8, r9, r0

### High NWC24iSetMsgSubjectBase64
Fetched origin/main. Source equals origin baseline9c641682; medium modifications still unlanded, target function remains below100. Pool check performed before tuning. Current percent99.632355. Immediate stack stw/lwz same-slot pairs=[].
src 0x220 base 0x220 insns 136/136
diffs 5: [8, 9, 10, 11, 12]
     8 M mr r18, r4
       B mr r22, r8
     9 M mr r19, r5
       B mr r18, r4
    10 M mr r20, r6
       B mr r19, r5
    11 M mr r21, r7
       B mr r20, r6
    12 M mr r22, r8
       B mr r21, r7

### High NWC24iDateToOSCalendarTime
Fetched origin/main. Source equals origin baseline9c641682; medium modifications still unlanded, target function remains below100. Pool check performed before tuning. Current percent99.17647. Immediate stack stw/lwz same-slot pairs=[].
src 0x154 base 0x154 insns 85/85
diffs 13: [6, 7, 16, 17, 24, 32, 33, 38, 43, 47, 52, 54, 55]
     6 M lhz r0, 0(r4)
       B lhz r5, 0(r4)
     7 M li r5, 0
       B li r0, 0
    16 M slwi r6, r0, 0x1e
       B slwi r6, r5, 0x1e
    17 M srwi r7, r0, 0x1f
       B srwi r7, r5, 0x1f
    24 M stw r0, 0x14(r3)
       B stw r5, 0x14(r3)
    32 M stw r5, 0x20(r3)
       B stw r0, 0x20(r3)
    33 M stw r5, 0x24(r3)
       B stw r0, 0x24(r3)
    38 M mulhw r7, r7, r0
       B mulhw r7, r7, r5
    43 M subf. r7, r7, r0
       B subf. r7, r7, r5
    47 M mulhw r7, r7, r0
       B mulhw r7, r7, r5
    52 M subf. r0, r7, r0
       B subf. r5, r7, r5
    54 M li r5, 1
       B li r0, 1
    55 M cmpwi r5, 0
       B cmpwi r0, 0

### High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect
Fetched origin/main. Source equals origin baseline9c641682; medium modifications still unlanded, target function remains below100. Pool check performed before tuning. Current percent99.13064. Immediate stack stw/lwz same-slot pairs=[].
src 0x10a0 base 0x10a0 insns 1064/1064
diffs 179: [5, 10, 17, 21, 27, 33, 34, 39, 40, 45, 46, 51, 57, 63, 69, 75, 81, 109, 116, 117]
     5 M lis r30, 0
       B lis r31, 0
    10 M addi r30, r30, 0
       B addi r31, r31, 0
    17 M addi r7, r30, 0x58
       B addi r7, r31, 0x58
    21 M addi r4, r30, 0x79
       B addi r4, r31, 0x79
    27 M addi r4, r30, 0xa3
       B addi r4, r31, 0xa3
    33 M addi r4, r30, 0xce
       B addi r4, r31, 0xce
    34 M addi r5, r30, 0xfb
       B addi r5, r31, 0xfb
    39 M addi r4, r30, 0x107
       B addi r4, r31, 0x107
    40 M addi r5, r30, 0xfb
       B addi r5, r31, 0xfb
    45 M addi r4, r30, 0x135
       B addi r4, r31, 0x135
    46 M addi r5, r30, 0x163
       B addi r5, r31, 0x163
    51 M addi r4, r30, 0x170
       B addi r4, r31, 0x170
    57 M addi r4, r30, 0x19f
       B addi r4, r31, 0x19f
    63 M addi r4, r30, 0x1cd
       B addi r4, r31, 0x1cd
    69 M addi r4, r30, 0x1f6
       B addi r4, r31, 0x1f6
    75 M addi r4, r30, 0x225
       B addi r4, r31, 0x225
    81 M addi r4, r30, 0x253
       B addi r4, r31, 0x253
   109 M addi r4, r30, 0x27c
       B addi r4, r31, 0x27c
   116 M lis r31, 0
       B lis r26, 0
   117 M mr r26, r3
       B mr r30, r3
   118 M addi r31, r31, 0
       B addi r26, r26, 0
   120 M lwz r3, 0x80(r31)
       B lwz r3, 0x80(r26)
   123 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   125 M mr r3, r26
       B mr r3, r30
   131 M addi r4, r30, 0x288
       B addi r4, r31, 0x288
   138 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   139 M mr r26, r3
       B mr r30, r3
   143 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   145 M mr r3, r26
       B mr r3, r30
   151 M addi r4, r30, 0x293
       B addi r4, r31, 0x293
   158 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   159 M mr r26, r3
       B mr r30, r3
   163 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   165 M mr r3, r26
       B mr r3, r30
   178 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   179 M mr r31, r3
       B mr r30, r3
   183 M lwz r12, 0(r31)
       B lwz r12, 0(r30)
   185 M mr r3, r31
       B mr r3, r30
   196 M addi r7, r30, 0x29e
       B addi r7, r31, 0x29e
   200 M addi r4, r30, 0x2bf
       B addi r4, r31, 0x2bf
   206 M addi r4, r30, 0x2e9
       B addi r4, r31, 0x2e9
   212 M addi r4, r30, 0x314
       B addi r4, r31, 0x314
   213 M addi r5, r30, 0xfb
       B addi r5, r31, 0xfb
   218 M addi r4, r30, 0x341
       B addi r4, r31, 0x341
   219 M addi r5, r30, 0xfb
       B addi r5, r31, 0xfb
   224 M addi r4, r30, 0x36f
       B addi r4, r31, 0x36f
   225 M addi r5, r30, 0x163
       B addi r5, r31, 0x163
   230 M addi r4, r30, 0x39d
       B addi r4, r31, 0x39d
   236 M addi r4, r30, 0x3cc
       B addi r4, r31, 0x3cc
   242 M addi r4, r30, 0x3fa
       B addi r4, r31, 0x3fa
   248 M addi r4, r30, 0x423
       B addi r4, r31, 0x423
   254 M addi r4, r30, 0x452
       B addi r4, r31, 0x452
   260 M addi r4, r30, 0x480
       B addi r4, r31, 0x480
   266 M addi r4, r30, 0x4a9
       B addi r4, r31, 0x4a9
   272 M addi r4, r30, 0x4d8
       B addi r4, r31, 0x4d8
   278 M addi r4, r30, 0x506
       B addi r4, r31, 0x506
   284 M addi r4, r30, 0x52f
       B addi r4, r31, 0x52f
   290 M addi r4, r30, 0x55e
       B addi r4, r31, 0x55e
   296 M addi r4, r30, 0x58c
       B addi r4, r31, 0x58c
   334 M addi r4, r30, 0x5b5
       B addi r4, r31, 0x5b5
   341 M lis r31, 0
       B lis r26, 0
   342 M mr r26, r3
       B mr r30, r3
   343 M addi r31, r31, 0
       B addi r26, r26, 0
   345 M lwz r3, 0x80(r31)
       B lwz r3, 0x80(r26)
   348 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   350 M mr r3, r26
       B mr r3, r30
   356 M addi r4, r30, 0x5be
       B addi r4, r31, 0x5be
   363 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   364 M mr r26, r3
       B mr r30, r3
   368 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   370 M mr r3, r26
       B mr r3, r30
   376 M addi r4, r30, 0x5c9
       B addi r4, r31, 0x5c9
   383 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   384 M mr r26, r3
       B mr r30, r3
   388 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   390 M mr r3, r26
       B mr r3, r30
   396 M addi r4, r30, 0x5d4
       B addi r4, r31, 0x5d4
   403 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   404 M mr r26, r3
       B mr r30, r3
   408 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   410 M mr r3, r26
       B mr r3, r30
   416 M addi r4, r30, 0x5df
       B addi r4, r31, 0x5df
   423 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   424 M mr r26, r3
       B mr r30, r3
   428 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   430 M mr r3, r26
       B mr r3, r30
   436 M addi r4, r30, 0x27c
       B addi r4, r31, 0x27c
   443 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   444 M mr r26, r3
       B mr r30, r3
   448 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   450 M mr r3, r26
       B mr r3, r30
   456 M addi r4, r30, 0x288
       B addi r4, r31, 0x288
   463 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   464 M mr r26, r3
       B mr r30, r3
   468 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   470 M mr r3, r26
       B mr r3, r30
   476 M addi r4, r30, 0x293
       B addi r4, r31, 0x293
   483 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   484 M mr r26, r3
       B mr r30, r3
   488 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   490 M mr r3, r26
       B mr r3, r30
   496 M addi r4, r30, 0x5ea
       B addi r4, r31, 0x5ea
   503 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   504 M mr r26, r3
       B mr r30, r3
   508 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   510 M mr r3, r26
       B mr r3, r30
   516 M lwz r5, 0x94(r31)
       B lwz r6, 0x94(r26)
   517 M li r6, 0
       B li r5, 0
   520 M add r4, r5, r3
       B add r4, r6, r3
   525 M addi r6, r6, 1
       B addi r5, r5, 1
   528 M cmpwi r6, 5
       B cmpwi r5, 5
   588 M mr r26, r3
       B mr r30, r3
   594 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   596 M mr r3, r26
       B mr r3, r30
   607 M addi r7, r30, 0x5f5
       B addi r7, r31, 0x5f5
   611 M addi r4, r30, 0x616
       B addi r4, r31, 0x616
   624 M addi r4, r30, 0x61f
       B addi r4, r31, 0x61f
   630 M addi r4, r30, 0x64e
       B addi r4, r31, 0x64e
   636 M addi r4, r30, 0x67e
       B addi r4, r31, 0x67e
   637 M addi r5, r30, 0x6ad
       B addi r5, r31, 0x6ad
   642 M addi r4, r30, 0x6ba
       B addi r4, r31, 0x6ba
   643 M addi r5, r30, 0x6ad
       B addi r5, r31, 0x6ad
   648 M addi r4, r30, 0x6e8
       B addi r4, r31, 0x6e8
   649 M addi r5, r30, 0x711
       B addi r5, r31, 0x711
   654 M addi r4, r30, 0x71b
       B addi r4, r31, 0x71b
   655 M addi r5, r30, 0x74a
       B addi r5, r31, 0x74a
   660 M addi r4, r30, 0x757
       B addi r4, r31, 0x757
   661 M addi r5, r30, 0x74a
       B addi r5, r31, 0x74a
   666 M addi r4, r30, 0x785
       B addi r4, r31, 0x785
   667 M addi r5, r30, 0x7ae
       B addi r5, r31, 0x7ae
   672 M addi r4, r30, 0x7b8
       B addi r4, r31, 0x7b8
   673 M addi r5, r30, 0x7e1
       B addi r5, r31, 0x7e1
   678 M addi r4, r30, 0x7ee
       B addi r4, r31, 0x7ee
   679 M addi r5, r30, 0x7e1
       B addi r5, r31, 0x7e1
   684 M addi r4, r30, 0x818
       B addi r4, r31, 0x818
   685 M addi r5, r30, 0x840
       B addi r5, r31, 0x840
   690 M addi r4, r30, 0x7b8
       B addi r4, r31, 0x7b8
   691 M addi r5, r30, 0x84a
       B addi r5, r31, 0x84a
   696 M addi r4, r30, 0x7ee
       B addi r4, r31, 0x7ee
   697 M addi r5, r30, 0x84a
       B addi r5, r31, 0x84a
   702 M addi r4, r30, 0x818
       B addi r4, r31, 0x818
   703 M addi r5, r30, 0x857
       B addi r5, r31, 0x857
   708 M addi r4, r30, 0x861
       B addi r4, r31, 0x861
   709 M addi r5, r30, 0x889
       B addi r5, r31, 0x889
   714 M addi r4, r30, 0x894
       B addi r4, r31, 0x894
   715 M addi r5, r30, 0x889
       B addi r5, r31, 0x889
   720 M addi r4, r30, 0x861
       B addi r4, r31, 0x861
   721 M addi r5, r30, 0x8ba
       B addi r5, r31, 0x8ba
   726 M addi r4, r30, 0x894
       B addi r4, r31, 0x894
   727 M addi r5, r30, 0x8ba
       B addi r5, r31, 0x8ba
   732 M addi r4, r30, 0x8c5
       B addi r4, r31, 0x8c5
   733 M addi r5, r30, 0x8eb
       B addi r5, r31, 0x8eb
   738 M addi r4, r30, 0x8f5
       B addi r4, r31, 0x8f5
   739 M addi r5, r30, 0x924
       B addi r5, r31, 0x924
   744 M addi r4, r30, 0x930
       B addi r4, r31, 0x930
   745 M addi r5, r30, 0x924
       B addi r5, r31, 0x924
   750 M addi r4, r30, 0x8f5
       B addi r4, r31, 0x8f5
   751 M addi r5, r30, 0x95d
       B addi r5, r31, 0x95d
   756 M addi r4, r30, 0x930
       B addi r4, r31, 0x930
   757 M addi r5, r30, 0x95d
       B addi r5, r31, 0x95d
   800 M addi r4, r30, 0x969
       B addi r4, r31, 0x969
   809 M lis r31, 0
       B lis r26, 0
   810 M mr r26, r3
       B mr r30, r3
   811 M addi r31, r31, 0
       B addi r26, r26, 0
   813 M lwz r3, 0x80(r31)
       B lwz r3, 0x80(r26)
   816 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   818 M mr r3, r26
       B mr r3, r30
   824 M addi r4, r30, 0x973
       B addi r4, r31, 0x973
   831 M lwz r5, 0x80(r31)
       B lwz r5, 0x80(r26)
   832 M mr r26, r3
       B mr r30, r3
   836 M lwz r12, 0(r26)
       B lwz r12, 0(r30)
   838 M mr r3, r26
       B mr r3, r30
   849 M addi r7, r30, 0x980
       B addi r7, r31, 0x980
   853 M addi r4, r30, 0x9a1
       B addi r4, r31, 0x9a1
   859 M addi r4, r30, 0x9cb
       B addi r4, r31, 0x9cb
   906 M addi r29, r30, 0
       B addi r29, r31, 0
   963 M addi r29, r30, 0xc
       B addi r29, r31, 0xc
   983 M addi r29, r30, 0x20
       B addi r29, r31, 0x20
  1037 M addi r29, r30, 0x48
       B addi r29, r31, 0x48

### High TMCJPEGDEC_exif_parse
Fetched origin/main. Source equals origin baseline9c641682; medium modifications still unlanded, target function remains below100. Pool check performed before tuning. Current percent98.77358. Immediate stack stw/lwz same-slot pairs=[].
src 0x350 base 0x350 insns 212/212
diffs 43: [7, 27, 28, 30, 31, 32, 34, 61, 69, 70, 72, 73, 74, 76, 77, 79, 80, 82, 89, 92]
     7 M mr r27, r3
       B mr r30, r3
    27 M lbz r5, 3(r3)
       B lbz r6, 3(r3)
    28 M lbz r6, 2(r3)
       B lbz r5, 2(r3)
    30 M rlwimi r6, r5, 8, 0x10, 0x17
       B rlwimi r5, r6, 8, 0x10, 0x17
    31 M rlwinm r0, r6, 8, 0x10, 0x17
       B rlwinm r0, r5, 8, 0x10, 0x17
    32 M rlwimi r0, r6, 0x18, 0x18, 0x1f
       B rlwimi r0, r5, 0x18, 0x18, 0x1f
    34 M clrlwi r0, r6, 0x10
       B clrlwi r0, r5, 0x10
    61 M add r30, r3, r5
       B add r27, r3, r5
    69 M lbz r3, 1(r30)
       B lbz r4, 1(r27)
    70 M lbz r4, 0(r30)
       B lbz r3, 0(r27)
    72 M rlwimi r4, r3, 8, 0x10, 0x17
       B rlwimi r3, r4, 8, 0x10, 0x17
    73 M rlwinm r0, r4, 8, 0x10, 0x17
       B rlwinm r0, r3, 8, 0x10, 0x17
    74 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r0, r3, 0x18, 0x18, 0x1f
    76 M clrlwi r0, r4, 0x10
       B clrlwi r0, r3, 0x10
    77 M clrlwi r26, r0, 0x10
       B clrlwi r23, r0, 0x10
    79 M mulli r23, r26, 0xc
       B mulli r26, r23, 0xc
    80 M addi r30, r30, 2
       B addi r27, r27, 2
    82 M cmpw r25, r23
       B cmpw r25, r26
    89 M mr r5, r30
       B mr r5, r27
    92 M addi r30, r30, 0xc
       B addi r27, r27, 0xc
    95 M cmplw r0, r26
       B cmplw r0, r23
    97 M subf r0, r23, r25
       B subf r0, r26, r25
   104 M lbz r3, 1(r30)
       B lbz r3, 1(r27)
   106 M lbz r4, 2(r30)
       B lbz r4, 2(r27)
   107 M lbz r5, 0(r30)
       B lbz r5, 0(r27)
   109 M lbz r0, 3(r30)
       B lbz r0, 3(r27)
   128 M add r26, r27, r3
       B add r26, r30, r3
   136 M lbz r3, 1(r26)
       B lbz r4, 1(r26)
   137 M lbz r4, 0(r26)
       B lbz r3, 0(r26)
   139 M rlwimi r4, r3, 8, 0x10, 0x17
       B rlwimi r3, r4, 8, 0x10, 0x17
   140 M rlwinm r0, r4, 8, 0x10, 0x17
       B rlwinm r0, r3, 8, 0x10, 0x17
   141 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r0, r3, 0x18, 0x18, 0x1f
   143 M clrlwi r0, r4, 0x10
       B clrlwi r0, r3, 0x10
   144 M clrlwi r30, r0, 0x10
       B clrlwi r27, r0, 0x10
   146 M mulli r0, r30, 0xc
       B mulli r0, r27, 0xc
   162 M cmplw r0, r30
       B cmplw r0, r27
   170 M add r26, r27, r3
       B add r26, r30, r3
   178 M lbz r3, 1(r26)
       B lbz r4, 1(r26)
   179 M lbz r4, 0(r26)
       B lbz r3, 0(r26)
   181 M rlwimi r4, r3, 8, 0x10, 0x17
       B rlwimi r3, r4, 8, 0x10, 0x17
   182 M rlwinm r0, r4, 8, 0x10, 0x17
       B rlwinm r0, r3, 8, 0x10, 0x17
   183 M rlwimi r0, r4, 0x18, 0x18, 0x1f
       B rlwimi r0, r3, 0x18, 0x18, 0x1f
   185 M clrlwi r0, r4, 0x10
       B clrlwi r0, r3, 0x10
High structural diagnosis Calendar:85/85, frame0x10, samebranches and field offsets. Only year r0/r5 versus zero/leap r5/r0 exchange. Const date input already in signature; initialization and helper lifetimes remain actionable. No extent overlap or reload proof.
- High NWC24iDateToOSCalendarTime: Leap flag initialization moved after calendar fields: ((0, 13), 85, 85) -> ((5, 76), 86, 85); restored
- High NWC24iDateToOSCalendarTime: Leap helper called after calendar fields instead of inline predicate: ((0, 13), 85, 85) -> ((5, 76), 86, 85); restored
- High NWC24iDateToOSCalendarTime: Const input local view isolates calendar write receiver: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Mutable input view for calendar alias assumptions: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Leap flag plain declaration in field-completion scope: ((0, 13), 85, 85) -> ((5, 76), 86, 85); restored
- High NWC24iDateToOSCalendarTime: Calendar field writes through immutable receiver binding: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
High extent check ConvertDaysToDate:0x814ac50c+0x19c=0x814ac6a8, next NWC24ReadFriendInfo0x814ac6a8; no overlap, no symbol edits.
High extent check NWC24iSetMsgSubjectBase64:0x814aab18+0x220=0x814aad38, next NWC24SuspendScheduler0x814aad38; no overlap, no symbol edits.
High extent check NWC24iDateToOSCalendarTime:0x814ac1c4+0x154=0x814ac318, next NWC24iIsValidDate0x814ac318; no overlap, no symbol edits.
High extent check create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect:0x813eb690+0x10a0=0x813ec730, next setTitleLists__Q33ipl5scene8SDMemoryFRCQ43ipl5scene8SDMemory10TitleRangeRCQ43ipl5scene8SDMemory10TitleRange0x813ec730; no overlap, no symbol edits.
High extent check TMCJPEGDEC_exif_parse:0x814ee1a0+0x350=0x814ee4f0, next TMCJPEGDEC_IFD0_tag_parse0x814ee4f0; no overlap, no symbol edits.
- High NWC24iDateToOSCalendarTime: Calendar zero fraction fields assigned as a chain: ((0, 13), 85, 85) -> ((2, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Calendar zero fraction fields sourced from current leap flag: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Leap zero established through fraction field assignment chain: ((0, 13), 85, 85) -> ((2, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Year read local initialized before leap zero assignment: ((0, 13), 85, 85) -> ((2, 19), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Leap flag signed byte instead of Boolean integer: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Leap flag unsigned16 instead of Boolean integer: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Leap flag unsigned32 instead of Boolean integer: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Date pointer binding itself const for field read scheduling: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
High structural diagnosis Base64:136/136, frame0x60, control/data exact. Five prologue parameter-copy order differences only. Work is genuinely mutable, subject genuinely const. Test split-buffer/helper and independent initialization order before declaration search; no stack reload proof.
- High NWC24iSetMsgSubjectBase64: Second buffer size computed before address: ((0, 5), 136, 136) -> ((2, 7), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Charset length read before buffer split setup: ((0, 5), 136, 136) -> ((6, 129), 137, 136); restored
- High NWC24iSetMsgSubjectBase64: Second half pointer produced by inline helper: ((0, 5), 136, 136) -> ((0, 15), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Second half capacity produced by inline helper: ((0, 5), 136, 136) -> ((0, 19), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Inline helper owns both buffer split outputs: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Encoded output pointer binding immutable after split: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Input buffer binding const pointer for repeated encoder calls: ((0, 5), 136, 136) -> ((0, 43), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Named split half local first with plain declaration: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Input size and subject pointer saved in semantic encoding scope: ((0, 5), 136, 136) -> ((0, 50), 136, 136); restored
High structural diagnosis month:103/103 frame0x10, all operand/branch/store offsets identical. Six month-versus-leap register differences remain after const month view. Target preserves month in r0 and inline leap flag in r12; helper definition and receiver lifetimes examined.
- High ConvertDaysToDate: Leap helper output supplied through Boolean pointer: ((0, 6), 103, 103) -> compile failure; restored
- High ConvertDaysToDate: Month-loop year input read-only view with explicit declaration before assignments: ((0, 6), 103, 103) -> ((0, 27), 103, 103); restored
- High ConvertDaysToDate: Readonly month view taken inside accessor helper: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Month read helper takes mutable input while local view remains const: ((0, 6), 103, 103) -> ((0, 29), 103, 103); restored
- High ConvertDaysToDate: Month pointer immutable binding within loop: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Month scalar promoted to unsigned32 with const month read: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- High ConvertDaysToDate: Month scalar promoted to unsigned16 with const month read: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- High ConvertDaysToDate: Month scalar promoted to signed32 with const month read: ((0, 6), 103, 103) -> ((1, 26), 103, 103); restored
- High ConvertDaysToDate: Year leap scalar copied into const binding in helper: ((0, 6), 103, 103) -> ((0, 27), 103, 103); restored
- High ConvertDaysToDate: Leap output pointer helper with declarations at scope start: ((0, 6), 103, 103) -> ((5, 71), 105, 103); restored
- High ConvertDaysToDate: Month accessor output pointer helper with readonly input: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Month comparison and table index use distinct promoted locals: ((0, 6), 103, 103) -> ((4, 35), 103, 103); restored
- High ConvertDaysToDate: Month table lookup operand promotes read into a signed index: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Leap flag bool normalized in arithmetic conditional branch: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Month comparison const scalar derived from currentMonth: ((0, 6), 103, 103) -> ((1, 26), 103, 103); restored
High structural diagnosis Exif:212/212 frame0x30, branches and data offsets exact. Three call-site byte-assembly groups exchange low/high temporary allocation; saved data/entries/count/extent registers also differ. Examine private read-only reader, narrowing point, and directory scope before local declaration search.
- High TMCJPEGDEC_exif_parse: Exif two-byte OR operands high byte first: ((0, 43), 212, 212) -> ((0, 43), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Exif two-byte low byte plain declaration and accumulated high byte: ((0, 43), 212, 212) -> ((29, 192), 216, 212); restored
- High TMCJPEGDEC_exif_parse: Exif two-byte reader value narrowed at declaration: ((0, 43), 212, 212) -> ((0, 21), 212, 212); kept
- High TMCJPEGDEC_exif_parse: Exif two-byte helper delegates to original endian reader: ((0, 21), 212, 212) -> ((0, 43), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Immutable data pointer binding at parse definition scope: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Writable view for first IFD entries with readonly tag helper: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Entry count promoted to signed32 only after byte reader: ((0, 21), 212, 212) -> ((3, 39), 212, 212); restored
High structural diagnosis create:1064/1064 frame0x20, identical control/load/field/string structure. Only register cycle remains: pool r30 versus31, TextBox r26 versus30, System global r31 versus26. The true setter boundary is now correct. Test parameter and message receiver const views, then local lifetimes; volatile has no proof.
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Heap and resource pointer bindings const in layout construction scope: ((0, 179), 1064, 1064) -> ((0, 189), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Scene mutable receiver binding for field writes: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Message requests use manager accessor receiver at each call: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: First pane is bound through a const pointer before TextBox conversion: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: TextBox pointer initially scoped to the first four message assignments: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: TextBox field receiver named for each message group with narrowed scope: ((0, 179), 1064, 1064) -> ((7, 761), 1063, 1064); restored
- High TMCJPEGDEC_exif_parse: Narrow Exif reader plain declaration before initialization: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Narrow Exif reader high and low bytes independently declared: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Writable base pointer read through const endian helpers: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Private EXIF parser accepts readonly opaque input then narrows its byte view: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Data base narrowed through a const byte view declared after extents: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Directory one entries and count live in their actual scope: ((0, 21), 212, 212) -> ((0, 34), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Directory indices narrowed separately for each lexical directory: ((0, 21), 212, 212) -> ((0, 30), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Directory first-count receiver declared with initializer immediately after bounds: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High NWC24iDateToOSCalendarTime: Leap flag zero initialized at definition: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Calendar fractional zero named independently before year fields: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Read-only year alias introduced only at leap predicate boundary: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High ConvertDaysToDate: Leap helper return type u16 instead of BOOL: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Leap helper return type s8 instead of BOOL: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Leap helper return type s16 instead of BOOL: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Leap helper flag local type u16 instead of BOOL: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Leap helper flag local type s8 instead of BOOL: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Leap helper flag local type s16 instead of BOOL: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Leap helper integer flag declared before const year scalar view: ((0, 6), 103, 103) -> ((0, 27), 103, 103); restored
- TMCJPEGDEC_exif_parse: register-only declaration search after structural attempts ((0, 21), 212, 212) -> ((0, 21), 212, 212); order was:
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Message fetches use const manager view per message call: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Message fetches own inline helper with const manager receiver: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: First message ID passed through scoped named scalar: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: TextBox pointer declared as generic Pane then narrowed at string calls: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Layout object construction receiver stored in actual local first: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Scroll animator declared before TextBox pointer and initialized at use: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High TMCJPEGDEC_exif_parse: Read-only EXIF record view for later offset read: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: EXIF record receiver binding const pointer for stores and helpers: ((0, 21), 212, 212) -> ((0, 26), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Entry count definition promoted to unsigned16 const within each directory: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Directory extent is unsigned32 instead of signed scalar: ((0, 21), 212, 212) -> ((3, 23), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Reader byte-order input widened to signed32 in private helper: ((0, 21), 212, 212) -> ((4, 25), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Directory count and extent grouped in a semantic record: ((0, 21), 212, 212) -> ((0, 46), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Guarded definition-level const input fields thumbnailData: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Guarded definition-level const input fields dataEnd: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Guarded definition-level const input fields thumbnailData,dataEnd: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High NWC24iDateToOSCalendarTime: Leap predicate preserves explicit false branch: ((0, 13), 85, 85) -> ((3, 69), 87, 85); restored
- High NWC24iDateToOSCalendarTime: Calendar output year assigned before other local initialization: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Fractional fields cleared before other calendar fields: ((0, 13), 85, 85) -> ((6, 18), 85, 85); restored
- High NWC24iSetMsgSubjectBase64: Output half helper size input const u32: ((0, 5), 136, 136) -> ((0, 15), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Output half helper size input s32: ((0, 5), 136, 136) -> ((0, 15), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Output half helper receives size before work pointer: ((0, 5), 136, 136) -> ((0, 15), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Output buffer split helper returns a semantic data/size record: ((0, 5), 136, 136) -> ((34, 140), 142, 136); restored
- High NWC24iSetMsgSubjectBase64: Half helper computes array-address expression instead of pointer sum: ((0, 5), 136, 136) -> ((0, 15), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Half helper input is readonly bytes then result regains writable buffer view: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: mutable buffer half helper followed by register-only declaration search: ((0, 5), 136, 136) -> ((0, 15), 136, 136); restored; order was:
- High ConvertDaysToDate: Leap helper uses int flag instead of SDK long BOOL: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Leap helper returns int instead of SDK long BOOL: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Leap helper returns and carries int flag instead of SDK long BOOL: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High ConvertDaysToDate: Month-loop saved days uses int instead of SDK signed long: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- High NWC24iDateToOSCalendarTime: Calendar leap flag int instead of SDK long BOOL: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iDateToOSCalendarTime: Calendar day-count int instead of SDK signed long: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- High NWC24iSetMsgSubjectBase64: Workspace declared as array parameter syntax: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Subject declared as readonly array parameter syntax: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Subject and workspace declared as array parameters: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Workspace size unsigned int scalar instead of SDK unsigned long: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Subject size unsigned int scalar instead of SDK unsigned long: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Region parameter signed long instead of enum int: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Readonly subject pointer copied after initial work split: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Each message TextBox receiver bound as scoped reference: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Message manager viewed through const reference at each request: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Both visibility panes use scoped reference receivers: ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High TMCJPEGDEC_exif_parse: First-directory entries pointer local shadows later directory receiver: ((0, 21), 212, 212) -> ((0, 34), 212, 212); restored
- High TMCJPEGDEC_exif_parse: First-directory count local shadows later directory count: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: First-directory pointer and count narrowed to first directory scope: ((0, 21), 212, 212) -> ((0, 34), 212, 212); restored
- High TMCJPEGDEC_exif_parse: First-directory extent local shadows later directory extents: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: First-directory pointer/count/extent get actual first-scope lifetimes: ((0, 21), 212, 212) -> ((0, 34), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Data extent scalar signed int instead of signed long: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Data pointer declared as array in private parser interface: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Directory offset scalar unsigned int instead of SDK unsigned long: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor message input view const Arg* arguments = &smArg; ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor both input view const Arg* arguments = &smArg; ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor message input view const Arg& arguments = smArg; ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor both input view const Arg& arguments = smArg; ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor message input view Arg* const arguments = &smArg; ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor both input view Arg* const arguments = &smArg; ((0, 179), 1064, 1064) -> ((0, 179), 1064, 1064); restored
- High TMCJPEGDEC_exif_parse: Private parser input parameter mutable byte view: ((0, 21), 212, 212) -> compile failure; restored
- High TMCJPEGDEC_exif_parse: Mutable parser input exposes readonly byte view for directory arithmetic: ((0, 21), 212, 212) -> compile failure; restored
- High TMCJPEGDEC_exif_parse: Mutable private parser receives opaque pointer then narrows readonly input: ((0, 21), 212, 212) -> compile failure; restored
- High TMCJPEGDEC_exif_parse: Readonly parser data input passed via pointer to fixed header array: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Private parser mutable formal input with matching caller byte view: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Mutable parser input narrows readonly view and caller uses writable buffer pointer: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Mutable opaque private input with const byte parser view and compatible caller: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High NWC24iDateToOSCalendarTime: register-only last explicit declaration span 87-88: ((0, 13), 85, 85) -> ((0, 13), 85, 85); order was:
- High ConvertDaysToDate: register-only last explicit declaration span 228-230: ((0, 6), 103, 103) -> ((0, 6), 103, 103); order was:
- High TMCJPEGDEC_exif_parse: Byte-order marker assembled by narrow scalar reader with fixed little-endian order: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Byte-order marker initialization uses a named narrow byte pair: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: First-directory pointer initialized by private const input offset helper: ((0, 21), 212, 212) -> ((0, 54), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Byte-order receiver plain struct field preserves narrow type: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High TMCJPEGDEC_exif_parse: Serialized base held in typed one-pointer input view: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: seven real receiver/event declarations moved to function leading scope, assignment order preserved, then register-only declsearch: ((0, 179), 1064, 1064) -> ((0, 175), 1064, 1064); kept; (0, 175) after 52 builds; kept in source:
- High NWC24iDateToOSCalendarTime: register-only last explicit declaration span 121-122: ((0, 13), 85, 85) -> ((0, 13), 85, 85); order was:
High Calendar declaration range corrected to actual function definition; earlier generic first-identifier range selected Minutes function flag/blank and was restored. No other function change retained.
- High NWC24iSetMsgSubjectBase64: Private workspace formal opaque pointer then mutable byte view: ((0, 5), 136, 136) -> ((0, 43), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Opaque workspace byte view declared after other plain locals: ((0, 5), 136, 136) -> ((0, 16), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Readonly workspace parameter with writable local view for encoder destination: ((0, 5), 136, 136) -> ((0, 43), 136, 136); restored
- High NWC24iSetMsgSubjectBase64: Opaque workspace view assigned before splitting buffers: ((0, 5), 136, 136) -> ((0, 43), 136, 136); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Visibility receiver declarations placed with other actual function receivers: ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Shared visible button receiver used across both display-mode branches: ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Saved-data pointer binding is const input object pointer from its actual read scope: ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: TextBox pointer widened to generic Pane after declaration graph search: ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor message input view const Arg* arguments = &smArg; ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor both input view const Arg* arguments = &smArg; ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor message input view const Arg& arguments = smArg; ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor both input view const Arg& arguments = smArg; ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor message input view Arg* const arguments = &smArg; ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: guarded System accessor both input view Arg* const arguments = &smArg; ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Scene loops reuse named function-scope index with initialization at each actual loop: ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: First title cache loop uses int index instead of SDK signed long: ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Title cache count uses int instead of SDK signed long: ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored
- High create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: Cached title count computed with canonical limit loop and index result: ((0, 175), 1064, 1064) -> ((0, 175), 1064, 1064); restored

### High final attempt audit
- ConvertDaysToDate: 7 distinct successfully compiled source-level trial labels this high round, before register searches.
- NWC24iSetMsgSubjectBase64: 9 distinct successfully compiled source-level trial labels this high round, before register searches.
- NWC24iDateToOSCalendarTime: 6 distinct successfully compiled source-level trial labels this high round, before register searches.

### High final attempt audit
- ConvertDaysToDate: 25 distinct successfully compiled source-level trial labels this high round, before register searches.
- NWC24iSetMsgSubjectBase64: 26 distinct successfully compiled source-level trial labels this high round, before register searches.
- NWC24iDateToOSCalendarTime: 22 distinct successfully compiled source-level trial labels this high round, before register searches.
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: 29 distinct successfully compiled source-level trial labels this high round, before register searches.
- TMCJPEGDEC_exif_parse: 41 distinct successfully compiled source-level trial labels this high round, before register searches.
The five selected functions were explored beyond the three-trial minimum; no selected function remains untried. Helpers/const views/definition types/branch scope were checked before declaration searches. Extents do not overlap. Target shows no immediate same-slot stw/lwz proof, so no volatile was added. Both guarded header experiments were fully restored, leaving no header edits or output in another unit. Retained narrow Exif scalar43->21 instruction differences, create declarations179->175. Quick full-system gate passed; each remaining per-function fuzzy percentage was compared with high baseline and none dropped. No new exact function yet. The first label-counting audit script failed parsing a differently formatted log row; corrected it and asserted all five counts here.

### High final full nonquick gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 3352/5352 data 232/232 functions 8/12 fuzzy 99.2638 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 8/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 99.263824
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectBase64 99.632355
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 3352/5352 data 232 functions 8 fuzzy 99.2638
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1168/2372 data 40/40 functions 5/8 fuzzy 99.2462 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 5/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.24621
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: NWC24iDateToOSCalendarTime 99.17647
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 99.70874
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 98.9005
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 96.5016 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 96.50157
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 94.46986
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 93.099174
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 96.2893
[src/scene/setting/AOSSLink] pool: IDENTICAL
[src/scene/setting/AOSSLink] objdiff: code 668/2196 data 2432/2432 functions 12/14 fuzzy 99.0073 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 12/14
[src/scene/setting/AOSSLink]   section .bss size 2344 match 100.0
[src/scene/setting/AOSSLink]   section .data size 48 match 100.0
[src/scene/setting/AOSSLink]   section .sbss size 40 match 100.0
[src/scene/setting/AOSSLink]   section .text size 2196 match 99.007286
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANGetBSSList 98.48018
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANConnect 98.70968
[src/scene/setting/AOSSLink] baseline: code 668/2196 data 2432 functions 12 fuzzy 91.1111
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3136/5504 data 7680/7680 functions 26/29 fuzzy 96.4608 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 26/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 96.460754
[src/keyboard/tiZiString]   below 100: clearCandidates__Q39textinput8tistring6WithZiFv 93.28395
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 91.70852
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 90.33846
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 96.3074
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14812/20872 data 3344/3344 functions 64/66 fuzzy 99.2035 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 63/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.20353
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 99.15884
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 92.7694
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14812/20872 data 3344 functions 64 fuzzy 98.9810
regressions vs baseline: 0
global matched_code_percent: 89.30427 -> 89.30427
global fuzzy_match_percent: 99.52654 -> 99.53481
global complete_code_percent: 67.07732 -> 67.07732
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
High before -> after instruction-exact functions, matched code bytes, matched data bytes, fuzzy unit percentage:
- libs/RevoEX/src/nwc24/NWC24MsgSubject: instruction exact 8/12 -> 8/12; code 3352/5352 -> 3352/5352; data 232/232 -> 232/232; fuzzy 99.2638 -> 99.2638.
- libs/RevoEX/src/nwc24/NWC24DateParser: instruction exact 5/8 -> 5/8; code 1168/2372 -> 1168/2372; data 40/40 -> 40/40; fuzzy 99.2462 -> 99.2462.
- libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse: instruction exact 3/6 -> 3/6; code 1348/5088 -> 1348/5088; data None/None -> None/None; fuzzy 96.3915 -> 96.5016.
- src/scene/setting/AOSSLink: instruction exact 12/14 -> 12/14; code 668/2196 -> 668/2196; data 2432/2432 -> 2432/2432; fuzzy 99.0073 -> 99.0073.
- src/keyboard/tiZiString: instruction exact 26/29 -> 26/29; code 3136/5504 -> 3136/5504; data 7680/7680 -> 7680/7680; fuzzy 96.4608 -> 96.4608.
- src/scene/sdChannelMemory/iplSDMemory: instruction exact 63/66 -> 63/66; code 14812/20872 -> 14812/20872; data 3344/3344 -> 3344/3344; fuzzy 99.1978 -> 99.2035.

Remaining17 functions, final clean rebuilt exact-name percentages:
- NWC24ReadMsgSubjectPublic: 96.15385%; 100/104; redundant overflow exit branches.
- NWC24ReadMsgTextPublic: 97.14286%; 68/70; redundant overflow exit branches.
- NWC24SetMsgSubjectAndTextPublic: 98.23684%; 190/190; input/context saved register allocation.
- NWC24iSetMsgSubjectBase64: 99.632355%; 136/136; five parameter-save copy order differences.
- NWC24iDateToOSCalendarTime: 99.17647%; 85/85; year and leap/zero registers exchanged.
- ConvertDateToDays: 96.92921%; 113/113; quotient/add scheduling and temporaries.
- ConvertDaysToDate: 99.70874%; 103/103; six month versus leap register differences.
- TMCJPEGDEC_exif_parse: 99.43396%; 212/212;21 saved base/first-directory/count/extent register differences, byte readers now exact.
- TMCJPEGDEC_IFD0_tag_parse: 94.46986%; 481/481; switch topology/byte-reader operand order.
- TMCJPEGDEC_IFD1_tag_parse: 93.099174%; 239/242; switch topology/byte-reader operand order.
- AOSSi_WLANGetBSSList: 98.48018%; 227/227; channel-store/argument scheduling and loop/retry registers.
- AOSSi_WLANConnect: 98.70968%; 155/155; two memset argument setup instructions reversed.
- clearCandidates__Q39textinput8tistring6WithZiFv: 93.28395%; 84/81; global candidate base and helper boundaries.
- update__Q39textinput8tistring6WithZiFv: 91.70852%; 447/446; candidate search lifetime and Korean loop structure.
- setElementBuffer__Q39textinput8tistring6WithZiFv: 90.33846%; 65/65; buffer base/load ordering and registers.
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: 99.15884%; 1064/1064;175 pool/System/TextBox and late temporary register differences.
- drawTransferTitles__Q33ipl5scene8SDMemoryFv: 92.7694%; 439/451; newline loop and Color copy boundaries/stack offsets.
High work gained zero new exact functions. Five closest functions received25,26,22,29,41 distinct compiled source trials respectively, plus declaration searches. This round leaves only exif_parse.c narrow readExifU16 local and iplSDMemory.cpp seven existing local declarations moved before assignments, plus this log. No header or symbol configuration change. All six pools/data remain exact; final full gate rebuild and DOL hash pass; global regressions0, forbidden0, readability0. Acceptance criterion of increasing instruction-exact count remains unachieved. SD instruction count63 versus objdiff64 is the previously proven identical-word disassembly artifact, not an additional open function. Higher effort may still resolve register allocation; no source-level impossibility claim.

## Round xhigh on same branch28639969
Closest four genuine open functions selected by current exact-name objdiff percentage. All six pools/data remain identical.
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 3352/5352 data 232/232 functions 8/12 fuzzy 99.2638 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 8/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 99.263824
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24iSetMsgSubjectBase64 99.632355
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 3352/5352 data 232 functions 8 fuzzy 99.2638
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1168/2372 data 40/40 functions 5/8 fuzzy 99.2462 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 5/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.24621
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: NWC24iDateToOSCalendarTime 99.17647
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 99.70874
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 98.9005
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 96.5016 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 96.50157
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 94.46986
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 93.099174
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 96.2893
[src/scene/setting/AOSSLink] pool: IDENTICAL
[src/scene/setting/AOSSLink] objdiff: code 668/2196 data 2432/2432 functions 12/14 fuzzy 99.0073 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 12/14
[src/scene/setting/AOSSLink]   section .bss size 2344 match 100.0
[src/scene/setting/AOSSLink]   section .data size 48 match 100.0
[src/scene/setting/AOSSLink]   section .sbss size 40 match 100.0
[src/scene/setting/AOSSLink]   section .text size 2196 match 99.007286
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANGetBSSList 98.48018
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANConnect 98.70968
[src/scene/setting/AOSSLink] baseline: code 668/2196 data 2432 functions 12 fuzzy 91.1111
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3136/5504 data 7680/7680 functions 26/29 fuzzy 96.4608 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 26/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 96.460754
[src/keyboard/tiZiString]   below 100: clearCandidates__Q39textinput8tistring6WithZiFv 93.28395
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 91.70852
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 90.33846
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 96.3074
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14812/20872 data 3344/3344 functions 64/66 fuzzy 99.2035 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 63/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.20353
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 99.15884
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 92.7694
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14812/20872 data 3344 functions 64 fuzzy 98.9810
regressions vs baseline: 0
global matched_code_percent: 89.30427 -> 89.30427
global fuzzy_match_percent: 99.52654 -> 99.53481
global complete_code_percent: 67.07732 -> 67.07732
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

### XHigh ConvertDaysToDate
Fetched origin; source agrees with earlier known below100 origin baseline. Immediate same-slot stack store/reload pairs=[], so no volatile evidence. Extent0x814ac50c+0x19c ends before/equal next NWC24ReadFriendInfo; no symbols.txt correction justified.
src 0x19c base 0x19c insns 103/103
diffs 6: [55, 57, 60, 83, 84, 88]
    55 M lbz r12, 0(r4)
       B lbz r0, 0(r4)
    57 M cmplwi r12, 2
       B cmplwi r0, 2
    60 M li r0, 0
       B li r12, 0
    83 M li r0, 1
       B li r12, 1
    84 M cmpwi r0, 0
       B cmpwi r12, 0
    88 M add r8, r9, r12
       B add r8, r9, r0

### XHigh NWC24iSetMsgSubjectBase64
Fetched origin; source agrees with earlier known below100 origin baseline. Immediate same-slot stack store/reload pairs=[], so no volatile evidence. Extent0x814aab18+0x220 ends before/equal next NWC24SuspendScheduler; no symbols.txt correction justified.
src 0x220 base 0x220 insns 136/136
diffs 5: [8, 9, 10, 11, 12]
     8 M mr r18, r4
       B mr r22, r8
     9 M mr r19, r5
       B mr r18, r4
    10 M mr r20, r6
       B mr r19, r5
    11 M mr r21, r7
       B mr r20, r6
    12 M mr r22, r8
       B mr r21, r7

### XHigh TMCJPEGDEC_exif_parse
Fetched origin; source agrees with earlier known below100 origin baseline. Immediate same-slot stack store/reload pairs=[], so no volatile evidence. Extent0x814ee1a0+0x350 ends before/equal next TMCJPEGDEC_IFD0_tag_parse; no symbols.txt correction justified.
src 0x350 base 0x350 insns 212/212
diffs 21: [7, 61, 69, 70, 77, 79, 80, 82, 89, 92, 95, 97, 104, 106, 107, 109, 128, 144, 146, 162]
     7 M mr r27, r3
       B mr r30, r3
    61 M add r30, r3, r5
       B add r27, r3, r5
    69 M lbz r4, 1(r30)
       B lbz r4, 1(r27)
    70 M lbz r3, 0(r30)
       B lbz r3, 0(r27)
    77 M clrlwi r26, r0, 0x10
       B clrlwi r23, r0, 0x10
    79 M mulli r23, r26, 0xc
       B mulli r26, r23, 0xc
    80 M addi r30, r30, 2
       B addi r27, r27, 2
    82 M cmpw r25, r23
       B cmpw r25, r26
    89 M mr r5, r30
       B mr r5, r27
    92 M addi r30, r30, 0xc
       B addi r27, r27, 0xc
    95 M cmplw r0, r26
       B cmplw r0, r23
    97 M subf r0, r23, r25
       B subf r0, r26, r25
   104 M lbz r3, 1(r30)
       B lbz r3, 1(r27)
   106 M lbz r4, 2(r30)
       B lbz r4, 2(r27)
   107 M lbz r5, 0(r30)
       B lbz r5, 0(r27)
   109 M lbz r0, 3(r30)
       B lbz r0, 3(r27)
   128 M add r26, r27, r3
       B add r26, r30, r3
   144 M clrlwi r30, r0, 0x10
       B clrlwi r27, r0, 0x10
   146 M mulli r0, r30, 0xc
       B mulli r0, r27, 0xc
   162 M cmplw r0, r30
       B cmplw r0, r27
   170 M add r26, r27, r3
       B add r26, r30, r3

### XHigh NWC24iDateToOSCalendarTime
Fetched origin; source agrees with earlier known below100 origin baseline. Immediate same-slot stack store/reload pairs=[], so no volatile evidence. Extent0x814ac1c4+0x154 ends before/equal next NWC24iIsValidDate; no symbols.txt correction justified.
src 0x154 base 0x154 insns 85/85
diffs 13: [6, 7, 16, 17, 24, 32, 33, 38, 43, 47, 52, 54, 55]
     6 M lhz r0, 0(r4)
       B lhz r5, 0(r4)
     7 M li r5, 0
       B li r0, 0
    16 M slwi r6, r0, 0x1e
       B slwi r6, r5, 0x1e
    17 M srwi r7, r0, 0x1f
       B srwi r7, r5, 0x1f
    24 M stw r0, 0x14(r3)
       B stw r5, 0x14(r3)
    32 M stw r5, 0x20(r3)
       B stw r0, 0x20(r3)
    33 M stw r5, 0x24(r3)
       B stw r0, 0x24(r3)
    38 M mulhw r7, r7, r0
       B mulhw r7, r7, r5
    43 M subf. r7, r7, r0
       B subf. r7, r7, r5
    47 M mulhw r7, r7, r0
       B mulhw r7, r7, r5
    52 M subf. r0, r7, r0
       B subf. r5, r7, r5
    54 M li r5, 1
       B li r0, 1
    55 M cmpwi r5, 0
       B cmpwi r0, 0
- XHigh ConvertDaysToDate: Leap helper defined after caller with prior inline prototype: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper is ordinary static function with automatic inlining: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper return returned through one additional typed inline boundary: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Month input value const at definition rather than separately assigned: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper flag reused as accumulated Boolean: ((0, 6), 103, 103) -> ((1, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper flag established through conditional assignment expression: ((0, 6), 103, 103) -> ((9, 104), 109, 103); restored
- XHigh ConvertDaysToDate: Month subtraction helper owns readonly year and month values: ((0, 6), 103, 103) -> ((0, 27), 103, 103); restored
- XHigh ConvertDaysToDate: Month subtraction helper updates days through typed output parameter: ((0, 6), 103, 103) -> ((0, 27), 103, 103); restored
- XHigh ConvertDaysToDate: Leap flag comparison normalizes return as true explicitly: ((0, 6), 103, 103) -> ((2, 7), 103, 103); restored
- XHigh ConvertDaysToDate: Month-loop condition inverted with ordinary-month branch first: ((0, 6), 103, 103) -> ((6, 12), 103, 103); restored
- XHigh ConvertDaysToDate: Month loop expressed as do while retaining both exit tests: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Month leap helper input pointer readonly with year load scoped after month guard: ((0, 6), 103, 103) -> ((0, 27), 103, 103); restored
- XHigh ConvertDaysToDate: Month guard and table lookup directly read const input without named scalar: ((0, 6), 103, 103) -> ((0, 29), 103, 103); restored
- XHigh ConvertDaysToDate: Month guard uses const input directly but table retains saved scalar: ((0, 6), 103, 103) -> ((0, 29), 103, 103); restored
- XHigh ConvertDaysToDate: Month table uses const input directly but guard retains saved scalar: ((0, 6), 103, 103) -> ((0, 29), 103, 103); restored
- XHigh ConvertDaysToDate: Month-loop previous days saved after the month load: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper flag uses signed long ternary assignment at declaration: ((0, 6), 103, 103) -> ((0, 33), 103, 103); restored
- XHigh ConvertDaysToDate: Month loaded through const inline accessor directly at both uses: ((0, 6), 103, 103) -> ((0, 29), 103, 103); restored
- XHigh ConvertDaysToDate: One common leap flag reused between year and month loops: ((0, 6), 103, 103) -> ((0, 34), 103, 103); restored
- XHigh ConvertDaysToDate: One overall leap flag reused between year and month loops: ((0, 6), 103, 103) -> compile failure; restored
- XHigh ConvertDaysToDate: Month scalar declared at function scope before both loops: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Previous-day saved value shared across both loops: ((0, 6), 103, 103) -> compile failure; restored
- XHigh ConvertDaysToDate: Month const view declared at function scope before loops: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Shared year local controls both annual and leap-month subtraction: ((0, 6), 103, 103) -> compile failure; restored
- XHigh ConvertDaysToDate: Both leap flags have function scope while year-loop values remain local: ((0, 6), 103, 103) -> ((0, 20), 103, 103); restored
- XHigh ConvertDaysToDate: Saved days has function scope shared across year and month loops C89 declarations retained: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Month result and annual leap flag share function scope: ((0, 6), 103, 103) -> ((2, 18), 103, 103); restored
- XHigh ConvertDaysToDate: Year value has function scope with explicit month guard reload: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Overall leap flag reused in month conditional after C89 declaration order fix: ((0, 6), 103, 103) -> ((2, 18), 103, 103); restored
- XHigh ConvertDaysToDate: Common leap flag and month scalar shared scope with readonly input: ((0, 6), 103, 103) -> ((0, 34), 103, 103); restored
- XHigh NWC24iDateToOSCalendarTime: Mutable formal date input rather than const local cast changes alias model: ((0, 13), 85, 85) -> ((38, 85), 87, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Leap helper return assigned via logical OR to existing initialized flag: ((0, 13), 85, 85) -> ((47, 80), 86, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Leap helper return guarded before existing flag assignment: ((0, 13), 85, 85) -> ((8, 68), 89, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Year read through typed const inline accessor for both field and leap test: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Year read through const scalar-field pointer accessor: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Leap test reads already copied calendar year through const output view: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Calendar fractional zeros supplied by typed helper after primary fields: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Independent leap flag is scoped inside field population block: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iSetMsgSubjectBase64: Complete encoding inline helper argument grouping 0: ((0, 5), 136, 136) -> ((11, 36), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Complete encoding inline helper argument grouping 1: ((0, 5), 136, 136) -> ((11, 36), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Complete encoding inline helper argument grouping 2: ((0, 5), 136, 136) -> ((11, 36), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Writable inputBuffer named alias initialized first in declaration block: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Const binding inputBuffer initialized first in declaration block: ((0, 5), 136, 136) -> ((0, 43), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Writable inputBuffer named alias initialized last in declaration block: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Const binding inputBuffer initialized last in declaration block: ((0, 5), 136, 136) -> ((0, 16), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Base64 workspace alias first assignment before declaration-split work pointer: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Workspace address computed via unsigned byte array indexing: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Work half split represented as division by two: ((0, 5), 136, 136) -> ((0, 5), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: First buffer mutable view and later base64 input readonly view separated: ((0, 5), 136, 136) -> ((0, 0), 136, 136); kept
- XHigh NWC24iSetMsgSubjectBase64: Second buffer ordinary pointer initialized at leading definition: ((0, 0), 136, 136) -> ((0, 0), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Both buffer pointer and size initialized at leading definitions: ((0, 0), 136, 136) -> ((0, 0), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Workspace second pointer explicit plus equals split assignment: ((0, 0), 136, 136) -> ((0, 0), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Capacity computed as original size minus pointer distance: ((0, 0), 136, 136) -> ((7, 132), 137, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Address and capacity produced in workspace-first inline view helper: ((0, 0), 136, 136) -> ((0, 0), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Named buffer first half plain alias declared immediately before result: ((0, 0), 136, 136) -> ((0, 0), 136, 136); restored
- XHigh NWC24iSetMsgSubjectBase64: Base64 line size calculation owns charset read in inline helper: ((0, 0), 136, 136) -> ((0, 14), 136, 136); restored

XHigh Base64 exact: input buffer has mutable work view for NWC24iConvertFromInternalEncoding destinations and const encodedInput view for both NWC24EncodeWord decoded inputs; that API passes decoded bytes only to read/encode operations. Declaring only that input view changes the five prologue saves to target work-first order, ctxdiff136/136 diffs0; pool identical; full quick gate all six GATE PASS, regressions0, forbidden0, readability0. No symbol edits.
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 3896/5352 data 232/232 functions 9/12 fuzzy 99.3012 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 9/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 99.30119
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 3352/5352 data 232 functions 8 fuzzy 99.2638
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1168/2372 data 40/40 functions 5/8 fuzzy 99.2462 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 5/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.24621
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: NWC24iDateToOSCalendarTime 99.17647
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 99.70874
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 98.9005
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 96.5016 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 96.50157
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 94.46986
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 93.099174
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 96.2893
[src/scene/setting/AOSSLink] pool: IDENTICAL
[src/scene/setting/AOSSLink] objdiff: code 668/2196 data 2432/2432 functions 12/14 fuzzy 99.0073 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 12/14
[src/scene/setting/AOSSLink]   section .bss size 2344 match 100.0
[src/scene/setting/AOSSLink]   section .data size 48 match 100.0
[src/scene/setting/AOSSLink]   section .sbss size 40 match 100.0
[src/scene/setting/AOSSLink]   section .text size 2196 match 99.007286
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANGetBSSList 98.48018
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANConnect 98.70968
[src/scene/setting/AOSSLink] baseline: code 668/2196 data 2432 functions 12 fuzzy 91.1111
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3136/5504 data 7680/7680 functions 26/29 fuzzy 96.4608 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 26/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 96.460754
[src/keyboard/tiZiString]   below 100: clearCandidates__Q39textinput8tistring6WithZiFv 93.28395
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 91.70852
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 90.33846
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 96.3074
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14812/20872 data 3344/3344 functions 64/66 fuzzy 99.2035 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 63/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.20353
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 99.15884
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 92.7694
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14812/20872 data 3344 functions 64 fuzzy 98.9810
regressions vs baseline: 0
global matched_code_percent: 89.30427 -> 89.32243
global fuzzy_match_percent: 99.52654 -> 99.53488
global complete_code_percent: 67.07732 -> 67.07732
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- XHigh NWC24iDateToOSCalendarTime: Year field readonly pointer view used only for leap predicate: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Year field readonly pointer view used for initial copy and predicate: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Leap year view through const date alias reserved for predicate only: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Fractional zeros written through separate calendar output binding: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Calendar read-only output view used for year only after field copy: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Leap flag uses unsigned char definition rather than SDK BOOL: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Leap flag uses signed16 definition rather than SDK BOOL: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Leap flag value and calendar fraction clears use enum false constant: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Year copy performed through self-contained inline assignment helper: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Primary date copies have inner scope separated from fractional clears: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Leap true assignment expressed as increment of initialized flag: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Leap true assignment expressed as addition of true to zero flag: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Plain year local assigned before leap initialization with all reads named: ((0, 13), 85, 85) -> ((2, 19), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Plain year local assigned after leap initialization with all reads named: ((0, 13), 85, 85) -> ((2, 19), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Calendar year const binding initialized after flag definition before field copy: ((0, 13), 85, 85) -> ((1, 4), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Calendar year const binding defined before flag with predicate-only usage: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Calendar year and leap flag held in scalarized semantic year record: ((0, 13), 85, 85) -> ((2, 19), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Calendar fraction default and leap flag held in scalarized semantic status record: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Successful conversion return uses declared result status: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Calendar fractional field clearing performed before leap flag initialized: ((0, 13), 85, 85) -> ((0, 13), 85, 85); restored
- XHigh NWC24iDateToOSCalendarTime: Year const read binding after day-count declaration while later days conversion reloads input: ((0, 13), 85, 85) -> ((0, 0), 85, 85); kept
- XHigh NWC24iDateToOSCalendarTime: Year const read binding before day-count declaration while later conversion reloads input: ((0, 0), 85, 85) -> compile failure; restored
- XHigh NWC24iDateToOSCalendarTime: Year const read binding after day count and flag initialized at definition: ((0, 0), 85, 85) -> compile failure; restored
- XHigh NWC24iDateToOSCalendarTime: Year const read binding last with day count declared int: ((0, 0), 85, 85) -> compile failure; restored
- XHigh NWC24iDateToOSCalendarTime: Year const read binding last with Boolean flag declared int: ((0, 0), 85, 85) -> compile failure; restored
- XHigh NWC24iDateToOSCalendarTime: Year readonly value binding used only in initial copy and modulo expressions: ((0, 0), 85, 85) -> compile failure; restored

XHigh calendar exact: readonly u16 year value captured after existing day-count and leap declarations feeds initial year copy and leap predicate, while ConvertDateToDays explicitly reloads date->year later as target does. Initial attempt using captured year for the later call gave85/85 four diffs including wrong mr instead of lhz and retained year lifetime; preserving that late read gives85/85 diffs0 and pool identical. Later batch variants accidentally repeated the new declaration and failed C89 compilation; every failure restored the exact source, and no failed compilation counts as a distinct source attempt.
XHigh calendar quick gate all six: GATE PASS; regressions0, forbidden0, readability0; exact-name objdiff100 and instruction-exact DateParser6/8.
```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 3896/5352 data 232/232 functions 9/12 fuzzy 99.3012 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 9/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 99.30119
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 3352/5352 data 232 functions 8 fuzzy 99.2638
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1508/2372 data 40/40 functions 6/8 fuzzy 99.3642 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 6/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.36425
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 99.70874
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 98.9005
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 96.5016 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 96.50157
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 94.46986
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 93.099174
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 96.2893
[src/scene/setting/AOSSLink] pool: IDENTICAL
[src/scene/setting/AOSSLink] objdiff: code 668/2196 data 2432/2432 functions 12/14 fuzzy 99.0073 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 12/14
[src/scene/setting/AOSSLink]   section .bss size 2344 match 100.0
[src/scene/setting/AOSSLink]   section .data size 48 match 100.0
[src/scene/setting/AOSSLink]   section .sbss size 40 match 100.0
[src/scene/setting/AOSSLink]   section .text size 2196 match 99.007286
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANGetBSSList 98.48018
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANConnect 98.70968
[src/scene/setting/AOSSLink] baseline: code 668/2196 data 2432 functions 12 fuzzy 91.1111
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3136/5504 data 7680/7680 functions 26/29 fuzzy 96.4608 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 26/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 96.460754
[src/keyboard/tiZiString]   below 100: clearCandidates__Q39textinput8tistring6WithZiFv 93.28395
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 91.70852
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 90.33846
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 96.3074
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14812/20872 data 3344/3344 functions 64/66 fuzzy 99.2035 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 63/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.20353
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 99.15884
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 92.7694
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14812/20872 data 3344 functions 64 fuzzy 98.9810
regressions vs baseline: 0
global matched_code_percent: 89.30427 -> 89.33379
global fuzzy_match_percent: 99.52654 -> 99.53497
global complete_code_percent: 67.07732 -> 67.07732
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
- XHigh TMCJPEGDEC_exif_parse: Directory byte view const u8* reserved for scopes [0]: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory byte view const u8* const reserved for scopes [0]: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory byte view const u8* reserved for scopes [1, 2]: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory byte view const u8* const reserved for scopes [1, 2]: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory byte view const u8* reserved for scopes [0, 1, 2]: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory byte view const u8* const reserved for scopes [0, 1, 2]: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Mutable input view for header and thumbnail pointers while directory view remains readonly: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Header view is immutable const pointer while directory arithmetic uses original formal: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Later directory base read from stored thumbnail field through const record view: ((0, 21), 212, 212) -> ((21, 179), 214, 212); restored
- XHigh TMCJPEGDEC_exif_parse: First-directory byte extent derived from exact entry record type size: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory view pointer binding has const pointer after first initialization: ((0, 21), 212, 212) -> ((0, 56), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Narrow count reader readonly value copied through a const scalar return binding: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh ConvertDaysToDate: Saved previous month days const binding at definition before month view: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Saved previous month days const binding defined after month view: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Month index const binding retains byte type and conditional helper scope: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- XHigh ConvertDaysToDate: Leap month year const value and explicit flag declared inside February guard: ((0, 6), 103, 103) -> ((0, 23), 103, 103); restored
- XHigh ConvertDaysToDate: Leap month year plain value and explicit flag declared inside February guard: ((0, 6), 103, 103) -> ((0, 31), 103, 103); restored
- XHigh ConvertDaysToDate: Inline leap input promoted to const signed32 binding in guarded helper: ((0, 6), 103, 103) -> compile failure; restored
- XHigh TMCJPEGDEC_exif_parse: Entry count unsigned32 with narrow conversion retained by helper: ((0, 21), 212, 212) -> ((0, 38), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Entry count unsigned int with narrow comparison cast: ((0, 21), 212, 212) -> ((0, 38), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Entry count signed32 with explicit narrow extent and loop uses: ((0, 21), 212, 212) -> ((0, 38), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory remaining count signed32 retaining unsigned16 updates: ((0, 21), 212, 212) -> ((4, 45), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Distinct leading locals for directory scopes count: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Distinct leading locals for directory scopes entries: ((0, 21), 212, 212) -> ((0, 34), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Distinct leading locals for directory scopes entriesSize: ((0, 21), 212, 212) -> ((0, 30), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Distinct leading locals for directory scopes count,entriesSize: ((0, 21), 212, 212) -> ((0, 30), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Distinct leading locals for directory scopes entries,count,entriesSize: ((0, 21), 212, 212) -> ((0, 43), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Distinct leading locals for directory scopes remaining,index,count,entriesSize: ((0, 21), 212, 212) -> ((0, 33), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: First-directory extent captured in const binding following count read: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Narrow count value stored and returned from explicit reader result local: ((0, 21), 212, 212) -> ((4, 25), 212, 212); restored
- XHigh ConvertDaysToDate: Leap helper year value and flag grouped in semantic scalarized record: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper year value readonly signed32 bound after flag initializer: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper year and const u16 year value under nested expression scope: ((0, 6), 103, 103) -> ((0, 27), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper year and const s32 year value under nested expression scope: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Month guard and year flag produced together by readonly pointer helper: ((0, 6), 103, 103) -> ((6, 49), 105, 103); restored
- XHigh ConvertDaysToDate: Month guard and year flag produced together by byte value helper: ((0, 6), 103, 103) -> ((6, 47), 105, 103); restored
- XHigh ConvertDaysToDate: Month table operand is read through readonly pointer-to-array view: ((0, 6), 103, 103) -> ((0, 27), 103, 103); restored
- XHigh ConvertDaysToDate: Month table day count read through inline scalar accessor: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh TMCJPEGDEC_exif_parse: Parser-specific wide scalar reader copies existing readonly readU32 boundary: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Parser-specific wide reader value const at its definition: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Parser-specific wide reader value unsigned int at definition: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Parser-specific wide reader value declared then assembled: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Parser-specific wide reader byte input const pointer binding: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Parser-specific wide reader byte-order scalar const binding: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Parser-specific wide reader read-only bytes view from opaque input: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory pointer extent computed as fixed entry-size shift-and-sum: ((0, 21), 212, 212) -> ((29, 153), 218, 212); restored
- XHigh TMCJPEGDEC_exif_parse: First entry pointer and extent have inner-directory scope after header checks: ((0, 21), 212, 212) -> ((0, 34), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Count reader result narrow alias distinct from loop bound variable: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: IFD byte extent declared as ptrdiff_t matching pointer-distance type: ((0, 21), 212, 212) -> compile failure; restored
- XHigh TMCJPEGDEC_exif_parse: First-directory remaining count literal update assignment instead of compound: ((0, 21), 212, 212) -> ((0, 29), 212, 212); restored
- XHigh ConvertDaysToDate: Current month scalar plain char rather than unsigned byte typedef: ((0, 6), 103, 103) -> ((4, 49), 104, 103); restored
- XHigh ConvertDaysToDate: Leap helper Boolean plain char local rather than SDK long: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Month readonly u8 scalar inside scope after saving days: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- XHigh ConvertDaysToDate: Month readonly u16 scalar inside scope after saving days: ((0, 6), 103, 103) -> ((0, 26), 103, 103); restored
- XHigh ConvertDaysToDate: Month readonly s32 scalar inside scope after saving days: ((0, 6), 103, 103) -> ((1, 26), 103, 103); restored
- XHigh ConvertDaysToDate: Saved previous days assigned through explicit scoped const capture: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Common-year month day read explicit byte local only inside else branch: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Saved remaining days assigned with subtraction expressed as one conditional: ((0, 6), 103, 103) -> ((9, 55), 108, 103); restored
- XHigh ConvertDaysToDate: register-only LAST declsearch explicit month block: declaration block: |           s32 previousDays; |           u8 currentMonth; |           const u8* parsedMonth = month; | start (0, 6) | best (0, 6) after 6 builds; source restored; best order was: |         s32 previousDays; |         u8 currentMonth; |         const u8* parsedMonth = month; |
- XHigh ConvertDaysToDate: exhaustive joint declaration orders across annual four and month three independent locals, plus Boolean-return/const-ternary inline-helper boundaries: 288 successful object builds; ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored; score distribution {('flag', '(0, 6)'): 24, ('flag', '(2, 32)'): 18, ('flag', '(2, 37)'): 6, ('flag', '(0, 17)'): 24, ('flag', '(0, 20)'): 24, ('flag', '(2, 34)'): 18, ('flag', '(2, 17)'): 24, ('flag', '(2, 39)'): 6, ('ternary', '(0, 33)'): 24, ('ternary', '(2, 59)'): 18, ('ternary', '(2, 64)'): 6, ('ternary', '(0, 44)'): 24, ('ternary', '(0, 47)'): 24, ('ternary', '(2, 61)'): 18, ('ternary', '(2, 44)'): 24, ('ternary', '(2, 66)'): 6}
- XHigh TMCJPEGDEC_exif_parse: Private parser input bytes formal is immutable pointer to const data: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Private parser data extent formal is const value: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Private parser output receiver formal is immutable pointer: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Private parser extent unsigned int instead of unsigned long SDK typedef: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Private EXIF parser extent narrow16 reflecting APP segment field type: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Wide-reader bytes opaque unsigned pointer const value cast at definition: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Entry count first scope retained unsigned16 but later directory counts separate: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: First-directory index plain local only in first directory: ((0, 21), 212, 212) -> ((0, 24), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: First-directory remaining size plain local only in first directory: ((0, 21), 212, 212) -> ((0, 30), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Narrow reader order formal const unsigned16: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Narrow reader raw word uses explicit source byte array const view: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Narrow reader raw word assembles masked unsigned16 high byte explicitly: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh ConvertDaysToDate: Leap helper year formal int promoted arithmetic input: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper year formal s32 promoted arithmetic input: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper year formal const int promoted arithmetic input: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper year formal const s32 promoted arithmetic input: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper year formal int with byte flag result: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap helper input year record readonly while scalar field accessed inside: ((0, 6), 103, 103) -> ((5, 34), 103, 103); restored

XHigh progress audit before final register search: {'ConvertDaysToDate': 56, 'NWC24iDateToOSCalendarTime': 29, 'NWC24iSetMsgSubjectBase64': 18, 'TMCJPEGDEC_exif_parse': 47} successfully compiled distinct source variants (excluding failures); Base64 and calendar exact in commits ab4394ab and06f5c37a. Month exhaustive joint declaration search288 valid builds plus ordinary declsearch. No unmatched selected function has fewer than three valid source-level attempts.
- XHigh TMCJPEGDEC_exif_parse: Mutable formal byte source with mutable readonly input binding used all: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Mutable formal byte source with immutable readonly input binding used all: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Mutable formal byte source with mutable readonly input binding used late: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Mutable formal byte source with immutable readonly input binding used late: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Mutable formal byte source with mutable readonly input binding used first: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Mutable formal byte source with immutable readonly input binding used first: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record immutable binding at declaration index 0: ((0, 21), 212, 212) -> ((0, 26), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record immutable binding at declaration index 1: ((0, 21), 212, 212) -> ((0, 26), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record immutable binding at declaration index 2: ((0, 21), 212, 212) -> ((0, 26), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record immutable binding at declaration index 3: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record immutable binding at declaration index 4: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record immutable binding at declaration index 5: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record immutable binding at declaration index 6: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record immutable binding at declaration index 7: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record plain pointer binding at declaration index 0: ((0, 21), 212, 212) -> ((0, 23), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Semantic output record plain pointer binding at declaration index 7: ((0, 21), 212, 212) -> ((0, 23), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: register-only LAST declsearch7 leading locals: declaration block: |       u16 byteOrder; |       u32 ifdOffset; |       const u8* entries; |       u16 remaining; |       u16 index; |       s32 entriesSize; |       u16 count; | start (0, 21) | best (0, 21) after 52 builds; source restored; best order was: |     u16 byteOrder; |     u32 ifdOffset; |     const u8* entries; |     u16 remaining; |     u16 index; |     s32 entriesSize; |     u16 count; |
- XHigh TMCJPEGDEC_exif_parse: seeded coordinated declaration permutations across baseline, genuine output-record pointer views and widened count variant: 256 successful object builds; ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored; score distribution {('baseline', '(0, 21)'): 11, ('baseline', '(0, 27)'): 20, ('baseline', '(0, 24)'): 9, ('baseline', '(0, 30)'): 24, ('immutable-record', '(0, 26)'): 7, ('immutable-record', '(0, 27)'): 6, ('immutable-record', '(0, 35)'): 21, ('immutable-record', '(0, 30)'): 14, ('immutable-record', '(0, 21)'): 4, ('immutable-record', '(0, 29)'): 6, ('immutable-record', '(0, 32)'): 2, ('immutable-record', '(0, 24)'): 4, ('plain-record', '(0, 23)'): 19, ('plain-record', '(0, 29)'): 7, ('plain-record', '(0, 32)'): 29, ('plain-record', '(0, 26)'): 9, ('wide-count', '(0, 38)'): 7, ('wide-count', '(0, 43)'): 11, ('wide-count', '(0, 46)'): 32, ('wide-count', '(0, 37)'): 4, ('wide-count', '(0, 40)'): 4, ('wide-count', '(0, 44)'): 6}
- XHigh ConvertDaysToDate: Leap output helper local flag after single February guard, year u16: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap output helper local flag after single February guard, year s32: ((0, 6), 103, 103) -> ((0, 6), 103, 103); restored
- XHigh ConvertDaysToDate: Leap output helper output flag after single February guard, year u16: ((0, 6), 103, 103) -> ((0, 31), 103, 103); restored
- XHigh ConvertDaysToDate: Leap output helper output flag after single February guard, year s32: ((0, 6), 103, 103) -> ((0, 31), 103, 103); restored
- XHigh TMCJPEGDEC_exif_parse: Directory count reader uses typed out parameter delegate: ((0, 21), 212, 212) -> ((0, 21), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory count reader uses typed out parameter local: ((0, 21), 212, 212) -> ((3, 24), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Directory count reader uses typed out parameter output: ((0, 21), 212, 212) -> ((15, 50), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Count output helper input order count output last: ((0, 21), 212, 212) -> ((3, 24), 212, 212); restored
- XHigh TMCJPEGDEC_exif_parse: Count output helper all readers including magic use typed local outputs: ((0, 21), 212, 212) -> ((4, 25), 212, 212); restored

XHigh final pre-gate: final locked origin fetch succeeded; all six origin/main sources remain byte-identical to initial9c641682, so neither new match duplicated an upstream-landed function. Structural audit and all selected extents remain valid, no overlaps. No selected function contains an immediate local store/reload proof; no volatile introduced. No data names/extents edited: all data already100 by name, all pools identical.
Selected remaining functions after deep source trials and last declaration searches: ConvertDaysToDate103/103 six month/flag register differences; TMCJPEGDEC_exif_parse212/21221 data/entries/count/extent register differences. Both exceed three valid distinct attempts; coordinated register searches288 and256 object builds also exhausted. New exact functions: Base64subject136/136 diffs0; DateToOSCalendarTime85/85 diffs0.

### XHigh final full nonquick gate over all six owned units
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RevoEX/src/nwc24/NWC24MsgSubject] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24MsgSubject] objdiff: code 3896/5352 data 232/232 functions 9/12 fuzzy 99.3012 linked code 0
[libs/RevoEX/src/nwc24/NWC24MsgSubject] instruction-exact functions: 9/12
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .data size 184 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .sdata size 48 match 100.0
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   section .text size 5352 match 99.30119
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgSubjectPublic 96.15385
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24ReadMsgTextPublic 97.14286
[libs/RevoEX/src/nwc24/NWC24MsgSubject]   below 100: NWC24SetMsgSubjectAndTextPublic 98.23684
[libs/RevoEX/src/nwc24/NWC24MsgSubject] baseline: code 3352/5352 data 232 functions 8 fuzzy 99.2638
[libs/RevoEX/src/nwc24/NWC24DateParser] pool: IDENTICAL
[libs/RevoEX/src/nwc24/NWC24DateParser] objdiff: code 1508/2372 data 40/40 functions 6/8 fuzzy 99.3642 linked code 0
[libs/RevoEX/src/nwc24/NWC24DateParser] instruction-exact functions: 6/8
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .rodata size 40 match 100.0
[libs/RevoEX/src/nwc24/NWC24DateParser]   section .text size 2372 match 99.36425
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDateToDays 96.92921
[libs/RevoEX/src/nwc24/NWC24DateParser]   below 100: ConvertDaysToDate 99.70874
[libs/RevoEX/src/nwc24/NWC24DateParser] baseline: code 1168/2372 data 40 functions 5 fuzzy 98.9005
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] pool: IDENTICAL
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] objdiff: code 1348/5088 data None/None functions 3/6 fuzzy 96.5016 linked code 0
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] instruction-exact functions: 3/6
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   section .text size 5088 match 96.50157
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_exif_parse 99.43396
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD0_tag_parse 94.46986
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse]   below 100: TMCJPEGDEC_IFD1_tag_parse 93.099174
[libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse] baseline: code 1348/5088 data None functions 3 fuzzy 96.2893
[src/scene/setting/AOSSLink] pool: IDENTICAL
[src/scene/setting/AOSSLink] objdiff: code 668/2196 data 2432/2432 functions 12/14 fuzzy 99.0073 linked code 0
[src/scene/setting/AOSSLink] instruction-exact functions: 12/14
[src/scene/setting/AOSSLink]   section .bss size 2344 match 100.0
[src/scene/setting/AOSSLink]   section .data size 48 match 100.0
[src/scene/setting/AOSSLink]   section .sbss size 40 match 100.0
[src/scene/setting/AOSSLink]   section .text size 2196 match 99.007286
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANGetBSSList 98.48018
[src/scene/setting/AOSSLink]   below 100: AOSSi_WLANConnect 98.70968
[src/scene/setting/AOSSLink] baseline: code 668/2196 data 2432 functions 12 fuzzy 91.1111
[src/keyboard/tiZiString] pool: IDENTICAL
[src/keyboard/tiZiString] objdiff: code 3136/5504 data 7680/7680 functions 26/29 fuzzy 96.4608 linked code 0
[src/keyboard/tiZiString] instruction-exact functions: 26/29
[src/keyboard/tiZiString]   section .bss size 7296 match 100.0
[src/keyboard/tiZiString]   section .data size 328 match 100.0
[src/keyboard/tiZiString]   section .rodata size 56 match 100.0
[src/keyboard/tiZiString]   section .text size 5504 match 96.460754
[src/keyboard/tiZiString]   below 100: clearCandidates__Q39textinput8tistring6WithZiFv 93.28395
[src/keyboard/tiZiString]   below 100: update__Q39textinput8tistring6WithZiFv 91.70852
[src/keyboard/tiZiString]   below 100: setElementBuffer__Q39textinput8tistring6WithZiFv 90.33846
[src/keyboard/tiZiString] baseline: code 3136/5504 data 7680 functions 26 fuzzy 96.3074
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 14812/20872 data 3344/3344 functions 64/66 fuzzy 99.2035 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 63/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.20353
[src/scene/sdChannelMemory/iplSDMemory]   below 100: create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect 99.15884
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 92.7694
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 14812/20872 data 3344 functions 64 fuzzy 98.9810
regressions vs baseline: 0
global matched_code_percent: 89.30427 -> 89.33379
global fuzzy_match_percent: 99.52654 -> 99.53497
global complete_code_percent: 67.07732 -> 67.07732
global matched_data_percent: 99.36508 -> 99.36508
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

XHigh before -> after instruction-exact functions, matched code bytes, matched data bytes:
- libs/RevoEX/src/nwc24/NWC24MsgSubject: instruction-exact 8/12 -> 9/12; code 3352/5352 -> 3896/5352; data 232/232 -> 232/232; fuzzy 99.2638 -> 99.3012.
- libs/RevoEX/src/nwc24/NWC24DateParser: instruction-exact 5/8 -> 6/8; code 1168/2372 -> 1508/2372; data 40/40 -> 40/40; fuzzy 99.2462 -> 99.3642.
- libs/RVLMiddleware/TMC_JPEG/src/exif/exif_parse: instruction-exact 3/6 -> 3/6; code 1348/5088 -> 1348/5088; data None/None -> None/None; fuzzy 96.5016 -> 96.5016.
- src/scene/setting/AOSSLink: instruction-exact 12/14 -> 12/14; code 668/2196 -> 668/2196; data 2432/2432 -> 2432/2432; fuzzy 99.0073 -> 99.0073.
- src/keyboard/tiZiString: instruction-exact 26/29 -> 26/29; code 3136/5504 -> 3136/5504; data 7680/7680 -> 7680/7680; fuzzy 96.4608 -> 96.4608.
- src/scene/sdChannelMemory/iplSDMemory: instruction-exact 63/66 -> 63/66; code 14812/20872 -> 14812/20872; data 3344/3344 -> 3344/3344; fuzzy 99.2035 -> 99.2035.

Remaining15 genuine nonmatching functions, final clean rebuilt exact-name percentages:
- NWC24ReadMsgSubjectPublic: 96.15385%; 100/104; redundant overflow exit branches.
- NWC24ReadMsgTextPublic: 97.14286%; 68/70; redundant overflow exit branches.
- NWC24SetMsgSubjectAndTextPublic: 98.23684%; 190/190; input/context saved register allocation.
- ConvertDateToDays: 96.92921%; 113/113; quotient/add scheduling and temporaries.
- ConvertDaysToDate: 99.70874%; 103/103, frame0x10, all control and operands exact;6 month r12/targetr0 versus leap r0/targetr12 register differences.
- TMCJPEGDEC_exif_parse: 99.43396%; 212/212, frame0x30, all control and operands exact;21 saved data/first-directory/count/extent register differences.
- TMCJPEGDEC_IFD0_tag_parse: 94.46986%; 481/481; switch topology/byte-reader operand order.
- TMCJPEGDEC_IFD1_tag_parse: 93.099174%; 239/242; switch topology/byte-reader operand order.
- AOSSi_WLANGetBSSList: 98.48018%; 227/227; channel-store/argument scheduling and loop/retry registers.
- AOSSi_WLANConnect: 98.70968%; 155/155; two memset argument setup instructions reversed.
- clearCandidates__Q39textinput8tistring6WithZiFv: 93.28395%; 84/81; global candidate base and helper boundaries.
- update__Q39textinput8tistring6WithZiFv: 91.70852%; 447/446; candidate search lifetime and Korean loop structure.
- setElementBuffer__Q39textinput8tistring6WithZiFv: 90.33846%; 65/65; buffer base/load ordering and registers.
- create__Q33ipl5scene8SDMemoryFPQ23EGG4HeapPQ33ipl4nand10LayoutFilePQ33ipl5scene15SDChannelSelect: 99.15884%; 1064/1064;175 pool/System/TextBox and late temporary register differences.
- drawTransferTitles__Q33ipl5scene8SDMemoryFv: 92.7694%; 439/451; newline loop and Color copy boundaries/stack offsets.

XHigh final source-attempt audit: {'ConvertDaysToDate': 58, 'NWC24iDateToOSCalendarTime': 29, 'NWC24iSetMsgSubjectBase64': 18, 'TMCJPEGDEC_exif_parse': 68} compiled distinct source variants; failed compilations excluded. All four selected functions exceed3 valid trials; every other survivor has>=3 logged source attempts from medium round, so none is untried. Last declaration searches: Month ordinary plus288 exhaustive joint orders; Exif ordinary52 plus256 coordinated seeded orders. No source-level impossibility claimed.
Round files changed: libs/RevoEX/src/nwc24/NWC24MsgSubject.c (const encoded input view for readonly MIME use); libs/RevoEX/src/nwc24/NWC24DateParser.c (const year capture used for initial copy and leap test, preserving later input reload); tools/decomp-assist/fz7.attempts.md. Source commits ab4394ab and06f5c37a; final gate/log commit recorded in final report. Other units retain their already committed medium/high changes. No symbols.txt, shared header, configure or data edits. All owned data sections/pools exact, Exif has no data. Final full clean build, DOL hash, regressions0, forbidden0, readability0 pass. New instruction-exact functions2, matched code bytes+884, data unchanged; incomplete units remain.
Known measurement limitation: SD updateState raw source/target function words are identical, objdiff100, but ctxdiff interprets two unsupported paired-single words as offset-sensitive absolute branches; full gate instruction count63 versus objdiff64 reflects this recorded disassembly artifact. No extra code change to hide it. Residual tie-break mechanisms for month/Exif remain uncertain; neither immediate-store/reload volatile nor overlap/data-name correction is supported by target evidence.
