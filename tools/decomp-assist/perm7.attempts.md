# perm7 C permuter lane

Started 2026-10-02T21:46:38.083581+00:00; branch HEAD and fetched origin/main 255f3e05305939d73df73fcf9c4cd9044be9fa91.
Skills applied: unslop and coah-voice. Worker only; no delegation, pushes, PRs, or linking changes.
Both focused objects are current. pool_diff.py ran before code generation: both pools have zero narrow strings and are identical.

## Baseline main/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc
{"fuzzy_match_percent": 96.65468, "matched_code": "4168", "matched_code_percent": 8.716747, "matched_data": "144", "matched_data_percent": 26.865673, "matched_functions": 5, "matched_functions_percent": 62.5, "total_code": "47816", "total_data": "536", "total_functions": 8, "total_units": 1}
[{"name": "ZiMatchZHSpelling", "size": "484", "fuzzy": 98.80165}, {"name": "zi8InternalGetZH", "size": "42704", "fuzzy": 96.27482}, {"name": "Zi8GetElementCount", "size": "460", "fuzzy": 99.347824}]

## Baseline main/libs/RVL_SDK/src/kpad/KPAD
{"fuzzy_match_percent": 98.83119, "matched_code": "7880", "matched_code_percent": 60.355396, "matched_data": "8032", "matched_data_percent": 100.0, "matched_functions": 25, "matched_functions_percent": 86.206894, "total_code": "13056", "total_data": "8032", "total_functions": 29, "total_units": 1}
[{"name": "read_kpad_acc", "size": "1600", "fuzzy": 98.15}, {"name": "calc_dpd_variable", "size": "1000", "fuzzy": 94.82}, {"name": "KPADRead", "size": "1836", "fuzzy": 97.52723}, {"name": "KPADInit", "size": "740", "fuzzy": 96.51351}]

zi8InternalGetZH is excluded by the task. KPAD current mismatches are below the prompt estimates; measure them live rather than assuming register-only differences.
Setup: default Python lacks toml. Use a task venv under /tmp.

Fresh report regenerated with objdiff-cli. Baseline instruction-exact: KPAD 25/29; zi8cgetc 5/8. Baseline strict ctxdiffs saved under /tmp/perm7-baseline-<function>.ctx.

Setup uses actual Ninja GC/3.0a5.2 flags, wibo and sjiswrap, and MWCC -E preprocessing. Compile scripts retain every unit flag except dependency emission. Function directories are /tmp/perm-<function>. Context retains only the function, prototypes, types, global declarations, and required inline helpers. GNU PPC objdump is extracted under /tmp/perm7-tools. Noise mutation weights are zero; every hint requires a readable full-unit trial.

Fetched origin/main 580b79f40da87ad1bbb33fc53833ad927b95d58f immediately before starting Zi8GetElementCount and ZiMatchZHSpelling. Origin source is byte-identical to local baseline and both remain non-exact. Baseline permuter scores with --stack-diffs: 75 and 145. Isolated baseline instructions are identical to the full-unit instructions.

Started Zi8GetElementCount: PID 781074, one permuter job, 2026-10-02T21:51:06.321392+00:00. Stop after 45 minutes without a new best score.

Started ZiMatchZHSpelling: PID 781075, one permuter job, 2026-10-02T21:51:06.321996+00:00. Stop after 45 minutes without a new best score.
Zi8GetElementCount: permuter best None -> 75, elapsed 0.1 minutes.
ZiMatchZHSpelling: permuter best None -> 145, elapsed 0.1 minutes.

Initial quick full gate: GATE PASS, full build ok, correct DOL SHA1, zero regressions, zero forbidden patterns and readability warnings. KPAD 25/29, 7880/13056 code, 8032/8032 data; zi8cgetc 5/8, 4168/47816 code, 144/536 data.
KPAD normalized isolated/full instruction fidelity: KPADInit 0 differences; calc_dpd_variable and read_kpad_acc 0 differences after removing static only in the temporary standalone context to keep the unused target emitted. KPADRead has 2 relocation placeholder branch differences caused by absent earlier static definitions; full-unit results remain the acceptance authority. Baseline permuter scores: KPADInit 675, calc_dpd_variable 1735, read_kpad_acc 710, KPADRead 1023.
Zi8GetElementCount: permuter best 75 -> 0, elapsed 1.8 minutes.
Stopped Zi8GetElementCount: best 0, 110 seconds, exit 0.

Pre-trial origin/main check for Zi8GetElementCount: b2089fbdba45c16bdc30c7a4a2837550414f77fe, unit source identical to initial baseline; not already exact.

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "separate_count_initialization", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 108, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.478264, "instructions": [116, 115], "label": "count_initialized_declaration", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "scoped_saved_separator", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Pre-trial origin/main check for ZiMatchZHSpelling: b2089fbdba45c16bdc30c7a4a2837550414f77fe, unit source identical to initial baseline; not already exact.

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 30, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 97.19009, "instructions": [121, 121], "label": "candidate_length_before_result", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "word_count_unsigned", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Pre-permuter origin check for KPADInit: b2089fbdba45c16bdc30c7a4a2837550414f77fe, source unchanged from non-exact initial baseline.

Started KPADInit: PID 831720, one permuter job, 2026-10-02T21:55:35.672456+00:00. Stop after 45 minutes without a new best score.

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "result_after_buffer_declarations", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Pre-trial origin/main check for KPADInit: b2089fbdba45c16bdc30c7a4a2837550414f77fe, unit source identical to initial baseline; not already exact.
KPADInit: permuter best None -> 675, elapsed 0.1 minutes.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 82, "exact": false, "function": "KPADInit", "fuzzy": 96.48649, "instructions": [185, 185], "label": "matrix_before_scale_initialization", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}
KPADInit: permuter best 675 -> 435, elapsed 0.3 minutes.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 79, "exact": false, "function": "KPADInit", "fuzzy": 96.62162, "instructions": [185, 185], "label": "reference_height_before_width", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 80, "exact": false, "function": "KPADInit", "fuzzy": 96.567566, "instructions": [185, 185], "label": "direct_sine_assignment", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Pre-trial origin/main check for calc_dpd_variable: b2089fbdba45c16bdc30c7a4a2837550414f77fe, unit source identical to initial baseline; not already exact.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 43, "exact": false, "function": "calc_dpd_variable", "fuzzy": 94.88, "instructions": [250, 250], "label": "distance_product_order", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 40, "exact": false, "function": "calc_dpd_variable", "fuzzy": 94.712, "instructions": [250, 250], "label": "rotation_scalar_order", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 46, "exact": false, "function": "calc_dpd_variable", "fuzzy": 92.348, "instructions": [250, 250], "label": "candidate_scale_before_rotation", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Pre-trial origin/main check for read_kpad_acc: b2089fbdba45c16bdc30c7a4a2837550414f77fe, unit source identical to initial baseline; not already exact.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 66, "exact": false, "function": "read_kpad_acc", "fuzzy": 97.135, "instructions": [400, 400], "label": "extension_condition_positive", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 82, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.11, "instructions": [400, 400], "label": "declare_previous_before_raw", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 66, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.15, "instructions": [400, 400], "label": "unsigned_extension_rotation_test", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Pre-trial origin/main check for KPADRead: b2089fbdba45c16bdc30c7a4a2837550414f77fe, unit source identical to initial baseline; not already exact.

Zi8GetElementCount permuter scored zero after 110 seconds. Its only change is an empty `if (!elementCount) {}` inside the Latin scan. This is compiler noise and cannot be accepted. Removing it returns to the baseline 75 score; seek a meaningful equivalent source use instead. No source win was applied.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 284, "exact": false, "function": "KPADRead", "fuzzy": 94.503265, "instructions": [459, 459], "label": "copy_end_then_decrement", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Started Zi8GetElementCount: PID 844704, one permuter job, 2026-10-02T21:57:05.240658+00:00. Stop after 45 minutes without a new best score.
Zi8GetElementCount: permuter best None -> 0, elapsed 0.0 minutes.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 86, "exact": false, "function": "KPADRead", "fuzzy": 97.553375, "instructions": [459, 459], "label": "gravity_xy_product_order", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Stopped the just-started Zi8GetElementCount retry immediately to preserve the two-job total while ZiMatchZHSpelling and KPADInit are running. Keep its rejected empty-guard hint only as diagnostic evidence.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 89, "exact": false, "function": "KPADRead", "fuzzy": 97.52723, "instructions": [459, 459], "label": "sample_pointer_before_remaining", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}
Stopped Zi8GetElementCount: best 0, 15 seconds, exit 0.

