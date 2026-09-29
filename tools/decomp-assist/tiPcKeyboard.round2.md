# PC keyboard second pass

Baseline: 120/141 instruction-exact functions, 16240 code bytes, 5964 data bytes. Existing string pool and .rodata match. This pass changes code and data only; configure.py remains unchanged.

## LayoutByNW4R::initLayout
Start: (99.71429, (384, 385, 66, 0.9934980494148244)); .data=12552, .bss=12, .sdata2=29, .rodata=5816.
1. use a signed switch for the second language query and a common matrix-update join: (99.42857, (385, 385, 6, 0.9896103896103896)); .data=12552, .bss=12, .sdata2=29, .rodata=5816; pool identical; reverted.
2. hold language-mode visibility in a boolean and switch on the second query: (97.42857, (392, 385, 80, 0.9781209781209781)); .data=12552, .bss=12, .sdata2=29, .rodata=5816; pool identical; reverted.
3. hold each language query result in a named enum before dispatch: (99.42857, (385, 385, 6, 0.9896103896103896)); .data=12552, .bss=12, .sdata2=29, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::init
Start: (75.89773, (280, 352, 336, 0.7563291139240507)); .data=12552, .bss=12, .sdata2=29, .rodata=5816.
1. make the two immutable mode-selector positions function-static: (73.62784, (299, 352, 346, 0.7158218125960062)); .data=12552, .bss=36, .sdata2=29, .rodata=5816; pool identical; reverted.
2. use function-static mutable mode-selector vectors: (73.62784, (299, 352, 346, 0.7158218125960062)); .data=12552, .bss=36, .sdata2=29, .rodata=5816; pool identical; reverted.
3. initialize ordinary function-static VEC3 positions as aggregates: compiler rejected; reverted. at, float)' #   'nw4r::math::VEC3::VEC3(const nw4r::math::VEC3 &)' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

## LayoutByNW4R::init
Start: (75.89773, (280, 352, 336, 0.7563291139240507)); .data=12552, .bss=12, .sdata2=29, .rodata=5816.
1. initialize the two local positions as ordinary float arrays consumed by VEC3: (81.963066, (289, 352, 338, 0.7956318252730109)); .data=12552, .bss=12, .sdata2=9, .rodata=5840; pool identical; retained.
2. initialize positions as aggregate _VEC3 and construct the pane translation from its fields: (81.79261, (289, 352, 338, 0.7831513260530422)); .data=12552, .bss=12, .sdata2=9, .rodata=5840; pool identical; reverted.
3. construct both local VEC3 positions from ordinary coordinate arrays before language dispatch: (75.03409, (295, 352, 341, 0.7666151468315301)); .data=12552, .bss=12, .sdata2=9, .rodata=5840; pool identical; reverted.


