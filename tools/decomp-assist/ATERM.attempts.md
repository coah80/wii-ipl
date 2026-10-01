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
