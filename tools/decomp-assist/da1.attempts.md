# da1 de-asm handoff

Four of eleven assigned asm bodies converted to C++. Seven retain their original asm after source attempts. This is partial de-asm progress. All accepted conversion functions remain 100.0% and instruction-exact.

| Function | Result | Best C++ evidence |
|---|---|---|
| keyboard::Manager::doSave | Converted, cd13786b | 100.0%, 85/85, diffs 0 |
| savedata::Manager::hasChannel | Kept asm | 91.66197%, 71/71, 54 diffs |
| savedata::Manager::makePriorTitleIDList | Kept asm | 80.22556%, 124/133 instructions |
| savedata::Manager::makeTmpList | Converted, 86b306d1 | 100.0%, 95/95, diffs 0 |
| savedata::Manager::doUpdateChanInfos | Kept asm | 91.9403%, 68/67 instructions |
| savedata::Manager::pushTitleCache | Converted, b395ddf0 | 100.0%, 58/58, diffs 0 |
| cdb_backup_delete_task_ | Kept asm | 99.781815%, 55/55, 2 epilogue diffs |
| cdb_backup_move_task_ | Kept asm | 99.82609%, 69/69, 2 epilogue diffs |
| System::warning_run | Kept asm | 98.66477%, 176/176, 47 register diffs |
| Exception::exception_callback | Kept asm | 99.18367%, 98/98, 13 register diffs |
| CArGBAOdh::compressGbaOdh | Converted, final commit | 100.0%, 101/101, diffs 0 |

Each trial below names its source, compiler output, pool result, ctxdiff and objdiff snapshot under build/da1. Inspect that folder before repeating an experiment. All seven kept functions have at least four successful compiled source attempts. No new asm, use-site volatile, register keyword, artificial padding, symbol edits or compiler flag changes were retained. Only keyboard, SaveDataManager, odh and this log changed.

## Attempts and verification

da1 de-asm round, base bfe77b7f, branch agent/w1005/da1.
Scope: keyboard doSave; savedata hasChannel, makePriorTitleIDList, makeTmpList, doUpdateChanInfos, pushTitleCache; CdbBackup delete/move tasks; System warning_run; Exception callback; odh compressGbaOdh.
Baseline: all assigned functions are 100% asm. Five units linked; odh remains NonMatching. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Fresh baseline report build/da1-baseline-report.json. Prior asm-conversions attempts reviewed.

keyboard-1 doSave__Q33ipl8keyboard7ManagerFv: Value-parameter comparison helper with direct returned setting initialization.
POOL IDENTICAL up to 28 (mine=28 base=28); 93.988235%; src 0x154 base 0x154 insns 85/85; diffs 57: [4, 5, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32]
Evidence: build/da1/keyboard-1

keyboard-2 doSave__Q33ipl8keyboard7ManagerFv: Materialize comparison boolean before testing pending save.
POOL IDENTICAL up to 28 (mine=28 base=28); 95.117645%; src 0x144 base 0x154 insns 81/85; --- insert mine 58:58 base 58:59
Evidence: build/da1/keyboard-2

keyboard-3 doSave__Q33ipl8keyboard7ManagerFv: Use SDK BOOL for comparison helper and result.
POOL IDENTICAL up to 28 (mine=28 base=28); 95.117645%; src 0x144 base 0x154 insns 81/85; --- insert mine 58:58 base 58:59
Evidence: build/da1/keyboard-3

keyboard-4 doSave__Q33ipl8keyboard7ManagerFv: Separate locals for equality and combined save predicate.
POOL IDENTICAL up to 28 (mine=28 base=28); 100.0%; src 0x154 base 0x154 insns 85/85; diffs 0: []
Evidence: build/da1/keyboard-4

keyboard-5 doSave__Q33ipl8keyboard7ManagerFv: Explicit bool conversion for combined save predicate.
POOL IDENTICAL up to 28 (mine=28 base=28); 95.117645%; src 0x144 base 0x154 insns 81/85; --- insert mine 58:58 base 58:59
Evidence: build/da1/keyboard-5

keyboard-6 doSave__Q33ipl8keyboard7ManagerFv: Const equality and SDK BOOL combined predicate.
POOL IDENTICAL up to 28 (mine=28 base=28); 100.0%; src 0x154 base 0x154 insns 85/85; diffs 0: []
Evidence: build/da1/keyboard-6

