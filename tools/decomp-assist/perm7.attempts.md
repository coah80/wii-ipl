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

## perm7c recovery and continued search 2026-10-03T03:28:22.274387+00:00
Current branch starts at origin/main 885cdfee. Initial quick full gate PASS: KPAD26/29 instruction-exact, code8880/13056, data8032/8032; zi8cgetc5/8, code4168/47816, data144/536. Both pools identical; DOL26116613f624061ba99c8d1a299aaa6efa85670d. Live baseline is /tmp/perm7c-baseline-report.json.
Recovery attempt1: transplant only read_kpad_acc and KPADRead from orch/perm7b-progress. Preserve #1014 smoothing helper and all other functions. KPADRead keeps #1014 early remaining assignment and lower16-bit extension-button narrowing; gravity product order and button locals use the prior exact variant. read_kpad_acc replaces the non-exact guard with the prior exact extension dispatch.
Recovery result: read_kpad_acc100.0%,400/400 instructions,diffs0; KPADRead100.0%,459/459 instructions,diffs0. Full clean gate PASS, DOL26116613f624061ba99c8d1a299aaa6efa85670d, regressions0, forbidden0, readability0; KPAD26/29 ->28/29, code8880 ->12316, data8032 unchanged. Source changes are limited to those two definitions; #1014 smoothing helper remains intact. Full gate /tmp/perm7c-recovery-full-gate.txt.
Recovery committed9cf16954. Refreshed all three permuter compile scripts from ninja -t commands, keeping every unit flag and using only input/output substitution. Original objects copied fresh; resumed old dirs and archived prior outputs. KPADInit resumes the readable365 declaration/matrix hint. Zi8GetElementCount and ZiMatchZHSpelling keep valid75/145 seeds. Unsafe/noise generators remain disabled, including context/function-type mutations and redundant literal/array alias passes. Each active permuter uses one job, two total.
Fresh origin 9c7d87ab008df7e35558321e3ca297a887d35c44: Zi8GetElementCount source unchanged from independently measured baseline 99.347824%; proceed.
Resume Zi8GetElementCount: fetched origin 9c7d87ab008df7e35558321e3ca297a887d35c44, function remains baseline/non-exact. Started PID 3685445, one job, score 75, 2026-10-03T03:31:38.864918+00:00.
Fresh origin 9c7d87ab008df7e35558321e3ca297a887d35c44: KPADInit source unchanged from independently measured baseline 96.51351%; proceed.
Resume KPADInit: fetched origin 9c7d87ab008df7e35558321e3ca297a887d35c44, function remains baseline/non-exact. Started PID 3685539, one job, score 365, 2026-10-03T03:31:39.164658+00:00.
Resume KPADInit: best 365 -> 355, elapsed 60s. Candidates require semantic/readability review.

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 108, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 95.89565, "instructions": [117, 115], "label": "perm7c_local_element_bound_const", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 108, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.89565, "instructions": [116, 115], "label": "perm7c_local_element_bound_mutable", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_loop_for_continue", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_loop_for_tail", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 50, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 86.652176, "instructions": [115, 115], "label": "perm7c_loop_explicit_guards", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_alphabet_while", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 37, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.608696, "instructions": [117, 115], "label": "perm7c_count_add_assign", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 38, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.521736, "instructions": [117, 115], "label": "perm7c_cursor_add_assign", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 64, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 96.86957, "instructions": [117, 115], "label": "perm7c_separator_equal_else", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_while_condition_positive", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.86957, "instructions": [115, 115], "label": "perm7c_return_explicit_narrow", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_bound_parameter_unsigned_compare", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_separate_fallback_zero", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 108, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.434784, "instructions": [116, 115], "label": "perm7c_return_phase_count", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 106, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.13043, "instructions": [116, 115], "label": "perm7c_return_phase_elementIndex", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 106, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.73913, "instructions": [116, 115], "label": "perm7c_return_phase_spacedIndex", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_match_compound_set", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_prefix_mismatch_nested", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_prefix_while", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_phonetic_for", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_phonetic_for_test", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 2, "error": "ts -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -inline off -opt off -str readonly -sdata 0 -fp_contract off -Cpp_exceptions on -lang=c -MMD -c libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.c -o build/43U/src/libs/RVLMiddleware/eZiText/src/clib && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.d build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVLMiddleware\\eZiText\\src\\clib\\zi8cgetc.c\n# -------------------------------------------------------\n#      95:         while (spellingCursor != NULL && candidateCursor != NULL) { \n#   Error:                                  ^^^^\n#   (10140) undefined identifier 'NULL'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "ZiMatchZHSpelling", "label": "perm7c_cursor_while_explicit"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_prefix_signed_length", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 2, "error": "ine auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -inline off -opt off -str readonly -sdata 0 -fp_contract off -Cpp_exceptions on -lang=c -MMD -c libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.c -o build/43U/src/libs/RVLMiddleware/eZiText/src/clib && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.d build/43U/src/libs/RVLMiddleware/eZiText/src/clib/zi8cgetc.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVLMiddleware\\eZiText\\src\\clib\\zi8cgetc.c\n# -------------------------------------------------------\n#      67:   candidateLength = Zi8WCharCount(candidateWord, __zi8_work_data); \n#   Error:                                                                 ^\n#   (10209) illegal implicit conversion from 'const unsigned short *' to\n#   'unsigned short *'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "ZiMatchZHSpelling", "label": "perm7c_candidate_word_local"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.34711, "instructions": [121, 121], "label": "perm7c_candidate_length_narrow", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_matches_local_boolean", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 98, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 97.06612, "instructions": [122, 121], "label": "perm7c_matches_local_short", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 118, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 95.76859, "instructions": [123, 121], "label": "perm7c_work_local", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 30, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 97.19009, "instructions": [121, 121], "label": "perm7c_candidate_length_const_int", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 30, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 96.735535, "instructions": [121, 121], "label": "perm7c_candidate_length_const_ziU8", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 30, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 96.735535, "instructions": [121, 121], "label": "perm7c_candidate_length_const_ziU16", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_declare_later_candidateCursor", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}
The explicit cursor guard trial initially used NULL, which is undefined in this C unit; corrected it to0 for the next sequential retry. Permuter debug generated debug_source.c in the invocation directory; removed this generated file. It is never part of the source diff.

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_declare_later_spellingCursor", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_declare_later_matches", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_declare_later_candidateLength", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_declare_later_index", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_cursor_while_explicit_zero", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_original", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 80, "exact": false, "function": "KPADInit", "fuzzy": 96.567566, "instructions": [185, 185], "label": "perm7c_init_original_negative_sine_double", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 80, "exact": false, "function": "KPADInit", "fuzzy": 96.567566, "instructions": [185, 185], "label": "perm7c_init_original_negative_sine_delayed_narrow", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_original_repeat_u16_loop", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_original_repeat_u16_sensitivity", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_original_repeat_u32_loop", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_original_repeat_u32_sensitivity", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_original_repeat_s32_loop", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_original_repeat_s32_sensitivity", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "7912", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_original_const_one", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "7912", "diffs": 85, "exact": false, "function": "KPADInit", "fuzzy": 96.4054, "instructions": [185, 185], "label": "perm7c_init_original_const_zero", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "7912", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_original_const_degreesToRadians", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_init_matrix_row_view", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 80, "exact": false, "function": "KPADInit", "fuzzy": 96.567566, "instructions": [185, 185], "label": "perm7c_init_matrix_row_view_double_sine", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 75, "exact": false, "function": "KPADInit", "fuzzy": 96.72973, "instructions": [185, 185], "label": "perm7c_init_original_channel_array_loop", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 86, "exact": false, "function": "KPADInit", "fuzzy": 94.96757, "instructions": [185, 185], "label": "perm7c_init_original_ring_sample_cursor", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 2, "error": "src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#    1581:     negativeSine = -sin(degreesToRadians * sensor_bar_angle_degrees); \n#   Error:     ^^^^^^^^^^^^\n#   (10140) undefined identifier 'negativeSine'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "KPADInit", "label": "perm7c_init_direct_matrix_hint365_negative_sine_double"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 15, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 97.652176, "instructions": [115, 115], "label": "perm7c_extra_count_then_restore_separator", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "5597736bc961f2567d5d42e35baf6445b79fb9bc20421d39fe1225ae4a9a1f5c"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 15, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.17391, "instructions": [115, 115], "label": "perm7c_extra_count_return_shared_label", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "eeef804053313c677e422a2b95a144a211dcee3bc6053bdeed2fa543a64a34a7"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 53, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 94.04348, "instructions": [115, 115], "label": "perm7c_extra_bounded_characters_for", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "86e910889c1e0ceddb9b40e31df95079756d6ba683dfd904599baa317efdc7b8"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 15, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.17391, "instructions": [115, 115], "label": "perm7c_extra_tone_before_skip_cursor", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "15f7fbc93dabaf9275bd76954eb6b1c71defea3f3d7a0ee3943ea9c5009bcca8"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 42, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 87.57391, "instructions": [115, 115], "label": "perm7c_extra_separator_is_special_branch", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "f985ec395498629a401587bed888356c57566790becc218f2c6469905e6a7db0"}

