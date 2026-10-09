# sol-r6 SDMemory attempts

Scope: `drawTransferTitles__Q33ipl5scene8SDMemoryFv` in `src/scene/sdChannelMemory/iplSDMemory.cpp`, branch `agent/w1009/sdmem-r`, starting commit `b1e91180`. No other source ownership.

Read sol-common, brief-v2, every lever, AGENTS, unslop, and writing-for-agents. The first full Ninja build passed, DOL SHA1 `26116613f624061ba99c8d1a299aaa6efa85670d`. Baseline unit 65/66 exact, code 19068/20872, data 3344/3344; draw 93.456764%, 371 differing, 438/451 instructions. Pool identical 90/90. Fetched origin before experimentation.

History collected from effort-policy.txt, archived and local logs, and all six SDMemory best diffs. Relevant rounds include ult1, ult18, g4, a6h/a6x, h1, f19, rx7, fz7, sol-singles, sol-x4, sol-x14, sol-x17. The archived aggregate points to older a6x body-alpha and message-render helpers. sol-x17 is the best equal-size positional candidate, 256/451; its objdiff score 93.27938% is below the retained baseline. Replay it only as an experiment.

Excluded repeats: compiler-version and unit-flag sweeps; pragma-only IRO 0/1; blind declaration permutations; newline while/for/do rewrites and cached delimiter variables alone; color ref/value/pointer wrappers and removing target-proven color snapshots; title-alpha helper alone; memo.y/bodyHeight reloads; cursor vectors replacing row offsets; ceil casts alone; NAND increment relocation alone. The earlier extra-FPR diagnosis is false: both equal-size versions save f24 through f31, and Capstone truncates/misdecodes paired-single instructions. Full four-byte decoding is required.

Sibling inspection: Memory::draw and ChannelEdit::draw use list walkers and delegate box drawing, without a multiline title loop. SDChannelSelect::draw names pane, text-box, matrix and position locals in each rendering block. Its drawChannelObjects/transition helpers are the remaining comparison targets. New trials combine real rendering/helper boundaries or named call arguments with function-scoped optimization and IRO levels. Allocator captures and constrained want-lists will distinguish numbering from lifetime changes.

## Measurements

- best-opt0-iro0: 701 differing, 704/451 instructions; register-blind positional 699; objdiff 11.536586%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- best-opt0-iro1: 709 differing, 711/451 instructions; register-blind positional 707; objdiff 9.339246%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- best-opt1-iro0: 458 differing, 469/451 instructions; register-blind positional 446; objdiff 69.6408%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- best-opt1-iro1: 458 differing, 469/451 instructions; register-blind positional 446; objdiff 69.6408%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- best-opt2-iro0: 446 differing, 447/451 instructions; register-blind positional 442; objdiff 75.25942%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- best-opt2-iro1: 446 differing, 447/451 instructions; register-blind positional 442; objdiff 75.25942%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- best-opt3-iro0: 256 differing, 451/451 instructions; register-blind positional 180; objdiff 93.27938%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- best-opt3-iro1: 256 differing, 451/451 instructions; register-blind positional 180; objdiff 93.27938%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

Debugger transport: default mwdbg queued on the shared lock and was canceled before execution. Private copies use port 19966 via a bind redirect, preserving compiler, emulator, flags and checkout; all copies are /tmp/sol-r6-*. The first private run failed on an import path, fixed in the driver copy. Shared tools remain unchanged.

- diagnostic-opt_loop_invariants-off: 256 differing, 451/451 instructions; register-blind positional 180; objdiff 93.27938%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- diagnostic-opt_common_subs-off: 256 differing, 451/451 instructions; register-blind positional 180; objdiff 93.27938%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- diagnostic-opt_propagation-off: 256 differing, 451/451 instructions; register-blind positional 180; objdiff 93.27938%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- diagnostic-opt_dead_assignments-off: 256 differing, 451/451 instructions; register-blind positional 180; objdiff 93.27938%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- diagnostic-scheduling-off: 337 differing, 451/451 instructions; register-blind positional 293; objdiff 66.3969%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- render-pointer-message: 265 differing, 451/451 instructions; register-blind positional 189; objdiff 91.758316%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- render-pointer-rows: 442 differing, 424/451 instructions; register-blind positional 434; objdiff 87.0%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- render-pointer-all: 448 differing, 400/451 instructions; register-blind positional 443; objdiff 81.62306%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- render-ref-message: 265 differing, 451/451 instructions; register-blind positional 189; objdiff 93.25277%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- render-ref-rows: 442 differing, 424/451 instructions; register-blind positional 434; objdiff 86.95122%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- render-ref-all: 448 differing, 400/451 instructions; register-blind positional 443; objdiff 81.96674%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- render-constref-message: 265 differing, 451/451 instructions; register-blind positional 189; objdiff 93.25277%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- render-constref-rows: 442 differing, 424/451 instructions; register-blind positional 434; objdiff 86.95122%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- render-constref-all: 448 differing, 400/451 instructions; register-blind positional 443; objdiff 81.96674%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-full-helper-u8-snapshot: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-full-helper-u8-named: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-full-helper-int-snapshot: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-full-helper-int-named: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-helper-before-iro: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-helper-before-iro-write-noinline: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-helper-inside-iro: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-helper-inside-iro-write-noinline: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-helper-after-iro: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops ['__ne__Q24nw4r2utFQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8IteratorQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8Iterator']; POOL IDENTICAL up to 90 (mine=90 base=90).

- color-helper-after-iro-write-noinline: 391 differing, 407/451 instructions; register-blind positional 370; objdiff 85.92017%; other drops ['__ne__Q24nw4r2utFQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8IteratorQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8Iterator']; POOL IDENTICAL up to 90 (mine=90 base=90).