keyboard-final doSave__Q33ipl8keyboard7ManagerFv: Keep two readable boolean locals and remove asm-only extern declarations.
POOL IDENTICAL up to 28 (mine=28 base=28); 100.0%; src 0x154 base 0x154 insns 85/85; diffs 0: []
Evidence: build/da1/keyboard-final

doSave CONVERTED. Final full gate build/da1/keyboard-full-gate.txt: GATE PASS, 32/32 exact unchanged, code 6024/6024, data 1184/1184; regressions 0; forbidden/readability 0; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Exact by-value comparison helper plus separate equality and save-condition locals.

hasChannel-1 hasChannel__Q33ipl8savedata7ManagerCFUxPiPi: Read-only SInfo reference helper assembles each stored title; direct nested array access, two masks.
POOL IDENTICAL up to 3 (mine=3 base=3); 86.676056%; src 0x11c base 0x11c insns 71/71; diffs 53: [0, 2, 3, 8, 9, 11, 12, 13, 14, 15, 16, 17, 19, 20, 21, 22, 23, 24, 25, 26]
Evidence: build/da1/hasChannel-1

hasChannel-2 hasChannel__Q33ipl8savedata7ManagerCFUxPiPi: Inline full title comparison helper; keeps masked comparisons together.
POOL IDENTICAL up to 3 (mine=3 base=3); 81.014084%; src 0x12c base 0x11c insns 75/71; --- replace mine 0:1 base 0:1
Evidence: build/da1/hasChannel-2

hasChannel-3 hasChannel__Q33ipl8savedata7ManagerCFUxPiPi: Const-reference comparison helper inputs instead of by-value inputs.
POOL IDENTICAL up to 3 (mine=3 base=3); 81.014084%; src 0x12c base 0x11c insns 75/71; --- replace mine 0:1 base 0:1
Evidence: build/da1/hasChannel-3

hasChannel-4 hasChannel__Q33ipl8savedata7ManagerCFUxPiPi: Block-scoped region mask inside each valid channel; direct indexed field loads.
POOL IDENTICAL up to 3 (mine=3 base=3); 91.66197%; src 0x11c base 0x11c insns 71/71; diffs 54: [0, 2, 3, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]
Evidence: build/da1/hasChannel-4

hasChannel-5 hasChannel__Q33ipl8savedata7ManagerCFUxPiPi: Const masks, pointer-to-const title helper, and target-side comparison operand order.
POOL IDENTICAL up to 3 (mine=3 base=3); 86.676056%; src 0x11c base 0x11c insns 71/71; diffs 53: [0, 2, 3, 8, 9, 11, 12, 13, 14, 15, 16, 17, 19, 20, 21, 22, 23, 24, 25, 26]
Evidence: build/da1/hasChannel-5

hasChannel provisionally KEPT ASM after five distinct compiled attempts. Best manual C++ 91.66197%, 71/71 instructions, 54 differences, different frame and invariant-hoist/register placement. Search on immutable candidate queued for shared srcsearch CPU slot; no original file mutation. Three prior simple-loop trials were not repeated.

prior-1 makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl: Photo-title replacement as const-reference inline helper; use direct indexed title accesses.
POOL IDENTICAL up to 3 (mine=3 base=3); 75.53384%; src 0x1e8 base 0x214 insns 122/133; --- replace mine 12:13 base 12:14
Evidence: build/da1/prior-1

prior-2 makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl: Const read helper and write helper around title-array indexing to preserve per-use address computation.
POOL IDENTICAL up to 3 (mine=3 base=3); 80.22556%; src 0x1f0 base 0x214 insns 124/133; --- replace mine 12:13 base 12:14
Evidence: build/da1/prior-2

prior-3 makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl: Inline photo replacement at use; unsigned input induction and early continue for empty slots.
POOL IDENTICAL up to 3 (mine=3 base=3); 75.53384%; src 0x1e8 base 0x214 insns 122/133; --- replace mine 12:13 base 12:14
Evidence: build/da1/prior-3

prior-4 makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl: Compute output index at nonempty-input use; separate const input title for comparison call.
POOL IDENTICAL up to 3 (mine=3 base=3); 77.83459%; src 0x1f0 base 0x214 insns 124/133; --- insert mine 12:12 base 12:14
Evidence: build/da1/prior-4

