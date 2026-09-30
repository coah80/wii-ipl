# vi3in1 attempts

All 18 functions implemented in object order; first build matched 15 exactly.
String pools identical. Data 1512/1512 bytes in objdiff.

## __VISetMacrovision
1. Indexed 26-byte copy loop, literal command byte after copy: 864/866 instructions, 94.26905%. Missing saved r28; copy pointer and bytes allocated to different registers.
2. Pointer increment loop: same 864/866 instruction diff.
3. Explicit byte assignments: 889/866 instructions, 37.678986%; excessive live byte values increased the stack frame. Rejected.
4. Structured switches and branch-local command arrays: same 864/866 diff. Retained for readability.

## VISetMacrovision
1. Literal byte loads and separate volume update: 68/68 instructions, 7 differences, 99.48529%. Load and intermediate registers differ.
2. Reordered old-byte loads and combined OR expression: 68/68, 22 differences. Rejected.
3. Reordered declarations: 68/68, 10 differences. Rejected.
4. Separate old-byte declaration order and reversed OR operands: 68/68, 24 differences. Rejected. Retained attempt 1.

## __VISetRevolutionModeSimple
1. Indexed ACP copy, original assignment order: 265/267 instructions, 96.82022%; saved constant register and byte-copy allocation differ.
2. Masked WSS operands and command-first caption assignment: 265/267; WSS and caption differences removed. Retained.
3. Explicit ACP byte copies: 266/267, 78.92135%; enlarged frame and save set. Rejected.

# Continuation from eaee2295

## __VISetRevolutionModeSimple
1. Store ACP command before the ascending byte transfer: 97.05618%; src 0x424 base 0x42c insns 265/267
2. Initialize power and clock command arrays at declaration: 94.29588%; src 0x428 base 0x42c insns 266/267
3. Use signed ACP index and store command first: 97.05618%; src 0x424 base 0x42c insns 265/267

## VISetMacrovision
1. Copy old type after volume masking: 99.48529%; src 0x110 base 0x110 insns 68/68
2. Load type before first byte, combine new flag operands: 99.48529%; src 0x110 base 0x110 insns 68/68
3. Express mode dispatch as a structured switch: 99.48529%; src 0x110 base 0x110 insns 68/68
4. Use word-sized intermediates for newType: 94.85294%; src 0x10c base 0x110 insns 67/68
5. Use word-sized intermediates for newType, oldType: 94.85294%; src 0x10c base 0x110 insns 67/68
6. Use word-sized intermediates for newType, oldWd0: 94.85294%; src 0x10c base 0x110 insns 67/68
7. Use word-sized intermediates for oldWd0: 99.48529%; src 0x110 base 0x110 insns 68/68
8. Use word-sized intermediates for newType, oldWd2: 94.85294%; src 0x10c base 0x110 insns 67/68
9. Use word-sized intermediates for oldWd0, mode: 98.60294%; src 0x110 base 0x110 insns 68/68
10. Use word-sized intermediates for oldType, mode: 98.60294%; src 0x110 base 0x110 insns 68/68
11. Load WSS state in oldWd2,oldType,oldWd0 order: 99.411766%; src 0x110 base 0x110 insns 68/68
12. Load WSS state in oldType,oldWd2,oldWd0 order: 99.411766%; src 0x110 base 0x110 insns 68/68
13. Load WSS state in oldWd2,oldWd0,oldType order: 99.411766%; src 0x110 base 0x110 insns 68/68

## __VISetMacrovision
1. Descending remaining-byte count and advancing source/destination: 94.26905%
2. Assign command byte before indexed ACP transfer: 96.77598%
3. Signed copy index and named per-byte value: 94.26905%

All data sections remain 100%; the ACP command-first assignment preserves pool contents and reaches 866/866 instructions, but allocation still differs.
No new instruction-exact functions yet; retained source experiments remain uncommitted pending an exact-function gain.


# Continuation from e81a2616

## VISetMacrovision

1. load type byte before first watchdog byte: 99.48529%; `src 0x110 base 0x110 insns 68/68; diffs 7: [8, 9, 11, 37, 39, 40, 46]`.
2. combine volume mask expression before assigning new watchdog byte: 96.617645%; `src 0x110 base 0x110 insns 68/68; diffs 22: [5, 8, 9, 11, 21, 22, 24, 25, 26, 28, 29, 30, 32, 33, 34, 35, 36, 37, 38, 39]`.
3. word mode temporary and reversed watchdog load order: 98.52941%; `src 0x110 base 0x110 insns 68/68; diffs 9: [8, 9, 10, 11, 37, 38, 39, 40, 46]`.

## __VISetMacrovision

1. inline packet copy with command first: 96.93187%; `src 0xd88 base 0xd88 insns 866/866; diffs 418: [31, 33, 35, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 49, 51, 53, 55, 57, 59, 60]`.
2. inline packet copy with command after payload: 94.26905%; `src 0xd80 base 0xd88 insns 864/866; --- insert mine 8:8 base 8:9`.
3. inline pointer walk command and payload copy: 96.77598%; `src 0xd88 base 0xd88 insns 866/866; diffs 435: [31, 33, 35, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 49, 51, 53, 55, 57, 59, 60]`.

## __VISetRevolutionModeSimple

1. derive ACP block as fixed size byte memcpy before prefix: 77.56929%; `src 0x354 base 0x42c insns 213/267; --- replace mine 8:9 base 8:12`.
2. retain shared enable value across power clock and filter transfers: 97.05618%; `src 0x424 base 0x42c insns 265/267; --- delete mine 9:10 base 9:9`.
3. typed ACP payload view before control transactions: build rejected (#   Error:                    ^^^^^^^^^^).
4. ACP payload pointer initialized after packet declarations: 97.05618%; `src 0x424 base 0x42c insns 265/267; --- delete mine 9:10 base 9:9`.

Target blocks were re-derived from vi3in1.s: each ACP packet has the command byte and 26 ascending byte copies, three unrolled groups of eight and two tail bytes. The simple-mode routine preserves power/clock enable across transfers before zeroing later command fields. The inline copy retains 866 instructions and reduces register differences from 435 to 418; other matched functions and data remain unchanged. Three public-mode variations and four simple-mode variations were evaluated.
All extracted data sections remain exact. There are no ASCII pools or missing tables to insert.

## Additional packet-copy derivation attempts

1. command prefix before constant size memcpy: 13.75866%; source and objdiff evidence sol-low-r3-vi-macro-copy-1.source/.json in /tmp.
2. constant size memcpy before command prefix: 19.581985%; source and objdiff evidence sol-low-r3-vi-macro-copy-2.source/.json in /tmp.
3. initialize packet prefix then copy payload: 27.85104%; source and objdiff evidence sol-low-r3-vi-macro-copy-3.source/.json in /tmp.
1. explicit eight byte groups with prefix before payload: 96.77598%; source and objdiff evidence sol-low-r3-vi-block-loop-1.source/.json in /tmp.
2. explicit eight byte groups with prefix after payload: 94.26905%; source and objdiff evidence sol-low-r3-vi-block-loop-2.source/.json in /tmp.
3. indexed pointer dereference byte loop: 96.77598%; source and objdiff evidence sol-low-r3-vi-block-loop-3.source/.json in /tmp.
