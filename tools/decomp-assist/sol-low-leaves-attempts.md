Baseline HEAD f4fd16f8. Current baseline report missing; nearest available ancestor 8e43db05 will be selected explicitly for gate, supplemented with current HEAD report /tmp/sol-low-start.json.
Structural diagnosis for every open function saved in /tmp/sol-low-diagnosis.
KPADGetProjectionPos | operand order: half height and pixel scale | structural/exact (0, 10) insns 19/19 | restored
KPADGetProjectionPos | target operand order: height first; pixel scale first | structural/exact (0, 10) insns 19/19 | restored
KPADGetProjectionPos | explicit double temporary initialized before products | structural/exact (0, 14) insns 19/19 | restored
reset_kpad | initialize reference distance before bounds | structural/exact (0, 10) insns 117/117 | restored
reset_kpad | expression temporary: retain numerator for both stores | structural/exact (0, 8) insns 117/117 | restored
reset_kpad | inline distance ratio and initialize reference distance | structural/exact (20, 95) insns 116/117 | restored
KPADSetSensorHeight | move channel pointer initialization ahead of constants | structural/exact (0, 7) insns 52/52 | restored
KPADSetSensorHeight | inline squares into sqrt argument | structural/exact (0, 7) insns 52/52 | restored
KPADSetSensorHeight | store center before squared intermediates | structural/exact (0, 7) insns 52/52 | restored
KPADGetProjectionPos | declaration-order search | declaration block:;       f64 scaled;;       f32 height = rect->bottom - rect->top;;       f32 halfHeight = height * 0.5f;;       f32 x = src->x * halfHeight;;       f32 y = src->y * halfHeight;; start (0, 9); best (0, 9) after 23 builds; source restored; best order was:;     f64 scaled;;     f32 height = rect->bottom - rect->top;;     f32 halfHeight = height * 0.5f;;     f32 x = src->x * halfHeight;;     f32 y = src->y * halfHeight;; 
KPADSetSensorHeight | declaration-order search | declaration block:;       KPADInside* kpad;;       f32 halfHeight;;       f32 barOffsetX;;       f32 barDiagonal;;       f32 halfWidthSquared;;       f32 halfWidth;;       f32 negativeSensorHeight;;       f32 barDiagonalSquared;;       f32 halfHeightSquared;; start (0, 7); best (0, 7) after 93 builds; source restored; best order was:;     KPADInside* kpad;;     f32 halfHeight;;     f32 barOffsetX;;     f32 barDiagonal;;     f32 halfWidthSquared;;     f32 halfWidth;;     f32 negativeSensorHeight;;     f32 barDiagonalSquared;;     f32 halfHeightSquared;; 
calc_acc_horizon | declaration-order search | declaration block:;       f32 magnitude = (f32)sqrt(kpad->acceleration.x * kpad->acceleration.x + kpad->acceleration.y * kpad->acceleration.y);;       f32 normalizedX;;       f32 normalizedY;;       f32 targetY;;       f32 targetX;;       f32 productX;;       f32 oldX;;       f32 oldY;;       f32 blend;;       f32 projectedX;;       f32 smoothing;;       f32 deltaX;;       f32 nextX;;       f32 nextY;;       f32 normalized;;       f32 unitX;;       f32 oldCircleX;;       f32 oldCircleY;;       f32 unitY;;       f32 circleX;;       f32 deltaCircleX;;       f32 circleY;;       f32 deltaCircleY;; start (2, 35); improved (0, 30); improved (0, 29); best (0, 29) after 100 builds; kept in source:;     f32 productX;;     f32 oldX;;     f32 normalizedY;;     f32 targetY;;     f32 targetX;;     f32 magnitude = (f32)sqrt(kpad->acceleration.x * kpad->acceleration.x + kpad->acceleration.y * kpad->acceleration.y);;     f32 normalizedX;;     f32 oldY;;     f32 blend;;     f32 projectedX;;     f32 smoothing;;     f32 deltaX;;     f32 nextX;;     f32 nextY;;     f32 normalized;;     f32 unitX;;     f32 oldCircleX;;     f32 oldCircleY;;     f32 unitY;;     f32 circleX;;     f32 deltaCircleX;;     f32 circleY;;     f32 deltaCircleY;; 
select_1obj_first | declaration-order search | declaration block:;       KPADDPDObject* object = kpad->dpdState.objects;;       KPADDPDObject* end = kpad->dpdState.candidates;;       f32 scale = kpad->dpdObjectScale;;       f32 productX = kpad->horizonTangent.x * kpad->horizonAxis.x;;       f32 productY = kpad->horizonTangent.y * kpad->horizonAxis.x;;       f32 offsetX = productX + kpad->horizonTangent.y * kpad->horizonAxis.y;;       f32 offsetY = productY - kpad->horizonTangent.x * kpad->horizonAxis.y;; start (2, 26); best (2, 26) after 52 builds; source restored; best order was:;     KPADDPDObject* object = kpad->dpdState.objects;;     KPADDPDObject* end = kpad->dpdState.candidates;;     f32 scale = kpad->dpdObjectScale;;     f32 productX = kpad->horizonTangent.x * kpad->horizonAxis.x;;     f32 productY = kpad->horizonTangent.y * kpad->horizonAxis.x;;     f32 offsetX = productX + kpad->horizonTangent.y * kpad->horizonAxis.y;;     f32 offsetY = productY - kpad->horizonTangent.x * kpad->horizonAxis.y;; 
kbdEventHandler | reuse report status temporary in comparisons | structural/exact (3, 148) insns 185/186 | restored
kbdEventHandler | initialize channel pointer in one expression | structural/exact (0, 6) insns 186/186 | restored
kbdEventHandler | declare report status with its first load | build failed .c -o build/43U/src/libs/RVL_SDK/src/kbd && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kbd/kbd_lib.d build/43U/src/libs/RVL_SDK/src/kbd/kbd_lib.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\kbd\kbd_lib.c
# ---------------------------------------
#     238:         u8 status = bytes[2]; 
#   Error:         ^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
 | restored
