# NWC24System matching attempts

Baseline: no source; 0/4 exact functions, 0/808 code, 0/192 data.
The SDK shutdown reference was adapted to this target using its assembly
and object-exported Ghidra output. LED state uses SCIdleModeInfo; IPC
shutdown input/output arrays use required 32-byte alignment. The inline
shutdown request retains its own function-name literal through the IPC macro.
All functions, .data, .sdata, .bss, and .sbss match. Unit remains NonMatching.

## Source attempts

NWC24DoDailyTasks | random value before tick in sampling sum | (99.875, -1) | src 0x140 base 0x140 insns 80/80
NWC24DoDailyTasks | unsigned random value retained in sampling temporary | (100.0, 0) | src 0x140 base 0x140 insns 80/80

No remaining non-matching functions.
