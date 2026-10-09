# opus-chansvm: CHANSVm round (ConvertToFloatFromStr, WinEmuWrite, DateDtor, BlobGetHexString, BlobPackCommon, Step)

Worktree data-d2, branch agent/w1009/o-chansvm, base 72e9c8d6. Start: 227/233 exact.
Scratch harness: /tmp/opus-chansvm (score.py compiles the unit with the Ninja flags and diffs every function).

## combosweep (single + pairwise pragmas, whole unit)

No setting improves any of the six functions (Float 2, Win 5, Date 7, Hex 14, Pack 47, Step 262).

## CHANSVmConvertToFloatFromStr: 2 -> 0 (exact)

Diff: target `lbz type; li 0; stw endPtr; cmplwi`, ours `... cmplwi; stw`.

Scheduler RE (mwcceppc 0x599ac0 builds the block graph bottom-up; 0x5a0150/0x5a0170 is Alias.c may_alias):
a load gets an edge to every later store it may alias, with the load latency as delay. The `obj->type`
load had the worst_case alias set, which contains the escaped local endPtr, so LBZ -> STW had delay 2
and the compare won the cycle-2 tie. A load whose base register comes from a pointer-to-const (or
restrict) variable gets a private pseudo-object alias instead (see zcanann/FFCC-Decomp
tools/patch_compiler_rw.py notes), so the edge disappears and the store issues at cycle 1.

The inlined parser's `const` parameter is copy-propagated into the caller's `object`, so the const has
to be on the caller's parameter. Small-harness check: const/restrict on the inline parameter alone keeps
the old order; on the caller parameter it gives the target order.

| attempt | Float | others |
|---|---|---|
| `const CHANSVmObjHdr* object` on ConvertToFloatFromStr, `(VmConvertFunc)` cast at its table slot | 0 | no change |
| VmConvertFunc typedef and all 11 converters take const, cast in StrFromArray | 0 | no change |
| `#pragma opt_pointer_analysis on` (diagnostic) | compiler segfaults | - |

Kept the first (minimal) form. Same lever as CHANSVmParseInt (`const CHANSVmObjHdr* obj`).

## VmDateDtor: 7 -> 0 (exact)

Diff: target loads `MonthTbl[mon]` before the outgoing `year` stack-argument store; ours after it.
Same mechanism: the stack-argument stores carry the worst_case alias, and global tables are members of
it, so every store -> table-load edge had delay 2. The target object has no symbols for the two tables
(0xb34, 0xb50 are unnamed local data), so they were never globals.

| attempt | Date | others |
|---|---|---|
| file-scope `static` on both tables | 7 | no change |
| file-scope `static` on one table (each) | 7 | no change |
| both tables as function-scope `static` inside VmDateDtor | 0 | no change, .data bytes identical |
| plus direct `date.x` access instead of `datePtr` | 84 | - |

Kept function-scope statics with the datePtr form.
