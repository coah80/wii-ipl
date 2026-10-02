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