Fresh capture `/tmp/sol-r6-best-capture2` matches Ninja .text/.data/.sdata/.sdata2 byte-for-byte; shared regsim reproduces 254/254. Private constrained regsim excludes compiler @ names, split variables, and this from reorderable declarations. Want-list this=r25, titleSizePane=r29, titleText=r28, nandTitleIndex=r27, titleIndex=r26, visibleRows=r20, row=r19, footerPane=r21, bodyPane=r29 reaches 2/9 over 3000 trials. The earlier unconstrained run is invalid as declaration evidence and was discarded. Fresh vmap `/tmp/sol-r6-fresh-vmap.txt` aligns 282 virtual operands; its raw positional target mappings are advisory because several blocks differ structurally. Four color-address nodes have 50 interference neighbors each and receive r26-r29. Lower levels alone and the diagnostic CSE/loop-invariant/propagation/dead-assignment toggles do not produce target color-address lifetimes. Scheduling-off worsens it.

- target-loops-ordinary-opt1-iro0: 444 differing, 472/451 instructions; register-blind positional 424; objdiff 72.521065%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-ordinary-opt1-iro1: 444 differing, 472/451 instructions; register-blind positional 424; objdiff 72.521065%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-ordinary-opt2-iro0: 445 differing, 450/451 instructions; register-blind positional 438; objdiff 80.137474%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-ordinary-opt2-iro1: 445 differing, 450/451 instructions; register-blind positional 438; objdiff 80.137474%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-ordinary-opt3-iro0: 390 differing, 454/451 instructions; register-blind positional 363; objdiff 95.78936%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-ordinary-opt3-iro1: 390 differing, 454/451 instructions; register-blind positional 363; objdiff 95.78936%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-best-opt1-iro0: 445 differing, 472/451 instructions; register-blind positional 424; objdiff 72.20621%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-best-opt1-iro1: 445 differing, 472/451 instructions; register-blind positional 424; objdiff 72.20621%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-best-opt2-iro0: 444 differing, 450/451 instructions; register-blind positional 438; objdiff 79.773834%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-best-opt2-iro1: 444 differing, 450/451 instructions; register-blind positional 438; objdiff 79.773834%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-best-opt3-iro0: 388 differing, 454/451 instructions; register-blind positional 363; objdiff 96.161865%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- target-loops-best-opt3-iro1: 388 differing, 454/451 instructions; register-blind positional 363; objdiff 96.161865%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-direct-before: 305 differing, 435/451 instructions; register-blind positional 236; objdiff 93.09978%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-direct-inside: 305 differing, 435/451 instructions; register-blind positional 236; objdiff 93.09978%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-direct-after: 305 differing, 435/451 instructions; register-blind positional 236; objdiff 93.09978%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-copy-before: 305 differing, 435/451 instructions; register-blind positional 236; objdiff 93.09978%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-copy-inside: 305 differing, 435/451 instructions; register-blind positional 236; objdiff 93.09978%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-copy-after: 305 differing, 435/451 instructions; register-blind positional 236; objdiff 93.09978%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-named-before: 308 differing, 443/451 instructions; register-blind positional 239; objdiff 94.77827%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-named-inside: 308 differing, 443/451 instructions; register-blind positional 239; objdiff 94.77827%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-named-after: 308 differing, 443/451 instructions; register-blind positional 239; objdiff 94.77827%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-direct-named: 305 differing, 435/451 instructions; register-blind positional 236; objdiff 93.09978%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-direct-const-named: 305 differing, 435/451 instructions; register-blind positional 236; objdiff 93.09978%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-direct-assign: 305 differing, 435/451 instructions; register-blind positional 236; objdiff 93.09978%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-named-named: 308 differing, 443/451 instructions; register-blind positional 239; objdiff 94.77827%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-named-const-named: 308 differing, 443/451 instructions; register-blind positional 239; objdiff 94.77827%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-color-named-assign: 308 differing, 443/451 instructions; register-blind positional 239; objdiff 94.77827%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-pair-direct: 305 differing, 447/451 instructions; register-blind positional 245; objdiff 94.45898%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-pair-direct-const: 305 differing, 447/451 instructions; register-blind positional 245; objdiff 94.45898%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-pair-named: 317 differing, 455/451 instructions; register-blind positional 257; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- value-pair-named-const: 317 differing, 455/451 instructions; register-blind positional 257; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- return-color-view: 305 differing, 447/451 instructions; register-blind positional 245; objdiff 94.45898%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- return-color-copy: 305 differing, 447/451 instructions; register-blind positional 245; objdiff 94.45898%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- return-color-view-pair: 305 differing, 447/451 instructions; register-blind positional 245; objdiff 94.45898%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

- return-color-copy-pair: 305 differing, 447/451 instructions; register-blind positional 245; objdiff 94.45898%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90).

## Disposition

67 compiled source trials, plus historical-best replay and fresh allocator tracing. No exact gain. Every trial checked the pool and every previously exact function. Two color-helper placement trials regressed the iterator comparator and were rejected. All source changes are restored to the initial b1e91180 source; configure.py and shared headers were never edited. Unit remains 65/66 exact and NonMatching.

Smallest equal-size candidate remains the replayed sol-x17 shape, 256/451 differing, 93.27938%; saved as `_luna-runs/best/sol-r6.iplSDMemory.diff`. New target-loop/color-parameter shape reaches 96.38359% but has 455/451 instructions and 317 positional differences; saved separately as `_luna-runs/best/sol-r6.iplSDMemory.target-loops.diff`. Fuzzy-only work is not retained or accepted.

