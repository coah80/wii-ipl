# ATERM matching attempts

Baseline: 3bfbb0c9. Target: Wii Menu 4.3U. All sizes are bytes.

Objdiff exact functions: 12/26 -> 15/26. Gate instruction-exact functions: 11/26 -> 14/26. Matched code: 6576/19204 -> 9296/19204. Matched data: 18504/18864 -> 18504/18864. Fuzzy code: 91.736305% -> 96.46365%.

Three functions reached exact matching. Eleven remain open; each has at least three distinct source attempts below. Failed and unchanged experiments were reverted. The remaining functions are not all registers-only.

| Function | Target bytes | Compiled bytes before -> after | Objdiff % before -> after | Final difference |
| --- | ---: | ---: | ---: | --- |
| ATERM_814021BC | 616 | 616 -> 616 | 96.61688 -> 97.91558 | Global address formation and load scheduling. |
| ATERM_8140276C | 696 | 696 -> 696 | 99.166664 -> 99.166664 | Register allocation only. |
| ATERM_81402A24 | 1052 | 1040 -> 1044 | 92.43346 -> 94.73384 | Two instructions short; scan loop and record addressing still differ. |
| ATERM_81402E40 | 384 | 384 -> 384 | 99.791664 -> 99.791664 | Two entry moves exchanged; CR1 branch differences in ctxdiff are an address-normalization artifact. |
| ATERM_814031DC | 532 | 516 -> 516 | 90.766914 -> 90.766914 | Four instructions short; formatting loops use branches rather than target CTR loops. |
| ATERM_814033F0 | 548 | 548 -> 548 | 99.56204 -> 99.56204 | Key cursor and zero constant swap r22/r23. |
| ATERM_814038C8 | 3804 | 3888 -> 3888 | 87.2755 -> 87.43323 | Twenty-one extra instructions; global base spills and local stack offsets differ. |
| ATERMi_AutoConfigThread | 160 | 160 -> 160 | 94.75 -> 94.75 | NOR destination register and global reload/shift scheduling. |
| ATERM_81404844 | 468 | 468 -> 468 | 99.0 -> 99.0 | Register allocation and block index/offset initialization order. |
| ATERM_81404BFC | 1072 | 1072 -> 1072 | 98.94403 -> 98.94403 | Initial byte-load/store scheduling and AES-128 table registers. |
| ATERM_8140502C | 552 | 552 -> 552 | 99.565216 -> 100.0 | Exact: 138 instructions, ctxdiff diffs 0. |
| ATERM_81405254 | 1084 | 1084 -> 1084 | 62.110703 -> 100.0 | Exact: 271 instructions, ctxdiff diffs 0. |
| ATERM_81405690 | 1084 | 1084 -> 1084 | 59.309963 -> 100.0 | Exact: 271 instructions, ctxdiff diffs 0. |
| ATERM_81405ACC | 576 | 556 -> 556 | 88.583336 -> 91.263885 | Five instructions short; byte-copy loops still use indexed rather than target pointer induction. |

Every retained function has the target stack-frame size. The main function still assigns different offsets to some locals.

## ATERM_814021BC

- use one network-settings aggregate pointer: 96.61688% (154/154 instructions, compiled/target).
- IP view scoped after clear: 96.61688% (154/154 instructions, compiled/target).
- host ID call before network zero conversion: 97.91558% (154/154 instructions, compiled/target).
- Retained result: Global address formation and load scheduling.

## ATERM_8140276C

- found/result/index before record pointer views: 98.56322% (174/174 instructions, compiled/target).
- initialize result before found: 98.965515% (174/174 instructions, compiled/target).
- signed traversal locals with original unsigned bounds: 99.166664% (174/174 instructions, compiled/target).
- Retained result: Register allocation only.

## ATERM_81402A24

- scan buffer alignment through wide unsigned address arithmetic: 93.78327% (261/263 instructions, compiled/target).
- retranslate descriptors with indexed record fields rather than interior cursor: 94.73384% (261/263 instructions, compiled/target).
- retranslate deadline comparison and counted MAC loop: 85.50571% (292/263 instructions, compiled/target).
- Retained result: Two instructions short; scan loop and record addressing still differ.

## ATERM_81402E40

