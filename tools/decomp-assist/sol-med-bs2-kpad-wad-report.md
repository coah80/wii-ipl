# BS2, KPAD, and WAD final matching report

Baseline: 94e6d862. Final full gate rebuilt all 43U objects from scratch. Matching only; configuration and link status were unchanged.

| Unit | Instruction exact before -> after | Code bytes before -> after | Data bytes before -> after | Fuzzy before -> after |
| --- | --- | --- | --- | --- |
| src/BS2/BS2Mach | 21 -> 21/29 | 4052 -> 4052/16980 | 155504 -> 155504/158528 | 83.72297 -> 84.64641 |
| libs/RVL_SDK/src/kpad/KPAD | 13 -> 14/29 | 2020 -> 2404/13056 | 7712 -> 7712/8032 | 82.43720 -> 84.08670 |
| src/BS2/BS2Update | 8 -> 8/10 | 112 -> 112/4052 | 0 -> 0/10488 | 84.19941 -> 84.61500 |
| libs/RVL_SDK/src/wad/wad | 23 -> 23/40 | 7080 -> 7080/24500 | 64 -> 64/528 | 85.70367 -> 87.00555 |

## New exact function

```text
libs/RVL_SDK/src/kpad/KPAD: get_ring_buffer_by_kpad1_style
src 0x180 base 0x180 insns 96/96
diffs 0: []

```

## Remaining functions

