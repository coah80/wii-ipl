# opus-prior: makePriorTitleIDList__Q33ipl8savedata7ManagerFPUxPUxUl

Start: opus-sdm best (p1 below), 96 differing / 133, 122 instructions.
Measured with odiff (differing / total). Harness spliced each trial over the asm block.

## Cause

The target is exactly MWCC's code with IRO (the front-end optimizer) disabled for this function.
No CSE of `&titleIdsIn[i]` / `&titleIdsOut[outputIndex]`, no LICM of `outputIndex << 3`, and the
backend alone strength-reduces and hoists the constants. That's why every C spelling caches the addresses.

| # | Change | odiff |
|---|---|---|
| p1 | opus-sdm best | 96 |
| h1 | `*&titleId` in isEqualChannel | 96 |
| h2 | assign through pointer helper | 97 |
| h3 | titleId written through a local pointer | 96 |
| b | match handled by switch (-2/0, 1) | 95 |
| a | goto instead of continue | 96 |
| d1 | diag `#pragma opt_common_subs off` | 64 |
| d2 | diag `#pragma opt_loop_invariants off` | 120 |
| d3 | diag both | 24 |
| d4 | diag `#pragma global_optimizer off` | 148/150 |
| d5 | diag `#pragma ppc_iro_level 0` (or 1) | 24, 133 insns, register names only |
| t1 | diag statement `asm { nop }` in body (IRO DisableDueToAsm) | same shape as d5 + nop |
| q1 | d5 + outputIndex declared before titleId | 10 |
| **q2** | d5 + `int outputIndex;` at function top, assigned per slot | **0 (exact)** |
| s1 | no pragma, function-local static | 116 |
| s2 | no pragma, try/catch | build error (exceptions off) |
| s3 | no pragma, inlined nw4r::math::FAbs (asm inline) | 119 |

## Result

Exact only with `#pragma push / #pragma ppc_iro_level 0 / #pragma pop` around the function (q2, saved in
opus-prior.best.cpp). The brief forbids `#pragma`, so this is not landed. Upstream uses the same pragma for
the same symptom (`// uhh` before iplChannelManager.cpp loadMetaHeaderAsync, iplUtility.cpp
BScroller::set_arw_param; koopthekoopa ff68d54a / 25f93e26). No natural construct found that disables IRO
(MWCC disables it for functions containing an asm statement; none fits here). Orchestrator call: allow the
upstream-precedent pragma for this function, or park it.

## Round 2 (landing)

Orchestrator accepted the function-scoped `ppc_iro_level 0` push/pop as an exception (same convention as
iplChannelManager.cpp, iplUtility.cpp, iplBoard.cpp, iplChannelTitle.cpp). q2 replaces the asm placeholder;
odiff 0 / 133, size 0x214 both; all 35 functions in the unit 0 differing; pool identical. Inventory row
removed (checker flagged it stale once the asm was gone); header counts 171/173/162/9. opus-prior.best.cpp
deleted as obsolete. Gate: only forbidden pattern is the pragma (push, ppc_iro_level 0, pop).
