# o4-aosslink attempts (AOSSi_WLANConnect, 2026-10-09)

Worktree data-d1, branch agent/w1009/o4-aosslink at 0cffbfe4. Start: AOSSLink 13/14 exact,
AOSSi_WLANConnect 2/155 (second memset: target `li r4,0; li r5,0x7c4; mr r3,r27`, ours
`li r4,0; mr r3,r27; li r5,0x7c4`), NonMatching.
End: 14/14 exact, AOSSLink flipped to Matching, main.dol SHA1 26116613f624061ba99c8d1a299aaa6efa85670d,
`gate.py src/scene/setting/AOSSLink --quick`: GATE PASS, 0 regressions, 0 forbidden, 0 readability.

Scratch: /tmp/o4-aosslink (cc.sh/cmp.py/try.py variant harness, sim.py + xenum*.py scheduler
enumeration on o3's sched13.py, blk.py stage tracer). Stage captures: /tmp/o2-aoss/mwdbg2/runs/o4-*
(per-pass PCode dumps); /tmp/o2-aoss/mwdbg3 adds a dump of the VN range globals.

## Source change

The IP-config step is guarded like every later step of the function:

    result = 0;
    if (result == 0) {
        ipConfig = &AOSSi_NcdIpConfig;
        memset(ipConfig, 0, sizeof(*ipConfig));
        ...
        if (NCDSetIpConfig(ipConfig) != 0) {
            result = -1;
        }
    }
    if (result == 0 && NCDSetIfConfig(&AOSSi_NcdIfConfig) != 0) {

For review: the first guard is always true where it stands (result was just set). It is the
function's uniform step-guard style (`if (result == 0 && NCDSetIfConfig...)`, `if (result == 0)
{ wait loop }`, `if (result == 0) { status }`), and it is the only structure found that
reproduces the target (see below). `if (!result)` and a fully nested chain for NCDSetIfConfig
are also exact.

## Why it works (stage dumps, capture o4-p4)

1. Pass 1 schedules each block on its own, with the opcode-rank tie-break (mr 0 < li 4). With
   `result = 0` in the memset block, cycle 2 has `mr r3` and `li r5` both critical and `mr r3`
   wins (baseline o4-base).
2. With the guard, `li result,0; cmpi; bf` is its own block at pass 1 (B14) and the memset block
   (B15) is `lis; addi; mr r3; li r4; li r5`, scheduled `lis, li r4, addi, li r5, mr r3`.
3. The post-scheduling peephole folds the constant compare (stage 28 -> 29), the two blocks
   merge, and pass 2 (no rank tie-break, list order, IU2 forwarding rule) emits
   `lis, li r28, addi, li r4, li r5, mr r3`: the target.

## Why the copy routes in o3's notes cannot work here

- 3.0a5.2's value numbering canonicalizes operands at the start of every instruction
  (0x5979ca): a use of a copy's destination is rewritten to the copy's source when the source
  is virtual and unchanged, everywhere in the extended basic block (B13..B22 here). Copy
  propagation mode 0 then unlinks the dead copy (0x621e70). Copies of parameters survive
  (physical canon, lever 37/ATERM); nothing in B14 has one.
- VN2 numbers `li` only for temps (dest in [0x710768], [0x7100fc] = r39..r80 here), so it
  cannot copy `result`'s zero; mode-1 copy propagation never unlinks a dead copy (0x621d40),
  which is why VN2 copies reach pass 1.
- Proof of the copy mechanism (e1): a copy of ipConfig used only after an artificial merge
  reaches pass 1 (`li r4; mr copy; li r5; mr r3`), RA coalesces it and pass 2 emits the target
  order. Not usable: the target has no ipConfig use after B20.
- Scheduler enumeration (sim.py/xenum.py): one transient `mr` reading the address, the result
  zero or the lis temp, listed before `mr r3`, also gives the target; a block boundary between
  `result = 0` and the memset is the natural source form of the same effect.

## Attempts

| attempt | WLANConnect diffs |
|---|---|
| baseline | 2 |
| copy `config = ipConfig` + opt_propagation/common_subs/dead_code/lifetimes/dead_assignments off | 2 (VN1 rewrites, stage 09 deletes) |
| same + peephole off | 11 |
| same + optimization_level 2/3 | 2; level 0/1: 139+ |
| typed sub-struct pointer `adjust = &ipConfig->adjust` before memset | 2 (add propagation removes it at stage 10) |
| typed sub-struct pointer `ip = &ipConfig->ip` | 97-103 |
| result copied from a zero variable (same block) | 2 (pre-phase retarget folds it at stage 05) |
| while (1) { ... break; } / do { ... } while (0) around the step | 2 |
| combosweep single + pairwise pragmas | 2 |
| unit flags (-O4,p, -O3, inline modes, -ipa function, -opt variants) | 2 or much worse |
| GC/3.0a3 .. 3.0a5.2 | 2; Wii/1.x: 134+ |
| no string.h prototype | 2 |
| `if (result == 0) { ip-config step }` | 0, kept |