- wire payload length unsigned int: 99.791664% (96/96 instructions, compiled/target).
- opaque payload formal with writable halfword view: 99.791664% (96/96 instructions, compiled/target).
- byte encryption key formal: 99.791664% (96/96 instructions, compiled/target).
- payload-header-typed-view: 99.583336% (96/96 instructions, compiled/target).
- Retained result: Two entry moves exchanged; CR1 branch differences in ctxdiff are an address-normalization artifact.

## ATERM_814031DC

- retranslate both MAC loops as six iterations with conditional separator: 53.969925% (191/133 instructions, compiled/target).
- MAC loops with final-iteration continue: 53.969925% (191/133 instructions, compiled/target).
- MAC loop bound from actual address field size: 53.969925% (191/133 instructions, compiled/target).
- mac-encoding-do-while-six-bytes: 90.22556% (131/133 instructions, compiled/target).
- mac-do-while-with-separate-index-increment: 90.22556% (131/133 instructions, compiled/target).
- mac-counted-loop-with-unsigned-bound-comparison: 53.969925% (191/133 instructions, compiled/target).
- Retained result: Four instructions short; formatting loops use branches rather than target CTR loops.

## ATERM_814033F0

- SSID-found flag initialized before cursor: 98.24818% (137/137 instructions, compiled/target).
- key pointer local to key options: 99.56204% (137/137 instructions, compiled/target).
- unsigned byte key view and unsigned found flag: 99.56204% (137/137 instructions, compiled/target).
- result-declared-before-key-with-explicit-init: 99.56204% (137/137 instructions, compiled/target).
- named-key-text-terminator-before-key: 99.56204% (137/137 instructions, compiled/target).
- indexed-source-byte-for-key-encoding: 95.985405% (139/137 instructions, compiled/target).
- Retained result: Key cursor and zero constant swap r22/r23.

## ATERM_814038C8

- block1 defer response and session pointer initialization after protocol state: 87.2755% (972/951 instructions, compiled/target).
- block1 direct global response and session key at each use: 86.11251% (974/951 instructions, compiled/target).
- block1 session key direct global while response stays typed local: 86.66246% (972/951 instructions, compiled/target).
- block1 packet buffer local view shared by send and receive paths: 84.303894% (979/951 instructions, compiled/target).
- retranslate MD5 count initialization and length encoding without snapshot array: 87.43323% (972/951 instructions, compiled/target).
- Retained result: Twenty-one extra instructions; global base spills and local stack offsets differ.

## ATERMi_AutoConfigThread

- signed equality intermediate and arithmetic: 94.75% (40/40 instructions, compiled/target).
- result reload before final state calculation: 91.45% (40/40 instructions, compiled/target).
- natural conditional completed state: 94.0% (40/40 instructions, compiled/target).
- completed state subtracts equality: 72.1% (39/40 instructions, compiled/target).
- state from nested signed expression: 94.75% (40/40 instructions, compiled/target).
- Retained result: NOR destination register and global reload/shift scheduling.

## ATERM_81404844

- signed AES round-count local: 99.0% (117/117 instructions, compiled/target).
- initialize wrapped-block index before byte offset: 98.97436% (117/117 instructions, compiled/target).
- destination byte view initialized with declarations: 98.74359% (117/117 instructions, compiled/target).
- wrapping-destination-index-derived-from-block-number: 95.44444% (116/117 instructions, compiled/target).
- wrapping-pass-base-computed-before-block-loop: 98.97436% (117/117 instructions, compiled/target).
- Retained result: Register allocation and block index/offset initialization order.

## ATERM_81404BFC

- initial key words as canonical big-endian XOR packing: 98.94403% (268/268 instructions, compiled/target).
- store each packed key word immediately: 98.01492% (268/268 instructions, compiled/target).
- initialize substitution view before round constants: 98.77612% (268/268 instructions, compiled/target).
- Retained result: Initial byte-load/store scheduling and AES-128 table registers.

## ATERM_8140502C

- canonical indexed round-key reversal: 99.565216% (138/138 instructions, compiled/target).
- reversal first index declared before last: 99.42029% (138/138 instructions, compiled/target).
- advance reversal indices after swaps: 99.565216% (138/138 instructions, compiled/target).
- canonical-indexed-reversal-with-shared-word: 100.0% (138/138 instructions, compiled/target).
- Retained result: Exact: 138 instructions, ctxdiff diffs 0.