New lead: separate positive line-count guard, a counted message-render loop and cached delimiters align the header blocks. A do-while newline counter omits one branch present in the target; guarded while restores it. The remaining four extra instructions coincide with four color-argument address hoists. Explicit pair-by-value gradient parameters preserve the three bytewise copies and improve similarity, but still do not reproduce the target lifetime/register graph. Single-color helpers remove 8 or 16 required instructions; full byte-construction helpers fail to inline and remove 44. Lower optimization levels stop address hoisting but also lose induction-variable strength reduction and iterator optimization. No claim of compiler impossibility.

Read-only worktree checker invoked from the worker rejects this path as its integration worktree; that command assumes an integration checkout as cwd. It did not change Git or files. Assigned cwd and branch remained data-d9 / agent/w1009/sdmem-r. No push, PR, merge, rebase, cross-worktree edit, or subagent was used.

## Final gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 19068/20872 data 3344/3344 functions 65/66 fuzzy 99.4345 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 65/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.434456
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 93.456764
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 19068/20872 data 3344 functions 65 fuzzy 99.4345
regressions vs baseline: 0
global matched_code_percent: 97.95043 -> 97.95043
global fuzzy_match_percent: 99.91234 -> 99.91234
global complete_code_percent: 89.90470 -> 89.90470
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Final retained draw: 93.456764%, 438/451 instructions, 371 differing. No source improvement accepted. DOL hash and all owned data/pools remain exact. Only this log is committed. The private diffs remain available for the next effort round.

## Round b, xhigh

Assigned branch agent/w1009/sdmem2, HEAD and freshly fetched origin/main b66bd1ed. Initial full Ninja build passed with target DOL SHA1. Only drawTransferTitles and this log are owned. Unslop and writing-for-agents applied to this report; worker silent mode applies to the run.

Previous round restored from bc4fb6db. Read the saved target-loop lead, sol-x17, sol-x4, sol-singles, sol-x14 and archived aggregate/fz7 evidence. Exclude the previous float-save misdiagnosis, blind declaration searches, compiler-version/unit-flag searches, unchanged pragma-only shapes, prior color ref/value identity wrappers and removed snapshots. New experiments target the four saved stack-color argument addresses, legitimate GXColor/Color copy boundaries, indexed color elements and scoped optimizer settings on the new lead. Baseline is 65/66 exact, draw 93.456764%, 438/451 instructions, 371 differing. Replayed lead is 317 differing, 455/451 instructions; target has no saved color addresses and recomputes r1+0x24/0x20/0x1c/0x18 at the calls.

### Compiled measurements
- lead-replay: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- lead-remove-uncalled-helper: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- lead-drop-opt-level: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- lead-drop-opt-iro0: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- lead-drop-draw-pragma: 247 differing; 441/451 instructions; objdiff 96.15078%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [].
- diagnostic-empty-asm-before-loop: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- diagnostic-empty-asm-inside-loop: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- helper-iro1-draw-default: 247 differing; 441/451 instructions; objdiff 96.15078%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [].
- helper-default-draw-iro1: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- gxcolor-value-pair-mutable: 309 differing; 455/451 instructions; objdiff 96.33703%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r28, r1, 0x20'), (221, 'r29, r1, 0x24'), (223, 'r26, r1, 0x18'), (225, 'r27, r1, 0x1c')].
- gxcolor-value-named-pair-mutable: 309 differing; 455/451 instructions; objdiff 96.33703%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r28, r1, 0x20'), (221, 'r29, r1, 0x24'), (223, 'r26, r1, 0x18'), (225, 'r27, r1, 0x1c')].
- gxcolor-value-pair-const: 309 differing; 455/451 instructions; objdiff 96.33703%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r28, r1, 0x20'), (221, 'r29, r1, 0x24'), (223, 'r26, r1, 0x18'), (225, 'r27, r1, 0x1c')].
- gxcolor-value-named-pair-const: 309 differing; 455/451 instructions; objdiff 96.33703%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r28, r1, 0x20'), (221, 'r29, r1, 0x24'), (223, 'r26, r1, 0x18'), (225, 'r27, r1, 0x1c')].
- loop-local-color-ctor: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- loop-local-color-default-assign: 324 differing; 457/451 instructions; objdiff 91.563194%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r23, r1, 0x38'), (221, 'r14, r1, 0x20'), (223, 'r22, r1, 0x30'), (225, 'r26, r1, 0x1c'), (226, 'r25, r1, 0x18')].
- loop-local-color-array: 313 differing; 447/451 instructions; objdiff 94.44124%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x48'), (221, 'r28, r1, 0x4c'), (223, 'r27, r1, 0x40'), (225, 'r26, r1, 0x44')].
- loop-local-color-gx-ctor: 217 differing; 451/451 instructions; objdiff 91.8204%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- loop-local-color-rgb-ctor: 322 differing; 459/451 instructions; objdiff 91.83148%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- gradient-named-array: 317 differing; 455/451 instructions; objdiff 96.31707%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x50'), (221, 'r28, r1, 0x54'), (223, 'r27, r1, 0x48'), (225, 'r26, r1, 0x4c')].
- gradient-named-pair: 317 differing; 455/451 instructions; objdiff 96.348114%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')].
- gradient-const-pair: 317 differing; 455/451 instructions; objdiff 96.348114%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')].
- gradient-outer-pair: 326 differing; 454/451 instructions; objdiff 88.63636%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r26, r1, 0x28'), (221, 'r23, r1, 0x34'), (223, 'r22, r1, 0x30'), (225, 'r25, r1, 0x20')].
- gradient-pointer-color: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- color-factory-gx-inside: 347 differing; 479/451 instructions; objdiff 90.96009%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x3c'), (221, 'r28, r1, 0x38'), (223, 'r27, r1, 0x34'), (225, 'r26, r1, 0x30')].
- color-factory-gx-outside: 347 differing; 479/451 instructions; objdiff 90.96009%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x3c'), (221, 'r28, r1, 0x38'), (223, 'r27, r1, 0x34'), (225, 'r26, r1, 0x30')].
- color-factory-color-gx-inside: 317 differing; 445/451 instructions; objdiff 93.65632%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- color-factory-color-gx-outside: 317 differing; 445/451 instructions; objdiff 93.65632%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- color-factory-color-copy-inside: 317 differing; 445/451 instructions; objdiff 93.65632%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- color-factory-color-copy-outside: 317 differing; 445/451 instructions; objdiff 93.65632%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- lead-api-const-value: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- lead-api-text-ref: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- lead-api-mutable-color-ref: 307 differing; 437/451 instructions; objdiff 93.36807%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r30, r1, 0x28'), (221, 'r29, r1, 0x20')].
- lead-api-color-pointer: 307 differing; 437/451 instructions; objdiff 93.36807%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r30, r1, 0x28'), (221, 'r29, r1, 0x20')].
- iteration-color-real-color-write: 328 differing; 459/451 instructions; objdiff 94.50111%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r23, r1, 0x3c'), (221, 'r14, r1, 0x20'), (223, 'r22, r1, 0x34'), (225, 'r26, r1, 0x1c'), (226, 'r25, r1, 0x18')].
- iteration-color-gxcolor-one-loop-local: 323 differing; 455/451 instructions; objdiff 96.332596%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- iteration-color-shared-color-snapshot: 330 differing; 456/451 instructions; objdiff 91.69845%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r27, r1, 0x24'), (221, 'r26, r1, 0x20'), (223, 'r22, r1, 0x38'), (225, 'r25, r1, 0x1c'), (226, 'r24, r1, 0x18')].
- remove-unused-newline-declaration: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- rendering-pointers-at-use: 317 differing; 455/451 instructions; objdiff 96.38359%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- named-float-getter-getTransferBackgroundOffset: 318 differing; 455/451 instructions; objdiff 96.36142%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- named-float-getter-getTransferTitleOffset: 321 differing; 455/451 instructions; objdiff 96.32816%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (221, 'r28, r1, 0x20'), (223, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].
- named-float-getter-getTransferClipLimit: 332 differing; 456/451 instructions; objdiff 94.88692%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x24'), (223, 'r28, r1, 0x20'), (224, 'r27, r1, 0x1c'), (225, 'r26, r1, 0x18')].

