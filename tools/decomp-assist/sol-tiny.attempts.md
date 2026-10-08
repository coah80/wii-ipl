# sol-tiny scheduler and allocator analysis

Assigned branch agent/w1008/sol-high-f, HEAD f49f337c. Full 43U build first passed, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Source baseline is clean; existing untracked rx4/rx59/rx70 files belong to earlier work and are preserved. No pushes, PRs, merges, rebases or other worktree edits.

Prior evidence read before implementation: main and local BS2Mach, kbd_lib, data-d13, scene4, structural-matching, sol-high rounds and register sweeps; historical sol-kbd at 9af09e10, sol-addr at 1d9fcfe8 and sol-bs2 at 58e02efc recovered with git show because those logs are absent from HEAD; opus-bs2 in the assigned checkout. The broad grep also identifies old fz1/fz15/fz16 sweeps. Previous declaration permutations, ordinary pointer/const casts, name accessors, inline parameter permutations, status spellings and volatility sweeps are excluded from this round.

Acceptance: equal size and zero instruction differences, exact-name objdiff 100%, identical pools, no regressions or artificial source constructs. Commit exact functions individually. Restore non-exact source and save private diffs. Run the requested quick gate over the three owned units at the end. A restored baseline gate is not evidence of a new match.

## Baseline

| Unit | Exact functions | Code | Data | Pool |
| --- | --- | --- | --- | --- |
| BS2Mach | 26/29 | 6024/16980 | 158528/158528 | 91/91 |
| iplAddressEdit | 91/94 | 23344/27112 | 2560/2560 | 57/57 |
| kbd_lib | 18/21 | 4472/5764 | 5296/5296 | 0/0 narrow strings |

## CheckBS2CommandStatus

Baseline 2/406 differing, equal 1624-byte size. The only swap is CCC store and shift in case 0x12.

| Operation | Register dependencies | Memory dependencies | Latency class |
| --- | --- | --- | --- |
| lwz r4,DataToc | defines r4 | reads global pointer | load |
| stw r6,NandPending | reads r6 | writes volatile pending flag | store |
| lwz r5,CacheLength | defines r5 | reads volatile cache length | load |
| lwz r3,0(r4) | reads r4, defines r3 | reads TOC partition count | load |
| slwi r3,r3,3 | reads and writes r3 | none | integer rotate/mask |
| stw r6,CCC | reads r6 | writes completion flag | store |
| addi/rlwinm/add/addi | r3 chain and r5 | none | integer ALU |
| stw/lwz CacheLength | reads then defines r3 | volatile write followed by read | store/load |

Target places the independent completion store in the count-load latency slot. Source places it after the shift. Hypothesis to test with PCode: the indirect count read introduces a conservative memory edge to the completion store, or the store is lowered with different alias metadata. The target DAG is inferred from assembly, not captured from retail source.

## update_friendinfo

Baseline 2/38 differing, equal 152-byte size. Target prepares r4 before r3 after memset.

| Operation | Register dependencies | Memory dependencies | Latency class |
| --- | --- | --- | --- |
| addi r3,r31,8 | reads saved sFriendInfo base, defines argument r3 | computes name address only | integer ALU |
| addi r4,r30,0x2b4 | reads saved this, defines argument r4 | computes String name address only | integer ALU |
| li r5,10 | defines argument r5 | none | integer ALU |
| bl wcsncpy | consumes r3/r4/r5, clobbers caller-saved registers | reads name source and writes destination | call |

The pair has no true register or memory dependency. Prior accessor trials preserve the order before allocation. A different creation/evaluation order or a move eliminated after scheduling is required; changing the text of the same address expression cannot create such an edge. Inspect frontend-to-backend PCode and any return value from memset before testing new address provenance.

## kbd_led_handler

Baseline 3/25 differing, equal 100-byte size. This is a CFG layout difference rather than an instruction scheduler swap: target cmpwi success,1 / bne error / li 0 / b join / li 7. Source dispatches beq success / li 7 / b join / li 0.

