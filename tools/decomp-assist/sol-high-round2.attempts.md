Round 2; base f9bd6755; candidates measured independently from the current function body.
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: reuse channel argument for unsigned sample loop; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.958336, 15, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: scope device selector within loop; (99.583336, 7, 96, 96, 13, 2020, 32) -> BUILD FAIL 3U/src/libs/RVL_SDK/src/kpad && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\kpad\KPAD.c
# -------------------------------------
#     204:         u32 type = kpad->ringData[index].device;
#   Error:         ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declare interrupt token before indices after size; (99.583336, 7, 96, 96, 13, 2020, 32) -> (99.010414, 17, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: reverse scale and coordinate multiplication operands; (96.57895, 9, 19, 19, 13, 2020, 32) -> (95.52631, 10, 19, 19, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: define projection factor after y temporary; (96.57895, 9, 19, 19, 13, 2020, 32) -> BUILD FAIL pad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\kpad\KPAD.c
# -------------------------------------
#    1242:     f64 scaled = 0.908 * scale;
#   Error:     ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: project vector using shared height and early double factor; (96.57895, 9, 19, 19, 13, 2020, 32) -> (95.52631, 11, 19, 19, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_horizon: reuse normalized vector components after projection; (95.89109, 87, 100, 101, 13, 2020, 32) -> (88.0, 87, 100, 101, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_horizon: keep horizon state as a vector copy; (95.89109, 87, 100, 101, 13, 2020, 32) -> (93.77228, 95, 102, 101, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_acc_horizon: reuse magnitude for final vector length; (95.89109, 87, 100, 101, 13, 2020, 32) -> (95.89109, 87, 100, 101, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declare sample ordinal after device with scoped device local; (99.583336, 7, 96, 96, 13, 2020, 32) -> (99.583336, 7, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: put destination width after loop ordinal and pointer last; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: declare all single precision coordinates before double scaling; (96.57895, 9, 19, 19, 13, 2020, 32) -> (96.57895, 10, 19, 19, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: calculate projection using a temporary vector; (96.57895, 9, 19, 19, 13, 2020, 32) -> (59.105263, 20, 23, 19, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_stick: retain clamp selector after extension pointer; (95.3481, 108, 157, 158, 13, 2020, 32) -> (93.00633, 123, 157, 158, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_stick: declare device and format before clamp and extension; (95.3481, 108, 157, 158, 13, 2020, 32) -> (95.3481, 108, 157, 158, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_stick: use local trigger range once for both trigger divisions; (95.3481, 108, 157, 158, 13, 2020, 32) -> (91.025314, 98, 156, 158, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: select minimum extent with a conditional expression; (93.55769, 21, 52, 52, 13, 2020, 32) -> (97.59615, 19, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: divide along separate width and height branches; (93.55769, 21, 52, 52, 13, 2020, 32) -> (91.59615, 31, 53, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: compute width squared before assigning height; (93.55769, 21, 52, 52, 13, 2020, 32) -> (93.55769, 21, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADiSamplingCallback: keep ring slot pointer before slot ordinal; (88.14835, 108, 182, 182, 13, 2020, 32) -> (88.14835, 108, 182, 182, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADiSamplingCallback: scope sensor extent scalars before angle and offset; (88.14835, 108, 182, 182, 13, 2020, 32) -> (87.79121, 108, 182, 182, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADiSamplingCallback: scale mode table index before querying DPD hardware; (88.14835, 108, 182, 182, 13, 2020, 32) -> (81.62637, 175, 178, 182, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_continue: copy whole typed candidate objects; (83.37681, 124, 141, 138, 13, 2020, 32) -> (86.347824, 124, 141, 138, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_continue: derive normalized direction before inverse distance; (83.37681, 124, 141, 138, 13, 2020, 32) -> (83.37681, 124, 141, 138, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_continue: split reversed and forward best candidates into signed dot branches; (83.37681, 124, 141, 138, 13, 2020, 32) -> (79.615944, 112, 140, 138, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADRead: retain conditional callback with pending flag test; (83.10022, 459, 470, 459, 13, 2020, 32) -> (83.57952, 458, 471, 459, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADRead: signed circular sample index following target cmpwi; (83.10022, 459, 470, 459, 13, 2020, 32) -> (83.05665, 459, 470, 459, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADRead: keep copied sample after gravity workspace to influence live frame; (83.10022, 459, 470, 459, 13, 2020, 32) -> (83.10022, 459, 470, 459, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_continue: walk second candidate with saved end pointer; (79.80645, 92, 95, 93, 13, 2020, 32) -> (79.37634, 93, 95, 93, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_continue: compute both tangent products before direction sums; (79.80645, 92, 95, 93, 13, 2020, 32) -> (80.07527, 92, 95, 93, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_continue: scale direction on right of products; (79.80645, 92, 95, 93, 13, 2020, 32) -> (79.860214, 92, 95, 93, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_first: cache first pointer for each inner pair scan; (72.86066, 110, 127, 122, 13, 2020, 32) -> (72.86066, 110, 127, 122, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_first: compute distance before direction normalization; (72.86066, 110, 127, 122, 13, 2020, 32) -> (72.86066, 110, 127, 122, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_2obj_first: copy absolute orientation into score after distance validation; (72.86066, 110, 127, 122, 13, 2020, 32) -> (72.86066, 110, 127, 122, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_dpd: use postdecrement pointer comparisons in DPD sample loop; (72.39209, 271, 281, 278, 13, 2020, 32) -> (73.54317, 271, 281, 278, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_dpd: scope pair normalization as vector delta; (72.39209, 271, 281, 278, 13, 2020, 32) -> BUILD FAIL D.c -o build/43U/src/libs/RVL_SDK/src/kpad && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\kpad\KPAD.c
# -------------------------------------
#    1005:         f32 scale = 1.0f / length;
#   Error:         ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

