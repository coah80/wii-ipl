# opus-bs2update UpdateThread attempts

Worktree data-d10, branch agent/w1009/o-bs2update, base 72e9c8d6 (origin/main). Owned `src/BS2/BS2Update.c`; the fix also needs a one-line rename in `config/43U/symbols.txt` and the Matching flip in `configure.py`. Read opus-common, levers, the effort-policy entries, sol-x8, sol-y3 (`git show 4925fde2`) and sol-z1.

Start: UpdateThread 6/913 differing, equal size 0xe44. The other nine functions are exact. The remaining diffs are the three seat-loop scheduling swaps described by sol-x8, sol-y3 and sol-z1.

combosweep (single and pairwise allowed pragmas): `BEST src/BS2/BS2Update UpdateThread base 6 -> 6 []`. No pragma moves it.

## Diagnosis

The decompiled 1.2.5 scheduler (rayanht/mwcc `src/backend/Scheduler.c`, inspiredrobot/mwcc `docs/SCHEDULER.md`) adds a store-to-later-load edge for every memory pair the alias test cannot separate, with the store's latency. sol-y3's capture already showed that the seat loads carry a worst-case alias set that contains Flags0's bit, so `Flags0[index] = 0` wins the height race against the seat address `add`. The target schedules the `add` first. That is the order you get when no such edge exists.

I tested small probe functions with the unit's exact compiler flags: a loop that stores `FlagsX[i] = 0` and then tests `p[i].attr & 1`. The results:

| Seat entries come from | Flag array | Edge (store first)? |
| --- | --- | --- |
| absolute `T a[] : addr` (array, struct, single entry, const, static) | file-scope static | yes |
| integer cast `(T*)0x80480000 + n` (folds to `addis`, wrong form anyway) | file-scope static | yes |
| pointer parameter | file-scope static | yes |
| normal relocated global array | file-scope static | no, but needs `lis/addi` with relocs (wrong form) |
| absolute array (target's `lis r0,0x8048; add` form) | file-scope static, initialized or tentative, extern | yes |
| absolute array | **function-local static** | **no** |
| absolute array | global scalar / local stack array | no |

An unknown pointer (absolute storage counts as unknown) may alias every file-scope object, but not a function-local static whose address is never taken. The target keeps the absolute `lis r0, 0x8048; add` form and has no edge. So Flags0 was a function-local static of the selection code.

## .bss order

The target order is Flags0, Flags1, Thread, ThreadStack, UpdateHeader0, UpdateHeader1. Probes on the same compiler show the emission rules:
- initialized objects are emitted where they are defined;
- tentative definitions are emitted at their first use;
- a function static is emitted when its function is parsed.

So the static has to come from a function parsed before BS2UpdateInit, and the other five arrays have to be tentative definitions. Init first uses Flags1, Thread and ThreadStack, and the inlined selection code first uses UpdateHeader0 and UpdateHeader1. That gives exactly the target order.

## Trials

1. `seatEntries = (BS2UpdateEntry*)0x80480000 + wadCount`: 549/912 (address folds into `addis`; the swaps stay). Rejected.
2. `static u32 Flags0[...] = {0};` inside BS2SelectUpdateEntries, everything else unchanged: 18/913. All three swaps gone; the 18 left are .bss offsets because Flags0 lands after UpdateHeader1. Init 4 diffs from the same shift.
3. As 2, but the Flags1/Thread/ThreadStack/UpdateHeader0/UpdateHeader1 definitions are tentative (the `= {0}` initializers dropped) and BS2SelectUpdateEntries is defined before BS2UpdateInit: **UpdateThread 0/913, all 10 functions exact**. .bss layout identical to the target, pool 55/55 identical.
4. Rename the target symbol `Flags0` to the compiler's local-static name `Flags0$1129` in config/43U/symbols.txt. This is the project convention for function statics (144 `name$N` entries). Report: code 4052/4052, data 10488/10488, every section 100%, functions 10/10.
5. Flip BS2Update to Matching and run the full build: DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d. build.ninja links build/43U/src/src/BS2/BS2Update.o.

No pragma, asm, volatile change, carrier, padding or dummy is added. The source change is: the selection helper moves above BS2UpdateInit, Flags0 becomes its function static, and five `= {0}` initializers are removed.
