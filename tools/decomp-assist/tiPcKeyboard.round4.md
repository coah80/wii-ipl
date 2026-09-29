# PC keyboard fourth pass

Baseline: 129/141 instruction-exact functions, 22828 code bytes, 5972 data bytes. Existing string pool and .rodata match. This pass changes code and data only; configure.py remains unchanged.

## LayoutByNW4R::updateInput HKBManager
Start: (99.73568, (227, 227, 1, 0.9955947136563876)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. signed scalar for Korean conversion: (98.67841, (227, 227, 5, 0.9779735682819384)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. 16-bit Korean scalar: (97.48898, (228, 227, 145, 0.8967032967032967)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. signed 16-bit conversion result: (99.73568, (227, 227, 1, 0.9955947136563876)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
4. declare Korean result before caps query: (97.9956, (227, 227, 26, 0.9383259911894273)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::init
Start: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. name vector inside each language branch: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. bind each constructed vector to const reference: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. reverse copy declarations with original assignment order: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::init
Start: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. populate named language vectors componentwise before SetTranslate: (99.96591, (352, 352, 12, 0.9659090909090909)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. declare language vectors in language order: (99.94886, (352, 352, 18, 0.9488636363636364)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput HKBManager
Start: (99.73568, (227, 227, 1, 0.9955947136563876)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. extract Korean conversion as typed inline helper: (99.73568, (227, 227, 1, 0.9955947136563876)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::setTranslateMode
Start: (99.04762, (106, 105, 99, 0.995260663507109)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. initialize fallback in default switch arm: (98.0, (107, 105, 89, 0.9528301886792453)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. switch signed translation mode: (99.04762, (106, 105, 99, 0.995260663507109)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. enum-typed translated key mode: (99.04762, (106, 105, 99, 0.995260663507109)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::getWCCode u32 index
Start: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. load modifiers with combined shift expression: (81.624, (117, 125, 115, 0.9008264462809917)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. index character table through a named entry: compiler rejected; reverted.            ^ #   (10224) 'const' or '&' variable needs initializer #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
3. switch direct punctuation characters: (81.44, (129, 125, 110, 0.7795275590551181)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::refresh_
Start: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. normalize kana mode with explicit language cases: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. assign normalized mode through inline setter: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. copy normalized mode into named flags value: (98.77095, (177, 179, 152, 0.9606741573033708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::init
Start: (99.96591, (352, 352, 12, 0.9659090909090909)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. reverse record declarations after named vectors and preserve load order: (100.0, (352, 352, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.

## Base::getControlKey
Start: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare control record reference through pointer before loop: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. declare table index before a while loop: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. compare named pane record outside condition: (93.333336, (36, 36, 8, 0.8055555555555556)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::getWCCode
Start: (None, (57, 2, 57, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. bind KeyState through owner pointer: (None, (57, 2, 57, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. name character result before returning: (None, (57, 2, 57, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. bind named KeyState reference: (None, (57, 2, 57, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Base::KeyState::getWCCode u32 index
Start: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. use named ASCII record with correct table type: (98.8, (124, 125, 109, 0.9236947791164659)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onPressedShift
Start: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. name requested shift flags: (90.71429, (45, 49, 42, 0.8085106382978723)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. bind shift button before changing flag state: compiler rejected; reverted.   ^^^^^^^^^^^^^^ #   (10140) undefined identifier 'ModifierButton' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
3. return when shift sound is disabled: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onReleasedShift
Start: (90.0, (38, 39, 35, 0.7792207792207793)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. bind modifier button then clear flag state: compiler rejected; reverted.   ^^^^^^^^^^^^^^ #   (10140) undefined identifier 'ModifierButton' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
2. early return for already released modifier: (90.0, (38, 39, 35, 0.7792207792207793)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. clear flags using named masks: (90.0, (38, 39, 35, 0.7792207792207793)); .data=12576, .bss=12, .sdata2=16, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::updateInput int chan
Start: (95.25, (135, 140, 92, 0.88)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. make hardware shift condition unsigned explicit: (95.25, (135, 140, 92, 0.88)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. use conditional-return release test: (95.25, (135, 140, 92, 0.88)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. bind gather as pointer: (95.25, (135, 140, 92, 0.88)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::create
Start: (87.49367, (151, 158, 106, 0.7637540453074434)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare modifier names before pane manager queries: (88.696205, (151, 158, 102, 0.7766990291262136)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. bind shift and caps button references: compiler rejected; reverted.   ^^^^^^^^^^^^^^ #   (10140) undefined identifier 'ModifierButton' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 
3. store handler in typed local before member assignment: (87.49367, (151, 158, 106, 0.7637540453074434)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onEvent
Start: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. signed event switch: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. early return for non-sound event: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. name sound identifier: (None, (0, 0, 100000, 0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onPressedShift
Start: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. bind correctly typed shift button before state refresh: (90.81633, (45, 49, 42, 0.7872340425531915)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::onReleasedShift
Start: (90.0, (38, 39, 35, 0.7792207792207793)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. bind correctly typed modifier button across state refresh: (90.0, (38, 39, 35, 0.7792207792207793)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::create
Start: (88.696205, (151, 158, 102, 0.7766990291262136)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. bind correctly typed shift and caps button references: (90.43671, (151, 158, 122, 0.6213592233009708)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

Named onPressedShift flag temporary restored after review: fuzzy score fell 90.81633 to 90.71429, no instruction-count improvement. Compiler-rejected misspelled types do not count toward the three valid experiments.

## Base::getWCCode
Start: (None, (57, 2, 57, 0.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. use existing NO_INLINE convention for real outlined KeyState name lookup: (100.0, (2, 2, 0, 1.0)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.

## LayoutByNW4R::create
Start: (88.696205, (151, 158, 102, 0.7766990291262136)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. convert layout freshly for each modifier and mode panel: (96.582275, (158, 158, 29, 0.8227848101265823)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
2. scope each modifier layout binding independently: (94.01899, (158, 158, 34, 0.8037974683544303)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. extract modifier creation into reusable inline member: compiler rejected; reverted. ete struct/union/class  #   'textinput::keyboard::pctype::AnmPane' #   Too many errors printed, aborting program  User break, cancelled... ninja: build stopped: subcommand failed. 

## LayoutByNW4R::create
Start: (96.582275, (158, 158, 29, 0.8227848101265823)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. declare layout and manager bindings at function entry: (96.55064, (158, 158, 30, 0.8164556962025317)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. declare first modifier names before layout conversion: (99.082275, (158, 158, 27, 0.8291139240506329)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; retained.
3. declare all modifier name bindings before calls: (96.55064, (158, 158, 30, 0.8164556962025317)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## LayoutByNW4R::create
Start: (99.082275, (158, 158, 27, 0.8291139240506329)); .data=12576, .bss=12, .sdata2=8, .rodata=5816.
1. reuse bounding name for both modifier setup blocks: (99.05064, (158, 158, 28, 0.8227848101265823)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
2. declare shared bounding name before allocator calls: (99.05064, (158, 158, 28, 0.8227848101265823)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.
3. reuse pane and bounding names together: (97.341774, (158, 158, 32, 0.7911392405063291)); .data=12576, .bss=12, .sdata2=8, .rodata=5816; pool identical; reverted.

## Data review

The string pool still matches all 204 entries. Raw .data matches all 12576 bytes, including pane-animation tables, jump tables, selector positions, and vtables in target order. Every one of the 1303 relocation sites coincides. After normalizing data symbols to section offsets and code symbols to demangled-equivalent names, 1302 relocation destinations agree. The remaining destination at .data+0x2fb8 is the compiler-generated LayoutByNW4R::onEvent thunk, whose target symbol name ends midway through its UIObj argument. Source thunk includes the complete UIObjUlPv suffix. Both thunks contain the same two instructions. No names or configuration were altered to hide this.

.rodata 5816 bytes, .sdata2 8 bytes, .sdata, .sbss, and .ctors remain 100% by objdiff. The source .bss has one 12-byte anonymous zero object; target has one 16-byte anonymous zero object. Both sections align to eight bytes. Source .sdata ends at 133 bytes and .sbss at five; target ends at 136 and eight. The trailing zero differences are consistent with extraction alignment, but their origin is unproven. No padding objects were introduced. .data fuzzy score remains 74.95624 despite identical raw bytes and nearly identical canonical relocations; objdiff symbol correspondence is a possible cause, not a proven fix.

## Final review

KeyState name lookup uses the existing repository NO_INLINE convention to preserve its real outlined call. Its standalone implementation remains exact. init declares two genuine translation vectors and populates all three components before either vector is read. No uninitialized values are used. Fresh base conversions in create preserve the nullable multiple-inheritance conversions present in the target. configure.py remains NonMatching and unchanged.

Final measures: {'fuzzy_match_percent': 99.63207, 'total_code': '28484', 'matched_code': '24244', 'matched_code_percent': 85.11445, 'total_data': '18564', 'matched_data': '5972', 'matched_data_percent': 32.169792, 'total_functions': 141, 'matched_functions': 131, 'matched_functions_percent': 92.90781, 'total_units': 1}

getControlKey__Q49textinput8keyboard6pctype4BaseFPc: 93.333336; (36, 36, 8, 0.8055555555555556)
setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode: 99.04762; (106, 105, 99, 0.995260663507109)
refresh___Q59textinput8keyboard6pctype4Base8KeyStateFv: 98.77095; (177, 179, 152, 0.9606741573033708)
getWCCode__Q59textinput8keyboard6pctype4Base8KeyStateFUl: 98.8; (124, 125, 109, 0.9236947791164659)
create__Q49textinput8keyboard6pctype12LayoutByNW4RFP12MEMAllocator: 99.082275; (158, 158, 27, 0.8291139240506329)
onPressedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFb: 90.81633; (45, 49, 42, 0.7872340425531915)
onReleasedShift__Q49textinput8keyboard6pctype12LayoutByNW4RFv: 90.0; (38, 39, 35, 0.7792207792207793)
updateInput__Q49textinput8keyboard6pctype12LayoutByNW4RFiffUlUlUlPv: 95.25; (135, 140, 92, 0.88)
updateInput__Q49textinput8keyboard6pctype12LayoutByNW4RFRQ39textinput5input10HKBManager: 99.73568; (227, 227, 1, 0.9955947136563876)
@236@onEvent__Q49textinput8keyboard6pctype12LayoutByNW4RFPQ49textinput8keyboard6pctype5: None; (0, 0, 100000, 0)

At least three compiling, distinct source-level experiments were run for each of the twelve functions unmatched at entry. Compiler-rejected experiments are retained as diagnostics and excluded from that count. Two functions are now instruction-exact. The remaining create differences are exclusively register assignments, with 158/158 instructions and matching operations. The remaining KeyState refresh/character lookup and modifier input differences include compiler-eliminated repeated flag loads. setTranslateMode still has one extra move from its defined fallback for invalid enum values; the target fallback behavior is uncertain.