## ATERM_81405254

- input word initialization in assembly scheduling order 1 2 0 3: 59.16236% (271/271 instructions, compiled/target).
- key xor precedes balanced big-endian packing and counter follows states: 53.553505% (271/271 instructions, compiled/target).
- full canonical AES input declarations then packing and direct round tables: 91.11808% (271/271 instructions, compiled/target).
- final AES round balanced low/high substitution pairs in target order: 91.11808% (271/271 instructions, compiled/target).
- final-interleaved-word-output: 100.0% (271/271 instructions, compiled/target).
- Retained result: Exact: 271 instructions, ctxdiff diffs 0.

## ATERM_81405690

- input word initialization in assembly scheduling order 1 2 0 3: 60.564575% (271/271 instructions, compiled/target).
- key xor precedes balanced big-endian packing and counter follows states: 55.583027% (271/271 instructions, compiled/target).
- full canonical AES input declarations then packing and direct round tables: 87.070114% (271/271 instructions, compiled/target).
- balanced inverse round and final substitution pairs in target order: 91.11808% (271/271 instructions, compiled/target).
- final-interleaved-word-output: 100.0% (271/271 instructions, compiled/target).
- Retained result: Exact: 271 instructions, ctxdiff diffs 0.

## ATERM_81405ACC

- retranslation copy blocks through destination/source byte pointers: 72.854164% (138/144 instructions, compiled/target).
- retranslation independent scoped byte copy views and lengths: 72.75% (138/144 instructions, compiled/target).
- retranslation incrementing copy pointers in each byte loop: 74.729164% (135/144 instructions, compiled/target).
- md5-byte-typed-input-formal: 88.583336% (139/144 instructions, compiled/target).
- md5-eight-byte-copy-blocks-followed-by-tail: objdiff score unavailable (267/144 instructions, compiled/target).
- md5-writable-input-formal: 91.263885% (139/144 instructions, compiled/target).
- md5-writable-input-and-scoped-copy-views: 74.6875% (138/144 instructions, compiled/target).
- md5-writable-copy-pointer-increments: 76.875% (135/144 instructions, compiled/target).
- md5-independent-copy-and-block-counters: 91.263885% (139/144 instructions, compiled/target).
- md5-copy-equality-bounds: 69.486115% (117/144 instructions, compiled/target).
- Retained result: Five instructions short; byte-copy loops still use indexed rather than target pointer induction.

## Exact translation evidence

- Encryption and decryption input packing and paired round bodies reached zero differences through instruction 198 before changing the final substitution block.
- Calculating and storing one final output word at a time made both AES functions instruction-exact.
- Indexed round-key reversal with one shared word temporary made ATERM_8140502C instruction-exact.

