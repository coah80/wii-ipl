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


# Continuation from e81a2616

## KBDTranslateHidCode

1. signed table mask follows cmpwi and addis comparison blocks: 92.92683%; `src 0x298 base 0x290 insns 166/164; --- replace mine 44:46 base 44:46`.
2. single bit conditions and signed combined modifier comparisons: 95.97561%; `src 0x290 base 0x290 insns 164/164; diffs 44: [44, 45, 49, 50, 57, 58, 62, 63, 67, 68, 70, 71, 72, 74, 76, 78, 80, 81, 83, 86]`.
3. shift flag assignment and group offset parenthesized final sum: 96.03658%; `src 0x290 base 0x290 insns 164/164; diffs 42: [44, 45, 46, 49, 50, 57, 62, 67, 70, 72, 74, 76, 78, 79, 80, 81, 83, 86, 88, 89]`.
4. reuse shift as offset through all mask branches with num lock result temp: 99.32927%; `src 0x290 base 0x290 insns 164/164; diffs 16: [44, 45, 46, 58, 63, 68, 71, 79, 80, 81, 83, 88, 91, 102, 159, 160]`.
5. separate narrowed active flag from live shifted flag: 99.481705%; `src 0x290 base 0x290 insns 164/164; diffs 11: [44, 45, 46, 79, 81, 83, 88, 91, 102, 159, 160]`.
6. signed offset and unsigned group for final table address: 96.92073%; `src 0x290 base 0x290 insns 164/164; diffs 18: [44, 45, 46, 79, 81, 83, 88, 91, 102, 104, 112, 120, 128, 136, 144, 152, 159, 160]`.
7. signed offset and signed group preserve inner final addition: 99.63415%; `src 0x290 base 0x290 insns 164/164; diffs 9: [44, 45, 46, 79, 81, 83, 88, 91, 102]`.
8. word entry with signed offset and group: 99.63415%; `src 0x290 base 0x290 insns 164/164; diffs 9: [44, 45, 46, 79, 81, 83, 88, 91, 102]`.
9. word active flag explicitly narrowed at assignment: 99.63415%; `src 0x290 base 0x290 insns 164/164; diffs 9: [44, 45, 46, 79, 81, 83, 88, 91, 102]`.

## kbdProcKey

1. derive getter destination from existing channel state before checked getter: 94.50581%; `src 0x2b4 base 0x2b0 insns 173/172; --- insert mine 5:5 base 5:7`.
2. initialize complete event aggregate before getter and field stores: 95.75581%; `src 0x2c0 base 0x2b0 insns 176/172; --- delete mine 5:6 base 5:5`.
3. stop processing on failed checked modifier getter: 94.09884%; `src 0x2d4 base 0x2b0 insns 181/172; --- replace mine 6:9 base 6:9`.

## kbdProcMod

1. derive whole word counter masks from neg or rlwimi target blocks: 75.97656%; `src 0x3c0 base 0x400 insns 240/256; --- replace mine 2:3 base 2:3`.
2. whole word counter masks from boolean nonzero count: 75.97656%; `src 0x3c0 base 0x400 insns 240/256; --- replace mine 2:3 base 2:3`.
3. pointer view for initialized modifier word across switch cases: 78.57422%; `src 0x3a4 base 0x400 insns 233/256; --- replace mine 2:3 base 2:3`.

## KBDSetModState

