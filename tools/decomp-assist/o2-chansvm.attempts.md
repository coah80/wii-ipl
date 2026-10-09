# o2-chansvm: CHANSVm round 2 (WinEmuWrite, BlobGetHexString, BlobPackCommon, Step)

Worktree data-d2, branch agent/w1009/o2-chansvm, base 20cf9f9f. Start: WinEmuWrite 5, BlobGetHexString 14,
BlobPackCommon 47, CHANSVmStep 262 (odiff differing instructions).
Scratch: /tmp/o2-chansvm (score.py = whole-unit compile + per-function diff; t/ = one-function harness
that reproduces the unit's codegen in under a second; tmw.sh = mwdbg on a harness file, ~8 s).

## VmWinEmuWrite: 5 -> 0 (exact)

Diff: strObj and totalLength swap r27/r29. mwdbg: every node is low-degree, so the color order is plain
descending vreg number. Named locals are numbered first (reverse declaration order), then IR temps and
inline locals (forward order), then codegen temps. The strObj value survived as the codegen temp of the
call result (`mr r40, r3; mr r37, r40` -> r37 propagated away), so it always had the highest number of
the loop values and took r29 first.

Copy-propagation probes on small functions (X1-X12 in t/x*.c): the backend replaces a named local by
the call-result temp unless the named local has a copy use (`mr rX, local`). Load-base and compare uses
do not block it; a copy use does (X8 vs X7). IRO removes plain `p = o` copies and inline parameters
before the backend sees them (X11, X12).

`strObj = CHANSVmGetArgString(vm, 0)` (the real exported helper, inlined) leaves the inline's return
temp (@1501, IR class) with a copy use, so that temp survives instead of the codegen temp. Moving the
loop into a static inline helper numbers its locals after that temp, which gives the target order.

| attempt | Win | others |
|---|---|---|
| strObj assigned twice (GetArg, then Convert), 3 declaration orders | 5 / 8 / 8 | - |
| for loop, guard clause, no `remaining`, if/else inLen, assign-in-if, nested if | 5 .. 54 | - |
| GetArgString only | 5 | - |
| loop in inline helper only (prior run) | 10 / 13 | - |
| GetArgString + inline helper, locals offset, totalLength, buf, outLen, inLen | 5 (outLen/inLen slots swapped) | - |
| GetArgString + inline helper, locals offset, totalLength, buf, inLen, outLen | 0 | no change, pool identical |

## VmBlobGetHexString: 14 -> 0 (exact)

Diff: loop registers. Target colors IV4 (byte offset +4) r4, the +2 counter r5, src r6, digit chain r7,
hexTbl r8; ours had the counter and the digit chain swapped. The digit chain is codegen temps, so the
counter and src must be numbered above it: both have to be strength-reduction IVs, created in the order
src, counter, IV4.

Per-pass PCode dumps (private copy of mwdbg with a breakpoint after every pass call in the -O4 driver at
0x5964c0, /tmp/o2-chansvm/mwdbgp) showed what each form does:
- pass 10 (0x62be80) is strength reduction; pass 14 (0x62e8d0) the CTR conversion.
- `src[byteIndex]` makes src an SR IV; `dest[byteIndex * 2]` gives IV4.
- A separate +1 counter for the low index (`lowDigitIndex = i * 2 + 1; i++`) gives the target coloring,
  but SR rewrites i as `mr i, byteIndex`, which keeps byteIndex alive past the CTR conversion: two extra
  instructions (n=84).
- `lowDigitIndex = byteIndex * 2 + 1` with matching signedness is folded by the front end into a
  displacement (`sth 2(rX)`, n=79).
- A signed index variable fed from the unsigned counter blocks that fold: the low index stays
  `(cnt + 1) << 1` with cnt = SR(byteIndex << 1), created between src and IV4.

| attempt | Hex |
|---|---|
| 16 combinations of src (ptr/index) x high (destOff/byteIndex*2/i) x low index | 16 .. 48 |
| byteIndex*2+1 low index forms (a1-a7), digitIndex++ forms (q1-q5), dest[j++] x2 (j1-j6) | 38 (n=79) |
| separate +1 counter for the low index (m2, n1-n6, 24 declaration orders) | 50 (n=84) |
| u32 counter, int/s32 low index (t_u32_int, c1, c5, c6) | 0 |
| int highDigitIndex/lowDigitIndex from u32 byteIndex (c7, kept) | 0, no change elsewhere, pool identical |

## VmBlobPackCommon: 47 -> 0 (exact)

Diff: argArr (ours r23, target r18) and argCount/writeArgCount (ours r18, target r23). The allocator
needs three simplify sweeps here, so sweep membership matters, not only numbering. A graph simulator
(/tmp/o2-chansvm/packsim.py, built on regsim) traced remaining degrees per sweep:
- Swapping the argArr/writeArgCount declaration slots alone fails: argArr reaches its sweep-2 scan
  with degree 29, one over the limit, and drags fmtLen/fmtStr/parentBlob into sweep 3.
- With argArr one neighbour lighter at that point, the swap plus argCount declared between fmtPos and
  totalSize reproduces every target register.
- Searching single-node renumberings found the neighbour: @10858, the `dataSize` local of the
  VmBlobCopyPadded inline. Inline locals are numbered after all declared locals; the target needs it
  in the declared range (ids 36..45), i.e. a local of PackCommon itself. srcOff and dest may sit
  anywhere (3855/4000 sampled placements hit).

Kept: the copy code written out in case 4 with writeBlobSrcOff/DataSize/Dest locals of the function,
argArr and writeArgCount declarations swapped, argCount declared between fmtPos and totalSize.
VmBlobCopyPadded (only used here) removed. Pool identical, no other function changed.

| attempt | Pack |
|---|---|
| shared argCount for both passes (merged node), all placements in the simulator | >= 28 misses |
| shared counter, restricted declaration-order annealing (6 seeds) | 7 misses best |
| simulator: swap only / swap + one edge cut / swap + merged loop constants | 3 / 2 / 0 misses |
| simulator: swap + argCount slot + @10858 in declared range | 0 misses |
| source: inline copy code with function-scope locals + two declaration moves | 0 |

## CHANSVmStep (in progress)

Structure first (opcode stream with registers masked, difflib-aligned; /tmp/o2-chansvm/opdiff.py),
then allocation. Findings, each checked against the target object:
- The target addresses VmResultTypeTbl and the constant objects off one .rodata base (r28 = .rodata+0,
  offsets 0x160.. and 0xa0). MWCC pools a section base only when a function references three or more
  distinct objects in it (/tmp/o2-chansvm/pool/p3.c: two objects never pool, three always do, global or
  static). VmResultTypeTbl (0xB4) has no relocation anywhere in the target: it is a dtk-inferred
  aggregate of five 6x6 tables (lever 13). Five separate tables give the pooled base.
- `&CHANSVmConstStringObjectUndefined_[4]` takes two addis (array, then element); the target takes one
  (`addi r5, r28, 0xa0`), so those five 16-byte objects were separate too. With names, the `base[7]`
  hack in CHANSVmConvertToStrFromFloat goes away and that function stays exact.
- `if (stepCount == 0) stepCount = 1;` plus `while (stepCount-- != 0)` (target enters the loop with a
  branch to the test at the bottom).
- Stack: target 0x30 = object behind stackPtr (SET_INDEX), 0x40 = STORE_INDIRECT object, 0x50 load,
  0x60 operand. MWCC orders frame slots by size, ties in reverse declaration order (pool/s2.c), so
  `copies[2]` was two separate objects.
- operandTypes filled through `&operandTypes[typeIdx]` (target keeps a +4 byte IV), not a walker.
- BRANCH_CASE computes into a case-local result (target `li r3, ..` then `mr r14, r3` at the join)
  and stores the flag only on the OK path after the pop.
- GET_PROPERTY_NAME: `foundEntry = 0` before the lookup, a one-case `switch (foundObj->type)` (target
  `beq +8; b far`), `shouldBranch = foundEntry` before `result = OK`, check reads shouldBranch.
- BRANCH_CASE reads pObjStackTopBuf into stackTop before the stackDepth test.
With these the opcode stream matches except three scheduling ties (511, 598, 836) that depend on
registers; 297 register differences remain.
