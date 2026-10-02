GATE PASS

The final gate rebuilt 43U from a clean build directory. The DOL SHA1 is 26116613f624061ba99c8d1a299aaa6efa85670d. All four pools are identical. Regressions, forbidden patterns, and readability warnings are zero.

| Unit | Instruction-exact before -> after | Objdiff code bytes before -> after | Objdiff data bytes before -> after |
| --- | --- | --- | --- |
| src/keyboard/tiPcKeyboard | 140/141 -> 140/141 | 28064/28484 -> 28064/28484 | 18548/18564 -> 18548/18564 |
| libs/RVL_SDK/src/axfx/AXFXChorusExp | 6/7 -> 7/7 | 2180/2684 -> 2684/2684 | 48/48 -> 48/48 |
| libs/RVL_SDK/src/fa/pdm_partition | 18/20 -> 18/20 | 2276/3716 -> 2276/3716 | 0/0 -> 0/0 |
| libs/RevoEX/src/net/aes | 7/9 -> 7/9 | 1116/2752 -> 1116/2752 | 2800/2800 -> 2800/2800 |

Matched __InitParams, 126/126 instructions and zero ctxdiff differences. The gradient field writer preserves the target floating calculation order. Three named signed conversions and their declaration order give the target integer registers. Nested history loops put the twelve zero stores after the conversions. Code and data for AXFXChorusExp are 100%.

Remaining functions, one line per function:

- setTranslateMode__Q49textinput8keyboard6pctype4BaseFQ59textinput8keyboard6pctype4Base13TranslateMode, 99.04762%, 3 distinct compiled source attempts; best experiment 99.04762%. 106/105 instructions, same 0x20 frame. The extra move gives keyMode a defined value for unsupported enums. The target default branch reads an unwritten saved register. Safe table, parameter, and branch forms did not match.
- pdm_part_is_master_boot_sector, 86.5%, 11 distinct compiled source attempts; best experiment 86.5%. 86/84 instructions; source frame0x40 with three saved GPRs, target0x30 with two. Endian byte-load order and partial-sum lifetimes still differ. Inline readers, compound assignments, and local range aggregates changed the frame but did not match.
- pdm_part_get_start_sector, 82.56159%, 10 distinct compiled source attempts; best experiment 84.884056%. 276/276 instructions and aligned0x2e0 frame. Unrolled primary and extended word byte loads, endian grouping and scalar lifetimes still differ. Named halves, field writers and loop forms did not match.
- AESiEncryptBlock, 60.348103%, 11 distinct compiled source attempts; best experiment 60.8038%. 158/158 instructions and frame0x40. State setup, lookup indices, table loads, rotations and XOR operand order still differ. Named byte terms and inline value/output helpers did not match.
- AESiDecryptBlock, 61.49004%, 6 distinct compiled source attempts; best experiment 65.30677%. 249/251 instructions and frame0x40. Key-base setup, inverse-mix loop addressing, and round lookup scheduling still differ. Typed schedule views and native inverse-mix chains reached251/251 without an exact match.

Changed files and commits:

- libs/RVL_SDK/src/axfx/AXFXChorusExp.c, 4bf4bad3, match chorus parameter initialization.
- tools/decomp-assist/sol-high-round2-oct2.attempts.jsonl records the function checks, source variations, measurements, and final attempt audit.
- tools/decomp-assist/sol-high-round2-oct2.exact-ctxdiff.txt contains the new exact function diff.
- tools/decomp-assist/sol-high-round2-oct2.final-gate.txt contains the full clean gate over all four units.
- tools/decomp-assist/sol-high-round2-oct2.report.md is this report.

Uncertainty: tiPcKeyboard has 16 unscored .bss bytes. Objdiff reports no match percentage for them. Data remains18548/18564. PDM has no data sections; the gate prints None/None and the table represents that as0/0. All unsuccessful source experiments were restored.

Final full gate unit lines copied verbatim:

```
[src/keyboard/tiPcKeyboard] objdiff: code 28064/28484 data 18548/18564 functions 140/141 fuzzy 99.9860 linked code 0
[src/keyboard/tiPcKeyboard] instruction-exact functions: 140/141
[libs/RVL_SDK/src/axfx/AXFXChorusExp] objdiff: code 2684/2684 data 48/48 functions 7/7 fuzzy 100.0000 linked code 0
[libs/RVL_SDK/src/axfx/AXFXChorusExp] instruction-exact functions: 7/7
[libs/RVL_SDK/src/fa/pdm_partition] objdiff: code 2276/3716 data None/None functions 18/20 fuzzy 93.5985 linked code 0
[libs/RVL_SDK/src/fa/pdm_partition] instruction-exact functions: 18/20
[libs/RevoEX/src/net/aes] objdiff: code 1116/2752 data 2800/2800 functions 7/9 fuzzy 76.8445 linked code 0
[libs/RevoEX/src/net/aes] instruction-exact functions: 7/9
GATE PASS
```
