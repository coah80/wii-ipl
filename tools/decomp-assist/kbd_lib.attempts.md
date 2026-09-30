# kbd_lib attempts

All 21 functions implemented in object order. Shared headers unchanged.
All modifier destinations are initialized; no volatile or register declarations were added.
Pools identical. Command reservation preserves the device marker until completion.

## kbdEventHandler
1. Compound search and unsigned report loops.
2. Byte channel search and for/break key scans.
3. Signed scan indices and byte mask.
4. Status reload after alarm; branch inversion; word mask.
Measured waves 1-6, objdiff percent: 63.822582, 65.145164, 73.053764, 73.268814, 98.81183, 99.10215.
Instruction diffs retained in /tmp/sol-low-kbd-final-ctx.txt.

## kbdProcKey
1. Range predicate; mapped byte local; repeat loop.
2. Explicit modifier keys; signed map loop; initialized getter destination.
3. Getter result handling with preloaded destination.
Measured waves 1-6, objdiff percent: 52.11628, 62.15116, 62.15116, 97.5, 97.5, 89.91279.
Instruction diffs retained in /tmp/sol-low-kbd-final-ctx.txt.

## kbdProcMod
1. Ascending cases and delta counters.
2. Object-order cases; getter/setter calls; unsigned count fields.
3. Boolean count expressions instead of word-sign masks.
Measured waves 1-6, objdiff percent: 29.371094, 29.371094, 27.867188, 81.50391, 81.50391, 75.78125.
Instruction diffs retained in /tmp/sol-low-kbd-final-ctx.txt.

## kbd_led_handler
1. Ternary result and callback pointer.
2. Switch result and numeric callback table.
3. Inverted if/else result.
Measured waves 1-6, objdiff percent: 22.16, 22.16, 70.0, 70.0, 70.0, 43.76.
Instruction diffs retained in /tmp/sol-low-kbd-final-ctx.txt.

## KBDSetLedsAsync
1. Compound free-command scan.
2. For/break scan and device reservation.
3. Guard returns, delayed channel lookup and explicit result checks.
Measured waves 1-6, objdiff percent: 60.4321, 60.4321, 60.444443, 66.03704, 66.03704, 73.02469.
Instruction diffs retained in /tmp/sol-low-kbd-final-ctx.txt.

## KBDSetLeds
1. Compound free-command scan.
2. For/break scan and device reservation.
3. Guard returns, delayed channel lookup and explicit result checks.
Measured waves 1-6, objdiff percent: 48.49367, 48.49367, 48.49367, 61.481014, 61.481014, 70.91139.
Instruction diffs retained in /tmp/sol-low-kbd-final-ctx.txt.

## KBDSetModState
1. Negative flag branch; direct scalar masks.
2. Positive flag branch; named masked value.
3. Bitfield state copy through a field pointer.
Measured waves 1-6, objdiff percent: 50.690475, 94.04762, 94.04762, 94.04762, 94.04762, 98.690475.
Instruction diffs retained in /tmp/sol-low-kbd-final-ctx.txt.

## KBDTranslateHidCode
1. Unsigned groups and final stateIndex.
2. Signed group and separate table selection.
3. Word mask, byte cast within each table branch.
Measured waves 1-6, objdiff percent: 79.152435, 79.152435, 82.54878, 82.54878, 82.54878, 86.29878.
Instruction diffs retained in /tmp/sol-low-kbd-final-ctx.txt.

## Final gate discrepancy
KBDResetChannel has objdiff 100.0% and identical 176-byte instruction contents.
The gate reports 12/21 instead of 13/21 because odiff.dis treats the first CR1 conditional-branch operand as an immediate and subtracts the different symbol offsets. Both disputed branch instruction words are identical. Tools were left unchanged.