Hint /tmp/perm-KPADInit/output-435-1/source.c
```diff
--- baseline
+++ /tmp/perm-KPADInit/output-435-1/source.c
@@ -1,8 +1,10 @@
 void KPADInit(void)
 {
   KPADInside *kpad;
+  int new_var;
   f32 distanceValue;
   f32 sensorDistance;
+  int new_var2;
   f32 rotationElement;
   f32 referenceWidth;
   f32 referenceHeight;
@@ -20,12 +22,13 @@
   chan = 0;
   one = 1.0f;
   zero = 0.0f;
+  new_var2 = 1;
   degreesToRadians = 0.017453292f;
   matrix = initial_rotation_matrix;
   kpad = inside_kpads;
   do
   {
-    kpad->dpdEnable = 1;
+    kpad->dpdEnable = new_var2;
     referenceWidth = 1.0f;
     kpad->dpdFormat = 0;
     referenceHeight = 0.75f;
@@ -56,9 +59,9 @@
     }
     referenceWidth = (referenceWidth < referenceHeight) ? (referenceWidth) : (referenceHeight);
     initial_rotation_matrix[0] = one;
-    matrix[1] = zero;
-    matrix[2] = zero;
-    matrix[3] = zero;
+    initial_rotation_matrix[new_var2] = zero;
+    initial_rotation_matrix[2] = zero;
+    initial_rotation_matrix[new_var = 3] = zero;
     kpad->sensorBarScale = sensorDistance / referenceWidth;
     kpad->value9C = zero;
     kpad->value94 = zero;
@@ -74,27 +77,27 @@
     kpad->repeatCount2 = 40000;
     kpad->repeatCurrent = 0;
     kpad->repeatCurrent2 = 40000;
-    kpad->sensorHeightPending = 1;
-    kpad->sensorBarPosition = 1;
+    kpad->sensorHeightPending = new_var2;
+    kpad->sensorBarPosition = new_var2;
     kpad->freeStyleAccelRotation = 0;
-    matrix[4] = zero;
+    initial_rotation_matrix[4] = zero;
     rotationElement = (f32) cos(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[5] = rotationElement;
+    initial_rotation_matrix[5] = rotationElement;
     rotationElement = (f32) (-sin(degreesToRadians * sensor_bar_angle_degrees));
-    matrix[7] = zero;
-    matrix[8] = zero;
-    matrix[6] = rotationElement;
+    initial_rotation_matrix[7] = zero;
+    initial_rotation_matrix[8] = zero;
+    initial_rotation_matrix[6] = rotationElement;
     rotationElement = (f32) sin(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[9] = rotationElement;
+    initial_rotation_matrix[9] = rotationElement;
     rotationElement = (f32) cos(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[10] = rotationElement;
-    matrix[11] = zero;
+    initial_rotation_matrix[10] = rotationElement;
+    initial_rotation_matrix[11] = zero;
     {
       i = 0;
       do
       {
         i++;
-        kpad->ringData[i - 1].error = -1;
+        kpad->ringData[i - new_var2].error = -new_var2;
       }
       while (i < 16);
     }
@@ -110,15 +113,15 @@
   kp_dist_vv1 = distanceValue;
   OSRestoreInterrupts(enabled);
   chan = 3;
-  kpad = &inside_kpads[3];
+  kpad = &inside_kpads[new_var];
   do
   {
-    if (WPADGetStatus() == 3)
+    if (WPADGetStatus() == new_var)
     {
       WPADControlMotor(chan, 0);
     }
     chan--;
-    kpad->flag51D = 1;
+    kpad->flag51D = new_var2;
     kpad--;
   }
   while (chan >= 0);
```

Hint /tmp/perm-KPADInit/output-435-2/source.c
```diff
--- baseline
+++ /tmp/perm-KPADInit/output-435-2/source.c
@@ -13,6 +13,7 @@
   f32 *matrix;
   u32 i;
   s32 chan;
+  double new_var;
   BOOL enabled;
   WPADInit();
   memset(inside_kpads, 0, 0x14A0);
@@ -21,7 +22,7 @@
   one = 1.0f;
   zero = 0.0f;
   degreesToRadians = 0.017453292f;
-  matrix = initial_rotation_matrix;
+  ;
   kpad = inside_kpads;
   do
   {
@@ -48,7 +49,11 @@
     distanceValue = kpad->sensorBarCenter.y;
     if (distanceValue < zero)
     {
-      referenceHeight += distanceValue;
+      do
+      {
+        referenceHeight += distanceValue;
+      }
+      while (0);
     }
     else
     {
@@ -56,9 +61,9 @@
     }
     referenceWidth = (referenceWidth < referenceHeight) ? (referenceWidth) : (referenceHeight);
     initial_rotation_matrix[0] = one;
-    matrix[1] = zero;
-    matrix[2] = zero;
-    matrix[3] = zero;
+    initial_rotation_matrix[1] = zero;
+    initial_rotation_matrix[2] = zero;
+    initial_rotation_matrix[3] = zero;
     kpad->sensorBarScale = sensorDistance / referenceWidth;
     kpad->value9C = zero;
     kpad->value94 = zero;
@@ -77,18 +82,19 @@
     kpad->sensorHeightPending = 1;
     kpad->sensorBarPosition = 1;
     kpad->freeStyleAccelRotation = 0;
-    matrix[4] = zero;
+    initial_rotation_matrix[4] = zero;
     rotationElement = (f32) cos(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[5] = rotationElement;
-    rotationElement = (f32) (-sin(degreesToRadians * sensor_bar_angle_degrees));
-    matrix[7] = zero;
-    matrix[8] = zero;
-    matrix[6] = rotationElement;
+    initial_rotation_matrix[5] = rotationElement;
+    new_var = sin(degreesToRadians * sensor_bar_angle_degrees);
+    rotationElement = (f32) (-new_var);
+    initial_rotation_matrix[7] = zero;
+    initial_rotation_matrix[8] = zero;
+    initial_rotation_matrix[6] = rotationElement;
     rotationElement = (f32) sin(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[9] = rotationElement;
+    initial_rotation_matrix[9] = rotationElement;
     rotationElement = (f32) cos(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[10] = rotationElement;
-    matrix[11] = zero;
+    initial_rotation_matrix[10] = rotationElement;
+    initial_rotation_matrix[11] = zero;
     {
       i = 0;
       do
@@ -113,7 +119,7 @@
   kpad = &inside_kpads[3];
   do
   {
-    if (WPADGetStatus() == 3)
+    if (inline_fn() == 3)
     {
       WPADControlMotor(chan, 0);
     }
```

Hint /tmp/perm-KPADInit/output-435-3/source.c
```diff
--- baseline
+++ /tmp/perm-KPADInit/output-435-3/source.c
@@ -12,7 +12,9 @@
   f32 one;
   f32 *matrix;
   u32 i;
+  KPADInside *new_var2;
   s32 chan;
+  double new_var;
   BOOL enabled;
   WPADInit();
   memset(inside_kpads, 0, 0x14A0);
@@ -21,15 +23,16 @@
   one = 1.0f;
   zero = 0.0f;
   degreesToRadians = 0.017453292f;
-  matrix = initial_rotation_matrix;
+  ;
   kpad = inside_kpads;
   do
   {
     kpad->dpdEnable = 1;
+    new_var2 = kpad;
     referenceWidth = 1.0f;
     kpad->dpdFormat = 0;
     referenceHeight = 0.75f;
-    kpad->status.dev_type = 0xFD;
+    new_var2->status.dev_type = 0xFD;
     kpad->status.data_format = 0;
     kpad->referenceDistance = idist_org;
     kpad->accelNormal = iaccXY_nrm_hori;
@@ -48,7 +51,11 @@
     distanceValue = kpad->sensorBarCenter.y;
     if (distanceValue < zero)
     {
-      referenceHeight += distanceValue;
+      do
+      {
+        referenceHeight += distanceValue;
+      }
+      while (0);
     }
     else
     {
@@ -56,9 +63,9 @@
     }
     referenceWidth = (referenceWidth < referenceHeight) ? (referenceWidth) : (referenceHeight);
     initial_rotation_matrix[0] = one;
-    matrix[1] = zero;
-    matrix[2] = zero;
-    matrix[3] = zero;
+    initial_rotation_matrix[1] = zero;
+    initial_rotation_matrix[2] = zero;
+    initial_rotation_matrix[3] = zero;
     kpad->sensorBarScale = sensorDistance / referenceWidth;
     kpad->value9C = zero;
     kpad->value94 = zero;
@@ -77,18 +84,19 @@
     kpad->sensorHeightPending = 1;
     kpad->sensorBarPosition = 1;
     kpad->freeStyleAccelRotation = 0;
-    matrix[4] = zero;
+    initial_rotation_matrix[4] = zero;
     rotationElement = (f32) cos(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[5] = rotationElement;
-    rotationElement = (f32) (-sin(degreesToRadians * sensor_bar_angle_degrees));
-    matrix[7] = zero;
-    matrix[8] = zero;
-    matrix[6] = rotationElement;
+    initial_rotation_matrix[5] = rotationElement;
+    new_var = sin(degreesToRadians * sensor_bar_angle_degrees);
+    rotationElement = (f32) (-new_var);
+    initial_rotation_matrix[7] = zero;
+    initial_rotation_matrix[8] = zero;
+    initial_rotation_matrix[6] = rotationElement;
     rotationElement = (f32) sin(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[9] = rotationElement;
+    initial_rotation_matrix[9] = rotationElement;
     rotationElement = (f32) cos(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[10] = rotationElement;
-    matrix[11] = zero;
+    initial_rotation_matrix[10] = rotationElement;
+    initial_rotation_matrix[11] = zero;
     {
       i = 0;
       do
@@ -113,7 +121,7 @@
   kpad = &inside_kpads[3];
   do
   {
-    if (WPADGetStatus() == 3)
+    if (inline_fn() == 3)
     {
       WPADControlMotor(chan, 0);
     }
```

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "postincrement_count", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "postincrement_cursors", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "separate_latin_conditions", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.391304, "instructions": [115, 115], "label": "signed_result_count", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.391304, "instructions": [115, 115], "label": "source_count_unsigned", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 58, "exact": false, "function": "KPADInit", "fuzzy": 97.810814, "instructions": [185, 185], "label": "direct_matrix_array", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "reference_dimensions_scoped", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 136, "exact": false, "function": "KPADInit", "fuzzy": 92.183784, "instructions": [183, 185], "label": "local_rotation_angle", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