- Source attempt {"build": 2, "error": "src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#    1581:     negativeSine = -sin(degreesToRadians * sensor_bar_angle_degrees); \n#   Error:     ^^^^^^^^^^^^\n#   (10140) undefined identifier 'negativeSine'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "KPADInit", "label": "perm7c_init_direct_matrix_hint365_negative_sine_delayed_narrow"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 24, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.608696, "instructions": [115, 115], "label": "perm7c_extra_alphabet_count", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "314a3caf96c690d746a8691ee6f31fb44f3b2226b396745a44e44d69372a5171"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 24, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.608696, "instructions": [115, 115], "label": "perm7c_extra_alphabet_elementIndex", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "795c8f7da4e39c2f5df9e51e4aa9cccdeb799f2c3e6030ae97c5e3314b7caa2e"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 107, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 96.50435, "instructions": [117, 115], "label": "perm7c_extra_limit_alias_const_ziU8", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "811f41b0d52955e92b026c5725a360747082336fd956cd0e951e599164ebc73e"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 108, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.5913, "instructions": [116, 115], "label": "perm7c_extra_limit_alias_ziU8", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "104150128b816003aeebcfca9b74bd6b4cf08220c87e10022527e362e34697a7"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 85, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 93.54783, "instructions": [112, 115], "label": "perm7c_extra_limit_alias_unsigned_int", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "0db25e8a9635f7600181e5945add4832510667b120bb869962b1a8baa1ad4286"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_extra_prefix_match_false_first", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "b0b8e7dd99a120950e57e11b62d98dd756c2b48b854980f52ac2c71d92b74d56"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 122, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 92.85124, "instructions": [124, 121], "label": "perm7c_extra_candidate_buffers_in_block", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "7677f8ee0932fafa99064a61b9bad161a9c47a598b590b33fb269c7c8a40a1a1"}

