# o3-chansvm: CHANSVmStep li/stw scheduling pair

Worktree data-d2, branch agent/w1009/o3-chansvm, base 239334ba. Start: CHANSVmStep 2 differing
instructions (836 `li r14, 0` / 837 `stw r26, 0xc(r1)` swapped), unit 232/233 exact, NonMatching.
Scratch: /tmp/o3-chansvm (score.py = whole-unit compile + per-function compare, 0.6 s; t/ = a
40-line reproduction of the GET_PROPERTY_NAME control flow, 0.3 s per compile).

## Why the scheduler always put the store first

Scheduler model from rayanht/mwcc `Scheduler.c` and `MachineSimulation750.c`, checked against our
captures (B261 in backend-00/01 of _mwdbg/runs/o3-chansvm-base):
- On the 750 model `li` has latency 1 and `stw` latency 2. Each node without successors gets a
  latency-0 edge to the block's branch, so height(stw) = 2 and height(li) = 1.
- `select_ready_coloring_node` prefers the node whose latest cycle has been reached. At cycle 0 the
  store is urgent and the li is not, so the store is issued first whatever the source order. That is
  why every statement order, type and status-local variant in g/g2-chansvm kept the same pair.
- `Scheduler_Schedule` only schedules blocks with more than two instructions. A two-instruction
  block keeps source order in both passes (harness: li stays first when the block falls through).

## What the target block really was

The target's three early exits (`beq/bne 0xcac8` at 759/762/769) and the `b 0xcac8` after the store
fit this layout before assembly:
- B261 = `li result; stw shouldBranch` (two instructions, never scheduled, source order).
- X = `mr result, <status>; b property_done`, reached by B261's fallthrough and by the three early
  exits, so MergeAdjacentBlocks cannot merge it into B261.
- The allocator coalesces the status with `result` (both r14) and deletes the copy, leaving X as a
  lone `b`. `optimize_branches` in PCodeAssembly then threads the early exits through X to
  property_done, so the final code shows no trace of X.

In C this is a case-local status for GET_PROPERTY_NAME, like the case-local results the other cases
already use (booleanResult, loadResult, arrayResult, deleteResult, caseResult), copied into `result`
after the property block, with the OK assignment written before the flag store. IRO cannot fold the
copy: the status is ERR on the early-exit paths and OK after the enumeration.

## Attempts

| attempt | Step diffs | others |
|---|---|---|
| harness: flag/status order, u8/s8/u16/s16 flag, inline setter, pointer to the flag, opt_propagation off | stw first | - |
| harness: do/while(0) breaks, goto early exits, extra end label, else branch | stw first | - |
| harness: B261 falling straight into property_done (error block moved) | li first | layout differs from target |
| harness: case-local status, OK before flag store, `result = status` after the if | li first, target layout | - |
| harness: same with the flag store first | stw first | - |
| CHANSVmStep: `propertyResult`, declared in each of the 74 local slots | 0 in 57 slots, 115 in slots 43-59 | all 232 others exact |
| kept: declared after `result` | 0 | pool identical, 233/233 |

## Result

CHANSVmStep 2 -> 0 (1253/1253, 5012 bytes). CHANSVm 233/233 exact, flipped to Matching.
Full build links build/43U/src/src/channelScript/CHANSVm.o; main.dol SHA1
26116613f624061ba99c8d1a299aaa6efa85670d. Unit report: code 53564/53564, data 6904/6904, complete
code and data 100%.

`gate.py src/channelScript/CHANSVm --quick`: GATE PASS, 0 regressions, 0 forbidden patterns,
0 readability warnings, all six sections 100%. Global complete code 94.67 -> 96.46 percent.