KPADRead standalone/full text bytes are identical. The earlier two strict ctxdiff discrepancies are odiff.py misreading the first operand of `beq cr1,target` as a branch address, making its output depend on the function address. GNU objdump with actual branch operands confirms identical relative branches. No compiler-context difference is involved. Full-unit ctxdiff is still required for acceptance.
ZiMatchZHSpelling: permuter best 145 -> 105, elapsed 13.2 minutes.

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "element_length_parameter", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "remaining_characters_parameter", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "named_element_result", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "named_element_cursors", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "prefix_length_parameter", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "remaining_phonetic_parameter", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "word_prefix_parameter_names", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Hint /tmp/perm-ZiMatchZHSpelling/output-105-1/source.c
```diff
--- baseline
+++ /tmp/perm-ZiMatchZHSpelling/output-105-1/source.c
@@ -17,6 +17,9 @@
   {
     if ((!candidate[index]) || (candidate[index] != spelling[index]))
     {
+      if (__zi8_work_data)
+      {
+      }
       matches = 0;
       break;
     }
```

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "named_spelling_locals", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

ZiMatchZHSpelling best 105 hint is another empty conditional, `if (__zi8_work_data) {}` inside the mismatch branch. It is rejected as source noise. No changes were kept. Zi8GetElementCount meaningful increment, condition, integer type, and parameter/local naming trials all failed to reach 100%. KPADInit direct global matrix indexing is a readable interpretation of the 435 hint; full-unit trial improved fuzzy to 97.810814% but has 58 ctxdiff differences and unchanged exact bytes. It is restored pending an exact result.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 302, "exact": false, "function": "read_kpad_acc", "fuzzy": 92.2375, "instructions": [394, 400], "label": "smooth_absolute_distance_in_place", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 63, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.2375, "instructions": [400, 400], "label": "smooth_distance_before_factor_product", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 293, "exact": false, "function": "read_kpad_acc", "fuzzy": 95.665, "instructions": [394, 400], "label": "smooth_previous_acceleration_value", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 62, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.2, "instructions": [400, 400], "label": "smooth_absolute_distance_explicit_branches", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 226, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.11, "instructions": [399, 400], "label": "extension_all_positive", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 226, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.11, "instructions": [399, 400], "label": "extension_nested_positive", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 227, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.0875, "instructions": [401, 400], "label": "extension_format_switch", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 63, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.3625, "instructions": [400, 400], "label": "extension_nested_switch", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 284, "exact": false, "function": "KPADRead", "fuzzy": 94.503265, "instructions": [459, 459], "label": "copy_cursor_pointer_subtraction", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 283, "exact": false, "function": "KPADRead", "fuzzy": 94.91503, "instructions": [459, 459], "label": "copy_cursor_before_ring_index", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 83, "exact": false, "function": "KPADRead", "fuzzy": 97.57952, "instructions": [459, 459], "label": "both_gravity_xy_product_order", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 164, "exact": false, "function": "KPADRead", "fuzzy": 97.22222, "instructions": [460, 459], "label": "button_masks_in_steps", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 89, "exact": false, "function": "KPADRead", "fuzzy": 97.54902, "instructions": [459, 459], "label": "changed_buttons_new_first", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}
KPADInit: permuter best 435 -> 420, elapsed 23.7 minutes.

Concurrency correction: the short Zi8GetElementCount retry overlapped the two current searches for 15 seconds, briefly exceeding the two-job cap. It was stopped as soon as detected. /tmp/perm7-queue.py checks only this lane's running permuter processes and keeps all subsequent searches at two one-job processes or fewer.

Hint /tmp/perm-KPADInit/output-420-1/source.c
```diff
--- baseline
+++ /tmp/perm-KPADInit/output-420-1/source.c
@@ -3,10 +3,11 @@
   KPADInside *kpad;
   f32 distanceValue;
   f32 sensorDistance;
+  int new_var;
   f32 rotationElement;
   f32 referenceWidth;
+  f32 objectInterval;
   f32 referenceHeight;
-  f32 objectInterval;
   f32 zero;
   f32 degreesToRadians;
   f32 one;
@@ -21,7 +22,7 @@
   one = 1.0f;
   zero = 0.0f;
   degreesToRadians = 0.017453292f;
-  matrix = initial_rotation_matrix;
+  ;
   kpad = inside_kpads;
   do
   {
@@ -56,9 +57,9 @@
     }
     referenceWidth = (referenceWidth < referenceHeight) ? (referenceWidth) : (referenceHeight);
     initial_rotation_matrix[0] = one;
-    matrix[1] = zero;
-    matrix[2] = zero;
-    matrix[3] = zero;
+    initial_rotation_matrix[1] = zero;
+    initial_rotation_matrix[2] = zero;
+    initial_rotation_matrix[3] = zero;
     kpad->sensorBarScale = sensorDistance / referenceWidth;
     kpad->value9C = zero;
     kpad->value94 = zero;
@@ -77,24 +78,24 @@
     kpad->sensorHeightPending = 1;
     kpad->sensorBarPosition = 1;
     kpad->freeStyleAccelRotation = 0;
-    matrix[4] = zero;
+    initial_rotation_matrix[4] = zero;
     rotationElement = (f32) cos(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[5] = rotationElement;
+    initial_rotation_matrix[5] = rotationElement;
     rotationElement = (f32) (-sin(degreesToRadians * sensor_bar_angle_degrees));
-    matrix[7] = zero;
-    matrix[8] = zero;
-    matrix[6] = rotationElement;
+    initial_rotation_matrix[7] = zero;
+    initial_rotation_matrix[8] = zero;
+    initial_rotation_matrix[6] = rotationElement;
     rotationElement = (f32) sin(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[9] = rotationElement;
+    initial_rotation_matrix[9] = rotationElement;
     rotationElement = (f32) cos(degreesToRadians * sensor_bar_angle_degrees);
-    matrix[10] = rotationElement;
-    matrix[11] = zero;
+    initial_rotation_matrix[10] = rotationElement;
+    initial_rotation_matrix[11] = zero;
     {
       i = 0;
       do
       {
         i++;
-        kpad->ringData[i - 1].error = -1;
+        kpad->ringData[i - 1].error = (new_var = -1);
       }
       while (i < 16);
     }
```

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 56, "exact": false, "function": "KPADInit", "fuzzy": 97.91892, "instructions": [185, 185], "label": "direct_matrix_reference_height_first", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 162, "exact": false, "function": "KPADInit", "fuzzy": 84.4054, "instructions": [197, 185], "label": "direct_matrix_ring_sample_cursor", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "7912", "diffs": 63, "exact": false, "function": "KPADInit", "fuzzy": 97.675674, "instructions": [185, 185], "label": "direct_matrix_constant_scalars", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 55, "exact": false, "function": "KPADInit", "fuzzy": 97.89189, "instructions": [185, 185], "label": "direct_matrix_object_interval_declaration", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 108, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.391304, "instructions": [116, 115], "label": "reuse_count_parameter", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 108, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.08696, "instructions": [116, 115], "label": "reuse_count_after_cursors", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 108, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.08696, "instructions": [116, 115], "label": "reuse_count_before_saved_separator", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Prepared calc_dpd_variable with 384 manual source combinations: four sum/operand forms for each rotation coordinate and all 24 orders of the four independent scalar initializations. PERM_RANDOMIZE adds normal local mutations. Empty conditional, global type, function type, internal volatile type, synthetic block, duplicate-assignment and statement-deletion mutations are disabled for this search. All macros remain outside the repository.

calc_dpd_variable preflight passed after flattening nested PERM_GENERAL arguments within each PERM_LINESWAP statement. The 384-base search parses and compiles; base score remains 1735 with --stack-diffs.
The queued read_kpad_acc and KPADRead searches also disable empty conditions, synthetic blocks, volatile type mutations, external/function type changes, duplicate assignments and statement deletion.

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 56, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 92.17391, "instructions": [115, 115], "label": "character_guard_then_bound", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 53, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 94.04348, "instructions": [115, 115], "label": "bound_guard_then_characters", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "forward_for_with_spaced_increment", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 55, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.347824, "instructions": [116, 115], "label": "spaced_cursor_continue", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}
Stopped ZiMatchZHSpelling: best 105, 3491 seconds, exit 0.