cmpwi reads r3 and defines CR0, conditional branch consumes CR0; both li operations define argument r3 on disjoint paths; join tail consumes r3 plus callback index r4. All status operations are integer/branch class and do not touch memory. The callback guard reads the callback pointer and command slot, clears the slot and returns when pointer is null. Target and source guard graphs currently match.

The DAG difference is control dependence and block fallthrough, not latency. A real callback selection which prevents early constant-select folding may retain the target if/else layout. Ordinary if/ternary, switch-case rearrangements and pointer-input notification helpers were already tried; repeat none of those.

## kbdProcMod and KBDSetModState

Baselines 4/256 and 4/42, equal 1024/168-byte sizes. Both swaps come from the same inlined physical-modifier merge in KBDSetModState.

| Operation | Register dependencies | Memory dependencies | Latency class |
| --- | --- | --- | --- |
| lis/addi base | defines table base | address only | integer ALU |
| add address | reads base and channel offset, defines address | address only | integer ALU |
| lwz old,0x220(address) | reads address, defines old | reads channel modifier word | load |
| rlwimi new,old,0,26,31 | reads old and masked new, writes new | none | integer rotate/insert |
| stw new,0x220(address) | reads new and address | writes same modifier word | store |

Target address=r4, old=r5. Source address=r5, old=r4. The address remains live through the store and interferes with old. Both instruction sequences have the same order and dependency chain. The target needs a different coloring priority or coalescing graph, not instruction reordering. Historical captures identify the two values as unnamed temps, so named declaration permutations cannot change their priority. Trace the common setter and derive a construct which changes temp creation or introduces a useful merge move that disappears late.

## BS2StartGame

Baseline 5/393 differing, equal 1572-byte size. MMIO write at 0xCC003024.

| Operation | Register dependencies | Memory dependencies | Latency class |
| --- | --- | --- | --- |
| lis addr,0xCC00 | defines address base | address only | integer ALU |
| li bits,2 | defines bits | none | integer ALU |
| lwz old,0x3024(addr) | reads addr, defines old | MMIO read | load |
| ori bits,bits,4 | reads/writes bits | none | integer ALU |
| ori old,old,1 | reads/writes old | none | integer ALU |
| or bits,old,bits | reads old and bits, writes bits | none | integer ALU |
| stw bits,0x3024(addr) | reads bits and addr | MMIO write | store |

Target address=r4, old=r3; source address=r3, old=r4; bits=r0 in both. Same dependency DAG and physical interference, but opposite coloring order. Ordinary named pointer/value/bits declarations were already forwarded to unnamed temps. Trace the raw block and test only constructs predicted to change surviving temp priority or coalescing. Full inline rewrites which combine the two OR constants lose an instruction and are not a match.

## Measurements


### address-clear-in-source-argument

A real memset call in the source argument should make evaluation of that argument precede destination materialization. This tests a call-induced DAG change, unlike prior separate getter/helper statements. Clear still occurs before copying and both addresses have no side effects.

Source /tmp/sol-tiny-address-clear-in-source-argument.cpp, object /tmp/sol-tiny-address-clear-in-source-argument.o.

- update_friendinfo__Q33ipl5scene11AddressEditFv: 2 differing, 38/38 instructions; size 152/152.
- POOL IDENTICAL up to 57 (mine=57 base=57)

### modifier-aggregate-copy-store

Copy the actual four-byte modifier union into the channel word using memcpy. Unlike scalar-store helpers tried earlier, aggregate copy lowering can create its destination address after the old-word temp, then common it with the read address. Prediction: address priority moves above old-word priority without adding a runtime operation.

Source /tmp/sol-tiny-modifier-aggregate-copy-store.c, object /tmp/sol-tiny-modifier-aggregate-copy-store.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 58 differing, 261/256 instructions; size 1044/1024.
- KBDSetModState: 24 differing, 48/42 instructions; size 192/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### modifier-aggregate-copy-load