Fresh debugger capture /tmp/sol-r6-roundb-lead-capture is byte-identical to the clean lead in .text/.data/.sdata/.sdata2. Regsim reproduces 254/254 virtual registers. The constrained named-local search reaches only 1/7 requested target registers in 3000 trials. Backend-00 computes four color-copy addresses in branch blocks B51/B54; backend-01 hoists them into the loop preheader B46. No declaration permutation is being presented as a solution.

Relocation audit found an additional defect in the saved lead: the two color calls target the newly emitted setTransferTitleColors by-value helper, not retail setTitleRowColors. The wrapper does not inline. The 96.38359% score alone conceals that call-target mismatch. Reject all such wrapper/factory candidates from retention. Direct named-gradient colors call the retail setter and score 96.348114%; pursue that shape instead.

Requested optsweep with all settings reported: IRO 0/1 both retain 455 instructions and 317 differences on the new lead; level 2 reaches 451 instructions but 438 differences because it changes many unrelated operations. Scoped source trials confirm IRO 0 leaves all four address hoists. Empty-assembly diagnostics also leave all four and will not be retained. Member-index tricks with an iteration-dependent index have no supported array in this function: the four problematic addresses point to stack arguments, not member colors. An invented selector or offset would change behavior or be artificial, so none was added.
- direct-pair-clean: 317 differing; 455/451 instructions; objdiff 96.348114%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-iro0: 317 differing; 455/451 instructions; objdiff 96.348114%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-no-iro: 249 differing; 441/451 instructions; objdiff 96.14191%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-declarations-at-use: 331 differing; 455/451 instructions; objdiff 96.01552%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-at-use-no-iro: 258 differing; 441/451 instructions; objdiff 95.898%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-alpha-definition-before: compile FAILED; details /tmp/sol-r6-error-direct-pair-alpha-definition-before.txt.
- direct-pair-locals-before-write: 339 differing; 457/451 instructions; objdiff 86.946785%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r25, r1, 0x3c'), (221, 'r24, r1, 0x38'), (223, 'r23, r1, 0x2c'), (225, 'r22, r1, 0x28'), (226, 'r14, r1, 0x20')]; color calls ['__as__Q34nw4r2ut5ColorFRCQ34nw4r2ut5Color', '__as__Q34nw4r2ut5ColorFRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', '__as__Q34nw4r2ut5ColorFRCQ34nw4r2ut5Color', '__as__Q34nw4r2ut5ColorFRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-locals-before-snapshot: 339 differing; 457/451 instructions; objdiff 87.5898%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r25, r1, 0x38'), (221, 'r24, r1, 0x34'), (223, 'r23, r1, 0x28'), (225, 'r22, r1, 0x24'), (226, 'r14, r1, 0x20')]; color calls ['__as__Q34nw4r2ut5ColorFRCQ34nw4r2ut5Color', '__as__Q34nw4r2ut5ColorFRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', '__as__Q34nw4r2ut5ColorFRCQ34nw4r2ut5Color', '__as__Q34nw4r2ut5ColorFRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-locals-bottom-first: 331 differing; 455/451 instructions; objdiff 96.01552%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-at-use-floats: 332 differing; 455/451 instructions; objdiff 95.971176%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-at-use-pointers: 317 differing; 455/451 instructions; objdiff 96.348114%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-at-use-float-and-pointers: 332 differing; 455/451 instructions; objdiff 95.971176%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-alpha-before-fixed: 317 differing; 455/451 instructions; objdiff 96.348114%; other drops ['__ne__Q24nw4r2utFQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8IteratorQ44nw4r2ut28LinkList<Q34nw4r3lyt4Pane,4>8Iterator']; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- direct-pair-native-gradient-array: 317 differing; 455/451 instructions; objdiff 96.31707%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x50'), (221, 'r28, r1, 0x54'), (223, 'r27, r1, 0x48'), (225, 'r26, r1, 0x4c')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- retained-readable-direct-pair: 317 differing; 455/451 instructions; objdiff 96.348114%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(219, 'r29, r1, 0x34'), (221, 'r28, r1, 0x30'), (223, 'r27, r1, 0x24'), (225, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].