Pre-permuter origin check Zi8GetElementCount: 813660b96efe6fa4a5e918d8c21cc4e4c52c4e30; full unit source still identical to the non-exact initial baseline. Started PID 1360619, one job, 2026-10-02T22:49:20.093632+00:00.
Zi8GetElementCount: permuter best None -> 75, elapsed 0.1 minutes.
Zi8GetElementCount: permuter best 75 -> 0, elapsed 1.2 minutes.
Stopped Zi8GetElementCount: best 0, 72 seconds, exit 0.

Pre-permuter origin check calc_dpd_variable: ac8d46d2317ec58e48d9010a46535bd7861b5256; full unit source still identical to the non-exact initial baseline. Started PID 1373652, one job, 2026-10-02T22:50:32.664433+00:00.
calc_dpd_variable: permuter best None -> 1195, elapsed 0.1 minutes.
calc_dpd_variable: permuter best 1195 -> 1065, elapsed 0.6 minutes.
calc_dpd_variable: permuter best 1065 -> 1025, elapsed 0.8 minutes.
calc_dpd_variable: permuter best 1025 -> 1005, elapsed 0.8 minutes.
calc_dpd_variable: permuter best 1005 -> 710, elapsed 2.6 minutes.
calc_dpd_variable: permuter best 710 -> 570, elapsed 2.6 minutes.

Zero-score hint /tmp/perm-Zi8GetElementCount/output-0-1/source.c
```diff
--- baseline
+++ /tmp/perm-Zi8GetElementCount/output-0-1/source.c
@@ -38,6 +38,9 @@
       {
         goto next_spaced_element;
       }
+      if (elementCount)
+      {
+      }
     }
     else
       if ((spacedElements[spacedIndex] >= 0xF331) && (spacedElements[spacedIndex] <= 0xF335))
```
calc_dpd_variable: permuter best 570 -> 545, elapsed 3.7 minutes.

Hint /tmp/perm-calc_dpd_variable/output-545-1
```diff
--- baseline
+++ /tmp/perm-calc_dpd_variable/output-545-1
@@ -40,7 +40,8 @@
       delta.x /= length;
       delta.y /= length;
       kpad->status.hori_vec.x = delta.x - kpad->status.horizon.x;
-      kpad->status.hori_vec.y = delta.y - kpad->status.horizon.y;
+      kpad->status.hori_vec.y = delta.y;
+      kpad->status.hori_vec.y = kpad->status.hori_vec.y - kpad->status.horizon.y;
       kpad->status.hori_speed = (f32) sqrt((kpad->status.hori_vec.x * kpad->status.hori_vec.x) + (kpad->status.hori_vec.y * kpad->status.hori_vec.y));
       kpad->status.horizon = delta;
     }
@@ -84,10 +85,10 @@
     }
   }
   {
-    f32 rotatedX = (kpad->horizonTangent.x * kpad->dpdObjectDirection.x) + (kpad->horizonTangent.y * kpad->dpdObjectDirection.y);
+    f32 scaleY = 0.5f * (kpad->dpdState.candidates[0].y + kpad->dpdState.candidates[1].y);
+    f32 rotatedX = (kpad->dpdObjectDirection.y * kpad->horizonTangent.y) + (kpad->dpdObjectDirection.x * kpad->horizonTangent.x);
+    f32 scaleX = 0.5f * (kpad->dpdState.candidates[0].x + kpad->dpdState.candidates[1].x);
     f32 rotatedY = ((-kpad->dpdObjectDirection.y) * kpad->horizonTangent.x) + (kpad->dpdObjectDirection.x * kpad->horizonTangent.y);
-    f32 scaleX = 0.5f * (kpad->dpdState.candidates[0].x + kpad->dpdState.candidates[1].x);
-    f32 scaleY = 0.5f * (kpad->dpdState.candidates[0].y + kpad->dpdState.candidates[1].y);
     delta.x = kpad->sensorBarScale * (kpad->sensorBarCenter.x - ((rotatedX * scaleX) - (rotatedY * scaleY)));
     delta.y = kpad->sensorBarScale * (kpad->sensorBarCenter.y - ((rotatedY * scaleX) + (rotatedX * scaleY)));
     point.x = ((-kpad->accelNormal.y) * delta.x) + (kpad->accelNormal.x * delta.y);
```

Zi8GetElementCount retry again scored zero after 72 seconds by adding an empty `if (elementCount) {}`. The responsible pass is perm_refer_to_var, which inserts a reference as an empty conditional, independent of perm_var_cond_block. This hint is rejected. Disabled perm_refer_to_var for the next element-count retry and both queued KPAD searches.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 39, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.908, "instructions": [250, 250], "label": "permuter545_scalar_order", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 39, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.908, "instructions": [250, 250], "label": "permuter545_horizon_difference_steps", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 50, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.568, "instructions": [250, 250], "label": "permuter545_named_horizon_difference", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}
calc_dpd_variable: permuter best 545 -> 530, elapsed 10.3 minutes.

Score530 hint compared to score545:
```diff
--- score545
+++ score530
@@ -1,5 +1,6 @@
 {
   Vec2 point;
+  f32 new_var;
   Vec2 delta;
   if (valid == 0)
   {
@@ -39,9 +40,8 @@
       delta.x /= length;
       delta.y /= length;
       kpad->status.hori_vec.x = delta.x - kpad->status.horizon.x;
-      kpad->status.hori_vec.y = delta.y;
-      kpad->status.hori_vec.y = kpad->status.hori_vec.y - kpad->status.horizon.y;
-      kpad->status.hori_speed = (f32) sqrt((kpad->status.hori_vec.x * kpad->status.hori_vec.x) + (kpad->status.hori_vec.y * kpad->status.hori_vec.y));
+      kpad->status.hori_vec.y = delta.y - kpad->status.horizon.y;
+      kpad->status.hori_speed = (f32) sqrt((kpad->status.hori_vec.x * kpad->status.hori_vec.x) + ((new_var = kpad->status.hori_vec.y) * new_var));
       kpad->status.horizon = delta;
     }
   }
@@ -85,7 +85,7 @@
   }
   {
     f32 scaleY = 0.5f * (kpad->dpdState.candidates[0].y + kpad->dpdState.candidates[1].y);
-    f32 rotatedX = (kpad->dpdObjectDirection.y * kpad->horizonTangent.y) + (kpad->dpdObjectDirection.x * kpad->horizonTangent.x);
+    f32 rotatedX = (kpad->dpdObjectDirection.x * kpad->horizonTangent.x) + (kpad->dpdObjectDirection.y * kpad->horizonTangent.y);
     f32 scaleX = 0.5f * (kpad->dpdState.candidates[0].x + kpad->dpdState.candidates[1].x);
     f32 rotatedY = ((-kpad->dpdObjectDirection.y) * kpad->horizonTangent.x) + (kpad->dpdObjectDirection.x * kpad->horizonTangent.y);
     delta.x = kpad->sensorBarScale * (kpad->sensorBarCenter.x - ((rotatedX * scaleX) - (rotatedY * scaleY)));

```

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 37, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.968, "instructions": [250, 250], "label": "permuter530_scalar_order", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 37, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.968, "instructions": [250, 250], "label": "permuter530_named_horizon_y", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}
Stopped KPADInit: best 420, 4121 seconds, exit 0.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 37, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.968, "instructions": [250, 250], "label": "permuter530_named_horizon_components", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Pre-permuter origin check read_kpad_acc: 5a222cdec4785d87b8b3686d2d4397b970e278f6; full unit source still identical to the non-exact initial baseline. Started PID 1491731, one job, 2026-10-02T23:04:20.918085+00:00.
read_kpad_acc: permuter best None -> 710, elapsed 0.1 minutes.

