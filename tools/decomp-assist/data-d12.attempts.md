# Data lane d12

Baseline HEAD and fetched origin/main: 9702056b. Owned sources and symbols unchanged on origin/main. Initial quick full gate PASS, zero regressions, DOL SHA1 26116613f624061ba99c8d1a299aaa6efa85670d.

| Unit | Exact functions | Code bytes | Data bytes |
| --- | --- | --- | --- |
| src/keyboard/tiHwKeyboard | 10/10 | 4596/4596 | 472/504 |
| libs/RevoEX/src/net/sha1 | 5/5 | 1496/1496 | 16/48 |
| libs/RevoEX/src/net/nettime | 1/1 | 228/228 | 0/8 |

All three pool_diff checks are identical, zero strings. No non-exact functions exist; code experiments are unnecessary for this data assignment.

## tiHwKeyboard

- .bss extent/name mismatch: target lbl_810C8940 has 16 bytes, source @6371 has 12; init .text+0x5a/0x66 and updateShift +0x102/0x10e pass its address as r5 to __register_global_object for LayoutGather singleton. Runtime NMWException.h defines DestructorChain as three 32-bit pointers, hence 12 bytes; trailing four bytes are alignment. Rename to compiler-emitted @6371 and set size 12, preserving section range and bytes.
- .sdata2 extent mismatch: target lbl_81694F00 has four bytes but source @6555 has eight, both contain command 8 followed by zero. updateTriggerKey .text+0x8d8 and source +0x9a0 load the first word for NavigationCommand {u32 command, u32 modifiers}; sizeof is 8, and dynamic modifiers overwrite the second initializer word. Correct extent to eight within existing section, retaining address and all bytes.
- .rodata/.data/.sdata already 100%; no renames needed for automatically paired anonymous symbols or controlKeys. Additional weak singleton storage is linker-deduplicated and ignored.

## sha1

- .rodata extent/name mismatch: NETGetSHA1Interface target .text+0x232/+0x236 and source same offsets load sha1template$2339/interface$143; its data relocations +0x10/+0x14/+0x18 point to NETSHA1Init/NETSHA1Update/NETSHA1GetDigest. DigestInterface contains four u32 fields and three function pointers, sizeof 28; target extent 32 absorbed four trailing alignment bytes. Rename to interface$143 and set size 28, preserving address, section range and bytes.
- .sbss2/.sdata2 already 100%; padlead$2309/endMarker$120 and padalign$2310/zeroBytes$121 are automatically paired by matching code references and need no renames.

## nettime

- .sbss split/name mismatch: target .text+0xc/+0x38/+0x78 uses lbl_81698DB0, +0x18/+0x2c/+0x74 uses lbl_81698DB4; source relocations at identical offsets use whenCached$1061 with addends 0 and 4 respectively. The two words hold the s64 __OSGetSystemTime return in r3:r4 and are compared/added as one s64. Combine into the real eight-byte whenCached$1061 at unchanged 0x81698DB0; remove artificial second-word symbol at 0x81698DB4, preserving section range and bytes.

## Verification after corrections

Quick gate PASS: tiHwKeyboard data 504/504, sha1 data 48/48, nettime data 8/8. All owned non-text sections report 100%; exact functions remain 10/10, 5/5, 1/1. Code bytes remain 4596/4596, 1496/1496, 228/228. Zero global regressions, forbidden patterns, or readability warnings. Only symbol metadata changed; no source edits or split edits.

## Final clean full gate