| Unit | Function | Objdiff | Compiling attempts | Remaining evidence |
| --- | --- | --- | --- | --- |
| src/BS2/BS2Mach | Run | 0.88372% | 3 | original register and stack reset cannot be expressed by this C call; instruction/block structure remains: 30/43 instructions |
| src/BS2/BS2Mach | BS2StartGame | 95.49618% | 3 | completion reload and time-multiply scheduling; empty-poll candidate rejected; instruction/block structure remains: 401/393 instructions |
| src/BS2/BS2Mach | BS2StartGCGame | 98.24561% | 3 | completion reload and startup sequencing; instruction/block structure remains: 227/228 instructions |
| src/BS2/BS2Mach | BS2NANDDivideCallback | 85.03906% | 3 | IPA eliminates target global reloads around empty report calls; instruction/block structure remains: 119/128 instructions |
| src/BS2/BS2Mach | BS2NANDDivideReadAsync | 60.31915% | 3 | IPA eliminates target global reloads around empty report calls; instruction/block structure remains: 45/47 instructions |
| src/BS2/BS2Mach | BS2NANDDivideWriteAsync | 60.31915% | 3 | IPA eliminates target global reloads around empty report calls; instruction/block structure remains: 45/47 instructions |
| src/BS2/BS2Mach | CheckBS2CommandStatus | 80.69704% | 3 | instruction/block structure remains: 388/406 instructions |
| src/BS2/BS2Mach | BS2Tick | 76.66908% | 6 | instruction/block structure remains: 1902/1940 instructions |
| libs/RVL_SDK/src/kpad/KPAD | reset_kpad | 69.37607% | 3 | instruction/block structure remains: 126/117 instructions |
| libs/RVL_SDK/src/kpad/KPAD | KPADGetProjectionPos | 96.57895% | 5 | register/operand assignment; 9 differing instructions |
| libs/RVL_SDK/src/kpad/KPAD | KPADSetSensorHeight | 99.23077% | 3 | register/operand assignment; 7 differing instructions |
| libs/RVL_SDK/src/kpad/KPAD | calc_acc_horizon | 96.98020% | 5 | instruction ordering, branch layout or operands; 39 differing instructions |
| libs/RVL_SDK/src/kpad/KPAD | read_kpad_acc | 66.56500% | 4 | instruction ordering, branch layout or operands; 381 differing instructions |
| libs/RVL_SDK/src/kpad/KPAD | select_2obj_first | 76.18033% | 3 | instruction/block structure remains: 125/122 instructions |
| libs/RVL_SDK/src/kpad/KPAD | select_2obj_continue | 89.39130% | 3 | instruction/block structure remains: 139/138 instructions |
| libs/RVL_SDK/src/kpad/KPAD | select_1obj_first | 90.83486% | 3 | instruction ordering, branch layout or operands; 50 differing instructions |
| libs/RVL_SDK/src/kpad/KPAD | select_1obj_continue | 80.18279% | 3 | instruction/block structure remains: 95/93 instructions |
| libs/RVL_SDK/src/kpad/KPAD | calc_dpd_variable | 80.02400% | 3 | instruction/block structure remains: 239/250 instructions |
| libs/RVL_SDK/src/kpad/KPAD | read_kpad_dpd | 73.54317% | 3 | instruction/block structure remains: 281/278 instructions |
| libs/RVL_SDK/src/kpad/KPAD | read_kpad_stick | 97.24683% | 3 | instruction ordering, branch layout or operands; 20 differing instructions |
| libs/RVL_SDK/src/kpad/KPAD | KPADRead | 83.57952% | 3 | instruction/block structure remains: 471/459 instructions |
| libs/RVL_SDK/src/kpad/KPAD | KPADInit | 72.46487% | 3 | instruction/block structure remains: 200/185 instructions |
| libs/RVL_SDK/src/kpad/KPAD | KPADiSamplingCallback | 89.30220% | 3 | instruction ordering, branch layout or operands; 108 differing instructions |
| src/BS2/BS2Update | BS2UpdateInit | 79.87500% | 3 | instruction/block structure remains: 71/72 instructions |
| src/BS2/BS2Update | UpdateThread | 84.51698% | 5 | instruction/block structure remains: 860/913 instructions |
| libs/RVL_SDK/src/wad/wad | WADImportGetBlocks | 83.95637% | 3 | instruction/block structure remains: 265/298 instructions |
| libs/RVL_SDK/src/wad/wad | WAD_815BFFA8 | 97.17742% | 3 | register/operand assignment; 30 differing instructions |
| libs/RVL_SDK/src/wad/wad | WADImportEx | 72.73997% | 3 | instruction/block structure remains: 1131/1146 instructions |
| libs/RVL_SDK/src/wad/wad | WAD_815C1288 | 96.39344% | 3 | register/operand assignment; 34 differing instructions |
| libs/RVL_SDK/src/wad/wad | WADBackupEx | 68.56780% | 3 | instruction/block structure remains: 906/1062 instructions |
| libs/RVL_SDK/src/wad/wad | _WADCheckContents | 96.70588% | 3 | instruction ordering, branch layout or operands; 19 differing instructions |
| libs/RVL_SDK/src/wad/wad | WADOpenStream | 98.89162% | 11 | instruction ordering, branch layout or operands; 30 differing instructions |
| libs/RVL_SDK/src/wad/wad | _WADUnpackBackup | 97.34513% | 3 | instruction ordering, branch layout or operands; 12 differing instructions |
| libs/RVL_SDK/src/wad/wad | _WADGetCidxCount | 95.05000% | 3 | instruction ordering, branch layout or operands; 25 differing instructions |
| libs/RVL_SDK/src/wad/wad | _WADGetCidx | 99.14286% | 4 | instruction ordering, branch layout or operands; 8 differing instructions |
| libs/RVL_SDK/src/wad/wad | _WADBackupGetFiles | 96.22398% | 3 | instruction ordering, branch layout or operands; 89 differing instructions |
| libs/RVL_SDK/src/wad/wad | _WADBackupGetSize | 88.54839% | 3 | instruction/block structure remains: 159/155 instructions |
| libs/RVL_SDK/src/wad/wad | _WADRandPad | 93.78022% | 3 | instruction/block structure remains: 89/91 instructions |
| libs/RVL_SDK/src/wad/wad | WAD_815C43E0 | 97.17742% | 3 | register/operand assignment; 30 differing instructions |
| libs/RVL_SDK/src/wad/wad | _WADHash | 96.08247% | 3 | instruction/block structure remains: 193/194 instructions |
| libs/RVL_SDK/src/wad/wad | WADVerify | 89.21769% | 3 | original contains two dormant cleanup paths; dummy allocations were not introduced; instruction/block structure remains: 135/147 instructions |
| libs/RVL_SDK/src/wad/wad | WADImportDVDExForBS | 89.79088% | 3 | instruction/block structure remains: 260/263 instructions |