- Source attempt {"build": 0, "code": "4168", "data": "96", "diffs": 110, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 88.434784, "instructions": [115, 115], "label": "named_latin_element", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 17, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.17391, "instructions": [115, 115], "label": "bound_on_left", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 17, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.17391, "instructions": [115, 115], "label": "bound_on_left_and_separator_first", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 41, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 94.73913, "instructions": [119, 115], "label": "result_in_saved_state", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 112, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 86.608696, "instructions": [113, 115], "label": "named_spaced_element", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 106, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.48695, "instructions": [113, 115], "label": "plain_saved_separator", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 108, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.89565, "instructions": [116, 115], "label": "element_count_local_limit", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "result_array_then_cursors", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Checkpoint 2026-10-02T23:07:04.919951+00:00: distinct readable source trials so far: {"KPADInit": 10, "KPADRead": 8, "Zi8GetElementCount": 27, "ZiMatchZHSpelling": 7, "calc_dpd_variable": 9, "read_kpad_acc": 11}. No exact readable candidate retained. Permuter runs continue, with at most two one-job processes.
calc_dpd_variable: permuter best 530 -> 505, elapsed 18.6 minutes.

Prepared final Zi retries with empty variable references, duplicated stores, structural removal, and type randomization disabled. These searches start only after the original queue has dispatched its last KPAD function, leaving its pending list empty.

Score505 hint compared to score530:
```diff
--- score530
+++ score505
@@ -1,7 +1,7 @@
 {
   Vec2 point;
-  f32 new_var;
   Vec2 delta;
+  float new_var;
   if (valid == 0)
   {
     kpad->status.dpd_valid_fg = 0;
@@ -29,7 +29,8 @@
       }
       else
       {
-        amount = length / kpad->value8C;
+        amount = length;
+        amount = amount / kpad->value8C;
         amount *= amount;
         amount *= amount;
       }
@@ -41,7 +42,7 @@
       delta.y /= length;
       kpad->status.hori_vec.x = delta.x - kpad->status.horizon.x;
       kpad->status.hori_vec.y = delta.y - kpad->status.horizon.y;
-      kpad->status.hori_speed = (f32) sqrt((kpad->status.hori_vec.x * kpad->status.hori_vec.x) + ((new_var = kpad->status.hori_vec.y) * new_var));
+      kpad->status.hori_speed = (f32) sqrt((kpad->status.hori_vec.x * kpad->status.hori_vec.x) + (kpad->status.hori_vec.y * kpad->status.hori_vec.y));
       kpad->status.horizon = delta;
     }
   }
@@ -83,10 +84,11 @@
       kpad->status.dist += kpad->status.dist_vec;
     }
   }
+  new_var = 0.5f;
   {
-    f32 scaleY = 0.5f * (kpad->dpdState.candidates[0].y + kpad->dpdState.candidates[1].y);
+    f32 scaleX = 0.5f * (kpad->dpdState.candidates[0].x + kpad->dpdState.candidates[1].x);
+    f32 scaleY = new_var * (kpad->dpdState.candidates[0].y + kpad->dpdState.candidates[1].y);
     f32 rotatedX = (kpad->dpdObjectDirection.x * kpad->horizonTangent.x) + (kpad->dpdObjectDirection.y * kpad->horizonTangent.y);
-    f32 scaleX = 0.5f * (kpad->dpdState.candidates[0].x + kpad->dpdState.candidates[1].x);
     f32 rotatedY = ((-kpad->dpdObjectDirection.y) * kpad->horizonTangent.x) + (kpad->dpdObjectDirection.x * kpad->horizonTangent.y);
     delta.x = kpad->sensorBarScale * (kpad->sensorBarCenter.x - ((rotatedX * scaleX) - (rotatedY * scaleY)));
     delta.y = kpad->sensorBarScale * (kpad->sensorBarCenter.y - ((rotatedY * scaleX) + (rotatedX * scaleY)));

```

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 23, "exact": false, "function": "calc_dpd_variable", "fuzzy": 95.332, "instructions": [250, 250], "label": "permuter505_scale_order", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 23, "exact": false, "function": "calc_dpd_variable", "fuzzy": 95.332, "instructions": [250, 250], "label": "permuter505_normalize_amount_steps", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 17, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.9, "instructions": [250, 250], "label": "permuter505_shared_midpoint_factor", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 23, "exact": false, "function": "calc_dpd_variable", "fuzzy": 95.332, "instructions": [250, 250], "label": "permuter505_midpoint_factor_last", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 17, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.9, "instructions": [250, 250], "label": "permuter505_shared_midpoint_context", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 15, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.96, "instructions": [250, 250], "label": "midpoint_distance_scale_in_place", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 35, "exact": false, "function": "calc_dpd_variable", "fuzzy": 96.688, "instructions": [250, 250], "label": "midpoint_delta_y_first", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 33, "exact": false, "function": "calc_dpd_variable", "fuzzy": 96.748, "instructions": [250, 250], "label": "midpoint_distance_scale_and_y_first", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 25, "exact": false, "function": "calc_dpd_variable", "fuzzy": 96.964, "instructions": [250, 250], "label": "midpoint_point_y_first", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "3548", "data": "72", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.391304, "instructions": [115, 115], "label": "const_element_limit", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 115, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 92.78261, "instructions": [118, 115], "label": "separate_scoped_latin_index", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "96", "diffs": 44, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.73913, "instructions": [115, 115], "label": "separate_latin_index_at_function_scope", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 15, "exact": false, "function": "calc_dpd_variable", "fuzzy": 97.96, "instructions": [250, 250], "label": "midpoint_distance_absolute_branches", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 4, "exact": false, "function": "calc_dpd_variable", "fuzzy": 99.92, "instructions": [250, 250], "label": "midpoint_named_transformed_coordinates", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 31, "exact": false, "function": "calc_dpd_variable", "fuzzy": 96.52, "instructions": [250, 250], "label": "midpoint_named_transformed_y_first", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 101, "exact": false, "function": "calc_dpd_variable", "fuzzy": 98.984, "instructions": [252, 250], "label": "midpoint_transformed_vector", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 4, "exact": false, "function": "calc_dpd_variable", "fuzzy": 99.92, "instructions": [250, 250], "label": "midpoint_reuse_transformed_point", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 0, "exact": true, "function": "calc_dpd_variable", "fuzzy": 100.0, "instructions": [250, 250], "label": "transformed_compound_distance_division", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "win": "/tmp/perm7-win-calc_dpd_variable-transformed_compound_distance_division.c"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 7, "exact": false, "function": "calc_dpd_variable", "fuzzy": 99.86, "instructions": [250, 250], "label": "transformed_distance_value_reuse", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 4, "exact": false, "function": "calc_dpd_variable", "fuzzy": 99.92, "instructions": [250, 250], "label": "transformed_named_distance_weight", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 4, "exact": false, "function": "calc_dpd_variable", "fuzzy": 99.92, "instructions": [250, 250], "label": "transformed_named_distance_terms", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 4, "exact": false, "function": "calc_dpd_variable", "fuzzy": 99.92, "instructions": [250, 250], "label": "transformed_distance_float_type", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Readable calc_dpd_variable candidate reached objdiff100.0 and ctxdiff0, 250/250 instructions, code8880/13056, data8032/8032. The score505 hint led to shared midpoint factor and separate transformed coordinates; compound distance division resolved the last four FPR differences. Candidate is awaiting a clean full gate. Stopping its obsolete baseline permuter process to release a job.
```diff
--- KPAD.c baseline
+++ KPAD.c candidate
@@ -912,7 +912,8 @@
             if (length >= kpad->value8C) {
                 amount = 1.0f;
             } else {
-                amount = length / kpad->value8C;
+                amount = length;
+                amount /= kpad->value8C;
                 amount *= amount;
                 amount *= amount;
             }
@@ -939,15 +940,20 @@
             f32 dx;
             f32 next;
             dx = value - kpad->status.dist;
-            magnitude = dx < 0.0f ? -dx : dx;
+            if (dx < 0.0f) {
+                magnitude = -dx;
+            } else {
+                magnitude = dx;
+            }
             if (magnitude >= kpad->value94) {
                 magnitude = 1.0f;
             } else {
-                magnitude = magnitude / kpad->value94;
+                magnitude /= kpad->value94;
                 magnitude *= magnitude;
                 magnitude *= magnitude;
             }
-            next = magnitude * kpad->value98 * dx;
+            magnitude *= kpad->value98;
+            next = magnitude * dx;
             kpad->status.dist_vec = next;
             if (next < 0.0f) {
                 kpad->status.dist_speed = -next;
@@ -958,12 +964,15 @@
         }
     }
     {
-        f32 rotatedX = kpad->horizonTangent.x * kpad->dpdObjectDirection.x + kpad->horizonTangent.y * kpad->dpdObjectDirection.y;
+        f32 midpointFactor = 0.5f;
+        f32 scaleX = midpointFactor * (kpad->dpdState.candidates[0].x + kpad->dpdState.candidates[1].x);
+        f32 scaleY = midpointFactor * (kpad->dpdState.candidates[0].y + kpad->dpdState.candidates[1].y);
+        f32 rotatedX = kpad->dpdObjectDirection.x * kpad->horizonTangent.x + kpad->dpdObjectDirection.y * kpad->horizonTangent.y;
         f32 rotatedY = -kpad->dpdObjectDirection.y * kpad->horizonTangent.x + kpad->dpdObjectDirection.x * kpad->horizonTangent.y;
-        f32 scaleX = 0.5f * (kpad->dpdState.candidates[0].x + kpad->dpdState.candidates[1].x);
-        f32 scaleY = 0.5f * (kpad->dpdState.candidates[0].y + kpad->dpdState.candidates[1].y);
-        delta.x = kpad->sensorBarScale * (kpad->sensorBarCenter.x - (rotatedX * scaleX - rotatedY * scaleY));
-        delta.y = kpad->sensorBarScale * (kpad->sensorBarCenter.y - (rotatedY * scaleX + rotatedX * scaleY));
+        f32 transformedX = rotatedX * scaleX - rotatedY * scaleY;
+        f32 transformedY = rotatedY * scaleX + rotatedX * scaleY;
+        delta.x = kpad->sensorBarScale * (kpad->sensorBarCenter.x - transformedX);
+        delta.y = kpad->sensorBarScale * (kpad->sensorBarCenter.y - transformedY);
         point.x = -kpad->accelNormal.y * delta.x + kpad->accelNormal.x * delta.y;
         point.y = -kpad->accelNormal.x * delta.x - kpad->accelNormal.y * delta.y;
         if (kpad->status.dpd_valid_fg == 0) {

```
Stopped calc_dpd_variable: best 505, 2126 seconds, exit 0.

Pre-permuter origin check KPADRead: b26e248bb0e08308371ff5f23c7c49b705e955ca; full unit source still identical to the non-exact initial baseline. Started PID 1704570, one job, 2026-10-02T23:25:58.596858+00:00.
KPADRead: permuter best None -> 1023, elapsed 0.1 minutes.
KPADRead: permuter best 1023 -> 1008, elapsed 0.3 minutes.

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 0, "exact": true, "function": "calc_dpd_variable", "fuzzy": 100.0, "instructions": [250, 250], "label": "exact_restore_horizon_division", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "win": "/tmp/perm7-win-calc_dpd_variable-exact_restore_horizon_division.c"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 4, "exact": false, "function": "calc_dpd_variable", "fuzzy": 99.92, "instructions": [250, 250], "label": "exact_restore_absolute_ternary", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}
read_kpad_acc: permuter best 710 -> 670, elapsed 22.6 minutes.

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 4, "exact": false, "function": "calc_dpd_variable", "fuzzy": 99.92, "instructions": [250, 250], "label": "exact_restore_both_simple_forms", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "7880", "data": "8032", "diffs": 18, "exact": false, "function": "calc_dpd_variable", "fuzzy": 96.48, "instructions": [250, 250], "label": "exact_direct_midpoint_literals", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Applied the smaller exact calc_dpd_variable candidate: restored the original one-line horizon division; explicit distance absolute branches, compound distance division, shared midpoint factor, and transformed coordinate temporaries remain necessary for 100.0/ctxdiff0. Starting a clean full gate over both owned units before committing.

