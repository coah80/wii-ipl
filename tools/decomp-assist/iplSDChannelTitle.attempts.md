# SDChannelTitle attempts

Unit: `src/scene/sdChannelTitle/iplSDChannelTitle`, Wii Menu 4.3U.
All 69 original functions have C++ definitions. The source follows original object order;
the 55-string pool is identical. The unit remains NonMatching.

The default gate baseline `70970038` is absent from this checkout. Checks use the
available ancestor `e265d9664e73912f2dbf8dd02425f9dc64eac55b` through the gate's
supported `--base` option. Its unit baseline is zero instruction-exact functions.

## Initial remaining functions

| Function | Distinct source attempts | Final instruction evidence |
| --- | --- | --- |
| `calcFadein` | Reversed fade-playing branch; cached event-handler pointer; explicitly typed null callback; named fade-playing condition. The latter three all kept 48/47 instructions. | One extra `li r5,0` for the declared unused second `SDButton::setEventHandler` argument. |
| `initCalcFadeout` | Cached empty handler (50/49); explicitly typed null arguments (50/49); reloaded SDButton directly at cleanup (54/49, reverted). | One extra `li r5,0` for the same unused argument. |
| `813E6CCC` | Combined positive early-return guards corrected the final animation branch; passed the actual title-range output pointer; cached title halves (89/86); cached selector (88/86); named enqueue result (87/86). Reverted the latter three. | 87/86; explicit ignored controller argument adds `li r4,0`; call setup also schedules differently. |
| `813E6E24` | Explicit range copies replaced reference-only arguments; reversed usage-enough branch; combined positive early-return guards; named copied ranges and cached memory receiver; reversed copy declaration order and original range declaration order. Named copies produced 6, 8, or 9 differing instructions; restored temporary copies. | 95/95; five differences in copy-load register selection and receiver/argument setup order. |
| `813E7074` | Reversed title comparison operands and copied-title branch; cached title halves (77/76); cached selector (77/76); named enqueue result (77/76). Reverted the latter three. | 77/76; explicit ignored controller argument adds `li r4,0`, with argument-move ordering differing. |
| `813E8A20` | Supplied page/index output locals to `hasChannel`; stored the SD previous page through a scoped inline setter; evaluated save heap separately; used a scoped reference accessor instead of the setter. | 37/37; six register/load-order differences around save-manager and heap access. |

## Resolved iterations

Constructor, destructor/thunk, layout creation, common calculation, normal calculation,
fadeout calculation, drawing, destruction, reset checks and most state handlers now
match instruction-exactly. Notable successful source changes were:

- Original function order and event-case order restored all pooled strings.
- Explicit nullable-file checks reproduced virtual-destructor branches.
- Dialog last-result access corrected offset 0x24.
- Arrow visibility access used the real byte at offset 0x81.
- Text-pane names used a normal pointer table instead of direct literals.
- Named pane-handler and text-box temporaries restored allocation/call order.
- Script-data aggregate initialization and a real low-title-ID mask restored 120/120 instructions.
- Script-state heap-index temporary restored register selection.
- Separate result switch cases preserved the original dispatch tree.
- Event switches and a hover-count reference restored both event handlers.
- Combined positive early-return scene-state checks restored script calculation (66/66).
- Named capture-dimension table restored the full .rodata section.
- Fadeout used two-byte maker-code access and separately timed vector construction.

## Layout and interface uncertainties

The 0x800 bytes following the title-range output are preserved as opaque scene work
storage; their internal type is not recovered. This is instance layout, not linker padding.
The embedded SDMemory's original following-member offset requires size 0x2a78; its
existing header's unused 16-byte tail is excluded only for this translation unit.

The original nonconst `isResetAcceptable` symbol differs from Base's existing const
virtual declaration. This needs review before linking. The event handler classes use
ordinary forwarding virtual methods, whose weak metadata may differ from the original.
The original extracted object's weak data can be zero-filled after linker deduplication;
no artificial data or force-active workaround was added.

The two notice APIs declare an ignored controller argument that the target callers do
not initialize. The source supplies zero rather than depending on an uninitialized value.
The title-range output pointer is passed as the fourth channel-notice argument.

## Continuation from merged main

Starting main: `fcb5be85f76b17b4341b6868b768f22ded14f8e7`.
Its gate baseline became available during this continuation, so the final check uses
ordinary `origin/main`, with 63/69 exact functions and 17064/18624 matched code bytes.

`813E6E24` now has 95/95 instructions and zero differences. An inline helper takes
both title ranges by value, preserving the copies while evaluating the memory receiver
before their loads. This changes no other translation unit and adds no out-of-line helper.
The string pool remains identical.

Fresh attempts for every function still open:

| Function | Attempt 1 | Attempt 2 | Attempt 3 | Retained result |
| --- | --- | --- | --- | --- |
| `813E8A20` | Cached save manager through the flush: 36/37 instructions, missing reload. | Named previous-page reference: 37/37, same six differences. | Read save heap before the page store: 37/37, reordered loads and six differences. | Original 37/37, six register/load-order differences. Also tried guarded direct field access and an inline save-page helper; neither improved it. |
| `calcFadein` | Scoped inline SDButton method body: 51/47, virtual call expanded. | Scoped inline body with NO_INLINE: 48/47, null callback argument remains. | Scoped inline body using a named gui-manager receiver: 51/47, same expanded virtual call. | Original 48/47; all header trials reverted. |
| `initCalcFadeout` | Scoped inline SDButton method body: 52/49, virtual call expanded. | Scoped inline body with NO_INLINE: 50/49, null callback argument remains. | Scoped inline body using a named gui-manager receiver: 52/49, same expanded virtual call. | Original 50/49; all header trials reverted. |
| `813E6CCC` | Inline notice wrapper with title ID and range parameters: 87/86, unchanged call setup. | Title-ID union with named words: 91/86, extra stores and loads. | Named enqueue result and failure early return: 87/86, result branches also differed. | Original 87/86; extra ignored-controller initialization and argument setup differences. |
| `813E7074` | Inline notice wrapper with title ID and state parameters: 77/76, unchanged. | Title-ID union with named words: 77/76, worse register and stack allocation. | Named enqueue result and failure early return: 77/76, result branches also differed. | Original 77/76; extra ignored-controller initialization and argument move order. |

All unsuccessful source and shared-header trials were reverted. The retained source
change is the by-value range helper and its call. The unit remains NonMatching because
five functions still differ; the condition for trying a Matching link has not been reached.
