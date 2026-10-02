GATE PASS

Final full gate over all four units passed a clean 43U rebuild, the DOL hash, zero regressions, zero forbidden patterns, and zero readability warnings. All four pools are identical. The four new matches and the existing updateInput caller have zero ctxdiff differences.

| Unit | Instruction-exact before -> after | Objdiff code bytes before -> after | Objdiff data bytes before -> after |
| --- | --- | --- | --- |
| src/keyboard/tiPcKeyboard | 138/141 -> 140/141 | 27712/28484 -> 28064/28484 | 18548/18564 -> 18548/18564 |
| libs/RVL_SDK/src/fa/pdm_partition | 18/20 -> 18/20 | 2276/3716 -> 2276/3716 | 0/0 -> 0/0 |
| libs/RVL_SDK/src/axfx/AXFXChorusExp | 5/7 -> 6/7 | 1920/2684 -> 2180/2684 | 48/48 -> 48/48 |
| libs/RevoEX/src/net/aes | 6/9 -> 7/9 | 684/2752 -> 1116/2752 | 2800/2800 -> 2800/2800 |

Remaining functions, with current objdiff scores and distinct compiled attempts:

- `setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode`, 99.04762%, 3 attempts, best experiment 98.09524%. Source 106/target 105 instructions. Sole extra move initializes keyMode for invalid enums; target reads an undefined saved register for that case. Defined switch variants were restored.
- `pdm_part_is_master_boot_sector`, 86.5%, 60 attempts, best experiment 88.86905%. Source 86/target 84 instructions. Source frame 0x40 saves three GPRs; target frame 0x30 saves two. Endian byte loads and pointer/index allocation differ. Best structural variants still have 14 structural differences.
- `pdm_part_get_start_sector`, 82.56159%, 6 attempts, best experiment 84.76087%. Both 276 instructions with aligned 0x2e0 frame. Primary/extended partition word byte grouping, operand evaluation order, and scalar lifetimes differ. Loop and inline-boundary variants did not match.
- `__InitParams`, 69.9127%, 6 attempts, best experiment 97.81746%. Both 126 instructions and 0x30 frame. Explicit history stores schedule before conversions, and comparison/gradient scheduling differs. History-loop and period variants reached 97.81746% but retained 16 positional differences.
- `AESiEncryptBlock`, 60.348103%, 6 attempts, best experiment 64.99367%. Both 158 instructions and 0x40 frame. State setup, table lookup/rotation scheduling, and XOR temporary lifetimes differ. Structural and declaration variants remained non-exact.
- `AESiDecryptBlock`, 61.49004%, 3 attempts, best experiment 65.09164%. Source 249/target 251 instructions with 0x40 frame. Initial key base, inverse-mix XOR dependencies, round indexing, and table state lifetimes differ. Closest key-base variant had 251 instructions but remained non-exact.

Changed source and local commits:

- [src/keyboard/tiPcKeyboard.cpp](/mnt/drive2/projects/wii-ipl-workers/sol-high/src/keyboard/tiPcKeyboard.cpp:2114), `bab40302` and `2dae31dd`. Pressed/released modifier update lifetimes match; updateInput preserves its existing exact code.
- [libs/RVL_SDK/src/axfx/AXFXChorusExp.c](/mnt/drive2/projects/wii-ipl-workers/sol-high/libs/RVL_SDK/src/axfx/AXFXChorusExp.c:200), `6feffd9d`. Native signed64 LFO products, fixed sample traversal, and local declaration order match.
- [libs/RevoEX/src/net/aes.c](/mnt/drive2/projects/wii-ipl-workers/sol-high/libs/RevoEX/src/net/aes.c:236), `af77141a`. Byte-to-bit round calculation and named substitution byte terms match.
- `tools/decomp-assist/sol-high-structural-oct2.attempts.jsonl`, `tools/decomp-assist/sol-high-structural-oct2.final-gate.txt`, and this report contain the attempt and validation evidence.

Uncertainty: tiPcKeyboard retains 16 unscored .bss data bytes. Objdiff gives that section no match percentage. No linking/configuration changes were made.

Final gate unit lines copied verbatim:

```
[src/keyboard/tiPcKeyboard] objdiff: code 28064/28484 data 18548/18564 functions 140/141 fuzzy 99.9860 linked code 0
[src/keyboard/tiPcKeyboard] instruction-exact functions: 140/141
[libs/RVL_SDK/src/fa/pdm_partition] objdiff: code 2276/3716 data None/None functions 18/20 fuzzy 93.5985 linked code 0
[libs/RVL_SDK/src/fa/pdm_partition] instruction-exact functions: 18/20
[libs/RVL_SDK/src/axfx/AXFXChorusExp] objdiff: code 2180/2684 data 48/48 functions 6/7 fuzzy 94.3502 linked code 0
[libs/RVL_SDK/src/axfx/AXFXChorusExp] instruction-exact functions: 6/7
[libs/RevoEX/src/net/aes] objdiff: code 1116/2752 data 2800/2800 functions 7/9 fuzzy 76.8445 linked code 0
[libs/RevoEX/src/net/aes] instruction-exact functions: 7/9
GATE PASS
```