## Limits

Three units gained fuzzy accuracy without increasing their instruction-exact counts. The exact-count increase requirement is achieved for KPAD only. The full gate passes; this is partial matching progress. No touched unit is fully matched or linked. KPAD lacks a source .data section: pool_diff was attempted first, and the gate string-pool comparison was used when pool_diff raised KeyError. The final gate verifies every touched pool, all baseline exact functions, zero regressions, the forbidden-pattern scan and the DOL hash.

## Final full gate

```text
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/BS2/BS2Mach] pool: IDENTICAL
[src/BS2/BS2Mach] objdiff: code 4052/16980 data 155504/158528 functions 21/29 fuzzy 84.6464 linked code 0
[src/BS2/BS2Mach] instruction-exact functions: 21/29
[src/BS2/BS2Mach]   section .bss size 155232 match 100.0
[src/BS2/BS2Mach]   section .data size 3024 match None
[src/BS2/BS2Mach]   section .sbss size 240 match 100.0
[src/BS2/BS2Mach]   section .sdata size 32 match 100.0
[src/BS2/BS2Mach]   section .text size 16980 match 84.64641
[src/BS2/BS2Mach]   below 100: Run 0.88372093
[src/BS2/BS2Mach]   below 100: BS2StartGame 95.496185
[src/BS2/BS2Mach]   below 100: BS2StartGCGame 98.24561
[src/BS2/BS2Mach]   below 100: BS2NANDDivideCallback 85.03906
[src/BS2/BS2Mach]   below 100: BS2NANDDivideReadAsync 60.31915
[src/BS2/BS2Mach]   below 100: BS2NANDDivideWriteAsync 60.31915
[src/BS2/BS2Mach]   below 100: CheckBS2CommandStatus 80.697044
[src/BS2/BS2Mach]   below 100: BS2Tick 76.669075
[src/BS2/BS2Mach] baseline: code 4052/16980 data 155504 functions 21 fuzzy 83.7230
[libs/RVL_SDK/src/kpad/KPAD] pool: IDENTICAL
[libs/RVL_SDK/src/kpad/KPAD] objdiff: code 2404/13056 data 7712/8032 functions 14/29 fuzzy 84.0867 linked code 0
[libs/RVL_SDK/src/kpad/KPAD] instruction-exact functions: 14/29
[libs/RVL_SDK/src/kpad/KPAD]   section .bss size 7680 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .data size 88 match None
[libs/RVL_SDK/src/kpad/KPAD]   section .sbss size 32 match 100.0
[libs/RVL_SDK/src/kpad/KPAD]   section .sdata size 112 match 94.545456
[libs/RVL_SDK/src/kpad/KPAD]   section .sdata2 size 120 match 85.71429
[libs/RVL_SDK/src/kpad/KPAD]   section .text size 13056 match 84.0867
[libs/RVL_SDK/src/kpad/KPAD]   below 100: reset_kpad 69.37607
[libs/RVL_SDK/src/kpad/KPAD]   below 100: KPADGetProjectionPos 96.57895
[libs/RVL_SDK/src/kpad/KPAD]   below 100: KPADSetSensorHeight 99.23077
[libs/RVL_SDK/src/kpad/KPAD]   below 100: calc_acc_horizon 96.9802
[libs/RVL_SDK/src/kpad/KPAD]   below 100: read_kpad_acc 66.565
[libs/RVL_SDK/src/kpad/KPAD]   below 100: select_2obj_first 76.18033
[libs/RVL_SDK/src/kpad/KPAD]   below 100: select_2obj_continue 89.391304
[libs/RVL_SDK/src/kpad/KPAD]   below 100: select_1obj_first 90.83486
[libs/RVL_SDK/src/kpad/KPAD]   below 100: select_1obj_continue 80.18279
[libs/RVL_SDK/src/kpad/KPAD]   below 100: calc_dpd_variable 80.024
[libs/RVL_SDK/src/kpad/KPAD]   below 100: read_kpad_dpd 73.54317
[libs/RVL_SDK/src/kpad/KPAD]   below 100: read_kpad_stick 97.24683
[libs/RVL_SDK/src/kpad/KPAD]   below 100: KPADRead 83.57952
[libs/RVL_SDK/src/kpad/KPAD]   below 100: KPADInit 72.46487
[libs/RVL_SDK/src/kpad/KPAD]   below 100: KPADiSamplingCallback 89.3022
[libs/RVL_SDK/src/kpad/KPAD] baseline: code 2020/13056 data 7712 functions 13 fuzzy 82.4372
[src/BS2/BS2Update] pool: IDENTICAL
[src/BS2/BS2Update] objdiff: code 112/4052 data None/10488 functions 8/10 fuzzy 84.6150 linked code 0
[src/BS2/BS2Update] instruction-exact functions: 8/10
[src/BS2/BS2Update]   section .bss size 9056 match 72.9682
[src/BS2/BS2Update]   section .data size 1328 match None
[src/BS2/BS2Update]   section .sbss size 80 match 78.947365
[src/BS2/BS2Update]   section .sdata size 24 match 94.117645
[src/BS2/BS2Update]   section .text size 4052 match 84.615005
[src/BS2/BS2Update]   below 100: BS2UpdateInit 79.875
[src/BS2/BS2Update]   below 100: UpdateThread 84.516975
[src/BS2/BS2Update] baseline: code 112/4052 data None functions 8 fuzzy 84.1994
[libs/RVL_SDK/src/wad/wad] pool: IDENTICAL
[libs/RVL_SDK/src/wad/wad] objdiff: code 7080/24500 data 64/528 functions 23/40 fuzzy 87.0056 linked code 0
[libs/RVL_SDK/src/wad/wad] instruction-exact functions: 23/40
[libs/RVL_SDK/src/wad/wad]   section .data size 464 match 99.34924
[libs/RVL_SDK/src/wad/wad]   section .sdata size 64 match 100.0
[libs/RVL_SDK/src/wad/wad]   section .text size 24500 match 87.005554
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportGetBlocks 83.956375
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815BFFA8 97.17742
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportEx 72.73997
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815C1288 96.39344
[libs/RVL_SDK/src/wad/wad]   below 100: WADBackupEx 68.567795
[libs/RVL_SDK/src/wad/wad]   below 100: _WADCheckContents 96.70588
[libs/RVL_SDK/src/wad/wad]   below 100: WADOpenStream 98.891624
[libs/RVL_SDK/src/wad/wad]   below 100: _WADUnpackBackup 97.34513
[libs/RVL_SDK/src/wad/wad]   below 100: _WADGetCidxCount 95.05
[libs/RVL_SDK/src/wad/wad]   below 100: _WADGetCidx 99.14286
[libs/RVL_SDK/src/wad/wad]   below 100: _WADBackupGetFiles 96.223976
[libs/RVL_SDK/src/wad/wad]   below 100: _WADBackupGetSize 88.548386
[libs/RVL_SDK/src/wad/wad]   below 100: _WADRandPad 93.78022
[libs/RVL_SDK/src/wad/wad]   below 100: WAD_815C43E0 97.17742
[libs/RVL_SDK/src/wad/wad]   below 100: _WADHash 96.08247
[libs/RVL_SDK/src/wad/wad]   below 100: WADVerify 89.21769
[libs/RVL_SDK/src/wad/wad]   below 100: WADImportDVDExForBS 89.79088
[libs/RVL_SDK/src/wad/wad] baseline: code 7080/24500 data 64 functions 23 fuzzy 85.7037
regressions vs baseline: 0
global matched_code_percent: 84.60095 -> 84.61377
global fuzzy_match_percent: 97.98296 -> 98.00660
global complete_code_percent: 58.20100 -> 58.20100
global matched_data_percent: 90.32545 -> 90.32545
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