read_kpad_acc score670 hint:
```diff
--- read_kpad_acc baseline
+++ 670
@@ -1,4 +1,6 @@
 {
+  f32 *new_var;
+  f32 new_var2;
   Vec raw;
   Vec previous;
   switch (status->dataFormat)
@@ -25,8 +27,9 @@
   kpad->acceleration.y = clamp_acc_value(((f32) (-((s32) status->accZ))) * kpad->value4E4, kp_rm_acc_max);
   kpad->acceleration.z = clamp_acc_value(((f32) status->accY) * kpad->value4E0, kp_rm_acc_max);
   previous = kpad->status.acc;
+  new_var = &kpad->acceleration.y;
   smooth_acc_value(kpad, kpad->acceleration.x, &kpad->status.acc.x);
-  smooth_acc_value(kpad, kpad->acceleration.y, &kpad->status.acc.y);
+  smooth_acc_value(kpad, *new_var, &kpad->status.acc.y);
   smooth_acc_value(kpad, kpad->acceleration.z, &kpad->status.acc.z);
   kpad->status.acc_value = (f32) sqrt((kpad->status.acc.z * kpad->status.acc.z) + ((kpad->status.acc.x * kpad->status.acc.x) + (kpad->status.acc.y * kpad->status.acc.y)));
   previous.x -= kpad->status.acc.x;
@@ -55,8 +58,9 @@
     extensionPrevious = kpad->status.ex_status.fs.acc;
     smooth_acc_value(kpad, raw.x, &kpad->status.ex_status.fs.acc.x);
     smooth_acc_value(kpad, raw.y, &kpad->status.ex_status.fs.acc.y);
+    new_var2 = kpad->status.ex_status.fs.acc.y;
     smooth_acc_value(kpad, raw.z, &kpad->status.ex_status.fs.acc.z);
-    kpad->status.ex_status.fs.acc_value = (f32) sqrt((kpad->status.ex_status.fs.acc.z * kpad->status.ex_status.fs.acc.z) + ((kpad->status.ex_status.fs.acc.x * kpad->status.ex_status.fs.acc.x) + (kpad->status.ex_status.fs.acc.y * kpad->status.ex_status.fs.acc.y)));
+    kpad->status.ex_status.fs.acc_value = (f32) sqrt((kpad->status.ex_status.fs.acc.z * kpad->status.ex_status.fs.acc.z) + ((kpad->status.ex_status.fs.acc.x * kpad->status.ex_status.fs.acc.x) + (kpad->status.ex_status.fs.acc.y * new_var2)));
     extensionPrevious.x -= kpad->status.ex_status.fs.acc.x;
     extensionPrevious.y -= kpad->status.ex_status.fs.acc.y;
     extensionPrevious.z -= kpad->status.ex_status.fs.acc.z;

```

KPADRead score1008 hint:
```diff
--- KPADRead baseline
+++ 1008
@@ -7,12 +7,12 @@
   s32 start;
   s32 sampleIndex;
   u32 remaining;
+  u32 coreButtons;
   u32 remainingSamples;
   u32 buttons;
   u16 previousButtons;
   u32 changed;
   u32 extensionButtons;
-  u32 coreButtons;
   u8 device;
   KPADSample latestSample;
   KPADSample *sample;
@@ -46,7 +46,7 @@
     reset_kpad(kpad);
   }
   WPADSetSamplingCallback(chan, KPADiSamplingCallback);
-  if (((kpad->ringCount == 0) || (statuses == 0)) || (count == 0))
+  if (((kpad->ringCount == 0) || (previousButtons = statuses == 0)) || (count == 0))
   {
     goto finish;
   }
@@ -86,7 +86,8 @@
     WPADAccGravityUnit gravity = {1, 1, 1};
     WPADAccGravityUnit extensionGravity = {1, 1, 1};
     WPADGetAccGravityUnit(chan, WPAD_ACC_GRAVITY_UNIT_CORE, &gravity);
-    if (((gravity.z * gravity.x) * gravity.y) != 0)
+    interruptState = (gravity.z * gravity.x) * gravity.y;
+    if (interruptState != 0)
     {
       kpad->value4DC = 1.0f / gravity.x;
       kpad->value4E0 = 1.0f / gravity.y;

```

Clean full gate before first improvement commit:
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/kpad/KPAD] objdiff: code 8880/13056 data 8032/8032 functions 26/29 fuzzy 99.2279 linked code 0
[libs/RVL_SDK/src/kpad/KPAD] instruction-exact functions: 26/29
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 4168/47816 data 144/536 functions 5/8 fuzzy 96.6547 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 5/8
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Committed gate-passing calc_dpd_variable exact improvement: 1613d0798ad7a1f5ffbbf2b131e59b2542ffe13c. KPAD now 26/29, matched code8880/13056, data8032/8032. Remaining functions continue.
KPADRead: permuter best 1008 -> 998, elapsed 5.5 minutes.

