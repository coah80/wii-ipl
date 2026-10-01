# zi8cgetc attempts

43U only. Starting source absent: 0/8 instruction-exact, 0/47816 objdiff code bytes, 0/536 data bytes. No shared headers or configuration changes.

The assembly is the authority. The first four functions were recovered in address order. The string pools contain no strings on either side.

- Zi8SetFindCand: signed integer remainder/division of the masked ordinal, as in the sibling unit. 50/50 instructions, diffs 0.
- ZiGetNextPhonetic: preserve repeated character reads and boundary-check order. 31/31 instructions, diffs 0.
- ZiPartialMatch: preserve the initial empty-range test, loop separator tests, and the repeated empty-range test after advancing both pointers. 51/51 instructions, diffs 0.

## ZiMatchZHSpelling

1. Two 64-character buffers, integer match/index, byte character count. 121/121 instructions, 29 register-choice differences, objdiff 98.80165%.
2. Declare the character count first and assign it after initializing the result. Same 121/121 and 29 differences.
3. Correct Zi8WCharCount's declaration to its actual 32-bit return, use an integer character count. Same 121/121 and 29 differences.
4. Move match/count/index declarations before cursors and buffers. Same 121/121 and 29 differences.

Differences are the candidate/spelling/work/count/result register assignments. Branches, buffer offsets and instruction counts agree. No forced stack/register storage.

## Zi8NewMatchPhonetic

Read the assembly in address order: argument/limit initialization, table selection, grouped-candidate loop, phonetic-offset loop, result exits. Recovered each block separately in /tmp before assembling the complete C function. The source uses a local work layout and a 12-byte record structure. No shared ABI changes.

1. Complete block reconstruction: 755/755 instructions, 198 differences. Most differences were reversed local stack order.
2. Reverse local declarations to restore stack slot order: 755/755, nine differences. Candidate-index/pointer increments were reversed and three byte swaps used arithmetic shifts.
3. Move the counter increment into the loop body and cast shifted values to byte: 759/755; register allocation changed throughout. Rejected.
4. Comma-expression increment in the for header and unsigned shift: 756/755, extra pointer temporary and shifted stack slots. Rejected.
5. While loop with index increment before pointer increment, and masked high-byte shifts: 755/755 instructions, diffs 0.

## Zi8GetElementCount

1. Literal assembly reconstruction: 114/115 instructions. Saved separator retained in a register rather than its original stack slot; three separate zero assignments and an early continue also differed.
2. Chained index/count initialization, common spaced-index update, and a 32-bit saved separator: 114/115. Control flow corrected; saved separator and associated buffer/register locations still differed.
3. Reverse index declarations and chain initialization in the original assignment order: 113/115. Remaining differences are separator storage and dependent register/frame allocation.
4. Const halfword separator: 115/115, 19 differences. It still remains in a register, with an extra conversion instead of the target stack store/load.
5. Signed separator: 115/115, 20 differences, including wrong signed load. Rejected. Kept the unsigned separator and literal common loop exit.

## Zi8GetChineseCandidates

1. Switch reconstruction with direct returns: 180/155 instructions. Repeated early calls, larger frame and separate length/result registers.
2. Shared early call exit and reverse local declarations: 150/155. Call exit was at the wrong end of the function; saved options registers were reversed.
3. Put the shared call immediately after the initial conditional and reuse length for the internal result: 155/155, six saved-options register differences.
4. Declare savedCountOnly before savedMaxResults: 155/155 instructions, diffs 0.
5. Widen savedCountOnly to int: 156/155, redundant byte conversion. Rejected.

Added the two ordinary four-character tone/punctuation tables and the zero-initialized tone table from the assembly. Jump tables are not manually reproduced.

## Follow-up attempts, 2026-09-30

ZiMatchZHSpelling: reversing the complete local declaration order and using a typed work pointer did not improve the 121/121 instruction, 29-register-difference result. Restored the accepted declaration order.