makePriorTitleIDList provisionally KEPT ASM. Four new distinct compiled source attempts, best helper candidate 80.22556%, 124/133 instructions. MWCC caches output/input addresses where target recomputes them and places photo mask differently. Search on immutable helper candidate queued.

tmp-1 makeTmpList__Q33ipl8savedata7ManagerFPUxUlPUxUl: Use ES_TITLE_TYPE and ES_TITLE_CODE macros for target-proven masking rather than truncated casts; direct title-list loops.
POOL IDENTICAL up to 3 (mine=3 base=3); 100.0%; src 0x17c base 0x17c insns 95/95; diffs 0: []
Evidence: build/da1/tmp-1

makeTmpList candidate exact on first new trial: 100.0%, 95/95, diffs 0, 3/3 pool. Target redundant and instructions come from ES_TITLE_TYPE/ES_TITLE_CODE macros. Retain pending full unit gate.

update-1 doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx: Const-reference channel initialization helper, ordinary SInfo fields and ES title macros.
POOL IDENTICAL up to 3 (mine=3 base=3); 91.9403%; src 0x110 base 0x10c insns 68/67; --- replace mine 5:7 base 5:7
Evidence: build/da1/update-1

update-2 doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx: Separate clearChannelInfo inline helper delays address formation for memset.
POOL IDENTICAL up to 3 (mine=3 base=3); 91.9403%; src 0x110 base 0x10c insns 68/67; --- replace mine 5:7 base 5:7
Evidence: build/da1/update-2

update-3 doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx: Bind SInfo reference for one channel before testing and updating it.
POOL IDENTICAL up to 3 (mine=3 base=3); 87.910446%; src 0x110 base 0x10c insns 68/67; --- replace mine 7:8 base 7:8
Evidence: build/da1/update-3

update-4 doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx: Pointer-to-const input and pointer output helper instead of references.
POOL IDENTICAL up to 3 (mine=3 base=3); 91.9403%; src 0x110 base 0x10c insns 68/67; --- replace mine 5:7 base 5:7
Evidence: build/da1/update-4

update-5 doUpdateChanInfos__Q33ipl8savedata7ManagerFPUx: Direct indexed stores with ES macros and a named comparison result; remove helper lifetime.
POOL IDENTICAL up to 3 (mine=3 base=3); 91.9403%; src 0x110 base 0x10c insns 68/67; --- replace mine 5:7 base 5:7
Evidence: build/da1/update-5

doUpdateChanInfos provisionally KEPT ASM after five new compiled variants: best C++ 91.9403%, 68/67 instructions. Extra per-page +0x30 address for memset forces different register allocation. Source search queued on direct-store candidate.

cache-1 pushTitleCache__Q33ipl8savedata7ManagerFUx: Use named title-type constants, NOMASK type extraction, repeated array accesses and one shrinking cache index.
POOL IDENTICAL up to 3 (mine=3 base=3); 91.86207%; src 0xd8 base 0xe8 insns 54/58; --- replace mine 24:25 base 24:25
Evidence: build/da1/cache-1

cache-2 pushTitleCache__Q33ipl8savedata7ManagerFUx: Unsigned previous slot index preserves separate predecessor address computation.
POOL IDENTICAL up to 3 (mine=3 base=3); 100.0%; src 0xe8 base 0xe8 insns 58/58; diffs 0: []
Evidence: build/da1/cache-2

cache-3 pushTitleCache__Q33ipl8savedata7ManagerFUx: Const-pointer inline cachedTitle accessor around predecessor read.
POOL IDENTICAL up to 3 (mine=3 base=3); 91.86207%; src 0xd8 base 0xe8 insns 54/58; --- replace mine 24:25 base 24:25
Evidence: build/da1/cache-3

cache-4 pushTitleCache__Q33ipl8savedata7ManagerFUx: Separate destination local and decrement the source index before its read.
POOL IDENTICAL up to 3 (mine=3 base=3); 92.98276%; src 0xe4 base 0xe8 insns 57/58; --- replace mine 24:25 base 24:25
Evidence: build/da1/cache-4

pushTitleCache candidate exact: cache-2 uses u32 previousIndex = index - 1 and normal indexed access, 100.0%, 58/58, diffs 0. No raw offsets or artificial assembly.
Prior automated search: 23 trials, no gain over 124/133 instructions and 80.22556%. hasChannel automated search waited 7 minutes without acquiring a CPU slot; stopped pending retry after clean unit gate. First relative --out invocation failed to resolve mini/report paths; subsequent invocations use absolute output paths.

