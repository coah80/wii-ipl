# tiZiString attempts

Created readable members from the extracted object and the existing tiString, tiZiString, tiUtil and tiCpData declarations. No source existed at task start. Replaced old scratch source's raw field casts, fabricated vtables, address labels and casts to an incompatible EZTXGetCandidates prototype. Reused PaneNameToCharCode::wc for holding-key characters; dictionary offsets are the actual serialized OEM dictionary format. Both string pools are empty. All 7680 data bytes match: BSS buffers in original order, ordinary Korean letter tables, ten Latin search-order entries, compiler switch table and vtable. The second Korean lookup table has the target's sixteen wchar_t slots, initialized with its ordinary fourteen-character literal and terminator.

## destructor
1. Normal destructor with only the dictionary allocation release: 29/31 instructions. Base destructor relocation was Decolated, whereas target calls StringBase.
2. Supply the ordinary inline Decolated destructor: 31/31, zero differences. Retained; the compiler supplies the additional null test and base destruction.

## clearCandidates
1. Typed EZTX fields and actual CandidatesBuffer subarrays instead of out-of-bounds ElementBuffer aliases: 84/81, 88.5679%. An additional pooled-buffer base register is live.
2. Reorder elementCount before firstCandidate as in the target: still 84/81, improved to 91.049385%. Retained.
3. Initialize typed elements/candidates pointers before the open-dictionary test: 80/81, 83.34568%, with additional saved registers and changed address lifetimes. Discarded.
Remaining: pooled buffer addresses and their register lifetimes; no raw cross-object offset alias is used.

## partialConfirmForKR
1. Explicit grouped comparisons inherited from scratch: 153/147; duplicated one-character fallback and missing loop-index maintenance.
2. Ordinary bounded indexed loops with initialized match flag and shared fallback: 148/147; flag lifetime differed.
3. Assign match only on loop exit, share fallback via labels: 147/147, 23 register differences.
4. Share loop index across both scans: unchanged 23 differences.
5. Pointer scans with postincrement: 147/147, 21 differences including scheduling.
6. Increment pointers after the unsuccessful comparison: 147/147, twelve differences, all r4/r5 in the second scan. Retained.
7. Initialize the second index before assigning its table pointer: unchanged twelve differences. These are allocator tie-breaks.

## update
1. Replace raw EZTX bytes with fields and holding-key offsets with typed records: 441/446, 77.3296%. This exposed incorrect scratch semantics and a wrong parameter-field layout.
2. Reset selected candidate, use a zero-extended element count, correct EZTX byte fields, use context |= 0x20 and inclusive element bounds; use a real bounded key-character loop and normal two-argument library call: 455/446. Corrected state/parameter writes and removed the incompatible function-pointer call.
3. Replace the manually expanded latest-word copy with an ordinary loop: 456/446.
4. Make the zero-extended element count a signed comparison operand: 456/446, 84.84529%.
5. Reuse sibling PaneNameToCharCode::wc; preserve the destination base with separate copy cursors; share successful candidate counting and use the target's letter-mode switch: 448/446, 91.4305%. Retained.
Remaining: buffer-base lifetimes, phone-loop scheduling, context-copy loop and saved-register allocation. No artificial extra library arguments retained.

## setElementBuffer
1. Typed indices replacing raw byte offsets: 67/65, 88.58462%; an extra index narrowing and secondary buffer base.
2. u32 element index rather than u16: 67/65; same count, different shift/narrowing.
3. Direct typed indices in condition/body: 66/65, with an extra load of the input character.
4. Initialize typed pointers/count before memset and use the condition's loaded character in the body: 65/65, twenty-four instruction differences; 87.815384%. Retained as the closest instruction structure.
5. Initialize pointers after memset and keep a u32 masked index: 66/65, 87.49231%. Discarded.
Remaining: pooled buffer base setup and callee-saved register assignments, with identical instruction count.

## setCurrentWord
1. Normal element indexing in the existing copy loops: 56/56, twenty-one differences; compiler strength-reduces indexed accesses to moving pointers.
2. Load source character then advance length/cursors before storing: 56/56, same differences.
3. Unsigned source/destination indices, store via length - 1: 56/56, same differences.
4. Remove the now-unused destination index: retained readable implementation; no output change.
Remaining: copy-loop address strength reduction, scheduling and caller-register assignments; 86.69643%.

## clearCandidates — session 3

Base binds the first static array (ElementBuffer) to r31 via lis/addi and
recomputes every memset arg as `addi r3,r31,off`; mine CSEs the
CandidatesBuffer base into a 4th callee reg (addi r31,r29,0x200). Tried:
`&arr[i]` vs `arr+i` args, cast forms, memset reorder — all invariant.
Same reverse-bind family: base binds globals high, this low.

## update — session 3

446v448, same family: base binds this->r28, global->r31 (savegpr_24 both);
mine rotates this->r29+ and gains 2 body insns. All-diff regions are pure
reg-name permutations; no structural gap found.