Zi8GetElementCount: moving the separator declaration before the buffer and splitting its initialization did not improve the 113/115 instruction result. Restored the accepted source. The original stores the separator on the stack; the ordinary scalar remains in a saved register. No spill-forcing declaration was introduced.

## zi8InternalGetZH: initial-block research only

The 10676-instruction internal engine remains absent. The following are three compiled alternatives for its initial basic blocks, not three completed reconstructions. Each research variant is under /tmp and is not part of the source change.

Recovered the initial mode normalization and non-phrase input validation, charset setup, match preparation and output copying from the assembly in address order. The original first clears a 494-byte ZiMatchParam with 61 paired word stores plus the final word and halfword. Tested that layout with the actual 43U compiler:

1. Aggregate zero initializer: 245 instructions in the isolated prefix. Emits the original 61-iteration paired-word clear, but its frame and registers differ because the remaining engine is absent.
2. Zi8Memset over the same structure: 240 prefix instructions. Produces a call rather than the target inline clear. Rejected.
3. Explicit byte loop: 244 prefix instructions. Bytewise clearing differs from the original word loop. Rejected.

No incomplete public function or placeholder body was added. The phrase paths and subsequent dictionary/candidate loops are not reconstructed. These prefix experiments do not satisfy full-unit completion or establish a compiler plateau for the complete engine.

## Engine continuation on 038cd6f9

Zi8GetElementCount, 460 target bytes: re-read all basic blocks in address order. Represented the separator backup as a saved work-state value with its actual separator field. This carries real state used after Zi8ZHaddSpace, with no unused fields or padding. It restores the target stack store/load and buffer offset. 115/115 instructions; thirteen remaining differences are solely the element-count/result register interchange. Scalar width, initialization placement, declaration order and scope variants did not improve those register choices. Quick full gate passes with zero regressions and 99.347824%, up from 97.48695%.

ZiMatchZHSpelling, 484 target bytes: all blocks are already translated, with 121/121 instructions. Re-read the complete assembly; all 29 remaining differences are register numbers. No control-flow or stack-offset mismatch remains.

## End-to-end engine reconstruction, round 2

- `zi8InternalGetZH`: wrote initialization, input/masks, fuzzy phonetics, dictionary preflight, OEM, PUD, context phrases, prediction/numeric tables, dictionary ranges, ordinal candidates, tones, user characters, global characters, component phrases, frequency merge, phonetic pairs/candidates, retry/finish, and filtered table search in successive source fragments. Object builds and ctxdiff snapshots 01 through 15 are in `/tmp/zi8-r2-engine-*.diff`; the final fragment resolves every control-flow label and includes the return and all retry paths. Temporary exits used during development are absent from the resulting source.
- The full body has 10,599 instructions against 10,676 target instructions; initialization still differs in stack layout, register allocation, and some later branch structure. It is an end-to-end reconstruction, not an exact match.
- The first full-body quick gate scored 75.59901% for the engine but failed because an extern declaration of the existing zero tone table changed its storage. Mutable storage was also incorrect. Moving the existing const tentative definition before its first use restored `.sbss2`, 24 matched data bytes, and zero regressions; engine score 75.60229%, unit fuzzy 78.19224%. Pool identical, forbidden additions 0, readability warnings 0, DOL hash correct, GATE PASS.
- Engine attempt 16: replaced conditional expressions for phrase length and final fallback eligibility with explicit logical branches. MWCC had allocated eight extra word temporaries for those expressions. Frame shrank from 0x500 to the target 0x4e0, instruction count 10,558/10,676, engine fuzzy 76.41532%; quick gate PASS, 0 regressions.
- Engine attempt 17: reordered the Boolean declarations to follow target stack slots; expressed phonetic pair rejection directly and initialized the pair-validation flag with branches. Aggregate and buffer offsets now align, frame remains 0x4e0, 10,535/10,676 instructions, engine fuzzy 76.57915%; quick gate PASS, 0 regressions.
- Engine attempt 18: sharing candidate status across matching/duplicate phases and correcting mask/range declaration order scored 76.535965%; this alone was below attempt 17. ASM review identified the missing independent phonetic-group wildcard byte at slot 0x48.
- Engine attempt 19: restored that real wildcard variable, separated it from candidate phonetic status, corrected byte truncation of secondary-match results, used the work-state halfword ordinal limit, and corrected OEM word-count increments. Engine 76.78999%; quick gate PASS, 0 regressions.
- Engine attempt 20: combined six phonetic-code assignments with their comparisons; engine score fell to 76.70392%, so restored attempt 19.
- Final read-only coverage check: every non-prologue helper has the same number of call sites as the target engine, including all 20 table-address calls, 22 table-count calls, 19 word-duplicate calls, and 11 secondary-character calls. All labels resolve, and no temporary completion exits remain. The initialization region after the save sequence has target stack offsets and instruction forms; the save sequence and GPR choices still differ.
- Final clean full gate: PASS; 5/8 instruction-exact functions, code 4168/47816, data 24/536, fuzzy 79.2530%. Pool identical, zero baseline regressions, zero forbidden patterns and readability warnings. Full build passed with target DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.