libs/RVL_SDK/src/kpad/KPAD read_kpad_dpd: iterate duplicate objects with a counted inner loop; (72.39209, 271, 281, 278, 13, 2020, 32) -> (72.28058, 271, 281, 278, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADInit: separate reference extents from adjusted extents by reusing scalars; (71.85946, 198, 201, 185, 13, 2020, 32) -> (71.72433, 198, 201, 185, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADInit: introduce explicit squared reference extents before center reads; (71.85946, 198, 201, 185, 13, 2020, 32) -> (71.61622, 198, 201, 185, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADInit: normalize extent selection with conditional expression and late matrix pointer; (71.85946, 198, 201, 185, 13, 2020, 32) -> (72.46487, 197, 200, 185, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_dpd_variable: round horizontal rotation through local vector copy; (71.404, 241, 231, 250, 13, 2020, 32) -> (73.028, 247, 237, 250, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_dpd_variable: use vector for blended final position; (71.404, 241, 231, 250, 13, 2020, 32) -> (73.56, 241, 235, 250, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD calc_dpd_variable: separate distance blend product before delta multiplication; (71.404, 241, 231, 250, 13, 2020, 32) -> (71.384, 241, 231, 250, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_first: construct missing endpoint vectors and typed coordinate copies; (70.220184, 109, 93, 109, 13, 2020, 32) -> (62.183487, 99, 112, 109, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_first: construct endpoint vectors and defer bounds to individual tests; (70.220184, 109, 93, 109, 13, 2020, 32) -> (73.02752, 114, 116, 109, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD select_1obj_first: copy both candidate and endpoint as typed objects; (70.220184, 109, 93, 109, 13, 2020, 32) -> (62.201836, 99, 112, 109, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD reset_kpad: walk pointers downward through inclusive beginning; (65.17094, 101, 115, 117, 13, 2020, 32) -> (0, 264, 264, 117, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD reset_kpad: copy the stored acceleration as a typed vector; (65.17094, 101, 115, 117, 13, 2020, 32) -> (69.37607, 121, 126, 117, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD reset_kpad: compute scaled reference after all bounds then resets; (65.17094, 101, 115, 117, 13, 2020, 32) -> (61.76923, 117, 116, 117, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_acc: represent core acceleration as local vector for length and speed; (63.5625, 386, 396, 400, 13, 2020, 32) -> (65.735, 383, 400, 400, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_acc: retain raw freestyle axes as named fields instead of array alias; (63.5625, 386, 396, 400, 13, 2020, 32) -> (63.5625, 386, 396, 400, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_acc: perform format selection with a switch over supported formats; (63.5625, 386, 396, 400, 13, 2020, 32) -> (64.3, 388, 398, 400, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: update half extents with compound assignments; (97.59615, 19, 52, 52, 13, 2020, 32) -> (98.84615, 10, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: initialize extents and squared lengths in separate scope; (97.59615, 19, 52, 52, 13, 2020, 32) -> (98.17308, 11, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: keep adjusted extents in original variables with goto join; (97.59615, 19, 52, 52, 13, 2020, 32) -> (91.63461, 32, 53, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD read_kpad_dpd: keep candidate delta as a Vec2 after correct C89 declarations; (73.54317, 271, 281, 278, 13, 2020, 32) -> (65.89568, 274, 277, 278, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes index,kpad,enabled,i,size,type,latest; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes size,i,type,index,latest,enabled,kpad; (99.583336, 7, 96, 96, 13, 2020, 32) -> (99.114586, 16, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes i,index,type,latest,kpad,size,enabled; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes size,latest,i,kpad,enabled,index,type; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes kpad,i,type,size,enabled,index,latest; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.697914, 21, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes kpad,i,type,enabled,latest,size,index; (99.583336, 7, 96, 96, 13, 2020, 32) -> (99.010414, 17, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes index,latest,size,type,i,enabled,kpad; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes kpad,type,index,enabled,i,latest,size; (99.583336, 7, 96, 96, 13, 2020, 32) -> (99.0625, 15, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes kpad,index,size,enabled,type,i,latest; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.90625, 18, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes latest,i,enabled,kpad,size,type,index; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes kpad,index,enabled,type,size,i,latest; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.90625, 18, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes i,enabled,size,index,type,latest,kpad; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.697914, 21, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes index,latest,i,enabled,kpad,type,size; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.75, 21, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes latest,enabled,index,type,i,kpad,size; (99.583336, 7, 96, 96, 13, 2020, 32) -> (99.166664, 14, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes enabled,size,kpad,type,latest,index,i; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.802086, 21, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes index,latest,kpad,type,i,enabled,size; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.75, 21, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes i,latest,type,size,enabled,kpad,index; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes type,latest,enabled,kpad,size,i,index; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.802086, 20, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes index,kpad,type,enabled,i,size,latest; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes type,size,latest,enabled,i,index,kpad; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.59375, 23, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes size,i,kpad,type,enabled,latest,index; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes type,index,enabled,kpad,latest,size,i; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.90625, 19, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes kpad,type,size,latest,i,enabled,index; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.697914, 21, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes enabled,type,index,latest,kpad,size,i; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes index,latest,type,size,enabled,kpad,i; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes i,type,size,kpad,latest,enabled,index; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.802086, 21, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes enabled,kpad,size,latest,type,index,i; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.802086, 21, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes i,size,latest,enabled,kpad,index,type; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes type,latest,i,kpad,size,enabled,index; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes size,enabled,i,index,kpad,type,latest; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.59375, 23, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes i,size,enabled,kpad,index,latest,type; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes enabled,index,size,i,latest,kpad,type; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.59375, 23, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes size,type,latest,index,kpad,enabled,i; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.802086, 20, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes enabled,index,size,i,kpad,latest,type; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: declaration lifetimes type,i,size,enabled,kpad,latest,index; (99.583336, 7, 96, 96, 13, 2020, 32) -> (98.489586, 25, 96, 96, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 0; (98.84615, 10, 52, 52, 13, 2020, 32) -> (97.01923, 19, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 1; (98.84615, 10, 52, 52, 13, 2020, 32) -> (97.21154, 19, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 2; (98.84615, 10, 52, 52, 13, 2020, 32) -> (97.01923, 19, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 3; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.65385, 13, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 4; (98.84615, 10, 52, 52, 13, 2020, 32) -> (99.03846, 8, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 5; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.26923, 16, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 6; (98.84615, 10, 52, 52, 13, 2020, 32) -> (96.44231, 22, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 7; (98.84615, 10, 52, 52, 13, 2020, 32) -> (96.63461, 22, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 8; (98.84615, 10, 52, 52, 13, 2020, 32) -> (97.21154, 19, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 9; (98.84615, 10, 52, 52, 13, 2020, 32) -> (99.23077, 7, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 10; (98.84615, 10, 52, 52, 13, 2020, 32) -> (97.01923, 19, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 11; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.65385, 13, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 12; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.84615, 10, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 13; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.26923, 16, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 14; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.84615, 10, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 15; (98.84615, 10, 52, 52, 13, 2020, 32) -> (97.01923, 19, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 16; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.65385, 13, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 17; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.46154, 15, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 18; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.84615, 10, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 19; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.46154, 14, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 20; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.26923, 16, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 21; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.84615, 10, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 22; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.26923, 16, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 23; (98.84615, 10, 52, 52, 13, 2020, 32) -> (97.01923, 19, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 24; (98.84615, 10, 52, 52, 13, 2020, 32) -> (96.44231, 22, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 25; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.26923, 16, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 26; (98.84615, 10, 52, 52, 13, 2020, 32) -> (96.82692, 20, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 27; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.46154, 15, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 28; (98.84615, 10, 52, 52, 13, 2020, 32) -> (99.03846, 8, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 29; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.46154, 15, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 30; (98.84615, 10, 52, 52, 13, 2020, 32) -> (96.44231, 22, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 31; (98.84615, 10, 52, 52, 13, 2020, 32) -> (97.01923, 19, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 32; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.26923, 16, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 33; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.26923, 16, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: extent scalar order 34; (98.84615, 10, 52, 52, 13, 2020, 32) -> (98.26923, 16, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: initialize channel pointer in declaration; (99.23077, 7, 52, 52, 13, 2020, 32) -> (99.23077, 7, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: load zero as a named local before squared extents; (99.23077, 7, 52, 52, 13, 2020, 32) -> (99.03846, 8, 52, 52, 13, 2020, 32)
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: square height within combined diagonal calculation; (99.23077, 7, 52, 52, 13, 2020, 32) -> (99.03846, 9, 52, 52, 13, 2020, 32)
src/system/odh cdj_d_decompressLoop: restore typed member Huffman calls; (97.67297, 383, 899, 899, 16, 4092, 6360) -> BUILD FAIL   Error:                                                                 ^
#   (10248) function call '[CArGBAOdh].huffmanDecoder({lval} unsigned
#   long[64], SArCDJ_HuffmanRequest *, {lval} const unsigned long *[4], int,
#   {lval} int)' does not match
#   'CArGBAOdh::huffmanDecoder(unsigned long *, SArCDJ_HuffmanRequest *,
#   unsigned short **, int, unsigned long)' (non-static)
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

src/system/odh cdj_d_decompressLoop: restore typed member inverse transform calls; (97.67297, 383, 899, 899, 16, 4092, 6360) -> (97.65073, 385, 899, 899, 16, 4092, 6360)
src/system/odh cdj_d_decompressLoop: restore all typed member decoder and transform calls; (97.67297, 383, 899, 899, 16, 4092, 6360) -> BUILD FAIL   Error:                                                                 ^
#   (10248) function call '[CArGBAOdh].huffmanDecoder({lval} unsigned
#   long[64], SArCDJ_HuffmanRequest *, {lval} const unsigned long *[4], int,
#   {lval} int)' does not match
#   'CArGBAOdh::huffmanDecoder(unsigned long *, SArCDJ_HuffmanRequest *,
#   unsigned short **, int, unsigned long)' (non-static)
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.

src/system/odh cdj_c_colorConv: declare persistent plane pointers before dimension processing; (97.402596, 30, 77, 77, 16, 4092, 6360) -> (97.402596, 30, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: keep height before width test and iterate with signed row; (97.402596, 30, 77, 77, 16, 4092, 6360) -> (92.207794, 32, 77, 77, 16, 4092, 6360)
src/system/odh cdj_c_colorConv: keep plane size as shared unsigned scalar; (97.402596, 30, 77, 77, 16, 4092, 6360) -> (97.402596, 30, 77, 77, 16, 4092, 6360)
src/system/odh LineDeconv22: keep output and planar destinations before pixel count; (96.434425, 115, 244, 244, 16, 4092, 6360) -> (96.065575, 127, 244, 244, 16, 4092, 6360)
src/system/odh LineDeconv22: use signed raster index with unsigned texture masks; (96.434425, 115, 244, 244, 16, 4092, 6360) -> (96.434425, 115, 244, 244, 16, 4092, 6360)
src/system/odh LineDeconv22: reuse packed red scalar instead of fresh pixel temporaries; (96.434425, 115, 244, 244, 16, 4092, 6360) -> (95.45082, 119, 244, 244, 16, 4092, 6360)
src/system/odh LineDeconv21: use packed pixel scalar separate from red channel; (92.578575, 125, 145, 140, 16, 4092, 6360) -> (92.578575, 125, 145, 140, 16, 4092, 6360)
src/system/odh LineDeconv21: calculate texture stride in unsigned plane arithmetic; (92.578575, 125, 145, 140, 16, 4092, 6360) -> (92.578575, 125, 145, 140, 16, 4092, 6360)
src/system/odh LineDeconv21: keep channel samples and output pointer in inner loop scope; (92.578575, 125, 145, 140, 16, 4092, 6360) -> (92.61429, 124, 145, 140, 16, 4092, 6360)
src/system/odh cdj_d_decompressLoop: typed decoder and inverse calls with actual table pointer casts; (97.67297, 383, 899, 899, 16, 4092, 6360) -> (97.65073, 385, 899, 899, 16, 4092, 6360)
src/system/odh cdj_d_decompressLoop: typed calls with unsigned source limit parameter copy; (97.67297, 383, 899, 899, 16, 4092, 6360) -> (97.68409, 379, 899, 899, 16, 4092, 6360)
src/system/odh cdj_d_decompressLoop: typed calls with natural permutation index inside each reorder loop; (97.67297, 383, 899, 899, 16, 4092, 6360) -> (97.65073, 385, 899, 899, 16, 4092, 6360)
src/system/odh huffmanCoder: read signed coefficients with sign extension instead of shifts; (91.96319, 155, 166, 163, 16, 4092, 6360) -> (90.29448, 78, 163, 163, 16, 4092, 6360)
src/system/odh huffmanCoder: traverse signed halfword coefficient pointers consistently; (91.96319, 155, 166, 163, 16, 4092, 6360) -> (90.171776, 78, 163, 163, 16, 4092, 6360)
src/system/odh huffmanCoder: reuse next coefficient cursor with postincrement pair stepping; (91.96319, 155, 166, 163, 16, 4092, 6360) -> (91.96319, 155, 166, 163, 16, 4092, 6360)
src/system/odh huffmanDecoder: advance bitstream with a remaining-byte loop; (91.04902, 277, 308, 306, 16, 4092, 6360) -> (89.117645, 216, 306, 306, 16, 4092, 6360)
src/system/odh huffmanDecoder: use unsigned maximum Huffman bit length throughout; (91.04902, 277, 308, 306, 16, 4092, 6360) -> (90.166664, 277, 308, 306, 16, 4092, 6360)
src/system/odh huffmanDecoder: use signed table symbol category local with explicit pointer predictor; (91.04902, 277, 308, 306, 16, 4092, 6360) -> (91.04902, 277, 308, 306, 16, 4092, 6360)
src/system/odh cdj_d_setDequantizationTable: unsigned byte offset and direct field indexing; (88.27451, 46, 54, 51, 16, 4092, 6360) -> (92.98039, 44, 52, 51, 16, 4092, 6360)
src/system/odh cdj_d_setDequantizationTable: unsigned table offset with explicit row and scale indices; (88.27451, 46, 54, 51, 16, 4092, 6360) -> (92.98039, 44, 52, 51, 16, 4092, 6360)
src/system/odh cdj_d_setDequantizationTable: table pass as destination row index; (88.27451, 46, 54, 51, 16, 4092, 6360) -> (94.60784, 30, 51, 51, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: unsigned byte offset with field-indexed quantization output; (81.671425, 58, 72, 70, 16, 4092, 6360) -> (92.42857, 58, 71, 70, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: unsigned byte offset with separate scale and destination indices; (81.671425, 58, 72, 70, 16, 4092, 6360) -> (92.42857, 58, 71, 70, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: use coefficient row index for destination pointer; (81.671425, 58, 72, 70, 16, 4092, 6360) -> (86.51428, 49, 70, 70, 16, 4092, 6360)
src/system/odh LineConv11: derive color planes from named pixel count and typed source indexing; (80.746574, 102, 146, 146, 16, 4092, 6360) -> (80.60959, 102, 146, 146, 16, 4092, 6360)
src/system/odh LineConv11: declare floating chroma intermediates before luma conversion; (80.746574, 102, 146, 146, 16, 4092, 6360) -> (69.83562, 105, 146, 146, 16, 4092, 6360)
src/system/odh LineConv11: use one raster ordinal in place of duplicate counter; (80.746574, 102, 146, 146, 16, 4092, 6360) -> (80.30137, 103, 146, 146, 16, 4092, 6360)
src/system/odh fdct_fast: store butterflies in ascending even coefficient order; (78.30769, 118, 169, 169, 16, 4092, 6360) -> (73.02959, 111, 169, 169, 16, 4092, 6360)
src/system/odh fdct_fast: use signed coefficient pointer for initial centered samples; (78.30769, 118, 169, 169, 16, 4092, 6360) -> (78.30769, 118, 169, 169, 16, 4092, 6360)
src/system/odh fdct_fast: advance initial sample column by pointer rather than index; (78.30769, 118, 169, 169, 16, 4092, 6360) -> (76.87574, 131, 169, 169, 16, 4092, 6360)
src/system/odh LineDeconv12: share blue channel temporary across rows; (78.095894, 142, 148, 146, 16, 4092, 6360) -> (78.095894, 142, 148, 146, 16, 4092, 6360)
src/system/odh LineDeconv12: keep planar output pointers beside next-row pointer; (78.095894, 142, 148, 146, 16, 4092, 6360) -> (78.095894, 142, 148, 146, 16, 4092, 6360)
src/system/odh LineDeconv12: compute RGB565 channels before shifting packed pixel; (78.095894, 142, 148, 146, 16, 4092, 6360) -> (83.4726, 124, 146, 146, 16, 4092, 6360)
src/system/odh idct_fast: advance coefficient and quantization pointers at common column exit; (70.49789, 174, 236, 237, 16, 4092, 6360) -> (69.12236, 210, 233, 237, 16, 4092, 6360)
src/system/odh idct_fast: use signed workspace coefficients throughout butterfly rows; (70.49789, 174, 236, 237, 16, 4092, 6360) -> (70.49789, 174, 236, 237, 16, 4092, 6360)
src/system/odh idct_fast: calculate output row address before first workspace load; (70.49789, 174, 236, 237, 16, 4092, 6360) -> (70.49789, 174, 236, 237, 16, 4092, 6360)
src/system/odh cdj_d_setDequantizationTable: initialize destination row before standard table row; (94.60784, 30, 51, 51, 16, 4092, 6360) -> (81.01961, 38, 51, 51, 16, 4092, 6360)
src/system/odh cdj_d_setDequantizationTable: name normalization divisor at outer scope; (94.60784, 30, 51, 51, 16, 4092, 6360) -> (94.60784, 30, 51, 51, 16, 4092, 6320)
src/system/odh cdj_d_setDequantizationTable: set destination by whole row index without row pointer; (94.60784, 30, 51, 51, 16, 4092, 6360) -> (94.60784, 30, 51, 51, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: use pass and coefficient indices for direct destination field; (92.42857, 58, 71, 70, 16, 4092, 6360) -> (93.97143, 48, 70, 70, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: separate outer pass variable for scale application; (92.42857, 58, 71, 70, 16, 4092, 6360) -> (93.97143, 48, 70, 70, 16, 4092, 6360)
src/system/odh cdj_c_setQuantizationTable: keep explicit scale and output ordinal with row multiplication; (92.42857, 58, 71, 70, 16, 4092, 6360) -> (93.97143, 48, 70, 70, 16, 4092, 6360)
src/BS2/BS2Mach BS2StartGCGame: multiply RTC sum before timer frequency; (98.11404, 97, 227, 228, 21, 4052, 155504) -> (98.24561, 93, 227, 228, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGCGame: poll DVD command state directly as original load loop; (98.11404, 97, 227, 228, 21, 4052, 155504) -> (95.4386, 103, 227, 228, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGCGame: reuse SRAM counter bias for time sum temporary; (98.11404, 97, 227, 228, 21, 4052, 155504) -> (98.13596, 97, 227, 228, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGame: declare boot state flags near read and write scope; (95.496185, 173, 401, 393, 21, 4052, 155504) -> (95.496185, 173, 401, 393, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGame: poll DVD state directly before boot transition; (95.496185, 173, 401, 393, 21, 4052, 155504) -> (93.94402, 179, 401, 393, 21, 4052, 155504)
src/BS2/BS2Mach BS2StartGame: declare IOS title halves adjacent to ticket count and views; (95.496185, 173, 401, 393, 21, 4052, 155504) -> (95.2799, 189, 401, 393, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideCallback: compute remaining amount from updated total before advancing buffer; (85.03906, 107, 119, 128, 21, 4052, 155504) -> (85.03906, 107, 119, 128, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideCallback: share read and write completion test after size branches; (85.03906, 107, 119, 128, 21, 4052, 155504) -> (68.984375, 106, 128, 128, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideCallback: split cancellation and failure as early exits; (85.03906, 107, 119, 128, 21, 4052, 155504) -> (85.03906, 107, 119, 128, 21, 4052, 155504)
src/BS2/BS2Mach CheckBS2CommandStatus: combine cache-disabled conditions in one branch; (80.133, 321, 387, 406, 21, 4052, 155504) -> (80.133, 321, 387, 406, 21, 4052, 155504)
src/BS2/BS2Mach CheckBS2CommandStatus: carry transfer length through a single local before overflow check; (80.133, 321, 387, 406, 21, 4052, 155504) -> (80.133, 321, 387, 406, 21, 4052, 155504)
src/BS2/BS2Mach CheckBS2CommandStatus: compute partition rounded length after completing command flag; (80.133, 321, 387, 406, 21, 4052, 155504) -> (80.12069, 321, 387, 406, 21, 4052, 155504)
src/BS2/BS2Mach BS2Tick: use dedicated unsigned ticket byte counter; (74.78608, 1765, 1905, 1940, 21, 4052, 155504) -> (74.78608, 1765, 1905, 1940, 21, 4052, 155504)
src/BS2/BS2Mach BS2Tick: use signed OS time type for delay arithmetic; (74.78608, 1765, 1905, 1940, 21, 4052, 155504) -> (74.78608, 1765, 1905, 1940, 21, 4052, 155504)
src/BS2/BS2Mach BS2Tick: perform IOS title half extraction in named title identifier; (74.78608, 1765, 1905, 1940, 21, 4052, 155504) -> (74.77577, 1765, 1905, 1940, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideReadAsync: assign completion operation and transfer counters before pointers; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (60.31915, 44, 45, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideReadAsync: choose a bounded first transfer size before reporting and issuing; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (28.382978, 45, 37, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideReadAsync: place file pointer before length and buffer after branch comparison; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (59.87234, 43, 46, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideWriteAsync: assign completion operation and transfer counters before pointers; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (60.31915, 44, 45, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideWriteAsync: choose a bounded first transfer size before reporting and issuing; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (28.382978, 45, 37, 47, 21, 4052, 155504)
src/BS2/BS2Mach BS2NANDDivideWriteAsync: place file pointer before length and buffer after branch comparison; (60.29787, 45, 45, 47, 21, 4052, 155504) -> (59.87234, 43, 46, 47, 21, 4052, 155504)
src/BS2/BS2Mach Run: iterate cache blocks with explicit ordinal instead of predecrement; (0, 43, 28, 43, 21, 4052, 155504) -> (0, 43, 31, 43, 21, 4052, 155504)
src/BS2/BS2Mach Run: clear and flush entire cache extent as a range; (0, 43, 28, 43, 21, 4052, 155504) -> (0, 43, 25, 43, 21, 4052, 155504)
src/BS2/BS2Mach Run: transfer to application without a fourth argument value; (0, 43, 28, 43, 21, 4052, 155504) -> (0, 43, 26, 43, 21, 4052, 155504)
All four units: audited target st_value order; corrected KPAD definition order and odh header/ScaleLimit order; no missing functions.
src/BS2/BS2Update UpdateThread: walk update and seat entries by pointers with a separate flag index; (84.05586, 867, 863, 913, 8, 112, 0) -> (83.423874, 865, 860, 913, 8, 112, 0)
src/BS2/BS2Update UpdateThread: keep available bytes as a local before budget checks; (84.05586, 867, 863, 913, 8, 112, 0) -> (84.05586, 867, 863, 913, 8, 112, 0)
src/BS2/BS2Update UpdateThread: keep stack workspaces in original product title and DVD order; (84.05586, 867, 863, 913, 8, 112, 0) -> (84.05586, 867, 863, 913, 8, 112, 0)
src/BS2/BS2Update BS2UpdateInit: retain thread pointer from entry through create and resume; (79.875, 65, 71, 72, 8, 112, 0) -> (79.875, 65, 71, 72, 8, 112, 0)
src/BS2/BS2Update BS2UpdateInit: derive stack end from stack pointer kept with flag pointer; (79.875, 65, 71, 72, 8, 112, 0) -> (79.875, 65, 71, 72, 8, 112, 0)
src/BS2/BS2Update BS2UpdateInit: store allocator before issuing version report calls; (79.875, 65, 71, 72, 8, 112, 0) -> (71.611115, 64, 71, 72, 8, 112, 0)

Final remaining-function evidence; counts include only compiled candidates, not failed builds.
libs/RVL_SDK/src/kpad/KPAD get_ring_buffer_by_kpad1_style: 39 compiled attempts; 99.583336%; instructions 96/96, positional differences 7; register allocation and instruction scheduling.
libs/RVL_SDK/src/kpad/KPAD reset_kpad: 3 compiled attempts; 69.37607%; instructions 126/117, positional differences 121; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD KPADGetProjectionPos: 4 compiled attempts; 96.57895%; instructions 19/19, positional differences 9; register allocation and instruction scheduling.
libs/RVL_SDK/src/kpad/KPAD KPADSetSensorHeight: 44 compiled attempts; 99.23077%; instructions 52/52, positional differences 7; register allocation and instruction scheduling.
libs/RVL_SDK/src/kpad/KPAD calc_acc_horizon: 3 compiled attempts; 95.89109%; instructions 100/101, positional differences 87; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD read_kpad_acc: 3 compiled attempts; 65.735%; instructions 400/400, positional differences 383; register allocation and instruction scheduling.
libs/RVL_SDK/src/kpad/KPAD select_2obj_first: 3 compiled attempts; 72.86066%; instructions 127/122, positional differences 110; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD select_2obj_continue: 3 compiled attempts; 86.347824%; instructions 141/138, positional differences 124; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD select_1obj_first: 3 compiled attempts; 73.02752%; instructions 116/109, positional differences 114; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD select_1obj_continue: 3 compiled attempts; 80.07527%; instructions 95/93, positional differences 92; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD calc_dpd_variable: 3 compiled attempts; 73.56%; instructions 235/250, positional differences 241; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD read_kpad_dpd: 3 compiled attempts; 73.54317%; instructions 281/278, positional differences 271; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD read_kpad_stick: 3 compiled attempts; 95.3481%; instructions 157/158, positional differences 108; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD KPADRead: 3 compiled attempts; 83.57952%; instructions 471/459, positional differences 458; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD KPADInit: 3 compiled attempts; 72.46487%; instructions 200/185, positional differences 197; remaining control flow, reloads, or temporary storage differ.
libs/RVL_SDK/src/kpad/KPAD KPADiSamplingCallback: 3 compiled attempts; 88.14835%; instructions 182/182, positional differences 108; register allocation and instruction scheduling.
src/system/odh cdj_c_setQuantizationTable__9CArGBAOdhFP16SArCDJ_OdhMasterUl: 6 compiled attempts; 93.97143%; instructions 70/70, positional differences 48; register allocation and instruction scheduling.
src/system/odh cdj_c_colorConv__9CArGBAOdhFP16SArCDJ_OdhMasterPUci: 3 compiled attempts; 97.402596%; instructions 77/77, positional differences 30; register allocation and instruction scheduling.
src/system/odh LineConv11__9CArGBAOdhFPUcPUcPUcPUcUsUsPCli: 3 compiled attempts; 80.746574%; instructions 146/146, positional differences 102; register allocation and instruction scheduling.
src/system/odh fdct_fast__9CArGBAOdhFPUlPUcUlPUl: 3 compiled attempts; 78.30769%; instructions 169/169, positional differences 118; register allocation and instruction scheduling.
src/system/odh huffmanCoder__9CArGBAOdhFPUsP21SArCDJ_HuffmanRequest: 3 compiled attempts; 91.96319%; instructions 166/163, positional differences 155; remaining control flow, reloads, or temporary storage differ.
src/system/odh cdj_d_decompressLoop__9CArGBAOdhFP16SArCDJ_OdhMasterii: 4 compiled attempts; 97.68409%; instructions 899/899, positional differences 379; register allocation and instruction scheduling.
src/system/odh cdj_d_setDequantizationTable__9CArGBAOdhFP16SArCDJ_OdhMasterUl: 6 compiled attempts; 94.60784%; instructions 51/51, positional differences 30; register allocation and instruction scheduling.
src/system/odh LineDeconv21__9CArGBAOdhFPUcPUcPUcPUcUsUsPC12SArDeconvTbli: 3 compiled attempts; 92.61429%; instructions 145/140, positional differences 124; remaining control flow, reloads, or temporary storage differ.
src/system/odh LineDeconv12__9CArGBAOdhFPUcPUcPUcPUcUsUsPC12SArDeconvTbli: 3 compiled attempts; 83.4726%; instructions 146/146, positional differences 124; register allocation and instruction scheduling.
src/system/odh LineDeconv22__9CArGBAOdhFPUcPUcPUcPUcUsUsPC12SArDeconvTbli: 3 compiled attempts; 96.434425%; instructions 244/244, positional differences 115; register allocation and instruction scheduling.
src/system/odh huffmanDecoder__9CArGBAOdhFPUlP21SArCDJ_HuffmanRequestPPUsiUl: 3 compiled attempts; 91.04902%; instructions 308/306, positional differences 277; remaining control flow, reloads, or temporary storage differ.
src/system/odh idct_fast__9CArGBAOdhFPCUcPUlPUlPUcUl: 3 compiled attempts; 70.49789%; instructions 236/237, positional differences 174; remaining control flow, reloads, or temporary storage differ.
src/BS2/BS2Mach Run: 3 compiled attempts; None%; instructions 28/43, positional differences 43; original clears architectural registers and replaces stack before branch; cannot express that faithfully with the permitted C changes.
src/BS2/BS2Mach BS2StartGame: 3 compiled attempts; 95.496185%; instructions 401/393, positional differences 173; DVD status poll and MMIO loads plus live register allocation differ.
src/BS2/BS2Mach BS2StartGCGame: 3 compiled attempts; 98.24561%; instructions 227/228, positional differences 93; DVD status poll and MMIO loads plus live register allocation differ.
src/BS2/BS2Mach BS2NANDDivideCallback: 3 compiled attempts; 85.03906%; instructions 119/128, positional differences 107; target retains asynchronous global reloads that current nonvolatile C definitions eliminate.
src/BS2/BS2Mach BS2NANDDivideReadAsync: 3 compiled attempts; 60.31915%; instructions 45/47, positional differences 44; target retains asynchronous global reloads that current nonvolatile C definitions eliminate.
src/BS2/BS2Mach BS2NANDDivideWriteAsync: 3 compiled attempts; 60.31915%; instructions 45/47, positional differences 44; target retains asynchronous global reloads that current nonvolatile C definitions eliminate.
src/BS2/BS2Mach CheckBS2CommandStatus: 3 compiled attempts; 80.133%; instructions 387/406, positional differences 321; target retains asynchronous global reloads that current nonvolatile C definitions eliminate.
src/BS2/BS2Mach BS2Tick: 3 compiled attempts; 74.78608%; instructions 1905/1940, positional differences 1765; remaining control flow, reloads, or temporary storage differ.
src/BS2/BS2Update BS2UpdateInit: 3 compiled attempts; 79.875%; instructions 71/72, positional differences 65; target retains shared BSS base across flags and thread setup; source uses separate symbol addressing.
src/BS2/BS2Update UpdateThread: 3 compiled attempts; 84.05586%; instructions 863/913, positional differences 867; remaining control flow, reloads, or temporary storage differ.
