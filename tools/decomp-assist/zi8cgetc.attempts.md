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