## First-divergence matching, round 3 on ad3da3bb

Baseline: engine 76.78999%, frame 0x4e0, 10,566/10,676 instructions. Exact first divergence is +0x000c, the individual register saves versus the target _savegpr_27 call. All initialization stack offsets agree; after aligning past the save sequence and ignoring GPR numbers and branch spans, the first instruction-form difference is +0x05e4, table 27 count assignment.

- Attempt 01: moved the two charset zero initializations into their declarations. Instruction stream and 76.78999% score unchanged; first divergence +0x000c. Rejected.
- Attempt 02: explicitly converted the table 27 count to its halfword destination type. Engine 76.90586%, 10,563/10,676 instructions; first divergence +0x000c. First body form difference remains +0x05e4. Quick gate PASS, zero regressions. Kept for its measured score gain.
- Attempt 03: changed the explicit conversion to unsigned int. Same 76.90586% stream and first divergence +0x000c; restored attempt 02.
- Attempt 04: gave the table-range index a field in a range-state aggregate. Match buffer moved eight bytes, body form divergence moved earlier to +0x0020, engine 76.59067%; rejected. Exact first divergence stayed +0x000c.
- Attempt 05: corrected the prepare-match return declaration to ziBool as in zprepare.c. Stream and 76.90586% unchanged, first divergence +0x000c; restored.
- Attempt 06: combined the table-count assignment with its following condition. Engine 76.72677%, first divergence +0x000c; rejected.
- Attempt 07: tried unsigned result-count storage; compiler rejected its address at the signed result-count helper parameter. No measurement from that failed build is used. Restored the signed count.
- Attempt 08: used zaddress.c's word return declaration for table addresses, with correctly typed pointer conversions. Stream and 76.90586% unchanged, first divergence +0x000c; restored.
- Attempt 09: tried a word-return table-count declaration. Extra halfword conversions regressed the already-exact phonetic helper, engine 76.524635%, first divergence +0x000c; rejected.
- Attempt 10: reconstructed the full six-term packed masks in target expression order and masked the extracted bytes. Engine 76.83871%, first divergence +0x000c; retained only as a scratch precursor to attempt 11.
- Attempt 11: completed that prefix block with shared clear/fill assignments, target store order, the two missing fourth-byte writes, and target bound/branch forms. Engine 77.37008%, frame 0x4e0, 10,568/10,676 instructions; first divergence +0x000c. Four individual register saves now differ from the target five-register helper. Quick gate PASS, zero regressions.
- Attempt 12: used the library signed-word typedef for the phase counter. Same 77.37008% stream, first divergence +0x000c; rejected.
- Attempt 13: converted the complete packed-mask expressions to unsigned word values. Same 77.37008% stream, first divergence +0x000c; rejected.
- Attempt 14: restored fuzzy-phonetic case emission order and corrected the PY final-code flags from the target bit extractions: code 0x60 tests enANDeng and code 0x180 tests inANDing. Engine 77.52538%, 10,568/10,676 instructions, first divergence +0x000c; quick gate PASS, zero regressions.
- Attempt 15: used signed-word result storage and the corresponding helper output parameter type. Same 77.52538% stream and first divergence +0x000c; rejected.
- Attempt 16: removed the earlier explicit table-count conversion after the mask reconstruction. Engine fell to 77.498505%, first divergence +0x000c; restored.
- Attempt 17: used an unsigned-word engine return type for the nonnegative count. Engine stream and 77.52538% score unchanged, first divergence +0x000c; wrapper stayed instruction-exact. Restored the accepted declaration.