KBDSetModState | typed channel pointer for load and store | structural/exact (0, 7) insns 42/42 | restored
KBDSetModState | physical modifier masked expression | structural/exact (3, 7) insns 42/42 | restored
KBDSetModState | single modifier state temporary | structural/exact (0, 4) insns 42/42 | restored
kbd_led_handler | load completion callback before releasing command | structural/exact (24, 19) insns 23/25 | restored
select_1obj_continue | declaration-order search | declaration block:;       KPADDPDObject* candidates = kpad->dpdState.candidates;;       KPADDPDObject* candidate;;       KPADDPDObject* object;;       KPADDPDObject* matchedCandidate;;       KPADDPDObject* source;;       f32 best = kp_err_near_pos * kp_err_near_pos;; start (0, 17); best (0, 17) after 36 builds; source restored; best order was:;     KPADDPDObject* candidates = kpad->dpdState.candidates;;     KPADDPDObject* candidate;;     KPADDPDObject* object;;     KPADDPDObject* matchedCandidate;;     KPADDPDObject* source;;     f32 best = kp_err_near_pos * kp_err_near_pos;; 
KPADInit | declaration-order search | declaration block:;       KPADInside* kpad;;       f32 distanceValue;;       f32 sensorDistance;;       f32 rotationElement;;       f32 referenceWidth;;       f32 referenceHeight;;       f32 objectInterval;;       f32 zero;;       f32 degreesToRadians;;       f32 one;;       f32* matrix;;       u32 i;;       s32 chan;;       BOOL enabled;; start (9, 81); improved (8, 70); improved (8, 67); improved (8, 58); improved (8, 54); improved (8, 51); best (8, 51) after 100 builds; kept in source:;     f32 referenceHeight;;     f32 objectInterval;;     f32 sensorDistance;;     f32 rotationElement;;     f32 referenceWidth;;     KPADInside* kpad;;     f32 distanceValue;;     f32 zero;;     f32 degreesToRadians;;     f32 one;;     u32 i;;     f32* matrix;;     s32 chan;;     BOOL enabled;; 
KPADRead | declaration-order search | declaration block:;       KPADInside* kpad = &inside_kpads[chan];;       s32 probe;;       BOOL interruptState;;       u32 available = 0;;       u32 ringCount;;       s32 start;;       s32 sampleIndex;;       u32 remaining;;       u32 remainingSamples;;       u32 buttons;;       u16 previousButtons;;       u32 changed;;       u32 extensionButtons;;       u32 coreButtons;;       u8 device;;       KPADSample latestSample;;       KPADSample* sample;;       KPADStatus* output;; start (11, 89); improved (11, 86); improved (11, 84); best (11, 84) after 100 builds; kept in source:;     KPADInside* kpad = &inside_kpads[chan];;     KPADStatus* output;;     BOOL interruptState;;     u32 available = 0;;     u32 ringCount;;     s32 start;;     s32 sampleIndex;;     u32 remaining;;     u32 remainingSamples;;     s32 probe;;     u16 previousButtons;;     u32 changed;;     u32 extensionButtons;;     u32 coreButtons;;     u8 device;;     KPADSample latestSample;;     KPADSample* sample;;     u32 buttons;; 
kbdProcMod | pass modifier expression directly | structural/exact (0, 4) insns 256/256 | restored
kbdProcMod | local modifier scope around inline setter | structural/exact (0, 4) insns 256/256 | restored
kbdProcMod | channel argument recovered from typed channel | structural/exact (14, 88) insns 259/256 | restored
KBDSetModState | read old union through typed field pointer | structural/exact (0, 7) insns 42/42 | restored
KBDSetModState | write new union through typed field pointer | structural/exact (0, 4) insns 42/42 | restored
KBDSetModState | reverse union temporary declaration order | structural/exact (0, 4) insns 42/42 | restored
kbd_led_handler | null callback test after clear; conditional error code | structural/exact (23, 21) insns 22/25 | restored
kbd_led_handler | guard completion body with non-null callback | structural/exact (24, 19) insns 23/25 | restored
KBDSetLedsAsync | unsigned indexed struct command loop | structural/exact (19, 72) insns 79/81 | restored
KBDSetLedsAsync | unsigned indexed loop and direct channel flags | structural/exact (19, 72) insns 79/81 | restored
KBDSetLedsAsync | unsigned counted byte offset with typed struct access | structural/exact (19, 72) insns 79/81 | restored
KBDSetLeds | unsigned indexed struct command loop | structural/exact (19, 68) insns 78/79 | restored
KBDSetLeds | unsigned indexed loop and direct flags access | structural/exact (19, 68) insns 78/79 | restored
KBDSetLeds | unsigned indexed loop; preserve allocated command pointer | structural/exact (22, 69) insns 78/79 | restored
KPADGetProjectionPos | inline double scale and target operand order | structural/exact (0, 10) insns 19/19 | restored
KPADGetProjectionPos | reuse height temporary and inline final scale | build failed c/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && "/usr/bin/python3" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d
### mwcceppc.exe Compiler:
#    File: libs\RVL_SDK\src\kpad\KPAD.c
# -------------------------------------
#     348:     f32 x = src->x * height; 
#   Error:     ^^^
#   (10141) expression syntax error
#   Too many errors printed, aborting program