## Verification

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 9296/19204 data 18504/18864 functions 15/26 fuzzy 96.4637 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 14/26
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```

Full gate used a clean 43U build. Regression, forbidden-pattern and readability counts are zero. configure.py was unchanged; ATERM remains NonMatching.

## Open questions

- The remaining register-allocation choices and scheduling differences have no confirmed source-level fix.
- ATERM_81402FC0 is already 100% in objdiff. Correctly decoding the last branch operand confirms zero instruction differences; ctxdiff and the gate treat the CR1 operand as the destination address and undercount exact functions by one.
- The .data jump-table and .sbss scores remain below exact. No data placement changes were attempted.

## Source commits

- 04ea573a: host address polling order.
- 663b43b7: exact AES transforms, scan record indexing and MD5 length encoding.
- 7c0020a6: writable MD5 input formal to preserve byte-copy alias dependencies.
- e2a5fe66: exact inverse key reversal and source formatting.

## Continuation at 07b3a2b5

Baseline: instruction-exact 14/26, objdiff exact 15/26, code 9296/19204, data 18504/18864, fuzzy 96.46365%. Fresh quick gate passed. Remaining functions will receive new attempts in this round. Data audit first: .rodata tables match; .sdata matches including section tail alignment. .data contains three generated switch tables and MD5 padding. .sbss is 84 bytes versus 80; selected BSSID is used as a six-byte MAC address but declared eight bytes, imposing eight-byte alignment at offset 0x48 instead of target 0x44.

- Data attempt: declare selected BSSID with its actual six-byte MAC length. Compiled .sbss shrinks 84 -> 80 bytes, BSSID moves 0x48 -> 0x44, cancel flag moves 0x50 -> 0x4c, all matching target offsets. Quick gate passed with zero regressions; objdiff data score remains unchanged. Retained as a real layout correction.

- ATERM_81402A24 — round-two block alignment audit: 94.73384%; 261/263 instructions; frame ('stwu', 'r1, -0x90(r1)')/('stwu', 'r1, -0x90(r1)').

- ATERM_81402A24 — initialize scan iteration after allocation to match block 1 lifetime: 94.52471%; 261/263 instructions; frame ('stwu', 'r1, -0x90(r1)')/('stwu', 'r1, -0x90(r1)').

- ATERM_81402A24 — compare current time first as target scan block does: 94.79088%; 261/263 instructions; frame ('stwu', 'r1, -0x90(r1)')/('stwu', 'r1, -0x90(r1)').

- ATERM_81402A24 — translate positive scan edge and separate cleanup jump literally: 94.79088%; 261/263 instructions; frame ('stwu', 'r1, -0x90(r1)')/('stwu', 'r1, -0x90(r1)').

- ATERM_814031DC — bound MAC formatting by the input byte pointer rather than integer trip count: 91.53384%; 139/133 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

- ATERM_814031DC — pointer endpoint equality for six-byte MAC formatting: 91.53384%; 139/133 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

- ATERM_814031DC — count six bytes with equality instead of ordered loop bound: 53.969925%; 191/133 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

- ATERM_814031DC — execute guaranteed nonempty MAC pointer loop as do-while: 93.44361%; 133/133 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

Progress: MAC formatter now has 133/133 instructions, 93.44361% (from 129/133, 90.766914%). Pointer do-while loops preserve real six-byte bounds; branch control still differs from target CTR loops. Quick gate passed with zero regressions. Scan comparison improvement retained at 94.79088%. Next: initial global-base block of the protocol state machine.

- ATERM_814038C8 — initialize protocol state before all local addresses and scalar state: 87.43323%; 972/951 instructions; frame ('stwu', 'r1, -0x180(r1)')/('stwu', 'r1, -0x180(r1)').

- ATERM_814038C8 — use one typed configuration aggregate view for all members: 87.43323%; 972/951 instructions; frame ('stwu', 'r1, -0x180(r1)')/('stwu', 'r1, -0x180(r1)').

- ATERM_814038C8 — reverse alarm and message local declaration order to align the stack block: 87.432175%; 972/951 instructions; frame ('stwu', 'r1, -0x180(r1)')/('stwu', 'r1, -0x180(r1)').

- ATERM_81405ACC — name destination at partial block start before indexed byte copy: 83.34028%; 139/144 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERM_81405ACC — increment partial destination index independently of source index: 71.46528%; 152/144 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERM_81405ACC — translate copy blocks as while loops with explicit byte temporaries: 91.263885%; 139/144 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERM_81405ACC — inline ordinary digest byte-copy helper at both copy blocks: 35.618057%; 59/144 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERM_81402E40 — initialize checksum cursor before the payload call to alter formal lifetimes: 79.9375%; 88/96 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERM_81402E40 — initialize checksum immediately before its loop instead of entry: 94.572914%; 96/96 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERM_81402E40 — name the payload header separately from encrypted payload: 99.791664%; 96/96 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERM_814033F0 — initialize option result after decoding the response end: 97.66423%; 137/137 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

- ATERM_814033F0 — initialize decoded key view at entry to change zero and key lifetimes: 99.56204%; 137/137 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

- ATERM_814033F0 — scope the decoded key view to the wireless-key option block: 99.56204%; 137/137 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

- ATERM_8140276C — initialize record loop index at its loop and result before found flag: 99.05173%; 174/174 instructions; frame ('stwu', 'r1, -0x80(r1)')/('stwu', 'r1, -0x80(r1)').

- ATERM_8140276C — initialize previous record view before current record view: 98.93678%; 174/174 instructions; frame ('stwu', 'r1, -0x80(r1)')/('stwu', 'r1, -0x80(r1)').

- ATERM_8140276C — translate current-record iteration as a while loop with explicit index advance: 99.034485%; 174/174 instructions; frame ('stwu', 'r1, -0x80(r1)')/('stwu', 'r1, -0x80(r1)').

- ATERM_81404844 — initialize wrapping success before the integrity constants: 99.0%; 117/117 instructions; frame ('stwu', 'r1, -0x190(r1)')/('stwu', 'r1, -0x190(r1)').

- ATERM_81404844 — write integrity words in increasing array order: 98.9829%; 117/117 instructions; frame ('stwu', 'r1, -0x190(r1)')/('stwu', 'r1, -0x190(r1)').

- ATERM_81404844 — initialize block ordinal before output byte offset: 98.97436%; 117/117 instructions; frame ('stwu', 'r1, -0x190(r1)')/('stwu', 'r1, -0x190(r1)').

- ATERM_81404BFC — store each decoded key word before loading the next key word: 98.01492%; 268/268 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

- ATERM_81404BFC — initialize substitution table before round constants in key schedules: 98.77612%; 268/268 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

- ATERM_81404BFC — declare key words in input order and advance round counter as a statement: 98.73881%; 268/268 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

- ATERM_814021BC — set socket-start flag directly before initializing success result: 96.51948%; 154/154 instructions; frame ('stwu', 'r1, -0xd0(r1)')/('stwu', 'r1, -0xd0(r1)').

- ATERM_814021BC — initialize interface configuration view before clearing it: 97.16883%; 154/154 instructions; frame ('stwu', 'r1, -0xd0(r1)')/('stwu', 'r1, -0xd0(r1)').

- ATERM_814021BC — advance interface polling counter at the for-loop edge: 96.61688%; 154/154 instructions; frame ('stwu', 'r1, -0xd0(r1)')/('stwu', 'r1, -0xd0(r1)').

- ATERMi_AutoConfigThread — reuse the completed thread result for its equality mask: 94.75%; 40/40 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERMi_AutoConfigThread — compute completed state before storing the deadline sentinel: 94.75%; 40/40 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERMi_AutoConfigThread — express the completion equality mask as a conditional: 84.475%; 42/40 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

Progress: every remaining ATERM function received at least three new source-level attempts. Retained scan deadline, six-byte BSSID layout and MAC loop improvements; all other trials reverted after measurement. Remaining count mismatches: scan 261/263, protocol 972/951 and MD5 update 139/144. Seven near matches have register or scheduling differences with equal counts. Next: AOSS baseline and its two lowest-scoring functions.

- ATERMi_AutoConfigThread — read reported result before deriving the completed state: 91.45%; 40/40 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

- ATERM_81405ACC — give both digest copy blocks their own source and destination array views: 74.93056%; 138/144 instructions; frame ('stwu', 'r1, -0x20(r1)')/('stwu', 'r1, -0x20(r1)').

Data audit: .bss: source/target sizes 8144/8160, alignments 8/32, raw section bytes differ. .rodata: source/target sizes 10280/10280, alignments 8/8, raw section bytes identical. .data: source/target sizes 280/280, alignments 8/8, raw section bytes identical. .sdata2: source/target sizes 7/8, alignments 8/8, raw section bytes differ. .sdata: source/target sizes 53/56, alignments 8/8, raw section bytes differ. .sbss: source/target sizes 80/80, alignments 8/8, raw section bytes identical.
ATERM .data generated switch-table addends remain dependent on nonmatching control-flow offsets. BSSID layout is corrected; raw .sbss extent matches but its symbol matching score remains 38.88889%. No manual tables, address labels or data padding added.

- ATERM_814021BC — declare network configuration with the target BSS alignment: 94.08442%; 153/154 instructions; frame ('stwu', 'r1, -0xd0(r1)')/('stwu', 'r1, -0xd0(r1)').

## Round-two final inventory

| Function | Target bytes | Compiled bytes before -> after | Objdiff % before -> after | Remaining difference |
| --- | ---: | ---: | ---: | --- |
| ATERM_814021BC | 616 | 616 -> 616 | 97.91558 -> 97.91558 | Global address formation and instruction scheduling. |
| ATERM_8140276C | 696 | 696 -> 696 | 99.166664 -> 99.166664 | Registers only. |
| ATERM_81402A24 | 1052 | 1044 -> 1044 | 94.73384 -> 94.79088 | Two instructions short; scan branch and address formation. |
| ATERM_81402E40 | 384 | 384 -> 384 | 99.791664 -> 99.791664 | Two entry moves exchanged. |
| ATERM_814031DC | 532 | 516 -> 532 | 90.766914 -> 93.44361 | Pointer loop branches versus target CTR; registers and scheduling. |
| ATERM_814033F0 | 548 | 548 -> 548 | 99.56204 -> 99.56204 | Key cursor and zero register swap. |
| ATERM_814038C8 | 3804 | 3888 -> 3888 | 87.43323 -> 87.43323 | Twenty-one extra instructions; global base spills and stack offsets. |
| ATERMi_AutoConfigThread | 160 | 160 -> 160 | 94.75 -> 94.75 | NOR destination and reload/shift scheduling. |
| ATERM_81404844 | 468 | 468 -> 468 | 99.0 -> 99.0 | Registers and block-counter initialization order. |
| ATERM_81404BFC | 1072 | 1072 -> 1072 | 98.94403 -> 98.94403 | Key-load scheduling and AES table registers. |
| ATERM_81405ACC | 576 | 556 -> 556 | 91.263885 -> 91.263885 | Five instructions short; byte-copy pointer induction. |

Instruction-exact 14/26 -> 14/26; objdiff exact 15/26 -> 15/26. Matched code 9296 -> 9296 of 19204 bytes; matched data 18504 -> 18504 of 18864 bytes. Fuzzy 96.46365 -> 96.54093%. No new instruction-exact function this round; this is partial progress, not unit completion.

The first-BSS-object alignment trial changed code generation (97.91558 -> 94.08442%) and was reverted. Whole-section .bss and small-data tail alignment is already accepted by objdiff at 100%; no padding added. Earlier raw-byte audit compares unrounded ELF section lengths; differing trailing zero extents do not imply new logical data objects.

Full final gate:

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/ATERM] pool: IDENTICAL
[src/scene/setting/ATERM] objdiff: code 9296/19204 data 18504/18864 functions 15/26 fuzzy 96.5409 linked code 0
[src/scene/setting/ATERM] instruction-exact functions: 14/26
[src/scene/setting/ATERM]   section .bss size 8160 match 100.0
[src/scene/setting/ATERM]   section .data size 280 match None
[src/scene/setting/ATERM]   section .rodata size 10280 match 100.0
[src/scene/setting/ATERM]   section .sbss size 80 match 38.88889
[src/scene/setting/ATERM]   section .sdata size 56 match 100.0
[src/scene/setting/ATERM]   section .sdata2 size 8 match 100.0
[src/scene/setting/ATERM]   section .text size 19204 match 96.54093
[src/scene/setting/ATERM]   below 100: ATERM_814021BC 97.91558
[src/scene/setting/ATERM]   below 100: ATERM_8140276C 99.166664
[src/scene/setting/ATERM]   below 100: ATERM_81402A24 94.79088
[src/scene/setting/ATERM]   below 100: ATERM_81402E40 99.791664
[src/scene/setting/ATERM]   below 100: ATERM_814031DC 93.44361
[src/scene/setting/ATERM]   below 100: ATERM_814033F0 99.56204
[src/scene/setting/ATERM]   below 100: ATERM_814038C8 87.43323
[src/scene/setting/ATERM]   below 100: ATERMi_AutoConfigThread 94.75
[src/scene/setting/ATERM]   below 100: ATERM_81404844 99.0
[src/scene/setting/ATERM]   below 100: ATERM_81404BFC 98.94403
[src/scene/setting/ATERM]   below 100: ATERM_81405ACC 91.263885
[src/scene/setting/ATERM] baseline: code 9296/19204 data 18504 functions 15 fuzzy 96.4637
regressions vs baseline: 0
global matched_code_percent: 86.26884 -> 86.26884
global fuzzy_match_percent: 98.87921 -> 98.88315
global complete_code_percent: 60.34391 -> 60.34391
global matched_data_percent: 90.91213 -> 90.91213
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