### Zi8GetElementCount, round 3

1. Put count before the two cursor declarations. Same 115/115 instructions, thirteen GPR differences, 99.347824%. Rejected.
2. Widen count to int. Ctxdiff still showed thirteen GPR differences; objdiff reported 98.391304%, so restored the byte count.
3. Use explicit count = count + 1 assignments. 117/115 instructions, redundant byte conversions, 97.608696%. Rejected.

Remaining accepted difference: elementCount uses r27 instead of r28; count uses r28 instead of r27. All thirteen differing instructions are those two GPR names.

### ZiMatchZHSpelling, round 3

1. Store the Boolean result in ziBool. 122/121 instructions, extra byte conversion, 97.06612%. Rejected.
2. Initialize matches and the read-only candidate length in their declarations. Same 121/121 instructions, 29 GPR differences, 98.80165%. Rejected.
3. Pass the typed ZI_WORK view to the helpers. Same 121/121 instructions, 29 GPR differences, 98.80165%. Rejected.

Remaining accepted differences: candidate, spelling, input length, work, candidate length and Boolean result GPR assignments. Branches, stack offsets and instruction counts agree.

No exact functions were added in this round. The engine's frame and local offsets are correct, but the first exact divergence remains +0x000c. Its four individual saves differ from the target _savegpr_27 sequence, and later expression/control-flow differences remain. All rejected source variants were restored.

Final clean full gate: PASS; pool identical, zero baseline regressions, zero forbidden-pattern additions and readability warnings. Full build passed with target DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. Unit 5/8 exact, code 4168/47816, data 24/536, fuzzy 79.9097%. Engine 76.78999% to 77.52538%, first divergence +0x000c to +0x000c; element count 99.347824% and spelling 98.80165% unchanged.

## Block-map round, 2026-10-01

Baseline engine: 10,598/10,676 instructions, deficit 78, fuzzy 78.05442%. Unit: 5/8 instruction-exact, code 4,168/47,816, data 72/536. Stack frame 0x4e0 and save sequence agree. Empty string pools agree. The target assembly was checked against the target object's full instruction count.

