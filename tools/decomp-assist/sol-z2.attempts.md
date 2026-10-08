# sol-z2 CHANSVmStep carrier removal

Worktree data-d2, branch agent/w1009/data-d2-c, base c723136f. Source scope is CHANSVmStep in src/channelScript/CHANSVm.c. The task requires committing the integrity fix after a passing gate even if Step remains non-exact.

Read sol-common.md, brief-v2.md, every lever, local AGENTS.md, unslop and writing-for-agents. Fetched origin with the shared Git lock. Source and branch were clean and current. Baseline Ninja build passed; pool identical 125/125; Step 276 differing, 1253/1253 instructions. Baseline object and report saved under /tmp/sol-z2-* for direct regression checks.

Collected 187 unique earlier Step entries from repository and archived logs. Read sol-vm, sol-x1, rx1b, big1 and earlier CHANSVm stack/control experiments. Prior attempts already cover countdown spellings, flattened/direct result tables, indexed enumeration, helper reconstruction, parameter copying, and four independent-buffer declarations. Do not repeat these on the unchanged source. This round tests allocation and scopes after mandatory carrier removal, starting with sol-y4's 264-difference Step shape only. VmBlobPackCommon is outside scope and its saved edits are excluded.

Target stack access audit covers all r1-relative accesses, including the saved-register frame. Live local slots: boolean result 0x08, branch predicate/property iterator spill 0x0c, parsed array index 0x10-0x17, bitwise integer 0x18-0x1f, operand types 0x20-0x27, float literal 0x28-0x2f, index/store copies 0x30-0x4f, indirect-load header 0x50-0x5f, binary operand 0x60-0x6f. Saved GPR area starts above these; FPR saves at 0xc0, 0xd0 and 0xe0; LR at 0xf4; frame 0xf0. Source baseline has an extra left-type spill at 0x70. Target enumeration uses right type first, an index and byte stride, then a 6x6 matrix lookup.

Ghidra's existing object export stops at the first paired-single save in Step and contains no useful full-function decompilation. Full target disassembly was read through odiff's per-word decoder, which preserves undecoded paired-single words and all 1253 positions.