- Source attempt {"build": 0, "code": "4168", "data": "96", "diffs": 54, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 97.099174, "instructions": [121, 121], "label": "perm7c_extra_prefix_match_separate_limit", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "236f5aa4279a86b90e3c008df4888a090e74b183db66e6eb695c90262e9239f3"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 30, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 97.19009, "instructions": [121, 121], "label": "perm7c_extra_candidate_length_after_result_set", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "f30a978764841cbcd141dfee91905810e247e1b1cc17ea4808412d4eb2d06e36"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 69, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 97.80991, "instructions": [122, 121], "label": "perm7c_extra_candidate_skip_predecrement", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "8233c959f41013afbdcd0b40405695197b7cff182ed67da6e95dc9d2049304be"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 30, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.76033, "instructions": [121, 121], "label": "perm7c_extra_prefix_end_equality", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "c3c43a2028514c659322d0868ecfa3faadad41d543cbe37b1d58de692da76096"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 51, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 95.41322, "instructions": [121, 121], "label": "perm7c_extra_loop_cursors_break", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "0fd1f1d61bcba08ded57503ceb2dc7720d8936d0b79523dc1ef07bf416cf27b7"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 98, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 97.06612, "instructions": [122, 121], "label": "perm7c_extra_type_matches_ziS16", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "757c1c8ed5d7b826d12f4425bec59cc5fd31a61337ad56313b5c14412201488f"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_extra_type_matches_long", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "59f8ad2649a4c7eddcc2020a30fbc076534ce618555b490c226c6ca9d9911392"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_extra_type_matches_ziU32", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "6fc47facaf2b3108080062f33b45f4f3b4ffa529893aff1ab105553e8261b819"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.34711, "instructions": [121, 121], "label": "perm7c_extra_type_candidateLength_ziS16", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "b3562c9ea48cd57a95b0d4fd4ea9b60210e53190c0deb0688f31815405d79c72"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_extra_type_candidateLength_long", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d3976e1ca637a886909dc445495820156d758248cbc4d6bf528a8a51685923de"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_extra_type_candidateLength_ziU32", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3d5001def4c5161189123f45264b9de8149c5ec074c9627b0ac800676804873a"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 114, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 95.24793, "instructions": [125, 121], "label": "perm7c_extra_type_index_ziS16", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "f46f0b24e9bad1a2cc0f089b5be9f9af9d58d6273ec7367e5d338751f99eaef8"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_extra_type_index_long", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "8a35b5d266883b709449529737b63fbd56ada627146fe8ed4fd0d9de574ce275"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 30, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.305786, "instructions": [121, 121], "label": "perm7c_extra_type_index_ziU32", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "2c215c834bc68202f8ae047a0b191444efc13a34719468a0578ff9069d178c17"}

- Source attempt {"build": 2, "error": "c/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#    1569:     kpad->repeatDelay = repeatDelay; \n#   Error:                         ^^^^^^^^^^^\n#   (10140) undefined identifier 'repeatDelay'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "KPADInit", "label": "perm7c_init_direct_matrix_hint365_repeat_u16_loop"}

- Source attempt {"build": 2, "error": "c/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#    1569:     kpad->repeatDelay = repeatDelay; \n#   Error:                         ^^^^^^^^^^^\n#   (10140) undefined identifier 'repeatDelay'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "KPADInit", "label": "perm7c_init_direct_matrix_hint365_repeat_u16_sensitivity"}

- Source attempt {"build": 2, "error": "c/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#    1569:     kpad->repeatDelay = repeatDelay; \n#   Error:                         ^^^^^^^^^^^\n#   (10140) undefined identifier 'repeatDelay'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "KPADInit", "label": "perm7c_init_direct_matrix_hint365_repeat_u32_loop"}

- Source attempt {"build": 2, "error": "c/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#    1569:     kpad->repeatDelay = repeatDelay; \n#   Error:                         ^^^^^^^^^^^\n#   (10140) undefined identifier 'repeatDelay'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "KPADInit", "label": "perm7c_init_direct_matrix_hint365_repeat_u32_sensitivity"}

- Source attempt {"build": 2, "error": "c/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#    1569:     kpad->repeatDelay = repeatDelay; \n#   Error:                         ^^^^^^^^^^^\n#   (10140) undefined identifier 'repeatDelay'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "KPADInit", "label": "perm7c_init_direct_matrix_hint365_repeat_s32_loop"}

- Source attempt {"build": 2, "error": "c/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#    1569:     kpad->repeatDelay = repeatDelay; \n#   Error:                         ^^^^^^^^^^^\n#   (10140) undefined identifier 'repeatDelay'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "KPADInit", "label": "perm7c_init_direct_matrix_hint365_repeat_s32_sensitivity"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_const_one", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_const_zero", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_const_degreesToRadians", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_channel_array_loop", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)"}

- Source attempt {"build": 2, "error": "[1/1] MWCC build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o\nFAILED: [code=2] build/43U/src/libs/RVL_SDK/src/kpad/KPAD.o \nbuild/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/3.0a5.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" -pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -DSDK_IPL -D_REVOLUTION -DMEM_MANAGER_DIRECT -i include -i include/global -i libs/MetroTRK/include -i libs/Runtime/include -i libs/MSL/include -i libs/RVL_SDK/include -i libs/RevoEX/include -i libs/NW4R/include -i libs/RVLMiddleware/eZiText/include -i libs/RVLMiddleware/TMC_JPEG/include -i libs/RVLFaceLib/include -i libs/EGG/include -i libs/OperaWWW/include -ir libs/RVL_SDK/include/private/bte -i build/43U/include -DBUILD_VERSION=0 -DVERSION_43U -i libs/RVL_SDK/include/private/bte -DNDEBUG=1 -DTARGET_RVL -ipa file -fp_contract off -lang=c -MMD -c libs/RVL_SDK/src/kpad/KPAD.c -o build/43U/src/libs/RVL_SDK/src/kpad && \"/usr/bin/python3\" tools/transform_dep.py build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d build/43U/src/libs/RVL_SDK/src/kpad/KPAD.d\n### mwcceppc.exe Compiler:\n#    File: libs\\RVL_SDK\\src\\kpad\\KPAD.c\n# -------------------------------------\n#    1595:         ringSample->error = -1; \n#   Error:         ^^^^^^^^^^\n#   (10140) undefined identifier 'ringSample'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\nninja: build stopped: subcommand failed.\n", "function": "KPADInit", "label": "perm7c_init_direct_matrix_hint365_ring_sample_cursor"}
Resume KPADInit: best 355 -> 320, elapsed 558s. Candidates require semantic/readability review.
KPADInit full-unit trials exposed a generator spacing mismatch on the two-space permuter seed. Fixed missing real declarations before retrying the affected negativeSine/repeatDelay/ringSample candidates. Constant follow-ups assign all consumed values before use; excluded the late-one assignment candidate before compiling it. No failing or uninitialized candidate is retained in repository source.

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "25a5c77bf022c7d1bc3a3b1ab15c36615edbb1bc1073bf5a0fe14aff37f01a09"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 47, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_negative_sine_double_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "aa03d03939e12b49d96d157e880f062ef83fdefdcc5b4756ecc3a05a76e29db0"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 47, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_negative_sine_delayed_narrow_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "357ccccd7215fcae8a317567b95c2fbf909516f98ec6de5514202a6170e1f007"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 169, "exact": false, "function": "KPADInit", "fuzzy": 94.11892, "instructions": [183, 185], "label": "perm7c_init_direct_matrix_hint365_repeat_u16_loop_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "cce120585c262c9fde2409511e53d74adb0ec790261606287f922ab59a227f22"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 169, "exact": false, "function": "KPADInit", "fuzzy": 94.11892, "instructions": [183, 185], "label": "perm7c_init_direct_matrix_hint365_repeat_u16_sensitivity_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "cce120585c262c9fde2409511e53d74adb0ec790261606287f922ab59a227f22"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 169, "exact": false, "function": "KPADInit", "fuzzy": 94.11892, "instructions": [183, 185], "label": "perm7c_init_direct_matrix_hint365_repeat_u32_loop_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "cce120585c262c9fde2409511e53d74adb0ec790261606287f922ab59a227f22"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 169, "exact": false, "function": "KPADInit", "fuzzy": 94.11892, "instructions": [183, 185], "label": "perm7c_init_direct_matrix_hint365_repeat_u32_sensitivity_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "cce120585c262c9fde2409511e53d74adb0ec790261606287f922ab59a227f22"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 169, "exact": false, "function": "KPADInit", "fuzzy": 94.11892, "instructions": [183, 185], "label": "perm7c_init_direct_matrix_hint365_repeat_s32_loop_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "cce120585c262c9fde2409511e53d74adb0ec790261606287f922ab59a227f22"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 169, "exact": false, "function": "KPADInit", "fuzzy": 94.11892, "instructions": [183, 185], "label": "perm7c_init_direct_matrix_hint365_repeat_s32_sensitivity_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "cce120585c262c9fde2409511e53d74adb0ec790261606287f922ab59a227f22"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_const_one_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "25a5c77bf022c7d1bc3a3b1ab15c36615edbb1bc1073bf5a0fe14aff37f01a09"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_const_zero_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "25a5c77bf022c7d1bc3a3b1ab15c36615edbb1bc1073bf5a0fe14aff37f01a09"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_const_degreesToRadians_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "25a5c77bf022c7d1bc3a3b1ab15c36615edbb1bc1073bf5a0fe14aff37f01a09"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.189186, "instructions": [185, 185], "label": "perm7c_init_direct_matrix_hint365_channel_array_loop_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "25a5c77bf022c7d1bc3a3b1ab15c36615edbb1bc1073bf5a0fe14aff37f01a09"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 112, "exact": false, "function": "KPADInit", "fuzzy": 96.427025, "instructions": [184, 185], "label": "perm7c_init_direct_matrix_hint365_ring_sample_cursor_fixed_declarations", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "62e50691fc1fd318fa08ec4be36583100d52ee7373404b1c74cf06bbd14c11f0"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 96, "exact": false, "function": "KPADInit", "fuzzy": 92.24324, "instructions": [185, 185], "label": "perm7c_init2_pointer_declaration_one", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "730254807c1a6bf93016330c910ca6bc452a93fdb4acb6a9adf6ff07354b223b"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 95, "exact": false, "function": "KPADInit", "fuzzy": 92.297295, "instructions": [185, 185], "label": "perm7c_init2_pointer_declaration_one_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d806a3255fbb391f9aabcd40cd7a8270f0f0ebc311447cf30a40e36a6a5f0b44"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 96, "exact": false, "function": "KPADInit", "fuzzy": 92.24324, "instructions": [185, 185], "label": "perm7c_init2_pointer_declaration_zero", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "730254807c1a6bf93016330c910ca6bc452a93fdb4acb6a9adf6ff07354b223b"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 95, "exact": false, "function": "KPADInit", "fuzzy": 92.297295, "instructions": [185, 185], "label": "perm7c_init2_pointer_declaration_zero_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d806a3255fbb391f9aabcd40cd7a8270f0f0ebc311447cf30a40e36a6a5f0b44"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 96, "exact": false, "function": "KPADInit", "fuzzy": 92.24324, "instructions": [185, 185], "label": "perm7c_init2_pointer_declaration_degreesToRadians", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "730254807c1a6bf93016330c910ca6bc452a93fdb4acb6a9adf6ff07354b223b"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 95, "exact": false, "function": "KPADInit", "fuzzy": 92.297295, "instructions": [185, 185], "label": "perm7c_init2_pointer_declaration_degreesToRadians_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d806a3255fbb391f9aabcd40cd7a8270f0f0ebc311447cf30a40e36a6a5f0b44"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 96, "exact": false, "function": "KPADInit", "fuzzy": 92.24324, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_init_one", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "aaf518cd6e6a0f6200296a365b735fc7b2e6551258a69da99356d7f1ca0f38dd"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 95, "exact": false, "function": "KPADInit", "fuzzy": 92.297295, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_init_one_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "b73e10baf346a8e6400cc29a16ce609a96d66220fb9bc4d8c4e1f0c3b4f3db11"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 96, "exact": false, "function": "KPADInit", "fuzzy": 92.24324, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_init_zero", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "13dbb0d2fa204f55e6986f49ae67813adf3c011a2d54b245006756f30f6b1273"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 95, "exact": false, "function": "KPADInit", "fuzzy": 92.297295, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_init_zero_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "de889f40d03c8b455f553ec52d2842f8c27b345a09cfea257fab754449adb558"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 96, "exact": false, "function": "KPADInit", "fuzzy": 92.24324, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_init_degreesToRadians", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "155dc036de4192afcfc198aef63b8d721795f42c146a2a4f575ea2cef17888ec"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 95, "exact": false, "function": "KPADInit", "fuzzy": 92.297295, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_init_degreesToRadians_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a75504f9fae18d11cfcb01ae960e4851ee8262f351dd0f6a775bc2555b16b6ff"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 92, "exact": false, "function": "KPADInit", "fuzzy": 92.24324, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_sensitivity_one", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "0184f3280afb82cd27afd2cbad7f3de05a1ff437a515853b410c11f06f173ecb"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 91, "exact": false, "function": "KPADInit", "fuzzy": 92.297295, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_sensitivity_one_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "93bdf7d132df4bbe1a63e7b6e8126a9ec76a5ee425df7e2093f670c8b590e7de"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 92, "exact": false, "function": "KPADInit", "fuzzy": 92.24324, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_sensitivity_zero", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "79fc6534a5f113c62d68694b76a927249592c27d276b9ec627d3e18faba8a8aa"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 91, "exact": false, "function": "KPADInit", "fuzzy": 92.297295, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_sensitivity_zero_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d263a6c601a0743e04e3b94bdce1db2af2338b51fc57e41aa37f21f7f64bf4a9"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 92, "exact": false, "function": "KPADInit", "fuzzy": 92.24324, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_sensitivity_degreesToRadians", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "9f045ac8f6686b670e9ac956db2a5eb01d4827a9cee9fb4de7a7c43d8529030d"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 91, "exact": false, "function": "KPADInit", "fuzzy": 92.297295, "instructions": [185, 185], "label": "perm7c_init2_pointer_before_sensitivity_degreesToRadians_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ec6f9458a861a36b34c08ba1139ffc6b5f8e11a84ee72253dd678752f0c48f00"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 94, "exact": false, "function": "KPADInit", "fuzzy": 95.45946, "instructions": [185, 185], "label": "perm7c_init2_pointer_shared_sensitivity_one_before_init", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "c69cf0d2a03b1a7276d690bbfe768181ae04856d1f168265b12969a5e715bb3b"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 91, "exact": false, "function": "KPADInit", "fuzzy": 95.45946, "instructions": [185, 185], "label": "perm7c_init2_pointer_shared_sensitivity_one_before_sensitivity", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "cfc69e8efe3412359219db8c5553f5c22b1124da8311c3b6597fcd4f5e9c647c"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 200, "exact": false, "function": "KPADInit", "fuzzy": 74.42162, "instructions": [202, 185], "label": "perm7c_init2_pointer_reference_vector", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "86ae89619524e69366d0fc70394da09cdd7cad9d4c37f60a9e08252c7cdd1b93"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 200, "exact": false, "function": "KPADInit", "fuzzy": 74.42162, "instructions": [202, 185], "label": "perm7c_init2_pointer_reference_vector_multiply_y_first", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "1621918dff70c731309f8ba7c77077b6b3ee46f94238e28527195da62c8db489"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 199, "exact": false, "function": "KPADInit", "fuzzy": 75.46487, "instructions": [201, 185], "label": "perm7c_init2_pointer_reference_vector_shorter_reference", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "06fa67644da66977774d6f98f3e342558a92bdc1b0d35f88a62416a57334bde3"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_declaration_one", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 93.97298, "instructions": [185, 185], "label": "perm7c_init2_direct_declaration_one_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ccc460c5ece736fabd259b5d42ac7e405fae671641ed55d074190f470ef50e59"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_declaration_zero", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 93.97298, "instructions": [185, 185], "label": "perm7c_init2_direct_declaration_zero_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ccc460c5ece736fabd259b5d42ac7e405fae671641ed55d074190f470ef50e59"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_declaration_degreesToRadians", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 93.97298, "instructions": [185, 185], "label": "perm7c_init2_direct_declaration_degreesToRadians_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ccc460c5ece736fabd259b5d42ac7e405fae671641ed55d074190f470ef50e59"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_before_init_one", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 93.97298, "instructions": [185, 185], "label": "perm7c_init2_direct_before_init_one_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ccc460c5ece736fabd259b5d42ac7e405fae671641ed55d074190f470ef50e59"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_before_init_zero", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 93.97298, "instructions": [185, 185], "label": "perm7c_init2_direct_before_init_zero_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ccc460c5ece736fabd259b5d42ac7e405fae671641ed55d074190f470ef50e59"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_before_init_degreesToRadians", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 93.97298, "instructions": [185, 185], "label": "perm7c_init2_direct_before_init_degreesToRadians_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ccc460c5ece736fabd259b5d42ac7e405fae671641ed55d074190f470ef50e59"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_before_sensitivity_one", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 93.97298, "instructions": [185, 185], "label": "perm7c_init2_direct_before_sensitivity_one_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ccc460c5ece736fabd259b5d42ac7e405fae671641ed55d074190f470ef50e59"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_before_sensitivity_zero", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 93.97298, "instructions": [185, 185], "label": "perm7c_init2_direct_before_sensitivity_zero_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ccc460c5ece736fabd259b5d42ac7e405fae671641ed55d074190f470ef50e59"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_before_sensitivity_degreesToRadians", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 93.97298, "instructions": [185, 185], "label": "perm7c_init2_direct_before_sensitivity_degreesToRadians_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ccc460c5ece736fabd259b5d42ac7e405fae671641ed55d074190f470ef50e59"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_shared_sensitivity_one_before_init", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 66, "exact": false, "function": "KPADInit", "fuzzy": 93.91892, "instructions": [185, 185], "label": "perm7c_init2_direct_shared_sensitivity_one_before_sensitivity", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3534c70811edea560ae2491948194e0c853a683209e263ad72e858c41ed403d5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 200, "exact": false, "function": "KPADInit", "fuzzy": 75.583786, "instructions": [202, 185], "label": "perm7c_init2_direct_reference_vector", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a684e4ac5d24d7f7a88a7d3a643503730f3818bb714280563f0c3f95f8dbc3f7"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 200, "exact": false, "function": "KPADInit", "fuzzy": 75.583786, "instructions": [202, 185], "label": "perm7c_init2_direct_reference_vector_multiply_y_first", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a684e4ac5d24d7f7a88a7d3a643503730f3818bb714280563f0c3f95f8dbc3f7"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 200, "exact": false, "function": "KPADInit", "fuzzy": 75.583786, "instructions": [202, 185], "label": "perm7c_init2_direct_reference_vector_shorter_reference", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a684e4ac5d24d7f7a88a7d3a643503730f3818bb714280563f0c3f95f8dbc3f7"}

## perm7c T3 restart 2026-10-03T03:52:56.277666+00:00
Resume audit: HEAD9cf16954 on agent/w1002/sol-perm7c-max; only preexisting attempts log uncommitted. Fresh origin/main a791e598. Requested open definitions unchanged on origin. Fresh quick full gate PASS, pools identical, DOL26116613f624061ba99c8d1a299aaa6efa85670d, regressions0; KPAD28/29 code12316 data8032, zi8cgetc5/8 code4168 data144. read_kpad_acc400/400 ctxdiff0, KPADRead459/459 ctxdiff0. Exact recovery commit preserved.
Saved KPADInit320 hints rejected: zero temporarily holds1 solely to alias one; output320-2 also adds a redundant kpad alias. Saved355-1 negative-sine double temporary was already tested, so do not repeat it. Saved355-3 reverses the independent squared dimensions and is readable; use it as the next seed. Zi8GetElementCount and ZiMatchZHSpelling have already completed multiple45-minute plateaus; restart only if a new readable seed improves them. No previous trial is re-run.
Seed safety check initially scanned existing context declarations, including register in SDK prototypes, and aborted before changing the seed. Restricted it to the KPADInit definition, then copied the readable355-3 seed. Debug artifacts were moved from the worktree to the permuter directory with a cross-filesystem move.
The generated source lacks parser-only context types; preserved the saved base context and transplanted only the readable355-3 definition. Fresh standalone seed score355, no changed flags.
T3 resume KPADInit one job PID3845392, readable seed355, 2026-10-03T03:54:37.821690+00:00. Other two functions retain completed plateau evidence pending new manual variants.

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_t3_counter_declaration_order_1", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "56c5e702e5af41dd220667b7bf416f0ad25e962ed9fcfa1151dab2e017981322"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_t3_counter_declaration_order_2", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ec7de6d5672376c1b4580daf7c5d5f6bf6211ffff43bf2cde83bb8e560906466"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_t3_counter_declaration_order_3", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "1d5869278bd0beed6cc304e6c463ef31b84cfd36b608a3ef5e48c2c7dd8df0fd"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_t3_counter_declaration_order_4", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "5b61cda9840f1a21c51b248b932443ee21061a264c2e3ca39af7b311853662d1"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_t3_counter_declaration_order_5", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "0909059d891420b0d51623dbe1ac78ae54c85b055f6b41849dcaf1f9449d2190"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 114, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 91.9913, "instructions": [119, 115], "label": "perm7c_t3_scoped_counter_count", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "67f123dbc06ad218dbecfd616b48f34b96453ff86972eedc48d52502210b70cf"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 114, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 91.9913, "instructions": [119, 115], "label": "perm7c_t3_scoped_counter_elementIndex", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3d376f1d9da6dc4bb9fd9c715d573c0744340678bc1fe1b27e73873d6c57dfdc"}

- Source attempt {"build": 2, "error": "### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\perm7c-evaluate\\zi8cgetc-candidate.c\n# ----------------------------------------------------\n#    2874:     for (spacedIndex = 0; spacedIndex < elementCount; ++spacedIndex) { \n#   Error:          ^^^^^^^^^^^\n#   (10140) undefined identifier 'spacedIndex'\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n", "function": "Zi8GetElementCount", "label": "perm7c_t3_scoped_counter_spacedIndex", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "source_sha256": "5783a11cb6b3c58b50d88acc57914885e502a2ab25d670925c055141e0cba012"}

- Source attempt {"build": 2, "error": "### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\perm7c-evaluate\\zi8cgetc-candidate.c\n# ----------------------------------------------------\n#    2886:     ziU8 count = 0; \n#   Error:     ^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n", "function": "Zi8GetElementCount", "label": "perm7c_t3_count_declaration_at_counting_phase", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "source_sha256": "513de31d42f349be8a665f6d4acc6e5870b4be8ebb4fbe992a5a16a258412083"}

- Source attempt {"build": 0, "code": "3548", "data": "72", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 98.391304, "instructions": [115, 115], "label": "perm7c_t3_const_length_parameter", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "deb0d12792ed28f92b6f69b1cab6402b56c8c3cd47e273a966a856a4e41436c5"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_t3_const_elements_pointer", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "c5ae892288f822638f392ded51e10896a8b4b088ccba05596929dc86d3700d9d"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_t3_counter_single_declaration", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "62cc1ddf4c9cd9940beedae7113194cf68f7590e49e1bbc678de1f79a8038ecc"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 13, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 99.347824, "instructions": [115, 115], "label": "perm7c_t3_latin_index_loop_scope", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "b08ec585051357d0250f17b6a896d22fd7c4a8f3b6937dde9e373fcef37e6752"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 53, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 94.04348, "instructions": [115, 115], "label": "perm7c_t3_bounded_counting_loop_character_break", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "83cad08c93fd4738443d2eab296f043119139aab8266503aaa36056d98819237"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_t3_spelling_declaration_order_1", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "c48c07a07c087fd3323f70848207cf31e81a5e57ac7655aa8137bd990cdb54e6"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_t3_spelling_declaration_order_2", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "39f4467e47ec51d3313c3f5d4021bac998bbe519766ae490acfd6bc48352672d"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_t3_spelling_declaration_order_3", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a0509c4cec8726312d94d557d5d5bbfab686658b672062dcd889ca5fb9f9b31a"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_t3_spelling_declaration_order_4", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "0e2f13cd0797e14e74ef05b98b251d31b254eccf32532d9c9dcec027a5f99af4"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_t3_spelling_declaration_order_5", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a85a70cb1a9d99bf98c496de6fe3cf7ab239b04c49b3309213c83e8cedcd15ed"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_t3_const_candidate_pointer", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3c49857109551378a1484c0768930287b316079b04e09ed30432ae322f46a945"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_t3_const_spelling_pointer", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "08420a52835d28043227d89b2f03bccc1c0d152c7da0e3d69294906ac18c7404"}

- Source attempt {"build": 0, "code": "4168", "data": "72", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_t3_const_spelling_length", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "7d60f3b2dc3e1a3a3796f4ecac50b180b36f9f74c802e8d70a63428616bb2524"}

- Source attempt {"build": 2, "error": "### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\perm7c-evaluate\\zi8cgetc-candidate.c\n# ----------------------------------------------------\n#      85:         ziWChar* candidateCursor = spacedCandidate; \n#   Error:         ^^^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n", "function": "ZiMatchZHSpelling", "label": "perm7c_t3_candidate_cursor_declare_at_use", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "source_sha256": "4da774491af5f8cff94641d16a20ba7616d879e521cdbde9de709e04046b4c1c"}

- Source attempt {"build": 2, "error": "### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\perm7c-evaluate\\zi8cgetc-candidate.c\n# ----------------------------------------------------\n#      84:         ziWChar* spellingCursor = spacedSpelling; \n#   Error:         ^^^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n", "function": "ZiMatchZHSpelling", "label": "perm7c_t3_spelling_cursor_declare_at_use", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "source_sha256": "d36817d98a76b7f2b0f763b07aedc77df5260ba78ce585be503e36643cf8928d"}

- Source attempt {"build": 2, "error": "### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\perm7c-evaluate\\zi8cgetc-candidate.c\n# ----------------------------------------------------\n#      83:         ziWChar* spellingCursor = spacedSpelling; \n#   Error:         ^^^^^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n", "function": "ZiMatchZHSpelling", "label": "perm7c_t3_both_cursors_declare_at_use", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "source_sha256": "1bb13c014aeeb090c1e89c3e3b893e044b8eca340f927908297869d5610a3141"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 122, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 92.85124, "instructions": [124, 121], "label": "perm7c_t3_prefix_cursor_index_scope", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "88e0c0e7d968bbddb87652ae4848ff3e09cf871941eed657e44c3fc77b0b1823"}

- Source attempt {"build": 0, "code": "4168", "data": "144", "diffs": 29, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 98.80165, "instructions": [121, 121], "label": "perm7c_t3_const_spellingCursor", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3f8f6d54b4a881c7263e6f70f8067e37016d9f3a443a72a01d6dc5d7cd04f224"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_direct_squared_dimensions_reversed", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "0a883b49f7e59c824cc96ca932067ae1c347e80629cdb926c8209744c9e4404b"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 47, "exact": false, "function": "KPADInit", "fuzzy": 98.297295, "instructions": [185, 185], "label": "perm7c_t3_direct_reversed_dimensions_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "05432deff0cdeb32bc9313144de1bbedc56fbf1c90ec48363e003b5b60a6142f"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 49, "exact": false, "function": "KPADInit", "fuzzy": 98.21622, "instructions": [185, 185], "label": "perm7c_t3_direct_scalar_init_order_1", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "487f488564d0e98b794abd5bea3ad939d0acdeaef391c4c98ff9caac0b41332f"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_direct_scalar_init_order_2", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "efd7cb84baf1ad238e52c7c7c79f8ee0e54dad0ea82948ca69c3620234f07898"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_direct_scalar_init_order_3", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d102b5702700605bdf89c378d5d2eccbba67a6edf125b3f73fdbc509e3718ab0"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 49, "exact": false, "function": "KPADInit", "fuzzy": 98.21622, "instructions": [185, 185], "label": "perm7c_t3_direct_scalar_init_order_4", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "6d5f712c21f0024a04197b6a1433c4df2f1f1b38d105529f39332a432e938d10"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 49, "exact": false, "function": "KPADInit", "fuzzy": 98.21622, "instructions": [185, 185], "label": "perm7c_t3_direct_scalar_init_order_5", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "4a96647cc284dff387fb94c77ac8cf4dfca9044ac42a318349d927c489e7faf7"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 169, "exact": false, "function": "KPADInit", "fuzzy": 97.54054, "instructions": [186, 185], "label": "perm7c_t3_direct_one_init_before_wpad", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "7f8ebbd8ca0f7682710ad01358e78cadac0782c01e509b47fd1f3074087ac869"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 164, "exact": false, "function": "KPADInit", "fuzzy": 97.54054, "instructions": [186, 185], "label": "perm7c_t3_direct_one_init_before_sensitivity", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "4524f3f3ec210782557e9531451ea3eab4ecf1bb61d2661ae4bcd9b49044bef4"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 64, "exact": false, "function": "KPADInit", "fuzzy": 97.16216, "instructions": [185, 185], "label": "perm7c_t3_direct_zero_init_before_wpad", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "c30b039a445af8041fedcf60aab40ac1bd2bbaed19e58e977634f787195f3e8e"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 59, "exact": false, "function": "KPADInit", "fuzzy": 97.16216, "instructions": [185, 185], "label": "perm7c_t3_direct_zero_init_before_sensitivity", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "6f9324bf18c8ab1ba78d007218d2009f5af57be617bd45d2316814cfbc38aadf"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 65, "exact": false, "function": "KPADInit", "fuzzy": 97.16216, "instructions": [185, 185], "label": "perm7c_t3_direct_degreesToRadians_init_before_wpad", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "4fd6813693d25a75895eb0edaf88ac65f9ace9cf77c0be8c87d8e6b5f0414eb7"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 60, "exact": false, "function": "KPADInit", "fuzzy": 97.16216, "instructions": [185, 185], "label": "perm7c_t3_direct_degreesToRadians_init_before_sensitivity", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "2038677aa3661d6dae8e425d5ccecbc936a9d9ced058aa1cb0751dcc6120cb9c"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_direct_geometry_negative_center_test", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "8ba460b3e3512eeb08467762535be21c338c031652c2b5454bca699f171d2293"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 131, "exact": false, "function": "KPADInit", "fuzzy": 94.567566, "instructions": [183, 185], "label": "perm7c_t3_direct_geometry_width_absolute_center", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "dcefe7810c6203b734d4c1b1f03112f02348e1d6e39457a6f3b12f2e8bdce00c"}

- Source attempt {"build": 2, "error": "### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\perm7c-evaluate\\KPAD-candidate.c\n# ------------------------------------------------\n#    1528:     f32 referenceWidth = 1.0f; \n#   Error:     ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n", "function": "KPADInit", "label": "perm7c_t3_direct_width_declare_inside_channel", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "source_sha256": "7074cf3d59ecc458bd5765aeabde81109a3508a7430f6231e1b7b8cdfc369055"}

- Source attempt {"build": 2, "error": "### mwcceppc.exe Compiler:\n#    File: Z:\\tmp\\perm7c-evaluate\\KPAD-candidate.c\n# ------------------------------------------------\n#    1526:     f32 referenceHeight = 0.75f; \n#   Error:     ^^^\n#   (10141) expression syntax error\n#   Too many errors printed, aborting program\n\nUser break, cancelled...\n", "function": "KPADInit", "label": "perm7c_t3_direct_height_declare_inside_channel", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "source_sha256": "da8dd3ad9cb3dc547f2be6259096e15fafa62d1074f47b986b302c9ba7e6b6f7"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_direct_finite_float_sine_result", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "691581ebc3bb0a1c05540d03f72baf89c977de4d62a721f8684711640f6acf85"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_direct_channel_postincrement_test", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "7e54d62bb31ec019b288771d471a2f457536fca6ccfae9430dbac0107b3548ab"}
T3 KPADInit best 355 -> 345, elapsed231s; candidate still requires readable full-unit validation.
T3 manual follow-up completed46 full-unit trials outside the build tree, preserving repository sources. No exact improvement. Zi8GetElementCount remains99.347824%,115/115 instructions,13 register differences; ZiMatchZHSpelling remains98.80165%,121/121,29 register differences. Real declaration-order and counter/cursor scopes were tested; C89 rejects declaration-after-statement forms, which are discarded. KPADInit best readable variant uses reversed squared dimensions plus a double negative-sine temporary:98.297295%,185/185,47 differences, unchanged exact code12316 and data8032. Fuzzy variants are not retained.
T3 standalone345 hints are negative-sine helper/temporary forms. Helper for unary negation is rejected as unnecessary; the meaningful double temporary was already measured above and is not re-run.

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_0", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "017600e027b1f9bc7e7662b2d93abaa1a502ccf4b6a1b2d9630939b0bb112ed3"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_1", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a08f0279c290954da7d0ffda3df672a3dd8721d703b13211f898ed0f0a100b5c"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_2", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "fce22ed962d13e090af776c78965de9f19405d92eab1c1d4bb6430efc5c27eee"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_3", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "1459b70c1181c22bd02df431a6e96add869718af1be160f5e83e01a1eb5b234e"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_4", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "e4ccc001d55f6799398911fffc5e0ca3dec791abc6808367354b4cb176bfb031"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_5", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "790e2944077b296ff723a7fd6d20b094f959a3402dd9869a0e948270904f8204"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_6", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "26c2a57739aada06f53b619b14d905ed577561724b5b796c80969569217de556"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_7", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "aa981b5c0a5a3fb67c464ea16ac08c67e68b3e28df0a428b24e16fe602666aa9"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_8", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "9881d93c4995ea46f76183b686a0f9dfb3d67ee362ae38c7b6238fcdc25112e8"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_9", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d4ad8676fe86a904eb822b27e98b77d6bd447c3f5847c8cf939eb510fa3efe6b"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_10", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "eb9e29b877a118258a8cf201557ab5112b5ac4e30f01924d129ff7cf7585aa62"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_11", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "81950d76cde3e7ed6d2df762db462e94c50989b983df69fadf1c08c225d0ea5d"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_12", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "21fd8aa71c8d96b72fa543f929642b1a026a223da2a7648f838d1598cdd4266d"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_13", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "12545c3f0eed380169484ab7915e62840f26ae529f92d2174ec24fed1e3a0f6f"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_14", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "1792f7ed1b55bb14243d7f44b8a6ee84ec392261b6c864b194caf00d18062078"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_15", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "14ce6dffecf754f6ad29d9fbbff71381b9330d2d97aaf69e028fe32393ed3116"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_16", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "41db8c037b3d1e150bef0cb81e329f4e7faa81e4620061d343a3a2cf1fbf1d29"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_17", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "8892b4dd6614b26212e0ed1a5a37193387eea994b0fe043b8832dcdc3ae18d49"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_18", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d1e7f54fee27c192ff9d528fb8d47332a572554c71d5bc318bfbed3be78658b5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_19", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "1deb4ab042714dde2ec831937d6603ce6da152cd33f5f9cfb3adc9509738c6bf"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_20", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ade1ced7e5a1bb08b8b621d075e73f8d5b9763921eea34139ec3a9d4cf4b3556"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_21", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "0bf897fd59ad53878a2d6f8b5c3950c10cf71a1a2417e83f04014ad55bbcb0bf"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_22", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "b516fa14c68ea7817f206eed49c896f833ba3972cb6f1401fe021d90c652ee17"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_23", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "468cfebc1be5ed7e2a0dfab94896c44290e926dae22dfb9dffe7747af7737e3a"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_24", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d4d1691eff128907b28b188a281fd5988b14edc899fe1c9a18191dee34fc7e33"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_scalar_literal_25", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "05ddecac949d0dc2538b49f8dc2960e6ed6a780c55e9cf3e6c9d18635a1e1b13"}
T3 scalar literal follow-up:26 new canonical integer/double/float combinations of the three consumed scalar initializers. All compile with pool identical and data8032, score98.24324%,185/185 instructions,48 differences; no exact gain. Sources remain at recovery commit9cf16954. Completeness audit confirms KPADInit, Zi8GetElementCount and ZiMatchZHSpelling each have at least3 distinct built attempts; zi8InternalGetZH is explicitly out of scope in this task.

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instruction_exact_functions": 28, "instructions": [185, 185], "label": "perm7c_t3_global_mtx44_row_pointer", "method": "full-unit Mtx44 global type experiment, preserves64-byte matrix and no shared headers", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "regressed_functions": [], "source_sha256": "c7f2dd1310fda54e65730408a0aa41e15a8a62ec5789703063d27ab4e96687c7"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instruction_exact_functions": 28, "instructions": [185, 185], "label": "perm7c_t3_global_mtx44_direct_geometry", "method": "full-unit Mtx44 global type experiment, preserves64-byte matrix and no shared headers", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "regressed_functions": [], "source_sha256": "c2492f6604bf475d51b34fdb9b842ae1962a26cf113f68e0e982bb8b0e2182bb"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 58, "exact": false, "function": "KPADInit", "fuzzy": 97.810814, "instruction_exact_functions": 28, "instructions": [185, 185], "label": "perm7c_t3_global_mtx44_direct_original_layout", "method": "full-unit Mtx44 global type experiment, preserves64-byte matrix and no shared headers", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "regressed_functions": [], "source_sha256": "427b21b4ed0af4ea54ab461352b29750775029c500dc918372b9c7d057c50a52"}
T3 global matrix type check: modeled the existing64-byte array as Mtx44, with a row pointer and two direct-index source forms. All3 preserve data8032 and the existing28 instruction-exact functions, but KPADInit remains non-exact; no type change is kept. The generated candidates stay outside the repository.

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 122, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 92.85124, "instructions": [124, 121], "label": "perm7c_t3_c89_mismatch_scope_spellingCursor", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3a403251ae71d680cf6d24ef441850b3e481ce5714154309ba4d78f8a55a7780"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 122, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 92.85124, "instructions": [124, 121], "label": "perm7c_t3_c89_mismatch_scope_candidateCursor", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "bfe94f19622e38e29951f1bffb876f339a5629fc735c3600ebffee83daf9d6f0"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 122, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 92.85124, "instructions": [124, 121], "label": "perm7c_t3_c89_mismatch_scope_spellingCursor_candidateCursor", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ba9a4b24f952ad3c20306ea88b9899441f3dcae08448b5f404766b705df0f5fa"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 122, "exact": false, "function": "ZiMatchZHSpelling", "fuzzy": 92.85124, "instructions": [124, 121], "label": "perm7c_t3_c89_prefix_index_inner_scope", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "7ab555eaba423dc0d6f0b9f4c691b170292fba5256397cdf427b172aeb14d94f"}

- Source attempt {"build": 0, "code": "4168", "data": "24", "diffs": 114, "exact": false, "function": "Zi8GetElementCount", "fuzzy": 91.9913, "instructions": [119, 115], "label": "perm7c_t3_c89_result_initialize_at_counting_scope", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "02408b9816c0ef74798fe174519d8bb1edc149ea10e8e61e26f4f046c5872c47"}
T3 C89 scope repairs: declarations moved to the start of their real mismatch/counting blocks. All5 distinct variants build, but lexical scopes worsen code and data: spelling124/121 instructions with122 differences; element count119/115 with114 differences; data24 instead of144. No exact gain and no scope variant is kept. The original repository functions remain at121/121 with29 differences and115/115 with13 differences.

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 142, "exact": false, "function": "KPADInit", "fuzzy": 94.91892, "instructions": [186, 185], "label": "perm7c_t3_pointer_minimum_if", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "b81ce6bc7f7dfacb0005b35f7344db19f00234cc5d0cdb69cbfe128cbf4aa20c"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.54054, "instructions": [185, 185], "label": "perm7c_t3_pointer_minimum_comparison_reversed", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "3b3d130f22a7b66c1a24b6ba66033b2f83ad02fa2fc247aff699c9f68fcd4b19"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_t3_pointer_minimum_in_height", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "61b0f13affb19e8d19139249d89e168fb8788156eedd0a8a03773453f10a27c1"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 81, "exact": false, "function": "KPADInit", "fuzzy": 96.51351, "instructions": [185, 185], "label": "perm7c_t3_pointer_minimum_dimension_local", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "99280d1c91a3868a76c621f9e276959fe4ae3425af8f2ae4f617fa834c92c56f"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 135, "exact": false, "function": "KPADInit", "fuzzy": 95.432434, "instructions": [186, 185], "label": "perm7c_t3_direct_minimum_if", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "c7ab7b2d9c65be06c56287c934cc440358bca5199edf7f4c07418111380ab5f0"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 135, "exact": false, "function": "KPADInit", "fuzzy": 95.48649, "instructions": [186, 185], "label": "perm7c_t3_direct_minimum_if_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "6385ca80a139198b3d7055725f752e4082781a1185dd70edbc1c7dc161540854"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 50, "exact": false, "function": "KPADInit", "fuzzy": 98.16216, "instructions": [185, 185], "label": "perm7c_t3_direct_minimum_comparison_reversed", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a250c8130ba601598f74be12a33c271b218117c9c80ee2dfdd267ff8f4c35d10"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 49, "exact": false, "function": "KPADInit", "fuzzy": 98.21622, "instructions": [185, 185], "label": "perm7c_t3_direct_minimum_comparison_reversed_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "64482065547fe31380f7a2466b747606b39af0cc6b6c0024149180c69b0b9bac"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_direct_minimum_in_height", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "77d6a5d96cab1a31cc0c2a5b39416090c7376ad582399eb00b48158997e675b5"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 47, "exact": false, "function": "KPADInit", "fuzzy": 98.297295, "instructions": [185, 185], "label": "perm7c_t3_direct_minimum_in_height_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "d09d831c74f7eb288bb04f23294c369aa130e3f08281b3df889746d4782ca1dd"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 48, "exact": false, "function": "KPADInit", "fuzzy": 98.24324, "instructions": [185, 185], "label": "perm7c_t3_direct_minimum_dimension_local", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a443ad1ee83f37518f33232f119729a55f05d37fc5b70348a570865533aa53b0"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 47, "exact": false, "function": "KPADInit", "fuzzy": 98.297295, "instructions": [185, 185], "label": "perm7c_t3_direct_minimum_dimension_local_negative_sine", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "daa68b63ab543b1da476d09c2013c8c0bd4f294c08e4e3d80bb8c0bb16f43e75"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 155, "exact": false, "function": "KPADInit", "fuzzy": 90.22703, "instructions": [184, 185], "label": "perm7c_t3_pointer_width_from_unit_value", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "ad30183c3b3376723aa1f2f8b40cc079bb2f80e9edac1409dc15b8f3a6aff991"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 163, "exact": false, "function": "KPADInit", "fuzzy": 89.71892, "instructions": [184, 185], "label": "perm7c_t3_pointer_shared_unit_width_and_sensitivity", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "351718062c34a23a9366696560c4b9e047719af30ebde9d26288ef47614d28fa"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 153, "exact": false, "function": "KPADInit", "fuzzy": 91.28108, "instructions": [184, 185], "label": "perm7c_t3_direct_width_from_unit_value", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "9ebe422e661dad1361ac8cd99afa04bbf9e1b49b36d133cb52aaddd5a5dbc636"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 59, "exact": false, "function": "KPADInit", "fuzzy": 97.189186, "instructions": [185, 185], "label": "perm7c_t3_direct_unit_value_used_in_sensitivity", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "c82e87802b4e815e3360d7e93d1973d40cc1babeb06be58efd27aceb46c59354"}

- Source attempt {"build": 0, "code": "12316", "data": "8032", "diffs": 161, "exact": false, "function": "KPADInit", "fuzzy": 90.98919, "instructions": [184, 185], "label": "perm7c_t3_direct_shared_unit_width_and_sensitivity", "method": "full-unit source compiled outside build tree with ninja MWCC flags", "pool": "POOL IDENTICAL up to 0 (mine=0 base=0)", "source_sha256": "a1a98bf882a98f32bdb5de597d51bfadec3c25cabfc8f274080d763a34fea539"}
T3 minimum follow-up: 12 distinct full-unit source variants; no exact gain. Best 98.297295%; no variant retained. Minimum alternatives preserve unordered comparisons and include a real minimum-dimension temporary; unit-constant alternatives use the unit value for sensitivity or width, with every value assigned before use.
T3 unit-constant follow-up: 5 distinct full-unit source variants; no exact gain. Best 97.189186%; no variant retained. Minimum alternatives preserve unordered comparisons and include a real minimum-dimension temporary; unit-constant alternatives use the unit value for sensitivity or width, with every value assigned before use.
T3 search finished {"function": "KPADInit", "best": 345, "seconds": 2933, "exit": 0}
T3 final search audit: KPADInit ran2933seconds with one permuter job, score355 ->345, no improvement for2701seconds, clean exit0. The meaningful negative-sine temporary translates to98.297295%,185/185 instructions with47 differences; it does not count as an exact match. 97 new full-unit trials logged, 90 built; no new exact result or fuzzy-only source retained. Every requested open function has at least3 distinct built attempts. Existing recovery commit9cf16954 and both exact reads are preserved. All owned permuter processes stopped before the final clean build.

### T3 final clean full gate
```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVL_SDK/src/kpad/KPAD] pool: IDENTICAL
[libs/RVL_SDK/src/kpad/KPAD] objdiff: code 12316/13056 data 8032/8032 functions 28/29 fuzzy 99.8024 linked code 0
[libs/RVL_SDK/src/kpad/KPAD] instruction-exact functions: 28/29
[libs/RVL_SDK/src/kpad/KPAD]   section .bss size 7680 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .data size 88 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sbss size 32 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sdata size 112 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sdata2 size 120 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .text size 13056 match 99.80239
[libs/RVL_SDK/src/kpad/KPAD]   below 100: KPADInit 96.51351
[libs/RVL_SDK/src/kpad/KPAD] baseline: code 8880/13056 data 8032 functions 26 fuzzy 99.5156
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
global matched_code_percent: 91.55201 -> 91.66673
global fuzzy_match_percent: 99.69881 -> 99.70007
global complete_code_percent: 74.74593 -> 74.74593
global matched_data_percent: 99.55890 -> 99.55890
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
Fresh post-clean checks: both pools identical; exact-name objdiff read_kpad_acc100.0 and KPADRead100.0; ctxdiff0 at400/400 and459/459. Remaining KPADInit185/185 with81 differences, Zi8GetElementCount115/115 with13, ZiMatchZHSpelling121/121 with29. No fuzzy-only source is retained. Original KPAD recovery baseline26/29 ->28/29, code8880 ->12316, data8032 ->8032; this resumed run28/29 ->28/29 and zi8cgetc5/8 ->5/8, code4168 ->4168, data144 ->144. All source remains exactly at9cf16954. Open-function built-attempt coverage {"KPADInit": 154, "Zi8GetElementCount": 74, "ZiMatchZHSpelling": 56}. zi8InternalGetZH remains unchanged and explicitly excluded. All searches stopped.