Full block maps and re-alignment artifacts are in `/tmp/sol-med-zi8-blocks/`. Both direct instruction and call-anchored alignments are recorded. Reordered calls produce apparent insertions paired with deletions; these are moved regions, not missing code. Register names and branch distances are excluded from structural alignment; stack offsets, calls, and literal/constant references remain.
- b01-mode-switch: R1 +1ae8: restore mode switch, pinyin before zhuyin, and explicit format >= 1 tests. Deficit 78 -> 77; engine fuzzy 78.05442% -> 78.32240%; kept.
- b02-bitmap-division: R1 +1ad4: use signed division by eight for scratch bitmap length. Deficit 77 -> 76; engine fuzzy 78.32240% -> 78.38188%; kept.
- b03-punctuation-postincrement: R2 +1eec/+1f00: emit punctuation with separate word/character postincrement paths. Deficit 76 -> 73; engine fuzzy 78.38188% -> 78.46590%; kept.
- b04-oem-duplicate-branches: R3 +287c: check bitmap/character/word duplicates in their own branches. Deficit 73 -> 67; engine fuzzy 78.46590% -> 78.58823%; kept.
- b05-oem-postincrement: R3 +2a6c/+2ae8: copy OEM word and character outputs with postincrements. Deficit 67 -> 72; engine fuzzy 78.58823% -> 78.76677%; rejected and restored.
- b06-pud-tone-status: R4 +2ee0: restore successful tone spelling status before bypassing ordinal checks. Deficit 67 -> 68; engine fuzzy 78.58823% -> 78.64771%; rejected and restored.
- b07-pud-duplicate-branches: R4 +367c: branch immediately after each PUD duplicate check. Deficit 67 -> 62; engine fuzzy 78.58823% -> 78.61596%; rejected and restored.
- b08-pud-mode-switch: R4 +329c: emit PUD fixed/wildcard/component/phonetic match cases in target order. Deficit 67 -> 62; engine fuzzy 78.58823% -> 79.62711%; rejected and restored.
- b09-pud-switch-punctuation-scan: R4/R2: combine target PUD switch with explicit punctuation duplicate loop. Deficit 67 -> 62; engine fuzzy 78.58823% -> 79.61090%; rejected and restored.
- b10-oem-character-postincrement: R3 +2ae8: keep OEM word branch order and postincrement character output count. Deficit 67 -> 71; engine fuzzy 78.58823% -> 78.62570%; rejected and restored.
- b11-oem-word-postincrement: R3 +2a6c: postincrement word-output index during OEM copy. Deficit 67 -> 67; engine fuzzy 78.58823% -> 78.49897%; rejected and restored.
- b12-context-duplicates: R5 +4580: context phrase duplicate decisions. Deficit 67 -> 64; engine fuzzy 78.58823% -> 78.71441%; kept.
- b13-dictionary-duplicates: R6 +518c: dictionary candidate duplicate decisions. Deficit 64 -> 66; engine fuzzy 78.71441% -> 78.61812%; rejected and restored.
- b14-range-duplicates: R7 +5860: character range duplicate decisions. Deficit 64 -> 62; engine fuzzy 78.71441% -> 78.55236%; rejected and restored.
- b15-ordinal-duplicates: R8 +5b60: component ordinal duplicate decisions. Deficit 64 -> 62; engine fuzzy 78.71441% -> 78.53213%; rejected and restored.
- b16-phonetic-ordinal-duplicates: R8 +6058: phonetic ordinal duplicate decisions. Deficit 64 -> 62; engine fuzzy 78.71441% -> 78.57109%; rejected and restored.
- b17-user-duplicates: R9 +6eb8: user character duplicate decisions. Deficit 64 -> 64; engine fuzzy 78.71441% -> 78.43996%; rejected and restored.
- b18-global-duplicates: R10 +73c0: global character duplicate decisions. Deficit 64 -> 61; engine fuzzy 78.71441% -> 78.53035%; rejected and restored.
- b19-phonetic-duplicates: R13 +84ec: phonetic phrase duplicate decisions. Deficit 64 -> 62; engine fuzzy 78.71441% -> 78.57680%; rejected and restored.
- b20-prediction-postcount: R6 +49a0: restore postincrement character emission in prediction. Deficit 64 -> 62; engine fuzzy 78.71441% -> 78.59377%; rejected and restored.
- b21-ordinal-postcount: R8 +5c30: restore postincrement character emission in ordinal. Deficit 64 -> 64; engine fuzzy 78.71441% -> 78.73923%; rejected and restored.
- b22-phonetic-ordinal-postcount: R8 +60b0: restore postincrement character emission in phonetic-ordinal. Deficit 64 -> 64; engine fuzzy 78.71441% -> 78.72611%; rejected and restored.
- b23-tone-postcount: R9 +6340: restore postincrement character emission in tone. Deficit 64 -> 64; engine fuzzy 78.71441% -> 78.72377%; rejected and restored.
- b24-alternate-tone-postcount: R9 +653c: restore postincrement character emission in alternate-tone. Deficit 64 -> 70; engine fuzzy 78.71441% -> 78.59545%; rejected and restored.
- b25-user-postcount: R9 +6f14: restore postincrement character emission in user. Deficit 64 -> 66; engine fuzzy 78.71441% -> 78.59414%; rejected and restored.
- b26-global-postcount: R10 +741c: restore postincrement character emission in global. Deficit 64 -> 63; engine fuzzy 78.71441% -> 78.75525%; kept.
- b27-frequency-character-postcount: R12 +81c4: restore postincrement character emission in frequency-character. Deficit 63 -> 61; engine fuzzy 78.75525% -> 78.45279%; rejected and restored.
- b28-frequency-component-postcount: R12 +8260: restore postincrement character emission in frequency-component. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.60641%; rejected and restored.
- b29-dictionary-postindex: R6/R7: restore both sequential postincrement word output writes in dictionary. Deficit 63 -> 65; engine fuzzy 78.75525% -> 78.71881%; rejected and restored.
- b30-range-postindex: R6/R7: restore both sequential postincrement word output writes in range. Deficit 63 -> 62; engine fuzzy 78.75525% -> 78.72143%; rejected and restored.
- b31-oem-inline-code: R3/R4/R5/R9: compare the phonetic helper result directly in oem. Deficit 63 -> 65; engine fuzzy 78.75525% -> 78.67928%; rejected and restored.
- b32-pud-inline-code: R3/R4/R5/R9: compare the phonetic helper result directly in pud. Deficit 63 -> 65; engine fuzzy 78.75525% -> 78.71403%; rejected and restored.
- b33-context-inline-code: R3/R4/R5/R9: compare the phonetic helper result directly in context. Deficit 63 -> 64; engine fuzzy 78.75525% -> 78.67731%; rejected and restored.
- b34-user-inline-code: R3/R4/R5/R9: compare the phonetic helper result directly in user. Deficit 63 -> 64; engine fuzzy 78.75525% -> 78.73117%; rejected and restored.
- b35-oem-segment-index: R3/R4/R5/R11: address segment subfields before applying row stride in oem. Deficit 63 -> 66; engine fuzzy 78.75525% -> 78.61858%; rejected and restored.
- b36-pud-segment-index: R3/R4/R5/R11: address segment subfields before applying row stride in pud. Deficit 63 -> 71; engine fuzzy 78.75525% -> 78.53775%; rejected and restored.
- b37-context-segment-index: R3/R4/R5/R11: address segment subfields before applying row stride in context. Deficit 63 -> 65; engine fuzzy 78.75525% -> 78.67535%; rejected and restored.
- b38-component-segment-index: R3/R4/R5/R11: address segment subfields before applying row stride in component. Deficit 63 -> 71; engine fuzzy 78.75525% -> 78.51958%; rejected and restored.
- b39-context-phrase-expression: R5/R6/R10: group phrase offset low bytes before OR with high nibble in context. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.70129%; rejected and restored.
- b40-dictionary-phrase-expression: R5/R6/R10: group phrase offset low bytes before OR with high nibble in dictionary. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.72621%; rejected and restored.
- b41-global-phrase-expression: R5/R6/R10: group phrase offset low bytes before OR with high nibble in global. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.73876%; rejected and restored.
- b42-initial-mode-switch: R0: express initial mode normalization as a switch. Deficit 63 -> 69; engine fuzzy 78.75525% -> 78.24532%; rejected and restored.
- b43-phrase-length-branches: R0: place nonzero match length branch after the zero-length fallback. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.72611%; rejected and restored.
- b44-fuzzy-phonetic-while: R0: express fuzzy phonetic masking as an explicit index loop. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.75525%; rejected and restored.
- b45-context-count-block: R1: separate context format/table-count setup from its conditional assignment. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.76546%; rejected and restored.
- b46-punctuation-loop-break: R2: separate duplicate equality exit from the punctuation scan bound. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.68452%; rejected and restored.
- b47-range-seen-loop: R7: separate output-character equality exit from the range scan bound. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.63507%; rejected and restored.
- b48-component-phrase-offset: R11: group low phrase-offset bytes before combining the high nibble. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.73773%; rejected and restored.
- b49-component-length-check: R11: separate insufficient phrase length from mismatching exact/prefix lengths. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.75525%; rejected and restored.
- b50-frequency-duplicate-order: R12: emit bitmap duplicate branch before character-buffer branch. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.65053%; rejected and restored.
- b51-pair-input-branch-order: R13: emit consonant phonetic input before vowel-special input. Deficit 63 -> 63; engine fuzzy 78.75525% -> 78.67244%; rejected and restored.
- b52-pair-extracted-bytes: R13: use explicit byte conversions for masked phonetic code extraction. Deficit 63 -> 62; engine fuzzy 78.75525% -> 78.74438%; rejected and restored.
- b53-pair-loop-strides: R13: advance phonetic pair cursor with the loop index. Deficit 63 -> 62; engine fuzzy 78.75525% -> 78.57971%; rejected and restored.
- b54-phonetic-loop-call: R14: separate phonetic-match failure from outer candidate bounds. Deficit 63 -> 63; engine fuzzy 78.75525% -> 79.19295%; rejected and restored.
- b55-phonetic-group-word-count: R14: increment word length before counting its appended character. Deficit 63 -> 62; engine fuzzy 78.75525% -> 78.76161%; kept.
- b56-finish-capacity-selection: R15: select count-only or emitted-candidate retry capacity explicitly. Deficit 62 -> 49; engine fuzzy 78.76161% -> 78.36839%; rejected and restored.
- b57-finish-terminator-index: R15: separate output terminator store from cursor increment. Deficit 62 -> 62; engine fuzzy 78.76161% -> 78.77238%; rejected and restored.
- b58-finish-final-code-index: R15: address final phonetic code by subtracting one element before indexing. Deficit 62 -> 69; engine fuzzy 78.76161% -> 78.70223%; rejected and restored.
- b59-filtered-duplicate-branches: R16: branch after each filtered character duplicate check. Deficit 62 -> 62; engine fuzzy 78.76161% -> 78.59835%; rejected and restored.
- b60-filtered-ordinal-expression: R16: combine ordinal bytes before multiplying the dictionary record stride. Deficit 62 -> 58; engine fuzzy 78.76161% -> 78.75215%; rejected and restored.
- b61-filtered-segment-addressing: R16: address segment subfields before row stride in filtered matching. Deficit 62 -> 59; engine fuzzy 78.76161% -> 78.26311%; rejected and restored.
- s01 Zi8GetElementCount: initialize output count to input length for early returns. Objdiff 99.34782% -> 97.78261%; rejected and restored.
- s02 Zi8GetElementCount: use a halfword output counter before returning its byte value. Objdiff 99.34782% -> 98.391304%; rejected and restored.
- s03 Zi8GetElementCount: initialize scan indices and count in separate statements. Objdiff 99.34782% -> 98.347824%; rejected and restored.
- s04 ZiMatchZHSpelling: keep character-count helper result unsigned. Objdiff 98.80165% -> 98.80165%; rejected and restored.
- s05 ZiMatchZHSpelling: scope candidate length to the fallback spelling conversion. Objdiff 98.80165% -> build failed%; rejected and restored.
- s06 ZiMatchZHSpelling: return success directly after a complete partial matching scan. Objdiff 98.80165% -> 97.06612%; rejected and restored.
- s07 ZiMatchZHSpelling: initialize immutable candidate length after the success flag. Objdiff 98.80165% -> 97.19009%; rejected and restored.