## Trials
- replay-264: Replay sol-y4 Step only, without Pack changes. {"label": "replay-264", "diff": 264, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 10, "sha": "1c8265c74eb6"}
- plain-ascending: Ordinary locals on the newer instruction-bitfield source, declaration order ascending. {"label": "plain-ascending", "diff": 279, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 25, "sha": "5e35278c6dac"}
- plain-ascending-float-scope: Float literal belongs only to LOAD_FLOAT; other buffers retain function scope. {"label": "plain-ascending-float-scope", "diff": 279, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 25, "sha": "9e7013aa53b4"}
- plain-ascending-case-scopes: Float and indirect-load headers in their opcode blocks. {"label": "plain-ascending-case-scopes", "diff": 279, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 25, "sha": "1e2b8280c12b"}
- plain-descending: Ordinary locals on the newer instruction-bitfield source, declaration order descending. {"label": "plain-descending", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "d0d5196b90ff"}
- plain-descending-float-scope: Float literal belongs only to LOAD_FLOAT; other buffers retain function scope. {"label": "plain-descending-float-scope", "diff": 279, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 25, "sha": "7ffdaa26a0ee"}
- plain-descending-case-scopes: Float and indirect-load headers in their opcode blocks. {"label": "plain-descending-case-scopes", "diff": 279, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 25, "sha": "8d4dbb944cb0"}
- separate-headers-target: Independent index, indirect-store, indirect-load and binary headers; direct store addresses follow target. {"label": "separate-headers-target", "diff": 1235, "insns": [1251, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "563e26a40a62"}
- separate-headers-target-float-case: Independent opcode headers with float literal in LOAD_FLOAT scope. {"label": "separate-headers-target-float-case", "diff": 1235, "insns": [1251, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "3bf381ecc0b1"}
- separate-headers-target-case-scopes: Indirect load and store headers belong to their separate opcode scopes. {"label": "separate-headers-target-case-scopes", "diff": 1235, "insns": [1251, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "5ef52b57bde4"}
- separate-headers-swap-load-operand: Independent index, indirect-store, indirect-load and binary headers; direct store addresses follow target. {"label": "separate-headers-swap-load-operand", "diff": 1235, "insns": [1251, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "79aea5b5f9fe"}
- separate-headers-swap-load-operand-float-case: Independent opcode headers with float literal in LOAD_FLOAT scope. {"label": "separate-headers-swap-load-operand-float-case", "diff": 1235, "insns": [1251, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "6b810090caf8"}
- separate-headers-swap-load-operand-case-scopes: Indirect load and store headers belong to their separate opcode scopes. {"label": "separate-headers-swap-load-operand-case-scopes", "diff": 1235, "insns": [1251, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "5ef52b57bde4"}
- separate-headers-forward: Independent index, indirect-store, indirect-load and binary headers; direct store addresses follow target. {"label": "separate-headers-forward", "diff": 1235, "insns": [1251, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "add41d46a731"}
- separate-headers-forward-float-case: Independent opcode headers with float literal in LOAD_FLOAT scope. {"label": "separate-headers-forward-float-case", "diff": 1235, "insns": [1251, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "76f49adc34b9"}
- separate-headers-forward-case-scopes: Indirect load and store headers belong to their separate opcode scopes. {"label": "separate-headers-forward-case-scopes", "diff": 1235, "insns": [1251, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "3881e866e432"}
- headers-while-if-pointer: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-while-if-pointer", "diff": 501, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 12, "sha": "b32b521b6a4c"}
- headers-while-if-index: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-while-if-index", "diff": 1232, "insns": [1254, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 55, "sha": "b03219306843"}
- headers-while-if-byte-offset: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-while-if-byte-offset", "diff": 1230, "insns": [1254, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 55, "sha": "ab9108dd4800"}
- headers-while-ternary-pointer: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-while-ternary-pointer", "diff": 1234, "insns": [1255, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "43386fc6612f"}
- headers-while-ternary-index: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-while-ternary-index", "diff": 1232, "insns": [1256, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 55, "sha": "cdd92bf5c92e"}
- headers-while-ternary-byte-offset: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-while-ternary-byte-offset", "diff": 1228, "insns": [1256, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 53, "sha": "4bb02843680e"}
- headers-for-if-pointer: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-for-if-pointer", "diff": 503, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 12, "sha": "fded378eef39"}
- headers-for-if-index: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-for-if-index", "diff": 1231, "insns": [1254, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 55, "sha": "a0c6d7bc3e35"}
- headers-for-if-byte-offset: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-for-if-byte-offset", "diff": 1229, "insns": [1254, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 55, "sha": "55f9dad03d65"}
- headers-for-ternary-pointer: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-for-ternary-pointer", "diff": 1234, "insns": [1255, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 56, "sha": "5a83b6b86d7d"}
- headers-for-ternary-index: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-for-ternary-index", "diff": 1232, "insns": [1256, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 55, "sha": "737fbbd2a605"}
- headers-for-ternary-byte-offset: Separate opcode headers combined with target loop and enumeration shape. Byte-offset traversal is diagnostic only. {"label": "headers-for-ternary-byte-offset", "diff": 1228, "insns": [1256, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 53, "sha": "e8435075d7da"}
- plain-scoped-optimization_level-0: Lever 30 scoped setting on independent locals. Retain only if supported by target structure. {"label": "plain-scoped-optimization_level-0", "diff": 1671, "insns": [1675, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 455, "sha": "1dcb2dc5e857"}
- plain-scoped-optimization_level-1: Lever 30 scoped setting on independent locals. Retain only if supported by target structure. {"label": "plain-scoped-optimization_level-1", "diff": 1227, "insns": [1279, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 60, "sha": "10cee536bbb2"}
- plain-scoped-optimization_level-2: Lever 30 scoped setting on independent locals. Retain only if supported by target structure. {"label": "plain-scoped-optimization_level-2", "diff": 1244, "insns": [1259, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 54, "sha": "efe92d3ea6f1"}
- plain-scoped-optimization_level-3: Lever 30 scoped setting on independent locals. Retain only if supported by target structure. {"label": "plain-scoped-optimization_level-3", "diff": 288, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "d30fca46bd0e"}
- plain-scoped-ppc_iro_level-0: Lever 30 scoped setting on independent locals. Retain only if supported by target structure. {"label": "plain-scoped-ppc_iro_level-0", "diff": 1124, "insns": [1264, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 42, "sha": "8d6c08d20cc5"}
- plain-scoped-ppc_iro_level-1: Lever 30 scoped setting on independent locals. Retain only if supported by target structure. {"label": "plain-scoped-ppc_iro_level-1", "diff": 1240, "insns": [1259, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 51, "sha": "26ac8cf43428"}
- plain-function-locals-loop: Lever 29: ordinary loop/opcode declarations in function scope, preserving execution and storage objects. {"label": "plain-function-locals-loop", "diff": 277, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "140aa6cfe445"}
- plain-function-locals-loop-split-init: Lever 29: declaration and initialization of real result-table pointer separated. {"label": "plain-function-locals-loop-split-init", "diff": 277, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "86ebea74e87b"}
- plain-function-locals-opcode: Lever 29: ordinary loop/opcode declarations in function scope, preserving execution and storage objects. {"label": "plain-function-locals-opcode", "diff": 356, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "7e9cadbc793b"}
- plain-function-locals-opcode-split-init: Lever 29: declaration and initialization of real result-table pointer separated. {"label": "plain-function-locals-opcode-split-init", "diff": 356, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "1934709ed569"}
- plain-function-locals-both: Lever 29: ordinary loop/opcode declarations in function scope, preserving execution and storage objects. {"label": "plain-function-locals-both", "diff": 355, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "4f5e94c09036"}
- plain-function-locals-both-split-init: Lever 29: declaration and initialization of real result-table pointer separated. {"label": "plain-function-locals-both-split-init", "diff": 355, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "f142d6865b22"}
- plain-header-placement-copies: compile failed. Opcode-local copies/load or ordinary binary operand declaration after the typed/float locals.
- plain-header-placement-operand: Opcode-local copies/load or ordinary binary operand declaration after the typed/float locals. {"label": "plain-header-placement-operand", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "f5d48214c47f"}
- plain-header-placement-load: Opcode-local copies/load or ordinary binary operand declaration after the typed/float locals. {"label": "plain-header-placement-load", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "20a2cfbff722"}

Lever 30 optsweep on the carrier-free unit completed with no leads. Scoped optimization levels 0-3 and IRO 0-1 were measured separately above; no accepted setting. The 180-second full Step debugger capture timed out after the initial backend dump, before coloring. A fresh 600-second capture uses the immutable /tmp/sol-z2-plain-descending.c source so other verification cannot change its input.

Source review: instruction.raw always contains a zero-extended opcode byte, so its class bitfield equals the existing 0xc0 class mask. Every raw opcode use is preserved. All five 6x6 result matrices are symmetric, verified from the live source, so right-first enumeration produces the same conversion type. CHANSVmGetEnumedType only writes its supplied output and returns validation success. Independent operand, load, float and type objects preserve each existing use; copies remains the real two-header array. No code comments, forced layout, offset casts, uninitialized objects, or artificial helper were added.

Selected plain-descending: Step 97.17638%, 275 differences, 1253/1253 instructions. Main baseline 96.98723%, 276 differences; saved sol-y4 carrier candidate 97.18915%, 264 differences. Code 44588/53564, data 6904/6904, exact 227/233 unchanged. Every other function remains byte-identical to the freshly built initial object. No scoped setting improved this source. Full target offsets remain unresolved: independent array storage is sorted after the individual 16-byte headers, while splitting the array reproduces stack slots but removes two instructions and loses data matching. Keep the array version for the required no-regression cleanup.
- plain-type-u8-left: Use the actual byte or object enum for the binary operand type; no arithmetic change. {"label": "plain-type-u8-left", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "b84db5333130"}
- plain-type-u8-right: Use the actual byte or object enum for the binary operand type; no arithmetic change. {"label": "plain-type-u8-right", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "3e84ff073411"}
- plain-type-u8-both: Use the actual byte or object enum for the binary operand type; no arithmetic change. {"label": "plain-type-u8-both", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "6b9350a2c4c2"}
- plain-type-CHANSVmObjType-left: Use the actual byte or object enum for the binary operand type; no arithmetic change. {"label": "plain-type-CHANSVmObjType-left", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "9f2b6739362a"}
- plain-type-CHANSVmObjType-right: Use the actual byte or object enum for the binary operand type; no arithmetic change. {"label": "plain-type-CHANSVmObjType-right", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "1b74355d453a"}
- plain-type-CHANSVmObjType-both: Use the actual byte or object enum for the binary operand type; no arithmetic change. {"label": "plain-type-CHANSVmObjType-both", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "694a6bd62662"}
- plain-conversion-enum: Ordinary typed local follows its use and target comparisons. {"label": "plain-conversion-enum", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "5831013483a3"}
- plain-opcode-size-int: Ordinary typed local follows its use and target comparisons. {"label": "plain-opcode-size-int", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "caa205040dec"}
- plain-loop-count-int: Ordinary typed local follows its use and target comparisons. {"label": "plain-loop-count-int", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "e3474057fb76"}
- plain-copies-opcode-scope: Two copy headers belong only to the base opcodes; declaration precedes statements. {"label": "plain-copies-opcode-scope", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "0672cb70cbd9"}

## Accepted integrity checkpoint

Requested quick gate PASS after a full 43U build. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Pool identical; every data section 100%; exact 227/233; regressions 0; net forbidden patterns 0; readability warnings 0. Step remains non-exact at 97.17638%, ctxdiff 275, 1253/1253 instructions. Direct ELF text comparison confirms all 232 other function bodies byte-identical to the initial source object, including the five existing non-exact functions.

Gate output:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 44588/53564 data 6904/6904 functions 227/233 fuzzy 99.5821 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 227/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.58211
[src/channelScript/CHANSVm]   below 100: CHANSVmConvertToFloatFromStr 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 98.0988
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 97.17638
[src/channelScript/CHANSVm] baseline: code 44588/53564 data 6904 functions 227 fuzzy 99.5644
regressions vs baseline: 0
global matched_code_percent: 97.95043 -> 97.95043
global fuzzy_match_percent: 99.90734 -> 99.90766
global complete_code_percent: 89.90470 -> 89.90470
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Carrier-free best saved to /mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-z2.CHANSVm.diff. Branch remains based on c723136f; origin advanced while this worker ran. No rebase, merge, push, PR or cross-worktree source edit.

## Allocator evidence

Completed fresh carrier-free capture at /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/sol-z2-Step-plain-full. Captured Step instruction stream equals the selected Ninja object. Final GPR allocation uses a second pass after spilling; regsim reproduces 491/491 virtual registers. vmap2 aligns 1067 scheduled positions and confirms opSize r26 versus target r21, leftOp r23 versus r18, rightOp r21 versus r17, conversion type r24 versus r19, resultTypes r27 versus r28, and stackPtr r28 versus r24. opKind r22 and opFunc r20 already agree. enumedType pointer r18 must become the target byte-stride r31, and typeIdx r19 must become r26; the target computes the output pointer inside the loop.

A permissive 5000-step model reaches 7/7 selected named colors but relocates function parameters and the compiler split value instruction'450. This is not a source declaration order and is rejected. A second search freezes parameters and all compiler aliases, only swapping actual locals inside their existing function/loop/opcode scopes. Its result is compiled next if it finds a lead.

Scoped 7000-step regsim search: 2/7 desired named colors initially, best 4/7. Parameters, compiler aliases, nested opcode locals and declaration scope boundaries were fixed. This shape cannot reach all requested saved-register colors by those declaration moves. Compile the all-scope suggestion and each scope separately before closing this diagnostic.
- model-order-all: Lever 25: compile the simulated declaration order with parameters and compiler aliases fixed; all scope. {"label": "model-order-all", "diff": 262, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "fb4ca779789d"}
- model-order-root: Lever 25: compile the simulated declaration order with parameters and compiler aliases fixed; root scope. {"label": "model-order-root", "diff": 274, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "0791034aa392"}
- model-order-loop: Lever 25: compile the simulated declaration order with parameters and compiler aliases fixed; loop scope. {"label": "model-order-loop", "diff": 275, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "ae7b996995a8"}
- model-order-opcode: Lever 25: compile the simulated declaration order with parameters and compiler aliases fixed; opcode scope. {"label": "model-order-opcode", "diff": 263, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "2db90f4d05f8"}
- model-order-root-opcode: Remove the loop declaration permutation, retaining only the measured root and opcode changes. {"label": "model-order-root-opcode", "diff": 262, "insns": [1253, 1253], "changed_others": [], "pool": "POOL IDENTICAL up to 125 (mine=125 base=125)", "stack_diffs": 21, "sha": "d876106c08b8"}

## Final retained source

Compiled scoped model orders: all scopes 262 differences, root only 274, loop only 275, opcode only 263. Removed the loop declaration moves because root plus opcode alone still gives 262. Applied only those two orders to the readable source with normal whitespace. The target keeps the operand in 0x60, load in 0x50 and copies in 0x30-0x4f; retained ordinary declarations still put operand in 0x40, load in 0x30 and copies in 0x50-0x6f. Float and type-array slots agree at 0x28 and 0x20. This is the remaining layout blocker, together with the extra shared-table base, operand-type spill and loop/control differences.

Final Step 97.23225%, 262 differing instructions, 1253/1253 instructions. Main start 276; saved carrier best 264. Exact count 227/233 unchanged, matched code 44588/53564, data 6904/6904, all 232 other function bodies byte-identical to the initial source object. No new exact function. Scoped optimization tests and 7000 legal allocator simulations produced the retained declaration lead; 56 compiled source candidates plus the final root/opcode check are recorded above.

Final requested gate:

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/channelScript/CHANSVm] pool: IDENTICAL
[src/channelScript/CHANSVm] objdiff: code 44588/53564 data 6904/6904 functions 227/233 fuzzy 99.5873 linked code 0
[src/channelScript/CHANSVm] instruction-exact functions: 227/233
[src/channelScript/CHANSVm]   section .data size 4672 match 100.0
[src/channelScript/CHANSVm]   section .rodata size 1432 match 100.0
[src/channelScript/CHANSVm]   section .sbss size 16 match 100.0
[src/channelScript/CHANSVm]   section .sdata size 600 match 100.0
[src/channelScript/CHANSVm]   section .sdata2 size 184 match 100.0
[src/channelScript/CHANSVm]   section .text size 53564 match 99.58733
[src/channelScript/CHANSVm]   below 100: CHANSVmConvertToFloatFromStr 97.59036
[src/channelScript/CHANSVm]   below 100: VmDateDtor 94.96703
[src/channelScript/CHANSVm]   below 100: VmBlobGetHexString 98.71951
[src/channelScript/CHANSVm]   below 100: VmBlobPackCommon 98.0988
[src/channelScript/CHANSVm]   below 100: VmWinEmuWrite 99.62687
[src/channelScript/CHANSVm]   below 100: CHANSVmStep 97.23225
[src/channelScript/CHANSVm] baseline: code 44588/53564 data 6904 functions 227 fuzzy 99.5644
regressions vs baseline: 0
global matched_code_percent: 97.95043 -> 97.95043
global fuzzy_match_percent: 99.90734 -> 99.90777
global complete_code_percent: 89.90470 -> 89.90470
global matched_data_percent: 100.00000 -> 100.00000
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Fresh report regenerated at build/43U/report.json. Source and this log are the only staged paths. Carrier removal is retained and committed under the task-specific integrity deliverable, despite Step remaining non-exact. No configuration/linking change.