cache-final pushTitleCache__Q33ipl8savedata7ManagerFUx: Restore exact unsigned predecessor candidate with exact makeTmpList retained.
POOL IDENTICAL up to 3 (mine=3 base=3); 100.0%; src 0xe8 base 0xe8 insns 58/58; diffs 0: []
Evidence: build/da1/cache-final

SaveDataManager full clean gate build/da1/save-full-gate.txt: GATE PASS. makeTmpList and pushTitleCache CONVERTED; hasChannel, makePriorTitleIDList and doUpdateChanInfos retain original asm. 35/35 exact unchanged, code 7172/7172, data 968/968; regressions 0; forbidden/readability 0; required DOL hash unchanged. update source search ran 14 trials without improving 68/67 instructions. Stage each exact conversion separately.

cdb-delete-1 cdb_backup_delete_task___3iplFPv: Use typed CdbBackup methods and existing CDB API, preserve date arguments and declaration order.
POOL IDENTICAL up to 2 (mine=2 base=2); 99.781815%; src 0xdc base 0xdc insns 55/55; diffs 2: [50, 51]
Evidence: build/da1/cdb-delete-1

cdb-delete-2 cdb_backup_delete_task___3iplFPv: Complete via a reference-taking static inline finishBackup helper.
POOL IDENTICAL up to 2 (mine=2 base=2); 99.781815%; src 0xdc base 0xdc insns 55/55; diffs 2: [50, 51]
Evidence: build/da1/cdb-delete-2

cdb-delete-3 cdb_backup_delete_task___3iplFPv: Const dates and block-local const backup pointer initialized after the date calls.
POOL IDENTICAL up to 2 (mine=2 base=2); 99.781815%; src 0xdc base 0xdc insns 55/55; diffs 2: [50, 51]
Evidence: build/da1/cdb-delete-3

cdb-delete-4 cdb_backup_delete_task___3iplFPv: Return the void completion setter expression to expose final-use lifetime.
POOL IDENTICAL up to 2 (mine=2 base=2); 99.781815%; src 0xdc base 0xdc insns 55/55; diffs 2: [50, 51]
Evidence: build/da1/cdb-delete-4

cdb_backup_delete_task_ provisionally KEPT ASM after four distinct compiled C++ variants. Each is 99.781815%, 55/55 instructions, only diffs 50/51: lwz r31,0x1c and lwz r0,0x24 in reverse order. Scope/reference/const/return-form levers do not change epilogue scheduling.

cdb-move-1 cdb_backup_move_task___3iplFPv: Use typed backup methods and const date locals; keep separate free-size loads and search arguments.
POOL IDENTICAL up to 2 (mine=2 base=2); 99.82609%; src 0x114 base 0x114 insns 69/69; diffs 2: [64, 65]
Evidence: build/da1/cdb-move-1

cdb-move-2 cdb_backup_move_task___3iplFPv: Pointer-taking completion helper instead of direct member call.
POOL IDENTICAL up to 2 (mine=2 base=2); 99.82609%; src 0x114 base 0x114 insns 69/69; diffs 2: [64, 65]
Evidence: build/da1/cdb-move-2

cdb-move-3 cdb_backup_move_task___3iplFPv: Nonconst date inputs, const backup pointer and returned void completion expression.
POOL IDENTICAL up to 2 (mine=2 base=2); 99.82609%; src 0x114 base 0x114 insns 69/69; diffs 2: [64, 65]
Evidence: build/da1/cdb-move-3

cdb-move-4 cdb_backup_move_task___3iplFPv: Separate use of original worker argument for search and final typed completion.
POOL IDENTICAL up to 2 (mine=2 base=2); 99.82609%; src 0x114 base 0x114 insns 69/69; diffs 2: [64, 65]
Evidence: build/da1/cdb-move-4

cdb_backup_move_task_ provisionally KEPT ASM after four distinct compiled variants. Every trial 99.82609%, 69/69 instructions, only diffs 64/65: reverse epilogue loads of r31 and LR. Original CdbBackup.cpp restored in full. Searches use a local srcsearch copy whose definition finder skips forward declarations; shared script unchanged.