### Block coverage audit

Address ranges group the complete target engine in object order; the basic-block map gives each individual instruction count, call and alignment. Every positive-length alignment difference belongs to exactly one range. Apparent gaps paired with displaced source blocks are not labeled missing behavior.

| Region | Target offsets | Code paths | Compiled attempts |
| --- | --- | --- | --- |
| R0 | +0000-1928 | input, masks, fuzzy preflight | b42, b43, b44 |
| R1 | +1928-1dd0 | table and mode setup | b01, b02, b45 |
| R2 | +1dd0-1f78 | punctuation | b03, b09, b46 |
| R3 | +1f78-2b5c | OEM | b04, b05, b10, b11, b31, b35 |
| R4 | +2b5c-3b80 | PUD | b06, b07, b08, b09, b32, b36 |
| R5 | +3b80-48bc | context phrases | b12, b33, b37, b39 |
| R6 | +48bc-5290 | prediction and dictionary candidates | b13, b20, b29, b40 |
| R7 | +5290-5a04 | character ranges | b14, b30, b47 |
| R8 | +5a04-626c | component and phonetic ordinals | b15, b16, b21, b22 |
| R9 | +626c-7110 | tones and user characters | b17, b23, b24, b25, b34 |
| R10 | +7110-7538 | global characters | b18, b26, b41 |
| R11 | +7538-7dbc | component phrases | b38, b48, b49 |
| R12 | +7dbc-88b8 | frequency merge | b27, b28, b50 |
| R13 | +88b8-94d0 | phonetic pairs and groups | b51, b52, b53 |
| R14 | +94d0-9be4 | phonetic candidate loop | b19, b54, b55 |
| R15 | +9be4-9fb0 | retry and finish | b56, b57, b58 |
| R16 | +9fb0-a6d0 | filtered table | b59, b60, b61 |

