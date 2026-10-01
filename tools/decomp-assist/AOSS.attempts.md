# AOSS continuation attempts

Baseline at 07b3a2b5: instruction-exact 15/21, objdiff exact 16/21, code 6436/16192, data 3896/3928, fuzzy 87.91403%. Quick gate passed. Pool identical; .data 368 bytes matches. Only data mismatch is .sbss (32 bytes, 42.857143%). Work lowest scoring functions first, stack frame and initial blocks first.

- AOSS_Init_old — baseline block and stack audit: 73.34911%; 1494/1584 instructions; frame ('stwu', 'r1, -0x100(r1)')/('clrlwi', 'r11, r1, 0x1b').

- AOSS_81401778 — baseline block and stack audit: 80.168495%; 276/273 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

- AOSS_Init_old — align the network-settings local to 32 bytes as the target frame requires: 69.66288%; 1549/1584 instructions; frame ('clrlwi', 'r11, r1, 0x1b')/('clrlwi', 'r11, r1, 0x1b').

- AOSS_81401778 — derive hello payload after clearing the response buffer: 79.8022%; 276/273 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

- AOSS_81401778 — reuse checksum accumulator throughout the CRC block: compiler rejected the variation.

- AOSS_81401778 — reuse checksum accumulator throughout CRC block with unchanged table name: 79.87546%; 276/273 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

- AOSS_81401778 — decode both permutation indices before updating the schedule fields: 84.83883%; 270/273 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

- AOSS_81401778 — align payload lifetime and share the CRC and checksum accumulator with a scoped table view: compiler rejected the variation.

- AOSS_81401778 — scope CRC table at block entry with shared checksum and aligned payload lifetime: 86.67033%; 270/273 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

- AOSS_81401E80 — write packet XOR directly with key-mask operand first: 97.993195%; 147/147 instructions; frame ('stwu', 'r1, -0x40(r1)')/('stwu', 'r1, -0x40(r1)').

- AOSS_81401E80 — load packet and key-mask bytes separately then XOR into the mask result: 97.993195%; 147/147 instructions; frame ('stwu', 'r1, -0x40(r1)')/('stwu', 'r1, -0x40(r1)').

- AOSS_81401E80 — express the packet byte update as compound XOR without a temporary: 98.23129%; 147/147 instructions; frame ('stwu', 'r1, -0x40(r1)')/('stwu', 'r1, -0x40(r1)').

- AOSS_81401E80 — keep packet XOR temporary full-width until its byte store: 98.605446%; 147/147 instructions; frame ('stwu', 'r1, -0x40(r1)')/('stwu', 'r1, -0x40(r1)').

- AOSS_814013AC — reuse response-record cursor for nested options: 96.18421%; 114/114 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

- AOSS_814013AC — initialize accumulated configuration flags after validating response length: 96.97369%; 114/114 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

- AOSS_814013AC — translate response selection as a conditional while loop: 82.149124%; 115/114 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

- AOSS_81400830 — initialize encrypted input cursor before plaintext output cursor: 97.0405%; 321/321 instructions; frame ('stwu', 'r1, -0x40(r1)')/('stwu', 'r1, -0x40(r1)').

- AOSS_81400830 — scope encrypted payload lifetime to the decryption blocks: 96.361374%; 321/321 instructions; frame ('stwu', 'r1, -0x40(r1)')/('stwu', 'r1, -0x40(r1)').

- AOSS_81400830 — split decrypted byte expression into encrypted-byte and key-byte temporaries: compiler rejected the variation.

- AOSS_81400830 — split byte XOR with temporaries declared at loop-block entry: 97.0405%; 321/321 instructions; frame ('stwu', 'r1, -0x40(r1)')/('stwu', 'r1, -0x40(r1)').

- AOSS_Init_old — translate the six target poll stores as two real socket poll descriptors: 73.00505%; 1496/1584 instructions; frame ('stwu', 'r1, -0x110(r1)')/('clrlwi', 'r11, r1, 0x1b').

- AOSS_Init_old — use signed timeout halfwords and compare the target minus-one sentinel directly: 73.85038%; 1494/1584 instructions; frame ('stwu', 'r1, -0x110(r1)')/('clrlwi', 'r11, r1, 0x1b').

Progress: all five objdiff-open AOSS functions have at least three distinct measured attempts. Retained hello permutation update ordering (80.168495 -> 86.67033%) and two typed poll descriptors with signed timeout sentinels (73.34911 -> 73.85038%). Both quick gates passed with zero regressions. The initializer remains 90 instructions short and has an unaligned frame versus the target aligned frame. Data audit and further block work continue.

- AOSS_814013AC — advance the formal response pointer directly through response and nested options: 95.08772%; 114/114 instructions; frame ('stwu', 'r1, -0x30(r1)')/('stwu', 'r1, -0x30(r1)').

