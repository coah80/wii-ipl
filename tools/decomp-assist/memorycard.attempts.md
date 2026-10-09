
## Wave w1011c — scheduling/opt pragmas on _create_icon (no movement)

Baseline 100v100 insn-equal, 20 diff ops (remat-vs-pin wall):
- `scheduling 604` → 26d (worse); `scheduling 750`/`schedule_twice on` → 20d (inert)
- `optimization_level 2` → 104 insns (+4, 11d) — rejected
- `ppc_iro_level 2/3` → 21d/20d (inert); IRO 0/1 previously regressed to 124v100
- TU `-ipa function`/`-ipa off` → 20d (inert); TU `-O4,p` → 20d (inert)