## Vtable declaration order
Reordered class declarations to Base, EventHandler, UIObj, modifier, mode panel, layout, animation base, normal, shift, toggle, on/off. Ordinary compiler vtables are emitted in reverse declaration order, matching the target. No code-exact functions lost. {'fuzzy_match_percent': 95.17947, 'total_code': '28484', 'matched_code': '16240', 'matched_code_percent': 57.014465, 'total_data': '18564', 'matched_data': '148', 'matched_data_percent': 0.79724205, 'total_functions': 141, 'matched_functions': 120, 'matched_functions_percent': 85.106384, 'total_units': 1}
## LayoutByNW4R::initLayout
Start: (99.42857, (385, 385, 6, 0.9896103896103896)); .data=12576, .bss=12, .sdata2=9, .rodata=5816.
1. switch on mode flag with explicit default join: (100.0, (385, 385, 0, 1.0)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; retained.
2. unsigned mode temporary before test: (99.71429, (384, 385, 66, 0.9934980494148244)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; reverted.
3. explicit early join for nonzero mode: (99.71429, (384, 385, 66, 0.9934980494148244)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::createAnmPane_
Start: (98.515625, (192, 192, 55, 0.7135416666666666)); .data=12576, .bss=12, .sdata2=9, .rodata=5816.
1. declare the new pane before the animation table reference: (98.515625, (192, 192, 55, 0.7135416666666666)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; reverted.
2. cache the shared pane before allocating the animation pane: (98.5625, (192, 192, 118, 0.9270833333333334)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; retained.
3. use a full-width table index: (95.41146, (191, 192, 180, 0.6161879895561357)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; reverted.

## Base::sendInputWChar
Start: (98.24074, (107, 108, 104, 0.9488372093023256)); .data=12576, .bss=12, .sdata2=9, .rodata=5816.
1. assign input fields separately after the modifier calculation: (91.07407, (103, 108, 102, 0.8341232227488151)); .data=12576, .bss=12, .sdata2=9, .rodata=5800; pool identical; reverted.
2. compute conversion bits from named booleans: (93.05556, (110, 108, 106, 0.908256880733945)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; reverted.
3. initialize the input structure before testing keyboard modifiers: (76.31481, (107, 108, 101, 0.8186046511627907)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; reverted.

## Base::setTranslateMode
Start: (98.0, (107, 105, 89, 0.9528301886792453)); .data=12576, .bss=12, .sdata2=9, .rodata=5816.
1. initialize mode from its enum and preserve the named valid cases: (99.04762, (106, 105, 99, 0.995260663507109)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; retained.
2. use the existing mode as the fallback for an unknown translation mode: (95.2381, (106, 105, 97, 0.976303317535545)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; reverted.
3. convert valid translation modes directly after an unsigned range guard: (84.03809, (90, 105, 95, 0.6871794871794872)); .data=12576, .bss=12, .sdata2=9, .rodata=5816; pool identical; reverted.

## Base::KeyState::getWCCode u32
Start: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. compute modifier bits with conditional expressions: (80.024, (121, 125, 113, 0.8780487804878049)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. refer to the selected ASCII key before choosing its modifier: compiler rejected; reverted.            ^ #   (10224) 'const' or '&' variable needs initializer #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
3. use a named low mode for the Japanese punctuation condition: (97.56, (125, 125, 14, 0.92)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::refresh_
Start: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. use the mode setter for the Chinese and Korean normalization: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. switch on the language for mode normalization: (96.899445, (179, 179, 12, 0.9385474860335196)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. give the nested normalized-mode test a named value: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::getWCCode char*
Start: (96.14035, (56, 57, 18, 0.9203539823008849)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. use full-width indices in both name lookup loops: (83.68421, (56, 57, 52, 0.4424778761061947)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. write the ASCII lookup as a do-while loop: (94.29825, (57, 57, 21, 0.8771929824561403)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. cache the grid key before comparing its pane name: (86.82456, (54, 57, 37, 0.5045045045045045)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::getControlKey
Start: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. write the control lookup with a do-while loop: (90.55556, (37, 36, 20, 0.7397260273972602)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. cache the control table before the loop: (75.833336, (33, 36, 32, 0.5797101449275363)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use a full-width control index: (85.138885, (37, 36, 29, 0.7397260273972602)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::getWCCode
Start: (None, (56, 2, 56, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. take a named reference to the key state before forwarding: (None, (56, 2, 56, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. name the character returned by the key state: (None, (56, 2, 56, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. forward through a named key-state pointer: (None, (56, 2, 56, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onPressedShift
Start: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. hold the requested shift flags in a named local: (90.71429, (45, 49, 42, 0.8085106382978723)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. update the modifier state explicitly before refreshing: (89.591835, (45, 49, 41, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. isolate the key-state reference before setting shift: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onReleasedShift
Start: (89.871796, (38, 39, 36, 0.7532467532467533)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. name the cleared modifier bits before the setter: (90.0, (38, 39, 35, 0.7792207792207793)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. clear shift and mode bits in separate expressions: (89.871796, (38, 39, 36, 0.7532467532467533)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. update the key-state modifier explicitly before refreshing: (88.07692, (38, 39, 36, 0.7012987012987013)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::sendInputWChar
Start: (93.97727, (42, 44, 35, 0.9302325581395349)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. keep the shift bit in an unsigned local: (95.22727, (42, 44, 35, 0.9302325581395349)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. extract shift through the state accessor: (81.09091, (47, 44, 39, 0.8571428571428571)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. select the last animation pane with a conditional expression: (91.34091, (43, 44, 35, 0.8275862068965517)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::setInputModeJP
Start: (86.92208, (69, 77, 36, 0.8493150684931506)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. dispatch input mode using its unsigned type: (86.92208, (69, 77, 36, 0.8493150684931506)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. cache the key-state reference for both mode setters: (79.97403, (72, 77, 73, 0.5100671140939598)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. express the language-data selection with named mode tests: (83.68831, (69, 77, 36, 0.8356164383561644)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput int chan
Start: (95.25, (135, 140, 92, 0.88)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. name the held-shift condition before dispatch: (95.25, (135, 140, 92, 0.88)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. query shift through a pointer to the gather singleton: (95.25, (135, 140, 92, 0.88)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. test release state in two nested conditions: (95.25, (135, 140, 92, 0.88)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::refreshText
Start: (90.46154, (170, 169, 107, 0.8141592920353983)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. initialize captions through separate character assignments: (95.6213, (170, 169, 103, 0.8436578171091446)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. use full-width text table indices: (80.79881, (170, 169, 154, 0.5427728613569321)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. resolve each text pane before its dynamic cast: (89.27811, (170, 169, 123, 0.6194690265486725)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::create
Start: (87.49367, (151, 158, 106, 0.7637540453074434)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. keep the event handler in a typed local before assigning its owner: (87.49367, (151, 158, 106, 0.7637540453074434)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. resolve each modifier animation before its pane components: (80.82912, (151, 158, 114, 0.7443365695792881)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use the direct layout member for modifier pane searches: (86.75949, (151, 158, 107, 0.7637540453074434)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onKey
Start: (66.72967, (341, 418, 373, 0.6824769433465085)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. hold the control code before dispatching its cases: (66.72967, (341, 418, 373, 0.6824769433465085)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. dispatch the control code as a signed enum-sized value: (66.72967, (341, 418, 373, 0.6824769433465085)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. separate the key-release event and character checks: (66.72967, (341, 418, 373, 0.6824769433465085)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput HKBManager
Start: (84.687225, (237, 227, 219, 0.6724137931034483)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare the repeated key set separately from triggered keys: (81.92951, (233, 227, 220, 0.6565217391304348)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. declare triggered character and key before its animation pointer: (84.4141, (237, 227, 217, 0.646551724137931)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use a switch for repeated hardware control keys: (89.07929, (239, 227, 230, 0.6952789699570815)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.

## EventHandler::onTiEvent
Start: (88.83249, (196, 197, 176, 0.8600508905852418)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. dispatch the event with its unsigned parameter type: (88.83249, (196, 197, 176, 0.8600508905852418)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. write the repetition threshold with inclusive bounds: (88.862946, (196, 197, 176, 0.8702290076335878)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. split the initial modifier exclusions into early returns: (88.83249, (196, 197, 176, 0.8600508905852418)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onEvent
Start: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. return early for non-sound listener events: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. dispatch the sound listener event with a switch: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. hold the listener sound value in its enum type: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::refreshText
Start: (95.6213, (170, 169, 103, 0.8436578171091446)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. keep the converted ASCII character in a scalar until the text call: (94.30769, (170, 169, 105, 0.855457227138643)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. use a scalar caption and choose grid variants with a conditional index: (95.60947, (171, 169, 106, 0.8823529411764706)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. use a scalar caption and an explicit signed grid variant: (95.01183, (170, 169, 105, 0.8613569321533924)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::getControlKey
Start: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare the control entry reference before the loop index: (81.77778, (34, 36, 26, 0.6571428571428571)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. use a signed index with a 16-bit table-index conversion: (91.80556, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. declare the index before a while loop and increment explicitly: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::refreshText
Start: (95.60947, (171, 169, 106, 0.8823529411764706)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. load the scalar caption after the caps query and store it after conversion: (99.23077, (170, 169, 97, 0.9321533923303835)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. load the scalar caption after caps and use an explicit negated grid-mode integer: (98.15976, (169, 169, 80, 0.8816568047337278)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. load the scalar caption after caps and cast the computed grid selector to signed int: (97.92899, (169, 169, 78, 0.9053254437869822)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::init
Start: (74.650566, (279, 352, 339, 0.7385103011093502)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare the virtual base initializer inline in the owned implementation header: (92.639206, (342, 352, 261, 0.8645533141210374)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. declare the base initializer inline at its definition: (92.639206, (342, 352, 261, 0.8645533141210374)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. construct both local selector translations before selecting the language: (75.9375, (285, 352, 337, 0.750392464678179)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::init
Start: (92.639206, (342, 352, 261, 0.8645533141210374)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. construct both selector translations after the base initializer is declared inline: (93.09375, (348, 352, 265, 0.8742857142857143)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. copy selector positions into aggregate vectors before language dispatch: compiler rejected; reverted. at, float)' #   'nw4r::math::VEC3::VEC3(const nw4r::math::VEC3 &)' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
3. name both translations before the visibility setters: (89.161934, (348, 352, 282, 0.8742857142857143)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::refreshText
Start: (99.23077, (170, 169, 97, 0.9321533923303835)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. use a full-width temporary for the converted caption: (99.28994, (169, 169, 2, 0.9881656804733728)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. use a signed full-width temporary for caption comparisons: (97.86982, (169, 169, 6, 0.9644970414201184)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. normalize the caption temporary once after the case conversion: (98.69823, (170, 169, 100, 0.9616519174041298)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::init
Start: (93.09375, (348, 352, 265, 0.8742857142857143)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. copy ordinary aggregate positions into the base of each VEC3 translation: (93.09375, (348, 352, 265, 0.8742857142857143)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. copy each vector position as an ordinary 12-byte record: (93.610794, (342, 352, 261, 0.8760806916426513)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. copy aggregate positions with both vectors declared together: (93.09375, (348, 352, 265, 0.8742857142857143)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::refreshText
Start: (99.28994, (169, 169, 2, 0.9881656804733728)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. convert the scalar character back to wchar_t when indexing Korean maps: (100.0, (169, 169, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. convert the Korean map index to a 16-bit character difference: (96.86391, (169, 169, 6, 0.9644970414201184)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. use a named 16-bit character for each Korean lookup: (100.0, (169, 169, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::init
Start: (93.610794, (342, 352, 261, 0.8760806916426513)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. copy coordinate records and construct the pane translation at the point of use: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. copy coordinate records with const local positions: compiler rejected; reverted. ::keyboard::pctype::Base::getTranslateMode()  #   const' redefined #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
3. copy coordinate records before visibility setters: compiler rejected; reverted. ::keyboard::pctype::Base::getTranslateMode()  #   const' redefined #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

## LayoutByNW4R::init
Start: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. make both local selector records immutable: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. declare the pane vectors before copying the selector records: (98.14773, (358, 352, 224, 0.8985915492957747)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. declare selector records at function entry and assign them before language dispatch: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onKey
Start: (66.72967, (341, 418, 373, 0.6824769433465085)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. restore control case order from target jump-table destinations: (80.52631, (341, 418, 374, 0.8221343873517787)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. declare the caps-press handler inline while retaining target case order: (92.710526, (419, 418, 301, 0.9342891278375149)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. inline the caps-press body at its call site with target case order: (92.710526, (419, 418, 301, 0.9342891278375149)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.

## LayoutByNW4R::onKey
Start: (92.710526, (419, 418, 301, 0.9342891278375149)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. cache the shift gather at entry to the shift-control case: (99.98325, (418, 418, 3, 0.992822966507177)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. cache the shift gather and order active-button animation first: (100.0, (418, 418, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. cache the shift gather and split modifier-state condition: (99.98325, (418, 418, 3, 0.992822966507177)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.


## Final source selection
Reverted the early shared-pane load in createAnmPane_: its sequence-alignment score improved by shifting instructions, but the original candidate has the correct instruction order and only register differences. Reverted the named flags temporary in onPressedShift because it lowered the fuzzy score. All attempts above remain recorded.
The second aggregate-position copy in the typed-copy batch repeated the first aggregate trial; it was not a distinct attempt. The next two full-source position transforms were inserted incorrectly by the trial harness and rejected; neither was retained. The following stack batch contains the actual distinct local-lifetime attempts.
The inline onPressedCaps declaration trial was rejected because it removed the separately emitted real function. The explicit caps-control case retains that function and matches onKey. The case has its own scope.

## Final verification
Full gate: GATE PASS; regressions 0, forbidden additions 0, readability warnings 0. Instruction-exact functions 120 -> 123/141. Objdiff code 16240 -> 20128/28484; data 5964 -> 5972/18564. New exact functions: initLayout (385 instructions), refreshText (169), onKey (418). Every remaining function has at least three distinct source-level attempts above.

Pool: 204/204 identical. .rodata, .sdata, .sdata2, .sbss, .ctors: 100%. Ordinary coordinate records now occupy the missing 24 bytes at the end of the string-bearing data. Owned vtables have identical target offsets after declaration reordering. Raw .data is byte-identical, 12576 bytes; all 1303 relocation sites coincide, and 1302 resolve to the same named function or section offset. The sole remaining normalized relocation-name difference is the truncated target onEvent thunk. The .data objdiff score remains 74.95624; why its anonymous-symbol alignment gives so little credit remains uncertain. .bss has 12 source bytes versus 16 target bytes, both zero; likely extraction alignment, not proven. No padding or dummy data was added.

The invalid TranslateMode fallback uses its supplied enum value; the target default appears to use an unset temporary, whose intended behavior is unknown. configure.py stays NonMatching, as requested.

Remaining functions:
getWCCode__Q49textinput8keyboard6pctype4BaseFPc: None; Compiler inlines the key-state lookup into the forwarding wrapper; 56 versus 2 instructions.
getControlKey__Q49textinput8keyboard6pctype4BaseFPc: 93.333336; Only loop-index and table-offset register allocation differs; 36/36 instructions, 8 differences.
sendInputWChar__Q49textinput8keyboard6pctype4BaseFwb: 98.24074; Missing zero initialization instruction and cached flag loads; 107/108 instructions.
setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode: 99.04762; One extra mode-register move, caused by defined fallback initialization; 106/105 instructions.
refresh___Q59textinput8keyboard6pctype4Base8KeyStateFv: 98.77095; Compiler eliminates two mode reloads in normalization; 177/179 instructions.
getWCCode__Q59textinput8keyboard6pctype4Base8KeyStateFUl: 98.8; Cached modifier load and register allocation; 124/125 instructions.
getWCCode__Q59textinput8keyboard6pctype4Base8KeyStateFPc: 96.14035; Grid-mode expression loses one instruction; 56/57 instructions.
create__Q49textinput8keyboard6pctype12LayoutByNW4RFP12MEMAllocator: 87.49367; Compiler removes nullable multiple-inheritance pointer adjustments; 151/158 instructions.
createAnmPane___Q49textinput8keyboard6pctype12LayoutByNW4RFP12MEMAllocator: 98.515625; Only register allocation differs; 192/192 instructions, 55 differences.
init__Q49textinput8keyboard6pctype12LayoutByNW4RFv: 99.94886; Only selector-record and VEC3 temporary stack offsets differ; 352/352 instructions, 18 differences.
onPressedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFb: 90.81633; Inlined setter removes repeated flag loads; 45/49 instructions.
onReleasedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFv: 90.0; Merged mask expression and eliminated flag reload; 38/39 instructions.
sendInputWChar__Q49textinput8keyboard6pctype12LayoutByNW4RFwb: 95.22727; Shift-bit test and FIFO pointer handling; 42/44 instructions.
setInputModeJP__Q49textinput8keyboard6pctype12LayoutByNW4RFbUlUl: 86.92208; Mode setters share conditions and remove repeated dispatch; 69/77 instructions.
updateInput__Q49textinput8keyboard6pctype12LayoutByNW4RFiffUlUlUlPv: 95.25; Inlined shift setters remove repeated flag loads; 135/140 instructions.
updateInput__Q49textinput8keyboard6pctype12LayoutByNW4RFRQ39textinput5input10HKBManager: 89.07929; KeySet aggregate stack allocation and control dispatch; 239/227 instructions.
onTiEvent__Q49textinput8keyboard6pctype12EventHandlerFPQ39textinput3gui13PaneComponentUlPQ49textinput11nw4rmanager14TiEventHandler5Input: 88.862946; Event branching, one missing instruction, and register allocation; 196/197 instructions.
@236@onEvent__Q49textinput8keyboard6pctype12LayoutByNW4RFPQ49textinput8keyboard6pctype5: None; Original symbol name is truncated; canonical compiler thunk has the same two instructions under its full signature.
