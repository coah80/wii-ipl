# NWC24MsgSubject matching attempts

Baseline: no source, 0/12 functions, 0/5352 code bytes, 0/232 data bytes.
All twelve functions are implemented in object order. The initial readable C
reference from /tmp was checked against target assembly and Ghidra output.
Charset strings and pointer tables retain source order; .data and .sdata
match 100%, with an identical pool.

## Source-level experiments

NWC24ReadMsgSubjectPublic | switch write overflow status | (92.11539, -10) | src 0x1a0 base 0x1a0 insns 104/104
NWC24ReadMsgSubjectPublic | signed subject whitespace index | (96.15385, -9999) | src 0x190 base 0x1a0 insns 100/104
NWC24ReadMsgSubjectPublic | late original-size read | (96.15385, -9999) | src 0x190 base 0x1a0 insns 100/104
NWC24ReadMsgTextPublic | switch read overflow status | (94.14286, -5) | src 0x118 base 0x118 insns 70/70
NWC24ReadMsgTextPublic | truncation flag after size temporaries | (96.71429, -9999) | src 0x110 base 0x118 insns 68/70
NWC24ReadMsgTextPublic | explicit error status declaration first | (97.14286, -9999) | src 0x110 base 0x118 insns 68/70
NWC24SetMsgSubjectPublic | regional encoding switch | (94.59649, -9999) | src 0x1b0 base 0x1c8 insns 108/114
NWC24SetMsgSubjectPublic | charset initialized before detection | (87.89474, -9999) | src 0x1bc base 0x1c8 insns 111/114
NWC24SetMsgSubjectPublic | private message view used directly | (95.74561, -9999) | src 0x1b8 base 0x1c8 insns 110/114
NWC24SetMsgSubjectAndTextPublic | regional subject encoding switch | (0, -9999) | [1/1] MWCC build/43U/src/libs/RevoEX/src/nwc24/NWC24MsgSubject.o
NWC24SetMsgSubjectAndTextPublic | unsigned intermediate text size | (0, -9999) | [1/1] MWCC build/43U/src/libs/RevoEX/src/nwc24/NWC24MsgSubject.o
NWC24SetMsgSubjectAndTextPublic | initialize charset before charset parser | (86.23158, -9999) | src 0x2d0 base 0x2f8 insns 180/190
NWC24ReadMsgSubjectPublic | switch only exceptional statuses | (94.03846, -9999) | src 0x198 base 0x1a0 insns 102/104
NWC24ReadMsgTextPublic | switch only exceptional statuses | (95.57143, -9999) | src 0x114 base 0x118 insns 69/70
NWC24SetMsgSubjectAndTextPublic | regional subject switch at final choice | (91.405266, -9999) | src 0x2e8 base 0x2f8 insns 186/190
NWC24SetMsgSubjectAndTextPublic | defer subject workspace pointer calculation | (86.6579, -9999) | src 0x2c4 base 0x2f8 insns 177/190
NWC24SetMsgSubjectAndTextPublic | reorder text source/work count declarations | (90.052635, -9999) | src 0x2cc base 0x2f8 insns 179/190
NWC24iDetectEncodingToSend | continue when text charset advances subject charset | (72.376144, -9999) | src 0x18c base 0x1b4 insns 99/109
NWC24iDetectEncodingToSend | signed charset region switch | (58.19266, -9999) | src 0x154 base 0x1b4 insns 85/109
NWC24iDetectEncodingToSend | result index before loop bound check | (65.39449, -9999) | src 0x164 base 0x1b4 insns 89/109
NWC24iDetectBreakPoint | signed scan counter | (77.75676, -53) | src 0x128 base 0x128 insns 74/74
NWC24iDetectBreakPoint | direct size fit return | (77.554054, -53) | src 0x128 base 0x128 insns 74/74
NWC24iDetectBreakPoint | cache leading byte for scan | (73.432434, -9999) | src 0x120 base 0x128 insns 72/74
NWC24iSetMsgSubjectPlain | signed folding scan index | (88.424, -9999) | src 0x1e8 base 0x1f4 insns 122/125
NWC24iSetMsgSubjectPlain | moving newline normalization cursor | (87.904, -9999) | src 0x1e8 base 0x1f4 insns 122/125
NWC24iSetMsgSubjectPlain | defer folded buffer pointer calculation | (81.744, -9999) | src 0x1e8 base 0x1f4 insns 122/125
NWC24iSetMsgSubjectQP | signed folding scan index | (76.75, -9999) | src 0x258 base 0x240 insns 150/144
NWC24iSetMsgSubjectQP | moving newline normalization cursor | (76.298615, -9999) | src 0x258 base 0x240 insns 150/144
NWC24iSetMsgSubjectQP | defer folded buffer pointer calculation | (71.02778, -9999) | src 0x258 base 0x240 insns 150/144
NWC24iSetMsgSubjectBase64 | signed folding scan index | (70.0, -9999) | src 0x230 base 0x220 insns 140/136
NWC24iSetMsgSubjectBase64 | moving newline normalization cursor | (70.0, -9999) | src 0x230 base 0x220 insns 140/136
NWC24iSetMsgSubjectBase64 | defer folded buffer pointer calculation | (70.0, -9999) | src 0x230 base 0x220 insns 140/136
NWC24ReadMsgSubjectPublic | success/default status switch | (96.15385, -9999) | src 0x190 base 0x1a0 insns 100/104
NWC24ReadMsgTextPublic | success/default status switch | (97.14286, -9999) | src 0x110 base 0x118 insns 68/70
NWC24SetMsgSubjectPublic | individual regional switch cases | (97.149124, -9999) | src 0x1d4 base 0x1c8 insns 117/114
NWC24iSetMsgSubjectPlain | begin folding after first line and reuse capacity slot | (90.496, -96) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | conversion status switch | (89.304, -9999) | src 0x1ec base 0x1f4 insns 123/125
NWC24iSetMsgSubjectPlain | folded capacity comparison direction | (88.384, -9999) | src 0x1e8 base 0x1f4 insns 122/125
NWC24iSetMsgSubjectQP | unsigned charset-size arithmetic | (78.13194, -9999) | src 0x250 base 0x240 insns 148/144
NWC24iSetMsgSubjectQP | separate running and per-word output counts | (86.270836, -9999) | src 0x230 base 0x240 insns 140/144
NWC24iSetMsgSubjectQP | conversion status switch | (77.513885, -9999) | src 0x25c base 0x240 insns 151/144
NWC24iSetMsgSubjectBase64 | signed line size and unsigned charset length | (71.43382, -9999) | src 0x230 base 0x220 insns 140/136
NWC24iSetMsgSubjectBase64 | separate total and encoded word sizes | (79.70588, -9999) | src 0x208 base 0x220 insns 130/136
NWC24iSetMsgSubjectBase64 | folded output capacity cached in input capacity | (70.0, -9999) | src 0x230 base 0x220 insns 140/136
NWC24iDetectBreakPoint | supported charset branch and early breakpoint returns | (98.64865, -8) | src 0x128 base 0x128 insns 74/74
NWC24ReadMsgSubjectPublic | break from overflowing switch case | (96.15385, -9999) | src 0x190 base 0x1a0 insns 100/104
NWC24ReadMsgTextPublic | break from overflowing switch case | (97.14286, -9999) | src 0x110 base 0x118 insns 68/70
NWC24iDetectBreakPoint | pointer declared before byte-encoding flag | (100.0, 0) | src 0x128 base 0x128 insns 74/74
NWC24SetMsgSubjectPublic | merge Korean and Chinese base64 cases | (100.0, 0) | src 0x1c8 base 0x1c8 insns 114/114
NWC24SetMsgSubjectAndTextPublic | merge second base64 regional cases | (93.947365, -9999) | src 0x2dc base 0x2f8 insns 183/190
NWC24SetMsgSubjectAndTextPublic | regional text encoding switch | (94.789474, -125) | src 0x2f8 base 0x2f8 insns 190/190
NWC24SetMsgSubjectAndTextPublic | test external conversion status before seven-bit flag | (90.378944, -9999) | src 0x2e8 base 0x2f8 insns 186/190
NWC24SetMsgSubjectAndTextPublic | work pointer before message view | (94.789474, -125) | src 0x2f8 base 0x2f8 insns 190/190
NWC24SetMsgSubjectAndTextPublic | detection status switch | (95.36842, -9999) | src 0x2fc base 0x2f8 insns 191/190
NWC24SetMsgSubjectAndTextPublic | work pointer declared after size variables | (94.789474, -125) | src 0x2f8 base 0x2f8 insns 190/190