warning-1 warning_run__Q23ipl6SystemFv: Normal warning render/update loop using existing accessors and visibility restoration; preserve named fatal-state and reset predicates.
POOL IDENTICAL up to 52 (mine=52 base=52); 98.66477%; src 0x2c0 base 0x2c0 insns 176/176; diffs 47: [8, 9, 16, 19, 20, 21, 23, 25, 27, 30, 32, 35, 37, 40, 50, 59, 61, 64, 69, 71]
Evidence: build/da1/warning-1

warning-2 warning_run__Q23ipl6SystemFv: Bind System::Arg as an early const reference for framework operations.
POOL IDENTICAL up to 52 (mine=52 base=52); 98.66477%; src 0x2c0 base 0x2c0 insns 176/176; diffs 47: [8, 9, 16, 19, 20, 21, 23, 25, 27, 30, 32, 35, 37, 40, 50, 59, 61, 64, 69, 71]
Evidence: build/da1/warning-2

warning-3 warning_run__Q23ipl6SystemFv: Use one typed System::Arg pointer for member accesses throughout the loop.
POOL IDENTICAL up to 52 (mine=52 base=52); 97.5%; src 0x2b8 base 0x2c0 insns 174/176; --- replace mine 8:10 base 8:10
Evidence: build/da1/warning-3

warning-4 warning_run__Q23ipl6SystemFv: Nest the body under the positive not-resetting guard instead of an early return.
POOL IDENTICAL up to 52 (mine=52 base=52); 98.66477%; src 0x2c0 base 0x2c0 insns 176/176; diffs 47: [8, 9, 16, 19, 20, 21, 23, 25, 27, 30, 32, 35, 37, 40, 50, 59, 61, 64, 69, 71]
Evidence: build/da1/warning-4

warning-5 warning_run__Q23ipl6SystemFv: Use explicit loop exit when warning check finishes.
POOL IDENTICAL up to 52 (mine=52 base=52); 98.66477%; src 0x2c0 base 0x2c0 insns 176/176; diffs 47: [8, 9, 16, 19, 20, 21, 23, 25, 27, 30, 32, 35, 37, 40, 50, 59, 61, 64, 69, 71]
Evidence: build/da1/warning-5

warning-6 warning_run__Q23ipl6SystemFv: Static inline viewport/scissor setup helper changes boundaries for float-conversion temporaries.
POOL IDENTICAL up to 52 (mine=52 base=52); 98.66477%; src 0x2c0 base 0x2c0 insns 176/176; diffs 47: [8, 9, 16, 19, 20, 21, 23, 25, 27, 30, 32, 35, 37, 40, 50, 59, 61, 64, 69, 71]
Evidence: build/da1/warning-6

warning-7 warning_run__Q23ipl6SystemFv: Use a const SDK BOOL for saved visibility.
POOL IDENTICAL up to 52 (mine=52 base=52); 98.52273%; src 0x2c0 base 0x2c0 insns 176/176; diffs 52: [8, 9, 16, 19, 20, 21, 23, 25, 27, 30, 32, 35, 37, 39, 40, 42, 44, 50, 54, 56]
Evidence: build/da1/warning-7

warning-8 warning_run__Q23ipl6SystemFv: Declare saved visibility before reset guard, assign only on the active warning path.
POOL IDENTICAL up to 52 (mine=52 base=52); 98.66477%; src 0x2c0 base 0x2c0 insns 176/176; diffs 47: [8, 9, 16, 19, 20, 21, 23, 25, 27, 30, 32, 35, 37, 40, 50, 59, 61, 64, 69, 71]
Evidence: build/da1/warning-8

warning_run provisionally KEPT ASM. Eight compiled variants. Best 98.66477%, 176/176, 47 register-only diffs: global System::Arg base r31 instead of r28, visibility r28 instead of r29, integer conversion r29 instead of r30, sound base r30 instead of r31. Other instructions identical. Tried const/reference/pointer state, loop and guard directions, scoped viewport helper, BOOL and declaration order. Original System.cpp restored.

exception-1 exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead: Use typed console APIs and KPAD loops; write only changed horizontal position as target proves.
POOL IDENTICAL up to 0 (mine=0 base=0); 97.60204%; src 0x188 base 0x188 insns 98/98; diffs 39: [6, 9, 11, 12, 15, 16, 17, 19, 22, 23, 25, 26, 27, 28, 35, 36, 37, 39, 40, 41]
Evidence: build/da1/exception-1