Use the aggregate copy for the actual old modifier word. This tests whether copy-source address propagation changes coalescing or temp identity before the shared physical-bit insertion. The interrupt interval, masks and scalar field layout remain identical.

Source /tmp/sol-tiny-modifier-aggregate-copy-load.c, object /tmp/sol-tiny-modifier-aggregate-copy-load.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 259 differing, 264/256 instructions; size 1056/1024.
- KBDSetModState: 49 differing, 51/42 instructions; size 204/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### led-predicate-control-dependence

Switch dispatch now consumes a comparison predicate rather than the raw callback status. Its case-FALSE branch should lower to success!=1 while the default is successful fallthrough. A temporary boolean comparison is expected to disappear late. This tests an extra control-dependence node; it is not a case-order permutation of the old raw-status switch.

Source /tmp/sol-tiny-led-predicate-control-dependence.c, object /tmp/sol-tiny-led-predicate-control-dependence.o.

- kbd_led_handler: 16 differing, 27/25 instructions; size 108/100.
- kbdProcMod: 4 differing, 256/256 instructions; size 1024/1024.
- KBDSetModState: 4 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### Validated captures

Fresh setter capture `_mwdbg/runs/sol-tiny-set-base` has source SHA256 73a09baeb394c13a2ccc5a8cac873f166276678c3b6dfca7855f3aee511c5d3b and complete object SHA256 6a85c207eaac2f59a57f1c2b16f05861bf20a1ca1250449848ef0fa7353d06de, byte-identical to the current Ninja object. Prior `sol-kbd-proc-base` has the same source and object hashes, so its PCode is current evidence. Existing address capture `update_friendinfo__Q33ipl5scene11AddressEditFv-20261008-195401` likewise has the exact current source and whole-object bytes, independently compared this run.

regsim reproduces setter 23/23, proc 156/156 and address 16/16. Search over named-local numbering reproduces 0/2 desired address/old-word colors for both keyboard functions. Setter pre-allocation B8 has address r48 then old-word r49; r49 is colored first to r4, excluding r4 for r48, which gets r5. The address is live through the store, creating the r48/r49 edge. The masked destination r52 becomes r0; OSDisableInterrupts return is live in physical r3 for OSRestoreInterrupts. Proc has the corresponding address r181 / old-word r182. Both values are unnamed compiler temps, outside source declaration-order control.

Address backend-00 emits a dead return move from memset, reloads the global base, then emits addi r3 followed by addi r4. Backend-01 removes the return move and commons the global base across calls, but keeps the pair order. Backend-02, 03 and 04 retain that order. There is no register interference explanation for the scheduling swap; the initial argument-evaluation order already differs from retail. Call-in-source-argument trial lowers to the same final pair, rejecting that hypothesized source construct.

### address-memset-result-destination

Use memset's actual destination return value as the wcsncpy destination. This creates a real call-result edge rather than recomputing a separate address. Check whether MWCC replaces that return value with its known destination late enough to change argument preparation. No extra work or dummy value is introduced.

Source /tmp/sol-tiny-address-memset-result-destination.cpp, object /tmp/sol-tiny-address-memset-result-destination.o.

- update_friendinfo__Q33ipl5scene11AddressEditFv: 24 differing, 37/38 instructions; size 148/152.
- POOL IDENTICAL up to 57 (mine=57 base=57)

### command-count-before-completion-reload-for-write

Isolate only the first partition-count read, then store completion before shifting the saved count. Unlike prior sol-bs2 local-count trials, retain the second DataToc/count reload for BS2NANDDivideWriteAsync, which the target has. This separates the read-to-store alias edge from the read-to-shift edge without removing the later four instructions.

Source /tmp/sol-tiny-command-count-before-completion-reload-for-write.c, object /tmp/sol-tiny-command-count-before-completion-reload-for-write.o.

