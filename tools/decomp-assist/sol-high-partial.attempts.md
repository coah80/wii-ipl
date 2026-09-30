libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declare interrupt state before loop index; (99.583336, 7, 96, 96, 11, '1324', '32') -> (99.270836, 12, 96, 96, 11, '1324', '32')
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declare channel copy before kpad; (99.583336, 7, 96, 96, 11, '1324', '32') -> (99.583336, 7, 96, 96, 11, '1324', '32')
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: scope loop index at for; (99.583336, 7, 96, 96, 11, '1324', '32') -> BUILD FAIL .c -o build/43U/src/libs/RVL_SDK/src/kpad && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\kpad\KPAD.c
# -------------------------------------
#     197:     for (u32 i = 0; i < 16; i++) {
#   Error:          ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: reuse normalizedX for vertical blend; (99.72603, 3, 73, 73, 11, '1324', '32') -> (99.65753, 5, 73, 73, 11, '1324', '32')
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: reuse accelZ for vertical blend; (99.72603, 3, 73, 73, 11, '1324', '32') -> (99.65753, 5, 73, 73, 11, '1324', '32')
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: declare vertical blend before horizontal; (99.72603, 3, 73, 73, 11, '1324', '32') -> (99.65753, 5, 73, 73, 11, '1324', '32')
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: multiply height then coefficient on left; (96.57895, 9, 19, 19, 11, '1324', '32') -> (95.52631, 10, 19, 19, 11, '1324', '32')
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: height operand before half coefficient; (96.57895, 9, 19, 19, 11, '1324', '32') -> (96.052635, 9, 19, 19, 11, '1324', '32')
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: compute scaled before floats; (96.57895, 9, 19, 19, 11, '1324', '32') -> (95.0, 13, 19, 19, 11, '1324', '32')
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: reuse horizontal magnitude after its final read; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.10959, 11, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: reuse blend after its final read; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.65753, 5, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: compute vertical before horizontal interpolation; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.15069, 10, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: keep double expression in output and left scale coefficient; (96.57895, 9, 19, 19, 11, 1324, 32) -> (96.31579, 10, 19, 19, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: reuse height for halfHeight with left coefficient; (96.57895, 9, 19, 19, 11, 1324, 32) -> BUILD FAIL c/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\kpad\KPAD.c
# -------------------------------------
#    1248:     f32 x = src->x * height;
#   Error:     ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: declare scaled after output floats with left coefficient; (96.57895, 9, 19, 19, 11, 1324, 32) -> (95.52631, 11, 19, 19, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: use signed sample loop index; (99.583336, 7, 96, 96, 11, 1324, 32) -> (99.010414, 7, 96, 96, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declare loop index after latest; (99.583336, 7, 96, 96, 11, 1324, 32) -> (98.958336, 17, 96, 96, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declare loop index after type; (99.583336, 7, 96, 96, 11, 1324, 32) -> (98.697914, 21, 96, 96, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: scope interrupt state and loop within process; (99.583336, 7, 96, 96, 11, 1324, 32) -> (99.322914, 12, 96, 96, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_button_repeat: load current before threshold and narrow next only in wrap; (95.50495, 16, 101, 101, 11, 1324, 32) -> (99.653465, 6, 101, 101, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_button_repeat: reload updated threshold inside wrap; (95.50495, 16, 101, 101, 11, 1324, 32) -> (99.653465, 6, 101, 101, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_button_repeat: load current first and scope narrowing within wrap; (95.50495, 16, 101, 101, 11, 1324, 32) -> (95.39604, 17, 101, 101, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 0; (99.72603, 3, 73, 73, 11, 1324, 32) -> (97.945206, 21, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 1; (99.72603, 3, 73, 73, 11, 1324, 32) -> (100.0, 0, 73, 73, 12, 1616, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 2; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.246574, 9, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 3; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.08219, 20, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 4; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.630135, 15, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 5; (99.72603, 3, 73, 73, 11, 1324, 32) -> (100.0, 0, 73, 73, 12, 1616, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 6; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.21918, 18, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 7; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.35616, 17, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 8; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.9726, 11, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 9; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.65753, 5, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 10; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.42466, 15, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 11; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.38356, 8, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 12; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.65753, 5, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 13; (99.72603, 3, 73, 73, 11, 1324, 32) -> (100.0, 0, 73, 73, 12, 1616, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 14; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.38356, 7, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 15; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.42466, 15, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 16; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.35616, 18, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 17; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.38356, 8, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 18; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.630135, 15, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 19; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.45206, 6, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 20; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.630135, 15, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 21; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.9726, 11, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 22; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.65753, 5, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 23; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.9726, 12, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 24; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.9726, 12, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 25; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.15069, 18, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 26; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.21918, 18, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 27; (99.72603, 3, 73, 73, 11, 1324, 32) -> (100.0, 0, 73, 73, 12, 1616, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 28; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.246574, 9, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 29; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.38356, 7, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 30; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.45206, 6, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 31; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.42466, 15, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 32; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.35616, 17, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 33; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.630135, 15, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 34; (99.72603, 3, 73, 73, 11, 1324, 32) -> (99.45206, 6, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_vertical: local declaration order 35; (99.72603, 3, 73, 73, 11, 1324, 32) -> (98.08219, 20, 73, 73, 11, 1324, 32)
libs/RVL_SDK/src/kpad/KPAD calc_button_repeat: independent extension temporaries; (99.653465, 6, 101, 101, 12, 1616, 32) -> BUILD FAIL DK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\kpad\KPAD.c
# -------------------------------------
#     301:     u16 extensionCount;
#   Error:     ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RVL_SDK/src/kpad/KPAD calc_button_repeat: independent extension temporaries reversed; (99.653465, 6, 101, 101, 12, 1616, 32) -> BUILD FAIL SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\kpad\KPAD.c
# -------------------------------------
#     301:     u32 extensionNext;
#   Error:     ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RVL_SDK/src/kpad/KPAD calc_button_repeat: separate extension scope temporaries; (99.653465, 6, 101, 101, 12, 1616, 32) -> (100.0, 0, 101, 101, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: ['scaled', 'height', 'halfHeight', 'x', 'y']; (96.57895, 9, 19, 19, 13, 2020, 32) -> (95.52631, 10, 19, 19, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: ['height', 'halfHeight', 'x', 'y', 'scaled']; (96.57895, 9, 19, 19, 13, 2020, 32) -> (95.52631, 11, 19, 19, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: ['height', 'halfHeight', 'scaled', 'x', 'y']; (96.57895, 9, 19, 19, 13, 2020, 32) -> (95.52631, 11, 19, 19, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: ['height', 'scaled', 'halfHeight', 'x', 'y']; (96.57895, 9, 19, 19, 13, 2020, 32) -> (95.52631, 11, 19, 19, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: ['scaled', 'x', 'y', 'height', 'halfHeight']; (96.57895, 9, 19, 19, 13, 2020, 32) -> (95.52631, 10, 19, 19, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_horizon: restore inclusive radius test from fcmpo/cror; (93.069305, 87, 99, 101, 13, 2020, 32) -> (95.89109, 87, 100, 101, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_horizon: inclusive radius and reuse targetX for nextY; (93.069305, 87, 99, 101, 13, 2020, 32) -> (95.49505, 87, 100, 101, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_horizon: inclusive radius and normalization uses old accelerations; (93.069305, 87, 99, 101, 13, 2020, 32) -> (93.26733, 87, 98, 101, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_acc: restore inclusive smoothing thresholds from cror; (58.565, 396, 378, 400, 13, 2020, 32) -> (58.3425, 396, 384, 400, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_acc: thresholds and preserve previous vectors as struct copies; (58.565, 396, 378, 400, 13, 2020, 32) -> (63.5625, 386, 396, 400, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_acc: thresholds and name raw acceleration axes; (58.565, 396, 378, 400, 13, 2020, 32) -> (58.3425, 396, 384, 400, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_first: restore inclusive near/far rejection tests; (65.86885, 110, 125, 122, 13, 2020, 32) -> (69.41803, 110, 127, 122, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_first: near/far tests and ordinary candidate copies; (65.86885, 110, 125, 122, 13, 2020, 32) -> (72.86066, 110, 127, 122, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_first: near/far tests and distance operand order; (65.86885, 110, 125, 122, 13, 2020, 32) -> (69.459015, 110, 127, 122, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_continue: restore bound tests and two-point score ceiling from assembly; (73.04348, 96, 138, 138, 13, 2020, 32) -> (79.615944, 112, 140, 138, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_continue: bounds and reuse distance for distance score; (73.04348, 96, 138, 138, 13, 2020, 32) -> (79.50725, 112, 140, 138, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_continue: bounds and explicit reverse branch; (73.04348, 96, 138, 138, 13, 2020, 32) -> (83.37681, 124, 141, 138, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_first: restore inclusive outside-frame branches and first candidate copy; (54.51376, 109, 85, 109, 13, 2020, 32) -> (70.220184, 109, 93, 109, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_first: outside-frame bounds and candidate struct copy; (54.51376, 109, 85, 109, 13, 2020, 32) -> (70.09174, 109, 93, 109, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_first: outside-frame bounds and offset operand order; (54.51376, 109, 85, 109, 13, 2020, 32) -> (70.220184, 109, 93, 109, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_dpd_variable: restore inclusive smoothing thresholds; (68.608, 241, 228, 250, 13, 2020, 32) -> (71.404, 241, 231, 250, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_dpd_variable: thresholds and reverse midpoint operand order; (68.608, 241, 228, 250, 13, 2020, 32) -> (71.404, 241, 231, 250, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_dpd_variable: thresholds and separate distance interpolation product; (68.608, 241, 228, 250, 13, 2020, 32) -> (71.384, 241, 231, 250, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_dpd: restore inclusive frame/acceleration rejection tests; (69.09712, 271, 276, 278, 13, 2020, 32) -> (72.39209, 271, 281, 278, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_dpd: bounds and direction scaling order; (69.09712, 271, 276, 278, 13, 2020, 32) -> (72.35612, 271, 281, 278, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_dpd: bounds and reference distance operand order; (69.09712, 271, 276, 278, 13, 2020, 32) -> (72.3741, 271, 281, 278, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD reset_kpad: restore post-store decrement loops from assembly; (65.17094, 101, 115, 117, 13, 2020, 32) -> (0, 264, 264, 117, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD reset_kpad: loops and copy direction as bit-preserving words; (65.17094, 101, 115, 117, 13, 2020, 32) -> (0, 266, 268, 117, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD reset_kpad: loops and separate object/candidate iterator; (65.17094, 101, 115, 117, 13, 2020, 32) -> (0, 264, 264, 117, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_stick: restore if/else device dispatch and signed right stick; (84.26582, 135, 157, 158, 13, 2020, 32) -> (88.73418, 109, 153, 158, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_stick: dispatch and signed trigger arithmetic; (84.26582, 135, 157, 158, 13, 2020, 32) -> (95.3481, 108, 157, 158, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_stick: dispatch and select clamp with explicit else; (84.26582, 135, 157, 158, 13, 2020, 32) -> (88.73418, 109, 153, 158, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_continue: ordinary matched candidate struct copy; (78.30108, 92, 95, 93, 13, 2020, 32) -> (79.80645, 92, 95, 93, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_continue: declare float products before directions; (78.30108, 92, 95, 93, 13, 2020, 32) -> (78.462364, 92, 95, 93, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_continue: multiply offset by direction first; (78.30108, 92, 95, 93, 13, 2020, 32) -> (78.354836, 92, 95, 93, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: restore unordered min branch direction; (93.55769, 21, 52, 52, 13, 2020, 32) -> (91.63461, 32, 53, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: declaration order one; (93.55769, 21, 52, 52, 13, 2020, 32) -> (92.78846, 23, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: declaration order two; (93.55769, 21, 52, 52, 13, 2020, 32) -> (92.78846, 23, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADRead: restore reachable unplugged callback condition; (82.53377, 452, 472, 459, 13, 2020, 32) -> (82.40305, 453, 472, 459, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADRead: use BOOL interrupt state; (82.53377, 452, 472, 459, 13, 2020, 32) -> (83.10022, 459, 470, 459, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADRead: declaration order one; (82.53377, 452, 472, 459, 13, 2020, 32) -> (82.50109, 452, 472, 459, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADInit: reuse reference extents after diagonal calculation; (71.85946, 198, 201, 185, 13, 2020, 32) -> (71.72433, 198, 201, 185, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADInit: scope diagonal extents within each channel; (71.85946, 198, 201, 185, 13, 2020, 32) -> (71.67027, 198, 201, 185, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADInit: declaration order two; (71.85946, 198, 201, 185, 13, 2020, 32) -> (71.53513, 197, 201, 185, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADiSamplingCallback: restore special device cases from switch branches; (84.2033, 152, 175, 182, 13, 2020, 32) -> (88.14835, 108, 182, 182, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADiSamplingCallback: restore unordered min branch; (84.2033, 152, 175, 182, 13, 2020, 32) -> (85.3022, 133, 176, 182, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADiSamplingCallback: scope sensor constants after position query; (84.2033, 152, 175, 182, 13, 2020, 32) -> (87.91209, 152, 175, 182, 13, 2020, 32)
src/system/odh cdj_c_colorConv: declare image planes before assignments; (97.402596, 30, 77, 77, 16, 4092, 6360) -> (97.402596, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: declare image planes in reverse order; (97.402596, 30, 77, 77, 16, 4092, 6360) -> (98.31169, 23, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: declare image planes by name; (97.402596, 30, 77, 77, 16, 4092, 6360) -> (97.72727, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: source offset adds base last; (97.402596, 30, 77, 77, 16, 4092, 6360) -> (97.46753, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_d_decompressLoop: decoder local declaration order one; (97.67297, 383, 899, 899, 16, 4092, 6360) -> (97.60623, 395, 899, 899, 16, 4092, 6360)
src/system/odh cdj_d_decompressLoop: decoder local declaration order two; (97.67297, 383, 899, 899, 16, 4092, 6360) -> (97.67297, 383, 899, 899, 16, 4092, 6360)
src/system/odh cdj_d_decompressLoop: decoder local declaration order three; (97.67297, 383, 899, 899, 16, 4092, 6360) -> (97.60623, 395, 899, 899, 16, 4092, 6360)
src/system/odh LineDeconv22: declare image planes before assignments; (96.434425, 115, 244, 244, 16, 4092, 6360) -> (96.434425, 115, 244, 244, 16, 4092, 6360)
src/system/odh LineDeconv22: declare image planes in reverse order; (96.434425, 115, 244, 244, 16, 4092, 6360) -> (96.434425, 115, 244, 244, 16, 4092, 6360)
src/system/odh LineDeconv22: pixel addressing adds destination last; (96.434425, 115, 244, 244, 16, 4092, 6360) -> (96.434425, 115, 244, 244, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 0, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.46753, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 1, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 2, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.207794, 31, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 3, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (98.05195, 21, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 4, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (98.31169, 20, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 5, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 6, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.53247, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 7, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.53247, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 8, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (98.31169, 20, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 9, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 10, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 11, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.792206, 27, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 12, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 13, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 14, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.85714, 27, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 15, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (98.05195, 21, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 16, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.46753, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 17, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 18, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.46753, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: plane/stride declarations 19, explicit remainder and base-first address; (98.31169, 23, 77, 77, 16, 4092, 6360) -> (97.53247, 29, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: unsigned table byte offsets remove signed divide correction; (81.671425, 58, 72, 70, 16, 4092, 6360) -> (85.171425, 49, 70, 70, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: unsigned offsets and indexed quantization destination; (81.671425, 58, 72, 70, 16, 4092, 6360) -> (84.9, 58, 71, 70, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: unsigned offsets and explicit standard table cursor; (81.671425, 58, 72, 70, 16, 4092, 6360) -> (78.21429, 63, 68, 70, 16, 4092, 6360)
src/system/odh cdj_d_setDequantizationTable: unsigned table byte offset; (88.27451, 46, 54, 51, 16, 4092, 6360) -> (92.98039, 44, 52, 51, 16, 4092, 6360)
src/system/odh cdj_d_setDequantizationTable: quantization destination expressed as row indices; (88.27451, 46, 54, 51, 16, 4092, 6360) -> (94.60784, 30, 51, 51, 16, 4092, 6360)
src/system/odh cdj_d_setDequantizationTable: unsigned offset and coefficient declaration order; (88.27451, 46, 54, 51, 16, 4092, 6360) -> (92.98039, 44, 52, 51, 16, 4092, 6360)
src/system/odh LineConv11: signed pixel cursor; (80.746574, 102, 146, 146, 16, 4092, 6360) -> (80.746574, 102, 146, 146, 16, 4092, 6360)
src/system/odh LineConv11: blue/red scale products on right; (80.746574, 102, 146, 146, 16, 4092, 6360) -> (80.746574, 102, 146, 146, 16, 4092, 6360)
src/system/odh fdct_fast: use existing butterfly temporaries throughout both passes; (78.30769, 118, 169, 169, 16, 4092, 6360) -> (78.36687, 118, 169, 169, 16, 4092, 6360)
src/system/odh fdct_fast: reverse independent even-sum add operands; (78.30769, 118, 169, 169, 16, 4092, 6360) -> (78.23669, 120, 169, 169, 16, 4092, 6360)
src/system/odh fdct_fast: column input traversal uses a cursor; (78.30769, 118, 169, 169, 16, 4092, 6360) -> (73.40237, 161, 167, 169, 16, 4092, 6360)
src/system/odh huffmanCoder: signed input cursor eliminates explicit sign-extension shifts; (91.96319, 155, 166, 163, 16, 4092, 6360) -> BUILD FAIL 3" tools/transform_dep.py build/43U/src/src/system/odh.d build/43U/src/src/system/odh.d
### mwcceppc.exe Compiler:
#    File: src\system\odh.cpp
# ---------------------------
#    1202:                 coefficientPointer = nextCoefficient;
#   Error:                                                     ^
#   (10209) illegal implicit conversion from 'short *' to
#   'unsigned short *'
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

src/system/odh huffmanCoder: declare predictor before block loop; (91.96319, 155, 166, 163, 16, 4092, 6360) -> (91.96319, 155, 166, 163, 16, 4092, 6360)
src/system/odh huffmanCoder: swap independent cursor and magnitude declarations; (91.96319, 155, 166, 163, 16, 4092, 6360) -> (91.96319, 155, 166, 163, 16, 4092, 6360)
src/system/odh LineDeconv21: signed pixel index; (92.578575, 125, 145, 140, 16, 4092, 6360) -> (92.578575, 125, 145, 140, 16, 4092, 6360)
src/system/odh LineDeconv21: unsigned blue channel packs with logical shift; (92.578575, 125, 145, 140, 16, 4092, 6360) -> (89.72143, 125, 145, 140, 16, 4092, 6360)
src/system/odh LineDeconv21: local declaration order one; (92.578575, 125, 145, 140, 16, 4092, 6360) -> (92.435715, 126, 145, 140, 16, 4092, 6360)
src/system/odh LineDeconv12: signed pixel index; (78.095894, 142, 148, 146, 16, 4092, 6360) -> (78.095894, 142, 148, 146, 16, 4092, 6360)
src/system/odh LineDeconv12: unsigned blue channel packs with logical shift; (78.095894, 142, 148, 146, 16, 4092, 6360) -> (77.68493, 142, 148, 146, 16, 4092, 6360)
src/system/odh LineDeconv12: local declaration order one; (78.095894, 142, 148, 146, 16, 4092, 6360) -> (78.095894, 142, 148, 146, 16, 4092, 6360)
src/system/odh huffmanDecoder: local declaration order one; (91.04902, 277, 308, 306, 16, 4092, 6360) -> (91.13072, 277, 308, 306, 16, 4092, 6360)
src/system/odh huffmanDecoder: local declaration order two; (91.04902, 277, 308, 306, 16, 4092, 6360) -> (91.13072, 277, 308, 306, 16, 4092, 6360)
src/system/odh huffmanDecoder: local declaration order three; (91.04902, 277, 308, 306, 16, 4092, 6360) -> (91.473854, 277, 308, 306, 16, 4092, 6360)
src/system/odh idct_fast: local declaration order one; (70.49789, 174, 236, 237, 16, 4092, 6360) -> (67.43038, 188, 236, 237, 16, 4092, 6360)
src/system/odh idct_fast: local declaration order two; (70.49789, 174, 236, 237, 16, 4092, 6360) -> (69.92827, 175, 236, 237, 16, 4092, 6360)
src/system/odh idct_fast: local declaration order three; (70.49789, 174, 236, 237, 16, 4092, 6360) -> (71.101265, 175, 236, 237, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 0; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (98.11688, 25, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 1; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.53247, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 2; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.53247, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 3; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (98.376625, 21, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 4; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.85714, 27, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 5; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.53247, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 6; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.53247, 29, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 7; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.53247, 29, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 8; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.987015, 22, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 9; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.207794, 31, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 10; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.53247, 29, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 11; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (98.31169, 20, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 12; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.207794, 31, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 13; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 14; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.207794, 31, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 15; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.53247, 29, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 16; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.792206, 27, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 17; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (98.05195, 25, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 18; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.53247, 29, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 19; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.207794, 31, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 20; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.207794, 31, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 21; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.792206, 27, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 22; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.53247, 29, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 23; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.46753, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 24; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (98.05195, 25, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 25; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 26; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.85714, 27, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 27; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.207794, 31, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 28; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.792206, 28, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 29; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.207794, 31, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 30; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.207794, 31, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: dimension and stride declaration order 31; (98.31169, 20, 77, 77, 16, 4092, 6360) -> (97.85714, 27, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: indexed destination row, variant 0; (85.171425, 49, 70, 70, 16, 4092, 6360) -> (86.51428, 49, 70, 70, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: indexed destination row, variant 1; (85.171425, 49, 70, 70, 16, 4092, 6360) -> (83.37143, 49, 70, 70, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: indexed destination row, variant 2; (85.171425, 49, 70, 70, 16, 4092, 6360) -> (86.51428, 49, 70, 70, 16, 4092, 6360)
src/BS2/BS2Mach BS2NANDDivideReadAsync: global state assignment order from target; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (60.31915, 44, 45, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideReadAsync: state assignment order and test incoming length; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (60.31915, 44, 45, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideReadAsync: keep request buffer for report; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (60.31915, 44, 45, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideWriteAsync: global state assignment order from target; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (60.31915, 44, 45, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideWriteAsync: state assignment order and test incoming length; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (60.31915, 44, 45, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideWriteAsync: keep request buffer for report; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (60.31915, 44, 45, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGCGame: poll cover command field directly; (98.11404, 97, 227, 228, 21, 4052, 155504) -> (95.4386, 103, 227, 228, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGCGame: time conversion expression from RTC and frequency; (98.11404, 97, 227, 228, 21, 4052, 155504) -> (98.24561, 93, 227, 228, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGCGame: reverse RTC local declarations; (98.11404, 97, 227, 228, 21, 4052, 155504) -> (98.11404, 97, 227, 228, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGame: poll cover command field directly; (95.496185, 173, 401, 393, 21, 4052, 155504) -> (93.94402, 179, 401, 393, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGame: reverse title-version local declarations; (95.496185, 173, 401, 393, 21, 4052, 155504) -> (95.31807, 186, 401, 393, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGame: poll cover with explicit do loop; (95.496185, 173, 401, 393, 21, 4052, 155504) -> (93.94402, 179, 401, 393, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideCallback: remaining length local reused for transfer decision; (85.03906, 107, 119, 128, 21, 4052, 155504) -> (85.03906, 107, 119, 128, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideCallback: cancel and error branches return immediately; (85.03906, 107, 119, 128, 21, 4052, 155504) -> (85.03906, 107, 119, 128, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideCallback: perform buffer update before transferred count; (85.03906, 107, 119, 128, 21, 4052, 155504) -> (85.0, 107, 119, 128, 21, 4052, 155504)
src/BS2/BS2Mach CheckBS2CommandStatus: unsigned declaration block reversed; (80.133, 321, 387, 406, 21, 4052, 155504) -> (80.133, 321, 387, 406, 21, 4052, 155504)
src/BS2/BS2Mach CheckBS2CommandStatus: signed partition count local; (80.133, 321, 387, 406, 21, 4052, 155504) -> (80.133, 321, 387, 406, 21, 4052, 155504)
src/BS2/BS2Mach CheckBS2CommandStatus: signed chunk length local; (80.133, 321, 387, 406, 21, 4052, 155504) -> (80.133, 321, 387, 406, 21, 4052, 155504)
src/BS2/BS2Mach BS2Tick: reverse integer declaration block; (74.78608, 1765, 1905, 1940, 21, 4052, 155504) -> (74.78608, 1765, 1905, 1940, 21, 4052, 155504)
src/BS2/BS2Mach Run: preincrement block after cache operations; (0, 43, 28, 43, 21, 4052, 155504) -> (0, 43, 28, 43, 21, 4052, 155504)
src/BS2/BS2Mach Run: use bounded cache block loop; (0, 43, 28, 43, 21, 4052, 155504) -> (0, 43, 31, 43, 21, 4052, 155504)
src/BS2/BS2Mach Run: decrement count before cache operations; (0, 43, 28, 43, 21, 4052, 155504) -> (0, 43, 29, 43, 21, 4052, 155504)
src/BS2/BS2Update BS2UpdateInit: retain workspace pointer before reporting; (77.5, 61, 71, 72, 8, 112, 0) -> (77.5, 61, 71, 72, 8, 112, 0)
src/BS2/BS2Update BS2UpdateInit: compute thread and DMA flag buffer pointers before reporting; (77.5, 61, 71, 72, 8, 112, 0) -> (90.09722, 50, 72, 72, 8, 112, 0)
src/BS2/BS2Update BS2UpdateInit: retain thread storage as a typed pointer before reporting; (77.5, 61, 71, 72, 8, 112, 0) -> (90.09722, 50, 72, 72, 8, 112, 0)
src/BS2/BS2Update UpdateThread: initialize counters after entry report to match block order; (78.59365, 884, 866, 913, 8, 112, 0) -> (79.10186, 884, 865, 913, 8, 112, 0)
src/BS2/BS2Update UpdateThread: keep primary update entry cursor across scan; (78.59365, 884, 866, 913, 8, 112, 0) -> (77.02628, 886, 865, 913, 8, 112, 0)
src/BS2/BS2Update UpdateThread: compare region characters in unsigned integer temporary; (78.59365, 884, 866, 913, 8, 112, 0) -> (78.31873, 882, 862, 913, 8, 112, 0)
src/BS2/BS2Mach BS2Tick: declare title prefix before code; (74.78608, 1765, 1905, 1940, 21, 4052, 155504) -> (74.78608, 1765, 1905, 1940, 21, 4052, 155504)
src/BS2/BS2Mach BS2Tick: declare read address before read length and offset; (74.78608, 1765, 1905, 1940, 21, 4052, 155504) -> (74.7866, 1765, 1905, 1940, 21, 4052, 155504)
src/BS2/BS2Mach BS2Tick: interrupt mask retains BOOL result type; (74.78608, 1765, 1905, 1940, 21, 4052, 155504) -> (74.78608, 1765, 1905, 1940, 21, 4052, 155504)
src/system/odh LineConv11: blue conversion constant declared before red and green constants; (80.746574, 102, 146, 146, 16, 4092, 6360) -> (80.712326, 102, 146, 146, 16, 4092, 6320)

Final source selection

KPAD retains the two exact functions and assembly-derived bound/device corrections. Odh and BS2Mach source experiments are reverted because none increased their exact counts. BS2Update retains the reconstructed initializer and complete thread, the integer progress counter, real thread/flag/header storage, and guarded metadata fields. The aggregate workspace experiment was removed. All 55 BS2Update strings are ordinary literals and identical in pool order. The product-area jump table maps areas 0 and 5 to J/D, 1 to E/D, 2 to P/D, 6 to K, and 11 to C; other areas reject. Both new functions remain nonmatching. No linking status changed.

libs/RVL_SDK/src/kpad/KPAD final unmatched functions
get_ring_buffer_by_kpad1_style: objdiff 99.583336%; instructions 96/96, positional differences 7; register allocation / operand order / scheduling.
reset_kpad: objdiff 65.17094%; instructions 115/117, positional differences 101; block layout / missing or extra instructions / scheduling.
KPADGetProjectionPos: objdiff 96.57895%; instructions 19/19, positional differences 9; register allocation / operand order / scheduling.
KPADSetSensorHeight: objdiff 93.55769%; instructions 52/52, positional differences 21; register allocation / operand order / scheduling.
calc_acc_horizon: objdiff 95.89109%; instructions 100/101, positional differences 87; block layout / missing or extra instructions / scheduling.
read_kpad_acc: objdiff 63.5625%; instructions 396/400, positional differences 386; block layout / missing or extra instructions / scheduling.
select_2obj_first: objdiff 72.86066%; instructions 127/122, positional differences 110; block layout / missing or extra instructions / scheduling.
select_2obj_continue: objdiff 83.37681%; instructions 141/138, positional differences 124; block layout / missing or extra instructions / scheduling.
select_1obj_first: objdiff 70.220184%; instructions 93/109, positional differences 109; block layout / missing or extra instructions / scheduling.
select_1obj_continue: objdiff 79.80645%; instructions 95/93, positional differences 92; block layout / missing or extra instructions / scheduling.
calc_dpd_variable: objdiff 71.404%; instructions 231/250, positional differences 241; block layout / missing or extra instructions / scheduling.
read_kpad_dpd: objdiff 72.39209%; instructions 281/278, positional differences 271; block layout / missing or extra instructions / scheduling.
read_kpad_stick: objdiff 95.3481%; instructions 157/158, positional differences 108; block layout / missing or extra instructions / scheduling.
KPADRead: objdiff 83.10022%; instructions 470/459, positional differences 459; block layout / missing or extra instructions / scheduling.
KPADInit: objdiff 71.85946%; instructions 201/185, positional differences 198; block layout / missing or extra instructions / scheduling.
KPADiSamplingCallback: objdiff 88.14835%; instructions 182/182, positional differences 108; register allocation / operand order / scheduling.

src/system/odh final unmatched functions
cdj_c_setQuantizationTable__9CArGBAOdhFP16SArCDJ_OdhMasterUl: objdiff 81.671425%; instructions 72/70, positional differences 58; block layout / missing or extra instructions / scheduling.
cdj_c_colorConv__9CArGBAOdhFP16SArCDJ_OdhMasterPUci: objdiff 97.402596%; instructions 77/77, positional differences 30; register allocation / operand order / scheduling.
LineConv11__9CArGBAOdhFPUcPUcPUcPUcUsUsPCli: objdiff 80.746574%; instructions 146/146, positional differences 102; register allocation / operand order / scheduling.
fdct_fast__9CArGBAOdhFPUlPUcUlPUl: objdiff 78.30769%; instructions 169/169, positional differences 118; register allocation / operand order / scheduling.
huffmanCoder__9CArGBAOdhFPUsP21SArCDJ_HuffmanRequest: objdiff 91.96319%; instructions 166/163, positional differences 155; block layout / missing or extra instructions / scheduling.
cdj_d_decompressLoop__9CArGBAOdhFP16SArCDJ_OdhMasterii: objdiff 97.67297%; instructions 899/899, positional differences 383; register allocation / operand order / scheduling.
cdj_d_setDequantizationTable__9CArGBAOdhFP16SArCDJ_OdhMasterUl: objdiff 88.27451%; instructions 54/51, positional differences 46; block layout / missing or extra instructions / scheduling.
LineDeconv21__9CArGBAOdhFPUcPUcPUcPUcUsUsPC12SArDeconvTbli: objdiff 92.578575%; instructions 145/140, positional differences 125; block layout / missing or extra instructions / scheduling.
LineDeconv12__9CArGBAOdhFPUcPUcPUcPUcUsUsPC12SArDeconvTbli: objdiff 78.095894%; instructions 148/146, positional differences 142; block layout / missing or extra instructions / scheduling.
LineDeconv22__9CArGBAOdhFPUcPUcPUcPUcUsUsPC12SArDeconvTbli: objdiff 96.434425%; instructions 244/244, positional differences 115; register allocation / operand order / scheduling.
huffmanDecoder__9CArGBAOdhFPUlP21SArCDJ_HuffmanRequestPPUsiUl: objdiff 91.04902%; instructions 308/306, positional differences 277; block layout / missing or extra instructions / scheduling.
idct_fast__9CArGBAOdhFPCUcPUlPUlPUcUl: objdiff 70.49789%; instructions 236/237, positional differences 174; block layout / missing or extra instructions / scheduling.

src/BS2/BS2Mach final unmatched functions
Run: objdiff unscored; instructions 28/43, positional differences 43; block layout / missing or extra instructions / scheduling.
BS2StartGame: objdiff 95.496185%; instructions 401/393, positional differences 173; block layout / missing or extra instructions / scheduling.
BS2StartGCGame: objdiff 98.11404%; instructions 227/228, positional differences 97; block layout / missing or extra instructions / scheduling.
BS2NANDDivideCallback: objdiff 85.03906%; instructions 119/128, positional differences 107; block layout / missing or extra instructions / scheduling.
BS2NANDDivideReadAsync: objdiff 60.29787%; instructions 45/47, positional differences 45; block layout / missing or extra instructions / scheduling.
BS2NANDDivideWriteAsync: objdiff 60.29787%; instructions 45/47, positional differences 45; block layout / missing or extra instructions / scheduling.
CheckBS2CommandStatus: objdiff 80.133%; instructions 387/406, positional differences 321; block layout / missing or extra instructions / scheduling.
BS2Tick: objdiff 74.78608%; instructions 1905/1940, positional differences 1765; block layout / missing or extra instructions / scheduling.

src/BS2/BS2Update final unmatched functions
BS2UpdateInit: objdiff 79.875%; instructions 71/72, positional differences 65; block layout / missing or extra instructions / scheduling.
UpdateThread: objdiff 84.05586%; instructions 863/913, positional differences 867; block layout / missing or extra instructions / scheduling.
