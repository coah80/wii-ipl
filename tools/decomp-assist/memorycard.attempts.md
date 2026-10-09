
## Wave w1011c — scheduling/opt pragmas on _create_icon (no movement)

Baseline 100v100 insn-equal, 20 diff ops (remat-vs-pin wall):
- `scheduling 604` → 26d (worse); `scheduling 750`/`schedule_twice on` → 20d (inert)
- `optimization_level 2` → 104 insns (+4, 11d) — rejected
- `ppc_iro_level 2/3` → 21d/20d (inert); IRO 0/1 previously regressed to 124v100
- TU `-ipa function`/`-ipa off` → 20d (inert); TU `-O4,p` → 20d (inert)

## w1011e — _create_icon decode progress

Orig pattern decoded: literal `&mFileCell[slot][file].icon` in first call arg
(recomputed per call) + NAMED local declared between calls -> "recompute + pin"
(`add r3,sum; bl; add r24,sum; mr r3,r24`). texObj/tlutObj named locals reproduce
the pin structure — diff moved to pure reg rotation but stays 20d.
Assoc fossil: orig groups `+0x10EC` (0xFE8+0x104 = member+icon offsets) into the
ROW base BEFORE `file*0x15c` — `((this+slot*S)+0x10ec)+file*0x15c`. Natural
`[slot][file].member` assoc is index-first. cell*/flat-byte/row-ref variants
regress (26/24/24). Also orig saves args r25-r28 vs mine r24-r27 — one extra
early callee web again.
