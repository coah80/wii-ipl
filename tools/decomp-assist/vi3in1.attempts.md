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
