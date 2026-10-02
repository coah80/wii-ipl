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
