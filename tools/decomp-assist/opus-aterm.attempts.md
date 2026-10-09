# opus-aterm attempts (ATERM, 2026-10-09)

Baseline 72e9c8d6: ATERM 20/26 exact; open: BuildEncryptedMessage 2, AutoConfigThread 3,
AesExpandEncryptKey 6, DiscoverAccessPoints 17, BuildAssociationRequest 28, RunConfigProtocol 294.

## Pragma sweep (combosweep, GC/3.0a5.2)

Single and pairwise pragmas: no function improves (BEST = base for all six).

## Compiler version (new finding)

Compiled the unchanged ATERM.c with every GC/Wii compiler that accepts the unit's flags:

| compiler | exact | total diffs | AutoConfigThread |
| --- | ---: | ---: | ---: |
| GC/3.0a3, 3.0a3.2, 3.0a3.3, 3.0a3.4, 3.0a5 | 21/26 | 347 | 0 |
| GC/3.0a5.2 (previous) | 20/26 | 350 | 3 |
| Wii/* | 7/26 | 1590+ | 5 |

GC/3.0a5 makes ATERMi_AutoConfigThread exact with no other function changing; pool identical,
data 100%. The other third-party middleware in this project (Zi Corp eZiText, NHTTP, bte) is already
built with GC/3.0a5. Set `mw_version="GC/3.0a5"` on ATERM.c.

## ATERMBuildEncryptedMessage (2: entry `mr r29,r7` / `mr r3,r27` swapped)

Read MWCC's scheduler (rayanht/mwcc decomp: Scheduler.c, MachineSimulation750.c) and wrote a model
(/tmp/opus-aterm-sched/sim.py). It reproduces our entry block and six micro-tests exactly (count of
unlocked successors, then height, then opcode rank mr < li, then program order; 2 IU slots).
The entry block is scheduled once, before register allocation (block flag 8 stops the post-RA pass).
Exhaustive search over that model: no order of the same ten PCode instructions with the parameter
copies first gives the target, and no single extra/deleted instruction does either. The target order
needs the copy of r7 to come after memset's first-argument move in the scheduler input.

## ATERMAesExpandEncryptKey (6 -> 0, EXACT)

The function is rijndaelKeySetupEnc from the public reference rijndael-alg-fst.c (Te4 = the
substitution table, rcon = the round constants). Earlier forms (initialKey[] array + copy loop,
hand-reassociated XOR trees) left the second key word's two XOR halves scheduled in the other order.
Trials (all GC/3.0a5): array/scalar/direct stores x seven XOR associations: 9..268; reference
GETU32 + reference loops verbatim: 3 (only cmplwi vs cmpwi); with the reference `int keyBits`: 0.

## ATERMDiscoverAccessPoints (17 -> 7)

mwdbg: callee-saved colors go r31 downward in decreasing vreg number. The three strength-reduced
record pointers (entries[i].ssid, entries[i] base, entries[i].bssid) are compiler temps created in
first-use order, so the target's increment order (ssid, base, bssid) means all three were indexed
accesses, not named cursors. The descriptor start (scan buffer + 2) has r27 above them, so it is a
loop-invariant expression hoisted after strength reduction, not a named local set before the loop.
- indexed record fields, named firstDescriptor: 22 (increment order fixed, firstDescriptor r24)
- descriptorWords = (u16*)scanBuffer + 1 inside the loop: 7; &((u16*)scanBuffer)[1]: 7;
  (u16*)(scanBuffer + 2) and (u16*)(scanBuffer + sizeof(u16)): 105 (size changes)
Remaining 7: MAC formatter input pointer r9 vs target r5, low nibble r5 vs r9.