1. C89 channel table declaration before interrupt disable: 98.690475%; `src 0xa8 base 0xa8 insns 42/42; diffs 7: [26, 27, 29, 30, 31, 32, 33]`.
2. C89 channel record declaration before interrupt disable: 98.690475%; `src 0xa8 base 0xa8 insns 42/42; diffs 7: [26, 27, 29, 30, 31, 32, 33]`.
3. name channel table before modifier field view: build rejected (#   Error:         ^^^^^^^^^^).
4. load old state before masking incoming state: 98.690475%; `src 0xa8 base 0xa8 insns 42/42; diffs 7: [26, 27, 29, 30, 31, 32, 33]`.
5. use channel record view for old state and store: build rejected (#   Error:         ^^^^^^^^^^).

## kbdEventHandler

1. range classification uses report status byte local: 99.83871%; `src 0x2e8 base 0x2e8 insns 186/186; diffs 5: [35, 36, 38, 39, 42]`.
2. selected channel pointer with reversed addition operands: 99.78494%; `src 0x2e8 base 0x2e8 insns 186/186; diffs 6: [35, 36, 37, 38, 39, 42]`.
3. load word report status before channel base address: 99.83871%; `src 0x2e8 base 0x2e8 insns 186/186; diffs 5: [35, 36, 38, 39, 42]`.

## kbd_led_handler

1. derive callback positive guard as target trailing return block: 70.0%; `src 0x60 base 0x64 insns 24/25; --- replace mine 2:4 base 2:4`.
2. positive callback guard with explicit success and error blocks: 39.36%; `src 0x58 base 0x64 insns 22/25; --- replace mine 2:4 base 2:4`.
3. retain typed callback value after command release: 69.6%; `src 0x60 base 0x64 insns 24/25; --- insert mine 0:0 base 0:1`.

## KBDSetLedsAsync

1. inline flag lookup and default-first result switch: 83.80247%; `src 0x13c base 0x144 insns 79/81; --- replace mine 7:9 base 7:9`.
2. scoped flag local read through inline accessor and default-first result switch: 83.80247%; `src 0x13c base 0x144 insns 79/81; --- replace mine 7:9 base 7:9`.
3. scoped flag local; async LED and index declaration order reversed (synchronous source repeated): 83.55556%; `src 0x13c base 0x144 insns 79/81; --- replace mine 7:9 base 7:9`.
4. narrow channel only at flag reads and case-zero-first result switch: 90.69136%; `src 0x150 base 0x144 insns 84/81; --- replace mine 14:15 base 14:15`.
5. narrow channel only at device reads and case-zero-first result switch: 85.06173%; `src 0x154 base 0x144 insns 85/81; --- replace mine 14:15 base 14:15`.
6. while command reservation loop and case-zero-first result switch: 82.48148%; `src 0x140 base 0x144 insns 80/81; --- replace mine 7:9 base 7:9`.

## KBDSetLeds

1. inline flag lookup and default-first result switch: 79.77215%; `src 0x138 base 0x13c insns 78/79; --- replace mine 4:5 base 4:5`.
2. scoped flag local read through inline accessor and default-first result switch: 79.77215%; `src 0x138 base 0x13c insns 78/79; --- replace mine 4:5 base 4:5`.
3. scoped flag local; async LED and index declaration order reversed (synchronous source repeated): 79.77215%; `src 0x138 base 0x13c insns 78/79; --- replace mine 4:5 base 4:5`.
4. narrow channel only at flag reads and case-zero-first result switch: 78.05064%; `src 0x14c base 0x13c insns 83/79; --- replace mine 4:5 base 4:5`.
5. narrow channel only at device reads and case-zero-first result switch: 75.94936%; `src 0x150 base 0x13c insns 84/79; --- replace mine 4:5 base 4:5`.
6. while command reservation loop and case-zero-first result switch: 78.48101%; `src 0x13c base 0x13c insns 79/79; diffs 39: [4, 16, 19, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43]`.

Target blocks were re-derived from kbd_lib.s: LED checks precede interrupt exclusion; twelve command slots are probed and reserved while interrupts are disabled; the device is queried again for transfer; completion releases the marker before invoking the callback. The translation routine carries the shift bit as the final table offset, keeps the active entry mask separate, and computes group plus offset before the key index.
kbdProcKey retains initialization of the getter destination. kbdProcMod retains initialization from channel state. The original getter may skip its output on invalid input; matching its missing initialization would introduce uninitialized reads and was rejected. Modifier counter cases were re-derived as separate counter, whole-word mask, and lock-toggle blocks.
Data: .bss, .sbss and .sdata remain exact; the real map, command, channel, and callback workspaces retain original order. The first 0x490 data bytes, including the SDK version literal and both maps, match raw target bytes. The remaining .data differences are the compiler-generated switch table; the version text has an anonymous source symbol and a target lbl symbol, which is not recreated. No packed pool, manual jump table, address pins or section directives were introduced.
KBDResetChannel remains objdiff 100% with identical raw instruction bytes. Its gate count discrepancy remains the documented CR1 branch-disassembly normalization issue; no tooling was modified.
