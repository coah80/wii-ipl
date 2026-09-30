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