Command: `python3 /mnt/drive2/projects/wii-ipl-workers/_restore0928-tools/gate.py src/keyboard/tiHwKeyboard libs/RevoEX/src/net/sha1 libs/RevoEX/src/net/nettime`

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/keyboard/tiHwKeyboard] pool: IDENTICAL
[src/keyboard/tiHwKeyboard] objdiff: code 4596/4596 data 504/504 functions 10/10 fuzzy 100.0000 linked code 4596
[src/keyboard/tiHwKeyboard] instruction-exact functions: 10/10
[src/keyboard/tiHwKeyboard]   section .bss size 16 match 100.0
[src/keyboard/tiHwKeyboard]   section .data size 288 match 100.0
[src/keyboard/tiHwKeyboard]   section .rodata size 176 match 100.0
[src/keyboard/tiHwKeyboard]   section .sdata size 8 match 100.0
[src/keyboard/tiHwKeyboard]   section .sdata2 size 16 match 100.0
[src/keyboard/tiHwKeyboard]   section .text size 4596 match 100.0
[src/keyboard/tiHwKeyboard] baseline: code 4596/4596 data 472 functions 10 fuzzy 100.0000
[libs/RevoEX/src/net/sha1] pool: IDENTICAL
[libs/RevoEX/src/net/sha1] objdiff: code 1496/1496 data 48/48 functions 5/5 fuzzy 100.0000 linked code 1496
[libs/RevoEX/src/net/sha1] instruction-exact functions: 5/5
[libs/RevoEX/src/net/sha1]   section .rodata size 32 match 100.0
[libs/RevoEX/src/net/sha1]   section .sbss2 size 8 match 100.0
[libs/RevoEX/src/net/sha1]   section .sdata2 size 8 match 100.0
[libs/RevoEX/src/net/sha1]   section .text size 1496 match 100.0
[libs/RevoEX/src/net/sha1] baseline: code 1496/1496 data 16 functions 5 fuzzy 100.0000
[libs/RevoEX/src/net/nettime] pool: IDENTICAL
[libs/RevoEX/src/net/nettime] objdiff: code 228/228 data 8/8 functions 1/1 fuzzy 100.0000 linked code 228
[libs/RevoEX/src/net/nettime] instruction-exact functions: 1/1
[libs/RevoEX/src/net/nettime]   section .sbss size 8 match 100.0
[libs/RevoEX/src/net/nettime]   section .text size 228 match 100.0
[libs/RevoEX/src/net/nettime] baseline: code 228/228 data None functions 1 fuzzy 100.0000
regressions vs baseline: 0
global matched_code_percent: 88.57407 -> 88.57407
global fuzzy_match_percent: 99.45531 -> 99.45531
global complete_code_percent: 63.07103 -> 63.07103
global matched_data_percent: 97.78074 -> 97.78467
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
note: config touched: config/43U/symbols.txt (orchestrator reviews every config/symbols change)
GATE PASS
```

All target sections retain their original sizes and bytes. splits.txt unchanged. Every owned symbol remains within its assigned split; only proven object extents and names changed. The two nettime word labels were consolidated into the s64 object rather than dropping data.

## Fresh pool and instruction checks after clean build

```text
src/keyboard/tiHwKeyboard: POOL IDENTICAL up to 0 (mine=0 base=0)
__ct__Q49textinput8keyboard5hwkey10HWKeyboardFPQ29textinput7Manager: src 0x28 base 0x28 insns 10/10; diffs 0: []
init__Q49textinput8keyboard5hwkey10HWKeyboardFv: src 0xa0 base 0xa0 insns 40/40; diffs 0: []
updateShift__Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager: src 0x184 base 0x184 insns 97/97; diffs 0: []
updateInput__Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager: src 0x1e8 base 0x1e8 insns 122/122; diffs 0: []
updateRepeatKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager: src 0x2d0 base 0x2d0 insns 180/180; diffs 0: []
updateTriggerKey___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager: src 0x654 base 0x654 insns 405/405; diffs 0: []
updateTappingShift___Q49textinput8keyboard5hwkey10HWKeyboardFRQ39textinput5input10HKBManager: src 0x244 base 0x244 insns 145/145; diffs 0: []
updateInput__Q49textinput8keyboard5hwkey10HWKeyboardFiffUlUlUlPv: src 0x14 base 0x14 insns 5/5; diffs 0: []
convertWCCode__Q49textinput8keyboard5hwkey10HWKeyboardCFw: src 0x20c base 0x20c insns 131/131; diffs 0: []
setLanguage__Q49textinput8keyboard5hwkey10HWKeyboardFQ29textinput11DestinationQ29textinput8Language: src 0x38 base 0x38 insns 14/14; diffs 0: []
libs/RevoEX/src/net/sha1: POOL IDENTICAL up to 0 (mine=0 base=0)
NETSHA1Init: src 0x50 base 0x50 insns 20/20; diffs 0: []
NETSHA1Update: src 0xb4 base 0xb4 insns 45/45; diffs 0: []
NETSHA1GetDigest: src 0x12c base 0x12c insns 75/75; diffs 0: []
NETGetSHA1Interface: src 0xc base 0xc insns 3/3; diffs 0: []
NETSHA1iProcessBlock: src 0x39c base 0x39c insns 231/231; diffs 0: []
libs/RevoEX/src/net/nettime: POOL IDENTICAL up to 0 (mine=0 base=0)
NETGetUniversalCalendar: src 0xe4 base 0xe4 insns 57/57; diffs 0: []
```

Open-function audit: none in any assigned unit. All sixteen functions were already instruction-exact before this data lane and remain exact. No source experiments, new code, or changes to configure.py were needed. All owned non-text sections reach 100% and matched_data equals total_data in each unit. No unresolved uncertainty.