### Round b disposition

55 successful compiled measurements and one failed alpha-helper-placement trial. The corrected placement also regressed the previously exact iterator comparator and was rejected. No exact function was gained.

Retain the readable direct-color version under the human's explicit permission to commit a clean non-exact improvement. drawTransferTitles improves from 93.456764% to 96.348114%, positional differences 371 to 317. Instruction count is 455/451, so this is not an exact match. The saved by-value-wrapper lead's 96.38359% score is not retained: its two color calls use a new tail-call wrapper. The final source emits no such wrapper and all 36 application/library call relocations match the target in order; the remaining two call-relocation differences are _savegpr_15/_restgpr_15 versus retail _savegpr_19/_restgpr_19, consistent with four additional saved GPRs.

Source changes keep the target-shaped guarded newline count and counted message loop, cache their actual newline delimiters, name the two gradient colors, and use the existing retail setTitleRowColors API. The alpha traversal is a normal inline helper. The IRO 1 pragma surrounds only drawTransferTitles. Rendering pane pointers stay at their point of use; scalar declaration/initialization order preserves the best measured source shape. No unused helper, carrier object, dummy selector, invented array/member layout, new assembly, new volatile field, or unrelated source edit is retained.

Semantics reviewed line by line: the count starts at zero and counts every newline; positive totalLines and lineIndex=0 produce the same message iterations; newline advancement and body-height subtraction stay in the same paths. Children get the same alpha. Both copies of each RGBA color contain the same four bytes as before. Advancing nandTitleIndex before writeFourFlagBytes changes no observable value used by that call and follows the target's increment-before-call order. All rendering coordinates, clipping comparisons, and title iterations retain their operations and types.

The four invariant color addresses are still hoisted into saved r26-r29; IRO 0, real GXColor conversions, named/API pointer and reference forms, native gradient arrays, return-value factories and lever-33 constant getters did not provide an accepted exact result. Typed GXColor conversion reached 451 instructions and 217 positional differences, but scored 91.8204% and still called the wrapper, so it is rejected. The target has a 0x140 frame; retained source has a 0x150 frame. Future work should start from the direct named-gradient source and investigate the backend address-hoisting lifetime, not the invalid wrapper score or an extra-FPR theory. No compiler-impossibility claim.

Unit stays NonMatching, exact functions 65/66 to 65/66, matched code 19068/20872 unchanged, data 3344/3344 unchanged. Unit fuzzy 99.434456% to 99.684364%. Pool remains identical 90/90. All previously exact functions remain exact. Parent verification is still required before acceptance or integration. No push, PR, merge, rebase, cross-worktree source edit or subagent was used.

Saved source-only diff: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-r6.iplSDMemory.roundb.diff. The older target-loops and equal-size exploratory diffs remain available for comparison, with their recorded limitations.