- CheckBS2CommandStatus: 7 differing, 406/406 instructions; size 1624/1624.
- BS2StartGame: 5 differing, 393/393 instructions; size 1572/1572.
- POOL IDENTICAL up to 91 (mine=91 base=91)

### command-save-length-and-count-before-completion

Preserve the baseline volatile CacheLength read before the partition-count read, then store completion and calculate the new length. This explicitly preserves the memory-read order while removing the shift from the completion-store predecessor chain. The write branch still reloads its own count.

Source /tmp/sol-tiny-command-save-length-and-count-before-completion.c, object /tmp/sol-tiny-command-save-length-and-count-before-completion.o.

- CheckBS2CommandStatus: 6 differing, 406/406 instructions; size 1624/1624.
- BS2StartGame: 5 differing, 393/393 instructions; size 1572/1572.
- POOL IDENTICAL up to 91 (mine=91 base=91)

### modifier-typed-union-assignment-store

The prior aggregate memcpy trials retained actual calls and stack storage, so reject that lowering. A typed four-byte union assignment should use aggregate load/store lowering without memcpy, creating a separate store lvalue whose address can common with the read later. The view names the actual modifier representation, not raw offsets or unrelated storage.

Source /tmp/sol-tiny-modifier-typed-union-assignment-store.c, object /tmp/sol-tiny-modifier-typed-union-assignment-store.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 4 differing, 256/256 instructions; size 1024/1024.
- KBDSetModState: 4 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### command-toc-disjoint-alias-contract

A restrict-qualified read-only TOC view asserts the actual disjointness of TOC storage and cache flags. It directly tests the load-to-store alias-edge hypothesis. Unlike the prior plain const pointer trials this adds an alias contract; the write branch still reads the original pointer. Retain only if the compiler supports the keyword and source/object evidence justifies it.

Source /tmp/sol-tiny-command-toc-disjoint-alias-contract.c, object /tmp/sol-tiny-command-toc-disjoint-alias-contract.o.

Compile failed: ### mwcceppc.exe Compiler: #    File: Z:\tmp\sol-tiny-command-toc-disjoint-alias-contract.c # -------------------------------------------------------------- #    1172:         const DVDGameTOC * restrict toc;  #   Error:                                     ^^^ #   (10123) ';' expected #   Too many errors printed, aborting program  User break, cancelled...

### command-completion-typed-state-storage

Replace the scalar completion storage with a single-field typed command state, preserving its four-byte representation and all accesses. A TOC field read and command-state field write now have distinct aggregate types, directly testing type-based alias separation. This is one real state field, with no grouped unrelated objects or padding.

Source /tmp/sol-tiny-command-completion-typed-state-storage.c, object /tmp/sol-tiny-command-completion-typed-state-storage.o.

- CheckBS2CommandStatus: 2 differing, 406/406 instructions; size 1624/1624.
- BS2StartGame: 5 differing, 393/393 instructions; size 1572/1572.
- POOL IDENTICAL up to 91 (mine=91 base=91)

### start-control-word-bitfield-promotion

The baseline old DI word survives as named scalar r33, while address becomes later temp r196. Represent the actual MMIO word and its low enable bit as a union, so stack/aggregate promotion creates a later load temp. Keep the independent diBits two-step construction unchanged to preserve li 2 / ori 4 rather than folding constants into ori 5. This changes old-word provenance, not declaration numbering.

Source /tmp/sol-tiny-start-control-word-bitfield-promotion.c, object /tmp/sol-tiny-start-control-word-bitfield-promotion.o.

- CheckBS2CommandStatus: 2 differing, 406/406 instructions; size 1624/1624.
- BS2StartGame: 7 differing, 393/393 instructions; size 1572/1572.
- POOL IDENTICAL up to 91 (mine=91 base=91)

### start-control-word-complete-update

Update the actual control word with both enable and legacy bits before storing it. The first union trial created a promoted old-word temp that took r0, displacing the separate bits to r4. A final aggregate field update should allocate the final OR result after that old-word temp rather than before it, leaving final result/bits in r0 and the loaded word in r3.