## Retained corrections

Grouped Korean/Chinese base64 cases match NWC24SetMsgSubjectPublic.
Breakpoint detection uses the supported-charset branch, separate UTF-8 scan,
early returns, and unsigned masked-byte comparison; it matches exactly.
Both internal-encoding conversion functions and the default charset selector
also match exactly. Plain subject folding starts after the initial line.
Charset detection repeats while the text charset advances the subject charset.
QP/base64 folding uses distinct running and per-word lengths; the short
single-word branch uses its initialized word length. Unsigned charset-length
arithmetic reproduces the target division. Removing unused base64 temporaries
and fixing those single-word branches gives QP 88.4375% and base64 81.94853%.
The detection-status switch gives SubjectAndText 95.36842%.

NWC24_MSG_SUBJECT is defined only by this source. Its header gate supplies the
five-argument, writable-name NWC24ReadMsgTextEx declaration seen in the target
callee, which overwrites r8 on entry. Every other translation unit keeps the
existing declaration. The gate reports zero regressions.

Several temporary variants failed compilation and were discarded. Unchanged
source variants in the raw log are not counted as distinct attempts. Every
remaining function has at least three actual source edits recorded.

## Remaining functions

NWC24ReadMsgSubjectPublic 96.15385%: 104 target instructions versus 100; overflow-handling branch structure
NWC24ReadMsgTextPublic 97.14286%: 70 target instructions versus 68; overflow-handling branch structure
NWC24SetMsgSubjectAndTextPublic 95.36842%: regional dispatch, detection-status flow and register allocation
NWC24iDetectEncodingToSend 72.376144%: charset scan state and search-loop scheduling/allocation
NWC24iSetMsgSubjectPlain 90.496%: folded-line control flow and allocation
NWC24iSetMsgSubjectQP 88.4375%: word-size accounting, folding control flow and allocation
NWC24iSetMsgSubjectBase64 81.94853%: conversion/encoding status flow and folding allocation

