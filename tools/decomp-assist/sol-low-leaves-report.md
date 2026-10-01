# Leaf matching result

Source commits: c012e880, 78a83518.

Full final gate: sol-low-leaves-final-gate.txt, explicitly selecting --base 8e43db05.
The current HEAD f4fd16f8 baseline file is absent. 8e43db05 is the nearest ancestor with an existing baseline; the starting HEAD report was independently saved as /tmp/sol-low-start.json. No baseline or gate tool was modified.

Before -> after:
- KPAD instruction-exact 18/29 -> 19/29; objdiff functions 18/29 -> 19/29; code 5188/13056 -> 5916/13056; data 7912/8032 -> 7912/8032.
- kbd_lib gate instruction-exact 13/21 -> 14/21; objdiff functions 14/21 -> 15/21; code 2432/5764 -> 3088/5764; data 5296/5296 -> 5296/5296.
- exif_parse instruction-exact 3/6 -> 3/6; code 1348/5088 -> 1348/5088; data 0/0 -> 0/0.

KBDResetChannel remains objdiff 100% and its actual instructions are identical. The gate undercounts it because odiff.dis normalizes the CR operand rather than the branch destination for two cr1 branches. This pre-existing gate-tool issue is recorded without editing the tools.

KPAD .sdata2 first divergence is the real 0.383864f constant: target offset 0x0c, source offset 0x60. Extracting the interval update into a meaningful inline helper did not change emission order and was restored. No dummy constant or forced placement was introduced.

## Remaining functions

- reset_kpad: 99.48718%; 117/117 instructions; 10 floating-register differences around reference distance and ratio temporaries.
- KPADGetProjectionPos: 96.57895%; 19/19 instructions; 9 floating-register and multiplication-operand differences.
- KPADSetSensorHeight: 99.23077%; 52/52 instructions; 7 base-pointer and square-result register differences.
- calc_acc_horizon: 97.27723%; 101/101 instructions; floating-register allocation and scheduling differ.
- read_kpad_acc: 98.15%; 400/400 instructions; smoothing helper expansion and floating-register allocation differ.
- select_1obj_first: 98.348625%; 109/109 instructions; end-pointer and floating temporary register allocation differ.
- select_1obj_continue: 98.49462%; 93/93 instructions; direction and offset temporaries use different registers and operand order.
- calc_dpd_variable: 94.82%; 250/250 instructions; distance magnitude and projected-coordinate temporaries differ.
- KPADRead: 97.52723%; 459/459 instructions; copy/gravity stack locals and inline expansion register scheduling differ.
- KPADInit: 96.51351%; 185/185 instructions; callee-saved integer and floating allocation, scheduling, and constant encounter order differ.
- kbdEventHandler: 99.83871%; 186/186 instructions; 5 report-byte and channel-base scratch-register differences.
- kbdProcMod: 99.90234%; 256/256 instructions; 4 pointer/value register differences in inlined modifier-state update.
- kbd_led_handler: 61.12%; 23/25 instructions; callback null-test/release ordering and scratch register allocation differ.
- KBDSetLedsAsync: 86.234566%; 80/81 instructions; channel offset rematerialization, signed loop index, and command addressing differ.
- KBDSetLeds: 84.6076%; 75/79 instructions; pointer induction versus target indexed command loop and channel offset rematerialization differ.
- KBDSetModState: 99.40476%; 42/42 instructions; 4 pointer/value register differences at physical-modifier insertion.
- TMCJPEGDEC_exif_parse: 98.679245%; 212/212 instructions; byte-reader temporaries and callee-saved parser cursor/count registers differ.
- TMCJPEGDEC_IFD0_tag_parse: 94.241165%; 481/481 instructions; decoded tag/type temporaries and switch default branch structure differ.
- TMCJPEGDEC_IFD1_tag_parse: 93.099174%; 239/242 instructions; switch decision tree/default-return structure and byte-reader temporary allocation differ.

Every remaining function has at least three distinct source-level trials logged in sol-low-leaves-attempts.md. Unsuccessful experiments were restored. Declaration-search tool outputs and target/source ctxdiff diagnosis are recorded or referenced there.

Changed files:
- libs/RVL_SDK/src/kpad/KPAD.c
- libs/RVL_SDK/src/kbd/kbd_lib.c
- tools/decomp-assist/sol-low-leaves-attempts.md
- tools/decomp-assist/sol-low-leaves-final-gate.txt
- tools/decomp-assist/sol-low-leaves-report.md

No source change to exif_parse; no linking/configuration/header change.