Source /tmp/sol-tiny-start-control-word-complete-update.c, object /tmp/sol-tiny-start-control-word-complete-update.o.

- CheckBS2CommandStatus: 2 differing, 406/406 instructions; size 1624/1624.
- BS2StartGame: 7 differing, 393/393 instructions; size 1572/1572.
- POOL IDENTICAL up to 91 (mine=91 base=91)

### led-output-parameter-conditional-stores

Use an actual output-parameter error converter with success passed by value. Previous both-pointer helpers also took success by pointer. This shape keeps the raw condition register available but hides the constant result behind conditional memory stores until inlining/promotion, which may preserve target fallthrough and remove the stores late.

Source /tmp/sol-tiny-led-output-parameter-conditional-stores.c, object /tmp/sol-tiny-led-output-parameter-conditional-stores.o.

- kbd_led_handler: 23 differing, 23/25 instructions; size 92/100.
- kbdProcMod: 4 differing, 256/256 instructions; size 1024/1024.
- KBDSetModState: 4 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### modifier-word-value-arguments

A real union-word merge takes both modifier values by value and returns the result. Prior helpers took a channel pointer and read the old word inside the helper. Here load/address provenance remains in the caller while aggregate parameter/return copies are introduced at the merge, testing a late coalescing change without pointer-read alias changes.

Source /tmp/sol-tiny-modifier-word-value-arguments.c, object /tmp/sol-tiny-modifier-word-value-arguments.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 4 differing, 256/256 instructions; size 1024/1024.
- KBDSetModState: 4 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### modifier-channel-field-union-representation

Model the actual channel modifier word as KBDModifierState at its declaration, preserving four-byte layout and scalar value access in every other function. Prior mod-channel-union trials changed only a local pointer, not the field type. Read the actual union object into oldState. This tests aggregate field lowering and alias metadata without extra storage.

Source /tmp/sol-tiny-modifier-channel-field-union-representation.c, object /tmp/sol-tiny-modifier-channel-field-union-representation.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 4 differing, 256/256 instructions; size 1024/1024.
- KBDSetModState: 4 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### modifier-direct-channel-physical-field

With the modifier representation in the real field, read physical bits directly into the requested union. The deleted oldState held a genuine copy that should be unnecessary. The field load may acquire a different temp identity than the baseline scalar-to-local-union copy; inspect the resulting address/word colors.

Source /tmp/sol-tiny-modifier-direct-channel-physical-field.c, object /tmp/sol-tiny-modifier-direct-channel-physical-field.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 47 differing, 253/256 instructions; size 1012/1024.
- KBDSetModState: 7 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### modifier-update-real-software-field

Assign the actual high software-modifier bitfield while leaving its low physical field intact under the same interrupt exclusion. It computes exactly the baseline 0xfc0 input mask plus old 0x3f bits. This tests whether target merge direction came from updating a declared field rather than merging two scalar representations.

Source /tmp/sol-tiny-modifier-update-real-software-field.c, object /tmp/sol-tiny-modifier-update-real-software-field.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 48 differing, 253/256 instructions; size 1012/1024.
- KBDSetModState: 7 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### address-clear-copy-output-helper

The direct memset-result trial preserved the returned destination and lost the required reload. Here a real clear-and-copy helper owns the source and record values while the call result supplies its destination. This combines a new actual return edge with the earlier helper boundary, testing whether the inliner late rematerializes the record name while preserving source-first evaluation.

Source /tmp/sol-tiny-address-clear-copy-output-helper.cpp, object /tmp/sol-tiny-address-clear-copy-output-helper.o.

- update_friendinfo__Q33ipl5scene11AddressEditFv: 24 differing, 37/38 instructions; size 148/152.
- POOL IDENTICAL up to 57 (mine=57 base=57)

### start-two-control-word-bitfield-promotion