- Source attempt {"build": 2, "error": "/1] MWCC build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#     605:     f32* verticalAcceleration = &kpad->acceleration.y; \n#   Error:     ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "read_kpad_acc", "label": "permuter670_vertical_acceleration_pointer"}

- Source attempt {"build": 2, "error": "C build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#     632:         f32 extensionY = kpad->status.ex_status.fs.acc.y; \n#   Error:         ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "read_kpad_acc", "label": "permuter670_cached_extension_y"}

- Source attempt {"build": 2, "error": "/1] MWCC build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#     605:     f32* verticalAcceleration = &kpad->acceleration.y; \n#   Error:     ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "read_kpad_acc", "label": "permuter670_pointer_and_cached_y"}

- Source attempt {"build": 2, "error": "[1/1] MWCC build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#     605:     Vec* acceleration = &kpad->acceleration; \n#   Error:     ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "read_kpad_acc", "label": "permuter670_acceleration_vector_pointer"}
KPADRead: permuter best 998 -> 988, elapsed 8.5 minutes.

- Source attempt {"build": 2, "error": "C build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#     637:         f32 extensionY = kpad->status.ex_status.fs.acc.y; \n#   Error:         ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "read_kpad_acc", "helper_changed": true, "label": "permuter670_cached_y_absolute_branches"}

- Source attempt {"build": 2, "error": "[1/1] MWCC build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#     610:     Vec* acceleration = &kpad->acceleration; \n#   Error:     ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "read_kpad_acc", "helper_changed": true, "label": "permuter670_vector_pointer_absolute_branches"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 222, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.16, "helper_changed": true, "instructions": [399, 400], "label": "permuter670_nested_extension_absolute_branches", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 2, "error": "C build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#     632:         f32 extensionY = kpad->status.ex_status.fs.acc.y; \n#   Error:         ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "read_kpad_acc", "helper_changed": true, "label": "permuter670_nested_extension_cached_y_absolute_branches"}

KPADRead score998 hint compared to score1008:
```diff
--- score1008
+++ score998
@@ -5,14 +5,15 @@
   u32 available = 0;
   u32 ringCount;
   s32 start;
+  s32 new_var;
   s32 sampleIndex;
   u32 remaining;
-  u32 coreButtons;
   u32 remainingSamples;
   u32 buttons;
   u16 previousButtons;
   u32 changed;
   u32 extensionButtons;
+  u32 coreButtons;
   u8 device;
   KPADSample latestSample;
   KPADSample *sample;
@@ -34,7 +35,7 @@
     if ((kpad->dpdCallback != 0) && (kpad->dpdCallbackPending == 0))
     {
       kpad->dpdCallbackPending = 1;
-      kpad->dpdCallback(chan, 1);
+      kpad->dpdCallback(new_var = chan, 1);
       kpad->dpdCallbackFired = 0;
     }
     kpad->flag51F = 0;
@@ -46,7 +47,7 @@
     reset_kpad(kpad);
   }
   WPADSetSamplingCallback(chan, KPADiSamplingCallback);
-  if (((kpad->ringCount == 0) || (previousButtons = statuses == 0)) || (count == 0))
+  if (((kpad->ringCount == 0) || (statuses == 0)) || (count == 0))
   {
     goto finish;
   }
@@ -86,8 +87,7 @@
     WPADAccGravityUnit gravity = {1, 1, 1};
     WPADAccGravityUnit extensionGravity = {1, 1, 1};
     WPADGetAccGravityUnit(chan, WPAD_ACC_GRAVITY_UNIT_CORE, &gravity);
-    interruptState = (gravity.z * gravity.x) * gravity.y;
-    if (interruptState != 0)
+    if (((gravity.z * gravity.x) * gravity.y) != 0)
     {
       kpad->value4DC = 1.0f / gravity.x;
       kpad->value4E0 = 1.0f / gravity.y;
@@ -184,7 +184,7 @@
       {
         previousButtons = kpad->status.ex_status.cl.hold;
         kpad->status.ex_status.cl.hold = (u16) extensionButtons;
-        changed = previousButtons ^ ((u16) extensionButtons);
+        changed = (long long) (previousButtons ^ ((u16) extensionButtons));
         kpad->status.ex_status.cl.trig = changed & extensionButtons;
         kpad->status.ex_status.cl.release = changed & previousButtons;
       }

```

Corrected the new read_kpad_acc hint translations for MWCC C90: declarations belong at each block start, with assignments kept at their original computation points. The failed mixed-declaration builds were restored and are not counted as successful source experiments. KPADRead score998 remains a rejected hint: it adds an unused callback-argument assignment and a redundant long-long cast.

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 66, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.15, "instructions": [400, 400], "label": "permuter670_vertical_acceleration_pointer_c90", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 109, "exact": false, "function": "read_kpad_acc", "fuzzy": 97.4075, "instructions": [399, 400], "label": "permuter670_cached_extension_y_c90", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 109, "exact": false, "function": "read_kpad_acc", "fuzzy": 97.4075, "instructions": [399, 400], "label": "permuter670_pointer_and_cached_y_c90", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 66, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.15, "instructions": [400, 400], "label": "permuter670_acceleration_vector_pointer_c90", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 103, "exact": false, "function": "read_kpad_acc", "fuzzy": 97.5075, "helper_changed": true, "instructions": [399, 400], "label": "permuter670_cached_y_absolute_branches_c90", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 62, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.2, "helper_changed": true, "instructions": [400, 400], "label": "permuter670_vector_pointer_absolute_branches_c90", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 220, "exact": false, "function": "read_kpad_acc", "fuzzy": 97.495, "helper_changed": true, "instructions": [398, 400], "label": "permuter670_nested_extension_cached_y_absolute_branches_c90", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

KPADRead score988 hint compared to score998:
```diff
--- score998
+++ score988
@@ -5,13 +5,11 @@
   u32 available = 0;
   u32 ringCount;
   s32 start;
-  s32 new_var;
   s32 sampleIndex;
   u32 remaining;
   u32 remainingSamples;
   u32 buttons;
   u16 previousButtons;
-  u32 changed;
   u32 extensionButtons;
   u32 coreButtons;
   u8 device;
@@ -35,7 +33,7 @@
     if ((kpad->dpdCallback != 0) && (kpad->dpdCallbackPending == 0))
     {
       kpad->dpdCallbackPending = 1;
-      kpad->dpdCallback(new_var = chan, 1);
+      kpad->dpdCallback(chan, 1);
       kpad->dpdCallbackFired = 0;
     }
     kpad->flag51F = 0;
@@ -176,17 +174,17 @@
       }
       buttons = (buttons & 0x9FFF) | (coreButtons & 0x6000);
       previousButtons = kpad->status.hold;
-      changed = previousButtons ^ buttons;
+      start = previousButtons ^ buttons;
       kpad->status.hold = buttons;
-      kpad->status.trig = changed & buttons;
-      kpad->status.release = changed & previousButtons;
+      kpad->status.trig = start & buttons;
+      kpad->status.release = start & previousButtons;
       if (device == 2)
       {
         previousButtons = kpad->status.ex_status.cl.hold;
         kpad->status.ex_status.cl.hold = (u16) extensionButtons;
-        changed = (long long) (previousButtons ^ ((u16) extensionButtons));
-        kpad->status.ex_status.cl.trig = changed & extensionButtons;
-        kpad->status.ex_status.cl.release = changed & previousButtons;
+        start = previousButtons ^ ((u16) extensionButtons);
+        kpad->status.ex_status.cl.trig = start & extensionButtons;
+        kpad->status.ex_status.cl.release = start & previousButtons;
       }
       calc_button_repeat(kpad, device, ringCount);
       remainingSamples = available;

```

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 37, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.608696, "instructions": [117, 115], "label": "compound_result_increment", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 37, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.608696, "instructions": [117, 115], "label": "explicit_result_increment", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 93, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 92.73913, "instructions": [122, 115], "label": "compound_all_cursors", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 93, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 92.73913, "instructions": [122, 115], "label": "explicit_all_cursors", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 60, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.21739, "instructions": [117, 115], "label": "compound_character_decrement", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

Post-commit source audit: retained only the gate-passing calc_dpd_variable change; every other trial restored. Successful distinct source trial counts: {"KPADInit": 10, "KPADRead": 8, "Zi8GetElementCount": 35, "ZiMatchZHSpelling": 7, "calc_dpd_variable": 32, "read_kpad_acc": 19}. Zi8InternalGetZH remains explicitly excluded. Remaining permuter processes are still capped at two jobs.

Search checkpoint 2026-10-02T23:51:42.302523+00:00: {"queue": {"active": [{"best": 670, "elapsed": 2837, "function": "read_kpad_acc", "pid": 1491731}, {"best": 988, "elapsed": 1539, "function": "KPADRead", "pid": 1704570}], "all_lane_processes": [1491731, 1704570], "pending": []}, "queue-zi": {"active": [], "all_lane_processes": [1491731, 1704570], "pending": ["Zi8GetElementCount", "ZiMatchZHSpelling"]}}. No further source candidates retained.
Stopped read_kpad_acc: best 670, 4059 seconds, exit 0.
Origin source changed for Zi8GetElementCount at 14a8b23adbd5e72873acdce882ded87eae1c2a2b. Do not launch until the function is checked again.
Origin source changed for ZiMatchZHSpelling at 14a8b23adbd5e72873acdce882ded87eae1c2a2b. Do not launch until the function is checked again.

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 66, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.15, "helper_changed": true, "instructions": [400, 400], "label": "smooth_separate_declarations", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 62, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.2, "helper_changed": true, "instructions": [400, 400], "label": "smooth_separate_declarations_absolute_branches", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 293, "exact": false, "function": "read_kpad_acc", "fuzzy": 95.665, "helper_changed": true, "instructions": [394, 400], "label": "smooth_cached_previous_value", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "8880", "data": "8032", "diffs": 66, "exact": false, "function": "read_kpad_acc", "fuzzy": 98.15, "helper_changed": true, "instructions": [400, 400], "label": "smooth_explicit_result_assignment", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}
Stopped KPADRead: best 988, 3216 seconds, exit 0.

Reviewed origin/main 1fa33882ae6f932c8603e54b62b7d134c0325b05 after the queue stopped on a full-unit source change. The change corrects Chinese phonetic contracts and dispatch in excluded/other functions. Both requested function definitions remain byte-for-byte identical to the original non-exact source; header/config changes: []. Recent origin report: {"baseline_commit": "14a8b23adbd5e72873acdce882ded87eae1c2a2b", "functions": {"ZiMatchZHSpelling": 98.80165, "Zi8GetElementCount": 99.347824}}.
Zi8GetElementCount: unrelated origin edits reviewed; requested definition and headers unchanged, origin report 14a8b23adbd5e72873acdce882ded87eae1c2a2b still scores 99.347824.

Pre-permuter origin check Zi8GetElementCount: 1fa33882ae6f932c8603e54b62b7d134c0325b05; requested definition remains the non-exact baseline; unrelated whole-unit updates were reviewed. Started PID 2233300, one job, 2026-10-03T00:21:26.229728+00:00.
Zi8GetElementCount: permuter best None -> 75, elapsed 0.1 minutes.
ZiMatchZHSpelling: unrelated origin edits reviewed; requested definition and headers unchanged, origin report 14a8b23adbd5e72873acdce882ded87eae1c2a2b still scores 98.80165.

Pre-permuter origin check ZiMatchZHSpelling: 1fa33882ae6f932c8603e54b62b7d134c0325b05; requested definition remains the non-exact baseline; unrelated whole-unit updates were reviewed. Started PID 2233987, one job, 2026-10-03T00:21:31.636547+00:00.
ZiMatchZHSpelling: permuter best None -> 145, elapsed 0.1 minutes.
ZiMatchZHSpelling: permuter best 145 -> 140, elapsed 31.5 minutes.

ZiMatchZHSpelling restricted retry score140 hint:
```diff
--- baseline145
+++ score140
@@ -1,50 +1,60 @@
 {
-ziWChar* candidateCursor;
-ziWChar* spellingCursor;
-int index;
-int matches;
-int candidateLength;
-ziWChar spacedSpelling[64];
-ziWChar spacedCandidate[64];
-matches = 1;
-candidateLength = Zi8WCharCount(candidate, __zi8_work_data);
-if (!candidate || !spellingLength) {
-return matches;
-}
-for (index = 0; index < spellingLength; ++index) {
-if (!candidate[index] || candidate[index] != spelling[index]) {
-matches = 0;
-break;
-}
-}
-if (!matches) {
-spacedSpelling[0] = 0;
-spacedCandidate[0] = 0;
-if (!Zi8ZHaddSpace(spelling, spellingLength, spacedSpelling, 64, __zi8_work_data)) {
-return 0;
-}
-if (!Zi8ZHaddSpace(candidate, candidateLength, spacedCandidate, 64, __zi8_work_data)) {
-return 0;
-}
-spellingCursor = spacedSpelling;
-candidateCursor = spacedCandidate;
-while (phoneticIndex) {
-candidateCursor = ZiGetNextPhonetic(candidateCursor, spacedCandidate + 64, __zi8_work_data);
-if (!candidateCursor) {
-return 0;
-}
---phoneticIndex;
-}
-matches = 1;
-while (spellingCursor && candidateCursor) {
-if (!ZiPartialMatch(spellingCursor, spacedSpelling + 64,
-candidateCursor, spacedCandidate + 64,
-phoneticIndex, __zi8_work_data)) {
-return 0;
-}
-spellingCursor = ZiGetNextPhonetic(spellingCursor, spacedSpelling + 64, __zi8_work_data);
-candidateCursor = ZiGetNextPhonetic(candidateCursor, spacedCandidate + 64, __zi8_work_data);
-}
-}
-return matches;
+  ziWChar *spellingCursor;
+  int index;
+  int matches;
+  int candidateLength;
+  ziWChar spacedSpelling[64];
+  ziWChar spacedCandidate[64];
+  matches = 1;
+  candidateLength = Zi8WCharCount(candidate, __zi8_work_data);
+  if ((!candidate) || (!spellingLength))
+  {
+    return matches;
+  }
+  for (index = 0; index < spellingLength; ++index)
+  {
+    if ((!candidate[index]) || (candidate[index] != spelling[index]))
+    {
+      matches = 0;
+      break;
+    }
+  }
+
+  if (!matches)
+  {
+    spacedSpelling[0] = 0;
+    spacedCandidate[0] = 0;
+    if (!Zi8ZHaddSpace(spelling, spellingLength, spacedSpelling, 64, __zi8_work_data))
+    {
+      return 0;
+    }
+    if (!Zi8ZHaddSpace(candidate, candidateLength, spacedCandidate, 64, __zi8_work_data))
+    {
+      return 0;
+    }
+    spellingCursor = spacedSpelling;
+    __zi8_work_data = spacedCandidate;
+    while (phoneticIndex != 0U)
+    {
+      __zi8_work_data = ZiGetNextPhonetic(__zi8_work_data, spacedCandidate + 64, __zi8_work_data);
+      if (!__zi8_work_data)
+      {
+        return 0;
+      }
+      --phoneticIndex;
+    }
+
+    matches = 1;
+    while (spellingCursor && __zi8_work_data)
+    {
+      if (!ZiPartialMatch(spellingCursor, spacedSpelling + 64, __zi8_work_data, spacedCandidate + 64, phoneticIndex, __zi8_work_data))
+      {
+        return 0;
+      }
+      spellingCursor = ZiGetNextPhonetic(spellingCursor, spacedSpelling + 64, __zi8_work_data);
+      __zi8_work_data = ZiGetNextPhonetic(__zi8_work_data, spacedCandidate + 64, __zi8_work_data);
+    }
+
+  }
+  return matches;
 }
```

Rejected ZiMatchZHSpelling score140: the permuter merges candidateCursor into __zi8_work_data, replacing the context pointer passed to ZiGetNextPhonetic/ZiPartialMatch with the candidate buffer. This changes semantics. The valid restricted-search score remains145. An unsafe hint does not extend the useful-search timer; stop this retry near 01:06:35 UTC if no valid improvement appears. No source changes retained.
Stopped Zi8GetElementCount: best 75, 2708 seconds, exit 0.

Stopped ZiMatchZHSpelling restricted retry after roughly45 minutes without a valid improvement. Raw best140 was rejected for corrupting the work pointer. Valid best145 remains the baseline.
Stopped ZiMatchZHSpelling: best 140, 2753 seconds, exit 0.

Final successful-source audit, counting distinct candidate source bytes including signature/helper changes: {"KPADInit": 10, "KPADRead": 8, "Zi8GetElementCount": 35, "ZiMatchZHSpelling": 7, "calc_dpd_variable": 31, "read_kpad_acc": 19}. Every requested function has at least three distinct successful-build trials. Zi8InternalGetZH remains excluded. All searches stopped, with no unresolved source edits beyond the committed exact calc_dpd_variable change. Starting the final clean full gate over both units.

## Final result

calc_dpd_variable: 94.82% -> 100.0%, ctxdiff0, 250/250 instructions. Commit1613d0798ad7a1f5ffbbf2b131e59b2542ffe13c.
KPAD: instruction-exact25/29 -> 26/29; code7880/13056 -> 8880/13056; data8032/8032 unchanged.
zi8cgetc: instruction-exact5/8 unchanged; code4168/47816 unchanged; data144/536 unchanged.

Permuter best scores and disposition:
- KPADInit675 -> 420: direct matrix-array hint; readable variants remained below100.
- calc_dpd_variable1735 -> 505: shared midpoint and scalar-order hint translated into the accepted exact implementation, after natural transformed-coordinate and compound-division changes.
- read_kpad_acc710 -> 670: pointer/cached-Y hints; readable variants remained below100 and were restored.
- KPADRead1023 -> 988: mixed-role index reuse and other discarded artifacts; no readable exact candidate.
- Zi8GetElementCount75 -> 0 in unrestricted retries: empty-condition noise rejected. Restricted45-minute retry stayed75.
- ZiMatchZHSpelling145 -> 105 with empty-condition noise, rejected. Restricted retry140 corrupted the context pointer, rejected; valid score remained145.

Remaining functions: [{"function": "read_kpad_acc", "fuzzy": 98.15}, {"function": "KPADRead", "fuzzy": 97.52723}, {"function": "KPADInit", "fuzzy": 96.51351}, {"function": "ZiMatchZHSpelling", "fuzzy": 98.80165}, {"function": "zi8InternalGetZH", "fuzzy": 96.27482}, {"function": "Zi8GetElementCount", "fuzzy": 99.347824}]. Every owned open function has at least three logged distinct successful-build source attempts. zi8InternalGetZH was skipped as requested.

Final clean full gate, both units:
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/kpad/KPAD] pool: IDENTICAL
[libs/RVL_SDK/src/kpad/KPAD] objdiff: code 8880/13056 data 8032/8032 functions 26/29 fuzzy 99.2279 linked code 0
[libs/RVL_SDK/src/kpad/KPAD] instruction-exact functions: 26/29
[libs/RVL_SDK/src/kpad/KPAD]   section .bss size 7680 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .data size 88 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sbss size 32 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sdata size 112 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sdata2 size 120 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .text size 13056 match 99.22794
[libs/RVL_SDK/src/kpad/KPAD]   below 100: read_kpad_acc 98.15
[libs/RVL_SDK/src/kpad/KPAD]   below 100: KPADRead 97.52723
[libs/RVL_SDK/src/kpad/KPAD]   below 100: KPADInit 96.51351
[libs/RVL_SDK/src/kpad/KPAD] baseline: code 7880/13056 data 8032 functions 25 fuzzy 98.8312
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 4168/47816 data 144/536 functions 5/8 fuzzy 96.6547 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 5/8
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .data size 392 match None
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sbss2 size 8 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .sdata2 size 16 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section .text size 47816 match 96.65468
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extab size 48 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   section extabindex size 72 match 100.0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: ZiMatchZHSpelling 98.80165
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: zi8InternalGetZH 96.27482
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc]   below 100: Zi8GetElementCount 99.347824
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] baseline: code 4168/47816 data 144 functions 5 fuzzy 96.6547
regressions vs baseline: 0
global matched_code_percent: 91.16326 -> 91.19665
global fuzzy_match_percent: 99.60110 -> 99.60283
global complete_code_percent: 74.56724 -> 74.56724
global matched_data_percent: 99.55890 -> 99.55890
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS

```
Final focused checks: both string pools identical; calc_dpd_variable ctxdiff0 at250/250 instructions; source matches the committed exact candidate; no other source changes remain. All permuter processes stopped.
