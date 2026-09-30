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