The old-word-only union trial moved old to r0 and left mask in r4. Promote both actual control words as the same real bitfield representation. The final OR reads old then mask, so mask promotion should create the latest input temp, coloring mask/result to r0, old to r3 and address to r4. Both unions contain only the related register word and its bits; no unrelated locals or dummy storage.

Source /tmp/sol-tiny-start-two-control-word-bitfield-promotion.c, object /tmp/sol-tiny-start-two-control-word-bitfield-promotion.o.

- CheckBS2CommandStatus: 2 differing, 406/406 instructions; size 1624/1624.
- BS2StartGame: 5 differing, 393/393 instructions; size 1572/1572.
- POOL IDENTICAL up to 91 (mine=91 base=91)

### command-readonly-toc-and-explicit-output-aliases

A real accounting helper takes a const TOC parameter plus two explicit output pointers. Pointer-to-const parameter provenance is different from a const cast at the load, and separate output parameters expose the read/store alias relation to the inliner. Unlike the previous begin-write helper, completion follows the length calculation and pending stays in the caller.

Source /tmp/sol-tiny-command-readonly-toc-and-explicit-output-aliases.c, object /tmp/sol-tiny-command-readonly-toc-and-explicit-output-aliases.o.

- CheckBS2CommandStatus: 9 differing, 406/406 instructions; size 1624/1624.
- BS2StartGame: 5 differing, 393/393 instructions; size 1572/1572.
- POOL IDENTICAL up to 91 (mine=91 base=91)

### led-output-parameter-switch-stores

The by-value condition/out-result helper folded the conditional into arithmetic. Keep conditional output memory stores but use switch lowering, whose constant stores survive early selection folding. Prediction: after inlining, the branch graph can keep successful fallthrough while promotion removes only memory operations. This is the output-only counterpart of the old both-pointer experiment.

Source /tmp/sol-tiny-led-output-parameter-switch-stores.c, object /tmp/sol-tiny-led-output-parameter-switch-stores.o.

- kbd_led_handler: 14 differing, 26/25 instructions; size 104/100.
- kbdProcMod: 4 differing, 256/256 instructions; size 1024/1024.
- KBDSetModState: 4 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### start-control-read-before-mask-construction

Trace of old-word union shows final OR result can share either input, and the higher-numbered surviving input gets r0. With two unions, old-word promotion was later than mask promotion and took r0. Read/update the actual control word before constructing the independent mask, so promoted old temp precedes promoted mask temp. Prediction: mask/result r0, old r3, address r4, with the scheduler restoring the same parallel instruction order.

Source /tmp/sol-tiny-start-control-read-before-mask-construction.c, object /tmp/sol-tiny-start-control-read-before-mask-construction.o.

- CheckBS2CommandStatus: 2 differing, 406/406 instructions; size 1624/1624.
- BS2StartGame: 0 differing, 393/393 instructions; size 1572/1572.
- POOL IDENTICAL up to 91 (mine=91 base=91)

### modifier-named-physical-extraction-before-insert

Extract the real physical six-bit state into a scalar using load then mask. A twice-assigned scalar survives forwarding as a named node, unlike the union old-word temp. The explicit mask is redundant at the later six-bit insertion and should disappear, leaving address as a higher-numbered temp than the old word. This is a phase-order test derived from the successful DI trace, not a declaration permutation.

Source /tmp/sol-tiny-modifier-named-physical-extraction-before-insert.c, object /tmp/sol-tiny-modifier-named-physical-extraction-before-insert.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 4 differing, 256/256 instructions; size 1024/1024.
- KBDSetModState: 4 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### modifier-physical-byte-promotion

Represent the six physical bits in an unsigned byte, consistent with HID modifier storage. Narrowing the loaded word may survive until late bitfield insertion and then disappear because only six bits are consumed. This tests typed promotion/coalescing rather than changing the masks or caller validation.