Retained: 5/12 exact functions; 1840/5352 code bytes; 232/232 data bytes.

## Continuation 2026-09-30

Baseline: 5/12 exact functions; 1840/5352 code bytes; 232/232 data bytes.

NWC24ReadMsgTextPublic | inline status-acceptance helper | (97.14286, -9999) | src 0x110 base 0x118 insns 68/70
NWC24ReadMsgTextPublic | successful reader branch before exceptional branch | (97.14286, -9999) | src 0x110 base 0x118 insns 68/70
NWC24ReadMsgTextPublic | subject conversion status separate from reader status | (97.14286, -9999) | src 0x110 base 0x118 insns 68/70
NWC24ReadMsgSubjectPublic | inline status-acceptance helper | (96.15385, -9999) | src 0x190 base 0x1a0 insns 100/104
NWC24ReadMsgSubjectPublic | walk subject through separate character pointer | (95.94231, -9999) | src 0x190 base 0x1a0 insns 100/104
NWC24ReadMsgSubjectPublic | signed decoded capacity temporary | (96.15385, -9999) | src 0x190 base 0x1a0 insns 100/104
NWC24SetMsgSubjectAndTextPublic | status switches | (96.52631, -9999) | src 0x304 base 0x2f8 insns 193/190
NWC24SetMsgSubjectAndTextPublic | grouped regional cases | (97.07895, -9999) | src 0x2f0 base 0x2f8 insns 188/190
NWC24SetMsgSubjectAndTextPublic | switches and grouped regional cases | (98.23684, -65) | src 0x2f8 base 0x2f8 insns 190/190
NWC24SetMsgSubjectAndTextPublic | work pointer declared before message alias | (98.23684, -65) | src 0x2f8 base 0x2f8 insns 190/190
NWC24SetMsgSubjectAndTextPublic | late work pointer initialization | (0, -9999) | [1/1] MWCC build/43U/src/libs/RevoEX/src/nwc24/NWC24MsgSubject.o
NWC24SetMsgSubjectAndTextPublic | derive subject buffer after text conversion | (98.23684, -65) | src 0x2f8 base 0x2f8 insns 190/190
NWC24SetMsgSubjectAndTextPublic | retain charset pointer instead of work object | (98.23684, -65) | src 0x2f8 base 0x2f8 insns 190/190
NWC24SetMsgSubjectAndTextPublic | declare input buffer partitions before work pointer | (98.23684, -65) | src 0x2f8 base 0x2f8 insns 190/190
NWC24SetMsgSubjectAndTextPublic | assign work pointer inside detection argument | (98.23684, -65) | src 0x2f8 base 0x2f8 insns 190/190
NWC24iSetMsgSubjectPlain | conversion status switch | (0, -9999) | [1/1] MWCC build/43U/src/libs/RevoEX/src/nwc24/NWC24MsgSubject.o
NWC24iSetMsgSubjectPlain | prepare fold capacity before fit test | (92.096, -96) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | capture consumed first line before copy | (91.296, -9999) | src 0x1f0 base 0x1f4 insns 124/125
NWC24iSetMsgSubjectQP | signed encoded word length | (88.4375, -9999) | src 0x22c base 0x240 insns 139/144
NWC24iSetMsgSubjectQP | capture fold capacity before charset length | (88.4375, -9999) | src 0x22c base 0x240 insns 139/144
NWC24iSetMsgSubjectQP | normalize via moving source pointer | (87.986115, -9999) | src 0x22c base 0x240 insns 139/144
NWC24iSetMsgSubjectBase64 | signed encoded word length | (81.94853, -9999) | src 0x20c base 0x220 insns 131/136
NWC24iSetMsgSubjectBase64 | multiply line length before shifting | (81.42647, -9999) | src 0x20c base 0x220 insns 131/136
NWC24iSetMsgSubjectBase64 | capture remaining input after fold capacity check | (79.94118, -9999) | src 0x20c base 0x220 insns 131/136
NWC24iDetectEncodingToSend | text status stored in search convergence index | (72.23853, -9999) | src 0x18c base 0x1b4 insns 99/109
NWC24iDetectEncodingToSend | encoding checks use status switches | (72.376144, -9999) | src 0x18c base 0x1b4 insns 99/109
NWC24iDetectEncodingToSend | region table selected with switch | (82.55963, -9999) | src 0x198 base 0x1b4 insns 102/109
NWC24iDetectEncodingToSend | store selected index at each search exit | (96.04587, -46) | src 0x1b4 base 0x1b4 insns 109/109
NWC24iDetectEncodingToSend | exit index plus cached byte sizes | (93.99083, -47) | src 0x1b4 base 0x1b4 insns 109/109
NWC24iSetMsgSubjectPlain | explicit fold overflow first and postincrement writes | (99.144, -20) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | postincrement writes with initial source cursor | (94.944, -9999) | src 0x1f0 base 0x1f4 insns 124/125
NWC24iDetectEncodingToSend | initialize search start before region dispatch | (96.60551, -32) | src 0x1b4 base 0x1b4 insns 109/109
NWC24iDetectEncodingToSend | byte count locals after region selection | (96.27523, -47) | src 0x1b4 base 0x1b4 insns 109/109
NWC24iDetectEncodingToSend | order table count and search locals by lifetime | (96.04587, -46) | src 0x1b4 base 0x1b4 insns 109/109
NWC24iSetMsgSubjectPlain | source offset declared before second buffer | (99.904, -2) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | line length initialized before buffer capacity | (99.0, -23) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | fold pointer declared after counters | (99.904, -2) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | zero break length before source size initialization | (99.904, -2) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | zero break length before partition pointer initialization | (99.904, -2) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | initialize source and break sizes before work capacity | (99.76, -6) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iDetectEncodingToSend | cache byte lengths before end index | (98.073395, -34) | src 0x1b4 base 0x1b4 insns 109/109
NWC24iDetectEncodingToSend | byte lengths and table local order | (98.073395, -34) | src 0x1b4 base 0x1b4 insns 109/109
NWC24iDetectEncodingToSend | search start variable declared after previous index | (96.60551, -32) | src 0x1b4 base 0x1b4 insns 109/109
NWC24iSetMsgSubjectPlain | break length initialized at declaration | (99.76, -6) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | break length declared first | (99.768, -20) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | input length declared after break length | (99.808, -14) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectPlain | work capacity initialized at declaration | (99.904, -2) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iDetectEncodingToSend | locals ordered by independent search roles | (100.0, 0) | src 0x1b4 base 0x1b4 insns 109/109
NWC24iSetMsgSubjectPlain | partition capacity computed after break initialization | (100.0, 0) | src 0x1f4 base 0x1f4 insns 125/125
NWC24iSetMsgSubjectQP | running output count excludes terminator and cached fold limit | (96.30556, -28) | src 0x240 base 0x240 insns 144/144
NWC24iSetMsgSubjectQP | source cursor lifetime and partition initialization | (99.34028, -16) | src 0x240 base 0x240 insns 144/144
NWC24iSetMsgSubjectQP | fold limit before source offset declaration | (99.34028, -16) | src 0x240 base 0x240 insns 144/144
NWC24iSetMsgSubjectQP | source cursor declared before capacity variable | (99.34028, -16) | src 0x240 base 0x240 insns 144/144
NWC24iSetMsgSubjectQP | running output computed through temporary before cursor advance | (99.548615, -12) | src 0x240 base 0x240 insns 144/144
NWC24iSetMsgSubjectQP | fold limit replaces exhausted partition capacity | (99.548615, -12) | src 0x240 base 0x240 insns 144/144
NWC24iSetMsgSubjectQP | source offset declared after output word size | (99.270836, -20) | src 0x240 base 0x240 insns 144/144
NWC24iSetMsgSubjectQP | capacity declared after folded buffer | (99.548615, -12) | src 0x240 base 0x240 insns 144/144

Retained continuation: encoding detection stores each selected charset index
at its actual search exit and caches input byte lengths. Plain folding uses
the explicit overflow branch and increments its output cursor for CR/LF.
Both functions are instruction-exact. SubjectAndText has matching control
flow but different saved-register allocation. QP caches its fold limit and
tracks the output length without the terminator; 144/144 instructions remain,
with twelve differences from the capacity/source-cursor register exchange.
All prior exact functions and all charset tables and strings are preserved.

## Remaining functions

NWC24iSetMsgSubjectQP, 99.548615%: 144/144 instructions; twelve register differences from capacity/source-offset allocation.
NWC24SetMsgSubjectAndTextPublic, 98.23684%: 190/190 instructions; 65 saved-register differences.
NWC24ReadMsgTextPublic, 97.14286%: 68/70 instructions; overflow-status branch lowering omits two target branches.
NWC24ReadMsgSubjectPublic, 96.15385%: 100/104 instructions; two overflow-status blocks each omit two target branches.
NWC24iSetMsgSubjectBase64, 81.94853%: 131/136 instructions; conversion-status branches and folded-output accumulation differ.