Data audit: .bss: source/target sizes 3496/3496, alignments 8/8, raw section bytes identical. .data: source/target sizes 364/368, alignments 8/8, raw section bytes differ. .sdata2: source/target sizes 8/8, alignments 8/8, raw section bytes identical. .sdata: source/target sizes 24/24, alignments 8/8, raw section bytes identical. .sbss: source/target sizes 32/32, alignments 8/8, raw section bytes identical.
All .sbss globals have the target offsets and sizes (list 0, config 4, name 8/8 bytes, connection 0x10, error 0x14, socketStarted 0x18, response 0x1c). Raw NOBITS extent matches; objdiff .sbss score remains 42.857143%, with semantic source names versus extracted address labels. .data pool and generated tables are reported 100%; no placement objects or symbol renaming added.

- AOSS_81401778 — give runtime, packet-key and CRC objects their target global binding: 86.67033%; 270/273 instructions; frame ('stwu', 'r1, -0x60(r1)')/('stwu', 'r1, -0x60(r1)').

- AOSS_Init_old — represent connection and response waits as the target two-halfword array: 73.85038%; 1494/1584 instructions; frame ('stwu', 'r1, -0x110(r1)')/('clrlwi', 'r11, r1, 0x1b').

- AOSS_Init_old — use a whole-word wait pair with signed halfword views for target initialization stores: 73.85038%; 1494/1584 instructions; frame ('stwu', 'r1, -0x110(r1)')/('clrlwi', 'r11, r1, 0x1b').

The target-global-binding trial changed no instructions and regressed matched data 3896 -> 400, so it was reverted. Wait-array and whole-word wait-view trials changed no instructions and were reverted. All reverted experiments are absent from the source diff.

## Round-two final inventory

| Function | Target bytes | Compiled bytes before -> after | Objdiff % before -> after | Remaining difference |
| --- | ---: | ---: | ---: | --- |
| AOSS_Init_old | 6336 | 5976 -> 5976 | 73.34911 -> 73.85038 | Ninety instructions short; aligned frame and initial halfword stores differ. |
| AOSS_81400830 | 1284 | 1284 -> 1284 | 97.0405 -> 97.0405 | Register allocation and permutation-loop move order. |
| AOSS_814013AC | 456 | 456 -> 456 | 98.77193 -> 98.77193 | Registers and two entry moves exchanged. |
| AOSS_81401778 | 1092 | 1104 -> 1080 | 80.168495 -> 86.67033 | Three instructions short; merged global base, payload lifetime and CRC scheduling. |
| AOSS_81401E80 | 588 | 588 -> 588 | 98.605446 -> 98.605446 | XOR result and pointer registers. |

Instruction-exact 15/21 -> 15/21; objdiff exact 16/21 -> 16/21. Matched code 6436 -> 6436 of 16192 bytes; matched data 3896 -> 3896 of 3928 bytes. Fuzzy 87.91403 -> 88.54867%. No new instruction-exact function this round; this is partial progress, not unit completion.

All five nonmatching functions received at least three successful distinct source-level experiments. Changed or failed trials were measured and reverted unless they improved the retained state. No data placement, symbol-address names, artificial objects or inline assembly were introduced. Target-global binding and alternative wait views were discarded. The initializer's original local alignment is unresolved; no unsupported alignment was retained. The gate's CR1 branch normalization still undercounts one already-100% function, as in ATERM.

Full final gate:

```
full build: ok
main.dol sha1: 26116613f624061ba99c8d1a299aaa6efa85670d
[src/scene/setting/AOSS] pool: IDENTICAL
[src/scene/setting/AOSS] objdiff: code 6436/16192 data 3896/3928 functions 16/21 fuzzy 88.5487 linked code 0
[src/scene/setting/AOSS] instruction-exact functions: 15/21
[src/scene/setting/AOSS]   section .bss size 3496 match 100.0
[src/scene/setting/AOSS]   section .data size 368 match 100.0
[src/scene/setting/AOSS]   section .sbss size 32 match 42.857143
[src/scene/setting/AOSS]   section .sdata size 24 match 100.0
[src/scene/setting/AOSS]   section .sdata2 size 8 match 100.0
[src/scene/setting/AOSS]   section .text size 16192 match 88.54867
[src/scene/setting/AOSS]   below 100: AOSS_Init_old 73.85038
[src/scene/setting/AOSS]   below 100: AOSS_81400830 97.0405
[src/scene/setting/AOSS]   below 100: AOSS_814013AC 98.77193
[src/scene/setting/AOSS]   below 100: AOSS_81401778 86.67033
[src/scene/setting/AOSS]   below 100: AOSS_81401E80 98.605446
[src/scene/setting/AOSS] baseline: code 6436/16192 data 3896 functions 16 fuzzy 87.9140
regressions vs baseline: 0
global matched_code_percent: 86.26884 -> 86.26884
global fuzzy_match_percent: 98.87921 -> 98.88315
global complete_code_percent: 60.34391 -> 60.34391
global matched_data_percent: 90.91213 -> 90.91213
forbidden patterns added (net, per file): 0
readability warnings (net, per file; must be 0 in the final result): 0
GATE PASS
```