Source /tmp/sol-tiny-modifier-physical-byte-promotion.c, object /tmp/sol-tiny-modifier-physical-byte-promotion.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 4 differing, 256/256 instructions; size 1024/1024.
- KBDSetModState: 4 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### modifier-physical-byte-read-helper

A real const-channel physical-modifier accessor returns only the six HID bits as a byte. Earlier read helpers returned the full u32 word or a full union. The smaller typed return plus const parameter tests a different inline result/coalescing boundary while preserving the target full-word read and final low-bit insertion.

Source /tmp/sol-tiny-modifier-physical-byte-read-helper.c, object /tmp/sol-tiny-modifier-physical-byte-read-helper.o.

- kbd_led_handler: 3 differing, 25/25 instructions; size 100/100.
- kbdProcMod: 4 differing, 256/256 instructions; size 1024/1024.
- KBDSetModState: 7 differing, 42/42 instructions; size 168/168.
- POOL IDENTICAL up to 0 (mine=0 base=0)

### start-control-word-bit-position-names

Source review: the target proves three bit positions, but not the semantic names legacyReset/legacyControl/enabled. Name the actual bit positions explicitly instead of claiming undocumented hardware meanings. This only changes field names; retain the same typed raw register word, width and update order. Expected code identity with the exact candidate.

Source /tmp/sol-tiny-start-control-word-bit-position-names.c, object /tmp/sol-tiny-start-control-word-bit-position-names.o.

- CheckBS2CommandStatus: 2 differing, 406/406 instructions; size 1624/1624.
- BS2StartGame: 0 differing, 393/393 instructions; size 1572/1572.
- POOL IDENTICAL up to 91 (mine=91 base=91)

## Backend conclusions and retained result

### BS2StartGame: exact

Fresh `_mwdbg/runs/sol-tiny-start-exact` confirms the predicted promotion order. Initial B113 reads the actual control word into the diValue aggregate, updates bit 0, then constructs diBits and updates bit 2. Before allocation those stores/loads promote to address r194, old-word r197, mask r200 and final OR r203. The final result can share either input. Coloring gives mask/result r0, old word r3 and address r4. regsim reproduces 173/173 virtual registers and all 3/3 requested colors. Backend-02, 03 and 04 retain exactly the target seven-operation MMIO sequence. The tracer whole-object bytes equal the normal Ninja object.

The raw u32 and 32-bit bitfield overlay describe the same DI control register. Both locals have that representation; they do not group unrelated state. Reading/updating the word precedes constructing the independent mask. For every input word the result remains `(old | 1) | (2 | 4)`. No extra memory access, call, storage or instruction survives. Source review replaced speculative hardware meanings with bit-position names. That rename leaves the complete object identical. The retained diff touches only this block, adds no code comments, and does not alter configure.py.

Normal Ninja verification after source cleanup: 1572/1572 bytes, ctxdiff 393/393 instructions with diffs 0, and pool 91/91 identical. Exact-name objdiff is 100.0%. BS2Mach rises from 26/29 to 27/29 exact functions and code 6024/16980 to 7596/16980. Every other function score in this unit is unchanged. The unit still has two non-exact functions, so it remains NonMatching; this is a function match, not safe whole-unit linking.

### CheckBS2CommandStatus: unresolved

Fresh `_mwdbg/runs/sol-tiny-command-base` reproduces 126/126 GPR allocations. B44 already puts the count shift before the completion store before allocation; backend-02/03/04 preserve that order. This eliminates register coloring as the cause. The count load has PCode flags 0x100000000022, completion store 0x100000000004, and volatile length/pending operations 0x100000000082/84. These are operation flags, not captured scheduler dependency edges. The tracer does not prove a count-load/completion-store alias edge, so that remains an inference rather than a recovered target DAG.

Preserving both target count loads while exposing the first read before the completion store did not move the store. Const input/output provenance did not do so either. The restrict alias contract is unsupported by this compiler. The single-field completion wrapper was diagnostic only and is rejected by the no-carrier rule. Best remains the source baseline, 2/406 differing with equal size. No speculative completion-storage or qualifier change is retained.

