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

# Continuation from eaee2295

## kbdEventHandler
1. Use the word mask directly for both report bytes: 99.72043%; src 0x2e8 base 0x2e8 insns 186/186
2. Initialize loop mask before the loop, retain byte conversion: 99.166664%; src 0x2ec base 0x2e8 insns 187/186
3. Use report-status byte local for error classification: 98.63441%; src 0x2e8 base 0x2e8 insns 186/186
4. Set mask before index in the word-mask loop initializer: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
5. Calculate report status before looking up channel data: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
6. Declare bytes before channel data and use a channel pointer expression: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
7. Use an unsigned report-status word only for the range check: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
8. Perform error classification before forming the channel pointer: 92.150536%; src 0x2f8 base 0x2e8 insns 190/186
9. Form channel pointer with a byte-sized channel index: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
10. Typed HID report fields, variation 1: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
11. Typed HID report fields, variation 2: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
12. Typed HID report fields, variation 3: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
13. Separate channel-array base and channel selection: 99.83871%; src 0x2e8 base 0x2e8 insns 186/186
14. Keep a typed channel-array local through channel lookup: 98.81721%; src 0x2e0 base 0x2e8 insns 184/186
15. Use the report word status minus one as signed arithmetic before narrowing: 99.752686%; src 0x2e8 base 0x2e8 insns 186/186
16. Declare and initialize channel record at the top of the found-channel block: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
17. Express channel selection with the index as the left operand: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
18. Declare a separate channel-array base for the selected record: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186
19. Load report state before final channel selection and use a word local: 99.78494%; src 0x2e8 base 0x2e8 insns 186/186

## KBDSetModState
1. Merge physical bits using a scalar mask instead of bitfields: 98.690475%; src 0xa8 base 0xa8 insns 42/42
2. Compute channel pointer before disabling interrupts: 86.54762%; src 0xa4 base 0xa8 insns 41/42
3. Use an initialized modifier union and write both fields: 93.21429%; src 0xb0 base 0xa8 insns 44/42

## kbdProcKey
1. Initialize getter destination with the known channel modifier state: 94.50581%; src 0x2b4 base 0x2b0 insns 173/172
2. Initialize event fields as one aggregate before channel lookup: build rejected (ninja: build stopped: subcommand failed.).
3. Read modifiers directly after validating the known channel: 87.6686%; src 0x294 base 0x2b0 insns 165/172
4. Initialize a separate modifier destination then copy to the event: 94.50581%; src 0x2bc base 0x2b0 insns 175/172
5. Zero-initialize the entire event before filling fields: 95.75581%; src 0x2c0 base 0x2b0 insns 176/172
6. Check getter status explicitly and initialize on failure: 92.93604%; src 0x2dc base 0x2b0 insns 183/172

## kbd_led_handler
1. Use a typed callback record and clear command first: 48.16%; src 0x54 base 0x64 insns 21/25
2. Return mapped result through if/else instead of switch: 39.36%; src 0x58 base 0x64 insns 22/25
3. Reload callback at the call and compare against numeric zero: 62.2%; src 0x58 base 0x64 insns 22/25

## KBDSetLedsAsync
1. Keep narrowed LED bits in a separate byte: 79.5679%; src 0x138 base 0x144 insns 78/81
2. Scan commands by index and test success before failure: 73.38271%; src 0x13c base 0x144 insns 79/81
3. Use a command-record pointer during reservation: 74.80247%; src 0x134 base 0x144 insns 77/81
4. Explicitly zero-initialize keyboard map and command records: 79.604935%; src 0x138 base 0x144 insns 78/81
5. Explicitly zero-initialize all real keyboard workspaces: 79.604935%; src 0x138 base 0x144 insns 78/81
6. Explicitly zero-initialize the typed per-channel state: 79.5679%; src 0x138 base 0x144 insns 78/81

## KBDSetLeds
1. Keep narrowed LED bits in a separate byte: 72.620255%; src 0x134 base 0x13c insns 77/79
2. Scan commands by index and test success before failure: 73.177216%; src 0x138 base 0x13c insns 78/79
3. Use a command-record pointer during reservation: 72.27848%; src 0x12c base 0x13c insns 75/79

## kbdProcMod
1. Use unsigned byte counts and logical nonzero masks: 75.78125%; src 0x3c0 base 0x400 insns 240/256
2. Use an initialized modifier union for the switch updates: 75.78125%; src 0x3c0 base 0x400 insns 240/256
3. Initialize from channel state and use word-sized count delta: 75.97656%; src 0x3c0 base 0x400 insns 240/256
4. Update named physical modifier bitfields: 78.90625%; src 0x3a0 base 0x400 insns 232/256

## KBDTranslateHidCode
1. Prioritize alt, lock and shift groups in a flat decision chain: 91.70731%; src 0x290 base 0x290 insns 164/164
2. Keep entry mask and group indices signed: 89.597565%; src 0x290 base 0x290 insns 164/164
3. Separate character offset calculation from table indexing: 86.29878%; src 0x284 base 0x290 insns 161/164

## Data and workspace checks
Named mutable SDK version text: matched data 3992/5296. Rejected; no improvement or data regression.
Named constant SDK version text: matched data 3984/5296. Rejected; no improvement or data regression.
Place SDK version declaration after the region tables: matched data 3984/5296. Rejected; no improvement or data regression.
Explicit zero-initialization of real map and command workspaces reproduces target BSS order: key maps 0x000, command records 0x400, channel state 0x580, callback records 0xf20. No extra objects or placement directives.
Using the existing SDK command type was also tested and produced identical function scores; the original private declaration was restored.
No new instruction-exact functions yet; retained source experiments remain uncommitted pending an exact-function gain.