All 17 ranges have at least three distinct compiled source attempts. All 213 positive alignment differences are assigned in `/tmp/sol-med-zi8-blocks/deficit-regions.json`. Full block counts/calls/alignment are in `/tmp/sol-med-zi8-blocks/aligned-blocks.md`; call-anchored instruction differences are in `map.md`; the direct alignment is in `global.diff`. Reproducible generators and every trial source/build/measurement are in the same directory.

The initial b01/b02 combination failed its clean gate because it saved four registers instead of five, dropping matched exception data from 72 to 24 bytes. b03 restored the target five-register save sequence before the combined state was committed. b07, b08 and b09 were also rejected for the same data regression despite their lower deficits or higher scores. All later accepted changes passed the full-build quick gate with zero regressions, 72 matched data bytes, and no forbidden/readability findings.

Source cleanup removed redundant scopes and changed indentation only. The engine remains 10,614/10,676 instructions, fuzzy 78.76161%, with the target 0x4e0 frame and `_savegpr_27` sequence. The deficit improved 78 to 62; unit instruction-exact count remains 5/8, code 4,168/47,816, data 72/536. No exact function was added.

Remaining smaller functions were rechecked: Zi8GetElementCount has three fresh measured source attempts, s01-s03; all were restored, retaining 115/115 instructions with thirteen register differences at 99.347824%. ZiMatchZHSpelling has three fresh successful-build measured alternatives s04, s06 and s07, plus the failed C declaration-placement attempt s05; all were restored, retaining 121/121 instructions with 29 register differences at 98.80165%. The s05 log describes its intended placement; its actual trial declared candidateLength after the first assignment, which the C compiler rejected.

Instruction-only alignment excludes register names and branch spans. It does not prove semantic equivalence for approximate or displaced block pairs. Remaining structural differences include case/body ordering, scalar call-result moves, array-index expressions and long conditional branch expansion. The worker stopping condition is the exhausted region-attempt audit; the higher instruction-exact function-count completion condition is unmet.

### Final clean gate

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] pool: IDENTICAL
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] objdiff: code 4168/47816 data 72/536 functions 5/8 fuzzy 81.0138 linked code 0
[libs/RVLMiddleware/eZiText/src/clib/zi8cgetc] instruction-exact functions: 5/8
regressions vs baseline: 0
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