exception-2 exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead: Static inline KPAD-read helper for one four-controller polling pass.
COMPILE FAIL: initial text replacement also altered key_input before the helper definition. Restored it, then restricted the helper to exception_callback in exception-5. Compiler diagnostic: undefined identifier 'readExceptionControllers'. Full output: build/da1/exception-2/build.txt.
Evidence: build/da1/exception-2

exception-3 exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead: Declare horizontal and vertical scroll state before initial auto-scroll; assign each before use.
POOL IDENTICAL up to 0 (mine=0 base=0); 97.85714%; src 0x188 base 0x188 insns 98/98; diffs 36: [6, 11, 12, 15, 17, 19, 23, 25, 26, 27, 28, 35, 36, 37, 39, 40, 41, 44, 48, 51]
Evidence: build/da1/exception-3

exception-4 exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead: Named const controller bound and const previous coordinates declared in x/y order.
POOL IDENTICAL up to 0 (mine=0 base=0); 97.39796%; src 0x188 base 0x188 insns 98/98; diffs 39: [6, 9, 11, 12, 15, 16, 17, 19, 22, 23, 25, 26, 27, 28, 35, 36, 37, 39, 40, 41]
Evidence: build/da1/exception-4

exception-5 exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead: Restrict read-controller helper to callback; leave key_input unchanged.
POOL IDENTICAL up to 0 (mine=0 base=0); 98.0102%; src 0x188 base 0x188 insns 98/98; diffs 28: [11, 23, 26, 27, 35, 37, 38, 39, 40, 41, 43, 44, 47, 48, 49, 55, 64, 66, 70, 72]
Evidence: build/da1/exception-5

exception-6 exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead: Declare scroll coordinates in natural x/y order before the introductory scroll.
POOL IDENTICAL up to 0 (mine=0 base=0); 99.18367%; src 0x188 base 0x188 insns 98/98; diffs 13: [35, 39, 40, 41, 44, 48, 55, 76, 78, 82, 84, 89, 92]
Evidence: build/da1/exception-6

exception-7 exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead: Combine x/y declaration order with controller-read helper.
POOL IDENTICAL up to 0 (mine=0 base=0); 98.46939%; src 0x188 base 0x188 insns 98/98; diffs 23: [9, 16, 22, 23, 35, 37, 38, 39, 40, 41, 43, 44, 47, 48, 49, 55, 76, 78, 82, 84]
Evidence: build/da1/exception-7

exception-8 exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead: Limit introductory auto-scroll cursor to its own scope; keep persistent coordinates outside.
POOL IDENTICAL up to 0 (mine=0 base=0); 99.18367%; src 0x188 base 0x188 insns 98/98; diffs 13: [35, 39, 40, 41, 44, 48, 55, 76, 78, 82, 84, 89, 92]
Evidence: build/da1/exception-8

exception-9 exception_callback__Q23ipl9ExceptionFPQ44nw4r2db6detail11ConsoleHead: Declare loop bound before persistent coordinates to separate its lifetime from the read cursor.
POOL IDENTICAL up to 0 (mine=0 base=0); 99.18367%; src 0x188 base 0x188 insns 98/98; diffs 13: [35, 39, 40, 41, 44, 48, 55, 76, 78, 82, 84, 89, 92]
Evidence: build/da1/exception-9

exception_callback provisionally KEPT ASM. Eight successfully compiled variants plus one rejected helper placement that was immediately corrected. Best exception-6 is 99.18367%, 98/98, 13 register diffs: horizontal coordinate, controller bound and read-loop stride are assigned r26/r29/r27 rather than r29/r27/r26. Other code is instruction-identical. Source search running on immutable best candidate; source restored pending result.

compressGbaOdh data prerequisite: baseline packs four Huffman pointers and ten diagnostic strings into HufftreeData with raw message offsets. New C++ must use ordinary literals. Trial splits table from compiler-pooled diagnostic literals, replaces the five existing decompression offset calls with identical text, and converts compression normally. No symbol metadata changed; byte/pool and other-function output must still match before accepting.

odh-1 compressGbaOdh__9CArGBAOdhFPUcPUciiiUlPUci: Typed master/dimensions, normal retry loop and ordinary diagnostic literals; remove packed string blob.
POOL IDENTICAL up to 10 (mine=10 base=10); 100.0%; src 0x194 base 0x194 insns 101/101; diffs 0: []
Evidence: build/da1/odh-1