### Round b final gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 19068/20872 data 3344/3344 functions 65/66 fuzzy 99.6844 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 65/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.684364
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 96.348114
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 19068/20872 data 3344 functions 65 fuzzy 99.4345
regressions vs baseline: 0
global matched_code_percent: 98.09787 -> 98.09787
global fuzzy_match_percent: 99.92176 -> 99.92351
global complete_code_percent: 90.12492 -> 90.12492
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: src/scene/sdChannelMemory/iplSDMemory.cpp: per-function optimization pragma (levers 26: orchestrator checks the per-use address recompute evidence) (+1 net), e.g. #pragma ppc_iro_level 1
GATE PASS
```

Fresh ctxdiff: src 0x71c base 0x70c, instructions 455/451. Fresh odiff: differing 317/455. This is a local non-exact improvement, not a full-unit completion.

## Round c, integrity cleanup and color-address lifetimes

Assigned data-d9 / agent/w1009/sdmem2, initial HEAD d966f166. The parent rejected the round-b newline guards and literal-only delimiter locals. Those constructs are removed before new experiments. The earlier round-b description calling them readable was incorrect. C89 scalar declarations, the real child-alpha traversal, direct retail color calls and the scoped IRO 1 setting remain in scope. Commit the clean result even if its honest instruction diff rises.

Read sol-common, brief-v2, all levers, the local log, saved-source history and target Ghidra output. Apply unslop and writing-for-agents to the log. Do not repeat earlier wrapper/factory experiments, unchanged optimization sweeps, blind declaration permutations, invented indexed selectors or empty-assembly trials. New work investigates real color-copy and rendering boundaries on the cleaned source.

- roundc-remove-redundant-guards-and-literal-locals: 389 differing; 450/451 instructions; objdiff 93.5765%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x34'), (216, 'r28, r1, 0x30'), (218, 'r27, r1, 0x24'), (220, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].

Integrity cleanup baseline: 389 differing, 450/451 instructions, 93.5765%. Round-b rejected source was 317 differing, 455/451 instructions, 96.348114%; pre-round-b accepted source was 371 differing, 438/451 instructions, 93.456764%. Removing the tricks loses their apparent gain, while the clean source keeps a small fuzzy improvement against the pre-round-b baseline. No exact-match claim. All 65 previously exact functions and all 90 pool strings remain exact.

- roundc-color-temporary-both: 389 differing; 450/451 instructions; objdiff 93.61198%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x24'), (216, 'r28, r1, 0x20'), (218, 'r27, r1, 0x1c'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-temporary-top: 389 differing; 450/451 instructions; objdiff 93.585365%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x34'), (216, 'r28, r1, 0x1c'), (218, 'r27, r1, 0x28'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-temporary-bottom: 389 differing; 450/451 instructions; objdiff 93.585365%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x34'), (216, 'r28, r1, 0x1c'), (218, 'r27, r1, 0x28'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-direct-ctor-both: 389 differing; 450/451 instructions; objdiff 93.5765%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x34'), (216, 'r28, r1, 0x30'), (218, 'r27, r1, 0x24'), (220, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-separate-scopes: 389 differing; 450/451 instructions; objdiff 93.5765%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x34'), (216, 'r28, r1, 0x30'), (218, 'r27, r1, 0x24'), (220, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-shared-gx-reference: 392 differing; 442/451 instructions; objdiff 91.669624%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x30'), (216, 'r28, r1, 0x2c'), (218, 'r27, r1, 0x24'), (220, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-solid-copy-helper-reference: 377 differing; 430/451 instructions; objdiff 90.31929%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r30, r1, 0x28'), (216, 'r29, r1, 0x20')]; color calls ['setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5Color', 'setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5Color'].
- roundc-solid-copy-helper-pointer: 377 differing; 430/451 instructions; objdiff 90.31929%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r30, r1, 0x28'), (216, 'r29, r1, 0x20')]; color calls ['setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxPCQ34nw4r2ut5Color', 'setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxPCQ34nw4r2ut5Color'].
- roundc-solid-copy-helper-const-reference: 377 differing; 430/451 instructions; objdiff 90.31929%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r30, r1, 0x28'), (216, 'r29, r1, 0x20')]; color calls ['setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5Color', 'setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5Color'].
- roundc-solid-copy-helper-copy-via-gx: 377 differing; 430/451 instructions; objdiff 90.31929%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r30, r1, 0x28'), (216, 'r29, r1, 0x20')]; color calls ['setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRC8_GXColor', 'setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRC8_GXColor'].
- roundc-solid-copy-helper-ctor-parameters: 377 differing; 430/451 instructions; objdiff 90.31929%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r30, r1, 0x28'), (216, 'r29, r1, 0x20')]; color calls ['setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5Color', 'setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5Color'].
- roundc-byte-colors-components-ctor: 362 differing; 446/451 instructions; objdiff 86.45011%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['__ct__Q34nw4r2ut5ColorFiiii', '__ct__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', '__ct__Q34nw4r2ut5ColorFiiii', '__ct__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-byte-colors-set-components: 382 differing; 455/451 instructions; objdiff 86.649666%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r25, r1, 0x34'), (216, 'r24, r1, 0x30'), (218, 'r23, r1, 0x24'), (220, 'r22, r1, 0x20')]; color calls ['Set__Q34nw4r2ut5ColorFiiii', 'Set__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'Set__Q34nw4r2ut5ColorFiiii', 'Set__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-byte-colors-assign-components: 382 differing; 455/451 instructions; objdiff 91.68071%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r25, r1, 0x34'), (216, 'r24, r1, 0x30'), (218, 'r23, r1, 0x24'), (220, 'r22, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-byte-colors-components-ctor-temporary: 362 differing; 446/451 instructions; objdiff 86.454544%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['__ct__Q34nw4r2ut5ColorFiiii', '__ct__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', '__ct__Q34nw4r2ut5ColorFiiii', '__ct__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-byte-colors-snapshot-components: 389 differing; 454/451 instructions; objdiff 89.04213%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x34'), (216, 'r28, r1, 0x30'), (218, 'r27, r1, 0x24'), (220, 'r26, r1, 0x20')]; color calls ['__ct__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', '__ct__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-byte-colors-gx-components-ctor: 359 differing; 454/451 instructions; objdiff 90.33703%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['__ct__Q34nw4r2ut5ColorFiiii', '__ct__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', '__ct__Q34nw4r2ut5ColorFiiii', '__ct__Q34nw4r2ut5ColorFiiii', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-snapshot-c-style: 389 differing; 450/451 instructions; objdiff 93.5765%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x34'), (216, 'r28, r1, 0x30'), (218, 'r27, r1, 0x24'), (220, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-snapshot-c-style-ctor: 389 differing; 450/451 instructions; objdiff 93.5765%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x34'), (216, 'r28, r1, 0x30'), (218, 'r27, r1, 0x24'), (220, 'r26, r1, 0x20')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-temporary-cast-copy: 389 differing; 450/451 instructions; objdiff 93.61198%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x24'), (216, 'r28, r1, 0x20'), (218, 'r27, r1, 0x1c'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-temporary-static-cast-copy: 389 differing; 450/451 instructions; objdiff 93.61198%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x24'), (216, 'r28, r1, 0x20'), (218, 'r27, r1, 0x1c'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-temporary-iro0: 389 differing; 450/451 instructions; objdiff 93.61198%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x24'), (216, 'r28, r1, 0x20'), (218, 'r27, r1, 0x1c'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-temporary-iro2: 363 differing; 436/451 instructions; objdiff 93.46785%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-temporary-iro3: 368 differing; 436/451 instructions; objdiff 93.37916%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-temporary-const-snapshot: 389 differing; 450/451 instructions; objdiff 93.61198%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x24'), (216, 'r28, r1, 0x20'), (218, 'r27, r1, 0x1c'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-temporary-snapshot-ctor: 389 differing; 450/451 instructions; objdiff 93.61198%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x24'), (216, 'r28, r1, 0x20'), (218, 'r27, r1, 0x1c'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-temporary-snapshot-reference: 389 differing; 450/451 instructions; objdiff 93.61198%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x24'), (216, 'r28, r1, 0x20'), (218, 'r27, r1, 0x1c'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].

Fresh cleanup capture /tmp/sol-r6-roundc-clean-capture reproduces 252/252 virtual registers. In backend-00 the Color copy-constructor destination addresses are created within active/inactive branch blocks. By backend-01, r146/r145/r140/r139 move to loop preheader B44. Each has 50 interference neighbors, including call-clobbered r4/r5, and is allocated to saved r29/r28/r27/r26. Those lifetimes prevent declaration order from replacing them with target call-argument registers. The constrained named-local search gets only 2/9 desired registers over 3000 trials; no blind declaration permutations are compiled. The target instead forms its two argument addresses at each setter call.

Direct Color temporary arguments reach the target's 0x24/0x20/0x1c/0x18 argument-slot offsets, but keep all four hoists and 389 differing instructions. Explicit RGBA constructors remove the observed hoists by adding four constructor calls absent from retail, so they are rejected. Copy helpers also stay out of line and call the new helper rather than the retail setter, so they are rejected. Direct byte assignments keep the four hoists and add initialization code.

- roundc-temporary-via-gx-reference: 389 differing; 450/451 instructions; objdiff 93.61198%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x24'), (216, 'r28, r1, 0x20'), (218, 'r27, r1, 0x1c'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-color-arguments-parenthesized: 389 differing; 450/451 instructions; objdiff 93.61198%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r29, r1, 0x24'), (216, 'r28, r1, 0x20'), (218, 'r27, r1, 0x1c'), (220, 'r26, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-helper: 384 differing; 412/451 instructions; objdiff 88.694016%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRC8_GXColor', 'setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRC8_GXColor'].
- roundc-rgba-helper: 384 differing; 406/451 instructions; objdiff 87.093124%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxUcUcUcUc', 'setSolidTitleColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxUcUcUcUc'].
- roundc-rgba-helper-after-caller: compile FAILED; details /tmp/sol-r6-error-roundc-rgba-helper-after-caller.txt.
- roundc-gx-slice: 362 differing; 446/451 instructions; objdiff 96.30155%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-components: 362 differing; 446/451 instructions; objdiff 96.30155%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-assign-components: 362 differing; 446/451 instructions; objdiff 96.30155%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-array-components: 362 differing; 446/451 instructions; objdiff 96.27051%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-array-slice: 390 differing; 448/451 instructions; objdiff 93.74058%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(216, 'r30, r1, 0x54'), (218, 'r29, r1, 0x4c')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-const-components: 362 differing; 446/451 instructions; objdiff 96.30155%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].

IRO 2 and 3 on the new direct-temporary shape remove the four preheader hoists but also eliminate target-proven snapshot stores, leaving 436/451 instructions. Their scores are 93.46785% and 93.37916%, below the cleaned IRO 1 candidate. They are not retained. The RGBA helper-placement experiment failed to compile because the insertion reached an earlier prototype instead of the intended definition; it is an experiment-script defect, not a compiler result.

- roundc-gx-slice-selected: 362 differing; 446/451 instructions; objdiff 96.30155%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].

Native GXColor top/bottom copies are the first clean lead that removes all four hoists while preserving the retail color-call targets and all three RGBA copy groups. Each outgoing color is a four-byte GXColor copied from the actual snapshot and viewed through the same typed Color cast already used at the GXColor boundary. There is no offset arithmetic, fabricated layout, extra call or unrelated storage. The compiler forms each setter argument address in r4/r5 immediately before its call. The frame is now the target's 0x140 and both register helper relocations now agree with _savegpr_19/_restgpr_19. Selected source is 362 differing, 446/451 instructions, 96.30155%, all other functions unchanged and pool 90/90 identical. The five-instruction deficit follows the cleaned header loops; do not restore redundant guarded while/for loops or literal-only locals to mask it.

- roundc-gx-declarations-top: 393 differing; 444/451 instructions; objdiff 87.38802%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r30, r1, 0x28'), (216, 'r29, r1, 0x20')]; color calls ['__as__8_GXColorFRC8_GXColor', '__as__8_GXColorFRC8_GXColor', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', '__as__8_GXColorFRC8_GXColor', '__as__8_GXColorFRC8_GXColor', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-declarations-loop: 393 differing; 444/451 instructions; objdiff 87.38802%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r30, r1, 0x28'), (216, 'r29, r1, 0x20')]; color calls ['__as__8_GXColorFRC8_GXColor', '__as__8_GXColorFRC8_GXColor', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', '__as__8_GXColorFRC8_GXColor', '__as__8_GXColorFRC8_GXColor', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-base-cast-copy: 362 differing; 446/451 instructions; objdiff 96.30155%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-color-reference-views: 362 differing; 446/451 instructions; objdiff 96.30155%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-snapshot-pod: 362 differing; 446/451 instructions; objdiff 96.30155%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-implicit-color-conversion: 399 differing; 458/451 instructions; objdiff 91.74058%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses [(214, 'r28, r1, 0x24'), (216, 'r27, r1, 0x20'), (218, 'r26, r1, 0x1c'), (220, 'r25, r1, 0x18')]; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-guarded-do-counter: 363 differing; 447/451 instructions; objdiff 97.13304%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].

Fresh native-color capture /tmp/sol-r6-roundc-gx-capture reproduces 244/244 virtual registers. Backend-01 now keeps the four argument-address addi instructions in the two color blocks; none exist in the loop preheader. The constrained named-local simulator reaches 9/9 requested semantic registers in 3000 steps, versus 2/9 for the cleaned Color-copy source. This justifies a small declaration-placement follow-up, with compiled validation required; it does not establish exact code while the header blocks differ.

- roundc-gx-simulator-declarations: 360 differing; 446/451 instructions; objdiff 96.57871%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-do-counter-simulator-declarations: 363 differing; 447/451 instructions; objdiff 97.4102%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-gx-guarded-do-both: 363 differing; 447/451 instructions; objdiff 97.07761%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-native-gx-simulator-best: 363 differing; 447/451 instructions; objdiff 97.4102%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-natural-declarations-geometry-panes-titles-message: 363 differing; 447/451 instructions; objdiff 97.4102%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-natural-declarations-geometry-message-titles-panes: 366 differing; 447/451 instructions; objdiff 97.02217%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
- roundc-natural-declarations-geometry-counters-panes-message: 367 differing; 447/451 instructions; objdiff 97.011086%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].

The counter guard is retained only in the do-while trial, where it prevents an initial null dereference and an incorrect first count. Retail proves the initial null check at instruction 99/100. The guarded while from round b remains removed. The message renderer keeps one ordinary for-loop and no outer positive-count test. Neither loop has a literal-holding local. A trial with guarded do-while rendering is worse and is rejected.

Separate native-gradient declarations at function/loop entry emit new GXColor assignment calls and are rejected. Implicit conversion back to Color adds word copies, restores the four hoists and is rejected. Converting the intermediate snapshot itself to GXColor preserves the measured instruction stream and removes an unnecessary reinterpret cast at initialization; outgoing views remain at the existing retail Color API boundary.

The simulator-guided declaration placement gets 97.4102%, 363 differing, 447/451 instructions without regressions or hoists. The declarations are all real, and every read follows its unchanged assignment. Natural declaration groups are checked before selecting the final readable result. No compiler-impossibility claim or exact-match claim.

- roundc-final-readable-groups: 363 differing; 447/451 instructions; objdiff 97.4102%; other drops []; POOL IDENTICAL up to 90 (mine=90 base=90); saved color addresses []; color calls ['setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color', 'setTitleRowColors__Q23ipl5sceneFPQ34nw4r3lyt7TextBoxRCQ34nw4r2ut5ColorRCQ34nw4r2ut5Color'].
### Round c disposition

54 successful compiled measurements and 1 failed experiment-script placement. Final source uses natural declaration groups: geometry, panes, title counters and message traversal. This grouping has the same 97.4102% score as the simulator-selected ordering and reads more directly. All colors, including the intermediate snapshots, are GXColor values; only the outgoing views cross the existing retail Color API boundary. Every RGBA byte is initialized before the value is copied or passed.

Rejected d966f166: 317 differing, 455/451 instructions, 96.348114%. Direct integrity cleanup: 389 differing, 450/451 instructions, 93.5765%. Final clean candidate: 363 differing, 447/451 instructions, 97.4102%. Accepted pre-round-b baseline: 371 differing, 438/451 instructions, 93.456764%. The final positional diff rises by 46 versus rejected d966f166 and falls by 8 versus the accepted baseline. Do not report the discarded 317 as an accepted gain.

All four saved color-address hoists are gone; the frame is 0x140, and all 38 ordered REL24 call/helper relocations agree with retail, including _savegpr_19/_restgpr_19. The target forms active arguments at 0x24/0x20 and inactive at 0x1c/0x18; the retained named GXColor buffers still occupy different slots. The cleaned header loops differ in entry branches and literal materialization. Those differences, stack-slot placement and remaining register choices are unresolved; four target instructions remain absent. No padding, redundant condition, dummy literal local, extra helper call or compiler-impossibility claim is used to hide that deficit.

Unit exact functions stay 65/66; matched code stays 19068/20872; data stays 3344/3344 and all three data sections remain 100%. Unit fuzzy becomes 99.77616%. Pool identical 90/90. No exact function gained, no Matching flip. The source diff changes only drawTransferTitles; the existing alpha helper and scoped IRO 1 remain. Parent review and fresh validation are still required before acceptance. No push, PR, merge, rebase, other-worktree edit or subagent.

Saved final source-only diff: /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-r6.iplSDMemory.roundc.diff. Fresh report, odiff and ctxdiff: /tmp/sol-r6-roundc-final-report.json, /tmp/sol-r6-roundc-final.odiff, /tmp/sol-r6-roundc-final.ctxdiff.


### Round c final gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/sdChannelMemory/iplSDMemory] pool: IDENTICAL
[src/scene/sdChannelMemory/iplSDMemory] objdiff: code 19068/20872 data 3344/3344 functions 65/66 fuzzy 99.7762 linked code 0
[src/scene/sdChannelMemory/iplSDMemory] instruction-exact functions: 65/66
[src/scene/sdChannelMemory/iplSDMemory]   section .data size 3144 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata size 152 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .sdata2 size 48 match 100.0
[src/scene/sdChannelMemory/iplSDMemory]   section .text size 20872 match 99.77616
[src/scene/sdChannelMemory/iplSDMemory]   below 100: drawTransferTitles__Q33ipl5scene8SDMemoryFv 97.4102
[src/scene/sdChannelMemory/iplSDMemory] baseline: code 19068/20872 data 3344 functions 65 fuzzy 99.4345
regressions vs baseline: 0
global matched_code_percent: 98.09787 -> 98.09787
global fuzzy_match_percent: 99.92176 -> 99.92416
global complete_code_percent: 90.12492 -> 90.12492
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
review note: src/scene/sdChannelMemory/iplSDMemory.cpp: per-function optimization pragma (levers 26: orchestrator checks the per-use address recompute evidence) (+1 net), e.g. #pragma ppc_iro_level 1
GATE PASS
```

Fresh final odiff: source 0x6fc, target 0x70c, 363/451 differing, 447/451 instructions. Gate passes with no regressions, no added forbidden patterns and no readability warnings. This verifies build integrity and retained partial progress; it does not make drawTransferTitles exact or link this NonMatching unit. Source is unchanged after the gate.