User break, cancelled...
ninja: build stopped: subcommand failed.
 | restored
TMCJPEGDEC_IFD1_tag_parse | ignored planar configuration and contiguous EXIF tags | structural/exact (14, 226) insns 239/242 | restored
TMCJPEGDEC_IFD1_tag_parse | ignored EXIF tag range only | structural/exact (57, 219) insns 239/242 | restored
TMCJPEGDEC_IFD1_tag_parse | unsigned tag selector and ignored EXIF range | structural/exact (57, 219) insns 239/242 | restored
TMCJPEGDEC_IFD0_tag_parse | unsigned widened tag selector | structural/exact (27, 446) insns 481/481 | restored
TMCJPEGDEC_IFD0_tag_parse | signed widened tag selector | structural/exact (27, 446) insns 481/481 | restored
TMCJPEGDEC_IFD0_tag_parse | swap initial tag/type local declarations | structural/exact (29, 446) insns 481/481 | restored
TMCJPEGDEC_exif_parse | read helper boundary: standard 16-bit helper | structural/exact (0, 46) insns 212/212 | restored
TMCJPEGDEC_exif_parse | declare IFD cursor before offset | structural/exact (0, 46) insns 212/212 | restored
TMCJPEGDEC_exif_parse | reverse byte order expression operands | structural/exact (0, 46) insns 212/212 | restored
calc_acc_horizon | operand order of acceleration dot products | structural/exact (4, 37) insns 101/101 | restored
calc_acc_horizon | reuse blend for quadratic smoothing | structural/exact (2, 35) insns 101/101 | restored
calc_acc_horizon | declare magnitude after scalar intermediates | structural/exact (2, 34) insns 101/101 | restored
read_kpad_acc | stack frame local declaration order | structural/exact (32, 82) insns 400/400 | restored
read_kpad_acc | scalar smoothing: explicit pre-update delta | structural/exact (16, 66) insns 400/400 | restored
read_kpad_acc | extension stack local moved to function scope | structural/exact (16, 66) insns 400/400 | restored
select_1obj_first | offset scale operand order | structural/exact (2, 26) insns 109/109 | restored
select_1obj_first | end pointer declared before object cursor | structural/exact (4, 27) insns 109/109 | restored
select_1obj_first | candidate positions declared before coordinates | structural/exact (2, 26) insns 109/109 | restored
select_1obj_continue | offset distance first as target operands | structural/exact (0, 17) insns 93/93 | restored
select_1obj_continue | direction block local declarations before initializers | structural/exact (0, 16) insns 93/93 | restored
select_1obj_continue | inline tangent product intermediates | structural/exact (0, 19) insns 93/93 | restored
calc_dpd_variable | explicit absolute-distance branch | structural/exact (14, 45) insns 250/250 | restored
calc_dpd_variable | vector stack declaration order | structural/exact (40, 71) insns 250/250 | restored
calc_dpd_variable | reuse distance smoothing magnitude for final displacement | structural/exact (14, 43) insns 250/250 | restored
KPADRead | gravity structures declaration order | structural/exact (15, 93) insns 459/459 | restored
KPADRead | ring count clear and cursor calculation order | structural/exact (14, 89) insns 459/459 | restored
KPADRead | explicit sample selection branch | structural/exact (11, 97) insns 459/459 | restored
KPADInit | matrix base declaration order | structural/exact (9, 65) insns 185/185 | restored
KPADInit | sensor diagonal operand order | structural/exact (9, 81) insns 185/185 | restored
KPADInit | rotation temporary separated for sine and cosine | structural/exact (9, 81) insns 185/185 | restored
KPADiSamplingCallback | status pointer declared before index | structural/exact (2, 28) insns 182/182 | restored
KPADiSamplingCallback | device declared before channel state pointer | structural/exact (2, 28) insns 182/182 | restored
KPADiSamplingCallback | sensor diagonal temporary local order | structural/exact (3, 39) insns 182/182 | restored
KBDTranslateHidCode | declaration-order search | declaration block:;       KBDKeyMap* map;;       u16* table;;       u32 keyIndex;;       u16 entry;;       s32 mask;;       s32 offset;;       s32 group;;       u32 shiftFlag;;       u16 activeFlag;;   ;       if (kbdInitialized == FALSE) {; start (0, 9); improved (0, 3); improved (0, 2); best (0, 2) after 173 builds; kept in source:;     s32 mask;;     u16* table;;     u16 activeFlag;;     u16 entry;;     KBDKeyMap* map;;     s32 offset;;     s32 group;;     u32 shiftFlag;;     u32 keyIndex;; ;     if (kbdInitialized == FALSE) {; 
KBDTranslateHidCode | target bit-test operand order | structural/exact (0, 1) insns 164/164 | restored
KBDTranslateHidCode | both target bit-test operand orders | structural/exact (0, 0) insns 164/164 | kept
reset_kpad | initialized declarations followed by declaration search | declaration block:;       f32 upperY = 0.75f;;       f32 distanceValue;;       f32 zero = 0.0f;;       f32 sensorDistance = kpad->referenceDistance;;       f32 lowerY = -0.75f;;       f32 one = 1.0f;;       f32 negativeOne = -1.0f;;       KPADDPDObject* object;; start (0, 10); best (0, 10) after 71 builds; source restored; best order was:;     f32 upperY = 0.75f;;     f32 distanceValue;;     f32 zero = 0.0f;;     f32 sensorDistance = kpad->referenceDistance;;     f32 lowerY = -0.75f;;     f32 one = 1.0f;;     f32 negativeOne = -1.0f;;     KPADDPDObject* object;;  | restored no exact gain

KBDTranslateHidCode accepted after full clean gate --base 8e43db05. Exact objdiff 100%, ctxdiff 164/164 diffs 0; kbd instruction-exact 13->14/21, objdiff functions 14->15/21, code 2432->3088/5764, data 5296/5296. Pools identical, regressions 0, forbidden 0, readability 0, target DOL SHA1 preserved.
KBDSetModState | single expression merging old physical modifiers | structural/exact (3, 7) insns 42/42 | restored
KBDSetModState | reverse physical merge operands | structural/exact (3, 7) insns 42/42 | restored
KBDSetModState | assign physical field directly from stored state | structural/exact (0, 4) insns 42/42 | restored
kbdEventHandler | remove redundant report status temporary | structural/exact (0, 5) insns 186/186 | restored
kbdEventHandler | load status before computing channel pointer | structural/exact (0, 5) insns 186/186 | restored
KPADGetProjectionPos | name pixel aspect multiplier as local | structural/exact (0, 10) insns 19/19 | restored
KPADGetProjectionPos | name both screen geometry constants | structural/exact (7, 11) insns 19/19 | restored
KPADGetProjectionPos | vector intermediate for projection scaled components | structural/exact (7, 19) insns 23/19 | restored
read_kpad_acc | final declaration search | declaration block:;       Vec raw;;       Vec previous;; start (16, 66); best (16, 66) after 2 builds; source restored; best order was:;     Vec raw;;     Vec previous;;  
calc_dpd_variable | final declaration search | declaration block:;       Vec2 point;;       Vec2 delta;; start (14, 45); best (14, 45) after 2 builds; source restored; best order was:;     Vec2 point;;     Vec2 delta;;  
KPADiSamplingCallback | final declaration search | declaration block:;           u8 index = kpad->ringIndex;;           KPADSample* status;;           u32 tier;;           u32 enabled;;           u32 tableIndex;; start (2, 28); improved (0, 0); best (0, 0) after 6 builds; kept in source:;         u8 index = kpad->ringIndex;;         u32 tier;;         KPADSample* status;;         u32 enabled;;         u32 tableIndex;;  
KBDSetModState | final declaration search | declaration block:;           KBDModifierState oldState;;           KBDModifierState newState;;           interrupts = OSDisableInterrupts();; start (0, 4); best (0, 4) after 6 builds; source restored; best order was:;         KBDModifierState oldState;;         KBDModifierState newState;;         interrupts = OSDisableInterrupts();;  
TMCJPEGDEC_exif_parse | final declaration search | declaration block:;       u16 byteOrder;;       u32 ifdOffset;;       const u8* entries;;       u16 remaining;;       u16 count;;       s32 entriesSize;;       u16 index;; start (0, 46); improved (0, 43); best (0, 43) after 70 builds; kept in source:;     u16 byteOrder;;     u32 ifdOffset;;     const u8* entries;;     u16 remaining;;     u16 index;;     s32 entriesSize;;     u16 count;;  
kbdProcMod | register-only declaration search | declaration block:;       KBDChannel* data;;       u32 modState;;       s32 delta;;       u8 flags;;   ;       u32 finalState;;       s8 value;; start (0, 4); best (0, 4) after 52 builds; source restored; best order was:;     KBDChannel* data;;     u32 modState;;     s32 delta;;     u8 flags;; ;     u32 finalState;;     s8 value;;  | restored
KBDResetChannel | objdiff 100% and actual instructions identical. gate.py reports two cr1 branch differences because odiff.dis subtracts function position from the CR operand instead of the branch target; source untouched. This accounts for instruction-exact 13 versus objdiff-exact 14 at baseline, and 14 versus 15 after translation match.
KPADiSamplingCallback | accepted fresh full gate --base 8e43db05, objdiff 100%, ctxdiff 182/182 diffs 0. KPAD exact 18->19/29, matched code 5188->5916/13056, data 7912/8032 unchanged. Regressions 0, forbidden 0, readability 0, DOL SHA1 correct.
KPADInit | extract atomic object-interval update into a real inline helper before reset_kpad | 185/185 instructions, 81 differences unchanged; sdata2 order unchanged because MWCC emits helper constant at call | restored

Final audit: all 19 remaining functions have >=3 logged distinct source-level trials. Full clean combined gate over all three units PASS (--base 8e43db05), DOL SHA1 correct; no baseline or tooling edits. Independent comparison to starting HEAD report: 0 regressions, only KPAD and kbd_lib report measures changed. See sol-low-leaves-report.md for percentages, structural differences, and pre-existing cr1 normalization caveat.