compressGbaOdh candidate exact on first reconstruction: 100.0%, 101/101, diffs 0. Ordinary diagnostic literals preserve pool 10/10 and all 459 emitted .data bytes versus target, whose remaining 5 bytes are alignment. .rodata 5856 and .sdata2 40 are byte-identical. No metadata edits: hufftreePtr source symbol now correctly contains 16 pointer bytes while original aggregate symbol spans 459 bytes; objdiff still reports every data section 100%. Existing decompressGbaOdh is 100.0%, 98/98, diffs 0; every other function score unchanged. Unit remains 26/28 exact, code 12876/14684, data 6360/6360. Removed five now-unused asm extern declarations.

odh-final compressGbaOdh__9CArGBAOdhFPUcPUciiiUlPUci: Remove unused asm externs; preserve ordinary string pooling and typed Huffman pointer table.
POOL IDENTICAL up to 10 (mine=10 base=10); 100.0%; src 0x194 base 0x194 insns 101/101; diffs 0: []
Evidence: build/da1/odh-final

Automated search outcomes: prior 23 compiled trials and update 14 compiled trials produced no gain. hasChannel first waited 7 minutes and its bounded retry waited 180 seconds without a slot. Cdb delete, Cdb move, warning_run and exception_callback also timed out at the shared 24-slot limiter before printing target counts or compiling any trial. Their results are supported by the manual source trials above, not by a claim of exhaustive automated search. No search process remains.

Open-function audit: hasChannel 5 compiled attempts; makePriorTitleIDList 4 plus 23 source-search trials; doUpdateChanInfos 5 plus 14 source-search trials; Cdb delete 4; Cdb move 4; warning_run 8; exception_callback 8 successful compilations plus one compiler-rejected helper placement. All seven original asm bodies restored. Converted functions: doSave, makeTmpList, pushTitleCache, compressGbaOdh.

## Final clean verification

Full non-quick gate across all six assigned units passes. Every unit measure in the full 1027-unit report is unchanged from the fresh bfe77b7f baseline. Of 1027 rebuilt source objects, only the three edited units have different object-file hashes; the other 1024 are byte-identical. All four converted functions are exact-name 100.0% with equal instruction counts and ctxdiff diffs 0. decompressGbaOdh also remains exact. Both odh string-argument audits check five calls each with zero candidates, skips or errors.

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/system/iplKeyboard] pool: IDENTICAL
[src/system/iplKeyboard] objdiff: code 6024/6024 data 1184/1184 functions 32/32 fuzzy 100.0000 linked code 6024
[src/system/iplKeyboard] instruction-exact functions: 32/32
[src/system/iplSaveDataManager] pool: IDENTICAL
[src/system/iplSaveDataManager] objdiff: code 7172/7172 data 968/968 functions 35/35 fuzzy 100.0000 linked code 7172
[src/system/iplSaveDataManager] instruction-exact functions: 35/35
[src/system/iplCdbBackup] pool: IDENTICAL
[src/system/iplCdbBackup] objdiff: code 4012/4012 data 108/108 functions 26/26 fuzzy 100.0000 linked code 4012
[src/system/iplCdbBackup] instruction-exact functions: 26/26
[src/system/iplSystem] pool: IDENTICAL
[src/system/iplSystem] objdiff: code 12456/12456 data 2228/2228 functions 63/63 fuzzy 100.0000 linked code 12456
[src/system/iplSystem] instruction-exact functions: 63/63
[src/system/iplException] pool: IDENTICAL
[src/system/iplException] objdiff: code 1004/1004 data 32/32 functions 7/7 fuzzy 100.0000 linked code 1004
[src/system/iplException] instruction-exact functions: 7/7
[src/system/odh] pool: IDENTICAL
[src/system/odh] objdiff: code 12876/14684 data 6360/6360 functions 26/28 fuzzy 99.5546 linked code 0
[src/system/odh] instruction-exact functions: 26/28
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Unit counts, matched code and matched data before -> after are unchanged at the numbers above. The improvement is removal of four game asm bodies. odh retains its two preexisting unassigned C++ mismatches, LineConv11 at 98.08219% and huffmanDecoder at 95.57189%; it remains NonMatching and unlinked.

Evidence: build/da1/final-full-gate.txt, build/da1/final-ctxdiff.txt, build/da1/object-isolation.json, build/da1-baseline-report.json and build/da1-final-report.json. All seven remaining assigned asm bodies have their original bytes and at least four compiled C++ attempts recorded above. No push, PR, merge or rebase.
