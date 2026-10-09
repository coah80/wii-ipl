# a2c-hasch attempts

Worktree data-d9; branch agent/w1009/a2c-hasch; base 85d653b0.
Full initial 43U build passed. DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
Owned function: hasChannel__Q33ipl8savedata7ManagerCFUxPiPi.

Read opus-common.md, AGENTS.md, opus-sdm, opus-iro, sol-ph1, and o3-idct evidence.
Prior best C: 12 differences, 71/71 instructions, 284/284 bytes.
Prior failures covered mask spelling, helpers, parameter copies, loop forms, and eight declaration orders.
Avoid repeating those sweeps. New method: full target-register map and declaration-order simulation
restricted to implementable locals, then restructure only if captured compiler temporaries require it.
The older simulated exact allocation moved compiler temporaries, so it was diagnostic only.

## Capture and legal declaration search

Corrected a missing closing brace during seed extraction; the failed compile was not measured as C.
Fresh seed build: 12/71 differences, 284/284 bytes; pool identical 3/3.
Baseline completion checker: DECOMPLETE_OK.

Two initial --args captures failed with WRITE_UNMAPPED at 40495a because --args disables automatic
sjiswrap detection. README identifies this exact failure. Recaptured through Ninja flags with sjiswrap.
Fresh capture: /mnt/drive2/projects/wii-ipl-workers/_mwdbg/runs/a2c-hasch-03.
regsim reproduces 53/53 virtual registers. The supplied vmap.py cannot align this function's
save/restore pseudo-instructions: 1 mapped register, 39 unmatched definitions. Used the existing
vmap2.py alignment fallback; it maps 29 registers across 60 instructions with unambiguous wants.

Exhaustive permutations of legal named locals stored/index/page leave all five allocation misses.
The supplied declsearch2.py confirms cost 5. The row-base virtual r45 is @17360; full-mask halves
r46/r47 are @17357. Diagnostic relabel r45 -> 48 alone gives all 29/29 target assignments,
including the two mask-constant registers. This is a required creation-order change, not a
declaration recipe. New hypothesis: preserve a real page view or mask locals so their source
creation order becomes controllable.

Moving the full-mask conditional inside the page loop: 53/71; inside the channel block: 50/71.
Plain SInfo row pointers add a base adjustment: 60/72, 70/72, 67/72.
Explicit nonzero if/else gives 12/71 but moves the row base to the desired r0 and swaps full/region
mask registers; capture this form to distinguish real locals from hoisted temporaries.
Scoped opt_lifetimes, opt_propagation, opt_strength_reduction off: each 12/71.
Scoped opt_loop_invariants off: 29/71. Scoped optimization_level 3: 35/71. Restored seed.

## Exact source

Explicit mask branches preserve mask as a named local; the region-mask expression remains an
IRO temporary when declared in the channel block. Legal declaration search stays at 4 mismatches.
A ChannelPage view makes the row pointer named, but leaves the region temporary ahead of both
row and full mask; legal search stays at 4 mismatches. Restored the experimental header fields.
All row-view candidates were rejected: 14-20 differing instructions, no lasting header edit.

Computing regionMask once outside the loops preserves a real invariant, but default IRO also
hoists titleId & regionMask and changes the instruction stream, 45/71 differences.
A scoped opt_loop_invariants off with this source prevents that extra hoist and produces
0/71 differing instructions, 284/284 bytes, on the first compile. Scoped ppc_iro_level 1 is
also exact, but the narrower loop-invariant switch is retained. Adding opt_common_subs off
is unnecessary. The earlier declaration-only proof identified the temporary-creation blocker;
the accepted source expresses the invariant directly and uses the owner-authorized scoped pragma.

Removed the hasChannel inventory row and decremented function/block/placeholder counts.
Removed the two external save/restore declarations that only the former assembly body used.

## Final validation

Final formatted source rebuilt successfully after removing assembly-only declarations.
Exact-name objdiff: hasChannel fuzzy_match_percent 100.0, size 284.
odiff: 0/71 differing; ctxdiff: 71/71 instructions, diffs 0.
Pool identical 3/3; the complete .data bytes are identical, 184/184.
Unit: 35/35 objdiff and instruction-exact functions; code 7172/7172; data 968/968;
linked code 7172. .data, .rodata, .sdata, and .text all 100.0.

Full 43U build passed. main.dol SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.
Fresh build/43U/report.json passed check_decomp_complete.py: DECOMPLETE_OK.
Gate command: gate.py src/system/iplSaveDataManager --base 85d653b0 --quick.
GATE PASS: zero regressions, zero forbidden additions, zero readability warnings.
The gate reports the scoped optimization pragma for parent review. Target comparison instructions
37 and 39 mask the input title inside the loop; default IRO with an explicit regionMask hoists
those two computations to the preheader. The scoped switch preserves those target lifetimes.
Evidence: /tmp/a2c-hasch-gate.log and /tmp/a2c-hasch-final-build.log.

check_asm_inventory.py still returns 1 solely for the three other owned placeholders:
TMCJPEGDEC_err_restart, CNTCACHEClear, and System::warning_run. There are no missing/stale rows
or coverage failures. Counts match the updated header: 165 functions, 167 bodies/blocks,
162 ORIGINAL, 3 PLACEHOLDER. hasChannel no longer contains assembly.

Experimental header changes and generated dependency files were removed. Only the function,
its inventory removal/counts, and this log are retained. No push, PR, merge, or rebase.