### update_friendinfo: unresolved

The source-first argument preparation in retail is absent in the initial source PCode, not introduced by physical-register allocation. The two independent addi operations have the same ALU latency and no memory effects; both consume saved bases and feed the same call. The compiler emits destination first before scheduling. A real memset return edge removes the required destination addi instead of delaying it, producing unequal size. Moving memset into the source argument or a genuine clear/copy helper does not produce the required two-argument preparation order. Best remains 2/38 differing, equal size. The source file is unchanged.

### kbd_led_handler: unresolved

Fresh `_mwdbg/runs/sol-tiny-led-base` confirms initial B2 tests success==1 and branches to successful B5; B3 supplies error 7. The same CFG reaches backend-01/02/03/04, with the final callback call becoming a tail branch. The target reverses this fallthrough, so the difference is control dependence/block placement rather than register or memory latency. A by-value status/output-pointer converter folds to arithmetic and loses two required instructions. Switch output stores retain a spare dispatch branch and add one instruction. Predicate-switch lowering preserves extra predicate materialization. None has equal-size improvement. Best remains 3/25 differing; source unchanged.

### kbdProcMod and KBDSetModState: unresolved

Current validated captures reproduce both allocations. Their load-address/old-word values are unnamed temps with a real interference edge because the address must survive until the store. Source declaration permutations cannot change their priority. Real union field copies, parameter/return copies and byte physical-state promotion either forward to the same address/word temps or retain extra operations. Direct field updates reverse the bit insertion direction; the proc then loses three required instructions. Unlike the DI result, the attempted real six-bit extraction mask disappears before it can preserve a named old-word value. No tested normal data representation makes the store address a later surviving temp than the old word while preserving the required operations. Best stays 4/256 and 4/42 differing, equal sizes. Both source functions remain at baseline.

## Private artifacts and scope

Directed trials are in `/tmp/sol-tiny-*.c`, `.cpp`, `.o` and the measurement log above. Tracer output must live under its own `_mwdbg/runs` root; it is tool-generated evidence outside every source worktree. Reused historical captures were accepted only after matching current source and complete object hashes. No worker source edits, rebase, push, PR or merge occurred outside the assigned worktree.

Private best diffs are `/mnt/drive2/projects/wii-ipl-workers/_luna-runs/best/sol-tiny.BS2Mach.diff`, `sol-tiny.iplAddressEdit.diff` and `sol-tiny.kbd_lib.diff`. BS2Mach archives the retained exact function within the still-partial unit. AddressEdit and kbd_lib have empty diffs because their best non-exact version is unchanged baseline. CheckBS2CommandStatus likewise has no retained non-exact diff.

## Final validation

Requested command: `python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/BS2/BS2Mach src/scene/address/iplAddressEdit libs/RVL_SDK/src/kbd/kbd_lib --quick`. Exit 0, GATE PASS. Full 43U build passed; DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Pools identical in all three units; every owned data section remains 100%. Regression count 0, net forbidden-pattern count 0, readability warning count 0. Raw output is `/tmp/sol-tiny-gate.log`. The quick gate was used exactly as requested; it did not remove the existing build tree.

Live report regenerated with `ninja progress build/43U/report.json`. Comparing every current function score to the initial report finds exactly one change: BS2StartGame becomes 100.0%; all other scores are unchanged. Final exact functions are BS2Mach 27/29, AddressEdit 91/94, kbd_lib 18/21. Final ctxdiff measurements confirm CheckBS2CommandStatus 2/406, update_friendinfo 2/38, kbd_led_handler 3/25, kbdProcMod 4/256 and KBDSetModState 4/42, all equal size. BS2StartGame alone is newly exact at 0/393. Linking is unchanged because no assigned unit is fully exact.

Only `src/BS2/BS2Mach.c` and this attempts log are committed. Existing untracked rx4/rx59/rx70 files are preserved. No push, PR, merge or rebase.
